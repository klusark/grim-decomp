/* GRIMFANDANGO.EXE :: smush.c
 * functions 0x004bd500 .. 0x004bdf00 (9 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004bd500  Smush_Pause ---- */
undefined4 Smush_Pause(void)

{
  if (UINT_008d16a8 != 0) {
    (**(code **)(UINT_008d1200 + 0x24))(UINT_008d11d8,1);
  }
  return 0;
}

/* ---- 0x004bd520  Smush_Resume ---- */
undefined4 Smush_Resume(void)

{
  if (UINT_008d16a8 != 0) {
    (**(code **)(UINT_008d1200 + 0x24))(UINT_008d11d8,0);
  }
  return 0;
}

/* ---- 0x004bd560  Smush_Idle ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Smush_Idle(undefined4 param_1)

{
  _DAT_008d16b4 = param_1;
  return;
}

/* ---- 0x004bd570  Smush_Open ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl
Smush_Open(char *name,int flags,int bufferSize,int x,int y,int w,int h,int a,int sixteenBit)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint *puVar7;
  undefined4 *puVar8;
  char *pcVar9;
  char *pcVar10;
  uint *puVar11;
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(undefined4 (*)[6])(_frame + (0x30 - 0x18)))
  
  bVar2 = false;
  if (UINT_008d1098 == 0) {
    return 1;
  }
  puVar8 = local_18;
  for (iVar4 = 6; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar8 = 0;
    puVar8 = puVar8 + 1;
  }
  iVar4 = (*(code *)*PTR_008d10c8)(name,&DAT_004ddb18);
  if (iVar4 != 0) {
    uVar5 = 0xffffffff;
    pcVar9 = name;
    do {
      pcVar10 = pcVar9;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar10 = pcVar9 + 1;
      cVar1 = *pcVar9;
      pcVar9 = pcVar10;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    puVar7 = (uint *)(pcVar10 + -uVar5);
    puVar11 = &UINT_008d10d0;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *puVar11 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar11 = puVar11 + 1;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(char *)puVar11 = (char)*puVar7;
      puVar7 = (uint *)((int)puVar7 + 1);
      puVar11 = (uint *)((int)puVar11 + 1);
    }
    (*(code *)PTR_008d10c8[5])(iVar4,a,1);
    iVar3 = Insane_ReadFrameHeader(iVar4,&DAT_008d1208);
    if (iVar3 == 0) {
      (*(code *)PTR_008d10c8[1])(iVar4);
      _DAT_008d166c = 5;
      _DAT_008d1670 = 6 - (uint)(sixteenBit != 0);
      _DAT_008d1674 = 5;
      _DAT_008d167c = 5;
      _DAT_008d1678 = 0xb - (uint)(sixteenBit != 0);
      _DAT_008d1684 = 3;
      _DAT_008d168c = 3;
      _DAT_008d1688 = (sixteenBit != 0) + 2;
      _DAT_008d1648 = 0;
      _DAT_008d164c = 0x280;
      _DAT_008d1650 = 0x1e0;
      _DAT_008d1654 = 2;
      _DAT_008d1658 = 0x10;
      _DAT_008d165c = 0x500;
      _DAT_008d1660 = 0;
      _DAT_008d1664 = 0;
      _DAT_008d1668 = 1;
      _DAT_008d1680 = 0;
      iVar4 = (*(code *)UINT_008d1098)(w,h,0x10,sixteenBit);
      if (iVar4 == 0) {
        _DAT_008d1090 = flags & 0xfffffff;
        bVar2 = true;
        iVar4 = (**(code **)(UINT_008d1200 + 4))
                          (&UINT_008d11d8,name,0xf,UINT_008d121a + 500000,UINT_008d121a + 10000,
                           0x600d);
        if (iVar4 == 0) {
          if (x < 0) {
            UINT_008d11e0 = (uint)DAT_008d120c;
          }
          else {
            UINT_008d11e0 = x;
          }
          if (y < 0) {
            UINT_008d11e4 = (uint)DAT_008d120e;
          }
          else {
            UINT_008d11e4 = y;
          }
          UINT_008d11e8 = (uint)DAT_008d1210;
          UINT_008d11ec = (uint)DAT_008d1212;
          if (UINT_008d10a8 != 0) {
            (*(code *)UINT_008d10a8)();
          }
          UINT_008d16a8 = 1;
          return 0;
        }
      }
    }
    else {
      (*(code *)PTR_008d10c8[1])();
    }
  }
  if (bVar2) {
    (*(code *)UINT_008d109c)();
  }
  return 1;
}
#undef local_18
#undef local_1c


/* ---- 0x004bd930  Smush_Close ---- */
undefined4 Smush_Close(void)

{
  if (UINT_008d16a8 != 0) {
    (**(code **)(UINT_008d1200 + 0x14))(&UINT_008d11d8);
    (**(code **)(UINT_008d169c + 0x10))();
    UINT_008d16b8 = 0;
  }
  UINT_008d16a8 = 0;
  (*(code *)UINT_008d109c)();
  return 0;
}

/* ---- 0x004bd970  Smush_Advance ---- */
int __cdecl Smush_Advance(int *outDone)

{
  unsigned char _frame[0x480] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_46c (*(uint *)(_frame + (0x480 - 0x46c)))
  #define local_468 (*(uint *)(_frame + (0x480 - 0x468)))
  #define auStack_464 (*(undefined1 (*)[16])(_frame + (0x480 - 0x464)))
  #define auStack_454 (*(undefined1 (*)[84])(_frame + (0x480 - 0x454)))
  #define local_400 (*(undefined1 (*)[1024])(_frame + (0x480 - 0x400)))
  
  local_46c = 0;
  local_468 = 0;
  Blocky16_SetOption(1,FUN_004bdad0,0);
  iVar1 = (**(code **)(UINT_008d1200 + 0xc))
                    (UINT_008d11d8,&DAT_008d1648,0,0,0,local_400,&local_468,&local_46c,1,0);
  (*(code *)UINT_008d10a0)(auStack_454,auStack_464);
  Insane_PrepareFrame(auStack_454,UINT_008d16b8,auStack_464);
  (*(code *)UINT_008d10a4)(auStack_454,auStack_464);
  if ((iVar1 < 0) || (iVar1 == 4)) {
    (**(code **)(UINT_008d1200 + 0x14))(&UINT_008d11d8);
    UINT_008d16b8 = 0;
    if ((DAT_008d1090 & 0x10) == 0) {
      *outDone = 1;
      UINT_008d16a8 = 0;
    }
    else {
      *outDone = 0;
      if (UINT_008d1216 == 0) {
        iVar1 = 0xf;
      }
      else {
        iVar1 = ((int)UINT_008d1216 / 2 + 1000000) / (int)UINT_008d1216;
      }
      (**(code **)(UINT_008d1200 + 4))
                (&UINT_008d11d8,&UINT_008d10d0,iVar1,UINT_008d121a + 500000,UINT_008d121a + 10000,
                 0x600d);
      UINT_008d16a8 = 1;
    }
  }
  else {
    *outDone = 0;
    UINT_008d16a8 = 1;
  }
  Blocky16_SetOption(1,0,0);
  return 0;
}
#undef auStack_454
#undef auStack_464
#undef local_400
#undef local_468
#undef local_46c


/* ---- 0x004bde90  Smush_SetColorTable ---- */
void Smush_SetColorTable(uint param_1)

{
  UINT_008d16bc = param_1;
  return;
}

/* ---- 0x004bdea0  Smush_GetFrameRect ---- */
undefined4 Smush_GetFrameRect(uint *param_1,uint *param_2)

{
  if (param_1 != (uint *)0x0) {
    *param_1 = UINT_008d11e0;
    param_1[1] = UINT_008d11e4;
    param_1[2] = UINT_008d11e8;
    param_1[3] = UINT_008d11ec;
  }
  if (param_2 != (uint *)0x0) {
    *param_2 = UINT_008d1638;
    param_2[1] = UINT_008d163c;
    param_2[2] = UINT_008d1640;
    param_2[3] = UINT_008d1644;
  }
  return 0;
}

/* ---- 0x004bdf00  Smush_SetFile ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
undefined * __cdecl Smush_SetFile(uint param_1)

{
  unsigned char _frame[0x440] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 unaff_ESI;
  longlong lVar2;
  #define auStack_428 (*(undefined1 (*)[2])(_frame + (0x440 - 0x428)))
  #define sStack_426 (*(short *)(_frame + (0x440 - 0x426)))
  
  iVar1 = (*(code *)*PTR_008d10c8)(param_1,&DAT_004dda54);
  if (iVar1 == 0) {
    return (undefined *)0x0;
  }
  Insane_ReadFrameHeader(iVar1,auStack_428);
  (*(code *)PTR_008d10c8[1])(iVar1);
  lVar2 = _ftol((double)CONCAT44((int)sStack_426,unaff_ESI));
  return (undefined *)lVar2;
}
#undef auStack_428
#undef sStack_426

#endif

