# orig-4: the software rasteriser, more globals, the start-up chain (branch `orig-4`, 2026-11-10)

Fourth round after [orig_names.md](orig_names.md), [orig_globals.md](orig_globals.md) and [orig_3.md](orig_3.md):
the remaster's unstripped `GrimFandango` (Linux) names the 351 generated `rdRaster_*` functions of the software
rasteriser (`rdNRaster_*`, `rdZRaster_*`, `rdAFRaster_*`), the rasteriser's globals, the start-up / module chain of
`Main_Startup`, and some corrections. Names and comments only (no types, no prototypes); exports, the MSVC runtime
and zlib untouched.

## Method

* **The rasteriser by structure, not by similarity.** The three dispatchers decide on the same tests in both builds:
  `rdCache_DrawFaceN` (no z-buffer) and `rdCache_DrawFaceZ` (z-buffer) switch on geometry mode (1 points, 2 wireframe,
  3 solid, 4 textured; 4 falls back to 3 without the material's +0 bit 3), lighting mode (0, 1 / 2, 3), texture mode
  (0 affine, 1 perspective), the mask bit (material +0x1c -> +0 bit 0) and the translucency bit (face +4 bit 1);
  `rdActive_AddActiveFace` (the occlusion path) the same without translucency. Every call of the v1.01 switch was
  given the remaster call under the same conditions (scratchpad `o4/dskel.py`, a skeleton of both switches): 32 + 32
  `DrawNGon*` entries and 16 `rdAFRaster_SetupNGon*`. Example: geometry 3, lighting 0, not translucent is
  `rdRaster_Draw16_FlatLit` -> rdNRaster_DrawNGonLS, translucent `rdRaster_Draw16_TexLit` -> rdNRaster_DrawNGonTLS;
  textured affine, lighting 0, no mask, not translucent `rdRaster_Draw16_TexLit_4` -> rdNRaster_DrawNGonLAT (the
  positional vote of orig-3 had it as TLAT: the remaster tests the bits in the other order, so the vote crossed the
  pairs).
* **Their callees by role** (scratchpad `o4/rcalls.py`, `o4/rmap.py`): in each pair the gradients call
  (`rdRaster_Grad_Flat*` / `rdRaster_SetupPoly*` -> `*_CalcAffineGradients` / `*_CalcPerspGradients`), the first and the
  second edge set-up call (`SetupLeftEdge*` / `SetupRightEdge*`), the call in the 8-bit and in the 16-bit branch
  (`if (bpp == 8)` / `== 0x10`: `DrawScanLine*_8` / `_16`; the remaster inlined some of them, its out-of-line symbol has
  the name), the span and edge functions `rdAFRaster_SetupNGon*` stores (`rdAFRaster_DrawNGon*`,
  `rdAFRaster_SetupEdgeNGon*`), the span calls of those, and the advance functions stored with side flag 1 / 0
  (left / right). A v1.01 function that lands in two remaster slots is a copy the linker folded (identical code:
  `rdRaster_Span_Flat` is the 8-bit scan line of both LS and FS, `rdRaster_EdgeStepFlat` the left and right advance of
  LW, LS and FS) and keeps its name. The body similarity (difflib ratio of the token streams) was only a sanity check:
  among the 30 near-identical variants of a kind it picks the structural partner first in about half the cases, so it
  says nothing on its own; spot checks of bodies (mask test `texel != 0`, alpha map, light table) agree with the slots.
* **Globals from statements** (scratchpad `o4/stmt.py`): in paired functions an assignment `GLOBAL = RHS;` whose RHS,
  normalised (casts dropped, locals `V`, `+ -1` as `- 1`), is the same and unique on both sides gives the left side's
  name. That settled 43 rasteriser globals exactly; the perspective group (`aOneOverZ` / `aUOverZ` / `aVOverZ`,
  `dOneOverZdX` .. `dVOverZdY`, the `*Step` = `d*dX * 16`, the rounding modifiers) and the scan-line statics of
  `rdNRaster_DrawScanLineNGonGIT_16` (`oneOverZ`, `curZ`, `endU`, `numSubdivisions`, `startScrap`, ...) were read off
  the code side by side, statement by statement. The token-alignment vote (`galign2.py`, now `o4/galign3.py`, which
  splits a remaster static that several files have by the family of the function, `DUP:aVertices@rdNRaster`) is
  unreliable inside these functions: it gave `aVOverZ` for v1.01's 1/z array (`aOneOverZ`), `rdZRaster_mipMapNum` for
  `rdZRaster_zScaleShift`, `rdNRaster_dUOverZdX` for `dOneOverZdX`; none of those votes was taken.
* **Widening the alignment.** The new pairs fed back into the global vote and the "only unpaired user of a matched
  global" pin (`fpin.py`) four times; each new candidate was looked at in both texts (scratchpad `o4/pv.py`, `o4/cg.py`).
  That led from `rdOpen` / `rdClose` and the frame counters to the whole start-up chain: `Grim_Init` is Main_Startup
  (one of the open doubtful ones: the same sequence, developer key compared with "TRUE" and "pl", rdStartup / rdOpen,
  stdDisplay_Startup, the four grimlib callbacks, grimlib_FindResources), its module-interface fillers
  (`IMuseModule_Init` is PolyglotInitialize: it fills the polyglot interface; `EngineModule_Init` is
  grimlib_GameInitialize), the callbacks it sets (`DebugLog_Init` is grimdemo_EnableDebugging, the five print functions
  by their host-service slot +4 .. +0x14) and the host services (`Services_InitDefaults` HostServicesInitialize,
  `Services_SetCurrent` stdStartup).
* Names: the remaster's as they are; the rasteriser statics that several of its files have get the file as prefix
  (`numVertices` of rdNRaster.c -> `g_nRdNRaster_numVertices`, of rdZRaster.c -> `g_dwRdZRaster_numVertices`), the
  unique ones not (`g_dwFixU`, `g_dwEndScrap`). Remaster stubs of the platform layer (std3D_StartScene,
  stdDisplay_SetPalette, grimPlat_SaveFileRequest) were given by their call slot, as orig-3 did for std3D.

## Batches and counts

| program | batch | renames | of which FUN_ | generated rdRaster_ | existing names replaced |
|---|---|---|---|---|---|
| GRIMFANDANGO.EXE | names/orig4_exe_funcs.json (rasteriser + 8 pins) | 283 | 15 | 260 | 8 |
| GRIMFANDANGO.EXE | names/orig4_exe_funcs2..5.json (frame counters, start-up chain) | 51 | 0 | 0 | 51 |
| GRIMFANDANGO.EXE | names/orig4_exe_globals.json (rasteriser, Smush, sputTime, ...) | 150 | | | 30 (+2 same name) |
| GRIMFANDANGO.EXE | names/orig4_exe_globals2..4.json | 26 | | | 6 (+1 same name) |
| IMUSE.DLL | names/orig4_imuse_funcs.json | 1 | 0 | | 1 |
| IMUSE.DLL | names/orig4_imuse_globals.json | 10 | | | 2 (corrections) |

Functions (`python -I tools/stats.py`):

| program | named before | after | of which auto/module-level | FUN_ before | after |
|---|---|---|---|---|---|
| GRIMFANDANGO.EXE | 2344 | 2359 | 378 -> 119 | 327 | 312 |
| LUA.DLL | 689 | 689 | 43 | 163 | 163 |
| IMUSE.DLL | 301 | 301 | 28 | 150 | 150 |

Globals referenced by the decompiled code (scratchpad `gcount.py`, as before):

| program | globals | named before | after | DAT_/PTR_/UINT_ before | after |
|---|---|---|---|---|---|
| GRIMFANDANGO.EXE | 2274 | 590 | 727 | 1684 | 1547 |
| IMUSE.DLL | 366 | 92 | 100 | 274 | 266 |
| LUA.DLL | 367 | 69 | 69 | 298 | 298 |

The rasteriser: 260 of the 351 generated names are original now, plus 15 FUN_ of the occlusion path and
`rdroid_BuildMathTables` -> rdRaster_Startup. The 91 left: 86 per-texture-width span fillers that only v1.01 has
(`rdRaster_Span16_TexLitZw*`, `_TexZw*`, `SpanR16_Tex*`, `SpanP16_Tex*`, chosen by a switch on the texture width 8 ..
0x100; the remaster has one generic span per variant), the two z-write spans `rdRaster_SpanR_FlatZw` / `_2` (inlined in
the remaster), and the three folded copies above; also 5 FUN_ edge advances that are folded (one function in both
slots, or shared by LIT and FIT).

Hand-made names replaced (the plate comment keeps "was X", the batch "old"), e.g. `rdroid_Open` -> rdOpen,
`rdCanvas_FlushSpans` -> rdActive_FlushSpans, `Smush_Open` -> SmushPlay_StartMovie, `Costume_SaveChoreListFile` ->
sputCostume_SaveHook (a doubtful one: same body and strings), `Actor_CanSeePoint` -> sputActor_CanActorSeePoint,
`rdroid_BeginFrame` -> rdAdvanceFrame, `rdCamera_ClearCanvas` -> rdCamera_AdvanceFrame, `rdCamera_ResetStats` ->
rdModel3_ClearFrameCounters (it clears the model counter), `Grim_Init` -> Main_Startup, `IMuseModule_Init` /
`_Stop` -> PolyglotInitialize / polyglot_shutdown, `EngineModule_Init` / `_Terminate` / `_Stop` -> grimlib_Game*,
`Display_Flip` -> stdDisplay_Update (also in build/fastpaths.c); globals `g_nRdRasterVertCount` / `StartVertex` /
`EndVertex` / `StepA` / `StepB` / `g_pRdRasterVerts` -> rdNRaster's numVertices / yMinVert / yMaxVert /
leftVertexStep / rightVertexStep / aVertices, `g_nMovieFullscreen` -> SmushLooping (it is the loop flag),
`g_nMoviePlaying` -> SmushPlaying, `g_poolList` -> pFirstPool, `g_pSvcText` -> pTextHS, `g_pSvcIMuseModule` ->
polyglot's pHS. Full lists: the batches.

IMUSE.DLL: `Im_FireTriggers` is TgProcessMarker (same body; its static text copy is TgProcessMarker.textCopy);
`panTable` and `mixBufSize` of MxInitialize; the lip-sync slots of LoadLip. Correction of the orig-globals round:
10031e78 / 10031e7c are lipSfx2ID / lipSfx3ID (sound ids compared and cleared in LoadLip and iMUSE_GetPhoneme; the
remaster's lipStreamID / lipSfx1ID / lipSfx2ID / lipSfx3ID are four consecutive ints as here), not lipSfx2Data /
lipSfx3Data, which are the 2000-byte buffers (now named with lipSfx1Data and lipStreamData). The old batch entry
(names/orig_imuse_globals.json) carries the new name and comment. Of the 150 FUN_ of IMUSE.DLL 124 are the MSVC
runtime (101 in crt_unnamed.c, 23 runtime helpers at 0x1000b8d0 and above that build_src puts into imuse_api.c:
fopen, putc, locks, sprintf); 26 are iMUSE code (music-script state, the timer set-up, lip-sync lookup, sound slot
helpers). None of those 26 got a pair: their remaster callers inlined them or the remaster's iMUSE differs there; the
new globals pin nothing new beyond TgProcessMarker.

LUA.DLL: nothing new. Of the 298 unnamed referenced "globals" 220 are used only by the MSVC runtime, most of the rest
are string literals and float constants the code takes the address of (`&DAT_1002bedc` is "", `&DAT_100261f0` a
format), the LState field pieces (+4, +8) and the v1.01 once-flag of luaT_setfallback.

## Doubtful list of orig-3

Settled: Grim_Init (Main_Startup), Costume_SaveChoreListFile (sputCostume_SaveHook), tmFuncs (it is the table
v1.01 passes as the immediate 0x10027d98 to lua_recognizelib; DAT_1002bf80 is a once-flag the remaster does not
have, so no global is tmFuncs). Still open: Win_WinMain, Display_Select (fpin points at Main_Startup again, but it is
the mode switch, not the start-up), Lab_ReadDirectory, Resource_OpenArchivesInDir, Actor_DrawShadowPlane,
SetFile_ParseSectors, LightEd_*, rdModel3_New, rdThing_DrawAlt, Collision_TestActorAgainstOthers,
LecShare_StartupModules / _Reset, Im_VimaDecompress, the dirty-rect statics (v1.01 MarkDirtyRect copies the rect into
statics the remaster does not have), loadLastSave, mlListSize, the struct fields (sou_fill_data, aFile, aView,
rdColormap_colorInfo fields). Also left: `Grim_OpenRegistry` / `Reg_Open` against wuRegistry_Startup (rewritten
in the remaster), `Str_ComparePtrs` (polyglot_strcmp, but v1.01 shares it with the registry code),
`Plat_ReturnTrue` / `LecShare_Nop` (shared empty functions), `StateImage_Draw` (SetupDraw is a part of it),
`Input_PollKeyboard` (UpdateKey is inlined into it), UINT_004f5a44 (one vote for stdDisplay_bOpen, contradicted by
its writer).

## Build and tools

* Regenerated src equal to the previous src after mapping old -> new (scratchpad `cmpg.py`) for all four programs
  after each batch; the one difference is a data label Ghidra renames itself after its target
  (`PTR_DAT_004dd040` -> `PTR_g_aHs_004dd040`, data symbol name only). All four LINKED, stubs EXE 42, LUA 58, IMUSE 9,
  CHORE 16. .text / .data / .rdata of the four binaries byte-identical to main's build (only the build time string, the
  DLL export tables and the EXE's IMUSE import hints differ).
* export_changed.py did not re-export Render_InitColorConstants (0x484c40), which writes sputRender_colorMap through
  an element address; it went through raw/touched.json. A check over raw/<prog>/functions found no old name outside
  comments after each export.
* scratchpad `fixplates.py` (old global names in function plate comments) has to be run with
  `MSYS2_ARG_CONV_EXCL='*'` from the MSYS2 shell: otherwise the `/v101/GRIMFANDANGO.EXE` argument is turned into a
  Windows path and nothing is updated (silently, 0 comments).
* tools/orig_history.py knows the orig-4 batches.
* build/difftest: `rename_refs.py --difftest` per batch. The rasteriser harnesses asm_q4 / q5 / q6 pasted
  `rdRaster_##n` from short names (`FN(K_SPAN, Span16_FlatZ)`), which no longer exist; their *_funcs.h list the full
  current names now, the macros paste `orig_##n` / `n`, run_all.sh takes the names as they are, and the mutate.py
  filters and the test's special cases use the full names.

## Checks

Harnesses (1 case each, as orig-3): asm_q4 67 cases, asm_q5 108, asm_q6 67, asm_s2, asm_p1, clipface, lua_core,
imuse_r1: 0 differences; r2 builds.

Clean-room (`run.py decomp`; the suite has 5319 tests, another session is adding expected files):

Each run of this branch was paired with a run of main's build (ea6e86a, built in a worktree, same expected files),
right after it. Every test that differs, differs identically for main's build (scratchpad `o4/crcmp.py` compares
the reported values): the differences are new or changed tests of the other session, and the .text / .data / .rdata
of the four binaries are byte-identical to main's.

| build | result |
|---|---|
| main, before the round | 2 of 5319 differ (gco_kf_badj, ims_ids), 5317 the same |
| EXE functions + globals batch 1 (orig4_exe_funcs, orig4_exe_globals) | 7 of 5319 differ (gco_kf_badj, gco_cos_bitmap, gco_font_kerned, gco_font_perm, gco_text_keys, ims_ids, ims_save_voice) |
| main, run right after | the same 7, identical values |
| final build (all EXE and IMUSE batches) | 9 of 5319 differ (gco_kf_badj, gco_cos_bitmap, gco_font_kerned, gco_font_perm, gco_text_keys, gl1_sound_pos_actor, gl1_sound_pos_max_below_min, ims_save_voice, smv_save_movie) |
| main, run right after | the same 9, identical values |

No test differs between this branch and main.

## What is left

* The rasteriser: the 86 v1.01-only per-width span fillers (no remaster counterpart), the folded copies and the
  z-write spans (above).
* EXE: 312 FUN_ (most in the runtime / LEC library range, as before), 1547 unnamed referenced globals; the alignment
  over all 1325 pairs is exhausted for votes that hold up (the rest are struct fields, contested statics, or votes the
  code contradicts).
* IMUSE.DLL: the 26 iMUSE FUN_ above; LUA.DLL: nothing the remaster can name.
* The doubtful list above.
