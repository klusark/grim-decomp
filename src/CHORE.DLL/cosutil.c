/* CHORE.DLL :: cosutil.c
 * functions 0x10001110 .. 0x10003100 (24 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10001110  CosUtil_Write ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 CosUtil_Write(char *param_1,int param_2,undefined4 param_3)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int *piVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined *puVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint *puVar11;
  int *piVar12;
  char *pcVar13;
  undefined4 *puVar14;
  #define uStack_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define uStack_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define uStack_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define uStack_18 (*(undefined4 *)(_frame + (0x40 - 0x18)))
  #define iStack_c (*(int *)(_frame + (0x40 - 0xc)))
  #define uStack_8 (*(undefined1 *)(_frame + (0x40 - 0x8)))
  
                    /* 0x1110  24  CosUtil_Write */
  if (param_2 == 0) {
    (**(code **)(DAT_100143a8 + 0x18))(IMG_ADDR(0x100101f8),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x14c);
  }
  uStack_24 = 0;
  if (*(int *)(param_2 + 0x30) != 0) {
    puVar11 = (uint *)(*(int *)(param_2 + 0x34) + 0x20);
    do {
      uVar3 = *puVar11;
      uStack_20 = 0;
      if (uVar3 != 0) {
        iVar10 = 0;
        do {
          uVar6 = 0;
          if (uVar3 != 0) {
            iVar8 = 0;
            do {
              if ((uStack_20 != uVar6) &&
                 (*(int *)(puVar11[1] + iVar10) == *(int *)(puVar11[1] + iVar8))) {
                return 0;
              }
              uVar6 = uVar6 + 1;
              iVar8 = iVar8 + 0x10;
            } while (uVar6 < uVar3);
          }
          uStack_20 = uStack_20 + 1;
          iVar10 = iVar10 + 0x10;
        } while (uStack_20 < uVar3);
      }
      uStack_24 = uStack_24 + 1;
      puVar11 = puVar11 + 0xb;
    } while (uStack_24 < *(uint *)(param_2 + 0x30));
  }
  uVar3 = FUN_10003c20(param_2);
  if (_DAT_100143e4 != (code *)0x0) {
    uVar4 = ((code *)FUN_10005180)((param_2 - DAT_100143b4) / 0x3c,param_3);
    iVar10 = (*_DAT_100143e4)(param_1,uVar4);
    if (iVar10 == 0) {
      return 0;
    }
  }
  iVar10 = (**(code **)(DAT_100143a8 + 0x30))(param_1,IMG_ADDR(0x100101f4));
  if (iVar10 == 0) {
    return 0;
  }
  iVar8 = FUN_100056a0(param_1,0x5c);
  if (iVar8 == 0) {
    uVar6 = 0xffffffff;
    pcVar13 = param_1;
    do {
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      cVar1 = *pcVar13;
      pcVar13 = pcVar13 + 1;
    } while (cVar1 != '\0');
    if (0x20 < ~uVar6 - 1) {
      uStack_18 = 0;
      goto LAB_1000167e;
    }
    FUN_100055a0(param_2,param_1,0x1f);
    *(undefined1 *)(param_2 + 0x1f) = 0;
  }
  else {
    uVar6 = 0xffffffff;
    pcVar13 = (char *)(iVar8 + 1);
    do {
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      cVar1 = *pcVar13;
      pcVar13 = pcVar13 + 1;
    } while (cVar1 != '\0');
    if (0x20 < ~uVar6 - 1) {
      uStack_18 = 0;
      goto LAB_1000167e;
    }
    FUN_100055a0(param_2,(char *)(iVar8 + 1),0x1f);
    *(undefined1 *)(param_2 + 0x1f) = 0;
  }
  (**(code **)(DAT_100143a8 + 0x54))(iVar10,IMG_ADDR(0x100101ec),param_3);
  (**(code **)(DAT_100143a8 + 0x54))(iVar10,IMG_ADDR(0x100101d8),0,1);
  (**(code **)(DAT_100143a8 + 0x54))(iVar10,IMG_ADDR(0x100101c8));
  (**(code **)(DAT_100143a8 + 0x54))(iVar10,IMG_ADDR(0x100101b8),uVar3);
  (**(code **)(DAT_100143a8 + 0x54))(iVar10,IMG_ADDR(0x100101a0));
  uVar6 = 0;
  if (uVar3 != 0) {
    piVar12 = (int *)&DAT_10014210;
    do {
      iVar8 = *piVar12;
      iStack_c = PTR_100143c0[iVar8 * 0x17];
      uStack_8 = 0;
      if (PTR_100143c0[iVar8 * 0x17 + 1] == 0) {
        uVar4 = IMG_ADDR(0x1001019c);
      }
      else {
        uVar4 = IMG_ADDR(0x10010198);
        if (PTR_100143c0[iVar8 * 0x17 + 1] != 1) {
          uVar4 = IMG_ADDR(0x10010190);
        }
      }
      (**(code **)(DAT_100143a8 + 0x54))
                (iVar10,IMG_ADDR(0x1001017c),uVar6,&iStack_c,uVar4,PTR_100143c0 + iVar8 * 0x17 + 2);
      uVar6 = uVar6 + 1;
      piVar12 = piVar12 + 1;
    } while (uVar6 < uVar3);
  }
  (**(code **)(DAT_100143a8 + 0x54))(iVar10,IMG_ADDR(0x10010164));
  (**(code **)(DAT_100143a8 + 0x54))(iVar10,IMG_ADDR(0x10010150),*(undefined4 *)(param_2 + 0x28));
  (**(code **)(DAT_100143a8 + 0x54))(iVar10,IMG_ADDR(0x10010130));
  iVar8 = *(int *)(param_2 + 0x2c);
  uStack_24 = 0;
  if (*(int *)(param_2 + 0x28) != 0) {
    do {
      uVar6 = 0;
      if (_DAT_10014210 != *(int *)(iVar8 + 0x20)) {
        puVar5 = &DAT_10014210;
        do {
          if (uVar3 <= uVar6) break;
          piVar12 = (int *)(puVar5 + 4);
          puVar5 = puVar5 + 4;
          uVar6 = uVar6 + 1;
        } while (*piVar12 != *(int *)(iVar8 + 0x20));
      }
      if (uVar6 == uVar3) {
        (**(code **)(DAT_100143a8 + 0x18))
                  (IMG_ADDR(0x10010120),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x1a9);
      }
      (**(code **)(DAT_100143a8 + 0x54))
                (iVar10,IMG_ADDR(0x10010108),uStack_24,uVar6,*(undefined4 *)(iVar8 + 0x28));
      uStack_24 = uStack_24 + 1;
      iVar8 = iVar8 + 0x40;
    } while (uStack_24 < *(uint *)(param_2 + 0x28));
  }
  (**(code **)(DAT_100143a8 + 0x54))(iVar10,IMG_ADDR(0x100100f4));
  (**(code **)(DAT_100143a8 + 0x54))(iVar10,IMG_ADDR(0x100100e4),*(undefined4 *)(param_2 + 0x30));
  (**(code **)(DAT_100143a8 + 0x54))(iVar10,IMG_ADDR(0x100100c8));
  uVar3 = 0;
  iVar8 = *(int *)(param_2 + 0x34);
  if (*(int *)(param_2 + 0x30) != 0) {
    do {
      iVar7 = *(int *)(iVar8 + 0x20);
      iVar9 = 0;
      if (iVar7 != 0) {
        piVar12 = (int *)(*(int *)(iVar8 + 0x24) + 8);
        do {
          if (*piVar12 != 0) {
            iVar9 = iVar9 + 1;
          }
          piVar12 = piVar12 + 4;
          iVar7 = iVar7 + -1;
        } while (iVar7 != 0);
      }
      (**(code **)(DAT_100143a8 + 0x54))
                (iVar10,IMG_ADDR(0x100100b4),uVar3,*(undefined4 *)(iVar8 + 0x28),iVar9,iVar8);
      uVar3 = uVar3 + 1;
      iVar8 = iVar8 + 0x2c;
    } while (uVar3 < *(uint *)(param_2 + 0x30));
  }
  (**(code **)(DAT_100143a8 + 0x54))(iVar10,IMG_ADDR(0x100100a4));
  uStack_20 = 0;
  iVar8 = *(int *)(param_2 + 0x34);
  if (*(int *)(param_2 + 0x30) != 0) {
    do {
      (**(code **)(DAT_100143a8 + 0x54))(iVar10,IMG_ADDR(0x10010094),uStack_20,iVar8);
      piVar12 = *(int **)(iVar8 + 0x24);
      uStack_1c = 0;
      if (*(int *)(iVar8 + 0x20) != 0) {
        do {
          if (piVar12[2] != 0) {
            (**(code **)(DAT_100143a8 + 0x54))(iVar10);
            (**(code **)(DAT_100143a8 + 0x54))(iVar10);
            (**(code **)(DAT_100143a8 + 0x54))(iVar10,IMG_ADDR(0x10010060),*piVar12,piVar12[2]);
            piVar2 = PTR_100143c0;
            puVar14 = (undefined4 *)piVar12[3];
            iVar7 = *(int *)(*piVar12 * 0x40 + 0x20 + *(int *)(param_2 + 0x2c));
            uStack_24 = 0;
            if (piVar12[2] != 0) {
              do {
                iVar9 = piVar2[iVar7 * 0x17 + 1];
                if ((iVar9 == 0) || (iVar9 == 1)) {
                  (**(code **)(DAT_100143a8 + 0x54))(iVar10,IMG_ADDR(0x10010054),*puVar14);
                }
                else if (iVar9 == 2) {
                  (**(code **)(DAT_100143a8 + 0x54))
                            (iVar10,IMG_ADDR(0x10010048),*puVar14,(double)(float)puVar14[1]);
                }
                else {
                  (**(code **)(DAT_100143a8 + 0x18))
                            (IMG_ADDR(0x10010040),s_C__grimsrc_libs_chore_Costume_c_1001020c);
                }
                uStack_24 = uStack_24 + 1;
                puVar14 = puVar14 + 2;
              } while (uStack_24 < (uint)piVar12[2]);
            }
            (**(code **)(DAT_100143a8 + 0x54))();
          }
          uStack_1c = uStack_1c + 1;
          piVar12 = piVar12 + 4;
        } while (uStack_1c < *(uint *)(iVar8 + 0x20));
      }
      uStack_20 = uStack_20 + 1;
      iVar8 = iVar8 + 0x2c;
    } while (uStack_20 < *(uint *)(param_2 + 0x30));
  }
LAB_1000167e:
  (**(code **)(DAT_100143a8 + 0x34))();
  return uStack_18;
}
#undef iStack_c
#undef uStack_18
#undef uStack_1c
#undef uStack_20
#undef uStack_24
#undef uStack_8

#endif


/* ---- 0x10002020  CosUtil_CompPtrFromHandle ---- */
int CosUtil_CompPtrFromHandle(int param_1,uint param_2)

{
                    /* 0x2020  8  CosUtil_CompPtrFromHandle */
  if (*(uint *)(param_1 + 0x28) <= param_2) {
    return 0;
  }
  return *(int *)(param_1 + 0x2c) + param_2 * 0x40;
}

/* ---- 0x10002040  CosUtil_PtrFromHandle ---- */
int CosUtil_PtrFromHandle(undefined4 param_1)

{
  int iVar1;
  
                    /* 0x2040  18  CosUtil_PtrFromHandle */
  iVar1 = FUN_10005160(param_1);
  return DAT_100143b4 + iVar1 * 0x3c;
}

/* ---- 0x10002060  CosUtil_RegisterCompNotifier ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 CosUtil_RegisterCompNotifier(undefined4 param_1)

{
  undefined4 uVar1;
  
                    /* 0x2060  21  CosUtil_RegisterCompNotifier */
  uVar1 = _DAT_100143d8;
  _DAT_100143d8 = param_1;
  return uVar1;
}

/* ---- 0x10002070  CosUtil_RegisterBitmapMunger ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 CosUtil_RegisterBitmapMunger(undefined4 param_1)

{
  undefined4 uVar1;
  
                    /* 0x2070  20  CosUtil_RegisterBitmapMunger */
  uVar1 = _DAT_100143dc;
  _DAT_100143dc = param_1;
  return uVar1;
}

/* ---- 0x10002260  CosUtil_DeleteComponent ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 CosUtil_DeleteComponent(uint param_1,uint param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  bool bVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  uint *puVar5;
  int iVar6;
  undefined4 uVar7;
  uint *puVar8;
  int *piVar9;
  int iVar10;
  uint uVar11;
  uint *puVar12;
  undefined4 *puVar13;
  int iVar14;
  int iVar15;
  undefined4 *puVar16;
  uint uVar17;
  int *piVar18;
  #define piStack_c (*(int **)(_frame + (0x20 - 0xc)))
  
                    /* 0x2260  15  CosUtil_DeleteComponent */
  iVar2 = CosUtil_PtrFromHandle(param_1);
  if ((iVar2 == 0) || (*(uint *)(iVar2 + 0x28) <= param_2)) {
    return 0;
  }
  piVar3 = (int *)(**(code **)(DAT_100143a8 + 0x20))
                            (*(uint *)(iVar2 + 0x28) * 4,s_C__grimsrc_libs_chore_Costume_c_1001020c,
                             0x539);
  uVar4 = 0;
  piVar18 = piVar3;
  if (*(int *)(iVar2 + 0x28) != 0) {
    do {
      *piVar18 = 0;
      uVar4 = uVar4 + 1;
      piVar18 = piVar18 + 1;
    } while (uVar4 < *(uint *)(iVar2 + 0x28));
  }
  puVar5 = (uint *)(**(code **)(DAT_100143a8 + 0x20))
                             (*(int *)(iVar2 + 0x28) << 2,s_C__grimsrc_libs_chore_Costume_c_1001020c
                              ,0x53e);
  uVar4 = 0;
  puVar12 = puVar5;
  if (*(int *)(iVar2 + 0x28) != 0) {
    do {
      *puVar12 = uVar4;
      uVar4 = uVar4 + 1;
      puVar12 = puVar12 + 1;
    } while (uVar4 < *(uint *)(iVar2 + 0x28));
  }
  param_1 = 0;
  piVar3[param_2] = 1;
  puVar5[param_2] = 0xffffffff;
  if (*(int *)(iVar2 + 0x28) != 0) {
    iVar14 = 0;
    puVar12 = puVar5;
    do {
      bVar1 = false;
      for (iVar10 = *(int *)(iVar14 + 0x2c + *(int *)(iVar2 + 0x2c)); iVar10 != -1;
          iVar10 = *(int *)(iVar10 * 0x40 + 0x2c + *(int *)(iVar2 + 0x2c))) {
        if (piVar3[iVar10] != 0) {
          bVar1 = true;
          break;
        }
      }
      if (bVar1) {
        *(undefined4 *)(((int)piVar3 - (int)puVar5) + (int)puVar12) = 1;
        *puVar12 = 0xffffffff;
      }
      param_1 = param_1 + 1;
      iVar14 = iVar14 + 0x40;
      puVar12 = puVar12 + 1;
    } while (param_1 < *(uint *)(iVar2 + 0x28));
  }
  iVar14 = 0;
  param_1 = 0;
  piStack_c = piVar3;
  if (*(int *)(iVar2 + 0x28) != 0) {
    do {
      if (*piStack_c != 0) {
        iVar15 = iVar14 + *(int *)(iVar2 + 0x2c);
        iVar10 = *(int *)(iVar15 + 0x28);
        iVar6 = FUN_10004170(iVar2,PTR_100143c0[*(int *)(iVar15 + 0x20) * 0x17],iVar10 + 1,iVar15);
        iVar10 = iVar10 + 2;
        while (-1 < iVar6) {
          piVar18 = (int *)(iVar6 * 0x40 + 0x28 + *(int *)(iVar2 + 0x2c));
          *piVar18 = *piVar18 + -1;
          iVar6 = FUN_10004170(iVar2,PTR_100143c0[*(int *)(iVar15 + 0x20) * 0x17],iVar10,iVar15);
          iVar10 = iVar10 + 1;
        }
      }
      param_1 = param_1 + 1;
      iVar14 = iVar14 + 0x40;
      piStack_c = piStack_c + 1;
    } while (param_1 < *(uint *)(iVar2 + 0x28));
  }
  iVar14 = 0;
  uVar4 = 0;
  if (*(int *)(iVar2 + 0x28) != 0) {
    param_1 = 0;
    piVar18 = piVar3;
    do {
      iVar14 = iVar14 + (uint)(*piVar18 != 0);
      if ((*piVar18 == 0) && (iVar14 != 0)) {
        *(uint *)(((int)puVar5 - (int)piVar3) + (int)piVar18) = uVar4 - iVar14;
        puVar16 = (undefined4 *)(param_1 + *(int *)(iVar2 + 0x2c));
        puVar13 = (undefined4 *)((uVar4 - iVar14) * 0x40 + *(int *)(iVar2 + 0x2c));
        for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
          *puVar13 = *puVar16;
          puVar16 = puVar16 + 1;
          puVar13 = puVar13 + 1;
        }
      }
      uVar4 = uVar4 + 1;
      piVar18 = piVar18 + 1;
      param_1 = param_1 + 0x40;
    } while (uVar4 < *(uint *)(iVar2 + 0x28));
  }
  uVar4 = *(uint *)(iVar2 + 0x28);
  *(uint *)(iVar2 + 0x28) = uVar4 - iVar14;
  uVar7 = (**(code **)(DAT_100143a8 + 0x28))
                    (*(undefined4 *)(iVar2 + 0x2c),(uVar4 - iVar14) * 0x40,
                     s_C__grimsrc_libs_chore_Costume_c_1001020c,0x583);
  *(undefined4 *)(iVar2 + 0x2c) = uVar7;
  uVar17 = 0;
  if (*(int *)(iVar2 + 0x28) != 0) {
    iVar14 = 0;
    do {
      iVar10 = *(int *)(iVar14 + 0x2c + *(int *)(iVar2 + 0x2c));
      if (iVar10 != -1) {
        *(uint *)(iVar14 + 0x2c + *(int *)(iVar2 + 0x2c)) = puVar5[iVar10];
      }
      uVar17 = uVar17 + 1;
      iVar14 = iVar14 + 0x40;
    } while (uVar17 < *(uint *)(iVar2 + 0x28));
  }
  uVar17 = 0;
  if (*(int *)(iVar2 + 0x30) != 0) {
    puVar12 = (uint *)(*(int *)(iVar2 + 0x34) + 0x20);
    do {
      uVar11 = 0;
      puVar8 = (uint *)puVar12[1];
      if (*puVar12 != 0) {
        do {
          uVar11 = uVar11 + 1;
          *puVar8 = puVar5[*puVar8];
          puVar8 = puVar8 + 4;
        } while (uVar11 < *puVar12);
      }
      uVar17 = uVar17 + 1;
      puVar12 = puVar12 + 0xb;
    } while (uVar17 < *(uint *)(iVar2 + 0x30));
  }
  param_1 = 0;
  if (*(int *)(iVar2 + 0x30) != 0) {
    piVar18 = (int *)(*(int *)(iVar2 + 0x34) + 0x24);
    do {
      piVar9 = (int *)*piVar18;
      iVar14 = 0;
      uVar17 = 0;
      if (piVar18[-1] != 0) {
        piStack_c = (int *)0x0;
        do {
          iVar14 = iVar14 + (uint)(*piVar9 == -1);
          if (*piVar9 == -1) {
            if (piVar9[2] != 0) {
              (**(code **)(DAT_100143a8 + 0x24))(piVar9[3]);
            }
          }
          else if (iVar14 != 0) {
            puVar16 = (undefined4 *)(*piVar18 + (int)piStack_c);
            puVar13 = (undefined4 *)((uVar17 - iVar14) * 0x10 + *piVar18);
            *puVar13 = *puVar16;
            puVar13[1] = puVar16[1];
            puVar13[2] = puVar16[2];
            puVar13[3] = puVar16[3];
          }
          uVar17 = uVar17 + 1;
          piStack_c = (int *)((int)piStack_c + 0x10);
          piVar9 = piVar9 + 4;
        } while (uVar17 < (uint)piVar18[-1]);
      }
      iVar10 = piVar18[-1];
      piVar18[-1] = iVar10 - iVar14;
      iVar14 = (**(code **)(DAT_100143a8 + 0x28))
                         (*piVar18,(iVar10 - iVar14) * 0x10,
                          s_C__grimsrc_libs_chore_Costume_c_1001020c,0x5be);
      *piVar18 = iVar14;
      param_1 = param_1 + 1;
      piVar18 = piVar18 + 0xb;
    } while (param_1 < *(uint *)(iVar2 + 0x30));
  }
  if (_DAT_100143d8 != (code *)0x0) {
    iVar14 = 0;
    uVar17 = 0;
    piVar18 = piVar3;
    if (uVar4 != 0) {
      do {
        if (*piVar18 != 0) {
          (*_DAT_100143d8)(iVar2,0,uVar17 - iVar14,0);
          iVar14 = iVar14 + 1;
        }
        uVar17 = uVar17 + 1;
        piVar18 = piVar18 + 1;
      } while (uVar17 < uVar4);
    }
  }
  (**(code **)(DAT_100143a8 + 0x24))(piVar3);
  (**(code **)(DAT_100143a8 + 0x24))(puVar5);
  return 1;
}
#undef piStack_c


/* ---- 0x100026a0  CosUtil_AdjustComponent ---- */
int CosUtil_AdjustComponent(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
                    /* 0x26a0  6  CosUtil_AdjustComponent */
  if (param_1 == 0) {
    (**(code **)(DAT_100143a8 + 0x18))(IMG_ADDR(0x1001034c),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x5df);
  }
  if (*(uint *)(param_1 + 0x28) <= param_2) {
    (**(code **)(DAT_100143a8 + 0x18))(IMG_ADDR(0x10010320),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x5e0);
  }
  iVar2 = *(int *)(param_1 + 0x2c) + param_2 * 0x40;
  iVar3 = *(int *)(iVar2 + 0x20);
  iVar1 = PTR_100143c0[iVar3 * 0x17 + 1];
  if ((iVar1 != 0) && (iVar1 != 1)) {
    if (iVar1 == 2) {
      iVar3 = (*(code *)PTR_100143c0[iVar3 * 0x17 + 0xf])(iVar2 + 0x24,iVar2,0x20);
      return iVar3;
    }
    return param_1;
  }
  iVar3 = (*(code *)PTR_100143c0[iVar3 * 0x17 + 0xf])(iVar2 + 0x24,iVar2,0x20);
  return iVar3;
}

/* ---- 0x10002740  CosUtil_ComponentHasAdjuster ---- */
undefined4 CosUtil_ComponentHasAdjuster(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  
                    /* 0x2740  9  CosUtil_ComponentHasAdjuster */
  if (param_1 == 0) {
    (**(code **)(DAT_100143a8 + 0x18))(IMG_ADDR(0x1001034c),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x604);
  }
  if (*(uint *)(param_1 + 0x28) <= param_2) {
    (**(code **)(DAT_100143a8 + 0x18))(IMG_ADDR(0x10010320),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x605);
  }
  iVar1 = *(int *)(*(int *)(param_1 + 0x2c) + 0x20 + param_2 * 0x40);
  iVar2 = PTR_100143c0[iVar1 * 0x17 + 1];
  if ((((iVar2 != 0) || (PTR_100143c0[iVar1 * 0x17 + 0xf] == 0)) &&
      ((iVar2 != 1 || (PTR_100143c0[iVar1 * 0x17 + 0xf] == 0)))) &&
     ((iVar2 != 2 || (PTR_100143c0[iVar1 * 0x17 + 0xf] == 0)))) {
    return 0;
  }
  return 1;
}

/* ---- 0x100027e0  CosUtil_AddComponent ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool CosUtil_AddComponent
               (undefined4 param_1,int param_2,int param_3,undefined4 param_4,undefined4 param_5)

{
  int *piVar1;
  code *pcVar2;
  int iVar3;
  uint uVar4;
  
                    /* 0x27e0  2  CosUtil_AddComponent */
  uVar4 = 0;
  piVar1 = PTR_100143c0;
  if (_DAT_100143b8 != 0) {
    do {
      if (*piVar1 == param_3) break;
      uVar4 = uVar4 + 1;
      piVar1 = piVar1 + 0x17;
    } while (uVar4 < _DAT_100143b8);
  }
  if (uVar4 == _DAT_100143b8) {
    return false;
  }
  iVar3 = piVar1[1];
  if (iVar3 == 0) {
    pcVar2 = (code *)piVar1[0xc];
    if (pcVar2 == (code *)0x0) {
      return false;
    }
  }
  else {
    if ((iVar3 != 1) && (iVar3 != 2)) {
      (**(code **)(DAT_100143a8 + 0x18))
                (&DAT_10010284,s_C__grimsrc_libs_chore_Costume_c_1001020c,0x652);
      return param_2 != 0;
    }
    pcVar2 = (code *)piVar1[0xc];
    if (pcVar2 == (code *)0x0) {
      return false;
    }
  }
  iVar3 = (*pcVar2)(param_1,param_3,param_4,param_5,param_2);
  return iVar3 != 0;
}

/* ---- 0x10002880  CosUtil_AddChore ---- */
int CosUtil_AddChore(int param_1)

{
  int iVar1;
  
                    /* 0x2880  1  CosUtil_AddChore */
  if (param_1 == 0) {
    (**(code **)(DAT_100143a8 + 0x18))(IMG_ADDR(0x1001034c),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x668);
  }
  iVar1 = *(int *)(param_1 + 0x30) + 1;
  *(int *)(param_1 + 0x30) = iVar1;
  iVar1 = (**(code **)(DAT_100143a8 + 0x28))
                    (*(undefined4 *)(param_1 + 0x34),iVar1 * 0x2c,
                     s_C__grimsrc_libs_chore_Costume_c_1001020c,0x66c);
  *(int *)(param_1 + 0x34) = iVar1;
  FUN_10004140(iVar1 + -0x2c + *(int *)(param_1 + 0x30) * 0x2c);
  return *(int *)(param_1 + 0x30) + -1;
}

/* ---- 0x100028f0  CosUtil_DeleteChore ---- */
undefined4 __cdecl CosUtil_DeleteChore(int param_1,uint param_2)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
                    /* 0x28f0  14  CosUtil_DeleteChore */
  if ((param_1 == 0) || (*(uint *)(param_1 + 0x30) <= param_2)) {
    (**(code **)(DAT_100143a8 + 0x18))(IMG_ADDR(0x10010364),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x67d);
  }
  iVar2 = *(int *)(param_1 + 0x34) + param_2 * 0x2c;
  iVar4 = *(int *)(*(int *)(param_1 + 0x34) + 0x20 + param_2 * 0x2c);
  if (iVar4 != 0) {
    uVar3 = 0;
    if (iVar4 != 0) {
      iVar4 = 0;
      do {
        if (*(int *)(*(int *)(iVar2 + 0x24) + 8 + iVar4) != 0) {
          (**(code **)(DAT_100143a8 + 0x24))(*(undefined4 *)(*(int *)(iVar2 + 0x24) + iVar4 + 0xc));
        }
        uVar3 = uVar3 + 1;
        iVar4 = iVar4 + 0x10;
      } while (uVar3 < *(uint *)(iVar2 + 0x20));
    }
    (**(code **)(DAT_100143a8 + 0x24))(*(undefined4 *)(iVar2 + 0x24));
  }
  if (param_2 < *(int *)(param_1 + 0x30) - 1U) {
    FUN_10005860(iVar2,iVar2 + 0x2c,*(int *)(param_1 + 0x30) * 0x2c + (param_2 + 1) * -0x2c);
  }
  iVar2 = *(int *)(param_1 + 0x30) + -1;
  *(int *)(param_1 + 0x30) = iVar2;
  uVar1 = (**(code **)(DAT_100143a8 + 0x28))
                    (*(undefined4 *)(param_1 + 0x34),iVar2 * 0x2c,
                     s_C__grimsrc_libs_chore_Costume_c_1001020c,0x697);
  *(undefined4 *)(param_1 + 0x34) = uVar1;
  return uVar1;
}

/* ---- 0x100029e0  CosUtil_SetChoreLength ---- */
int __cdecl CosUtil_SetChoreLength(int param_1,uint param_2,uint param_3)

{
  uint uVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint *puVar7;
  
                    /* 0x29e0  22  CosUtil_SetChoreLength */
  if ((param_1 == 0) || (*(uint *)(param_1 + 0x30) <= param_2)) {
    (**(code **)(DAT_100143a8 + 0x18))(IMG_ADDR(0x10010364),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x6a3);
  }
  iVar5 = param_2 * 0x2c;
  iVar2 = *(int *)(param_1 + 0x34) + iVar5;
  if (param_3 <= *(uint *)(*(int *)(param_1 + 0x34) + 0x28 + iVar5)) {
    uVar4 = 0;
    if (*(int *)(iVar2 + 0x20) != 0) {
      puVar7 = (uint *)(*(int *)(iVar2 + 0x24) + 8);
      do {
        uVar1 = *puVar7;
        uVar6 = 0;
        if (uVar1 != 0) {
          puVar3 = (uint *)puVar7[1];
          do {
            if (*(uint *)(iVar2 + 0x28) < *puVar3) break;
            uVar6 = uVar6 + 1;
            puVar3 = puVar3 + 2;
          } while (uVar6 < uVar1);
        }
        if (uVar6 < uVar1) {
          uVar1 = (**(code **)(DAT_100143a8 + 0x28))
                            (puVar7[1],uVar6 * 8,s_C__grimsrc_libs_chore_Costume_c_1001020c,0x6b6);
          puVar7[1] = uVar1;
          *puVar7 = uVar6;
        }
        uVar4 = uVar4 + 1;
        puVar7 = puVar7 + 4;
        iVar2 = *(int *)(param_1 + 0x34) + iVar5;
      } while (uVar4 < *(uint *)(iVar2 + 0x20));
    }
  }
  *(uint *)(*(int *)(param_1 + 0x34) + 0x28 + iVar5) = param_3;
  return iVar2;
}

/* ---- 0x10002ab0  CosUtil_NameChore ---- */
undefined1 * __cdecl CosUtil_NameChore(int param_1,int param_2,char *param_3)

{
  char cVar1;
  undefined1 *puVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  char *pcVar8;
  
                    /* 0x2ab0  17  CosUtil_NameChore */
  if (param_1 == 0) {
    (**(code **)(DAT_100143a8 + 0x18))(IMG_ADDR(0x1001034c),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x6c6);
  }
  uVar3 = 0xffffffff;
  puVar2 = (undefined1 *)0x0;
  pcVar8 = param_3;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar8;
    pcVar8 = pcVar8 + 1;
  } while (cVar1 != '\0');
  iVar4 = ~uVar3 - 1;
  if (iVar4 < 0x20) {
    iVar7 = param_2 * 0x2c;
    FUN_100055a0(*(int *)(param_1 + 0x34) + iVar7,param_3,0x1f);
    puVar2 = *(undefined1 **)(param_1 + 0x34);
    iVar5 = 0;
    puVar2[iVar7 + 0x1f] = 0;
    if (0 < iVar4) {
      do {
        iVar6 = iVar5 + *(int *)(param_1 + 0x34);
        puVar2 = (undefined1 *)(iVar6 + iVar7);
        if (*(char *)(iVar6 + iVar7) == ' ') {
          *puVar2 = 0x5f;
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 < iVar4);
    }
  }
  return puVar2;
}

/* ---- 0x10002b40  CosUtil_DeleteKey ---- */
undefined4 CosUtil_DeleteKey(int param_1,uint param_2,uint param_3,int param_4)

{
  uint uVar1;
  uint uVar2;
  int *piVar3;
  uint *puVar4;
  
                    /* 0x2b40  16  CosUtil_DeleteKey */
  if (((param_1 == 0) || (*(uint *)(param_1 + 0x30) <= param_2)) ||
     (*(uint *)(param_1 + 0x28) <= param_3)) {
    (**(code **)(DAT_100143a8 + 0x18))(IMG_ADDR(0x100103b0),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x6e5);
  }
  puVar4 = *(uint **)(*(int *)(param_1 + 0x34) + 0x24 + param_2 * 0x2c);
  uVar1 = 0;
  uVar2 = *(uint *)(*(int *)(param_1 + 0x34) + param_2 * 0x2c + 0x20);
  if (uVar2 != 0) {
    do {
      if (*puVar4 == param_3) break;
      uVar1 = uVar1 + 1;
      puVar4 = puVar4 + 4;
    } while (uVar1 < uVar2);
  }
  if (uVar1 != uVar2) {
    piVar3 = (int *)puVar4[3];
    uVar2 = 0;
    if (puVar4[2] != 0) {
      do {
        if (*piVar3 == param_4) {
          FUN_10005860(piVar3,puVar4[3] + (uVar2 + 1) * 8,((uVar2 + 1) * 0x1fffffff + puVar4[2]) * 8
                      );
          uVar2 = puVar4[2] - 1;
          puVar4[2] = uVar2;
          if (uVar2 == 0) {
            (**(code **)(DAT_100143a8 + 0x24))(puVar4[3]);
            puVar4[3] = 0;
            return 1;
          }
          uVar2 = (**(code **)(DAT_100143a8 + 0x28))
                            (puVar4[3],uVar2 * 8,s_C__grimsrc_libs_chore_Costume_c_1001020c,0x704);
          puVar4[3] = uVar2;
          return 1;
        }
        uVar2 = uVar2 + 1;
        piVar3 = piVar3 + 2;
      } while (uVar2 < puVar4[2]);
      return 0;
    }
  }
  return 0;
}

/* ---- 0x10002c50  CosUtil_QueryValueAtTime ---- */
uint * CosUtil_QueryValueAtTime(int param_1,uint param_2,uint param_3,uint param_4)

{
  uint uVar1;
  uint *puVar2;
  uint uVar3;
  uint *puVar4;
  
                    /* 0x2c50  19  CosUtil_QueryValueAtTime */
  if (((param_1 == 0) || (*(uint *)(param_1 + 0x30) <= param_2)) ||
     (*(uint *)(param_1 + 0x28) <= param_3)) {
    (**(code **)(DAT_100143a8 + 0x18))(IMG_ADDR(0x100103b0),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x722);
  }
  puVar4 = *(uint **)(*(int *)(param_1 + 0x34) + 0x24 + param_2 * 0x2c);
  uVar3 = 0;
  uVar1 = *(uint *)(*(int *)(param_1 + 0x34) + param_2 * 0x2c + 0x20);
  if (uVar1 != 0) {
    do {
      if (*puVar4 == param_3) break;
      uVar3 = uVar3 + 1;
      puVar4 = puVar4 + 4;
    } while (uVar3 < uVar1);
  }
  if (uVar3 != uVar1) {
    puVar2 = (uint *)puVar4[3];
    uVar1 = puVar4[2];
    uVar3 = 0;
    puVar4 = puVar2;
    if (uVar1 != 0) {
      do {
        if (*puVar4 == param_4) {
          return puVar4;
        }
        if (param_4 <= *puVar4) {
          if (uVar3 == 0) {
            return (uint *)0x0;
          }
          return puVar2 + uVar3 * 2 + -2;
        }
        uVar3 = uVar3 + 1;
        puVar4 = puVar4 + 2;
      } while (uVar3 < uVar1);
    }
    if (uVar1 != 0) {
      return puVar2 + uVar1 * 2 + -2;
    }
  }
  return (uint *)0x0;
}

/* ---- 0x10002cf0  CosUtil_AddFSKey ---- */
undefined4
CosUtil_AddFSKey(int param_1,undefined4 param_2,int param_3,undefined4 param_4,undefined4 param_5)

{
  int iVar1;
  
                    /* 0x2cf0  3  CosUtil_AddFSKey */
  if (PTR_100143c0[*(int *)(*(int *)(param_1 + 0x2c) + 0x20 + param_3 * 0x40) * 0x17 + 1] != 0) {
    return 0;
  }
  iVar1 = FUN_10003c90(param_1,param_2,param_3,param_4);
  if (iVar1 == 0) {
    return 0;
  }
  *(undefined4 *)(iVar1 + 4) = param_5;
  return 1;
}

/* ---- 0x10002d50  CosUtil_AddIntKey ---- */
undefined4
CosUtil_AddIntKey(int param_1,undefined4 param_2,int param_3,undefined4 param_4,undefined4 param_5)

{
  int iVar1;
  
                    /* 0x2d50  5  CosUtil_AddIntKey */
  if (PTR_100143c0[*(int *)(*(int *)(param_1 + 0x2c) + 0x20 + param_3 * 0x40) * 0x17 + 1] != 1) {
    return 0;
  }
  iVar1 = FUN_10003c90(param_1,param_2,param_3,param_4);
  if (iVar1 == 0) {
    return 0;
  }
  *(undefined4 *)(iVar1 + 4) = param_5;
  return 1;
}

/* ---- 0x10002db0  CosUtil_AddFloatKey ---- */
undefined4
CosUtil_AddFloatKey(int param_1,undefined4 param_2,int param_3,undefined4 param_4,undefined4 param_5
                   )

{
  int iVar1;
  
                    /* 0x2db0  4  CosUtil_AddFloatKey */
  if (PTR_100143c0[*(int *)(*(int *)(param_1 + 0x2c) + 0x20 + param_3 * 0x40) * 0x17 + 1] != 2) {
    return 0;
  }
  iVar1 = FUN_10003c90(param_1,param_2,param_3,param_4);
  if (iVar1 == 0) {
    return 0;
  }
  *(undefined4 *)(iVar1 + 4) = param_5;
  return 1;
}

/* ---- 0x10002e10  CosUtil_CountComponents ---- */
undefined4 CosUtil_CountComponents(int param_1)

{
                    /* 0x2e10  12  CosUtil_CountComponents */
  if (param_1 == 0) {
    (**(code **)(DAT_100143a8 + 0x18))(IMG_ADDR(0x1001034c),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x789);
  }
  return *(undefined4 *)(param_1 + 0x28);
}

/* ---- 0x10002e40  CosUtil_ComponentInfo ---- */
void CosUtil_ComponentInfo
               (int param_1,uint param_2,int *param_3,undefined4 *param_4,undefined4 *param_5,
               int *param_6)

{
  int *piVar1;
  int iVar2;
  
                    /* 0x2e40  10  CosUtil_ComponentInfo */
  if (param_1 == 0) {
    (**(code **)(DAT_100143a8 + 0x18))(IMG_ADDR(0x1001034c),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x797);
  }
  if (*(uint *)(param_1 + 0x28) <= param_2) {
    (**(code **)(DAT_100143a8 + 0x18))(IMG_ADDR(0x10010444),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x798);
  }
  iVar2 = *(int *)(param_1 + 0x2c) + param_2 * 0x40;
  piVar1 = PTR_100143c0 + *(int *)(iVar2 + 0x20) * 0x17;
  if (param_3 != (int *)0x0) {
    *param_3 = *piVar1;
  }
  if (param_4 != (undefined4 *)0x0) {
    *param_4 = *(undefined4 *)(iVar2 + 0x24);
  }
  if (param_6 != (int *)0x0) {
    *param_6 = piVar1[1];
  }
  if (param_5 != (undefined4 *)0x0) {
    *param_5 = *(undefined4 *)(iVar2 + 0x2c);
  }
  return;
}

/* ---- 0x10002fa0  CosUtil_CountChores ---- */
undefined4 CosUtil_CountChores(int param_1)

{
                    /* 0x2fa0  11  CosUtil_CountChores */
  return *(undefined4 *)(param_1 + 0x30);
}

/* ---- 0x100030b0  CosUtil_ChoreName ---- */
int CosUtil_ChoreName(int param_1,uint param_2)

{
                    /* 0x30b0  7  CosUtil_ChoreName */
  if (*(uint *)(param_1 + 0x30) <= param_2) {
    (**(code **)(DAT_100143a8 + 0x18))(IMG_ADDR(0x10010498),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x80d);
  }
  return *(int *)(param_1 + 0x34) + param_2 * 0x2c;
}

/* ---- 0x100030f0  CosUtil_CountTags ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 CosUtil_CountTags(void)

{
                    /* 0x30f0  13  CosUtil_CountTags */
  return _DAT_100143b8;
}

/* ---- 0x10003100  CosUtil_TagInfo ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int * CosUtil_TagInfo(uint param_1,int *param_2)

{
                    /* 0x3100  23  CosUtil_TagInfo */
  if (_DAT_100143b8 <= param_1) {
    (**(code **)(DAT_100143a8 + 0x18))(IMG_ADDR(0x100104c8),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x81f);
  }
  if (param_2 != (int *)0x0) {
    *param_2 = PTR_100143c0[param_1 * 0x17];
  }
  return PTR_100143c0 + param_1 * 0x17 + 2;
}
