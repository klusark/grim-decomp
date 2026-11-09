# Assembly to C, upper half (agent asm_p2)

Scope: the GRIMFANDANGO.EXE addresses of `names/asm_funcs.json` (291 at bb04517), sorted by address, upper half:
146 functions from 0x00436e80 (`rdRaster_Draw_TexLitKeyZw_5`) to 0x004d6100.  The lower half (to 0x00436be0) is the
other agent's.

Result: **7 functions converted to C, each verified against the original 1.01 machine code by a differential test
(0 differences in 1,000,000 cases per function; see "Known differences" for signalling-NaN inputs).**
139 stay assembled (table below).

Files:

* `build/overrides_asm_p2.c`: the C (GRIM_EXE), one `/* OVERRIDES: name */` line before each definition.
* `build/difftest/asm_p2/`: `math_test.c` (the test of all seven), `build.sh` (slices the original functions out of the
  bb04517 `asm_funcs.s`, links them with the C, the data image and the stand-ins), `run_all.sh` (all runs below),
  `mutate.py` (sensitivity check), `strip_asm.py` (smoke-test helper, below).
* Not changed: `names/asm_funcs.json`, `src/`.  The seven functions are still listed in `asm_funcs.json` and still in
  `src/GRIMFANDANGO.EXE/asm_funcs.s`; the integrator removes them at the next regeneration.  Until then the build links
  the C for C callers (override objects come before `asm_funcs.o`, `--allow-multiple-definition`), but assembled callers
  inside `asm_funcs.s` still call the assembled copy (the assembler resolves calls within the file).

## Converted

| address | name | what it does | verification |
|---|---|---|---|
| 0044e7d0 | Frustum_TestSphere | sphere vs view frustum: 2 outside, 1 crossing, 0 inside; depth axis y; perspective camera (type 1) scales the side planes with depth | 1,000,000 cases, 0 differences |
| 0044ea50 | Polygon_ClipToPlane | Sutherland-Hodgman clip of a polygon (positions, optional uv and intensities) against one plane through the static buffers 0x007f48c0 / 0x007f46b8 / 0x007f47c0, copied back; returns the count | 1,000,000, 0 |
| 0044eeb0 | Angles_ToMatrix | 3x4 matrix of pitch / yaw / roll through Math_SinCosTable, translation copied | 1,000,000, 0 (+270 NaN-payload-only, below) |
| 0044f080 | Angles_ToMatrixNoPos | same, translation 0 | 1,000,000, 0 (+241 NaN-payload-only) |
| 0044f210 | Matrix_AxisAngle | rotation about a unit axis; special cases for axis z within 1e-5f of +1 / -1 | 1,000,000, 0 (+6 NaN-payload-only) |
| 00451510 | rdLight_CalcVertexIntensities | per-vertex light level (types 0/1 direct, 2 omni, 3 spot), clamped to 1.0f, returns the mean | 1,000,000, 0 |
| 00451dd0 | rdCanvas_DrawPoint | point of radius r drawn as a polygon of rdPrimit2_DrawLine segments, when its box touches the canvas rect | 250,000, 0 |

The per-function details (which value is stored as a float before use, which compare is "or unordered", the
order of the sums) are in the block comment above each function in the override file.

Prototype changes (the symbol stays the same; the functions.h prototype is renamed while it is included):

* `rdLight_CalcVertexIntensities` returns `long double`: the original returns the unrounded quotient in st0
  (`fild qword; fdivr`); Ghidra declared `float`.  Same ABI (st0).
* `Matrix_AxisAngle` takes the angle as `uint`: it only passes the dword on to Math_SinCosTable, and with a float
  parameter gcc -O2 copies it with FLD/FSTP (changes a signalling NaN; the -O2 test found it).
* `Polygon_ClipToPlane` keeps Ghidra's prototype; the last parameter (`uint *param_6`) is the vertex count.

Behaviour kept from the original that looks odd:

* Polygon_ClipToPlane copies three dwords of uv for a kept vertex (the third lands on the next output vertex, or
  stays behind the last one), and reads vertex n-1 and its intensity even when n <= 0.
* rdLight_CalcVertexIntensities: for light types < 2 the range test is `0 < range^2`; the squared distance is
  `dx * float(dx) + ...` with dx extended; the spot term multiplies by `dot(n, dir)` (unclamped), not `dot(n, L)`.
* rdCanvas_DrawPoint: the loop test `angle + step <= 360` uses the unrounded sum, the next angle is the float;
  a NaN or non-positive step loops forever, as in the original.
* Frustum_TestSphere: the first near test compares the unrounded `y + r`; the "y + r" / "y - r" style values that
  are compared later are floats; the perspective bound `k * (y - r)` stays extended while `k * (y + r)` is stored.

Not reproduced (no effect on callers): the original writes temporaries into its own parameter slots
(Frustum_TestSphere, Polygon_ClipToPlane, Angles_ToMatrix*, Matrix_AxisAngle, rdLight_CalcVertexIntensities); the C
uses locals.

## Differential test

`build/difftest/asm_p2/run_all.sh [cases]` (needs a linked build for `build/obj/GRIMFANDANGO.EXE/data_s.o`; makes
`out/base_asm_funcs.s` from `git show bb04517:src/GRIMFANDANGO.EXE/asm_funcs.s`).

* Inputs: small integers and halves (ties), random floats, and 0, -0, +-inf, quiet and signalling NaN, denormals,
  1e-5f neighbours, values near +-1; targeted ties: frustum side bounds equal to `float(k * y)`, light ranges equal to
  `float(sqrt(d^2))`, spot cone cosines equal to the float of the extended dot product (set by the Vec3_Normalize
  stand-in), DrawPoint steps whose sum ends within half an ulp above 360 (searched at start-up), polygons up to 16
  vertices with a vertex on the plane.
* Each case runs the original and the C on copies of the same state under the x87 precision control 24, 53 or 64
  bits and compares the return value (the 80-bit st0 for rdLight_CalcVertexIntensities), all output buffers, the
  static clip buffers, the call log of the stand-ins (Math_SinCosTable / Vec3_Normalize write values from a per-case
  stream; rdPrimit2_DrawLine records its arguments), the x87 control word and the x87 stack top.
* The C is tested with the Makefile flags at -O0 and -O2 and with the flags `build/link.py` really compiles override
  files with (`/mingw32/bin/gcc`, no -O, no -fwrapv / -fsingle-precision-constant): 0 differences in every
  configuration (1,000,000 cases at -O0 and link.py flags, 250,000 at -O2).
* `mutate.py`: 19 deliberately wrong versions (rounding points, compare kinds, operand order, the uv third dword,
  FLD/FSTP vs dword copy, the 360 loop test, the clamp, ...): all 19 are reported.  Two mutations that cannot be seen
  were dropped as equivalent: `<` instead of `<=` against 1e-5f in Matrix_AxisAngle (|1 - z| of a float z is never
  exactly 1e-5f) and in the 1.0f clamp of rdLight_CalcVertexIntensities (both store 1.0f).

### Known differences (signalling NaN inputs only)

Angles_ToMatrix / NoPos and Matrix_AxisAngle can return a different NaN (payload / sign) than the original when an
input is a **signalling** NaN and another operand of the same operation is a different NaN: the original uses memory
operands (`fmul dword ptr`), where the x87 returns the quiet operand over the signalling one; gcc loads every float with
FLD first (which quiets it), and then the x87 picks the larger payload.  Only the NaN bits differ (the test counts
these separately as "NaN-payload-only": about 1 case in 4000 with these inputs); with no signalling NaN in the inputs
(`P2_NAN=1`) there are 0 such cases at -O0.  At -O2 gcc also moved negations past multiplications (`(-a)*b` ->
`-(a*b)`), which changed the sign of NaN results; negations are now a separate volatile step (p2_neg) and the -O2 run
shows only the signalling-NaN cases.  Game data has no signalling NaNs.

## Build and smoke test

* `python -I tools/build_src.py`, `make -C build -j8`, `make -C build link`: all pass (EXE, LUA, IMUSE, CHORE linked).
* For the smoke test the seven functions were removed from a local copy of `asm_funcs.s` (`strip_asm.py`) so every
  caller, assembled ones included, used the C; then `src/` was restored with `git checkout -- src`.
* `build/perf/libcheck.py` (tag asmp2, shared GRIMDATA): boot to Manny's office, Lua probes, save / load round trip, no
  Lua errors, process alive: all PASS.  Against a baseline build of bb04517 (same procedure, overrides file removed):
  probe.txt identical except the `RU` line (random() before randomseed, differs between any two runs), the idle and
  walk shots pixel-identical (0.000%); the set shots differ by 0-5% between ANY two runs, the baseline against itself
  included (5.0% / 4.7% / 0.02% / 5.0% / 0%), so they say nothing about this change.
* Manny looks wrong (a blocky blue mesh) in the walk shot of both builds; that is the rendering bug the other work
  stream fixes, not this change (the baseline shot is pixel-identical).

## Left assembled (139)

| addresses | names | reason |
|---|---|---|
| 00436e80 - 00446030, 00451fa0 - 004710e0 (113) | rdRaster_* | excluded from this pass: a separate rendering-bug fix changes them |
| 00446c10 - 0044da40 (11) | rdClip_Line2D, rdClip_Face3_* | excluded (rendering-bug fix) |
| 004507e0, 00450ba0 | rdPuppet_AdvanceTrack, rdPuppet_UpdateFrame | excluded (rendering-bug fix) |
| 004ac6f0 | _ftol | the CRT float-to-int helper: switches the x87 rounding mode and returns EDX:EAX; machine code by definition (asm_reasons_logic.json) |
| 004addf0 | FUN_004addf0 (__chkstk) | CRT stack probe: moves ESP by EAX bytes and returns into the caller's frame; not expressible in C |
| 004d5e1c, 004d5e30 | FUN_004d5e1c, FUN_004d5e30 | SEH filter / handler funclets: run on the parent function's EBP frame (`mov EDX,[EBP-0x14]`, `mov ESP,[EBP-0x18]`) and resume inside it |
| 004d6030, 004d6050, 004d6070, 004d6090, 004d609e, 004d60ac, 004d60d0, 004d60db, 004d6100 | FUN_004d6030 ... FUN_004d6100 | unwind funclets: free a slot of the parent's EBP frame ([EBP-0x10], [EBP+8], [EBP+4], [EBP-0x1fc]) or tail-jump to StateImage_Release with ECX from it; not standalone functions, no differential test possible |

None of the 146 had an existing `/* OVERRIDES */` in build/overrides_*.c.

## Open questions

* The seven functions stay in `names/asm_funcs.json` / `asm_funcs.s` until the integrator regenerates; until then
  assembled callers use the assembled copies (see above).
* Frustum_TestSphere's plane order (f[3] / f[5] for x, f[4] / f[6] for z, f[7..10] the perspective factors) was read
  from the code; the field names of the frustum record are not known.
