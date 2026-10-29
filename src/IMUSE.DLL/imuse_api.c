/* IMUSE.DLL :: imuse_api.c
 * functions 0x10003d70 .. 0x1000d1f0 (113 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10003d70  ImInitFilelist ---- */
undefined4
ImInitFilelist(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  
                    /* 0x3d70  14  ImInitFilelist */
  DAT_1002dcf0 = param_1;
  DAT_1002dcf4 = param_2;
  DAT_1002dae4 = param_4;
  DAT_1002dae0 = param_3;
  puVar1 = (undefined4 *)IMG_ADDR(0x1002daec);
  do {
    puVar1[-1] = 0;
    *puVar1 = 0;
    puVar1[1] = 0;
    puVar1 = puVar1 + 0xd;
  } while ((int)puVar1 < IMG_ADDR(0x1002dcf4));
  DAT_1002dd00 = 1;
  return 0;
}

/* ---- 0x10003dc0  ImSaveFilelist ---- */
int ImSaveFilelist(int *param_1,uint param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  undefined4 *puVar6;
  int *piVar7;
  undefined4 *puVar8;
  int *piVar9;
  
  puVar1 = DAT_1002dcf8;
                    /* 0x3dc0  29  ImSaveFilelist */
  if (0x20f < param_2) {
    iVar2 = 8;
    *param_1 = 0;
    piVar4 = PTR_1002dcfc;
    for (; PTR_1002dcfc = piVar4, puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)puVar1[1]) {
      *param_1 = *param_1 + 1;
      puVar6 = puVar1;
      puVar8 = (undefined4 *)(iVar2 + (int)param_1);
      for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar8 = *puVar6;
        puVar6 = puVar6 + 1;
        puVar8 = puVar8 + 1;
      }
      iVar2 = iVar2 + 0x34;
      piVar4 = PTR_1002dcfc;
    }
    param_1[1] = 0;
    if (piVar4 != (int *)0x0) {
      piVar5 = (int *)(iVar2 + (int)param_1);
      do {
        param_1[1] = param_1[1] + 1;
        piVar7 = piVar4;
        piVar9 = piVar5;
        for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
          *piVar9 = *piVar7;
          piVar7 = piVar7 + 1;
          piVar9 = piVar9 + 1;
        }
        piVar4 = (int *)piVar4[1];
        iVar2 = iVar2 + 0x34;
        piVar5 = piVar5 + 0xd;
      } while (piVar4 != (int *)0x0);
    }
    return iVar2;
  }
  ImPrintf(IMG_ADDR(0x10017124));
  return 0;
}

/* ---- 0x10003e50  ImRestoreFilelist ---- */
int ImRestoreFilelist(int *param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
                    /* 0x3e50  25  ImRestoreFilelist */
  piVar1 = param_1;
  puVar2 = (undefined4 *)IMG_ADDR(0x1002daec);
  do {
    puVar2[-1] = 0;
    *puVar2 = 0;
    puVar2[1] = 0;
    puVar2 = puVar2 + 0xd;
  } while ((int)puVar2 < IMG_ADDR(0x1002dcf4));
  iVar6 = *param_1;
  iVar4 = param_1[1];
  iVar5 = 8;
  while (iVar6 != 0) {
    iVar6 = iVar6 + -1;
    iVar3 = ImLoadSound((int)param_1 + iVar5 + 0xc,*(undefined4 *)(iVar5 + 8 + (int)param_1));
    if (iVar3 == 0) {
      ImPrintf(IMG_ADDR(0x10017144));
      ImPrintf((int)param_1 + iVar5 + 0xc);
      ImPrintf(&DAT_100171b0);
      return 0;
    }
    if (*(int *)((int)param_1 + iVar5 + 8) != *(int *)(DAT_1002dcf8 + 8)) goto LAB_10003f3a;
    *(undefined4 *)(DAT_1002dcf8 + 0x30) = *(undefined4 *)((int)param_1 + iVar5 + 0x30);
    iVar5 = iVar5 + 0x34;
  }
  param_1 = (int *)iVar4;
  if (iVar4 == 0) {
    return iVar5;
  }
  while( true ) {
    param_1 = (int *)((int)param_1 + -1);
    iVar3 = iVar5 + 0x34;
    iVar6 = (int)piVar1 + iVar5 + 0xc;
    iVar4 = ImOpenSound(iVar6,*(undefined4 *)(iVar5 + 8 + (int)piVar1));
    if (iVar4 == 0) {
      ImPrintf(IMG_ADDR(0x100171b4));
      ImPrintf(iVar6);
      ImPrintf(&DAT_100171b0);
    }
    if (*(int *)((int)piVar1 + iVar5 + 8) != PTR_1002dcfc[2]) break;
    PTR_1002dcfc[0xc] = *(int *)((int)piVar1 + iVar5 + 0x30);
    iVar5 = iVar3;
    if (param_1 == (int *)0x0) {
      return iVar3;
    }
  }
LAB_10003f3a:
  ImPrintf(IMG_ADDR(0x10017174));
  return 0;
}

/* ---- 0x10003f90  ImLoadSound ---- */
int ImLoadSound(char *param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  undefined4 uVar5;
  
                    /* 0x3f90  17  ImLoadSound */
  if ((((DAT_1002dd00 != 0) && (*param_1 != '\0')) && (DAT_1002dcf0 != (code *)0x0)) &&
     (DAT_1002dcf4 != 0)) {
    iVar2 = ImFindSound(param_1);
    iVar3 = DAT_1002dcf8;
    if (iVar2 != 0) {
      for (; iVar3 != 0; iVar3 = *(int *)(iVar3 + 4)) {
        if (iVar2 == *(int *)(iVar3 + 8)) {
          *(int *)(iVar3 + 0x30) = *(int *)(iVar3 + 0x30) + 1;
          return iVar2;
        }
      }
    }
    piVar4 = (int *)IMG_ADDR(0x1002dae8);
    while (piVar4[2] != 0) {
      piVar4 = piVar4 + 0xd;
      if (IMG_ADDR(0x1002dcef) < (int)piVar4) {
        ImPrintf(IMG_ADDR(0x10017210));
        return 0;
      }
    }
    iVar3 = (*DAT_1002dcf0)(param_1,param_2);
    if (iVar3 == 0) {
      uVar5 = IMG_ADDR(0x100171f4);
    }
    else {
      cVar1 = *param_1;
      iVar2 = 0;
      while( true ) {
        if (cVar1 == '\0') {
          *(undefined1 *)(iVar2 + 0xc + (int)piVar4) = 0;
          piVar4[2] = iVar3;
          piVar4[0xc] = 1;
          FUN_10004460(&DAT_1002dcf8,piVar4);
          return iVar3;
        }
        if (0x1f < iVar2) break;
        *(char *)(iVar2 + 0xc + (int)piVar4) = param_1[iVar2];
        cVar1 = param_1[iVar2 + 1];
        iVar2 = iVar2 + 1;
      }
      uVar5 = IMG_ADDR(0x100171e4);
    }
    ImPrintf(uVar5);
    ImPrintf(param_1);
    ImPrintf(&DAT_100171b0);
    return 0;
  }
  return 0;
}

/* ---- 0x100040b0  ImUnloadSound ---- */
undefined4 __cdecl ImUnloadSound(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
                    /* 0x40b0  49  ImUnloadSound */
  if (((DAT_1002dd00 == 0) || (DAT_1002dcf0 == 0)) || (iVar1 = DAT_1002dcf8, DAT_1002dcf4 == 0)) {
    return DAT_1002dcf8;
  }
  do {
    if (iVar1 == 0) {
LAB_100040f4:
      uVar2 = ImFlushSounds();
      return uVar2;
    }
    if (*(int *)(iVar1 + 8) == param_1) {
      if (*(int *)(iVar1 + 0x30) != 0) {
        *(int *)(iVar1 + 0x30) = *(int *)(iVar1 + 0x30) + -1;
      }
      goto LAB_100040f4;
    }
    iVar1 = *(int *)(iVar1 + 4);
  } while( true );
}

/* ---- 0x10004100  ImUnloadAll ---- */
undefined4 __cdecl ImUnloadAll(void)

{
  int iVar1;
  undefined4 uVar2;
  
                    /* 0x4100  48  ImUnloadAll */
  if (((DAT_1002dd00 != 0) && (DAT_1002dcf0 != 0)) && (iVar1 = DAT_1002dcf8, DAT_1002dcf4 != 0)) {
    for (; iVar1 != 0; iVar1 = *(int *)(iVar1 + 4)) {
      *(undefined4 *)(iVar1 + 0x30) = 0;
    }
    uVar2 = ImFlushSounds();
    return uVar2;
  }
  return DAT_1002dcf8;
}

/* ---- 0x10004140  ImOpenSound ---- */
int ImOpenSound(char *param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  undefined4 uVar5;
  
                    /* 0x4140  18  ImOpenSound */
  if ((((DAT_1002dd00 != 0) && (*param_1 != '\0')) && (DAT_1002dae0 != (code *)0x0)) &&
     (DAT_1002dae4 != 0)) {
    iVar2 = ImFindSound(param_1);
    piVar4 = PTR_1002dcfc;
    if (iVar2 != 0) {
      for (; piVar4 != (int *)0x0; piVar4 = (int *)piVar4[1]) {
        if (iVar2 == piVar4[2]) {
          piVar4[0xc] = piVar4[0xc] + 1;
          return iVar2;
        }
      }
    }
    piVar4 = (int *)IMG_ADDR(0x1002dae8);
    while (piVar4[2] != 0) {
      piVar4 = piVar4 + 0xd;
      if (IMG_ADDR(0x1002dcef) < (int)piVar4) {
        ImPrintf(IMG_ADDR(0x10017210));
        return 0;
      }
    }
    iVar2 = (*DAT_1002dae0)(param_1,param_2);
    if (iVar2 == 0) {
      uVar5 = IMG_ADDR(0x10017224);
    }
    else {
      cVar1 = *param_1;
      iVar3 = 0;
      while( true ) {
        if (cVar1 == '\0') {
          *(undefined1 *)(iVar3 + 0xc + (int)piVar4) = 0;
          piVar4[2] = iVar2;
          piVar4[0xc] = 1;
          FUN_10004460((int *)&PTR_1002dcfc,piVar4);
          return iVar2;
        }
        if (0x1f < iVar3) break;
        *(char *)(iVar3 + 0xc + (int)piVar4) = param_1[iVar3];
        cVar1 = param_1[iVar3 + 1];
        iVar3 = iVar3 + 1;
      }
      uVar5 = IMG_ADDR(0x100171e4);
    }
    ImPrintf(uVar5);
    ImPrintf(param_1);
    ImPrintf(&DAT_100171b0);
    return 0;
  }
  return 0;
}

/* ---- 0x10004260  ImCloseSound ---- */
undefined4 __cdecl ImCloseSound(int param_1)

{
  int *piVar1;
  undefined4 uVar2;
  
                    /* 0x4260  4  ImCloseSound */
  if (((DAT_1002dd00 == 0) || (DAT_1002dae0 == 0)) || (piVar1 = PTR_1002dcfc, DAT_1002dae4 == 0)) {
    return PTR_1002dcfc;
  }
  do {
    if (piVar1 == (int *)0x0) {
LAB_100042a4:
      uVar2 = ImFlushSounds();
      return uVar2;
    }
    if (piVar1[2] == param_1) {
      if (piVar1[0xc] != 0) {
        piVar1[0xc] = piVar1[0xc] + -1;
      }
      goto LAB_100042a4;
    }
    piVar1 = (int *)piVar1[1];
  } while( true );
}

/* ---- 0x100042b0  ImCloseAll ---- */
undefined4 __cdecl ImCloseAll(void)

{
  int *piVar1;
  undefined4 uVar2;
  
                    /* 0x42b0  3  ImCloseAll */
  if (((DAT_1002dd00 != 0) && (DAT_1002dae0 != 0)) && (piVar1 = PTR_1002dcfc, DAT_1002dae4 != 0)) {
    for (; piVar1 != (int *)0x0; piVar1 = (int *)piVar1[1]) {
      piVar1[0xc] = 0;
    }
    uVar2 = ImFlushSounds();
    return uVar2;
  }
  return PTR_1002dcfc;
}

/* ---- 0x100042f0  ImFindSound ---- */
int ImFindSound(char *param_1)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  
                    /* 0x42f0  8  ImFindSound */
  if (DAT_1002dcf8 != (int *)0x0) {
    piVar3 = DAT_1002dcf8;
    do {
      cVar1 = *param_1;
      for (iVar2 = 0; (cVar1 != '\0' && (*(char *)(iVar2 + 0xc + (int)piVar3) == cVar1));
          iVar2 = iVar2 + 1) {
        cVar1 = param_1[iVar2];
      }
      if (((iVar2 != 0) && (param_1[iVar2] == '\0')) &&
         (*(char *)(iVar2 + 0xc + (int)piVar3) == '\0')) goto LAB_10004371;
      piVar3 = (int *)piVar3[1];
    } while (piVar3 != (int *)0x0);
  }
  if (PTR_1002dcfc == (int *)0x0) {
    return 0;
  }
  piVar3 = PTR_1002dcfc;
  while( true ) {
    cVar1 = *param_1;
    for (iVar2 = 0; (cVar1 != '\0' && (*(char *)(iVar2 + 0xc + (int)piVar3) == cVar1));
        iVar2 = iVar2 + 1) {
      cVar1 = param_1[iVar2];
    }
    if (((iVar2 != 0) && (param_1[iVar2] == '\0')) && (*(char *)(iVar2 + 0xc + (int)piVar3) == '\0')
       ) break;
    piVar3 = (int *)piVar3[1];
    if (piVar3 == (int *)0x0) {
      return 0;
    }
  }
LAB_10004371:
  return piVar3[2];
}

/* ---- 0x10004380  ImFlushSounds ---- */
uint __cdecl ImFlushSounds(void)

{
  int *piVar1;
  int *piVar2;
  uint in_EAX;
  
  piVar1 = DAT_1002dcf8;
  while (piVar2 = piVar1, piVar1 = PTR_1002dcfc, piVar2 != (int *)0x0) {
    in_EAX = piVar2[0xc];
    piVar1 = (int *)piVar2[1];
    if (((in_EAX == 0) && (in_EAX = ImGetParam(piVar2[2],0x100), in_EAX == 0)) &&
       (in_EAX = ImGetParam(piVar2[2],0x200), in_EAX == 0)) {
      if (DAT_1002dcf4 != (code *)0x0) {
        (*DAT_1002dcf4)(piVar2[2]);
      }
      piVar2[2] = 0;
      in_EAX = FUN_100044b0((int *)&DAT_1002dcf8,piVar2);
    }
  }
  while (piVar2 = piVar1, piVar2 != (int *)0x0) {
    in_EAX = piVar2[0xc];
    piVar1 = (int *)piVar2[1];
    if (((in_EAX == 0) && (in_EAX = ImGetParam(piVar2[2],0x100), in_EAX == 0)) &&
       (in_EAX = ImGetParam(piVar2[2],0x200), in_EAX == 0)) {
      if (DAT_1002dae4 != (code *)0x0) {
        (*DAT_1002dae4)(piVar2[2]);
      }
      piVar2[2] = 0;
      in_EAX = FUN_100044b0((int *)&PTR_1002dcfc,piVar2);
    }
  }
  return in_EAX;
}

/* ---- 0x10004460  FUN_10004460 ---- */
undefined4 __cdecl FUN_10004460(int *param_1,int *param_2)

{
  if (((param_2 != (int *)0x0) && (*param_2 == 0)) && (param_2[1] == 0)) {
    param_2[1] = *param_1;
    if ((undefined4 *)*param_1 != (undefined4 *)0x0) {
      *(undefined4 *)*param_1 = param_2;
    }
    *param_2 = 0;
    *param_1 = (int)param_2;
    return 0;
  }
  ImPrintf(IMG_ADDR(0x10017240));
  return 0xfffffffb;
}

/* ---- 0x100044b0  FUN_100044b0 ---- */
undefined4 __cdecl FUN_100044b0(int *param_1,int *param_2)

{
  int *piVar1;
  
  piVar1 = (int *)*param_1;
  if ((param_2 == (int *)0x0) || (piVar1 == (int *)0x0)) {
    ImPrintf(IMG_ADDR(0x10017268));
    return 0xfffffffb;
  }
  do {
    if (piVar1 == param_2) break;
    piVar1 = (int *)piVar1[1];
  } while (piVar1 != (int *)0x0);
  if (piVar1 == (int *)0x0) {
    ImPrintf(IMG_ADDR(0x10017290));
    return 0xfffffffd;
  }
  if ((int *)param_2[1] != (int *)0x0) {
    *(int *)param_2[1] = *param_2;
  }
  if (*param_2 != 0) {
    *(int *)(*param_2 + 4) = param_2[1];
    param_2[1] = 0;
    *param_2 = 0;
    return 0;
  }
  *param_1 = param_2[1];
  param_2[1] = 0;
  *param_2 = 0;
  return 0;
}

/* ---- 0x10004aa0  ImInitialize ---- */
undefined4 ImInitialize(void)

{
  int iVar1;
  
                    /* 0x4aa0  15  ImInitialize */
  if (DAT_1002df0c == 0) {
    DAT_1002df04 = 0;
    DAT_1002df08 = 0;
    iVar1 = Im_GroupsInit();
    if (iVar1 == 0) {
      iVar1 = Im_DSoundReset();
      if (iVar1 == 0) {
        iVar1 = Im_TriggersInit();
        if (iVar1 == 0) {
          iVar1 = Im_InitSubsystems();
          if (iVar1 == 0) {
            DAT_100172c0 = 0;
            DAT_1002df10 = 0;
            DAT_1002df00 = 0;
            DAT_1002df0c = 1;
            return 0x31;
          }
        }
      }
    }
  }
  return 0xffffffff;
}

/* ---- 0x10004b20  ImPrintf ---- */
undefined4 ImPrintf(undefined4 param_1)

{
                    /* 0x4b20  20  ImPrintf */
  FUN_1000b8d0((undefined1 *)IMG_ADDR(0x1002de00),param_1,&STACK0X(0x00000008));
  return 0;
}

/* ---- 0x10004b40  ImPause ---- */
int ImPause(void)

{
  int iVar1;
  bool bVar2;
  
                    /* 0x4b40  19  ImPause */
  iVar1 = DAT_1002df00 + 1;
  bVar2 = DAT_1002df00 == 0;
  DAT_1002df00 = iVar1;
  if (bVar2) {
    Im_PauseImpl();
  }
  return DAT_1002df00;
}

/* ---- 0x10004b60  ImResume ---- */
int ImResume(void)

{
                    /* 0x4b60  27  ImResume */
  DAT_1002df00 = DAT_1002df00 + -1;
  if (DAT_1002df00 == 0) {
    Im_ResumeImpl();
    return DAT_1002df00;
  }
  if (DAT_1002df00 < 0) {
    DAT_1002df00 = 0;
  }
  return DAT_1002df00;
}

/* ---- 0x10004ba0  ImSave ---- */
int __cdecl ImSave(undefined4 *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
                    /* 0x4ba0  28  ImSave */
  if (param_2 < 80000) {
    return -1;
  }
  *param_1 = 0x31;
  iVar1 = Im_DSoundSave(param_1 + 1,param_2 - 4);
  if (-1 < iVar1) {
    iVar2 = iVar1 + 4;
    iVar1 = Im_TriggersSave((undefined4 *)(iVar2 + (int)param_1),param_2 - iVar2);
    if (-1 < iVar1) {
      iVar2 = iVar2 + iVar1;
      iVar1 = Im_SaveImpl((undefined4 *)(iVar2 + (int)param_1),param_2 - iVar2);
      if (-1 < iVar1) {
        iVar1 = iVar2 + iVar1;
      }
    }
  }
  return iVar1;
}

/* ---- 0x10004c10  ImRestore ---- */
int __cdecl ImRestore(int *param_1)

{
  int iVar1;
  int iVar2;
  
                    /* 0x4c10  24  ImRestore */
  ImStopAllSounds();
  if (*param_1 != 0x31) {
    return -1;
  }
  iVar1 = Im_DSoundRestore(param_1 + 1);
  iVar2 = Im_TriggersRestore((undefined4 *)(iVar1 + 4 + (int)param_1));
  iVar2 = iVar1 + 4 + iVar2;
  iVar1 = Im_RestoreImpl((undefined4 *)(iVar2 + (int)param_1));
  return iVar2 + iVar1;
}

/* ---- 0x10004c60  ImSetGroupVol ---- */
undefined4 __cdecl ImSetGroupVol(uint param_1,uint param_2)

{
  undefined4 uVar1;
  
                    /* 0x4c60  33  ImSetGroupVol */
  uVar1 = Im_SetGroupVolImpl(param_1,param_2);
  return uVar1;
}

/* ---- 0x10004c80  ImStartSound ---- */
undefined4 __cdecl ImStartSound(uint param_1,int param_2)

{
  char *pcVar1;
  int iVar2;
  undefined4 uVar3;
  char *pcVar4;
  bool bVar5;
  
                    /* 0x4c80  40  ImStartSound */
  uVar3 = 0xffffffff;
  pcVar1 = (char *)iMUSE_dsound__4570(param_1);
  if (pcVar1 == (char *)0x0) {
    return 0xffffffff;
  }
  iVar2 = 4;
  bVar5 = true;
  pcVar4 = (char *)&DAT_10017074;
  do {
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    bVar5 = *pcVar1 == *pcVar4;
    pcVar1 = pcVar1 + 1;
    pcVar4 = pcVar4 + 1;
  } while (bVar5);
  if (bVar5) {
    uVar3 = Im_StartSoundImpl(param_1,param_2,0);
  }
  return uVar3;
}

/* ---- 0x10004cd0  ImStopSound ---- */
undefined4 __cdecl ImStopSound(int param_1)

{
  undefined4 uVar1;
  
                    /* 0x4cd0  44  ImStopSound */
  uVar1 = Im_StopSoundImpl(param_1);
  return uVar1;
}

/* ---- 0x10004ce0  ImStopAllSounds ---- */
undefined4 ImStopAllSounds(void)

{
  undefined4 uVar1;
  
                    /* 0x4ce0  42  ImStopAllSounds */
  ((code *)Im_GuardEnter)();
  uVar1 = Im_StopAllSoundsImpl();
  Im_GuardLeave();
  return uVar1;
}

/* ---- 0x10004d00  ImGetNextSound ---- */
uint __cdecl ImGetNextSound(uint param_1)

{
  uint uVar1;
  
                    /* 0x4d00  11  ImGetNextSound */
  uVar1 = Im_GetNextSoundImpl(param_1);
  return uVar1;
}

/* ---- 0x10004d10  ImSetParam ---- */
undefined4 __cdecl ImSetParam(int param_1,int param_2,uint param_3)

{
  undefined4 uVar1;
  
                    /* 0x4d10  35  ImSetParam */
  uVar1 = Im_SetParamImpl(param_1,param_2,param_3);
  return uVar1;
}

/* ---- 0x10004d30  ImGetParam ---- */
uint __cdecl ImGetParam(int param_1,int param_2)

{
  uint uVar1;
  
                    /* 0x4d30  12  ImGetParam */
  if (param_2 == 0) {
    return 2;
  }
  if (param_2 == 0x200) {
    uVar1 = Im_GetTriggerParam(param_1);
    return uVar1;
  }
  Im_GuardEnter();
  uVar1 = Im_GetParamImpl(param_1,param_2);
  Im_GuardLeave();
  if (((int)uVar1 < 0) && (param_2 == 0x100)) {
    return 0;
  }
  return uVar1;
}

/* ---- 0x10004d90  ImFadeParam ---- */
undefined4 __cdecl ImFadeParam(int param_1,int param_2,uint param_3,int param_4)

{
  undefined4 uVar1;
  
                    /* 0x4d90  6  ImFadeParam */
  uVar1 = Im_FadeParamImpl(param_1,param_2,param_3,param_4);
  return uVar1;
}

/* ---- 0x10004db0  ImSetHook ---- */
undefined4 __cdecl ImSetHook(int param_1,uint param_2)

{
  undefined4 uVar1;
  
                    /* 0x4db0  34  ImSetHook */
  uVar1 = Im_SetHookImpl(param_1,param_2);
  return uVar1;
}

/* ---- 0x10004dd0  ImGetHook ---- */
undefined4 __cdecl ImGetHook(int param_1)

{
  undefined4 uVar1;
  
                    /* 0x4dd0  10  ImGetHook */
  uVar1 = Im_GetHookImpl(param_1);
  return uVar1;
}

/* ---- 0x10004de0  ImSetTrigger ---- */
undefined4 __cdecl ImSetTrigger(int param_1,char *param_2,int param_3)

{
  undefined4 uVar1;
  
                    /* 0x4de0  38  ImSetTrigger */
  uVar1 = Im_SetTriggerImpl(param_1,param_2,param_3);
  return uVar1;
}

/* ---- 0x10004e10  ImCheckTrigger ---- */
int __cdecl ImCheckTrigger(int param_1,byte *param_2,int param_3)

{
  int iVar1;
  
                    /* 0x4e10  1  ImCheckTrigger */
  iVar1 = Im_CheckTriggerImpl(param_1,param_2,param_3);
  return iVar1;
}

/* ---- 0x10004e30  ImClearTrigger ---- */
undefined4 __cdecl ImClearTrigger(int param_1,byte *param_2,int param_3)

{
  undefined4 uVar1;
  
                    /* 0x4e30  2  ImClearTrigger */
  uVar1 = Im_ClearTriggerImpl(param_1,param_2,param_3);
  return uVar1;
}

/* ---- 0x10004e50  ImDeferCommand ---- */
undefined4 __cdecl ImDeferCommand(int param_1,int param_2)

{
  undefined4 uVar1;
  
                    /* 0x4e50  5  ImDeferCommand */
  uVar1 = Im_DeferCommandImpl(param_1,param_2);
  return uVar1;
}

/* ---- 0x10004e80  ImStartStream ---- */
undefined4 __cdecl ImStartStream(uint param_1,int param_2,uint param_3)

{
  int iVar1;
  undefined4 uVar2;
  
                    /* 0x4e80  41  ImStartStream */
  iVar1 = iMUSE_dsound__45a0(param_1);
  if (iVar1 != 0) {
    Im_GuardEnter();
    uVar2 = Im_StartSoundImpl(param_1,param_2,param_3);
    Im_GuardLeave();
    return uVar2;
  }
  return 0xffffffff;
}

/* ---- 0x10004ec0  ImSwitchStream ---- */
undefined4 __cdecl
ImSwitchStream(int param_1,undefined4 param_2,uint param_3,uint param_4,uint param_5)

{
  undefined4 uVar1;
  
                    /* 0x4ec0  45  ImSwitchStream */
  uVar1 = Im_SwitchStreamImpl(param_1,param_2,param_3,param_4,param_5);
  return uVar1;
}

/* ---- 0x10004f00  ImQueryStream ---- */
undefined4 __cdecl
ImQueryStream(int param_1,undefined4 *param_2,undefined4 *param_3,int *param_4,undefined4 *param_5)

{
  undefined4 uVar1;
  
                    /* 0x4f00  22  ImQueryStream */
  uVar1 = Im_QueryStreamImpl(param_1,param_2,param_3,param_4,param_5);
  return uVar1;
}

/* ---- 0x10004f30  ImFeedStream ---- */
undefined4 __cdecl ImFeedStream(int param_1,undefined4 *param_2,uint param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
                    /* 0x4f30  7  ImFeedStream */
  uVar1 = Im_FeedStreamImpl(param_1,param_2,param_3,param_4);
  return uVar1;
}

/* ---- 0x10005190  ImHeartbeat ---- */
uint __cdecl ImHeartbeat(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
                    /* 0x5190  13  ImHeartbeat */
  uVar1 = timeGetTime();
  if (((DAT_1002df10 == 0) && (DAT_100172c0 == 0)) &&
     (((int)DAT_100172bc < 0 || (0x13 < uVar1 - DAT_100172bc)))) {
    DAT_1002df10 = 1;
    DAT_100172bc = uVar1;
    Im_HeartbeatBody();
    uVar1 = DAT_1002df00;
    if (DAT_1002df00 == 0) {
      DAT_1002df04 = DAT_1002df04 + 20000;
      while (19999 < DAT_1002df04) {
        DAT_1002df04 = DAT_1002df04 - 20000;
        Im_FadesHeartbeat();
        Im_ProcessDeferred();
      }
      uVar1 = DAT_1002df08 + 20000;
      DAT_1002df08 = uVar1;
joined_r0x1000522c:
      if (199999 < DAT_1002df08) {
        DAT_1002df08 = DAT_1002df08 - 200000;
        uVar2 = Im_SetGroupVolImpl(3,0xffffffff);
        for (uVar1 = ImGetNextSound(0); uVar1 != 0; uVar1 = ImGetNextSound(uVar1)) {
          uVar3 = ImGetParam(uVar1,0x400);
          if (uVar3 == 2) {
            uVar2 = uVar2 * 0x4d >> 7;
            break;
          }
        }
        uVar3 = Im_SetGroupVolImpl(4,0xffffffff);
        uVar1 = Im_SetGroupVolImpl(3,0xffffffff);
        if (uVar3 <= uVar2) goto LAB_100052c3;
        uVar3 = uVar3 - 0x24;
        if (uVar3 <= uVar2) {
          if (uVar1 <= uVar2) goto LAB_100052d8;
          goto LAB_100052d6;
        }
        if (uVar3 < uVar1) {
          uVar1 = uVar3;
        }
        goto LAB_100052d8;
      }
    }
    DAT_1002df10 = 0;
  }
  return uVar1;
LAB_100052c3:
  if (uVar3 < uVar2) {
    uVar3 = uVar3 + 1;
    if (uVar3 < uVar2) {
      if (uVar1 < uVar3) {
        uVar1 = uVar3;
      }
    }
    else if (uVar1 < uVar2) {
LAB_100052d6:
      uVar1 = uVar2;
    }
LAB_100052d8:
    uVar1 = Im_SetGroupVolImpl(4,uVar1);
  }
  goto joined_r0x1000522c;
}

/* ---- 0x10005300  ImStartRecording ---- */
undefined4 ImStartRecording(undefined4 param_1,int param_2)

{
                    /* 0x5300  39  ImStartRecording */
  DAT_1002df64 = (int *)((code *)FUN_1000ba60)(param_1,IMG_ADDR(0x100172c4));
  if (DAT_1002df64 == (int *)0x0) {
    DAT_1002df60 = 0;
  }
  else {
    DAT_1002df60 = 2 - (uint)(param_2 != 0);
  }
  DAT_1002df1c = 0;
  ImFile_Read(DAT_1002df64,0x2c,0);
  return 0;
}

/* ---- 0x10005350  ImStopRecording ---- */
undefined4 ImStopRecording(void)

{
                    /* 0x5350  43  ImStopRecording */
  DAT_1002df60 = 3;
  return 0;
}

/* ---- 0x10007130  ImInitializeScript ---- */
undefined4 __cdecl ImInitializeScript(int a1,int a2,int a3,int a4,int a5,int a6,int a7)

{
  undefined4 uVar1;
  
                    /* 0x7130  16  ImInitializeScript */
  uVar1 = FUN_10006070(0,&DAT_100336a0,a1,a2,a3,a4,a5,a6,a7);
  return uVar1;
}

/* ---- 0x10007170  ImTerminateScript ---- */
undefined4 __cdecl ImTerminateScript(void)

{
  undefined4 uVar1;
  
                    /* 0x7170  47  ImTerminateScript */
  uVar1 = FUN_10006070(1);
  return uVar1;
}

/* ---- 0x10007180  ImSaveScript ---- */
undefined4 __cdecl ImSaveScript(int a1,int a2)

{
  undefined4 uVar1;
  
                    /* 0x7180  30  ImSaveScript */
  uVar1 = FUN_10006070(2,a1,a2);
  return uVar1;
}

/* ---- 0x100071a0  ImRestoreScript ---- */
undefined4 __cdecl ImRestoreScript(int a1)

{
  undefined4 uVar1;
  
                    /* 0x71a0  26  ImRestoreScript */
  uVar1 = FUN_10006070(3,a1);
  return uVar1;
}

/* ---- 0x100071b0  ImRefreshScript ---- */
undefined4 __cdecl ImRefreshScript(void)

{
  undefined4 uVar1;
  
                    /* 0x71b0  23  ImRefreshScript */
  uVar1 = FUN_10006070(4);
  return uVar1;
}

/* ---- 0x100071c0  ImSetState ---- */
undefined4 __cdecl ImSetState(int a1)

{
  undefined4 uVar1;
  
                    /* 0x71c0  37  ImSetState */
  uVar1 = FUN_10006070(5,a1);
  return uVar1;
}

/* ---- 0x100071d0  ImSetSequence ---- */
undefined4 __cdecl ImSetSequence(int a1)

{
  undefined4 uVar1;
  
                    /* 0x71d0  36  ImSetSequence */
  uVar1 = FUN_10006070(6,a1);
  return uVar1;
}

/* ---- 0x100071e0  ImSetCuePoint ---- */
undefined4 __cdecl ImSetCuePoint(int a1)

{
  undefined4 uVar1;
  
                    /* 0x71e0  32  ImSetCuePoint */
  uVar1 = FUN_10006070(7,a1);
  return uVar1;
}

/* ---- 0x100071f0  ImSetAttribute ---- */
undefined4 __cdecl ImSetAttribute(int a1,int a2)

{
  undefined4 uVar1;
  
                    /* 0x71f0  31  ImSetAttribute */
  uVar1 = FUN_10006070(8,a1,a2);
  return uVar1;
}

/* ---- 0x10007210  SoundsAllocateBuffer ---- */
undefined4 __cdecl
SoundsAllocateBuffer(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  
                    /* 0x7210  53  SoundsAllocateBuffer */
  iVar2 = param_1 * 0x10;
  uVar1 = (**(code **)(DAT_10033510 + 0x20))
                    (param_2,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0x11d);
  *(undefined4 *)(iVar2 + IMG_ADDR(0x1002ebe4)) = param_2;
  *(undefined4 *)(iVar2 + IMG_ADDR(0x1002ebe0)) = uVar1;
  *(undefined4 *)(iVar2 + IMG_ADDR(0x1002ebe8)) = param_3;
  *(undefined4 *)(iVar2 + IMG_ADDR(0x1002ebec)) = param_4;
  return uVar1;
}

/* ---- 0x10007250  FUN_10007250 ---- */
undefined4 __cdecl FUN_10007250(int param_1)

{
  int iVar1;
  
  iVar1 = (param_1 + -10000) * 0x28;
  if (*(undefined4 **)(&DAT_1002eb10 + iVar1) == (undefined4 *)0x0) {
    return 1;
  }
  if (*(int *)(iVar1 + IMG_ADDR(0x1002eb34)) < 2) {
    Im_SoundsUnload(*(undefined4 **)(&DAT_1002eb10 + iVar1));
    *(undefined4 *)(&DAT_1002eb10 + iVar1) = 0;
    *(undefined1 *)(iVar1 + IMG_ADDR(0x1002eb14)) = 0;
    *(undefined4 *)(iVar1 + IMG_ADDR(0x1002eb34)) = 0;
    return 0;
  }
  *(int *)(iVar1 + IMG_ADDR(0x1002eb34)) = *(int *)(iVar1 + IMG_ADDR(0x1002eb34)) + -1;
  return 0;
}

/* ---- 0x100072b0  SoundsRegisterVoice ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int * SoundsRegisterVoice(char *param_1)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  char *pcVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  #define acStack_20 (*(char (*)[32])(_frame + (0x30 - 0x20)))
  
                    /* 0x72b0  67  SoundsRegisterVoice */
  uVar5 = 0xffffffff;
  pcVar2 = param_1;
  do {
    pcVar7 = pcVar2;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar7 = pcVar2 + 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar7;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar2 = pcVar7 + -uVar5;
  pcVar7 = &DAT_10031d50;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar2;
    pcVar2 = pcVar2 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar7 = *pcVar2;
    pcVar2 = pcVar2 + 1;
    pcVar7 = pcVar7 + 1;
  }
  uVar5 = 0xffffffff;
  pcVar2 = param_1;
  do {
    pcVar7 = pcVar2;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar7 = pcVar2 + 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar7;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar2 = pcVar7 + -uVar5;
  pcVar7 = acStack_20;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar2;
    pcVar2 = pcVar2 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar7 = *pcVar2;
    pcVar2 = pcVar2 + 1;
    pcVar7 = pcVar7 + 1;
  }
  pcVar2 = Im_StrChr(acStack_20,'.');
  if (pcVar2 != (char *)0x0) {
    *(undefined4 *)pcVar2 = DAT_1001e904;
    pcVar2[4] = DAT_1001e908;
    Im_SoundsFindByName(acStack_20,(char *)0x2710);
  }
  piVar3 = Im_SoundsLoad(param_1,&DAT_1001e900);
  _DAT_1002eb10 = piVar3;
  if (piVar3 != (int *)0x0) {
    iMUSE_sounds__9e40((undefined *)piVar3,0,2);
    iVar4 = iMUSE_sounds__9e10((undefined *)_DAT_1002eb10);
    iMUSE_sounds__9e40((undefined *)_DAT_1002eb10,0,0);
    _DAT_10031d34 = ((iVar4 + -0x2c) * 10) / 0x1b9;
    return piVar3;
  }
  _DAT_10031d34 = 0;
  return (int *)0x0;
}
#undef acStack_20


/* ---- 0x100073c0  SoundsCloseVoiceFile ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl SoundsCloseVoiceFile(void)

{
  undefined4 uVar1;
  
                    /* 0x73c0  54  SoundsCloseVoiceFile */
  uVar1 = 0;
  if (_DAT_1002eb10 != (undefined4 *)0x0) {
    Im_SoundsUnload(_DAT_1002eb10);
    uVar1 = ((code *)Im_SoundsFreeSlot)(10000);
    _DAT_1002eb10 = (undefined4 *)0x0;
  }
  return uVar1;
}

/* ---- 0x100073f0  SoundsReOpenVoiceFile ---- */
undefined4 __cdecl SoundsReOpenVoiceFile(void)

{
  undefined4 uVar1;
  
                    /* 0x73f0  66  SoundsReOpenVoiceFile */
  uVar1 = SoundsCloseVoiceFile();
  uVar1 = CONCAT31((int3)((uint)uVar1 >> 8),DAT_10031d50);
  if (DAT_10031d50 != '\0') {
    uVar1 = SoundsRegisterVoice(&DAT_10031d50);
  }
  return uVar1;
}

/* ---- 0x10007410  SoundsLoadStartSound ---- */
undefined4 __cdecl SoundsLoadStartSound(uint *param_1,int param_2,uint param_3)

{
  uint uVar1;
  
                    /* 0x7410  64  SoundsLoadStartSound */
  uVar1 = Sounds_ResolveName_LoadIfNeeded(param_1);
  if (uVar1 == 0) {
    return 0;
  }
  if (0x7c < param_2) {
    param_2 = 0x7c;
  }
  ImStartSound(uVar1,param_2);
  ImSetParam(uVar1,0x400,param_3);
  *(int *)(&DAT_10031564 + (uVar1 - 100) * 0x40) = param_2;
  return (&DAT_10031548)[(uVar1 - 100) * 0x10];
}

/* ---- 0x10007470  SoundsLoadProcessStartSound ---- */
undefined4 __cdecl SoundsLoadProcessStartSound(uint *param_1,int param_2,uint param_3)

{
  uint uVar1;
  
                    /* 0x7470  63  SoundsLoadProcessStartSound */
  uVar1 = Sounds_ResolveName_LoadIfNeeded(param_1);
  if (uVar1 == 0) {
    return 0;
  }
  if (0x7c < param_2) {
    param_2 = 0x7c;
  }
  if (DAT_10031d30 != 0) {
    if (((&DAT_10031548)[(uVar1 - 100) * 0x10] != 0) &&
       (*(int *)(&DAT_10031560 + (uVar1 - 100) * 0x40) == 0)) {
      Im_SoundsPrepare((&DAT_10031548)[(uVar1 - 100) * 0x10]);
    }
  }
  ImStartSound(uVar1,param_2);
  ImSetParam(uVar1,0x400,param_3);
  *(int *)(&DAT_10031564 + (uVar1 - 100) * 0x40) = param_2;
  return (&DAT_10031548)[(uVar1 - 100) * 0x10];
}

/* ---- 0x10007500  SoundsStopSound ---- */
undefined4 __cdecl SoundsStopSound(uint *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
                    /* 0x7500  71  SoundsStopSound */
  iVar1 = Sounds_ResolveName_LoadIfNeeded(param_1);
  uVar2 = 0;
  if (iVar1 != 0) {
    uVar2 = ImStopSound(iVar1);
  }
  return uVar2;
}

/* ---- 0x10007520  SoundsGetParam ---- */
uint __cdecl SoundsGetParam(uint *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
                    /* 0x7520  59  SoundsGetParam */
  iVar1 = Sounds_ResolveName_LoadIfNeeded(param_1);
  if (iVar1 == 0) {
    return 1;
  }
  uVar2 = ImGetParam(iVar1,param_2);
  return uVar2;
}

/* ---- 0x10007550  SoundsSetParam ---- */
undefined4 __cdecl SoundsSetParam(uint *param_1,int param_2,uint param_3)

{
  int iVar1;
  undefined4 uVar2;
  
                    /* 0x7550  70  SoundsSetParam */
  iVar1 = Sounds_ResolveName_LoadIfNeeded(param_1);
  uVar2 = 0;
  if (iVar1 != 0) {
    uVar2 = ImSetParam(iVar1,param_2,param_3);
  }
  return uVar2;
}

/* ---- 0x10007580  SoundsFadeParam ---- */
undefined4 SoundsFadeParam(uint *param_1,int param_2,uint param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  
                    /* 0x7580  55  SoundsFadeParam */
  iVar1 = Sounds_ResolveName_LoadIfNeeded(param_1);
  if (iVar1 == 0) {
    return 1;
  }
  uVar2 = ImFadeParam(iVar1,param_2,param_3,(param_4 * 0x3c) / 1000);
  return uVar2;
}

/* ---- 0x100075d0  SoundsIsSoundInUse ---- */
bool __cdecl SoundsIsSoundInUse(uint *param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
                    /* 0x75d0  61  SoundsIsSoundInUse */
  iVar1 = Sounds_ResolveName_LoadIfNeeded(param_1);
  iVar3 = iVar1 + -100;
  if ((((-1 < iVar3) && (iVar3 < 0x20)) && ((&DAT_10031528)[iVar3 * 0x40] != '\0')) &&
     (*(int *)(&DAT_10031550 + iVar3 * 0x40) != 0)) {
    uVar2 = ImGetParam(iVar1,0x100);
    if (0 < (int)uVar2) {
      return true;
    }
    uVar2 = ImGetParam(iVar1,0x200);
    return 0 < (int)uVar2;
  }
  return false;
}

/* ---- 0x10007640  SoundsIsSoundPlaying ---- */
bool __cdecl SoundsIsSoundPlaying(uint *param_1)

{
  int iVar1;
  uint uVar2;
  
                    /* 0x7640  62  SoundsIsSoundPlaying */
  iVar1 = Sounds_ResolveName_LoadIfNeeded(param_1);
  uVar2 = ImGetParam(iVar1,0x100);
  return 0 < (int)uVar2;
}

/* ---- 0x10007670  SoundsFillStreamsWhileMusicCritical ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl SoundsFillStreamsWhileMusicCritical(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
                    /* 0x7670  56  SoundsFillStreamsWhileMusicCritical */
  uVar2 = 0;
  if (_DAT_10031d44 != 0) {
    iVar1 = FUN_100076b0();
    uVar2 = 0;
    if (iVar1 != 0) {
      do {
        ImProcessStreams();
        iVar1 = FUN_100076b0();
      } while (iVar1 != 0);
      uVar2 = 0;
      if (0 < param_1) {
        do {
          uVar2 = ImProcessStreams();
          param_1 = param_1 + -1;
        } while (param_1 != 0);
      }
    }
  }
  return uVar2;
}

/* ---- 0x100076b0  FUN_100076b0 ---- */
undefined4 FUN_100076b0(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_10 (*(int *)(_frame + (0x20 - 0x10)))
  #define local_c (*(int *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(int *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  iVar1 = FUN_10007700(&local_4,&local_8,&local_c,&local_10);
  if (((iVar1 != 0) && (local_10 == 0)) && (local_c <= local_8)) {
    return 1;
  }
  return 0;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x10007700  FUN_10007700 ---- */
undefined4 __cdecl
FUN_10007700(undefined4 *param_1,undefined4 *param_2,int *param_3,undefined4 *param_4)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = ImGetNextSound(0);
  if (uVar1 == 0) {
    return 0;
  }
  do {
    uVar2 = ImGetParam(uVar1,0x1800);
    if (uVar2 == 1) {
      uVar2 = ImGetParam(uVar1,0x400);
      if (uVar2 == 3) {
LAB_1000775b:
        ImQueryStream(uVar1,param_1,param_2,param_3,param_4);
        return 1;
      }
      uVar2 = ImGetParam(uVar1,0x400);
      if (uVar2 == 4) goto LAB_1000775b;
    }
    uVar1 = ImGetNextSound(uVar1);
    if (uVar1 == 0) {
      return 0;
    }
  } while( true );
}

/* ---- 0x10007790  SoundsFloodMusicBuffer ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl SoundsFloodMusicBuffer(void)

{
  int iVar1;
  
                    /* 0x7790  57  SoundsFloodMusicBuffer */
  iVar1 = 0;
  if (_DAT_10031d44 != 0) {
    iVar1 = FUN_100077c0();
    while (iVar1 == 0) {
      ImProcessStreams();
      iVar1 = FUN_100077c0();
    }
  }
  return iVar1;
}

/* ---- 0x100077c0  FUN_100077c0 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_100077c0(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_10 (*(int *)(_frame + (0x20 - 0x10)))
  #define local_c (*(int *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(int *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  iVar1 = FUN_10007700(&local_c,&local_4,&local_8,&local_10);
  if (((iVar1 != 0) && (local_10 == 0)) && (local_8 <= local_c - _DAT_1001e8b8)) {
    return 0;
  }
  return 1;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x10007810  SoundsPeriodic ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

char * __stdcall SoundsPeriodic(int a1,int a2,int a3,int a4,int a5)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  
                    /* 0x7810  65  SoundsPeriodic */
  if (_DAT_10031d44 != 0) {
    ImProcessStreams();
    ImRefreshScript();
    iVar2 = 0;
    pcVar1 = &DAT_10031ce8;
    iVar3 = 0x20;
    do {
      if ((*pcVar1 != '\0') && (*(int *)(pcVar1 + 0x28) != 0)) {
        iVar2 = iVar2 + *(int *)(pcVar1 + 0x34);
      }
      pcVar1 = pcVar1 + -0x40;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    if (_DAT_1001e8d0 < iVar2) {
      pcVar1 = (char *)Sounds_EvictOldestIdleSlot();
    }
    return pcVar1;
  }
  return (char *)0;
}

/* ---- 0x10007830  SoundsGetMusicPosition ---- */
uint __cdecl SoundsGetMusicPosition(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
                    /* 0x7830  58  SoundsGetMusicPosition */
  uVar1 = ImGetNextSound(0);
  uVar2 = 0;
  if (uVar1 != 0) {
    while ((uVar2 = ImGetParam(uVar1,0x1800), uVar2 == 0 ||
           (uVar3 = ImGetParam(uVar1,0x1900), uVar2 = uVar1, uVar3 != 2))) {
      uVar1 = ImGetNextSound(uVar1);
      if (uVar1 == 0) {
        uVar2 = ImGetParam(0,0x1a00);
        return uVar2;
      }
    }
  }
  uVar2 = ImGetParam(uVar2,0x1a00);
  return uVar2;
}

/* ---- 0x100078a0  SoundsSetMuscriptLocal ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl SoundsSetMuscriptLocal(undefined4 param_1)

{
                    /* 0x78a0  68  SoundsSetMuscriptLocal */
  _DAT_1001e8dc = param_1;
  return param_1;
}

/* ---- 0x100078b0  SoundsSetMuscriptRemote ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl SoundsSetMuscriptRemote(undefined4 param_1)

{
                    /* 0x78b0  69  SoundsSetMuscriptRemote */
  _DAT_10031e54 = param_1;
  return param_1;
}

/* ---- 0x100078c0  Sounds_PlatformDevice ---- */
undefined4 __cdecl Sounds_PlatformDevice(undefined4 param_1)

{
                    /* 0x78c0  72  Sounds_PlatformDevice */
  DAT_100336bc = param_1;
  return param_1;
}

/* ---- 0x100078d0  SoundsInitialize ---- */
undefined4 SoundsInitialize(undefined4 param_1,undefined4 *param_2)

{
                    /* 0x78d0  60  SoundsInitialize */
  DAT_10033510 = param_1;
  *param_2 = SoundsInitialize;
  param_2[1] = 0;
  param_2[2] = FUN_10007920;
  param_2[3] = FUN_10008140;
  param_2[4] = FUN_10008250;
  param_2[5] = FUN_10008580;
  param_2[6] = FUN_10008860;
  param_2[7] = FUN_100088a0;
  return 0;
}

/* ---- 0x10007920  FUN_10007920 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_10007920(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (DAT_100336bc != 0) {
    FUN_10007a20();
    if (_DAT_1001e8d8 != 0) {
      FUN_10004660(_DAT_1001e8d8);
    }
    puVar2 = (undefined4 *)&DAT_10031528;
    for (iVar1 = 0x200; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
    }
    puVar2 = (undefined4 *)&DAT_1002eb10;
    for (iVar1 = 0x32; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
    }
    iVar1 = FUN_10008ce0();
    if (iVar1 == 0) {
      return 1;
    }
    DAT_100336a0 = FUN_10007a70;
    DAT_100336a4 = FUN_10007a60;
    DAT_100336b4 = FUN_10007a80;
    DAT_100336ac = FUN_10007bc0;
    DAT_100336b0 = FUN_10007ca0;
    ImInitialize();
    SoundsAllocateBuffer(2,_DAT_1001e8b4,_DAT_1001e8b8,_DAT_1001e8bc);
    SoundsAllocateBuffer(1,_DAT_1001e8a8,_DAT_1001e8ac,_DAT_1001e8b0);
    ImInitializeScript(((unsigned)(uintptr_t)FUN_100067a0),((unsigned)(uintptr_t)FUN_100067a0),0x10007a90,((unsigned)(uintptr_t)FUN_10007250),0,0,_DAT_1001e8dc);
    _DAT_10031d44 = 1;
  }
  return 0;
}

/* ---- 0x10007a20  FUN_10007a20 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_10007a20(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  _DAT_1002ec10 = 0x14;
  _DAT_10031d38 =
       (undefined4 *)
       (**(code **)(DAT_10033510 + 0x20))(0x50,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0x7a);
  if (_DAT_10031d38 != (undefined4 *)0x0) {
    puVar2 = _DAT_10031d38;
    for (iVar1 = 0x14; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
    }
    _DAT_1002ebd8 = 0;
  }
  return;
}

/* ---- 0x10007a60  FUN_10007a60 ---- */
void FUN_10007a60(undefined4 param_1)

{
  FUN_10009530(param_1);
  return;
}

/* ---- 0x10007a70  FUN_10007a70 ---- */
void FUN_10007a70(undefined4 param_1)

{
  FUN_10009560(param_1);
  return;
}

/* ---- 0x10007a80  FUN_10007a80 ---- */
int FUN_10007a80(int param_1)

{
  return param_1 * 0x10 + 0x1002ebe0;
}

/* ---- 0x10007bc0  FUN_10007bc0 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_10007bc0(int param_1,int param_2,int param_3)

{
  undefined *puVar1;
  int iVar2;
  
  if (((9999 < param_1) && (param_1 < 0x2715)) &&
     (puVar1 = *(undefined **)(&DAT_1002eb10 + (param_1 + -10000) * 0x28),
     puVar1 != (undefined *)0x0)) {
    iVar2 = iMUSE_sounds__9e40(puVar1,param_2,param_3);
    if (iVar2 == 0) {
      if (((param_1 == 10000) && (DAT_10031d30 != 0)) && (param_3 == 2)) {
        iVar2 = iMUSE_sounds__9e10(puVar1);
        return (iVar2 + -0x2c + _DAT_1001e8a4) * DAT_10031d30 + 0x2c;
      }
      if (((param_1 != 10000) || (DAT_10031d30 == 0)) || (param_3 != 0)) {
        iVar2 = iMUSE_sounds__9e10(puVar1);
        return iVar2;
      }
      iVar2 = param_2;
      if (0x2c < param_2) {
        iVar2 = (param_2 - 0x2cU) / DAT_10031d30 + 0x2c;
      }
      iVar2 = iMUSE_sounds__9e40(puVar1,iVar2,0);
      if (iVar2 == 0) {
        return param_2;
      }
    }
  }
  return 0;
}

/* ---- 0x10007ca0  FUN_10007ca0 ---- */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * FUN_10007ca0(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  uint uVar5;
  undefined4 *puVar6;
  uint uVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  #define uStack_c (*(uint *)(_frame + (0x20 - 0xc)))
  
  puVar4 = *(undefined4 **)(&DAT_1002eb10 + (int)(param_1 + -0x9c4) * 0x28);
  if (puVar4 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  if ((param_1 == (undefined4 *)0x2710) && (DAT_10031d30 != 0)) {
    iVar2 = iMUSE_sounds__9e10((undefined *)puVar4);
    iMUSE_sounds__9e40((undefined *)puVar4,0,2);
    iVar3 = iMUSE_sounds__9e10((undefined *)puVar4);
    iMUSE_sounds__9e40((undefined *)puVar4,iVar2,0);
    puVar1 = param_3;
    if ((int)_DAT_10031e5c < (int)param_3) {
      if (_DAT_10031e58 != (undefined4 *)0x0) {
        (**(code **)(DAT_10033510 + 0x24))(_DAT_10031e58);
        _DAT_10031e58 = (undefined4 *)0x0;
      }
      _DAT_10031e58 =
           (undefined4 *)
           (**(code **)(DAT_10033510 + 0x20))
                     (puVar1,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0x1cd);
      _DAT_10031e5c = puVar1;
    }
    if (iVar3 <= iVar2) {
      puVar4 = puVar1;
      if (_DAT_10031e64 != 0) {
        puVar4 = (undefined4 *)(_DAT_10031e64 - (int)_DAT_10031e6c);
        if ((int)puVar1 < (int)(_DAT_10031e64 - (int)_DAT_10031e6c)) {
          puVar4 = puVar1;
        }
        puVar8 = (undefined4 *)((int)_DAT_10031e60 + (int)_DAT_10031e6c);
        puVar10 = param_2;
        for (uVar5 = (uint)puVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
          *puVar10 = *puVar8;
          puVar8 = puVar8 + 1;
          puVar10 = puVar10 + 1;
        }
        for (uVar5 = (uint)puVar4 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined1 *)puVar10 = *(undefined1 *)puVar8;
          puVar8 = (undefined4 *)((int)puVar8 + 1);
          puVar10 = (undefined4 *)((int)puVar10 + 1);
        }
        _DAT_10031e6c = _DAT_10031e6c + (int)puVar4;
        if ((int)puVar1 <= (int)puVar4) {
          return puVar1;
        }
        param_2 = (undefined4 *)((int)puVar4 + (int)param_2);
        puVar4 = (undefined4 *)((int)puVar1 - (int)puVar4);
      }
      for (uVar5 = (uint)puVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *param_2 = 0;
        param_2 = param_2 + 1;
      }
      for (uVar5 = (uint)puVar4 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined1 *)param_2 = 0;
        param_2 = (undefined4 *)((int)param_2 + 1);
      }
      return puVar1;
    }
    if (iVar2 == 0) {
      puVar8 = puVar1 + -0xb;
      uVar5 = Im_SoundsReadBlock(puVar4,_DAT_10031e58,(uint)puVar8 / DAT_10031d30 + 0x2c);
      iVar2 = iMUSE_sounds__9e10((undefined *)puVar4);
      puVar4 = param_2;
      uStack_c = (uint)(iVar3 <= iVar2);
      puVar10 = _DAT_10031e58;
      puVar6 = param_2;
      for (iVar2 = 0xb; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar6 = *puVar10;
        puVar10 = puVar10 + 1;
        puVar6 = puVar6 + 1;
      }
      iVar2 = param_2[10] + _DAT_1001e8a4;
      param_2[10] = iVar2;
      param_2[10] = DAT_10031d30 * iVar2;
      param_2[7] = DAT_10031d30 * param_2[7];
      if (1 < DAT_10031d30) {
        *(char *)((int)param_2 + 0x16) = *(char *)((int)param_2 + 0x16) << 1;
        *(char *)(param_2 + 8) = *(char *)(param_2 + 8) << 1;
      }
      puVar10 = param_2 + 0xb;
      Im_ApplyFXPreset((undefined2 *)(_DAT_10031e58 + 0xb),uVar5 - 0x2c,(undefined2 *)puVar10,
                       (int *)&param_3,(int *)&param_1,uStack_c);
      if ((uStack_c != 0) && (param_3 != (undefined4 *)0x0)) {
        puVar6 = puVar8;
        if ((int)param_1 <= (int)puVar8) {
          puVar6 = param_1;
        }
        puVar9 = param_3;
        for (uVar5 = (uint)puVar6 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
          *puVar10 = *puVar9;
          puVar9 = puVar9 + 1;
          puVar10 = puVar10 + 1;
        }
        for (uVar5 = (uint)puVar6 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined1 *)puVar10 = *(undefined1 *)puVar9;
          puVar9 = (undefined4 *)((int)puVar9 + 1);
          puVar10 = (undefined4 *)((int)puVar10 + 1);
        }
        if ((int)param_1 < (int)puVar8) {
          puVar4 = (undefined4 *)((int)(param_1 + 0xb) + (int)puVar4);
          for (uVar5 = (uint)((int)puVar8 - (int)param_1) >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
            *puVar4 = 0;
            puVar4 = puVar4 + 1;
          }
          for (uVar5 = (int)puVar8 - (int)param_1 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
            *(undefined1 *)puVar4 = 0;
            puVar4 = (undefined4 *)((int)puVar4 + 1);
          }
        }
        if ((int)puVar8 < (int)param_1) {
          _DAT_10031e64 = (int)param_1 - (int)puVar8;
          _DAT_10031e6c = (undefined1 *)0x0;
          if ((int)_DAT_10031e68 < (int)_DAT_10031e64) {
            if (_DAT_10031e60 != (undefined4 *)0x0) {
              (**(code **)(DAT_10033510 + 0x24))(_DAT_10031e60);
              _DAT_10031e60 = (undefined4 *)0x0;
            }
            _DAT_10031e60 =
                 (undefined4 *)
                 (**(code **)(DAT_10033510 + 0x20))
                           (_DAT_10031e64,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0x212);
            _DAT_10031e68 = _DAT_10031e64;
          }
          uVar5 = _DAT_10031e64;
          puVar4 = (undefined4 *)((int)param_3 + (int)puVar8);
          puVar8 = _DAT_10031e60;
          for (uVar7 = _DAT_10031e64 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
            *puVar8 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar8 = puVar8 + 1;
          }
          for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
            *(undefined1 *)puVar8 = *(undefined1 *)puVar4;
            puVar4 = (undefined4 *)((int)puVar4 + 1);
            puVar8 = (undefined4 *)((int)puVar8 + 1);
          }
        }
        else {
          _DAT_10031e64 = 0;
        }
        hmiFXFree(param_3);
        return puVar1;
      }
    }
    else {
      uVar5 = Im_SoundsReadBlock(puVar4,_DAT_10031e58,(uint)puVar1 / DAT_10031d30);
      iVar2 = iMUSE_sounds__9e10((undefined *)puVar4);
      puVar4 = param_2;
      uStack_c = (uint)(iVar3 <= iVar2);
      Im_ApplyFXPreset((undefined2 *)_DAT_10031e58,uVar5,(undefined2 *)param_2,(int *)&param_3,
                       (int *)&param_1,uStack_c);
      if ((uStack_c != 0) && (param_3 != (undefined4 *)0x0)) {
        puVar8 = puVar1;
        if ((int)param_1 <= (int)puVar1) {
          puVar8 = param_1;
        }
        puVar10 = param_3;
        puVar6 = puVar4;
        for (uVar5 = (uint)puVar8 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
          *puVar6 = *puVar10;
          puVar10 = puVar10 + 1;
          puVar6 = puVar6 + 1;
        }
        for (uVar5 = (uint)puVar8 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined1 *)puVar6 = *(undefined1 *)puVar10;
          puVar10 = (undefined4 *)((int)puVar10 + 1);
          puVar6 = (undefined4 *)((int)puVar6 + 1);
        }
        if ((int)param_1 < (int)puVar1) {
          puVar4 = (undefined4 *)((int)param_1 + (int)puVar4);
          for (uVar5 = (uint)((int)puVar1 - (int)param_1) >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
            *puVar4 = 0;
            puVar4 = puVar4 + 1;
          }
          for (uVar5 = (int)puVar1 - (int)param_1 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
            *(undefined1 *)puVar4 = 0;
            puVar4 = (undefined4 *)((int)puVar4 + 1);
          }
        }
        if ((int)param_1 <= (int)puVar1) {
          _DAT_10031e64 = 0;
          hmiFXFree(param_3);
          return puVar1;
        }
        _DAT_10031e64 = (int)param_1 - (int)puVar1;
        _DAT_10031e6c = (undefined1 *)0x0;
        if ((int)_DAT_10031e68 < (int)_DAT_10031e64) {
          if (_DAT_10031e60 != (undefined4 *)0x0) {
            (**(code **)(DAT_10033510 + 0x24))(_DAT_10031e60);
            _DAT_10031e60 = (undefined4 *)0x0;
          }
          _DAT_10031e60 =
               (undefined4 *)
               (**(code **)(DAT_10033510 + 0x20))
                         (_DAT_10031e64,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0x23b);
          _DAT_10031e68 = _DAT_10031e64;
        }
        uVar5 = _DAT_10031e64;
        puVar4 = (undefined4 *)((int)param_3 + (int)puVar1);
        puVar8 = _DAT_10031e60;
        for (uVar7 = _DAT_10031e64 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
          *puVar8 = *puVar4;
          puVar4 = puVar4 + 1;
          puVar8 = puVar8 + 1;
        }
        for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined1 *)puVar8 = *(undefined1 *)puVar4;
          puVar4 = (undefined4 *)((int)puVar4 + 1);
          puVar8 = (undefined4 *)((int)puVar8 + 1);
        }
        hmiFXFree(param_3);
        return puVar1;
      }
    }
    return puVar1;
  }
  puVar4 = (undefined4 *)Im_SoundsReadBlock(puVar4,param_2,(uint)param_3);
  return puVar4;
}
#undef uStack_c


/* ---- 0x10008140  FUN_10008140 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_10008140(void)

{
  int *piVar1;
  
  if (DAT_100336bc != 0) {
    FUN_10008e30();
    ImStopAllSounds();
    ImRefreshScript();
    ImHeartbeat();
    if (_DAT_1001e8d8 != 0) {
      FUN_10004970();
    }
    if (_DAT_10031e58 != 0) {
      (**(code **)(DAT_10033510 + 0x24))(_DAT_10031e58);
      _DAT_10031e58 = 0;
    }
    _DAT_10031e5c = 0;
    if (_DAT_10031e60 != 0) {
      (**(code **)(DAT_10033510 + 0x24))(_DAT_10031e60);
      _DAT_10031e60 = 0;
    }
    _DAT_10031d44 = 0;
    piVar1 = (int *)IMG_ADDR(0x1002ebe0);
    do {
      if (*piVar1 != 0) {
        (**(code **)(DAT_10033510 + 0x24))(*piVar1);
        *piVar1 = 0;
      }
      piVar1 = piVar1 + 4;
    } while ((int)piVar1 < IMG_ADDR(0x1002ec10));
    ImTerminate();
    FUN_10008e60();
    FUN_100081f0();
  }
  return;
}

/* ---- 0x100081f0  FUN_100081f0 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_100081f0(void)

{
  int *piVar1;
  int iVar2;
  
  if (_DAT_10031d38 != (int *)0x0) {
    iVar2 = 0;
    piVar1 = _DAT_10031d38;
    if (0 < _DAT_1002ec10) {
      do {
        if (*piVar1 != 0) {
          (**(code **)(DAT_10033510 + 0x24))(*piVar1);
        }
        piVar1 = piVar1 + 1;
        iVar2 = iVar2 + 1;
      } while (iVar2 < _DAT_1002ec10);
    }
    (**(code **)(DAT_10033510 + 0x24))(_DAT_10031d38);
    _DAT_10031d38 = (int *)0x0;
  }
  return;
}

/* ---- 0x10008250  FUN_10008250 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_10008250(code *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  code *pcVar1;
  undefined4 *puVar2;
  uint uVar3;
  int iVar4;
  int *piVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  char *pcVar9;
  bool bVar10;
  #define iStack_10 (*(int *)(_frame + (0x20 - 0x10)))
  #define iStack_c (*(int *)(_frame + (0x20 - 0xc)))
  #define uStack_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define puStack_4 (*(undefined4 **)(_frame + (0x20 - 0x4)))
  
  pcVar1 = param_1;
  puVar2 = (undefined4 *)
           (**(code **)(DAT_10033510 + 0x20))
                     (0x20000,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0x3f9);
  if (puVar2 == (undefined4 *)0x0) {
    return 1;
  }
  if (DAT_10031d30 == 0) {
    _DAT_10033520 = _DAT_1001e90c;
  }
  DAT_10031d50 = 0;
  puStack_4 = puVar2;
  (*param_1)(&DAT_10033520,0x28);
  iStack_10 = ImSave(puVar2,0x20000);
  (*param_1)(&iStack_10,4);
  (*param_1)(puVar2,iStack_10);
  iStack_10 = ImSaveScript((int)puVar2,0x20000);
  (*param_1)(&iStack_10,4);
  (*param_1)(puVar2,iStack_10);
  iStack_c = 0;
  param_1 = (code *)0x0;
  piVar5 = (int *)&DAT_10031550;
  do {
    if (((char)piVar5[-10] != '\0') && (*piVar5 != 0)) {
      uVar3 = ImGetParam((int)param_1 + 100,0x100);
      if (0 < (int)uVar3) {
        pcVar6 = (char *)piVar5[2];
        iVar4 = 4;
        bVar10 = true;
        pcVar8 = pcVar6;
        pcVar7 = (char *)&DAT_10017074;
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar10 = *pcVar8 == *pcVar7;
          pcVar8 = pcVar8 + 1;
          pcVar7 = pcVar7 + 1;
        } while (bVar10);
        if ((bVar10) && ((pcVar6[0xf] != '8' || (pcVar6[0xe] != '\0')))) {
          iStack_c = iStack_c + 1;
        }
      }
    }
    piVar5 = piVar5 + 0x10;
    param_1 = (code *)((int)param_1 + 1);
  } while ((int)piVar5 < IMG_ADDR(0x10031d50));
  (*pcVar1)(&iStack_c,4);
  param_1 = (code *)0x0;
  pcVar6 = &DAT_10031528;
  do {
    if ((*pcVar6 != '\0') && (*(int *)(pcVar6 + 0x28) != 0)) {
      uVar3 = ImGetParam((int)param_1 + 100,0x100);
      if (0 < (int)uVar3) {
        pcVar8 = *(char **)(pcVar6 + 0x30);
        iVar4 = 4;
        bVar10 = true;
        pcVar7 = pcVar8;
        pcVar9 = (char *)&DAT_10017074;
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar10 = *pcVar7 == *pcVar9;
          pcVar7 = pcVar7 + 1;
          pcVar9 = pcVar9 + 1;
        } while (bVar10);
        if ((bVar10) && ((pcVar8[0xf] != '8' || (pcVar8[0xe] != '\0')))) {
          (*pcVar1)(pcVar6,0x20);
          (*pcVar1)(pcVar6 + 0x20,4);
          (*pcVar1)(pcVar6 + 0x3c,4);
        }
      }
    }
    pcVar6 = pcVar6 + 0x40;
    param_1 = (code *)((int)param_1 + 1);
  } while ((int)pcVar6 < IMG_ADDR(0x10031d28));
  param_1 = (code *)0x0;
  puVar2 = &DAT_10031548;
  do {
    if ((*(char *)(puVar2 + -8) != '\0') && (puVar2[2] != 0)) {
      uVar3 = ImGetParam((int)param_1 + 100,0x100);
      if (0 < (int)uVar3) {
        pcVar6 = (char *)puVar2[4];
        iVar4 = 4;
        bVar10 = true;
        pcVar8 = pcVar6;
        pcVar7 = (char *)&DAT_10017074;
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar10 = *pcVar8 == *pcVar7;
          pcVar8 = pcVar8 + 1;
          pcVar7 = pcVar7 + 1;
        } while (bVar10);
        if ((bVar10) && ((pcVar6[0xf] != '8' || (pcVar6[0xe] != '\0')))) {
          (*pcVar1)(puVar2,4);
          uStack_8 = SoundsGetParam((uint *)*puVar2,0x600);
          (*pcVar1)(&uStack_8,4);
          uStack_8 = SoundsGetParam((uint *)*puVar2,0x700);
          (*pcVar1)(&uStack_8,4);
        }
      }
    }
    puVar2 = puVar2 + 0x10;
    param_1 = (code *)((int)param_1 + 1);
  } while ((int)puVar2 < IMG_ADDR(0x10031d48));
  param_1 = (code *)0x0;
  piVar5 = (int *)&DAT_10031550;
  do {
    if (((char)piVar5[-10] != '\0') && (*piVar5 != 0)) {
      uVar3 = ImGetParam((int)param_1 + 100,0x100);
      if (0 < (int)uVar3) {
        pcVar6 = (char *)piVar5[2];
        iVar4 = 4;
        bVar10 = true;
        pcVar8 = pcVar6;
        pcVar7 = (char *)&DAT_10017074;
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar10 = *pcVar8 == *pcVar7;
          pcVar8 = pcVar8 + 1;
          pcVar7 = pcVar7 + 1;
        } while (bVar10);
        if ((bVar10) && ((pcVar6[0xf] != '8' || (pcVar6[0xe] != '\0')))) {
          (*pcVar1)(piVar5 + -2,4);
          uStack_8 = iMUSE_GetHook(piVar5[-2]);
          (*pcVar1)(&uStack_8,4);
        }
      }
    }
    piVar5 = piVar5 + 0x10;
    param_1 = (code *)((int)param_1 + 1);
    if (IMG_ADDR(0x10031d4f) < (int)piVar5) {
      (**(code **)(DAT_10033510 + 0x24))(puStack_4);
      return 0;
    }
  } while( true );
}
#undef iStack_10
#undef iStack_c
#undef puStack_4
#undef uStack_8


/* ---- 0x10008580  FUN_10008580 ---- */
undefined4 FUN_10008580(code *param_1,uint param_2)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *a1;
  int iVar1;
  uint uVar2;
  int iVar3;
  #define iStack_28 (*(int *)(_frame + (0x40 - 0x28)))
  #define uStack_24 (*(undefined4 *)(_frame + (0x40 - 0x24)))
  #define puStack_20 (*(uint **)(_frame + (0x40 - 0x20)))
  #define auStack_1c (*(uint (*)[6])(_frame + (0x40 - 0x1c)))
  #define uStack_4 (*(uint *)(_frame + (0x40 - 0x4)))
  
  a1 = (int *)(**(code **)(DAT_10033510 + 0x20))
                        (0x20000,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0x46a);
  if (a1 == (int *)0x0) {
    return 1;
  }
  iVar1 = (*param_1)(&DAT_10033520,0x28);
  if (iVar1 != 0) {
    return 1;
  }
  ((code *)FUN_10009700)(IMG_ADDR(0x1001e98c));
  ImStopAllSounds();
  ((code *)FUN_10009700)(IMG_ADDR(0x1001e97c));
  ImFlushSounds();
  ((code *)FUN_10009700)(IMG_ADDR(0x1001e970));
  SoundsCloseVoiceFile();
  ((code *)FUN_10009700)(IMG_ADDR(0x1001e958));
  FUN_10008e60();
  ((code *)FUN_10009700)(IMG_ADDR(0x1001e944));
  iMUSE_SetVoiceEffect((uint *)&DAT_10033520);
  DAT_10031d50 = 0;
  (*param_1)(&uStack_24,4);
  (*param_1)(a1,uStack_24);
  iVar1 = ImRestore(a1);
  if (iVar1 != 0) {
    ((code *)FUN_10009700)(IMG_ADDR(0x1001e930));
    (*param_1)(&uStack_24,4);
    (*param_1)(a1,uStack_24);
    iVar1 = ImRestoreScript((int)a1);
    if (iVar1 != 0) {
      ((code *)FUN_10009700)(IMG_ADDR(0x1001e910));
      for (uVar2 = ImGetNextSound(0); uVar2 != 0; uVar2 = ImGetNextSound(uVar2)) {
        if ((int)uVar2 < 0x2711) {
          ImStopSound(uVar2);
        }
      }
      SoundsCloseVoiceFile();
      ((code *)FUN_10009700)(IMG_ADDR(0x1001e958));
      iVar1 = (*param_1)(&iStack_28,4);
      if ((iVar1 == 0) && (iStack_28 != 0)) {
        iVar1 = 0;
        if (0 < iStack_28) {
          do {
            iVar3 = (*param_1)(auStack_1c,0x20);
            if ((iVar3 != 0) || (iVar3 = (*param_1)(&param_2,4), iVar3 != 0)) goto LAB_1000883c;
            DAT_10031d3c = param_2 - 0x457;
            iVar3 = (*param_1)(&param_2,4);
            if (iVar3 != 0) goto LAB_1000883c;
            SoundsLoadStartSound(auStack_1c,param_2,1);
            iVar1 = iVar1 + 1;
          } while (iVar1 < iStack_28);
        }
        iVar1 = 0;
        if (0 < iStack_28) {
          do {
            iVar3 = (*param_1)(&puStack_20,4);
            if ((iVar3 != 0) || (iVar3 = (*param_1)(&param_2,4), iVar3 != 0)) goto LAB_1000883c;
            SoundsSetParam(puStack_20,0x600,param_2);
            iVar3 = (*param_1)(&STACK0X(0x00000014));
            if (iVar3 != 0) goto LAB_1000883c;
            SoundsSetParam((uint *)0x4,0x700,uStack_4);
            iVar1 = iVar1 + 1;
          } while (iVar1 < iStack_28);
        }
        iVar1 = 0;
        if (0 < iStack_28) {
          do {
            iVar3 = (*param_1)(&puStack_20,4);
            if ((iVar3 != 0) || (iVar3 = (*param_1)(&param_2,4), iVar3 != 0)) break;
            iMUSE_SetHook(puStack_20,param_2);
            iVar1 = iVar1 + 1;
          } while (iVar1 < iStack_28);
        }
      }
LAB_1000883c:
      (**(code **)(DAT_10033510 + 0x24))(a1);
      return 0;
    }
  }
  (**(code **)(DAT_10033510 + 0x24))(a1);
  return 1;
}
#undef auStack_1c
#undef iStack_28
#undef puStack_20
#undef uStack_24
#undef uStack_4


/* ---- 0x10008860  FUN_10008860 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_10008860(void)

{
  ImPause();
  _DAT_10031d2c = ImSetGroupVol(0,0xffffffff);
  ImSetGroupVol(0,0);
  ImSetAttribute(-1,0);
  return 0;
}

/* ---- 0x100088a0  FUN_100088a0 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_100088a0(void)

{
  ImSetGroupVol(0,_DAT_10031d2c);
  ImResume();
  ImSetAttribute(-1,1);
  return 0;
}

/* ---- 0x10008ec0  Sounds_ResolveName_LoadIfNeeded ---- */
/* Name (or handle) -> sound slot id (100..131) of the 32-slot sound cache. A name that is not
   cached is LOADED here (a free slot, or Sounds_EvictOldestIdleSlot). A handle (0x457..0x556, the
   number Lua gets from ImStartSound; one per cached SOUND, not per playing instance, reused when
   the slot is) that is not in the cache gives 0. Returns 0 when it cannot load. Callers:
   SoundsGetParam returns 1 (!) for 0, so ImGetParam(name or stale handle, anything) reads 1, i.e.
   'playing', when the sound is not resolvable (sound_playing loops). */

int __cdecl Sounds_ResolveName_LoadIfNeeded(uint *param_1)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int *piVar2;
  char *pcVar3;
  uint *puVar4;
  uint *puVar5;
  uint uVar6;
  uint uVar7;
  uint *puVar8;
  uint *puVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  bool bVar12;
  #define local_44 (*(int *)(_frame + (0x60 - 0x44)))
  #define uStack_40 (*(uint *)(_frame + (0x60 - 0x40)))
  #define uStack_3c (*(uint *)(_frame + (0x60 - 0x3c)))
  #define iStack_38 (*(int *)(_frame + (0x60 - 0x38)))
  #define iStack_34 (*(int *)(_frame + (0x60 - 0x34)))
  #define iStack_30 (*(int *)(_frame + (0x60 - 0x30)))
  #define puStack_2c (*(undefined4 **)(_frame + (0x60 - 0x2c)))
  #define uStack_28 (*(uint *)(_frame + (0x60 - 0x28)))
  #define uStack_24 (*(uint *)(_frame + (0x60 - 0x24)))
  #define auStack_20 (*(uint (*)[8])(_frame + (0x60 - 0x20)))
  
  uVar6 = 0xffffffff;
  local_44 = -1;
  if (param_1 == (uint *)0x0) {
    return 0;
  }
  if (param_1 == (uint *)0x2710) {
    return 10000;
  }
  if ((int)param_1 < 0x458) {
    return 0;
  }
  puVar9 = param_1;
  if (0x557 < (int)param_1) {
    do {
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      uVar7 = *puVar9;
      puVar9 = (uint *)((int)puVar9 + 1);
    } while ((char)uVar7 != '\0');
    if (~uVar6 - 1 < 5) {
      iVar1 = atoi((byte *)param_1);
      if (iVar1 == 10000) {
        return 10000;
      }
      if ((0x456 < iVar1) && (iVar1 < 0x557)) {
        return 0;
      }
    }
  }
  puVar9 = (uint *)&DAT_10031ce8;
  if ((int)param_1 < 0x557) {
    local_44 = 0x1f;
    while ((uint *)puVar9[8] != param_1) {
      puVar9 = puVar9 + -0x10;
      bVar12 = local_44 == 0;
      local_44 = local_44 + -1;
      if (bVar12) {
        return 0;
      }
    }
    if (puVar9[10] != 0) {
      return local_44 + 100;
    }
  }
  else {
    iVar1 = 0x1f;
    do {
      uVar6 = Im_StrCmpNoCase((byte *)puVar9,(byte *)param_1);
      if (uVar6 == 0) {
        local_44 = iVar1;
        if (puVar9[10] != 0) {
          return iVar1 + 100;
        }
        goto LAB_10009063;
      }
      if ((byte)*puVar9 == 0) {
        local_44 = iVar1;
      }
      puVar9 = puVar9 + -0x10;
      bVar12 = iVar1 != 0;
      iVar1 = iVar1 + -1;
    } while (bVar12);
    if ((local_44 < 0) && (local_44 = Sounds_EvictOldestIdleSlot(), local_44 < 0)) {
      return 0;
    }
    puVar9 = (uint *)(&DAT_10031528 + local_44 * 0x40);
    Im_MemCopy(puVar9,param_1,0x20);
    *(undefined1 *)(local_44 * 0x40 + IMG_ADDR(0x10031547)) = 0;
    do {
      bVar12 = false;
      uVar6 = (int)DAT_10031d3c >> 0x1f;
      iVar1 = 0;
      do {
        if ((DAT_10031528 != '\0') &&
           (DAT_10031548 == (((DAT_10031d3c ^ uVar6) - uVar6 & 0xff ^ uVar6) - uVar6) + 0x457)) {
          bVar12 = true;
          DAT_10031d3c = DAT_10031d3c + 1;
          break;
        }
        iVar1 = iVar1 + 1;
      } while (iVar1 < 0x20);
    } while (bVar12);
    uVar6 = (int)DAT_10031d3c >> 0x1f;
    (&DAT_10031548)[local_44 * 0x10] =
         (((DAT_10031d3c ^ uVar6) - uVar6 & 0xff ^ uVar6) - uVar6) + 0x457;
    DAT_10031d3c = DAT_10031d3c + 1;
  }
LAB_10009063:
  puVar9[0xe] = 0;
  piVar2 = Im_SoundsLoad(puVar9,&DAT_1001e900);
  if (piVar2 == (int *)0x0) {
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar9 = 0;
      puVar9 = puVar9 + 1;
    }
    return 0;
  }
  uVar6 = timeGetTime();
  puVar9[9] = uVar6;
  Im_MemCopy(auStack_20,puVar9,0x20);
  pcVar3 = Im_StrChr((char *)auStack_20,'.');
  if (pcVar3 != (char *)0x0) {
    *(undefined4 *)pcVar3 = DAT_1001e904;
    pcVar3[4] = DAT_1001e908;
    Im_SoundsFindByName(auStack_20,(char *)puVar9[8]);
  }
  iMUSE_sounds__9e40((undefined *)piVar2,0,2);
  uVar6 = iMUSE_sounds__9e10((undefined *)piVar2);
  puVar9[0xd] = uVar6;
  iMUSE_sounds__9e40((undefined *)piVar2,0,0);
  uVar6 = (**(code **)(DAT_10033510 + 0x20))
                    (puVar9[0xd] + 0x50,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0x774);
  puVar9[10] = uVar6;
  if (uVar6 != 0) {
    Im_SoundsReadBlock(piVar2,(undefined4 *)puVar9[10],puVar9[0xd]);
  }
  Im_SoundsUnload(piVar2);
  puVar4 = Im_VimaDecompress((uint *)puVar9[10],&iStack_38,&uStack_24,&uStack_3c,&uStack_28,
                             &iStack_34,&uStack_40);
  if ((iStack_38 != 3) && (iStack_38 != 5)) {
    (**(code **)(DAT_10033510 + 0x24))(puVar9[10]);
    Im_SoundsFreeSlot(puVar9[8]);
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar9 = 0;
      puVar9 = puVar9 + 1;
    }
    return 0;
  }
  puVar8 = puVar4;
  if (uStack_3c == 8) {
    uVar7 = (int)puVar4 - puVar9[10];
    iVar1 = puVar9[0xd] - uVar7;
    iStack_30 = iVar1;
    puStack_2c = (undefined4 *)
                 (**(code **)(DAT_10033510 + 0x20))
                           (puVar9[0xd] * 2 + 0x50,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0x798);
    puVar9[0xd] = uVar7 + iVar1 * 2;
    puVar10 = (undefined4 *)puVar9[10];
    puVar11 = puStack_2c;
    for (uVar6 = uVar7 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *puVar11 = *puVar10;
      puVar10 = puVar10 + 1;
      puVar11 = puVar11 + 1;
    }
    for (uVar6 = uVar7 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined1 *)puVar11 = *(undefined1 *)puVar10;
      puVar10 = (undefined4 *)((int)puVar10 + 1);
      puVar11 = (undefined4 *)((int)puVar11 + 1);
    }
    puVar8 = (uint *)(uVar7 + (int)puStack_2c);
    puVar5 = puVar8;
    for (iVar1 = iStack_30; iVar1 != 0; iVar1 = iVar1 + -1) {
      *(undefined1 *)puVar5 = 0x80;
      *(byte *)((int)puVar5 + 1) = (byte)*puVar4 ^ 0x80;
      puVar5 = (uint *)((int)puVar5 + 2);
      puVar4 = (uint *)((int)puVar4 + 1);
    }
    (**(code **)(DAT_10033510 + 0x24))(puVar9[10]);
    uStack_40 = uStack_40 << 1;
    puVar9[10] = (uint)puStack_2c;
    iStack_34 = 1;
    uStack_3c = 0x10;
    iStack_38 = 0;
  }
  if (iStack_38 != 3) {
    Im_DecodeSoundBlock((undefined4 *)(puVar9[10] + puVar9[0xd]),3,uStack_24,0x10,uStack_28,
                        uStack_40);
    puVar9[0xc] = puVar9[10] + puVar9[0xd];
    puVar9[0xb] = (uint)(puVar8 + -0x14);
    *(undefined1 *)(puVar9[10] + puVar9[0xd] + 0x1f) = (undefined1)iStack_34;
    return local_44 + 100;
  }
  puVar9[0xc] = puVar9[10];
  puVar9[0xb] = puVar9[10];
  return local_44 + 100;
}
#undef auStack_20
#undef iStack_30
#undef iStack_34
#undef iStack_38
#undef local_44
#undef puStack_2c
#undef uStack_24
#undef uStack_28
#undef uStack_3c
#undef uStack_40


/* ---- 0x100092f0  Sounds_EvictOldestIdleSlot ---- */
/* Frees the cache slot of the sound that was used longest ago (timeGetTime stamp at +0x24) among
   loaded slots with no playing track (param 0x100 == 0) and nothing pending (0x200 == 0). Returns
   the slot index, or -1 when every slot is in use. */

int Sounds_EvictOldestIdleSlot(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  undefined4 *puVar6;
  bool bVar7;
  #define iStack_8 (*(int *)(_frame + (0x20 - 0x8)))
  #define iStack_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  iStack_8 = timeGetTime();
  iVar4 = -1;
  iStack_4 = -1;
  pcVar5 = &DAT_10031ce8;
  iVar3 = 0x1f;
  do {
    iVar1 = iVar3;
    if ((*pcVar5 != '\0') && (*(int *)(pcVar5 + 0x28) != 0)) {
      uVar2 = ImGetParam(iVar3 + 100,0x100);
      iVar1 = iStack_4;
      if (((uVar2 == 0) && (uVar2 = ImGetParam(iVar3 + 100,0x200), uVar2 == 0)) &&
         ((iVar4 < 0 || (*(int *)(pcVar5 + 0x24) < iStack_8)))) {
        iStack_8 = *(int *)(pcVar5 + 0x24);
        iVar4 = iVar3;
      }
    }
    iStack_4 = iVar1;
    pcVar5 = pcVar5 + -0x40;
    bVar7 = iVar3 != 0;
    iVar3 = iVar3 + -1;
  } while (bVar7);
  if (iVar4 < 0) {
    iVar4 = iStack_4;
    if (iStack_4 < 0) {
      return -1;
    }
  }
  else {
    iVar3 = (&DAT_10031548)[iVar4 * 0x10];
    (&DAT_10031528)[iVar4 * 0x40] = 0;
    Im_SoundsFreeSlot(iVar3);
    if (*(int *)(&DAT_10031550 + iVar4 * 0x40) != 0) {
      (**(code **)(DAT_10033510 + 0x24))(*(int *)(&DAT_10031550 + iVar4 * 0x40));
    }
    puVar6 = (undefined4 *)(&DAT_10031528 + iVar4 * 0x40);
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar6 = 0;
      puVar6 = puVar6 + 1;
    }
  }
  return iVar4;
}
#undef iStack_4
#undef iStack_8


/* ---- 0x1000b940  ImFile_Read ---- */
/* File layer (module name inferred): locked read through the installed callbacks */

int __cdecl ImFile_Read(int *param_1,int param_2,int param_3)

{
  int iVar1;
  
  ImFile_Lock((uint)param_1);
  iVar1 = ImFile_ReadImpl(param_1,param_2,param_3);
  ImFile_Unlock((uint)param_1);
  return iVar1;
}

/* ---- 0x1000b980  ImFile_ReadImpl ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl ImFile_ReadImpl(int *param_1,int param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  
  if (((param_1[3] & 0x83U) != 0) && (((param_3 == 0 || (param_3 == 1)) || (param_3 == 2)))) {
    param_1[3] = param_1[3] & 0xffffffef;
    if (param_3 == 1) {
      iVar2 = _ftell_lk(param_1);
      param_2 = param_2 + iVar2;
      param_3 = 0;
    }
    _flush(param_1);
    uVar1 = param_1[3];
    if ((uVar1 & 0x80) == 0) {
      if ((((uVar1 & 1) != 0) && ((uVar1 & 8) != 0)) && ((uVar1 & 0x400) == 0)) {
        param_1[6] = 0x200;
      }
    }
    else {
      param_1[3] = uVar1 & 0xfffffffc;
    }
    iVar2 = _lseek(param_1[4],param_2,param_3);
    return (iVar2 != -1) - 1;
  }
  piVar3 = _errno();
  *piVar3 = 0x16;
  return -1;
}

/* ---- 0x1000ba20  FUN_1000ba20 ---- */
undefined4 __cdecl FUN_1000ba20(undefined4 param_1,char *param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar1 = FUN_1000d9e0();
  if (puVar1 == (undefined4 *)0x0) {
    return 0;
  }
  puVar2 = FUN_1000d810(param_1,param_2,param_3,puVar1);
  ImFile_Unlock((uint)puVar1);
  return puVar2;
}

/* ---- 0x1000ba60  FUN_1000ba60 ---- */
void __cdecl FUN_1000ba60(undefined4 param_1,undefined4 param_2)

{
  FUN_1000ba20(param_1,param_2,0x40);
  return;
}

/* ---- 0x1000ba80  FUN_1000ba80 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1000ba80(void)

{
  FUN_1000baa0();
  _DAT_10032f50 = FUN_1000db30();
  FUN_1000dac0();
  return;
}

/* ---- 0x1000baa0  FUN_1000baa0 ---- */
void FUN_1000baa0(void)

{
  PTR_FUN_1001ee9c = FUN_1000dbc0;
  PTR_FUN_1001ee98 = FUN_1000e020;
  PTR_FUN_1001eea0 = FUN_1000dc50;
  PTR_FUN_1001eea4 = FUN_1000db60;
  PTR_FUN_1001eea8 = FUN_1000dc30;
  PTR_FUN_1001eeac = FUN_1000e020;
  return;
}

/* ---- 0x1000bb10  ImFile_Close ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl ImFile_Close(int *param_1)

{
  undefined4 uVar1;
  
  if ((*(byte *)(param_1 + 3) & 0x40) != 0) {
    param_1[3] = 0;
    return 0xffffffff;
  }
  ImFile_Lock((uint)param_1);
  uVar1 = ImFile_CloseImpl(param_1);
  ImFile_Unlock((uint)param_1);
  return uVar1;
}

/* ---- 0x1000bb50  ImFile_CloseImpl ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl ImFile_CloseImpl(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0xffffffff;
  if ((*(byte *)(param_1 + 3) & 0x83) != 0) {
    uVar2 = _flush(param_1);
    _freebuf(param_1);
    iVar1 = _close(param_1[4]);
    if (iVar1 < 0) {
      param_1[3] = 0;
      return 0xffffffff;
    }
    if ((undefined *)param_1[7] != (undefined *)0x0) {
      free((undefined *)param_1[7]);
      param_1[7] = 0;
    }
  }
  param_1[3] = 0;
  return uVar2;
}

/* ---- 0x1000bbc0  ImFile_Open ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl ImFile_Open(char *param_1,uint param_2,uint param_3,int *param_4)

{
  uint uVar1;
  
  ImFile_Lock((uint)param_4);
  uVar1 = ImFile_OpenImpl(param_1,param_2,param_3,param_4);
  ImFile_Unlock((uint)param_4);
  return uVar1;
}

/* ---- 0x1000bc00  ImFile_OpenImpl ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl ImFile_OpenImpl(char *param_1,uint param_2,uint param_3,int *param_4)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  int *piVar6;
  int *piVar7;
  char *pcVar8;
  char *pcVar9;
  
  piVar1 = param_4;
  piVar6 = (int *)(param_3 * param_2);
  if (piVar6 == (int *)0x0) {
    return 0;
  }
  piVar7 = piVar6;
  if ((param_4[3] & 0x10cU) == 0) {
    param_4 = (int *)0x1000;
  }
  else {
    param_4 = (int *)param_4[6];
  }
  do {
    if (((piVar1[3] & 0x108U) == 0) || (piVar2 = (int *)piVar1[1], piVar2 == (int *)0x0)) {
      if (piVar7 < param_4) {
        uVar5 = _flsbuf((int)*param_1,piVar1);
        if (uVar5 == 0xffffffff) goto LAB_1000bd34;
        param_4 = (int *)piVar1[6];
        param_1 = param_1 + 1;
        piVar7 = (int *)((int)piVar7 - 1);
        if ((int)param_4 < 1) {
          param_4 = (int *)0x1;
        }
      }
      else {
        if (((piVar1[3] & 0x108U) != 0) && (iVar3 = _flush(piVar1), iVar3 != 0)) {
LAB_1000bd34:
          return (uint)((int)piVar6 - (int)piVar7) / param_2;
        }
        piVar2 = piVar7;
        if (param_4 != (int *)0x0) {
          piVar2 = (int *)((int)piVar7 - (uint)piVar7 % (uint)param_4);
        }
        piVar4 = (int *)_write(piVar1[4],param_1,(uint)piVar2);
        if (piVar4 == (int *)0xffffffff) {
LAB_1000bd19:
          piVar1[3] = piVar1[3] | 0x20;
          return (uint)((int)piVar6 - (int)piVar7) / param_2;
        }
        piVar7 = (int *)((int)piVar7 - (int)piVar4);
        param_1 = param_1 + (int)piVar4;
        if (piVar4 < piVar2) goto LAB_1000bd19;
      }
    }
    else {
      if (piVar7 < piVar2) {
        piVar2 = piVar7;
      }
      piVar7 = (int *)((int)piVar7 - (int)piVar2);
      pcVar8 = param_1;
      pcVar9 = (char *)*piVar1;
      for (uVar5 = (uint)piVar2 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar8;
        pcVar8 = pcVar8 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar5 = (uint)piVar2 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar9 = *pcVar8;
        pcVar8 = pcVar8 + 1;
        pcVar9 = pcVar9 + 1;
      }
      param_1 = param_1 + (int)piVar2;
      piVar1[1] = piVar1[1] - (int)piVar2;
      *piVar1 = *piVar1 + (int)piVar2;
    }
    if (piVar7 == (int *)0x0) {
      return param_3;
    }
  } while( true );
}

/* ---- 0x1000c4f0  ImFile_LockInit ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl ImFile_LockInit(int param_1)

{
  undefined *a1;
  
  if (*(int *)(&DAT_1001e9e8 + param_1 * 4) == 0) {
    a1 = (undefined *)malloc(0x18);
    if (a1 == (undefined *)0x0) {
      _amsg_exit(0x11);
    }
    ImFile_LockInit(0x11);
    if (*(int *)(&DAT_1001e9e8 + param_1 * 4) == 0) {
      InitializeCriticalSection((int)a1);
      *(undefined **)(&DAT_1001e9e8 + param_1 * 4) = a1;
    }
    else {
      free(a1);
    }
    ImFile_UnlockInner(0x11);
  }
  EnterCriticalSection(*(int *)(&DAT_1001e9e8 + param_1 * 4));
  return;
}

/* ---- 0x1000c570  ImFile_UnlockInner ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl ImFile_UnlockInner(int param_1)

{
  LeaveCriticalSection(*(int *)(&DAT_1001e9e8 + param_1 * 4));
  return;
}

/* ---- 0x1000c590  ImFile_Lock ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl ImFile_Lock(uint param_1)

{
  if ((IMG_ADDR(0x1001eaaf) < param_1) && (param_1 < IMG_ADDR(0x1001ed11))) {
    ImFile_LockInit(((int)(param_1 + 0xeffe1550) >> 5) + 0x1c);
    return;
  }
  EnterCriticalSection(param_1 + 0x20);
  return;
}

/* ---- 0x1000c5d0  FUN_1000c5d0 ---- */
void __cdecl FUN_1000c5d0(int param_1,int param_2)

{
  if (param_1 < 0x14) {
    ImFile_LockInit(param_1 + 0x1c);
    return;
  }
  EnterCriticalSection(param_2 + 0x20);
  return;
}

/* ---- 0x1000c600  ImFile_Unlock ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl ImFile_Unlock(uint param_1)

{
  if ((IMG_ADDR(0x1001eaaf) < param_1) && (param_1 < IMG_ADDR(0x1001ed11))) {
    ImFile_UnlockInner(((int)(param_1 + 0xeffe1550) >> 5) + 0x1c);
    return;
  }
  LeaveCriticalSection(param_1 + 0x20);
  return;
}

/* ---- 0x1000c640  FUN_1000c640 ---- */
void __cdecl FUN_1000c640(int param_1,int param_2)

{
  if (param_1 < 0x14) {
    ImFile_UnlockInner(param_1 + 0x1c);
    return;
  }
  LeaveCriticalSection(param_2 + 0x20);
  return;
}

/* ---- 0x1000c670  FUN_1000c670 ---- */
int __cdecl FUN_1000c670(int *param_1,char *param_2,undefined4 *param_3)

{
  unsigned char _frame[0x260] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char *pcVar1;
  ushort uVar2;
  uint uVar3;
  short *psVar4;
  int *piVar5;
  undefined4 uVar6;
  ushort *puVar7;
  int iVar8;
  char cVar9;
  undefined1 *puVar10;
  undefined1 *puVar11;
  int iVar12;
  ulonglong uVar13;
  undefined8 uVar14;
  longlong lVar15;
  uint uVar16;
  #define uStack_24c (*(uint *)(_frame + (0x260 - 0x24c)))
  #define puStack_248 (*(ushort **)(_frame + (0x260 - 0x248)))
  #define iStack_244 (*(int *)(_frame + (0x260 - 0x244)))
  #define local_240 (*(int *)(_frame + (0x260 - 0x240)))
  #define cStack_23a (*(char *)(_frame + (0x260 - 0x23a)))
  #define cStack_239 (*(char *)(_frame + (0x260 - 0x239)))
  #define iStack_238 (*(int *)(_frame + (0x260 - 0x238)))
  #define local_234 (*(int *)(_frame + (0x260 - 0x234)))
  #define iStack_230 (*(int *)(_frame + (0x260 - 0x230)))
  #define uStack_22c (*(uint *)(_frame + (0x260 - 0x22c)))
  #define iStack_228 (*(int *)(_frame + (0x260 - 0x228)))
  #define iStack_224 (*(int *)(_frame + (0x260 - 0x224)))
  #define local_220 (*(int *)(_frame + (0x260 - 0x220)))
  #define local_21c (*(uint *)(_frame + (0x260 - 0x21c)))
  #define uStack_218 (*(undefined4 *)(_frame + (0x260 - 0x218)))
  #define acStack_214 (*(char (*)[4])(_frame + (0x260 - 0x214)))
  #define uStack_210 (*(undefined4 *)(_frame + (0x260 - 0x210)))
  #define uStack_20c (*(undefined4 *)(_frame + (0x260 - 0x20c)))
  #define uStack_204 (*(uint *)(_frame + (0x260 - 0x204)))
  #define auStack_200 (*(undefined1 (*)[511])(_frame + (0x260 - 0x200)))
  #define uStack_1 (*(undefined1 *)(_frame + (0x260 - 0x1)))
  
  local_220 = 0;
  puVar11 = (undefined1 *)0x0;
  local_240 = 0;
  cVar9 = *param_2;
  local_21c = CONCAT31(PIECE(local_21c,1,3),cVar9);
  pcVar1 = param_2;
  do {
    if ((cVar9 == '\0') || (param_2 = pcVar1 + 1, local_240 < 0)) {
      return local_240;
    }
    if ((cVar9 < ' ') || ('x' < cVar9)) {
      uVar3 = 0;
    }
    else {
      uVar3 = (byte)(&DAT_10015398)[cVar9] & 0xf;
    }
    local_220 = (int)(char)(&UNK_100153b8)[uVar3 * 8 + local_220] >> 4;
    switch(local_220) {
    case 0:
code_r0x1000c870:
      iStack_230 = 0;
      if ((PTR_DAT_1001f010[(local_21c & 0xff) * 2 + 1] & 0x80) != 0) {
        FUN_1000d000((int)cVar9,param_1,&local_240);
        cVar9 = *param_2;
        param_2 = pcVar1 + 2;
      }
      FUN_1000d000((int)cVar9,param_1,&local_240);
      break;
    case 1:
      uStack_218 = 0;
      iStack_228 = 0;
      local_234 = 0;
      iStack_238 = 0;
      uStack_24c = 0;
      iStack_244 = -1;
      iStack_230 = 0;
      break;
    case 2:
      switch(cVar9) {
      case ' ':
        uStack_24c = uStack_24c | 2;
        break;
      case '#':
        uStack_24c = uStack_24c | 0x80;
        break;
      case '+':
        uStack_24c = uStack_24c | 1;
        break;
      case '-':
        uStack_24c = uStack_24c | 4;
        break;
      case '0':
        uStack_24c = uStack_24c | 8;
      }
      break;
    case 3:
      if (cVar9 == '*') {
        local_234 = FUN_1000d0d0((int *)&param_3);
        if (local_234 < 0) {
          uStack_24c = uStack_24c | 4;
          local_234 = -local_234;
        }
      }
      else {
        local_234 = cVar9 + -0x30 + local_234 * 10;
      }
      break;
    case 4:
      iStack_244 = 0;
      break;
    case 5:
      if (cVar9 == '*') {
        iStack_244 = FUN_1000d0d0((int *)&param_3);
        if (iStack_244 < 0) {
          iStack_244 = -1;
        }
      }
      else {
        iStack_244 = cVar9 + -0x30 + iStack_244 * 10;
      }
      break;
    case 6:
      switch(cVar9) {
      case 'I':
        if ((*param_2 != '6') || (pcVar1[2] != '4')) {
          local_220 = 0;
          goto code_r0x1000c870;
        }
        param_2 = pcVar1 + 3;
        uStack_24c = uStack_24c | 0x8000;
        break;
      case 'h':
        uStack_24c = uStack_24c | 0x20;
        break;
      case 'l':
        uStack_24c = uStack_24c | 0x10;
        break;
      case 'w':
        uStack_24c = uStack_24c | 0x800;
      }
      break;
    case 7:
      switch(cVar9) {
      case 'C':
        if ((uStack_24c & 0x830) == 0) {
          uStack_24c = uStack_24c | 0x800;
        }
      case 'c':
        if ((uStack_24c & 0x810) == 0) {
          uVar6 = FUN_1000d0d0((int *)&param_3);
          auStack_200[0] = (char)uVar6;
          puVar11 = (undefined1 *)0x1;
        }
        else {
          uVar6 = FUN_1000d110(&param_3);
          puVar11 = (undefined1 *)FUN_1000fd50(auStack_200,(ushort)uVar6);
          if ((int)puVar11 < 0) {
            puStack_248 = (ushort *)auStack_200;
            iStack_228 = 1;
            break;
          }
        }
        puStack_248 = (ushort *)auStack_200;
        break;
      case 'E':
      case 'G':
        uStack_218 = 1;
        cVar9 = cVar9 + ' ';
      case 'e':
      case 'f':
      case 'g':
        puStack_248 = (ushort *)auStack_200;
        if (iStack_244 < 0) {
          iStack_244 = 6;
        }
        else if ((iStack_244 == 0) && (cVar9 == 'g')) {
          iStack_244 = 1;
        }
        uStack_210 = *param_3;
        uStack_20c = param_3[1];
        param_3 = param_3 + 2;
        (*(code *)PTR_LAB_1001ee98)(&uStack_210,auStack_200,(int)cVar9,iStack_244,uStack_218);
        if (((uStack_24c & 0x80) != 0) && (iStack_244 == 0)) {
          (*(code *)PTR_LAB_1001eea4)(auStack_200);
        }
        if ((cVar9 == 'g') && ((uStack_24c & 0x80) == 0)) {
          (*(code *)PTR_LAB_1001ee9c)(auStack_200);
        }
        uVar3 = uStack_24c | 0x40;
        if (auStack_200[0] == '-') {
          puStack_248 = (ushort *)(auStack_200 + 1);
          uVar3 = uStack_24c | 0x140;
        }
        uStack_24c = uVar3;
        uVar3 = 0xffffffff;
        puVar7 = puStack_248;
        do {
          if (uVar3 == 0) break;
          uVar3 = uVar3 - 1;
          uVar2 = *puVar7;
          puVar7 = (ushort *)((int)puVar7 + 1);
        } while ((char)uVar2 != '\0');
        puVar11 = (undefined1 *)(~uVar3 - 1);
        break;
      case 'S':
        if ((uStack_24c & 0x830) == 0) {
          uStack_24c = uStack_24c | 0x800;
        }
      case 's':
        iVar12 = 0x7fffffff;
        if (iStack_244 != -1) {
          iVar12 = iStack_244;
        }
        puStack_248 = (ushort *)FUN_1000d0d0((int *)&param_3);
        if ((uStack_24c & 0x810) == 0) {
          puVar7 = puStack_248;
          if (puStack_248 == (ushort *)0x0) {
            puVar7 = (*(uint * *)IMG_ADDR(0x1001eaa8));
            puStack_248 = (*(uint * *)IMG_ADDR(0x1001eaa8));
          }
          for (; (iVar12 != 0 && (iVar12 = iVar12 + -1, (char)*puVar7 != '\0'));
              puVar7 = (ushort *)((int)puVar7 + 1)) {
          }
          puVar11 = (undefined1 *)((int)puVar7 - (int)puStack_248);
        }
        else {
          if (puStack_248 == (ushort *)0x0) {
            puStack_248 = (*(uint * *)IMG_ADDR(0x1001eaac));
          }
          iStack_230 = 1;
          for (puVar7 = puStack_248; (iVar12 != 0 && (iVar12 = iVar12 + -1, *puVar7 != 0));
              puVar7 = puVar7 + 1) {
          }
          puVar11 = (undefined1 *)((int)puVar7 - (int)puStack_248 >> 1);
        }
        break;
      case 'X':
        goto code_r0x1000cbe0;
      case 'Z':
        psVar4 = (short *)FUN_1000d0d0((int *)&param_3);
        if ((psVar4 == (short *)0x0) ||
           (puStack_248 = *(ushort **)(psVar4 + 2), puStack_248 == (ushort *)0x0)) {
          uVar3 = 0xffffffff;
          puStack_248 = (*(uint * *)IMG_ADDR(0x1001eaa8));
          puVar7 = (*(uint * *)IMG_ADDR(0x1001eaa8));
          do {
            if (uVar3 == 0) break;
            uVar3 = uVar3 - 1;
            uVar2 = *puVar7;
            puVar7 = (ushort *)((int)puVar7 + 1);
          } while ((char)uVar2 != '\0');
          puVar11 = (undefined1 *)(~uVar3 - 1);
        }
        else if ((uStack_24c & 0x800) == 0) {
          puVar11 = (undefined1 *)(int)*psVar4;
          iStack_230 = 0;
        }
        else {
          iStack_230 = 1;
          puVar11 = (undefined1 *)((uint)(int)*psVar4 >> 1);
        }
        break;
      case 'd':
      case 'i':
        uStack_22c = 10;
        uStack_24c = uStack_24c | 0x40;
        goto code_r0x1000cc37;
      case 'n':
        piVar5 = (int *)FUN_1000d0d0((int *)&param_3);
        if ((uStack_24c & 0x20) == 0) {
          iStack_228 = 1;
          *piVar5 = local_240;
        }
        else {
          iStack_228 = 1;
          *(undefined2 *)piVar5 = (undefined2)local_240;
        }
        break;
      case 'o':
        uStack_22c = 8;
        if ((uStack_24c & 0x80) != 0) {
          uStack_24c = uStack_24c | 0x200;
        }
        goto code_r0x1000cc37;
      case 'p':
        iStack_244 = 8;
code_r0x1000cbe0:
        iStack_224 = 7;
code_r0x1000cbf2:
        uStack_22c = 0x10;
        if ((uStack_24c & 0x80) != 0) {
          cStack_23a = '0';
          cStack_239 = (char)iStack_224 + 'Q';
          iStack_238 = 2;
        }
        goto code_r0x1000cc37;
      case 'u':
        uStack_22c = 10;
code_r0x1000cc37:
        if ((uStack_24c & 0x8000) == 0) {
          if ((uStack_24c & 0x20) == 0) {
            if ((uStack_24c & 0x40) == 0) {
              uVar3 = FUN_1000d0d0((int *)&param_3);
              uVar13 = (ulonglong)uVar3;
            }
            else {
              iVar12 = FUN_1000d0d0((int *)&param_3);
              uVar13 = (ulonglong)iVar12;
            }
          }
          else if ((uStack_24c & 0x40) == 0) {
            uVar3 = FUN_1000d0d0((int *)&param_3);
            uVar13 = (ulonglong)uVar3 & 0xffffffff0000ffff;
          }
          else {
            uVar6 = FUN_1000d0d0((int *)&param_3);
            uVar13 = (ulonglong)(int)(short)uVar6;
          }
        }
        else {
          uVar13 = FUN_1000d0f0((int *)&param_3);
        }
        iVar12 = (int)(uVar13 >> 0x20);
        if ((((uStack_24c & 0x40) != 0) && (iVar12 == 0 || (longlong)uVar13 < 0)) &&
           ((longlong)uVar13 < 0)) {
          uStack_24c = uStack_24c | 0x100;
          uVar13 = CONCAT44(-(iVar12 + (uint)((int)uVar13 != 0)),-(int)uVar13);
        }
        iVar12 = (int)(uVar13 >> 0x20);
        if ((uStack_24c & 0x8000) == 0) {
          iVar12 = 0;
        }
        lVar15 = CONCAT44(iVar12,(int)uVar13);
        if (iStack_244 < 0) {
          iStack_244 = 1;
        }
        else {
          uStack_24c = uStack_24c & 0xfffffff7;
        }
        puStack_248 = (ushort *)REGISTER0X(0x00000010);
        if ((int)uVar13 == 0 && iVar12 == 0) {
          iStack_238 = 0;
        }
        while( true ) {
          uVar3 = uStack_22c;
          puVar7 = (ushort *)((int)puStack_248 + -1);
          iVar12 = iStack_244 + -1;
          if ((iStack_244 < 1) && (lVar15 == 0)) break;
          uStack_204 = (int)uStack_22c >> 0x1f;
          uVar16 = (uint)((ulonglong)lVar15 >> 0x20);
          uVar14 = FUN_1000feb0((uint)lVar15,uVar16,uStack_22c,uStack_204);
          iVar8 = (int)uVar14 + 0x30;
          lVar15 = FUN_1000fe40((uint)lVar15,uVar16,uVar3,uStack_204);
          if (0x39 < iVar8) {
            iVar8 = iVar8 + iStack_224;
          }
          *(char *)puVar7 = (char)iVar8;
          iStack_244 = iVar12;
          puStack_248 = puVar7;
        }
        puVar11 = &uStack_1 + -(int)puVar7;
        iStack_244 = iVar12;
        if (((uStack_24c & 0x200) != 0) &&
           (((char)*puStack_248 != '0' || (puVar11 == (undefined1 *)0x0)))) {
          puVar11 = &STACK0X(0x00000000) + -(int)puVar7;
          *(char *)puVar7 = '0';
          puStack_248 = puVar7;
        }
        break;
      case 'x':
        iStack_224 = 0x27;
        goto code_r0x1000cbf2;
      }
      if (iStack_228 == 0) {
        if ((uStack_24c & 0x40) != 0) {
          if ((uStack_24c & 0x100) == 0) {
            if ((uStack_24c & 1) == 0) {
              if ((uStack_24c & 2) == 0) goto code_r0x1000cdcf;
              cStack_23a = ' ';
            }
            else {
              cStack_23a = '+';
            }
          }
          else {
            cStack_23a = '-';
          }
          iStack_238 = 1;
        }
code_r0x1000cdcf:
        iVar12 = (local_234 - (int)puVar11) - iStack_238;
        if ((uStack_24c & 0xc) == 0) {
          FUN_1000d050(0x20,iVar12,param_1,&local_240);
        }
        FUN_1000d090(&cStack_23a,iStack_238,param_1,&local_240);
        if (((uStack_24c & 8) != 0) && ((uStack_24c & 4) == 0)) {
          FUN_1000d050(0x30,iVar12,param_1,&local_240);
        }
        if ((iStack_230 == 0) || (puVar7 = puStack_248, puVar10 = puVar11, (int)puVar11 < 1)) {
          FUN_1000d090((char *)puStack_248,(int)puVar11,param_1,&local_240);
        }
        else {
          do {
            puVar10 = puVar10 + -1;
            iVar8 = FUN_1000fd50(acStack_214,*puVar7);
            if (iVar8 < 1) break;
            FUN_1000d090(acStack_214,iVar8,param_1,&local_240);
            puVar7 = puVar7 + 1;
          } while (puVar10 != (undefined1 *)0x0);
        }
        if ((uStack_24c & 4) != 0) {
          FUN_1000d050(0x20,iVar12,param_1,&local_240);
        }
      }
    }
    cVar9 = *param_2;
    local_21c = CONCAT31(PIECE(local_21c,1,3),cVar9);
    pcVar1 = param_2;
  } while( true );
}
#undef acStack_214
#undef auStack_200
#undef cStack_239
#undef cStack_23a
#undef iStack_224
#undef iStack_228
#undef iStack_230
#undef iStack_238
#undef iStack_244
#undef local_21c
#undef local_220
#undef local_234
#undef local_240
#undef puStack_248
#undef uStack_1
#undef uStack_204
#undef uStack_20c
#undef uStack_210
#undef uStack_218
#undef uStack_22c
#undef uStack_24c


/* ---- 0x1000d000  FUN_1000d000 ---- */
void __cdecl FUN_1000d000(uint param_1,int *param_2,int *param_3)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = param_2[1];
  param_2[1] = iVar1 + -1;
  if (iVar1 + -1 < 0) {
    uVar2 = _flsbuf(param_1,param_2);
  }
  else {
    *(char *)*param_2 = (char)param_1;
    uVar2 = param_1 & 0xff;
    *param_2 = *param_2 + 1;
  }
  if (uVar2 == 0xffffffff) {
    *param_3 = -1;
    return;
  }
  *param_3 = *param_3 + 1;
  return;
}

/* ---- 0x1000d050  FUN_1000d050 ---- */
void __cdecl FUN_1000d050(uint param_1,int param_2,int *param_3,int *param_4)

{
  do {
    if (param_2 < 1) {
      return;
    }
    param_2 = param_2 + -1;
    FUN_1000d000(param_1,param_3,param_4);
  } while (*param_4 != -1);
  return;
}

/* ---- 0x1000d090  FUN_1000d090 ---- */
void __cdecl FUN_1000d090(char *param_1,int param_2,int *param_3,int *param_4)

{
  char cVar1;
  
  do {
    if (param_2 < 1) {
      return;
    }
    param_2 = param_2 + -1;
    cVar1 = *param_1;
    param_1 = param_1 + 1;
    FUN_1000d000((int)cVar1,param_3,param_4);
  } while (*param_4 != -1);
  return;
}

/* ---- 0x1000d0d0  FUN_1000d0d0 ---- */
undefined4 __cdecl FUN_1000d0d0(int *param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)*param_1;
  *param_1 = (int)(puVar1 + 1);
  return *puVar1;
}

/* ---- 0x1000d0f0  FUN_1000d0f0 ---- */
undefined8 __cdecl FUN_1000d0f0(int *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  *param_1 = (int)(puVar1 + 1);
  return *puVar1;
}

/* ---- 0x1000d110  FUN_1000d110 ---- */
undefined4 __cdecl FUN_1000d110(undefined4 *param_1)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  
  puVar1 = (undefined2 *)*param_1;
  puVar2 = puVar1 + 2;
  *param_1 = puVar2;
  return CONCAT22((short)((uint)puVar2 >> 0x10),*puVar1);
}

/* ---- 0x1000d130  FUN_1000d130 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1000d130(void)

{
  undefined **ppuVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  
  if (_DAT_10034800 == 0) {
    _DAT_10034800 = 0x200;
  }
  else if (_DAT_10034800 < 0x14) {
    _DAT_10034800 = 0x14;
  }
  _DAT_100337f4 = calloc(_DAT_10034800,4);
  if (_DAT_100337f4 == (int *)0x0) {
    _DAT_10034800 = 0x14;
    _DAT_100337f4 = calloc(0x14,4);
    if (_DAT_100337f4 == (int *)0x0) {
      _amsg_exit(0x1a);
    }
  }
  iVar3 = 0;
  ppuVar1 = &PTR_DAT_1001eab0;
  do {
    *(undefined ***)((int)_DAT_100337f4 + iVar3) = ppuVar1;
    ppuVar1 = ppuVar1 + 8;
    iVar3 = iVar3 + 4;
  } while ((int)ppuVar1 < IMG_ADDR(0x1001ed30));
  uVar2 = 0;
  puVar4 = (undefined4 *)IMG_ADDR(0x1001eac0);
  do {
    if (((&PTR_100336e0)[(int)uVar2 >> 5][(uVar2 & 0x1f) * 9] == -1) ||
       ((&PTR_100336e0)[(int)uVar2 >> 5][(uVar2 & 0x1f) * 9] == 0)) {
      *puVar4 = 0xffffffff;
    }
    puVar4 = puVar4 + 8;
    uVar2 = uVar2 + 1;
  } while ((int)puVar4 < IMG_ADDR(0x1001eb20));
  return;
}

/* ---- 0x1000d1f0  FUN_1000d1f0 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __stdcall FUN_1000d1f0(int a1,int a2,int a3,int a4)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  uVar2 = ((code *)FUN_1000d590)();
  if (DAT_10033040 == '\0') {
    return CONCAT31((int3)((uint)uVar2 >> 8),DAT_10033040);
  }
  iVar4 = 0;
  ImFile_LockInit(2);
  iVar5 = 3;
  if (3 < _DAT_10034800) {
    do {
      piVar1 = *(int **)(_DAT_100337f4 + iVar5 * 4);
      if (piVar1 != (int *)0x0) {
        if (((*(byte *)(piVar1 + 3) & 0x83) != 0) && (iVar3 = ImFile_Close(piVar1), iVar3 != -1)) {
          iVar4 = iVar4 + 1;
        }
        if (0x13 < iVar5) {
          DeleteCriticalSection(*(int *)(_DAT_100337f4 + iVar5 * 4) + 0x20);
          free(*(undefined **)(_DAT_100337f4 + iVar5 * 4));
          *(undefined4 *)(_DAT_100337f4 + iVar5 * 4) = 0;
        }
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < _DAT_10034800);
  }
  ImFile_UnlockInner(2);
  return iVar4;
}
