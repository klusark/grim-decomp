/* CHORE.DLL :: costume.c
 * functions 0x10001000 .. 0x10005f50 (85 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10001000  Cos_InstRescue ---- */
int __cdecl Cos_InstRescue(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
                    /* 0x1000  43  Cos_InstRescue */
  iVar2 = FUN_10005160(param_2);
  iVar3 = iVar2;
  if (-1 < iVar2) {
    iVar3 = FUN_100051a0(param_1);
    iVar1 = DAT_100143cc;
    if ((-1 < iVar3) && (iVar3 < DAT_100143c8)) {
      *(int *)(DAT_100143cc + iVar3 * 0x14) = iVar2;
      iVar3 = iVar1;
    }
  }
  return iVar3;
}

/* ---- 0x10001040  Cos_Free ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl Cos_Free(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
                    /* 0x1040  26  Cos_Free */
  iVar1 = FUN_10005160(param_1);
  iVar3 = 0;
  if (0 < DAT_100143c8) {
    iVar4 = 0;
    iVar2 = DAT_100143cc;
    do {
      if ((*(int *)(iVar2 + 0x10 + iVar4) == 0) && (*(int *)(iVar2 + iVar4) == iVar1)) {
        iVar2 = FUN_100051c0(iVar3);
        Cos_FreeCosInstance(iVar2);
        iVar2 = DAT_100143cc;
      }
      iVar3 = iVar3 + 1;
      iVar4 = iVar4 + 0x14;
    } while (iVar3 < DAT_100143c8);
  }
  FUN_10004c70(param_1);
  *(undefined4 *)(DAT_100143b4 + 0x38 + iVar1 * 0x3c) = 1;
  _DAT_100143ac = _DAT_100143ac + -1;
  return _DAT_100143ac;
}

/* ---- 0x100010d0  FUN_100010d0 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_100010d0(int param_1)

{
  FUN_100055a0(param_1,IMG_ADDR(0x10010030),0x1f);
  *(undefined1 *)(param_1 + 0x1f) = 0;
  *(int *)(param_1 + 0x24) = _DAT_100143f0;
  _DAT_100143f0 = _DAT_100143f0 + 1;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0;
  return;
}

/* ---- 0x100016a0  Cos_New ---- */
undefined4 Cos_New(void)

{
  int iVar1;
  undefined4 uVar2;
  
                    /* 0x16a0  53  Cos_New */
  iVar1 = FUN_10004e50();
  if (iVar1 < 0) {
    return 0;
  }
  FUN_100010d0(DAT_100143b4 + iVar1 * 0x3c);
  uVar2 = FUN_10005180(iVar1);
  return uVar2;
}

/* ---- 0x100016e0  Cos_Load ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 Cos_Load(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
                    /* 0x16e0  51  Cos_Load */
  iVar4 = 0;
  if (0 < _DAT_100143b0) {
    iVar3 = 0;
    do {
      if (*(int *)(DAT_100143b4 + iVar3 + 0x38) == 0) {
        iVar1 = FUN_10005740(param_1,DAT_100143b4 + iVar3);
        if (iVar1 == 0) {
          uVar2 = FUN_10005180(iVar4);
          return uVar2;
        }
      }
      iVar4 = iVar4 + 1;
      iVar3 = iVar3 + 0x3c;
    } while (iVar4 < _DAT_100143b0);
  }
  iVar4 = FUN_10004e50();
  if (iVar4 != -1) {
    uVar2 = FUN_10005180(iVar4);
    iVar3 = Cos_LoadEntry(param_1,uVar2);
    if (iVar3 != 0) {
      return uVar2;
    }
  }
  uVar2 = FUN_10005180(iVar4);
  FUN_10004c70(uVar2);
  return 0;
}

/* ---- 0x10001770  Cos_LoadEntry ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 Cos_LoadEntry(char *param_1,int param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char *pcVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  char *pcVar9;
  uint *puVar10;
  int unaff_retaddr;
  uint uStack00000010;
  #define auStack_8 (*(undefined1 (*)[4])(_frame + (0x20 - 0x8)))
  #define uStack_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
                    /* 0x1770  52  Cos_LoadEntry */
  iVar4 = CosUtil_PtrFromHandle(param_2);
  FUN_100010d0(iVar4);
  iVar5 = FUN_100056a0(param_1,0x5c);
  if (iVar5 == 0) {
    uVar7 = 0xffffffff;
    pcVar9 = param_1;
    do {
      pcVar1 = param_1;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      cVar2 = *pcVar9;
      pcVar9 = pcVar9 + 1;
    } while (cVar2 != '\0');
  }
  else {
    pcVar1 = (char *)(iVar5 + 1);
    uVar7 = 0xffffffff;
    pcVar9 = pcVar1;
    do {
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      cVar2 = *pcVar9;
      pcVar9 = pcVar9 + 1;
    } while (cVar2 != '\0');
  }
  iVar5 = param_2;
  if (~uVar7 - 1 < 0x21) {
    FUN_100055a0(iVar4,pcVar1,0x1f);
    *(undefined1 *)(iVar4 + 0x1f) = 0;
    iVar5 = (**(code **)(DAT_100143a8 + 0x30))(param_1,IMG_ADDR(0x10010280));
    if (iVar5 == 0) {
      *(undefined4 *)(iVar4 + 0x38) = 1;
      return 0;
    }
    _DAT_100143ec = 0;
    iVar6 = FUN_10004bb0(iVar5,IMG_ADDR(0x10013e10),0x400);
    if (iVar6 != 0) {
      FUN_10005810((char *)IMG_ADDR(0x10013e10),(char *)IMG_ADDR(0x10010270),&uStack_4,auStack_8);
      iVar6 = FUN_10004bb0(iVar5,IMG_ADDR(0x10013e10),0x400);
      if (((((((iVar6 != 0) &&
              (iVar6 = FUN_10005810((char *)IMG_ADDR(0x10013e10),(char *)IMG_ADDR(0x10010260)), iVar6 == 0)) &&
             (iVar6 = FUN_100041e0(iVar5,iVar4,param_1), iVar6 != 0)) &&
            ((iVar6 = FUN_10004bb0(iVar5,IMG_ADDR(0x10013e10),0x400), iVar6 != 0 &&
             (iVar6 = FUN_10005810((char *)IMG_ADDR(0x10013e10),(char *)IMG_ADDR(0x1001024c)), iVar6 == 0)))) &&
           ((iVar6 = ((code *)FUN_10004390)(iVar5,param_2,param_1), iVar6 != 0 &&
            ((iVar6 = FUN_10004bb0(iVar5,IMG_ADDR(0x10013e10),0x400), iVar6 != 0 &&
             (iVar6 = FUN_10005810((char *)IMG_ADDR(0x10013e10),(char *)IMG_ADDR(0x1001023c)), iVar6 == 0)))))) &&
          (iVar6 = FUN_100047f0(iVar5,iVar4,param_1), iVar6 != 0)) &&
         (((iVar6 = FUN_10004bb0(iVar5,IMG_ADDR(0x10013e10),0x400), iVar6 != 0 &&
           (iVar6 = FUN_10005810((char *)IMG_ADDR(0x10013e10),(char *)IMG_ADDR(0x1001022c)), iVar6 == 0)) &&
          ((*(int *)(iVar4 + 0x30) == 0 || (iVar6 = ((code *)FUN_10004970)(iVar5,iVar4,param_1), iVar6 != 0)))
          ))) {
        uVar7 = 0;
        if (*(int *)(iVar4 + 0x30) != 0) {
          puVar10 = (uint *)(*(int *)(iVar4 + 0x34) + 0x20);
          do {
            CosUtil_SetChoreLength(iVar4,uVar7,puVar10[2]);
            uVar3 = *puVar10;
            uStack00000010 = 0;
            if (uVar3 != 0) {
              iVar6 = 0;
              do {
                uVar7 = 0;
                if (uVar3 != 0) {
                  iVar8 = 0;
                  do {
                    if ((uStack00000010 != uVar7) &&
                       (iVar4 = unaff_retaddr,
                       *(int *)(puVar10[1] + iVar6) == *(int *)(puVar10[1] + iVar8)))
                    goto LAB_10001a10;
                    uVar7 = uVar7 + 1;
                    iVar8 = iVar8 + 0x10;
                  } while (uVar7 < uVar3);
                }
                uStack00000010 = uStack00000010 + 1;
                iVar6 = iVar6 + 0x10;
                uVar7 = uStack_4;
              } while (uStack00000010 < uVar3);
            }
            uVar7 = uVar7 + 1;
            puVar10 = puVar10 + 0xb;
            uStack_4 = uVar7;
          } while (uVar7 < *(uint *)(iVar4 + 0x30));
        }
        (**(code **)(DAT_100143a8 + 0x34))(iVar5);
        return 1;
      }
    }
  }
LAB_10001a10:
  *(undefined4 *)(iVar4 + 0x38) = 1;
  (**(code **)(DAT_100143a8 + 0x34))(iVar5);
  return 0;
}
#undef auStack_8
#undef uStack_4

#endif


/* ---- 0x10001a30  Cos_FreeCosInstance ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl Cos_FreeCosInstance(int param_1)

{
  int iVar1;
  
                    /* 0x1a30  27  Cos_FreeCosInstance */
  iVar1 = FUN_100051a0(param_1);
  if (_DAT_100143e0 != (code *)0x0) {
    (*_DAT_100143e0)(param_1,0);
  }
  FUN_10004f70(iVar1);
  *(undefined4 *)(DAT_100143cc + 0x10 + iVar1 * 0x14) = 1;
  _DAT_100143c4 = _DAT_100143c4 + -1;
  return _DAT_100143c4;
}

/* ---- 0x10001a80  Cos_CreateCosInstance ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int Cos_CreateCosInstance(uint *param_1,uint param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  int iVar2;
  code *pcVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int *piVar7;
  int iVar8;
  uint *puVar9;
  int iVar10;
  #define uStack_c (*(uint *)(_frame + (0x20 - 0xc)))
  
                    /* 0x1a80  25  Cos_CreateCosInstance */
  iVar4 = FUN_10005160(param_1);
  if ((iVar4 < 0) || (_DAT_100143b0 <= iVar4)) {
    return 0;
  }
  iVar8 = DAT_100143b4 + iVar4 * 0x3c;
  iVar5 = FUN_10005090();
  piVar1 = (int *)(DAT_100143cc + iVar5 * 0x14);
  *piVar1 = iVar4;
  if (*(int *)(iVar8 + 0x30) == 0) {
    piVar1[1] = 0;
  }
  else {
    iVar4 = (**(code **)(DAT_100143a8 + 0x20))
                      (*(int *)(iVar8 + 0x30) * 0xc,s_C__grimsrc_libs_chore_Costume_c_1001020c,0x347
                      );
    piVar1[1] = iVar4;
    if (iVar4 == 0) {
      (**(code **)(DAT_100143a8 + 0x18))
                (IMG_ADDR(0x100102cc),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x348);
    }
  }
  FUN_10004c40(*(undefined4 *)(iVar8 + 0x34),piVar1[1],*(undefined4 *)(iVar8 + 0x30));
  if (*(int *)(iVar8 + 0x28) == 0) {
    piVar1[3] = 0;
  }
  else {
    iVar4 = (**(code **)(DAT_100143a8 + 0x20))
                      (*(int *)(iVar8 + 0x28) * 4,s_C__grimsrc_libs_chore_Costume_c_1001020c,0x354);
    piVar1[3] = iVar4;
    if (iVar4 == 0) {
      (**(code **)(DAT_100143a8 + 0x18))
                (IMG_ADDR(0x100102a4),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x355);
    }
    uVar6 = 0;
    if (*(int *)(iVar8 + 0x28) != 0) {
      iVar4 = 0;
      do {
        uVar6 = uVar6 + 1;
        iVar2 = iVar4 + 0x24;
        iVar4 = iVar4 + 0x40;
        *(undefined4 *)(piVar1[3] + -4 + uVar6 * 4) =
             *(undefined4 *)(iVar2 + *(int *)(iVar8 + 0x2c));
      } while (uVar6 < *(uint *)(iVar8 + 0x28));
    }
  }
  piVar1[2] = param_2;
  iVar4 = FUN_100051c0(iVar5);
  uVar6 = 0;
  if (*(int *)(iVar8 + 0x28) == 0) {
    param_1 = (uint *)0x0;
  }
  else {
    param_1 = (uint *)(**(code **)(DAT_100143a8 + 0x20))
                                (*(int *)(iVar8 + 0x28) * 4,
                                 s_C__grimsrc_libs_chore_Costume_c_1001020c,0x369);
    if (param_1 == (uint *)0x0) {
      (**(code **)(DAT_100143a8 + 0x18))
                (IMG_ADDR(0x10010288),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x36a);
    }
  }
  uStack_c = 0;
  if (*(int *)(iVar8 + 0x28) != 0) {
    piVar7 = (int *)(*(int *)(iVar8 + 0x2c) + 0x2c);
    puVar9 = param_1;
    do {
      iVar5 = *piVar7;
      *puVar9 = 0;
      while (iVar5 != -1) {
        iVar5 = *(int *)(iVar5 * 0x40 + 0x2c + *(int *)(iVar8 + 0x2c));
        *puVar9 = *puVar9 + 1;
      }
      if (uStack_c <= *puVar9) {
        uStack_c = *puVar9;
      }
      uVar6 = uVar6 + 1;
      puVar9 = puVar9 + 1;
      piVar7 = piVar7 + 0x10;
    } while (uVar6 < *(uint *)(iVar8 + 0x28));
  }
  param_2 = 0;
  do {
    uVar6 = 0;
    if (*(int *)(iVar8 + 0x28) != 0) {
      piVar7 = (int *)(*(int *)(iVar8 + 0x2c) + 0x20);
      do {
        if (param_1[uVar6] == param_2) {
          iVar5 = *piVar7;
          iVar10 = 0;
          iVar2 = PTR_100143c0[iVar5 * 0x17 + 1];
          if (iVar2 == 0) {
            pcVar3 = (code *)PTR_100143c0[iVar5 * 0x17 + 0x10];
joined_r0x10001cd0:
            if (pcVar3 != (code *)0x0) {
              iVar10 = (*pcVar3)(iVar4,uVar6,1);
            }
          }
          else {
            if ((iVar2 == 1) || (iVar2 == 2)) {
              pcVar3 = (code *)PTR_100143c0[iVar5 * 0x17 + 0x10];
              goto joined_r0x10001cd0;
            }
            (**(code **)(DAT_100143a8 + 0x18))
                      (&DAT_10010284,s_C__grimsrc_libs_chore_Costume_c_1001020c,0x3a3);
          }
          if (iVar10 != 0) {
            *(int *)(piVar1[3] + uVar6 * 4) = iVar10;
          }
        }
        uVar6 = uVar6 + 1;
        piVar7 = piVar7 + 0x10;
      } while (uVar6 < *(uint *)(iVar8 + 0x28));
    }
    param_2 = param_2 + 1;
    if (uStack_c < param_2) {
      (**(code **)(DAT_100143a8 + 0x24))(param_1);
      if (_DAT_100143e0 == (code *)0x0) {
        piVar1[2] = 0;
      }
      else {
        iVar8 = (*_DAT_100143e0)(iVar4,1);
        if (iVar8 == 0) {
          Cos_FreeCosInstance(iVar4);
          return 0;
        }
      }
      return iVar4;
    }
  } while( true );
}
#undef uStack_c


/* ---- 0x10001d70  Cos_InstGetInstanceData ---- */
undefined4 Cos_InstGetInstanceData(int param_1,int param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  
                    /* 0x1d70  38  Cos_InstGetInstanceData */
  iVar2 = FUN_100051a0(param_1);
  if (((-1 < iVar2) && (iVar2 < DAT_100143c8)) && (-1 < param_2)) {
    iVar1 = DAT_100143b4 + *(int *)(DAT_100143cc + iVar2 * 0x14) * 0x3c;
    if (param_2 < *(int *)(iVar1 + 0x28)) {
      if (param_3 != (int *)0x0) {
        *param_3 = PTR_100143c0[*(int *)(param_2 * 0x40 + 0x20 + *(int *)(iVar1 + 0x2c)) * 0x17];
      }
      return *(undefined4 *)(*(int *)(DAT_100143cc + 0xc + iVar2 * 0x14) + param_2 * 4);
    }
  }
  return 0;
}

/* ---- 0x10001e00  Cos_RegisterInstanceHook ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 Cos_RegisterInstanceHook(undefined4 param_1)

{
  undefined4 uVar1;
  
                    /* 0x1e00  58  Cos_RegisterInstanceHook */
  uVar1 = _DAT_100143e0;
  _DAT_100143e0 = param_1;
  return uVar1;
}

/* ---- 0x10001e10  Cos_RegisterSaveHook ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 Cos_RegisterSaveHook(undefined4 param_1)

{
  undefined4 uVar1;
  
                    /* 0x1e10  59  Cos_RegisterSaveHook */
  uVar1 = _DAT_100143e4;
  _DAT_100143e4 = param_1;
  return uVar1;
}

/* ---- 0x10001e20  Cos_InstGetUserData ---- */
undefined4 Cos_InstGetUserData(int param_1)

{
  int iVar1;
  
                    /* 0x1e20  39  Cos_InstGetUserData */
  iVar1 = FUN_100051a0(param_1);
  if ((-1 < iVar1) && (iVar1 < DAT_100143c8)) {
    return *(undefined4 *)(DAT_100143cc + 8 + iVar1 * 0x14);
  }
  return 0;
}

/* ---- 0x10001e50  Cos_InstSetUserData ---- */
int __cdecl Cos_InstSetUserData(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
                    /* 0x1e50  46  Cos_InstSetUserData */
  iVar2 = FUN_100051a0(param_1);
  iVar1 = DAT_100143cc;
  if ((-1 < iVar2) && (iVar2 < DAT_100143c8)) {
    *(undefined4 *)(DAT_100143cc + 8 + iVar2 * 0x14) = param_2;
    iVar2 = iVar1;
  }
  return iVar2;
}

/* ---- 0x10001e80  Cos_NewStateBasedTag ---- */
undefined4
Cos_NewStateBasedTag
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4,int param_5)

{
  int iVar1;
  undefined4 *puVar2;
  
                    /* 0x1e80  56  Cos_NewStateBasedTag */
  iVar1 = FUN_10001ed0(&param_5,param_1,param_2,param_3,param_5);
  if (iVar1 != 0) {
    *(undefined4 *)(param_5 + 4) = 0;
    puVar2 = (undefined4 *)(param_5 + 0x2c);
    for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = *param_4;
      param_4 = param_4 + 1;
      puVar2 = puVar2 + 1;
    }
    return 1;
  }
  return 0;
}

/* ---- 0x10001ed0  FUN_10001ed0 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
FUN_10001ed0(int *param_1,int param_2,char *param_3,undefined4 param_4,undefined4 param_5)

{
  char cVar1;
  uint uVar2;
  int *piVar3;
  char *pcVar4;
  
  uVar2 = 0;
  piVar3 = PTR_100143c0;
  if (_DAT_100143b8 != 0) {
    do {
      if (*piVar3 == param_2) {
        return 0;
      }
      uVar2 = uVar2 + 1;
      piVar3 = piVar3 + 0x17;
    } while (uVar2 < _DAT_100143b8);
  }
  uVar2 = 0xffffffff;
  pcVar4 = param_3;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  if (0x1f < ~uVar2 - 1) {
    return 0;
  }
  uVar2 = FUN_10004f30();
  if (_DAT_100143b8 <= uVar2) {
    (**(code **)(DAT_100143a8 + 0x18))(IMG_ADDR(0x100102f8),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x420);
  }
  piVar3 = PTR_100143c0 + uVar2 * 0x17;
  *param_1 = (int)piVar3;
  FUN_100055a0(piVar3 + 2,param_3,0x1f);
  *(undefined1 *)(*param_1 + 0x27) = 0;
  *(int *)*param_1 = param_2;
  *(undefined4 *)(*param_1 + 0x28) = param_5;
  return 1;
}

/* ---- 0x10001f80  Cos_NewIntTag ---- */
undefined4
Cos_NewIntTag(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4,
             int param_5)

{
  int iVar1;
  undefined4 *puVar2;
  
                    /* 0x1f80  55  Cos_NewIntTag */
  iVar1 = FUN_10001ed0(&param_5,param_1,param_2,param_3,param_5);
  if (iVar1 != 0) {
    *(undefined4 *)(param_5 + 4) = 1;
    puVar2 = (undefined4 *)(param_5 + 0x2c);
    for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = *param_4;
      param_4 = param_4 + 1;
      puVar2 = puVar2 + 1;
    }
    return 1;
  }
  return 0;
}

/* ---- 0x10001fd0  Cos_NewFloatTag ---- */
undefined4
Cos_NewFloatTag(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4,
               int param_5)

{
  int iVar1;
  undefined4 *puVar2;
  
                    /* 0x1fd0  54  Cos_NewFloatTag */
  iVar1 = FUN_10001ed0(&param_5,param_1,param_2,param_3,param_5);
  if (iVar1 != 0) {
    *(undefined4 *)(param_5 + 4) = 2;
    puVar2 = (undefined4 *)(param_5 + 0x2c);
    for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = *param_4;
      param_4 = param_4 + 1;
      puVar2 = puVar2 + 1;
    }
    return 1;
  }
  return 0;
}

/* ---- 0x10002080  Cos_RegisterComponent ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
Cos_RegisterComponent
          (uint param_1,int param_2,undefined4 param_3,int param_4,int param_5,int param_6,
          undefined4 param_7)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  
                    /* 0x2080  57  Cos_RegisterComponent */
  iVar1 = FUN_10005160(param_1);
  if (param_2 == 0) {
    return 0;
  }
  iVar1 = DAT_100143b4 + iVar1 * 0x3c;
  if (param_5 != 0) {
    uVar2 = 0;
    piVar3 = PTR_100143c0;
    if (_DAT_100143b8 != 0) {
      do {
        if (*piVar3 == param_6) break;
        uVar2 = uVar2 + 1;
        piVar3 = piVar3 + 0x17;
      } while (uVar2 < _DAT_100143b8);
    }
    if (uVar2 == _DAT_100143b8) {
      return 0;
    }
    uVar2 = *(uint *)(iVar1 + 0x28);
    param_1 = 0;
    if (uVar2 != 0) {
      piVar3 = (int *)(*(int *)(iVar1 + 0x2c) + 0x24);
      do {
        if ((PTR_100143c0[piVar3[-1] * 0x17] == param_6) && (*piVar3 == param_5)) break;
        piVar3 = piVar3 + 0x10;
        param_1 = param_1 + 1;
      } while (param_1 < uVar2);
    }
    if (param_1 == uVar2) {
      return 0;
    }
  }
  uVar2 = 0;
  piVar3 = PTR_100143c0;
  if (_DAT_100143b8 != 0) {
    do {
      if (*piVar3 == param_4) break;
      uVar2 = uVar2 + 1;
      piVar3 = piVar3 + 0x17;
    } while (uVar2 < _DAT_100143b8);
  }
  if (uVar2 != _DAT_100143b8) {
    iVar4 = (**(code **)(DAT_100143a8 + 0x28))
                      (*(undefined4 *)(iVar1 + 0x2c),(*(int *)(iVar1 + 0x28) + 1) * 0x40,
                       s_C__grimsrc_libs_chore_Costume_c_1001020c,0x4ef);
    *(int *)(iVar1 + 0x2c) = iVar4;
    iVar4 = *(int *)(iVar1 + 0x28) * 0x40 + iVar4;
    if (param_5 == 0) {
      param_1 = 0xffffffff;
    }
    FUN_10004090(iVar1,iVar4,param_2,uVar2,param_3,param_1);
    *(int *)(iVar1 + 0x28) = *(int *)(iVar1 + 0x28) + 1;
    FUN_10003e70(iVar4,param_7);
    if (_DAT_100143d8 != (code *)0x0) {
      (*_DAT_100143d8)(iVar1,iVar4,*(int *)(iVar1 + 0x28) + -1,1);
    }
    return 1;
  }
  return 0;
}

/* ---- 0x100021f0  Cos_RemoveComponent ---- */
int __cdecl Cos_RemoveComponent(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  
                    /* 0x21f0  61  Cos_RemoveComponent */
  iVar1 = CosUtil_PtrFromHandle(param_1);
  if (iVar1 != 0) {
    uVar4 = 0;
    if (*(uint *)(iVar1 + 0x28) != 0) {
      piVar3 = (int *)(*(int *)(iVar1 + 0x2c) + 0x20);
      while ((iVar2 = piVar3[1], iVar2 != param_3 ||
             (iVar2 = *piVar3, PTR_100143c0[iVar2 * 0x17] != param_2))) {
        uVar4 = uVar4 + 1;
        piVar3 = piVar3 + 0x10;
        if (*(uint *)(iVar1 + 0x28) <= uVar4) {
          return iVar2;
        }
      }
      iVar1 = CosUtil_DeleteComponent(param_1,uVar4);
    }
  }
  return iVar1;
}

/* ---- 0x10002ee0  Cos_InstCountComponents ---- */
undefined4 Cos_InstCountComponents(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
                    /* 0x2ee0  36  Cos_InstCountComponents */
  iVar1 = FUN_100051a0(param_1);
  if (iVar1 < 0) {
    return 0;
  }
  uVar2 = CosUtil_CountComponents(DAT_100143b4 + *(int *)(DAT_100143cc + iVar1 * 0x14) * 0x3c);
  return uVar2;
}

/* ---- 0x10002f20  Cos_InstComponentInfo ---- */
void Cos_InstComponentInfo
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5)

{
  int iVar1;
  
                    /* 0x2f20  34  Cos_InstComponentInfo */
  iVar1 = FUN_100051a0(param_1);
  CosUtil_ComponentInfo
            (DAT_100143b4 + *(int *)(DAT_100143cc + iVar1 * 0x14) * 0x3c,param_2,param_3,param_4,
             param_5,0);
  return;
}

/* ---- 0x10002f70  Cos_InstCountChores ---- */
undefined4 Cos_InstCountChores(int param_1)

{
  int iVar1;
  
                    /* 0x2f70  35  Cos_InstCountChores */
  iVar1 = FUN_100051a0(param_1);
  return *(undefined4 *)(DAT_100143b4 + 0x30 + *(int *)(DAT_100143cc + iVar1 * 0x14) * 0x3c);
}

/* ---- 0x10002fb0  Cos_GetCostumeName ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int Cos_GetCostumeName(undefined4 param_1)

{
  int iVar1;
  
                    /* 0x2fb0  28  Cos_GetCostumeName */
  iVar1 = FUN_10005160(param_1);
  if ((iVar1 < 0) || (_DAT_100143b0 <= iVar1)) {
    (**(code **)(DAT_100143a8 + 0x18))(IMG_ADDR(0x10010468),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x7eb);
  }
  return DAT_100143b4 + iVar1 * 0x3c;
}

/* ---- 0x10003000  Cos_InstGetCostume ---- */
int Cos_InstGetCostume(int param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
                    /* 0x3000  37  Cos_InstGetCostume */
  iVar2 = FUN_100051a0(param_1);
  iVar1 = *(int *)(DAT_100143cc + iVar2 * 0x14);
  iVar2 = DAT_100143b4 + iVar1 * 0x3c;
  if (param_2 != (undefined4 *)0x0) {
    uVar3 = FUN_10005180(iVar1);
    *param_2 = uVar3;
  }
  return iVar2;
}

/* ---- 0x10003050  Cos_InstChoreName ---- */
int Cos_InstChoreName(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  
                    /* 0x3050  30  Cos_InstChoreName */
  iVar2 = FUN_100051a0(param_1);
  iVar1 = *(int *)(DAT_100143cc + iVar2 * 0x14);
  iVar2 = DAT_100143b4 + iVar1 * 0x3c;
  if (*(uint *)(DAT_100143b4 + 0x30 + iVar1 * 0x3c) <= param_2) {
    (**(code **)(DAT_100143a8 + 0x18))(IMG_ADDR(0x10010498),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x802);
  }
  return *(int *)(iVar2 + 0x34) + param_2 * 0x2c;
}

/* ---- 0x10003160  Cos_InstStopChores ---- */
undefined4 Cos_InstStopChores(uint param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  uint uVar6;
  int iVar7;
  
                    /* 0x3160  48  Cos_InstStopChores */
  iVar4 = FUN_100051a0(param_1);
  param_1 = 0;
  iVar2 = *(int *)(DAT_100143cc + iVar4 * 0x14);
  iVar4 = DAT_100143cc + iVar4 * 0x14;
  puVar5 = *(undefined4 **)(iVar4 + 4);
  iVar1 = DAT_100143b4 + iVar2 * 0x3c;
  if (*(int *)(DAT_100143b4 + 0x30 + iVar2 * 0x3c) != 0) {
    do {
      iVar7 = 0;
      *puVar5 = 0;
      puVar5[2] = 0;
      uVar6 = 0;
      iVar2 = *(int *)(iVar1 + 0x34) + puVar5[1] * 0x2c;
      if (*(int *)(*(int *)(iVar1 + 0x34) + 0x20 + puVar5[1] * 0x2c) != 0) {
        do {
          iVar3 = *(int *)(*(int *)(iVar2 + 0x24) + iVar7);
          if ((code *)PTR_100143c0
                      [*(int *)(iVar3 * 0x40 + 0x20 + *(int *)(iVar1 + 0x2c)) * 0x17 + 0xe] !=
              (code *)0x0) {
            (*(code *)PTR_100143c0
                      [*(int *)(iVar3 * 0x40 + 0x20 + *(int *)(iVar1 + 0x2c)) * 0x17 + 0xe])
                      (*(undefined4 *)(*(int *)(iVar4 + 0xc) + iVar3 * 4));
          }
          uVar6 = uVar6 + 1;
          iVar7 = iVar7 + 0x10;
        } while (uVar6 < *(uint *)(iVar2 + 0x20));
      }
      param_1 = param_1 + 1;
      puVar5 = puVar5 + 3;
    } while (param_1 < *(uint *)(iVar1 + 0x30));
  }
  return 1;
}

/* ---- 0x10003240  Cos_InstStopChore ---- */
undefined4 Cos_InstStopChore(int param_1,uint param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
                    /* 0x3240  47  Cos_InstStopChore */
  iVar5 = FUN_100051a0(param_1);
  iVar1 = DAT_100143cc + iVar5 * 0x14;
  iVar5 = DAT_100143b4 + *(int *)(DAT_100143cc + iVar5 * 0x14) * 0x3c;
  if (param_2 < *(uint *)(iVar5 + 0x30)) {
    iVar7 = 0;
    puVar2 = (undefined4 *)(*(int *)(iVar1 + 4) + param_2 * 0xc);
    iVar6 = 0;
    *puVar2 = 0;
    puVar2[2] = 0;
    iVar3 = *(int *)(iVar5 + 0x34) + puVar2[1] * 0x2c;
    if (0 < *(int *)(*(int *)(iVar5 + 0x34) + 0x20 + puVar2[1] * 0x2c)) {
      do {
        iVar4 = *(int *)(*(int *)(iVar3 + 0x24) + iVar7);
        if ((code *)PTR_100143c0
                    [*(int *)(iVar4 * 0x40 + 0x20 + *(int *)(iVar5 + 0x2c)) * 0x17 + 0xe] !=
            (code *)0x0) {
          (*(code *)PTR_100143c0
                    [*(int *)(iVar4 * 0x40 + 0x20 + *(int *)(iVar5 + 0x2c)) * 0x17 + 0xe])
                    (*(undefined4 *)(*(int *)(iVar1 + 0xc) + iVar4 * 4));
        }
        iVar6 = iVar6 + 1;
        iVar7 = iVar7 + 0x10;
      } while (iVar6 < *(int *)(iVar3 + 0x20));
    }
    return 1;
  }
  return 0;
}

/* ---- 0x10003300  Cos_InstPauseChores ---- */
undefined4 Cos_InstPauseChores(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint *puVar4;
  uint uVar5;
  
                    /* 0x3300  41  Cos_InstPauseChores */
  iVar3 = FUN_100051a0(param_1);
  piVar1 = (int *)(DAT_100143cc + iVar3 * 0x14);
  iVar2 = *piVar1;
  iVar3 = DAT_100143b4 + iVar2 * 0x3c;
  uVar5 = 0;
  puVar4 = (uint *)piVar1[1];
  if (*(int *)(DAT_100143b4 + 0x30 + iVar2 * 0x3c) != 0) {
    do {
      uVar5 = uVar5 + 1;
      *puVar4 = *puVar4 & 0xfffffffe;
      puVar4 = puVar4 + 3;
    } while (uVar5 < *(uint *)(iVar3 + 0x30));
  }
  return 1;
}

/* ---- 0x10003360  Cos_InstPauseChore ---- */
undefined4 Cos_InstPauseChore(int param_1,uint param_2)

{
  uint *puVar1;
  int iVar2;
  
                    /* 0x3360  40  Cos_InstPauseChore */
  iVar2 = FUN_100051a0(param_1);
  if (param_2 < *(uint *)(DAT_100143b4 + 0x30 + *(int *)(DAT_100143cc + iVar2 * 0x14) * 0x3c)) {
    puVar1 = (uint *)(*(int *)(DAT_100143cc + iVar2 * 0x14 + 4) + param_2 * 0xc);
    *puVar1 = *puVar1 & 0xfffffffe;
    return 1;
  }
  return 0;
}

/* ---- 0x100033b0  Cos_InstCompleteChore ---- */
undefined4 Cos_InstCompleteChore(int param_1,uint param_2)

{
  int *piVar1;
  int iVar2;
  
                    /* 0x33b0  32  Cos_InstCompleteChore */
  iVar2 = FUN_100051a0(param_1);
  piVar1 = (int *)(DAT_100143cc + iVar2 * 0x14);
  iVar2 = DAT_100143b4 + *piVar1 * 0x3c;
  if (param_2 < *(uint *)(iVar2 + 0x30)) {
    *(undefined4 *)(piVar1[1] + param_2 * 0xc) = 1;
    Chore_AdvanceTime(iVar2,(int)piVar1,param_2,
                      *(int *)(*(int *)(iVar2 + 0x34) + 0x28 + param_2 * 0x2c) -
                      *(int *)(piVar1[1] + 8 + param_2 * 0xc),param_1);
    return 1;
  }
  return 0;
}

/* ---- 0x10003430  Cos_InstCompleteChores ---- */
undefined4 Cos_InstCompleteChores(int param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;
  uint uVar6;
  #define iStack_4 (*(int *)(_frame + (0x20 - 0x4)))
  
                    /* 0x3430  33  Cos_InstCompleteChores */
  iVar3 = FUN_100051a0(param_1);
  iVar5 = 0;
  iVar2 = *(int *)(DAT_100143cc + iVar3 * 0x14);
  iVar3 = DAT_100143cc + iVar3 * 0x14;
  uVar6 = 0;
  iVar1 = DAT_100143b4 + iVar2 * 0x3c;
  if (*(int *)(DAT_100143b4 + 0x30 + iVar2 * 0x3c) != 0) {
    iStack_4 = 0;
    do {
      pbVar4 = (byte *)(iStack_4 + *(int *)(iVar3 + 4));
      if ((*pbVar4 & 1) != 0) {
        Chore_AdvanceTime(iVar1,iVar3,uVar6,
                          *(int *)(*(int *)(iVar1 + 0x34) + 0x28 + iVar5) - *(int *)(pbVar4 + 8),
                          param_1);
      }
      uVar6 = uVar6 + 1;
      iVar5 = iVar5 + 0x2c;
      iStack_4 = iStack_4 + 0xc;
    } while (uVar6 < *(uint *)(iVar1 + 0x30));
  }
  return 1;
}
#undef iStack_4


/* ---- 0x100034c0  Cos_InstPlayChore ---- */
undefined4 __cdecl Cos_InstPlayChore(int param_1,uint param_2,int param_3,int param_4)

{
  uint *puVar1;
  int iVar2;
  
                    /* 0x34c0  42  Cos_InstPlayChore */
  iVar2 = FUN_100051a0(param_1);
  if (param_2 < *(uint *)(DAT_100143b4 + 0x30 + *(int *)(DAT_100143cc + iVar2 * 0x14) * 0x3c)) {
    puVar1 = (uint *)(*(int *)(DAT_100143cc + iVar2 * 0x14 + 4) + param_2 * 0xc);
    *puVar1 = 1;
    if (param_3 != 0) {
      *puVar1 = 3;
    }
    if (param_4 == 0) {
      *puVar1 = *puVar1 | 4;
    }
    return 1;
  }
  return 0;
}

/* ---- 0x10003530  Cos_InstUpdateChore ---- */
undefined4 __cdecl Cos_InstUpdateChore(int param_1,uint param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  
                    /* 0x3530  49  Cos_InstUpdateChore */
  iVar2 = FUN_100051a0(param_1);
  piVar1 = (int *)(DAT_100143cc + iVar2 * 0x14);
  if (param_2 < *(uint *)(DAT_100143b4 + 0x30 + *piVar1 * 0x3c)) {
    if ((*(byte *)(piVar1[1] + param_2 * 0xc) & 1) != 0) {
      Chore_AdvanceTime(DAT_100143b4 + *piVar1 * 0x3c,(int)piVar1,param_2,param_3,param_1);
    }
    return 1;
  }
  return 0;
}

/* ---- 0x100035a0  Cos_InstUpdateChores ---- */
undefined4 Cos_InstUpdateChores(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint *puVar4;
  uint uVar5;
  
                    /* 0x35a0  50  Cos_InstUpdateChores */
  iVar3 = FUN_100051a0(param_1);
  uVar5 = 0;
  iVar2 = *(int *)(DAT_100143cc + iVar3 * 0x14);
  iVar3 = DAT_100143cc + iVar3 * 0x14;
  puVar4 = *(uint **)(iVar3 + 4);
  iVar1 = DAT_100143b4 + iVar2 * 0x3c;
  if (*(int *)(DAT_100143b4 + 0x30 + iVar2 * 0x3c) != 0) {
    do {
      if (((*puVar4 & 1) != 0) && ((*puVar4 & 4) != 0)) {
        Chore_AdvanceTime(iVar1,iVar3,uVar5,param_2,param_1);
      }
      uVar5 = uVar5 + 1;
      puVar4 = puVar4 + 3;
    } while (uVar5 < *(uint *)(iVar1 + 0x30));
  }
  return 1;
}

/* ---- 0x10003620  Cos_InstSetChoreLoop ---- */
undefined4 Cos_InstSetChoreLoop(int param_1,uint param_2,int param_3)

{
  uint *puVar1;
  int iVar2;
  
                    /* 0x3620  45  Cos_InstSetChoreLoop */
  iVar2 = FUN_100051a0(param_1);
  if (*(uint *)(DAT_100143b4 + 0x30 + *(int *)(DAT_100143cc + iVar2 * 0x14) * 0x3c) <= param_2) {
    return 0;
  }
  puVar1 = (uint *)(*(int *)(DAT_100143cc + iVar2 * 0x14 + 4) + param_2 * 0xc);
  if (param_3 != 0) {
    *puVar1 = *puVar1 | 2;
    return 1;
  }
  *puVar1 = *puVar1 & 0xfffffffd;
  return 1;
}

/* ---- 0x10003690  Cos_InstSetChoreAdv ---- */
undefined4 Cos_InstSetChoreAdv(int param_1,uint param_2,int param_3)

{
  uint *puVar1;
  int iVar2;
  
                    /* 0x3690  44  Cos_InstSetChoreAdv */
  iVar2 = FUN_100051a0(param_1);
  if (*(uint *)(DAT_100143b4 + 0x30 + *(int *)(DAT_100143cc + iVar2 * 0x14) * 0x3c) <= param_2) {
    return 0;
  }
  puVar1 = (uint *)(*(int *)(DAT_100143cc + iVar2 * 0x14 + 4) + param_2 * 0xc);
  if (param_3 != 0) {
    *puVar1 = *puVar1 & 0xfffffffb;
    return 1;
  }
  *puVar1 = *puVar1 | 4;
  return 1;
}

/* ---- 0x10003700  Cos_InstChoreStatus ---- */
undefined4 Cos_InstChoreStatus(int param_1,uint param_2)

{
  int iVar1;
  
                    /* 0x3700  31  Cos_InstChoreStatus */
  iVar1 = FUN_100051a0(param_1);
  if (param_2 < *(uint *)(DAT_100143b4 + 0x30 + *(int *)(DAT_100143cc + iVar1 * 0x14) * 0x3c)) {
    return *(undefined4 *)(*(int *)(DAT_100143cc + iVar1 * 0x14 + 4) + param_2 * 0xc);
  }
  return 0;
}

/* ---- 0x10003750  Cos_Initialize ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 Cos_Initialize(undefined4 param_1,undefined4 *param_2)

{
                    /* 0x3750  29  Cos_Initialize */
  DAT_100143a8 = param_1;
  *param_2 = Cos_Initialize;
  param_2[1] = FUN_100051e0;
  param_2[2] = FUN_10005200;
  param_2[3] = FUN_10005350;
  param_2[4] = Cos_Save;
  param_2[5] = Cos_Restore;
  param_2[6] = 0;
  param_2[7] = 0;
  _DAT_100143a0 = 1;
  return 0;
}

/* ---- 0x100037a0  Cos_Save ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 Cos_Save(code *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  code *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  #define iStack_4 (*(int *)(_frame + (0x20 - 0x4)))
  
                    /* 0x37a0  64  Cos_Save */
  pcVar1 = param_1;
  iStack_4 = 0;
  (*param_1)(&DAT_100143b0,4);
  iVar4 = 0;
  if (0 < _DAT_100143b0) {
    iVar3 = 0;
    do {
      if (*(int *)(DAT_100143b4 + iVar3 + 0x38) == 0) {
        if (_DAT_100143e8 != (code *)0x0) {
          iVar2 = (*_DAT_100143e8)(DAT_100143b4 + iVar3);
          if (iVar2 == 0) goto LAB_100037ef;
        }
        iStack_4 = iStack_4 + 1;
      }
LAB_100037ef:
      iVar4 = iVar4 + 1;
      iVar3 = iVar3 + 0x3c;
    } while (iVar4 < _DAT_100143b0);
  }
  (*pcVar1)(&iStack_4,4);
  iVar4 = 0;
  if (0 < _DAT_100143b0) {
    iVar3 = 0;
    do {
      if (*(int *)(DAT_100143b4 + 0x38 + iVar3) == 0) {
        if (_DAT_100143e8 != (code *)0x0) {
          iVar2 = (*_DAT_100143e8)(DAT_100143b4 + iVar3);
          if (iVar2 == 0) goto LAB_10003863;
        }
        param_1 = (code *)FUN_10005180(iVar4);
        (*pcVar1)(&param_1,4);
        (*pcVar1)(DAT_100143b4 + iVar3,0x20);
      }
LAB_10003863:
      iVar4 = iVar4 + 1;
      iVar3 = iVar3 + 0x3c;
    } while (iVar4 < _DAT_100143b0);
  }
  (*pcVar1)(&DAT_100143c8,4);
  return 0;
}
#undef iStack_4


/* ---- 0x10003890  Cos_SaveInstance ---- */
undefined4 Cos_SaveInstance(int param_1,code *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
                    /* 0x3890  65  Cos_SaveInstance */
  iVar2 = FUN_100051a0(param_1);
  iVar3 = *(int *)(DAT_100143cc + iVar2 * 0x14);
  iVar2 = DAT_100143cc + iVar2 * 0x14;
  iVar4 = 0;
  iVar1 = DAT_100143b4 + iVar3 * 0x3c;
  if (0 < *(int *)(DAT_100143b4 + 0x28 + iVar3 * 0x3c)) {
    iVar3 = 0;
    do {
      if ((code *)PTR_100143c0[*(int *)(*(int *)(iVar1 + 0x2c) + 0x20 + iVar3) * 0x17 + 0x11] !=
          (code *)0x0) {
        (*(code *)PTR_100143c0[*(int *)(*(int *)(iVar1 + 0x2c) + 0x20 + iVar3) * 0x17 + 0x11])
                  (param_1,iVar4,1,*(undefined4 *)(*(int *)(iVar2 + 0xc) + iVar4 * 4),param_2);
      }
      iVar4 = iVar4 + 1;
      iVar3 = iVar3 + 0x40;
    } while (iVar4 < *(int *)(iVar1 + 0x28));
  }
  iVar3 = 0;
  if (0 < *(int *)(iVar1 + 0x30)) {
    param_1 = 0;
    do {
      iVar4 = *(int *)(iVar2 + 4) + param_1;
      (*param_2)(iVar4,4);
      (*param_2)(iVar4 + 4,4);
      (*param_2)(iVar4 + 8,4);
      iVar3 = iVar3 + 1;
      param_1 = param_1 + 0xc;
    } while (iVar3 < *(int *)(iVar1 + 0x30));
  }
  return 0;
}

/* ---- 0x10003970  Cos_Restore ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 Cos_Restore(code *param_1)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  code *pcVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  #define iStack_28 (*(int *)(_frame + (0x40 - 0x28)))
  #define iStack_24 (*(int *)(_frame + (0x40 - 0x24)))
  #define auStack_20 (*(undefined1 (*)[32])(_frame + (0x40 - 0x20)))
  
                    /* 0x3970  62  Cos_Restore */
  iVar3 = 0;
  if (0 < _DAT_100143b0) {
    iVar5 = 0;
    do {
      if (*(int *)(DAT_100143b4 + 0x38 + iVar5) == 0) {
        uVar2 = FUN_10005180(iVar3);
        Cos_Free(uVar2);
      }
      iVar3 = iVar3 + 1;
      iVar5 = iVar5 + 0x3c;
    } while (iVar3 < _DAT_100143b0);
  }
  pcVar1 = param_1;
  (*param_1)(&iStack_28,4);
  if (_DAT_100143b0 < iStack_28) {
    DAT_100143b4 = (**(code **)(DAT_100143a8 + 0x28))
                             (DAT_100143b4,iStack_28 * 0x3c,
                              s_C__grimsrc_libs_chore_Costume_c_1001020c,0xa2b);
    if (_DAT_100143b0 < iStack_28) {
      iVar3 = _DAT_100143b0 * 0x3c;
      do {
        _DAT_100143b0 = _DAT_100143b0 + 1;
        *(undefined4 *)(DAT_100143b4 + 0x38 + iVar3) = 1;
        iVar3 = iVar3 + 0x3c;
      } while (_DAT_100143b0 < iStack_28);
    }
    _DAT_100143b0 = iStack_28;
  }
  (*pcVar1)(&iStack_24,4);
  iVar3 = 0;
  if (0 < iStack_24) {
    do {
      (*pcVar1)(&param_1,4);
      (*pcVar1)(auStack_20,0x20);
      Cos_LoadEntry(auStack_20,param_1);
      iVar5 = FUN_10005160(param_1);
      *(undefined4 *)(DAT_100143b4 + 0x38 + iVar5 * 0x3c) = 0;
      _DAT_100143ac = _DAT_100143ac + 1;
      iVar3 = iVar3 + 1;
    } while (iVar3 < iStack_24);
  }
  (*pcVar1)(&iStack_28,4);
  if (DAT_100143c8 < iStack_28) {
    DAT_100143cc = (**(code **)(DAT_100143a8 + 0x28))
                             (DAT_100143cc,iStack_28 * 0x14,
                              s_C__grimsrc_libs_chore_Costume_c_1001020c,0xa42);
    DAT_100143c8 = iStack_28;
  }
  iVar3 = 0;
  if (0 < DAT_100143c8) {
    iVar5 = 0;
    do {
      puVar4 = (undefined4 *)(DAT_100143cc + iVar5);
      iVar3 = iVar3 + 1;
      iVar5 = iVar5 + 0x14;
      *puVar4 = 0;
      puVar4[1] = 0;
      puVar4[2] = 0;
      puVar4[3] = 0;
      puVar4[4] = 0;
      *(undefined4 *)(DAT_100143cc + -4 + iVar5) = 1;
    } while (iVar3 < DAT_100143c8);
  }
  DAT_100143c8 = iStack_28;
  return 0;
}
#undef auStack_20
#undef iStack_24
#undef iStack_28


/* ---- 0x10003b40  Cos_RestoreInstance ---- */
undefined4 Cos_RestoreInstance(int param_1,code *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
                    /* 0x3b40  63  Cos_RestoreInstance */
  iVar2 = FUN_100051a0(param_1);
  iVar3 = *(int *)(DAT_100143cc + iVar2 * 0x14);
  iVar2 = DAT_100143cc + iVar2 * 0x14;
  iVar4 = 0;
  iVar1 = DAT_100143b4 + iVar3 * 0x3c;
  if (0 < *(int *)(DAT_100143b4 + 0x28 + iVar3 * 0x3c)) {
    iVar3 = 0;
    do {
      if ((code *)PTR_100143c0[*(int *)(*(int *)(iVar1 + 0x2c) + 0x20 + iVar3) * 0x17 + 0x11] !=
          (code *)0x0) {
        (*(code *)PTR_100143c0[*(int *)(*(int *)(iVar1 + 0x2c) + 0x20 + iVar3) * 0x17 + 0x11])
                  (param_1,iVar4,0,*(undefined4 *)(*(int *)(iVar2 + 0xc) + iVar4 * 4),param_2);
      }
      iVar4 = iVar4 + 1;
      iVar3 = iVar3 + 0x40;
    } while (iVar4 < *(int *)(iVar1 + 0x28));
  }
  iVar3 = 0;
  if (0 < *(int *)(iVar1 + 0x30)) {
    param_1 = 0;
    do {
      iVar4 = *(int *)(iVar2 + 4) + param_1;
      (*param_2)(iVar4,4);
      (*param_2)(iVar4 + 4,4);
      (*param_2)(iVar4 + 8,4);
      iVar3 = iVar3 + 1;
      param_1 = param_1 + 0xc;
    } while (iVar3 < *(int *)(iVar1 + 0x30));
  }
  return 0;
}

/* ---- 0x10003c20  FUN_10003c20 ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int FUN_10003c20(int param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int iVar6;
  #define uStack_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar6 = 0;
  iVar1 = 0;
  uStack_4 = 0;
  if (*(int *)(param_1 + 0x28) != 0) {
    puVar4 = (undefined4 *)&DAT_10014210;
    do {
      iVar2 = 0;
      if (IMG_ADDR(0x10014210) < (int)puVar4) {
        piVar3 = (int *)&DAT_10014210;
        do {
          if (*piVar3 == *(int *)(*(int *)(param_1 + 0x2c) + 0x20 + iVar6)) break;
          iVar2 = iVar2 + 1;
          piVar3 = piVar3 + 1;
        } while (iVar2 < iVar1);
      }
      puVar5 = puVar4;
      if (iVar2 == iVar1) {
        iVar1 = iVar1 + 1;
        puVar5 = puVar4 + 1;
        *puVar4 = *(undefined4 *)(*(int *)(param_1 + 0x2c) + 0x20 + iVar6);
      }
      uStack_4 = uStack_4 + 1;
      iVar6 = iVar6 + 0x40;
      puVar4 = puVar5;
    } while (uStack_4 < *(uint *)(param_1 + 0x28));
  }
  return iVar1;
}
#undef uStack_4


/* ---- 0x10003c90  FUN_10003c90 ---- */
undefined4 FUN_10003c90(int param_1,uint param_2,int param_3,uint param_4)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int *piVar2;
  int iVar3;
  uint *puVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  int *piVar8;
  #define auStack_8 (*(uint (*)[2])(_frame + (0x20 - 0x8)))
  
  if (param_1 == 0) {
    (**(code **)(DAT_100143a8 + 0x18))(IMG_ADDR(0x1001034c),s_C__grimsrc_libs_chore_Costume_c_1001020c,0xa9b);
  }
  uVar6 = 0;
  iVar1 = *(int *)(param_1 + 0x34) + param_2 * 0x2c;
  uVar7 = *(uint *)(*(int *)(param_1 + 0x34) + 0x20 + param_2 * 0x2c);
  piVar2 = *(int **)(iVar1 + 0x24);
  piVar8 = piVar2;
  if (uVar7 != 0) {
    do {
      if (*piVar8 == param_3) break;
      uVar6 = uVar6 + 1;
      piVar8 = piVar8 + 4;
    } while (uVar6 < uVar7);
  }
  if (uVar6 == uVar7) {
    *(uint *)(iVar1 + 0x20) = uVar7 + 1;
    iVar3 = (**(code **)(DAT_100143a8 + 0x28))
                      (piVar2,(uVar7 + 1) * 0x10,s_C__grimsrc_libs_chore_Costume_c_1001020c,0xaa8);
    *(int *)(iVar1 + 0x24) = iVar3;
    piVar8 = (int *)(*(int *)(iVar1 + 0x20) * 0x10 + -0x10 + iVar3);
    piVar8[2] = 0;
    piVar8[3] = 0;
    piVar8[1] = 0;
    *piVar8 = param_3;
  }
  auStack_8[0] = param_4;
  if (piVar8[2] == 0) {
    puVar4 = (uint *)0x0;
  }
  else {
    puVar4 = (uint *)FUN_10005de0(auStack_8,piVar8[3],piVar8[2],8,FUN_10003e50);
  }
  if (puVar4 == (uint *)0x0) {
    iVar3 = piVar8[2];
    piVar8[2] = iVar3 + 1;
    iVar3 = (**(code **)(DAT_100143a8 + 0x28))
                      (piVar8[3],(iVar3 + 1) * 8,s_C__grimsrc_libs_chore_Costume_c_1001020c,0xabb);
    piVar8[3] = iVar3;
    puVar4 = (uint *)(iVar3 + -8 + piVar8[2] * 8);
  }
  *puVar4 = param_4;
  if ((uint)piVar8[1] < param_4) {
    piVar8[1] = param_4;
  }
  uVar7 = 1;
  if (param_4 != 0) {
    uVar7 = param_4;
  }
  uVar6 = *(uint *)(iVar1 + 0x28);
  if ((*(uint *)(iVar1 + 0x28) < uVar7) && (uVar6 = param_4, param_4 == 0)) {
    uVar6 = 1;
  }
  *(uint *)(iVar1 + 0x28) = uVar6;
  FUN_10005ba0(piVar8[3],piVar8[2],8,FUN_10003e50);
  uVar7 = *(uint *)(iVar1 + 0x20);
  param_2 = 0;
  if (uVar7 != 0) {
    param_1 = 0;
    do {
      uVar6 = 0;
      if (uVar7 != 0) {
        iVar3 = 0;
        do {
          if ((param_2 != uVar6) &&
             (*(int *)(param_1 + *(int *)(iVar1 + 0x24)) == *(int *)(iVar3 + *(int *)(iVar1 + 0x24))
             )) {
            return 0;
          }
          uVar6 = uVar6 + 1;
          iVar3 = iVar3 + 0x10;
        } while (uVar6 < uVar7);
      }
      param_2 = param_2 + 1;
      param_1 = param_1 + 0x10;
    } while (param_2 < uVar7);
  }
  uVar5 = FUN_10005de0(auStack_8,piVar8[3],piVar8[2],8,FUN_10003e50);
  return uVar5;
}
#undef auStack_8


/* ---- 0x10003e50  FUN_10003e50 ---- */
uint FUN_10003e50(uint *param_1,uint *param_2)

{
  if (*param_1 < *param_2) {
    return 0xffffffff;
  }
  return (uint)(*param_2 < *param_1);
}

/* ---- 0x10003e70  FUN_10003e70 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_10003e70(int param_1,int *param_2)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  char *pcVar8;
  
  uVar4 = PTR_100143c0[*(int *)(param_1 + 0x20) * 0x17 + 1];
  if (uVar4 == 0) {
    if (param_2 == (int *)0x0) {
      return 0;
    }
    iVar5 = *param_2;
    if (iVar5 == 0) {
      return 0;
    }
    *(int *)(param_1 + 0x30) = iVar5;
    if (param_2[1] != 0) {
      puVar2 = (undefined4 *)
               (**(code **)(DAT_100143a8 + 0x20))
                         (iVar5 << 2,s_C__grimsrc_libs_chore_Costume_c_1001020c,0xaf4);
      *(undefined4 **)(param_1 + 0x34) = puVar2;
      puVar7 = (undefined4 *)param_2[1];
      for (uVar4 = *(uint *)(param_1 + 0x30) & 0x3fffffff; uVar4 != 0; uVar4 = uVar4 - 1) {
        *puVar2 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar2 = puVar2 + 1;
      }
      for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
        *(undefined1 *)puVar2 = *(undefined1 *)puVar7;
        puVar7 = (undefined4 *)((int)puVar7 + 1);
        puVar2 = (undefined4 *)((int)puVar2 + 1);
      }
    }
    if (param_2[2] != 0) {
      uVar3 = (**(code **)(DAT_100143a8 + 0x20))
                        (*(int *)(param_1 + 0x30) << 2,s_C__grimsrc_libs_chore_Costume_c_1001020c,
                         0xafc);
      *(undefined4 *)(param_1 + 0x38) = uVar3;
      uVar4 = 0;
      if (*(int *)(param_1 + 0x30) != 0) {
        do {
          uVar6 = 0xffffffff;
          uVar3 = 0;
          pcVar8 = *(char **)(param_2[2] + uVar4 * 4);
          do {
            if (uVar6 == 0) break;
            uVar6 = uVar6 - 1;
            cVar1 = *pcVar8;
            pcVar8 = pcVar8 + 1;
          } while (cVar1 != '\0');
          uVar6 = ~uVar6;
          if (uVar6 != 0) {
            uVar3 = (**(code **)(DAT_100143a8 + 0x20))
                              (uVar6,s_C__grimsrc_libs_chore_Costume_c_1001020c,0xb00);
          }
          *(undefined4 *)(*(int *)(param_1 + 0x38) + uVar4 * 4) = uVar3;
          FUN_100055a0(*(undefined4 *)(*(int *)(param_1 + 0x38) + uVar4 * 4),
                       *(undefined4 *)(param_2[2] + uVar4 * 4),uVar6 - 1);
          iVar5 = uVar4 * 4;
          uVar4 = uVar4 + 1;
          *(undefined1 *)(*(int *)(*(int *)(param_1 + 0x38) + iVar5) + -1 + uVar6) = 0;
        } while (uVar4 < *(uint *)(param_1 + 0x30));
      }
    }
    uVar4 = 0;
    if (param_2[3] != 0) {
      iVar5 = (**(code **)(DAT_100143a8 + 0x20))
                        (*(int *)(param_1 + 0x30) << 2,s_C__grimsrc_libs_chore_Costume_c_1001020c,
                         0xb0b);
      *(int *)(param_1 + 0x3c) = iVar5;
      if (iVar5 == 0) {
        (**(code **)(DAT_100143a8 + 0x18))
                  (IMG_ADDR(0x100104f8),s_C__grimsrc_libs_chore_Costume_c_1001020c,0xb0c);
      }
      uVar6 = 0;
      uVar4 = 0;
      if (*(int *)(param_1 + 0x30) != 0) {
        iVar5 = 0;
        do {
          uVar3 = (**(code **)(DAT_100143a8 + 0x20))
                            (0x14,s_C__grimsrc_libs_chore_Costume_c_1001020c,0xb0e);
          *(undefined4 *)(*(int *)(param_1 + 0x3c) + uVar6 * 4) = uVar3;
          puVar2 = (undefined4 *)(iVar5 + param_2[3]);
          puVar7 = *(undefined4 **)(*(int *)(param_1 + 0x3c) + uVar6 * 4);
          *puVar7 = *puVar2;
          puVar7[1] = puVar2[1];
          puVar7[2] = puVar2[2];
          puVar7[3] = puVar2[3];
          if (_DAT_100143dc == (code *)0x0) {
            *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x3c) + uVar6 * 4) + 0x10) = 0;
          }
          else if (param_2[4] == 0) {
            uVar3 = (*_DAT_100143dc)(iVar5 + param_2[3],0);
            *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x3c) + uVar6 * 4) + 0x10) = uVar3;
          }
          else {
            uVar3 = (*_DAT_100143dc)(iVar5 + param_2[3],*(undefined4 *)(param_2[4] + uVar6 * 4));
            *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x3c) + uVar6 * 4) + 0x10) = uVar3;
          }
          uVar4 = *(uint *)(param_1 + 0x30);
          uVar6 = uVar6 + 1;
          iVar5 = iVar5 + 0x10;
        } while (uVar6 < uVar4);
      }
    }
  }
  return uVar4;
}

/* ---- 0x10004090  FUN_10004090 ---- */
void FUN_10004090(undefined4 param_1,int param_2,char *param_3,int param_4,undefined4 param_5,
                 undefined4 param_6)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  
  uVar3 = 0xffffffff;
  pcVar4 = param_3;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  if (~uVar3 - 1 < 0x20) {
    FUN_100055a0(param_2,param_3,0x1f);
    *(undefined4 *)(param_2 + 0x24) = param_5;
    *(int *)(param_2 + 0x20) = param_4;
    *(undefined1 *)(param_2 + 0x1f) = 0;
    *(undefined4 *)(param_2 + 0x2c) = param_6;
    *(undefined4 *)(param_2 + 0x28) = 0;
    for (iVar2 = FUN_10004170(param_1,PTR_100143c0[param_4 * 0x17],0,param_3); -1 < iVar2;
        iVar2 = FUN_10004170(param_1,PTR_100143c0[*(int *)(param_2 + 0x20) * 0x17],iVar2,param_3)) {
      iVar2 = *(int *)(param_2 + 0x28) + 1;
      *(int *)(param_2 + 0x28) = iVar2;
    }
    *(undefined4 *)(param_2 + 0x30) = 0;
    *(undefined4 *)(param_2 + 0x34) = 0;
    *(undefined4 *)(param_2 + 0x38) = 0;
    *(undefined4 *)(param_2 + 0x3c) = 0;
  }
  return;
}

/* ---- 0x10004140  FUN_10004140 ---- */
void FUN_10004140(int param_1)

{
  *(undefined4 *)(param_1 + 0x28) = 0xf;
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  FUN_100055a0(param_1,IMG_ADDR(0x10010030),0x1f);
  *(undefined1 *)(param_1 + 0x1f) = 0;
  return;
}

/* ---- 0x10004170  FUN_10004170 ---- */
uint FUN_10004170(int param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = *(int *)(param_1 + 0x2c);
  uVar3 = 0;
  if (*(int *)(param_1 + 0x28) == 0) {
    return 0xffffffff;
  }
  while (((*(int *)(iVar2 + 0x28) != param_3 ||
          (PTR_100143c0[*(int *)(iVar2 + 0x20) * 0x17] != param_2)) ||
         (iVar1 = FUN_10005740(iVar2,param_4), iVar1 != 0))) {
    uVar3 = uVar3 + 1;
    iVar2 = iVar2 + 0x40;
    if (*(uint *)(param_1 + 0x28) <= uVar3) {
      return 0xffffffff;
    }
  }
  return uVar3;
}

/* ---- 0x100041e0  FUN_100041e0 ---- */
undefined4 FUN_100041e0(undefined4 param_1,undefined4 param_2,uint param_3)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  #define auStack_2c (*(undefined1 (*)[4])(_frame + (0x40 - 0x2c)))
  #define iStack_28 (*(int *)(_frame + (0x40 - 0x28)))
  #define auStack_24 (*(undefined4 (*)[2])(_frame + (0x40 - 0x24)))
  #define auStack_1c (*(undefined1 (*)[4])(_frame + (0x40 - 0x1c)))
  #define auStack_18 (*(undefined1 (*)[8])(_frame + (0x40 - 0x18)))
  #define auStack_10 (*(undefined1 (*)[16])(_frame + (0x40 - 0x10)))
  
  uVar1 = param_1;
  iVar2 = FUN_10004bb0(param_1,IMG_ADDR(0x10013e10),0x400);
  if (iVar2 == 0) {
    return 0;
  }
  iVar2 = FUN_10005810((char *)IMG_ADDR(0x10013e10),(char *)IMG_ADDR(0x10010538),&param_1);
  if (iVar2 != 1) {
    return 0;
  }
  uVar4 = 0;
  if (param_3 == 0) {
    return 1;
  }
  do {
    iVar2 = FUN_10004bb0(uVar1,IMG_ADDR(0x10013e10),0x400);
    if (iVar2 == 0) {
      return 0;
    }
    iVar2 = FUN_10005810((char *)IMG_ADDR(0x10013e10),(char *)IMG_ADDR(0x10010524),&iStack_28,auStack_2c,auStack_24,
                         auStack_18);
    if (iVar2 != 4) {
      return 0;
    }
    iVar2 = FUN_10005740(auStack_1c,IMG_ADDR(0x1001019c));
    uVar3 = 0;
    if (iVar2 != 0) {
      iVar2 = FUN_10005740(auStack_1c,IMG_ADDR(0x10010198));
      if (iVar2 == 0) {
        uVar3 = 1;
      }
      else {
        iVar2 = FUN_10005740(auStack_1c,IMG_ADDR(0x10010190));
        if (iVar2 != 0) {
          return 0;
        }
        uVar3 = 2;
      }
    }
    uVar3 = FUN_10004320(auStack_24[0],auStack_10,uVar3);
    uVar4 = uVar4 + 1;
    *(undefined4 *)(&DAT_10014210 + iStack_28 * 4) = uVar3;
  } while (uVar4 < param_3);
  return 1;
}
#undef auStack_10
#undef auStack_18
#undef auStack_1c
#undef auStack_24
#undef auStack_2c
#undef iStack_28


/* ---- 0x10004320  FUN_10004320 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_10004320(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  
  uVar3 = 0;
  if (_DAT_100143b8 != 0) {
    piVar2 = PTR_100143c0 + 2;
    do {
      if ((piVar2[-2] == param_1) && (piVar2[-1] == param_3)) {
        iVar1 = FUN_10005740(piVar2,param_2);
        if (iVar1 == 0) break;
      }
      uVar3 = uVar3 + 1;
      piVar2 = piVar2 + 0x17;
    } while (uVar3 < _DAT_100143b8);
  }
  if (uVar3 == _DAT_100143b8) {
    return 0xffffffff;
  }
  return uVar3;
}

/* ---- 0x10004390  FUN_10004390 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_10004390(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint *puVar5;
  undefined4 uVar6;
  uint uVar7;
  int *piVar8;
  uint uVar9;
  uint uVar10;
  int unaff_retaddr;
  #define auStack_1c (*(undefined1 (*)[8])(_frame + (0x30 - 0x1c)))
  #define uStack_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define puStack_10 (*(uint **)(_frame + (0x30 - 0x10)))
  #define uStack_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define iStack_8 (*(int *)(_frame + (0x30 - 0x8)))
  #define uStack_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  iVar2 = CosUtil_PtrFromHandle(param_2);
  iVar3 = FUN_10004bb0(param_1,IMG_ADDR(0x10013e10),0x400);
  if (iVar3 == 0) {
    return 0;
  }
  iVar3 = FUN_10005810((char *)IMG_ADDR(0x10013e10),(char *)IMG_ADDR(0x10010574),auStack_1c);
  if (iVar3 != 1) {
    return 0;
  }
  uVar10 = 0;
  if (uStack_14 == 0) {
    param_3 = 0;
  }
  else {
    param_3 = (**(code **)(DAT_100143a8 + 0x20))
                        (uStack_14 << 6,s_C__grimsrc_libs_chore_Costume_c_1001020c,0xbdf);
    if (param_3 == 0) {
      (**(code **)(DAT_100143a8 + 0x18))
                (IMG_ADDR(0x10010558),s_C__grimsrc_libs_chore_Costume_c_1001020c,0xbe0);
    }
  }
  if (param_3 == 0) {
    return 0;
  }
  if (_DAT_100143d4 < uStack_14) {
    _DAT_100143d0 =
         (**(code **)(DAT_100143a8 + 0x28))
                   (_DAT_100143d0,uStack_14 * 4,s_C__grimsrc_libs_chore_Costume_c_1001020c,0xbeb);
    _DAT_100143d4 = uStack_14;
  }
  if (uStack_14 != 0) {
    iVar3 = param_3 + 0x28;
    do {
      iVar4 = FUN_10004bb0(param_1,IMG_ADDR(0x10013e10),0x400);
      if ((iVar4 == 0) ||
         (iVar4 = FUN_10005810((char *)IMG_ADDR(0x10013e10),(char *)IMG_ADDR(0x10010544),&puStack_10,&iStack_8,iVar3,
                               iVar3 + 4,iVar3 + -0x28), iVar4 != 5)) {
        return 0;
      }
      uVar10 = uVar10 + 1;
      *(undefined4 *)(iVar3 + -8) = *(undefined4 *)(&DAT_10014210 + unaff_retaddr * 4);
      iVar3 = iVar3 + 0x40;
    } while (uVar10 < uStack_14);
  }
  if (uStack_14 == 0) {
    puStack_10 = (uint *)0x0;
    puVar5 = (uint *)0x0;
  }
  else {
    puVar5 = (uint *)(**(code **)(DAT_100143a8 + 0x20))
                               (uStack_14 * 4,s_C__grimsrc_libs_chore_Costume_c_1001020c,0xc02);
    puStack_10 = puVar5;
    if (puVar5 == (uint *)0x0) {
      (**(code **)(DAT_100143a8 + 0x18))
                (IMG_ADDR(0x10010288),s_C__grimsrc_libs_chore_Costume_c_1001020c,0xc03);
    }
  }
  uVar10 = 0;
  uStack_c = 0;
  if (uStack_14 != 0) {
    piVar8 = (int *)(param_3 + 0x2c);
    do {
      iVar3 = *piVar8;
      *puVar5 = 0;
      while (iVar3 != -1) {
        iVar3 = *(int *)(iVar3 * 0x40 + 0x2c + param_3);
        *puVar5 = *puVar5 + 1;
      }
      if (uStack_c <= *puVar5) {
        uStack_c = *puVar5;
      }
      uVar10 = uVar10 + 1;
      puVar5 = puVar5 + 1;
      piVar8 = piVar8 + 0x10;
    } while (uVar10 < uStack_14);
  }
  uStack_4 = 0;
  uVar10 = uStack_14;
  do {
    uVar9 = 0;
    uVar7 = uStack_4;
    if (uVar10 != 0) {
      piVar8 = (int *)(param_3 + 0x2c);
      do {
        if (puStack_10[uVar9] == uVar7) {
          piVar1 = piVar8 + -0xb;
          iStack_8 = FUN_10004770(iVar2,PTR_100143c0[piVar8[-3] * 0x17],piVar8[-1],piVar1,*piVar8);
          uVar10 = uStack_14;
          uVar7 = uStack_4;
          if (iStack_8 < 0) {
            if (*piVar8 < 0) {
              iVar3 = CosUtil_AddComponent(param_4,piVar1,PTR_100143c0[piVar8[-3] * 0x17],0,0);
            }
            else {
              iVar3 = *piVar8 * 0x40 + param_3;
              iStack_8 = FUN_10004170(iVar2,PTR_100143c0[*(int *)(iVar3 + 0x20) * 0x17],
                                      *(undefined4 *)(iVar3 + 0x28),iVar3);
              if (iStack_8 < 0) goto LAB_1000470a;
              iVar3 = CosUtil_AddComponent
                                (param_4,piVar1,PTR_100143c0[piVar8[-3] * 0x17],
                                 *(undefined4 *)(iStack_8 * 0x40 + *(int *)(iVar2 + 0x2c) + 0x24),
                                 PTR_100143c0
                                 [*(int *)(iStack_8 * 0x40 + 0x20 + *(int *)(iVar2 + 0x2c)) * 0x17])
              ;
            }
            if (iVar3 == 0) {
LAB_1000470a:
              (**(code **)(DAT_100143a8 + 0x24))(param_3);
              (**(code **)(DAT_100143a8 + 0x24))(puStack_10);
              return 0;
            }
            uVar6 = FUN_10004170(iVar2,PTR_100143c0[piVar8[-3] * 0x17],piVar8[-1],piVar1);
            *(undefined4 *)(_DAT_100143d0 + uVar9 * 4) = uVar6;
            uVar10 = uStack_14;
            uVar7 = uStack_4;
            if (*(int *)(_DAT_100143d0 + uVar9 * 4) < 0) goto LAB_1000470a;
          }
        }
        uVar9 = uVar9 + 1;
        piVar8 = piVar8 + 0x10;
      } while (uVar9 < uVar10);
    }
    uStack_4 = uVar7 + 1;
    if (uStack_c < uStack_4) {
      (**(code **)(DAT_100143a8 + 0x24))(param_3);
      (**(code **)(DAT_100143a8 + 0x24))(puStack_10);
      return 1;
    }
  } while( true );
}
#undef auStack_1c
#undef iStack_8
#undef puStack_10
#undef uStack_14
#undef uStack_4
#undef uStack_c

#endif


/* ---- 0x10004770  FUN_10004770 ---- */
uint FUN_10004770(int param_1,int param_2,int param_3,undefined4 param_4,int param_5)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = *(int *)(param_1 + 0x2c);
  uVar3 = 0;
  if (*(int *)(param_1 + 0x28) == 0) {
    return 0xffffffff;
  }
  while ((((*(int *)(iVar2 + 0x28) != param_3 ||
           (PTR_100143c0[*(int *)(iVar2 + 0x20) * 0x17] != param_2)) ||
          (*(int *)(iVar2 + 0x2c) != param_5)) || (iVar1 = FUN_10005740(iVar2,param_4), iVar1 != 0))
        ) {
    uVar3 = uVar3 + 1;
    iVar2 = iVar2 + 0x40;
    if (*(uint *)(param_1 + 0x28) <= uVar3) {
      return 0xffffffff;
    }
  }
  return uVar3;
}

/* ---- 0x100047f0  FUN_100047f0 ---- */
undefined4 FUN_100047f0(undefined4 param_1,int param_2,undefined4 param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint *puVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  uint uStack00000010;
  #define auStack_4 (*(undefined1 (*)[4])(_frame + (0x20 - 0x4)))
  
  iVar2 = FUN_10004bb0(param_1,IMG_ADDR(0x10013e10),0x400);
  if (iVar2 == 0) {
    return 0;
  }
  puVar1 = (uint *)(param_2 + 0x30);
  iVar2 = FUN_10005810((char *)IMG_ADDR(0x10013e10),(char *)IMG_ADDR(0x100105c0),puVar1);
  if (iVar2 != 1) {
    return 0;
  }
  uVar4 = 0;
  if (*puVar1 == 0) {
    *(undefined4 *)(param_2 + 0x34) = 0;
  }
  else {
    iVar2 = (**(code **)(DAT_100143a8 + 0x20))
                      (*puVar1 * 0x2c,s_C__grimsrc_libs_chore_Costume_c_1001020c,0xc7e);
    *(int *)(param_2 + 0x34) = iVar2;
    if (iVar2 == 0) {
      *puVar1 = 0;
      return 0;
    }
  }
  iVar2 = *(int *)(param_2 + 0x34);
  if (*puVar1 != 0) {
    do {
      FUN_10004140(iVar2);
      uVar4 = uVar4 + 1;
      iVar2 = iVar2 + 0x2c;
    } while (uVar4 < *puVar1);
  }
  iVar2 = *(int *)(param_2 + 0x34);
  uStack00000010 = 0;
  if (*puVar1 != 0) {
    piVar5 = (int *)(iVar2 + 0x20);
    while( true ) {
      iVar3 = FUN_10004bb0(param_3,IMG_ADDR(0x10013e10),0x400);
      if (iVar3 == 0) {
        return 0;
      }
      iVar3 = FUN_10005810((char *)IMG_ADDR(0x10013e10),(char *)IMG_ADDR(0x100105ac),auStack_4,piVar5 + 2,piVar5,iVar2);
      if (iVar3 != 4) break;
      if (*piVar5 == 0) {
        piVar5[1] = 0;
      }
      else {
        iVar3 = (**(code **)(DAT_100143a8 + 0x20))
                          (*piVar5 << 4,s_C__grimsrc_libs_chore_Costume_c_1001020c,0xca1);
        piVar5[1] = iVar3;
        if (iVar3 == 0) {
          (**(code **)(DAT_100143a8 + 0x18))
                    (IMG_ADDR(0x10010588),s_C__grimsrc_libs_chore_Costume_c_1001020c,0xca2);
        }
      }
      uStack00000010 = uStack00000010 + 1;
      iVar2 = iVar2 + 0x2c;
      piVar5 = piVar5 + 0xb;
      if (*puVar1 <= uStack00000010) {
        return 1;
      }
    }
    return 0;
  }
  return 1;
}
#undef auStack_4


/* ---- 0x10004970  FUN_10004970 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_10004970(undefined4 param_1,int param_2)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  uint *puVar6;
  #define uStack_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define piStack_14 (*(int **)(_frame + (0x30 - 0x14)))
  #define uStack_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define iStack_c (*(int *)(_frame + (0x30 - 0xc)))
  #define piStack_8 (*(int **)(_frame + (0x30 - 0x8)))
  #define iStack_4 (*(int *)(_frame + (0x30 - 0x4)))
  
  uStack_10 = 0;
  if (*(int *)(param_2 + 0x30) == 0) {
    return 1;
  }
  do {
    iVar1 = FUN_10004bb0(param_1,IMG_ADDR(0x10013e10),0x400);
    if ((iVar1 == 0) ||
       (iVar1 = FUN_10005810((char *)IMG_ADDR(0x10013e10),(char *)IMG_ADDR(0x10010600),&piStack_14), iVar1 != 1)) {
      return 0;
    }
    uStack_18 = 0;
    piVar4 = *(int **)(*(int *)(param_2 + 0x34) + 0x24 + iStack_c * 0x2c);
    iStack_4 = *(int *)(param_2 + 0x34) + iStack_c * 0x2c;
    piStack_14 = piVar4;
    if (*(int *)(iStack_4 + 0x20) != 0) {
      puVar6 = (uint *)(piVar4 + 2);
      do {
        uVar5 = 0;
        piStack_14 = piVar4;
        iVar1 = FUN_10004bb0(param_1,IMG_ADDR(0x10013e10),0x400);
        if (iVar1 == 0) {
          return 0;
        }
        iVar1 = FUN_10005810((char *)IMG_ADDR(0x10013e10),(char *)IMG_ADDR(0x100105f8),piVar4,puVar6);
        if (iVar1 != 2) {
          return 0;
        }
        uVar2 = *puVar6;
        *piVar4 = *(int *)(_DAT_100143d0 + *piVar4 * 4);
        if (uVar2 == 0) {
          puVar6[1] = 0;
        }
        else {
          uVar2 = (**(code **)(DAT_100143a8 + 0x20))
                            (uVar2 << 3,s_C__grimsrc_libs_chore_Costume_c_1001020c,0xcda);
          puVar6[1] = uVar2;
          if (uVar2 == 0) {
            (**(code **)(DAT_100143a8 + 0x18))
                      (IMG_ADDR(0x100105d8),s_C__grimsrc_libs_chore_Costume_c_1001020c,0xcdb);
          }
        }
        uVar2 = puVar6[1];
        piStack_8 = PTR_100143c0 + *(int *)(*(int *)(param_2 + 0x2c) + 0x20 + *piVar4 * 0x40) * 0x17
        ;
        if (*puVar6 != 0) {
          iVar1 = uVar2 + 4;
          do {
            iVar3 = FUN_10004bb0(param_1,IMG_ADDR(0x10013e10),0x400);
            if (iVar3 == 0) {
              return 0;
            }
            if ((*(int *)(uStack_10 + 4) == 0) || (*(int *)(uStack_10 + 4) == 1)) {
              iVar3 = FUN_10005810((char *)IMG_ADDR(0x10013e10),(char *)IMG_ADDR(0x100105f8),uVar2,iVar1);
              piVar4 = piStack_14;
            }
            else {
              iVar3 = FUN_10005810((char *)IMG_ADDR(0x10013e10),(char *)IMG_ADDR(0x100105d0),uVar2,iVar1);
              piVar4 = piStack_14;
            }
            if (iVar3 != 2) {
              return 0;
            }
            uVar5 = uVar5 + 1;
            uVar2 = uVar2 + 8;
            iVar1 = iVar1 + 8;
            piStack_14 = piVar4;
          } while (uVar5 < *puVar6);
        }
        if (*puVar6 == 0) {
          uVar5 = 0;
        }
        else {
          uVar5 = *(uint *)((puVar6[1] - 8) + *puVar6 * 8);
        }
        puVar6[-1] = uVar5;
        uStack_18 = uStack_18 + 1;
        piVar4 = piVar4 + 4;
        puVar6 = puVar6 + 4;
        piStack_14 = piVar4;
      } while (uStack_18 < *(uint *)(iStack_4 + 0x20));
    }
    uStack_10 = uStack_10 + 1;
    if (*(uint *)(param_2 + 0x30) <= uStack_10) {
      return 1;
    }
  } while( true );
}
#undef iStack_4
#undef iStack_c
#undef piStack_14
#undef piStack_8
#undef uStack_10
#undef uStack_18


/* ---- 0x10004bb0  FUN_10004bb0 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_10004bb0(undefined4 param_1,char *param_2,int param_3)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  undefined1 *puVar4;
  
  bVar2 = false;
  while( true ) {
    if (param_3 + -1 == 0) {
      return 1;
    }
    iVar3 = (**(code **)(DAT_100143a8 + 0x3c))(param_1,param_2,param_3 + -1);
    if (iVar3 == 0) break;
    _DAT_100143ec = _DAT_100143ec + 1;
    cVar1 = *param_2;
    if (((cVar1 != ';') && (cVar1 != '#')) && (cVar1 != '\n')) {
      puVar4 = (undefined1 *)FUN_10005e90(param_2,0x23);
      if (puVar4 != (undefined1 *)0x0) {
        *puVar4 = 0;
      }
      if (*param_2 != '\0') {
        bVar2 = true;
      }
    }
    if (bVar2) {
      return 1;
    }
  }
  return 0;
}

/* ---- 0x10004c40  FUN_10004c40 ---- */
void FUN_10004c40(undefined4 param_1,int param_2,uint param_3)

{
  undefined4 *puVar1;
  uint uVar2;
  
  uVar2 = 0;
  if (param_3 != 0) {
    puVar1 = (undefined4 *)(param_2 + 8);
    do {
      puVar1[-2] = 0;
      puVar1[-1] = uVar2;
      *puVar1 = 0;
      uVar2 = uVar2 + 1;
      puVar1 = puVar1 + 3;
    } while (uVar2 < param_3);
  }
  return;
}

/* ---- 0x10004c70  FUN_10004c70 ---- */
void FUN_10004c70(undefined4 param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  #define uStack_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = CosUtil_PtrFromHandle(param_1);
  uVar3 = 0;
  if (*(int *)(iVar1 + 0x28) != 0) {
    iVar4 = 0;
    do {
      iVar2 = *(int *)(iVar1 + 0x2c) + iVar4;
      FUN_10004d70(param_1,PTR_100143c0 + *(int *)(iVar2 + 0x20) * 0x17,iVar2);
      uVar3 = uVar3 + 1;
      iVar4 = iVar4 + 0x40;
    } while (uVar3 < *(uint *)(iVar1 + 0x28));
  }
  (**(code **)(DAT_100143a8 + 0x24))(*(undefined4 *)(iVar1 + 0x2c));
  iVar4 = 0;
  uStack_4 = 0;
  if (*(int *)(iVar1 + 0x30) != 0) {
    do {
      uVar3 = 0;
      iVar2 = *(int *)(iVar1 + 0x34) + iVar4;
      if (*(int *)(iVar2 + 0x20) != 0) {
        iVar5 = 0;
        do {
          (**(code **)(DAT_100143a8 + 0x24))(*(undefined4 *)(*(int *)(iVar2 + 0x24) + 0xc + iVar5));
          uVar3 = uVar3 + 1;
          iVar5 = iVar5 + 0x10;
          iVar2 = *(int *)(iVar1 + 0x34) + iVar4;
        } while (uVar3 < *(uint *)(*(int *)(iVar1 + 0x34) + 0x20 + iVar4));
      }
      (**(code **)(DAT_100143a8 + 0x24))(*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x24 + iVar4));
      uStack_4 = uStack_4 + 1;
      iVar4 = iVar4 + 0x2c;
    } while (uStack_4 < *(uint *)(iVar1 + 0x30));
  }
  (**(code **)(DAT_100143a8 + 0x24))(*(undefined4 *)(iVar1 + 0x34));
  iVar1 = FUN_10005160(param_1);
  *(undefined4 *)(DAT_100143b4 + 0x38 + iVar1 * 0x3c) = 1;
  return;
}
#undef uStack_4


/* ---- 0x10004d70  FUN_10004d70 ---- */
void FUN_10004d70(undefined4 param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  code *pcVar2;
  uint uVar3;
  
  iVar1 = param_2[1];
  if (iVar1 == 0) {
    pcVar2 = (code *)param_2[0xd];
  }
  else {
    if ((iVar1 != 1) && (iVar1 != 2)) {
      (**(code **)(DAT_100143a8 + 0x18))
                (&DAT_10010284,s_C__grimsrc_libs_chore_Costume_c_1001020c,0xe9c);
      goto LAB_10004dc2;
    }
    pcVar2 = (code *)param_2[0xd];
  }
  if (pcVar2 != (code *)0x0) {
    (*pcVar2)(param_1,*param_2,*(undefined4 *)(param_3 + 0x24));
  }
LAB_10004dc2:
  (**(code **)(DAT_100143a8 + 0x24))(*(undefined4 *)(param_3 + 0x34));
  if (*(int *)(param_3 + 0x38) != 0) {
    uVar3 = 0;
    if (*(int *)(param_3 + 0x30) != 0) {
      do {
        (**(code **)(DAT_100143a8 + 0x24))(*(undefined4 *)(*(int *)(param_3 + 0x38) + uVar3 * 4));
        uVar3 = uVar3 + 1;
      } while (uVar3 < *(uint *)(param_3 + 0x30));
    }
    (**(code **)(DAT_100143a8 + 0x24))(*(undefined4 *)(param_3 + 0x38));
  }
  if (*(int *)(param_3 + 0x3c) != 0) {
    uVar3 = 0;
    if (*(int *)(param_3 + 0x30) != 0) {
      do {
        (**(code **)(DAT_100143a8 + 0x24))(*(undefined4 *)(*(int *)(param_3 + 0x3c) + uVar3 * 4));
        uVar3 = uVar3 + 1;
      } while (uVar3 < *(uint *)(param_3 + 0x30));
    }
    (**(code **)(DAT_100143a8 + 0x24))(*(undefined4 *)(param_3 + 0x3c));
  }
  return;
}

/* ---- 0x10004e50  FUN_10004e50 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int FUN_10004e50(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  iVar1 = 0;
  if (0 < _DAT_100143b0) {
    piVar3 = (int *)(DAT_100143b4 + 0x38);
    do {
      if (*piVar3 != 0) {
        *(undefined4 *)(DAT_100143b4 + 0x38 + iVar1 * 0x3c) = 0;
        _DAT_100143ac = _DAT_100143ac + 1;
        return iVar1;
      }
      iVar1 = iVar1 + 1;
      piVar3 = piVar3 + 0xf;
    } while (iVar1 < _DAT_100143b0);
  }
  if (_DAT_100143b0 < _DAT_100143ac + 1) {
    _DAT_100143b0 = _DAT_100143b0 + 8;
    DAT_100143b4 = (**(code **)(DAT_100143a8 + 0x28))
                             (DAT_100143b4,_DAT_100143b0 * 0x3c,
                              s_C__grimsrc_libs_chore_Costume_c_1001020c,0xed0);
    if (_DAT_100143ac < _DAT_100143b0) {
      iVar2 = _DAT_100143ac * 0x3c;
      iVar1 = _DAT_100143ac;
      do {
        *(undefined4 *)(DAT_100143b4 + 0x38 + iVar2) = 1;
        iVar1 = iVar1 + 1;
        iVar2 = iVar2 + 0x3c;
      } while (iVar1 < _DAT_100143b0);
    }
  }
  iVar2 = _DAT_100143ac;
  iVar1 = _DAT_100143ac * 0x3c;
  _DAT_100143ac = _DAT_100143ac + 1;
  *(undefined4 *)(DAT_100143b4 + 0x38 + iVar1) = 0;
  return iVar2;
}

/* ---- 0x10004f30  FUN_10004f30 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_10004f30(void)

{
  int iVar1;
  
  if (_DAT_100143bc < _DAT_100143b8 + 1U) {
    (**(code **)(DAT_100143a8 + 0x18))(IMG_ADDR(0x1001060c),s_C__grimsrc_libs_chore_Costume_c_1001020c,0xede);
  }
  iVar1 = _DAT_100143b8;
  _DAT_100143b8 = _DAT_100143b8 + 1;
  return iVar1;
}

/* ---- 0x10004f70  FUN_10004f70 ---- */
void FUN_10004f70(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  code *pcVar5;
  undefined4 uVar6;
  int *piVar7;
  int iVar8;
  uint uVar9;
  
  piVar1 = (int *)(DAT_100143cc + param_1 * 0x14);
  iVar2 = DAT_100143b4 + *piVar1 * 0x3c;
  uVar6 = FUN_100051c0(param_1);
  if (piVar1[4] == 0) {
    uVar9 = 0;
    if (*(int *)(iVar2 + 0x28) != 0) {
      piVar7 = (int *)(*(int *)(iVar2 + 0x2c) + 0x20);
      do {
        iVar3 = *piVar7;
        iVar8 = 0;
        iVar4 = PTR_100143c0[iVar3 * 0x17 + 1];
        if (iVar4 == 0) {
          pcVar5 = (code *)PTR_100143c0[iVar3 * 0x17 + 0x10];
joined_r0x10005011:
          if (pcVar5 != (code *)0x0) {
            iVar8 = (*pcVar5)(uVar6,uVar9,0);
          }
        }
        else {
          if ((iVar4 == 1) || (iVar4 == 2)) {
            pcVar5 = (code *)PTR_100143c0[iVar3 * 0x17 + 0x10];
            goto joined_r0x10005011;
          }
          (**(code **)(DAT_100143a8 + 0x18))
                    (&DAT_10010284,s_C__grimsrc_libs_chore_Costume_c_1001020c,0xf13);
        }
        if (iVar8 != 0) {
          *(int *)(piVar1[3] + uVar9 * 4) = iVar8;
        }
        uVar9 = uVar9 + 1;
        piVar7 = piVar7 + 0x10;
      } while (uVar9 < *(uint *)(iVar2 + 0x28));
    }
    if (piVar1[1] != 0) {
      (**(code **)(DAT_100143a8 + 0x24))(piVar1[1]);
    }
    if (piVar1[3] != 0) {
      (**(code **)(DAT_100143a8 + 0x24))(piVar1[3]);
    }
    *piVar1 = 0;
    piVar1[1] = 0;
    piVar1[2] = 0;
    piVar1[3] = 0;
    piVar1[4] = 0;
    *piVar1 = -1;
    piVar1[4] = 1;
  }
  return;
}

/* ---- 0x10005090  FUN_10005090 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int FUN_10005090(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  iVar1 = 0;
  if (0 < DAT_100143c8) {
    piVar3 = (int *)(DAT_100143cc + 0x10);
    do {
      if (*piVar3 != 0) {
        *(undefined4 *)(DAT_100143cc + 0x10 + iVar1 * 0x14) = 0;
        _DAT_100143c4 = _DAT_100143c4 + 1;
        return iVar1;
      }
      iVar1 = iVar1 + 1;
      piVar3 = piVar3 + 5;
    } while (iVar1 < DAT_100143c8);
  }
  if (DAT_100143c8 < _DAT_100143c4 + 1) {
    DAT_100143c8 = DAT_100143c8 + 8;
    DAT_100143cc = (**(code **)(DAT_100143a8 + 0x28))
                             (DAT_100143cc,DAT_100143c8 * 0x14,
                              s_C__grimsrc_libs_chore_Costume_c_1001020c,0xf3a);
    if (_DAT_100143c4 < DAT_100143c8) {
      iVar2 = _DAT_100143c4 * 0x14;
      iVar1 = _DAT_100143c4;
      do {
        *(undefined4 *)(DAT_100143cc + 0x10 + iVar2) = 1;
        iVar1 = iVar1 + 1;
        iVar2 = iVar2 + 0x14;
      } while (iVar1 < DAT_100143c8);
    }
  }
  iVar2 = _DAT_100143c4;
  iVar1 = _DAT_100143c4 * 0x14;
  _DAT_100143c4 = _DAT_100143c4 + 1;
  *(undefined4 *)(DAT_100143cc + 0x10 + iVar1) = 0;
  return iVar2;
}

/* ---- 0x10005160  FUN_10005160 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_10005160(int param_1)

{
  if ((param_1 != 0) && (param_1 <= _DAT_100143b0)) {
    return param_1 + -1;
  }
  return -1;
}

/* ---- 0x10005180  FUN_10005180 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_10005180(int param_1)

{
  if ((-1 < param_1) && (param_1 < _DAT_100143b0)) {
    return param_1 + 1;
  }
  return 0;
}

/* ---- 0x100051a0  FUN_100051a0 ---- */
int __cdecl FUN_100051a0(int param_1)

{
  if ((param_1 != 0) && (param_1 <= DAT_100143c8)) {
    return param_1 + -1;
  }
  return -1;
}

/* ---- 0x100051c0  FUN_100051c0 ---- */
int FUN_100051c0(int param_1)

{
  if ((-1 < param_1) && (param_1 < DAT_100143c8)) {
    return param_1 + 1;
  }
  return 0;
}

/* ---- 0x100051e0  FUN_100051e0 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_100051e0(void)

{
  DAT_100143a8 = 0;
  if (_DAT_100143a0 != 0) {
    _DAT_100143a0 = 0;
  }
  return;
}

/* ---- 0x10005200  FUN_10005200 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_10005200(void)

{
  int iVar1;
  
  if (_DAT_100143a4 != 0) {
    return 1;
  }
  _DAT_100143ac = 0;
  _DAT_100143b0 = 0x20;
  DAT_100143b4 = (**(code **)(DAT_100143a8 + 0x20))
                           (0x780,s_C__grimsrc_libs_chore_Costume_c_1001020c,0xf91);
  if (DAT_100143b4 == 0) {
    (**(code **)(DAT_100143a8 + 0x18))(IMG_ADDR(0x1001067c),s_C__grimsrc_libs_chore_Costume_c_1001020c,0xf92);
  }
  iVar1 = 0;
  do {
    iVar1 = iVar1 + 0x3c;
    *(undefined4 *)(DAT_100143b4 + -4 + iVar1) = 1;
  } while (iVar1 < 0x780);
  _DAT_100143b8 = 0;
  _DAT_100143bc = 0x20;
  PTR_100143c0 = (int *)(**(code **)(DAT_100143a8 + 0x20))
                                  (0xb80,s_C__grimsrc_libs_chore_Costume_c_1001020c,0xf99);
  if (PTR_100143c0 == (int *)0x0) {
    (**(code **)(DAT_100143a8 + 0x18))(IMG_ADDR(0x1001065c),s_C__grimsrc_libs_chore_Costume_c_1001020c,0xf9a);
  }
  _DAT_100143c4 = 0;
  DAT_100143c8 = 0x20;
  DAT_100143cc = (**(code **)(DAT_100143a8 + 0x20))
                           (0x280,s_C__grimsrc_libs_chore_Costume_c_1001020c,3999);
  if (DAT_100143cc == 0) {
    (**(code **)(DAT_100143a8 + 0x18))(IMG_ADDR(0x10010638),s_C__grimsrc_libs_chore_Costume_c_1001020c,4000);
  }
  iVar1 = 0;
  do {
    iVar1 = iVar1 + 0x14;
    *(undefined4 *)(DAT_100143cc + -4 + iVar1) = 1;
  } while (iVar1 < 0x280);
  _DAT_100143a4 = 1;
  return 0;
}

/* ---- 0x10005350  FUN_10005350 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_10005350(void)

{
  _DAT_100143b0 = 0;
  _DAT_100143ac = 0;
  (**(code **)(DAT_100143a8 + 0x24))(DAT_100143b4);
  _DAT_100143bc = 0;
  _DAT_100143b8 = 0;
  (**(code **)(DAT_100143a8 + 0x24))(PTR_100143c0);
  DAT_100143c8 = 0;
  _DAT_100143c4 = 0;
  (**(code **)(DAT_100143a8 + 0x24))(DAT_100143cc);
  if (_DAT_100143d4 != 0) {
    (**(code **)(DAT_100143a8 + 0x24))(_DAT_100143d0);
    _DAT_100143d0 = 0;
    _DAT_100143d4 = 0;
  }
  _DAT_100143a4 = 0;
  return;
}

/* ---- 0x10005590  Cos_RegisterSaveVerify ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl Cos_RegisterSaveVerify(undefined4 param_1)

{
                    /* 0x5590  60  Cos_RegisterSaveVerify */
  _DAT_100143e8 = param_1;
  return param_1;
}

/* ---- 0x100055a0  FUN_100055a0 ---- */
uint * FUN_100055a0(uint *param_1,uint *param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  char cVar3;
  uint uVar4;
  uint *puVar5;
  
  if (param_3 == 0) {
    return param_1;
  }
  puVar5 = param_1;
  if (((uint)param_2 & 3) != 0) {
    while( true ) {
      uVar4 = *param_2;
      param_2 = (uint *)((int)param_2 + 1);
      *(char *)puVar5 = (char)uVar4;
      puVar5 = (uint *)((int)puVar5 + 1);
      param_3 = param_3 - 1;
      if (param_3 == 0) {
        return param_1;
      }
      if ((char)uVar4 == '\0') break;
      if (((uint)param_2 & 3) == 0) {
        uVar4 = param_3 >> 2;
        goto joined_r0x100055de;
      }
    }
    do {
      if (((uint)puVar5 & 3) == 0) {
        uVar4 = param_3 >> 2;
        cVar3 = '\0';
        if (uVar4 == 0) goto LAB_1000561b;
        goto LAB_10005689;
      }
      *(char *)puVar5 = '\0';
      puVar5 = (uint *)((int)puVar5 + 1);
      param_3 = param_3 - 1;
    } while (param_3 != 0);
    return param_1;
  }
  uVar4 = param_3 >> 2;
  if (uVar4 != 0) {
    do {
      uVar1 = *param_2;
      uVar2 = *param_2;
      param_2 = param_2 + 1;
      if (((uVar1 ^ 0xffffffff ^ uVar1 + 0x7efefeff) & 0x81010100) != 0) {
        if ((char)uVar2 == '\0') {
          *puVar5 = 0;
joined_r0x10005685:
          while( true ) {
            uVar4 = uVar4 - 1;
            puVar5 = puVar5 + 1;
            if (uVar4 == 0) break;
LAB_10005689:
            *puVar5 = 0;
          }
          cVar3 = '\0';
          param_3 = param_3 & 3;
          if (param_3 != 0) goto LAB_1000561b;
          return param_1;
        }
        if ((char)(uVar2 >> 8) == '\0') {
          *puVar5 = uVar2 & 0xff;
          goto joined_r0x10005685;
        }
        if ((uVar2 & 0xff0000) == 0) {
          *puVar5 = uVar2 & 0xffff;
          goto joined_r0x10005685;
        }
        if ((uVar2 & 0xff000000) == 0) {
          *puVar5 = uVar2;
          goto joined_r0x10005685;
        }
      }
      *puVar5 = uVar2;
      puVar5 = puVar5 + 1;
      uVar4 = uVar4 - 1;
joined_r0x100055de:
    } while (uVar4 != 0);
    param_3 = param_3 & 3;
    if (param_3 == 0) {
      return param_1;
    }
  }
  do {
    cVar3 = (char)*param_2;
    param_2 = (uint *)((int)param_2 + 1);
    *(char *)puVar5 = cVar3;
    puVar5 = (uint *)((int)puVar5 + 1);
    if (cVar3 == '\0') {
      while (param_3 = param_3 - 1, param_3 != 0) {
LAB_1000561b:
        *(char *)puVar5 = cVar3;
        puVar5 = (uint *)((int)puVar5 + 1);
      }
      return param_1;
    }
    param_3 = param_3 - 1;
  } while (param_3 != 0);
  return param_1;
}

/* ---- 0x100056a0  FUN_100056a0 ---- */
char * FUN_100056a0(char *param_1,char param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  
  iVar2 = -1;
  do {
    pcVar4 = param_1;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar4 = param_1 + 1;
    cVar1 = *param_1;
    param_1 = pcVar4;
  } while (cVar1 != '\0');
  iVar2 = -(iVar2 + 1);
  pcVar4 = pcVar4 + -1;
  do {
    pcVar3 = pcVar4;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar3 = pcVar4 + -1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar3;
  } while (param_2 != cVar1);
  pcVar3 = pcVar3 + 1;
  if (*pcVar3 != param_2) {
    pcVar3 = (char *)0x0;
  }
  return pcVar3;
}

/* ---- 0x100056d0  FUN_100056d0 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_100056d0(void)

{
  FUN_10005700();
  _DAT_100143f8 = FUN_100061d0();
  FUN_10006160();
  return;
}

/* ---- 0x100056f0  FUN_100056f0 ---- */
void FUN_100056f0(void)

{
  return;
}

/* ---- 0x10005700  FUN_10005700 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_10005700(void)

{
  _DAT_100106cc = FUN_10006260;
  _DAT_100106c8 = FUN_100066c0;
  _DAT_100106d0 = FUN_100062f0;
  _DAT_100106d4 = FUN_10006200;
  _DAT_100106d8 = FUN_100062d0;
  _DAT_100106dc = FUN_100066c0;
  return;
}

/* ---- 0x10005740  FUN_10005740 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

char FUN_10005740(byte *param_1,byte *param_2)

{
  bool bVar1;
  int iVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  char cVar6;
  uint uVar7;
  
  iVar2 = _DAT_10015af0;
  if (_DAT_10014478 == 0) {
    bVar5 = 0xff;
    do {
      do {
        if (bVar5 == 0) {
          return '\0';
        }
        bVar5 = *param_2;
        param_2 = param_2 + 1;
        bVar4 = *param_1;
        param_1 = param_1 + 1;
      } while (bVar4 == bVar5);
      bVar3 = bVar5 + 0xbf + (-((byte)(bVar5 + 0xbf) < 0x1a) & 0x20U) + 0x41;
      bVar4 = bVar4 + 0xbf;
      bVar5 = bVar4 + (-(bVar4 < 0x1a) & 0x20U) + 0x41;
    } while (bVar5 == bVar3);
    cVar6 = (bVar5 < bVar3) * -2 + '\x01';
  }
  else {
    LOCK();
    _DAT_10015af0 = _DAT_10015af0 + 1;
    UNLOCK();
    bVar1 = 0 < _DAT_10015aec;
    if (bVar1) {
      LOCK();
      UNLOCK();
      _DAT_10015af0 = iVar2;
      FUN_10006810(0x13);
    }
    uVar7 = (uint)bVar1;
    bVar5 = 0xff;
    do {
      do {
        cVar6 = '\0';
        if (bVar5 == 0) goto LAB_100057ef;
        bVar5 = *param_2;
        param_2 = param_2 + 1;
        bVar4 = *param_1;
        param_1 = param_1 + 1;
      } while (bVar5 == bVar4);
      bVar4 = ((code *)FUN_10006a30)(bVar4,bVar5);
      bVar5 = ((code *)FUN_10006a30)();
    } while (bVar4 == bVar5);
    cVar6 = (bVar4 < bVar5) * -2 + '\x01';
LAB_100057ef:
    if (uVar7 == 0) {
      LOCK();
      _DAT_10015af0 = _DAT_10015af0 + -1;
      UNLOCK();
    }
    else {
      FUN_10006890(0x13);
    }
  }
  return cVar6;
}

/* ---- 0x10005810  FUN_10005810 ---- */
int __cdecl FUN_10005810(char *param_1,char *param_2,...)

{
  unsigned char _frame[0x30];  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  uint uVar3;
  #define pcStack_20 (*(char **)(_frame + (0x30 - 0x20)))
  #define iStack_1c (*(int *)(_frame + (0x30 - 0x1c)))
  #define pcStack_18 (*(char **)(_frame + (0x30 - 0x18)))
  #define uStack_14 (*(undefined4 *)(_frame + (0x30 - 0x14)))
  
  uVar3 = 0xffffffff;
  pcStack_18 = param_1;
  pcStack_20 = param_1;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *param_1;
    param_1 = param_1 + 1;
  } while (cVar1 != '\0');
  iStack_1c = ~uVar3 - 1;
  uStack_14 = 0x49;
  iVar2 = FUN_10006b30(&pcStack_20,param_2,&STACK0X(0x0000000c));
  return iVar2;
}
#undef iStack_1c
#undef pcStack_18
#undef pcStack_20
#undef uStack_14


/* ---- 0x10005860  FUN_10005860 ---- */
undefined4 * FUN_10005860(undefined4 *param_1,undefined4 *param_2,uint param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  
  if ((param_2 < param_1) && (param_1 < (undefined4 *)(param_3 + (int)param_2))) {
    param_2 = (undefined4 *)((param_3 - 4) + (int)param_2);
    puVar2 = (undefined4 *)((param_3 - 4) + (int)param_1);
    if (((uint)puVar2 & 3) == 0) {
      uVar1 = param_3 >> 2;
      param_3 = param_3 & 3;
      if (7 < uVar1) {
        for (; uVar1 != 0; uVar1 = uVar1 - 1) {
          *puVar2 = *param_2;
          param_2 = param_2 + -1;
          puVar2 = puVar2 + -1;
        }
        switch(param_3) {
        case 0:
          return param_1;
        case 2:
          goto code_r0x10005b68;
        case 3:
          goto code_r0x10005b7c;
        }
        goto code_r0x10005b58;
      }
    }
    else {
      switch(param_3) {
      case 0:
        goto code_r0x10005b50;
      case 1:
        goto code_r0x10005b58;
      case 2:
        goto code_r0x10005b68;
      case 3:
        goto code_r0x10005b7c;
      default:
        uVar1 = param_3 - ((uint)puVar2 & 3);
        switch((uint)puVar2 & 3) {
        case 1:
          param_3 = uVar1 & 3;
          *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
          param_2 = (undefined4 *)((int)param_2 + -1);
          uVar1 = uVar1 >> 2;
          puVar2 = (undefined4 *)((int)puVar2 - 1);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar2 = *param_2;
              param_2 = param_2 + -1;
              puVar2 = puVar2 + -1;
            }
            switch(param_3) {
            case 0:
              return param_1;
            case 2:
              goto code_r0x10005b68;
            case 3:
              goto code_r0x10005b7c;
            }
            goto code_r0x10005b58;
          }
          break;
        case 2:
          param_3 = uVar1 & 3;
          *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
          uVar1 = uVar1 >> 2;
          *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
          param_2 = (undefined4 *)((int)param_2 + -2);
          puVar2 = (undefined4 *)((int)puVar2 - 2);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar2 = *param_2;
              param_2 = param_2 + -1;
              puVar2 = puVar2 + -1;
            }
            switch(param_3) {
            case 0:
              return param_1;
            case 2:
              goto code_r0x10005b68;
            case 3:
              goto code_r0x10005b7c;
            }
            goto code_r0x10005b58;
          }
          break;
        case 3:
          param_3 = uVar1 & 3;
          *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
          *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
          uVar1 = uVar1 >> 2;
          *(undefined1 *)((int)puVar2 + 1) = *(undefined1 *)((int)param_2 + 1);
          param_2 = (undefined4 *)((int)param_2 + -3);
          puVar2 = (undefined4 *)((int)puVar2 - 3);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar2 = *param_2;
              param_2 = param_2 + -1;
              puVar2 = puVar2 + -1;
            }
            switch(param_3) {
            case 0:
              return param_1;
            case 2:
              goto code_r0x10005b68;
            case 3:
              goto code_r0x10005b7c;
            }
            goto code_r0x10005b58;
          }
        }
      }
    }
    switch(uVar1) {
    case 7:
      puVar2[7 - uVar1] = param_2[7 - uVar1];
    case 6:
      puVar2[6 - uVar1] = param_2[6 - uVar1];
    case 5:
      puVar2[5 - uVar1] = param_2[5 - uVar1];
    case 4:
      puVar2[4 - uVar1] = param_2[4 - uVar1];
    case 3:
      puVar2[3 - uVar1] = param_2[3 - uVar1];
    case 2:
      puVar2[2 - uVar1] = param_2[2 - uVar1];
    case 1:
      puVar2[1 - uVar1] = param_2[1 - uVar1];
      param_2 = param_2 + -uVar1;
      puVar2 = puVar2 + -uVar1;
    }
    switch(param_3) {
    case 1:
code_r0x10005b58:
      *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
      return param_1;
    case 2:
code_r0x10005b68:
      *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
      *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
      return param_1;
    case 3:
code_r0x10005b7c:
      *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
      *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
      *(undefined1 *)((int)puVar2 + 1) = *(undefined1 *)((int)param_2 + 1);
      return param_1;
    }
code_r0x10005b50:
    return param_1;
  }
  puVar2 = param_1;
  if (((uint)param_1 & 3) == 0) {
    uVar1 = param_3 >> 2;
    param_3 = param_3 & 3;
    if (7 < uVar1) {
      for (; uVar1 != 0; uVar1 = uVar1 - 1) {
        *puVar2 = *param_2;
        param_2 = param_2 + 1;
        puVar2 = puVar2 + 1;
      }
      switch(param_3) {
      case 0:
        return param_1;
      case 2:
        goto code_r0x100059cc;
      case 3:
        goto code_r0x100059e0;
      }
      goto code_r0x100059c0;
    }
  }
  else {
    switch(param_3) {
    case 0:
      goto code_r0x100059b8;
    case 1:
      goto code_r0x100059c0;
    case 2:
      goto code_r0x100059cc;
    case 3:
      goto code_r0x100059e0;
    default:
      uVar1 = (param_3 - 4) + ((uint)param_1 & 3);
      switch((uint)param_1 & 3) {
      case 1:
        param_3 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        *(undefined1 *)((int)param_1 + 1) = *(undefined1 *)((int)param_2 + 1);
        uVar1 = uVar1 >> 2;
        *(undefined1 *)((int)param_1 + 2) = *(undefined1 *)((int)param_2 + 2);
        param_2 = (undefined4 *)((int)param_2 + 3);
        puVar2 = (undefined4 *)((int)param_1 + 3);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar2 = *param_2;
            param_2 = param_2 + 1;
            puVar2 = puVar2 + 1;
          }
          switch(param_3) {
          case 0:
            return param_1;
          case 2:
            goto code_r0x100059cc;
          case 3:
            goto code_r0x100059e0;
          }
          goto code_r0x100059c0;
        }
        break;
      case 2:
        param_3 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        uVar1 = uVar1 >> 2;
        *(undefined1 *)((int)param_1 + 1) = *(undefined1 *)((int)param_2 + 1);
        param_2 = (undefined4 *)((int)param_2 + 2);
        puVar2 = (undefined4 *)((int)param_1 + 2);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar2 = *param_2;
            param_2 = param_2 + 1;
            puVar2 = puVar2 + 1;
          }
          switch(param_3) {
          case 0:
            return param_1;
          case 2:
            goto code_r0x100059cc;
          case 3:
            goto code_r0x100059e0;
          }
          goto code_r0x100059c0;
        }
        break;
      case 3:
        param_3 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        param_2 = (undefined4 *)((int)param_2 + 1);
        uVar1 = uVar1 >> 2;
        puVar2 = (undefined4 *)((int)param_1 + 1);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar2 = *param_2;
            param_2 = param_2 + 1;
            puVar2 = puVar2 + 1;
          }
          switch(param_3) {
          case 0:
            return param_1;
          case 2:
            goto code_r0x100059cc;
          case 3:
            goto code_r0x100059e0;
          }
          goto code_r0x100059c0;
        }
      }
    }
  }
  switch(uVar1) {
  case 7:
    puVar2[uVar1 - 7] = param_2[uVar1 - 7];
  case 6:
    puVar2[uVar1 - 6] = param_2[uVar1 - 6];
  case 5:
    puVar2[uVar1 - 5] = param_2[uVar1 - 5];
  case 4:
    puVar2[uVar1 - 4] = param_2[uVar1 - 4];
  case 3:
    puVar2[uVar1 - 3] = param_2[uVar1 - 3];
  case 2:
    puVar2[uVar1 - 2] = param_2[uVar1 - 2];
  case 1:
    puVar2[uVar1 - 1] = param_2[uVar1 - 1];
    param_2 = param_2 + uVar1;
    puVar2 = puVar2 + uVar1;
  }
  switch(param_3) {
  case 1:
code_r0x100059c0:
    *(undefined1 *)puVar2 = *(undefined1 *)param_2;
    return param_1;
  case 2:
code_r0x100059cc:
    *(undefined1 *)puVar2 = *(undefined1 *)param_2;
    *(undefined1 *)((int)puVar2 + 1) = *(undefined1 *)((int)param_2 + 1);
    return param_1;
  case 3:
code_r0x100059e0:
    *(undefined1 *)puVar2 = *(undefined1 *)param_2;
    *(undefined1 *)((int)puVar2 + 1) = *(undefined1 *)((int)param_2 + 1);
    *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
    return param_1;
  }
code_r0x100059b8:
  return param_1;
}

/* ---- 0x10005ba0  FUN_10005ba0 ---- */
void FUN_10005ba0(uint param_1,uint param_2,uint param_3,code *param_4)

{
  unsigned char _frame[0x110] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  int iVar2;
  uint uVar3;
  #define uStack_100 (*(uint *)(_frame + (0x110 - 0x100)))
  #define puStack_fc (*(uint **)(_frame + (0x110 - 0xfc)))
  #define puStack_f8 (*(uint **)(_frame + (0x110 - 0xf8)))
  #define iStack_f4 (*(int *)(_frame + (0x110 - 0xf4)))
  #define auStack_f0 (*(uint (*)[30])(_frame + (0x110 - 0xf0)))
  #define auStack_78 (*(uint (*)[30])(_frame + (0x110 - 0x78)))
  
  if ((param_2 < 2) || (param_3 == 0)) {
    return;
  }
  uStack_100 = (param_2 - 1) * param_3 + param_1;
  puStack_fc = auStack_f0;
  puStack_f8 = auStack_78;
  iStack_f4 = 0;
LAB_10005bf4:
  uVar1 = (uStack_100 - param_1) / param_3 + 1;
  if (8 < uVar1) {
    FUN_10005db0((uVar1 >> 1) * param_3 + param_1,param_1,param_3);
    uVar3 = uStack_100 + param_3;
    uVar1 = param_1;
LAB_10005c6e:
    uVar1 = uVar1 + param_3;
    if (uVar1 <= uStack_100) goto code_r0x10005c78;
    goto LAB_10005c88;
  }
  FUN_10005d50(param_1,uStack_100,param_3,param_4);
  goto LAB_10005c15;
code_r0x10005c78:
  iVar2 = (*param_4)(uVar1,param_1);
  if (iVar2 < 1) goto LAB_10005c6e;
LAB_10005c88:
  do {
    uVar3 = uVar3 - param_3;
    if (uVar3 <= param_1) break;
    iVar2 = (*param_4)(uVar3,param_1);
  } while (-1 < iVar2);
  if (uVar1 <= uVar3) {
    FUN_10005db0(uVar1,uVar3,param_3);
    goto LAB_10005c6e;
  }
  FUN_10005db0(param_1,uVar3,param_3);
  if ((int)((uVar3 - param_1) + -1) < (int)(uStack_100 - uVar1)) {
    if (uVar1 < uStack_100) {
      *puStack_f8 = uVar1;
      *puStack_fc = uStack_100;
      iStack_f4 = iStack_f4 + 1;
      puStack_f8 = puStack_f8 + 1;
      puStack_fc = puStack_fc + 1;
    }
    if (param_1 + param_3 < uVar3) {
      uStack_100 = uVar3 - param_3;
      goto LAB_10005bf4;
    }
  }
  else {
    if (param_1 + param_3 < uVar3) {
      *puStack_f8 = param_1;
      *puStack_fc = uVar3 - param_3;
      iStack_f4 = iStack_f4 + 1;
      puStack_f8 = puStack_f8 + 1;
      puStack_fc = puStack_fc + 1;
    }
    param_1 = uVar1;
    if (uVar1 < uStack_100) goto LAB_10005bf4;
  }
LAB_10005c15:
  iStack_f4 = iStack_f4 + -1;
  puStack_f8 = puStack_f8 + -1;
  puStack_fc = puStack_fc + -1;
  if (iStack_f4 < 0) {
    return;
  }
  uStack_100 = *puStack_fc;
  param_1 = *puStack_f8;
  goto LAB_10005bf4;
}
#undef auStack_78
#undef auStack_f0
#undef iStack_f4
#undef puStack_f8
#undef puStack_fc
#undef uStack_100


/* ---- 0x10005d50  FUN_10005d50 ---- */
void FUN_10005d50(uint param_1,uint param_2,int param_3,code *param_4)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  for (; uVar2 = param_1, uVar1 = param_1, param_1 < param_2; param_2 = param_2 - param_3) {
    while (uVar1 = param_3 + uVar1, uVar1 <= param_2) {
      iVar3 = (*param_4)(uVar1,uVar2);
      if (0 < iVar3) {
        uVar2 = uVar1;
      }
    }
    FUN_10005db0(uVar2,param_2,param_3);
  }
  return;
}

/* ---- 0x10005db0  FUN_10005db0 ---- */
void FUN_10005db0(undefined1 *param_1,undefined1 *param_2,int param_3)

{
  undefined1 uVar1;
  
  if (param_1 != param_2) {
    for (; param_3 != 0; param_3 = param_3 + -1) {
      uVar1 = *param_1;
      *param_1 = *param_2;
      param_1 = param_1 + 1;
      *param_2 = uVar1;
      param_2 = param_2 + 1;
    }
  }
  return;
}

/* ---- 0x10005de0  FUN_10005de0 ---- */
uint FUN_10005de0(undefined4 param_1,uint param_2,uint param_3,int param_4,code *param_5)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar3 = (param_3 - 1) * param_4 + param_2;
  bVar1 = param_2 <= uVar3;
  uVar4 = param_2;
  param_2 = uVar3;
  if (bVar1) {
    while (uVar3 = param_3 >> 1, uVar3 != 0) {
      uVar5 = uVar3;
      if ((param_3 & 1) == 0) {
        uVar5 = uVar3 - 1;
      }
      uVar5 = param_4 * uVar5 + uVar4;
      iVar2 = (*param_5)(param_1,uVar5);
      if (iVar2 == 0) {
        return uVar5;
      }
      if (iVar2 < 0) {
        param_2 = uVar5 - param_4;
        if ((param_3 & 1) == 0) {
          uVar3 = uVar3 - 1;
        }
      }
      else {
        uVar4 = uVar5 + param_4;
      }
      param_3 = uVar3;
      if (param_2 < uVar4) {
        return 0;
      }
    }
    if (param_3 != 0) {
      iVar2 = (*param_5)(param_1,uVar4);
      return ~-(uint)(iVar2 != 0) & uVar4;
    }
  }
  return 0;
}

/* ---- 0x10005e90  FUN_10005e90 ---- */
uint * FUN_10005e90(uint *param_1,char param_2)

{
  uint uVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  
  while (((uint)param_1 & 3) != 0) {
    uVar1 = *param_1;
    if ((char)uVar1 == param_2) {
      return param_1;
    }
    param_1 = (uint *)((int)param_1 + 1);
    if ((char)uVar1 == '\0') {
      return (uint *)0x0;
    }
  }
  while( true ) {
    while( true ) {
      uVar1 = *param_1;
      uVar4 = uVar1 ^ CONCAT22(CONCAT11(param_2,param_2),CONCAT11(param_2,param_2));
      uVar3 = uVar1 ^ 0xffffffff ^ uVar1 + 0x7efefeff;
      puVar5 = param_1 + 1;
      if (((uVar4 ^ 0xffffffff ^ uVar4 + 0x7efefeff) & 0x81010100) != 0) break;
      param_1 = puVar5;
      if ((uVar3 & 0x81010100) != 0) {
        if ((uVar3 & 0x1010100) != 0) {
          return (uint *)0x0;
        }
        if ((uVar1 + 0x7efefeff & 0x80000000) == 0) {
          return (uint *)0x0;
        }
      }
    }
    uVar1 = *param_1;
    if ((char)uVar1 == param_2) {
      return param_1;
    }
    if ((char)uVar1 == '\0') {
      return (uint *)0x0;
    }
    cVar2 = (char)(uVar1 >> 8);
    if (cVar2 == param_2) {
      return (uint *)((int)param_1 + 1);
    }
    if (cVar2 == '\0') {
      return (uint *)0x0;
    }
    cVar2 = (char)(uVar1 >> 0x10);
    if (cVar2 == param_2) {
      return (uint *)((int)param_1 + 2);
    }
    if (cVar2 == '\0') break;
    cVar2 = (char)(uVar1 >> 0x18);
    if (cVar2 == param_2) {
      return (uint *)((int)param_1 + 3);
    }
    param_1 = puVar5;
    if (cVar2 == '\0') {
      return (uint *)0x0;
    }
  }
  return (uint *)0x0;
}

/* ---- 0x10005f50  FUN_10005f50 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __stdcall FUN_10005f50(int a1,int a2,int a3)

{
  int iVar1;
  
  if (a2 != 1) {
    if (a2 != 0) {
      if (a2 == 3) {
        FUN_10007be0(0);
      }
      return 1;
    }
    if (0 < _DAT_100143fc) {
      _DAT_100143fc = _DAT_100143fc + -1;
      if (_DAT_100144d4 == 0) {
        FUN_100079a0();
      }
      FUN_10007ea0();
      FUN_10007b10();
      FUN_10008950();
      return 1;
    }
    return 0;
  }
  _DAT_1001449c = GetVersion();
  iVar1 = FUN_10008910();
  if (iVar1 == 0) {
    return 0;
  }
  _DAT_100144a8 = _DAT_1001449c >> 8 & 0xff;
  _DAT_100144a4 = _DAT_1001449c & 0xff;
  _DAT_100144a0 = _DAT_100144a4 * 0x100 + _DAT_100144a8;
  _DAT_1001449c = _DAT_1001449c >> 0x10;
  iVar1 = FUN_10007ab0();
  if (iVar1 == 0) {
    FUN_10008950();
    return 0;
  }
  _DAT_10015af4 = GetCommandLineA();
  _DAT_10014400 = FUN_100087b0();
  if ((_DAT_10015af4 != 0) && (_DAT_10014400 != 0)) {
    FUN_10007c90();
    FUN_100087a0();
    FUN_10007ff0();
    FUN_10007f00();
    FUN_10007950();
    _DAT_100143fc = _DAT_100143fc + 1;
    return 1;
  }
  FUN_10007b10();
  FUN_10008950();
  return 0;
}
