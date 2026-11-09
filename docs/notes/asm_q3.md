# Assembly to C, round q, agent q3

Scope: four GRIMFANDANGO.EXE functions that were still built from the original machine code: the two puppet functions
(rdPuppet_AdvanceTrack, rdPuppet_UpdateFrame), the text .3do loader (rdModel3_LoadText) and the Direct3D mesh batcher
(rdCache_DrawMeshList3D).

Result: **all four converted to C**, each verified against the original 1.01 machine code (sliced from the assembly of
2df265d) by a differential test with 0 differences, and the clean-room tests report 5107 of 5107 the same.

Files:

* `build/overrides_asm_q3.c`: the C (GRIM_EXE), one `/* OVERRIDES: name */` line before each definition, a block comment
  above each function with what it does and the x87 / compare / integer details kept.
* `build/difftest/asm_q3/`: `build.sh` (slices the original functions out of `git show 2df265d:src/GRIMFANDANGO.EXE/asm_funcs.s`,
  links them with the C, the data image `build/obj/GRIMFANDANGO.EXE/data_s.o` and the stand-ins; `LINKPY=1` compiles the C
  with the flags build/link.py uses, `EXTRA_CFLAGS=-O2` at -O2), `puppet_test.c`, `model_test.c`, `cache_test.c`,
  `mutate.py` (sensitivity check), `run_all.sh` (everything below).
* `names/asm_funcs.json`: 0x004507e0, 0x00450ba0, 0x0040aa20, 0x00406aa0 removed (GRIMFANDANGO.EXE: 271 -> 267).
* `src/GRIMFANDANGO.EXE/asm_funcs.s`: the four bodies removed with `build/difftest/asm_p2/strip_asm.py`.

## Converted

| address | name | what it does | verification |
|---|---|---|---|
| 004507e0 | rdPuppet_AdvanceTrack | advances one track's time by dt; at the end of the animation holds (0x20: then stops the track; 0x40; 0x80: fades out over 0.25 s) or wraps (loop count = FRNDINT of time/frames with the control word DAT_00900526); calls the marker callback for the markers passed | 1,000,000 cases at -O0, 1,000,000 with the link.py flags, 250,000 at -O2: 0 differences (also 250,000 without signalling NaN inputs) |
| 00450ba0 | rdPuppet_UpdateFrame | advances each animation node's current key, blends the two highest track priorities per joint (position / rotation, weights, Math_NormalizeAngle180), Angles_ToMatrix, Matrix_BuildTransform with a non-zero scale, rdThing_BuildNodeMatrix | same runs: 0 differences |
| 0040aa20 | rdModel3_LoadText | the text .3do loader (stdConffile lines, the game's sscanf / strtok / atoi): materials, geometry sets, meshes (vertices, uvs, normals, faces with vertex / uv lists), hierarchy nodes | 1,000,000 cases at -O0, 1,000,000 with the link.py flags, 250,000 at -O2: 0 differences (about 31 % of the cases load a model, the rest are rejected at some mutated line) |
| 00406aa0 | rdCache_DrawMeshList3D | the D3D path of the mesh cache: mip level, texture upload (rdMaterial_EnsureTexture), light levels, D3D vertices, triangle fans into the textured / untextured lists | 1,000,000 cases at -O0 (and 250,000 without signalling NaN), 1,000,000 with the link.py flags, 250,000 at -O2: 0 differences |

Every test compares the whole state the function can change: memory (puppet / model / cache arenas, the global regions:
D3D vertex buffer, both triangle lists and counts, cache entries, the scan buffer DAT_009056c0), the call log of the
stand-in callees (arguments as dwords, strings by content, stack pointers as one marker), the return value, the x87
control word and stack top; NaN payloads must match too (no "NaN-payload-only" cases in any run).

Prototype change: `rdModel3_LoadText` is `undefined4 rdModel3_LoadText(char *path, char *model)` (two arguments: the
original reads `[ESP+0x2049c]` / `[ESP+0x204a0]` after its 0x20488-byte frame; its only caller, rdModel3_Load, passes
these two).  functions.h keeps Ghidra's 8-parameter prototype; the override renames it while functions.h is included
(as asm_p2 did).  The other three keep their prototypes.

## Odd behaviour kept

* rdPuppet_AdvanceTrack: dt equal to 0 **or NaN** does nothing; the wrap divides by the FILD of the unsigned frame count
  and rounds the float quotient with DAT_00900526 (round down in the game), the product count * loops stays extended;
  the key slots are cleared for min(model node count, 0x40); after each marker callback the animation pointer and the
  marker count are read again; the original returns garbage in EAX (void, no caller reads it).
* rdPuppet_UpdateFrame: the rotation y / z of a key with velocity stay extended until the rest rotation is subtracted
  (x is stored first); a lower priority track is still blended while the best weight is NaN; the scale test is "ordered
  and non-zero" (a NaN scale component does not call Matrix_BuildTransform).
* rdModel3_LoadText: the third per-vertex array (+0x3c, 4 bytes per vertex) is cleared for only `vertices` bytes; the
  vertex intensities and normals go through FLD / FSTP, every other float is copied as a dword; the material count
  >= 0x80 only asserts and goes on; "mesh %d" is scanned into the global buffer DAT_009056c0.
* rdCache_DrawMeshList3D: the light clamp compares the extended sum with 0 and the float of it with 1 (observably the
  same); the "no alpha in the device caps" flag stays set for every later mesh; the triangle fan of a mesh uses the
  vertex count taken before a texture upload that had to flush (the retry path); geometry 3 always sets the 0x8000
  flag, geometry 4 only with a non-default palette; geometry 4 writes z +- 1 back into the mesh, geometry 3 does not; a
  mesh of 3 or fewer vertices (0, 1, 2 included) writes one triangle.

Not reproducible, avoided by the tests (the game data does not reach them):

* rdModel3_LoadText keeps the material names in 0x80 stack slots of 0x400 bytes indexed by the number in the file: an
  index outside 0..0x7f writes past the slots, a hole among 0..count-1 makes rdMaterial_Load read uninitialised stack.
  The C has the same slots in its own frame; the bytes it would read differ.  The test keeps the slots a permutation.
* rdCache_DrawMeshList3D keeps the mip level and the last vertex colour in stack slots it never initialises: the first
  textured mesh with a texture type outside 1-4 uses a garbage mip level, and geometry 3 + lighting 3 + G 0x0090004c on
  the very first vertex uses a garbage colour.  The C starts both at 0; the test avoids these two first cases (later
  meshes do use the carried-over values, as in the original).

## Differential tests

`build/difftest/asm_q3/run_all.sh [cases] [model cases]` (default 1,000,000 each; needs a linked build for
`data_s.o`; extracts the text .3do files from `$GRIMDATA` into `out/3do` on the first run, read only).

* puppet_test.c: random puppets / animations / joints in an arena; frame counts 0, small, >= 2^31 and not
  representable as floats (the quotient's rounding), dt landing on the count or a multiple, marker ties with the old
  and new time, NaN / inf / denormal / signalling NaN times and weights, every rounding mode in DAT_00900526; the marker
  callback stand-in sometimes changes the track's times, the marker count, the animation or the callback;
  Math_NormalizeAngle180 returns extended values; the x87 precision control 24 / 53 / 64 rotates.
* model_test.c: the ten text .3do files of the game data (DATA*.LAB: "# MODEL" files) with random mutations: lines
  deleted, duplicated, swapped, truncated, junk, the shadow line dropped, numbers replaced (0, -1, the 0x18 / 0x200 /
  0x300 / 0x80 limits and neighbours, large values, floats, words), material lines permuted, the 0x80-material assertion;
  plus a failing allocation, a failing rdMaterial_Load, a failing open.  stdConffile_ReadLine lower-cases and skips
  comments; sscanf / strtok / atoi / strncpy forward to msvcrt and log their arguments; the allocator logs size, file
  and line.  About 0.8 ms per case; 1,000,000 cases.
* cache_test.c: up to 8 cache entries with random geometry / lighting modes around the limits, cels, textures with and
  without flag 0x8, texture types and distances on 10 / 20 / 40, default and other palettes (factors overflowing 255),
  z = 0 / -0 / +-1 / NaN, x / y on halves, light levels on 0 / 1 / the floor, tiny negatives and NaN, tints, channel
  masks, global scale, small batch capacities (flushes), a failing rdMaterial_Ensure (both retries); Begin3DBatch
  sometimes resets the vertex count (so the retry path's stale base shows).
* mutate.py: 26 puppet, 17 model, 25 cache mutations (rounding points, compare kinds and NaN directions, operand
  order, dword vs FPU copies, re-reads after callbacks, limits, line numbers, loop counts): all reported.  Dropped as
  equivalent (cannot be seen): the extended vs float operand of the first / second light clamp compares and the 255
  product of a float, the float r/2 of the tints (r/2 of a normal float is exact), the one-triangle path for exactly 3
  vertices (the fan of 3 writes the same triangle); the association of the tint sums changes a tint by one ulp that the
  truncated colour products practically never show.

Results (`run_all.sh`, default counts):

```
== C at -O0 (the build's default)
rdPuppet_AdvanceTrack             1000000 cases, 0 differences, 0 NaN-payload-only
rdPuppet_UpdateFrame              1000000 cases, 0 differences, 0 NaN-payload-only
rdPuppet_AdvanceTrack              250000 cases, 0 differences, 0 NaN-payload-only
rdPuppet_UpdateFrame               250000 cases, 0 differences, 0 NaN-payload-only
rdModel3_LoadText                 1000000 cases (312612 loaded, 687388 rejected), 0 differences; 10 files
rdCache_DrawMeshList3D            1000000 cases (68672 returned 0), 0 differences, 0 NaN-payload-only
rdCache_DrawMeshList3D             250000 cases (17235 returned 0), 0 differences, 0 NaN-payload-only
== C with the build/link.py flags (the object that is linked into the game)
rdPuppet_AdvanceTrack             1000000 cases, 0 differences, 0 NaN-payload-only
rdPuppet_UpdateFrame              1000000 cases, 0 differences, 0 NaN-payload-only
rdModel3_LoadText                 1000000 cases (312612 loaded, 687388 rejected), 0 differences; 10 files
rdCache_DrawMeshList3D            1000000 cases (68672 returned 0), 0 differences, 0 NaN-payload-only
== C at -O2
rdPuppet_AdvanceTrack              250000 cases, 0 differences, 0 NaN-payload-only
rdPuppet_UpdateFrame               250000 cases, 0 differences, 0 NaN-payload-only
rdModel3_LoadText                  250000 cases (78054 loaded, 171946 rejected), 0 differences; 10 files
rdCache_DrawMeshList3D             250000 cases (17235 returned 0), 0 differences, 0 NaN-payload-only
== mutations
0 of 26 mutations missed
0 of 17 mutations missed
0 of 25 mutations missed
```

## Clean-room tests and build

* `rm -f src/*/*.[ch] src/*/*.md && python -I tools/build_src.py && make -C build -j8 && make -C build link`: all
  linked (GRIMFANDANGO.EXE 180 objects).
* `cd grim_tools/cleanroom && GRIM_DECOMP=<the four binaries> run.py decomp`:
  with the two puppet functions and rdModel3_LoadText as C: `0 of 5107 tests differ, 0 are close (within 0.001), 5107 the same`;
  with all four as C (the committed state): `0 of 5107 tests differ, 0 are close (within 0.001), 5107 the same`.
* `python -I build/perf/libcheck.py <the four binaries> asmq3 --data <private copy of GRIMDATA>`: lua hook, boot to
  Manny's office, Lua probes, save / load round trip, no Lua errors, process alive: all PASS (no baseline comparison).
* build_src.py rewrites the "NOT COMPILED" line above the four functions' Ghidra text in src/GRIMFANDANGO.EXE/rdpuppet.c,
  rdmodel3.c, rdcache.c and changes stddisplay.c (FTOL); those generated changes are not committed.

## Left assembled

None of the four.
