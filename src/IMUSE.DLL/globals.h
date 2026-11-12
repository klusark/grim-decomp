/* IMUSE.DLL: every global / string symbol referenced by the decompiled code.
 * Named globals carry their Ghidra type. For DAT_/PTR_/s_ symbols Ghidra exported
 * no type; the type below is inferred from how the code uses the symbol
 * (see infer_global_types in tools/build_src.py) - fix it in Ghidra, not here. */
#pragma once
#include "ghidra_types.h"

/* ---- named globals (type from Ghidra) ---- */
extern ImMusicEntry g_aImStateTable[181]; /* 0x100172e8 */
extern ImMusicEntry g_aImSeqTable[41]; /* 0x1001ae50 */
extern ImNameAlias g_aImNameAlias[171]; /* 0x1001bbc8 */

/* ---- unnamed data (type inferred from use) ---- */
extern undefined2 DAT_10015228; /* used by 1 fn(s), first 0x10001c30 */
extern undefined DAT_100152da; /* used by 1 fn(s), first 0x10001c30 */
extern undefined DAT_100152e0; /* used by 1 fn(s), first 0x10001c30 */
extern undefined DAT_10015398; /* used by 1 fn(s), first 0x1000c670 */
extern undefined UNK_100153b8; /* used by 1 fn(s), first 0x1000c670 */
extern undefined UNK_10015454; /* used by 1 fn(s), first 0x1000db30 */
extern undefined4 DAT_10015774; /* used by 1 fn(s), first 0x1000fa70 */
extern undefined4 DAT_10015790; /* used by 1 fn(s), first 0x1000fa70 */
extern undefined DAT_10017000; /* used by 1 fn(s), first 0x1000e9e0 */
extern undefined DAT_10017014; /* used by 1 fn(s), first 0x1000ea40 */
extern undefined DAT_1001701c; /* used by 1 fn(s), first 0x1000ea40 */
extern undefined DAT_10017020; /* used by 1 fn(s), first 0x1000ea40 */
extern undefined DAT_10017024; /* used by 1 fn(s), first 0x1000ea40 */
extern undefined DAT_10017030; /* used by 1 fn(s), first 0x10001c30 */
extern undefined4 DAT_10017050; /* used by 2 fn(s), first 0x100013c0 */
extern undefined4 DAT_10017058; /* used by 2 fn(s), first 0x100013c0 */
extern undefined4 DAT_1001705c; /* used by 1 fn(s), first 0x100017e0 */
extern undefined DAT_10017064; /* used by 1 fn(s), first 0x100013c0 */
extern undefined4 DAT_1001706c; /* used by 2 fn(s), first 0x100013c0 */
extern undefined4 DAT_10017074; /* used by 5 fn(s), first 0x100013c0 */
extern undefined4 DAT_1001707c; /* used by 2 fn(s), first 0x100013c0 */
extern undefined DAT_10017084; /* used by 2 fn(s), first 0x100013c0 */
extern undefined4 DAT_10017088; /* used by 1 fn(s), first 0x100017e0 */
extern undefined DAT_10017090; /* used by 2 fn(s), first 0x100013c0 */
extern undefined DAT_10017098; /* used by 2 fn(s), first 0x100013c0 */
extern undefined4 DAT_100170a0; /* used by 1 fn(s), first 0x100017e0 */
extern undefined4 DAT_100170a8; /* used by 1 fn(s), first 0x100017e0 */
extern undefined4 DAT_100170b0; /* used by 1 fn(s), first 0x100017e0 */
extern undefined4 DAT_100170b8; /* used by 2 fn(s), first 0x100017e0 */
extern char s_C__grimsrc_libs_iMUSE_Dispatch_c_100170c0[]; /* used by 1 fn(s), first 0x10001f10 */
extern int * PTR_100170ec; /* used by 1 fn(s), first 0x10003730 */
extern undefined DAT_100170f0; /* used by 1 fn(s), first 0x10003930 */
extern char s_C__grimsrc_libs_iMUSE_dsound_c_10017104[]; /* used by 1 fn(s), first 0x100036b0 */
extern undefined DAT_100171b0; /* used by 7 fn(s), first 0x10003e50 */
extern uint DAT_100172bc; /* used by 1 fn(s), first 0x10005190 */
extern undefined4 g_dwWvSlicingHalted; /* used by 4 fn(s), first 0x10004aa0 */
extern char s_C__grimsrc_libs_iMUSE_Mixer_c_100172c8[]; /* used by 1 fn(s), first 0x10005360 */
extern undefined DAT_100172e8; /* used by 1 fn(s), first 0x10006560 */
extern undefined4 DAT_1001730c; /* used by 1 fn(s), first 0x10006560 */
extern undefined4 g_dwLocalMusic; /* used by 3 fn(s), first 0x10006360 */
extern char s_SCRIPT_ERR__save_buffer_too_smal_1001e6f8[]; /* used by 1 fn(s), first 0x10006400 */
extern char s_ERR__bogus_sequence____1001e720[]; /* used by 1 fn(s), first 0x10006620 */
extern char s_ERR__bogus_attribute____1001e738[]; /* used by 1 fn(s), first 0x100067b0 */
extern char s_Set_attr__lu_to__lu____1001e750[]; /* used by 1 fn(s), first 0x100067b0 */
extern char s_SCRIPT_ERR__bogus_trans_type____1001e768[]; /* used by 1 fn(s), first 0x100068b0 */
extern char s_SCRIPT_ERR__failed_start_stream__1001e788[]; /* used by 1 fn(s), first 0x100068b0 */
extern char s_No_stream_sound____1001e7ac[]; /* used by 1 fn(s), first 0x100068b0 */
extern char s_and_PAN__lu____1001e7c0[]; /* used by 1 fn(s), first 0x100068b0 */
extern char s_fading_VOL__lu____1001e7d0[]; /* used by 1 fn(s), first 0x100068b0 */
extern char s_set_pan__lu____1001e7e4[]; /* used by 1 fn(s), first 0x100068b0 */
extern char s_clear_1001e7f4[]; /* used by 1 fn(s), first 0x100068b0 */
extern char s_exit2_1001e7fc[]; /* used by 1 fn(s), first 0x100068b0 */
extern undefined DAT_1001e804; /* used by 1 fn(s), first 0x100068b0 */
extern char s_vol__lu____1001e80c[]; /* used by 1 fn(s), first 0x100068b0 */
extern char s_FADE__lu____1001e818[]; /* used by 1 fn(s), first 0x100068b0 */
extern char s_HOOK__lu____1001e824[]; /* used by 1 fn(s), first 0x100068b0 */
extern char s_SCRIPT_ERR__Unable_to_open_1001e830[]; /* used by 1 fn(s), first 0x100068b0 */
extern char s_opening_1001e84c[]; /* used by 1 fn(s), first 0x100068b0 */
extern undefined DAT_1001e858; /* used by 1 fn(s), first 0x100068b0 */
extern char s_Trans_null____1001e860[]; /* used by 1 fn(s), first 0x100068b0 */
extern char s_ERR_callback_got_marker______end_1001e870[]; /* used by 1 fn(s), first 0x100070e0 */
extern char s_CALLBACK__1001e898[]; /* used by 1 fn(s), first 0x100070e0 */
extern undefined g_dwTAIL_BYTES; /* used by 2 fn(s), first 0x10007bc0 */
extern undefined g_dwImVoiceBufferSize; /* used by 2 fn(s), first 0x10007920 */
extern undefined g_dwImVoiceGulpSize; /* used by 2 fn(s), first 0x10007920 */
extern undefined g_dwImVoiceCriticalSize; /* used by 2 fn(s), first 0x10007920 */
extern undefined g_dwImMusicBufferSize; /* used by 2 fn(s), first 0x10007920 */
extern undefined g_dwImMusicGulpSize; /* used by 3 fn(s), first 0x100077c0 */
extern undefined g_dwImMusicCriticalSize; /* used by 2 fn(s), first 0x10007920 */
extern undefined4 g_dwImLargeFadeSize; /* used by 4 fn(s), first 0x10001f10 */
extern undefined4 g_dwImLargeFadeCount; /* used by 5 fn(s), first 0x10001f10 */
extern undefined4 g_dwImSmallFadeSize; /* used by 4 fn(s), first 0x10001f10 */
extern undefined4 g_dwImSmallFadeCount; /* used by 5 fn(s), first 0x10001f10 */
extern undefined g_dwImNonPurgeCacheSize; /* used by 2 fn(s), first 0x10007810 */
extern undefined4 g_dwImWaveMixCount; /* used by 3 fn(s), first 0x10005360 */
extern undefined g_dwEffectsHeapSize; /* used by 4 fn(s), first 0x10007920 */
extern undefined g_bMuscriptLocal; /* used by 2 fn(s), first 0x100078a0 */
extern char s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0[]; /* used by 13 fn(s), first 0x10007210 */
extern undefined DAT_1001e900; /* used by 5 fn(s), first 0x100072b0 */
extern undefined4 DAT_1001e904; /* used by 2 fn(s), first 0x100072b0 */
extern undefined DAT_1001e908; /* used by 2 fn(s), first 0x100072b0 */
extern undefined DAT_1001e90c; /* used by 1 fn(s), first 0x10008250 */
extern undefined DAT_1001e994; /* used by 1 fn(s), first 0x100089b0 */
extern undefined DAT_1001e9c0; /* used by 1 fn(s), first 0x10009b90 */
extern undefined DAT_1001e9d0; /* used by 1 fn(s), first 0x1000e9e0 */
extern undefined *PTR_exit_1001e9e0; /* used by 1 fn(s), first 0x1000c400 */
extern undefined DAT_1001e9e8; /* used by 3 fn(s), first 0x1000c470 */
extern undefined DAT_1001e9ec; /* used by 1 fn(s), first 0x1000c470 */
extern undefined DAT_1001ea0c; /* used by 1 fn(s), first 0x1000c470 */
extern undefined DAT_1001ea1c; /* used by 1 fn(s), first 0x1000c470 */
extern undefined DAT_1001ea2c; /* used by 1 fn(s), first 0x1000c470 */
extern undefined *PTR_DAT_1001eab0; /* used by 1 fn(s), first 0x1000d130 */
extern undefined DAT_1001ead0; /* used by 1 fn(s), first 0x1000d210 */
extern undefined DAT_1001eaf0; /* used by 1 fn(s), first 0x1000d210 */
extern undefined4 DAT_1001ed30; /* used by 1 fn(s), first 0x1000d340 */
extern undefined *PTR_FUN_1001ee98; /* used by 3 fn(s), first 0x1000baa0 */
extern undefined *PTR_FUN_1001ee9c; /* used by 2 fn(s), first 0x1000baa0 */
extern undefined *PTR_FUN_1001eea0; /* used by 1 fn(s), first 0x1000baa0 */
extern undefined *PTR_FUN_1001eea4; /* used by 2 fn(s), first 0x1000baa0 */
extern undefined *PTR_FUN_1001eea8; /* used by 1 fn(s), first 0x1000baa0 */
extern undefined *PTR_FUN_1001eeac; /* used by 1 fn(s), first 0x1000baa0 */
extern undefined *PTR_DAT_1001f010; /* used by 9 fn(s), first 0x1000bf50 */
extern undefined DAT_1001f014; /* used by 1 fn(s), first 0x10012840 */
extern undefined DAT_1001f01a; /* used by 1 fn(s), first 0x10012840 */
extern undefined4 DAT_1001f21c; /* used by 8 fn(s), first 0x1000bf50 */
extern undefined DAT_1001f220; /* used by 6 fn(s), first 0x1000db60 */
extern undefined DAT_1001f224; /* used by 1 fn(s), first 0x10012350 */
extern undefined4 DAT_1001f230; /* used by 4 fn(s), first 0x1000eb40 */
extern undefined DAT_1001f238; /* used by 1 fn(s), first 0x1000d210 */
extern undefined4 DAT_1001f360; /* used by 1 fn(s), first 0x1000fa70 */
extern undefined DAT_1001f3f0; /* used by 2 fn(s), first 0x1000fa70 */
extern undefined *PTR_LOOP_1001f420; /* used by 5 fn(s), first 0x1000f9e0 */
extern undefined *PTR_LOOP_1001f424; /* used by 2 fn(s), first 0x100114c0 */
extern undefined4 DAT_1001f430; /* used by 2 fn(s), first 0x100114c0 */
extern undefined *PTR_LOOP_10021440; /* used by 2 fn(s), first 0x10011630 */
extern undefined4 DAT_10021444; /* used by 2 fn(s), first 0x1000fcc0 */
extern undefined DAT_10021bd0; /* used by 2 fn(s), first 0x1000ebd0 */
extern undefined DAT_10021d04; /* used by 1 fn(s), first 0x10011be0 */
extern undefined DAT_10021d10; /* used by 1 fn(s), first 0x10012550 */
extern undefined DAT_10021d14; /* used by 1 fn(s), first 0x10012550 */
extern undefined DAT_10021d18; /* used by 1 fn(s), first 0x10012550 */
extern undefined DAT_10021d40; /* used by 2 fn(s), first 0x10012350 */
extern undefined2 DAT_10022140; /* used by 1 fn(s), first 0x10001c30 */
extern undefined DAT_100221c0; /* used by 1 fn(s), first 0x10001c30 */
extern undefined4 DAT_10024dc0; /* used by 1 fn(s), first 0x10001c30 */
extern int * PTR_10024dc8; /* used by 4 fn(s), first 0x10001f10 */
extern int g_dwLargeFadeBufs; /* used by 3 fn(s), first 0x10001f10 */
extern uint g_dwLargeFadeFlags; /* used by 1 fn(s), first 0x10002260 */
extern int g_dwSmallFadeBufs; /* used by 3 fn(s), first 0x10001f10 */
extern undefined g_dwPredictStream_jumpHook; /* used by 1 fn(s), first 0x10003130 */
extern undefined g_dwDpProcessTrack_critSize; /* used by 1 fn(s), first 0x10002570 */
extern undefined4 g_dwFadeStartedFlag; /* used by 2 fn(s), first 0x10002570 */
extern undefined4 g_dwStreamZones; /* used by 2 fn(s), first 0x10001f10 */
extern undefined4 DAT_10024df0; /* used by 1 fn(s), first 0x10002040 */
extern int * g_pSmallFadeFlags; /* used by 4 fn(s), first 0x10001f10 */
extern undefined4 g_dwDispatches; /* used by 5 fn(s), first 0x10001ff0 */
extern undefined4 DAT_10025abc; /* used by 1 fn(s), first 0x100020c0 */
extern undefined g_dwDpProcessTrack_curLevel; /* used by 1 fn(s), first 0x10002570 */
extern undefined g_dwDpProcessTrack_pauseFlag; /* used by 1 fn(s), first 0x10002570 */
extern undefined4 g_dwGoToNextRegion_fadeSize; /* used by 1 fn(s), first 0x10002a60 */
extern undefined4 g_dwMemAddr; /* used by 2 fn(s), first 0x10001f10 */
extern undefined4 g_dwPrepareToJump_fadeSize; /* used by 1 fn(s), first 0x10003250 */
extern undefined g_dwDpProcessTrack_bufSize; /* used by 1 fn(s), first 0x10002570 */
extern undefined4 DAT_1002d814; /* used by 1 fn(s), first 0x10002a60 */
extern int * DAT_1002d818; /* used by 2 fn(s), first 0x100036b0 */
extern undefined DAT_1002d81c; /* used by 1 fn(s), first 0x10003a80 */
extern undefined4 DAT_1002d820; /* used by 1 fn(s), first 0x10003730 */
extern int DAT_1002d824; /* used by 3 fn(s), first 0x10003730 */
extern undefined4 DAT_1002d828; /* used by 1 fn(s), first 0x10003a80 */
extern uint DAT_1002d82c; /* used by 1 fn(s), first 0x10003730 */
extern int * PTR_1002d830; /* used by 2 fn(s), first 0x100036b0 */
extern int * PTR_1002d834; /* used by 2 fn(s), first 0x100036b0 */
extern int * PTR_1002d838; /* used by 1 fn(s), first 0x100038d0 */
extern int * PTR_1002d83c; /* used by 4 fn(s), first 0x10003730 */
extern int * DAT_1002d840; /* used by 2 fn(s), first 0x10003730 */
extern undefined4 DAT_1002d844; /* used by 3 fn(s), first 0x100036b0 */
extern undefined4 DAT_1002d848; /* used by 1 fn(s), first 0x10003730 */
extern undefined4 g_dwCurrentWriteIndex; /* used by 1 fn(s), first 0x10003730 */
extern int * DAT_1002d850; /* used by 1 fn(s), first 0x10003730 */
extern undefined4 * DAT_1002d854; /* used by 1 fn(s), first 0x10003730 */
extern uint g_dwFadesOn; /* used by 4 fn(s), first 0x10003ac0 */
extern undefined4 g_dwFades; /* used by 5 fn(s), first 0x10003ac0 */
extern undefined4 DAT_1002d880; /* used by 1 fn(s), first 0x10003cb0 */
extern code *g_dwOpenSoundFunc; /* used by 4 fn(s), first 0x10003d70 */
extern code *g_dwCloseSoundFunc; /* used by 5 fn(s), first 0x10003d70 */
extern code *g_dwLoadSoundFunc; /* used by 4 fn(s), first 0x10003d70 */
extern code *g_dwUnloadSoundFunc; /* used by 5 fn(s), first 0x10003d70 */
extern int * g_pLoadedList; /* used by 7 fn(s), first 0x10003dc0 */
extern int * g_pOpenedList; /* used by 7 fn(s), first 0x10003dc0 */
extern undefined4 g_dwInitFlag; /* used by 7 fn(s), first 0x10003d70 */
extern undefined DAT_1002dd08; /* used by 2 fn(s), first 0x10004750 */
extern undefined DAT_1002dd0c; /* used by 2 fn(s), first 0x10004750 */
extern undefined DAT_1002dd10; /* used by 1 fn(s), first 0x10004750 */
extern undefined2 * DAT_1002dd14; /* used by 1 fn(s), first 0x10004820 */
extern undefined4 DAT_1002dd18; /* used by 1 fn(s), first 0x10004820 */
extern undefined DAT_1002dd1c; /* used by 1 fn(s), first 0x10004820 */
extern undefined DAT_1002dd20; /* used by 1 fn(s), first 0x10004820 */
extern undefined DAT_1002dd24; /* used by 1 fn(s), first 0x10004820 */
extern undefined DAT_1002dd28; /* used by 1 fn(s), first 0x10004820 */
extern undefined4 DAT_1002dd2c; /* used by 4 fn(s), first 0x10004660 */
extern undefined DAT_1002dd30; /* used by 1 fn(s), first 0x10004820 */
extern undefined DAT_1002dd32; /* used by 1 fn(s), first 0x10004660 */
extern undefined DAT_1002dd34; /* used by 1 fn(s), first 0x10004660 */
extern undefined DAT_1002dd38; /* used by 1 fn(s), first 0x10004660 */
extern undefined DAT_1002dd3c; /* used by 1 fn(s), first 0x10004660 */
extern undefined DAT_1002dd3e; /* used by 1 fn(s), first 0x10004660 */
extern undefined DAT_1002dd40; /* used by 1 fn(s), first 0x10004660 */
extern undefined DAT_1002dd50; /* used by 1 fn(s), first 0x10004660 */
extern undefined DAT_1002dd58; /* used by 1 fn(s), first 0x10004660 */
extern undefined DAT_1002dd5c; /* used by 1 fn(s), first 0x10004660 */
extern undefined DAT_1002dd60; /* used by 1 fn(s), first 0x10004820 */
extern undefined2 DAT_1002dd62; /* used by 3 fn(s), first 0x10004660 */
extern undefined DAT_1002dd64; /* used by 1 fn(s), first 0x10004660 */
extern undefined DAT_1002dd68; /* used by 2 fn(s), first 0x10004660 */
extern undefined DAT_1002dd6c; /* used by 2 fn(s), first 0x10004660 */
extern undefined DAT_1002dd6e; /* used by 1 fn(s), first 0x10004660 */
extern undefined DAT_1002dd70; /* used by 1 fn(s), first 0x10004660 */
extern undefined4 DAT_1002dd74; /* used by 3 fn(s), first 0x10004750 */
extern undefined DAT_1002dd78; /* used by 2 fn(s), first 0x10004660 */
extern undefined4 DAT_1002dd7c; /* used by 2 fn(s), first 0x10004750 */
extern uint g_dwGroupVols; /* used by 2 fn(s), first 0x100049b0 */
extern undefined4 DAT_1002dd84; /* used by 1 fn(s), first 0x100049e0 */
extern uint g_dwGroupEffVols; /* used by 3 fn(s), first 0x100049b0 */
extern undefined4 DAT_1002ddc4; /* used by 1 fn(s), first 0x100049e0 */
extern int g_dwPauseCount; /* used by 4 fn(s), first 0x10004aa0 */
extern undefined4 g_dwRunning50HzCount; /* used by 2 fn(s), first 0x10004aa0 */
extern uint g_dwRunning10HzCount; /* used by 2 fn(s), first 0x10004aa0 */
extern undefined4 g_dwIm_initialized; /* used by 2 fn(s), first 0x10004aa0 */
extern undefined4 g_dwIntFlag; /* used by 2 fn(s), first 0x10004aa0 */
extern undefined4 g_dwOutChannelCount; /* used by 3 fn(s), first 0x10005360 */
extern undefined4 g_dwDataSizeInBytes; /* used by 2 fn(s), first 0x10005300 */
extern undefined4 g_dwSoftLTable; /* used by 3 fn(s), first 0x10005360 */
extern uint g_dwMixBufSize; /* used by 2 fn(s), first 0x10005360 */
extern undefined DAT_1002df28; /* used by 1 fn(s), first 0x10005360 */
extern undefined g_aMxEndMix_wavHeader; /* used by 1 fn(s), first 0x10005610 */
extern int * g_pMixBuf; /* used by 9 fn(s), first 0x10005360 */
extern undefined4 g_dwRecordState; /* used by 3 fn(s), first 0x10005300 */
extern undefined4 g_dwRecordFile; /* used by 2 fn(s), first 0x10005300 */
extern undefined DAT_1002df68; /* used by 1 fn(s), first 0x10006360 */
extern undefined DAT_1002df6c; /* used by 1 fn(s), first 0x10006360 */
extern uint g_dwCurrentState; /* used by 7 fn(s), first 0x10006360 */
extern undefined4 DAT_1002df78; /* used by 5 fn(s), first 0x10006360 */
extern undefined DAT_1002df84; /* used by 1 fn(s), first 0x100068b0 */
extern undefined4 DAT_1002e25c; /* used by 1 fn(s), first 0x10006620 */
extern undefined4 DAT_1002e304; /* used by 3 fn(s), first 0x100064d0 */
extern int g_dwCurrentSequence; /* used by 7 fn(s), first 0x10006360 */
extern int g_dwCurrentCuePoint; /* used by 5 fn(s), first 0x10006360 */
extern char g_bTrans_name; /* used by 1 fn(s), first 0x100068b0 */
extern undefined DAT_1002e311; /* used by 1 fn(s), first 0x100068b0 */
extern undefined DAT_1002e330; /* used by 1 fn(s), first 0x10006070 */
extern undefined DAT_1002e338; /* used by 1 fn(s), first 0x10008ce0 */
extern undefined g_aLipSfx1Data; /* used by 2 fn(s), first 0x100089b0 */
extern undefined g_aStreamID; /* used by 5 fn(s), first 0x10007250 */
extern undefined g_dwMlListSize; /* used by 3 fn(s), first 0x10007a20 */
extern undefined g_dwMlEntryCount; /* used by 3 fn(s), first 0x10007a20 */
extern undefined g_aLipSfx2Data; /* used by 2 fn(s), first 0x100089b0 */
extern undefined g_bLipStreamData; /* used by 2 fn(s), first 0x100089b0 */
extern undefined g_aLipSfx3Data; /* used by 2 fn(s), first 0x100089b0 */
extern undefined g_aMcmpFileHandles; /* used by 3 fn(s), first 0x10009710 */
extern undefined DAT_100303a4; /* used by 1 fn(s), first 0x10009710 */
extern undefined DAT_100303a8; /* used by 1 fn(s), first 0x10009710 */
extern undefined DAT_100303ac; /* used by 1 fn(s), first 0x10009710 */
extern undefined DAT_100303b0; /* used by 1 fn(s), first 0x10009710 */
extern undefined DAT_100303b4; /* used by 1 fn(s), first 0x10009710 */
extern undefined DAT_100303b8; /* used by 1 fn(s), first 0x10009710 */
extern undefined DAT_100303bc; /* used by 1 fn(s), first 0x10009710 */
extern undefined DAT_100303c0; /* used by 1 fn(s), first 0x10009710 */
extern undefined DAT_100303c4; /* used by 1 fn(s), first 0x10009710 */
extern undefined DAT_100303c8; /* used by 1 fn(s), first 0x10009710 */
extern undefined DAT_100303cc; /* used by 1 fn(s), first 0x10009710 */
extern undefined DAT_100303d0; /* used by 1 fn(s), first 0x10009710 */
extern undefined DAT_10030429; /* used by 1 fn(s), first 0x10009710 */
extern undefined DAT_10031520; /* used by 2 fn(s), first 0x10009b20 */
extern undefined g_bSoundCache; /* used by 6 fn(s), first 0x100075d0 */
extern undefined4 DAT_10031548; /* used by 6 fn(s), first 0x10007410 */
extern undefined DAT_10031550; /* used by 3 fn(s), first 0x100075d0 */
extern undefined DAT_10031560; /* used by 1 fn(s), first 0x10007470 */
extern undefined DAT_10031564; /* used by 2 fn(s), first 0x10007410 */
extern undefined DAT_10031ce8; /* used by 5 fn(s), first 0x10007810 */
extern undefined DAT_10031d28; /* used by 2 fn(s), first 0x10008ce0 */
extern undefined g_iMuseMasterVolHold; /* used by 2 fn(s), first 0x10008860 */
extern undefined4 g_dwUseVoxFx; /* used by 5 fn(s), first 0x10007470 */
extern undefined DAT_10031d34; /* used by 1 fn(s), first 0x100072b0 */
extern undefined g_dwMlEntries; /* used by 4 fn(s), first 0x10007a20 */
extern undefined4 g_dwNextHandle; /* used by 3 fn(s), first 0x10008580 */
extern undefined g_bImuseInitialized; /* used by 5 fn(s), first 0x10007670 */
extern undefined DAT_10031d48; /* used by 1 fn(s), first 0x1000a100 */
extern undefined DAT_10031d4c; /* used by 1 fn(s), first 0x1000a0f0 */
extern undefined g_aLastVoiceFilename; /* used by 4 fn(s), first 0x100072b0 */
extern undefined g_bMuscriptRemote; /* used by 1 fn(s), first 0x100078b0 */
extern undefined DAT_10031e58; /* used by 2 fn(s), first 0x10007ca0 */
extern undefined DAT_10031e5c; /* used by 2 fn(s), first 0x10007ca0 */
extern undefined g_dwVoxFxBuf; /* used by 2 fn(s), first 0x10007ca0 */
extern undefined DAT_10031e64; /* used by 1 fn(s), first 0x10007ca0 */
extern undefined DAT_10031e68; /* used by 1 fn(s), first 0x10007ca0 */
extern undefined DAT_10031e6c; /* used by 1 fn(s), first 0x10007ca0 */
extern char * g_dwLipStreamID; /* used by 4 fn(s), first 0x100089b0 */
extern char * g_dwLipSfx1ID; /* used by 4 fn(s), first 0x100089b0 */
extern char * g_dwLipSfx2ID; /* used by 4 fn(s), first 0x100089b0 */
extern char * g_dwLipSfx3ID; /* used by 4 fn(s), first 0x100089b0 */
extern undefined DAT_10031e80; /* used by 1 fn(s), first 0x10008e00 */
extern undefined g_dwTimerCounter; /* used by 2 fn(s), first 0x10008ce0 */
extern undefined4 g_dwNextToAllocate; /* used by 1 fn(s), first 0x10009710 */
extern undefined4 g_dwIRes_csInit; /* used by 1 fn(s), first 0x10009710 */
extern uint * g_dwLastStreamLoaded; /* used by 5 fn(s), first 0x1000a1e0 */
extern undefined4 g_dwBailFlag; /* used by 4 fn(s), first 0x1000a500 */
extern undefined4 g_dwStreams; /* used by 3 fn(s), first 0x1000a1e0 */
extern undefined4 DAT_10031f28; /* used by 3 fn(s), first 0x1000a910 */
extern undefined4 DAT_10031f30; /* used by 1 fn(s), first 0x1000a7e0 */
extern undefined4 g_dwTrIntHandler_outSampleRate; /* used by 1 fn(s), first 0x1000aa40 */
extern undefined g_aTrInitialize_waveDriverInfo; /* used by 1 fn(s), first 0x1000a7e0 */
extern int g_dwTrackList; /* used by 16 fn(s), first 0x1000a7e0 */
extern undefined4 g_dwTrIntHandler_outFramesNeeded; /* used by 1 fn(s), first 0x1000aa40 */
extern undefined DAT_10032308; /* used by 1 fn(s), first 0x1000a7e0 */
extern undefined4 g_dwPauseTimer; /* used by 4 fn(s), first 0x1000a7e0 */
extern undefined4 DAT_10032310; /* used by 1 fn(s), first 0x1000aa40 */
extern undefined4 g_dwTrIntHandler_outPtr; /* used by 1 fn(s), first 0x1000aa40 */
extern undefined4 g_dwTrigs; /* used by 7 fn(s), first 0x1000b170 */
extern undefined4 DAT_10032424; /* used by 1 fn(s), first 0x1000b630 */
extern undefined4 DAT_10032cc0; /* used by 5 fn(s), first 0x1000b170 */
extern undefined4 DAT_10032cc4; /* used by 1 fn(s), first 0x1000b630 */
extern undefined4 g_dwTgProcessMarker_textCopy; /* used by 1 fn(s), first 0x1000b430 */
extern undefined4 g_dwDefersOn; /* used by 4 fn(s), first 0x1000b170 */
extern undefined4 g_dwMidProcessing; /* used by 3 fn(s), first 0x1000b170 */
extern undefined DAT_10032f48; /* used by 1 fn(s), first 0x1000b220 */
extern undefined DAT_10032f50; /* used by 1 fn(s), first 0x1000ba80 */
extern undefined DAT_10032f54; /* used by 2 fn(s), first 0x1000c230 */
extern undefined DAT_10032f58; /* used by 2 fn(s), first 0x1000c230 */
extern undefined4 DAT_10032f60; /* used by 3 fn(s), first 0x1000c400 */
extern undefined4 DAT_10032f64; /* used by 5 fn(s), first 0x1000c400 */
extern undefined4 DAT_10032fd0; /* used by 2 fn(s), first 0x1000d810 */
extern int DAT_10032fe0; /* used by 9 fn(s), first 0x1000be80 */
extern undefined DAT_10032fe4; /* used by 1 fn(s), first 0x10012550 */
extern undefined DAT_10032fe8; /* used by 1 fn(s), first 0x10012350 */
extern undefined DAT_10032fec; /* used by 1 fn(s), first 0x10011be0 */
extern int DAT_10032ff0; /* used by 6 fn(s), first 0x1000e780 */
extern undefined4 DAT_10033004; /* used by 1 fn(s), first 0x1000e780 */
extern undefined DAT_1003300c; /* used by 1 fn(s), first 0x1000c230 */
extern undefined DAT_10033010; /* used by 1 fn(s), first 0x1000c230 */
extern undefined DAT_10033014; /* used by 1 fn(s), first 0x1000c230 */
extern undefined DAT_10033018; /* used by 1 fn(s), first 0x1000c230 */
extern undefined DAT_1003301c; /* used by 1 fn(s), first 0x1000f080 */
extern undefined DAT_10033020; /* used by 1 fn(s), first 0x1000f080 */
extern undefined DAT_10033028; /* used by 1 fn(s), first 0x1000ef90 */
extern undefined DAT_10033038; /* used by 1 fn(s), first 0x1000f080 */
extern undefined DAT_10033040; /* used by 2 fn(s), first 0x1000d1f0 */
extern undefined DAT_10033044; /* used by 2 fn(s), first 0x1000c230 */
extern undefined4 DAT_10033048; /* used by 1 fn(s), first 0x1000ea40 */
extern undefined DAT_10033360; /* used by 3 fn(s), first 0x1000f330 */
extern undefined DAT_10033364; /* used by 3 fn(s), first 0x1000f330 */
extern undefined DAT_10033368; /* used by 2 fn(s), first 0x1000f330 */
extern undefined DAT_1003336c; /* used by 2 fn(s), first 0x1000f330 */
extern undefined DAT_10033370; /* used by 2 fn(s), first 0x1000f330 */
extern undefined DAT_10033374; /* used by 2 fn(s), first 0x1000f330 */
extern undefined DAT_1003337c; /* used by 1 fn(s), first 0x1000f840 */
extern code *DAT_10033380; /* used by 1 fn(s), first 0x1000fa30 */
extern undefined DAT_10033384; /* used by 1 fn(s), first 0x1000d810 */
extern undefined4 DAT_10033388; /* used by 2 fn(s), first 0x10011690 */
extern undefined DAT_1003338c; /* used by 1 fn(s), first 0x10011be0 */
extern undefined DAT_10033390; /* used by 1 fn(s), first 0x10012350 */
extern undefined DAT_10033394; /* used by 1 fn(s), first 0x10012350 */
extern undefined DAT_10033398; /* used by 1 fn(s), first 0x10012350 */
extern undefined DAT_1003339c; /* used by 1 fn(s), first 0x10012550 */
extern undefined DAT_100333a0; /* used by 1 fn(s), first 0x10012840 */
extern undefined DAT_100333a4; /* used by 1 fn(s), first 0x10012840 */
extern undefined DAT_100333b4; /* used by 1 fn(s), first 0x10012840 */
extern undefined DAT_100333bc; /* used by 1 fn(s), first 0x10012640 */
extern undefined DAT_100333c2; /* used by 1 fn(s), first 0x10012350 */
extern undefined DAT_100333c6; /* used by 1 fn(s), first 0x10011c90 */
extern undefined DAT_100333c8; /* used by 1 fn(s), first 0x10011c90 */
extern undefined DAT_100333f0; /* used by 1 fn(s), first 0x10012bc0 */
extern int DAT_100333f4; /* used by 1 fn(s), first 0x10012d50 */
extern code *DAT_100333f8; /* used by 1 fn(s), first 0x10012e90 */
extern code *DAT_100333fc; /* used by 1 fn(s), first 0x10012e90 */
extern code *DAT_10033400; /* used by 1 fn(s), first 0x10012e90 */
extern undefined4 DAT_10033404; /* used by 2 fn(s), first 0x1000fc50 */
extern code *DAT_10033408; /* used by 1 fn(s), first 0x10012f20 */
extern undefined DAT_100334fc; /* used by 1 fn(s), first 0x10014690 */
extern undefined DAT_10033500; /* used by 1 fn(s), first 0x100147c0 */
extern int g_dwTrackCount; /* used by 6 fn(s), first 0x100020c0 */
extern undefined4 g_dwSounds_pHS; /* used by 29 fn(s), first 0x10001f10 */
extern undefined g_aVoxFxName; /* used by 3 fn(s), first 0x10008250 */
extern undefined DAT_10033547; /* used by 1 fn(s), first 0x1000a160 */
extern undefined g_bPanTable; /* used by 1 fn(s), first 0x10005360 */
extern undefined DAT_10033568; /* used by 1 fn(s), first 0x100054f0 */
extern code * g_dwImuseInitData; /* used by 3 fn(s), first 0x10004570 */
extern code * DAT_100336a4; /* used by 2 fn(s), first 0x10004540 */
extern code *DAT_100336a8; /* used by 2 fn(s), first 0x1000b6a0 */
extern code * DAT_100336ac; /* used by 2 fn(s), first 0x100045c0 */
extern code * DAT_100336b0; /* used by 2 fn(s), first 0x10004600 */
extern code *DAT_100336b4; /* used by 2 fn(s), first 0x10004640 */
extern undefined4 DAT_100336bc; /* used by 4 fn(s), first 0x100036b0 */
extern undefined4 DAT_100336c0; /* used by 7 fn(s), first 0x1000e0c0 */
extern undefined DAT_100336c4; /* used by 2 fn(s), first 0x1000f330 */
extern int * PTR_100336e0; /* used by 23 fn(s), first 0x1000d130 */
extern undefined4 DAT_100336e4; /* used by 1 fn(s), first 0x1000ed20 */
extern undefined4 DAT_100337e0; /* used by 10 fn(s), first 0x1000d3e0 */
extern undefined4 DAT_100337e4; /* used by 1 fn(s), first 0x1000ea40 */
extern undefined4 * DAT_100337e8; /* used by 1 fn(s), first 0x1000ea40 */
extern undefined4 DAT_100337ec; /* used by 4 fn(s), first 0x1000be80 */
extern undefined DAT_100337f0; /* used by 1 fn(s), first 0x1000be80 */
extern undefined DAT_100337f4; /* used by 4 fn(s), first 0x1000d130 */
extern undefined DAT_10034800; /* used by 4 fn(s), first 0x1000d130 */
extern undefined DAT_10034804; /* used by 2 fn(s), first 0x1000c230 */
extern undefined DAT_10034808; /* used by 1 fn(s), first 0x1000c350 */

/* ---- re-typed views of the symbols above ---- */
#define _DAT_10017064 (*(undefined *)&DAT_10017064) /* same address as DAT_10017064, other width */
#define _DAT_10017084 (*(undefined *)&DAT_10017084) /* same address as DAT_10017084, other width */
#define _DAT_10017090 (*(undefined *)&DAT_10017090) /* same address as DAT_10017090, other width */
#define _g_dwTAIL_BYTES (*(undefined4 *)&g_dwTAIL_BYTES) /* same address as g_dwTAIL_BYTES, other width */
#define _g_dwImVoiceBufferSize (*(undefined4 *)&g_dwImVoiceBufferSize) /* same address as g_dwImVoiceBufferSize, other width */
#define _g_dwImVoiceGulpSize (*(undefined4 *)&g_dwImVoiceGulpSize) /* same address as g_dwImVoiceGulpSize, other width */
#define _g_dwImVoiceCriticalSize (*(undefined4 *)&g_dwImVoiceCriticalSize) /* same address as g_dwImVoiceCriticalSize, other width */
#define _g_dwImMusicBufferSize (*(undefined4 *)&g_dwImMusicBufferSize) /* same address as g_dwImMusicBufferSize, other width */
#define _g_dwImMusicGulpSize (*(undefined4 *)&g_dwImMusicGulpSize) /* same address as g_dwImMusicGulpSize, other width */
#define _g_dwImMusicCriticalSize (*(undefined4 *)&g_dwImMusicCriticalSize) /* same address as g_dwImMusicCriticalSize, other width */
#define _g_dwImNonPurgeCacheSize (*(undefined4 *)&g_dwImNonPurgeCacheSize) /* same address as g_dwImNonPurgeCacheSize, other width */
#define _g_dwEffectsHeapSize (*(undefined4 *)&g_dwEffectsHeapSize) /* same address as g_dwEffectsHeapSize, other width */
#define _g_bMuscriptLocal (*(undefined4 *)&g_bMuscriptLocal) /* same address as g_bMuscriptLocal, other width */
#define _DAT_1001e90c (*(undefined4 *)&DAT_1001e90c) /* same address as DAT_1001e90c, other width */
#define _DAT_1001e9d0 (*(code * *)&DAT_1001e9d0) /* same address as DAT_1001e9d0, other width */
#define _DAT_1001e9ec (*(undefined4 *)&DAT_1001e9ec) /* same address as DAT_1001e9ec, other width */
#define _DAT_1001ea0c (*(undefined4 *)&DAT_1001ea0c) /* same address as DAT_1001ea0c, other width */
#define _DAT_1001ea1c (*(undefined4 *)&DAT_1001ea1c) /* same address as DAT_1001ea1c, other width */
#define _DAT_1001ea2c (*(undefined4 *)&DAT_1001ea2c) /* same address as DAT_1001ea2c, other width */
#define _DAT_1001f014 (*(undefined4 *)&DAT_1001f014) /* same address as DAT_1001f014, other width */
#define _DAT_1001f224 (*(undefined4 *)&DAT_1001f224) /* same address as DAT_1001f224, other width */
#define _DAT_10021d04 (*(int * *)&DAT_10021d04) /* same address as DAT_10021d04, other width */
#define _DAT_10021d10 (*(undefined4 *)&DAT_10021d10) /* same address as DAT_10021d10, other width */
#define _DAT_10021d14 (*(undefined4 *)&DAT_10021d14) /* same address as DAT_10021d14, other width */
#define _DAT_10021d18 (*(undefined4 *)&DAT_10021d18) /* same address as DAT_10021d18, other width */
#define _DAT_10021d40 (*(int * *)&DAT_10021d40) /* same address as DAT_10021d40, other width */
#define _g_dwPredictStream_jumpHook (*(undefined4 *)&g_dwPredictStream_jumpHook) /* same address as g_dwPredictStream_jumpHook, other width */
#define _DAT_1002dd08 (*(undefined4 *)&DAT_1002dd08) /* same address as DAT_1002dd08, other width */
#define _DAT_1002dd0c (*(undefined4 *)&DAT_1002dd0c) /* same address as DAT_1002dd0c, other width */
#define _DAT_1002dd10 (*(uint *)&DAT_1002dd10) /* same address as DAT_1002dd10, other width */
#define _DAT_1002dd1c (*(undefined2 * *)&DAT_1002dd1c) /* same address as DAT_1002dd1c, other width */
#define _DAT_1002dd20 (*(uint *)&DAT_1002dd20) /* same address as DAT_1002dd20, other width */
#define _DAT_1002dd24 (*(undefined4 *)&DAT_1002dd24) /* same address as DAT_1002dd24, other width */
#define _DAT_1002dd28 (*(undefined4 *)&DAT_1002dd28) /* same address as DAT_1002dd28, other width */
#define _DAT_1002dd30 (*(undefined2 *)&DAT_1002dd30) /* same address as DAT_1002dd30, other width */
#define _DAT_1002dd32 (*(undefined2 *)&DAT_1002dd32) /* same address as DAT_1002dd32, other width */
#define _DAT_1002dd34 (*(undefined4 *)&DAT_1002dd34) /* same address as DAT_1002dd34, other width */
#define _DAT_1002dd38 (*(undefined4 *)&DAT_1002dd38) /* same address as DAT_1002dd38, other width */
#define _DAT_1002dd3c (*(undefined2 *)&DAT_1002dd3c) /* same address as DAT_1002dd3c, other width */
#define _DAT_1002dd3e (*(undefined2 *)&DAT_1002dd3e) /* same address as DAT_1002dd3e, other width */
#define _DAT_1002dd40 (*(undefined2 *)&DAT_1002dd40) /* same address as DAT_1002dd40, other width */
#define _DAT_1002dd50 (*(undefined4 *)&DAT_1002dd50) /* same address as DAT_1002dd50, other width */
#define _DAT_1002dd58 (*(undefined4 *)&DAT_1002dd58) /* same address as DAT_1002dd58, other width */
#define _DAT_1002dd5c (*(undefined4 *)&DAT_1002dd5c) /* same address as DAT_1002dd5c, other width */
#define _DAT_1002dd60 (*(undefined2 *)&DAT_1002dd60) /* same address as DAT_1002dd60, other width */
#define _DAT_1002dd64 (*(undefined4 *)&DAT_1002dd64) /* same address as DAT_1002dd64, other width */
#define _DAT_1002dd68 (*(undefined4 *)&DAT_1002dd68) /* same address as DAT_1002dd68, other width */
#define _DAT_1002dd6c (*(undefined2 *)&DAT_1002dd6c) /* same address as DAT_1002dd6c, other width */
#define _DAT_1002dd6e (*(undefined2 *)&DAT_1002dd6e) /* same address as DAT_1002dd6e, other width */
#define _DAT_1002dd70 (*(undefined2 *)&DAT_1002dd70) /* same address as DAT_1002dd70, other width */
#define _DAT_1002dd78 (*(undefined4 *)&DAT_1002dd78) /* same address as DAT_1002dd78, other width */
#define _DAT_1002df28 (*(undefined4 *)&DAT_1002df28) /* same address as DAT_1002df28, other width */
#define _DAT_1002df68 (*(undefined4 *)&DAT_1002df68) /* same address as DAT_1002df68, other width */
#define _DAT_1002df6c (*(undefined4 *)&DAT_1002df6c) /* same address as DAT_1002df6c, other width */
#define _DAT_1002e330 (*(undefined4 *)&DAT_1002e330) /* same address as DAT_1002e330, other width */
#define _DAT_1002e338 (*(undefined4 *)&DAT_1002e338) /* same address as DAT_1002e338, other width */
#define _g_aStreamID (*(undefined4 *)&g_aStreamID) /* same address as g_aStreamID, other width */
#define _g_dwMlListSize (*(undefined4 *)&g_dwMlListSize) /* same address as g_dwMlListSize, other width */
#define _g_dwMlEntryCount (*(undefined4 *)&g_dwMlEntryCount) /* same address as g_dwMlEntryCount, other width */
#define _DAT_10031520 (*(undefined4 *)&DAT_10031520) /* same address as DAT_10031520, other width */
#define _DAT_10031d28 (*(undefined4 *)&DAT_10031d28) /* same address as DAT_10031d28, other width */
#define _g_iMuseMasterVolHold (*(undefined4 *)&g_iMuseMasterVolHold) /* same address as g_iMuseMasterVolHold, other width */
#define _DAT_10031d34 (*(undefined4 *)&DAT_10031d34) /* same address as DAT_10031d34, other width */
#define _g_dwMlEntries (*(int * *)&g_dwMlEntries) /* same address as g_dwMlEntries, other width */
#define _g_bImuseInitialized (*(undefined4 *)&g_bImuseInitialized) /* same address as g_bImuseInitialized, other width */
#define _DAT_10031d48 (*(undefined4 *)&DAT_10031d48) /* same address as DAT_10031d48, other width */
#define _DAT_10031d4c (*(undefined4 *)&DAT_10031d4c) /* same address as DAT_10031d4c, other width */
#define _g_bMuscriptRemote (*(undefined4 *)&g_bMuscriptRemote) /* same address as g_bMuscriptRemote, other width */
#define _DAT_10031e58 (*(undefined4 *)&DAT_10031e58) /* same address as DAT_10031e58, other width */
#define _DAT_10031e5c (*(undefined4 *)&DAT_10031e5c) /* same address as DAT_10031e5c, other width */
#define _g_dwVoxFxBuf (*(undefined4 *)&g_dwVoxFxBuf) /* same address as g_dwVoxFxBuf, other width */
#define _DAT_10031e64 (*(undefined4 *)&DAT_10031e64) /* same address as DAT_10031e64, other width */
#define _DAT_10031e68 (*(undefined4 *)&DAT_10031e68) /* same address as DAT_10031e68, other width */
#define _DAT_10031e6c (*(undefined4 *)&DAT_10031e6c) /* same address as DAT_10031e6c, other width */
#define _DAT_10031e80 (*(undefined4 *)&DAT_10031e80) /* same address as DAT_10031e80, other width */
#define _g_dwTimerCounter (*(undefined4 *)&g_dwTimerCounter) /* same address as g_dwTimerCounter, other width */
#define _DAT_10032308 (*(undefined4 *)&DAT_10032308) /* same address as DAT_10032308, other width */
#define _DAT_10032f50 (*(undefined4 *)&DAT_10032f50) /* same address as DAT_10032f50, other width */
#define _DAT_10032f54 (*(undefined4 *)&DAT_10032f54) /* same address as DAT_10032f54, other width */
#define _DAT_10032f58 (*(undefined4 * *)&DAT_10032f58) /* same address as DAT_10032f58, other width */
#define _DAT_10032fe4 (*(undefined4 *)&DAT_10032fe4) /* same address as DAT_10032fe4, other width */
#define _DAT_10032fe8 (*(undefined4 *)&DAT_10032fe8) /* same address as DAT_10032fe8, other width */
#define _DAT_10032fec (*(undefined4 *)&DAT_10032fec) /* same address as DAT_10032fec, other width */
#define _DAT_1003300c (*(undefined4 *)&DAT_1003300c) /* same address as DAT_1003300c, other width */
#define _DAT_10033010 (*(undefined4 *)&DAT_10033010) /* same address as DAT_10033010, other width */
#define _DAT_10033014 (*(undefined4 *)&DAT_10033014) /* same address as DAT_10033014, other width */
#define _DAT_10033018 (*(undefined4 *)&DAT_10033018) /* same address as DAT_10033018, other width */
#define _DAT_1003301c (*(undefined4 *)&DAT_1003301c) /* same address as DAT_1003301c, other width */
#define _DAT_10033020 (*(undefined4 *)&DAT_10033020) /* same address as DAT_10033020, other width */
#define _DAT_10033028 (*(undefined4 *)&DAT_10033028) /* same address as DAT_10033028, other width */
#define _DAT_10033038 (*(undefined4 *)&DAT_10033038) /* same address as DAT_10033038, other width */
#define _DAT_10033044 (*(undefined4 *)&DAT_10033044) /* same address as DAT_10033044, other width */
#define _DAT_10033360 (*(undefined4 *)&DAT_10033360) /* same address as DAT_10033360, other width */
#define _DAT_10033364 (*(undefined4 *)&DAT_10033364) /* same address as DAT_10033364, other width */
#define _DAT_10033368 (*(undefined4 *)&DAT_10033368) /* same address as DAT_10033368, other width */
#define _DAT_1003336c (*(undefined4 *)&DAT_1003336c) /* same address as DAT_1003336c, other width */
#define _DAT_10033370 (*(undefined4 *)&DAT_10033370) /* same address as DAT_10033370, other width */
#define _DAT_10033374 (*(undefined4 *)&DAT_10033374) /* same address as DAT_10033374, other width */
#define _DAT_1003337c (*(undefined4 *)&DAT_1003337c) /* same address as DAT_1003337c, other width */
#define _DAT_10033384 (*(undefined4 *)&DAT_10033384) /* same address as DAT_10033384, other width */
#define _DAT_1003338c (*(int * *)&DAT_1003338c) /* same address as DAT_1003338c, other width */
#define _DAT_10033390 (*(undefined4 *)&DAT_10033390) /* same address as DAT_10033390, other width */
#define _DAT_10033394 (*(undefined4 *)&DAT_10033394) /* same address as DAT_10033394, other width */
#define _DAT_10033398 (*(undefined4 *)&DAT_10033398) /* same address as DAT_10033398, other width */
#define _DAT_1003339c (*(int * *)&DAT_1003339c) /* same address as DAT_1003339c, other width */
#define _DAT_100333a0 (*(undefined4 *)&DAT_100333a0) /* same address as DAT_100333a0, other width */
#define _DAT_100333a4 (*(undefined4 *)&DAT_100333a4) /* same address as DAT_100333a4, other width */
#define _DAT_100333b4 (*(undefined2 *)&DAT_100333b4) /* same address as DAT_100333b4, other width */
#define _DAT_100333bc (*(undefined2 *)&DAT_100333bc) /* same address as DAT_100333bc, other width */
#define _DAT_100333c2 (*(undefined2 *)&DAT_100333c2) /* same address as DAT_100333c2, other width */
#define _DAT_100333c6 (*(undefined2 *)&DAT_100333c6) /* same address as DAT_100333c6, other width */
#define _DAT_100333c8 (*(undefined2 *)&DAT_100333c8) /* same address as DAT_100333c8, other width */
#define _DAT_100333f0 (*(undefined4 *)&DAT_100333f0) /* same address as DAT_100333f0, other width */
#define _DAT_100334fc (*(undefined4 *)&DAT_100334fc) /* same address as DAT_100334fc, other width */
#define _DAT_10033500 (*(undefined4 *)&DAT_10033500) /* same address as DAT_10033500, other width */
#define _g_aVoxFxName (*(undefined4 *)&g_aVoxFxName) /* same address as g_aVoxFxName, other width */
#define _DAT_100336c4 (*(undefined4 *)&DAT_100336c4) /* same address as DAT_100336c4, other width */
#define _DAT_100337f0 (*(int *)&DAT_100337f0) /* same address as DAT_100337f0, other width */
#define _DAT_100337f4 (*(undefined4 *)&DAT_100337f4) /* same address as DAT_100337f4, other width */
#define _DAT_10034800 (*(undefined4 *)&DAT_10034800) /* same address as DAT_10034800, other width */
#define _DAT_10034804 (*(undefined4 * *)&DAT_10034804) /* same address as DAT_10034804, other width */
#define _DAT_10034808 (*(code * *)&DAT_10034808) /* same address as DAT_10034808, other width */

/* ---- data the code addressed by number (IMG_ADDR): the span at that address (src/IMUSE.DLL/data.c) ---- */
extern unsigned char DAT_10015438[]; /* 0x10015438 */
extern unsigned char DAT_100154b4[]; /* 0x100154b4 */
extern unsigned char DAT_100154b8[]; /* 0x100154b8 */
extern unsigned char s_GetLastActivePopup_10015e28[]; /* 0x10015e28 */
extern unsigned char s_GetActiveWindow_10015e3c[]; /* 0x10015e3c */
extern unsigned char s_MessageBoxA_10015e4c[]; /* 0x10015e4c */
extern unsigned char DAT_10015e58[]; /* 0x10015e58 */
extern unsigned char DAT_10017004[]; /* 0x10017004 */
extern unsigned char DAT_10017008[]; /* 0x10017008 */
extern unsigned char DAT_10017010[]; /* 0x10017010 */
extern unsigned char DAT_10017124[]; /* 0x10017124 */
extern unsigned char DAT_10017144[]; /* 0x10017144 */
extern unsigned char DAT_10017174[]; /* 0x10017174 */
extern unsigned char DAT_100171b4[]; /* 0x100171b4 */
extern unsigned char DAT_100171e4[]; /* 0x100171e4 */
extern unsigned char DAT_100171f4[]; /* 0x100171f4 */
extern unsigned char DAT_10017210[]; /* 0x10017210 */
extern unsigned char DAT_10017224[]; /* 0x10017224 */
extern unsigned char DAT_10017240[]; /* 0x10017240 */
extern unsigned char DAT_10017268[]; /* 0x10017268 */
extern unsigned char DAT_10017290[]; /* 0x10017290 */
extern unsigned char DAT_100172b0[]; /* 0x100172b0 */
extern unsigned char DAT_100172c4[]; /* 0x100172c4 */
extern unsigned char DAT_1001ae4c[]; /* 0x1001ae4c */
extern unsigned char DAT_1001bbc4[]; /* 0x1001bbc4 */
extern unsigned char DAT_1001e68c[]; /* 0x1001e68c */
extern unsigned char DAT_1001e6b4[]; /* 0x1001e6b4 */
extern unsigned char DAT_1001e6d8[]; /* 0x1001e6d8 */
extern unsigned char DAT_1001e910[]; /* 0x1001e910 */
extern unsigned char DAT_1001e930[]; /* 0x1001e930 */
extern unsigned char DAT_1001e944[]; /* 0x1001e944 */
extern unsigned char DAT_1001e958[]; /* 0x1001e958 */
extern unsigned char DAT_1001e970[]; /* 0x1001e970 */
extern unsigned char DAT_1001e97c[]; /* 0x1001e97c */
extern unsigned char DAT_1001e98c[]; /* 0x1001e98c */
extern unsigned char DAT_1001e99c[]; /* 0x1001e99c */
extern unsigned char DAT_1001e9b8[]; /* 0x1001e9b8 */
extern unsigned char DAT_1001eaa8[]; /* 0x1001eaa8 */
extern unsigned char DAT_1001eaac[]; /* 0x1001eaac */
extern unsigned char DAT_1001eac0[]; /* 0x1001eac0 */
extern unsigned char DAT_1001eb20[]; /* 0x1001eb20 */
extern unsigned char DAT_1001ed11[]; /* 0x1001ed11 */
extern unsigned char DAT_1001ed34[]; /* 0x1001ed34 */
extern unsigned char DAT_1001f260[]; /* 0x1001f260 */
extern unsigned char DAT_1001f268[]; /* 0x1001f268 */
extern unsigned char DAT_1001f26c[]; /* 0x1001f26c */
extern unsigned char DAT_1001f270[]; /* 0x1001f270 */
extern unsigned char DAT_1001f274[]; /* 0x1001f274 */
extern unsigned char DAT_1001f278[]; /* 0x1001f278 */
extern unsigned char DAT_1001f358[]; /* 0x1001f358 */
extern unsigned char DAT_1001f364[]; /* 0x1001f364 */
extern unsigned char DAT_1001f408[]; /* 0x1001f408 */
extern unsigned char DAT_10021c58[]; /* 0x10021c58 */
extern unsigned char DAT_10021d08[]; /* 0x10021d08 */
extern unsigned char DAT_10021da8[]; /* 0x10021da8 */
extern unsigned char DAT_10021f08[]; /* 0x10021f08 */
extern unsigned char DAT_1002d7f0[]; /* 0x1002d7f0 */
extern unsigned char DAT_1002dae8[]; /* 0x1002dae8 */
extern unsigned char DAT_1002daec[]; /* 0x1002daec */
extern unsigned char DAT_1002dcef[]; /* 0x1002dcef */
extern unsigned char DAT_1002dd48[]; /* 0x1002dd48 */
extern unsigned char DAT_1002de00[]; /* 0x1002de00 */
extern unsigned char DAT_1002eb14[]; /* 0x1002eb14 */
extern unsigned char DAT_1002eb33[]; /* 0x1002eb33 */
extern unsigned char DAT_1002eb34[]; /* 0x1002eb34 */
extern unsigned char DAT_1002eb3c[]; /* 0x1002eb3c */
extern unsigned char DAT_1002ebdb[]; /* 0x1002ebdb */
extern unsigned char DAT_1002ebe0[]; /* 0x1002ebe0 */
extern unsigned char DAT_1002ebe4[]; /* 0x1002ebe4 */
extern unsigned char DAT_1002ebe8[]; /* 0x1002ebe8 */
extern unsigned char DAT_1002ebec[]; /* 0x1002ebec */
extern unsigned char DAT_1002fbb8[]; /* 0x1002fbb8 */
extern unsigned char DAT_1003039f[]; /* 0x1003039f */
extern unsigned char DAT_100303d4[]; /* 0x100303d4 */
extern unsigned char DAT_100303da[]; /* 0x100303da */
extern unsigned char DAT_1003151f[]; /* 0x1003151f */
extern unsigned char DAT_10031547[]; /* 0x10031547 */
extern unsigned char DAT_10031554[]; /* 0x10031554 */
extern unsigned char DAT_10031558[]; /* 0x10031558 */
extern unsigned char DAT_10031d4f[]; /* 0x10031d4f */
extern unsigned char DAT_10033008[]; /* 0x10033008 */
extern unsigned char DAT_10033050[]; /* 0x10033050 */
extern unsigned char DAT_10033158[]; /* 0x10033158 */
extern unsigned char DAT_10033159[]; /* 0x10033159 */
extern unsigned char DAT_10033260[]; /* 0x10033260 */
extern unsigned char DAT_10033430[]; /* 0x10033430 */
extern unsigned char DAT_10033437[]; /* 0x10033437 */
extern unsigned char DAT_10033438[]; /* 0x10033438 */
