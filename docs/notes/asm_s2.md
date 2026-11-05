# Software rasteriser, slice 2 (0x0041a130 - 0x0042b1f0): notes

File: `build/overrides_asm_s2.c`.  Types: only 1.01 Ghidra types and the names in `src/GRIMFANDANGO.EXE/globals.h` /
`functions.h` were used.  No remaster (Linux) struct or type definitions were taken, so nothing needs listing as
remaster-derived.  The remaster was not used for behaviour.

Checks: the C was compared with the 1.01 instructions in `src/GRIMFANDANGO.EXE/asm_funcs.s` by reading only.  No
differential test was run.  `gcc -m32 -fsyntax-only` with the Makefile flags passes for the file.

## Converted (2)

| address | name | how it was checked |
|---|---|---|
| 0041a810 | rdRaster_Span8_Flat | read against the asm line by line: ceil of both edge x values, 64-bit reciprocal product >> 16, the -0x51e clamp, shade table lookup `((x >> 8) & 0x3f00) + UINT_008ddeb0 + DAT_008ddec0`; loop runs at least once. Reading only. |
| 0041a900 | rdRaster_Span16_Flat_3 | read against the asm: same set-up as Span8; word table `UINT_008ddebc + ((x >> 16) & 0x3f) * 0x100 + DAT_008ddec0` (in words); writes through the global `PTR_007f43a8`, which is advanced by 2 per pixel and left at the end of the span, as the asm does. Reading only. |

## Left assembled (86)

Reason for all of them: not translated in this pass.  They are the templated texture / lit / keyed span and draw
functions (50-580 assembly lines each), plus the edge stepping functions (143-251 lines).  Each variant needs its own
line-by-line check (texture index shifts, the lit / key branches, the stack layout of the `[EBP+...]` arguments and
the globals they write), and there was not time to do that reliably for 86 near-identical copies.  Assembled is the
safe choice; these are the candidates for a follow-up pass.

| address | name |
|---|---|
| 0041a130 | rdRaster_Edge_Flat_4 |
| 0041a2f0 | rdRaster_Draw16_TexLit_2 |
| 0041a4f0 | rdRaster_Span_Tex |
| 0041a580 | rdRaster_Span16_Tex_2 |
| 0041a640 | rdRaster_Draw_FlatLit |
| 0041aa10 | rdRaster_Edge_Flat_5 |
| 0041ac60 | rdRaster_Edge_Flat_6 |
| 0041aeb0 | rdRaster_Draw16_TexLit_3 |
| 0041b0d0 | rdRaster_Span_Tex_2 |
| 0041b1e0 | rdRaster_Span16_Tex_3 |
| 0041b310 | rdRaster_Draw16_TexLit_4 |
| 0041b6f0 | rdRaster_Span_Flat_2 |
| 0041b880 | rdRaster_Span16_Tex_4 |
| 0041ba30 | rdRaster_Edge_Flat_7 |
| 0041bd20 | rdRaster_Edge_Flat_8 |
| 0041c010 | rdRaster_Draw16_TexLit_5 |
| 0041c260 | rdRaster_Span_Tex_3 |
| 0041c410 | rdRaster_Span16_Tex_5 |
| 0041c5e0 | rdRaster_Draw16_TexLitKey |
| 0041c810 | rdRaster_Span_FlatKey |
| 0041c9b0 | rdRaster_Span16_TexKey |
| 0041cb80 | rdRaster_Draw16_TexLitKey_2 |
| 0041cdd0 | rdRaster_Span_TexKey |
| 0041cf90 | rdRaster_Span16_TexKey_2 |
| 0041d180 | rdRaster_Draw_FlatLit_2 |
| 0041d560 | rdRaster_Span16_Tex_6 |
| 0041d710 | rdRaster_Edge_Flat_9 |
| 0041da00 | rdRaster_Edge_Flat_10 |
| 0041dcf0 | rdRaster_Draw16_TexLit_6 |
| 0041df60 | rdRaster_Span_Tex_4 |
| 0041e120 | rdRaster_Span16_Tex_7 |
| 0041e300 | rdRaster_Draw_TexLitKey |
| 0041e550 | rdRaster_Span8_TexKey |
| 0041e700 | rdRaster_Span16_TexKey_3 |
| 0041e8d0 | rdRaster_Draw_TexLitKey_2 |
| 0041eb40 | rdRaster_Span_TexKey_2 |
| 0041ed10 | rdRaster_Span_TexKey_3 |
| 0041eef0 | rdRaster_Draw_FlatLit_3 |
| 0041f2f0 | rdRaster_Span16_Tex_8 |
| 0041f520 | rdRaster_Edge_Flat_11 |
| 0041f890 | rdRaster_Edge_Flat_12 |
| 0041fc00 | rdRaster_Draw16_TexLit_7 |
| 0041fe90 | rdRaster_Span_Tex_5 |
| 0042003c | FUN_0042003c (no label match in asm_funcs.s, not reviewed) |
| 004200c0 | rdRaster_Span16_Tex_9 |
| 00420310 | rdRaster_Draw_TexLitKey_3 |
| 00420580 | rdRaster_Span8_TexKey_2 |
| 004207b0 | rdRaster_Span16_TexKey_4 |
| 004209f0 | rdRaster_Draw16_TexLitKey_3 |
| 00420c80 | rdRaster_Span_TexKey_4 |
| 00420ec0 | rdRaster_Span16_TexKey_5 |
| 00421120 | rdRaster_Draw_FlatLit_4 |
| 00421510 | rdRaster_Span16_Tex_10 |
| 00421b60 | rdRaster_Edge_Flat_13 |
| 00421dc0 | rdRaster_Edge_Flat_14 |
| 00421f80 | rdRaster_Draw16_TexLit_8 |
| 004221f0 | rdRaster_Span_Tex_6 |
| 00422820 | rdRaster_Span16_Tex_11 |
| 00422f00 | rdRaster_Draw16_TexLitKey_4 |
| 00423150 | rdRaster_Span_FlatKey_2 |
| 00423740 | rdRaster_Span16_TexKey_6 |
| 00423db0 | rdRaster_Draw16_TexLitKey_5 |
| 00424020 | rdRaster_Span_TexKey_5 |
| 00424670 | rdRaster_Span16_TexKey_7 |
| 00424d50 | rdRaster_Draw_FlatLit_5 |
| 00425150 | rdRaster_Span16_Tex_12 |
| 004257a0 | rdRaster_Edge_Flat_15 |
| 00425a00 | rdRaster_Edge_Flat_16 |
| 00425bc0 | rdRaster_Draw16_TexLit_9 |
| 00425e50 | rdRaster_Span_Tex_7 |
| 004264a0 | rdRaster_Span16_Tex_13 |
| 00426bc0 | rdRaster_Draw_TexLitKey_4 |
| 00426e30 | rdRaster_Span8_TexKey_3 |
| 00427470 | rdRaster_Span16_TexKey_8 |
| 00427ae0 | rdRaster_Draw16_TexLitKey_6 |
| 00427d70 | rdRaster_Span_TexKey_6 |
| 004283f0 | rdRaster_Span16_TexKey_9 |
| 00428ae0 | rdRaster_Draw_FlatLit_6 |
| 00428f00 | rdRaster_Span16_Tex_14 |
| 00429870 | rdRaster_Edge_Flat_17 |
| 00429b70 | rdRaster_Edge_Flat_18 |
| 00429dc0 | rdRaster_Draw16_TexLit_10 |
| 0042a070 | rdRaster_Span_Tex_8 |
| 0042a790 | rdRaster_Span16_Tex_15 |
| 0042af60 | rdRaster_Draw_TexLitKey_5 |
| 0042b1f0 | rdRaster_Span8_TexKey_4 |

## Doubtful

* The shade and pixel tables are read through the global values `UINT_008ddeb0`, `UINT_008ddebc` and the byte
  `DAT_008ddec0`.  These are Ghidra's names; if their meaning changes, the two converted functions change with them.
* `PTR_007f43a8` is written by Span16_Flat_3 and left at the end of the span (kept as in the original).
