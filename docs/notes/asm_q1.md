# Assembly to C, round q, agent q1: rdClip_Line2D and five frustum clippers

Scope: six GRIMFANDANGO.EXE functions of `src/GRIMFANDANGO.EXE/rdclip.c` that were still built from the original machine
code: rdClip_Line2D and the clippers rdClip_Face3_Pos, _PosB, _Pos_2, _PosB_2, _PosUv.  (The other five Face3 clippers
are agent q2's.)

Result: **all six converted to C, each checked against the original 1.01 machine code with a differential test: 0
differences in 1,000,000 cases per function** (plus a handful of NaN-payload-only cases that need a signalling NaN input,
see "Known differences").  The cleanroom tests: 5107 of 5107 the same as the original.

Files:

* `build/overrides_asm_q1.c`: the C (GRIM_EXE), one `/* OVERRIDES: name */` line before each definition.
* `build/difftest/asm_q1/`: `q1_test.c` (the test of all six), `build.sh` (slices the original functions and `_ftol` out
  of the 2df265d `asm_funcs.s`, links them with the C, the data image and int3 stubs), `run_all.sh` (all runs below),
  `mutate.py` (sensitivity check).
* `names/asm_funcs.json`: the six addresses removed; `src/GRIMFANDANGO.EXE/asm_funcs.s`: their bodies removed
  (`build/difftest/asm_p2/strip_asm.py`); `src/GRIMFANDANGO.EXE/rdclip.c`: regenerated (only the "NOT COMPILED" comment
  lines of the six functions change to "replaced by the hand-written version").  No assembled function called any of
  the six.

## Converted

| address | name | what it does | verification |
|---|---|---|---|
| 00446c10 | rdClip_Line2D | Cohen-Sutherland clip of an integer line against the canvas rectangle (canvas +0x18..+0x24), outcodes from rdClip_Outcode2D; 1 = visible (end points written back), 0 = outside | 1,000,000 cases, 0 differences |
| 004478c0 | rdClip_Face3_Pos | Sutherland-Hodgman clip of a position polygon against the perspective frustum: side planes slope*y with the slopes fr[9], fr[10] (x) and fr[7], fr[8] (z), then near fr[1], far fr[2] when fr[0] != 0 | 1,000,000, 0 |
| 00448260 | rdClip_Face3_PosB | the same for an orthographic view: constant bounds fr[3], fr[5] (x) and fr[4], fr[6] (z) | 1,000,000, 0 |
| 004489b0 | rdClip_Face3_Pos_2 | the machine code of Face3_Pos with the slopes fr[12], fr[10], fr[11], fr[8] | 1,000,000, 0 |
| 00449350 | rdClip_Face3_PosB_2 | byte for byte the same code as Face3_PosB (only the addresses differ) | 1,000,000, 0 |
| 0044a6d0 | rdClip_Face3_PosUv | Face3_PosB with one intensity per vertex (param_3; there are no uvs despite Ghidra's name), interpolated with the same t | 1,000,000, 0 |

The five clippers share one C pass function (`q1_pass`, one Sutherland-Hodgman pass against one plane) and one driver
(`q1_clip`, the plane sequence and the buffer ping-pong); the per-plane differences of the machine code are parameters.
The details (which value is stored as a float, which compare is "or unordered") are in the block comments of the override
file; in short:

* **Calling convention.** All six are cdecl (the caller pops), return the count / result in EAX and leave the x87 stack
  empty.  The prototypes of functions.h are kept (PosUv / PosB return int or uint; none returns float).
* **Buffers and globals.** Positions ping-pong between the caller's array and the static buffer UINT_007f48c0 (43
  vertices; it is followed by the clip flags UINT_007f4ac4), intensities (PosUv) between the caller's array and
  UINT_007f47c0.  At the start of every pass UINT_007f47b8 / UINT_007f46ac get the input / output position buffers
  (UINT_007f4618 / UINT_007f46b0 the intensity ones for PosUv).  UINT_007f4ac4 is cleared at the start and gets 0x10 /
  0x20 / 4 / 8 / 1 / 2 for an intersection with the x-low / x-high / z-high / z-low / near / far plane, 0x40 when the
  near pass leaves fewer than 3 vertices.  A pass that leaves fewer than 3 vertices ends the clip (no copy back; the
  caller's array may hold the output of pass 2 or 4); otherwise a result in the static buffer is copied back with dword
  moves (positions, then intensities).
* **Compares.** Each side plane uses one of two compare patterns (planes 1 and 4: P in when !LT_U(P, a), C in when
  LE_U(b, C); planes 2 and 3: P in when LE_U(P, a), C in when !LT_U(b, C)); near uses !LT_U on both ends, far LE_U on
  both ends.  An intersection is added only when neither end is exactly on the plane (equal or unordered) and one end is
  out; then the current vertex is added when it is in.  These matter only for NaNs and exact ties, and the test covers
  both.
* **Perspective intersection.** a = float(slope * P.y), b = slope * C.y unrounded; DY = float(C.y - P.y),
  DX = float(C.x - P.x), den = slope*DY - DX (extended), s = C.y*P.x - P.y*C.x divided by float(den) unless the extended
  den is 0 or unordered.  x planes: X = float(slope*s), u = (X - P.x)/DX when |DY| <= |DX| (or unordered), else
  (s - P.y)/DY; out = (X, s, (C.z - P.z)*u + P.z).  z planes: Z = slope*s stays extended (used for u and stored as z).
* **Orthographic / near / far intersection.** t = (k - P.c)/(C.c - P.c); the clipped coordinate is FLD/FSTP of the
  bound for the side planes but a dword copy of fr[1] / fr[2] for near / far; store order x, y, z (near / far: y, z, x),
  then the intensity.
* **rdClip_Line2D.** Ghidra lost the _ftol operands; written from the machine code: the "vertical" test compares the
  exact integer x0 with float(x1), "horizontal" float(y0) with float(y1), both once before the loop.  For a top / bottom
  edge the new x is x0 + (edge - y0) * ((x1 - x0)/(y1 - y0)) unrounded and the new y the integer edge; for left / right
  the new y is the same formula stored as a float.  The outcode of the moved point is taken from _ftol (64-bit
  truncation, low dword) of the unrounded values while the end point keeps their floats; the final write-back truncates
  the floats.  `_ftol` is `(int)(long long)x` in the C (same fistp qword with truncation).

Behaviour kept from the original that looks odd:

* Face3_Pos and Face3_Pos_2 use different slope fields for the low-x and high-z planes (9 / 7 against 12 / 11) but the
  same ones for the other two (10, 8).
* Face3_PosB and Face3_PosB_2 are two copies of the same function.
* A polygon that grows past 43 vertices overruns the static buffer into the clip flags and beyond (the C writes the same
  addresses in the same order; the test compares the data image from 0x7f4600 to 0x7f5400 and generates such polygons).
* rdClip_Line2D moves the first end point whose outcode is non-zero, uses x0 for a vertical line even when moving the
  second end point, and ends any loop only through the outcodes (a NaN / infinite slope gives _ftol's 0x80000000 low
  dword 0, as in the original).

Not reproduced (no effect on callers): the originals use their own parameter slots as scratch (Line2D keeps float(x0) in
the canvas slot; the clippers keep plane bounds, DY and loop counters in the frustum / count / position slots); the C
uses locals.  All callers are C (rdPrimit2_DrawLine, rdPrimit3_ClipFace, the overrides_logic.c callers of
rdClip_Face3_Pos_2) and do not read their argument slots back.

## Differential test

`build/difftest/asm_q1/run_all.sh [cases]` (needs `build/obj/GRIMFANDANGO.EXE/data_s.o`, or uses the main checkout's;
makes `out/base_asm_funcs.s` from `git show 2df265d:src/GRIMFANDANGO.EXE/asm_funcs.s`).

* Inputs: Face3 polygons of 0..16 vertices (and negative counts), convex fans and random point sets around the frustum,
  vertices snapped onto planes (x = float(slope*y), float of the double product, one ulp off, y = near / far, x = bound),
  duplicated vertices, special values (0, -0, +-inf, quiet and signalling NaN, denormals, FLT_MAX), frustum slopes and
  bounds of both signs and special values, far plane on / off, near > far.  Line2D: canvas rectangles (also empty or
  inverted, huge), end points inside / outside / on the edges, vertical and horizontal lines, values up to +-2^31
  (float rounding of x0, _ftol beyond the int range).  Every fourth case has ten times more special values.
* Each case runs the original and the C on the same addresses from the same start state (restored in between) under
  the x87 precision control 24, 53 or 64 bits, and compares the return value, the caller's arrays (also past the
  polygon), the data image 0x7f4600..0x7f5400 (static buffers, pointer globals, flags; randomised before each case),
  the call log of the rdClip_Outcode2D stand-in (the real outcode, logged; ends any loop after 64 calls), the x87
  control word and the stack top.
* Coverage per 100,000 Face3 cases: each plane flag is set in 3,800 to 35,000 cases, 0x40 in 4,900 to 6,800; Line2D:
  more than one clip step in 56% of the cases.  One Face3 case in 25 is a tiny polygon (coordinates scaled by 2^-100 ..
  2^-139, edges with DX == 0 and DY of a few denormal steps).
* Signalling NaNs: the generator keeps every value as bits (a float return value goes through st0 and would quieten a
  signalling NaN; the first version of the test did that and generated almost none).
* Flags: the C is tested compiled the way `build/link.py` compiles override files (`/mingw32/bin/gcc`, no -O), and with
  the Makefile flags at -O0 and -O2.

Results of `run_all.sh 1000000` (cases per function; NaN-payload-only = only NaN bits differ, both quiet NaNs, with a
signalling NaN input, see below):

| configuration | Line2D | Pos | PosB | Pos_2 | PosB_2 | PosUv |
|---|---|---|---|---|---|---|
| link.py flags (the C actually linked) | 1,000,000: 0 | 1,000,000: 0 (+21) | 1,000,000: 0 (+47) | 1,000,000: 0 (+24) | 1,000,000: 0 (+59) | 1,000,000: 0 (+371) |
| link.py flags, `Q1_NAN=1` (no signalling NaN inputs) | 0 | 0 (+0) | 0 (+0) | 0 (+0) | 0 (+0) | 0 (+0) |
| Makefile flags -O0 | 0 | 0 (+21) | 0 (+47) | 0 (+24) | 0 (+59) | 0 (+371) |
| Makefile flags -O2 (250,000 each) | 0 | 0 (+16) | 0 (+28) | 0 (+11) | 0 (+29) | 0 (+164) |

`mutate.py`: 18 deliberately wrong versions (rounding points of the perspective bounds, u, den, the
intensity; compare kinds with NaN; `<` for `<=` in the |DY| / |DX| choice and the far plane; equality not excluded on
the near plane; flag 0x40 after any pass; FLD/FSTP of a kept intensity; the Pos_2 slope fields; Line2D's outcode of the
rounded point, the unrounded left / right y, a 32-bit conversion instead of _ftol): all 18 are reported (30,000 cases
each).  Dropped as equivalent: "P in when < far" (a P exactly on the plane is never interpolated, its C decides alone),
Line2D's vertical test on float(x0) instead of the integer (with x1 - x0 == 0 the general formula gives x0 too), and
FLD/FSTP against a dword copy of a plane bound in an intersection (only a NaN bound would show it, and a NaN bound never
produces an intersection).  Not reachable by random inputs: testing float(den) instead of the extended den against 0.
They differ only when 0 < |den| < 2^-149 on an edge that crosses the plane.  For a crossing edge |den| >= |P.x - k*P.y|,
and that is at least 2^-150 because P.x is a float strictly on the other side of float(k*P.y).  So it needs den == +-2^-150
exactly, which rounds to 0 as a float.

### Known differences (signalling NaN inputs only)

When an input is a **signalling** NaN and the other operand of the same subtraction / addition is a different quiet NaN,
the original returns the quiet one (it uses memory operands, `fsub dword ptr`, and the x87 picks the QNaN over an SNaN),
while gcc loads every float with FLD first (which quiets the SNaN) and the x87 then picks the larger payload.  Only NaN
bits differ; the test counts these cases separately ("NaN-payload-only", allowed only when an input holds a signalling
NaN) and with every input NaN quiet (`Q1_NAN=1`) there are none.  Game data has no signalling NaNs.  (Same as asm_p2.)

## Build and checks

* `rm -f src/*/*.[ch] src/*/*.md && python -I tools/build_src.py && make -C build -j8 && make -C build link`: all pass
  (EXE 180 objects).  build_src.py also rewrote `src/GRIMFANDANGO.EXE/stddisplay.c` (`(longlong)_CIpow()` ->
  `FTOL(_CIpow())`, unrelated to this work, the same at 2df265d); it was restored with `git checkout`.
* Cleanroom: `cd grim_tools/cleanroom && GRIM_DECOMP=<worktree>\build\run python run.py decomp` (the four binaries
  copied to build/run): `0 of 5107 tests differ, 0 are close (within 0.001), 5107 the same`.
* `build/perf/libcheck.py` was not run.

## Left assembled

None of the six.
