/* IMUSE.DLL :: imuse_api.c
 * functions 0x10003d70 .. 0x1000d1f0 (114 functions)
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
  g_dwLoadSoundFunc = param_1;
  g_dwUnloadSoundFunc = param_2;
  g_dwCloseSoundFunc = param_4;
  g_dwOpenSoundFunc = param_3;
  puVar1 = (undefined4 *)((unsigned)(uintptr_t)&DAT_1002daec);
  do {
    puVar1[-1] = 0;
    *puVar1 = 0;
    puVar1[1] = 0;
    puVar1 = puVar1 + 0xd;
  } while ((int)puVar1 < ((unsigned)(uintptr_t)&g_dwUnloadSoundFunc));
  g_dwInitFlag = 1;
  return 0;
}

/* ---- 0x10003dc0  ImSaveFilelist ---- */
int ImSaveFilelist(int *param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  
  piVar4 = g_pLoadedList;
                    /* 0x3dc0  29  ImSaveFilelist */
  if (0x20f < param_2) {
    iVar1 = 8;
    *param_1 = 0;
    piVar3 = g_pOpenedList;
    for (; g_pOpenedList = piVar3, piVar4 != (int *)0x0; piVar4 = (int *)piVar4[1]) {
      *param_1 = *param_1 + 1;
      piVar3 = piVar4;
      piVar5 = (int *)(iVar1 + (int)param_1);
      for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
        *piVar5 = *piVar3;
        piVar3 = piVar3 + 1;
        piVar5 = piVar5 + 1;
      }
      iVar1 = iVar1 + 0x34;
      piVar3 = g_pOpenedList;
    }
    param_1[1] = 0;
    if (piVar3 != (int *)0x0) {
      piVar4 = (int *)(iVar1 + (int)param_1);
      do {
        param_1[1] = param_1[1] + 1;
        piVar5 = piVar3;
        piVar6 = piVar4;
        for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
          *piVar6 = *piVar5;
          piVar5 = piVar5 + 1;
          piVar6 = piVar6 + 1;
        }
        piVar3 = (int *)piVar3[1];
        iVar1 = iVar1 + 0x34;
        piVar4 = piVar4 + 0xd;
      } while (piVar3 != (int *)0x0);
    }
    return iVar1;
  }
  ImPrintf((char *)((unsigned)(uintptr_t)&DAT_10017124));
  return 0;
}

/* ---- 0x10003e50  ImRestoreFilelist ---- */
int ImRestoreFilelist(int *param_1)

{
  char *fmt;
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
                    /* 0x3e50  25  ImRestoreFilelist */
  piVar1 = param_1;
  puVar2 = (undefined4 *)((unsigned)(uintptr_t)&DAT_1002daec);
  do {
    puVar2[-1] = 0;
    *puVar2 = 0;
    puVar2[1] = 0;
    puVar2 = puVar2 + 0xd;
  } while ((int)puVar2 < ((unsigned)(uintptr_t)&g_dwUnloadSoundFunc));
  iVar6 = *param_1;
  iVar5 = param_1[1];
  iVar4 = 8;
  while (iVar6 != 0) {
    iVar6 = iVar6 + -1;
    iVar3 = ImLoadSound((int)param_1 + iVar4 + 0xc,*(undefined4 *)(iVar4 + 8 + (int)param_1));
    if (iVar3 == 0) {
      ImPrintf((char *)((unsigned)(uintptr_t)&DAT_10017144));
      ImPrintf((char *)((int)param_1 + iVar4 + 0xc));
      ImPrintf(&DAT_100171b0);
      return 0;
    }
    if (*(int *)((int)param_1 + iVar4 + 8) != g_pLoadedList[2]) goto LAB_10003f3a;
    g_pLoadedList[0xc] = *(int *)((int)param_1 + iVar4 + 0x30);
    iVar4 = iVar4 + 0x34;
  }
  param_1 = (int *)iVar5;
  if (iVar5 == 0) {
    return iVar4;
  }
  while( true ) {
    param_1 = (int *)((int)param_1 + -1);
    iVar5 = iVar4 + 0x34;
    fmt = (char *)((int)piVar1 + iVar4 + 0xc);
    iVar6 = ImOpenSound(fmt,*(undefined4 *)(iVar4 + 8 + (int)piVar1));
    if (iVar6 == 0) {
      ImPrintf((char *)((unsigned)(uintptr_t)&DAT_100171b4));
      ImPrintf(fmt);
      ImPrintf(&DAT_100171b0);
    }
    if (*(int *)((int)piVar1 + iVar4 + 8) != g_pOpenedList[2]) break;
    g_pOpenedList[0xc] = *(int *)((int)piVar1 + iVar4 + 0x30);
    iVar4 = iVar5;
    if (param_1 == (int *)0x0) {
      return iVar5;
    }
  }
LAB_10003f3a:
  ImPrintf((char *)((unsigned)(uintptr_t)&DAT_10017174));
  return 0;
}

/* ---- 0x10003f90  ImLoadSound ---- */
int ImLoadSound(char *param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  char *fmt;
  
                    /* 0x3f90  17  ImLoadSound */
  if ((((g_dwInitFlag != 0) && (*param_1 != '\0')) && (g_dwLoadSoundFunc != (code *)0x0)) &&
     (g_dwUnloadSoundFunc != 0)) {
    iVar2 = ImFindSound(param_1);
    piVar4 = g_pLoadedList;
    if (iVar2 != 0) {
      for (; piVar4 != (int *)0x0; piVar4 = (int *)piVar4[1]) {
        if (iVar2 == piVar4[2]) {
          piVar4[0xc] = piVar4[0xc] + 1;
          return iVar2;
        }
      }
    }
    piVar4 = (int *)((unsigned)(uintptr_t)&DAT_1002dae8);
    while (piVar4[2] != 0) {
      piVar4 = piVar4 + 0xd;
      if (((unsigned)(uintptr_t)&DAT_1002dcef) < (int)piVar4) {
        ImPrintf((char *)((unsigned)(uintptr_t)&DAT_10017210));
        return 0;
      }
    }
    iVar2 = (*g_dwLoadSoundFunc)(param_1,param_2);
    if (iVar2 == 0) {
      fmt = (char *)((unsigned)(uintptr_t)&DAT_100171f4);
    }
    else {
      cVar1 = *param_1;
      iVar3 = 0;
      while( true ) {
        if (cVar1 == '\0') {
          *(undefined1 *)(iVar3 + 0xc + (int)piVar4) = 0;
          piVar4[2] = iVar2;
          piVar4[0xc] = 1;
          FUN_10004460((int *)&g_pLoadedList,piVar4);
          return iVar2;
        }
        if (0x1f < iVar3) break;
        *(char *)(iVar3 + 0xc + (int)piVar4) = param_1[iVar3];
        cVar1 = param_1[iVar3 + 1];
        iVar3 = iVar3 + 1;
      }
      fmt = (char *)((unsigned)(uintptr_t)&DAT_100171e4);
    }
    ImPrintf(fmt);
    ImPrintf(param_1);
    ImPrintf(&DAT_100171b0);
    return 0;
  }
  return 0;
}

/* ---- 0x100040b0  ImUnloadSound ---- */
undefined4 __cdecl ImUnloadSound(int param_1)

{
  int *piVar1;
  undefined4 uVar2;
  
                    /* 0x40b0  49  ImUnloadSound */
  if (((g_dwInitFlag == 0) || (g_dwLoadSoundFunc == 0)) ||
     (piVar1 = g_pLoadedList, g_dwUnloadSoundFunc == 0)) {
    return g_pLoadedList;
  }
  do {
    if (piVar1 == (int *)0x0) {
LAB_100040f4:
      uVar2 = ImFlushSounds();
      return uVar2;
    }
    if (piVar1[2] == param_1) {
      if (piVar1[0xc] != 0) {
        piVar1[0xc] = piVar1[0xc] + -1;
      }
      goto LAB_100040f4;
    }
    piVar1 = (int *)piVar1[1];
  } while( true );
}

/* ---- 0x10004100  ImUnloadAll ---- */
undefined4 __cdecl ImUnloadAll(void)

{
  int *piVar1;
  undefined4 uVar2;
  
                    /* 0x4100  48  ImUnloadAll */
  if (((g_dwInitFlag != 0) && (g_dwLoadSoundFunc != 0)) &&
     (piVar1 = g_pLoadedList, g_dwUnloadSoundFunc != 0)) {
    for (; piVar1 != (int *)0x0; piVar1 = (int *)piVar1[1]) {
      piVar1[0xc] = 0;
    }
    uVar2 = ImFlushSounds();
    return uVar2;
  }
  return g_pLoadedList;
}

/* ---- 0x10004140  ImOpenSound ---- */
int ImOpenSound(char *param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  char *fmt;
  
                    /* 0x4140  18  ImOpenSound */
  if ((((g_dwInitFlag != 0) && (*param_1 != '\0')) && (g_dwOpenSoundFunc != (code *)0x0)) &&
     (g_dwCloseSoundFunc != 0)) {
    iVar2 = ImFindSound(param_1);
    piVar4 = g_pOpenedList;
    if (iVar2 != 0) {
      for (; piVar4 != (int *)0x0; piVar4 = (int *)piVar4[1]) {
        if (iVar2 == piVar4[2]) {
          piVar4[0xc] = piVar4[0xc] + 1;
          return iVar2;
        }
      }
    }
    piVar4 = (int *)((unsigned)(uintptr_t)&DAT_1002dae8);
    while (piVar4[2] != 0) {
      piVar4 = piVar4 + 0xd;
      if (((unsigned)(uintptr_t)&DAT_1002dcef) < (int)piVar4) {
        ImPrintf((char *)((unsigned)(uintptr_t)&DAT_10017210));
        return 0;
      }
    }
    iVar2 = (*g_dwOpenSoundFunc)(param_1,param_2);
    if (iVar2 == 0) {
      fmt = (char *)((unsigned)(uintptr_t)&DAT_10017224);
    }
    else {
      cVar1 = *param_1;
      iVar3 = 0;
      while( true ) {
        if (cVar1 == '\0') {
          *(undefined1 *)(iVar3 + 0xc + (int)piVar4) = 0;
          piVar4[2] = iVar2;
          piVar4[0xc] = 1;
          FUN_10004460((int *)&g_pOpenedList,piVar4);
          return iVar2;
        }
        if (0x1f < iVar3) break;
        *(char *)(iVar3 + 0xc + (int)piVar4) = param_1[iVar3];
        cVar1 = param_1[iVar3 + 1];
        iVar3 = iVar3 + 1;
      }
      fmt = (char *)((unsigned)(uintptr_t)&DAT_100171e4);
    }
    ImPrintf(fmt);
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
  if (((g_dwInitFlag == 0) || (g_dwOpenSoundFunc == 0)) ||
     (piVar1 = g_pOpenedList, g_dwCloseSoundFunc == 0)) {
    return g_pOpenedList;
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
  if (((g_dwInitFlag != 0) && (g_dwOpenSoundFunc != 0)) &&
     (piVar1 = g_pOpenedList, g_dwCloseSoundFunc != 0)) {
    for (; piVar1 != (int *)0x0; piVar1 = (int *)piVar1[1]) {
      piVar1[0xc] = 0;
    }
    uVar2 = ImFlushSounds();
    return uVar2;
  }
  return g_pOpenedList;
}

/* ---- 0x100042f0  ImFindSound ---- */
int ImFindSound(char *param_1)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  
                    /* 0x42f0  8  ImFindSound */
  if (g_pLoadedList != (int *)0x0) {
    piVar3 = g_pLoadedList;
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
  if (g_pOpenedList == (int *)0x0) {
    return 0;
  }
  piVar3 = g_pOpenedList;
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
  
  piVar1 = g_pLoadedList;
  while (piVar2 = piVar1, piVar1 = g_pOpenedList, piVar2 != (int *)0x0) {
    in_EAX = piVar2[0xc];
    piVar1 = (int *)piVar2[1];
    if (((in_EAX == 0) && (in_EAX = ImGetParam(piVar2[2],0x100), in_EAX == 0)) &&
       (in_EAX = ImGetParam(piVar2[2],0x200), in_EAX == 0)) {
      if (g_dwUnloadSoundFunc != (code *)0x0) {
        (*g_dwUnloadSoundFunc)(piVar2[2]);
      }
      piVar2[2] = 0;
      in_EAX = FUN_100044b0((int *)&g_pLoadedList,piVar2);
    }
  }
  while (piVar2 = piVar1, piVar2 != (int *)0x0) {
    in_EAX = piVar2[0xc];
    piVar1 = (int *)piVar2[1];
    if (((in_EAX == 0) && (in_EAX = ImGetParam(piVar2[2],0x100), in_EAX == 0)) &&
       (in_EAX = ImGetParam(piVar2[2],0x200), in_EAX == 0)) {
      if (g_dwCloseSoundFunc != (code *)0x0) {
        (*g_dwCloseSoundFunc)(piVar2[2]);
      }
      piVar2[2] = 0;
      in_EAX = FUN_100044b0((int *)&g_pOpenedList,piVar2);
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
  ImPrintf((char *)((unsigned)(uintptr_t)&DAT_10017240));
  return 0xfffffffb;
}

/* ---- 0x100044b0  FUN_100044b0 ---- */
undefined4 __cdecl FUN_100044b0(int *param_1,int *param_2)

{
  int *piVar1;
  
  piVar1 = (int *)*param_1;
  if ((param_2 == (int *)0x0) || (piVar1 == (int *)0x0)) {
    ImPrintf((char *)((unsigned)(uintptr_t)&DAT_10017268));
    return 0xfffffffb;
  }
  do {
    if (piVar1 == param_2) break;
    piVar1 = (int *)piVar1[1];
  } while (piVar1 != (int *)0x0);
  if (piVar1 == (int *)0x0) {
    ImPrintf((char *)((unsigned)(uintptr_t)&DAT_10017290));
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
  if (g_dwIm_initialized == 0) {
    g_dwRunning50HzCount = 0;
    g_dwRunning10HzCount = 0;
    iVar1 = GrInitialize();
    if (iVar1 == 0) {
      iVar1 = FdInitialize();
      if (iVar1 == 0) {
        iVar1 = TgInitialize();
        if (iVar1 == 0) {
          iVar1 = TrInitialize();
          if (iVar1 == 0) {
            g_dwWvSlicingHalted = 0;
            g_dwIntFlag = 0;
            g_dwPauseCount = 0;
            g_dwIm_initialized = 1;
            return 0x31;
          }
        }
      }
    }
  }
  return 0xffffffff;
}

/* ---- 0x10004b20  ImPrintf ---- */
undefined4 __cdecl ImPrintf(char *fmt,...)

{
                    /* 0x4b20  20  ImPrintf */
  FUN_1000b8d0((undefined1 *)((unsigned)(uintptr_t)&DAT_1002de00),fmt,&STACK0X(0x00000008));
  return 0;
}

/* ---- 0x10004b40  ImPause ---- */
int ImPause(void)

{
  int iVar1;
  bool bVar2;
  
                    /* 0x4b40  19  ImPause */
  iVar1 = g_dwPauseCount + 1;
  bVar2 = g_dwPauseCount == 0;
  g_dwPauseCount = iVar1;
  if (bVar2) {
    TrPause();
  }
  return g_dwPauseCount;
}

/* ---- 0x10004b60  ImResume ---- */
int ImResume(void)

{
                    /* 0x4b60  27  ImResume */
  g_dwPauseCount = g_dwPauseCount + -1;
  if (g_dwPauseCount == 0) {
    TrResume();
    return g_dwPauseCount;
  }
  if (g_dwPauseCount < 0) {
    g_dwPauseCount = 0;
  }
  return g_dwPauseCount;
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
  iVar1 = FdSave(param_1 + 1,param_2 - 4);
  if (-1 < iVar1) {
    iVar2 = iVar1 + 4;
    iVar1 = TgSave((undefined4 *)(iVar2 + (int)param_1),param_2 - iVar2);
    if (-1 < iVar1) {
      iVar2 = iVar2 + iVar1;
      iVar1 = TrSave((undefined4 *)(iVar2 + (int)param_1),param_2 - iVar2);
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
  iVar1 = FdRestore(param_1 + 1);
  iVar2 = TgRestore((undefined4 *)(iVar1 + 4 + (int)param_1));
  iVar2 = iVar1 + 4 + iVar2;
  iVar1 = TrRestore((undefined4 *)(iVar2 + (int)param_1));
  return iVar2 + iVar1;
}

/* ---- 0x10004c60  ImSetGroupVol ---- */
undefined4 __cdecl ImSetGroupVol(uint param_1,uint param_2)

{
  undefined4 uVar1;
  
                    /* 0x4c60  33  ImSetGroupVol */
  uVar1 = GrSetGroupVol(param_1,param_2);
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
  pcVar1 = (char *)FmGetMapAddr(param_1);
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
    uVar3 = TrStartSound(param_1,param_2,0);
  }
  return uVar3;
}

/* ---- 0x10004cd0  ImStopSound ---- */
undefined4 __cdecl ImStopSound(int param_1)

{
  undefined4 uVar1;
  
                    /* 0x4cd0  44  ImStopSound */
  uVar1 = TrStopSound(param_1);
  return uVar1;
}

/* ---- 0x10004ce0  ImStopAllSounds ---- */
undefined4 ImStopAllSounds(void)

{
  undefined4 uVar1;
  
                    /* 0x4ce0  42  ImStopAllSounds */
  ((code *)ImWaveHalt)();
  uVar1 = TrStopAllSounds();
  ImWaveProceed();
  return uVar1;
}

/* ---- 0x10004d00  ImGetNextSound ---- */
uint __cdecl ImGetNextSound(uint param_1)

{
  uint uVar1;
  
                    /* 0x4d00  11  ImGetNextSound */
  uVar1 = TrGetNextSound(param_1);
  return uVar1;
}

/* ---- 0x10004d10  ImSetParam ---- */
undefined4 __cdecl ImSetParam(int param_1,int param_2,uint param_3)

{
  undefined4 uVar1;
  
                    /* 0x4d10  35  ImSetParam */
  uVar1 = TrSetParam(param_1,param_2,param_3);
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
    uVar1 = TgGetPendCount(param_1);
    return uVar1;
  }
  ImWaveHalt();
  uVar1 = TrGetParam(param_1,param_2);
  ImWaveProceed();
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
  uVar1 = FdFadeParam(param_1,param_2,param_3,param_4);
  return uVar1;
}

/* ---- 0x10004db0  ImSetHook ---- */
undefined4 __cdecl ImSetHook(int param_1,uint param_2)

{
  undefined4 uVar1;
  
                    /* 0x4db0  34  ImSetHook */
  uVar1 = TrSetHook(param_1,param_2);
  return uVar1;
}

/* ---- 0x10004dd0  ImGetHook ---- */
undefined4 __cdecl ImGetHook(int param_1)

{
  undefined4 uVar1;
  
                    /* 0x4dd0  10  ImGetHook */
  uVar1 = TrGetHook(param_1);
  return uVar1;
}

/* ---- 0x10004de0  ImSetTrigger ---- */
undefined4 __cdecl
ImSetTrigger(int sound,char *marker,int cmd,int p0,int p1,int p2,int p3,int p4,int p5,int p6,int p7,
            int p8,int p9)

{
  undefined4 uVar1;
  
                    /* 0x4de0  38  ImSetTrigger */
  uVar1 = TgSetTrigger(sound,marker,cmd,p9,p9,p9,p9,p9,p9,p9,p9,p9,p9);
  return uVar1;
}

/* ---- 0x10004e10  ImCheckTrigger ---- */
int __cdecl ImCheckTrigger(int param_1,byte *param_2,int param_3)

{
  int iVar1;
  
                    /* 0x4e10  1  ImCheckTrigger */
  iVar1 = TgCheckTrigger(param_1,param_2,param_3);
  return iVar1;
}

/* ---- 0x10004e30  ImClearTrigger ---- */
undefined4 __cdecl ImClearTrigger(int param_1,byte *param_2,int param_3)

{
  undefined4 uVar1;
  
                    /* 0x4e30  2  ImClearTrigger */
  uVar1 = TgClearTrigger(param_1,param_2,param_3);
  return uVar1;
}

/* ---- 0x10004e50  ImDeferCommand ---- */
undefined4 __cdecl
ImDeferCommand(int time,int cmd,int p0,int p1,int p2,int p3,int p4,int p5,int p6,int p7,int p8,
              int p9)

{
  undefined4 uVar1;
  
                    /* 0x4e50  5  ImDeferCommand */
  uVar1 = TgDeferCommand(time,cmd,p9,p9,p9,p9,p9,p9,p9,p9,p9,p9);
  return uVar1;
}

/* ---- 0x10004e80  ImStartStream ---- */
undefined4 __cdecl ImStartStream(uint param_1,int param_2,uint param_3)

{
  int iVar1;
  undefined4 uVar2;
  
                    /* 0x4e80  41  ImStartStream */
  iVar1 = FmValidateSoundId(param_1);
  if (iVar1 != 0) {
    ImWaveHalt();
    uVar2 = TrStartSound(param_1,param_2,param_3);
    ImWaveProceed();
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
  uVar1 = DpSwitchStream(param_1,param_2,param_3,param_4,param_5);
  return uVar1;
}

/* ---- 0x10004f00  ImQueryStream ---- */
undefined4 __cdecl
ImQueryStream(int param_1,undefined4 *param_2,undefined4 *param_3,int *param_4,undefined4 *param_5)

{
  undefined4 uVar1;
  
                    /* 0x4f00  22  ImQueryStream */
  uVar1 = TrQueryStream(param_1,param_2,param_3,param_4,param_5);
  return uVar1;
}

/* ---- 0x10004f30  ImFeedStream ---- */
undefined4 __cdecl ImFeedStream(int param_1,undefined4 *param_2,uint param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
                    /* 0x4f30  7  ImFeedStream */
  uVar1 = TrFeedStream(param_1,param_2,param_3,param_4);
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
  if (((g_dwIntFlag == 0) && (g_dwWvSlicingHalted == 0)) &&
     (((int)DAT_100172bc < 0 || (0x13 < uVar1 - DAT_100172bc)))) {
    g_dwIntFlag = 1;
    DAT_100172bc = uVar1;
    TrIntHandler();
    uVar1 = g_dwPauseCount;
    if (g_dwPauseCount == 0) {
      g_dwRunning50HzCount = g_dwRunning50HzCount + 20000;
      while (19999 < g_dwRunning50HzCount) {
        g_dwRunning50HzCount = g_dwRunning50HzCount - 20000;
        FdIntHandler();
        TgIntHandler();
      }
      uVar1 = g_dwRunning10HzCount + 20000;
      g_dwRunning10HzCount = uVar1;
joined_r0x1000522c:
      if (199999 < g_dwRunning10HzCount) {
        g_dwRunning10HzCount = g_dwRunning10HzCount - 200000;
        uVar2 = GrSetGroupVol(3,0xffffffff);
        for (uVar1 = ImGetNextSound(0); uVar1 != 0; uVar1 = ImGetNextSound(uVar1)) {
          uVar3 = ImGetParam(uVar1,0x400);
          if (uVar3 == 2) {
            uVar2 = uVar2 * 0x4d >> 7;
            break;
          }
        }
        uVar3 = GrSetGroupVol(4,0xffffffff);
        uVar1 = GrSetGroupVol(3,0xffffffff);
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
    g_dwIntFlag = 0;
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
    uVar1 = GrSetGroupVol(4,uVar1);
  }
  goto joined_r0x1000522c;
}

/* ---- 0x10005300  ImStartRecording ---- */
undefined4 ImStartRecording(undefined4 param_1,int param_2)

{
                    /* 0x5300  39  ImStartRecording */
  g_dwRecordFile = (int *)FUN_1000ba60(param_1,((unsigned)(uintptr_t)&DAT_100172c4));
  if (g_dwRecordFile == (int *)0x0) {
    g_dwRecordState = 0;
  }
  else {
    g_dwRecordState = 2 - (uint)(param_2 != 0);
  }
  g_dwDataSizeInBytes = 0;
  ImFile_Read(g_dwRecordFile,0x2c,0);
  return 0;
}

/* ---- 0x10005350  ImStopRecording ---- */
undefined4 ImStopRecording(void)

{
                    /* 0x5350  43  ImStopRecording */
  g_dwRecordState = 3;
  return 0;
}

/* ---- 0x10007130  ImInitializeScript ---- */
undefined4 __cdecl ImInitializeScript(int a1,int a2,int a3,int a4,int a5,int a6,int a7)

{
  undefined4 uVar1;
  
                    /* 0x7130  16  ImInitializeScript */
  uVar1 = ScriptCall(0,&g_dwImuseInitData,a1,a2,a3,a4,a5,a6,a7);
  return uVar1;
}

/* ---- 0x10007170  ImTerminateScript ---- */
undefined4 __cdecl ImTerminateScript(void)

{
  undefined4 uVar1;
  
                    /* 0x7170  47  ImTerminateScript */
  uVar1 = ScriptCall(1);
  return uVar1;
}

/* ---- 0x10007180  ImSaveScript ---- */
undefined4 __cdecl ImSaveScript(int a1,int a2)

{
  undefined4 uVar1;
  
                    /* 0x7180  30  ImSaveScript */
  uVar1 = ScriptCall(2,a1,a2);
  return uVar1;
}

/* ---- 0x100071a0  ImRestoreScript ---- */
undefined4 __cdecl ImRestoreScript(int a1)

{
  undefined4 uVar1;
  
                    /* 0x71a0  26  ImRestoreScript */
  uVar1 = ScriptCall(3,a1);
  return uVar1;
}

/* ---- 0x100071b0  ImRefreshScript ---- */
undefined4 __cdecl ImRefreshScript(void)

{
  undefined4 uVar1;
  
                    /* 0x71b0  23  ImRefreshScript */
  uVar1 = ScriptCall(4);
  return uVar1;
}

/* ---- 0x100071c0  ImSetState ---- */
undefined4 __cdecl ImSetState(int a1)

{
  undefined4 uVar1;
  
                    /* 0x71c0  37  ImSetState */
  uVar1 = ScriptCall(5,a1);
  return uVar1;
}

/* ---- 0x100071d0  ImSetSequence ---- */
undefined4 __cdecl ImSetSequence(int a1)

{
  undefined4 uVar1;
  
                    /* 0x71d0  36  ImSetSequence */
  uVar1 = ScriptCall(6,a1);
  return uVar1;
}

/* ---- 0x100071e0  ImSetCuePoint ---- */
undefined4 __cdecl ImSetCuePoint(int a1)

{
  undefined4 uVar1;
  
                    /* 0x71e0  32  ImSetCuePoint */
  uVar1 = ScriptCall(7,a1);
  return uVar1;
}

/* ---- 0x100071f0  ImSetAttribute ---- */
undefined4 __cdecl ImSetAttribute(int a1,int a2)

{
  undefined4 uVar1;
  
                    /* 0x71f0  31  ImSetAttribute */
  uVar1 = ScriptCall(8,a1,a2);
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
  uVar1 = (**(code **)(g_dwSounds_pHS + 0x20))
                    (param_2,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0x11d);
  *(undefined4 *)(iVar2 + ((unsigned)(uintptr_t)&DAT_1002ebe4)) = param_2;
  *(undefined4 *)(iVar2 + ((unsigned)(uintptr_t)&DAT_1002ebe0)) = uVar1;
  *(undefined4 *)(iVar2 + ((unsigned)(uintptr_t)&DAT_1002ebe8)) = param_3;
  *(undefined4 *)(iVar2 + ((unsigned)(uintptr_t)&DAT_1002ebec)) = param_4;
  return uVar1;
}

/* ---- 0x10007250  ihost_close_sound ---- */
/* Original name ihost_close_sound (the remaster's GrimFandango (Linux): the fourth function
   sounds_startup passes to ImInitializeScript in both builds (ihost_load_sound, ihost_unload_sound,
   ihost_open_sound, ihost_close_sound); same body (sound id - 10000 indexes streamID, the file is
   closed when the use count is below 2, else the count drops); also SoundStopVoiceStream's call
   (inlined there in the remaster)); was FUN_10007250. */

undefined4 __cdecl ihost_close_sound(int param_1)

{
  int iVar1;
  
  iVar1 = (param_1 + -10000) * 0x28;
  if (*(undefined4 **)(&g_aStreamID + iVar1) == (undefined4 *)0x0) {
    return 1;
  }
  if (*(int *)(iVar1 + ((unsigned)(uintptr_t)&DAT_1002eb34)) < 2) {
    iRes_FCLOSE(*(undefined4 **)(&g_aStreamID + iVar1));
    *(undefined4 *)(&g_aStreamID + iVar1) = 0;
    *(undefined1 *)(iVar1 + ((unsigned)(uintptr_t)&DAT_1002eb14)) = 0;
    *(undefined4 *)(iVar1 + ((unsigned)(uintptr_t)&DAT_1002eb34)) = 0;
    return 0;
  }
  *(int *)(iVar1 + ((unsigned)(uintptr_t)&DAT_1002eb34)) = *(int *)(iVar1 + ((unsigned)(uintptr_t)&DAT_1002eb34)) + -1;
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
  pcVar7 = &g_aLastVoiceFilename;
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
    LoadLip(acStack_20,(char *)0x2710);
  }
  piVar3 = iRes_FOPEN(param_1,&DAT_1001e900);
  _g_aStreamID = piVar3;
  if (piVar3 != (int *)0x0) {
    iRes_FSEEK((undefined *)piVar3,0,2);
    iVar4 = iRes_FTELL((undefined *)_g_aStreamID);
    iRes_FSEEK((undefined *)_g_aStreamID,0,0);
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
  if (_g_aStreamID != (undefined4 *)0x0) {
    iRes_FCLOSE(_g_aStreamID);
    uVar1 = ((code *)Im_SoundsFreeSlot)(10000);
    _g_aStreamID = (undefined4 *)0x0;
  }
  return uVar1;
}

/* ---- 0x100073f0  SoundsReOpenVoiceFile ---- */
undefined4 __cdecl SoundsReOpenVoiceFile(void)

{
  undefined4 uVar1;
  
                    /* 0x73f0  66  SoundsReOpenVoiceFile */
  uVar1 = SoundsCloseVoiceFile();
  uVar1 = CONCAT31((int3)((uint)uVar1 >> 8),g_aLastVoiceFilename);
  if (g_aLastVoiceFilename != '\0') {
    uVar1 = SoundsRegisterVoice(&g_aLastVoiceFilename);
  }
  return uVar1;
}

/* ---- 0x10007410  SoundsLoadStartSound ---- */
undefined4 __cdecl SoundsLoadStartSound(uint *param_1,int param_2,uint param_3)

{
  uint uVar1;
  
                    /* 0x7410  64  SoundsLoadStartSound */
  uVar1 = CacheGetSoundId(param_1);
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
  uVar1 = CacheGetSoundId(param_1);
  if (uVar1 == 0) {
    return 0;
  }
  if (0x7c < param_2) {
    param_2 = 0x7c;
  }
  if (g_dwUseVoxFx != 0) {
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
  iVar1 = CacheGetSoundId(param_1);
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
  iVar1 = CacheGetSoundId(param_1);
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
  iVar1 = CacheGetSoundId(param_1);
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
  iVar1 = CacheGetSoundId(param_1);
  if (iVar1 == 0) {
    return 1;
  }
  uVar2 = ImFadeParam(iVar1,param_2,param_3,(param_4 * 0x3c) / 1000);
  return uVar2;
}

/* ---- 0x100075d0  SoundsIsSoundInUse ---- */
int __cdecl SoundsIsSoundInUse(uint *param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
                    /* 0x75d0  61  SoundsIsSoundInUse */
  iVar1 = CacheGetSoundId(param_1);
  iVar3 = iVar1 + -100;
  if ((((-1 < iVar3) && (iVar3 < 0x20)) && ((&g_bSoundCache)[iVar3 * 0x40] != '\0')) &&
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
int __cdecl SoundsIsSoundPlaying(uint *param_1)

{
  int iVar1;
  uint uVar2;
  
                    /* 0x7640  62  SoundsIsSoundPlaying */
  iVar1 = CacheGetSoundId(param_1);
  uVar2 = ImGetParam(iVar1,0x100);
  return 0 < (int)uVar2;
}

/* ---- 0x10007670  SoundsFillStreamsWhileMusicCritical ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl SoundsFillStreamsWhileMusicCritical(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
                    /* 0x7670  56  SoundsFillStreamsWhileMusicCritical */
  uVar2 = 0;
  if (_g_bImuseInitialized != 0) {
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
#endif


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
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl SoundsFloodMusicBuffer(void)

{
  int iVar1;
  
                    /* 0x7790  57  SoundsFloodMusicBuffer */
  iVar1 = 0;
  if (_g_bImuseInitialized != 0) {
    iVar1 = FUN_100077c0();
    while (iVar1 == 0) {
      ImProcessStreams();
      iVar1 = FUN_100077c0();
    }
  }
  return iVar1;
}
#endif


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
  if (((iVar1 != 0) && (local_10 == 0)) && (local_8 <= local_c - _g_dwImMusicGulpSize)) {
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

void __cdecl SoundsPeriodic(void)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  
                    /* 0x7810  65  SoundsPeriodic */
  if (_g_bImuseInitialized != 0) {
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
    if (_g_dwImNonPurgeCacheSize < iVar2) {
      CachePurgeOldestStoppedSound();
    }
    return;
  }
  return;
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
  _g_bMuscriptLocal = param_1;
  return param_1;
}

/* ---- 0x100078b0  SoundsSetMuscriptRemote ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl SoundsSetMuscriptRemote(undefined4 param_1)

{
                    /* 0x78b0  69  SoundsSetMuscriptRemote */
  _g_bMuscriptRemote = param_1;
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
  g_dwSounds_pHS = param_1;
  *param_2 = SoundsInitialize;
  param_2[1] = 0;
  param_2[2] = sounds_startup;
  param_2[3] = sounds_shutdown;
  param_2[4] = sounds_save;
  param_2[5] = sounds_restore;
  param_2[6] = sounds_pause;
  param_2[7] = sounds_resume;
  return 0;
}

/* ---- 0x10007920  sounds_startup ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Original name sounds_startup (the remaster's GrimFandango (Linux): the only unmatched caller of
   ImInitializeScript; 2 matched neighbours agree, 1 disagree); was FUN_10007920. */

undefined4 sounds_startup(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (DAT_100336bc != 0) {
    FUN_10007a20();
    if (_g_dwEffectsHeapSize != 0) {
      FUN_10004660(_g_dwEffectsHeapSize);
    }
    puVar2 = (undefined4 *)&g_bSoundCache;
    for (iVar1 = 0x200; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
    }
    puVar2 = (undefined4 *)&g_aStreamID;
    for (iVar1 = 0x32; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
    }
    iVar1 = FUN_10008ce0();
    if (iVar1 == 0) {
      return 1;
    }
    g_dwImuseInitData = ihost_get_map_addr;
    DAT_100336a4 = ihost_get_sound_addr;
    DAT_100336b4 = ihost_get_buffer_info;
    DAT_100336ac = ihost_fseek;
    DAT_100336b0 = ihost_read;
    ImInitialize();
    SoundsAllocateBuffer(2,_g_dwImMusicBufferSize,_g_dwImMusicGulpSize,_g_dwImMusicCriticalSize);
    SoundsAllocateBuffer(1,_g_dwImVoiceBufferSize,_g_dwImVoiceGulpSize,_g_dwImVoiceCriticalSize);
    ImInitializeScript(((unsigned)(uintptr_t)FUN_100067a0),((unsigned)(uintptr_t)FUN_100067a0),((unsigned)(uintptr_t)ihost_open_sound),((unsigned)(uintptr_t)ihost_close_sound),0,0,_g_bMuscriptLocal);
    _g_bImuseInitialized = 1;
  }
  return 0;
}

/* ---- 0x10007a20  FUN_10007a20 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_10007a20(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  _g_dwMlEntryCount = 0x14;
  _g_dwMlEntries =
       (undefined4 *)
       (**(code **)(g_dwSounds_pHS + 0x20))(0x50,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0x7a);
  if (_g_dwMlEntries != (undefined4 *)0x0) {
    puVar2 = _g_dwMlEntries;
    for (iVar1 = 0x14; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
    }
    _g_dwMlListSize = 0;
  }
  return;
}

/* ---- 0x10007a60  ihost_get_sound_addr ---- */
/* Original name ihost_get_sound_addr (the remaster's GrimFandango (Linux): aligned call in
   sounds_startup); was FUN_10007a60. */

void ihost_get_sound_addr(undefined4 param_1)

{
  FUN_10009530(param_1);
  return;
}

/* ---- 0x10007a70  ihost_get_map_addr ---- */
/* Original name ihost_get_map_addr (the remaster's GrimFandango (Linux): aligned call in
   sounds_startup); was FUN_10007a70. */

void ihost_get_map_addr(undefined4 param_1)

{
  FUN_10009560(param_1);
  return;
}

/* ---- 0x10007a80  ihost_get_buffer_info ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name ihost_get_buffer_info (the remaster's GrimFandango (Linux): aligned call in
   sounds_startup); was FUN_10007a80. */

int ihost_get_buffer_info(int param_1)

{
  return param_1 * 0x10 + 0x1002ebe0;
}
#endif


/* ---- 0x10007a90  ihost_open_sound ---- */
/* Original name ihost_open_sound (the remaster's GrimFandango (Linux): same body (0x28-byte stream
   slots from id 10000, iRes_FOPEN, 0x20-byte name, use count); the only unpaired caller of
   iRes_FOPEN on both sides); was FUN_10007a90. */

int ihost_open_sound(uint *param_1,int param_2)

{
  byte bVar1;
  int *piVar2;
  byte *pbVar3;
  int iVar4;
  int iVar5;
  uint *puVar6;
  byte *pbVar7;
  bool bVar8;
  
  if (param_2 != 0) {
    iVar5 = (param_2 + -10000) * 0x28;
    piVar2 = iRes_FOPEN(param_1,&DAT_1001e900);
    *(int **)(&g_aStreamID + iVar5) = piVar2;
    Im_MemCopy((uint *)(iVar5 + ((unsigned)(uintptr_t)&DAT_1002eb14)),param_1,0x20);
    *(undefined1 *)(iVar5 + ((unsigned)(uintptr_t)&DAT_1002eb33)) = 0;
    *(undefined4 *)(iVar5 + ((unsigned)(uintptr_t)&DAT_1002eb34)) = 1;
    return param_2;
  }
  iVar5 = 1;
  pbVar7 = (byte *)((unsigned)(uintptr_t)&DAT_1002eb3c);
  do {
    if (*(int *)(pbVar7 + -4) == 0) {
      piVar2 = iRes_FOPEN(param_1,&DAT_1001e900);
      iVar4 = iVar5 * 0x28;
      *(int **)(&g_aStreamID + iVar4) = piVar2;
      if (piVar2 == (int *)0x0) {
        return 0;
      }
      Im_MemCopy((uint *)(iVar4 + ((unsigned)(uintptr_t)&DAT_1002eb14)),param_1,0x20);
      *(undefined1 *)(iVar4 + ((unsigned)(uintptr_t)&DAT_1002eb33)) = 0;
      *(undefined4 *)(iVar4 + ((unsigned)(uintptr_t)&DAT_1002eb34)) = 1;
      return iVar5 + 10000;
    }
    pbVar3 = pbVar7;
    puVar6 = param_1;
    if (*pbVar7 != 0) {
      do {
        bVar1 = *pbVar3;
        bVar8 = bVar1 < (byte)*puVar6;
        if (bVar1 != (byte)*puVar6) {
LAB_10007b28:
          iVar4 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
          goto LAB_10007b2d;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar3[1];
        bVar8 = bVar1 < *(byte *)((int)puVar6 + 1);
        if (bVar1 != *(byte *)((int)puVar6 + 1)) goto LAB_10007b28;
        pbVar3 = pbVar3 + 2;
        puVar6 = (uint *)((int)puVar6 + 2);
      } while (bVar1 != 0);
      iVar4 = 0;
LAB_10007b2d:
      if (iVar4 == 0) {
        *(int *)(iVar5 * 0x28 + ((unsigned)(uintptr_t)&DAT_1002eb34)) = *(int *)(iVar5 * 0x28 + ((unsigned)(uintptr_t)&DAT_1002eb34)) + 1;
        return iVar5 + 10000;
      }
    }
    pbVar7 = pbVar7 + 0x28;
    iVar5 = iVar5 + 1;
    if (((unsigned)(uintptr_t)&DAT_1002ebdb) < (int)pbVar7) {
      return 0;
    }
  } while( true );
}

/* ---- 0x10007bc0  ihost_fseek ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Original name ihost_fseek (the remaster's GrimFandango (Linux): aligned call in sounds_startup);
   was FUN_10007bc0. */

int ihost_fseek(int param_1,int param_2,int param_3)

{
  undefined *puVar1;
  int iVar2;
  
  if (((9999 < param_1) && (param_1 < 0x2715)) &&
     (puVar1 = *(undefined **)(&g_aStreamID + (param_1 + -10000) * 0x28), puVar1 != (undefined *)0x0
     )) {
    iVar2 = iRes_FSEEK(puVar1,param_2,param_3);
    if (iVar2 == 0) {
      if (((param_1 == 10000) && (g_dwUseVoxFx != 0)) && (param_3 == 2)) {
        iVar2 = iRes_FTELL(puVar1);
        return (iVar2 + -0x2c + _g_dwTAIL_BYTES) * g_dwUseVoxFx + 0x2c;
      }
      if (((param_1 != 10000) || (g_dwUseVoxFx == 0)) || (param_3 != 0)) {
        iVar2 = iRes_FTELL(puVar1);
        return iVar2;
      }
      iVar2 = param_2;
      if (0x2c < param_2) {
        iVar2 = (param_2 - 0x2cU) / g_dwUseVoxFx + 0x2c;
      }
      iVar2 = iRes_FSEEK(puVar1,iVar2,0);
      if (iVar2 == 0) {
        return param_2;
      }
    }
  }
  return 0;
}

/* ---- 0x10007ca0  ihost_read ---- */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Original name ihost_read (the remaster's GrimFandango (Linux): the iMUSE host read callback:
   per-sound file handle table, voice sound 10000 with useVoxFx measures the file by seeking to the
   end, as the remaster's ihost_read); was FUN_10007ca0. */

undefined4 * ihost_read(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

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
  
  puVar4 = *(undefined4 **)(&g_aStreamID + (int)(param_1 + -0x9c4) * 0x28);
  if (puVar4 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  if ((param_1 == (undefined4 *)0x2710) && (g_dwUseVoxFx != 0)) {
    iVar2 = iRes_FTELL((undefined *)puVar4);
    iRes_FSEEK((undefined *)puVar4,0,2);
    iVar3 = iRes_FTELL((undefined *)puVar4);
    iRes_FSEEK((undefined *)puVar4,iVar2,0);
    puVar1 = param_3;
    if ((int)_DAT_10031e5c < (int)param_3) {
      if (_DAT_10031e58 != (undefined4 *)0x0) {
        (**(code **)(g_dwSounds_pHS + 0x24))(_DAT_10031e58);
        _DAT_10031e58 = (undefined4 *)0x0;
      }
      _DAT_10031e58 =
           (undefined4 *)
           (**(code **)(g_dwSounds_pHS + 0x20))
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
        puVar8 = (undefined4 *)((int)_g_dwVoxFxBuf + (int)_DAT_10031e6c);
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
      uVar5 = iRes_FREAD(puVar4,_DAT_10031e58,(uint)puVar8 / g_dwUseVoxFx + 0x2c);
      iVar2 = iRes_FTELL((undefined *)puVar4);
      puVar4 = param_2;
      uStack_c = (uint)(iVar3 <= iVar2);
      puVar10 = _DAT_10031e58;
      puVar6 = param_2;
      for (iVar2 = 0xb; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar6 = *puVar10;
        puVar10 = puVar10 + 1;
        puVar6 = puVar6 + 1;
      }
      iVar2 = param_2[10] + _g_dwTAIL_BYTES;
      param_2[10] = iVar2;
      param_2[10] = g_dwUseVoxFx * iVar2;
      param_2[7] = g_dwUseVoxFx * param_2[7];
      if (1 < g_dwUseVoxFx) {
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
            if (_g_dwVoxFxBuf != (undefined4 *)0x0) {
              (**(code **)(g_dwSounds_pHS + 0x24))(_g_dwVoxFxBuf);
              _g_dwVoxFxBuf = (undefined4 *)0x0;
            }
            _g_dwVoxFxBuf =
                 (undefined4 *)
                 (**(code **)(g_dwSounds_pHS + 0x20))
                           (_DAT_10031e64,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0x212);
            _DAT_10031e68 = _DAT_10031e64;
          }
          uVar5 = _DAT_10031e64;
          puVar4 = (undefined4 *)((int)param_3 + (int)puVar8);
          puVar8 = _g_dwVoxFxBuf;
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
      uVar5 = iRes_FREAD(puVar4,_DAT_10031e58,(uint)puVar1 / g_dwUseVoxFx);
      iVar2 = iRes_FTELL((undefined *)puVar4);
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
          if (_g_dwVoxFxBuf != (undefined4 *)0x0) {
            (**(code **)(g_dwSounds_pHS + 0x24))(_g_dwVoxFxBuf);
            _g_dwVoxFxBuf = (undefined4 *)0x0;
          }
          _g_dwVoxFxBuf =
               (undefined4 *)
               (**(code **)(g_dwSounds_pHS + 0x20))
                         (_DAT_10031e64,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0x23b);
          _DAT_10031e68 = _DAT_10031e64;
        }
        uVar5 = _DAT_10031e64;
        puVar4 = (undefined4 *)((int)param_3 + (int)puVar1);
        puVar8 = _g_dwVoxFxBuf;
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
  puVar4 = (undefined4 *)iRes_FREAD(puVar4,param_2,(uint)param_3);
  return puVar4;
}
#undef uStack_c


/* ---- 0x10008140  sounds_shutdown ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Original name sounds_shutdown (the remaster's GrimFandango (Linux): the only unmatched caller of
   ImRefreshScript; 3 matched neighbours agree, 0 disagree); was FUN_10008140. */

void sounds_shutdown(void)

{
  int *piVar1;
  
  if (DAT_100336bc != 0) {
    FUN_10008e30();
    ImStopAllSounds();
    ImRefreshScript();
    ImHeartbeat();
    if (_g_dwEffectsHeapSize != 0) {
      FUN_10004970();
    }
    if (_DAT_10031e58 != 0) {
      (**(code **)(g_dwSounds_pHS + 0x24))(_DAT_10031e58);
      _DAT_10031e58 = 0;
    }
    _DAT_10031e5c = 0;
    if (_g_dwVoxFxBuf != 0) {
      (**(code **)(g_dwSounds_pHS + 0x24))(_g_dwVoxFxBuf);
      _g_dwVoxFxBuf = 0;
    }
    _g_bImuseInitialized = 0;
    piVar1 = (int *)((unsigned)(uintptr_t)&DAT_1002ebe0);
    do {
      if (*piVar1 != 0) {
        (**(code **)(g_dwSounds_pHS + 0x24))(*piVar1);
        *piVar1 = 0;
      }
      piVar1 = piVar1 + 4;
    } while ((int)piVar1 < ((unsigned)(uintptr_t)&g_dwMlEntryCount));
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
  
  if (_g_dwMlEntries != (int *)0x0) {
    iVar2 = 0;
    piVar1 = _g_dwMlEntries;
    if (0 < _g_dwMlEntryCount) {
      do {
        if (*piVar1 != 0) {
          (**(code **)(g_dwSounds_pHS + 0x24))(*piVar1);
        }
        piVar1 = piVar1 + 1;
        iVar2 = iVar2 + 1;
      } while (iVar2 < _g_dwMlEntryCount);
    }
    (**(code **)(g_dwSounds_pHS + 0x24))(_g_dwMlEntries);
    _g_dwMlEntries = (int *)0x0;
  }
  return;
}

/* ---- 0x10008250  sounds_save ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Original name sounds_save (the remaster's GrimFandango (Linux): aligned call in
   SoundsInitialize); was FUN_10008250. */

undefined4 sounds_save(code *param_1)

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
           (**(code **)(g_dwSounds_pHS + 0x20))
                     (0x20000,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0x3f9);
  if (puVar2 == (undefined4 *)0x0) {
    return 1;
  }
  if (g_dwUseVoxFx == 0) {
    _g_aVoxFxName = _DAT_1001e90c;
  }
  g_aLastVoiceFilename = 0;
  puStack_4 = puVar2;
  (*param_1)(&g_aVoxFxName,0x28);
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
  } while ((int)piVar5 < ((unsigned)(uintptr_t)&g_aLastVoiceFilename));
  (*pcVar1)(&iStack_c,4);
  param_1 = (code *)0x0;
  pcVar6 = &g_bSoundCache;
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
  } while ((int)pcVar6 < ((unsigned)(uintptr_t)&DAT_10031d28));
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
  } while ((int)puVar2 < ((unsigned)(uintptr_t)&DAT_10031d48));
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
    if (((unsigned)(uintptr_t)&DAT_10031d4f) < (int)piVar5) {
      (**(code **)(g_dwSounds_pHS + 0x24))(puStack_4);
      return 0;
    }
  } while( true );
}
#undef iStack_10
#undef iStack_c
#undef puStack_4
#undef uStack_8


/* ---- 0x10008580  sounds_restore ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name sounds_restore (the remaster's GrimFandango (Linux): aligned call in
   SoundsInitialize); was FUN_10008580. */

undefined4 sounds_restore(code *param_1,uint param_2)

{
  unsigned char _frame[0x40];  /* Ghidra stack frame, see tools/frame_locals.py */
  int *a1;
  int iVar1;
  uint uVar2;
  int iVar3;
  #define iStack_28 (*(int *)(_frame + (0x40 - 0x28)))
  #define uStack_24 (*(undefined4 *)(_frame + (0x40 - 0x24)))
  #define puStack_20 (*(uint **)(_frame + (0x40 - 0x20)))
  #define auStack_1c (*(uint (*)[6])(_frame + (0x40 - 0x1c)))
  #define uStack_4 (*(uint *)(_frame + (0x40 - 0x4)))
  
  a1 = (int *)(**(code **)(g_dwSounds_pHS + 0x20))
                        (0x20000,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0x46a);
  if (a1 == (int *)0x0) {
    return 1;
  }
  iVar1 = (*param_1)(&g_aVoxFxName,0x28);
  if (iVar1 != 0) {
    return 1;
  }
  ((code *)FUN_10009700)(((unsigned)(uintptr_t)&DAT_1001e98c));
  ImStopAllSounds();
  ((code *)FUN_10009700)(((unsigned)(uintptr_t)&DAT_1001e97c));
  ImFlushSounds();
  ((code *)FUN_10009700)(((unsigned)(uintptr_t)&DAT_1001e970));
  SoundsCloseVoiceFile();
  ((code *)FUN_10009700)(((unsigned)(uintptr_t)&DAT_1001e958));
  FUN_10008e60();
  ((code *)FUN_10009700)(((unsigned)(uintptr_t)&DAT_1001e944));
  iMUSE_SetVoiceEffect((uint *)&g_aVoxFxName);
  g_aLastVoiceFilename = 0;
  (*param_1)(&uStack_24,4);
  (*param_1)(a1,uStack_24);
  iVar1 = ImRestore(a1);
  if (iVar1 != 0) {
    ((code *)FUN_10009700)(((unsigned)(uintptr_t)&DAT_1001e930));
    (*param_1)(&uStack_24,4);
    (*param_1)(a1,uStack_24);
    iVar1 = ImRestoreScript((int)a1);
    if (iVar1 != 0) {
      ((code *)FUN_10009700)(((unsigned)(uintptr_t)&DAT_1001e910));
      for (uVar2 = ImGetNextSound(0); uVar2 != 0; uVar2 = ImGetNextSound(uVar2)) {
        if ((int)uVar2 < 0x2711) {
          ImStopSound(uVar2);
        }
      }
      SoundsCloseVoiceFile();
      ((code *)FUN_10009700)(((unsigned)(uintptr_t)&DAT_1001e958));
      iVar1 = (*param_1)(&iStack_28,4);
      if ((iVar1 == 0) && (iStack_28 != 0)) {
        iVar1 = 0;
        if (0 < iStack_28) {
          do {
            iVar3 = (*param_1)(auStack_1c,0x20);
            if ((iVar3 != 0) || (iVar3 = (*param_1)(&param_2,4), iVar3 != 0)) goto LAB_1000883c;
            g_dwNextHandle = param_2 - 0x457;
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
      (**(code **)(g_dwSounds_pHS + 0x24))(a1);
      return 0;
    }
  }
  (**(code **)(g_dwSounds_pHS + 0x24))(a1);
  return 1;
}
#undef auStack_1c
#undef iStack_28
#undef puStack_20
#undef uStack_24
#undef uStack_4

#endif


/* ---- 0x10008860  sounds_pause ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Original name sounds_pause (the remaster's GrimFandango (Linux): aligned call in
   SoundsInitialize); was FUN_10008860. */

undefined4 sounds_pause(void)

{
  ImPause();
  _g_iMuseMasterVolHold = ImSetGroupVol(0,0xffffffff);
  ImSetGroupVol(0,0);
  ImSetAttribute(-1,0);
  return 0;
}

/* ---- 0x100088a0  sounds_resume ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Original name sounds_resume (the remaster's GrimFandango (Linux): aligned call in
   SoundsInitialize); was FUN_100088a0. */

undefined4 sounds_resume(void)

{
  ImSetGroupVol(0,_g_iMuseMasterVolHold);
  ImResume();
  ImSetAttribute(-1,1);
  return 0;
}

/* ---- 0x10008ec0  CacheGetSoundId ---- */
/* Name (or handle) -> sound slot id (100..131) of the 32-slot sound cache. A name that is not
   cached is LOADED here (a free slot, or Sounds_EvictOldestIdleSlot). A handle (0x457..0x556, the
   number Lua gets from ImStartSound; one per cached SOUND, not per playing instance, reused when
   the slot is) that is not in the cache gives 0. Returns 0 when it cannot load. Callers:
   SoundsGetParam returns 1 (!) for 0, so ImGetParam(name or stale handle, anything) reads 1, i.e.
   'playing', when the sound is not resolvable (sound_playing loops). Original name CacheGetSoundId
   (the remaster's GrimFandango (Linux): the only unmatched callee of SoundsFadeParam; the only
   unmatched callee of SoundsGetParam; the only unmatched callee of SoundsIsSoundInUse; the only
   unmatched callee of SoundsIsSoundPlaying; the only unmatched callee of SoundsLoadStartSound; the
   only unmatched callee of SoundsSetParam; the only unmatched callee of SoundsStopSound; the only
   unmatched callee of iMUSE_GetHook; the only unmatched callee of iMUSE_SetHook; 10 matched
   neighbours agree, 1 disagree); was Sounds_ResolveName_LoadIfNeeded. */

int __cdecl CacheGetSoundId(uint *param_1)

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
    if ((local_44 < 0) && (local_44 = CachePurgeOldestStoppedSound(), local_44 < 0)) {
      return 0;
    }
    puVar9 = (uint *)(&g_bSoundCache + local_44 * 0x40);
    Im_MemCopy(puVar9,param_1,0x20);
    *(undefined1 *)(local_44 * 0x40 + ((unsigned)(uintptr_t)&DAT_10031547)) = 0;
    do {
      bVar12 = false;
      uVar6 = (int)g_dwNextHandle >> 0x1f;
      iVar1 = 0;
      do {
        if ((g_bSoundCache != '\0') &&
           (DAT_10031548 == (((g_dwNextHandle ^ uVar6) - uVar6 & 0xff ^ uVar6) - uVar6) + 0x457)) {
          bVar12 = true;
          g_dwNextHandle = g_dwNextHandle + 1;
          break;
        }
        iVar1 = iVar1 + 1;
      } while (iVar1 < 0x20);
    } while (bVar12);
    uVar6 = (int)g_dwNextHandle >> 0x1f;
    (&DAT_10031548)[local_44 * 0x10] =
         (((g_dwNextHandle ^ uVar6) - uVar6 & 0xff ^ uVar6) - uVar6) + 0x457;
    g_dwNextHandle = g_dwNextHandle + 1;
  }
LAB_10009063:
  puVar9[0xe] = 0;
  piVar2 = iRes_FOPEN(puVar9,&DAT_1001e900);
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
    LoadLip(auStack_20,(char *)puVar9[8]);
  }
  iRes_FSEEK((undefined *)piVar2,0,2);
  uVar6 = iRes_FTELL((undefined *)piVar2);
  puVar9[0xd] = uVar6;
  iRes_FSEEK((undefined *)piVar2,0,0);
  uVar6 = (**(code **)(g_dwSounds_pHS + 0x20))
                    (puVar9[0xd] + 0x50,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0x774);
  puVar9[10] = uVar6;
  if (uVar6 != 0) {
    iRes_FREAD(piVar2,(undefined4 *)puVar9[10],puVar9[0xd]);
  }
  iRes_FCLOSE(piVar2);
  puVar4 = AudioLib_ParseWaveFileHeader
                     ((uint *)puVar9[10],&iStack_38,&uStack_24,&uStack_3c,&uStack_28,&iStack_34,
                      &uStack_40);
  if ((iStack_38 != 3) && (iStack_38 != 5)) {
    (**(code **)(g_dwSounds_pHS + 0x24))(puVar9[10]);
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
                 (**(code **)(g_dwSounds_pHS + 0x20))
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
    (**(code **)(g_dwSounds_pHS + 0x24))(puVar9[10]);
    uStack_40 = uStack_40 << 1;
    puVar9[10] = (uint)puStack_2c;
    iStack_34 = 1;
    uStack_3c = 0x10;
    iStack_38 = 0;
  }
  if (iStack_38 != 3) {
    AudioLib_CreateWaveFileHeader
              ((undefined4 *)(puVar9[10] + puVar9[0xd]),3,uStack_24,0x10,uStack_28,uStack_40);
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


/* ---- 0x100092f0  CachePurgeOldestStoppedSound ---- */
/* Frees the cache slot of the sound that was used longest ago (timeGetTime stamp at +0x24) among
   loaded slots with no playing track (param 0x100 == 0) and nothing pending (0x200 == 0). Returns
   the slot index, or -1 when every slot is in use. Original name CachePurgeOldestStoppedSound (the
   remaster's GrimFandango (Linux): aligned call in CacheGetSoundId, SoundsPeriodic); was
   Sounds_EvictOldestIdleSlot. */

int CachePurgeOldestStoppedSound(void)

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
    (&g_bSoundCache)[iVar4 * 0x40] = 0;
    Im_SoundsFreeSlot(iVar3);
    if (*(int *)(&DAT_10031550 + iVar4 * 0x40) != 0) {
      (**(code **)(g_dwSounds_pHS + 0x24))(*(int *)(&DAT_10031550 + iVar4 * 0x40));
    }
    puVar6 = (undefined4 *)(&g_bSoundCache + iVar4 * 0x40);
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
/* not in the source: names/lib_replace.json (host): the system C runtime (msvcrt.dll) has it */


/* ---- 0x1000b980  ImFile_ReadImpl ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1000ba20  FUN_1000ba20 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1000ba60  FUN_1000ba60 ---- */
/* not in the source: names/lib_replace.json (host): the system C runtime (msvcrt.dll) has it */


/* ---- 0x1000ba80  FUN_1000ba80 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1000baa0  FUN_1000baa0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1000bb10  ImFile_Close ---- */
/* not in the source: names/lib_replace.json (host): the system C runtime (msvcrt.dll) has it */


/* ---- 0x1000bb50  ImFile_CloseImpl ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1000bbc0  ImFile_Open ---- */
/* not in the source: names/lib_replace.json (host): the system C runtime (msvcrt.dll) has it */


/* ---- 0x1000bc00  ImFile_OpenImpl ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1000c4f0  ImFile_LockInit ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1000c570  ImFile_UnlockInner ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1000c590  ImFile_Lock ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1000c5d0  FUN_1000c5d0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1000c600  ImFile_Unlock ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1000c640  FUN_1000c640 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1000c670  FUN_1000c670 ---- */
/* replaced by the hand-written version in build/overrides*.c; the original C runtime code is not kept */


/* ---- 0x1000d000  FUN_1000d000 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1000d050  FUN_1000d050 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1000d090  FUN_1000d090 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1000d0d0  FUN_1000d0d0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1000d0f0  FUN_1000d0f0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1000d110  FUN_1000d110 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1000d130  FUN_1000d130 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x1000d1f0  FUN_1000d1f0 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */

