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
void __cdecl Win_AbortIfAlreadyRunning (void *hInstance,void *hPrevInstance,char *cmdLine,int nCmdShow,char *appName); /* 0x004abf40 */
uint Win_PumpMessages(void); /* 0x004ac020 */
int __cdecl Win_SetWindowedSize(int fullscreen,int w,int h); /* 0x004ac100 */
void Win_AddMessageHook(void *param_1); /* 0x004ac160 */
undefined4 Win_RemoveMessageHook(void *param_1); /* 0x004ac1a0 */
undefined4 Win_CreateMainWindow(uint param_1,undefined4 param_2,int param_3); /* 0x004ac1f0 */
undefined * __stdcall Win_KernelWndProc(int a1,int a2,int a3,int a4); /* 0x004ac340 */
int __cdecl Win_IsFocusWithin(void *hwnd); /* 0x004bff70 */

/* ===== debuglog.c ===== */
void __cdecl DebugLog_Init(int enable); /* 0x00401040 */
undefined4 DebugLog_Load(void); /* 0x004020a0 */
void DebugLog_Write(char *param_1,undefined4 param_2); /* 0x00402560 */

/* ===== grim.c ===== */
int __cdecl Grim_FindDataOnDrives(char *subdir); /* 0x00401140 */
undefined4 Grim_Init(char *param_1); /* 0x004012b0 */
void __cdecl Grim_DecodeRegKeyName(char *s); /* 0x00401640 */
int Grim_FatalMessageBox(int param_1,int param_2,int param_3,int param_4); /* 0x004018b0 */
void Grim_ShutdownDisplay(void); /* 0x00401900 */
void Grim_Shutdown(void); /* 0x00401950 */
void Grim_EnumDisplayModes(void); /* 0x00401a50 */
undefined4 Grim_OnDisplayModeChange(void *param_1,int param_2); /* 0x00402060 */
int __cdecl Grim_ParseCommandLine(char *cmdline); /* 0x00402c80 */
void Grim_OpenRegistry(void); /* 0x004034b0 */
void Grim_ShowSplash(void); /* 0x00403520 */

/* ===== game.c ===== */
void Game_FrameUpdate(void); /* 0x004016a0 */

/* ===== lua.c ===== */
void Lua_Is3DHardwareEnabled(void); /* 0x00401ca0 */
void Lua_SetHardwareState(void); /* 0x00401cc0 */
void Lua_GetVideoDevices(void); /* 0x00401d30 */
void Lua_SetVideoDevices(void); /* 0x00401da0 */
void Lua_Enumerate3DDevices(void); /* 0x00401e90 */
void Lua_EnumerateVideoDevices(void); /* 0x00401fb0 */
void FUN_00402050(void); /* 0x00402050 */
void Lua_NextSetup(void); /* 0x00482880 */
void Lua_PreviousSetup(void); /* 0x004828a0 */
void Lua_IrisClear(void); /* 0x00486f50 */
void Lua_DrawLine(void); /* 0x00489840 */
void Lua_DrawPolygon(void); /* 0x00489a80 */
void Lua_DrawRectangle(void); /* 0x00489d70 */
void Lua_ChangePrimitive(void); /* 0x00489fe0 */
void __cdecl Lua_KillPrimitive(void); /* 0x0048a460 */
void Lua_PurgePrimitiveQueue(void); /* 0x0048a4a0 */
void Lua_SetOffscreenTextPos(void); /* 0x0048ad60 */
void Lua_SetEmergencyFont(void); /* 0x0048ade0 */
void Lua_LocalizeString(void); /* 0x0048ae60 */
void Lua_MakeColor(void); /* 0x0048aed0 */
void Lua_GetColorComponents(void); /* 0x0048b100 */
void Lua_SetActorTalkColor(void); /* 0x0048b190 */
void Lua_GetActorTalkColor(void); /* 0x0048b230 */
void Lua_SetSayLineDefaults(void); /* 0x0048b2a0 */
void Lua_SayLine(void); /* 0x0048b4c0 */
void Lua_ParseSayLineTable (undefined4 param_1,int *param_2,int *param_3,int *param_4,int *param_5,int *param_6); /* 0x0048b6a0 */
void Lua_PrintLine(void); /* 0x0048b830 */
void Lua_IsMessageGoing(void); /* 0x0048b9a0 */
void Lua_ExpireText(void); /* 0x0048ba90 */
void Lua_PurgeText(void); /* 0x0048baf0 */
void Lua_KillTextObject(void); /* 0x0048bb20 */
void Lua_GetFontDimensions(void); /* 0x0048bb70 */
void Lua_GetTextObjectDimensions(void); /* 0x0048bbc0 */
void Lua_GetTextCharPosition(void); /* 0x0048bc50 */
void Lua_ChangeTextObject(void); /* 0x0048bd10 */
void Lua_MakeTextObject(void); /* 0x0048be30 */
void Lua_BlastText(void); /* 0x0048bf50 */
void Lua_GetTranslationMode(void); /* 0x0048c960 */
void Lua_SetTranslationMode(void); /* 0x0048c980 */
void Lua_GetKeyLength(void); /* 0x00495850 */
void Lua_GetSmushLength(void); /* 0x00495900 */
void FUN_00495960(void); /* 0x00495960 */
undefined4 FUN_004959a0(void); /* 0x004959a0 */
undefined4 FUN_00495e90(char *param_1,undefined4 param_2,undefined4 param_3); /* 0x00495e90 */
undefined4 FUN_00496020(undefined4 param_1,int param_2); /* 0x00496020 */
void Lua_Stub(void); /* 0x00497830 */
bool FUN_00497840(undefined4 param_1,int param_2,int param_3,undefined4 param_4); /* 0x00497840 */
void FUN_00497890(undefined4 param_1,int *param_2,undefined4 param_3,int param_4,uint param_5, undefined4 param_6,undefined4 param_7,undefined4 param_8); /* 0x00497890 */
undefined4 * FUN_00497d10(undefined4 param_1,int *param_2,int param_3); /* 0x00497d10 */
bool FUN_00497e10(undefined4 param_1,undefined4 param_2,int param_3,int param_4,uint param_5); /* 0x00497e10 */
undefined4 FUN_00498000(int *param_1,undefined4 param_2); /* 0x00498000 */
void Lua_GetMemoryUsage(void); /* 0x00498d80 */
void Lua_GetDiskFreeSpace(void); /* 0x00498da0 */
void Lua_TEST(void); /* 0x00498e20 */
void Lua_ShrinkBoxes(void); /* 0x00498e50 */
void Lua_UnShrinkBoxes(void); /* 0x00498e90 */
void Lua_GetShrinkPos(void); /* 0x00498ea0 */
void Lua_SetSoundParameters(void); /* 0x00499000 */
void Lua_GetSoundParameters(void); /* 0x004991c0 */
void Lua_SetDebugKeysCallback(uint param_1); /* 0x00499250 */
void Lua_EnginePause(void); /* 0x00499260 */
void Lua_EngineResume(void); /* 0x00499270 */
void Lua_EngineDisplay(void); /* 0x00499280 */
void Lua_LoadActor(void); /* 0x004992b0 */
void Lua_PutActorAtInterest(void); /* 0x004992d0 */
void Lua_SetSelectedActor(void); /* 0x00499360 */
void Lua_PutActorAt(void); /* 0x004993c0 */
void Lua_PutActorInSet(void); /* 0x004994a0 */
void Lua_WalkActorVector(void); /* 0x00499590 */
void Lua_WalkActorForward(void); /* 0x00499800 */
void Lua_WalkActorTo(void); /* 0x00499860 */
void Lua_WalkActorToAvoiding(void); /* 0x004999d0 */
void Lua_IsActorMoving(void); /* 0x00499b80 */
void Lua_IsActorTurning(void); /* 0x00499be0 */
void Lua_SetActorChoreLooping(void); /* 0x00499c70 */
void Lua_IsActorResting(void); /* 0x00499da0 */
void Lua_IsActorChoring(void); /* 0x00499e20 */
void Lua_GetActorChores(void); /* 0x00499ff0 */
void Lua_GetActorCostumeDepth(void); /* 0x0049a160 */
void Lua_GetActorCostume(void); /* 0x0049a1e0 */
void Lua_GetActorLoopingChores(void); /* 0x0049a2a0 */
void Lua_SetActorColormap(void); /* 0x0049a410 */
void Lua_SetActorCostume(void); /* 0x0049a500 */
void Lua_PrintActorCostumes(void); /* 0x0049a5e0 */
void Lua_PushActorCostume(void); /* 0x0049a640 */
void Lua_PopActorCostume(void); /* 0x0049a6c0 */
void Lua_StopActorChore(void); /* 0x0049a750 */
void Lua_PlayActorChore(void); /* 0x0049a830 */
void Lua_CompleteActorChore(void); /* 0x0049a910 */
void Lua_PlayActorChoreLooping(void); /* 0x0049a9e0 */
void Lua_ActorLookAt(void); /* 0x0049aac0 */
void Lua_IsActorLooking(void); /* 0x0049ad30 */
void Lua_SetActorLookRate(void); /* 0x0049ad90 */
void Lua_GetActorLookRate(void); /* 0x0049ae10 */
void Lua_SetActorVisibility(void); /* 0x0049ae80 */
void Lua_SetActorFollowBoxes(void); /* 0x0049af00 */
void Lua_ShutUpActor(void); /* 0x0049af80 */
void Lua_SetActorFrustrumCull(void); /* 0x0049afd0 */
void Lua_GetCameraActor(void); /* 0x0049b040 */
void Lua_GetActorWalkRate(void); /* 0x0049b060 */
void Lua_SetActorWalkRate(void); /* 0x0049b0d0 */
void Lua_GetActorTurnRate(void); /* 0x0049b160 */
void Lua_SetActorTurnRate(void); /* 0x0049b1d0 */
void Lua_SetActorWalkChore(void); /* 0x0049b280 */
void Lua_SetActorTurnChores(void); /* 0x0049b350 */
void Lua_SetActorRestChore(void); /* 0x0049b430 */
void Lua_SetActorMumblechore(void); /* 0x0049b500 */
void Lua_SetActorTalkChore(void); /* 0x0049b5a0 */
void Lua_SetActorHead(void); /* 0x0049b6c0 */
void Lua_CanActorSee(void); /* 0x0049b830 */
void Lua_GetVisibleThings(void); /* 0x0049b9e0 */
void Lua_GetActorRect(void); /* 0x0049bb10 */
void Lua_GetActorPuckVector(void); /* 0x0049bba0 */
void Lua_GetActorYawToPoint(void); /* 0x0049bcc0 */
void Lua_SetActorReflection(void); /* 0x0049be40 */
void Lua_GetActorPos(void); /* 0x0049bec0 */
void Lua_GetActorRot(void); /* 0x0049bf30 */
void Lua_SetActorRot(void); /* 0x0049bfa0 */
void Lua_SetActorPitch(void); /* 0x0049c0a0 */
void Lua_SetActorRoll(void); /* 0x0049c110 */
void Lua_TurnActor(void); /* 0x0049c180 */
void Lua_GetActorSector(void); /* 0x0049c200 */
void Lua_IsActorInSector(void); /* 0x0049c2c0 */
void Lua_GetPointSector(void); /* 0x0049c3b0 */
void Lua_IsPointInSector(void); /* 0x0049c4c0 */
bool Lua_RunSystemScript(void); /* 0x0049c5e0 */
int __cdecl Lua_CallSystemFunction(int flag,char *str); /* 0x0049c600 */
void __cdecl Lua_CallCamChangeHandler(int fromSetup,int toSetup); /* 0x0049c660 */
void __cdecl Lua_CallPostCamChangeHandler(int setup); /* 0x0049c6e0 */
void Lua_UpdateFrame(void); /* 0x0049c8f0 */
void Lua_OpenEngineLib(undefined4 param_1,undefined4 param_2); /* 0x0049ca60 */
void Lua_JustLoaded(void); /* 0x0049ca80 */
void Lua_ActorVoiceIs3D(void); /* 0x0049caa0 */
int __cdecl Lua_ResolveCostumeArg(void *luaObj,void *costumeList,void **outCostume); /* 0x0049cb10 */
void Lua_FunctionName(void); /* 0x0049cbe0 */
void Lua_CheckForFile(void); /* 0x0049cca0 */
void Lua_NukeResources(void); /* 0x0049cd10 */
void Lua_DetachFromResources(void); /* 0x0049cd40 */
void Lua_AttachToResources(void); /* 0x0049cd50 */
void Lua_SearchForFileOrSwapCDs(void); /* 0x0049cd60 */
void Lua_Load(void); /* 0x0049cea0 */
void Lua_Save(void); /* 0x0049cef0 */
void Lua_EnableDebugKeys(void); /* 0x0049cf40 */
void Lua_WorldToScreen(void); /* 0x0049cf60 */
void Lua_ScreenToWorld(void); /* 0x0049d030 */
void Lua_TypeOverride(void); /* 0x0049d140 */
void Lua_ConcatFallback(void); /* 0x0049d220 */
void Lua_exit(void); /* 0x0049d3a0 */
void Lua_EnableControl(void); /* 0x0049d3f0 */
void Lua_DisableControl(void); /* 0x0049d430 */
void Lua_GetControlState(void); /* 0x0049d470 */
void __cdecl Lua_CallCostumeOverrideHandler(void *actor,int flag); /* 0x0049d550 */
void __cdecl Lua_CallCostumeMarkerHandler(void *actor,uint marker); /* 0x0049d670 */
void Lua_CallUserPaintHandler(void); /* 0x0049d7b0 */
uint Lua_CallExitHandler(void); /* 0x0049d890 */
uint Lua_CallPauseHandler(void); /* 0x0049d970 */
int __cdecl Lua_CallCharacterHandler(int ch); /* 0x0049da50 */
void Lua_MakeCurrentSetup(void); /* 0x0049db70 */
void Lua_GetCurrentSetup(void); /* 0x0049dbb0 */
void Lua_MakeCurrentSet(void); /* 0x0049dc70 */
void Lua_LockSet(void); /* 0x0049dcb0 */
void Lua_UnLockSet(void); /* 0x0049dd10 */
void Lua_PrintMessage(void); /* 0x0049dd70 */
void Lua_Print_NoOp(void); /* 0x0049ddd0 */
undefined4 Lua_InitGameLibs(void); /* 0x0049de00 */
uint Lua_SaveUserdataHook(int param_1,uint param_2); /* 0x0049dfa0 */
void * Lua_RestoreUserdataHook(int param_1,void *param_2); /* 0x0049e020 */
undefined4 Lua_DispatchControlHandlers(void); /* 0x0049e0b0 */
undefined4 Lua_CreateSystemTable(void); /* 0x0049e380 */
void Lua_CreateControlsTable(undefined4 param_1); /* 0x0049e460 */
void FUN_0049e500(void); /* 0x0049e500 */
void FUN_0049e530(void); /* 0x0049e530 */
void Lua_SetSoundPosition(void); /* 0x0049e590 */
void Lua_StartFullscreenMovie(void); /* 0x0049e7e0 */
void Lua_PauseMovie(void); /* 0x0049e860 */
void Lua_StartMovie(void); /* 0x0049e880 */
void Lua_IsMoviePlaying(void); /* 0x0049e960 */
void __fastcall Lua_FileFindFirst(char *param_1); /* 0x0049e980 */
void Lua_FileFindNext(void); /* 0x0049ea20 */
void Lua_FileFindDispose(void); /* 0x0049ea90 */
void Lua_QueryDialog(void); /* 0x0049eab0 */
void Lua_InputDialog(void); /* 0x0049eb60 */
void Lua_WriteRegistryValue(void); /* 0x0049ec50 */
void Lua_ReadRegistryValue(void); /* 0x0049ece0 */
void Lua_GetSectorOppositeEdge(void); /* 0x0049ed90 */
void Lua_IsSectorActive(void); /* 0x0049ee20 */
void Lua_MakeSectorActive(void); /* 0x0049eeb0 */
void Lua_PreRender(void); /* 0x0049ef50 */
void Lua_GetCurrentScript(void); /* 0x0049efc0 */
void Lua_LockFont(void); /* 0x0049efe0 */
void Lua_LoadCostume(void); /* 0x0049f040 */
void __fastcall Lua_GetPhysicalBytes(undefined4 param_1); /* 0x0049f080 */
void Lua_SetMemoryUsage(void); /* 0x0049f0a0 */
void Lua_RotateVector(void); /* 0x0049f0f0 */
void Lua_GetCameraPosition(void); /* 0x0049f2b0 */
void Lua_GetCameraInterest(void); /* 0x0049f300 */
void Lua_GetCameraFOV(void); /* 0x0049f350 */
void Lua_GetCameraRoll(void); /* 0x0049f380 */
void Lua_SetCameraPosition(void); /* 0x0049f3b0 */
void Lua_SetCameraInterest(void); /* 0x0049f480 */
void Lua_SetActorScale(void); /* 0x0049f550 */
void Lua_SetActorTimeScale(void); /* 0x0049f5d0 */
void Lua_GetActorNodeLocation(void); /* 0x0049f690 */
void Lua_GetActorScale(void); /* 0x0049f810 */
void Lua_GetActorTimeScale(void); /* 0x0049f860 */
void Lua_SetCameraFOV(void); /* 0x0049f8d0 */
void Lua_SetCameraRoll(void); /* 0x0049f930 */
void Lua_GetCameraLookVector(void); /* 0x0049f9b0 */
void Lua_PointActorAt(void); /* 0x0049fb00 */
void Lua_TurnActorTo(void); /* 0x0049fc60 */
void Lua_PerSecond(void); /* 0x0049fdf0 */
void Lua_SnapToPlane(void); /* 0x0049fe40 */
void Lua_GetAngleBetweenVectors(void); /* 0x0049ff00 */
void Lua_GetAngleBetweenActors(void); /* 0x004a00a0 */
void Lua_SetAmbientLight(void); /* 0x004a0230 */
void Lua_FindLight(void); /* 0x004a0290 */
void Lua_TurnLightOn(void); /* 0x004a02f0 */
void Lua_IsLightOn(void); /* 0x004a0380 */
void Lua_SetLightType(void); /* 0x004a0400 */
void Lua_GetLightType(void); /* 0x004a0530 */
void Lua_SetLightPosition(void); /* 0x004a05e0 */
void Lua_GetLightPosition(void); /* 0x004a0760 */
void Lua_SetLightRotation(void); /* 0x004a0800 */
void Lua_GetLightRotation(void); /* 0x004a09a0 */
void Lua_SetLightAngles(void); /* 0x004a0a50 */
void Lua_GetLightAngles(void); /* 0x004a0b40 */
void Lua_PointLightAt(void); /* 0x004a0bd0 */
void Lua_SetLightIntensity(void); /* 0x004a0da0 */
void Lua_GetLightIntensity(void); /* 0x004a0e90 */
void Lua_ImStartRecording(void); /* 0x004a0f20 */
void Lua_ImStartSound(void); /* 0x004a0f80 */
void Lua_ImStopSound(void); /* 0x004a1030 */
void Lua_ImGetParam(void); /* 0x004a1090 */
void Lua_ImSetParam(void); /* 0x004a1140 */
void Lua_ImFadeParam(void); /* 0x004a1260 */
void __fastcall Lua_ImGetMasterVol(undefined4 param_1); /* 0x004a13d0 */
void Lua_ImSetMasterVol(void); /* 0x004a1400 */
void __fastcall Lua_ImGetSfxVol(undefined4 param_1); /* 0x004a1440 */
void Lua_ImSetSfxVol(void); /* 0x004a1470 */
void __fastcall Lua_ImGetVoiceVol(undefined4 param_1); /* 0x004a14b0 */
void Lua_ImSetVoiceVol(void); /* 0x004a14e0 */
void __fastcall Lua_ImGetMusicVol(undefined4 param_1); /* 0x004a1520 */
void Lua_ImSetMusicVol(void); /* 0x004a1550 */
void Lua_ImStartVoice(void); /* 0x004a1590 */
void Lua_ImSetState(void); /* 0x004a1640 */
void __fastcall Lua_ImSetSequence(undefined4 param_1); /* 0x004a1680 */
void Lua_ImSetCuePoint(void); /* 0x004a16d0 */
void Lua_ImSetAttribute(void); /* 0x004a1710 */
void Lua_ImSetVoiceEffect(void); /* 0x004a17b0 */
void Lua_ImGetMemoryFootprint(void); /* 0x004a17f0 */
void Lua_ImGetSoundCacheSize(void); /* 0x004a1820 */
void Lua_SetGamma(void); /* 0x004a1850 */
void Lua_SetActorWalkDominate(void); /* 0x004a1890 */
void Lua_SetActorConstrain(void); /* 0x004a1900 */
void Lua_RenderModeUser(void); /* 0x004a1970 */
void Lua_DimScreen(void); /* 0x004a19f0 */
void Lua_DimRegion(void); /* 0x004a1a00 */
void Lua_SetSpeechMode(void); /* 0x004a1ae0 */
void Lua_GetSpeechMode(void); /* 0x004a1b40 */
void Lua_ActorShadow(void); /* 0x004a1b80 */
void Lua_ActivateActorShadow(void); /* 0x004a1bf0 */
void Lua_SetActorShadowPlane(void); /* 0x004a1c90 */
void Lua_SetActorShadowPoint(void); /* 0x004a1d10 */
void Lua_SetActiveShadow(void); /* 0x004a1dc0 */
void Lua_ActorDistToShadowPlane(void); /* 0x004a1e50 */
void Lua_AddShadowPlane(void); /* 0x004a1f30 */
void Lua_SetActorShadowValid(void); /* 0x004a1fd0 */
void Lua_KillActorShadows(void); /* 0x004a2070 */
void Lua_SetShadowColor(void); /* 0x004a20d0 */
void Lua_NewObjectState(void); /* 0x004a2130 */
void Lua_FreeObjectState(void); /* 0x004a21f0 */
void Lua_SendObjectToBack(void); /* 0x004a2240 */
void Lua_SendObjectToFront(void); /* 0x004a22b0 */
void Lua_SetObjectType(void); /* 0x004a2320 */
void Lua_ActorToClean(void); /* 0x004a2380 */
void Lua_SetActorCollisionMode(void); /* 0x004a23e0 */
void Lua_SetActorCollisionScale(void); /* 0x004a2470 */
void Lua_SetActorOffsetYaw(void); /* 0x004a2500 */
void Lua_CacheRect(void); /* 0x004a2590 */
void Lua_RestoreCacheRect(void); /* 0x004a26b0 */
void __fastcall Lua_ResReport(undefined4 param_1); /* 0x004a26f0 */
void Lua_HardwareAccelerated(void); /* 0x004a2720 */
void Lua_SetActorClipActive(void); /* 0x004a2750 */
void Lua_SetActorClipPlane(void); /* 0x004a27b0 */
void Lua_MarkDirtyRect(void); /* 0x004a2920 */
void Lua_FadeOutChore(void); /* 0x004a2a20 */
void Lua_FadeInChore(void); /* 0x004a2b00 */
void Lua_IrisDown(void); /* 0x004a2c10 */
void Lua_IrisUp(void); /* 0x004a2c70 */
void __fastcall Lua_IrisComplete(undefined4 param_1); /* 0x004a2cd0 */
void Lua_TextFileGetLineCount(void); /* 0x004a2d00 */
void Lua_TextFileGetLine(void); /* 0x004a2e20 */
void Lua_ScreenShot(void); /* 0x004a2ee0 */
void Lua_SaveScreen(void); /* 0x004a2f90 */
void Lua_GetSaveGameImage(void); /* 0x004a2fd0 */
void Lua_GetImage(void); /* 0x004a3040 */
void Lua_FreeImage(void); /* 0x004a30e0 */
void Lua_BlastImage(void); /* 0x004a3130 */
void Lua_BlastRect(void); /* 0x004a31f0 */
void __cdecl Lua_CallSaveGameCallback(void *writeFn); /* 0x004a34c0 */
void Lua_SubmitSaveGameData(void); /* 0x004a35d0 */
void Lua_GetSaveGameData(void); /* 0x004a3720 */
void __fastcall Lua_GetTextSpeed(undefined4 param_1); /* 0x004a3830 */
void Lua_SetTextSpeed(void); /* 0x004a3850 */
void Lua_FindFileOnAnyCD(void); /* 0x004a3890 */
void Lua_ActorPuckOrient(void); /* 0x004a3a10 */
void Lua_GetTickCount(void); /* 0x004a3aa0 */
void Lua_SetActorInvClipNode(void); /* 0x004a3ae0 */
void Lua_SetWalkSystemFadeTime(void); /* 0x004a3b80 */
void Lua_LightMgrStartup(void); /* 0x004be180 */
void Lua_LightMgrSetChange(void); /* 0x004be260 */
void Lua_LightMgrShutdown(void); /* 0x004be2a0 */

/* ===== choreface.c ===== */
int __cdecl ChoreFace_Toggle(int show); /* 0x00402120 */
undefined4 FUN_00402200(void); /* 0x00402200 */
void FUN_00402290(undefined4 param_1,int param_2); /* 0x00402290 */
char * FUN_00402330(char *param_1); /* 0x00402330 */
char * FUN_004023a0(char *param_1); /* 0x004023a0 */
char * FUN_00402410(char *param_1); /* 0x00402410 */
char * FUN_00402480(char *param_1); /* 0x00402480 */
char * FUN_004024f0(char *param_1); /* 0x004024f0 */

/* ===== stddisplay.c ===== */
void Display_Shutdown3D(void); /* 0x00402580 */
int __cdecl Display_Select(int deviceIdx,int modeIdx,int threeDIdx); /* 0x004025b0 */
int __cdecl Display_Select3DDevice(int threeDNum); /* 0x00402860 */
undefined * Display_InitFromConfig(void); /* 0x00402930 */
int __cdecl Display_GetLastFromRegistry(uint *deviceIdx,uint *modeIdx,uint *threeDIdx); /* 0x004029b0 */
int __cdecl Display_PickDefault(int wantFullscreen,int want3D,int *deviceIdx,int *modeIdx,int *threeDIdx); /* 0x00402b60 */
void stdDisplay_BuildBitmapInfo8 (int param_1,uint param_2,int param_3,int param_4,undefined1 *param_5); /* 0x004730d0 */
void stdDisplay_BuildBitmapInfo16(int param_1,uint param_2,int param_3,int param_4); /* 0x00473180 */
undefined * __cdecl FUN_004731f0(uint param_1,uint param_2,int param_3,uint param_4); /* 0x004731f0 */
undefined4 Palette_SwapRedBlue(int param_1,undefined1 *param_2); /* 0x00473270 */
bool Display_EnumDevices(void); /* 0x00473a40 */
void Display_RestoreMode(void); /* 0x00473b30 */
int __cdecl Display_SelectDevice(int deviceIdx); /* 0x00473c80 */
void Display_CloseDevice(void); /* 0x00474100 */
int __cdecl Display_OpenMode(uint modeIdx,void *palette,int use3D); /* 0x00474140 */
void Display_CloseMode(void); /* 0x00474310 */
void Display_SuspendForDialog(void); /* 0x00474380 */
void Display_ResumeAfterDialog(void); /* 0x004743d0 */
int Display_Flip(void); /* 0x00474420 */
void * __cdecl Surface_Create(void *info,int videoMem,int b,int c); /* 0x00474480 */
void __cdecl Surface_Free(void *surface); /* 0x004746d0 */
void __cdecl Surface_Release(void *surface); /* 0x004746f0 */
int __cdecl Surface_Lock(void *surface); /* 0x00474750 */
int __cdecl Surface_Unlock(void *surface); /* 0x004747b0 */
int __cdecl Surface_Fill(void *surface,int color,int *rect); /* 0x00474800 */
int __cdecl Surface_Blit(void *dst,void *src,int x,int y,int *srcRect,int colorKey); /* 0x00474a60 */
int __cdecl Surface_SetColorKey(void *surface,int color); /* 0x00474ae0 */
void __cdecl Surface_Decompress(void *surface); /* 0x00474b30 */
int __cdecl Surface_CopyConvert(void *src,void *dst); /* 0x00474ba0 */
void * Surface_CreateFromBitmap(int *param_1,void *param_2); /* 0x00474be0 */
int Display_SetDIBPalette(undefined4 param_1); /* 0x00474d10 */
void __cdecl Display_SetPalette(void *palette); /* 0x00474d90 */
int __cdecl Palette_ApplyGamma(void *dst,void *src,int count,int gammaIdx); /* 0x00474dd0 */
int __cdecl Display_DrawText(char *text,int x,int y); /* 0x00474e40 */
uint Display_FindClosestDevice(uint *param_1); /* 0x00475000 */
uint __cdecl Display_FindClosestMode(void *wanted,void *modes,uint count); /* 0x00475090 */
int FUN_00475140(int *param_1,int *param_2); /* 0x00475140 */
int __cdecl Surface_BlitSoftware(void *dst,void *src,uint x,uint y,int *srcRect,uint flags); /* 0x004751b0 */
undefined4 Surface_BlitDDraw(int param_1,int param_2,uint param_3,uint param_4,uint *param_5,byte param_6); /* 0x004755e0 */
undefined4 Surface_BlitLockedSrc (void *param_1,int param_2,void *param_3,uint param_4,int *param_5,void *param_6); /* 0x004758a0 */
undefined4 Surface_BlitLockedDst (int param_1,void *param_2,void *param_3,uint param_4,int *param_5,void *param_6); /* 0x00475c90 */
bool DDraw_Create(undefined4 param_1); /* 0x004760d0 */
void DDraw_Release(void); /* 0x00476190 */
undefined * __stdcall FUN_004761b0(int a1,int a2,int a3,int a4); /* 0x004761b0 */
undefined * __stdcall FUN_00476390(int a1,int a2); /* 0x00476390 */
undefined * __stdcall FUN_004765a0(int a1,int a2); /* 0x004765a0 */
void * DDraw_Get(void); /* 0x004767c0 */
undefined4 DDraw_CreateSurfaces(undefined4 param_1,int *param_2); /* 0x004767d0 */
void DDraw_ReleaseSurfaces(void); /* 0x00476bc0 */
undefined4 DDraw_LockSurface(undefined4 *param_1); /* 0x00476bf0 */
undefined4 DDraw_UnlockSurface(undefined4 *param_1); /* 0x00476c40 */
undefined4 DDraw_Flip(void); /* 0x00476c90 */
undefined4 DDraw_FillSurface(undefined4 *param_1,uint param_2,uint *param_3); /* 0x00476cd0 */
undefined4 DDraw_SetPalette(undefined1 *param_1); /* 0x00476dc0 */
void * __cdecl DIB_CreateSurface(void *mode,void *surface,void *palette,void *hwnd); /* 0x00476e40 */
void DIB_ReleaseSurface(void); /* 0x00476ee0 */
void __cdecl Display_SetPalette3D(void *palette,int flags); /* 0x00478fc0 */
void Palette_FromFloatTable(undefined1 *param_1,undefined4 param_2,int param_3); /* 0x0047b610 */
void __cdecl Pixel_Convert(ushort *dst,int dstFormat,ushort *src,int srcFormat,uint count); /* 0x0047b8a0 */
int Pixel_ConvertOne(int param_1,undefined4 param_2,int param_3); /* 0x0047bbb0 */

/* ===== services.c ===== */
undefined4 __cdecl Svc_Printf(char *fmt,...); /* 0x004035b0 */
undefined4 Svc_Printf2(undefined4 param_1); /* 0x004035e0 */
undefined4 Svc_Warning(undefined4 param_1); /* 0x00403610 */
undefined4 Svc_Error(undefined4 param_1); /* 0x00403640 */
undefined4 Svc_Debug(undefined4 param_1); /* 0x00403670 */
void __cdecl Svc_AssertFail(char *expr,char *file,int line); /* 0x004036a0 */
void Svc_Fn1c(undefined4 param_1); /* 0x004036d0 */
void * __cdecl Svc_Realloc(void *p,uint size); /* 0x004036e0 */
void * __cdecl Svc_Fopen(char *name,char *mode); /* 0x00403710 */
void Svc_Fclose(undefined4 param_1); /* 0x00403730 */
int __cdecl Svc_Fread(void *file,void *buf,int size); /* 0x00403740 */
char * __cdecl Svc_Fgets(void *file,char *buf,int size); /* 0x00403760 */
int __cdecl Svc_Fwrite(void *file,void *buf,int size); /* 0x00403780 */
uint Svc_Feof(int param_1); /* 0x004037a0 */
void Svc_Ftell(undefined4 param_1); /* 0x004037b0 */
int __cdecl Svc_Fseek(void *file,int offset,int whence); /* 0x004037c0 */
int __cdecl Svc_FileSize(char *name); /* 0x004037e0 */
void __cdecl Svc_Fprintf(void *fp,char *fmt,...); /* 0x00403830 */
void * __cdecl Svc_Malloc(uint size); /* 0x00403850 */
void __cdecl Svc_Free(void *p); /* 0x00403860 */
undefined4 Svc_Identity(undefined4 param_1); /* 0x00403870 */
void __cdecl Services_InitDefaults(GrimServices *svc); /* 0x00403880 */
void __cdecl Services_SetCurrent(GrimServices *svc); /* 0x004733a0 */
void Services_Clear(void); /* 0x00473400 */
void Services_InitPlatform(GrimServices *param_1); /* 0x00473420 */
undefined4 __cdecl Svc_DebugPrintf(char *fmt,...); /* 0x00478000 */
void FUN_00478030(uint param_1); /* 0x00478030 */
void FUN_00478040(undefined4 param_1); /* 0x00478040 */
void FUN_00478050(undefined4 param_1,undefined4 param_2); /* 0x00478050 */
undefined4 FUN_00478070(undefined4 param_1); /* 0x00478070 */
void __cdecl Services_InitPlatformTable(GrimServices *svc); /* 0x00478080 */

/* ===== reg.c ===== */
void Reg_Open(void *param_1,uint param_2,char *param_3); /* 0x004038a0 */
void Reg_CacheValueNames(void); /* 0x004039a0 */
int FUN_00403ae0(undefined4 *param_1,undefined4 *param_2); /* 0x00403ae0 */
void Reg_Close(void); /* 0x00403b20 */
void Reg_FreeValueNames(void); /* 0x00403b30 */
int __cdecl Reg_SetInt(char *name,int value); /* 0x00403b80 */
int __cdecl Reg_AddValueName(char *name); /* 0x00403bf0 */
int __cdecl Reg_HasValue(char *name); /* 0x00403cf0 */
int __cdecl Reg_SetFloat(char *name,float value); /* 0x00403d90 */
int __cdecl Reg_GetInt(char *name,int defaultValue); /* 0x00403e00 */
float __cdecl Reg_GetFloat(char *name,float defaultValue); /* 0x00403e90 */
int __cdecl Reg_SetBinary(char *name,void *data,int size); /* 0x00403f20 */
int __cdecl Reg_GetBinary(char *name,void *data,int size); /* 0x00403f90 */
void __cdecl Reg_SetString(char *name,char *value); /* 0x00404010 */
int __cdecl Reg_GetString(char *name,char *buf,int size,char *defaultValue); /* 0x00404070 */
int __cdecl Reg_GetValueType(char *name); /* 0x00404120 */

/* ===== rdroid.c ===== */
int __cdecl rdroid_Startup(GrimServices *svc); /* 0x00404180 */
void rdroid_Shutdown(void); /* 0x004041c0 */
int __cdecl rdroid_Open(int flags); /* 0x004041e0 */
void rdroid_Close(void); /* 0x00404270 */
void rdroid_SetRenderFlags(uint param_1); /* 0x00404290 */
void rdroid_SetGeometryMode(int param_1); /* 0x004042a0 */
void rdroid_SetLightingMode(int param_1); /* 0x004042b0 */
void rdroid_SetTextureMode(int param_1); /* 0x004042c0 */
void rdroid_SetSortMode(int param_1); /* 0x004042d0 */
void rdroid_SetOcclusionMode(int param_1); /* 0x004042e0 */
void rdroid_SetZBufferMode(int param_1); /* 0x004042f0 */
void rdroid_BeginFrame(void); /* 0x00404300 */
void rdroid_EndFrame(void); /* 0x00404320 */
void rdroid_InitCaches(void); /* 0x00404330 */
undefined4 rdroid_SetColormap(uint param_1); /* 0x00404350 */
void rdroid_BuildMathTables(void); /* 0x00404b80 */

/* ===== rdcolormap.c ===== */
undefined4 rdColormap_SetCurrent(uint param_1); /* 0x00404380 */
void * __cdecl rdColormap_Load(char *name); /* 0x004043c0 */
int __cdecl rdColormap_LoadEntry(char *name,void *cmp); /* 0x00404420 */
void rdColormap_Free(undefined4 param_1); /* 0x00404730 */
void rdColormap_FreeEntry(int param_1); /* 0x00404750 */
undefined8 rdColormap_Build16bitTables(undefined2 *param_1,ushort *param_2); /* 0x004047e0 */
undefined4 rdColormap_BuildGreyRamp(undefined4 *param_1); /* 0x00404a40 */
int FUN_00404b30(int param_1); /* 0x00404b30 */

/* ===== rdcanvas.c ===== */
void rdCanvas_InitEdgeTables(void); /* 0x00404c00 */
void rdCanvas_ResetPolyCount(void); /* 0x00404ca0 */
void rdCanvas_ScanConvert(void); /* 0x00404cb0 */
void rdCanvas_EmitSpans(void); /* 0x00404e00 */
void rdCanvas_FlushSpans(void); /* 0x004055d0 */
void rdCanvas_BuildEdgeLists(void); /* 0x00405620 */
undefined4 rdCanvas_PreparePolygon(byte *param_1); /* 0x00405770 */
void __cdecl rdCanvas_DrawLine(void *canvas,int x0,int y0,int x1,int y1,ushort color,uint pattern); /* 0x00451950 */
void rdCanvas_DrawPoint(void *param_1,int param_2,int param_3,undefined4 param_4,float param_5, int param_6,int param_7); /* 0x00451dd0 */
uint * rdCanvas_New(uint param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6, uint param_7,uint param_8); /* 0x004c04f0 */
int __cdecl rdCanvas_Init(uint *canvas,uint flags,uint surface,uint zSurface,uint x0,uint y0,uint x1,uint y1, uint extra); /* 0x004c0550 */
void rdCanvas_Free(int param_1); /* 0x004c0610 */

/* ===== rdcache.c ===== */
void rdCache_BeginScene3D(void); /* 0x00406650 */
void rdCache_EndScene3D(void); /* 0x00406660 */
void rdCache_Reset(void); /* 0x00406670 */
void rdCache_ClearStats(void); /* 0x00406690 */
undefined1 * rdCache_AllocMesh(void); /* 0x004066a0 */
void rdCache_Flush(void); /* 0x00406770 */
int __cdecl rdCache_AddMesh(void *mesh,uint vertexCount,byte flags); /* 0x00406860 */
undefined4 rdCache_DrawMeshList3D(void); /* 0x00406aa0 */
void rdCache_Begin3DBatch(void); /* 0x00407ed0 */
void rdCache_Flush3DBatch(void); /* 0x00407ef0 */
int FUN_00407f90(int param_1,int param_2); /* 0x00407f90 */
int __cdecl rdCache_DrawMesh(void *mesh); /* 0x00407fd0 */
undefined4 FUN_00408800(void); /* 0x00408800 */
int __cdecl rdCache_DrawMeshZ(void *mesh); /* 0x00408af0 */

/* ===== rdmodel.c ===== */
undefined4 rdModel_ComputeMeshLighting(byte *param_1); /* 0x00409580 */
undefined4 FUN_00409d20(int param_1,int param_2); /* 0x00409d20 */
void rdModel_DrawNode(int param_1); /* 0x0040d140 */
void __cdecl rdModel_DrawMesh(void *mesh,float *matrix); /* 0x0040d230 */
undefined4 rdModel_AddMeshToCache(int param_1,undefined4 param_2); /* 0x0040d880 */

/* ===== rdprimit3.c ===== */
void * __cdecl rdPrimit3_DrawPolygon(float *verts,int count,void *material); /* 0x00409d50 */
undefined4 rdPrimit3_DrawLine(float *param_1,float *param_2,int *param_3,int *param_4,int *param_5,int *param_6 ,ushort param_7,uint param_8); /* 0x0040dcc0 */
void rdPrimit3_DrawPoint(float *param_1,float param_2,undefined4 param_3); /* 0x0040dde0 */
void rdPrimit3_ClipFace(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4, uint *param_5,undefined4 *param_6,float *param_7); /* 0x0040deb0 */
void rdPrimit3_CopyFaceVerts (undefined4 param_1,int param_2,undefined4 param_3,uint *param_4,uint *param_5, float *param_6); /* 0x0040e500 */

/* ===== rdcamera.c ===== */
void * __cdecl rdCamera_New(float fov,int type,float aspectX,float aspectY,float zoom); /* 0x00409f50 */
int __cdecl rdCamera_Init(void *camera,float fov,int a,int b,int c,float zoom); /* 0x00409fb0 */
void FUN_0040a080(int param_1); /* 0x0040a080 */
void FUN_0040a0a0(int param_1); /* 0x0040a0a0 */
void __cdecl rdCamera_SetCanvas(void *camera,void *canvas); /* 0x0040a0c0 */
undefined4 rdCamera_SetCurrent(void *param_1); /* 0x0040a0e0 */
void __cdecl rdCamera_SetFov(void *camera,float fov); /* 0x0040a100 */
int __cdecl rdCamera_SetProjectType(void *camera,int type); /* 0x0040a150 */
void __cdecl rdCamera_SetZoom(void *camera,float zoom); /* 0x0040a1d0 */
undefined4 rdCamera_BuildProjection(int *param_1); /* 0x0040a280 */
void __cdecl rdCamera_SetFrame(float *frame); /* 0x0040a430 */
void FUN_0040a470(float *param_1,float *param_2); /* 0x0040a470 */
void FUN_0040a4b0(float *param_1,float *param_2,int param_3); /* 0x0040a4b0 */
void FUN_0040a530(float *param_1,float *param_2); /* 0x0040a530 */
void FUN_0040a570(float *param_1,float *param_2,int param_3); /* 0x0040a570 */
void FUN_0040a5e0(float *param_1,float *param_2); /* 0x0040a5e0 */
void FUN_0040a620(float *param_1,float *param_2,int param_3); /* 0x0040a620 */
void FUN_0040a6a0(float *param_1,float *param_2); /* 0x0040a6a0 */
void FUN_0040a6e0(float *param_1,float *param_2,int param_3); /* 0x0040a6e0 */
void __cdecl rdCamera_SetAmbientLight(void *camera,float ambient); /* 0x0040a750 */
void __cdecl rdCamera_AddLight(void *camera,void *light,float *pos); /* 0x0040a760 */
void rdCamera_ClearCanvas(void); /* 0x0040a7d0 */
void rdCamera_ResetStats(void); /* 0x0040a860 */
int __cdecl rdCamera_ProjectPoint(float *world,float *outScreen); /* 0x0040dc30 */

/* ===== renderer.c ===== */
void Renderer_EnableClipPlane(uint param_1); /* 0x0040a870 */
void Renderer_SetClipPlane(undefined4 *param_1,undefined4 *param_2); /* 0x0040a880 */
void FUN_0040a8c0(undefined4 *param_1); /* 0x0040a8c0 */
undefined4 * FUN_0040a8f0(undefined4 param_1); /* 0x0040a8f0 */
undefined4 FUN_0040a980(int param_1,undefined4 param_2); /* 0x0040a980 */
undefined4 FUN_0040aa20(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,uint param_5, uint param_6,uint param_7,uint param_8); /* 0x0040aa20 */
undefined4 FUN_0040b8e0(int param_1,int param_2); /* 0x0040b8e0 */
void FUN_0040c090(undefined4 param_1); /* 0x0040c090 */
void FUN_0040c0d0(int param_1); /* 0x0040c0d0 */
void FUN_0040c100(int param_1); /* 0x0040c100 */
void FUN_0040c280(int param_1); /* 0x0040c280 */
void FUN_0040c520(uint param_1); /* 0x0040c520 */
void FUN_0040c710(int param_1,int param_2,float *param_3); /* 0x0040c710 */
void FUN_0040c8c0(int param_1); /* 0x0040c8c0 */
void FUN_0040c970(int param_1,int param_2,float *param_3); /* 0x0040c970 */
void FUN_0040cad0(uint param_1); /* 0x0040cad0 */
void FUN_0040cc30(int param_1); /* 0x0040cc30 */
void FUN_0040ce90(int param_1); /* 0x0040ce90 */

/* ===== rdpuppet.c ===== */
void __cdecl rdPuppet_BuildJointMatrices(void *model,float *frame); /* 0x0040cee0 */
undefined4 * rdPuppet_New(void *param_1); /* 0x00450500 */
int __cdecl rdPuppet_Init(void *puppet,void *thing); /* 0x00450560 */
uint __cdecl rdPuppet_AddTrack(void *puppet,uint keyframe,uint lowPri,uint highPri); /* 0x004505a0 */
void __cdecl rdPuppet_StopTrack(void *puppet,int track); /* 0x00450640 */
undefined4 rdPuppet_SetTrackFlags(int param_1,int param_2,uint param_3); /* 0x004506a0 */
void rdPuppet_SetTrackUserData(int param_1,int param_2,undefined4 param_3); /* 0x004506d0 */
undefined4 rdPuppet_PlayTrack(int param_1,int param_2); /* 0x004506f0 */
int __cdecl rdPuppet_FadeInTrack(void *puppet,int track,float seconds); /* 0x00450720 */
int __cdecl rdPuppet_FadeOutTrack(void *puppet,int track,float seconds); /* 0x00450780 */
void __cdecl rdPuppet_AdvanceTrack(void *puppet,int track,float dt); /* 0x004507e0 */
void __cdecl rdPuppet_Advance(void *puppet,float seconds); /* 0x00450a90 */
void rdPuppet_ClearTrackNodes(int param_1,int param_2); /* 0x00450b50 */
void __cdecl rdPuppet_UpdateFrame(void *model,float *frame); /* 0x00450ba0 */
float __cdecl rdKeyframe_Interpolate(void); /* 0x00451510 */
float __cdecl rdKeyframe_InterpolateNode(void); /* 0x00451800 */

/* ===== rdthing.c ===== */
int __cdecl rdThing_Draw(void *thing,float *position); /* 0x0040cf20 */
uint rdThing_New(undefined4 param_1); /* 0x00471a40 */
undefined4 rdThing_Init(undefined4 *param_1,undefined4 param_2); /* 0x00471a80 */
void rdThing_Free(int param_1); /* 0x00471af0 */
void rdThing_FreeEntry(int *param_1); /* 0x00471b10 */
void __cdecl rdThing_SetModel(void *thing,void *model); /* 0x00471bd0 */
undefined4 rdThing_SetCamera(undefined4 *param_1,undefined4 param_2); /* 0x00471d40 */
undefined4 rdThing_SetPolyline(undefined4 *param_1,undefined4 param_2); /* 0x00471d60 */
int __cdecl rdThing_DrawAlt(void *thing,float *frame); /* 0x00471d80 */
void rdThing_BuildNodeMatrix(int param_1,int param_2,float *param_3); /* 0x00471e00 */

/* ===== rdraster.c ===== */
void rdRaster_SetupPoly(float *param_1,int param_2); /* 0x0040ea50 */
void rdRaster_SetupPolyTex(float *param_1,int param_2); /* 0x0040ef90 */
void rdRaster_Select_Flat(float *param_1,int param_2); /* 0x0040f5f0 */
void rdRaster_SpanFlatSetup(int *param_1); /* 0x0040f650 */
void rdRaster_SpanOutline8(int *param_1); /* 0x0040f6d0 */
void rdRaster_SpanOutline16(int *param_1); /* 0x0040f710 */
void rdRaster_EdgeStepFlat(int param_1); /* 0x0040f750 */
undefined4 rdRaster_EdgeSetup_Flat(undefined4 *param_1,int *param_2,int param_3,int param_4); /* 0x0040f770 */
void rdRaster_Select_Flat_2(float *param_1,int param_2); /* 0x0040fa20 */
void rdRaster_SpanTexSetup(int *param_1); /* 0x0040fa80 */
undefined4 rdRaster_EdgeSetup_Flat_2(undefined4 *param_1,int *param_2,int param_3,int param_4); /* 0x0040fbe0 */
void rdRaster_Select_TexLit(float *param_1,int param_2,float param_3); /* 0x0040fe90 */
void rdRaster_SpanLitSetup(int param_1); /* 0x0040ff20 */
undefined4 rdRaster_EdgeSetup_Flat_3(undefined4 *param_1,int *param_2,int param_3,int param_4); /* 0x0040ffe0 */
void rdRaster_Select_FlatLit(float *param_1,int param_2); /* 0x00410290 */
void FUN_00410330(int param_1); /* 0x00410330 */
void FUN_004104b0(int param_1); /* 0x004104b0 */
undefined4 rdRaster_EdgeSetup_Flat_4(undefined4 *param_1,int *param_2,int param_3,int param_4); /* 0x004104e0 */
void rdRaster_Select_FlatLit_2(int *param_1,int param_2); /* 0x004108b0 */
void FUN_00410970(int param_1); /* 0x00410970 */
undefined4 rdRaster_EdgeSetup_Flat_5(undefined4 *param_1,int *param_2,int param_3,int param_4); /* 0x00410d80 */
void rdRaster_Select_FlatLit_3(int *param_1,int param_2); /* 0x00411270 */
void FUN_00411330(int param_1); /* 0x00411330 */
void rdRaster_SpanR8_TexKey(int *param_1); /* 0x004113e0 */
void rdRaster_SpanR16_TexKey(int *param_1); /* 0x004114f0 */
void rdRaster_Select_FlatLit_4(int *param_1,int param_2,float param_3); /* 0x00411630 */
void FUN_00411740(int param_1); /* 0x00411740 */
void FUN_00411b70(int param_1); /* 0x00411b70 */
undefined4 rdRaster_EdgeSetup_Flat_6(undefined4 *param_1,int *param_2,int param_3,int param_4); /* 0x00411ba0 */
void rdRaster_Select_FlatLit_5(int *param_1,int param_2,float param_3); /* 0x00412090 */
void FUN_004121a0(int param_1); /* 0x004121a0 */
void rdRaster_SpanR8_TexKey_2(int *param_1); /* 0x00412280 */
void rdRaster_SpanR16_TexKey_2(int *param_1); /* 0x004123b0 */
void rdRaster_Select_FlatLit_6(int *param_1,int param_2); /* 0x004124f0 */
void FUN_004125c0(int param_1); /* 0x004125c0 */
void FUN_004129f0(int param_1); /* 0x004129f0 */
undefined4 rdRaster_EdgeSetup_Flat_7(undefined4 *param_1,int *param_2,int param_3,int param_4); /* 0x00412a30 */
void rdRaster_Select_FlatLit_7(int *param_1,int param_2); /* 0x00413040 */
void FUN_00413110(int param_1); /* 0x00413110 */
void rdRaster_SpanR8_TexKey_3(int *param_1); /* 0x004131f0 */
void rdRaster_SpanR16_TexKey_3(int *param_1); /* 0x00413340 */
void rdRaster_Select_FlatLit_8(int *param_1,int param_2); /* 0x004134a0 */
void FUN_00413590(int param_1); /* 0x00413590 */
undefined4 rdRaster_EdgeSetup_Flat_8(undefined4 *param_1,int *param_2,int param_3,int param_4); /* 0x004139f0 */
void rdRaster_Select_FlatLit_9(int *param_1,int param_2); /* 0x00413ce0 */
void FUN_00413dd0(int param_1); /* 0x00413dd0 */
void rdRaster_SpanP8_TexKeyZw(uint *param_1); /* 0x00413ee0 */
void rdRaster_SpanP16_TexKeyZw(uint *param_1); /* 0x00414530 */
void rdRaster_Select_FlatLit_10(int *param_1,int param_2,float param_3); /* 0x00414be0 */
void FUN_00414d20(int param_1); /* 0x00414d20 */
void FUN_00415180(int param_1); /* 0x00415180 */
void FUN_004151c0(int param_1); /* 0x004151c0 */
undefined4 rdRaster_EdgeSetup_Flat_9(undefined4 *param_1,int *param_2,int param_3,int param_4); /* 0x004151d0 */
void rdRaster_Select_FlatLit_11(int *param_1,int param_2,float param_3); /* 0x004154c0 */
void FUN_00415600(int param_1); /* 0x00415600 */
void rdRaster_SpanP8_TexKeyZw_2(uint *param_1); /* 0x00415720 */
void rdRaster_SpanP16_TexKeyZw_2(uint *param_1); /* 0x00415dc0 */
void rdRaster_Select_FlatLit_12(int *param_1,int param_2); /* 0x00416470 */
void FUN_00416580(int param_1); /* 0x00416580 */
void FUN_004169f0(int param_1); /* 0x004169f0 */
void FUN_00416a30(int param_1); /* 0x00416a30 */
undefined4 rdRaster_EdgeSetup_Flat_10(undefined4 *param_1,int *param_2,int param_3,int param_4); /* 0x00416a50 */
undefined4 rdRaster_Select_FlatLit_13(int *param_1,int param_2); /* 0x00416e70 */
void FUN_00416f80(int param_1); /* 0x00416f80 */
void rdRaster_SpanP8_TexKeyZw_3(uint *param_1); /* 0x004170a0 */
void rdRaster_SpanP16_TexKeyZw_3(uint *param_1); /* 0x00417790 */
void rdRaster_Grad_Flat(float param_1); /* 0x00418550 */
void rdRaster_Grad_Flat_2(float param_1); /* 0x00418a00 */
void rdRaster_DrawPoints(int param_1,int param_2); /* 0x00418fe0 */
void rdRaster_DrawWireframe(int param_1,int param_2); /* 0x00419150 */
void rdRaster_Draw16_FlatLit(int param_1,int param_2); /* 0x00419450 */
void rdRaster_Span16_Flat(uint *param_1,uint *param_2); /* 0x004195f0 */
undefined4 rdRaster_Edge_Flat(int *param_1); /* 0x00419680 */
undefined4 rdRaster_Edge_Flat_2(int *param_1); /* 0x00419840 */
void rdRaster_Draw16_TexLit(int param_1,int param_2); /* 0x00419a00 */
void rdRaster_Span16_Tex(uint *param_1,uint *param_2); /* 0x00419be0 */
void rdRaster_Draw16_FlatLit_2(int param_1,int param_2,float param_3); /* 0x00419ca0 */
void rdRaster_Span_Flat(uint *param_1,uint *param_2); /* 0x00419e60 */
void rdRaster_Span16_Flat_2(uint *param_1,uint *param_2); /* 0x00419ee0 */
undefined4 rdRaster_Edge_Flat_3(int *param_1); /* 0x00419f70 */
undefined4 rdRaster_Edge_Flat_4(int *param_1); /* 0x0041a130 */
void rdRaster_Draw16_TexLit_2(int param_1,int param_2,float param_3); /* 0x0041a2f0 */
void rdRaster_Span_Tex(uint *param_1,uint *param_2); /* 0x0041a4f0 */
void rdRaster_Span16_Tex_2(uint *param_1,uint *param_2); /* 0x0041a580 */
void rdRaster_Draw_FlatLit(int param_1,int param_2); /* 0x0041a640 */
void rdRaster_Span8_Flat(uint *param_1,uint *param_2); /* 0x0041a810 */
void rdRaster_Span16_Flat_3(uint *param_1,uint *param_2); /* 0x0041a900 */
undefined4 rdRaster_Edge_Flat_5(int *param_1); /* 0x0041aa10 */
undefined4 rdRaster_Edge_Flat_6(int *param_1); /* 0x0041ac60 */
void rdRaster_Draw16_TexLit_3(int param_1,int param_2); /* 0x0041aeb0 */
void rdRaster_Span_Tex_2(uint *param_1,uint *param_2); /* 0x0041b0d0 */
void rdRaster_Span16_Tex_3(uint *param_1,uint *param_2); /* 0x0041b1e0 */
void rdRaster_Draw16_TexLit_4(int param_1,int param_2); /* 0x0041b310 */
void rdRaster_Span_Flat_2(uint *param_1,uint *param_2); /* 0x0041b6f0 */
void rdRaster_Span16_Tex_4(uint *param_1,uint *param_2); /* 0x0041b880 */
undefined4 rdRaster_Edge_Flat_7(int *param_1); /* 0x0041ba30 */
undefined4 rdRaster_Edge_Flat_8(int *param_1); /* 0x0041bd20 */
void rdRaster_Draw16_TexLit_5(int param_1,int param_2); /* 0x0041c010 */
void rdRaster_Span_Tex_3(uint *param_1,uint *param_2); /* 0x0041c260 */
void rdRaster_Span16_Tex_5(uint *param_1,uint *param_2); /* 0x0041c410 */
void rdRaster_Draw16_TexLitKey(int param_1,int param_2); /* 0x0041c5e0 */
void rdRaster_Span_FlatKey(uint *param_1,uint *param_2); /* 0x0041c810 */
void rdRaster_Span16_TexKey(uint *param_1,uint *param_2); /* 0x0041c9b0 */
void rdRaster_Draw16_TexLitKey_2(int param_1,int param_2); /* 0x0041cb80 */
void rdRaster_Span_TexKey(uint *param_1,uint *param_2); /* 0x0041cdd0 */
void rdRaster_Span16_TexKey_2(uint *param_1,uint *param_2); /* 0x0041cf90 */
void rdRaster_Draw_FlatLit_2(int param_1,int param_2,float param_3); /* 0x0041d180 */
void rdRaster_Span16_Tex_6(uint *param_1,uint *param_2); /* 0x0041d560 */
undefined4 rdRaster_Edge_Flat_9(int *param_1); /* 0x0041d710 */
undefined4 rdRaster_Edge_Flat_10(int *param_1); /* 0x0041da00 */
void rdRaster_Draw16_TexLit_6(int param_1,int param_2,float param_3); /* 0x0041dcf0 */
void rdRaster_Span_Tex_4(uint *param_1,uint *param_2); /* 0x0041df60 */
void rdRaster_Span16_Tex_7(uint *param_1,uint *param_2); /* 0x0041e120 */
void rdRaster_Draw_TexLitKey(int param_1,int param_2,float param_3); /* 0x0041e300 */
void rdRaster_Span8_TexKey(uint *param_1,uint *param_2); /* 0x0041e550 */
void rdRaster_Span16_TexKey_3(uint *param_1,uint *param_2); /* 0x0041e700 */
void rdRaster_Draw_TexLitKey_2(int param_1,int param_2,float param_3); /* 0x0041e8d0 */
void rdRaster_Span_TexKey_2(uint *param_1,uint *param_2); /* 0x0041eb40 */
void rdRaster_Span_TexKey_3(uint *param_1,uint *param_2); /* 0x0041ed10 */
void rdRaster_Draw_FlatLit_3(int param_1,int param_2); /* 0x0041eef0 */
void rdRaster_Span16_Tex_8(uint *param_1,uint *param_2); /* 0x0041f2f0 */
undefined4 rdRaster_Edge_Flat_11(int *param_1); /* 0x0041f520 */
undefined4 rdRaster_Edge_Flat_12(int *param_1); /* 0x0041f890 */
void rdRaster_Draw16_TexLit_7(int param_1,int param_2); /* 0x0041fc00 */
void rdRaster_Span_Tex_5(uint *param_1,uint *param_2); /* 0x0041fe90 */
void __fastcall FUN_0042003c(int param_1,int param_2); /* 0x0042003c */
void rdRaster_Span16_Tex_9(uint *param_1,uint *param_2); /* 0x004200c0 */
void rdRaster_Draw_TexLitKey_3(int param_1,int param_2); /* 0x00420310 */
void rdRaster_Span8_TexKey_2(uint *param_1,uint *param_2); /* 0x00420580 */
void rdRaster_Span16_TexKey_4(uint *param_1,uint *param_2); /* 0x004207b0 */
void rdRaster_Draw16_TexLitKey_3(int param_1,int param_2); /* 0x004209f0 */
void rdRaster_Span_TexKey_4(uint *param_1,uint *param_2); /* 0x00420c80 */
void rdRaster_Span16_TexKey_5(uint *param_1,uint *param_2); /* 0x00420ec0 */
void rdRaster_Draw_FlatLit_4(int param_1,int param_2); /* 0x00421120 */
void rdRaster_Span16_Tex_10(uint *param_1,uint *param_2); /* 0x00421510 */
undefined4 rdRaster_Edge_Flat_13(int *param_1); /* 0x00421b60 */
undefined4 rdRaster_Edge_Flat_14(int *param_1); /* 0x00421dc0 */
void rdRaster_Draw16_TexLit_8(int param_1,int param_2); /* 0x00421f80 */
void rdRaster_Span_Tex_6(uint *param_1,uint *param_2); /* 0x004221f0 */
void rdRaster_Span16_Tex_11(uint *param_1,uint *param_2); /* 0x00422820 */
void rdRaster_Draw16_TexLitKey_4(int param_1,int param_2); /* 0x00422f00 */
void rdRaster_Span_FlatKey_2(uint *param_1,uint *param_2); /* 0x00423150 */
void rdRaster_Span16_TexKey_6(uint *param_1,uint *param_2); /* 0x00423740 */
void rdRaster_Draw16_TexLitKey_5(int param_1,int param_2); /* 0x00423db0 */
void rdRaster_Span_TexKey_5(uint *param_1,uint *param_2); /* 0x00424020 */
void rdRaster_Span16_TexKey_7(uint *param_1,uint *param_2); /* 0x00424670 */
void rdRaster_Draw_FlatLit_5(int param_1,int param_2,float param_3); /* 0x00424d50 */
void rdRaster_Span16_Tex_12(uint *param_1,uint *param_2); /* 0x00425150 */
undefined4 rdRaster_Edge_Flat_15(int *param_1); /* 0x004257a0 */
undefined4 rdRaster_Edge_Flat_16(int *param_1); /* 0x00425a00 */
void rdRaster_Draw16_TexLit_9(int param_1,int param_2,float param_3); /* 0x00425bc0 */
void rdRaster_Span_Tex_7(uint *param_1,uint *param_2); /* 0x00425e50 */
void rdRaster_Span16_Tex_13(uint *param_1,uint *param_2); /* 0x004264a0 */
void rdRaster_Draw_TexLitKey_4(int param_1,int param_2,float param_3); /* 0x00426bc0 */
void rdRaster_Span8_TexKey_3(uint *param_1,uint *param_2); /* 0x00426e30 */
void rdRaster_Span16_TexKey_8(uint *param_1,uint *param_2); /* 0x00427470 */
void rdRaster_Draw16_TexLitKey_6(int param_1,int param_2,float param_3); /* 0x00427ae0 */
void rdRaster_Span_TexKey_6(uint *param_1,uint *param_2); /* 0x00427d70 */
void rdRaster_Span16_TexKey_9(uint *param_1,uint *param_2); /* 0x004283f0 */
void rdRaster_Draw_FlatLit_6(int param_1,int param_2); /* 0x00428ae0 */
void rdRaster_Span16_Tex_14(uint *param_1,uint *param_2); /* 0x00428f00 */
undefined4 rdRaster_Edge_Flat_17(int *param_1); /* 0x00429870 */
undefined4 rdRaster_Edge_Flat_18(int *param_1); /* 0x00429b70 */
void rdRaster_Draw16_TexLit_10(int param_1,int param_2); /* 0x00429dc0 */
void rdRaster_Span_Tex_8(uint *param_1,uint *param_2); /* 0x0042a070 */
void rdRaster_Span16_Tex_15(uint *param_1,uint *param_2); /* 0x0042a790 */
void rdRaster_Draw_TexLitKey_5(int param_1,int param_2); /* 0x0042af60 */
void rdRaster_Span8_TexKey_4(uint *param_1,uint *param_2); /* 0x0042b1f0 */
void rdRaster_Span16_TexKey_10(uint *param_1,uint *param_2); /* 0x0042b8e0 */
void rdRaster_Draw16_TexLitKey_7(int param_1,int param_2); /* 0x0042c010 */
void rdRaster_Span_TexKey_7(uint *param_1,uint *param_2); /* 0x0042c2c0 */
void rdRaster_Span16_TexKey_11(uint *param_1,uint *param_2); /* 0x0042c9f0 */
void rdRaster_Grad_Flat_3(float param_1); /* 0x0042d190 */
void rdRaster_Grad_Flat_4(float param_1); /* 0x0042d5f0 */
void rdRaster_DrawPointsZ(int param_1,int param_2); /* 0x0042dba0 */
void rdRaster_DrawWireframeZ(int param_1,int param_2); /* 0x0042dd10 */
void rdRaster_Draw_FlatLitZ(int param_1,int param_2); /* 0x0042e010 */
void rdRaster_Span8_FlatZ(uint *param_1,uint *param_2); /* 0x0042e200 */
void rdRaster_Span16_FlatZ(uint *param_1,uint *param_2); /* 0x0042e320 */
undefined4 rdRaster_SpanR_Flat(int *param_1); /* 0x0042e440 */
undefined4 rdRaster_SpanR_Flat_2(int *param_1); /* 0x0042e630 */
void rdRaster_Draw_TexLitZ(int param_1,int param_2); /* 0x0042e820 */
void rdRaster_Span8_TexLitZ(uint *param_1,uint *param_2); /* 0x0042ea50 */
void rdRaster_Span16_TexLitZ(uint *param_1,uint *param_2); /* 0x0042eb90 */
void rdRaster_Draw_FlatLitZ_2(int param_1,int param_2,float param_3); /* 0x0042ecf0 */
void rdRaster_Span8_FlatZ_2(uint *param_1,uint *param_2); /* 0x0042ef00 */
void rdRaster_Span16_FlatZ_2(uint *param_1,uint *param_2); /* 0x0042f020 */
undefined4 rdRaster_SpanR_Flat_3(int *param_1); /* 0x0042f140 */
undefined4 rdRaster_SpanR_Flat_4(int *param_1); /* 0x0042f330 */
void rdRaster_Draw_TexLitZ_2(int param_1,int param_2,float param_3); /* 0x0042f520 */
void rdRaster_Span8_TexLitZ_2(uint *param_1,uint *param_2); /* 0x0042f770 */
void rdRaster_Span16_TexLitZ_2(uint *param_1,uint *param_2); /* 0x0042f8b0 */
void rdRaster_Draw_FlatLitZ_3(int param_1,int param_2); /* 0x0042fa10 */
void rdRaster_Span8_FlatZ_3(uint *param_1,uint *param_2); /* 0x0042fc30 */
void rdRaster_Span16_FlatZ_3(uint *param_1,uint *param_2); /* 0x0042fdc0 */
undefined4 rdRaster_SpanR_Flat_5(int *param_1); /* 0x0042ff50 */
undefined4 rdRaster_SpanR_Flat_6(int *param_1); /* 0x004301d0 */
void rdRaster_Draw_TexLitZ_3(int param_1,int param_2); /* 0x00430450 */
void rdRaster_Span8_TexZ(uint *param_1,uint *param_2); /* 0x004306c0 */
void rdRaster_Span16_TexZ(uint *param_1,uint *param_2); /* 0x00430860 */
void rdRaster_Draw_FlatLit_7(int param_1,int param_2); /* 0x00430a20 */
void rdRaster_Span_FlatZ(uint *param_1,uint *param_2); /* 0x00430fd0 */
void rdRaster_Span16_TexLit(uint *param_1,uint *param_2); /* 0x004311d0 */
undefined4 rdRaster_SpanR_Flat_7(int *param_1); /* 0x00431400 */
undefined4 rdRaster_SpanR_Flat_8(int *param_1); /* 0x00431710 */
void rdRaster_Draw_TexLitZ_4(int param_1,int param_2); /* 0x00431a20 */
void rdRaster_Span8_TexLitZ_3(uint *param_1,uint *param_2); /* 0x00431c90 */
void rdRaster_Span16_TexLit_2(uint *param_1,uint *param_2); /* 0x00431eb0 */
void rdRaster_Draw_TexLitKeyZw(int param_1,int param_2); /* 0x00432100 */
void rdRaster_Span8_FlatKeyZw(uint *param_1,uint *param_2); /* 0x00432350 */
void rdRaster_Span16_TexLitKey(uint *param_1,uint *param_2); /* 0x00432560 */
void rdRaster_Draw_TexLitKeyZw_2(int param_1,int param_2); /* 0x004327a0 */
void rdRaster_Span8_TexLitKeyZw(uint *param_1,uint *param_2); /* 0x00432a10 */
void rdRaster_Span16_TexLitKey_2(uint *param_1,uint *param_2); /* 0x00432c40 */
void rdRaster_Draw_FlatLit_8(int param_1,int param_2,float param_3); /* 0x00432ea0 */
void rdRaster_Span_TexLitZ(uint *param_1,uint *param_2); /* 0x00433480 */
void rdRaster_Span16_TexLit_3(uint *param_1,uint *param_2); /* 0x004336a0 */
undefined4 rdRaster_SpanR_Flat_9(int *param_1); /* 0x004338d0 */
undefined4 rdRaster_SpanR_Flat_10(int *param_1); /* 0x00433be0 */
void rdRaster_Draw_TexLitZ_5(int param_1,int param_2,float param_3); /* 0x00433ef0 */
void rdRaster_Span8_TexLitZ_4(uint *param_1,uint *param_2); /* 0x00434180 */
void rdRaster_Span16_TexLitZ_3(uint *param_1,uint *param_2); /* 0x004343b0 */
void rdRaster_Draw_TexLitKeyZw_3(int param_1,int param_2,float param_3); /* 0x00434610 */
void rdRaster_Span8_TexLitKeyZw_2(uint *param_1,uint *param_2); /* 0x00434880 */
void rdRaster_Span16_TexLitKey_3(uint *param_1,uint *param_2); /* 0x00434aa0 */
void rdRaster_Draw_TexLitKeyZw_4(int param_1,int param_2,float param_3); /* 0x00434ce0 */
void rdRaster_Span8_TexLitKeyZw_3(uint *param_1,uint *param_2); /* 0x00434f70 */
void rdRaster_Span16_TexLitKey_4(uint *param_1,uint *param_2); /* 0x004351a0 */
void rdRaster_Draw_FlatLit_9(int param_1,int param_2); /* 0x00435400 */
void rdRaster_Span_TexLitZ_2(uint *param_1,uint *param_2); /* 0x00435a00 */
void rdRaster_Span16_TexLitZ_4(uint *param_1,uint *param_2); /* 0x00435c70 */
undefined4 rdRaster_SpanR_Flat_11(int *param_1); /* 0x00435f60 */
undefined4 rdRaster_SpanR_Flat_12(int *param_1); /* 0x00436300 */
void rdRaster_Draw_TexLitZ_6(int param_1,int param_2); /* 0x004366a0 */
void rdRaster_Span8_TexLitZ_5(uint *param_1,uint *param_2); /* 0x00436950 */
void rdRaster_Span16_TexLitZ_5(uint *param_1,uint *param_2); /* 0x00436be0 */
void rdRaster_Draw_TexLitKeyZw_5(int param_1,int param_2); /* 0x00436e80 */
void rdRaster_Span8_TexLitKeyZw_4(uint *param_1,uint *param_2); /* 0x00437110 */
void rdRaster_Span16_TexLitKeyZw(uint *param_1,uint *param_2); /* 0x00437390 */
void rdRaster_Draw_TexLitKeyZw_6(int param_1,int param_2); /* 0x00437620 */
void rdRaster_Span8_TexLitKeyZw_5(uint *param_1,uint *param_2); /* 0x004378d0 */
void rdRaster_Span16_TexLitKeyZw_2(uint *param_1,uint *param_2); /* 0x00437b60 */
void rdRaster_Draw_FlatLit_10(int param_1,int param_2); /* 0x00437e10 */
void rdRaster_Span_FlatZ_2(uint *param_1,uint *param_2); /* 0x004383d0 */
void rdRaster_Span16_TexZ_2(uint *param_1,uint *param_2); /* 0x00438a90 */
undefined4 rdRaster_SpanR_Flat_13(int *param_1); /* 0x004391a0 */
undefined4 rdRaster_SpanR_Flat_14(int *param_1); /* 0x00439400 */
void rdRaster_Draw_TexLitZ_7(int param_1,int param_2); /* 0x004395c0 */
void rdRaster_Span8_TexZ_2(uint *param_1,uint *param_2); /* 0x00439840 */
void rdRaster_Span16_TexZ_3(uint *param_1,uint *param_2); /* 0x00439f50 */
void rdRaster_Draw_TexLitKeyZw_7(int param_1,int param_2); /* 0x0043a6e0 */
void rdRaster_Span8_FlatKeyZw_2(uint *param_1,uint *param_2); /* 0x0043a940 */
void rdRaster_Span16_TexKeyZw(uint *param_1,uint *param_2); /* 0x0043b020 */
void rdRaster_Draw_TexLitKeyZw_8(int param_1,int param_2); /* 0x0043b760 */
void rdRaster_Span8_TexKeyZw(uint *param_1,uint *param_2); /* 0x0043b9e0 */
void rdRaster_Span16_TexKeyZw_2(uint *param_1,uint *param_2); /* 0x0043c130 */
void rdRaster_Draw_FlatLit_11(int param_1,int param_2,float param_3); /* 0x0043c8d0 */
void rdRaster_Span_TexZ(uint *param_1,uint *param_2); /* 0x0043ceb0 */
void rdRaster_Span16_TexZ_4(uint *param_1,uint *param_2); /* 0x0043d5b0 */
undefined4 rdRaster_SpanR_Flat_15(int *param_1); /* 0x0043dcc0 */
undefined4 rdRaster_SpanR_Flat_16(int *param_1); /* 0x0043df20 */
void rdRaster_Draw_TexLitZ_8(int param_1,int param_2,float param_3); /* 0x0043e0e0 */
void rdRaster_Span8_TexZ_3(uint *param_1,uint *param_2); /* 0x0043e380 */
void rdRaster_Span16_TexZ_5(uint *param_1,uint *param_2); /* 0x0043eab0 */
void rdRaster_Draw_TexLitKeyZw_9(int param_1,int param_2,float param_3); /* 0x0043f280 */
void rdRaster_Span8_TexKeyZw_2(uint *param_1,uint *param_2); /* 0x0043f500 */
void rdRaster_Span16_TexKeyZw_3(uint *param_1,uint *param_2); /* 0x0043fc30 */
void rdRaster_Draw_TexLitKeyZw_10(int param_1,int param_2,float param_3); /* 0x00440370 */
void rdRaster_Span8_TexKeyZw_3(uint *param_1,uint *param_2); /* 0x00440610 */
void rdRaster_Span16_TexKeyZw_4(uint *param_1,uint *param_2); /* 0x00440d80 */
void rdRaster_Draw_FlatLit_12(int param_1,int param_2); /* 0x00441520 */
void rdRaster_Span_TexZ_2(uint *param_1,uint *param_2); /* 0x00441b20 */
void rdRaster_Span16_TexZ_6(uint *param_1,uint *param_2); /* 0x004422d0 */
undefined4 rdRaster_SpanR_Flat_17(int *param_1); /* 0x00442ab0 */
undefined4 rdRaster_SpanR_Flat_18(int *param_1); /* 0x00442db0 */
void rdRaster_Draw_TexLitZ_9(int param_1,int param_2); /* 0x00443000 */
void rdRaster_Span8_TexZ_4(uint *param_1,uint *param_2); /* 0x004432c0 */
void rdRaster_Span16_TexZ_7(uint *param_1,uint *param_2); /* 0x00443ab0 */
void rdRaster_Draw_TexLitKeyZw_11(int param_1,int param_2); /* 0x00444320 */
void rdRaster_Span8_TexKeyZw_4(uint *param_1,uint *param_2); /* 0x004445c0 */
void rdRaster_Span16_TexKeyZw_5(uint *param_1,uint *param_2); /* 0x00444d90 */
void rdRaster_Draw_TexLitKeyZw_12(int param_1,int param_2); /* 0x00445570 */
void rdRaster_Span8_TexKeyZw_5(uint *param_1,uint *param_2); /* 0x00445830 */
void rdRaster_Span16_TexKeyZw_6(uint *param_1,uint *param_2); /* 0x00446030 */
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
uint rdMaterial_SetLoadHook(uint param_1); /* 0x00417e90 */
uint rdMaterial_SetFreeHook(uint param_1); /* 0x00417ea0 */
void * __cdecl rdMaterial_Load(char *name,int a,int b); /* 0x00417eb0 */
int __cdecl rdMaterial_LoadFile(char *filename,void *material,int a,int b); /* 0x00417f30 */
void rdMaterial_Free(undefined4 param_1); /* 0x00418360 */
void rdMaterial_FreeContents(int param_1); /* 0x004183a0 */
int __cdecl rdMaterial_EnsureTexture(void *a,uint *material,int cel,int alt); /* 0x004184a0 */

/* ===== math3d.c ===== */
float __cdecl Vec3_Dot(float *a,float *b); /* 0x00446880 */
float __cdecl Vec3_Dot2(float *a,float *b); /* 0x004468a0 */
void __cdecl Vec3_Cross(float *out,float *a,float *b); /* 0x004468d0 */
void Vec3_NormalizeTo(float *param_1,float *param_2); /* 0x00446920 */
float __cdecl Vec3_Normalize(float *param_1); /* 0x004469a0 */
float __cdecl Vec3_NormalizeApprox(float *param_1); /* 0x00446a10 */
void __cdecl Vec3_Rotate(float *vec,float *rot); /* 0x00446ba0 */
void __cdecl Matrix_GetAngles(float *matrix,float *outAngles); /* 0x00446bd0 */
undefined1 Frustum_TestSphere(int *param_1,float *param_2,float param_3); /* 0x0044e7d0 */
uint Polygon_ClipToPlane(float *param_1,float *param_2,float *param_3,undefined4 *param_4, float *param_5,uint *param_6); /* 0x0044ea50 */
void Angles_ToMatrix(float *param_1,undefined4 *param_2,float *param_3); /* 0x0044eeb0 */
void __cdecl Matrix_Transpose(float *out,float *m); /* 0x0044efd0 */
void Angles_ToMatrixNoPos(float *param_1,undefined4 *param_2); /* 0x0044f080 */
void __cdecl Matrix_BuildTranslation(float *m,float *pos); /* 0x0044f1a0 */
void Matrix_BuildTranslation2(undefined4 *param_1,undefined4 *param_2); /* 0x0044f1d0 */
void Matrix_AxisAngle(float *param_1,float *param_2,float param_3); /* 0x0044f210 */
void Camera_BuildBasis(float *param_1,float *param_2,float *param_3,undefined4 param_4); /* 0x0044f490 */
void Matrix_ToAngles(float *param_1,float *param_2); /* 0x0044f650 */
void __cdecl Matrix_Identity(float *m); /* 0x0044f880 */
void __cdecl Matrix_Mul34(float *out,float *a,float *b); /* 0x0044f8a0 */
void __cdecl Matrix_BuildRotation(float *m,float *angles); /* 0x0044fa70 */
void Matrix_Multiply(float *param_1,float *param_2); /* 0x0044fc60 */
void Matrix_BuildTransform(float *param_1,undefined4 param_2); /* 0x0044fe50 */
void Matrix_SetTranslation(int param_1,float *param_2); /* 0x0044fe80 */
void Matrix_BuildTransform2(float *param_1,undefined4 param_2); /* 0x0044feb0 */
void __cdecl Vec3_Copy(float *out,float *v); /* 0x0044fee0 */
void __cdecl Vec3_TransformTo(float *out,float *v,float *m); /* 0x0044ff50 */
void __cdecl Vec3_Transform(float *vec,float *m); /* 0x0044ffc0 */
void __cdecl Vec3_Sub(float *out,float *a,float *b); /* 0x00450060 */
void __cdecl Vec3_Rotate3x3(float *vec,float *m); /* 0x004500d0 */
void __cdecl Matrix_TransformPoints(float *m,float *in,float *out,int count); /* 0x00450170 */
undefined4 FUN_00450220(undefined4 *param_1); /* 0x00450220 */
void FUN_00450260(int param_1); /* 0x00450260 */
void FUN_00450290(float *param_1,float *param_2,float *param_3,float *param_4); /* 0x00450290 */
void FUN_00450380(float *param_1,float param_2); /* 0x00450380 */
undefined4 FUN_00450410(float *param_1,float *param_2,float *param_3); /* 0x00450410 */

/* ===== rdclip.c ===== */
undefined4 rdClip_Line2D(undefined4 param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4, undefined4 *param_5); /* 0x00446c10 */
uint rdClip_Outcode2D(int param_1,int param_2,int param_3); /* 0x00446e80 */
int __cdecl rdClip_PointInFrustum(void *frustum,float *point); /* 0x00446ec0 */
int __cdecl rdClip_Line3(void *frustum,float *p0,float *p1,int *clipped0,int *clipped1); /* 0x00446f80 */
uint rdClip_Face3_Pos(int *param_1,float *param_2,uint param_3); /* 0x004478c0 */
int rdClip_Face3_PosB(int *param_1,float *param_2,int param_3); /* 0x00448260 */
uint rdClip_Face3_Pos_2(int *param_1,float *param_2,uint param_3); /* 0x004489b0 */
int rdClip_Face3_PosB_2(int *param_1,float *param_2,int param_3); /* 0x00449350 */
uint rdClip_Face3_PosUvLit(int *param_1,float *param_2,float *param_3,float *param_4); /* 0x00449aa0 */
uint rdClip_Face3_PosUv(int *param_1,float *param_2,float *param_3,uint param_4); /* 0x0044a6d0 */
uint rdClip_Face3_PosUvLit_2(int *param_1,float *param_2,float *param_3,float *param_4); /* 0x0044b0a0 */
uint rdClip_Face3_PosUvFlags(int *param_1,float *param_2,float *param_3,uint param_4); /* 0x0044be80 */
uint rdClip_Face3_PosUvLitColor (int *param_1,float *param_2,float *param_3,undefined4 *param_4,float *param_5); /* 0x0044c9d0 */
uint rdClip_Face3_PosUvLitFlags (int *param_1,float *param_2,undefined4 *param_3,undefined4 *param_4,uint param_5); /* 0x0044da40 */

/* ===== rdlight.c ===== */
undefined4 rdLight_Init(int param_1); /* 0x00451460 */
void __cdecl rdLight_SetAngles(void *light,float inner,float outer); /* 0x004514a0 */

/* ===== rdprimit2.c ===== */
void __cdecl rdPrimit2_DrawLine(void *canvas,int x1,int y1,int x2,int y2,int color,int mask); /* 0x00451b80 */
void __cdecl rdPrimit2_DrawRect(void *canvas,int x1,int y1,int x2,int y2,int color,int mask); /* 0x00451f20 */

/* ===== memory.c ===== */
void Mem_DumpLog(void); /* 0x0045ff00 */
void __cdecl Mem_Copy(void *dst,void *src,uint n); /* 0x00478170 */
void __cdecl Mem_CheckAlloc(void *p,char *file,int line); /* 0x0047fe00 */
undefined4 Memory_SysInitialize(GrimServices *param_1,undefined4 *param_2); /* 0x004888d0 */
void FUN_00488930(void); /* 0x00488930 */
undefined4 FUN_00488940(void); /* 0x00488940 */
void FUN_00488970(void); /* 0x00488970 */
void ** Pool_Create(int param_1,void *param_2,void *param_3); /* 0x00488980 */
void Pool_Destroy(void **param_1); /* 0x00488a70 */
int * Pool_Alloc(int *param_1); /* 0x00488b10 */
void __cdecl Pool_Free(void *item); /* 0x00488ba0 */
void Pool_Grow(int param_1,int param_2); /* 0x00488c00 */

/* ===== rdprimitive.c ===== */
undefined4 rdPolyline_Draw(int param_1,float *param_2); /* 0x00471ee0 */
void rdPolyline_DrawFace(int param_1,int param_2,undefined4 param_3,undefined4 *param_4); /* 0x00472360 */
int __cdecl rdSprite_DrawThing(void *thing,void *sprite); /* 0x00472640 */
int rdPolyline_New(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8, undefined4 param_9,undefined4 param_10); /* 0x004728a0 */
undefined4 rdPolyline_Init(int param_1,int param_2,undefined4 param_3,char *param_4,undefined4 param_5, undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9, undefined4 param_10,undefined4 *param_11); /* 0x00472910 */
void rdSprite_Free(int param_1); /* 0x00472b50 */
void rdSprite_FreeContents(int param_1); /* 0x00472b70 */
undefined4 rdSprite_Draw(int param_1,int param_2); /* 0x00472bd0 */

/* ===== stdfileutil.c ===== */
undefined * __cdecl stdFile_Open(uint param_1,uint param_2); /* 0x00473430 */
void stdFile_Close(undefined4 param_1); /* 0x00473450 */
void FUN_00473460(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x00473460 */
void stdFile_Write(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x00473480 */
void FUN_004734a0(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x004734a0 */
void FUN_004734c0(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x004734c0 */
uint FUN_004734e0(int param_1); /* 0x004734e0 */
undefined * __cdecl stdFile_Tell(uint param_1); /* 0x004734f0 */
void stdFile_Seek(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x00473500 */
undefined * FUN_00473520(uint param_1); /* 0x00473520 */
undefined4 FUN_00473570(undefined4 param_1,char *param_2); /* 0x00473570 */
uint stdFile_ReadByte(uint param_1); /* 0x004735f0 */
void stdFile_WriteByte(undefined4 param_1,undefined4 param_2); /* 0x00473610 */
int __cdecl stdCompress_Decompress(void *dst,void *src,int srcSize); /* 0x00473a00 */
void stdCompress_DecompressLoop(void); /* 0x00473b60 */
void * __cdecl stdFileUtil_NewFind(char *dir,int mode,char *ext); /* 0x004c1170 */
void stdFileUtil_DisposeFind(int param_1); /* 0x004c12a0 */
int __cdecl stdFileUtil_FindNext(void *find,void *outEntry); /* 0x004c12d0 */

/* ===== string.c ===== */
char * __cdecl Str_FileNameFromPath(char *path); /* 0x004735b0 */
char * __cdecl Str_ToLower(char *s); /* 0x0047b5c0 */
char * __cdecl Str_Basename(char *path); /* 0x0047fd20 */
char * __cdecl Str_FileExtension(char *path); /* 0x0047fd50 */
void Str_StripExtension(char *param_1); /* 0x0047fda0 */
void __cdecl Str_CopyBasenameNoExt(char *dst,int size,char *path); /* 0x0047fdc0 */
undefined * __cdecl Str_FindChar(char *param_1,int param_2); /* 0x004838c0 */
uint * String_ContainsSubstring(uint *param_1,char *param_2); /* 0x004aef70 */
byte * __cdecl Str_WildcardMatch(char *str,char *pattern); /* 0x004c1c30 */
int Str_ModuleNameLength(byte *param_1); /* 0x004c1e00 */
void Str_StripNonPrintable(byte *param_1); /* 0x004c1e60 */
int Str_CompareNoCase(char *param_1,char *param_2); /* 0x004c1e90 */
int Str_CompareNoCaseN(char *param_1,char *param_2,int param_3); /* 0x004c1ee0 */

/* ===== math.c ===== */
int __cdecl Math_Log2Int(int n); /* 0x004735d0 */
float __cdecl Math_PowInt(float x,int n); /* 0x0047bbe0 */
float __cdecl Math_NormalizeAngle360(float degrees); /* 0x0047bc20 */
float __cdecl Math_NormalizeAngle180(float param_1); /* 0x0047bce0 */
void Math_SinCosTable(float param_1,float *param_2,float *param_3); /* 0x0047bd20 */
float __cdecl Math_Round(float param_1); /* 0x0047c100 */
float10 Math_SinDeg(float param_1); /* 0x0047c120 */
float __cdecl Math_AsinDegrees(float x); /* 0x0047c3b0 */
float __cdecl Math_Sqrt(float param_1); /* 0x0047c490 */
float __cdecl Math_AsinDegreesSeries(float param_1); /* 0x0047c4a0 */
float __cdecl Math_Atan2Deg(float y,float x); /* 0x0047c5f0 */
void FUN_0047c7c0(undefined4 param_1); /* 0x0047c7c0 */
undefined4 FUN_0047c7e0(byte *param_1,undefined4 param_2); /* 0x0047c7e0 */
void FUN_0047c8c0(void); /* 0x0047c8c0 */

/* ===== stdbitmap.c ===== */
void * __cdecl stdBitmap_Load(char *filename); /* 0x00473630 */
void * __cdecl stdBitmap_LoadFile(char *name,int a,int b); /* 0x00473660 */
int __cdecl stdBitmap_SaveByExtension(char *filename,void *bitmap); /* 0x00473810 */
void * __cdecl stdBitmap_LoadResource(char *name,int a,int b); /* 0x0047aa50 */
void * __cdecl stdBitmap_LoadFromFile(char *filename,int a,int b,int c); /* 0x0047aab0 */
undefined4 stdBitmap_LoadBM(undefined4 param_1,int param_2,int param_3,int param_4); /* 0x0047ab20 */
void __cdecl stdBitmap_Free(void *bitmap); /* 0x0047ae70 */
void stdBitmap_FreeSurfaces(int param_1); /* 0x0047ae90 */
undefined4 stdBitmap_WriteBM(undefined4 param_1,int param_2); /* 0x0047aef0 */
int __cdecl stdBitmap_SaveBM(char *filename,void *bitmap); /* 0x0047b250 */
void stdBitmap_CopyFrom(int *param_1,int param_2); /* 0x0047b2b0 */
int __cdecl stdBitmap_Convert(void *bitmap,int format,int flags); /* 0x0047b380 */
undefined4 stdBitmap_Init(undefined4 *param_1,uint param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 *param_6); /* 0x0047b4b0 */
void stdBitmap_SetSurface(int param_1,int param_2,undefined4 param_3); /* 0x0047b540 */
int __cdecl stdBitmap_ConvertToDisplay(void *bitmap); /* 0x0047b560 */
void stdBitmap_DecompressAll(int param_1); /* 0x0047b590 */
void stdBitmap_InitHeader(undefined4 *param_1); /* 0x0047b5f0 */

/* ===== stdinput.c ===== */
undefined * Input_Init(void); /* 0x00476f10 */
void Input_Shutdown(void); /* 0x00476f70 */
undefined4 Input_Enable(void); /* 0x00476fc0 */
undefined4 Input_Disable(void); /* 0x00476fe0 */
void Input_Flush(void); /* 0x00477010 */
void Input_ResetState(void); /* 0x00477040 */
int __cdecl Input_EnableAxis(uint axis); /* 0x00477090 */
void Input_Update(void); /* 0x004770d0 */
float __cdecl Input_GetAxis(int inputId); /* 0x00477160 */
int __cdecl Input_GetButtonState(int inputId,int *down,int *justPressed); /* 0x00477230 */
undefined4 FUN_004772d0(undefined4 param_1,int param_2,int param_3); /* 0x004772d0 */
void __cdecl Input_SetAcquired(int acquire); /* 0x00477300 */
void Input_ShowCursor(int param_1); /* 0x00477380 */
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
void FUN_00477f10(undefined4 param_1,char *param_2,undefined4 param_3); /* 0x00477f10 */
uint Plat_GetPhysicalMemory(void); /* 0x00478150 */
int __cdecl Plat_MessageBox(char *text,char *caption,uint flags); /* 0x00487650 */
void Plat_SetDialogDirectory(undefined4 param_1); /* 0x00487690 */
char * Plat_GetDialogFileName(void); /* 0x004876b0 */
int __cdecl Plat_OpenFileDialog(char *title,char *filter); /* 0x004876c0 */
int __cdecl Plat_SaveFileDialog(char *title,char *filter); /* 0x004877d0 */
bool Plat_PromptDialog(int param_1,int param_2,undefined4 *param_3,uint param_4); /* 0x004878c0 */
int __cdecl Plat_TreeSelectDialog(char *title,char **items,int count,int *recursive); /* 0x00487c10 */
int __cdecl Plat_InputDialog(char *title,char *prompt,char *buf,int bufSize,char *defaultText); /* 0x00487e30 */
void * __cdecl Plat_Alloc(uint size); /* 0x00488800 */
void __cdecl Plat_Free(void *p); /* 0x00488820 */

/* ===== std3d.c ===== */
undefined4 D3D_Enumerate(void); /* 0x00478230 */
void D3D_Release(void); /* 0x004782b0 */
uint D3D_IsAvailable(void); /* 0x004782d0 */
int __cdecl D3D_SelectDriver(uint driverIdx,int useZBuffer); /* 0x004782e0 */
void D3D_ReleaseDriver(void); /* 0x00478660 */
void __cdecl D3D_SetTextureLimits(int minW,int minH,int maxSize,int d); /* 0x00478700 */
void D3D_BeginScene(void); /* 0x00478730 */
void D3D_EndScene(void); /* 0x00478750 */
undefined4 D3D_BeginExecuteBuffer(void); /* 0x00478770 */
int __cdecl D3D_AddVertices(void *verts,uint count); /* 0x004787d0 */
undefined4 D3D_BeginInstructions(void); /* 0x00478840 */
int __cdecl D3D_AddTriangles(void *tris,uint count); /* 0x004788c0 */
bool D3D_ExecuteBuffer(void); /* 0x00478b40 */
void __cdecl D3D_SetRenderFlags(uint flags); /* 0x00478c00 */
void D3D_ClampTextureSize(uint param_1,uint param_2,uint *param_3,uint *param_4); /* 0x00479070 */
void D3D_ResetTextures(void); /* 0x00479110 */
int __cdecl D3D_CreateTexture(void *surface,void *texture,int usePalette,int colorKey); /* 0x00479170 */
void D3D_FreeAllTextures(void); /* 0x00479860 */
void D3D_LinkTexture(void *param_1); /* 0x004798e0 */
void D3D_UnlinkTexture(void *param_1); /* 0x00479950 */
undefined4 D3D_SetVertexLimit(void); /* 0x00479a00 */
void D3D_TouchTexture(int param_1); /* 0x00479a70 */
undefined4 D3D_ClearZBuffer(void); /* 0x00479aa0 */
uint D3D_FindClosestDriver(int *param_1,int param_2,uint param_3); /* 0x00479b50 */
uint D3D_FindTextureFormat(int *param_1,int param_2,uint param_3); /* 0x00479be0 */
void D3D_SetViewportRect(uint *param_1); /* 0x00479cc0 */
undefined4 D3D_InitRenderState(void); /* 0x00479db0 */
undefined4 D3D_CreateViewport(void); /* 0x0047a130 */
undefined4 D3D_CreateZBuffer(int param_1,int param_2); /* 0x0047a240 */
undefined * __stdcall FUN_0047a3b0(int a1,int a2,int a3,int a4,int a5,int a6); /* 0x0047a3b0 */
undefined * __stdcall FUN_0047a590(int a1,int a2); /* 0x0047a590 */
byte D3D_CapsToFilterBits(uint param_1); /* 0x0047a850 */
byte D3D_FilterBitsToMask(byte param_1); /* 0x0047a890 */
byte D3D_FilterBitsToEnum(byte param_1); /* 0x0047a8e0 */
int __cdecl D3D_EvictTexture(uint size); /* 0x0047a930 */

/* ===== stdpcx.c ===== */
undefined4 stdPcx_DecodeRun16(byte *param_1,ushort *param_2,int param_3); /* 0x0047b710 */
undefined4 stdPcx_DecodeRun8(byte *param_1,int param_2,int param_3); /* 0x0047b780 */
undefined4 stdPcx_DecodeRunMasked(byte *param_1,int param_2,int param_3,uint param_4); /* 0x0047b810 */
void * stdPcx_Load(char *param_1,int param_2,int param_3); /* 0x0047db00 */
undefined4 stdPcx_Save(undefined4 param_1,int param_2); /* 0x0047ef10 */
void * FUN_0047f120(char *param_1,int param_2,int param_3); /* 0x0047f120 */

/* ===== std.c ===== */
undefined4 Std_ParseCommandLine(void); /* 0x0047c920 */
void FUN_0047ca00(void); /* 0x0047ca00 */
void FUN_0047ca90(void); /* 0x0047ca90 */
uint Std_Swap32(uint param_1); /* 0x0047fc50 */
uint Std_Swap16(uint param_1); /* 0x0047fd00 */

/* ===== stdbmp.c ===== */
uint stdBmp_Load(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x0047cb20 */
undefined4 stdBmp_LoadInto(char *param_1,undefined4 *param_2,int param_3,int param_4); /* 0x0047cb70 */
undefined4 stdBmp_Save(undefined4 param_1,int param_2); /* 0x0047d050 */

/* ===== stdgif.c ===== */
uint stdGif_Load(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x0047d280 */
undefined4 stdGif_LoadInto(char *param_1,undefined4 *param_2,int param_3,int param_4); /* 0x0047d2d0 */
undefined4 stdGif_Save(undefined4 param_1,int param_2); /* 0x0047e060 */
uint stdGif_LzwInitDecoder(short param_1); /* 0x0047e3c0 */
uint stdGif_LzwDecodeNext(undefined4 param_1); /* 0x0047e470 */
uint stdGif_LzwReadCode(undefined4 param_1); /* 0x0047e600 */
uint stdGif_ReadByte(undefined4 param_1); /* 0x0047e770 */
uint stdGif_LzwInitEncoder(undefined4 param_1,undefined4 param_2); /* 0x0047e7f0 */
void stdGif_LzwWriteCode(undefined4 param_1,short param_2); /* 0x0047e8b0 */
uint stdGif_LzwEncodePixel(undefined4 param_1,byte param_2); /* 0x0047ea30 */
void stdGif_LzwClearTable(undefined4 param_1); /* 0x0047eba0 */
undefined4 stdGif_LzwFinishEncode(undefined4 param_1); /* 0x0047ebe0 */
void stdGif_WriteSubBlock(undefined4 param_1,short param_2); /* 0x0047ec40 */

/* ===== stdlbm.c ===== */
undefined4 * stdLbm_Load(undefined4 param_1,int param_2,int param_3); /* 0x0047ec80 */
undefined4 stdLbm_Save(undefined4 param_1,int param_2); /* 0x0047f720 */
void stdLbm_PackBits(undefined4 param_1,undefined1 *param_2,int param_3,char *param_4); /* 0x0047f9d0 */
void stdLbm_PackByte(char param_1); /* 0x0047fa70 */
void stdLbm_SwapHeader(undefined2 *param_1); /* 0x0047fc80 */

/* ===== stdmemory.c ===== */
void stdMemory_CheckMagic(int param_1); /* 0x0047fe20 */
void * __cdecl stdMemory_Alloc(uint size,char *file,int line); /* 0x0047fe50 */
void __cdecl stdMemory_Free(void *p); /* 0x0047ff00 */
void * __cdecl stdMemory_Realloc(void *p,uint size,char *file,int line); /* 0x0047ff70 */

/* ===== res.c ===== */
int Res_GetMemoryUsed(void); /* 0x00480000 */
void * __cdecl Res_Register(int fourcc,char *name,void *data); /* 0x00480230 */
int __cdecl Res_GetFilePath(char *name,char *buf,int size); /* 0x004802b0 */
void * __cdecl Res_Load(int type,char *name); /* 0x00480520 */
uint __cdecl Res_SetLocked(void *data,int unlock); /* 0x00480560 */
int __cdecl Res_FreeUnreferenced(uint bytesWanted,uint *bytesFreed); /* 0x004805b0 */
int __cdecl Res_WriteReport(char *filename,int type); /* 0x00480680 */
int __cdecl Res_OpenLog(char *filename); /* 0x00480740 */
void __cdecl Res_InstallFileServices(GrimServices *svc); /* 0x00480790 */
void __cdecl Res_RestoreFileServices(GrimServices *svc); /* 0x00480800 */
void * __cdecl Res_FindByData(void *data); /* 0x004810e0 */
void * __cdecl Res_DataFromHandle(void *handle); /* 0x00481100 */
void * __cdecl Res_FindByHandle(void *handle); /* 0x00481120 */
void * __cdecl Res_Find(int type,char *name); /* 0x00481140 */
void * __cdecl Res_FindByName(int type,char *name); /* 0x00481160 */
void * __cdecl Res_LoadInternal(int type,char *name,int *status); /* 0x00481210 */
undefined * __cdecl Res_FindByNameFrom(uint param_1,uint param_2); /* 0x00481300 */
int * Res_FindByNameInList(int param_1,char *param_2,int *param_3); /* 0x00481320 */
void * __cdecl Res_CreateRecord(int type,char *name,void *data); /* 0x00481400 */
void __cdecl Res_CallUnload(void *res); /* 0x00481510 */
int __cdecl Res_Unlink(void *res); /* 0x004815c0 */
int __cdecl Res_GetSize(void *res); /* 0x00481ef0 */
void __cdecl Res_MoveToFront(void *res); /* 0x00481f00 */
uint __cdecl Res_HashName(char *name,char *outLower); /* 0x00481f60 */
void Res_FindByHandleOrNull(int *param_1,int *param_2,int param_3); /* 0x00482170 */
void Res_NextInList(int *param_1,int *param_2,int param_3); /* 0x004821b0 */
undefined * __cdecl Res_TouchByData(void *param_1); /* 0x00482200 */
int Res_CountChildren(uint param_1,uint param_2); /* 0x004824f0 */
void Res_SetCacheSizeMB(int param_1); /* 0x00482520 */
void Res_PrintReport(void); /* 0x0048e230 */

/* ===== resource.c ===== */
undefined4 Resource_RegisterFilioModule(uint param_1,undefined4 *param_2); /* 0x00480010 */
undefined4 __fastcall FUN_00480020(uint param_1,int param_2,undefined4 param_3,undefined4 *param_4); /* 0x00480020 */
void FUN_004800a0(void); /* 0x004800a0 */
undefined4 FUN_004800b0(void); /* 0x004800b0 */
void __cdecl Resource_SetNoPurge(int noPurge); /* 0x0048d340 */
void * __cdecl Resource_Load(int fourcc,char *name); /* 0x0048d350 */
undefined4 Resource_CloseArchives(void); /* 0x0048d3e0 */
undefined4 Resource_OpenArchives(void); /* 0x0048d3f0 */
int __cdecl Resource_SetExtraDataDir(char *dir); /* 0x0048d4b0 */
bool Resource_OpenLog(char *param_1); /* 0x0048d550 */
int __cdecl Resource_OpenArchivesInDir(char *dir); /* 0x0048d570 */
void FUN_0048d770(void); /* 0x0048d770 */
bool FUN_0048d790(void); /* 0x0048d790 */
void FUN_0048d810(undefined4 param_1); /* 0x0048d810 */
void FUN_0048d830(void); /* 0x0048d830 */
undefined4 Resource_RegisterTypes(void); /* 0x0048d870 */
void __cdecl Resource_SetMemoryUsage(int budget,int b); /* 0x0048d8a0 */
void * FUN_0048d8c0(int *param_1); /* 0x0048d8c0 */
void Resource_ReloadBitmaps(void); /* 0x0048df50 */
void Resource_RebuildColormaps(void); /* 0x0048e0a0 */
void * FUN_0048e170(char *param_1); /* 0x0048e170 */
void FUN_0048e1b0(void *param_1); /* 0x0048e1b0 */
undefined4 FUN_0048e1e0(int *param_1); /* 0x0048e1e0 */

/* ===== lab.c ===== */
void Lab_CloseAll(void); /* 0x00480120 */
void FUN_00480140(void); /* 0x00480140 */
int __cdecl Lab_OpenByName(char *path); /* 0x00480360 */
int __cdecl Lab_Close(char *name); /* 0x004803a0 */
int __cdecl Lab_MoveToFront(char *name); /* 0x004804c0 */
void * __cdecl Lab_Find(char *name); /* 0x00481070 */
void Lab_Unlink(int *param_1); /* 0x004813c0 */
int __cdecl Lab_FindFile(char *name,void *outEntry); /* 0x00481630 */
void * __cdecl Lab_Open(char *name); /* 0x004816b0 */
int * Lab_AllocRecord(void); /* 0x00481750 */
int __cdecl Lab_ReadDirectory(void *lab); /* 0x004817a0 */
int __cdecl Lab_FindEntry(void *lab,int fourcc,char *lowerName,uint hash,void *outEntry); /* 0x00481a00 */
int __cdecl Lab_ReadRaw(void *entry,void *buf,int offset,int n); /* 0x00482020 */

/* ===== restype.c ===== */
int __cdecl ResType_Register(int fourcc,void *handler); /* 0x004801a0 */
void * __cdecl ResType_Find(int fourcc); /* 0x00481050 */
int __cdecl ResType_DefaultHandler(void *msg); /* 0x00481e10 */
int __cdecl ResType_BitmapHandler(void *msg); /* 0x0048d930 */
int __cdecl ResType_CostumeHandler(void *msg); /* 0x0048da40 */
void * FUN_0048dab0(int *param_1); /* 0x0048dab0 */
void * FUN_0048dbd0(int *param_1); /* 0x0048dbd0 */
void * FUN_0048dc60(int *param_1); /* 0x0048dc60 */
void * FUN_0048dd20(int *param_1); /* 0x0048dd20 */
void * FUN_0048de10(int *param_1); /* 0x0048de10 */
void * FUN_0048de70(int *param_1); /* 0x0048de70 */
void * FUN_0048dee0(int *param_1); /* 0x0048dee0 */

/* ===== resfile.c ===== */
int __cdecl ResFile_Open(char *name,char *mode); /* 0x00480890 */
int __cdecl ResFile_Close(int fh); /* 0x00480a00 */
uint __cdecl ResFile_Read(int fh,void *buf,uint n); /* 0x00480a70 */
char * FUN_00480bb0(int param_1,char *param_2,uint param_3); /* 0x00480bb0 */
undefined4 FUN_00480ce0(int param_1,undefined4 param_2,undefined4 param_3); /* 0x00480ce0 */
undefined4 FUN_00480d50(int param_1); /* 0x00480d50 */
undefined4 FUN_00480dc0(int param_1); /* 0x00480dc0 */
int __cdecl ResFile_Seek(int fh,int offset,int whence); /* 0x00480e30 */
int __cdecl ResFile_Size(char *name); /* 0x00480f40 */
int __cdecl ResFile_Printf(int fh,char *fmt,...); /* 0x00480f90 */
void __cdecl ResFile_FillBuffer(void *entry); /* 0x00481fd0 */

/* ===== labdir.c ===== */
void * __cdecl LabDir_Open(char *dir); /* 0x00481b00 */
undefined4 LabDir_FindEntry(int param_1,undefined4 param_2,byte *param_3,int param_4,undefined4 *param_5); /* 0x00481cf0 */

/* ===== resref.c ===== */
void __cdecl ResRef_Add(void *ref,void *data,char *file,int line); /* 0x00482070 */
void ResRef_Remove(void *ref); /* 0x00482110 */
void ResRef_Release(undefined4 *param_1); /* 0x00482220 */
undefined4 FUN_00482260(code *param_1); /* 0x00482260 */
undefined4 FUN_00482380(code *param_1); /* 0x00482380 */

/* ===== engine.c ===== */
void Engine_ResetState(void); /* 0x00482460 */
void Engine_OpenResourceLog(undefined4 param_1); /* 0x00482530 */
void Engine_PushSelectedActorCostume(void); /* 0x004825c0 */
void Engine_PopSelectedActorCostume(void); /* 0x004825f0 */
int __cdecl Engine_OpenRenderer(void *mode,int flags); /* 0x00482620 */
undefined4 Engine_CloseRenderer(void); /* 0x00482660 */
void Engine_ShutdownGame(void); /* 0x004826e0 */
void Engine_SetDebugKeysCallback(undefined4 param_1); /* 0x00482720 */
void Engine_SetRenderUserCallback(undefined4 param_1); /* 0x00482730 */
void Engine_SetIdleCallback(uint param_1); /* 0x00482740 */
void Engine_SetFlipCallback(undefined4 param_1); /* 0x00482750 */
void Engine_SetZBufferEnabled(undefined4 param_1); /* 0x00482760 */
void Engine_SetExtraDataDir(char *param_1); /* 0x00482770 */
bool Engine_RunSystemScript(void); /* 0x00482790 */
undefined4 Engine_CallSystemFunction(int param_1,char *param_2); /* 0x004827a0 */
void Engine_InvalidateRect(int *param_1,int param_2); /* 0x00482800 */
bool Engine_CallExitHandler(void); /* 0x004828d0 */
void __cdecl Engine_Quit(int exitCode); /* 0x004828e0 */
void __cdecl Engine_SetPaused(int paused); /* 0x00482900 */
undefined * __cdecl Engine_CallCharacterHandler(int param_1); /* 0x00482980 */
void Engine_UpdateFrame(int param_1,int param_2); /* 0x00482990 */
void __cdecl Engine_SetIMuseState(int state); /* 0x00482ae0 */
void Engine_PresentFrame(void); /* 0x00482af0 */
undefined * FUN_00482b60(void); /* 0x00482b60 */
int FUN_00482ba0(void); /* 0x00482ba0 */
undefined * FUN_00482cc0(void); /* 0x00482cc0 */
uint Engine_RegisterSubsystems(undefined4 param_1,undefined4 *param_2,int param_3,int param_4); /* 0x00482cf0 */
undefined4 Engine_InitSubsystems(int param_1,int param_2); /* 0x00482d60 */
undefined4 Engine_ShutdownSubsystems(int param_1,int param_2); /* 0x00482dd0 */
undefined4 Engine_ResetSubsystems(int param_1,int param_2); /* 0x00482e00 */
void Profile_Begin(int param_1); /* 0x00482e30 */
undefined * __cdecl Profile_End(int param_1); /* 0x00482e80 */
undefined4 Engine_BlitToBackBuffer (undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5); /* 0x00482f00 */
void Engine_CallUserPaint(void); /* 0x00482f80 */
void Engine_RequestSave(char *param_1); /* 0x00482f90 */
void Engine_RequestLoad(char *param_1); /* 0x00482fb0 */
uint Engine_TakeRestoreFlag(void); /* 0x00482fd0 */
void Engine_SaveGame(void); /* 0x00482fe0 */
void Engine_LoadGame(void); /* 0x00483240 */
void Engine_SetSavedValue(uint param_1); /* 0x004835f0 */
uint Engine_GetSavedValue(void); /* 0x00483600 */
undefined4 Engine_CreateCameraActor(void); /* 0x00484000 */
void Engine_RenderFrame(void); /* 0x00484260 */
void __cdecl Engine_RegisterShutdownHook(void *fn); /* 0x0048d1a0 */
void Engine_RunShutdownHooks(undefined4 param_1); /* 0x0048d1c0 */

/* ===== set.c ===== */
int Set_GetRefCount(void *param_1); /* 0x004824c0 */
void __cdecl Set_MakeCurrent(char *name); /* 0x00482670 */
void * Set_ChangeSetup(uint param_1); /* 0x00482820 */
void __cdecl Set_ApplySetupCamera(void *set,int setupIdx); /* 0x00483aa0 */
void __cdecl Set_SwitchSetup(void *set,int setupIdx); /* 0x00483b50 */
void Set_DrawDebugLights(int param_1); /* 0x00485780 */
void __cdecl Set_DrawDebugCameras(void *set,uint setupIdx); /* 0x004859c0 */
void Set_SetSoundParams(int param_1,undefined4 param_2,undefined1 param_3,undefined1 param_4, undefined4 param_5,undefined4 param_6); /* 0x004a4010 */
void __cdecl Set_GetSoundParams(void *set,float *minVol,char *maxVol,char *c,float *d,float *e); /* 0x004a4050 */
void __cdecl Set_SetCurrent(void *set); /* 0x004a40f0 */
void * Set_GetCurrent(void); /* 0x004a41b0 */
char * Set_GetCurrentName(void); /* 0x004a41d0 */
int __cdecl Set_SaveState(void *writeFn); /* 0x004a41e0 */
int __cdecl Set_RestoreState(void *readFn); /* 0x004a44e0 */
void __cdecl Set_ReleaseResources(void *set); /* 0x004a4b40 */
void FUN_004a4c40(undefined4 param_1); /* 0x004a4c40 */
void FUN_004a4c60(char *param_1); /* 0x004a4c60 */
void FUN_004a4d10(int param_1); /* 0x004a4d10 */
void FUN_004a4d80(undefined4 param_1,int param_2); /* 0x004a4d80 */
int __cdecl Set_LoadResources(void *set); /* 0x004a4fe0 */
void FUN_004a5390(void); /* 0x004a5390 */
undefined4 FUN_004a53b0(void); /* 0x004a53b0 */
void FUN_004a5430(void); /* 0x004a5430 */
int __cdecl Set_RegisterHandle(char *name,void *fn); /* 0x004a54a0 */
int Set_FindHandle(char *name); /* 0x004a5500 */
undefined4 FUN_004a5550(undefined4 param_1); /* 0x004a5550 */
bool Set_IsHandleValid(char *param_1); /* 0x004a55d0 */
undefined4 FUN_004a5600(void); /* 0x004a5600 */
undefined4 FUN_004a5890(void); /* 0x004a5890 */
undefined4 FUN_004a5b40(void); /* 0x004a5b40 */
undefined4 FUN_004a5c90(void); /* 0x004a5c90 */
void * __cdecl Set_GetActorListByName(char *setName); /* 0x004a60a0 */
void * Set_FindNameInList(int param_1); /* 0x004a60c0 */
void * __cdecl Set_NormalizeName(char *setName); /* 0x004a6100 */
void FUN_004a6160(void *param_1); /* 0x004a6160 */
void __cdecl Set_ActivateSectors(void *set); /* 0x004a7150 */

/* ===== enginemodule.c ===== */
undefined * __cdecl EngineModule_Init(GrimServices *param_1,undefined **param_2); /* 0x00482540 */

/* ===== savegame.c ===== */
int __cdecl SaveGame_Write(void *data,int bytes); /* 0x004831f0 */
int __cdecl SaveGame_Read(void *buf,int n); /* 0x00483470 */
void * __cdecl SaveGame_LoadThumbnail(char *filename); /* 0x00483490 */

/* ===== imuse.c ===== */
void IMuse_SaveToTemp(void); /* 0x00483610 */
void IMuse_RestoreFromTemp(void); /* 0x00483650 */

/* ===== imusemodule.c ===== */
undefined4 IMuseModule_Init(GrimServices *param_1,undefined4 *param_2); /* 0x004836b0 */
void FUN_004836f0(void); /* 0x004836f0 */

/* ===== polyglot.c ===== */
void Polyglot_LoadTable(undefined *param_1); /* 0x00483720 */
char * __cdecl Polyglot_Lookup(char *textId); /* 0x004838e0 */

/* ===== render.c ===== */
uint * Render_GetBackBuffer(void); /* 0x004839f0 */
void Render_ToggleDebugOverlay(void); /* 0x00483a00 */
void Render_SetUserCallback(uint param_1); /* 0x00483a80 */
void Render_SetFlipCallback(void *param_1); /* 0x00483a90 */
int __cdecl Render_SaveState(void *writeFn); /* 0x00483da0 */
int __cdecl Render_RestoreState(void *readFn); /* 0x00483e20 */
void Render_SetZBufferEnabled(int param_1); /* 0x00483ea0 */
void __cdecl Render_SetBufferCount(int n); /* 0x00483eb0 */
void __cdecl Render_InvalidateRectLastBuffer(int *rect,int flag); /* 0x00483ed0 */
void __cdecl Render_InvalidateRect(int *rect,int flag); /* 0x00483f60 */
undefined4 Render_Open(uint param_1,uint param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5, undefined4 param_6,int param_7); /* 0x00484030 */
void Render_Close(void); /* 0x004841f0 */
void Render_Present(void); /* 0x004849a0 */
void Render_SetPixelFormat(uint *param_1); /* 0x004849d0 */
undefined4 FUN_00484a50(void); /* 0x00484a50 */
void Render_InitColorConstants(int param_1); /* 0x00484c40 */
void Render_DrawDebugGrid(void); /* 0x00485bd0 */
bool Render_CanvasIsPaletted(void); /* 0x00486100 */
void Render_BuildActorDrawList(void); /* 0x00486120 */
void __cdecl Render_ScreenToWorld(int x,int y,float *outPos); /* 0x004862e0 */
void __cdecl Render_InvalidateBackground(int redrawBackground,int redrawDepth); /* 0x004863b0 */
void Render_BuildColorTable(int param_1,float param_2); /* 0x004864a0 */
void __cdecl Render_RemapPixels(ushort *pixels,uint n); /* 0x00486620 */
void __cdecl Render_SetGamma(float gamma); /* 0x00486710 */
void Render_ConvertBackground(void *param_1); /* 0x00486760 */
void Render_DimBackground(ushort *param_1,byte param_2); /* 0x004867d0 */
void Render_CopyBackBufferToBackground(void); /* 0x00486990 */
void Render_CleanBuffer(void); /* 0x004869b0 */
void Render_RequestFullRedraw(void); /* 0x00486a00 */
void * Render_GetBackgroundSurface(void); /* 0x00486b00 */
void * Render_GetZBufferSurface(void); /* 0x00486b10 */
uint Render_GetUserCallback(void); /* 0x00486b20 */
void Render_SetDrawEnabled(int param_1); /* 0x00486b30 */
void __cdecl Render_DrawIris(float percent,int x,int y); /* 0x00486d00 */
void __cdecl Render_StartIrisClose(int x,int y,int durationMs); /* 0x00486eb0 */
void __cdecl Render_StartIrisOpen(int x,int y,int durationMs); /* 0x00486ef0 */
uint Render_IsIrisDone(void); /* 0x00486f30 */
void * __cdecl Render_CaptureThumbnail(int w,int h); /* 0x00486f90 */
void __cdecl Render_FillRect(int x,int y,int w,int h,float r,float g,float b); /* 0x004870e0 */
void __cdecl Render_SaveScreen(char *filename); /* 0x00487260 */
void __cdecl Render_SaveZBufferBmp(char *filename); /* 0x004872f0 */
void __cdecl Render_SaveScreenshotBmp(char *filename); /* 0x00487340 */
void __cdecl Render_DrawProgressBar(float fraction); /* 0x004873d0 */
void Render_SetWaitCursorEnabled(uint param_1); /* 0x004874c0 */
void Render_UpdateWaitCursor(void); /* 0x004874d0 */
int Render_GetFrameCounter(void); /* 0x0048f920 */

/* ===== sputrender.c ===== */
undefined4 sputRender_Initialize(GrimServices *param_1,undefined4 *param_2); /* 0x00483d40 */

/* ===== actor.c ===== */
void __cdecl Actor_ComputeScreenBox(void *actor); /* 0x00485290 */
void Actor_DrawDebugWalker(void *param_1); /* 0x00485320 */
void * __cdecl Actor_CreateSubtitle(void *actor,char *text,int x,int y); /* 0x0048b2e0 */
int __cdecl Actor_SetCostume(void *actor,char *name); /* 0x0048f930 */
void __cdecl Actor_SetHead(void *actor,int joint1,int joint2,int joint3,float maxRoll,float maxPitch,float maxYaw ); /* 0x0048f9d0 */
int __cdecl Actor_CanSeePoint(void *actor,float *point,float *outDistance); /* 0x0048fa60 */
int __cdecl Actor_CanSee(void *viewer,void *target,float *outDistance); /* 0x0048fb80 */
void Actor_TurnKey(int param_1,float param_2); /* 0x0048fbd0 */
void Actor_WalkForward(int param_1); /* 0x0048fc80 */
void Actor_UpdateMovement(void *param_1,float param_2); /* 0x0048fd90 */
void __cdecl Actor_UpdateLookAt(void *actor,float dt); /* 0x0048fe80 */
void __cdecl Actor_UpdateTalk(void *actor,float dt); /* 0x00490210 */
int __cdecl Actor_SetSelected(int handle); /* 0x00490320 */
void * Actor_FromHandle(int param_1); /* 0x00490360 */
int __cdecl Actor_GetHandle(void *actor,int tag); /* 0x00490380 */
int Actor_Create(void); /* 0x004903a0 */
void Actor_CreateExtra(int param_1); /* 0x00490580 */
void Actor_SetFollowBoxes(int param_1,int param_2); /* 0x004906b0 */
void Actor_CreateWalker(void *param_1,int param_2); /* 0x00490730 */
void Actor_SetPositionClamped(int param_1,float *param_2); /* 0x00490870 */
void Actor_SetRot(int param_1,undefined4 *param_2,int param_3); /* 0x00490900 */
void __cdecl Actor_SetReflection(void *actor,float angle); /* 0x00490a40 */
void __cdecl Actor_SetWalkChore(void *actor,int chore,void *costume); /* 0x00490a60 */
void __cdecl Actor_SetTurnChores(void *actor,int leftChore,int rightChore,void *costume); /* 0x00490b50 */
void __cdecl Actor_SetRestChore(void *actor,int chore,void *costume); /* 0x00490c80 */
int __cdecl Actor_PushCostume(void *actor,char *name); /* 0x00490d30 */
void __cdecl Actor_PopCostume(void *actor,int free); /* 0x00490dd0 */
void Actor_PuckOrient(float param_1); /* 0x00490f50 */
void Actor_UpdateWalker(int param_1); /* 0x00491110 */
void Actor_UpdateMoveChores(int param_1); /* 0x004913f0 */
void __cdecl Actor_SayLine(void *actor,char *text,int background,int volume,int pan,int x,int y); /* 0x00492b30 */
void __cdecl Actor_ShutUp(void *actor); /* 0x00493060 */
void __cdecl Actor_PushSectorOppositeEdge(int a1,int a2); /* 0x004931f0 */
void Actor_FollowPath(int param_1); /* 0x00493230 */
void __cdecl Actor_SetWalkDominate(void *actor,int dominate); /* 0x004933c0 */
void Actor_SetConstrain(int param_1,int param_2); /* 0x004933e0 */
int __cdecl Actor_IsVoicePlaying(void *actor); /* 0x004934b0 */
int __cdecl Actor_HasShadow(void *actor); /* 0x00493510 */
void __cdecl Actor_ActivateShadow(void *actor,int shadowIdx,int active); /* 0x00493540 */
void Actor_SetShadowPlane(int param_1,char *param_2); /* 0x00493570 */
void __cdecl Actor_SetShadowPoint(void *actor,float x,float y,float z); /* 0x004935f0 */
void __cdecl Actor_SetShadowValid(void *actor,int shadowIdx,int valid); /* 0x00493630 */
void __cdecl Actor_AddShadowPlane(void *actor,int shadowIdx,char *sectorName); /* 0x00493660 */
void __cdecl Actor_KillShadows(void *actor); /* 0x004936b0 */
void Actor_DrawShadows(int param_1); /* 0x004936e0 */
float * __cdecl Actor_GetFrame(void *actor); /* 0x00493790 */
void __cdecl Actor_ToClean(void *actor); /* 0x004937c0 */
int Actor_CountCostumes(int param_1); /* 0x00494690 */
void Actor_SetClipPlane(int param_1,undefined4 *param_2,undefined4 *param_3); /* 0x004946b0 */
void Actor_SetClipActive(int param_1,undefined4 param_2); /* 0x00494710 */
void Actor_SetFrustumCull(int param_1,int param_2); /* 0x00494780 */
void __cdecl Actor_Destroy(void *actor); /* 0x004947c0 */
void Actor_DrawShadowPlane(void *costumeList,void *shadow); /* 0x00494940 */
void Actor_DrawCostumes(undefined4 param_1,undefined4 param_2); /* 0x00495080 */
void Actor_DrawCostumeMeshes(undefined4 *param_1,float *param_2); /* 0x004950a0 */
void __cdecl Actor_RemoveFromSet(char *setName,void *actor); /* 0x004a5eb0 */
void __cdecl Actor_PutInSet(void *actor,char *setName); /* 0x004a5f60 */
float __thiscall Actor_GetYawToPoint(void *this,int a1); /* 0x004a8500 */

/* ===== dirtyrect.c ===== */
void __cdecl DirtyRect_Add(int *rect,int flag,int bufferIdx); /* 0x00485420 */
void __cdecl DirtyRect_Flush(void *dst,void *zdst); /* 0x00485e50 */
void DirtyRect_Clear(void); /* 0x00486020 */
void FUN_00486050(void); /* 0x00486050 */
bool FUN_00486070(void); /* 0x00486070 */
void FUN_004860d0(void); /* 0x004860d0 */

/* ===== setup.c ===== */
void Setup_DrawDebugCamera(int param_1); /* 0x00485a40 */
void * __cdecl Setup_GetBackgroundBitmap(void *set,int setupIdx); /* 0x004a3db0 */
void * __cdecl Setup_GetZBufferBitmap(void *set,int setupIdx); /* 0x004a3ef0 */

/* ===== sector.c ===== */
void __cdecl Sector_DrawAllDebug(void); /* 0x00485dc0 */
void Sector_IntersectSegment (int param_1,int param_2,undefined4 *param_3,undefined4 *param_4,undefined4 *param_5); /* 0x0049c750 */
void SectorList_SaveForShrink(void); /* 0x004a61c0 */
void SectorList_FreeShrinkSave(void); /* 0x004a6330 */
void SectorList_RestoreAfterShrink(void); /* 0x004a6380 */
undefined1 * __thiscall Sector_Construct(void *this,int a1,int a2,int a3); /* 0x004a6490 */
void __fastcall FUN_004a66e0(void *param_1); /* 0x004a66e0 */
void __thiscall Sector_SetName(void *this,char *name); /* 0x004a6760 */
void __thiscall Sector_SetSavedType(void *this,uint type); /* 0x004a6790 */
undefined * Sector_ContainsPoint(int a1,int a2); /* 0x004a6980 */
int __thiscall Sector_ClampPoint(void *this,int a1); /* 0x004a6b30 */
float __thiscall Sector_FindExitPoint(void *this,int a1,int a2,int a3); /* 0x004a6d10 */
void __thiscall Sector_SnapToPlane(void *this,float *pos); /* 0x004a6fa0 */
int __thiscall Sector_FixPlaneCoordinate(void *this,int a1); /* 0x004a7000 */
void __thiscall Sector_DrawOutline(void *this,int color); /* 0x004a70a0 */
void FUN_004a7100(void *param_1); /* 0x004a7100 */
void * SectorList_FindByPoint(int param_1,uint param_2); /* 0x004a71e0 */
void * __cdecl Sector_FindByName(char *name); /* 0x004a7230 */
void * __cdecl Sector_FindById(int id); /* 0x004a7290 */
void * SectorList_FindNearestPoint(float *param_1,uint param_2); /* 0x004a72b0 */
void __thiscall Sector_MoveWalkerToOppositeEdge(void *this,float *walker); /* 0x004a7390 */
float * __thiscall Sector_EdgeFollowDirection(void *this,float *walker); /* 0x004a7520 */
void SectorList_ResetFree(void); /* 0x004a7a90 */
float * SectorVertexPool_GetOrAdd(undefined4 param_1,float *param_2); /* 0x004a7ab0 */
void SectorVertexPool_Release(int *param_1); /* 0x004a7ba0 */
undefined * SetFile_ParseSectors(int param_1); /* 0x004a7bc0 */
int __thiscall Sector_ClipPolygon(void *this,float *verts,int count,float *out); /* 0x004a8cb0 */
float __thiscall Sector_EdgeDistance(void *this,int a1,int a2); /* 0x004a9070 */
undefined4 __fastcall Sector_CollapseShortestEdge(void *param_1); /* 0x004a9180 */
void SectorList_ShrinkWalkSectors(float param_1); /* 0x004a9d00 */

/* ===== drawlist.c ===== */
void DrawList_Reset(void); /* 0x00486250 */
undefined * DrawList_Alloc(void); /* 0x00486280 */
undefined4 FUN_004862b0(int *param_1,int *param_2); /* 0x004862b0 */

/* ===== plane.c ===== */
int __cdecl Plane_IntersectSegment(float *out,float *p1,float *p2,float a,float b,float c,float d); /* 0x00486a10 */

/* ===== cacherect.c ===== */
void * __cdecl CacheRect_Create(int x,int y,int w,int h); /* 0x00486b40 */
void CacheRect_Restore(void); /* 0x00486c50 */
void CacheRect_FreeAll(void); /* 0x00486cb0 */

/* ===== dlg.c ===== */
undefined4 * Dlg_MakeItemTemplate (undefined4 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4, undefined2 param_5,undefined2 param_6,int param_7,int param_8,uint *param_9); /* 0x00488010 */
uint * Dlg_MakeDialogTemplate (undefined4 *param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4, undefined2 param_5,undefined2 param_6,int param_7,int param_8,undefined2 param_9, uint *param_10); /* 0x004881a0 */
undefined * __stdcall FUN_00488370(int a1,int a2,int a3,int a4); /* 0x00488370 */
undefined * __stdcall FUN_00488460(int a1,int a2,int a3,int a4); /* 0x00488460 */
undefined * __stdcall FUN_004886f0(int a1,int a2,int a3,int a4); /* 0x004886f0 */

/* ===== spew.c ===== */
void Spew_Startup(void); /* 0x00488840 */
void Spew_Shutdown(void); /* 0x00488860 */
void Spew_LoadDll(void); /* 0x00488890 */

/* ===== fileutil.c ===== */
undefined4 FileUtil_SysInitialize(GrimServices *param_1,undefined4 *param_2); /* 0x00488c80 */
void FUN_00488ce0(void); /* 0x00488ce0 */
undefined4 FUN_00488cf0(void); /* 0x00488cf0 */
void FUN_00488d20(void); /* 0x00488d20 */
undefined4 FUN_00488d30(code *param_1); /* 0x00488d30 */

/* ===== savefile.c ===== */
undefined4 SaveFile_CheckFUTBHeader(code *param_1); /* 0x00488d80 */
void * SaveFile_Open(char *name,char *mode); /* 0x004c3e40 */

/* ===== dirscan.c ===== */
undefined4 * DirScan_Create(undefined4 param_1,int param_2,char *param_3); /* 0x00488de0 */
void DirScan_Destroy(int param_1); /* 0x00488e70 */
void DirScan_Reset(int param_1); /* 0x00488eb0 */
undefined4 DirScan_Next(int param_1,char *param_2); /* 0x00488ee0 */

/* ===== sputsmush.c ===== */
undefined4 sputSmush_Initialize(undefined4 param_1,undefined4 *param_2); /* 0x00488fb0 */

/* ===== movie.c ===== */
int __cdecl Movie_SaveState(void *fn); /* 0x00489030 */
undefined4 FUN_00489090(code *param_1); /* 0x00489090 */
undefined4 FUN_00489130(void); /* 0x00489130 */
void FUN_00489190(void); /* 0x00489190 */
undefined4 Movie_PollPlayback(void); /* 0x004891b0 */
int __cdecl Movie_SetTarget(void *surface); /* 0x00489280 */
undefined4 Movie_Start(char *param_1,int param_2,uint param_3,uint param_4); /* 0x004892a0 */
void Movie_Stop(void); /* 0x00489370 */
undefined * Movie_SetFile(char *param_1); /* 0x00489390 */
undefined4 FUN_004893d0(int param_1,int param_2,int param_3); /* 0x004893d0 */
bool FUN_00489410(void); /* 0x00489410 */
undefined4 FUN_00489420(undefined4 *param_1,undefined4 *param_2); /* 0x00489420 */
undefined4 FUN_004894b0(void); /* 0x004894b0 */
bool FUN_004894d0(void); /* 0x004894d0 */
int Movie_IsPlaying(void); /* 0x004894e0 */
void Movie_SetPaused(int paused); /* 0x004894f0 */
void FUN_00489510(void); /* 0x00489510 */
void FUN_00489520(void); /* 0x00489520 */
void FUN_00489530(void); /* 0x00489530 */

/* ===== primitives.c ===== */
void __cdecl Primitives_DrawAll(uint layerMask); /* 0x00489550 */
void Primitives_Hide(void); /* 0x004895d0 */
void Primitives_Show(void); /* 0x004895f0 */
undefined4 FUN_00489600(code *param_1); /* 0x00489600 */
undefined4 FUN_004896b0(code *param_1); /* 0x004896b0 */
void FUN_004897d0(void); /* 0x004897d0 */
undefined4 FUN_004897f0(void); /* 0x004897f0 */
void FUN_00489820(void); /* 0x00489820 */
void __thiscall Primitive_Construct(void *this,int id,int unused); /* 0x0048a4b0 */
void __fastcall FUN_0048a500(undefined4 *param_1); /* 0x0048a500 */
int __stdcall Primitive_AddLine(int x1,int y1,int x2,int y2,int color,int layer); /* 0x0048a560 */
int __stdcall Primitive_AddRect(int x1,int y1,int x2,int y2,int color,int filled,int layer); /* 0x0048a5b0 */
int __stdcall Primitive_AddPolyline(int count,int *points,int color,int layer); /* 0x0048a600 */
void __thiscall Primitive_Kill(void *this,int id); /* 0x0048a740 */
undefined * __stdcall Primitive_SetColor(int a1,int a2); /* 0x0048a7b0 */
undefined * __stdcall Primitive_SetLayer(int a1,int a2); /* 0x0048a7e0 */
undefined * __stdcall Primitive_Offset(int a1,int a2,int a3); /* 0x0048a830 */
undefined * __stdcall Primitive_MoveTo(int a1,int a2,int a3); /* 0x0048a8a0 */
undefined * __stdcall Primitive_SetEnd(int a1,int a2,int a3); /* 0x0048a960 */
undefined * __stdcall Primitive_SetSize(int a1,int a2,int a3); /* 0x0048a9a0 */
void __stdcall Primitive_Draw(void *prim,void *canvas); /* 0x0048aa20 */
undefined * __stdcall Primitive_Invalidate(int a1); /* 0x0048ab50 */
void Primitive_ResetIds(void); /* 0x0048abc0 */

/* ===== sputprimitive.c ===== */
undefined4 sputPrimitive_Initialize(undefined4 param_1,undefined4 *param_2); /* 0x00489580 */

/* ===== primitivelist.c ===== */
void __fastcall PrimitiveList_Clear(int *param_1); /* 0x0048a520 */
void * __thiscall PrimitiveList_Append(void *this,int id,int layer); /* 0x0048a670 */
void __thiscall PrimitiveList_Draw(void *this,void *canvas,uint layerMask); /* 0x0048a9f0 */
undefined * __thiscall PrimitiveList_Invalidate(void *this,int a1); /* 0x0048ab20 */
undefined * __stdcall PrimitiveList_FindById(int a1,int a2); /* 0x0048abd0 */

/* ===== list.c ===== */
void __cdecl List_Unlink(void *obj); /* 0x0048ac00 */

/* ===== textobjects.c ===== */
void __cdecl TextObjects_Update(int drawAll); /* 0x0048ac40 */
void TextObjects_Freeze(void); /* 0x0048ad40 */
void TextObjects_Unfreeze(void); /* 0x0048ad50 */

/* ===== sputtext.c ===== */
undefined4 sputText_Initialize(GrimServices *param_1,undefined4 *param_2); /* 0x0048acc0 */

/* ===== text.c ===== */
int __cdecl Text_ParseLuaTable(void *ctx,void *table,void *textObj); /* 0x0048c050 */
char * __cdecl Text_ParseLineId(char *line,char *outId); /* 0x0048c8d0 */
int Text_GetSpeed(void); /* 0x00494740 */
void __cdecl Text_SetSpeed(int speed); /* 0x00494750 */
void * Text_GetDefaultFont(void); /* 0x004aa930 */
int __cdecl Font_LoadFile(char *filename,void **outFont); /* 0x004aa940 */
void __cdecl Font_Free(void *font); /* 0x004aa990 */
char __cdecl Text_NextChar(char **pText); /* 0x004aa9b0 */
int __cdecl Text_CharWidth(void *ctx,int ch); /* 0x004aaa20 */
int __cdecl Text_MeasureWidth(void *ctx,char *text); /* 0x004aaa80 */
int Text_MeasureHeight(void *ctx,char *text); /* 0x004aab10 */
undefined4 Text_DrawFormatted(void *param_1,int param_2); /* 0x004aabb0 */
undefined4 Text_WrapLines(uint *param_1); /* 0x004aac40 */
void Text_CopyRunes(byte *param_1,undefined4 *param_2,int param_3,int param_4); /* 0x004aae90 */
undefined4 Text_BuildLineTable(undefined4 param_1,int *param_2); /* 0x004aaf30 */
char * Text_LayoutString(void *param_1,void *param_2,char *param_3,int *param_4,uint *param_5, int param_6); /* 0x004ab210 */
uint __cdecl Font_GlyphAdvance(void *ctx,void *font,int ch); /* 0x004ab510 */
uint Font_GlyphWidth(int param_1,int param_2,uint param_3); /* 0x004ab570 */
void __cdecl Text_DrawString(void *ctx,void *font,char *text); /* 0x004ab5d0 */
void __cdecl Text_DrawChar(void *ctx,void *font,int ch); /* 0x004ab710 */

/* ===== textobject.c ===== */
void __cdecl TextObject_Activate(void *obj,int durationMs,int flags); /* 0x0048c470 */
void FUN_0048c4d0(void); /* 0x0048c4d0 */
undefined4 FUN_0048c500(void); /* 0x0048c500 */
void FUN_0048c6f0(void); /* 0x0048c6f0 */
void * __cdecl TextObject_New(void *ctx,char *text,int durationMs,int flags); /* 0x0048c7e0 */
void __cdecl TextObject_Draw(void *obj,int invalidate); /* 0x0048c9f0 */
undefined4 * TextObject_FindBySelf(int param_1); /* 0x0048cba0 */
undefined4 FUN_0048cbc0(code *param_1); /* 0x0048cbc0 */
undefined4 FUN_0048cd80(code *param_1); /* 0x0048cd80 */
bool FUN_0048d030(undefined4 param_1); /* 0x0048d030 */

/* ===== controls.c ===== */
void Controls_ResetAll(void); /* 0x0048d050 */

/* ===== control.c ===== */
void __cdecl Control_Enable(int control); /* 0x0048d090 */
void __cdecl Control_Disable(int control); /* 0x0048d0d0 */
undefined * Control_Capture(void); /* 0x0048d150 */
undefined4 Control_Release(void); /* 0x0048d170 */

/* ===== sputcontrol.c ===== */
undefined4 sputControl_Initialize(undefined4 param_1,undefined4 *param_2); /* 0x0048d100 */

/* ===== debug.c ===== */
undefined4 Debug_CameraFovKeys(void); /* 0x0048d210 */
void FUN_0048d2c0(void); /* 0x0048d2c0 */
undefined4 FUN_0048d2e0(void); /* 0x0048d2e0 */
void FUN_0048d330(void); /* 0x0048d330 */

/* ===== sputresource.c ===== */
undefined * __cdecl sputResource_Initialize(uint param_1,undefined **param_2); /* 0x0048d4e0 */

/* ===== actors.c ===== */
void Actors_FreeAllCostumes(void); /* 0x0048e240 */
void __cdecl Actors_UpdateTalking(float dt); /* 0x0048fcc0 */
void __cdecl Actors_UpdateAll(float dt); /* 0x0048fcf0 */

/* ===== sputactor.c ===== */
undefined4 sputActor_Initialize(uint param_1,undefined4 *param_2); /* 0x0048e2c0 */
undefined4 FUN_0048e330(code *param_1); /* 0x0048e330 */
undefined4 FUN_0048ecd0(code *param_1); /* 0x0048ecd0 */

/* ===== phoneme.c ===== */
ushort __cdecl Phoneme_ToTalkChore(void *unused,int phoneme); /* 0x00490e00 */
int FUN_00490e50(int *param_1,int *param_2); /* 0x00490e50 */
void FUN_00490e60(void); /* 0x00490e60 */
undefined4 FUN_00490e80(void); /* 0x00490e80 */
void FUN_00490ef0(void); /* 0x00490ef0 */

/* ===== walker.c ===== */
undefined4 Walker_UpdateYaw(void *param_1,float *param_2); /* 0x00491230 */
void Walker_ReplanPath(int param_1,int param_2,undefined4 *param_3,undefined4 param_4); /* 0x00491650 */
uint Walker_AvoidActorPath (void *param_1,void *param_2,undefined4 *param_3,uint param_4,float *param_5); /* 0x004917e0 */
void __cdecl Walker_SetFadeTime(int ms); /* 0x00494880 */
void * __thiscall Walker_Create(void *this,float radius); /* 0x004a8200 */
void __fastcall Walker_Destroy(int param_1); /* 0x004a8270 */
undefined * __fastcall Walker_GetAngles(int param_1); /* 0x004a82a0 */
void __fastcall Walker_ReattachToSet(void *param_1); /* 0x004a82c0 */
void __thiscall Walker_SetPosition(void *this,float *pos); /* 0x004a8310 */
void __thiscall Walker_RotateVector(void *this,float *vec); /* 0x004a8350 */
void __thiscall Walker_ToLocalSpace(void *this,float *vec); /* 0x004a8370 */
undefined * __thiscall Walker_TurnHeading(void *this,int a1); /* 0x004a83c0 */
float __thiscall Walker_TurnToPoint(void *this,int a1,int a2); /* 0x004a8450 */
undefined * __thiscall Walker_SetConstraint(void *this,int a1); /* 0x004a85b0 */
undefined * __thiscall Walker_WalkSectors(void *this,int a1,int a2,int a3); /* 0x004a8610 */
undefined * __thiscall Walker_SetSectorFrame(void *this,int a1); /* 0x004a89b0 */
void __fastcall Walker_RebuildRightVector(int param_1); /* 0x004a8a90 */
void __stdcall Walker_DrawDebugAxes(int color); /* 0x004a8b00 */
uint Planner_GetPath(undefined4 *param_1); /* 0x004a9420 */
undefined4 Planner_PlanPath(undefined4 param_1,uint *param_2,int param_3); /* 0x004a9430 */
undefined4 Planner_SearchSectors(float *param_1,int param_2,void *param_3); /* 0x004a94d0 */
uint Planner_CollectSharedCorners(void *param_1,float *param_2,uint *param_3); /* 0x004a96f0 */
undefined4 Planner_PortalPoint(int param_1,int param_2,float *param_3,undefined4 *param_4); /* 0x004a9920 */
undefined4 Planner_SmoothPath(void); /* 0x004a9aa0 */
int Planner_SharedSector(undefined4 param_1,int param_2); /* 0x004a9ca0 */

/* ===== collision.c ===== */
void Collision_PushOutOfBox (float *param_1,float param_2,float param_3,float param_4,float param_5,float param_6 ,float param_7,float *param_8,float *param_9); /* 0x004922d0 */
undefined4 Collision_PointInBox(float *param_1,float *param_2,undefined4 param_3); /* 0x00492510 */
void Collision_BoxCorners(int param_1,float param_2,float *param_3,float param_4,float *param_5); /* 0x004925c0 */
undefined4 Collision_SegmentHitsBox (float *param_1,float *param_2,float *param_3,float param_4,float param_5, undefined4 param_6,float param_7,float param_8,undefined4 param_9,float *param_10); /* 0x00492680 */
int Collision_PickDetour(float *param_1,float *param_2,int param_3); /* 0x00492a50 */
undefined4 Collision_UpdateMovedActors(void); /* 0x004939a0 */
undefined4 Collision_TestActorAgainstOthers(void *param_1); /* 0x004939f0 */
undefined4 Collision_BoxSlide(float *param_1,float *param_2,float param_3,float param_4,float param_5, float param_6,float param_7,float param_8,float *param_9); /* 0x00494100 */

/* ===== speech.c ===== */
void __cdecl Speech_SetMode(int mode); /* 0x004931c0 */
uint Speech_GetMode(void); /* 0x004931e0 */

/* ===== costume.c ===== */
void Cos_StartChoreFaded(void *param_1,int param_2,int param_3); /* 0x00493410 */
undefined * __cdecl Cos_StopChoreFaded(void *param_1,int param_2,int param_3); /* 0x00493450 */
void __cdecl Costume_PrintList(void *costume); /* 0x00494d10 */
void __cdecl Costume_FreeList(void *list,int free); /* 0x00494dc0 */
void * __cdecl Costume_Pop(void *list,int free); /* 0x00494e10 */
void * __cdecl Costume_ReplaceTop(void *list,void *costumeRes,int flags); /* 0x00494e50 */
void * __cdecl Costume_Push(void *list,void *costumeRes,int flags); /* 0x00494e80 */
undefined4 Costume_AllocRecord(void); /* 0x00494f90 */
void Costume_InitRecord(undefined4 *param_1); /* 0x00494fb0 */
void * __cdecl Costume_GetMainModel(void *cosInst); /* 0x00495020 */
void __cdecl Costume_ApplyScale(void *actor,void *componentList); /* 0x00495510 */
void __cdecl Costume_ApplyComponentState(void *cosInst); /* 0x004955e0 */
void __cdecl Costume_UpdateAttachedFrame(void *component,float *frame); /* 0x004956a0 */
void Costume_TouchComponents(undefined4 param_1); /* 0x004956f0 */
void __cdecl Costume_UpdateAll(void *costumeList,float dt); /* 0x00495730 */

/* ===== shadow.c ===== */
void __cdecl Shadow_SetColor(int r,int g,int b); /* 0x00494890 */
void __cdecl Shadow_DrawClippedPoly(float *verts,int count,float *minXY,float *maxXY,void *shadow); /* 0x00494bf0 */

/* ===== sputcostume.c ===== */
bool sputCostume_Initialize(GrimServices *param_1,undefined4 *param_2); /* 0x004957f0 */

/* ===== component.c ===== */
void Component_SetBitmapFrame(undefined4 param_1,int *param_2,undefined4 param_3,int param_4); /* 0x00496060 */
undefined4 FUN_004960a0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, char *param_5); /* 0x004960a0 */

/* ===== spritecomponent.c ===== */
undefined4 SpriteComponent_Destroy(undefined4 param_1,undefined4 param_2,void *param_3); /* 0x00496340 */
undefined4 * FUN_00496370(undefined4 param_1,undefined4 param_2,int *param_3); /* 0x00496370 */
undefined4 * SpriteComponent_NewInstance(undefined4 param_1,undefined4 param_2,int param_3); /* 0x00496d70 */
void FUN_00496e10(int param_1); /* 0x00496e10 */

/* ===== cmapcomponent.c ===== */
bool CmapComponent_Create (undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,char *param_5); /* 0x00496460 */
undefined4 CmapComponent_Destroy(undefined4 param_1,undefined4 param_2,void *param_3); /* 0x00496580 */
undefined4 FUN_004965b0(void); /* 0x004965b0 */
void FUN_004965d0(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4); /* 0x004965d0 */
void * __cdecl CmapComponent_NewInstance(void *cosInst,int componentIdx,int create); /* 0x004965e0 */
bool FUN_00496670(undefined4 param_1,undefined4 param_2,int *param_3,int param_4,char *param_5); /* 0x00496670 */

/* ===== modelcomponent.c ===== */
undefined4 ModelComponent_EditParentOffset(int *param_1,undefined4 param_2); /* 0x00496890 */
void ModelComponent_SetVisibleFlag(undefined4 param_1,int param_2,undefined4 param_3,int param_4); /* 0x00496930 */
void * __cdecl ModelComponent_NewInstance(void *cosInst,int componentIdx,int create); /* 0x00496950 */
undefined4 FUN_00496b40(int param_1); /* 0x00496b40 */
bool FUN_00496b60(undefined4 param_1,undefined4 param_2,int param_3,int param_4,char *param_5); /* 0x00496b60 */
undefined4 ModelComponent_Destroy(undefined4 param_1,undefined4 param_2,void *param_3); /* 0x00496d10 */
void FUN_00496d40(undefined4 param_1,int *param_2,undefined4 param_3,int param_4); /* 0x00496d40 */
undefined4 ModelComponent_Create(undefined4 param_1,undefined4 param_2,int *param_3,int param_4,char *param_5); /* 0x00496e20 */
bool FUN_00497180(undefined4 param_1,undefined4 param_2); /* 0x00497180 */
void FUN_004971a0(int param_1,float param_2,undefined4 param_3,float param_4); /* 0x004971a0 */
undefined4 FUN_00497320(int *param_1,undefined4 param_2); /* 0x00497320 */
bool FUN_00497460(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,char *param_5 ); /* 0x00497460 */
undefined4 FUN_00497640(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x00497640 */
undefined4 FUN_00497660(undefined4 param_1); /* 0x00497660 */
void FUN_00497680(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4); /* 0x00497680 */
undefined4 FUN_004976a0(undefined4 *param_1,int param_2,int param_3); /* 0x004976a0 */
bool FUN_00497710(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,int param_5); /* 0x00497710 */
undefined4 FUN_004977f0(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x004977f0 */
undefined4 FUN_00497810(undefined4 param_1); /* 0x00497810 */

/* ===== bitmapcomponent.c ===== */
undefined4 BitmapComponent_Destroy(undefined4 param_1,undefined4 param_2,void *param_3); /* 0x004980b0 */

/* ===== keyframecomponent.c ===== */
undefined4 KeyframeComponent_Stop(int *param_1); /* 0x004980e0 */
undefined4 FUN_00498140(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x00498140 */
void FUN_00498160(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4); /* 0x00498160 */
undefined4 FUN_00498180(void); /* 0x00498180 */
bool FUN_00498190(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, char *param_5); /* 0x00498190 */
undefined4 FUN_00498280(undefined4 param_1,undefined4 param_2,int param_3,float param_4,char *param_5); /* 0x00498280 */
void FUN_00498550(undefined4 param_1,int param_2,undefined4 param_3,int param_4); /* 0x00498550 */
undefined4 KeyframeComponent_Destroy(undefined4 param_1,undefined4 param_2,int *param_3); /* 0x00498580 */
undefined4 * FUN_004985c0(int param_1,undefined4 *param_2,int param_3); /* 0x004985c0 */
undefined4 FUN_004986e0(undefined4 *param_1,undefined4 param_2); /* 0x004986e0 */
void FUN_004988a0(void); /* 0x004988a0 */

/* ===== chore.c ===== */
void __cdecl Chore_FadeIn(void *cosInst,int chore,int ms); /* 0x00498990 */
void __cdecl Chore_FadeOut(void *cosInst,int chore,int ms); /* 0x00498ad0 */

/* ===== config.c ===== */
void __cdecl Config_GetPath(char *name,char *buf,char *defaultSubdir); /* 0x00498bf0 */
void __cdecl Config_SetPath(char *name,char *value); /* 0x00498cf0 */

/* ===== sputlua.c ===== */
undefined4 sputLua_Initialize(GrimServices *param_1,undefined4 *param_2); /* 0x0049c9f0 */

/* ===== timer.c ===== */
uint Timer_GetTotalMs(void); /* 0x004a3be0 */
uint Timer_GetFrameMs(void); /* 0x004a3bf0 */
float __cdecl Timer_GetFrameSeconds(void); /* 0x004a3c00 */
void Timer_UpdateFromWallClock(void); /* 0x004a3c10 */
void Timer_UpdateFixedStep(uint param_1); /* 0x004a3c80 */
void Timer_Reset(void); /* 0x004a3ce0 */

/* ===== sputtime.c ===== */
undefined4 sputTime_Initialize(undefined4 param_1,undefined4 *param_2); /* 0x004a3d00 */
void FUN_004a3d50(void); /* 0x004a3d50 */
undefined4 FUN_004a3d70(void); /* 0x004a3d70 */
void FUN_004a3da0(void); /* 0x004a3da0 */

/* ===== sound.c ===== */
void PositionedSounds_UpdateAll(void); /* 0x004a3fe0 */
void Sound_SetPosition(uint param_1,undefined **param_2,uint param_3,uint param_4,uint param_5, uint param_6); /* 0x004a40a0 */
void PositionedSounds_DropFinished(void); /* 0x004a4dc0 */
undefined * __cdecl PositionedSound_Add(uint param_1,undefined **param_2,uint param_3,uint param_4,uint param_5, uint param_6); /* 0x004a4e20 */
undefined4 PositionedSound_Apply(int param_1); /* 0x004a4e80 */
undefined4 Sound_DriverQuery(void); /* 0x004d0c20 */
undefined * __cdecl Sound_VoiceSampleCount(int param_1); /* 0x004d0cf0 */

/* ===== sputroom.c ===== */
undefined * __cdecl sputRoom_Initialize(uint param_1,undefined **param_2); /* 0x004a48c0 */
void FUN_004a4920(undefined4 param_1); /* 0x004a4920 */
undefined4 FUN_004a4930(char *param_1); /* 0x004a4930 */
void FUN_004a4980(undefined4 param_1); /* 0x004a4980 */
void FUN_004a4990(void *param_1); /* 0x004a4990 */
undefined4 * FUN_004a49a0(char *param_1); /* 0x004a49a0 */
void FUN_004a4a70(undefined4 *param_1); /* 0x004a4a70 */
bool FUN_004a4b00(char *param_1,uint param_2); /* 0x004a4b00 */

/* ===== light.c ===== */
void * __cdecl Light_Get(void *set,int index); /* 0x004a5cc0 */
int __cdecl Light_FindByName(void *set,char *name); /* 0x004a5cf0 */

/* ===== objstate.c ===== */
void * __cdecl ObjectState_Create(int setupIdx,int type,char *bitmap,char *zbitmap,int visible); /* 0x004a5d50 */
void __cdecl ObjectState_Free(void *state); /* 0x004a5e50 */
undefined4 * __fastcall StateImage_Construct(undefined4 *param_1); /* 0x004aa070 */
void __fastcall StateImage_Release(int param_1); /* 0x004aa0b0 */
void __thiscall StateImage_Init(void *this,char *name); /* 0x004aa100 */
void __thiscall StateImage_Load(void *this,int load); /* 0x004aa130 */
undefined4 __fastcall StateImage_GetFrameSurface(int param_1); /* 0x004aa1f0 */
void __thiscall StateImage_CaptureFrom(void *this,void *surface); /* 0x004aa290 */
void __thiscall StateImage_Draw(void *this,void *dst); /* 0x004aa310 */
bool __fastcall StateImage_IsCurrentFrame(int param_1); /* 0x004aa3e0 */
void * __thiscall ObjectState_Construct(void *this,int type,char *bitmapName,char *zbufName,int setupIdx); /* 0x004aa410 */
void __fastcall ObjectState_Destruct(int param_1); /* 0x004aa4c0 */
void __fastcall ObjectState_LoadImages(int param_1); /* 0x004aa540 */
void __fastcall ObjectState_UnloadBitmaps(int param_1); /* 0x004aa560 */
void __thiscall ObjectState_CaptureBackground(void *this,void *bg,void *zbuf); /* 0x004aa580 */
void __thiscall ObjectState_Draw(void *this,int type,void *dst,void *zdst); /* 0x004aa5c0 */
int __thiscall ObjectState_SetFrame(void *this,int a1); /* 0x004aa6b0 */
void * __thiscall ObjectState_SendToBack(void *this,void *list); /* 0x004aa6c0 */
void * __thiscall ObjectState_SendToFront(void *this,void *list); /* 0x004aa720 */

/* ===== textmodule.c ===== */
int __cdecl TextModule_Init(GrimServices *svc,void *iface); /* 0x004aa7b0 */
void FUN_004aa810(void); /* 0x004aa810 */
void FUN_004aa820(void); /* 0x004aa820 */
void FUN_004aa860(void); /* 0x004aa860 */
undefined4 FUN_004aa880(code *param_1); /* 0x004aa880 */
undefined4 TextModule_CheckHeader(code *param_1); /* 0x004aa8d0 */

/* ===== glyph.c ===== */
void Glyph_Blit16(int param_1,undefined4 param_2,int *param_3); /* 0x004ab910 */
void Glyph_Blit8(int param_1,int param_2,int *param_3); /* 0x004ab9d0 */
void Glyph_Blit16Clipped(int param_1,undefined4 param_2,int *param_3); /* 0x004abae0 */
void Glyph_Blit8Clipped(int param_1,int param_2,int *param_3); /* 0x004abc80 */

/* ===== platmodule.c ===== */
int PlatModule_Init(GrimServices *svc,void *iface); /* 0x004abe90 */
void FUN_004abef0(void); /* 0x004abef0 */
undefined4 FUN_004abf00(void); /* 0x004abf00 */
void FUN_004abf30(void); /* 0x004abf30 */

/* ===== crt.c ===== */
char _stricmp(byte *param_1,byte *param_2); /* 0x004ac550 */
int __cdecl sprintf(char *buf,char *fmt,...); /* 0x004ac620 */
longlong __cdecl _ftol(double x); /* 0x004ac6f0 */
int __cdecl _snprintf(char *buf,uint n,char *fmt,...); /* 0x004ac720 */
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
uint memcmp(char *param_1,char *param_2,int param_3); /* 0x004add60 */
int __cdecl sscanf(char *str,char *fmt,...); /* 0x004adda0 */
uint * strchr(uint *param_1,char param_2); /* 0x004ade30 */
undefined4 _vsnprintf(uint param_1,uint param_2,undefined4 param_3); /* 0x004adf70 */
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
byte _isatty(uint param_1); /* 0x004b6d40 */
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
bool _isindst_lk(int *param_1); /* 0x004b8250 */
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
undefined2 _filwbuf(undefined4 *param_1); /* 0x004b9010 */
void _except1(int param_1,int *param_2,ushort *param_3); /* 0x004b9ea0 */
bool _ValidateRead(int param_1,int param_2); /* 0x004ba2c0 */
bool _ValidateWrite(int param_1,int param_2); /* 0x004ba2e0 */
bool _ValidateExecute(int param_1); /* 0x004ba300 */
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
bool _handle_exc(uint param_1,double *param_2,uint param_3); /* 0x004bc0a0 */
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
void FUN_004addf0(void); /* 0x004addf0 */
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
int FUN_004b0740(undefined4 *param_1,int param_2,int param_3,undefined4 param_4); /* 0x004b0740 */
undefined1 * FUN_004b07c0(undefined1 *param_1,int param_2,int param_3,int *param_4,char param_5); /* 0x004b07c0 */
int FUN_004b08c0(undefined4 *param_1,int param_2,int param_3); /* 0x004b08c0 */
undefined1 * FUN_004b0930(undefined1 *param_1,uint param_2,int *param_3,char param_4); /* 0x004b0930 */
void FUN_004b09f0(undefined4 *param_1,int param_2,int param_3,undefined4 param_4); /* 0x004b09f0 */
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
bool FUN_004b5baa(void); /* 0x004b5baa */
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
undefined4 FUN_004b9916(undefined4 param_1,uint param_2,ushort param_3); /* 0x004b9916 */
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
void FUN_004bd430(void); /* 0x004bd430 */
undefined4 FUN_004bd440(void); /* 0x004bd440 */
void FUN_004bd4d0(void); /* 0x004bd4d0 */
undefined4 FUN_004bdad0(void); /* 0x004bdad0 */
undefined4 FUN_004bdf70(int *param_1,undefined4 param_2); /* 0x004bdf70 */
void FUN_004bdfb0(void); /* 0x004bdfb0 */
void FUN_004bdfe0(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x004bdfe0 */
void FUN_004be000(undefined4 param_1); /* 0x004be000 */
void FUN_004be020(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4); /* 0x004be020 */
undefined4 FUN_004be050(int *param_1,undefined4 param_2); /* 0x004be050 */
void FUN_004be090(void); /* 0x004be090 */
void FUN_004be0c0(undefined4 param_1,undefined4 param_2); /* 0x004be0c0 */
void FUN_004be0e0(undefined4 param_1); /* 0x004be0e0 */
void FUN_004be100(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x004be100 */
void FUN_004be120(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x004be120 */
void FUN_004be140(undefined4 param_1); /* 0x004be140 */
void FUN_004be160(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x004be160 */
undefined * __stdcall FUN_004bf950(int a1,int a2,int a3,int a4); /* 0x004bf950 */
undefined * __stdcall FUN_004bffb0(int a1,int a2,int a3); /* 0x004bffb0 */
void FUN_004c0630(undefined4 *param_1); /* 0x004c0630 */
int FUN_004c0660(char *param_1); /* 0x004c0660 */
undefined4 FUN_004c0770(char *param_1,int param_2); /* 0x004c0770 */
undefined4 FUN_004c0ce0(undefined4 param_1,int param_2); /* 0x004c0ce0 */
void FUN_004c0e40(int param_1); /* 0x004c0e40 */
void FUN_004c0e70(int param_1); /* 0x004c0e70 */
undefined4 FUN_004c1900(int *param_1); /* 0x004c1900 */
undefined4 FUN_004c1f40(int *param_1,uint param_2); /* 0x004c1f40 */
void FUN_004c1fb0(void); /* 0x004c1fb0 */
undefined4 FUN_004c1ff0(void); /* 0x004c1ff0 */
void FUN_004c2150(void); /* 0x004c2150 */
int FUN_004c21e0(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8, undefined4 param_9,code *param_10,int param_11,undefined4 param_12, undefined4 param_13); /* 0x004c21e0 */
undefined4 FUN_004c23c0(undefined4 *param_1,undefined4 param_2,int param_3,undefined4 param_4, undefined4 param_5,int param_6); /* 0x004c23c0 */
int FUN_004c2590(int param_1); /* 0x004c2590 */
undefined4 FUN_004c25c0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5 ,undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9, undefined4 param_10); /* 0x004c25c0 */
void FUN_004c2650(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8, undefined4 param_9); /* 0x004c2650 */
void FUN_004c2690(int *param_1); /* 0x004c2690 */
void FUN_004c2720(undefined4 *param_1,int param_2); /* 0x004c2720 */
void FUN_004c2760(undefined4 *param_1); /* 0x004c2760 */
undefined4 FUN_004c2780(int param_1); /* 0x004c2780 */
int FUN_004c27a0(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8, undefined4 param_9,undefined4 param_10); /* 0x004c27a0 */
void FUN_004c2a80(undefined4 param_1,int param_2); /* 0x004c2a80 */
char * FUN_004c2b00(int param_1); /* 0x004c2b00 */
void FUN_004c2b30(uint param_1); /* 0x004c2b30 */
uint FUN_004c2b40(void); /* 0x004c2b40 */
undefined4 FUN_004c2b50(int *param_1,uint param_2); /* 0x004c2b50 */
void FUN_004c2ba0(void); /* 0x004c2ba0 */
int FUN_004c2be0(void); /* 0x004c2be0 */
void FUN_004c2dc0(void); /* 0x004c2dc0 */
void FUN_004c2eb0(void); /* 0x004c2eb0 */
undefined4 FUN_004c2ee0(undefined1 *param_1,int param_2); /* 0x004c2ee0 */
uint FUN_004c2fa0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, uint *param_5,uint *param_6,uint *param_7,uint param_8,undefined4 param_9, undefined4 param_10,byte *param_11,int param_12); /* 0x004c2fa0 */
void FUN_004c34d0(short *param_1,int param_2); /* 0x004c34d0 */
int FUN_004c3560(int param_1); /* 0x004c3560 */
void FUN_004c35c0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,byte param_6,byte param_7,uint param_8); /* 0x004c35c0 */
char * FUN_004c3660(int param_1); /* 0x004c3660 */
void FUN_004c3690(uint param_1); /* 0x004c3690 */
uint FUN_004c36a0(void); /* 0x004c36a0 */
void FUN_004c36b0(int param_1); /* 0x004c36b0 */
uint FUN_004c36f0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8, undefined4 param_9,undefined4 param_10,undefined4 param_11); /* 0x004c36f0 */
void FUN_004c3b30(int param_1,undefined4 param_2); /* 0x004c3b30 */
undefined4 FUN_004c3bb0(int param_1); /* 0x004c3bb0 */
undefined4 FUN_004c3c00(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5 ,undefined4 param_6,undefined4 param_7,undefined4 param_8,uint param_9, undefined4 param_10,undefined4 param_11); /* 0x004c3c00 */
void FUN_004c3c90(int param_1,int param_2,undefined4 param_3,uint *param_4); /* 0x004c3c90 */
undefined4 FUN_004c3d00(int param_1); /* 0x004c3d00 */
void FUN_004c3d10(int param_1); /* 0x004c3d10 */
undefined4 FUN_004c3d30(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5 ,undefined4 param_6); /* 0x004c3d30 */
void FUN_004c3d90(int param_1,undefined4 param_2,undefined4 param_3); /* 0x004c3d90 */
uint FUN_004c3db0(int param_1,int param_2); /* 0x004c3db0 */
void FUN_004c3df0(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x004c3df0 */
undefined8 __fastcall FUN_004c3e10(undefined4 param_1,undefined4 param_2,undefined4 *param_3,undefined4 *param_4, uint param_5); /* 0x004c3e10 */
uint FUN_004c4650(int param_1,undefined4 param_2); /* 0x004c4650 */
undefined * FUN_004c4a00(int param_1,int *param_2); /* 0x004c4a00 */
undefined4 FUN_004c4b20(int *param_1,uint param_2); /* 0x004c4b20 */
void FUN_004c4b60(void); /* 0x004c4b60 */
undefined4 FUN_004c4b90(void); /* 0x004c4b90 */
void FUN_004c4c10(void); /* 0x004c4c10 */
int FUN_004c4c50(undefined4 *param_1,uint param_2,int param_3); /* 0x004c4c50 */
void FUN_004c4d20(int *param_1); /* 0x004c4d20 */
void FUN_004c4d90(undefined4 *param_1); /* 0x004c4d90 */
void FUN_004c4dd0(uint *param_1,uint param_2); /* 0x004c4dd0 */
undefined4 FUN_004c4ee0(int param_1,char *param_2,undefined4 param_3); /* 0x004c4ee0 */
undefined4 FUN_004c4f60(int param_1); /* 0x004c4f60 */
undefined4 FUN_004c5080(int param_1); /* 0x004c5080 */
int FUN_004c50a0(undefined4 *param_1,int param_2); /* 0x004c50a0 */
undefined4 FUN_004c51b0(int param_1); /* 0x004c51b0 */
undefined4 FUN_004c51e0(int param_1,int param_2); /* 0x004c51e0 */
int FUN_004c5220(int param_1); /* 0x004c5220 */
undefined4 FUN_004c5280(int *param_1,uint param_2); /* 0x004c5280 */
void FUN_004c52c0(void); /* 0x004c52c0 */
undefined4 FUN_004c52f0(void); /* 0x004c52f0 */
void FUN_004c5330(void); /* 0x004c5330 */
void FUN_004c5350(undefined4 param_1,undefined4 *param_2); /* 0x004c5350 */
void FUN_004c5370(undefined4 *param_1); /* 0x004c5370 */
bool FUN_004c5380(int param_1); /* 0x004c5380 */
void FUN_004c53b0(undefined4 param_1,undefined4 param_2); /* 0x004c53b0 */
void FUN_004c53d0(undefined4 param_1); /* 0x004c53d0 */
int FUN_004c53e0(undefined4 param_1,int param_2,int param_3,undefined4 param_4,byte param_5); /* 0x004c53e0 */
bool FUN_004c54f0(char *param_1,int param_2); /* 0x004c54f0 */
undefined4 FUN_004c5570(int param_1,char *param_2); /* 0x004c5570 */
undefined4 FUN_004c55d0(char *param_1,char *param_2,char *param_3,undefined4 param_4); /* 0x004c55d0 */
int FUN_004c5720(int param_1,int param_2); /* 0x004c5720 */
undefined4 FUN_004c5790(int *param_1,uint param_2); /* 0x004c5790 */
void FUN_004c5840(void); /* 0x004c5840 */
undefined4 FUN_004c5870(void); /* 0x004c5870 */
void FUN_004c5910(void); /* 0x004c5910 */
int * FUN_004c5950(char *param_1,char *param_2); /* 0x004c5950 */
void FUN_004c5ab0(int *param_1); /* 0x004c5ab0 */
int FUN_004c5b00(int *param_1,undefined4 param_2,int param_3); /* 0x004c5b00 */
undefined4 FUN_004c5bc0(int *param_1,undefined4 param_2,int param_3); /* 0x004c5bc0 */
int FUN_004c5c20(int *param_1); /* 0x004c5c20 */
void FUN_004c5c50(int *param_1,int param_2,int param_3); /* 0x004c5c50 */
void FUN_004c5cb0(int *param_1); /* 0x004c5cb0 */
undefined4 FUN_004c5ce0(int *param_1,uint param_2); /* 0x004c5ce0 */
void FUN_004c5d20(void); /* 0x004c5d20 */
undefined4 FUN_004c5d50(void); /* 0x004c5d50 */
void FUN_004c5d90(void); /* 0x004c5d90 */
void FUN_004c5db0(undefined4 param_1,undefined4 param_2); /* 0x004c5db0 */
void FUN_004c5dd0(undefined4 param_1); /* 0x004c5dd0 */
void FUN_004c5df0(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x004c5df0 */
void FUN_004c5e10(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x004c5e10 */
void FUN_004c5e30(undefined4 param_1); /* 0x004c5e30 */
void FUN_004c5e50(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x004c5e50 */
void FUN_004c5e70(undefined4 param_1); /* 0x004c5e70 */
undefined4 FUN_004c5e90(undefined4 param_1); /* 0x004c5e90 */
int FUN_004c5ee0(undefined4 param_1,int param_2,int param_3); /* 0x004c5ee0 */
bool FUN_004c5f50(undefined4 param_1); /* 0x004c5f50 */
void FUN_004c5f80(undefined4 param_1,undefined4 param_2); /* 0x004c5f80 */
uint FUN_004c5fe0(uint param_1); /* 0x004c5fe0 */
uint FUN_004c6010(undefined4 param_1,uint param_2); /* 0x004c6010 */
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
undefined4 FUN_004cba30(int *param_1,uint param_2); /* 0x004cba30 */
void FUN_004cba70(void); /* 0x004cba70 */
int FUN_004cbaa0(void); /* 0x004cbaa0 */
void FUN_004cbb30(void); /* 0x004cbb30 */
char * FUN_004cbb80(int param_1); /* 0x004cbb80 */
undefined4 FUN_004cbbb0(void); /* 0x004cbbb0 */
undefined4 FUN_004cbbc0(void); /* 0x004cbbc0 */
void FUN_004cbbd0(void); /* 0x004cbbd0 */
undefined4 FUN_004cbbe0(int param_1); /* 0x004cbbe0 */
undefined4 FUN_004cbc00(void); /* 0x004cbc00 */
undefined4 FUN_004cbf40(void); /* 0x004cbf40 */
void FUN_004cbf50(int param_1,undefined1 *param_2,uint param_3,uint param_4); /* 0x004cbf50 */
undefined4 FUN_004cc210(int *param_1,uint param_2); /* 0x004cc210 */
undefined4 FUN_004cc250(uint param_1); /* 0x004cc250 */
void FUN_004cc290(void); /* 0x004cc290 */
undefined4 FUN_004cc2c0(void); /* 0x004cc2c0 */
void FUN_004cc340(void); /* 0x004cc340 */
char * FUN_004cc370(int param_1); /* 0x004cc370 */
undefined4 FUN_004cc3a0(void); /* 0x004cc3a0 */
undefined4 FUN_004cc3c0(int param_1); /* 0x004cc3c0 */
int FUN_004cc410(int param_1,int param_2,uint param_3); /* 0x004cc410 */
void FUN_004cc590(void); /* 0x004cc590 */
void FUN_004cc620(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8); /* 0x004cc620 */
undefined4 FUN_004cc650(short *param_1,int param_2,int *param_3,int *param_4,int *param_5,int *param_6); /* 0x004cc650 */
void FUN_004cc6a0(uint param_1); /* 0x004cc6a0 */
void FUN_004cc7d0(int param_1); /* 0x004cc7d0 */
undefined4 FUN_004ccd00(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5 ,int param_6,byte param_7); /* 0x004ccd00 */
void FUN_004cd1e0(int param_1); /* 0x004cd1e0 */
void FUN_004cd300(int param_1,ushort *param_2,int param_3,int param_4); /* 0x004cd300 */
int FUN_004cd3f0(uint param_1,uint param_2); /* 0x004cd3f0 */
void FUN_004cd450(int param_1,byte *param_2,int param_3,int param_4,int param_5); /* 0x004cd450 */
undefined8 __fastcall FUN_004cd550(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5 ,int param_6,int param_7,uint param_8,int param_9,int param_10,undefined4 param_11, undefined4 param_12,undefined4 param_13,uint param_14); /* 0x004cd550 */
void FUN_004cd610(void); /* 0x004cd610 */
void FUN_004cd9b0(void); /* 0x004cd9b0 */
void FUN_004cdb80(void); /* 0x004cdb80 */
undefined4 FUN_004cdc90(int *param_1,uint param_2); /* 0x004cdc90 */
void FUN_004cdce0(void); /* 0x004cdce0 */
undefined4 FUN_004cdd10(void); /* 0x004cdd10 */
void FUN_004cdd60(void); /* 0x004cdd60 */
undefined4 FUN_004cdd80(void); /* 0x004cdd80 */
void FUN_004cde80(void); /* 0x004cde80 */
void FUN_004cdef0(void); /* 0x004cdef0 */
void FUN_004cdf00(void); /* 0x004cdf00 */
int FUN_004cdf10(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4); /* 0x004cdf10 */
void FUN_004cdf80(int param_1); /* 0x004cdf80 */
void FUN_004cdfa0(int param_1,undefined4 param_2); /* 0x004cdfa0 */
void FUN_004cdfd0(int param_1); /* 0x004cdfd0 */
uint FUN_004ce000(void); /* 0x004ce000 */
uint FUN_004ce010(void); /* 0x004ce010 */
void FUN_004ce020(int param_1); /* 0x004ce020 */
undefined4 FUN_004ce2e0(int *param_1,uint param_2); /* 0x004ce2e0 */
void FUN_004ce320(void); /* 0x004ce320 */
undefined4 FUN_004ce350(void); /* 0x004ce350 */
void FUN_004ce3b0(void); /* 0x004ce3b0 */
undefined4 FUN_004ce3e0(int *param_1,int param_2,int param_3,int param_4); /* 0x004ce3e0 */
undefined4 FUN_004ce840(int *param_1,int param_2,int param_3,int param_4,int param_5,undefined4 param_6, undefined4 *param_7); /* 0x004ce840 */
void FUN_004ce980(int *param_1); /* 0x004ce980 */
void FUN_004ce9b0(undefined4 *param_1,undefined4 param_2); /* 0x004ce9b0 */
void FUN_004cea30(int *param_1,uint *param_2,int param_3,int param_4,int *param_5,undefined4 param_6 ,undefined1 *param_7); /* 0x004cea30 */
void FUN_004cec40(char *param_1,int param_2,int param_3,char *param_4); /* 0x004cec40 */
undefined4 FUN_004ced70(int param_1,int param_2,undefined4 param_3,int param_4); /* 0x004ced70 */
undefined4 FUN_004cedc0(int param_1,int param_2,int param_3,undefined4 param_4,int param_5,int param_6, int param_7); /* 0x004cedc0 */
undefined4 FUN_004cf010(uint *param_1,int param_2,int param_3,int param_4,byte *param_5); /* 0x004cf010 */
undefined4 FUN_004cf520(uint *param_1,int param_2,int param_3,undefined4 param_4,int param_5); /* 0x004cf520 */
void FUN_004cfdb0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8, undefined4 param_9,undefined4 param_10); /* 0x004cfdb0 */
undefined8 __fastcall FUN_004cfdf0(undefined4 param_1,undefined4 param_2,undefined4 *param_3,ushort *param_4,uint param_5, char param_6,int param_7); /* 0x004cfdf0 */
undefined8 __fastcall FUN_004cfea0(undefined4 param_1,undefined4 param_2,int param_3); /* 0x004cfea0 */
undefined8 __fastcall FUN_004cff60(undefined4 param_1,undefined4 param_2,undefined4 *param_3,uint *param_4,uint param_5); /* 0x004cff60 */
undefined8 __fastcall FUN_004cffe0(undefined4 param_1,uint param_2,uint *param_3,ushort *param_4,uint param_5); /* 0x004cffe0 */
undefined8 __fastcall FUN_004d0070(undefined4 param_1,undefined4 param_2,undefined4 *param_3,uint *param_4,uint param_5); /* 0x004d0070 */
undefined8 __fastcall FUN_004d00f0(undefined4 param_1,uint param_2,uint *param_3,ushort *param_4,uint param_5); /* 0x004d00f0 */
undefined8 __fastcall FUN_004d0180(undefined4 param_1,undefined4 param_2,undefined4 *param_3,uint *param_4,uint param_5); /* 0x004d0180 */
undefined8 __fastcall FUN_004d01f0(undefined4 param_1,undefined4 param_2,int *param_3,ushort *param_4,uint param_5); /* 0x004d01f0 */
undefined8 __fastcall FUN_004d0260(undefined4 param_1,undefined4 param_2,int param_3,int param_4,int param_5,uint param_6, int param_7,uint param_8,uint param_9,int param_10,uint param_11,uint param_12); /* 0x004d0260 */
undefined4 FUN_004d0300(int *param_1,uint param_2); /* 0x004d0300 */
void FUN_004d03a0(void); /* 0x004d03a0 */
undefined4 FUN_004d03d0(void); /* 0x004d03d0 */
void FUN_004d0510(void); /* 0x004d0510 */
undefined4 FUN_004d0550(undefined4 param_1,undefined4 param_2,uint param_3); /* 0x004d0550 */
uint FUN_004d0610(void); /* 0x004d0610 */
undefined4 FUN_004d06a0(uint param_1,int param_2); /* 0x004d06a0 */
void FUN_004d0860(undefined1 *param_1,undefined4 param_2,int param_3,int param_4,uint param_5); /* 0x004d0860 */
void FUN_004d0a50(uint param_1); /* 0x004d0a50 */
void FUN_004d0a80(void); /* 0x004d0a80 */
void FUN_004d0a90(void); /* 0x004d0a90 */
void FUN_004d0aa0(void); /* 0x004d0aa0 */
void FUN_004d0ad0(int param_1,uint param_2); /* 0x004d0ad0 */
uint FUN_004d0b10(uint param_1); /* 0x004d0b10 */
void FUN_004d0b60(int param_1,undefined1 param_2); /* 0x004d0b60 */
int FUN_004d0b90(uint param_1); /* 0x004d0b90 */
void FUN_004d0bd0(undefined4 param_1); /* 0x004d0bd0 */
undefined4 FUN_004d0bf0(void); /* 0x004d0bf0 */
void FUN_004d0c00(uint param_1); /* 0x004d0c00 */
int FUN_004d0c30(uint param_1); /* 0x004d0c30 */
undefined4 FUN_004d0d70(undefined4 param_1,undefined4 param_2,uint param_3,uint param_4); /* 0x004d0d70 */
undefined4 FUN_004d0e00(undefined4 param_1,undefined4 param_2,uint *param_3,uint *param_4); /* 0x004d0e00 */
undefined1 FUN_004d0eb0(byte param_1); /* 0x004d0eb0 */
void FUN_004d0ed0(byte param_1,byte param_2); /* 0x004d0ed0 */
void FUN_004d0f00(undefined4 param_1,uint param_2,uint param_3,undefined1 param_4,undefined1 param_5 ,uint param_6); /* 0x004d0f00 */
void FUN_004d1180(int param_1,int param_2,uint param_3,int param_4,int param_5,uint param_6, int param_7,int param_8,int param_9,int param_10); /* 0x004d1180 */
void FUN_004d1690(void); /* 0x004d1690 */
void FUN_004d2340(int param_1,undefined4 param_2); /* 0x004d2340 */
void FUN_004d23e0(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x004d23e0 */
void FUN_004d2400(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x004d2400 */
undefined4 FUN_004d2420(int *param_1,uint param_2); /* 0x004d2420 */
void FUN_004d2480(void); /* 0x004d2480 */
undefined4 FUN_004d24b0(void); /* 0x004d24b0 */
void FUN_004d2520(void); /* 0x004d2520 */
undefined4 FUN_004d2550(uint param_1,undefined4 param_2,uint param_3); /* 0x004d2550 */
void FUN_004d25f0(void); /* 0x004d25f0 */
void FUN_004d2630(uint param_1); /* 0x004d2630 */
uint FUN_004d27b0(void); /* 0x004d27b0 */
undefined4 FUN_004d27c0(void); /* 0x004d27c0 */
undefined4 FUN_004d2940(void); /* 0x004d2940 */
void FUN_004d2aa0(uint param_1); /* 0x004d2aa0 */
void FUN_004d2bf0(void); /* 0x004d2bf0 */
undefined8 __fastcall FUN_004d2cb0(undefined4 param_1,undefined4 param_2,undefined4 *param_3,undefined4 *param_4, uint param_5); /* 0x004d2cb0 */
undefined8 __fastcall FUN_004d2ce0(undefined4 param_1,undefined4 param_2,undefined4 *param_3,undefined1 param_4, uint param_5); /* 0x004d2ce0 */
void FUN_004d2d40(undefined4 param_1,uint param_2,int param_3); /* 0x004d2d40 */
void FUN_004d2d70(undefined4 param_1); /* 0x004d2d70 */
void FUN_004d2d90(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4, undefined4 param_5,undefined4 param_6,int param_7,int param_8); /* 0x004d2d90 */
undefined4 FUN_004d2e80(undefined4 *param_1,uint param_2,int param_3,undefined4 param_4); /* 0x004d2e80 */
undefined4 FUN_004d2fb0(int param_1); /* 0x004d2fb0 */
float10 FUN_004d54b4(void); /* 0x004d54b4 */
int FUN_004d56f0(void); /* 0x004d56f0 */
undefined4 FUN_004d5740(int param_1); /* 0x004d5740 */
undefined4 FUN_004d57c0(int param_1,int param_2); /* 0x004d57c0 */
undefined4 FUN_004d5800(int param_1); /* 0x004d5800 */
undefined4 FUN_004d5830(undefined4 param_1,undefined4 param_2); /* 0x004d5830 */
char * FUN_004d5860(int param_1,char *param_2,uint param_3); /* 0x004d5860 */
undefined4 FUN_004d5990(uint param_1); /* 0x004d5990 */
undefined * FUN_004d5de0(int a1); /* 0x004d5de0 */
bool FUN_004d5e1c(void); /* 0x004d5e1c */
undefined4 FUN_004d5e30(void); /* 0x004d5e30 */
undefined * __stdcall FUN_004d5e35(int a1); /* 0x004d5e35 */
void FUN_004d5e50(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x004d5e50 */
void FUN_004d5e70(undefined1 *param_1,undefined4 param_2,int param_3); /* 0x004d5e70 */
void FUN_004d5eb0(int *param_1); /* 0x004d5eb0 */
uint __fastcall FUN_004d5ed0(undefined4 param_1); /* 0x004d5ed0 */
void FUN_004d5f70(undefined4 param_1); /* 0x004d5f70 */
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
undefined * Insane_Poll(void); /* 0x004bd370 */
undefined4 Insane_RegisterFilio(uint param_1,undefined4 *param_2); /* 0x004bd3a0 */
void Insane_SetOutputParams(uint *param_1); /* 0x004bd540 */
undefined4 Insane_ReadFrameHeader(int param_1,int param_2); /* 0x004bd7c0 */
undefined4 Insane_PrepareFrame(int *param_1,undefined4 *param_2,uint *param_3); /* 0x004bdb00 */
undefined8 __fastcall Insane_Blit8To16Doubled (undefined4 param_1,undefined4 param_2,uint *param_3,int param_4,uint *param_5,int param_6 ,int param_7,int param_8); /* 0x004bdca0 */
void Insane_BlitRowsDual(int param_1,int param_2,undefined4 *param_3,int param_4,int param_5, int param_6); /* 0x004bdd50 */
void Insane_BlitRows16(ushort *param_1,int param_2,int param_3,int param_4,int param_5,int param_6); /* 0x004bddb0 */

/* ===== smush.c ===== */
undefined4 Smush_Pause(void); /* 0x004bd500 */
undefined4 Smush_Resume(void); /* 0x004bd520 */
void Smush_Idle(undefined4 param_1); /* 0x004bd560 */
int __cdecl Smush_Open(char *name,int flags,int bufferSize,int x,int y,int w,int h,int a,int sixteenBit); /* 0x004bd570 */
undefined4 Smush_Close(void); /* 0x004bd930 */
int __cdecl Smush_Advance(int *outDone); /* 0x004bd970 */
void Smush_SetColorTable(uint param_1); /* 0x004bde90 */
undefined4 Smush_GetFrameRect(uint *param_1,uint *param_2); /* 0x004bdea0 */
undefined * __cdecl Smush_SetFile(uint param_1); /* 0x004bdf00 */

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
void LightEd_ReadControl(int param_1,int param_2); /* 0x004bf560 */
void LightEd_SetLightPosComponent(int param_1,short param_2,undefined4 param_3); /* 0x004bf760 */
void LightEd_SetLightAngle(int param_1,short param_2,uint param_3); /* 0x004bf7d0 */
void LightEd_SetAllEnabled(int param_1); /* 0x004bf850 */
void LightEd_MoveMarkerActor(void); /* 0x004bf8b0 */
void LightEd_GetLightAngles(int param_1,float *param_2); /* 0x004bf930 */

/* ===== mixer.c ===== */
undefined4 DSound_Init(void); /* 0x004c0ed0 */
void DSound_Shutdown(void); /* 0x004c1090 */
void __cdecl DSound_SetPrimaryVolume(int volume); /* 0x004c1110 */
undefined * __stdcall Mixer_TimerThread(int a1); /* 0x004cddf0 */
void Mixer_Update(void); /* 0x004ce060 */
void Mixer_ServiceVoices(void); /* 0x004ce1d0 */
void Mixer_ScheduleVoices(void); /* 0x004ce260 */
void DSound_FillStreamBuffer(void); /* 0x004d27d0 */
int DSound_GetPlayBlock(void); /* 0x004d2c60 */
void Mixer_Output(undefined4 param_1,undefined4 param_2); /* 0x004d2e60 */
undefined4 Mixer_ClearAccumulator(void); /* 0x004d3010 */
void Mixer_MixVoice(byte *param_1,int param_2,int param_3,int param_4,uint param_5,int param_6, int param_7,int param_8,int param_9,int param_10); /* 0x004d3040 */
undefined4 Mixer_ConvertTo16(undefined2 *param_1,int param_2); /* 0x004d31d0 */
void __cdecl Mixer_Mix8MonoLR(byte *src,int count,uint rateFrac,int accumOffset,int volL,int volR); /* 0x004d3240 */
void Mixer_Mix8Mono(byte *param_1,int param_2,uint param_3,int param_4,int param_5); /* 0x004d34a0 */
void Mixer_Mix16MonoLR(short *param_1,int param_2,uint param_3,int param_4,int param_5,int param_6); /* 0x004d36e0 */
void Mixer_Mix16Mono(short *param_1,int param_2,uint param_3,int param_4,int param_5); /* 0x004d38a0 */
void Mixer_MixStereoLR_A(ushort *param_1,int param_2,uint param_3,uint param_4,int param_5, int param_6); /* 0x004d3a60 */
void Mixer_MixStereo_A(ushort *param_1,int param_2,uint param_3,uint param_4,int param_5); /* 0x004d3c40 */
void Mixer_MixStereoLR_B(ushort *param_1,int param_2,uint param_3,uint param_4,int param_5, int param_6); /* 0x004d3e60 */
void Mixer_MixStereo_B(ushort *param_1,int param_2,uint param_3,uint param_4,int param_5); /* 0x004d40d0 */

/* ===== lecshare.c ===== */
undefined ** LecShare_Startup(undefined *param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4); /* 0x004c1390 */
undefined4 LecShare_Shutdown(void); /* 0x004c13f0 */
int LecShare_StartupModules(void); /* 0x004c1460 */
undefined4 LecShare_UnwindStartup(void); /* 0x004c1500 */
void LecShare_Reset(uint param_1,uint param_2); /* 0x004c1590 */
int __cdecl LecShare_Register(char *name,void *vtable); /* 0x004c15c0 */
uint LecShare_Unregister(undefined4 param_1); /* 0x004c1650 */
undefined4 LecShare_Resolve(char *param_1,char *param_2); /* 0x004c16c0 */
undefined4 LecShare_Release(uint param_1); /* 0x004c1800 */
undefined4 LecShare_BatchSubscribe(int *param_1,char *param_2); /* 0x004c1850 */
uint LecShare_Subscribe(char *param_1,uint param_2); /* 0x004c1990 */
uint LecShare_CountMatching(char *param_1); /* 0x004c1b60 */
uint * LecShare_FindEntry(undefined4 param_1); /* 0x004c1be0 */
undefined4 LecShare_Nop(void); /* 0x004c1e50 */

/* ===== zlib.c ===== */
undefined4 * gz_open(char *param_1,char *param_2,int param_3); /* 0x004c3e60 */
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
void gz_putLong(undefined4 param_1,uint param_2); /* 0x004c49c0 */
undefined4 zlibVersion(void); /* 0x004c4c40 */
undefined4 deflateParams_or_SetDictionary(int param_1); /* 0x004c57d0 */
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
int lua_pushnumber(); /* import */
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
int thunk_FUN_004cc590(); /* thunk */
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
