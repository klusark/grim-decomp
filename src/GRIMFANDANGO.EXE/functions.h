/* GRIMFANDANGO.EXE: prototypes of every decompiled function, by module */
#pragma once
#include "ghidra_types.h"

/* ===== window.c ===== */
undefined * __stdcall Win_WinMain(int a1,int a2,int a3,int a4); /* 0x00401010 */
undefined * __cdecl Win_WndProc(uint param_1,uint param_2,int param_3); /* 0x00402fd0 */
void __cdecl Win_SetMainHwnd(void *param_1); /* 0x00473360 */
void * __cdecl Win_GetMainHwnd(void); /* 0x00473370 */
void __cdecl Win_SetInstance(uint param_1); /* 0x00473380 */
uint __cdecl Win_GetInstance(void); /* 0x00473390 */
uint __cdecl Win_IsSysCommandBlocked(uint param_1,int param_2,int param_3); /* 0x004772d0 */
void __cdecl Win_AbortIfAlreadyRunning (void *hInstance,void *hPrevInstance,char *cmdLine,int nCmdShow,char *appName); /* 0x004abf40 */
uint __cdecl Win_PumpMessages(void); /* 0x004ac020 */
int __cdecl Win_SetWindowedSize(int fullscreen,int w,int h); /* 0x004ac100 */
void __cdecl Win_AddMessageHook(void *param_1); /* 0x004ac160 */
undefined4 __cdecl Win_RemoveMessageHook(void *hook); /* 0x004ac1a0 */
uint __cdecl Win_CreateMainWindow(uint param_1,uint param_2,int param_3); /* 0x004ac1f0 */
undefined * __stdcall Win_KernelWndProc(int a1,int a2,int a3,int a4); /* 0x004ac340 */
int __cdecl Win_IsFocusWithin(void *hwnd); /* 0x004bff70 */

/* ===== debuglog.c ===== */
void __cdecl grimdemo_EnableDebugging(int enable); /* 0x00401040 */
uint __cdecl DebugLog_Load(void); /* 0x004020a0 */
char * __cdecl grimdemo_MessagePrint(char *fmt,...); /* 0x00402330 */
char * __cdecl grimdemo_StatusPrint(char *fmt,...); /* 0x004023a0 */
char * __cdecl grimdemo_ErrorPrint(char *fmt,...); /* 0x00402410 */
char * __cdecl grimdemo_WarningPrint(char *fmt,...); /* 0x00402480 */
char * __cdecl grimdemo_DebugPrint(char *fmt,...); /* 0x004024f0 */
void __cdecl DebugLog_Write(char *param_1,uint param_2); /* 0x00402560 */

/* ===== grim.c ===== */
int __cdecl Grim_FindDataOnDrives(char *subdir); /* 0x00401140 */
uint __cdecl Main_Startup(char *param_1); /* 0x004012b0 */
void __cdecl Grim_DecodeRegKeyName(char *s); /* 0x00401640 */
int __cdecl Grim_FatalMessageBox(int param_1,int param_2,int param_3,int param_4); /* 0x004018b0 */
void __cdecl Grim_ShutdownDisplay(void); /* 0x00401900 */
void __cdecl Main_Shutdown(void); /* 0x00401950 */
void __cdecl Grim_EnumDisplayModes(void); /* 0x00401a50 */
void __cdecl grimdemo_PleaseShutdown(void); /* 0x00402050 */
uint __cdecl grimdemo_SetPalette(void *param_1,int param_2); /* 0x00402060 */
int __cdecl Grim_ParseCommandLine(char *cmdline); /* 0x00402c80 */
void __cdecl Grim_OpenRegistry(void); /* 0x004034b0 */
void __cdecl Grim_ShowSplash(void); /* 0x00403520 */

/* ===== game.c ===== */
void __cdecl Main_Service(void); /* 0x004016a0 */

/* ===== lua.c ===== */
void __cdecl sputLua_Is3DHardwareEnabledL(void); /* 0x00401ca0 */
void __cdecl Lua_SetHardwareState(void); /* 0x00401cc0 */
void __cdecl Lua_GetVideoDevices(void); /* 0x00401d30 */
void __cdecl Lua_SetVideoDevices(void); /* 0x00401da0 */
void __cdecl Lua_Enumerate3DDevices(void); /* 0x00401e90 */
void __cdecl Lua_EnumerateVideoDevices(void); /* 0x00401fb0 */
void __cdecl grimlib_NextSetup(void); /* 0x00482880 */
void __cdecl grimlib_PreviousSetup(void); /* 0x004828a0 */
void __cdecl sputRender_ClearIris(void); /* 0x00486f50 */
void __cdecl sputPrimitive_DrawLine(void); /* 0x00489840 */
void __cdecl sputPrimitive_DrawPolygon(void); /* 0x00489a80 */
void __cdecl sputPrimitive_DrawRectangle(void); /* 0x00489d70 */
void __cdecl sputPrimitive_ChangePrimitive(void); /* 0x00489fe0 */
void __cdecl sputPrimitive_KillPrimitive(void); /* 0x0048a460 */
void sputPrimitive_PurgeQueue(void); /* 0x0048a4a0 */
void __cdecl sputText_SetOffscreenTextPosL(void); /* 0x0048ad60 */
void __cdecl sputText_SetEmergencyFontL(void); /* 0x0048ade0 */
void __cdecl sputText_LocalizeStringL(void); /* 0x0048ae60 */
void __cdecl sputText_MakeColorL(void); /* 0x0048aed0 */
void __cdecl sputText_GetColorComponentsL(void); /* 0x0048b100 */
void __cdecl sputText_SetActorTalkColorL(void); /* 0x0048b190 */
void __cdecl sputText_GetActorTalkColorL(void); /* 0x0048b230 */
void __cdecl sputText_SetSayLineDefaultsL(void); /* 0x0048b2a0 */
void __cdecl sputText_SayLineL(void); /* 0x0048b4c0 */
void __cdecl Lua_ParseSayLineTable(int param_1,int *param_2,int *param_3,int *param_4,int *param_5,int *param_6); /* 0x0048b6a0 */
void __cdecl sputText_PrintLineL(void); /* 0x0048b830 */
void __cdecl sputText_IsMessageGoingL(void); /* 0x0048b9a0 */
void __cdecl sputText_ExpireTextQueueL(void); /* 0x0048ba90 */
void __cdecl sputText_PurgeTextQueueL(void); /* 0x0048baf0 */
void __cdecl sputText_KillTextObjectL(void); /* 0x0048bb20 */
void __cdecl sputText_GetFontDimensionsL(void); /* 0x0048bb70 */
void __cdecl sputText_GetTextObjectDimensionsL(void); /* 0x0048bbc0 */
void __cdecl sputText_GetTextCharPositionL(void); /* 0x0048bc50 */
void __cdecl sputText_ChangeTextObjectL(void); /* 0x0048bd10 */
void __cdecl sputText_MakeTextObjectL(void); /* 0x0048be30 */
void __cdecl sputText_BlastText(void); /* 0x0048bf50 */
void __cdecl sputText_GetTranslationModeL(void); /* 0x0048c960 */
void __cdecl sputText_SetTranslationModeL(void); /* 0x0048c980 */
void __cdecl sputCostume_GetKeyLengthL(void); /* 0x00495850 */
void __cdecl sputCostume_GetSmushLengthL(void); /* 0x00495900 */
void __cdecl Lua_Stub(char *fmt,...); /* 0x00497830 */
void __cdecl sputLua_GetMemoryUsageL(void); /* 0x00498d80 */
void __cdecl sputLua_GetDiskFreeSpaceL(void); /* 0x00498da0 */
void __cdecl sputLua_Test(void); /* 0x00498e20 */
void __cdecl sputLua_ShrinkBoxes(void); /* 0x00498e50 */
void sputLua_UnShrinkBoxes(void); /* 0x00498e90 */
void __cdecl sputLua_GetShrinkPosition(void); /* 0x00498ea0 */
void __cdecl sputLua_SetSoundParametersL(void); /* 0x00499000 */
void __cdecl sputLua_GetSoundParametersL(void); /* 0x004991c0 */
void __cdecl sputLua_SetDebugToggleCallback(uint param_1); /* 0x00499250 */
void __cdecl sputLua_EnginePause(void); /* 0x00499260 */
void __cdecl sputLua_EngineResume(void); /* 0x00499270 */
void __cdecl sputLua_EngineDisplay(void); /* 0x00499280 */
void __cdecl sputLua_AllocateActorL(void); /* 0x004992b0 */
void __cdecl sputLua_PutActorAtInterestL(void); /* 0x004992d0 */
void __cdecl sputLua_SetSelectedActorL(void); /* 0x00499360 */
void __cdecl sputLua_PutActorAtL(void); /* 0x004993c0 */
void __cdecl sputLua_PutActorInSetL(void); /* 0x004994a0 */
void __cdecl sputLua_WalkActorVectorL(void); /* 0x00499590 */
void __cdecl sputLua_WalkActorForwardL(void); /* 0x00499800 */
void __cdecl sputLua_WalkActorToL(void); /* 0x00499860 */
void __cdecl sputLua_WalkActorToAvoidingL(void); /* 0x004999d0 */
void __cdecl sputLua_IsActorMovingL(void); /* 0x00499b80 */
void __cdecl sputLua_IsActorTurningL(void); /* 0x00499be0 */
void __cdecl sputLua_SetActorChoreLoopingL(void); /* 0x00499c70 */
void __cdecl sputLua_IsActorRestingL(void); /* 0x00499da0 */
void __cdecl sputLua_IsActorChoringL(void); /* 0x00499e20 */
void __cdecl sputLua_GetActorChoresL(void); /* 0x00499ff0 */
void __cdecl sputLua_GetActorCostumeDepthL(void); /* 0x0049a160 */
void __cdecl sputLua_GetActorLoopingChoresL(void); /* 0x0049a2a0 */
void __cdecl sputLua_SetActorColormapL(void); /* 0x0049a410 */
void __cdecl sputLua_SetActorCostumeL(void); /* 0x0049a500 */
void __cdecl sputLua_PrintActorCostumesL(void); /* 0x0049a5e0 */
void __cdecl sputLua_PushActorCostumeL(void); /* 0x0049a640 */
void __cdecl sputLua_PopActorCostumeL(void); /* 0x0049a6c0 */
void __cdecl sputLua_StopActorChoreL(void); /* 0x0049a750 */
void __cdecl sputLua_PlayActorChoreL(void); /* 0x0049a830 */
void __cdecl sputLua_CompleteActorChoreL(void); /* 0x0049a910 */
void __cdecl sputLua_PlayActorChoreLoopingL(void); /* 0x0049a9e0 */
void __cdecl sputLua_ActorLookAtL(void); /* 0x0049aac0 */
void __cdecl sputLua_IsActorLookingL(void); /* 0x0049ad30 */
void __cdecl sputLua_SetActorLookRate(void); /* 0x0049ad90 */
void __cdecl sputLua_GetActorLookRate(void); /* 0x0049ae10 */
void __cdecl sputLua_SetActorVisibilityL(void); /* 0x0049ae80 */
void __cdecl sputLua_SetActorFollowBoxesL(void); /* 0x0049af00 */
void __cdecl sputLua_ShutUpActorL(void); /* 0x0049af80 */
void __cdecl sputLua_SetActorFrustrumCull(void); /* 0x0049afd0 */
void __cdecl sputLua_GetCameraActorL(void); /* 0x0049b040 */
void __cdecl sputLua_GetActorWalkRateL(void); /* 0x0049b060 */
void __cdecl sputLua_SetActorWalkRateL(void); /* 0x0049b0d0 */
void __cdecl sputLua_GetActorTurnRateL(void); /* 0x0049b160 */
void __cdecl sputLua_SetActorTurnRateL(void); /* 0x0049b1d0 */
void __cdecl sputLua_SetActorWalkChoresL(void); /* 0x0049b280 */
void __cdecl sputLua_SetActorTurnChoresL(void); /* 0x0049b350 */
void __cdecl sputLua_SetActorRestChoreL(void); /* 0x0049b430 */
void __cdecl sputLua_SetActorMumbleChoreL(void); /* 0x0049b500 */
void __cdecl sputLua_SetActorTalkChoreL(void); /* 0x0049b5a0 */
void __cdecl sputLua_SetActorHeadL(void); /* 0x0049b6c0 */
void __cdecl sputLua_CanActorSeeL(void); /* 0x0049b830 */
void __cdecl sputLua_GetVisibleThingsL(void); /* 0x0049b9e0 */
void __cdecl sputLua_GetActorRectL(void); /* 0x0049bb10 */
void __cdecl sputLua_GetActorPuckVectorL(void); /* 0x0049bba0 */
void __cdecl sputLua_GetActorYawToPoint(void); /* 0x0049bcc0 */
void __cdecl sputLua_SetActorReflection(void); /* 0x0049be40 */
void __cdecl sputLua_GetActorPosL(void); /* 0x0049bec0 */
void __cdecl sputLua_GetActorRotL(void); /* 0x0049bf30 */
void __cdecl sputLua_SetActorRotL(void); /* 0x0049bfa0 */
void __cdecl sputLua_SetActorPitch(void); /* 0x0049c0a0 */
void __cdecl sputLua_SetActorRoll(void); /* 0x0049c110 */
void __cdecl sputLua_TurnActorL(void); /* 0x0049c180 */
void __cdecl sputLua_GetActorSectorL(void); /* 0x0049c200 */
void __cdecl sputLua_IsActorInSector(void); /* 0x0049c2c0 */
void __cdecl sputLua_IsPointInSector(void); /* 0x0049c4c0 */
int __cdecl sputLua_FindSystemFiles(void); /* 0x0049c5e0 */
int __cdecl sputLua_Boot(int flag,char *str); /* 0x0049c600 */
void __cdecl sputLua_CameraChange(int fromSetup,int toSetup); /* 0x0049c660 */
void __cdecl sputLua_PostCameraChange(int setup); /* 0x0049c6e0 */
void __cdecl sputLua_RegisterFunctions(int *param_1,int param_2); /* 0x0049ca60 */
void __cdecl sputLua_JustLoadedL(void); /* 0x0049ca80 */
void __cdecl sputLua_ActorVoiceIs3DL(void); /* 0x0049caa0 */
int __cdecl FindCostumeInStack(void *luaObj,CostumeNode *costumeList,CostumeNode **outCostume); /* 0x0049cb10 */
void __cdecl sputLua_CheckForFileL(void); /* 0x0049cca0 */
void __cdecl sputLua_NukeResourcesL(void); /* 0x0049cd10 */
void __cdecl sputLua_DetachFromResourcesL(void); /* 0x0049cd40 */
void __cdecl sputLua_AttachToResourcesL(void); /* 0x0049cd50 */
void __cdecl sputLua_SearchForFileOrSwapCDsL(void); /* 0x0049cd60 */
void __cdecl sputLua_LoadL(void); /* 0x0049cea0 */
void __cdecl sputLua_SaveL(void); /* 0x0049cef0 */
void __cdecl sputLua_EnableDebugKeysL(void); /* 0x0049cf40 */
void __cdecl sputLua_WorldToScreenL(void); /* 0x0049cf60 */
void __cdecl sputLua_ScreenToWorldL(void); /* 0x0049d030 */
void __cdecl sputLua_ConcatFallback(void); /* 0x0049d220 */
void __cdecl sputLua_ExitL(void); /* 0x0049d3a0 */
void __cdecl sputLua_EnableControlL(void); /* 0x0049d3f0 */
void __cdecl sputLua_DisableControlL(void); /* 0x0049d430 */
void __cdecl sputLua_GetControlStateL(void); /* 0x0049d470 */
void __cdecl sputLua_DoCostumeOverrideCallback(void *actor,int flag); /* 0x0049d550 */
void __cdecl sputLua_DoCostumeMarkerCallback(void *actor,uint marker); /* 0x0049d670 */
void __cdecl sputLua_DoUserPaintCallback(void); /* 0x0049d7b0 */
uint __cdecl sputLua_DoExitCallback(void); /* 0x0049d890 */
uint __cdecl sputLua_DoPauseCallback(void); /* 0x0049d970 */
int __cdecl sputLua_DoCharacterCallback(int ch); /* 0x0049da50 */
void __cdecl sputLua_MakeCurrentSetupL(void); /* 0x0049db70 */
void __cdecl sputLua_GetCurrentSetupL(void); /* 0x0049dbb0 */
void __cdecl sputLua_MakeCurrentSetL(void); /* 0x0049dc70 */
void __cdecl sputLua_LockSet(void); /* 0x0049dcb0 */
void __cdecl sputLua_UnLockSet(void); /* 0x0049dd10 */
void __cdecl sputLua_MessagePrintL(void); /* 0x0049dd70 */
void __cdecl Lua_Print_NoOp(void); /* 0x0049ddd0 */
uint __cdecl sputLua_Startup(void); /* 0x0049de00 */
uint __cdecl sputLua_SaveIndirector(int param_1,uint param_2); /* 0x0049dfa0 */
TextObject * __cdecl sputLua_RestoreIndirector(int param_1,TextObject *param_2); /* 0x0049e020 */
uint __cdecl sputLua_NotifyControlHandlers(void); /* 0x0049e0b0 */
uint __cdecl Lua_CreateSystemTable(void); /* 0x0049e380 */
void __cdecl Lua_CreateControlsTable(uint param_1); /* 0x0049e460 */
void __cdecl sputLua_SetSoundPosition(void); /* 0x0049e590 */
void __cdecl sputLua_StartFullScreenMovieL(void); /* 0x0049e7e0 */
void __cdecl sputLua_PauseMovieL(void); /* 0x0049e860 */
void __cdecl sputLua_IsMoviePlayingL(void); /* 0x0049e960 */
void __fastcall sputLua_FileFindFirst(char *param_1); /* 0x0049e980 */
void __cdecl sputLua_FileFindNext(void); /* 0x0049ea20 */
void __cdecl sputLua_FileFindDispose(void); /* 0x0049ea90 */
void __cdecl sputLua_QueryDialog(void); /* 0x0049eab0 */
void __cdecl sputLua_InputDialog(void); /* 0x0049eb60 */
void __cdecl sputLua_WriteRegistryValue(void); /* 0x0049ec50 */
void __cdecl sputLua_ReadRegistryValue(void); /* 0x0049ece0 */
void __cdecl sputLua_GetSectorOppositeEdge(void); /* 0x0049ed90 */
void __cdecl sputLua_IsSectorActiveL(void); /* 0x0049ee20 */
void __cdecl sputLua_MakeSectorActiveL(void); /* 0x0049eeb0 */
void __cdecl sputLua_PreRender(void); /* 0x0049ef50 */
void __cdecl sputLua_GetCurrentScript(void); /* 0x0049efc0 */
void __cdecl sputLua_LockFontL(void); /* 0x0049efe0 */
void __cdecl sputLua_LoadCostumeL(void); /* 0x0049f040 */
void __fastcall sputLua_GetPhysicalBytes(undefined4 param_1); /* 0x0049f080 */
void __cdecl sputLua_SetMemoryUsage(void); /* 0x0049f0a0 */
void __cdecl sputLua_GetCameraPositionL(void); /* 0x0049f2b0 */
void __cdecl sputLua_GetCameraInterestL(void); /* 0x0049f300 */
void __cdecl sputLua_GetCameraFOVL(void); /* 0x0049f350 */
void __cdecl sputLua_GetCameraRollL(void); /* 0x0049f380 */
void __cdecl sputLua_SetCameraPositionL(void); /* 0x0049f3b0 */
void __cdecl sputLua_SetCameraInterestL(void); /* 0x0049f480 */
void __cdecl sputLua_SetActorScaleL(void); /* 0x0049f550 */
void __cdecl sputLua_SetActorTimeScaleL(void); /* 0x0049f5d0 */
void __cdecl sputLua_GetActorNodeLocationL(void); /* 0x0049f690 */
void __cdecl sputLua_GetActorScaleL(void); /* 0x0049f810 */
void __cdecl sputLua_GetActorTimeScaleL(void); /* 0x0049f860 */
void __cdecl sputLua_SetCameraFOVL(void); /* 0x0049f8d0 */
void __cdecl sputLua_SetCameraRollL(void); /* 0x0049f930 */
void __cdecl sputLua_GetCameraLookVectorL(void); /* 0x0049f9b0 */
void __cdecl sputLua_PointActorAtL(void); /* 0x0049fb00 */
void __cdecl sputLua_TurnActorTo(void); /* 0x0049fc60 */
void __cdecl sputLua_PerSecondL(void); /* 0x0049fdf0 */
void __cdecl sputLua_SnapToPlane(void); /* 0x0049fe40 */
void __cdecl sputLua_GetAngleBetweenVectorsL(void); /* 0x0049ff00 */
void __cdecl sputLua_GetAngleBetweenActorsL(void); /* 0x004a00a0 */
void __cdecl sputLua_SetAmbientLight(void); /* 0x004a0230 */
void __cdecl sputLua_FindLight(void); /* 0x004a0290 */
void __cdecl sputLua_TurnLightOn(void); /* 0x004a02f0 */
void __cdecl sputLua_IsLightOn(void); /* 0x004a0380 */
void __cdecl sputLua_SetLightType(void); /* 0x004a0400 */
void __cdecl sputLua_GetLightType(void); /* 0x004a0530 */
void __cdecl sputLua_SetLightPosition(void); /* 0x004a05e0 */
void __cdecl sputLua_GetLightPosition(void); /* 0x004a0760 */
void __cdecl sputLua_SetLightRotation(void); /* 0x004a0800 */
void __cdecl sputLua_GetLightRotation(void); /* 0x004a09a0 */
void __cdecl sputLua_SetLightAngles(void); /* 0x004a0a50 */
void __cdecl sputLua_GetLightAngles(void); /* 0x004a0b40 */
void __cdecl sputLua_PointLightAt(void); /* 0x004a0bd0 */
void __cdecl sputLua_SetLightIntensity(void); /* 0x004a0da0 */
void __cdecl sputLua_GetLightIntensity(void); /* 0x004a0e90 */
void __fastcall sputLua_ImGetMasterVol(undefined4 param_1); /* 0x004a13d0 */
void __cdecl sputLua_ImSetMasterVol(void); /* 0x004a1400 */
void __fastcall sputLua_ImGetSfxVol(undefined4 param_1); /* 0x004a1440 */
void __cdecl sputLua_ImSetSfxVol(void); /* 0x004a1470 */
void __fastcall sputLua_ImGetVoiceVol(undefined4 param_1); /* 0x004a14b0 */
void __cdecl sputLua_ImSetVoiceVol(void); /* 0x004a14e0 */
void __fastcall sputLua_ImGetMusicVol(undefined4 param_1); /* 0x004a1520 */
void __cdecl sputLua_ImSetMusicVol(void); /* 0x004a1550 */
void __cdecl sputLua_ImSetState(void); /* 0x004a1640 */
void __cdecl sputLua_ImSetCuePoint(void); /* 0x004a16d0 */
void __cdecl sputLua_ImGetMemoryFootprint(void); /* 0x004a17f0 */
void __cdecl sputLua_ImGetSoundCacheSize(void); /* 0x004a1820 */
void __cdecl sputLua_SetGamma(void); /* 0x004a1850 */
void __cdecl sputLua_SetActorWalkDominate(void); /* 0x004a1890 */
void __cdecl sputLua_SetActorConstrain(void); /* 0x004a1900 */
void __cdecl sputLua_RenderModeUser(void); /* 0x004a1970 */
void __cdecl sputLua_DimScreen(void); /* 0x004a19f0 */
void __cdecl sputLua_DimRegion(void); /* 0x004a1a00 */
void __cdecl sputLua_SetSpeechMode(void); /* 0x004a1ae0 */
void __cdecl sputLua_GetSpeechMode(void); /* 0x004a1b40 */
void __cdecl sputLua_ActorShadow(void); /* 0x004a1b80 */
void __cdecl sputLua_ActivateActorShadow(void); /* 0x004a1bf0 */
void __cdecl sputLua_SetActorShadowPlane(void); /* 0x004a1c90 */
void __cdecl sputLua_SetActorShadowPoint(void); /* 0x004a1d10 */
void __cdecl sputLua_SetActiveShadow(void); /* 0x004a1dc0 */
void __cdecl sputLua_ActorDistToShadowPlane(void); /* 0x004a1e50 */
void __cdecl sputLua_AddShadowClipPlane(void); /* 0x004a1f30 */
void __cdecl sputLua_SetActorShadowValid(void); /* 0x004a1fd0 */
void __cdecl sputLua_KillActorShadows(void); /* 0x004a2070 */
void __cdecl sputLua_SetShadowColor(void); /* 0x004a20d0 */
void __cdecl sputLua_NewObjectState(void); /* 0x004a2130 */
void __cdecl sputLua_FreeObjectState(void); /* 0x004a21f0 */
void __cdecl sputLua_SendObjectToBack(void); /* 0x004a2240 */
void __cdecl sputLua_SendObjectToFront(void); /* 0x004a22b0 */
void __cdecl sputLua_SetObjectType(void); /* 0x004a2320 */
void __cdecl sputLua_ActorToClean(void); /* 0x004a2380 */
void __cdecl sputLua_SetActorCollisionMode(void); /* 0x004a23e0 */
void __cdecl sputLua_SetActorCollisionScale(void); /* 0x004a2470 */
void __cdecl sputLua_SetActorOffsetYaw(void); /* 0x004a2500 */
void __cdecl sputLua_CacheRect(void); /* 0x004a2590 */
void __cdecl sputLua_RestoreCacheRect(void); /* 0x004a26b0 */
void __fastcall sputLua_ResReport(undefined4 param_1); /* 0x004a26f0 */
void __cdecl sputLua_HardwareAccelerated(void); /* 0x004a2720 */
void __cdecl sputLua_SetActorClipActive(void); /* 0x004a2750 */
void __cdecl sputLua_SetActorClipPlane(void); /* 0x004a27b0 */
void __cdecl sputLua_MarkDirtyRect(void); /* 0x004a2920 */
void __cdecl sputLua_FadeOutChore(void); /* 0x004a2a20 */
void __cdecl sputLua_IrisDown(void); /* 0x004a2c10 */
void __cdecl sputLua_IrisUp(void); /* 0x004a2c70 */
void __fastcall sputLua_IrisComplete(undefined4 param_1); /* 0x004a2cd0 */
void __cdecl Lua_TextFileGetLineCount(void); /* 0x004a2d00 */
void __cdecl Lua_TextFileGetLine(void); /* 0x004a2e20 */
void __cdecl sputLua_ScreenShot(void); /* 0x004a2ee0 */
void __cdecl sputLua_SaveScreen(void); /* 0x004a2f90 */
void __cdecl sputLua_GetSaveGameImage(void); /* 0x004a2fd0 */
void __cdecl sputLua_GetImage(void); /* 0x004a3040 */
void __cdecl sputLua_FreeImage(void); /* 0x004a30e0 */
void __cdecl sputLua_BlastImage(void); /* 0x004a3130 */
void __cdecl sputLua_BlastRect(void); /* 0x004a31f0 */
void __cdecl sputLua_SaveGameCallback(void *writeFn); /* 0x004a34c0 */
void __cdecl sputLua_GetSaveGameData(void); /* 0x004a3720 */
void __fastcall sputLua_GetTextSpeed(undefined4 param_1); /* 0x004a3830 */
void __cdecl sputLua_SetTextSpeed(void); /* 0x004a3850 */
void __cdecl sputLua_FindFileOnAnyCD(void); /* 0x004a3890 */
void __cdecl sputLua_ActorPuckOrient(void); /* 0x004a3a10 */
void __cdecl sputLua_GetTickCount(void); /* 0x004a3aa0 */
void __cdecl sputLua_SetActorInvClipNode(void); /* 0x004a3ae0 */
void __cdecl sputLua_SetWalkSystemFadeTime(void); /* 0x004a3b80 */
void __cdecl Lua_LightMgrStartup(void); /* 0x004be180 */
void __cdecl Lua_LightMgrSetChange(void); /* 0x004be260 */
void __cdecl Lua_LightMgrShutdown(void); /* 0x004be2a0 */

/* ===== choreface.c ===== */
int __cdecl ChoreFace_Toggle(int show); /* 0x00402120 */
uint __cdecl FUN_00402200(void); /* 0x00402200 */
void __cdecl ChoreFace_OnCommand(uint param_1,int param_2); /* 0x00402290 */

/* ===== stddisplay.c ===== */
void __cdecl Display_Shutdown3D(void); /* 0x00402580 */
int __cdecl Display_Select(int deviceIdx,int modeIdx,int threeDIdx); /* 0x004025b0 */
int __cdecl Display_Select3DDevice(int threeDNum); /* 0x00402860 */
undefined * Display_InitFromConfig(void); /* 0x00402930 */
int __cdecl Display_GetLastFromRegistry(uint *deviceIdx,uint *modeIdx,uint *threeDIdx); /* 0x004029b0 */
int __cdecl Display_PickDefault(int wantFullscreen,int want3D,int *deviceIdx,int *modeIdx,int *threeDIdx); /* 0x00402b60 */
void __cdecl stdDisplay_BuildBitmapInfo8(int param_1,uint param_2,int param_3,int param_4,undefined1 *param_5); /* 0x004730d0 */
void __cdecl stdDisplay_BuildBitmapInfo16(int param_1,uint param_2,int param_3,int param_4); /* 0x00473180 */
undefined * __cdecl DIB_CreateSection565(uint param_1,uint param_2,int param_3,uint param_4); /* 0x004731f0 */
uint __cdecl Palette_SwapRedBlue(int param_1,undefined1 *param_2); /* 0x00473270 */
int __cdecl stdDisplay_Startup(void); /* 0x00473a40 */
void __cdecl stdDisplay_Shutdown(void); /* 0x00473b30 */
int __cdecl Display_SelectDevice(int deviceIdx); /* 0x00473c80 */
void __cdecl stdDisplay_Close(void); /* 0x00474100 */
int __cdecl Display_OpenMode(uint modeIdx,void *palette,int use3D); /* 0x00474140 */
void __cdecl stdDisplay_ClearMode(void); /* 0x00474310 */
void __cdecl Display_SuspendForDialog(void); /* 0x00474380 */
void __cdecl Display_ResumeAfterDialog(void); /* 0x004743d0 */
int __cdecl stdDisplay_Update(void); /* 0x00474420 */
void * __cdecl stdDisplay_VBufferNew(void *info,int videoMem,int b,int c); /* 0x00474480 */
void __cdecl stdDisplay_VBufferFree(void *surface); /* 0x004746d0 */
void __cdecl Surface_Release(void *surface); /* 0x004746f0 */
int __cdecl stdDisplay_VBufferLock(void *surface); /* 0x00474750 */
int __cdecl stdDisplay_VBufferUnlock(void *surface); /* 0x004747b0 */
int __cdecl Surface_Fill(void *surface,int color,int *rect); /* 0x00474800 */
int __cdecl Surface_Blit(void *dst,void *src,int x,int y,int *srcRect,int colorKey); /* 0x00474a60 */
int __cdecl stdDisplay_VBufferSetColorKey(void *surface,int color); /* 0x00474ae0 */
void __cdecl stdDisplay_VBufferDeCompress(void *surface); /* 0x00474b30 */
int __cdecl stdDisplay_VBufferDeCompressTo(void *src,void *dst); /* 0x00474ba0 */
void * __cdecl stdDisplay_VBufferConvertColorFormat(int *param_1,void *param_2); /* 0x00474be0 */
int __cdecl stdDisplay_SetPalette(uint param_1); /* 0x00474d10 */
void __cdecl stdDisplay_SetMasterPalette(void *palette); /* 0x00474d90 */
int __cdecl Palette_ApplyGamma(void *dst,void *src,int count,int gammaIdx); /* 0x00474dd0 */
int __cdecl stdDisplay_TextOut(char *text,int x,int y); /* 0x00474e40 */
uint __cdecl Display_FindClosestDevice(uint *param_1); /* 0x00475000 */
uint __cdecl Display_FindClosestMode(void *wanted,void *modes,uint count); /* 0x00475090 */
int __cdecl Display_CompareVideoModes(int *param_1,int *param_2); /* 0x00475140 */
int __cdecl Surface_BlitSoftware(void *dst,void *src,uint x,uint y,int *srcRect,uint flags); /* 0x004751b0 */
uint __cdecl Surface_BlitDDraw(int param_1,int param_2,uint param_3,uint param_4,uint *param_5,byte param_6); /* 0x004755e0 */
uint __cdecl Surface_BlitLockedSrc (void *param_1,int param_2,void *param_3,uint param_4,int *param_5,void *param_6); /* 0x004758a0 */
uint __cdecl Surface_BlitLockedDst (int param_1,void *param_2,void *param_3,uint param_4,int *param_5,void *param_6); /* 0x00475c90 */
int __cdecl DDraw_Create(uint param_1); /* 0x004760d0 */
void __cdecl DDraw_Release(void); /* 0x00476190 */
undefined * __stdcall FUN_004761b0(int a1,int a2,int a3,int a4); /* 0x004761b0 */
undefined * __stdcall DDraw_EnumModesCallback(int a1,int a2); /* 0x00476390 */
undefined * __stdcall DDraw_EnumModesCallback320(int a1,int a2); /* 0x004765a0 */
void * __cdecl DDraw_Get(void); /* 0x004767c0 */
undefined4 __cdecl DDraw_CreateSurfaces(undefined4 hwnd,int *mode,byte *palette); /* 0x004767d0 */
void __cdecl DDraw_ReleaseSurfaces(void); /* 0x00476bc0 */
uint __cdecl DDraw_LockSurface(undefined4 *param_1); /* 0x00476bf0 */
uint __cdecl DDraw_UnlockSurface(undefined4 *param_1); /* 0x00476c40 */
uint __cdecl DDraw_Flip(void); /* 0x00476c90 */
uint __cdecl DDraw_FillSurface(undefined4 *param_1,uint param_2,uint *param_3); /* 0x00476cd0 */
uint __cdecl DDraw_SetPalette(undefined1 *param_1); /* 0x00476dc0 */
void * __cdecl DIB_CreateSurface(void *mode,void *surface,void *palette,void *hwnd); /* 0x00476e40 */
void __cdecl DIB_ReleaseSurface(void); /* 0x00476ee0 */
void __cdecl std3D_SetCurrentPalette(void *palette,int flags); /* 0x00478fc0 */
void __cdecl Palette_FromFloatTable(byte *out,byte *in,int n,double gamma); /* 0x0047b610 */
void __cdecl stdColor_ColorConvertOneRow(ushort *dst,int dstFormat,ushort *src,int srcFormat,uint count); /* 0x0047b8a0 */
int __cdecl stdColor_ColorConvertOnePixel(int param_1,uint param_2,int param_3); /* 0x0047bbb0 */

/* ===== services.c ===== */
uint __cdecl defaultStatusPrint(char *fmt,...); /* 0x004035b0 */
uint __cdecl defaultMessagePrint(char *fmt,...); /* 0x004035e0 */
uint __cdecl defaultWarningPrint(char *fmt,...); /* 0x00403610 */
uint __cdecl defaultErrorPrint(char *fmt,...); /* 0x00403640 */
uint __cdecl defaultDebugPrint(char *fmt,...); /* 0x00403670 */
void __cdecl defaultAssert(char *expr,char *file,int line); /* 0x004036a0 */
void __cdecl defaultAtExit(uint param_1); /* 0x004036d0 */
void * __cdecl Svc_Realloc(void *p,uint size); /* 0x004036e0 */
void * __cdecl defaultFileOpen(char *name,char *mode); /* 0x00403710 */
void __cdecl defaultFileClose(uint param_1); /* 0x00403730 */
int __cdecl defaultFileRead(void *file,void *buf,int size); /* 0x00403740 */
char * __cdecl defaultFileGets(void *file,char *buf,int size); /* 0x00403760 */
int __cdecl defaultFileWrite(void *file,void *buf,int size); /* 0x00403780 */
uint __cdecl defaultFileEOF(int param_1); /* 0x004037a0 */
void __cdecl defaultFileTell(uint param_1); /* 0x004037b0 */
int __cdecl defaultFileSeek(void *file,int offset,int whence); /* 0x004037c0 */
int __cdecl defaultFileSize(char *name); /* 0x004037e0 */
void __cdecl defaultFilePrintf(void *fp,char *fmt,...); /* 0x00403830 */
void * __cdecl Svc_Malloc(uint size); /* 0x00403850 */
void __cdecl Svc_Free(void *p); /* 0x00403860 */
uint __cdecl defaultLockHandle(uint param_1); /* 0x00403870 */
void __cdecl HostServicesInitialize(GrimServices *svc); /* 0x00403880 */
void __cdecl stdStartup(GrimServices *svc); /* 0x004733a0 */
void __cdecl stdShutdown(void); /* 0x00473400 */
void __cdecl stdInitServices(GrimServices *param_1); /* 0x00473420 */
undefined4 __cdecl stdPlatform_Printf(char *fmt,...); /* 0x00478000 */
void __cdecl stdPlatform_InitServices(GrimServices *svc); /* 0x00478080 */

/* ===== reg.c ===== */
void __cdecl Reg_Open(void *param_1,uint param_2,char *param_3); /* 0x004038a0 */
void __cdecl Reg_CacheValueNames(void); /* 0x004039a0 */
void __cdecl wuRegistry_Shutdown(void); /* 0x00403b20 */
void __cdecl Reg_FreeValueNames(void); /* 0x00403b30 */
int __cdecl Reg_SetInt(char *name,int value); /* 0x00403b80 */
int __cdecl Reg_AddValueName(char *name); /* 0x00403bf0 */
int __cdecl Reg_HasValue(char *name); /* 0x00403cf0 */
int __cdecl wuRegistry_SaveFloat(char *name,float value); /* 0x00403d90 */
int __cdecl Reg_GetInt(char *name,int defaultValue); /* 0x00403e00 */
float __cdecl wuRegistry_GetFloat(char *name,float defaultValue); /* 0x00403e90 */
int __cdecl Reg_SetBinary(char *name,void *data,int size); /* 0x00403f20 */
int __cdecl Reg_GetBinary(char *name,void *data,int size); /* 0x00403f90 */
void __cdecl wuRegistry_SaveStr(char *name,char *value); /* 0x00404010 */
int __cdecl wuRegistry_GetStr(char *name,char *buf,int size,char *defaultValue); /* 0x00404070 */
int __cdecl wuRegistry_QueryType(char *name); /* 0x00404120 */

/* ===== string.c ===== */
int __cdecl Str_ComparePtrs(undefined4 *param_1,undefined4 *param_2); /* 0x00403ae0 */
char * __cdecl stdFileFromPath(char *path); /* 0x004735b0 */
void __cdecl Str_ToLower(char *s); /* 0x0047b5c0 */
char * __cdecl stdFnames_FindMedName(char *path); /* 0x0047fd20 */
char * __cdecl stdFnames_FindExt(char *path); /* 0x0047fd50 */
void __cdecl Str_StripExtension(char *param_1); /* 0x0047fda0 */
void __cdecl stdFnames_CopyShortName(char *dst,int size,char *path); /* 0x0047fdc0 */
undefined * __cdecl Str_FindChar(char *param_1,int param_2); /* 0x004838c0 */
uint * __cdecl String_ContainsSubstring(uint *param_1,char *param_2); /* 0x004aef70 */
byte * __cdecl FindMatch(char *str,char *pattern); /* 0x004c1c30 */
int __cdecl Str_ModuleNameLength(byte *param_1); /* 0x004c1e00 */
void __cdecl Str_StripNonPrintable(byte *param_1); /* 0x004c1e60 */
int __cdecl Str_CompareNoCase(char *param_1,char *param_2); /* 0x004c1e90 */
int __cdecl Str_CompareNoCaseN(char *param_1,char *param_2,int param_3); /* 0x004c1ee0 */

/* ===== rdroid.c ===== */
int __cdecl rdStartup(GrimServices *svc); /* 0x00404180 */
void __cdecl rdShutdown(void); /* 0x004041c0 */
int __cdecl rdOpen(int flags); /* 0x004041e0 */
void __cdecl rdClose(void); /* 0x00404270 */
void __cdecl rdSetRenderOptions(uint param_1); /* 0x00404290 */
void __cdecl rdSetGeometryMode(int param_1); /* 0x004042a0 */
void __cdecl rdSetLightingMode(int param_1); /* 0x004042b0 */
void __cdecl rdSetTextureMode(int param_1); /* 0x004042c0 */
void __cdecl rdSetSortingMethod(int param_1); /* 0x004042d0 */
void __cdecl rdSetOcclusionMethod(int param_1); /* 0x004042e0 */
void __cdecl rdSetZBufferMethod(int param_1); /* 0x004042f0 */
void rdAdvanceFrame(void); /* 0x00404300 */
void __cdecl rdFinishFrame(void); /* 0x00404320 */
void rdClearPreStatistics(void); /* 0x00404330 */
uint __cdecl rdroid_SetColormap(uint param_1); /* 0x00404350 */
void __cdecl rdRaster_Startup(void); /* 0x00404b80 */

/* ===== rdcolormap.c ===== */
uint __cdecl rdColormap_SetCurrent(uint param_1); /* 0x00404380 */
void * __cdecl rdColormap_Load(char *name); /* 0x004043c0 */
int __cdecl rdColormap_LoadEntry(char *name,void *cmp); /* 0x00404420 */
void __cdecl rdColormap_Free(uint param_1); /* 0x00404730 */
void __cdecl rdColormap_FreeEntry(int param_1); /* 0x00404750 */
undefined8 __cdecl rdColormap_BuildRGB16 (undefined2 *param_1,ushort *param_2,uint param_3,uint param_4,uint param_5,int param_6); /* 0x004047e0 */
uint __cdecl rdColormap_BuildGrayRamp(undefined4 *param_1); /* 0x00404a40 */
int __cdecl rdColormap_Size(int param_1); /* 0x00404b30 */

/* ===== rdcanvas.c ===== */
void __cdecl rdActive_AdvanceFrame(void); /* 0x00404c00 */
void __cdecl rdActive_ClearFrameCounters(void); /* 0x00404ca0 */
void rdActive_DrawScene(void); /* 0x00404cb0 */
void __cdecl rdActive_BuildSpans(void); /* 0x00404e00 */
void __cdecl rdActive_FlushSpans(void); /* 0x004055d0 */
void __cdecl rdActive_BuildEdges(void); /* 0x00405620 */
uint __cdecl rdActive_AddActiveFace(byte *param_1); /* 0x00405770 */
void __cdecl rdCanvas_DrawLine(void *canvas,int x0,int y0,int x1,int y1,ushort color,uint pattern); /* 0x00451950 */
void __cdecl rdCanvas_DrawPoint(void *param_1,int param_2,int param_3,uint param_4,float param_5,int param_6, int param_7); /* 0x00451dd0 */
uint * __cdecl rdCanvas_New(uint param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6, uint param_7,uint param_8); /* 0x004c04f0 */
int __cdecl rdCanvas_NewEntry(uint *canvas,uint flags,uint surface,uint zSurface,uint x0,uint y0,uint x1,uint y1 ,uint extra); /* 0x004c0550 */
void __cdecl rdCanvas_Free(int param_1); /* 0x004c0610 */

/* ===== rdcache.c ===== */
void __cdecl rdCache_AdvanceFrame(void); /* 0x00406650 */
void __cdecl rdCache_FinishFrame(void); /* 0x00406660 */
void __cdecl rdCache_Reset(void); /* 0x00406670 */
void __cdecl rdCache_ClearFrameCounters(void); /* 0x00406690 */
undefined1 * __cdecl rdCache_GetProcEntry(void); /* 0x004066a0 */
void __cdecl rdCache_Flush(void); /* 0x00406770 */
int __cdecl rdCache_AddProcFace(void *mesh,uint vertexCount,byte flags); /* 0x00406860 */
uint __cdecl rdCache_SendFaceListToHardware(void); /* 0x00406aa0 */
void __cdecl std3D_ResetRenderList(void); /* 0x00407ed0 */
void __cdecl rdCache_DrawRenderList(void); /* 0x00407ef0 */
int __cdecl rdCache_TriCompare(int param_1,int param_2); /* 0x00407f90 */
int __cdecl rdCache_DrawFaceN(void *mesh); /* 0x00407fd0 */
uint __cdecl FUN_00408800(void); /* 0x00408800 */
int __cdecl rdCache_DrawFaceZ(void *mesh); /* 0x00408af0 */

/* ===== rdmodel.c ===== */
uint __cdecl rdCache_DrawFaceUser(byte *param_1); /* 0x00409580 */
uint __cdecl rdCache_ProcFaceCompare(int param_1,int param_2); /* 0x00409d20 */
void __cdecl rdModel3_DrawHNode(int param_1); /* 0x0040d140 */
void __cdecl rdModel3_DrawMeshImpl(void *mesh,float *matrix); /* 0x0040d230 */
uint __cdecl rdModel3_DrawFace(int param_1,int param_2); /* 0x0040d880 */

/* ===== rdprimit3.c ===== */
void * __cdecl rdCache_InsertFace(float *verts,int count,void *material); /* 0x00409d50 */
undefined4 __cdecl rdPrimit3_DrawLine(float *a,float *b,int *outA,int *outB,int *clipA,int *clipB,uint color, uint pattern); /* 0x0040dcc0 */
void __cdecl rdPrimit3_DrawPoint(float *world,float radius,uint a3,uint a4,uint a5); /* 0x0040dde0 */
void __cdecl rdPrimit3_ClipFace(uint param_1,uint param_2,int param_3,uint param_4,uint *param_5,uint *param_6, float *param_7); /* 0x0040deb0 */
void __cdecl rdPrimit3_NoClipFace (uint param_1,int param_2,uint param_3,uint *param_4,uint *param_5,float *param_6); /* 0x0040e500 */

/* ===== rdcamera.c ===== */
void * __cdecl rdCamera_New(float fov,int type,float aspectX,float aspectY,float zoom); /* 0x00409f50 */
int __cdecl rdCamera_NewEntry(void *camera,float fov,int projType,float aspectX,float aspectY,float zoom); /* 0x00409fb0 */
void __cdecl rdCamera_Free(int param_1); /* 0x0040a080 */
void __cdecl rdCamera_FreeEntry(int param_1); /* 0x0040a0a0 */
void __cdecl rdCamera_SetCanvas(void *camera,void *canvas); /* 0x0040a0c0 */
uint __cdecl rdCamera_SetCurrent(void *param_1); /* 0x0040a0e0 */
void __cdecl rdCamera_SetFOV(void *camera,float fov); /* 0x0040a100 */
int __cdecl rdCamera_SetProjectType(void *camera,int type); /* 0x0040a150 */
void __cdecl rdCamera_SetAspectRatio(void *camera,float zoom); /* 0x0040a1d0 */
uint __cdecl rdCamera_BuildFOV(int *param_1); /* 0x0040a280 */
void __cdecl rdCamera_Update(float *frame); /* 0x0040a430 */
void __cdecl rdCamera_OrthoProject(float *param_1,float *param_2); /* 0x0040a470 */
void __cdecl rdCamera_OrthoProjectLst(float *param_1,float *param_2,int param_3); /* 0x0040a4b0 */
void __cdecl rdCamera_OrthoProjectSquare(float *param_1,float *param_2); /* 0x0040a530 */
void __cdecl rdCamera_OrthoProjectSquareLst(float *param_1,float *param_2,int param_3); /* 0x0040a570 */
void __cdecl rdCamera_PerspProject(float *param_1,float *param_2); /* 0x0040a5e0 */
void __cdecl rdCamera_PerspProjectLst(float *param_1,float *param_2,int param_3); /* 0x0040a620 */
void __cdecl rdCamera_PerspProjectSquare(float *param_1,float *param_2); /* 0x0040a6a0 */
void __cdecl rdCamera_PerspProjectSquareLst(float *param_1,float *param_2,int param_3); /* 0x0040a6e0 */
void __cdecl rdCamera_SetAmbientLight(void *camera,float ambient); /* 0x0040a750 */
void __cdecl rdCamera_AddLight(void *camera,void *light,float *pos); /* 0x0040a760 */
void __cdecl rdCamera_AdvanceFrame(void); /* 0x0040a7d0 */
void __cdecl rdModel3_ClearFrameCounters(void); /* 0x0040a860 */
int __cdecl rdPrimit3_GetScreenCoord(float *world,ScreenCoord *outScreen); /* 0x0040dc30 */

/* ===== renderer.c ===== */
void __cdecl rdModel3_ActivateClipPlane(uint param_1); /* 0x0040a870 */
void __cdecl rdModel3_SetClipPlane(undefined4 *param_1,undefined4 *param_2); /* 0x0040a880 */

/* ===== rdmodel3.c ===== */
void __cdecl rdModel3_NewEntry(undefined4 *param_1); /* 0x0040a8c0 */
undefined4 * __cdecl rdModel3_Load(uint param_1); /* 0x0040a8f0 */
uint __cdecl rdModel3_LoadEntry(int param_1,uint param_2); /* 0x0040a980 */
uint __cdecl rdModel3_LoadEntryText (uint param_1,uint param_2,uint param_3,int param_4,uint param_5,uint param_6,uint param_7 ,uint param_8); /* 0x0040aa20 */
uint __cdecl rdModel3_LoadEntryBinary(int param_1,int param_2); /* 0x0040b8e0 */
void __cdecl rdModel3_LoadPostProcess(uint param_1); /* 0x0040c090 */
void __cdecl rdModel3_Free(int param_1); /* 0x0040c0d0 */
void __cdecl rdModel3_FreeEntry(int param_1); /* 0x0040c100 */
void __cdecl rdModel3_BuildShadowModel(int param_1); /* 0x0040c280 */
void __cdecl rdModel3_CalcBoundingBoxes(uint param_1); /* 0x0040c520 */
void __cdecl rdModel3_CalcModelBoundingBox(int param_1,int param_2,float *param_3); /* 0x0040c710 */
void __cdecl rdModel3_CalcRadii(int param_1); /* 0x0040c8c0 */
void __cdecl rdModel3_BuildExpandedRadius(int param_1,int param_2,float *param_3); /* 0x0040c970 */
void __cdecl rdModel3_CalcFaceNormals(uint param_1); /* 0x0040cad0 */
void __cdecl rdModel3_CalcVertexNormals(int param_1); /* 0x0040cc30 */
void __cdecl rdModel3_CountNodeChildren(int param_1); /* 0x0040ce90 */

/* ===== rdpuppet.c ===== */
void __cdecl rdPuppet_BuildJointMatrices(void *model,float *frame,uint index,float *out); /* 0x0040cee0 */
undefined4 * __cdecl rdPuppet_New(void *param_1); /* 0x00450500 */
int __cdecl rdPuppet_NewEntry(void *puppet,void *thing); /* 0x00450560 */
uint __cdecl rdPuppet_AddTrack(void *puppet,uint keyframe,uint lowPri,uint highPri); /* 0x004505a0 */
void __cdecl rdPuppet_RemoveTrack(void *puppet,int track); /* 0x00450640 */
uint __cdecl rdPuppet_SetStatus(int param_1,int param_2,uint param_3); /* 0x004506a0 */
void __cdecl rdPuppet_SetCallback(int param_1,int param_2,uint param_3); /* 0x004506d0 */
uint __cdecl rdPuppet_PlayTrack(int param_1,int param_2); /* 0x004506f0 */
int __cdecl rdPuppet_FadeInTrack(void *puppet,int track,float seconds); /* 0x00450720 */
int __cdecl rdPuppet_FadeOutTrack(void *puppet,int track,float seconds); /* 0x00450780 */
void __cdecl rdPuppet_AdvanceTrack(void *puppet,int track,float dt); /* 0x004507e0 */
void __cdecl rdPuppet_UpdateTracks(void *puppet,float seconds); /* 0x00450a90 */
void __cdecl rdPuppet_ResetTrack(int param_1,int param_2); /* 0x00450b50 */
void __cdecl rdPuppet_UpdateFrame(void *model,float *frame); /* 0x00450ba0 */
void __cdecl rdKeyframe_NewEntry(undefined4 *param_1); /* 0x004c0630 */
int __cdecl rdKeyframe_Load(char *param_1); /* 0x004c0660 */
uint __cdecl rdKeyframe_LoadEntry(char *param_1,int param_2); /* 0x004c0770 */
uint __cdecl rdKeyframe_LoadEntryBinary(uint param_1,int param_2); /* 0x004c0ce0 */
void __cdecl rdKeyframe_Free(int param_1); /* 0x004c0e40 */
void __cdecl rdKeyframe_FreeEntry(int param_1); /* 0x004c0e70 */

/* ===== rdthing.c ===== */
int __cdecl rdModel3_Draw(void *thing,float *position); /* 0x0040cf20 */
uint __cdecl rdThing_New(uint param_1); /* 0x00471a40 */
uint __cdecl rdThing_NewEntry(undefined4 *param_1,uint param_2); /* 0x00471a80 */
void __cdecl rdThing_Free(int param_1); /* 0x00471af0 */
void __cdecl rdThing_FreeEntry(int *param_1); /* 0x00471b10 */
void __cdecl rdThing_SetModel3(void *thing,void *model); /* 0x00471bd0 */
uint __cdecl rdThing_SetCamera(undefined4 *param_1,uint param_2); /* 0x00471d40 */
uint __cdecl rdThing_SetPolyline(undefined4 *param_1,uint param_2); /* 0x00471d60 */
int __cdecl rdThing_Draw(void *thing,float *frame); /* 0x00471d80 */
void __cdecl rdThing_AccumulateMatrices(int param_1,int param_2,float *param_3); /* 0x00471e00 */

/* ===== rdraster.c ===== */
void __cdecl rdAFRaster_CalcAffineGradients(float *param_1,int param_2); /* 0x0040ea50 */
void __cdecl rdAFRaster_CalcPerspGradients(float *param_1,int param_2); /* 0x0040ef90 */
void __cdecl rdAFRaster_SetupNGonLW(float *param_1,int param_2); /* 0x0040f5f0 */
void __cdecl rdAFRaster_DrawNGonLW(int *param_1); /* 0x0040f650 */
void __cdecl rdAFRaster_DrawSpanNGonLW_8(int *param_1); /* 0x0040f6d0 */
void __cdecl rdAFRaster_DrawSpanNGonLW_16(int *param_1); /* 0x0040f710 */
void __cdecl rdRaster_EdgeStepFlat(int param_1); /* 0x0040f750 */
uint __cdecl rdAFRaster_SetupEdgeNGonLW(uint *param_1,int *param_2,int param_3,int param_4); /* 0x0040f770 */
void __cdecl rdAFRaster_SetupNGonLS(float *param_1,int param_2); /* 0x0040fa20 */
void __cdecl rdAFRaster_DrawNGonLS(int *param_1); /* 0x0040fa80 */
uint __cdecl rdAFRaster_SetupEdgeNGonLS(uint *param_1,int *param_2,int param_3,int param_4); /* 0x0040fbe0 */
void __cdecl rdAFRaster_SetupNGonFS(float *param_1,int param_2,float param_3); /* 0x0040fe90 */
void __cdecl rdAFRaster_DrawNGonFS(int param_1); /* 0x0040ff20 */
uint __cdecl rdAFRaster_SetupEdgeNGonFS(uint *param_1,int *param_2,int param_3,int param_4); /* 0x0040ffe0 */
void __cdecl rdAFRaster_SetupNGonGS(float *param_1,int param_2); /* 0x00410290 */
void __cdecl rdAFRaster_DrawNGonGS(int param_1); /* 0x00410330 */
void __cdecl FUN_004104b0(int param_1); /* 0x004104b0 */
uint __cdecl rdAFRaster_SetupEdgeNGonGS(uint *param_1,int *param_2,int param_3,int param_4); /* 0x004104e0 */
void __cdecl rdAFRaster_SetupNGonLAT(int *param_1,int param_2); /* 0x004108b0 */
void __cdecl rdAFRaster_DrawNGonLAT(int param_1); /* 0x00410970 */
uint __cdecl rdAFRaster_SetupEdgeNGonLAT(uint *param_1,int *param_2,int param_3,int param_4); /* 0x00410d80 */
void __cdecl rdAFRaster_SetupNGonMLAT(int *param_1,int param_2); /* 0x00411270 */
void __cdecl rdAFRaster_DrawNGonMLAT(int param_1); /* 0x00411330 */
void __cdecl rdAFRaster_DrawSpanNGonMLAT_8(int *param_1); /* 0x004113e0 */
void __cdecl rdAFRaster_DrawSpanNGonMLAT_16(int *param_1); /* 0x004114f0 */
void __cdecl rdAFRaster_SetupNGonFAT(int *param_1,int param_2,float param_3); /* 0x00411630 */
void __cdecl rdAFRaster_DrawNGonFAT(int param_1); /* 0x00411740 */
void __cdecl FUN_00411b70(int param_1); /* 0x00411b70 */
uint __cdecl rdAFRaster_SetupEdgeNGonFAT(uint *param_1,int *param_2,int param_3,int param_4); /* 0x00411ba0 */
void __cdecl rdAFRaster_SetupNGonMFAT(int *param_1,int param_2,float param_3); /* 0x00412090 */
void __cdecl rdAFRaster_DrawNGonMFAT(int param_1); /* 0x004121a0 */
void __cdecl rdAFRaster_DrawSpanNGonMFAT_8(int *param_1); /* 0x00412280 */
void __cdecl rdAFRaster_DrawSpanNGonMFAT_16(int *param_1); /* 0x004123b0 */
void __cdecl rdAFRaster_SetupNGonGAT(int *param_1,int param_2); /* 0x004124f0 */
void __cdecl rdAFRaster_DrawNGonGAT(int param_1); /* 0x004125c0 */
void __cdecl FUN_004129f0(int param_1); /* 0x004129f0 */
uint __cdecl rdAFRaster_SetupEdgeNGonGAT(uint *param_1,int *param_2,int param_3,int param_4); /* 0x00412a30 */
void __cdecl rdAFRaster_SetupNGonMGAT(int *param_1,int param_2); /* 0x00413040 */
void __cdecl rdAFRaster_DrawNGonMGAT(int param_1); /* 0x00413110 */
void __cdecl rdAFRaster_DrawSpanNGonMGAT_8(int *param_1); /* 0x004131f0 */
void __cdecl rdAFRaster_DrawSpanNGonMGAT_16(int *param_1); /* 0x00413340 */
void __cdecl rdAFRaster_SetupNGonLIT(int *param_1,int param_2); /* 0x004134a0 */
void __cdecl rdAFRaster_DrawNGonLIT(int param_1); /* 0x00413590 */
uint __cdecl rdAFRaster_SetupEdgeNGonLIT(uint *param_1,int *param_2,int param_3,int param_4); /* 0x004139f0 */
void __cdecl rdAFRaster_SetupNGonMLIT(int *param_1,int param_2); /* 0x00413ce0 */
void __cdecl rdAFRaster_DrawNGonMLIT(int param_1); /* 0x00413dd0 */
void __cdecl rdAFRaster_DrawSpanNGonMLIT_8(uint *param_1); /* 0x00413ee0 */
void __cdecl rdAFRaster_DrawSpanNGonMLIT_16(uint *param_1); /* 0x00414530 */
void __cdecl rdAFRaster_SetupNGonFIT(int *param_1,int param_2,float param_3); /* 0x00414be0 */
void __cdecl rdAFRaster_DrawNGonFIT(int param_1); /* 0x00414d20 */
void __cdecl FUN_00415180(int param_1); /* 0x00415180 */
void __cdecl FUN_004151c0(int param_1); /* 0x004151c0 */
uint __cdecl rdAFRaster_SetupEdgeNGonFIT(uint *param_1,int *param_2,int param_3,int param_4); /* 0x004151d0 */
void __cdecl rdAFRaster_SetupNGonMFIT(int *param_1,int param_2,float param_3); /* 0x004154c0 */
void __cdecl rdAFRaster_DrawNGonMFIT(int param_1); /* 0x00415600 */
void __cdecl rdAFRaster_DrawSpanNGonMFIT_8(uint *param_1); /* 0x00415720 */
void __cdecl rdAFRaster_DrawSpanNGonMFIT_16(uint *param_1); /* 0x00415dc0 */
void __cdecl rdAFRaster_SetupNGonGIT(int *param_1,int param_2); /* 0x00416470 */
void __cdecl rdAFRaster_DrawNGonGIT(int param_1); /* 0x00416580 */
void __cdecl rdAFRaster_AdvanceLeftEdgeNGonGIT(int param_1); /* 0x004169f0 */
void __cdecl rdAFRaster_AdvanceRightEdgeNGonGIT(int param_1); /* 0x00416a30 */
uint __cdecl rdAFRaster_SetupEdgeNGonGIT(uint *param_1,int *param_2,int param_3,int param_4); /* 0x00416a50 */
uint __cdecl rdAFRaster_SetupNGonMGIT(int *param_1,int param_2); /* 0x00416e70 */
void __cdecl rdAFRaster_DrawNGonMGIT(int param_1); /* 0x00416f80 */
void __cdecl rdAFRaster_DrawSpanNGonMGIT_8(uint *param_1); /* 0x004170a0 */
void __cdecl rdAFRaster_DrawSpanNGonMGIT_16(uint *param_1); /* 0x00417790 */
void __cdecl rdNRaster_CalcAffineGradients(float param_1); /* 0x00418550 */
void __cdecl rdNRaster_CalcPerspGradients(float param_1); /* 0x00418a00 */
void __cdecl rdNRaster_DrawNGonLV(int param_1,int param_2); /* 0x00418fe0 */
void __cdecl rdNRaster_DrawNGonLW(int param_1,int param_2); /* 0x00419150 */
void __cdecl rdNRaster_DrawNGonLS(int param_1,int param_2); /* 0x00419450 */
void __cdecl rdNRaster_DrawScanLineNGonLS_16(uint *param_1,uint *param_2); /* 0x004195f0 */
uint __cdecl rdNRaster_SetupLeftEdgeNGonLS(int *param_1); /* 0x00419680 */
uint __cdecl rdNRaster_SetupRightEdgeNGonLS(int *param_1); /* 0x00419840 */
void __cdecl rdNRaster_DrawNGonTLS(int param_1,int param_2); /* 0x00419a00 */
void __cdecl rdNRaster_DrawScanLineNGonTLS_16(uint *param_1,uint *param_2); /* 0x00419be0 */
void __cdecl rdNRaster_DrawNGonFS(int param_1,int param_2,float param_3); /* 0x00419ca0 */
void __cdecl rdRaster_Span_Flat(uint *param_1,uint *param_2); /* 0x00419e60 */
void __cdecl rdNRaster_DrawScanLineNGonFS_16(uint *param_1,uint *param_2); /* 0x00419ee0 */
uint __cdecl rdNRaster_SetupLeftEdgeNGonFS(int *param_1); /* 0x00419f70 */
uint __cdecl rdNRaster_SetupRightEdgeNGonFS(int *param_1); /* 0x0041a130 */
void __cdecl rdNRaster_DrawNGonTFS(int param_1,int param_2,float param_3); /* 0x0041a2f0 */
void __cdecl rdRaster_Span_Tex(uint *param_1,uint *param_2); /* 0x0041a4f0 */
void __cdecl rdNRaster_DrawScanLineNGonTFS_16(uint *param_1,uint *param_2); /* 0x0041a580 */
void __cdecl rdNRaster_DrawNGonGS(int param_1,int param_2); /* 0x0041a640 */
void __cdecl rdNRaster_DrawScanLineNGonGS_8(uint *param_1,uint *param_2); /* 0x0041a810 */
void __cdecl rdNRaster_DrawScanLineNGonGS_16(uint *param_1,uint *param_2); /* 0x0041a900 */
uint __cdecl rdNRaster_SetupLeftEdgeNGonGS(int *param_1); /* 0x0041aa10 */
uint __cdecl rdNRaster_SetupRightEdgeNGonGS(int *param_1); /* 0x0041ac60 */
void __cdecl rdNRaster_DrawNGonTGS(int param_1,int param_2); /* 0x0041aeb0 */
void __cdecl rdNRaster_DrawScanLineNGonTGS_8(uint *param_1,uint *param_2); /* 0x0041b0d0 */
void __cdecl rdNRaster_DrawScanLineNGonTGS_16(uint *param_1,uint *param_2); /* 0x0041b1e0 */
void __cdecl rdNRaster_DrawNGonLAT(int param_1,int param_2); /* 0x0041b310 */
void __cdecl rdNRaster_DrawScanLineNGonLAT_8(uint *param_1,uint *param_2); /* 0x0041b6f0 */
void __cdecl rdNRaster_DrawScanLineNGonLAT_16(uint *param_1,uint *param_2); /* 0x0041b880 */
uint __cdecl rdNRaster_SetupLeftEdgeNGonLAT(int *param_1); /* 0x0041ba30 */
uint __cdecl rdNRaster_SetupRightEdgeNGonLAT(int *param_1); /* 0x0041bd20 */
void __cdecl rdNRaster_DrawNGonTLAT(int param_1,int param_2); /* 0x0041c010 */
void __cdecl rdNRaster_DrawScanLineNGonTLAT_8(uint *param_1,uint *param_2); /* 0x0041c260 */
void __cdecl rdNRaster_DrawScanLineNGonTLAT_16(uint *param_1,uint *param_2); /* 0x0041c410 */
void __cdecl rdNRaster_DrawNGonMLAT(int param_1,int param_2); /* 0x0041c5e0 */
void __cdecl rdNRaster_DrawScanLineNGonMLAT_8(uint *param_1,uint *param_2); /* 0x0041c810 */
void __cdecl rdNRaster_DrawScanLineNGonMLAT_16(uint *param_1,uint *param_2); /* 0x0041c9b0 */
void __cdecl rdNRaster_DrawNGonMTLAT(int param_1,int param_2); /* 0x0041cb80 */
void __cdecl rdNRaster_DrawScanLineNGonMTLAT_8(uint *param_1,uint *param_2); /* 0x0041cdd0 */
void __cdecl rdNRaster_DrawScanLineNGonMTLAT_16(uint *param_1,uint *param_2); /* 0x0041cf90 */
void __cdecl rdNRaster_DrawNGonFAT(int param_1,int param_2,float param_3); /* 0x0041d180 */
void __cdecl rdNRaster_DrawScanLineNGonFAT_16(uint *param_1,uint *param_2); /* 0x0041d560 */
uint __cdecl rdNRaster_SetupLeftEdgeNGonFAT(int *param_1); /* 0x0041d710 */
uint __cdecl rdNRaster_SetupRightEdgeNGonFAT(int *param_1); /* 0x0041da00 */
void __cdecl rdNRaster_DrawNGonTFAT(int param_1,int param_2,float param_3); /* 0x0041dcf0 */
void __cdecl rdNRaster_DrawScanLineNGonTFAT_8(uint *param_1,uint *param_2); /* 0x0041df60 */
void __cdecl rdNRaster_DrawScanLineNGonTFAT_16(uint *param_1,uint *param_2); /* 0x0041e120 */
void __cdecl rdNRaster_DrawNGonMFAT(int param_1,int param_2,float param_3); /* 0x0041e300 */
void __cdecl rdNRaster_DrawScanLineNGonMFAT_8(uint *param_1,uint *param_2); /* 0x0041e550 */
void __cdecl rdNRaster_DrawScanLineNGonMFAT_16(uint *param_1,uint *param_2); /* 0x0041e700 */
void __cdecl rdNRaster_DrawNGonMTFAT(int param_1,int param_2,float param_3); /* 0x0041e8d0 */
void __cdecl rdNRaster_DrawScanLineNGonMTFAT_8(uint *param_1,uint *param_2); /* 0x0041eb40 */
void __cdecl rdNRaster_DrawScanLineNGonMTFAT_16(uint *param_1,uint *param_2); /* 0x0041ed10 */
void __cdecl rdNRaster_DrawNGonGAT(int param_1,int param_2); /* 0x0041eef0 */
void __cdecl rdNRaster_DrawScanLineNGonGAT_16(uint *param_1,uint *param_2); /* 0x0041f2f0 */
uint __cdecl rdNRaster_SetupLeftEdgeNGonGAT(int *param_1); /* 0x0041f520 */
uint __cdecl rdNRaster_SetupRightEdgeNGonGAT(int *param_1); /* 0x0041f890 */
void __cdecl rdNRaster_DrawNGonTGAT(int param_1,int param_2); /* 0x0041fc00 */
void __cdecl rdNRaster_DrawScanLineNGonTGAT_8(uint *param_1,uint *param_2); /* 0x0041fe90 */
void __fastcall FUN_0042003c(int param_1,int param_2); /* 0x0042003c */
void __cdecl rdNRaster_DrawScanLineNGonTGAT_16(uint *param_1,uint *param_2); /* 0x004200c0 */
void __cdecl rdNRaster_DrawNGonMGAT(int param_1,int param_2); /* 0x00420310 */
void __cdecl rdNRaster_DrawScanLineNGonMGAT_8(uint *param_1,uint *param_2); /* 0x00420580 */
void __cdecl rdNRaster_DrawScanLineNGonMGAT_16(uint *param_1,uint *param_2); /* 0x004207b0 */
void __cdecl rdNRaster_DrawNGonMTGAT(int param_1,int param_2); /* 0x004209f0 */
void __cdecl rdNRaster_DrawScanLineNGonMTGAT_8(uint *param_1,uint *param_2); /* 0x00420c80 */
void __cdecl rdNRaster_DrawScanLineNGonMTGAT_16(uint *param_1,uint *param_2); /* 0x00420ec0 */
void __cdecl rdNRaster_DrawNGonLIT(int param_1,int param_2); /* 0x00421120 */
void __cdecl rdNRaster_DrawScanLineNGonLIT_16(uint *param_1,uint *param_2); /* 0x00421510 */
uint __cdecl rdNRaster_SetupLeftEdgeNGonLIT(int *param_1); /* 0x00421b60 */
uint __cdecl rdNRaster_SetupRightEdgeNGonLIT(int *param_1); /* 0x00421dc0 */
void __cdecl rdNRaster_DrawNGonTLIT(int param_1,int param_2); /* 0x00421f80 */
void __cdecl rdNRaster_DrawScanLineNGonTLIT_8(uint *param_1,uint *param_2); /* 0x004221f0 */
void __cdecl rdNRaster_DrawScanLineNGonTLIT_16(uint *param_1,uint *param_2); /* 0x00422820 */
void __cdecl rdNRaster_DrawNGonMLIT(int param_1,int param_2); /* 0x00422f00 */
void __cdecl rdNRaster_DrawScanLineNGonMLIT_8(uint *param_1,uint *param_2); /* 0x00423150 */
void __cdecl rdNRaster_DrawScanLineNGonMLIT_16(uint *param_1,uint *param_2); /* 0x00423740 */
void __cdecl rdNRaster_DrawNGonMTLIT(int param_1,int param_2); /* 0x00423db0 */
void __cdecl rdNRaster_DrawScanLineNGonMTLIT_8(uint *param_1,uint *param_2); /* 0x00424020 */
void __cdecl rdNRaster_DrawScanLineNGonMTLIT_16(uint *param_1,uint *param_2); /* 0x00424670 */
void __cdecl rdNRaster_DrawNGonFIT(int param_1,int param_2,float param_3); /* 0x00424d50 */
void __cdecl rdNRaster_DrawScanLineNGonFIT_16(uint *param_1,uint *param_2); /* 0x00425150 */
uint __cdecl rdNRaster_SetupLeftEdgeNGonFIT(int *param_1); /* 0x004257a0 */
uint __cdecl rdNRaster_SetupRightEdgeNGonFIT(int *param_1); /* 0x00425a00 */
void __cdecl rdNRaster_DrawNGonTFIT(int param_1,int param_2,float param_3); /* 0x00425bc0 */
void __cdecl rdNRaster_DrawScanLineNGonTFIT_8(uint *param_1,uint *param_2); /* 0x00425e50 */
void __cdecl rdNRaster_DrawScanLineNGonTFIT_16(uint *param_1,uint *param_2); /* 0x004264a0 */
void __cdecl rdNRaster_DrawNGonMFIT(int param_1,int param_2,float param_3); /* 0x00426bc0 */
void __cdecl rdNRaster_DrawScanLineNGonMFIT_8(uint *param_1,uint *param_2); /* 0x00426e30 */
void __cdecl rdNRaster_DrawScanLineNGonMFIT_16(uint *param_1,uint *param_2); /* 0x00427470 */
void __cdecl rdNRaster_DrawNGonMTFIT(int param_1,int param_2,float param_3); /* 0x00427ae0 */
void __cdecl rdNRaster_DrawScanLineNGonMTFIT_8(uint *param_1,uint *param_2); /* 0x00427d70 */
void __cdecl rdNRaster_DrawScanLineNGonMTFIT_16(uint *param_1,uint *param_2); /* 0x004283f0 */
void __cdecl rdNRaster_DrawNGonGIT(int param_1,int param_2); /* 0x00428ae0 */
void __cdecl rdNRaster_DrawScanLineNGonGIT_16(uint *param_1,uint *param_2); /* 0x00428f00 */
uint __cdecl rdNRaster_SetupLeftEdgeNGonGIT(int *param_1); /* 0x00429870 */
uint __cdecl rdNRaster_SetupRightEdgeNGonGIT(int *param_1); /* 0x00429b70 */
void __cdecl rdNRaster_DrawNGonTGIT(int param_1,int param_2); /* 0x00429dc0 */
void __cdecl rdNRaster_DrawScanLineNGonTGIT_8(uint *param_1,uint *param_2); /* 0x0042a070 */
void __cdecl rdNRaster_DrawScanLineNGonTGIT_16(uint *param_1,uint *param_2); /* 0x0042a790 */
void __cdecl rdNRaster_DrawNGonMGIT(int param_1,int param_2); /* 0x0042af60 */
void __cdecl rdNRaster_DrawScanLineNGonMGIT_8(uint *param_1,uint *param_2); /* 0x0042b1f0 */
void __cdecl rdNRaster_DrawScanLineNGonMGIT_16(uint *param_1,uint *param_2); /* 0x0042b8e0 */
void __cdecl rdNRaster_DrawNGonMTGIT(int param_1,int param_2); /* 0x0042c010 */
void __cdecl rdNRaster_DrawScanLineNGonMTGIT_8(uint *param_1,uint *param_2); /* 0x0042c2c0 */
void __cdecl rdNRaster_DrawScanLineNGonMTGIT_16(uint *param_1,uint *param_2); /* 0x0042c9f0 */
void __cdecl rdZRaster_CalcAffineGradients(float param_1); /* 0x0042d190 */
void __cdecl rdZRaster_CalcPerspGradients(float param_1); /* 0x0042d5f0 */
void __cdecl rdZRaster_DrawNGonLV(int param_1,int param_2); /* 0x0042dba0 */
void __cdecl rdZRaster_DrawNGonLW(int param_1,int param_2); /* 0x0042dd10 */
void __cdecl rdZRaster_DrawNGonLS(int param_1,int param_2); /* 0x0042e010 */
void __cdecl rdZRaster_DrawScanLineNGonLS_8(uint *param_1,uint *param_2); /* 0x0042e200 */
void __cdecl rdZRaster_DrawScanLineNGonLS_16(uint *param_1,uint *param_2); /* 0x0042e320 */
uint __cdecl rdZRaster_SetupLeftEdgeNGonLS(int *param_1); /* 0x0042e440 */
uint __cdecl rdZRaster_SetupRightEdgeNGonLS(int *param_1); /* 0x0042e630 */
void __cdecl rdZRaster_DrawNGonTLS(int param_1,int param_2); /* 0x0042e820 */
void __cdecl rdZRaster_DrawScanLineNGonTLS_8(uint *param_1,uint *param_2); /* 0x0042ea50 */
void __cdecl rdZRaster_DrawScanLineNGonTLS_16(uint *param_1,uint *param_2); /* 0x0042eb90 */
void __cdecl rdZRaster_DrawNGonFS(int param_1,int param_2,float param_3); /* 0x0042ecf0 */
void __cdecl rdZRaster_DrawScanLineNGonFS_8(uint *param_1,uint *param_2); /* 0x0042ef00 */
void __cdecl rdZRaster_DrawScanLineNGonFS_16(uint *param_1,uint *param_2); /* 0x0042f020 */
uint __cdecl rdZRaster_SetupLeftEdgeNGonFS(int *param_1); /* 0x0042f140 */
uint __cdecl rdZRaster_SetupRightEdgeNGonFS(int *param_1); /* 0x0042f330 */
void __cdecl rdZRaster_DrawNGonTFS(int param_1,int param_2,float param_3); /* 0x0042f520 */
void __cdecl rdZRaster_DrawScanLineNGonTFS_8(uint *param_1,uint *param_2); /* 0x0042f770 */
void __cdecl rdZRaster_DrawScanLineNGonTFS_16(uint *param_1,uint *param_2); /* 0x0042f8b0 */
void __cdecl rdZRaster_DrawNGonGS(int param_1,int param_2); /* 0x0042fa10 */
void __cdecl rdZRaster_DrawScanLineNGonGS_8(uint *param_1,uint *param_2); /* 0x0042fc30 */
void __cdecl rdZRaster_DrawScanLineNGonGS_16(uint *param_1,uint *param_2); /* 0x0042fdc0 */
uint __cdecl rdZRaster_SetupLeftEdgeNGonGS(int *param_1); /* 0x0042ff50 */
uint __cdecl rdZRaster_SetupRightEdgeNGonGS(int *param_1); /* 0x004301d0 */
void __cdecl rdZRaster_DrawNGonTGS(int param_1,int param_2); /* 0x00430450 */
void __cdecl rdZRaster_DrawScanLineNGonTGS_8(uint *param_1,uint *param_2); /* 0x004306c0 */
void __cdecl rdZRaster_DrawScanLineNGonTGS_16(uint *param_1,uint *param_2); /* 0x00430860 */
void __cdecl rdZRaster_DrawNGonLAT(int param_1,int param_2); /* 0x00430a20 */
void __cdecl rdZRaster_DrawScanLineNGonLAT_8(uint *param_1,uint *param_2); /* 0x00430fd0 */
void __cdecl rdZRaster_DrawScanLineNGonLAT_16(uint *param_1,uint *param_2); /* 0x004311d0 */
uint __cdecl rdZRaster_SetupLeftEdgeNGonLAT(int *param_1); /* 0x00431400 */
uint __cdecl rdZRaster_SetupRightEdgeNGonLAT(int *param_1); /* 0x00431710 */
void __cdecl rdZRaster_DrawNGonTLAT(int param_1,int param_2); /* 0x00431a20 */
void __cdecl rdZRaster_DrawScanLineNGonTLAT_8(uint *param_1,uint *param_2); /* 0x00431c90 */
void __cdecl rdZRaster_DrawScanLineNGonTLAT_16(uint *param_1,uint *param_2); /* 0x00431eb0 */
void __cdecl rdZRaster_DrawNGonMLAT(int param_1,int param_2); /* 0x00432100 */
void __cdecl rdZRaster_DrawScanLineNGonMLAT_8(uint *param_1,uint *param_2); /* 0x00432350 */
void __cdecl rdZRaster_DrawScanLineNGonMLAT_16(uint *param_1,uint *param_2); /* 0x00432560 */
void __cdecl rdZRaster_DrawNGonMTLAT(int param_1,int param_2); /* 0x004327a0 */
void __cdecl rdZRaster_DrawScanLineNGonMTLAT_8(uint *param_1,uint *param_2); /* 0x00432a10 */
void __cdecl rdZRaster_DrawScanLineNGonMTLAT_16(uint *param_1,uint *param_2); /* 0x00432c40 */
void __cdecl rdZRaster_DrawNGonFAT(int param_1,int param_2,float param_3); /* 0x00432ea0 */
void __cdecl rdZRaster_DrawScanLineNGonFAT_8(uint *param_1,uint *param_2); /* 0x00433480 */
void __cdecl rdZRaster_DrawScanLineNGonFAT_16(uint *param_1,uint *param_2); /* 0x004336a0 */
uint __cdecl rdZRaster_SetupLeftEdgeNGonFAT(int *param_1); /* 0x004338d0 */
uint __cdecl rdZRaster_SetupRightEdgeNGonFAT(int *param_1); /* 0x00433be0 */
void __cdecl rdZRaster_DrawNGonTFAT(int param_1,int param_2,float param_3); /* 0x00433ef0 */
void __cdecl rdZRaster_DrawScanLineNGonTFAT_8(uint *param_1,uint *param_2); /* 0x00434180 */
void __cdecl rdZRaster_DrawScanLineNGonTFAT_16(uint *param_1,uint *param_2); /* 0x004343b0 */
void __cdecl rdZRaster_DrawNGonMFAT(int param_1,int param_2,float param_3); /* 0x00434610 */
void __cdecl rdZRaster_DrawScanLineNGonMFAT_8(uint *param_1,uint *param_2); /* 0x00434880 */
void __cdecl rdZRaster_DrawScanLineNGonMFAT_16(uint *param_1,uint *param_2); /* 0x00434aa0 */
void __cdecl rdZRaster_DrawNGonMTFAT(int param_1,int param_2,float param_3); /* 0x00434ce0 */
void __cdecl rdZRaster_DrawScanLineNGonMTFAT_8(uint *param_1,uint *param_2); /* 0x00434f70 */
void __cdecl rdZRaster_DrawScanLineNGonMTFAT_16(uint *param_1,uint *param_2); /* 0x004351a0 */
void __cdecl rdZRaster_DrawNGonGAT(int param_1,int param_2); /* 0x00435400 */
void __cdecl rdZRaster_DrawScanLineNGonGAT_8(uint *param_1,uint *param_2); /* 0x00435a00 */
void __cdecl rdZRaster_DrawScanLineNGonGAT_16(uint *param_1,uint *param_2); /* 0x00435c70 */
uint __cdecl rdZRaster_SetupLeftEdgeNGonGAT(int *param_1); /* 0x00435f60 */
uint __cdecl rdZRaster_SetupRightEdgeNGonGAT(int *param_1); /* 0x00436300 */
void __cdecl rdZRaster_DrawNGonTGAT(int param_1,int param_2); /* 0x004366a0 */
void __cdecl rdZRaster_DrawScanLineNGonTGAT_8(uint *param_1,uint *param_2); /* 0x00436950 */
void __cdecl rdZRaster_DrawScanLineNGonTGAT_16(uint *param_1,uint *param_2); /* 0x00436be0 */
void __cdecl rdZRaster_DrawNGonMGAT(int param_1,int param_2); /* 0x00436e80 */
void __cdecl rdZRaster_DrawScanLineNGonMGAT_8(uint *param_1,uint *param_2); /* 0x00437110 */
void __cdecl rdZRaster_DrawScanLineNGonMGAT_16(uint *param_1,uint *param_2); /* 0x00437390 */
void __cdecl rdZRaster_DrawNGonMTGAT(int param_1,int param_2); /* 0x00437620 */
void __cdecl rdZRaster_DrawScanLineNGonMTGAT_8(uint *param_1,uint *param_2); /* 0x004378d0 */
void __cdecl rdZRaster_DrawScanLineNGonMTGAT_16(uint *param_1,uint *param_2); /* 0x00437b60 */
void __cdecl rdZRaster_DrawNGonLIT(int param_1,int param_2); /* 0x00437e10 */
void __cdecl rdZRaster_DrawScanLineNGonLIT_8(uint *param_1,uint *param_2); /* 0x004383d0 */
void __cdecl rdZRaster_DrawScanLineNGonLIT_16(uint *param_1,uint *param_2); /* 0x00438a90 */
uint __cdecl rdZRaster_SetupLeftEdgeNGonLIT(int *param_1); /* 0x004391a0 */
uint __cdecl rdZRaster_SetupRightEdgeNGonLIT(int *param_1); /* 0x00439400 */
void __cdecl rdZRaster_DrawNGonTLIT(int param_1,int param_2); /* 0x004395c0 */
void __cdecl rdZRaster_DrawScanLineNGonTLIT_8(uint *param_1,uint *param_2); /* 0x00439840 */
void __cdecl rdZRaster_DrawScanLineNGonTLIT_16(uint *param_1,uint *param_2); /* 0x00439f50 */
void __cdecl rdZRaster_DrawNGonMLIT(int param_1,int param_2); /* 0x0043a6e0 */
void __cdecl rdZRaster_DrawScanLineNGonMLIT_8(uint *param_1,uint *param_2); /* 0x0043a940 */
void __cdecl rdZRaster_DrawScanLineNGonMLIT_16(uint *param_1,uint *param_2); /* 0x0043b020 */
void __cdecl rdZRaster_DrawNGonMTLIT(int param_1,int param_2); /* 0x0043b760 */
void __cdecl rdZRaster_DrawScanLineNGonMTLIT_8(uint *param_1,uint *param_2); /* 0x0043b9e0 */
void __cdecl rdZRaster_DrawScanLineNGonMTLIT_16(uint *param_1,uint *param_2); /* 0x0043c130 */
void __cdecl rdZRaster_DrawNGonFIT(int param_1,int param_2,float param_3); /* 0x0043c8d0 */
void __cdecl rdZRaster_DrawScanLineNGonFIT_8(uint *param_1,uint *param_2); /* 0x0043ceb0 */
void __cdecl rdZRaster_DrawScanLineNGonFIT_16(uint *param_1,uint *param_2); /* 0x0043d5b0 */
uint __cdecl rdZRaster_SetupLeftEdgeNGonFIT(int *param_1); /* 0x0043dcc0 */
uint __cdecl rdZRaster_SetupRightEdgeNGonFIT(int *param_1); /* 0x0043df20 */
void __cdecl rdZRaster_DrawNGonTFIT(int param_1,int param_2,float param_3); /* 0x0043e0e0 */
void __cdecl rdZRaster_DrawScanLineNGonTFIT_8(uint *param_1,uint *param_2); /* 0x0043e380 */
void __cdecl rdZRaster_DrawScanLineNGonTFIT_16(uint *param_1,uint *param_2); /* 0x0043eab0 */
void __cdecl rdZRaster_DrawNGonMFIT(int param_1,int param_2,float param_3); /* 0x0043f280 */
void __cdecl rdZRaster_DrawScanLineNGonMFIT_8(uint *param_1,uint *param_2); /* 0x0043f500 */
void __cdecl rdZRaster_DrawScanLineNGonMFIT_16(uint *param_1,uint *param_2); /* 0x0043fc30 */
void __cdecl rdZRaster_DrawNGonMTFIT(int param_1,int param_2,float param_3); /* 0x00440370 */
void __cdecl rdZRaster_DrawScanLineNGonMTFIT_8(uint *param_1,uint *param_2); /* 0x00440610 */
void __cdecl rdZRaster_DrawScanLineNGonMTFIT_16(uint *param_1,uint *param_2); /* 0x00440d80 */
void __cdecl rdZRaster_DrawNGonGIT(int param_1,int param_2); /* 0x00441520 */
void __cdecl rdZRaster_DrawScanLineNGonGIT_8(uint *param_1,uint *param_2); /* 0x00441b20 */
void __cdecl rdZRaster_DrawScanLineNGonGIT_16(uint *param_1,uint *param_2); /* 0x004422d0 */
uint __cdecl rdZRaster_SetupLeftEdgeNGonGIT(int *param_1); /* 0x00442ab0 */
uint __cdecl rdZRaster_SetupRightEdgeNGonGIT(int *param_1); /* 0x00442db0 */
void __cdecl rdZRaster_DrawNGonTGIT(int param_1,int param_2); /* 0x00443000 */
void __cdecl rdZRaster_DrawScanLineNGonTGIT_8(uint *param_1,uint *param_2); /* 0x004432c0 */
void __cdecl rdZRaster_DrawScanLineNGonTGIT_16(uint *param_1,uint *param_2); /* 0x00443ab0 */
void __cdecl rdZRaster_DrawNGonMGIT(int param_1,int param_2); /* 0x00444320 */
void __cdecl rdZRaster_DrawScanLineNGonMGIT_8(uint *param_1,uint *param_2); /* 0x004445c0 */
void __cdecl rdZRaster_DrawScanLineNGonMGIT_16(uint *param_1,uint *param_2); /* 0x00444d90 */
void __cdecl rdZRaster_DrawNGonMTGIT(int param_1,int param_2); /* 0x00445570 */
void __cdecl rdZRaster_DrawScanLineNGonMTGIT_8(uint *param_1,uint *param_2); /* 0x00445830 */
void __cdecl rdZRaster_DrawScanLineNGonMTGIT_16(uint *param_1,uint *param_2); /* 0x00446030 */
void __cdecl rdRaster_SpanR_FlatZw(int *param_1); /* 0x00451fa0 */
void __cdecl rdRaster_SpanR_FlatZw_2(int *param_1); /* 0x00452070 */
void __cdecl rdRaster_SpanR16_Tex(int *param_1); /* 0x00452150 */
void __cdecl rdRaster_SpanR16_Tex_2(int *param_1); /* 0x004522b0 */
void __cdecl rdRaster_SpanR16_Tex_3(int *param_1); /* 0x004523f0 */
void __cdecl rdRaster_SpanR16_Tex_4(int *param_1); /* 0x00452530 */
void __cdecl rdRaster_SpanR16_TexLit(int *param_1); /* 0x00452670 */
void __cdecl rdRaster_SpanR16_Tex_5(int *param_1); /* 0x004527b0 */
void __cdecl rdRaster_SpanR16_Tex_6(int *param_1); /* 0x004528f0 */
void __cdecl rdRaster_SpanR16_Tex_7(int *param_1); /* 0x00452a30 */
void __cdecl rdRaster_SpanR16_Tex_8(int *param_1); /* 0x00452b90 */
void __cdecl rdRaster_SpanR16_Tex_9(int *param_1); /* 0x00452cd0 */
void __cdecl rdRaster_SpanR16_Tex_10(int *param_1); /* 0x00452e10 */
void __cdecl rdRaster_SpanR16_TexLit_2(int *param_1); /* 0x00452f50 */
void __cdecl rdRaster_SpanR16_Tex_11(int *param_1); /* 0x00453090 */
void __cdecl rdRaster_SpanR16_Tex_12(int *param_1); /* 0x004531d0 */
void __cdecl rdRaster_SpanR16_TexLit_3(int *param_1); /* 0x00453310 */
void __cdecl rdRaster_SpanR16_TexLit_4(int *param_1); /* 0x004534d0 */
void __cdecl rdRaster_SpanR16_TexLit_5(int *param_1); /* 0x00453660 */
void __cdecl rdRaster_SpanR16_TexLit_6(int *param_1); /* 0x004537f0 */
void __cdecl rdRaster_SpanR16_TexLit_7(int *param_1); /* 0x00453980 */
void __cdecl rdRaster_SpanR16_TexLit_8(int *param_1); /* 0x00453b10 */
void __cdecl rdRaster_SpanR16_TexLit_9(int *param_1); /* 0x00453ca0 */
void __cdecl rdRaster_SpanP16_Tex(uint *param_1); /* 0x00453e30 */
void __cdecl rdRaster_SpanP16_Tex_2(uint *param_1); /* 0x00454780 */
void __cdecl rdRaster_SpanP16_Tex_3(uint *param_1); /* 0x00455050 */
void __cdecl rdRaster_SpanP16_Tex_4(uint *param_1); /* 0x00455920 */
void __cdecl rdRaster_SpanP16_TexLit(uint *param_1); /* 0x004561f0 */
void __cdecl rdRaster_SpanP16_Tex_5(uint *param_1); /* 0x00456ac0 */
void __cdecl rdRaster_SpanP16_Tex_6(uint *param_1); /* 0x00457390 */
void __cdecl rdRaster_SpanP16_Tex_7(uint *param_1); /* 0x00457c60 */
void __cdecl rdRaster_SpanP16_Tex_8(uint *param_1); /* 0x004585b0 */
void __cdecl rdRaster_SpanP16_Tex_9(uint *param_1); /* 0x00458e80 */
void __cdecl rdRaster_SpanP16_Tex_10(uint *param_1); /* 0x00459750 */
void __cdecl rdRaster_SpanP16_TexLit_2(uint *param_1); /* 0x0045a020 */
void __cdecl rdRaster_SpanP16_Tex_11(uint *param_1); /* 0x0045a8f0 */
void __cdecl rdRaster_SpanP16_Tex_12(uint *param_1); /* 0x0045b1c0 */
void __cdecl rdRaster_SpanP16_TexLit_3(uint *param_1); /* 0x0045ba90 */
void __cdecl rdRaster_SpanP16_TexLit_4(uint *param_1); /* 0x0045c4e0 */
void __cdecl rdRaster_SpanP16_TexLit_5(uint *param_1); /* 0x0045ce90 */
void __cdecl rdRaster_SpanP16_TexLit_6(uint *param_1); /* 0x0045d840 */
void __cdecl rdRaster_SpanP16_TexLit_7(uint *param_1); /* 0x0045e1f0 */
void __cdecl rdRaster_SpanP16_TexLit_8(uint *param_1); /* 0x0045eba0 */
void __cdecl rdRaster_SpanP16_TexLit_9(uint *param_1); /* 0x0045f550 */
void __cdecl rdRaster_Span16_TexLitZw(uint *param_1,uint *param_2); /* 0x0045ff10 */
void __cdecl rdRaster_Span16_TexLitZw_2(uint *param_1,uint *param_2); /* 0x004602c0 */
void __cdecl rdRaster_Span16_TexLitZw_3(uint *param_1,uint *param_2); /* 0x00460670 */
void __cdecl rdRaster_Span16_TexLitZw_4(uint *param_1,uint *param_2); /* 0x00460a20 */
void __cdecl rdRaster_Span16_TexLitZw_5(uint *param_1,uint *param_2); /* 0x00460dd0 */
void __cdecl rdRaster_Span16_TexLitZw_6(uint *param_1,uint *param_2); /* 0x00461180 */
void __cdecl rdRaster_Span16_TexLitZw_7(uint *param_1,uint *param_2); /* 0x00461530 */
void __cdecl rdRaster_Span16_TexLitZw_8(uint *param_1,uint *param_2); /* 0x004618e0 */
void __cdecl rdRaster_Span16_TexZw(uint *param_1,uint *param_2); /* 0x00461c90 */
void __cdecl rdRaster_Span16_TexLitZw_9(uint *param_1,uint *param_2); /* 0x00462780 */
void __cdecl rdRaster_Span16_TexLitZw_10(uint *param_1,uint *param_2); /* 0x00463270 */
void __cdecl rdRaster_Span16_TexLitZw_11(uint *param_1,uint *param_2); /* 0x00463d60 */
void __cdecl rdRaster_Span16_TexLitZw_12(uint *param_1,uint *param_2); /* 0x00464850 */
void __cdecl rdRaster_Span16_TexLitZw_13(uint *param_1,uint *param_2); /* 0x00465340 */
void __cdecl rdRaster_Span16_TexLitZw_14(uint *param_1,uint *param_2); /* 0x00465e30 */
void __cdecl rdRaster_Span16_TexLitZw_15(uint *param_1,uint *param_2); /* 0x00466920 */
void __cdecl rdRaster_Span16_TexLitZw_16(uint *param_1,uint *param_2); /* 0x00466c30 */
void __cdecl rdRaster_Span16_TexLitZw_17(uint *param_1,uint *param_2); /* 0x00466f30 */
void __cdecl rdRaster_Span16_TexLitZw_18(uint *param_1,uint *param_2); /* 0x00467230 */
void __cdecl rdRaster_Span16_TexLitZw_19(uint *param_1,uint *param_2); /* 0x00467530 */
void __cdecl rdRaster_Span16_TexLitZw_20(uint *param_1,uint *param_2); /* 0x00467830 */
void __cdecl rdRaster_Span16_TexLitZw_21(uint *param_1,uint *param_2); /* 0x00467b30 */
void __cdecl rdRaster_Span16_TexLitZw_22(uint *param_1,uint *param_2); /* 0x00467e30 */
void __cdecl rdRaster_Span16_TexZw_2(uint *param_1,uint *param_2); /* 0x00468130 */
void __cdecl rdRaster_Span16_TexZw_3(uint *param_1,uint *param_2); /* 0x00468af0 */
void __cdecl rdRaster_Span16_TexZw_4(uint *param_1,uint *param_2); /* 0x00469450 */
void __cdecl rdRaster_Span16_TexZw_5(uint *param_1,uint *param_2); /* 0x00469db0 */
void __cdecl rdRaster_Span16_TexLitZw_23(uint *param_1,uint *param_2); /* 0x0046a710 */
void __cdecl rdRaster_Span16_TexZw_6(uint *param_1,uint *param_2); /* 0x0046b070 */
void __cdecl rdRaster_Span16_TexZw_7(uint *param_1,uint *param_2); /* 0x0046b9d0 */
void __cdecl rdRaster_Span16_TexLitZw_24(uint *param_1,uint *param_2); /* 0x0046c330 */
void __cdecl rdRaster_Span16_TexLitZw_25(uint *param_1,uint *param_2); /* 0x0046c640 */
void __cdecl rdRaster_Span16_TexLitZw_26(uint *param_1,uint *param_2); /* 0x0046c940 */
void __cdecl rdRaster_Span16_TexLitZw_27(uint *param_1,uint *param_2); /* 0x0046cc40 */
void __cdecl rdRaster_Span16_TexLitZw_28(uint *param_1,uint *param_2); /* 0x0046cf40 */
void __cdecl rdRaster_Span16_TexLitZw_29(uint *param_1,uint *param_2); /* 0x0046d240 */
void __cdecl rdRaster_Span16_TexLitZw_30(uint *param_1,uint *param_2); /* 0x0046d540 */
void __cdecl rdRaster_Span16_TexZw_8(uint *param_1,uint *param_2); /* 0x0046d840 */
void __cdecl rdRaster_Span16_TexZw_9(uint *param_1,uint *param_2); /* 0x0046e200 */
void __cdecl rdRaster_Span16_TexZw_10(uint *param_1,uint *param_2); /* 0x0046eb60 */
void __cdecl rdRaster_Span16_TexZw_11(uint *param_1,uint *param_2); /* 0x0046f4c0 */
void __cdecl rdRaster_Span16_TexLitZw_31(uint *param_1,uint *param_2); /* 0x0046fe20 */
void __cdecl rdRaster_Span16_TexZw_12(uint *param_1,uint *param_2); /* 0x00470780 */
void __cdecl rdRaster_Span16_TexZw_13(uint *param_1,uint *param_2); /* 0x004710e0 */

/* ===== rdmaterial.c ===== */
uint __cdecl rdMaterial_RegisterLoader(uint param_1); /* 0x00417e90 */
uint __cdecl rdMaterial_RegisterUnloader(uint param_1); /* 0x00417ea0 */
void * __cdecl rdMaterial_Load(char *name,int a,int b); /* 0x00417eb0 */
int __cdecl rdMaterial_LoadEntry(char *filename,void *material,int a,int b); /* 0x00417f30 */
void __cdecl rdMaterial_Free(uint param_1); /* 0x00418360 */
void __cdecl rdMaterial_FreeEntry(int param_1); /* 0x004183a0 */
int __cdecl rdMaterial_AddToTextureCache(void *a,uint *material,int cel,int alt); /* 0x004184a0 */

/* ===== math3d.c ===== */
float __cdecl rdVector_Dot2(float *a,float *b); /* 0x00446880 */
float __cdecl rdVector_Dot3(float *a,float *b); /* 0x004468a0 */
void __cdecl rdVector_Cross3(float *out,float *a,float *b); /* 0x004468d0 */
void __cdecl rdVector_Normalize3(float *param_1,float *param_2); /* 0x00446920 */
float __cdecl rdVector_Normalize3Acc(float *param_1); /* 0x004469a0 */
float __cdecl rdVector_Normalize3QuickAcc(float *param_1); /* 0x00446a10 */
void __cdecl rdVector_Rotate3Acc(float *vec,float *rot); /* 0x00446ba0 */
void __cdecl rdVector_ExtractAngles(float *matrix,float *outAngles); /* 0x00446bd0 */
uint __cdecl rdClip_SphereInFrustrum(int *param_1,float *param_2,float param_3); /* 0x0044e7d0 */
uint __cdecl rdClip_FaceToPlane(float *param_1,float *param_2,float *param_3,uint *param_4,float *param_5, uint *param_6); /* 0x0044ea50 */
void __cdecl rdMatrix_Build34(float *param_1,uint *param_2,float *param_3); /* 0x0044eeb0 */
void __cdecl rdMatrix_InvertOrtho34(float *out,float *m); /* 0x0044efd0 */
void __cdecl rdMatrix_BuildRotate34(float *param_1,uint *param_2); /* 0x0044f080 */
void __cdecl rdMatrix_BuildTranslate34(float *m,float *pos); /* 0x0044f1a0 */
void __cdecl rdMatrix_BuildScale34(undefined4 *param_1,undefined4 *param_2); /* 0x0044f1d0 */
void __cdecl rdMatrix_BuildFromVectorAngle34(float *param_1,float *param_2,float param_3); /* 0x0044f210 */
void __cdecl rdMatrix_LookAt(float *param_1,float *param_2,float *param_3,uint param_4); /* 0x0044f490 */
void __cdecl rdMatrix_ExtractAngles34(float *param_1,float *param_2); /* 0x0044f650 */
void __cdecl rdMatrix_Identity34(float *m); /* 0x0044f880 */
void __cdecl rdMatrix_Multiply34(float *out,float *a,float *b); /* 0x0044f8a0 */
void __cdecl rdMatrix_PreMultiply34(float *m,float *angles); /* 0x0044fa70 */
void __cdecl rdMatrix_PostMultiply34(float *param_1,float *param_2); /* 0x0044fc60 */
void __cdecl Matrix_BuildTransform(float *param_1,uint param_2); /* 0x0044fe50 */
void __cdecl rdMatrix_PostTranslate34(int param_1,float *param_2); /* 0x0044fe80 */
void __cdecl rdMatrix_PreScale34(float *param_1,uint param_2); /* 0x0044feb0 */
void __cdecl rdMatrix_TransformVector34(float *out,float *v,float *param_3); /* 0x0044fee0 */
void __cdecl rdMatrix_TransformVectorOrtho34(float *out,float *v,float *m); /* 0x0044ff50 */
void __cdecl rdMatrix_TransformVector34Acc(float *vec,float *m); /* 0x0044ffc0 */
void __cdecl rdMatrix_TransformPoint34(float *out,float *a,float *b); /* 0x00450060 */
void __cdecl rdMatrix_TransformPoint34Acc(float *vec,float *m); /* 0x004500d0 */
void __cdecl rdMatrix_TransformPointLst34(float *m,float *in,float *out,int count); /* 0x00450170 */
uint __cdecl FUN_00450220(undefined4 *param_1); /* 0x00450220 */
void __cdecl rdFace_FreeEntry(int param_1); /* 0x00450260 */
void __cdecl rdMath_CalcSurfaceNormal(float *param_1,float *param_2,float *param_3,float *param_4); /* 0x00450290 */
void __cdecl rdMath_ClampVector(float *param_1,float param_2); /* 0x00450380 */
uint __cdecl rdMath_PointsCollinear(float *param_1,float *param_2,float *param_3); /* 0x00450410 */

/* ===== rdclip.c ===== */
undefined4 __cdecl rdClip_Line2(int canvas,undefined4 *x0,undefined4 *y0,undefined4 *x1,undefined4 *y1); /* 0x00446c10 */
uint __cdecl rdClip_CalcOutcode2(int canvas,int x,int y); /* 0x00446e80 */
int __cdecl rdClip_Point3(void *frustum,float *point); /* 0x00446ec0 */
int __cdecl rdClip_Line3(void *frustum,float *p0,float *p1,int *clipped0,int *clipped1); /* 0x00446f80 */
uint __cdecl rdClip_Face3W(int *param_1,float *param_2,uint param_3); /* 0x004478c0 */
int __cdecl rdClip_Face3WOrtho(int *param_1,float *param_2,int param_3); /* 0x00448260 */
uint __cdecl rdClip_Face3S(int *param_1,float *param_2,uint param_3); /* 0x004489b0 */
int __cdecl rdClip_Face3SOrtho(int *param_1,float *param_2,int param_3); /* 0x00449350 */
float __cdecl rdClip_Face3GS(int *param_1,float *param_2,float *param_3,float *param_4); /* 0x00449aa0 */
uint __cdecl rdClip_Face3GSOrtho(int *param_1,float *param_2,float *param_3,uint param_4); /* 0x0044a6d0 */
float __cdecl rdClip_Face3T(int *param_1,float *param_2,float *param_3,float *param_4); /* 0x0044b0a0 */
uint __cdecl rdClip_Face3TOrtho(int *param_1,float *param_2,float *param_3,uint param_4); /* 0x0044be80 */
float __cdecl rdClip_Face3GT(int *param_1,float *param_2,float *param_3,uint *param_4,float *param_5); /* 0x0044c9d0 */
uint __cdecl rdClip_Face3GTOrtho(int *param_1,float *param_2,uint *param_3,uint *param_4,uint param_5); /* 0x0044da40 */

/* ===== rdlight.c ===== */
uint __cdecl rdLight_NewEntry(int param_1); /* 0x00451460 */
void __cdecl rdLight_SetAngles(void *light,float inner,float outer); /* 0x004514a0 */
float __cdecl rdLight_CalcVertexIntensities (int *param_1,float *param_2,int param_3,uint param_4,int *param_5,uint param_6, float *param_7,float *param_8,uint param_9,float param_10); /* 0x00451510 */
float __cdecl rdLight_CalcFaceIntensity (int *param_1,int param_2,uint param_3,uint param_4,int param_5,float *param_6,int param_7 ,float param_8); /* 0x00451800 */

/* ===== rdprimit2.c ===== */
void __cdecl rdPrimit2_DrawLine(void *canvas,int x1,int y1,int x2,int y2,int color,int mask); /* 0x00451b80 */
void __cdecl rdPrimit2_DrawRectangle(void *canvas,int x1,int y1,int x2,int y2,int color,int mask); /* 0x00451f20 */

/* ===== memory.c ===== */
void __cdecl Mem_DumpLog(void); /* 0x0045ff00 */
void __cdecl Mem_Copy(void *dst,void *src,uint n); /* 0x00478170 */
void __cdecl Mem_CheckAlloc(void *p,char *file,int line); /* 0x0047fe00 */
uint __cdecl Memory_SysInitialize(GrimServices *param_1,undefined4 *param_2); /* 0x004888d0 */
void __cdecl Memory_SysTerminate(void); /* 0x00488930 */
uint __cdecl Memory_SysStartup(void); /* 0x00488940 */
void __cdecl Memory_SysShutdown(void); /* 0x00488970 */
void ** __cdecl Memory_AllocatePool(int param_1,void *param_2,void *param_3); /* 0x00488980 */
void __cdecl Memory_FreePool(void **param_1); /* 0x00488a70 */
int * __cdecl Memory_AllocFixed(int *param_1); /* 0x00488b10 */
void __cdecl Pool_Free(void *item); /* 0x00488ba0 */
void __cdecl Pool_Grow(int param_1,int param_2); /* 0x00488c00 */

/* ===== rdprimitive.c ===== */
uint __cdecl rdPolyline_Draw(int param_1,float *param_2); /* 0x00471ee0 */
void __cdecl rdPolyline_DrawFace(int param_1,int param_2,uint param_3,undefined4 *param_4); /* 0x00472360 */
int __cdecl rdSprite_DrawThing(void *thing,void *sprite); /* 0x00472640 */
int __cdecl rdSprite_New(uint param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6, uint param_7,uint param_8,uint param_9,uint param_10); /* 0x004728a0 */
uint __cdecl rdSprite_NewEntry(int param_1,int param_2,uint param_3,char *param_4,uint param_5,uint param_6, uint param_7,uint param_8,uint param_9,uint param_10,undefined4 *param_11); /* 0x00472910 */
void __cdecl rdSprite_Free(int param_1); /* 0x00472b50 */
void __cdecl rdSprite_FreeEntry(int param_1); /* 0x00472b70 */
uint __cdecl rdSprite_Draw(int param_1,float *param_2); /* 0x00472bd0 */

/* ===== stdfileutil.c ===== */
undefined * __cdecl stdFileOpen(uint param_1,uint param_2); /* 0x00473430 */
void __cdecl stdFileClose(uint param_1); /* 0x00473450 */
void __cdecl stdFileRead(uint param_1,uint param_2,uint param_3); /* 0x00473460 */
uint __cdecl stdFileWrite(uint param_1,uint param_2,uint param_3); /* 0x00473480 */
void __cdecl stdFileGets(uint param_1,uint param_2,uint param_3); /* 0x004734a0 */
uint __cdecl stdFileGetws(uint param_1,uint param_2,uint param_3); /* 0x004734c0 */
uint __cdecl stdFeof(int param_1); /* 0x004734e0 */
undefined * __cdecl stdFtell(uint param_1); /* 0x004734f0 */
uint __cdecl stdFseek(uint param_1,uint param_2,uint param_3); /* 0x00473500 */
undefined * __cdecl stdFileSize(uint param_1); /* 0x00473520 */
uint __cdecl stdFilePrintf(uint fh,char *fmt,...); /* 0x00473570 */
uint __cdecl stdFGetc(uint param_1); /* 0x004735f0 */
void __cdecl stdFPutc(uint param_1,uint param_2); /* 0x00473610 */
int __cdecl LzssDecompress(void *dst,void *src,int srcSize); /* 0x00473a00 */
void __cdecl stdCompress_DecompressLoop(void); /* 0x00473b60 */
void * __cdecl stdFileUtil_NewFind(char *dir,int mode,char *ext); /* 0x004c1170 */
void __cdecl stdFileUtil_DisposeFind(int param_1); /* 0x004c12a0 */
int __cdecl stdFileUtil_FindNext(void *find,void *outEntry); /* 0x004c12d0 */

/* ===== math.c ===== */
int __cdecl stdCalcBitPos(int n); /* 0x004735d0 */
float __cdecl stdMath_FlexPower(float x,int n); /* 0x0047bbe0 */
float __cdecl stdMath_NormalizeAngle(float degrees); /* 0x0047bc20 */
float __cdecl stdMath_NormalizeAngleAcute(float param_1); /* 0x0047bce0 */
void __cdecl stdMath_SinCos(float param_1,float *param_2,float *param_3); /* 0x0047bd20 */
float __cdecl Math_Floor(float param_1); /* 0x0047c100 */
float10 stdMath_Tan(float param_1); /* 0x0047c120 */
float __cdecl stdMath_ArcSin1(float x); /* 0x0047c3b0 */
float __cdecl Math_Sqrt(float param_1); /* 0x0047c490 */
float __cdecl stdMath_ArcSin3(float param_1); /* 0x0047c4a0 */
float __cdecl stdMath_ArcTan4(float y,float x); /* 0x0047c5f0 */

/* ===== stdbitmap.c ===== */
void * __cdecl stdLoadImage(char *filename,int param_2,int param_3); /* 0x00473630 */
void * __cdecl stdLoadImageData(char *name,int a,int b); /* 0x00473660 */
int __cdecl stdWriteImage(char *filename,void *bitmap); /* 0x00473810 */
void * __cdecl stdBitmap_Load(char *name,int a,int b); /* 0x0047aa50 */
void * __cdecl stdBitmap_LoadFromFile(char *filename,int a,int b,int c); /* 0x0047aab0 */
uint __cdecl stdBitmap_LoadEntryFromFile(uint param_1,int param_2,int param_3,int param_4); /* 0x0047ab20 */
void __cdecl stdBitmap_Free(void *bitmap); /* 0x0047ae70 */
void __cdecl stdBitmap_FreeEntry(int param_1); /* 0x0047ae90 */
uint __cdecl stdBitmap_AppendToFile(uint param_1,int param_2); /* 0x0047aef0 */
int __cdecl stdBitmap_Write(char *filename,void *bitmap); /* 0x0047b250 */
void __cdecl stdBitmap_ConvertColorFormat(int *param_1,int param_2); /* 0x0047b2b0 */
int __cdecl stdBitmap_VBufferToBitmap(void *bitmap,int format,int flags); /* 0x0047b380 */
uint __cdecl stdBitmap_NewEntry(undefined4 *param_1,uint param_2,uint param_3,uint param_4,uint param_5, undefined4 *param_6); /* 0x0047b4b0 */
void __cdecl stdBitmap_SetSurface(int param_1,int param_2,uint param_3); /* 0x0047b540 */
int __cdecl stdBitmap_MemUsage(void *bitmap); /* 0x0047b560 */
void __cdecl stdBitmap_DeCompress(int param_1); /* 0x0047b590 */
void __cdecl stdPalEffects_ResetEffect(undefined4 *param_1); /* 0x0047b5f0 */

/* ===== stdinput.c ===== */
undefined * stdControl_Startup(void); /* 0x00476f10 */
void __cdecl stdControl_Shutdown(void); /* 0x00476f70 */
uint __cdecl stdControl_Open(void); /* 0x00476fc0 */
uint __cdecl stdControl_Close(void); /* 0x00476fe0 */
void __cdecl stdControl_Flush(void); /* 0x00477010 */
void __cdecl stdControl_Reset(void); /* 0x00477040 */
int __cdecl stdControl_EnableAxis(uint axis); /* 0x00477090 */
void __cdecl stdControl_ReadControls(void); /* 0x004770d0 */
float __cdecl stdControl_ReadAxis(int inputId); /* 0x00477160 */
int __cdecl stdControl_ReadKey(int inputId,int *down,int *justPressed); /* 0x00477230 */
void __cdecl Input_SetAcquired(int acquire); /* 0x00477300 */
void __cdecl stdControl_ShowMouseCursor(int param_1); /* 0x00477380 */
void __cdecl Input_InitJoysticks(void); /* 0x00477390 */
void __cdecl Input_CreateKeyboard(void); /* 0x00477530 */
void __cdecl Input_CreateMouse(void); /* 0x004775a0 */
void __cdecl Input_MarkAxisUsed(uint param_1); /* 0x00477680 */
void __cdecl Input_PollKeyboard(void); /* 0x00477730 */
void __cdecl Input_FlushKeyboard(void); /* 0x004778a0 */
void __cdecl Input_PollJoysticks(void); /* 0x004778f0 */
void __cdecl Input_PollMouse(void); /* 0x00477c20 */
void __cdecl Input_FlushJoystick(void); /* 0x00477dc0 */
void __cdecl Input_SetAxisRange(int axis,int min,int max,float deadZone); /* 0x00477e70 */

/* ===== plat.c ===== */
uint __cdecl Plat_ReturnTrue(void); /* 0x00477f00 */
uint __cdecl stdPlatform_GetPhysicalRam(void); /* 0x00478150 */
int __cdecl grimPlat_QueryDialog(char *text,char *caption,uint flags); /* 0x00487650 */
void __cdecl grimPlat_SetDefaultOpenPath(uint param_1); /* 0x00487690 */
char * __cdecl grimPlat_GetDefaultOpenPath(void); /* 0x004876b0 */
int __cdecl grimPlat_OpenFileRequest(char *title,char *filter); /* 0x004876c0 */
int __cdecl grimPlat_SaveFileRequest(char *title,char *filter); /* 0x004877d0 */
int __cdecl grimPlat_SpinDialog(int param_1,int param_2,undefined4 *param_3,uint param_4); /* 0x004878c0 */
int __cdecl grimPlat_TreeDialog(char *title,char **items,int count,int *recursive); /* 0x00487c10 */
int __cdecl grimPlat_InputDialog(char *title,char *prompt,char *buf,int bufSize,char *defaultText); /* 0x00487e30 */
undefined * __stdcall Plat_PromptDialogProc(int a1,int a2,int a3,int a4); /* 0x00488370 */
undefined * __stdcall Plat_TreeSelectDialogProc(int a1,int a2,int a3,int a4); /* 0x00488460 */
undefined * __stdcall Plat_InputDialogProc(int a1,int a2,int a3,int a4); /* 0x004886f0 */
void * __cdecl Plat_Alloc(uint size); /* 0x00488800 */
void __cdecl Plat_Free(void *p); /* 0x00488820 */

/* ===== platsvc.c ===== */
void __cdecl stdPlatform_Assert(uint param_1,char *param_2,uint param_3); /* 0x00477f10 */
uint __cdecl stdPlatform_AllocHandle(uint param_1); /* 0x00478030 */
void __cdecl stdPlatform_FreeHandle(uint param_1); /* 0x00478040 */
uint __cdecl stdPlatform_ReallocHandle(uint param_1,uint param_2); /* 0x00478050 */
uint __cdecl stdPlatform_LockHandle(uint param_1); /* 0x00478070 */

/* ===== std3d.c ===== */
uint __cdecl D3D_Enumerate(void); /* 0x00478230 */
void __cdecl D3D_Release(void); /* 0x004782b0 */
uint __cdecl D3D_IsAvailable(void); /* 0x004782d0 */
int __cdecl D3D_SelectDriver(uint driverIdx,int useZBuffer); /* 0x004782e0 */
void __cdecl D3D_ReleaseDriver(void); /* 0x00478660 */
void __cdecl D3D_SetTextureLimits(int minW,int minH,int maxSize,int d); /* 0x00478700 */
void __cdecl std3D_StartScene(void); /* 0x00478730 */
void __cdecl std3D_EndScene(void); /* 0x00478750 */
uint __cdecl D3D_BeginExecuteBuffer(void); /* 0x00478770 */
int __cdecl std3D_AddRenderListVertices(void *verts,uint count); /* 0x004787d0 */
uint __cdecl std3D_RenderListVerticesFinish(void); /* 0x00478840 */
int __cdecl std3D_AddRenderListTris(void *tris,uint count); /* 0x004788c0 */
int __cdecl std3D_DrawRenderList(void); /* 0x00478b40 */
void __cdecl D3D_SetRenderFlags(uint flags); /* 0x00478c00 */
void __cdecl std3D_GetValidDimensions(uint param_1,uint param_2,uint *param_3,uint *param_4); /* 0x00479070 */
void __cdecl std3D_PurgeTextureCache(void); /* 0x00479110 */
int __cdecl std3D_AddToTextureCache(void *surface,void *texture,int usePalette,int colorKey); /* 0x00479170 */
void __cdecl D3D_FreeAllTextures(void); /* 0x00479860 */
void __cdecl D3D_LinkTexture(void *param_1); /* 0x004798e0 */
void __cdecl D3D_UnlinkTexture(void *param_1); /* 0x00479950 */
uint __cdecl D3D_SetVertexLimit(void); /* 0x00479a00 */
void __cdecl std3D_UpdateFrameCount(int param_1); /* 0x00479a70 */
uint __cdecl std3D_ClearZBuffer(void); /* 0x00479aa0 */
uint __cdecl D3D_FindClosestDriver(int *param_1,int param_2,uint param_3); /* 0x00479b50 */
uint __cdecl D3D_FindTextureFormat(int *param_1,int param_2,uint param_3); /* 0x00479be0 */
void __cdecl D3D_SetViewportRect(uint *param_1); /* 0x00479cc0 */
uint __cdecl D3D_InitRenderState(void); /* 0x00479db0 */
undefined4 __cdecl D3D_CreateViewport(uint width,uint height); /* 0x0047a130 */
uint __cdecl D3D_CreateZBuffer(int param_1,int param_2); /* 0x0047a240 */
undefined * __stdcall D3D_EnumDevicesCallback(int a1,int a2,int a3,int a4,int a5,int a6); /* 0x0047a3b0 */
undefined * __stdcall D3D_EnumTextureFormatsCallback(int a1,int a2); /* 0x0047a590 */
uint __cdecl D3D_CapsToFilterBits(uint param_1); /* 0x0047a850 */
uint __cdecl D3D_FilterBitsToMask(byte param_1); /* 0x0047a890 */
uint __cdecl D3D_FilterBitsToEnum(byte param_1); /* 0x0047a8e0 */
int __cdecl D3D_EvictTexture(uint size); /* 0x0047a930 */

/* ===== stdpcx.c ===== */
uint __cdecl stdPcx_DecodeRun16(byte *param_1,ushort *param_2,int param_3); /* 0x0047b710 */
uint __cdecl stdPcx_DecodeRun8(byte *param_1,int param_2,int param_3); /* 0x0047b780 */
uint __cdecl stdPcx_DecodeRunMasked(byte *param_1,int param_2,int param_3,uint param_4); /* 0x0047b810 */
undefined4 * __cdecl stdPcx_Load(uint param_1,int param_2,int param_3); /* 0x0047ec80 */
uint __cdecl stdPcx_Write(uint param_1,int param_2); /* 0x0047ef10 */

/* ===== stdconffile.c ===== */
uint __cdecl stdConffile_Open(uint param_1); /* 0x0047c7c0 */
uint __cdecl stdConffile_OpenMode(byte *param_1,uint param_2); /* 0x0047c7e0 */
void __cdecl stdConffile_Close(void); /* 0x0047c8c0 */
uint __cdecl stdConffile_ReadLine(void); /* 0x0047c920 */
void __cdecl stdConffile_Push(void); /* 0x0047ca00 */
void __cdecl stdConffile_Pop(void); /* 0x0047ca90 */

/* ===== stdbmp.c ===== */
uint __cdecl stdBmp_Load(uint param_1,uint param_2,uint param_3); /* 0x0047cb20 */
uint __cdecl stdBmp_LoadEntry(char *param_1,undefined4 *param_2,int param_3,int param_4); /* 0x0047cb70 */
uint __cdecl stdBmp_Write(uint param_1,int param_2); /* 0x0047d050 */

/* ===== stdpic.c ===== */
uint __cdecl stdPic_Load(uint param_1,uint param_2,uint param_3); /* 0x0047d280 */
uint __cdecl stdPic_LoadEntry(char *param_1,uint *param_2,int param_3,int param_4); /* 0x0047d2d0 */

/* ===== stdgif.c ===== */
void * __cdecl stdGif_Load(char *param_1,int param_2,int param_3); /* 0x0047db00 */
uint __cdecl stdGif_Write(uint param_1,int param_2); /* 0x0047e060 */
uint __cdecl stdGif_LzwInitDecoder(short param_1); /* 0x0047e3c0 */
uint __cdecl stdGif_LzwDecodeNext(uint param_1); /* 0x0047e470 */
uint __cdecl getcode(uint param_1); /* 0x0047e600 */
uint __cdecl stdGif_ReadByte(uint param_1); /* 0x0047e770 */
uint __cdecl stdGif_LzwInitEncoder(uint param_1,uint param_2); /* 0x0047e7f0 */
void __cdecl putcode(uint param_1,short param_2); /* 0x0047e8b0 */
uint __cdecl stdGif_LzwEncodePixel(uint param_1,byte param_2); /* 0x0047ea30 */
void __cdecl stdGif_LzwClearTable(uint param_1); /* 0x0047eba0 */
uint __cdecl stdGif_LzwFinishEncode(uint param_1); /* 0x0047ebe0 */
void __cdecl stdGif_WriteSubBlock(uint param_1,short param_2); /* 0x0047ec40 */

/* ===== stdlbm.c ===== */
void * __cdecl stdLbm_Load(char *param_1,int param_2,int param_3); /* 0x0047f120 */
uint __cdecl stdLbm_Write(uint param_1,int param_2); /* 0x0047f720 */
void __cdecl stdLbm_PackBits(uint param_1,undefined1 *param_2,int param_3,char *param_4); /* 0x0047f9d0 */
void __cdecl stdLbm_PackByte(char param_1); /* 0x0047fa70 */
void __cdecl stdLbm_SwapHeader(undefined2 *param_1); /* 0x0047fc80 */

/* ===== std.c ===== */
uint __cdecl Std_Swap32(uint param_1); /* 0x0047fc50 */
uint __cdecl Std_Swap16(uint param_1); /* 0x0047fd00 */

/* ===== stdmemory.c ===== */
void __cdecl stdMemory_CheckMagic(int param_1); /* 0x0047fe20 */
void * __cdecl stdMemory_Alloc(uint size,char *file,int line); /* 0x0047fe50 */
void __cdecl stdMemory_Free(void *p); /* 0x0047ff00 */
void * __cdecl stdMemory_Realloc(void *p,uint size,char *file,int line); /* 0x0047ff70 */

/* ===== res.c ===== */
int daTotalAllocated(void); /* 0x00480000 */
void * __cdecl Res_SysAddHandle(int fourcc,char *name,void *data); /* 0x00480230 */
int __cdecl Res_FindExternalFile(char *name,char *buf,int size); /* 0x004802b0 */
void * __cdecl Res_Load(int type,char *name); /* 0x00480520 */
uint __cdecl Res_SetPurgable(void *data,int unlock); /* 0x00480560 */
int __cdecl Res_SysPurgeBySize(uint bytesWanted,uint *bytesFreed); /* 0x004805b0 */
int __cdecl Res_Dump(char *filename,int type); /* 0x00480680 */
int __cdecl Res_Log(char *filename); /* 0x00480740 */
void __cdecl Res_OverrideFileCalls(GrimServices *svc); /* 0x00480790 */
void __cdecl Res_RestoreFileCalls(GrimServices *svc); /* 0x00480800 */
void * __cdecl Res_FindByData(void *data); /* 0x004810e0 */
void * __cdecl Res_HandleFromSerialNumber(void *handle); /* 0x00481100 */
void * __cdecl Res_FindByHandle(void *handle); /* 0x00481120 */
void * __cdecl Res_Loaded(int type,char *name); /* 0x00481140 */
void * __cdecl Res_FindByName(int type,char *name); /* 0x00481160 */
void * __cdecl res_Load(int type,char *name,int *status); /* 0x00481210 */
undefined * __cdecl res_LocateResByName(uint param_1,uint param_2); /* 0x00481300 */
int * __cdecl Res_FindByNameInList(int param_1,char *param_2,int *param_3); /* 0x00481320 */
void * __cdecl Res_CreateRecord(int type,char *name,void *data); /* 0x00481400 */
void __cdecl Res_CallUnload(void *res); /* 0x00481510 */
int __cdecl Res_Unlink(void *res); /* 0x004815c0 */
int __cdecl Res_GetSize(void *res); /* 0x00481ef0 */
void __cdecl Res_MoveToFront(void *res); /* 0x00481f00 */
uint __cdecl Res_HashName(char *name,char *outLower); /* 0x00481f60 */
void __cdecl Res_GetFirstType(int *param_1,int *param_2,int param_3); /* 0x00482170 */
void __cdecl Res_GetNextType(int *param_1,int *param_2,int param_3); /* 0x004821b0 */
void __cdecl Res_Touch(void *data); /* 0x00482200 */
int __cdecl Res_CountChildren(uint param_1,uint param_2); /* 0x004824f0 */
void __cdecl grimlib_SetCacheMax(int param_1); /* 0x00482520 */
void __cdecl sputResource_ReportAllocations(void); /* 0x0048e230 */

/* ===== resource.c ===== */
uint __cdecl Res_SysInitialize(uint param_1,undefined4 *param_2); /* 0x00480010 */
undefined4 __fastcall FUN_00480020(uint param_1,int param_2,undefined4 param_3,undefined4 *param_4); /* 0x00480020 */
void __cdecl Res_SysTerminate(void); /* 0x004800a0 */
uint __cdecl Res_SysStartup(void); /* 0x004800b0 */
void __cdecl Res_SysShutdown(void); /* 0x00480140 */
uint __cdecl Res_SysSave(code *param_1); /* 0x00482260 */
uint __cdecl Res_SysLoad(code *param_1); /* 0x00482380 */
void __cdecl Resource_SetNoPurge(int noPurge); /* 0x0048d340 */
void * __cdecl sputResource_Alloc(int fourcc,char *name); /* 0x0048d350 */
uint __cdecl sputResource_CloseResources(void); /* 0x0048d3e0 */
uint __cdecl grimlib_FindResources(void); /* 0x0048d3f0 */
int __cdecl sputResource_AddResourcePath(char *dir); /* 0x0048d4b0 */
int __cdecl sputResource_LogToFile(char *param_1); /* 0x0048d550 */
int __cdecl AddResourcePath(char *dir); /* 0x0048d570 */
uint __cdecl Resource_CountCostumeRefs(uint param_1); /* 0x0048d810 */
uint __cdecl Resource_RegisterTypes(void); /* 0x0048d870 */
void __cdecl sputResource_SetMemoryUsage(int budget,int b); /* 0x0048d8a0 */
void __cdecl Resource_ReloadBitmaps(void); /* 0x0048df50 */
void __cdecl Resource_RebuildColormaps(void); /* 0x0048e0a0 */
void * __cdecl sputResource_MatLoader(char *param_1); /* 0x0048e170 */
void __cdecl sputResource_MatUnloader(void *param_1); /* 0x0048e1b0 */

/* ===== lab.c ===== */
void __cdecl Res_FileCloseAll(void); /* 0x00480120 */
int __cdecl Res_FileOpen(char *path); /* 0x00480360 */
int __cdecl Res_FileClose(char *name); /* 0x004803a0 */
int __cdecl Res_FileMoveToFront(char *name); /* 0x004804c0 */
void * __cdecl Lab_Find(char *name); /* 0x00481070 */
void __cdecl Lab_Unlink(int *param_1); /* 0x004813c0 */
int __cdecl res_FindInternalFile(char *name,void *outEntry); /* 0x00481630 */
void * __cdecl Lab_Open(char *name); /* 0x004816b0 */
int * Lab_AllocRecord(void); /* 0x00481750 */
int __cdecl Lab_ReadDirectory(void *lab); /* 0x004817a0 */
int __cdecl Lab_FindEntry(void *lab,int fourcc,char *lowerName,uint hash,void *outEntry); /* 0x00481a00 */
int __cdecl Lab_ReadRaw(void *entry,void *buf,int offset,int n); /* 0x00482020 */

/* ===== restype.c ===== */
int __cdecl Res_SysRegisterHandler(int fourcc,void *handler); /* 0x004801a0 */
void * __cdecl ResType_Find(int fourcc); /* 0x00481050 */
int __cdecl res_DefaultHandler(void *msg); /* 0x00481e10 */
void * __cdecl sputResource_LipSyncHandler(int *param_1); /* 0x0048d8c0 */
int __cdecl sputResource_BackgroundHandler(void *msg); /* 0x0048d930 */
int __cdecl sputResource_CostumeHandler(void *msg); /* 0x0048da40 */
void * __cdecl sputResource_ColormapHandler(int *param_1); /* 0x0048dab0 */
void * __cdecl sputResource_FontHandler(int *param_1); /* 0x0048dbd0 */
void * __cdecl sputResource_KeyframeHandler(int *param_1); /* 0x0048dc60 */
void * __cdecl sputResource_MaterialHandler(int *param_1); /* 0x0048dd20 */
void * __cdecl sputResource_ModelHandler(int *param_1); /* 0x0048de10 */
void * __cdecl sputResource_SetHandler(int *param_1); /* 0x0048de70 */
void * __cdecl sputResource_ZBufferHandler(int *param_1); /* 0x0048dee0 */
uint __cdecl sputResource_MemoryHandler(int *param_1); /* 0x0048e1e0 */

/* ===== resfile.c ===== */
int __cdecl Res_FOpen(char *name,char *mode); /* 0x00480890 */
int __cdecl Res_FClose(int fh); /* 0x00480a00 */
uint __cdecl Res_FRead(int fh,void *buf,uint n); /* 0x00480a70 */
char * __cdecl Res_FGets(int param_1,char *param_2,uint param_3); /* 0x00480bb0 */
uint __cdecl Res_FWrite(int param_1,uint param_2,uint param_3); /* 0x00480ce0 */
uint __cdecl Res_FEOF(int param_1); /* 0x00480d50 */
uint __cdecl Res_FTell(int param_1); /* 0x00480dc0 */
int __cdecl Res_FSeek(int fh,int offset,int whence); /* 0x00480e30 */
int __cdecl Res_FSize(char *name); /* 0x00480f40 */
int __cdecl Res_FPrintf(int fh,char *fmt,...); /* 0x00480f90 */
void __cdecl ResFile_FillBuffer(void *entry); /* 0x00481fd0 */

/* ===== labdir.c ===== */
void * __cdecl LabDir_Open(char *dir); /* 0x00481b00 */
int __cdecl res_FindDirectoryEntry(int archive,int type,byte *name,uint hash,undefined4 *entry); /* 0x00481cf0 */

/* ===== resref.c ===== */
void __cdecl Res_SetReference(void *ref,void *data,char *file,int line); /* 0x00482070 */
void Res_RemoveReference(void *ref); /* 0x00482110 */
void __cdecl Res_ResolveToSerialNumber(undefined4 *param_1); /* 0x00482220 */

/* ===== engine.c ===== */
void __cdecl Res_FreeAll(void); /* 0x00482460 */
void __cdecl grimlib_LogResources(uint param_1); /* 0x00482530 */
void __cdecl grimlib_OverrideSelectedActorCostume(int param_1); /* 0x004825c0 */
void __cdecl grimlib_RestoreSelectedActorCostume(void); /* 0x004825f0 */
int __cdecl grimlib_SetDisplay(void *mode,int flags); /* 0x00482620 */
uint __cdecl grimlib_UnsetDisplay(void); /* 0x00482660 */
void __cdecl grimlib_Close(void); /* 0x004826e0 */
void __cdecl grimlib_SetDebugToggleCallback(uint param_1); /* 0x00482720 */
void __cdecl grimlib_SetPaletteCallback(uint param_1); /* 0x00482730 */
void __cdecl grimlib_SetShutdownCallback(uint param_1); /* 0x00482740 */
void __cdecl grimlib_SetPageFlipCallback(uint param_1); /* 0x00482750 */
void __cdecl grimlib_Using3DHardware(uint param_1); /* 0x00482760 */
void __cdecl grimlib_AddResourcePath(char *param_1); /* 0x00482770 */
int __cdecl grimlib_FindSystemFiles(void); /* 0x00482790 */
uint __cdecl grimlib_Open(int param_1,char *param_2); /* 0x004827a0 */
void __cdecl grimlib_MarkDirtyRect(int *rect,int flags); /* 0x00482800 */
int __cdecl grimlib_ConfirmClose(void); /* 0x004828d0 */
void __cdecl grimlib_RequestShutdown(int exitCode); /* 0x004828e0 */
void __cdecl grimlib_SetPause(int paused); /* 0x00482900 */
undefined * __cdecl grimlib_CharacterCallback(int param_1); /* 0x00482980 */
void __cdecl grimlib_UpdateManual(int draw,int frameMs); /* 0x00482990 */
void __cdecl gimlib_SetImuseState(int state); /* 0x00482ae0 */
void __cdecl grimlib_Display(void); /* 0x00482af0 */
uint __cdecl Engine_RegisterSubsystems(uint param_1,undefined4 *param_2,int param_3,int param_4); /* 0x00482cf0 */
uint __cdecl Engine_InitSubsystems(int param_1,int param_2); /* 0x00482d60 */
uint __cdecl Engine_ShutdownSubsystems(int param_1,int param_2); /* 0x00482dd0 */
uint __cdecl Engine_ResetSubsystems(int param_1,int param_2); /* 0x00482e00 */
void __cdecl PerfBegin(int param_1); /* 0x00482e30 */
undefined * __cdecl PerfEnd(int param_1); /* 0x00482e80 */
uint __cdecl grimlib_PlayMovie(uint param_1,int param_2,uint param_3,uint param_4,uint param_5); /* 0x00482f00 */
void __cdecl grimlib_UserPaint(void); /* 0x00482f80 */
void __cdecl grimlib_Save(char *param_1); /* 0x00482f90 */
void __cdecl grimlib_Load(char *param_1); /* 0x00482fb0 */
uint __cdecl grimlib_JustLoaded(void); /* 0x00482fd0 */
void __cdecl Engine_SaveGame(void); /* 0x00482fe0 */
void __cdecl Engine_LoadGame(void); /* 0x00483240 */
void __cdecl SetPrevMode(uint param_1); /* 0x004835f0 */
uint __cdecl GetPrevMode(void); /* 0x00483600 */
uint __cdecl sputRender_Open(void); /* 0x00484000 */
void __cdecl sputRender_Update(void); /* 0x00484260 */
void __cdecl sputControl_AddCallback(void *fn); /* 0x0048d1a0 */
void __cdecl sputControl_Update(undefined4 param_1,undefined4 param_2); /* 0x0048d1c0 */

/* ===== set.c ===== */
int __cdecl Res_NumRefs(void *param_1); /* 0x004824c0 */
void __cdecl grimlib_MakeCurrentSet(char *name); /* 0x00482670 */
void * __cdecl grimlib_MakeCurrentSetup(uint setup); /* 0x00482820 */
void __cdecl sputRender_SyncCamera(void *set,int setupIdx); /* 0x00483aa0 */
void __cdecl sputRender_UseSetup(void *set,int setupIdx); /* 0x00483b50 */
void __cdecl Set_DrawDebugLights(int param_1); /* 0x00485780 */
void __cdecl Set_DrawDebugCameras(void *set,uint setupIdx); /* 0x004859c0 */
void __cdecl sputRoom_SetSoundParameters (int param_1,uint param_2,byte param_3,byte param_4,uint param_5,uint param_6); /* 0x004a4010 */
void __cdecl sputRoom_GetSoundParameters(void *set,float *minVol,char *maxVol,char *c,float *d,float *e); /* 0x004a4050 */
void __cdecl sputRoom_SetCurrentRoom(void *set,int param_2); /* 0x004a40f0 */
void * sputRoom_GetCurrentRoom(void); /* 0x004a41b0 */
char * sputRoom_GetCurrentRoomName(void); /* 0x004a41d0 */
int __cdecl sputRoom_Save(void *writeFn); /* 0x004a41e0 */
int __cdecl sputRoom_Restore(void *readFn); /* 0x004a44e0 */
undefined4 * __cdecl sputRoom_LoadRoom(char *param_1); /* 0x004a49a0 */
void __cdecl Set_InitRecord(undefined4 *param_1); /* 0x004a4a70 */
void __cdecl sputRoom_UnReference(void *set); /* 0x004a4b40 */
void __cdecl sputRoom_FreeRoom(uint param_1); /* 0x004a4c40 */
void __cdecl sputRoom_FreeRoomEntry(char *param_1); /* 0x004a4c60 */
void __cdecl Set_FreeSetups(int param_1); /* 0x004a4d10 */
void __cdecl Set_FreeSetup(uint param_1,int param_2); /* 0x004a4d80 */
int __cdecl sputRoom_LoadResources(void *set); /* 0x004a4fe0 */
int __cdecl Set_RegisterHandle(char *name,void *fn); /* 0x004a54a0 */
int Set_FindHandle(char *name); /* 0x004a5500 */
int Set_IsHandleValid(char *param_1); /* 0x004a55d0 */
void * __cdecl GetRoomActors(char *setName); /* 0x004a60a0 */
void * __cdecl Set_FindNameInList(int param_1); /* 0x004a60c0 */
void * __cdecl Set_NormalizeName(char *setName); /* 0x004a6100 */
void __cdecl WalkPlane_KillCollection(void *param_1); /* 0x004a7100 */
void __cdecl WalkPlane_SetCollection(void *set); /* 0x004a7150 */

/* ===== enginemodule.c ===== */
undefined * __cdecl grimlib_GameInitialize(GrimServices *param_1,undefined **param_2); /* 0x00482540 */
undefined * grimlib_GameTerminate(void); /* 0x00482b60 */
int __cdecl grimlib_GameStartup(void); /* 0x00482ba0 */
undefined * grimlib_GameShutdown(void); /* 0x00482cc0 */

/* ===== savegame.c ===== */
int __cdecl SaveGame_Write(void *data,int bytes); /* 0x004831f0 */
int __cdecl SaveGame_Read(void *buf,int n); /* 0x00483470 */
void * __cdecl sputMain_GetSaveGameImage(char *filename); /* 0x00483490 */

/* ===== imuse.c ===== */
void __cdecl IMuse_SaveToTemp(void); /* 0x00483610 */
void __cdecl IMuse_RestoreFromTemp(void); /* 0x00483650 */

/* ===== imusemodule.c ===== */
uint __cdecl PolyglotInitialize(GrimServices *param_1,undefined4 *param_2); /* 0x004836b0 */
void __cdecl polyglot_shutdown(void); /* 0x004836f0 */

/* ===== polyglot.c ===== */
void __cdecl PolyglotConfigure(undefined *param_1); /* 0x00483720 */
char * __cdecl PolyglotGetString(char *textId); /* 0x004838e0 */

/* ===== render.c ===== */
uint * __cdecl Render_GetBackBuffer(void); /* 0x004839f0 */
void __cdecl sputRender_DrawDebuggingToggle(void); /* 0x00483a00 */
void __cdecl sputRender_SetPaletteCallback(uint param_1); /* 0x00483a80 */
void __cdecl sputRender_SetPageFlipCallback(void *param_1); /* 0x00483a90 */
int __cdecl sputRender_Save(void *writeFn); /* 0x00483da0 */
int __cdecl sputRender_Restore(void *readFn); /* 0x00483e20 */
void __cdecl sputRender_Using3DHardware(int param_1); /* 0x00483ea0 */
void __cdecl sputRender_PageCountIs(int n); /* 0x00483eb0 */
void __cdecl sputRender_MarkDirtyRect(int *rect,int flag); /* 0x00483ed0 */
void __cdecl MarkDirtyRect(int *rect,int flag); /* 0x00483f60 */
uint __cdecl sputRender_SetDisplay (uint param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6,int param_7 ); /* 0x00484030 */
void __cdecl sputRender_Close(void); /* 0x004841f0 */
void __cdecl sputRender_PageFlip(void); /* 0x004849a0 */
void __cdecl Render_SetPixelFormat(uint *param_1); /* 0x004849d0 */
uint __cdecl sputRender_ControlHandler(void); /* 0x00484a50 */
void __cdecl Render_InitColorConstants(int param_1); /* 0x00484c40 */
void __cdecl Render_DrawDebugGrid(void); /* 0x00485bd0 */
int __cdecl Render_CanvasIsPaletted(void); /* 0x00486100 */
void __cdecl Render_BuildActorDrawList(void); /* 0x00486120 */
void __cdecl sputRender_ReverseProject(int x,int y,float *outPos); /* 0x004862e0 */
void __cdecl sputRender_PreRendered(int redrawBackground,int redrawDepth); /* 0x004863b0 */
void __cdecl Render_BuildColorTable(int param_1,float param_2); /* 0x004864a0 */
void __cdecl sputRender_ColorCorrect(ushort *pixels,uint n); /* 0x00486620 */
void __cdecl sputRender_SetGamma(float gamma); /* 0x00486710 */
void __cdecl sputRender_Decompress(void *param_1); /* 0x00486760 */
void __cdecl sputRender_Dim(ushort *param_1,byte param_2); /* 0x004867d0 */
void __cdecl Render_CopyBackBufferToBackground(void); /* 0x00486990 */
void __cdecl Render_CleanBuffer(void); /* 0x004869b0 */
void __cdecl sputRender_ForceRefresh(void); /* 0x00486a00 */
void * __cdecl sputRender_CleanArtBuffer(void); /* 0x00486b00 */
void * __cdecl sputRender_CleanZBuffer(void); /* 0x00486b10 */
code * __cdecl sputRender_SetPaletteFunc(void); /* 0x00486b20 */
void __cdecl sputRender_SetPageFlip(int param_1); /* 0x00486b30 */
void __cdecl sputRender_DrawIrisEffect(float percent,int x,int y); /* 0x00486d00 */
void __cdecl sputRender_IrisDown(int x,int y,int durationMs); /* 0x00486eb0 */
void __cdecl sputRender_IrisUp(int x,int y,int durationMs); /* 0x00486ef0 */
uint __cdecl sputRender_IrisComplete(void); /* 0x00486f30 */
void * __cdecl sputRender_ScreenShot(int w,int h); /* 0x00486f90 */
void __cdecl sputRender_DimRegion(int x,int y,int w,int h,float scale); /* 0x004870e0 */
void __cdecl sputRender_SaveScreen(char *filename); /* 0x00487260 */
void __cdecl Render_SaveZBufferBmp(char *filename); /* 0x004872f0 */
void __cdecl sputRender_SaveDrawBuffer(char *filename); /* 0x00487340 */
void __cdecl Render_DrawProgressBar(float fraction); /* 0x004873d0 */
void __cdecl sputRender_AllowLoadImage(uint param_1); /* 0x004874c0 */
void __cdecl sputRender_DrawLoadingImage(void); /* 0x004874d0 */
int __cdecl sputActor_GetNumActorsTalking(void); /* 0x0048f920 */

/* ===== sputrender.c ===== */
uint __cdecl sputRender_Initialize(GrimServices *param_1,undefined4 *param_2); /* 0x00483d40 */
void __cdecl sputRender_Terminate(void); /* 0x00486050 */
int __cdecl sputRender_Startup(void); /* 0x00486070 */
void __cdecl sputRender_Shutdown(void); /* 0x004860d0 */

/* ===== actor.c ===== */
void __cdecl Actor_ComputeScreenBox(Actor *actor); /* 0x00485290 */
void __cdecl Actor_DrawDebugWalker(Actor *actor); /* 0x00485320 */
TextObject * __cdecl sputText_CreateActorText(Actor *actor,char *text,int x,int y); /* 0x0048b2e0 */
int __cdecl sputActor_SetCostume(Actor *actor,char *name,int param_3); /* 0x0048f930 */
void __cdecl sputActor_SetActorHead (void *actor,int joint1,int joint2,int joint3,float maxRoll,float maxPitch,float maxYaw); /* 0x0048f9d0 */
int __cdecl sputActor_CanActorSeePoint(Actor *actor,float *point,float *outDistance); /* 0x0048fa60 */
int __cdecl sputActor_CanActorSeeActor(Actor *viewer,Actor *target,float *outDistance); /* 0x0048fb80 */
void __cdecl sputActor_Turn(Actor *actor,float param_2); /* 0x0048fbd0 */
void __cdecl sputActor_Forward(Actor *actor); /* 0x0048fc80 */
void __cdecl Actor_UpdateMovement(Actor *actor,float param_2); /* 0x0048fd90 */
void __cdecl Actor_UpdateLookAt(Actor *actor,float dt); /* 0x0048fe80 */
void __cdecl sputActor_UpdateActorSpeech(Actor *actor,float dt); /* 0x00490210 */
int __cdecl sputActor_SetSelectedActor(int handle); /* 0x00490320 */
Actor * __cdecl sputActor_ActorDeref(int handle); /* 0x00490360 */
int __cdecl sputActor_GetActorHandle(Actor *actor); /* 0x00490380 */
int sputActor_AllocateActor(void); /* 0x004903a0 */
void __cdecl sputActor_AllocateActorExtra(Actor *actor); /* 0x00490580 */
void __cdecl sputActor_EnableWalkSystem(Actor *actor,int param_2); /* 0x004906b0 */
void __cdecl sputActor_EnablePuck(Actor *actor,int param_2); /* 0x00490730 */
void __cdecl sputActor_SetActorPosition(Actor *actor,float *param_2); /* 0x00490870 */
void __cdecl sputActor_SetActorRotation(Actor *actor,undefined4 *param_2,int param_3); /* 0x00490900 */
void __cdecl sputActor_SetReflection(Actor *actor,float angle); /* 0x00490a40 */
void __cdecl sputActor_SetTurnChores(Actor *actor,int leftChore,int rightChore,CostumeNode *costume); /* 0x00490b50 */
void __cdecl sputActor_SetRestChore(Actor *actor,int chore,CostumeNode *costume); /* 0x00490c80 */
int __cdecl sputActor_PushCostume(Actor *actor,char *name,int param_3); /* 0x00490d30 */
void __cdecl sputActor_PopCostume(Actor *actor,int free); /* 0x00490dd0 */
void __cdecl Actor_PuckOrient(Actor *actor); /* 0x00490f50 */
void __cdecl Actor_UpdateWalker(Actor *actor); /* 0x00491110 */
void __cdecl Actor_UpdateMoveChores(Actor *actor); /* 0x004913f0 */
void __cdecl sputActor_SayLine(Actor *actor,char *text,int background,int volume,int pan,int x,int y); /* 0x00492b30 */
void __cdecl sputActor_ShutUp(Actor *actor); /* 0x00493060 */
void __cdecl sputActor_LeaveSector(int a1,int a2); /* 0x004931f0 */
void __cdecl Actor_FollowPath(Actor *actor); /* 0x00493230 */
void __cdecl sputActor_SetWalkDominate(Actor *actor,int dominate); /* 0x004933c0 */
void __cdecl sputActor_SetActorConstrain(Actor *actor,int param_2); /* 0x004933e0 */
int __cdecl Actor_IsVoicePlaying(Actor *actor); /* 0x004934b0 */
int __cdecl sputActor_ActorHasShadow(Actor *actor); /* 0x00493510 */
void __cdecl sputActor_ActivateActorShadow(Actor *actor,int shadowIdx,int active); /* 0x00493540 */
void __cdecl sputActor_SetShadowPlane(Actor *actor,char *param_2); /* 0x00493570 */
void __cdecl sputActor_SetShadowPoint(Actor *actor,float x,float y,float z); /* 0x004935f0 */
void __cdecl sputActor_SetShadowValid(Actor *actor,int shadowIdx,int valid); /* 0x00493630 */
void __cdecl sputActor_AddShadowClipPlane(Actor *actor,int shadowIdx,char *sectorName); /* 0x00493660 */
void __cdecl sputActor_ResetShadows(Actor *actor); /* 0x004936b0 */
void __cdecl sputCostume_DrawActorShadow(Actor *actor); /* 0x004936e0 */
float * __cdecl sputActor_GetOrientMatrix(Actor *actor); /* 0x00493790 */
void __cdecl sputActor_DrawToClean(Actor *actor); /* 0x004937c0 */
int __cdecl Actor_CountCostumes(Actor *actor); /* 0x00494690 */
void __cdecl sputActor_SetClipPlane(Actor *actor,undefined4 *param_2,undefined4 *param_3); /* 0x004946b0 */
void __cdecl sputActor_SetClipPlaneActive(Actor *actor,int param_2); /* 0x00494710 */
void __cdecl sputActor_SetFrustrumCull(Actor *actor,int param_2); /* 0x00494780 */
void __cdecl sputActor_FreeActor(Actor *actor); /* 0x004947c0 */
void __cdecl sputCostume_DrawMeshShadow(CostumeNode *costumeList,ActorShadow *shadow); /* 0x00494940 */
void __cdecl sputCostume_Draw3D(uint param_1,uint param_2); /* 0x00495080 */
void __cdecl sputCostume_InternalDraw3D(int *param_1,float *param_2); /* 0x004950a0 */
void __cdecl sputRoom_RemoveActor(char *setName,void *actor); /* 0x004a5eb0 */
void __cdecl sputRoom_AddActor(Actor *actor,char *setName); /* 0x004a5f60 */
float __thiscall Puck_GetYawToPoint(Puck *this,float *point); /* 0x004a8500 */

/* ===== dirtyrect.c ===== */
void __cdecl DirtyRect_Add(int *rect,int flag,int bufferIdx); /* 0x00485420 */
void __cdecl DirtyRect_Flush(void *dst,void *zdst); /* 0x00485e50 */
void __cdecl DirtyRect_Clear(void); /* 0x00486020 */

/* ===== setup.c ===== */
void __cdecl Setup_DrawDebugCamera(int param_1); /* 0x00485a40 */
void * __cdecl sputRoom_GetSetupBackground(void *set,int setupIdx); /* 0x004a3db0 */
void * __cdecl sputRoom_GetSetupZBackground(void *set,int setupIdx); /* 0x004a3ef0 */

/* ===== sector.c ===== */
void __cdecl Sector_DrawAllDebug(void); /* 0x00485dc0 */
void __cdecl sputLua_CollisionHandler(int self,int other,float *a,float *b,float *c); /* 0x0049c750 */
int __cdecl SetFile_Parse(char *param_1,uint param_2); /* 0x004a4b00 */
uint __cdecl sputRoom_LoadRoomEntry(uint param_1); /* 0x004a5550 */
uint __cdecl sputRoom_ParseColormaps(void); /* 0x004a5b40 */
uint __cdecl sputRoom_ParseSectors(void); /* 0x004a5c90 */
void __cdecl WalkPlane_BuildCache(void); /* 0x004a61c0 */
void __cdecl WalkPlane_DestroyCache(void); /* 0x004a6330 */
void __cdecl WalkPlane_RestoreCache(void); /* 0x004a6380 */
WalkPlane * __thiscall WalkPlane_Construct(WalkPlane *this,int a1,int a2,int a3); /* 0x004a6490 */
void __fastcall WalkPlane_Destruct(WalkPlane *plane); /* 0x004a66e0 */
void __thiscall WalkPlane_SetName(WalkPlane *this,char *name); /* 0x004a6760 */
void __thiscall WalkPlane_SetType(WalkPlane *this,uint type); /* 0x004a6790 */
int __thiscall WalkPlane_Within(WalkPlane *this,float *point,int checkActive); /* 0x004a6980 */
int __thiscall WalkPlane_ClosestPoint(WalkPlane *this,int a1); /* 0x004a6b30 */
float __thiscall WalkPlane_Intersection(WalkPlane *this,int a1,int a2,int a3); /* 0x004a6d10 */
void __thiscall WalkPlane_SnapTo(WalkPlane *this,float *pos); /* 0x004a6fa0 */
int __thiscall WalkPlane_Project(WalkPlane *this,int a1); /* 0x004a7000 */
void __thiscall WalkPlane_Draw(WalkPlane *this,int color); /* 0x004a70a0 */
WalkPlane * __cdecl WalkPlane_PlaneAt(float *point,uint mask); /* 0x004a71e0 */
WalkPlane * __cdecl WalkPlane_PlaneNamed(char *name); /* 0x004a7230 */
WalkPlane * __cdecl WalkPlane_PlaneNumbered(int id); /* 0x004a7290 */
WalkPlane * __cdecl WalkPlane_PlaneClosest(float *point,uint mask); /* 0x004a72b0 */
void __thiscall WalkPlane_JumpOut(WalkPlane *this,float *walker); /* 0x004a7390 */
float * __thiscall WalkPlane_GetConstraintVector(WalkPlane *this,float *walker); /* 0x004a7520 */
void __cdecl WalkPlane_AllActive(void); /* 0x004a7a90 */
WalkVertex * __cdecl WalkPlane_AddVertex(uint param_1,float *param_2); /* 0x004a7ab0 */
void __cdecl WalkPlane_RemoveVertex(int *param_1); /* 0x004a7ba0 */
undefined * __cdecl ParseCollection(int param_1); /* 0x004a7bc0 */
int __thiscall WalkPlane_ClipPoly(WalkPlane *this,float *verts,int count,float *out); /* 0x004a8cb0 */
float __thiscall WalkPlane_DistToEdge(WalkPlane *this,int edge,float *point); /* 0x004a9070 */
undefined4 __fastcall WalkPlane_RemoveShortEdge(WalkPlane *plane); /* 0x004a9180 */
void __cdecl ShrinkBoxes(float radius); /* 0x004a9d00 */

/* ===== drawlist.c ===== */
void __cdecl DrawList_Reset(void); /* 0x00486250 */
undefined * __cdecl DrawList_Alloc(void); /* 0x00486280 */
uint __cdecl FUN_004862b0(int *param_1,int *param_2); /* 0x004862b0 */

/* ===== plane.c ===== */
int __cdecl sputRender_SegmentPlaneIntersect(float *out,float *p1,float *p2,float a,float b,float c,float d); /* 0x00486a10 */

/* ===== cacherect.c ===== */
void * __cdecl sputRender_CreateCacheRect(int x,int y,int w,int h); /* 0x00486b40 */
void __cdecl sputRender_RestoreCacheRect(int unused); /* 0x00486c50 */
void __cdecl CacheRect_FreeAll(void); /* 0x00486cb0 */

/* ===== dlg.c ===== */
undefined4 * __cdecl Dlg_MakeItemTemplate (uint param_1,ushort param_2,ushort param_3,ushort param_4,ushort param_5,ushort param_6, int param_7,int param_8,uint *param_9); /* 0x00488010 */
uint * __cdecl Dlg_MakeDialogTemplate (undefined4 *param_1,ushort param_2,ushort param_3,ushort param_4,ushort param_5, ushort param_6,int param_7,int param_8,ushort param_9,uint *param_10); /* 0x004881a0 */

/* ===== spew.c ===== */
void __cdecl Spew_Startup(void); /* 0x00488840 */
void __cdecl grimDebug_Shutdown(void); /* 0x00488860 */
void __cdecl Spew_LoadDll(void); /* 0x00488890 */

/* ===== fileutil.c ===== */
uint __cdecl FileUtil_SysInitialize(GrimServices *param_1,undefined4 *param_2); /* 0x00488c80 */
void __cdecl FileUtil_SysTerminate(void); /* 0x00488ce0 */
uint __cdecl FileUtil_SysStartup(void); /* 0x00488cf0 */
void __cdecl FileUtil_SysShutdown(void); /* 0x00488d20 */
uint __cdecl FileUtil_SysSave(code *param_1); /* 0x00488d30 */

/* ===== savefile.c ===== */
uint __cdecl FileUtil_SysRestore(code *param_1); /* 0x00488d80 */
void * SaveFile_Open(char *name,char *mode); /* 0x004c3e40 */

/* ===== dirscan.c ===== */
undefined4 * __cdecl DirScan_Create(uint param_1,int param_2,char *param_3); /* 0x00488de0 */
void __cdecl DirScan_Destroy(int param_1); /* 0x00488e70 */
void __cdecl DirScan_Reset(int param_1); /* 0x00488eb0 */
uint __cdecl DirScan_Next(int param_1,char *param_2); /* 0x00488ee0 */

/* ===== sputsmush.c ===== */
uint __cdecl sputSmush_Initialize(uint param_1,undefined4 *param_2); /* 0x00488fb0 */
uint __cdecl sputSmush_Startup(void); /* 0x00489130 */
void __cdecl sputSmush_Shutdown(void); /* 0x00489190 */

/* ===== movie.c ===== */
int __cdecl sputSmush_Save(void *fn); /* 0x00489030 */
uint __cdecl sputSmush_Restore(code *param_1); /* 0x00489090 */
uint __cdecl sputSmush_Periodic(void); /* 0x004891b0 */
int __cdecl sputSmush_SetTarget(void *surface); /* 0x00489280 */
uint __cdecl sputSmush_StartMovie(char *param_1,int param_2,uint param_3,uint param_4); /* 0x004892a0 */
void __cdecl sputSmush_StopMovie(void); /* 0x00489370 */
int __cdecl sputSmush_GetMovieLength(char *param_1); /* 0x00489390 */
uint __cdecl sputSmush_StartVideo(int param_1,int param_2,int param_3); /* 0x004893d0 */
int __cdecl sputSmush_StopVideo(void); /* 0x00489410 */
uint __cdecl sputSmush_LockMovieBuffer(undefined4 *param_1,undefined4 *param_2); /* 0x00489420 */
uint __cdecl sputSmush_UnLockMovieBuffer(void); /* 0x004894b0 */
int __cdecl sputSmush_SetVideoPalette(void); /* 0x004894d0 */
int __cdecl sputSmush_MoviePlaying(void); /* 0x004894e0 */
void sputSmush_Pause(int paused); /* 0x004894f0 */

/* ===== primitivelist.c ===== */
void PrimitiveList_StaticConstruct(void); /* 0x00489510 */
void PrimitiveList_InitGlobal(void); /* 0x00489520 */
void __cdecl PrimitiveList_RegisterAtExit(void); /* 0x00489530 */
void __cdecl PrimitiveList_AtExitClear(void); /* 0x00489540 */
void __fastcall PrimitiveQueue_Construct(undefined4 *param_1); /* 0x0048a500 */
void __fastcall PrimitiveQueue_purge(int *param_1); /* 0x0048a520 */
void * __thiscall PrimitiveQueue_addObject(void *this,int id,int layer); /* 0x0048a670 */
void __thiscall PrimitiveQueue_draw(void *this,void *canvas,uint layerMask); /* 0x0048a9f0 */
undefined * __thiscall PrimitiveQueue_markAllDirty(void *this,int a1); /* 0x0048ab20 */
void * __thiscall PrimitiveQueue_findPrimitive(void *this,int id,void *after); /* 0x0048abd0 */

/* ===== primitives.c ===== */
void __cdecl sputPrimitive_Update(uint layerMask); /* 0x00489550 */
void __cdecl sputPrimitive_Pause(void); /* 0x004895d0 */
void __cdecl sputPrimitive_Resume(void); /* 0x004895f0 */
void * __thiscall PrimitiveObject_Construct(void *this,int id,int unused); /* 0x0048a4b0 */
int __thiscall PrimitiveQueue_addLine(void *this,int x1,int y1,int x2,int y2,int color,int layer); /* 0x0048a560 */
int __thiscall PrimitiveQueue_addRect(void *this,int x1,int y1,int x2,int y2,int color,int filled,int layer); /* 0x0048a5b0 */
int __thiscall PrimitiveQueue_addPolygon(void *this,int count,int *points,int color,int layer); /* 0x0048a600 */
void __thiscall PrimitiveQueue_deletePrimitive(void *this,int id); /* 0x0048a740 */
int __thiscall PrimitiveQueue_changeColor(void *this,int id,int color); /* 0x0048a7b0 */
int __thiscall PrimitiveQueue_changeLayer(void *this,int id,int layer); /* 0x0048a7e0 */
int __thiscall PrimitiveQueue_move(void *this,int id,int dx,int dy); /* 0x0048a830 */
int __thiscall PrimitiveQueue_moveTo(void *this,int id,int x,int y); /* 0x0048a8a0 */
int __thiscall PrimitiveQueue_moveEndpoint(void *this,int id,int x,int y); /* 0x0048a960 */
int __thiscall PrimitiveQueue_changeDimensions(void *this,int id,int w,int h); /* 0x0048a9a0 */
void __stdcall PrimitiveQueue_drawPrimitive(void *prim,void *canvas); /* 0x0048aa20 */
int __thiscall PrimitiveQueue_markDirty(void *this,void *prim); /* 0x0048ab50 */
void __cdecl PrimitiveQueue_resetId(void); /* 0x0048abc0 */

/* ===== sputprimitive.c ===== */
uint __cdecl sputPrimitive_Initialize(uint param_1,undefined4 *param_2); /* 0x00489580 */
uint __cdecl sputPrimitive_Save(code *param_1); /* 0x00489600 */
uint __cdecl sputPrimitive_Restore(code *param_1); /* 0x004896b0 */
void __cdecl sputPrimitive_Terminate(void); /* 0x004897d0 */
uint __cdecl sputPrimitive_Startup(void); /* 0x004897f0 */
void __cdecl sputPrimitive_Shutdown(void); /* 0x00489820 */

/* ===== list.c ===== */
void __cdecl List_Unlink(void *obj); /* 0x0048ac00 */

/* ===== textobjects.c ===== */
void __cdecl sputText_Update(int drawAll); /* 0x0048ac40 */
void __cdecl sputText_Pause(void); /* 0x0048ad40 */
void __cdecl sputText_Resume(void); /* 0x0048ad50 */

/* ===== sputtext.c ===== */
uint __cdecl sputText_Initialize(GrimServices *param_1,undefined4 *param_2); /* 0x0048acc0 */
void __cdecl sputText_Terminate(void); /* 0x0048c4d0 */
uint __cdecl sputText_Startup(void); /* 0x0048c500 */
void __cdecl sputText_Shutdown(void); /* 0x0048c6f0 */
uint __cdecl sputText_Save(code *param_1); /* 0x0048cbc0 */
uint __cdecl sputText_Restore(code *param_1); /* 0x0048cd80 */

/* ===== text.c ===== */
int __cdecl GetTextParamsFromTable(TextContext *ctx,void *table,TextObject *textObj); /* 0x0048c050 */
char * __cdecl sputText_ExtractSayLineData(char *line,char *outId); /* 0x0048c8d0 */
int __cdecl sputActor_GetActorTextRate(void); /* 0x00494740 */
void __cdecl sputActor_SetActorTextRate(int speed); /* 0x00494750 */
void * __cdecl Text_GetSystemFont(void); /* 0x004aa930 */
int __cdecl Text_LoadNativeFont(char *filename,void **outFont); /* 0x004aa940 */
void __cdecl Text_FreeFont(void *font); /* 0x004aa990 */
int __cdecl Text_NextChar(char **pText); /* 0x004aa9b0 */
int __cdecl Text_GetCharKernedWidth(TextContext *ctx,int ch); /* 0x004aaa20 */
int __cdecl Text_GetStringWidth(TextContext *ctx,char *text); /* 0x004aaa80 */
int __cdecl Text_GetStringHeight(TextContext *ctx,char *text); /* 0x004aab10 */
uint __cdecl Text_DrawFormatted(TextContext *ctx,char *fmt,...); /* 0x004aabb0 */
uint __cdecl Text_WrapLines(uint *param_1); /* 0x004aac40 */
void __cdecl Text_CopyRunes(byte *param_1,undefined4 *param_2,int param_3,int param_4); /* 0x004aae90 */
uint __cdecl Text_BuildLineTable(uint param_1,int *param_2); /* 0x004aaf30 */
char * __cdecl text_FindNextBreak(TextContext *param_1,void *param_2,char *param_3,int *param_4,uint *param_5, int param_6); /* 0x004ab210 */
uint __cdecl Font_GlyphAdvance(TextContext *ctx,void *font,int ch); /* 0x004ab510 */
uint __cdecl Font_GlyphWidth(int param_1,int param_2,uint param_3); /* 0x004ab570 */
void __cdecl Text_DrawString(TextContext *ctx,void *font,char *text); /* 0x004ab5d0 */
void __cdecl Text_DrawChar(void *ctx,void *font,int ch); /* 0x004ab710 */

/* ===== textobject.c ===== */
void __cdecl sputText_AddToQueue(TextObject *obj,int durationMs,int flags); /* 0x0048c470 */
TextObject * __cdecl TextObject_New(TextContext *ctx,char *text); /* 0x0048c7e0 */
void __cdecl TextObject_Draw(TextObject *obj,int invalidate); /* 0x0048c9f0 */
TextObject * __cdecl sputText_FindSerialNumber(int serial); /* 0x0048cba0 */

/* ===== controls.c ===== */
int __cdecl Controls_DebugKeysHook(uint param_1); /* 0x0048d030 */
void __cdecl sputControl_Reset(void); /* 0x0048d050 */

/* ===== control.c ===== */
void __cdecl sputControl_EnableControl(int control); /* 0x0048d090 */
void __cdecl sputControl_DisableControl(int control); /* 0x0048d0d0 */
undefined * sputControl_Open(void); /* 0x0048d150 */
uint __cdecl sputControl_Close(void); /* 0x0048d170 */

/* ===== sputcontrol.c ===== */
uint __cdecl sputControl_Initialize(uint param_1,undefined4 *param_2); /* 0x0048d100 */
void __cdecl sputControl_Terminate(void); /* 0x0048d2c0 */
uint __cdecl sputControl_Startup(void); /* 0x0048d2e0 */
void __cdecl sputControl_Shutdown(void); /* 0x0048d330 */

/* ===== debug.c ===== */
uint __cdecl sputControl_StandardHandler(void); /* 0x0048d210 */

/* ===== sputresource.c ===== */
undefined * __cdecl sputResource_Initialize(uint param_1,undefined **param_2); /* 0x0048d4e0 */
void __cdecl sputResource_Terminate(void); /* 0x0048d770 */
int __cdecl sputResource_Startup(void); /* 0x0048d790 */
void __cdecl sputResource_Shutdown(void); /* 0x0048d830 */

/* ===== actors.c ===== */
void __cdecl sputActor_NukeCostumeStacks(void); /* 0x0048e240 */
void __cdecl sputActor_UpdateSpeechOnly(float dt); /* 0x0048fcc0 */
void __cdecl sputActor_UpdateActors(float dt); /* 0x0048fcf0 */

/* ===== sputactor.c ===== */
uint __cdecl sputActor_Initialize(uint param_1,undefined4 *param_2); /* 0x0048e2c0 */
uint __cdecl sputActor_Save(code *param_1); /* 0x0048e330 */
uint __cdecl sputActor_Restore(code *param_1); /* 0x0048ecd0 */
void __cdecl sputActor_SetWalkChore(Actor *actor,int chore,CostumeNode *costume); /* 0x00490a60 */
void __cdecl sputActor_Terminate(void); /* 0x00490e60 */
uint __cdecl sputActor_Startup(void); /* 0x00490e80 */
void __cdecl sputActor_Shutdown(void); /* 0x00490ef0 */

/* ===== phoneme.c ===== */
uint __cdecl Phoneme_ToTalkChore(void *unused,int phoneme); /* 0x00490e00 */
int __cdecl ComparePhonemes(int *param_1,int *param_2); /* 0x00490e50 */

/* ===== walker.c ===== */
undefined4 __cdecl sputActor_AlignToPuck(Actor *actor,float *param_2); /* 0x00491230 */
void __cdecl sputActor_ActorWalkTo(Actor *actor,int param_2,undefined4 *param_3,Actor *param_4); /* 0x00491650 */
uint __cdecl Walker_AvoidActorPath(Actor *self,Actor *other,undefined4 *pts,uint count,float *out); /* 0x004917e0 */
void __cdecl sputActor_SetWalkSystemFadeTime(int ms); /* 0x00494880 */
Puck * __thiscall Puck_Construct(Puck *this,float radius); /* 0x004a8200 */
void __fastcall Puck_Destruct(Puck *puck); /* 0x004a8270 */
undefined * __fastcall Puck_Rot(Puck *puck); /* 0x004a82a0 */
void __fastcall Puck_Validate(Puck *puck); /* 0x004a82c0 */
void __thiscall Puck_SetPos(Puck *this,float *pos); /* 0x004a8310 */
void __thiscall Puck_Xform(Puck *this,float *vec); /* 0x004a8350 */
void __thiscall Puck_InvXform(Puck *this,float *vec); /* 0x004a8370 */
void __thiscall Puck_Rotate(Puck *this,float angle); /* 0x004a83c0 */
float __thiscall Puck_PointAt(Puck *this,float *point,float maxTurn); /* 0x004a8450 */
void __thiscall Puck_Constrain(Puck *this,int a1); /* 0x004a85b0 */
undefined * __thiscall Puck_Forward(Puck *this,float step,int turnLeftOk,int turnRightOk); /* 0x004a8610 */
void __thiscall Puck_OrientToPlane(Puck *this,int a1); /* 0x004a89b0 */
void __fastcall Puck_Normalize(Puck *puck); /* 0x004a8a90 */
void __thiscall Puck_Draw(Puck *this,int color); /* 0x004a8b00 */
uint __cdecl GetPath(undefined4 *out); /* 0x004a9420 */
int __cdecl BuildPath(float *from,float *to,int flags); /* 0x004a9430 */
undefined4 __cdecl Planner_FindPath(float *param_1,float *param_2,WalkPlane *plane); /* 0x004a94d0 */
uint __cdecl FindExitPoints(WalkPlane *plane,float *param_2,uint *param_3); /* 0x004a96f0 */
undefined4 __cdecl Planner_PortalPoint(WalkPlane *planeA,WalkPlane *planeB,float *point,float *out); /* 0x004a9920 */
uint __cdecl TightenPath(void); /* 0x004a9aa0 */
WalkPlane * __cdecl Planner_SharedSector(float *from,float *to); /* 0x004a9ca0 */

/* ===== collision.c ===== */
void __cdecl GetOuttaTheBox(float *pos,float xmin,float ymin,float zmin,float xmax,float ymax,float zmax, float *frame,float *out); /* 0x004922d0 */
int __cdecl Collision_PointInBox (float *a,float *b,float *p3,float bx0,float by0,float bz0,float bx1,float by1,float bz1, float *p10,float *offset); /* 0x00492510 */
void __cdecl FindObjectCorners(int param_1,float param_2,float *param_3,float param_4,float *param_5); /* 0x004925c0 */
int __cdecl TestCollision(float *from,float *to,float *hit,float xmin,float ymin,float zmin,float xmax, float ymax,float zmax,float *frame); /* 0x00492680 */
int __cdecl Collision_PickDetour(float *param_1,float *param_2,int param_3); /* 0x00492a50 */
uint __cdecl Collision_UpdateMovedActors(void); /* 0x004939a0 */
uint __cdecl Collision_TestActorAgainstOthers(Actor *param_1); /* 0x004939f0 */
undefined4 __cdecl Collision_BoxSlide(float *from,float *to,float xmin,float ymin,float zmin,float xmax,float ymax, float zmax,float *out); /* 0x00494100 */

/* ===== speech.c ===== */
void __cdecl sputActor_SetSpeechMode(int mode); /* 0x004931c0 */
uint __cdecl sputActor_GetSpeechMode(void); /* 0x004931e0 */

/* ===== costume.c ===== */
void __cdecl FadeInChore(void *param_1,uint param_2,int param_3); /* 0x00493410 */
undefined * __cdecl FadeOutChore(void *param_1,int param_2,int param_3); /* 0x00493450 */
void __cdecl sputCostume_PrintCostumeInfo(CostumeNode *costume); /* 0x00494d10 */
void __cdecl sputCostume_FreeCostumeNodes(CostumeNode *list,int free); /* 0x00494dc0 */
CostumeNode * __cdecl sputCostume_PopCostume(CostumeNode *list,int free); /* 0x00494e10 */
CostumeNode * __cdecl sputCostume_SetCostume(CostumeNode *list,void *costumeRes,int flags); /* 0x00494e50 */
CostumeNode * __cdecl sputCostume_PushCostume(CostumeNode *list,void *costumeRes,int flags); /* 0x00494e80 */
CostumeNode * __cdecl Costume_AllocRecord(void); /* 0x00494f90 */
void __cdecl Costume_InitRecord(CostumeNode *node); /* 0x00494fb0 */
void * __cdecl Costume_GetMainModel(void *cosInst); /* 0x00495020 */
void __cdecl Costume_ApplyScale(void *actor,void *componentList); /* 0x00495510 */
void __cdecl Costume_ApplyComponentState(void *cosInst); /* 0x004955e0 */
void __cdecl sputCostume_BuildThingStateMatrices(void *component,float *frame); /* 0x004956a0 */
void __cdecl sputCostume_Draw2D(int param_1); /* 0x004956f0 */
void __cdecl sputCostume_Update(CostumeNode *costumeList,float dt); /* 0x00495730 */
uint __cdecl sputCostume_SaveHook(char *param_1,uint *param_2,uint param_3); /* 0x00495e90 */
uint __cdecl Costume_InstanceHook(int param_1,int param_2); /* 0x00496020 */

/* ===== shadow.c ===== */
void __cdecl sputCostume_SetShadowColor(int r,int g,int b); /* 0x00494890 */
void __cdecl sputCostume_OutputShadowPoly(float *verts,int count,float *minXY,float *maxXY,ActorShadow *shadow); /* 0x00494bf0 */

/* ===== sputcostume.c ===== */
int __cdecl sputCostume_Initialize(GrimServices *param_1,undefined4 *param_2); /* 0x004957f0 */
void __cdecl sputCostume_Terminate(void); /* 0x00495960 */
uint __cdecl sputCostume_Startup(void); /* 0x004959a0 */
void __cdecl sputCostume_Shutdown(void); /* 0x004988a0 */

/* ===== component.c ===== */
void __cdecl BitmapChanger(uint param_1,int *param_2,uint param_3,int param_4); /* 0x00496060 */

/* ===== bitmapcomponent.c ===== */
uint __cdecl BitmapRequester(uint param_1,int param_2,int param_3,int param_4,char *param_5); /* 0x004960a0 */
undefined4 BitmapFreer(undefined4 param_1,undefined4 param_2,void *param_3); /* 0x00496340 */

/* ===== cmapcomponent.c ===== */
int * __cdecl ColormapInstancer(int inst,int component,int create); /* 0x00496370 */
int __cdecl ColormapRequester(uint param_1,int param_2,int param_3,int param_4,char *param_5); /* 0x00496460 */
undefined4 ColormapFreer(undefined4 param_1,undefined4 param_2,void *param_3); /* 0x00496580 */
uint __cdecl MaterialInstanceSaveLoad(void); /* 0x004965b0 */

/* ===== materialcomponent.c ===== */
void __cdecl MaterialChanger(uint param_1,int param_2,uint param_3,uint param_4); /* 0x004965d0 */
void * __cdecl MaterialInstancer(void *cosInst,int componentIdx,int create); /* 0x004965e0 */
int __cdecl MaterialRequester(uint param_1,int param_2,int *param_3,int param_4,char *param_5); /* 0x00496670 */

/* ===== modelcomponent.c ===== */
uint __cdecl ThingAdjuster(int *param_1,uint param_2); /* 0x00496890 */
void __cdecl ThingChanger(uint param_1,int param_2,uint param_3,int param_4); /* 0x00496930 */
void * __cdecl ThingInstancer(void *cosInst,int componentIdx,int create); /* 0x00496950 */
uint __cdecl ThingStopper(int param_1); /* 0x00496b40 */
int __cdecl ThingRequester(uint param_1,int param_2,int param_3,int param_4,char *param_5); /* 0x00496b60 */
undefined4 ThingFreer(undefined4 param_1,undefined4 param_2,void *param_3); /* 0x00496d10 */

/* ===== meshcomponent.c ===== */
void __cdecl MeshChanger(uint param_1,int *param_2,uint param_3,int param_4); /* 0x00496d40 */
int * __cdecl MeshInstancer(int inst,int component,int create); /* 0x00496d70 */
void __cdecl MeshStopper(int param_1); /* 0x00496e10 */
uint __cdecl MeshRequester(uint param_1,int param_2,int *param_3,int param_4,char *param_5); /* 0x00496e20 */
int __cdecl MeshAdjuster(uint param_1,uint param_2); /* 0x00497180 */

/* ===== imusesoundcomponent.c ===== */
void __cdecl SoundChanger(int tag,int snd,undefined4 param_3,int slot,uint param_5,uint param_6,uint param_7, uint inst); /* 0x004971a0 */
uint __cdecl SoundAdjuster(int *param_1,uint param_2); /* 0x00497320 */
int __cdecl SoundRequester(uint param_1,int param_2,int param_3,int param_4,char *param_5); /* 0x00497460 */
uint __cdecl SoundFreer(uint param_1,uint param_2,uint param_3); /* 0x00497640 */
uint __cdecl SoundStopper(int param_1); /* 0x00497660 */

/* ===== luavarcomponent.c ===== */
void __cdecl LuaVarChanger(uint param_1,char *param_2,uint param_3,int param_4); /* 0x00497680 */
uint __cdecl LuaVarAdjuster(undefined4 *param_1,int param_2,int param_3); /* 0x004976a0 */
int __cdecl LuaVarRequester(uint param_1,int param_2,int param_3,int param_4,int param_5); /* 0x00497710 */
uint __cdecl LuaVarFreer(uint param_1,uint param_2,uint param_3); /* 0x004977f0 */
uint __cdecl LuaVarStopper(char *param_1); /* 0x00497810 */

/* ===== imuseintcomponent.c ===== */
int __cdecl IMuseRequester(uint param_1,int param_2,int param_3,int param_4); /* 0x00497840 */

/* ===== keyframecomponent.c ===== */
void __cdecl KeyframeChanger(uint param_1,int *param_2,uint param_3,int param_4,uint param_5,uint param_6, uint param_7,uint param_8); /* 0x00497890 */
void __cdecl sputCostume_PuppetHook(int param_1,int param_2,uint param_3); /* 0x00497cb0 */
int * __cdecl KeyframeInstancer(int inst,int component,int create); /* 0x00497d10 */
int __cdecl KeyframeRequester(uint param_1,int param_2,int param_3,int param_4,uint param_5); /* 0x00497e10 */
uint __cdecl KeyframeAdjuster(int *param_1,uint param_2); /* 0x00498000 */
undefined4 KeyframeFreer(undefined4 param_1,undefined4 param_2,void *param_3); /* 0x004980b0 */
uint __cdecl KeyframeStopper(int *param_1); /* 0x004980e0 */

/* ===== smushcomponent.c ===== */
uint __cdecl SmushFreer(uint param_1,uint param_2,uint param_3); /* 0x00498140 */
void __cdecl SmushChanger(uint param_1,uint param_2,uint param_3,int param_4); /* 0x00498160 */
int __cdecl SmushRequester(uint param_1,int param_2,int param_3,int param_4,char *param_5); /* 0x00498190 */

/* ===== costumetag.c ===== */
uint __cdecl CostumeTag_Nop(void); /* 0x00498180 */

/* ===== spritecomponent.c ===== */
uint __cdecl SpriteRequester(uint param_1,int param_2,int param_3,float param_4,char *param_5); /* 0x00498280 */
void __cdecl SpriteChanger(uint param_1,int param_2,uint param_3,int param_4); /* 0x00498550 */
uint __cdecl SpriteFreer(uint param_1,uint param_2,int *param_3); /* 0x00498580 */
uint * __cdecl SpriteInstancer(int param_1,uint *param_2,int param_3); /* 0x004985c0 */
uint __cdecl SpriteAdjuster(uint *param_1,uint param_2); /* 0x004986e0 */

/* ===== chore.c ===== */
void __cdecl sputCostume_FadeKeysIn(void *cosInst,int chore,int ms); /* 0x00498990 */
void __cdecl sputCostume_FadeKeysOut(void *cosInst,int chore,int ms); /* 0x00498ad0 */

/* ===== config.c ===== */
void __cdecl Config_GetPath(char *name,char *buf,char *defaultSubdir); /* 0x00498bf0 */
void __cdecl Config_SetPath(char *name,char *value); /* 0x00498cf0 */

/* ===== sputlua.c ===== */
void __cdecl sputLua_GetActorCostumeL(void); /* 0x0049a1e0 */
void __cdecl sputLua_GetPointSectorL(void); /* 0x0049c3b0 */
void __cdecl sputLua_Update(void); /* 0x0049c8f0 */
uint __cdecl sputLua_Initialize(GrimServices *param_1,undefined4 *param_2); /* 0x0049c9f0 */
void __cdecl sputLua_FunctionNameL(void); /* 0x0049cbe0 */
void __cdecl sputLua_TypeOverride(void); /* 0x0049d140 */
void __cdecl sputLua_Terminate(void); /* 0x0049e500 */
void __cdecl sputLua_Shutdown(void); /* 0x0049e530 */
void __cdecl sputLua_StartMovieL(void); /* 0x0049e880 */
void __cdecl sputLua_RotateVectorL(void); /* 0x0049f0f0 */
void __cdecl sputLua_ImStartRecording(void); /* 0x004a0f20 */
void __cdecl sputLua_ImStartSound(void); /* 0x004a0f80 */
void __cdecl sputLua_ImStopSound(void); /* 0x004a1030 */
void __cdecl sputLua_ImGetParam(void); /* 0x004a1090 */
void __cdecl sputLua_ImSetParam(void); /* 0x004a1140 */
void __cdecl sputLua_ImFadeParam(void); /* 0x004a1260 */
void __cdecl sputLua_ImStartVoice(void); /* 0x004a1590 */
void __cdecl sputLua_ImSetSequence(void); /* 0x004a1680 */
void __cdecl sputLua_ImSetAttribute(void); /* 0x004a1710 */
void __cdecl sputLua_ImSetVoiceEffect(void); /* 0x004a17b0 */
void __cdecl sputLua_FadeInChore(void); /* 0x004a2b00 */
void __cdecl sputLua_SubmitSaveGameData(void); /* 0x004a35d0 */

/* ===== timer.c ===== */
uint __cdecl sputTime_GetGameTime(void); /* 0x004a3be0 */
uint __cdecl sputTime_GetFrameTime(void); /* 0x004a3bf0 */
float __cdecl sputTime_GetFrameTimeFlex(void); /* 0x004a3c00 */
void __cdecl sputTime_Advance(void); /* 0x004a3c10 */
void __cdecl sputTime_AdvanceManual(uint param_1); /* 0x004a3c80 */
void __cdecl Timer_Reset(void); /* 0x004a3ce0 */

/* ===== sputtime.c ===== */
uint __cdecl sputTime_Initialize(uint param_1,undefined4 *param_2); /* 0x004a3d00 */
void __cdecl sputTime_Terminate(void); /* 0x004a3d50 */
uint __cdecl sputTime_Startup(void); /* 0x004a3d70 */
void __cdecl sputTime_Shutdown(void); /* 0x004a3da0 */

/* ===== sound.c ===== */
void __cdecl sputRoom_RelocateSounds(void); /* 0x004a3fe0 */
void __cdecl sputRoom_SetSoundPosition (uint param_1,undefined **param_2,uint param_3,uint param_4,uint param_5,uint param_6); /* 0x004a40a0 */
void __cdecl PositionedSounds_DropFinished(void); /* 0x004a4dc0 */
undefined * __cdecl PositionedSound_Add(uint param_1,undefined **param_2,uint param_3,uint param_4,uint param_5, uint param_6); /* 0x004a4e20 */
uint __cdecl SetSoundPosition(int param_1); /* 0x004a4e80 */
uint __cdecl sou_engine_GetRate(void); /* 0x004d0c20 */
int __cdecl sou_engine_QueryTime(int voice); /* 0x004d0cf0 */

/* ===== sputroom.c ===== */
undefined * __cdecl sputRoom_Initialize(uint param_1,undefined **param_2); /* 0x004a48c0 */
void __cdecl sputRoom_Terminate(void); /* 0x004a5390 */
uint __cdecl sputRoom_Startup(void); /* 0x004a53b0 */
void __cdecl sputRoom_Shutdown(void); /* 0x004a5430 */
uint __cdecl sputRoom_ParseLights(void); /* 0x004a5600 */
uint __cdecl sputRoom_ParseSetups(void); /* 0x004a5890 */

/* ===== zbuffer.c ===== */
uint __cdecl sputRoom_LoadZBuffer(uint param_1); /* 0x004a4920 */
uint __cdecl ZBuffer_LoadFile(char *param_1); /* 0x004a4930 */
void __cdecl sputRoom_FreeZBuffer(uint param_1); /* 0x004a4980 */
void __cdecl ZBuffer_FreeData(void *param_1); /* 0x004a4990 */

/* ===== light.c ===== */
void * __cdecl sputRoom_GetLight(void *set,int index); /* 0x004a5cc0 */
int __cdecl sputRoom_FindLightByName(void *set,char *name); /* 0x004a5cf0 */

/* ===== objstate.c ===== */
void * __cdecl sputRoom_AddObjectState(int setupIdx,int type,char *bitmap,char *zbitmap,int visible); /* 0x004a5d50 */
void __cdecl sputRoom_RemoveObjectState(void *state); /* 0x004a5e50 */
undefined4 * __fastcall ObjectStateImage_Construct(undefined4 *param_1); /* 0x004aa070 */
void __fastcall ObjectStateImage_Clear(int param_1); /* 0x004aa0b0 */
void __thiscall ObjectStateImage_SetFile(void *this,char *name); /* 0x004aa100 */
void __thiscall ObjectStateImage_Load(void *this,int load); /* 0x004aa130 */
undefined4 __fastcall ObjectStateImage_VBuffer(int param_1); /* 0x004aa1f0 */
void __thiscall ObjectStateImage_SetClean(void *this,void *surface); /* 0x004aa290 */
void __thiscall ObjectStateImage_Draw(void *this,void *dst); /* 0x004aa310 */
int __fastcall ObjectStateImage_InSync(int param_1); /* 0x004aa3e0 */
void * __thiscall ObjectState_Construct(void *this,int type,char *bitmapName,char *zbufName,int setupIdx); /* 0x004aa410 */
void __fastcall ObjectState_Destruct(int param_1); /* 0x004aa4c0 */
void __fastcall ObjectState_LoadResources(int param_1); /* 0x004aa540 */
void __fastcall ObjectState_UnLoadResources(int param_1); /* 0x004aa560 */
void __thiscall ObjectState_Reset(void *this,void *bg,void *zbuf); /* 0x004aa580 */
void __thiscall ObjectState_Update(void *this,int type,void *dst,void *zdst); /* 0x004aa5c0 */
int __thiscall ObjectState_SetCopyMode(void *this,int a1); /* 0x004aa6b0 */
void * __thiscall ObjectState_MoveToBack(void *this,void *list); /* 0x004aa6c0 */
void * __thiscall ObjectState_MoveToFront(void *this,void *list); /* 0x004aa720 */

/* ===== setactorlist.c ===== */
void __cdecl SetActorList_Free(void *param_1); /* 0x004a6160 */

/* ===== textmodule.c ===== */
int __cdecl Text_SysInitialize(GrimServices *svc,void *iface); /* 0x004aa7b0 */
void __cdecl Text_SysTerminate(void); /* 0x004aa810 */
void __cdecl Text_SysStartup(void); /* 0x004aa820 */
void __cdecl Text_SysShutdown(void); /* 0x004aa860 */
uint __cdecl Text_SysSave(code *param_1); /* 0x004aa880 */
uint __cdecl Text_SysRestore(code *param_1); /* 0x004aa8d0 */

/* ===== glyph.c ===== */
void __cdecl Glyph_Blit16(int param_1,uint param_2,int *param_3); /* 0x004ab910 */
void __cdecl Glyph_Blit8(int param_1,int param_2,int *param_3); /* 0x004ab9d0 */
void __cdecl Glyph_Blit16Clipped(int param_1,uint param_2,int *param_3); /* 0x004abae0 */
void __cdecl Glyph_Blit8Clipped(int param_1,int param_2,int *param_3); /* 0x004abc80 */

/* ===== platmodule.c ===== */
int Graph_SysInitialize(GrimServices *svc,void *iface); /* 0x004abe90 */
void __cdecl Graph_SysTerminate(void); /* 0x004abef0 */
uint __cdecl Graph_SysStartup(void); /* 0x004abf00 */
void __cdecl Graph_SysShutdown(void); /* 0x004abf30 */

/* ===== crt.c ===== */
int __cdecl _stricmp(byte *param_1,byte *param_2); /* 0x004ac550 */
int __cdecl sprintf(char *buf,char *fmt,...); /* 0x004ac620 */
longlong __cdecl _ftol(float10 x); /* 0x004ac6f0 */
int __cdecl _vsnprintf(char *buf,uint n,char *fmt,void *args); /* 0x004ac720 */
int __cdecl atol(byte *param_1); /* 0x004ac790 */
undefined * __cdecl atoi(uint param_1); /* 0x004ac830 */
uint * __cdecl strncpy(uint *param_1,uint *param_2,uint param_3); /* 0x004ac840 */
uint __cdecl strtok(byte *param_1,byte *param_2); /* 0x004ac940 */
void __cdecl entry(void); /* 0x004aca30 */
void __cdecl _amsg_exit(uint param_1); /* 0x004acbe0 */
int __cdecl printf(char *fmt,...); /* 0x004acc40 */
uint __cdecl vsprintf(uint param_1,uint param_2,uint param_3); /* 0x004acca0 */
void __cdecl exit(uint param_1); /* 0x004acd40 */
void __cdecl _exit(uint param_1); /* 0x004acd60 */
void __cdecl doexit(int param_1,int param_2,int param_3); /* 0x004acd80 */
void __cdecl _lockexit(void); /* 0x004ace40 */
void __cdecl _unlockexit(void); /* 0x004ace50 */
void __cdecl _initterm(undefined4 *param_1,undefined4 *param_2); /* 0x004ace60 */
void * __cdecl _onexit(void *param_1); /* 0x004ace80 */
int __cdecl atexit(uint param_1); /* 0x004acf10 */
undefined * __cdecl malloc(uint param_1); /* 0x004acf70 */
int __cdecl _nh_malloc(uint param_1,int param_2); /* 0x004acf90 */
int __cdecl _heap_alloc(int param_1); /* 0x004acfe0 */
void __cdecl free(int param_1); /* 0x004ad040 */
undefined4 * __cdecl realloc(undefined4 *param_1,uint param_2); /* 0x004ad0b0 */
uint __cdecl _fsopen(uint param_1,uint param_2,uint param_3); /* 0x004ad2c0 */
undefined * __cdecl fopen(uint param_1,uint param_2); /* 0x004ad300 */
uint __cdecl fclose(int param_1); /* 0x004ad320 */
uint __cdecl _fclose_lk(int param_1); /* 0x004ad360 */
uint __cdecl fread(uint param_1,uint param_2,uint param_3,uint param_4); /* 0x004ad3d0 */
uint __cdecl _fread_lk(undefined4 *param_1,uint param_2,uint param_3,int *param_4); /* 0x004ad410 */
char * __cdecl fgets(char *param_1,int param_2,undefined4 *param_3); /* 0x004ad550 */
uint __cdecl fwrite(uint param_1,uint param_2,uint param_3,uint param_4); /* 0x004ad5e0 */
uint __cdecl _fwrite_lk(char *param_1,uint param_2,uint param_3,int *param_4); /* 0x004ad620 */
uint __cdecl ftell(uint param_1); /* 0x004ad770 */
uint __cdecl _ftell_lk(undefined4 *param_1); /* 0x004ad7a0 */
uint __cdecl fseek(uint param_1,uint param_2,uint param_3); /* 0x004ad950 */
int __cdecl _fseek_lk(int param_1,int param_2,int param_3); /* 0x004ad990 */
uint __cdecl vfprintf(uint param_1,uint param_2,uint param_3); /* 0x004ada30 */
void __cdecl qsort(void *base,uint num,uint width,code *compare); /* 0x004ada80 */
void __cdecl shortsort(uint param_1,uint param_2,int param_3,code *param_4); /* 0x004adc30 */
void __cdecl qsort_swap(undefined1 *param_1,undefined1 *param_2,int param_3); /* 0x004adc90 */
void * __cdecl bsearch(void *key,void *base,uint num,uint width,code *compare); /* 0x004adcc0 */
uint __cdecl strncmp(char *param_1,char *param_2,int param_3); /* 0x004add60 */
int __cdecl sscanf(char *str,char *fmt,...); /* 0x004adda0 */
uint * __cdecl strchr(uint *param_1,char param_2); /* 0x004ade30 */
int __cdecl _snprintf(char *buf,uint n,char *fmt,...); /* 0x004adf70 */
char * __cdecl _strupr(char *param_1); /* 0x004adfe0 */
char * __cdecl strrchr(char *param_1,char param_2); /* 0x004ae160 */
int __cdecl fprintf(void *fp,char *fmt,...); /* 0x004ae190 */
int __cdecl wcslen(short *param_1); /* 0x004ae260 */
int __cdecl tolower(int param_1); /* 0x004ae280 */
uint __cdecl _tolower_lk(uint param_1); /* 0x004ae310 */
float10 __cdecl _CIpow(float10 x,float10 y); /* 0x004ae540 */
float10 _pow(int param_1,uint param_2,int param_3,uint param_4); /* 0x004ae562 */
char * __cdecl _strlwr(char *param_1); /* 0x004ae760 */
int __cdecl toupper(int param_1); /* 0x004ae8e0 */
uint __cdecl _toupper_lk(uint param_1); /* 0x004ae970 */
uint __cdecl fflush(int param_1); /* 0x004aea70 */
int __cdecl _fflush_lk(int param_1); /* 0x004aeab0 */
uint __cdecl _flush(int *param_1); /* 0x004aeaf0 */
uint __cdecl _flushall(int param_1); /* 0x004aeb70 */
undefined4 * __cdecl memmove(undefined4 *param_1,undefined4 *param_2,uint param_3); /* 0x004aec30 */
int __cdecl _findfirst(int param_1,uint *param_2); /* 0x004aeff0 */
uint __cdecl _findnext(int param_1,uint *param_2); /* 0x004af120 */
uint __cdecl _findclose(int param_1); /* 0x004af240 */
uint __cdecl _FileTimeToTime_t(int *param_1); /* 0x004af270 */
void _CallSettingFrame(code *UNRECOVERED_JUMPTABLE); /* 0x004af300 */
undefined * __stdcall _UnwindNestedFrames(int a1,int a2); /* 0x004af350 */
uint __cdecl __CxxFrameHandler(uint param_1,uint param_2,uint param_3,uint param_4); /* 0x004af3b0 */
void __cdecl _global_unwind2(int param_1); /* 0x004af660 */
void __cdecl _local_unwind2(int param_1,int param_2); /* 0x004af6a2 */
uint __cdecl _unwind_handler(void); /* 0x004af70a */
undefined * __stdcall _NLG_Notify(int a1); /* 0x004af736 */
uint __cdecl isdigit(int param_1); /* 0x004af750 */
uint __cdecl isspace(int param_1); /* 0x004af780 */
void __cdecl _lock(int param_1); /* 0x004af7e0 */
void __cdecl _unlock(int param_1); /* 0x004af860 */
void __cdecl _lock_file(uint param_1); /* 0x004af880 */
void __cdecl _lock_file2(int param_1,int param_2); /* 0x004af8c0 */
void __cdecl _unlock_file(uint param_1); /* 0x004af8f0 */
void __cdecl _unlock_file2(int param_1,int param_2); /* 0x004af930 */
uint __cdecl _flsbuf(uint param_1,int *param_2); /* 0x004af960 */
uint __cdecl _output(uint param_1,char *param_2,uint *param_3); /* 0x004afa90 */
void __cdecl write_char(uint param_1,int *param_2,int *param_3); /* 0x004b0420 */
void __cdecl write_multi_char(uint param_1,int param_2,uint param_3,int *param_4); /* 0x004b0470 */
void __cdecl write_string(char *param_1,int param_2,uint param_3,int *param_4); /* 0x004b04b0 */
uint __cdecl get_int_arg(int *param_1); /* 0x004b04f0 */
ulonglong __cdecl get_short_arg(int *param_1); /* 0x004b0510 */
uint __cdecl get_int64_arg(undefined4 *param_1); /* 0x004b0530 */
uint __cdecl _isctype(int param_1,uint param_2); /* 0x004b0b50 */
undefined * __stdcall _allmul(int a1,int a2,int a3,int a4); /* 0x004b0bf0 */
void __cdecl _initptd(int param_1); /* 0x004b0c90 */
int * __cdecl _getptd(void); /* 0x004b0cb0 */
void __cdecl _FF_MSGBANNER(void); /* 0x004b1d20 */
void __cdecl _NMSG_WRITE(undefined *param_1); /* 0x004b1d60 */
uint __cdecl _stbuf(uint *param_1); /* 0x004b1f40 */
void __cdecl _ftbuf(int param_1,undefined4 *param_2); /* 0x004b2000 */
int __cdecl _msize(int param_1); /* 0x004b2120 */
uint __cdecl _callnewh(uint param_1); /* 0x004b2190 */
undefined ** __cdecl __sbh_alloc_new_region(void); /* 0x004b21b0 */
void __cdecl __sbh_release_region(undefined **param_1); /* 0x004b2320 */
void __cdecl __sbh_decommit_pages(int param_1); /* 0x004b2380 */
int __cdecl __sbh_find_block(undefined *param_1,undefined4 *param_2,uint *param_3); /* 0x004b2450 */
void __cdecl __sbh_free_block(int param_1,int param_2,byte *param_3); /* 0x004b24b0 */
int * __cdecl __sbh_alloc_block(uint param_1); /* 0x004b2510 */
int __cdecl __sbh_alloc_new_group(int *param_1,uint param_2,uint param_3); /* 0x004b2750 */
uint __cdecl __sbh_resize_block(int param_1,int *param_2,byte *param_3,uint param_4); /* 0x004b28d0 */
void __cdecl time(undefined4 *param_1); /* 0x004b29a0 */
undefined4 * __cdecl _openfile(uint param_1,char *param_2,uint param_3,undefined4 *param_4); /* 0x004b2a60 */
undefined4 * __cdecl _getstream(void); /* 0x004b2c30 */
uint __cdecl _close(uint param_1); /* 0x004b2d10 */
uint __cdecl _close_lk(uint param_1); /* 0x004b2d80 */
void __cdecl _freebuf(undefined4 *param_1); /* 0x004b2e10 */
uint __cdecl _filbuf(undefined4 *param_1); /* 0x004b2e50 */
uint __cdecl _read(uint param_1,uint param_2,uint param_3); /* 0x004b2f40 */
int __cdecl _read_lk(uint param_1,char *param_2,int param_3); /* 0x004b2fc0 */
uint __cdecl _write(uint param_1,uint param_2,uint param_3); /* 0x004b31f0 */
int __cdecl _write_lk(uint param_1,char *param_2,uint param_3); /* 0x004b3270 */
void __cdecl _dosmaperr(uint param_1); /* 0x004b3480 */
int __cdecl _errno(void); /* 0x004b3500 */
int __cdecl __doserrno(void); /* 0x004b3510 */
uint __cdecl _lseek(uint param_1,uint param_2,uint param_3); /* 0x004b3520 */
int __cdecl _lseek_lk(uint param_1,int param_2,int param_3); /* 0x004b35a0 */
uint __cdecl _input(uint param_1,byte *param_2,uint *param_3); /* 0x004b3620 */
uint __cdecl _hextodec(uint param_1); /* 0x004b4360 */
uint __cdecl _inc(undefined4 *param_1); /* 0x004b43a0 */
void __cdecl _un_inc(int param_1,uint param_2); /* 0x004b43d0 */
uint __cdecl _whiteout(int *param_1,uint param_2); /* 0x004b43f0 */
uint __cdecl __crtLCMapStringA(int param_1,uint param_2,int param_3,undefined *param_4,int param_5,int param_6, uint param_7,int param_8); /* 0x004b4560 */
int __cdecl _strncnt(char *param_1,int param_2); /* 0x004b4790 */
float10 __fastcall _pow_except1(undefined4 param_1,undefined4 param_2,undefined2 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6,uint param_7,uint param_8); /* 0x004b4ba0 */
float10 __fastcall _pow_except2(undefined4 param_1,int param_2,ushort param_3,undefined4 param_4,uint param_5, uint param_6); /* 0x004b4bb7 */
uint __cdecl _pow_special_cases(double param_1,double param_2,double *param_3); /* 0x004b4d90 */
uint __cdecl _is_integer_double(double param_1); /* 0x004b4fc0 */
uint __cdecl _commit(uint param_1); /* 0x004b5050 */
int __cdecl __loctotime_t(int param_1,int param_2,int param_3,uint param_4,int param_5,int param_6,int param_7); /* 0x004b50f0 */
uint __cdecl __InternalCxxFrameHandler (int *param_1,uint param_2,uint param_3,uint param_4,int *param_5,int param_6,uint param_7 ,uint param_8); /* 0x004b51e0 */
void __cdecl FindHandler(int *param_1,int param_2,uint param_3,uint param_4,int param_5,char param_6,uint param_7 ,uint param_8); /* 0x004b52b0 */
void __cdecl Eh_FindForeignHandler (uint param_1,uint param_2,uint param_3,uint param_4,uint param_5,int param_6,uint param_7 ,uint param_8); /* 0x004b5570 */
void __cdecl FrameUnwindToState(int param_1,uint param_2,int param_3,int param_4); /* 0x004b5650 */
void __cdecl CatchIt(int param_1,int param_2,uint param_3,uint param_4,uint param_5,int param_6,int param_7, undefined4 *param_8,uint param_9,int param_10); /* 0x004b5730 */
uint __cdecl CallCatchBlock(uint param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6, uint param_7); /* 0x004b57c0 */
void __cdecl Eh_CallCatchBlockInner(void); /* 0x004b58b8 */
void __cdecl BuildCatchObject(int param_1,int param_2,byte *param_3,byte *param_4); /* 0x004b5950 */
void __cdecl terminate(void); /* 0x004b5c60 */
void __cdecl _getbuf(int *param_1); /* 0x004b6ce0 */
uint __cdecl _isatty(uint param_1); /* 0x004b6d40 */
uint __cdecl wctomb(uint param_1,uint param_2); /* 0x004b6d70 */
int __cdecl _wctomb_lk(undefined1 *param_1,ushort param_2); /* 0x004b6de0 */
undefined * __stdcall _aulldiv(int a1,int a2,int a3,int a4); /* 0x004b6e60 */
undefined * __stdcall _aullrem(int a1,int a2,int a3,int a4); /* 0x004b6ed0 */
uint __cdecl _ld12tocvt(ushort *param_1,uint *param_2,int *param_3); /* 0x004b7370 */
undefined * __cdecl _ld12tod(uint param_1,uint param_2); /* 0x004b7540 */
uint __cdecl __crtGetStringTypeA(int param_1,int param_2,int param_3,int param_4,uint param_5,uint param_6, int param_7); /* 0x004b7990 */
undefined4 * __cdecl calloc(int param_1,int param_2); /* 0x004b7ad0 */
uint __cdecl __crtMessageBoxA(uint param_1,uint param_2,uint param_3); /* 0x004b7b80 */
undefined * __cdecl mktime(uint param_1); /* 0x004b7cb0 */
int __cdecl _make_time_t(int *param_1,int param_2); /* 0x004b7cc0 */
void __cdecl __tzset(void); /* 0x004b7f00 */
void __cdecl _tzset_lk(void); /* 0x004b7f40 */
uint __cdecl _isindst(uint param_1); /* 0x004b8220 */
int __cdecl _isindst_lk(int *param_1); /* 0x004b8250 */
void __cdecl _cvtdate(int param_1,int param_2,uint param_3,int param_4,int param_5,int param_6,int param_7, int param_8,int param_9,int param_10,int param_11); /* 0x004b84c0 */
uint __cdecl _sopen(int param_1,uint param_2,uint param_3,uint param_4); /* 0x004b8660 */
uint __cdecl _alloc_osfhnd(void); /* 0x004b8a00 */
uint __cdecl _set_osfhnd(uint param_1,int param_2); /* 0x004b8b70 */
uint __cdecl _free_osfhnd(uint param_1); /* 0x004b8c20 */
int __cdecl _get_osfhandle(uint param_1); /* 0x004b8cc0 */
void __cdecl _lock_fhandle(uint param_1); /* 0x004b8d10 */
void __cdecl _unlock_fhandle(uint param_1); /* 0x004b8d80 */
uint __cdecl mbtowc(uint param_1,uint param_2,uint param_3); /* 0x004b8db0 */
uint __cdecl _mbtowc_lk(ushort *param_1,byte *param_2,uint param_3); /* 0x004b8e30 */
uint __cdecl ungetc(uint param_1,uint param_2); /* 0x004b8f50 */
uint __cdecl _ungetc_lk(uint param_1,int *param_2); /* 0x004b8f80 */
uint __cdecl _filwbuf(undefined4 *param_1); /* 0x004b9010 */
void __cdecl _except1(int param_1,int *param_2,ushort *param_3); /* 0x004b9ea0 */
int __cdecl _ValidateRead(int param_1,int param_2); /* 0x004ba2c0 */
int __cdecl _ValidateWrite(int param_1,int param_2); /* 0x004ba2e0 */
int __cdecl _ValidateExecute(int param_1); /* 0x004ba300 */
void __cdecl abort(void); /* 0x004ba320 */
uint __cdecl raise(int param_1); /* 0x004ba600 */
uint __cdecl siglookup(int param_1,uint param_2); /* 0x004ba810 */
uint __cdecl __addl(uint param_1,uint param_2,uint *param_3); /* 0x004ba850 */
void __cdecl __add_12(undefined4 *param_1,undefined4 *param_2); /* 0x004ba880 */
void __cdecl __shl_12(uint *param_1); /* 0x004ba8f0 */
void __cdecl __shr_12(uint *param_1); /* 0x004ba920 */
void __cdecl __mtold12(char *param_1,int param_2,uint *param_3); /* 0x004ba950 */
uint __cdecl __strgtold12(ushort *param_1,int *param_2,byte *param_3,uint param_4,int param_5,int param_6, int param_7); /* 0x004baa50 */
int * __cdecl gmtime(int *param_1); /* 0x004bb570 */
int * __cdecl localtime(int *param_1); /* 0x004bb6e0 */
uint __cdecl wcstombs(uint param_1,uint param_2,uint param_3); /* 0x004bb8d0 */
uint __cdecl _wcstombs_lk(int param_1,ushort *param_2,uint param_3); /* 0x004bb950 */
int __cdecl wcsncnt(short *param_1,int param_2); /* 0x004bbb40 */
int __cdecl getenv(char *param_1); /* 0x004bbb80 */
int __cdecl _chsize(void); /* 0x004bbc10 */
void __cdecl _raise_exc(uint *param_1,uint *param_2,byte param_3,uint param_4,uint *param_5,uint *param_6); /* 0x004bbd60 */
int __cdecl _handle_exc(uint param_1,double *param_2,uint param_3); /* 0x004bc0a0 */
void __cdecl __ld12mul(int *param_1,int *param_2); /* 0x004bc730 */
void __cdecl __multtenpow12(undefined2 *param_1,uint param_2,int param_3); /* 0x004bc9f0 */
int __cdecl _strnicoll(uint param_1,uint param_2,int param_3); /* 0x004bca80 */
uint __cdecl __crtsetenv_from_wenviron(void); /* 0x004bcac0 */
uint __cdecl __crtCompareStringA(int param_1,int param_2,byte *param_3,undefined *param_4,byte *param_5, int param_6,uint param_7); /* 0x004bcbb0 */
uint __cdecl __crtsetenv(char *param_1,int param_2); /* 0x004bce80 */
int __cdecl findenv(uint param_1,int param_2); /* 0x004bd090 */
undefined4 * __cdecl copy_environ(int *param_1); /* 0x004bd110 */
byte * __cdecl _mbschr(byte *param_1,uint param_2); /* 0x004bd180 */
char * __cdecl _strdup(char *param_1); /* 0x004bd250 */
float __cdecl atof(byte *param_1); /* 0x004d5430 */
int __cdecl _fdopen(uint param_1,char *param_2); /* 0x004d54e0 */
void __cdecl rewind(int param_1); /* 0x004d5670 */
void longjmp(int param_1); /* 0x004d59d0 */
uint __cdecl _setjmp3(undefined4 *param_1,int param_2,int param_3,uint param_4); /* 0x004d5a4c */
undefined * __cdecl _fltin(uint *param_1,int param_2); /* 0x004d5ad0 */

/* ===== crt_unnamed.c ===== */
void __cdecl FUN_004ac690(void); /* 0x004ac690 */
void __cdecl FUN_004ac6b0(void); /* 0x004ac6b0 */
void __cdecl FUN_004acb8d(void); /* 0x004acb8d */
void __cdecl FUN_004acba2(void); /* 0x004acba2 */
void __cdecl FUN_004acc10(uint param_1); /* 0x004acc10 */
void __cdecl FUN_004acd10(void); /* 0x004acd10 */
void __cdecl FUN_004acf30(void); /* 0x004acf30 */
void __cdecl FUN_004ad2b0(void); /* 0x004ad2b0 */
int FUN_004addf0(void); /* 0x004addf0 */
short * __cdecl FUN_004adef0(short *param_1,int param_2,uint param_3); /* 0x004adef0 */
uint * __cdecl FUN_004ae410(uint *param_1,uint *param_2,uint param_3); /* 0x004ae410 */
float __cdecl FUN_004ae735(void); /* 0x004ae735 */
void __cdecl FUN_004aeb60(void); /* 0x004aeb60 */
void FUN_004af340(undefined4 param_1,code *UNRECOVERED_JUMPTABLE); /* 0x004af340 */
undefined * __cdecl FUN_004af3f0(uint param_1,uint param_2,int param_3,int param_4,int param_5); /* 0x004af3f0 */
void __cdecl FUN_004af450(uint param_1,int param_2,uint param_3); /* 0x004af450 */
uint __cdecl FUN_004af480(undefined4 *param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6, uint param_7); /* 0x004af480 */
uint __cdecl FUN_004af550(int param_1,int param_2,uint param_3); /* 0x004af550 */
int __cdecl FUN_004af5e0(int param_1,int param_2,int param_3,uint *param_4,uint *param_5); /* 0x004af5e0 */
void __fastcall FUN_004af72d(uint param_1); /* 0x004af72d */
void __cdecl FUN_004af7b0(void); /* 0x004af7b0 */
void __cdecl FUN_004b0550(void); /* 0x004b0550 */
uint __cdecl FUN_004b0570(void); /* 0x004b0570 */
undefined * FUN_004b05c0(void); /* 0x004b05c0 */
void __cdecl FUN_004b05f0(char *param_1); /* 0x004b05f0 */
void __cdecl FUN_004b0650(char *param_1); /* 0x004b0650 */
uint __cdecl FUN_004b06c0(double *param_1); /* 0x004b06c0 */
void __cdecl FUN_004b06e0(int param_1,undefined4 *param_2,uint param_3); /* 0x004b06e0 */
int __cdecl FUN_004b0740(undefined4 *param_1,int param_2,int param_3,uint param_4); /* 0x004b0740 */
undefined1 * __cdecl FUN_004b07c0(undefined1 *param_1,int param_2,int param_3,int *param_4,char param_5); /* 0x004b07c0 */
int __cdecl FUN_004b08c0(undefined4 *param_1,int param_2,int param_3); /* 0x004b08c0 */
undefined1 * __cdecl FUN_004b0930(undefined1 *param_1,uint param_2,int *param_3,char param_4); /* 0x004b0930 */
void __cdecl FUN_004b09f0(undefined4 *param_1,int param_2,int param_3,uint param_4); /* 0x004b09f0 */
void __cdecl FUN_004b0ab0(uint param_1,uint param_2,int param_3,uint param_4,uint param_5); /* 0x004b0ab0 */
void __cdecl FUN_004b0b20(char *param_1,int param_2); /* 0x004b0b20 */
uint __cdecl FUN_004b0c30(void); /* 0x004b0c30 */
uint __cdecl FUN_004b0d30(uint param_1,uint param_2); /* 0x004b0d30 */
int * __cdecl FUN_004b0f40(int param_1,int *param_2); /* 0x004b0f40 */
undefined * __cdecl FUN_004b0f80(uint param_1); /* 0x004b0f80 */
uint __cdecl FUN_004b0fa0(uint param_1,uint param_2,byte param_3); /* 0x004b0fa0 */
void __cdecl FUN_004b0fe0(void); /* 0x004b0fe0 */
void __cdecl FUN_004b10d0(void); /* 0x004b10d0 */
void __cdecl FUN_004b1170(byte *param_1,undefined4 *param_2,byte *param_3,int *param_4,int *param_5); /* 0x004b1170 */
char * __cdecl FUN_004b1380(void); /* 0x004b1380 */
uint __cdecl FUN_004b14e0(uint param_1); /* 0x004b14e0 */
uint __cdecl FUN_004b1710(uint param_1); /* 0x004b1710 */
uint __cdecl FUN_004b1760(uint param_1); /* 0x004b1760 */
void __cdecl FUN_004b17c0(void); /* 0x004b17c0 */
void __cdecl FUN_004b1800(void); /* 0x004b1800 */
void __cdecl FUN_004b19e0(void); /* 0x004b19e0 */
void __cdecl FUN_004b19f0(void); /* 0x004b19f0 */
uint __cdecl FUN_004b1c00(void); /* 0x004b1c00 */
uint __cdecl FUN_004b1c48(int param_1,int param_2,uint param_3); /* 0x004b1c48 */
void __cdecl FUN_004b2040(void); /* 0x004b2040 */
void __cdecl FUN_004b2100(void); /* 0x004b2100 */
uint __thiscall FUN_004b4440(undefined4 param_1,undefined4 *param_2); /* 0x004b4440 */
float10 FUN_004b4ad4(void); /* 0x004b4ad4 */
float10 FUN_004b4b0d(void); /* 0x004b4b0d */
float10 FUN_004b4b0f(void); /* 0x004b4b0f */
unkbyte10 FUN_004b4c00(void); /* 0x004b4c00 */
undefined * FUN_004b4c15(void); /* 0x004b4c15 */
uint __fastcall FUN_004b4c45(undefined4 param_1,int param_2); /* 0x004b4c45 */
undefined * FUN_004b4c9e(void); /* 0x004b4c9e */
undefined * __fastcall FUN_004b4ce9(uint param_1,int param_2); /* 0x004b4ce9 */
void __cdecl FUN_004b56c6(void); /* 0x004b56c6 */
void __cdecl FUN_004b56d3(void); /* 0x004b56d3 */
uint __cdecl FUN_004b5710(undefined4 *param_1); /* 0x004b5710 */
uint __cdecl FUN_004b5884(void); /* 0x004b5884 */
void FUN_004b58af(void); /* 0x004b58af */
void __cdecl FUN_004b5b60(int param_1); /* 0x004b5b60 */
int __cdecl FUN_004b5baa(void); /* 0x004b5baa */
void __cdecl FUN_004b5bb5(void); /* 0x004b5bb5 */
int __cdecl FUN_004b5be0(int param_1,int *param_2); /* 0x004b5be0 */
undefined * __stdcall FUN_004b5c10(int a1,int a2,int a3); /* 0x004b5c10 */
uint __cdecl FUN_004b5caa(void); /* 0x004b5caa */
void __cdecl FUN_004b5cb0(void); /* 0x004b5cb0 */
void __cdecl FUN_004b5cd7(void); /* 0x004b5cd7 */
void __cdecl FUN_004b5cf0(void); /* 0x004b5cf0 */
void __cdecl FUN_004b5d5e(void); /* 0x004b5d5e */
uint __cdecl FUN_004b5d80(void); /* 0x004b5d80 */
uint __cdecl FUN_004b5e30(int param_1); /* 0x004b5e30 */
void __cdecl FUN_004b61b0(undefined4 *param_1); /* 0x004b61b0 */
uint __cdecl FUN_004b63f0(char *param_1,int param_2); /* 0x004b63f0 */
uint __cdecl FUN_004b64f0(void); /* 0x004b64f0 */
void __cdecl FUN_004b66f0(char *param_1); /* 0x004b66f0 */
uint __cdecl FUN_004b6730(void); /* 0x004b6730 */
uint __cdecl FUN_004b6820(int param_1); /* 0x004b6820 */
void __cdecl FUN_004b6970(int param_1); /* 0x004b6970 */
uint __cdecl FUN_004b69e0(void); /* 0x004b69e0 */
uint __cdecl FUN_004b6f50(uint param_1,uint param_2); /* 0x004b6f50 */
void __cdecl FUN_004b6f90(uint param_1,uint param_2); /* 0x004b6f90 */
uint __cdecl FUN_004b6fb0(uint param_1); /* 0x004b6fb0 */
void __cdecl FUN_004b7050(void); /* 0x004b7050 */
uint __cdecl FUN_004b70e0(int param_1,int param_2); /* 0x004b70e0 */
undefined * __cdecl FUN_004b7150(int param_1,int param_2); /* 0x004b7150 */
undefined * __cdecl FUN_004b71c0(int param_1,int param_2); /* 0x004b71c0 */
void __cdecl FUN_004b7260(int param_1,undefined4 *param_2); /* 0x004b7260 */
void __cdecl FUN_004b7280(undefined4 *param_1); /* 0x004b7280 */
uint __cdecl FUN_004b7290(int *param_1); /* 0x004b7290 */
void __cdecl FUN_004b72b0(uint *param_1,int param_2); /* 0x004b72b0 */
void __cdecl FUN_004b7560(uint param_1,uint param_2); /* 0x004b7560 */
void __cdecl FUN_004b7580(uint param_1,uint param_2); /* 0x004b7580 */
void __cdecl FUN_004b75c0(uint param_1,uint param_2); /* 0x004b75c0 */
void __cdecl FUN_004b7600(char *param_1,int param_2,int param_3); /* 0x004b7600 */
int * __cdecl FUN_004b76a0(uint param_1,uint param_2,int *param_3,char *param_4); /* 0x004b76a0 */
void __cdecl FUN_004b7730(uint *param_1,uint *param_2); /* 0x004b7730 */
void __cdecl FUN_004b77f0(void); /* 0x004b77f0 */
uint __cdecl FUN_004b7800(int param_1,int param_2,int param_3,int param_4,uint param_5,uint param_6); /* 0x004b7800 */
int __cdecl FUN_004b7c10(void); /* 0x004b7c10 */
int __fastcall FUN_004b8f30(byte param_1,int param_2); /* 0x004b8f30 */
undefined4 __cdecl FUN_004b9916(undefined4 param_1,uint param_2,ushort param_3,uint param_4,uint param_5,uint param_6, uint param_7,uint param_8,ushort param_9); /* 0x004b9916 */
float10 FUN_004b9b1c(void); /* 0x004b9b1c */
float __cdecl FUN_004b9fc0(undefined4 param_1,undefined4 param_2,short param_3); /* 0x004b9fc0 */
uint __cdecl FUN_004ba000(int param_1,uint param_2); /* 0x004ba000 */
float __cdecl FUN_004ba060(uint param_1,uint param_2,int *param_3); /* 0x004ba060 */
float __cdecl FUN_004ba170(double param_1); /* 0x004ba170 */
int __cdecl FUN_004ba190(int param_1,uint param_2); /* 0x004ba190 */
undefined * __stdcall FUN_004ba230(int a1); /* 0x004ba230 */
void __cdecl FUN_004ba290(void); /* 0x004ba290 */
void __cdecl FUN_004ba2b0(void); /* 0x004ba2b0 */
uint __cdecl FUN_004ba340(int param_1,uint param_2,uint param_3,char *param_4); /* 0x004ba340 */
uint __cdecl FUN_004bb1e0(int param_1,uint param_2,uint param_3,int param_4,byte param_5,short *param_6); /* 0x004bb1e0 */
void __cdecl FUN_004bc3d0(int param_1); /* 0x004bc3d0 */
int __cdecl FUN_004bc400(void); /* 0x004bc400 */
int __cdecl FUN_004bc410(void); /* 0x004bc410 */
int __cdecl FUN_004bc430(void); /* 0x004bc430 */
void __cdecl FUN_004bc460(void); /* 0x004bc460 */
uint __cdecl FUN_004bc4c0(uint param_1,uint param_2,uint param_3,uint param_4); /* 0x004bc4c0 */
uint __cdecl FUN_004bc5f0(uint param_1,uint param_2,uint param_3,uint param_4); /* 0x004bc5f0 */
int __cdecl FUN_004bcb40(uint param_1,int param_2); /* 0x004bcb40 */
undefined4 __cdecl SmushPlay_FakeBlit(uint param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6, uint param_7); /* 0x004bdad0 */
uint __cdecl grimmem_memory_module(int *param_1,uint param_2); /* 0x004bdf70 */
void __cdecl grimmem_module_terminate(void); /* 0x004bdfb0 */
uint __cdecl mem_Alloc(uint param_1,uint param_2,uint param_3); /* 0x004bdfe0 */
uint __cdecl mem_Free(uint param_1); /* 0x004be000 */
uint __cdecl mem_Realloc(uint param_1,uint param_2,uint param_3,uint param_4); /* 0x004be020 */
uint __cdecl grimio_stdio_module(int *param_1,uint param_2); /* 0x004be050 */
void __cdecl grimio_terminate(void); /* 0x004be090 */
uint __cdecl grimio_Open(uint param_1,uint param_2); /* 0x004be0c0 */
uint __cdecl grimio_Close(uint param_1); /* 0x004be0e0 */
uint __cdecl grimio_Read(uint param_1,uint param_2,uint param_3); /* 0x004be100 */
uint __cdecl grimio_Write(uint param_1,uint param_2,uint param_3); /* 0x004be120 */
uint __cdecl grimio_Tell(uint param_1); /* 0x004be140 */
uint __cdecl grimio_Seek(uint param_1,uint param_2,uint param_3); /* 0x004be160 */
undefined * __stdcall FUN_004bf950(int a1,int a2,int a3,int a4); /* 0x004bf950 */
uint __cdecl BatchUnsubscribe(int *param_1); /* 0x004c1900 */
uint __cdecl anm_animplay_module(int *param_1,uint param_2); /* 0x004c1f40 */
void __cdecl AnimPlay_module_terminate(void); /* 0x004c1fb0 */
uint __cdecl AnimPlay_module_startup(void); /* 0x004c1ff0 */
void __cdecl AnimPlay_module_shutdown(void); /* 0x004c2150 */
int __cdecl anm_EasyPlay(char *param_1,int param_2,uint param_3,uint param_4,uint param_5,uint param_6, uint param_7,uint param_8,uint param_9,code *param_10,int param_11,int param_12, int param_13); /* 0x004c21e0 */
int __cdecl anm_GetTime(int param_1); /* 0x004c2590 */
int __cdecl FUN_004c25c0(void *param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7, int param_8,int param_9,int param_10); /* 0x004c25c0 */
void __cdecl AnimPlay_anm_Display (uint param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6, uint param_7,uint param_8,uint param_9); /* 0x004c2650 */
void __cdecl anm_SetRate(undefined4 *param_1,int param_2); /* 0x004c2720 */
void __cdecl anm_SyncUp(undefined4 *param_1); /* 0x004c2760 */
uint __cdecl anm_RenderQuery(int param_1); /* 0x004c2780 */
void __cdecl frame_Timer(uint param_1,int param_2); /* 0x004c2a70 */
void __cdecl sync_Timer(uint param_1,int param_2); /* 0x004c2a80 */
char * __cdecl AnimPlay_anm_DebugInfo(int param_1); /* 0x004c2b00 */
void __cdecl AnimPlay_anm_DebugSetState(uint param_1); /* 0x004c2b30 */
uint __cdecl AnimPlay_anm_DebugGetState(void); /* 0x004c2b40 */
uint __cdecl anm_animframe_module(int *param_1,uint param_2); /* 0x004c2b50 */
void __cdecl AnimFrame_module_terminate(void); /* 0x004c2ba0 */
int __cdecl AnimFrame_module_startup(void); /* 0x004c2be0 */
void __cdecl AnimFrame_module_shutdown(void); /* 0x004c2dc0 */
void __cdecl anm_Reset(void); /* 0x004c2eb0 */
uint __cdecl anm_DecodeHeader(undefined1 *param_1,int param_2); /* 0x004c2ee0 */
uint __cdecl anm_DecodeBody(uint param_1,uint param_2,uint param_3,uint param_4,uint *param_5,uint *param_6, uint *param_7,uint param_8,uint param_9,uint param_10,byte *param_11,int param_12); /* 0x004c2fa0 */
void __cdecl anm_PreloadPut(short *param_1,int param_2); /* 0x004c34d0 */
int __cdecl anm_PreloadGet(int param_1); /* 0x004c3560 */
void __cdecl AnimFrame_anm_Display (int param_1,uint param_2,uint param_3,uint param_4,uint param_5,byte param_6,byte param_7 ,uint param_8); /* 0x004c35c0 */
char * __cdecl AnimFrame_anm_DebugInfo(int param_1); /* 0x004c3660 */
void __cdecl AnimFrame_anm_DebugSetState(uint param_1); /* 0x004c3690 */
uint __cdecl AnimFrame_anm_DebugGetState(void); /* 0x004c36a0 */
uint __cdecl anm_animator_Render(int param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6, uint param_7,uint param_8,uint param_9,uint param_10,uint param_11); /* 0x004c36f0 */
void __cdecl FUN_004c3b30(int param_1,uint param_2); /* 0x004c3b30 */
uint __cdecl FUN_004c3bb0(int param_1); /* 0x004c3bb0 */
uint __cdecl FUN_004c3c00(int param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6, uint param_7,uint param_8,uint param_9,uint param_10,uint param_11); /* 0x004c3c00 */
void __cdecl FUN_004c3c90(int param_1,int param_2,void *param_3,uint *param_4); /* 0x004c3c90 */
uint __cdecl anm_animator_Query(int param_1); /* 0x004c3d00 */
void __cdecl anm_animator_Quit(int param_1); /* 0x004c3d10 */
void __cdecl FUN_004c3d90(int param_1,uint param_2,uint param_3); /* 0x004c3d90 */
uint __cdecl anm_animator_Pause(int param_1,int param_2); /* 0x004c3db0 */
uint __cdecl FUN_004c4650(int param_1,uint param_2); /* 0x004c4650 */
undefined * __cdecl FUN_004c4a00(int param_1,int *param_2); /* 0x004c4a00 */
uint __cdecl fle_streamer_module(int *param_1,uint param_2); /* 0x004c4b20 */
void __cdecl Streamer_module_terminate(void); /* 0x004c4b60 */
uint __cdecl Streamer_module_startup(void); /* 0x004c4b90 */
void __cdecl Streamer_module_shutdown(void); /* 0x004c4c10 */
int __cdecl fle_StreamerAlloc(undefined4 *param_1,uint param_2,int param_3); /* 0x004c4c50 */
void __cdecl fle_StreamerFree(int *param_1); /* 0x004c4d20 */
void __cdecl fle_StreamerReset(undefined4 *param_1); /* 0x004c4d90 */
void __cdecl fle_StreamerAcquire(uint *param_1,uint param_2); /* 0x004c4dd0 */
uint __cdecl fle_StreamerStart(int param_1,char *param_2,uint param_3); /* 0x004c4ee0 */
uint __cdecl FUN_004c4f60(int param_1); /* 0x004c4f60 */
uint __cdecl fle_StreamerCheck(int param_1); /* 0x004c5080 */
int __cdecl fle_StreamerDispense(undefined4 *param_1,int param_2); /* 0x004c50a0 */
uint __cdecl FUN_004c51b0(int param_1); /* 0x004c51b0 */
uint __cdecl FUN_004c51e0(int param_1,int param_2); /* 0x004c51e0 */
int __cdecl fle_StreamerQuerySize(int param_1); /* 0x004c5220 */
uint __cdecl fle_directory_module(int *param_1,uint param_2); /* 0x004c5280 */
void __cdecl Directory_module_terminate(void); /* 0x004c52c0 */
uint __cdecl Directory_module_startup(void); /* 0x004c52f0 */
uint __cdecl Directory_module_shutdown(void); /* 0x004c5330 */
void __cdecl FUN_004c5350(uint param_1,undefined4 *param_2); /* 0x004c5350 */
void __cdecl FUN_004c5370(undefined4 *param_1); /* 0x004c5370 */
int __cdecl fle_Exists(int param_1); /* 0x004c5380 */
void __cdecl fle_Rename(uint param_1,uint param_2); /* 0x004c53b0 */
void __cdecl fle_Remove(uint param_1); /* 0x004c53d0 */
int __cdecl fle_DirectoryLoad(uint param_1,int param_2,int param_3,uint param_4,byte param_5); /* 0x004c53e0 */
int __cdecl fle_DirectoryGetCWD(char *param_1,int param_2); /* 0x004c54f0 */
uint __cdecl fle_DirectoryGetParent(int param_1,char *param_2); /* 0x004c5570 */
uint __cdecl fle_DirectoryGetPath(char *param_1,char *param_2,char *param_3,uint param_4); /* 0x004c55d0 */
int __cdecl fle_VolumeLoadList(int param_1,int param_2); /* 0x004c5720 */
uint __cdecl fle_zfilio_module(int *param_1,uint param_2); /* 0x004c5790 */
void __cdecl Zfile_module_terminate(void); /* 0x004c5840 */
uint __cdecl Zfile_module_startup(void); /* 0x004c5870 */
void __cdecl Zfile_module_shutdown(void); /* 0x004c5910 */
int * Zfile_fle_Open(char *param_1,char *param_2); /* 0x004c5950 */
int __cdecl Zfile_fle_Read(int *param_1,uint param_2,int param_3); /* 0x004c5b00 */
uint __cdecl Zfile_fle_Write(int *param_1,uint param_2,int param_3); /* 0x004c5bc0 */
int __cdecl Zfile_fle_Tell(int *param_1); /* 0x004c5c20 */
void __cdecl Zfile_fle_Seek(int *param_1,int param_2,int param_3); /* 0x004c5c50 */
void __cdecl Zfile_fle_Flush(int *param_1); /* 0x004c5cb0 */
uint __cdecl fle_stdfile_module(int *param_1,uint param_2); /* 0x004c5ce0 */
void __cdecl StdFile_module_terminate(void); /* 0x004c5d20 */
uint __cdecl StdFile_module_startup(void); /* 0x004c5d50 */
uint __cdecl StdFile_module_shutdown(void); /* 0x004c5d90 */
uint __cdecl StdFile_fle_Open(uint param_1,uint param_2); /* 0x004c5db0 */
uint __cdecl StdFile_fle_Close(uint param_1); /* 0x004c5dd0 */
uint __cdecl StdFile_fle_Read(uint param_1,uint param_2,uint param_3); /* 0x004c5df0 */
uint __cdecl StdFile_fle_Write(uint param_1,uint param_2,uint param_3); /* 0x004c5e10 */
uint __cdecl StdFile_fle_Seek(uint param_1,uint param_2,uint param_3); /* 0x004c5e50 */
uint __cdecl StdFile_fle_Flush(uint param_1); /* 0x004c5e70 */
int __cdecl fle_GetS(uint param_1,int param_2,int param_3); /* 0x004c5ee0 */
void __cdecl fle_PrintF(uint fh,char *fmt,...); /* 0x004c5f80 */
uint __cdecl fle_GetC(uint param_1); /* 0x004c5fe0 */
uint __cdecl fle_PutC(uint param_1,uint param_2); /* 0x004c6010 */
uint __cdecl FUN_004c6db0(int *param_1,int param_2); /* 0x004c6db0 */
void __cdecl FUN_004c6f10(int *param_1); /* 0x004c6f10 */
uint __cdecl FUN_004c7040(int *param_1,undefined4 *param_2,uint param_3); /* 0x004c7040 */
uint __cdecl FUN_004c70c0(int *param_1,int param_2); /* 0x004c70c0 */
char * __cdecl FUN_004c73f0(int param_1,uint param_2); /* 0x004c73f0 */
uint __cdecl FUN_004c7570(int *param_1,int param_2); /* 0x004c7570 */
void __cdecl FUN_004c7b10(uint param_1,uint param_2); /* 0x004c7b10 */
uint __cdecl FUN_004c8990(uint param_1,byte *param_2,uint param_3); /* 0x004c8990 */
void __cdecl FUN_004c8ba0(int param_1,uint param_2,uint param_3,int param_4); /* 0x004c8ba0 */
void __cdecl FUN_004c8e90(int param_1,int param_2,int param_3,int param_4); /* 0x004c8e90 */
void __cdecl FUN_004c9090(short *param_1,undefined4 *param_2); /* 0x004c9090 */
void __cdecl FUN_004c92d0(int param_1,int param_2,int param_3); /* 0x004c92d0 */
void __cdecl FUN_004c9390(int *param_1,int *param_2); /* 0x004c9390 */
void __cdecl FUN_004c95c0(undefined2 *param_1,int param_2,short *param_3); /* 0x004c95c0 */
void __cdecl FUN_004c9640(int param_1); /* 0x004c9640 */
void __cdecl FUN_004c96c0(int param_1,int param_2,int param_3); /* 0x004c96c0 */
void __cdecl FUN_004c97b0(int param_1,int param_2,int param_3,int param_4); /* 0x004c97b0 */
void __cdecl FUN_004c9a20(int param_1,int param_2,ushort *param_3); /* 0x004c9a20 */
void __cdecl FUN_004c9fa0(int param_1,int param_2,int param_3); /* 0x004c9fa0 */
void __cdecl FUN_004ca3f0(int param_1); /* 0x004ca3f0 */
uint __cdecl FUN_004ca460(uint param_1,int param_2); /* 0x004ca460 */
uint __cdecl fob_flobdec_wave_module(int *param_1,uint param_2); /* 0x004cba30 */
void __cdecl DWave_module_terminate(void); /* 0x004cba70 */
int __cdecl DWave_module_startup(void); /* 0x004cbaa0 */
void __cdecl DWave_module_shutdown(void); /* 0x004cbb30 */
char * __cdecl DWave_flobdec_Info(int param_1); /* 0x004cbb80 */
uint __cdecl DWave_flobdec_GetID(void); /* 0x004cbbb0 */
uint __cdecl DWave_flobdec_GetType(void); /* 0x004cbbc0 */
void __cdecl DWave_flobdec_Reset(void); /* 0x004cbbd0 */
uint __cdecl DWave_flobdec_DecodeHeader(int param_1); /* 0x004cbbe0 */
undefined4 __cdecl DWave_flobdec_DecodeBody (uint param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint *param_6); /* 0x004cbc00 */
uint __cdecl FUN_004cbf40(void); /* 0x004cbf40 */
void VbrAdpcm_Uncompress(int param_1,undefined1 *param_2,uint param_3,uint param_4); /* 0x004cbf50 */
int __cdecl FUN_004cd3f0(uint param_1,uint param_2); /* 0x004cd3f0 */
uint __cdecl sys_GetCount(void); /* 0x004ce010 */
void __cdecl sys_ExtSync(int param_1); /* 0x004ce020 */
uint __cdecl bmp_bitmap_module(int *param_1,uint param_2); /* 0x004ce2e0 */
void __cdecl Video_module_terminate(void); /* 0x004ce320 */
uint __cdecl Video_module_startup(void); /* 0x004ce350 */
void __cdecl Video_module_shutdown(void); /* 0x004ce3b0 */
uint __cdecl bmp_bitmap_AllocRaw(int *param_1,int param_2,int param_3,int param_4,int param_5,uint param_6, undefined4 *param_7); /* 0x004ce840 */
void __cdecl bmp_bitmap_Free(int *param_1); /* 0x004ce980 */
void __cdecl gra_SetBitmap(undefined4 *param_1,uint param_2); /* 0x004ce9b0 */
uint __cdecl gra_ConvertMakeLookup(int param_1,void *param_2,void *param_3,byte *param_4); /* 0x004ced70 */
void __cdecl sou_mixer_terminate(int *param_1); /* 0x004d2d70 */
float10 FUN_004d54b4(void); /* 0x004d54b4 */
int __cdecl FUN_004d56f0(void); /* 0x004d56f0 */
uint __cdecl FUN_004d5740(int param_1); /* 0x004d5740 */
uint __cdecl FUN_004d57c0(int param_1,int param_2); /* 0x004d57c0 */
uint __cdecl FUN_004d5800(int param_1); /* 0x004d5800 */
uint __cdecl FUN_004d5830(uint param_1,uint param_2); /* 0x004d5830 */
char * __cdecl FUN_004d5860(int param_1,char *param_2,uint param_3); /* 0x004d5860 */
uint __cdecl FUN_004d5990(uint param_1); /* 0x004d5990 */
undefined * FUN_004d5de0(int a1); /* 0x004d5de0 */
int __cdecl FUN_004d5e1c(void); /* 0x004d5e1c */
undefined4 FUN_004d5e30(void); /* 0x004d5e30 */
undefined * __stdcall FUN_004d5e35(int a1); /* 0x004d5e35 */
void __cdecl msc_MemSet(uint param_1,uint param_2,uint param_3); /* 0x004d5e50 */
int __cdecl msc_error_SaveString(char *fmt,...); /* 0x004d5f70 */
void __cdecl FUN_004d5fd0(byte *dst,int value,int count); /* 0x004d5fd0 */
void __cdecl FUN_004d6030(void); /* 0x004d6030 */
void __cdecl FUN_004d6046(void); /* 0x004d6046 */
void __cdecl FUN_004d6050(void); /* 0x004d6050 */
void __cdecl FUN_004d605b(void); /* 0x004d605b */
void __cdecl FUN_004d6070(void); /* 0x004d6070 */
void __cdecl FUN_004d607b(void); /* 0x004d607b */
void __cdecl FUN_004d6090(void); /* 0x004d6090 */
void __cdecl FUN_004d609e(void); /* 0x004d609e */
void __cdecl FUN_004d60ac(void); /* 0x004d60ac */
void __cdecl FUN_004d60ba(void); /* 0x004d60ba */
void __cdecl FUN_004d60d0(void); /* 0x004d60d0 */
void __cdecl FUN_004d60db(void); /* 0x004d60db */
void __cdecl FUN_004d60e9(void); /* 0x004d60e9 */
void __cdecl FUN_004d6100(void); /* 0x004d6100 */
void __cdecl FUN_004d610b(void); /* 0x004d610b */

/* ===== clock.c ===== */
int __cdecl Clock_ElapsedMs(void); /* 0x004ad260 */

/* ===== strpbrk.c ===== */
int __cdecl strpbrk_or_strspn(byte *param_1,byte *param_2); /* 0x004ae220 */

/* ===== insane.c ===== */
int __cdecl SmushPlay_GetMovieTime(void); /* 0x004bd370 */
uint __cdecl SmushPlay_SysInitialize(uint param_1,undefined4 *param_2); /* 0x004bd3a0 */
void __cdecl SmushPlay_SysTerminate(void); /* 0x004bd430 */
uint __cdecl SmushPlay_SysStartup(void); /* 0x004bd440 */
void __cdecl SmushPlay_SysShutdown(void); /* 0x004bd4d0 */
void __cdecl SmushPlay_SysSetVideoCallbacks(uint *param_1); /* 0x004bd540 */
uint __cdecl smushplay_GetInfo(int param_1,int param_2); /* 0x004bd7c0 */
uint __cdecl Insane_PrepareFrame(int *param_1,undefined4 *param_2,uint *param_3); /* 0x004bdb00 */
undefined8 __fastcall Insane_Blit8To16Doubled (undefined4 param_1,undefined4 param_2,uint *param_3,int param_4,uint *param_5,int param_6 ,int param_7,int param_8); /* 0x004bdca0 */
void __cdecl Insane_BlitRowsDual(int param_1,int param_2,undefined4 *param_3,int param_4,int param_5,int param_6); /* 0x004bdd50 */
void __cdecl Insane_BlitRows16(ushort *param_1,int param_2,int param_3,int param_4,int param_5,int param_6); /* 0x004bddb0 */
void __cdecl msc_MemCopy(void *dst,void *src,uint n); /* 0x004c3df0 */
void __cdecl Insane_MemCopy(void *dst,void *src,uint n); /* 0x004c3e10 */

/* ===== smush.c ===== */
uint __cdecl SmushPlay_Pause(void); /* 0x004bd500 */
uint __cdecl SmushPlay_Resume(void); /* 0x004bd520 */
void __cdecl SmushPlay_SysConfigureColorLookup(uint param_1); /* 0x004bd560 */
int __cdecl SmushPlay_StartMovie (char *name,int flags,int bufferSize,int x,int y,int w,int h,int a,int sixteenBit); /* 0x004bd570 */
uint __cdecl SmushPlay_StopMovie(void); /* 0x004bd930 */
int __cdecl SmushPlay_UpdateMovie(int *outDone); /* 0x004bd970 */
void __cdecl SmushPlay_SetTranslationTable(uint param_1); /* 0x004bde90 */
uint __cdecl SmushPlay_GetFrameRect(uint *param_1,uint *param_2); /* 0x004bdea0 */
int __cdecl SmushPlay_GetMovieLength(char *path); /* 0x004bdf00 */

/* ===== lightmgr.c ===== */
void __cdecl LightMgr_Refresh(void); /* 0x004be310 */
void __cdecl LightMgr_UpdateDialog(uint param_1); /* 0x004beee0 */

/* ===== lighted.c ===== */
void __cdecl LightEd_SyncFromSet(void); /* 0x004be3b0 */
void __cdecl LightEd_ResetLight(int index,int mode); /* 0x004be4c0 */
void __cdecl LightEd_DeleteLight(uint index); /* 0x004be560 */
void __cdecl LightEd_MakeUniqueName(int param_1,char *param_2); /* 0x004be730 */
void __cdecl LightEd_AddLight(void); /* 0x004be7b0 */
void __cdecl LightEd_SaveSetFile(void); /* 0x004be990 */
void __cdecl LightEd_WriteLightsSection(void *set,void *file); /* 0x004bed40 */
void __cdecl LightEd_FillListBox(int param_1); /* 0x004bef10 */
void __cdecl LightEd_UpdateDialog(int param_1); /* 0x004befe0 */
void __cdecl LightEd_EnableControls(int param_1); /* 0x004bf2f0 */
void __cdecl LightEd_SetDlgFloat(int param_1,int param_2,float param_3,int param_4); /* 0x004bf3f0 */
void __cdecl LightEd_RefreshControl(int param_1,float param_2,uint param_3,int param_4); /* 0x004bf460 */
void __cdecl LightEd_ReadControl(int hdlg,int id); /* 0x004bf560 */
void __cdecl LightEd_SetLightPosComponent(int param_1,short param_2,uint param_3); /* 0x004bf760 */
void __cdecl LightEd_SetLightAngle(int param_1,short param_2,uint param_3); /* 0x004bf7d0 */
void __cdecl LightEd_SetAllEnabled(int param_1); /* 0x004bf850 */
void __cdecl LightEd_MoveMarkerActor(void); /* 0x004bf8b0 */
void __cdecl LightEd_GetLightAngles(int param_1,float *param_2); /* 0x004bf930 */
int __stdcall LightEd_KeyboardProc(int code,uint wParam,uint lParam); /* 0x004bffb0 */

/* ===== mixer.c ===== */
uint __cdecl DSound_Init(void); /* 0x004c0ed0 */
void __cdecl DSound_Shutdown(void); /* 0x004c1090 */
void __cdecl DSound_SetPrimaryVolume(int volume); /* 0x004c1110 */
void __cdecl dsn_fill_thread(void); /* 0x004d27d0 */
int __cdecl DSound_GetPlayBlock(void); /* 0x004d2c60 */
int __cdecl sou_mixer_initialize(int *services,uint tableUnits,int frames); /* 0x004d2d40 */
void __cdecl sou_mixer_mix(byte *data,int accumOffset,uint outFrames,int srcBytes,int unused,int volume,int pan, int format); /* 0x004d2d90 */
void __cdecl sou_mixer_end(short *dst,int frames); /* 0x004d2e60 */
int __cdecl Mixer_InitTables(int *services,uint channels,int frames4,int unused); /* 0x004d2e80 */
int __cdecl Mixer_Free(int *services); /* 0x004d2fb0 */
int sou_mixer_start(void); /* 0x004d3010 */
void __cdecl Mixer_MixVoice(byte *data,int count,int bits,int channels,uint outFrames,int accumOffset,int volume, int pan,int offsetBinary,int byteSwapped); /* 0x004d3040 */
int __cdecl Mixer_ConvertTo16(short *dst,int frames); /* 0x004d31d0 */
void __cdecl Mixer_Mix8MonoLR(byte *src,int count,uint rateFrac,int accumOffset,int volL,int volR); /* 0x004d3240 */
void __cdecl Mixer_Mix8Mono(byte *param_1,int param_2,uint param_3,int param_4,int param_5); /* 0x004d34a0 */
void __cdecl Mixer_Mix16MonoLR(short *param_1,int param_2,uint param_3,int param_4,int param_5,int param_6); /* 0x004d36e0 */
void __cdecl Mixer_Mix16Mono(short *param_1,int param_2,uint param_3,int param_4,int param_5); /* 0x004d38a0 */
void __cdecl Mixer_MixStereoLR_A(ushort *param_1,int param_2,uint param_3,uint param_4,int param_5,int param_6); /* 0x004d3a60 */
void __cdecl Mixer_MixStereo_A(ushort *param_1,int param_2,uint param_3,uint param_4,int param_5); /* 0x004d3c40 */
void __cdecl Mixer_MixStereoLR_B(ushort *param_1,int param_2,uint param_3,uint param_4,int param_5,int param_6); /* 0x004d3e60 */
void __cdecl Mixer_MixStereo_B(ushort *param_1,int param_2,uint param_3,uint param_4,int param_5); /* 0x004d40d0 */

/* ===== lecshare.c ===== */
undefined ** __cdecl LecShare_Initialize(undefined *param_1,undefined4 *param_2,uint param_3,uint param_4); /* 0x004c1390 */
uint __cdecl LecShare_Terminate(void); /* 0x004c13f0 */
int __cdecl LecShare_Startup(void); /* 0x004c1460 */
uint __cdecl LecShare_Shutdown(void); /* 0x004c1500 */
void __cdecl LecShare_Reset(uint param_1,uint param_2); /* 0x004c1590 */
int __cdecl LecShare_Publish(char *name,void *vtable); /* 0x004c15c0 */
uint __cdecl LecShare_Unpublish(uint param_1); /* 0x004c1650 */
void * __cdecl LecShare_Subscribe(char *name,char *pattern); /* 0x004c16c0 */
uint __cdecl LecShare_Unsubscribe(uint param_1); /* 0x004c1800 */
uint __cdecl BatchSubscribe(int *param_1,char *param_2); /* 0x004c1850 */
uint __cdecl GetCatalogEntry(char *param_1,uint param_2); /* 0x004c1990 */
uint __cdecl GetCatalogCount(char *param_1); /* 0x004c1b60 */
uint * __cdecl LecShare_FindEntry(uint param_1); /* 0x004c1be0 */
uint __cdecl LecShare_Nop(void); /* 0x004c1e50 */

/* ===== animplay.c ===== */
int __cdecl anm_Start(void **out,char *name,int fps,int streamArg1,int streamArg2,uint flags); /* 0x004c23c0 */
void __cdecl anm_Stop(void **pp); /* 0x004c2690 */
int __cdecl anm_Render(void *p,int a2,int a3,int a4,int a5,int a6,int a7,int a8,int a9,int a10); /* 0x004c27a0 */
int __cdecl anm_animator_Initialize(void *p); /* 0x004c36b0 */
int __cdecl anm_animator_NewAnim(void *p,char *name,uint flags,int a4,int a5,int a6); /* 0x004c3d30 */

/* ===== zlib.c ===== */
void * __cdecl gz_open(char *path,char *mode,int fd); /* 0x004c3e60 */
void __cdecl gz_check_header(int *param_1); /* 0x004c4120 */
uint __cdecl gz_get_byte(undefined4 *param_1); /* 0x004c4280 */
int __cdecl gz_destroy(int param_1); /* 0x004c42f0 */
int __cdecl gzread(int *param_1,int param_2,int param_3); /* 0x004c43a0 */
int __cdecl gzwrite(undefined4 *param_1,uint param_2,int param_3); /* 0x004c45b0 */
uint __cdecl gz_do_flush(int param_1,uint param_2); /* 0x004c4690 */
uint __cdecl gzseek(undefined4 *param_1,uint param_2,int param_3); /* 0x004c4750 */
uint __cdecl gzrewind(undefined4 *param_1); /* 0x004c48a0 */
int __cdecl gz_getLong(int param_1); /* 0x004c4920 */
uint __cdecl gzclose(int param_1); /* 0x004c4970 */
void __cdecl gz_putLong(void *file,uint x); /* 0x004c49c0 */
undefined4 zlibVersion(void); /* 0x004c4c40 */
uint __cdecl fle_zfilio_config(int cmd,...); /* 0x004c57d0 */
uint __cdecl inflateReset(int param_1); /* 0x004c6040 */
uint __cdecl inflateEnd(int param_1); /* 0x004c6090 */
uint __cdecl inflateInit2_(int param_1,int param_2,char *param_3,int param_4); /* 0x004c60e0 */
undefined * __cdecl inflate(int *param_1,int param_2); /* 0x004c61f0 */
uint __cdecl deflateInit2_(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,char *param_7, int param_8); /* 0x004c6640 */
uint __cdecl deflateReset(int param_1); /* 0x004c6870 */
uint __cdecl deflate(int *param_1,int param_2); /* 0x004c68f0 */
void __cdecl putShortMSB(int param_1,uint param_2); /* 0x004c6bb0 */
void __cdecl flush_pending(int param_1); /* 0x004c6be0 */
uint __cdecl deflateEnd(int param_1); /* 0x004c6c60 */
void __cdecl lm_init(int param_1); /* 0x004c6d10 */
uint __cdecl crc32(uint param_1,byte *param_2,uint param_3); /* 0x004c79b0 */
void __cdecl zcalloc(uint param_1,uint param_2,uint param_3); /* 0x004c7af0 */
void __cdecl inflate_blocks_reset(int *param_1,int param_2,int *param_3); /* 0x004c7b20 */
undefined4 * __cdecl inflate_blocks_new(int param_1,uint param_2,int param_3); /* 0x004c7ba0 */
undefined * __cdecl inflate_blocks(uint *param_1,int *param_2,uint param_3); /* 0x004c7c50 */
uint __cdecl inflate_blocks_free(int param_1,int param_2); /* 0x004c8940 */
void __cdecl _tr_init(int param_1); /* 0x004c8ac0 */
void __cdecl init_block(int param_1); /* 0x004c8b30 */
void __cdecl _tr_align(int param_1); /* 0x004c8c40 */
void __cdecl bi_flush(int param_1); /* 0x004ca480 */
void __cdecl bi_windup(int param_1); /* 0x004ca510 */
void __cdecl copy_block(int param_1,undefined1 *param_2,int param_3,int param_4); /* 0x004ca580 */
undefined * __cdecl inflate_codes_new(undefined1 param_1,undefined1 param_2,uint param_3,uint param_4,int param_5); /* 0x004ca620 */
undefined * __cdecl inflate_codes(uint param_1,byte *param_2,int param_3); /* 0x004ca660 */
void __cdecl inflate_codes_free(uint param_1,int param_2); /* 0x004cae10 */
int __cdecl inflate_trees_bits(uint param_1,int *param_2,uint param_3,uint param_4,int param_5); /* 0x004cae30 */
uint __cdecl huft_build(int *param_1,uint param_2,uint param_3,int param_4,int param_5,uint *param_6, uint *param_7,int param_8,uint *param_9,uint param_10); /* 0x004caee0 */
int __cdecl inflate_trees_dynamic (uint param_1,uint param_2,int param_3,int *param_4,int *param_5,uint param_6,uint param_7 ,uint param_8,int param_9); /* 0x004cb390 */
uint __cdecl inflate_trees_fixed(uint *param_1,uint *param_2,undefined4 *param_3,undefined4 *param_4); /* 0x004cb520 */
int __cdecl inflate_flush(int param_1,int param_2,int param_3); /* 0x004cb550 */
uint __cdecl inflate_fast(int param_1,uint param_2,int param_3,int param_4,int param_5,int *param_6); /* 0x004cb690 */

/* ===== zfile.c ===== */
void __cdecl Zfile_fle_Close(int *z); /* 0x004c5ab0 */

/* ===== stdfile.c ===== */
int __cdecl StdFile_fle_Tell(void *file); /* 0x004c5e30 */
int __cdecl fle_Size(void *file); /* 0x004c5e90 */
int __cdecl fle_Eof(void *file); /* 0x004c5f50 */

/* ===== blocky16.c ===== */
uint __cdecl fob_flobdec_blocky16_module(int *param_1,uint param_2); /* 0x004cc210 */
int __cdecl fob_flobdec_blocky16_config(int key,...); /* 0x004cc250 */
void __cdecl Blocky16_module_terminate(void); /* 0x004cc290 */
uint __cdecl Blocky16_module_startup(void); /* 0x004cc2c0 */
void __cdecl Blocky16_module_shutdown(void); /* 0x004cc340 */
char * __cdecl Blocky16_flobdec_Info(int param_1); /* 0x004cc370 */
uint __cdecl Blocky16_flobdec_GetID(void); /* 0x004cc3a0 */
uint __cdecl Blocky16_flobdec_DecodeHeader(int param_1); /* 0x004cc3c0 */
int __cdecl AllocBuffers(int param_1,int param_2,int param_3); /* 0x004cc410 */
void __cdecl Blocky16_flobdec_Reset(void); /* 0x004cc590 */
void __cdecl Blocky16_flobdec_DecodeBody (void *param_1,uint *param_2,int param_3,int param_4,int param_5,byte *param_6, uint param_7,byte param_8); /* 0x004cc620 */
uint __cdecl Blocky16_flobdec_GetVal (short *param_1,int param_2,int *param_3,int *param_4,int *param_5,int *param_6); /* 0x004cc650 */
void __cdecl fob_blk16_configure(uint param_1); /* 0x004cc6a0 */
void __cdecl fob_block_maketiles(int size); /* 0x004cc7d0 */
int __cdecl Blocky16_DecodeFrame(void *dst,uint *clip,int x,int y,int palette,byte *hdr,byte flags); /* 0x004ccd00 */
void __cdecl Blocky16_BuildExpandTable(void *param_1); /* 0x004cd1e0 */
void __cdecl Blocky16_DecodeHalfRows16(void *param_1,ushort *param_2,int param_3,int param_4); /* 0x004cd300 */
void __cdecl Blocky16_DecodeHalfRows8(void *param_1,byte *param_2,int param_3,int param_4,int param_5); /* 0x004cd450 */
void __cdecl Blocky16_DecodeBlocks (byte *dst,byte *src,int prevOffset,int prev2Offset,int width,short *motion,short *colors, int height,int unused,byte *split4,byte *split8,ushort *pairColors); /* 0x004cd550 */
byte * __cdecl Blocky16_DecodeBlock8(byte *src,byte *dst,int pitch); /* 0x004cd610 */
byte * __cdecl block16_RenderBlock4(byte *src,byte *dst,int pitch); /* 0x004cd9b0 */
byte * __cdecl block16_RenderBlock2(byte *src,byte *dst,int pitch); /* 0x004cdb80 */

/* ===== insanetimer.c ===== */
int __cdecl sys_timer_module(int *services,uint workspaceSize); /* 0x004cdc90 */
void InsaneTimer_module_terminate(void); /* 0x004cdce0 */
int InsaneTimer_module_startup(void); /* 0x004cdd10 */
void InsaneTimer_module_shutdown(void); /* 0x004cdd60 */
int InsaneTimer_StartThread(void); /* 0x004cdd80 */
undefined * __stdcall timer_thread(int a1); /* 0x004cddf0 */
void InsaneTimer_StopThread(void); /* 0x004cde80 */
void sys_Disable(void); /* 0x004cdef0 */
void sys_Enable(void); /* 0x004cdf00 */
int __cdecl sys_Alloc(void *callback,int period,uint flags,int user); /* 0x004cdf10 */
void __cdecl sys_Free(int slot); /* 0x004cdf80 */
void __cdecl sys_Reset(int slot,int period); /* 0x004cdfa0 */
void __cdecl sys_Delay(int ticks); /* 0x004cdfd0 */
int __cdecl sys_GetTime(void); /* 0x004ce000 */
void __cdecl InsaneTimer_Tick(void); /* 0x004ce060 */
void __cdecl sys_timer_dispatcher(void); /* 0x004ce1d0 */
void __cdecl InsaneTimer_RunDeferred(void); /* 0x004ce260 */

/* ===== videobitmap.c ===== */
int __cdecl bmp_bitmap_Alloc(void *out,int width,int height,int format); /* 0x004ce3e0 */
int __cdecl gra_ConvertCopy(byte *src,void *srcFmt,int count,byte *palette,byte *dst,void *dstFmt, byte *expandTable); /* 0x004cedc0 */

/* ===== video.c ===== */
void __cdecl gra_BlitRectLookup(int *param_1,uint *param_2,int param_3,int param_4,int *param_5,byte *param_6, byte *param_7); /* 0x004cea30 */
void __cdecl gra_SetBuffer(char *param_1,int param_2,int param_3,char *param_4); /* 0x004cec40 */
int __cdecl gra_ConvertToLecColor(void *src,void *fmt,int count,byte *palette,byte *dst); /* 0x004cf010 */
int __cdecl gra_ConvertFromLecColor(void *dst,void *fmt,int count,int unused,byte *src); /* 0x004cf520 */
void __cdecl Video_CopyRectDstFirst (byte *dst,byte *src,int dstX,uint dstY,int srcX,uint srcY,uint width,int rows, uint dstPitch,uint srcPitch); /* 0x004cfdb0 */
void __cdecl Video_ExpandIndexed8(byte *dst,byte *src,int count,int bytesPerPixel,byte *table); /* 0x004cfdf0 */
void __cdecl Video_ExpandIndexed16(byte *dst,ushort *src,int count,int bytesPerPixel,byte *table); /* 0x004cfea0 */
void __cdecl Video_Rgba32To555(ushort *dst,uint *src,uint count); /* 0x004cff60 */
void __cdecl Video_555ToRgba32(uint *dst,ushort *src,uint count); /* 0x004cffe0 */
void __cdecl Video_Rgba32To565(ushort *dst,uint *src,uint count); /* 0x004d0070 */
void __cdecl Video_565ToRgba32(uint *dst,ushort *src,uint count); /* 0x004d00f0 */
void __cdecl Video_Rgba32To565Alt(ushort *dst,uint *src,uint count); /* 0x004d0180 */
void __cdecl Video_565AltToRgba32(uint *dst,ushort *src,uint count); /* 0x004d01f0 */
void __cdecl Video_CopyRect(byte *src,byte *dst,int srcX,uint srcY,int dstX,uint dstY,uint width,int rows, uint srcPitch,uint dstPitch); /* 0x004d0260 */

/* ===== soundmodule.c ===== */
int __cdecl sou_sound_module(int *services,uint moduleSize); /* 0x004d0300 */
void SoundModule_module_terminate(void); /* 0x004d03a0 */
int SoundModule_module_startup(void); /* 0x004d03d0 */
void SoundModule_module_shutdown(void); /* 0x004d0510 */
int __cdecl engine_Initialize(int rate,int limit,uint size,...); /* 0x004d0550 */
int SoundModule_Close(void); /* 0x004d0610 */
int __cdecl SoundModule_AddTrackBuffer(uint size,int limit); /* 0x004d06a0 */
void __cdecl sou_engine_Start(byte *p,int id,int volume,int pan,uint flags); /* 0x004d0860 */
void __cdecl sou_engine_Stop(uint id); /* 0x004d0a50 */
void sou_engine_Pause(void); /* 0x004d0a80 */
void sou_engine_Resume(void); /* 0x004d0a90 */
void sou_engine_StopAll(void); /* 0x004d0aa0 */
void __cdecl sou_engine_SetVol(int id,uint volume); /* 0x004d0ad0 */
uint __cdecl sou_engine_GetVol(uint id); /* 0x004d0b10 */
void __cdecl sou_engine_SetPan(int id,byte pan); /* 0x004d0b60 */
int __cdecl sou_engine_GetPan(uint id); /* 0x004d0b90 */
void __cdecl sou_engine_SetHVol(int arg); /* 0x004d0bd0 */
int sou_engine_GetHVol(void); /* 0x004d0bf0 */
void __cdecl sou_engine_SetRate(uint rate); /* 0x004d0c00 */
int __cdecl sou_engine_Query(uint id); /* 0x004d0c30 */
int __cdecl sou_engine_SetParam(int unused,int which,uint a,uint b); /* 0x004d0d70 */
int __cdecl sou_engine_GetParam(int unused,int which,uint *a,uint *b); /* 0x004d0e00 */
uint __cdecl SoundModule_GetChannelVolume(byte channel); /* 0x004d0eb0 */
void __cdecl SoundModule_SetChannelVolume(byte channel,byte value); /* 0x004d0ed0 */
void __cdecl SoundModule_PlayVoc(byte *src,uint size,int id,int volume,int pan,uint flags); /* 0x004d0f00 */
void __cdecl sou_engine_start_stream (byte *data,int size,int id,int volume,int pan,uint flags,int key,int chunkNo,int kind, int whole); /* 0x004d1180 */
void SoundModule_SyncClock(void); /* 0x004d1690 */
void __cdecl sou_engine_fill(int frames,void *mix); /* 0x004d16a0 */
void __cdecl SoundModule_AdvanceClock(double ticks); /* 0x004d2340 */

/* ===== dsnd.c ===== */
void __cdecl Dsnd_MemCopyCdecl(void *dst,void *src,uint n); /* 0x004d23e0 */
void __cdecl Dsnd_MemFillCdecl(void *dst,int value,uint n); /* 0x004d2400 */
void __cdecl Dsnd_MemCopy(void *dst,void *src,uint n); /* 0x004d2cb0 */
void __cdecl Dsnd_MemFill(void *dst,int value,uint n); /* 0x004d2ce0 */

/* ===== dsnddriver.c ===== */
int __cdecl sou_dsnd_module(int *services,uint moduleSize); /* 0x004d2420 */
void DsndDriver_module_terminate(void); /* 0x004d2480 */
int DsndDriver_module_startup(void); /* 0x004d24b0 */
void DsndDriver_module_shutdown(void); /* 0x004d2520 */
int __cdecl dsn_initialize(int rate,int unused,void *mix); /* 0x004d2550 */
void dsn_terminate(void); /* 0x004d25f0 */
void __cdecl dsn_setvol(uint volume); /* 0x004d2630 */
uint dsn_getvol(void); /* 0x004d27b0 */
int dsn_getrate(void); /* 0x004d27c0 */
int DsndDriver_InitDirectSound(void); /* 0x004d2940 */
void __cdecl DsndDriver_CreateStreamBuffer(int blocks); /* 0x004d2aa0 */
void DsndDriver_ReleaseDirectSound(void); /* 0x004d2bf0 */

/* ===== rle.c ===== */
void __cdecl msc_rle_DecompressBlock(byte *param_1,uint param_2,int param_3); /* 0x004d5e70 */
void __cdecl msc_rle_DecompressInitialize(int *param_1); /* 0x004d5eb0 */
uint __fastcall msc_rle_DecompressGetbyte(undefined4 param_1); /* 0x004d5ed0 */

/* ===== referenced, not decompiled here (thunks, imports, unknown FUN_) ===== */
int STDCALL AnimatePalette() __asm__("_AnimatePalette@16"); /* import */
int STDCALL BitBlt() __asm__("_BitBlt@36"); /* import */
int STDCALL CallNextHookEx() __asm__("_CallNextHookEx@16"); /* import */
int STDCALL CheckDlgButton() __asm__("_CheckDlgButton@12"); /* import */
int STDCALL CloseHandle() __asm__("_CloseHandle@4"); /* import */
int STDCALL CloseWindow() __asm__("_CloseWindow@4"); /* import */
int STDCALL CompareStringA() __asm__("_CompareStringA@24"); /* import */
int STDCALL CompareStringW() __asm__("_CompareStringW@24"); /* import */
int CosUtil_PtrFromHandle(); /* import */
int Cos_CreateCosInstance(); /* import */
int Cos_Free(); /* import */
int Cos_FreeCosInstance(); /* import */
int Cos_GetCostumeName(); /* import */
int Cos_Initialize(); /* import */
int Cos_InstChoreName(); /* import */
int Cos_InstChoreStatus(); /* import */
int Cos_InstCompleteChore(); /* import */
int Cos_InstComponentInfo(); /* import */
int Cos_InstCountChores(); /* import */
int Cos_InstCountComponents(); /* import */
int Cos_InstGetCostume(); /* import */
int Cos_InstGetInstanceData(); /* import */
int Cos_InstGetUserData(); /* import */
int Cos_InstPlayChore(); /* import */
int Cos_InstRescue(); /* import */
int Cos_InstSetChoreLoop(); /* import */
int Cos_InstSetUserData(); /* import */
int Cos_InstStopChore(); /* import */
int Cos_InstStopChores(); /* import */
int Cos_InstUpdateChore(); /* import */
int Cos_InstUpdateChores(); /* import */
int Cos_Load(); /* import */
int Cos_NewIntTag(); /* import */
int Cos_NewStateBasedTag(); /* import */
int Cos_RegisterComponent(); /* import */
int Cos_RegisterInstanceHook(); /* import */
int Cos_RegisterSaveHook(); /* import */
int Cos_RegisterSaveVerify(); /* import */
int Cos_Restore(); /* import */
int Cos_RestoreInstance(); /* import */
int Cos_Save(); /* import */
int Cos_SaveInstance(); /* import */
int STDCALL CreateCompatibleDC() __asm__("_CreateCompatibleDC@4"); /* import */
int STDCALL CreateDIBSection() __asm__("_CreateDIBSection@24"); /* import */
int STDCALL CreateDialogParamA() __asm__("_CreateDialogParamA@20"); /* import */
int STDCALL CreateEventA() __asm__("_CreateEventA@16"); /* import */
int STDCALL CreateFileA() __asm__("_CreateFileA@28"); /* import */
int STDCALL CreateFontA() __asm__("_CreateFontA@56"); /* import */
int STDCALL CreatePalette() __asm__("_CreatePalette@4"); /* import */
int STDCALL CreateThread() __asm__("_CreateThread@24"); /* import */
int STDCALL CreateWindowExA() __asm__("_CreateWindowExA@48"); /* import */
int STDCALL DebugBreak() __asm__("_DebugBreak@0"); /* import */
int STDCALL DefWindowProcA() __asm__("_DefWindowProcA@16"); /* import */
int STDCALL DeleteCriticalSection() __asm__("_DeleteCriticalSection@4"); /* import */
int STDCALL DeleteDC() __asm__("_DeleteDC@4"); /* import */
int STDCALL DeleteFileA() __asm__("_DeleteFileA@4"); /* import */
int STDCALL DeleteObject() __asm__("_DeleteObject@4"); /* import */
int STDCALL DestroyWindow() __asm__("_DestroyWindow@4"); /* import */
int STDCALL DialogBoxIndirectParamA() __asm__("_DialogBoxIndirectParamA@20"); /* import */
int STDCALL DirectDrawCreate() __asm__("_DirectDrawCreate@12"); /* import */
int STDCALL DirectDrawEnumerateA() __asm__("_DirectDrawEnumerateA@8"); /* import */
int STDCALL DirectInputCreateA() __asm__("_DirectInputCreateA@16"); /* import */
int STDCALL DirectSoundCreate() __asm__("_DirectSoundCreate@12"); /* import */
int STDCALL DispatchMessageA() __asm__("_DispatchMessageA@4"); /* import */
int STDCALL EnableWindow() __asm__("_EnableWindow@8"); /* import */
int STDCALL EndDialog() __asm__("_EndDialog@8"); /* import */
int STDCALL EnterCriticalSection() __asm__("_EnterCriticalSection@4"); /* import */
int STDCALL ExitProcess() __asm__("_ExitProcess@4"); /* import */
int STDCALL FileTimeToLocalFileTime() __asm__("_FileTimeToLocalFileTime@8"); /* import */
int STDCALL FileTimeToSystemTime() __asm__("_FileTimeToSystemTime@8"); /* import */
int STDCALL FindClose() __asm__("_FindClose@4"); /* import */
int STDCALL FindFirstFileA() __asm__("_FindFirstFileA@8"); /* import */
int STDCALL FindNextFileA() __asm__("_FindNextFileA@8"); /* import */
int STDCALL FindWindowA() __asm__("_FindWindowA@8"); /* import */
int STDCALL FlushFileBuffers() __asm__("_FlushFileBuffers@4"); /* import */
int STDCALL FreeEnvironmentStringsA() __asm__("_FreeEnvironmentStringsA@4"); /* import */
int STDCALL FreeEnvironmentStringsW() __asm__("_FreeEnvironmentStringsW@4"); /* import */
int STDCALL FreeLibrary() __asm__("_FreeLibrary@4"); /* import */
int STDCALL GdiFlush() __asm__("_GdiFlush@0"); /* import */
int STDCALL GetACP() __asm__("_GetACP@0"); /* import */
int STDCALL GetCPInfo() __asm__("_GetCPInfo@8"); /* import */
int STDCALL GetCommandLineA() __asm__("_GetCommandLineA@0"); /* import */
int STDCALL GetCurrentDirectoryA() __asm__("_GetCurrentDirectoryA@8"); /* import */
int STDCALL GetCurrentProcess() __asm__("_GetCurrentProcess@0"); /* import */
int STDCALL GetCurrentThreadId() __asm__("_GetCurrentThreadId@0"); /* import */
int STDCALL GetDC() __asm__("_GetDC@4"); /* import */
int STDCALL GetDeviceCaps() __asm__("_GetDeviceCaps@8"); /* import */
int STDCALL GetDiskFreeSpaceA() __asm__("_GetDiskFreeSpaceA@20"); /* import */
int STDCALL GetDlgItem() __asm__("_GetDlgItem@8"); /* import */
int STDCALL GetDlgItemInt() __asm__("_GetDlgItemInt@16"); /* import */
int STDCALL GetDlgItemTextA() __asm__("_GetDlgItemTextA@16"); /* import */
int STDCALL GetDriveTypeA() __asm__("_GetDriveTypeA@4"); /* import */
int STDCALL GetEnvironmentStrings() __asm__("_GetEnvironmentStrings@0"); /* import */
int STDCALL GetEnvironmentStringsW() __asm__("_GetEnvironmentStringsW@0"); /* import */
int STDCALL GetExitCodeThread() __asm__("_GetExitCodeThread@8"); /* import */
int STDCALL GetFileType() __asm__("_GetFileType@4"); /* import */
int STDCALL GetFocus() __asm__("_GetFocus@0"); /* import */
int STDCALL GetFullPathNameA() __asm__("_GetFullPathNameA@16"); /* import */
int STDCALL GetKeyState() __asm__("_GetKeyState@4"); /* import */
int STDCALL GetLastError() __asm__("_GetLastError@0"); /* import */
int STDCALL GetLocalTime() __asm__("_GetLocalTime@4"); /* import */
int STDCALL GetLocaleInfoA() __asm__("_GetLocaleInfoA@16"); /* import */
int STDCALL GetLocaleInfoW() __asm__("_GetLocaleInfoW@16"); /* import */
int STDCALL GetLogicalDriveStringsA() __asm__("_GetLogicalDriveStringsA@8"); /* import */
int STDCALL GetMessageA() __asm__("_GetMessageA@16"); /* import */
int STDCALL GetModuleFileNameA() __asm__("_GetModuleFileNameA@12"); /* import */
int STDCALL GetModuleHandleA() __asm__("_GetModuleHandleA@4"); /* import */
int STDCALL GetOEMCP() __asm__("_GetOEMCP@0"); /* import */
int STDCALL GetOpenFileNameA() __asm__("_GetOpenFileNameA@4"); /* import */
int STDCALL GetParent() __asm__("_GetParent@4"); /* import */
int STDCALL GetProcAddress() __asm__("_GetProcAddress@8"); /* import */
int STDCALL GetSaveFileNameA() __asm__("_GetSaveFileNameA@4"); /* import */
int STDCALL GetStartupInfoA() __asm__("_GetStartupInfoA@4"); /* import */
int STDCALL GetStdHandle() __asm__("_GetStdHandle@4"); /* import */
int STDCALL GetStockObject() __asm__("_GetStockObject@4"); /* import */
int STDCALL GetStringTypeA() __asm__("_GetStringTypeA@20"); /* import */
int STDCALL GetStringTypeW() __asm__("_GetStringTypeW@16"); /* import */
int STDCALL GetSystemMetrics() __asm__("_GetSystemMetrics@4"); /* import */
int STDCALL GetSystemPaletteEntries() __asm__("_GetSystemPaletteEntries@16"); /* import */
int STDCALL GetTempFileNameA() __asm__("_GetTempFileNameA@16"); /* import */
int STDCALL GetTempPathA() __asm__("_GetTempPathA@8"); /* import */
int STDCALL GetTickCount() __asm__("_GetTickCount@0"); /* import */
int STDCALL GetTimeZoneInformation() __asm__("_GetTimeZoneInformation@4"); /* import */
int STDCALL GetVersion() __asm__("_GetVersion@0"); /* import */
int STDCALL GetWindowThreadProcessId() __asm__("_GetWindowThreadProcessId@8"); /* import */
int STDCALL GlobalMemoryStatus() __asm__("_GlobalMemoryStatus@4"); /* import */
int STDCALL HeapAlloc() __asm__("_HeapAlloc@12"); /* import */
int STDCALL HeapCreate() __asm__("_HeapCreate@12"); /* import */
int STDCALL HeapDestroy() __asm__("_HeapDestroy@4"); /* import */
int STDCALL HeapFree() __asm__("_HeapFree@12"); /* import */
int STDCALL HeapReAlloc() __asm__("_HeapReAlloc@16"); /* import */
int STDCALL HeapSize() __asm__("_HeapSize@12"); /* import */
int ImGetParam(); /* import */
int ImPause(); /* import */
int ImResume(); /* import */
int ImSetAttribute(); /* import */
int ImSetCuePoint(); /* import */
int ImSetGroupVol(); /* import */
int ImSetSequence(); /* import */
int ImSetState(); /* import */
int ImStartRecording(); /* import */
int ImStopAllSounds(); /* import */
int STDCALL InitCommonControls() __asm__("_InitCommonControls@0"); /* import */
int STDCALL InitializeCriticalSection() __asm__("_InitializeCriticalSection@4"); /* import */
int STDCALL InterlockedDecrement() __asm__("_InterlockedDecrement@4"); /* import */
int STDCALL InterlockedIncrement() __asm__("_InterlockedIncrement@4"); /* import */
int STDCALL IsBadCodePtr() __asm__("_IsBadCodePtr@4"); /* import */
int STDCALL IsBadReadPtr() __asm__("_IsBadReadPtr@8"); /* import */
int STDCALL IsBadWritePtr() __asm__("_IsBadWritePtr@8"); /* import */
int STDCALL IsDialogMessageA() __asm__("_IsDialogMessageA@8"); /* import */
int STDCALL IsDlgButtonChecked() __asm__("_IsDlgButtonChecked@8"); /* import */
int STDCALL IsIconic() __asm__("_IsIconic@4"); /* import */
int STDCALL IsWindowEnabled() __asm__("_IsWindowEnabled@4"); /* import */
int STDCALL LCMapStringA() __asm__("_LCMapStringA@24"); /* import */
int STDCALL LCMapStringW() __asm__("_LCMapStringW@24"); /* import */
int STDCALL LeaveCriticalSection() __asm__("_LeaveCriticalSection@4"); /* import */
int STDCALL LoadCursorA() __asm__("_LoadCursorA@8"); /* import */
int STDCALL LoadIconA() __asm__("_LoadIconA@8"); /* import */
int STDCALL LoadLibraryA() __asm__("_LoadLibraryA@4"); /* import */
int STDCALL MessageBeep() __asm__("_MessageBeep@4"); /* import */
int STDCALL MessageBoxA() __asm__("_MessageBoxA@16"); /* import */
int STDCALL MoveFileA() __asm__("_MoveFileA@8"); /* import */
int STDCALL MultiByteToWideChar() __asm__("_MultiByteToWideChar@24"); /* import */
int STDCALL OutputDebugStringA() __asm__("_OutputDebugStringA@4"); /* import */
int STDCALL PeekMessageA() __asm__("_PeekMessageA@20"); /* import */
int STDCALL PostQuitMessage() __asm__("_PostQuitMessage@4"); /* import */
int STDCALL QueryPerformanceCounter() __asm__("_QueryPerformanceCounter@4"); /* import */
int STDCALL QueryPerformanceFrequency() __asm__("_QueryPerformanceFrequency@4"); /* import */
int STDCALL RaiseException() __asm__("_RaiseException@16"); /* import */
int STDCALL ReadFile() __asm__("_ReadFile@20"); /* import */
int STDCALL RealizePalette() __asm__("_RealizePalette@4"); /* import */
int STDCALL RegCloseKey() __asm__("_RegCloseKey@4"); /* import */
int STDCALL RegCreateKeyExA() __asm__("_RegCreateKeyExA@36"); /* import */
int STDCALL RegDeleteKeyA() __asm__("_RegDeleteKeyA@8"); /* import */
int STDCALL RegEnumValueA() __asm__("_RegEnumValueA@32"); /* import */
int STDCALL RegOpenKeyExA() __asm__("_RegOpenKeyExA@20"); /* import */
int STDCALL RegQueryInfoKeyA() __asm__("_RegQueryInfoKeyA@48"); /* import */
int STDCALL RegQueryValueExA() __asm__("_RegQueryValueExA@24"); /* import */
int STDCALL RegSetValueExA() __asm__("_RegSetValueExA@24"); /* import */
int STDCALL RegisterClassExA() __asm__("_RegisterClassExA@4"); /* import */
int STDCALL ReleaseDC() __asm__("_ReleaseDC@8"); /* import */
int STDCALL RtlUnwind() __asm__("_RtlUnwind@16"); /* import */
int STDCALL SelectObject() __asm__("_SelectObject@8"); /* import */
int STDCALL SelectPalette() __asm__("_SelectPalette@12"); /* import */
int STDCALL SendDlgItemMessageA() __asm__("_SendDlgItemMessageA@20"); /* import */
int STDCALL SendMessageA() __asm__("_SendMessageA@16"); /* import */
int STDCALL SetActiveWindow() __asm__("_SetActiveWindow@4"); /* import */
int STDCALL SetBkMode() __asm__("_SetBkMode@8"); /* import */
int STDCALL SetCurrentDirectoryA() __asm__("_SetCurrentDirectoryA@4"); /* import */
int STDCALL SetCursor() __asm__("_SetCursor@4"); /* import */
int STDCALL SetDIBColorTable() __asm__("_SetDIBColorTable@16"); /* import */
int STDCALL SetDlgItemInt() __asm__("_SetDlgItemInt@16"); /* import */
int STDCALL SetDlgItemTextA() __asm__("_SetDlgItemTextA@12"); /* import */
int STDCALL SetEndOfFile() __asm__("_SetEndOfFile@4"); /* import */
int STDCALL SetEnvironmentVariableA() __asm__("_SetEnvironmentVariableA@8"); /* import */
int STDCALL SetFilePointer() __asm__("_SetFilePointer@16"); /* import */
int STDCALL SetFocus() __asm__("_SetFocus@4"); /* import */
int STDCALL SetForegroundWindow() __asm__("_SetForegroundWindow@4"); /* import */
int STDCALL SetHandleCount() __asm__("_SetHandleCount@4"); /* import */
int STDCALL SetLastError() __asm__("_SetLastError@4"); /* import */
int STDCALL SetStdHandle() __asm__("_SetStdHandle@8"); /* import */
int STDCALL SetTextColor() __asm__("_SetTextColor@8"); /* import */
int STDCALL SetThreadPriority() __asm__("_SetThreadPriority@8"); /* import */
int STDCALL SetUnhandledExceptionFilter() __asm__("_SetUnhandledExceptionFilter@4"); /* import */
int STDCALL SetWindowLongA() __asm__("_SetWindowLongA@12"); /* import */
int STDCALL SetWindowPos() __asm__("_SetWindowPos@28"); /* import */
int STDCALL SetWindowsHookExA() __asm__("_SetWindowsHookExA@16"); /* import */
int STDCALL ShowCursor() __asm__("_ShowCursor@4"); /* import */
int STDCALL ShowWindow() __asm__("_ShowWindow@8"); /* import */
int STDCALL SoundStartVoiceStream() __asm__("_SoundStartVoiceStream"); /* import */
int STDCALL SoundStopVoiceStream() __asm__("_SoundStopVoiceStream"); /* import */
int SoundsCloseVoiceFile(); /* import */
int SoundsFadeParam(); /* import */
int SoundsFloodMusicBuffer(); /* import */
int SoundsGetParam(); /* import */
int SoundsIsSoundPlaying(); /* import */
int SoundsLoadProcessStartSound(); /* import */
int SoundsLoadStartSound(); /* import */
int SoundsPeriodic(); /* import */
int SoundsSetParam(); /* import */
int SoundsStopSound(); /* import */
int Sounds_PlatformDevice(); /* import */
int STDCALL TerminateProcess() __asm__("_TerminateProcess@8"); /* import */
int STDCALL TextOutA() __asm__("_TextOutA@20"); /* import */
int STDCALL TlsAlloc() __asm__("_TlsAlloc@0"); /* import */
int STDCALL TlsGetValue() __asm__("_TlsGetValue@4"); /* import */
int STDCALL TlsSetValue() __asm__("_TlsSetValue@8"); /* import */
int STDCALL TranslateMessage() __asm__("_TranslateMessage@4"); /* import */
int STDCALL UnhandledExceptionFilter() __asm__("_UnhandledExceptionFilter@4"); /* import */
int STDCALL UnhookWindowsHookEx() __asm__("_UnhookWindowsHookEx@4"); /* import */
int STDCALL UpdateWindow() __asm__("_UpdateWindow@4"); /* import */
int STDCALL VirtualAlloc() __asm__("_VirtualAlloc@16"); /* import */
int STDCALL VirtualFree() __asm__("_VirtualFree@12"); /* import */
int STDCALL WaitForSingleObject() __asm__("_WaitForSingleObject@8"); /* import */
int STDCALL WideCharToMultiByte() __asm__("_WideCharToMultiByte@32"); /* import */
int STDCALL WriteFile() __asm__("_WriteFile@20"); /* import */
int grimSound_LipSyncFree(); /* import */
int grimSound_LipSyncLoad(); /* import */
int iMUSE_DeclareBufferSizes(); /* import */
int iMUSE_GetMemoryFootprint(); /* import */
int iMUSE_GetPhoneme(); /* import */
int iMUSE_GetSoundCacheSize(); /* import */
int iMUSE_SetHook(); /* import */
int iMUSE_SetVoiceEffect(); /* import */
int STDCALL joyGetDevCapsA() __asm__("_joyGetDevCapsA@12"); /* import */
int STDCALL joyGetNumDevs() __asm__("_joyGetNumDevs@0"); /* import */
int STDCALL joyGetPos() __asm__("_joyGetPos@8"); /* import */
int STDCALL joyGetPosEx() __asm__("_joyGetPosEx@8"); /* import */
int lua_Initialize(); /* import */
int lua_Restore(); /* import */
int lua_Save(); /* import */
int lua_beginblock(); /* import */
int lua_callfunction(); /* import */
int lua_collectgarbage(); /* import */
int lua_createtable(); /* import */
int lua_currenttask(); /* import */
int lua_dofile(); /* import */
int lua_endblock(); /* import */
int lua_funcinfo(); /* import */
int lua_getglobal(); /* import */
float lua_getnumber(); /* import */
int lua_getobjname(); /* import */
int lua_getref(); /* import */
int lua_getstring(); /* import */
int lua_gettable(); /* import */
int lua_getuserdata(); /* import */
int lua_iolibopen(); /* import */
int lua_isfunction(); /* import */
int lua_isnil(); /* import */
int lua_isnumber(); /* import */
int lua_isstring(); /* import */
int lua_istable(); /* import */
int lua_isuserdata(); /* import */
int lua_lua2C(); /* import */
int lua_mathlibopen(); /* import */
int lua_openlib(); /* import */
int lua_printstack(); /* import */
int lua_pushCclosure(); /* import */
int lua_pushnil(); /* import */
void lua_pushnumber(float); /* import */
int lua_pushobject(); /* import */
int lua_pushstring(); /* import */
int lua_pushtask(); /* import */
int lua_pushusertag(); /* import */
int lua_recognizelib(); /* import */
int lua_ref(); /* import */
int lua_setfallback(); /* import */
int lua_setglobal(); /* import */
int lua_settable(); /* import */
int lua_strlibopen(); /* import */
int lua_tag(); /* import */
int lua_unref(); /* import */
int lua_updatetasks(); /* import */
int STDCALL timeGetTime() __asm__("_timeGetTime@0"); /* import */
int wsprintfA(); /* import */
extern int (STDCALL *SendDlgItemMessageA_exref)(); /* import address table slot */
extern int (STDCALL *lua_assume_binary_exref)(); /* import address table slot */
extern int (STDCALL *lua_gettable_exref)(); /* import address table slot */
extern int (STDCALL *lua_isfunction_exref)(); /* import address table slot */
extern int (STDCALL *lua_isnumber_exref)(); /* import address table slot */
extern int (STDCALL *lua_lua2C_exref)(); /* import address table slot */
extern int (STDCALL *lua_restorehook_exref)(); /* import address table slot */
extern int (STDCALL *lua_savehook_exref)(); /* import address table slot */
