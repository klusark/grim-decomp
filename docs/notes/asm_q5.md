# Assembly to C: the software rasteriser, perspective half (agent q5)

Scope: the 108 functions of `src/GRIMFANDANGO.EXE/rdraster.c` that agent q4 left assembled in the perspective-correct
half of the RDroid software rasteriser (docs/notes/asm_q4.md, "Left assembled", first two rows): 0x0042d5f0 and
0x00437e10 - 0x00446030 (the z-buffered perspective pipeline: Grad_Flat_4, six edge set-ups, twelve drivers, 24 span
fillers) and 0x00451fa0 - 0x004710e0 (the 21 z-buffered fillers without z shift the opaque perspective drivers choose by
texture width, and the 44 fillers of the renderer without z-buffer that build/overrides_asm_p1.c's span drivers call).

Result: **all 108 are C now** (`build/overrides_asm_q5.c`).  Each is checked against the original 1.01 machine code (the
unpeepholed assembly of 2df265d) by a differential test: 1,000,000 cases per function, 0 differences (108,000,000 cases).
The clean-room tests report 5107 of 5107 the same.  `names/asm_funcs.json` 193 -> 85 GRIMFANDANGO.EXE entries.

## The peephole finding (q4) and what it changed

The perspective fillers start with `fldcw [0x00900528]` (round toward zero, 24-bit precision).  In the original their
first float -> int conversion (`fldcw floor; fld; fistp; fldcw [0x00900524]`) puts the default control word back, so only
the instructions before it run truncated at 24 bits.  `build/peephole.py` rewrites those conversions into SSE without the
control-word loads, so the assembled build ran each whole filler truncated at 24 bits: every perspective divide (1/z per
16 pixels), the u/v products, the per-part steps.  The C follows the original: it loads the same control words at the
same points (`q5_fldcw`; the values computed in between go through volatile stores, which keeps them on their side of the
load), and the test compares against the unpeepholed original.

How far the peepholed build was off (`PEEP=1` build of the test: the C, i.e. the original's behaviour, against the
assembly after build/peephole.py; 20,000 cases per function, `out/peep_20000.txt`):

* z-buffered fillers with z shift (24): 10 - 24 of 20,000 spans differ, 24 - 156 colour bytes in all (texel choice at
  the 16-pixel steps; z itself is converted before the restore, but the keyed fillers' z-buffer writes follow the
  texel choice).
* their drivers (12): 83 - 103 of 20,000 polygons differ (285 - 452 colour bytes); the opaque drivers 715 - 744 (their
  16 bpp no-z-shift fillers' state globals).
* fillers without z shift (21): ~5,600 of 20,000 spans differ, mostly in the span-state globals (u, v and their steps
  left for the next span), 52 - 215 colour bytes.
* SpanP16_* (21, renderer without z-buffer): ~12,500 of 20,000 spans differ (here everything up to the first
  conversion runs truncated even in the original: the initial 1/z divide and the first part's divide; the build kept
  truncating for the rest), 82 - 306 colour bytes.
* Grad_Flat_4, the edges, SpanR16_*, SpanR_FlatZw*: no difference (no truncating control word).

The clean-room tests draw 10 perspective polygons and matched the original with either version.  The differences are
single texels (u / v steps off by one in their low bits); this branch removes them for the 66 converted fillers.

### Proposed peephole.py fix for the 27 that stay assembled (not applied)

27 assembled functions outside this scope still load `0x00900528` (the non-z-buffered renderer's `Span16_Tex_10..15`,
`Span_Tex_6..8`, `Span*_TexKey_3..11`, `Span_FlatKey_2`, `SpanP8/16_TexKeyZw*`; `out/trunc_funcs.txt`), so the build
still runs them truncated.  `build/difftest/asm_q5/peephole_fix.py` is build/peephole.py with one change: in a function
that contains `fldcw [0x00900528]`, a rewritten floor / ceil sequence keeps its final `fldcw [default]` (the SSE
conversion does not need the control word; keeping the restore on every conversion of such a function gives the
original's behaviour whichever conversion runs first).  Tested on the 66 converted fillers of this round (same code
generator, same pattern): `PEEP=1 PEEPHOLE=build/difftest/asm_q5/peephole_fix.py` against this C (= the original):
2,160,000 cases, 0 differences (the current peephole: 385,049 difference lines).  On the 2df265d assembly it keeps 1167
`fldcw` (all in the 93 functions); on the current assembly only the 27 remain.  The 27 never run in the game or the
clean-room tests (the display always has a z-buffer), so the cost is nil; applying it is the lead's decision (it changes
build/peephole.py).

## How the family is built (and how the C is organised)

The z-buffered perspective drivers (`Draw_FlatLit_10..12`, `Draw_TexLitZ_7..9`, `Draw_TexLitKeyZw_7..12`) follow q4's
affine ones (q4_tex_setup / Q4_WALK) with three changes: `Grad_Flat_4` computes per vertex 1/(z+1), u/(z+1), v/(z+1) and
the screen-space plane gradients d/dx, d/dy of the three; the left edge carries the three plane values (1/z, u/z, v/z at
the row) and their per-row steps, the right edge only x (and light); the driver also stores the 16-pixel steps
float(16 * d/dx).  The fillers cut a span into a first part up to the next screen column that is a multiple of 16,
whole 16-pixel chunks and a last part of 1..16 pixels; at each part's end u = u/z / (1/z) and v are computed exactly and
stepped linearly in between.

C templates: `Q5_EDGE_FN(name, dir, PERSP, LIT)` (6 edges), `Q5_PSPAN8/16(name, LIT, KEY, G, PIXEL)` (24 fillers),
`Q5_ZSPAN(name, LIT, TEXEL, PIXEL)` (21 fillers without z shift), `q5_tex_setup` / `Q5_WALK` / `Q5_PICK` / `Q5_ODRAW` /
`Q5_TDRAW` (12 drivers), `Q5_ZWRITE` (2 z-buffer passes), `Q5_RSPAN` (21 affine) and `Q5_P16` (21 perspective) for the
renderer without z-buffer.  Reading aids in `build/difftest/asm_q5/`: `dump.py` (each function normalised, globals by
address, into out/fn/), `x87sym.py` (q4's symbolic x87 trace plus `_ftol` and a per-instruction stack trace,
X87TRACE=1); q4's `fdiff.py`, `core.py`, `setup.py`, `jtab.py`, `consts.py` were used as they are.

## x87 / odd behaviour kept

* Grad_Flat_4 (traced with x87sym.py): A = float(xa - xc), B = float(xb - xc), C = ya - yc, D = yb - yc (extended),
  R = float(1 / (C * B - D * A)); for each plane (Zb = float(Z[b] - Z[c]), Za likewise) d/dx = float((Zb * C - Za * D) *
  R), d/dy = float((Zb * A - Za * B) * -R); the integer z step is `_ftol` of the unrounded d(1/z)/dx * 65536.  Per vertex
  u/z = float(u * zi) with the unrounded zi but v/z = float(v * float(zi)).  The rounding biases test e = zi(a) * du/dx -
  u/z(a) * dz/dx > 0 (0x8000), < 0 or NaN (0x7fff), = 0 the same on the d/dy gradients.  Vertex choice and mip level as
  Grad_Flat_3 (q4).
* Edges: SpanR_Flat_13..16 divide (x1 - x0) / (y1 - y0) directly, _17 / _18 multiply by float(1 / (y1 - y0)) (q4's way);
  the plane values at the row are float((sub * d/dy + v0) + dxs * d/dx) for 1/z and u/z but float((dxs * d/dx + v0) +
  sub * d/dy) for v/z, with dxs = float(x start) - x0 extended; the steps float(float(t) * d/dx + d/dy).
* Fillers: the first part's / chunks' plane values are float(k * d/dx + start) / advanced by the stored 16-pixel steps;
  the last part's are 1 / ((k - 1) * d/dx - 16 d/dx + plane) kept extended (z-buffered) or stored (SpanP16_*);
  du = floor(float((u1 - u0) * (1/k) * 65536)) >> mip with 1/k the float table at 0x008fe000 (chunks 0.0625); a 1-pixel
  last part keeps u, v from the part before.  SpanP16_* use the rounded w for v (float(float(w) * v/z)) but the extended
  w for u.
* Left-over values: without a first part (span starting on a multiple of 16) u and v hold a register's value until the
  first chunk, so a 1-pixel span there is drawn with it: per filler the z value, the light, the colour or z-buffer
  pointer, or the bits of float(1/z * 65536) (macro argument G, found from the assembly and confirmed by the test).  The
  fillers without z shift and SpanP16_* keep their u, v state in globals, so it is the previous span's.
* `Span16_TexZ_5` and `_7` (translucent lit, 16 bpp) look the lit colour up as `UINT_008dde44[colour << 8]` and add it
  to the blend index instead of multiplying (the original reads up to 16 MB past the 64 KB table; the test's table is
  16 MB).  The generic lit filler without z shift (`Span16_TexZw`) adds light >> 8 unmasked (row and fraction) to the
  texel; the fixed-width ones mask the row.
* The fillers without z shift write the span count 0x007f4cac before the empty-span test, compare z's low 16 bits
  unshifted and write the z-buffer before the pixel; each part is drawn right to left in the original, left to right in
  the C (independent pixels; the state globals end the same).  SpanR16_* with a count <= 0 draw one pixel (index count -
  1), and the three generic ones keep u, v in memory, so their end state differs then (kept, MEM).
* `Draw_TexLitZ_9` / `Draw_TexLitKeyZw_12` set the blend table for every colour depth, the others as q4.

## Converted (108)

| addresses | names | kind | verification |
|---|---|---|---|
| 0042d5f0 | rdRaster_Grad_Flat_4 | plane gradients, per-vertex 1/z, u/z, v/z, mip, biases | 1,000,000 cases, 0 differences |
| 004391a0 .. 00442db0 | rdRaster_SpanR_Flat_13 .. _18 | edge set-up (left: x + planes; right: x; _17 / _18 with light) | 1,000,000 each, 0 |
| 00437e10, 0043c8d0, 00441520 | rdRaster_Draw_FlatLit_10, _11, _12 | driver, opaque (unlit / flat light / gouraud), filler by depth / z shift / width | 1,000,000 each, 0 |
| 004395c0, 0043e0e0, 00443000 | rdRaster_Draw_TexLitZ_7, _8, _9 | driver, translucent | 1,000,000 each, 0 |
| 0043a6e0 .. 00445570 | rdRaster_Draw_TexLitKeyZw_7 .. _12 | driver, keyed (opaque / translucent per light mode) | 1,000,000 each, 0 |
| 004383d0 .. 00446030 | rdRaster_Span_FlatZ_2, Span16_TexZ_2 .. _7, Span8_TexZ_2 .. _4, Span_TexZ, _2, Span8_FlatKeyZw_2, Span8/16_TexKeyZw .. _6 (24) | z-buffered perspective fillers, 8 / 16 bpp | 1,000,000 each, 0 |
| 00461c90 .. 004710e0 | rdRaster_Span16_TexZw, _2 .. _13, Span16_TexLitZw_9 .. _14, _23, _31 (21) | 16 bpp perspective fillers without z shift, by texture width | 1,000,000 each, 0 |
| 00451fa0, 00452070 | rdRaster_SpanR_FlatZw, _2 | z-buffer pass of the renderer without z-buffer | 1,000,000 each, 0 |
| 00452150 .. 00453ca0 | rdRaster_SpanR16_Tex .. _12, SpanR16_TexLit .. _9 (21) | affine 16 bpp fillers of the renderer without z-buffer | 1,000,000 each, 0 |
| 00453e30 .. 0045f550 | rdRaster_SpanP16_Tex .. _12, SpanP16_TexLit .. _9 (21) | perspective 16 bpp fillers of the renderer without z-buffer | 1,000,000 each, 0 |

Calls seen: q4's instrumented runs saw none of these in the game tour; the clean-room run draws 10 polygons through
Grad_Flat_4, Draw_FlatLit_10, SpanR_Flat_13 / 14 and Span16_TexZw_9.  Nothing stays assembled in this scope.

Prototype changes: none (the file declares the globals it uses with the types it needs; functions.h is not included).

## Differential test (`build/difftest/asm_q5/`)

A copy of q4's harness (`raster_test.c`, `build.sh`, `run_all.sh`, `run_par.sh`, `take_out.py`) with: the perspective
edge layout, random plane gradients / 16-pixel steps / integer z step, plane values 1/z in (0.02, 1] with u/z, v/z
(1/64 special values), edges near screen columns that are multiples of 16 and short spans (all part layouts, the
left-over case), random span-state globals of an earlier span (0x007f4c40 - 0x007f4d00, 0x007f4ac8 - 0x007f4b78), span
records for the renderer without z-buffer (kinds K_ZSPAN, K_NZW, K_NSPAN, K_NPSPAN), a 16 MB lut44, a blend-table
pointer that differs from the colormap's (a driver that does not set it is seen), larger perturbations of the 1/n
tables, the compared globals widened to 0x007f4440 - 0x007f4d00 and 0x008dde40 - 0x008ddf60, and a count of differing
cases / colour bytes.  The C is compiled exactly as build/link.py compiles override files (the file's pragmas select
-O2 / SSE4.1).  Control words: 0x00900528 = the default with 24-bit precision and truncation, as Services_SetCurrent
sets it; the precision control rotates 24 / 53 / 64 bits.

Results:

* `run_par.sh 1000000 8`: **108,000,000 cases, 0 differences** (1,000,000 per function; `out/par_1M.txt`).
* Against the assembly after build/peephole.py (`PEEP=1`): the differences listed above (`out/peep_20000.txt`); after
  the proposed fix (`PEEP=1 PEEPHOLE=build/difftest/asm_q5/peephole_fix.py`): 2,160,000 cases, 0 differences.
* `mutate.py 20000`: 27 of 28 mutations caught at 20,000 cases, the 28th (Grad_Flat_4's bias compare `>` -> `>=`, which
  needs e exactly 0) at 1,000,000 (42 cases).  Mutations: the peephole's behaviour (no default control word after the
  first conversion) in a z-buffered filler and in a no-z-shift filler, no truncating control word at the start, the
  first part's divide by the unrounded plane value, the last part's operand order, two left-over values (G), 1/k not
  from the table, Span16_TexZ_5's lookup corrected, key ignored, an edge's v/z operand order, direct divide replaced by
  the reciprocal, h < 2 -> h < 1, Grad_Flat_4's v/z from the unrounded zi and z step from the rounded d/dx and bias
  compare, the light mask, the span count written after the empty test, `>` -> `>=` in the z test, the blend table not
  set, a 16-pixel step * 15, the left edge's v/z step dropped, SpanP16 v0 from the extended w, SpanP16 never restoring
  the default control word, the chunk counter's end value, SpanR16 light mask, the shifted z pass's global count, the u
  bias.  (A first attempt, du not rounded to a float before its conversion, was not a mutation: q5_floor_i takes a
  float, so the C rounds there anyway.)

## Speed

Per call (`Q5_TIME=1`, cycles including the harness' call overhead of ~400, 30,000 cases, `out/timing*.txt`):

* against the original machine code (`raster_test.exe`, the code the C must match, with its fldcw pairs): every
  converted filler is about twice as fast (z-buffered fillers 1,390 - 2,300 -> 660 - 870; no-z-shift fillers 1,520 -
  1,960 -> 630 - 850; SpanP16 2,040 - 2,920 -> 950 - 1,260).
* against the peephole'd assembly the game linked until now (`raster_peep.exe`, which runs the fillers at 24 bits):
  Grad_Flat_4 1,231 -> 880, edges 437 - 503 -> 424 - 492, drivers (whole polygon) 2,314 - 3,086 -> 1,960 - 2,575,
  no-z-shift fillers 716 - 876 -> 678 - 842 (a few up to +15%), SpanR16 / SpanR_FlatZw 417 - 550 -> 377 - 433;
  z-buffered fillers 681 - 1,369 -> 656 - 882 (equal on average, single ones up to +15%: the C's divides run at the
  default precision as the original's do, the peephole'd ones at 24 bits, which divides faster); SpanP16 922 - 1,084 ->
  1,002 - 1,244 (+5 - 15%, same reason, plus the state globals they must leave).
* Frame time: not measured with bench_q4.py / libcheck.py: the perspective path does not run in normal play (q4's
  instrumented game tour saw none; 10 polygons in the clean-room run) and the renderer without z-buffer never runs, so
  a frame-time benchmark cannot see these functions.

## Commands and results

```
python -I build/difftest/asm_q5/dump.py                    # reading aid: out/fn/<name>.s
BUILD_ONLY=1 bash build/difftest/asm_q5/run_all.sh; build/difftest/asm_q5/out/raster_test.exe 20000   # 2,160,000 cases, 0 differences
bash build/difftest/asm_q5/run_par.sh 1000000 8              # 108,000,000 cases, 0 differences
PEEP=1 OUTEXE=raster_peep BUILD_ONLY=1 bash build/difftest/asm_q5/run_all.sh; out/raster_peep.exe 20000   # the peephole's differences (above)
PEEP=1 PEEPHOLE=build/difftest/asm_q5/peephole_fix.py OUTEXE=raster_peepfix BUILD_ONLY=1 bash build/difftest/asm_q5/run_all.sh
out/raster_peepfix.exe 20000                                 # 2,160,000 cases, 0 differences
python -I build/difftest/asm_q5/mutate.py 20000              # 27 of 28 caught; mutation 15 caught with 1,000,000
Q5_TIME=1 out/raster_peep.exe 30000; Q5_TIME=1 out/raster_test.exe 30000 Span   # timing above
python -I build/difftest/asm_q5/take_out.py                  # asm_funcs.json 193 -> 85, 108 bodies out of asm_funcs.s
rm -f src/*/*.[ch] src/*/*.md && python -I tools/build_src.py && make -C build -j8 && make -C build link   # OK
cd grim_tools/cleanroom && GRIM_DECOMP=<worktree>\build\run run.py decomp
    # 0 of 5107 tests differ, 0 are close (within 0.001), 5107 the same
```

Clean-room note: the first run of this round (64 of the functions converted, while an 8-process differential test was
running on the same machine) crashed in `save_load` (access violation in ResRef_Remove, called from
ModelComponent_Destroy during Engine_LoadGame; nothing of the rasteriser on the stack) and then reported 84 tests
different (text positions shifted by 3 pixels in the run that restarted after the crash).  The same binaries run again
on an idle machine: 5107 of 5107; the final build (all 108): 5107 of 5107.  Probably a timing-dependent problem
outside this scope; worth watching.
