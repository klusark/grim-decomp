# Software rasteriser, follow-up of slice 2 (0x0041a130 - 0x0042b1f0): notes

File: `build/overrides_asm_o1.c` (67 functions).  Names are the ones of the work list (Ghidra's); types only from the
1.01 headers (`src/GRIMFANDANGO.EXE/globals.h`, `functions.h`).  The remaster was not used.  The C was written from the
1.01 machine code (`src/GRIMFANDANGO.EXE/asm_funcs.s`); the decompiler text was only a guide (it loses several
things here, see below).

## How it was verified

Differential tests in `build/difftest/asm_s2/` (`run_all.sh` builds and runs everything):

* `rt.c`, `img.ld`, `grim_img.s`: the test program is linked at image base 0x400000 with a reserved section over
  0x401000 - 0x94e000, into which the ORIGINAL 1.01 bytes are loaded (`raw/GRIMFANDANGO.EXE/sections/text.bin`,
  `rdata.bin`, `data.bin`).  The original function runs at its own address, unmodified (so the original, not the
  reassembled `asm_funcs.s`, is the reference; this matters for `rdRaster_Span_Tex_5`, below).
* `gensyms.py`: every global and function the C names is defined as an absolute symbol at its 1.01 address, so the C
  works on the same memory.  Functions the C calls that are not in this file (`rdRaster_Edge_Flat_3`,
  `rdRaster_Grad_Flat`, `_2`, the perspective spans, `Mem_DumpLog`) are the original code on both sides.
* `harness.h`: per case, random state (rasteriser globals, tables, frame buffer, texture, edge records, polygons,
  x87 control words 0x027f / 0x007f / 0x037f with the derived round-up / round-down / truncate words that
  `Services_SetCurrent` stores at 0x900524..0x90052a) is set; the original runs; its result (all of .data, a 4 MB
  arena with the frame buffer and tables, EAX, the x87 control word) is saved; the state is restored and the C runs;
  everything is compared.  Faults are caught (vectored handler); a case where the original faults is skipped.
* Each test was checked for sensitivity: `NEG=1` runs every original against the C of the next function in the list;
  every pair reports differences except pairs that are really identical (`Span16_Tex_4` / `_6`, `Span16_TexKey` /
  `_3`, `Edge_Flat_4` / `_14` / `_16`, `Edge_Flat_13` / `_15`, `Edge_Flat_6` / `_18`: the integer row and the
  rounded-up y are the same number).
* The C under test was compiled three ways: Makefile `GHIDRA_CFLAGS` at -O0, the exact `link.py` flags (no -fwrapv
  etc.), and -O2.  All three: 0 differences.

Tests: `test_span.c` (the span functions, 8 and 16 bit set-ups), `test_edge.c` (edge stepping on random polygons
with integral, half-integral and equal y values), `test_draw.c` (whole polygons: random convex polygons, 8 and 16 bit
targets; the span pointer `UINT_007f42f8` is mapped from C to 1.01 addresses before the comparison).  The two
functions of `build/overrides_asm_s2.c` (`rdRaster_Span8_Flat`, `rdRaster_Span16_Flat_3`) are in the span test too and
pass (they had only been read before).

## Converted (67)

Cases: per function, at -O0 with the Makefile flags plus a quarter of that each with the link.py flags and at -O2.
Span: 2000 + 500 + 500; edge: 4000 + 1000 + 1000; draw: 400 + 100 + 100 for each of 8 and 16 bit.  No original faulted in
the edge and draw tests, nor in the span test except as noted.  Log of the final run: all 12 test runs `TOTAL differences 0`.

| address | name | verified |
|---|---|---|
| 0041a4f0 | rdRaster_Span_Tex | diff test, 3000 cases |
| 0041a580 | rdRaster_Span16_Tex_2 | diff test, 3000 |
| 0041b0d0 | rdRaster_Span_Tex_2 | diff test, 3000 |
| 0041b1e0 | rdRaster_Span16_Tex_3 | diff test, 3000 |
| 0041b6f0 | rdRaster_Span_Flat_2 | diff test, 3000 |
| 0041b880 | rdRaster_Span16_Tex_4 | diff test, 3000 |
| 0041c260 | rdRaster_Span_Tex_3 | diff test, 3000 |
| 0041c410 | rdRaster_Span16_Tex_5 | diff test, 3000 |
| 0041c810 | rdRaster_Span_FlatKey | diff test, 3000 |
| 0041c9b0 | rdRaster_Span16_TexKey | diff test, 3000 |
| 0041cdd0 | rdRaster_Span_TexKey | diff test, 1594 (the other random states make the original fault: v is shifted left by up to 15, skipped) |
| 0041cf90 | rdRaster_Span16_TexKey_2 | diff test, 1602 (same reason) |
| 0041d560 | rdRaster_Span16_Tex_6 | diff test, 3000 (identical to Span16_Tex_4) |
| 0041df60 | rdRaster_Span_Tex_4 | diff test, 3000 |
| 0041e120 | rdRaster_Span16_Tex_7 | diff test, 3000 |
| 0041e550 | rdRaster_Span8_TexKey | diff test, 3000 |
| 0041e700 | rdRaster_Span16_TexKey_3 | diff test, 3000 (identical to Span16_TexKey) |
| 0041eb40 | rdRaster_Span_TexKey_2 | diff test, 3000 |
| 0041ed10 | rdRaster_Span_TexKey_3 | diff test, 3000 |
| 0041f2f0 | rdRaster_Span16_Tex_8 | diff test, 3000 |
| 0041fe90 | rdRaster_Span_Tex_5 | diff test, 3000 (against the original bytes; see below) |
| 004200c0 | rdRaster_Span16_Tex_9 | diff test, 3000 |
| 00420580 | rdRaster_Span8_TexKey_2 | diff test, 3000 |
| 004207b0 | rdRaster_Span16_TexKey_4 | diff test, 3000 |
| 00420c80 | rdRaster_Span_TexKey_4 | diff test, 3000 |
| 00420ec0 | rdRaster_Span16_TexKey_5 | diff test, 3000 |
| 0041a130 | rdRaster_Edge_Flat_4 | diff test, 6000 |
| 0041aa10 | rdRaster_Edge_Flat_5 | diff test, 6000 |
| 0041ac60 | rdRaster_Edge_Flat_6 | diff test, 6000 |
| 0041ba30 | rdRaster_Edge_Flat_7 | diff test, 6000 |
| 0041bd20 | rdRaster_Edge_Flat_8 | diff test, 6000 |
| 0041d710 | rdRaster_Edge_Flat_9 | diff test, 6000 |
| 0041da00 | rdRaster_Edge_Flat_10 | diff test, 6000 |
| 0041f520 | rdRaster_Edge_Flat_11 | diff test, 6000 |
| 0041f890 | rdRaster_Edge_Flat_12 | diff test, 6000 |
| 00421b60 | rdRaster_Edge_Flat_13 | diff test, 6000 |
| 00421dc0 | rdRaster_Edge_Flat_14 | diff test, 6000 |
| 004257a0 | rdRaster_Edge_Flat_15 | diff test, 6000 |
| 00425a00 | rdRaster_Edge_Flat_16 | diff test, 6000 |
| 00429870 | rdRaster_Edge_Flat_17 | diff test, 6000 |
| 00429b70 | rdRaster_Edge_Flat_18 | diff test, 6000 |
| 0041a640 | rdRaster_Draw_FlatLit | diff test, 1200 polygons |
| 0041a2f0 | rdRaster_Draw16_TexLit_2 | diff test, 1200 |
| 0041aeb0 | rdRaster_Draw16_TexLit_3 | diff test, 1200 |
| 0041b310 | rdRaster_Draw16_TexLit_4 | diff test, 1200 |
| 0041c010 | rdRaster_Draw16_TexLit_5 | diff test, 1200 |
| 0041c5e0 | rdRaster_Draw16_TexLitKey | diff test, 1200 |
| 0041cb80 | rdRaster_Draw16_TexLitKey_2 | diff test, 1200 |
| 0041d180 | rdRaster_Draw_FlatLit_2 | diff test, 1200 |
| 0041dcf0 | rdRaster_Draw16_TexLit_6 | diff test, 1200 |
| 0041e300 | rdRaster_Draw_TexLitKey | diff test, 1200 |
| 0041e8d0 | rdRaster_Draw_TexLitKey_2 | diff test, 1200 |
| 0041eef0 | rdRaster_Draw_FlatLit_3 | diff test, 1200 |
| 0041fc00 | rdRaster_Draw16_TexLit_7 | diff test, 1200 |
| 00420310 | rdRaster_Draw_TexLitKey_3 | diff test, 1200 |
| 004209f0 | rdRaster_Draw16_TexLitKey_3 | diff test, 1200 |
| 00421120 | rdRaster_Draw_FlatLit_4 | diff test, 1200 |
| 00421f80 | rdRaster_Draw16_TexLit_8 | diff test, 1200 |
| 00422f00 | rdRaster_Draw16_TexLitKey_4 | diff test, 1200 |
| 00423db0 | rdRaster_Draw16_TexLitKey_5 | diff test, 1200 |
| 00424d50 | rdRaster_Draw_FlatLit_5 | diff test, 1200 |
| 00425bc0 | rdRaster_Draw16_TexLit_9 | diff test, 1200 |
| 00426bc0 | rdRaster_Draw_TexLitKey_4 | diff test, 1200 |
| 00427ae0 | rdRaster_Draw16_TexLitKey_6 | diff test, 1200 |
| 00428ae0 | rdRaster_Draw_FlatLit_6 | diff test, 1200 |
| 00429dc0 | rdRaster_Draw16_TexLit_10 | diff test, 1200 |
| 0042af60 | rdRaster_Draw_TexLitKey_5 | diff test, 1200 |

## Left assembled (19)

| address | name | reason |
|---|---|---|
| 0042003c | FUN_0042003c | not a function: the inner loop of rdRaster_Span_Tex_5 that Ghidra split off (it runs on the registers and stack frame of Span_Tex_5).  Nothing calls it; with Span_Tex_5 in C it is dead code. |
| 004221f0 | rdRaster_Span_Tex_6 | perspective-correct span (below) |
| 00421510 | rdRaster_Span16_Tex_10 | perspective span |
| 00422820 | rdRaster_Span16_Tex_11 | perspective span |
| 00423150 | rdRaster_Span_FlatKey_2 | perspective span |
| 00423740 | rdRaster_Span16_TexKey_6 | perspective span |
| 00424020 | rdRaster_Span_TexKey_5 | perspective span |
| 00424670 | rdRaster_Span16_TexKey_7 | perspective span |
| 00425150 | rdRaster_Span16_Tex_12 | perspective span |
| 00425e50 | rdRaster_Span_Tex_7 | perspective span |
| 004264a0 | rdRaster_Span16_Tex_13 | perspective span |
| 00426e30 | rdRaster_Span8_TexKey_3 | perspective span |
| 00427470 | rdRaster_Span16_TexKey_8 | perspective span |
| 00427d70 | rdRaster_Span_TexKey_6 | perspective span |
| 004283f0 | rdRaster_Span16_TexKey_9 | perspective span |
| 00428f00 | rdRaster_Span16_Tex_14 | perspective span |
| 0042a070 | rdRaster_Span_Tex_8 | perspective span |
| 0042a790 | rdRaster_Span16_Tex_15 | perspective span |
| 0042b1f0 | rdRaster_Span8_TexKey_4 | perspective span |

The perspective spans (450-580 instructions, about 190 x87 instructions each) divide the span into runs of 16 pixels
and compute u, v from the three plane values with a division per run, with a 1/n float table at 0x008fe000 for the
partial runs.  They switch the x87 control word inside the function (`DAT_00900528`, 24 bit precision and truncation,
at the start; the default word after every rounded conversion), and keep values on the x87 stack across those
switches.  A faithful C version needs the exact order of every x87 operation relative to each `fldcw`, which plain C
does not guarantee (gcc may move register arithmetic across an `asm volatile`); it would be mostly inline assembly.
Not done; they stay assembled.  The draw functions that call them are converted (they call the assembled spans).

## Details of the original that the C keeps

* **rdRaster_Span_Tex_5 is broken in the assembled build.**  Ghidra split it at 0x0042003c; `gen_asm.py` turned the
  two branches between the parts (`jle` to the epilogue, `jnz` back into the loop) into `ud2`, so the assembled
  function faults the first time it draws a pixel.  The C is the 1.01 behaviour (tested against the 1.01 bytes).
  This is a change against the current build (a fix), not against 1.01.
* x87 rounding: the edges and the `param_3` light levels round with the control words of `Services_SetCurrent`
  (`DAT_0090052a` round up for `frndint`, `DAT_00900526` round down for `fistp`, then `DAT_00900524`); the helpers
  `rd_ceilf` / `rd_floori` are those instruction sequences in inline asm.  Values the original stores to a float are
  stored to a volatile float (`rd_f`); values it keeps on the stack are long double.  `rdRaster_Edge_Flat_9` - `_12`
  use 1 / dy before it is rounded to a float for x (the other attributes use the float); `_4`, `_13` - `_16` divide by
  dy instead.
* The perspective edges (`_13`, `_15`, `_17`) store three plane values as floats in e[4], e[6], e[8] and their steps
  in e[5], e[7], e[9] (Ghidra shows them as int conversions from int arrays: they are float arrays at 0x007f43c8,
  0x007f4260, 0x007f4310); only edge A's plane values are stepped by the draw functions.
* The perspective draw functions also set `DAT_008ddf00` = `DAT_008ddedc` * 16 and `UINT_008ddefc` (the v mask,
  `(hdr[0x14] >> mip) << vshift`); the decompiler dropped both.
* `Draw_FlatLit_2` - `_6` and `Draw16_TexLit_4` set the span pointer `UINT_007f42f8`: for 8 bit targets every case of
  their switch on the texture width stores `Mem_DumpLog` (0x0045ff00, an empty function), so these variants draw
  nothing in 8 bit; for 16 bit a span function.  `Draw_FlatLit_*` call through the pointer (also when the depth is
  neither 8 nor 16: then the old value is called), `Draw16_TexLit_4` calls its spans directly.
* `rdRaster_Span_TexKey_3` sets the 8 bit address of the first pixel in `PTR_007f4300` and never advances it, and
  writes 16 bit pixels through `PTR_007f43a8`, which it does not set.  The 16 bit "blended" spans read the 8 bit
  pixel at `PTR_007f4300` without advancing it.  Kept.
* Shift counts come from globals and are taken mod 32 (`SAR`), as `sar reg, cl` does.

## Doubtful / least sure

* The x87 helpers depend on gcc emitting the long double arithmetic in source order between the inline asm
  statements.  This held at -O0 and -O2 in the tests (and the build compiles overrides at -O0), but it is a compiler
  behaviour, not a guarantee.
* The draw tests use convex polygons with the top / bottom vertex set correctly; degenerate polygons (top vertex not
  the topmost) were not generated.  The edge test does cover arbitrary vertex orders.
* Stack garbage: the original edge records are uninitialised stack; fields an edge function does not write (e.g. the
  steps when an edge covers one scanline) are never used before being written, in both versions, as far as the tests
  show.
