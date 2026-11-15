# Where the reconstruction stands (2026-11-15)

A one-page summary; build/BUILD_NOTES.md has the history and the details of every step.

## What is true

* **All four programs build from the tracked tree** (`src/`, `build/`): no original machine code, no `raw/` at build
  time. CI builds them and runs the clean-room tests on every pull request.
* **They match the original.** grim_tools' clean-room tests (`run.py decomp`): 5490 of 5490 the same. The whole game
  plays through on them (grim_tools' autorun, chapters 1 to 65, `grimW_work/wg_start.sh`).
* **Names.** Every function of the game, LEC and engine code is named; the `FUN_` left are C runtime (most of it dead,
  kept out of the build). Coverage table: README.md.
* **Generated code.** Everything is Ghidra's C except 526 hand-written functions, each listed with the reason in
  docs/OVERRIDES.md:

  | Why it stays hand-written | Count |
  |---|---|
  | The rasteriser's span fillers: the original switches the x87 control word part-way through a span (24-bit truncation); kept on purpose, differentially tested | 363 |
  | A recorded reason: a twin test result, a deliberate fix, a hook, a decompiler limit (names/override_reasons.json) | 74 |
  | x87-exact ports (rounding to float through memory, FCOMP compares, values left in ST0) | 66 |
  | The build's own hooks (GRIM_SIMTIME, the debug log, host file handling) | 10 |
  | asm() blocks (register conventions C cannot declare) | 14 |

* **Parameters.** Named in the prototypes, from the calls (tools/propagate_params.py), the hand-written definitions
  (tools/names_from_overrides.py), the Lua 3.1 sources and what each function does with them (names/params_*.py,
  tools/names_batch.py); a naming round leaves the four programs' .text byte-identical.
* **Types.** The engine's records are typed (actors, costumes, sets, walk sectors, the renderer, text, resources,
  Lua's objects, states, call frames and parser). Raw `((int)p + 0x..)` accesses: EXE 76, LUA.DLL 0, a few byte
  streams in IMUSE.DLL; what is left in the EXE is data whose type is only known at run time (resource data by fourcc,
  costume instance data), name buffers and the C runtime.

## How a change is checked

1. `python -I tools/export_changed.py`, `python -I tools/build_src.py`, `make -C build -j8 && make -C build link`.
2. The clean-room tests on the four built programs (`run.py decomp`): 0 differences is the bar.
3. For a function whose hand-written version is replaced by generated code: `build/mixdiff/twin.sh` runs the
   existing differential test of build/mixdiff or build/difftest against the generated twin and the original machine
   code.
4. For data: `python -I build/datacmp.py OLD NEW` (0 differences, the layout pinned).

## What is left

* **Parameters.** In live game code 81 `param_N` are left (EXE 48, LUA.DLL 9, IMUSE.DLL 24): names that collide
  with a local, custom-storage functions (which a parameter edit would turn into __cdecl) and `undefined **`
  parameters the bridge will not retype. The rest of the `param_N` in the prototypes (EXE 1059, LUA.DLL 745,
  IMUSE.DLL 314, CHORE.DLL 259 in all) are the C runtime, most of it dead.
* **Data.** Untyped initialised bytes: EXE 39,299 (the C runtime's tables, the PE import directory, DirectInput's data
  formats, a constant pool of floats, doubles and GUIDs), LUA.DLL 16,286, IMUSE.DLL 19,399, CHORE.DLL 14,236.
  `DATAGEN_TOP=n python -I tools/datagen.py report PROG` lists the largest spans.
* **Not planned:** generating the 363 rasteriser span fillers (see above), and dropping the x87 exactness: the
  rasteriser test shows the difference is small (about 13,000 colour bytes in 1.5 million random spans without the
  precision switch), but the clean-room tests compare exactly and would lose their meaning.
