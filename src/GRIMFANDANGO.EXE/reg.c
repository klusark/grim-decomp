/* GRIMFANDANGO.EXE :: reg.c
 * functions 0x004038a0 .. 0x00404120 (15 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004038a0  Reg_Open ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* W32Util/wuregistry: creates/opens the game key; if its Version value differs from ours the key is
   deleted and recreated. Then caches all value names. */

void Reg_Open(void *param_1,uint param_2,char *param_3)

{
  unsigned char _frame[0xa0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  #define local_88 (*(int *)(_frame + (0xa0 - 0x88)))
  #define local_84 (*(undefined1 (*)[4])(_frame + (0xa0 - 0x84)))
  #define acStack_80 (*(char (*)[128])(_frame + (0xa0 - 0x80)))
  
  _DAT_004f5ea8 = 1;
  UINT_004f5eac = param_2;
  g_pRegRootKey = param_1;
  iVar1 = RegCreateKeyExA((int)param_1,param_2,0,((unsigned)(uintptr_t)&DAT_004f5a98),0,0xf003f,0,(int)&local_88,(int)local_84);
  if (iVar1 == 0) {
    iVar2 = wuRegistry_GetStr(s_Version_004dda60,acStack_80,0x80,(char *)0x0);
    if (iVar2 != 0) {
      iVar2 = _stricmp(acStack_80,param_3);
      if (iVar2 != 0) {
        RegDeleteKeyA((int)g_pRegRootKey,UINT_004f5eac);
        iVar1 = RegCreateKeyExA((int)g_pRegRootKey,UINT_004f5eac,0,((unsigned)(uintptr_t)&DAT_004f5a98),0,0xf003f,0,
                                (int)&local_88,(int)local_84);
      }
    }
  }
  if (iVar1 == 0) {
    wuRegistry_SaveStr(s_Version_004dda60,param_3);
    RegCloseKey(local_88);
  }
  Reg_CacheValueNames();
  return;
}
#undef acStack_80
#undef local_84
#undef local_88


/* ---- 0x004039a0  Reg_CacheValueNames ---- */
/* RegEnumValue into g_ppRegValueNames (lower-cased, qsorted) so Reg_HasValue can bsearch */

void Reg_CacheValueNames(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char *pcVar1;
  uint uVar2;
  char **ppcVar3;
  #define local_c (*(void **)(_frame + (0x20 - 0xc)))
  #define iStack_8 (*(int *)(_frame + (0x20 - 0x8)))
  #define iStack_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  RegOpenKeyExA(g_pRegRootKey,(char *)UINT_004f5eac,0,0xf003f,&local_c);
  RegQueryInfoKeyA((int)local_c,0,0,0,0,0,0,((unsigned)(uintptr_t)&g_dwRegValueCount),(int)&iStack_8,0,0,0);
  g_ppRegValueNames =
       (char **)(*g_pStd_HS->pAlloc)
                          (g_dwRegValueCount * 4,s_C__grimjedi_Libs_W32Util_Wuregis_004dda68,
                           DAT_004dda58 + 0x25);
  ppcVar3 = g_ppRegValueNames;
  for (uVar2 = g_dwRegValueCount; uVar2 != 0; uVar2 = uVar2 - 1) {
    *ppcVar3 = (char *)0x0;
    ppcVar3 = ppcVar3 + 1;
  }
  uVar2 = 0;
  if (g_dwRegValueCount != 0) {
    do {
      iStack_4 = iStack_8 + 1;
      pcVar1 = (char *)(*g_pStd_HS->pAlloc)
                                 (iStack_4,s_C__grimjedi_Libs_W32Util_Wuregis_004dda68,
                                  DAT_004dda58 + 0x31);
      g_ppRegValueNames[uVar2] = pcVar1;
      *g_ppRegValueNames[uVar2] = '\0';
      RegEnumValueA((int)local_c,uVar2,(int)g_ppRegValueNames[uVar2],(int)&iStack_4,0,0,0,0);
      Str_ToLower(g_ppRegValueNames[uVar2]);
      uVar2 = uVar2 + 1;
    } while (uVar2 < g_dwRegValueCount);
  }
  qsort(g_ppRegValueNames,g_dwRegValueCount,4,Str_ComparePtrs);
  RegCloseKey((int)local_c);
  return;
}
#undef iStack_4
#undef iStack_8
#undef local_c


/* ---- 0x00403b20  wuRegistry_Shutdown ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Original name wuRegistry_Shutdown (the remaster's GrimFandango (Linux): the registry shutdown
   after the cursor in Main_Shutdown in both builds (the remaster's is empty)); was Reg_Close. */

void wuRegistry_Shutdown(void)

{
  Reg_FreeValueNames();
  _DAT_004f5ea8 = 0;
  return;
}

/* ---- 0x00403b30  Reg_FreeValueNames ---- */
void Reg_FreeValueNames(void)

{
  uint uVar1;
  
  uVar1 = 0;
  if (g_dwRegValueCount != 0) {
    do {
      (*g_pStd_HS->pFree)(g_ppRegValueNames[uVar1]);
      uVar1 = uVar1 + 1;
    } while (uVar1 < g_dwRegValueCount);
  }
  (*g_pStd_HS->pFree)(g_ppRegValueNames);
  g_ppRegValueNames = (char **)0x0;
  return;
}

/* ---- 0x00403b80  Reg_SetInt ---- */
int __cdecl Reg_SetInt(char *name,int value)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_4 (*(void **)(_frame + (0x20 - 0x4)))
  
  iVar1 = RegOpenKeyExA(g_pRegRootKey,(char *)UINT_004f5eac,0,0xf003f,&local_4);
  if (iVar1 != 0) {
    return 0;
  }
  RegSetValueExA((int)local_4,(int)name,0,3,(int)&value,4);
  RegCloseKey((int)local_4);
  Reg_AddValueName(name);
  return 1;
}
#undef local_4


/* ---- 0x00403bf0  Reg_AddValueName ---- */
int __cdecl Reg_AddValueName(char *name)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  
  iVar2 = Reg_HasValue(name);
  if (iVar2 == 0) {
    g_dwRegValueCount = g_dwRegValueCount + 1;
    g_ppRegValueNames =
         (char **)(*g_pStd_HS->pRealloc)
                            (g_ppRegValueNames,g_dwRegValueCount * 4,
                             s_C__grimjedi_Libs_W32Util_Wuregis_004dda68,DAT_004dda5c + 7);
    uVar4 = 0xffffffff;
    pcVar3 = name;
    do {
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    pcVar3 = (char *)(*g_pStd_HS->pAlloc)
                               (~uVar4,s_C__grimjedi_Libs_W32Util_Wuregis_004dda68,DAT_004dda5c + 8)
    ;
    g_ppRegValueNames[g_dwRegValueCount - 1] = pcVar3;
    uVar4 = 0xffffffff;
    do {
      pcVar3 = name;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar3 = name + 1;
      cVar1 = *name;
      name = pcVar3;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    pcVar3 = pcVar3 + -uVar4;
    pcVar6 = g_ppRegValueNames[g_dwRegValueCount - 1];
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar6 = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      pcVar6 = pcVar6 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar6 = *pcVar3;
      pcVar3 = pcVar3 + 1;
      pcVar6 = pcVar6 + 1;
    }
    Str_ToLower(g_ppRegValueNames[g_dwRegValueCount - 1]);
    qsort(g_ppRegValueNames,g_dwRegValueCount,4,Str_ComparePtrs);
  }
  return iVar2;
}

/* ---- 0x00403cf0  Reg_HasValue ---- */
int __cdecl Reg_HasValue(char *name)

{
  unsigned char _frame[0xa0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int *piVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  #define local_84 (*(uint *)(_frame + (0xa0 - 0x84)))
  #define local_80 (*(char (*)[128])(_frame + (0xa0 - 0x80)))
  
  local_84 = (uint)local_80;
  if (g_ppRegValueNames == (char **)0x0) {
    return 1;
  }
  uVar3 = 0xffffffff;
  do {
    pcVar5 = name;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar5 = name + 1;
    cVar1 = *name;
    name = pcVar5;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar5 = pcVar5 + -uVar3;
  pcVar6 = local_80;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar6 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar6 = pcVar6 + 1;
  }
  Str_ToLower(local_80);
  piVar2 = (int *)bsearch(&local_84,g_ppRegValueNames,g_dwRegValueCount,4,Str_ComparePtrs);
  if (piVar2 != (int *)0x0) {
    return *piVar2;
  }
  return 0;
}
#undef local_80
#undef local_84


/* ---- 0x00403d90  wuRegistry_SaveFloat ---- */
/* Original name wuRegistry_SaveFloat (the remaster's GrimFandango (Linux): aligned call in
   sputLua_WriteRegistryValue); was Reg_SetFloat. */

int __cdecl wuRegistry_SaveFloat(char *name,float value)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_4 (*(void **)(_frame + (0x20 - 0x4)))
  
  iVar1 = RegOpenKeyExA(g_pRegRootKey,(char *)UINT_004f5eac,0,0xf003f,&local_4);
  if (iVar1 != 0) {
    return 0;
  }
  RegSetValueExA((int)local_4,(int)name,0,3,(int)&value,4);
  RegCloseKey((int)local_4);
  Reg_AddValueName(name);
  return 1;
}
#undef local_4


/* ---- 0x00403e00  Reg_GetInt ---- */
int __cdecl Reg_GetInt(char *name,int defaultValue)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char *a2;
  int iVar1;
  #define uStack_c (*(undefined4 *)(_frame + (0x20 - 0xc)))
  #define iStack_8 (*(int *)(_frame + (0x20 - 0x8)))
  #define auStack_4 (*(undefined1 (*)[4])(_frame + (0x20 - 0x4)))
  
  a2 = name;
  iVar1 = Reg_HasValue(name);
  if (iVar1 != 0) {
    iVar1 = RegOpenKeyExA(g_pRegRootKey,(char *)UINT_004f5eac,0,0xf003f,&name);
    if (iVar1 == 0) {
      uStack_c = 4;
      iVar1 = RegQueryValueExA((int)name,(int)a2,0,(int)auStack_4,(int)&iStack_8,(int)&uStack_c);
      if (iVar1 == 0) {
        RegCloseKey((int)name);
        return iStack_8;
      }
      RegCloseKey((int)name);
    }
  }
  return defaultValue;
}
#undef auStack_4
#undef iStack_8
#undef uStack_c


/* ---- 0x00403e90  wuRegistry_GetFloat ---- */
/* Original name wuRegistry_GetFloat (the remaster's GrimFandango (Linux): aligned call in
   sputLua_ReadRegistryValue); was Reg_GetFloat. */

float __cdecl wuRegistry_GetFloat(char *name,float defaultValue)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char *a2;
  int iVar1;
  #define uStack_c (*(undefined4 *)(_frame + (0x20 - 0xc)))
  #define fStack_8 (*(float *)(_frame + (0x20 - 0x8)))
  #define auStack_4 (*(undefined1 (*)[4])(_frame + (0x20 - 0x4)))
  
  a2 = name;
  iVar1 = Reg_HasValue(name);
  if (iVar1 != 0) {
    iVar1 = RegOpenKeyExA(g_pRegRootKey,(char *)UINT_004f5eac,0,0xf003f,&name);
    if (iVar1 == 0) {
      uStack_c = 4;
      iVar1 = RegQueryValueExA((int)name,(int)a2,0,(int)auStack_4,(int)&fStack_8,(int)&uStack_c);
      if (iVar1 == 0) {
        RegCloseKey((int)name);
        return fStack_8;
      }
      RegCloseKey((int)name);
    }
  }
  return defaultValue;
}
#undef auStack_4
#undef fStack_8
#undef uStack_c


/* ---- 0x00403f20  Reg_SetBinary ---- */
int __cdecl Reg_SetBinary(char *name,void *data,int size)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_4 (*(void **)(_frame + (0x20 - 0x4)))
  
  iVar1 = RegOpenKeyExA(g_pRegRootKey,(char *)UINT_004f5eac,0,0xf003f,&local_4);
  if (iVar1 == 0) {
    RegSetValueExA((int)local_4,(int)name,0,3,(int)data,size);
    RegCloseKey((int)local_4);
    Reg_AddValueName(name);
    return 1;
  }
  return 0;
}
#undef local_4


/* ---- 0x00403f90  Reg_GetBinary ---- */
int __cdecl Reg_GetBinary(char *name,void *data,int size)

{
  char *a2;
  int iVar1;
  
  a2 = name;
  iVar1 = Reg_HasValue(name);
  if (iVar1 != 0) {
    iVar1 = RegOpenKeyExA(g_pRegRootKey,(char *)UINT_004f5eac,0,0xf003f,&name);
    if (iVar1 == 0) {
      iVar1 = RegQueryValueExA((int)name,(int)a2,0,(int)&data,(int)data,(int)&size);
      if (iVar1 == 0) {
        RegCloseKey((int)name);
        return 1;
      }
      RegCloseKey((int)name);
    }
  }
  return 0;
}

/* ---- 0x00404010  wuRegistry_SaveStr ---- */
/* Original name wuRegistry_SaveStr (the remaster's GrimFandango (Linux): aligned call in
   sputLua_WriteRegistryValue); was Reg_SetString. */

void __cdecl wuRegistry_SaveStr(char *name,char *value)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  uint uVar2;
  char *pcVar3;
  #define local_4 (*(void **)(_frame + (0x20 - 0x4)))
  
  RegOpenKeyExA(g_pRegRootKey,(char *)UINT_004f5eac,0,0xf003f,&local_4);
  uVar2 = 0xffffffff;
  pcVar3 = value;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  RegSetValueExA((int)local_4,(int)name,0,1,(int)value,~uVar2 - 1);
  RegCloseKey((int)local_4);
  Reg_AddValueName(name);
  return;
}
#undef local_4


/* ---- 0x00404070  wuRegistry_GetStr ---- */
/* Original name wuRegistry_GetStr (the remaster's GrimFandango (Linux): aligned call in
   sputLua_ReadRegistryValue, sputLua_Startup, sputSmush_Startup); was Reg_GetString. */

int __cdecl wuRegistry_GetStr(char *name,char *buf,int size,char *defaultValue)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char *a2;
  char *pcVar1;
  int iVar2;
  int iVar3;
  #define iStack_8 (*(int *)(_frame + (0x20 - 0x8)))
  #define auStack_4 (*(undefined1 (*)[4])(_frame + (0x20 - 0x4)))
  
  a2 = name;
  iVar2 = Reg_HasValue(name);
  if (iVar2 == 0) {
    return 0;
  }
  RegOpenKeyExA(g_pRegRootKey,(char *)UINT_004f5eac,0,0xf003f,&name);
  iVar2 = size;
  pcVar1 = buf;
  iStack_8 = size;
  iVar3 = RegQueryValueExA((int)name,(int)a2,0,(int)auStack_4,(int)buf,(int)&iStack_8);
  if (iVar3 != 0) {
    if (defaultValue != (char *)0x0) {
      strncpy(pcVar1,defaultValue,iVar2 + -1);
      pcVar1[iVar2 + -1] = '\0';
    }
    RegCloseKey((int)name);
    return 0;
  }
  RegCloseKey((int)name);
  return 1;
}
#undef auStack_4
#undef iStack_8


/* ---- 0x00404120  wuRegistry_QueryType ---- */
/* Returns the registry value type (1 = REG_SZ, 3 = REG_BINARY) or 0 Original name
   wuRegistry_QueryType (the remaster's GrimFandango (Linux): aligned call in
   sputLua_ReadRegistryValue); was Reg_GetValueType. */

int __cdecl wuRegistry_QueryType(char *name)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_8 (*(void **)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0;
  RegOpenKeyExA(g_pRegRootKey,(char *)UINT_004f5eac,0,1,&local_8);
  RegQueryValueExA((int)local_8,(int)name,0,(int)&local_4,0,0);
  RegCloseKey((int)local_8);
  return local_4;
}
#undef local_4
#undef local_8

