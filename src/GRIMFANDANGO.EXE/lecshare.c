/* GRIMFANDANGO.EXE :: lecshare.c
 * functions 0x004c1390 .. 0x004c1e50 (14 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004c1390  LecShare_Startup ---- */
/* LecShare module registry (LEC shared module system used by INSANE/iMUSE): resets the table and
   runs each {init, arg} pair of the module list */

undefined **
LecShare_Startup(undefined *param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  code *pcVar2;
  
  if (param_1 != (undefined *)0x0) {
    PTR_LecShare_Nop_004f1220 = param_1;
  }
  LecShare_Reset(param_3,param_4);
  DAT_008d56e8 = 0;
  pcVar2 = (code *)*param_2;
  while (pcVar2 != (code *)0x0) {
    (*pcVar2)(&PTR_LecShare_Register_004f1200,param_2[1]);
    puVar1 = param_2 + 2;
    param_2 = param_2 + 2;
    pcVar2 = (code *)*puVar1;
  }
  DAT_008d56e8 = 1;
  return &PTR_LecShare_Register_004f1200;
}

/* ---- 0x004c13f0  LecShare_Shutdown ---- */
/* Calls the shutdown entry of every registered LECMODULE */

undefined4 LecShare_Shutdown(void)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  
  piVar3 = &DAT_008d56f0 + DAT_008d56f8 * 3;
  for (iVar4 = DAT_008d56f8; iVar4 != 0; iVar4 = iVar4 + -1) {
    if ((*piVar3 != 0) && (iVar1 = Str_ModuleNameLength(*piVar3), iVar1 == 9)) {
      uVar2 = Str_ModuleNameLength(*piVar3);
      iVar1 = Str_CompareNoCaseN(s_LECMODULE_004f1224,*piVar3,uVar2);
      if ((iVar1 == 0) && (*(code **)(piVar3[1] + 4) != (code *)0x0)) {
        (**(code **)(piVar3[1] + 4))();
      }
    }
    piVar3 = piVar3 + -3;
  }
  return 0;
}

/* ---- 0x004c1460  LecShare_StartupModules ---- */
/* Calls the startup entry of every registered LECMODULE; on failure unwinds and reports 'LecShare
   Startup: Failed with module' */

int LecShare_StartupModules(void)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  
  piVar4 = &DAT_008d56fc;
  PTR_008d56f4 = (int *)0x0;
  iVar5 = DAT_008d56f8;
  if (DAT_008d56f8 == 0) {
    PTR_008d56f4 = (int *)0x0;
    return 0;
  }
  do {
    iVar5 = iVar5 + -1;
    piVar1 = PTR_008d56f4;
    if ((*piVar4 != 0) && (iVar2 = Str_ModuleNameLength(*piVar4), piVar1 = PTR_008d56f4, iVar2 == 9)
       ) {
      uVar3 = Str_ModuleNameLength(*piVar4);
      iVar2 = Str_CompareNoCaseN(s_LECMODULE_004f1224,*piVar4,uVar3);
      piVar1 = PTR_008d56f4;
      if ((iVar2 == 0) &&
         ((piVar1 = piVar4, *(code **)(piVar4[1] + 8) != (code *)0x0 &&
          (iVar2 = (**(code **)(piVar4[1] + 8))(), iVar2 != 0)))) {
        if (PTR_LecShare_Nop_004f1220 != (undefined *)0x0) {
          (*(code *)PTR_LecShare_Nop_004f1220)(s_LecShare_Startup__Failed_with_mo_004f1230,*piVar4);
        }
        LecShare_UnwindStartup();
        return iVar2;
      }
    }
    PTR_008d56f4 = piVar1;
    piVar4 = piVar4 + 3;
    if (iVar5 == 0) {
      return 0;
    }
  } while( true );
}

/* ---- 0x004c1500  LecShare_UnwindStartup ---- */
undefined4 LecShare_UnwindStartup(void)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  
  if (PTR_008d56f4 == (int *)0x0) {
    return 1;
  }
  piVar1 = PTR_008d56f4 + 3;
  piVar4 = PTR_008d56f4;
  for (iVar5 = (int)((int *)((char *)PTR_008d56f4 - IMG_ADDR(0x008d56f0))) / 0xc; PTR_008d56f4 = piVar1, iVar5 != 0;
      iVar5 = iVar5 + -1) {
    if ((*piVar4 != 0) && (iVar2 = Str_ModuleNameLength(*piVar4), iVar2 == 9)) {
      uVar3 = Str_ModuleNameLength(*piVar4);
      iVar2 = Str_CompareNoCaseN(s_LECMODULE_004f1224,*piVar4,uVar3);
      if ((iVar2 == 0) && (*(code **)(piVar4[1] + 0xc) != (code *)0x0)) {
        (**(code **)(piVar4[1] + 0xc))();
      }
    }
    piVar4 = piVar4 + -3;
    piVar1 = PTR_008d56f4;
  }
  return 0;
}

/* ---- 0x004c1590  LecShare_Reset ---- */
/* Zeroes the 0x605-dword registry and stores the application name and version */

void LecShare_Reset(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_008d56e8;
  for (iVar1 = 0x605; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  DAT_008d56ec = param_1;
  DAT_008d56f0 = param_2;
  return;
}

/* ---- 0x004c15c0  LecShare_Register ---- */
/* Entries are 3 dwords: name, vtable, reference count */

int __cdecl LecShare_Register(char *name,void *vtable)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  uint uVar5;
  
  uVar5 = DAT_008d56f8;
  Str_StripNonPrintable(name);
  uVar3 = DAT_008d56f8;
  piVar4 = &DAT_008d56f0 + uVar5 * 3;
  while (uVar5 != 0) {
    uVar5 = uVar5 - 1;
    if (*piVar4 == 0) {
      *piVar4 = (int)name;
      piVar4[1] = (int)vtable;
      piVar4[2] = 0;
      return 0;
    }
    piVar4 = piVar4 + -3;
  }
  if (DAT_008d56f8 < 0x200) {
    iVar1 = DAT_008d56f8 * 0xc;
    iVar2 = DAT_008d56f8 * 3;
    DAT_008d56f8 = DAT_008d56f8 + 1;
    (&DAT_008d56fc)[iVar2] = name;
    (&DAT_008d5700)[uVar3 * 3] = vtable;
    *(undefined4 *)(&DAT_008d5704 + iVar1) = 0;
    return 0;
  }
  return 1;
}

/* ---- 0x004c1650  LecShare_Unregister ---- */
int LecShare_Unregister(undefined4 param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = DAT_008d56f8;
  Str_StripNonPrintable(param_1);
  piVar2 = &DAT_008d56f0 + iVar3 * 3;
  if (iVar3 == 0) {
    return 1;
  }
  do {
    iVar3 = iVar3 + -1;
    if (*piVar2 != 0) {
      iVar1 = Str_CompareNoCase(*piVar2,param_1);
      if (iVar1 == 0) {
        iVar3 = piVar2[2];
        *piVar2 = 0;
        piVar2[1] = 0;
        piVar2[2] = 0;
        return iVar3;
      }
    }
    piVar2 = piVar2 + -3;
  } while (iVar3 != 0);
  return 1;
}

/* ---- 0x004c16c0  LecShare_Resolve ---- */
/* Looks a module up by name (wildcards allowed), honouring the application's override list */

undefined4 LecShare_Resolve(char *param_1,char *param_2)

{
  unsigned char _frame[0x80] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  byte bVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  byte *pbVar7;
  char *pcVar8;
  char *pcVar9;
  char *pcVar10;
  byte *pbVar11;
  #define local_64 (*(char (*)[100])(_frame + (0x80 - 0x64)))
  
  pbVar7 = (byte *)0x0;
  if (DAT_008d56e8 != 0) {
    if (DAT_008d56f0 != (char *)0x0) {
      pbVar7 = Str_WildcardMatch(param_1,DAT_008d56f0);
    }
    if (pbVar7 == (byte *)0x0) {
      if (param_2 != (char *)0x0) {
        pbVar7 = Str_WildcardMatch(param_1,param_2);
      }
      if ((pbVar7 == (byte *)0x0) && (DAT_008d56ec != (char *)0x0)) {
        pbVar7 = Str_WildcardMatch(param_1,DAT_008d56ec);
      }
    }
    iVar3 = Str_ModuleNameLength(param_1);
    strncpy(local_64,param_1,iVar3);
    local_64[iVar3] = '\0';
    if (pbVar7 == (byte *)0x0) {
      iVar3 = LecShare_CountMatching(local_64);
      if (iVar3 == 0) {
        return 0;
      }
      uVar4 = ((code *)LecShare_Subscribe)(local_64,iVar3 + -1,99);
      ((code *)strncpy)(local_64,uVar4);
    }
    else {
      uVar5 = 0xffffffff;
      pcVar8 = "=";
      do {
        pcVar10 = pcVar8;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar10 = pcVar8 + 1;
        cVar1 = *pcVar8;
        pcVar8 = pcVar10;
      } while (cVar1 != '\0');
      uVar5 = ~uVar5;
      iVar3 = -1;
      pcVar8 = local_64;
      do {
        pcVar9 = pcVar8;
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        pcVar9 = pcVar8 + 1;
        cVar1 = *pcVar8;
        pcVar8 = pcVar9;
      } while (cVar1 != '\0');
      pcVar8 = pcVar10 + -uVar5;
      pcVar10 = pcVar9 + -1;
      for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar10 = *(undefined4 *)pcVar8;
        pcVar8 = pcVar8 + 4;
        pcVar10 = pcVar10 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar10 = *pcVar8;
        pcVar8 = pcVar8 + 1;
        pcVar10 = pcVar10 + 1;
      }
      uVar5 = 0xffffffff;
      do {
        pbVar11 = pbVar7;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pbVar11 = pbVar7 + 1;
        bVar2 = *pbVar7;
        pbVar7 = pbVar11;
      } while (bVar2 != 0);
      uVar5 = ~uVar5;
      iVar3 = -1;
      pcVar8 = local_64;
      do {
        pcVar10 = pcVar8;
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        pcVar10 = pcVar8 + 1;
        cVar1 = *pcVar8;
        pcVar8 = pcVar10;
      } while (cVar1 != '\0');
      pbVar7 = pbVar11 + -uVar5;
      pbVar11 = (byte *)(pcVar10 + -1);
      for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pbVar11 = *(undefined4 *)pbVar7;
        pbVar7 = pbVar7 + 4;
        pbVar11 = pbVar11 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pbVar11 = *pbVar7;
        pbVar7 = pbVar7 + 1;
        pbVar11 = pbVar11 + 1;
      }
    }
    iVar3 = LecShare_FindEntry(local_64);
    if (iVar3 != 0) {
      *(int *)(iVar3 + 8) = *(int *)(iVar3 + 8) + 1;
      return *(undefined4 *)(iVar3 + 4);
    }
  }
  return 0;
}
#undef local_64


/* ---- 0x004c1800  LecShare_Release ---- */
/* Drops one reference from the entry owning the given vtable */

undefined4 LecShare_Release(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = &DAT_008d56f0 + DAT_008d56f8 * 3;
  iVar2 = DAT_008d56f8;
  if (DAT_008d56f8 == 0) {
    return 1;
  }
  do {
    iVar2 = iVar2 + -1;
    if (param_1 == puVar1[1]) {
      puVar1[2] = puVar1[2] + -1;
      return 0;
    }
    puVar1 = puVar1 + -3;
  } while (iVar2 != 0);
  return 1;
}

/* ---- 0x004c1850  LecShare_BatchSubscribe ---- */
/* Resolves a null-terminated list of {out, name} subscriptions */

undefined4 LecShare_BatchSubscribe(int *param_1,char *param_2)

{
  int *piVar1;
  char *pcVar2;
  undefined4 uVar3;
  
  if (*param_1 == 0) {
    return 0;
  }
  while( true ) {
    pcVar2 = (char *)param_1[2];
    if ((pcVar2 == (char *)0x0) || (*pcVar2 == '\0')) {
      *(undefined4 *)*param_1 = 0;
    }
    else {
      uVar3 = LecShare_Resolve(param_1[1],pcVar2);
      *(undefined4 *)*param_1 = uVar3;
    }
    if (((*(int *)*param_1 == 0) && (param_2 != (char *)0x0)) && (*param_2 != '\0')) {
      uVar3 = LecShare_Resolve(param_1[1],param_2);
      *(undefined4 *)*param_1 = uVar3;
    }
    if (*(int *)*param_1 == 0) {
      uVar3 = LecShare_Resolve(param_1[1],0);
      *(undefined4 *)*param_1 = uVar3;
    }
    if (*(int *)*param_1 == 0) break;
    piVar1 = param_1 + 3;
    param_1 = param_1 + 3;
    if (*piVar1 == 0) {
      return 0;
    }
  }
  if (PTR_LecShare_Nop_004f1220 != (undefined *)0x0) {
    (*(code *)PTR_LecShare_Nop_004f1220)(s_LecShare_BatchSubscribe_Couldn_t_004f125c,param_1[1]);
  }
  return 1;
}

/* ---- 0x004c1990  LecShare_Subscribe ---- */
int LecShare_Subscribe(char *param_1,int param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  char *pcVar9;
  bool bVar10;
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  iVar6 = DAT_008d56f8;
  iVar8 = 1;
  local_4 = 1;
  if (DAT_008d56f8 == 0) {
    return 0;
  }
  if (param_2 < 0) {
    return 0;
  }
  if (DAT_008d6f00 == (int *)0x0) {
LAB_004c1a7f:
    piVar7 = &DAT_008d56fc;
    iVar2 = param_2;
  }
  else {
    if (param_1 == (char *)0x0) {
      if (DAT_008d3680 != '\0') goto LAB_004c1a7f;
    }
    else {
      iVar2 = Str_CompareNoCase(param_1,&DAT_008d3680);
      if (iVar2 != 0) goto LAB_004c1a7f;
    }
    if (param_2 == DAT_008d6efc) {
      return *DAT_008d6f00;
    }
    if (param_2 < DAT_008d6efc) {
      local_4 = -1;
      iVar8 = -1;
      iVar6 = (int)((int *)((char *)DAT_008d6f00 - IMG_ADDR(0x008d56fc))) / 0xc;
      piVar7 = DAT_008d6f00 + -3;
      iVar2 = (DAT_008d6efc - param_2) + -1;
    }
    else {
      iVar6 = iVar6 + (-1 - (int)((int *)((char *)DAT_008d6f00 - IMG_ADDR(0x008d56fc))) / 0xc);
      piVar7 = DAT_008d6f00 + 3;
      iVar2 = param_2 + (-1 - DAT_008d6efc);
    }
  }
  DAT_008d6efc = param_2;
  if (param_1 == (char *)0x0) {
    DAT_008d3680 = '\0';
  }
  else {
    strncpy(&DAT_008d3680,param_1,99);
    DAT_008d36e3 = 0;
  }
  if (iVar6 == 0) {
    DAT_008d6f00 = (int *)0x0;
    return 0;
  }
  do {
    iVar6 = iVar6 + -1;
    if (*piVar7 != 0) {
      if (param_1 == (char *)0x0) {
LAB_004c1b0c:
        bVar10 = iVar2 == 0;
        iVar2 = iVar2 + -1;
        if (bVar10) {
          DAT_008d6f00 = piVar7;
          return *piVar7;
        }
      }
      else {
        iVar3 = Str_ModuleNameLength(*piVar7);
        uVar5 = 0xffffffff;
        pcVar9 = param_1;
        do {
          if (uVar5 == 0) break;
          uVar5 = uVar5 - 1;
          cVar1 = *pcVar9;
          pcVar9 = pcVar9 + 1;
        } while (cVar1 != '\0');
        iVar8 = local_4;
        if (~uVar5 - 1 == iVar3) {
          uVar4 = Str_ModuleNameLength(*piVar7);
          iVar3 = Str_CompareNoCaseN(param_1,*piVar7,uVar4);
          if (iVar3 == 0) goto LAB_004c1b0c;
        }
      }
    }
    piVar7 = piVar7 + iVar8 * 3;
    if (iVar6 == 0) {
      DAT_008d6f00 = (int *)iVar6;
      return 0;
    }
  } while( true );
}
#undef local_4


/* ---- 0x004c1b60  LecShare_CountMatching ---- */
int LecShare_CountMatching(char *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  int *piVar6;
  char *pcVar7;
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0;
  piVar6 = &DAT_008d56f0 + DAT_008d56f8 * 3;
  iVar5 = DAT_008d56f8;
  do {
    if (iVar5 == 0) {
      return local_4;
    }
    if (*piVar6 != 0) {
      if (param_1 == (char *)0x0) {
LAB_004c1bc7:
        local_4 = local_4 + 1;
      }
      else {
        iVar2 = Str_ModuleNameLength(*piVar6);
        uVar4 = 0xffffffff;
        pcVar7 = param_1;
        do {
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          cVar1 = *pcVar7;
          pcVar7 = pcVar7 + 1;
        } while (cVar1 != '\0');
        if (~uVar4 - 1 == iVar2) {
          uVar3 = Str_ModuleNameLength(*piVar6);
          iVar2 = Str_CompareNoCaseN(param_1,*piVar6,uVar3);
          if (iVar2 == 0) goto LAB_004c1bc7;
        }
      }
    }
    piVar6 = piVar6 + -3;
    iVar5 = iVar5 + -1;
  } while( true );
}
#undef local_4


/* ---- 0x004c1be0  LecShare_FindEntry ---- */
undefined4 * LecShare_FindEntry(undefined4 param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  
  puVar2 = &DAT_008d56f0 + DAT_008d56f8 * 3;
  iVar3 = DAT_008d56f8;
  if (DAT_008d56f8 == 0) {
    return (undefined4 *)0x0;
  }
  do {
    iVar3 = iVar3 + -1;
    iVar1 = Str_CompareNoCase(*puVar2,param_1);
    if (iVar1 == 0) {
      return puVar2;
    }
    puVar2 = puVar2 + -3;
  } while (iVar3 != 0);
  return (undefined4 *)0x0;
}

/* ---- 0x004c1e50  LecShare_Nop ---- */
undefined4 LecShare_Nop(void)

{
  return 0;
}
