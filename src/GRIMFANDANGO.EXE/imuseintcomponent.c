/* GRIMFANDANGO.EXE :: imuseintcomponent.c
 * functions 0x00497840 .. 0x00497840 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00497840  IMuseRequester ---- */
/* Costume tag handler for 'iMuse Sequence / iMuse State' (registered by sputCostume_Start through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 1 of the iMuse Sequence / iMuse State integer tags:
   registers the key with Cos_RegisterComponent. Original name IMuseRequester (the remaster's
   GrimFandango (Linux): the same handler slot (requester) of the same costume tag registration in
   sputCostume_Startup); was ImuseIntComponent_Create. */

int IMuseRequester(uint param_1,int param_2,int param_3,int param_4)

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
  iVar2 = Cos_RegisterComponent(param_1,(int)pcVar1,1,param_2,0,param_4,0);
  return iVar2 != 0;
}
