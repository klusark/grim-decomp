# orig-7: LUA.DLL against Lua 3.1, the last iMUSE and LEC / light-editor look (branch `orig-7`, 2026-11-11)

Seventh round after [orig_names.md](orig_names.md), [orig_globals.md](orig_globals.md), [orig_3.md](orig_3.md),
[orig_4.md](orig_4.md), [orig_5.md](orig_5.md) and [orig_6.md](orig_6.md): LUA.DLL's hand-made names against the Lua
3.1 source names and `libLua.so`, a last pass over IMUSE.DLL's leftovers, one more look at the EXE's LEC helpers and
light editor, and the closing summary of the series ([orig_summary.md](orig_summary.md)). Names and comments only (no
types, no prototypes); exports, the MSVC runtime and zlib untouched.

## Method

* **LUA.DLL against Lua 3.1.** None of the 56 Lua-style hand-made names is a `libLua.so` symbol (gcc inlined every one
  of them; the remaster's own names were all used by the earlier rounds). Each was read against the Lua 3.1 sources
  (file and function names only, no code copied; the reference for the names was ScummVM's port of Grim's Lua 3.1,
  `engines/grim/lua`, which keeps the 3.1 file layout and static names; Lua 3.1 itself is not on this machine): the same file (the v1.01 module and the
  `C:\grimsrc\libs\lua\src\<file>` strings of the allocator calls), the same callers and callees, the same error
  strings ("API error - wrong number of arguments in C2lua stack", "unexpected type to index table", "invalid capture
  index", "unbalanced pattern", "code too long (%ld bytes)", "constant table overflow", ...) and the same body (field
  offsets of LState, the tag numbers of Grim's Lua with LUA_T_TASK: NIL -7, CLOSURE -8, CLMARK -9, PMARK -10, CMARK -11).
  Plate comment: "Named X (not in the remaster, gcc inlined it there): Lua 3.1 source name (file static X: ...); was Y".
* **LUA.DLL globals.** The remaster's data symbols that v1.01 references and that were still DAT_ (`libLua.so`
  OBJECT symbols against the referenced globals of src/LUA.DLL/globals.h, by address order and size: tables follow
  each other as in the remaster: iolib 0x50 then iolibtag 0x28, reserved 0x80 then checkcond's opts 0xc,
  opcodeDirectory 0x60c then stateFuncs).
* **IMUSE.DLL.** The 29 hand-made, 14 generated and the iMUSE `FUN_` read against the remaster's unpaired iMUSE
  functions (UtReadLongHilo, UtReadShortHilo, UtWriteLongHilo, UtCheckHook, ConvertMap, StViewData, StGetOffset,
  StGetFileSize, FmGetChunkAddr, ihost_load_sound / unload_sound / close_sound, query_music_stream, TWIST16,
  MCMP_Status, SoundsIsDryVoiceStillPlaying, iMUSE_SetBufferCount, the AudioLib_* additions), body against body and by
  their callers (the remaster's GoToNextRegion inlined v1.01's `Im_DispatchFetchNext`, its PredictStream the JUMP
  search, its sounds_startup passes the four ihost_* script callbacks to ImInitializeScript).
* **EXE.** The 61 LEC helpers and 24 light-editor functions against the remaster's LEC functions that no v1.01 function
  has (anm_animator_Terminate, SmushPlay_IsPlaying / PlayMovie / SysSetSoundCallbacks / SysConfigureSubtitles,
  SmushInstanceSaveLoad, msc_error_GetString, msc_rle_DecompressTerminate, grimio_startup / shutdown / Flush,
  memory_CrunchHeap, fle_StreamerPrime, block16_DeltaBlock8, gra_BlitRect, the *_config functions, timer_callback) and
  the remaster's Lua registration table for the light manager.

## Batches and counts

| program | batch | renames | of which FUN_ | generated | hand-made names replaced |
|---|---|---|---|---|---|
| LUA.DLL | names/orig7_lua_funcs.json | 52 | 0 | 0 | 52 |
| LUA.DLL | names/orig7_lua_globals.json (globals) | 4 | | | 0 |
| IMUSE.DLL | names/orig7_imuse_funcs.json, orig7_imuse_funcs2.json | 6 | 1 | 4 | 1 |
| GRIMFANDANGO.EXE | none | 0 | | | |

Functions by origin of the name (scratchpad `o7/classify.py`, the orig-6 classifier; before -> after):

| program | hand-made | FUN_ | generated `__` | original (remaster symbol, orig batch, Lua 3.1 source name) |
|---|---|---|---|---|
| LUA.DLL | 65 -> 13 | 163 -> 163 | 8 -> 8 | 378 -> 430 (Lua 3.1 source names 63 -> 115) |
| IMUSE.DLL | 29 -> 28 | 147 -> 146 | 14 -> 10 | 195 -> 201 |
| GRIMFANDANGO.EXE | 400 (+2 prefixed originals) | 207 | 91 rdRaster | 1594 |

`python -I tools/stats.py`: LUA.DLL unchanged (689 named, 163 FUN_); IMUSE.DLL named 304 -> 305, auto/module-level
26 -> 22, FUN_ 147 -> 146; EXE and CHORE.DLL unchanged.

Globals referenced by the decompiled code (scratchpad `gcount.py`): LUA.DLL 69 -> 73 named of 367 (DAT_/PTR_ 298 ->
294); the others unchanged.

### Target 1: LUA.DLL

52 renames (names/orig7_lua_funcs.json, each with its evidence):

| file | renames |
|---|---|
| lapi.c | `luaA_checkCparams` -> checkCparams, `luaA_setnormalized` -> set_normalized, `luaA_normalizedtype` -> normalized_type, `luaA_normalizeObj` -> luaA_protovalue, `luaA_callObject` -> do_unprotectedrun (lua_setfallback's helper; Grim added the break-prevention counter) |
| lbuffer.c | `luaL_growbuffer` -> Lbuffer_Openspace (Lua 3.1's static Openspace; the bridge refuses the one-token name, so the module is the prefix as with `Undump_LoadString`) |
| ldo.c | `luaD_callC` -> callCclosure (copies the upvalues, then callC), `luaD_message` -> message, `luaD_callinc` -> do_callinc |
| liolib.c | `io_getint` -> gettag, `io_pushresult` -> pushresult, `io_setfile` -> closefile, `io_getfilebyname` -> getfile, `io_gethandle` -> ishandler, `io_setreturn` -> setreturn, `io_setfilebyname` -> setfile, `io_getfileparam` -> getfileparam, `lua_ioregister` -> openwithtags |
| lstring.c | `luaS_grow` -> grow, `luaS_newlstr` -> newone |
| lstrlib.c | `str_addnchar` -> addnchar, `str_closeandpush` -> closeandpush, `str_addstr` -> addstr, `str_bracket_end` -> bracket_end, `str_push_captures` -> push_captures, `str_capture_to_close` -> capture_to_close, `str_check_capture` -> check_cap, `str_add_value` -> add_s, `str_add_s` -> luaI_addquoted (format %q), and two wrong guesses: `str_matchbalance` is matchitem (%digit / %b / single match) and `str_expand` is matchbalance (the %b counter) |
| lua.stx | `luaY_string_constant` / `next_constant` / `code_number` / `real_constant` -> the bare static names (right apart from the prefix, as orig-3 noted) |
| ltable.c | `luaH_hashindex` -> hashindex, `luaH_rehash` -> rehash, `luaH_nuse` -> emptyslots (1 when a slot has a key and a nil value) |
| ltm.c | `luaT_gettm` -> validevent (it is the validevents lookup, not the tag-method getter), `luaT_gettmbyObj` -> fillvalids (luaT_setfallback's loop over the tags) |
| lundump.c | `luaU_LoadChunk` -> LoadChunk, `luaU_unexpectedEOZ` -> unexpectedEOZ, `luaU_LoadBlock` -> ezread, `luaU_LoadCode` -> LoadSize ("code too long"; orig-names had rejected LoadFunction for it), `luaU_LoadLocals` -> LoadLocals, `luaU_LoadConstants` -> LoadConstants, `luaU_loadheader` -> LoadHeader, `luaU_LoadSignature` -> LoadSignature |
| lvm.c | `luaV_adjust_varargs` -> adjust_varargs, `luaV_strconc` -> strconc, `luaV_call_arith` -> call_arith, `luaV_comparison` -> comparison |

Left (13 hand-made, why): `luaI_checkevent` is already the Lua 3.1 name (gcc inlined it); `luaM_malloc` / `luaM_free`
are macros of Lua 3.1's lmem.h that Grim's lmem.cpp made functions over the host services (the macro names are the
best names there are); `luaU_LoadNumber` is Grim's 4- / 8-byte float loader with byte swapping (Lua 3.1 reads numbers
through macros, no function of that role to take the name from); the other 9 are the MSVC runtime and two import thunks
(tmpnam_genfname, GetLcidFromDefault, TranslateName, parse_cmdline, getSystemCP, setSBCS, setSBUpLow,
GetCurrentProcessId, RtlUnwind). The 8 generated `lstate__85e0`, `lundump__d030` / `d130` / `d360` / `d380` / `d3c0`,
`lzio__ef20` / `ef40` stay (Grim's own opcode-size walk, undump decoding and byte swaps, CRT stream set-up; orig-5).

Globals (names/orig7_lua_globals.json): `g_aValidevents` (validevents, ltm.c, 0x90 bytes), `g_pIolibtag`
(iolibtag, the five closures of openwithtags), `g_pCheckcond_opts` (checkcond's static opts {"nil", "1", NULL}),
`g_aOpcodeDirectory` (the remaster's global opcodeDirectory, 0x81 entries of 0xc, read by lstate__85e0). Left out:
reserved (0x10026d10; the code references reserved+4 only, a field piece), stateFuncs (not referenced by code), the
errorim value piece DAT_1002bf5c (LState::errorim + 4), luaT_setfallback's once-flag DAT_1002bf80 (v1.01 only); the
other referenced DAT_ of the Lua code are string literals and format strings taken by address (the signature, "%.16g",
"n", "arg", the %q specials), and the MSVC ctype tables.

### Target 2: IMUSE.DLL

6 renames (names/orig7_imuse_funcs.json, and orig7_imuse_funcs2.json for the last one, found while writing up the leftovers):
* `iMUSE_stream__b810` -> UtReadLongHilo, `iMUSE_stream__b840` -> UtCheckHook: the same bodies (big-endian 32-bit
  read; the hook test that clears a matching hook, 0 matching 0x80).
* `iMUSE_Dispatch__2fe0` -> ConvertMap: the same body ('MAP ' 0x4d415020, size + 8 at most 0x800, every record
  converted, 'TEXT' records skipped); called by the region fetch.
* `iMUSE_stream__a490` -> StViewData: the same body (offset + size within the valid size and the view size, the ring
  wrap copied behind the buffer, buffer + offset returned); called by the region fetch.
* `FUN_10007250` -> ihost_close_sound: sounds_startup passes (load, unload, open, close) to ImInitializeScript in both
  builds and 0x10007250 is the fourth; the same body (id - 10000 indexes streamID, close below a use count of 2).
* `Im_DecodeSoundBlock` -> AudioLib_CreateWaveFileHeader: not a decoder; the same body (buffer, type, rate, bits,
  channels, size: type 3 the iMUS header with MAP / FRMT / REGN / STOP / DATA, type 5 RIFF, type 7 AIFF; returns the
  header length), and the callers agree (the region fetch, CacheGetSoundId, MxEndMix).

Left, with the reason (each read against the remaster):

| v1.01 | why |
|---|---|
| `Im_DispatchFetchNext` | inlined into the remaster's GoToNextRegion (v1.01's GoToNextRegion calls it; the remaster's calls ConvertMap / StViewData / UtReadLongHilo itself) |
| `iMUSE_Dispatch__30d0` (region search), `__35a0` / `__3640` (fade buffer alloc / free) | inlined into GoToNextRegion / DpSwitchStream / DpStopTrack / DpProcessTrack |
| `iMUSE_Dispatch__31d0` (JUMP search), `__3430` (stream splice) | inlined into the remaster's PredictStream (its UtCheckHook / StEraseFromMid / StSpliceStream calls) |
| `iMUSE_Dispatch__34b0` / `__3510` (fade volume step), `__3570` (stream zone reset) | inlined into DpProcessTrack / DpConcludeRestore / PrepareToJump |
| `iMUSE_dsound__3a80` | DwQuery's DirectSound play position (platform; the remaster has zg_Audio_*) |
| `iMUSE_sounds__9eb0`, `FUN_10009ef0` | iRes_FREAD's bsearch lookup and its comparator (inlined) |
| `Im_MixLoopA..D`, `Im_ConvertBlockImpl` | inlined into the remaster's MxMix and AudioLib_UncompressBlock (the delta table set-up and the decode loop are in its body) |
| `Im_DSoundCreateBuffer`, `Im_ApplyFXPreset`, `FUN_10004660` / `_10004750` / `_10004970` | DirectSound and the HMI FX presets (not in the remaster) |
| `Im_SoundsFreeSlot`, `Im_SoundsPrepare`, `FUN_10008c40`, `FUN_10008e60`, `FUN_10009530` / `_10009560` | sounds.c helpers inlined into their callers (SoundsCloseVoiceFile / LoadLip / the cache, SoundsLoadProcessStartSound, iMUSE_GetPhoneme, sounds_shutdown / restore, ihost_get_sound_addr / ihost_get_map_addr) |
| `Im_AllocTrackOrSteal`, `Im_RunTriggerCommand`, `Im_RunDeferredCommand` | inlined into TrStartSound / TgIntHandler (as orig-3 / orig-6) |
| `FUN_10006360` / `63d0` / `6400` / `6470` / `64d0` / `6560` / `67b0`, `FUN_10007110` | the cases of v1.01's ScriptCall (initialize, terminate, save, restore, refresh, state, ...) as separate functions; the remaster's ScriptCall has them inline |
| `FUN_100067a0` | one empty function in two slots (ihost_load_sound and ihost_unload_sound, two stubs in the remaster): a shared copy keeps FUN_ |
| `FUN_10004460` / `_100044b0` | the file manager's list add / remove copies (with "iMUSE.C: list arg err ..."), inlined into ImLoadSound / ImFlushSounds |
| `FUN_100076b0` / `7700` / `77c0` | three v1.01 functions for one remaster query_music_stream (as orig-3 / orig-5) |
| `FUN_10007a20` / `_100081f0` / `_10009f40` / `_1000a030`, `FUN_10008ce0` / `_10008e30` | the memory list and the multimedia timer set-up / shutdown, inlined into sounds_startup / shutdown, iMUSE_Malloc / Free (the remaster uses zg_Thread) |
| `FUN_10009700` | an empty function called by sounds_restore |
| 15 import thunks (timeGetTime ... hmiFXFree) | named after the import |

The remaster's UtReadShortHilo, UtWriteLongHilo, TWIST16, StGetOffset, StGetFileSize, FmGetChunkAddr, MCMP_Status,
iMUSE_SetBufferCount, SoundsIsDryVoiceStillPlaying and the other AudioLib_* additions (GetVersion, CompressBlock,
EstimateConversionSize, GetMouthPosition, GenerateLipSynchBlock: no caller in the remaster) have no v1.01 body
(inlined or new).

### Target 3: the EXE's LEC helpers and light editor

No rename. The light editor: the remaster registers the Lua functions LightMgrStartup / LightMgrShutdown /
LightMgrSetChange with `DoNothing` (its Lua table read from the ELF: the name pointer at 0x829ee50 is followed by
0x80acb00 DoNothing for all three), so `Lua_LightMgr*` and the 21 `LightEd_*` / `LightMgr_*` functions behind them
have no counterpart (its InitLight / LightsPrint / LightsCleanup / LECReadLightSection are the new L3D light format,
not the v1.01 editor: other fields, other strings). The 61 LEC helpers: the remaster's LEC functions without a v1.01
partner are empty slots or remaster additions (anm_animator_Terminate, msc_rle_DecompressTerminate, grimio_Flush /
startup / shutdown, fle_StreamerPrime, SmushPlay_IsPlaying are empty; SmushPlay_PlayMovie, SmushInstanceSaveLoad,
SmushPlay_SysSetSoundCallbacks / SysConfigureSubtitles, memory_CrunchHeap, msc_error_GetString are not in v1.01;
gra_BlitRect is a wrapper v1.01 does not have; block16_DeltaBlock8 is the 8x8 motion copy that v1.01's
Blocky16_DecodeBlock8 has inline, not the whole 8x8 decoder). The reasons of orig-6 stand (inlined: the mixer internals,
the pixel converters, the blocky16 levels, the timer, SoundModule_*, LecShare_*; platform: DSound_* / DsndDriver_* /
Dsnd_*, the timer thread, the SMUSH blits). `Video_CopyRectDstFirst` (gra_CopyRect) stays as orig-6 left it.

## Build and tools

* Regenerated src equal to the previous src after mapping old -> new (scratchpad `cmpg.py`): LUA.DLL and IMUSE.DLL
  0 files and 0 data.s lines differing; EXE and CHORE.DLL src unchanged. All four LINKED, stubs EXE 42, LUA 58,
  IMUSE 9, CHORE 16.
* .text, .data and .rdata of LUA.DLL and IMUSE.DLL byte-identical to main's build (worktree of 0ee553a with a copy of
  raw/ from before the round); the DLLs' .edata (export names) differ by the new names, the EXE's .idata by the LUA /
  IMUSE import hints and its .rdata by the build time string; the EXE imports the same 332 names.
* rename_refs.py once per batch and `--difftest` once per batch: build/overrides.c, build/overrides_lua_core.c,
  build/difftest/lua_core/core_test.c, names/lua_internals.json / lua_new.json / orig3_lua_funcs.json,
  tools/gen_dll_module_names.py / gen_lua_new_names.py, names/imuse_internals.json, docs/ASM_REMAINING_2.md;
  build/im_names.txt and build/perf/imuse (imuse_diff_codec.c, README.md: `Im_DecodeSoundBlock`) by the one-pass script
  of orig-5 (`o5/rr_extra.py`; build/mixdiff has none of the names). imuse_diff_codec.c looks the function up by its
  export name in both DLLs, so like the earlier renames there it needs an assembled imuse_a.dll that exports the
  current names. A grep of the whole tree
  (except src/, raw/, names/, docs/notes/) for every old name with a `_` prefix or `__x` suffix finds none; no
  token-pasted uses. raw/<prog>/functions has no old name outside comments after each export.
* names/orig_modules.json: the pins of the renamed functions (orig_batch.py), so every function stays in its file.
* tools/orig_history.py knows the orig-7 batches (2756 renames from the earliest names).
* One plate comment that named an old function was updated (callC's "used by luaD_call / luaD_callC", as in
  names/orig3_lua_funcs.json, which rename_refs updated); no other plate comment names an old name.
* build/difftest/lua_core (2000 cases): 0 differences on this branch and on main.

## Checks

Clean-room (`run.py decomp`; 5322 tests, another session is adding expected files). Each run of this branch was
followed by a run of main's build (worktree of 0ee553a, raw/ from before the round); `run.py compare` of the two logs:

| build | this branch | main, run right after | compare of the two logs |
|---|---|---|---|
| LUA.DLL function batch | 6 of 5322 differ (sound_fade, gl1_say_right_edge, ims_voices, ims_save, ims_save_voice, rnd_say_low) | the same 6 | 0 of 5324 differ |
| LUA.DLL final (functions + globals) | 6 (ims_cache instead of sound_fade) | 6 (with sound_fade) | 2 of 5324: sound_fade (after "1 0 1 64 120 67" / "1 0 1 64 127 64"), ims_cache (keep_after "0" / "1") |
| final build (LUA + IMUSE) | 6 (sound_fade, gl1_say_right_edge, ims_voices, ims_save, ims_save_voice, rnd_say_low) | 7 (the same and ims_cache) | 2 of 5324: ims_ids (id_plus_1 0 / 1), ims_cache (keep_after "1" / "0") |

The three values that move were run alone (`run.py decomp --only T`, three times for each build, alternating, final
build against main's): ims_ids differs from the reference alone for both builds with the same three values every time
(by_id / set_by_id / stopped_by_id: the test depends on the sounds the earlier tests leave), sound_fade gives after
"1 0 1 64 120 67" for both builds every time, ims_cache gives keep -216 for both builds every time and keep_after "1"
or "0" from run to run for both (this branch 0 / 1 / 1 differing values, main 1 / 0 / 1). These are the timing values
the earlier rounds saw (sound_fade, ims_ids|id_plus_1, ims_cache|keep_after); the other differences are the other
session's new / changing tests, the same for both builds, whose .text / .data / .rdata are byte-identical.

## What is left

See [orig_summary.md](orig_summary.md): the names that stay are the platform layer, helpers the remaster inlined,
v1.01-only code and the runtime.
