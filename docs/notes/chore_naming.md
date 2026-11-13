# chore_naming: names, types and structures for CHORE.DLL (branch `chore-naming`, 2026-11-09/10)

CHORE.DLL is the costume / chore library of the GrimE engine (one source file, `C:\grimsrc\libs\chore\Costume.c`,
assert strings). Before this round 197 of its 264 functions were `FUN_`; 152 of those are dead copies of the MSVC 6 C
runtime (`names/lib_replace.json` "dead"), 6 host-replaced runtime functions ("host"), 39 real code.

## Sources

* **The remaster's `libchore.so`** (`C:\GOG Games\Grim Fandango Remastered\libchore.so`, i386 ELF, *not stripped*):
  the same Costume.c built with gcc. Its symbol table gives the original names of the exports, of the static functions
  gcc did not inline (`Cos_NewEntry`, `FreeCostume`, `AddKey`, `CompareKeys`, `AdvanceChoreTracks2`, `Cos_Terminate`,
  `Cos_Startup`, `Cos_Shutdown`) and of every global (`aCostumes`, `maxCostumes`, `aComponentTags`, `pcosHS`,
  `aParseLine`, `aTagLookups`, ...). The record offsets are the same (checked on `Cos_NewEntry`, `Cos_Terminate`).
  It has no DWARF, so field names come from the asserts.
* The assert strings of the DLL (`pChore->aChoreTracks`, `pCTrack->aKeys`, `pInstance->aInstanceData`,
  `pInstance->aChoreInstances`, `pComponent->apStateBitmaps`, `numComponentTags + 1 <= maxComponentTags`, ...).
* The EXE side (its handler names: `*_OnKey`, `*_Create`, `*_Stop`, `*_EditKey`, `*_NewInstance`, slot numbers in the
  plate comments of names/exe_pass3.json) and the text costume files (`.cos`, e.g. `olivia_talks.cos` in DATA00x.LAB).

## Naming scheme

* Exports keep their export names. Internal functions are `Cos_<Verb>` (Costume.c) and `Chore_<Verb>` for the two chore
  key functions (`Chore_AdvanceTime`, already named, and `Chore_ApplyKey`). Where libchore.so has the original static
  name the `Cos_` form of it is used and the plate comment says so (`FreeCostume` -> `Cos_FreeCostume`, `AddKey` ->
  `Cos_AddKey`, `CompareKeys` -> `Cos_CompareKeys`; `Cos_NewEntry`, `Cos_Terminate`, `Cos_Startup`, `Cos_Shutdown`
  are the original names; `AdvanceChoreTracks2` stays `Chore_AdvanceTime`).
* **CHORE.DLL's own copies of C runtime functions that are still referenced are `msvc_<name>`** (`msvc_strncpy`,
  `msvc_strrchr`, `msvc_sscanf`, `msvc_memmove`, `msvc_bsearch`, `msvc_strchr`, `msvc_stricmp`, `msvc_qsort`,
  `msvc_shortsort`, `msvc_qsort_swap`, `msvc_fpmath`, `msvc_fpclear`, `msvc_cfltcvt_init`, `msvc_CPtoLCID`), not the
  plain runtime name, for three reasons:
  1. tools/build_src.py puts a function with a plain runtime name (`qsort`, `_stricmp`, `strncpy`) into `crt.c`, which is
     left out of the link (the host runtime replaces it): the private `qsort` copy that `Cos_AddKey` calls would vanish;
  2. the rebuilt chore.dll exports every symbol (`--export-all-symbols`) and the EXE links against libchore.a before the
     system libraries, so a chore.dll `qsort` / `_stricmp` would capture the EXE's own calls;
  3. a call to plain `sscanf` binds to mingw's own sscanf, not msvcrt's (see the `_input` note in build/overrides.c).
  The six host functions keep their thunks: names/lib_replace.json "aliases" now maps `_msvc_strncpy` -> `_strncpy` etc.
  (instead of `_FUN_100055a0`), so they still jump through the msvcrt import table. `msvc_stricmp` stays hand-written
  in build/overrides.c (host `_stricmp`, sign only).
* Globals: `g_` + the bridge's Hungarian prefix + the original name (`g_aCostumes`, `g_nMaxCostumes`,
  `g_pSvcChore` = pcosHS, `g_szParseLine` = aParseLine, `g_pfnInstanceHook` = instanceHook, ...); the plate comment of
  each gives the original name. The bridge refuses `g_b` for an `int` and `g_n` for a `uint`, hence `g_nCosInitialize`
  (bcosInitialize), `g_dwNumComponentTags` (numComponentTags).
* Struct field names follow the bridge's Hungarian rule (it renames fields itself: `aName`, `dwNumTracks`,
  `pChoreTracks`); where the assert names an array (`aChoreTracks`) the field is `p<Name>`.

## Structures

All in the Ghidra program `/CHORE.DLL` and defined for the build in `build/compat.h` (with size asserts). Handles are
index + 1 (0 = none) for costumes (`Cos_HandleToIndex` / `Cos_IndexToHandle`) and instances (`Cos_InstHandleToIndex`).

**Costume** (0x3c, `g_aCostumes`, `g_nMaxCostumes` records, 32 at start-up, grows by 8):

| off | field | |
|---|---|---|
| 0x00 | `char aName[32]` | file name without directory |
| 0x20 | `dwField_0x20` | not used by CHORE.DLL |
| 0x24 | `int nId` | serial number (`g_nNextCostumeID`, Cos_NewEntry) |
| 0x28 | `uint dwNumComponents` | |
| 0x2c | `CosComponent *pComponents` | |
| 0x30 | `uint dwNumChores` | |
| 0x34 | `Chore *pChores` | |
| 0x38 | `int nFree` | 1 = slot free; also set when a load fails |

**CosComponent** (0x40): `aName[32]`; 0x20 `nTag` (index into `g_aComponentTags`); 0x24 `nData` (the EXE's component
data given to Cos_RegisterComponent, copied into each instance's instance data); 0x28 `nHash` (number of earlier
components with the same tag and name, the "Hash" column of the .cos file); 0x2c `nParent` (component index, -1 = root);
0x30 `dwNumStates`, 0x34 `pStateValues`, 0x38 `ppStateNames`, 0x3c `apStateBitmaps` (state-based tags only;
`CosStateBitmap` 0x14 = the EXE's 16-byte description + 0x10 `nMunged`, the bitmap munger's result).

**Chore** (0x2c): `aName[32]`; 0x20 `dwNumTracks`; 0x24 `ChoreTrack *pChoreTracks`; 0x28 `dwLength` (ms; a new chore is
15 ms long).

**ChoreTrack** (0x10): 0x00 `nCompNum` (component index; the file's index is mapped through `g_aComponentLookups`);
0x04 `dwLastKeyTime`; 0x08 `dwNumKeys`; 0x0c `ChoreKey *pKeys` (sorted by time).

**ChoreKey** (8): 0x00 `dwTime` (ms), 0x04 `nValue` (for float tags the bits of a float).

**CosInstance** (0x14, `g_aCostumeInstances`, `g_nMaxInstances` records): 0x00 `nCostume` (costume index, -1 = free);
0x04 `ChoreInstance *pChoreInstances` (one per chore); 0x08 `nUserData` (the EXE's actor); 0x0c `int *pInstanceData`
(one per component, from the tag's NewInstance handler); 0x10 `nFree`.

**ChoreInstance** (0x0c): 0x00 `dwFlags` (1 playing, 2 looping, 4 advanced by Cos_InstUpdateChores, i.e. not manual);
0x04 `nChore`; 0x08 `nTime` (ms played).

**ComponentTag** (0x5c, `g_aComponentTags`, `g_dwMaxComponentTags` = 32 records): 0x00 `nId` (four-character id, e.g.
'MMDL', 'cmap', 'MAT '); 0x04 `nKind` (0 state based "fs", 1 int, 2 float); 0x08 `aName[32]` ("MAIN RDroid Thing
(.3DO)"); 0x28 `nUserData`; seven handlers copied from the EXE: 0x2c `pfnOnKey` (slot 0, Chore_ApplyKey), 0x30
`pfnCreate` (1, CosUtil_AddComponent), 0x34 `pfnDestroy` (2, Cos_FreeComponent), 0x38 `pfnStop` (3,
Cos_InstStopChore(s)), 0x3c `pfnEdit` (4, CosUtil_AdjustComponent), 0x40 `pfnNewInstance` (5, Cos_CreateCosInstance
/ Cos_FreeInstanceData), 0x44 `pfnSave` (6, Cos_SaveInstance / Cos_RestoreInstance); 0x48..0x5b not used.

**GrimServices** (0x70): copied from the EXE's type; `g_pSvcChore` points at the host table (pAssertFail +0x18, pAlloc
+0x20, pFree +0x24, pRealloc +0x28, pFopen +0x30, pFclose +0x34, pFgets +0x3c, pFprintf +0x54).

Other globals: `g_szParseLine` (0x400-byte line buffer), `g_aTagLookups` (100 tag indices: file tag index -> registered
tag), `g_aComponentLookups` / `g_dwNumComponentLookups`, the hooks `g_pfnCompNotifier`, `g_pfnBitmapMunger`,
`g_pfnInstanceHook`, `g_pfnSaveHook`, `g_pfnSaveVerify`, `g_nLineNum`, `g_nNextCostumeID`, `g_nCosInitialize`,
`g_nCosStartup`. `g_aTagLookups` is typed `uint` (the bridge does not apply the array type), Ghidra prints
`(&g_aTagLookups)[i]`.

The module interface Cos_Initialize fills: Cos_Initialize, Cos_Terminate, Cos_Startup, Cos_Shutdown, Cos_Save,
Cos_Restore, 0, 0.

## Batches

* `names/chore_functions.json`: names, plate comments and tags of the 39 unnamed functions with real code, the 6 host
  runtime functions and the referenced runtime copies.
* `names/chore_globals.json`: the globals (names, types, comments).
* `names/chore_types.json`: prototypes (Cos_Save / Cos_Restore / Cos_SaveInstance / Cos_RestoreInstance take `void *io`:
  the bridge cannot resolve `code *`) (all `__cdecl`, parameter counts and void-ness as before, checked against the
  previous functions.h), incl. locked prototypes for the functions defined in build/overrides*.c: re-decompiling with
  the new callee types made Ghidra infer other signatures for unlocked ones (Cos_ReadComponentsSection got 17
  parameters), which then conflicted with the hand-written definitions.
* `names/chore_comments.json`: plate comments for the exports.
* The structs are not in a batch (apply_names.py cannot create types): create them from the tables above (or
  build/compat.h) before applying chore_globals.json / chore_types.json to a fresh project.

Tool changes: `tools/ghidra_api.py` `post()` puts `program` into the query string (the bridge ignores it in the JSON body
and wrote to its current program, the EXE, which `switch_program` did not change); `tools/apply_names.py` handles the
bridge's `prefix_type_mismatch` like `name_quality`, re-applies an existing label without failing and sets a data
plate comment with `set_comment` (`set_plate_comment` only takes functions).

## Stack purge: why 11 functions were hand-written (build/overrides_chore_naming.c, removed 2026-11-13)

**Resolved 2026-11-13:** the purges were set from the RET instruction with `run_script_inline` (104 DLL functions,
BUILD_NOTES "Stack purges"); the generated text of the 11 functions has no `in_stack_` reads any more, the file is
gone and the clean-room suite gives 0 of 5327 differences. The section below is the history.

Locking the prototypes (names/chore_types.json, all `__cdecl`, correct parameter counts) broke the decompilation of
the *callers* of some of them: Ghidra now reads their parameters after such a call at the wrong stack offset
(`in_stack_00000024` for `value` in CosUtil_AddFSKey, `hCostume = in_stack_00000008` in Cos_FreeCostume, and silently
the wrong parameter in Cos_InstRescue: `Cos_InstHandleToIndex(hCostume)` instead of `(hInst)`). The first clean-room
run of the typed build showed it (321 of 5107 tests differ). Experiments (`force_decompile` of CosUtil_AddFSKey while
changing Cos_AddKey): the caller's text does not change with the callee's calling convention (`__cdecl`, `__stdcall`,
`__thiscall`), its parameter list (none, one, four) or the caller's own prototype; it follows the stack purge stored
in the Ghidra function record (Cos_AddKey behaves as if it popped 16 bytes, CosUtil_PtrFromHandle / Cos_HandleToIndex /
Cos_InstIndexToHandle 4; the code ends in a plain `RET`). While a callee's signature was not locked the decompiler
recovered the real stack change itself; with a locked one it trusts the stored purge. The functions that were
`__cdecl` in main already (Cos_InstHandleToIndex, Chore_ApplyKey, ...) have a correct purge and their callers are fine.
The bridge has no way to set a purge (no endpoint; `run_script_inline` is disabled; `delete_function` +
`create_function` fails with a ConcurrentModificationException on the Swing thread; `run_analysis` would create 48
new functions).

So the 11 compiled functions that read the stack after a call to a function with a bad purge are hand-written in
`build/overrides_chore_naming.c`: Cos_InstRescue, CosUtil_Write, Cos_CreateCosInstance, Cos_RegisterComponent,
Cos_RemoveComponent, CosUtil_DeleteComponent, CosUtil_AddFSKey / AddIntKey / AddFloatKey, Cos_FreeCostume,
Cos_FreeInstanceData. Their bodies are main's decompilation (the clean-room-checked text), with the new function
names; parameters are copied into locals of the old types, and macros give the globals their old Ghidra views, so the
code is the same. (Cos_LoadEntry, Cos_Save / Cos_Restore, the Cos_New*Tag functions and the Cos_Read*Section loaders,
also affected, were hand-written already.) The set was found by scanning the disassembly of every live function for
stack accesses after a call to a newly locked function that was not `__cdecl` before, and by comparing the number of
uses of each parameter per function with main (scratchpad scripts, see the report); the clean-room run is the check.

**For the other programs:** setting a prototype on a function whose purge Ghidra never computed correctly can break
its callers the same way, silently. After a prototype batch, look for new `in_stack_` / changed parameter uses in the
callers. The fix in Ghidra would be `Function.setStackPurgeSize(0)` for the functions of names/chore_types.json that were not `__cdecl` in main (seen wrong: Cos_AddKey, CosUtil_PtrFromHandle, Cos_HandleToIndex, Cos_InstIndexToHandle; all of them are `__cdecl` with a plain `RET`); after that the overrides can go.

## Override files touched

build/overrides_chore_naming.c (new, see above), build/overrides.c (`msvc_stricmp`), build/overrides_logic_chore.c, build/overrides_s1_chore.c,
build/overrides_asm_o2_chore.c, build/overrides_asm_s5_chore.c (comments): renamed definitions, `OVERRIDES:` lines and
calls; `DAT_100143xx` accesses became the named globals, the service table calls `g_pSvcChore->pX`; the tables are
used as `(int)g_aCostumes + i * 0x3c` so the hand-written offset arithmetic does not depend on the Ghidra type.

## What stays unnamed

The 152 dead runtime copies (`names/lib_replace.json` CHORE.DLL "dead": `FUN_10005f50` and everything from 0x10006120
on: start-up, locale, stdio, heap, the scanf engine `FUN_10006b30` that build/overrides.c replaces with msvcrt's
sscanf). Nothing live calls them.

## Results

* `python -I tools/stats.py`: CHORE.DLL 264 functions, **67 -> 112 named, 197 -> 152 `FUN_`**; the 152 left are exactly
  the dead runtime copies of names/lib_replace.json. All 39 unnamed functions with real code are named, plus the six
  host runtime functions, the referenced private runtime copies (`msvc_*`) and `msvc_CPtoLCID`; plate comments on
  every non-runtime function, tags `chore` + topic (`costume`, `component`, `tag`, `instance`, `keys`, `cosfile`,
  `module`, `savegame`, `export`).
* Build: all four programs LINKED, CHORE.DLL stubs.txt unchanged (the same 16 dead runtime functions); a second
  regeneration from the Ghidra project gives the same src/CHORE.DLL and a byte-identical chore.dll.
* Names-only stage (before types and prototypes): every function body identical to main after renaming (scratchpad
  `cmpfuncs.py`, whitespace-insensitive).
* Clean-room (`run.py decomp`): **0 of 5118 tests differ, 5118 the same** (the suite has 5118 tests now) with the final
  build. An earlier run of the typed build without overrides_chore_naming.c: 321 of 5107 differ (the stack purge
  problem above); a run with only the function names: 411 differ, caused by the EXE side (below), not by CHORE.DLL.

## Note for the merge: the EXE's raw/ is ahead of main's src

The first `export_changed.py` of this round also exported 212 EXE functions from the pending journal (149 EXE
addresses touched before this round, not by this branch). The Ghidra project has 34 EXE function renames that are not
in main's src (e.g. `Lua_GetActorCostume` -> `sputLua_GetActorCostumeL`, `Vec3_Sub` -> `Matrix34_TransformPoint`,
`BitmapComponent_Create` -> `BitmapRequester`) and no batch in names/ has them. raw/GRIMFANDANGO.EXE is now that
newer state while src/GRIMFANDANGO.EXE on this branch is main's, so a link with them together stubs the 18 renamed
Lua functions that the data sections point at (`sputLua_*` -> ud2: the 411 failures). For the tests of this branch
the link ran with a copy of raw/GRIMFANDANGO.EXE/functions.json that has main's names (restored afterwards); the EXE
src is not regenerated on this branch. Regenerating the EXE from the project (the normal flow) picks the renames up.
