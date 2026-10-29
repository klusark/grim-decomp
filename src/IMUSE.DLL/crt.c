/* IMUSE.DLL :: crt.c
 * functions 0x1000b940 .. 0x10012f20 (65 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x1000b940  fseek ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl fseek(int *param_1,int param_2,int param_3)

{
  int iVar1;
  
  _lock_file((uint)param_1);
  iVar1 = _fseek_lk(param_1,param_2,param_3);
  _unlock_file((uint)param_1);
  return iVar1;
}

/* ---- 0x1000b980  _fseek_lk ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl _fseek_lk(int *param_1,int param_2,int param_3)

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

/* ---- 0x1000bb10  fclose ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl fclose(int *param_1)

{
  undefined4 uVar1;
  
  if ((*(byte *)(param_1 + 3) & 0x40) != 0) {
    param_1[3] = 0;
    return 0xffffffff;
  }
  _lock_file((uint)param_1);
  uVar1 = _fclose_lk(param_1);
  _unlock_file((uint)param_1);
  return uVar1;
}

/* ---- 0x1000bb50  _fclose_lk ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl _fclose_lk(int *param_1)

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

/* ---- 0x1000bbc0  fwrite ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl fwrite(char *param_1,uint param_2,uint param_3,int *param_4)

{
  uint uVar1;
  
  _lock_file((uint)param_4);
  uVar1 = _fwrite_lk(param_1,param_2,param_3,param_4);
  _unlock_file((uint)param_4);
  return uVar1;
}

/* ---- 0x1000bc00  _fwrite_lk ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl _fwrite_lk(char *param_1,uint param_2,uint param_3,int *param_4)

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

/* ---- 0x1000bd50  strchr ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

char * __cdecl strchr(char *param_1,char param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  
  iVar2 = -1;
  do {
    pcVar4 = param_1;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar4 = param_1 + 1;
    cVar1 = *param_1;
    param_1 = pcVar4;
  } while (cVar1 != '\0');
  iVar2 = -(iVar2 + 1);
  pcVar4 = pcVar4 + -1;
  do {
    pcVar3 = pcVar4;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar3 = pcVar4 + -1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar3;
  } while (param_2 != cVar1);
  pcVar3 = pcVar3 + 1;
  if (*pcVar3 != param_2) {
    pcVar3 = (char *)0x0;
  }
  return pcVar3;
}

/* ---- 0x1000bd80  strncpy ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint * __cdecl strncpy(uint *param_1,uint *param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  char cVar3;
  uint uVar4;
  uint *puVar5;
  
  if (param_3 == 0) {
    return param_1;
  }
  puVar5 = param_1;
  if (((uint)param_2 & 3) != 0) {
    while( true ) {
      uVar4 = *param_2;
      param_2 = (uint *)((int)param_2 + 1);
      *(char *)puVar5 = (char)uVar4;
      puVar5 = (uint *)((int)puVar5 + 1);
      param_3 = param_3 - 1;
      if (param_3 == 0) {
        return param_1;
      }
      if ((char)uVar4 == '\0') break;
      if (((uint)param_2 & 3) == 0) {
        uVar4 = param_3 >> 2;
        goto joined_r0x1000bdbe;
      }
    }
    do {
      if (((uint)puVar5 & 3) == 0) {
        uVar4 = param_3 >> 2;
        cVar3 = '\0';
        if (uVar4 == 0) goto LAB_1000bdfb;
        goto LAB_1000be69;
      }
      *(char *)puVar5 = '\0';
      puVar5 = (uint *)((int)puVar5 + 1);
      param_3 = param_3 - 1;
    } while (param_3 != 0);
    return param_1;
  }
  uVar4 = param_3 >> 2;
  if (uVar4 != 0) {
    do {
      uVar1 = *param_2;
      uVar2 = *param_2;
      param_2 = param_2 + 1;
      if (((uVar1 ^ 0xffffffff ^ uVar1 + 0x7efefeff) & 0x81010100) != 0) {
        if ((char)uVar2 == '\0') {
          *puVar5 = 0;
joined_r0x1000be65:
          while( true ) {
            uVar4 = uVar4 - 1;
            puVar5 = puVar5 + 1;
            if (uVar4 == 0) break;
LAB_1000be69:
            *puVar5 = 0;
          }
          cVar3 = '\0';
          param_3 = param_3 & 3;
          if (param_3 != 0) goto LAB_1000bdfb;
          return param_1;
        }
        if ((char)(uVar2 >> 8) == '\0') {
          *puVar5 = uVar2 & 0xff;
          goto joined_r0x1000be65;
        }
        if ((uVar2 & 0xff0000) == 0) {
          *puVar5 = uVar2 & 0xffff;
          goto joined_r0x1000be65;
        }
        if ((uVar2 & 0xff000000) == 0) {
          *puVar5 = uVar2;
          goto joined_r0x1000be65;
        }
      }
      *puVar5 = uVar2;
      puVar5 = puVar5 + 1;
      uVar4 = uVar4 - 1;
joined_r0x1000bdbe:
    } while (uVar4 != 0);
    param_3 = param_3 & 3;
    if (param_3 == 0) {
      return param_1;
    }
  }
  do {
    cVar3 = (char)*param_2;
    param_2 = (uint *)((int)param_2 + 1);
    *(char *)puVar5 = cVar3;
    puVar5 = (uint *)((int)puVar5 + 1);
    if (cVar3 == '\0') {
      while (param_3 = param_3 - 1, param_3 != 0) {
LAB_1000bdfb:
        *(char *)puVar5 = cVar3;
        puVar5 = (uint *)((int)puVar5 + 1);
      }
      return param_1;
    }
    param_3 = param_3 - 1;
  } while (param_3 != 0);
  return param_1;
}

/* ---- 0x1000be80  _stricmp ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl _stricmp(byte *param_1,byte *param_2)

{
  bool bVar1;
  int iVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  char cVar6;
  uint uVar8;
  uint uVar9;
  uint uVar7;
  
  iVar2 = _DAT_100337f0;
  if (DAT_10032fe0 == 0) {
    bVar5 = 0xff;
    do {
      do {
        cVar6 = '\0';
        if (bVar5 == 0) goto LAB_1000bece;
        bVar5 = *param_2;
        param_2 = param_2 + 1;
        bVar4 = *param_1;
        param_1 = param_1 + 1;
      } while (bVar4 == bVar5);
      bVar3 = bVar5 + 0xbf + (-((byte)(bVar5 + 0xbf) < 0x1a) & 0x20U) + 0x41;
      bVar4 = bVar4 + 0xbf;
      bVar5 = bVar4 + (-(bVar4 < 0x1a) & 0x20U) + 0x41;
    } while (bVar5 == bVar3);
    cVar6 = (bVar5 < bVar3) * -2 + '\x01';
LAB_1000bece:
    uVar7 = (uint)cVar6;
  }
  else {
    LOCK();
    _DAT_100337f0 = _DAT_100337f0 + 1;
    UNLOCK();
    bVar1 = 0 < DAT_100337ec;
    if (bVar1) {
      LOCK();
      UNLOCK();
      _DAT_100337f0 = iVar2;
      _lock(0x13);
    }
    uVar9 = (uint)bVar1;
    uVar7 = 0xff;
    uVar8 = 0;
    do {
      do {
        if ((char)uVar7 == '\0') goto LAB_1000bf2f;
        bVar5 = *param_2;
        uVar7 = CONCAT31((int3)(uVar7 >> 8),bVar5);
        param_2 = param_2 + 1;
        bVar4 = *param_1;
        uVar8 = CONCAT31((int3)(uVar8 >> 8),bVar4);
        param_1 = param_1 + 1;
      } while (bVar5 == bVar4);
      uVar8 = _tolower_lk(uVar8);
      uVar7 = _tolower_lk(uVar7);
    } while ((byte)uVar8 == (byte)uVar7);
    uVar8 = (uint)((byte)uVar8 < (byte)uVar7);
    uVar7 = (1 - uVar8) - (uint)(uVar8 != 0);
LAB_1000bf2f:
    if (uVar9 == 0) {
      LOCK();
      _DAT_100337f0 = _DAT_100337f0 + -1;
      UNLOCK();
    }
    else {
      _unlock(0x13);
    }
  }
  return uVar7;
}

/* ---- 0x1000bf50  atol ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl atol(byte *param_1)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  byte *pbVar6;
  
  while( true ) {
    if (DAT_1001f21c < 2) {
      uVar2 = (byte)PTR_DAT_1001f010[(uint)*param_1 * 2] & 8;
    }
    else {
      uVar2 = _isctype((uint)*param_1,8);
    }
    if (uVar2 == 0) break;
    param_1 = param_1 + 1;
  }
  uVar2 = (uint)*param_1;
  pbVar6 = param_1 + 1;
  if ((uVar2 == 0x2d) || (uVar4 = uVar2, uVar2 == 0x2b)) {
    uVar4 = (uint)*pbVar6;
    pbVar6 = param_1 + 2;
  }
  iVar5 = 0;
  while( true ) {
    if (DAT_1001f21c < 2) {
      uVar3 = (byte)PTR_DAT_1001f010[uVar4 * 2] & 4;
    }
    else {
      uVar3 = _isctype(uVar4,4);
    }
    if (uVar3 == 0) break;
    bVar1 = *pbVar6;
    pbVar6 = pbVar6 + 1;
    iVar5 = (uVar4 - 0x30) + iVar5 * 10;
    uVar4 = (uint)bVar1;
  }
  if (uVar2 == 0x2d) {
    iVar5 = -iVar5;
  }
  return iVar5;
}

/* ---- 0x1000bff0  atoi ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl atoi(byte *param_1)

{
  int iVar1;
  
  iVar1 = atol(param_1);
  return iVar1;
}

/* ---- 0x1000c000  bsearch ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl bsearch(undefined4 param_1,uint param_2,uint param_3,int param_4,undefined *param_5)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar3 = (param_3 - 1) * param_4 + param_2;
  bVar1 = param_2 <= uVar3;
  uVar4 = param_2;
  param_2 = uVar3;
  if (bVar1) {
    while (uVar3 = param_3 >> 1, uVar3 != 0) {
      uVar5 = uVar3;
      if ((param_3 & 1) == 0) {
        uVar5 = uVar3 - 1;
      }
      uVar5 = param_4 * uVar5 + uVar4;
      iVar2 = (*(code *)param_5)(param_1,uVar5);
      if (iVar2 == 0) {
        return uVar5;
      }
      if (iVar2 < 0) {
        param_2 = uVar5 - param_4;
        if ((param_3 & 1) == 0) {
          uVar3 = uVar3 - 1;
        }
      }
      else {
        uVar4 = uVar5 + param_4;
      }
      param_3 = uVar3;
      if (param_2 < uVar4) {
        return 0;
      }
    }
    if (param_3 != 0) {
      iVar2 = (*(code *)param_5)(param_1,uVar4);
      return ~-(uint)(iVar2 != 0) & uVar4;
    }
  }
  return 0;
}

/* ---- 0x1000c350  entry ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __stdcall entry(int a1,int a2,int a3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 1;
  if ((a2 == 0) && (_DAT_10032f54 == 0)) {
    return 0;
  }
  if ((a2 != 1) && (a2 != 2)) {
LAB_1000c3ae:
    iVar1 = FUN_1000fa20(a1,a2,a3);
    if ((a2 == 1) && (iVar1 == 0)) {
      FUN_1000c230(a1,0,a3);
    }
    if ((a2 == 0) || (a2 == 3)) {
      iVar2 = FUN_1000c230(a1,a2,a3);
      if (iVar2 == 0) {
        iVar1 = 0;
      }
      if ((iVar1 != 0) && (_DAT_10034808 != (code *)0x0)) {
        iVar1 = (*_DAT_10034808)(a1,a2,a3);
      }
    }
    return iVar1;
  }
  if (_DAT_10034808 != (code *)0x0) {
    iVar1 = (*_DAT_10034808)(a1,a2,a3);
  }
  if (iVar1 != 0) {
    iVar1 = FUN_1000c230(a1,a2,a3);
    if (iVar1 != 0) goto LAB_1000c3ae;
  }
  return 0;
}

/* ---- 0x1000c400  _amsg_exit ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _amsg_exit(int param_1)

{
  if ((DAT_10032f60 == 1) || ((DAT_10032f60 == 0 && (DAT_10032f64 == 1)))) {
    _FF_MSGBANNER();
  }
  _NMSG_WRITE(param_1);
  (*(code *)PTR_exit_1001e9e0)(0xff);
  return;
}

/* ---- 0x1000c4f0  _lock ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _lock(int param_1)

{
  undefined *a1;
  
  if (*(int *)(&DAT_1001e9e8 + param_1 * 4) == 0) {
    a1 = (undefined *)malloc(0x18);
    if (a1 == (undefined *)0x0) {
      _amsg_exit(0x11);
    }
    _lock(0x11);
    if (*(int *)(&DAT_1001e9e8 + param_1 * 4) == 0) {
      InitializeCriticalSection((int)a1);
      *(undefined **)(&DAT_1001e9e8 + param_1 * 4) = a1;
    }
    else {
      free(a1);
    }
    _unlock(0x11);
  }
  EnterCriticalSection(*(int *)(&DAT_1001e9e8 + param_1 * 4));
  return;
}

/* ---- 0x1000c570  _unlock ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _unlock(int param_1)

{
  LeaveCriticalSection(*(int *)(&DAT_1001e9e8 + param_1 * 4));
  return;
}

/* ---- 0x1000c590  _lock_file ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _lock_file(uint param_1)

{
  if ((IMG_ADDR(0x1001eaaf) < param_1) && (param_1 < IMG_ADDR(0x1001ed11))) {
    _lock(((int)(param_1 + 0xeffe1550) >> 5) + 0x1c);
    return;
  }
  EnterCriticalSection(param_1 + 0x20);
  return;
}

/* ---- 0x1000c600  _unlock_file ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _unlock_file(uint param_1)

{
  if ((IMG_ADDR(0x1001eaaf) < param_1) && (param_1 < IMG_ADDR(0x1001ed11))) {
    _unlock(((int)(param_1 + 0xeffe1550) >> 5) + 0x1c);
    return;
  }
  LeaveCriticalSection(param_1 + 0x20);
  return;
}

/* ---- 0x1000d210  _flsbuf ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl _flsbuf(uint param_1,int *param_2)

{
  uint uVar1;
  char *pcVar2;
  int *piVar3;
  byte bVar4;
  undefined3 extraout_var;
  int *piVar5;
  uint uVar6;
  uint uVar7;
  
  piVar3 = param_2;
  uVar7 = param_2[3];
  uVar1 = param_2[4];
  if (((uVar7 & 0x82) == 0) || ((uVar7 & 0x40) != 0)) {
LAB_1000d333:
    param_2[3] = uVar7 | 0x20;
    return 0xffffffff;
  }
  uVar6 = 0;
  if ((uVar7 & 1) != 0) {
    param_2[1] = 0;
    if ((uVar7 & 0x10) == 0) goto LAB_1000d333;
    *param_2 = param_2[2];
    param_2[3] = uVar7 & 0xfffffffe;
  }
  uVar7 = param_2[3];
  param_2[1] = 0;
  param_2[3] = uVar7 & 0xffffffef | 2;
  if ((uVar7 & 0x10c) == 0) {
    if ((param_2 == (int *)&DAT_1001ead0) || (param_2 == (int *)&DAT_1001eaf0)) {
      bVar4 = _isatty(uVar1);
      if (CONCAT31(extraout_var,bVar4) != 0) goto LAB_1000d283;
    }
    _getbuf(piVar3);
  }
LAB_1000d283:
  if ((piVar3[3] & 0x108U) == 0) {
    uVar7 = 1;
    uVar6 = _write(uVar1,(char *)&param_1,1);
  }
  else {
    pcVar2 = (char *)piVar3[2];
    uVar7 = *piVar3 - (int)pcVar2;
    *piVar3 = (int)(pcVar2 + 1);
    piVar3[1] = piVar3[6] + -1;
    if ((int)uVar7 < 1) {
      if (uVar1 == 0xffffffff) {
        piVar5 = (int *)&DAT_1001f238;
      }
      else {
        piVar5 = (&PTR_100336e0)[(int)uVar1 >> 5] + (uVar1 & 0x1f) * 9;
      }
      if ((*(byte *)(piVar5 + 1) & 0x20) != 0) {
        _lseek(uVar1,0,2);
      }
      *(undefined1 *)piVar3[2] = (undefined1)param_1;
    }
    else {
      uVar6 = _write(uVar1,pcVar2,uVar7);
      *(undefined1 *)piVar3[2] = (undefined1)param_1;
    }
  }
  if (uVar6 != uVar7) {
    piVar3[3] = piVar3[3] | 0x20;
    return 0xffffffff;
  }
  return param_1 & 0xff;
}

/* ---- 0x1000d340  _dosmaperr ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _dosmaperr(undefined *param_1)

{
  int *piVar1;
  undefined **ppuVar2;
  int iVar3;
  
  piVar1 = __doserrno();
  iVar3 = 0;
  *piVar1 = (int)param_1;
  ppuVar2 = (undefined **)&DAT_1001ed30;
  do {
    if (param_1 == *ppuVar2) {
      piVar1 = _errno();
      *piVar1 = *(int *)(iVar3 * 8 + IMG_ADDR(0x1001ed34));
      return;
    }
    ppuVar2 = ppuVar2 + 2;
    iVar3 = iVar3 + 1;
  } while (ppuVar2 < &PTR_FUN_1001ee98);
  if (((undefined *)0x12 < param_1) && (param_1 < (undefined *)0x25)) {
    piVar1 = _errno();
    *piVar1 = 0xd;
    return;
  }
  if (((undefined *)0xbb < param_1) && (param_1 < (undefined *)0xcb)) {
    piVar1 = _errno();
    *piVar1 = 8;
    return;
  }
  piVar1 = _errno();
  *piVar1 = 0x16;
  return;
}

/* ---- 0x1000d3c0  _errno ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int * _errno(void)

{
  int *piVar1;
  
  piVar1 = _getptd();
  return piVar1 + 2;
}

/* ---- 0x1000d3d0  __doserrno ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int * __doserrno(void)

{
  int *piVar1;
  
  piVar1 = _getptd();
  return piVar1 + 3;
}

/* ---- 0x1000d3e0  _lseek ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl _lseek(uint param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int *piVar2;
  
  if ((param_1 < DAT_100337e0) &&
     ((*(byte *)((&PTR_100336e0)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) & 1) != 0)) {
    _lock_fhandle(param_1);
    iVar1 = _lseek_lk(param_1,param_2,param_3);
    _unlock_fhandle(param_1);
    return iVar1;
  }
  piVar2 = _errno();
  *piVar2 = 9;
  piVar2 = __doserrno();
  *piVar2 = 0;
  return -1;
}

/* ---- 0x1000d460  _lseek_lk ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl _lseek_lk(uint param_1,int param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  undefined *puVar3;
  
  iVar1 = _get_osfhandle(param_1);
  if (iVar1 == -1) {
    piVar2 = _errno();
    *piVar2 = 9;
    return -1;
  }
  iVar1 = SetFilePointer(iVar1,param_2,0,param_3);
  if (iVar1 == -1) {
    puVar3 = (undefined *)GetLastError();
  }
  else {
    puVar3 = (undefined *)0x0;
  }
  if (puVar3 != (undefined *)0x0) {
    _dosmaperr(puVar3);
    return -1;
  }
  *(byte *)((&PTR_100336e0)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) =
       *(byte *)((&PTR_100336e0)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) & 0xfd;
  return iVar1;
}

/* ---- 0x1000d520  _flush ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl _flush(int *param_1)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  
  uVar3 = 0;
  if ((((byte)param_1[3] & 3) == 2) && ((param_1[3] & 0x108U) != 0)) {
    uVar4 = *param_1 - param_1[2];
    if (0 < (int)uVar4) {
      uVar2 = _write(param_1[4],(char *)param_1[2],uVar4);
      uVar1 = param_1[3];
      if (uVar2 == uVar4) {
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

/* ---- 0x1000d660  _ftell_lk ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl _ftell_lk(undefined4 *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint uVar2;
  char *pcVar3;
  int iVar4;
  char *pcVar5;
  int *piVar6;
  char *pcVar7;
  #define local_8 (*(int *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  uVar1 = param_1[4];
  if ((int)param_1[1] < 0) {
    param_1[1] = 0;
  }
  local_4 = _lseek(uVar1,0,1);
  if (local_4 < 0) {
    return -1;
  }
  uVar2 = param_1[3];
  if ((uVar2 & 0x108) == 0) {
    return local_4 - param_1[1];
  }
  pcVar7 = (char *)*param_1;
  pcVar3 = (char *)param_1[2];
  local_8 = (int)pcVar7 - (int)pcVar3;
  if ((uVar2 & 3) == 0) {
    if ((uVar2 & 0x80) == 0) {
      piVar6 = _errno();
      *piVar6 = 0x16;
      return -1;
    }
  }
  else {
    pcVar5 = pcVar3;
    if ((*(byte *)((&PTR_100336e0)[(int)uVar1 >> 5] + (uVar1 & 0x1f) * 9 + 1) & 0x80) != 0) {
      for (; pcVar5 < pcVar7; pcVar5 = pcVar5 + 1) {
        if (*pcVar5 == '\n') {
          local_8 = local_8 + 1;
        }
      }
    }
  }
  if (local_4 == 0) {
    return local_8;
  }
  if ((*(byte *)(param_1 + 3) & 1) == 0) goto LAB_1000d7d7;
  if (param_1[1] == 0) {
    return local_4;
  }
  pcVar7 = pcVar7 + (param_1[1] - (int)pcVar3);
  if ((*(byte *)((&PTR_100336e0)[(int)uVar1 >> 5] + (uVar1 & 0x1f) * 9 + 1) & 0x80) != 0) {
    iVar4 = _lseek(uVar1,0,2);
    if (iVar4 == local_4) {
      pcVar5 = (char *)param_1[2];
      pcVar3 = pcVar5 + (int)pcVar7;
      for (; pcVar5 < pcVar3; pcVar5 = pcVar5 + 1) {
        if (*pcVar5 == '\n') {
          pcVar7 = pcVar7 + 1;
        }
      }
      if ((param_1[3] & 0x2000) != 0) {
LAB_1000d7ce:
        pcVar7 = pcVar7 + 1;
      }
    }
    else {
      _lseek(uVar1,local_4,0);
      if (((pcVar7 < (char *)0x201) && ((param_1[3] & 8) != 0)) && ((param_1[3] & 0x400) == 0)) {
        pcVar7 = (char *)0x200;
      }
      else {
        pcVar7 = (char *)param_1[6];
      }
      if ((*(byte *)((&PTR_100336e0)[(int)uVar1 >> 5] + (uVar1 & 0x1f) * 9 + 1) & 4) != 0)
      goto LAB_1000d7ce;
    }
  }
  local_4 = local_4 - (int)pcVar7;
LAB_1000d7d7:
  return local_4 + local_8;
}
#undef local_4
#undef local_8


/* ---- 0x1000e0c0  free ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl free(undefined *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined *a3;
  byte *pbVar1;
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  a3 = param_1;
  if (param_1 != (undefined *)0x0) {
    _lock(9);
    pbVar1 = (byte *)__sbh_find_block(a3,&local_4,(uint *)&param_1);
    if (pbVar1 != (byte *)0x0) {
      __sbh_free_block(local_4,(int)param_1,pbVar1);
      _unlock(9);
      return;
    }
    _unlock(9);
    HeapFree(DAT_100336c0,0,(int)a3);
  }
  return;
}
#undef local_4


/* ---- 0x1000e130  _close ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl _close(uint param_1)

{
  undefined4 uVar1;
  int *piVar2;
  
  if ((param_1 < DAT_100337e0) &&
     ((*(byte *)((&PTR_100336e0)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) & 1) != 0)) {
    _lock_fhandle(param_1);
    uVar1 = _close_lk(param_1);
    _unlock_fhandle(param_1);
    return uVar1;
  }
  piVar2 = _errno();
  *piVar2 = 9;
  piVar2 = __doserrno();
  *piVar2 = 0;
  return 0xffffffff;
}

/* ---- 0x1000e1a0  _close_lk ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl _close_lk(uint param_1)

{
  int iVar1;
  int iVar2;
  undefined *puVar3;
  
  iVar1 = _get_osfhandle(param_1);
  if (iVar1 != -1) {
    if ((param_1 == 1) || (param_1 == 2)) {
      iVar1 = _get_osfhandle(1);
      iVar2 = _get_osfhandle(2);
      if (iVar1 == iVar2) goto LAB_1000e1f6;
    }
    iVar1 = _get_osfhandle(param_1);
    iVar1 = CloseHandle(iVar1);
    if (iVar1 == 0) {
      puVar3 = (undefined *)GetLastError();
      goto LAB_1000e1f8;
    }
  }
LAB_1000e1f6:
  puVar3 = (undefined *)0x0;
LAB_1000e1f8:
  _free_osfhnd(param_1);
  *(undefined1 *)((&PTR_100336e0)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) = 0;
  if (puVar3 != (undefined *)0x0) {
    _dosmaperr(puVar3);
    return 0xffffffff;
  }
  return 0;
}

/* ---- 0x1000e230  _freebuf ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _freebuf(undefined4 *param_1)

{
  if (((param_1[3] & 0x83) != 0) && ((param_1[3] & 8) != 0)) {
    free((undefined *)param_1[2]);
    param_1[3] = param_1[3] & 0xfffffbf7;
    *param_1 = 0;
    param_1[2] = 0;
    param_1[1] = 0;
  }
  return;
}

/* ---- 0x1000e270  _write ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl _write(uint param_1,char *param_2,uint param_3)

{
  int iVar1;
  int *piVar2;
  
  if ((param_1 < DAT_100337e0) &&
     ((*(byte *)((&PTR_100336e0)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) & 1) != 0)) {
    _lock_fhandle(param_1);
    iVar1 = _write_lk(param_1,param_2,param_3);
    _unlock_fhandle(param_1);
    return iVar1;
  }
  piVar2 = _errno();
  *piVar2 = 9;
  piVar2 = __doserrno();
  *piVar2 = 0;
  return -1;
}

/* ---- 0x1000e2f0  _write_lk ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl _write_lk(uint param_1,char *param_2,uint param_3)

{
  unsigned char _frame[0x430] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int **ppiVar1;
  char cVar2;
  uint uVar3;
  char *pcVar4;
  int iVar5;
  int *piVar6;
  char *pcVar7;
  #define local_41c (*(int *)(_frame + (0x430 - 0x41c)))
  #define local_414 (*(undefined **)(_frame + (0x430 - 0x414)))
  #define local_410 (*(int *)(_frame + (0x430 - 0x410)))
  #define local_40c (*(int *)(_frame + (0x430 - 0x40c)))
  #define local_408 (*(int ***)(_frame + (0x430 - 0x408)))
  #define local_404 (*(char (*)[1028])(_frame + (0x430 - 0x404)))
  
  local_41c = 0;
  local_40c = 0;
  if (param_3 == 0) {
    return 0;
  }
  ppiVar1 = &PTR_100336e0 + ((int)param_1 >> 5);
  uVar3 = param_1 & 0x1f;
  local_408 = ppiVar1;
  if ((*(byte *)(*ppiVar1 + uVar3 * 9 + 1) & 0x20) != 0) {
    _lseek_lk(param_1,0,2);
  }
  if ((*(byte *)(*ppiVar1 + uVar3 * 9 + 1) & 0x80) == 0) {
    iVar5 = WriteFile((*ppiVar1)[uVar3 * 9],(int)param_2,param_3,(int)&local_410,0);
    if (iVar5 == 0) {
      local_414 = (undefined *)GetLastError();
    }
    else {
      local_41c = local_410;
      local_414 = (undefined *)0x0;
    }
  }
  else {
    local_414 = (undefined *)0x0;
    pcVar7 = param_2;
    if (param_3 != 0) {
      do {
        pcVar4 = local_404;
        do {
          if (param_3 <= (uint)((int)pcVar7 - (int)param_2)) break;
          cVar2 = *pcVar7;
          pcVar7 = pcVar7 + 1;
          if (cVar2 == '\n') {
            *pcVar4 = '\r';
            local_40c = local_40c + 1;
            pcVar4 = pcVar4 + 1;
          }
          *pcVar4 = cVar2;
          pcVar4 = pcVar4 + 1;
        } while ((int)pcVar4 - (int)local_404 < 0x400);
        iVar5 = WriteFile((*local_408)[uVar3 * 9],(int)local_404,(int)pcVar4 - (int)local_404,
                          (int)&local_410,0);
        if (iVar5 == 0) {
          local_414 = (undefined *)GetLastError();
          break;
        }
        local_41c = local_41c + local_410;
        if ((local_410 < (int)pcVar4 - (int)local_404) ||
           (param_3 <= (uint)((int)pcVar7 - (int)param_2))) break;
      } while( true );
    }
  }
  if (local_41c != 0) {
    return local_41c - local_40c;
  }
  if (local_414 == (undefined *)0x0) {
    if (((*(byte *)(*local_408 + uVar3 * 9 + 1) & 0x40) != 0) && (*param_2 == '\x1a')) {
      return 0;
    }
    piVar6 = _errno();
    *piVar6 = 0x1c;
    piVar6 = __doserrno();
    *piVar6 = 0;
    return -1;
  }
  if (local_414 != (undefined *)0x5) {
    _dosmaperr(local_414);
    return -1;
  }
  piVar6 = _errno();
  *piVar6 = 9;
  piVar6 = __doserrno();
  *piVar6 = 5;
  return -1;
}
#undef local_404
#undef local_408
#undef local_40c
#undef local_410
#undef local_414
#undef local_41c


/* ---- 0x1000e5a0  _tolower_lk ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl _tolower_lk(uint param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint uVar2;
  int iVar3;
  #define local_8 (*(uint (*)[2])(_frame + (0x20 - 0x8)))
  
  uVar1 = param_1;
  if (DAT_10032fe0 == 0) {
    if ((0x40 < (int)param_1) && ((int)param_1 < 0x5b)) {
      return param_1 + 0x20;
    }
  }
  else {
    if ((int)param_1 < 0x100) {
      if (DAT_1001f21c < 2) {
        uVar2 = (byte)PTR_DAT_1001f010[param_1 * 2] & 1;
      }
      else {
        uVar2 = _isctype(param_1,1);
      }
      if (uVar2 == 0) {
        return uVar1;
      }
    }
    uVar2 = param_1;
    if ((PTR_DAT_1001f010[((int)uVar1 >> 8 & 0xffU) * 2 + 1] & 0x80) == 0) {
      PIECE(param_1,0,2) = (ushort)(byte)uVar1;
      iVar3 = 1;
    }
    else {
      PIECE(param_1,0,2) = CONCAT11((byte)uVar1,(char)(uVar1 >> 8));
      PIECE(param_1,3,1) = SUB41(uVar2,3);
      PIECE(param_1,0,3) = (uint3)(ushort)param_1;
      iVar3 = 2;
    }
    iVar3 = __crtLCMapStringA(DAT_10032fe0,0x100,(char *)&param_1,iVar3,local_8,3,0,1);
    if (iVar3 == 0) {
      return uVar1;
    }
    if (iVar3 == 1) {
      return local_8[0] & 0xff;
    }
    param_1 = (local_8[0] >> 8 & 0xff) << 8 | local_8[0] & 0xff;
  }
  return param_1;
}
#undef local_8


/* ---- 0x1000e6a0  _isctype ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl _isctype(int param_1,uint param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  int iVar2;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar2 = param_1;
  if (param_1 + 1U < 0x101) {
    return *(ushort *)(PTR_DAT_1001f010 + param_1 * 2) & param_2;
  }
  if ((PTR_DAT_1001f010[(param_1 >> 8 & 0xffU) * 2 + 1] & 0x80) == 0) {
    PIECE(param_1,0,2) = (ushort)(byte)param_1;
    uVar1 = 1;
  }
  else {
    PIECE(param_1,0,2) = CONCAT11((byte)param_1,(char)((uint)param_1 >> 8));
    PIECE(param_1,3,1) = SUB41(iVar2,3);
    PIECE(param_1,0,3) = (uint3)(ushort)param_1;
    uVar1 = 2;
  }
  iVar2 = __crtGetStringTypeA(1,&param_1,uVar1,&local_4,0,0,1);
  if (iVar2 == 0) {
    return 0;
  }
  return local_4 & 0xffff & param_2;
}
#undef local_4


/* ---- 0x1000e780  __crtLCMapStringA ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl
__crtLCMapStringA(int param_1,uint param_2,char *param_3,int param_4,int param_5,int param_6,
                 uint param_7,int param_8)

{
  int iVar1;
  int iVar2;
  undefined *a5;
  
  if (DAT_10033004 == 0) {
    iVar1 = LCMapStringW(0,0x100,IMG_ADDR(0x100154b8),1,0,0);
    if (iVar1 == 0) {
      iVar1 = LCMapStringA(0,0x100,IMG_ADDR(0x100154b4),1,0,0);
      if (iVar1 == 0) {
        return 0;
      }
      DAT_10033004 = 2;
    }
    else {
      DAT_10033004 = 1;
    }
  }
  iVar1 = param_4;
  if (0 < param_4) {
    iVar1 = _strncnt(param_3,param_4);
  }
  if (DAT_10033004 == 2) {
    iVar1 = LCMapStringA(param_1,param_2,(int)param_3,iVar1,param_5,param_6);
    return iVar1;
  }
  if (DAT_10033004 != 1) {
    return DAT_10033004;
  }
  param_4 = 0;
  if (param_7 == 0) {
    param_7 = DAT_10032ff0;
  }
  iVar2 = MultiByteToWideChar(param_7,(-(uint)(param_8 != 0) & 8) + 1,(int)param_3,iVar1,0,0);
  if (iVar2 == 0) {
    return 0;
  }
  a5 = (undefined *)malloc(iVar2 * 2);
  if (a5 == (undefined *)0x0) {
    return 0;
  }
  iVar1 = MultiByteToWideChar(param_7,1,(int)param_3,iVar1,(int)a5,iVar2);
  if ((iVar1 != 0) && (iVar1 = LCMapStringW(param_1,param_2,(int)a5,iVar2,0,0), iVar1 != 0)) {
    if ((param_2 & 0x400) == 0) {
      param_4 = malloc(iVar1 * 2);
      if ((param_4 == 0) ||
         (iVar2 = LCMapStringW(param_1,param_2,(int)a5,iVar2,param_4,iVar1), iVar2 == 0))
      goto LAB_1000e988;
      if (param_6 == 0) {
        iVar1 = WideCharToMultiByte(param_7,0x220,param_4,iVar1,0,0,0,0);
        iVar2 = iVar1;
      }
      else {
        iVar1 = WideCharToMultiByte(param_7,0x220,param_4,iVar1,param_5,param_6,0,0);
        iVar2 = iVar1;
      }
    }
    else {
      if (param_6 == 0) goto LAB_1000e8ef;
      if (param_6 < iVar1) goto LAB_1000e988;
      iVar2 = LCMapStringW(param_1,param_2,(int)a5,iVar2,param_5,param_6);
    }
    if (iVar2 != 0) {
LAB_1000e8ef:
      free(a5);
      free((undefined *)param_4);
      return iVar1;
    }
  }
LAB_1000e988:
  free(a5);
  free((undefined *)param_4);
  return 0;
}

/* ---- 0x1000e9b0  _strncnt ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl _strncnt(char *param_1,int param_2)

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

/* ---- 0x1000ea10  exit ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl exit(undefined4 param_1)

{
  doexit(param_1,1,0);
  return;
}

/* ---- 0x1000ea40  doexit ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl doexit(int param_1,int param_2,int param_3)

{
  int a1;
  undefined4 *puVar1;
  undefined4 *puVar2;
  int a2;
  
  _lockexit();
  if (DAT_10033048 == 1) {
    a2 = param_1;
    a1 = GetCurrentProcess();
    TerminateProcess(a1,a2);
  }
  _DAT_10033044 = 1;
  DAT_10033040 = (undefined1)param_3;
  if (param_2 == 0) {
    if ((DAT_100337e8 != (undefined4 *)0x0) &&
       (puVar2 = (undefined4 *)(DAT_100337e4 + -4), puVar1 = DAT_100337e8, DAT_100337e8 <= puVar2))
    {
      do {
        if ((code *)*puVar2 != (code *)0x0) {
          (*(code *)*puVar2)();
          puVar1 = DAT_100337e8;
        }
        puVar2 = puVar2 + -1;
      } while (puVar1 <= puVar2);
    }
    _initterm((undefined4 *)&DAT_10017014,(undefined4 *)&DAT_1001701c);
  }
  _initterm((undefined4 *)&DAT_10017020,(undefined4 *)&DAT_10017024);
  if (param_3 != 0) {
    _unlockexit();
    return;
  }
  DAT_10033048 = 1;
  ExitProcess(param_1);
  return;
}

/* ---- 0x1000eb00  _lockexit ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void _lockexit(void)

{
  _lock(0xd);
  return;
}

/* ---- 0x1000eb10  _unlockexit ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void _unlockexit(void)

{
  _unlock(0xd);
  return;
}

/* ---- 0x1000eb20  _initterm ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _initterm(undefined4 *param_1,undefined4 *param_2)

{
  for (; param_1 < param_2; param_1 = param_1 + 1) {
    if ((code *)*param_1 != (code *)0x0) {
      (*(code *)*param_1)();
    }
  }
  return;
}

/* ---- 0x1000ebd0  _initptd ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _initptd(int param_1)

{
  *(undefined **)(param_1 + 0x50) = &DAT_10021bd0;
  *(undefined4 *)(param_1 + 0x14) = 1;
  return;
}

/* ---- 0x1000ebf0  _getptd ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int * _getptd(void)

{
  int a1;
  int *a2;
  int iVar1;
  
  a1 = GetLastError();
  a2 = (int *)TlsGetValue(DAT_1001f230);
  if (a2 == (int *)0x0) {
    a2 = calloc(1,0x74);
    if (a2 != (int *)0x0) {
      iVar1 = TlsSetValue(DAT_1001f230,(int)a2);
      if (iVar1 != 0) {
        _initptd((int)a2);
        iVar1 = GetCurrentThreadId();
        *a2 = iVar1;
        a2[1] = -1;
        SetLastError(a1);
        return a2;
      }
    }
    _amsg_exit(0x10);
  }
  SetLastError(a1);
  return a2;
}

/* ---- 0x1000fa30  _FF_MSGBANNER ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void _FF_MSGBANNER(void)

{
  if ((DAT_10032f60 == 1) || ((DAT_10032f60 == 0 && (DAT_10032f64 == 1)))) {
    _NMSG_WRITE(0xfc);
    if (DAT_10033380 != (code *)0x0) {
      (*DAT_10033380)();
    }
    _NMSG_WRITE(0xff);
  }
  return;
}

/* ---- 0x1000fa70  _NMSG_WRITE ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _NMSG_WRITE(int param_1)

{
  unsigned char _frame[0x1c0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  int iVar7;
  undefined4 *puVar8;
  char *pcVar9;
  undefined4 *puVar10;
  uint *puVar11;
  char *pcVar12;
  char *pcVar13;
  #define local_1a8 (*(undefined1 (*)[4])(_frame + (0x1c0 - 0x1a8)))
  #define acStack_1a4 (*(char (*)[100])(_frame + (0x1c0 - 0x1a4)))
  #define auStack_140 (*(uint (*)[15])(_frame + (0x1c0 - 0x140)))
  #define local_104 (*(undefined4 *)(_frame + (0x1c0 - 0x104)))
  
  piVar2 = &DAT_1001f360;
  iVar7 = 0;
  do {
    if (param_1 == *piVar2) break;
    piVar2 = piVar2 + 2;
    iVar7 = iVar7 + 1;
  } while (piVar2 < &DAT_1001f3f0);
  if (param_1 == (&DAT_1001f360)[iVar7 * 2]) {
    if ((DAT_10032f60 == 1) || ((DAT_10032f60 == 0 && (DAT_10032f64 == 1)))) {
      if ((PTR_100336e0 == (int *)0x0) || (iVar3 = PTR_100336e0[0x12], iVar3 == -1)) {
        iVar3 = GetStdHandle(-0xc);
      }
      pcVar9 = *(char **)(iVar7 * 8 + 0x1001f364);
      uVar4 = 0xffffffff;
      pcVar13 = pcVar9;
      do {
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        cVar1 = *pcVar13;
        pcVar13 = pcVar13 + 1;
      } while (cVar1 != '\0');
      WriteFile(iVar3,(int)pcVar9,~uVar4 - 1,(int)local_1a8,0);
    }
    else if (param_1 != 0xfc) {
      iVar3 = GetModuleFileNameA(0,(int)&local_104,0x104);
      if (iVar3 == 0) {
        puVar8 = &DAT_10015790;
        puVar10 = &local_104;
        for (iVar3 = 5; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar10 = *puVar8;
          puVar8 = puVar8 + 1;
          puVar10 = puVar10 + 1;
        }
        *(undefined2 *)puVar10 = *(undefined2 *)puVar8;
        *(undefined1 *)((int)puVar10 + 2) = *(undefined1 *)((int)puVar8 + 2);
      }
      uVar4 = 0xffffffff;
      puVar6 = &local_104;
      pcVar9 = (char *)&local_104;
      do {
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar9 + 1;
      } while (cVar1 != '\0');
      if (0x3c < ~uVar4) {
        uVar4 = 0xffffffff;
        pcVar9 = (char *)&local_104;
        do {
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          cVar1 = *pcVar9;
          pcVar9 = pcVar9 + 1;
        } while (cVar1 != '\0');
        puVar6 = (uint *)((int)auStack_140 + ~uVar4);
        strncpy(puVar6,(uint *)&DAT_100171b0,3);
      }
      puVar8 = &DAT_10015774;
      pcVar9 = acStack_1a4;
      for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
        *(undefined4 *)pcVar9 = *puVar8;
        puVar8 = puVar8 + 1;
        pcVar9 = pcVar9 + 4;
      }
      *(undefined2 *)pcVar9 = *(undefined2 *)puVar8;
      uVar4 = 0xffffffff;
      do {
        puVar11 = puVar6;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        puVar11 = (uint *)((int)puVar6 + 1);
        uVar5 = *puVar6;
        puVar6 = puVar11;
      } while ((char)uVar5 != '\0');
      uVar4 = ~uVar4;
      iVar3 = -1;
      pcVar9 = acStack_1a4;
      do {
        pcVar13 = pcVar9;
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        pcVar13 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar13;
      } while (cVar1 != '\0');
      pcVar9 = (char *)((int)puVar11 - uVar4);
      pcVar13 = pcVar13 + -1;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
        pcVar9 = pcVar9 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar13 = *pcVar9;
        pcVar9 = pcVar9 + 1;
        pcVar13 = pcVar13 + 1;
      }
      uVar4 = 0xffffffff;
      pcVar9 = "\n\n";
      do {
        pcVar13 = pcVar9;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar13 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar13;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      iVar3 = -1;
      pcVar9 = acStack_1a4;
      do {
        pcVar12 = pcVar9;
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        pcVar12 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar12;
      } while (cVar1 != '\0');
      pcVar9 = pcVar13 + -uVar4;
      pcVar13 = pcVar12 + -1;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
        pcVar9 = pcVar9 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar13 = *pcVar9;
        pcVar9 = pcVar9 + 1;
        pcVar13 = pcVar13 + 1;
      }
      uVar4 = 0xffffffff;
      pcVar9 = *(char **)(iVar7 * 8 + 0x1001f364);
      do {
        pcVar13 = pcVar9;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar13 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar13;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      iVar7 = -1;
      pcVar9 = acStack_1a4;
      do {
        pcVar12 = pcVar9;
        if (iVar7 == 0) break;
        iVar7 = iVar7 + -1;
        pcVar12 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar12;
      } while (cVar1 != '\0');
      pcVar9 = pcVar13 + -uVar4;
      pcVar13 = pcVar12 + -1;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
        pcVar9 = pcVar9 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar13 = *pcVar9;
        pcVar9 = pcVar9 + 1;
        pcVar13 = pcVar13 + 1;
      }
      __crtMessageBoxA(acStack_1a4,"Microsoft Visual C++ Runtime Library",0x12010);
      return;
    }
  }
  return;
}
#undef acStack_1a4
#undef auStack_140
#undef local_104
#undef local_1a8


/* ---- 0x1000fc50  malloc ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int * __cdecl malloc(uint param_1)

{
  int *piVar1;
  
  piVar1 = _nh_malloc(param_1,DAT_10033404);
  return piVar1;
}

/* ---- 0x1000fc70  _nh_malloc ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int * __cdecl _nh_malloc(uint param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  if (param_1 < 0xffffffe1) {
    if (param_1 == 0) {
      param_1 = 1;
    }
    do {
      if (param_1 < 0xffffffe1) {
        piVar1 = _heap_alloc(param_1);
      }
      else {
        piVar1 = (int *)0x0;
      }
      if (piVar1 != (int *)0x0) {
        return piVar1;
      }
      if (param_2 == 0) {
        return (int *)0x0;
      }
      iVar2 = _callnewh(param_1);
    } while (iVar2 != 0);
  }
  return (int *)0x0;
}

/* ---- 0x1000fcc0  _heap_alloc ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int * __cdecl _heap_alloc(int param_1)

{
  int *piVar1;
  uint a3;
  
  a3 = param_1 + 0xfU & 0xfffffff0;
  if (a3 <= DAT_10021444) {
    _lock(9);
    piVar1 = __sbh_alloc_block(param_1 + 0xfU >> 4);
    _unlock(9);
    if (piVar1 != (int *)0x0) {
      return piVar1;
    }
  }
  piVar1 = (int *)HeapAlloc(DAT_100336c0,0,a3);
  return piVar1;
}

/* ---- 0x1000fd20  _isatty ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

byte __cdecl _isatty(uint param_1)

{
  if (DAT_100337e0 <= param_1) {
    return 0;
  }
  return *(byte *)((&PTR_100336e0)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) & 0x40;
}

/* ---- 0x1000ff30  calloc ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int * __cdecl calloc(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint a3;
  int *piVar3;
  int *piVar4;
  
  a3 = param_2 * param_1;
  if (a3 < 0xffffffe1) {
    if (a3 == 0) {
      a3 = 0x10;
    }
    else {
      a3 = a3 + 0xf & 0xfffffff0;
    }
  }
  do {
    piVar3 = (int *)0x0;
    if (a3 < 0xffffffe1) {
      if (DAT_10021444 < a3) {
LAB_1000ffa4:
        if (piVar3 != (int *)0x0) {
          return piVar3;
        }
      }
      else {
        _lock(9);
        piVar3 = __sbh_alloc_block(a3 >> 4);
        _unlock(9);
        if (piVar3 != (int *)0x0) {
          piVar4 = piVar3;
          for (uVar2 = a3 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
            *piVar4 = 0;
            piVar4 = piVar4 + 1;
          }
          for (uVar2 = a3 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
            *(undefined1 *)piVar4 = 0;
            piVar4 = (int *)((int)piVar4 + 1);
          }
          goto LAB_1000ffa4;
        }
      }
      piVar3 = (int *)HeapAlloc(DAT_100336c0,8,a3);
    }
    if ((piVar3 != (int *)0x0) || (DAT_10033404 == 0)) {
      return piVar3;
    }
    iVar1 = _callnewh(a3);
    if (iVar1 == 0) {
      return (int *)0x0;
    }
  } while( true );
}

/* ---- 0x10010080  _getbuf ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _getbuf(int *param_1)

{
  int iVar1;
  
  DAT_10032fd0 = DAT_10032fd0 + 1;
  iVar1 = malloc(0x1000);
  param_1[2] = iVar1;
  if (iVar1 != 0) {
    param_1[3] = param_1[3] | 8;
    param_1[6] = 0x1000;
    *param_1 = param_1[2];
    param_1[1] = 0;
    return;
  }
  param_1[6] = 2;
  param_1[3] = param_1[3] | 4;
  param_1[2] = (int)(param_1 + 5);
  *param_1 = (int)(param_1 + 5);
  param_1[1] = 0;
  return;
}

/* ---- 0x10010300  _free_osfhnd ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl _free_osfhnd(uint param_1)

{
  uint uVar1;
  int *piVar2;
  int a1;
  
  if (param_1 < DAT_100337e0) {
    uVar1 = param_1 & 0x1f;
    piVar2 = (&PTR_100336e0)[(int)param_1 >> 5];
    if (((*(byte *)(piVar2 + uVar1 * 9 + 1) & 1) != 0) && (piVar2[uVar1 * 9] != -1)) {
      if (DAT_10032f64 == 1) {
        if (param_1 == 0) {
          a1 = -10;
        }
        else if (param_1 == 1) {
          a1 = -0xb;
        }
        else {
          if (param_1 != 2) goto LAB_10010367;
          a1 = -0xc;
        }
        SetStdHandle(a1,0);
      }
LAB_10010367:
      (&PTR_100336e0)[(int)param_1 >> 5][uVar1 * 9] = -1;
      return 0;
    }
  }
  piVar2 = _errno();
  *piVar2 = 9;
  piVar2 = __doserrno();
  *piVar2 = 0;
  return 0xffffffff;
}

/* ---- 0x100103a0  _get_osfhandle ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl _get_osfhandle(uint param_1)

{
  int *piVar1;
  
  if ((param_1 < DAT_100337e0) &&
     ((*(byte *)((&PTR_100336e0)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) & 1) != 0)) {
    return (&PTR_100336e0)[(int)param_1 >> 5][(param_1 & 0x1f) * 9];
  }
  piVar1 = _errno();
  *piVar1 = 9;
  piVar1 = __doserrno();
  *piVar1 = 0;
  return 0xffffffff;
}

/* ---- 0x100103f0  _lock_fhandle ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _lock_fhandle(uint param_1)

{
  int *piVar1;
  uint uVar2;
  
  uVar2 = param_1 & 0x1f;
  piVar1 = (&PTR_100336e0)[(int)param_1 >> 5];
  if (piVar1[uVar2 * 9 + 2] == 0) {
    _lock(0x11);
    if (piVar1[uVar2 * 9 + 2] == 0) {
      InitializeCriticalSection((int)(piVar1 + uVar2 * 9 + 3));
      piVar1[uVar2 * 9 + 2] = piVar1[uVar2 * 9 + 2] + 1;
    }
    _unlock(0x11);
  }
  EnterCriticalSection((int)((&PTR_100336e0)[(int)param_1 >> 5] + uVar2 * 9 + 3));
  return;
}

/* ---- 0x10010460  _unlock_fhandle ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _unlock_fhandle(uint param_1)

{
  LeaveCriticalSection((int)((&PTR_100336e0)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 3));
  return;
}

/* ---- 0x100114c0  __sbh_alloc_new_region ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined ** __sbh_alloc_new_region(void)

{
  bool bVar1;
  undefined4 *a1;
  int iVar2;
  undefined **ppuVar3;
  undefined **a3;
  undefined4 *puVar4;
  
  if (DAT_1001f430 == -1) {
    a3 = &PTR_LOOP_1001f420;
  }
  else {
    a3 = (undefined **)HeapAlloc(DAT_100336c0,0,0x2020);
    if (a3 == (undefined **)0x0) {
      return (undefined **)0x0;
    }
  }
  a1 = (undefined4 *)VirtualAlloc(0,0x400000,0x2000,4);
  if (a1 != (undefined4 *)0x0) {
    iVar2 = VirtualAlloc((int)a1,0x10000,0x1000,4);
    if (iVar2 != 0) {
      if (a3 == &PTR_LOOP_1001f420) {
        if (PTR_LOOP_1001f420 == (undefined *)0x0) {
          PTR_LOOP_1001f420 = (undefined *)&PTR_LOOP_1001f420;
        }
        if (PTR_LOOP_1001f424 == (undefined *)0x0) {
          PTR_LOOP_1001f424 = (undefined *)&PTR_LOOP_1001f420;
        }
      }
      else {
        *a3 = (undefined *)&PTR_LOOP_1001f420;
        a3[1] = PTR_LOOP_1001f424;
        PTR_LOOP_1001f424 = (undefined *)a3;
        *(undefined ***)a3[1] = a3;
      }
      a3[5] = (undefined *)(a1 + 0x100000);
      a3[4] = (undefined *)a1;
      a3[2] = (undefined *)(a3 + 6);
      a3[3] = (undefined *)(a3 + 0x26);
      iVar2 = 0;
      ppuVar3 = a3 + 6;
      do {
        bVar1 = 0xf < iVar2;
        iVar2 = iVar2 + 1;
        *ppuVar3 = (undefined *)((bVar1 - 1 & 0xf1) - 1);
        ppuVar3[1] = (undefined *)0xf1;
        ppuVar3 = ppuVar3 + 2;
      } while (iVar2 < 0x400);
      puVar4 = a1;
      for (iVar2 = 0x4000; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar4 = 0;
        puVar4 = puVar4 + 1;
      }
      if (a1 < a3[4] + 0x10000) {
        do {
          a1[1] = 0xf0;
          *a1 = a1 + 2;
          *(undefined1 *)(a1 + 0x3e) = 0xff;
          a1 = a1 + 0x400;
        } while (a1 < a3[4] + 0x10000);
      }
      return a3;
    }
    VirtualFree((int)a1,0,0x8000);
  }
  if (a3 != &PTR_LOOP_1001f420) {
    HeapFree(DAT_100336c0,0,(int)a3);
  }
  return (undefined **)0x0;
}

/* ---- 0x10011630  __sbh_release_region ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl __sbh_release_region(undefined **param_1)

{
  VirtualFree((int)param_1[4],0,0x8000);
  if ((undefined **)PTR_LOOP_10021440 == param_1) {
    PTR_LOOP_10021440 = param_1[1];
  }
  if (param_1 != &PTR_LOOP_1001f420) {
    *(undefined **)param_1[1] = *param_1;
    *(undefined **)(*param_1 + 4) = param_1[1];
    HeapFree(DAT_100336c0,0,(int)param_1);
    return;
  }
  DAT_1001f430 = 0xffffffff;
  return;
}

/* ---- 0x10011690  __sbh_decommit_pages ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl __sbh_decommit_pages(int param_1)

{
  int iVar1;
  undefined **ppuVar2;
  int iVar3;
  int iVar4;
  undefined **ppuVar5;
  undefined **ppuVar6;
  
  ppuVar6 = (undefined **)PTR_LOOP_1001f424;
  do {
    ppuVar5 = ppuVar6;
    if (ppuVar6[4] != (undefined *)0xffffffff) {
      iVar4 = 0;
      ppuVar5 = ppuVar6 + 0x804;
      iVar3 = 0x3ff000;
      do {
        if (*ppuVar5 == (undefined *)0xf0) {
          iVar1 = VirtualFree((int)(ppuVar6[4] + iVar3),0x1000,0x4000);
          if (iVar1 != 0) {
            *ppuVar5 = (undefined *)0xffffffff;
            DAT_10033388 = DAT_10033388 + -1;
            if (((undefined **)ppuVar6[3] == (undefined **)0x0) || (ppuVar5 < ppuVar6[3])) {
              ppuVar6[3] = (undefined *)ppuVar5;
            }
            iVar4 = iVar4 + 1;
            param_1 = param_1 + -1;
            if (param_1 == 0) break;
          }
        }
        iVar3 = iVar3 + -0x1000;
        ppuVar5 = ppuVar5 + -2;
      } while (-1 < iVar3);
      ppuVar5 = (undefined **)ppuVar6[1];
      if ((iVar4 != 0) && (ppuVar6[6] == (undefined *)0xffffffff)) {
        iVar3 = 1;
        ppuVar2 = ppuVar6 + 8;
        do {
          if (*ppuVar2 != (undefined *)0xffffffff) break;
          iVar3 = iVar3 + 1;
          ppuVar2 = ppuVar2 + 2;
        } while (iVar3 < 0x400);
        if (iVar3 == 0x400) {
          __sbh_release_region(ppuVar6);
        }
      }
    }
    if ((ppuVar5 == (undefined **)PTR_LOOP_1001f424) || (ppuVar6 = ppuVar5, param_1 < 1)) {
      return;
    }
  } while( true );
}

/* ---- 0x10011760  __sbh_find_block ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl __sbh_find_block(undefined *param_1,undefined4 *param_2,uint *param_3)

{
  undefined **ppuVar1;
  uint uVar2;
  
  ppuVar1 = &PTR_LOOP_1001f420;
  while ((param_1 <= ppuVar1[4] || (ppuVar1[5] <= param_1))) {
    ppuVar1 = (undefined **)*ppuVar1;
    if (ppuVar1 == &PTR_LOOP_1001f420) {
      return 0;
    }
  }
  if (((uint)param_1 & 0xf) != 0) {
    return 0;
  }
  if (((uint)param_1 & 0xfff) < 0x100) {
    return 0;
  }
  *param_2 = ppuVar1;
  uVar2 = (uint)param_1 & 0xfffff000;
  *param_3 = uVar2;
  return ((int)(param_1 + (-0x100 - uVar2)) >> 4) + 8 + uVar2;
}

/* ---- 0x100117c0  __sbh_free_block ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl __sbh_free_block(int param_1,int param_2,byte *param_3)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = param_2 - *(int *)(param_1 + 0x10) >> 0xc;
  piVar1 = (int *)(param_1 + 0x18 + iVar2 * 8);
  *piVar1 = *(int *)(param_1 + 0x18 + iVar2 * 8) + (uint)*param_3;
  *param_3 = 0;
  piVar1[1] = 0xf1;
  if ((*piVar1 == 0xf0) && (DAT_10033388 = DAT_10033388 + 1, DAT_10033388 == 0x20)) {
    __sbh_decommit_pages(0x10);
  }
  return;
}

/* ---- 0x10011820  __sbh_alloc_block ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int * __cdecl __sbh_alloc_block(uint param_1)

{
  undefined **ppuVar1;
  uint *puVar2;
  undefined **ppuVar3;
  undefined *puVar4;
  int *piVar5;
  undefined **ppuVar6;
  undefined **ppuVar7;
  int *piVar8;
  int iVar9;
  uint *puVar10;
  int *piVar11;
  bool bVar12;
  
  piVar11 = (int *)PTR_LOOP_10021440;
  do {
    if (piVar11[4] != -1) {
      puVar10 = (uint *)piVar11[2];
      piVar8 = (int *)(((int)puVar10 + (-0x18 - (int)piVar11) >> 3) * 0x1000 + piVar11[4]);
      for (; puVar10 < piVar11 + 0x806; puVar10 = puVar10 + 2) {
        if (((int)param_1 <= (int)*puVar10) && (param_1 < puVar10[1])) {
          piVar5 = (int *)__sbh_alloc_new_group(piVar8,*puVar10,param_1);
          if (piVar5 != (int *)0x0) {
            PTR_LOOP_10021440 = (undefined *)piVar11;
            *puVar10 = *puVar10 - param_1;
            piVar11[2] = (int)puVar10;
            return piVar5;
          }
          puVar10[1] = param_1;
        }
        piVar8 = piVar8 + 0x400;
      }
      puVar2 = (uint *)piVar11[2];
      piVar8 = (int *)piVar11[4];
      for (puVar10 = (uint *)(piVar11 + 6); puVar10 < puVar2; puVar10 = puVar10 + 2) {
        if (((int)param_1 <= (int)*puVar10) && (param_1 < puVar10[1])) {
          piVar5 = (int *)__sbh_alloc_new_group(piVar8,*puVar10,param_1);
          if (piVar5 != (int *)0x0) {
            PTR_LOOP_10021440 = (undefined *)piVar11;
            *puVar10 = *puVar10 - param_1;
            piVar11[2] = (int)puVar10;
            return piVar5;
          }
          puVar10[1] = param_1;
        }
        piVar8 = piVar8 + 0x400;
      }
    }
    piVar11 = (int *)*piVar11;
  } while (piVar11 != (int *)PTR_LOOP_10021440);
  ppuVar7 = &PTR_LOOP_1001f420;
  while ((ppuVar7[4] == (undefined *)0xffffffff || (ppuVar7[3] == (undefined *)0x0))) {
    ppuVar7 = (undefined **)*ppuVar7;
    if (ppuVar7 == &PTR_LOOP_1001f420) {
      ppuVar7 = __sbh_alloc_new_region();
      if (ppuVar7 == (undefined **)0x0) {
        return (int *)0x0;
      }
      piVar11 = (int *)ppuVar7[4];
      *(char *)(piVar11 + 2) = (char)param_1;
      PTR_LOOP_10021440 = (undefined *)ppuVar7;
      *piVar11 = (int)piVar11 + param_1 + 8;
      piVar11[1] = 0xf0 - param_1;
      ppuVar7[6] = ppuVar7[6] + -(param_1 & 0xff);
      return piVar11 + 0x40;
    }
  }
  ppuVar3 = (undefined **)ppuVar7[3];
  puVar4 = *ppuVar3;
  piVar11 = (int *)(ppuVar7[4] + ((int)ppuVar3 + (-0x18 - (int)ppuVar7) >> 3) * 0x1000);
  ppuVar6 = ppuVar3;
  for (iVar9 = 0; (puVar4 == (undefined *)0xffffffff && (iVar9 < 0x10)); iVar9 = iVar9 + 1) {
    puVar4 = ppuVar6[2];
    ppuVar6 = ppuVar6 + 2;
  }
  piVar8 = (int *)VirtualAlloc((int)piVar11,iVar9 << 0xc,0x1000,4);
  if (piVar8 != piVar11) {
    return (int *)0x0;
  }
  ppuVar6 = ppuVar3;
  if (0 < iVar9) {
    piVar8 = piVar11 + 1;
    do {
      *piVar8 = 0xf0;
      piVar8[-1] = (int)(piVar8 + 1);
      *(undefined1 *)(piVar8 + 0x3d) = 0xff;
      *ppuVar6 = (undefined *)0xf0;
      ppuVar6[1] = (undefined *)0xf1;
      piVar8 = piVar8 + 0x400;
      ppuVar6 = ppuVar6 + 2;
      iVar9 = iVar9 + -1;
    } while (iVar9 != 0);
  }
  ppuVar1 = ppuVar7 + 0x806;
  bVar12 = false;
  if (ppuVar6 < ppuVar1) {
    do {
      if (*ppuVar6 == (undefined *)0xffffffff) break;
      ppuVar6 = ppuVar6 + 2;
    } while (ppuVar6 < ppuVar1);
    bVar12 = ppuVar6 < ppuVar1;
  }
  PTR_LOOP_10021440 = (undefined *)ppuVar7;
  ppuVar7[3] = (undefined *)(-(uint)bVar12 & (uint)ppuVar6);
  *(char *)(piVar11 + 2) = (char)param_1;
  ppuVar7[2] = (undefined *)ppuVar3;
  *ppuVar3 = *ppuVar3 + -param_1;
  piVar11[1] = piVar11[1] - param_1;
  *piVar11 = (int)piVar11 + param_1 + 8;
  return piVar11 + 0x40;
}

/* ---- 0x10011a60  __sbh_alloc_new_group ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl __sbh_alloc_new_group(int *param_1,uint param_2,uint param_3)

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
            goto LAB_10011baf;
          }
          *param_1 = (int)(pbVar6 + param_3);
          param_1[1] = uVar5 - param_3;
          goto LAB_10011bb6;
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
LAB_10011baf:
            param_1[1] = 0;
          }
LAB_10011bb6:
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

/* ---- 0x10012d50  __crtGetStringTypeA ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl
__crtGetStringTypeA(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                   int param_7)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int *a5;
  #define local_2 (*(undefined1 (*)[2])(_frame + (0x20 - 0x2)))
  
  a5 = (int *)0x0;
  if (DAT_100333f4 == 0) {
    iVar1 = GetStringTypeW(1,IMG_ADDR(0x100154b8),1,(int)local_2);
    if (iVar1 == 0) {
      iVar1 = GetStringTypeA(0,1,IMG_ADDR(0x100154b4),1,(int)local_2);
      if (iVar1 == 0) {
        return 0;
      }
      DAT_100333f4 = 2;
    }
    else {
      DAT_100333f4 = 1;
    }
  }
  if (DAT_100333f4 == 2) {
    if (param_6 == 0) {
      param_6 = DAT_10032fe0;
    }
    iVar1 = GetStringTypeA(param_6,param_1,param_2,param_3,param_4);
    return iVar1;
  }
  param_6 = DAT_100333f4;
  if (DAT_100333f4 == 1) {
    param_6 = 0;
    if (param_5 == 0) {
      param_5 = DAT_10032ff0;
    }
    iVar1 = MultiByteToWideChar(param_5,(-(uint)(param_7 != 0) & 8) + 1,param_2,param_3,0,0);
    if (iVar1 != 0) {
      a5 = calloc(2,iVar1);
      if (a5 != (int *)0x0) {
        iVar1 = MultiByteToWideChar(param_5,1,param_2,param_3,(int)a5,iVar1);
        if (iVar1 != 0) {
          iVar1 = GetStringTypeW(param_1,(int)a5,iVar1,param_4);
          free((undefined *)a5);
          return iVar1;
        }
      }
    }
    free((undefined *)a5);
  }
  return param_6;
}
#undef local_2


/* ---- 0x10012e90  __crtMessageBoxA ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl __crtMessageBoxA(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int a1;
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = 0;
  if (DAT_100333f8 != (code *)0x0) {
LAB_10012ee0:
    if (DAT_100333fc != (code *)0x0) {
      iVar2 = (*DAT_100333fc)();
    }
    if ((iVar2 != 0) && (DAT_10033400 != (code *)0x0)) {
      iVar2 = (*DAT_10033400)(iVar2);
    }
    uVar1 = (*DAT_100333f8)(iVar2,param_1,param_2,param_3);
    return uVar1;
  }
  a1 = LoadLibraryA(IMG_ADDR(0x10015e58));
  if (a1 != 0) {
    DAT_100333f8 = (code *)GetProcAddress(a1,IMG_ADDR(0x10015e4c));
    if (DAT_100333f8 != (code *)0x0) {
      DAT_100333fc = (code *)GetProcAddress(a1,IMG_ADDR(0x10015e3c));
      DAT_10033400 = (code *)GetProcAddress(a1,IMG_ADDR(0x10015e28));
      goto LAB_10012ee0;
    }
  }
  return 0;
}

/* ---- 0x10012f20  _callnewh ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl _callnewh(undefined4 param_1)

{
  int iVar1;
  
  if (DAT_10033408 != (code *)0x0) {
    iVar1 = (*DAT_10033408)(param_1);
    if (iVar1 != 0) {
      return 1;
    }
  }
  return 0;
}
