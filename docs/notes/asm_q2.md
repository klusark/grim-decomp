# Assembly to C, round q, agent q2: five face clippers

Scope: five GRIMFANDANGO.EXE functions of `src/GRIMFANDANGO.EXE/rdclip.c` that were still built from the original
machine code: rdClip_Face3_PosUvLit, rdClip_Face3_PosUvLit_2, rdClip_Face3_PosUvFlags, rdClip_Face3_PosUvLitColor,
rdClip_Face3_PosUvLitFlags.  (rdClip_Line2D and the other five clippers are agent q1's.)

Result: **all 5 converted to C, each verified against the original 1.01 machine code by a differential test
(0 differences in 1,000,000 cases per function with the build/link.py flags, plus 250,000 per function in each of
three more configurations).**  Nothing stays assembled.

Files:

* `build/overrides_asm_q2.c`: the C (GRIM_EXE), one `/* OVERRIDES: name */` line before each definition.  The five
  functions share one plane routine (`q2_clip_plane`) and one driver (`q2_clip`).
* `build/difftest/asm_q2/`: `clip_test.c` (the test of all five), `build.sh` (slices the original functions out of
  the 2df265d `asm_funcs.s`, links them with the C, the data image and int3 stubs), `run_all.sh` (all runs below),
  `mutate.py` (sensitivity check).
* `names/asm_funcs.json`: the five addresses removed (EXE list 271 -> 266).
* `src/GRIMFANDANGO.EXE/asm_funcs.s`: the five bodies removed with `build/difftest/asm_p2/strip_asm.py`.

## Converted

| address | name | what it does | verification |
|---|---|---|---|
| 00449aa0 | rdClip_Face3_PosUvLit | perspective frustum clip of positions + 1 intensity per vertex | 1,000,000 (link.py flags) + 3 x 250,000, 0 differences |
| 0044b0a0 | rdClip_Face3_PosUvLit_2 | perspective clip of positions + uv | same, 0 |
| 0044be80 | rdClip_Face3_PosUvFlags | orthographic clip of positions + uv | same, 0 |
| 0044c9d0 | rdClip_Face3_PosUvLitColor | perspective clip of positions + uv + intensity | same, 0 |
| 0044da40 | rdClip_Face3_PosUvLitFlags | orthographic clip of positions + uv + intensity | same, 0 |

What they do (all five have the same structure; the attribute sets and the plane kind differ):

* Sutherland-Hodgman against six planes of the frustum record `f` (passed by rdPrimit3_ClipFace):
  perspective x >= f[12]*y (flag 0x10), x <= f[10]*y (0x20), z <= f[11]*y (0x04), z >= f[8]*y (0x08);
  orthographic x >= f[3], x <= f[5], z <= f[4], z >= f[6] (same flags); then near y >= f[1] (0x01) and, only when
  f[0] != 0, far y <= f[2] (0x02).  A plane that writes an intersection ORs its flag into UINT_007f4ac4 (cleared at
  the start); a polygon that the near plane leaves with fewer than 3 vertices also gets 0x40.
* The arrays ping-pong: plane 1 reads the caller's arrays and writes the static buffers 0x007f48c0 (positions),
  0x007f46b8 (uv), 0x007f47c0 (intensity); plane 2 writes back into the caller's arrays; and so on.  The current
  input / output pointers live in the globals 0x007f47b8 / 0x007f46ac (positions), 0x007f461c / 0x007f46a8 (uv),
  0x007f4618 / 0x007f46b0 (intensity) and are swapped before each plane (only the ones the function uses).
* After any plane that leaves fewer than 3 vertices the count is returned at once (no swap, no copy-back; the caller's
  arrays keep what an intermediate plane wrote).  Otherwise, when the last output is not the caller's position array
  (far plane disabled), positions, uv and intensities are copied back with dword copies.

Calling convention (checked in the assembly): all five are cdecl, (frustum, positions, [uv,] [intensities,] count),
return the vertex count in EAX and leave the x87 stack empty; the caller pops.  This is how rdPrimit3_ClipFace
(overrides_logic.c) already calls them, through int-returning pointers (commit a09980a).

Prototype changes: none in `functions.h`.  Ghidra declares PosUvLit, PosUvLit_2 and PosUvLitColor as returning
`float`; the override file renames the `functions.h` prototypes while it is included (as overrides_asm_p2.c does) and
defines all five as returning `uint` with an `int` count, which is the real ABI (EAX).  The only caller,
rdPrimit3_ClipFace, uses its own int-returning function pointer types and is unchanged.

Behaviour kept from the original (all in `q2_clip_plane`; see its block comment):

* perspective side planes: the bound of the previous vertex `k*prev.y` is stored as a float before it is compared,
  the bound of the current vertex `k*cur.y` is compared unrounded;
* the intersection: dy and da (a = x or z) stored as floats; `den = k*dyF - daF` is compared with 0 unrounded but the
  division uses the float denF; `N = cur.y*prev.a - prev.y*cur.a` extended; `Y = N/denF` (N itself when den is 0 or
  NaN); `kY = float(k*Y)`; `t = (Y - prev.y)/dyF` when |dyF| > |daF| (ordered), else `(kY - prev.a)/daF`; the new
  vertex is a = kY, y = float(Y), other attributes `(cur - prev)*t + prev` rounded at the store;
* orthographic side planes: `t = (c - prev.a)/(cur.a - prev.a)`, a = c through FLD/FSTP;
* near / far: `t = (c - prev.y)/(cur.y - prev.y)`, y = the dword of f[1] / f[2] (MOV);
* NaN handling of the compares: the "both outside" test, the "edge crosses" test (both compares ordered and not
  equal) and the "keep the current vertex" test have their own unordered results per plane kind (>= / <= / near / far);
* kept vertices and the copy-back are dword copies (NaN bits survive).

Not reproduced (no effect on the caller): the original uses its own parameter slots (the count, the uv pointer) as
scratch for float temporaries and the running intensity pointer; the C uses locals.  rdPrimit3_ClipFace never reads
its outgoing argument area after the call.

## Differential test

`build/difftest/asm_q2/run_all.sh [cases]` (needs `build/obj/GRIMFANDANGO.EXE/data_s.o` of a linked build; makes
`out/base_asm_funcs.s` from `git show 2df265d:src/GRIMFANDANGO.EXE/asm_funcs.s`).

* Inputs per case: a frustum record (slopes f[8], f[10..12] random or simple values 0, -0, +-0.5, +-1, +-2, ...,
  constants f[3..6], near / far, far enable 0 / 1 / random), a polygon of -1..10 vertices (random, small integers and
  halves, "inside the view" polygons, vertices placed exactly on a plane: x = float(k*y), z = float(k*y), y = near /
  far, x or z = an orthographic constant), uv and intensities; special values 0, -0, +-inf, quiet and signalling NaN,
  denormals, smallest normal, largest finite (also whole frustum records of them); a denormal mode (coordinates of a
  few 2^-149, slopes 0.25 .. 1.5) for the `den` rounding; a random start state of the work area 0x007f4600..0x007f4ad0.
* Each case runs the original and the C on the same state under the x87 precision control 24, 53 or 64 bits and
  compares the return value (EAX), the caller's arrays (512 vertices each, so overruns show), the whole work area (the
  three static buffers, the six pointer globals, the clip flags), the x87 control word and stack top.  A difference
  where every differing dword is NaN on both sides would be counted as "NaN-payload-only" and also fails the run;
  there were none.

Runs (`run_all.sh 1000000`, 2026-11-09):

| configuration | cases per function | differences |
|---|---|---|
| C compiled with the build/link.py flags (`/mingw32/bin/gcc`, no -O; the object linked into the game), all inputs | 1,000,000 | 0 (0 NaN-payload-only) in each of the five |
| same, no signalling NaN inputs, other seed (`Q2_NOSNAN=1 Q2_SEED=7`) | 250,000 | 0 |
| C with the Makefile flags at -O0 (`Q2_SEED=11`) | 250,000 | 0 |
| C with the Makefile flags at -O2 (`Q2_SEED=13`) | 250,000 | 0 |

Plane flags seen in the 1,000,000 link.py-flag cases (0x01 near, 0x02 far, 0x04 / 0x08 / 0x10 / 0x20 sides,
0x40 near left < 3): PosUvLit 105504 / 119972 / 340473 / 272494 / 626168 / 494980 / 37914; PosUvLit_2 105689 /
119975 / 339089 / 272775 / 626178 / 495132 / 37786; PosUvFlags 179951 / 100561 / 400075 / 365164 / 614962 /
571799 / 76079; PosUvLitColor 105652 / 119690 / 339738 / 272522 / 626635 / 495310 / 37927; PosUvLitFlags 180757 /
100376 / 400948 / 365846 / 615402 / 573207 / 76812.  Results: about 43-47% return 0 (outside or degenerate), the rest 1 or more vertices.

`mutate.py 20000`: 20 deliberately wrong versions (rounding of the previous / current bound, den, dy, kY, Y and N
products, the |dy| > |da| branch, the unordered results of the keep and crossing tests of each plane kind, the
orthographic t, uv / intensity interpolation, 0x40 after the far plane, the copy-back, the pointer swap, the far
enable): **0 of 20 missed**.  Five more are listed in mutate.py and not run: four are equivalent (the unordered part
of the three "both outside" tests: an unordered compare already blocks the crossing and decides the keep test; near /
far y through FLD/FSTP: a NaN near / far blocks every crossing), and one the test cannot show (den tested after
rounding to float: only for 0 < |den| <= 2^-150 on a crossing edge, which the denormal mode never produced; the C
follows the original there).

## Build and clean-room tests

* `strip_asm.py` (asm_p2's) took the five bodies out of `src/GRIMFANDANGO.EXE/asm_funcs.s` (5335 lines), and the five
  addresses out of `names/asm_funcs.json`, so every caller reaches the C.
* `rm -f src/*/*.[ch] src/*/*.md && python -I tools/build_src.py`: the only tracked change kept is `rdclip.c` (the five
  Ghidra texts now say "replaced by the hand-written version").  build_src.py also rewrote three `(longlong)_CIpow()`
  casts in `stddisplay.c` (Palette_FromFloatTable) to `FTOL(...)`, unrelated to this work; that file was restored to
  its committed text.
* `make -C build -j8`, `make -C build link`: pass (EXE, LUA, IMUSE, CHORE linked; overrides_asm_q2.o defines the five
  symbols).  The four binaries were copied to `build/run`.
* Clean-room tests: `cd /c/Users/Joel/grim_tools/cleanroom && GRIM_DECOMP=<worktree>\build\run ~/venv/bin/python.exe
  run.py decomp`: **`0 of 5107 tests differ, 0 are close (within 0.001), 5107 the same`**.
* `build/perf/libcheck.py` (optional) was not run: it needs a private game data directory (default
  `C:\Users\Joel\grimM_data`, absent), and the other data copies belong to other sessions.

## Left assembled

None of the five.
