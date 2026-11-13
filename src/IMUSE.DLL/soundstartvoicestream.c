/* IMUSE.DLL :: soundstartvoicestream.c
 * functions 0x100088d0 .. 0x100088d0 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x100088d0  SoundStartVoiceStream ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
int __cdecl SoundStartVoiceStream(char *name,uint volume,uint pan)

{
  int *piVar1;
  
                    /* 0x88d0  51  SoundStartVoiceStream */
  ImStopSound(10000);
  SoundsCloseVoiceFile();
  piVar1 = SoundsRegisterVoice(name);
  if (piVar1 != (int *)0x0) {
    SoundsFillStreamsWhileMusicCritical(5);
    ImStartStream(10000,0x7f,1);
    ImSetParam(10000,0x400,2);
    ImSetParam(10000,0x600,volume);
    ImSetParam(10000,0x700,pan);
    ImProcessStreams();
    ImProcessStreams();
    return 0;
  }
  return 1;
}
#endif

