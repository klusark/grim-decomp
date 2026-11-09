# Assembled EXE functions, lower half (agent asm_p1): notes

Scope: the lower half by address of the 291 GRIMFANDANGO.EXE functions still listed in `names/asm_funcs.json`
(145 functions, 0x00404e00 - 0x00436be0).  128 of them are `rdRaster_*` functions, which are excluded (a separate
rendering fix changes them); none of the 145 is in the excluded `overrides_big_*.c` files.

File: `build/overrides_asm_p1.c` (13 functions).  The C was written from the 1.01 machine code
(`src/GRIMFANDANGO.EXE/asm_funcs.s`, checked against `raw/GRIMFANDANGO.EXE/sections/text.bin` where it mattered, e.g. the
jump tables); Ghidra's text was only a guide.  No remaster types were used.

## How it was verified

Differential tests in `build/difftest/asm_p1/` (`run_all.sh` builds and runs everything), derived from the
`asm_s2` harness:

* `rt.c`, `img.ld`, `grim_img.s`: the test program is linked at image base 0x400000 with a reserved section over
  0x401000 - 0x94e000 into which the ORIGINAL 1.01 text, rdata and data are loaded; the original function runs at its
  own address, unmodified.  `gensyms.py` defines every game symbol the C names at its 1.01 address, so both sides work
  on the same memory.
* Callees are recorders: `rt_patch(addr, id, argbytes)` writes `push id; jmp rec_thunk` at a callee's 1.01 address, so
  the original code and the C both reach `rec_dispatch` (rt.c), which appends the call (id and the argument words) to a
  log in the compared arena and runs a per-test handler (stand-in behaviour: file reads from a random stream, a bump
  allocator, vector ops on the real values, results derived from the inputs only).  Arguments that point to the
  caller's stack are logged by content (their addresses differ between the two sides).  A float-returning callee
  (`argbytes -1`) returns its value in ST0.
* `harness.h`: per case, random state and up to 8 argument words; the original runs; .data, the 4 MB arena (with the
  callee log), EAX, optionally ST0 and the x87 control word are saved; the state is restored and the C runs; all is
  compared.  Initial control words 0x027f / 0x007f / 0x037f (53, 24 and 64 bit precision).  A case where the original
  faults is skipped; the C faulting where the original does not is a difference.
* Sensitivity: `NEG=1` runs each original against the next function's C (all differ), and `mut.sh` with
  `mut_*.txt` applies single mutations to the C (a changed comparison, operand order, constant, rounding step) and checks
  that the test reports them.  Undetected mutations are listed per function below.
* `slice_test.sh`: the same tests with the reassembled asm of the build (`asm_funcs_fast.s`, sliced) in place of the C:
  the seven span drivers' assembled versions also match the 1.01 bytes.
* Compilations of the C under test: Makefile GHIDRA_CFLAGS at -O0, the exact `link.py` flags, and -O2.

## Converted (13)

| address | name | what it does | test (cases at -O0 + link.py + -O2) |
|---|---|---|---|
| 00404e00 | rdCanvas_EmitSpans | scanline span builder of the software canvas: walks the edge crossings, keeps the front-to-back list of covering polygons, computes dz/dx (float, and *65536 rounded with the DAT_00900526 control word), closes spans into the 0x2c-byte span table (flushes at 0x800) | test_canvas, 20000 + 5000 + 5000, 0 differences |
| 00405770 | rdCanvas_PreparePolygon | takes the next canvas polygon record, clamps the face modes, picks the cel, computes the light level, calls one of 15 rdRaster_Select_* selectors (or the face callback) | test_prep, 18670 + 4683 + 4683 ran (of 20000 + 5000 + 5000; the rest are textured faces without a material, where the original faults), 0 differences |
| 00409580 | rdModel_ComputeMeshLighting | the same mode / cel / light-level logic for the D3D path, calls the face draw callback | test_light, 20000 + 5000 + 5000, 0 differences |
| 0040b8e0 | rdModel3_LoadBinary | binary model reader through g_pSvcRdroid pFread / pAlloc / pFree, rdMaterial_Load for the materials | test_lbin, 5000 + 1250 + 1250 generated streams of which 2229 + 562 + 562 ran, 0 differences (the rest make the original fault on a huge count and are skipped) |
| 0040d230 | rdModel_DrawMesh | frustum / clip-plane culling, vertex transform, light collection (modes 2 and 3) with the original's x87 precision, back-face test, rdModel_AddMeshToCache | test_mesh, 20000 + 5000 + 5000, 0 differences |
| 0040e500 | rdPrimit3_CopyFaceVerts | copies an unclipped face into the output vertex pools (positions, uvs + offset, clamped intensities) | test_prim, 20000 + 5000 + 5000, 0 differences |
| 00410330 | FUN_00410330 | span driver of rdRaster_Select_FlatLit: Gouraud-lit flat colour, 8 and 16 bpp, then the z-write pass | test_drv, 3000 + 750 + 750, 0 differences; see the in-game note below |
| 00410970 | FUN_00410970 | span driver of rdRaster_Select_FlatLit_2: copies the interpolants, picks rdRaster_SpanR16_Tex* by texture size (Mem_DumpLog at 8 bpp), z-write pass | test_drv, same counts, 0 differences |
| 00411740 | FUN_00411740 | the same for rdRaster_SpanR16_Tex_7 .. _12 | test_drv, 0 differences |
| 004125c0 | FUN_004125c0 | the same for rdRaster_SpanR16_TexLit_3 .. _9 | test_drv, 0 differences |
| 00413590 | FUN_00413590 | perspective version (rdRaster_SpanP16_Tex .. _6, also copies the perspective terms) | test_drv, 0 differences |
| 00414d20 | FUN_00414d20 | the same for rdRaster_SpanP16_Tex_7 .. _12 | test_drv, 0 differences |
| 00416580 | FUN_00416580 | the same for rdRaster_SpanP16_TexLit_3 .. _9 | test_drv, 0 differences |

The jump tables of the seven span drivers and of rdModel_ComputeMeshLighting / rdCanvas_PreparePolygon /
rdPrimit3_CopyFaceVerts / rdModel_DrawMesh were read from the 1.01 bytes (`jt.py`); the repeated per-mode blocks of
ComputeMeshLighting and PreparePolygon were compared instruction by instruction (`blkdiff.py`): they differ only in
the called selector, so the C uses a table.

Details that the C reproduces on purpose:

* x87 temporaries are `long double`; where the original spills to a float slot and reloads, the C uses a volatile
  float (rdModel_DrawMesh mode 2: dy and dz are rounded to float before their squares, dx is not).
* NaN behaviour of every comparison follows the fnstsw test (`test ah,0x41` / `0x01` / `0x40`), e.g. mode 3 of
  rdModel_DrawMesh counts a NaN distance as inside, the light level clamps treat NaN as 0.
* The light level (ComputeMeshLighting, PreparePolygon) tests the x87 sum against 0 but the float copy against 1, and
  clamps a second time on the float copy only; the level is passed to callbacks as its raw dword.
* Float arguments that the original pushes as raw dwords (Frustum_TestSphere radius, rdLight_CalcVertexIntensities
  ambient) are passed through casts to integer parameters, so an SNaN is not quieted.
* rdCanvas_EmitSpans restores the DAT_00900524 control word after the rounding, as the original does (the harness
  compares the control word).
* rdModel3_LoadBinary re-reads every count and pointer from the record where the original does.

Mutations the tests did not detect (judged equivalent or out of the generated range): rdModel_DrawMesh re-association
of the mode 3 squared sum (only sub-ulp at 64 bit precision); rdCanvas_EmitSpans `(float)s * 65536` vs
`(float)(s * 65536)` (exact, a power of two) and the -0x51e boundary; rdModel_ComputeMeshLighting `sf` as long double
(converted at the call anyway).

## In-game check

Build: `python -I tools/build_src.py`, `make -C build -j8`, `make -C build link`: all pass.  `build/perf/libcheck.py`
with a private hard-linked data folder: boots, Lua probes run, save/load round trip passes, no Lua errors, process alive.

Shots against a build without `overrides_asm_p1.c` (same tree): idle identical; set01 and walk differ in every pair of
runs, also base against base (timing noise).  One systematic difference: 330 pixels (0.108%) at x 466..497 y 90..143 of
the set shots, the top edge of the black-rendered figure in that scene.  Bisected to FUN_00410330.  It is NOT a
difference in what FUN_00410330 computes:

* the C matches the 1.01 bytes in the differential test, and so does the reassembled asm of the build;
* the difference goes away when the same C is called through a one-line wrapper (variant v8), when the asm is called
  through the same wrapper (v5, v6 also with a busy loop, so it is not timing), and when only a 256-byte unused local is
  added to the C (v9).

So the shot depends on what FUN_00410330's stack frame leaves below the stack pointer: some code that runs later reads
uninitialised stack memory.  That fits the black rendering of that figure (the known rendering bug).  The C is kept as
written; the renderer fix should look for the uninitialised read (it is not in the functions of this file: none reads a
local before writing it).  The experiment scripts are `variant.sh` / `variant.py` (link without some overrides),
`variant_wrap.py` (C name, sliced asm body), `variant_wrapc.py` (C wrapper), `variant_probe.py` (in-game comparison of
both versions, its log did not work), `shotbox.py` / `shotpix.py` (where two shots differ).

## Not converted

| address | name | reason |
|---|---|---|
| 128 functions 0x0040ea50 - 0x00436be0 | rdRaster_* | excluded: the rendering fix changes them |
| 0042003c | FUN_0042003c | not a function: the loop tail of rdRaster_Span_Tex_5 (already C in overrides_asm_o1.c), entered by a jump with the caller's registers |
| 0040aa20 | rdModel3_LoadText | not done in this pass: text .3do parser with a 0x20480-byte stack frame (128 material names of 0x400 bytes, __chkstk), sscanf into stack and register-held values, the prototype in functions.h (8 arguments) does not match the real one; needs the full instruction trace and a stand-in stdConffile |
| 00406aa0 | rdCache_DrawMeshList3D | not done in this pass: 1569 instructions of the D3D batching path (colour packing through _ftol and frndint with control words, execute-buffer vertex output, several register values carried across calls) |

The seven `FUN_004xxxxx` span drivers are rasteriser functions without an `rdRaster_` name; they were converted because
the exclusion is by name.  The renderer fix may want to look at them together with the rdRaster_* functions.

## Open questions

* The uninitialised stack read behind the FUN_00410330 shot difference (above). **Gone after the merge onto a09980a**
  (rdPrimit3_ClipFace reads the clipped vertex count from EAX): 2026-11-09, libcheck twice each with FUN_00410330 as C and
  as the original machine code (`variant.sh`, the asm kept for that one function): idle, walk and set00-set04 identical
  between the two builds; the only differences are between two runs of the same build (timing noise in idle / walk /
  set04). This branch was made before a09980a, whose old C read an empty ST(0) and left the x87 stack one entry off.
  The figure in set01 (ha.set) still renders as a black silhouette in both builds; whether the original does the same
  has not been checked.
* rdModel3_LoadBinary: a face with a uv list (+0x1c != 0) but no vertex list (+0x14 == 0) allocates and reads 0 bytes
  for the uv list; the original does the same.
