# Assembly to C: the non-z-buffered software rasteriser (agent q6)

Scope (task 1): the 68 functions docs/notes/asm_q4.md left as "the non-z-buffered renderer (and the point / wireframe
modes)" (0x0040ea50 - 0x0042d190 and 0x0042dd10).  Task 2: whether the span fillers of build/overrides_asm_o2.c that the
game's textured drivers call per scan line can be compiled at -O2 and stay bit-exact.

Result: **67 of the 68 are C now** (`build/overrides_asm_q6.c`), each checked against the original 1.01 machine code by
a differential test (1,000,000 cases per function, 0 differences; 67,000,000 cases in all); one stays assembled
(FUN_0042003c: not a function, below).  The clean-room tests report 5107 of 5107 the same.  Task 2: the span fillers are now compiled at -O2 (with explicit x87 rounding points): bit-exact (23,000,000
differential cases against their original machine code, and 34 million in-game calls checked against the -O0 code,
0 differences) and frames about 35-40% faster (bench_q6 mean of 12 set medians 0.710 / 0.667 -> 0.440 / 0.480 ms;
libcheck perf 1.74 / 1.68 -> 0.93 / 1.00 ms/frame).

None of these functions runs in the game or in the clean-room run (q4's instrumented counts: the display always has a
z-buffer), so the differential test is the only check of their behaviour, and the file is compiled the way
build/link.py compiles every override file, at -O0, without speed pragmas (see "x87 and the -O level").

## The two families

* **The edge walker** (0x00418fe0 - 0x0042d190, the siblings of build/overrides_asm_o1.c): `DrawPoints`,
  `DrawWireframe`, `DrawWireframeZ` (outline with rdCanvas_DrawLine; Z keeps its state in the z-buffered half's
  globals), the drivers `Draw16_FlatLit`, `Draw16_TexLit`, `Draw16_FlatLit_2`, `Draw16_TexLitKey_7` (walk a left and a
  right edge record down the polygon, one span per scan line), the edge set-ups `Edge_Flat`, `_2`, `_3` (o1's `rd_edge`
  template with a division for the slope), `Span16_Tex` (translucent flat), the gradient set-ups `Grad_Flat` (affine:
  u / v rounding biases and the mip level) and `Grad_Flat_2` (perspective: 1/z, u/z, v/z per vertex and their screen
  gradients), and 21 perspective-correct spans (`Span16_Tex_10` .. `_15`, `Span_Tex_6` .. `_8`, `Span_FlatKey_2`,
  `Span16_TexKey_6` .. `_11`, `Span_TexKey_5` .. `_7`, `Span8_TexKey_3`, `_4`).
* **The span-list renderer** (0x0040ea50 - 0x00418fe0, the siblings of build/overrides_asm_s1.c): a selector
  (`Select_TexLit`, `Select_FlatLit_4`, `_5`, `_8` .. `_13`) fills a polygon record (rec[0] the polygon, per vertex
  1/z, u/z, v/z, the gradients, biases, mip level, texture fields, colour tables) with `SetupPoly` (affine) or
  `SetupPolyTex` (perspective) and stores the callbacks of an edge set-up (`EdgeSetup_Flat` .. `_10`: one node per
  edge, from its upper vertex, with x / u / v / light / 1/z or the three plane values) and of a span-list drawer (C
  since s1), which calls one span function per node: affine `SpanR8/16_TexKey`, `_2`, `_3` or perspective
  `SpanP8/16_TexKeyZw`, `_2`, `_3` (keyed, the z of a drawn texel written to the z-buffer without a depth test).

All 67 are plain cdecl functions: no register arguments (checked: `regargs.py` lists the registers each reads before
writing them; only callee-saved pushes and `push ECX` frame slots), the callers in asm_funcs.s and C pass stack
arguments only.  `Select_FlatLit_13` returns 1, the `EdgeSetup_*` / `Edge_Flat*` return 0 / 1; the other selectors
leave EAX undefined (void).

## How the C is organised

The variants are generated from a few templates (the asm reading aids in `build/difftest/asm_q6/` sorted them:
`groups.py` closest function by normalised diff, `psig.py` x87 sequence / integer diff against a reference,
`pbody.py` the pixel loops, `nohead.py` the no-head path of the perspective spans, `x87sym2.py` a symbolic x87 trace
that also follows integer registers, `feat.py` globals / calls / x87 counts, `regargs.py` register arguments; they read src/GRIMFANDANGO.EXE/asm_funcs.s,
so they need the assembly of 2df265d now that the functions are out of it):

* `q6_edge_x` (Edge_Flat*), `q6_walk_x` (the flat drivers), `q6_wireframe`.
* `q6_pick` (third vertex and search direction of Grad_Flat / _2 and SetupPoly / SetupPolyTex, as q4's Grad_Flat_3 but
  with the `_ftol` pre-test of the original: the slope test only when |_ftol(xc - xb)| > 1 or |_ftol(xc - xa)| > 1),
  `q6_affine_bias` (the four affine gradients and the biases, shared by Grad_Flat and SetupPoly), `q6_mip_level`.
* `q6_pspan(L, R, kind, bpp16, key, pixel)`: the 20 perspective spans of the edge walker.  Three kinds (identical
  x87 sequences within a kind, `psig.py`): 10 (the unlit drivers' spans: the tail step divides by float(t)), 12 (the
  light-level spans: the tail step multiplies by the 1/n table), 15 (gouraud: as 12, the third plane value rounded to
  a float at the start, a light value l stepped per pixel).  Eight pixel expressions (`Q6P_*`).  `Span16_Tex_14` is a
  separate implementation of kind 15 whose every intermediate value lives in a global (0x007f4240 .. 0x007f4458): the
  C keeps them all there (they are left with the last values, the run counter at -1) and follows its own x87
  differences (head / tail counts stored as floats, 1/p stored and v = float(1/p) * V).
* `q6_esetup(node, rec, i0, i1, flags, down, up)`: the ten EdgeSetup functions (`Q6E_LIGHT`, `Q6E_UV`, `Q6E_PERSP`,
  `Q6E_DIV`); `q6_spanr`, `q6_spanp`: the span-list spans (`Q6R_*` pixels); the selector helpers.

## x87 and the -O level

* As in o1 / q4: `long double` for values the original keeps on the x87 stack, `q6_f` (a volatile float store) at
  every FSTP m32, `q6_floor_i` / `q6_ceil` are the original's `fldcw floor; fld; fistp; fldcw default` /
  `fldcw ceil; fld; frndint; fstp; fldcw default` in inline assembly (so they also load the default control word).
* The perspective spans load DAT_00900528 (truncate, 24-bit precision) after the empty-span test; everything up to the
  first float -> int conversion runs in that mode, which conversion leaves the default word loaded (q4's finding: the
  peephole'd build keeps the 24-bit mode for the whole span; the C follows the original, not the peephole).  Which
  arithmetic is in the 24-bit mode depends on the path: with a head, its set-up; without, the 16-pixel steps of the
  start values and the first run's (or the tail's) divisions.  The C loads the word at the same two points
  (`q6_fldcw`) and does its conversions with the original sequence.  The span-list's SpanP spans load it first of all,
  so only `z = floor(float(W * 65536))` runs in it.  This relies on the statement order, which is why the file is
  compiled at -O0 (link.py's level; there is no speed reason for -O2 here); the values that cross a control-word load
  are in memory (volatile floats or long double locals) either way.
* Compares follow the original's `test ah` masks (NaN goes the "unordered" way): `!(d >= 0)` for the `fchs`
  absolute values, `d > max` for the farthest vertex, `!(x >= 0)` for "negative or NaN" in the biases.

## Odd behaviour kept

* **Spans starting on a multiple of 16** (no head) that are a single tail pixel: the original draws it with u / v
  registers it never set in that path.  Edge walker: the bits of the first plane value after its 16-pixel step (the
  8 bpp gouraud spans: the light value); Span16_Tex_14: the globals' old u / v; SpanP: the bits of the z-buffer
  pointer (SpanP16_TexKeyZw and _2: of the colour pointer).  The C uses the same bits.
* `Span16_Tex_13` and `_15` index the 16 bpp -> palette index table with `colour << 8` (`texpal[pal[tx] << 8]`), up to
  16 MB past the 64 KB table, then blend with `texpal[*PTR_007f4300]` (the stale 8 bpp pointer, also read by
  `Span16_Tex`, `Span16_Tex_11`, `Span16_TexKey_7`, `_9`, `_11`).  Kept (the test gives the table 16 MB).
* The edge walker spans take the head as `16 - xl % 16` with C's remainder (17 .. 31 pixels for a negative xl); the
  SpanP spans `16 - (x & 15)`.
* `Grad_Flat`: the third vertex starts as the argument's bits; `SetupPoly`: as the record pointer's bits (an index the
  original uses if no vertex beats 0, when the vertex next to the top is the bottom).  `Grad_Flat_2` and
  `SetupPolyTex` start it from a stack slot they never write (the caller's garbage): **the C starts it at 0**, the one
  place where the C cannot reproduce the original; the test does not generate those polygons (some vertex between top
  and bottom must be clearly away from the top / bottom midpoint), the game's clipped polygons are not degenerate there.
* `SetupPolyTex`'s biases use the extended dU/dx and dW/dx left on the x87 stack across the mip-level code; its
  +0x19c is `_ftol(dW/dx * 65536)` of the extended value.  `Grad_Flat_2` and `SetupPolyTex` differ in which
  differences are rounded (Grad_Flat_2: dWa as a float; SetupPolyTex: dWa and dWb extended).
* EdgeSetup_8 / 9 divide for the x slope, EdgeSetup_10 multiplies by float(1 / dy); the perspective edges give an edge
  going up no plane values and a one-line edge no plane steps.  The V start value is associated as
  `(gV_x * dxs + Va) + gV_y * dy`, W and U as `(g_y * dy + a) + g_x * dxs`.
* `Select_TexLit` loops with an unsigned count; `SpanR` loops `while (--n)`-style on the count (0 draws nothing).

## Converted (67)

| address | name | kind | verification |
|---|---|---|---|
| 00418fe0 | rdRaster_DrawPoints | points | 1,000,000 cases, 0 differences |
| 00419150, 0042dd10 | rdRaster_DrawWireframe, DrawWireframeZ | outline (rdCanvas_DrawLine calls logged) | 1,000,000 each, 0 |
| 00419680, 00419840, 00419f70 | rdRaster_Edge_Flat, _2, _3 | edge set-up, x | 1,000,000 each, 0 |
| 00419450, 00419a00, 00419ca0 | rdRaster_Draw16_FlatLit, Draw16_TexLit, Draw16_FlatLit_2 | drivers, flat | 1,000,000 each, 0 |
| 0042c010 | rdRaster_Draw16_TexLitKey_7 | driver, perspective gouraud keyed | 1,000,000, 0 |
| 00419be0 | rdRaster_Span16_Tex | span, translucent flat | 1,000,000, 0 |
| 00418550, 00418a00 | rdRaster_Grad_Flat, _2 | gradients, mip | 1,000,000 each, 0 |
| 00421510, 004221f0, 00422820, 00423150, 00423740, 00424020, 00424670 | rdRaster_Span16_Tex_10, Span_Tex_6, Span16_Tex_11, Span_FlatKey_2, Span16_TexKey_6, Span_TexKey_5, Span16_TexKey_7 | perspective spans, kind 10 | 1,000,000 each, 0 |
| 00425150, 00425e50, 004264a0, 00426e30, 00427470, 00427d70, 004283f0 | rdRaster_Span16_Tex_12, Span_Tex_7, Span16_Tex_13, Span8_TexKey_3, Span16_TexKey_8, Span_TexKey_6, Span16_TexKey_9 | kind 12 | 1,000,000 each, 0 |
| 0042a070, 0042a790, 0042b1f0, 0042b8e0, 0042c2c0, 0042c9f0 | rdRaster_Span_Tex_8, Span16_Tex_15, Span8_TexKey_4, Span16_TexKey_10, Span_TexKey_7, Span16_TexKey_11 | kind 15 | 1,000,000 each, 0 |
| 00428f00 | rdRaster_Span16_Tex_14 | kind 15 with globals | 1,000,000, 0 |
| 0040ea50, 0040ef90 | rdRaster_SetupPoly, SetupPolyTex | polygon record set-up | 1,000,000 each, 0 |
| 0040fe90, 00411630, 00412090, 004134a0, 00413ce0, 00414be0, 004154c0, 00416470, 00416e70 | rdRaster_Select_TexLit, Select_FlatLit_4, _5, _8 .. _13 | selectors | 1,000,000 each, 0 |
| 0040f770, 0040fbe0, 0040ffe0, 004104e0, 00410d80, 00411ba0, 00412a30, 004139f0, 004151d0, 00416a50 | rdRaster_EdgeSetup_Flat .. _10 | edge set-up into a node | 1,000,000 each, 0 |
| 004113e0, 004114f0, 00412280, 004123b0, 004131f0, 00413340 | rdRaster_SpanR8/16_TexKey, _2, _3 | affine span node | 1,000,000 each, 0 |
| 00413ee0, 00414530, 00415720, 00415dc0, 004170a0, 00417790 | rdRaster_SpanP8/16_TexKeyZw, _2, _3 | perspective span node | 1,000,000 each, 0 |

Prototype changes: none (functions.h is not included; the file declares what it uses).  `Grad_Flat` / `_2` are
defined with an `int` parameter (the float's bits, also used as an index; same stack slot), `SetupPoly` / `SetupPolyTex`
/ the selectors / EdgeSetups with `int *` records.

## Differential test (`build/difftest/asm_q6/`)

* `run_all.sh [cases] [filter]` builds `out/q6_test.exe`: the originals sliced from `git show
  2df265d:src/GRIMFANDANGO.EXE/asm_funcs.s` (renamed `orig_*`, calling each other, and `orig__ftol`), the C compiled as
  build/link.py compiles override files, the data image `build/obj/GRIMFANDANGO.EXE/data_s.o`, the C neighbours the
  originals call (`overrides_asm_o1.o`, `overrides_asm_s1.o` of the linked build), int3 stubs (and a check that no data
  symbol got stubbed); `run_par.sh [cases] [processes]` runs every function in parallel; `mutate.py` is the
  sensitivity check; `take_out.py` removed the 67 from `names/asm_funcs.json` and `asm_funcs.s`; `dbg.sh` runs a case
  under gdb.
* Each case: canvas 1..96 x 1..48, 8 / 16 / 24 bpp, random pitches, colour and z-buffers of random bytes with 4 KB
  margins (the z-buffer 74 KB away from the colour buffer, so pointer bits used as u / v differ), z shift 0..32, light
  / palette / translucency / 16 MB index tables, textures (log2 width 3..8, mip levels, widths), 1/n and 65536/n tables
  (perturbed by 1 ulp / +-2 in 1/32, a random 1/n in 1/64); polygons of 1..12 vertices, half of them convex with their
  real top / bottom and (mostly) the winding that puts edge A on the left, coordinates as q4 (integers, halves,
  neighbours, repeated x / y), special values (0, -0, inf, NaN, SNaN, denormals, huge, +-2^31, +-32768) in attributes
  and, for the edge / gradient set-ups, in x / y; edge records with plane values (1/z 0.05..2, u, v up to 300 or up to
  9 million texels, gradients, 16-pixel steps usually 16 * gradient, light steps around the -1309..-1 clamp), starts
  on multiples of 16, negative starts, 0..3-pixel spans; polygon records with per-vertex W / U / V and gradients;
  span nodes; x87 precision control 24 / 53 / 64 bits in rotation with the floor / ceil / truncate words derived.
* Compared after each call: return value (where there is one), colour buffer and z-buffer with margins, edge records,
  polygon, polygon record, span nodes, the rasteriser globals 0x007f4200 - 0x007f4600 and 0x008dde40 - 0x008ddf60
  (a word where the original stored orig_X and the C X counts as equal), the rdCanvas_DrawLine calls (a stand-in that
  logs its 7 arguments), the x87 control word and stack top.
* Not generated: polygons where Grad_Flat_2 / SetupPolyTex would use their uninitialised slot (and Grad_Flat /
  SetupPoly their bit-pattern index), negative span-node counts (4 G pixels in both), light levels outside 0..63 for
  the light-level drivers / selectors (table rows).
* Results: `run_par.sh 1000000 7`: 67,000,000 cases, 0 differences (after the last change; the full run before it
  found that SpanP16_TexKeyZw_3's no-head u / v come from the z-buffer pointer, not the colour pointer as in
  SpanP16_TexKeyZw: fixed).  `mutate.py 20000`: 34 of 34 mutations caught (perspective spans: no 24-bit mode, the
  no-head u / v sources, tail step by the table, unrounded 1/p, tail one pixel short, no light clamp, head 1/n index,
  Span16_Tex_13's index; Span16_Tex_14: extended 1/p, run counter; Edge_Flat: unrounded slope, one-line rounding;
  Grad: float E, extended 1/z, mip threshold tie, the _ftol test; SetupPolyTex: rounded dWa, NaN in the bias, _ftol vs
  floor; SetupPoly: mip mode; selectors: level row, palette row 63; EdgeSetup: rounded dW, V plane association, _10 by
  division, up-edge y; SpanR: z step; SpanP: two no-head sources, z of transparent texels; DrawPoints, DrawWireframe,
  Span16_Tex).  Mutations that turned out (nearly) equivalent were replaced: rounding p2 inside the 24-bit mode (it
  already has 24 bits), (u1 - u0) rounded to a float (exact by Sterbenz), 0.0625 * 65536 folded, dy from
  floor(ceil(y)).

## Left assembled (1)

| address | name | reason |
|---|---|---|
| 0042003c | FUN_0042003c (`@FUN_0042003c@8`) | not a function: the inner loop tail of rdRaster_Span_Tex_5 that Ghidra split off (o1's notes); it runs on that function's registers and stack frame (EAX, EBX, ECX, EDX, ESI, EDI, EBP all live on entry), its back jump is a `ud2` in the generated assembly, and nothing calls it (Span_Tex_5 is C since o1).  No C function can express it; it is dead code. |

## Task 2: build/overrides_asm_o2.c's span fillers at -O2

q4 noticed that the 23 span fillers at the end of build/overrides_asm_o2.c (`rdRaster_Span16_TexLitZw`, `_2` .. `_8`,
`_15` .. `_22`, `_24` .. `_30`: the 16 bpp spans that q4's `Draw_FlatLit_7` .. `_9`, the game's opaque textured
drivers, call per scan line when the z shift is 0) are compiled at -O0 by build/link.py.  At -O0 every global access
goes through `img_addr_()` (a range check, a call per access, also per pixel in the loop) and every value through
memory.

**Applied** (bit-exact and faster; this touches build/overrides_asm_o2.c, round 4's file, in its span section only).
The change, made with `build/difftest/asm_q6/o2span_patch.py` and limited to the
span section (`#pragma GCC push_options` / `optimize("O2", "no-strict-aliasing", "no-omit-frame-pointer")` /
`pop_options`):

* the span section's `RG32` / `RGU32` / `RG16` and address literals use `SPAN_DATA(a)` = `sect_data + (a -
  0x004dd000)` (all are .data addresses) instead of `IMG_ADDR(a)`: `img_addr_` is defined (at -O0) in
  ghidra_types.h and gcc does not inline a function of another optimisation level into -O2 code;
* x87: the FSTP m32 points of the original (z step and z start before their conversions, the frac / 65536 float) are
  stores through a volatile float (`span_f`); the float `dzf` that the z start reads after the first conversion is
  volatile, so that arithmetic cannot be scheduled before the conversion's `fldcw` pair (it runs in the default
  control word in the original; the test sets the caller's word and the default word differently); `span_fist`
  clobbers memory and is always_inline.

Verification: `o2span.sh` compiles the file as build/link.py does and links it against the originals sliced from
`git show 9a56b04^:src/GRIMFANDANGO.EXE/asm_funcs.s` (round 4, which converted them, kept their test as
build/difftest/asm_s5/span_test.c: random spans, z-buffer, texture, palette, tables, control words, precision 24 / 53
/ 64 bits; colour surface, z-buffer and the span state globals compared): 23,000,000 cases (1,000,000 per function),
0 differences.  The -O0 file passes the same
test (2,300,000 cases, 0 differences).  A plain `optimize("O2")` without the volatiles also passed 230,000 cases
(gcc happened to spill there), but nothing would keep it so; the volatiles make the rounding points explicit.

Speed:

* Per call (`TIME=1 o2span.sh`, `o2span_time.c`: the same random 16 bpp spans of 1..200 pixels, half the z-buffer in
  front, rdtsc around each call): original machine code ~1,240 cycles, the C at -O0 2,370 / 2,550, at -O2 1,203 /
  1,205 (mean over the 23 functions, two runs each).
* Frame time (`bench_ab.sh`: `bench_q6.py`, a copy of q4's bench_q4.py with its own command / log files and window
  tag; office idle, office walking, 12 sets, 4 s dwell each, in-process `GRIM_PERFLOG` medians), A = this branch with
  the -O0 spans, B = with the -O2 spans, interleaved A B A B:

| | A (-O0) round 1 | B (-O2) round 1 | A round 2 | B round 2 |
|---|---|---|---|---|
| office idle | 0.730 | 0.420 | 0.720 | 0.400 |
| office walk | 0.660 | 0.430 | 0.670 | 0.410 |
| mean of 12 set medians | 0.710 | 0.440 | 0.667 | 0.480 |

  About 35-40% less frame time (ms/frame); apart from the three near-empty sets (ga, ce, sh: 0.05 ms) every set is
  faster in both rounds except bi.set in round 2 (B 0.995 against A 0.850 and 0.965; 0.645 in B's round 1).  The machine was shared with other agents' runs; the differential tests were not running during the
  benchmark.
* `build/perf/libcheck.py` (`libcheck_ab.sh`, 8 sets, a private mod directory): all PASS for both builds; perf (fixed
  17 ms frames, 256 frames) 1.74 and 1.68 ms/frame with the -O0 spans, 0.93 and 1.00 with the -O2 spans (two runs
  each).  `--diff`: probe.txt differs only in the `RU` line (random() before randomseed, different in every run); the
  idle shot is identical within each build over two runs but differs by 0.086% between the builds; the walk and set
  shots differ between any two runs (26% walk between two -O0 runs).  libcheck takes its shots after wall-clock
  sleeps, and with frames at a fixed 17 ms of game time a build twice as fast is at a later game time then.  To make
  sure the 0.086% is that and not the spans, `ingame_check.py` builds (for the check only, nothing committed) an exe
  whose `rdRaster_Span16_TexLitZw*` run the -O0 code and then the -O2 code on the same state (the span's colour and z
  rows, the span globals, the control word) and log every difference: a libcheck run with 12 sets through it made
  **34,406,400 span calls, 0 differences**, none skipped.

## Commands and results

```
bash build/difftest/asm_q6/run_par.sh 1000000 7         # 67,000,000 cases, 0 differences
python -I build/difftest/asm_q6/mutate.py 20000         # 34 of 34 mutations caught
python -I build/difftest/asm_q6/take_out.py             # asm_funcs.json 193 -> 126 (GRIMFANDANGO.EXE), 67 bodies out of asm_funcs.s
rm -f src/*/*.[ch] src/*/*.md && python -I tools/build_src.py && make -C build -j8 && make -C build link   # OK
cd grim_tools/cleanroom && GRIM_DECOMP=<worktree>\build\run run.py decomp
    # task 1 alone: 0 of 5107 tests differ, 0 are close (within 0.001), 5107 the same
    # with task 2 (final tree): 0 of 5107 tests differ, 0 are close (within 0.001), 5107 the same
python -I build/difftest/asm_q6/o2span_patch.py <o2 at -O0> build/overrides_asm_o2.c
bash build/difftest/asm_q6/o2span.sh 23000000            # 23,000,000 cases, 0 differences (the -O0 file: 2,300,000, 0)
TIME=1 OUTEXE=t_O2 BUILD_ONLY=1 bash build/difftest/asm_q6/o2span.sh 1 build/overrides_asm_o2.c; out/t_O2.exe 20000
bash build/difftest/asm_q6/bench_ab.sh <dir -O0 spans> <dir -O2 spans> 2 4
python -I build/perf/libcheck.py <exe-dir> <tag> --data <mod dir> --out <dir>   # all PASS; 1.74 / 1.68 -> 0.93 / 1.00 ms/frame
python -I build/difftest/asm_q6/ingame_check.py <o2 -O0> <o2 -O2>; make -C build link; libcheck --sets 12   # 34,406,400 calls, 0 differences (then restored)
```
