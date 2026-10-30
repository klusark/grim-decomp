/* IMUSE.DLL :: soundstartvoicestream.c
 * functions 0x100088d0 .. 0x100088d0 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x100088d0  SoundStartVoiceStream ---- */
int __cdecl SoundStartVoiceStream(undefined4 param_1,undefined4 param_2,uint param_3,uint param_4)

{
  int iVar1;
  
                    /* 0x88d0  51  SoundStartVoiceStream */
  ImStopSound(10000);
  SoundsCloseVoiceFile();
  iVar1 = SoundsRegisterVoice(param_1);
  if (iVar1 != 0) {
    SoundsFillStreamsWhileMusicCritical(5);
    ImStartStream(10000,0x7f,1);
    ImSetParam(10000,0x400,2);
    ImSetParam(10000,0x600,param_3);
    ImSetParam(10000,0x700,param_4);
    ImProcessStreams();
    ImProcessStreams();
    return 0;
  }
  return 1;
}
