# Grim Fandango (GOG v1.01) source reconstruction

A decompiled, symbol-named reconstruction of `GRIMFANDANGO.EXE` v1.01 and its
three engine DLLs (`LUA.DLL`, `IMUSE.DLL`, `CHORE.DLL`), produced from the Ghidra
project `grim` through the ghidra-mcp bridge. It is *not* compilable source: it
is Ghidra's C output with original-style names, prototypes and comments, grouped
into files that follow the original module layout.

The Ghidra project is the system of record. Every name, prototype, struct and
plate comment lives there; this tree is regenerated from it.

**The rebuilt executable runs the real game** (boots to Manny's office, walks, dialogue, inventory, movies, save/load).
To learn the code and change the game - build/run loop, how the game finds its Lua scripts and data (loose files
override `.LAB` contents), how to add a Lua API function, a subsystem map and three worked example mods -
read **[docs/MODDING.md](docs/MODDING.md)**; the 319 Lua functions the engine registers are in
[docs/LUA_API.md](docs/LUA_API.md).

## Layout

| Path | Contents |
|---|---|
| `names/*.json` | Curated symbol batches (functions, prototypes, globals, comments, tags). Re-applying is idempotent. |
| `tools/apply_names.py` | Applies one or more batches to Ghidra over the HTTP bridge (`127.0.0.1:8089`). |
| `tools/export_raw.py` | Full dump of every function's decompilation plus imports/exports/strings/segments/globals into `raw/<program>/`. |
| `tools/export_changed.py` | Incremental dump: only the functions the journaled Ghidra edits invalidated. |
| `tools/build_src.py` | Organises `raw/` into `src/<program>/<module>.c` with `functions.h`, `globals.h`, `imports.h`, `ghidra_types.h`, `FUNCTIONS.md`. |
| `tools/classify_raster.py` | Derives feature-based names for the ~340 RDroid software-rasterizer variants. |
| `tools/gen_dll_module_names.py` | Module-level names for LUA.DLL / IMUSE.DLL internals from their `__FILE__` strings. |
| `tools/gen_dll_crt_names.py` | C runtime names for the DLLs, matched against the EXE runtime. |
| `tools/export_data.py` | Dumps the `.rdata`/`.data` contents of each program into `raw/<prog>/sections/`. |
| `build/` | Makefile, `gendata.py` (data sections with relocations), `link.py`, `compat.h`, shims, `BUILD_NOTES.md`. |
| `tools/stats.py` | Coverage table (below). |
| `tools/lab.py`, `tools/luadump.py`, `tools/list_lua_api.py` | List/extract/pack `.LAB` archives; dump precompiled Lua 3.1 scripts; list the Lua API (`docs/LUA_API.md`). |
| `tools/run_game.sh`, `tools/lua_cmd.sh`, `tools/grim_shot.ps1`, `tools/mkmoddir.sh` | Start the rebuilt game with the test knobs, run Lua in it, screenshot it, create a mod directory. |
| `mods/` | Example mods (loose-file scripts and set files; the C examples live in `build/overrides.c`). |
| `raw/` | Regenerable dump. `raw/exe_source_spans.json` maps address ranges to the original source files. |
| `src/` | Regenerable organised tree. |

## Regenerating

```bash
python -I tools/apply_names.py names/*.json      # only after editing a batch
python -I tools/export_changed.py                # re-decompiles only what the edits invalidated
python -I tools/build_src.py
python -I tools/stats.py
```

`tools/ghidra_api.py` journals every write (rename, prototype, comment,
label, created function) in `raw/touched.json`; `export_changed.py` re-exports
those functions plus everything that references them (callers, users of a
global, callers of an import through its import-table slot) and functions that
are new since the last export, then clears the journal. `export_raw.py` is the
full export (about 20 minutes for all four programs); `export_changed.py
--full` forces it, and a struct-layout change triggers it automatically.

The bridge's write endpoints act on Ghidra's *current* program; the scripts
switch it explicitly (`ghidra_api.ensure_current`).

## Building

The tree compiles and links with the MSYS2 toolchain (UCRT64 `gcc -m32` for
objects, the i686 gcc for linking). See `build/BUILD_NOTES.md` for details and
`docs/MODDING.md` for the edit-build-run loop.

```bash
rm -f src/*/*.[ch] src/*/*.md && python -I tools/build_src.py && make -C build -j8   # objects + summary
# keep src/<prog>/asm_funcs.s: build_src.py does not write it, tools/gen_asm.py does (needs the Ghidra bridge)
make -C build link                                                 # link all four
```

All four programs compile and link; the link uses the real section contents dumped from Ghidra
(`tools/export_data.py`, `build/gendata.py`: labels at the original offsets, relocations for every pointer into the
image) and the real Win32/DirectX import libraries (`build/stdcall_names.json`). No function of the four programs is built from the original machine code any more (since 2026-11-09;
`tools/gen_asm.py` and the empty `src/<prog>/asm_funcs.s` remain for the method): everything, the software rasteriser
included, is compiled C (much of
it hand-written in `build/overrides*.c` where Ghidra's C is wrong about x87 results, register calling conventions and
lost arguments), verified against the original machine code by differential tests and the clean-room tests
(`grim_tools/cleanroom`, `run.py decomp`: all 5167 the same as the original). The result is playable. What is still stubbed:
11 MSVC runtime helpers (the host runtime replaces them) in the EXE.

## What the binary tells us about the original source

The engine allocator and assert service receive `__FILE__`/`__LINE__`, so the
original file names survive. Engine ("sput", LucasArts' GrimE) sources under
`C:\grimsrc\libs\grimlib\`: `Main/sputmain.cpp`, `sputresource.cpp`,
`Engine/sputRender.cpp`, `sputActor.cpp`, `sputCostume.cpp`, `sputRoom.cpp`,
`WalkPlane.cpp`, `ObjectState.cpp`, `polyglot.c`, `Scripts/sputLua.cpp`,
`Win95/grimplat.cpp`, `Temp/Res.c`, `Temp/Text.c`, `Memory.c`, `Fileutil.c`,
`grimdemo.c`. Shared Jedi Knight-era libraries under `C:\grimjedi\Libs\`:
`RDroid` (Rdcamera, Rdcolormap, Rdmaterial, Rdpuppet, Rdthing, Rdsprite,
Rdcanvas, the software rasterizer and clipper), `Std` (Stddisplay, Stdbitmap,
Stdbmp, Stdgif, Stdpcx, Stdlbm, Stdmemory, Stdfileutil) and `W32Util`.
Third-party code: Lua 3.1 (modified with "tasks"), zlib 1.1.3 (save games),
the INSANE/SMUSH movie player through the LecShare module registry, HMI SOS
audio hooks, and the MSVC 6 C runtime.

Key structures are documented in plate comments on their constructors
(Actor 0xa8, ActorExtra 0x4a0, costume 0xb4, set/setup, ResRecord/ResRef,
text object 0x260, ObjectState 0xfc, GrimServices 0x70, cached mesh 0x78,
puppet track 0x134).

## Naming conventions

* `Module_Verb` for engine and library functions (`Actor_SetRot`,
  `rdCache_Flush`, `stdGif_LzwDecodeNext`, `D3D_CreateTexture`).
* Globals carry the bridge's Hungarian prefixes: `g_p…`, `g_n…`, `g_dw…`,
  `g_fl…`, `g_sz…`.
* `rdRaster_<Role><Bpp>_<Features>[_n]` names are **auto-classified** from the
  decompilation (role: Draw/Select/Edge/EdgeSetup/Span/SpanP/SpanR/Grad;
  features: Tex/Flat, Lit, Key, Z/Zw). Treat the suffix as a strong hint, not
  a verified fact; each has a plate comment saying so and the tag `auto`.
* `<module>__<addr>` names in LUA.DLL and IMUSE.DLL (`llex__6b10`,
  `iMUSE_Dispatch__2040`) mean "in this original file, identity still open".
  Functions whose identity is clear carry their Lua 3.1 / iMUSE names
  (`luaV_execute`, `luaY_syntaxerror`, `Im_RefillStreamTrack`).

## Coverage

Output of `tools/stats.py` (regenerate after changes):

| Program | Functions | Named | of which auto/module-level | Unnamed (FUN_) |
|---|---|---|---|---|
| GRIMFANDANGO.EXE | 2671 | 2344 | 378 | 327 |
| LUA.DLL | 852 | 689 | 43 | 163 |
| IMUSE.DLL | 451 | 301 | 28 | 150 |
| CHORE.DLL | 264 | 112 | 0 | 152 (all of them dead MSVC runtime copies) |

Files in src/: 214

## Known gaps

* The MSVC 6 C runtime linked into the EXE and both DLLs is named by matching
  each function's structure against the known runtime layout (`_output`,
  `__sbh_alloc_block`, `_getptd`, ...). About 30 small helpers (floating-point
  conversion internals, C++ exception-handling thunks) are still `FUN_`.
* Lua 3.1 internals carry their original names where the identity is clear
  (`luaD_call`, `luaH_set`, `luaV_settable`, `luaU_LoadFunction`); the rest
  keep `<module>__<addr>` names. The same holds for iMUSE (`Im_FadesHeartbeat`,
  `Im_DispatchCommand`, `Im_FireTriggers`), where several names are inferred
  from call structure rather than strings and say so in their comments.
* Rasterizer variant suffixes and the clipper vertex-attribute sets are
  inferred, not verified pixel-by-pixel.
* LUA.DLL grew from 436 to 690 functions when the exported entry points were
  defined; the new ones are the Lua io/string libraries and more C runtime,
  now named, apart from ~100 small runtime fragments (x87 helpers, locale
  tables, exception-handling thunks).
* Original names from the remaster's unstripped Linux build (`GrimFandango`,
  `libLua.so`) replace FUN_ and guessed names where the match is clear
  (docs/notes/orig_names.md): the Lua bindings are `sputLua_*`, LUA.DLL's VM
  is `ExecutionState_CrunchOpcodes`, ... Each renamed function's plate comment
  says "was X". Globals too: EXE 590 of 2274 named, LUA.DLL 69 of 367,
  IMUSE.DLL 92 of 366 (docs/notes/orig_globals.md, orig_3.md). The generated
  `rdRaster_*` names are not done yet.
* CHORE.DLL is fully named (names from the remaster's unstripped `libchore.so`,
  docs/notes/chore_naming.md) and its costume / chore / key records are typed;
  the 152 `FUN_` left are dead copies of the C runtime.
* Struct types are applied only where a batch set a prototype; most parameters
  are still Ghidra's inferred `int`/`undefined4`.
