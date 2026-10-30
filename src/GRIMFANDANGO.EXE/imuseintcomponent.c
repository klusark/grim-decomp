/* GRIMFANDANGO.EXE :: imuseintcomponent.c
 * functions 0x00497840 .. 0x00497840 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00497840  ImuseIntComponent_Create ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Costume tag handler for 'iMuse Sequence / iMuse State' (registered by sputCostume_Start through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 1 of the iMuse Sequence / iMuse State integer tags:
   registers the key with Cos_RegisterComponent. */

bool ImuseIntComponent_Create(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  char *pcVar1;
  int iVar2;
  
  if (param_3 != 0) {
    return false;
  }
  pcVar1 = s_iMuse_Sequence_004ea2b4;
  if (param_2 != 0x65736d69) {
    pcVar1 = s_iMuse_State_004ea2a8;
  }
  iVar2 = Cos_RegisterComponent(param_1,pcVar1,1,param_2,0,param_4,0);
  return iVar2 != 0;
}
#endif

