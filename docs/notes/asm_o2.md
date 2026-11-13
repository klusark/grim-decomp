# Slice 5, second pass (agent asm_o2): assembly to C with differential tests

Scope: the 88 GRIMFANDANGO.EXE addresses of slice 5 and the five CHORE.DLL costume loaders that agent asm_s5 left
assembled (docs/notes/asm_s5.md).

Result: **43 EXE functions and all 5 CHORE.DLL functions converted to C; every one of them verified bit for bit
against the original machine code by a differential test** (none is "unverified").  45 EXE functions stay assembled
(table below).

Files:

* `build/overrides_asm_o2.c` (GRIM_EXE), `build/overrides_asm_o2_chore.c` (GRIM_CHORE): both compile with the
  Makefile's GHIDRA_CFLAGS (`-O0 -m32 -march=i686 ... -include compat.h -I. -Isrc/<PROG>`) against the generated headers
  in `src/<PROG>/`.  Nothing was regenerated (build_src.py / gen_asm.py / make were not run), so the functions are
  still also in `src/<PROG>/asm_funcs.s`; they leave it at the next regeneration (the names are found by
  `load_overrides`, checked with its regex: 48 + 5 names, including some static helpers, which is harmless).
* `build/difftest/asm_s5/`: `build.sh` (copy of build/mixdiff/build.sh with its own output directory, the build's
  real compiler flags and a stub generator that keeps fastcall names), `run_all.sh` (builds and runs all tests),
  the tests `small_test.c`, `dx_test.c`, `cos_test.c`, `lua_test.c`, `display_test.c`, `sector_test.c`,
  `span_test.c`, `chore_test.c`, helpers `show.py` (decompiled text + assembly of a function) and `addchunk.py`.
* The tests slice the original functions out of the CURRENT `src/<PROG>/asm_funcs.s` (they are still assembled
  there).  After the next regeneration they are gone from it: run with `BASE_ASM=<copy of today's asm_funcs.s>`
  (`git show HEAD:src/GRIMFANDANGO.EXE/asm_funcs.s > /tmp/base.s`).

## Method

As in docs/notes/mixer.md: the original instructions (renamed `orig_<name>`) and the C are linked into one test
program with the original data image (`build/obj/<PROG>/data_s.o`) and run from the same start state; return values,
registered memory regions (globals, buffers, the whole CHORE .data) and the log of every call into recorder thunks
(COM methods with their stdcall argument counts, Win32 / LUA.DLL / CHORE.DLL imports through their `__imp__` slots,
service tables, game callees) are compared.  Where a callee is plain C of the current build it is linked in
(stdGif_LzwWriteCode, Rle_NextByte, the CHORE line reader and sscanf).  Each test was checked for sensitivity with
deliberately wrong versions (changed constants, comparisons, offsets, the NaN test, the light clamp, the z test ...);
every non-equivalent mutation was reported.  Floating point tests run under the x87 precision controls 24, 53 and
64 bits.

Prototype fixes without touching Ghidra: where Ghidra's prototype in functions.h is wrong the name is renamed while
functions.h is included (`#define name name__ghidra`) and the definition carries the real prototype and an
`/* OVERRIDES: name */` line: FUN_004d5f70 (varargs, declared `(void)`; since 2026-11-13 Ghidra stores
`(char *fmt, ...)` and msc_error_SaveString compiles from the generated text again), FUN_004d5fd0 (cdecl memset declared
`__fastcall` with 5 arguments; defined with `__asm__("@FUN_004d5fd0@20")` so the decorated name stays), FUN_004d5e50
(returns the count), FUN_004965b0 (5 arguments), D3D_CreateViewport (width, height lost), DDraw_CreateSurfaces
(palette lost).

Build patches of `names/asm_patches.json` are kept in the C: Input_PollKeyboard (count 0 when GetDeviceData fails),
FUN_004761b0 (first SetCooperativeLevel with 8 instead of 0x11), Lua_InitGameLibs (GRIM_RegisterModApiLib /
GRIM_RegisterModApi calls).

## Converted

| prog | address | name | verification (cases, 0 differences each) |
|---|---|---|---|
| EXE | 004d5fd0 | FUN_004d5fd0 (memset, hand asm) | small_test, 1500 random fills incl. 20000-byte block boundaries |
| EXE | 004d5e50 | FUN_004d5e50 (memset wrapper, returns count) | small_test, 1500 |
| EXE | 004d5f70 | FUN_004d5f70 (log ring vsprintf) | small_test, 3000 (counters incl. out-of-range values) |
| EXE | 004d5e70 | Rle_Decode | small_test, 3000 (random streams, RLE state compared) |
| EXE | 004965b0 | FUN_004965b0 (component callback) | small_test, 3000 |
| EXE | 0047e7f0 | stdGif_LzwInitEncoder | small_test, 301 whole encode runs (init + up to 30000 pixels + finish, fwrite failures) |
| EXE | 0047ea30 | stdGif_LzwEncodePixel | same runs (millions of pixels, table clears) |
| EXE | 00477730 | Input_PollKeyboard | dx_test, 10000 (fake DirectInput device, overflow / failure returns) |
| EXE | 00477c20 | Input_PollMouse | dx_test, 10000 |
| EXE | 00477dc0 | Input_FlushJoystick | dx_test, 10000 |
| EXE | 00478b40 | D3D_ExecuteBuffer | dx_test, 10000 (D3DEXECUTEDATA captured) |
| EXE | 0047a130 | D3D_CreateViewport | dx_test, 10000 (D3DVIEWPORT captured, widths up to 2^32) |
| EXE | 00496950 | ModelComponent_NewInstance | cos_test, 100000 (sharing, assert, parent / root, release) |
| EXE | 004985c0 | FUN_004985c0 (sprite component instance) | cos_test, 100000 |
| EXE | 0049de00 | Lua_InitGameLibs | lua_test, 5000 |
| EXE | 004761b0 | FUN_004761b0 (DirectDrawEnumerate callback) | display_test, 10000 |
| EXE | 00474e40 | Display_DrawText | display_test, 10000 |
| EXE | 00479db0 | D3D_InitRenderState | display_test, 10000 (render state list compared) |
| EXE | 004767d0 | DDraw_CreateSurfaces | display_test, 10000 (paletted / RGB, back buffer, every failing call) |
| EXE | 004a6980 | Sector_ContainsPoint | sector_test, 3000000 (203175 inside; NaN, inf, 1e-5 neighbours; PC 24/53/64) |
| EXE | 0045ff10 | rdRaster_Span16_TexLitZw | span_test, 20000 per function (460000 in all) |
| EXE | 004602c0 .. 004618e0 | rdRaster_Span16_TexLitZw_2 .. _8 | span_test, 20000 each |
| EXE | 00466920 .. 00467e30 | rdRaster_Span16_TexLitZw_15 .. _22 | span_test, 20000 each |
| EXE | 0046c330 .. 0046d540 | rdRaster_Span16_TexLitZw_24 .. _30 | span_test, 20000 each |
| CHORE | 10001770 | Cos_LoadEntry | chore_test, 100000 random text costumes (valid, truncated, damaged lines, bad types, comments, duplicate tracks, allocation failures) |
| CHORE | 100041e0 | FUN_100041e0 (tags section) | chore_test (called by Cos_LoadEntry), 100000 |
| CHORE | 10004390 | FUN_10004390 (components section) | chore_test, 100000 |
| CHORE | 100047f0 | FUN_100047f0 (chores section) | chore_test, 100000 |
| CHORE | 10004970 | FUN_10004970 (keys section) | chore_test, 100000 |

Notes on what the C keeps:

* Sector_ContainsPoint: extended precision throughout, and the original's "FCOM + TEST AH,0x41" treats NaN as below
  the 1e-5 tolerance (snapped to 0): written as `!(a > 1e-5)`.  The C version that logic.md reports as bad used plain
  float comparisons; this one is bit-identical in 3 million cases.
* Spans: the two templates `span16_tex_zw` / `span16_texlit_zw` cover 23 functions (they differ only in the texture
  width; _25 .. _30 are byte-identical copies of _17 .. _22).  The z start and step are rounded with FISTP under the
  control word at 0x00900526: a three-instruction inline asm helper `span_fist` (fldcw / fistp / fldcw), the only
  inline asm in the files.
* The CHORE loaders reuse parameter slots as locals in the original (the tag count, the component array, loop
  counters): Ghidra showed them as `unaff_retaddr` / `param_3`.  Cos_LoadEntry closes the HANDLE as a file when the
  costume name is longer than 32 characters (the file variable is the second parameter's slot) - kept.
* D3D_CreateViewport also stores (float)width into its own first argument slot; not visible to C callers, not kept.
* Crashes of the original are not reproduced in a test (negative span right edge, failed key / track / depth
  allocation in the CHORE loaders, a damaged costume line that still parses): both versions write through NULL or out
  of range there.

Finding outside the slice (not changed): `Display_OpenMode` (src/GRIMFANDANGO.EXE/stddisplay.c, compiled at -O2) calls
`((code *)Win_GetMainHwnd)(g_pVideoMode, palette)` and then `((code *)DDraw_CreateSurfaces)(hwnd)`: the original passes
(hwnd, video mode, palette), the compiled code passes (hwnd, palette, whatever is in the next stack slot) - the
lost-arguments pattern of BUILD_NOTES.  It hurts the assembled DDraw_CreateSurfaces exactly as the C one; the
DirectDraw display type (device +0x100 == 1) path is affected.

## Left assembled

| address | name | obstacle |
|---|---|---|
| 004ac6f0 | _ftol | takes its argument in ST(0) (no C calling convention passes a value in an x87 register); CRT helper, must stay asm |
| 004addf0 | FUN_004addf0 (_chkstk / _alloca_probe) | size in EAX, probes the pages and moves the CALLER's ESP, returns by `push [old ESP]; ret`: not a C function |
| 004d5e1c | FUN_004d5e1c | SEH filter funclet: reads the exception record through the parent's frame (`mov EDX,[EBP-0x14]`, EBP is the parent's) |
| 004d5e30 | FUN_004d5e30 | SEH handler fragment, 2 instructions (`mov ESP,[EBP-0x18]; xor EAX,EAX`) that resume in the parent function |
| 004d6030, 004d6050, 004d6070 | FUN_004d6030 / 6050 / 6070 | unwind funclets: Plat_Free of a slot of the parent's EBP frame ([EBP-0x10], [EBP+8], [EBP+4]) |
| 004d6090, 004d609e, 004d60ac | FUN_004d6090 / 609e / 60ac | unwind funclets: Plat_Free([EBP-0x1fc]) of the parent frame |
| 004d60d0, 004d60db, 004d6100 | FUN_004d60d0 / 60db / 6100 | unwind funclets: tail jump to StateImage_Release with ECX = [EBP-0x10] + 0xc / + 0x80 of the parent frame |
| 00461c90, 00462780 .. 00465340 | rdRaster_Span16_TexZw, rdRaster_Span16_TexLitZw_9 .. _14 (7) | not converted in this pass: perspective-correct spans (705 lines each: an FDIV per 16 / 8 pixel segment, control words 0x00900526 / 0x00900528, two pixel loops); no instruction-level obstacle found, the template method of the converted spans applies |
| 00468130 .. 004710e0 | rdRaster_Span16_TexZw_2 .. _13, rdRaster_Span16_TexLitZw_23, _31 (14) | same as above (617 / 631 lines, perspective subdivision) |
| 0045ba90 .. 0045f550 | rdRaster_SpanP16_TexLit_3 .. _9 (7) | same as above (555 / 585 lines, 4 FDIVs, lit) |
| 0047d2d0 | stdPic_LoadInto | not attempted in this pass (616 lines); no obstacle identified |
| 00484260 | Engine_RenderFrame | not attempted in this pass (524 lines; logic.md: an earlier C version crashed at +0x240) |
| 004917e0 | Walker_AvoidActorPath | not attempted in this pass (831 lines) |
| 004939f0 | Collision_TestActorAgainstOthers | not attempted in this pass (486 lines; logic.md: NaN compares, earlier C crashed) - the Sector_ContainsPoint approach (long double, `!(a > b)` for TEST AH,0x41) should apply |

Count: 43 converted (20 + 23 spans) + 13 frame / CRT fragments + 28 perspective spans + 4 large functions = 88 EXE
addresses (rdRaster_Span16_TexLitZw_23 and _31 belong to the perspective family); CHORE.DLL 5 of 5 converted.
