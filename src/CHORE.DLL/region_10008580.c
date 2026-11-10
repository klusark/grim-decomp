/* CHORE.DLL :: region_10008580.c
 * functions 0x10008580 .. 0x1000dba0 (102 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10008580  FUN_10008580 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_10008580(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)IMG_ADDR(0x100145e8);
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined1 *)puVar2 = 0;
  _DAT_100147f0 = 0;
  _DAT_100159c8 = 0;
  _DAT_100147f4 = 0;
  _DAT_100147f8 = 0;
  _DAT_100147fc = 0;
  _DAT_10014800 = 0;
  return;
}
#endif


/* ---- 0x100085c0  FUN_100085c0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_100085c0(void)

{
  unsigned char _frame[0x530] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  unsigned char _stkneg[1328] __attribute__((aligned(16)));  /* the original frame below the return address */
  byte bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  byte *pbVar6;
  ushort *puVar7;
  undefined4 unaff_EBX;
  undefined4 *puVar8;
  #define abStack_514 (*(byte (*)[12])(_frame + (0x530 - 0x514)))
  #define auStack_508 (*(undefined4 (*)[64])(_frame + (0x530 - 0x508)))
  #define auStack_408 (*(undefined1 (*)[256])(_frame + (0x530 - 0x408)))
  #define auStack_308 (*(undefined1 (*)[256])(_frame + (0x530 - 0x308)))
  #define auStack_208 (*(ushort (*)[260])(_frame + (0x530 - 0x208)))
  
  iVar2 = GetCPInfo(_DAT_100147f0,abStack_514);
  if (iVar2 == 1) {
    uVar3 = 0;
    do {
      *(char *)((int)auStack_508 + uVar3) = (char)uVar3;
      uVar3 = uVar3 + 1;
    } while (uVar3 < 0x100);
    bVar1 = (byte)((uint)unaff_EBX >> 0x10);
    auStack_508[0]._0_1_ = 0x20;
    if (bVar1 != 0) {
      pbVar6 = (_stkneg + 27);
      do {
        uVar3 = (uint)bVar1;
        if (uVar3 <= *pbVar6) {
          uVar4 = (*pbVar6 - uVar3) + 1;
          puVar8 = (undefined4 *)((int)auStack_508 + uVar3);
          for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
            *puVar8 = 0x20202020;
            puVar8 = puVar8 + 1;
          }
          for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
            *(undefined1 *)puVar8 = 0x20;
            puVar8 = (undefined4 *)((int)puVar8 + 1);
          }
        }
        bVar1 = pbVar6[1];
        pbVar6 = pbVar6 + 2;
      } while (bVar1 != 0);
    }
    FUN_1000af40(1,auStack_508,0x100,auStack_208,_DAT_100147f0,_DAT_100147f4,0);
    FUN_1000a710(_DAT_100147f4,0x100,auStack_508,0x100,auStack_408,0x100,_DAT_100147f0,0);
    FUN_1000a710(_DAT_100147f4,0x200,auStack_508,0x100,auStack_308,0x100,_DAT_100147f0,0);
    uVar3 = 0;
    puVar7 = auStack_208;
    do {
      if ((*puVar7 & 1) == 0) {
        if ((*puVar7 & 2) == 0) {
          *(undefined1 *)(uVar3 + IMG_ADDR(0x100146f0)) = 0;
        }
        else {
          *(byte *)(uVar3 + IMG_ADDR(0x100145e9)) = *(byte *)(uVar3 + IMG_ADDR(0x100145e9)) | 0x20;
          *(undefined1 *)(uVar3 + IMG_ADDR(0x100146f0)) = auStack_308[uVar3];
        }
      }
      else {
        *(byte *)(uVar3 + IMG_ADDR(0x100145e9)) = *(byte *)(uVar3 + IMG_ADDR(0x100145e9)) | 0x10;
        *(undefined1 *)(uVar3 + IMG_ADDR(0x100146f0)) = auStack_408[uVar3];
      }
      uVar3 = uVar3 + 1;
      puVar7 = puVar7 + 1;
    } while (uVar3 < 0x100);
    return;
  }
  uVar3 = 0;
  do {
    if ((uVar3 < 0x41) || (0x5a < uVar3)) {
      if ((uVar3 < 0x61) || (0x7a < uVar3)) {
        *(undefined1 *)(uVar3 + IMG_ADDR(0x100146f0)) = 0;
      }
      else {
        *(byte *)(uVar3 + IMG_ADDR(0x100145e9)) = *(byte *)(uVar3 + IMG_ADDR(0x100145e9)) | 0x20;
        *(char *)(uVar3 + IMG_ADDR(0x100146f0)) = (char)uVar3 + -0x20;
      }
    }
    else {
      *(byte *)(uVar3 + IMG_ADDR(0x100145e9)) = *(byte *)(uVar3 + IMG_ADDR(0x100145e9)) | 0x10;
      *(char *)(uVar3 + IMG_ADDR(0x100146f0)) = (char)uVar3 + ' ';
    }
    uVar3 = uVar3 + 1;
  } while (uVar3 < 0x100);
  return;
}
#undef abStack_514
#undef auStack_208
#undef auStack_308
#undef auStack_408
#undef auStack_508

#endif


/* ---- 0x100087a0  FUN_100087a0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_100087a0(void)

{
  FUN_100082a0(0xfffffffd);
  return;
}
#endif


/* ---- 0x100087b0  FUN_100087b0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

char * FUN_100087b0(void)

{
  char cVar1;
  short sVar2;
  short *psVar3;
  int iVar5;
  int iVar6;
  char *pcVar7;
  char *pcVar8;
  uint uVar9;
  char *pcVar10;
  short *psVar11;
  char *pcVar12;
  char *pcVar13;
  short *psVar4;
  
  psVar11 = (short *)0x0;
  pcVar10 = (char *)0x0;
  if (_DAT_1001480c == 0) {
    psVar11 = (short *)GetEnvironmentStringsW();
    if (psVar11 == (short *)0x0) {
      pcVar10 = (char *)GetEnvironmentStrings();
      if (pcVar10 == (char *)0x0) {
        return (char *)0x0;
      }
      _DAT_1001480c = 2;
    }
    else {
      _DAT_1001480c = 1;
    }
  }
  if (_DAT_1001480c == 1) {
    if ((psVar11 != (short *)0x0) ||
       (psVar11 = (short *)GetEnvironmentStringsW(), psVar11 != (short *)0x0)) {
      sVar2 = *psVar11;
      psVar3 = psVar11;
      while (sVar2 != 0) {
        do {
          psVar4 = psVar3;
          psVar3 = psVar4 + 1;
        } while (*psVar3 != 0);
        psVar3 = psVar4 + 2;
        sVar2 = *psVar3;
      }
      iVar5 = ((int)psVar3 - (int)psVar11 >> 1) + 1;
      iVar6 = WideCharToMultiByte(0,0,psVar11,iVar5,0,0,0,0);
      if ((iVar6 != 0) && (pcVar10 = (char *)FUN_10009580(iVar6), pcVar10 != (char *)0x0)) {
        iVar5 = WideCharToMultiByte(0,0,psVar11,iVar5,pcVar10,iVar6,0,0);
        if (iVar5 == 0) {
          FUN_10009510();
          pcVar10 = (char *)0x0;
        }
        FreeEnvironmentStringsW(psVar11);
        return pcVar10;
      }
      FreeEnvironmentStringsW(psVar11);
      return (char *)0x0;
    }
  }
  else if ((_DAT_1001480c == 2) &&
          ((pcVar10 != (char *)0x0 ||
           (pcVar10 = (char *)GetEnvironmentStrings(), pcVar10 != (char *)0x0)))) {
    cVar1 = *pcVar10;
    pcVar7 = pcVar10;
    while (cVar1 != '\0') {
      do {
        pcVar8 = pcVar7;
        pcVar7 = pcVar8 + 1;
      } while (pcVar8[1] != '\0');
      pcVar7 = pcVar8 + 2;
      cVar1 = pcVar8[2];
    }
    pcVar7 = pcVar7 + (1 - (int)pcVar10);
    pcVar8 = (char *)FUN_10009580(pcVar7);
    if (pcVar8 != (char *)0x0) {
      pcVar12 = pcVar10;
      pcVar13 = pcVar8;
      for (uVar9 = (uint)pcVar7 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar12;
        pcVar12 = pcVar12 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar9 = (uint)pcVar7 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
        *pcVar13 = *pcVar12;
        pcVar12 = pcVar12 + 1;
        pcVar13 = pcVar13 + 1;
      }
      FreeEnvironmentStringsA(pcVar10);
      return pcVar8;
    }
    FreeEnvironmentStringsA(pcVar10);
    return (char *)0x0;
  }
  return (char *)0x0;
}
#endif


/* ---- 0x10008910  FUN_10008910 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_10008910(void)

{
  int iVar1;
  
  _DAT_100159c4 = HeapCreate(0,0x1000,0);
  if (_DAT_100159c4 == 0) {
    return 0;
  }
  iVar1 = FUN_1000b080();
  if (iVar1 == 0) {
    HeapDestroy(_DAT_100159c4);
    return 0;
  }
  return 1;
}
#endif


/* ---- 0x10008950  FUN_10008950 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_10008950(void)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)&DAT_100117a8;
  do {
    if (puVar1[4] != 0) {
      VirtualFree(puVar1[4],0,0x8000);
    }
    puVar1 = (undefined4 *)*puVar1;
  } while (puVar1 != (undefined4 *)&DAT_100117a8);
  HeapDestroy(_DAT_100159c4);
  return;
}
#endif


/* ---- 0x10008990  FUN_10008990 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 __stdcall FUN_10008990(int a1,int a2,int a3)

{
  return 1;
}
#endif


/* ---- 0x100089a0  FUN_100089a0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_100089a0(void)

{
  if ((_DAT_10014408 == 1) || ((_DAT_10014408 == 0 && (_DAT_1001440c == 1)))) {
    FUN_100089e0(0xfc);
    if (_DAT_10014810 != (code *)0x0) {
      (*_DAT_10014810)();
    }
    FUN_100089e0(0xff);
  }
  return;
}
#endif


/* ---- 0x100089e0  FUN_100089e0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_100089e0(int param_1)

{
  unsigned char _frame[0x1c0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  unsigned char _stkneg[448] __attribute__((aligned(16)));  /* the original frame below the return address */
  char cVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  char *pcVar10;
  char *pcVar11;
  #define auStack_1a8 (*(undefined1 (*)[92])(_frame + (0x1c0 - 0x1a8)))
  #define acStack_14c (*(char (*)[60])(_frame + (0x1c0 - 0x14c)))
  #define acStack_110 (*(char (*)[12])(_frame + (0x1c0 - 0x110)))
  #define auStack_104 (*(undefined1 (*)[260])(_frame + (0x1c0 - 0x104)))
  
  piVar2 = (int *)IMG_ADDR(0x10010a38);
  iVar7 = 0;
  do {
    if (param_1 == *piVar2) break;
    piVar2 = piVar2 + 2;
    iVar7 = iVar7 + 1;
  } while (piVar2 < &DAT_10010ac8);
  if (param_1 == *(int *)(iVar7 * 8 + IMG_ADDR(0x10010a38))) {
    if ((_DAT_10014408 == 1) || ((_DAT_10014408 == 0 && (_DAT_1001440c == 1)))) {
      if ((_DAT_100159e0 == 0) || (iVar3 = *(int *)(_DAT_100159e0 + 0x48), iVar3 == -1)) {
        iVar3 = GetStdHandle(0xfffffff4);
      }
      pcVar6 = *(char **)(iVar7 * 8 + IMG_ADDR(0x10010a3c));
      uVar4 = 0xffffffff;
      pcVar11 = pcVar6;
      do {
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        cVar1 = *pcVar11;
        pcVar11 = pcVar11 + 1;
      } while (cVar1 != '\0');
      WriteFile(iVar3,pcVar6,~uVar4 - 1,auStack_1a8,0);
    }
    else if (param_1 != 0xfc) {
      iVar3 = GetModuleFileNameA(0,auStack_104,0x104);
      if (iVar3 == 0) {
        puVar8 = (undefined4 *)&UNK_1000e434;
        pcVar6 = acStack_110;
        for (iVar3 = 5; iVar3 != 0; iVar3 = iVar3 + -1) {
          *(undefined4 *)pcVar6 = *puVar8;
          puVar8 = puVar8 + 1;
          pcVar6 = pcVar6 + 4;
        }
        *(undefined2 *)pcVar6 = *(undefined2 *)puVar8;
        pcVar6[2] = *(char *)((int)puVar8 + 2);
      }
      uVar4 = 0xffffffff;
      pcVar6 = acStack_110;
      pcVar11 = acStack_110;
      do {
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        cVar1 = *pcVar11;
        pcVar11 = pcVar11 + 1;
      } while (cVar1 != '\0');
      if (0x3c < ~uVar4) {
        uVar4 = 0xffffffff;
        pcVar6 = acStack_110;
        do {
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          cVar1 = *pcVar6;
          pcVar6 = pcVar6 + 1;
        } while (cVar1 != '\0');
        pcVar6 = acStack_14c + ~uVar4;
        msvc_strncpy(pcVar6,&UNK_1000e430,3);
      }
      puVar8 = (undefined4 *)&UNK_1000e414;
      puVar9 = (undefined4 *)(_stkneg + 16);
      for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar9 = *puVar8;
        puVar8 = puVar8 + 1;
        puVar9 = puVar9 + 1;
      }
      *(undefined2 *)puVar9 = *(undefined2 *)puVar8;
      uVar4 = 0xffffffff;
      do {
        pcVar11 = pcVar6;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar11 = pcVar6 + 1;
        cVar1 = *pcVar6;
        pcVar6 = pcVar11;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      iVar3 = -1;
      pcVar6 = (_stkneg + 16);
      do {
        pcVar10 = pcVar6;
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        pcVar10 = pcVar6 + 1;
        cVar1 = *pcVar6;
        pcVar6 = pcVar10;
      } while (cVar1 != '\0');
      pcVar6 = pcVar11 + -uVar4;
      pcVar11 = pcVar10 + -1;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar11 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar11 = pcVar11 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar11 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar11 = pcVar11 + 1;
      }
      uVar4 = 0xffffffff;
      pcVar6 = "\n\n";
      do {
        pcVar11 = pcVar6;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar11 = pcVar6 + 1;
        cVar1 = *pcVar6;
        pcVar6 = pcVar11;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      iVar3 = -1;
      pcVar6 = (_stkneg + 16);
      do {
        pcVar10 = pcVar6;
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        pcVar10 = pcVar6 + 1;
        cVar1 = *pcVar6;
        pcVar6 = pcVar10;
      } while (cVar1 != '\0');
      pcVar6 = pcVar11 + -uVar4;
      pcVar11 = pcVar10 + -1;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar11 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar11 = pcVar11 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar11 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar11 = pcVar11 + 1;
      }
      uVar4 = 0xffffffff;
      pcVar6 = *(char **)(iVar7 * 8 + IMG_ADDR(0x10010a3c));
      do {
        pcVar11 = pcVar6;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar11 = pcVar6 + 1;
        cVar1 = *pcVar6;
        pcVar6 = pcVar11;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      iVar7 = -1;
      pcVar6 = (_stkneg + 16);
      do {
        pcVar10 = pcVar6;
        if (iVar7 == 0) break;
        iVar7 = iVar7 + -1;
        pcVar10 = pcVar6 + 1;
        cVar1 = *pcVar6;
        pcVar6 = pcVar10;
      } while (cVar1 != '\0');
      pcVar6 = pcVar11 + -uVar4;
      pcVar11 = pcVar10 + -1;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar11 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar11 = pcVar11 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar11 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar11 = pcVar11 + 1;
      }
      ((code *)FUN_1000b7a0)((_stkneg + 16),&UNK_1000e3e8);
      return;
    }
  }
  return;
}
#undef acStack_110
#undef acStack_14c
#undef auStack_104
#undef auStack_1a8

#endif


/* ---- 0x10008bc0  FUN_10008bc0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint FUN_10008bc0(uint param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = ((code *)FUN_10008c20)();
  FUN_10008cc0();
  return param_2 & param_1 | ~param_2 & uVar1;
}
#endif


/* ---- 0x10008c00  FUN_10008c00 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10008c00(undefined4 param_1,uint param_2)

{
  FUN_10008bc0(param_1,param_2 & 0xfff7ffff);
  return;
}
#endif


/* ---- 0x10008c20  FUN_10008c20 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint FUN_10008c20(uint param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = 0;
  if ((param_1 & 1) != 0) {
    uVar1 = 0x10;
  }
  if ((param_1 & 4) != 0) {
    uVar1 = uVar1 | 8;
  }
  if ((param_1 & 8) != 0) {
    uVar1 = uVar1 | 4;
  }
  if ((param_1 & 0x10) != 0) {
    uVar1 = uVar1 | 2;
  }
  if ((param_1 & 0x20) != 0) {
    uVar1 = uVar1 | 1;
  }
  if ((param_1 & 2) != 0) {
    uVar1 = uVar1 | 0x80000;
  }
  uVar2 = param_1 & 0xc00;
  if (uVar2 < 0x401) {
    if (uVar2 == 0x400) {
      uVar1 = uVar1 | 0x100;
    }
  }
  else if (uVar2 == 0x800) {
    uVar1 = uVar1 | 0x200;
  }
  else if (uVar2 == 0xc00) {
    uVar1 = uVar1 | 0x300;
  }
  if ((param_1 & 0x300) == 0) {
    uVar1 = uVar1 | 0x20000;
  }
  else if ((param_1 & 0x300) == 0x200) {
    uVar1 = uVar1 | 0x10000;
  }
  if ((param_1 & 0x1000) != 0) {
    uVar1 = uVar1 | 0x40000;
  }
  return uVar1;
}
#endif


/* ---- 0x10008cc0  FUN_10008cc0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int FUN_10008cc0(void)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  uint in_stack_00000004;
  
  bVar3 = (in_stack_00000004 & 0x10) != 0;
  if ((in_stack_00000004 & 8) != 0) {
    bVar3 = bVar3 | 4;
  }
  if ((in_stack_00000004 & 4) != 0) {
    bVar3 = bVar3 | 8;
  }
  if ((in_stack_00000004 & 2) != 0) {
    bVar3 = bVar3 | 0x10;
  }
  if ((in_stack_00000004 & 1) != 0) {
    bVar3 = bVar3 | 0x20;
  }
  if ((in_stack_00000004 & 0x80000) != 0) {
    bVar3 = bVar3 | 2;
  }
  uVar1 = (uint)bVar3;
  uVar2 = in_stack_00000004 & 0x300;
  if (uVar2 < 0x101) {
    if (uVar2 == 0x100) {
      uVar1 = bVar3 | 0x400;
    }
  }
  else if (uVar2 == 0x200) {
    uVar1 = (uint)CONCAT11(8,bVar3);
  }
  else if (uVar2 == 0x300) {
    uVar1 = (uint)CONCAT11(0xc,bVar3);
  }
  if ((in_stack_00000004 & 0x30000) == 0) {
    uVar1 = uVar1 | 0x300;
  }
  else if ((in_stack_00000004 & 0x30000) == 0x10000) {
    uVar1 = uVar1 | 0x200;
  }
  if ((in_stack_00000004 & 0x40000) != 0) {
    uVar1 = uVar1 | 0x1000;
  }
  return uVar1;
}
#endif


/* ---- 0x10008d50  FUN_10008d50 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_10008d50(int param_1,uint param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  int iVar2;
  #define uStack_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar2 = param_1;
  if (param_1 + 1U < 0x101) {
    return *(ushort *)(_DAT_10010ad8 + param_1 * 2) & param_2;
  }
  if ((*(byte *)(_DAT_10010ad8 + 1 + (param_1 >> 8 & 0xffU) * 2) & 0x80) == 0) {
    PIECE(param_1,0,2) = (ushort)(byte)param_1;
    uVar1 = 1;
  }
  else {
    PIECE(param_1,0,2) = CONCAT11((byte)param_1,(char)((uint)param_1 >> 8));
    PIECE(param_1,3,1) = SUB41(iVar2,3);
    PIECE(param_1,0,3) = (uint3)(ushort)param_1;
    uVar1 = 2;
  }
  iVar2 = FUN_1000af40(1,&param_1,uVar1,&uStack_4,0,0,1);
  if (iVar2 == 0) {
    return 0;
  }
  return uStack_4 & 0xffff & param_2;
}
#undef uStack_4

#endif


/* ---- 0x10008df0  FUN_10008df0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_10008df0(int param_1,int param_2)

{
  byte bVar1;
  int *piVar2;
  int iVar3;
  
  bVar1 = (byte)(param_2 >> 0x1f);
  iVar3 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  if ((*(uint *)(param_1 + iVar3 * 4) &
      ~(-1 << (0x1f - ((((byte)param_2 ^ bVar1) - bVar1 & 0x1f ^ bVar1) - bVar1) & 0x1f))) != 0) {
    return 0;
  }
  iVar3 = iVar3 + 1;
  if (iVar3 < 3) {
    piVar2 = (int *)(param_1 + iVar3 * 4);
    do {
      if (*piVar2 != 0) {
        return 0;
      }
      iVar3 = iVar3 + 1;
      piVar2 = piVar2 + 1;
    } while (iVar3 < 3);
    return 1;
  }
  return 1;
}
#endif


/* ---- 0x10008e60  FUN_10008e60 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int FUN_10008e60(void)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  int in_stack_00000004;
  int in_stack_00000008;
  
  bVar1 = (byte)(in_stack_00000008 >> 0x1f);
  iVar3 = (int)(in_stack_00000008 + (in_stack_00000008 >> 0x1f & 0x1fU)) >> 5;
  iVar2 = FUN_1000b830(*(undefined4 *)(in_stack_00000004 + iVar3 * 4),
                       1 << (0x1f - ((((byte)in_stack_00000008 ^ bVar1) - bVar1 & 0x1f ^ bVar1) -
                                    bVar1) & 0x1f),in_stack_00000004 + iVar3 * 4);
  iVar3 = iVar3 + -1;
  if (-1 < iVar3) {
    puVar4 = (undefined4 *)(in_stack_00000004 + iVar3 * 4);
    do {
      if (iVar2 == 0) {
        return 0;
      }
      iVar2 = FUN_1000b830(*puVar4,1,puVar4);
      iVar3 = iVar3 + -1;
      puVar4 = puVar4 + -1;
    } while (-1 < iVar3);
  }
  return iVar2;
}
#endif


/* ---- 0x10008ed0  FUN_10008ed0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_10008ed0(int param_1,int param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  byte bVar2;
  int iVar3;
  undefined4 *puVar4;
  #define iStack_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  iStack_4 = 0;
  bVar2 = (byte)(param_2 >> 0x1f);
  bVar2 = 0x1f - ((((byte)param_2 ^ bVar2) - bVar2 & 0x1f ^ bVar2) - bVar2);
  iVar3 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  if (((*(uint *)(param_1 + iVar3 * 4) & 1 << (bVar2 & 0x1f)) != 0) &&
     (iVar1 = FUN_10008df0(param_1,param_2 + 1), iVar1 == 0)) {
    iStack_4 = FUN_10008e60();
  }
  *(uint *)(param_1 + iVar3 * 4) = *(uint *)(param_1 + iVar3 * 4) & -1 << (bVar2 & 0x1f);
  iVar3 = iVar3 + 1;
  if (iVar3 < 3) {
    puVar4 = (undefined4 *)(param_1 + iVar3 * 4);
    for (iVar1 = 3 - iVar3; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
  }
  return iStack_4;
}
#undef iStack_4

#endif


/* ---- 0x10008f70  FUN_10008f70 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10008f70(int param_1,undefined4 *param_2)

{
  int iVar1;
  
  param_1 = param_1 - (int)param_2;
  iVar1 = 3;
  do {
    *(undefined4 *)((int)param_2 + param_1) = *param_2;
    param_2 = param_2 + 1;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}
#endif


/* ---- 0x10008f90  FUN_10008f90 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10008f90(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  return;
}
#endif


/* ---- 0x10008fa0  FUN_10008fa0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_10008fa0(int *param_1)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    if (*param_1 != 0) {
      return 0;
    }
    iVar1 = iVar1 + 1;
    param_1 = param_1 + 1;
  } while (iVar1 < 3);
  return 1;
}
#endif


/* ---- 0x10008fc0  FUN_10008fc0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10008fc0(uint *param_1,int param_2)

{
  int iVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  int iVar7;
  
  iVar1 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  bVar2 = (byte)(param_2 >> 0x1f);
  uVar5 = 0;
  bVar2 = (((byte)param_2 ^ bVar2) - bVar2 & 0x1f ^ bVar2) - bVar2;
  param_2 = 3;
  puVar6 = param_1;
  do {
    uVar4 = *puVar6 >> (bVar2 & 0x1f) | uVar5;
    uVar5 = (~(-1 << (bVar2 & 0x1f)) & *puVar6) << (0x20 - bVar2 & 0x1f);
    *puVar6 = uVar4;
    param_2 = param_2 + -1;
    puVar6 = puVar6 + 1;
  } while (param_2 != 0);
  iVar7 = 2;
  iVar3 = 8;
  do {
    if (iVar7 < iVar1) {
      *(undefined4 *)((int)param_1 + iVar3) = 0;
    }
    else {
      *(undefined4 *)((int)param_1 + iVar3) = *(undefined4 *)((int)param_1 + iVar3 + iVar1 * -4);
    }
    iVar7 = iVar7 + -1;
    iVar3 = iVar3 + -4;
  } while (-1 < iVar3);
  return;
}
#endif


/* ---- 0x10009080  FUN_10009080 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_10009080(ushort *param_1,uint *param_2,int *param_3)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  #define uStack_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define uStack_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define iStack_10 (*(int *)(_frame + (0x30 - 0x10)))
  #define auStack_c (*(undefined1 (*)[12])(_frame + (0x30 - 0xc)))
  
  uVar1 = param_1[5];
  uStack_14 = *(uint *)(param_1 + 1);
  uStack_18 = *(uint *)(param_1 + 3);
  uVar4 = uVar1 & 0x7fff;
  iVar5 = uVar4 - 0x3fff;
  iStack_10 = (uint)*param_1 << 0x10;
  if (iVar5 == -0x3fff) {
    iVar5 = 0;
    iVar2 = FUN_10008fa0(&uStack_18);
    if (iVar2 == 0) {
      FUN_10008f90(&uStack_18);
      uVar3 = 2;
      goto LAB_10009201;
    }
  }
  else {
    FUN_10008f70(auStack_c,&uStack_18);
    iVar2 = FUN_10008ed0(&uStack_18,param_3[2]);
    if (iVar2 != 0) {
      iVar5 = uVar4 - 0x3ffe;
    }
    iVar2 = param_3[1];
    if (iVar5 < iVar2 - param_3[2]) {
      FUN_10008f90(&uStack_18);
      iVar5 = 0;
      uVar3 = 2;
      goto LAB_10009201;
    }
    if (iVar5 <= iVar2) {
      FUN_10008f70(&uStack_18,auStack_c);
      FUN_10008fc0(&uStack_18,iVar2 - iVar5);
      FUN_10008ed0(&uStack_18,param_3[2]);
      FUN_10008fc0(&uStack_18,param_3[3] + 1);
      iVar5 = 0;
      uVar3 = 2;
      goto LAB_10009201;
    }
    if (*param_3 <= iVar5) {
      FUN_10008f90(&uStack_18);
      uStack_18 = uStack_18 | 0x80000000;
      FUN_10008fc0(&uStack_18,param_3[3]);
      iVar5 = param_3[5] + *param_3;
      uVar3 = 1;
      goto LAB_10009201;
    }
    iVar5 = param_3[5] + iVar5;
    uStack_18 = uStack_18 & 0x7fffffff;
    FUN_10008fc0(&uStack_18,param_3[3]);
  }
  uVar3 = 0;
LAB_10009201:
  uStack_18 = iVar5 << (0x1fU - (char)param_3[3] & 0x1f) |
              -(uint)((uVar1 & 0x8000) != 0) & 0x80000000 | uStack_18;
  if (param_3[4] == 0x40) {
    param_2[1] = uStack_18;
    *param_2 = uStack_14;
    return uVar3;
  }
  if (param_3[4] == 0x20) {
    *param_2 = uStack_18;
  }
  return uVar3;
}
#undef auStack_c
#undef iStack_10
#undef uStack_14
#undef uStack_18

#endif


/* ---- 0x10009250  FUN_10009250 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10009250(undefined4 param_1,undefined4 param_2)

{
  FUN_10009080(param_1,param_2,IMG_ADDR(0x10010ce8));
  return;
}
#endif


/* ---- 0x10009270  FUN_10009270 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10009270(undefined4 param_1,undefined4 param_2)

{
  FUN_10009080(param_1,param_2,IMG_ADDR(0x10010d00));
  return;
}
#endif


/* ---- 0x10009290  FUN_10009290 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10009290(undefined4 param_1,undefined4 param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define auStack_c (*(undefined1 (*)[12])(_frame + (0x20 - 0xc)))
  
  FUN_1000ba30(auStack_c,&param_2,param_2,0,0,0,0);
  FUN_10009250(auStack_c,param_1);
  return;
}
#undef auStack_c

#endif


/* ---- 0x100092d0  FUN_100092d0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_100092d0(undefined4 param_1,undefined4 param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define auStack_c (*(undefined1 (*)[12])(_frame + (0x20 - 0xc)))
  
  FUN_1000ba30(auStack_c,&param_2,param_2,0,0,0,0);
  FUN_10009270(auStack_c,param_1);
  return;
}
#undef auStack_c

#endif


/* ---- 0x10009310  FUN_10009310 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10009310(char *param_1,int param_2,int param_3)

{
  char *pcVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  int iVar6;
  char *pcVar7;
  
  pcVar5 = *(char **)(param_3 + 0xc);
  pcVar7 = param_1 + 1;
  *param_1 = '0';
  pcVar1 = pcVar7;
  iVar6 = param_2;
  if (0 < param_2) {
    do {
      cVar2 = *pcVar5;
      if (cVar2 == '\0') {
        cVar2 = '0';
      }
      else {
        pcVar5 = pcVar5 + 1;
      }
      *pcVar1 = cVar2;
      pcVar1 = pcVar1 + 1;
      iVar6 = iVar6 + -1;
      param_2 = param_2 + -1;
    } while (param_2 != 0);
  }
  *pcVar1 = '\0';
  if ((-1 < iVar6) && ('4' < *pcVar5)) {
    cVar2 = pcVar1[-1];
    while (pcVar5 = pcVar1 + -1, cVar2 == '9') {
      *pcVar5 = '0';
      cVar2 = pcVar1[-2];
      pcVar1 = pcVar5;
    }
    *pcVar5 = *pcVar5 + '\x01';
  }
  if (*param_1 == '1') {
    *(int *)(param_3 + 4) = *(int *)(param_3 + 4) + 1;
    return;
  }
  uVar3 = 0xffffffff;
  do {
    pcVar5 = pcVar7;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar5 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar5;
  } while (cVar2 != '\0');
  uVar3 = ~uVar3;
  pcVar7 = pcVar5 + -uVar3;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)param_1 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    param_1 = param_1 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *param_1 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    param_1 = param_1 + 1;
  }
  return;
}
#endif


/* ---- 0x100093b0  FUN_100093b0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int * FUN_100093b0(undefined4 param_1,undefined4 param_2,int *param_3,char *param_4)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  #define uStack_28 (*(undefined4 *)(_frame + (0x40 - 0x28)))
  #define uStack_24 (*(undefined4 *)(_frame + (0x40 - 0x24)))
  #define uStack_20 (*(undefined2 *)(_frame + (0x40 - 0x20)))
  #define sStack_1c (*(short *)(_frame + (0x40 - 0x1c)))
  #define cStack_1a (*(char *)(_frame + (0x40 - 0x1a)))
  #define acStack_18 (*(char (*)[24])(_frame + (0x40 - 0x18)))
  
  FUN_10009440(&uStack_28,&param_1);
  iVar2 = FUN_1000c1c0(uStack_28,uStack_24,uStack_20,0x11,0,&sStack_1c);
  param_3[2] = iVar2;
  param_3[1] = (int)sStack_1c;
  *param_3 = (int)cStack_1a;
  uVar3 = 0xffffffff;
  pcVar5 = acStack_18;
  do {
    pcVar6 = pcVar5;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar6 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar6;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar5 = pcVar6 + -uVar3;
  pcVar6 = param_4;
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
  param_3[3] = (int)param_4;
  return param_3;
}
#undef acStack_18
#undef cStack_1a
#undef sStack_1c
#undef uStack_20
#undef uStack_24
#undef uStack_28

#endif


/* ---- 0x10009440  FUN_10009440 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10009440(uint *param_1,uint *param_2)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  ushort uVar5;
  int iVar6;
  
  uVar4 = 0x80000000;
  uVar1 = *(ushort *)((int)param_2 + 6);
  uVar2 = *param_2;
  uVar3 = (uVar1 & 0x7ff0) >> 4;
  if (uVar3 == 0) {
    uVar4 = 0;
    if (((param_2[1] & 0xfffff) == 0) && (uVar2 == 0)) {
      param_1[1] = 0;
      *param_1 = 0;
      *(undefined2 *)(param_1 + 2) = 0;
      return;
    }
    iVar6 = 0x3c01;
  }
  else if (uVar3 == 0x7ff) {
    iVar6 = 0x7fff;
  }
  else {
    iVar6 = uVar3 + 0x3c00;
  }
  uVar5 = (ushort)iVar6;
  uVar3 = uVar2 >> 0x15 | (param_2[1] & 0xfffff) << 0xb | uVar4;
  param_1[1] = uVar3;
  *param_1 = uVar2 << 0xb;
  for (; uVar4 == 0; uVar4 = uVar4 & 0x80000000) {
    uVar4 = uVar3 * 2;
    uVar3 = *param_1 >> 0x1f | uVar4;
    iVar6 = iVar6 + 0xffff;
    uVar5 = (ushort)iVar6;
    param_1[1] = uVar3;
    *param_1 = *param_1 * 2;
  }
  *(ushort *)(param_1 + 2) = uVar5 | uVar1 & 0x8000;
  return;
}
#endif


/* ---- 0x10009500  FUN_10009500 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10009500(void)

{
  FUN_10006120(2);
  return;
}
#endif


/* ---- 0x10009510  FUN_10009510 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int FUN_10009510(void)

{
  int in_EAX;
  int iVar1;
  undefined4 in_ECX;
  int in_stack_00000004;
  
  if (in_stack_00000004 != 0) {
    FUN_10006810(9);
    iVar1 = ((code *)FUN_1000b320)();
    if (iVar1 != 0) {
      FUN_1000b380(in_ECX,in_stack_00000004,iVar1);
      iVar1 = FUN_10006890();
      return iVar1;
    }
    FUN_10006890();
    in_EAX = HeapFree(_DAT_100159c4,0);
  }
  return in_EAX;
}
#endif


/* ---- 0x10009580  FUN_10009580 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined4 FUN_10009580(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = FUN_100095a0(param_1,_DAT_100148b4);
  return uVar1;
}
#endif


/* ---- 0x100095a0  FUN_100095a0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_100095a0(uint param_1,int param_2)

{
  int iVar1;
  
  if (param_1 < 0xffffffe1) {
    if (param_1 == 0) {
      param_1 = 1;
    }
    do {
      if (param_1 < 0xffffffe1) {
        iVar1 = FUN_100095f0(param_1);
      }
      else {
        iVar1 = 0;
      }
      if (iVar1 != 0) {
        return iVar1;
      }
      if (param_2 == 0) {
        return 0;
      }
      iVar1 = FUN_1000c550(param_1);
    } while (iVar1 != 0);
  }
  return 0;
}
#endif


/* ---- 0x100095f0  FUN_100095f0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_100095f0(int param_1)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = param_1 + 0xfU & 0xfffffff0;
  if (uVar2 <= _DAT_100137cc) {
    FUN_10006810(9);
    iVar1 = FUN_1000b3e0(param_1 + 0xfU >> 4);
    FUN_10006890();
    if (iVar1 != 0) {
      return iVar1;
    }
  }
  iVar1 = HeapAlloc(_DAT_100159c4,0,uVar2);
  return iVar1;
}
#endif


/* ---- 0x10009650  FUN_10009650 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_10009650(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  
  if (_DAT_100159c0 == 0) {
    _DAT_100159c0 = 0x200;
  }
  else if (_DAT_100159c0 < 0x14) {
    _DAT_100159c0 = 0x14;
  }
  _DAT_100149a4 = FUN_1000ad00(_DAT_100159c0,4);
  if (_DAT_100149a4 == 0) {
    _DAT_100159c0 = 0x14;
    _DAT_100149a4 = FUN_1000ad00(0x14,4);
    if (_DAT_100149a4 == 0) {
      FUN_10006120(0x1a);
    }
  }
  iVar3 = 0;
  iVar1 = IMG_ADDR(0x10010d18);
  do {
    *(int *)(_DAT_100149a4 + iVar3) = iVar1;
    iVar1 = iVar1 + 0x20;
    iVar3 = iVar3 + 4;
  } while (iVar1 < 0x10010f98);
  uVar2 = 0;
  puVar4 = (undefined4 *)IMG_ADDR(0x10010d28);
  do {
    iVar1 = *(int *)(*(int *)(&DAT_100159e0 + ((int)uVar2 >> 5) * 4) + (uVar2 & 0x1f) * 0x24);
    if ((iVar1 == -1) || (iVar1 == 0)) {
      *puVar4 = 0xffffffff;
    }
    puVar4 = puVar4 + 8;
    uVar2 = uVar2 + 1;
  } while ((int)puVar4 < IMG_ADDR(0x10010d88));
  return;
}
#endif


/* ---- 0x10009710  FUN_10009710 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __stdcall FUN_10009710(int a1,int a2,int a3,int a4)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  uVar1 = ((code *)FUN_1000c6c0)();
  if (DAT_100144d0 == '\0') {
    return CONCAT31((int3)((uint)uVar1 >> 8),DAT_100144d0);
  }
  iVar3 = 0;
  FUN_10006810(2);
  iVar4 = 3;
  if (3 < _DAT_100159c0) {
    do {
      iVar2 = *(int *)(_DAT_100149a4 + iVar4 * 4);
      if (iVar2 != 0) {
        if (((*(byte *)(iVar2 + 0xc) & 0x83) != 0) && (iVar2 = FUN_1000d150(iVar2), iVar2 != -1)) {
          iVar3 = iVar3 + 1;
        }
        if (0x13 < iVar4) {
          DeleteCriticalSection(*(int *)(_DAT_100149a4 + iVar4 * 4) + 0x20);
          FUN_10009510();
          *(undefined4 *)(_DAT_100149a4 + iVar4 * 4) = 0;
        }
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < _DAT_100159c0);
  }
  FUN_10006890();
  return iVar3;
}
#endif


/* ---- 0x10009730  FUN_10009730 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_10009730(void)

{
  int iVar1;
  int iVar2;
  
  if (_DAT_10014484 == 0) {
    _DAT_1001387c = IMG_ADDR(0x100137d0);
    FUN_10009b60(_DAT_10014818);
    FUN_10009510();
    _DAT_10014818 = 0;
    return 0;
  }
  iVar1 = FUN_1000ad00(1,0xac);
  if (iVar1 == 0) {
    return 1;
  }
  iVar2 = FUN_100097e0(iVar1);
  if (iVar2 != 0) {
    FUN_10009b60(iVar1);
    FUN_10009510();
    return 1;
  }
  _DAT_1001387c = iVar1;
  FUN_10009b60(_DAT_10014818);
  FUN_10009510();
  _DAT_10014818 = iVar1;
  return 0;
}
#endif


/* ---- 0x100097e0  FUN_100097e0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_100097e0(int param_1)

{
  undefined2 uVar1;
  undefined2 uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  uint uVar21;
  uint uVar22;
  uint uVar23;
  uint uVar24;
  uint uVar25;
  uint uVar26;
  uint uVar27;
  uint uVar28;
  uint uVar29;
  uint uVar30;
  uint uVar31;
  uint uVar32;
  uint uVar33;
  uint uVar34;
  uint uVar35;
  uint uVar36;
  uint uVar37;
  uint uVar38;
  uint uVar39;
  uint uVar40;
  uint uVar41;
  uint uVar42;
  uint uVar43;
  uint uVar44;
  uint uVar45;
  
  uVar2 = _DAT_10014858;
  uVar1 = _DAT_10014856;
  if (param_1 == 0) {
    return 0xffffffff;
  }
  uVar3 = FUN_1000c790(1,_DAT_10014856,0x31,param_1 + 4);
  uVar4 = FUN_1000c790(1,uVar1,0x32,param_1 + 8);
  uVar5 = FUN_1000c790(1,uVar1,0x33,param_1 + 0xc);
  uVar6 = FUN_1000c790(1,uVar1,0x34,param_1 + 0x10);
  uVar7 = FUN_1000c790(1,uVar1,0x35,param_1 + 0x14);
  uVar8 = FUN_1000c790(1,uVar1,0x36,param_1 + 0x18);
  uVar9 = FUN_1000c790(1,uVar1,0x37,param_1);
  uVar10 = FUN_1000c790(1,uVar1,0x2a,param_1 + 0x20);
  uVar11 = FUN_1000c790(1,uVar1,0x2b,param_1 + 0x24);
  uVar12 = FUN_1000c790(1,uVar1,0x2c,param_1 + 0x28);
  uVar13 = FUN_1000c790(1,uVar1,0x2d,param_1 + 0x2c);
  uVar14 = FUN_1000c790(1,uVar1,0x2e,param_1 + 0x30);
  uVar15 = FUN_1000c790(1,uVar1,0x2f,param_1 + 0x34);
  uVar16 = FUN_1000c790(1,uVar1,0x30,param_1 + 0x1c);
  uVar17 = FUN_1000c790(1,uVar1,0x44,param_1 + 0x38);
  uVar18 = FUN_1000c790(1,uVar1,0x45,param_1 + 0x3c);
  uVar19 = FUN_1000c790(1,uVar1,0x46,param_1 + 0x40);
  uVar20 = FUN_1000c790(1,uVar1,0x47,param_1 + 0x44);
  uVar21 = FUN_1000c790(1,uVar1,0x48,param_1 + 0x48);
  uVar22 = FUN_1000c790(1,uVar1,0x49,param_1 + 0x4c);
  uVar23 = FUN_1000c790(1,uVar1,0x4a,param_1 + 0x50);
  uVar24 = FUN_1000c790(1,uVar1,0x4b,param_1 + 0x54);
  uVar25 = FUN_1000c790(1,uVar1,0x4c,param_1 + 0x58);
  uVar26 = FUN_1000c790(1,uVar1,0x4d,param_1 + 0x5c);
  uVar27 = FUN_1000c790(1,uVar1,0x4e,param_1 + 0x60);
  uVar28 = FUN_1000c790(1,uVar1,0x4f,param_1 + 100);
  uVar29 = FUN_1000c790(1,uVar1,0x38,param_1 + 0x68);
  uVar30 = FUN_1000c790(1,uVar1,0x39,param_1 + 0x6c);
  uVar31 = FUN_1000c790(1,uVar1,0x3a,param_1 + 0x70);
  uVar32 = FUN_1000c790(1,uVar1,0x3b,param_1 + 0x74);
  uVar33 = FUN_1000c790(1,uVar1,0x3c,param_1 + 0x78);
  uVar34 = FUN_1000c790(1,uVar1,0x3d,param_1 + 0x7c);
  uVar35 = FUN_1000c790(1,uVar1,0x3e,param_1 + 0x80);
  uVar36 = FUN_1000c790(1,uVar1,0x3f,param_1 + 0x84);
  uVar37 = FUN_1000c790(1,uVar1,0x40,param_1 + 0x88);
  uVar38 = FUN_1000c790(1,uVar1,0x41,param_1 + 0x8c);
  uVar39 = FUN_1000c790(1,uVar1,0x42,param_1 + 0x90);
  uVar40 = FUN_1000c790(1,uVar1,0x43,param_1 + 0x94);
  uVar41 = FUN_1000c790(1,uVar1,0x28,param_1 + 0x98);
  uVar42 = FUN_1000c790(1,uVar1,0x29,param_1 + 0x9c);
  uVar43 = FUN_1000c790(1,uVar2,0x1f,param_1 + 0xa0);
  uVar44 = FUN_1000c790(1,uVar2,0x20,param_1 + 0xa4);
  uVar45 = ((code *)FUN_10009da0)(uVar2,param_1);
  return uVar3 | uVar4 | uVar5 | uVar6 | uVar7 | uVar8 | uVar9 | uVar10 | uVar11 | uVar12 | uVar13 |
         uVar14 | uVar15 | uVar16 | uVar17 | uVar18 | uVar19 | uVar20 | uVar21 | uVar22 | uVar23 |
         uVar24 | uVar25 | uVar26 | uVar27 | uVar28 | uVar29 | uVar30 | uVar31 | uVar32 | uVar33 |
         uVar34 | uVar35 | uVar36 | uVar37 | uVar38 | uVar39 | uVar40 | uVar41 | uVar42 | uVar43 |
         uVar44 | uVar45;
}
#endif


/* ---- 0x10009b60  FUN_10009b60 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10009b60(int param_1)

{
  if (param_1 != 0) {
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
  }
  return;
}
#endif


/* ---- 0x10009da0  FUN_10009da0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint FUN_10009da0(undefined4 param_1,char *param_2,int param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char *pcVar1;
  char cVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  undefined1 *puVar7;
  char *pcVar8;
  char *pcVar9;
  int unaff_retaddr;
  #define uStack_8 (*(undefined4 *)(_frame + (0x20 - 0x8)))
  #define iStack_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  uVar3 = param_1;
  iStack_4 = 0;
  uStack_8 = 0;
  uVar4 = FUN_1000c790(0,param_1,0x23,&iStack_4);
  uVar5 = FUN_1000c790(0,uVar3,0x25,&uStack_8);
  uVar6 = FUN_1000c790(1,uVar3,0x1e,&param_1);
  uVar6 = uVar4 | uVar5 | uVar6;
  if (uVar6 != 0) {
    return uVar6;
  }
  puVar7 = (undefined1 *)FUN_10009580(0xd);
  *(undefined1 **)(param_3 + 0xa8) = puVar7;
  if (unaff_retaddr == 0) {
    *puVar7 = 0x68;
    pcVar8 = puVar7 + 1;
    if (iStack_4 == 0) goto LAB_10009e3c;
    *pcVar8 = 'h';
  }
  else {
    *puVar7 = 0x48;
    pcVar8 = puVar7 + 1;
    if (iStack_4 == 0) goto LAB_10009e3c;
    *pcVar8 = 'H';
  }
  pcVar8 = puVar7 + 2;
LAB_10009e3c:
  cVar2 = *param_2;
  pcVar9 = param_2;
  while (cVar2 != '\0') {
    *pcVar8 = cVar2;
    pcVar1 = pcVar9 + 1;
    pcVar8 = pcVar8 + 1;
    pcVar9 = pcVar9 + 1;
    cVar2 = *pcVar1;
  }
  *pcVar8 = 'm';
  pcVar9 = pcVar8 + 1;
  if (iStack_4 != 0) {
    *pcVar9 = 'm';
    pcVar9 = pcVar8 + 2;
  }
  cVar2 = *param_2;
  pcVar8 = param_2;
  while (cVar2 != '\0') {
    *pcVar9 = cVar2;
    pcVar1 = pcVar8 + 1;
    pcVar9 = pcVar9 + 1;
    pcVar8 = pcVar8 + 1;
    cVar2 = *pcVar1;
  }
  *pcVar9 = 's';
  pcVar9[1] = 's';
  pcVar9[2] = '\0';
  FUN_10009510();
  return 0;
}
#undef iStack_4
#undef uStack_8

#endif


/* ---- 0x10009ea0  FUN_10009ea0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_10009ea0(void)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  uVar1 = _DAT_10014852;
  if (_DAT_10014480 == 0) {
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    _DAT_1001481c = 0;
    _DAT_10014820 = 0;
    _DAT_10014824 = 0;
    iVar2 = FUN_10009580(2);
    *_DAT_100138b8 = iVar2;
    if ((undefined2 *)*_DAT_100138b8 == (undefined2 *)0x0) {
      return 0xffffffff;
    }
    *(undefined2 *)*_DAT_100138b8 = 0x2e;
    iVar2 = FUN_10009580(2);
    _DAT_100138b8[1] = iVar2;
    if ((undefined1 *)_DAT_100138b8[1] == (undefined1 *)0x0) {
      return 0xffffffff;
    }
    *(undefined1 *)_DAT_100138b8[1] = 0;
    iVar2 = FUN_10009580(2);
    _DAT_100138b8[2] = iVar2;
    if ((undefined1 *)_DAT_100138b8[2] == (undefined1 *)0x0) {
      return 0xffffffff;
    }
    *(undefined1 *)_DAT_100138b8[2] = 0;
  }
  else {
    iVar2 = FUN_1000c790(1,_DAT_10014852,0xe,&DAT_1001481c);
    iVar3 = FUN_1000c790(1,uVar1,0xf,&DAT_10014820);
    iVar4 = FUN_1000c790(1,uVar1,0x10,&DAT_10014824);
    FUN_1000a2e0(_DAT_10014824);
    if ((iVar2 != 0 || iVar3 != 0) || iVar4 != 0) {
      FUN_10009510();
      FUN_10009510();
      FUN_10009510();
      _DAT_1001481c = 0;
      _DAT_10014820 = 0;
      _DAT_10014824 = 0;
      return 0xffffffff;
    }
    if (*_DAT_100138b8 != IMG_ADDR(0x10013880)) {
      FUN_10009510();
      FUN_10009510();
      FUN_10009510();
    }
    *_DAT_100138b8 = _DAT_1001481c;
    _DAT_100138b8[1] = _DAT_10014820;
    _DAT_100138b8[2] = _DAT_10014824;
  }
  _DAT_10010ad0 = 1;
  DAT_10010acc = *(undefined1 *)*_DAT_100138b8;
  return 0;
}
#endif


/* ---- 0x1000a0a0  FUN_1000a0a0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_1000a0a0(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  if (_DAT_1001447c == 0) {
    _DAT_10013888 = *_DAT_100138b8;
    _DAT_1001388c = _DAT_100138b8[1];
    _DAT_10013890 = _DAT_100138b8[2];
    _DAT_100138b8 = (undefined4 *)&DAT_10013888;
    FUN_1000a320(_DAT_10014828);
    FUN_10009510();
    _DAT_10014828 = (undefined4 *)0x0;
    return 0;
  }
  puVar1 = (undefined4 *)FUN_1000ad00(1,0x30);
  if (puVar1 == (undefined4 *)0x0) {
    return 1;
  }
  iVar2 = FUN_1000a190(puVar1);
  if (iVar2 != 0) {
    FUN_1000a320(puVar1);
    FUN_10009510();
    return 1;
  }
  *puVar1 = *_DAT_100138b8;
  puVar1[1] = _DAT_100138b8[1];
  puVar1[2] = _DAT_100138b8[2];
  _DAT_100138b8 = puVar1;
  FUN_1000a320(_DAT_10014828);
  FUN_10009510();
  _DAT_10014828 = puVar1;
  return 0;
}
#endif


/* ---- 0x1000a190  FUN_1000a190 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_1000a190(int param_1)

{
  undefined2 uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  
  uVar1 = _DAT_1001484c;
  if (param_1 == 0) {
    return 0xffffffff;
  }
  uVar2 = FUN_1000c790(1,_DAT_1001484c,0x15,param_1 + 0xc);
  uVar3 = FUN_1000c790(1,uVar1,0x14,param_1 + 0x10);
  uVar4 = FUN_1000c790(1,uVar1,0x16,param_1 + 0x14);
  uVar5 = FUN_1000c790(1,uVar1,0x17,param_1 + 0x18);
  uVar6 = FUN_1000c790(1,uVar1,0x18,(undefined4 *)(param_1 + 0x1c));
  FUN_1000a2e0(*(undefined4 *)(param_1 + 0x1c));
  uVar7 = FUN_1000c790(1,uVar1,0x50,param_1 + 0x20);
  uVar8 = FUN_1000c790(1,uVar1,0x51,param_1 + 0x24);
  uVar9 = FUN_1000c790(0,uVar1,0x1a,param_1 + 0x28);
  uVar10 = FUN_1000c790(0,uVar1,0x19,param_1 + 0x29);
  uVar11 = FUN_1000c790(0,uVar1,0x54,param_1 + 0x2a);
  uVar12 = FUN_1000c790(0,uVar1,0x55,param_1 + 0x2b);
  uVar13 = FUN_1000c790(0,uVar1,0x56,param_1 + 0x2c);
  uVar14 = FUN_1000c790(0,uVar1,0x57,param_1 + 0x2d);
  uVar15 = FUN_1000c790(0,uVar1,0x52,param_1 + 0x2e);
  uVar16 = FUN_1000c790(0,uVar1,0x53,param_1 + 0x2f);
  return uVar2 | uVar3 | uVar4 | uVar5 | uVar6 | uVar7 | uVar8 | uVar9 | uVar10 | uVar11 | uVar12 |
         uVar13 | uVar14 | uVar15 | uVar16;
}
#endif


/* ---- 0x1000a2e0  FUN_1000a2e0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_1000a2e0(char *param_1)

{
  char *pcVar1;
  char cVar2;
  char *pcVar3;
  
  cVar2 = *param_1;
  do {
    if (cVar2 == '\0') {
      return;
    }
    if ((cVar2 < '0') || ('9' < cVar2)) {
      pcVar3 = param_1;
      if (cVar2 != ';') goto LAB_1000a2f6;
      do {
        *pcVar3 = pcVar3[1];
        pcVar1 = pcVar3 + 1;
        pcVar3 = pcVar3 + 1;
      } while (*pcVar1 != '\0');
    }
    else {
      *param_1 = cVar2 + -0x30;
LAB_1000a2f6:
      param_1 = param_1 + 1;
    }
    cVar2 = *param_1;
  } while( true );
}
#endif


/* ---- 0x1000a320  FUN_1000a320 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_1000a320(int param_1)

{
  if ((param_1 != 0) && (*(int *)(param_1 + 0xc) != IMG_ADDR(0x100148d0))) {
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
    FUN_10009510();
  }
  return;
}
#endif


/* ---- 0x1000a390  FUN_1000a390 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_1000a390(void)

{
  unsigned char _frame[0x20];  /* Ghidra stack frame, see tools/frame_locals.py */
  byte *pbVar1;
  undefined2 *puVar2;
  int iVar3;
  undefined2 *puVar4;
  int iVar5;
  undefined2 *puVar6;
  uint uVar7;
  byte *pbVar8;
  undefined2 *puVar9;
  char unaff_retaddr;
  #define puStack_c (*(undefined2 **)(_frame + (0x20 - 0xc)))
  #define puStack_8 (*(undefined2 **)(_frame + (0x20 - 0x8)))
  #define uStack_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  if (_DAT_10014478 == 0) {
    _DAT_10010ad8 = (undefined2 *)IMG_ADDR(0x10010ae2);
    _DAT_10010adc = (undefined2 *)IMG_ADDR(0x10010ae2);
    FUN_10009510();
    FUN_10009510();
    _DAT_1001482c = (undefined2 *)0x0;
    _DAT_10014830 = (undefined2 *)0x0;
    return 0;
  }
  if ((_DAT_10014488 != 0) || (iVar3 = FUN_1000c790(0,_DAT_10014844,0xb,&DAT_10014488), iVar3 == 0))
  {
    puVar4 = (undefined2 *)FUN_10009580(0x202);
    iVar3 = FUN_10009580(0x202);
    iVar5 = FUN_10009580(0x101);
    puVar6 = (undefined2 *)FUN_10009580(0x202);
    if ((puVar4 != (undefined2 *)0x0) &&
       (((iVar3 != 0 && (iVar5 != 0)) && (puVar6 != (undefined2 *)0x0)))) {
      iVar3 = 0;
      do {
        *(char *)(iVar3 + iVar5) = (char)iVar3;
        iVar3 = iVar3 + 1;
      } while (iVar3 < 0x100);
      iVar3 = GetCPInfo(_DAT_10014488,&uStack_4);
      if ((iVar3 != 0) && (uStack_4 < 3)) {
        _DAT_10010ac8 = uStack_4 & 0xffff;
        if ((1 < _DAT_10010ac8) && (unaff_retaddr != '\0')) {
          pbVar8 = &STACK0X(0x00000003);
          do {
            if (*pbVar8 == 0) break;
            uVar7 = (uint)pbVar8[-1];
            if (uVar7 <= *pbVar8) {
              do {
                *(undefined1 *)(uVar7 + iVar5) = 0;
                uVar7 = uVar7 + 1;
              } while ((int)uVar7 <= (int)(uint)*pbVar8);
            }
            pbVar1 = pbVar8 + 1;
            pbVar8 = pbVar8 + 2;
          } while (*pbVar1 != 0);
        }
        puVar2 = puVar4 + 1;
        iVar3 = FUN_1000af40(1,iVar5,0x100,puVar2,0,0,0);
        if (iVar3 != 0) {
          *puVar4 = 0;
          iVar3 = 0;
          puVar9 = puVar6;
          do {
            *puVar9 = (short)iVar3;
            puVar9 = puVar9 + 1;
            iVar3 = iVar3 + 1;
          } while (iVar3 < 0x100);
          puVar9 = puStack_c + 1;
          iVar3 = ((code *)FUN_1000adb0)(1,puVar6,0x100,puVar9,0,0);
          if (iVar3 != 0) {
            *puStack_c = 0;
            if ((1 < (int)_DAT_10010ac8) && (unaff_retaddr != '\0')) {
              pbVar8 = &STACK0X(0x00000003);
              do {
                puVar4 = puStack_8;
                if (*pbVar8 == 0) break;
                uVar7 = (uint)pbVar8[-1];
                if (uVar7 <= *pbVar8) {
                  puVar6 = puStack_8 + uVar7 + 1;
                  do {
                    *puVar6 = 0x8000;
                    uVar7 = uVar7 + 1;
                    puVar6 = puVar6 + 1;
                  } while ((int)uVar7 <= (int)(uint)*pbVar8);
                }
                pbVar1 = pbVar8 + 1;
                pbVar8 = pbVar8 + 2;
              } while (*pbVar1 != 0);
            }
            _DAT_10010ad8 = puVar2;
            _DAT_10010adc = puVar9;
            if (_DAT_1001482c != (undefined2 *)0x0) {
              FUN_10009510();
            }
            _DAT_1001482c = puVar4;
            if (_DAT_10014830 != (undefined2 *)0x0) {
              FUN_10009510();
            }
            _DAT_10014830 = puStack_c;
            FUN_10009510();
            FUN_10009510();
            return 0;
          }
        }
      }
    }
  }
  FUN_10009510();
  FUN_10009510();
  FUN_10009510();
  FUN_10009510();
  return 1;
}
#undef puStack_8
#undef puStack_c
#undef uStack_4

#endif


/* ---- 0x1000a710  FUN_1000a710 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_1000a710(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,
                undefined4 param_5,undefined4 param_6,int param_7,int param_8)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 unaff_EBP;
  undefined4 unaff_EDI;
  uint uVar7;
  undefined4 uVar8;
  int iVar9;
  
  if (_DAT_10014884 == 0) {
    iVar1 = LCMapStringW(0,0x100,&UNK_1000ead0,1,0,0);
    if (iVar1 == 0) {
      iVar1 = LCMapStringA(0,0x100,&UNK_1000eacc,1,0,0);
      if (iVar1 == 0) {
        return 0;
      }
      _DAT_10014884 = 2;
    }
    else {
      _DAT_10014884 = 1;
    }
  }
  if (0 < param_4) {
    param_4 = FUN_1000a940(param_3,param_4);
  }
  if (_DAT_10014884 == 2) {
    iVar1 = LCMapStringA(param_1,param_2,param_3,param_4,param_5,param_6);
    return iVar1;
  }
  if (_DAT_10014884 != 1) {
    return _DAT_10014884;
  }
  if (param_7 == 0) {
    param_7 = _DAT_10014488;
  }
  iVar9 = 0;
  uVar8 = 0;
  uVar6 = (-(uint)(param_8 != 0) & 8) + 1;
  iVar1 = param_4;
  iVar2 = MultiByteToWideChar(param_7,uVar6,param_3,param_4,0);
  if (iVar2 == 0) {
    return 0;
  }
  iVar3 = FUN_10009580(iVar2 * 2);
  if (iVar3 == 0) {
    return 0;
  }
  iVar5 = iVar2;
  iVar4 = MultiByteToWideChar(param_7,1,unaff_EBP,param_4,iVar3,iVar2);
  if ((iVar4 != 0) && (uVar7 = uVar6, iVar4 = LCMapStringW(iVar5,uVar6,iVar3,iVar2,0,0), iVar4 != 0)
     ) {
    if ((uVar6 & 0x400) == 0) {
      iVar5 = FUN_10009580(iVar4 * 2);
      if ((iVar5 == 0) || (iVar2 = LCMapStringW(uVar7,uVar6,iVar3,iVar2,iVar5,iVar4), iVar2 == 0))
      goto LAB_1000a918;
      if (iVar9 == 0) {
        iVar4 = WideCharToMultiByte(unaff_EDI,0x220,iVar1,iVar4,0,0,0,0);
        iVar1 = iVar4;
      }
      else {
        iVar4 = WideCharToMultiByte(unaff_EDI,0x220,iVar1,iVar4,iVar5,iVar9,0,0);
        iVar1 = iVar4;
      }
    }
    else {
      if (iVar9 == 0) goto LAB_1000a87f;
      if (iVar9 < iVar4) goto LAB_1000a918;
      iVar1 = LCMapStringW(iVar5,uVar6,iVar3,iVar2,uVar8,iVar9);
    }
    if (iVar1 != 0) {
LAB_1000a87f:
      FUN_10009510();
      FUN_10009510();
      return iVar4;
    }
  }
LAB_1000a918:
  FUN_10009510();
  FUN_10009510();
  return 0;
}
#endif


/* ---- 0x1000a940  FUN_1000a940 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_1000a940(char *param_1,int param_2)

{
  char *pcVar1;
  int iVar2;
  
  iVar2 = param_2;
  for (pcVar1 = param_1; (iVar2 != 0 && (iVar2 = iVar2 + -1, *pcVar1 != '\0')); pcVar1 = pcVar1 + 1)
  {
  }
  if (*pcVar1 != '\0') {
    return param_2;
  }
  return (int)pcVar1 - (int)param_1;
}
#endif


/* ---- 0x1000a970  FUN_1000a970 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_1000a970(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  bool bVar2;
  
  InterlockedIncrement(IMG_ADDR(0x10015af0));
  bVar2 = _DAT_10015aec != 0;
  if (bVar2) {
    InterlockedDecrement(IMG_ADDR(0x10015af0));
    FUN_10006810(0x13);
  }
  uVar1 = FUN_1000a9f0(param_1,param_2,param_3);
  if (!bVar2) {
    InterlockedDecrement(IMG_ADDR(0x10015af0));
    return uVar1;
  }
  FUN_10006890();
  return uVar1;
}
#endif


/* ---- 0x1000a9f0  FUN_1000a9f0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_1000a9f0(ushort *param_1,byte *param_2,uint param_3)

{
  byte bVar1;
  int iVar2;
  undefined4 *puVar3;
  
  if ((param_2 != (byte *)0x0) && (param_3 != 0)) {
    bVar1 = *param_2;
    if (bVar1 != 0) {
      if (_DAT_10014478 == 0) {
        if (param_1 == (ushort *)0x0) {
          return 1;
        }
        *param_1 = (ushort)bVar1;
        return 1;
      }
      if ((*(byte *)(_DAT_10010ad8 + 1 + (uint)bVar1 * 2) & 0x80) == 0) {
        iVar2 = MultiByteToWideChar(_DAT_10014488,9,param_2,1,param_1,param_1 != (ushort *)0x0);
        if (iVar2 != 0) {
          return 1;
        }
      }
      else {
        if (((1 < (int)_DAT_10010ac8) && ((int)_DAT_10010ac8 <= (int)param_3)) &&
           (iVar2 = MultiByteToWideChar(_DAT_10014488,9,param_2,_DAT_10010ac8,param_1,
                                        param_1 != (ushort *)0x0), iVar2 != 0)) {
          return _DAT_10010ac8;
        }
        if (_DAT_10010ac8 <= param_3) {
          if (param_2[1] != 0) {
            return _DAT_10010ac8;
          }
          puVar3 = (undefined4 *)FUN_1000cad0();
          *puVar3 = 0x2a;
          return 0xffffffff;
        }
      }
      puVar3 = (undefined4 *)FUN_1000cad0();
      *puVar3 = 0x2a;
      return 0xffffffff;
    }
    if (param_1 != (ushort *)0x0) {
      *param_1 = 0;
      return 0;
    }
  }
  return 0;
}
#endif


/* ---- 0x1000aaf0  FUN_1000aaf0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_1000aaf0(int param_1)

{
  uint uVar1;
  
  if (1 < _DAT_10010ac8) {
    uVar1 = FUN_10008d50(param_1,8);
    return uVar1;
  }
  return *(byte *)(_DAT_10010ad8 + param_1 * 2) & 8;
}
#endif


/* ---- 0x1000ab20  FUN_1000ab20 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int __stdcall FUN_1000ab20(int a1,int a2,int a3,int a4)

{
  if (a4 == 0 && a2 == 0) {
    return a1 * a3;
  }
  return a1 * a3;
}
#endif


/* ---- 0x1000ab60  FUN_1000ab60 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int __fastcall FUN_1000ab60(byte param_1,int param_2)

{
  int in_EAX;
  
  if (0x3f < param_1) {
    return 0;
  }
  if (param_1 < 0x20) {
    return in_EAX << (param_1 & 0x1f);
  }
  return 0;
}
#endif


/* ---- 0x1000ab80  FUN_1000ab80 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint FUN_1000ab80(undefined4 *param_1)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  uVar2 = param_1[3];
  if (((uVar2 & 0x83) != 0) && ((uVar2 & 0x40) == 0)) {
    if ((uVar2 & 2) != 0) {
      param_1[3] = uVar2 | 0x20;
      return 0xffffffff;
    }
    param_1[3] = uVar2 | 1;
    if ((uVar2 & 0x10c) == 0) {
      ((code *)FUN_1000cda0)(param_1);
    }
    else {
      *param_1 = param_1[2];
    }
    iVar3 = FUN_1000caf0(param_1[4],param_1[2],param_1[6]);
    param_1[1] = iVar3;
    if ((iVar3 != 0) && (iVar3 != -1)) {
      if ((param_1[3] & 0x82) == 0) {
        uVar2 = param_1[4];
        if (uVar2 == 0xffffffff) {
          iVar4 = IMG_ADDR(0x10010910);
        }
        else {
          iVar4 = *(int *)(&DAT_100159e0 + ((int)uVar2 >> 5) * 4) + (uVar2 & 0x1f) * 0x24;
        }
        if ((*(byte *)(iVar4 + 4) & 0x82) == 0x82) {
          param_1[3] = param_1[3] | 0x2000;
        }
      }
      if (((param_1[6] == 0x200) && ((param_1[3] & 8) != 0)) && ((param_1[3] & 0x400) == 0)) {
        param_1[6] = 0x1000;
      }
      param_1[1] = iVar3 + -1;
      bVar1 = *(byte *)*param_1;
      *param_1 = (byte *)*param_1 + 1;
      return (uint)bVar1;
    }
    param_1[1] = 0;
    param_1[3] = param_1[3] | (-(uint)(iVar3 != 0) & 0x10) + 0x10;
  }
  return 0xffffffff;
}
#endif


/* ---- 0x1000ac70  FUN_1000ac70 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint FUN_1000ac70(uint param_1,int *param_2)

{
  uint uVar1;
  int iVar2;
  char *pcVar3;
  
  if ((param_1 != 0xffffffff) &&
     ((uVar1 = param_2[3], (uVar1 & 1) != 0 || (((uVar1 & 0x80) != 0 && ((uVar1 & 2) == 0)))))) {
    if (param_2[2] == 0) {
      ((code *)FUN_1000cda0)(param_2);
    }
    if (*param_2 == param_2[2]) {
      if (param_2[1] != 0) {
        return 0xffffffff;
      }
      *param_2 = *param_2 + 1;
    }
    if ((*(byte *)(param_2 + 3) & 0x40) == 0) {
      iVar2 = *param_2;
      *param_2 = iVar2 + -1;
      *(char *)(iVar2 + -1) = (char)param_1;
    }
    else {
      iVar2 = *param_2;
      pcVar3 = (char *)(iVar2 + -1);
      *param_2 = (int)pcVar3;
      if (*pcVar3 != (char)param_1) {
        *param_2 = iVar2;
        return 0xffffffff;
      }
    }
    param_2[1] = param_2[1] + 1;
    param_2[3] = param_2[3] & 0xffffffefU | 1;
    return param_1 & 0xff;
  }
  return 0xffffffff;
}
#endif


/* ---- 0x1000ad00  FUN_1000ad00 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * FUN_1000ad00(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  uVar3 = param_2 * param_1;
  if (uVar3 < 0xffffffe1) {
    if (uVar3 == 0) {
      uVar3 = 0x10;
    }
    else {
      uVar3 = uVar3 + 0xf & 0xfffffff0;
    }
  }
  do {
    puVar4 = (undefined4 *)0x0;
    if (uVar3 < 0xffffffe1) {
      if (_DAT_100137cc < uVar3) {
LAB_1000ad74:
        if (puVar4 != (undefined4 *)0x0) {
          return puVar4;
        }
      }
      else {
        FUN_10006810(9);
        puVar4 = (undefined4 *)FUN_1000b3e0(uVar3 >> 4);
        FUN_10006890();
        if (puVar4 != (undefined4 *)0x0) {
          puVar5 = puVar4;
          for (uVar2 = uVar3 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
            *puVar5 = 0;
            puVar5 = puVar5 + 1;
          }
          for (uVar2 = uVar3 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
            *(undefined1 *)puVar5 = 0;
            puVar5 = (undefined4 *)((int)puVar5 + 1);
          }
          goto LAB_1000ad74;
        }
      }
      puVar4 = (undefined4 *)HeapAlloc(_DAT_100159c4,8,uVar3);
    }
    if ((puVar4 != (undefined4 *)0x0) || (_DAT_100148b4 == 0)) {
      return puVar4;
    }
    iVar1 = FUN_1000c550(uVar3);
    if (iVar1 == 0) {
      return (undefined4 *)0x0;
    }
  } while( true );
}
#endif


/* ---- 0x1000adb0  FUN_1000adb0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_1000adb0(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,int param_5)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 unaff_EBP;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 uVar8;
  #define uStack_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  if (_DAT_10014888 == 0) {
    iVar1 = GetStringTypeW(1,&UNK_1000ead0,1,&uStack_4);
    if (iVar1 == 0) {
      iVar1 = GetStringTypeA(0,1,&UNK_1000eacc,1,&uStack_4);
      if (iVar1 == 0) {
        return 0;
      }
      _DAT_10014888 = 2;
    }
    else {
      _DAT_10014888 = 1;
    }
  }
  if (_DAT_10014888 != 1) {
    iVar1 = _DAT_10014888;
    if (_DAT_10014888 == 2) {
      uStack_4 = 0;
      if (param_5 == 0) {
        param_5 = _DAT_10014488;
      }
      uVar8 = 0;
      iVar7 = 0;
      uVar6 = 0x220;
      iVar2 = WideCharToMultiByte(param_5,0x220,param_2,param_3,0,0,0,0);
      if (iVar2 == 0) {
        return 0;
      }
      iVar3 = FUN_1000ad00(1,iVar2);
      if (iVar3 == 0) {
        return 0;
      }
      uVar5 = 0;
      iVar1 = iVar3;
      iVar4 = WideCharToMultiByte(unaff_EBP,0x220,uVar8,param_3,iVar3,iVar2,0,0);
      if ((iVar4 != 0) && (iVar4 = FUN_10009580(iVar2 * 2 + 2), iVar4 != 0)) {
        if (iVar7 == 0) {
          iVar7 = _DAT_10014478;
        }
        param_3 = param_3 * 2;
        *(undefined2 *)(iVar4 + param_3) = 0xffff;
        *(undefined2 *)(iVar4 + -2 + param_3) = 0xffff;
        iVar1 = GetStringTypeA(iVar7,uVar5,iVar3,iVar2,iVar4);
        if ((*(short *)(iVar4 + -2 + param_3) == -1) || (*(short *)(iVar4 + param_3) != -1)) {
          iVar1 = 0;
        }
        else {
          msvc_memmove(uVar6,iVar4,param_3);
        }
      }
      FUN_10009510();
      FUN_10009510();
    }
    return iVar1;
  }
  iVar1 = GetStringTypeW(param_1,param_2,param_3,param_4);
  return iVar1;
}
#undef uStack_4

#endif


/* ---- 0x1000af40  FUN_1000af40 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_1000af40(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                int param_5,int param_6,int param_7)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  undefined4 unaff_EBX;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  int unaff_retaddr;
  #define auStack_2 (*(undefined1 (*)[2])(_frame + (0x20 - 0x2)))
  
  if (_DAT_1001488c == 0) {
    iVar1 = GetStringTypeW(1,&UNK_1000ead0,1,auStack_2);
    if (iVar1 == 0) {
      iVar1 = GetStringTypeA(0,1,&UNK_1000eacc,1,auStack_2);
      if (iVar1 == 0) {
        return 0;
      }
      _DAT_1001488c = 2;
    }
    else {
      _DAT_1001488c = 1;
    }
  }
  if (_DAT_1001488c == 2) {
    if (param_6 == 0) {
      param_6 = _DAT_10014478;
    }
    iVar1 = GetStringTypeA(param_6,param_1,param_2,param_3,param_4);
    return iVar1;
  }
  iVar1 = _DAT_1001488c;
  if (_DAT_1001488c == 1) {
    if (param_5 == 0) {
      param_5 = _DAT_10014488;
    }
    iVar1 = MultiByteToWideChar(param_5,(-(param_7 != 0) & 8U) + 1,param_2,param_3,0,0);
    if (iVar1 != 0) {
      iVar2 = FUN_1000ad00(2,iVar1);
      if (iVar2 != 0) {
        iVar1 = MultiByteToWideChar(param_5,1,unaff_ESI,param_3,iVar2,iVar1);
        if (iVar1 != 0) {
          iVar1 = GetStringTypeW(unaff_EDI,iVar2,iVar1,unaff_EBX);
          FUN_10009510();
          return iVar1;
        }
      }
    }
    FUN_10009510();
    iVar1 = unaff_retaddr;
  }
  return iVar1;
}
#undef auStack_2

#endif


/* ---- 0x1000b080  FUN_1000b080 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * FUN_1000b080(void)

{
  bool bVar1;
  undefined4 *puVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  if (_DAT_100117b8 == -1) {
    puVar5 = (undefined4 *)&DAT_100117a8;
  }
  else {
    puVar5 = (undefined4 *)HeapAlloc(_DAT_100159c4,0,0x2020);
    if (puVar5 == (undefined4 *)0x0) {
      return (undefined4 *)0x0;
    }
  }
  puVar2 = (undefined4 *)VirtualAlloc(0,0x400000,0x2000,4);
  if (puVar2 != (undefined4 *)0x0) {
    iVar3 = VirtualAlloc(puVar2,0x10000,0x1000,4);
    if (iVar3 != 0) {
      if (puVar5 == (undefined4 *)&DAT_100117a8) {
        if (_DAT_100117a8 == (undefined *)0x0) {
          _DAT_100117a8 = &DAT_100117a8;
        }
        if (_DAT_100117ac == (undefined4 *)0x0) {
          _DAT_100117ac = (undefined4 *)&DAT_100117a8;
        }
      }
      else {
        *puVar5 = &DAT_100117a8;
        puVar5[1] = _DAT_100117ac;
        _DAT_100117ac = puVar5;
        *(undefined4 **)puVar5[1] = puVar5;
      }
      puVar5[5] = puVar2 + 0x100000;
      puVar5[4] = puVar2;
      puVar5[2] = puVar5 + 6;
      puVar5[3] = puVar5 + 0x26;
      iVar3 = 0;
      piVar4 = puVar5 + 6;
      do {
        bVar1 = 0xf < iVar3;
        iVar3 = iVar3 + 1;
        *piVar4 = (bVar1 - 1 & 0xf1) - 1;
        piVar4[1] = 0xf1;
        piVar4 = piVar4 + 2;
      } while (iVar3 < 0x400);
      puVar6 = puVar2;
      for (iVar3 = 0x4000; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar6 = 0;
        puVar6 = puVar6 + 1;
      }
      if (puVar2 < (undefined4 *)(puVar5[4] + 0x10000)) {
        do {
          puVar2[1] = 0xf0;
          *puVar2 = puVar2 + 2;
          *(undefined1 *)(puVar2 + 0x3e) = 0xff;
          puVar2 = puVar2 + 0x400;
        } while (puVar2 < (undefined4 *)(puVar5[4] + 0x10000));
      }
      return puVar5;
    }
    VirtualFree(puVar2,0,0x8000);
  }
  if (puVar5 != (undefined4 *)&DAT_100117a8) {
    HeapFree(_DAT_100159c4,0,puVar5);
  }
  return (undefined4 *)0x0;
}
#endif


/* ---- 0x1000b1f0  FUN_1000b1f0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1000b1f0(int *param_1)

{
  VirtualFree(param_1[4],0,0x8000);
  if (_DAT_100137c8 == param_1) {
    _DAT_100137c8 = (int *)param_1[1];
  }
  if (param_1 != (int *)&DAT_100117a8) {
    *(int *)param_1[1] = *param_1;
    *(int *)(*param_1 + 4) = param_1[1];
    HeapFree(_DAT_100159c4,0,param_1);
    return;
  }
  _DAT_100117b8 = 0xffffffff;
  return;
}
#endif


/* ---- 0x1000b250  FUN_1000b250 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1000b250(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = _DAT_100117ac;
  do {
    iVar3 = iVar5;
    if (*(int *)(iVar5 + 0x10) != -1) {
      iVar4 = 0;
      piVar2 = (int *)(iVar5 + 0x2010);
      iVar3 = 0x3ff000;
      do {
        if (*piVar2 == 0xf0) {
          iVar1 = VirtualFree(*(int *)(iVar5 + 0x10) + iVar3,0x1000,0x4000);
          if (iVar1 != 0) {
            *piVar2 = -1;
            _DAT_10014890 = _DAT_10014890 + -1;
            if ((*(int **)(iVar5 + 0xc) == (int *)0x0) || (piVar2 < *(int **)(iVar5 + 0xc))) {
              *(int **)(iVar5 + 0xc) = piVar2;
            }
            iVar4 = iVar4 + 1;
            param_1 = param_1 + -1;
            if (param_1 == 0) break;
          }
        }
        iVar3 = iVar3 + -0x1000;
        piVar2 = piVar2 + -2;
      } while (-1 < iVar3);
      iVar3 = *(int *)(iVar5 + 4);
      if ((iVar4 != 0) && (*(int *)(iVar5 + 0x18) == -1)) {
        iVar4 = 1;
        piVar2 = (int *)(iVar5 + 0x20);
        do {
          if (*piVar2 != -1) break;
          iVar4 = iVar4 + 1;
          piVar2 = piVar2 + 2;
        } while (iVar4 < 0x400);
        if (iVar4 == 0x400) {
          FUN_1000b1f0(iVar5);
        }
      }
    }
    if ((iVar3 == _DAT_100117ac) || (iVar5 = iVar3, param_1 < 1)) {
      return;
    }
  } while( true );
}
#endif


/* ---- 0x1000b320  FUN_1000b320 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_1000b320(uint param_1,undefined4 *param_2,uint *param_3)

{
  undefined4 *puVar1;
  uint uVar2;
  
  puVar1 = (undefined4 *)&DAT_100117a8;
  while ((param_1 <= (uint)puVar1[4] || ((uint)puVar1[5] <= param_1))) {
    puVar1 = (undefined4 *)*puVar1;
    if (puVar1 == (undefined4 *)&DAT_100117a8) {
      return 0;
    }
  }
  if ((param_1 & 0xf) != 0) {
    return 0;
  }
  if ((param_1 & 0xfff) < 0x100) {
    return 0;
  }
  *param_2 = puVar1;
  uVar2 = param_1 & 0xfffff000;
  *param_3 = uVar2;
  return ((int)((param_1 - uVar2) + -0x100) >> 4) + 8 + uVar2;
}
#endif


/* ---- 0x1000b380  FUN_1000b380 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1000b380(int param_1,int param_2,byte *param_3)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = param_2 - *(int *)(param_1 + 0x10) >> 0xc;
  piVar1 = (int *)(param_1 + 0x18 + iVar2 * 8);
  *piVar1 = *(int *)(param_1 + 0x18 + iVar2 * 8) + (uint)*param_3;
  *param_3 = 0;
  piVar1[1] = 0xf1;
  if ((*piVar1 == 0xf0) && (_DAT_10014890 = _DAT_10014890 + 1, _DAT_10014890 == 0x20)) {
    FUN_1000b250(0x10);
  }
  return;
}
#endif


/* ---- 0x1000b3e0  FUN_1000b3e0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int * FUN_1000b3e0(uint param_1)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int *unaff_EBP;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  bool bVar8;
  
  piVar3 = _DAT_100137c8;
  do {
    if (piVar3[4] != -1) {
      piVar7 = (int *)piVar3[2];
      iVar5 = ((int)piVar7 + (-0x18 - (int)piVar3) >> 3) * 0x1000 + piVar3[4];
      for (; piVar7 < piVar3 + 0x806; piVar7 = piVar7 + 2) {
        if (((int)param_1 <= *piVar7) && (param_1 < (uint)piVar7[1])) {
          piVar1 = (int *)FUN_1000b620(iVar5,*piVar7,param_1);
          if (piVar1 != (int *)0x0) {
            _DAT_100137c8 = piVar3;
            *piVar7 = *piVar7 - param_1;
            piVar3[2] = (int)piVar7;
            return piVar1;
          }
          piVar7[1] = param_1;
        }
        iVar5 = iVar5 + 0x1000;
      }
      piVar1 = (int *)piVar3[2];
      iVar5 = piVar3[4];
      for (piVar7 = piVar3 + 6; piVar7 < piVar1; piVar7 = piVar7 + 2) {
        if (((int)param_1 <= *piVar7) && (param_1 < (uint)piVar7[1])) {
          piVar2 = (int *)FUN_1000b620(iVar5,*piVar7,param_1);
          if (piVar2 != (int *)0x0) {
            _DAT_100137c8 = piVar3;
            *piVar7 = *piVar7 - param_1;
            piVar3[2] = (int)piVar7;
            return piVar2;
          }
          piVar7[1] = param_1;
        }
        iVar5 = iVar5 + 0x1000;
      }
    }
    piVar3 = (int *)*piVar3;
  } while (piVar3 != _DAT_100137c8);
  puVar4 = (undefined4 *)&DAT_100117a8;
  while ((puVar4[4] == -1 || (puVar4[3] == 0))) {
    puVar4 = (undefined4 *)*puVar4;
    if (puVar4 == (undefined4 *)&DAT_100117a8) {
      iVar5 = FUN_1000b080();
      if (iVar5 == 0) {
        return (int *)0x0;
      }
      piVar3 = *(int **)(iVar5 + 0x10);
      *(char *)(piVar3 + 2) = (char)param_1;
      _DAT_100137c8 = (int *)iVar5;
      *piVar3 = (int)piVar3 + param_1 + 8;
      piVar3[1] = 0xf0 - param_1;
      *(uint *)(iVar5 + 0x18) = *(int *)(iVar5 + 0x18) - (param_1 & 0xff);
      return piVar3 + 0x40;
    }
  }
  piVar3 = (int *)puVar4[3];
  iVar5 = *piVar3;
  piVar7 = (int *)(((int)piVar3 + (-0x18 - (int)puVar4) >> 3) * 0x1000 + puVar4[4]);
  for (iVar6 = 0; (iVar5 == -1 && (iVar6 < 0x10)); iVar6 = iVar6 + 1) {
    iVar5 = piVar3[2];
    piVar3 = piVar3 + 2;
  }
  piVar3 = (int *)VirtualAlloc(piVar7,iVar6 << 0xc,0x1000,4);
  if (piVar3 != piVar7) {
    return (int *)0x0;
  }
  piVar3 = unaff_EBP;
  if (0 < iVar6) {
    piVar1 = piVar7 + 1;
    do {
      *piVar1 = 0xf0;
      piVar1[-1] = (int)(piVar1 + 1);
      *(undefined1 *)(piVar1 + 0x3d) = 0xff;
      *piVar3 = 0xf0;
      piVar3[1] = 0xf1;
      piVar1 = piVar1 + 0x400;
      piVar3 = piVar3 + 2;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
  }
  piVar1 = puVar4 + 0x806;
  bVar8 = false;
  if (piVar3 < piVar1) {
    do {
      if (*piVar3 == -1) break;
      piVar3 = piVar3 + 2;
    } while (piVar3 < piVar1);
    bVar8 = piVar3 < piVar1;
  }
  _DAT_100137c8 = puVar4;
  puVar4[3] = -(uint)bVar8 & (uint)piVar3;
  *(char *)(piVar7 + 2) = (char)param_1;
  puVar4[2] = unaff_EBP;
  *unaff_EBP = *unaff_EBP - param_1;
  piVar7[1] = piVar7[1] - param_1;
  *piVar7 = (int)piVar7 + param_1 + 8;
  return piVar7 + 0x40;
}
#endif


/* ---- 0x1000b620  FUN_1000b620 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_1000b620(int *param_1,uint param_2,uint param_3)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte *pbVar4;
  uint uVar5;
  byte *pbVar6;
  
  pbVar2 = (byte *)*param_1;
  if (param_3 <= (uint)param_1[1]) {
    *pbVar2 = (byte)param_3;
    if (pbVar2 + param_3 < param_1 + 0x3e) {
      *param_1 = *param_1 + param_3;
      param_1[1] = param_1[1] - param_3;
    }
    else {
      param_1[1] = 0;
      *param_1 = (int)(param_1 + 2);
    }
    return (int)(pbVar2 + 8) * 0x10 + (int)param_1 * -0xf;
  }
  pbVar6 = pbVar2;
  if (pbVar2[param_1[1]] != 0) {
    pbVar6 = pbVar2 + param_1[1];
  }
  if (pbVar6 + param_3 < param_1 + 0x3e) {
    do {
      if (*pbVar6 == 0) {
        pbVar3 = pbVar6 + 1;
        uVar5 = 1;
        bVar1 = pbVar6[1];
        while (bVar1 == 0) {
          pbVar3 = pbVar3 + 1;
          uVar5 = uVar5 + 1;
          bVar1 = *pbVar3;
        }
        if (param_3 <= uVar5) {
          if (param_1 + 0x3e <= pbVar6 + param_3) {
            *param_1 = (int)(param_1 + 2);
            goto LAB_1000b76f;
          }
          *param_1 = (int)(pbVar6 + param_3);
          param_1[1] = uVar5 - param_3;
          goto LAB_1000b776;
        }
        if (pbVar6 == pbVar2) {
          param_1[1] = uVar5;
        }
        else {
          param_2 = param_2 - uVar5;
          if (param_2 < param_3) {
            return 0;
          }
        }
      }
      else {
        pbVar3 = pbVar6 + *pbVar6;
      }
      pbVar6 = pbVar3;
    } while (pbVar3 + param_3 < param_1 + 0x3e);
  }
  pbVar3 = (byte *)(param_1 + 2);
  pbVar6 = pbVar3;
  if (pbVar3 < pbVar2) {
    while (pbVar6 + param_3 < param_1 + 0x3e) {
      if (*pbVar6 == 0) {
        pbVar4 = pbVar6 + 1;
        uVar5 = 1;
        bVar1 = pbVar6[1];
        while (bVar1 == 0) {
          pbVar4 = pbVar4 + 1;
          uVar5 = uVar5 + 1;
          bVar1 = *pbVar4;
        }
        if (param_3 <= uVar5) {
          if (pbVar6 + param_3 < param_1 + 0x3e) {
            *param_1 = (int)(pbVar6 + param_3);
            param_1[1] = uVar5 - param_3;
          }
          else {
            *param_1 = (int)pbVar3;
LAB_1000b76f:
            param_1[1] = 0;
          }
LAB_1000b776:
          *pbVar6 = (byte)param_3;
          return (int)(pbVar6 + 8) * 0x10 + (int)param_1 * -0xf;
        }
        param_2 = param_2 - uVar5;
        if (param_2 < param_3) {
          return 0;
        }
      }
      else {
        pbVar4 = pbVar6 + *pbVar6;
      }
      pbVar6 = pbVar4;
      if (pbVar2 <= pbVar4) {
        return 0;
      }
    }
  }
  return 0;
}
#endif


/* ---- 0x1000b7a0  FUN_1000b7a0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_1000b7a0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int a1;
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = 0;
  if (_DAT_10014894 != (code *)0x0) {
LAB_1000b7f0:
    if (_DAT_10014898 != (code *)0x0) {
      iVar2 = (*_DAT_10014898)();
    }
    if ((iVar2 != 0) && (_DAT_1001489c != (code *)0x0)) {
      iVar2 = (*_DAT_1001489c)(iVar2);
    }
    uVar1 = (*_DAT_10014894)(iVar2,param_1,param_2,param_3);
    return uVar1;
  }
  a1 = LoadLibraryA(&UNK_1000eb04);
  if (a1 != 0) {
    _DAT_10014894 = (code *)GetProcAddress(a1,IMG_ADDR(0x1000eaf8));
    if (_DAT_10014894 != (code *)0x0) {
      _DAT_10014898 = (code *)GetProcAddress(a1,IMG_ADDR(0x1000eae8));
      _DAT_1001489c = (code *)GetProcAddress(a1,IMG_ADDR(0x1000ead4));
      goto LAB_1000b7f0;
    }
  }
  return 0;
}
#endif


/* ---- 0x1000b830  FUN_1000b830 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_1000b830(uint param_1,uint param_2,uint *param_3)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  uVar1 = param_2 + param_1;
  if ((uVar1 < param_1) || (uVar1 < param_2)) {
    uVar2 = 1;
  }
  *param_3 = uVar1;
  return uVar2;
}
#endif


/* ---- 0x1000b860  FUN_1000b860 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_1000b860(undefined4 *param_1,undefined4 *param_2)

{
  int iVar1;
  
  iVar1 = FUN_1000b830(*param_1,*param_2,param_1);
  if (iVar1 != 0) {
    iVar1 = FUN_1000b830(param_1[1],1,param_1 + 1);
    if (iVar1 != 0) {
      param_1[2] = param_1[2] + 1;
    }
  }
  iVar1 = FUN_1000b830(param_1[1],param_2[1],param_1 + 1);
  if (iVar1 != 0) {
    param_1[2] = param_1[2] + 1;
  }
  FUN_1000b830(param_1[2],param_2[2],param_1 + 2);
  return;
}
#endif


/* ---- 0x1000b8d0  FUN_1000b8d0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_1000b8d0(uint *param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *param_1;
  uVar2 = param_1[1];
  *param_1 = uVar1 * 2;
  param_1[1] = uVar2 * 2 | uVar1 >> 0x1f;
  param_1[2] = param_1[2] << 1 | uVar2 >> 0x1f;
  return;
}
#endif


/* ---- 0x1000b900  FUN_1000b900 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_1000b900(uint *param_1)

{
  uint uVar1;
  
  uVar1 = param_1[1];
  param_1[1] = uVar1 >> 1 | param_1[2] << 0x1f;
  param_1[2] = param_1[2] >> 1;
  *param_1 = *param_1 >> 1 | uVar1 << 0x1f;
  return;
}
#endif


/* ---- 0x1000b930  FUN_1000b930 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_1000b930(char *param_1,int param_2,uint *param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint *puVar2;
  short sVar3;
  #define uStack_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define uStack_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define uStack_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  puVar2 = param_3;
  sVar3 = 0x404e;
  *param_3 = 0;
  param_3[1] = 0;
  param_3[2] = 0;
  if (param_2 != 0) {
    param_3 = (uint *)param_2;
    do {
      uStack_c = *puVar2;
      uStack_8 = puVar2[1];
      uStack_4 = puVar2[2];
      FUN_1000b8d0(puVar2);
      FUN_1000b8d0(puVar2);
      FUN_1000b860(puVar2,&uStack_c);
      FUN_1000b8d0(puVar2);
      uStack_c = (uint)*param_1;
      uStack_8 = 0;
      uStack_4 = 0;
      FUN_1000b860(puVar2,&uStack_c);
      param_1 = param_1 + 1;
      param_3 = (uint *)((int)param_3 + -1);
    } while (param_3 != (uint *)0x0);
  }
  uVar1 = puVar2[2];
  while (uVar1 == 0) {
    sVar3 = sVar3 + -0x10;
    puVar2[2] = puVar2[1] >> 0x10;
    uVar1 = puVar2[2];
    puVar2[1] = *puVar2 >> 0x10 | puVar2[1] << 0x10;
    *puVar2 = *puVar2 << 0x10;
  }
  uVar1 = puVar2[2];
  while ((uVar1 & 0x8000) == 0) {
    FUN_1000b8d0(puVar2);
    sVar3 = sVar3 + -1;
    uVar1 = puVar2[2];
  }
  *(short *)((int)puVar2 + 10) = sVar3;
  return;
}
#undef uStack_4
#undef uStack_8
#undef uStack_c

#endif


/* ---- 0x1000ba30  FUN_1000ba30 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
FUN_1000ba30(ushort *param_1,int *param_2,byte *param_3,undefined4 param_4,int param_5,int param_6,
            int param_7)

{
  unsigned char _frame[0x70] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  ushort uVar7;
  int iVar8;
  uint uVar9;
  byte bVar10;
  byte *pbVar11;
  byte *pbVar12;
  uint uVar13;
  byte *pbVar14;
  #define iStack_60 (*(int *)(_frame + (0x70 - 0x60)))
  #define pcStack_5c (*(char **)(_frame + (0x70 - 0x5c)))
  #define uStack_54 (*(uint *)(_frame + (0x70 - 0x54)))
  #define pbStack_50 (*(byte **)(_frame + (0x70 - 0x50)))
  #define iStack_4c (*(int *)(_frame + (0x70 - 0x4c)))
  #define iStack_48 (*(int *)(_frame + (0x70 - 0x48)))
  #define uStack_30 (*(undefined4 *)(_frame + (0x70 - 0x30)))
  #define uStack_2c (*(ushort *)(_frame + (0x70 - 0x2c)))
  #define uStack_2a (*(undefined2 *)(_frame + (0x70 - 0x2a)))
  #define uStack_28 (*(undefined2 *)(_frame + (0x70 - 0x28)))
  #define pbStack_26 (*(byte **)(_frame + (0x70 - 0x26)))
  #define uStack_22 (*(ushort *)(_frame + (0x70 - 0x22)))
  #define acStack_1c (*(char (*)[23])(_frame + (0x70 - 0x1c)))
  #define cStack_5 (*(char *)(_frame + (0x70 - 0x5)))
  
  pcStack_5c = acStack_1c;
  iVar8 = 0;
  uVar13 = 0;
  uVar7 = 0;
  iStack_4c = 1;
  uStack_54 = 0;
  bVar2 = false;
  bVar4 = false;
  bVar3 = false;
  bVar5 = false;
  bVar6 = false;
  iStack_48 = 0;
  iStack_60 = 0;
  uStack_30 = 0;
  pbStack_50 = param_3;
  for (pbVar11 = param_3;
      (((bVar10 = *pbVar11, bVar10 == 0x20 || (bVar10 == 9)) || (bVar10 == 10)) ||
      (pbVar14 = param_3, bVar10 == 0xd)); pbVar11 = pbVar11 + 1) {
  }
  do {
    bVar10 = *pbVar11;
    pbVar12 = pbVar11 + 1;
    param_3 = (byte *)CONCAT31(PIECE(param_3,1,3),bVar10);
    switch(iVar8) {
    case 0:
      if (('0' < (char)bVar10) && ((char)bVar10 < ':')) {
        iVar8 = 3;
        goto code_r0x1000bf02;
      }
      if (bVar10 == DAT_10010acc) {
        iVar8 = 5;
      }
      else if (bVar10 == 0x2b) {
        iVar8 = 2;
        uVar7 = 0;
      }
      else if (bVar10 == 0x2d) {
        iVar8 = 2;
        uVar7 = 0x8000;
      }
      else {
        if (bVar10 != 0x30) goto code_r0x1000befd;
        iVar8 = 1;
      }
      break;
    case 1:
      bVar2 = true;
      if (('0' < (char)bVar10) && ((char)bVar10 < ':')) {
        iVar8 = 3;
        goto code_r0x1000bf02;
      }
      if (bVar10 == DAT_10010acc) {
        iVar8 = 4;
      }
      else {
        switch(bVar10) {
        case 0x2b:
        case 0x2d:
          goto code_r0x1000bd03;
        default:
          goto code_r0x1000befd;
        case 0x30:
code_r0x1000bba4:
          iVar8 = 1;
          break;
        case 0x44:
        case 0x45:
        case 100:
        case 0x65:
          goto code_r0x1000bcf9;
        }
      }
      break;
    case 2:
      if (('0' < (char)bVar10) && ((char)bVar10 < ':')) {
        iVar8 = 3;
        goto code_r0x1000bf02;
      }
      if (bVar10 == DAT_10010acc) {
        iVar8 = 5;
      }
      else {
        if (bVar10 == 0x30) goto code_r0x1000bba4;
        iVar8 = 10;
        pbVar12 = pbVar14;
      }
      break;
    case 3:
      while( true ) {
        bVar2 = true;
        if (_DAT_10010ac8 < 2) {
          uVar9 = *(byte *)(_DAT_10010ad8 + ((uint)param_3 & 0xff) * 2) & 4;
        }
        else {
          uVar9 = FUN_10008d50((uint)param_3 & 0xff,4);
        }
        if (uVar9 == 0) break;
        if (uVar13 < 0x19) {
          uVar13 = uVar13 + 1;
          *pcStack_5c = bVar10 - 0x30;
          bVar10 = *pbVar12;
          pcStack_5c = pcStack_5c + 1;
          param_3 = (byte *)CONCAT31(PIECE(param_3,1,3),bVar10);
          pbVar12 = pbVar12 + 1;
        }
        else {
          bVar10 = *pbVar12;
          iStack_60 = iStack_60 + 1;
          param_3 = (byte *)CONCAT31(PIECE(param_3,1,3),bVar10);
          pbVar12 = pbVar12 + 1;
        }
      }
      uStack_54 = uVar13;
      if (bVar10 != DAT_10010acc) {
        switch(bVar10) {
        case 0x2b:
        case 0x2d:
          goto code_r0x1000bd03;
        case 0x44:
        case 0x45:
        case 100:
        case 0x65:
          goto code_r0x1000bcf9;
        }
code_r0x1000befd:
        iVar8 = 10;
        goto code_r0x1000bf02;
      }
      iVar8 = 4;
      break;
    case 4:
      bVar4 = true;
      if (uVar13 == 0) {
        while (bVar10 == 0x30) {
          bVar10 = *pbVar12;
          iStack_60 = iStack_60 + -1;
          pbVar12 = pbVar12 + 1;
          PIECE(param_3,1,3) = (undefined3)((uint)param_3 >> 8);
          param_3 = (byte *)CONCAT31(PIECE(param_3,1,3),bVar10);
        }
      }
      while( true ) {
        bVar2 = true;
        if (_DAT_10010ac8 < 2) {
          uVar9 = *(byte *)(_DAT_10010ad8 + ((uint)param_3 & 0xff) * 2) & 4;
        }
        else {
          uVar9 = FUN_10008d50((uint)param_3 & 0xff,4);
        }
        if (uVar9 == 0) break;
        if (uVar13 < 0x19) {
          uVar13 = uVar13 + 1;
          *pcStack_5c = bVar10 - 0x30;
          pcStack_5c = pcStack_5c + 1;
          iStack_60 = iStack_60 + -1;
        }
        bVar10 = *pbVar12;
        pbVar12 = pbVar12 + 1;
        param_3 = (byte *)CONCAT31(PIECE(param_3,1,3),bVar10);
      }
      uStack_54 = uVar13;
      switch(bVar10) {
      case 0x2b:
      case 0x2d:
code_r0x1000bd03:
        bVar2 = true;
        pbVar12 = pbVar12 + -1;
        iVar8 = 0xb;
        break;
      default:
        goto code_r0x1000befd;
      case 0x44:
      case 0x45:
      case 100:
      case 0x65:
code_r0x1000bcf9:
        bVar2 = true;
        iVar8 = 6;
      }
      break;
    case 5:
      bVar4 = true;
      if (_DAT_10010ac8 < 2) {
        uVar9 = *(byte *)(_DAT_10010ad8 + (uint)bVar10 * 2) & 4;
      }
      else {
        uVar9 = FUN_10008d50(bVar10,4);
      }
      if (uVar9 == 0) {
        iVar8 = 10;
        pbVar12 = pbVar14;
      }
      else {
        iVar8 = 4;
        pbVar12 = pbVar11;
      }
      break;
    case 6:
      pbVar11 = pbVar11 + -1;
      pbVar14 = pbVar11;
      pbStack_50 = pbVar11;
      if (('0' < (char)bVar10) && ((char)bVar10 < ':')) {
        iVar8 = 9;
        goto code_r0x1000bf02;
      }
      if (bVar10 == 0x2b) {
code_r0x1000bef6:
        iVar8 = 7;
        pbVar14 = pbVar11;
        pbStack_50 = pbVar11;
      }
      else {
        if (bVar10 != 0x2d) goto code_r0x1000bde6;
code_r0x1000bee7:
        iVar8 = 7;
        iStack_4c = -1;
        pbVar14 = pbVar11;
        pbStack_50 = pbVar11;
      }
      break;
    case 7:
      if (('0' < (char)bVar10) && ((char)bVar10 < ':')) {
        iVar8 = 9;
        goto code_r0x1000bf02;
      }
code_r0x1000bde6:
      if (bVar10 == 0x30) {
        iVar8 = 8;
      }
      else {
        iVar8 = 10;
        pbVar12 = pbVar14;
      }
      break;
    case 8:
      bVar3 = true;
      while (bVar10 == 0x30) {
        bVar10 = *pbVar12;
        pbVar12 = pbVar12 + 1;
      }
      if (((char)bVar10 < '1') || ('9' < (char)bVar10)) goto code_r0x1000befd;
      iVar8 = 9;
code_r0x1000bf02:
      pbVar12 = pbVar12 + -1;
      break;
    case 9:
      bVar3 = true;
      iStack_48 = 0;
      while( true ) {
        if (_DAT_10010ac8 < 2) {
          uVar13 = *(byte *)(_DAT_10010ad8 + ((uint)param_3 & 0xff) * 2) & 4;
        }
        else {
          uVar13 = FUN_10008d50((uint)param_3 & 0xff,4);
        }
        if (uVar13 == 0) goto code_r0x1000be6a;
        iStack_48 = (char)bVar10 + -0x30 + iStack_48 * 10;
        if (0x1450 < iStack_48) break;
        bVar10 = *pbVar12;
        pbVar12 = pbVar12 + 1;
        param_3 = (byte *)CONCAT31(PIECE(param_3,1,3),bVar10);
      }
      iStack_48 = 0x1451;
code_r0x1000be6a:
      while( true ) {
        if (_DAT_10010ac8 < 2) {
          uVar13 = *(byte *)(_DAT_10010ad8 + ((uint)param_3 & 0xff) * 2) & 4;
        }
        else {
          uVar13 = FUN_10008d50((uint)param_3 & 0xff,4);
        }
        if (uVar13 == 0) break;
        bVar10 = *pbVar12;
        pbVar12 = pbVar12 + 1;
        param_3 = (byte *)CONCAT31(PIECE(param_3,1,3),bVar10);
      }
      iVar8 = 10;
      pbVar12 = pbVar12 + -1;
      uVar13 = uStack_54;
      pbVar14 = pbStack_50;
      break;
    case 0xb:
      if (param_7 == 0) goto code_r0x1000befd;
      if (bVar10 == 0x2b) goto code_r0x1000bef6;
      if (bVar10 == 0x2d) goto code_r0x1000bee7;
      iVar8 = 10;
      pbVar12 = pbVar11;
      pbVar14 = pbVar11;
      pbStack_50 = pbVar11;
    }
    pbVar11 = pbVar12;
  } while (iVar8 != 10);
  *param_2 = (int)pbVar12;
  if (bVar2) {
    if (0x18 < uVar13) {
      if ('\x04' < cStack_5) {
        cStack_5 = cStack_5 + '\x01';
      }
      pcStack_5c = pcStack_5c + -1;
      iStack_60 = iStack_60 + 1;
      uVar13 = 0x18;
    }
    if (uVar13 == 0) {
      uStack_2c = 0;
      uStack_22 = 0;
      param_3 = (byte *)0x0;
      pbVar11 = (byte *)0x0;
      goto LAB_1000bfd4;
    }
    cVar1 = pcStack_5c[-1];
    while (cVar1 == '\0') {
      uVar13 = uVar13 - 1;
      iStack_60 = iStack_60 + 1;
      cVar1 = pcStack_5c[-2];
      pcStack_5c = pcStack_5c + -1;
    }
    FUN_1000b930(acStack_1c,uVar13,&uStack_2c);
    if (iStack_4c < 0) {
      iStack_48 = -iStack_48;
    }
    iStack_48 = iStack_48 + iStack_60;
    if (!bVar3) {
      iStack_48 = iStack_48 + param_5;
    }
    if (!bVar4) {
      iStack_48 = iStack_48 - param_6;
    }
    if (iStack_48 < 0x1451) {
      if (-0x1451 < iStack_48) {
        FUN_1000d0c0(&uStack_2c,iStack_48,param_4);
        pbVar11 = (byte *)CONCAT22(uStack_28,uStack_2a);
        param_3 = pbStack_26;
        goto LAB_1000bfd4;
      }
      bVar6 = true;
    }
    else {
      bVar5 = true;
    }
  }
  uStack_2c = (ushort)param_3;
  pbVar11 = param_3;
  uStack_22 = uStack_2c;
LAB_1000bfd4:
  if (bVar2) {
    if (bVar5) {
      pbVar11 = (byte *)0x0;
      uStack_22 = 0x7fff;
      param_3 = (byte *)0x80000000;
      uStack_2c = 0;
      uStack_30 = 2;
    }
    else if (bVar6) {
      uStack_2c = 0;
      uStack_22 = 0;
      param_3 = (byte *)0x0;
      pbVar11 = (byte *)0x0;
      uStack_30 = 1;
    }
  }
  else {
    uStack_2c = 0;
    uStack_22 = 0;
    param_3 = (byte *)0x0;
    pbVar11 = (byte *)0x0;
    uStack_30 = 4;
  }
  *param_1 = uStack_2c;
  *(byte **)(param_1 + 1) = pbVar11;
  *(byte **)(param_1 + 3) = param_3;
  param_1[5] = uStack_22 | uVar7;
  return uStack_30;
}
#undef acStack_1c
#undef cStack_5
#undef iStack_48
#undef iStack_4c
#undef iStack_60
#undef pbStack_26
#undef pbStack_50
#undef pcStack_5c
#undef uStack_22
#undef uStack_28
#undef uStack_2a
#undef uStack_2c
#undef uStack_30
#undef uStack_54

#endif


/* ---- 0x1000c1c0  FUN_1000c1c0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4
FUN_1000c1c0(int param_1,uint param_2,uint param_3,int param_4,byte param_5,short *param_6)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  short *psVar1;
  ushort uVar2;
  char cVar3;
  uint uVar4;
  int iVar5;
  short *psVar6;
  short *psVar7;
  int iVar8;
  short sVar9;
  int iVar10;
  #define uStack_1c (*(undefined1 *)(_frame + (0x30 - 0x1c)))
  #define uStack_1b (*(undefined1 *)(_frame + (0x30 - 0x1b)))
  #define uStack_1a (*(undefined1 *)(_frame + (0x30 - 0x1a)))
  #define uStack_19 (*(undefined1 *)(_frame + (0x30 - 0x19)))
  #define uStack_18 (*(undefined1 *)(_frame + (0x30 - 0x18)))
  #define uStack_17 (*(undefined1 *)(_frame + (0x30 - 0x17)))
  #define uStack_16 (*(undefined1 *)(_frame + (0x30 - 0x16)))
  #define uStack_15 (*(undefined1 *)(_frame + (0x30 - 0x15)))
  #define uStack_14 (*(undefined1 *)(_frame + (0x30 - 0x14)))
  #define uStack_13 (*(undefined1 *)(_frame + (0x30 - 0x13)))
  #define uStack_12 (*(undefined1 *)(_frame + (0x30 - 0x12)))
  #define uStack_11 (*(undefined1 *)(_frame + (0x30 - 0x11)))
  #define uStack_10 (*(undefined2 *)(_frame + (0x30 - 0x10)))
  #define uStack_e (*(undefined2 *)(_frame + (0x30 - 0xe)))
  #define uStack_c (*(undefined2 *)(_frame + (0x30 - 0xc)))
  #define uStack_a (*(undefined2 *)(_frame + (0x30 - 0xa)))
  #define uStack_8 (*(undefined2 *)(_frame + (0x30 - 0x8)))
  #define uStack_6 (*(undefined1 *)(_frame + (0x30 - 0x6)))
  #define cStack_5 (*(char *)(_frame + (0x30 - 0x5)))
  
  psVar1 = param_6;
  uStack_1c = 0xcc;
  uStack_1b = 0xcc;
  uStack_1a = 0xcc;
  uStack_19 = 0xcc;
  uStack_18 = 0xcc;
  uStack_17 = 0xcc;
  uStack_16 = 0xcc;
  uStack_15 = 0xcc;
  uStack_14 = 0xcc;
  uStack_13 = 0xcc;
  uVar4 = param_3 & 0x7fff;
  uStack_12 = 0xfb;
  uStack_11 = 0x3f;
  if ((param_3 & 0x8000) == 0) {
    *(undefined1 *)(param_6 + 1) = 0x20;
  }
  else {
    *(undefined1 *)(param_6 + 1) = 0x2d;
  }
  if ((((short)uVar4 == 0) && (param_2 == 0)) && (param_1 == 0)) {
    *param_6 = 0;
LAB_1000c3cf:
    *(undefined1 *)(psVar1 + 1) = 0x20;
    *(undefined1 *)((int)psVar1 + 3) = 1;
    *(undefined1 *)(psVar1 + 2) = 0x30;
    *(undefined1 *)((int)psVar1 + 5) = 0;
    return 1;
  }
  if ((short)uVar4 == 0x7fff) {
    *param_6 = 1;
    if (((param_2 != 0x80000000) || (param_1 != 0)) && ((param_2 & 0x40000000) == 0)) {
      param_6[2] = 0x2331;
      param_6[3] = 0x4e53;
      param_6[4] = 0x4e41;
      *(undefined1 *)((int)param_6 + 3) = 6;
      *(undefined1 *)(param_6 + 5) = 0;
      return 0;
    }
    if ((((param_3 & 0x8000) != 0) && (param_2 == 0xc0000000)) && (param_1 == 0)) {
      param_6[2] = 0x2331;
      param_6[3] = 0x4e49;
      *(undefined1 *)((int)param_6 + 3) = 5;
      param_6[4] = 0x44;
      return 0;
    }
    if ((param_2 == 0x80000000) && (param_1 == 0)) {
      param_6[2] = 0x2331;
      param_6[3] = 0x4e49;
      *(undefined1 *)((int)param_6 + 3) = 5;
      param_6[4] = 0x46;
      return 0;
    }
    param_6[2] = 0x2331;
    param_6[3] = 0x4e51;
    param_6[4] = 0x4e41;
    *(undefined1 *)((int)param_6 + 3) = 6;
    *(undefined1 *)(param_6 + 5) = 0;
    return 0;
  }
  uStack_6 = (undefined1)uVar4;
  cStack_5 = (char)(uVar4 >> 8);
  uStack_a = (undefined2)param_2;
  uStack_8 = (undefined2)(param_2 >> 0x10);
  uStack_e = (undefined2)param_1;
  uStack_c = (undefined2)((uint)param_1 >> 0x10);
  uStack_10 = 0;
  sVar9 = (short)(((uVar4 >> 8) + (param_2 >> 0x18) * 2) * 0x4d + -0x134312f4 + uVar4 * 0x4d10 >>
                 0x10);
  FUN_1000d0c0(&uStack_10,-(int)sVar9,1);
  if (0x3ffe < CONCAT11(cStack_5,uStack_6)) {
    sVar9 = sVar9 + 1;
    FUN_1000ce00(&uStack_10,&uStack_1c);
  }
  *psVar1 = sVar9;
  iVar8 = param_4;
  if (((param_5 & 1) != 0) && (iVar8 = param_4 + sVar9, param_4 + sVar9 < 1)) {
    *psVar1 = 0;
    goto LAB_1000c3cf;
  }
  if (0x15 < iVar8) {
    iVar8 = 0x15;
  }
  uVar2 = CONCAT11(cStack_5,uStack_6);
  uStack_6 = 0;
  cStack_5 = '\0';
  iVar5 = 8;
  iVar10 = uVar2 - 0x3ffe;
  do {
    FUN_1000b8d0(&uStack_10);
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  if (iVar10 < 0) {
    for (uVar4 = -iVar10 & 0xff; uVar4 != 0; uVar4 = uVar4 - 1) {
      FUN_1000b900(&uStack_10);
    }
  }
  psVar1 = psVar1 + 2;
  iVar8 = iVar8 + 1;
  psVar6 = psVar1;
  if (0 < iVar8) {
    do {
      param_1 = CONCAT22(uStack_e,uStack_10);
      param_2 = CONCAT22(uStack_a,uStack_c);
      param_3 = CONCAT13(cStack_5,CONCAT12(uStack_6,uStack_8));
      FUN_1000b8d0(&uStack_10);
      FUN_1000b8d0(&uStack_10);
      FUN_1000b860(&uStack_10,&param_1);
      FUN_1000b8d0(&uStack_10);
      cVar3 = cStack_5 + '0';
      cStack_5 = '\0';
      *(char *)psVar6 = cVar3;
      psVar6 = (short *)((int)psVar6 + 1);
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
  }
  psVar7 = psVar6 + -1;
  if (*(char *)((int)psVar6 + -1) < '5') {
    if (psVar1 <= psVar7) {
      do {
        if ((char)*psVar7 != '0') break;
        psVar7 = (short *)((int)psVar7 + -1);
      } while (psVar1 <= psVar7);
      if (psVar1 <= psVar7) goto LAB_1000c526;
    }
    *(undefined1 *)psVar1 = 0x30;
    *param_6 = 0;
    *(undefined1 *)(param_6 + 1) = 0x20;
    *(undefined1 *)((int)param_6 + 3) = 1;
    *(undefined1 *)((int)param_6 + 5) = 0;
    return 1;
  }
  if (psVar1 <= psVar7) {
    do {
      if ((char)*psVar7 != '9') break;
      *(undefined1 *)psVar7 = 0x30;
      psVar7 = (short *)((int)psVar7 + -1);
    } while (psVar1 <= psVar7);
    if (psVar1 <= psVar7) {
      *(char *)psVar7 = (char)*psVar7 + '\x01';
      goto LAB_1000c526;
    }
  }
  psVar7 = (short *)((int)psVar7 + 1);
  *param_6 = *param_6 + 1;
  *(char *)psVar7 = *(char *)psVar7 + '\x01';
LAB_1000c526:
  cVar3 = ((char)psVar7 - (char)param_6) + -3;
  *(char *)((int)param_6 + 3) = cVar3;
  *(undefined1 *)((int)param_6 + cVar3 + 4) = 0;
  return 1;
}
#undef cStack_5
#undef uStack_10
#undef uStack_11
#undef uStack_12
#undef uStack_13
#undef uStack_14
#undef uStack_15
#undef uStack_16
#undef uStack_17
#undef uStack_18
#undef uStack_19
#undef uStack_1a
#undef uStack_1b
#undef uStack_1c
#undef uStack_6
#undef uStack_8
#undef uStack_a
#undef uStack_c
#undef uStack_e

#endif


/* ---- 0x1000c550  FUN_1000c550 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_1000c550(undefined4 param_1)

{
  int iVar1;
  
  if (_DAT_100148b8 != (code *)0x0) {
    iVar1 = (*_DAT_100148b8)(param_1);
    if (iVar1 != 0) {
      return 1;
    }
  }
  return 0;
}
#endif


/* ---- 0x1000c610  FUN_1000c610 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_1000c610(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_1000c650(param_1);
  if (iVar1 != 0) {
    return -1;
  }
  if ((*(uint *)(param_1 + 0xc) & 0x4000) != 0) {
    iVar1 = FUN_1000d200(*(undefined4 *)(param_1 + 0x10));
    return -(uint)(iVar1 != 0);
  }
  return 0;
}
#endif


/* ---- 0x1000c650  FUN_1000c650 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_1000c650(int *param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  uVar3 = 0;
  if ((((byte)param_1[3] & 3) == 2) && ((param_1[3] & 0x108U) != 0)) {
    iVar4 = *param_1 - param_1[2];
    if (0 < iVar4) {
      iVar2 = FUN_1000d2a0(param_1[4],param_1[2],iVar4);
      uVar1 = param_1[3];
      if (iVar2 == iVar4) {
        if ((uVar1 & 0x80) != 0) {
          param_1[1] = 0;
          param_1[3] = uVar1 & 0xfffffffd;
          *param_1 = param_1[2];
          return 0;
        }
      }
      else {
        uVar3 = 0xffffffff;
        param_1[3] = uVar1 | 0x20;
      }
    }
  }
  param_1[1] = 0;
  *param_1 = param_1[2];
  return uVar3;
}
#endif


/* ---- 0x1000c6c0  FUN_1000c6c0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_1000c6c0(void)

{
  FUN_1000c6d0(1);
  return;
}
#endif


/* ---- 0x1000c6d0  FUN_1000c6d0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_1000c6d0(int param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  #define iStack_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  iVar3 = 0;
  iStack_4 = 0;
  iVar2 = 0;
  FUN_10006810(2);
  if (0 < _DAT_100159c0) {
    do {
      iVar1 = *(int *)(_DAT_100149a4 + iVar3 * 4);
      if ((iVar1 != 0) && ((*(byte *)(iVar1 + 0xc) & 0x83) != 0)) {
        FUN_100068f0(iVar3,iVar1);
        iVar1 = *(int *)(_DAT_100149a4 + iVar3 * 4);
        if ((*(uint *)(iVar1 + 0xc) & 0x83) != 0) {
          if (param_1 == 1) {
            iVar1 = FUN_1000c610(iVar1);
            if (iVar1 != -1) {
              iStack_4 = iStack_4 + 1;
            }
          }
          else if (((param_1 == 0) && ((*(uint *)(iVar1 + 0xc) & 2) != 0)) &&
                  (iVar1 = FUN_1000c610(iVar1), iVar1 == -1)) {
            iVar2 = -1;
          }
        }
        FUN_10006960(iVar3,*(undefined4 *)(_DAT_100149a4 + iVar3 * 4));
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < _DAT_100159c0);
  }
  FUN_10006890();
  if (param_1 != 1) {
    iStack_4 = iVar2;
  }
  return iStack_4;
}
#undef iStack_4

#endif


/* ---- 0x1000c790  FUN_1000c790 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_1000c790(int param_1,undefined4 param_2,undefined4 param_3,int *param_4)

{
  unsigned char _frame[0x90] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  bool bVar2;
  int iVar3;
  undefined1 *puVar4;
  int iVar5;
  uint uVar6;
  byte *pbVar7;
  #define auStack_80 (*(undefined1 (*)[128])(_frame + (0x90 - 0x80)))
  
  if (param_1 != 1) {
    if (param_1 != 0) {
      return 0xffffffff;
    }
    iVar3 = ((code *)FUN_1000d530)(param_2,param_3,IMG_ADDR(0x100148c8),4,0);
    if (iVar3 != 0) {
      pbVar7 = (byte *)IMG_ADDR(0x100148c8);
      *(char *)param_4 = '\0';
      while( true ) {
        bVar1 = *pbVar7;
        if (_DAT_10010ac8 < 2) {
          uVar6 = *(byte *)(_DAT_10010ad8 + (uint)bVar1 * 2) & 4;
        }
        else {
          uVar6 = FUN_10008d50(bVar1,4);
        }
        if (uVar6 == 0) break;
        pbVar7 = pbVar7 + 2;
        *(byte *)param_4 = (char)*param_4 * '\n' + bVar1 + -0x30;
        if (IMG_ADDR(0x100148cf) < (int)pbVar7) {
          return 0;
        }
      }
      return 0;
    }
    return 0xffffffff;
  }
  puVar4 = auStack_80;
  bVar2 = false;
  iVar3 = ((code *)FUN_1000d660)(param_2,param_3,auStack_80,0x80,0);
  if (iVar3 == 0) {
    iVar3 = GetLastError();
    if (((iVar3 != 0x7a) || (iVar3 = ((code *)FUN_1000d660)(param_2,param_3,0,0,0), iVar3 == 0)) ||
       (puVar4 = (undefined1 *)FUN_10009580(iVar3), puVar4 == (undefined1 *)0x0)) goto LAB_1000c840;
    bVar2 = true;
    iVar3 = ((code *)FUN_1000d660)(param_2,param_3,puVar4,iVar3,0);
    if (iVar3 == 0) goto LAB_1000c840;
  }
  iVar5 = FUN_10009580(iVar3);
  *param_4 = iVar5;
  if (iVar5 != 0) {
    msvc_strncpy(iVar5,puVar4,iVar3);
    if (!bVar2) {
      return 0;
    }
    FUN_10009510();
    return 0;
  }
LAB_1000c840:
  if (!bVar2) {
    return 0xffffffff;
  }
  FUN_10009510();
  return 0xffffffff;
}
#undef auStack_80

#endif


/* ---- 0x1000ca50  FUN_1000ca50 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int FUN_1000ca50(void)

{
  uint *puVar1;
  undefined4 *puVar2;
  int iVar3;
  uint in_stack_00000004;
  
  puVar1 = (uint *)FUN_1000cae0();
  iVar3 = 0;
  *puVar1 = in_stack_00000004;
  puVar1 = (uint *)IMG_ADDR(0x100138c0);
  do {
    if (in_stack_00000004 == *puVar1) {
      puVar2 = (undefined4 *)FUN_1000cad0();
      *puVar2 = *(undefined4 *)(iVar3 * 8 + IMG_ADDR(0x100138c4));
      return (int)puVar2;
    }
    puVar1 = puVar1 + 2;
    iVar3 = iVar3 + 1;
  } while (puVar1 < (uint *)IMG_ADDR(0x10013a28));
  if ((0x12 < in_stack_00000004) && (in_stack_00000004 < 0x25)) {
    puVar2 = (undefined4 *)FUN_1000cad0();
    *puVar2 = 0xd;
    return (int)puVar2;
  }
  if ((0xbb < in_stack_00000004) && (in_stack_00000004 < 0xcb)) {
    puVar2 = (undefined4 *)FUN_1000cad0();
    *puVar2 = 8;
    return (int)puVar2;
  }
  puVar2 = (undefined4 *)FUN_1000cad0();
  *puVar2 = 0x16;
  return (int)puVar2;
}
#endif


/* ---- 0x1000cad0  FUN_1000cad0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_1000cad0(void)

{
  int iVar1;
  
  iVar1 = FUN_10007b60();
  return iVar1 + 8;
}
#endif


/* ---- 0x1000cae0  FUN_1000cae0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_1000cae0(void)

{
  int iVar1;
  
  iVar1 = FUN_10007b60();
  return iVar1 + 0xc;
}
#endif


/* ---- 0x1000caf0  FUN_1000caf0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_1000caf0(uint param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  if ((param_1 < _DAT_10015ae0) &&
     ((*(byte *)(*(int *)(&DAT_100159e0 + ((int)param_1 >> 5) * 4) + 4 + (param_1 & 0x1f) * 0x24) &
      1) != 0)) {
    FUN_1000d980(param_1);
    uVar1 = FUN_1000cb70(param_1,param_2,param_3);
    FUN_1000d9f0(param_1);
    return uVar1;
  }
  puVar2 = (undefined4 *)FUN_1000cad0();
  *puVar2 = 9;
  puVar2 = (undefined4 *)FUN_1000cae0();
  *puVar2 = 0;
  return 0xffffffff;
}
#endif


/* ---- 0x1000cb70  FUN_1000cb70 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_1000cb70(uint param_1,char *param_2,int param_3)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  unsigned char _stkneg[48] __attribute__((aligned(16)));  /* the original frame below the return address */
  int *piVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 unaff_EBX;
  int iVar6;
  int iVar7;
  int *unaff_ESI;
  int unaff_EDI;
  char *pcVar8;
  #define uStack_20 (*(undefined4 *)(_frame + (0x30 - 0x20)))
  #define pcStack_c (*(char **)(_frame + (0x30 - 0xc)))
  #define pcStack_8 (*(char **)(_frame + (0x30 - 0x8)))
  #define piStack_4 (*(int **)(_frame + (0x30 - 0x4)))
  
  iVar7 = 0;
  if (param_3 != 0) {
    piVar1 = (int *)(&DAT_100159e0 + ((int)param_1 >> 5) * 4);
    iVar6 = (param_1 & 0x1f) * 0x24;
    bVar3 = *(byte *)(iVar6 + 4 + *(int *)(&DAT_100159e0 + ((int)param_1 >> 5) * 4));
    if ((bVar3 & 2) == 0) {
      pcVar8 = param_2;
      if (((bVar3 & 0x48) != 0) &&
         (cVar2 = *(char *)(iVar6 + *(int *)(&DAT_100159e0 + ((int)param_1 >> 5) * 4) + 5),
         cVar2 != '\n')) {
        *param_2 = cVar2;
        param_3 = param_3 + -1;
        pcVar8 = param_2 + 1;
        iVar7 = 1;
        *(undefined1 *)(iVar6 + 5 + *piVar1) = 10;
      }
      uStack_20 = 0;
      piStack_4 = piVar1;
      iVar4 = ReadFile(*(undefined4 *)(iVar6 + *piVar1),pcVar8,param_3,&pcStack_8);
      if (iVar4 != 0) {
        iVar7 = iVar7 + unaff_EDI;
        bVar3 = *(byte *)(iVar6 + 4 + *piVar1);
        if ((bVar3 & 0x80) != 0) {
          if ((unaff_EDI == 0) || (*param_2 != '\n')) {
            bVar3 = bVar3 & 0xfb;
          }
          else {
            bVar3 = bVar3 | 4;
          }
          *(byte *)(iVar6 + 4 + *piVar1) = bVar3;
          pcStack_8 = pcStack_c + iVar7;
          pcVar8 = param_2;
          if (pcStack_c < pcStack_8) {
            while (cVar2 = *pcVar8, cVar2 != '\x1a') {
              if (cVar2 == '\r') {
                if (pcVar8 < pcStack_8 + -1) {
                  if (pcVar8[1] == '\n') {
                    pcVar8 = pcVar8 + 2;
                    *param_2 = '\n';
                    goto LAB_1000cd48;
                  }
                  *param_2 = '\r';
                  param_2 = param_2 + 1;
                  pcVar8 = pcVar8 + 1;
                }
                else {
                  iVar4 = 0;
                  pcVar8 = pcVar8 + 1;
                  iVar7 = ReadFile(*(undefined4 *)(iVar6 + *unaff_ESI),(int)&uStack_20 + 3,1,
                                   (_stkneg + 20),0);
                  if (iVar7 == 0) {
                    iVar4 = GetLastError();
                  }
                  if ((iVar4 == 0) && (unaff_EDI != 0)) {
                    if ((*(byte *)(iVar6 + 4 + *unaff_ESI) & 0x48) == 0) {
                      if ((param_2 == pcStack_c) && (PIECE(uStack_20,3,1) == '\n')) {
                        *param_2 = '\n';
                        goto LAB_1000cd48;
                      }
                      FUN_1000da20(unaff_EBX,0xffffffff,1);
                      if (PIECE(uStack_20,3,1) != '\n') goto LAB_1000cd45;
                    }
                    else {
                      if (PIECE(uStack_20,3,1) == '\n') {
                        *param_2 = '\n';
                        goto LAB_1000cd48;
                      }
                      *param_2 = '\r';
                      param_2 = param_2 + 1;
                      *(char *)(iVar6 + 5 + *unaff_ESI) = PIECE(uStack_20,3,1);
                    }
                  }
                  else {
LAB_1000cd45:
                    *param_2 = '\r';
LAB_1000cd48:
                    param_2 = param_2 + 1;
                  }
                }
              }
              else {
                *param_2 = cVar2;
                param_2 = param_2 + 1;
                pcVar8 = pcVar8 + 1;
              }
              if (pcStack_8 <= pcVar8) {
                return (int)param_2 - (int)pcStack_c;
              }
            }
            bVar3 = *(byte *)(iVar6 + 4 + *unaff_ESI);
            if ((bVar3 & 0x40) == 0) {
              *(byte *)(iVar6 + 4 + *unaff_ESI) = bVar3 | 2;
            }
          }
          iVar7 = (int)param_2 - (int)pcStack_c;
        }
        return iVar7;
      }
      iVar7 = GetLastError();
      if (iVar7 == 5) {
        puVar5 = (undefined4 *)FUN_1000cad0();
        *puVar5 = 9;
        puVar5 = (undefined4 *)FUN_1000cae0();
        *puVar5 = 5;
        return -1;
      }
      if (iVar7 != 0x6d) {
        FUN_1000ca50();
        return -1;
      }
    }
  }
  return 0;
}
#undef pcStack_8
#undef pcStack_c
#undef piStack_4
#undef uStack_20

#endif


/* ---- 0x1000cda0  FUN_1000cda0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1000cda0(undefined4 param_1,int *param_2)

{
  int iVar1;
  
  _DAT_10014814 = _DAT_10014814 + 1;
  iVar1 = FUN_10009580(0x1000);
  param_2[2] = iVar1;
  if (iVar1 != 0) {
    param_2[3] = param_2[3] | 8;
    param_2[6] = 0x1000;
    *param_2 = param_2[2];
    param_2[1] = 0;
    return;
  }
  param_2[6] = 2;
  param_2[3] = param_2[3] | 4;
  param_2[2] = (int)(param_2 + 5);
  *param_2 = (int)(param_2 + 5);
  param_2[1] = 0;
  return;
}
#endif


/* ---- 0x1000ce00  FUN_1000ce00 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_1000ce00(int *param_1,int *param_2)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  ushort uVar1;
  int iVar2;
  ushort uVar3;
  ushort uVar4;
  int iVar5;
  ushort uVar6;
  ushort *puVar7;
  ushort *puVar8;
  #define psStack_20 (*(short **)(_frame + (0x30 - 0x20)))
  #define iStack_18 (*(int *)(_frame + (0x30 - 0x18)))
  #define iStack_14 (*(int *)(_frame + (0x30 - 0x14)))
  #define iStack_10 (*(int *)(_frame + (0x30 - 0x10)))
  #define bStack_c (*(byte *)(_frame + (0x30 - 0xc)))
  #define uStack_b (*(undefined1 *)(_frame + (0x30 - 0xb)))
  #define uStack_a (*(undefined2 *)(_frame + (0x30 - 0xa)))
  #define sStack_8 (*(short *)(_frame + (0x30 - 0x8)))
  #define uStack_6 (*(undefined2 *)(_frame + (0x30 - 0x6)))
  #define uStack_4 (*(undefined2 *)(_frame + (0x30 - 0x4)))
  #define uStack_2 (*(ushort *)(_frame + (0x30 - 0x2)))
  
  iStack_14 = 0;
  bStack_c = 0;
  uStack_b = 0;
  uStack_a = 0;
  sStack_8 = 0;
  uStack_6 = 0;
  uVar3 = *(ushort *)((int)param_2 + 10) & 0x7fff;
  uVar1 = *(ushort *)((int)param_1 + 10) & 0x7fff;
  uVar6 = (*(ushort *)((int)param_2 + 10) ^ *(ushort *)((int)param_1 + 10)) & 0x8000;
  uVar4 = uVar3 + uVar1;
  uStack_4 = 0;
  uStack_2 = 0;
  if (((0x7ffe < uVar1) || (0x7ffe < uVar3)) || (0xbffd < uVar4)) {
    param_1[1] = 0;
    *param_1 = 0;
    param_1[2] = (-(uint)(uVar6 != 0) & 0x80000000) + 0x7fff8000;
    return;
  }
  if (uVar4 < 0x3fc0) {
    param_1[2] = 0;
    param_1[1] = 0;
    *param_1 = 0;
    return;
  }
  if (((uVar1 == 0) && (uVar4 = uVar4 + 1, (param_1[2] & 0x7fffffffU) == 0)) &&
     ((param_1[1] == 0 && (*param_1 == 0)))) {
    *(undefined2 *)((int)param_1 + 10) = 0;
    return;
  }
  if (((uVar3 == 0) && (uVar4 = uVar4 + 1, (param_2[2] & 0x7fffffffU) == 0)) &&
     ((param_2[1] == 0 && (*param_2 == 0)))) {
    param_1[2] = 0;
    param_1[1] = 0;
    *param_1 = 0;
    return;
  }
  psStack_20 = &sStack_8;
  iStack_18 = 0;
  iVar5 = 5;
  do {
    if (0 < iVar5) {
      puVar8 = (ushort *)(param_2 + 2);
      puVar7 = (ushort *)(iStack_18 * 2 + (int)param_1);
      iStack_10 = iVar5;
      do {
        iVar2 = FUN_1000b830(*(undefined4 *)(psStack_20 + -2),(uint)*puVar8 * (uint)*puVar7,
                             psStack_20 + -2);
        if (iVar2 != 0) {
          *psStack_20 = *psStack_20 + 1;
        }
        puVar7 = puVar7 + 1;
        puVar8 = puVar8 + -1;
        iStack_10 = iStack_10 + -1;
      } while (iStack_10 != 0);
    }
    psStack_20 = psStack_20 + 1;
    iStack_18 = iStack_18 + 1;
    iVar5 = iVar5 + -1;
  } while (0 < iVar5);
  uVar4 = uVar4 + 0xc002;
  while ((0 < (short)uVar4 && ((uStack_2 & 0x8000) == 0))) {
    FUN_1000b8d0(&bStack_c);
    uVar4 = uVar4 - 1;
  }
  if ((short)uVar4 < 1) {
    uVar4 = uVar4 - 1;
    if ((short)uVar4 < 0) {
      iVar5 = -(int)(short)uVar4;
      uVar4 = uVar4 + (short)iVar5;
      do {
        if ((bStack_c & 1) != 0) {
          iStack_14 = iStack_14 + 1;
        }
        FUN_1000b900(&bStack_c);
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    if (iStack_14 != 0) {
      bStack_c = bStack_c | 1;
    }
  }
  if ((0x8000 < CONCAT11(uStack_b,bStack_c)) ||
     (iVar2 = CONCAT22(uStack_4,uStack_6), iVar5 = CONCAT22(sStack_8,uStack_a),
     (CONCAT22(uStack_a,CONCAT11(uStack_b,bStack_c)) & 0x1ffff) == 0x18000)) {
    if (CONCAT22(sStack_8,uStack_a) == -1) {
      iVar5 = 0;
      if (CONCAT22(uStack_4,uStack_6) == -1) {
        if (uStack_2 == 0xffff) {
          uStack_2 = 0x8000;
          uVar4 = uVar4 + 1;
          iVar2 = 0;
          iVar5 = 0;
        }
        else {
          uStack_2 = uStack_2 + 1;
          iVar2 = 0;
          iVar5 = 0;
        }
      }
      else {
        iVar2 = CONCAT22(uStack_4,uStack_6) + 1;
      }
    }
    else {
      iVar5 = CONCAT22(sStack_8,uStack_a) + 1;
      iVar2 = CONCAT22(uStack_4,uStack_6);
    }
  }
  sStack_8 = (short)((uint)iVar5 >> 0x10);
  uStack_a = (undefined2)iVar5;
  uStack_4 = (undefined2)((uint)iVar2 >> 0x10);
  uStack_6 = (undefined2)iVar2;
  if (0x7ffe < uVar4) {
    param_1[1] = 0;
    *param_1 = 0;
    param_1[2] = (-(uint)(uVar6 != 0) & 0x80000000) + 0x7fff8000;
    return;
  }
  *(undefined2 *)param_1 = uStack_a;
  *(uint *)((int)param_1 + 2) = CONCAT22(uStack_6,sStack_8);
  *(uint *)((int)param_1 + 6) = CONCAT22(uStack_2,uStack_4);
  *(ushort *)((int)param_1 + 10) = uVar4 | uVar6;
  return;
}
#undef bStack_c
#undef iStack_10
#undef iStack_14
#undef iStack_18
#undef psStack_20
#undef sStack_8
#undef uStack_2
#undef uStack_4
#undef uStack_6
#undef uStack_a
#undef uStack_b

#endif


/* ---- 0x1000d0c0  FUN_1000d0c0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_1000d0c0(undefined2 *param_1,uint param_2,int param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  undefined4 *puVar2;
  int iVar3;
  #define uStack_c (*(undefined2 *)(_frame + (0x20 - 0xc)))
  #define uStack_a (*(undefined4 *)(_frame + (0x20 - 0xa)))
  #define uStack_6 (*(undefined2 *)(_frame + (0x20 - 0x6)))
  #define uStack_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  iVar3 = IMG_ADDR(0x10013a80);
  if (param_2 != 0) {
    if ((int)param_2 < 0) {
      param_2 = -param_2;
      iVar3 = IMG_ADDR(0x10013be0);
    }
    if (param_3 == 0) {
      *param_1 = 0;
    }
    while (param_2 != 0) {
      iVar3 = iVar3 + 0x54;
      uVar1 = param_2 & 7;
      param_2 = (int)param_2 >> 3;
      if (uVar1 != 0) {
        puVar2 = (undefined4 *)(iVar3 + uVar1 * 0xc);
        if (0x7fff < *(ushort *)(iVar3 + uVar1 * 0xc)) {
          uStack_c = (undefined2)*puVar2;
          PIECE(uStack_a,0,2) = (undefined2)((uint)*puVar2 >> 0x10);
          PIECE(uStack_a,2,2) = (undefined2)puVar2[1];
          uStack_6 = (undefined2)((uint)puVar2[1] >> 0x10);
          uStack_4 = puVar2[2];
          uStack_a = CONCAT22(PIECE(uStack_a,2,2),(undefined2)uStack_a) + -1;
          puVar2 = (undefined4 *)&uStack_c;
        }
        FUN_1000ce00(param_1,puVar2);
      }
    }
  }
  return;
}
#undef uStack_4
#undef uStack_6
#undef uStack_a
#undef uStack_c

#endif


/* ---- 0x1000d150  FUN_1000d150 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_1000d150(int param_1)

{
  undefined4 uVar1;
  
  if ((*(byte *)(param_1 + 0xc) & 0x40) != 0) {
    *(undefined4 *)(param_1 + 0xc) = 0;
    return 0xffffffff;
  }
  FUN_100068b0(param_1);
  uVar1 = FUN_1000d190(param_1);
  FUN_10006920(param_1);
  return uVar1;
}
#endif


/* ---- 0x1000d190  FUN_1000d190 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_1000d190(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0xffffffff;
  if ((*(byte *)(param_1 + 0xc) & 0x83) != 0) {
    uVar2 = FUN_1000c650(param_1);
    FUN_1000dba0(param_1);
    iVar1 = FUN_1000daa0(*(undefined4 *)(param_1 + 0x10));
    if (iVar1 < 0) {
      *(undefined4 *)(param_1 + 0xc) = 0;
      return 0xffffffff;
    }
    if (*(int *)(param_1 + 0x1c) != 0) {
      FUN_10009510();
      *(undefined4 *)(param_1 + 0x1c) = 0;
    }
  }
  *(undefined4 *)(param_1 + 0xc) = 0;
  return uVar2;
}
#endif


/* ---- 0x1000d200  FUN_1000d200 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_1000d200(uint param_1)

{
  undefined4 uVar1;
  int *piVar2;
  undefined4 *puVar3;
  int iVar4;
  
  if (_DAT_10015ae0 <= param_1) {
LAB_1000d28c:
    puVar3 = (undefined4 *)FUN_1000cad0();
    *puVar3 = 9;
    return 0xffffffff;
  }
  iVar4 = (param_1 & 0x1f) * 0x24;
  if ((*(byte *)(*(int *)(&DAT_100159e0 + ((int)param_1 >> 5) * 4) + 4 + iVar4) & 1) == 0)
  goto LAB_1000d28c;
  FUN_1000d980(param_1);
  if ((*(byte *)(*(int *)(&DAT_100159e0 + ((int)param_1 >> 5) * 4) + 4 + iVar4) & 1) != 0) {
    uVar1 = FUN_1000d930(param_1);
    iVar4 = FlushFileBuffers(uVar1);
    if (iVar4 == 0) {
      iVar4 = GetLastError();
    }
    else {
      iVar4 = 0;
    }
    uVar1 = 0;
    if (iVar4 == 0) goto LAB_1000d27d;
    piVar2 = (int *)FUN_1000cae0();
    *piVar2 = iVar4;
  }
  puVar3 = (undefined4 *)FUN_1000cad0();
  *puVar3 = 9;
  uVar1 = 0xffffffff;
LAB_1000d27d:
  FUN_1000d9f0(param_1);
  return uVar1;
}
#endif


/* ---- 0x1000d2a0  FUN_1000d2a0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_1000d2a0(uint param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  if ((param_1 < _DAT_10015ae0) &&
     ((*(byte *)(*(int *)(&DAT_100159e0 + ((int)param_1 >> 5) * 4) + 4 + (param_1 & 0x1f) * 0x24) &
      1) != 0)) {
    FUN_1000d980(param_1);
    uVar1 = FUN_1000d320(param_1,param_2,param_3);
    FUN_1000d9f0(param_1);
    return uVar1;
  }
  puVar2 = (undefined4 *)FUN_1000cad0();
  *puVar2 = 9;
  puVar2 = (undefined4 *)FUN_1000cae0();
  *puVar2 = 0;
  return 0xffffffff;
}
#endif


/* ---- 0x1000d320  FUN_1000d320 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_1000d320(uint param_1,char *param_2,uint param_3)

{
  unsigned char _frame[0x430] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  char cVar2;
  char *pcVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  char *pcVar7;
  #define iStack_41c (*(int *)(_frame + (0x430 - 0x41c)))
  #define iStack_414 (*(int *)(_frame + (0x430 - 0x414)))
  #define iStack_410 (*(int *)(_frame + (0x430 - 0x410)))
  #define iStack_40c (*(int *)(_frame + (0x430 - 0x40c)))
  #define piStack_408 (*(int **)(_frame + (0x430 - 0x408)))
  #define acStack_404 (*(char (*)[1028])(_frame + (0x430 - 0x404)))
  
  iStack_41c = 0;
  iStack_40c = 0;
  if (param_3 == 0) {
    return 0;
  }
  piVar1 = (int *)(&DAT_100159e0 + ((int)param_1 >> 5) * 4);
  iVar6 = (param_1 & 0x1f) * 0x24;
  piStack_408 = piVar1;
  if ((*(byte *)(iVar6 + 4 + *piVar1) & 0x20) != 0) {
    FUN_1000da20(param_1,0,2);
  }
  if ((*(byte *)((undefined4 *)(*piVar1 + iVar6) + 1) & 0x80) == 0) {
    iVar4 = WriteFile(*(undefined4 *)(*piVar1 + iVar6),param_2,param_3,&iStack_410,0);
    if (iVar4 == 0) {
      iStack_414 = GetLastError();
    }
    else {
      iStack_41c = iStack_410;
      iStack_414 = 0;
    }
  }
  else {
    iStack_414 = 0;
    pcVar7 = param_2;
    if (param_3 != 0) {
      do {
        pcVar3 = acStack_404;
        do {
          if (param_3 <= (uint)((int)pcVar7 - (int)param_2)) break;
          cVar2 = *pcVar7;
          pcVar7 = pcVar7 + 1;
          if (cVar2 == '\n') {
            *pcVar3 = '\r';
            iStack_40c = iStack_40c + 1;
            pcVar3 = pcVar3 + 1;
          }
          *pcVar3 = cVar2;
          pcVar3 = pcVar3 + 1;
        } while ((int)pcVar3 - (int)acStack_404 < 0x400);
        iVar4 = WriteFile(*(undefined4 *)(iVar6 + *piStack_408),acStack_404,
                          (int)pcVar3 - (int)acStack_404,&iStack_410,0);
        if (iVar4 == 0) {
          iStack_414 = GetLastError();
          break;
        }
        iStack_41c = iStack_41c + iStack_410;
        if ((iStack_410 < (int)pcVar3 - (int)acStack_404) ||
           (param_3 <= (uint)((int)pcVar7 - (int)param_2))) break;
      } while( true );
    }
  }
  if (iStack_41c != 0) {
    return iStack_41c - iStack_40c;
  }
  if (iStack_414 == 0) {
    if (((*(byte *)(iVar6 + 4 + *piStack_408) & 0x40) != 0) && (*param_2 == '\x1a')) {
      return 0;
    }
    puVar5 = (undefined4 *)FUN_1000cad0();
    *puVar5 = 0x1c;
    puVar5 = (undefined4 *)FUN_1000cae0();
    *puVar5 = 0;
    return -1;
  }
  if (iStack_414 != 5) {
    FUN_1000ca50();
    return -1;
  }
  puVar5 = (undefined4 *)FUN_1000cad0();
  *puVar5 = 9;
  puVar5 = (undefined4 *)FUN_1000cae0();
  *puVar5 = 5;
  return -1;
}
#undef acStack_404
#undef iStack_40c
#undef iStack_410
#undef iStack_414
#undef iStack_41c
#undef piStack_408

#endif


/* ---- 0x1000d530  FUN_1000d530 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_1000d530(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 unaff_EBP;
  int unaff_ESI;
  undefined4 unaff_EDI;
  
  if (_DAT_10014994 == 0) {
    iVar1 = GetLocaleInfoW(0,1,0,0);
    if (iVar1 == 0) {
      iVar1 = GetLocaleInfoA(0,1,0,0);
      if (iVar1 == 0) {
        return 0;
      }
      _DAT_10014994 = 2;
    }
    else {
      _DAT_10014994 = 1;
    }
  }
  if (_DAT_10014994 == 1) {
    iVar1 = GetLocaleInfoW(param_1,param_2,param_3,param_4);
    return iVar1;
  }
  if (_DAT_10014994 != 2) {
    return _DAT_10014994;
  }
  iVar1 = GetLocaleInfoA(param_1,param_2,0,0);
  if (iVar1 != 0) {
    iVar2 = FUN_10009580(iVar1);
    if (iVar2 == 0) {
      return 0;
    }
    iVar1 = GetLocaleInfoA(param_1,param_2,iVar2,iVar1);
    if (iVar1 != 0) {
      if (unaff_ESI == 0) {
        iVar1 = MultiByteToWideChar(unaff_EBP,1,iVar2,0xffffffff,0,0);
        if (iVar1 != 0) {
          FUN_10009510();
          return iVar1;
        }
      }
      else {
        iVar1 = MultiByteToWideChar(unaff_EBP,1,iVar2,0xffffffff,unaff_EDI,unaff_ESI);
        if (iVar1 != 0) {
          FUN_10009510();
          return iVar1;
        }
      }
    }
    FUN_10009510();
    return 0;
  }
  return 0;
}
#endif


/* ---- 0x1000d660  FUN_1000d660 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_1000d660(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 unaff_EBP;
  int unaff_ESI;
  undefined4 unaff_EDI;
  
  if (_DAT_10014998 == 0) {
    iVar1 = GetLocaleInfoW(0,1,0,0);
    if (iVar1 == 0) {
      iVar1 = GetLocaleInfoA(0,1,0,0);
      if (iVar1 == 0) {
        return 0;
      }
      _DAT_10014998 = 2;
    }
    else {
      _DAT_10014998 = 1;
    }
  }
  if (_DAT_10014998 == 2) {
    iVar1 = GetLocaleInfoA(param_1,param_2,param_3,param_4);
    return iVar1;
  }
  if (_DAT_10014998 != 1) {
    return _DAT_10014998;
  }
  iVar1 = GetLocaleInfoW(param_1,param_2,0,0);
  if (iVar1 != 0) {
    iVar2 = FUN_10009580(iVar1 * 2);
    if (iVar2 == 0) {
      return 0;
    }
    iVar1 = GetLocaleInfoW(param_1,param_2,iVar2,iVar1);
    if (iVar1 != 0) {
      if (unaff_ESI == 0) {
        iVar1 = WideCharToMultiByte(unaff_EBP,0x220,iVar2,0xffffffff,0,0,0,0);
        if (iVar1 != 0) {
          FUN_10009510();
          return iVar1;
        }
      }
      else {
        iVar1 = WideCharToMultiByte(unaff_EBP,0x220,iVar2,0xffffffff,unaff_EDI,unaff_ESI,0,0);
        if (iVar1 != 0) {
          FUN_10009510();
          return iVar1;
        }
      }
    }
    FUN_10009510();
    return 0;
  }
  return 0;
}
#endif


/* ---- 0x1000d890  FUN_1000d890 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_1000d890(uint param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  
  if (param_1 < _DAT_10015ae0) {
    iVar1 = *(int *)(&DAT_100159e0 + ((int)param_1 >> 5) * 4);
    iVar3 = (param_1 & 0x1f) * 0x24;
    if (((*(byte *)(iVar1 + 4 + iVar3) & 1) != 0) && (*(int *)(iVar1 + iVar3) != -1)) {
      if (_DAT_1001440c == 1) {
        if (param_1 == 0) {
          uVar4 = 0xfffffff6;
        }
        else if (param_1 == 1) {
          uVar4 = 0xfffffff5;
        }
        else {
          if (param_1 != 2) goto LAB_1000d8f7;
          uVar4 = 0xfffffff4;
        }
        SetStdHandle(uVar4,0);
      }
LAB_1000d8f7:
      *(undefined4 *)(*(int *)(&DAT_100159e0 + ((int)param_1 >> 5) * 4) + iVar3) = 0xffffffff;
      return 0;
    }
  }
  puVar2 = (undefined4 *)FUN_1000cad0();
  *puVar2 = 9;
  puVar2 = (undefined4 *)FUN_1000cae0();
  *puVar2 = 0;
  return 0xffffffff;
}
#endif


/* ---- 0x1000d930  FUN_1000d930 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_1000d930(uint param_1)

{
  undefined4 *puVar1;
  
  if ((param_1 < _DAT_10015ae0) &&
     ((*(byte *)(*(int *)(&DAT_100159e0 + ((int)param_1 >> 5) * 4) + 4 + (param_1 & 0x1f) * 0x24) &
      1) != 0)) {
    return *(undefined4 *)
            (*(int *)(&DAT_100159e0 + ((int)param_1 >> 5) * 4) + (param_1 & 0x1f) * 0x24);
  }
  puVar1 = (undefined4 *)FUN_1000cad0();
  *puVar1 = 9;
  puVar1 = (undefined4 *)FUN_1000cae0();
  *puVar1 = 0;
  return 0xffffffff;
}
#endif


/* ---- 0x1000d980  FUN_1000d980 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_1000d980(uint param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = (param_1 & 0x1f) * 0x24;
  iVar1 = *(int *)(&DAT_100159e0 + ((int)param_1 >> 5) * 4) + iVar2;
  if (*(int *)(iVar1 + 8) == 0) {
    FUN_10006810(0x11);
    if (*(int *)(iVar1 + 8) == 0) {
      InitializeCriticalSection(iVar1 + 0xc);
      *(int *)(iVar1 + 8) = *(int *)(iVar1 + 8) + 1;
    }
    FUN_10006890();
  }
  EnterCriticalSection(*(int *)(&DAT_100159e0 + ((int)param_1 >> 5) * 4) + 0xc + iVar2);
  return;
}
#endif


/* ---- 0x1000d9f0  FUN_1000d9f0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_1000d9f0(uint param_1)

{
  LeaveCriticalSection
            (*(int *)(&DAT_100159e0 + ((int)param_1 >> 5) * 4) + 0xc + (param_1 & 0x1f) * 0x24);
  return;
}
#endif


/* ---- 0x1000da20  FUN_1000da20 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_1000da20(uint param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  
  iVar1 = FUN_1000d930(param_1);
  if (iVar1 == -1) {
    puVar2 = (undefined4 *)FUN_1000cad0();
    *puVar2 = 9;
    return -1;
  }
  iVar1 = SetFilePointer(iVar1,param_2,0,param_3);
  if (iVar1 == -1) {
    iVar3 = GetLastError();
  }
  else {
    iVar3 = 0;
  }
  if (iVar3 != 0) {
    FUN_1000ca50();
    return -1;
  }
  *(byte *)(*(int *)(&DAT_100159e0 + ((int)param_1 >> 5) * 4) + 4 + (param_1 & 0x1f) * 0x24) =
       *(byte *)(*(int *)(&DAT_100159e0 + ((int)param_1 >> 5) * 4) + 4 + (param_1 & 0x1f) * 0x24) &
       0xfd;
  return iVar1;
}
#endif


/* ---- 0x1000daa0  FUN_1000daa0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_1000daa0(uint param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  if ((param_1 < _DAT_10015ae0) &&
     ((*(byte *)(*(int *)(&DAT_100159e0 + ((int)param_1 >> 5) * 4) + 4 + (param_1 & 0x1f) * 0x24) &
      1) != 0)) {
    FUN_1000d980(param_1);
    uVar1 = FUN_1000db10(param_1);
    FUN_1000d9f0(param_1);
    return uVar1;
  }
  puVar2 = (undefined4 *)FUN_1000cad0();
  *puVar2 = 9;
  puVar2 = (undefined4 *)FUN_1000cae0();
  *puVar2 = 0;
  return 0xffffffff;
}
#endif


/* ---- 0x1000db10  FUN_1000db10 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_1000db10(uint param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_1000d930(param_1);
  if (iVar1 != -1) {
    if ((param_1 == 1) || (param_1 == 2)) {
      iVar1 = FUN_1000d930(1);
      iVar2 = FUN_1000d930(2);
      if (iVar1 == iVar2) goto LAB_1000db66;
    }
    uVar3 = FUN_1000d930(param_1);
    iVar1 = CloseHandle(uVar3);
    if (iVar1 == 0) {
      iVar1 = GetLastError();
      goto LAB_1000db68;
    }
  }
LAB_1000db66:
  iVar1 = 0;
LAB_1000db68:
  FUN_1000d890(param_1);
  *(undefined1 *)(*(int *)(&DAT_100159e0 + ((int)param_1 >> 5) * 4) + 4 + (param_1 & 0x1f) * 0x24) =
       0;
  if (iVar1 != 0) {
    FUN_1000ca50();
    return 0xffffffff;
  }
  return 0;
}
#endif


/* ---- 0x1000dba0  FUN_1000dba0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_1000dba0(undefined4 *param_1)

{
  if (((param_1[3] & 0x83) != 0) && ((param_1[3] & 8) != 0)) {
    FUN_10009510();
    param_1[3] = param_1[3] & 0xfffffbf7;
    *param_1 = 0;
    param_1[2] = 0;
    param_1[1] = 0;
  }
  return;
}
#endif

