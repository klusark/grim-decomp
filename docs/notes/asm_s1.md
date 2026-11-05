# Software rasteriser, slice 1 (agent asm_s1): C versions

Source: `build/overrides_asm_s1.c` (new; the only code file of this slice). The 88 addresses of exe_slice1.txt are all in GRIMFANDANGO.EXE and belong to the rdRaster / rdCanvas / rdModel / rdCache / rdPrimit3 / rdModel3 family.

Result: 29 converted, 59 left assembled. Only the syntax of the file was checked (`gcc -fsyntax-only -Wall` with the GRIM_EXE flags of build/Makefile and `-I../src/GRIMFANDANGO.EXE`): no errors, no warnings. Nothing was built, linked or run, and no differential test was done. Each conversion was checked by reading the original assembly (src/GRIMFANDANGO.EXE/asm_funcs.s) line by line against the C; the Ghidra decompilation was used for names and structure only.

Remaster types: none were used. Struct offsets are the 1.01 ones. Global names are those of src/GRIMFANDANGO.EXE/globals.h (`_DAT_` is the dword view of a `DAT_` global, as in globals.h).

## Converted (29)

| address | name | how it was checked |
|---|---|---|
| 0x0040f5f0 | rdRaster_Select_Flat | read asm and decompile; the `1.0f / w` loop matches fdivr + fstp (one extended division, one rounding); function pointers stored as dword bits |
| 0x0040f650 | rdRaster_SpanFlatSetup | read asm; 8 bpp and 16 bpp branches and the palette index (byte at +0x1d0) match |
| 0x0040f6d0 | rdRaster_SpanOutline8 | read asm; pixel address = base + y*pitch + x, last pixel at len-1 |
| 0x0040f710 | rdRaster_SpanOutline16 | read asm; pitch halved as unsigned (shr), word stores |
| 0x0040f750 | rdRaster_EdgeStepFlat | read asm; fadd + fstp is one float rounding, as in the C |
| 0x0040fa20 | rdRaster_Select_Flat_2 | as rdRaster_Select_Flat; constant 1.0 taken from Ghidra's decompile, not read from the data bytes |
| 0x0040fa80 | rdRaster_SpanTexSetup | read asm; 8 bpp fill is a byte loop (rep stosd / rep stosb write the same bytes); 16 bpp word fill; FlatZw / FlatZw_2 chosen by camera flag +0x14 |
| 0x0040ff20 | rdRaster_SpanLitSetup | read asm; fill is bytes at any bpp (the original has no 16 bpp fill here) |
| 0x00410290 | rdRaster_Select_FlatLit | read asm; 8 / 16 bpp stores at +0x1dc / +0x1e0 are dword copies (int, not float) |
| 0x004108b0 | rdRaster_Select_FlatLit_2 | read asm; shift counts masked with 0x1f as x86 does; 16 bpp table at +0x7e00 |
| 0x00411270 | rdRaster_Select_FlatLit_3 | read asm; same as _2 with FUN_00411330 and edge setup _5 |
| 0x004124f0 | rdRaster_Select_FlatLit_6 | read asm twice; 16 bpp table WITHOUT +0x7e00 (unlike _2 and _3); 8 bpp at +0x330 |
| 0x00413040 | rdRaster_Select_FlatLit_7 | read asm; as _6 with FUN_00413110 and edge setup _7 |
| 0x004195f0 | rdRaster_Span16_Flat | read asm; ceil of the 16.16 ends; cursor PTR_007f43a8 is set only when the span is not empty |
| 0x00419e60 | rdRaster_Span_Flat | read asm; rep stosd + rep stosb is a byte fill of width bytes |
| 0x00419ee0 | rdRaster_Span16_Flat_2 | read asm; same instruction sequence as rdRaster_Span16_Flat |
| 0x004104b0 | FUN_004104b0 | read asm; int and float updates on disjoint fields |
| 0x00411b70 | FUN_00411b70 | read asm; same family as the other edge steps |
| 0x00415180 | FUN_00415180 | read asm; the x87 stack holds three sums, each rounded once at its store: same as three C statements |
| 0x004151c0 | FUN_004151c0 | read asm (one add) |
| 0x004169f0 | FUN_004169f0 | read asm |
| 0x00416a30 | FUN_00416a30 | read asm |
| 0x004129f0 | FUN_004129f0 | read asm |
| 0x00411330 | FUN_00411330 | read asm; +0x1e0 copied only for 16 bpp; span routine chosen by bpp |
| 0x004121a0 | FUN_004121a0 | read asm; the 8 bpp path copies only +0x1dc (the +0x19c copy is in the 16 bpp block only, as in the original) |
| 0x00413110 | FUN_00413110 | read asm; as FUN_004121a0 with the _3 span routines |
| 0x00415600 | FUN_00415600 | read asm; the 16 bpp path copies the fields listed in the C comment |
| 0x00416f80 | FUN_00416f80 | read asm; as FUN_00415600 with the _3 span routines |
| 0x00413dd0 | FUN_00413dd0 | read asm; ALL copies are in the 16 bpp branch (the 8 bpp path copies nothing); calls P8 / P16_TexKeyZw |

The static helper `select_flatlit_nooffset` in the file (not a slice function) is the shared body of Select_FlatLit_6 and _7.

## Left assembled (59)

| address | name | reason |
|---|---|---|
| 0x00404e00 | rdCanvas_EmitSpans | x87 rounding through control words (fldcw/fistp); the control-word values were not verified |
| 0x00405770 | rdCanvas_PreparePolygon | large (1152 insts); not read in detail |
| 0x00406aa0 | rdCache_DrawMeshList3D | x87 rounding through control words (fldcw/frndint); the control-word values were not verified |
| 0x00409580 | rdModel_ComputeMeshLighting | fcomp / fnstsw compares; not read in detail |
| 0x0040aa20 | rdModel3_LoadText | large text parser (rdModel3_LoadText); not read in detail |
| 0x0040b8e0 | rdModel3_LoadBinary | large binary loader (rdModel3_LoadBinary); not read in detail |
| 0x0040d230 | rdModel_DrawMesh | fsqrt and fcompp; not read in detail |
| 0x0040e500 | rdPrimit3_CopyFaceVerts | fcom / fnstsw compares; not read in detail |
| 0x0040ea50 | rdRaster_SetupPoly | fcom / fnstsw, fild and division; called by most selectors; not read in detail |
| 0x0040ef90 | rdRaster_SetupPolyTex | fcom / fnstsw, fild and division; not read in detail |
| 0x0040f770 | rdRaster_EdgeSetup_Flat | x87 rounding through control words (fldcw/frndint/fistp); the control-word values were not verified |
| 0x0040fbe0 | rdRaster_EdgeSetup_Flat_2 | x87 rounding through control words (fldcw/frndint/fistp); the control-word values were not verified |
| 0x0040fe90 | rdRaster_Select_TexLit | x87 rounding through control words (fldcw + fistp) |
| 0x0040ffe0 | rdRaster_EdgeSetup_Flat_3 | x87 rounding through control words (fldcw/frndint/fistp); the control-word values were not verified |
| 0x00410330 | FUN_00410330 | lit span loop: palette-table indexing, branches per bpp, span calls; read in part only, not converted |
| 0x004104e0 | rdRaster_EdgeSetup_Flat_4 | x87 rounding through control words (fldcw/frndint/fistp); the control-word values were not verified |
| 0x00410970 | FUN_00410970 | lit span helper (109 insts), not read in detail |
| 0x00410d80 | rdRaster_EdgeSetup_Flat_5 | x87 rounding through control words (fldcw/frndint/fistp); the control-word values were not verified |
| 0x004113e0 | rdRaster_SpanR8_TexKey | x87 rounding through control words (fldcw/fistp); the control-word values were not verified |
| 0x004114f0 | rdRaster_SpanR16_TexKey | x87 rounding through control words (fldcw/fistp); the control-word values were not verified |
| 0x00411630 | rdRaster_Select_FlatLit_4 | x87 rounding through control words (fldcw/fistp); the control-word values were not verified |
| 0x00411740 | FUN_00411740 | not read in this slice (budget); not converted |
| 0x00411ba0 | rdRaster_EdgeSetup_Flat_6 | x87 rounding through control words (fldcw/frndint/fistp); the control-word values were not verified |
| 0x00412090 | rdRaster_Select_FlatLit_5 | x87 rounding through control words (fldcw/fistp); the control-word values were not verified |
| 0x00412280 | rdRaster_SpanR8_TexKey_2 | x87 rounding through control words (fldcw/fistp); the control-word values were not verified |
| 0x004123b0 | rdRaster_SpanR16_TexKey_2 | x87 rounding through control words (fldcw/fistp); the control-word values were not verified |
| 0x004125c0 | FUN_004125c0 | not read in this slice (budget); not converted |
| 0x00412a30 | rdRaster_EdgeSetup_Flat_7 | x87 rounding through control words (fldcw/frndint/fistp); the control-word values were not verified |
| 0x004131f0 | rdRaster_SpanR8_TexKey_3 | x87 rounding through control words (fldcw/fistp); the control-word values were not verified |
| 0x00413340 | rdRaster_SpanR16_TexKey_3 | x87 rounding through control words (fldcw/fistp); the control-word values were not verified |
| 0x004134a0 | rdRaster_Select_FlatLit_8 | float scale constant at rdata+0x78c, not visible in Ghidra's text; not verified (same for _9, _12, _13 with their own constants) |
| 0x00413590 | FUN_00413590 | not read in this slice (budget); not converted |
| 0x004139f0 | rdRaster_EdgeSetup_Flat_8 | x87 rounding through control words (fldcw/frndint/fistp); the control-word values were not verified |
| 0x00413ce0 | rdRaster_Select_FlatLit_9 | float scale constant at rdata+0x794, not verified |
| 0x00413ee0 | rdRaster_SpanP8_TexKeyZw | x87 rounding through control words (fldcw/fistp); the control-word values were not verified |
| 0x00414530 | rdRaster_SpanP16_TexKeyZw | x87 rounding through control words (fldcw/fistp); the control-word values were not verified |
| 0x00414be0 | rdRaster_Select_FlatLit_10 | x87 rounding through control words (fldcw/fistp); the control-word values were not verified |
| 0x00414d20 | FUN_00414d20 | not read in this slice (budget); not converted |
| 0x004151d0 | rdRaster_EdgeSetup_Flat_9 | x87 rounding through control words (fldcw/frndint/fistp); the control-word values were not verified |
| 0x004154c0 | rdRaster_Select_FlatLit_11 | x87 rounding through control words (fldcw/fistp); the control-word values were not verified |
| 0x00415720 | rdRaster_SpanP8_TexKeyZw_2 | x87 rounding through control words (fldcw/fistp); the control-word values were not verified |
| 0x00415dc0 | rdRaster_SpanP16_TexKeyZw_2 | x87 rounding through control words (fldcw/fistp); the control-word values were not verified |
| 0x00416470 | rdRaster_Select_FlatLit_12 | float scale constant at rdata+0x7d4, not verified |
| 0x00416580 | FUN_00416580 | not read in this slice (budget); not converted |
| 0x00416a50 | rdRaster_EdgeSetup_Flat_10 | x87 rounding through control words (fldcw/frndint/fistp); the control-word values were not verified |
| 0x00416e70 | rdRaster_Select_FlatLit_13 | float scale constant at rdata+0x7e0, not verified |
| 0x004170a0 | rdRaster_SpanP8_TexKeyZw_3 | x87 rounding through control words (fldcw/fistp); the control-word values were not verified |
| 0x00417790 | rdRaster_SpanP16_TexKeyZw_3 | x87 rounding through control words (fldcw/fistp); the control-word values were not verified |
| 0x00418550 | rdRaster_Grad_Flat | fcom / fnstsw compares and division (NaN ordering); not read in detail |
| 0x00418a00 | rdRaster_Grad_Flat_2 | fcom / fnstsw compares and division; not read in detail |
| 0x00418fe0 | rdRaster_DrawPoints | x87 rounding through control words (fldcw/fistp); the control-word values were not verified |
| 0x00419150 | rdRaster_DrawWireframe | x87 rounding through control words (fldcw/fistp); the control-word values were not verified |
| 0x00419450 | rdRaster_Draw16_FlatLit | calls span routines; not read in detail |
| 0x00419680 | rdRaster_Edge_Flat | x87 rounding through control words (fldcw/frndint/fistp); the control-word values were not verified |
| 0x00419840 | rdRaster_Edge_Flat_2 | x87 rounding through control words (fldcw/frndint/fistp); the control-word values were not verified |
| 0x00419a00 | rdRaster_Draw16_TexLit | calls span routines; not read in detail |
| 0x00419be0 | rdRaster_Span16_Tex | texture span loop: reads globals (texture pointer DAT_317300 and tables) per pixel and does not advance the texture pointer; not verified |
| 0x00419ca0 | rdRaster_Draw16_FlatLit_2 | x87 rounding through control words (fldcw/fistp); the control-word values were not verified |
| 0x00419f70 | rdRaster_Edge_Flat_3 | x87 rounding through control words (fldcw/frndint/fistp); the control-word values were not verified |

## Pitfalls handled in the C

* Function pointers are stored as dwords (`(int)fn`), as the asm does (`mov dword ptr [..], offset ...`). Ghidra prints `(float)fn`; in the original that is a bit copy, not a float conversion.
* Colours, pointers and table values that Ghidra shows as floats are copied as ints (an x87 `fld` would quieten a signalling NaN).
* Shift counts are masked with 0x1f (x86 `shr EAX,CL` does that in hardware).
* A 16.16 end is rounded up to the next pixel only when its fraction is nonzero (`(v + 0x10000) & 0xffff0000`).
* FUN_004121a0, FUN_00413110 and FUN_00413dd0 copy different field sets per bpp; the C follows the asm.

## Doubts to check

* docs/notes/logic.md gives the control words 0x52a (ceil), 0x526 (floor), 0x528 (truncate). The RC field (bits 10-11) of each of these is 01 (round down), so at least one of those notes is wrong or the values are not the ones meant. This slice does not depend on them: the functions that use them are left assembled.
* Select_FlatLit_6 and _7 (16 bpp table without +0x7e00) differ from _2 and _3 (with +0x7e00). Both were read from the asm twice; a differential test would settle it.
* FUN_00413dd0 copies nothing for 8 bpp; if that path needs the fields of the other dispatchers, check the asm again.
