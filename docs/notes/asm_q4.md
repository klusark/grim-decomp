# Assembly to C: the software rasteriser, pilot (agent q4)

Scope: the 243 functions of `src/GRIMFANDANGO.EXE/rdraster.c` that were still assembled at 2df265d (0x0040ea50 -
0x004710e0, the RDroid software rasteriser that draws the game's default display device, the windowed DIB).  The task
was a pilot: find a faithful, pixel-exact and fast-enough way to port this family, then port as much as possible.

Result: **67 of the 243 are C now** (`build/overrides_asm_q4.c`): the whole affine z-buffered pipeline - every function
of it that a normal run of the game calls, and their siblings.  Each is checked against the original 1.01 machine code
by a differential test (1,000,000 cases per function, 0 differences; 67,000,000 cases in all), the clean-room tests
report 5107 of 5107 the same, and frames are about 10% faster than with the assembly (numbers below).  176 stay
assembled (table at the end).

## Which variants run

An instrumented build (a `lock inc` counter at the entry of each of the 255 assembled functions of the range, dumped
by a thread; `out/cnt/`, not committed) was run through `bench_q4.py` (office idle + walk + a tour of 12 sets) and
through the clean-room suite:

* Game (real data): only 20 of the 243 run, all in the "z-buffered affine" half 0x0042d190 - 0x00437e10:
  `SpanR_Flat_11` 22.2M calls, `SpanR_Flat_12` 13.6M, `Grad_Flat_3` 10.8M, `Draw_FlatLit_9` 8.4M, `Span16_FlatZ_2`
  7.4M, `SpanR_Flat_9/10` 5.4M / 3.2M, `Span16_FlatZ_3` 2.7M, `Draw_FlatLit_8` 2.1M, `Span16_TexLitKeyZw` 1.8M,
  `SpanR_Flat_3/4/5/6`, `Draw_FlatLitZ_2/3`, `Span16_TexLitKey_3`, `Draw_TexLitKeyZw_3/5`.
* Clean-room suite: `Grad_Flat_3`, `Draw_FlatLit_7`, `SpanR_Flat_7/8`, and 10 polygons of the perspective family
  (`Grad_Flat_4`, `Draw_FlatLit_10`, `SpanR_Flat_13/14`, `Span16_TexZw_9`).
* The textured opaque drivers (`Draw_FlatLit_7/8/9`) draw their spans with the C fillers of
  `build/overrides_asm_o2.c` (`rdRaster_Span16_TexLitZw*`, chosen by texture width) when the z shift is 0, which is
  the game's case; their own 8/16 bpp fillers (`Span_TexLitZ_2`, `Span16_TexLitZ_4` ...) only run with a z shift.
  The non-z-buffered half (0x0040ea50 - 0x0042d190) and the perspective fillers at 0x00451fa0+ never ran.

## How the family is built (and how the C is organised)

The pipeline is ordinary cdecl code that passes its state through globals and two 0x44-byte edge records on the
driver's stack (no register-passed set-up in this half):

* `Draw_*(poly, material[, float light])`: copies the polygon's arrays (vertices x/y/z, u/v, light), top / bottom
  vertex, winding, the light / translucency table pointers and the canvas' z shift into globals (`UINT_007f44xx`,
  `UINT_008ddexx`), computes 1/(z+1) per vertex (directly or in `Grad_Flat_3`), sets the texture mip globals, then
  walks a left and a right edge (`SpanR_Flat_n` / `n+1`), calls the span filler per scan line, steps the edges
  (x, z, u, v, light, y), and sets up the next vertex pair when an edge's line count runs out.
* `SpanR_Flat*`: the edge set-up (16.16 x / u / v / light, float 1/(z+1)).
* `Span8/16_*`: one scan line, z-buffered (unsigned 16-bit compare, larger is nearer), 8 bpp palette index or 16 bpp.
* `Grad_Flat_3`: picks three vertices, the signs of the u / v plane gradients (rounding biases) and the mip level.

They are generated from a few templates that differ only by feature flags, so the C is macro-templated:
`Q4_EDGE_FN(name, direction global, UV, LIT)` makes the 12 edge functions, `Q4_SPAN_*` / `Q4_TSPAN8/16(name, LIT, KEY,
PIXEL)` the 48 span fillers (the per-pixel expression is the only part that differs; it is written out per function,
because the originals are not regular: e.g. the keyed translucent flat-lit filler blends then lights, the unkeyed one
lights then blends), `Q4_WALK` / `Q4_WALK_PTR` / `q4_tex_setup` / `Q4_PICK` the 18 drivers.  The asm reading aids in
`build/difftest/asm_q4/` (`fdiff.py` diff of two functions with labels normalised, `feat.py` globals / fields each
function touches, `core.py` the per-pixel core, `setup.py` a driver's set-up, `jtab.py` the texture-width switch,
`x87sym.py` symbolic trace of an x87 block, `consts.py` the float constants) were used to sort the 243 into templates.

x87 / conversion details kept (block comments above each template):

* The float -> int conversions are `fldcw floor; fld m32; fistp; fldcw default` and `fldcw ceil; fld m32; frndint;
  fstp m32` on floats; the C does the same with SSE4.1 `roundss` (+ `cvttss2si`), which is what `build/peephole.py`
  already turns them into in the build (exact for a float operand; NaN / out of range give 0x80000000 either way).
  No control-word change, so the C is as fast as the peephole'd assembly.
* Extended intermediates stay `long double`; every `fstp m32` of the original is a store through a volatile float
  (`q4_f`).  Edge set-up: `inv = float(1 / (y1 - y0))`, `sub = float(ceil(y0) - y0)`, per attribute
  `t = (a1 - a0) * inv` extended, `step = floor(float(t * 65536))`, `start = floor(float((float(t) * sub + a0) * 65536))`;
  z: `dz = float(t)` but `z = float(sub * t + z0)` with the unrounded t.  Span: `z` the same way with 1/n from the table
  at 0x008fe000; light, u, v by integer `imul` / `shrd 16` with 65536/n from 0x008fbfc0.
* `Grad_Flat_3`: the gradient block was traced instruction by instruction (it uses all eight x87 registers): du/dx uses
  the extended u differences, the other three gradients the float ones, R = 1/(C * float(B) - D * float(A)); compares
  are "greater" / "not greater-or-equal" exactly as the `test ah,1` / `test ah,0x41` branches (NaN goes the
  "unordered" way).  When the vertex next to the top is the bottom, the third vertex starts as the bits of the float
  argument and is only replaced by a vertex whose x differs from the top/bottom midpoint (an index the original uses
  as is otherwise; the game never gets there, the test does not generate it).
* The 16 bpp span x offset is `((pitch >> 1) * y + x) * 2` (not `pitch * y`), the right edge's x is converted with an
  unsigned shift (a negative right x gives a 65535-pixel span, in the original as well), the light step is set to 0 when
  it is in -1309 .. -1, the u / v shifts use the mip level and `16 - log2 width` modulo 32 (x86 shift counts).
* `Span16_TexLitZ_4` dithers the light: (l + {0, 0xc000, 0x8000, 0x4000}[col & 1 + 2 * (row & 1)]) >> 16, without the
  0..63 mask; its column counter runs down from the last pixel while the pixels go left to right (kept).  The original
  takes the parities as C remainders, so a negative column or row would index below its table on the stack; spans are
  on screen, the C uses `& 1`.
* `Draw_FlatLit_7/8/9` choose the span filler once, after the first two edge set-ups, into `UINT_007f44f0` (8 bpp
  without z shift: the empty `Mem_DumpLog`; 16 bpp: the C fillers by texture width 4 .. 256 / other); with another
  colour depth the pointer keeps its old value, as in the original.

Speed: build/link.py compiles override files without `-O` (that is -O0), which would make this hot code slow, so the
file starts with `#pragma GCC optimize("O2", "no-strict-aliasing", "no-omit-frame-pointer")` and
`#pragma GCC target("sse4.1")`, and its small helpers are `always_inline` (the pragma's -O2 alone did not inline them
into the macro-made functions: the first version called `q4_f` / `q4_floor_i` and its edge set-up was 30% slower than
the peephole'd assembly).  The differential test compiles the file exactly as link.py does, so the pragmas are part
of what is verified.

## Converted (67)

| address | name | kind | calls in the game run / clean-room | verification |
|---|---|---|---|---|
| 0042d190 | rdRaster_Grad_Flat_3 | gradients, mip | 10.8M / 19,889 | 1,000,000 cases, 0 differences |
| 0042e440, 0042e630 | rdRaster_SpanR_Flat, _2 | edge x, z | 0 / 0 | 1,000,000 each, 0 |
| 0042f140, 0042f330 | rdRaster_SpanR_Flat_3, _4 | edge x, z | 1.45M, 0.92M / 0 | 1,000,000 each, 0 |
| 0042ff50, 004301d0 | rdRaster_SpanR_Flat_5, _6 | edge x, z, light | 0.77M, 0.51M / 0 | 1,000,000 each, 0 |
| 00431400, 00431710 | rdRaster_SpanR_Flat_7, _8 | edge x, z, u, v | 0 / 50k, 30k | 1,000,000 each, 0 |
| 004338d0, 00433be0 | rdRaster_SpanR_Flat_9, _10 | edge x, z, u, v | 5.4M, 3.2M / 0 | 1,000,000 each, 0 |
| 00435f60, 00436300 | rdRaster_SpanR_Flat_11, _12 | edge x, z, u, v, light | 22.2M, 13.6M / 0 | 1,000,000 each, 0 |
| 0042e200, 0042e320, 0042ef00, 0042f020 | rdRaster_Span8/16_FlatZ, _2 | flat colour | Span16_FlatZ_2 7.4M | 1,000,000 each, 0 |
| 0042ea50, 0042eb90, 0042f770, 0042f8b0 | rdRaster_Span8/16_TexLitZ, _2 | translucent colour | 0 | 1,000,000 each, 0 |
| 0042fc30, 0042fdc0 | rdRaster_Span8/16_FlatZ_3 | gouraud colour | Span16 2.7M | 1,000,000 each, 0 |
| 004306c0, 00430860 | rdRaster_Span8/16_TexZ | gouraud translucent colour | 0 | 1,000,000 each, 0 |
| 00430fd0, 004311d0, 00431c90, 00431eb0 | rdRaster_Span_FlatZ, Span16_TexLit, Span8_TexLitZ_3, Span16_TexLit_2 | textured unlit: opaque 8/16, translucent 8/16 | 0 | 1,000,000 each, 0 |
| 00432350, 00432560, 00432a10, 00432c40 | rdRaster_Span8_FlatKeyZw, Span16_TexLitKey, Span8_TexLitKeyZw, Span16_TexLitKey_2 | textured unlit keyed: opaque 8/16, translucent 8/16 | 0 | 1,000,000 each, 0 |
| 00433480, 004336a0, 00434180, 004343b0 | rdRaster_Span_TexLitZ, Span16_TexLit_3, Span8_TexLitZ_4, Span16_TexLitZ_3 | textured flat-lit | 0 | 1,000,000 each, 0 |
| 00434880, 00434aa0, 00434f70, 004351a0 | rdRaster_Span8_TexLitKeyZw_2, Span16_TexLitKey_3, Span8_TexLitKeyZw_3, Span16_TexLitKey_4 | textured flat-lit keyed | Span16_TexLitKey_3 0.38M | 1,000,000 each, 0 |
| 00435a00, 00435c70, 00436950, 00436be0 | rdRaster_Span_TexLitZ_2, Span16_TexLitZ_4 (dithered), Span8_TexLitZ_5, Span16_TexLitZ_5 | textured gouraud | 0 | 1,000,000 each, 0 |
| 00437110, 00437390, 004378d0, 00437b60 | rdRaster_Span8_TexLitKeyZw_4, Span16_TexLitKeyZw, Span8_TexLitKeyZw_5, Span16_TexLitKeyZw_2 | textured gouraud keyed | Span16_TexLitKeyZw 1.75M | 1,000,000 each, 0 |
| 0042e010, 0042ecf0, 0042fa10 | rdRaster_Draw_FlatLitZ, _2, _3 | driver: flat colour (material / polygon light / gouraud) | _2 0.50M, _3 0.26M | 1,000,000 each, 0 |
| 0042e820, 0042f520, 00430450 | rdRaster_Draw_TexLitZ, _2, _3 | driver: translucent colour | 0 | 1,000,000 each, 0 |
| 00430a20, 00432ea0, 00435400 | rdRaster_Draw_FlatLit_7, _8, _9 | driver: textured opaque (unlit / flat / gouraud) | _8 2.1M, _9 8.4M; _7 clean-room 19,889 | 1,000,000 each, 0 |
| 00431a20, 00433ef0, 004366a0 | rdRaster_Draw_TexLitZ_4, _5, _6 | driver: textured translucent | 0 | 1,000,000 each, 0 |
| 00432100, 004327a0, 00434610, 00434ce0, 00436e80, 00437620 | rdRaster_Draw_TexLitKeyZw .. _6 | driver: textured keyed (opaque / translucent per light mode) | _3 0.11M, _5 0.21M | 1,000,000 each, 0 |

Prototype changes: none (functions.h is not included; the file declares the globals it uses with the types it needs).
`rdRaster_Grad_Flat_3` is defined with an `int` parameter (the float's bits: the original also uses them as an index,
see above, and a float parameter could be copied through the FPU); same stack slot as Ghidra's `float`.

## Differential test (`build/difftest/asm_q4/`)

* `run_all.sh [cases] [filter]` builds `out/raster_test.exe`: the original functions sliced from
  `git show 2df265d:src/GRIMFANDANGO.EXE/asm_funcs.s` (renamed `orig_*`; the original drivers call the original edge
  and span functions), `build/overrides_asm_q4.c` compiled exactly as build/link.py compiles override files (mingw32
  gcc, no -O on the command line), the original data image (`build/obj/GRIMFANDANGO.EXE/data_s.o`), the C span fillers
  of `build/obj/GRIMFANDANGO.EXE/overrides_asm_o2.o` (the opaque drivers call them), int3 stubs.  `run_par.sh [cases]
  [processes]` runs every function in parallel; `PEEP=1` slices from the assembly after `build/peephole.py` (the code the
  game really links; used for the timing below); `mutate.py` is the sensitivity check; `take_out.py` removed the 67
  from `names/asm_funcs.json` and `asm_funcs.s`.
* Each case: a canvas of random size (1..96 x 1..48), 8 / 16 / 24 bpp, random pitches (odd ones too), colour and
  z-buffers filled with random bytes plus margins, z shift 0 (the game's), 8, 16 or 0..16, random light / 16->8 /
  translucency tables and texel arrays (a quarter of the texels 0, for the key), texture records with log2 width 3..8,
  height 1..256, 1..4 mip levels or an out-of-range count (mode), level widths 4..256 and others (the C-filler switch);
  polygons of 1..12 vertices with screen x in [1, W + 1) and y in [0, H) (uniform, integers, halves, neighbours of
  integers, repeated x or y for vertical / horizontal edges), attributes (z, u, v, light) with 1/64 special values
  (0, -0, +-inf, NaNs, denormals, huge, +-2^31), random top / bottom / winding, polygon distances (ties at 0, 10, 20,
  30, 40), the 65536/n and 1/n tables sometimes perturbed; edge records and span edges random.  Edges get a random
  record, spans random left / right edges (same row, touching, empty).
* Compared after each call: return value, the edge records, the whole colour and z-buffer allocations with margins,
  the rasteriser globals 0x007f4440 - 0x007f4700 and 0x008dde40 - 0x008ddec0 (span pointer with orig_X mapped to X),
  the x87 control word and stack top; precision control 24 / 53 / 64 bits in rotation, with the floor / ceil / trunc
  control words set from it as `Services_SetCurrent` does.
* Not generated (the original crashes or reads its stack; the game's clipped polygons never do it): a negative right
  edge x, a mip level above log2 width, Grad_Flat_3's bit-pattern index (above), light beyond the table for the dithered
  filler.
* Results: `run_par.sh 1000000 8`: 67,000,000 cases, 0 differences.  Against the peephole'd assembly (`PEEP=1`),
  30,000 cases per function, 0 differences.  `mutate.py 20000`: 20 of 20 mutations caught (edge: rounded z step,
  unrounded float t, unrounded 1/dy, h < 1, missing ceil; span: unrounded t in z, light clamp bound, >= z compare,
  v shift, key ignored, dither constant, blend / light order; Grad: direction tie, mip threshold tie, farthest-vertex
  tie; drivers: light table row, width-switch case, flat light row shift, z step dropped, 1/(z+1) changed).

## Speed

* Per call (`Q4_TIME=1 raster_peep.exe 30000`, original = the peephole'd assembly the game links, cycles including
  the harness' call overhead of ~400): edge set-up 460-490 -> 440-465, flat spans 430-490 -> 420-450, textured spans
  470-590 -> 450-490, Grad_Flat_3 803 -> 794, drivers (whole polygon) 1060-1930 -> 1060-1740.  The C is as fast or
  faster everywhere.
* Frame time, `bench_q4.py` (own window title / command files; office idle, office walking, 12 sets, movies off,
  in-process `GRIM_PERFLOG` medians), A/B interleaved: mean of the 12 set medians **0.753 / 0.768 ms (2df265d) ->
  0.684 / 0.684 ms (this branch)**, about 10% less; office walking 0.745 / 0.780 -> 0.675 / 0.710 ms.  The machine was
  shared with other agents' runs, so single numbers move by 5-10%; every set was faster in both pairs.
* `build/perf/libcheck.py` (fixed 17 ms frames): all PASS for both builds; perf line 2.23 / 2.23 ms (2df265d, two runs)
  -> 2.13 ms; the idle and walk shots are pixel-identical to the 2df265d build (0.000%); the set shots differ by 3-10%
  between any two runs, 2df265d against itself included, so they say nothing here.

Observation (not changed, outside this file): the C span fillers of `build/overrides_asm_o2.c` that the opaque textured
drivers use in the game (`rdRaster_Span16_TexLitZw*`) are compiled at -O0 by link.py; the same pragma there would
probably speed up the game's main span loop.

## Found: build/peephole.py changes the perspective fillers' arithmetic

93 assembled perspective fillers (`SpanP8/16_*`, `Span16_Tex_10..15`, `Span_Tex*`, `Span*_TexZ*`, `Span*_TexKeyZw*`,
`Span16_TexZw*`, ...) start with `fldcw [0x00900528]` (truncate, 24-bit precision: a fast divide), but their first
float -> int conversion ends with `fldcw [0x00900524]` (the default), so in the original only the code before that
conversion runs at 24 bits / truncation; every later `fdiv` / `fmul` runs at the default precision and rounding.
`build/peephole.py` replaces those conversions by SSE without control-word loads, so in the build the truncating
24-bit mode stays on for the whole filler: the perspective divides of the build differ from the original's in their low
bits (texel choice at the 16-pixel steps).  The clean-room tests draw only 10 such polygons and still match.  A C port
of these must set the default control word back at the first conversion (or the peephole could keep `fldcw default`
after the first conversion of a function that loaded 0x00900528).

## Left assembled (176)

| addresses | names | reason |
|---|---|---|
| 0042d5f0, 004391a0 - 00446030 (43) | Grad_Flat_4, SpanR_Flat_13..18, Draw_FlatLit_10..12, Draw_TexLitZ_7..9, Draw_TexLitKeyZw_7..12, Span*_TexZ_2..7, Span*_TexKeyZw*, Span_FlatZ_2, Span8_FlatKeyZw_2 | the perspective-correct z-buffered half: the next family to port with the same method (drivers and edge set-up follow the same templates with Grad_Flat_4's plane equations; the fillers are 500-600 instructions each with the control-word pattern described above). Not reached in this session; 10 polygons in the clean-room run, none in the game tour |
| 00451fa0 - 004710e0 (65) | SpanR_FlatZw*, SpanR16_Tex*, SpanP16_*, Span16_TexZw*, Span16_TexLitZw_9..14/23/31 | span fillers of 0x00451fa0+: affine `SpanR16_*`, perspective `SpanP16_*`, and the `Span16_TexZw*` / `TexLitZw_*` the perspective FlatLit drivers choose by texture width; none ran in the game run (`Span16_TexZw_9`: 360 calls in the clean-room run); the perspective ones have the control-word pattern described above |
| 0040ea50 - 0042d190, 0042dd10 (68) | SetupPoly*, EdgeSetup_Flat*, Select_*, SpanR8/16_TexKey*, SpanP8/16_TexKeyZw*, Grad_Flat/_2, DrawPoints, DrawWireframe, DrawWireframeZ, Draw16_*, Edge_Flat*, Span16_Tex_10..15, Span_Tex_6..8, Span*_TexKey_3..11, FUN_0042003c | the non-z-buffered renderer (and the point / wireframe modes): never runs in the game or the clean-room tests (the display always has a z-buffer); parts of it pass state in registers (Select_* / FUN_ helpers); not attempted |

## Commands and results

```
bash build/difftest/asm_q4/run_par.sh 1000000 8        # 67,000,000 cases, 0 differences
PEEP=1 OUTEXE=raster_peep BUILD_ONLY=1 bash build/difftest/asm_q4/run_all.sh
Q4_TIME=1 build/difftest/asm_q4/out/raster_peep.exe 30000   # 0 differences; timing above
python -I build/difftest/asm_q4/mutate.py 20000         # 20 of 20 mutations caught
python -I build/difftest/asm_q4/take_out.py             # asm_funcs.json 271 -> 204, 67 bodies out of asm_funcs.s
rm -f src/*/*.[ch] src/*/*.md && python -I tools/build_src.py && make -C build -j8 && make -C build link   # OK
cd grim_tools/cleanroom && GRIM_DECOMP=<worktree>\build\run run.py decomp
    # 0 of 5107 tests differ, 0 are close (within 0.001), 5107 the same
python -I build/difftest/asm_q4/bench_q4.py <exe-dir> 4  # frame times above
python -I build/perf/libcheck.py <exe-dir> <tag> --data <private GRIMDATA copy> --sets 8   # all PASS
```
