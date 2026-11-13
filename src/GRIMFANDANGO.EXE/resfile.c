/* GRIMFANDANGO.EXE :: resfile.c
 * functions 0x00480890 .. 0x00481fd0 (11 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00480890  Res_FOpen ---- */
/* Returns a 1-based handle into the 128-entry g_ResFileTable. Read-mode names without a path are
   looked up inside the open LAB archives first (entry = archive handle + offset + size); otherwise
   the underlying fopen is used. Original name Res_FOpen (the remaster's GrimFandango (Linux): the
   same file-services slot filled by Res_OverrideFileCalls); was ResFile_Open. */

int __cdecl Res_FOpen(char *name,char *mode)

{
  unsigned char _frame[0x230] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  char cVar2;
  uint *puVar3;
  uint *puVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  char *pcVar9;
  char *pcVar10;
  #define local_21c (*(uint *)(_frame + (0x230 - 0x21c)))
  #define local_218 (*(undefined1 (*)[4])(_frame + (0x230 - 0x218)))
  #define local_214 (*(uint *)(_frame + (0x230 - 0x214)))
  #define local_210 (*(uint *)(_frame + (0x230 - 0x210)))
  #define local_20c (*(uint *)(_frame + (0x230 - 0x20c)))
  #define local_208 (*(uint *)(_frame + (0x230 - 0x208)))
  #define local_103 (*(undefined1 (*)[259])(_frame + (0x230 - 0x103)))
  
  puVar3 = &UINT_00825f40;
  iVar8 = 0;
  do {
    if (*puVar3 == 0) break;
    puVar3 = puVar3 + 0x40b;
    iVar8 = iVar8 + 1;
  } while ((int)puVar3 < ((unsigned)(uintptr_t)&DAT_008a7540));
  if (iVar8 != 0x80) {
    iVar1 = iVar8 * 0x102c;
    puVar3 = &UINT_00825f40 + iVar8 * 0x40b;
    puVar4 = puVar3;
    for (iVar5 = 0x40b; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    uVar6 = 0xffffffff;
    *(undefined4 *)(iVar1 + ((unsigned)(uintptr_t)&DAT_00825f60)) = 0x1000;
    pcVar9 = mode;
    do {
      pcVar10 = pcVar9;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar10 = pcVar9 + 1;
      cVar2 = *pcVar9;
      pcVar9 = pcVar10;
    } while (cVar2 != '\0');
    uVar6 = ~uVar6;
    pcVar9 = pcVar10 + -uVar6;
    pcVar10 = (char *)(iVar1 + ((unsigned)(uintptr_t)&DAT_00825f64));
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar10 = *(undefined4 *)pcVar9;
      pcVar9 = pcVar9 + 4;
      pcVar10 = pcVar10 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar10 = *pcVar9;
      pcVar9 = pcVar9 + 1;
      pcVar10 = pcVar10 + 1;
    }
    iVar5 = tolower((int)*mode);
    if (((iVar5 == 0x72) && (puVar4 = strchr((uint *)name,'\\'), puVar4 == (uint *)0x0)) &&
       (iVar5 = res_FindInternalFile(name,local_218), iVar5 != 0)) {
      if (local_208 != 0) {
        *puVar3 = local_214;
        *(undefined4 *)(iVar1 + ((unsigned)(uintptr_t)&DAT_00825f5c)) = 0;
        *(uint *)(iVar1 + ((unsigned)(uintptr_t)&DAT_00825f50)) = local_210;
        *(uint *)(iVar1 + ((unsigned)(uintptr_t)&DAT_00825f54)) = local_20c;
        return iVar8 + 1;
      }
      uVar6 = (**(code **)(g_dwLowLevelHS + 0x30))(local_103,mode);
      *puVar3 = uVar6;
      if (uVar6 == 0) {
        return 0;
      }
      *(undefined4 *)(iVar1 + ((unsigned)(uintptr_t)&DAT_00825f5c)) = 1;
      return iVar8 + 1;
    }
    uVar6 = (**(code **)(g_dwLowLevelHS + 0x30))(name,mode);
    *puVar3 = uVar6;
    if (uVar6 != 0) {
      *(undefined4 *)(iVar1 + ((unsigned)(uintptr_t)&DAT_00825f5c)) = 1;
      return iVar8 + 1;
    }
  }
  return 0;
}
#undef local_103
#undef local_208
#undef local_20c
#undef local_210
#undef local_214
#undef local_218
#undef local_21c


/* ---- 0x00480a00  Res_FClose ---- */
/* Source: Temp/Res.c (line 1844, from __FILE__/__LINE__ passed to the allocator) Original name
   Res_FClose (the remaster's GrimFandango (Linux): the same file-services slot filled by
   Res_OverrideFileCalls); was ResFile_Close. */

int __cdecl Res_FClose(int fh)

{
  int iVar1;
  int *piVar2;
  
  if ((fh < 1) || (0x80 < fh)) {
    (**(code **)(g_dwResHS + 0x18))
              (s__int_fh___0_____int_fh____MAX_OP_004e7a8c,
               s_C__grimsrc_libs_grimlib_Temp_Res_004e7a1c,0x734);
  }
  iVar1 = *(int *)(&DAT_00824f14 + fh * 0x102c);
  if (iVar1 == 0) {
    return 1;
  }
  if (*(int *)(&DAT_00824f30 + fh * 0x102c) != 0) {
    (**(code **)(g_dwLowLevelHS + 0x34))(iVar1);
  }
  piVar2 = (int *)(&DAT_00824f14 + fh * 0x102c);
  for (iVar1 = 0x40b; iVar1 != 0; iVar1 = iVar1 + -1) {
    *piVar2 = 0;
    piVar2 = piVar2 + 1;
  }
  return 0;
}

/* ---- 0x00480a70  Res_FRead ---- */
/* Buffered (4 KB) read; archive-backed handles read through Lab_ReadRaw with the entry offset
   applied Original name Res_FRead (the remaster's GrimFandango (Linux): the same file-services slot
   filled by Res_OverrideFileCalls); was ResFile_Read. */

uint __cdecl Res_FRead(int fh,void *buf,uint n)

{
  int iVar1;
  int *entry;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  
  iVar1 = fh * 0x102c;
  entry = (int *)(&DAT_00824f14 + iVar1);
  if ((fh < 1) || (0x80 < fh)) {
    (**(code **)(g_dwResHS + 0x18))
              (s__int_fh___0_____int_fh____MAX_OP_004e7a8c,
               s_C__grimsrc_libs_grimlib_Temp_Res_004e7a1c,0x76b);
  }
  if (*entry == 0) {
    return 0;
  }
  if (*(int *)(&DAT_00824f30 + iVar1) != 0) {
    uVar3 = (**(code **)(g_dwLowLevelHS + 0x38))(*entry,buf,n);
    return uVar3;
  }
  *(uint *)(&DAT_00824f2c + iVar1) =
       (uint)(*(int *)(&DAT_00824f24 + iVar1) <= *(int *)(&DAT_00824f18 + iVar1));
  if ((n < *(uint *)(&DAT_00824f34 + iVar1)) && (*(uint *)(&DAT_00824f20 + iVar1) < n)) {
    ResFile_FillBuffer(entry);
  }
  uVar3 = *(uint *)(&DAT_00824f20 + iVar1);
  if (n <= uVar3) {
    puVar6 = (undefined4 *)(iVar1 + ((unsigned)(uintptr_t)&DAT_00824f40) + *(int *)(&DAT_00824f1c + iVar1));
    for (uVar3 = n >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(undefined4 *)buf = *puVar6;
      puVar6 = puVar6 + 1;
      buf = (undefined4 *)((int)buf + 4);
    }
    for (uVar3 = n & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(undefined1 *)buf = *(undefined1 *)puVar6;
      puVar6 = (undefined4 *)((int)puVar6 + 1);
      buf = (undefined4 *)((int)buf + 1);
    }
    *(uint *)(&DAT_00824f20 + iVar1) = *(int *)(&DAT_00824f20 + iVar1) - n;
    *(uint *)(&DAT_00824f18 + iVar1) = *(int *)(&DAT_00824f18 + iVar1) + n;
    *(uint *)(&DAT_00824f1c + iVar1) = *(int *)(&DAT_00824f1c + iVar1) + n;
    return n;
  }
  if (uVar3 != 0) {
    puVar6 = (undefined4 *)(*(int *)(&DAT_00824f1c + iVar1) + 0x2c + (int)entry);
    puVar7 = buf;
    for (uVar5 = uVar3 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *puVar7 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar7 = puVar7 + 1;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(undefined1 *)puVar7 = *(undefined1 *)puVar6;
      puVar6 = (undefined4 *)((int)puVar6 + 1);
      puVar7 = (undefined4 *)((int)puVar7 + 1);
    }
  }
  iVar2 = *(int *)(&DAT_00824f20 + iVar1);
  iVar4 = *(int *)(&DAT_00824f18 + iVar1);
  *(int *)(&DAT_00824f18 + iVar1) = iVar4 + iVar2;
  *(int *)(&DAT_00824f1c + iVar1) = *(int *)(&DAT_00824f1c + iVar1) + iVar2;
  *(undefined4 *)(&DAT_00824f20 + iVar1) = 0;
  iVar4 = Lab_ReadRaw(entry,(void *)(iVar2 + (int)buf),iVar4 + iVar2,n - iVar2);
  *(int *)(&DAT_00824f18 + iVar1) = *(int *)(&DAT_00824f18 + iVar1) + iVar4;
  return iVar4 + iVar2;
}

/* ---- 0x00480bb0  Res_FGets ---- */
/* pFgets of the resource file services (Res_InstallFileServices): reads a line from the 4 KB buffer
   of an archive entry or forwards to the real file. Original name Res_FGets (the remaster's
   GrimFandango (Linux): the same file-services slot filled by Res_OverrideFileCalls); was
   ResFile_Gets. */

char * __cdecl Res_FGets(int param_1,char *param_2,uint param_3)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  char cVar4;
  char *pcVar5;
  
  iVar2 = param_1;
  cVar4 = '\0';
  param_1 = 0;
  iVar1 = iVar2 * 0x102c;
  if ((iVar2 < 1) || (0x80 < iVar2)) {
    (**(code **)(g_dwResHS + 0x18))
              (s__int_fh___0_____int_fh____MAX_OP_004e7a8c,
               s_C__grimsrc_libs_grimlib_Temp_Res_004e7a1c,0x7bc);
  }
  iVar2 = *(int *)(&DAT_00824f14 + iVar1);
  if (iVar2 == 0) {
    return (char *)0x0;
  }
  if (*(int *)(&DAT_00824f30 + iVar1) != 0) {
    pcVar3 = (char *)(**(code **)(g_dwLowLevelHS + 0x3c))(iVar2,param_2,param_3);
    return pcVar3;
  }
  if (*(uint *)(&DAT_00824f20 + iVar1) < param_3) {
    ResFile_FillBuffer(&DAT_00824f14 + iVar1);
  }
  if (*(uint *)(&DAT_00824f20 + iVar1) < param_3) {
    param_3 = *(uint *)(&DAT_00824f20 + iVar1) + 1;
  }
  pcVar3 = (char *)(iVar1 + ((unsigned)(uintptr_t)&DAT_00824f40) + *(int *)(&DAT_00824f1c + iVar1));
  pcVar5 = param_2;
  while (param_3 = param_3 - 1, 0 < (int)param_3) {
    cVar4 = *pcVar3;
    pcVar3 = pcVar3 + 1;
    param_1 = param_1 + 1;
    if ((cVar4 == '\n') || (cVar4 == '\r')) break;
    *pcVar5 = cVar4;
    pcVar5 = pcVar5 + 1;
  }
  if (param_3 != 0) {
    *pcVar5 = '\n';
    pcVar5 = pcVar5 + 1;
  }
  *pcVar5 = '\0';
  if ((cVar4 == '\r') && (*pcVar3 == '\n')) {
    param_1 = param_1 + 1;
  }
  iVar2 = *(int *)(&DAT_00824f18 + iVar1);
  *(int *)(&DAT_00824f18 + iVar1) = iVar2 + param_1;
  *(int *)(&DAT_00824f1c + iVar1) = *(int *)(&DAT_00824f1c + iVar1) + param_1;
  *(int *)(&DAT_00824f20 + iVar1) = *(int *)(&DAT_00824f20 + iVar1) - param_1;
  if ((*(int *)(&DAT_00824f24 + iVar1) <= iVar2 + param_1) && (*param_2 == '\0')) {
    *(undefined4 *)(&DAT_00824f2c + iVar1) = 1;
    return (char *)0x0;
  }
  *(undefined4 *)(&DAT_00824f2c + iVar1) = 0;
  return param_2;
}

/* ---- 0x00480ce0  Res_FWrite ---- */
/* pFwrite of the resource file services: only real files can be written. Original name Res_FWrite
   (the remaster's GrimFandango (Linux): the same file-services slot filled by
   Res_OverrideFileCalls); was ResFile_Write. */

uint __cdecl Res_FWrite(int param_1,uint param_2,uint param_3)

{
  uint uVar1;
  
  if (param_1 != 0) {
    if ((param_1 < 1) || (0x80 < param_1)) {
      (**(code **)(g_dwResHS + 0x18))
                (s__int_fh___0_____int_fh____MAX_OP_004e7a8c,
                 s_C__grimsrc_libs_grimlib_Temp_Res_004e7a1c,0x81b);
    }
    if ((*(int *)(&DAT_00824f14 + param_1 * 0x102c) != 0) &&
       (*(int *)(&DAT_00824f30 + param_1 * 0x102c) != 0)) {
      uVar1 = (**(code **)(g_dwLowLevelHS + 0x40))
                        (*(int *)(&DAT_00824f14 + param_1 * 0x102c),param_2,param_3);
      return uVar1;
    }
  }
  return 0;
}

/* ---- 0x00480d50  Res_FEOF ---- */
/* pFeof of the resource file services. Original name Res_FEOF (the remaster's GrimFandango (Linux):
   the same file-services slot filled by Res_OverrideFileCalls); was ResFile_Eof. */

uint __cdecl Res_FEOF(int param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = param_1 * 0x102c;
  if ((param_1 < 1) || (0x80 < param_1)) {
    (**(code **)(g_dwResHS + 0x18))
              (s__int_fh___0_____int_fh____MAX_OP_004e7a8c,
               s_C__grimsrc_libs_grimlib_Temp_Res_004e7a1c,0x84c);
  }
  if (*(int *)(&DAT_00824f14 + iVar1) == 0) {
    return 1;
  }
  if (*(int *)(&DAT_00824f30 + iVar1) != 0) {
    uVar2 = (**(code **)(g_dwLowLevelHS + 0x44))(*(int *)(&DAT_00824f14 + iVar1));
    return uVar2;
  }
  return *(uint *)(&DAT_00824f2c + iVar1);
}

/* ---- 0x00480dc0  Res_FTell ---- */
/* pFtell of the resource file services: the current position of an archive entry (relative to its
   start) or of the real file. Original name Res_FTell (the remaster's GrimFandango (Linux): the
   same file-services slot filled by Res_OverrideFileCalls); was ResFile_Tell. */

uint __cdecl Res_FTell(int param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = param_1 * 0x102c;
  if ((param_1 < 1) || (0x80 < param_1)) {
    (**(code **)(g_dwResHS + 0x18))
              (s__int_fh___0_____int_fh____MAX_OP_004e7a8c,
               s_C__grimsrc_libs_grimlib_Temp_Res_004e7a1c,0x87e);
  }
  if (*(int *)(&DAT_00824f14 + iVar1) == 0) {
    return 0xffffffff;
  }
  if (*(int *)(&DAT_00824f30 + iVar1) != 0) {
    uVar2 = (**(code **)(g_dwLowLevelHS + 0x48))(*(int *)(&DAT_00824f14 + iVar1));
    return uVar2;
  }
  return *(uint *)(&DAT_00824f18 + iVar1);
}

/* ---- 0x00480e30  Res_FSeek ---- */
/* Source: Temp/Res.c (line 2225, from __FILE__/__LINE__ passed to the allocator) Original name
   Res_FSeek (the remaster's GrimFandango (Linux): the same file-services slot filled by
   Res_OverrideFileCalls); was ResFile_Seek. */

int __cdecl Res_FSeek(int fh,int offset,int whence)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = fh * 0x102c;
  if ((fh < 1) || (0x80 < fh)) {
    (**(code **)(g_dwResHS + 0x18))
              (s__int_fh___0_____int_fh____MAX_OP_004e7a8c,
               s_C__grimsrc_libs_grimlib_Temp_Res_004e7a1c,0x8b1);
  }
  iVar1 = *(int *)(&DAT_00824f14 + iVar2);
  if (iVar1 == 0) {
    return 1;
  }
  if (*(int *)(&DAT_00824f30 + iVar2) != 0) {
    if ((whence == 0) && (iVar1 = (**(code **)(g_dwLowLevelHS + 0x48))(iVar1), iVar1 == offset)) {
      return 0;
    }
    iVar2 = (**(code **)(g_dwLowLevelHS + 0x4c))(*(int *)(&DAT_00824f14 + iVar2),offset,whence);
    return (uint)(iVar2 == 0);
  }
  if (whence != 0) {
    if (whence == 1) {
      iVar1 = *(int *)(&DAT_00824f18 + iVar2);
    }
    else {
      if (whence != 2) {
        return 1;
      }
      iVar1 = *(int *)(&DAT_00824f24 + iVar2);
    }
    offset = iVar1 + offset;
  }
  iVar3 = *(int *)(&DAT_00824f18 + iVar2) - *(int *)(&DAT_00824f1c + iVar2);
  iVar1 = iVar3 + *(int *)(&DAT_00824f20 + iVar2) + *(int *)(&DAT_00824f1c + iVar2);
  if ((iVar3 <= offset) && (offset < iVar1 + -1)) {
    *(int *)(&DAT_00824f20 + iVar2) = iVar1 - offset;
    *(int *)(&DAT_00824f1c + iVar2) = offset - iVar3;
    *(int *)(&DAT_00824f18 + iVar2) = offset;
    return 0;
  }
  *(undefined4 *)(&DAT_00824f20 + iVar2) = 0;
  *(undefined4 *)(&DAT_00824f1c + iVar2) = 0;
  *(int *)(&DAT_00824f18 + iVar2) = offset;
  return 0;
}

/* ---- 0x00480f40  Res_FSize ---- */
/* Original name Res_FSize (the remaster's GrimFandango (Linux): the same file-services slot filled
   by Res_OverrideFileCalls); was ResFile_Size. */

int __cdecl Res_FSize(char *name)

{
  unsigned char _frame[0x230] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_218 (*(undefined1 (*)[8])(_frame + (0x230 - 0x218)))
  #define local_210 (*(uint *)(_frame + (0x230 - 0x210)))
  
  iVar1 = res_FindInternalFile(name,local_218);
  if (iVar1 != 0) {
    return local_210;
  }
  iVar1 = (**(code **)(g_dwLowLevelHS + 0x50))(name);
  return iVar1;
}
#undef local_210
#undef local_218


/* ---- 0x00480f90  Res_FPrintf ---- */
/* Source: Temp/Res.c (line 2342, from __FILE__/__LINE__ passed to the allocator) Original name
   Res_FPrintf (the remaster's GrimFandango (Linux): the same file-services slot filled by
   Res_OverrideFileCalls); was ResFile_Printf. */

int __cdecl Res_FPrintf(int fh,char *fmt,...)

{
  unsigned char _frame[0x410];  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  int iVar2;
  #define local_400 (*(undefined1 (*)[1024])(_frame + (0x410 - 0x400)))
  
  piVar1 = (int *)(&DAT_00824f14 + fh * 0x102c);
  if (fh == 0) {
    return 0;
  }
  if ((fh < 1) || (0x80 < fh)) {
    (**(code **)(g_dwResHS + 0x18))
              (s__int_fh___0_____int_fh____MAX_OP_004e7a8c,
               s_C__grimsrc_libs_grimlib_Temp_Res_004e7a1c,0x926);
  }
  if ((*piVar1 != 0) && (*(int *)(&DAT_00824f30 + fh * 0x102c) != 0)) {
    vsprintf((uint)local_400,(uint)fmt,(uint)&STACK0X(0x0000000c));
    iVar2 = (**(code **)(g_dwLowLevelHS + 0x54))(*piVar1,local_400);
    fflush(*piVar1);
    return iVar2;
  }
  return 0;
}
#undef local_400


/* ---- 0x00481fd0  ResFile_FillBuffer ---- */
void __cdecl ResFile_FillBuffer(void *entry)

{
  int iVar1;
  int iVar2;
  uint *buf;
  
  iVar2 = *(int *)((int)entry + 0x20);
  buf = (uint *)((int)entry + 0x2c);
  iVar1 = 0;
  if (*(uint *)((int)entry + 0xc) != 0) {
    memmove(buf,(uint *)(*(int *)((int)entry + 8) + (int)buf),*(uint *)((int)entry + 0xc));
    iVar1 = *(int *)((int)entry + 0xc);
    iVar2 = iVar2 - iVar1;
    buf = (uint *)((int)buf + iVar1);
  }
  iVar2 = Lab_ReadRaw(entry,buf,*(int *)((int)entry + 4) + iVar1,iVar2);
  *(undefined4 *)((int)entry + 8) = 0;
  *(int *)((int)entry + 0xc) = *(int *)((int)entry + 0xc) + iVar2;
  return;
}
