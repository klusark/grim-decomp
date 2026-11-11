# orig-6: the hand-made names left (branch `orig-6`, 2026-11-11)

Sixth round after [orig_names.md](orig_names.md), [orig_globals.md](orig_globals.md), [orig_3.md](orig_3.md),
[orig_4.md](orig_4.md) and [orig_5.md](orig_5.md): the hand-made (non-original) function names that are left, LEC
library first, then the rest of GRIMFANDANGO.EXE, IMUSE.DLL and LUA.DLL, and the globals the new pairs pin. Sources as
before (`/linux/GrimFandango`, `/linux/libLua.so`, the ELF `.symtab`, Lua 3.1 source names). Names and comments only
(no types, no prototypes); exports, the MSVC runtime and zlib untouched.

## Method

* **Counting the hand-made names** (scratchpad `o6/classify.py`): every function of a program is FUN_, a runtime /
  zlib / lib_replace copy, a generated `<module>__<addr>` or `rdRaster_*` name, an original name (equal to a
  demangled remaster symbol, `Class::Method` as `Class_Method`, constructors / destructors as `_Construct` /
  `_Destruct`, or set by an orig batch), or hand-made (the rest). A hand-made name that happens to be a remaster
  symbol counts as original there; one of them was wrong (0x473630, below).
* **Pairs from today's names** (`o6/pairs.py`: the earlier pair files plus every v1.01 function whose current name is
  a remaster symbol), then three candidate sources, each candidate read in both texts (`o6/sh.py`, `o6/nb.py`:
  callers / callees with their pairs and the partner's unpaired callees):
  * **call-sequence alignment** (`o6/callalign.py`): the ordered calls of both sides of every pair, paired calls as
    anchors (difflib); an unpaired v1.01 callee against an unpaired remaster callee in an equal-length block between
    matched calls is a vote. This found what the token alignment of the earlier rounds missed, for example the whole
    shutdown sequence of Main_Shutdown (Spew_Shutdown, Engine_ShutdownGame, rdroid_Shutdown, Display_RestoreMode,
    Input_ShowCursor, Reg_Close, Services_Clear in the slots of grimDebug_Shutdown, grimlib_Close, rdShutdown,
    stdDisplay_Shutdown, stdControl_ShowMouseCursor, wuRegistry_Shutdown, stdShutdown);
  * the only-unpaired-callee / caller propagation of orig-5 (`o6/prop.py`) and the token alignment `o4/galign3.py`,
    rerun with the new pairs after each batch of reviews;
  * **the remaster's C++ classes and file order**: WalkPlane::*, Puck::*, PrimitiveQueue::*, ObjectStateImage::*,
    ObjectState::* have their methods in the order of the v1.01 functions (sector.c / walker.c / primitives.c /
    objstate.c); each pair was checked body against body (same field offsets, constants, asserts such as
    "tot_verts < MAX_DB_VERTS - 2", "edge_index < num_verts", the same calls).
* Remaster stubs of the platform layer (std3D_EndScene, stdDisplay_Shutdown, stdControl_ShowMouseCursor,
  wuRegistry_Shutdown, stdShutdown, grimDebug_Shutdown) are named by their call slot, as orig-4 did for std3D. The
  grimlib wrappers that are a single jump in the remaster (grimlib_CharacterCallback, grimlib_Using3DHardware,
  grimlib_AddResourcePath, grimlib_LogResources) are the v1.01 one-call wrappers of the same functions.
* Naming as before: the remaster's name as is when unique; `Class::Method` as `Class_Method`; a static two remaster
  files have keeps the v1.01 module prefix (`FindPath` -> Planner_FindPath); a JMP thunk gets its target's name
  (0x4d2d80 sou_mixer_start, 0x48a510 PrimitiveQueue_purge, 0x4aa0a0 ObjectStateImage_Clear: no thunk stub is added
  to .text). LUA.DLL: Lua 3.1 source names for the statics gcc inlined ("Named X (not in the remaster ...)").
* Globals: the statement method of orig-4 / orig-5 on the new pairs (the same assignment or test on both sides, the
  remaster's data symbol of that size); names by tools/orig_gbatch.py, the mixer statics the iMUSE mixer also has with
  the module prefix (`g_pMixer_mixBuf`).

## Batches and counts

| program | batch | renames | of which FUN_ | generated | hand-made names replaced |
|---|---|---|---|---|---|
| GRIMFANDANGO.EXE | names/orig6_exe_funcs.json | 194 | 2 | 0 | 191 (+ 1 wrong original-looking name) |
| GRIMFANDANGO.EXE | names/orig6_exe_globals.json (globals) | 25 | | | 10 `g_` names (+ 4 same name) |
| IMUSE.DLL | names/orig6_imuse_funcs.json | 4 | 2 | 2 | 0 |
| IMUSE.DLL | names/orig6_imuse_globals.json (globals) | 3 | | | 0 |
| LUA.DLL | names/orig6_lua_funcs.json | 4 | 0 | 0 | 4 |

Functions by origin of the name (scratchpad `o6/classify.py`, before -> after):

| program | hand-made | FUN_ | generated `__` | original |
|---|---|---|---|---|
| GRIMFANDANGO.EXE | 593 -> 402 | 209 -> 207 | 0 | 1400 -> 1592 |
| IMUSE.DLL | 29 -> 29 | 149 -> 147 | 16 -> 14 | 191 -> 195 |
| LUA.DLL | 69 -> 65 | 163 -> 163 | 8 -> 8 | 315 (+59 Lua 3.1) -> 315 (+63 Lua 3.1) |

`python -I tools/stats.py`: GRIMFANDANGO.EXE named 2462 -> 2464, FUN_ 209 -> 207; IMUSE.DLL named 302 -> 304, generated
28 -> 26, FUN_ 149 -> 147; LUA.DLL unchanged (689 named, 163 FUN_).

### Target 1: the LEC library

16 renames: the LEC mixer (`Mixer_Init` -> sou_mixer_initialize, `Mixer_ClearAccumulator` -> sou_mixer_start with
its thunk, `Mixer_MixVoiceByFormat` -> sou_mixer_mix, `Mixer_Output` -> sou_mixer_end; the order of
dsn_fill_thread: start, fill callback with sou_mixer_mix, end), `DSound_FillStreamBuffer` -> dsn_fill_thread (the
fill routine dsn_initialize starts: a timer callback here, a thread in the remaster), the video converters
(`VideoBitmap_ConvertPixels` -> gra_ConvertCopy, `Video_PixelsToRgba` -> gra_ConvertToLecColor (the counterpart of
gra_ConvertFromLecColor), `Video_BlitConvert` -> gra_BlitRectLookup, `FUN_004ced70` -> gra_ConvertMakeLookup), blocky16
(`Blocky16_BuildPixelOffsets` -> fob_blk16_configure, `Blocky16_DecodeBlock4` / `_DecodeBlock2` ->
block16_RenderBlock4 / _RenderBlock2: the 4x4 and 2x2 levels of the opcode decoder), the timer
(`InsaneTimer_ThreadProc` -> timer_thread, `InsaneTimer_ServiceDeferred` -> sys_timer_dispatcher).

Left (61 LEC names, why): inlined or rewritten in the remaster: the mixer internals (Mixer_InitTables, Mixer_Free,
Mixer_MixVoice, Mixer_ConvertTo16 and the eight per-format mix loops are one sou_mixer_mix / _end there), the video
pixel converters (Video_ExpandIndexed*, Video_*ToRgba32 / Rgba32To*), Video_CopyRect (assembler copy; the remaster calls
msc_MemCopy), Blocky16_DecodeFrame / _DecodeBlocks / _DecodeBlock8 / _DecodeHalfRows* / _BuildExpandTable (inlined into
the remaster's flobdec_DecodeBody, whose 8x8 level has no separate function), InsaneTimer_Tick / _RunDeferred (inlined
into timer_thread / sys_timer_dispatcher), the SoundModule_* helpers (inlined into sou_engine_*), LecShare_FindEntry /
_Reset and the Str_* helpers of lecshare.c (inlined), Insane_MemCopy (inlined into msc_MemCopy); platform code:
DSound_* / DsndDriver_* / Dsnd_* (DirectSound, the assembler memory helpers), InsaneTimer_StartThread / _StopThread
(Win32 thread), the Insane_* blits of the SMUSH frame (the remaster draws through its renderer). LecShare_Nop is a
shared empty function (several slots). The remaster's *_config functions (sou_sound_config, sys_timer_config, ...) are
referenced by nothing in either build.

Doubtful, left out: `Video_CopyRectDstFirst` is the remaster's gra_CopyRect (same slot and arguments), but with the
shorter name Ghidra wraps the call in gra_BlitRectLookup differently, build_src then drops the `(code *)` cast of that
call and video.o changes (the call returns void instead of int); the name was put back and the plate comment says so.

### Target 2: the rest of the EXE

178 renames. The big groups:
* WalkPlane / Puck (sector.c, walker.c): 23 `Sector_*` / `SectorList_*` / `SectorVertexPool_*` / `Set_FreeSectors` /
  `Set_ActivateSectors` -> WalkPlane_* (Construct, Destruct, SetName, SetType, Within, ClosestPoint, Project, Draw,
  KillCollection, SetCollection, PlaneAt, PlaneNumbered, PlaneClosest, GetConstraintVector, AllActive, AddVertex,
  RemoveVertex, ClipPoly, DistToEdge, RemoveShortEdge, BuildCache, DestroyCache, RestoreCache); 9 `Walker_*` -> Puck_*
  (Construct, Destruct, Rot, Xform, InvXform, OrientToPlane, Normalize, Forward, Draw); the planner (`Planner_PlanPath`
  -> BuildPath, `_SearchSectors` -> Planner_FindPath, `_CollectSharedCorners` -> FindExitPoints, `_SmoothPath` ->
  TightenPath), the collision box helpers (`Collision_BoxCorners` / `_SegmentHitsBox` / `_PushOutOfBox` ->
  FindObjectCorners / TestCollision / GetOuttaTheBox), `Walker_UpdateYaw` -> sputActor_AlignToPuck.
* PrimitiveQueue (primitives.c): 21 `Primitive_*` / `PrimitiveList_*` -> PrimitiveQueue_* (addLine, addRect,
  addPolygon, addObject, deletePrimitive, changeColor, changeLayer, move, moveTo, moveEndpoint, changeDimensions, draw,
  drawPrimitive, markAllDirty, markDirty, resetId, findPrimitive, purge with its thunk, Construct) and
  PrimitiveObject_Construct.
* ObjectStateImage / ObjectState (objstate.c): 15 `StateImage_*` / `ObjectState_*` -> ObjectStateImage_* (Construct,
  Clear with its thunk, SetFile, Load, VBuffer, SetClean, Draw, InSync) and ObjectState_* (LoadResources,
  UnLoadResources, Reset, Update, SetCopyMode). `StateImage_Draw` was left by orig-4 because the remaster split
  SetupDraw out of Draw; it is the function in Draw's call slot (ObjectState_Update) with the same body.
* The shutdown chain of Main_Shutdown (`Grim_Shutdown` -> Main_Shutdown and its callees above), the display close
  (`Engine_CloseRenderer` -> grimlib_UnsetDisplay, `Display_CloseMode` -> stdDisplay_ClearMode, `Display_CloseDevice`
  -> stdDisplay_Close), controls (`Control_Release` / `_Enable` / `_Disable` -> sputControl_Close / _EnableControl /
  _DisableControl, `Controls_ResetAll` -> sputControl_Reset, `Debug_CameraFovKeys` -> sputControl_StandardHandler,
  `Input_Disable` / `_ResetState` / `_EnableAxis` -> stdControl_Close / _Reset / _EnableAxis).
* std.c and the std libraries: `stdFile_*` -> stdFileOpen .. stdFilePrintf (+ FUN_004734c0 stdFileGetws; the same order
  as the remaster's std.c), the image / bitmap writers and loaders (stdGif_Write, getcode, putcode, stdBitmap_Write /
  _AppendToFile / _LoadEntryFromFile / _NewEntry / _FreeEntry / _Load / _MemUsage), stdPlatform_InitServices and the
  four handle services, stdMath_* (NormalizeAngle, NormalizeAngleAcute, FlexPower, ArcSin1, ArcTan4), LzssDecompress.
* rdroid / Jedi: the rd setters (`rdroid_Set*Mode` -> rdSetGeometryMode .. rdSetZBufferMethod, rdSetRenderOptions),
  rdFinishFrame, rdCache_FinishFrame, rdCache_InsertFace (`rdPrimit3_DrawPolygon`), rdCamera_NewEntry / _FreeEntry /
  _SetFOV, rdCanvas_NewEntry, rdThing_NewEntry / _AccumulateMatrices, rdSprite_FreeEntry, rdMaterial_FreeEntry,
  rdColormap_BuildGrayRamp, rdClip_Line2 / _CalcOutcode2, rdPrimit2_DrawRectangle, rdMath_CalcSurfaceNormal /
  _ClampVector, rdVector_Cross3 / _Dot2 / _Normalize3 / _ExtractAngles, rdMatrix_TransformVectorOrtho34, std3D_EndScene.
* grimlib / sput*: grimlib_Close, _Save, _RequestShutdown, _CharacterCallback, _Using3DHardware, _AddResourcePath,
  _LogResources; sputRender_MarkDirtyRect, _CreateCacheRect, _SetPaletteFunc, _Using3DHardware,
  _DrawDebuggingToggle; sputResource_AddResourcePath / _LogToFile, Res_Log, Res_RestoreFileCalls (orig-3 had rejected
  the Res_SysUnregisterHandler vote; this is the right one), res_LocateResByName, res_DefaultHandler;
  sputActor_SetTurnChores / _SetShadowValid; sputText_FindSerialNumber; GetRoomActors; GetPrevMode.
* A wrong earlier name: 0x473630 `stdBitmap_Load` (hand-made, not from an orig batch) is the remaster's stdLoadImage (std.c
  between stdFPutc and stdLoadImageData: stdLoadImageData, then stdBitmap_DeCompress); the remaster's stdBitmap_Load is
  0x47aa50 (`stdBitmap_LoadResource`). Also `stdBitmap_ConvertToDisplay` computes the memory use: stdBitmap_MemUsage.

Left (402, why; scratchpad `o6/cls1_GRIMFANDANGO.EXE.json`):

| group | count | why |
|---|---|---|
| platform layer (DirectDraw / Direct3D / DirectInput / DirectSound / Win32 window, registry, dialogs: stddisplay 40, std3d 24, window 15, stdinput 11, reg 9, grim 8, plat 6, ...) | 131 | the remaster's platform layer is new (zg_* / OpenGL / SDL); only the slots that still exist were named |
| engine helpers (lua 12, res 11, render 11, actor 10, set 10, text 9, stdgif 8, lab 7, engine 6, costume 6, ...) | 176 | inlined into their remaster callers (gcc), Grim v1.01-only debug drawing, or no unpaired partner in the caller pair |
| LEC library helpers | 61 | above |
| the v1.01 light editor (LightEd_*, LightMgr_*, Lua_LightMgr*) | 24 | not in the remaster |
| import thunks named after the import (DirectSoundCreate, GetOpenFileNameA, ...) | 10 | not renamed |

Rejected after a look (with the reason): `rdroid_SetColormap` (its body sets rdColormap_pIdentityMap like the
remaster's rdColormap_SetIdentity, but every v1.01 caller calls rdColormap_SetCurrent in the remaster and
rdColormap_SetIdentity has no caller), `Controls_DebugKeysHook` (the v1.01 wrapper registered as the control callback;
its body is the call of sputControl_StandardHandler), the Engine_*Subsystems table helpers (inlined into the
remaster's grimlib_Base* module functions), `0x482970` (a JMP thunk to sputLua_DoPauseCallback where the remaster has
grimlib_PauseCallback: a thunk keeps its target's name), the earlier rejected `Lab_FindEntry`, `stdConffile_Pop`,
`Engine_SaveGame`, `Grim_OpenRegistry`, `Str_ComparePtrs`, `Actor_UpdateMovement`, `Set_DrawDebugLights`
(votes the code contradicts, as in orig-3 / orig-4), `Mem_DumpLog` / `Plat_ReturnTrue` / `Lua_Stub` /
`CostumeTag_Nop` (shared empty functions), `Math_Floor` / `Math_Sqrt` (wrappers of the C runtime's floor / sqrt).

### Target 3: IMUSE.DLL

4 renames: the generated `iMUSE_sounds__9e10` / `__9e40` are iRes_FTELL / iRes_FSEEK (same bodies: the MCMP handle
array or the host service), `FUN_10009f10` / `FUN_1000a010` are iMUSE_Malloc / iMUSE_Free (the host alloc / free in
sounds.c and the memory list; the remaster inlined the list helpers FUN_10009f40 / FUN_1000a030). The 29 hand-made
Im_* names have no counterpart (the remaster's dispatcher and mixer inlined them: Im_MixLoopA..D, Im_DecodeSoundBlock,
Im_ConvertBlockImpl; DirectSound / HMI FX code: Im_DSoundCreateBuffer, Im_ApplyFXPreset; the earlier rejected
Im_DispatchFetchNext, Im_RunTriggerCommand, Im_SoundsPrepare; the 11 import thunks timeGetTime, hmiFX*). Of the 25
iMUSE FUN_ 23 stay: the memory-list set-up / free of sounds_startup / _shutdown (inlined), the three
query_music_stream votes (three v1.01 functions for one remaster function, as in orig-3 / orig-5), the music-script
state helpers, the HMI FX glue, the bsearch comparator.

### Target 4: LUA.DLL

4 renames by Lua 3.1 source names (lgc.c statics gcc inlined in libLua.so): `luaC_markall` -> markall (the stacks,
globalmark, travlock, the tag methods, in Lua 3.1's order), `luaC_travglobal` -> globalmark, `luaC_travstack` ->
travlock (the locked refArray entries, not a stack), `luaC_strmark` -> strmark. The other 65 hand-made names are
Lua-3.1-style names of Grim's LUA.DLL that are right apart from a guessed prefix or have no source counterpart this
round could check (luaA_*, luaD_callC, the io_* / str_* helpers, luaU_Load*: Grim's undump), and the MSVC runtime
helpers (GetLcidFromDefault, TranslateName, parse_cmdline, getSystemCP, setSBCS, setSBUpLow, tmpnam_genfname, the two
import thunks). libLua.so's unpaired functions (luaFPutc, lua_PrintGlobals, luaD_travstack, LState::LState /
~LState / PrintGlobals / prev / freeglobals, ExecutionState new / delete / constructor, stderrorim) have no v1.01 body
(Grim's luaD_travallstacks walks all states, not one).

### Target 5: globals

EXE (25 entries): the LEC mixer statics (`g_dwMixTableUnits` -> g_dwWaveMixCount, `g_pMixAccum` -> g_pMixer_mixBuf,
`g_dwMixAccumBytes` -> g_dwMixer_mixBufSize, `g_pMixCompanderTable` -> g_pMixer_softLTable, `g_dwMixChannels` ->
g_dwMixer_outChannelCount), fob_blk16_configure.old_mod, convert_bitmask, timer_thread.lastTime, the WalkPlane cache
(`g_nShrinkVertexCount` / `g_pShrinkVertexSave` / `g_nShrinkSectorCount` / `g_pShrinkSectorSave` -> VertexCacheSize /
VertexCache / WalkPlaneCacheSize / WalkPlaneCache, wpCacheBuilt), WalkPlane::tot_verts, WalkPlane::Collection,
Puck::p_head, Puck::Forward's recursion_level, Puck::Rot's ret, `g_nNextPrimitiveId` -> PrimitiveQueue::nextId,
sputRender_MarkDirtyRect::trect, stdControl_aAxes; TotWorkingPathPoints, WorkingPath, debugFlags and logFile keep
their (already right) names and get the comment. IMUSE: mlEntries, mlEntryCount, mlListSize (the contested
mlListSize of the earlier rounds, now settled by iMUSE_Malloc / iMUSE_Free: append at mlListSize while below
mlEntryCount, double mlEntryCount when full). Left out: printBuffer (two remaster files have one), the vertex
database base (the code uses vert_db + 4), prevMode (no symbol of that name).

## Build and tools

* Regenerated src equal to the previous src after mapping old -> new (scratchpad `cmpg.py`): LUA / IMUSE / CHORE
  identical; EXE only the PTR label Ghidra renames after its target (`PTR_ResType_DefaultHandler_004e79ac` ->
  `PTR_res_DefaultHandler_004e79ac`, data symbol only). All four LINKED, stubs EXE 42, LUA 58, IMUSE 9, CHORE 16.
* .text and .data of the four binaries byte-identical to main's build (worktree of 2e58b5e with a copy of raw/ from
  before the round); .rdata differs in the build time string only, the DLLs' .edata (export names) and the EXE's .idata
  (IMUSE import hints) by the new names.
* export_changed.py did not re-export IMUSE's 0x10004660, which stores iMUSE_Malloc / iMUSE_Free into the HMI FX
  callbacks (no xref from those stores); it went through raw/touched.json. A check over raw/<prog>/functions (code
  without comments) finds no old name afterwards (only the four same-name globals and the chain stdBitmap_Load).
* rename_refs.py once per batch (and `--difftest` once per batch); build/mixdiff, build/perf and build/im_names.txt by
  the one-pass script of orig-5 (scratchpad `o5/rr_extra.py`). Fixed by hand: the `__ghidra` aliases of
  build/overrides.c (`stdFileRead__ghidra`), the asm label `_ObjectState_Update:` in
  build/difftest/big_engine_renderframe/renderframe_test.c (inside a string), a comment of build/opt.mk. A grep of the
  whole tree (except src/, raw/, names/, docs/notes/) for every old name with a `_` prefix or `__x` suffix finds none.
  No token-pasted (`##`) uses of the renamed names.
* names/orig_modules.json: the pins of the renamed functions recorded by orig_batch.py (no earlier pin key changed
  meaning; `stdBitmap_Load` had no pin).
* A plate comment that named 0x473630 as stdBitmap_Load (stdBitmap_DeCompress's evidence) now says stdLoadImage; one
  that named g_pMixAccum (sou_mixer_start) the new global (scratchpad `fixplates.py`).
* tools/orig_history.py knows the orig-6 batches (2694 renames from the earliest names).

## Checks

Clean-room (`run.py decomp`; 5322 tests, another session is adding expected files):

Each run of this branch was followed by a run of main's build (worktree of 2e58b5e with raw/ from before the round,
same expected files); `run.py compare` of the two logs:

| build | this branch | main, run right after | compare of the two logs |
|---|---|---|---|
| EXE function batch | 7 of 5322 differ (sound_fade, gl1_say_right_edge, ims_cache, ims_voices, ims_save, ims_save_voice, rnd_say_low) | 6 (the same without ims_cache) | 1 of 5324: ims_cache (last 14 / 13, keep_after "0" / "1") |
| final build (all batches) | 6 of 5322 differ (sound_fade, gl1_say_right_edge, ims_voices, ims_save, ims_save_voice, rnd_say_low) | the same 6 | 0 of 5324 differ |

ims_cache run alone (`--only ims_cache`, three times for each build, EXE function build against main): both builds give
keep -216 every time and keep_after "1" or "0" from run to run (this branch 0 / 1 / 0, main 0 / 1 / 1): a
timing-dependent new test of the other session, as in orig-5. The six that differ for both builds are the other
session's new / changing tests and sound_fade's timing value; .text / .data are byte-identical to main's.

Harnesses: build/mixdiff quick (`run_all.sh quick`) on this branch and on main alike: mix_test 0 of 150000, mixcore 0
differences, timer_test and drv_test exit with code 3 and no output on both, snd_test's resume loop runs past the
20-minute limit on both; video_test / codec_test (0 of 2000) / frame_test run separately: the same on both.
build/difftest asm_q1 (1000 cases: 0 differences) and asm_q3 (200 cases: 0 differences, 0 of 25 mutations missed).

## What is left

* EXE: 402 hand-made names (above: platform code, inlined helpers, the light editor), 207 FUN_ (runtime / zlib /
  folded copies and 20 LEC / game functions without a remaster symbol, orig-5), `Video_CopyRectDstFirst` (gra_CopyRect,
  blocked by the generated cast).
* IMUSE.DLL: 29 hand-made, 14 generated, 23 iMUSE FUN_ without a counterpart; LUA.DLL: 65 hand-made names, 56 of
  them Lua-3.1-style names that a check against the Lua 3.1 sources could still correct.
* Globals: the remaining statics of the platform layer and of inlined helpers.
