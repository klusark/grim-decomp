/* IMUSE.DLL: prototypes of every decompiled function, by module */
#pragma once
#include "ghidra_types.h"

/* ===== imuse.c ===== */
void __cdecl AudioLib_DetectRawFormat (ushort *param_1,uint param_2,undefined4 *param_3,undefined4 *param_4,undefined4 *param_5); /* 0x10001000 */
uint * __cdecl AudioLib_ParseWaveFileHeader (uint *param_1,int *param_2,uint *param_3,uint *param_4,uint *param_5,int *param_6, uint *param_7); /* 0x100013c0 */
int __cdecl AudioLib_CreateWaveFileHeader (undefined4 *param_1,int param_2,uint param_3,uint param_4,uint param_5,uint param_6); /* 0x100017e0 */
void __cdecl AudioLib_ResetCompressor(undefined1 *param_1); /* 0x10001ba0 */
void __cdecl AudioLib_UncompressBlock(byte *param_1,undefined2 *param_2,byte *param_3,uint param_4); /* 0x10001bc0 */
void __cdecl Im_ConvertBlockImpl(short *param_1,undefined2 *param_2,byte *param_3,int param_4,uint param_5, int param_6); /* 0x10001c30 */
undefined4 DpInitialize(void); /* 0x10001f10 */
undefined4 __cdecl DpSwitchStream(int param_1,undefined4 param_2,uint param_3,uint param_4,uint param_5); /* 0x10002260 */
void __cdecl DpProcessTrack(int *param_1,uint param_2,uint param_3); /* 0x10002570 */
int __cdecl GoToNextRegion(int *param_1); /* 0x10002a60 */
int __cdecl Im_DispatchFetchNext(int *param_1); /* 0x10002d30 */
undefined4 __cdecl DwInitialize(undefined4 param_1,undefined4 *param_2); /* 0x100036b0 */
int __cdecl DwQuery(int **buf_out,uint *count_out,int *rate_out); /* 0x10003730 */
undefined4 DwTerminate(void); /* 0x100038d0 */
void __cdecl Im_DSoundCreateBuffer(int param_1); /* 0x10003930 */
undefined4 FdInitialize(void); /* 0x10003ac0 */
undefined4 __cdecl FdSave(undefined4 *param_1,uint param_2); /* 0x10003ae0 */
undefined4 __cdecl FdRestore(undefined4 *param_1); /* 0x10003b10 */
undefined4 __cdecl FdFadeParam(int param_1,int param_2,uint param_3,int param_4); /* 0x10003b40 */
void __cdecl FdStopFade(int param_1,int param_2); /* 0x10003c70 */
uint FdIntHandler(void); /* 0x10003cb0 */
undefined4 __cdecl Im_ApplyFXPreset(undefined2 *param_1,uint param_2,undefined2 *param_3,int *param_4,int *param_5, int param_6); /* 0x10004820 */
void __cdecl FUN_10004970(void); /* 0x10004970 */
undefined4 GrInitialize(void); /* 0x100049b0 */
undefined4 __cdecl GrSetGroupVol(uint param_1,uint param_2); /* 0x100049e0 */
undefined4 __cdecl GrGetGroupEffVol(uint param_1); /* 0x10004a80 */
void ImWaveHalt(void); /* 0x10004f50 */
int ImWaveProceed(void); /* 0x10004f60 */
uint __cdecl ImSoundCall(uint cmd,int a2,int a3,int a4,int a5,int a6,int a7,int a8,int a9,int a10,int a11); /* 0x10004f70 */
undefined4 __cdecl MxInitialize(undefined4 *param_1); /* 0x10005360 */
undefined4 MxTerminate(void); /* 0x10005490 */
undefined4 MxBeginMix(void); /* 0x100054c0 */
void __cdecl Mixer_MxMix(short *param_1,int param_2,int param_3,int param_4,int param_5,uint param_6,uint param_7 ,int param_8,int param_9); /* 0x100054f0 */
undefined4 __cdecl MxEndMix(int *param_1,int param_2); /* 0x10005610 */
void __cdecl Im_MixLoopA(short *param_1,int param_2,uint param_3,uint param_4,int param_5,int param_6); /* 0x100057a0 */
void __cdecl Im_MixLoopB(short *param_1,int param_2,uint param_3,uint param_4,int param_5); /* 0x100059a0 */
void __cdecl Im_MixLoopC(undefined2 *param_1,int param_2,uint param_3,int param_4,int param_5,int param_6); /* 0x10005b80 */
void __cdecl Im_MixLoopD(undefined2 *param_1,int param_2,uint param_3,uint param_4,int param_5); /* 0x10005db0 */
undefined4 __cdecl ScriptCall(int cmd,...); /* 0x10006070 */
undefined4 __cdecl FUN_10006360(int param_1,uint param_2,uint param_3,uint param_4,uint param_5,undefined4 param_6, undefined4 param_7,undefined4 param_8); /* 0x10006360 */
undefined4 FUN_100063d0(void); /* 0x100063d0 */
int __cdecl FUN_10006400(undefined4 *param_1,int param_2); /* 0x10006400 */
int __cdecl FUN_10006470(undefined4 *param_1); /* 0x10006470 */
undefined4 FUN_100064d0(void); /* 0x100064d0 */
int __cdecl FUN_10006560(int param_1); /* 0x10006560 */
int __cdecl Script_SetSequence(int param_1); /* 0x10006620 */
undefined4 FUN_100067a0(void); /* 0x100067a0 */
undefined4 __cdecl FUN_100067b0(uint param_1,char *param_2); /* 0x100067b0 */
void __cdecl Script_Trans(char *param_1,uint param_2,int param_3,uint param_4,int param_5,uint param_6, uint param_7,uint param_8); /* 0x100068b0 */
void __cdecl Script_Callback(char *marker); /* 0x100070e0 */
void FUN_10007110(void); /* 0x10007110 */
undefined4 __cdecl LoadLip(undefined4 param_1,char *param_2); /* 0x100089b0 */
void __cdecl Im_SoundsFreeSlot(int param_1); /* 0x10008b60 */
int __cdecl iMUSE_GetPhoneme(int param_1,int param_2); /* 0x10008bb0 */
int __cdecl FUN_10008c40(int param_1,int param_2); /* 0x10008c40 */
int __cdecl FUN_10008ce0(void); /* 0x10008ce0 */
undefined4 __stdcall timer_callback(int a1,int a2,int a3,int a4,int a5); /* 0x10008e00 */
void __cdecl FUN_10008e30(void); /* 0x10008e30 */
void __cdecl FUN_10008e60(void); /* 0x10008e60 */
void __cdecl Im_SoundsPrepare(uint param_1); /* 0x100093d0 */
uint __cdecl FUN_10009530(int param_1); /* 0x10009530 */
uint __cdecl FUN_10009560(int param_1); /* 0x10009560 */
uint * __cdecl grimSound_LipSyncLoad(uint *param_1); /* 0x100095d0 */
undefined4 __cdecl grimSound_LipSyncFree(int param_1); /* 0x100096b0 */
void __cdecl FUN_10009700(char *fmt,...); /* 0x10009700 */
int * __cdecl iRes_FOPEN(uint *param_1,char *param_2); /* 0x10009710 */
undefined4 __cdecl iRes_FCLOSE(undefined4 *param_1); /* 0x10009b20 */
uint __cdecl iRes_FREAD(undefined4 *param_1,undefined4 *param_2,uint param_3); /* 0x10009b90 */
void __cdecl iMUSE_DeclareBufferSizes (uint param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6, uint param_7,uint param_8,uint param_9,uint param_10,uint param_11,uint param_12); /* 0x1000a070 */
uint __cdecl iMUSE_GetMemoryFootprint(void); /* 0x1000a0f0 */
uint __cdecl iMUSE_GetSoundCacheSize(void); /* 0x1000a100 */
uint __cdecl iMUSE_SetHook(uint *param_1,uint param_2); /* 0x1000a110 */
uint __cdecl iMUSE_GetHook(uint *param_1); /* 0x1000a140 */
int __cdecl iMUSE_SetVoiceEffect(uint *param_1); /* 0x1000a160 */
undefined4 StInitialize(void); /* 0x1000a1e0 */
undefined4 StProcessStreams(void); /* 0x1000a300 */
int __cdecl StGetValidSize(int param_1); /* 0x1000a580 */
undefined4 __cdecl StQueryStream(int param_1,undefined4 *param_2,undefined4 *param_3,int *param_4,undefined4 *param_5); /* 0x1000a5e0 */
undefined4 __cdecl StFeedStream(int param_1,undefined4 *param_2,uint param_3,undefined4 param_4); /* 0x1000a620 */
undefined4 __cdecl Stream_LoadData(uint *param_1); /* 0x1000a6d0 */
undefined4 TrInitialize(void); /* 0x1000a7e0 */
int TrTerminate(void); /* 0x1000a8a0 */
void TrPause(void); /* 0x1000a8d0 */
void TrResume(void); /* 0x1000a8f0 */
int __cdecl TrSave(undefined4 *param_1,uint param_2); /* 0x1000a910 */
int __cdecl TrRestore(undefined4 *param_1); /* 0x1000a970 */
undefined4 TrUpdateVols(void); /* 0x1000aa00 */
void TrIntHandler(void); /* 0x1000aa40 */
undefined4 __cdecl TrStartSound(int param_1,int param_2,uint param_3); /* 0x1000ab00 */
undefined4 __cdecl TrStopSound(int param_1); /* 0x1000abb0 */
undefined4 TrStopAllSounds(void); /* 0x1000ac00 */
uint __cdecl TrGetNextSound(uint param_1); /* 0x1000ac20 */
undefined4 __cdecl TrQueryStream(int param_1,undefined4 *param_2,undefined4 *param_3,int *param_4,undefined4 *param_5); /* 0x1000ac60 */
undefined4 __cdecl TrFeedStream(int param_1,undefined4 *param_2,uint param_3,undefined4 param_4); /* 0x1000ace0 */
void __cdecl TrStopTrack(int *param_1); /* 0x1000ad50 */
undefined4 __cdecl TrSetParam(int param_1,int param_2,uint param_3); /* 0x1000ada0 */
uint __cdecl TrGetParam(int param_1,int param_2); /* 0x1000af50 */
undefined4 __cdecl TrSetHook(int param_1,uint param_2); /* 0x1000b0a0 */
undefined4 __cdecl TrGetHook(int param_1); /* 0x1000b0e0 */
int * __cdecl Im_AllocTrackOrSteal(int param_1); /* 0x1000b110 */
undefined4 TgInitialize(void); /* 0x1000b170 */
undefined4 __cdecl TgSave(undefined4 *param_1,int param_2); /* 0x1000b1a0 */
undefined4 __cdecl TgRestore(undefined4 *param_1); /* 0x1000b1e0 */
undefined4 __cdecl TgSetTrigger(int sound,char *marker,int cmd,int p0,int p1,int p2,int p3,int p4,int p5,int p6,int p7, int p8,int p9); /* 0x1000b220 */
int __cdecl TgCheckTrigger(int param_1,byte *param_2,int param_3); /* 0x1000b2e0 */
undefined4 __cdecl TgClearTrigger(int param_1,byte *param_2,int param_3); /* 0x1000b380 */
undefined4 * __cdecl TgProcessMarker(int param_1,char *param_2); /* 0x1000b430 */
undefined4 __cdecl TgDeferCommand(int time,int cmd,int p0,int p1,int p2,int p3,int p4,int p5,int p6,int p7,int p8, int p9); /* 0x1000b570 */
void TgIntHandler(void); /* 0x1000b5e0 */
int __cdecl TgGetPendCount(int param_1); /* 0x1000b630 */
void __cdecl Im_RunTriggerCommand(undefined4 *param_1,undefined4 param_2); /* 0x1000b6a0 */
void __cdecl Im_RunDeferredCommand(int param_1); /* 0x1000b710 */
char * __cdecl Im_StrChr(char *param_1,char param_2); /* 0x1000bd50 */
uint * __cdecl Im_MemCopy(uint *param_1,uint *param_2,uint param_3); /* 0x1000bd80 */
uint __cdecl Im_StrCmpNoCase(byte *param_1,byte *param_2); /* 0x1000be80 */

/* ===== imuse_dispatch.c ===== */
undefined4 DpTerminate(void); /* 0x10001fd0 */
undefined4 * __cdecl DpGetDp(int param_1); /* 0x10001ff0 */
undefined4 __cdecl DpSave(undefined4 *param_1,uint param_2); /* 0x10002010 */
undefined4 __cdecl DpBeginRestore(undefined4 *param_1); /* 0x10002040 */
undefined4 DpConcludeRestore(void); /* 0x100020c0 */
undefined4 __cdecl DpStartSound(int param_1,uint param_2); /* 0x10002170 */
undefined4 __cdecl DpStopTrack(int param_1); /* 0x10002200 */
void DpPredictStreams(void); /* 0x10002a00 */
int __cdecl ConvertMap(undefined4 *param_1,undefined4 *param_2); /* 0x10002fe0 */
uint __cdecl iMUSE_Dispatch__30d0(int param_1,int param_2,int param_3); /* 0x100030d0 */
void __cdecl PredictStream(int *param_1); /* 0x10003130 */
int * __cdecl iMUSE_Dispatch__31d0(int *param_1,int param_2,int *param_3); /* 0x100031d0 */
void __cdecl PrepareToJump(int *param_1,undefined4 *param_2,int param_3,int param_4); /* 0x10003250 */
void __cdecl iMUSE_Dispatch__3430(int *param_1,int param_2); /* 0x10003430 */
int __cdecl iMUSE_Dispatch__34b0(int *param_1); /* 0x100034b0 */
int __cdecl iMUSE_Dispatch__3510(int *param_1,int param_2); /* 0x10003510 */
undefined4 * iMUSE_Dispatch__3570(void); /* 0x10003570 */
int __cdecl iMUSE_Dispatch__35a0(uint *param_1); /* 0x100035a0 */
void __cdecl iMUSE_Dispatch__3640(int param_1); /* 0x10003640 */

/* ===== imuse_dsound.c ===== */
int iMUSE_dsound__3a80(void); /* 0x10003a80 */
undefined4 __cdecl FmGetSoundAddr(uint param_1); /* 0x10004540 */
undefined4 __cdecl FmGetMapAddr(uint param_1); /* 0x10004570 */
undefined4 __cdecl FmValidateSoundId(uint param_1); /* 0x100045a0 */
undefined4 __cdecl FmSeek(uint param_1,undefined4 param_2,undefined4 param_3); /* 0x100045c0 */
undefined4 __cdecl FmRead(uint param_1,undefined4 param_2,undefined4 param_3); /* 0x10004600 */
undefined4 __cdecl FmGetBufInfo(int param_1); /* 0x10004640 */
uint __cdecl FUN_10004660(uint param_1); /* 0x10004660 */
int __cdecl FUN_10004750(uint param_1); /* 0x10004750 */

/* ===== imuse_api.c ===== */
uint __cdecl ImInitFilelist(uint param_1,uint param_2,uint param_3,uint param_4); /* 0x10003d70 */
int __cdecl ImSaveFilelist(int *param_1,uint param_2); /* 0x10003dc0 */
int __cdecl ImRestoreFilelist(int *param_1); /* 0x10003e50 */
int __cdecl ImLoadSound(char *param_1,uint param_2); /* 0x10003f90 */
undefined4 __cdecl ImUnloadSound(int param_1); /* 0x100040b0 */
undefined4 __cdecl ImUnloadAll(void); /* 0x10004100 */
int __cdecl ImOpenSound(char *param_1,uint param_2); /* 0x10004140 */
undefined4 __cdecl ImCloseSound(int param_1); /* 0x10004260 */
undefined4 __cdecl ImCloseAll(void); /* 0x100042b0 */
int __cdecl ImFindSound(char *param_1); /* 0x100042f0 */
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
uint __cdecl ImStartRecording(uint param_1,int param_2); /* 0x10005300 */
uint __cdecl ImStopRecording(void); /* 0x10005350 */
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
undefined4 __cdecl ihost_close_sound(int param_1); /* 0x10007250 */
int * __cdecl SoundsRegisterVoice(char *param_1); /* 0x100072b0 */
undefined4 __cdecl SoundsCloseVoiceFile(void); /* 0x100073c0 */
int * __cdecl SoundsReOpenVoiceFile(void); /* 0x100073f0 */
undefined4 __cdecl SoundsLoadStartSound(uint *param_1,int param_2,uint param_3); /* 0x10007410 */
undefined4 __cdecl SoundsLoadProcessStartSound(uint *param_1,int param_2,uint param_3); /* 0x10007470 */
undefined4 __cdecl SoundsStopSound(uint *param_1); /* 0x10007500 */
uint __cdecl SoundsGetParam(uint *param_1,int param_2); /* 0x10007520 */
undefined4 __cdecl SoundsSetParam(uint *param_1,int param_2,uint param_3); /* 0x10007550 */
uint __cdecl SoundsFadeParam(uint *param_1,int param_2,uint param_3,int param_4); /* 0x10007580 */
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
uint __cdecl SoundsInitialize(uint param_1,undefined4 *param_2); /* 0x100078d0 */
uint __cdecl sounds_startup(void); /* 0x10007920 */
void __cdecl FUN_10007a20(void); /* 0x10007a20 */
void __cdecl ihost_get_sound_addr(uint param_1); /* 0x10007a60 */
void __cdecl ihost_get_map_addr(uint param_1); /* 0x10007a70 */
int __cdecl ihost_get_buffer_info(int param_1); /* 0x10007a80 */
int __cdecl ihost_open_sound(uint *param_1,int param_2); /* 0x10007a90 */
int __cdecl ihost_fseek(int param_1,int param_2,int param_3); /* 0x10007bc0 */
undefined4 * __cdecl ihost_read(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3); /* 0x10007ca0 */
void __cdecl sounds_shutdown(void); /* 0x10008140 */
void __cdecl FUN_100081f0(void); /* 0x100081f0 */
uint __cdecl sounds_save(code *param_1); /* 0x10008250 */
undefined4 sounds_restore(code *param_1,uint param_2); /* 0x10008580 */
uint __cdecl sounds_pause(void); /* 0x10008860 */
uint __cdecl sounds_resume(void); /* 0x100088a0 */
int __cdecl CacheGetSoundId(uint *param_1); /* 0x10008ec0 */
int CachePurgeOldestStoppedSound(void); /* 0x100092f0 */
int __cdecl ImFile_Read(int *param_1,int param_2,int param_3); /* 0x1000b940 */
int __cdecl ImFile_ReadImpl(int *param_1,int param_2,int param_3); /* 0x1000b980 */
undefined4 __cdecl FUN_1000ba20(undefined4 param_1,char *param_2,undefined4 param_3); /* 0x1000ba20 */
int __cdecl FUN_1000ba60(undefined4 param_1,undefined4 param_2); /* 0x1000ba60 */
void __cdecl FUN_1000ba80(void); /* 0x1000ba80 */
void __cdecl FUN_1000baa0(void); /* 0x1000baa0 */
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
void __cdecl FUN_1000d130(void); /* 0x1000d130 */
int __stdcall FUN_1000d1f0(int a1,int a2,int a3,int a4); /* 0x1000d1f0 */

/* ===== soundstartvoicestream.c ===== */
int __cdecl SoundStartVoiceStream(char *name,uint volume,uint pan); /* 0x100088d0 */

/* ===== soundstopvoicestream.c ===== */
undefined4 __cdecl SoundStopVoiceStream(void); /* 0x10008970 */

/* ===== soundgetvoicetime.c ===== */
uint SoundGetVoiceTime(void); /* 0x10008990 */

/* ===== imuse_sounds.c ===== */
undefined4 __cdecl iRes_FTELL(undefined *param_1); /* 0x10009e10 */
undefined4 __cdecl iRes_FSEEK(undefined *param_1,int param_2,int param_3); /* 0x10009e40 */
int __cdecl iMUSE_sounds__9eb0(int param_1,uint param_2); /* 0x10009eb0 */
int __cdecl FUN_10009ef0(uint param_1,uint *param_2); /* 0x10009ef0 */
uint __cdecl iMUSE_Malloc(uint param_1); /* 0x10009f10 */
void __cdecl FUN_10009f40(int param_1); /* 0x10009f40 */
void __cdecl iMUSE_Free(uint param_1); /* 0x1000a010 */
void __cdecl FUN_1000a030(int param_1); /* 0x1000a030 */

/* ===== imuse_stream.c ===== */
uint * __cdecl StStartStream(uint param_1,uint param_2,uint param_3); /* 0x1000a210 */
undefined4 __cdecl StStopStream(undefined4 *param_1); /* 0x1000a2d0 */
int __cdecl StReadData(int param_1,uint param_2); /* 0x1000a420 */
int __cdecl StViewData(int param_1,int param_2,uint param_3); /* 0x1000a490 */
undefined4 __cdecl StEraseFromFront(int param_1,uint param_2); /* 0x1000a500 */
undefined4 __cdecl StEraseFromMid(int param_1,uint param_2); /* 0x1000a540 */
undefined4 __cdecl StSpliceStream(undefined4 *param_1,undefined4 param_2,undefined4 param_3); /* 0x1000a5a0 */
undefined4 __cdecl UtAddToList(int *param_1,int *param_2); /* 0x1000b760 */
undefined4 __cdecl UtRemoveFromList(int *param_1,int *param_2); /* 0x1000b7a0 */
undefined4 __cdecl UtReadLongHilo(undefined1 *param_1); /* 0x1000b810 */
undefined4 __cdecl UtCheckHook(int *param_1,int param_2); /* 0x1000b840 */
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
int __cdecl FUN_1000d4e0(int *param_1); /* 0x1000d4e0 */
void __cdecl FUN_1000d590(void); /* 0x1000d590 */
int __cdecl FUN_1000d5a0(int param_1); /* 0x1000d5a0 */
undefined4 * __cdecl FUN_1000d810(undefined4 param_1,char *param_2,undefined4 param_3,undefined4 *param_4); /* 0x1000d810 */
undefined4 * FUN_1000d9e0(void); /* 0x1000d9e0 */
void __cdecl FUN_1000dac0(void); /* 0x1000dac0 */
uint __cdecl FUN_1000db30(void); /* 0x1000db30 */
void __cdecl FUN_1000db60(char *param_1); /* 0x1000db60 */
void __cdecl FUN_1000dbc0(char *param_1); /* 0x1000dbc0 */
uint __cdecl FUN_1000dc30(double *param_1); /* 0x1000dc30 */
void __cdecl FUN_1000dc50(int param_1,undefined4 *param_2,uint param_3); /* 0x1000dc50 */
int __cdecl FUN_1000dcb0(undefined4 *param_1,int param_2,int param_3,uint param_4); /* 0x1000dcb0 */
undefined1 * __cdecl FUN_1000dd30(undefined1 *param_1,int param_2,int param_3,int *param_4,char param_5); /* 0x1000dd30 */
int __cdecl FUN_1000de30(undefined4 *param_1,int param_2,int param_3); /* 0x1000de30 */
undefined1 * __cdecl FUN_1000dea0(undefined1 *param_1,uint param_2,int *param_3,char param_4); /* 0x1000dea0 */
void __cdecl FUN_1000df60(undefined4 *param_1,int param_2,int param_3,uint param_4); /* 0x1000df60 */
void __cdecl FUN_1000e020(uint param_1,uint param_2,int param_3,uint param_4,uint param_5); /* 0x1000e020 */
void __cdecl FUN_1000e090(char *param_1,int param_2); /* 0x1000e090 */
uint __cdecl FUN_1000e500(void); /* 0x1000e500 */
uint __cdecl FUN_1000e510(uint param_1); /* 0x1000e510 */
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
uint __cdecl FUN_10010490(uint param_1); /* 0x10010490 */
uint __cdecl FUN_10010530(undefined4 param_1,uint param_2,undefined4 param_3,byte param_4); /* 0x10010530 */
uint __cdecl FUN_100108d0(uint param_1,uint param_2); /* 0x100108d0 */
void __cdecl FUN_10010910(uint param_1,uint param_2); /* 0x10010910 */
uint __cdecl FUN_10010930(uint param_1); /* 0x10010930 */
int FUN_100109d0(void); /* 0x100109d0 */
uint __cdecl FUN_10010a60(int param_1,int param_2); /* 0x10010a60 */
int FUN_10010ad0(void); /* 0x10010ad0 */
int __cdecl FUN_10010b40(int param_1,int param_2); /* 0x10010b40 */
void __cdecl FUN_10010be0(int param_1,undefined4 *param_2); /* 0x10010be0 */
void __cdecl FUN_10010c00(undefined4 *param_1); /* 0x10010c00 */
uint __cdecl FUN_10010c10(int *param_1); /* 0x10010c10 */
void __cdecl FUN_10010c30(uint *param_1,int param_2); /* 0x10010c30 */
uint __cdecl FUN_10010cf0(ushort *param_1,uint *param_2,int *param_3); /* 0x10010cf0 */
void __cdecl FUN_10010ec0(uint param_1,uint param_2); /* 0x10010ec0 */
void __cdecl FUN_10010ee0(uint param_1,uint param_2); /* 0x10010ee0 */
void __cdecl FUN_10010f00(uint param_1,uint param_2); /* 0x10010f00 */
void __cdecl FUN_10010f40(uint param_1,uint param_2); /* 0x10010f40 */
void __cdecl FUN_10010f80(char *param_1,int param_2,int param_3); /* 0x10010f80 */
int * __cdecl FUN_10011020(uint param_1,uint param_2,int *param_3,char *param_4); /* 0x10011020 */
void __cdecl FUN_100110b0(uint *param_1,uint *param_2); /* 0x100110b0 */
undefined4 * FUN_10011170(undefined4 *param_1,undefined4 *param_2,uint param_3); /* 0x10011170 */
void __cdecl FUN_100114b0(void); /* 0x100114b0 */
uint __cdecl FUN_10011be0(void); /* 0x10011be0 */
uint __cdecl FUN_10011c90(int param_1); /* 0x10011c90 */
void __cdecl FUN_10012010(undefined4 *param_1); /* 0x10012010 */
uint __cdecl FUN_10012250(char *param_1,int param_2); /* 0x10012250 */
uint __cdecl FUN_10012350(void); /* 0x10012350 */
uint __cdecl FUN_10012550(void); /* 0x10012550 */
uint __cdecl FUN_10012640(int param_1); /* 0x10012640 */
void __cdecl FUN_10012790(char *param_1); /* 0x10012790 */
void __cdecl FUN_100127d0(int param_1); /* 0x100127d0 */
uint __cdecl FUN_10012840(void); /* 0x10012840 */
int __cdecl FUN_10012bc0(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6); /* 0x10012bc0 */
int FUN_10012f40(void); /* 0x10012f40 */
int __cdecl FUN_10013090(uint param_1,char *param_2,int param_3); /* 0x10013090 */
uint __cdecl FUN_100132c0(uint param_1,uint param_2,uint *param_3); /* 0x100132c0 */
void __cdecl FUN_100132f0(undefined4 *param_1,undefined4 *param_2); /* 0x100132f0 */
void __cdecl FUN_10013360(uint *param_1); /* 0x10013360 */
void __cdecl FUN_10013390(uint *param_1); /* 0x10013390 */
void __cdecl FUN_100133c0(char *param_1,int param_2,uint *param_3); /* 0x100133c0 */
uint __cdecl FUN_100134c0(ushort *param_1,int *param_2,byte *param_3,uint param_4,int param_5,int param_6, int param_7); /* 0x100134c0 */
uint __cdecl FUN_10013c50(int param_1,uint param_2,uint param_3,int param_4,byte param_5,short *param_6); /* 0x10013c50 */
uint __cdecl FUN_10013fe0(int param_1,uint param_2,uint param_3,char *param_4); /* 0x10013fe0 */
int __cdecl FUN_100142a0(uint param_1,int param_2); /* 0x100142a0 */
void FUN_10014310(void); /* 0x10014310 */
void __cdecl FUN_10014340(int *param_1,int *param_2); /* 0x10014340 */
void __cdecl FUN_10014600(undefined2 *param_1,uint param_2,int param_3); /* 0x10014600 */
int __cdecl FUN_10014690(uint param_1,uint param_2,uint param_3,uint param_4); /* 0x10014690 */
int __cdecl FUN_100147c0(uint param_1,uint param_2,uint param_3,uint param_4); /* 0x100147c0 */

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
int hmiFXFree(); /* import */
int STDCALL hmiFXInitSystem() __asm__("_hmiFXInitSystem"); /* import */
int hmiFXMalloc(); /* import */
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
