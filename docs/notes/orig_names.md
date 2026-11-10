# orig-names: original function names from the remaster's Linux binaries (branch `orig-names`, 2026-11-10)

## Sources

* `/linux/libLua.so` (`C:\GOG Games\Grim Fandango Remastered\libLua.so`): the remaster's Lua 3.1, built with gcc as
  C++ (`lstate.cpp`, `lvm.cpp`, ... in its assert paths). Matched against `/LUA.DLL`.
* `/linux/GrimFandango`: the remaster's engine with iMUSE linked in. Matched against `/v101/GRIMFANDANGO.EXE` and
  `/v101/IMUSE.DLL`. Much of it is new (the `zg_*` platform layer, the OpenGL renderer, theora, stb, Steam); those
  names were never used.
* The names come from the ELF `.symtab` (read directly from the files, demangled to `Class::Method`), not from
  Ghidra's function list: Ghidra often starts the PIC functions of libLua.so 5 bytes late and calls the first
  bytes a thunk, so its names are partly `FUN_` there.

## Method

`tools/orig_dump.py` dumps a program through the bridge (functions, call-graph edges, decompiled text: the Linux ones
in full, the v1.01 ones use `raw/<prog>/functions`), `tools/orig_match.py` pairs functions and writes candidates with
their evidence:

* anchors: the same (non-generated) name on both sides;
* `{name, function}` tables in the data: the Lua registration tables (int_funcs, iolib, strlib, mathlib, the
  fallbacks, the EXE's Lua function tables) and the EXE's module table (`sputRoom_Initialize`, ...). Each run of
  alternating string / function pointers is a table; its first word gives the order of the pairs (the EXE module
  table is `{function, name}`, the Lua tables `{name, function}`);
* strings / asserts referenced by exactly one function on each side (the v1.01 `s_*_ADDR` / `0x` / `DAT_` operands
  are read from the section dumps, the Linux ones from the ELF);
* call-graph propagation: for a matched pair, the only unmatched callee (caller) on each side, kept when the matched
  neighbours agree.

Every candidate was then reviewed by hand (code of both sides via a scratch viewer, sizes, callees): gcc inlined
many statics, so a string often sits in a different function on the Linux side (rejected: e.g. `luaU_LoadCode ->
LoadFunction`, `Actor_SayLine -> zg_TryOpenfile`, `Lab_ReadDirectory -> Res_FileOpen`). The reviewed lists became
`<addr> <name> <evidence>` specs, `tools/orig_batch.py` turned them into the batches (plate comment: the existing
comment + "Original name X (source: evidence); was Y.", the old name in `"old"`), then the usual
`apply_names.py` -> `export_changed.py`, and `tools/rename_refs.py` carried old -> new into build/*.c,
build/cleanroom/*.c, the other names/*.json batches, tools/*.py, build/*.py and docs/*.md (one pass per batch, so
swaps and chains work; it respects the `#ifdef GRIM_*` guards for the shared FUN_1000xxxx names).

Naming rules:
* the remaster's name as is when it is unique there and in the target (`nextvar`, `match`, `sputLua_TurnActorL`,
  `grimlib_SetPause`, `MeshRequester`);
* C++ methods `Class::Method` -> `Class_Method`, constructors / destructors `Class_Construct` / `Class_Destruct`,
  operator new / delete `Class_New` / `Class_Delete` (`LState_SerialToPtr`, `ExecutionState_CrunchOpcodes`,
  `WalkPlane_JumpOut`, `Puck_SetPos`, `ObjectState_MoveToBack`); the v1.01 LUA.DLL is C++ too (`__thiscall` LState
  and ExecutionState methods, `lstate.cpp` asserts);
* statics that exist several times in the remaster get the module as prefix, like the `Cos_` forms of the chore
  round: the twelve LEC module `module_startup`s -> `AnimPlay_module_startup`, `Zfile_module_startup`,
  `Blocky16_module_startup`, ...; `Zfile_fle_Open`; the iMUSE music-script statics the bridge refuses bare
  -> `Script_SetSequence`, `Script_Trans`, `Script_Callback`;
* exports, the MSVC runtime and zlib are not renamed.
* `names/orig_modules.json` pins every renamed function to the module file it was in (tools/build_src.py reads it
  before the prefix rules), so lowercase names (`next`, `insert`, `setloc`) do not fall into crt.c and the source
  files keep their contents.

## Batches and counts (`python -I tools/stats.py`)

| program | batch | renames | of which FUN_ | `<module>__<addr>` | existing names replaced |
|---|---|---|---|---|---|
| LUA.DLL | names/orig_lua.json | 158 | 66 | 60 | 32 |
| GRIMFANDANGO.EXE | names/orig_exe_lua.json (Lua bindings, by the registration tables) | 265 | 0 | 0 | 265 |
| GRIMFANDANGO.EXE | names/orig_exe_engine.json | 190 | 15 | 0 | 175 |
| IMUSE.DLL | names/orig_imuse.json | 12 | 7 | 0 | 5 |

| program | named before | after | FUN_ before | after |
|---|---|---|---|---|
| GRIMFANDANGO.EXE | 2319 | 2334 | 352 | 337 |
| LUA.DLL | 623 | 689 | 229 | 163 |
| IMUSE.DLL | 285 | 292 | 166 | 159 |

LUA.DLL: every FUN_ of the Lua code (below 0x1000ef80) is named now; the 163 left are the MSVC runtime. The
generated `<module>__<addr>` names went from 123 to 63 (the rest are Lua 3.1 statics that gcc inlined, so the
remaster has no symbol for them). The EXE has no `<module>__<addr>` names; of its 337 FUN_ 300 are in the runtime / LEC library range
(0x4ac540..0x4d61ff, 171 of them dead runtime copies of names/lib_replace.json) and 37 elsewhere; 15 FUN_ were named here. The old names are in each plate comment ("was X") and in the batches' `"old"`.

Renames of existing LUA.DLL names worth knowing (the earlier guesses were wrong, the remaster shows the function):
`luaU_str2number` -> `luaV_tonumber`, `lundump__d620` -> `luaV_tostring` (lvm.obj starts there, as lvm.c does),
`luaH_new` -> `luaH_load`, `luaH_init` -> `luaH_new`, `ltable__c190` -> `luaH_free` (the old `luaH_free` is Lua 3.1's
`hashnodecreate`, now `luaH_hashnodecreate`), `luaT_checktag` / `luaT_realtag` swapped, `luaC_closuremark` ->
`hashmark`, `luaC_protomark` -> `closuremark` (and the old `luaC_hashmark`, Lua 3.1's protomark, -> `luaC_protomark`),
`luaS_hash` -> `luaS_createudata`, `luaX_save` -> `luaX_lasttoken`, `luaX_inclinenumber` -> `skipspace`,
`luaX_pragma` -> `inclinenumber`, `luaX_error` -> `checkcond`, `luaY_code_word` -> `luaY_codedebugline`,
`yyparse` -> `luaY_parse`, `luaX_lex` -> `luaY_lex`, `luaV_execute` -> `ExecutionState_CrunchOpcodes`,
`lua_initstate` -> `LState_initglobals`. In the EXE e.g. `Sector_IntersectSegment` -> `sputLua_CollisionHandler`
(it calls the Lua `collisionHandler`), `Movie_SetFile` -> `sputSmush_GetMovieLength`, `rdPolyline_New` / `_Init` ->
`rdSprite_New` / `rdSprite_NewEntry` (0xb8-byte record, rdSprite.c in the remaster's assert path),
`deflateParams_or_SetDictionary` -> `fle_zfilio_config` (not zlib), `Render_GetFrameCounter` ->
`sputActor_GetNumActorsTalking`. Full lists: the batches.

## Left out (doubtful)

Rejected candidates (inlined on the Linux side, platform rewrites, too little evidence): Win_WinMain, Display_Select
(Main_Startup), Grim_Init, Lab_ReadDirectory, Resource_OpenArchivesInDir, Actor_SayLine, Actor_DrawShadowPlane,
Costume_SaveChoreListFile (sputCostume_SaveHook?), SetFile_ParseSections, SetFile_ParseSectors
(WalkPlane::ParseCollection), LightEd_WriteLightsSection, LightEd_ReadControl, rdModel3_New (ModelHandler?),
rdThing_DrawAlt, Display_SetPalette3D, Math_SinDeg (stdMath_Tan?), Res_Register (Res_SysAddHandle?),
Actor_CreateSubtitle, Walker_ReplanPath, Collision_TestActorAgainstOthers, LecShare_StartupModules / _Reset,
SoundModule_Open, the zlib and runtime pairs, Im_VimaDecompress.

Not done in this round:
* globals (the remaster has them: `pLuaHS`, `lua_totalBytesSaved`, `LState::refArray`, ...; renaming DAT_ globals
  also means the overrides' DAT_ uses);
* the software rasteriser (`rdRaster_*`, 351 generated names; the remaster has `rdNRaster_*` / `rdZRaster_*` /
  `rdAFRaster_*`, matching them needs the dispatch tables);
* most of IMUSE.DLL's internals (92 of its functions pair up; the remaster's iMUSE is mostly a different build).

## Build notes

* `build_src.fix_stdcall` looked for the function name anywhere in the head, so a plate comment with `Name (` got
  the `__stdcall` (LState_* prototypes lost it); it now only looks after the comment.
* One call is cast now where it was not: `((code *)rdModel3_DrawMeshImpl)(...)` in rdModel3_Draw (Ghidra wraps the
  longer name as `F\n (args)\n ;`, which `call_is_statement` does not take for a statement). Pointer arguments,
  cdecl: the same code.
* Ghidra names pointer labels after their function: `PTR_FUN_004f12f0` -> `PTR_anm_EasyPlay_004f12f0`,
  `PTR_FUN_004f1d08` -> `PTR_Zfile_fle_Open_004f1d08` (data symbol names only).
* build/overrides_exe.c declares `__asm__("_ShrinkBoxes")`; rename_refs now also renames `"_Name"` asm labels.
* export_changed.py did not re-export IMUSE.DLL's module-interface filler 0x100078d0, which stores
  `sounds_startup` / `sounds_shutdown` into the interface (no xref from that store); it was re-exported by putting its
  address into raw/touched.json. A check over raw/<prog>/functions (code without comments) found no other old name.
* IMUSE: the bridge refuses the bare `SetSequence` (token collision with `ImSetSequence`), `Trans` and `Callback`
  (single token), hence the `Script_` forms; the comments before the guard in build/overrides_imuse_r1.c and
  names/imuse_asm_reasons.json (shared FUN_1000xxxx name, not renamed by rename_refs) were renamed by hand.

## Checks

Per program: the regenerated src identical to the previous one after mapping old -> new and dropping comments
(scratchpad `cmpsrc.py`, whitespace-insensitive; differences only the items above), all four LINKED, stubs.txt
EXE 42, LUA 58, IMUSE 9, CHORE 16.

Clean-room (`run.py decomp`):
* LUA.DLL batch: 0 of 5118 tests differ, 5118 the same.
* GRIMFANDANGO.EXE batches (with LUA.DLL): 0 of 5118 tests differ, 5118 the same.
* IMUSE.DLL batch (final build, all three batches): 0 of 5118 tests differ, 5118 the same.
