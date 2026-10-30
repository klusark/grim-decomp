/* IMUSE.DLL: prototypes of every decompiled function, by module */
#pragma once
#include "ghidra_types.h"

/* ===== imuse.c ===== */
void __cdecl Im_VimaDecodeBlock(ushort *param_1,uint param_2,undefined4 *param_3,undefined4 *param_4, undefined4 *param_5); /* 0x10001000 */
uint * __cdecl Im_VimaDecompress(uint *param_1,int *param_2,uint *param_3,uint *param_4,uint *param_5,int *param_6, uint *param_7); /* 0x100013c0 */
int __cdecl Im_DecodeSoundBlock(undefined4 *param_1,int param_2,uint param_3,uint param_4,uint param_5, uint param_6); /* 0x100017e0 */
void __cdecl Im_CodecInit(undefined1 *param_1); /* 0x10001ba0 */
void __cdecl Im_ConvertBlock(byte *param_1,undefined2 *param_2,byte *param_3,uint param_4); /* 0x10001bc0 */
void __cdecl Im_ConvertBlockImpl(short *param_1,undefined2 *param_2,byte *param_3,int param_4,uint param_5, int param_6); /* 0x10001c30 */
undefined4 Im_DispatchInit(void); /* 0x10001f10 */
undefined4 __cdecl Im_SwitchStreamImpl(int param_1,undefined4 param_2,uint param_3,uint param_4,uint param_5); /* 0x10002260 */
void __cdecl Im_DispatchMixTrack(int *param_1,uint param_2,uint param_3); /* 0x10002570 */
int __cdecl Im_DispatchAllocBuffers(int *param_1); /* 0x10002a60 */
int __cdecl Im_DispatchFetchNext(int *param_1); /* 0x10002d30 */
undefined4 __cdecl Im_DSoundInit(undefined4 param_1,undefined4 *param_2); /* 0x100036b0 */
int __cdecl Im_DSoundHeartbeat(int **buf_out,uint *count_out,int *rate_out); /* 0x10003730 */
undefined4 Im_DSoundShutdown(void); /* 0x100038d0 */
void __cdecl Im_DSoundCreateBuffer(int param_1); /* 0x10003930 */
undefined4 Im_DSoundReset(void); /* 0x10003ac0 */
undefined4 __cdecl Im_DSoundSave(undefined4 *param_1,uint param_2); /* 0x10003ae0 */
undefined4 __cdecl Im_DSoundRestore(undefined4 *param_1); /* 0x10003b10 */
undefined4 __cdecl Im_FadeParamImpl(int param_1,int param_2,uint param_3,int param_4); /* 0x10003b40 */
void __cdecl Im_FadesClearSound(int param_1,int param_2); /* 0x10003c70 */
uint Im_FadesHeartbeat(void); /* 0x10003cb0 */
undefined4 __cdecl Im_ApplyFXPreset(undefined2 *param_1,uint param_2,undefined2 *param_3,int *param_4,int *param_5, int param_6); /* 0x10004820 */
void FUN_10004970(void); /* 0x10004970 */
undefined4 Im_GroupsInit(void); /* 0x100049b0 */
undefined4 __cdecl Im_SetGroupVolImpl(uint param_1,uint param_2); /* 0x100049e0 */
undefined4 __cdecl Im_GetGroupVol(uint param_1); /* 0x10004a80 */
void Im_GuardEnter(void); /* 0x10004f50 */
int Im_GuardLeave(void); /* 0x10004f60 */
uint __cdecl Im_DispatchCommand(uint cmd,int a2,int a3,int a4,int a5,int a6,int a7,int a8,int a9,int a10,int a11); /* 0x10004f70 */
undefined4 __cdecl Im_MixerInit(undefined4 *param_1); /* 0x10005360 */
undefined4 Im_MixerReset(void); /* 0x10005490 */
undefined4 Im_MixerHeartbeat(void); /* 0x100054c0 */
void __cdecl Im_MixSamples(short *param_1,int param_2,int param_3,int param_4,int param_5,uint param_6, uint param_7,int param_8,int param_9); /* 0x100054f0 */
undefined4 __cdecl Im_ReadSoundData(int *param_1,int param_2); /* 0x10005610 */
void __cdecl Im_MixLoopA(short *param_1,int param_2,uint param_3,uint param_4,int param_5,int param_6); /* 0x100057a0 */
void __cdecl Im_MixLoopB(short *param_1,int param_2,uint param_3,uint param_4,int param_5); /* 0x100059a0 */
void __cdecl Im_MixLoopC(undefined2 *param_1,int param_2,uint param_3,int param_4,int param_5,int param_6); /* 0x10005b80 */
void __cdecl Im_MixLoopD(undefined2 *param_1,int param_2,uint param_3,uint param_4,int param_5); /* 0x10005db0 */
undefined4 __cdecl FUN_10006070(int cmd,...); /* 0x10006070 */
undefined4 __cdecl FUN_10006360(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5 ,undefined4 param_6,undefined4 param_7,undefined4 param_8); /* 0x10006360 */
undefined4 FUN_100063d0(void); /* 0x100063d0 */
int __cdecl FUN_10006400(undefined4 *param_1,int param_2); /* 0x10006400 */
int __cdecl FUN_10006470(undefined4 *param_1); /* 0x10006470 */
undefined4 FUN_100064d0(void); /* 0x100064d0 */
undefined4 __cdecl FUN_10006560(int param_1); /* 0x10006560 */
undefined4 __cdecl FUN_10006620(int param_1); /* 0x10006620 */
undefined4 FUN_100067a0(void); /* 0x100067a0 */
undefined4 __cdecl FUN_100067b0(uint param_1,char *param_2); /* 0x100067b0 */
void __cdecl FUN_100068b0(char *param_1,uint param_2,int param_3,uint param_4,int param_5,uint param_6, uint param_7,uint param_8); /* 0x100068b0 */
void __cdecl FUN_100070e0(char *marker); /* 0x100070e0 */
void FUN_10007110(void); /* 0x10007110 */
undefined4 __cdecl Im_SoundsFindByName(undefined4 param_1,char *param_2); /* 0x100089b0 */
void __cdecl Im_SoundsFreeSlot(int param_1); /* 0x10008b60 */
int iMUSE_GetPhoneme(int param_1,int param_2); /* 0x10008bb0 */
int __cdecl FUN_10008c40(int param_1,int param_2); /* 0x10008c40 */
int FUN_10008ce0(void); /* 0x10008ce0 */
undefined4 __stdcall FUN_10008e00(int a1,int a2,int a3,int a4,int a5); /* 0x10008e00 */
void FUN_10008e30(void); /* 0x10008e30 */
void FUN_10008e60(void); /* 0x10008e60 */
void __cdecl Im_SoundsPrepare(uint param_1); /* 0x100093d0 */
undefined4 FUN_10009530(int param_1); /* 0x10009530 */
undefined4 FUN_10009560(int param_1); /* 0x10009560 */
uint * grimSound_LipSyncLoad(uint *param_1); /* 0x100095d0 */
undefined4 __cdecl grimSound_LipSyncFree(int param_1); /* 0x100096b0 */
void FUN_10009700(void); /* 0x10009700 */
int * __cdecl Im_SoundsLoad(uint *param_1,char *param_2); /* 0x10009710 */
undefined4 __cdecl Im_SoundsUnload(undefined4 *param_1); /* 0x10009b20 */
uint __cdecl Im_SoundsReadBlock(undefined4 *param_1,undefined4 *param_2,uint param_3); /* 0x10009b90 */
void iMUSE_DeclareBufferSizes (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8, undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12); /* 0x1000a070 */
undefined4 iMUSE_GetMemoryFootprint(void); /* 0x1000a0f0 */
undefined4 iMUSE_GetSoundCacheSize(void); /* 0x1000a100 */
undefined4 iMUSE_SetHook(uint *param_1,uint param_2); /* 0x1000a110 */
undefined4 iMUSE_GetHook(uint *param_1); /* 0x1000a140 */
int __cdecl iMUSE_SetVoiceEffect(uint *param_1); /* 0x1000a160 */
undefined4 Im_TracksInit(void); /* 0x1000a1e0 */
undefined4 Im_ProcessStreamsImpl(void); /* 0x1000a300 */
int __cdecl Im_FindTrack(int param_1); /* 0x1000a580 */
undefined4 __cdecl Im_QueryStreamTrack(int param_1,undefined4 *param_2,undefined4 *param_3,int *param_4, undefined4 *param_5); /* 0x1000a5e0 */
undefined4 __cdecl Im_FeedStreamTrack(int param_1,undefined4 *param_2,uint param_3,undefined4 param_4); /* 0x1000a620 */
undefined4 __cdecl Im_RefillStreamTrack(uint *param_1); /* 0x1000a6d0 */
undefined4 Im_InitSubsystems(void); /* 0x1000a7e0 */
int Im_ShutdownSubsystems(void); /* 0x1000a8a0 */
void Im_PauseImpl(void); /* 0x1000a8d0 */
void Im_ResumeImpl(void); /* 0x1000a8f0 */
int __cdecl Im_SaveImpl(undefined4 *param_1,uint param_2); /* 0x1000a910 */
int __cdecl Im_RestoreImpl(undefined4 *param_1); /* 0x1000a970 */
undefined4 Im_UpdateGroupVolumes(void); /* 0x1000aa00 */
void Im_HeartbeatBody(void); /* 0x1000aa40 */
undefined4 __cdecl Im_StartSoundImpl(int param_1,int param_2,uint param_3); /* 0x1000ab00 */
undefined4 __cdecl Im_StopSoundImpl(int param_1); /* 0x1000abb0 */
undefined4 Im_StopAllSoundsImpl(void); /* 0x1000ac00 */
uint __cdecl Im_GetNextSoundImpl(uint param_1); /* 0x1000ac20 */
undefined4 __cdecl Im_QueryStreamImpl(int param_1,undefined4 *param_2,undefined4 *param_3,int *param_4, undefined4 *param_5); /* 0x1000ac60 */
undefined4 __cdecl Im_FeedStreamImpl(int param_1,undefined4 *param_2,uint param_3,undefined4 param_4); /* 0x1000ace0 */
void __cdecl Im_FreeTrack(int *param_1); /* 0x1000ad50 */
undefined4 __cdecl Im_SetParamImpl(int param_1,int param_2,uint param_3); /* 0x1000ada0 */
uint __cdecl Im_GetParamImpl(int param_1,int param_2); /* 0x1000af50 */
undefined4 __cdecl Im_SetHookImpl(int param_1,uint param_2); /* 0x1000b0a0 */
undefined4 __cdecl Im_GetHookImpl(int param_1); /* 0x1000b0e0 */
int * __cdecl Im_AllocTrackOrSteal(int param_1); /* 0x1000b110 */
undefined4 Im_TriggersInit(void); /* 0x1000b170 */
undefined4 __cdecl Im_TriggersSave(undefined4 *param_1,int param_2); /* 0x1000b1a0 */
undefined4 __cdecl Im_TriggersRestore(undefined4 *param_1); /* 0x1000b1e0 */
undefined4 __cdecl Im_SetTriggerImpl(int sound,char *marker,int cmd,int p0,int p1,int p2,int p3,int p4,int p5,int p6, int p7,int p8,int p9); /* 0x1000b220 */
int __cdecl Im_CheckTriggerImpl(int param_1,byte *param_2,int param_3); /* 0x1000b2e0 */
undefined4 __cdecl Im_ClearTriggerImpl(int param_1,byte *param_2,int param_3); /* 0x1000b380 */
undefined4 * __cdecl Im_FireTriggers(int param_1,char *param_2); /* 0x1000b430 */
undefined4 __cdecl Im_DeferCommandImpl(int time,int cmd,int p0,int p1,int p2,int p3,int p4,int p5,int p6,int p7,int p8, int p9); /* 0x1000b570 */
void Im_ProcessDeferred(void); /* 0x1000b5e0 */
int __cdecl Im_GetTriggerParam(int param_1); /* 0x1000b630 */
void __cdecl Im_RunTriggerCommand(undefined4 *param_1,undefined4 param_2); /* 0x1000b6a0 */
void __cdecl Im_RunDeferredCommand(int param_1); /* 0x1000b710 */
char * __cdecl Im_StrChr(char *param_1,char param_2); /* 0x1000bd50 */
uint * __cdecl Im_MemCopy(uint *param_1,uint *param_2,uint param_3); /* 0x1000bd80 */
uint __cdecl Im_StrCmpNoCase(byte *param_1,byte *param_2); /* 0x1000be80 */

/* ===== imuse_dispatch.c ===== */
undefined4 iMUSE_Dispatch__1fd0(void); /* 0x10001fd0 */
undefined4 * __cdecl iMUSE_Dispatch__1ff0(int param_1); /* 0x10001ff0 */
undefined4 __cdecl iMUSE_Dispatch__2010(undefined4 *param_1,uint param_2); /* 0x10002010 */
undefined4 __cdecl iMUSE_Dispatch__2040(undefined4 *param_1); /* 0x10002040 */
undefined4 iMUSE_Dispatch__20c0(void); /* 0x100020c0 */
undefined4 __cdecl iMUSE_Dispatch__2170(int param_1,uint param_2); /* 0x10002170 */
undefined4 __cdecl iMUSE_Dispatch__2200(int param_1); /* 0x10002200 */
void iMUSE_Dispatch__2a00(void); /* 0x10002a00 */
int __cdecl iMUSE_Dispatch__2fe0(undefined4 *param_1,undefined4 *param_2); /* 0x10002fe0 */
uint __cdecl iMUSE_Dispatch__30d0(int param_1,int param_2,int param_3); /* 0x100030d0 */
void __cdecl iMUSE_Dispatch__3130(int *param_1); /* 0x10003130 */
int * __cdecl iMUSE_Dispatch__31d0(int *param_1,int param_2,int *param_3); /* 0x100031d0 */
void __cdecl iMUSE_Dispatch__3250(int *param_1,undefined4 *param_2,int param_3,int param_4); /* 0x10003250 */
void __cdecl iMUSE_Dispatch__3430(int *param_1,int param_2); /* 0x10003430 */
int __cdecl iMUSE_Dispatch__34b0(int *param_1); /* 0x100034b0 */
int __cdecl iMUSE_Dispatch__3510(int *param_1,int param_2); /* 0x10003510 */
undefined4 * iMUSE_Dispatch__3570(void); /* 0x10003570 */
int __cdecl iMUSE_Dispatch__35a0(uint *param_1); /* 0x100035a0 */
void __cdecl iMUSE_Dispatch__3640(int param_1); /* 0x10003640 */

/* ===== imuse_dsound.c ===== */
int iMUSE_dsound__3a80(void); /* 0x10003a80 */
undefined4 __cdecl iMUSE_dsound__4540(uint param_1); /* 0x10004540 */
undefined4 __cdecl iMUSE_dsound__4570(uint param_1); /* 0x10004570 */
undefined4 __cdecl iMUSE_dsound__45a0(uint param_1); /* 0x100045a0 */
undefined4 __cdecl iMUSE_dsound__45c0(uint param_1,undefined4 param_2,undefined4 param_3); /* 0x100045c0 */
undefined4 __cdecl iMUSE_dsound__4600(uint param_1,undefined4 param_2,undefined4 param_3); /* 0x10004600 */
undefined4 __cdecl iMUSE_dsound__4640(int param_1); /* 0x10004640 */
undefined4 FUN_10004660(undefined4 param_1); /* 0x10004660 */
int __cdecl FUN_10004750(uint param_1); /* 0x10004750 */

/* ===== imuse_api.c ===== */
undefined4 ImInitFilelist(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4); /* 0x10003d70 */
int ImSaveFilelist(int *param_1,uint param_2); /* 0x10003dc0 */
int ImRestoreFilelist(int *param_1); /* 0x10003e50 */
int ImLoadSound(char *param_1,undefined4 param_2); /* 0x10003f90 */
undefined4 __cdecl ImUnloadSound(int param_1); /* 0x100040b0 */
undefined4 __cdecl ImUnloadAll(void); /* 0x10004100 */
int ImOpenSound(char *param_1,undefined4 param_2); /* 0x10004140 */
undefined4 __cdecl ImCloseSound(int param_1); /* 0x10004260 */
undefined4 __cdecl ImCloseAll(void); /* 0x100042b0 */
int ImFindSound(char *param_1); /* 0x100042f0 */
uint __cdecl ImFlushSounds(void); /* 0x10004380 */
undefined4 __cdecl FUN_10004460(int *param_1,int *param_2); /* 0x10004460 */
undefined4 __cdecl FUN_100044b0(int *param_1,int *param_2); /* 0x100044b0 */
undefined4 ImInitialize(void); /* 0x10004aa0 */
undefined4 __cdecl ImPrintf(char *fmt,...); /* 0x10004b20 */
int ImPause(void); /* 0x10004b40 */
int ImResume(void); /* 0x10004b60 */
int __cdecl ImSave(undefined4 *param_1,int param_2); /* 0x10004ba0 */
int __cdecl ImRestore(int *param_1); /* 0x10004c10 */
undefined4 __cdecl ImSetGroupVol(uint param_1,uint param_2); /* 0x10004c60 */
undefined4 __cdecl ImStartSound(uint param_1,int param_2); /* 0x10004c80 */
undefined4 __cdecl ImStopSound(int param_1); /* 0x10004cd0 */
undefined4 ImStopAllSounds(void); /* 0x10004ce0 */
uint __cdecl ImGetNextSound(uint param_1); /* 0x10004d00 */
undefined4 __cdecl ImSetParam(int param_1,int param_2,uint param_3); /* 0x10004d10 */
uint __cdecl ImGetParam(int param_1,int param_2); /* 0x10004d30 */
undefined4 __cdecl ImFadeParam(int param_1,int param_2,uint param_3,int param_4); /* 0x10004d90 */
undefined4 __cdecl ImSetHook(int param_1,uint param_2); /* 0x10004db0 */
undefined4 __cdecl ImGetHook(int param_1); /* 0x10004dd0 */
undefined4 __cdecl ImSetTrigger(int sound,char *marker,int cmd,int p0,int p1,int p2,int p3,int p4,int p5,int p6,int p7, int p8,int p9); /* 0x10004de0 */
int __cdecl ImCheckTrigger(int param_1,byte *param_2,int param_3); /* 0x10004e10 */
undefined4 __cdecl ImClearTrigger(int param_1,byte *param_2,int param_3); /* 0x10004e30 */
undefined4 __cdecl ImDeferCommand(int time,int cmd,int p0,int p1,int p2,int p3,int p4,int p5,int p6,int p7,int p8, int p9); /* 0x10004e50 */
undefined4 __cdecl ImStartStream(uint param_1,int param_2,uint param_3); /* 0x10004e80 */
undefined4 __cdecl ImSwitchStream(int param_1,undefined4 param_2,uint param_3,uint param_4,uint param_5); /* 0x10004ec0 */
undefined4 __cdecl ImQueryStream(int param_1,undefined4 *param_2,undefined4 *param_3,int *param_4,undefined4 *param_5); /* 0x10004f00 */
undefined4 __cdecl ImFeedStream(int param_1,undefined4 *param_2,uint param_3,undefined4 param_4); /* 0x10004f30 */
uint __cdecl ImHeartbeat(void); /* 0x10005190 */
undefined4 ImStartRecording(undefined4 param_1,int param_2); /* 0x10005300 */
undefined4 ImStopRecording(void); /* 0x10005350 */
undefined4 __cdecl ImInitializeScript(int a1,int a2,int a3,int a4,int a5,int a6,int a7); /* 0x10007130 */
undefined4 __cdecl ImTerminateScript(void); /* 0x10007170 */
undefined4 __cdecl ImSaveScript(int a1,int a2); /* 0x10007180 */
undefined4 __cdecl ImRestoreScript(int a1); /* 0x100071a0 */
undefined4 __cdecl ImRefreshScript(void); /* 0x100071b0 */
undefined4 __cdecl ImSetState(int a1); /* 0x100071c0 */
undefined4 __cdecl ImSetSequence(int a1); /* 0x100071d0 */
undefined4 __cdecl ImSetCuePoint(int a1); /* 0x100071e0 */
undefined4 __cdecl ImSetAttribute(int a1,int a2); /* 0x100071f0 */
undefined4 __cdecl SoundsAllocateBuffer(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4); /* 0x10007210 */
undefined4 __cdecl FUN_10007250(int param_1); /* 0x10007250 */
int * SoundsRegisterVoice(char *param_1); /* 0x100072b0 */
undefined4 __cdecl SoundsCloseVoiceFile(void); /* 0x100073c0 */
undefined4 __cdecl SoundsReOpenVoiceFile(void); /* 0x100073f0 */
undefined4 __cdecl SoundsLoadStartSound(uint *param_1,int param_2,uint param_3); /* 0x10007410 */
undefined4 __cdecl SoundsLoadProcessStartSound(uint *param_1,int param_2,uint param_3); /* 0x10007470 */
undefined4 __cdecl SoundsStopSound(uint *param_1); /* 0x10007500 */
uint __cdecl SoundsGetParam(uint *param_1,int param_2); /* 0x10007520 */
undefined4 __cdecl SoundsSetParam(uint *param_1,int param_2,uint param_3); /* 0x10007550 */
undefined4 SoundsFadeParam(uint *param_1,int param_2,uint param_3,int param_4); /* 0x10007580 */
int __cdecl SoundsIsSoundInUse(uint *param_1); /* 0x100075d0 */
int __cdecl SoundsIsSoundPlaying(uint *param_1); /* 0x10007640 */
undefined4 __cdecl SoundsFillStreamsWhileMusicCritical(int param_1); /* 0x10007670 */
undefined4 FUN_100076b0(void); /* 0x100076b0 */
undefined4 __cdecl FUN_10007700(undefined4 *param_1,undefined4 *param_2,int *param_3,undefined4 *param_4); /* 0x10007700 */
int __cdecl SoundsFloodMusicBuffer(void); /* 0x10007790 */
undefined4 FUN_100077c0(void); /* 0x100077c0 */
void __cdecl SoundsPeriodic(void); /* 0x10007810 */
uint __cdecl SoundsGetMusicPosition(void); /* 0x10007830 */
undefined4 __cdecl SoundsSetMuscriptLocal(undefined4 param_1); /* 0x100078a0 */
undefined4 __cdecl SoundsSetMuscriptRemote(undefined4 param_1); /* 0x100078b0 */
undefined4 __cdecl Sounds_PlatformDevice(undefined4 param_1); /* 0x100078c0 */
undefined4 SoundsInitialize(undefined4 param_1,undefined4 *param_2); /* 0x100078d0 */
undefined4 FUN_10007920(void); /* 0x10007920 */
void FUN_10007a20(void); /* 0x10007a20 */
void FUN_10007a60(undefined4 param_1); /* 0x10007a60 */
void FUN_10007a70(undefined4 param_1); /* 0x10007a70 */
int FUN_10007a80(int param_1); /* 0x10007a80 */
int FUN_10007a90(uint *param_1,int param_2); /* 0x10007a90 */
int FUN_10007bc0(int param_1,int param_2,int param_3); /* 0x10007bc0 */
undefined4 * FUN_10007ca0(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3); /* 0x10007ca0 */
void FUN_10008140(void); /* 0x10008140 */
void FUN_100081f0(void); /* 0x100081f0 */
undefined4 FUN_10008250(code *param_1); /* 0x10008250 */
undefined4 FUN_10008580(code *param_1,uint param_2); /* 0x10008580 */
undefined4 FUN_10008860(void); /* 0x10008860 */
undefined4 FUN_100088a0(void); /* 0x100088a0 */
int __cdecl Sounds_ResolveName_LoadIfNeeded(uint *param_1); /* 0x10008ec0 */
int Sounds_EvictOldestIdleSlot(void); /* 0x100092f0 */
int __cdecl ImFile_Read(int *param_1,int param_2,int param_3); /* 0x1000b940 */
int __cdecl ImFile_ReadImpl(int *param_1,int param_2,int param_3); /* 0x1000b980 */
undefined4 __cdecl FUN_1000ba20(undefined4 param_1,char *param_2,undefined4 param_3); /* 0x1000ba20 */
int __cdecl FUN_1000ba60(undefined4 param_1,undefined4 param_2); /* 0x1000ba60 */
void FUN_1000ba80(void); /* 0x1000ba80 */
void FUN_1000baa0(void); /* 0x1000baa0 */
undefined4 __cdecl ImFile_Close(int *param_1); /* 0x1000bb10 */
undefined4 __cdecl ImFile_CloseImpl(int *param_1); /* 0x1000bb50 */
uint __cdecl ImFile_Open(char *param_1,uint param_2,uint param_3,int *param_4); /* 0x1000bbc0 */
uint __cdecl ImFile_OpenImpl(char *param_1,uint param_2,uint param_3,int *param_4); /* 0x1000bc00 */
void __cdecl ImFile_LockInit(int param_1); /* 0x1000c4f0 */
int __cdecl ImFile_UnlockInner(int param_1); /* 0x1000c570 */
void __cdecl ImFile_Lock(uint param_1); /* 0x1000c590 */
void __cdecl FUN_1000c5d0(int param_1,int param_2); /* 0x1000c5d0 */
void __cdecl ImFile_Unlock(uint param_1); /* 0x1000c600 */
void __cdecl FUN_1000c640(int param_1,int param_2); /* 0x1000c640 */
int __cdecl FUN_1000c670(int *param_1,char *param_2,undefined4 *param_3); /* 0x1000c670 */
void __cdecl FUN_1000d000(uint param_1,int *param_2,int *param_3); /* 0x1000d000 */
void __cdecl FUN_1000d050(uint param_1,int param_2,int *param_3,int *param_4); /* 0x1000d050 */
void __cdecl FUN_1000d090(char *param_1,int param_2,int *param_3,int *param_4); /* 0x1000d090 */
undefined4 __cdecl FUN_1000d0d0(int *param_1); /* 0x1000d0d0 */
undefined8 __cdecl FUN_1000d0f0(int *param_1); /* 0x1000d0f0 */
undefined4 __cdecl FUN_1000d110(undefined4 *param_1); /* 0x1000d110 */
void FUN_1000d130(void); /* 0x1000d130 */
int __stdcall FUN_1000d1f0(int a1,int a2,int a3,int a4); /* 0x1000d1f0 */

/* ===== soundstartvoicestream.c ===== */
int __cdecl SoundStartVoiceStream(undefined4 param_1,uint volume,uint pan); /* 0x100088d0 */

/* ===== soundstopvoicestream.c ===== */
undefined4 __cdecl SoundStopVoiceStream(void); /* 0x10008970 */

/* ===== soundgetvoicetime.c ===== */
uint SoundGetVoiceTime(void); /* 0x10008990 */

/* ===== imuse_sounds.c ===== */
undefined4 __cdecl iMUSE_sounds__9e10(undefined *param_1); /* 0x10009e10 */
undefined4 __cdecl iMUSE_sounds__9e40(undefined *param_1,int param_2,int param_3); /* 0x10009e40 */
int __cdecl iMUSE_sounds__9eb0(int param_1,uint param_2); /* 0x10009eb0 */
int __cdecl FUN_10009ef0(uint param_1,uint *param_2); /* 0x10009ef0 */
undefined4 FUN_10009f10(undefined4 param_1); /* 0x10009f10 */
void FUN_10009f40(int param_1); /* 0x10009f40 */
void FUN_1000a010(undefined4 param_1); /* 0x1000a010 */
void FUN_1000a030(int param_1); /* 0x1000a030 */

/* ===== imuse_stream.c ===== */
uint * __cdecl iMUSE_stream__a210(uint param_1,uint param_2,uint param_3); /* 0x1000a210 */
undefined4 __cdecl iMUSE_stream__a2d0(undefined4 *param_1); /* 0x1000a2d0 */
int __cdecl iMUSE_stream__a420(int param_1,uint param_2); /* 0x1000a420 */
int __cdecl iMUSE_stream__a490(int param_1,int param_2,uint param_3); /* 0x1000a490 */
undefined4 __cdecl iMUSE_stream__a500(int param_1,uint param_2); /* 0x1000a500 */
undefined4 __cdecl iMUSE_stream__a540(int param_1,uint param_2); /* 0x1000a540 */
undefined4 __cdecl iMUSE_stream__a5a0(undefined4 *param_1,undefined4 param_2,undefined4 param_3); /* 0x1000a5a0 */
undefined4 __cdecl iMUSE_stream__b760(int *param_1,int *param_2); /* 0x1000b760 */
undefined4 __cdecl iMUSE_stream__b7a0(int *param_1,int *param_2); /* 0x1000b7a0 */
undefined4 __cdecl iMUSE_stream__b810(undefined1 *param_1); /* 0x1000b810 */
undefined4 __cdecl iMUSE_stream__b840(int *param_1,int param_2); /* 0x1000b840 */
int __cdecl FUN_1000b8d0(undefined1 *param_1,char *param_2,undefined4 *param_3); /* 0x1000b8d0 */

/* ===== hmi.c ===== */
longlong hmi__bae0(void); /* 0x1000bae0 */

/* ===== crt.c ===== */
int __cdecl atol(byte *param_1); /* 0x1000bf50 */
int __cdecl atoi(byte *param_1); /* 0x1000bff0 */
uint __cdecl bsearch(undefined4 param_1,uint param_2,uint param_3,int param_4,undefined *param_5); /* 0x1000c000 */
undefined4 __stdcall entry(int a1,int a2,int a3); /* 0x1000c350 */
void __cdecl _amsg_exit(int param_1); /* 0x1000c400 */
uint __cdecl _flsbuf(uint param_1,int *param_2); /* 0x1000d210 */
void __cdecl _dosmaperr(undefined *param_1); /* 0x1000d340 */
int * _errno(void); /* 0x1000d3c0 */
int * __doserrno(void); /* 0x1000d3d0 */
int __cdecl _lseek(uint param_1,undefined4 param_2,undefined4 param_3); /* 0x1000d3e0 */
int __cdecl _lseek_lk(uint param_1,int param_2,int param_3); /* 0x1000d460 */
undefined4 __cdecl _flush(int *param_1); /* 0x1000d520 */
int __cdecl _ftell_lk(undefined4 *param_1); /* 0x1000d660 */
void __cdecl free(undefined *param_1); /* 0x1000e0c0 */
undefined4 __cdecl _close(uint param_1); /* 0x1000e130 */
undefined4 __cdecl _close_lk(uint param_1); /* 0x1000e1a0 */
void __cdecl _freebuf(undefined4 *param_1); /* 0x1000e230 */
int __cdecl _write(uint param_1,char *param_2,uint param_3); /* 0x1000e270 */
int __cdecl _write_lk(uint param_1,char *param_2,uint param_3); /* 0x1000e2f0 */
uint __cdecl _tolower_lk(uint param_1); /* 0x1000e5a0 */
uint __cdecl _isctype(int param_1,uint param_2); /* 0x1000e6a0 */
int __cdecl __crtLCMapStringA(int param_1,uint param_2,char *param_3,int param_4,int param_5,int param_6, uint param_7,int param_8); /* 0x1000e780 */
int __cdecl _strncnt(char *param_1,int param_2); /* 0x1000e9b0 */
void __cdecl exit(undefined4 param_1); /* 0x1000ea10 */
void __cdecl doexit(int param_1,int param_2,int param_3); /* 0x1000ea40 */
void _lockexit(void); /* 0x1000eb00 */
void _unlockexit(void); /* 0x1000eb10 */
void __cdecl _initterm(undefined4 *param_1,undefined4 *param_2); /* 0x1000eb20 */
void __cdecl _initptd(int param_1); /* 0x1000ebd0 */
int * _getptd(void); /* 0x1000ebf0 */
void _FF_MSGBANNER(void); /* 0x1000fa30 */
void __cdecl _NMSG_WRITE(int param_1); /* 0x1000fa70 */
int * __cdecl malloc(uint param_1); /* 0x1000fc50 */
int * __cdecl _nh_malloc(uint param_1,int param_2); /* 0x1000fc70 */
int * __cdecl _heap_alloc(int param_1); /* 0x1000fcc0 */
uint __cdecl _isatty(uint param_1); /* 0x1000fd20 */
int * __cdecl calloc(int param_1,int param_2); /* 0x1000ff30 */
void __cdecl _getbuf(int *param_1); /* 0x10010080 */
undefined4 __cdecl _free_osfhnd(uint param_1); /* 0x10010300 */
int __cdecl _get_osfhandle(uint param_1); /* 0x100103a0 */
void __cdecl _lock_fhandle(uint param_1); /* 0x100103f0 */
void __cdecl _unlock_fhandle(uint param_1); /* 0x10010460 */
undefined ** __sbh_alloc_new_region(void); /* 0x100114c0 */
void __cdecl __sbh_release_region(undefined **param_1); /* 0x10011630 */
void __cdecl __sbh_decommit_pages(int param_1); /* 0x10011690 */
int __cdecl __sbh_find_block(undefined *param_1,undefined4 *param_2,uint *param_3); /* 0x10011760 */
void __cdecl __sbh_free_block(int param_1,int param_2,byte *param_3); /* 0x100117c0 */
int * __cdecl __sbh_alloc_block(uint param_1); /* 0x10011820 */
int __cdecl __sbh_alloc_new_group(int *param_1,uint param_2,uint param_3); /* 0x10011a60 */
int __cdecl __crtGetStringTypeA(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6, int param_7); /* 0x10012d50 */
undefined4 __cdecl __crtMessageBoxA(undefined4 param_1,undefined4 param_2,undefined4 param_3); /* 0x10012e90 */
undefined4 __cdecl _callnewh(undefined4 param_1); /* 0x10012f20 */

/* ===== crt_unnamed.c ===== */
int __cdecl FUN_1000c0a0(int param_1); /* 0x1000c0a0 */
uint __cdecl FUN_1000c130(uint param_1); /* 0x1000c130 */
undefined4 __stdcall FUN_1000c230(int a1,int a2,int a3); /* 0x1000c230 */
void FUN_1000c440(void); /* 0x1000c440 */
void FUN_1000c470(void); /* 0x1000c470 */
int FUN_1000d4e0(int *param_1); /* 0x1000d4e0 */
void FUN_1000d590(void); /* 0x1000d590 */
int FUN_1000d5a0(int param_1); /* 0x1000d5a0 */
undefined4 * __cdecl FUN_1000d810(undefined4 param_1,char *param_2,undefined4 param_3,undefined4 *param_4); /* 0x1000d810 */
undefined4 * FUN_1000d9e0(void); /* 0x1000d9e0 */
void FUN_1000dac0(void); /* 0x1000dac0 */
undefined4 FUN_1000db30(void); /* 0x1000db30 */
void FUN_1000db60(char *param_1); /* 0x1000db60 */
void FUN_1000dbc0(char *param_1); /* 0x1000dbc0 */
undefined4 FUN_1000dc30(double *param_1); /* 0x1000dc30 */
void FUN_1000dc50(int param_1,undefined4 *param_2,undefined4 param_3); /* 0x1000dc50 */
int FUN_1000dcb0(undefined4 *param_1,int param_2,int param_3,undefined4 param_4); /* 0x1000dcb0 */
undefined1 * FUN_1000dd30(undefined1 *param_1,int param_2,int param_3,int *param_4,char param_5); /* 0x1000dd30 */
int FUN_1000de30(undefined4 *param_1,int param_2,int param_3); /* 0x1000de30 */
undefined1 * FUN_1000dea0(undefined1 *param_1,uint param_2,int *param_3,char param_4); /* 0x1000dea0 */
void FUN_1000df60(undefined4 *param_1,int param_2,int param_3,undefined4 param_4); /* 0x1000df60 */
void FUN_1000e020(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4, undefined4 param_5); /* 0x1000e020 */
void FUN_1000e090(char *param_1,int param_2); /* 0x1000e090 */
undefined4 FUN_1000e500(void); /* 0x1000e500 */
uint FUN_1000e510(uint param_1); /* 0x1000e510 */
void FUN_1000e9e0(void); /* 0x1000e9e0 */
void FUN_1000ea30(void); /* 0x1000ea30 */
undefined4 FUN_1000eb40(void); /* 0x1000eb40 */
void FUN_1000eba0(void); /* 0x1000eba0 */
void __cdecl FUN_1000ec70(undefined *param_1); /* 0x1000ec70 */
void FUN_1000ed20(void); /* 0x1000ed20 */
void FUN_1000ef30(void); /* 0x1000ef30 */
void FUN_1000ef90(void); /* 0x1000ef90 */
void FUN_1000f080(void); /* 0x1000f080 */
void __cdecl FUN_1000f120(byte *param_1,undefined4 *param_2,byte *param_3,int *param_4,int *param_5); /* 0x1000f120 */
undefined4 __cdecl FUN_1000f330(int param_1); /* 0x1000f330 */
int __cdecl FUN_1000f560(int param_1); /* 0x1000f560 */
undefined4 __cdecl FUN_1000f5b0(undefined4 param_1); /* 0x1000f5b0 */
void FUN_1000f610(void); /* 0x1000f610 */
void FUN_1000f650(void); /* 0x1000f650 */
void FUN_1000f830(void); /* 0x1000f830 */
char * FUN_1000f840(void); /* 0x1000f840 */
undefined4 FUN_1000f9a0(void); /* 0x1000f9a0 */
void FUN_1000f9e0(void); /* 0x1000f9e0 */
undefined4 __stdcall FUN_1000fa20(int a1,int a2,int a3); /* 0x1000fa20 */
int __cdecl FUN_1000fd50(undefined1 *param_1,ushort param_2); /* 0x1000fd50 */
int __cdecl FUN_1000fdc0(undefined1 *param_1,ushort param_2); /* 0x1000fdc0 */
int __stdcall FUN_1000fe40(int a1,int a2,int a3,int a4); /* 0x1000fe40 */
int __stdcall FUN_1000feb0(int a1,int a2,int a3,int a4); /* 0x1000feb0 */
uint FUN_100100e0(void); /* 0x100100e0 */
undefined4 __cdecl FUN_10010250(uint param_1,int param_2); /* 0x10010250 */
undefined4 FUN_10010490(uint param_1); /* 0x10010490 */
uint __cdecl FUN_10010530(undefined4 param_1,uint param_2,undefined4 param_3,byte param_4); /* 0x10010530 */
uint FUN_100108d0(uint param_1,uint param_2); /* 0x100108d0 */
void FUN_10010910(undefined4 param_1,uint param_2); /* 0x10010910 */
uint FUN_10010930(uint param_1); /* 0x10010930 */
int FUN_100109d0(void); /* 0x100109d0 */
undefined4 FUN_10010a60(int param_1,int param_2); /* 0x10010a60 */
int FUN_10010ad0(void); /* 0x10010ad0 */
int FUN_10010b40(int param_1,int param_2); /* 0x10010b40 */
void FUN_10010be0(int param_1,undefined4 *param_2); /* 0x10010be0 */
void FUN_10010c00(undefined4 *param_1); /* 0x10010c00 */
undefined4 FUN_10010c10(int *param_1); /* 0x10010c10 */
void FUN_10010c30(uint *param_1,int param_2); /* 0x10010c30 */
undefined4 FUN_10010cf0(ushort *param_1,uint *param_2,int *param_3); /* 0x10010cf0 */
void FUN_10010ec0(undefined4 param_1,undefined4 param_2); /* 0x10010ec0 */
void FUN_10010ee0(undefined4 param_1,undefined4 param_2); /* 0x10010ee0 */
void FUN_10010f00(undefined4 param_1,undefined4 param_2); /* 0x10010f00 */
void FUN_10010f40(undefined4 param_1,undefined4 param_2); /* 0x10010f40 */
void FUN_10010f80(char *param_1,int param_2,int param_3); /* 0x10010f80 */
int * FUN_10011020(undefined4 param_1,undefined4 param_2,int *param_3,char *param_4); /* 0x10011020 */
void FUN_100110b0(uint *param_1,uint *param_2); /* 0x100110b0 */
undefined4 * FUN_10011170(undefined4 *param_1,undefined4 *param_2,uint param_3); /* 0x10011170 */
void FUN_100114b0(void); /* 0x100114b0 */
undefined4 FUN_10011be0(void); /* 0x10011be0 */
uint FUN_10011c90(int param_1); /* 0x10011c90 */
void FUN_10012010(undefined4 *param_1); /* 0x10012010 */
uint FUN_10012250(char *param_1,int param_2); /* 0x10012250 */
undefined4 FUN_10012350(void); /* 0x10012350 */
undefined4 FUN_10012550(void); /* 0x10012550 */
uint FUN_10012640(int param_1); /* 0x10012640 */
void FUN_10012790(char *param_1); /* 0x10012790 */
void FUN_100127d0(int param_1); /* 0x100127d0 */
undefined4 FUN_10012840(void); /* 0x10012840 */
int FUN_10012bc0(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6); /* 0x10012bc0 */
int FUN_10012f40(void); /* 0x10012f40 */
int __cdecl FUN_10013090(uint param_1,char *param_2,int param_3); /* 0x10013090 */
undefined4 FUN_100132c0(uint param_1,uint param_2,uint *param_3); /* 0x100132c0 */
void FUN_100132f0(undefined4 *param_1,undefined4 *param_2); /* 0x100132f0 */
void FUN_10013360(uint *param_1); /* 0x10013360 */
void FUN_10013390(uint *param_1); /* 0x10013390 */
void FUN_100133c0(char *param_1,int param_2,uint *param_3); /* 0x100133c0 */
undefined4 FUN_100134c0(ushort *param_1,int *param_2,byte *param_3,undefined4 param_4,int param_5,int param_6, int param_7); /* 0x100134c0 */
undefined4 FUN_10013c50(int param_1,uint param_2,uint param_3,int param_4,byte param_5,short *param_6); /* 0x10013c50 */
undefined4 FUN_10013fe0(int param_1,undefined4 param_2,undefined4 param_3,char *param_4); /* 0x10013fe0 */
int __cdecl FUN_100142a0(uint param_1,int param_2); /* 0x100142a0 */
void FUN_10014310(void); /* 0x10014310 */
void FUN_10014340(int *param_1,int *param_2); /* 0x10014340 */
void FUN_10014600(undefined2 *param_1,uint param_2,int param_3); /* 0x10014600 */
int FUN_10014690(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4); /* 0x10014690 */
int FUN_100147c0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4); /* 0x100147c0 */

/* ===== referenced, not decompiled here (thunks, imports, unknown FUN_) ===== */
int STDCALL CloseHandle() __asm__("_CloseHandle@4"); /* import */
int STDCALL CreateFileA() __asm__("_CreateFileA@28"); /* import */
int STDCALL DeleteCriticalSection() __asm__("_DeleteCriticalSection@4"); /* import */
int STDCALL EnterCriticalSection() __asm__("_EnterCriticalSection@4"); /* import */
int STDCALL ExitProcess() __asm__("_ExitProcess@4"); /* import */
int STDCALL FlushFileBuffers() __asm__("_FlushFileBuffers@4"); /* import */
int STDCALL FreeEnvironmentStringsA() __asm__("_FreeEnvironmentStringsA@4"); /* import */
int STDCALL FreeEnvironmentStringsW() __asm__("_FreeEnvironmentStringsW@4"); /* import */
int STDCALL GetACP() __asm__("_GetACP@0"); /* import */
int STDCALL GetCPInfo() __asm__("_GetCPInfo@8"); /* import */
int STDCALL GetCommandLineA() __asm__("_GetCommandLineA@0"); /* import */
int STDCALL GetCurrentProcess() __asm__("_GetCurrentProcess@0"); /* import */
int STDCALL GetCurrentThreadId() __asm__("_GetCurrentThreadId@0"); /* import */
int STDCALL GetEnvironmentStrings() __asm__("_GetEnvironmentStrings@0"); /* import */
int STDCALL GetEnvironmentStringsW() __asm__("_GetEnvironmentStringsW@0"); /* import */
int STDCALL GetFileType() __asm__("_GetFileType@4"); /* import */
int STDCALL GetLastError() __asm__("_GetLastError@0"); /* import */
int STDCALL GetLocaleInfoA() __asm__("_GetLocaleInfoA@16"); /* import */
int STDCALL GetLocaleInfoW() __asm__("_GetLocaleInfoW@16"); /* import */
int STDCALL GetModuleFileNameA() __asm__("_GetModuleFileNameA@12"); /* import */
int STDCALL GetModuleHandleA() __asm__("_GetModuleHandleA@4"); /* import */
int STDCALL GetOEMCP() __asm__("_GetOEMCP@0"); /* import */
int STDCALL GetProcAddress() __asm__("_GetProcAddress@8"); /* import */
int STDCALL GetStartupInfoA() __asm__("_GetStartupInfoA@4"); /* import */
int STDCALL GetStdHandle() __asm__("_GetStdHandle@4"); /* import */
int STDCALL GetStringTypeA() __asm__("_GetStringTypeA@20"); /* import */
int STDCALL GetStringTypeW() __asm__("_GetStringTypeW@16"); /* import */
int STDCALL GetVersion() __asm__("_GetVersion@0"); /* import */
int STDCALL HeapAlloc() __asm__("_HeapAlloc@12"); /* import */
int STDCALL HeapCreate() __asm__("_HeapCreate@12"); /* import */
int STDCALL HeapDestroy() __asm__("_HeapDestroy@4"); /* import */
int STDCALL HeapFree() __asm__("_HeapFree@12"); /* import */
int ImProcessStreams(); /* thunk */
int ImTerminate(); /* thunk */
int STDCALL InitializeCriticalSection() __asm__("_InitializeCriticalSection@4"); /* import */
int STDCALL InterlockedDecrement() __asm__("_InterlockedDecrement@4"); /* import */
int STDCALL InterlockedIncrement() __asm__("_InterlockedIncrement@4"); /* import */
int STDCALL LCMapStringA() __asm__("_LCMapStringA@24"); /* import */
int STDCALL LCMapStringW() __asm__("_LCMapStringW@24"); /* import */
int STDCALL LeaveCriticalSection() __asm__("_LeaveCriticalSection@4"); /* import */
int STDCALL LoadLibraryA() __asm__("_LoadLibraryA@4"); /* import */
int STDCALL MultiByteToWideChar() __asm__("_MultiByteToWideChar@24"); /* import */
int STDCALL ReadFile() __asm__("_ReadFile@20"); /* import */
int STDCALL SetEndOfFile() __asm__("_SetEndOfFile@4"); /* import */
int STDCALL SetFilePointer() __asm__("_SetFilePointer@16"); /* import */
int STDCALL SetHandleCount() __asm__("_SetHandleCount@4"); /* import */
int STDCALL SetLastError() __asm__("_SetLastError@4"); /* import */
int STDCALL SetStdHandle() __asm__("_SetStdHandle@8"); /* import */
int STDCALL TerminateProcess() __asm__("_TerminateProcess@8"); /* import */
int STDCALL TlsAlloc() __asm__("_TlsAlloc@0"); /* import */
int STDCALL TlsFree() __asm__("_TlsFree@4"); /* import */
int STDCALL TlsGetValue() __asm__("_TlsGetValue@4"); /* import */
int STDCALL TlsSetValue() __asm__("_TlsSetValue@8"); /* import */
int STDCALL VirtualAlloc() __asm__("_VirtualAlloc@16"); /* import */
int STDCALL VirtualFree() __asm__("_VirtualFree@12"); /* import */
int STDCALL WideCharToMultiByte() __asm__("_WideCharToMultiByte@32"); /* import */
int STDCALL WriteFile() __asm__("_WriteFile@20"); /* import */
int STDCALL hmiFXFree() __asm__("_hmiFXFree"); /* import */
int STDCALL hmiFXInitSystem() __asm__("_hmiFXInitSystem"); /* import */
int STDCALL hmiFXMalloc() __asm__("_hmiFXMalloc"); /* import */
int STDCALL hmiFXPresetFreeLibrary() __asm__("_hmiFXPresetFreeLibrary"); /* import */
int STDCALL hmiFXPresetLoadLibrary() __asm__("_hmiFXPresetLoadLibrary"); /* import */
int STDCALL hmiFXPresetLock() __asm__("_hmiFXPresetLock"); /* import */
int STDCALL hmiFXPresetProcess() __asm__("_hmiFXPresetProcess"); /* import */
int STDCALL hmiFXPresetRelease() __asm__("_hmiFXPresetRelease"); /* import */
int STDCALL hmiFXUnInitSystem() __asm__("_hmiFXUnInitSystem"); /* import */
int STDCALL timeBeginPeriod() __asm__("_timeBeginPeriod@4"); /* import */
int STDCALL timeEndPeriod() __asm__("_timeEndPeriod@4"); /* import */
int STDCALL timeGetDevCaps() __asm__("_timeGetDevCaps@8"); /* import */
int STDCALL timeGetTime() __asm__("_timeGetTime@0"); /* import */
int STDCALL timeKillEvent() __asm__("_timeKillEvent@4"); /* import */
int STDCALL timeSetEvent() __asm__("_timeSetEvent@20"); /* import */
