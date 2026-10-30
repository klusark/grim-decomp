/* GRIMFANDANGO.EXE :: string.c
 * functions 0x004735b0 .. 0x004c1ee0 (13 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004735b0  Str_FileNameFromPath ---- */
char * __cdecl Str_FileNameFromPath(char *path)

{
  int iVar1;
  
  iVar1 = strrchr(path,0x5c);
  if (iVar1 != 0) {
    return (char *)(iVar1 + 1);
  }
  return path;
}

/* ---- 0x0047b5c0  Str_ToLower ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
char * __cdecl Str_ToLower(char *s)

{
  char cVar1;
  undefined4 in_EAX;
  char *pcVar2;
  undefined4 uVar3;
  
  cVar1 = *s;
  pcVar2 = (char *)CONCAT31((int3)((uint)in_EAX >> 8),cVar1);
  while (cVar1 != '\0') {
    uVar3 = tolower((int)(char)pcVar2);
    *s = (char)uVar3;
    cVar1 = s[1];
    pcVar2 = (char *)CONCAT31((int3)((uint)uVar3 >> 8),cVar1);
    s = s + 1;
  }
  return pcVar2;
}
#endif


/* ---- 0x0047fd20  Str_Basename ---- */
char * __cdecl Str_Basename(char *path)

{
  char *pcVar1;
  char cVar2;
  char *pcVar3;
  
  pcVar3 = (char *)strrchr(path,0x5c);
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

/* ---- 0x0047fd50  Str_FileExtension ---- */
char * __cdecl Str_FileExtension(char *path)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  pcVar1 = Str_Basename(path);
  iVar2 = strrchr(pcVar1,0x2e);
  if (iVar2 != 0) {
    iVar3 = strrchr(iVar2 + 1,0x2e);
    while (iVar3 != 0) {
      iVar4 = strrchr(iVar3 + 1,0x2e);
      iVar2 = iVar3;
      iVar3 = iVar4;
    }
    return (char *)(iVar2 + 1);
  }
  return (char *)0x0;
}

/* ---- 0x0047fda0  Str_StripExtension ---- */
void Str_StripExtension(char *param_1)

{
  char *pcVar1;
  
  pcVar1 = Str_FileExtension(param_1);
  if (pcVar1 != (char *)0x0) {
    pcVar1[-1] = '\0';
  }
  return;
}

/* ---- 0x0047fdc0  Str_CopyBasenameNoExt ---- */
void __cdecl Str_CopyBasenameNoExt(char *dst,int size,char *path)

{
  char *pcVar1;
  
  pcVar1 = Str_Basename(path);
  strncpy(dst,pcVar1,size + -1);
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
uint * String_ContainsSubstring(uint *param_1,char *param_2)

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

/* ---- 0x004c1c30  Str_WildcardMatch ---- */
byte * __cdecl Str_WildcardMatch(char *str,char *pattern)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  bool bVar2;
  bool bVar3;
  int iVar4;
  char cVar5;
  uint uVar6;
  int iVar7;
  byte *pbVar8;
  byte *pbVar9;
  char *pcVar10;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar6 = 0xffffffff;
  bVar3 = false;
  pcVar10 = pattern;
  do {
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    cVar5 = *pcVar10;
    pcVar10 = pcVar10 + 1;
  } while (cVar5 != '\0');
  local_4 = 0;
  if (~uVar6 - 1 < 0x1fff) {
    uVar6 = 0xffffffff;
    pcVar10 = pattern;
    do {
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      cVar5 = *pcVar10;
      pcVar10 = pcVar10 + 1;
    } while (cVar5 != '\0');
    iVar7 = ~uVar6 - 1;
  }
  else {
    iVar7 = 0x1fff;
  }
  strncpy(&DAT_008d36e8,pattern,iVar7);
  uVar6 = 0xffffffff;
  pcVar10 = pattern;
  do {
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    cVar5 = *pcVar10;
    pcVar10 = pcVar10 + 1;
  } while (cVar5 != '\0');
  if (~uVar6 - 1 < 0x1fff) {
    uVar6 = 0xffffffff;
    do {
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      cVar5 = *pattern;
      pattern = pattern + 1;
    } while (cVar5 != '\0');
    iVar7 = ~uVar6 - 1;
  }
  else {
    iVar7 = 0x1fff;
  }
  (&DAT_008d36e8)[iVar7] = 0;
  pbVar8 = &DAT_008d36e8;
  bVar1 = DAT_008d36e8;
  do {
    if (bVar1 == 0) {
      return (byte *)local_4;
    }
    bVar1 = *pbVar8;
    while ((bVar1 != 0 &&
           ((((bVar1 < 0x21 || (0x7f < bVar1)) || (bVar1 == 0x2c)) || (bVar1 == 0x3b))))) {
      pbVar9 = pbVar8 + 1;
      pbVar8 = pbVar8 + 1;
      bVar1 = *pbVar9;
    }
    bVar1 = *pbVar8;
    pcVar10 = str;
    while (bVar1 != 0) {
      if (*pcVar10 == '\0') goto LAB_004c1d16;
      iVar7 = toupper(*pcVar10);
      iVar4 = toupper(bVar1);
      if (iVar7 != iVar4) break;
      pbVar9 = pbVar8 + 1;
      pbVar8 = pbVar8 + 1;
      pcVar10 = pcVar10 + 1;
      bVar1 = *pbVar9;
    }
    if (*pcVar10 == '\0') {
LAB_004c1d16:
      if (*pbVar8 == 0x2e) {
        pcVar10 = str;
      }
    }
    bVar1 = *pbVar8;
    if (((bVar1 == 0) || (bVar1 < 0x21)) || ((0x7f < bVar1 || (bVar1 == 0x3d)))) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    while ((bVar1 != 0 && (bVar1 != 0x3d))) {
      pbVar9 = pbVar8 + 1;
      pbVar8 = pbVar8 + 1;
      bVar1 = *pbVar9;
    }
    if (*pbVar8 == 0) {
      return (byte *)local_4;
    }
    bVar1 = pbVar8[1];
    pbVar9 = pbVar8;
    while ((pbVar8 = pbVar9 + 1, bVar1 != 0 &&
           ((((bVar1 < 0x21 || (0x7f < bVar1)) || (bVar1 == 0x2c)) || (bVar1 == 0x3b))))) {
      bVar1 = pbVar9[2];
      pbVar9 = pbVar8;
    }
    if ((bVar2) && (*pcVar10 == '\0')) {
      cVar5 = '\0';
      local_4 = (uint)pbVar8;
    }
    else {
      cVar5 = *pcVar10;
      if (cVar5 == '.') {
        bVar3 = true;
        local_4 = (uint)pbVar8;
      }
    }
    bVar1 = *pbVar8;
    while (((bVar1 != 0 && (0x20 < bVar1)) &&
           ((bVar1 < 0x80 && ((bVar1 != 0x2c && (bVar1 != 0x3b))))))) {
      pbVar9 = pbVar8 + 1;
      pbVar8 = pbVar8 + 1;
      bVar1 = *pbVar9;
    }
    if ((cVar5 == '\0') || (bVar3)) {
      if (*pbVar8 == 0) {
        bVar3 = false;
      }
      else {
        *pbVar8 = 0;
        pbVar8 = pbVar8 + 1;
      }
      if (!bVar3) {
        return (byte *)local_4;
      }
      bVar3 = false;
    }
    bVar1 = *pbVar8;
    while ((bVar1 != 0 &&
           ((((bVar1 < 0x21 || (0x7f < bVar1)) || (bVar1 == 0x2c)) || (bVar1 == 0x3b))))) {
      pbVar9 = pbVar8 + 1;
      pbVar8 = pbVar8 + 1;
      bVar1 = *pbVar9;
    }
    bVar1 = *pbVar8;
  } while( true );
}
#undef local_4


/* ---- 0x004c1e00  Str_ModuleNameLength ---- */
/* Length of a module name up to the first '.' or '=' (trailing spaces before '=' trimmed) */

int Str_ModuleNameLength(byte *param_1)

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
void Str_StripNonPrintable(byte *param_1)

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
int Str_CompareNoCase(char *param_1,char *param_2)

{
  char cVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = -1;
  while ((cVar1 = *param_1, cVar1 != '\0' || (*param_2 != '\0'))) {
    cVar2 = *param_2;
    param_1 = param_1 + 1;
    param_2 = param_2 + 1;
    iVar3 = toupper(cVar1);
    iVar4 = toupper(cVar2);
    iVar5 = 0;
    if (iVar3 - iVar4 != 0) {
      return iVar3 - iVar4;
    }
  }
  return iVar5;
}

/* ---- 0x004c1ee0  Str_CompareNoCaseN ---- */
int Str_CompareNoCaseN(char *param_1,char *param_2,int param_3)

{
  char cVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = -1;
  if (param_3 != 0) {
    while( true ) {
      param_3 = param_3 + -1;
      cVar1 = *param_1;
      if ((cVar1 == '\0') && (*param_2 == '\0')) break;
      cVar2 = *param_2;
      param_1 = param_1 + 1;
      param_2 = param_2 + 1;
      iVar3 = toupper(cVar2);
      iVar4 = toupper(cVar1);
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
