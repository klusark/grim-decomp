/* GRIMFANDANGO.EXE: prototypes of every decompiled function, by module */
#pragma once
#include "ghidra_types.h"

/* ===== window.c ===== */
undefined * __stdcall Win_WinMain(int a1,int a2,int a3,int a4); /* 0x00401010 */
undefined * Win_WndProc(undefined4 param_1,uint param_2,int param_3); /* 0x00402fd0 */
void Win_SetMainHwnd(void *param_1); /* 0x00473360 */
void * Win_GetMainHwnd(void); /* 0x00473370 */
void Win_SetInstance(uint param_1); /* 0x00473380 */
uint Win_GetInstance(void); /* 0x00473390 */
undefined4 Win_IsSysCommandBlocked(undefined4 param_1,int param_2,int param_3); /* 0x004772d0 */
void __cdecl Win_AbortIfAlreadyRunning (void *hInstance,void *hPrevInstance,char *cmdLine,int nCmdShow,char *appName); /* 0x004abf40 */
uint Win_PumpMessages(void); /* 0x004ac020 */
int __cdecl Win_SetWindowedSize(int fullscreen,int w,int h); /* 0x004ac100 */
void Win_AddMessageHook(void *param_1); /* 0x004ac160 */
undefined4 Win_RemoveMessageHook(void *param_1); /* 0x004ac1a0 */
undefined4 Win_CreateMainWindow(uint param_1,undefined4 param_2,int param_3); /* 0x004ac1f0 */
undefined * __stdcall Win_KernelWndProc(int a1,int a2,int a3,int a4); /* 0x004ac340 */
int __cdecl Win_IsFocusWithin(void *hwnd); /* 0x004bff70 */

/* ===== debuglog.c ===== */
void __cdecl grimdemo_EnableDebugging(int enable); /* 0x00401040 */
undefined4 DebugLog_Load(void); /* 0x004020a0 */
char * grimdemo_MessagePrint(char *param_1); /* 0x00402330 */
char * grimdemo_StatusPrint(char *param_1); /* 0x004023a0 */
char * grimdemo_ErrorPrint(char *param_1); /* 0x00402410 */
char * grimdemo_WarningPrint(char *param_1); /* 0x00402480 */
char * grimdemo_DebugPrint(char *param_1); /* 0x004024f0 */
void DebugLog_Write(char *param_1,undefined4 param_2); /* 0x00402560 */

/* ===== grim.c ===== */
int __cdecl Grim_FindDataOnDrives(char *subdir); /* 0x00401140 */
undefined4 Main_Startup(char *param_1); /* 0x004012b0 */
void __cdecl Grim_DecodeRegKeyName(char *s); /* 0x00401640 */
int Grim_FatalMessageBox(int param_1,int param_2,int param_3,int param_4); /* 0x004018b0 */
void Grim_ShutdownDisplay(void); /* 0x00401900 */
void Main_Shutdown(void); /* 0x00401950 */
void Grim_EnumDisplayModes(void); /* 0x00401a50 */
void grimdemo_PleaseShutdown(void); /* 0x00402050 */
undefined4 grimdemo_SetPalette(void *param_1,int param_2); /* 0x00402060 */
int __cdecl Grim_ParseCommandLine(char *cmdline); /* 0x00402c80 */
void Grim_OpenRegistry(void); /* 0x004034b0 */
void Grim_ShowSplash(void); /* 0x00403520 */

/* ===== game.c ===== */
void Main_Service(void); /* 0x004016a0 */

/* ===== lua.c ===== */
void sputLua_Is3DHardwareEnabledL(void); /* 0x00401ca0 */
void Lua_SetHardwareState(void); /* 0x00401cc0 */
void Lua_GetVideoDevices(void); /* 0x00401d30 */
void Lua_SetVideoDevices(void); /* 0x00401da0 */
void Lua_Enumerate3DDevices(void); /* 0x00401e90 */
void Lua_EnumerateVideoDevices(void); /* 0x00401fb0 */
void grimlib_NextSetup(void); /* 0x00482880 */
void grimlib_PreviousSetup(void); /* 0x004828a0 */
void sputRender_ClearIris(void); /* 0x00486f50 */
void sputPrimitive_DrawLine(void); /* 0x00489840 */
void sputPrimitive_DrawPolygon(void); /* 0x00489a80 */
void sputPrimitive_DrawRectangle(void); /* 0x00489d70 */
void sputPrimitive_ChangePrimitive(void); /* 0x00489fe0 */
void __cdecl sputPrimitive_KillPrimitive(void); /* 0x0048a460 */
void sputPrimitive_PurgeQueue(void); /* 0x0048a4a0 */
void sputText_SetOffscreenTextPosL(void); /* 0x0048ad60 */
void sputText_SetEmergencyFontL(void); /* 0x0048ade0 */
void sputText_LocalizeStringL(void); /* 0x0048ae60 */
void sputText_MakeColorL(void); /* 0x0048aed0 */
void sputText_GetColorComponentsL(void); /* 0x0048b100 */
void sputText_SetActorTalkColorL(void); /* 0x0048b190 */
void sputText_GetActorTalkColorL(void); /* 0x0048b230 */
void sputText_SetSayLineDefaultsL(void); /* 0x0048b2a0 */
void sputText_SayLineL(void); /* 0x0048b4c0 */
void Lua_ParseSayLineTable (int param_1,int *param_2,int *param_3,int *param_4,int *param_5,int *param_6); /* 0x0048b6a0 */
void sputText_PrintLineL(void); /* 0x0048b830 */
void sputText_IsMessageGoingL(void); /* 0x0048b9a0 */
void sputText_ExpireTextQueueL(void); /* 0x0048ba90 */
void sputText_PurgeTextQueueL(void); /* 0x0048baf0 */
void sputText_KillTextObjectL(void); /* 0x0048bb20 */
void sputText_GetFontDimensionsL(void); /* 0x0048bb70 */
void sputText_GetTextObjectDimensionsL(void); /* 0x0048bbc0 */
void sputText_GetTextCharPositionL(void); /* 0x0048bc50 */
void sputText_ChangeTextObjectL(void); /* 0x0048bd10 */
void sputText_MakeTextObjectL(void); /* 0x0048be30 */
void sputText_BlastText(void); /* 0x0048bf50 */
void sputText_GetTranslationModeL(void); /* 0x0048c960 */
void sputText_SetTranslationModeL(void); /* 0x0048c980 */
void sputCostume_GetKeyLengthL(void); /* 0x00495850 */
void sputCostume_GetSmushLengthL(void); /* 0x00495900 */
void Lua_Stub(void); /* 0x00497830 */
void sputLua_GetMemoryUsageL(void); /* 0x00498d80 */
void sputLua_GetDiskFreeSpaceL(void); /* 0x00498da0 */
void __cdecl sputLua_Test(void); /* 0x00498e20 */
void __cdecl sputLua_ShrinkBoxes(void); /* 0x00498e50 */
void sputLua_UnShrinkBoxes(void); /* 0x00498e90 */
void __cdecl sputLua_GetShrinkPosition(void); /* 0x00498ea0 */
void sputLua_SetSoundParametersL(void); /* 0x00499000 */
void sputLua_GetSoundParametersL(void); /* 0x004991c0 */
void sputLua_SetDebugToggleCallback(uint param_1); /* 0x00499250 */
void sputLua_EnginePause(void); /* 0x00499260 */
void sputLua_EngineResume(void); /* 0x00499270 */
void sputLua_EngineDisplay(void); /* 0x00499280 */
void sputLua_AllocateActorL(void); /* 0x004992b0 */
void sputLua_PutActorAtInterestL(void); /* 0x004992d0 */
void sputLua_SetSelectedActorL(void); /* 0x00499360 */
void sputLua_PutActorAtL(void); /* 0x004993c0 */
void sputLua_PutActorInSetL(void); /* 0x004994a0 */
void sputLua_WalkActorVectorL(void); /* 0x00499590 */
void sputLua_WalkActorForwardL(void); /* 0x00499800 */
void sputLua_WalkActorToL(void); /* 0x00499860 */
void sputLua_WalkActorToAvoidingL(void); /* 0x004999d0 */
void sputLua_IsActorMovingL(void); /* 0x00499b80 */
void sputLua_IsActorTurningL(void); /* 0x00499be0 */
void sputLua_SetActorChoreLoopingL(void); /* 0x00499c70 */
void sputLua_IsActorRestingL(void); /* 0x00499da0 */
void sputLua_IsActorChoringL(void); /* 0x00499e20 */
void sputLua_GetActorChoresL(void); /* 0x00499ff0 */
void sputLua_GetActorCostumeDepthL(void); /* 0x0049a160 */
void sputLua_GetActorLoopingChoresL(void); /* 0x0049a2a0 */
void sputLua_SetActorColormapL(void); /* 0x0049a410 */
void sputLua_SetActorCostumeL(void); /* 0x0049a500 */
void sputLua_PrintActorCostumesL(void); /* 0x0049a5e0 */
void sputLua_PushActorCostumeL(void); /* 0x0049a640 */
void sputLua_PopActorCostumeL(void); /* 0x0049a6c0 */
void sputLua_StopActorChoreL(void); /* 0x0049a750 */
void sputLua_PlayActorChoreL(void); /* 0x0049a830 */
void sputLua_CompleteActorChoreL(void); /* 0x0049a910 */
void sputLua_PlayActorChoreLoopingL(void); /* 0x0049a9e0 */
void sputLua_ActorLookAtL(void); /* 0x0049aac0 */
void sputLua_IsActorLookingL(void); /* 0x0049ad30 */
void sputLua_SetActorLookRate(void); /* 0x0049ad90 */
void sputLua_GetActorLookRate(void); /* 0x0049ae10 */
void sputLua_SetActorVisibilityL(void); /* 0x0049ae80 */
void sputLua_SetActorFollowBoxesL(void); /* 0x0049af00 */
void sputLua_ShutUpActorL(void); /* 0x0049af80 */
void sputLua_SetActorFrustrumCull(void); /* 0x0049afd0 */
void sputLua_GetCameraActorL(void); /* 0x0049b040 */
void sputLua_GetActorWalkRateL(void); /* 0x0049b060 */
void sputLua_SetActorWalkRateL(void); /* 0x0049b0d0 */
void sputLua_GetActorTurnRateL(void); /* 0x0049b160 */
void sputLua_SetActorTurnRateL(void); /* 0x0049b1d0 */
void sputLua_SetActorWalkChoresL(void); /* 0x0049b280 */
void sputLua_SetActorTurnChoresL(void); /* 0x0049b350 */
void sputLua_SetActorRestChoreL(void); /* 0x0049b430 */
void sputLua_SetActorMumbleChoreL(void); /* 0x0049b500 */
void sputLua_SetActorTalkChoreL(void); /* 0x0049b5a0 */
void sputLua_SetActorHeadL(void); /* 0x0049b6c0 */
void sputLua_CanActorSeeL(void); /* 0x0049b830 */
void sputLua_GetVisibleThingsL(void); /* 0x0049b9e0 */
void sputLua_GetActorRectL(void); /* 0x0049bb10 */
void sputLua_GetActorPuckVectorL(void); /* 0x0049bba0 */
void sputLua_GetActorYawToPoint(void); /* 0x0049bcc0 */
void sputLua_SetActorReflection(void); /* 0x0049be40 */
void sputLua_GetActorPosL(void); /* 0x0049bec0 */
void sputLua_GetActorRotL(void); /* 0x0049bf30 */
void sputLua_SetActorRotL(void); /* 0x0049bfa0 */
void sputLua_SetActorPitch(void); /* 0x0049c0a0 */
void sputLua_SetActorRoll(void); /* 0x0049c110 */
void sputLua_TurnActorL(void); /* 0x0049c180 */
void sputLua_GetActorSectorL(void); /* 0x0049c200 */
void sputLua_IsActorInSector(void); /* 0x0049c2c0 */
void sputLua_IsPointInSector(void); /* 0x0049c4c0 */
int sputLua_FindSystemFiles(void); /* 0x0049c5e0 */
int __cdecl sputLua_Boot(int flag,char *str); /* 0x0049c600 */
void __cdecl sputLua_CameraChange(int fromSetup,int toSetup); /* 0x0049c660 */
void __cdecl sputLua_PostCameraChange(int setup); /* 0x0049c6e0 */
void sputLua_RegisterFunctions(int *param_1,int param_2); /* 0x0049ca60 */
void sputLua_JustLoadedL(void); /* 0x0049ca80 */
void sputLua_ActorVoiceIs3DL(void); /* 0x0049caa0 */
int __cdecl FindCostumeInStack(void *luaObj,CostumeNode *costumeList,CostumeNode **outCostume); /* 0x0049cb10 */
void sputLua_CheckForFileL(void); /* 0x0049cca0 */
void sputLua_NukeResourcesL(void); /* 0x0049cd10 */
void sputLua_DetachFromResourcesL(void); /* 0x0049cd40 */
void sputLua_AttachToResourcesL(void); /* 0x0049cd50 */
void sputLua_SearchForFileOrSwapCDsL(void); /* 0x0049cd60 */
void sputLua_LoadL(void); /* 0x0049cea0 */
void sputLua_SaveL(void); /* 0x0049cef0 */
void sputLua_EnableDebugKeysL(void); /* 0x0049cf40 */
void sputLua_WorldToScreenL(void); /* 0x0049cf60 */
void sputLua_ScreenToWorldL(void); /* 0x0049d030 */
void sputLua_ConcatFallback(void); /* 0x0049d220 */
void sputLua_ExitL(void); /* 0x0049d3a0 */
void sputLua_EnableControlL(void); /* 0x0049d3f0 */
void sputLua_DisableControlL(void); /* 0x0049d430 */
void sputLua_GetControlStateL(void); /* 0x0049d470 */
void __cdecl sputLua_DoCostumeOverrideCallback(void *actor,int flag); /* 0x0049d550 */
void __cdecl sputLua_DoCostumeMarkerCallback(void *actor,uint marker); /* 0x0049d670 */
void sputLua_DoUserPaintCallback(void); /* 0x0049d7b0 */
uint sputLua_DoExitCallback(void); /* 0x0049d890 */
uint sputLua_DoPauseCallback(void); /* 0x0049d970 */
int __cdecl sputLua_DoCharacterCallback(int ch); /* 0x0049da50 */
void sputLua_MakeCurrentSetupL(void); /* 0x0049db70 */
void sputLua_GetCurrentSetupL(void); /* 0x0049dbb0 */
void sputLua_MakeCurrentSetL(void); /* 0x0049dc70 */
void sputLua_LockSet(void); /* 0x0049dcb0 */
void sputLua_UnLockSet(void); /* 0x0049dd10 */
void sputLua_MessagePrintL(void); /* 0x0049dd70 */
void Lua_Print_NoOp(void); /* 0x0049ddd0 */
undefined4 sputLua_Startup(void); /* 0x0049de00 */
uint sputLua_SaveIndirector(int param_1,uint param_2); /* 0x0049dfa0 */
TextObject * sputLua_RestoreIndirector(int param_1,TextObject *param_2); /* 0x0049e020 */
undefined4 sputLua_NotifyControlHandlers(void); /* 0x0049e0b0 */
uint Lua_CreateSystemTable(void); /* 0x0049e380 */
void Lua_CreateControlsTable(uint param_1); /* 0x0049e460 */
void sputLua_SetSoundPosition(void); /* 0x0049e590 */
void sputLua_StartFullScreenMovieL(void); /* 0x0049e7e0 */
void sputLua_PauseMovieL(void); /* 0x0049e860 */
void sputLua_IsMoviePlayingL(void); /* 0x0049e960 */
void __fastcall sputLua_FileFindFirst(char *param_1); /* 0x0049e980 */
void sputLua_FileFindNext(void); /* 0x0049ea20 */
void sputLua_FileFindDispose(void); /* 0x0049ea90 */
void sputLua_QueryDialog(void); /* 0x0049eab0 */
void sputLua_InputDialog(void); /* 0x0049eb60 */
void sputLua_WriteRegistryValue(void); /* 0x0049ec50 */
void sputLua_ReadRegistryValue(void); /* 0x0049ece0 */
void sputLua_GetSectorOppositeEdge(void); /* 0x0049ed90 */
void sputLua_IsSectorActiveL(void); /* 0x0049ee20 */
void sputLua_MakeSectorActiveL(void); /* 0x0049eeb0 */
void sputLua_PreRender(void); /* 0x0049ef50 */
void sputLua_GetCurrentScript(void); /* 0x0049efc0 */
void sputLua_LockFontL(void); /* 0x0049efe0 */
void sputLua_LoadCostumeL(void); /* 0x0049f040 */
void __fastcall sputLua_GetPhysicalBytes(undefined4 param_1); /* 0x0049f080 */
void sputLua_SetMemoryUsage(void); /* 0x0049f0a0 */
void sputLua_GetCameraPositionL(void); /* 0x0049f2b0 */
void sputLua_GetCameraInterestL(void); /* 0x0049f300 */
void sputLua_GetCameraFOVL(void); /* 0x0049f350 */
void sputLua_GetCameraRollL(void); /* 0x0049f380 */
void sputLua_SetCameraPositionL(void); /* 0x0049f3b0 */
void sputLua_SetCameraInterestL(void); /* 0x0049f480 */
void sputLua_SetActorScaleL(void); /* 0x0049f550 */
void sputLua_SetActorTimeScaleL(void); /* 0x0049f5d0 */
void sputLua_GetActorNodeLocationL(void); /* 0x0049f690 */
void sputLua_GetActorScaleL(void); /* 0x0049f810 */
void sputLua_GetActorTimeScaleL(void); /* 0x0049f860 */
void sputLua_SetCameraFOVL(void); /* 0x0049f8d0 */
void sputLua_SetCameraRollL(void); /* 0x0049f930 */
void sputLua_GetCameraLookVectorL(void); /* 0x0049f9b0 */
void sputLua_PointActorAtL(void); /* 0x0049fb00 */
void sputLua_TurnActorTo(void); /* 0x0049fc60 */
void sputLua_PerSecondL(void); /* 0x0049fdf0 */
void sputLua_SnapToPlane(void); /* 0x0049fe40 */
void sputLua_GetAngleBetweenVectorsL(void); /* 0x0049ff00 */
void sputLua_GetAngleBetweenActorsL(void); /* 0x004a00a0 */
void sputLua_SetAmbientLight(void); /* 0x004a0230 */
void sputLua_FindLight(void); /* 0x004a0290 */
void sputLua_TurnLightOn(void); /* 0x004a02f0 */
void sputLua_IsLightOn(void); /* 0x004a0380 */
void sputLua_SetLightType(void); /* 0x004a0400 */
void sputLua_GetLightType(void); /* 0x004a0530 */
void sputLua_SetLightPosition(void); /* 0x004a05e0 */
void sputLua_GetLightPosition(void); /* 0x004a0760 */
void sputLua_SetLightRotation(void); /* 0x004a0800 */
void sputLua_GetLightRotation(void); /* 0x004a09a0 */
void sputLua_SetLightAngles(void); /* 0x004a0a50 */
void sputLua_GetLightAngles(void); /* 0x004a0b40 */
void sputLua_PointLightAt(void); /* 0x004a0bd0 */
void sputLua_SetLightIntensity(void); /* 0x004a0da0 */
void sputLua_GetLightIntensity(void); /* 0x004a0e90 */
void __fastcall sputLua_ImGetMasterVol(undefined4 param_1); /* 0x004a13d0 */
void sputLua_ImSetMasterVol(void); /* 0x004a1400 */
void __fastcall sputLua_ImGetSfxVol(undefined4 param_1); /* 0x004a1440 */
void sputLua_ImSetSfxVol(void); /* 0x004a1470 */
void __fastcall sputLua_ImGetVoiceVol(undefined4 param_1); /* 0x004a14b0 */
void sputLua_ImSetVoiceVol(void); /* 0x004a14e0 */
void __fastcall sputLua_ImGetMusicVol(undefined4 param_1); /* 0x004a1520 */
void sputLua_ImSetMusicVol(void); /* 0x004a1550 */
void sputLua_ImSetState(void); /* 0x004a1640 */
void sputLua_ImSetCuePoint(void); /* 0x004a16d0 */
void sputLua_ImGetMemoryFootprint(void); /* 0x004a17f0 */
void sputLua_ImGetSoundCacheSize(void); /* 0x004a1820 */
void sputLua_SetGamma(void); /* 0x004a1850 */
void sputLua_SetActorWalkDominate(void); /* 0x004a1890 */
void sputLua_SetActorConstrain(void); /* 0x004a1900 */
void sputLua_RenderModeUser(void); /* 0x004a1970 */
void sputLua_DimScreen(void); /* 0x004a19f0 */
void sputLua_DimRegion(void); /* 0x004a1a00 */
void sputLua_SetSpeechMode(void); /* 0x004a1ae0 */
void sputLua_GetSpeechMode(void); /* 0x004a1b40 */
void sputLua_ActorShadow(void); /* 0x004a1b80 */
void sputLua_ActivateActorShadow(void); /* 0x004a1bf0 */
void sputLua_SetActorShadowPlane(void); /* 0x004a1c90 */
void sputLua_SetActorShadowPoint(void); /* 0x004a1d10 */
void sputLua_SetActiveShadow(void); /* 0x004a1dc0 */
void sputLua_ActorDistToShadowPlane(void); /* 0x004a1e50 */
void sputLua_AddShadowClipPlane(void); /* 0x004a1f30 */
void sputLua_SetActorShadowValid(void); /* 0x004a1fd0 */
void sputLua_KillActorShadows(void); /* 0x004a2070 */
void sputLua_SetShadowColor(void); /* 0x004a20d0 */
void sputLua_NewObjectState(void); /* 0x004a2130 */
void sputLua_FreeObjectState(void); /* 0x004a21f0 */
void sputLua_SendObjectToBack(void); /* 0x004a2240 */
void sputLua_SendObjectToFront(void); /* 0x004a22b0 */
void sputLua_SetObjectType(void); /* 0x004a2320 */
void sputLua_ActorToClean(void); /* 0x004a2380 */
void sputLua_SetActorCollisionMode(void); /* 0x004a23e0 */
void sputLua_SetActorCollisionScale(void); /* 0x004a2470 */
void sputLua_SetActorOffsetYaw(void); /* 0x004a2500 */
void sputLua_CacheRect(void); /* 0x004a2590 */
void sputLua_RestoreCacheRect(void); /* 0x004a26b0 */
void __fastcall sputLua_ResReport(undefined4 param_1); /* 0x004a26f0 */
void sputLua_HardwareAccelerated(void); /* 0x004a2720 */
void sputLua_SetActorClipActive(void); /* 0x004a2750 */
void sputLua_SetActorClipPlane(void); /* 0x004a27b0 */
void sputLua_MarkDirtyRect(void); /* 0x004a2920 */
void sputLua_FadeOutChore(void); /* 0x004a2a20 */
void sputLua_IrisDown(void); /* 0x004a2c10 */
void sputLua_IrisUp(void); /* 0x004a2c70 */
void __fastcall sputLua_IrisComplete(undefined4 param_1); /* 0x004a2cd0 */
void Lua_TextFileGetLineCount(void); /* 0x004a2d00 */
void Lua_TextFileGetLine(void); /* 0x004a2e20 */
void sputLua_ScreenShot(void); /* 0x004a2ee0 */
void sputLua_SaveScreen(void); /* 0x004a2f90 */
void sputLua_GetSaveGameImage(void); /* 0x004a2fd0 */
void sputLua_GetImage(void); /* 0x004a3040 */
void sputLua_FreeImage(void); /* 0x004a30e0 */
void sputLua_BlastImage(void); /* 0x004a3130 */
void sputLua_BlastRect(void); /* 0x004a31f0 */
void __cdecl sputLua_SaveGameCallback(void *writeFn); /* 0x004a34c0 */
void sputLua_GetSaveGameData(void); /* 0x004a3720 */
void __fastcall sputLua_GetTextSpeed(undefined4 param_1); /* 0x004a3830 */
void sputLua_SetTextSpeed(void); /* 0x004a3850 */
void sputLua_FindFileOnAnyCD(void); /* 0x004a3890 */
void sputLua_ActorPuckOrient(void); /* 0x004a3a10 */
void sputLua_GetTickCount(void); /* 0x004a3aa0 */
void sputLua_SetActorInvClipNode(void); /* 0x004a3ae0 */
void sputLua_SetWalkSystemFadeTime(void); /* 0x004a3b80 */
void Lua_LightMgrStartup(void); /* 0x004be180 */
void Lua_LightMgrSetChange(void); /* 0x004be260 */
void Lua_LightMgrShutdown(void); /* 0x004be2a0 */

/* ===== choreface.c ===== */
int __cdecl ChoreFace_Toggle(int show); /* 0x00402120 */
undefined4 FUN_00402200(void); /* 0x00402200 */
void ChoreFace_OnCommand(undefined4 param_1,int param_2); /* 0x00402290 */

/* ===== stddisplay.c ===== */
void Display_Shutdown3D(void); /* 0x00402580 */
int __cdecl Display_Select(int deviceIdx,int modeIdx,int threeDIdx); /* 0x004025b0 */
int __cdecl Display_Select3DDevice(int threeDNum); /* 0x00402860 */
undefined * Display_InitFromConfig(void); /* 0x00402930 */
int __cdecl Display_GetLastFromRegistry(uint *deviceIdx,uint *modeIdx,uint *threeDIdx); /* 0x004029b0 */
int __cdecl Display_PickDefault(int wantFullscreen,int want3D,int *deviceIdx,int *modeIdx,int *threeDIdx); /* 0x00402b60 */
void stdDisplay_BuildBitmapInfo8 (int param_1,uint param_2,int param_3,int param_4,undefined1 *param_5); /* 0x004730d0 */
void stdDisplay_BuildBitmapInfo16(int param_1,uint param_2,int param_3,int param_4); /* 0x00473180 */
undefined * __cdecl DIB_CreateSection565(uint param_1,uint param_2,int param_3,uint param_4); /* 0x004731f0 */
undefined4 Palette_SwapRedBlue(int param_1,undefined1 *param_2); /* 0x00473270 */
int stdDisplay_Startup(void); /* 0x00473a40 */
void stdDisplay_Shutdown(void); /* 0x00473b30 */
int __cdecl Display_SelectDevice(int deviceIdx); /* 0x00473c80 */
void stdDisplay_Close(void); /* 0x00474100 */
int __cdecl Display_OpenMode(uint modeIdx,void *palette,int use3D); /* 0x00474140 */
void stdDisplay_ClearMode(void); /* 0x00474310 */
void Display_SuspendForDialog(void); /* 0x00474380 */
void Display_ResumeAfterDialog(void); /* 0x004743d0 */
int stdDisplay_Update(void); /* 0x00474420 */
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
void * stdDisplay_VBufferConvertColorFormat(int *param_1,void *param_2); /* 0x00474be0 */
int stdDisplay_SetPalette(undefined4 param_1); /* 0x00474d10 */
void __cdecl stdDisplay_SetMasterPalette(void *palette); /* 0x00474d90 */
int __cdecl Palette_ApplyGamma(void *dst,void *src,int count,int gammaIdx); /* 0x00474dd0 */
int __cdecl stdDisplay_TextOut(char *text,int x,int y); /* 0x00474e40 */
uint Display_FindClosestDevice(uint *param_1); /* 0x00475000 */
uint __cdecl Display_FindClosestMode(void *wanted,void *modes,uint count); /* 0x00475090 */
int Display_CompareVideoModes(int *param_1,int *param_2); /* 0x00475140 */
int __cdecl Surface_BlitSoftware(void *dst,void *src,uint x,uint y,int *srcRect,uint flags); /* 0x004751b0 */
undefined4 Surface_BlitDDraw(int param_1,int param_2,uint param_3,uint param_4,uint *param_5,byte param_6); /* 0x004755e0 */
undefined4 Surface_BlitLockedSrc (void *param_1,int param_2,void *param_3,uint param_4,int *param_5,void *param_6); /* 0x004758a0 */
undefined4 Surface_BlitLockedDst (int param_1,void *param_2,void *param_3,uint param_4,int *param_5,void *param_6); /* 0x00475c90 */
int DDraw_Create(undefined4 param_1); /* 0x004760d0 */
void DDraw_Release(void); /* 0x00476190 */
undefined * __stdcall FUN_004761b0(int a1,int a2,int a3,int a4); /* 0x004761b0 */
undefined * __stdcall DDraw_EnumModesCallback(int a1,int a2); /* 0x00476390 */
undefined * __stdcall DDraw_EnumModesCallback320(int a1,int a2); /* 0x004765a0 */
void * DDraw_Get(void); /* 0x004767c0 */
undefined4 __cdecl DDraw_CreateSurfaces(undefined4 hwnd,int *mode,byte *palette); /* 0x004767d0 */
void DDraw_ReleaseSurfaces(void); /* 0x00476bc0 */
undefined4 DDraw_LockSurface(undefined4 *param_1); /* 0x00476bf0 */
undefined4 DDraw_UnlockSurface(undefined4 *param_1); /* 0x00476c40 */
undefined4 DDraw_Flip(void); /* 0x00476c90 */
undefined4 DDraw_FillSurface(undefined4 *param_1,uint param_2,uint *param_3); /* 0x00476cd0 */
undefined4 DDraw_SetPalette(undefined1 *param_1); /* 0x00476dc0 */
void * __cdecl DIB_CreateSurface(void *mode,void *surface,void *palette,void *hwnd); /* 0x00476e40 */
void DIB_ReleaseSurface(void); /* 0x00476ee0 */
void __cdecl std3D_SetCurrentPalette(void *palette,int flags); /* 0x00478fc0 */
void __cdecl Palette_FromFloatTable(byte *out,byte *in,int n,double gamma); /* 0x0047b610 */
void __cdecl stdColor_ColorConvertOneRow(ushort *dst,int dstFormat,ushort *src,int srcFormat,uint count); /* 0x0047b8a0 */
int stdColor_ColorConvertOnePixel(int param_1,undefined4 param_2,int param_3); /* 0x0047bbb0 */

/* ===== services.c ===== */
undefined4 __cdecl defaultStatusPrint(char *fmt,...); /* 0x004035b0 */
undefined4 defaultMessagePrint(undefined4 param_1); /* 0x004035e0 */
undefined4 defaultWarningPrint(undefined4 param_1); /* 0x00403610 */
undefined4 defaultErrorPrint(undefined4 param_1); /* 0x00403640 */
undefined4 defaultDebugPrint(undefined4 param_1); /* 0x00403670 */
void __cdecl defaultAssert(char *expr,char *file,int line); /* 0x004036a0 */
void defaultAtExit(undefined4 param_1); /* 0x004036d0 */
void * __cdecl Svc_Realloc(void *p,uint size); /* 0x004036e0 */
void * __cdecl defaultFileOpen(char *name,char *mode); /* 0x00403710 */
void defaultFileClose(undefined4 param_1); /* 0x00403730 */
int __cdecl defaultFileRead(void *file,void *buf,int size); /* 0x00403740 */
char * __cdecl defaultFileGets(void *file,char *buf,int size); /* 0x00403760 */
int __cdecl defaultFileWrite(void *file,void *buf,int size); /* 0x00403780 */
uint defaultFileEOF(int param_1); /* 0x004037a0 */
void defaultFileTell(undefined4 param_1); /* 0x004037b0 */
int __cdecl defaultFileSeek(void *file,int offset,int whence); /* 0x004037c0 */
int __cdecl defaultFileSize(char *name); /* 0x004037e0 */
void __cdecl defaultFilePrintf(void *fp,char *fmt,...); /* 0x00403830 */
void * __cdecl Svc_Malloc(uint size); /* 0x00403850 */
void __cdecl Svc_Free(void *p); /* 0x00403860 */
undefined4 defaultLockHandle(undefined4 param_1); /* 0x00403870 */
void __cdecl HostServicesInitialize(GrimServices *svc); /* 0x00403880 */
void __cdecl stdStartup(GrimServices *svc); /* 0x004733a0 */
void stdShutdown(void); /* 0x00473400 */
void stdInitServices(GrimServices *param_1); /* 0x00473420 */
undefined4 __cdecl stdPlatform_Printf(char *fmt,...); /* 0x00478000 */
void __cdecl stdPlatform_InitServices(GrimServices *svc); /* 0x00478080 */

/* ===== reg.c ===== */
void Reg_Open(void *param_1,uint param_2,char *param_3); /* 0x004038a0 */
void Reg_CacheValueNames(void); /* 0x004039a0 */
void wuRegistry_Shutdown(void); /* 0x00403b20 */
void Reg_FreeValueNames(void); /* 0x00403b30 */
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
int Str_ComparePtrs(undefined4 *param_1,undefined4 *param_2); /* 0x00403ae0 */
char * __cdecl stdFileFromPath(char *path); /* 0x004735b0 */
char * __cdecl Str_ToLower(char *s); /* 0x0047b5c0 */
char * __cdecl stdFnames_FindMedName(char *path); /* 0x0047fd20 */
char * __cdecl stdFnames_FindExt(char *path); /* 0x0047fd50 */
void Str_StripExtension(char *param_1); /* 0x0047fda0 */
void __cdecl stdFnames_CopyShortName(char *dst,int size,char *path); /* 0x0047fdc0 */
undefined * __cdecl Str_FindChar(char *param_1,int param_2); /* 0x004838c0 */
uint * String_ContainsSubstring(uint *param_1,char *param_2); /* 0x004aef70 */
byte * __cdecl FindMatch(char *str,char *pattern); /* 0x004c1c30 */
int Str_ModuleNameLength(byte *param_1); /* 0x004c1e00 */
void Str_StripNonPrintable(byte *param_1); /* 0x004c1e60 */
int Str_CompareNoCase(char *param_1,char *param_2); /* 0x004c1e90 */
int Str_CompareNoCaseN(char *param_1,char *param_2,int param_3); /* 0x004c1ee0 */

/* ===== rdroid.c ===== */
int __cdecl rdStartup(GrimServices *svc); /* 0x00404180 */
void rdShutdown(void); /* 0x004041c0 */
int __cdecl rdOpen(int flags); /* 0x004041e0 */
void rdClose(void); /* 0x00404270 */
void rdSetRenderOptions(uint param_1); /* 0x00404290 */
void rdSetGeometryMode(int param_1); /* 0x004042a0 */
void rdSetLightingMode(int param_1); /* 0x004042b0 */
void rdSetTextureMode(int param_1); /* 0x004042c0 */
void rdSetSortingMethod(int param_1); /* 0x004042d0 */
void rdSetOcclusionMethod(int param_1); /* 0x004042e0 */
void rdSetZBufferMethod(int param_1); /* 0x004042f0 */
void rdAdvanceFrame(void); /* 0x00404300 */
void rdFinishFrame(void); /* 0x00404320 */
void rdClearPreStatistics(void); /* 0x00404330 */
undefined4 rdroid_SetColormap(uint param_1); /* 0x00404350 */
void rdRaster_Startup(void); /* 0x00404b80 */

/* ===== rdcolormap.c ===== */
undefined4 rdColormap_SetCurrent(uint param_1); /* 0x00404380 */
void * __cdecl rdColormap_Load(char *name); /* 0x004043c0 */
int __cdecl rdColormap_LoadEntry(char *name,void *cmp); /* 0x00404420 */
void rdColormap_Free(undefined4 param_1); /* 0x00404730 */
void rdColormap_FreeEntry(int param_1); /* 0x00404750 */
undefined8 __cdecl rdColormap_BuildRGB16 (undefined2 *param_1,ushort *param_2,uint param_3,uint param_4,uint param_5,int param_6); /* 0x004047e0 */
undefined4 rdColormap_BuildGrayRamp(undefined4 *param_1); /* 0x00404a40 */
int rdColormap_Size(int param_1); /* 0x00404b30 */

/* ===== rdcanvas.c ===== */
void rdActive_AdvanceFrame(void); /* 0x00404c00 */
void rdActive_ClearFrameCounters(void); /* 0x00404ca0 */
void rdActive_DrawScene(void); /* 0x00404cb0 */
void rdActive_BuildSpans(void); /* 0x00404e00 */
void rdActive_FlushSpans(void); /* 0x004055d0 */
void rdActive_BuildEdges(void); /* 0x00405620 */
undefined4 rdActive_AddActiveFace(byte *param_1); /* 0x00405770 */
void __cdecl rdCanvas_DrawLine(void *canvas,int x0,int y0,int x1,int y1,ushort color,uint pattern); /* 0x00451950 */
void rdCanvas_DrawPoint(void *param_1,int param_2,int param_3,undefined4 param_4,float param_5, int param_6,int param_7); /* 0x00451dd0 */
uint * rdCanvas_New(uint param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6, uint param_7,uint param_8); /* 0x004c04f0 */
int __cdecl rdCanvas_NewEntry(uint *canvas,uint flags,uint surface,uint zSurface,uint x0,uint y0,uint x1,uint y1 ,uint extra); /* 0x004c0550 */
void rdCanvas_Free(int param_1); /* 0x004c0610 */

/* ===== rdcache.c ===== */
void rdCache_AdvanceFrame(void); /* 0x00406650 */
void rdCache_FinishFrame(void); /* 0x00406660 */
void rdCache_Reset(void); /* 0x00406670 */
void rdCache_ClearFrameCounters(void); /* 0x00406690 */
undefined1 * rdCache_GetProcEntry(void); /* 0x004066a0 */
void rdCache_Flush(void); /* 0x00406770 */
int __cdecl rdCache_AddProcFace(void *mesh,uint vertexCount,byte flags); /* 0x00406860 */
undefined4 rdCache_SendFaceListToHardware(void); /* 0x00406aa0 */
void std3D_ResetRenderList(void); /* 0x00407ed0 */
void rdCache_DrawRenderList(void); /* 0x00407ef0 */
int rdCache_TriCompare(int param_1,int param_2); /* 0x00407f90 */
int __cdecl rdCache_DrawFaceN(void *mesh); /* 0x00407fd0 */
undefined4 FUN_00408800(void); /* 0x00408800 */
int __cdecl rdCache_DrawFaceZ(void *mesh); /* 0x00408af0 */

/* ===== rdmodel.c ===== */
undefined4 rdCache_DrawFaceUser(byte *param_1); /* 0x00409580 */
undefined4 rdCache_ProcFaceCompare(int param_1,int param_2); /* 0x00409d20 */
void rdModel3_DrawHNode(int param_1); /* 0x0040d140 */
void __cdecl rdModel3_DrawMeshImpl(void *mesh,float *matrix); /* 0x0040d230 */
undefined4 rdModel3_DrawFace(int param_1,int param_2); /* 0x0040d880 */

/* ===== rdprimit3.c ===== */
void * __cdecl rdCache_InsertFace(float *verts,int count,void *material); /* 0x00409d50 */
undefined4 __cdecl rdPrimit3_DrawLine(float *a,float *b,int *outA,int *outB,int *clipA,int *clipB,uint color, uint pattern); /* 0x0040dcc0 */
void __cdecl rdPrimit3_DrawPoint(float *world,float radius,uint a3,uint a4,uint a5); /* 0x0040dde0 */
void rdPrimit3_ClipFace(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4, uint *param_5,undefined4 *param_6,float *param_7); /* 0x0040deb0 */
void rdPrimit3_NoClipFace (undefined4 param_1,int param_2,undefined4 param_3,uint *param_4,uint *param_5, float *param_6); /* 0x0040e500 */

/* ===== rdcamera.c ===== */
void * __cdecl rdCamera_New(float fov,int type,float aspectX,float aspectY,float zoom); /* 0x00409f50 */
int __cdecl rdCamera_NewEntry(void *camera,float fov,int projType,float aspectX,float aspectY,float zoom); /* 0x00409fb0 */
void rdCamera_Free(int param_1); /* 0x0040a080 */
void rdCamera_FreeEntry(int param_1); /* 0x0040a0a0 */
void __cdecl rdCamera_SetCanvas(void *camera,void *canvas); /* 0x0040a0c0 */
undefined4 rdCamera_SetCurrent(void *param_1); /* 0x0040a0e0 */
void __cdecl rdCamera_SetFOV(void *camera,float fov); /* 0x0040a100 */
int __cdecl rdCamera_SetProjectType(void *camera,int type); /* 0x0040a150 */
void __cdecl rdCamera_SetAspectRatio(void *camera,float zoom); /* 0x0040a1d0 */
undefined4 rdCamera_BuildFOV(int *param_1); /* 0x0040a280 */
void __cdecl rdCamera_Update(float *frame); /* 0x0040a430 */
void rdCamera_OrthoProject(float *param_1,float *param_2); /* 0x0040a470 */
void rdCamera_OrthoProjectLst(float *param_1,float *param_2,int param_3); /* 0x0040a4b0 */
void rdCamera_OrthoProjectSquare(float *param_1,float *param_2); /* 0x0040a530 */
void rdCamera_OrthoProjectSquareLst(float *param_1,float *param_2,int param_3); /* 0x0040a570 */
void rdCamera_PerspProject(float *param_1,float *param_2); /* 0x0040a5e0 */
void rdCamera_PerspProjectLst(float *param_1,float *param_2,int param_3); /* 0x0040a620 */
void rdCamera_PerspProjectSquare(float *param_1,float *param_2); /* 0x0040a6a0 */
void rdCamera_PerspProjectSquareLst(float *param_1,float *param_2,int param_3); /* 0x0040a6e0 */
void __cdecl rdCamera_SetAmbientLight(void *camera,float ambient); /* 0x0040a750 */
void __cdecl rdCamera_AddLight(void *camera,void *light,float *pos); /* 0x0040a760 */
void rdCamera_AdvanceFrame(void); /* 0x0040a7d0 */
void rdModel3_ClearFrameCounters(void); /* 0x0040a860 */
int __cdecl rdPrimit3_GetScreenCoord(float *world,float *outScreen); /* 0x0040dc30 */

/* ===== renderer.c ===== */
void rdModel3_ActivateClipPlane(uint param_1); /* 0x0040a870 */
void rdModel3_SetClipPlane(undefined4 *param_1,undefined4 *param_2); /* 0x0040a880 */

/* ===== rdmodel3.c ===== */
void rdModel3_NewEntry(undefined4 *param_1); /* 0x0040a8c0 */
undefined4 * rdModel3_Load(undefined4 param_1); /* 0x0040a8f0 */
undefined4 rdModel3_LoadEntry(int param_1,undefined4 param_2); /* 0x0040a980 */
undefined4 rdModel3_LoadEntryText (undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,uint param_5, uint param_6,uint param_7,uint param_8); /* 0x0040aa20 */
undefined4 rdModel3_LoadEntryBinary(int param_1,int param_2); /* 0x0040b8e0 */
void rdModel3_LoadPostProcess(undefined4 param_1); /* 0x0040c090 */
void rdModel3_Free(int param_1); /* 0x0040c0d0 */
void rdModel3_FreeEntry(int param_1); /* 0x0040c100 */
void rdModel3_BuildShadowModel(int param_1); /* 0x0040c280 */
void rdModel3_CalcBoundingBoxes(uint param_1); /* 0x0040c520 */
void rdModel3_CalcModelBoundingBox(int param_1,int param_2,float *param_3); /* 0x0040c710 */
void rdModel3_CalcRadii(int param_1); /* 0x0040c8c0 */
void rdModel3_BuildExpandedRadius(int param_1,int param_2,float *param_3); /* 0x0040c970 */
void rdModel3_CalcFaceNormals(uint param_1); /* 0x0040cad0 */
void rdModel3_CalcVertexNormals(int param_1); /* 0x0040cc30 */
void rdModel3_CountNodeChildren(int param_1); /* 0x0040ce90 */

/* ===== rdpuppet.c ===== */
void __cdecl rdPuppet_BuildJointMatrices(void *model,float *frame,uint index,float *out); /* 0x0040cee0 */
undefined4 * rdPuppet_New(void *param_1); /* 0x00450500 */
int __cdecl rdPuppet_NewEntry(void *puppet,void *thing); /* 0x00450560 */
uint __cdecl rdPuppet_AddTrack(void *puppet,uint keyframe,uint lowPri,uint highPri); /* 0x004505a0 */
void __cdecl rdPuppet_RemoveTrack(void *puppet,int track); /* 0x00450640 */
undefined4 rdPuppet_SetStatus(int param_1,int param_2,uint param_3); /* 0x004506a0 */
void rdPuppet_SetCallback(int param_1,int param_2,undefined4 param_3); /* 0x004506d0 */
undefined4 rdPuppet_PlayTrack(int param_1,int param_2); /* 0x004506f0 */
int __cdecl rdPuppet_FadeInTrack(void *puppet,int track,float seconds); /* 0x00450720 */
int __cdecl rdPuppet_FadeOutTrack(void *puppet,int track,float seconds); /* 0x00450780 */
void __cdecl rdPuppet_AdvanceTrack(void *puppet,int track,float dt); /* 0x004507e0 */
void __cdecl rdPuppet_UpdateTracks(void *puppet,float seconds); /* 0x00450a90 */
void rdPuppet_ResetTrack(int param_1,int param_2); /* 0x00450b50 */
void __cdecl rdPuppet_UpdateFrame(void *model,float *frame); /* 0x00450ba0 */
void rdKeyframe_NewEntry(undefined4 *param_1); /* 0x004c0630 */
int rdKeyframe_Load(char *param_1); /* 0x004c0660 */
undefined4 rdKeyframe_LoadEntry(char *param_1,int param_2); /* 0x004c0770 */
undefined4 rdKeyframe_LoadEntryBinary(undefined4 param_1,int param_2); /* 0x004c0ce0 */
void rdKeyframe_Free(int param_1); /* 0x004c0e40 */
void rdKeyframe_FreeEntry(int param_1); /* 0x004c0e70 */

/* ===== rdthing.c ===== */
int __cdecl rdModel3_Draw(void *thing,float *position); /* 0x0040cf20 */
uint rdThing_New(undefined4 param_1); /* 0x00471a40 */
undefined4 rdThing_NewEntry(undefined4 *param_1,undefined4 param_2); /* 0x00471a80 */
void rdThing_Free(int param_1); /* 0x00471af0 */
void rdThing_FreeEntry(int *param_1); /* 0x00471b10 */
void __cdecl rdThing_SetModel3(void *thing,void *model); /* 0x00471bd0 */
undefined4 rdThing_SetCamera(undefined4 *param_1,undefined4 param_2); /* 0x00471d40 */
undefined4 rdThing_SetPolyline(undefined4 *param_1,undefined4 param_2); /* 0x00471d60 */
int __cdecl rdThing_Draw(void *thing,float *frame); /* 0x00471d80 */
void rdThing_AccumulateMatrices(int param_1,int param_2,float *param_3); /* 0x00471e00 */

/* ===== rdraster.c ===== */
void rdAFRaster_CalcAffineGradients(float *param_1,int param_2); /* 0x0040ea50 */
void rdAFRaster_CalcPerspGradients(float *param_1,int param_2); /* 0x0040ef90 */
void rdAFRaster_SetupNGonLW(float *param_1,int param_2); /* 0x0040f5f0 */
void rdAFRaster_DrawNGonLW(int *param_1); /* 0x0040f650 */
void rdAFRaster_DrawSpanNGonLW_8(int *param_1); /* 0x0040f6d0 */
void rdAFRaster_DrawSpanNGonLW_16(int *param_1); /* 0x0040f710 */
void rdRaster_EdgeStepFlat(int param_1); /* 0x0040f750 */
undefined4 rdAFRaster_SetupEdgeNGonLW(undefined4 *param_1,int *param_2,int param_3,int param_4); /* 0x0040f770 */
void rdAFRaster_SetupNGonLS(float *param_1,int param_2); /* 0x0040fa20 */
void rdAFRaster_DrawNGonLS(int *param_1); /* 0x0040fa80 */
undefined4 rdAFRaster_SetupEdgeNGonLS(undefined4 *param_1,int *param_2,int param_3,int param_4); /* 0x0040fbe0 */
void rdAFRaster_SetupNGonFS(float *param_1,int param_2,float param_3); /* 0x0040fe90 */
void rdAFRaster_DrawNGonFS(int param_1); /* 0x0040ff20 */
undefined4 rdAFRaster_SetupEdgeNGonFS(undefined4 *param_1,int *param_2,int param_3,int param_4); /* 0x0040ffe0 */
void rdAFRaster_SetupNGonGS(float *param_1,int param_2); /* 0x00410290 */
void rdAFRaster_DrawNGonGS(int param_1); /* 0x00410330 */
void FUN_004104b0(int param_1); /* 0x004104b0 */
undefined4 rdAFRaster_SetupEdgeNGonGS(undefined4 *param_1,int *param_2,int param_3,int param_4); /* 0x004104e0 */
void rdAFRaster_SetupNGonLAT(int *param_1,int param_2); /* 0x004108b0 */
void rdAFRaster_DrawNGonLAT(int param_1); /* 0x00410970 */
undefined4 rdAFRaster_SetupEdgeNGonLAT(undefined4 *param_1,int *param_2,int param_3,int param_4); /* 0x00410d80 */
void rdAFRaster_SetupNGonMLAT(int *param_1,int param_2); /* 0x00411270 */
void rdAFRaster_DrawNGonMLAT(int param_1); /* 0x00411330 */
void rdAFRaster_DrawSpanNGonMLAT_8(int *param_1); /* 0x004113e0 */
void rdAFRaster_DrawSpanNGonMLAT_16(int *param_1); /* 0x004114f0 */
void rdAFRaster_SetupNGonFAT(int *param_1,int param_2,float param_3); /* 0x00411630 */
void rdAFRaster_DrawNGonFAT(int param_1); /* 0x00411740 */
void FUN_00411b70(int param_1); /* 0x00411b70 */
undefined4 rdAFRaster_SetupEdgeNGonFAT(undefined4 *param_1,int *param_2,int param_3,int param_4); /* 0x00411ba0 */
void rdAFRaster_SetupNGonMFAT(int *param_1,int param_2,float param_3); /* 0x00412090 */
void rdAFRaster_DrawNGonMFAT(int param_1); /* 0x004121a0 */
void rdAFRaster_DrawSpanNGonMFAT_8(int *param_1); /* 0x00412280 */
void rdAFRaster_DrawSpanNGonMFAT_16(int *param_1); /* 0x004123b0 */
void rdAFRaster_SetupNGonGAT(int *param_1,int param_2); /* 0x004124f0 */
void rdAFRaster_DrawNGonGAT(int param_1); /* 0x004125c0 */
void FUN_004129f0(int param_1); /* 0x004129f0 */
undefined4 rdAFRaster_SetupEdgeNGonGAT(undefined4 *param_1,int *param_2,int param_3,int param_4); /* 0x00412a30 */
void rdAFRaster_SetupNGonMGAT(int *param_1,int param_2); /* 0x00413040 */
void rdAFRaster_DrawNGonMGAT(int param_1); /* 0x00413110 */
void rdAFRaster_DrawSpanNGonMGAT_8(int *param_1); /* 0x004131f0 */
void rdAFRaster_DrawSpanNGonMGAT_16(int *param_1); /* 0x00413340 */
void rdAFRaster_SetupNGonLIT(int *param_1,int param_2); /* 0x004134a0 */
void rdAFRaster_DrawNGonLIT(int param_1); /* 0x00413590 */
undefined4 rdAFRaster_SetupEdgeNGonLIT(undefined4 *param_1,int *param_2,int param_3,int param_4); /* 0x004139f0 */
void rdAFRaster_SetupNGonMLIT(int *param_1,int param_2); /* 0x00413ce0 */
void rdAFRaster_DrawNGonMLIT(int param_1); /* 0x00413dd0 */
void rdAFRaster_DrawSpanNGonMLIT_8(uint *param_1); /* 0x00413ee0 */
void rdAFRaster_DrawSpanNGonMLIT_16(uint *param_1); /* 0x00414530 */
void rdAFRaster_SetupNGonFIT(int *param_1,int param_2,float param_3); /* 0x00414be0 */
void rdAFRaster_DrawNGonFIT(int param_1); /* 0x00414d20 */
void FUN_00415180(int param_1); /* 0x00415180 */
void FUN_004151c0(int param_1); /* 0x004151c0 */
undefined4 rdAFRaster_SetupEdgeNGonFIT(undefined4 *param_1,int *param_2,int param_3,int param_4); /* 0x004151d0 */
void rdAFRaster_SetupNGonMFIT(int *param_1,int param_2,float param_3); /* 0x004154c0 */
void rdAFRaster_DrawNGonMFIT(int param_1); /* 0x00415600 */
void rdAFRaster_DrawSpanNGonMFIT_8(uint *param_1); /* 0x00415720 */
void rdAFRaster_DrawSpanNGonMFIT_16(uint *param_1); /* 0x00415dc0 */
void rdAFRaster_SetupNGonGIT(int *param_1,int param_2); /* 0x00416470 */
void rdAFRaster_DrawNGonGIT(int param_1); /* 0x00416580 */
void rdAFRaster_AdvanceLeftEdgeNGonGIT(int param_1); /* 0x004169f0 */
void rdAFRaster_AdvanceRightEdgeNGonGIT(int param_1); /* 0x00416a30 */
undefined4 rdAFRaster_SetupEdgeNGonGIT(undefined4 *param_1,int *param_2,int param_3,int param_4); /* 0x00416a50 */
undefined4 rdAFRaster_SetupNGonMGIT(int *param_1,int param_2); /* 0x00416e70 */
void rdAFRaster_DrawNGonMGIT(int param_1); /* 0x00416f80 */
void rdAFRaster_DrawSpanNGonMGIT_8(uint *param_1); /* 0x004170a0 */
void rdAFRaster_DrawSpanNGonMGIT_16(uint *param_1); /* 0x00417790 */
void rdNRaster_CalcAffineGradients(float param_1); /* 0x00418550 */
void rdNRaster_CalcPerspGradients(float param_1); /* 0x00418a00 */
void rdNRaster_DrawNGonLV(int param_1,int param_2); /* 0x00418fe0 */
void rdNRaster_DrawNGonLW(int param_1,int param_2); /* 0x00419150 */
void rdNRaster_DrawNGonLS(int param_1,int param_2); /* 0x00419450 */
void rdNRaster_DrawScanLineNGonLS_16(uint *param_1,uint *param_2); /* 0x004195f0 */
undefined4 rdNRaster_SetupLeftEdgeNGonLS(int *param_1); /* 0x00419680 */
undefined4 rdNRaster_SetupRightEdgeNGonLS(int *param_1); /* 0x00419840 */
void rdNRaster_DrawNGonTLS(int param_1,int param_2); /* 0x00419a00 */
void rdNRaster_DrawScanLineNGonTLS_16(uint *param_1,uint *param_2); /* 0x00419be0 */
void rdNRaster_DrawNGonFS(int param_1,int param_2,float param_3); /* 0x00419ca0 */
void rdRaster_Span_Flat(uint *param_1,uint *param_2); /* 0x00419e60 */
void rdNRaster_DrawScanLineNGonFS_16(uint *param_1,uint *param_2); /* 0x00419ee0 */
undefined4 rdNRaster_SetupLeftEdgeNGonFS(int *param_1); /* 0x00419f70 */
undefined4 rdNRaster_SetupRightEdgeNGonFS(int *param_1); /* 0x0041a130 */
void rdNRaster_DrawNGonTFS(int param_1,int param_2,float param_3); /* 0x0041a2f0 */
void rdRaster_Span_Tex(uint *param_1,uint *param_2); /* 0x0041a4f0 */
void rdNRaster_DrawScanLineNGonTFS_16(uint *param_1,uint *param_2); /* 0x0041a580 */
void rdNRaster_DrawNGonGS(int param_1,int param_2); /* 0x0041a640 */
void rdNRaster_DrawScanLineNGonGS_8(uint *param_1,uint *param_2); /* 0x0041a810 */
void rdNRaster_DrawScanLineNGonGS_16(uint *param_1,uint *param_2); /* 0x0041a900 */
undefined4 rdNRaster_SetupLeftEdgeNGonGS(int *param_1); /* 0x0041aa10 */
undefined4 rdNRaster_SetupRightEdgeNGonGS(int *param_1); /* 0x0041ac60 */
void rdNRaster_DrawNGonTGS(int param_1,int param_2); /* 0x0041aeb0 */
void rdNRaster_DrawScanLineNGonTGS_8(uint *param_1,uint *param_2); /* 0x0041b0d0 */
void rdNRaster_DrawScanLineNGonTGS_16(uint *param_1,uint *param_2); /* 0x0041b1e0 */
void rdNRaster_DrawNGonLAT(int param_1,int param_2); /* 0x0041b310 */
void rdNRaster_DrawScanLineNGonLAT_8(uint *param_1,uint *param_2); /* 0x0041b6f0 */
void rdNRaster_DrawScanLineNGonLAT_16(uint *param_1,uint *param_2); /* 0x0041b880 */
undefined4 rdNRaster_SetupLeftEdgeNGonLAT(int *param_1); /* 0x0041ba30 */
undefined4 rdNRaster_SetupRightEdgeNGonLAT(int *param_1); /* 0x0041bd20 */
void rdNRaster_DrawNGonTLAT(int param_1,int param_2); /* 0x0041c010 */
void rdNRaster_DrawScanLineNGonTLAT_8(uint *param_1,uint *param_2); /* 0x0041c260 */
void rdNRaster_DrawScanLineNGonTLAT_16(uint *param_1,uint *param_2); /* 0x0041c410 */
void rdNRaster_DrawNGonMLAT(int param_1,int param_2); /* 0x0041c5e0 */
void rdNRaster_DrawScanLineNGonMLAT_8(uint *param_1,uint *param_2); /* 0x0041c810 */
void rdNRaster_DrawScanLineNGonMLAT_16(uint *param_1,uint *param_2); /* 0x0041c9b0 */
void rdNRaster_DrawNGonMTLAT(int param_1,int param_2); /* 0x0041cb80 */
void rdNRaster_DrawScanLineNGonMTLAT_8(uint *param_1,uint *param_2); /* 0x0041cdd0 */
void rdNRaster_DrawScanLineNGonMTLAT_16(uint *param_1,uint *param_2); /* 0x0041cf90 */
void rdNRaster_DrawNGonFAT(int param_1,int param_2,float param_3); /* 0x0041d180 */
void rdNRaster_DrawScanLineNGonFAT_16(uint *param_1,uint *param_2); /* 0x0041d560 */
undefined4 rdNRaster_SetupLeftEdgeNGonFAT(int *param_1); /* 0x0041d710 */
undefined4 rdNRaster_SetupRightEdgeNGonFAT(int *param_1); /* 0x0041da00 */
void rdNRaster_DrawNGonTFAT(int param_1,int param_2,float param_3); /* 0x0041dcf0 */
void rdNRaster_DrawScanLineNGonTFAT_8(uint *param_1,uint *param_2); /* 0x0041df60 */
void rdNRaster_DrawScanLineNGonTFAT_16(uint *param_1,uint *param_2); /* 0x0041e120 */
void rdNRaster_DrawNGonMFAT(int param_1,int param_2,float param_3); /* 0x0041e300 */
void rdNRaster_DrawScanLineNGonMFAT_8(uint *param_1,uint *param_2); /* 0x0041e550 */
void rdNRaster_DrawScanLineNGonMFAT_16(uint *param_1,uint *param_2); /* 0x0041e700 */
void rdNRaster_DrawNGonMTFAT(int param_1,int param_2,float param_3); /* 0x0041e8d0 */
void rdNRaster_DrawScanLineNGonMTFAT_8(uint *param_1,uint *param_2); /* 0x0041eb40 */
void rdNRaster_DrawScanLineNGonMTFAT_16(uint *param_1,uint *param_2); /* 0x0041ed10 */
void rdNRaster_DrawNGonGAT(int param_1,int param_2); /* 0x0041eef0 */
void rdNRaster_DrawScanLineNGonGAT_16(uint *param_1,uint *param_2); /* 0x0041f2f0 */
undefined4 rdNRaster_SetupLeftEdgeNGonGAT(int *param_1); /* 0x0041f520 */
undefined4 rdNRaster_SetupRightEdgeNGonGAT(int *param_1); /* 0x0041f890 */
void rdNRaster_DrawNGonTGAT(int param_1,int param_2); /* 0x0041fc00 */
void rdNRaster_DrawScanLineNGonTGAT_8(uint *param_1,uint *param_2); /* 0x0041fe90 */
void __fastcall FUN_0042003c(int param_1,int param_2); /* 0x0042003c */
void rdNRaster_DrawScanLineNGonTGAT_16(uint *param_1,uint *param_2); /* 0x004200c0 */
void rdNRaster_DrawNGonMGAT(int param_1,int param_2); /* 0x00420310 */
void rdNRaster_DrawScanLineNGonMGAT_8(uint *param_1,uint *param_2); /* 0x00420580 */
void rdNRaster_DrawScanLineNGonMGAT_16(uint *param_1,uint *param_2); /* 0x004207b0 */
void rdNRaster_DrawNGonMTGAT(int param_1,int param_2); /* 0x004209f0 */
void rdNRaster_DrawScanLineNGonMTGAT_8(uint *param_1,uint *param_2); /* 0x00420c80 */
void rdNRaster_DrawScanLineNGonMTGAT_16(uint *param_1,uint *param_2); /* 0x00420ec0 */
void rdNRaster_DrawNGonLIT(int param_1,int param_2); /* 0x00421120 */
void rdNRaster_DrawScanLineNGonLIT_16(uint *param_1,uint *param_2); /* 0x00421510 */
undefined4 rdNRaster_SetupLeftEdgeNGonLIT(int *param_1); /* 0x00421b60 */
undefined4 rdNRaster_SetupRightEdgeNGonLIT(int *param_1); /* 0x00421dc0 */
void rdNRaster_DrawNGonTLIT(int param_1,int param_2); /* 0x00421f80 */
void rdNRaster_DrawScanLineNGonTLIT_8(uint *param_1,uint *param_2); /* 0x004221f0 */
void rdNRaster_DrawScanLineNGonTLIT_16(uint *param_1,uint *param_2); /* 0x00422820 */
void rdNRaster_DrawNGonMLIT(int param_1,int param_2); /* 0x00422f00 */
void rdNRaster_DrawScanLineNGonMLIT_8(uint *param_1,uint *param_2); /* 0x00423150 */
void rdNRaster_DrawScanLineNGonMLIT_16(uint *param_1,uint *param_2); /* 0x00423740 */
void rdNRaster_DrawNGonMTLIT(int param_1,int param_2); /* 0x00423db0 */
void rdNRaster_DrawScanLineNGonMTLIT_8(uint *param_1,uint *param_2); /* 0x00424020 */
void rdNRaster_DrawScanLineNGonMTLIT_16(uint *param_1,uint *param_2); /* 0x00424670 */
void rdNRaster_DrawNGonFIT(int param_1,int param_2,float param_3); /* 0x00424d50 */
void rdNRaster_DrawScanLineNGonFIT_16(uint *param_1,uint *param_2); /* 0x00425150 */
undefined4 rdNRaster_SetupLeftEdgeNGonFIT(int *param_1); /* 0x004257a0 */
undefined4 rdNRaster_SetupRightEdgeNGonFIT(int *param_1); /* 0x00425a00 */
void rdNRaster_DrawNGonTFIT(int param_1,int param_2,float param_3); /* 0x00425bc0 */
void rdNRaster_DrawScanLineNGonTFIT_8(uint *param_1,uint *param_2); /* 0x00425e50 */
void rdNRaster_DrawScanLineNGonTFIT_16(uint *param_1,uint *param_2); /* 0x004264a0 */
void rdNRaster_DrawNGonMFIT(int param_1,int param_2,float param_3); /* 0x00426bc0 */
void rdNRaster_DrawScanLineNGonMFIT_8(uint *param_1,uint *param_2); /* 0x00426e30 */
void rdNRaster_DrawScanLineNGonMFIT_16(uint *param_1,uint *param_2); /* 0x00427470 */
void rdNRaster_DrawNGonMTFIT(int param_1,int param_2,float param_3); /* 0x00427ae0 */
void rdNRaster_DrawScanLineNGonMTFIT_8(uint *param_1,uint *param_2); /* 0x00427d70 */
void rdNRaster_DrawScanLineNGonMTFIT_16(uint *param_1,uint *param_2); /* 0x004283f0 */
void rdNRaster_DrawNGonGIT(int param_1,int param_2); /* 0x00428ae0 */
void rdNRaster_DrawScanLineNGonGIT_16(uint *param_1,uint *param_2); /* 0x00428f00 */
undefined4 rdNRaster_SetupLeftEdgeNGonGIT(int *param_1); /* 0x00429870 */
undefined4 rdNRaster_SetupRightEdgeNGonGIT(int *param_1); /* 0x00429b70 */
void rdNRaster_DrawNGonTGIT(int param_1,int param_2); /* 0x00429dc0 */
void rdNRaster_DrawScanLineNGonTGIT_8(uint *param_1,uint *param_2); /* 0x0042a070 */
void rdNRaster_DrawScanLineNGonTGIT_16(uint *param_1,uint *param_2); /* 0x0042a790 */
void rdNRaster_DrawNGonMGIT(int param_1,int param_2); /* 0x0042af60 */
void rdNRaster_DrawScanLineNGonMGIT_8(uint *param_1,uint *param_2); /* 0x0042b1f0 */
void rdNRaster_DrawScanLineNGonMGIT_16(uint *param_1,uint *param_2); /* 0x0042b8e0 */
void rdNRaster_DrawNGonMTGIT(int param_1,int param_2); /* 0x0042c010 */
void rdNRaster_DrawScanLineNGonMTGIT_8(uint *param_1,uint *param_2); /* 0x0042c2c0 */
void rdNRaster_DrawScanLineNGonMTGIT_16(uint *param_1,uint *param_2); /* 0x0042c9f0 */
void rdZRaster_CalcAffineGradients(float param_1); /* 0x0042d190 */
void rdZRaster_CalcPerspGradients(float param_1); /* 0x0042d5f0 */
void rdZRaster_DrawNGonLV(int param_1,int param_2); /* 0x0042dba0 */
void rdZRaster_DrawNGonLW(int param_1,int param_2); /* 0x0042dd10 */
void rdZRaster_DrawNGonLS(int param_1,int param_2); /* 0x0042e010 */
void rdZRaster_DrawScanLineNGonLS_8(uint *param_1,uint *param_2); /* 0x0042e200 */
void rdZRaster_DrawScanLineNGonLS_16(uint *param_1,uint *param_2); /* 0x0042e320 */
undefined4 rdZRaster_SetupLeftEdgeNGonLS(int *param_1); /* 0x0042e440 */
undefined4 rdZRaster_SetupRightEdgeNGonLS(int *param_1); /* 0x0042e630 */
void rdZRaster_DrawNGonTLS(int param_1,int param_2); /* 0x0042e820 */
void rdZRaster_DrawScanLineNGonTLS_8(uint *param_1,uint *param_2); /* 0x0042ea50 */
void rdZRaster_DrawScanLineNGonTLS_16(uint *param_1,uint *param_2); /* 0x0042eb90 */
void rdZRaster_DrawNGonFS(int param_1,int param_2,float param_3); /* 0x0042ecf0 */
void rdZRaster_DrawScanLineNGonFS_8(uint *param_1,uint *param_2); /* 0x0042ef00 */
void rdZRaster_DrawScanLineNGonFS_16(uint *param_1,uint *param_2); /* 0x0042f020 */
undefined4 rdZRaster_SetupLeftEdgeNGonFS(int *param_1); /* 0x0042f140 */
undefined4 rdZRaster_SetupRightEdgeNGonFS(int *param_1); /* 0x0042f330 */
void rdZRaster_DrawNGonTFS(int param_1,int param_2,float param_3); /* 0x0042f520 */
void rdZRaster_DrawScanLineNGonTFS_8(uint *param_1,uint *param_2); /* 0x0042f770 */
void rdZRaster_DrawScanLineNGonTFS_16(uint *param_1,uint *param_2); /* 0x0042f8b0 */
void rdZRaster_DrawNGonGS(int param_1,int param_2); /* 0x0042fa10 */
void rdZRaster_DrawScanLineNGonGS_8(uint *param_1,uint *param_2); /* 0x0042fc30 */
void rdZRaster_DrawScanLineNGonGS_16(uint *param_1,uint *param_2); /* 0x0042fdc0 */
undefined4 rdZRaster_SetupLeftEdgeNGonGS(int *param_1); /* 0x0042ff50 */
undefined4 rdZRaster_SetupRightEdgeNGonGS(int *param_1); /* 0x004301d0 */
void rdZRaster_DrawNGonTGS(int param_1,int param_2); /* 0x00430450 */
void rdZRaster_DrawScanLineNGonTGS_8(uint *param_1,uint *param_2); /* 0x004306c0 */
void rdZRaster_DrawScanLineNGonTGS_16(uint *param_1,uint *param_2); /* 0x00430860 */
void rdZRaster_DrawNGonLAT(int param_1,int param_2); /* 0x00430a20 */
void rdZRaster_DrawScanLineNGonLAT_8(uint *param_1,uint *param_2); /* 0x00430fd0 */
void rdZRaster_DrawScanLineNGonLAT_16(uint *param_1,uint *param_2); /* 0x004311d0 */
undefined4 rdZRaster_SetupLeftEdgeNGonLAT(int *param_1); /* 0x00431400 */
undefined4 rdZRaster_SetupRightEdgeNGonLAT(int *param_1); /* 0x00431710 */
void rdZRaster_DrawNGonTLAT(int param_1,int param_2); /* 0x00431a20 */
void rdZRaster_DrawScanLineNGonTLAT_8(uint *param_1,uint *param_2); /* 0x00431c90 */
void rdZRaster_DrawScanLineNGonTLAT_16(uint *param_1,uint *param_2); /* 0x00431eb0 */
void rdZRaster_DrawNGonMLAT(int param_1,int param_2); /* 0x00432100 */
void rdZRaster_DrawScanLineNGonMLAT_8(uint *param_1,uint *param_2); /* 0x00432350 */
void rdZRaster_DrawScanLineNGonMLAT_16(uint *param_1,uint *param_2); /* 0x00432560 */
void rdZRaster_DrawNGonMTLAT(int param_1,int param_2); /* 0x004327a0 */
void rdZRaster_DrawScanLineNGonMTLAT_8(uint *param_1,uint *param_2); /* 0x00432a10 */
void rdZRaster_DrawScanLineNGonMTLAT_16(uint *param_1,uint *param_2); /* 0x00432c40 */
void rdZRaster_DrawNGonFAT(int param_1,int param_2,float param_3); /* 0x00432ea0 */
void rdZRaster_DrawScanLineNGonFAT_8(uint *param_1,uint *param_2); /* 0x00433480 */
void rdZRaster_DrawScanLineNGonFAT_16(uint *param_1,uint *param_2); /* 0x004336a0 */
undefined4 rdZRaster_SetupLeftEdgeNGonFAT(int *param_1); /* 0x004338d0 */
undefined4 rdZRaster_SetupRightEdgeNGonFAT(int *param_1); /* 0x00433be0 */
void rdZRaster_DrawNGonTFAT(int param_1,int param_2,float param_3); /* 0x00433ef0 */
void rdZRaster_DrawScanLineNGonTFAT_8(uint *param_1,uint *param_2); /* 0x00434180 */
void rdZRaster_DrawScanLineNGonTFAT_16(uint *param_1,uint *param_2); /* 0x004343b0 */
void rdZRaster_DrawNGonMFAT(int param_1,int param_2,float param_3); /* 0x00434610 */
void rdZRaster_DrawScanLineNGonMFAT_8(uint *param_1,uint *param_2); /* 0x00434880 */
void rdZRaster_DrawScanLineNGonMFAT_16(uint *param_1,uint *param_2); /* 0x00434aa0 */
void rdZRaster_DrawNGonMTFAT(int param_1,int param_2,float param_3); /* 0x00434ce0 */
void rdZRaster_DrawScanLineNGonMTFAT_8(uint *param_1,uint *param_2); /* 0x00434f70 */
void rdZRaster_DrawScanLineNGonMTFAT_16(uint *param_1,uint *param_2); /* 0x004351a0 */
void rdZRaster_DrawNGonGAT(int param_1,int param_2); /* 0x00435400 */
void rdZRaster_DrawScanLineNGonGAT_8(uint *param_1,uint *param_2); /* 0x00435a00 */
void rdZRaster_DrawScanLineNGonGAT_16(uint *param_1,uint *param_2); /* 0x00435c70 */
undefined4 rdZRaster_SetupLeftEdgeNGonGAT(int *param_1); /* 0x00435f60 */
undefined4 rdZRaster_SetupRightEdgeNGonGAT(int *param_1); /* 0x00436300 */
void rdZRaster_DrawNGonTGAT(int param_1,int param_2); /* 0x004366a0 */
void rdZRaster_DrawScanLineNGonTGAT_8(uint *param_1,uint *param_2); /* 0x00436950 */
void rdZRaster_DrawScanLineNGonTGAT_16(uint *param_1,uint *param_2); /* 0x00436be0 */
void rdZRaster_DrawNGonMGAT(int param_1,int param_2); /* 0x00436e80 */
void rdZRaster_DrawScanLineNGonMGAT_8(uint *param_1,uint *param_2); /* 0x00437110 */
void rdZRaster_DrawScanLineNGonMGAT_16(uint *param_1,uint *param_2); /* 0x00437390 */
void rdZRaster_DrawNGonMTGAT(int param_1,int param_2); /* 0x00437620 */
void rdZRaster_DrawScanLineNGonMTGAT_8(uint *param_1,uint *param_2); /* 0x004378d0 */
void rdZRaster_DrawScanLineNGonMTGAT_16(uint *param_1,uint *param_2); /* 0x00437b60 */
void rdZRaster_DrawNGonLIT(int param_1,int param_2); /* 0x00437e10 */
void rdZRaster_DrawScanLineNGonLIT_8(uint *param_1,uint *param_2); /* 0x004383d0 */
void rdZRaster_DrawScanLineNGonLIT_16(uint *param_1,uint *param_2); /* 0x00438a90 */
undefined4 rdZRaster_SetupLeftEdgeNGonLIT(int *param_1); /* 0x004391a0 */
undefined4 rdZRaster_SetupRightEdgeNGonLIT(int *param_1); /* 0x00439400 */
void rdZRaster_DrawNGonTLIT(int param_1,int param_2); /* 0x004395c0 */
void rdZRaster_DrawScanLineNGonTLIT_8(uint *param_1,uint *param_2); /* 0x00439840 */
void rdZRaster_DrawScanLineNGonTLIT_16(uint *param_1,uint *param_2); /* 0x00439f50 */
void rdZRaster_DrawNGonMLIT(int param_1,int param_2); /* 0x0043a6e0 */
void rdZRaster_DrawScanLineNGonMLIT_8(uint *param_1,uint *param_2); /* 0x0043a940 */
void rdZRaster_DrawScanLineNGonMLIT_16(uint *param_1,uint *param_2); /* 0x0043b020 */
void rdZRaster_DrawNGonMTLIT(int param_1,int param_2); /* 0x0043b760 */
void rdZRaster_DrawScanLineNGonMTLIT_8(uint *param_1,uint *param_2); /* 0x0043b9e0 */
void rdZRaster_DrawScanLineNGonMTLIT_16(uint *param_1,uint *param_2); /* 0x0043c130 */
void rdZRaster_DrawNGonFIT(int param_1,int param_2,float param_3); /* 0x0043c8d0 */
void rdZRaster_DrawScanLineNGonFIT_8(uint *param_1,uint *param_2); /* 0x0043ceb0 */
void rdZRaster_DrawScanLineNGonFIT_16(uint *param_1,uint *param_2); /* 0x0043d5b0 */
undefined4 rdZRaster_SetupLeftEdgeNGonFIT(int *param_1); /* 0x0043dcc0 */
undefined4 rdZRaster_SetupRightEdgeNGonFIT(int *param_1); /* 0x0043df20 */
void rdZRaster_DrawNGonTFIT(int param_1,int param_2,float param_3); /* 0x0043e0e0 */
void rdZRaster_DrawScanLineNGonTFIT_8(uint *param_1,uint *param_2); /* 0x0043e380 */
void rdZRaster_DrawScanLineNGonTFIT_16(uint *param_1,uint *param_2); /* 0x0043eab0 */
void rdZRaster_DrawNGonMFIT(int param_1,int param_2,float param_3); /* 0x0043f280 */
void rdZRaster_DrawScanLineNGonMFIT_8(uint *param_1,uint *param_2); /* 0x0043f500 */
void rdZRaster_DrawScanLineNGonMFIT_16(uint *param_1,uint *param_2); /* 0x0043fc30 */
void rdZRaster_DrawNGonMTFIT(int param_1,int param_2,float param_3); /* 0x00440370 */
void rdZRaster_DrawScanLineNGonMTFIT_8(uint *param_1,uint *param_2); /* 0x00440610 */
void rdZRaster_DrawScanLineNGonMTFIT_16(uint *param_1,uint *param_2); /* 0x00440d80 */
void rdZRaster_DrawNGonGIT(int param_1,int param_2); /* 0x00441520 */
void rdZRaster_DrawScanLineNGonGIT_8(uint *param_1,uint *param_2); /* 0x00441b20 */
void rdZRaster_DrawScanLineNGonGIT_16(uint *param_1,uint *param_2); /* 0x004422d0 */
undefined4 rdZRaster_SetupLeftEdgeNGonGIT(int *param_1); /* 0x00442ab0 */
undefined4 rdZRaster_SetupRightEdgeNGonGIT(int *param_1); /* 0x00442db0 */
void rdZRaster_DrawNGonTGIT(int param_1,int param_2); /* 0x00443000 */
void rdZRaster_DrawScanLineNGonTGIT_8(uint *param_1,uint *param_2); /* 0x004432c0 */
void rdZRaster_DrawScanLineNGonTGIT_16(uint *param_1,uint *param_2); /* 0x00443ab0 */
void rdZRaster_DrawNGonMGIT(int param_1,int param_2); /* 0x00444320 */
void rdZRaster_DrawScanLineNGonMGIT_8(uint *param_1,uint *param_2); /* 0x004445c0 */
void rdZRaster_DrawScanLineNGonMGIT_16(uint *param_1,uint *param_2); /* 0x00444d90 */
void rdZRaster_DrawNGonMTGIT(int param_1,int param_2); /* 0x00445570 */
void rdZRaster_DrawScanLineNGonMTGIT_8(uint *param_1,uint *param_2); /* 0x00445830 */
void rdZRaster_DrawScanLineNGonMTGIT_16(uint *param_1,uint *param_2); /* 0x00446030 */
void rdRaster_SpanR_FlatZw(int *param_1); /* 0x00451fa0 */
void rdRaster_SpanR_FlatZw_2(int *param_1); /* 0x00452070 */
void rdRaster_SpanR16_Tex(int *param_1); /* 0x00452150 */
void rdRaster_SpanR16_Tex_2(int *param_1); /* 0x004522b0 */
void rdRaster_SpanR16_Tex_3(int *param_1); /* 0x004523f0 */
void rdRaster_SpanR16_Tex_4(int *param_1); /* 0x00452530 */
void rdRaster_SpanR16_TexLit(int *param_1); /* 0x00452670 */
void rdRaster_SpanR16_Tex_5(int *param_1); /* 0x004527b0 */
void rdRaster_SpanR16_Tex_6(int *param_1); /* 0x004528f0 */
void rdRaster_SpanR16_Tex_7(int *param_1); /* 0x00452a30 */
void rdRaster_SpanR16_Tex_8(int *param_1); /* 0x00452b90 */
void rdRaster_SpanR16_Tex_9(int *param_1); /* 0x00452cd0 */
void rdRaster_SpanR16_Tex_10(int *param_1); /* 0x00452e10 */
void rdRaster_SpanR16_TexLit_2(int *param_1); /* 0x00452f50 */
void rdRaster_SpanR16_Tex_11(int *param_1); /* 0x00453090 */
void rdRaster_SpanR16_Tex_12(int *param_1); /* 0x004531d0 */
void rdRaster_SpanR16_TexLit_3(int *param_1); /* 0x00453310 */
void rdRaster_SpanR16_TexLit_4(int *param_1); /* 0x004534d0 */
void rdRaster_SpanR16_TexLit_5(int *param_1); /* 0x00453660 */
void rdRaster_SpanR16_TexLit_6(int *param_1); /* 0x004537f0 */
void rdRaster_SpanR16_TexLit_7(int *param_1); /* 0x00453980 */
void rdRaster_SpanR16_TexLit_8(int *param_1); /* 0x00453b10 */
void rdRaster_SpanR16_TexLit_9(int *param_1); /* 0x00453ca0 */
void rdRaster_SpanP16_Tex(uint *param_1); /* 0x00453e30 */
void rdRaster_SpanP16_Tex_2(uint *param_1); /* 0x00454780 */
void rdRaster_SpanP16_Tex_3(uint *param_1); /* 0x00455050 */
void rdRaster_SpanP16_Tex_4(uint *param_1); /* 0x00455920 */
void rdRaster_SpanP16_TexLit(uint *param_1); /* 0x004561f0 */
void rdRaster_SpanP16_Tex_5(uint *param_1); /* 0x00456ac0 */
void rdRaster_SpanP16_Tex_6(uint *param_1); /* 0x00457390 */
void rdRaster_SpanP16_Tex_7(uint *param_1); /* 0x00457c60 */
void rdRaster_SpanP16_Tex_8(uint *param_1); /* 0x004585b0 */
void rdRaster_SpanP16_Tex_9(uint *param_1); /* 0x00458e80 */
void rdRaster_SpanP16_Tex_10(uint *param_1); /* 0x00459750 */
void rdRaster_SpanP16_TexLit_2(uint *param_1); /* 0x0045a020 */
void rdRaster_SpanP16_Tex_11(uint *param_1); /* 0x0045a8f0 */
void rdRaster_SpanP16_Tex_12(uint *param_1); /* 0x0045b1c0 */
void rdRaster_SpanP16_TexLit_3(uint *param_1); /* 0x0045ba90 */
void rdRaster_SpanP16_TexLit_4(uint *param_1); /* 0x0045c4e0 */
void rdRaster_SpanP16_TexLit_5(uint *param_1); /* 0x0045ce90 */
void rdRaster_SpanP16_TexLit_6(uint *param_1); /* 0x0045d840 */
void rdRaster_SpanP16_TexLit_7(uint *param_1); /* 0x0045e1f0 */
void rdRaster_SpanP16_TexLit_8(uint *param_1); /* 0x0045eba0 */
void rdRaster_SpanP16_TexLit_9(uint *param_1); /* 0x0045f550 */
void rdRaster_Span16_TexLitZw(uint *param_1,uint *param_2); /* 0x0045ff10 */
void rdRaster_Span16_TexLitZw_2(uint *param_1,uint *param_2); /* 0x004602c0 */
void rdRaster_Span16_TexLitZw_3(uint *param_1,uint *param_2); /* 0x00460670 */
void rdRaster_Span16_TexLitZw_4(uint *param_1,uint *param_2); /* 0x00460a20 */
void rdRaster_Span16_TexLitZw_5(uint *param_1,uint *param_2); /* 0x00460dd0 */
void rdRaster_Span16_TexLitZw_6(uint *param_1,uint *param_2); /* 0x00461180 */
void rdRaster_Span16_TexLitZw_7(uint *param_1,uint *param_2); /* 0x00461530 */
void rdRaster_Span16_TexLitZw_8(uint *param_1,uint *param_2); /* 0x004618e0 */
void rdRaster_Span16_TexZw(uint *param_1,uint *param_2); /* 0x00461c90 */
void rdRaster_Span16_TexLitZw_9(uint *param_1,uint *param_2); /* 0x00462780 */
void rdRaster_Span16_TexLitZw_10(uint *param_1,uint *param_2); /* 0x00463270 */
void rdRaster_Span16_TexLitZw_11(uint *param_1,uint *param_2); /* 0x00463d60 */
void rdRaster_Span16_TexLitZw_12(uint *param_1,uint *param_2); /* 0x00464850 */
void rdRaster_Span16_TexLitZw_13(uint *param_1,uint *param_2); /* 0x00465340 */
void rdRaster_Span16_TexLitZw_14(uint *param_1,uint *param_2); /* 0x00465e30 */
void rdRaster_Span16_TexLitZw_15(uint *param_1,uint *param_2); /* 0x00466920 */
void rdRaster_Span16_TexLitZw_16(uint *param_1,uint *param_2); /* 0x00466c30 */
void rdRaster_Span16_TexLitZw_17(uint *param_1,uint *param_2); /* 0x00466f30 */
void rdRaster_Span16_TexLitZw_18(uint *param_1,uint *param_2); /* 0x00467230 */
void rdRaster_Span16_TexLitZw_19(uint *param_1,uint *param_2); /* 0x00467530 */
void rdRaster_Span16_TexLitZw_20(uint *param_1,uint *param_2); /* 0x00467830 */
void rdRaster_Span16_TexLitZw_21(uint *param_1,uint *param_2); /* 0x00467b30 */
void rdRaster_Span16_TexLitZw_22(uint *param_1,uint *param_2); /* 0x00467e30 */
void rdRaster_Span16_TexZw_2(uint *param_1,uint *param_2); /* 0x00468130 */
void rdRaster_Span16_TexZw_3(uint *param_1,uint *param_2); /* 0x00468af0 */
void rdRaster_Span16_TexZw_4(uint *param_1,uint *param_2); /* 0x00469450 */
void rdRaster_Span16_TexZw_5(uint *param_1,uint *param_2); /* 0x00469db0 */
void rdRaster_Span16_TexLitZw_23(uint *param_1,uint *param_2); /* 0x0046a710 */
void rdRaster_Span16_TexZw_6(uint *param_1,uint *param_2); /* 0x0046b070 */
void rdRaster_Span16_TexZw_7(uint *param_1,uint *param_2); /* 0x0046b9d0 */
void rdRaster_Span16_TexLitZw_24(uint *param_1,uint *param_2); /* 0x0046c330 */
void rdRaster_Span16_TexLitZw_25(uint *param_1,uint *param_2); /* 0x0046c640 */
void rdRaster_Span16_TexLitZw_26(uint *param_1,uint *param_2); /* 0x0046c940 */
void rdRaster_Span16_TexLitZw_27(uint *param_1,uint *param_2); /* 0x0046cc40 */
void rdRaster_Span16_TexLitZw_28(uint *param_1,uint *param_2); /* 0x0046cf40 */
void rdRaster_Span16_TexLitZw_29(uint *param_1,uint *param_2); /* 0x0046d240 */
void rdRaster_Span16_TexLitZw_30(uint *param_1,uint *param_2); /* 0x0046d540 */
void rdRaster_Span16_TexZw_8(uint *param_1,uint *param_2); /* 0x0046d840 */
void rdRaster_Span16_TexZw_9(uint *param_1,uint *param_2); /* 0x0046e200 */
void rdRaster_Span16_TexZw_10(uint *param_1,uint *param_2); /* 0x0046eb60 */
void rdRaster_Span16_TexZw_11(uint *param_1,uint *param_2); /* 0x0046f4c0 */
void rdRaster_Span16_TexLitZw_31(uint *param_1,uint *param_2); /* 0x0046fe20 */
void rdRaster_Span16_TexZw_12(uint *param_1,uint *param_2); /* 0x00470780 */
void rdRaster_Span16_TexZw_13(uint *param_1,uint *param_2); /* 0x004710e0 */

/* ===== rdmaterial.c ===== */
uint rdMaterial_RegisterLoader(uint param_1); /* 0x00417e90 */
uint rdMaterial_RegisterUnloader(uint param_1); /* 0x00417ea0 */
void * __cdecl rdMaterial_Load(char *name,int a,int b); /* 0x00417eb0 */
int __cdecl rdMaterial_LoadEntry(char *filename,void *material,int a,int b); /* 0x00417f30 */
void rdMaterial_Free(undefined4 param_1); /* 0x00418360 */
void rdMaterial_FreeEntry(int param_1); /* 0x004183a0 */
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
uint rdClip_SphereInFrustrum(int *param_1,float *param_2,float param_3); /* 0x0044e7d0 */
uint rdClip_FaceToPlane(float *param_1,float *param_2,float *param_3,undefined4 *param_4, float *param_5,uint *param_6); /* 0x0044ea50 */
void rdMatrix_Build34(float *param_1,undefined4 *param_2,float *param_3); /* 0x0044eeb0 */
void __cdecl rdMatrix_InvertOrtho34(float *out,float *m); /* 0x0044efd0 */
void rdMatrix_BuildRotate34(float *param_1,undefined4 *param_2); /* 0x0044f080 */
void __cdecl rdMatrix_BuildTranslate34(float *m,float *pos); /* 0x0044f1a0 */
void rdMatrix_BuildScale34(undefined4 *param_1,undefined4 *param_2); /* 0x0044f1d0 */
void rdMatrix_BuildFromVectorAngle34(float *param_1,float *param_2,float param_3); /* 0x0044f210 */
void rdMatrix_LookAt(float *param_1,float *param_2,float *param_3,undefined4 param_4); /* 0x0044f490 */
void rdMatrix_ExtractAngles34(float *param_1,float *param_2); /* 0x0044f650 */
void __cdecl rdMatrix_Identity34(float *m); /* 0x0044f880 */
void __cdecl rdMatrix_Multiply34(float *out,float *a,float *b); /* 0x0044f8a0 */
void __cdecl rdMatrix_PreMultiply34(float *m,float *angles); /* 0x0044fa70 */
void rdMatrix_PostMultiply34(float *param_1,float *param_2); /* 0x0044fc60 */
void Matrix_BuildTransform(float *param_1,undefined4 param_2); /* 0x0044fe50 */
void rdMatrix_PostTranslate34(int param_1,float *param_2); /* 0x0044fe80 */
void rdMatrix_PreScale34(float *param_1,undefined4 param_2); /* 0x0044feb0 */
void __cdecl rdMatrix_TransformVector34(float *out,float *v,float *param_3); /* 0x0044fee0 */
void __cdecl rdMatrix_TransformVectorOrtho34(float *out,float *v,float *m); /* 0x0044ff50 */
void __cdecl rdMatrix_TransformVector34Acc(float *vec,float *m); /* 0x0044ffc0 */
void __cdecl rdMatrix_TransformPoint34(float *out,float *a,float *b); /* 0x00450060 */
void __cdecl rdMatrix_TransformPoint34Acc(float *vec,float *m); /* 0x004500d0 */
void __cdecl rdMatrix_TransformPointLst34(float *m,float *in,float *out,int count); /* 0x00450170 */
undefined4 FUN_00450220(undefined4 *param_1); /* 0x00450220 */
void rdFace_FreeEntry(int param_1); /* 0x00450260 */
void rdMath_CalcSurfaceNormal(float *param_1,float *param_2,float *param_3,float *param_4); /* 0x00450290 */
void rdMath_ClampVector(float *param_1,float param_2); /* 0x00450380 */
undefined4 rdMath_PointsCollinear(float *param_1,float *param_2,float *param_3); /* 0x00450410 */

/* ===== rdclip.c ===== */
undefined4 rdClip_Line2(undefined4 param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4, undefined4 *param_5); /* 0x00446c10 */
uint rdClip_CalcOutcode2(int param_1,int param_2,int param_3); /* 0x00446e80 */
int __cdecl rdClip_Point3(void *frustum,float *point); /* 0x00446ec0 */
int __cdecl rdClip_Line3(void *frustum,float *p0,float *p1,int *clipped0,int *clipped1); /* 0x00446f80 */
uint rdClip_Face3W(int *param_1,float *param_2,uint param_3); /* 0x004478c0 */
int rdClip_Face3WOrtho(int *param_1,float *param_2,int param_3); /* 0x00448260 */
uint rdClip_Face3S(int *param_1,float *param_2,uint param_3); /* 0x004489b0 */
int rdClip_Face3SOrtho(int *param_1,float *param_2,int param_3); /* 0x00449350 */
float rdClip_Face3GS(int *param_1,float *param_2,float *param_3,float *param_4); /* 0x00449aa0 */
uint rdClip_Face3GSOrtho(int *param_1,float *param_2,float *param_3,uint param_4); /* 0x0044a6d0 */
float rdClip_Face3T(int *param_1,float *param_2,float *param_3,float *param_4); /* 0x0044b0a0 */
uint rdClip_Face3TOrtho(int *param_1,float *param_2,float *param_3,uint param_4); /* 0x0044be80 */
float rdClip_Face3GT(int *param_1,float *param_2,float *param_3,undefined4 *param_4,float *param_5); /* 0x0044c9d0 */
uint rdClip_Face3GTOrtho(int *param_1,float *param_2,undefined4 *param_3,undefined4 *param_4, uint param_5); /* 0x0044da40 */

/* ===== rdlight.c ===== */
undefined4 rdLight_NewEntry(int param_1); /* 0x00451460 */
void __cdecl rdLight_SetAngles(void *light,float inner,float outer); /* 0x004514a0 */
float __cdecl rdLight_CalcVertexIntensities (int *param_1,float *param_2,int param_3,uint param_4,int *param_5,uint param_6, float *param_7,float *param_8,uint param_9,float param_10); /* 0x00451510 */
float __cdecl rdLight_CalcFaceIntensity (int *param_1,int param_2,uint param_3,uint param_4,int param_5,float *param_6,int param_7 ,float param_8); /* 0x00451800 */

/* ===== rdprimit2.c ===== */
void __cdecl rdPrimit2_DrawLine(void *canvas,int x1,int y1,int x2,int y2,int color,int mask); /* 0x00451b80 */
void __cdecl rdPrimit2_DrawRectangle(void *canvas,int x1,int y1,int x2,int y2,int color,int mask); /* 0x00451f20 */

/* ===== memory.c ===== */
void Mem_DumpLog(void); /* 0x0045ff00 */
void __cdecl Mem_Copy(void *dst,void *src,uint n); /* 0x00478170 */
void __cdecl Mem_CheckAlloc(void *p,char *file,int line); /* 0x0047fe00 */
undefined4 Memory_SysInitialize(GrimServices *param_1,undefined4 *param_2); /* 0x004888d0 */
void Memory_SysTerminate(void); /* 0x00488930 */
undefined4 Memory_SysStartup(void); /* 0x00488940 */
void Memory_SysShutdown(void); /* 0x00488970 */
void ** Memory_AllocatePool(int param_1,void *param_2,void *param_3); /* 0x00488980 */
void Memory_FreePool(void **param_1); /* 0x00488a70 */
int * Memory_AllocFixed(int *param_1); /* 0x00488b10 */
void __cdecl Pool_Free(void *item); /* 0x00488ba0 */
void Pool_Grow(int param_1,int param_2); /* 0x00488c00 */

/* ===== rdprimitive.c ===== */
undefined4 rdPolyline_Draw(int param_1,float *param_2); /* 0x00471ee0 */
void rdPolyline_DrawFace(int param_1,int param_2,undefined4 param_3,undefined4 *param_4); /* 0x00472360 */
int __cdecl rdSprite_DrawThing(void *thing,void *sprite); /* 0x00472640 */
int rdSprite_New(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8, undefined4 param_9,undefined4 param_10); /* 0x004728a0 */
undefined4 rdSprite_NewEntry(int param_1,int param_2,undefined4 param_3,char *param_4,undefined4 param_5, undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9, undefined4 param_10,undefined4 *param_11); /* 0x00472910 */
void rdSprite_Free(int param_1); /* 0x00472b50 */
void rdSprite_FreeEntry(int param_1); /* 0x00472b70 */
undefined4 rdSprite_Draw(int param_1,float *param_2); /* 0x00472bd0 */

/* ===== stdfileutil.c ===== */
undefined * __cdecl stdFileOpen(uint param_1,uint param_2); /* 0x00473430 */
void stdFileClose(undefined4 param_1); /* 0x00473450 */
void stdFileRead(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x00473460 */
void stdFileWrite(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x00473480 */
void stdFileGets(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x004734a0 */
void stdFileGetws(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x004734c0 */
uint stdFeof(int param_1); /* 0x004734e0 */
undefined * __cdecl stdFtell(uint param_1); /* 0x004734f0 */
void stdFseek(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x00473500 */
undefined * stdFileSize(uint param_1); /* 0x00473520 */
undefined4 stdFilePrintf(undefined4 param_1,char *param_2); /* 0x00473570 */
uint stdFGetc(uint param_1); /* 0x004735f0 */
void stdFPutc(undefined4 param_1,undefined4 param_2); /* 0x00473610 */
int __cdecl LzssDecompress(void *dst,void *src,int srcSize); /* 0x00473a00 */
void stdCompress_DecompressLoop(void); /* 0x00473b60 */
void * __cdecl stdFileUtil_NewFind(char *dir,int mode,char *ext); /* 0x004c1170 */
void stdFileUtil_DisposeFind(int param_1); /* 0x004c12a0 */
int __cdecl stdFileUtil_FindNext(void *find,void *outEntry); /* 0x004c12d0 */

/* ===== math.c ===== */
int __cdecl stdCalcBitPos(int n); /* 0x004735d0 */
float __cdecl stdMath_FlexPower(float x,int n); /* 0x0047bbe0 */
float __cdecl stdMath_NormalizeAngle(float degrees); /* 0x0047bc20 */
float __cdecl stdMath_NormalizeAngleAcute(float param_1); /* 0x0047bce0 */
void stdMath_SinCos(float param_1,float *param_2,float *param_3); /* 0x0047bd20 */
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
undefined4 stdBitmap_LoadEntryFromFile(undefined4 param_1,int param_2,int param_3,int param_4); /* 0x0047ab20 */
void __cdecl stdBitmap_Free(void *bitmap); /* 0x0047ae70 */
void stdBitmap_FreeEntry(int param_1); /* 0x0047ae90 */
undefined4 stdBitmap_AppendToFile(undefined4 param_1,int param_2); /* 0x0047aef0 */
int __cdecl stdBitmap_Write(char *filename,void *bitmap); /* 0x0047b250 */
void stdBitmap_ConvertColorFormat(int *param_1,int param_2); /* 0x0047b2b0 */
int __cdecl stdBitmap_VBufferToBitmap(void *bitmap,int format,int flags); /* 0x0047b380 */
undefined4 stdBitmap_NewEntry(undefined4 *param_1,uint param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 *param_6); /* 0x0047b4b0 */
void stdBitmap_SetSurface(int param_1,int param_2,undefined4 param_3); /* 0x0047b540 */
int __cdecl stdBitmap_MemUsage(void *bitmap); /* 0x0047b560 */
void stdBitmap_DeCompress(int param_1); /* 0x0047b590 */
void stdPalEffects_ResetEffect(undefined4 *param_1); /* 0x0047b5f0 */

/* ===== stdinput.c ===== */
undefined * stdControl_Startup(void); /* 0x00476f10 */
void stdControl_Shutdown(void); /* 0x00476f70 */
undefined4 stdControl_Open(void); /* 0x00476fc0 */
undefined4 stdControl_Close(void); /* 0x00476fe0 */
void stdControl_Flush(void); /* 0x00477010 */
void stdControl_Reset(void); /* 0x00477040 */
int __cdecl stdControl_EnableAxis(uint axis); /* 0x00477090 */
void stdControl_ReadControls(void); /* 0x004770d0 */
float __cdecl stdControl_ReadAxis(int inputId); /* 0x00477160 */
int __cdecl stdControl_ReadKey(int inputId,int *down,int *justPressed); /* 0x00477230 */
void __cdecl Input_SetAcquired(int acquire); /* 0x00477300 */
void stdControl_ShowMouseCursor(int param_1); /* 0x00477380 */
void Input_InitJoysticks(void); /* 0x00477390 */
void Input_CreateKeyboard(void); /* 0x00477530 */
void Input_CreateMouse(void); /* 0x004775a0 */
void Input_MarkAxisUsed(uint param_1); /* 0x00477680 */
void Input_PollKeyboard(void); /* 0x00477730 */
void Input_FlushKeyboard(void); /* 0x004778a0 */
void Input_PollJoysticks(void); /* 0x004778f0 */
void Input_PollMouse(void); /* 0x00477c20 */
void Input_FlushJoystick(void); /* 0x00477dc0 */
void __cdecl Input_SetAxisRange(int axis,int min,int max,float deadZone); /* 0x00477e70 */

/* ===== plat.c ===== */
undefined4 Plat_ReturnTrue(void); /* 0x00477f00 */
uint stdPlatform_GetPhysicalRam(void); /* 0x00478150 */
int __cdecl grimPlat_QueryDialog(char *text,char *caption,uint flags); /* 0x00487650 */
void grimPlat_SetDefaultOpenPath(undefined4 param_1); /* 0x00487690 */
char * grimPlat_GetDefaultOpenPath(void); /* 0x004876b0 */
int __cdecl grimPlat_OpenFileRequest(char *title,char *filter); /* 0x004876c0 */
int __cdecl grimPlat_SaveFileRequest(char *title,char *filter); /* 0x004877d0 */
int grimPlat_SpinDialog(int param_1,int param_2,undefined4 *param_3,uint param_4); /* 0x004878c0 */
int __cdecl grimPlat_TreeDialog(char *title,char **items,int count,int *recursive); /* 0x00487c10 */
int __cdecl grimPlat_InputDialog(char *title,char *prompt,char *buf,int bufSize,char *defaultText); /* 0x00487e30 */
undefined * __stdcall Plat_PromptDialogProc(int a1,int a2,int a3,int a4); /* 0x00488370 */
undefined * __stdcall Plat_TreeSelectDialogProc(int a1,int a2,int a3,int a4); /* 0x00488460 */
undefined * __stdcall Plat_InputDialogProc(int a1,int a2,int a3,int a4); /* 0x004886f0 */
void * __cdecl Plat_Alloc(uint size); /* 0x00488800 */
void __cdecl Plat_Free(void *p); /* 0x00488820 */

/* ===== platsvc.c ===== */
void stdPlatform_Assert(undefined4 param_1,char *param_2,undefined4 param_3); /* 0x00477f10 */
void stdPlatform_AllocHandle(uint param_1); /* 0x00478030 */
void stdPlatform_FreeHandle(undefined4 param_1); /* 0x00478040 */
void stdPlatform_ReallocHandle(undefined4 param_1,undefined4 param_2); /* 0x00478050 */
undefined4 stdPlatform_LockHandle(undefined4 param_1); /* 0x00478070 */

/* ===== std3d.c ===== */
undefined4 D3D_Enumerate(void); /* 0x00478230 */
void D3D_Release(void); /* 0x004782b0 */
uint D3D_IsAvailable(void); /* 0x004782d0 */
int __cdecl D3D_SelectDriver(uint driverIdx,int useZBuffer); /* 0x004782e0 */
void D3D_ReleaseDriver(void); /* 0x00478660 */
void __cdecl D3D_SetTextureLimits(int minW,int minH,int maxSize,int d); /* 0x00478700 */
void std3D_StartScene(void); /* 0x00478730 */
void std3D_EndScene(void); /* 0x00478750 */
undefined4 D3D_BeginExecuteBuffer(void); /* 0x00478770 */
int __cdecl std3D_AddRenderListVertices(void *verts,uint count); /* 0x004787d0 */
undefined4 std3D_RenderListVerticesFinish(void); /* 0x00478840 */
int __cdecl std3D_AddRenderListTris(void *tris,uint count); /* 0x004788c0 */
int std3D_DrawRenderList(void); /* 0x00478b40 */
void __cdecl D3D_SetRenderFlags(uint flags); /* 0x00478c00 */
void std3D_GetValidDimensions(uint param_1,uint param_2,uint *param_3,uint *param_4); /* 0x00479070 */
void std3D_PurgeTextureCache(void); /* 0x00479110 */
int __cdecl std3D_AddToTextureCache(void *surface,void *texture,int usePalette,int colorKey); /* 0x00479170 */
void D3D_FreeAllTextures(void); /* 0x00479860 */
void D3D_LinkTexture(void *param_1); /* 0x004798e0 */
void D3D_UnlinkTexture(void *param_1); /* 0x00479950 */
undefined4 D3D_SetVertexLimit(void); /* 0x00479a00 */
void std3D_UpdateFrameCount(int param_1); /* 0x00479a70 */
undefined4 std3D_ClearZBuffer(void); /* 0x00479aa0 */
uint D3D_FindClosestDriver(int *param_1,int param_2,uint param_3); /* 0x00479b50 */
uint D3D_FindTextureFormat(int *param_1,int param_2,uint param_3); /* 0x00479be0 */
void D3D_SetViewportRect(uint *param_1); /* 0x00479cc0 */
undefined4 D3D_InitRenderState(void); /* 0x00479db0 */
undefined4 __cdecl D3D_CreateViewport(uint width,uint height); /* 0x0047a130 */
undefined4 D3D_CreateZBuffer(int param_1,int param_2); /* 0x0047a240 */
undefined * __stdcall D3D_EnumDevicesCallback(int a1,int a2,int a3,int a4,int a5,int a6); /* 0x0047a3b0 */
undefined * __stdcall D3D_EnumTextureFormatsCallback(int a1,int a2); /* 0x0047a590 */
uint D3D_CapsToFilterBits(uint param_1); /* 0x0047a850 */
uint D3D_FilterBitsToMask(byte param_1); /* 0x0047a890 */
uint D3D_FilterBitsToEnum(byte param_1); /* 0x0047a8e0 */
int __cdecl D3D_EvictTexture(uint size); /* 0x0047a930 */

/* ===== stdpcx.c ===== */
undefined4 stdPcx_DecodeRun16(byte *param_1,ushort *param_2,int param_3); /* 0x0047b710 */
undefined4 stdPcx_DecodeRun8(byte *param_1,int param_2,int param_3); /* 0x0047b780 */
undefined4 stdPcx_DecodeRunMasked(byte *param_1,int param_2,int param_3,uint param_4); /* 0x0047b810 */
undefined4 * stdPcx_Load(undefined4 param_1,int param_2,int param_3); /* 0x0047ec80 */
undefined4 stdPcx_Write(undefined4 param_1,int param_2); /* 0x0047ef10 */

/* ===== stdconffile.c ===== */
void stdConffile_Open(undefined4 param_1); /* 0x0047c7c0 */
undefined4 stdConffile_OpenMode(byte *param_1,undefined4 param_2); /* 0x0047c7e0 */
void stdConffile_Close(void); /* 0x0047c8c0 */
undefined4 stdConffile_ReadLine(void); /* 0x0047c920 */
void stdConffile_Push(void); /* 0x0047ca00 */
void stdConffile_Pop(void); /* 0x0047ca90 */

/* ===== stdbmp.c ===== */
uint stdBmp_Load(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x0047cb20 */
undefined4 stdBmp_LoadEntry(char *param_1,undefined4 *param_2,int param_3,int param_4); /* 0x0047cb70 */
undefined4 stdBmp_Write(undefined4 param_1,int param_2); /* 0x0047d050 */

/* ===== stdpic.c ===== */
uint stdPic_Load(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x0047d280 */
undefined4 stdPic_LoadEntry(char *param_1,undefined4 *param_2,int param_3,int param_4); /* 0x0047d2d0 */

/* ===== stdgif.c ===== */
void * stdGif_Load(char *param_1,int param_2,int param_3); /* 0x0047db00 */
undefined4 stdGif_Write(undefined4 param_1,int param_2); /* 0x0047e060 */
uint stdGif_LzwInitDecoder(short param_1); /* 0x0047e3c0 */
uint stdGif_LzwDecodeNext(undefined4 param_1); /* 0x0047e470 */
uint getcode(undefined4 param_1); /* 0x0047e600 */
uint stdGif_ReadByte(undefined4 param_1); /* 0x0047e770 */
uint stdGif_LzwInitEncoder(undefined4 param_1,undefined4 param_2); /* 0x0047e7f0 */
void putcode(undefined4 param_1,short param_2); /* 0x0047e8b0 */
uint stdGif_LzwEncodePixel(undefined4 param_1,byte param_2); /* 0x0047ea30 */
void stdGif_LzwClearTable(undefined4 param_1); /* 0x0047eba0 */
undefined4 stdGif_LzwFinishEncode(undefined4 param_1); /* 0x0047ebe0 */
void stdGif_WriteSubBlock(undefined4 param_1,short param_2); /* 0x0047ec40 */

/* ===== stdlbm.c ===== */
void * stdLbm_Load(char *param_1,int param_2,int param_3); /* 0x0047f120 */
undefined4 stdLbm_Write(undefined4 param_1,int param_2); /* 0x0047f720 */
void stdLbm_PackBits(undefined4 param_1,undefined1 *param_2,int param_3,char *param_4); /* 0x0047f9d0 */
void stdLbm_PackByte(char param_1); /* 0x0047fa70 */
void stdLbm_SwapHeader(undefined2 *param_1); /* 0x0047fc80 */

/* ===== std.c ===== */
uint Std_Swap32(uint param_1); /* 0x0047fc50 */
uint Std_Swap16(uint param_1); /* 0x0047fd00 */

/* ===== stdmemory.c ===== */
void stdMemory_CheckMagic(int param_1); /* 0x0047fe20 */
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
int * Res_FindByNameInList(int param_1,char *param_2,int *param_3); /* 0x00481320 */
void * __cdecl Res_CreateRecord(int type,char *name,void *data); /* 0x00481400 */
void __cdecl Res_CallUnload(void *res); /* 0x00481510 */
int __cdecl Res_Unlink(void *res); /* 0x004815c0 */
int __cdecl Res_GetSize(void *res); /* 0x00481ef0 */
void __cdecl Res_MoveToFront(void *res); /* 0x00481f00 */
uint __cdecl Res_HashName(char *name,char *outLower); /* 0x00481f60 */
void Res_GetFirstType(int *param_1,int *param_2,int param_3); /* 0x00482170 */
void Res_GetNextType(int *param_1,int *param_2,int param_3); /* 0x004821b0 */
undefined * __cdecl Res_Touch(void *param_1); /* 0x00482200 */
int Res_CountChildren(uint param_1,uint param_2); /* 0x004824f0 */
void grimlib_SetCacheMax(int param_1); /* 0x00482520 */
void sputResource_ReportAllocations(void); /* 0x0048e230 */

/* ===== resource.c ===== */
undefined4 Res_SysInitialize(uint param_1,undefined4 *param_2); /* 0x00480010 */
undefined4 __fastcall FUN_00480020(uint param_1,int param_2,undefined4 param_3,undefined4 *param_4); /* 0x00480020 */
void Res_SysTerminate(void); /* 0x004800a0 */
undefined4 Res_SysStartup(void); /* 0x004800b0 */
void Res_SysShutdown(void); /* 0x00480140 */
undefined4 Res_SysSave(code *param_1); /* 0x00482260 */
undefined4 Res_SysLoad(code *param_1); /* 0x00482380 */
void __cdecl Resource_SetNoPurge(int noPurge); /* 0x0048d340 */
void * __cdecl sputResource_Alloc(int fourcc,char *name); /* 0x0048d350 */
undefined4 sputResource_CloseResources(void); /* 0x0048d3e0 */
undefined4 grimlib_FindResources(void); /* 0x0048d3f0 */
int __cdecl sputResource_AddResourcePath(char *dir); /* 0x0048d4b0 */
int sputResource_LogToFile(char *param_1); /* 0x0048d550 */
int __cdecl AddResourcePath(char *dir); /* 0x0048d570 */
void Resource_CountCostumeRefs(undefined4 param_1); /* 0x0048d810 */
undefined4 Resource_RegisterTypes(void); /* 0x0048d870 */
void __cdecl sputResource_SetMemoryUsage(int budget,int b); /* 0x0048d8a0 */
void Resource_ReloadBitmaps(void); /* 0x0048df50 */
void Resource_RebuildColormaps(void); /* 0x0048e0a0 */
void * sputResource_MatLoader(char *param_1); /* 0x0048e170 */
void sputResource_MatUnloader(void *param_1); /* 0x0048e1b0 */

/* ===== lab.c ===== */
void Res_FileCloseAll(void); /* 0x00480120 */
int __cdecl Res_FileOpen(char *path); /* 0x00480360 */
int __cdecl Res_FileClose(char *name); /* 0x004803a0 */
int __cdecl Res_FileMoveToFront(char *name); /* 0x004804c0 */
void * __cdecl Lab_Find(char *name); /* 0x00481070 */
void Lab_Unlink(int *param_1); /* 0x004813c0 */
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
void * sputResource_LipSyncHandler(int *param_1); /* 0x0048d8c0 */
int __cdecl sputResource_BackgroundHandler(void *msg); /* 0x0048d930 */
int __cdecl sputResource_CostumeHandler(void *msg); /* 0x0048da40 */
void * sputResource_ColormapHandler(int *param_1); /* 0x0048dab0 */
void * sputResource_FontHandler(int *param_1); /* 0x0048dbd0 */
void * sputResource_KeyframeHandler(int *param_1); /* 0x0048dc60 */
void * sputResource_MaterialHandler(int *param_1); /* 0x0048dd20 */
void * sputResource_ModelHandler(int *param_1); /* 0x0048de10 */
void * sputResource_SetHandler(int *param_1); /* 0x0048de70 */
void * sputResource_ZBufferHandler(int *param_1); /* 0x0048dee0 */
undefined4 sputResource_MemoryHandler(int *param_1); /* 0x0048e1e0 */

/* ===== resfile.c ===== */
int __cdecl Res_FOpen(char *name,char *mode); /* 0x00480890 */
int __cdecl Res_FClose(int fh); /* 0x00480a00 */
uint __cdecl Res_FRead(int fh,void *buf,uint n); /* 0x00480a70 */
char * Res_FGets(int param_1,char *param_2,uint param_3); /* 0x00480bb0 */
undefined4 Res_FWrite(int param_1,undefined4 param_2,undefined4 param_3); /* 0x00480ce0 */
undefined4 Res_FEOF(int param_1); /* 0x00480d50 */
undefined4 Res_FTell(int param_1); /* 0x00480dc0 */
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
void Res_ResolveToSerialNumber(undefined4 *param_1); /* 0x00482220 */

/* ===== engine.c ===== */
void Res_FreeAll(void); /* 0x00482460 */
void grimlib_LogResources(undefined4 param_1); /* 0x00482530 */
void grimlib_OverrideSelectedActorCostume(int param_1); /* 0x004825c0 */
void grimlib_RestoreSelectedActorCostume(void); /* 0x004825f0 */
int __cdecl grimlib_SetDisplay(void *mode,int flags); /* 0x00482620 */
undefined4 grimlib_UnsetDisplay(void); /* 0x00482660 */
void grimlib_Close(void); /* 0x004826e0 */
void grimlib_SetDebugToggleCallback(undefined4 param_1); /* 0x00482720 */
void grimlib_SetPaletteCallback(undefined4 param_1); /* 0x00482730 */
void grimlib_SetShutdownCallback(uint param_1); /* 0x00482740 */
void grimlib_SetPageFlipCallback(undefined4 param_1); /* 0x00482750 */
void grimlib_Using3DHardware(undefined4 param_1); /* 0x00482760 */
void grimlib_AddResourcePath(char *param_1); /* 0x00482770 */
int grimlib_FindSystemFiles(void); /* 0x00482790 */
undefined4 grimlib_Open(int param_1,char *param_2); /* 0x004827a0 */
void grimlib_MarkDirtyRect(int *param_1,int param_2); /* 0x00482800 */
int grimlib_ConfirmClose(void); /* 0x004828d0 */
void __cdecl grimlib_RequestShutdown(int exitCode); /* 0x004828e0 */
void __cdecl grimlib_SetPause(int paused); /* 0x00482900 */
undefined * __cdecl grimlib_CharacterCallback(int param_1); /* 0x00482980 */
void grimlib_UpdateManual(int param_1,int param_2); /* 0x00482990 */
void __cdecl gimlib_SetImuseState(int state); /* 0x00482ae0 */
void grimlib_Display(void); /* 0x00482af0 */
uint Engine_RegisterSubsystems(undefined4 param_1,undefined4 *param_2,int param_3,int param_4); /* 0x00482cf0 */
undefined4 Engine_InitSubsystems(int param_1,int param_2); /* 0x00482d60 */
undefined4 Engine_ShutdownSubsystems(int param_1,int param_2); /* 0x00482dd0 */
undefined4 Engine_ResetSubsystems(int param_1,int param_2); /* 0x00482e00 */
void PerfBegin(int param_1); /* 0x00482e30 */
undefined * __cdecl PerfEnd(int param_1); /* 0x00482e80 */
undefined4 grimlib_PlayMovie(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5); /* 0x00482f00 */
void grimlib_UserPaint(void); /* 0x00482f80 */
void grimlib_Save(char *param_1); /* 0x00482f90 */
void grimlib_Load(char *param_1); /* 0x00482fb0 */
uint grimlib_JustLoaded(void); /* 0x00482fd0 */
void Engine_SaveGame(void); /* 0x00482fe0 */
void Engine_LoadGame(void); /* 0x00483240 */
void SetPrevMode(uint param_1); /* 0x004835f0 */
uint GetPrevMode(void); /* 0x00483600 */
undefined4 sputRender_Open(void); /* 0x00484000 */
void sputRender_Update(void); /* 0x00484260 */
void __cdecl sputControl_AddCallback(void *fn); /* 0x0048d1a0 */
void __cdecl sputControl_Update(undefined4 param_1,undefined4 param_2); /* 0x0048d1c0 */

/* ===== set.c ===== */
int Res_NumRefs(void *param_1); /* 0x004824c0 */
void __cdecl grimlib_MakeCurrentSet(char *name); /* 0x00482670 */
void * grimlib_MakeCurrentSetup(uint param_1); /* 0x00482820 */
void __cdecl sputRender_SyncCamera(void *set,int setupIdx); /* 0x00483aa0 */
void __cdecl sputRender_UseSetup(void *set,int setupIdx); /* 0x00483b50 */
void Set_DrawDebugLights(int param_1); /* 0x00485780 */
void __cdecl Set_DrawDebugCameras(void *set,uint setupIdx); /* 0x004859c0 */
void sputRoom_SetSoundParameters (int param_1,undefined4 param_2,undefined1 param_3,undefined1 param_4, undefined4 param_5,undefined4 param_6); /* 0x004a4010 */
void __cdecl sputRoom_GetSoundParameters(void *set,float *minVol,char *maxVol,char *c,float *d,float *e); /* 0x004a4050 */
void __cdecl sputRoom_SetCurrentRoom(void *set,int param_2); /* 0x004a40f0 */
void * sputRoom_GetCurrentRoom(void); /* 0x004a41b0 */
char * sputRoom_GetCurrentRoomName(void); /* 0x004a41d0 */
int __cdecl sputRoom_Save(void *writeFn); /* 0x004a41e0 */
int __cdecl sputRoom_Restore(void *readFn); /* 0x004a44e0 */
undefined4 * sputRoom_LoadRoom(char *param_1); /* 0x004a49a0 */
void Set_InitRecord(undefined4 *param_1); /* 0x004a4a70 */
void __cdecl sputRoom_UnReference(void *set); /* 0x004a4b40 */
void sputRoom_FreeRoom(undefined4 param_1); /* 0x004a4c40 */
void sputRoom_FreeRoomEntry(char *param_1); /* 0x004a4c60 */
void Set_FreeSetups(int param_1); /* 0x004a4d10 */
void Set_FreeSetup(undefined4 param_1,int param_2); /* 0x004a4d80 */
int __cdecl sputRoom_LoadResources(void *set); /* 0x004a4fe0 */
int __cdecl Set_RegisterHandle(char *name,void *fn); /* 0x004a54a0 */
int Set_FindHandle(char *name); /* 0x004a5500 */
int Set_IsHandleValid(char *param_1); /* 0x004a55d0 */
void * __cdecl GetRoomActors(char *setName); /* 0x004a60a0 */
void * Set_FindNameInList(int param_1); /* 0x004a60c0 */
void * __cdecl Set_NormalizeName(char *setName); /* 0x004a6100 */
void WalkPlane_KillCollection(void *param_1); /* 0x004a7100 */
void __cdecl WalkPlane_SetCollection(void *set); /* 0x004a7150 */

/* ===== enginemodule.c ===== */
undefined * __cdecl grimlib_GameInitialize(GrimServices *param_1,undefined **param_2); /* 0x00482540 */
undefined * grimlib_GameTerminate(void); /* 0x00482b60 */
int grimlib_GameStartup(void); /* 0x00482ba0 */
undefined * grimlib_GameShutdown(void); /* 0x00482cc0 */

/* ===== savegame.c ===== */
int __cdecl SaveGame_Write(void *data,int bytes); /* 0x004831f0 */
int __cdecl SaveGame_Read(void *buf,int n); /* 0x00483470 */
void * __cdecl sputMain_GetSaveGameImage(char *filename); /* 0x00483490 */

/* ===== imuse.c ===== */
void IMuse_SaveToTemp(void); /* 0x00483610 */
void IMuse_RestoreFromTemp(void); /* 0x00483650 */

/* ===== imusemodule.c ===== */
undefined4 PolyglotInitialize(GrimServices *param_1,undefined4 *param_2); /* 0x004836b0 */
void polyglot_shutdown(void); /* 0x004836f0 */

/* ===== polyglot.c ===== */
void PolyglotConfigure(undefined *param_1); /* 0x00483720 */
char * __cdecl PolyglotGetString(char *textId); /* 0x004838e0 */

/* ===== render.c ===== */
uint * Render_GetBackBuffer(void); /* 0x004839f0 */
void sputRender_DrawDebuggingToggle(void); /* 0x00483a00 */
void sputRender_SetPaletteCallback(uint param_1); /* 0x00483a80 */
void sputRender_SetPageFlipCallback(void *param_1); /* 0x00483a90 */
int __cdecl sputRender_Save(void *writeFn); /* 0x00483da0 */
int __cdecl sputRender_Restore(void *readFn); /* 0x00483e20 */
void sputRender_Using3DHardware(int param_1); /* 0x00483ea0 */
void __cdecl sputRender_PageCountIs(int n); /* 0x00483eb0 */
void __cdecl sputRender_MarkDirtyRect(int *rect,int flag); /* 0x00483ed0 */
void __cdecl MarkDirtyRect(int *rect,int flag); /* 0x00483f60 */
undefined4 sputRender_SetDisplay (uint param_1,uint param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5, undefined4 param_6,int param_7); /* 0x00484030 */
void sputRender_Close(void); /* 0x004841f0 */
void sputRender_PageFlip(void); /* 0x004849a0 */
void Render_SetPixelFormat(uint *param_1); /* 0x004849d0 */
undefined4 sputRender_ControlHandler(void); /* 0x00484a50 */
void Render_InitColorConstants(int param_1); /* 0x00484c40 */
void Render_DrawDebugGrid(void); /* 0x00485bd0 */
int Render_CanvasIsPaletted(void); /* 0x00486100 */
void Render_BuildActorDrawList(void); /* 0x00486120 */
void __cdecl sputRender_ReverseProject(int x,int y,float *outPos); /* 0x004862e0 */
void __cdecl sputRender_PreRendered(int redrawBackground,int redrawDepth); /* 0x004863b0 */
void Render_BuildColorTable(int param_1,float param_2); /* 0x004864a0 */
void __cdecl sputRender_ColorCorrect(ushort *pixels,uint n); /* 0x00486620 */
void __cdecl sputRender_SetGamma(float gamma); /* 0x00486710 */
void sputRender_Decompress(void *param_1); /* 0x00486760 */
void sputRender_Dim(ushort *param_1,byte param_2); /* 0x004867d0 */
void Render_CopyBackBufferToBackground(void); /* 0x00486990 */
void Render_CleanBuffer(void); /* 0x004869b0 */
void sputRender_ForceRefresh(void); /* 0x00486a00 */
void * sputRender_CleanArtBuffer(void); /* 0x00486b00 */
void * sputRender_CleanZBuffer(void); /* 0x00486b10 */
code * __cdecl sputRender_SetPaletteFunc(void); /* 0x00486b20 */
void sputRender_SetPageFlip(int param_1); /* 0x00486b30 */
void __cdecl sputRender_DrawIrisEffect(float percent,int x,int y); /* 0x00486d00 */
void __cdecl sputRender_IrisDown(int x,int y,int durationMs); /* 0x00486eb0 */
void __cdecl sputRender_IrisUp(int x,int y,int durationMs); /* 0x00486ef0 */
uint sputRender_IrisComplete(void); /* 0x00486f30 */
void * __cdecl sputRender_ScreenShot(int w,int h); /* 0x00486f90 */
void __cdecl sputRender_DimRegion(int x,int y,int w,int h,float scale); /* 0x004870e0 */
void __cdecl sputRender_SaveScreen(char *filename); /* 0x00487260 */
void __cdecl Render_SaveZBufferBmp(char *filename); /* 0x004872f0 */
void __cdecl sputRender_SaveDrawBuffer(char *filename); /* 0x00487340 */
void __cdecl Render_DrawProgressBar(float fraction); /* 0x004873d0 */
void sputRender_AllowLoadImage(uint param_1); /* 0x004874c0 */
void sputRender_DrawLoadingImage(void); /* 0x004874d0 */
int sputActor_GetNumActorsTalking(void); /* 0x0048f920 */

/* ===== sputrender.c ===== */
undefined4 sputRender_Initialize(GrimServices *param_1,undefined4 *param_2); /* 0x00483d40 */
void sputRender_Terminate(void); /* 0x00486050 */
int sputRender_Startup(void); /* 0x00486070 */
void sputRender_Shutdown(void); /* 0x004860d0 */

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
int __cdecl sputActor_GetActorHandle(Actor *actor,int tag); /* 0x00490380 */
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
void sputCostume_Draw3D(undefined4 param_1,undefined4 param_2); /* 0x00495080 */
void sputCostume_InternalDraw3D(int *param_1,float *param_2); /* 0x004950a0 */
void __cdecl sputRoom_RemoveActor(char *setName,void *actor); /* 0x004a5eb0 */
void __cdecl sputRoom_AddActor(Actor *actor,char *setName); /* 0x004a5f60 */
float __thiscall Puck_GetYawToPoint(Puck *this,float *point); /* 0x004a8500 */

/* ===== dirtyrect.c ===== */
void __cdecl DirtyRect_Add(int *rect,int flag,int bufferIdx); /* 0x00485420 */
void __cdecl DirtyRect_Flush(void *dst,void *zdst); /* 0x00485e50 */
void DirtyRect_Clear(void); /* 0x00486020 */

/* ===== setup.c ===== */
void Setup_DrawDebugCamera(int param_1); /* 0x00485a40 */
void * __cdecl sputRoom_GetSetupBackground(void *set,int setupIdx); /* 0x004a3db0 */
void * __cdecl sputRoom_GetSetupZBackground(void *set,int setupIdx); /* 0x004a3ef0 */

/* ===== sector.c ===== */
void __cdecl Sector_DrawAllDebug(void); /* 0x00485dc0 */
void sputLua_CollisionHandler(int param_1,int param_2,float *param_3,float *param_4,float *param_5); /* 0x0049c750 */
int SetFile_Parse(char *param_1,uint param_2); /* 0x004a4b00 */
undefined4 sputRoom_LoadRoomEntry(undefined4 param_1); /* 0x004a5550 */
undefined4 sputRoom_ParseColormaps(void); /* 0x004a5b40 */
undefined4 sputRoom_ParseSectors(void); /* 0x004a5c90 */
void WalkPlane_BuildCache(void); /* 0x004a61c0 */
void WalkPlane_DestroyCache(void); /* 0x004a6330 */
void WalkPlane_RestoreCache(void); /* 0x004a6380 */
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
void WalkPlane_AllActive(void); /* 0x004a7a90 */
WalkVertex * WalkPlane_AddVertex(undefined4 param_1,float *param_2); /* 0x004a7ab0 */
void WalkPlane_RemoveVertex(int *param_1); /* 0x004a7ba0 */
undefined * ParseCollection(int param_1); /* 0x004a7bc0 */
int __thiscall WalkPlane_ClipPoly(WalkPlane *this,float *verts,int count,float *out); /* 0x004a8cb0 */
float __thiscall WalkPlane_DistToEdge(WalkPlane *this,int edge,float *point); /* 0x004a9070 */
undefined4 __fastcall WalkPlane_RemoveShortEdge(WalkPlane *plane); /* 0x004a9180 */
void __cdecl ShrinkBoxes(float radius); /* 0x004a9d00 */

/* ===== drawlist.c ===== */
void DrawList_Reset(void); /* 0x00486250 */
undefined * DrawList_Alloc(void); /* 0x00486280 */
undefined4 FUN_004862b0(int *param_1,int *param_2); /* 0x004862b0 */

/* ===== plane.c ===== */
int __cdecl sputRender_SegmentPlaneIntersect(float *out,float *p1,float *p2,float a,float b,float c,float d); /* 0x00486a10 */

/* ===== cacherect.c ===== */
void * __cdecl sputRender_CreateCacheRect(int x,int y,int w,int h); /* 0x00486b40 */
void sputRender_RestoreCacheRect(void); /* 0x00486c50 */
void CacheRect_FreeAll(void); /* 0x00486cb0 */

/* ===== dlg.c ===== */
undefined4 * Dlg_MakeItemTemplate (undefined4 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4, undefined2 param_5,undefined2 param_6,int param_7,int param_8,uint *param_9); /* 0x00488010 */
uint * Dlg_MakeDialogTemplate (undefined4 *param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4, undefined2 param_5,undefined2 param_6,int param_7,int param_8,undefined2 param_9, uint *param_10); /* 0x004881a0 */

/* ===== spew.c ===== */
void Spew_Startup(void); /* 0x00488840 */
void grimDebug_Shutdown(void); /* 0x00488860 */
void Spew_LoadDll(void); /* 0x00488890 */

/* ===== fileutil.c ===== */
undefined4 FileUtil_SysInitialize(GrimServices *param_1,undefined4 *param_2); /* 0x00488c80 */
void FileUtil_SysTerminate(void); /* 0x00488ce0 */
undefined4 FileUtil_SysStartup(void); /* 0x00488cf0 */
void FileUtil_SysShutdown(void); /* 0x00488d20 */
undefined4 FileUtil_SysSave(code *param_1); /* 0x00488d30 */

/* ===== savefile.c ===== */
undefined4 FileUtil_SysRestore(code *param_1); /* 0x00488d80 */
void * SaveFile_Open(char *name,char *mode); /* 0x004c3e40 */

/* ===== dirscan.c ===== */
undefined4 * DirScan_Create(undefined4 param_1,int param_2,char *param_3); /* 0x00488de0 */
void DirScan_Destroy(int param_1); /* 0x00488e70 */
void DirScan_Reset(int param_1); /* 0x00488eb0 */
undefined4 DirScan_Next(int param_1,char *param_2); /* 0x00488ee0 */

/* ===== sputsmush.c ===== */
undefined4 sputSmush_Initialize(undefined4 param_1,undefined4 *param_2); /* 0x00488fb0 */
undefined4 sputSmush_Startup(void); /* 0x00489130 */
void sputSmush_Shutdown(void); /* 0x00489190 */

/* ===== movie.c ===== */
int __cdecl sputSmush_Save(void *fn); /* 0x00489030 */
undefined4 sputSmush_Restore(code *param_1); /* 0x00489090 */
undefined4 sputSmush_Periodic(void); /* 0x004891b0 */
int __cdecl sputSmush_SetTarget(void *surface); /* 0x00489280 */
undefined4 sputSmush_StartMovie(char *param_1,int param_2,uint param_3,uint param_4); /* 0x004892a0 */
void sputSmush_StopMovie(void); /* 0x00489370 */
int sputSmush_GetMovieLength(char *param_1); /* 0x00489390 */
undefined4 sputSmush_StartVideo(int param_1,int param_2,int param_3); /* 0x004893d0 */
int sputSmush_StopVideo(void); /* 0x00489410 */
undefined4 sputSmush_LockMovieBuffer(undefined4 *param_1,undefined4 *param_2); /* 0x00489420 */
undefined4 sputSmush_UnLockMovieBuffer(void); /* 0x004894b0 */
int sputSmush_SetVideoPalette(void); /* 0x004894d0 */
int sputSmush_MoviePlaying(void); /* 0x004894e0 */
void sputSmush_Pause(int paused); /* 0x004894f0 */

/* ===== primitivelist.c ===== */
void PrimitiveList_StaticConstruct(void); /* 0x00489510 */
void PrimitiveList_InitGlobal(void); /* 0x00489520 */
void PrimitiveList_RegisterAtExit(void); /* 0x00489530 */
void PrimitiveList_AtExitClear(void); /* 0x00489540 */
void __fastcall PrimitiveQueue_Construct(undefined4 *param_1); /* 0x0048a500 */
void __fastcall PrimitiveQueue_purge(int *param_1); /* 0x0048a520 */
void * __thiscall PrimitiveQueue_addObject(void *this,int id,int layer); /* 0x0048a670 */
void __thiscall PrimitiveQueue_draw(void *this,void *canvas,uint layerMask); /* 0x0048a9f0 */
undefined * __thiscall PrimitiveQueue_markAllDirty(void *this,int a1); /* 0x0048ab20 */
void * __thiscall PrimitiveQueue_findPrimitive(void *this,int id,void *after); /* 0x0048abd0 */

/* ===== primitives.c ===== */
void __cdecl sputPrimitive_Update(uint layerMask); /* 0x00489550 */
void sputPrimitive_Pause(void); /* 0x004895d0 */
void sputPrimitive_Resume(void); /* 0x004895f0 */
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
void PrimitiveQueue_resetId(void); /* 0x0048abc0 */

/* ===== sputprimitive.c ===== */
undefined4 sputPrimitive_Initialize(undefined4 param_1,undefined4 *param_2); /* 0x00489580 */
undefined4 sputPrimitive_Save(code *param_1); /* 0x00489600 */
undefined4 sputPrimitive_Restore(code *param_1); /* 0x004896b0 */
void sputPrimitive_Terminate(void); /* 0x004897d0 */
undefined4 sputPrimitive_Startup(void); /* 0x004897f0 */
void sputPrimitive_Shutdown(void); /* 0x00489820 */

/* ===== list.c ===== */
void __cdecl List_Unlink(void *obj); /* 0x0048ac00 */

/* ===== textobjects.c ===== */
void __cdecl sputText_Update(int drawAll); /* 0x0048ac40 */
void sputText_Pause(void); /* 0x0048ad40 */
void sputText_Resume(void); /* 0x0048ad50 */

/* ===== sputtext.c ===== */
undefined4 sputText_Initialize(GrimServices *param_1,undefined4 *param_2); /* 0x0048acc0 */
void sputText_Terminate(void); /* 0x0048c4d0 */
undefined4 sputText_Startup(void); /* 0x0048c500 */
void sputText_Shutdown(void); /* 0x0048c6f0 */
undefined4 sputText_Save(code *param_1); /* 0x0048cbc0 */
undefined4 sputText_Restore(code *param_1); /* 0x0048cd80 */

/* ===== text.c ===== */
int __cdecl GetTextParamsFromTable(TextContext *ctx,void *table,TextObject *textObj); /* 0x0048c050 */
char * __cdecl sputText_ExtractSayLineData(char *line,char *outId); /* 0x0048c8d0 */
int sputActor_GetActorTextRate(void); /* 0x00494740 */
void __cdecl sputActor_SetActorTextRate(int speed); /* 0x00494750 */
void * Text_GetSystemFont(void); /* 0x004aa930 */
int __cdecl Text_LoadNativeFont(char *filename,void **outFont); /* 0x004aa940 */
void __cdecl Text_FreeFont(void *font); /* 0x004aa990 */
int __cdecl Text_NextChar(char **pText); /* 0x004aa9b0 */
int __cdecl Text_GetCharKernedWidth(TextContext *ctx,int ch); /* 0x004aaa20 */
int __cdecl Text_GetStringWidth(TextContext *ctx,char *text); /* 0x004aaa80 */
int __cdecl Text_GetStringHeight(TextContext *ctx,char *text); /* 0x004aab10 */
undefined4 Text_DrawFormatted(TextContext *param_1,int param_2); /* 0x004aabb0 */
undefined4 Text_WrapLines(uint *param_1); /* 0x004aac40 */
void Text_CopyRunes(byte *param_1,undefined4 *param_2,int param_3,int param_4); /* 0x004aae90 */
undefined4 Text_BuildLineTable(undefined4 param_1,int *param_2); /* 0x004aaf30 */
char * text_FindNextBreak(TextContext *param_1,void *param_2,char *param_3,int *param_4, uint *param_5,int param_6); /* 0x004ab210 */
uint __cdecl Font_GlyphAdvance(TextContext *ctx,void *font,int ch); /* 0x004ab510 */
uint Font_GlyphWidth(int param_1,int param_2,uint param_3); /* 0x004ab570 */
void __cdecl Text_DrawString(TextContext *ctx,void *font,char *text); /* 0x004ab5d0 */
void __cdecl Text_DrawChar(void *ctx,void *font,int ch); /* 0x004ab710 */

/* ===== textobject.c ===== */
void __cdecl sputText_AddToQueue(TextObject *obj,int durationMs,int flags); /* 0x0048c470 */
TextObject * __cdecl TextObject_New(TextContext *ctx,char *text,int durationMs,int flags); /* 0x0048c7e0 */
void __cdecl TextObject_Draw(TextObject *obj,int invalidate); /* 0x0048c9f0 */
TextObject * __cdecl sputText_FindSerialNumber(int serial); /* 0x0048cba0 */

/* ===== controls.c ===== */
int Controls_DebugKeysHook(undefined4 param_1); /* 0x0048d030 */
void sputControl_Reset(void); /* 0x0048d050 */

/* ===== control.c ===== */
void __cdecl sputControl_EnableControl(int control); /* 0x0048d090 */
void __cdecl sputControl_DisableControl(int control); /* 0x0048d0d0 */
undefined * sputControl_Open(void); /* 0x0048d150 */
undefined4 sputControl_Close(void); /* 0x0048d170 */

/* ===== sputcontrol.c ===== */
undefined4 sputControl_Initialize(undefined4 param_1,undefined4 *param_2); /* 0x0048d100 */
void sputControl_Terminate(void); /* 0x0048d2c0 */
undefined4 sputControl_Startup(void); /* 0x0048d2e0 */
void sputControl_Shutdown(void); /* 0x0048d330 */

/* ===== debug.c ===== */
undefined4 sputControl_StandardHandler(void); /* 0x0048d210 */

/* ===== sputresource.c ===== */
undefined * __cdecl sputResource_Initialize(uint param_1,undefined **param_2); /* 0x0048d4e0 */
void sputResource_Terminate(void); /* 0x0048d770 */
int sputResource_Startup(void); /* 0x0048d790 */
void sputResource_Shutdown(void); /* 0x0048d830 */

/* ===== actors.c ===== */
void sputActor_NukeCostumeStacks(void); /* 0x0048e240 */
void __cdecl sputActor_UpdateSpeechOnly(float dt); /* 0x0048fcc0 */
void __cdecl sputActor_UpdateActors(float dt); /* 0x0048fcf0 */

/* ===== sputactor.c ===== */
undefined4 sputActor_Initialize(uint param_1,undefined4 *param_2); /* 0x0048e2c0 */
undefined4 sputActor_Save(code *param_1); /* 0x0048e330 */
undefined4 sputActor_Restore(code *param_1); /* 0x0048ecd0 */
void __cdecl sputActor_SetWalkChore(Actor *actor,int chore,CostumeNode *costume); /* 0x00490a60 */
void sputActor_Terminate(void); /* 0x00490e60 */
undefined4 sputActor_Startup(void); /* 0x00490e80 */
void sputActor_Shutdown(void); /* 0x00490ef0 */

/* ===== phoneme.c ===== */
uint __cdecl Phoneme_ToTalkChore(void *unused,int phoneme); /* 0x00490e00 */
int ComparePhonemes(int *param_1,int *param_2); /* 0x00490e50 */

/* ===== walker.c ===== */
undefined4 __cdecl sputActor_AlignToPuck(Actor *actor,float *param_2); /* 0x00491230 */
void __cdecl sputActor_ActorWalkTo(Actor *actor,int param_2,undefined4 *param_3,undefined4 param_4); /* 0x00491650 */
uint Walker_AvoidActorPath (Actor *param_1,Actor *param_2,undefined4 *param_3,uint param_4,float *param_5); /* 0x004917e0 */
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
uint GetPath(undefined4 *param_1); /* 0x004a9420 */
undefined4 BuildPath(float *param_1,float *param_2,int param_3); /* 0x004a9430 */
undefined4 __cdecl Planner_FindPath(float *param_1,float *param_2,WalkPlane *plane); /* 0x004a94d0 */
uint __cdecl FindExitPoints(WalkPlane *plane,float *param_2,uint *param_3); /* 0x004a96f0 */
undefined4 __cdecl Planner_PortalPoint(WalkPlane *planeA,WalkPlane *planeB,float *point,float *out); /* 0x004a9920 */
undefined4 TightenPath(void); /* 0x004a9aa0 */
WalkPlane * __cdecl Planner_SharedSector(float *from,float *to); /* 0x004a9ca0 */

/* ===== collision.c ===== */
void GetOuttaTheBox(float *param_1,float param_2,float param_3,float param_4,float param_5, float param_6,float param_7,float *param_8,float *param_9); /* 0x004922d0 */
undefined4 __cdecl Collision_PointInBox (float *a,float *b,float *p3,float bx0,float by0,float bz0,float bx1,float by1,float bz1, float *p10,float *offset); /* 0x00492510 */
void FindObjectCorners(int param_1,float param_2,float *param_3,float param_4,float *param_5); /* 0x004925c0 */
undefined4 TestCollision(float *param_1,float *param_2,float *param_3,float param_4,float param_5, undefined4 param_6,float param_7,float param_8,undefined4 param_9,float *param_10); /* 0x00492680 */
int Collision_PickDetour(float *param_1,float *param_2,int param_3); /* 0x00492a50 */
undefined4 Collision_UpdateMovedActors(void); /* 0x004939a0 */
undefined4 Collision_TestActorAgainstOthers(Actor *param_1); /* 0x004939f0 */
undefined4 Collision_BoxSlide(float *param_1,float *param_2,float param_3,float param_4,float param_5, float param_6,float param_7,float param_8,float *param_9); /* 0x00494100 */

/* ===== speech.c ===== */
void __cdecl sputActor_SetSpeechMode(int mode); /* 0x004931c0 */
uint sputActor_GetSpeechMode(void); /* 0x004931e0 */

/* ===== costume.c ===== */
void FadeInChore(void *param_1,uint param_2,int param_3); /* 0x00493410 */
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
void sputCostume_Draw2D(int param_1); /* 0x004956f0 */
void __cdecl sputCostume_Update(CostumeNode *costumeList,float dt); /* 0x00495730 */
undefined4 sputCostume_SaveHook(char *param_1,uint *param_2,undefined4 param_3); /* 0x00495e90 */
undefined4 Costume_InstanceHook(int param_1,int param_2); /* 0x00496020 */

/* ===== shadow.c ===== */
void __cdecl sputCostume_SetShadowColor(int r,int g,int b); /* 0x00494890 */
void __cdecl sputCostume_OutputShadowPoly(float *verts,int count,float *minXY,float *maxXY,ActorShadow *shadow); /* 0x00494bf0 */

/* ===== sputcostume.c ===== */
int sputCostume_Initialize(GrimServices *param_1,undefined4 *param_2); /* 0x004957f0 */
void sputCostume_Terminate(void); /* 0x00495960 */
undefined4 sputCostume_Startup(void); /* 0x004959a0 */
void sputCostume_Shutdown(void); /* 0x004988a0 */

/* ===== component.c ===== */
void BitmapChanger(undefined4 param_1,int *param_2,undefined4 param_3,int param_4); /* 0x00496060 */

/* ===== bitmapcomponent.c ===== */
undefined4 BitmapRequester(uint param_1,int param_2,int param_3,int param_4,char *param_5); /* 0x004960a0 */
undefined4 BitmapFreer(undefined4 param_1,undefined4 param_2,void *param_3); /* 0x00496340 */

/* ===== cmapcomponent.c ===== */
int * __cdecl ColormapInstancer(int inst,int component,int create); /* 0x00496370 */
int ColormapRequester(uint param_1,int param_2,int param_3,int param_4,char *param_5); /* 0x00496460 */
undefined4 ColormapFreer(undefined4 param_1,undefined4 param_2,void *param_3); /* 0x00496580 */
undefined4 MaterialInstanceSaveLoad(void); /* 0x004965b0 */

/* ===== materialcomponent.c ===== */
void MaterialChanger(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4); /* 0x004965d0 */
void * __cdecl MaterialInstancer(void *cosInst,int componentIdx,int create); /* 0x004965e0 */
int MaterialRequester(uint param_1,int param_2,int *param_3,int param_4,char *param_5); /* 0x00496670 */

/* ===== modelcomponent.c ===== */
undefined4 ThingAdjuster(int *param_1,undefined4 param_2); /* 0x00496890 */
void ThingChanger(undefined4 param_1,int param_2,undefined4 param_3,int param_4); /* 0x00496930 */
void * __cdecl ThingInstancer(void *cosInst,int componentIdx,int create); /* 0x00496950 */
undefined4 ThingStopper(int param_1); /* 0x00496b40 */
int ThingRequester(uint param_1,int param_2,int param_3,int param_4,char *param_5); /* 0x00496b60 */
undefined4 ThingFreer(undefined4 param_1,undefined4 param_2,void *param_3); /* 0x00496d10 */

/* ===== meshcomponent.c ===== */
void MeshChanger(undefined4 param_1,int *param_2,undefined4 param_3,int param_4); /* 0x00496d40 */
int * __cdecl MeshInstancer(int inst,int component,int create); /* 0x00496d70 */
void MeshStopper(int param_1); /* 0x00496e10 */
undefined4 MeshRequester(uint param_1,int param_2,int *param_3,int param_4,char *param_5); /* 0x00496e20 */
int MeshAdjuster(undefined4 param_1,undefined4 param_2); /* 0x00497180 */

/* ===== imusesoundcomponent.c ===== */
void __cdecl SoundChanger(int tag,int snd,undefined4 param_3,int slot,uint param_5,uint param_6,uint param_7, uint inst); /* 0x004971a0 */
undefined4 SoundAdjuster(int *param_1,undefined4 param_2); /* 0x00497320 */
int SoundRequester(uint param_1,int param_2,int param_3,int param_4,char *param_5); /* 0x00497460 */
undefined4 SoundFreer(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x00497640 */
undefined4 SoundStopper(int param_1); /* 0x00497660 */

/* ===== luavarcomponent.c ===== */
void LuaVarChanger(undefined4 param_1,char *param_2,undefined4 param_3,int param_4); /* 0x00497680 */
undefined4 LuaVarAdjuster(undefined4 *param_1,int param_2,int param_3); /* 0x004976a0 */
int LuaVarRequester(uint param_1,int param_2,int param_3,int param_4,int param_5); /* 0x00497710 */
undefined4 LuaVarFreer(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x004977f0 */
undefined4 LuaVarStopper(char *param_1); /* 0x00497810 */

/* ===== imuseintcomponent.c ===== */
int IMuseRequester(uint param_1,int param_2,int param_3,int param_4); /* 0x00497840 */

/* ===== keyframecomponent.c ===== */
void KeyframeChanger(undefined4 param_1,int *param_2,undefined4 param_3,int param_4,uint param_5, undefined4 param_6,undefined4 param_7,undefined4 param_8); /* 0x00497890 */
void sputCostume_PuppetHook(int param_1,int param_2,uint param_3); /* 0x00497cb0 */
int * __cdecl KeyframeInstancer(int inst,int component,int create); /* 0x00497d10 */
int KeyframeRequester(uint param_1,int param_2,int param_3,int param_4,uint param_5); /* 0x00497e10 */
undefined4 KeyframeAdjuster(int *param_1,undefined4 param_2); /* 0x00498000 */
undefined4 KeyframeFreer(undefined4 param_1,undefined4 param_2,void *param_3); /* 0x004980b0 */
undefined4 KeyframeStopper(int *param_1); /* 0x004980e0 */

/* ===== smushcomponent.c ===== */
undefined4 SmushFreer(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x00498140 */
void SmushChanger(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4); /* 0x00498160 */
int SmushRequester(uint param_1,int param_2,int param_3,int param_4,char *param_5); /* 0x00498190 */

/* ===== costumetag.c ===== */
undefined4 CostumeTag_Nop(void); /* 0x00498180 */

/* ===== spritecomponent.c ===== */
undefined4 SpriteRequester(uint param_1,int param_2,int param_3,float param_4,char *param_5); /* 0x00498280 */
void SpriteChanger(undefined4 param_1,int param_2,undefined4 param_3,int param_4); /* 0x00498550 */
undefined4 SpriteFreer(undefined4 param_1,undefined4 param_2,int *param_3); /* 0x00498580 */
undefined4 * SpriteInstancer(int param_1,undefined4 *param_2,int param_3); /* 0x004985c0 */
undefined4 SpriteAdjuster(undefined4 *param_1,undefined4 param_2); /* 0x004986e0 */

/* ===== chore.c ===== */
void __cdecl sputCostume_FadeKeysIn(void *cosInst,int chore,int ms); /* 0x00498990 */
void __cdecl sputCostume_FadeKeysOut(void *cosInst,int chore,int ms); /* 0x00498ad0 */

/* ===== config.c ===== */
void __cdecl Config_GetPath(char *name,char *buf,char *defaultSubdir); /* 0x00498bf0 */
void __cdecl Config_SetPath(char *name,char *value); /* 0x00498cf0 */

/* ===== sputlua.c ===== */
void sputLua_GetActorCostumeL(void); /* 0x0049a1e0 */
void sputLua_GetPointSectorL(void); /* 0x0049c3b0 */
void sputLua_Update(void); /* 0x0049c8f0 */
undefined4 sputLua_Initialize(GrimServices *param_1,undefined4 *param_2); /* 0x0049c9f0 */
void sputLua_FunctionNameL(void); /* 0x0049cbe0 */
void sputLua_TypeOverride(void); /* 0x0049d140 */
void sputLua_Terminate(void); /* 0x0049e500 */
void sputLua_Shutdown(void); /* 0x0049e530 */
void sputLua_StartMovieL(void); /* 0x0049e880 */
void sputLua_RotateVectorL(void); /* 0x0049f0f0 */
void sputLua_ImStartRecording(void); /* 0x004a0f20 */
void sputLua_ImStartSound(void); /* 0x004a0f80 */
void sputLua_ImStopSound(void); /* 0x004a1030 */
void sputLua_ImGetParam(void); /* 0x004a1090 */
void sputLua_ImSetParam(void); /* 0x004a1140 */
void sputLua_ImFadeParam(void); /* 0x004a1260 */
void sputLua_ImStartVoice(void); /* 0x004a1590 */
void __fastcall sputLua_ImSetSequence(undefined4 param_1); /* 0x004a1680 */
void sputLua_ImSetAttribute(void); /* 0x004a1710 */
void sputLua_ImSetVoiceEffect(void); /* 0x004a17b0 */
void sputLua_FadeInChore(void); /* 0x004a2b00 */
void sputLua_SubmitSaveGameData(void); /* 0x004a35d0 */

/* ===== timer.c ===== */
uint sputTime_GetGameTime(void); /* 0x004a3be0 */
uint sputTime_GetFrameTime(void); /* 0x004a3bf0 */
float __cdecl sputTime_GetFrameTimeFlex(void); /* 0x004a3c00 */
void sputTime_Advance(void); /* 0x004a3c10 */
void sputTime_AdvanceManual(uint param_1); /* 0x004a3c80 */
void Timer_Reset(void); /* 0x004a3ce0 */

/* ===== sputtime.c ===== */
undefined4 sputTime_Initialize(undefined4 param_1,undefined4 *param_2); /* 0x004a3d00 */
void sputTime_Terminate(void); /* 0x004a3d50 */
undefined4 sputTime_Startup(void); /* 0x004a3d70 */
void sputTime_Shutdown(void); /* 0x004a3da0 */

/* ===== sound.c ===== */
void sputRoom_RelocateSounds(void); /* 0x004a3fe0 */
void sputRoom_SetSoundPosition (uint param_1,undefined **param_2,uint param_3,uint param_4,uint param_5,uint param_6 ); /* 0x004a40a0 */
void PositionedSounds_DropFinished(void); /* 0x004a4dc0 */
undefined * __cdecl PositionedSound_Add(uint param_1,undefined **param_2,uint param_3,uint param_4,uint param_5, uint param_6); /* 0x004a4e20 */
undefined4 SetSoundPosition(int param_1); /* 0x004a4e80 */
undefined4 sou_engine_GetRate(void); /* 0x004d0c20 */
int __cdecl sou_engine_QueryTime(int voice); /* 0x004d0cf0 */

/* ===== sputroom.c ===== */
undefined * __cdecl sputRoom_Initialize(uint param_1,undefined **param_2); /* 0x004a48c0 */
void sputRoom_Terminate(void); /* 0x004a5390 */
undefined4 sputRoom_Startup(void); /* 0x004a53b0 */
void sputRoom_Shutdown(void); /* 0x004a5430 */
undefined4 sputRoom_ParseLights(void); /* 0x004a5600 */
undefined4 sputRoom_ParseSetups(void); /* 0x004a5890 */

/* ===== zbuffer.c ===== */
void sputRoom_LoadZBuffer(undefined4 param_1); /* 0x004a4920 */
undefined4 ZBuffer_LoadFile(char *param_1); /* 0x004a4930 */
void sputRoom_FreeZBuffer(undefined4 param_1); /* 0x004a4980 */
void ZBuffer_FreeData(void *param_1); /* 0x004a4990 */

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
void SetActorList_Free(void *param_1); /* 0x004a6160 */

/* ===== textmodule.c ===== */
int __cdecl Text_SysInitialize(GrimServices *svc,void *iface); /* 0x004aa7b0 */
void Text_SysTerminate(void); /* 0x004aa810 */
void Text_SysStartup(void); /* 0x004aa820 */
void Text_SysShutdown(void); /* 0x004aa860 */
undefined4 Text_SysSave(code *param_1); /* 0x004aa880 */
undefined4 Text_SysRestore(code *param_1); /* 0x004aa8d0 */

/* ===== glyph.c ===== */
void Glyph_Blit16(int param_1,undefined4 param_2,int *param_3); /* 0x004ab910 */
void Glyph_Blit8(int param_1,int param_2,int *param_3); /* 0x004ab9d0 */
void Glyph_Blit16Clipped(int param_1,undefined4 param_2,int *param_3); /* 0x004abae0 */
void Glyph_Blit8Clipped(int param_1,int param_2,int *param_3); /* 0x004abc80 */

/* ===== platmodule.c ===== */
int Graph_SysInitialize(GrimServices *svc,void *iface); /* 0x004abe90 */
void Graph_SysTerminate(void); /* 0x004abef0 */
undefined4 Graph_SysStartup(void); /* 0x004abf00 */
void Graph_SysShutdown(void); /* 0x004abf30 */

/* ===== crt.c ===== */
int _stricmp(byte *param_1,byte *param_2); /* 0x004ac550 */
int __cdecl sprintf(char *buf,char *fmt,...); /* 0x004ac620 */
longlong __cdecl _ftol(double x); /* 0x004ac6f0 */
int __cdecl _vsnprintf(char *buf,uint n,char *fmt,void *args); /* 0x004ac720 */
int atol(byte *param_1); /* 0x004ac790 */
undefined * __cdecl atoi(uint param_1); /* 0x004ac830 */
uint * strncpy(uint *param_1,uint *param_2,uint param_3); /* 0x004ac840 */
uint strtok(byte *param_1,byte *param_2); /* 0x004ac940 */
void entry(void); /* 0x004aca30 */
void _amsg_exit(undefined4 param_1); /* 0x004acbe0 */
int __cdecl printf(char *fmt,...); /* 0x004acc40 */
undefined4 vsprintf(uint param_1,undefined4 param_2,undefined4 param_3); /* 0x004acca0 */
void exit(undefined4 param_1); /* 0x004acd40 */
void _exit(undefined4 param_1); /* 0x004acd60 */
void doexit(int param_1,int param_2,int param_3); /* 0x004acd80 */
void _lockexit(void); /* 0x004ace40 */
void _unlockexit(void); /* 0x004ace50 */
void _initterm(undefined4 *param_1,undefined4 *param_2); /* 0x004ace60 */
void * _onexit(void *param_1); /* 0x004ace80 */
int atexit(undefined4 param_1); /* 0x004acf10 */
undefined * __cdecl malloc(uint param_1); /* 0x004acf70 */
int _nh_malloc(uint param_1,int param_2); /* 0x004acf90 */
int _heap_alloc(int param_1); /* 0x004acfe0 */
void free(int param_1); /* 0x004ad040 */
undefined4 * realloc(undefined4 *param_1,uint param_2); /* 0x004ad0b0 */
undefined4 _fsopen(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x004ad2c0 */
undefined * __cdecl fopen(uint param_1,uint param_2); /* 0x004ad300 */
undefined4 fclose(int param_1); /* 0x004ad320 */
undefined4 _fclose_lk(int param_1); /* 0x004ad360 */
undefined4 fread(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4); /* 0x004ad3d0 */
uint _fread_lk(undefined4 *param_1,uint param_2,uint param_3,int *param_4); /* 0x004ad410 */
char * fgets(char *param_1,int param_2,undefined4 *param_3); /* 0x004ad550 */
undefined4 fwrite(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4); /* 0x004ad5e0 */
uint _fwrite_lk(char *param_1,uint param_2,uint param_3,int *param_4); /* 0x004ad620 */
undefined4 ftell(undefined4 param_1); /* 0x004ad770 */
uint _ftell_lk(undefined4 *param_1); /* 0x004ad7a0 */
undefined4 fseek(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x004ad950 */
int _fseek_lk(int param_1,int param_2,int param_3); /* 0x004ad990 */
undefined4 vfprintf(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x004ada30 */
void qsort(uint param_1,uint param_2,uint param_3,code *param_4); /* 0x004ada80 */
void shortsort(uint param_1,uint param_2,int param_3,code *param_4); /* 0x004adc30 */
void qsort_swap(undefined1 *param_1,undefined1 *param_2,int param_3); /* 0x004adc90 */
uint bsearch(undefined4 param_1,uint param_2,uint param_3,int param_4,code *param_5); /* 0x004adcc0 */
uint strncmp(char *param_1,char *param_2,int param_3); /* 0x004add60 */
int __cdecl sscanf(char *str,char *fmt,...); /* 0x004adda0 */
uint * strchr(uint *param_1,char param_2); /* 0x004ade30 */
int __cdecl _snprintf(char *buf,uint n,char *fmt,...); /* 0x004adf70 */
char * _strupr(char *param_1); /* 0x004adfe0 */
char * strrchr(char *param_1,char param_2); /* 0x004ae160 */
int __cdecl fprintf(void *fp,char *fmt,...); /* 0x004ae190 */
int wcslen(short *param_1); /* 0x004ae260 */
int tolower(int param_1); /* 0x004ae280 */
uint _tolower_lk(uint param_1); /* 0x004ae310 */
float __cdecl _CIpow(void); /* 0x004ae540 */
float10 _pow(int param_1,uint param_2,int param_3,uint param_4); /* 0x004ae562 */
char * _strlwr(char *param_1); /* 0x004ae760 */
int toupper(int param_1); /* 0x004ae8e0 */
uint _toupper_lk(uint param_1); /* 0x004ae970 */
undefined4 fflush(int param_1); /* 0x004aea70 */
int _fflush_lk(int param_1); /* 0x004aeab0 */
undefined4 _flush(int *param_1); /* 0x004aeaf0 */
uint _flushall(int param_1); /* 0x004aeb70 */
undefined4 * memmove(undefined4 *param_1,undefined4 *param_2,uint param_3); /* 0x004aec30 */
int _findfirst(int param_1,uint *param_2); /* 0x004aeff0 */
undefined4 _findnext(int param_1,uint *param_2); /* 0x004af120 */
undefined4 _findclose(int param_1); /* 0x004af240 */
undefined4 _FileTimeToTime_t(int *param_1); /* 0x004af270 */
void _CallSettingFrame(code *UNRECOVERED_JUMPTABLE); /* 0x004af300 */
undefined * __stdcall _UnwindNestedFrames(int a1,int a2); /* 0x004af350 */
undefined4 __CxxFrameHandler(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4); /* 0x004af3b0 */
void _global_unwind2(int param_1); /* 0x004af660 */
void _local_unwind2(int param_1,int param_2); /* 0x004af6a2 */
undefined4 _unwind_handler(void); /* 0x004af70a */
undefined * __stdcall _NLG_Notify(int a1); /* 0x004af736 */
uint isdigit(int param_1); /* 0x004af750 */
uint isspace(int param_1); /* 0x004af780 */
void _lock(int param_1); /* 0x004af7e0 */
void _unlock(int param_1); /* 0x004af860 */
void _lock_file(uint param_1); /* 0x004af880 */
void _lock_file2(int param_1,int param_2); /* 0x004af8c0 */
void _unlock_file(uint param_1); /* 0x004af8f0 */
void _unlock_file2(int param_1,int param_2); /* 0x004af930 */
uint _flsbuf(uint param_1,int *param_2); /* 0x004af960 */
uint _output(undefined4 param_1,char *param_2,uint *param_3); /* 0x004afa90 */
void write_char(uint param_1,int *param_2,int *param_3); /* 0x004b0420 */
void write_multi_char(undefined4 param_1,int param_2,undefined4 param_3,int *param_4); /* 0x004b0470 */
void write_string(char *param_1,int param_2,undefined4 param_3,int *param_4); /* 0x004b04b0 */
undefined4 get_int_arg(int *param_1); /* 0x004b04f0 */
undefined8 get_short_arg(int *param_1); /* 0x004b0510 */
undefined4 get_int64_arg(undefined4 *param_1); /* 0x004b0530 */
uint _isctype(int param_1,uint param_2); /* 0x004b0b50 */
undefined * __stdcall _allmul(int a1,int a2,int a3,int a4); /* 0x004b0bf0 */
void _initptd(int param_1); /* 0x004b0c90 */
int * _getptd(void); /* 0x004b0cb0 */
void _FF_MSGBANNER(void); /* 0x004b1d20 */
void _NMSG_WRITE(undefined *param_1); /* 0x004b1d60 */
undefined4 _stbuf(uint *param_1); /* 0x004b1f40 */
void _ftbuf(int param_1,undefined4 *param_2); /* 0x004b2000 */
int _msize(int param_1); /* 0x004b2120 */
undefined4 _callnewh(undefined4 param_1); /* 0x004b2190 */
undefined ** __sbh_alloc_new_region(void); /* 0x004b21b0 */
void __sbh_release_region(undefined **param_1); /* 0x004b2320 */
void __sbh_decommit_pages(int param_1); /* 0x004b2380 */
int __sbh_find_block(undefined *param_1,undefined4 *param_2,uint *param_3); /* 0x004b2450 */
void __sbh_free_block(int param_1,int param_2,byte *param_3); /* 0x004b24b0 */
int * __sbh_alloc_block(uint param_1); /* 0x004b2510 */
int __sbh_alloc_new_group(int *param_1,uint param_2,uint param_3); /* 0x004b2750 */
undefined4 __sbh_resize_block(int param_1,int *param_2,byte *param_3,uint param_4); /* 0x004b28d0 */
void time(undefined4 *param_1); /* 0x004b29a0 */
undefined4 * _openfile(undefined4 param_1,char *param_2,undefined4 param_3,undefined4 *param_4); /* 0x004b2a60 */
undefined4 * _getstream(void); /* 0x004b2c30 */
undefined4 _close(uint param_1); /* 0x004b2d10 */
undefined4 _close_lk(uint param_1); /* 0x004b2d80 */
void _freebuf(undefined4 *param_1); /* 0x004b2e10 */
uint _filbuf(undefined4 *param_1); /* 0x004b2e50 */
undefined4 _read(uint param_1,undefined4 param_2,undefined4 param_3); /* 0x004b2f40 */
int _read_lk(uint param_1,char *param_2,int param_3); /* 0x004b2fc0 */
undefined4 _write(uint param_1,undefined4 param_2,undefined4 param_3); /* 0x004b31f0 */
int _write_lk(uint param_1,char *param_2,uint param_3); /* 0x004b3270 */
void _dosmaperr(uint param_1); /* 0x004b3480 */
int _errno(void); /* 0x004b3500 */
int __doserrno(void); /* 0x004b3510 */
undefined4 _lseek(uint param_1,undefined4 param_2,undefined4 param_3); /* 0x004b3520 */
int _lseek_lk(uint param_1,int param_2,int param_3); /* 0x004b35a0 */
uint _input(undefined4 param_1,byte *param_2,uint *param_3); /* 0x004b3620 */
uint _hextodec(uint param_1); /* 0x004b4360 */
uint _inc(undefined4 *param_1); /* 0x004b43a0 */
void _un_inc(int param_1,undefined4 param_2); /* 0x004b43d0 */
undefined4 _whiteout(int *param_1,undefined4 param_2); /* 0x004b43f0 */
uint __crtLCMapStringA(int param_1,uint param_2,int param_3,undefined *param_4,int param_5, int param_6,uint param_7,int param_8); /* 0x004b4560 */
int _strncnt(char *param_1,int param_2); /* 0x004b4790 */
float10 __fastcall _pow_except1(undefined4 param_1,undefined4 param_2,undefined2 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6,uint param_7,uint param_8); /* 0x004b4ba0 */
float10 __fastcall _pow_except2(undefined4 param_1,undefined4 param_2,undefined2 param_3,undefined4 param_4, uint param_5,uint param_6); /* 0x004b4bb7 */
undefined4 _pow_special_cases(double param_1,double param_2,double *param_3); /* 0x004b4d90 */
undefined4 _is_integer_double(double param_1); /* 0x004b4fc0 */
undefined4 _commit(uint param_1); /* 0x004b5050 */
int __loctotime_t(int param_1,int param_2,int param_3,uint param_4,int param_5,int param_6, int param_7); /* 0x004b50f0 */
undefined4 __InternalCxxFrameHandler (int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int *param_5, int param_6,undefined4 param_7,uint param_8); /* 0x004b51e0 */
void FindHandler(int *param_1,int param_2,undefined4 param_3,undefined4 param_4,int param_5, char param_6,undefined4 param_7,undefined4 param_8); /* 0x004b52b0 */
void Eh_FindForeignHandler (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,int param_6,undefined4 param_7,undefined4 param_8); /* 0x004b5570 */
void FrameUnwindToState(int param_1,undefined4 param_2,int param_3,int param_4); /* 0x004b5650 */
void CatchIt(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5, int param_6,int param_7,undefined4 *param_8,undefined4 param_9,int param_10); /* 0x004b5730 */
undefined4 CallCatchBlock(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6,undefined4 param_7); /* 0x004b57c0 */
void Eh_CallCatchBlockInner(void); /* 0x004b58b8 */
void BuildCatchObject(int param_1,int param_2,byte *param_3,byte *param_4); /* 0x004b5950 */
void terminate(void); /* 0x004b5c60 */
void _getbuf(int *param_1); /* 0x004b6ce0 */
uint _isatty(uint param_1); /* 0x004b6d40 */
undefined4 wctomb(undefined4 param_1,undefined4 param_2); /* 0x004b6d70 */
int _wctomb_lk(undefined1 *param_1,ushort param_2); /* 0x004b6de0 */
undefined * __stdcall _aulldiv(int a1,int a2,int a3,int a4); /* 0x004b6e60 */
undefined * __stdcall _aullrem(int a1,int a2,int a3,int a4); /* 0x004b6ed0 */
undefined4 _ld12tocvt(ushort *param_1,uint *param_2,int *param_3); /* 0x004b7370 */
undefined * __cdecl _ld12tod(uint param_1,uint param_2); /* 0x004b7540 */
uint __crtGetStringTypeA(int param_1,int param_2,int param_3,int param_4,uint param_5,uint param_6, int param_7); /* 0x004b7990 */
undefined4 * calloc(int param_1,int param_2); /* 0x004b7ad0 */
undefined4 __crtMessageBoxA(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x004b7b80 */
undefined * __cdecl mktime(uint param_1); /* 0x004b7cb0 */
int _make_time_t(int *param_1,int param_2); /* 0x004b7cc0 */
void __tzset(void); /* 0x004b7f00 */
void _tzset_lk(void); /* 0x004b7f40 */
undefined4 _isindst(undefined4 param_1); /* 0x004b8220 */
int _isindst_lk(int *param_1); /* 0x004b8250 */
void _cvtdate(int param_1,int param_2,uint param_3,int param_4,int param_5,int param_6,int param_7, int param_8,int param_9,int param_10,int param_11); /* 0x004b84c0 */
uint _sopen(int param_1,uint param_2,uint param_3,undefined4 param_4); /* 0x004b8660 */
uint _alloc_osfhnd(void); /* 0x004b8a00 */
undefined4 _set_osfhnd(uint param_1,int param_2); /* 0x004b8b70 */
undefined4 _free_osfhnd(uint param_1); /* 0x004b8c20 */
int _get_osfhandle(uint param_1); /* 0x004b8cc0 */
void _lock_fhandle(uint param_1); /* 0x004b8d10 */
void _unlock_fhandle(uint param_1); /* 0x004b8d80 */
undefined4 mbtowc(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x004b8db0 */
uint _mbtowc_lk(ushort *param_1,byte *param_2,uint param_3); /* 0x004b8e30 */
undefined4 ungetc(undefined4 param_1,undefined4 param_2); /* 0x004b8f50 */
uint _ungetc_lk(uint param_1,int *param_2); /* 0x004b8f80 */
uint _filwbuf(undefined4 *param_1); /* 0x004b9010 */
void _except1(int param_1,int *param_2,ushort *param_3); /* 0x004b9ea0 */
int _ValidateRead(int param_1,int param_2); /* 0x004ba2c0 */
int _ValidateWrite(int param_1,int param_2); /* 0x004ba2e0 */
int _ValidateExecute(int param_1); /* 0x004ba300 */
void abort(void); /* 0x004ba320 */
undefined4 raise(int param_1); /* 0x004ba600 */
uint siglookup(int param_1,uint param_2); /* 0x004ba810 */
undefined4 __addl(uint param_1,uint param_2,uint *param_3); /* 0x004ba850 */
void __add_12(undefined4 *param_1,undefined4 *param_2); /* 0x004ba880 */
void __shl_12(uint *param_1); /* 0x004ba8f0 */
void __shr_12(uint *param_1); /* 0x004ba920 */
void __mtold12(char *param_1,int param_2,uint *param_3); /* 0x004ba950 */
uint __strgtold12(ushort *param_1,int *param_2,byte *param_3,undefined4 param_4,int param_5, int param_6,int param_7); /* 0x004baa50 */
int * gmtime(int *param_1); /* 0x004bb570 */
int * localtime(int *param_1); /* 0x004bb6e0 */
undefined4 wcstombs(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x004bb8d0 */
uint _wcstombs_lk(int param_1,ushort *param_2,uint param_3); /* 0x004bb950 */
int wcsncnt(short *param_1,int param_2); /* 0x004bbb40 */
int getenv(char *param_1); /* 0x004bbb80 */
int _chsize(void); /* 0x004bbc10 */
void _raise_exc(uint *param_1,uint *param_2,byte param_3,uint param_4,uint *param_5,uint *param_6); /* 0x004bbd60 */
int _handle_exc(uint param_1,double *param_2,uint param_3); /* 0x004bc0a0 */
void __ld12mul(int *param_1,int *param_2); /* 0x004bc730 */
void __multtenpow12(undefined2 *param_1,uint param_2,int param_3); /* 0x004bc9f0 */
int _strnicoll(undefined4 param_1,undefined4 param_2,int param_3); /* 0x004bca80 */
undefined4 __crtsetenv_from_wenviron(void); /* 0x004bcac0 */
uint __crtCompareStringA(int param_1,int param_2,byte *param_3,undefined *param_4,byte *param_5, int param_6,uint param_7); /* 0x004bcbb0 */
undefined4 __crtsetenv(char *param_1,int param_2); /* 0x004bce80 */
int findenv(undefined4 param_1,int param_2); /* 0x004bd090 */
undefined4 * copy_environ(int *param_1); /* 0x004bd110 */
byte * _mbschr(byte *param_1,uint param_2); /* 0x004bd180 */
char * _strdup(char *param_1); /* 0x004bd250 */
float __cdecl atof(byte *param_1); /* 0x004d5430 */
int _fdopen(uint param_1,char *param_2); /* 0x004d54e0 */
void rewind(int param_1); /* 0x004d5670 */
void longjmp(int param_1); /* 0x004d59d0 */
undefined4 _setjmp3(undefined4 *param_1,int param_2,int param_3,undefined4 param_4); /* 0x004d5a4c */
undefined * __cdecl _fltin(uint *param_1,int param_2); /* 0x004d5ad0 */

/* ===== crt_unnamed.c ===== */
void FUN_004ac690(void); /* 0x004ac690 */
void FUN_004ac6b0(void); /* 0x004ac6b0 */
void FUN_004acb8d(void); /* 0x004acb8d */
void FUN_004acba2(void); /* 0x004acba2 */
void FUN_004acc10(undefined4 param_1); /* 0x004acc10 */
void FUN_004acd10(void); /* 0x004acd10 */
void FUN_004acf30(void); /* 0x004acf30 */
void FUN_004ad2b0(void); /* 0x004ad2b0 */
int FUN_004addf0(void); /* 0x004addf0 */
short * FUN_004adef0(short *param_1,int param_2,undefined4 param_3); /* 0x004adef0 */
uint * FUN_004ae410(uint *param_1,uint *param_2,uint param_3); /* 0x004ae410 */
float __cdecl FUN_004ae735(void); /* 0x004ae735 */
void FUN_004aeb60(void); /* 0x004aeb60 */
void FUN_004af340(undefined4 param_1,code *UNRECOVERED_JUMPTABLE); /* 0x004af340 */
undefined * FUN_004af3f0(uint param_1,uint param_2,int param_3,int param_4,int param_5); /* 0x004af3f0 */
void FUN_004af450(undefined4 param_1,int param_2,undefined4 param_3); /* 0x004af450 */
undefined4 FUN_004af480(undefined4 *param_1,uint param_2,uint param_3,undefined4 param_4,uint param_5, uint param_6,uint param_7); /* 0x004af480 */
undefined4 FUN_004af550(int param_1,int param_2,undefined4 param_3); /* 0x004af550 */
int FUN_004af5e0(int param_1,int param_2,int param_3,uint *param_4,uint *param_5); /* 0x004af5e0 */
void __fastcall FUN_004af72d(uint param_1); /* 0x004af72d */
void FUN_004af7b0(void); /* 0x004af7b0 */
void FUN_004b0550(void); /* 0x004b0550 */
undefined4 FUN_004b0570(void); /* 0x004b0570 */
undefined * FUN_004b05c0(void); /* 0x004b05c0 */
void FUN_004b05f0(char *param_1); /* 0x004b05f0 */
void FUN_004b0650(char *param_1); /* 0x004b0650 */
undefined4 FUN_004b06c0(double *param_1); /* 0x004b06c0 */
void FUN_004b06e0(int param_1,undefined4 *param_2,undefined4 param_3); /* 0x004b06e0 */
int FUN_004b0740(undefined4 *param_1,int param_2,int param_3,undefined4 param_4); /* 0x004b0740 */
undefined1 * FUN_004b07c0(undefined1 *param_1,int param_2,int param_3,int *param_4,char param_5); /* 0x004b07c0 */
int FUN_004b08c0(undefined4 *param_1,int param_2,int param_3); /* 0x004b08c0 */
undefined1 * FUN_004b0930(undefined1 *param_1,uint param_2,int *param_3,char param_4); /* 0x004b0930 */
void FUN_004b09f0(undefined4 *param_1,int param_2,int param_3,undefined4 param_4); /* 0x004b09f0 */
void FUN_004b0ab0(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4, undefined4 param_5); /* 0x004b0ab0 */
void FUN_004b0b20(char *param_1,int param_2); /* 0x004b0b20 */
undefined4 FUN_004b0c30(void); /* 0x004b0c30 */
undefined4 FUN_004b0d30(undefined4 param_1,undefined4 param_2); /* 0x004b0d30 */
int * FUN_004b0f40(int param_1,int *param_2); /* 0x004b0f40 */
undefined * __cdecl FUN_004b0f80(uint param_1); /* 0x004b0f80 */
undefined4 FUN_004b0fa0(uint param_1,uint param_2,byte param_3); /* 0x004b0fa0 */
void FUN_004b0fe0(void); /* 0x004b0fe0 */
void FUN_004b10d0(void); /* 0x004b10d0 */
void FUN_004b1170(byte *param_1,undefined4 *param_2,byte *param_3,int *param_4,int *param_5); /* 0x004b1170 */
char * FUN_004b1380(void); /* 0x004b1380 */
undefined4 FUN_004b14e0(undefined4 param_1); /* 0x004b14e0 */
uint FUN_004b1710(uint param_1); /* 0x004b1710 */
undefined4 FUN_004b1760(undefined4 param_1); /* 0x004b1760 */
void FUN_004b17c0(void); /* 0x004b17c0 */
void FUN_004b1800(void); /* 0x004b1800 */
void FUN_004b19e0(void); /* 0x004b19e0 */
void FUN_004b19f0(void); /* 0x004b19f0 */
undefined4 FUN_004b1c00(void); /* 0x004b1c00 */
undefined4 FUN_004b1c48(int param_1,int param_2,undefined4 param_3); /* 0x004b1c48 */
void FUN_004b2040(void); /* 0x004b2040 */
void FUN_004b2100(void); /* 0x004b2100 */
uint __thiscall FUN_004b4440(undefined4 param_1,undefined4 *param_2); /* 0x004b4440 */
float10 FUN_004b4ad4(void); /* 0x004b4ad4 */
float10 FUN_004b4b0d(void); /* 0x004b4b0d */
float10 FUN_004b4b0f(void); /* 0x004b4b0f */
unkbyte10 FUN_004b4c00(void); /* 0x004b4c00 */
undefined * FUN_004b4c15(void); /* 0x004b4c15 */
uint __fastcall FUN_004b4c45(undefined4 param_1,int param_2); /* 0x004b4c45 */
undefined * FUN_004b4c9e(void); /* 0x004b4c9e */
undefined * __fastcall FUN_004b4ce9(uint param_1,int param_2); /* 0x004b4ce9 */
void FUN_004b56c6(void); /* 0x004b56c6 */
void FUN_004b56d3(void); /* 0x004b56d3 */
undefined4 FUN_004b5710(undefined4 *param_1); /* 0x004b5710 */
undefined4 FUN_004b5884(void); /* 0x004b5884 */
void FUN_004b58af(void); /* 0x004b58af */
void FUN_004b5b60(int param_1); /* 0x004b5b60 */
int FUN_004b5baa(void); /* 0x004b5baa */
void FUN_004b5bb5(void); /* 0x004b5bb5 */
int FUN_004b5be0(int param_1,int *param_2); /* 0x004b5be0 */
undefined * __stdcall FUN_004b5c10(int a1,int a2,int a3); /* 0x004b5c10 */
undefined4 FUN_004b5caa(void); /* 0x004b5caa */
void FUN_004b5cb0(void); /* 0x004b5cb0 */
void FUN_004b5cd7(void); /* 0x004b5cd7 */
void FUN_004b5cf0(void); /* 0x004b5cf0 */
void FUN_004b5d5e(void); /* 0x004b5d5e */
undefined4 FUN_004b5d80(void); /* 0x004b5d80 */
uint FUN_004b5e30(int param_1); /* 0x004b5e30 */
void FUN_004b61b0(undefined4 *param_1); /* 0x004b61b0 */
uint FUN_004b63f0(char *param_1,int param_2); /* 0x004b63f0 */
undefined4 FUN_004b64f0(void); /* 0x004b64f0 */
void FUN_004b66f0(char *param_1); /* 0x004b66f0 */
undefined4 FUN_004b6730(void); /* 0x004b6730 */
uint FUN_004b6820(int param_1); /* 0x004b6820 */
void FUN_004b6970(int param_1); /* 0x004b6970 */
undefined4 FUN_004b69e0(void); /* 0x004b69e0 */
uint FUN_004b6f50(uint param_1,uint param_2); /* 0x004b6f50 */
void FUN_004b6f90(undefined4 param_1,uint param_2); /* 0x004b6f90 */
uint FUN_004b6fb0(uint param_1); /* 0x004b6fb0 */
void FUN_004b7050(void); /* 0x004b7050 */
undefined4 FUN_004b70e0(int param_1,int param_2); /* 0x004b70e0 */
undefined * __cdecl FUN_004b7150(int param_1,int param_2); /* 0x004b7150 */
undefined * FUN_004b71c0(int param_1,int param_2); /* 0x004b71c0 */
void FUN_004b7260(int param_1,undefined4 *param_2); /* 0x004b7260 */
void FUN_004b7280(undefined4 *param_1); /* 0x004b7280 */
undefined4 FUN_004b7290(int *param_1); /* 0x004b7290 */
void FUN_004b72b0(uint *param_1,int param_2); /* 0x004b72b0 */
void FUN_004b7560(undefined4 param_1,undefined4 param_2); /* 0x004b7560 */
void FUN_004b7580(uint param_1,undefined4 param_2); /* 0x004b7580 */
void FUN_004b75c0(undefined4 param_1,undefined4 param_2); /* 0x004b75c0 */
void FUN_004b7600(char *param_1,int param_2,int param_3); /* 0x004b7600 */
int * FUN_004b76a0(undefined4 param_1,undefined4 param_2,int *param_3,char *param_4); /* 0x004b76a0 */
void FUN_004b7730(uint *param_1,uint *param_2); /* 0x004b7730 */
void FUN_004b77f0(void); /* 0x004b77f0 */
uint FUN_004b7800(int param_1,int param_2,int param_3,int param_4,uint param_5,uint param_6); /* 0x004b7800 */
int FUN_004b7c10(void); /* 0x004b7c10 */
int __fastcall FUN_004b8f30(byte param_1,int param_2); /* 0x004b8f30 */
undefined4 __cdecl FUN_004b9916(undefined4 param_1,uint param_2,ushort param_3,uint param_4,uint param_5,uint param_6, uint param_7,uint param_8,ushort param_9); /* 0x004b9916 */
float10 FUN_004b9b1c(void); /* 0x004b9b1c */
float __cdecl FUN_004b9fc0(undefined4 param_1,undefined4 param_2,short param_3); /* 0x004b9fc0 */
undefined4 FUN_004ba000(int param_1,uint param_2); /* 0x004ba000 */
float __cdecl FUN_004ba060(uint param_1,uint param_2,int *param_3); /* 0x004ba060 */
float __cdecl FUN_004ba170(double param_1); /* 0x004ba170 */
int FUN_004ba190(int param_1,uint param_2); /* 0x004ba190 */
undefined * __stdcall FUN_004ba230(int a1); /* 0x004ba230 */
void FUN_004ba290(void); /* 0x004ba290 */
void FUN_004ba2b0(void); /* 0x004ba2b0 */
undefined4 FUN_004ba340(int param_1,undefined4 param_2,undefined4 param_3,char *param_4); /* 0x004ba340 */
undefined4 FUN_004bb1e0(int param_1,uint param_2,uint param_3,int param_4,byte param_5,short *param_6); /* 0x004bb1e0 */
void FUN_004bc3d0(int param_1); /* 0x004bc3d0 */
int FUN_004bc400(void); /* 0x004bc400 */
int FUN_004bc410(void); /* 0x004bc410 */
int FUN_004bc430(void); /* 0x004bc430 */
void FUN_004bc460(void); /* 0x004bc460 */
uint FUN_004bc4c0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4); /* 0x004bc4c0 */
uint FUN_004bc5f0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4); /* 0x004bc5f0 */
int FUN_004bcb40(uint param_1,int param_2); /* 0x004bcb40 */
undefined4 __cdecl SmushPlay_FakeBlit(uint param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6, uint param_7); /* 0x004bdad0 */
undefined4 grimmem_memory_module(int *param_1,undefined4 param_2); /* 0x004bdf70 */
void grimmem_module_terminate(void); /* 0x004bdfb0 */
void mem_Alloc(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x004bdfe0 */
void mem_Free(undefined4 param_1); /* 0x004be000 */
void mem_Realloc(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4); /* 0x004be020 */
undefined4 grimio_stdio_module(int *param_1,undefined4 param_2); /* 0x004be050 */
void grimio_terminate(void); /* 0x004be090 */
void grimio_Open(undefined4 param_1,undefined4 param_2); /* 0x004be0c0 */
void grimio_Close(undefined4 param_1); /* 0x004be0e0 */
void grimio_Read(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x004be100 */
void grimio_Write(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x004be120 */
void grimio_Tell(undefined4 param_1); /* 0x004be140 */
void grimio_Seek(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x004be160 */
undefined * __stdcall FUN_004bf950(int a1,int a2,int a3,int a4); /* 0x004bf950 */
undefined4 BatchUnsubscribe(int *param_1); /* 0x004c1900 */
undefined4 anm_animplay_module(int *param_1,uint param_2); /* 0x004c1f40 */
void AnimPlay_module_terminate(void); /* 0x004c1fb0 */
undefined4 AnimPlay_module_startup(void); /* 0x004c1ff0 */
void AnimPlay_module_shutdown(void); /* 0x004c2150 */
int anm_EasyPlay(char *param_1,int param_2,uint param_3,undefined4 param_4,undefined4 param_5, undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9, code *param_10,int param_11,int param_12,int param_13); /* 0x004c21e0 */
int anm_GetTime(int param_1); /* 0x004c2590 */
int FUN_004c25c0(void *param_1,int param_2,int param_3,int param_4,int param_5,int param_6, int param_7,int param_8,int param_9,int param_10); /* 0x004c25c0 */
void AnimPlay_anm_Display (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8, undefined4 param_9); /* 0x004c2650 */
void anm_SetRate(undefined4 *param_1,int param_2); /* 0x004c2720 */
void anm_SyncUp(undefined4 *param_1); /* 0x004c2760 */
undefined4 anm_RenderQuery(int param_1); /* 0x004c2780 */
void frame_Timer(undefined4 param_1,int param_2); /* 0x004c2a70 */
void sync_Timer(undefined4 param_1,int param_2); /* 0x004c2a80 */
char * AnimPlay_anm_DebugInfo(int param_1); /* 0x004c2b00 */
void AnimPlay_anm_DebugSetState(uint param_1); /* 0x004c2b30 */
uint AnimPlay_anm_DebugGetState(void); /* 0x004c2b40 */
undefined4 anm_animframe_module(int *param_1,uint param_2); /* 0x004c2b50 */
void AnimFrame_module_terminate(void); /* 0x004c2ba0 */
int AnimFrame_module_startup(void); /* 0x004c2be0 */
void AnimFrame_module_shutdown(void); /* 0x004c2dc0 */
void anm_Reset(void); /* 0x004c2eb0 */
undefined4 anm_DecodeHeader(undefined1 *param_1,int param_2); /* 0x004c2ee0 */
uint anm_DecodeBody(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, uint *param_5,uint *param_6,uint *param_7,uint param_8,undefined4 param_9, undefined4 param_10,byte *param_11,int param_12); /* 0x004c2fa0 */
void anm_PreloadPut(short *param_1,int param_2); /* 0x004c34d0 */
int anm_PreloadGet(int param_1); /* 0x004c3560 */
void AnimFrame_anm_Display (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,byte param_6,byte param_7,uint param_8); /* 0x004c35c0 */
char * AnimFrame_anm_DebugInfo(int param_1); /* 0x004c3660 */
void AnimFrame_anm_DebugSetState(uint param_1); /* 0x004c3690 */
uint AnimFrame_anm_DebugGetState(void); /* 0x004c36a0 */
uint anm_animator_Render(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8, undefined4 param_9,undefined4 param_10,undefined4 param_11); /* 0x004c36f0 */
void FUN_004c3b30(int param_1,undefined4 param_2); /* 0x004c3b30 */
undefined4 FUN_004c3bb0(int param_1); /* 0x004c3bb0 */
undefined4 FUN_004c3c00(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5 ,undefined4 param_6,undefined4 param_7,undefined4 param_8,uint param_9, undefined4 param_10,undefined4 param_11); /* 0x004c3c00 */
void FUN_004c3c90(int param_1,int param_2,void *param_3,uint *param_4); /* 0x004c3c90 */
undefined4 anm_animator_Query(int param_1); /* 0x004c3d00 */
void anm_animator_Quit(int param_1); /* 0x004c3d10 */
void FUN_004c3d90(int param_1,undefined4 param_2,undefined4 param_3); /* 0x004c3d90 */
uint anm_animator_Pause(int param_1,int param_2); /* 0x004c3db0 */
uint FUN_004c4650(int param_1,undefined4 param_2); /* 0x004c4650 */
undefined * FUN_004c4a00(int param_1,int *param_2); /* 0x004c4a00 */
undefined4 fle_streamer_module(int *param_1,uint param_2); /* 0x004c4b20 */
void Streamer_module_terminate(void); /* 0x004c4b60 */
undefined4 Streamer_module_startup(void); /* 0x004c4b90 */
void Streamer_module_shutdown(void); /* 0x004c4c10 */
int fle_StreamerAlloc(undefined4 *param_1,uint param_2,int param_3); /* 0x004c4c50 */
void fle_StreamerFree(int *param_1); /* 0x004c4d20 */
void fle_StreamerReset(undefined4 *param_1); /* 0x004c4d90 */
void fle_StreamerAcquire(uint *param_1,uint param_2); /* 0x004c4dd0 */
undefined4 fle_StreamerStart(int param_1,char *param_2,undefined4 param_3); /* 0x004c4ee0 */
undefined4 FUN_004c4f60(int param_1); /* 0x004c4f60 */
undefined4 fle_StreamerCheck(int param_1); /* 0x004c5080 */
int fle_StreamerDispense(undefined4 *param_1,int param_2); /* 0x004c50a0 */
undefined4 FUN_004c51b0(int param_1); /* 0x004c51b0 */
undefined4 FUN_004c51e0(int param_1,int param_2); /* 0x004c51e0 */
int fle_StreamerQuerySize(int param_1); /* 0x004c5220 */
undefined4 fle_directory_module(int *param_1,uint param_2); /* 0x004c5280 */
void Directory_module_terminate(void); /* 0x004c52c0 */
undefined4 Directory_module_startup(void); /* 0x004c52f0 */
void Directory_module_shutdown(void); /* 0x004c5330 */
void FUN_004c5350(undefined4 param_1,undefined4 *param_2); /* 0x004c5350 */
void FUN_004c5370(undefined4 *param_1); /* 0x004c5370 */
int fle_Exists(int param_1); /* 0x004c5380 */
void fle_Rename(undefined4 param_1,undefined4 param_2); /* 0x004c53b0 */
void fle_Remove(undefined4 param_1); /* 0x004c53d0 */
int fle_DirectoryLoad(undefined4 param_1,int param_2,int param_3,undefined4 param_4,byte param_5); /* 0x004c53e0 */
int fle_DirectoryGetCWD(char *param_1,int param_2); /* 0x004c54f0 */
undefined4 fle_DirectoryGetParent(int param_1,char *param_2); /* 0x004c5570 */
undefined4 fle_DirectoryGetPath(char *param_1,char *param_2,char *param_3,undefined4 param_4); /* 0x004c55d0 */
int fle_VolumeLoadList(int param_1,int param_2); /* 0x004c5720 */
undefined4 fle_zfilio_module(int *param_1,uint param_2); /* 0x004c5790 */
void Zfile_module_terminate(void); /* 0x004c5840 */
undefined4 Zfile_module_startup(void); /* 0x004c5870 */
void Zfile_module_shutdown(void); /* 0x004c5910 */
int * Zfile_fle_Open(char *param_1,char *param_2); /* 0x004c5950 */
int Zfile_fle_Read(int *param_1,undefined4 param_2,int param_3); /* 0x004c5b00 */
undefined4 Zfile_fle_Write(int *param_1,undefined4 param_2,int param_3); /* 0x004c5bc0 */
int Zfile_fle_Tell(int *param_1); /* 0x004c5c20 */
void Zfile_fle_Seek(int *param_1,int param_2,int param_3); /* 0x004c5c50 */
void Zfile_fle_Flush(int *param_1); /* 0x004c5cb0 */
undefined4 fle_stdfile_module(int *param_1,uint param_2); /* 0x004c5ce0 */
void StdFile_module_terminate(void); /* 0x004c5d20 */
undefined4 StdFile_module_startup(void); /* 0x004c5d50 */
void StdFile_module_shutdown(void); /* 0x004c5d90 */
void StdFile_fle_Open(undefined4 param_1,undefined4 param_2); /* 0x004c5db0 */
void StdFile_fle_Close(undefined4 param_1); /* 0x004c5dd0 */
void StdFile_fle_Read(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x004c5df0 */
void StdFile_fle_Write(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x004c5e10 */
void StdFile_fle_Seek(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x004c5e50 */
void StdFile_fle_Flush(undefined4 param_1); /* 0x004c5e70 */
int fle_GetS(undefined4 param_1,int param_2,int param_3); /* 0x004c5ee0 */
void fle_PrintF(undefined4 param_1,undefined4 param_2); /* 0x004c5f80 */
uint fle_GetC(uint param_1); /* 0x004c5fe0 */
uint fle_PutC(undefined4 param_1,uint param_2); /* 0x004c6010 */
uint FUN_004c6db0(int *param_1,int param_2); /* 0x004c6db0 */
void FUN_004c6f10(int *param_1); /* 0x004c6f10 */
uint FUN_004c7040(int *param_1,undefined4 *param_2,uint param_3); /* 0x004c7040 */
uint FUN_004c70c0(int *param_1,int param_2); /* 0x004c70c0 */
char * FUN_004c73f0(int param_1,uint param_2); /* 0x004c73f0 */
uint FUN_004c7570(int *param_1,int param_2); /* 0x004c7570 */
void FUN_004c7b10(undefined4 param_1,undefined4 param_2); /* 0x004c7b10 */
uint FUN_004c8990(uint param_1,byte *param_2,uint param_3); /* 0x004c8990 */
void FUN_004c8ba0(int param_1,undefined4 param_2,undefined4 param_3,int param_4); /* 0x004c8ba0 */
void FUN_004c8e90(int param_1,int param_2,int param_3,int param_4); /* 0x004c8e90 */
void FUN_004c9090(short *param_1,undefined4 *param_2); /* 0x004c9090 */
void FUN_004c92d0(int param_1,int param_2,int param_3); /* 0x004c92d0 */
void FUN_004c9390(int *param_1,int *param_2); /* 0x004c9390 */
void FUN_004c95c0(undefined2 *param_1,int param_2,short *param_3); /* 0x004c95c0 */
void FUN_004c9640(int param_1); /* 0x004c9640 */
void FUN_004c96c0(int param_1,int param_2,int param_3); /* 0x004c96c0 */
void FUN_004c97b0(int param_1,int param_2,int param_3,int param_4); /* 0x004c97b0 */
void FUN_004c9a20(int param_1,int param_2,ushort *param_3); /* 0x004c9a20 */
void FUN_004c9fa0(int param_1,int param_2,int param_3); /* 0x004c9fa0 */
void FUN_004ca3f0(int param_1); /* 0x004ca3f0 */
uint FUN_004ca460(uint param_1,int param_2); /* 0x004ca460 */
undefined4 fob_flobdec_wave_module(int *param_1,uint param_2); /* 0x004cba30 */
void DWave_module_terminate(void); /* 0x004cba70 */
int DWave_module_startup(void); /* 0x004cbaa0 */
void DWave_module_shutdown(void); /* 0x004cbb30 */
char * DWave_flobdec_Info(int param_1); /* 0x004cbb80 */
undefined4 DWave_flobdec_GetID(void); /* 0x004cbbb0 */
undefined4 DWave_flobdec_GetType(void); /* 0x004cbbc0 */
void DWave_flobdec_Reset(void); /* 0x004cbbd0 */
undefined4 DWave_flobdec_DecodeHeader(int param_1); /* 0x004cbbe0 */
undefined4 __cdecl DWave_flobdec_DecodeBody (uint param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint *param_6); /* 0x004cbc00 */
undefined4 FUN_004cbf40(void); /* 0x004cbf40 */
void VbrAdpcm_Uncompress(int param_1,undefined1 *param_2,uint param_3,uint param_4); /* 0x004cbf50 */
int FUN_004cd3f0(uint param_1,uint param_2); /* 0x004cd3f0 */
uint sys_GetCount(void); /* 0x004ce010 */
void sys_ExtSync(int param_1); /* 0x004ce020 */
undefined4 bmp_bitmap_module(int *param_1,uint param_2); /* 0x004ce2e0 */
void Video_module_terminate(void); /* 0x004ce320 */
undefined4 Video_module_startup(void); /* 0x004ce350 */
void Video_module_shutdown(void); /* 0x004ce3b0 */
undefined4 bmp_bitmap_AllocRaw(int *param_1,int param_2,int param_3,int param_4,int param_5,undefined4 param_6, undefined4 *param_7); /* 0x004ce840 */
void bmp_bitmap_Free(int *param_1); /* 0x004ce980 */
void gra_SetBitmap(undefined4 *param_1,undefined4 param_2); /* 0x004ce9b0 */
undefined4 gra_ConvertMakeLookup(int param_1,void *param_2,void *param_3,byte *param_4); /* 0x004ced70 */
void sou_mixer_terminate(int *param_1); /* 0x004d2d70 */
float10 FUN_004d54b4(void); /* 0x004d54b4 */
int FUN_004d56f0(void); /* 0x004d56f0 */
undefined4 FUN_004d5740(int param_1); /* 0x004d5740 */
undefined4 FUN_004d57c0(int param_1,int param_2); /* 0x004d57c0 */
undefined4 FUN_004d5800(int param_1); /* 0x004d5800 */
undefined4 FUN_004d5830(undefined4 param_1,undefined4 param_2); /* 0x004d5830 */
char * FUN_004d5860(int param_1,char *param_2,uint param_3); /* 0x004d5860 */
undefined4 FUN_004d5990(uint param_1); /* 0x004d5990 */
undefined * FUN_004d5de0(int a1); /* 0x004d5de0 */
int FUN_004d5e1c(void); /* 0x004d5e1c */
undefined4 FUN_004d5e30(void); /* 0x004d5e30 */
undefined * __stdcall FUN_004d5e35(int a1); /* 0x004d5e35 */
void msc_MemSet(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x004d5e50 */
int msc_error_SaveString(void); /* 0x004d5f70 */
undefined8 __fastcall FUN_004d5fd0(undefined4 param_1,undefined4 param_2,undefined4 *param_3,undefined1 param_4, uint param_5); /* 0x004d5fd0 */
void FUN_004d6030(void); /* 0x004d6030 */
void FUN_004d6046(void); /* 0x004d6046 */
void FUN_004d6050(void); /* 0x004d6050 */
void FUN_004d605b(void); /* 0x004d605b */
void FUN_004d6070(void); /* 0x004d6070 */
void FUN_004d607b(void); /* 0x004d607b */
void FUN_004d6090(void); /* 0x004d6090 */
void FUN_004d609e(void); /* 0x004d609e */
void FUN_004d60ac(void); /* 0x004d60ac */
void FUN_004d60ba(void); /* 0x004d60ba */
void FUN_004d60d0(void); /* 0x004d60d0 */
void FUN_004d60db(void); /* 0x004d60db */
void FUN_004d60e9(void); /* 0x004d60e9 */
void FUN_004d6100(void); /* 0x004d6100 */
void FUN_004d610b(void); /* 0x004d610b */

/* ===== clock.c ===== */
int Clock_ElapsedMs(void); /* 0x004ad260 */

/* ===== strpbrk.c ===== */
int strpbrk_or_strspn(byte *param_1,byte *param_2); /* 0x004ae220 */

/* ===== insane.c ===== */
int SmushPlay_GetMovieTime(void); /* 0x004bd370 */
undefined4 SmushPlay_SysInitialize(uint param_1,undefined4 *param_2); /* 0x004bd3a0 */
void SmushPlay_SysTerminate(void); /* 0x004bd430 */
undefined4 SmushPlay_SysStartup(void); /* 0x004bd440 */
void SmushPlay_SysShutdown(void); /* 0x004bd4d0 */
void SmushPlay_SysSetVideoCallbacks(uint *param_1); /* 0x004bd540 */
undefined4 smushplay_GetInfo(int param_1,int param_2); /* 0x004bd7c0 */
undefined4 Insane_PrepareFrame(int *param_1,undefined4 *param_2,uint *param_3); /* 0x004bdb00 */
undefined8 __fastcall Insane_Blit8To16Doubled (undefined4 param_1,undefined4 param_2,uint *param_3,int param_4,uint *param_5,int param_6 ,int param_7,int param_8); /* 0x004bdca0 */
void Insane_BlitRowsDual(int param_1,int param_2,undefined4 *param_3,int param_4,int param_5, int param_6); /* 0x004bdd50 */
void Insane_BlitRows16(ushort *param_1,int param_2,int param_3,int param_4,int param_5,int param_6); /* 0x004bddb0 */
void __cdecl msc_MemCopy(void *dst,void *src,uint n); /* 0x004c3df0 */
void __cdecl Insane_MemCopy(void *dst,void *src,uint n); /* 0x004c3e10 */

/* ===== smush.c ===== */
undefined4 SmushPlay_Pause(void); /* 0x004bd500 */
undefined4 SmushPlay_Resume(void); /* 0x004bd520 */
void SmushPlay_SysConfigureColorLookup(undefined4 param_1); /* 0x004bd560 */
int __cdecl SmushPlay_StartMovie (char *name,int flags,int bufferSize,int x,int y,int w,int h,int a,int sixteenBit); /* 0x004bd570 */
undefined4 SmushPlay_StopMovie(void); /* 0x004bd930 */
int __cdecl SmushPlay_UpdateMovie(int *outDone); /* 0x004bd970 */
void SmushPlay_SetTranslationTable(uint param_1); /* 0x004bde90 */
undefined4 SmushPlay_GetFrameRect(uint *param_1,uint *param_2); /* 0x004bdea0 */
int __cdecl SmushPlay_GetMovieLength(char *path); /* 0x004bdf00 */

/* ===== lightmgr.c ===== */
void LightMgr_Refresh(void); /* 0x004be310 */
void LightMgr_UpdateDialog(undefined4 param_1); /* 0x004beee0 */

/* ===== lighted.c ===== */
void LightEd_SyncFromSet(void); /* 0x004be3b0 */
void __cdecl LightEd_ResetLight(int index,int mode); /* 0x004be4c0 */
void __cdecl LightEd_DeleteLight(uint index); /* 0x004be560 */
void LightEd_MakeUniqueName(int param_1,char *param_2); /* 0x004be730 */
void LightEd_AddLight(void); /* 0x004be7b0 */
void LightEd_SaveSetFile(void); /* 0x004be990 */
void __cdecl LightEd_WriteLightsSection(void *set,void *file); /* 0x004bed40 */
void LightEd_FillListBox(int param_1); /* 0x004bef10 */
void LightEd_UpdateDialog(int param_1); /* 0x004befe0 */
void LightEd_EnableControls(int param_1); /* 0x004bf2f0 */
void LightEd_SetDlgFloat(int param_1,int param_2,float param_3,int param_4); /* 0x004bf3f0 */
void LightEd_RefreshControl(int param_1,float param_2,undefined4 param_3,int param_4); /* 0x004bf460 */
void __cdecl LightEd_ReadControl(int hdlg,int id); /* 0x004bf560 */
void LightEd_SetLightPosComponent(int param_1,short param_2,undefined4 param_3); /* 0x004bf760 */
void LightEd_SetLightAngle(int param_1,short param_2,uint param_3); /* 0x004bf7d0 */
void LightEd_SetAllEnabled(int param_1); /* 0x004bf850 */
void LightEd_MoveMarkerActor(void); /* 0x004bf8b0 */
void LightEd_GetLightAngles(int param_1,float *param_2); /* 0x004bf930 */
int __stdcall LightEd_KeyboardProc(int code,uint wParam,uint lParam); /* 0x004bffb0 */

/* ===== mixer.c ===== */
undefined4 DSound_Init(void); /* 0x004c0ed0 */
void DSound_Shutdown(void); /* 0x004c1090 */
void __cdecl DSound_SetPrimaryVolume(int volume); /* 0x004c1110 */
void dsn_fill_thread(void); /* 0x004d27d0 */
int DSound_GetPlayBlock(void); /* 0x004d2c60 */
int __cdecl sou_mixer_initialize(int *services,uint tableUnits,int frames); /* 0x004d2d40 */
void __cdecl sou_mixer_mix(byte *data,int accumOffset,uint outFrames,int srcBytes,int unused,int volume,int pan, int format); /* 0x004d2d90 */
void __cdecl sou_mixer_end(short *dst,int frames); /* 0x004d2e60 */
int __cdecl Mixer_InitTables(int *services,uint channels,int frames4,int unused); /* 0x004d2e80 */
int __cdecl Mixer_Free(int *services); /* 0x004d2fb0 */
int sou_mixer_start(void); /* 0x004d3010 */
void __cdecl Mixer_MixVoice(byte *data,int count,int bits,int channels,uint outFrames,int accumOffset,int volume, int pan,int offsetBinary,int byteSwapped); /* 0x004d3040 */
int __cdecl Mixer_ConvertTo16(short *dst,int frames); /* 0x004d31d0 */
void __cdecl Mixer_Mix8MonoLR(byte *src,int count,uint rateFrac,int accumOffset,int volL,int volR); /* 0x004d3240 */
void Mixer_Mix8Mono(byte *param_1,int param_2,uint param_3,int param_4,int param_5); /* 0x004d34a0 */
void Mixer_Mix16MonoLR(short *param_1,int param_2,uint param_3,int param_4,int param_5,int param_6); /* 0x004d36e0 */
void Mixer_Mix16Mono(short *param_1,int param_2,uint param_3,int param_4,int param_5); /* 0x004d38a0 */
void Mixer_MixStereoLR_A(ushort *param_1,int param_2,uint param_3,uint param_4,int param_5, int param_6); /* 0x004d3a60 */
void Mixer_MixStereo_A(ushort *param_1,int param_2,uint param_3,uint param_4,int param_5); /* 0x004d3c40 */
void Mixer_MixStereoLR_B(ushort *param_1,int param_2,uint param_3,uint param_4,int param_5, int param_6); /* 0x004d3e60 */
void Mixer_MixStereo_B(ushort *param_1,int param_2,uint param_3,uint param_4,int param_5); /* 0x004d40d0 */

/* ===== lecshare.c ===== */
undefined ** LecShare_Initialize(undefined *param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4); /* 0x004c1390 */
undefined4 LecShare_Terminate(void); /* 0x004c13f0 */
int LecShare_Startup(void); /* 0x004c1460 */
undefined4 LecShare_Shutdown(void); /* 0x004c1500 */
void LecShare_Reset(uint param_1,uint param_2); /* 0x004c1590 */
int __cdecl LecShare_Publish(char *name,void *vtable); /* 0x004c15c0 */
uint LecShare_Unpublish(undefined4 param_1); /* 0x004c1650 */
void * __cdecl LecShare_Subscribe(char *name,char *pattern); /* 0x004c16c0 */
undefined4 LecShare_Unsubscribe(uint param_1); /* 0x004c1800 */
undefined4 BatchSubscribe(int *param_1,char *param_2); /* 0x004c1850 */
uint GetCatalogEntry(char *param_1,uint param_2); /* 0x004c1990 */
uint GetCatalogCount(char *param_1); /* 0x004c1b60 */
uint * LecShare_FindEntry(undefined4 param_1); /* 0x004c1be0 */
undefined4 LecShare_Nop(void); /* 0x004c1e50 */

/* ===== animplay.c ===== */
int __cdecl anm_Start(void **out,char *name,int fps,int streamArg1,int streamArg2,uint flags); /* 0x004c23c0 */
void __cdecl anm_Stop(void **pp); /* 0x004c2690 */
int __cdecl anm_Render(void *p,int a2,int a3,int a4,int a5,int a6,int a7,int a8,int a9,int a10); /* 0x004c27a0 */
int __cdecl anm_animator_Initialize(void *p); /* 0x004c36b0 */
int __cdecl anm_animator_NewAnim(void *p,char *name,uint flags,int a4,int a5,int a6); /* 0x004c3d30 */

/* ===== zlib.c ===== */
void * __cdecl gz_open(char *path,char *mode,int fd); /* 0x004c3e60 */
void gz_check_header(int *param_1); /* 0x004c4120 */
uint gz_get_byte(undefined4 *param_1); /* 0x004c4280 */
int gz_destroy(int param_1); /* 0x004c42f0 */
int gzread(int *param_1,int param_2,int param_3); /* 0x004c43a0 */
int gzwrite(undefined4 *param_1,undefined4 param_2,int param_3); /* 0x004c45b0 */
uint gz_do_flush(int param_1,undefined4 param_2); /* 0x004c4690 */
uint gzseek(undefined4 *param_1,uint param_2,int param_3); /* 0x004c4750 */
undefined4 gzrewind(undefined4 *param_1); /* 0x004c48a0 */
int gz_getLong(int param_1); /* 0x004c4920 */
undefined4 gzclose(int param_1); /* 0x004c4970 */
void __cdecl gz_putLong(void *file,uint x); /* 0x004c49c0 */
undefined4 zlibVersion(void); /* 0x004c4c40 */
undefined4 fle_zfilio_config(int param_1); /* 0x004c57d0 */
undefined4 inflateReset(int param_1); /* 0x004c6040 */
undefined4 inflateEnd(int param_1); /* 0x004c6090 */
undefined4 inflateInit2_(int param_1,int param_2,char *param_3,int param_4); /* 0x004c60e0 */
undefined * inflate(int *param_1,int param_2); /* 0x004c61f0 */
undefined4 deflateInit2_(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,char *param_7, int param_8); /* 0x004c6640 */
undefined4 deflateReset(int param_1); /* 0x004c6870 */
uint deflate(int *param_1,int param_2); /* 0x004c68f0 */
void putShortMSB(int param_1,undefined4 param_2); /* 0x004c6bb0 */
void flush_pending(int param_1); /* 0x004c6be0 */
uint deflateEnd(int param_1); /* 0x004c6c60 */
void lm_init(int param_1); /* 0x004c6d10 */
uint crc32(uint param_1,byte *param_2,uint param_3); /* 0x004c79b0 */
void zcalloc(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x004c7af0 */
void inflate_blocks_reset(int *param_1,int param_2,int *param_3); /* 0x004c7b20 */
undefined4 * inflate_blocks_new(int param_1,undefined4 param_2,int param_3); /* 0x004c7ba0 */
undefined * __cdecl inflate_blocks(uint *param_1,int *param_2,uint param_3); /* 0x004c7c50 */
undefined4 inflate_blocks_free(int param_1,int param_2); /* 0x004c8940 */
void _tr_init(int param_1); /* 0x004c8ac0 */
void init_block(int param_1); /* 0x004c8b30 */
void _tr_align(int param_1); /* 0x004c8c40 */
void bi_flush(int param_1); /* 0x004ca480 */
void bi_windup(int param_1); /* 0x004ca510 */
void copy_block(int param_1,undefined1 *param_2,int param_3,int param_4); /* 0x004ca580 */
undefined * __cdecl inflate_codes_new(undefined1 param_1,undefined1 param_2,uint param_3,uint param_4,int param_5); /* 0x004ca620 */
undefined * __cdecl inflate_codes(uint param_1,byte *param_2,int param_3); /* 0x004ca660 */
void inflate_codes_free(undefined4 param_1,int param_2); /* 0x004cae10 */
int inflate_trees_bits(undefined4 param_1,int *param_2,undefined4 param_3,undefined4 param_4, int param_5); /* 0x004cae30 */
undefined4 huft_build(int *param_1,uint param_2,uint param_3,int param_4,int param_5,uint *param_6, uint *param_7,int param_8,uint *param_9,uint param_10); /* 0x004caee0 */
int inflate_trees_dynamic (uint param_1,undefined4 param_2,int param_3,int *param_4,int *param_5, undefined4 param_6,undefined4 param_7,undefined4 param_8,int param_9); /* 0x004cb390 */
undefined4 inflate_trees_fixed(uint *param_1,uint *param_2,undefined4 *param_3,undefined4 *param_4); /* 0x004cb520 */
int inflate_flush(int param_1,int param_2,int param_3); /* 0x004cb550 */
undefined4 inflate_fast(int param_1,uint param_2,int param_3,int param_4,int param_5,int *param_6); /* 0x004cb690 */

/* ===== zfile.c ===== */
void __cdecl Zfile_fle_Close(int *z); /* 0x004c5ab0 */

/* ===== stdfile.c ===== */
int __cdecl StdFile_fle_Tell(void *file); /* 0x004c5e30 */
int __cdecl fle_Size(void *file); /* 0x004c5e90 */
int __cdecl fle_Eof(void *file); /* 0x004c5f50 */

/* ===== blocky16.c ===== */
undefined4 fob_flobdec_blocky16_module(int *param_1,uint param_2); /* 0x004cc210 */
int __cdecl fob_flobdec_blocky16_config(int key,...); /* 0x004cc250 */
void Blocky16_module_terminate(void); /* 0x004cc290 */
undefined4 Blocky16_module_startup(void); /* 0x004cc2c0 */
void Blocky16_module_shutdown(void); /* 0x004cc340 */
char * Blocky16_flobdec_Info(int param_1); /* 0x004cc370 */
undefined4 Blocky16_flobdec_GetID(void); /* 0x004cc3a0 */
undefined4 Blocky16_flobdec_DecodeHeader(int param_1); /* 0x004cc3c0 */
int AllocBuffers(int param_1,int param_2,int param_3); /* 0x004cc410 */
void Blocky16_flobdec_Reset(void); /* 0x004cc590 */
void Blocky16_flobdec_DecodeBody (void *param_1,uint *param_2,int param_3,int param_4,int param_5,byte *param_6, undefined4 param_7,byte param_8); /* 0x004cc620 */
undefined4 Blocky16_flobdec_GetVal (short *param_1,int param_2,int *param_3,int *param_4,int *param_5,int *param_6); /* 0x004cc650 */
void fob_blk16_configure(uint param_1); /* 0x004cc6a0 */
void __cdecl fob_block_maketiles(int size); /* 0x004cc7d0 */
int __cdecl Blocky16_DecodeFrame(void *dst,uint *clip,int x,int y,int palette,byte *hdr,byte flags); /* 0x004ccd00 */
void Blocky16_BuildExpandTable(void *param_1); /* 0x004cd1e0 */
void Blocky16_DecodeHalfRows16(void *param_1,ushort *param_2,int param_3,int param_4); /* 0x004cd300 */
void Blocky16_DecodeHalfRows8(void *param_1,byte *param_2,int param_3,int param_4,int param_5); /* 0x004cd450 */
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
int sys_GetTime(void); /* 0x004ce000 */
void InsaneTimer_Tick(void); /* 0x004ce060 */
void sys_timer_dispatcher(void); /* 0x004ce1d0 */
void InsaneTimer_RunDeferred(void); /* 0x004ce260 */

/* ===== videobitmap.c ===== */
int __cdecl bmp_bitmap_Alloc(void *out,int width,int height,int format); /* 0x004ce3e0 */
int __cdecl gra_ConvertCopy(byte *src,void *srcFmt,int count,byte *palette,byte *dst,void *dstFmt, byte *expandTable); /* 0x004cedc0 */

/* ===== video.c ===== */
void gra_BlitRectLookup(int *param_1,uint *param_2,int param_3,int param_4,int *param_5, byte *param_6,byte *param_7); /* 0x004cea30 */
void gra_SetBuffer(char *param_1,int param_2,int param_3,char *param_4); /* 0x004cec40 */
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
void msc_rle_DecompressBlock(undefined1 *param_1,undefined4 param_2,int param_3); /* 0x004d5e70 */
void msc_rle_DecompressInitialize(int *param_1); /* 0x004d5eb0 */
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
