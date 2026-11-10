# orig-3: what the remaster's symbols can still name (branch `orig-3`, 2026-11-10)

Third round after [orig_names.md](orig_names.md) and [orig_globals.md](orig_globals.md): more functions and globals of
GRIMFANDANGO.EXE and IMUSE.DLL from the remaster's unstripped `GrimFandango` (Linux), Lua 3.1 source names for the
statics of LUA.DLL that gcc inlined in `libLua.so`, corrections of earlier names the new matches contradict, and the
renames of all three rounds carried into build/difftest.

## Method

* **Anchored alignment of the paired functions** (scratchpad `o3/galign2.py`, an extension of the previous round's
  `galign.py`). Both decompilations are tokenised as before; paired functions and already matched globals keep their
  identity in the token streams (`F<remaster address>`, `G=<symbol>`), unpaired ones are generic (`F?`, `G`). The
  diff of each pair then votes for globals *and* for functions: an unpaired v1.01 callee in a matching block against
  an unpaired remaster callee. Every pair found is fed back as an anchor and the alignment rerun until nothing new
  turns up (EXE: 670 pairs -> 993 after four rounds; IMUSE: 95 -> 187).
* **Every function candidate was checked by hand**, from the call skeletons of the caller pairs (the call lines of both
  sides with the condition above them, scratchpad `o3/skel.py`), body similarity of the pair (difflib ratio of the
  anchored token streams; median of the known pairs 0.62) and callee agreement. The positional vote is wrong where a
  branch is inverted or where two similar calls are adjacent: all ten rdClip_Face3* votes were wrong (perspective and
  ortho swapped, the S/T variants crossed) and were set from the `rdPrimit3_ClipFace` switch instead; Matrix_BuildTransform2
  / Matrix_BuildTranslation2 / Matrix_BuildRotation, ResFile_Printf and the costume tag handlers likewise came from the
  structure, not from the vote. Strong structural evidence used directly: module interfaces filled slot by slot
  (`*_SysInitialize`, `sputX_Initialize`: Initialize / Terminate / Startup / Shutdown / Save / Restore), the
  file-services table of `Res_OverrideFileCalls`, the costume tag registrations of `sputCostume_Startup`
  (changer / requester / freer / stopper / adjuster / instancer / instance save-load per tag), the `ImSoundCall` command
  switch (case 0..0x1d in both builds).
* Rejected after the look: empty functions the compiler shares (`Mem_DumpLog`, `Lua_Stub`, `CostumeTag_Nop` sit in
  several slots), zlib (`SaveFile_Open` is gzopen), the `timeGetTime` import thunk, platform rewrites (`zg_*`), and
  every vote the code contradicts (Resource_RegisterTypes, Res_RestoreFileServices, Lab_FindEntry, stdConffile_Pop,
  Engine_SaveGame, Set_DrawDebugLights, Actor_UpdateMovement, Config_GetPath, Im_DecodeSoundBlock, Im_DispatchFetchNext,
  Im_RunTriggerCommand, Im_SoundsPrepare, the two query_music_stream callers).
* Remaster stubs that share an address: only `std3D_AddRenderListVertices` / `std3D_DrawRenderList` (checked for every
  pair against the ELF .symtab); `D3D_AddVertices` / `D3D_ExecuteBuffer` were told apart by their arguments.
* Globals: the same votes, accepted as in the previous round (all votes agree, or >= 2 and 3x the next, the symbol's
  own best match), each one looked at in both texts (scratchpad `o3/gctx.py`, the v1.01 line and the remaster line).
  Struct fields: only bases whose fields agree on one base address and that the code references were named
  (`privateData`, `rdroid_curColorEffects` (40 bytes, rdroid_curOcclusionMethod follows at +40 as in the remaster),
  `rdColormap_colorInfo`, `activeEdgeHead`); the +n pieces stay as Ghidra shows them.
* LUA.DLL: the 63 generated `l<module>__<addr>` names against the Lua 3.1 sources (lapi.c, lbuiltin.c, ldo.c, lgc.c,
  llex.c, lstring.c, ltable.c, ltm.c, lundump.c, lua.stx): structure, callers and the error strings. Plate comment
  "Named X (not in the remaster, gcc inlined it there): Lua 3.1 source name (...)".
* Names that the bridge refuses bare: `Subscribe` -> LecShare_Subscribe, `MxMix` -> Mixer_MxMix (token subset of
  MxBeginMix), `LoadData` -> Stream_LoadData (weak noun), `LoadString` -> Undump_LoadString (beside LoadTString); the
  plate comment gives the original.

## Batches and counts

| program | batch | renames | of which FUN_ | `<module>__<addr>` | existing names replaced |
|---|---|---|---|---|---|
| GRIMFANDANGO.EXE | names/orig3_exe_funcs.json | 325 | 6 | 0 | 319 |
| GRIMFANDANGO.EXE | names/orig3_exe_globals.json (globals) | 127 | | | 0 |
| IMUSE.DLL | names/orig3_imuse_funcs.json | 92 | 8 | 24 | 60 |
| IMUSE.DLL | names/orig3_imuse_globals.json (globals) | 41 | | | 0 |
| LUA.DLL | names/orig3_lua_funcs.json | 62 | 0 | 55 | 7 |

Functions (`python -I tools/stats.py`):

| program | named before | after | FUN_ before | after |
|---|---|---|---|---|
| GRIMFANDANGO.EXE | 2338 | 2344 | 333 | 327 |
| LUA.DLL | 689 | 689 (Lua `l*__` names 63 -> 8) | 163 | 163 |
| IMUSE.DLL | 293 | 301 | 158 | 150 |

Globals referenced by the decompiled code (as in orig_globals.md, scratchpad `gcount.py`):

| program | globals | named before | after | DAT_/PTR_/UINT_ before | after |
|---|---|---|---|---|---|
| GRIMFANDANGO.EXE | 2274 | 463 | 590 | 1811 | 1684 |
| IMUSE.DLL | 366 | 51 | 92 | 315 | 274 |
| LUA.DLL | 367 | 69 | 69 | 298 | 298 |

The EXE renames are mostly hand-made names replaced by the originals, e.g. the module interfaces (`sputX_Start` /
`_Stop` / `_SaveState` -> `sputX_Startup` / `_Shutdown` / `_Save`, `Memory_Sys_*`, `FileUtil_Sys_*`,
`Resource_Filio_*` -> `Res_Sys*`, `TextModule_*` -> `Text_Sys*`, `PlatModule_*` -> `Graph_Sys*`), the Jedi
libraries (`Matrix_*` / `Angles_*` / `Vec3_*` -> `rdMatrix_*` / `rdVector_*`, `Surface_*` -> `stdDisplay_VBuffer*`,
`rdCanvas_*` (the occlusion scan converter) -> `rdActive_*`, `rdCache_DrawMesh*` -> `rdCache_DrawFace*`,
`D3D_*` -> `std3D_*`), the resource layer (`ResFile_*` -> `Res_F*`, `Pool_*` -> `Memory_*Pool` / `_AllocFixed`),
Smush, the costume tag handlers (`MeshComponent_OnKey` -> MeshChanger, ...), the registry (`Reg_*` -> `wuRegistry_*`).
Some old names were wrong in substance: `Math_SinDeg` is stdMath_Tan (the second table, quadrant signs of a tangent),
`Vec3_Copy` is rdMatrix_TransformVector34, `Matrix_BuildTranslation2` builds a scale (rdMatrix_BuildScale34),
`Matrix_BuildRotation` is rdMatrix_PreMultiply34, `Engine_RunShutdownHooks` is sputControl_Update, `Input_Init` is
stdControl_Startup, `Res_DataFromHandle` is Res_HandleFromSerialNumber, `Im_FindTrack` is StGetValidSize.

IMUSE.DLL: the internal modules of iMUSE now carry their own prefixes: Dp* (dispatch), Dw* (wave driver), Fd* (fades),
Fm* (file manager), Gr* (groups), Mx* (mixer), St* (streams), Tg* (triggers), Tr* (tracks), Ut* (lists), iRes_*,
ihost_*, sounds_*; `Im_DispatchCommand` is ImSoundCall, `Im_GuardEnter` / `_Leave` are ImWaveHalt / ImWaveProceed
(their counter is wvSlicingHalted).

LUA.DLL corrections with the remaster's symbols: `luaY_error` (msg, token) is luaY_syntaxerror, the old
`luaY_syntaxerror` is close_func, `lparser__a730` is luaY_error; `luaF_freeclosure` is luaF_freeproto (it walks
rootproto), the old `luaF_freeproto` is Lua 3.1's freefunc, `lfunc__4cc0` is luaF_freeclosure (rootcl). Lua 3.1 names
also replace three wrong guesses: `luaY_code_byte` -> check_pc, `luaY_code_opcode_arg` -> code_oparg,
`luaY_growvector` -> luaI_registerlocalvar. Left: lstate__85e0 (Grim's save code), lundump__d030 / d130 / d360 / d380 /
d3c0 (Grim's undump: XOR, byte swaps), lzio__ef20 / ef40 (CRT set-up), and the four `luaY_*` names that are right
apart from the prefix (string_constant, next_constant, code_number, real_constant).

## Settled doubtful candidates of the earlier rounds

Walker_ReplanPath -> sputActor_ActorWalkTo (both callers agree; the remaster inlined the planner), Actor_SayLine ->
sputActor_SayLine, Actor_CreateSubtitle -> sputText_CreateActorText, SetFile_ParseSections -> sputRoom_LoadRoomEntry,
Res_Register -> Res_SysAddHandle, Math_SinDeg -> stdMath_Tan, Engine_UpdateFrame -> grimlib_UpdateManual (the
remaster inlined more into it), the contested globals ClipPlaneActive, numGeoLights, rdColormap_pIdentityMap,
wvSlicingHalted, streamID, aMcmpFileHandles (through the new pairs Renderer_EnableClipPlane, ImWaveHalt, iRes_FREAD).
Still open: Win_WinMain, Display_Select, Grim_Init, Lab_ReadDirectory, Resource_OpenArchivesInDir,
Actor_DrawShadowPlane, Costume_SaveChoreListFile, SetFile_ParseSectors, LightEd_*, rdModel3_New, rdThing_DrawAlt,
Collision_TestActorAgainstOthers, LecShare_StartupModules / _Reset, Im_VimaDecompress, the dirty-rect statics,
loadLastSave, tmFuncs, mlListSize, the remaining struct fields (sou_fill_data, sou_channel, aView, aFile, ...).

## Not done

* The software rasteriser's `rdRaster_*` names stay as they are (as asked). Note for later: the remaster's .symtab does
  have `rdNRaster_*` / `rdZRaster_*` functions, and the alignment paired 86 of them with v1.01 rdRaster functions
  (body similarity about 0.45..0.85), through `rdCache_DrawFaceN` / `_DrawFaceZ`; the many near-identical span
  functions need the dispatch tables to be told apart.
* LUA.DLL globals (no new pairs to align beyond the previous round).

## Build and tools

* tools/rename_refs.py: also renames the ld --wrap symbols `__wrap_X` / `__real_X` of build/cleanroom (cleanroom.c
  wraps Reg_GetFloat etc., which are wuRegistry_* now) and `.def _X` / `.globl _X` lines of __asm__ blocks
  (build/overrides.c defines ImWaveHalt / ImWaveProceed in assembler); `--difftest` processes build/difftest only
  (also `orig_X`).
* build/mixdiff/slice_orig.py: the harnesses cut the original machine code out of baseline assemblies older than the
  renames; a function given under its current name is found under its old names (names/orig*.json) and becomes
  orig_<current name>, and the symbols a slice references under an old name are written with the current one, so the
  slices link against today's objects and data image.
* A plate comment must not contain `*/` (one evidence text had `Tr*/Fd*/` and closed the comment in the generated C;
  fixed before the build).
* export_changed.py did not re-export the module-interface fillers Res_SysInitialize (EXE 0x480010) and IMUSE's
  0x100078d0, nor ImSoundCall and 0x10007130 (computed accesses); they went through raw/touched.json.
* Regenerated src equal to the previous src after mapping old -> new for all four programs (scratchpad `cmpg.py`); the
  only data.s line that differs is a comparison artefact of the chain LecShare_Subscribe -> GetCatalogEntry /
  LecShare_Resolve -> LecShare_Subscribe. All four LINKED, stubs EXE 42, LUA 58, IMUSE 9, CHORE 16. The .text, .data
  and .rdata of the four binaries are byte-identical to main's build (only the build time string, the DLL export
  tables, which list the new names, and the EXE's import hints differ).

## build/difftest

The harnesses were written before all three rounds. tools/orig_history.py writes one batch from the earliest old name
of every renamed address to its current name (1688 renames), and `rename_refs.py --difftest` carried it into
build/difftest (53 files; FUN_100068b0 -> Script_Trans of imuse_r1 / s2, a shared DLL name, by hand). Fixes the renames
needed beyond the text:
* build/mixdiff/slice_orig.py maps current names to the old labels of the baseline assemblies (see above);
* asm_p1/gensyms.py and asm_s2/gensyms.py take the address of a named global from raw/GRIMFANDANGO.EXE/globals.json (a
  renamed DAT_ global no longer carries its address in its name; asm_p1 did not link since the orig-globals round);
* clipface/clip_test.c pasted the rdClip_Face3_* stand-in names with `##` (now rdClip_Face3W ... GTOrtho).

Every harness built and run with 1 case (or its default short run where it has no case count), mutation steps left
out, on main (36f4ca5, worktree) and on this branch:

| harness | main | orig-3 |
|---|---|---|
| asm_p1 | link fails (renamed globals) | builds, 0 differences |
| asm_p2, asm_s2 | fail | build and run |
| clipface, lua_core | crash (stubbed renamed callees) | 0 differences |
| asm_q1, q2, q4, q5, q6, imuse_r1, r2, s2 | ok | ok |
| asm_q3 | rc 1 with 1 case | same |
| asm_s5, big_collision_others, big_engine_renderframe, big_stdpic_loadinto, big_walker_avoid | slice from today's (empty) src/<prog>/asm_funcs.s | same (not a naming problem) |
| s1 | link fails: CHORE globals of the chore round | same |

## Checks

Clean-room (`run.py decomp`): the suite grew from 5167 to 5319 tests during the round (another session saved new,
still uncommitted expected results in grim_tools/cleanroom/expected). Each run of this branch was paired with a run of
main's build (36f4ca5, built in a worktree, same expected files):

| build | result |
|---|---|
| EXE batches only | 1 of 5319 differ (gco_kf_badj), 5318 the same |
| main, run right after | 1 of 5319 differ (gco_kf_badj), 5318 the same |
| final build (all batches), two runs | 2 of 5319 differ (gco_kf_badj, ims_ids id_plus_1), 5317 the same |
| main, run right after | 2 of 5319 differ (gco_kf_badj, ims_ids id_plus_1), 5317 the same |

Both differences are new tests of the other session (gco_kf_badj's expected values are nil; ims_ids|id_plus_1 depends on
which sound has the number id+1) and come out identically with main's build; the .text / .data / .rdata of the four
binaries are byte-identical to main's. No test differs between this branch and main.
