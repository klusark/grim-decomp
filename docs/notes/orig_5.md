# orig-5: the LEC library, the start-up / resource tables, the doubtful list (branch `orig-5`, 2026-11-10)

Fifth round after [orig_names.md](orig_names.md), [orig_globals.md](orig_globals.md), [orig_3.md](orig_3.md) and
[orig_4.md](orig_4.md): the remaining `FUN_` of GRIMFANDANGO.EXE, the generated names, the doubtful lists of the
earlier rounds, the unnamed EXE globals, and whether the remaster's ELF carries type information. Sources as before
(`/linux/GrimFandango`, `/linux/libLua.so`, the ELF `.symtab`). Names and comments only (no types, no prototypes);
exports, the MSVC runtime and zlib untouched.

## Method

* **Function-pointer tables, slot by slot** (scratchpad `o5/tabpair.py`, `o5/gtab.py`). The LEC library (the
  INSANE / SMUSH player) registers its services by name: each `X_module` function calls
  `share_services->Publish("LECMODULE=insane_<x>", module_services)` and `("<SERVICE>=insane_<x>", x_services)`; both
  builds use the same strings. The v1.01 registration (`(s_..., &PTR_...)`) and the remaster's (`("...", sym)`) give the
  two tables; read as pointer arrays from the PE sections and the ELF segments (the remaster table bounded by its symbol
  size, the right `module_services` among the dozen of that name by slot 0 = the registering function), they pair slot
  by slot: memory, stdio (grimio), animplay, animframe (and their DEBUG tables), streamer, directory, zfilio, stdfile,
  wave flobdec, blocky16 flobdec, bitmap, timer, sound, dsnd. The same through matched globals: `shl_modules`
  (the module list), `lecShareServices` (Publish / Unpublish / Subscribe / Unsubscribe), `defaultHostServices`,
  `sputVideoCallBacks`, and the resource type table (`g_ResTypeTable` / `TypesToRegister`, by its four-letter tags).
  A function in two slots (`LecShare_Nop`, `Lua_Stub`, `Svc_Malloc` / `_Free` / `_Realloc` as both `default*` and
  `default*Handle`, `FUN_004cbf40` as flobdec SetVal / GetVal) is a shared or folded copy and keeps its name. Bodies
  were looked at side by side for every pair (scratchpad `o5/tab_review.txt`); remaster stubs (`fle_DirectoryLoad`,
  `fle_Rename` return 0 / write 0xdead) are named by their slot, as orig-4 did for std3D.
* **Propagation from the new pairs** (scratchpad `o5/prop.py`: the only unpaired callee / caller of a pair on both
  sides; `o4/galign3.py` votes rerun with the new pairs as anchors, five iterations): each candidate checked in both
  texts (`o4/pv.py`, `o5/calls.py` call skeletons with the strings resolved, `o5/cg2.py` callers / callees).
* **Globals**: the token-alignment votes of `galign3.py` over 1540 pairs (`o3/gnew2.py`), accepted when unanimous (or
  >= 2 and 3x the next), the symbol's own best match, and the statement agrees in both texts; hand-made `g_` names
  only with a unanimous vote in small functions where the assignment is the same.
* Naming as before: the remaster's name as is when unique; a static several LEC modules have gets the v1.01 module
  prefix already used for that module (`AnimPlay_module_terminate`, `Zfile_fle_Read`, `StdFile_fle_Open`,
  `DWave_flobdec_Info`, `Blocky16_flobdec_DecodeHeader`, `Video_module_shutdown` for the bitmap module,
  `InsaneTimer_` / `SoundModule_` / `DsndDriver_module_*`); the bare one-word `Publish` / `Unpublish` /
  `Unsubscribe` as `LecShare_*` (like `LecShare_Subscribe`; the plate comment gives the original).

## Batches and counts

| program | batch | renames | of which FUN_ | existing names replaced |
|---|---|---|---|---|
| GRIMFANDANGO.EXE | names/orig5_exe_funcs.json | 212 | 103 | 109 |
| GRIMFANDANGO.EXE | names/orig5_exe_globals.json (globals) | 53 | | 16 (+1 same name) |
| IMUSE.DLL | names/orig5_imuse_funcs.json | 3 | 1 | 2 |

Functions (`python -I tools/stats.py`):

| program | named before | after | of which auto/module-level | FUN_ before | after |
|---|---|---|---|---|---|
| GRIMFANDANGO.EXE | 2359 | 2462 | 119 -> 119 | 312 | 209 |
| LUA.DLL | 689 | 689 | 43 | 163 | 163 |
| IMUSE.DLL | 301 | 302 | 28 | 150 | 149 |

Globals referenced by the decompiled code (scratchpad `gcount.py`): GRIMFANDANGO.EXE 727 -> 764 named of 2274
(DAT_/PTR_/UINT_ 1547 -> 1510); LUA.DLL 69 / 367 and IMUSE.DLL 100 / 366 unchanged.

### Target 1: the EXE's 312 FUN_

103 named (the LEC library's service functions, `rdColormap_Size`, `gra_SetBitmap`, `msc_MemSet`,
`msc_error_SaveString`, `SmushPlay_FakeBlit`, `frame_Timer` / `sync_Timer`, `VbrAdpcm_Uncompress`,
`sys_GetCount` / `sys_ExtSync`, `sou_mixer_terminate`, `sputSmush_StopVideo` / `_SetVideoPalette`, ...). The 209 left:

| class | count |
|---|---|
| dead MSVC runtime / zlib copies (names/lib_replace.json `dead`) | 144 |
| zlib (lib_replace `zlib`, 21; live `gzflush` 0x4c4650 and `gzerror` 0x4c4a00, 2) | 23 |
| runtime replaced by the host msvcrt (lib_replace `host`) | 6 |
| live MSVC runtime (0x4addf0, the rename / remove / getcwd helpers 0x4d56f0..0x4d5990) | 8 |
| folded copies: 5 rdRaster edge advances (orig-4), the shared LEC stub 0x4cbf40 (flobdec SetVal / GetVal) | 6 |
| LEC library code the remaster inlined or does not have | 15 |
| game code with no remaster symbol | 7 |

The 15 LEC ones: the animator internals of `anm_animator_Render` / `_NewAnim` (0x4c3b30, 0x4c3bb0, 0x4c3c00,
0x4c3c90, 0x4c3d90; inlined, the remaster's render calls only SyncUp / SetRate / gra_SetBitmap / msc_MemCopy), the
table slot 0x4c25c0 that wraps `anm_Render` (0x4c27a0; the remaster's anm_Render is both, so the slot keeps FUN_),
the streamer internals 0x4c4f60 / 0x4c51b0 / 0x4c51e0, the directory path helpers 0x4c5350 / 0x4c5370, the Blocky16
helper 0x4cd3f0, the video converter 0x4ced70, the assembler fill 0x4d5fd0 behind msc_MemSet, and the v1.01 light
editor's dialog procedure 0x4bf950 (no light editor in the remaster). The 7 game ones: 0x402200 (an indirect call,
no caller), 0x408800 (a tail of rdNRaster_DrawNGonTFAT, no caller), 0x450220 (a record initialiser of
rdModel3_LoadEntryText, inlined there), 0x4734c0 (the platform table's fgetws wrapper), 0x4761b0 (the DirectDraw
enumeration callback), 0x480020 (an overlap inside Res_SysInitialize, a Ghidra artefact), 0x4862b0 (the qsort
comparator of the actor draw list).

### Target 2: the generated names

* EXE 119 = 91 `rdRaster_*` (the 86 v1.01-only per-texture-width span fillers, the 2 z-write spans the remaster
  inlined, the 3 folded copies; `rdRaster_Startup` is original but counted by its prefix) + 28 MSVC runtime names
  with `__` (`__sbh_*`, `__crt*`, `__addl`, ...): nothing to pair.
* LUA.DLL 43 = 8 Lua `l<module>__<addr>` names + 35 runtime. The 8 are Grim's own code: `lstate__85e0` checks the
  opcode directory (assert `op < (sizeof(opcodeDirectory)...)`), `lundump__d030` / `d130` / `d360` / `d380` / `d3c0`
  are the undump allocation, XOR decoding, byte swaps and the `#` line skip, `lzio__ef20` / `ef40` the runtime
  set-up of the stream pointers. The remaster's libLua.so has no counterpart (its unpaired functions are luaFPutc,
  lua_PrintGlobals, luaD_init, luaD_travstack, PrintGlobals, stderrorim, prev, freeglobals: none of these bodies).
* IMUSE.DLL 28 = 16 `iMUSE_*__<addr>` + `hmi__bae0` (the runtime `sin`) + 11 runtime. No candidate held up: the
  alignment's only votes are `iMUSE_Dispatch__3510 -> MxMix` (MxMix is paired already) and
  `iMUSE_dsound__3a80 -> zg_Audio_GetCurrentFillIndex` (platform); the remaster's dispatch inlined the small helpers.
  IMUSE FUN_: `FUN_10007a90` is ihost_open_sound; the three `query_music_stream` votes (0x100076b0, 0x10007700,
  0x100077c0) stay out as in orig-3 (three v1.01 functions for one remaster function), `FUN_100067b0` (calls ImPause /
  ImResume) is not grimlib_SetPause (that is the engine's).

## Target 3: the doubtful lists, settled

Renamed:
* `Resource_OpenArchivesInDir` -> AddResourcePath (same sequence: strip the separator, NewFind(dir, 3, ext), open and
  move each archive to the front, the fixed list); with it `Lab_OpenByName` -> Res_FileOpen and `Lab_MoveToFront` ->
  Res_FileMoveToFront (its two calls).
* `Actor_DrawShadowPlane` -> sputCostume_DrawMeshShadow (the only shadow.mat / shadow.cmp loader; caller
  sputCostume_DrawActorShadow and callees agree), `Shadow_DrawClippedPoly` -> sputCostume_OutputShadowPoly,
  `Plane_IntersectSegment` -> sputRender_SegmentPlaneIntersect.
* `SetFile_ParseSectors` -> ParseCollection (WalkPlane.cpp's parser; the only unpaired callee of sputRoom_ParseSectors).
* `rdThing_DrawAlt` -> rdThing_Draw (the switch on the thing type), and the old `rdThing_Draw` (0x40cf20) ->
  rdModel3_Draw (it is the model case: sphere test, geometry set, puppet, counts rdModel3_numDrawnModels);
  `rdModel_DrawNode` -> rdModel3_DrawHNode.
* `rdModel3_New` -> rdModel3_Load (alloc 0x90, loader hook, load, post-process) and the old `rdModel3_Load` (0x40a980)
  -> rdModel3_LoadEntry (LDOM magic -> Binary / Text).
* `Im_VimaDecompress` (IMUSE) -> AudioLib_ParseWaveFileHeader: it is not a VIMA decoder; the body is the remaster's
  wave header parser (MCMP header skipped, RIFF / `WAVEfmt ` checked), callers CacheGetSoundId, the dispatcher's
  region change and the sound start agree. Its callee `Im_VimaDecodeBlock` -> AudioLib_DetectRawFormat.
* A wrong name of the orig-names round: 0x4a49a0 `sputResource_SetHandler` is sputRoom_LoadRoom (alloc the set record,
  LoadRoomEntry, find the name, Puck validate, free on failure), `ResType_SetHandler` (0x48de70) is the real
  sputResource_SetHandler (the 'SET ' slot of the type table), and the old `sputRoom_LoadRoom` (0x4a4b00) is a helper
  gcc inlined into sputRoom_LoadRoom: back to its hand-made name SetFile_Parse ("not in the remaster").

Stay (with the reason):
* `Win_WinMain`: the v1.01 WinMain (8 lines into Main_*); the remaster's entry is the zg platform layer.
* `Display_Select`: inlined into the remaster's Main_Startup (its assert `stdDisplay_numVideoModes ==
  grimdemo_aDisplayInfo[deviceNum]...` is there); v1.01 has Main_Startup separately.
* `Lab_ReadDirectory`, `Lab_Open`, `LabDir_Open`: inlined into Res_FileOpen (LABN parsing, StoreFile).
* `LightEd_*` (WriteLightsSection, ReadControl, SaveSetFile, ...): the v1.01 Win32 light editor; sputRoom_WriteRoomToFile
  writes a whole set file, LightEd_SaveSetFile copies one and replaces the lights section: not the same function.
* `Collision_TestActorAgainstOthers` (and its caller Collision_UpdateMovedActors): inlined into
  sputActor_UpdateActors (the remaster's only sputLua_CollisionHandler caller).
* `LecShare_Reset`: inlined into LecShare_Initialize (the memset of privateData and the two stores).
  `LecShare_StartupModules` was settled in orig-globals (LecShare_Startup).
* The dirty-rect statics: v1.01 MarkDirtyRect copies the rect into 0x8a92a8..b4 (the vote NumDirtyRects for 0x8a92b0 is
  positional and wrong); the remaster has no such statics.
* `loadLastSave`: one vote for `g_pSaveFileName` again, contradicted as in orig-globals (a file name in v1.01, a slot
  in the remaster).
* `mlListSize`: no vote with the new pairs.

Other renames found on the way (all in the batch with their evidence): the resource type handlers
`ResType_*Handler` -> sputResource_*Handler (Bitmap -> Background), `ZBuffer_Load` / `_Free` ->
sputRoom_LoadZBuffer / _FreeZBuffer, `Set_Free` / `Set_FreeContents` -> sputRoom_FreeRoom / _FreeRoomEntry,
`Font_LoadFile` -> Text_LoadNativeFont, `Vec3_Rotate3x3` -> rdMatrix_TransformPoint34Acc, `Rle_*` ->
msc_rle_Decompress*, `Svc_*` -> default* (host services), `Movie_*Surface` -> sputSmush_*, `InsaneTimer_*` -> sys_*,
`SoundModule_*` -> sou_engine_*, `DsndDriver_*` -> dsn_*, `Blocky16_*` -> fob_* / flobdec_*, `AnimPlay_Destroy` ->
anm_Stop, `VideoBitmap_Create` -> bmp_bitmap_Alloc, `Video_PixelsFromRgba` / `Video_FillPixels` ->
gra_ConvertFromLecColor / gra_SetBuffer, `LecShare_Register` / `_Unregister` / `_Release` -> Publish / Unpublish /
Unsubscribe.

## Target 4: the EXE globals

Of the 1510 unnamed referenced globals (scratchpad `o5/gclass.py`; heuristic classes):

| class | count |
|---|---|
| used only by the MSVC runtime / zlib | 276 |
| literal / read-only (in .rdata, or initialised .data never written: float constants, string and pointer tables taken by address) | 198 |
| struct / array pieces (inside a matched remaster object of <= 4 KB, or aligned against `symbol+offset`) | 316 |
| real statics, zero-initialised | 684 |
| real statics, initialised and written | 32 |
| not data (code labels, stack / import artefacts) | 4 |

37 statics named (53 entries: the LEC service tables and module statics `grimmem_*`, `anm_preload_in` / `_out`,
`anm_audio_halted`, `msc_uncompress_*`, `msc_error_*`, `sys_*`, `sou_paused_flag`, `sound_channel`, `pCurGeo` /
`pModel3Loader`, `pTabFilename`, ...; 16 hand-made `g_` names replaced: `g_pRdCurrentThing` -> pCurThing,
`g_pRdCurrentModel` -> pCurModel3, the Blocky16 buffers -> fob_blk16_key / delta / render_buffer, global_bm_type,
fob_buffersize, fob_translation_shift*, the timer clock / count, `g_dwStreamVolume` -> currentVol, the timer / dsnd
interface tables). Most of the 716 real statics left belong to v1.01 code the remaster does not have (the DirectX /
DirectInput / Win32 layer, the light editor, the dirty-rect copies) or to functions whose pair has no vote for them.
Left out: `compressorState.2` / `.3` (gcc's numbered copies of one static name), the Blocky16 split tables (the votes
cross x / y and 4 / 8), `dsn_thread` (v1.01 has a timer id there), `aFile` / `sou_fill_data` (struct fields),
`stdDisplay_bOpen` (contested as in orig-4), the `DUP:` votes that point at another module's static.

## Target 5: type information in the remaster (feasibility only, nothing changed)

`GrimFandango`, `libLua.so` and `libchore.so` have no `.debug_*` sections and no `.gnu_debuglink` (only `.symtab` /
`.strtab`; built with GCC 4.8.2 and clang 3.5 by the `.comment`): no DWARF, so no struct or field names. What the
symbols do give: object sizes (8501 OBJECT symbols in GrimFandango, 141 in libLua.so, 32 in libchore.so: sizes of the
globals, e.g. the 0x104-byte WalkPlane records against v1.01's 0x84 sectors), and the C++ mangled names of 2053
GrimFandango and 137 libLua.so functions, which carry class names and parameter types (`ParseCollection(char*)`,
`WalkPlane::`, `Puck::`, `ObjectState::`, `PathFinder::`, `PrimitiveQueue::`, `HotspotManager::`,
`ObjectStateImage::`, `LState::`, `ExecutionState::`). That would type parameters of the C++ engine classes (WalkPlane
= Sector, Puck, ObjectState, LState) but not their layouts; field names still have to come from asserts and code (as the
chore round did). libchore.so has no mangled names (C).

## Build and tools

* The PTR labels Ghidra names after their target changed with the functions (`PTR_FUN_004f131c` ->
  `PTR_anm_SyncUp_004f131c`, `PTR_FUN_004f1328` -> `PTR_AnimPlay_anm_DebugInfo_004f1328`, ...: data symbol names
  only). The globals batch records the C-text name of the regenerated src as `"old"` (`PTR_FUN_004f0c18`,
  `PTR_s_language_tab_004e8024`), not Ghidra's relabelled one, so build_src's alias and rename_refs see the old src.
* 0x4cc3b0 is a JMP thunk (the blocky16 Reset slot) to 0x4cc590; both are named Blocky16_flobdec_Reset, as both were
  Blocky16_FreeBuffers, so build_src emits no thunk stub (a different name would add a jump to .text).
* `((code *)rdModel3_DrawMeshImpl)(...)` in rdModel3_DrawHNode lost its cast (the shorter global names change Ghidra's
  line wrapping, see orig_globals.md); .text is byte-identical with main's.
* names/orig_modules.json: the pins of the renamed functions recomputed (two old keys, `sputResource_SetHandler` and
  `sputRoom_LoadRoom`, now mean other functions). rename_refs is not idempotent for chains: it must run once per batch
  (a second run here would have carried rdThing_Draw on to rdModel3_Draw; the tree was reset and rerun once).
* rename_refs.py does not process build/mixdiff, build/perf/** or build/im_names.txt: carried by a one-pass script
  (scratchpad `o5/rr_extra.py`, also `_OLD` and `OLD__suffix`); build/overrides_asm_o2.c's `__ghidra` aliases updated.
  A grep of the whole tree (except src/, raw/, names/, docs/notes/) for every old name with a `_` prefix or `__x` suffix
  finds none. No token-pasted (`##`) uses of the renamed names.
* tools/orig_history.py knows the orig-5 batches.

## Checks

* Regenerated src equal to the previous src after mapping old -> new (scratchpad `cmpg.py`): IMUSE.DLL identical,
  EXE: only the relabelled PTR_ symbols, the rdModel3_DrawHNode cast and comparison artefacts of the chains; LUA /
  CHORE unchanged. All four LINKED, stubs EXE 42, LUA 58, IMUSE 9, CHORE 16.
* .text and .data of the four binaries byte-identical to main's build (worktree of 01e0e6e with raw/ from before the
  round); .rdata differs in the build time string only, IMUSE's .edata (export names) and the EXE's .idata (IMUSE
  import hints) by the new names.

Clean-room (`run.py decomp`; the suite has 5322 tests now, another session is adding expected files). Run on the final
build (EXE and IMUSE batches), then main's build (worktree of 01e0e6e, raw/ from before the round) right after it:

| build | result |
|---|---|
| orig-5, final | 6 of 5322 differ (sound_fade, gl1_say_right_edge, ims_voices, ims_save, ims_save_voice, rnd_say_low), 5316 the same |
| main 01e0e6e, run right after | the same 6, identical values |
| `run.py compare` of the two logs | 0 of 5322 differ |

The six are the other session's new / changing tests (the say-line text boxes, the iMUSE voice and save tests) and
sound_fade's timing value (`after` "1 0 1 64 120 67" against "1 0 1 64 127 64", as in rounds 3 and 4); they come out
identically with main's build, whose .text / .data are byte-identical to this one.

Harnesses: build/mixdiff (all nine: mix, mixcore, timer, drv, snd, video, codec, frame, misc) build on this branch and
on main alike and print the same (mix_test 0 of 150000, mixcore 0, codec 15000 cases 0 differences; timer_test exits
with code 3 and no output on main too; snd_test's resume loop runs for a long time on both). The build/difftest files
changed here (asm_s5, big_collision_others, r2, s3) only had names carried; asm_s5 / big_collision_others slice from
the empty asm_funcs.s on main as well (orig-3).

## What is left

* EXE: 209 FUN_ (186 runtime / zlib / folded, 15 LEC and 7 game functions without a remaster symbol, above), 1510
  unnamed globals (mostly runtime, literals, struct pieces and statics of v1.01-only code).
* The LEC library's hand-made names that did not come up in a table (e.g. `Blocky16_DecodeFrame`, the `Insane_*` /
  `Smush*` helpers) could be checked against the remaster's `fob_*` / `gra_*` / `anm_*` the same way.
* IMUSE.DLL: 149 FUN_ (124 runtime + 25 iMUSE code without a counterpart), the 16 `iMUSE_*__` names; LUA.DLL: nothing.
* Types: no DWARF; a typing round would take class names / parameter types from the mangled symbols only.
