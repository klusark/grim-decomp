/* CHORE.DLL :: chore.c
 * functions 0x100053e0 .. 0x10005530 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x100053e0  Chore_AdvanceTime ---- */
/* Advances a chore by dt ms. Keys with time in [cur, cur+dt) are set; first update after
   Cos_InstPlayChore already takes dt (no zero-length first frame). time >= length ends the chore
   (flags and time cleared); a looping chore carries the remainder over from time 0. */

void __cdecl Chore_AdvanceTime(int param_1,int param_2,int param_3,int param_4,undefined4 param_5)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  byte *pbVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  iVar1 = *(int *)(param_1 + 0x34) + param_3 * 0x2c;
  pbVar2 = (byte *)(*(int *)(param_2 + 4) + param_3 * 0xc);
  if (param_4 == 0) {
    return;
  }
  do {
    local_4 = 0;
    if (0 < *(int *)(iVar1 + 0x20)) {
      param_3 = 0;
      do {
        piVar5 = (int *)(*(int *)(iVar1 + 0x24) + param_3);
        iVar6 = piVar5[2];
        if (iVar6 != 0) {
          iVar7 = 0;
          if (0 < iVar6) {
            piVar4 = (int *)piVar5[3];
            do {
              if (*(int *)(pbVar2 + 8) <= *piVar4) break;
              iVar7 = iVar7 + 1;
              piVar4 = piVar4 + 2;
            } while (iVar7 < iVar6);
          }
          if (iVar7 < iVar6) {
            do {
              iVar3 = *(int *)(piVar5[3] + iVar7 * 8);
              iVar6 = piVar5[3] + iVar7 * 8;
              if (param_4 + *(int *)(pbVar2 + 8) <= iVar3) break;
              FUN_10005530(2,PTR_100143c0 +
                             *(int *)(*(int *)(param_1 + 0x2c) + 0x20 + *piVar5 * 0x40) * 0x17,
                           *(undefined4 *)(*(int *)(param_2 + 0xc) + *piVar5 * 4),iVar6,
                           (param_4 + *(int *)(pbVar2 + 8)) - iVar3,iVar6,0,param_5);
              iVar7 = iVar7 + 1;
            } while (iVar7 < piVar5[2]);
          }
        }
        local_4 = local_4 + 1;
        param_3 = param_3 + 0x10;
      } while (local_4 < *(int *)(iVar1 + 0x20));
    }
    iVar6 = *(int *)(pbVar2 + 8) + param_4;
    *(int *)(pbVar2 + 8) = iVar6;
    if (iVar6 < *(int *)(iVar1 + 0x28)) {
      return;
    }
    if ((*pbVar2 & 2) == 0) {
      pbVar2[0] = 0;
      pbVar2[1] = 0;
      pbVar2[2] = 0;
      pbVar2[3] = 0;
      pbVar2[8] = 0;
      pbVar2[9] = 0;
      pbVar2[10] = 0;
      pbVar2[0xb] = 0;
      return;
    }
    param_4 = iVar6 - *(int *)(iVar1 + 0x28);
    pbVar2[8] = 0;
    pbVar2[9] = 0;
    pbVar2[10] = 0;
    pbVar2[0xb] = 0;
  } while( true );
}
#undef local_4


/* ---- 0x10005530  FUN_10005530 ---- */
void __cdecl
FUN_10005530(undefined4 param_1,undefined4 *param_2,undefined4 param_3,int param_4,
            undefined4 param_5,int param_6,undefined4 param_7,undefined4 param_8)

{
  int iVar1;
  
  iVar1 = param_2[1];
  if (((iVar1 != 0) && (iVar1 != 1)) && (iVar1 != 2)) {
    (**(code **)(DAT_100143a8 + 0x18))
              (&DAT_10010284,s_C__grimsrc_libs_chore_Costume_c_1001020c,0xd67);
    return;
  }
  (*(code *)param_2[0xb])
            (*param_2,param_3,param_1,*(undefined4 *)(param_4 + 4),param_5,
             *(undefined4 *)(param_6 + 4),param_7,param_8);
  return;
}
