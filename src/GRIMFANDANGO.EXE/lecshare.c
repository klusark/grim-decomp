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
LecShare_Initialize(undefined *nop,undefined4 *registry,uint version,uint flags)

{
  undefined4 *puVar1;
  code *pcVar2;
  
  if (nop != (undefined *)0x0) {
    PTR_LecShare_Nop_004f1220 = nop;
  }
  LecShare_Reset(version,flags);
  g_dwPrivateData = 0;
  pcVar2 = (code *)*registry;
  while (pcVar2 != (code *)0x0) {
    (*pcVar2)(&g_pLecShareServices,registry[1]);
    puVar1 = registry + 2;
    registry = registry + 2;
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
  
  puVar2 = g_adwLecShare_catalog + g_adwLecShare_catalog[2] * 3;
  for (uVar3 = g_adwLecShare_catalog[2]; uVar3 != 0; uVar3 = uVar3 - 1) {
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
  
  puVar3 = g_adwLecShare_catalog;
  g_adwLecShare_catalog[1] = 0;
  uVar4 = g_adwLecShare_catalog[2];
  if (g_adwLecShare_catalog[2] == 0) {
    g_adwLecShare_catalog[1] = 0;
    return 0;
  }
  do {
    puVar3 = puVar3 + 3;
    uVar4 = uVar4 - 1;
    puVar1 = (uint *)g_adwLecShare_catalog[1];
    if (((byte *)*puVar3 != (byte *)0x0) &&
       (iVar2 = Str_ModuleNameLength((byte *)*puVar3), puVar1 = (uint *)g_adwLecShare_catalog[1],
       iVar2 == 9)) {
      iVar2 = Str_ModuleNameLength((byte *)*puVar3);
      iVar2 = Str_CompareNoCaseN(s_LECMODULE_004f1224,(char *)*puVar3,iVar2);
      puVar1 = (uint *)g_adwLecShare_catalog[1];
      if ((iVar2 == 0) &&
         ((puVar1 = puVar3, *(code **)(puVar3[1] + 8) != (code *)0x0 &&
          (iVar2 = (**(code **)(puVar3[1] + 8))(), iVar2 != 0)))) {
        if (PTR_LecShare_Nop_004f1220 != (undefined *)0x0) {
          (*(code *)PTR_LecShare_Nop_004f1220)(s_LecShare_Startup__Failed_with_mo_004f1230,*puVar3);
        }
        LecShare_Shutdown();
        return iVar2;
      }
    }
    g_adwLecShare_catalog[1] = (uint)puVar1;
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
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  
  if (g_adwLecShare_catalog[1] == 0) {
    return 1;
  }
  uVar1 = g_adwLecShare_catalog[1] + 0xc;
  puVar3 = (undefined4 *)g_adwLecShare_catalog[1];
  for (iVar4 = (int)(g_adwLecShare_catalog[1] - 0x8d56f0) / 0xc; g_adwLecShare_catalog[1] = uVar1,
      iVar4 != 0; iVar4 = iVar4 + -1) {
    if (((byte *)*puVar3 != (byte *)0x0) &&
       (iVar2 = Str_ModuleNameLength((byte *)*puVar3), iVar2 == 9)) {
      iVar2 = Str_ModuleNameLength((byte *)*puVar3);
      iVar2 = Str_CompareNoCaseN(s_LECMODULE_004f1224,(char *)*puVar3,iVar2);
      if ((iVar2 == 0) && (*(code **)(puVar3[1] + 0xc) != (code *)0x0)) {
        (**(code **)(puVar3[1] + 0xc))();
      }
    }
    puVar3 = puVar3 + -3;
    uVar1 = g_adwLecShare_catalog[1];
  }
  return 0;
}

/* ---- 0x004c1590  LecShare_Reset ---- */
/* Zeroes the 0x605-dword registry and stores the application name and version */

void __cdecl LecShare_Reset(uint version,uint flags)

{
  int iVar1;
  uint *puVar2;
  
  puVar2 = &g_dwPrivateData;
  for (iVar1 = 0x605; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  UINT_008d56ec = version;
  g_adwLecShare_catalog[0] = flags;
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
  uint uVar2;
  uint *puVar3;
  uint uVar4;
  
  uVar4 = g_adwLecShare_catalog[2];
  Str_StripNonPrintable((byte *)name);
  uVar2 = g_adwLecShare_catalog[2];
  puVar3 = g_adwLecShare_catalog + uVar4 * 3;
  while (uVar4 != 0) {
    uVar4 = uVar4 - 1;
    if (*puVar3 == 0) {
      *puVar3 = (uint)name;
      puVar3[1] = (uint)vtable;
      puVar3[2] = 0;
      return 0;
    }
    puVar3 = puVar3 + -3;
  }
  if (g_adwLecShare_catalog[2] < 0x200) {
    iVar1 = g_adwLecShare_catalog[2] * 3;
    g_adwLecShare_catalog[2] = g_adwLecShare_catalog[2] + 1;
    g_adwLecShare_catalog[iVar1 + 3] = (uint)name;
    g_adwLecShare_catalog[uVar2 * 3 + 4] = (uint)vtable;
    g_adwLecShare_catalog[uVar2 * 3 + 5] = 0;
    return 0;
  }
  return 1;
}

/* ---- 0x004c1650  LecShare_Unpublish ---- */
/* Original name LecShare_Unpublish (the remaster's GrimFandango (Linux): slot 1 of lecShareServices
   (g_pLecShareServices); the original is Unpublish (the bridge takes no bare one-word name; as
   LecShare_Subscribe)); was LecShare_Unregister. */

uint __cdecl LecShare_Unpublish(uint name)

{
  int iVar1;
  uint *puVar2;
  uint uVar3;
  
  uVar3 = g_adwLecShare_catalog[2];
  Str_StripNonPrintable((byte *)name);
  puVar2 = g_adwLecShare_catalog + uVar3 * 3;
  if (uVar3 == 0) {
    return 1;
  }
  do {
    uVar3 = uVar3 - 1;
    if ((char *)*puVar2 != (char *)0x0) {
      iVar1 = Str_CompareNoCase((char *)*puVar2,(char *)name);
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
    if (g_adwLecShare_catalog[0] != 0) {
      pbVar6 = FindMatch(name,(char *)g_adwLecShare_catalog[0]);
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

uint __cdecl LecShare_Unsubscribe(uint handle)

{
  uint *puVar1;
  uint uVar2;
  
  puVar1 = g_adwLecShare_catalog + g_adwLecShare_catalog[2] * 3;
  uVar2 = g_adwLecShare_catalog[2];
  if (g_adwLecShare_catalog[2] == 0) {
    return 1;
  }
  do {
    uVar2 = uVar2 - 1;
    if (handle == puVar1[1]) {
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

uint __cdecl BatchSubscribe(int *batch,char *name)

{
  int *piVar1;
  char *pattern;
  void *pvVar2;
  
  if (*batch == 0) {
    return 0;
  }
  while( true ) {
    pattern = (char *)batch[2];
    if ((pattern == (char *)0x0) || (*pattern == '\0')) {
      *(undefined4 *)*batch = 0;
    }
    else {
      pvVar2 = LecShare_Subscribe((char *)batch[1],pattern);
      *(void **)*batch = pvVar2;
    }
    if (((*(int *)*batch == 0) && (name != (char *)0x0)) && (*name != '\0')) {
      pvVar2 = LecShare_Subscribe((char *)batch[1],name);
      *(void **)*batch = pvVar2;
    }
    if (*(int *)*batch == 0) {
      pvVar2 = LecShare_Subscribe((char *)batch[1],(char *)0x0);
      *(void **)*batch = pvVar2;
    }
    if (*(int *)*batch == 0) break;
    piVar1 = batch + 3;
    batch = batch + 3;
    if (*piVar1 == 0) {
      return 0;
    }
  }
  if (PTR_LecShare_Nop_004f1220 != (undefined *)0x0) {
    (*(code *)PTR_LecShare_Nop_004f1220)(s_LecShare_BatchSubscribe_Couldn_t_004f125c,batch[1]);
  }
  return 1;
}

/* ---- 0x004c1990  GetCatalogEntry ---- */
/* Original name GetCatalogEntry (the remaster's GrimFandango (Linux): aligned call in Subscribe);
   was LecShare_Subscribe. */

uint __cdecl GetCatalogEntry(char *type,uint index)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  uint uVar7;
  char *pcVar8;
  bool bVar9;
  uint local_4;
  
  uVar4 = g_adwLecShare_catalog[2];
  uVar7 = 1;
  local_4 = 1;
  if (g_adwLecShare_catalog[2] == 0) {
    return 0;
  }
  if ((int)index < 0) {
    return 0;
  }
  if (UINT_008d6f00 == 0) {
LAB_004c1a7f:
    puVar6 = g_adwLecShare_catalog + 3;
    uVar5 = index;
  }
  else {
    if (type == (char *)0x0) {
      if (g_bGetCatalogEntry_pLastType != '\0') goto LAB_004c1a7f;
    }
    else {
      iVar2 = Str_CompareNoCase(type,&g_bGetCatalogEntry_pLastType);
      if (iVar2 != 0) goto LAB_004c1a7f;
    }
    if (index == UINT_008d6efc) {
      return *(uint *)UINT_008d6f00;
    }
    if ((int)index < (int)UINT_008d6efc) {
      local_4 = 0xffffffff;
      uVar7 = 0xffffffff;
      uVar4 = (int)(UINT_008d6f00 - 0x8d56fc) / 0xc;
      puVar6 = (uint *)(UINT_008d6f00 - 0xc);
      uVar5 = (UINT_008d6efc - index) - 1;
    }
    else {
      uVar4 = uVar4 + (-1 - (int)(UINT_008d6f00 - 0x8d56fc) / 0xc);
      puVar6 = (uint *)(UINT_008d6f00 + 0xc);
      uVar5 = index + (-1 - UINT_008d6efc);
    }
  }
  UINT_008d6efc = index;
  if (type == (char *)0x0) {
    g_bGetCatalogEntry_pLastType = '\0';
  }
  else {
    strncpy((uint *)&g_bGetCatalogEntry_pLastType,(uint *)type,99);
    DAT_008d36e3 = 0;
  }
  if (uVar4 == 0) {
    UINT_008d6f00 = 0;
    return 0;
  }
  do {
    uVar4 = uVar4 - 1;
    if ((byte *)*puVar6 != (byte *)0x0) {
      if (type == (char *)0x0) {
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
        pcVar8 = type;
        do {
          if (uVar3 == 0) break;
          uVar3 = uVar3 - 1;
          cVar1 = *pcVar8;
          pcVar8 = pcVar8 + 1;
        } while (cVar1 != '\0');
        uVar7 = local_4;
        if (~uVar3 - 1 == iVar2) {
          iVar2 = Str_ModuleNameLength((byte *)*puVar6);
          iVar2 = Str_CompareNoCaseN(type,(char *)*puVar6,iVar2);
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

/* ---- 0x004c1b60  GetCatalogCount ---- */
/* Original name GetCatalogCount (the remaster's GrimFandango (Linux): aligned call in Subscribe);
   was LecShare_CountMatching. */

uint __cdecl GetCatalogCount(char *type)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  char *pcVar6;
  uint local_4;
  
  local_4 = 0;
  puVar5 = g_adwLecShare_catalog + g_adwLecShare_catalog[2] * 3;
  uVar4 = g_adwLecShare_catalog[2];
  do {
    if (uVar4 == 0) {
      return local_4;
    }
    if ((byte *)*puVar5 != (byte *)0x0) {
      if (type == (char *)0x0) {
LAB_004c1bc7:
        local_4 = local_4 + 1;
      }
      else {
        iVar2 = Str_ModuleNameLength((byte *)*puVar5);
        uVar3 = 0xffffffff;
        pcVar6 = type;
        do {
          if (uVar3 == 0) break;
          uVar3 = uVar3 - 1;
          cVar1 = *pcVar6;
          pcVar6 = pcVar6 + 1;
        } while (cVar1 != '\0');
        if (~uVar3 - 1 == iVar2) {
          iVar2 = Str_ModuleNameLength((byte *)*puVar5);
          iVar2 = Str_CompareNoCaseN(type,(char *)*puVar5,iVar2);
          if (iVar2 == 0) goto LAB_004c1bc7;
        }
      }
    }
    puVar5 = puVar5 + -3;
    uVar4 = uVar4 - 1;
  } while( true );
}

/* ---- 0x004c1be0  LecShare_FindEntry ---- */
uint * __cdecl LecShare_FindEntry(uint name)

{
  int iVar1;
  uint *puVar2;
  uint uVar3;
  
  puVar2 = g_adwLecShare_catalog + g_adwLecShare_catalog[2] * 3;
  uVar3 = g_adwLecShare_catalog[2];
  if (g_adwLecShare_catalog[2] == 0) {
    return (uint *)0x0;
  }
  do {
    uVar3 = uVar3 - 1;
    iVar1 = Str_CompareNoCase((char *)*puVar2,(char *)name);
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


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern char f_BatchSubscribe[] __asm__("_BatchSubscribe");
extern char f_BatchUnsubscribe[] __asm__("_BatchUnsubscribe");
extern char f_GetCatalogCount[] __asm__("_GetCatalogCount");
extern char f_GetCatalogEntry[] __asm__("_GetCatalogEntry");
extern char f_LecShare_Publish[] __asm__("_LecShare_Publish");
extern char f_LecShare_Subscribe[] __asm__("_LecShare_Subscribe");
extern char f_LecShare_Unpublish[] __asm__("_LecShare_Unpublish");
extern char f_LecShare_Unsubscribe[] __asm__("_LecShare_Unsubscribe");
extern unsigned char grim_def_DAT_008d36e3[5] __asm__("_DAT_008d36e3");
extern unsigned int grim_def_UINT_008d56ec __asm__("_UINT_008d56ec");
extern unsigned int grim_def_UINT_008d6efc __asm__("_UINT_008d6efc");
extern unsigned int grim_def_UINT_008d6f00 __asm__("_UINT_008d6f00");
extern unsigned int grim_def_g_adwLecShare_catalog[1539] __asm__("_g_adwLecShare_catalog");
extern unsigned char grim_def_g_bGetCatalogEntry_pLastType[99] __asm__("_g_bGetCatalogEntry_pLastType");
extern unsigned int grim_def_g_dwPrivateData __asm__("_g_dwPrivateData");
extern void *grim_def_g_pLecShareServices[8] __asm__("_g_pLecShareServices");
extern char grim_def_s_LECMODULE_004f1224[12] __asm__("_s_LECMODULE_004f1224");
extern char grim_def_s_LecShare_BatchSubscribe_Couldn_t_004f125c[60] __asm__("_s_LecShare_BatchSubscribe_Couldn_t_004f125c");
extern char grim_def_s_LecShare_Startup__Failed_with_mo_004f1230[44] __asm__("_s_LecShare_Startup__Failed_with_mo_004f1230");
static unsigned char grim_anchor_004f1200[0] __attribute__((section(".data$grim_004f1200"), aligned(16), used));
static unsigned char grim_pad_004f1200[0] __attribute__((section(".data$grim_004f1200_"), aligned(4), used));
/* 0x004f1200, 32 bytes */ GRIM_DATA("004f1200z") void *grim_def_g_pLecShareServices[8] __asm__("_g_pLecShareServices") = {
    (void *)f_LecShare_Publish, (void *)f_LecShare_Unpublish, (void *)f_LecShare_Subscribe, (void *)f_LecShare_Unsubscribe,
    (void *)f_BatchSubscribe, (void *)f_BatchUnsubscribe, (void *)f_GetCatalogEntry, (void *)f_GetCatalogCount
};
/* 0x004f1224, 12 bytes */ /* loose */ char grim_def_s_LECMODULE_004f1224[12] __asm__("_s_LECMODULE_004f1224") = "LECMODULE";
/* 0x004f1230, 44 bytes */ /* loose */ char grim_def_s_LecShare_Startup__Failed_with_mo_004f1230[44] __asm__("_s_LecShare_Startup__Failed_with_mo_004f1230") = "LecShare_Startup: Failed with module %s.";
/* 0x004f125c, 60 bytes */ /* loose */ char grim_def_s_LecShare_BatchSubscribe_Couldn_t_004f125c[60] __asm__("_s_LecShare_BatchSubscribe_Couldn_t_004f125c") = "LecShare:BatchSubscribe Couldn't subscribe to %s interface.";
/* 0x008d3680, 99 bytes */ GRIM_DATA("008d3680") unsigned char grim_def_g_bGetCatalogEntry_pLastType[99] __asm__("_g_bGetCatalogEntry_pLastType") = {0};
/* 0x008d36e3, 5 bytes */ GRIM_DATA("008d3680") unsigned char grim_def_DAT_008d36e3[5] __asm__("_DAT_008d36e3") = {0};
/* 0x008d56e8, 4 bytes */ GRIM_DATA("008d56e8") unsigned int grim_def_g_dwPrivateData __asm__("_g_dwPrivateData") = 0x0;
/* 0x008d56ec, 4 bytes */ GRIM_DATA("008d56ec") unsigned int grim_def_UINT_008d56ec __asm__("_UINT_008d56ec") = 0x0;
/* 0x008d56f0, 6156 bytes */ GRIM_DATA("008d56f0") unsigned int grim_def_g_adwLecShare_catalog[1539] __asm__("_g_adwLecShare_catalog") = {0};
/* 0x008d6efc, 4 bytes */ GRIM_DATA("008d6efc") unsigned int grim_def_UINT_008d6efc __asm__("_UINT_008d6efc") = 0x0;
/* 0x008d6f00, 4 bytes */ GRIM_DATA("008d6f00") unsigned int grim_def_UINT_008d6f00 __asm__("_UINT_008d6f00") = 0x0;
