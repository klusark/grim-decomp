/* GRIMFANDANGO.EXE :: lecshare.c
 * functions 0x004c1390 .. 0x004c1e50 (14 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004c1390  LecShare_Initialize ---- */
/* LecShare module registry (LEC shared module system used by INSANE/iMUSE): resets the table and
   runs each {init, arg} pair of the module list Original name LecShare_Initialize (the remaster's
   GrimFandango (Linux): the LecShare set-up SmushPlay_SysInitialize calls with (0, module list,
   "FILIO=insane_zfilio", ...)); was LecShare_Startup. */

undefined ** __cdecl
LecShare_Initialize(undefined *param_1,undefined4 *param_2,uint param_3,uint param_4)

{
  undefined4 *puVar1;
  code *pcVar2;
  
  if (param_1 != (undefined *)0x0) {
    PTR_LecShare_Nop_004f1220 = param_1;
  }
  LecShare_Reset(param_3,param_4);
  g_dwPrivateData = 0;
  pcVar2 = (code *)*param_2;
  while (pcVar2 != (code *)0x0) {
    (*pcVar2)(&g_pLecShareServices,param_2[1]);
    puVar1 = param_2 + 2;
    param_2 = param_2 + 2;
    pcVar2 = (code *)*puVar1;
  }
  g_dwPrivateData = 1;
  return &g_pLecShareServices;
}

/* ---- 0x004c13f0  LecShare_Terminate ---- */
/* Calls the shutdown entry of every registered LECMODULE Original name LecShare_Terminate (the
   remaster's GrimFandango (Linux): calls the terminate slot (+4) of every LECMODULE backwards, from
   SmushPlay_SysTerminate); was LecShare_Shutdown. */

uint __cdecl LecShare_Terminate(void)

{
  int iVar1;
  uint *puVar2;
  uint uVar3;
  
  puVar2 = &UINT_008d56f0 + UINT_008d56f8 * 3;
  for (uVar3 = UINT_008d56f8; uVar3 != 0; uVar3 = uVar3 - 1) {
    if (((byte *)*puVar2 != (byte *)0x0) &&
       (iVar1 = Str_ModuleNameLength((byte *)*puVar2), iVar1 == 9)) {
      iVar1 = Str_ModuleNameLength((byte *)*puVar2);
      iVar1 = Str_CompareNoCaseN(s_LECMODULE_004f1224,(char *)*puVar2,iVar1);
      if ((iVar1 == 0) && (*(code **)(puVar2[1] + 4) != (code *)0x0)) {
        (**(code **)(puVar2[1] + 4))();
      }
    }
    puVar2 = puVar2 + -3;
  }
  return 0;
}

/* ---- 0x004c1460  LecShare_Startup ---- */
/* Calls the startup entry of every registered LECMODULE; on failure unwinds and reports 'LecShare
   Startup: Failed with module' Original name LecShare_Startup (the remaster's GrimFandango (Linux):
   calls the startup slot (+8) of every LECMODULE in order, from SmushPlay_SysStartup); was
   LecShare_StartupModules. */

int __cdecl LecShare_Startup(void)

{
  uint *puVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  
  puVar3 = &UINT_008d56fc;
  PTR_008d56f4 = (int *)0x0;
  uVar4 = UINT_008d56f8;
  if (UINT_008d56f8 == 0) {
    PTR_008d56f4 = (int *)0x0;
    return 0;
  }
  do {
    uVar4 = uVar4 - 1;
    puVar1 = (uint *)PTR_008d56f4;
    if (((byte *)*puVar3 != (byte *)0x0) &&
       (iVar2 = Str_ModuleNameLength((byte *)*puVar3), puVar1 = (uint *)PTR_008d56f4, iVar2 == 9)) {
      iVar2 = Str_ModuleNameLength((byte *)*puVar3);
      iVar2 = Str_CompareNoCaseN(s_LECMODULE_004f1224,(char *)*puVar3,iVar2);
      puVar1 = (uint *)PTR_008d56f4;
      if ((iVar2 == 0) &&
         ((puVar1 = puVar3, *(code **)(puVar3[1] + 8) != (code *)0x0 &&
          (iVar2 = (**(code **)(puVar3[1] + 8))(), puVar1 = puVar3, iVar2 != 0)))) {
        if (PTR_LecShare_Nop_004f1220 != (undefined *)0x0) {
          (*(code *)PTR_LecShare_Nop_004f1220)(s_LecShare_Startup__Failed_with_mo_004f1230,*puVar3);
        }
        LecShare_Shutdown();
        return iVar2;
      }
    }
    PTR_008d56f4 = (int *)puVar1;
    puVar3 = puVar3 + 3;
    if (uVar4 == 0) {
      return 0;
    }
  } while( true );
}

/* ---- 0x004c1500  LecShare_Shutdown ---- */
/* Original name LecShare_Shutdown (the remaster's GrimFandango (Linux): calls the shutdown slot
   (+0xc) of the started LECMODULEs backwards, from SmushPlay_SysShutdown); was
   LecShare_UnwindStartup. */

uint __cdecl LecShare_Shutdown(void)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  if (PTR_008d56f4 == (int *)0x0) {
    return 1;
  }
  piVar1 = PTR_008d56f4 + 3;
  piVar3 = PTR_008d56f4;
  for (iVar4 = (int)((int *)((char *)PTR_008d56f4 - ((unsigned)(uintptr_t)&UINT_008d56f0))) / 0xc; PTR_008d56f4 = piVar1, iVar4 != 0;
      iVar4 = iVar4 + -1) {
    if (((byte *)*piVar3 != (byte *)0x0) &&
       (iVar2 = Str_ModuleNameLength((byte *)*piVar3), iVar2 == 9)) {
      iVar2 = Str_ModuleNameLength((byte *)*piVar3);
      iVar2 = Str_CompareNoCaseN(s_LECMODULE_004f1224,(char *)*piVar3,iVar2);
      if ((iVar2 == 0) && (*(code **)(piVar3[1] + 0xc) != (code *)0x0)) {
        (**(code **)(piVar3[1] + 0xc))();
      }
    }
    piVar3 = piVar3 + -3;
    piVar1 = PTR_008d56f4;
  }
  return 0;
}

/* ---- 0x004c1590  LecShare_Reset ---- */
/* Zeroes the 0x605-dword registry and stores the application name and version */

void __cdecl LecShare_Reset(uint param_1,uint param_2)

{
  int iVar1;
  uint *puVar2;
  
  puVar2 = &g_dwPrivateData;
  for (iVar1 = 0x605; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  UINT_008d56ec = param_1;
  UINT_008d56f0 = param_2;
  return;
}

/* ---- 0x004c15c0  LecShare_Publish ---- */
/* Entries are 3 dwords: name, vtable, reference count Original name LecShare_Publish (the
   remaster's GrimFandango (Linux): slot 0 of lecShareServices (g_pLecShareServices); the original
   is Publish (the bridge takes no bare one-word name; as LecShare_Subscribe)); was
   LecShare_Register. */

int __cdecl LecShare_Publish(char *name,void *vtable)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint *puVar4;
  uint uVar5;
  
  uVar5 = UINT_008d56f8;
  Str_StripNonPrintable((byte *)name);
  uVar3 = UINT_008d56f8;
  puVar4 = &UINT_008d56f0 + uVar5 * 3;
  while (uVar5 != 0) {
    uVar5 = uVar5 - 1;
    if (*puVar4 == 0) {
      *puVar4 = (uint)name;
      puVar4[1] = (uint)vtable;
      puVar4[2] = 0;
      return 0;
    }
    puVar4 = puVar4 + -3;
  }
  if (UINT_008d56f8 < 0x200) {
    iVar1 = UINT_008d56f8 * 0xc;
    iVar2 = UINT_008d56f8 * 3;
    UINT_008d56f8 = UINT_008d56f8 + 1;
    (&UINT_008d56fc)[iVar2] = (uint)name;
    (&UINT_008d5700)[uVar3 * 3] = (uint)vtable;
    *(undefined4 *)(&DAT_008d5704 + iVar1) = 0;
    return 0;
  }
  return 1;
}

/* ---- 0x004c1650  LecShare_Unpublish ---- */
/* Original name LecShare_Unpublish (the remaster's GrimFandango (Linux): slot 1 of lecShareServices
   (g_pLecShareServices); the original is Unpublish (the bridge takes no bare one-word name; as
   LecShare_Subscribe)); was LecShare_Unregister. */

uint __cdecl LecShare_Unpublish(uint param_1)

{
  int iVar1;
  uint *puVar2;
  uint uVar3;
  
  uVar3 = UINT_008d56f8;
  Str_StripNonPrintable((byte *)param_1);
  puVar2 = &UINT_008d56f0 + uVar3 * 3;
  if (uVar3 == 0) {
    return 1;
  }
  do {
    uVar3 = uVar3 - 1;
    if ((char *)*puVar2 != (char *)0x0) {
      iVar1 = Str_CompareNoCase((char *)*puVar2,(char *)param_1);
      if (iVar1 == 0) {
        uVar3 = puVar2[2];
        *puVar2 = 0;
        puVar2[1] = 0;
        puVar2[2] = 0;
        return uVar3;
      }
    }
    puVar2 = puVar2 + -3;
  } while (uVar3 != 0);
  return 1;
}

/* ---- 0x004c16c0  LecShare_Subscribe ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Looks a module up by name (wildcards allowed), honouring the application's override list Original
   name Subscribe, written LecShare_Subscribe because the bridge refuses one-token names (the
   remaster's GrimFandango (Linux): aligned call in BatchSubscribe); was LecShare_Resolve. */

void * __cdecl LecShare_Subscribe(char *name,char *pattern)

{
  unsigned char _frame[0x80] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  byte bVar2;
  uint uVar3;
  uint *puVar4;
  int iVar5;
  byte *pbVar6;
  char *pcVar7;
  char *pcVar8;
  uint *puVar9;
  byte *pbVar10;
  uint uVar11;
  #define local_64 (*(uint (*)[25])(_frame + (0x80 - 0x64)))
  
  pbVar6 = (byte *)0x0;
  if (g_dwPrivateData != 0) {
    if (UINT_008d56f0 != 0) {
      pbVar6 = FindMatch(name,(char *)UINT_008d56f0);
    }
    if (pbVar6 == (byte *)0x0) {
      if (pattern != (char *)0x0) {
        pbVar6 = FindMatch(name,pattern);
      }
      if ((pbVar6 == (byte *)0x0) && (UINT_008d56ec != 0)) {
        pbVar6 = FindMatch(name,(char *)UINT_008d56ec);
      }
    }
    uVar3 = Str_ModuleNameLength((byte *)name);
    strncpy(local_64,(uint *)name,uVar3);
    *(undefined1 *)((int)local_64 + uVar3) = 0;
    if (pbVar6 == (byte *)0x0) {
      uVar3 = GetCatalogCount((char *)local_64);
      if (uVar3 == 0) {
        return (void *)0x0;
      }
      uVar11 = 99;
      puVar4 = (uint *)GetCatalogEntry((char *)local_64,uVar3 - 1);
      strncpy(local_64,puVar4,uVar11);
    }
    else {
      uVar3 = 0xffffffff;
      pcVar7 = "=";
      do {
        pcVar8 = pcVar7;
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        pcVar8 = pcVar7 + 1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar8;
      } while (cVar1 != '\0');
      uVar3 = ~uVar3;
      iVar5 = -1;
      puVar4 = local_64;
      do {
        puVar9 = puVar4;
        if (iVar5 == 0) break;
        iVar5 = iVar5 + -1;
        puVar9 = (uint *)((int)puVar4 + 1);
        uVar11 = *puVar4;
        puVar4 = puVar9;
      } while ((char)uVar11 != '\0');
      pcVar7 = pcVar8 + -uVar3;
      pcVar8 = (char *)((int)puVar9 + -1);
      for (uVar11 = uVar3 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
        *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
        pcVar7 = pcVar7 + 4;
        pcVar8 = pcVar8 + 4;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar8 = *pcVar7;
        pcVar7 = pcVar7 + 1;
        pcVar8 = pcVar8 + 1;
      }
      uVar3 = 0xffffffff;
      do {
        pbVar10 = pbVar6;
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        pbVar10 = pbVar6 + 1;
        bVar2 = *pbVar6;
        pbVar6 = pbVar10;
      } while (bVar2 != 0);
      uVar3 = ~uVar3;
      iVar5 = -1;
      puVar4 = local_64;
      do {
        puVar9 = puVar4;
        if (iVar5 == 0) break;
        iVar5 = iVar5 + -1;
        puVar9 = (uint *)((int)puVar4 + 1);
        uVar11 = *puVar4;
        puVar4 = puVar9;
      } while ((char)uVar11 != '\0');
      pbVar6 = pbVar10 + -uVar3;
      pbVar10 = (byte *)((int)puVar9 + -1);
      for (uVar11 = uVar3 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
        *(undefined4 *)pbVar10 = *(undefined4 *)pbVar6;
        pbVar6 = pbVar6 + 4;
        pbVar10 = pbVar10 + 4;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pbVar10 = *pbVar6;
        pbVar6 = pbVar6 + 1;
        pbVar10 = pbVar10 + 1;
      }
    }
    puVar4 = LecShare_FindEntry((uint)local_64);
    if (puVar4 != (uint *)0x0) {
      puVar4[2] = puVar4[2] + 1;
      return (void *)puVar4[1];
    }
  }
  return (void *)0x0;
}
#undef local_64

#endif


/* ---- 0x004c1800  LecShare_Unsubscribe ---- */
/* Drops one reference from the entry owning the given vtable Original name LecShare_Unsubscribe
   (the remaster's GrimFandango (Linux): slot 3 of lecShareServices (g_pLecShareServices); the
   original is Unsubscribe (the bridge takes no bare one-word name; as LecShare_Subscribe)); was
   LecShare_Release. */

uint __cdecl LecShare_Unsubscribe(uint param_1)

{
  uint *puVar1;
  uint uVar2;
  
  puVar1 = &UINT_008d56f0 + UINT_008d56f8 * 3;
  uVar2 = UINT_008d56f8;
  if (UINT_008d56f8 == 0) {
    return 1;
  }
  do {
    uVar2 = uVar2 - 1;
    if (param_1 == puVar1[1]) {
      puVar1[2] = puVar1[2] - 1;
      return 0;
    }
    puVar1 = puVar1 + -3;
  } while (uVar2 != 0);
  return 1;
}

/* ---- 0x004c1850  BatchSubscribe ---- */
/* Resolves a null-terminated list of {out, name} subscriptions Original name BatchSubscribe (the
   remaster's GrimFandango (Linux): strings: "LecShare:BatchSubscribe Couldn't subscribe to %s
   interface.); was LecShare_BatchSubscribe. */

uint __cdecl BatchSubscribe(int *param_1,char *param_2)

{
  int *piVar1;
  char *pattern;
  void *pvVar2;
  
  if (*param_1 == 0) {
    return 0;
  }
  while( true ) {
    pattern = (char *)param_1[2];
    if ((pattern == (char *)0x0) || (*pattern == '\0')) {
      *(undefined4 *)*param_1 = 0;
    }
    else {
      pvVar2 = LecShare_Subscribe((char *)param_1[1],pattern);
      *(void **)*param_1 = pvVar2;
    }
    if (((*(int *)*param_1 == 0) && (param_2 != (char *)0x0)) && (*param_2 != '\0')) {
      pvVar2 = LecShare_Subscribe((char *)param_1[1],param_2);
      *(void **)*param_1 = pvVar2;
    }
    if (*(int *)*param_1 == 0) {
      pvVar2 = LecShare_Subscribe((char *)param_1[1],(char *)0x0);
      *(void **)*param_1 = pvVar2;
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

/* ---- 0x004c1990  GetCatalogEntry ---- */
/* Original name GetCatalogEntry (the remaster's GrimFandango (Linux): aligned call in Subscribe);
   was LecShare_Subscribe. */

uint __cdecl GetCatalogEntry(char *param_1,uint param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  uint uVar7;
  char *pcVar8;
  bool bVar9;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar4 = UINT_008d56f8;
  uVar7 = 1;
  local_4 = 1;
  if (UINT_008d56f8 == 0) {
    return 0;
  }
  if ((int)param_2 < 0) {
    return 0;
  }
  if (UINT_008d6f00 == 0) {
LAB_004c1a7f:
    puVar6 = &UINT_008d56fc;
    uVar5 = param_2;
  }
  else {
    if (param_1 == (char *)0x0) {
      if (g_bGetCatalogEntry_pLastType != '\0') goto LAB_004c1a7f;
    }
    else {
      iVar2 = Str_CompareNoCase(param_1,&g_bGetCatalogEntry_pLastType);
      if (iVar2 != 0) goto LAB_004c1a7f;
    }
    if (param_2 == UINT_008d6efc) {
      return *(uint *)UINT_008d6f00;
    }
    if ((int)param_2 < (int)UINT_008d6efc) {
      local_4 = 0xffffffff;
      uVar7 = 0xffffffff;
      uVar4 = (int)(UINT_008d6f00 - 0x8d56fc) / 0xc;
      puVar6 = (uint *)(UINT_008d6f00 - 0xc);
      uVar5 = (UINT_008d6efc - param_2) - 1;
    }
    else {
      uVar4 = uVar4 + (-1 - (int)(UINT_008d6f00 - 0x8d56fc) / 0xc);
      puVar6 = (uint *)(UINT_008d6f00 + 0xc);
      uVar5 = param_2 + (-1 - UINT_008d6efc);
    }
  }
  UINT_008d6efc = param_2;
  if (param_1 == (char *)0x0) {
    g_bGetCatalogEntry_pLastType = '\0';
  }
  else {
    strncpy((uint *)&g_bGetCatalogEntry_pLastType,(uint *)param_1,99);
    DAT_008d36e3 = 0;
  }
  if (uVar4 == 0) {
    UINT_008d6f00 = 0;
    return 0;
  }
  do {
    uVar4 = uVar4 - 1;
    if ((byte *)*puVar6 != (byte *)0x0) {
      if (param_1 == (char *)0x0) {
LAB_004c1b0c:
        bVar9 = uVar5 == 0;
        uVar5 = uVar5 - 1;
        if (bVar9) {
          UINT_008d6f00 = (uint)puVar6;
          return *puVar6;
        }
      }
      else {
        iVar2 = Str_ModuleNameLength((byte *)*puVar6);
        uVar3 = 0xffffffff;
        pcVar8 = param_1;
        do {
          if (uVar3 == 0) break;
          uVar3 = uVar3 - 1;
          cVar1 = *pcVar8;
          pcVar8 = pcVar8 + 1;
        } while (cVar1 != '\0');
        uVar7 = local_4;
        if (~uVar3 - 1 == iVar2) {
          iVar2 = Str_ModuleNameLength((byte *)*puVar6);
          iVar2 = Str_CompareNoCaseN(param_1,(char *)*puVar6,iVar2);
          if (iVar2 == 0) goto LAB_004c1b0c;
        }
      }
    }
    puVar6 = puVar6 + uVar7 * 3;
    if (uVar4 == 0) {
      UINT_008d6f00 = uVar4;
      return 0;
    }
  } while( true );
}
#undef local_4


/* ---- 0x004c1b60  GetCatalogCount ---- */
/* Original name GetCatalogCount (the remaster's GrimFandango (Linux): aligned call in Subscribe);
   was LecShare_CountMatching. */

uint __cdecl GetCatalogCount(char *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  char *pcVar6;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0;
  puVar5 = &UINT_008d56f0 + UINT_008d56f8 * 3;
  uVar4 = UINT_008d56f8;
  do {
    if (uVar4 == 0) {
      return local_4;
    }
    if ((byte *)*puVar5 != (byte *)0x0) {
      if (param_1 == (char *)0x0) {
LAB_004c1bc7:
        local_4 = local_4 + 1;
      }
      else {
        iVar2 = Str_ModuleNameLength((byte *)*puVar5);
        uVar3 = 0xffffffff;
        pcVar6 = param_1;
        do {
          if (uVar3 == 0) break;
          uVar3 = uVar3 - 1;
          cVar1 = *pcVar6;
          pcVar6 = pcVar6 + 1;
        } while (cVar1 != '\0');
        if (~uVar3 - 1 == iVar2) {
          iVar2 = Str_ModuleNameLength((byte *)*puVar5);
          iVar2 = Str_CompareNoCaseN(param_1,(char *)*puVar5,iVar2);
          if (iVar2 == 0) goto LAB_004c1bc7;
        }
      }
    }
    puVar5 = puVar5 + -3;
    uVar4 = uVar4 - 1;
  } while( true );
}
#undef local_4


/* ---- 0x004c1be0  LecShare_FindEntry ---- */
uint * __cdecl LecShare_FindEntry(uint param_1)

{
  int iVar1;
  uint *puVar2;
  uint uVar3;
  
  puVar2 = &UINT_008d56f0 + UINT_008d56f8 * 3;
  uVar3 = UINT_008d56f8;
  if (UINT_008d56f8 == 0) {
    return (uint *)0x0;
  }
  do {
    uVar3 = uVar3 - 1;
    iVar1 = Str_CompareNoCase((char *)*puVar2,(char *)param_1);
    if (iVar1 == 0) {
      return puVar2;
    }
    puVar2 = puVar2 + -3;
  } while (uVar3 != 0);
  return (uint *)0x0;
}

/* ---- 0x004c1e50  LecShare_Nop ---- */
uint __cdecl LecShare_Nop(void)

{
  return 0;
}
