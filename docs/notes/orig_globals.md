# orig-globals: original global names from the remaster's Linux build (branch `orig-globals`, 2026-11-10)

Second round after [orig_names.md](orig_names.md): the data symbols of the remaster's unstripped `libLua.so` and
`GrimFandango` (iMUSE linked in) for the globals of LUA.DLL, GRIMFANDANGO.EXE and IMUSE.DLL, then some leftovers of
the function round that the globals settled.

## Method

* Function pairs: every v1.01 function whose name is the remaster's (`Class::Method` written `Class_Method`, also
  `_Construct` / `_Destruct` / `_New` / `_Delete`, from the demangled ELF `.symtab`) plus the reviewed candidates of
  the function round. LUA.DLL 312 pairs, EXE 648, IMUSE 93.
* Alignment (scratchpad `galign.py`): the decompiled text of both sides of a pair is tokenised (locals -> `V`,
  globals -> `G`, string literals -> their contents: the v1.01 `s_..._ADDR` / `&DAT_x` strings are read from the
  section dumps, the remaster's `"..."` and `&DAT_x` from the ELF, so `lua_pushstring("width")` anchors), the token
  streams are diffed (difflib) and every `G` inside a matching block is a vote v1.01 global -> remaster symbol
  (`sym+offset` for `sym._4_4_` and DAT_ addresses inside a symbol). The remaster's names come from the ELF data
  symbols (demangled: `LState::refArray`, `grimlib_SetPause::oldmode`, C statics `Main_Service.frameRate`); a name
  several modules have (`memory_services`, `share_config`, `pHS`) is kept apart (`DUP:`) and named per module.
* Candidates: all votes for the top symbol at offset 0, the symbol's own best match the same global, one global per
  symbol; plus the function sets (paired functions using each side). Then every candidate was looked at; the
  positional alignment does go wrong where the code differs (sputText_Startup's lua_ref list before strings were
  anchors, `aParsers` for the sound pool, the swapped SmushPlay flags, a struct field taken for its struct), so
  single-vote ones were checked in both texts, and struct fields (`rdColormap_colorInfo+12`, `aView+24`) were left
  unnamed unless the base itself is referenced.
* Names (tools/orig_gbatch.py): `g_` + a Hungarian prefix the bridge accepts for the global's *current* Ghidra type
  + the original name, the original's own prefix kept when the type allows it (`pLuaHS` -> `g_dwLuaHS` on an
  undefined4, `psputCosHS` -> `g_pSputCosHS` on a `GrimServices *`, `rdroid_pHS` -> `g_pRdroid_HS`,
  `stdConffile_aLine` -> `g_dwStdConffile_aLine` on a uint), `::` and `.` -> `_` (`g_dwLState_refArray`,
  `g_dwGrimlib_SetPause_oldmode`, `g_flMain_Service_frameRate`), module statics `g_pZfile_memory_services`.
  Arrays take `sz` / `fl` / `ab`, a label without data `dw` (scalar by the remaster's symbol size) or `a`. The bridge
  takes no prefix at all for Ghidra's generic `pointer` type; those (`g_pSubscription_info`, `g_pStatic_l_desc`)
  were applied with `strict_mode=warn`. `L` is `g_pLuaState` (a one-letter descriptor is refused). The plate comment
  of each global is its old comment + "Original name X (source: evidence); was OLD."; each batch entry has `"old"`
  and `"oldtype"`.
* **Names and comments only, no types.** The batches are `names_only` entries (apply_names.py: rename_or_label /
  rename_label + plate comment); the Ghidra types stay.

## Build: renamed globals are built under their old names

tools/build_src.py declares a DAT_/PTR_/UINT_ global with a type inferred from its uses and its data item, a named
one with its Ghidra type, and several fix-ups look at the `DAT_` prefix; a plain rename would have changed the
declarations. So `load_global_aliases()` reads the names_only entries of names/*.json: while a renamed global has
the type recorded in `"oldtype"`, the raw text is read with the old name (also `_OLD`, `OLD_2`) and the old name is
replaced by the new one in the written files. The regenerated src is the previous src after mapping old -> new; a
global retyped in Ghidra later is taken as named.

tools/rename_refs.py carries global renames too (`"global"` entries; also Ghidra's other-width view `_OLD` and its
pieces `OLD_2`; the owners of a `DAT_1000xxxx` name come from raw/<prog>/data_items.txt, globals.json and the
decompiled code, so the #ifdef GRIM_* guard rule works for globals). It updated build/*.c (asm labels
`__asm__("_g_dwSound_samplerate")` included), the names/exe_*.json and mixer batches, docs/ASM_REMAINING_mixer.md.
Function plate comments in Ghidra that named an old global were updated (20 in the EXE).

## Batches and counts

| program | batch | globals | renamed | of which replace an earlier g_ name |
|---|---|---|---|---|
| LUA.DLL | names/orig_lua_globals.json | 58 | 58 | 0 |
| GRIMFANDANGO.EXE | names/orig_exe_globals.json | 279 | 274 (5 keep their name) | 87 |
| GRIMFANDANGO.EXE | names/orig_exe_globals2.json (SmushPlay, LEC modules) | 5 | 5 | 0 |
| IMUSE.DLL | names/orig_imuse_globals.json | 48 | 48 | 0 |
| IMUSE.DLL | names/orig_imuse_globals2.json (the mixer) | 3 | 3 | 0 |

Globals the decompiled code references (declarations in src/<prog>/globals.h without strings and code labels,
scratchpad `gcount.py`):

| program | globals | named before | after | DAT_/PTR_/UINT_ before | after |
|---|---|---|---|---|---|
| GRIMFANDANGO.EXE | 2274 | 271 | 463 | 2003 | 1811 |
| LUA.DLL | 367 | 11 | 69 | 356 | 298 |
| IMUSE.DLL | 366 | 0 | 51 | 366 | 315 |

Functions (`python -I tools/stats.py`), the leftovers of the function round (names/orig_exe_leftovers.json,
names/orig_imuse_leftovers.json):

| program | renamed | FUN_ named | named before | after | FUN_ before | after |
|---|---|---|---|---|---|---|
| GRIMFANDANGO.EXE | 27 | 4 | 2334 | 2338 | 337 | 333 |
| IMUSE.DLL | 2 | 1 | 292 | 293 | 159 | 158 |

The function renames the globals settled:
* SmushPlay: the module interface SmushPlay_SysInitialize fills is {Initialize, Terminate, Startup, Shutdown};
  the round before had `SmushPlay_SysShutdown` on the terminate slot. 0x4bd3a0 `Insane_RegisterFilio` ->
  SmushPlay_SysInitialize, 0x4bd430 `SmushPlay_SysShutdown` -> SmushPlay_SysTerminate (clears
  fSmushPlaySysInitialized), 0x4bd4d0 `Insane_Stop` -> SmushPlay_SysShutdown (clears fSmushPlaySysStarted),
  0x4bd370 `Insane_Poll` -> SmushPlay_GetMovieTime (sputLua_Update's movieTimeMsec).
* LecShare: `LecShare_Startup` -> LecShare_Initialize, `LecShare_StartupModules` -> LecShare_Startup (slot +8),
  `LecShare_Shutdown` -> LecShare_Terminate (slot +4, backwards), `LecShare_UnwindStartup` -> LecShare_Shutdown
  (slot +0xc).
* `SoundModule_Open` -> engine_Initialize, `Display_SetPalette3D` -> std3D_SetCurrentPalette (two of the doubtful
  candidates of the function round: SoundModule_module_startup / rdColormap_SetCurrent call them the same way).
* The functions that are the only unpaired user of a named global on both sides (scratchpad `fpin.py`, each
  checked): grimdemo_PleaseShutdown (bQuitApp), rdCache_ClearFrameCounters, rdMaterial_RegisterLoader /
  _RegisterUnloader, grimlib_SetCacheMax (max_ram), the module slots sputText_Shutdown / sputText_Restore /
  sputCostume_Shutdown / sputRoom_Shutdown (`*_Stop` / `*_RestoreState` before), sputText_ExtractSayLineData
  (`Text_ParseLineId`), sputResource_SetMemoryUsage, BitmapFreer (`BitmapComponent_Destroy`),
  sputLua_SetDebugToggleCallback, AnimPlay_ / AnimFrame_ / DWave_module_shutdown and anm_DecodeHeader (were FUN_);
  IMUSE MxEndMix (`Im_ReadSoundData`) and ihost_read (was FUN_10007ca0).

## Left out (doubtful)

* Struct fields the alignment found (rdColormap_colorInfo +n, aView +n, vertexSrc / vertexDst +n, attributes +n,
  states +64, trigs +304, sequences +32, imuseInitData +n, rootX +4 in LUA): the v1.01 code reads them as separate
  DAT_ globals; only a referenced base was named.
* Contested or v1.01-only: loadLastSave (v1.01 grimlib_Load stores a file name, the remaster a slot), the dirty
  rect statics of MarkDirtyRect (the remaster rewrote it), tmFuncs (v1.01 has a once flag instead), wvSlicingHalted,
  streamID / aMcmpFileHandles, mlListSize, rdColormap_pIdentityMap / numGeoLights / ClipPlaneActive / localCamera
  (one vote each in large functions), sputControl_numControlSymbols' second copy (0x4ec54c).
* Function pins rejected after a look: Win_WndProc -> zg_Grimdemo_mainMsgFunc (platform rewrite),
  Display_RestoreMode -> stdControl_ReadControls, Engine_LoadGame -> grimlib_UpdateManual (inlined),
  Blocky16_DecodeFrame -> flobdec_DecodeBody (not checked), FUN_10008ce0 -> iRes_FCLOSE (the timer set-up),
  luaL_growbuffer / luaC_travglobal -> PrintGlobals.
* The function round's other doubtful candidates are still open (Win_WinMain, Grim_Init, Lab_ReadDirectory, ...).

## Notes

* rename_or_label on an address with a user label and no data item adds a second label instead of renaming
  (seen when correcting seven EXE names); apply_names.py now renames such a label with rename_label, and
  ghidra_api.py journals rename_label / delete_label.
* The bridge's dry_run (and strict_mode) are read from the query string only; a `dry_run` in the JSON body is
  ignored and the write happens.
* One generated call is cast now where it was not: `((code *)Matrix34_TransformPoint)(...)` in
  rdModel3_DrawMeshImpl (Ghidra wraps the call `F\n (args)\n ;` with the longer global name, which
  call_is_statement does not take for a statement; the same as rdModel3_Draw in the round before). Pointer
  arguments, cdecl: rdmodel.o is byte-identical with and without the cast (checked). Letting call_is_statement skip
  newlines would be the general fix, but it also drops the float-argument casts of LightEd_SetDlgFloat, so it was
  not done.
* export_changed.py did not re-export IMUSE's 0x100072b0 (it reaches lastVoiceFilename through a
  computed address) nor the EXE's thunk 0x488fa0 and its caller; they were re-exported through raw/touched.json. A
  check over raw/<prog>/functions afterwards found no old name outside plate comments.

## Checks

Per batch: raw/<prog>/functions after the export equal to the previous export after mapping new -> old
(whitespace-insensitive, scratchpad `cmpraw.py`), the regenerated src and data.s equal to the previous ones after
mapping old -> new (`cmpg.py`; the one difference is the cast above), all four LINKED, stubs.txt EXE 42, LUA 58,
IMUSE 9, CHORE 16.

Clean-room (`run.py decomp`, the suite has 5167 tests now):
* LUA.DLL globals: 0 of 5167 tests differ, 5167 the same.
* GRIMFANDANGO.EXE globals: 0 of 5167 tests differ, 5167 the same (before and after the seven name corrections).
* IMUSE.DLL globals: 0 of 5167 tests differ, 5167 the same.
* GRIMFANDANGO.EXE leftovers + globals2: 0 of 5167 tests differ, 5167 the same.
* IMUSE.DLL leftovers + globals2 (final build of the round): 0 of 5167 tests differ, 5167 the same.

## What is left

* The function round's doubtful candidates other than the two settled here, the 351 generated rdRaster_* names.
* iMUSE: two more functions paired here (94); the rest of the remaster's iMUSE is a different build (Mx*, ihost_*, iRes_*
  exist on both sides, so more of the mixer and the resource layer could be paired by hand).
* Globals: the struct fields above (they could get `struct` types and names in a typing round), the CHORE.DLL
  globals were named in the chore round already.
* build/difftest harnesses still use old names (as after the function round).
