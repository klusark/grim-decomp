/* GRIMFANDANGO.EXE :: string.c
 * functions 0x00403ae0 .. 0x004c1ee0 (14 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00403ae0  Str_ComparePtrs ---- */
/* qsort/bsearch comparator for arrays of char *: compares the strings the two entries point to. */

int __cdecl Str_ComparePtrs(undefined4 *param_1,undefined4 *param_2)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  bool bVar4;
  
  pbVar3 = (byte *)*param_2;
  pbVar2 = (byte *)*param_1;
  while( true ) {
    bVar1 = *pbVar2;
    bVar4 = bVar1 < *pbVar3;
    if (bVar1 != *pbVar3) break;
    if (bVar1 == 0) {
      return 0;
    }
    bVar1 = pbVar2[1];
    bVar4 = bVar1 < pbVar3[1];
    if (bVar1 != pbVar3[1]) break;
    pbVar2 = pbVar2 + 2;
    pbVar3 = pbVar3 + 2;
    if (bVar1 == 0) {
      return 0;
    }
  }
  return (1 - (uint)bVar4) - (uint)(bVar4 != 0);
}

/* ---- 0x004735b0  stdFileFromPath ---- */
/* Original name stdFileFromPath (the remaster's GrimFandango (Linux): aligned call in
   rdColormap_LoadEntry, rdMaterial_LoadEntry, rdModel3_LoadEntryText); was Str_FileNameFromPath. */

char * __cdecl stdFileFromPath(char *path)

{
  char *pcVar1;
  
  pcVar1 = strrchr(path,'\\');
  if (pcVar1 != (char *)0x0) {
    return pcVar1 + 1;
  }
  return path;
}

/* ---- 0x0047b5c0  Str_ToLower ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
char * __cdecl Str_ToLower(char *s)

{
  char cVar1;
  undefined4 in_EAX;
  char *pcVar2;
  int iVar3;
  
  cVar1 = *s;
  pcVar2 = (char *)CONCAT31((int3)((uint)in_EAX >> 8),cVar1);
  while (cVar1 != '\0') {
    iVar3 = tolower((int)(char)pcVar2);
    *s = (char)iVar3;
    cVar1 = s[1];
    pcVar2 = (char *)CONCAT31((int3)((uint)iVar3 >> 8),cVar1);
    s = s + 1;
  }
  return pcVar2;
}
#endif


/* ---- 0x0047fd20  stdFnames_FindMedName ---- */
/* Original name stdFnames_FindMedName (the remaster's GrimFandango (Linux): aligned call in
   BitmapRequester, ColormapRequester, MaterialRequester); was Str_Basename. */

char * __cdecl stdFnames_FindMedName(char *path)

{
  char *pcVar1;
  char cVar2;
  char *pcVar3;
  
  pcVar3 = strrchr(path,'\\');
  if (pcVar3 != (char *)0x0) {
    cVar2 = *pcVar3;
    while (cVar2 == '\\') {
      pcVar1 = pcVar3 + 1;
      pcVar3 = pcVar3 + 1;
      cVar2 = *pcVar1;
    }
    return pcVar3;
  }
  return path;
}

/* ---- 0x0047fd50  stdFnames_FindExt ---- */
/* Original name stdFnames_FindExt (the remaster's GrimFandango (Linux): aligned call in
   stdWriteImage); was Str_FileExtension. */

char * __cdecl stdFnames_FindExt(char *path)

{
  char *pcVar1;
  char *pcVar2;
  char *pcVar3;
  
  pcVar1 = stdFnames_FindMedName(path);
  pcVar1 = strrchr(pcVar1,'.');
  if (pcVar1 != (char *)0x0) {
    pcVar2 = strrchr(pcVar1 + 1,'.');
    while (pcVar2 != (char *)0x0) {
      pcVar3 = strrchr(pcVar2 + 1,'.');
      pcVar1 = pcVar2;
      pcVar2 = pcVar3;
    }
    return pcVar1 + 1;
  }
  return (char *)0x0;
}

/* ---- 0x0047fda0  Str_StripExtension ---- */
void __cdecl Str_StripExtension(char *param_1)

{
  char *pcVar1;
  
  pcVar1 = stdFnames_FindExt(param_1);
  if (pcVar1 != (char *)0x0) {
    pcVar1[-1] = '\0';
  }
  return;
}

/* ---- 0x0047fdc0  stdFnames_CopyShortName ---- */
/* Original name stdFnames_CopyShortName (the remaster's GrimFandango (Linux): the short-name call
   of sputCostume_SaveHook (dst, 0x20, path), same body); was Str_CopyBasenameNoExt. */

void __cdecl stdFnames_CopyShortName(char *dst,int size,char *path)

{
  uint *puVar1;
  
  puVar1 = (uint *)stdFnames_FindMedName(path);
  strncpy((uint *)dst,puVar1,size - 1);
  dst[size + -1] = '\0';
  Str_StripExtension(dst);
  return;
}

/* ---- 0x004838c0  Str_FindChar ---- */
undefined * __cdecl Str_FindChar(char *param_1,int param_2)

{
  char *pcVar1;
  char cVar2;
  
  cVar2 = *param_1;
  while ((cVar2 != '\0' && (cVar2 != param_2))) {
    pcVar1 = param_1 + 1;
    param_1 = param_1 + 1;
    cVar2 = *pcVar1;
  }
  return param_1;
}

/* ---- 0x004aef70  String_ContainsSubstring ---- */
uint * __cdecl String_ContainsSubstring(uint *param_1,char *param_2)

{
  char *pcVar1;
  char *pcVar2;
  char cVar3;
  uint *puVar4;
  uint uVar5;
  char cVar6;
  uint uVar7;
  uint uVar8;
  char *pcVar9;
  uint *puVar10;
  
  cVar3 = *param_2;
  if (cVar3 == '\0') {
    return param_1;
  }
  if (param_2[1] == '\0') {
    while (((uint)param_1 & 3) != 0) {
      uVar5 = *param_1;
      if ((char)uVar5 == cVar3) {
        return param_1;
      }
      param_1 = (uint *)((int)param_1 + 1);
      if ((char)uVar5 == '\0') {
        return (uint *)0x0;
      }
    }
    while( true ) {
      while( true ) {
        uVar5 = *param_1;
        uVar8 = uVar5 ^ CONCAT22(CONCAT11(cVar3,cVar3),CONCAT11(cVar3,cVar3));
        uVar7 = uVar5 ^ 0xffffffff ^ uVar5 + 0x7efefeff;
        puVar10 = param_1 + 1;
        if (((uVar8 ^ 0xffffffff ^ uVar8 + 0x7efefeff) & 0x81010100) != 0) break;
        param_1 = puVar10;
        if ((uVar7 & 0x81010100) != 0) {
          if ((uVar7 & 0x1010100) != 0) {
            return (uint *)0x0;
          }
          if ((uVar5 + 0x7efefeff & 0x80000000) == 0) {
            return (uint *)0x0;
          }
        }
      }
      uVar5 = *param_1;
      if ((char)uVar5 == cVar3) {
        return param_1;
      }
      if ((char)uVar5 == '\0') {
        return (uint *)0x0;
      }
      cVar6 = (char)(uVar5 >> 8);
      if (cVar6 == cVar3) {
        return (uint *)((int)param_1 + 1);
      }
      if (cVar6 == '\0') {
        return (uint *)0x0;
      }
      cVar6 = (char)(uVar5 >> 0x10);
      if (cVar6 == cVar3) {
        return (uint *)((int)param_1 + 2);
      }
      if (cVar6 == '\0') break;
      cVar6 = (char)(uVar5 >> 0x18);
      if (cVar6 == cVar3) {
        return (uint *)((int)param_1 + 3);
      }
      param_1 = puVar10;
      if (cVar6 == '\0') {
        return (uint *)0x0;
      }
    }
    return (uint *)0x0;
  }
  do {
    cVar6 = (char)*param_1;
    do {
      while (puVar10 = param_1, param_1 = (uint *)((int)puVar10 + 1), cVar6 != cVar3) {
        if (cVar6 == '\0') {
          return (uint *)0x0;
        }
        cVar6 = *(char *)param_1;
      }
      cVar6 = *(char *)param_1;
      pcVar9 = param_2;
      puVar4 = puVar10;
    } while (cVar6 != param_2[1]);
    do {
      if (pcVar9[2] == '\0') {
        return puVar10;
      }
      if (*(char *)((int)puVar4 + 2) != pcVar9[2]) break;
      pcVar1 = pcVar9 + 3;
      if (*pcVar1 == '\0') {
        return puVar10;
      }
      pcVar2 = (char *)((int)puVar4 + 3);
      pcVar9 = pcVar9 + 2;
      puVar4 = (uint *)((int)puVar4 + 2);
    } while (*pcVar1 == *pcVar2);
  } while( true );
}

/* ---- 0x004c1c30  FindMatch ---- */
/* Original name FindMatch (the remaster's GrimFandango (Linux): aligned call in Subscribe); was
   Str_WildcardMatch. */

byte * __cdecl FindMatch(char *str,char *pattern)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  byte bVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  byte bVar6;
  uint uVar7;
  int iVar8;
  byte *pbVar9;
  byte *pbVar10;
  char *pcVar11;
  byte *pbVar12;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar7 = 0xffffffff;
  bVar4 = false;
  pcVar11 = pattern;
  do {
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    cVar1 = *pcVar11;
    pcVar11 = pcVar11 + 1;
  } while (cVar1 != '\0');
  local_4 = 0;
  if (~uVar7 - 1 < 0x1fff) {
    uVar7 = 0xffffffff;
    pcVar11 = pattern;
    do {
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      cVar1 = *pcVar11;
      pcVar11 = pcVar11 + 1;
    } while (cVar1 != '\0');
    uVar7 = ~uVar7 - 1;
  }
  else {
    uVar7 = 0x1fff;
  }
  strncpy((uint *)&g_bFindMatch_stringBuffer,(uint *)pattern,uVar7);
  uVar7 = 0xffffffff;
  pcVar11 = pattern;
  do {
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    cVar1 = *pcVar11;
    pcVar11 = pcVar11 + 1;
  } while (cVar1 != '\0');
  if (~uVar7 - 1 < 0x1fff) {
    uVar7 = 0xffffffff;
    do {
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      cVar1 = *pattern;
      pattern = pattern + 1;
    } while (cVar1 != '\0');
    iVar8 = ~uVar7 - 1;
  }
  else {
    iVar8 = 0x1fff;
  }
  (&g_bFindMatch_stringBuffer)[iVar8] = 0;
  pbVar9 = &g_bFindMatch_stringBuffer;
  bVar6 = g_bFindMatch_stringBuffer;
  do {
    if (bVar6 == 0) {
      return (byte *)local_4;
    }
    bVar6 = *pbVar9;
    while ((bVar6 != 0 &&
           ((((bVar6 < 0x21 || (0x7f < bVar6)) || (bVar6 == 0x2c)) || (bVar6 == 0x3b))))) {
      pbVar12 = pbVar9 + 1;
      pbVar9 = pbVar9 + 1;
      bVar6 = *pbVar12;
    }
    bVar6 = *pbVar9;
    pbVar12 = (byte *)str;
    while (bVar6 != 0) {
      if (*pbVar12 == 0) goto LAB_004c1d16;
      iVar8 = toupper((uint)*pbVar12);
      iVar5 = toupper((uint)bVar6);
      if (iVar8 != iVar5) break;
      pbVar10 = pbVar9 + 1;
      pbVar9 = pbVar9 + 1;
      pbVar12 = pbVar12 + 1;
      bVar6 = *pbVar10;
    }
    if (*pbVar12 == 0) {
LAB_004c1d16:
      if (*pbVar9 == 0x2e) {
        pbVar12 = (byte *)str;
      }
    }
    bVar6 = *pbVar9;
    if (((bVar6 == 0) || (bVar6 < 0x21)) || ((0x7f < bVar6 || (bVar6 == 0x3d)))) {
      bVar3 = true;
    }
    else {
      bVar3 = false;
    }
    while ((bVar6 != 0 && (bVar6 != 0x3d))) {
      pbVar10 = pbVar9 + 1;
      pbVar9 = pbVar9 + 1;
      bVar6 = *pbVar10;
    }
    if (*pbVar9 == 0) {
      return (byte *)local_4;
    }
    bVar6 = pbVar9[1];
    pbVar10 = pbVar9;
    while ((pbVar9 = pbVar10 + 1, bVar6 != 0 &&
           ((((bVar6 < 0x21 || (0x7f < bVar6)) || (bVar6 == 0x2c)) || (bVar6 == 0x3b))))) {
      bVar6 = pbVar10[2];
      pbVar10 = pbVar9;
    }
    if ((bVar3) && (*pbVar12 == 0)) {
      bVar6 = 0;
      local_4 = (uint)pbVar9;
    }
    else {
      bVar6 = *pbVar12;
      if (bVar6 == 0x2e) {
        bVar4 = true;
        local_4 = (uint)pbVar9;
      }
    }
    bVar2 = *pbVar9;
    while (((bVar2 != 0 && (0x20 < bVar2)) &&
           ((bVar2 < 0x80 && ((bVar2 != 0x2c && (bVar2 != 0x3b))))))) {
      pbVar12 = pbVar9 + 1;
      pbVar9 = pbVar9 + 1;
      bVar2 = *pbVar12;
    }
    if ((bVar6 == 0) || (bVar4)) {
      if (*pbVar9 == 0) {
        bVar4 = false;
      }
      else {
        *pbVar9 = 0;
        pbVar9 = pbVar9 + 1;
      }
      if (!bVar4) {
        return (byte *)local_4;
      }
      bVar4 = false;
    }
    bVar6 = *pbVar9;
    while ((bVar6 != 0 &&
           ((((bVar6 < 0x21 || (0x7f < bVar6)) || (bVar6 == 0x2c)) || (bVar6 == 0x3b))))) {
      pbVar12 = pbVar9 + 1;
      pbVar9 = pbVar9 + 1;
      bVar6 = *pbVar12;
    }
    bVar6 = *pbVar9;
  } while( true );
}
#undef local_4


/* ---- 0x004c1e00  Str_ModuleNameLength ---- */
/* Length of a module name up to the first '.' or '=' (trailing spaces before '=' trimmed) */

int __cdecl Str_ModuleNameLength(byte *param_1)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  
  bVar1 = *param_1;
  pbVar2 = param_1;
  while (((bVar1 != 0 && (bVar1 != 0x2e)) && (bVar1 != 0x3d))) {
    pbVar3 = pbVar2 + 1;
    pbVar2 = pbVar2 + 1;
    bVar1 = *pbVar3;
  }
  if ((param_1 < pbVar2) && (pbVar3 = pbVar2, *pbVar2 == 0x3d)) {
    do {
      pbVar2 = pbVar3;
      pbVar3 = pbVar2 + -1;
      if ((pbVar3 <= param_1) || (bVar1 = *pbVar3, bVar1 == 0)) break;
    } while ((((bVar1 < 0x21) || (0x7f < bVar1)) || (bVar1 == 0x2c)) || (bVar1 == 0x3b));
  }
  return (int)pbVar2 - (int)param_1;
}

/* ---- 0x004c1e60  Str_StripNonPrintable ---- */
void __cdecl Str_StripNonPrintable(byte *param_1)

{
  byte *pbVar1;
  byte bVar2;
  byte *pbVar3;
  
  bVar2 = *param_1;
  pbVar3 = param_1;
  while (bVar2 != 0) {
    bVar2 = *param_1;
    if ((0x20 < bVar2) && (bVar2 < 0x80)) {
      *pbVar3 = bVar2;
      pbVar3 = pbVar3 + 1;
    }
    pbVar1 = param_1 + 1;
    param_1 = param_1 + 1;
    bVar2 = *pbVar1;
  }
  *pbVar3 = 0;
  return;
}

/* ---- 0x004c1e90  Str_CompareNoCase ---- */
int __cdecl Str_CompareNoCase(char *param_1,char *param_2)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = -1;
  while ((bVar1 = *param_1, bVar1 != 0 || (*param_2 != 0))) {
    bVar2 = *param_2;
    param_1 = param_1 + 1;
    param_2 = param_2 + 1;
    iVar3 = toupper((uint)bVar1);
    iVar4 = toupper((uint)bVar2);
    iVar5 = 0;
    if (iVar3 - iVar4 != 0) {
      return iVar3 - iVar4;
    }
  }
  return iVar5;
}

/* ---- 0x004c1ee0  Str_CompareNoCaseN ---- */
int __cdecl Str_CompareNoCaseN(char *param_1,char *param_2,int param_3)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = -1;
  if (param_3 != 0) {
    while( true ) {
      param_3 = param_3 + -1;
      bVar1 = *param_1;
      if ((bVar1 == 0) && (*param_2 == 0)) break;
      bVar2 = *param_2;
      param_1 = param_1 + 1;
      param_2 = param_2 + 1;
      iVar3 = toupper((uint)bVar2);
      iVar4 = toupper((uint)bVar1);
      if (iVar4 - iVar3 != 0) {
        return iVar4 - iVar3;
      }
      iVar3 = 0;
      if (param_3 == 0) {
        return 0;
      }
    }
  }
  return iVar3;
}
