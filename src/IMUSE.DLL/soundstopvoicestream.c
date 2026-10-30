/* IMUSE.DLL :: soundstopvoicestream.c
 * functions 0x10008970 .. 0x10008970 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10008970  SoundStopVoiceStream ---- */
undefined4 __cdecl SoundStopVoiceStream(void)

{
  undefined4 uVar1;
  
                    /* 0x8970  52  SoundStopVoiceStream */
  ImStopSound(10000);
  uVar1 = FUN_10007250(10000);
  return uVar1;
}
