/* GRIMFANDANGO.EXE: every global / string symbol referenced by the decompiled code.
 * Named globals carry their Ghidra type. For DAT_/PTR_/s_ symbols Ghidra exported
 * no type; the type below is inferred from how the code uses the symbol
 * (see infer_global_types in tools/build_src.py) - fix it in Ghidra, not here. */
#pragma once
#include "ghidra_types.h"

/* ---- named globals (type from Ghidra) ---- */
extern float g_MatrixIdentity[12]; /* 0x004d75a0 */
extern int g_nIrisX; /* 0x004e8064 */
extern int g_nIrisY; /* 0x004e8068 */
extern float g_flGamma; /* 0x004e8070 */
extern int g_nBufferCount; /* 0x004e8074 */
extern uint g_dwRenderDebugFlags; /* 0x004e8078 */
extern float g_flAmbientLight; /* 0x004e807c */
extern int g_nDrawEnabled; /* 0x004e8080 */
extern int g_nRenderedSetup; /* 0x004e8084 */
extern int g_nNextPrimitiveId; /* 0x004e8394 */
extern int g_nSubtitleDefaultX; /* 0x004e8488 */
extern int g_nSubtitleDefaultY; /* 0x004e848c */
extern uint g_PrintLineTextCtx; /* 0x004e8498 */
extern uint g_SubtitleTextCtx; /* 0x004e84c8 */
extern uint g_TextObjectCtx; /* 0x004e84f8 */
extern uint g_ControlTable; /* 0x004e87c8 */
extern int g_nControlCount; /* 0x004e9238 */
extern char ** g_ppRequiredLabs; /* 0x004e99b0 */
extern int g_nRequiredLabCount; /* 0x004e9a28 */
extern int g_nResMemoryBudget; /* 0x004e9a2c */
extern uint g_ResTypeTable; /* 0x004e9a38 */
extern int g_nActorCapacity; /* 0x004e9c80 */
extern uint g_PhonemeTable; /* 0x004e9c88 */
extern int g_nPhonemeCount; /* 0x004e9df8 */
extern uint g_dwSpeechMode; /* 0x004e9dfc */
extern int g_nTextSpeed; /* 0x004e9e00 */
extern int g_nChoreFadeMs; /* 0x004e9e04 */
extern char g_szConfigKeyPrefix[8]; /* 0x004ea884 */
extern int g_nLightEdSelected; /* 0x004f0d10 */
extern float g_measuredFps; /* 0x004f44e4 */
extern int g_quitRequested; /* 0x004f5a0c */
extern int g_bWindowedMode; /* 0x004f5a20 */
extern bool g_bShowFps; /* 0x004f5a2c */
extern int g_bShowProfile; /* 0x004f5a30 */
extern void * g_pDisplayModes; /* 0x004f5a38 */
extern int g_fixedFrameMs; /* 0x004f5a48 */
extern uint g_dwFrameCounter; /* 0x004f5a58 */
extern int g_bDebugChordHeld; /* 0x004f5a88 */
extern char ** g_ppRegValueNames; /* 0x004f5ea0 */
extern uint g_dwRegValueCount; /* 0x004f5ea4 */
extern void * g_pRegRootKey; /* 0x004f5eb0 */
extern void * g_pRdCurrentCamera; /* 0x007f0fc8 */
extern void * g_pRdCurrentModel; /* 0x007f30d4 */
extern void * g_pRdCurrentThing; /* 0x007f31e0 */
extern int g_nRdRasterVertCount; /* 0x007f424c */
extern int g_nRdRasterStartVertex; /* 0x007f42e8 */
extern int g_nRdRasterStepA; /* 0x007f42ec */
extern int g_nRdRasterEndVertex; /* 0x007f42fc */
extern float * g_pRdRasterVerts; /* 0x007f4308 */
extern int g_nRdRasterStepB; /* 0x007f4394 */
extern void * g_pMainHwnd; /* 0x007f6088 */
extern void * g_pDebugFont; /* 0x007fa7a8 */
extern int g_nDisplayDeviceOpen; /* 0x00803f84 */
extern int g_nDisplayModeOpen; /* 0x00803f88 */
extern uint g_dwDisplayDeviceCount; /* 0x00803f8c */
extern void * g_pDisplayDevice; /* 0x00803f90 */
extern uint g_dwVideoModeCount; /* 0x00803f94 */
extern void * g_pVideoMode; /* 0x00803f98 */
extern void * g_pDirectDraw; /* 0x00803fa4 */
extern void * g_pDDrawPrimary; /* 0x00803fa8 */
extern void * g_pDDrawBack; /* 0x00803fac */
extern int g_nInputEnabled; /* 0x00805f9c */
extern int g_nInputAcquired; /* 0x00805fa8 */
extern void * g_pDirectInput; /* 0x00805fac */
extern void * g_pDInputMouse; /* 0x00805fb0 */
extern void * g_pDInputKeyboard; /* 0x00805fb4 */
extern void * g_pD3dDevice; /* 0x008061e4 */
extern void * g_pDirect3D; /* 0x00806608 */
extern uint g_dwD3dRenderFlags; /* 0x00806920 */
extern uint g_dwD3dDriverCount; /* 0x00806928 */
extern void * g_pD3dDriver; /* 0x0080692c */
extern void * g_pD3dTextureList; /* 0x00806948 */
extern void * g_pD3dExecuteBuffer; /* 0x00806954 */
extern GrimServices g_ResFileServices; /* 0x00825e90 */
extern char g_szDialogFileName[128]; /* 0x008a86f0 */
extern void * g_pfnIMuseSaveHook; /* 0x008a87a8 */
extern void * g_pfnIMuseRestoreHook; /* 0x008a87ac */
extern int g_nDebugKeysEnabled; /* 0x008a8c54 */
extern GrimServices * g_pSvcEngineModule; /* 0x008a8c74 */
extern char * g_pSaveFileName; /* 0x008a8c88 */
extern GrimServices * g_pSvcIMuseModule; /* 0x008a8c98 */
extern char * g_pPolyglotText; /* 0x008a8ca0 */
extern ushort g_wColorTable; /* 0x008a9530 */
extern int g_nCameraActor; /* 0x008c9530 */
extern GrimServices * g_pSvcRender; /* 0x008c9768 */
extern uint g_dwIrisStartMs; /* 0x008c9774 */
extern float g_flIrisDurationMs; /* 0x008c9778 */
extern float * g_pCameraSetup; /* 0x008c977c */
extern int g_nZBufferEnabled; /* 0x008c9784 */
extern uint g_dwRenderFlags; /* 0x008c9798 */
extern void * g_pDirtyRectList; /* 0x008c979c */
extern void * g_pCanvas; /* 0x008c97a8 */
extern void * g_pTempSurface; /* 0x008c97ac */
extern void * g_pBackgroundSurface; /* 0x008c97b0 */
extern void * g_pZBufferSurface; /* 0x008c97b4 */
extern void * g_pfnFlipCallback; /* 0x008c97bc */
extern ushort g_wTextColors[3]; /* 0x008c97c0 */
extern void ** g_pDirtyRectPool; /* 0x008c97ec */
extern int g_nFullRedrawPending; /* 0x008c97f0 */
extern void * g_pCacheRectList; /* 0x008c97f4 */
extern int g_nDirtyRectCount; /* 0x008c97fc */
extern void * g_pRenderedSet; /* 0x008c9800 */
extern char g_szDialogOpenDir[260]; /* 0x008c9858 */
extern char g_szDialogSaveDir[260]; /* 0x008c9960 */
extern void * g_pfnSpewStartup; /* 0x008c9a64 */
extern void * g_pfnSpewShutdown; /* 0x008c9a68 */
extern void * g_hSpewDll; /* 0x008c9a6c */
extern GrimServices * g_pSvcMemory; /* 0x008c9a70 */
extern void ** g_poolList; /* 0x008c9a80 */
extern GrimServices * g_pSvcFileutil; /* 0x008c9a90 */
extern void * g_pMovieSurface; /* 0x008c9aa0 */
extern char g_szMovieName[128]; /* 0x008ca000 */
extern int g_nMovieAvailable; /* 0x008ca084 */
extern int g_nMoviePlaying; /* 0x008ca088 */
extern int g_nMoviePaused; /* 0x008ca08c */
extern int g_nMovieStopRequested; /* 0x008ca090 */
extern int g_nMovieFullscreen; /* 0x008ca094 */
extern int g_nPrimitivesHidden; /* 0x008ca0b4 */
extern int g_nTranslationMode; /* 0x008ca140 */
extern void * g_pOverrideFont; /* 0x008ca14c */
extern void * g_pTextObjectList; /* 0x008ca150 */
extern void ** g_pTextObjectPool; /* 0x008ca154 */
extern int g_nTextObjectsFrozen; /* 0x008ca158 */
extern int g_nShutdownHookCount; /* 0x008ca160 */
extern void * g_pShutdownHooks; /* 0x008ca198 */
extern int g_nInputCaptured; /* 0x008ca1c4 */
extern char g_szExtraDataDir[128]; /* 0x008ca208 */
extern int g_nResNoPurge; /* 0x008ca30c */
extern void * g_pTalkingActors; /* 0x008ca310 */
extern int g_nDrawableActorCount; /* 0x008ca330 */
extern void * g_pDrawableActors; /* 0x008ca358 */
extern void * g_pActorTable; /* 0x008ca758 */
extern int g_nActorCount; /* 0x008ca75c */
extern void * g_pSelectedActor; /* 0x008ca760 */
extern int g_nTalkingActorCount; /* 0x008ca764 */
extern void * g_pShadowColormap; /* 0x008ca790 */
extern void ** g_pCostumePool; /* 0x008ca794 */
extern GrimServices * g_pSvcCostume; /* 0x008ca7a0 */
extern void * g_pShadowMaterial; /* 0x008cab38 */
extern int g_nLuaSystemTableRef; /* 0x008cab40 */
extern void * g_pfnLuaSaveWrite; /* 0x008cab70 */
extern uint g_dwMovieTime; /* 0x008cab74 */
extern int g_nLuaSaveStringCount; /* 0x008cab78 */
extern GrimServices * g_pSvcLua; /* 0x008cab84 */
extern void * g_pLuaFileFind; /* 0x008cab88 */
extern uint g_dwLuaGcTimerMs; /* 0x008cab90 */
extern uint g_dwTimerLastTick; /* 0x008caba0 */
extern uint g_dwTimerTotalMs; /* 0x008caba4 */
extern uint g_dwTimerFrameMs; /* 0x008caba8 */
extern float g_flTimerFrameSeconds; /* 0x008cabac */
extern uint g_CurrentSetRef; /* 0x008cabb0 */
extern void * g_pCurrentSet; /* 0x008cabb4 */
extern char g_szCurrentSetName[32]; /* 0x008cabe8 */
extern void ** g_pPositionedSoundPool; /* 0x008cb088 */
extern void * g_pPositionedSoundList; /* 0x008cb08c */
extern GrimServices * g_pSvcRoom; /* 0x008cb090 */
extern int g_nSkipSetupBitmaps; /* 0x008cb0a0 */
extern void * g_pSetActorLists; /* 0x008cb0ac */
extern float g_vEdgeFollowDir; /* 0x008cf260 */
extern int g_nShrinkVertexCount; /* 0x008cf270 */
extern void * g_pShrinkVertexSave; /* 0x008cf274 */
extern int g_nShrinkSectorCount; /* 0x008cf278 */
extern void * g_pShrinkSectorSave; /* 0x008cf27c */
extern void * g_pSectorList; /* 0x008cf280 */
extern GrimServices * g_pSvcText; /* 0x008d0878 */
extern void * g_pDefaultFont; /* 0x008d0988 */
extern void * g_pWinDialogs; /* 0x008d0998 */
extern void * g_pWinMainHwnd; /* 0x008d09d8 */
extern void * g_pWinMessageHooks; /* 0x008d09e8 */
extern int g_nWinMessageHookOn; /* 0x008d09ec */
extern int g_nWinQuit; /* 0x008d0a74 */
extern uint g_dwWinDialogCount; /* 0x008d0a78 */
extern void * g_hLightEdDialog; /* 0x008d3630 */
extern void * g_pLightEdSet; /* 0x008d3634 */
extern void * g_pLightEdMarkerActor; /* 0x008d3638 */
extern void * g_pDirectSound; /* 0x008d365c */
extern void * g_pDSoundPrimary; /* 0x008d3670 */
extern int * g_pMixAccum; /* 0x008dcdb0 */
extern int g_nDrawBoxMinX; /* 0x008ddf90 */
extern int g_nDrawBoxMinY; /* 0x008ddf94 */
extern int g_nDrawBoxMaxX; /* 0x008ddf98 */
extern int g_nDrawBoxMaxY; /* 0x008ddf9c */
extern uint g_dwRdCacheMeshCount; /* 0x008ddfa0 */
extern int g_nRdroidLightingMode; /* 0x00900000 */
extern GrimServices * g_pSvcRdroid; /* 0x00900004 */
extern int g_nRdroidGeometryMode; /* 0x00900008 */
extern int g_nRdroidOcclusionMode; /* 0x00900048 */
extern int g_nRdroidZBufferMode; /* 0x00900050 */
extern int g_nRdroidSortMode; /* 0x00900058 */
extern int g_nRdroid3DAccel; /* 0x0090005c */
extern int g_nRdroidTextureMode; /* 0x00900060 */
extern uint g_dwRdroidFlags; /* 0x00900064 */
extern uint g_PrimarySurface; /* 0x00901680 */
extern uint g_BackBuffer; /* 0x009055e0 */
extern GrimServices * g_pSvcMain; /* 0x00905ac0 */
extern void ** g_pOnExitEnd; /* 0x00906c10 */
extern void ** g_pOnExitBegin; /* 0x00906c14 */

/* ---- unnamed data (type inferred from use) ---- */
extern undefined4 in_stack_00000010; /* used by 1 fn(s), first 0x004ac720 */
extern undefined DAT_004891a0; /* used by 1 fn(s), first 0x00488fb0 */
extern code LAB_004af680;  /* code label (address only) */ /* used by 2 fn(s), first 0x004af6a2 */
extern undefined DAT_004ce808; /* used by 1 fn(s), first 0x004ce3e0 */
extern undefined DAT_004d5370; /* used by 1 fn(s), first 0x00477530 */
extern undefined DAT_004d5400; /* used by 1 fn(s), first 0x004775a0 */
extern undefined DAT_004d7530; /* used by 1 fn(s), first 0x0044f490 */
extern undefined DAT_004d7540; /* used by 1 fn(s), first 0x0044f490 */
extern undefined DAT_004d7600; /* used by 1 fn(s), first 0x0047bd20 */
extern undefined DAT_004d8340; /* used by 1 fn(s), first 0x004775a0 */
extern undefined DAT_004d8350; /* used by 1 fn(s), first 0x00477530 */
extern undefined DAT_004d8460; /* used by 1 fn(s), first 0x00479a00 */
extern undefined DAT_004d8510; /* used by 1 fn(s), first 0x004c0ed0 */
extern undefined DAT_004d8570; /* used by 1 fn(s), first 0x00478230 */
extern undefined DAT_004d85f0; /* used by 1 fn(s), first 0x00479170 */
extern undefined DAT_004d86a0; /* used by 1 fn(s), first 0x0047b8a0 */
extern undefined DAT_004d8998; /* used by 1 fn(s), first 0x004aca30 */
extern undefined DAT_004d89c8; /* used by 1 fn(s), first 0x004afa90 */
extern undefined DAT_004d89e8; /* used by 1 fn(s), first 0x004afa90 */
extern undefined4 UINT_004d8d54; /* used by 1 fn(s), first 0x004b1d60 */
extern undefined DAT_004d8d70; /* used by 1 fn(s), first 0x004b1d60 */
extern undefined4 UINT_004d8d74; /* used by 1 fn(s), first 0x004b1d60 */
extern undefined DAT_004d8df0; /* used by 1 fn(s), first 0x004b5650 */
extern undefined DAT_004d8e00; /* used by 1 fn(s), first 0x004b57c0 */
extern undefined DAT_004d8e18; /* used by 1 fn(s), first 0x004b5950 */
extern undefined DAT_004d8e28; /* used by 1 fn(s), first 0x004b5b60 */
extern undefined DAT_004d8e38; /* used by 1 fn(s), first 0x004b5c60 */
extern undefined DAT_004d8e50; /* used by 1 fn(s), first 0x004b5cf0 */
extern undefined DAT_004d9568; /* used by 1 fn(s), first 0x004b7f40 */
extern undefined DAT_004d9830; /* used by 1 fn(s), first 0x004c6d10 */
extern undefined DAT_004d9832; /* used by 1 fn(s), first 0x004c6d10 */
extern undefined DAT_004d9834; /* used by 1 fn(s), first 0x004c6d10 */
extern undefined DAT_004d9836; /* used by 1 fn(s), first 0x004c6d10 */
extern undefined DAT_004d9838; /* used by 1 fn(s), first 0x004c68f0 */
extern undefined DAT_004d98a8; /* used by 1 fn(s), first 0x004c79b0 */
extern undefined DAT_004d9ca8; /* used by 1 fn(s), first 0x004c7c50 */
extern undefined DAT_004d9cf8; /* used by 1 fn(s), first 0x004c9fa0 */
extern undefined DAT_004d9d70; /* used by 1 fn(s), first 0x004c9fa0 */
extern undefined DAT_004d9e38; /* used by 2 fn(s), first 0x004c9640 */
extern undefined DAT_004d9e50; /* used by 1 fn(s), first 0x004c8e90 */
extern undefined DAT_004da2d0; /* used by 1 fn(s), first 0x004c8e90 */
extern undefined DAT_004da347; /* used by 1 fn(s), first 0x004c9fa0 */
extern undefined DAT_004da348; /* used by 2 fn(s), first 0x004c70c0 */
extern undefined DAT_004da448; /* used by 3 fn(s), first 0x004c70c0 */
extern undefined DAT_004da548; /* used by 3 fn(s), first 0x004c70c0 */
extern undefined DAT_004da648; /* used by 1 fn(s), first 0x004c9fa0 */
extern undefined DAT_004da6c0; /* used by 1 fn(s), first 0x004c9fa0 */
extern undefined DAT_004da768; /* used by 1 fn(s), first 0x004cb390 */
extern undefined DAT_004da7e8; /* used by 1 fn(s), first 0x004cb390 */
extern undefined DAT_004da868; /* used by 1 fn(s), first 0x004cb390 */
extern undefined DAT_004da8e0; /* used by 1 fn(s), first 0x004cb390 */
extern undefined2 DAT_004daa58; /* used by 1 fn(s), first 0x004cbf50 */
extern undefined DAT_004dab0a; /* used by 1 fn(s), first 0x004cbf50 */
extern undefined DAT_004dab10; /* used by 1 fn(s), first 0x004cbf50 */
extern undefined DAT_004dac00; /* used by 1 fn(s), first 0x004d5de0 */
extern undefined DAT_004dd000; /* used by 1 fn(s), first 0x004acd10 */
extern undefined DAT_004dd008; /* used by 1 fn(s), first 0x004acd10 */
extern undefined DAT_004dd00c; /* used by 1 fn(s), first 0x004acd10 */
extern undefined DAT_004dd020; /* used by 1 fn(s), first 0x004acd10 */
extern undefined DAT_004dd024; /* used by 1 fn(s), first 0x004acd80 */
extern undefined DAT_004dd02c; /* used by 1 fn(s), first 0x004acd80 */
extern undefined DAT_004dd030; /* used by 1 fn(s), first 0x004acd80 */
extern undefined DAT_004dd038; /* used by 1 fn(s), first 0x004acd80 */
extern undefined *PTR_DAT_004dd040; /* used by 1 fn(s), first 0x00402120 */
extern char s_GRIME__Grim_Fandango_Executable_U_004dd048[]; /* used by 1 fn(s), first 0x00402c80 */
extern char s_grim_tab_004dd238[]; /* used by 2 fn(s), first 0x004012b0 */
extern undefined DAT_004dd33b; /* used by 1 fn(s), first 0x00402c80 */
extern undefined4 UINT_004dd33c; /* used by 1 fn(s), first 0x00402b60 */
extern undefined4 UINT_004dd340; /* used by 3 fn(s), first 0x004016a0 */
extern undefined4 UINT_004dd344; /* used by 3 fn(s), first 0x004016a0 */
extern undefined4 UINT_004dd348; /* used by 3 fn(s), first 0x004016a0 */
extern undefined DAT_004dd34c; /* used by 1 fn(s), first 0x00402c80 */
extern undefined *PTR_s_Is3DHardwareEnabled_004dd350; /* used by 1 fn(s), first 0x004012b0 */
extern undefined4 UINT_004dd380; /* used by 1 fn(s), first 0x004012b0 */
extern undefined DAT_004dd384; /* used by 1 fn(s), first 0x004016a0 */
extern undefined4 UINT_004dd388; /* used by 1 fn(s), first 0x00402290 */
extern undefined4 INT_004dd38c; /* used by 1 fn(s), first 0x00402fd0 */
extern char s_Grim_Fandango_004dd404[]; /* used by 1 fn(s), first 0x00401010 */
extern char s_resource_log_004dd414[]; /* used by 1 fn(s), first 0x00401040 */
extern char s_Unable_to_open_debug_log_in_the_c_004dd424[]; /* used by 1 fn(s), first 0x00401040 */
extern char s_Uh_oh__004dd464[]; /* used by 1 fn(s), first 0x00401040 */
extern char s_debug_log_004dd46c[]; /* used by 1 fn(s), first 0x00401040 */
extern undefined DAT_004dd478; /* used by 4 fn(s), first 0x00401040 */
extern char s__engn006_Please_make_sure_that_t_004dd47c[]; /* used by 2 fn(s), first 0x00401140 */
extern char s__engn007_Grim_Fandango_could_not_004dd4dc[]; /* used by 2 fn(s), first 0x00401140 */
extern char s_C__grimsrc_tools_grimdemo_grimde_004dd50c[]; /* used by 4 fn(s), first 0x00401140 */
extern char s__engn004_Please_make_sure_you_ar_004dd534[]; /* used by 1 fn(s), first 0x004012b0 */
extern char s__engn005_Grim_Fandango_could_not_004dd5a8[]; /* used by 1 fn(s), first 0x004012b0 */
extern char s_ExperimentalDisplay_004dd5e4[]; /* used by 4 fn(s), first 0x004012b0 */
extern char s__engn002_System_must_be_in_256_c_004dd5f8[]; /* used by 1 fn(s), first 0x004012b0 */
extern char s__engn001_Grim_Fandango_004dd638[]; /* used by 1 fn(s), first 0x004012b0 */
extern char s_GrimData_004dd650[]; /* used by 1 fn(s), first 0x004012b0 */
extern undefined DAT_004dd65c; /* used by 1 fn(s), first 0x004012b0 */
extern undefined DAT_004dd660; /* used by 1 fn(s), first 0x004012b0 */
extern undefined4 UINT_004dd668; /* used by 1 fn(s), first 0x004012b0 */
extern undefined4 UINT_004dd66c; /* used by 1 fn(s), first 0x004012b0 */
extern undefined2 DAT_004dd670; /* used by 1 fn(s), first 0x004012b0 */
extern undefined DAT_004dd672; /* used by 1 fn(s), first 0x004012b0 */
extern char s__s__02_3f_004dd674[]; /* used by 1 fn(s), first 0x004016a0 */
extern char s__02_3f_004dd680[]; /* used by 1 fn(s), first 0x004016a0 */
extern char s__engn003_Software_004dd688[]; /* used by 1 fn(s), first 0x00401e90 */
extern char s_Grim_Debug_004dd69c[]; /* used by 1 fn(s), first 0x004020a0 */
extern char s_LastDisplayDevice_004dd738[]; /* used by 2 fn(s), first 0x004025b0 */
extern char s_stdDisplay_numVideoModes____grim_004dd74c[]; /* used by 1 fn(s), first 0x004025b0 */
extern char s_Last3DDevice_004dd794[]; /* used by 2 fn(s), first 0x00402860 */
extern char s_threeDNum____0____threeDNum____i_004dd7a4[]; /* used by 1 fn(s), first 0x00402860 */
extern char s_Usage_004dd8b0[]; /* used by 1 fn(s), first 0x00402c80 */
extern undefined DAT_004dd8b8; /* used by 1 fn(s), first 0x00402c80 */
extern undefined DAT_004dd8bc; /* used by 1 fn(s), first 0x00402c80 */
extern undefined DAT_004dd8c0; /* used by 1 fn(s), first 0x00402c80 */
extern undefined DAT_004dd8c4; /* used by 1 fn(s), first 0x00402c80 */
extern undefined DAT_004dd8c8; /* used by 1 fn(s), first 0x00402c80 */
extern undefined DAT_004dd8cc; /* used by 1 fn(s), first 0x00402c80 */
extern undefined DAT_004dd8d0; /* used by 1 fn(s), first 0x00402c80 */
extern undefined DAT_004dd8d4; /* used by 1 fn(s), first 0x00402c80 */
extern undefined DAT_004dd8d8; /* used by 1 fn(s), first 0x00402c80 */
extern undefined DAT_004dd8dc; /* used by 1 fn(s), first 0x00402c80 */
extern undefined DAT_004dd8e0; /* used by 1 fn(s), first 0x00402c80 */
extern undefined DAT_004dd8e4; /* used by 1 fn(s), first 0x00402c80 */
extern undefined DAT_004dd8e8; /* used by 1 fn(s), first 0x00402c80 */
extern undefined DAT_004dd8ec; /* used by 1 fn(s), first 0x00402c80 */
extern undefined DAT_004dd8f0; /* used by 1 fn(s), first 0x00402c80 */
extern undefined DAT_004dd8f4; /* used by 1 fn(s), first 0x00402c80 */
extern undefined DAT_004dd8f8; /* used by 1 fn(s), first 0x00402c80 */
extern undefined DAT_004dd8fc; /* used by 1 fn(s), first 0x00402c80 */
extern undefined DAT_004dd900; /* used by 1 fn(s), first 0x00402c80 */
extern undefined DAT_004dd904; /* used by 1 fn(s), first 0x00402c80 */
extern undefined DAT_004dd908; /* used by 1 fn(s), first 0x00402c80 */
extern undefined DAT_004dd90c; /* used by 1 fn(s), first 0x00402c80 */
extern undefined DAT_004dd910; /* used by 1 fn(s), first 0x00402c80 */
extern undefined DAT_004dd914; /* used by 1 fn(s), first 0x00402c80 */
extern undefined DAT_004dd918; /* used by 1 fn(s), first 0x00402c80 */
extern char s__s_d_zbm_004dd91c[]; /* used by 1 fn(s), first 0x00402fd0 */
extern char s__s_d_bmp_004dd928[]; /* used by 1 fn(s), first 0x00402fd0 */
extern undefined DAT_004dd934; /* used by 1 fn(s), first 0x00402fd0 */
extern char s_grimpatch_bin_004dd93c[]; /* used by 1 fn(s), first 0x00402fd0 */
extern char s_GrimDataDir_004dd94c[]; /* used by 3 fn(s), first 0x004034b0 */
extern char s_SOFTWARE_LucasArts_Entertainment_004dd958[]; /* used by 1 fn(s), first 0x004034b0 */
extern undefined DAT_004dd998; /* used by 1 fn(s), first 0x004034b0 */
extern char s_splash_bm_004dd99c[]; /* used by 1 fn(s), first 0x00403520 */
extern undefined GrimServices_004dd9a8; /* used by 1 fn(s), first 0x00403880 */
extern undefined DAT_004dda18; /* used by 2 fn(s), first 0x004035b0 */
extern char s_WARNING___s_004dda1c[]; /* used by 1 fn(s), first 0x00403610 */
extern char s_ERROR___s_004dda28[]; /* used by 1 fn(s), first 0x00403640 */
extern char s_DEBUG___s_004dda34[]; /* used by 1 fn(s), first 0x00403670 */
extern char s_ASSERT____s__d___s_004dda40[]; /* used by 1 fn(s), first 0x004036a0 */
extern undefined DAT_004dda54; /* used by 4 fn(s), first 0x0047c7c0 */
extern undefined2 DAT_004dda58; /* used by 1 fn(s), first 0x004039a0 */
extern undefined2 DAT_004dda5c; /* used by 1 fn(s), first 0x00403bf0 */
extern char s_Version_004dda60[]; /* used by 1 fn(s), first 0x004038a0 */
extern char s_C__grimjedi_Libs_W32Util_Wuregis_004dda68[]; /* used by 2 fn(s), first 0x004039a0 */
extern undefined DAT_004dda90; /* used by 7 fn(s), first 0x00406aa0 */
extern undefined DAT_004dda94; /* used by 7 fn(s), first 0x00406aa0 */
extern undefined DAT_004dda98; /* used by 7 fn(s), first 0x00406aa0 */
extern undefined4 UINT_004ddaa0; /* used by 2 fn(s), first 0x004025b0 */
extern undefined4 UINT_004ddaac; /* used by 1 fn(s), first 0x00404420 */
extern undefined4 UINT_004ddab4; /* used by 4 fn(s), first 0x00489840 */
extern undefined4 UINT_004ddab8; /* used by 4 fn(s), first 0x00489840 */
extern undefined4 UINT_004ddabc; /* used by 4 fn(s), first 0x00489840 */
extern undefined4 UINT_004ddac0; /* used by 4 fn(s), first 0x00489840 */
extern undefined4 UINT_004ddac4; /* used by 4 fn(s), first 0x00489840 */
extern undefined4 UINT_004ddac8; /* used by 4 fn(s), first 0x00489840 */
extern undefined2 DAT_004ddad8; /* used by 1 fn(s), first 0x004043c0 */
extern undefined2 DAT_004ddadc; /* used by 1 fn(s), first 0x00404420 */
extern undefined2 DAT_004ddae0; /* used by 1 fn(s), first 0x00404a40 */
extern char s_C__grimjedi_Libs_RDroid_Engine_R_004ddae4[]; /* used by 3 fn(s), first 0x004043c0 */
extern undefined DAT_004ddb10; /* used by 1 fn(s), first 0x00404420 */
extern undefined DAT_004ddb18; /* used by 22 fn(s), first 0x00404420 */
extern undefined DAT_004ddb1c; /* used by 1 fn(s), first 0x0047b250 */
extern char s_GREYRAMP_CMP_004ddb20[]; /* used by 1 fn(s), first 0x00404a40 */
extern undefined DAT_004ddb30; /* used by 1 fn(s), first 0x00404b80 */
extern undefined2 DAT_004ddb3c; /* used by 1 fn(s), first 0x00409f50 */
extern undefined2 DAT_004ddb40; /* used by 1 fn(s), first 0x00409fb0 */
extern char s_C__grimjedi_Libs_RDroid_Engine_R_004ddb44[]; /* used by 2 fn(s), first 0x00409f50 */
extern undefined DAT_004ddb70; /* used by 1 fn(s), first 0x0040d880 */
extern undefined DAT_004ddb74; /* used by 2 fn(s), first 0x0040a880 */
extern undefined DAT_004ddb78; /* used by 2 fn(s), first 0x0040a880 */
extern undefined2 DAT_004ddb7c; /* used by 1 fn(s), first 0x0040a8f0 */
extern undefined2 DAT_004ddb84; /* used by 1 fn(s), first 0x0040b8e0 */
extern undefined2 DAT_004ddb88; /* used by 1 fn(s), first 0x0040c280 */
extern char s_UNKNOWN_004ddb8c[]; /* used by 2 fn(s), first 0x0040a8c0 */
extern char s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94[]; /* used by 3 fn(s), first 0x0040a8f0 */
extern char s__d___x__x__d__d__d__d__d__f__f___004ddbc4[]; /* used by 1 fn(s), first 0x0040aa20 */
extern char s_hierarchy_nodes__d_004ddbfc[]; /* used by 1 fn(s), first 0x0040aa20 */
extern undefined DAT_004ddc14; /* used by 2 fn(s), first 0x0040aa20 */
extern undefined DAT_004ddc18; /* used by 2 fn(s), first 0x0040aa20 */
extern undefined DAT_004ddc1c; /* used by 1 fn(s), first 0x0040aa20 */
extern char s_faces__d_004ddc20[]; /* used by 1 fn(s), first 0x0040aa20 */
extern char s__d___f__f__f_004ddc2c[]; /* used by 1 fn(s), first 0x0040aa20 */
extern char s__d___f__f_004ddc3c[]; /* used by 1 fn(s), first 0x0040aa20 */
extern char s_texture_vertices__d_004ddc48[]; /* used by 1 fn(s), first 0x0040aa20 */
extern char s__d___f__f__f__f_004ddc60[]; /* used by 1 fn(s), first 0x0040aa20 */
extern char s_vertices__d_004ddc74[]; /* used by 1 fn(s), first 0x0040aa20 */
extern char s_texturemode__d_004ddc84[]; /* used by 1 fn(s), first 0x0040aa20 */
extern char s_lightingmode__d_004ddc94[]; /* used by 1 fn(s), first 0x0040aa20 */
extern char s_geometrymode__d_004ddca8[]; /* used by 1 fn(s), first 0x0040aa20 */
extern char s_shadow__d_004ddcbc[]; /* used by 1 fn(s), first 0x0040aa20 */
extern char s_name__s_004ddcc8[]; /* used by 1 fn(s), first 0x0040aa20 */
extern char s_mesh__d_004ddcd4[]; /* used by 1 fn(s), first 0x0040aa20 */
extern char s_meshes__d_004ddce0[]; /* used by 1 fn(s), first 0x0040aa20 */
extern char s_geoset__d_004ddcec[]; /* used by 1 fn(s), first 0x0040aa20 */
extern char s_geosets__d_004ddcf8[]; /* used by 1 fn(s), first 0x0040aa20 */
extern char s_insert_offset__f__f__f_004ddd04[]; /* used by 1 fn(s), first 0x0040aa20 */
extern char s_radius__f_004ddd1c[]; /* used by 1 fn(s), first 0x0040aa20 */
extern char s__d___s_004ddd28[]; /* used by 1 fn(s), first 0x0040aa20 */
extern char s_materials__d_004ddd48[]; /* used by 1 fn(s), first 0x0040aa20 */
extern char s_3do__d__d_004ddd58[]; /* used by 1 fn(s), first 0x0040aa20 */
extern char s_section___s_004ddd64[]; /* used by 3 fn(s), first 0x0040aa20 */
extern undefined4 UINT_004ddd74; /* used by 2 fn(s), first 0x004b1d60 */
extern undefined DAT_004ddd78; /* used by 6 fn(s), first 0x0047d050 */
extern undefined2 DAT_004ddd7c; /* used by 1 fn(s), first 0x00417eb0 */
extern undefined2 DAT_004ddd80; /* used by 1 fn(s), first 0x00417f30 */
extern char s_C__grimjedi_Libs_RDroid_Engine_R_004ddd84[]; /* used by 2 fn(s), first 0x00417eb0 */
extern undefined DAT_004dddb0; /* used by 1 fn(s), first 0x00417f30 */
extern undefined2 DAT_004dddd8; /* used by 1 fn(s), first 0x00450500 */
extern char s_C__grimjedi_Libs_RDroid_Engine_R_004ddddc[]; /* used by 1 fn(s), first 0x00450500 */
extern undefined2 DAT_004dde0c; /* used by 1 fn(s), first 0x00471a40 */
extern undefined2 DAT_004dde10; /* used by 1 fn(s), first 0x00471bd0 */
extern char s_C__grimjedi_Libs_RDroid_Engine_R_004dde14[]; /* used by 2 fn(s), first 0x00471a40 */
extern undefined2 DAT_004dde5c; /* used by 1 fn(s), first 0x004728a0 */
extern undefined2 DAT_004dde60; /* used by 1 fn(s), first 0x00472910 */
extern char s_C__grimjedi_Libs_RDroid_Primitiv_004dde64[]; /* used by 2 fn(s), first 0x004728a0 */
extern undefined DAT_004dde98; /* used by 1 fn(s), first 0x00473660 */
extern undefined DAT_004ddea0; /* used by 1 fn(s), first 0x00473660 */
extern undefined DAT_004ddea8; /* used by 1 fn(s), first 0x00473660 */
extern undefined DAT_004ddeb0; /* used by 1 fn(s), first 0x00473660 */
extern undefined DAT_004ddeb4; /* used by 1 fn(s), first 0x00473660 */
extern undefined DAT_004ddebc; /* used by 1 fn(s), first 0x00473660 */
extern undefined DAT_004ddec4; /* used by 2 fn(s), first 0x00473660 */
extern undefined DAT_004ddecc; /* used by 1 fn(s), first 0x00473810 */
extern undefined DAT_004dded0; /* used by 1 fn(s), first 0x00473810 */
extern undefined DAT_004dded4; /* used by 1 fn(s), first 0x00473810 */
extern undefined DAT_004dded8; /* used by 1 fn(s), first 0x00473810 */
extern undefined DAT_004ddedc; /* used by 1 fn(s), first 0x00473810 */
extern undefined DAT_004ddee0; /* used by 1 fn(s), first 0x00473810 */
extern undefined2 DAT_004de1d8; /* used by 1 fn(s), first 0x00474b30 */
extern char s_DIBsection_windowed_display_004de9dc[]; /* used by 1 fn(s), first 0x00473a40 */
extern char s_Window_Display_Device_004de9f8[]; /* used by 1 fn(s), first 0x00473a40 */
extern char s_C__grimjedi_Libs_Std_Win95_Stddi_004dea18[]; /* used by 1 fn(s), first 0x00474b30 */
extern undefined4 UINT_004dea40; /* used by 5 fn(s), first 0x00477040 */
extern undefined DAT_004dea44; /* used by 1 fn(s), first 0x004770d0 */
extern undefined DAT_004dea48; /* used by 1 fn(s), first 0x004770d0 */
extern undefined DAT_004dee34; /* used by 1 fn(s), first 0x004be990 */
extern char s__s__d____s_004dee38[]; /* used by 1 fn(s), first 0x00477f10 */
extern int UINT_004dee48; /* used by 3 fn(s), first 0x00478700 */
extern int UINT_004dee4c; /* used by 3 fn(s), first 0x00478700 */
extern uint UINT_004dee50; /* used by 2 fn(s), first 0x00478700 */
extern undefined DAT_004dee54; /* used by 1 fn(s), first 0x00478700 */
extern undefined4 UINT_004dee58; /* used by 6 fn(s), first 0x004782e0 */
extern uint UINT_004dee5c; /* used by 2 fn(s), first 0x00478770 */
extern undefined4 UINT_004dee60; /* used by 3 fn(s), first 0x00478230 */
extern undefined2 DAT_004df550; /* used by 1 fn(s), first 0x0047aa50 */
extern undefined2 DAT_004df558; /* used by 1 fn(s), first 0x0047ab20 */
extern undefined2 DAT_004df55c; /* used by 1 fn(s), first 0x0047b2b0 */
extern undefined2 DAT_004df568; /* used by 1 fn(s), first 0x0047b380 */
extern undefined2 DAT_004df570; /* used by 1 fn(s), first 0x0047b4b0 */
extern char s_C__grimjedi_Libs_Std_General_Std_004df574[]; /* used by 5 fn(s), first 0x0047aa50 */
extern undefined DAT_004df5a0; /* used by 2 fn(s), first 0x0047ab20 */
extern char s_Unable_to_allocate_a_new_frame_w_004df5a8[]; /* used by 1 fn(s), first 0x0047b2b0 */
extern undefined DAT_004df600; /* used by 1 fn(s), first 0x0047bd20 */
extern undefined DAT_004e3600; /* used by 1 fn(s), first 0x0047c120 */
extern undefined2 DAT_004e7600; /* used by 1 fn(s), first 0x0047c7e0 */
extern char s_C__grimjedi_Libs_Std_General_Std_004e7604[]; /* used by 1 fn(s), first 0x0047c7e0 */
extern undefined DAT_004e7630; /* used by 1 fn(s), first 0x0047c7e0 */
extern undefined2 DAT_004e7638; /* used by 1 fn(s), first 0x0047cb20 */
extern undefined2 DAT_004e763c; /* used by 1 fn(s), first 0x0047cb70 */
extern undefined2 DAT_004e7640; /* used by 1 fn(s), first 0x0047d050 */
extern char s_C__grimjedi_Libs_Std_General_Std_004e7644[]; /* used by 3 fn(s), first 0x0047cb20 */
extern char s_Unable_to_read_all_the_data_from_004e766c[]; /* used by 1 fn(s), first 0x0047cb70 */
extern char s_Unable_to_lock_VBuffer_memory__004e76b4[]; /* used by 2 fn(s), first 0x0047cb70 */
extern char s_Unable_to_allocate_memory__004e76d4[]; /* used by 2 fn(s), first 0x0047cb70 */
extern char s_This_BMP_file_uses_a_bit_depth_w_004e76f0[]; /* used by 1 fn(s), first 0x0047cb70 */
extern char s_32bit_per_pixel_BMP_not_yet_supp_004e772c[]; /* used by 1 fn(s), first 0x0047cb70 */
extern char s_16_bit_per_pixel_BMP_not_yet_sup_004e7754[]; /* used by 1 fn(s), first 0x0047cb70 */
extern char s_Unable_to_read_the_palette__Your_004e777c[]; /* used by 1 fn(s), first 0x0047cb70 */
extern char s_Only_24bpp_supported_004e77b4[]; /* used by 1 fn(s), first 0x0047d050 */
extern undefined2 DAT_004e77cc; /* used by 1 fn(s), first 0x0047d280 */
extern undefined2 DAT_004e77d0; /* used by 1 fn(s), first 0x0047d2d0 */
extern char s_C__grimjedi_Libs_Std_General_std_004e77d8[]; /* used by 2 fn(s), first 0x0047d280 */
extern undefined2 DAT_004e7800; /* used by 4 fn(s), first 0x0047e470 */
extern undefined DAT_004e780c; /* used by 1 fn(s), first 0x0047db00 */
extern undefined DAT_004e7858; /* used by 1 fn(s), first 0x0047e8b0 */
extern undefined DAT_004e7868; /* used by 2 fn(s), first 0x0047e600 */
extern undefined *PTR_UINT_004e7874; /* used by 2 fn(s), first 0x0047e3c0 */
extern undefined *PTR_UINT_004e7878; /* used by 2 fn(s), first 0x0047e3c0 */
extern undefined2 DAT_004e787c; /* used by 1 fn(s), first 0x0047db00 */
extern undefined2 DAT_004e7880; /* used by 1 fn(s), first 0x0047e060 */
extern char s_C__grimjedi_Libs_Std_General_Std_004e7884[]; /* used by 2 fn(s), first 0x0047db00 */
extern undefined DAT_004e78ac; /* used by 1 fn(s), first 0x0047e060 */
extern undefined DAT_004e78b0; /* used by 1 fn(s), first 0x0047e060 */
extern undefined2 DAT_004e78b4; /* used by 1 fn(s), first 0x0047ec80 */
extern char s_C__grimjedi_Libs_Std_General_Std_004e78b8[]; /* used by 1 fn(s), first 0x0047ec80 */
extern undefined2 DAT_004e78e0; /* used by 1 fn(s), first 0x0047f120 */
extern undefined DAT_004e78e4; /* used by 1 fn(s), first 0x0047f120 */
extern char s_C__grimjedi_Libs_Std_General_Std_004e78ec[]; /* used by 1 fn(s), first 0x0047f120 */
extern char s_BODYxxxx_004e7914[]; /* used by 1 fn(s), first 0x0047f720 */
extern undefined DAT_004e7920; /* used by 1 fn(s), first 0x0047f720 */
extern char s_FORMxxxxPBM_BMHD_004e7928[]; /* used by 1 fn(s), first 0x0047f720 */
extern undefined2 DAT_004e793c; /* used by 1 fn(s), first 0x004b64f0 */
extern undefined2 DAT_004e7940; /* used by 1 fn(s), first 0x0047fe20 */
extern undefined2 DAT_004e7944; /* used by 1 fn(s), first 0x0047fe50 */
extern char s_allocation__magic____0x12345678_004e7948[]; /* used by 1 fn(s), first 0x0047fe20 */
extern char s_C__grimjedi_Libs_Std_General_Std_004e7968[]; /* used by 2 fn(s), first 0x0047fe20 */
extern char s_allocation_004e7994[]; /* used by 1 fn(s), first 0x0047fe50 */
extern undefined *PTR_ResType_DefaultHandler_004e79ac; /* used by 2 fn(s), first 0x004801a0 */
extern char s_Resource____12s__allocated___8ld_004e79f4[]; /* used by 1 fn(s), first 0x00480230 */
extern char s_C__grimsrc_libs_grimlib_Temp_Res_004e7a1c[]; /* used by 15 fn(s), first 0x004803a0 */
extern char s_Total___d_items___d_bytes_004e7a40[]; /* used by 1 fn(s), first 0x00480680 */
extern char s_Resource___12s__size____7ld__s_004e7a5c[]; /* used by 1 fn(s), first 0x00480680 */
extern char s_REFERENCED_004e7a80[]; /* used by 1 fn(s), first 0x00480680 */
extern char s__int_fh___0_____int_fh____MAX_OP_004e7a8c[]; /* used by 8 fn(s), first 0x00480a00 */
extern char s_Resource____12s__freed___d_refer_004e7ab8[]; /* used by 1 fn(s), first 0x00481510 */
extern char s_ref__valid____0_004e7ae0[]; /* used by 1 fn(s), first 0x00481510 */
extern undefined DAT_004e7af0; /* used by 1 fn(s), first 0x004817a0 */
extern undefined DAT_004e7af8; /* used by 2 fn(s), first 0x00481cf0 */
extern char s_ref_____ref__valid_004e7b00[]; /* used by 1 fn(s), first 0x00482070 */
extern undefined DAT_004e7b14; /* used by 1 fn(s), first 0x00482260 */
extern uint UINT_004e7b20; /* used by 2 fn(s), first 0x00482520 */
extern undefined DAT_004e7b48; /* used by 2 fn(s), first 0x00482e30 */
extern undefined4 UINT_004e7b50; /* used by 2 fn(s), first 0x004016a0 */
extern undefined4 UINT_004e7d98; /* used by 1 fn(s), first 0x00482990 */
extern undefined DAT_004e7da0; /* used by 1 fn(s), first 0x00482620 */
extern undefined *PTR_FileUtil_SysInitialize_004e7dc0; /* used by 1 fn(s), first 0x00482540 */
extern undefined *PTR_sputControl_Initialize_004e7e00; /* used by 1 fn(s), first 0x00482540 */
extern int UINT_004e7e30; /* used by 2 fn(s), first 0x00482990 */
extern char s_slot____1____slot___PerfTotalEnt_004e7f74[]; /* used by 2 fn(s), first 0x00482e30 */
extern char s_C__grimsrc_libs_grimlib_Main_spu_004e7f9c[]; /* used by 4 fn(s), first 0x00482e30 */
extern char s_grim_sav_004e7fc8[]; /* used by 2 fn(s), first 0x00482fe0 */
extern char s_tot_____int_bytes_004e7fd4[]; /* used by 1 fn(s), first 0x004831f0 */
extern char s_patch05_bin_004e7fe8[]; /* used by 1 fn(s), first 0x00483240 */
extern char s_size_____int_vbuf__rasterInfo_si_004e7ff4[]; /* used by 1 fn(s), first 0x00483490 */
extern char s_grim_tmp_004e8018[]; /* used by 2 fn(s), first 0x00483610 */
extern undefined *PTR_s_language_tab_004e8024; /* used by 1 fn(s), first 0x00483720 */
extern char s_C__grimsrc_libs_grimlib_Engine_p_004e8038[]; /* used by 1 fn(s), first 0x00483720 */
extern undefined4 UINT_004e806c; /* used by 2 fn(s), first 0x00402c80 */
extern uint UINT_004e8088; /* used by 2 fn(s), first 0x004874c0 */
extern undefined4 UINT_004e808c; /* used by 1 fn(s), first 0x004874d0 */
extern char s_Bad_Colormap_Reference_004e8090[]; /* used by 7 fn(s), first 0x00483aa0 */
extern char s_main_sputResource_h_004e80a8[]; /* used by 30 fn(s), first 0x00483aa0 */
extern char s_C__grimsrc_libs_grimlib_Engine_s_004e80bc[]; /* used by 3 fn(s), first 0x00486b40 */
extern char s__percent____0_0f______percent____004e80ec[]; /* used by 1 fn(s), first 0x00486d00 */
extern char s_Bad_Bitmap_Reference_004e8114[]; /* used by 10 fn(s), first 0x004874d0 */
extern char s_wait_bm_004e812c[]; /* used by 1 fn(s), first 0x004874d0 */
extern undefined4 UINT_004e8138; /* used by 2 fn(s), first 0x00487c10 */
extern undefined4 UINT_004e813c; /* used by 2 fn(s), first 0x00487c10 */
extern int UINT_004e8140; /* used by 2 fn(s), first 0x00487c10 */
extern undefined4 UINT_004e8144; /* used by 2 fn(s), first 0x00487c10 */
extern undefined4 UINT_004e8148; /* used by 2 fn(s), first 0x00487c10 */
extern undefined4 UINT_004e814c; /* used by 8 fn(s), first 0x004018b0 */
extern char s_Cancel_004e8150[]; /* used by 3 fn(s), first 0x004878c0 */
extern undefined DAT_004e8158; /* used by 3 fn(s), first 0x004878c0 */
extern char s_BUTTON_004e815c[]; /* used by 3 fn(s), first 0x004878c0 */
extern char s_msctls_updown32_004e8164[]; /* used by 1 fn(s), first 0x004878c0 */
extern undefined DAT_004e8174; /* used by 2 fn(s), first 0x004878c0 */
extern char s_STATIC_004e817c[]; /* used by 2 fn(s), first 0x004878c0 */
extern char s_MS_Sans_Serif_004e8184[]; /* used by 3 fn(s), first 0x004878c0 */
extern char s_Recursive_004e8194[]; /* used by 1 fn(s), first 0x00487c10 */
extern char s_SysTreeView32_004e81a0[]; /* used by 1 fn(s), first 0x00487c10 */
extern char s_Tree_Select_004e81b0[]; /* used by 1 fn(s), first 0x00487c10 */
extern char s_Input_004e81bc[]; /* used by 1 fn(s), first 0x00487e30 */
extern undefined DAT_004e81c4; /* used by 1 fn(s), first 0x00488460 */
extern char s_Not_so_fast__004e81c8[]; /* used by 1 fn(s), first 0x00488460 */
extern char s_No_item_was_picked__004e81d8[]; /* used by 1 fn(s), first 0x00488460 */
extern char s_C__grimsrc_libs_grimlib_Win95_gr_004e81ec[]; /* used by 1 fn(s), first 0x00488800 */
extern char s_C__grimsrc_libs_grimlib_Temp_Mem_004e8264[]; /* used by 5 fn(s), first 0x00488980 */
extern char s_pData_004e828c[]; /* used by 1 fn(s), first 0x00488ba0 */
extern char s_pPool__poolItems____itemCount_004e8294[]; /* used by 1 fn(s), first 0x00488980 */
extern char s_pPool_004e82b4[]; /* used by 1 fn(s), first 0x00488980 */
extern char s_itemGrowBy___0_004e82bc[]; /* used by 1 fn(s), first 0x00488980 */
extern char s_itemSize___0_004e82cc[]; /* used by 1 fn(s), first 0x00488980 */
extern char s_pPool__pPool____pPool_004e82dc[]; /* used by 3 fn(s), first 0x00488a70 */
extern undefined DAT_004e82f4; /* used by 2 fn(s), first 0x00488a70 */
extern char s__s____004e82fc[]; /* used by 1 fn(s), first 0x00488de0 */
extern char s__s___s_004e8304[]; /* used by 1 fn(s), first 0x00488de0 */
extern char s_C__grimsrc_libs_grimlib_Temp_Fil_004e830c[]; /* used by 1 fn(s), first 0x00488de0 */
extern undefined *PTR_Movie_CheckSurfaceFormat_004e8338; /* used by 1 fn(s), first 0x00488fb0 */
extern char s_FALSE_004e8350[]; /* used by 1 fn(s), first 0x00489130 */
extern char s_StartSmush_004e8358[]; /* used by 1 fn(s), first 0x00489130 */
extern undefined *PTR_s_color_004e8368; /* used by 4 fn(s), first 0x00489840 */
extern undefined *PTR_s_xoffset_004e836c; /* used by 1 fn(s), first 0x00489fe0 */
extern undefined *PTR_s_yoffset_004e8370; /* used by 1 fn(s), first 0x00489fe0 */
extern undefined *PTR_DAT_004e8374; /* used by 1 fn(s), first 0x00489fe0 */
extern undefined *PTR_DAT_004e8378; /* used by 1 fn(s), first 0x00489fe0 */
extern undefined *PTR_DAT_004e837c; /* used by 1 fn(s), first 0x00489fe0 */
extern undefined *PTR_DAT_004e8380; /* used by 1 fn(s), first 0x00489fe0 */
extern undefined *PTR_s_width_004e8384; /* used by 1 fn(s), first 0x00489fe0 */
extern undefined *PTR_s_height_004e8388; /* used by 1 fn(s), first 0x00489fe0 */
extern undefined *PTR_s_filled_004e838c; /* used by 1 fn(s), first 0x00489d70 */
extern undefined *PTR_s_layer_004e8390; /* used by 4 fn(s), first 0x00489840 */
extern undefined *PTR_s_DrawLine_004e8398; /* used by 1 fn(s), first 0x004897f0 */
extern undefined4 UINT_004e83c8; /* used by 1 fn(s), first 0x004897f0 */
extern char s_filled_004e8430[]; /* used by 1 fn(s), first 0x004a31f0 */
extern char s_height_004e8438[]; /* used by 1 fn(s), first 0x0048c500 */
extern char s_width_004e8440[]; /* used by 1 fn(s), first 0x0048c500 */
extern undefined DAT_004e8450; /* used by 5 fn(s), first 0x0048c500 */
extern undefined DAT_004e8454; /* used by 5 fn(s), first 0x0048c500 */
extern char s_color_004e8468[]; /* used by 1 fn(s), first 0x004a31f0 */
extern undefined4 UINT_004e8480; /* used by 1 fn(s), first 0x0048b830 */
extern undefined4 UINT_004e8484; /* used by 1 fn(s), first 0x0048b830 */
extern undefined4 UINT_004e8490; /* used by 1 fn(s), first 0x0048b2e0 */
extern undefined4 UINT_004e84a0; /* used by 3 fn(s), first 0x0048c500 */
extern undefined4 UINT_004e84d0; /* used by 3 fn(s), first 0x0048c500 */
extern undefined4 UINT_004e8500; /* used by 3 fn(s), first 0x0048c500 */
extern undefined *PTR_s_IsMessageGoing_004e8528; /* used by 1 fn(s), first 0x0048c500 */
extern undefined4 UINT_004e85d8; /* used by 1 fn(s), first 0x0048c500 */
extern char s___s__s_004e8754[]; /* used by 1 fn(s), first 0x0048ae60 */
extern char s_background_004e875c[]; /* used by 1 fn(s), first 0x0048c500 */
extern undefined DAT_004e8768; /* used by 1 fn(s), first 0x0048c500 */
extern char s_volume_004e876c[]; /* used by 1 fn(s), first 0x0048c500 */
extern char s_rjustify_004e8774[]; /* used by 1 fn(s), first 0x0048c500 */
extern char s_ljustify_004e8780[]; /* used by 1 fn(s), first 0x0048c500 */
extern char s_center_004e878c[]; /* used by 1 fn(s), first 0x0048c500 */
extern char s_duration_004e8794[]; /* used by 1 fn(s), first 0x0048c500 */
extern char s_hicolor_004e87a0[]; /* used by 1 fn(s), first 0x0048c500 */
extern char s_fxcolor_004e87a8[]; /* used by 1 fn(s), first 0x0048c500 */
extern char s_bgcolor_004e87b0[]; /* used by 1 fn(s), first 0x0048c500 */
extern char s_fgcolor_004e87b8[]; /* used by 1 fn(s), first 0x0048c500 */
extern undefined DAT_004e87c0; /* used by 1 fn(s), first 0x0048c500 */
extern undefined DAT_004e87cc; /* used by 2 fn(s), first 0x0048d090 */
extern undefined4 UINT_004e87d0; /* used by 1 fn(s), first 0x0049e0b0 */
extern undefined *PTR_s_KEY_ESCAPE_004e87d4; /* used by 1 fn(s), first 0x0049e460 */
extern int UINT_004e9a30; /* used by 2 fn(s), first 0x0048d350 */
extern char s_DEBUG_Loops__004e9a98[]; /* used by 1 fn(s), first 0x0048d870 */
extern char s_C__grimsrc_libs_grimlib_Main_spu_004e9c30[]; /* used by 2 fn(s), first 0x0048d350 */
extern undefined DAT_004e9c60; /* used by 5 fn(s), first 0x0048d570 */
extern undefined DAT_004e9c64; /* used by 1 fn(s), first 0x0048d570 */
extern char s_dflt_mat_004e9c68[]; /* used by 1 fn(s), first 0x0048dd20 */
extern char s_Grim_res_004e9c74[]; /* used by 1 fn(s), first 0x0048e230 */
extern char s_Bad_model_Reference_004e9e08[]; /* used by 5 fn(s), first 0x0048e330 */
extern char s_Valid_Ref___pCosNode__rCostume___004e9e1c[]; /* used by 1 fn(s), first 0x0048e330 */
extern char s_C__grimsrc_libs_grimlib_Engine_s_004e9e40[]; /* used by 7 fn(s), first 0x0048e330 */
extern char s_tot_clips___MAX_SHADOW_CLIPS_004e9e70[]; /* used by 1 fn(s), first 0x0048ecd0 */
extern char s_Bad_costume_Reference_004e9e90[]; /* used by 2 fn(s), first 0x0048ecd0 */
extern char s_pActor__pExtra_004e9ea8[]; /* used by 2 fn(s), first 0x0048fe80 */
extern char s_pActor_____pActor__pExtra_004e9eb8[]; /* used by 1 fn(s), first 0x00490580 */
extern char s__s_imu_004e9ed4[]; /* used by 1 fn(s), first 0x00492b30 */
extern char s__s_imc_004e9edc[]; /* used by 1 fn(s), first 0x00492b30 */
extern char s__s_wav_004e9ee4[]; /* used by 1 fn(s), first 0x00492b30 */
extern char s__s_wvc_004e9eec[]; /* used by 1 fn(s), first 0x00492b30 */
extern undefined DAT_004e9ef8; /* used by 1 fn(s), first 0x00496930 */
extern undefined DAT_004e9f38; /* used by 1 fn(s), first 0x00496d40 */
extern undefined DAT_004e9f60; /* used by 1 fn(s), first 0x00497890 */
extern undefined DAT_004e9ff8; /* used by 1 fn(s), first 0x004971a0 */
extern undefined *PTR_s_GetKeyLength_004ea058; /* used by 1 fn(s), first 0x004959a0 */
extern undefined4 UINT_004ea068; /* used by 1 fn(s), first 0x004959a0 */
extern char s_shadow_cmp_004ea190[]; /* used by 2 fn(s), first 0x00494890 */
extern char s_shadow_mat_004ea19c[]; /* used by 1 fn(s), first 0x00494940 */
extern char s_skirt_004ea1a8[]; /* used by 1 fn(s), first 0x00494d10 */
extern char s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0[]; /* used by 18 fn(s), first 0x00494e80 */
extern char s_Bad_keyframe_Reference_004ea1e0[]; /* used by 5 fn(s), first 0x00495850 */
extern char s_BitmapPath_004ea1f8[]; /* used by 2 fn(s), first 0x004959a0 */
extern char s_Objects_004ea204[]; /* used by 1 fn(s), first 0x004959a0 */
extern char s_SmushPath_004ea20c[]; /* used by 2 fn(s), first 0x004959a0 */
extern char s_Movies_004ea218[]; /* used by 1 fn(s), first 0x004959a0 */
extern char s_SoundPath_004ea220[]; /* used by 2 fn(s), first 0x004959a0 */
extern undefined DAT_004ea22c; /* used by 1 fn(s), first 0x004959a0 */
extern char s_ModelPath_004ea230[]; /* used by 2 fn(s), first 0x004959a0 */
extern char s_Models_004ea23c[]; /* used by 1 fn(s), first 0x004959a0 */
extern char s_MaterialPath_004ea244[]; /* used by 2 fn(s), first 0x004959a0 */
extern char s_Materials_004ea254[]; /* used by 1 fn(s), first 0x004959a0 */
extern char s_ColormapPath_004ea260[]; /* used by 2 fn(s), first 0x004959a0 */
extern char s_Colormaps_004ea270[]; /* used by 1 fn(s), first 0x004959a0 */
extern char s_KeyframePath_004ea27c[]; /* used by 2 fn(s), first 0x004959a0 */
extern char s_Animation_004ea28c[]; /* used by 1 fn(s), first 0x004959a0 */
extern char s_iMuse_State_004ea2a8[]; /* used by 1 fn(s), first 0x00497840 */
extern char s_iMuse_Sequence_004ea2b4[]; /* used by 1 fn(s), first 0x00497840 */
extern char s__s__s____d_004ea3bc[]; /* used by 1 fn(s), first 0x00495e90 */
extern char s_____s_004ea3cc[]; /* used by 1 fn(s), first 0x00495e90 */
extern char s____Chore_numbering_for__s__004ea3d4[]; /* used by 1 fn(s), first 0x00495e90 */
extern char s_File_Error__004ea3f0[]; /* used by 1 fn(s), first 0x00495e90 */
extern char s_Unable_to_open_chore_list_file__C_004ea3fc[]; /* used by 1 fn(s), first 0x00495e90 */
extern undefined DAT_004ea45c; /* used by 1 fn(s), first 0x00495e90 */
extern char s_Name_chore_list_file____004ea460[]; /* used by 1 fn(s), first 0x00495e90 */
extern char s_Script_files____lua____def__004ea478[]; /* used by 1 fn(s), first 0x00495e90 */
extern char s_Select_image_file_to_add____004ea4b8[]; /* used by 1 fn(s), first 0x004960a0 */
extern char s_Graphics_files____pcx____gif___l_004ea4d4[]; /* used by 1 fn(s), first 0x004960a0 */
extern undefined DAT_004ea52c; /* used by 9 fn(s), first 0x004960a0 */
extern char s_Select_colormap_file_to_add____004ea530[]; /* used by 1 fn(s), first 0x00496460 */
extern char s_Colormap_files____cmp__004ea550[]; /* used by 1 fn(s), first 0x00496460 */
extern char s_Select_mat_file_to_animate____004ea584[]; /* used by 1 fn(s), first 0x00496670 */
extern char s_Material_files____mat__004ea5a4[]; /* used by 2 fn(s), first 0x00496670 */
extern char s__s__d_004ea5d8[]; /* used by 1 fn(s), first 0x00496890 */
extern char s_Resolve_parent_offset__0___off__004ea5e0[]; /* used by 1 fn(s), first 0x00496890 */
extern char s_Select_model_file_to_add____004ea600[]; /* used by 1 fn(s), first 0x00496b60 */
extern char s_Model_files____3do__004ea61c[]; /* used by 1 fn(s), first 0x00496b60 */
extern char s_Mesh__d___s__004ea64c[]; /* used by 1 fn(s), first 0x00496e20 */
extern char s_Select_mesh_node_to_add____004ea65c[]; /* used by 1 fn(s), first 0x00496e20 */
extern char s__s__d__d__d__d_004ea678[]; /* used by 1 fn(s), first 0x00497320 */
extern char s_Minimum_Volume_004ea688[]; /* used by 1 fn(s), first 0x00497320 */
extern char s_Priority_004ea698[]; /* used by 1 fn(s), first 0x00497320 */
extern undefined DAT_004ea6a4; /* used by 1 fn(s), first 0x00497320 */
extern char s_Maximum_Volume_004ea6a8[]; /* used by 1 fn(s), first 0x00497320 */
extern char s_Select_sound_file_to_add____004ea6b8[]; /* used by 1 fn(s), first 0x00497460 */
extern char s_Sound_files____imu____imc____wvc_004ea6d4[]; /* used by 1 fn(s), first 0x00497460 */
extern char s_Change_variable_properties_004ea72c[]; /* used by 1 fn(s), first 0x004976a0 */
extern char s_Variable_name_004ea748[]; /* used by 2 fn(s), first 0x004976a0 */
extern char s_Name_of_variable_004ea758[]; /* used by 1 fn(s), first 0x00497710 */
extern char s_Select_keyframe_file_to_add____004ea76c[]; /* used by 1 fn(s), first 0x00497e10 */
extern char s_Keyframe_files____key__004ea78c[]; /* used by 1 fn(s), first 0x00497e10 */
extern char s__s__d__d_004ea7c0[]; /* used by 1 fn(s), first 0x00498000 */
extern char s_Normal_Priority_004ea7cc[]; /* used by 1 fn(s), first 0x00498000 */
extern char s_Tagged_Priority_004ea7dc[]; /* used by 1 fn(s), first 0x00498000 */
extern char s_Select_smush_file____004ea7ec[]; /* used by 1 fn(s), first 0x00498190 */
extern char s_Smush_files____snm__004ea804[]; /* used by 1 fn(s), first 0x00498190 */
extern char s_Select_mat_file_for_sprite____004ea834[]; /* used by 1 fn(s), first 0x00498280 */
extern char s__s__d__d__d__d__d_004ea854[]; /* used by 1 fn(s), first 0x004986e0 */
extern undefined DAT_004ea868; /* used by 1 fn(s), first 0x004986e0 */
extern undefined DAT_004ea86c; /* used by 1 fn(s), first 0x004986e0 */
extern undefined DAT_004ea870; /* used by 1 fn(s), first 0x004986e0 */
extern char s_Height_004ea874[]; /* used by 1 fn(s), first 0x004986e0 */
extern char s_Width_004ea87c[]; /* used by 1 fn(s), first 0x004986e0 */
extern undefined *PTR_s_EnginePause_004ea8b0; /* used by 1 fn(s), first 0x0049de00 */
extern undefined4 UINT_004eb168; /* used by 1 fn(s), first 0x0049de00 */
extern char s_count_004ec384[]; /* used by 3 fn(s), first 0x00499ff0 */
extern char s_C__grimsrc_libs_grimlib_Scripts__004ec38c[]; /* used by 3 fn(s), first 0x0049a410 */
extern undefined DAT_004ec3b8; /* used by 4 fn(s), first 0x0049bcc0 */
extern char s__system_lua_004ec3bc[]; /* used by 1 fn(s), first 0x0049c5e0 */
extern undefined DAT_004ec3c8; /* used by 1 fn(s), first 0x0049c600 */
extern char s_camChangeHandler_004ec3d0[]; /* used by 2 fn(s), first 0x0049c660 */
extern char s_postCamChangeHandler_004ec3e4[]; /* used by 1 fn(s), first 0x0049c6e0 */
extern char s_collisionHandler_004ec3fc[]; /* used by 1 fn(s), first 0x0049c750 */
extern char s_movieTime_004ec410[]; /* used by 1 fn(s), first 0x0049c8f0 */
extern char s_frameTime_004ec41c[]; /* used by 1 fn(s), first 0x0049c8f0 */
extern char s__s___s____s__d__004ec428[]; /* used by 1 fn(s), first 0x0049cbe0 */
extern char s_unnamed_function_004ec43c[]; /* used by 1 fn(s), first 0x0049cbe0 */
extern char s_tag_method_004ec450[]; /* used by 1 fn(s), first 0x0049cbe0 */
extern char s_function_004ec45c[]; /* used by 1 fn(s), first 0x0049cbe0 */
extern char s__unknown__004ec468[]; /* used by 1 fn(s), first 0x0049cbe0 */
extern char s_actor_004ec474[]; /* used by 1 fn(s), first 0x0049d140 */
extern char s_costume_004ec47c[]; /* used by 1 fn(s), first 0x0049d140 */
extern char s_keyframe_004ec484[]; /* used by 1 fn(s), first 0x0049d140 */
extern undefined DAT_004ec490; /* used by 2 fn(s), first 0x0049d140 */
extern char s__actor_d__s__004ec494[]; /* used by 1 fn(s), first 0x0049d220 */
extern char s__nil__004ec4a4[]; /* used by 2 fn(s), first 0x0049d220 */
extern char s_costumeOverrideHandler_004ec4ac[]; /* used by 1 fn(s), first 0x0049d550 */
extern char s_costumeMarkerHandler_004ec4c4[]; /* used by 1 fn(s), first 0x0049d670 */
extern char s_userPaintHandler_004ec4dc[]; /* used by 1 fn(s), first 0x0049d7b0 */
extern char s_exitHandler_004ec4f0[]; /* used by 1 fn(s), first 0x0049d890 */
extern char s_pauseHandler_004ec4fc[]; /* used by 1 fn(s), first 0x0049d970 */
extern char s_characterHandler_004ec50c[]; /* used by 1 fn(s), first 0x0049da50 */
extern char s_concat_004ec520[]; /* used by 1 fn(s), first 0x0049de00 */
extern undefined DAT_004ec528; /* used by 1 fn(s), first 0x0049de00 */
extern char s_SPECIAL_004ec52c[]; /* used by 1 fn(s), first 0x0049de00 */
extern char s_CAMERA_004ec534[]; /* used by 1 fn(s), first 0x0049de00 */
extern undefined DAT_004ec53c; /* used by 1 fn(s), first 0x0049de00 */
extern undefined DAT_004ec544; /* used by 1 fn(s), first 0x0049de00 */
extern undefined DAT_004ec54c; /* used by 1 fn(s), first 0x0049de00 */
extern undefined DAT_004ec554; /* used by 1 fn(s), first 0x0049de00 */
extern char s_TextAllowed_004ec55c[]; /* used by 1 fn(s), first 0x0049de00 */
extern char s_axisHandler_004ec568[]; /* used by 2 fn(s), first 0x0049e0b0 */
extern char s_buttonHandler_004ec574[]; /* used by 2 fn(s), first 0x0049e0b0 */
extern char s_system_004ec584[]; /* used by 1 fn(s), first 0x0049e380 */
extern char s_controls_004ec58c[]; /* used by 1 fn(s), first 0x0049e460 */
extern undefined DAT_004ec598; /* used by 3 fn(s), first 0x004a0400 */
extern char s_global_004ec5a0[]; /* used by 1 fn(s), first 0x004a0400 */
extern char s_parallel_004ec5a8[]; /* used by 2 fn(s), first 0x004a0400 */
extern undefined DAT_004ec5b4; /* used by 2 fn(s), first 0x004a0530 */
extern undefined DAT_004ec5bc; /* used by 2 fn(s), first 0x004a2e20 */
extern char s_saveGameCallback_004ec5c0[]; /* used by 1 fn(s), first 0x004a34c0 */
extern char s_dfltroom_bm_004ec5d4[]; /* used by 2 fn(s), first 0x004a3db0 */
extern char s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0[]; /* used by 11 fn(s), first 0x004a3db0 */
extern undefined DAT_004ec60c; /* used by 4 fn(s), first 0x004a3db0 */
extern char s_Bad_ZBuffer_Reference_004ec614[]; /* used by 2 fn(s), first 0x004a3ef0 */
extern char s_Bad_room_Reference_004ec62c[]; /* used by 2 fn(s), first 0x004a40f0 */
extern char s_penumbraangle__f_004ec654[]; /* used by 1 fn(s), first 0x004bed40 */
extern char s_umbraangle__f_004ec668[]; /* used by 1 fn(s), first 0x004bed40 */
extern char s_intensity__f_004ec67c[]; /* used by 1 fn(s), first 0x004bed40 */
extern char s_direction__f__f__f_004ec68c[]; /* used by 1 fn(s), first 0x004bed40 */
extern char s_position__f__f__f_004ec6a4[]; /* used by 1 fn(s), first 0x004bed40 */
extern char s_section__lights_004ec6fc[]; /* used by 1 fn(s), first 0x004bed40 */
extern char s_dfltcmp_cmp_004ec710[]; /* used by 1 fn(s), first 0x004a4fe0 */
extern char s_sectors_004ec71c[]; /* used by 1 fn(s), first 0x004a53b0 */
extern char s_lights_004ec724[]; /* used by 2 fn(s), first 0x004a53b0 */
extern char s_setups_004ec72c[]; /* used by 1 fn(s), first 0x004a53b0 */
extern char s_colormaps_004ec734[]; /* used by 1 fn(s), first 0x004a53b0 */
extern char s_section___s_004ec740[]; /* used by 1 fn(s), first 0x004a5550 */
extern char s_color__d__d__d_004ec74c[]; /* used by 1 fn(s), first 0x004a5600 */
extern char s_penumbraangle__f_004ec75c[]; /* used by 1 fn(s), first 0x004a5600 */
extern char s_umbraangle__f_004ec770[]; /* used by 1 fn(s), first 0x004a5600 */
extern char s_intensity__f_004ec780[]; /* used by 1 fn(s), first 0x004a5600 */
extern char s_position__f__f__f_004ec790[]; /* used by 2 fn(s), first 0x004a5600 */
extern char s_direction__f__f__f_004ec7a4[]; /* used by 1 fn(s), first 0x004a5600 */
extern char s_type__s_004ec7b8[]; /* used by 2 fn(s), first 0x004a5600 */
extern char s_light__s_004ec7c4[]; /* used by 1 fn(s), first 0x004a5600 */
extern char s_numlights__d_004ec7d0[]; /* used by 1 fn(s), first 0x004a5600 */
extern char s_section___s_004ec7e0[]; /* used by 3 fn(s), first 0x004a5600 */
extern char s_fclip__f_004ec7f0[]; /* used by 1 fn(s), first 0x004a5890 */
extern char s_nclip__f_004ec7fc[]; /* used by 1 fn(s), first 0x004a5890 */
extern char s_fov__f_004ec808[]; /* used by 1 fn(s), first 0x004a5890 */
extern char s_roll__f_004ec810[]; /* used by 1 fn(s), first 0x004a5890 */
extern char s_interest__f__f__f_004ec81c[]; /* used by 1 fn(s), first 0x004a5890 */
extern char s_zbuffer__s_004ec830[]; /* used by 1 fn(s), first 0x004a5890 */
extern char s_background__s_004ec83c[]; /* used by 1 fn(s), first 0x004a5890 */
extern char s_setup__s_004ec84c[]; /* used by 1 fn(s), first 0x004a5890 */
extern char s_numsetups__d_004ec858[]; /* used by 1 fn(s), first 0x004a5890 */
extern char s_colormap__s_004ec868[]; /* used by 1 fn(s), first 0x004a5b40 */
extern char s_numcolormaps__d_004ec878[]; /* used by 1 fn(s), first 0x004a5b40 */
extern char s_pRoom__apColormaps____NULL_004ec88c[]; /* used by 1 fn(s), first 0x004a5b40 */
extern char s_tot_verts___MAX_DB_VERTS___2_004ec8a8[]; /* used by 1 fn(s), first 0x004a7ab0 */
extern char s_C__grimsrc_libs_grimlib_Engine_W_004ec8c8[]; /* used by 3 fn(s), first 0x004a7ab0 */
extern char s__f__f__f_004ec8f8[]; /* used by 1 fn(s), first 0x004a7bc0 */
extern char s_vertices___f__f__f_004ec904[]; /* used by 1 fn(s), first 0x004a7bc0 */
extern char s_numgates__s_004ec918[]; /* used by 1 fn(s), first 0x004a7bc0 */
extern char s_numvertices__d_004ec928[]; /* used by 1 fn(s), first 0x004a7bc0 */
extern char s_height__f_004ec938[]; /* used by 1 fn(s), first 0x004a7bc0 */
extern undefined DAT_004ec944; /* used by 1 fn(s), first 0x004a7bc0 */
extern char s_default_visibility__s_004ec950[]; /* used by 1 fn(s), first 0x004a7bc0 */
extern undefined DAT_004ec968; /* used by 1 fn(s), first 0x004a7bc0 */
extern undefined DAT_004ec974; /* used by 1 fn(s), first 0x004a7bc0 */
extern undefined DAT_004ec97c; /* used by 1 fn(s), first 0x004a7bc0 */
extern undefined DAT_004ec984; /* used by 1 fn(s), first 0x004a7bc0 */
extern undefined DAT_004ec98c; /* used by 1 fn(s), first 0x004a7bc0 */
extern char s_id__i_004ec994[]; /* used by 1 fn(s), first 0x004a7bc0 */
extern char s_sector__s_004ec99c[]; /* used by 1 fn(s), first 0x004a7bc0 */
extern char s_numsectors_004ec9a8[]; /* used by 1 fn(s), first 0x004a7bc0 */
extern char s_edge_index___num_verts_004ec9b8[]; /* used by 1 fn(s), first 0x004a9070 */
extern char s_C__grimsrc_libs_grimlib_Engine_O_004ec9d0[]; /* used by 1 fn(s), first 0x004aa130 */
extern undefined4 UINT_004eca00; /* used by 1 fn(s), first 0x004aac40 */
extern undefined4 UINT_004eca04; /* used by 1 fn(s), first 0x004aac40 */
extern char s_c_____0______c______0______ppTex_004ed008[]; /* used by 1 fn(s), first 0x004aa9b0 */
extern char s__ppText______void___0__004ed03c[]; /* used by 1 fn(s), first 0x004aa9b0 */
extern char s_C__grimsrc_libs_grimlib_Temp_Tex_004ed054[]; /* used by 5 fn(s), first 0x004aa9b0 */
extern char s_hFont_004ed078[]; /* used by 4 fn(s), first 0x004aaa20 */
extern char s_wKernel_004ed080[]; /* used by 1 fn(s), first 0x004ac1f0 */
extern undefined *PTR_FUN_004ed098; /* used by 1 fn(s), first 0x004acd10 */
extern undefined *PTR__exit_004ed0b0; /* used by 1 fn(s), first 0x004acbe0 */
extern undefined4 UINT_004ed0b4; /* used by 4 fn(s), first 0x004b1d20 */
extern uint UINT_004ed0d4; /* used by 2 fn(s), first 0x004af72d */
extern uint UINT_004ed0d8; /* used by 2 fn(s), first 0x004af72d */
extern uint UINT_004ed0dc; /* used by 2 fn(s), first 0x004af72d */
extern undefined DAT_004ed0e0; /* used by 2 fn(s), first 0x004af7e0 */
extern undefined *PTR_DAT_004ed0e4; /* used by 1 fn(s), first 0x004af7b0 */
extern undefined *PTR_DAT_004ed104; /* used by 1 fn(s), first 0x004af7b0 */
extern undefined *PTR_DAT_004ed114; /* used by 1 fn(s), first 0x004af7b0 */
extern undefined *PTR_DAT_004ed124; /* used by 1 fn(s), first 0x004af7b0 */
extern undefined *PTR_DAT_004ed2fc; /* used by 1 fn(s), first 0x004afa90 */
extern undefined *PTR_DAT_004ed300; /* used by 1 fn(s), first 0x004afa90 */
extern undefined *PTR_FUN_004ed308; /* used by 2 fn(s), first 0x004ac6b0 */
extern undefined *PTR_FUN_004ed30c; /* used by 2 fn(s), first 0x004ac6b0 */
extern undefined *PTR_FUN_004ed310; /* used by 2 fn(s), first 0x004ac6b0 */
extern undefined *PTR_FUN_004ed314; /* used by 2 fn(s), first 0x004ac6b0 */
extern undefined *PTR_FUN_004ed318; /* used by 1 fn(s), first 0x004ac6b0 */
extern undefined *PTR_FUN_004ed31c; /* used by 1 fn(s), first 0x004ac6b0 */
extern undefined *PTR_DAT_004ed320; /* used by 16 fn(s), first 0x004ac790 */
extern undefined *PTR_DAT_004ed324; /* used by 1 fn(s), first 0x004b69e0 */
extern undefined DAT_004ed32a; /* used by 2 fn(s), first 0x004b0fa0 */
extern undefined4 UINT_004ed52c; /* used by 15 fn(s), first 0x004ac790 */
extern undefined DAT_004ed530; /* used by 7 fn(s), first 0x004b05f0 */
extern undefined DAT_004ed534; /* used by 1 fn(s), first 0x004b64f0 */
extern undefined4 UINT_004ed540; /* used by 2 fn(s), first 0x004b0c30 */
extern undefined DAT_004ed548; /* used by 1 fn(s), first 0x004b0c90 */
extern undefined4 UINT_004ed5c0; /* used by 2 fn(s), first 0x004b0d30 */
extern undefined4 UINT_004ed5c4; /* used by 2 fn(s), first 0x004b0d30 */
extern undefined4 UINT_004ed5cc; /* used by 2 fn(s), first 0x004b0f40 */
extern undefined DAT_004ed5d0; /* used by 1 fn(s), first 0x004b14e0 */
extern undefined4 UINT_004ed5d8; /* used by 1 fn(s), first 0x004b14e0 */
extern undefined DAT_004ed6c8; /* used by 6 fn(s), first 0x004af960 */
extern undefined4 UINT_004ed6f0; /* used by 1 fn(s), first 0x004b1d60 */
extern undefined *PTR_DAT_004ed780; /* used by 2 fn(s), first 0x004b1d60 */
extern undefined4 UINT_004ed790; /* used by 1 fn(s), first 0x004b2040 */
extern undefined DAT_004ed7a0; /* used by 3 fn(s), first 0x004acc40 */
extern undefined DAT_004ed7c0; /* used by 2 fn(s), first 0x004af960 */
extern undefined *PTR_LOOP_004eda00; /* used by 4 fn(s), first 0x004b21b0 */
extern undefined *PTR_LOOP_004eda04; /* used by 2 fn(s), first 0x004b21b0 */
extern undefined4 UINT_004eda10; /* used by 2 fn(s), first 0x004b21b0 */
extern undefined *PTR_LOOP_004efa20; /* used by 2 fn(s), first 0x004b2320 */
extern undefined4 UINT_004efa24; /* used by 3 fn(s), first 0x004acfe0 */
extern undefined4 UINT_004efa28; /* used by 1 fn(s), first 0x004b3480 */
extern char s_____004efb90[]; /* used by 2 fn(s), first 0x004b3480 */
extern undefined DAT_004efb98; /* used by 1 fn(s), first 0x004b3620 */
extern undefined DAT_004efba0; /* used by 1 fn(s), first 0x004ae562 */
extern undefined DAT_004efc00; /* used by 1 fn(s), first 0x004ae562 */
extern undefined *PTR_terminate_004efc40; /* used by 1 fn(s), first 0x004b5cf0 */
extern undefined DAT_004f03d0; /* used by 1 fn(s), first 0x004b7540 */
extern undefined DAT_004f03e8; /* used by 1 fn(s), first 0x004b7560 */
extern undefined4 UINT_004f0400; /* used by 5 fn(s), first 0x004b29a0 */
extern undefined4 UINT_004f0404; /* used by 4 fn(s), first 0x004b50f0 */
extern undefined4 UINT_004f0408; /* used by 5 fn(s), first 0x004b50f0 */
extern undefined *PTR_DAT_004f0490; /* used by 1 fn(s), first 0x004b7f40 */
extern undefined *PTR_DAT_004f0494; /* used by 1 fn(s), first 0x004b7f40 */
extern uint UINT_004f0498; /* used by 3 fn(s), first 0x004b7f40 */
extern uint UINT_004f049c; /* used by 2 fn(s), first 0x004b8250 */
extern undefined4 UINT_004f04a0; /* used by 2 fn(s), first 0x004b8250 */
extern uint UINT_004f04a8; /* used by 3 fn(s), first 0x004b7f40 */
extern uint UINT_004f04ac; /* used by 2 fn(s), first 0x004b8250 */
extern undefined4 UINT_004f04b0; /* used by 2 fn(s), first 0x004b8250 */
extern undefined DAT_004f04dc; /* used by 1 fn(s), first 0x004b9916 */
extern undefined DAT_004f04f4; /* used by 1 fn(s), first 0x004b9b1c */
extern undefined DAT_004f050c; /* used by 1 fn(s), first 0x004b9916 */
extern undefined4 UINT_004f0620; /* used by 2 fn(s), first 0x004b4d90 */
extern uint UINT_004f0624; /* used by 2 fn(s), first 0x004b4d90 */
extern undefined4 UINT_004f0628; /* used by 1 fn(s), first 0x004b4d90 */
extern undefined4 UINT_004f062c; /* used by 1 fn(s), first 0x004b4d90 */
extern undefined4 UINT_004f0630; /* used by 1 fn(s), first 0x004bc0a0 */
extern undefined4 UINT_004f0634; /* used by 1 fn(s), first 0x004bc0a0 */
extern undefined4 UINT_004f0640; /* used by 1 fn(s), first 0x004b4d90 */
extern uint UINT_004f0644; /* used by 2 fn(s), first 0x004b4d90 */
extern undefined DAT_004f0648; /* used by 2 fn(s), first 0x004b84c0 */
extern undefined DAT_004f067c; /* used by 2 fn(s), first 0x004b50f0 */
extern undefined4 UINT_004f0680; /* used by 3 fn(s), first 0x004b7cc0 */
extern undefined *PTR_DAT_004f06b8; /* used by 1 fn(s), first 0x004b5d80 */
extern undefined *PTR_PTR_004f0764; /* used by 1 fn(s), first 0x004b5d80 */
extern undefined DAT_004f0768; /* used by 1 fn(s), first 0x004b64f0 */
extern undefined *PTR_DAT_004f0770; /* used by 1 fn(s), first 0x004b6730 */
extern undefined *PTR_DAT_004f0774; /* used by 1 fn(s), first 0x004b6730 */
extern undefined *PTR_DAT_004f0778; /* used by 1 fn(s), first 0x004b6730 */
extern undefined *PTR_PTR_004f07a0; /* used by 2 fn(s), first 0x004b64f0 */
extern undefined4 UINT_004f0888; /* used by 1 fn(s), first 0x004b9ea0 */
extern undefined *PTR_PTR_004f0b70; /* used by 2 fn(s), first 0x004bd440 */
extern undefined *PTR_FUN_004f0ba0; /* used by 1 fn(s), first 0x004bd3a0 */
extern undefined *PTR_FUN_004f0c18; /* used by 1 fn(s), first 0x004bdf70 */
extern undefined *PTR_FUN_004f0c28; /* used by 1 fn(s), first 0x004bdf70 */
extern undefined *PTR_FUN_004f0c38; /* used by 1 fn(s), first 0x004be050 */
extern undefined *PTR_FUN_004f0c48; /* used by 1 fn(s), first 0x004be050 */
extern char s_FILIO_insane_stdio_004f0c64[]; /* used by 2 fn(s), first 0x004be050 */
extern char s_FILIO_insane_zfilio_004f0ca0[]; /* used by 3 fn(s), first 0x004bd3a0 */
extern undefined DAT_004f0cb4; /* used by 1 fn(s), first 0x004bd440 */
extern undefined DAT_004f0cb8; /* used by 1 fn(s), first 0x004bd440 */
extern undefined DAT_004f0cbc; /* used by 1 fn(s), first 0x004bd440 */
extern undefined DAT_004f0cc4; /* used by 1 fn(s), first 0x004bd440 */
extern char s_MEMORY_insane_004f0ccc[]; /* used by 2 fn(s), first 0x004bdf70 */
extern char s_LECMODULE_insane_memory_004f0cdc[]; /* used by 2 fn(s), first 0x004bdf70 */
extern char s_LECMODULE_insane_stdio_004f0cf4[]; /* used by 2 fn(s), first 0x004be050 */
extern undefined4 UINT_004f0d0c; /* used by 1 fn(s), first 0x004be180 */
extern undefined *PTR_s_Error_004f0d14; /* used by 1 fn(s), first 0x004be990 */
extern undefined DAT_004f0d18; /* used by 1 fn(s), first 0x004bffb0 */
extern undefined DAT_004f0d1c; /* used by 1 fn(s), first 0x004bffb0 */
extern char s_x_spot_cos_004f0d28[]; /* used by 1 fn(s), first 0x004be180 */
extern char s_LightManager_Startup__Could_not_c_004f0d34[]; /* used by 1 fn(s), first 0x004be180 */
extern char s_newlight_d_004f0d6c[]; /* used by 1 fn(s), first 0x004be730 */
extern char s_Could_not_open_file___s___004f0dc8[]; /* used by 1 fn(s), first 0x004be990 */
extern char s_section__004f0e00[]; /* used by 1 fn(s), first 0x004be990 */
extern char s_Set_Files____set__004f0e0c[]; /* used by 1 fn(s), first 0x004be990 */
extern char s_LightManager_UpdateDialog__No_cu_004f0e3c[]; /* used by 1 fn(s), first 0x004beee0 */
extern char s__Light__d__004f0e68[]; /* used by 1 fn(s), first 0x004bef10 */
extern char s_New_light_name_004f0ec8[]; /* used by 1 fn(s), first 0x004bf950 */
extern undefined2 DAT_004f0ed8; /* used by 1 fn(s), first 0x004c04f0 */
extern char s_C__grimjedi_Libs_RDroid_Engine_R_004f0edc[]; /* used by 1 fn(s), first 0x004c04f0 */
extern undefined2 DAT_004f0f08; /* used by 1 fn(s), first 0x004c0660 */
extern undefined2 DAT_004f0f0c; /* used by 1 fn(s), first 0x004c0770 */
extern undefined2 DAT_004f0f10; /* used by 1 fn(s), first 0x004c0ce0 */
extern char s_C__grimjedi_Libs_RDroid_Engine_R_004f0f14[]; /* used by 3 fn(s), first 0x004c0660 */
extern char s__f__f__f__f__f__f_004f0f40[]; /* used by 1 fn(s), first 0x004c0770 */
extern char s__d___f__x__f__f__f__f__f__f_004f0f54[]; /* used by 1 fn(s), first 0x004c0770 */
extern char s_entries__d_004f0f74[]; /* used by 1 fn(s), first 0x004c0770 */
extern char s_mesh_name__s_004f0f80[]; /* used by 1 fn(s), first 0x004c0770 */
extern char s_node__d_004f0f90[]; /* used by 1 fn(s), first 0x004c0770 */
extern char s_nodes__d_004f0f9c[]; /* used by 1 fn(s), first 0x004c0770 */
extern char s__f__d_004f0fa8[]; /* used by 1 fn(s), first 0x004c0770 */
extern char s_markers__d_004f0fb0[]; /* used by 1 fn(s), first 0x004c0770 */
extern undefined DAT_004f0fbc; /* used by 1 fn(s), first 0x004c0770 */
extern char s_joints__d_004f0fc4[]; /* used by 1 fn(s), first 0x004c0770 */
extern char s_fps__f_004f0fd0[]; /* used by 1 fn(s), first 0x004c0770 */
extern char s_frames__d_004f0fd8[]; /* used by 1 fn(s), first 0x004c0770 */
extern char s_type__x_004f0fe4[]; /* used by 1 fn(s), first 0x004c0770 */
extern char s_flags__x_004f0ff0[]; /* used by 1 fn(s), first 0x004c0770 */
extern undefined4 UINT_004f1000; /* used by 1 fn(s), first 0x004c0ed0 */
extern undefined2 DAT_004f11c0; /* used by 1 fn(s), first 0x004c1170 */
extern undefined DAT_004f11c4; /* used by 1 fn(s), first 0x004c1170 */
extern undefined DAT_004f11c8; /* used by 1 fn(s), first 0x004c1170 */
extern char s_C__grimjedi_Libs_Std_General_Std_004f11d0[]; /* used by 1 fn(s), first 0x004c1170 */
extern undefined *PTR_LecShare_Register_004f1200; /* used by 1 fn(s), first 0x004c1390 */
extern undefined *PTR_LecShare_Nop_004f1220; /* used by 4 fn(s), first 0x004c1390 */
extern char s_LECMODULE_004f1224[]; /* used by 3 fn(s), first 0x004c13f0 */
extern char s_LecShare_Startup__Failed_with_mo_004f1230[]; /* used by 1 fn(s), first 0x004c1460 */
extern char s_LecShare_BatchSubscribe_Couldn_t_004f125c[]; /* used by 1 fn(s), first 0x004c1850 */
extern char s_LecShare_BatchUnsubscribe_Couldn_004f1298[]; /* used by 1 fn(s), first 0x004c1900 */
extern undefined *PTR_FUN_004f12e0; /* used by 1 fn(s), first 0x004c1f40 */
extern undefined *PTR_FUN_004f12f0; /* used by 1 fn(s), first 0x004c1f40 */
extern undefined *PTR_FUN_004f1318; /* used by 1 fn(s), first 0x004c3c90 */
extern undefined *PTR_FUN_004f131c; /* used by 2 fn(s), first 0x004c3c00 */
extern undefined *PTR_FUN_004f1328; /* used by 1 fn(s), first 0x004c1f40 */
extern undefined4 UINT_004f1334; /* used by 1 fn(s), first 0x004c25c0 */
extern char s_DEBUG_insane_animplay_004f1338[]; /* used by 2 fn(s), first 0x004c1f40 */
extern char s_ANIMPLAY_insane_004f1350[]; /* used by 2 fn(s), first 0x004c1f40 */
extern char s_LECMODULE_insane_animplay_004f1360[]; /* used by 2 fn(s), first 0x004c1f40 */
extern char s_AnimPlay_Module__Cannot_allocate_004f137c[]; /* used by 1 fn(s), first 0x004c1ff0 */
extern char s_AnimPlay_Module__Cannot_allocate_004f13b0[]; /* used by 1 fn(s), first 0x004c1ff0 */
extern char s_AnimPlay_Module__Cannot_allocate_004f13e4[]; /* used by 1 fn(s), first 0x004c1ff0 */
extern char s_AnimPlay_Module__Cannot_allocate_004f141c[]; /* used by 1 fn(s), first 0x004c1ff0 */
extern char s_AnimPlay_Module__Cannot_allocate_004f1450[]; /* used by 1 fn(s), first 0x004c1ff0 */
extern char s_SOUND_lipsync_004f1484[]; /* used by 1 fn(s), first 0x004c1ff0 */
extern char s_TIMER_clocks_004f1494[]; /* used by 1 fn(s), first 0x004c1ff0 */
extern char s_BITMAP_buffers_004f14a4[]; /* used by 2 fn(s), first 0x004c1ff0 */
extern char s_ANIMFRAME_render_004f14b4[]; /* used by 1 fn(s), first 0x004c1ff0 */
extern char s_STREAMER_spooler_004f14c8[]; /* used by 1 fn(s), first 0x004c1ff0 */
extern char s_VIRTHERC_debug_004f14dc[]; /* used by 3 fn(s), first 0x004c1ff0 */
extern char s_MEMORY_workspace_004f14ec[]; /* used by 7 fn(s), first 0x004c1ff0 */
extern char s_Cannot_allocate_render_bitmap__004f1500[]; /* used by 1 fn(s), first 0x004c21e0 */
extern char s_AnimPlay_Module__Cannot_allocate_004f1520[]; /* used by 1 fn(s), first 0x004c23c0 */
extern char s_AnimPlay_Module__Cannot_init_Ani_004f1554[]; /* used by 1 fn(s), first 0x004c23c0 */
extern char s_AnimPlay_Module__Cannot_open_fil_004f1584[]; /* used by 1 fn(s), first 0x004c23c0 */
extern char s_AnimPlay_Module__Cannot_allocate_004f15ac[]; /* used by 1 fn(s), first 0x004c23c0 */
extern char s_AnimPlay_Module__Cannot_allocate_004f15d8[]; /* used by 1 fn(s), first 0x004c23c0 */
extern char s_C__grimsrc_libs_lecsmush_insane__004f1608[]; /* used by 2 fn(s), first 0x004c23c0 */
extern char s_State___d_004f1640[]; /* used by 1 fn(s), first 0x004c27a0 */
extern char s_Sync_Ticks___ld_004f1658[]; /* used by 1 fn(s), first 0x004c27a0 */
extern char s_Frame_Delay___ld___ld_target__004f1670[]; /* used by 1 fn(s), first 0x004c27a0 */
extern char s_Buffer___ld___004f1694[]; /* used by 1 fn(s), first 0x004c27a0 */
extern char s_Insane_AnimPlay_004f16ac[]; /* used by 1 fn(s), first 0x004c2b00 */
extern char s_Insane_AnimPlay_Debug_Interface_004f16bc[]; /* used by 1 fn(s), first 0x004c2b00 */
extern char s_This_is_the_debugging_interface_f_004f16dc[]; /* used by 1 fn(s), first 0x004c2b00 */
extern undefined4 UINT_004f1720; /* used by 1 fn(s), first 0x004c2fa0 */
extern undefined4 UINT_004f1724; /* used by 2 fn(s), first 0x004c34d0 */
extern undefined *PTR_FUN_004f1728; /* used by 1 fn(s), first 0x004c2b50 */
extern undefined *PTR_FUN_004f1738; /* used by 1 fn(s), first 0x004c2b50 */
extern undefined *PTR_FUN_004f1750; /* used by 1 fn(s), first 0x004c2b50 */
extern char s_DEBUG_animframe_004f175c[]; /* used by 2 fn(s), first 0x004c2b50 */
extern char s_ANIMFRAME_insane_004f176c[]; /* used by 2 fn(s), first 0x004c2b50 */
extern char s_LECMODULE_insane_animframe_004f1780[]; /* used by 2 fn(s), first 0x004c2b50 */
extern char s_FLOBDEC_temp_004f179c[]; /* used by 1 fn(s), first 0x004c2be0 */
extern char s_FLOBDEC_004f17ac[]; /* used by 1 fn(s), first 0x004c2be0 */
extern char s_AnimFrame_Module__Can_t_allocate_004f17b4[]; /* used by 1 fn(s), first 0x004c2be0 */
extern char s_AnimFrame_Module__Can_t_allocate_004f17f0[]; /* used by 1 fn(s), first 0x004c2be0 */
extern char s_C__grimsrc_libs_lecsmush_insane__004f182c[]; /* used by 2 fn(s), first 0x004c2be0 */
extern char s_VIDEO_display_004f1864[]; /* used by 1 fn(s), first 0x004c2be0 */
extern char s_AnimFrame_Module__Cannot_allocat_004f1874[]; /* used by 1 fn(s), first 0x004c2be0 */
extern char s_AnimFrame_Module__Cannot_allocat_004f18a8[]; /* used by 1 fn(s), first 0x004c2be0 */
extern char s_Bad_Header_Found___c_c_c_c__004f18dc[]; /* used by 1 fn(s), first 0x004c2fa0 */
extern char s_Found_Unknown_Block___c_c_c_c__004f18fc[]; /* used by 1 fn(s), first 0x004c2fa0 */
extern char s_Parsing_Block___c_c_c_c____ld__004f191c[]; /* used by 1 fn(s), first 0x004c2fa0 */
extern char s_Insane_AnimFrame_004f193c[]; /* used by 1 fn(s), first 0x004c3660 */
extern char s_Insane_AnimFrame_Debug_Interface_004f1950[]; /* used by 1 fn(s), first 0x004c3660 */
extern char s_This_is_the_debugging_interface_f_004f1974[]; /* used by 1 fn(s), first 0x004c3660 */
extern char s_Read_invalid_frame_header__c_c_c_004f19bc[]; /* used by 1 fn(s), first 0x004c36f0 */
extern undefined4 UINT_004f1a00; /* used by 2 fn(s), first 0x004c3e60 */
extern undefined4 UINT_004f1a04; /* used by 1 fn(s), first 0x004c3e60 */
extern char s__c_c_c_c_c_c_c_c_c_c_004f1a08[]; /* used by 2 fn(s), first 0x004c3e60 */
extern char s_1_1_3_004f1a20[]; /* used by 2 fn(s), first 0x004c3e60 */
extern undefined DAT_004f1a28; /* used by 1 fn(s), first 0x004c4a00 */
extern undefined *PTR_FUN_004f1a30; /* used by 1 fn(s), first 0x004c4b20 */
extern undefined *PTR_FUN_004f1a40; /* used by 1 fn(s), first 0x004c4b20 */
extern char s_STREAMER_insane_streamer_004f1a60[]; /* used by 2 fn(s), first 0x004c4b20 */
extern char s_LECMODULE_insane_streamer_004f1a7c[]; /* used by 2 fn(s), first 0x004c4b20 */
extern char s_Streamer_Module__Cannot_allocate_004f1a98[]; /* used by 1 fn(s), first 0x004c4b90 */
extern char s_Streamer_Module__Cannot_allocate_004f1acc[]; /* used by 1 fn(s), first 0x004c4b90 */
extern char s_FILIO_io_004f1b00[]; /* used by 1 fn(s), first 0x004c4b90 */
extern char s_C__grimsrc_libs_lecsmush_insane__004f1b0c[]; /* used by 2 fn(s), first 0x004c4c50 */
extern char s_File_Streamer__Invalid_frame_siz_004f1b44[]; /* used by 1 fn(s), first 0x004c50a0 */
extern undefined *PTR_FUN_004f1b70; /* used by 1 fn(s), first 0x004c5280 */
extern undefined *PTR_FUN_004f1b80; /* used by 1 fn(s), first 0x004c5280 */
extern char s_DIRECTORY_insane_directory_004f1ba4[]; /* used by 2 fn(s), first 0x004c5280 */
extern char s_LECMODULE_insane_directory_004f1bc0[]; /* used by 2 fn(s), first 0x004c5280 */
extern char s_Directory_Module__Cannot_allocat_004f1bdc[]; /* used by 1 fn(s), first 0x004c52f0 */
extern char s_FILE_io_004f1c10[]; /* used by 1 fn(s), first 0x004c52f0 */
extern undefined DAT_004f1c18; /* used by 1 fn(s), first 0x004c5720 */
extern uint UINT_004f1c20; /* used by 2 fn(s), first 0x004c57d0 */
extern undefined *PTR_DAT_004f1c28; /* used by 2 fn(s), first 0x004c57d0 */
extern undefined DAT_004f1cf0; /* used by 1 fn(s), first 0x004c5950 */
extern undefined *PTR_FUN_004f1cf8; /* used by 1 fn(s), first 0x004c5790 */
extern undefined *PTR_FUN_004f1d08; /* used by 1 fn(s), first 0x004c5790 */
extern char s_LECMODULE_insane_zfilio_004f1d24[]; /* used by 2 fn(s), first 0x004c5790 */
extern char s_Too_many_zfilio_extension_set_004f1d3c[]; /* used by 1 fn(s), first 0x004c57d0 */
extern char s_Zfile_Module__Cannot_allocate_me_004f1d5c[]; /* used by 1 fn(s), first 0x004c5870 */
extern char s_Zfile_Module__Cannot_allocate_fi_004f1d8c[]; /* used by 1 fn(s), first 0x004c5870 */
extern char s_MEMORY_buffers_004f1dbc[]; /* used by 1 fn(s), first 0x004c5870 */
extern char s_FILIO_chainto_004f1dcc[]; /* used by 2 fn(s), first 0x004c5870 */
extern char s_Zfile_Memory_Alloc_fail_004f1ddc[]; /* used by 1 fn(s), first 0x004c5950 */
extern char s_C__grimsrc_libs_lecsmush_insane__004f1df4[]; /* used by 2 fn(s), first 0x004c5950 */
extern undefined *PTR_FUN_004f1e30; /* used by 1 fn(s), first 0x004c5ce0 */
extern undefined *PTR_FUN_004f1e40; /* used by 1 fn(s), first 0x004c5ce0 */
extern char s_FILE_insane_stdfile_004f1e74[]; /* used by 2 fn(s), first 0x004c5ce0 */
extern char s_LECMODULE_insane_stdfile_004f1e88[]; /* used by 2 fn(s), first 0x004c5ce0 */
extern char s_StdFile_Module__Cannot_allocate_f_004f1ea4[]; /* used by 1 fn(s), first 0x004c5d50 */
extern char s_need_dictionary_004f1ed4[]; /* used by 1 fn(s), first 0x004c61f0 */
extern char s_incorrect_data_check_004f1ee4[]; /* used by 1 fn(s), first 0x004c61f0 */
extern char s_incorrect_header_check_004f1efc[]; /* used by 1 fn(s), first 0x004c61f0 */
extern char s_invalid_window_size_004f1f14[]; /* used by 1 fn(s), first 0x004c61f0 */
extern char s_unknown_compression_method_004f1f28[]; /* used by 1 fn(s), first 0x004c61f0 */
extern undefined *PTR_s_1_1_3_004f1f44; /* used by 1 fn(s), first 0x004c6640 */
extern undefined *PTR_DAT_004f1f50; /* used by 1 fn(s), first 0x004c4a00 */
extern undefined *PTR_s_stream_error_004f1f58; /* used by 2 fn(s), first 0x004c4a00 */
extern undefined *PTR_s_insufficient_memory_004f1f60; /* used by 1 fn(s), first 0x004c6640 */
extern undefined *PTR_s_buffer_error_004f1f64; /* used by 1 fn(s), first 0x004c68f0 */
extern char s_invalid_bit_length_repeat_004f1fe0[]; /* used by 1 fn(s), first 0x004c7c50 */
extern char s_too_many_length_or_distance_symb_004f1ffc[]; /* used by 1 fn(s), first 0x004c7c50 */
extern char s_invalid_stored_block_lengths_004f2020[]; /* used by 1 fn(s), first 0x004c7c50 */
extern char s_invalid_block_type_004f2040[]; /* used by 1 fn(s), first 0x004c7c50 */
extern undefined *PTR_DAT_004f2058; /* used by 1 fn(s), first 0x004c8ac0 */
extern undefined *PTR_DAT_004f2070; /* used by 1 fn(s), first 0x004c8ac0 */
extern undefined DAT_004f2088; /* used by 1 fn(s), first 0x004c8ac0 */
extern char s_invalid_distance_code_004f209c[]; /* used by 2 fn(s), first 0x004ca660 */
extern char s_invalid_literal_length_code_004f20b4[]; /* used by 2 fn(s), first 0x004ca660 */
extern undefined4 UINT_004f20d0; /* used by 1 fn(s), first 0x004cb520 */
extern undefined4 UINT_004f20d4; /* used by 1 fn(s), first 0x004cb520 */
extern undefined DAT_004f20d8; /* used by 1 fn(s), first 0x004cb520 */
extern undefined DAT_004f30d8; /* used by 1 fn(s), first 0x004cb520 */
extern char s_incomplete_dynamic_bit_lengths_t_004f31d8[]; /* used by 1 fn(s), first 0x004cae30 */
extern char s_oversubscribed_dynamic_bit_lengt_004f31fc[]; /* used by 1 fn(s), first 0x004cae30 */
extern char s_incomplete_literal_length_tree_004f3224[]; /* used by 1 fn(s), first 0x004cb390 */
extern char s_oversubscribed_literal_length_tr_004f3244[]; /* used by 1 fn(s), first 0x004cb390 */
extern char s_empty_distance_tree_with_lengths_004f3268[]; /* used by 1 fn(s), first 0x004cb390 */
extern char s_incomplete_distance_tree_004f328c[]; /* used by 1 fn(s), first 0x004cb390 */
extern char s_oversubscribed_distance_tree_004f32a8[]; /* used by 1 fn(s), first 0x004cb390 */
extern undefined DAT_004f32c8; /* used by 3 fn(s), first 0x004c7c50 */
extern undefined *PTR_FUN_004f3310; /* used by 1 fn(s), first 0x004cba30 */
extern undefined *PTR_FUN_004f3320; /* used by 1 fn(s), first 0x004cba30 */
extern uint UINT_004f3340; /* used by 1 fn(s), first 0x004cbc00 */
extern undefined DAT_004f3348; /* used by 1 fn(s), first 0x004cbf50 */
extern char s_FLOBDEC_insane_wave_004f3368[]; /* used by 2 fn(s), first 0x004cba30 */
extern char s_LECMODULE_insane_wave_flobdec_004f337c[]; /* used by 2 fn(s), first 0x004cba30 */
extern char s_C__grimsrc_libs_lecsmush_insane__004f339c[]; /* used by 2 fn(s), first 0x004cbaa0 */
extern char s_D_WAVE__Cannot_allocate_memory_s_004f33d8[]; /* used by 1 fn(s), first 0x004cbaa0 */
extern char s_MEMORY_004f3404[]; /* used by 1 fn(s), first 0x004cbaa0 */
extern char s_D_WAVE__Cannot_allocate_sound_se_004f340c[]; /* used by 1 fn(s), first 0x004cbaa0 */
extern char s_SOUND_004f3434[]; /* used by 1 fn(s), first 0x004cbaa0 */
extern char s_Audio_004f343c[]; /* used by 1 fn(s), first 0x004cbb80 */
extern char s_Decompresses_VBR_ADPCM_16_bit_au_004f3444[]; /* used by 1 fn(s), first 0x004cbb80 */
extern char s_Decompresses_Variable_Bit_Rate_A_004f346c[]; /* used by 1 fn(s), first 0x004cbb80 */
extern uint UINT_004f34a0; /* used by 1 fn(s), first 0x004cbc00 */
extern uint UINT_004f34a8; /* used by 1 fn(s), first 0x004cbc00 */
extern undefined4 UINT_004f34b0; /* used by 1 fn(s), first 0x004cbc00 */
extern undefined *PTR_FUN_004f34b8; /* used by 1 fn(s), first 0x004cc210 */
extern undefined *PTR_FUN_004f34c8; /* used by 1 fn(s), first 0x004cc210 */
extern undefined2 DAT_004f34e8; /* used by 1 fn(s), first 0x004cc6a0 */
extern uint UINT_004f38e4; /* used by 1 fn(s), first 0x004cc6a0 */
extern undefined4 UINT_004f38e8; /* used by 1 fn(s), first 0x004cc7d0 */
extern undefined4 UINT_004f3928; /* used by 1 fn(s), first 0x004cc7d0 */
extern undefined DAT_004f3968; /* used by 1 fn(s), first 0x004cc7d0 */
extern undefined DAT_004f39a8; /* used by 1 fn(s), first 0x004cc7d0 */
extern undefined4 UINT_004f39e8; /* used by 1 fn(s), first 0x004ccd00 */
extern char s_FLOBDEC_insane_blocky16_004f39ec[]; /* used by 2 fn(s), first 0x004cc210 */
extern char s_LECMODULE_insane_blocky16_flobde_004f3a04[]; /* used by 2 fn(s), first 0x004cc210 */
extern char s_FlobDec_Blocky16_Module__Cannot_a_004f3a28[]; /* used by 1 fn(s), first 0x004cc2c0 */
extern char s_FlobDec_Blocky16_Module__Cannot_a_004f3a64[]; /* used by 1 fn(s), first 0x004cc2c0 */
extern char s_BITMAP_clear_004f3aa0[]; /* used by 1 fn(s), first 0x004cc2c0 */
extern char s_Blocky16_Tile_004f3ab0[]; /* used by 1 fn(s), first 0x004cc370 */
extern char s_Decompresses_a_block16_tile_vide_004f3ac0[]; /* used by 1 fn(s), first 0x004cc370 */
extern char s_This_module_decompresses_the_blo_004f3aec[]; /* used by 1 fn(s), first 0x004cc370 */
extern char s_C__grimsrc_libs_lecsmush_insane__004f3bbc[]; /* used by 2 fn(s), first 0x004cc410 */
extern undefined *PTR_FUN_004f3bf8; /* used by 1 fn(s), first 0x004cdc90 */
extern undefined *PTR_FUN_004f3c08; /* used by 1 fn(s), first 0x004cdc90 */
extern undefined DAT_004f3c2c; /* used by 1 fn(s), first 0x004cdd80 */
extern char s_TIMER_insane_004f3c30[]; /* used by 2 fn(s), first 0x004cdc90 */
extern char s_LECMODULE_insane_timer_004f3c40[]; /* used by 2 fn(s), first 0x004cdc90 */
extern char s_Timer_Module__Cannot_allocate_me_004f3c58[]; /* used by 1 fn(s), first 0x004cdd10 */
extern undefined *PTR_FUN_004f3cc0; /* used by 1 fn(s), first 0x004ce2e0 */
extern undefined *PTR_FUN_004f3cd0; /* used by 1 fn(s), first 0x004ce2e0 */
extern char s_BITMAP_insane_004f3cdc[]; /* used by 2 fn(s), first 0x004ce2e0 */
extern char s_LECMODULE_insane_bitmap_004f3cec[]; /* used by 2 fn(s), first 0x004ce2e0 */
extern char s_Video_Module__Cannot_allocate_me_004f3d04[]; /* used by 1 fn(s), first 0x004ce350 */
extern char s_VIDEO_getbm_004f3d34[]; /* used by 1 fn(s), first 0x004ce350 */
extern char s__s__line__s__Type__d_not_support_004f3d40[]; /* used by 1 fn(s), first 0x004ce3e0 */
extern char s_C__grimsrc_libs_lecsmush_insane__004f3d64[]; /* used by 3 fn(s), first 0x004ce3e0 */
extern undefined DAT_004f3da0; /* used by 2 fn(s), first 0x004cf010 */
extern undefined *PTR_FUN_004f3dc8; /* used by 1 fn(s), first 0x004d0300 */
extern undefined *PTR_FUN_004f3dd8; /* used by 1 fn(s), first 0x004d0300 */
extern undefined DAT_004f3e18; /* used by 1 fn(s), first 0x004d16a0 */
extern uint UINT_004f3e30; /* used by 13 fn(s), first 0x004d0550 */
extern uint UINT_004f3e34; /* used by 6 fn(s), first 0x004d0550 */
extern uint UINT_004f3e38; /* used by 3 fn(s), first 0x004d0550 */
extern uint UINT_004f3e3c; /* used by 3 fn(s), first 0x004d0d70 */
extern uint UINT_004f3e40; /* used by 3 fn(s), first 0x004d0d70 */
extern undefined4 UINT_004f3e44; /* used by 1 fn(s), first 0x004d16a0 */
extern undefined4 UINT_004f3e48; /* used by 1 fn(s), first 0x004d16a0 */
extern char s_SOUND_insane_004f3e4c[]; /* used by 2 fn(s), first 0x004d0300 */
extern char s_LECMODULE_insane_sound_004f3e5c[]; /* used by 2 fn(s), first 0x004d0300 */
extern char s_Sound_Module__Cannot_allocate_sn_004f3e74[]; /* used by 1 fn(s), first 0x004d03d0 */
extern char s_Sound_Module__Cannot_allocate_ti_004f3ea8[]; /* used by 1 fn(s), first 0x004d03d0 */
extern char s_Sound_Module__Cannot_allocate_me_004f3ed8[]; /* used by 1 fn(s), first 0x004d03d0 */
extern char s_SNDDRIVER_driver_004f3f08[]; /* used by 1 fn(s), first 0x004d03d0 */
extern char s_TIMER_external_sync_004f3f1c[]; /* used by 1 fn(s), first 0x004d03d0 */
extern char s_C__grimsrc_libs_lecsmush_insane__004f3f30[]; /* used by 2 fn(s), first 0x004d0610 */
extern undefined *PTR_FUN_004f3f68; /* used by 1 fn(s), first 0x004d2420 */
extern undefined *PTR_FUN_004f3f78; /* used by 1 fn(s), first 0x004d2420 */
extern undefined4 UINT_004f3f94; /* used by 1 fn(s), first 0x004d27d0 */
extern uint UINT_004f3f98; /* used by 2 fn(s), first 0x004d2550 */
extern undefined4 UINT_004f3f9c; /* used by 1 fn(s), first 0x004d2630 */
extern undefined4 UINT_004f3fa0; /* used by 2 fn(s), first 0x004d2940 */
extern undefined DAT_004f3fa8; /* used by 1 fn(s), first 0x004d2940 */
extern undefined DAT_004f3fc0; /* used by 1 fn(s), first 0x004d2aa0 */
extern char s_SNDDRIVER_insane_dsnd_004f3fd4[]; /* used by 2 fn(s), first 0x004d2420 */
extern char s_LECMODULE_insane_dsnd_004f3fec[]; /* used by 2 fn(s), first 0x004d2420 */
extern char s_MEMORY_mixertable_004f4004[]; /* used by 1 fn(s), first 0x004d24b0 */
extern char s_DirectSoundDriver_Module__Cannot_004f4018[]; /* used by 1 fn(s), first 0x004d24b0 */
extern char s_TIMER_clock_004f4054[]; /* used by 1 fn(s), first 0x004d24b0 */
extern char s_DirectSound__Error__08X_while_cr_004f4060[]; /* used by 1 fn(s), first 0x004d2940 */
extern char s_DirectSound__Error__08X_while_se_004f4098[]; /* used by 1 fn(s), first 0x004d2940 */
extern char s_Cannot_create_DirectSound_object_004f40d0[]; /* used by 1 fn(s), first 0x004d2940 */
extern uint UINT_004f40f8; /* used by 2 fn(s), first 0x004d2d40 */
extern char s_C__grimsrc_libs_lecsmush_insane__004f4158[]; /* used by 2 fn(s), first 0x004d2e80 */
extern undefined DAT_004f41e0; /* used by 1 fn(s), first 0x004025b0 */
extern undefined4 UINT_004f44e0; /* used by 3 fn(s), first 0x00401040 */
extern undefined4 UINT_004f44e8; /* used by 2 fn(s), first 0x00401a50 */
extern undefined4 UINT_004f44ec; /* used by 1 fn(s), first 0x00401a50 */
extern undefined DAT_004f44f0; /* used by 1 fn(s), first 0x00401a50 */
extern undefined DAT_004f450c; /* used by 1 fn(s), first 0x00401a50 */
extern undefined4 UINT_004f4530; /* used by 1 fn(s), first 0x00402120 */
extern undefined DAT_004f4538; /* used by 1 fn(s), first 0x004023a0 */
extern undefined DAT_004f4938; /* used by 1 fn(s), first 0x004024f0 */
extern undefined4 UINT_004f4d38; /* used by 4 fn(s), first 0x00401a50 */
extern undefined DAT_004f4d40; /* used by 1 fn(s), first 0x00401a50 */
extern undefined DAT_004f4d44; /* used by 1 fn(s), first 0x00401a50 */
extern undefined4 UINT_004f4d54; /* used by 1 fn(s), first 0x00401a50 */
extern undefined DAT_004f4d90; /* used by 1 fn(s), first 0x00402120 */
extern undefined4 UINT_004f4d94; /* used by 1 fn(s), first 0x00402120 */
extern undefined4 UINT_004f4d98; /* used by 1 fn(s), first 0x00402120 */
extern undefined4 UINT_004f4d9c; /* used by 1 fn(s), first 0x00402120 */
extern undefined DAT_004f4db0; /* used by 1 fn(s), first 0x00402410 */
extern undefined DAT_004f51b0; /* used by 1 fn(s), first 0x00402480 */
extern undefined DAT_004f55b0; /* used by 1 fn(s), first 0x00402330 */
extern undefined DAT_004f59b0; /* used by 1 fn(s), first 0x00402c80 */
extern undefined DAT_004f59ff; /* used by 1 fn(s), first 0x00402c80 */
extern undefined DAT_004f5a00; /* used by 1 fn(s), first 0x004012b0 */
extern undefined4 UINT_004f5a04; /* used by 1 fn(s), first 0x00401040 */
extern undefined4 UINT_004f5a08; /* used by 6 fn(s), first 0x00401040 */
extern undefined4 UINT_004f5a10; /* used by 2 fn(s), first 0x004012b0 */
extern undefined4 UINT_004f5a14; /* used by 2 fn(s), first 0x004012b0 */
extern undefined4 UINT_004f5a18; /* used by 8 fn(s), first 0x00401040 */
extern undefined4 UINT_004f5a1c; /* used by 2 fn(s), first 0x00401040 */
extern undefined4 INT_004f5a24; /* used by 5 fn(s), first 0x00401040 */
extern undefined4 UINT_004f5a28; /* used by 2 fn(s), first 0x00402930 */
extern undefined4 UINT_004f5a34; /* used by 2 fn(s), first 0x00401900 */
extern undefined4 UINT_004f5a3c; /* used by 6 fn(s), first 0x004020a0 */
extern undefined4 UINT_004f5a40; /* used by 1 fn(s), first 0x004020a0 */
extern undefined4 UINT_004f5a44; /* used by 2 fn(s), first 0x004012b0 */
extern undefined4 UINT_004f5a50; /* used by 3 fn(s), first 0x004016a0 */
extern undefined4 UINT_004f5a54; /* used by 1 fn(s), first 0x00401040 */
extern undefined4 UINT_004f5a5c; /* used by 1 fn(s), first 0x004016a0 */
extern undefined DAT_004f5a60; /* used by 1 fn(s), first 0x004016a0 */
extern undefined4 UINT_004f5a64; /* used by 1 fn(s), first 0x004016a0 */
extern undefined4 UINT_004f5a68; /* used by 1 fn(s), first 0x004020a0 */
extern undefined4 UINT_004f5a6c; /* used by 1 fn(s), first 0x00402120 */
extern undefined4 UINT_004f5a70; /* used by 2 fn(s), first 0x00402120 */
extern undefined4 UINT_004f5a74; /* used by 1 fn(s), first 0x00402120 */
extern undefined4 UINT_004f5a78; /* used by 1 fn(s), first 0x00402120 */
extern undefined DAT_004f5a7c; /* used by 1 fn(s), first 0x00402120 */
extern undefined DAT_004f5a80; /* used by 1 fn(s), first 0x00402120 */
extern undefined4 UINT_004f5a84; /* used by 1 fn(s), first 0x004025b0 */
extern undefined4 UINT_004f5a90; /* used by 1 fn(s), first 0x00402fd0 */
extern undefined4 UINT_004f5a94; /* used by 1 fn(s), first 0x00402fd0 */
extern undefined DAT_004f5a98; /* used by 25 fn(s), first 0x004034b0 */
extern undefined DAT_004f5aa0; /* used by 5 fn(s), first 0x004035b0 */
extern undefined DAT_004f5ea8; /* used by 2 fn(s), first 0x004038a0 */
extern uint UINT_004f5eac; /* used by 11 fn(s), first 0x004038a0 */
extern undefined4 UINT_004f5eb4; /* used by 3 fn(s), first 0x004041e0 */
extern undefined4 UINT_004f5eb8; /* used by 2 fn(s), first 0x00404180 */
extern undefined4 UINT_004f5ebc; /* used by 2 fn(s), first 0x004041e0 */
extern uint UINT_004f5ec0; /* used by 5 fn(s), first 0x00404350 */
extern undefined4 UINT_004f5ec4; /* used by 36 fn(s), first 0x00404350 */
extern undefined DAT_004f5ec8; /* used by 3 fn(s), first 0x00404c00 */
extern undefined4 UINT_004f6ec8; /* used by 3 fn(s), first 0x00404c00 */
extern undefined DAT_004f6ed0; /* used by 1 fn(s), first 0x00404c00 */
extern undefined DAT_004f6ef8; /* used by 1 fn(s), first 0x00404c00 */
extern undefined DAT_004f6f1c; /* used by 1 fn(s), first 0x00404c00 */
extern uint UINT_004f6f20; /* used by 3 fn(s), first 0x00404c00 */
extern undefined4 UINT_004f6f28; /* used by 3 fn(s), first 0x00404c00 */
extern undefined4 UINT_004f6f2c; /* used by 3 fn(s), first 0x00404c00 */
extern undefined DAT_004f6f30; /* used by 1 fn(s), first 0x00404e00 */
extern undefined DAT_004f6f34; /* used by 1 fn(s), first 0x00404e00 */
extern undefined DAT_004f6f38; /* used by 1 fn(s), first 0x00404e00 */
extern undefined DAT_004f6f3c; /* used by 1 fn(s), first 0x00404e00 */
extern undefined DAT_004f6f40; /* used by 1 fn(s), first 0x00404e00 */
extern undefined DAT_004f6f44; /* used by 1 fn(s), first 0x00404e00 */
extern undefined DAT_004f6f48; /* used by 1 fn(s), first 0x00404e00 */
extern undefined DAT_004f6f4c; /* used by 1 fn(s), first 0x00404e00 */
extern undefined DAT_004f6f50; /* used by 1 fn(s), first 0x00404e00 */
extern undefined DAT_004f6f54; /* used by 1 fn(s), first 0x00404e00 */
extern undefined DAT_004f6f58; /* used by 1 fn(s), first 0x00404e00 */
extern undefined4 UINT_0050cf30; /* used by 2 fn(s), first 0x00404cb0 */
extern undefined DAT_0050cf38; /* used by 3 fn(s), first 0x00404c00 */
extern undefined DAT_0050df38; /* used by 1 fn(s), first 0x00405620 */
extern undefined4 UINT_00565f38; /* used by 2 fn(s), first 0x00405620 */
extern undefined4 UINT_005660f0; /* used by 2 fn(s), first 0x004055d0 */
extern undefined4 UINT_005660f4; /* used by 1 fn(s), first 0x00405770 */
extern undefined DAT_00566124; /* used by 1 fn(s), first 0x00405770 */
extern undefined DAT_00566128; /* used by 1 fn(s), first 0x00405770 */
extern undefined DAT_00566130; /* used by 1 fn(s), first 0x00405770 */
extern undefined4 UINT_005e6f38; /* used by 3 fn(s), first 0x00404c00 */
extern undefined4 UINT_005e6f3c; /* used by 4 fn(s), first 0x00404c00 */
extern undefined DAT_005e6f40; /* used by 3 fn(s), first 0x00404c00 */
extern undefined DAT_005e6f68; /* used by 1 fn(s), first 0x00404c00 */
extern undefined DAT_005e6f8c; /* used by 1 fn(s), first 0x00404c00 */
extern undefined DAT_005e6f90; /* used by 1 fn(s), first 0x00404c00 */
extern undefined4 UINT_005e6f98; /* used by 2 fn(s), first 0x00404ca0 */
extern undefined DAT_005e6fa0; /* used by 1 fn(s), first 0x004066a0 */
extern undefined DAT_00606fa0; /* used by 2 fn(s), first 0x00406aa0 */
extern undefined DAT_00606fa4; /* used by 1 fn(s), first 0x00406aa0 */
extern undefined DAT_00606fa8; /* used by 1 fn(s), first 0x00406aa0 */
extern undefined DAT_00606fac; /* used by 1 fn(s), first 0x00406aa0 */
extern undefined DAT_00606fb0; /* used by 1 fn(s), first 0x00406aa0 */
extern undefined4 UINT_0060bfa0; /* used by 3 fn(s), first 0x00406aa0 */
extern undefined DAT_0060bfa8; /* used by 1 fn(s), first 0x004066a0 */
extern undefined DAT_0062bfa8; /* used by 1 fn(s), first 0x004066a0 */
extern undefined4 UINT_0068bfa8; /* used by 3 fn(s), first 0x00406aa0 */
extern undefined DAT_0068bfb0; /* used by 1 fn(s), first 0x004066a0 */
extern undefined DAT_006cbfb0; /* used by 2 fn(s), first 0x00406aa0 */
extern undefined DAT_006cbfb4; /* used by 1 fn(s), first 0x00406aa0 */
extern undefined DAT_006cbfb8; /* used by 1 fn(s), first 0x00406aa0 */
extern undefined DAT_006cbfbc; /* used by 1 fn(s), first 0x00406aa0 */
extern undefined DAT_006cbfc0; /* used by 1 fn(s), first 0x00406aa0 */
extern undefined DAT_006d0fb0; /* used by 1 fn(s), first 0x004066a0 */
extern undefined4 UINT_006f0fb0; /* used by 3 fn(s), first 0x00406aa0 */
extern undefined DAT_006f0fb8; /* used by 2 fn(s), first 0x00406aa0 */
extern undefined DAT_006f0fbc; /* used by 1 fn(s), first 0x00406aa0 */
extern undefined DAT_006f0fc0; /* used by 1 fn(s), first 0x00406aa0 */
extern undefined DAT_006f0fc4; /* used by 1 fn(s), first 0x00406aa0 */
extern undefined DAT_006f0fc8; /* used by 1 fn(s), first 0x00406aa0 */
extern undefined DAT_006f0fcc; /* used by 1 fn(s), first 0x00406aa0 */
extern undefined DAT_006f0fd0; /* used by 1 fn(s), first 0x00406aa0 */
extern undefined DAT_006f0fd4; /* used by 1 fn(s), first 0x00406aa0 */
extern undefined DAT_007f0fb8; /* used by 2 fn(s), first 0x00406690 */
extern undefined4 UINT_007f0fbc; /* used by 3 fn(s), first 0x00406670 */
extern undefined4 UINT_007f0fc0; /* used by 3 fn(s), first 0x00406670 */
extern undefined4 UINT_007f0fc4; /* used by 3 fn(s), first 0x00406670 */
extern undefined4 UINT_007f0fd0; /* used by 2 fn(s), first 0x0040cf20 */
extern undefined DAT_007f0fd8; /* used by 1 fn(s), first 0x0040d230 */
extern undefined DAT_007f0fdc; /* used by 1 fn(s), first 0x0040d230 */
extern undefined DAT_007f0fe0; /* used by 1 fn(s), first 0x0040d230 */
extern undefined DAT_007f0fe8; /* used by 1 fn(s), first 0x0040d230 */
extern undefined DAT_007f1168; /* used by 1 fn(s), first 0x0040d230 */
extern undefined4 UINT_007f1468; /* used by 1 fn(s), first 0x0040d880 */
extern undefined4 UINT_007f1474; /* used by 2 fn(s), first 0x0040d230 */
extern undefined4 UINT_007f1478; /* used by 1 fn(s), first 0x0040d880 */
extern undefined4 UINT_007f147c; /* used by 1 fn(s), first 0x0040d880 */
extern undefined4 UINT_007f1490; /* used by 1 fn(s), first 0x0040d880 */
extern undefined4 UINT_007f1494; /* used by 2 fn(s), first 0x0040cf20 */
extern undefined4 UINT_007f1498; /* used by 2 fn(s), first 0x0040cf20 */
extern undefined DAT_007f1598; /* used by 1 fn(s), first 0x0040d230 */
extern undefined4 UINT_007f1898; /* used by 2 fn(s), first 0x0040d230 */
extern undefined4 UINT_007f189c; /* used by 2 fn(s), first 0x0040cf20 */
extern undefined DAT_007f18a0; /* used by 1 fn(s), first 0x0040d230 */
extern void * PTR_007f30a0; /* used by 2 fn(s), first 0x0040d230 */
extern undefined4 UINT_007f30a4; /* used by 2 fn(s), first 0x0040cf20 */
extern undefined DAT_007f30a8; /* used by 1 fn(s), first 0x0040d880 */
extern undefined DAT_007f30ac; /* used by 1 fn(s), first 0x0040d880 */
extern undefined DAT_007f30b0; /* used by 1 fn(s), first 0x0040d880 */
extern undefined DAT_007f30b4; /* used by 1 fn(s), first 0x0040d230 */
extern undefined DAT_007f30b8; /* used by 1 fn(s), first 0x0040d230 */
extern undefined DAT_007f30bc; /* used by 1 fn(s), first 0x0040d230 */
extern undefined DAT_007f30c0; /* used by 1 fn(s), first 0x0040d230 */
extern undefined4 UINT_007f30d8; /* used by 2 fn(s), first 0x0040d230 */
extern undefined4 UINT_007f30dc; /* used by 2 fn(s), first 0x0040cf20 */
extern undefined4 UINT_007f30e0; /* used by 2 fn(s), first 0x0040d230 */
extern undefined4 UINT_007f31e4; /* used by 2 fn(s), first 0x0040d230 */
extern undefined4 UINT_007f31e8; /* used by 2 fn(s), first 0x0040d230 */
extern undefined4 UINT_007f31ec; /* used by 2 fn(s), first 0x0040a860 */
extern undefined4 UINT_007f31f0; /* used by 1 fn(s), first 0x0040a8f0 */
extern undefined4 UINT_007f31f4; /* used by 1 fn(s), first 0x0040c0d0 */
extern undefined4 UINT_007f31f8; /* used by 2 fn(s), first 0x0040cf20 */
extern undefined4 UINT_007f31fc; /* used by 2 fn(s), first 0x0040d230 */
extern undefined DAT_007f3200; /* used by 2 fn(s), first 0x0040c8c0 */
extern uint UINT_007f3204; /* used by 3 fn(s), first 0x0040a870 */
extern undefined DAT_007f3208; /* used by 1 fn(s), first 0x0040d880 */
extern undefined DAT_007f320c; /* used by 2 fn(s), first 0x0040a880 */
extern undefined DAT_007f3210; /* used by 2 fn(s), first 0x0040a880 */
extern undefined4 UINT_007f3214; /* used by 6 fn(s), first 0x00410970 */
extern uint UINT_007f4238; /* used by 2 fn(s), first 0x00417e90 */
extern uint UINT_007f423c; /* used by 2 fn(s), first 0x00417ea0 */
extern undefined DAT_007f4240; /* used by 1 fn(s), first 0x00428f00 */
extern undefined4 UINT_007f4244; /* used by 1 fn(s), first 0x00428f00 */
extern undefined DAT_007f4248; /* used by 1 fn(s), first 0x00428f00 */
extern undefined4 UINT_007f4250; /* used by 26 fn(s), first 0x00418550 */
extern undefined4 UINT_007f4254; /* used by 24 fn(s), first 0x0041b6f0 */
extern undefined DAT_007f4258; /* used by 1 fn(s), first 0x00428f00 */
extern undefined4 UINT_007f4260; /* used by 4 fn(s), first 0x00418a00 */
extern undefined DAT_007f42e0; /* used by 1 fn(s), first 0x00428f00 */
extern undefined DAT_007f42e4; /* used by 1 fn(s), first 0x00428f00 */
extern undefined DAT_007f42f0; /* used by 1 fn(s), first 0x00428f00 */
extern undefined DAT_007f42f4; /* used by 1 fn(s), first 0x00428f00 */
extern undefined4 UINT_007f42f8; /* used by 6 fn(s), first 0x0041b310 */
extern byte * PTR_007f4300; /* used by 26 fn(s), first 0x00419be0 */
extern undefined4 UINT_007f4304; /* used by 16 fn(s), first 0x0041a640 */
extern undefined4 UINT_007f4310; /* used by 4 fn(s), first 0x00418a00 */
extern undefined4 UINT_007f4390; /* used by 1 fn(s), first 0x00428f00 */
extern undefined4 UINT_007f4398; /* used by 32 fn(s), first 0x00418550 */
extern undefined4 UINT_007f439c; /* used by 9 fn(s), first 0x0041f2f0 */
extern undefined DAT_007f43a0; /* used by 1 fn(s), first 0x00428f00 */
extern undefined DAT_007f43a4; /* used by 1 fn(s), first 0x00428f00 */
extern int * PTR_007f43a8; /* used by 30 fn(s), first 0x004195f0 */
extern undefined4 UINT_007f43ac; /* used by 1 fn(s), first 0x00428f00 */
extern undefined4 UINT_007f43b0; /* used by 1 fn(s), first 0x00428f00 */
extern undefined4 UINT_007f43b4; /* used by 1 fn(s), first 0x00428f00 */
extern undefined4 UINT_007f43b8; /* used by 1 fn(s), first 0x00428f00 */
extern undefined4 UINT_007f43bc; /* used by 24 fn(s), first 0x0041b6f0 */
extern undefined DAT_007f43c0; /* used by 1 fn(s), first 0x00428f00 */
extern undefined DAT_007f43c4; /* used by 1 fn(s), first 0x00428f00 */
extern undefined4 UINT_007f43c8; /* used by 4 fn(s), first 0x00418a00 */
extern undefined DAT_007f4448; /* used by 1 fn(s), first 0x00428f00 */
extern undefined DAT_007f444c; /* used by 1 fn(s), first 0x00428f00 */
extern undefined4 UINT_007f4450; /* used by 9 fn(s), first 0x0041f2f0 */
extern undefined4 UINT_007f4454; /* used by 24 fn(s), first 0x0041b6f0 */
extern undefined4 UINT_007f4458; /* used by 24 fn(s), first 0x0041b6f0 */
extern undefined4 UINT_007f4460; /* used by 52 fn(s), first 0x0042d190 */
extern undefined4 UINT_007f4464; /* used by 26 fn(s), first 0x0042d190 */
extern undefined4 UINT_007f4468; /* used by 4 fn(s), first 0x0042d5f0 */
extern undefined4 UINT_007f44e8; /* used by 32 fn(s), first 0x0042d190 */
extern undefined4 UINT_007f44ec; /* used by 39 fn(s), first 0x0042e010 */
extern undefined4 UINT_007f44f0; /* used by 6 fn(s), first 0x00430a20 */
extern undefined4 UINT_007f44f4; /* used by 50 fn(s), first 0x0042d190 */
extern undefined4 UINT_007f44f8; /* used by 16 fn(s), first 0x0042fa10 */
extern int * PTR_007f44fc; /* used by 52 fn(s), first 0x0042d190 */
extern undefined4 UINT_007f4500; /* used by 4 fn(s), first 0x0042d5f0 */
extern undefined4 UINT_007f4580; /* used by 39 fn(s), first 0x0042e010 */
extern undefined4 UINT_007f4584; /* used by 32 fn(s), first 0x0042d190 */
extern undefined4 UINT_007f4588; /* used by 23 fn(s), first 0x0042d190 */
extern undefined4 UINT_007f4618; /* used by 4 fn(s), first 0x00449aa0 */
extern undefined4 UINT_007f461c; /* used by 4 fn(s), first 0x0044b0a0 */
extern undefined4 UINT_007f46a8; /* used by 4 fn(s), first 0x0044b0a0 */
extern uint UINT_007f46ac; /* used by 10 fn(s), first 0x004478c0 */
extern undefined4 UINT_007f46b0; /* used by 4 fn(s), first 0x00449aa0 */
extern undefined4 UINT_007f46b8; /* used by 5 fn(s), first 0x0044b0a0 */
extern undefined4 UINT_007f46bc; /* used by 1 fn(s), first 0x0044ea50 */
extern uint UINT_007f47b8; /* used by 10 fn(s), first 0x004478c0 */
extern undefined4 UINT_007f47c0; /* used by 5 fn(s), first 0x00449aa0 */
extern undefined4 UINT_007f48c0; /* used by 11 fn(s), first 0x004478c0 */
extern undefined4 UINT_007f48c4; /* used by 1 fn(s), first 0x0044ea50 */
extern undefined4 UINT_007f48c8; /* used by 1 fn(s), first 0x0044ea50 */
extern undefined4 UINT_007f4ac4; /* used by 10 fn(s), first 0x004478c0 */
extern undefined DAT_007f4ac8; /* used by 21 fn(s), first 0x00453e30 */
extern undefined4 UINT_007f4acc; /* used by 21 fn(s), first 0x00453e30 */
extern undefined4 UINT_007f4ad0; /* used by 2 fn(s), first 0x00451fa0 */
extern undefined DAT_007f4ad4; /* used by 21 fn(s), first 0x00453e30 */
extern undefined4 UINT_007f4adc; /* used by 42 fn(s), first 0x00452150 */
extern undefined DAT_007f4ae4; /* used by 21 fn(s), first 0x00453e30 */
extern undefined DAT_007f4aec; /* used by 21 fn(s), first 0x00453e30 */
extern undefined DAT_007f4af0; /* used by 21 fn(s), first 0x00453e30 */
extern undefined DAT_007f4af4; /* used by 21 fn(s), first 0x00453e30 */
extern undefined DAT_007f4af8; /* used by 21 fn(s), first 0x00453e30 */
extern undefined4 UINT_007f4b28; /* used by 2 fn(s), first 0x00451fa0 */
extern undefined4 UINT_007f4b2c; /* used by 21 fn(s), first 0x00453e30 */
extern undefined4 UINT_007f4b30; /* used by 14 fn(s), first 0x00453310 */
extern undefined DAT_007f4b34; /* used by 21 fn(s), first 0x00453e30 */
extern undefined DAT_007f4b38; /* used by 21 fn(s), first 0x00453e30 */
extern uint UINT_007f4b3c; /* used by 42 fn(s), first 0x00452150 */
extern undefined4 UINT_007f4b40; /* used by 1 fn(s), first 0x00452070 */
extern undefined4 UINT_007f4b44; /* used by 21 fn(s), first 0x00453e30 */
extern undefined4 UINT_007f4b48; /* used by 21 fn(s), first 0x00453e30 */
extern undefined4 UINT_007f4b4c; /* used by 21 fn(s), first 0x00453e30 */
extern undefined4 UINT_007f4b50; /* used by 21 fn(s), first 0x00453e30 */
extern undefined4 UINT_007f4b54; /* used by 42 fn(s), first 0x00452150 */
extern undefined DAT_007f4b58; /* used by 21 fn(s), first 0x00453e30 */
extern undefined DAT_007f4b5c; /* used by 21 fn(s), first 0x00453e30 */
extern undefined DAT_007f4b60; /* used by 21 fn(s), first 0x00453e30 */
extern undefined DAT_007f4b64; /* used by 21 fn(s), first 0x00453e30 */
extern uint UINT_007f4b68; /* used by 14 fn(s), first 0x00453310 */
extern uint UINT_007f4b6c; /* used by 42 fn(s), first 0x00452150 */
extern uint UINT_007f4b70; /* used by 42 fn(s), first 0x00452150 */
extern undefined4 UINT_007f4b74; /* used by 2 fn(s), first 0x00451fa0 */
extern undefined4 UINT_007f4c44; /* used by 44 fn(s), first 0x0045ff10 */
extern undefined4 UINT_007f4c54; /* used by 44 fn(s), first 0x0045ff10 */
extern undefined4 UINT_007f4ca4; /* used by 44 fn(s), first 0x0045ff10 */
extern undefined4 UINT_007f4cac; /* used by 44 fn(s), first 0x0045ff10 */
extern undefined4 UINT_007f4cb0; /* used by 44 fn(s), first 0x0045ff10 */
extern undefined4 UINT_007f4cb4; /* used by 15 fn(s), first 0x0045ff10 */
extern undefined4 UINT_007f4cc4; /* used by 44 fn(s), first 0x0045ff10 */
extern undefined4 UINT_007f4cdc; /* used by 44 fn(s), first 0x0045ff10 */
extern undefined4 UINT_007f4cf0; /* used by 15 fn(s), first 0x0045ff10 */
extern undefined4 UINT_007f4cf4; /* used by 44 fn(s), first 0x0045ff10 */
extern undefined4 UINT_007f4cf8; /* used by 44 fn(s), first 0x0045ff10 */
extern undefined4 UINT_007f4cfc; /* used by 44 fn(s), first 0x0045ff10 */
extern undefined DAT_007f4d00; /* used by 1 fn(s), first 0x00472360 */
extern undefined DAT_007f4e80; /* used by 1 fn(s), first 0x00471ee0 */
extern undefined DAT_007f4e84; /* used by 1 fn(s), first 0x00471ee0 */
extern undefined DAT_007f4e88; /* used by 1 fn(s), first 0x00471ee0 */
extern undefined DAT_007f4e8c; /* used by 1 fn(s), first 0x00471ee0 */
extern undefined DAT_007f4e90; /* used by 1 fn(s), first 0x00471ee0 */
extern undefined DAT_007f4e94; /* used by 1 fn(s), first 0x00471ee0 */
extern undefined DAT_007f4e98; /* used by 1 fn(s), first 0x00471ee0 */
extern undefined DAT_007f4e9c; /* used by 1 fn(s), first 0x00471ee0 */
extern undefined DAT_007f4ea0; /* used by 1 fn(s), first 0x00471ee0 */
extern undefined DAT_007f4ea4; /* used by 1 fn(s), first 0x00471ee0 */
extern undefined DAT_007f4ea8; /* used by 1 fn(s), first 0x00471ee0 */
extern undefined DAT_007f4eac; /* used by 1 fn(s), first 0x00471ee0 */
extern undefined DAT_007f5000; /* used by 1 fn(s), first 0x00472640 */
extern undefined DAT_007f5004; /* used by 1 fn(s), first 0x00472640 */
extern undefined DAT_007f5008; /* used by 1 fn(s), first 0x00472640 */
extern undefined DAT_007f500c; /* used by 1 fn(s), first 0x00472640 */
extern undefined DAT_007f5010; /* used by 1 fn(s), first 0x00472640 */
extern undefined DAT_007f5014; /* used by 1 fn(s), first 0x00472640 */
extern undefined DAT_007f5018; /* used by 1 fn(s), first 0x00472640 */
extern undefined DAT_007f501c; /* used by 1 fn(s), first 0x00472640 */
extern undefined DAT_007f5020; /* used by 1 fn(s), first 0x00472640 */
extern undefined DAT_007f5024; /* used by 1 fn(s), first 0x00472640 */
extern undefined DAT_007f5028; /* used by 1 fn(s), first 0x00472640 */
extern undefined DAT_007f502c; /* used by 1 fn(s), first 0x00472640 */
extern undefined4 UINT_007f5180; /* used by 1 fn(s), first 0x00472640 */
extern undefined4 UINT_007f5184; /* used by 1 fn(s), first 0x00472640 */
extern undefined DAT_007f5d88; /* used by 1 fn(s), first 0x00472bd0 */
extern undefined DAT_007f5f08; /* used by 1 fn(s), first 0x00472bd0 */
extern undefined DAT_007f5f0c; /* used by 1 fn(s), first 0x00472bd0 */
extern undefined DAT_007f5f10; /* used by 1 fn(s), first 0x00472bd0 */
extern undefined DAT_007f5f14; /* used by 1 fn(s), first 0x00472bd0 */
extern undefined DAT_007f5f18; /* used by 1 fn(s), first 0x00472bd0 */
extern undefined DAT_007f5f1c; /* used by 1 fn(s), first 0x00472bd0 */
extern undefined DAT_007f5f20; /* used by 1 fn(s), first 0x00472bd0 */
extern undefined DAT_007f5f24; /* used by 1 fn(s), first 0x00472bd0 */
extern undefined DAT_007f5f28; /* used by 1 fn(s), first 0x00472bd0 */
extern undefined DAT_007f5f2c; /* used by 1 fn(s), first 0x00472bd0 */
extern undefined DAT_007f5f30; /* used by 1 fn(s), first 0x00472bd0 */
extern undefined DAT_007f5f34; /* used by 1 fn(s), first 0x00472bd0 */
extern uint UINT_007f608c; /* used by 1 fn(s), first 0x00473380 */
extern undefined DAT_007f6090; /* used by 1 fn(s), first 0x00473570 */
extern undefined DAT_007f6490; /* used by 2 fn(s), first 0x004733a0 */
extern undefined4 UINT_007f6498; /* used by 5 fn(s), first 0x00474420 */
extern undefined DAT_007f64a0; /* used by 1 fn(s), first 0x00474d90 */
extern undefined4 UINT_007fa7ac; /* used by 2 fn(s), first 0x00473a00 */
extern undefined DAT_007fa7b8; /* used by 1 fn(s), first 0x00474d90 */
extern undefined DAT_007feac8; /* used by 1 fn(s), first 0x00474140 */
extern undefined DAT_007feacc; /* used by 1 fn(s), first 0x00474140 */
extern undefined DAT_007fead0; /* used by 1 fn(s), first 0x00474140 */
extern undefined DAT_007fead4; /* used by 1 fn(s), first 0x00474140 */
extern int * PTR_007fead8; /* used by 2 fn(s), first 0x00473a00 */
extern undefined4 UINT_007feae0; /* used by 1 fn(s), first 0x00474140 */
extern undefined4 UINT_007feae4; /* used by 2 fn(s), first 0x00473a00 */
extern undefined DAT_007feb54; /* used by 1 fn(s), first 0x00473a00 */
extern undefined DAT_007feb58; /* used by 2 fn(s), first 0x00473a00 */
extern uint UINT_00803f7c; /* used by 4 fn(s), first 0x00474420 */
extern undefined DAT_00803f80; /* used by 2 fn(s), first 0x00473a40 */
extern int UINT_00803f9c; /* used by 5 fn(s), first 0x00474140 */
extern undefined4 UINT_00803fa0; /* used by 3 fn(s), first 0x00474140 */
extern undefined4 UINT_00803fb0; /* used by 2 fn(s), first 0x004743d0 */
extern undefined4 UINT_00803fb4; /* used by 2 fn(s), first 0x00476e40 */
extern undefined4 UINT_00803fb8; /* used by 1 fn(s), first 0x00474d90 */
extern undefined4 UINT_00803fc0; /* used by 1 fn(s), first 0x00474dd0 */
extern undefined4 UINT_00803fc8; /* used by 3 fn(s), first 0x00477040 */
extern undefined DAT_00803fcc; /* used by 1 fn(s), first 0x00477040 */
extern undefined4 UINT_00803fd0; /* used by 3 fn(s), first 0x00476f10 */
extern undefined4 UINT_00803fd4; /* used by 1 fn(s), first 0x004778f0 */
extern undefined DAT_00804000; /* used by 1 fn(s), first 0x00477c20 */
extern undefined DAT_00804004; /* used by 1 fn(s), first 0x00477c20 */
extern undefined DAT_00804008; /* used by 1 fn(s), first 0x00477c20 */
extern undefined4 UINT_00804010; /* used by 3 fn(s), first 0x00477040 */
extern undefined DAT_00804014; /* used by 1 fn(s), first 0x00477040 */
extern undefined4 UINT_00804018; /* used by 2 fn(s), first 0x00477230 */
extern undefined4 UINT_00804020; /* used by 3 fn(s), first 0x00477730 */
extern undefined4 UINT_00804024; /* used by 1 fn(s), first 0x00477730 */
extern undefined4 UINT_00804028; /* used by 1 fn(s), first 0x00477730 */
extern undefined4 UINT_0080402c; /* used by 2 fn(s), first 0x00477230 */
extern undefined4 UINT_00804030; /* used by 2 fn(s), first 0x00477230 */
extern undefined4 UINT_00805c20; /* used by 2 fn(s), first 0x00477730 */
extern undefined4 UINT_00805f30; /* used by 2 fn(s), first 0x00477c20 */
extern undefined4 UINT_00805f98; /* used by 3 fn(s), first 0x00476f10 */
extern undefined4 UINT_00805fa0; /* used by 4 fn(s), first 0x00477230 */
extern undefined4 UINT_00805fa4; /* used by 3 fn(s), first 0x004770d0 */
extern undefined4 UINT_00805fb8; /* used by 3 fn(s), first 0x00477040 */
extern undefined4 UINT_00805fbc; /* used by 7 fn(s), first 0x00477010 */
extern undefined4 UINT_00805fc0; /* used by 1 fn(s), first 0x004770d0 */
extern uint UINT_00805fc8; /* used by 2 fn(s), first 0x004770d0 */
extern undefined4 UINT_00805fcc; /* used by 1 fn(s), first 0x00477c20 */
extern undefined4 UINT_00805fd0; /* used by 1 fn(s), first 0x00477c20 */
extern undefined4 UINT_00805fd4; /* used by 1 fn(s), first 0x00477f10 */
extern undefined DAT_00805fd8; /* used by 2 fn(s), first 0x00478fc0 */
extern undefined4 UINT_008061d8; /* used by 1 fn(s), first 0x00478c00 */
extern undefined4 UINT_008061dc; /* used by 1 fn(s), first 0x00478c00 */
extern undefined4 UINT_008061e0; /* used by 1 fn(s), first 0x00478c00 */
extern undefined DAT_008061e8; /* used by 2 fn(s), first 0x00478fc0 */
extern undefined4 UINT_008063e8; /* used by 1 fn(s), first 0x00478c00 */
extern undefined4 UINT_008063ec; /* used by 1 fn(s), first 0x00478770 */
extern undefined DAT_008063f0; /* used by 2 fn(s), first 0x004782e0 */
extern undefined DAT_008063f4; /* used by 1 fn(s), first 0x004782e0 */
extern undefined DAT_008063f8; /* used by 1 fn(s), first 0x004782e0 */
extern undefined DAT_008063fc; /* used by 1 fn(s), first 0x004782e0 */
extern undefined4 UINT_00806400; /* used by 2 fn(s), first 0x004782e0 */
extern undefined4 UINT_00806408; /* used by 2 fn(s), first 0x00478fc0 */
extern int * PTR_0080660c; /* used by 4 fn(s), first 0x00478660 */
extern undefined4 UINT_00806610; /* used by 1 fn(s), first 0x00478c00 */
extern int * PTR_00806614; /* used by 1 fn(s), first 0x00478660 */
extern undefined DAT_00806618; /* used by 1 fn(s), first 0x00478fc0 */
extern int * PTR_00806918; /* used by 6 fn(s), first 0x00478770 */
extern undefined4 UINT_0080691c; /* used by 1 fn(s), first 0x00478840 */
extern uint UINT_00806924; /* used by 2 fn(s), first 0x00478c00 */
extern undefined4 UINT_00806930; /* used by 2 fn(s), first 0x004782e0 */
extern undefined4 UINT_00806934; /* used by 3 fn(s), first 0x004782e0 */
extern undefined4 UINT_00806938; /* used by 3 fn(s), first 0x004782e0 */
extern undefined4 UINT_0080693c; /* used by 3 fn(s), first 0x004782e0 */
extern undefined4 UINT_00806940; /* used by 3 fn(s), first 0x00406aa0 */
extern undefined4 UINT_00806944; /* used by 4 fn(s), first 0x004782e0 */
extern void * PTR_0080694c; /* used by 4 fn(s), first 0x004782e0 */
extern undefined4 UINT_00806950; /* used by 2 fn(s), first 0x004782e0 */
extern undefined DAT_00806958; /* used by 1 fn(s), first 0x004782e0 */
extern undefined4 UINT_0080695c; /* used by 3 fn(s), first 0x00478770 */
extern undefined4 UINT_00806960; /* used by 2 fn(s), first 0x00478770 */
extern int * PTR_00806964; /* used by 1 fn(s), first 0x0047a240 */
extern int * PTR_00806968; /* used by 5 fn(s), first 0x00478230 */
extern undefined4 UINT_0080696c; /* used by 2 fn(s), first 0x00478230 */
extern undefined4 UINT_00806970; /* used by 2 fn(s), first 0x004782e0 */
extern undefined4 UINT_00806974; /* used by 2 fn(s), first 0x00478730 */
extern undefined4 UINT_00806c80; /* used by 1 fn(s), first 0x0047b8a0 */
extern undefined DAT_00806c88; /* used by 2 fn(s), first 0x0047ca00 */
extern undefined DAT_00807688; /* used by 2 fn(s), first 0x0047ca00 */
extern undefined DAT_008076d8; /* used by 2 fn(s), first 0x0047ca00 */
extern undefined DAT_00807728; /* used by 2 fn(s), first 0x0047ca00 */
extern undefined DAT_0080c778; /* used by 2 fn(s), first 0x0047ca00 */
extern undefined4 UINT_0080cbc8; /* used by 4 fn(s), first 0x0047c7e0 */
extern undefined4 UINT_0080cbcc; /* used by 2 fn(s), first 0x0047c7e0 */
extern undefined4 UINT_0080cbd0; /* used by 5 fn(s), first 0x0047c7e0 */
extern uint UINT_0080cbd8; /* used by 3 fn(s), first 0x0047c8c0 */
extern undefined2 DAT_0080cbe0; /* used by 1 fn(s), first 0x0047e470 */
extern undefined4 UINT_0080cbe4; /* used by 4 fn(s), first 0x0047e3c0 */
extern undefined2 DAT_0080cbe8; /* used by 2 fn(s), first 0x0047e3c0 */
extern undefined2 DAT_0080cbec; /* used by 7 fn(s), first 0x0047e3c0 */
extern undefined2 DAT_0080cbf0; /* used by 2 fn(s), first 0x0047e7f0 */
extern undefined DAT_0080cbf8; /* used by 3 fn(s), first 0x0047e770 */
extern undefined4 UINT_0080ccf8; /* used by 3 fn(s), first 0x0047e7f0 */
extern undefined2 DAT_00811b24; /* used by 2 fn(s), first 0x0047ea30 */
extern undefined2 DAT_00811b28; /* used by 2 fn(s), first 0x0047e3c0 */
extern undefined2 DAT_00811b2c; /* used by 2 fn(s), first 0x0047e7f0 */
extern undefined DAT_00811b30; /* used by 2 fn(s), first 0x0047e3c0 */
extern undefined2 DAT_00812ebc; /* used by 1 fn(s), first 0x0047ebe0 */
extern int * PTR_00812ec0; /* used by 2 fn(s), first 0x0047e3c0 */
extern undefined DAT_00812ec4; /* used by 2 fn(s), first 0x0047e600 */
extern undefined DAT_00812ec8; /* used by 1 fn(s), first 0x0047e470 */
extern undefined4 UINT_00812ecc; /* used by 6 fn(s), first 0x0047e3c0 */
extern undefined2 DAT_00812ed0; /* used by 5 fn(s), first 0x0047e3c0 */
extern undefined4 UINT_00812ed8; /* used by 1 fn(s), first 0x0047ea30 */
extern undefined2 DAT_008155f0; /* used by 2 fn(s), first 0x0047e3c0 */
extern undefined2 DAT_008155f4; /* used by 4 fn(s), first 0x0047e3c0 */
extern undefined2 DAT_008155f8; /* used by 1 fn(s), first 0x0047ebe0 */
extern undefined DAT_00815600; /* used by 1 fn(s), first 0x0047e600 */
extern undefined DAT_00815608; /* used by 1 fn(s), first 0x0047ea30 */
extern uint UINT_0081560c; /* used by 1 fn(s), first 0x0047ea30 */
extern char DAT_00815610; /* used by 2 fn(s), first 0x0047f9d0 */
extern undefined4 UINT_00815614; /* used by 2 fn(s), first 0x0047f9d0 */
extern undefined4 UINT_00815618; /* used by 1 fn(s), first 0x0047fa70 */
extern char * PTR_0081561c; /* used by 2 fn(s), first 0x0047f9d0 */
extern undefined2 DAT_00815620; /* used by 2 fn(s), first 0x0047f9d0 */
extern undefined2 DAT_00815624; /* used by 1 fn(s), first 0x0047fa70 */
extern undefined DAT_00824f14; /* used by 8 fn(s), first 0x00480a00 */
extern undefined DAT_00824f18; /* used by 4 fn(s), first 0x00480a70 */
extern undefined DAT_00824f1c; /* used by 3 fn(s), first 0x00480a70 */
extern undefined DAT_00824f20; /* used by 3 fn(s), first 0x00480a70 */
extern undefined DAT_00824f24; /* used by 3 fn(s), first 0x00480a70 */
extern undefined DAT_00824f2c; /* used by 3 fn(s), first 0x00480a70 */
extern undefined DAT_00824f30; /* used by 8 fn(s), first 0x00480a00 */
extern undefined DAT_00824f34; /* used by 1 fn(s), first 0x00480a70 */
extern undefined4 UINT_00825e78; /* used by 2 fn(s), first 0x0047fe50 */
extern undefined4 UINT_00825e7c; /* used by 2 fn(s), first 0x0047fe50 */
extern undefined4 UINT_00825e80; /* used by 1 fn(s), first 0x0047fe50 */
extern undefined4 UINT_00825e84; /* used by 2 fn(s), first 0x0047fe50 */
extern undefined DAT_00825f00; /* used by 3 fn(s), first 0x00481400 */
extern undefined4 UINT_00825f40; /* used by 1 fn(s), first 0x00480890 */
extern uint UINT_008a856c; /* used by 22 fn(s), first 0x00480010 */
extern uint UINT_008a8570; /* used by 15 fn(s), first 0x00480010 */
extern undefined DAT_008a8578; /* used by 3 fn(s), first 0x00481400 */
extern undefined4 UINT_008a85b8; /* used by 4 fn(s), first 0x00480010 */
extern undefined4 UINT_008a85bc; /* used by 2 fn(s), first 0x004800b0 */
extern undefined4 UINT_008a85c0; /* used by 5 fn(s), first 0x00480010 */
extern int * PTR_008a85c4; /* used by 9 fn(s), first 0x00480010 */
extern undefined4 UINT_008a85c8; /* used by 5 fn(s), first 0x00480010 */
extern undefined4 UINT_008a85cc; /* used by 4 fn(s), first 0x00480010 */
extern undefined4 UINT_008a85d0; /* used by 5 fn(s), first 0x00480010 */
extern int * PTR_008a85d4; /* used by 14 fn(s), first 0x00480010 */
extern undefined4 UINT_008a85d8; /* used by 6 fn(s), first 0x00480010 */
extern undefined4 UINT_008a85e0; /* used by 3 fn(s), first 0x00481400 */
extern undefined4 UINT_008a85e4; /* used by 3 fn(s), first 0x00480230 */
extern undefined4 UINT_008a85e8; /* used by 3 fn(s), first 0x004805b0 */
extern undefined DAT_008a85f0; /* used by 4 fn(s), first 0x00482540 */
extern undefined4 UINT_008a8640; /* used by 1 fn(s), first 0x00482fe0 */
extern undefined4 UINT_008a8644; /* used by 1 fn(s), first 0x00483240 */
extern undefined4 UINT_008a86c0; /* used by 1 fn(s), first 0x00482fe0 */
extern undefined4 UINT_008a86c4; /* used by 1 fn(s), first 0x00483240 */
extern undefined4 UINT_008a86e0; /* used by 1 fn(s), first 0x00482fe0 */
extern undefined4 UINT_008a86e4; /* used by 1 fn(s), first 0x00483240 */
extern undefined4 UINT_008a8770; /* used by 6 fn(s), first 0x00482fe0 */
extern undefined DAT_008a8778; /* used by 4 fn(s), first 0x00482540 */
extern undefined4 UINT_008a87c8; /* used by 1 fn(s), first 0x00482fe0 */
extern undefined4 UINT_008a87cc; /* used by 1 fn(s), first 0x00483240 */
extern undefined4 UINT_008a87e8; /* used by 1 fn(s), first 0x00482fe0 */
extern undefined4 UINT_008a87ec; /* used by 1 fn(s), first 0x00483240 */
extern undefined4 UINT_008a8808; /* used by 1 fn(s), first 0x00482fe0 */
extern undefined4 UINT_008a880c; /* used by 1 fn(s), first 0x00483240 */
extern undefined4 UINT_008a8828; /* used by 1 fn(s), first 0x00482fe0 */
extern undefined4 UINT_008a882c; /* used by 1 fn(s), first 0x00483240 */
extern undefined4 UINT_008a8c3c; /* used by 1 fn(s), first 0x00482990 */
extern undefined4 UINT_008a8c40; /* used by 16 fn(s), first 0x004016a0 */
extern undefined4 UINT_008a8c44; /* used by 1 fn(s), first 0x00482900 */
extern uint UINT_008a8c48; /* used by 3 fn(s), first 0x00482fe0 */
extern undefined4 UINT_008a8c58; /* used by 2 fn(s), first 0x00482540 */
extern undefined4 UINT_008a8c5c; /* used by 2 fn(s), first 0x00482ba0 */
extern undefined4 UINT_008a8c60; /* used by 2 fn(s), first 0x00482990 */
extern uint UINT_008a8c70; /* used by 2 fn(s), first 0x00482740 */
extern undefined4 UINT_008a8c78; /* used by 2 fn(s), first 0x004826e0 */
extern undefined4 UINT_008a8c7c; /* used by 3 fn(s), first 0x00482990 */
extern undefined4 UINT_008a8c80; /* used by 3 fn(s), first 0x00482990 */
extern uint UINT_008a8c84; /* used by 2 fn(s), first 0x00482fd0 */
extern undefined4 UINT_008a8c90; /* used by 1 fn(s), first 0x00482900 */
extern undefined4 UINT_008a8c94; /* used by 1 fn(s), first 0x00482900 */
extern undefined4 UINT_008a8c9c; /* used by 3 fn(s), first 0x004836f0 */
extern undefined4 UINT_008a8ca4; /* used by 2 fn(s), first 0x00483720 */
extern undefined DAT_008a8ca8; /* used by 2 fn(s), first 0x00486250 */
extern undefined DAT_008a92a8; /* used by 1 fn(s), first 0x00483f60 */
extern undefined DAT_008a92ac; /* used by 1 fn(s), first 0x00483f60 */
extern undefined DAT_008a92b0; /* used by 1 fn(s), first 0x00483f60 */
extern undefined DAT_008a92b4; /* used by 1 fn(s), first 0x00483f60 */
extern undefined DAT_008a92b8; /* used by 1 fn(s), first 0x00483ed0 */
extern undefined DAT_008a92bc; /* used by 1 fn(s), first 0x00483ed0 */
extern undefined DAT_008a92c0; /* used by 1 fn(s), first 0x00483ed0 */
extern undefined DAT_008a92c4; /* used by 1 fn(s), first 0x00483ed0 */
extern undefined4 UINT_008a92c8; /* used by 1 fn(s), first 0x004874d0 */
extern undefined4 UINT_008a92d0; /* used by 1 fn(s), first 0x004874d0 */
extern undefined4 UINT_008a92d4; /* used by 1 fn(s), first 0x004874d0 */
extern undefined4 UINT_008a94b8; /* used by 3 fn(s), first 0x00484030 */
extern undefined4 UINT_008a94bc; /* used by 6 fn(s), first 0x00484030 */
extern undefined4 UINT_008a94c0; /* used by 6 fn(s), first 0x00484030 */
extern undefined DAT_008a94c4; /* used by 1 fn(s), first 0x00484030 */
extern undefined DAT_008a94cc; /* used by 1 fn(s), first 0x00484030 */
extern undefined4 UINT_008a9510; /* used by 2 fn(s), first 0x004849d0 */
extern undefined4 UINT_008a9514; /* used by 2 fn(s), first 0x004849d0 */
extern undefined4 UINT_008a9518; /* used by 2 fn(s), first 0x004849d0 */
extern undefined4 UINT_008a951c; /* used by 2 fn(s), first 0x004849d0 */
extern undefined4 UINT_008a9520; /* used by 2 fn(s), first 0x004849d0 */
extern undefined4 UINT_008a9524; /* used by 2 fn(s), first 0x004849d0 */
extern undefined4 UINT_008a9528; /* used by 2 fn(s), first 0x004849d0 */
extern uint UINT_008a952c; /* used by 4 fn(s), first 0x00484260 */
extern undefined2 DAT_008c856e; /* used by 1 fn(s), first 0x00486760 */
extern undefined4 UINT_008c9568; /* used by 3 fn(s), first 0x00484260 */
extern undefined4 UINT_008c9770; /* used by 1 fn(s), first 0x004874d0 */
extern undefined4 UINT_008c9780; /* used by 3 fn(s), first 0x00484030 */
extern undefined4 UINT_008c9788; /* used by 2 fn(s), first 0x00483d40 */
extern undefined4 UINT_008c978c; /* used by 2 fn(s), first 0x00486070 */
extern undefined DAT_008c9790; /* used by 2 fn(s), first 0x00484030 */
extern uint UINT_008c97a0; /* used by 2 fn(s), first 0x00484030 */
extern uint UINT_008c97a4; /* used by 4 fn(s), first 0x00484030 */
extern uint UINT_008c97b8; /* used by 2 fn(s), first 0x00483a80 */
extern undefined2 DAT_008c97c6; /* used by 3 fn(s), first 0x00484c40 */
extern undefined4 UINT_008c97c8; /* used by 4 fn(s), first 0x00484c40 */
extern undefined4 UINT_008c97cc; /* used by 4 fn(s), first 0x00484c40 */
extern undefined4 UINT_008c97d0; /* used by 2 fn(s), first 0x00484c40 */
extern undefined4 UINT_008c97d4; /* used by 2 fn(s), first 0x00484c40 */
extern undefined DAT_008c97d8; /* used by 1 fn(s), first 0x00484c40 */
extern undefined DAT_008c97da; /* used by 1 fn(s), first 0x00484c40 */
extern undefined DAT_008c97dc; /* used by 1 fn(s), first 0x00484c40 */
extern undefined DAT_008c97de; /* used by 1 fn(s), first 0x00484c40 */
extern undefined4 UINT_008c97e0; /* used by 2 fn(s), first 0x00484c40 */
extern undefined4 UINT_008c97e4; /* used by 2 fn(s), first 0x00484c40 */
extern undefined4 UINT_008c97e8; /* used by 2 fn(s), first 0x00484c40 */
extern undefined4 UINT_008c97f8; /* used by 4 fn(s), first 0x00483da0 */
extern undefined4 UINT_008c9804; /* used by 1 fn(s), first 0x00484260 */
extern undefined4 UINT_008c9808; /* used by 1 fn(s), first 0x00484a50 */
extern undefined4 UINT_008c980c; /* used by 1 fn(s), first 0x00484a50 */
extern undefined4 UINT_008c9810; /* used by 1 fn(s), first 0x00484a50 */
extern undefined4 UINT_008c9814; /* used by 1 fn(s), first 0x00484a50 */
extern undefined4 UINT_008c9818; /* used by 1 fn(s), first 0x00484a50 */
extern undefined4 UINT_008c981c; /* used by 1 fn(s), first 0x00485420 */
extern undefined4 UINT_008c9820; /* used by 1 fn(s), first 0x00485e50 */
extern undefined4 UINT_008c9824; /* used by 1 fn(s), first 0x004874d0 */
extern undefined4 UINT_008c9828; /* used by 1 fn(s), first 0x00488460 */
extern undefined4 UINT_008c982c; /* used by 1 fn(s), first 0x00488460 */
extern undefined4 UINT_008c9830; /* used by 2 fn(s), first 0x00487e30 */
extern undefined4 UINT_008c9834; /* used by 2 fn(s), first 0x00487e30 */
extern undefined4 UINT_008c9838; /* used by 2 fn(s), first 0x00487e30 */
extern int UINT_008c983c; /* used by 2 fn(s), first 0x00487e30 */
extern undefined4 UINT_008c9840; /* used by 2 fn(s), first 0x00487e30 */
extern undefined DAT_008c9848; /* used by 1 fn(s), first 0x004878c0 */
extern undefined DAT_008c984c; /* used by 1 fn(s), first 0x004878c0 */
extern undefined4 UINT_008c9850; /* used by 2 fn(s), first 0x004878c0 */
extern uint UINT_008c9854; /* used by 3 fn(s), first 0x004876c0 */
extern undefined DAT_008c995f; /* used by 1 fn(s), first 0x004877d0 */
extern undefined4 UINT_008c9a74; /* used by 3 fn(s), first 0x004888d0 */
extern undefined4 UINT_008c9a78; /* used by 2 fn(s), first 0x00488940 */
extern undefined4 UINT_008c9a94; /* used by 3 fn(s), first 0x00488c80 */
extern undefined4 UINT_008c9a98; /* used by 2 fn(s), first 0x00488cf0 */
extern undefined DAT_008c9ca8; /* used by 1 fn(s), first 0x00488fb0 */
extern uint UINT_008c9fb0; /* used by 3 fn(s), first 0x00489030 */
extern uint UINT_008c9fb4; /* used by 3 fn(s), first 0x00489030 */
extern undefined DAT_008c9fb8; /* used by 1 fn(s), first 0x00488fb0 */
extern undefined4 UINT_008c9fc0; /* used by 1 fn(s), first 0x00489130 */
extern undefined DAT_008c9fc4; /* used by 1 fn(s), first 0x00489190 */
extern undefined DAT_008c9ff8; /* used by 1 fn(s), first 0x004892a0 */
extern undefined DAT_008ca080; /* used by 1 fn(s), first 0x00488fb0 */
extern undefined DAT_008ca098; /* used by 1 fn(s), first 0x004891b0 */
extern undefined4 UINT_008ca0a0; /* used by 12 fn(s), first 0x00489520 */
extern undefined4 UINT_008ca0a8; /* used by 2 fn(s), first 0x00489580 */
extern undefined4 UINT_008ca0ac; /* used by 2 fn(s), first 0x004897f0 */
extern undefined DAT_008ca0b0; /* used by 2 fn(s), first 0x00489580 */
extern undefined DAT_008ca0b8; /* used by 1 fn(s), first 0x0048acc0 */
extern undefined4 UINT_008ca0bc; /* used by 1 fn(s), first 0x0048c4d0 */
extern undefined4 UINT_008ca0c0; /* used by 1 fn(s), first 0x0048c500 */
extern undefined4 UINT_008ca0c4; /* used by 1 fn(s), first 0x0048c6f0 */
extern undefined4 UINT_008ca0d8; /* used by 3 fn(s), first 0x0048c050 */
extern undefined4 UINT_008ca0dc; /* used by 4 fn(s), first 0x0048b6a0 */
extern undefined4 UINT_008ca0e0; /* used by 4 fn(s), first 0x0048b6a0 */
extern undefined4 UINT_008ca0e4; /* used by 3 fn(s), first 0x0048b6a0 */
extern undefined4 UINT_008ca0e8; /* used by 2 fn(s), first 0x0048c500 */
extern undefined4 UINT_008ca0ec; /* used by 3 fn(s), first 0x0048c050 */
extern undefined4 UINT_008ca0f0; /* used by 3 fn(s), first 0x0048c050 */
extern undefined4 UINT_008ca0f4; /* used by 3 fn(s), first 0x0048c050 */
extern undefined4 UINT_008ca0f8; /* used by 3 fn(s), first 0x0048c050 */
extern undefined4 UINT_008ca0fc; /* used by 3 fn(s), first 0x0048c050 */
extern undefined4 UINT_008ca100; /* used by 3 fn(s), first 0x0048b6a0 */
extern undefined4 UINT_008ca104; /* used by 3 fn(s), first 0x0048c050 */
extern undefined4 UINT_008ca108; /* used by 3 fn(s), first 0x0048c050 */
extern undefined4 UINT_008ca10c; /* used by 3 fn(s), first 0x0048c050 */
extern undefined4 UINT_008ca110; /* used by 3 fn(s), first 0x0048c050 */
extern undefined4 UINT_008ca114; /* used by 3 fn(s), first 0x0048b6a0 */
extern undefined DAT_008ca118; /* used by 1 fn(s), first 0x0048acc0 */
extern undefined4 UINT_008ca11c; /* used by 1 fn(s), first 0x0048c4d0 */
extern undefined4 UINT_008ca120; /* used by 1 fn(s), first 0x0048c500 */
extern undefined4 UINT_008ca124; /* used by 1 fn(s), first 0x0048c6f0 */
extern undefined4 UINT_008ca138; /* used by 2 fn(s), first 0x0048acc0 */
extern undefined4 UINT_008ca13c; /* used by 2 fn(s), first 0x0048c500 */
extern undefined DAT_008ca144; /* used by 2 fn(s), first 0x0048acc0 */
extern undefined4 UINT_008ca148; /* used by 2 fn(s), first 0x0048c500 */
extern undefined DAT_008ca1b8; /* used by 2 fn(s), first 0x0048d100 */
extern undefined4 UINT_008ca1bc; /* used by 2 fn(s), first 0x0048d100 */
extern undefined4 UINT_008ca1c0; /* used by 2 fn(s), first 0x0048d2e0 */
extern uint UINT_008ca1d0; /* used by 6 fn(s), first 0x0048d4e0 */
extern undefined DAT_008ca1d8; /* used by 1 fn(s), first 0x0048d4e0 */
extern undefined4 UINT_008ca1dc; /* used by 1 fn(s), first 0x0048d770 */
extern undefined4 UINT_008ca1e0; /* used by 1 fn(s), first 0x0048d790 */
extern undefined4 UINT_008ca1e4; /* used by 1 fn(s), first 0x0048d830 */
extern undefined4 UINT_008ca1e8; /* used by 1 fn(s), first 0x0048d4e0 */
extern undefined4 UINT_008ca1ec; /* used by 1 fn(s), first 0x0048d4e0 */
extern undefined4 UINT_008ca1f0; /* used by 1 fn(s), first 0x0048d4e0 */
extern undefined4 UINT_008ca1f4; /* used by 1 fn(s), first 0x0048d4e0 */
extern undefined DAT_008ca1f8; /* used by 2 fn(s), first 0x0048d4e0 */
extern undefined4 UINT_008ca1fc; /* used by 2 fn(s), first 0x0048d790 */
extern undefined4 UINT_008ca200; /* used by 2 fn(s), first 0x0048d790 */
extern undefined4 UINT_008ca204; /* used by 2 fn(s), first 0x0048d790 */
extern undefined4 UINT_008ca314; /* used by 2 fn(s), first 0x0048e2c0 */
extern undefined DAT_008ca318; /* used by 2 fn(s), first 0x0048e2c0 */
extern undefined DAT_008ca31c; /* used by 2 fn(s), first 0x0048e2c0 */
extern undefined DAT_008ca320; /* used by 2 fn(s), first 0x004917e0 */
extern undefined DAT_008ca324; /* used by 3 fn(s), first 0x00492680 */
extern undefined DAT_008ca328; /* used by 3 fn(s), first 0x00492680 */
extern uint UINT_008ca32c; /* used by 11 fn(s), first 0x0048e2c0 */
extern undefined DAT_008ca338; /* used by 1 fn(s), first 0x004939f0 */
extern undefined DAT_008ca33c; /* used by 1 fn(s), first 0x004939f0 */
extern undefined DAT_008ca340; /* used by 1 fn(s), first 0x004939f0 */
extern undefined DAT_008ca348; /* used by 1 fn(s), first 0x004939f0 */
extern undefined DAT_008ca34c; /* used by 1 fn(s), first 0x004939f0 */
extern undefined DAT_008ca350; /* used by 1 fn(s), first 0x004939f0 */
extern undefined4 UINT_008ca768; /* used by 2 fn(s), first 0x0048e2c0 */
extern undefined4 UINT_008ca76c; /* used by 2 fn(s), first 0x00490e80 */
extern undefined DAT_008ca770; /* used by 1 fn(s), first 0x004957f0 */
extern undefined4 UINT_008ca774; /* used by 1 fn(s), first 0x00495960 */
extern undefined4 UINT_008ca778; /* used by 1 fn(s), first 0x004959a0 */
extern undefined4 UINT_008ca77c; /* used by 1 fn(s), first 0x004988a0 */
extern undefined4 UINT_008ca798; /* used by 2 fn(s), first 0x004957f0 */
extern undefined4 UINT_008ca79c; /* used by 2 fn(s), first 0x004959a0 */
extern undefined4 UINT_008ca7a4; /* used by 3 fn(s), first 0x004960a0 */
extern undefined4 UINT_008ca7ac; /* used by 2 fn(s), first 0x004959a0 */
extern undefined4 UINT_008ca7b0; /* used by 2 fn(s), first 0x004959a0 */
extern undefined DAT_008ca7b4; /* used by 2 fn(s), first 0x004960a0 */
extern undefined DAT_008ca7b8; /* used by 3 fn(s), first 0x004959a0 */
extern undefined DAT_008ca837; /* used by 1 fn(s), first 0x00497e10 */
extern undefined DAT_008ca838; /* used by 3 fn(s), first 0x004959a0 */
extern undefined DAT_008ca8b7; /* used by 1 fn(s), first 0x004960a0 */
extern undefined DAT_008ca8b8; /* used by 3 fn(s), first 0x004959a0 */
extern undefined DAT_008ca937; /* used by 1 fn(s), first 0x00496460 */
extern undefined DAT_008ca938; /* used by 4 fn(s), first 0x004959a0 */
extern undefined DAT_008ca9b7; /* used by 2 fn(s), first 0x00496670 */
extern undefined DAT_008ca9b8; /* used by 3 fn(s), first 0x004959a0 */
extern undefined DAT_008caa37; /* used by 1 fn(s), first 0x00496b60 */
extern undefined DAT_008caa38; /* used by 3 fn(s), first 0x004959a0 */
extern undefined DAT_008caab7; /* used by 1 fn(s), first 0x00497460 */
extern undefined DAT_008caab8; /* used by 3 fn(s), first 0x004959a0 */
extern undefined DAT_008cab37; /* used by 1 fn(s), first 0x00498190 */
extern undefined4 UINT_008cab44; /* used by 2 fn(s), first 0x0049d220 */
extern undefined4 UINT_008cab48; /* used by 2 fn(s), first 0x0049d140 */
extern undefined DAT_008cab50; /* used by 1 fn(s), first 0x0049c9f0 */
extern undefined4 UINT_008cab54; /* used by 1 fn(s), first 0x0049e500 */
extern undefined4 UINT_008cab58; /* used by 1 fn(s), first 0x0049de00 */
extern undefined4 UINT_008cab5c; /* used by 1 fn(s), first 0x0049e530 */
extern undefined4 UINT_008cab7c; /* used by 2 fn(s), first 0x0049c9f0 */
extern undefined4 UINT_008cab80; /* used by 2 fn(s), first 0x0049de00 */
extern uint UINT_008cab8c; /* used by 2 fn(s), first 0x00499250 */
extern undefined DAT_008cab94; /* used by 2 fn(s), first 0x004a3d00 */
extern undefined4 UINT_008cab98; /* used by 2 fn(s), first 0x004a3d00 */
extern undefined4 UINT_008cab9c; /* used by 2 fn(s), first 0x004a3d70 */
extern undefined DAT_008cac08; /* used by 2 fn(s), first 0x004a54a0 */
extern undefined DAT_008cac27; /* used by 1 fn(s), first 0x004a54a0 */
extern undefined DAT_008cac28; /* used by 2 fn(s), first 0x004a54a0 */
extern undefined4 UINT_008cb098; /* used by 2 fn(s), first 0x004a48c0 */
extern undefined4 UINT_008cb09c; /* used by 2 fn(s), first 0x004a53b0 */
extern uint UINT_008cb0a4; /* used by 2 fn(s), first 0x004a54a0 */
extern uint UINT_008cb0a8; /* used by 5 fn(s), first 0x004a4b00 */
extern float FLOAT_008cb0b0; /* used by 2 fn(s), first 0x004a6380 */
extern undefined4 UINT_008cb0b4; /* used by 2 fn(s), first 0x004a6380 */
extern undefined4 UINT_008cb0b8; /* used by 2 fn(s), first 0x004a6380 */
extern undefined4 UINT_008cb0bc; /* used by 1 fn(s), first 0x004a6380 */
extern undefined4 UINT_008cf0b0; /* used by 3 fn(s), first 0x004a9420 */
extern undefined4 UINT_008cf0b4; /* used by 3 fn(s), first 0x004a9430 */
extern undefined4 UINT_008cf0b8; /* used by 2 fn(s), first 0x004a9430 */
extern undefined4 UINT_008cf0c8; /* used by 1 fn(s), first 0x004a9aa0 */
extern undefined DAT_008cf218; /* used by 1 fn(s), first 0x004a7bc0 */
extern uint UINT_008cf248; /* used by 4 fn(s), first 0x004a9420 */
extern undefined DAT_008cf250; /* used by 1 fn(s), first 0x004a82a0 */
extern undefined DAT_008cf264; /* used by 1 fn(s), first 0x004a7520 */
extern undefined DAT_008cf268; /* used by 1 fn(s), first 0x004a7520 */
extern undefined4 UINT_008cf26c; /* used by 3 fn(s), first 0x004a6380 */
extern undefined DAT_008cf284; /* used by 1 fn(s), first 0x004a7150 */
extern undefined4 UINT_008cf288; /* used by 3 fn(s), first 0x004a6490 */
extern undefined DAT_008cf28c; /* used by 2 fn(s), first 0x004a6490 */
extern undefined4 UINT_008d0868; /* used by 3 fn(s), first 0x004a61c0 */
extern uint UINT_008d086c; /* used by 3 fn(s), first 0x00485dc0 */
extern undefined4 UINT_008d0870; /* used by 1 fn(s), first 0x004a8610 */
extern undefined DAT_008d0880; /* used by 6 fn(s), first 0x004aa820 */
extern undefined DAT_008d0900; /* used by 1 fn(s), first 0x004ab5d0 */
extern undefined DAT_008d097f; /* used by 1 fn(s), first 0x004ab5d0 */
extern undefined4 UINT_008d0980; /* used by 3 fn(s), first 0x004aa7b0 */
extern undefined4 UINT_008d0984; /* used by 2 fn(s), first 0x004aa820 */
extern undefined DAT_008d098c; /* used by 1 fn(s), first 0x004abe90 */
extern undefined4 UINT_008d0990; /* used by 3 fn(s), first 0x004abe90 */
extern undefined4 UINT_008d0994; /* used by 2 fn(s), first 0x004abf00 */
extern int UINT_008d09dc; /* used by 2 fn(s), first 0x004ac100 */
extern undefined DAT_008d09e0; /* used by 1 fn(s), first 0x004abf40 */
extern uint UINT_008d09e4; /* used by 2 fn(s), first 0x004abf40 */
extern undefined DAT_008d0a68; /* used by 1 fn(s), first 0x004ac340 */
extern undefined4 UINT_008d0a6c; /* used by 1 fn(s), first 0x004ac340 */
extern undefined4 UINT_008d0a70; /* used by 3 fn(s), first 0x004016a0 */
extern undefined4 UINT_008d0a7c; /* used by 4 fn(s), first 0x004abf40 */
extern undefined4 UINT_008d0a84; /* used by 2 fn(s), first 0x004abf40 */
extern undefined4 UINT_008d0a88; /* used by 2 fn(s), first 0x004abf40 */
extern undefined4 UINT_008d0a8c; /* used by 2 fn(s), first 0x004abf40 */
extern undefined4 UINT_008d0a90; /* used by 1 fn(s), first 0x004ac340 */
extern undefined4 UINT_008d0a94; /* used by 1 fn(s), first 0x004ac340 */
extern undefined4 UINT_008d0a98; /* used by 1 fn(s), first 0x004ac340 */
extern undefined4 UINT_008d0a9c; /* used by 1 fn(s), first 0x004ae562 */
extern undefined4 UINT_008d0aa0; /* used by 2 fn(s), first 0x004ac690 */
extern undefined4 UINT_008d0aa4; /* used by 2 fn(s), first 0x004aca30 */
extern undefined4 UINT_008d0aac; /* used by 4 fn(s), first 0x004acbe0 */
extern undefined4 UINT_008d0ab0; /* used by 1 fn(s), first 0x004b8660 */
extern undefined DAT_008d0ab4; /* used by 1 fn(s), first 0x004aca30 */
extern undefined DAT_008d0ab8; /* used by 1 fn(s), first 0x004aca30 */
extern undefined DAT_008d0abc; /* used by 1 fn(s), first 0x004aca30 */
extern undefined DAT_008d0ac0; /* used by 1 fn(s), first 0x004aca30 */
extern undefined DAT_008d0ac4; /* used by 1 fn(s), first 0x004b10d0 */
extern undefined DAT_008d0ac8; /* used by 1 fn(s), first 0x004b10d0 */
extern undefined4 UINT_008d0ad0; /* used by 4 fn(s), first 0x004b0fe0 */
extern undefined4 UINT_008d0ad4; /* used by 1 fn(s), first 0x004bce80 */
extern undefined4 UINT_008d0ad8; /* used by 3 fn(s), first 0x004bbb80 */
extern undefined DAT_008d0ae0; /* used by 1 fn(s), first 0x004b10d0 */
extern undefined DAT_008d0ae8; /* used by 2 fn(s), first 0x004acd80 */
extern undefined DAT_008d0aec; /* used by 1 fn(s), first 0x004acd80 */
extern undefined4 UINT_008d0af0; /* used by 1 fn(s), first 0x004acd80 */
extern undefined4 UINT_008d0af8; /* used by 2 fn(s), first 0x004ad260 */
extern undefined4 UINT_008d0afc; /* used by 1 fn(s), first 0x004ad260 */
extern uint UINT_008d0b70; /* used by 13 fn(s), first 0x004ac550 */
extern undefined4 UINT_008d0b74; /* used by 1 fn(s), first 0x004b6730 */
extern undefined4 UINT_008d0b78; /* used by 1 fn(s), first 0x004b64f0 */
extern undefined4 UINT_008d0b7c; /* used by 1 fn(s), first 0x004b5d80 */
extern uint UINT_008d0b80; /* used by 9 fn(s), first 0x004b1710 */
extern undefined DAT_008d0b90; /* used by 1 fn(s), first 0x004b10d0 */
extern undefined4 UINT_008d0c98; /* used by 1 fn(s), first 0x004b1380 */
extern undefined4 UINT_008d0ca0; /* used by 6 fn(s), first 0x004b0fa0 */
extern undefined DAT_008d0da8; /* used by 1 fn(s), first 0x004b1800 */
extern undefined4 UINT_008d0ea8; /* used by 5 fn(s), first 0x004b14e0 */
extern undefined4 UINT_008d0eac; /* used by 4 fn(s), first 0x004b14e0 */
extern undefined DAT_008d0eb0; /* used by 2 fn(s), first 0x004b14e0 */
extern undefined DAT_008d0eb4; /* used by 2 fn(s), first 0x004b14e0 */
extern undefined DAT_008d0eb8; /* used by 2 fn(s), first 0x004b14e0 */
extern undefined4 UINT_008d0ebc; /* used by 2 fn(s), first 0x004b14e0 */
extern undefined4 UINT_008d0ec0; /* used by 1 fn(s), first 0x004b1d20 */
extern undefined4 UINT_008d0ec8; /* used by 1 fn(s), first 0x004b1f40 */
extern undefined4 UINT_008d0ed0; /* used by 4 fn(s), first 0x004b1f40 */
extern undefined4 UINT_008d0ed4; /* used by 3 fn(s), first 0x004acf70 */
extern undefined4 UINT_008d0ed8; /* used by 1 fn(s), first 0x004b2190 */
extern undefined4 UINT_008d0edc; /* used by 2 fn(s), first 0x004b2380 */
extern undefined4 UINT_008d0ee4; /* used by 1 fn(s), first 0x004b4560 */
extern undefined4 UINT_008d0ee8; /* used by 1 fn(s), first 0x004b5d80 */
extern undefined4 UINT_008d0eec; /* used by 1 fn(s), first 0x004b64f0 */
extern undefined4 UINT_008d0ef0; /* used by 1 fn(s), first 0x004b64f0 */
extern undefined4 UINT_008d0ef4; /* used by 1 fn(s), first 0x004b64f0 */
extern undefined4 UINT_008d0ef8; /* used by 1 fn(s), first 0x004b6730 */
extern undefined4 UINT_008d0efc; /* used by 1 fn(s), first 0x004b69e0 */
extern undefined4 UINT_008d0f00; /* used by 1 fn(s), first 0x004b69e0 */
extern undefined2 DAT_008d0f14; /* used by 1 fn(s), first 0x004b69e0 */
extern undefined2 DAT_008d0f1c; /* used by 1 fn(s), first 0x004b6820 */
extern undefined2 DAT_008d0f22; /* used by 1 fn(s), first 0x004b64f0 */
extern undefined2 DAT_008d0f26; /* used by 1 fn(s), first 0x004b5e30 */
extern undefined2 DAT_008d0f28; /* used by 1 fn(s), first 0x004b5e30 */
extern undefined4 UINT_008d0f50; /* used by 1 fn(s), first 0x004b7800 */
extern uint UINT_008d0f54; /* used by 1 fn(s), first 0x004b7990 */
extern undefined4 UINT_008d0f58; /* used by 1 fn(s), first 0x004b7b80 */
extern undefined4 UINT_008d0f5c; /* used by 1 fn(s), first 0x004b7b80 */
extern undefined4 UINT_008d0f60; /* used by 1 fn(s), first 0x004b7b80 */
extern undefined4 UINT_008d0f68; /* used by 2 fn(s), first 0x004b7f40 */
extern undefined4 UINT_008d0f70; /* used by 1 fn(s), first 0x004b7f40 */
extern undefined DAT_008d0f74; /* used by 1 fn(s), first 0x004b7f40 */
extern undefined2 DAT_008d0fb4; /* used by 1 fn(s), first 0x004b8250 */
extern undefined2 DAT_008d0fb6; /* used by 2 fn(s), first 0x004b7f40 */
extern undefined4 UINT_008d0fb8; /* used by 1 fn(s), first 0x004b8250 */
extern undefined4 UINT_008d0fbc; /* used by 1 fn(s), first 0x004b8250 */
extern undefined4 UINT_008d0fc0; /* used by 1 fn(s), first 0x004b8250 */
extern undefined4 UINT_008d0fc4; /* used by 1 fn(s), first 0x004b7f40 */
extern undefined DAT_008d0fc8; /* used by 1 fn(s), first 0x004b7f40 */
extern undefined2 DAT_008d1008; /* used by 1 fn(s), first 0x004b8250 */
extern undefined2 DAT_008d100a; /* used by 2 fn(s), first 0x004b7f40 */
extern undefined4 UINT_008d100c; /* used by 1 fn(s), first 0x004b8250 */
extern undefined4 UINT_008d1010; /* used by 1 fn(s), first 0x004b8250 */
extern undefined4 UINT_008d1014; /* used by 1 fn(s), first 0x004b8250 */
extern undefined4 UINT_008d1018; /* used by 1 fn(s), first 0x004b7f40 */
extern undefined4 UINT_008d101c; /* used by 1 fn(s), first 0x004b7f40 */
extern undefined4 UINT_008d1020; /* used by 1 fn(s), first 0x004b7f00 */
extern undefined4 UINT_008d1024; /* used by 2 fn(s), first 0x004b2a60 */
extern undefined4 UINT_008d1028; /* used by 3 fn(s), first 0x004ba230 */
extern undefined DAT_008d1038; /* used by 1 fn(s), first 0x004ba340 */
extern undefined DAT_008d1040; /* used by 1 fn(s), first 0x004b6970 */
extern undefined4 UINT_008d1044; /* used by 1 fn(s), first 0x004ba600 */
extern undefined4 UINT_008d1048; /* used by 1 fn(s), first 0x004ba600 */
extern undefined4 UINT_008d104c; /* used by 1 fn(s), first 0x004ba600 */
extern undefined4 UINT_008d1050; /* used by 1 fn(s), first 0x004ba600 */
extern undefined DAT_008d1058; /* used by 1 fn(s), first 0x004bb570 */
extern undefined4 UINT_008d107c; /* used by 1 fn(s), first 0x004b8660 */
extern undefined4 UINT_008d1080; /* used by 1 fn(s), first 0x004bc4c0 */
extern undefined4 UINT_008d1084; /* used by 1 fn(s), first 0x004bc5f0 */
extern undefined4 UINT_008d108c; /* used by 1 fn(s), first 0x004bcbb0 */
extern undefined DAT_008d1090; /* used by 1 fn(s), first 0x004bd970 */
extern undefined4 UINT_008d1098; /* used by 2 fn(s), first 0x004bd540 */
extern undefined4 UINT_008d109c; /* used by 2 fn(s), first 0x004bd570 */
extern undefined4 UINT_008d10a0; /* used by 1 fn(s), first 0x004bd970 */
extern undefined4 UINT_008d10a4; /* used by 1 fn(s), first 0x004bd970 */
extern undefined4 UINT_008d10a8; /* used by 1 fn(s), first 0x004bd570 */
extern int * PTR_008d10c8; /* used by 3 fn(s), first 0x004bd570 */
extern undefined4 UINT_008d10d0; /* used by 2 fn(s), first 0x004bd570 */
extern int * PTR_008d11d4; /* used by 5 fn(s), first 0x004bd3a0 */
extern undefined4 UINT_008d11d8; /* used by 5 fn(s), first 0x004bd500 */
extern int UINT_008d11e0; /* used by 3 fn(s), first 0x004bd570 */
extern int UINT_008d11e4; /* used by 3 fn(s), first 0x004bd570 */
extern undefined4 UINT_008d11e8; /* used by 3 fn(s), first 0x004bd570 */
extern undefined4 UINT_008d11ec; /* used by 3 fn(s), first 0x004bd570 */
extern undefined DAT_008d11f0; /* used by 1 fn(s), first 0x004bdf70 */
extern uint UINT_008d11f4; /* used by 10 fn(s), first 0x004bd3a0 */
extern int * PTR_008d11f8; /* used by 2 fn(s), first 0x004bdf70 */
extern undefined4 UINT_008d1200; /* used by 5 fn(s), first 0x004bd500 */
extern undefined DAT_008d1208; /* used by 1 fn(s), first 0x004bd570 */
extern undefined2 DAT_008d120c; /* used by 1 fn(s), first 0x004bd570 */
extern undefined2 DAT_008d120e; /* used by 1 fn(s), first 0x004bd570 */
extern undefined2 DAT_008d1210; /* used by 1 fn(s), first 0x004bd570 */
extern undefined2 DAT_008d1212; /* used by 1 fn(s), first 0x004bd570 */
extern undefined4 UINT_008d1216; /* used by 1 fn(s), first 0x004bd970 */
extern undefined4 UINT_008d121a; /* used by 2 fn(s), first 0x004bd570 */
extern undefined DAT_008d1630; /* used by 1 fn(s), first 0x004be050 */
extern undefined4 UINT_008d1638; /* used by 1 fn(s), first 0x004bdea0 */
extern undefined4 UINT_008d163c; /* used by 1 fn(s), first 0x004bdea0 */
extern undefined4 UINT_008d1640; /* used by 1 fn(s), first 0x004bdea0 */
extern undefined4 UINT_008d1644; /* used by 1 fn(s), first 0x004bdea0 */
extern undefined DAT_008d1648; /* used by 1 fn(s), first 0x004bd970 */
extern undefined DAT_008d164c; /* used by 1 fn(s), first 0x004bd570 */
extern undefined DAT_008d1650; /* used by 1 fn(s), first 0x004bd570 */
extern undefined DAT_008d1654; /* used by 1 fn(s), first 0x004bd570 */
extern undefined DAT_008d1658; /* used by 1 fn(s), first 0x004bd570 */
extern undefined DAT_008d165c; /* used by 1 fn(s), first 0x004bd570 */
extern undefined DAT_008d1660; /* used by 1 fn(s), first 0x004bd570 */
extern undefined DAT_008d1664; /* used by 1 fn(s), first 0x004bd570 */
extern undefined DAT_008d1668; /* used by 1 fn(s), first 0x004bd570 */
extern undefined DAT_008d166c; /* used by 1 fn(s), first 0x004bd570 */
extern undefined DAT_008d1670; /* used by 1 fn(s), first 0x004bd570 */
extern undefined DAT_008d1674; /* used by 1 fn(s), first 0x004bd570 */
extern undefined DAT_008d1678; /* used by 1 fn(s), first 0x004bd570 */
extern undefined DAT_008d167c; /* used by 1 fn(s), first 0x004bd570 */
extern undefined DAT_008d1680; /* used by 1 fn(s), first 0x004bd570 */
extern undefined DAT_008d1684; /* used by 1 fn(s), first 0x004bd570 */
extern undefined DAT_008d1688; /* used by 1 fn(s), first 0x004bd570 */
extern undefined DAT_008d168c; /* used by 1 fn(s), first 0x004bd570 */
extern undefined4 UINT_008d169c; /* used by 1 fn(s), first 0x004bd930 */
extern undefined4 UINT_008d16a0; /* used by 4 fn(s), first 0x004bd370 */
extern undefined4 UINT_008d16a4; /* used by 3 fn(s), first 0x004bd370 */
extern undefined4 UINT_008d16a8; /* used by 6 fn(s), first 0x004bd370 */
extern undefined DAT_008d16ac; /* used by 1 fn(s), first 0x004bdb00 */
extern undefined DAT_008d16b0; /* used by 1 fn(s), first 0x004bdad0 */
extern undefined DAT_008d16b4; /* used by 1 fn(s), first 0x004bd560 */
extern uint UINT_008d16b8; /* used by 3 fn(s), first 0x004bd930 */
extern uint UINT_008d16bc; /* used by 3 fn(s), first 0x004bdad0 */
extern undefined DAT_008d16c0; /* used by 1 fn(s), first 0x004bdb00 */
extern undefined4 UINT_008d16c8; /* used by 1 fn(s), first 0x004be4c0 */
extern undefined4 UINT_008d1730; /* used by 12 fn(s), first 0x004be310 */
extern undefined4 UINT_008d1734; /* used by 5 fn(s), first 0x004be560 */
extern undefined4 UINT_008d1738; /* used by 6 fn(s), first 0x004be3b0 */
extern undefined4 UINT_008d173c; /* used by 3 fn(s), first 0x004be7b0 */
extern undefined4 UINT_008d1740; /* used by 3 fn(s), first 0x004be7b0 */
extern undefined4 UINT_008d1c30; /* used by 2 fn(s), first 0x004be310 */
extern undefined4 UINT_008d1c50; /* used by 1 fn(s), first 0x004be3b0 */
extern undefined4 UINT_008d1c54; /* used by 1 fn(s), first 0x004be3b0 */
extern undefined4 UINT_008d1c58; /* used by 1 fn(s), first 0x004be3b0 */
extern undefined4 UINT_008d363c; /* used by 3 fn(s), first 0x004be180 */
extern undefined4 UINT_008d3640; /* used by 2 fn(s), first 0x004bf3f0 */
extern undefined4 UINT_008d3644; /* used by 2 fn(s), first 0x004be310 */
extern undefined4 UINT_008d3648; /* used by 1 fn(s), first 0x004bffb0 */
extern undefined4 UINT_008d364c; /* used by 1 fn(s), first 0x004c0660 */
extern undefined4 UINT_008d3650; /* used by 1 fn(s), first 0x004c0e40 */
extern undefined4 UINT_008d3654; /* used by 2 fn(s), first 0x004c0ed0 */
extern undefined4 UINT_008d3658; /* used by 2 fn(s), first 0x004c0ed0 */
extern undefined4 UINT_008d3660; /* used by 1 fn(s), first 0x004c0ed0 */
extern undefined4 UINT_008d3664; /* used by 1 fn(s), first 0x004c0ed0 */
extern int * PTR_008d3674; /* used by 2 fn(s), first 0x004c0ed0 */
extern undefined DAT_008d3680; /* used by 1 fn(s), first 0x004c1990 */
extern undefined DAT_008d36e3; /* used by 1 fn(s), first 0x004c1990 */
extern undefined DAT_008d36e8; /* used by 1 fn(s), first 0x004c1c30 */
extern undefined4 UINT_008d56e8; /* used by 3 fn(s), first 0x004c1390 */
extern uint UINT_008d56ec; /* used by 2 fn(s), first 0x004c1590 */
extern uint UINT_008d56f0; /* used by 8 fn(s), first 0x004c13f0 */
extern int * PTR_008d56f4; /* used by 2 fn(s), first 0x004c1460 */
extern uint UINT_008d56f8; /* used by 8 fn(s), first 0x004c13f0 */
extern undefined4 UINT_008d56fc; /* used by 3 fn(s), first 0x004c1460 */
extern undefined4 UINT_008d5700; /* used by 1 fn(s), first 0x004c15c0 */
extern undefined DAT_008d5704; /* used by 1 fn(s), first 0x004c15c0 */
extern uint UINT_008d6efc; /* used by 1 fn(s), first 0x004c1990 */
extern undefined4 UINT_008d6f00; /* used by 1 fn(s), first 0x004c1990 */
extern undefined4 UINT_008d6f04; /* used by 3 fn(s), first 0x004c1ff0 */
extern undefined DAT_008d6f08; /* used by 1 fn(s), first 0x004c1f40 */
extern undefined DAT_008d6f0c; /* used by 1 fn(s), first 0x004c1f40 */
extern int * PTR_008d6f10; /* used by 7 fn(s), first 0x004c1ff0 */
extern uint UINT_008d6f14; /* used by 2 fn(s), first 0x004c1f40 */
extern undefined4 UINT_008d6f18; /* used by 4 fn(s), first 0x004c1ff0 */
extern undefined4 UINT_008d6f1c; /* used by 2 fn(s), first 0x004c27a0 */
extern uint UINT_008d6f20; /* used by 3 fn(s), first 0x004c23c0 */
extern undefined4 UINT_008d6f24; /* used by 2 fn(s), first 0x004c2690 */
extern undefined4 UINT_008d6f28; /* used by 1 fn(s), first 0x004c27a0 */
extern undefined4 UINT_008d6f30; /* used by 2 fn(s), first 0x004c2be0 */
extern undefined4 UINT_008d70c0; /* used by 5 fn(s), first 0x004c2be0 */
extern undefined4 UINT_008d7250; /* used by 3 fn(s), first 0x004c2be0 */
extern uint UINT_008d73e0; /* used by 2 fn(s), first 0x004c2b50 */
extern undefined DAT_008d73e8; /* used by 1 fn(s), first 0x004c2fa0 */
extern uint UINT_008d77e8; /* used by 2 fn(s), first 0x004c2fa0 */
extern uint UINT_008d77ec; /* used by 5 fn(s), first 0x004c2be0 */
extern undefined4 UINT_008d77f0; /* used by 3 fn(s), first 0x004c2be0 */
extern undefined4 UINT_008d77f4; /* used by 4 fn(s), first 0x004c2be0 */
extern undefined4 UINT_008d77f8; /* used by 2 fn(s), first 0x004c2be0 */
extern undefined4 UINT_008d77fc; /* used by 2 fn(s), first 0x004c2be0 */
extern undefined4 UINT_008d7800; /* used by 2 fn(s), first 0x004c34d0 */
extern undefined4 UINT_008d7804; /* used by 1 fn(s), first 0x004c2fa0 */
extern uint UINT_008d7808; /* used by 1 fn(s), first 0x004c34d0 */
extern undefined DAT_008d780c; /* used by 1 fn(s), first 0x004c34d0 */
extern undefined DAT_008d7810; /* used by 1 fn(s), first 0x004c3bb0 */
extern int * PTR_008d7814; /* used by 4 fn(s), first 0x004c4b90 */
extern int * PTR_008d7818; /* used by 5 fn(s), first 0x004c4b20 */
extern int * PTR_008d781c; /* used by 7 fn(s), first 0x004c4b90 */
extern uint UINT_008d7820; /* used by 2 fn(s), first 0x004c4b20 */
extern undefined4 UINT_008d7824; /* used by 1 fn(s), first 0x004c50a0 */
extern undefined4 UINT_008d7828; /* used by 2 fn(s), first 0x004c52f0 */
extern int * PTR_008d782c; /* used by 4 fn(s), first 0x004c5280 */
extern uint UINT_008d7830; /* used by 2 fn(s), first 0x004c5280 */
extern int * PTR_008d7834; /* used by 4 fn(s), first 0x004c5870 */
extern int * PTR_008d7838; /* used by 4 fn(s), first 0x004c5790 */
extern uint UINT_008d783c; /* used by 4 fn(s), first 0x004c57d0 */
extern uint UINT_008d7840; /* used by 2 fn(s), first 0x004c5790 */
extern int * PTR_008d7844; /* used by 4 fn(s), first 0x004c5ce0 */
extern int * PTR_008d7848; /* used by 13 fn(s), first 0x004c5d50 */
extern uint UINT_008d784c; /* used by 2 fn(s), first 0x004c5ce0 */
extern int * PTR_008d7850; /* used by 2 fn(s), first 0x004cbaa0 */
extern undefined DAT_008d7858; /* used by 2 fn(s), first 0x004cbc00 */
extern undefined DAT_008d7859; /* used by 1 fn(s), first 0x004cbc00 */
extern undefined2 DAT_008d785a; /* used by 2 fn(s), first 0x004cbc00 */
extern undefined2 DAT_008d785c; /* used by 1 fn(s), first 0x004cbc00 */
extern undefined2 DAT_008d785e; /* used by 3 fn(s), first 0x004cbbd0 */
extern uint UINT_008d7860; /* used by 2 fn(s), first 0x004cbbe0 */
extern int * PTR_008d7864; /* used by 4 fn(s), first 0x004cba30 */
extern undefined2 DAT_008d7868; /* used by 1 fn(s), first 0x004cbf50 */
extern undefined DAT_008d78e8; /* used by 1 fn(s), first 0x004cbf50 */
extern uint UINT_008da4e8; /* used by 2 fn(s), first 0x004cba30 */
extern undefined4 UINT_008da4ec; /* used by 3 fn(s), first 0x004cbaa0 */
extern int * PTR_008da4f0; /* used by 3 fn(s), first 0x004cbaa0 */
extern undefined4 UINT_008da4f4; /* used by 1 fn(s), first 0x004cbf50 */
extern int * PTR_008da4f8; /* used by 4 fn(s), first 0x004cc2c0 */
extern int * PTR_008da4fc; /* used by 4 fn(s), first 0x004cc2c0 */
extern int * PTR_008da500; /* used by 4 fn(s), first 0x004cc210 */
extern uint UINT_008da504; /* used by 2 fn(s), first 0x004cc210 */
extern undefined4 UINT_008da508; /* used by 2 fn(s), first 0x004cc250 */
extern undefined4 UINT_008da50c; /* used by 2 fn(s), first 0x004cc410 */
extern undefined4 UINT_008da510; /* used by 4 fn(s), first 0x004cc410 */
extern undefined4 UINT_008da514; /* used by 3 fn(s), first 0x004cc410 */
extern undefined4 UINT_008da518; /* used by 3 fn(s), first 0x004cc410 */
extern undefined4 UINT_008da51c; /* used by 2 fn(s), first 0x004cc410 */
extern uint UINT_008da520; /* used by 2 fn(s), first 0x004cc3c0 */
extern int * PTR_008da528; /* used by 5 fn(s), first 0x004cc3c0 */
extern undefined4 UINT_008da52c; /* used by 3 fn(s), first 0x004cc410 */
extern undefined4 UINT_008da530; /* used by 3 fn(s), first 0x004cc410 */
extern undefined4 UINT_008da534; /* used by 2 fn(s), first 0x004cc410 */
extern undefined4 UINT_008da538; /* used by 1 fn(s), first 0x004ccd00 */
extern undefined4 UINT_008da540; /* used by 2 fn(s), first 0x004cdd10 */
extern undefined4 UINT_008da544; /* used by 2 fn(s), first 0x004cdc90 */
extern undefined DAT_008da548; /* used by 1 fn(s), first 0x004ce1d0 */
extern undefined DAT_008da588; /* used by 1 fn(s), first 0x004ce1d0 */
extern uint UINT_008da5c8; /* used by 2 fn(s), first 0x004cdfd0 */
extern int * PTR_008da5cc; /* used by 4 fn(s), first 0x004cdc90 */
extern undefined DAT_008da5d0; /* used by 1 fn(s), first 0x004ce1d0 */
extern undefined4 UINT_008da5d4; /* used by 1 fn(s), first 0x004ce1d0 */
extern undefined DAT_008da5d8; /* used by 2 fn(s), first 0x004cdf10 */
extern undefined DAT_008da5dc; /* used by 2 fn(s), first 0x004cdf10 */
extern undefined DAT_008da5ec; /* used by 2 fn(s), first 0x004cdf10 */
extern undefined4 UINT_008da5f8; /* used by 2 fn(s), first 0x004cdd80 */
extern undefined4 UINT_008da60c; /* used by 3 fn(s), first 0x004ce020 */
extern undefined4 UINT_008da858; /* used by 2 fn(s), first 0x004cdd80 */
extern uint UINT_008da85c; /* used by 2 fn(s), first 0x004cdc90 */
extern uint UINT_008da860; /* used by 2 fn(s), first 0x004cdd80 */
extern undefined4 UINT_008da864; /* used by 1 fn(s), first 0x004cddf0 */
extern undefined4 UINT_008da868; /* used by 2 fn(s), first 0x004ce060 */
extern undefined DAT_008da86c; /* used by 1 fn(s), first 0x004ce060 */
extern undefined4 UINT_008da870; /* used by 1 fn(s), first 0x004ce060 */
extern undefined4 UINT_008da874; /* used by 3 fn(s), first 0x004cdd80 */
extern undefined4 UINT_008da878; /* used by 3 fn(s), first 0x004cdef0 */
extern undefined4 UINT_008da87c; /* used by 1 fn(s), first 0x004ce060 */
extern undefined4 UINT_008da880; /* used by 1 fn(s), first 0x004ce060 */
extern undefined4 UINT_008da884; /* used by 1 fn(s), first 0x004ce1d0 */
extern undefined DAT_008da888; /* used by 1 fn(s), first 0x004ce1d0 */
extern undefined4 UINT_008da88c; /* used by 1 fn(s), first 0x004ce1d0 */
extern int * PTR_008da890; /* used by 5 fn(s), first 0x004ce350 */
extern int * PTR_008da894; /* used by 4 fn(s), first 0x004ce2e0 */
extern uint UINT_008da898; /* used by 2 fn(s), first 0x004ce2e0 */
extern undefined4 UINT_008da89c; /* used by 3 fn(s), first 0x004ce350 */
extern undefined4 UINT_008da8a0; /* used by 1 fn(s), first 0x004cedc0 */
extern int * PTR_008da8a8; /* used by 4 fn(s), first 0x004d03d0 */
extern undefined4 UINT_008da8f0; /* used by 1 fn(s), first 0x004d16a0 */
extern undefined4 UINT_008da8f4; /* used by 1 fn(s), first 0x004d16a0 */
extern undefined4 UINT_008da8f8; /* used by 1 fn(s), first 0x004d16a0 */
extern undefined4 UINT_008da8fc; /* used by 1 fn(s), first 0x004d16a0 */
extern undefined4 UINT_008da900; /* used by 1 fn(s), first 0x004d16a0 */
extern undefined4 UINT_008da904; /* used by 1 fn(s), first 0x004d16a0 */
extern undefined DAT_008da908; /* used by 1 fn(s), first 0x004d16a0 */
extern undefined4 UINT_008da90c; /* used by 1 fn(s), first 0x004d16a0 */
extern undefined4 UINT_008da910; /* used by 1 fn(s), first 0x004d16a0 */
extern undefined4 UINT_008da914; /* used by 1 fn(s), first 0x004d16a0 */
extern undefined4 UINT_008da918; /* used by 1 fn(s), first 0x004d16a0 */
extern undefined DAT_008da91c; /* used by 1 fn(s), first 0x004d16a0 */
extern undefined4 UINT_008da920; /* used by 1 fn(s), first 0x004d16a0 */
extern undefined4 UINT_008da924; /* used by 1 fn(s), first 0x004d16a0 */
extern undefined4 UINT_008da928; /* used by 1 fn(s), first 0x004d16a0 */
extern undefined4 UINT_008dacb0; /* used by 2 fn(s), first 0x004d0300 */
extern undefined4 UINT_008dacb4; /* used by 1 fn(s), first 0x004d03d0 */
extern undefined4 UINT_008dacb8; /* used by 1 fn(s), first 0x004d03d0 */
extern undefined4 UINT_008dacbc; /* used by 1 fn(s), first 0x004d03d0 */
extern undefined4 UINT_008dacc0; /* used by 1 fn(s), first 0x004d03d0 */
extern undefined4 UINT_008dacc4; /* used by 1 fn(s), first 0x004d03d0 */
extern undefined4 UINT_008dacc8; /* used by 1 fn(s), first 0x004d03d0 */
extern undefined4 UINT_008daccc; /* used by 1 fn(s), first 0x004d03d0 */
extern undefined4 UINT_008dacd0; /* used by 1 fn(s), first 0x004d03d0 */
extern undefined4 UINT_008dacd4; /* used by 1 fn(s), first 0x004d03d0 */
extern undefined4 UINT_008dacd8; /* used by 1 fn(s), first 0x004d03d0 */
extern undefined4 UINT_008dacdc; /* used by 1 fn(s), first 0x004d03d0 */
extern undefined4 UINT_008dace0; /* used by 1 fn(s), first 0x004d03d0 */
extern undefined4 UINT_008dace4; /* used by 1 fn(s), first 0x004d03d0 */
extern undefined4 UINT_008dace8; /* used by 1 fn(s), first 0x004d03d0 */
extern undefined4 UINT_008dacec; /* used by 1 fn(s), first 0x004d03d0 */
extern int * PTR_008dacf0; /* used by 9 fn(s), first 0x004d0300 */
extern undefined4 UINT_008dacf4; /* used by 4 fn(s), first 0x004d0300 */
extern int * PTR_008dacf8; /* used by 4 fn(s), first 0x004d0300 */
extern undefined4 UINT_008dacfc; /* used by 2 fn(s), first 0x004d0300 */
extern uint UINT_008dad40; /* used by 4 fn(s), first 0x004d0550 */
extern uint UINT_008dad44; /* used by 4 fn(s), first 0x004d0550 */
extern undefined4 UINT_008dad48; /* used by 5 fn(s), first 0x004d03d0 */
extern uint UINT_008dad4c; /* used by 4 fn(s), first 0x004d0550 */
extern undefined4 UINT_008dad50; /* used by 1 fn(s), first 0x004d0300 */
extern undefined4 UINT_008dad58; /* used by 3 fn(s), first 0x004d06a0 */
extern undefined4 UINT_008dad5c; /* used by 3 fn(s), first 0x004d0610 */
extern undefined4 UINT_008dad60; /* used by 3 fn(s), first 0x004d0f00 */
extern undefined4 UINT_008dad64; /* used by 3 fn(s), first 0x004d0f00 */
extern undefined DAT_008dad6c; /* used by 5 fn(s), first 0x004d0ad0 */
extern undefined DAT_008dad6d; /* used by 5 fn(s), first 0x004d0b60 */
extern undefined DAT_008dad6e; /* used by 5 fn(s), first 0x004d06a0 */
extern undefined DAT_008dad6f; /* used by 3 fn(s), first 0x004d0cf0 */
extern undefined4 UINT_008dad70; /* used by 4 fn(s), first 0x004d06a0 */
extern undefined4 UINT_008dad74; /* used by 9 fn(s), first 0x004d06a0 */
extern undefined4 UINT_008dad7c; /* used by 3 fn(s), first 0x004d0f00 */
extern undefined4 UINT_008dad80; /* used by 3 fn(s), first 0x004d0f00 */
extern undefined4 UINT_008dad84; /* used by 6 fn(s), first 0x004d06a0 */
extern undefined4 UINT_008dad88; /* used by 2 fn(s), first 0x004d1180 */
extern uint UINT_008db098; /* used by 2 fn(s), first 0x004d0300 */
extern undefined4 UINT_008db09c; /* used by 2 fn(s), first 0x004d0300 */
extern uint UINT_008db0a0; /* used by 2 fn(s), first 0x004d0300 */
extern undefined DAT_008db0e8; /* used by 4 fn(s), first 0x004d0550 */
extern undefined DAT_008db1e8; /* used by 1 fn(s), first 0x004d0300 */
extern undefined4 UINT_008db1ec; /* used by 3 fn(s), first 0x004d0a80 */
extern undefined4 UINT_008db1f0; /* used by 3 fn(s), first 0x004d0550 */
extern undefined4 UINT_008db1f8; /* used by 2 fn(s), first 0x004d1690 */
extern undefined DAT_008db200; /* used by 1 fn(s), first 0x004d2340 */
extern undefined4 UINT_008db208; /* used by 4 fn(s), first 0x004d24b0 */
extern undefined DAT_008db20c; /* used by 1 fn(s), first 0x004d2420 */
extern undefined4 UINT_008db210; /* used by 1 fn(s), first 0x004d2630 */
extern undefined DAT_008db214; /* used by 1 fn(s), first 0x004d2630 */
extern undefined DAT_008db218; /* used by 1 fn(s), first 0x004d2630 */
extern undefined DAT_008db21c; /* used by 1 fn(s), first 0x004d2630 */
extern undefined DAT_008db220; /* used by 1 fn(s), first 0x004d2630 */
extern undefined DAT_008db224; /* used by 1 fn(s), first 0x004d2630 */
extern undefined DAT_008db228; /* used by 1 fn(s), first 0x004d2630 */
extern undefined DAT_008db22c; /* used by 1 fn(s), first 0x004d2630 */
extern undefined4 UINT_008db230; /* used by 1 fn(s), first 0x004d2630 */
extern undefined4 UINT_008db290; /* used by 1 fn(s), first 0x004d2630 */
extern undefined4 UINT_008db310; /* used by 1 fn(s), first 0x004d2630 */
extern undefined4 UINT_008db40c; /* used by 1 fn(s), first 0x004d2630 */
extern uint UINT_008db410; /* used by 2 fn(s), first 0x004d2550 */
extern undefined DAT_008db414; /* used by 1 fn(s), first 0x004d2420 */
extern undefined DAT_008db418; /* used by 1 fn(s), first 0x004d2c60 */
extern int * PTR_008db41c; /* used by 4 fn(s), first 0x004d2420 */
extern uint UINT_008db420; /* used by 3 fn(s), first 0x004d27d0 */
extern int * PTR_008db424; /* used by 5 fn(s), first 0x004d24b0 */
extern undefined4 UINT_008db428; /* used by 1 fn(s), first 0x004d2c60 */
extern undefined DAT_008db42c; /* used by 1 fn(s), first 0x004d2420 */
extern uint UINT_008db430; /* used by 2 fn(s), first 0x004d2420 */
extern undefined4 UINT_008db438; /* used by 1 fn(s), first 0x004d27d0 */
extern undefined DAT_008dcc38; /* used by 1 fn(s), first 0x004d2420 */
extern undefined DAT_008dcc3c; /* used by 1 fn(s), first 0x004d2550 */
extern int * PTR_008dcc40; /* used by 3 fn(s), first 0x004d2940 */
extern int * PTR_008dcc44; /* used by 2 fn(s), first 0x004d2940 */
extern int * PTR_008dcc48; /* used by 5 fn(s), first 0x004d2630 */
extern undefined DAT_008dcc4c; /* used by 1 fn(s), first 0x004d2aa0 */
extern undefined4 UINT_008dcc50; /* used by 2 fn(s), first 0x004d2940 */
extern undefined4 UINT_008dcc54; /* used by 3 fn(s), first 0x004d2550 */
extern undefined4 UINT_008dcc58; /* used by 1 fn(s), first 0x004d2630 */
extern uint UINT_008dcc60; /* used by 2 fn(s), first 0x004d2e80 */
extern undefined4 UINT_008dcc64; /* used by 2 fn(s), first 0x004d2e80 */
extern undefined DAT_008dcc70; /* used by 1 fn(s), first 0x004d2e80 */
extern undefined DAT_008dcc78; /* used by 1 fn(s), first 0x004d3040 */
extern uint UINT_008dcd9c; /* used by 2 fn(s), first 0x004d2e80 */
extern undefined DAT_008dcda0; /* used by 1 fn(s), first 0x004d2e80 */
extern undefined4 UINT_008dcdb8; /* used by 1 fn(s), first 0x004d5ed0 */
extern undefined4 UINT_008dcdbc; /* used by 2 fn(s), first 0x004d5eb0 */
extern undefined DAT_008dcdc0; /* used by 1 fn(s), first 0x004d5ed0 */
extern int * PTR_008dcdc4; /* used by 2 fn(s), first 0x004d5eb0 */
extern undefined DAT_008dcdc8; /* used by 1 fn(s), first 0x004d5f70 */
extern undefined4 UINT_008ddd68; /* used by 1 fn(s), first 0x004d5f70 */
extern undefined4 UINT_008ddd6c; /* used by 1 fn(s), first 0x004d5f70 */
extern undefined DAT_008ddd80; /* used by 1 fn(s), first 0x004012b0 */
extern undefined4 UINT_008ddd84; /* used by 1 fn(s), first 0x00401950 */
extern undefined4 UINT_008ddd88; /* used by 1 fn(s), first 0x004012b0 */
extern undefined4 UINT_008ddd8c; /* used by 1 fn(s), first 0x00401950 */
extern undefined DAT_008ddda0; /* used by 1 fn(s), first 0x004012b0 */
extern undefined DAT_008ddda4; /* used by 1 fn(s), first 0x00401040 */
extern undefined DAT_008ddda8; /* used by 1 fn(s), first 0x00401040 */
extern undefined4 UINT_008dddac; /* used by 2 fn(s), first 0x00401040 */
extern undefined DAT_008dddb0; /* used by 1 fn(s), first 0x00401040 */
extern undefined DAT_008dddb4; /* used by 2 fn(s), first 0x00401040 */
extern undefined DAT_008dde20; /* used by 1 fn(s), first 0x004012b0 */
extern undefined4 UINT_008dde24; /* used by 1 fn(s), first 0x00401950 */
extern undefined4 UINT_008dde28; /* used by 1 fn(s), first 0x004012b0 */
extern undefined4 UINT_008dde2c; /* used by 1 fn(s), first 0x00401950 */
extern uint UINT_008dde40; /* used by 42 fn(s), first 0x00452150 */
extern undefined4 UINT_008dde44; /* used by 30 fn(s), first 0x0042e820 */
extern undefined4 UINT_008dde48; /* used by 78 fn(s), first 0x00430a20 */
extern undefined DAT_008dde4c; /* used by 57 fn(s), first 0x00437e10 */
extern undefined4 UINT_008dde50; /* used by 94 fn(s), first 0x0042d190 */
extern undefined4 UINT_008dde54; /* used by 118 fn(s), first 0x0042d190 */
extern undefined4 UINT_008dde58; /* used by 116 fn(s), first 0x00430a20 */
extern undefined4 UINT_008dde5c; /* used by 100 fn(s), first 0x0042e820 */
extern undefined DAT_008dde60; /* used by 61 fn(s), first 0x0042d5f0 */
extern undefined DAT_008dde64; /* used by 4 fn(s), first 0x0042d5f0 */
extern undefined4 UINT_008dde68; /* used by 6 fn(s), first 0x00430a20 */
extern undefined4 UINT_008dde6c; /* used by 36 fn(s), first 0x0042fa10 */
extern undefined2 DAT_008dde70; /* used by 9 fn(s), first 0x0042dba0 */
extern undefined DAT_008dde74; /* used by 57 fn(s), first 0x00437e10 */
extern undefined4 UINT_008dde78; /* used by 94 fn(s), first 0x0042d190 */
extern undefined4 UINT_008dde7c; /* used by 116 fn(s), first 0x00430a20 */
extern undefined DAT_008dde80; /* used by 61 fn(s), first 0x0042d5f0 */
extern undefined DAT_008dde84; /* used by 4 fn(s), first 0x0042d5f0 */
extern undefined4 UINT_008dde88; /* used by 46 fn(s), first 0x0042d5f0 */
extern undefined4 UINT_008dde8c; /* used by 78 fn(s), first 0x00430a20 */
extern undefined4 UINT_008dde90; /* used by 45 fn(s), first 0x0042e820 */
extern undefined DAT_008dde94; /* used by 57 fn(s), first 0x00437e10 */
extern undefined DAT_008dde98; /* used by 18 fn(s), first 0x0042dba0 */
extern undefined DAT_008dde9c; /* used by 4 fn(s), first 0x0042d5f0 */
extern undefined DAT_008ddea0; /* used by 61 fn(s), first 0x0042d5f0 */
extern undefined4 UINT_008ddea4; /* used by 90 fn(s), first 0x0042e010 */
extern undefined4 UINT_008ddea8; /* used by 45 fn(s), first 0x00419a00 */
extern undefined4 UINT_008ddeac; /* used by 45 fn(s), first 0x00418550 */
extern undefined4 UINT_008ddeb0; /* used by 33 fn(s), first 0x0041a640 */
extern undefined4 UINT_008ddeb4; /* used by 6 fn(s), first 0x0041b310 */
extern undefined2 DAT_008ddeb8; /* used by 9 fn(s), first 0x00418fe0 */
extern undefined4 UINT_008ddebc; /* used by 56 fn(s), first 0x00419a00 */
extern undefined1 DAT_008ddec0; /* used by 16 fn(s), first 0x00418fe0 */
extern undefined DAT_008ddec4; /* used by 4 fn(s), first 0x00418a00 */
extern undefined DAT_008ddec8; /* used by 37 fn(s), first 0x00418a00 */
extern undefined4 UINT_008ddecc; /* used by 68 fn(s), first 0x0041b310 */
extern undefined DAT_008dded0; /* used by 33 fn(s), first 0x00421120 */
extern undefined4 UINT_008dded4; /* used by 30 fn(s), first 0x00419a00 */
extern undefined4 UINT_008dded8; /* used by 68 fn(s), first 0x0041b310 */
extern undefined DAT_008ddedc; /* used by 37 fn(s), first 0x00418a00 */
extern undefined DAT_008ddee0; /* used by 4 fn(s), first 0x00418a00 */
extern undefined4 UINT_008ddee4; /* used by 69 fn(s), first 0x00418550 */
extern int UINT_008ddee8; /* used by 68 fn(s), first 0x0041b310 */
extern undefined DAT_008ddeec; /* used by 33 fn(s), first 0x00421120 */
extern undefined DAT_008ddef0; /* used by 4 fn(s), first 0x00418a00 */
extern undefined DAT_008ddef4; /* used by 37 fn(s), first 0x00418a00 */
extern undefined4 UINT_008ddef8; /* used by 45 fn(s), first 0x00418550 */
extern undefined4 UINT_008ddefc; /* used by 68 fn(s), first 0x0041b310 */
extern undefined DAT_008ddf00; /* used by 33 fn(s), first 0x00421120 */
extern undefined4 UINT_008ddf04; /* used by 39 fn(s), first 0x00410970 */
extern undefined2 DAT_008ddf08; /* used by 3 fn(s), first 0x0040f650 */
extern undefined4 UINT_008ddf0c; /* used by 13 fn(s), first 0x00410330 */
extern undefined4 UINT_008ddf10; /* used by 30 fn(s), first 0x00410970 */
extern undefined4 UINT_008ddf14; /* used by 66 fn(s), first 0x00410970 */
extern undefined4 UINT_008ddf18; /* used by 59 fn(s), first 0x00410970 */
extern undefined DAT_008ddf1c; /* used by 33 fn(s), first 0x00413590 */
extern undefined DAT_008ddf20; /* used by 33 fn(s), first 0x00413590 */
extern undefined4 UINT_008ddf24; /* used by 29 fn(s), first 0x0040fa80 */
extern undefined DAT_008ddf28; /* used by 33 fn(s), first 0x00413590 */
extern undefined DAT_008ddf2c; /* used by 33 fn(s), first 0x00413590 */
extern uint UINT_008ddf30; /* used by 61 fn(s), first 0x00410330 */
extern undefined DAT_008ddf34; /* used by 12 fn(s), first 0x00410970 */
extern undefined DAT_008ddf38; /* used by 33 fn(s), first 0x00413590 */
extern undefined4 UINT_008ddf3c; /* used by 66 fn(s), first 0x00410970 */
extern undefined1 DAT_008ddf40; /* used by 5 fn(s), first 0x0040f650 */
extern undefined4 UINT_008ddf44; /* used by 59 fn(s), first 0x00410970 */
extern undefined DAT_008ddf48; /* used by 33 fn(s), first 0x00413590 */
extern undefined4 UINT_008ddf4c; /* used by 30 fn(s), first 0x00410970 */
extern undefined DAT_008ddf50; /* used by 1 fn(s), first 0x0040a430 */
extern undefined4 UINT_008ddf60; /* used by 1 fn(s), first 0x0040a430 */
extern undefined4 UINT_008ddf84; /* used by 1 fn(s), first 0x0040d230 */
extern undefined4 UINT_008ddf88; /* used by 1 fn(s), first 0x0040d230 */
extern undefined4 UINT_008ddf8c; /* used by 1 fn(s), first 0x0040d230 */
extern undefined DAT_008ddfc0; /* used by 5 fn(s), first 0x00405620 */
extern undefined4 UINT_008ddfdc; /* used by 1 fn(s), first 0x00406860 */
extern undefined4 UINT_008ddfe0; /* used by 2 fn(s), first 0x004066a0 */
extern undefined DAT_008ddfe4; /* used by 1 fn(s), first 0x004066a0 */
extern undefined4 UINT_008ddfe8; /* used by 1 fn(s), first 0x004066a0 */
extern undefined4 UINT_008ddfec; /* used by 1 fn(s), first 0x004066a0 */
extern undefined4 UINT_008ddff0; /* used by 1 fn(s), first 0x004066a0 */
extern undefined4 UINT_008ddff4; /* used by 1 fn(s), first 0x004066a0 */
extern undefined4 UINT_008de00c; /* used by 1 fn(s), first 0x00406860 */
extern undefined DAT_008de014; /* used by 1 fn(s), first 0x00406860 */
extern undefined DAT_008de018; /* used by 1 fn(s), first 0x00406860 */
extern undefined DAT_008de01c; /* used by 1 fn(s), first 0x00406860 */
extern undefined DAT_008de020; /* used by 1 fn(s), first 0x00406860 */
extern undefined DAT_008de024; /* used by 1 fn(s), first 0x00406860 */
extern undefined DAT_008de028; /* used by 1 fn(s), first 0x00406860 */
extern undefined DAT_008de02c; /* used by 1 fn(s), first 0x00406860 */
extern undefined DAT_008de030; /* used by 1 fn(s), first 0x00406860 */
extern undefined DAT_008de034; /* used by 1 fn(s), first 0x00406860 */
extern undefined DAT_008fbfc0; /* used by 100 fn(s), first 0x00404e00 */
extern undefined4 UINT_008fbfc4; /* used by 1 fn(s), first 0x00404b80 */
extern undefined4 UINT_008fdfc0; /* used by 1 fn(s), first 0x00404b80 */
extern undefined4 UINT_008fe000; /* used by 154 fn(s), first 0x00404b80 */
extern undefined4 UINT_008fe004; /* used by 1 fn(s), first 0x00404b80 */
extern undefined4 UINT_00900020; /* used by 2 fn(s), first 0x004041e0 */
extern undefined4 UINT_00900024; /* used by 1 fn(s), first 0x00406aa0 */
extern undefined4 UINT_00900028; /* used by 1 fn(s), first 0x00406aa0 */
extern undefined DAT_0090002c; /* used by 1 fn(s), first 0x00406aa0 */
extern undefined DAT_00900030; /* used by 1 fn(s), first 0x00406aa0 */
extern undefined DAT_00900034; /* used by 1 fn(s), first 0x00406aa0 */
extern undefined DAT_00900044; /* used by 1 fn(s), first 0x00406aa0 */
extern undefined4 UINT_0090004c; /* used by 2 fn(s), first 0x004041e0 */
extern undefined4 UINT_00900054; /* used by 2 fn(s), first 0x004041e0 */
extern undefined DAT_00900068; /* used by 3 fn(s), first 0x0040d230 */
extern undefined4 UINT_00900080; /* used by 2 fn(s), first 0x0047ca00 */
extern undefined DAT_009004a0; /* used by 3 fn(s), first 0x0047c7e0 */
extern undefined DAT_0090051f; /* used by 1 fn(s), first 0x0047c7e0 */
extern uint UINT_00900520; /* used by 12 fn(s), first 0x0040aa20 */
extern undefined2 DAT_00900524; /* used by 1 fn(s), first 0x004733a0 */
extern undefined2 DAT_00900526; /* used by 1 fn(s), first 0x004733a0 */
extern undefined2 DAT_00900528; /* used by 1 fn(s), first 0x004733a0 */
extern undefined2 DAT_0090052a; /* used by 1 fn(s), first 0x004733a0 */
extern undefined DAT_0090052c; /* used by 1 fn(s), first 0x004782e0 */
extern uint UINT_00900530; /* used by 4 fn(s), first 0x00401cc0 */
extern undefined4 UINT_00900534; /* used by 5 fn(s), first 0x00406aa0 */
extern undefined DAT_00900540; /* used by 1 fn(s), first 0x00479cc0 */
extern undefined DAT_00900544; /* used by 1 fn(s), first 0x00479cc0 */
extern undefined DAT_00900548; /* used by 1 fn(s), first 0x00479cc0 */
extern undefined DAT_0090054c; /* used by 1 fn(s), first 0x00479cc0 */
extern undefined DAT_00900550; /* used by 1 fn(s), first 0x00479cc0 */
extern undefined DAT_00900554; /* used by 1 fn(s), first 0x00479cc0 */
extern undefined DAT_00900558; /* used by 1 fn(s), first 0x00479cc0 */
extern undefined DAT_0090055c; /* used by 1 fn(s), first 0x00479cc0 */
extern undefined DAT_00900560; /* used by 1 fn(s), first 0x00479cc0 */
extern undefined DAT_00900564; /* used by 1 fn(s), first 0x00479cc0 */
extern undefined DAT_00900568; /* used by 1 fn(s), first 0x004782e0 */
extern undefined4 UINT_00900580; /* used by 1 fn(s), first 0x00479cc0 */
extern undefined4 UINT_00900584; /* used by 1 fn(s), first 0x00479cc0 */
extern undefined DAT_009005a0; /* used by 1 fn(s), first 0x00479cc0 */
extern undefined DAT_009005a4; /* used by 1 fn(s), first 0x00479cc0 */
extern undefined DAT_009005c0; /* used by 1 fn(s), first 0x00479cc0 */
extern undefined DAT_009005c4; /* used by 1 fn(s), first 0x00479cc0 */
extern undefined DAT_009005e0; /* used by 1 fn(s), first 0x00479cc0 */
extern undefined DAT_009005e4; /* used by 1 fn(s), first 0x00479cc0 */
extern undefined4 UINT_00900600; /* used by 2 fn(s), first 0x00479aa0 */
extern uint UINT_00900604; /* used by 2 fn(s), first 0x00479aa0 */
extern undefined4 UINT_00900608; /* used by 2 fn(s), first 0x00479aa0 */
extern undefined4 UINT_0090060c; /* used by 2 fn(s), first 0x00479aa0 */
extern undefined DAT_00900620; /* used by 2 fn(s), first 0x004782e0 */
extern undefined DAT_00900624; /* used by 1 fn(s), first 0x0047a590 */
extern undefined DAT_00900628; /* used by 1 fn(s), first 0x0047a590 */
extern undefined DAT_0090062c; /* used by 1 fn(s), first 0x0047a590 */
extern undefined DAT_00900630; /* used by 1 fn(s), first 0x0047a590 */
extern undefined DAT_00900634; /* used by 1 fn(s), first 0x0047a590 */
extern undefined DAT_00900638; /* used by 1 fn(s), first 0x0047a590 */
extern undefined DAT_0090063c; /* used by 1 fn(s), first 0x0047a590 */
extern undefined DAT_00900640; /* used by 1 fn(s), first 0x0047a590 */
extern undefined DAT_00900644; /* used by 1 fn(s), first 0x0047a590 */
extern undefined DAT_00900648; /* used by 1 fn(s), first 0x0047a590 */
extern undefined DAT_0090064c; /* used by 1 fn(s), first 0x0047a590 */
extern undefined DAT_00900650; /* used by 1 fn(s), first 0x0047a590 */
extern undefined DAT_00900654; /* used by 1 fn(s), first 0x0047a590 */
extern undefined4 UINT_00900b40; /* used by 3 fn(s), first 0x00401a50 */
extern undefined DAT_00900b44; /* used by 1 fn(s), first 0x0047a3b0 */
extern undefined DAT_00900b48; /* used by 2 fn(s), first 0x004782e0 */
extern undefined DAT_00900b4c; /* used by 1 fn(s), first 0x0047a3b0 */
extern undefined DAT_00900b50; /* used by 1 fn(s), first 0x0047a3b0 */
extern undefined DAT_00900b54; /* used by 1 fn(s), first 0x0047a3b0 */
extern undefined DAT_00900b58; /* used by 1 fn(s), first 0x0047a3b0 */
extern undefined DAT_00900b5c; /* used by 1 fn(s), first 0x0047a3b0 */
extern undefined DAT_00900b64; /* used by 1 fn(s), first 0x0047a3b0 */
extern undefined DAT_00900b68; /* used by 1 fn(s), first 0x0047a3b0 */
extern undefined DAT_00900b6c; /* used by 1 fn(s), first 0x0047a3b0 */
extern undefined DAT_00900b70; /* used by 1 fn(s), first 0x0047a3b0 */
extern undefined DAT_00900b74; /* used by 1 fn(s), first 0x0047a3b0 */
extern undefined DAT_00900b78; /* used by 1 fn(s), first 0x0047a3b0 */
extern undefined DAT_00900b7c; /* used by 1 fn(s), first 0x0047a3b0 */
extern undefined DAT_00900b80; /* used by 1 fn(s), first 0x0047a3b0 */
extern undefined DAT_00900b84; /* used by 1 fn(s), first 0x0047a3b0 */
extern undefined DAT_00900c07; /* used by 1 fn(s), first 0x0047a3b0 */
extern undefined DAT_00900c87; /* used by 1 fn(s), first 0x0047a3b0 */
extern undefined DAT_00900c98; /* used by 1 fn(s), first 0x0047a3b0 */
extern undefined DAT_00900d00; /* used by 1 fn(s), first 0x0047a3b0 */
extern undefined DAT_00900d10; /* used by 1 fn(s), first 0x0047a3b0 */
extern undefined DAT_00900d14; /* used by 1 fn(s), first 0x0047a3b0 */
extern undefined DAT_00900d1c; /* used by 1 fn(s), first 0x0047a3b0 */
extern undefined DAT_00900d2c; /* used by 1 fn(s), first 0x0047a3b0 */
extern undefined DAT_00900d30; /* used by 1 fn(s), first 0x0047a3b0 */
extern undefined DAT_00900d34; /* used by 1 fn(s), first 0x0047a3b0 */
extern undefined DAT_00900d38; /* used by 1 fn(s), first 0x0047a3b0 */
extern undefined DAT_00900d3c; /* used by 1 fn(s), first 0x0047a3b0 */
extern undefined DAT_00900d40; /* used by 1 fn(s), first 0x0047a3b0 */
extern undefined DAT_00900d44; /* used by 1 fn(s), first 0x0047a3b0 */
extern undefined DAT_00900d48; /* used by 1 fn(s), first 0x0047a3b0 */
extern undefined DAT_00901400; /* used by 1 fn(s), first 0x004025b0 */
extern undefined DAT_00901408; /* used by 1 fn(s), first 0x0047a240 */
extern undefined DAT_0090140c; /* used by 1 fn(s), first 0x0047a240 */
extern undefined DAT_00901458; /* used by 1 fn(s), first 0x0047a240 */
extern undefined DAT_0090145c; /* used by 1 fn(s), first 0x0047a240 */
extern int * PTR_00901464; /* used by 3 fn(s), first 0x00478660 */
extern undefined4 UINT_0090146c; /* used by 1 fn(s), first 0x0047a240 */
extern undefined DAT_009014d8; /* used by 1 fn(s), first 0x004782e0 */
extern undefined4 UINT_009014e0; /* used by 1 fn(s), first 0x00477390 */
extern undefined DAT_009014e4; /* used by 1 fn(s), first 0x00477390 */
extern undefined4 UINT_009014e8; /* used by 2 fn(s), first 0x00477390 */
extern undefined DAT_009014ec; /* used by 1 fn(s), first 0x00477390 */
extern undefined4 UINT_00901500; /* used by 5 fn(s), first 0x00476f10 */
extern undefined4 UINT_00901504; /* used by 1 fn(s), first 0x00477e70 */
extern undefined DAT_00901508; /* used by 1 fn(s), first 0x00477e70 */
extern undefined DAT_0090150c; /* used by 2 fn(s), first 0x00477160 */
extern undefined DAT_00901510; /* used by 2 fn(s), first 0x00477160 */
extern undefined DAT_00901514; /* used by 2 fn(s), first 0x00477160 */
extern undefined4 UINT_00901668; /* used by 2 fn(s), first 0x00477040 */
extern undefined DAT_0090166c; /* used by 1 fn(s), first 0x00477390 */
extern undefined DAT_00901684; /* used by 2 fn(s), first 0x00474140 */
extern undefined DAT_00901688; /* used by 2 fn(s), first 0x00474140 */
extern undefined DAT_0090168c; /* used by 2 fn(s), first 0x00474140 */
extern undefined4 UINT_00901698; /* used by 2 fn(s), first 0x004767d0 */
extern undefined DAT_0090169c; /* used by 1 fn(s), first 0x004767d0 */
extern undefined4 UINT_009016ac; /* used by 1 fn(s), first 0x004892a0 */
extern undefined DAT_009016d8; /* used by 2 fn(s), first 0x00474140 */
extern undefined4 UINT_009016dc; /* used by 4 fn(s), first 0x00474140 */
extern undefined4 UINT_009016e4; /* used by 1 fn(s), first 0x004767d0 */
extern undefined4 UINT_009016ec; /* used by 1 fn(s), first 0x004767d0 */
extern uint UINT_00901758; /* used by 5 fn(s), first 0x00401cc0 */
extern undefined DAT_0090175c; /* used by 1 fn(s), first 0x00474140 */
extern undefined4 UINT_00901760; /* used by 6 fn(s), first 0x00401a50 */
extern undefined DAT_00901764; /* used by 2 fn(s), first 0x00476390 */
extern undefined DAT_00901768; /* used by 2 fn(s), first 0x00476390 */
extern undefined DAT_0090176c; /* used by 2 fn(s), first 0x00476390 */
extern undefined DAT_00901770; /* used by 2 fn(s), first 0x00476390 */
extern undefined DAT_00901774; /* used by 2 fn(s), first 0x00476390 */
extern undefined DAT_00901778; /* used by 2 fn(s), first 0x00476390 */
extern undefined DAT_0090177c; /* used by 2 fn(s), first 0x00476390 */
extern undefined DAT_00901780; /* used by 2 fn(s), first 0x00476390 */
extern undefined DAT_00901784; /* used by 2 fn(s), first 0x00476390 */
extern undefined DAT_00901788; /* used by 2 fn(s), first 0x00476390 */
extern undefined DAT_0090178c; /* used by 2 fn(s), first 0x00476390 */
extern undefined DAT_00901790; /* used by 2 fn(s), first 0x00476390 */
extern undefined DAT_00901794; /* used by 2 fn(s), first 0x00476390 */
extern undefined DAT_00901798; /* used by 2 fn(s), first 0x00476390 */
extern undefined DAT_0090179c; /* used by 2 fn(s), first 0x00476390 */
extern undefined DAT_009017a0; /* used by 2 fn(s), first 0x00476390 */
extern undefined DAT_009017a4; /* used by 2 fn(s), first 0x00476390 */
extern undefined DAT_009017b4; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009017b8; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009017bc; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009017c0; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009017c4; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009017c8; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009017cc; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009017d0; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009017d4; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009017d8; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009017dc; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009017e0; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901808; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_0090180c; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901810; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901814; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901818; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_0090181c; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901820; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901824; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901828; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_0090182c; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901830; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901834; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_0090185c; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901860; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901864; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901868; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_0090186c; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901870; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901874; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901878; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_0090187c; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901880; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901884; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901888; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009018b0; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009018b4; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009018b8; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009018bc; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009018c0; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009018c4; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009018c8; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009018cc; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009018d0; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009018d4; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009018d8; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009018dc; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901904; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901908; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_0090190c; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901910; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901914; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901918; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_0090191c; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901920; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901924; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901928; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_0090192c; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901930; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901958; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_0090195c; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901960; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901964; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901968; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_0090196c; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901970; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901974; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901978; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_0090197c; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901980; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901984; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009019ac; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009019b0; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009019b4; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009019b8; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009019bc; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009019c0; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009019c4; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009019c8; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009019cc; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009019d0; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009019d4; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009019d8; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009019dc; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009019e0; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009019e4; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009019e8; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009019ec; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_009019f0; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a00; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a04; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a08; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a0c; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a10; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a14; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a18; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a1c; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a20; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a24; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a28; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a2c; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a30; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a34; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a38; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a3c; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a40; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a44; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a54; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a58; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a5c; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a60; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a64; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a68; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a6c; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a70; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a74; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a78; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a7c; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a80; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a84; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a88; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a8c; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a90; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a94; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00901a98; /* used by 1 fn(s), first 0x00473c80 */
extern undefined DAT_00902c60; /* used by 3 fn(s), first 0x00473a40 */
extern undefined DAT_00902cdf; /* used by 2 fn(s), first 0x00473a40 */
extern undefined DAT_00902ce0; /* used by 3 fn(s), first 0x00401fb0 */
extern undefined DAT_00902d5f; /* used by 2 fn(s), first 0x00473a40 */
extern undefined4 UINT_00902d60; /* used by 4 fn(s), first 0x00473a40 */
extern undefined4 UINT_00902d64; /* used by 2 fn(s), first 0x00473a40 */
extern undefined4 UINT_00902d68; /* used by 3 fn(s), first 0x00401e90 */
extern undefined4 UINT_00902d6c; /* used by 3 fn(s), first 0x00401e90 */
extern undefined4 UINT_00902d70; /* used by 3 fn(s), first 0x004025b0 */
extern undefined4 UINT_00902d74; /* used by 2 fn(s), first 0x00473a40 */
extern undefined4 UINT_00902d78; /* used by 2 fn(s), first 0x00473a40 */
extern undefined DAT_00902ee8; /* used by 2 fn(s), first 0x004029b0 */
extern undefined DAT_00902eec; /* used by 1 fn(s), first 0x004761b0 */
extern undefined DAT_00902ef0; /* used by 1 fn(s), first 0x004761b0 */
extern undefined DAT_00902ef4; /* used by 1 fn(s), first 0x004761b0 */
extern undefined DAT_009055e4; /* used by 1 fn(s), first 0x004767d0 */
extern undefined DAT_009055e8; /* used by 2 fn(s), first 0x00474140 */
extern undefined4 UINT_009055ec; /* used by 3 fn(s), first 0x00474140 */
extern undefined4 UINT_009055f0; /* used by 1 fn(s), first 0x00484030 */
extern uint UINT_009055f8; /* used by 4 fn(s), first 0x004767d0 */
extern undefined DAT_009055fc; /* used by 1 fn(s), first 0x004767d0 */
extern undefined DAT_00905600; /* used by 1 fn(s), first 0x00484030 */
extern undefined4 UINT_00905604; /* used by 1 fn(s), first 0x00484030 */
extern undefined DAT_00905614; /* used by 1 fn(s), first 0x004870e0 */
extern undefined4 UINT_00905618; /* used by 1 fn(s), first 0x004870e0 */
extern undefined4 UINT_0090561c; /* used by 1 fn(s), first 0x004870e0 */
extern undefined DAT_00905638; /* used by 2 fn(s), first 0x00474140 */
extern uint UINT_0090563c; /* used by 7 fn(s), first 0x00474140 */
extern int * PTR_00905644; /* used by 3 fn(s), first 0x004767d0 */
extern undefined4 UINT_00905648; /* used by 1 fn(s), first 0x00476bc0 */
extern undefined4 UINT_0090564c; /* used by 1 fn(s), first 0x004767d0 */
extern undefined DAT_009056c0; /* used by 3 fn(s), first 0x004016a0 */
extern undefined4 UINT_00905ac4; /* used by 4 fn(s), first 0x004aeb70 */
extern undefined4 UINT_00906ae0; /* used by 4 fn(s), first 0x004aeb70 */
extern undefined4 UINT_00906ae4; /* used by 8 fn(s), first 0x004acfe0 */
extern int * PTR_00906b00; /* used by 28 fn(s), first 0x004ad7a0 */
extern undefined4 UINT_00906b04; /* used by 1 fn(s), first 0x004b19f0 */
extern undefined4 UINT_00906c00; /* used by 12 fn(s), first 0x004b19f0 */
extern undefined DAT_00906c04; /* used by 2 fn(s), first 0x004b14e0 */
extern undefined4 UINT_00906c08; /* used by 8 fn(s), first 0x004ac550 */
extern undefined DAT_00906c0c; /* used by 1 fn(s), first 0x004ac550 */
extern undefined4 UINT_00906c18; /* used by 2 fn(s), first 0x004aca30 */
extern int * PTR_00906c1c; /* used by 2 fn(s), first 0x004c2be0 */
extern undefined4 UINT_00906c20; /* used by 2 fn(s), first 0x004c2be0 */
extern int * PTR_00906c24; /* used by 4 fn(s), first 0x004c2b50 */
extern undefined4 UINT_00906c28; /* used by 3 fn(s), first 0x004c2be0 */
extern undefined4 UINT_00906c2c; /* used by 3 fn(s), first 0x004c2be0 */
extern int * PTR_00906c30; /* used by 4 fn(s), first 0x004c1ff0 */
extern int * PTR_00906c34; /* used by 8 fn(s), first 0x004c1ff0 */
extern int * PTR_00906c38; /* used by 10 fn(s), first 0x004c1ff0 */
extern int * PTR_00906c3c; /* used by 4 fn(s), first 0x004c1ff0 */
extern int * PTR_00906c40; /* used by 6 fn(s), first 0x004c1f40 */
extern int * PTR_00906c44; /* used by 19 fn(s), first 0x004c3e60 */
extern undefined4 UINT_00906c48; /* used by 1 fn(s), first 0x004cd550 */
extern uint UINT_00906c4c; /* used by 4 fn(s), first 0x004cd550 */
extern undefined DAT_00906c50; /* used by 2 fn(s), first 0x004cd550 */
extern undefined4 UINT_00906c54; /* used by 4 fn(s), first 0x004cd550 */
extern undefined DAT_00906c58; /* used by 4 fn(s), first 0x004cd550 */
extern undefined DAT_00906c5c; /* used by 1 fn(s), first 0x004cd550 */
extern undefined DAT_00906c5d; /* used by 1 fn(s), first 0x004cd550 */
extern undefined DAT_00906c60; /* used by 1 fn(s), first 0x004cd550 */
extern undefined DAT_00906c64; /* used by 1 fn(s), first 0x004cd550 */
extern uint UINT_00906c68; /* used by 4 fn(s), first 0x004cd550 */
extern uint UINT_00906c6c; /* used by 4 fn(s), first 0x004cd550 */
extern undefined DAT_00906c70; /* used by 2 fn(s), first 0x004cd550 */
extern undefined4 UINT_00906c74; /* used by 2 fn(s), first 0x004cc410 */
extern undefined2 DAT_00906c80; /* used by 1 fn(s), first 0x004ccd00 */
extern undefined DAT_00906d80; /* used by 1 fn(s), first 0x004cc7d0 */
extern undefined DAT_00906dc0; /* used by 1 fn(s), first 0x004cc7d0 */
extern undefined DAT_00906e00; /* used by 2 fn(s), first 0x004cc6a0 */
extern undefined DAT_00906e01; /* used by 1 fn(s), first 0x004cc7d0 */
extern undefined4 UINT_0091f080; /* used by 2 fn(s), first 0x004cc410 */
extern undefined2 DAT_0091f0a0; /* used by 1 fn(s), first 0x004ccd00 */
extern undefined DAT_0091f0e0; /* used by 1 fn(s), first 0x004cc7d0 */
extern undefined DAT_0091f0f0; /* used by 1 fn(s), first 0x004cc7d0 */
extern undefined DAT_0091f100; /* used by 2 fn(s), first 0x004cc6a0 */
extern undefined DAT_0091f101; /* used by 1 fn(s), first 0x004cc7d0 */
extern undefined2 DAT_009270a0; /* used by 2 fn(s), first 0x004cc6a0 */
extern undefined DAT_009272a0; /* used by 1 fn(s), first 0x004cedc0 */
extern undefined4 in_stack_fffffed0; /* used by 1 fn(s), first 0x004917e0 */
extern undefined4 in_stack_ffffffd8; /* used by 1 fn(s), first 0x004b9b1c */
extern undefined4 in_stack_ffffffdc; /* used by 1 fn(s), first 0x004b9b1c */
extern undefined4 in_stack_ffffffe0; /* used by 1 fn(s), first 0x004b9b1c */
extern undefined4 in_stack_ffffffe2; /* used by 1 fn(s), first 0x004b9b1c */
extern undefined4 in_stack_ffffffe8; /* used by 2 fn(s), first 0x0040dc30 */

/* ---- re-typed views of the symbols above ---- */
#define _DAT_004dd34c (*(undefined4 *)&DAT_004dd34c) /* same address as DAT_004dd34c, other width */
#define _DAT_004dd384 (*(undefined4 *)&DAT_004dd384) /* same address as DAT_004dd384, other width */
#define _DAT_004dda90 (*(undefined4 *)&DAT_004dda90) /* same address as DAT_004dda90, other width */
#define _DAT_004dda94 (*(undefined4 *)&DAT_004dda94) /* same address as DAT_004dda94, other width */
#define _DAT_004dda98 (*(undefined4 *)&DAT_004dda98) /* same address as DAT_004dda98, other width */
#define _DAT_004ddb30 (*(undefined4 *)&DAT_004ddb30) /* same address as DAT_004ddb30, other width */
#define _DAT_004ddb70 (*(undefined4 *)&DAT_004ddb70) /* same address as DAT_004ddb70, other width */
#define _DAT_004ddb74 (*(undefined4 *)&DAT_004ddb74) /* same address as DAT_004ddb74, other width */
#define _DAT_004ddb78 (*(undefined4 *)&DAT_004ddb78) /* same address as DAT_004ddb78, other width */
#define _DAT_004dea44 (*(float *)&DAT_004dea44) /* same address as DAT_004dea44, other width */
#define _DAT_004dea48 (*(undefined4 *)&DAT_004dea48) /* same address as DAT_004dea48, other width */
#define _DAT_004dee54 (*(int *)&DAT_004dee54) /* same address as DAT_004dee54, other width */
#define _DAT_004ed534 (*(undefined4 *)&DAT_004ed534) /* same address as DAT_004ed534, other width */
#define _DAT_004efba0 (*(undefined4 *)&DAT_004efba0) /* same address as DAT_004efba0, other width */
#define _DAT_004efc00 (*(undefined4 *)&DAT_004efc00) /* same address as DAT_004efc00, other width */
#define _DAT_004f04f4 (*(undefined4 *)&DAT_004f04f4) /* same address as DAT_004f04f4, other width */
#define _DAT_004f050c (*(undefined4 *)&DAT_004f050c) /* same address as DAT_004f050c, other width */
#define _DAT_004f0d18 (*(float *)&DAT_004f0d18) /* same address as DAT_004f0d18, other width */
#define _DAT_004f0d1c (*(float *)&DAT_004f0d1c) /* same address as DAT_004f0d1c, other width */
#define _DAT_004f3c2c (*(undefined4 *)&DAT_004f3c2c) /* same address as DAT_004f3c2c, other width */
#define _DAT_004f44f0 (*(undefined4 *)&DAT_004f44f0) /* same address as DAT_004f44f0, other width */
#define _DAT_004f450c (*(undefined4 *)&DAT_004f450c) /* same address as DAT_004f450c, other width */
#define _DAT_004f4d40 (*(undefined4 *)&DAT_004f4d40) /* same address as DAT_004f4d40, other width */
#define _DAT_004f4d44 (*(undefined4 *)&DAT_004f4d44) /* same address as DAT_004f4d44, other width */
#define _DAT_004f5a00 (*(undefined4 *)&DAT_004f5a00) /* same address as DAT_004f5a00, other width */
#define _DAT_004f5a60 (*(undefined4 *)&DAT_004f5a60) /* same address as DAT_004f5a60, other width */
#define _DAT_004f5a7c (*(code * *)&DAT_004f5a7c) /* same address as DAT_004f5a7c, other width */
#define _DAT_004f5a80 (*(undefined4 *)&DAT_004f5a80) /* same address as DAT_004f5a80, other width */
#define _DAT_004f5ea8 (*(undefined4 *)&DAT_004f5ea8) /* same address as DAT_004f5ea8, other width */
#define _DAT_004f6ef8 (*(undefined4 *)&DAT_004f6ef8) /* same address as DAT_004f6ef8, other width */
#define _DAT_004f6f1c (*(undefined4 *)&DAT_004f6f1c) /* same address as DAT_004f6f1c, other width */
#define _DAT_005e6f68 (*(undefined4 *)&DAT_005e6f68) /* same address as DAT_005e6f68, other width */
#define _DAT_005e6f8c (*(undefined4 *)&DAT_005e6f8c) /* same address as DAT_005e6f8c, other width */
#define _DAT_005e6f90 (*(undefined4 *)&DAT_005e6f90) /* same address as DAT_005e6f90, other width */
#define _DAT_007f0fb8 (*(undefined4 *)&DAT_007f0fb8) /* same address as DAT_007f0fb8, other width */
#define _DAT_007f0fd8 (*(undefined4 *)&DAT_007f0fd8) /* same address as DAT_007f0fd8, other width */
#define _DAT_007f0fdc (*(undefined4 *)&DAT_007f0fdc) /* same address as DAT_007f0fdc, other width */
#define _DAT_007f0fe0 (*(undefined4 *)&DAT_007f0fe0) /* same address as DAT_007f0fe0, other width */
#define _DAT_007f30a8 (*(undefined4 *)&DAT_007f30a8) /* same address as DAT_007f30a8, other width */
#define _DAT_007f30ac (*(undefined4 *)&DAT_007f30ac) /* same address as DAT_007f30ac, other width */
#define _DAT_007f30b0 (*(undefined4 *)&DAT_007f30b0) /* same address as DAT_007f30b0, other width */
#define _DAT_007f30b4 (*(undefined4 *)&DAT_007f30b4) /* same address as DAT_007f30b4, other width */
#define _DAT_007f30b8 (*(undefined4 *)&DAT_007f30b8) /* same address as DAT_007f30b8, other width */
#define _DAT_007f30bc (*(undefined4 *)&DAT_007f30bc) /* same address as DAT_007f30bc, other width */
#define _DAT_007f30c0 (*(undefined4 *)&DAT_007f30c0) /* same address as DAT_007f30c0, other width */
#define _DAT_007f3200 (*(undefined4 *)&DAT_007f3200) /* same address as DAT_007f3200, other width */
#define _DAT_007f3208 (*(undefined4 *)&DAT_007f3208) /* same address as DAT_007f3208, other width */
#define _DAT_007f320c (*(undefined4 *)&DAT_007f320c) /* same address as DAT_007f320c, other width */
#define _DAT_007f3210 (*(undefined4 *)&DAT_007f3210) /* same address as DAT_007f3210, other width */
#define _DAT_007f4240 (*(undefined4 *)&DAT_007f4240) /* same address as DAT_007f4240, other width */
#define _DAT_007f4248 (*(undefined4 *)&DAT_007f4248) /* same address as DAT_007f4248, other width */
#define _DAT_007f4258 (*(undefined4 *)&DAT_007f4258) /* same address as DAT_007f4258, other width */
#define _DAT_007f42e0 (*(float *)&DAT_007f42e0) /* same address as DAT_007f42e0, other width */
#define _DAT_007f42e4 (*(undefined4 *)&DAT_007f42e4) /* same address as DAT_007f42e4, other width */
#define _DAT_007f42f0 (*(undefined4 *)&DAT_007f42f0) /* same address as DAT_007f42f0, other width */
#define _DAT_007f42f4 (*(float *)&DAT_007f42f4) /* same address as DAT_007f42f4, other width */
#define _DAT_007f43a0 (*(float *)&DAT_007f43a0) /* same address as DAT_007f43a0, other width */
#define _DAT_007f43a4 (*(float *)&DAT_007f43a4) /* same address as DAT_007f43a4, other width */
#define _DAT_007f43c0 (*(float *)&DAT_007f43c0) /* same address as DAT_007f43c0, other width */
#define _DAT_007f43c4 (*(float *)&DAT_007f43c4) /* same address as DAT_007f43c4, other width */
#define _DAT_007f4448 (*(undefined4 *)&DAT_007f4448) /* same address as DAT_007f4448, other width */
#define _DAT_007f444c (*(undefined4 *)&DAT_007f444c) /* same address as DAT_007f444c, other width */
#define _DAT_007f4ac8 (*(undefined4 *)&DAT_007f4ac8) /* same address as DAT_007f4ac8, other width */
#define _DAT_007f4ad4 (*(undefined4 *)&DAT_007f4ad4) /* same address as DAT_007f4ad4, other width */
#define _DAT_007f4ae4 (*(undefined4 *)&DAT_007f4ae4) /* same address as DAT_007f4ae4, other width */
#define _DAT_007f4aec (*(float *)&DAT_007f4aec) /* same address as DAT_007f4aec, other width */
#define _DAT_007f4af0 (*(undefined4 *)&DAT_007f4af0) /* same address as DAT_007f4af0, other width */
#define _DAT_007f4af4 (*(undefined4 *)&DAT_007f4af4) /* same address as DAT_007f4af4, other width */
#define _DAT_007f4af8 (*(float *)&DAT_007f4af8) /* same address as DAT_007f4af8, other width */
#define _DAT_007f4b34 (*(float *)&DAT_007f4b34) /* same address as DAT_007f4b34, other width */
#define _DAT_007f4b38 (*(float *)&DAT_007f4b38) /* same address as DAT_007f4b38, other width */
#define _DAT_007f4b58 (*(float *)&DAT_007f4b58) /* same address as DAT_007f4b58, other width */
#define _DAT_007f4b5c (*(float *)&DAT_007f4b5c) /* same address as DAT_007f4b5c, other width */
#define _DAT_007f4b60 (*(undefined4 *)&DAT_007f4b60) /* same address as DAT_007f4b60, other width */
#define _DAT_007f4b64 (*(undefined4 *)&DAT_007f4b64) /* same address as DAT_007f4b64, other width */
#define _DAT_007f4e80 (*(undefined4 *)&DAT_007f4e80) /* same address as DAT_007f4e80, other width */
#define _DAT_007f4e84 (*(undefined4 *)&DAT_007f4e84) /* same address as DAT_007f4e84, other width */
#define _DAT_007f4e88 (*(undefined4 *)&DAT_007f4e88) /* same address as DAT_007f4e88, other width */
#define _DAT_007f4e8c (*(undefined4 *)&DAT_007f4e8c) /* same address as DAT_007f4e8c, other width */
#define _DAT_007f4e90 (*(undefined4 *)&DAT_007f4e90) /* same address as DAT_007f4e90, other width */
#define _DAT_007f4e94 (*(undefined4 *)&DAT_007f4e94) /* same address as DAT_007f4e94, other width */
#define _DAT_007f4e98 (*(undefined4 *)&DAT_007f4e98) /* same address as DAT_007f4e98, other width */
#define _DAT_007f4e9c (*(undefined4 *)&DAT_007f4e9c) /* same address as DAT_007f4e9c, other width */
#define _DAT_007f4ea0 (*(undefined4 *)&DAT_007f4ea0) /* same address as DAT_007f4ea0, other width */
#define _DAT_007f4ea4 (*(undefined4 *)&DAT_007f4ea4) /* same address as DAT_007f4ea4, other width */
#define _DAT_007f4ea8 (*(undefined4 *)&DAT_007f4ea8) /* same address as DAT_007f4ea8, other width */
#define _DAT_007f4eac (*(undefined4 *)&DAT_007f4eac) /* same address as DAT_007f4eac, other width */
#define _DAT_007f5000 (*(undefined4 *)&DAT_007f5000) /* same address as DAT_007f5000, other width */
#define _DAT_007f5004 (*(undefined4 *)&DAT_007f5004) /* same address as DAT_007f5004, other width */
#define _DAT_007f5008 (*(undefined4 *)&DAT_007f5008) /* same address as DAT_007f5008, other width */
#define _DAT_007f500c (*(undefined4 *)&DAT_007f500c) /* same address as DAT_007f500c, other width */
#define _DAT_007f5010 (*(undefined4 *)&DAT_007f5010) /* same address as DAT_007f5010, other width */
#define _DAT_007f5014 (*(undefined4 *)&DAT_007f5014) /* same address as DAT_007f5014, other width */
#define _DAT_007f5018 (*(undefined4 *)&DAT_007f5018) /* same address as DAT_007f5018, other width */
#define _DAT_007f501c (*(undefined4 *)&DAT_007f501c) /* same address as DAT_007f501c, other width */
#define _DAT_007f5020 (*(undefined4 *)&DAT_007f5020) /* same address as DAT_007f5020, other width */
#define _DAT_007f5024 (*(undefined4 *)&DAT_007f5024) /* same address as DAT_007f5024, other width */
#define _DAT_007f5028 (*(undefined4 *)&DAT_007f5028) /* same address as DAT_007f5028, other width */
#define _DAT_007f502c (*(undefined4 *)&DAT_007f502c) /* same address as DAT_007f502c, other width */
#define _DAT_007f5f08 (*(undefined4 *)&DAT_007f5f08) /* same address as DAT_007f5f08, other width */
#define _DAT_007f5f0c (*(undefined4 *)&DAT_007f5f0c) /* same address as DAT_007f5f0c, other width */
#define _DAT_007f5f10 (*(undefined4 *)&DAT_007f5f10) /* same address as DAT_007f5f10, other width */
#define _DAT_007f5f14 (*(undefined4 *)&DAT_007f5f14) /* same address as DAT_007f5f14, other width */
#define _DAT_007f5f18 (*(undefined4 *)&DAT_007f5f18) /* same address as DAT_007f5f18, other width */
#define _DAT_007f5f1c (*(undefined4 *)&DAT_007f5f1c) /* same address as DAT_007f5f1c, other width */
#define _DAT_007f5f20 (*(undefined4 *)&DAT_007f5f20) /* same address as DAT_007f5f20, other width */
#define _DAT_007f5f24 (*(undefined4 *)&DAT_007f5f24) /* same address as DAT_007f5f24, other width */
#define _DAT_007f5f28 (*(undefined4 *)&DAT_007f5f28) /* same address as DAT_007f5f28, other width */
#define _DAT_007f5f2c (*(undefined4 *)&DAT_007f5f2c) /* same address as DAT_007f5f2c, other width */
#define _DAT_007f5f30 (*(undefined4 *)&DAT_007f5f30) /* same address as DAT_007f5f30, other width */
#define _DAT_007f5f34 (*(undefined4 *)&DAT_007f5f34) /* same address as DAT_007f5f34, other width */
#define _DAT_007f6490 (*(undefined4 *)&DAT_007f6490) /* same address as DAT_007f6490, other width */
#define _DAT_007feac8 (*(undefined4 *)&DAT_007feac8) /* same address as DAT_007feac8, other width */
#define _DAT_007feacc (*(undefined4 *)&DAT_007feacc) /* same address as DAT_007feacc, other width */
#define _DAT_007fead0 (*(undefined4 *)&DAT_007fead0) /* same address as DAT_007fead0, other width */
#define _DAT_007fead4 (*(undefined4 *)&DAT_007fead4) /* same address as DAT_007fead4, other width */
#define _DAT_007feb54 (*(int *)&DAT_007feb54) /* same address as DAT_007feb54, other width */
#define _DAT_007feb58 (*(undefined4 *)&DAT_007feb58) /* same address as DAT_007feb58, other width */
#define _DAT_00803f80 (*(undefined4 *)&DAT_00803f80) /* same address as DAT_00803f80, other width */
#define _DAT_00803fcc (*(undefined4 *)&DAT_00803fcc) /* same address as DAT_00803fcc, other width */
#define _DAT_00804000 (*(undefined4 *)&DAT_00804000) /* same address as DAT_00804000, other width */
#define _DAT_00804004 (*(undefined4 *)&DAT_00804004) /* same address as DAT_00804004, other width */
#define _DAT_00804008 (*(undefined4 *)&DAT_00804008) /* same address as DAT_00804008, other width */
#define _DAT_00804014 (*(undefined4 *)&DAT_00804014) /* same address as DAT_00804014, other width */
#define _DAT_008063f0 (*(undefined4 *)&DAT_008063f0) /* same address as DAT_008063f0, other width */
#define _DAT_008063f4 (*(undefined4 *)&DAT_008063f4) /* same address as DAT_008063f4, other width */
#define _DAT_008063f8 (*(undefined4 *)&DAT_008063f8) /* same address as DAT_008063f8, other width */
#define _DAT_008063fc (*(undefined4 *)&DAT_008063fc) /* same address as DAT_008063fc, other width */
#define _DAT_00806958 (*(undefined4 *)&DAT_00806958) /* same address as DAT_00806958, other width */
#define _DAT_0080cbe0 (*(uint *)&DAT_0080cbe0) /* same address as DAT_0080cbe0, other width */
#define _DAT_0080cbe8 (*(undefined2 *)&DAT_0080cbe8) /* same address as DAT_0080cbe8, other width */
#define _DAT_0080cbec (*(undefined2 *)&DAT_0080cbec) /* same address as DAT_0080cbec, other width */
#define _DAT_00811b24 (*(undefined2 *)&DAT_00811b24) /* same address as DAT_00811b24, other width */
#define _DAT_00811b2c (*(undefined2 *)&DAT_00811b2c) /* same address as DAT_00811b2c, other width */
#define _DAT_00812ebc (*(undefined2 *)&DAT_00812ebc) /* same address as DAT_00812ebc, other width */
#define _DAT_00812ec4 (*(undefined4 *)&DAT_00812ec4) /* same address as DAT_00812ec4, other width */
#define _DAT_00812ec8 (*(undefined *)&DAT_00812ec8) /* same address as DAT_00812ec8, other width */
#define _DAT_008155f8 (*(undefined2 *)&DAT_008155f8) /* same address as DAT_008155f8, other width */
#define _DAT_00815608 (*(undefined *)&DAT_00815608) /* same address as DAT_00815608, other width */
#define _DAT_008a92a8 (*(undefined4 *)&DAT_008a92a8) /* same address as DAT_008a92a8, other width */
#define _DAT_008a92ac (*(undefined4 *)&DAT_008a92ac) /* same address as DAT_008a92ac, other width */
#define _DAT_008a92b0 (*(undefined4 *)&DAT_008a92b0) /* same address as DAT_008a92b0, other width */
#define _DAT_008a92b4 (*(undefined4 *)&DAT_008a92b4) /* same address as DAT_008a92b4, other width */
#define _DAT_008a92b8 (*(undefined4 *)&DAT_008a92b8) /* same address as DAT_008a92b8, other width */
#define _DAT_008a92bc (*(undefined4 *)&DAT_008a92bc) /* same address as DAT_008a92bc, other width */
#define _DAT_008a92c0 (*(undefined4 *)&DAT_008a92c0) /* same address as DAT_008a92c0, other width */
#define _DAT_008a92c4 (*(undefined4 *)&DAT_008a92c4) /* same address as DAT_008a92c4, other width */
#define _DAT_008a94c4 (*(undefined4 *)&DAT_008a94c4) /* same address as DAT_008a94c4, other width */
#define _DAT_008a94cc (*(undefined4 *)&DAT_008a94cc) /* same address as DAT_008a94cc, other width */
#define _DAT_008c9790 (*(undefined4 *)&DAT_008c9790) /* same address as DAT_008c9790, other width */
#define _DAT_008c97d8 (*(undefined2 *)&DAT_008c97d8) /* same address as DAT_008c97d8, other width */
#define _DAT_008c97da (*(undefined2 *)&DAT_008c97da) /* same address as DAT_008c97da, other width */
#define _DAT_008c97dc (*(undefined2 *)&DAT_008c97dc) /* same address as DAT_008c97dc, other width */
#define _DAT_008c97de (*(undefined2 *)&DAT_008c97de) /* same address as DAT_008c97de, other width */
#define _DAT_008c9848 (*(int *)&DAT_008c9848) /* same address as DAT_008c9848, other width */
#define _DAT_008c984c (*(int *)&DAT_008c984c) /* same address as DAT_008c984c, other width */
#define _DAT_008c9ca8 (*(undefined4 *)&DAT_008c9ca8) /* same address as DAT_008c9ca8, other width */
#define _DAT_008c9fc4 (*(code * *)&DAT_008c9fc4) /* same address as DAT_008c9fc4, other width */
#define _DAT_008c9ff8 (*(undefined4 *)&DAT_008c9ff8) /* same address as DAT_008c9ff8, other width */
#define _DAT_008ca080 (*(undefined4 *)&DAT_008ca080) /* same address as DAT_008ca080, other width */
#define _DAT_008ca098 (*(undefined4 *)&DAT_008ca098) /* same address as DAT_008ca098, other width */
#define _DAT_008ca0b0 (*(undefined4 *)&DAT_008ca0b0) /* same address as DAT_008ca0b0, other width */
#define _DAT_008ca144 (*(GrimServices * *)&DAT_008ca144) /* same address as DAT_008ca144, other width */
#define _DAT_008ca1b8 (*(undefined4 *)&DAT_008ca1b8) /* same address as DAT_008ca1b8, other width */
#define _DAT_008ca1f8 (*(undefined4 *)&DAT_008ca1f8) /* same address as DAT_008ca1f8, other width */
#define _DAT_008ca318 (*(undefined4 *)&DAT_008ca318) /* same address as DAT_008ca318, other width */
#define _DAT_008ca31c (*(undefined4 *)&DAT_008ca31c) /* same address as DAT_008ca31c, other width */
#define _DAT_008ca320 (*(undefined4 *)&DAT_008ca320) /* same address as DAT_008ca320, other width */
#define _DAT_008ca324 (*(undefined4 *)&DAT_008ca324) /* same address as DAT_008ca324, other width */
#define _DAT_008ca328 (*(undefined4 *)&DAT_008ca328) /* same address as DAT_008ca328, other width */
#define _DAT_008ca338 (*(undefined4 *)&DAT_008ca338) /* same address as DAT_008ca338, other width */
#define _DAT_008ca33c (*(undefined4 *)&DAT_008ca33c) /* same address as DAT_008ca33c, other width */
#define _DAT_008ca340 (*(undefined4 *)&DAT_008ca340) /* same address as DAT_008ca340, other width */
#define _DAT_008ca348 (*(undefined4 *)&DAT_008ca348) /* same address as DAT_008ca348, other width */
#define _DAT_008ca34c (*(undefined4 *)&DAT_008ca34c) /* same address as DAT_008ca34c, other width */
#define _DAT_008ca350 (*(undefined4 *)&DAT_008ca350) /* same address as DAT_008ca350, other width */
#define _DAT_008ca7b4 (*(void * *)&DAT_008ca7b4) /* same address as DAT_008ca7b4, other width */
#define _DAT_008cab94 (*(undefined4 *)&DAT_008cab94) /* same address as DAT_008cab94, other width */
#define _DAT_008cf264 (*(float *)&DAT_008cf264) /* same address as DAT_008cf264, other width */
#define _DAT_008cf268 (*(float *)&DAT_008cf268) /* same address as DAT_008cf268, other width */
#define _DAT_008cf284 (*(undefined4 *)&DAT_008cf284) /* same address as DAT_008cf284, other width */
#define _DAT_008d098c (*(GrimServices * *)&DAT_008d098c) /* same address as DAT_008d098c, other width */
#define _DAT_008d09e0 (*(int *)&DAT_008d09e0) /* same address as DAT_008d09e0, other width */
#define _DAT_008d0a68 (*(undefined4 *)&DAT_008d0a68) /* same address as DAT_008d0a68, other width */
#define _DAT_008d0ab4 (*(undefined4 *)&DAT_008d0ab4) /* same address as DAT_008d0ab4, other width */
#define _DAT_008d0ab8 (*(undefined4 *)&DAT_008d0ab8) /* same address as DAT_008d0ab8, other width */
#define _DAT_008d0abc (*(undefined4 *)&DAT_008d0abc) /* same address as DAT_008d0abc, other width */
#define _DAT_008d0ac0 (*(undefined4 *)&DAT_008d0ac0) /* same address as DAT_008d0ac0, other width */
#define _DAT_008d0ac4 (*(undefined4 *)&DAT_008d0ac4) /* same address as DAT_008d0ac4, other width */
#define _DAT_008d0ac8 (*(undefined4 *)&DAT_008d0ac8) /* same address as DAT_008d0ac8, other width */
#define _DAT_008d0ae0 (*(undefined4 *)&DAT_008d0ae0) /* same address as DAT_008d0ae0, other width */
#define _DAT_008d0aec (*(undefined4 *)&DAT_008d0aec) /* same address as DAT_008d0aec, other width */
#define _DAT_008d0eb0 (*(undefined4 *)&DAT_008d0eb0) /* same address as DAT_008d0eb0, other width */
#define _DAT_008d0eb4 (*(undefined4 *)&DAT_008d0eb4) /* same address as DAT_008d0eb4, other width */
#define _DAT_008d0eb8 (*(undefined4 *)&DAT_008d0eb8) /* same address as DAT_008d0eb8, other width */
#define _DAT_008d1090 (*(undefined *)&DAT_008d1090) /* same address as DAT_008d1090, other width */
#define _DAT_008d11f0 (*(undefined4 *)&DAT_008d11f0) /* same address as DAT_008d11f0, other width */
#define _DAT_008d1630 (*(undefined4 *)&DAT_008d1630) /* same address as DAT_008d1630, other width */
#define _DAT_008d1648 (*(undefined4 *)&DAT_008d1648) /* same address as DAT_008d1648, other width */
#define _DAT_008d164c (*(undefined4 *)&DAT_008d164c) /* same address as DAT_008d164c, other width */
#define _DAT_008d1650 (*(undefined4 *)&DAT_008d1650) /* same address as DAT_008d1650, other width */
#define _DAT_008d1654 (*(undefined4 *)&DAT_008d1654) /* same address as DAT_008d1654, other width */
#define _DAT_008d1658 (*(undefined4 *)&DAT_008d1658) /* same address as DAT_008d1658, other width */
#define _DAT_008d165c (*(undefined4 *)&DAT_008d165c) /* same address as DAT_008d165c, other width */
#define _DAT_008d1660 (*(undefined4 *)&DAT_008d1660) /* same address as DAT_008d1660, other width */
#define _DAT_008d1664 (*(undefined4 *)&DAT_008d1664) /* same address as DAT_008d1664, other width */
#define _DAT_008d1668 (*(undefined4 *)&DAT_008d1668) /* same address as DAT_008d1668, other width */
#define _DAT_008d166c (*(undefined4 *)&DAT_008d166c) /* same address as DAT_008d166c, other width */
#define _DAT_008d1670 (*(undefined4 *)&DAT_008d1670) /* same address as DAT_008d1670, other width */
#define _DAT_008d1674 (*(undefined4 *)&DAT_008d1674) /* same address as DAT_008d1674, other width */
#define _DAT_008d1678 (*(undefined4 *)&DAT_008d1678) /* same address as DAT_008d1678, other width */
#define _DAT_008d167c (*(undefined4 *)&DAT_008d167c) /* same address as DAT_008d167c, other width */
#define _DAT_008d1680 (*(undefined4 *)&DAT_008d1680) /* same address as DAT_008d1680, other width */
#define _DAT_008d1684 (*(undefined4 *)&DAT_008d1684) /* same address as DAT_008d1684, other width */
#define _DAT_008d1688 (*(undefined4 *)&DAT_008d1688) /* same address as DAT_008d1688, other width */
#define _DAT_008d168c (*(undefined4 *)&DAT_008d168c) /* same address as DAT_008d168c, other width */
#define _DAT_008d16ac (*(undefined4 *)&DAT_008d16ac) /* same address as DAT_008d16ac, other width */
#define _DAT_008d16b0 (*(uint *)&DAT_008d16b0) /* same address as DAT_008d16b0, other width */
#define _DAT_008d16b4 (*(undefined4 *)&DAT_008d16b4) /* same address as DAT_008d16b4, other width */
#define _DAT_008d16c0 (*(undefined4 *)&DAT_008d16c0) /* same address as DAT_008d16c0, other width */
#define _DAT_008d6f08 (*(undefined4 *)&DAT_008d6f08) /* same address as DAT_008d6f08, other width */
#define _DAT_008d6f0c (*(undefined4 *)&DAT_008d6f0c) /* same address as DAT_008d6f0c, other width */
#define _DAT_008d780c (*(undefined4 *)&DAT_008d780c) /* same address as DAT_008d780c, other width */
#define _DAT_008d7810 (*(undefined4 *)&DAT_008d7810) /* same address as DAT_008d7810, other width */
#define _DAT_008da5d0 (*(undefined4 *)&DAT_008da5d0) /* same address as DAT_008da5d0, other width */
#define _DAT_008da86c (*(undefined4 *)&DAT_008da86c) /* same address as DAT_008da86c, other width */
#define _DAT_008da888 (*(undefined4 *)&DAT_008da888) /* same address as DAT_008da888, other width */
#define _DAT_008db1e8 (*(undefined4 *)&DAT_008db1e8) /* same address as DAT_008db1e8, other width */
#define _DAT_008db200 (*(undefined4 *)&DAT_008db200) /* same address as DAT_008db200, other width */
#define _DAT_008db20c (*(undefined4 *)&DAT_008db20c) /* same address as DAT_008db20c, other width */
#define _DAT_008db214 (*(undefined4 *)&DAT_008db214) /* same address as DAT_008db214, other width */
#define _DAT_008db218 (*(undefined4 *)&DAT_008db218) /* same address as DAT_008db218, other width */
#define _DAT_008db21c (*(undefined4 *)&DAT_008db21c) /* same address as DAT_008db21c, other width */
#define _DAT_008db220 (*(undefined4 *)&DAT_008db220) /* same address as DAT_008db220, other width */
#define _DAT_008db224 (*(undefined4 *)&DAT_008db224) /* same address as DAT_008db224, other width */
#define _DAT_008db228 (*(undefined4 *)&DAT_008db228) /* same address as DAT_008db228, other width */
#define _DAT_008db22c (*(undefined4 *)&DAT_008db22c) /* same address as DAT_008db22c, other width */
#define _DAT_008db414 (*(undefined4 *)&DAT_008db414) /* same address as DAT_008db414, other width */
#define _DAT_008db42c (*(undefined4 *)&DAT_008db42c) /* same address as DAT_008db42c, other width */
#define _DAT_008dcc38 (*(undefined4 *)&DAT_008dcc38) /* same address as DAT_008dcc38, other width */
#define _DAT_008dcc3c (*(undefined4 *)&DAT_008dcc3c) /* same address as DAT_008dcc3c, other width */
#define _DAT_008dcc4c (*(undefined4 *)&DAT_008dcc4c) /* same address as DAT_008dcc4c, other width */
#define _DAT_008dcda0 (*(undefined4 *)&DAT_008dcda0) /* same address as DAT_008dcda0, other width */
#define _DAT_008ddda4 (*(undefined4 *)&DAT_008ddda4) /* same address as DAT_008ddda4, other width */
#define _DAT_008ddda8 (*(undefined4 *)&DAT_008ddda8) /* same address as DAT_008ddda8, other width */
#define _DAT_008dddb0 (*(undefined4 *)&DAT_008dddb0) /* same address as DAT_008dddb0, other width */
#define _DAT_008dddb4 (*(undefined4 *)&DAT_008dddb4) /* same address as DAT_008dddb4, other width */
#define _DAT_008dde4c (*(undefined4 *)&DAT_008dde4c) /* same address as DAT_008dde4c, other width */
#define _DAT_008dde60 (*(float *)&DAT_008dde60) /* same address as DAT_008dde60, other width */
#define _DAT_008dde64 (*(undefined4 *)&DAT_008dde64) /* same address as DAT_008dde64, other width */
#define _DAT_008dde74 (*(undefined4 *)&DAT_008dde74) /* same address as DAT_008dde74, other width */
#define _DAT_008dde80 (*(float *)&DAT_008dde80) /* same address as DAT_008dde80, other width */
#define _DAT_008dde84 (*(undefined4 *)&DAT_008dde84) /* same address as DAT_008dde84, other width */
#define _DAT_008dde94 (*(undefined4 *)&DAT_008dde94) /* same address as DAT_008dde94, other width */
#define _DAT_008dde9c (*(undefined4 *)&DAT_008dde9c) /* same address as DAT_008dde9c, other width */
#define _DAT_008ddea0 (*(float *)&DAT_008ddea0) /* same address as DAT_008ddea0, other width */
#define _DAT_008ddec4 (*(undefined4 *)&DAT_008ddec4) /* same address as DAT_008ddec4, other width */
#define _DAT_008ddec8 (*(float *)&DAT_008ddec8) /* same address as DAT_008ddec8, other width */
#define _DAT_008dded0 (*(undefined4 *)&DAT_008dded0) /* same address as DAT_008dded0, other width */
#define _DAT_008ddedc (*(float *)&DAT_008ddedc) /* same address as DAT_008ddedc, other width */
#define _DAT_008ddee0 (*(undefined4 *)&DAT_008ddee0) /* same address as DAT_008ddee0, other width */
#define _DAT_008ddeec (*(undefined4 *)&DAT_008ddeec) /* same address as DAT_008ddeec, other width */
#define _DAT_008ddef0 (*(undefined4 *)&DAT_008ddef0) /* same address as DAT_008ddef0, other width */
#define _DAT_008ddef4 (*(float *)&DAT_008ddef4) /* same address as DAT_008ddef4, other width */
#define _DAT_008ddf00 (*(undefined4 *)&DAT_008ddf00) /* same address as DAT_008ddf00, other width */
#define _DAT_008ddf1c (*(undefined4 *)&DAT_008ddf1c) /* same address as DAT_008ddf1c, other width */
#define _DAT_008ddf20 (*(undefined4 *)&DAT_008ddf20) /* same address as DAT_008ddf20, other width */
#define _DAT_008ddf28 (*(undefined4 *)&DAT_008ddf28) /* same address as DAT_008ddf28, other width */
#define _DAT_008ddf2c (*(undefined4 *)&DAT_008ddf2c) /* same address as DAT_008ddf2c, other width */
#define _DAT_008ddf34 (*(undefined4 *)&DAT_008ddf34) /* same address as DAT_008ddf34, other width */
#define _DAT_008ddf38 (*(undefined4 *)&DAT_008ddf38) /* same address as DAT_008ddf38, other width */
#define _DAT_008ddf48 (*(undefined4 *)&DAT_008ddf48) /* same address as DAT_008ddf48, other width */
#define _DAT_008fbfc0 (*(undefined4 *)&DAT_008fbfc0) /* same address as DAT_008fbfc0, other width */
#define _DAT_0090002c (*(float *)&DAT_0090002c) /* same address as DAT_0090002c, other width */
#define _DAT_00900030 (*(float *)&DAT_00900030) /* same address as DAT_00900030, other width */
#define _DAT_00900034 (*(float *)&DAT_00900034) /* same address as DAT_00900034, other width */
#define _DAT_00900044 (*(undefined4 *)&DAT_00900044) /* same address as DAT_00900044, other width */
#define _DAT_00900068 (*(undefined *)&DAT_00900068) /* same address as DAT_00900068, other width */
#define _DAT_0090052c (*(undefined4 *)&DAT_0090052c) /* same address as DAT_0090052c, other width */
#define _DAT_00900540 (*(undefined4 *)&DAT_00900540) /* same address as DAT_00900540, other width */
#define _DAT_00900544 (*(undefined4 *)&DAT_00900544) /* same address as DAT_00900544, other width */
#define _DAT_00900548 (*(undefined4 *)&DAT_00900548) /* same address as DAT_00900548, other width */
#define _DAT_0090054c (*(undefined4 *)&DAT_0090054c) /* same address as DAT_0090054c, other width */
#define _DAT_00900550 (*(undefined4 *)&DAT_00900550) /* same address as DAT_00900550, other width */
#define _DAT_00900554 (*(undefined4 *)&DAT_00900554) /* same address as DAT_00900554, other width */
#define _DAT_00900558 (*(undefined4 *)&DAT_00900558) /* same address as DAT_00900558, other width */
#define _DAT_0090055c (*(undefined4 *)&DAT_0090055c) /* same address as DAT_0090055c, other width */
#define _DAT_00900560 (*(undefined4 *)&DAT_00900560) /* same address as DAT_00900560, other width */
#define _DAT_00900564 (*(undefined4 *)&DAT_00900564) /* same address as DAT_00900564, other width */
#define _DAT_00900568 (*(undefined4 *)&DAT_00900568) /* same address as DAT_00900568, other width */
#define _DAT_009005a0 (*(undefined4 *)&DAT_009005a0) /* same address as DAT_009005a0, other width */
#define _DAT_009005a4 (*(undefined4 *)&DAT_009005a4) /* same address as DAT_009005a4, other width */
#define _DAT_009005c0 (*(undefined4 *)&DAT_009005c0) /* same address as DAT_009005c0, other width */
#define _DAT_009005c4 (*(undefined4 *)&DAT_009005c4) /* same address as DAT_009005c4, other width */
#define _DAT_009005e0 (*(undefined4 *)&DAT_009005e0) /* same address as DAT_009005e0, other width */
#define _DAT_009005e4 (*(undefined4 *)&DAT_009005e4) /* same address as DAT_009005e4, other width */
#define _DAT_00901400 (*(undefined4 *)&DAT_00901400) /* same address as DAT_00901400, other width */
#define _DAT_00901408 (*(undefined4 *)&DAT_00901408) /* same address as DAT_00901408, other width */
#define _DAT_00901458 (*(undefined4 *)&DAT_00901458) /* same address as DAT_00901458, other width */
#define _DAT_0090145c (*(undefined4 *)&DAT_0090145c) /* same address as DAT_0090145c, other width */
#define _DAT_009014d8 (*(undefined4 *)&DAT_009014d8) /* same address as DAT_009014d8, other width */
#define _DAT_009014e4 (*(undefined4 *)&DAT_009014e4) /* same address as DAT_009014e4, other width */
#define _DAT_009014ec (*(undefined4 *)&DAT_009014ec) /* same address as DAT_009014ec, other width */
#define _DAT_0090166c (*(undefined4 *)&DAT_0090166c) /* same address as DAT_0090166c, other width */
#define _DAT_00901684 (*(undefined4 *)&DAT_00901684) /* same address as DAT_00901684, other width */
#define _DAT_00901688 (*(undefined4 *)&DAT_00901688) /* same address as DAT_00901688, other width */
#define _DAT_0090169c (*(undefined4 *)&DAT_0090169c) /* same address as DAT_0090169c, other width */
#define _DAT_009016d8 (*(void * *)&DAT_009016d8) /* same address as DAT_009016d8, other width */
#define _DAT_0090175c (*(uint *)&DAT_0090175c) /* same address as DAT_0090175c, other width */
#define _DAT_00901764 (*(undefined *)&DAT_00901764) /* same address as DAT_00901764, other width */
#define _DAT_00901768 (*(undefined4 *)&DAT_00901768) /* same address as DAT_00901768, other width */
#define _DAT_0090176c (*(undefined4 *)&DAT_0090176c) /* same address as DAT_0090176c, other width */
#define _DAT_00901770 (*(undefined4 *)&DAT_00901770) /* same address as DAT_00901770, other width */
#define _DAT_00901774 (*(undefined4 *)&DAT_00901774) /* same address as DAT_00901774, other width */
#define _DAT_00901778 (*(undefined4 *)&DAT_00901778) /* same address as DAT_00901778, other width */
#define _DAT_0090177c (*(undefined4 *)&DAT_0090177c) /* same address as DAT_0090177c, other width */
#define _DAT_00901780 (*(undefined4 *)&DAT_00901780) /* same address as DAT_00901780, other width */
#define _DAT_00901784 (*(undefined4 *)&DAT_00901784) /* same address as DAT_00901784, other width */
#define _DAT_00901788 (*(undefined4 *)&DAT_00901788) /* same address as DAT_00901788, other width */
#define _DAT_0090178c (*(undefined4 *)&DAT_0090178c) /* same address as DAT_0090178c, other width */
#define _DAT_009017b4 (*(undefined4 *)&DAT_009017b4) /* same address as DAT_009017b4, other width */
#define _DAT_009017b8 (*(undefined4 *)&DAT_009017b8) /* same address as DAT_009017b8, other width */
#define _DAT_009017bc (*(undefined4 *)&DAT_009017bc) /* same address as DAT_009017bc, other width */
#define _DAT_009017c0 (*(undefined4 *)&DAT_009017c0) /* same address as DAT_009017c0, other width */
#define _DAT_009017c4 (*(undefined4 *)&DAT_009017c4) /* same address as DAT_009017c4, other width */
#define _DAT_009017c8 (*(undefined4 *)&DAT_009017c8) /* same address as DAT_009017c8, other width */
#define _DAT_009017cc (*(undefined4 *)&DAT_009017cc) /* same address as DAT_009017cc, other width */
#define _DAT_009017d0 (*(undefined4 *)&DAT_009017d0) /* same address as DAT_009017d0, other width */
#define _DAT_009017d4 (*(undefined4 *)&DAT_009017d4) /* same address as DAT_009017d4, other width */
#define _DAT_009017d8 (*(undefined4 *)&DAT_009017d8) /* same address as DAT_009017d8, other width */
#define _DAT_009017dc (*(undefined4 *)&DAT_009017dc) /* same address as DAT_009017dc, other width */
#define _DAT_009017e0 (*(undefined4 *)&DAT_009017e0) /* same address as DAT_009017e0, other width */
#define _DAT_00901808 (*(undefined4 *)&DAT_00901808) /* same address as DAT_00901808, other width */
#define _DAT_0090180c (*(undefined4 *)&DAT_0090180c) /* same address as DAT_0090180c, other width */
#define _DAT_00901810 (*(undefined4 *)&DAT_00901810) /* same address as DAT_00901810, other width */
#define _DAT_00901814 (*(undefined4 *)&DAT_00901814) /* same address as DAT_00901814, other width */
#define _DAT_00901818 (*(undefined4 *)&DAT_00901818) /* same address as DAT_00901818, other width */
#define _DAT_0090181c (*(undefined4 *)&DAT_0090181c) /* same address as DAT_0090181c, other width */
#define _DAT_00901820 (*(undefined4 *)&DAT_00901820) /* same address as DAT_00901820, other width */
#define _DAT_00901824 (*(undefined4 *)&DAT_00901824) /* same address as DAT_00901824, other width */
#define _DAT_00901828 (*(undefined4 *)&DAT_00901828) /* same address as DAT_00901828, other width */
#define _DAT_0090182c (*(undefined4 *)&DAT_0090182c) /* same address as DAT_0090182c, other width */
#define _DAT_00901830 (*(undefined4 *)&DAT_00901830) /* same address as DAT_00901830, other width */
#define _DAT_00901834 (*(undefined4 *)&DAT_00901834) /* same address as DAT_00901834, other width */
#define _DAT_0090185c (*(undefined4 *)&DAT_0090185c) /* same address as DAT_0090185c, other width */
#define _DAT_00901860 (*(undefined4 *)&DAT_00901860) /* same address as DAT_00901860, other width */
#define _DAT_00901864 (*(undefined4 *)&DAT_00901864) /* same address as DAT_00901864, other width */
#define _DAT_00901868 (*(undefined4 *)&DAT_00901868) /* same address as DAT_00901868, other width */
#define _DAT_0090186c (*(undefined4 *)&DAT_0090186c) /* same address as DAT_0090186c, other width */
#define _DAT_00901870 (*(undefined4 *)&DAT_00901870) /* same address as DAT_00901870, other width */
#define _DAT_00901874 (*(undefined4 *)&DAT_00901874) /* same address as DAT_00901874, other width */
#define _DAT_00901878 (*(undefined4 *)&DAT_00901878) /* same address as DAT_00901878, other width */
#define _DAT_0090187c (*(undefined4 *)&DAT_0090187c) /* same address as DAT_0090187c, other width */
#define _DAT_00901880 (*(undefined4 *)&DAT_00901880) /* same address as DAT_00901880, other width */
#define _DAT_00901884 (*(undefined4 *)&DAT_00901884) /* same address as DAT_00901884, other width */
#define _DAT_00901888 (*(undefined4 *)&DAT_00901888) /* same address as DAT_00901888, other width */
#define _DAT_009018b0 (*(undefined4 *)&DAT_009018b0) /* same address as DAT_009018b0, other width */
#define _DAT_009018b4 (*(undefined4 *)&DAT_009018b4) /* same address as DAT_009018b4, other width */
#define _DAT_009018b8 (*(undefined4 *)&DAT_009018b8) /* same address as DAT_009018b8, other width */
#define _DAT_009018bc (*(undefined4 *)&DAT_009018bc) /* same address as DAT_009018bc, other width */
#define _DAT_009018c0 (*(undefined4 *)&DAT_009018c0) /* same address as DAT_009018c0, other width */
#define _DAT_009018c4 (*(undefined4 *)&DAT_009018c4) /* same address as DAT_009018c4, other width */
#define _DAT_009018c8 (*(undefined4 *)&DAT_009018c8) /* same address as DAT_009018c8, other width */
#define _DAT_009018cc (*(undefined4 *)&DAT_009018cc) /* same address as DAT_009018cc, other width */
#define _DAT_009018d0 (*(undefined4 *)&DAT_009018d0) /* same address as DAT_009018d0, other width */
#define _DAT_009018d4 (*(undefined4 *)&DAT_009018d4) /* same address as DAT_009018d4, other width */
#define _DAT_009018d8 (*(undefined4 *)&DAT_009018d8) /* same address as DAT_009018d8, other width */
#define _DAT_009018dc (*(undefined4 *)&DAT_009018dc) /* same address as DAT_009018dc, other width */
#define _DAT_00901904 (*(undefined4 *)&DAT_00901904) /* same address as DAT_00901904, other width */
#define _DAT_00901908 (*(undefined4 *)&DAT_00901908) /* same address as DAT_00901908, other width */
#define _DAT_0090190c (*(undefined4 *)&DAT_0090190c) /* same address as DAT_0090190c, other width */
#define _DAT_00901910 (*(undefined4 *)&DAT_00901910) /* same address as DAT_00901910, other width */
#define _DAT_00901914 (*(undefined4 *)&DAT_00901914) /* same address as DAT_00901914, other width */
#define _DAT_00901918 (*(undefined4 *)&DAT_00901918) /* same address as DAT_00901918, other width */
#define _DAT_0090191c (*(undefined4 *)&DAT_0090191c) /* same address as DAT_0090191c, other width */
#define _DAT_00901920 (*(undefined4 *)&DAT_00901920) /* same address as DAT_00901920, other width */
#define _DAT_00901924 (*(undefined4 *)&DAT_00901924) /* same address as DAT_00901924, other width */
#define _DAT_00901928 (*(undefined4 *)&DAT_00901928) /* same address as DAT_00901928, other width */
#define _DAT_0090192c (*(undefined4 *)&DAT_0090192c) /* same address as DAT_0090192c, other width */
#define _DAT_00901930 (*(undefined4 *)&DAT_00901930) /* same address as DAT_00901930, other width */
#define _DAT_00901958 (*(undefined4 *)&DAT_00901958) /* same address as DAT_00901958, other width */
#define _DAT_0090195c (*(undefined4 *)&DAT_0090195c) /* same address as DAT_0090195c, other width */
#define _DAT_00901960 (*(undefined4 *)&DAT_00901960) /* same address as DAT_00901960, other width */
#define _DAT_00901964 (*(undefined4 *)&DAT_00901964) /* same address as DAT_00901964, other width */
#define _DAT_00901968 (*(undefined4 *)&DAT_00901968) /* same address as DAT_00901968, other width */
#define _DAT_0090196c (*(undefined4 *)&DAT_0090196c) /* same address as DAT_0090196c, other width */
#define _DAT_00901970 (*(undefined4 *)&DAT_00901970) /* same address as DAT_00901970, other width */
#define _DAT_00901974 (*(undefined4 *)&DAT_00901974) /* same address as DAT_00901974, other width */
#define _DAT_00901978 (*(undefined4 *)&DAT_00901978) /* same address as DAT_00901978, other width */
#define _DAT_0090197c (*(undefined4 *)&DAT_0090197c) /* same address as DAT_0090197c, other width */
#define _DAT_00901980 (*(undefined4 *)&DAT_00901980) /* same address as DAT_00901980, other width */
#define _DAT_00901984 (*(undefined4 *)&DAT_00901984) /* same address as DAT_00901984, other width */
#define _DAT_009019ac (*(undefined4 *)&DAT_009019ac) /* same address as DAT_009019ac, other width */
#define _DAT_009019b0 (*(undefined4 *)&DAT_009019b0) /* same address as DAT_009019b0, other width */
#define _DAT_009019b4 (*(undefined4 *)&DAT_009019b4) /* same address as DAT_009019b4, other width */
#define _DAT_009019b8 (*(undefined4 *)&DAT_009019b8) /* same address as DAT_009019b8, other width */
#define _DAT_009019bc (*(undefined4 *)&DAT_009019bc) /* same address as DAT_009019bc, other width */
#define _DAT_009019c0 (*(undefined4 *)&DAT_009019c0) /* same address as DAT_009019c0, other width */
#define _DAT_009019c4 (*(undefined4 *)&DAT_009019c4) /* same address as DAT_009019c4, other width */
#define _DAT_009019c8 (*(undefined4 *)&DAT_009019c8) /* same address as DAT_009019c8, other width */
#define _DAT_009019cc (*(undefined4 *)&DAT_009019cc) /* same address as DAT_009019cc, other width */
#define _DAT_009019d0 (*(undefined4 *)&DAT_009019d0) /* same address as DAT_009019d0, other width */
#define _DAT_009019d4 (*(undefined4 *)&DAT_009019d4) /* same address as DAT_009019d4, other width */
#define _DAT_009019d8 (*(undefined4 *)&DAT_009019d8) /* same address as DAT_009019d8, other width */
#define _DAT_009019dc (*(undefined4 *)&DAT_009019dc) /* same address as DAT_009019dc, other width */
#define _DAT_009019e0 (*(undefined4 *)&DAT_009019e0) /* same address as DAT_009019e0, other width */
#define _DAT_009019e4 (*(undefined4 *)&DAT_009019e4) /* same address as DAT_009019e4, other width */
#define _DAT_009019e8 (*(undefined4 *)&DAT_009019e8) /* same address as DAT_009019e8, other width */
#define _DAT_009019ec (*(undefined4 *)&DAT_009019ec) /* same address as DAT_009019ec, other width */
#define _DAT_009019f0 (*(undefined4 *)&DAT_009019f0) /* same address as DAT_009019f0, other width */
#define _DAT_00901a00 (*(undefined4 *)&DAT_00901a00) /* same address as DAT_00901a00, other width */
#define _DAT_00901a04 (*(undefined4 *)&DAT_00901a04) /* same address as DAT_00901a04, other width */
#define _DAT_00901a08 (*(undefined4 *)&DAT_00901a08) /* same address as DAT_00901a08, other width */
#define _DAT_00901a0c (*(undefined4 *)&DAT_00901a0c) /* same address as DAT_00901a0c, other width */
#define _DAT_00901a10 (*(undefined4 *)&DAT_00901a10) /* same address as DAT_00901a10, other width */
#define _DAT_00901a14 (*(undefined4 *)&DAT_00901a14) /* same address as DAT_00901a14, other width */
#define _DAT_00901a18 (*(undefined4 *)&DAT_00901a18) /* same address as DAT_00901a18, other width */
#define _DAT_00901a1c (*(undefined4 *)&DAT_00901a1c) /* same address as DAT_00901a1c, other width */
#define _DAT_00901a20 (*(undefined4 *)&DAT_00901a20) /* same address as DAT_00901a20, other width */
#define _DAT_00901a24 (*(undefined4 *)&DAT_00901a24) /* same address as DAT_00901a24, other width */
#define _DAT_00901a28 (*(undefined4 *)&DAT_00901a28) /* same address as DAT_00901a28, other width */
#define _DAT_00901a2c (*(undefined4 *)&DAT_00901a2c) /* same address as DAT_00901a2c, other width */
#define _DAT_00901a30 (*(undefined4 *)&DAT_00901a30) /* same address as DAT_00901a30, other width */
#define _DAT_00901a34 (*(undefined4 *)&DAT_00901a34) /* same address as DAT_00901a34, other width */
#define _DAT_00901a38 (*(undefined4 *)&DAT_00901a38) /* same address as DAT_00901a38, other width */
#define _DAT_00901a3c (*(undefined4 *)&DAT_00901a3c) /* same address as DAT_00901a3c, other width */
#define _DAT_00901a40 (*(undefined4 *)&DAT_00901a40) /* same address as DAT_00901a40, other width */
#define _DAT_00901a44 (*(undefined4 *)&DAT_00901a44) /* same address as DAT_00901a44, other width */
#define _DAT_00901a54 (*(undefined4 *)&DAT_00901a54) /* same address as DAT_00901a54, other width */
#define _DAT_00901a58 (*(undefined4 *)&DAT_00901a58) /* same address as DAT_00901a58, other width */
#define _DAT_00901a5c (*(undefined4 *)&DAT_00901a5c) /* same address as DAT_00901a5c, other width */
#define _DAT_00901a60 (*(undefined4 *)&DAT_00901a60) /* same address as DAT_00901a60, other width */
#define _DAT_00901a64 (*(undefined4 *)&DAT_00901a64) /* same address as DAT_00901a64, other width */
#define _DAT_00901a68 (*(undefined4 *)&DAT_00901a68) /* same address as DAT_00901a68, other width */
#define _DAT_00901a6c (*(undefined4 *)&DAT_00901a6c) /* same address as DAT_00901a6c, other width */
#define _DAT_00901a70 (*(undefined4 *)&DAT_00901a70) /* same address as DAT_00901a70, other width */
#define _DAT_00901a74 (*(undefined4 *)&DAT_00901a74) /* same address as DAT_00901a74, other width */
#define _DAT_00901a78 (*(undefined4 *)&DAT_00901a78) /* same address as DAT_00901a78, other width */
#define _DAT_00901a7c (*(undefined4 *)&DAT_00901a7c) /* same address as DAT_00901a7c, other width */
#define _DAT_00901a80 (*(undefined4 *)&DAT_00901a80) /* same address as DAT_00901a80, other width */
#define _DAT_00901a84 (*(undefined4 *)&DAT_00901a84) /* same address as DAT_00901a84, other width */
#define _DAT_00901a88 (*(undefined4 *)&DAT_00901a88) /* same address as DAT_00901a88, other width */
#define _DAT_00901a8c (*(undefined4 *)&DAT_00901a8c) /* same address as DAT_00901a8c, other width */
#define _DAT_00901a90 (*(undefined4 *)&DAT_00901a90) /* same address as DAT_00901a90, other width */
#define _DAT_00901a94 (*(undefined4 *)&DAT_00901a94) /* same address as DAT_00901a94, other width */
#define _DAT_00901a98 (*(undefined4 *)&DAT_00901a98) /* same address as DAT_00901a98, other width */
#define _DAT_00902ee8 (*(undefined *)&DAT_00902ee8) /* same address as DAT_00902ee8, other width */
#define _DAT_00902eec (*(undefined4 *)&DAT_00902eec) /* same address as DAT_00902eec, other width */
#define _DAT_00902ef0 (*(undefined4 *)&DAT_00902ef0) /* same address as DAT_00902ef0, other width */
#define _DAT_00902ef4 (*(undefined4 *)&DAT_00902ef4) /* same address as DAT_00902ef4, other width */
#define _DAT_009055e4 (*(undefined4 *)&DAT_009055e4) /* same address as DAT_009055e4, other width */
#define _DAT_009055e8 (*(undefined4 *)&DAT_009055e8) /* same address as DAT_009055e8, other width */
#define _DAT_009055fc (*(undefined4 *)&DAT_009055fc) /* same address as DAT_009055fc, other width */
#define _DAT_00905614 (*(undefined2 *)&DAT_00905614) /* same address as DAT_00905614, other width */
#define _DAT_00905638 (*(void * *)&DAT_00905638) /* same address as DAT_00905638, other width */
#define _DAT_00906c04 (*(undefined4 *)&DAT_00906c04) /* same address as DAT_00906c04, other width */
#define _DAT_00906c0c (*(undefined4 *)&DAT_00906c0c) /* same address as DAT_00906c0c, other width */
#define _DAT_00906c50 (*(undefined4 *)&DAT_00906c50) /* same address as DAT_00906c50, other width */
#define _DAT_00906c58 (*(undefined4 *)&DAT_00906c58) /* same address as DAT_00906c58, other width */
#define _DAT_00906c60 (*(int *)&DAT_00906c60) /* same address as DAT_00906c60, other width */
#define _DAT_00906c70 (*(undefined4 *)&DAT_00906c70) /* same address as DAT_00906c70, other width */
#define _g_bShowFps (*(undefined4 *)&g_bShowFps) /* same address as g_bShowFps, other width */
#define DAT_0080cbe0_2 (*(undefined2 *)((undefined *)&DAT_0080cbe0 + 2))
#define DAT_0080cbec_2 (*(undefined2 *)((undefined *)&DAT_0080cbec + 2))
#define DAT_00811b24_2 (*(undefined2 *)((undefined *)&DAT_00811b24 + 2))
#define DAT_00812ec4_2 (*(undefined2 *)((undefined *)&DAT_00812ec4 + 2))
#define DAT_00815608_2 (*(undefined2 *)((undefined *)&DAT_00815608 + 2))
