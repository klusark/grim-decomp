/* CHORE.DLL functions whose Ghidra decompilation went wrong when their callees' prototypes were locked (round
 * chore_naming, docs/notes/chore_naming.md "Stack purge"): the callees Cos_HandleToIndex, Cos_IndexToHandle,
 * Cos_InstIndexToHandle, CosUtil_PtrFromHandle, Cos_InitChoreInstances, Cos_AddKey, ... carry a stack purge in the Ghidra
 * project as if they popped their arguments (they are __cdecl, plain RET), which the decompiler ignored while their
 * prototypes were not locked and uses now, so the callers read their parameters at the wrong stack offsets
 * (in_stack_..., or the neighbouring parameter: Cos_InstRescue converted hCostume as the instance handle).  The bodies
 * below are the decompilation from before the prototypes were set (main 8c1f6ee, checked by the clean-room tests),
 * with the new function names; the parameters are copied into locals of the old types, and the globals are reached
 * through views of the old Ghidra types (macros below), so the code is unchanged.  Remove a function from here once
 * the purge of its callees is fixed in the Ghidra project (and the regenerated text is checked). */
#include "ghidra_types.h"

#ifdef GRIM_CHORE
#include "globals.h"
#include "functions.h"

/* the globals as the old text saw them (raw/ types of main 8c1f6ee) */
#define DAT_100143a8 (*(undefined4 *)&g_pSvcChore)
#define DAT_100143b4 (*(undefined4 *)&g_aCostumes)
#define DAT_100143c8 (*(undefined4 *)&g_nMaxInstances)
#define DAT_100143cc (*(int *)&g_aCostumeInstances)
#define PTR_100143c0 (*(int **)&g_aComponentTags)
#define DAT_10014210 (*(undefined *)&g_aTagLookups)
#define _DAT_10014210 (*(undefined4 *)&g_aTagLookups)
#define _DAT_100143b0 (*(undefined4 *)&g_nMaxCostumes)
#define _DAT_100143b8 (*(int *)&g_dwNumComponentTags)
#define _DAT_100143d8 (*(code **)&g_pfnCompNotifier)
#define _DAT_100143e0 (*(code **)&g_pfnInstanceHook)
#define _DAT_100143e4 (*(code **)&g_pfnSaveHook)

/* ==== Cos_InstRescue (0x10001000) ==== */
/* OVERRIDES: Cos_InstRescue */
int __cdecl Cos_InstRescue(int hInst_, int hCostume_)
{
  int param_1 = (int)hInst_;
  undefined4 param_2 = (undefined4)hCostume_;
  int iVar1;
  int iVar2;
  int iVar3;
  
                    /* 0x1000  43  Cos_InstRescue */
  iVar2 = Cos_HandleToIndex(param_2);
  iVar3 = iVar2;
  if (-1 < iVar2) {
    iVar3 = Cos_InstHandleToIndex(param_1);
    iVar1 = DAT_100143cc;
    if ((-1 < iVar3) && (iVar3 < DAT_100143c8)) {
      *(int *)(DAT_100143cc + iVar3 * 0x14) = iVar2;
      iVar3 = iVar1;
    }
  }
  return iVar3;
}

/* ==== CosUtil_Write (0x10001110) ==== */
/* OVERRIDES: CosUtil_Write */
int __cdecl CosUtil_Write(char * fileName_, Costume * pCostume_, char * comment_)
{
  char * param_1 = (char *)fileName_;
  int param_2 = (int)pCostume_;
  undefined4 param_3 = (undefined4)comment_;
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
  uVar3 = Cos_CollectUsedTags(param_2);
  if (_DAT_100143e4 != (code *)0x0) {
    uVar4 = ((code *)Cos_IndexToHandle)((param_2 - DAT_100143b4) / 0x3c,param_3);
    iVar10 = (*_DAT_100143e4)(param_1,uVar4);
    if (iVar10 == 0) {
      return 0;
    }
  }
  iVar10 = (**(code **)(DAT_100143a8 + 0x30))(param_1,IMG_ADDR(0x100101f4));
  if (iVar10 == 0) {
    return 0;
  }
  iVar8 = msvc_strrchr(param_1,0x5c);
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
    msvc_strncpy(param_2,param_1,0x1f);
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
    msvc_strncpy(param_2,(char *)(iVar8 + 1),0x1f);
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
                            (iVar10,IMG_ADDR(0x10010048),*puVar14,(double)PUN(float,puVar14[1]));
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

/* ==== Cos_CreateCosInstance (0x10001a80) ==== */
/* OVERRIDES: Cos_CreateCosInstance */
int __cdecl Cos_CreateCosInstance(int hCostume_, int userData_)
{
  uint * param_1 = (uint *)hCostume_;
  uint param_2 = (uint)userData_;
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
  iVar4 = Cos_HandleToIndex(param_1);
  if ((iVar4 < 0) || (_DAT_100143b0 <= iVar4)) {
    return 0;
  }
  iVar8 = DAT_100143b4 + iVar4 * 0x3c;
  iVar5 = Cos_AllocInstanceSlot();
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
  Cos_InitChoreInstances(*(undefined4 *)(iVar8 + 0x34),piVar1[1],*(undefined4 *)(iVar8 + 0x30));
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
  iVar4 = Cos_InstIndexToHandle(iVar5);
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

/* ==== Cos_RegisterComponent (0x10002080) ==== */
/* OVERRIDES: Cos_RegisterComponent */
int __cdecl Cos_RegisterComponent(uint hCostume_, char * name_, int data_, int tagId_, int parentData_, int parentTagId_, int * pStates_)
{
  uint param_1 = (uint)hCostume_;
  int param_2 = (int)name_;
  undefined4 param_3 = (undefined4)data_;
  int param_4 = (int)tagId_;
  int param_5 = (int)parentData_;
  int param_6 = (int)parentTagId_;
  undefined4 param_7 = (undefined4)pStates_;
  int iVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  
                    /* 0x2080  57  Cos_RegisterComponent */
  iVar1 = Cos_HandleToIndex(param_1);
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
    Cos_InitComponent(iVar1,iVar4,param_2,uVar2,param_3,param_1);
    *(int *)(iVar1 + 0x28) = *(int *)(iVar1 + 0x28) + 1;
    Cos_InitComponentStates(iVar4,param_7);
    if (_DAT_100143d8 != (code *)0x0) {
      (*_DAT_100143d8)(iVar1,iVar4,*(int *)(iVar1 + 0x28) + -1,1);
    }
    return 1;
  }
  return 0;
}

/* ==== Cos_RemoveComponent (0x100021f0) ==== */
/* OVERRIDES: Cos_RemoveComponent */
int __cdecl Cos_RemoveComponent(int hCostume_, int tagId_, int data_)
{
  undefined4 param_1 = (undefined4)hCostume_;
  int param_2 = (int)tagId_;
  int param_3 = (int)data_;
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

/* ==== CosUtil_DeleteComponent (0x10002260) ==== */
/* OVERRIDES: CosUtil_DeleteComponent */
int __cdecl CosUtil_DeleteComponent(uint hCostume_, uint compNum_)
{
  uint param_1 = (uint)hCostume_;
  uint param_2 = (uint)compNum_;
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
        iVar6 = Cos_FindComponent(iVar2,PTR_100143c0[*(int *)(iVar15 + 0x20) * 0x17],iVar10 + 1,iVar15);
        iVar10 = iVar10 + 2;
        while (-1 < iVar6) {
          piVar18 = (int *)(iVar6 * 0x40 + 0x28 + *(int *)(iVar2 + 0x2c));
          *piVar18 = *piVar18 + -1;
          iVar6 = Cos_FindComponent(iVar2,PTR_100143c0[*(int *)(iVar15 + 0x20) * 0x17],iVar10,iVar15);
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

/* ==== CosUtil_AddFSKey (0x10002cf0) ==== */
/* OVERRIDES: CosUtil_AddFSKey */
int __cdecl CosUtil_AddFSKey(Costume * pCostume_, uint choreNum_, int compNum_, uint time_, int value_)
{
  int param_1 = (int)pCostume_;
  undefined4 param_2 = (undefined4)choreNum_;
  int param_3 = (int)compNum_;
  undefined4 param_4 = (undefined4)time_;
  undefined4 param_5 = (undefined4)value_;
  int iVar1;
  
                    /* 0x2cf0  3  CosUtil_AddFSKey */
  if (PTR_100143c0[*(int *)(*(int *)(param_1 + 0x2c) + 0x20 + param_3 * 0x40) * 0x17 + 1] != 0) {
    return 0;
  }
  iVar1 = Cos_AddKey(param_1,param_2,param_3,param_4);
  if (iVar1 == 0) {
    return 0;
  }
  *(undefined4 *)(iVar1 + 4) = param_5;
  return 1;
}

/* ==== CosUtil_AddIntKey (0x10002d50) ==== */
/* OVERRIDES: CosUtil_AddIntKey */
int __cdecl CosUtil_AddIntKey(Costume * pCostume_, uint choreNum_, int compNum_, uint time_, int value_)
{
  int param_1 = (int)pCostume_;
  undefined4 param_2 = (undefined4)choreNum_;
  int param_3 = (int)compNum_;
  undefined4 param_4 = (undefined4)time_;
  undefined4 param_5 = (undefined4)value_;
  int iVar1;
  
                    /* 0x2d50  5  CosUtil_AddIntKey */
  if (PTR_100143c0[*(int *)(*(int *)(param_1 + 0x2c) + 0x20 + param_3 * 0x40) * 0x17 + 1] != 1) {
    return 0;
  }
  iVar1 = Cos_AddKey(param_1,param_2,param_3,param_4);
  if (iVar1 == 0) {
    return 0;
  }
  *(undefined4 *)(iVar1 + 4) = param_5;
  return 1;
}

/* ==== CosUtil_AddFloatKey (0x10002db0) ==== */
/* OVERRIDES: CosUtil_AddFloatKey */
int __cdecl CosUtil_AddFloatKey(Costume * pCostume_, uint choreNum_, int compNum_, uint time_, int value_)
{
  int param_1 = (int)pCostume_;
  undefined4 param_2 = (undefined4)choreNum_;
  int param_3 = (int)compNum_;
  undefined4 param_4 = (undefined4)time_;
  undefined4 param_5 = (undefined4)value_;
  int iVar1;
  
                    /* 0x2db0  4  CosUtil_AddFloatKey */
  if (PTR_100143c0[*(int *)(*(int *)(param_1 + 0x2c) + 0x20 + param_3 * 0x40) * 0x17 + 1] != 2) {
    return 0;
  }
  iVar1 = Cos_AddKey(param_1,param_2,param_3,param_4);
  if (iVar1 == 0) {
    return 0;
  }
  *(undefined4 *)(iVar1 + 4) = param_5;
  return 1;
}

/* ==== Cos_FreeCostume (0x10004c70) ==== */
/* OVERRIDES: Cos_FreeCostume */
void __cdecl Cos_FreeCostume(int hCostume_)
{
  undefined4 param_1 = (undefined4)hCostume_;
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
      Cos_FreeComponent(param_1,PTR_100143c0 + *(int *)(iVar2 + 0x20) * 0x17,iVar2);
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
  iVar1 = Cos_HandleToIndex(param_1);
  *(undefined4 *)(DAT_100143b4 + 0x38 + iVar1 * 0x3c) = 1;
  return;
}

/* ==== Cos_FreeInstanceData (0x10004f70) ==== */
/* OVERRIDES: Cos_FreeInstanceData */
void __cdecl Cos_FreeInstanceData(int instIndex_)
{
  int param_1 = (int)instIndex_;
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
  uVar6 = Cos_InstIndexToHandle(param_1);
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

#endif /* GRIM_CHORE */
