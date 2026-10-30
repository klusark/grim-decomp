/* GRIMFANDANGO.EXE :: zlib.c
 * functions 0x004c3e60 .. 0x004cb690 (46 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004c3e60  gz_open ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* zlib 1.1.3 gzio.c (file access routed through the file service table at g_pZlibFileOps): opens a
   gzip stream for 'r' or 'w' */

void * __cdecl gz_open(char *path,char *mode,int fd)

{
  unsigned char _frame[0x80];  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  char *pcVar4;
  int iVar5;
  undefined *puVar6;
  undefined4 *puVar7;
  uint uVar8;
  uint uVar9;
  char *pcVar10;
  char *pcVar11;
  #define local_64 (*(uint *)(_frame + (0x80 - 0x64)))
  #define local_60 (*(uint *)(_frame + (0x80 - 0x60)))
  #define cStack_5c (*(char *)(_frame + (0x80 - 0x5c)))
  #define local_5b (*(uint *)(_frame + (0x80 - 0x5b)))
  #define local_57 (*(uint *)(_frame + (0x80 - 0x57)))
  #define uStack_53 (*(undefined1 *)(_frame + (0x80 - 0x53)))
  #define local_50 (*(char (*)[80])(_frame + (0x80 - 0x50)))
  
  local_60 = 0xffffffff;
  local_64 = 0;
  if (path == (char *)0x0) {
    return (void *)0x0;
  }
  if (mode == (char *)0x0) {
    return (void *)0x0;
  }
  puVar2 = (undefined4 *)malloc(100);
  if (puVar2 == (undefined4 *)0x0) {
    return (void *)0x0;
  }
  puVar2[8] = 0;
  puVar2[9] = 0;
  puVar2[10] = 0;
  puVar2[0x11] = 0;
  *puVar2 = 0;
  puVar2[0x12] = 0;
  puVar2[3] = 0;
  puVar2[4] = 0;
  puVar2[1] = 0;
  puVar2[0x10] = 0;
  puVar2[0xe] = 0;
  puVar2[0xf] = 0;
  uVar3 = crc32(0,0,0);
  puVar2[0x13] = uVar3;
  uVar8 = 0xffffffff;
  puVar2[0x14] = 0;
  puVar2[0x16] = 0;
  pcVar4 = path;
  do {
    if (uVar8 == 0) break;
    uVar8 = uVar8 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  pcVar4 = malloc(~uVar8);
  puVar2[0x15] = pcVar4;
  if (pcVar4 != (char *)0x0) {
    uVar8 = 0xffffffff;
    pcVar10 = path;
    do {
      pcVar11 = pcVar10;
      if (uVar8 == 0) break;
      uVar8 = uVar8 - 1;
      pcVar11 = pcVar10 + 1;
      cVar1 = *pcVar10;
      pcVar10 = pcVar11;
    } while (cVar1 != '\0');
    uVar8 = ~uVar8;
    pcVar10 = pcVar11 + -uVar8;
    for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
      *(undefined4 *)pcVar4 = *(undefined4 *)pcVar10;
      pcVar10 = pcVar10 + 4;
      pcVar4 = pcVar4 + 4;
    }
    for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
      *pcVar4 = *pcVar10;
      pcVar10 = pcVar10 + 1;
      pcVar4 = pcVar4 + 1;
    }
    *(undefined1 *)(puVar2 + 0x17) = 0;
    pcVar4 = mode;
    mode = local_50;
    do {
      if (*pcVar4 == 'r') {
        *(undefined1 *)(puVar2 + 0x17) = 0x72;
      }
      if ((*pcVar4 == 'w') || (*pcVar4 == 'a')) {
        *(undefined1 *)(puVar2 + 0x17) = 0x77;
      }
      cVar1 = *pcVar4;
      if ((cVar1 < '0') || ('9' < cVar1)) {
        if (cVar1 == 'f') {
          local_64 = 1;
        }
        else if (cVar1 == 'h') {
          local_64 = 2;
        }
        else {
          *mode = cVar1;
          mode = mode + 1;
        }
      }
      else {
        local_60 = (int)cVar1 - 0x30;
      }
      pcVar4 = pcVar4 + 1;
    } while ((cVar1 != '\0') && (mode != &STACK0X(0x00000000)));
    if (*(char *)(puVar2 + 0x17) != '\0') {
      if (*(char *)(puVar2 + 0x17) == 'w') {
        iVar5 = deflateInit2_(puVar2,local_60,8,0xfffffff1,8,local_64,s_1_1_3_004f1a20,0x38);
        puVar6 = malloc(0x4000);
        puVar2[0x12] = puVar6;
        puVar2[3] = puVar6;
        if (iVar5 != 0) goto LAB_004c410c;
        if (puVar6 == (undefined *)0x0) {
          gz_destroy(puVar2);
          return (void *)0x0;
        }
      }
      else {
        puVar6 = malloc(0x4000);
        puVar2[0x11] = puVar6;
        *puVar2 = puVar6;
        iVar5 = inflateInit2_(puVar2,0xfffffff1,s_1_1_3_004f1a20,0x38);
        if ((iVar5 != 0) || (puVar2[0x11] == 0)) goto LAB_004c410c;
      }
      puVar2[4] = 0x4000;
      puVar7 = (undefined4 *)_errno();
      *puVar7 = 0;
      if (fd < 0) {
        iVar5 = (*(code *)*g_pZfileFileIo)(path);
      }
      else {
        iVar5 = _fdopen(fd,local_50);
      }
      puVar2[0x10] = iVar5;
      if (iVar5 != 0) {
        if (*(char *)(puVar2 + 0x17) == 'w') {
          local_5b = 0;
          local_57 = 0;
          cStack_5c = DAT_004f5a98;
          uStack_53 = 0;
          sprintf(&cStack_5c,s__c_c_c_c_c_c_c_c_c_c_004f1a08,UINT_004f1a00,UINT_004f1a04,8,0,0,0,0,0
                  ,0,0xb);
          (*(code *)g_pZfileFileIo[3])(puVar2[0x10],&cStack_5c,10);
          puVar2[0x18] = 10;
          return puVar2;
        }
        gz_check_header(puVar2);
        if (puVar2[0x16] != 1) {
          iVar5 = (*(code *)g_pZfileFileIo[4])(puVar2[0x10]);
          puVar2[0x18] = iVar5 - puVar2[1];
          return puVar2;
        }
      }
    }
  }
LAB_004c410c:
  gz_destroy(puVar2);
  return (void *)0x0;
}
#undef cStack_5c
#undef local_50
#undef local_57
#undef local_5b
#undef local_60
#undef local_64
#undef uStack_53

#endif


/* ---- 0x004c4120  gz_check_header ---- */
void gz_check_header(int *param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint *puVar4;
  
  iVar3 = 0;
  puVar4 = &UINT_004f1a00;
  do {
    uVar1 = gz_get_byte(param_1);
    if (uVar1 != *puVar4) {
      if (iVar3 != 0) {
        param_1[1] = param_1[1] + 1;
        *param_1 = *param_1 + -1;
      }
      if (uVar1 != 0xffffffff) {
        param_1[1] = param_1[1] + 1;
        *param_1 = *param_1 + -1;
        param_1[0x16] = 1;
      }
      param_1[0xe] = (uint)(param_1[1] == 0);
      return;
    }
    puVar4 = puVar4 + 1;
    iVar3 = iVar3 + 1;
  } while (puVar4 < s__c_c_c_c_c_c_c_c_c_c_004f1a08);
  iVar3 = gz_get_byte(param_1);
  uVar1 = gz_get_byte(param_1);
  if ((iVar3 != 8) || ((uVar1 & 0xe0) != 0)) {
    param_1[0xe] = -3;
    return;
  }
  iVar3 = 6;
  do {
    gz_get_byte(param_1);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  if ((uVar1 & 4) != 0) {
    iVar3 = gz_get_byte(param_1);
    iVar2 = gz_get_byte(param_1);
    iVar3 = iVar3 + iVar2 * 0x100;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      iVar2 = gz_get_byte(param_1);
    } while (iVar2 != -1);
  }
  if ((uVar1 & 8) != 0) {
    iVar3 = gz_get_byte(param_1);
    while ((iVar3 != 0 && (iVar3 != -1))) {
      iVar3 = gz_get_byte(param_1);
    }
  }
  if ((uVar1 & 0x10) != 0) {
    iVar3 = gz_get_byte(param_1);
    while ((iVar3 != 0 && (iVar3 != -1))) {
      iVar3 = gz_get_byte(param_1);
    }
  }
  if ((uVar1 & 2) != 0) {
    iVar3 = 2;
    do {
      gz_get_byte(param_1);
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  param_1[0xe] = -(uint)(param_1[0xf] != 0) & 0xfffffffd;
  return;
}

/* ---- 0x004c4280  gz_get_byte ---- */
uint gz_get_byte(undefined4 *param_1)

{
  byte bVar1;
  undefined4 *puVar2;
  int iVar3;
  
  if (param_1[0xf] != 0) {
    return 0xffffffff;
  }
  if (param_1[1] == 0) {
    puVar2 = (undefined4 *)_errno();
    *puVar2 = 0;
    iVar3 = (*(code *)g_pZfileFileIo[2])(param_1[0x10],param_1[0x11],0x4000);
    param_1[1] = iVar3;
    if (iVar3 == 0) {
      param_1[0xf] = 1;
      return 0xffffffff;
    }
    *param_1 = param_1[0x11];
  }
  param_1[1] = param_1[1] + -1;
  bVar1 = *(byte *)*param_1;
  *param_1 = (byte *)*param_1 + 1;
  return (uint)bVar1;
}

/* ---- 0x004c42f0  gz_destroy ---- */
int gz_destroy(int param_1)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = 0;
  if (param_1 != 0) {
    if (*(int *)(param_1 + 0x50) != 0) {
      free(*(int *)(param_1 + 0x50));
    }
    if (*(int *)(param_1 + 0x1c) != 0) {
      if (*(char *)(param_1 + 0x5c) == 'w') {
        iVar2 = deflateEnd(param_1);
      }
      else if (*(char *)(param_1 + 0x5c) == 'r') {
        iVar2 = inflateEnd(param_1);
      }
    }
    if (*(int *)(param_1 + 0x40) != 0) {
      (*(code *)g_pZfileFileIo[1])(*(int *)(param_1 + 0x40));
      piVar1 = (int *)_errno();
      if (*piVar1 != 0x1d) {
        iVar2 = -1;
      }
    }
    if (*(int *)(param_1 + 0x38) < 0) {
      iVar2 = *(int *)(param_1 + 0x38);
    }
    if (*(int *)(param_1 + 0x44) != 0) {
      free(*(int *)(param_1 + 0x44));
    }
    if (*(int *)(param_1 + 0x48) != 0) {
      free(*(int *)(param_1 + 0x48));
    }
    if (*(int *)(param_1 + 0x54) != 0) {
      free(*(int *)(param_1 + 0x54));
    }
    free(param_1);
    return iVar2;
  }
  return -2;
}

/* ---- 0x004c43a0  gzread ---- */
int gzread(int *param_1,int param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  undefined4 *puVar8;
  
  piVar2 = param_1;
  if ((param_1 == (int *)0x0) || ((char)param_1[0x17] != 'r')) {
    return -2;
  }
  iVar5 = param_1[0xe];
  if ((iVar5 == -3) || (iVar5 == -1)) {
    return -1;
  }
  if (iVar5 == 1) {
    return 0;
  }
  param_1 = (int *)param_2;
  piVar2[3] = param_2;
  piVar2[4] = param_3;
  iVar5 = param_2;
  if (param_3 != 0) {
    do {
      uVar6 = piVar2[1];
      if (piVar2[0x16] != 0) {
        if ((uint)piVar2[4] < uVar6) {
          uVar6 = piVar2[4];
        }
        if (uVar6 != 0) {
          puVar3 = (undefined4 *)*piVar2;
          puVar8 = (undefined4 *)piVar2[3];
          for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
            *puVar8 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar8 = puVar8 + 1;
          }
          for (uVar7 = uVar6 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
            *(undefined1 *)puVar8 = *(undefined1 *)puVar3;
            puVar3 = (undefined4 *)((int)puVar3 + 1);
            puVar8 = (undefined4 *)((int)puVar8 + 1);
          }
          param_1 = (int *)(param_2 + uVar6);
          piVar2[3] = (int)param_1;
          *piVar2 = *piVar2 + uVar6;
          piVar2[4] = piVar2[4] - uVar6;
          piVar2[1] = piVar2[1] - uVar6;
        }
        if (piVar2[4] != 0) {
          iVar5 = (*(code *)g_pZfileFileIo[2])(piVar2[0x10],param_1,piVar2[4]);
          piVar2[4] = piVar2[4] - iVar5;
        }
        param_3 = param_3 - piVar2[4];
        piVar2[2] = piVar2[2] + param_3;
        piVar2[5] = piVar2[5] + param_3;
        if (param_3 == 0) {
          piVar2[0xf] = 1;
        }
        return param_3;
      }
      if ((uVar6 == 0) && (piVar2[0xf] == 0)) {
        puVar3 = (undefined4 *)_errno();
        *puVar3 = 0;
        iVar4 = (*(code *)g_pZfileFileIo[2])(piVar2[0x10],piVar2[0x11],0x4000);
        piVar2[1] = iVar4;
        if (iVar4 == 0) {
          piVar2[0xf] = 1;
        }
        *piVar2 = piVar2[0x11];
      }
      iVar4 = inflate(piVar2,0);
      piVar2[0xe] = iVar4;
      if (iVar4 == 1) {
        iVar4 = crc32(piVar2[0x13],iVar5,piVar2[3] - iVar5);
        iVar5 = piVar2[3];
        piVar2[0x13] = iVar4;
        iVar4 = gz_getLong(piVar2);
        if (iVar4 == piVar2[0x13]) {
          gz_getLong(piVar2);
          gz_check_header(piVar2);
          if (piVar2[0xe] != 0) break;
          iVar4 = piVar2[2];
          iVar1 = piVar2[5];
          inflateReset(piVar2);
          piVar2[2] = iVar4;
          piVar2[5] = iVar1;
          iVar4 = crc32(0,0,0);
          piVar2[0x13] = iVar4;
        }
        else {
          piVar2[0xe] = -3;
        }
      }
      if (((piVar2[0xe] != 0) || (piVar2[0xf] != 0)) || (piVar2[4] == 0)) break;
    } while( true );
  }
  iVar5 = crc32(piVar2[0x13],iVar5,piVar2[3] - iVar5);
  piVar2[0x13] = iVar5;
  return param_3 - piVar2[4];
}

/* ---- 0x004c45b0  gzwrite ---- */
int gzwrite(undefined4 *param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  if ((param_1 == (undefined4 *)0x0) || (*(char *)(param_1 + 0x17) != 'w')) {
    return -2;
  }
  *param_1 = param_2;
  param_1[1] = param_3;
  iVar1 = param_3;
  do {
    if (iVar1 == 0) {
LAB_004c4624:
      uVar2 = crc32(param_1[0x13],param_2,param_3);
      param_1[0x13] = uVar2;
      return param_3 - param_1[1];
    }
    if (param_1[4] == 0) {
      param_1[3] = param_1[0x12];
      iVar1 = (*(code *)g_pZfileFileIo[3])(param_1[0x10],param_1[0x12],0x4000);
      if (iVar1 != 0x4000) {
        param_1[0xe] = 0xffffffff;
        goto LAB_004c4624;
      }
      param_1[4] = 0x4000;
    }
    iVar1 = deflate(param_1,0);
    param_1[0xe] = iVar1;
    if (iVar1 != 0) goto LAB_004c4624;
    iVar1 = param_1[1];
  } while( true );
}

/* ---- 0x004c4690  gz_do_flush ---- */
uint gz_do_flush(int param_1,undefined4 param_2)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  
  bVar1 = false;
  if ((param_1 == 0) || (*(char *)(param_1 + 0x5c) != 'w')) {
    return 0xfffffffe;
  }
  *(undefined4 *)(param_1 + 4) = 0;
  do {
    iVar3 = 0x4000 - *(int *)(param_1 + 0x10);
    if (iVar3 != 0) {
      iVar2 = (*(code *)g_pZfileFileIo[3])
                        (*(undefined4 *)(param_1 + 0x40),*(undefined4 *)(param_1 + 0x48),iVar3);
      if (iVar2 != iVar3) {
        *(undefined4 *)(param_1 + 0x38) = 0xffffffff;
        return 0xffffffff;
      }
      *(undefined4 *)(param_1 + 0x10) = 0x4000;
      *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(param_1 + 0x48);
    }
    if (bVar1) break;
    iVar2 = deflate(param_1,param_2);
    *(int *)(param_1 + 0x38) = iVar2;
    if ((iVar3 == 0) && (iVar2 == -5)) {
      *(undefined4 *)(param_1 + 0x38) = 0;
    }
    if ((*(int *)(param_1 + 0x10) == 0) && (*(int *)(param_1 + 0x38) != 1)) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
  } while ((*(int *)(param_1 + 0x38) == 0) || (*(int *)(param_1 + 0x38) == 1));
  return -(uint)(*(uint *)(param_1 + 0x38) != 1) & *(uint *)(param_1 + 0x38);
}

/* ---- 0x004c4750  gzseek ---- */
uint gzseek(undefined4 *param_1,uint param_2,int param_3)

{
  undefined4 *puVar1;
  undefined *puVar2;
  uint uVar3;
  int iVar4;
  
  if ((((param_1 != (undefined4 *)0x0) && (param_3 != 2)) && (param_1[0xe] != -1)) &&
     (param_1[0xe] != -3)) {
    if (*(char *)(param_1 + 0x17) == 'w') {
      if (param_3 == 0) {
        param_2 = param_2 - param_1[2];
      }
      if (-1 < (int)param_2) {
        if (param_1[0x11] == 0) {
          puVar1 = (undefined4 *)malloc(0x4000);
          param_1[0x11] = puVar1;
          for (iVar4 = 0x1000; iVar4 != 0; iVar4 = iVar4 + -1) {
            *puVar1 = 0;
            puVar1 = puVar1 + 1;
          }
        }
        while( true ) {
          if ((int)param_2 < 1) {
            return param_1[2];
          }
          uVar3 = 0x4000;
          if ((int)param_2 < 0x4000) {
            uVar3 = param_2;
          }
          iVar4 = gzwrite(param_1,param_1[0x11],uVar3);
          if (iVar4 == 0) break;
          param_2 = param_2 - iVar4;
        }
      }
    }
    else {
      if (param_3 == 1) {
        param_2 = param_2 + param_1[5];
      }
      if (-1 < (int)param_2) {
        if (param_1[0x16] != 0) {
          param_1[1] = 0;
          *param_1 = param_1[0x11];
          (*(code *)g_pZfileFileIo[5])(param_1[0x10],param_2,0);
          param_1[5] = param_2;
          param_1[2] = param_2;
          return param_2;
        }
        if (param_2 < (uint)param_1[5]) {
          iVar4 = gzrewind(param_1);
          if (iVar4 < 0) {
            return 0xffffffff;
          }
        }
        else {
          param_2 = param_2 - param_1[5];
        }
        if (param_2 != 0) {
          if (param_1[0x12] == 0) {
            puVar2 = malloc(0x4000);
            param_1[0x12] = puVar2;
          }
          for (; 0 < (int)param_2; param_2 = param_2 - iVar4) {
            uVar3 = 0x4000;
            if ((int)param_2 < 0x4000) {
              uVar3 = param_2;
            }
            iVar4 = gzread(param_1,param_1[0x12],uVar3);
            if (iVar4 < 1) {
              return 0xffffffff;
            }
          }
        }
        return param_1[5];
      }
    }
  }
  return 0xffffffff;
}

/* ---- 0x004c48a0  gzrewind ---- */
undefined4 gzrewind(undefined4 *param_1)

{
  undefined4 uVar1;
  
  if ((param_1 != (undefined4 *)0x0) && (*(char *)(param_1 + 0x17) == 'r')) {
    param_1[0xe] = 0;
    param_1[0xf] = 0;
    param_1[1] = 0;
    *param_1 = param_1[0x11];
    uVar1 = crc32(0,0,0);
    param_1[0x13] = uVar1;
    if (param_1[0x18] == 0) {
      rewind(param_1[0x10]);
      return 0;
    }
    inflateReset(param_1);
    uVar1 = (*(code *)g_pZfileFileIo[5])(param_1[0x10],param_1[0x18],0);
    return uVar1;
  }
  return 0xffffffff;
}

/* ---- 0x004c4920  gz_getLong ---- */
int gz_getLong(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = gz_get_byte(param_1);
  iVar2 = gz_get_byte(param_1);
  iVar3 = gz_get_byte(param_1);
  iVar4 = gz_get_byte(param_1);
  if (iVar4 == -1) {
    *(undefined4 *)(param_1 + 0x38) = 0xfffffffd;
  }
  return iVar4 * 0x1000000 + iVar1 + iVar2 * 0x100 + iVar3 * 0x10000;
}

/* ---- 0x004c4970  gzclose ---- */
undefined4 gzclose(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_1 == 0) {
    return 0xfffffffe;
  }
  if (*(char *)(param_1 + 0x5c) == 'w') {
    iVar1 = gz_do_flush(param_1,4);
    if (iVar1 == 0) {
      gz_putLong(*(void **)(param_1 + 0x40),*(uint *)(param_1 + 0x4c));
      gz_putLong(*(void **)(param_1 + 0x40),*(uint *)(param_1 + 8));
    }
  }
  uVar2 = gz_destroy(param_1);
  return uVar2;
}

/* ---- 0x004c49c0  gz_putLong ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void __cdecl gz_putLong(void *file,uint x)

{
  void *pvVar1;
  uint uVar2;
  int iVar3;
  
  pvVar1 = file;
  iVar3 = 4;
  uVar2 = x;
  do {
    file = (void *)CONCAT31(PIECE(file,1,3),(char)uVar2);
    (*(code *)g_pZfileFileIo[3])(pvVar1,&file,1);
    uVar2 = uVar2 >> 8;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return;
}
#endif


/* ---- 0x004c4c40  zlibVersion ---- */
/* MSVC CRT default _matherr: returns 0 (was mislabelled zlibVersion) */

undefined4 zlibVersion(void)

{
  return 0;
}

/* ---- 0x004c57d0  deflateParams_or_SetDictionary ---- */
/* zlib deflate.c helper taking the stream only; exact identity not confirmed */

undefined4 deflateParams_or_SetDictionary(int param_1)

{
  undefined *puVar1;
  uint uVar2;
  uint uVar3;
  int *piVar4;
  
  piVar4 = (int *)&STACK0X(0x00000008);
  uVar2 = UINT_004f1c20;
  uVar3 = UINT_008d783c;
  if (param_1 == 0) {
    return 0;
  }
  do {
    if (param_1 != 1) {
      return 0xffffffff;
    }
    if ((int)uVar2 < 0x32) {
      puVar1 = (undefined *)*piVar4;
      piVar4 = piVar4 + 1;
      (&PTR_DAT_004f1c28)[uVar2] = puVar1;
      UINT_004f1c20 = uVar2 + 1;
      uVar2 = UINT_004f1c20;
    }
    else if (uVar3 != 0) {
      (**(code **)(uVar3 + 0xc))(s_Too_many_zfilio_extension_set_004f1d3c);
      uVar2 = UINT_004f1c20;
      uVar3 = UINT_008d783c;
    }
    param_1 = *piVar4;
    piVar4 = piVar4 + 1;
  } while (param_1 != 0);
  return 0;
}

/* ---- 0x004c6040  inflateReset ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 inflateReset(int param_1)

{
  uint *puVar1;
  
  if ((param_1 != 0) && (puVar1 = *(uint **)(param_1 + 0x1c), puVar1 != (uint *)0x0)) {
    *(undefined4 *)(param_1 + 0x14) = 0;
    *(undefined4 *)(param_1 + 8) = 0;
    *(undefined4 *)(param_1 + 0x18) = 0;
    *puVar1 = -(uint)(puVar1[3] != 0) & 7;
    inflate_blocks_reset(*(undefined4 *)(*(int *)(param_1 + 0x1c) + 0x14),param_1,0);
    return 0;
  }
  return 0xfffffffe;
}
#endif


/* ---- 0x004c6090  inflateEnd ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 inflateEnd(int param_1)

{
  int iVar1;
  
  if (((param_1 != 0) && (*(int *)(param_1 + 0x1c) != 0)) && (*(int *)(param_1 + 0x24) != 0)) {
    iVar1 = *(int *)(*(int *)(param_1 + 0x1c) + 0x14);
    if (iVar1 != 0) {
      inflate_blocks_free(iVar1,param_1);
    }
    (**(code **)(param_1 + 0x24))(*(undefined4 *)(param_1 + 0x28),*(undefined4 *)(param_1 + 0x1c));
    *(undefined4 *)(param_1 + 0x1c) = 0;
    return 0;
  }
  return 0xfffffffe;
}
#endif


/* ---- 0x004c60e0  inflateInit2_ ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 inflateInit2_(int param_1,int param_2,char *param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  if (((param_3 == (char *)0x0) || (*param_3 != s_1_1_3_004f1a20[0])) || (param_4 != 0x38)) {
    return 0xfffffffa;
  }
  if (param_1 == 0) {
    return 0xfffffffe;
  }
  *(undefined4 *)(param_1 + 0x18) = 0;
  if (*(int *)(param_1 + 0x20) == 0) {
    *(code **)(param_1 + 0x20) = zcalloc;
    *(undefined4 *)(param_1 + 0x28) = 0;
  }
  if (*(int *)(param_1 + 0x24) == 0) {
    *(code **)(param_1 + 0x24) = FUN_004c7b10;
  }
  iVar1 = (**(code **)(param_1 + 0x20))(*(undefined4 *)(param_1 + 0x28),1,0x18);
  *(int *)(param_1 + 0x1c) = iVar1;
  if (iVar1 == 0) {
    return 0xfffffffc;
  }
  *(undefined4 *)(iVar1 + 0x14) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x1c) + 0xc) = 0;
  if (param_2 < 0) {
    param_2 = -param_2;
    *(undefined4 *)(*(int *)(param_1 + 0x1c) + 0xc) = 1;
  }
  if ((7 < param_2) && (param_2 < 0x10)) {
    *(int *)(*(int *)(param_1 + 0x1c) + 0x10) = param_2;
    uVar2 = inflate_blocks_new(param_1,~-(uint)(*(int *)(*(int *)(param_1 + 0x1c) + 0xc) != 0) &
                                       0x4c8990,1 << ((byte)param_2 & 0x1f));
    *(undefined4 *)(*(int *)(param_1 + 0x1c) + 0x14) = uVar2;
    if (*(int *)(*(int *)(param_1 + 0x1c) + 0x14) == 0) {
      ((code *)inflateEnd)();
      return 0xfffffffc;
    }
    inflateReset(param_1);
    return 0;
  }
  inflateEnd(param_1);
  return 0xfffffffe;
}
#endif


/* ---- 0x004c61f0  inflate ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined * inflate(int *param_1,int param_2)

{
  byte bVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined *puVar4;
  undefined *puVar5;
  
  if (((param_1 == (int *)0x0) || (param_1[7] == 0)) || (*param_1 == 0)) {
switchD_004c6240_default:
    return (undefined *)0xfffffffe;
  }
  puVar5 = (undefined *)((param_2 != 4) - 1 & 0xfffffffb);
  puVar4 = (undefined *)0xfffffffb;
  do {
    puVar2 = (undefined4 *)param_1[7];
    switch(*puVar2) {
    case 0:
      if (param_1[1] == 0) {
        return puVar4;
      }
      param_1[1] = param_1[1] + -1;
      param_1[2] = param_1[2] + 1;
      puVar2[1] = (uint)*(byte *)*param_1;
      puVar2 = (undefined4 *)param_1[7];
      uVar3 = puVar2[1];
      *param_1 = *param_1 + 1;
      if (((byte)uVar3 & 0xf) != 8) {
        *puVar2 = 0xd;
        param_1[6] = (int)s_unknown_compression_method_004f1f28;
        *(undefined4 *)(param_1[7] + 4) = 5;
        puVar4 = puVar5;
        break;
      }
      if ((uint)puVar2[4] < ((uint)puVar2[1] >> 4) + 8) {
        *puVar2 = 0xd;
        param_1[6] = (int)s_invalid_window_size_004f1f14;
        *(undefined4 *)(param_1[7] + 4) = 5;
        puVar4 = puVar5;
        break;
      }
      *puVar2 = 1;
      puVar4 = puVar5;
    case 1:
      if (param_1[1] == 0) {
        return puVar4;
      }
      param_1[1] = param_1[1] + -1;
      puVar2 = (undefined4 *)param_1[7];
      param_1[2] = param_1[2] + 1;
      bVar1 = *(byte *)*param_1;
      *param_1 = (int)((byte *)*param_1 + 1);
      if ((puVar2[1] * 0x100 + (uint)bVar1) % 0x1f == 0) {
        if ((bVar1 & 0x20) != 0) {
          *(undefined4 *)param_1[7] = 2;
          puVar4 = puVar5;
          goto switchD_004c6240_caseD_2;
        }
        *puVar2 = 7;
        puVar4 = puVar5;
      }
      else {
        *puVar2 = 0xd;
        param_1[6] = (int)s_incorrect_header_check_004f1efc;
        *(undefined4 *)(param_1[7] + 4) = 5;
        puVar4 = puVar5;
      }
      break;
    case 2:
switchD_004c6240_caseD_2:
      if (param_1[1] == 0) {
        return puVar4;
      }
      param_1[2] = param_1[2] + 1;
      param_1[1] = param_1[1] + -1;
      *(uint *)(param_1[7] + 8) = (uint)*(byte *)*param_1 << 0x18;
      *param_1 = *param_1 + 1;
      *(undefined4 *)param_1[7] = 3;
      puVar4 = puVar5;
switchD_004c6240_caseD_3:
      if (param_1[1] == 0) {
        return puVar4;
      }
      param_1[1] = param_1[1] + -1;
      param_1[2] = param_1[2] + 1;
      *(uint *)(param_1[7] + 8) = *(int *)(param_1[7] + 8) + (uint)*(byte *)*param_1 * 0x10000;
      *param_1 = *param_1 + 1;
      *(undefined4 *)param_1[7] = 4;
      puVar4 = puVar5;
switchD_004c6240_caseD_4:
      if (param_1[1] == 0) {
        return puVar4;
      }
      param_1[1] = param_1[1] + -1;
      param_1[2] = param_1[2] + 1;
      *(uint *)(param_1[7] + 8) = *(int *)(param_1[7] + 8) + (uint)*(byte *)*param_1 * 0x100;
      *param_1 = *param_1 + 1;
      *(undefined4 *)param_1[7] = 5;
      puVar4 = puVar5;
switchD_004c6240_caseD_5:
      if (param_1[1] == 0) {
        return puVar4;
      }
      param_1[1] = param_1[1] + -1;
      param_1[2] = param_1[2] + 1;
      *(uint *)(param_1[7] + 8) = *(int *)(param_1[7] + 8) + (uint)*(byte *)*param_1;
      *param_1 = *param_1 + 1;
      param_1[0xc] = ((undefined4 *)param_1[7])[2];
      *(undefined4 *)param_1[7] = 6;
      return (undefined *)0x2;
    case 3:
      goto switchD_004c6240_caseD_3;
    case 4:
      goto switchD_004c6240_caseD_4;
    case 5:
      goto switchD_004c6240_caseD_5;
    case 6:
      *(undefined4 *)param_1[7] = 0xd;
      param_1[6] = (int)s_need_dictionary_004f1ed4;
      *(undefined4 *)(param_1[7] + 4) = 0;
      return (undefined *)0xfffffffe;
    case 7:
      puVar4 = inflate_blocks((uint *)puVar2[5],param_1,(uint)puVar4);
      if (puVar4 == (undefined *)0xfffffffd) {
        *(undefined4 *)param_1[7] = 0xd;
        *(undefined4 *)(param_1[7] + 4) = 0;
        puVar4 = (undefined *)0xfffffffd;
      }
      else {
        if (puVar4 == (undefined *)0x0) {
          puVar4 = puVar5;
        }
        if (puVar4 != (undefined *)0x1) {
          return puVar4;
        }
        inflate_blocks_reset(*(undefined4 *)(param_1[7] + 0x14),param_1,param_1[7] + 4);
        puVar2 = (undefined4 *)param_1[7];
        if (puVar2[3] == 0) {
          *puVar2 = 8;
          puVar4 = puVar5;
          goto switchD_004c6240_caseD_8;
        }
        *puVar2 = 0xc;
        puVar4 = puVar5;
      }
      break;
    case 8:
switchD_004c6240_caseD_8:
      if (param_1[1] == 0) {
        return puVar4;
      }
      param_1[1] = param_1[1] + -1;
      param_1[2] = param_1[2] + 1;
      *(uint *)(param_1[7] + 8) = (uint)*(byte *)*param_1 << 0x18;
      *param_1 = *param_1 + 1;
      *(undefined4 *)param_1[7] = 9;
      puVar4 = puVar5;
switchD_004c6240_caseD_9:
      if (param_1[1] == 0) {
        return puVar4;
      }
      param_1[2] = param_1[2] + 1;
      param_1[1] = param_1[1] + -1;
      *(uint *)(param_1[7] + 8) = *(int *)(param_1[7] + 8) + (uint)*(byte *)*param_1 * 0x10000;
      *param_1 = *param_1 + 1;
      *(undefined4 *)param_1[7] = 10;
      puVar4 = puVar5;
switchD_004c6240_caseD_a:
      if (param_1[1] == 0) {
        return puVar4;
      }
      param_1[2] = param_1[2] + 1;
      param_1[1] = param_1[1] + -1;
      *(uint *)(param_1[7] + 8) = *(int *)(param_1[7] + 8) + (uint)*(byte *)*param_1 * 0x100;
      *param_1 = *param_1 + 1;
      *(undefined4 *)param_1[7] = 0xb;
      puVar4 = puVar5;
switchD_004c6240_caseD_b:
      if (param_1[1] == 0) {
        return puVar4;
      }
      param_1[1] = param_1[1] + -1;
      param_1[2] = param_1[2] + 1;
      *(uint *)(param_1[7] + 8) = *(int *)(param_1[7] + 8) + (uint)*(byte *)*param_1;
      *param_1 = *param_1 + 1;
      puVar2 = (undefined4 *)param_1[7];
      if (puVar2[1] == puVar2[2]) {
        *(undefined4 *)param_1[7] = 0xc;
switchD_004c6240_caseD_c:
        return (undefined *)0x1;
      }
      *puVar2 = 0xd;
      param_1[6] = (int)s_incorrect_data_check_004f1ee4;
      *(undefined4 *)(param_1[7] + 4) = 5;
      puVar4 = puVar5;
      break;
    case 9:
      goto switchD_004c6240_caseD_9;
    case 10:
      goto switchD_004c6240_caseD_a;
    case 0xb:
      goto switchD_004c6240_caseD_b;
    case 0xc:
      goto switchD_004c6240_caseD_c;
    case 0xd:
      return (undefined *)0xfffffffd;
    default:
      goto switchD_004c6240_default;
    }
  } while( true );
}
#endif


/* ---- 0x004c6640  deflateInit2_ ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4
deflateInit2_(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,char *param_7,
             int param_8)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  bool bVar6;
  
  if (((param_7 == (char *)0x0) || (*param_7 != *PTR_s_1_1_3_004f1f44)) || (param_8 != 0x38)) {
    return 0xfffffffa;
  }
  if (param_1 == 0) {
    return 0xfffffffe;
  }
  *(undefined4 *)(param_1 + 0x18) = 0;
  if (*(int *)(param_1 + 0x20) == 0) {
    *(code **)(param_1 + 0x20) = zcalloc;
    *(undefined4 *)(param_1 + 0x28) = 0;
  }
  if (*(int *)(param_1 + 0x24) == 0) {
    *(code **)(param_1 + 0x24) = FUN_004c7b10;
  }
  if (param_2 == -1) {
    param_2 = 6;
  }
  bVar6 = param_4 < 0;
  if (bVar6) {
    param_4 = -param_4;
  }
  if (((((0 < param_5) && (param_5 < 10)) && ((param_3 == 8 && ((7 < param_4 && (param_4 < 0x10)))))
       ) && (-1 < param_2)) && (((param_2 < 10 && (-1 < param_6)) && (param_6 < 3)))) {
    piVar2 = (int *)(**(code **)(param_1 + 0x20))(*(undefined4 *)(param_1 + 0x28),1,0x16b8);
    if (piVar2 == (int *)0x0) {
      return 0xfffffffc;
    }
    *(int **)(param_1 + 0x1c) = piVar2;
    piVar2[6] = (uint)bVar6;
    iVar5 = 1 << ((byte)param_4 & 0x1f);
    piVar2[10] = param_4;
    *piVar2 = param_1;
    piVar2[0x12] = param_5 + 7;
    piVar2[9] = iVar5;
    piVar2[0xb] = iVar5 + -1;
    iVar3 = 1 << ((byte)(param_5 + 7) & 0x1f);
    piVar2[0x11] = iVar3;
    piVar2[0x13] = iVar3 + -1;
    piVar2[0x14] = (param_5 + 9U) / 3;
    iVar3 = (**(code **)(param_1 + 0x20))(*(undefined4 *)(param_1 + 0x28),iVar5,2);
    piVar2[0xc] = iVar3;
    iVar3 = (**(code **)(param_1 + 0x20))(*(undefined4 *)(param_1 + 0x28),piVar2[9],2);
    piVar2[0xe] = iVar3;
    iVar3 = (**(code **)(param_1 + 0x20))(*(undefined4 *)(param_1 + 0x28),piVar2[0x11],2);
    piVar2[0xf] = iVar3;
    iVar3 = 1 << ((char)param_5 + 6U & 0x1f);
    piVar2[0x5a5] = iVar3;
    iVar3 = (**(code **)(param_1 + 0x20))(*(undefined4 *)(param_1 + 0x28),iVar3,4);
    uVar1 = piVar2[0x5a5];
    piVar2[2] = iVar3;
    piVar2[3] = uVar1 * 4;
    if (((piVar2[0xc] != 0) && (piVar2[0xe] != 0)) && ((piVar2[0xf] != 0 && (iVar3 != 0)))) {
      *(undefined1 *)((int)piVar2 + 0x1d) = 8;
      piVar2[0x5a7] = iVar3 + (uVar1 & 0xfffffffe);
      piVar2[0x5a4] = iVar3 + uVar1 * 3;
      piVar2[0x20] = param_6;
      piVar2[0x1f] = param_2;
      uVar4 = deflateReset(param_1);
      return uVar4;
    }
    *(undefined **)(param_1 + 0x18) = PTR_s_insufficient_memory_004f1f60;
    deflateEnd(param_1);
    return 0xfffffffc;
  }
  return 0xfffffffe;
}
#endif


/* ---- 0x004c6870  deflateReset ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 deflateReset(int param_1)

{
  int iVar1;
  
  if ((((param_1 != 0) && (iVar1 = *(int *)(param_1 + 0x1c), iVar1 != 0)) &&
      (*(int *)(param_1 + 0x20) != 0)) && (*(int *)(param_1 + 0x24) != 0)) {
    *(undefined4 *)(param_1 + 0x14) = 0;
    *(undefined4 *)(param_1 + 8) = 0;
    *(undefined4 *)(param_1 + 0x18) = 0;
    *(undefined4 *)(param_1 + 0x2c) = 2;
    *(undefined4 *)(iVar1 + 0x14) = 0;
    *(undefined4 *)(iVar1 + 0x10) = *(undefined4 *)(iVar1 + 8);
    if (*(int *)(iVar1 + 0x18) < 0) {
      *(undefined4 *)(iVar1 + 0x18) = 0;
    }
    *(uint *)(iVar1 + 4) = (-(uint)(*(int *)(iVar1 + 0x18) != 0) & 0x47) + 0x2a;
    *(undefined4 *)(param_1 + 0x30) = 1;
    *(undefined4 *)(iVar1 + 0x20) = 0;
    _tr_init(iVar1);
    lm_init(iVar1);
    return 0;
  }
  return 0xfffffffe;
}
#endif


/* ---- 0x004c68f0  deflate ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint deflate(int *param_1,int param_2)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  
  if ((((param_1 == (int *)0x0) || (puVar1 = (undefined4 *)param_1[7], puVar1 == (undefined4 *)0x0))
      || (4 < param_2)) || (param_2 < 0)) {
    return 0xfffffffe;
  }
  if (((param_1[3] == 0) || ((*param_1 == 0 && (param_1[1] != 0)))) ||
     ((puVar1[1] == 0x29a && (param_2 != 4)))) {
    param_1[6] = (int)PTR_s_stream_error_004f1f58;
    return 0xfffffffe;
  }
  if (param_1[4] == 0) {
    param_1[6] = (int)PTR_s_buffer_error_004f1f64;
    return 0xfffffffb;
  }
  iVar3 = puVar1[8];
  *puVar1 = param_1;
  puVar1[8] = param_2;
  if (puVar1[1] == 0x2a) {
    uVar2 = puVar1[0x1f] + -1 >> 1;
    if (3 < uVar2) {
      uVar2 = 3;
    }
    uVar2 = puVar1[10] * 0x1000 - 0x7800U | uVar2 << 6;
    if (puVar1[0x19] != 0) {
      uVar2 = uVar2 | 0x20;
    }
    puVar1[1] = 0x71;
    putShortMSB(puVar1,(uVar2 - uVar2 % 0x1f) + 0x1f);
    if (puVar1[0x19] != 0) {
      putShortMSB(puVar1,(uint)param_1[0xc] >> 0x10);
      putShortMSB(puVar1,param_1[0xc] & 0xffff);
    }
    param_1[0xc] = 1;
  }
  if (puVar1[5] == 0) {
    if (((param_1[1] == 0) && (param_2 <= iVar3)) && (param_2 != 4)) {
      param_1[6] = (int)PTR_s_buffer_error_004f1f64;
      return 0xfffffffb;
    }
  }
  else {
    flush_pending(param_1);
    if (param_1[4] == 0) {
      puVar1[8] = 0xffffffff;
      return 0;
    }
  }
  if (puVar1[1] == 0x29a) {
    if (param_1[1] != 0) {
      param_1[6] = (int)PTR_s_buffer_error_004f1f64;
      return 0xfffffffb;
    }
LAB_004c6a65:
    if ((puVar1[0x1b] == 0) && ((param_2 == 0 || (puVar1[1] == 0x29a)))) goto LAB_004c6b1f;
  }
  else if (param_1[1] == 0) goto LAB_004c6a65;
  iVar3 = (**(code **)(&DAT_004d9838 + puVar1[0x1f] * 0xc))(puVar1,param_2);
  if ((iVar3 == 2) || (iVar3 == 3)) {
    puVar1[1] = 0x29a;
  }
  if ((iVar3 == 0) || (iVar3 == 2)) {
    if (param_1[4] == 0) {
      puVar1[8] = 0xffffffff;
    }
    return 0;
  }
  if (iVar3 == 1) {
    if (param_2 == 1) {
      _tr_align(puVar1);
    }
    else {
      FUN_004c8ba0(puVar1,0,0,0);
      if (param_2 == 3) {
        *(undefined2 *)(puVar1[0xf] + -2 + puVar1[0x11] * 2) = 0;
        uVar2 = puVar1[0x11] * 2 - 2;
        puVar5 = (undefined4 *)puVar1[0xf];
        for (uVar4 = uVar2 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
          *puVar5 = 0;
          puVar5 = puVar5 + 1;
        }
        for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
          *(undefined1 *)puVar5 = 0;
          puVar5 = (undefined4 *)((int)puVar5 + 1);
        }
      }
    }
    flush_pending(param_1);
    if (param_1[4] == 0) {
      puVar1[8] = 0xffffffff;
      return 0;
    }
  }
LAB_004c6b1f:
  if (param_2 != 4) {
    return 0;
  }
  if (puVar1[6] == 0) {
    putShortMSB(puVar1,(uint)param_1[0xc] >> 0x10);
    putShortMSB(puVar1,param_1[0xc] & 0xffff);
    flush_pending(param_1);
    puVar1[6] = 0xffffffff;
    return (uint)(puVar1[5] == 0);
  }
  return 1;
}
#endif


/* ---- 0x004c6bb0  putShortMSB ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void putShortMSB(int param_1,undefined4 param_2)

{
  int iVar1;
  
  *(char *)(*(int *)(param_1 + 8) + *(int *)(param_1 + 0x14)) = (char)((uint)param_2 >> 8);
  iVar1 = *(int *)(param_1 + 0x14) + 1;
  *(int *)(param_1 + 0x14) = iVar1;
  *(char *)(*(int *)(param_1 + 8) + iVar1) = (char)param_2;
  *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
  return;
}
#endif


/* ---- 0x004c6be0  flush_pending ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void flush_pending(int param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  uVar3 = *(uint *)(*(int *)(param_1 + 0x1c) + 0x14);
  if (*(uint *)(param_1 + 0x10) < uVar3) {
    uVar3 = *(uint *)(param_1 + 0x10);
  }
  if (uVar3 != 0) {
    puVar4 = *(undefined4 **)(*(int *)(param_1 + 0x1c) + 0x10);
    puVar5 = *(undefined4 **)(param_1 + 0xc);
    for (uVar2 = uVar3 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
    for (uVar2 = uVar3 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(undefined1 *)puVar5 = *(undefined1 *)puVar4;
      puVar4 = (undefined4 *)((int)puVar4 + 1);
      puVar5 = (undefined4 *)((int)puVar5 + 1);
    }
    *(uint *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + uVar3;
    *(uint *)(*(int *)(param_1 + 0x1c) + 0x10) = *(int *)(*(int *)(param_1 + 0x1c) + 0x10) + uVar3;
    *(uint *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + uVar3;
    *(uint *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) - uVar3;
    *(uint *)(*(int *)(param_1 + 0x1c) + 0x14) = *(int *)(*(int *)(param_1 + 0x1c) + 0x14) - uVar3;
    iVar1 = *(int *)(param_1 + 0x1c);
    if (*(int *)(iVar1 + 0x14) == 0) {
      *(undefined4 *)(iVar1 + 0x10) = *(undefined4 *)(iVar1 + 8);
    }
  }
  return;
}
#endif


/* ---- 0x004c6c60  deflateEnd ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint deflateEnd(int param_1)

{
  int iVar1;
  int iVar2;
  
  if (((param_1 != 0) && (iVar1 = *(int *)(param_1 + 0x1c), iVar1 != 0)) &&
     ((iVar2 = *(int *)(iVar1 + 4), iVar2 == 0x2a || ((iVar2 == 0x71 || (iVar2 == 0x29a)))))) {
    if (*(int *)(iVar1 + 8) != 0) {
      (**(code **)(param_1 + 0x24))(*(undefined4 *)(param_1 + 0x28),*(int *)(iVar1 + 8));
    }
    iVar1 = *(int *)(*(int *)(param_1 + 0x1c) + 0x3c);
    if (iVar1 != 0) {
      (**(code **)(param_1 + 0x24))(*(undefined4 *)(param_1 + 0x28),iVar1);
    }
    iVar1 = *(int *)(*(int *)(param_1 + 0x1c) + 0x38);
    if (iVar1 != 0) {
      (**(code **)(param_1 + 0x24))(*(undefined4 *)(param_1 + 0x28),iVar1);
    }
    iVar1 = *(int *)(*(int *)(param_1 + 0x1c) + 0x30);
    if (iVar1 != 0) {
      (**(code **)(param_1 + 0x24))(*(undefined4 *)(param_1 + 0x28),iVar1);
    }
    (**(code **)(param_1 + 0x24))(*(undefined4 *)(param_1 + 0x28),*(undefined4 *)(param_1 + 0x1c));
    *(undefined4 *)(param_1 + 0x1c) = 0;
    return (iVar2 != 0x71) - 1 & 0xfffffffd;
  }
  return 0xfffffffe;
}
#endif


/* ---- 0x004c6d10  lm_init ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* deflate.c: window_size = 2*w_size, clears the hash head table */

void lm_init(int param_1)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  
  *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x24) << 1;
  *(undefined2 *)(*(int *)(param_1 + 0x3c) + -2 + *(int *)(param_1 + 0x44) * 2) = 0;
  uVar4 = *(int *)(param_1 + 0x44) * 2 - 2;
  puVar5 = *(undefined4 **)(param_1 + 0x3c);
  for (uVar3 = uVar4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined1 *)puVar5 = 0;
    puVar5 = (undefined4 *)((int)puVar5 + 1);
  }
  iVar2 = *(int *)(param_1 + 0x7c) * 0xc;
  *(uint *)(param_1 + 0x78) = (uint)*(ushort *)(&DAT_004d9832 + iVar2);
  *(uint *)(param_1 + 0x84) = (uint)*(ushort *)(&DAT_004d9830 + iVar2);
  *(uint *)(param_1 + 0x88) = (uint)*(ushort *)(&DAT_004d9834 + iVar2);
  uVar1 = *(ushort *)(&DAT_004d9836 + iVar2);
  *(undefined4 *)(param_1 + 100) = 0;
  *(undefined4 *)(param_1 + 0x54) = 0;
  *(undefined4 *)(param_1 + 0x6c) = 0;
  *(undefined4 *)(param_1 + 0x60) = 0;
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(uint *)(param_1 + 0x74) = (uint)uVar1;
  *(undefined4 *)(param_1 + 0x70) = 2;
  *(undefined4 *)(param_1 + 0x58) = 2;
  return;
}
#endif


/* ---- 0x004c79b0  crc32 ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint crc32(uint param_1,byte *param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  
  if (param_2 == (byte *)0x0) {
    return 0;
  }
  param_1 = ~param_1;
  if (7 < param_3) {
    uVar2 = param_3 >> 3;
    do {
      param_3 = param_3 - 8;
      uVar1 = *(uint *)(&DAT_004d98a8 + (param_1 & 0xff ^ (uint)*param_2) * 4) ^ param_1 >> 8;
      uVar1 = *(uint *)(&DAT_004d98a8 + (uVar1 & 0xff ^ (uint)param_2[1]) * 4) ^ uVar1 >> 8;
      uVar1 = *(uint *)(&DAT_004d98a8 + (uVar1 & 0xff ^ (uint)param_2[2]) * 4) ^ uVar1 >> 8;
      uVar1 = *(uint *)(&DAT_004d98a8 + (uVar1 & 0xff ^ (uint)param_2[3]) * 4) ^ uVar1 >> 8;
      uVar1 = *(uint *)(&DAT_004d98a8 + (uVar1 & 0xff ^ (uint)param_2[4]) * 4) ^ uVar1 >> 8;
      uVar1 = *(uint *)(&DAT_004d98a8 + (uVar1 & 0xff ^ (uint)param_2[5]) * 4) ^ uVar1 >> 8;
      uVar1 = *(uint *)(&DAT_004d98a8 + (uVar1 & 0xff ^ (uint)param_2[6]) * 4) ^ uVar1 >> 8;
      param_1 = uVar1 >> 8 ^ *(uint *)(&DAT_004d98a8 + (uVar1 & 0xff ^ (uint)param_2[7]) * 4);
      param_2 = param_2 + 8;
      uVar2 = uVar2 - 1;
    } while (uVar2 != 0);
  }
  for (; param_3 != 0; param_3 = param_3 - 1) {
    param_1 = param_1 >> 8 ^ *(uint *)(&DAT_004d98a8 + (param_1 & 0xff ^ (uint)*param_2) * 4);
    param_2 = param_2 + 1;
  }
  return ~param_1;
}
#endif


/* ---- 0x004c7af0  zcalloc ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void zcalloc(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  calloc(param_2,param_3);
  return;
}
#endif


/* ---- 0x004c7b20  inflate_blocks_reset ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void inflate_blocks_reset(int *param_1,int param_2,int *param_3)

{
  int iVar1;
  
  if (param_3 != (int *)0x0) {
    *param_3 = param_1[0xf];
  }
  if ((*param_1 == 4) || (*param_1 == 5)) {
    (**(code **)(param_2 + 0x24))(*(undefined4 *)(param_2 + 0x28),param_1[3]);
  }
  if (*param_1 == 6) {
    inflate_codes_free(param_1[1],param_2);
  }
  *param_1 = 0;
  param_1[0xd] = param_1[10];
  param_1[0xc] = param_1[10];
  param_1[7] = 0;
  param_1[8] = 0;
  if ((code *)param_1[0xe] != (code *)0x0) {
    iVar1 = (*(code *)param_1[0xe])(0,0,0);
    param_1[0xf] = iVar1;
    *(int *)(param_2 + 0x30) = iVar1;
  }
  return;
}
#endif


/* ---- 0x004c7ba0  inflate_blocks_new ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 * inflate_blocks_new(int param_1,undefined4 param_2,int param_3)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = (undefined4 *)(**(code **)(param_1 + 0x20))(*(undefined4 *)(param_1 + 0x28),1,0x40);
  if (puVar1 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  iVar2 = (**(code **)(param_1 + 0x20))(*(undefined4 *)(param_1 + 0x28),8,0x5a0);
  puVar1[9] = iVar2;
  if (iVar2 == 0) {
    (**(code **)(param_1 + 0x24))(*(undefined4 *)(param_1 + 0x28),puVar1);
    return (undefined4 *)0x0;
  }
  iVar2 = (**(code **)(param_1 + 0x20))(*(undefined4 *)(param_1 + 0x28),1,param_3);
  puVar1[10] = iVar2;
  if (iVar2 == 0) {
    (**(code **)(param_1 + 0x24))(*(undefined4 *)(param_1 + 0x28),puVar1[9]);
    (**(code **)(param_1 + 0x24))(*(undefined4 *)(param_1 + 0x28),puVar1);
    return (undefined4 *)0x0;
  }
  puVar1[0xb] = param_3 + iVar2;
  puVar1[0xe] = param_2;
  *puVar1 = 0;
  inflate_blocks_reset(puVar1,param_1,0);
  return puVar1;
}
#endif


/* ---- 0x004c7c50  inflate_blocks ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined * __cdecl inflate_blocks(uint *param_1,int *param_2,uint param_3)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  uint *puVar2;
  int iVar3;
  undefined4 uVar4;
  undefined *puVar5;
  uint uVar6;
  uint uVar7;
  uint *puVar8;
  uint uVar9;
  uint *puVar10;
  byte *pbVar11;
  byte *pbVar12;
  #define local_30 (*(uint *)(_frame + (0x40 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x40 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x40 - 0x4)))
  
  puVar2 = param_1;
  local_2c = *param_2;
  local_30 = param_2[1];
  local_28 = param_1[8];
  uVar7 = param_1[7];
  puVar8 = (uint *)param_1[0xd];
  if (puVar8 < (uint *)param_1[0xc]) {
    local_24 = (int)param_1[0xc] + (-1 - (int)puVar8);
    param_1 = puVar8;
  }
  else {
    local_24 = param_1[0xb] - (int)puVar8;
    param_1 = puVar8;
  }
switchD_004c7d01_default:
  uVar9 = local_28;
  pbVar11 = (byte *)local_2c;
  pbVar12 = (byte *)local_2c;
  switch(*puVar2) {
  case 0:
    for (; local_2c = (uint)pbVar12, local_28 = uVar9, uVar7 < 3; uVar7 = uVar7 + 8) {
      if (local_30 == 0) {
        puVar2[8] = uVar9;
        puVar2[7] = uVar7;
        param_2[1] = 0;
        param_2[2] = (int)(pbVar12 + (param_2[2] - *param_2));
        *param_2 = (int)pbVar12;
        puVar2[0xd] = (uint)param_1;
        puVar5 = (undefined *)inflate_flush(puVar2,param_2,param_3);
        return puVar5;
      }
      local_30 = local_30 - 1;
      param_3 = 0;
      uVar9 = uVar9 | (uint)*pbVar12 << ((byte)uVar7 & 0x1f);
      pbVar12 = pbVar12 + 1;
    }
    puVar2[6] = uVar9 & 1;
    switch((uVar9 & 7) >> 1) {
    case 0:
      *puVar2 = 1;
      uVar6 = uVar7 - 3 & 7;
      local_28 = (uVar9 >> 3) >> (sbyte)uVar6;
      uVar7 = (uVar7 - 3) - uVar6;
      break;
    case 1:
      ((code *)inflate_trees_fixed)(&local_14,&local_18,&local_1c,&local_20,param_2);
      puVar5 = inflate_codes_new((char)local_14,(char)local_18,local_1c,local_20,(int)param_2);
      puVar2[1] = (uint)puVar5;
      if (puVar5 == (undefined *)0x0) {
LAB_004c8562:
        puVar2[8] = uVar9;
        puVar2[7] = uVar7;
        param_2[1] = local_30;
        param_2[2] = (int)(pbVar12 + (param_2[2] - *param_2));
        *param_2 = (int)pbVar12;
        puVar2[0xd] = (uint)param_1;
        puVar5 = (undefined *)inflate_flush(puVar2,param_2,0xfffffffc);
        return puVar5;
      }
      local_28 = uVar9 >> 3;
      uVar7 = uVar7 - 3;
      *puVar2 = 6;
      break;
    case 2:
      local_28 = uVar9 >> 3;
      uVar7 = uVar7 - 3;
      *puVar2 = 3;
      break;
    case 3:
      *puVar2 = 9;
      param_2[6] = (int)s_invalid_block_type_004f2040;
      puVar2[8] = uVar9 >> 3;
      puVar2[7] = uVar7 - 3;
      param_2[1] = local_30;
      param_2[2] = (int)(pbVar12 + (param_2[2] - *param_2));
      *param_2 = (int)pbVar12;
      puVar2[0xd] = (uint)param_1;
      puVar5 = (undefined *)inflate_flush(puVar2,param_2,0xfffffffd);
      return puVar5;
    }
    goto switchD_004c7d01_default;
  case 1:
    for (; uVar7 < 0x20; uVar7 = uVar7 + 8) {
      if (local_30 == 0) {
        puVar2[8] = uVar9;
        puVar2[7] = uVar7;
        iVar3 = *param_2;
        param_2[1] = 0;
        *param_2 = local_2c;
        param_2[2] = (int)(local_2c + (param_2[2] - iVar3));
        puVar2[0xd] = (uint)param_1;
        puVar5 = (undefined *)inflate_flush(puVar2,param_2,param_3);
        return puVar5;
      }
      param_3 = 0;
      local_30 = local_30 - 1;
      uVar9 = uVar9 | (uint)*(byte *)local_2c << ((byte)uVar7 & 0x1f);
      local_2c = local_2c + 1;
    }
    uVar6 = uVar9 & 0xffff;
    if (~uVar9 >> 0x10 != uVar6) {
      *puVar2 = 9;
      param_2[6] = (int)s_invalid_stored_block_lengths_004f2020;
      puVar2[8] = uVar9;
      puVar2[7] = uVar7;
      iVar3 = *param_2;
      *param_2 = local_2c;
      param_2[1] = local_30;
      param_2[2] = (int)(local_2c + (param_2[2] - iVar3));
      puVar2[0xd] = (uint)param_1;
      puVar5 = (undefined *)inflate_flush(puVar2,param_2,0xfffffffd);
      return puVar5;
    }
    uVar7 = 0;
    puVar2[1] = uVar6;
    local_28 = 0;
    if (uVar6 != 0) {
      *puVar2 = 2;
      goto switchD_004c7d01_default;
    }
    break;
  case 2:
    if (local_30 == 0) {
      puVar2[8] = local_28;
      puVar2[7] = uVar7;
      iVar3 = *param_2;
      *param_2 = local_2c;
      param_2[1] = 0;
      param_2[2] = param_2[2] + (local_2c - iVar3);
      puVar2[0xd] = (uint)param_1;
      puVar5 = (undefined *)inflate_flush(puVar2,param_2,param_3);
      return puVar5;
    }
    if (local_24 == 0) {
      if (param_1 == (uint *)puVar2[0xb]) {
        puVar8 = (uint *)puVar2[0xc];
        puVar10 = (uint *)puVar2[10];
        if (puVar8 != puVar10) {
          param_1 = puVar10;
          if (puVar10 < puVar8) {
            local_24 = (int)puVar8 + (-1 - (int)puVar10);
          }
          else {
            local_24 = (int)puVar2[0xb] - (int)puVar10;
          }
        }
      }
      if (local_24 == 0) {
        puVar2[0xd] = (uint)param_1;
        uVar4 = inflate_flush(puVar2,param_2,param_3);
        param_1 = (uint *)puVar2[0xd];
        puVar8 = (uint *)puVar2[0xc];
        if (param_1 < puVar8) {
          local_24 = (int)puVar8 + (-1 - (int)param_1);
        }
        else {
          local_24 = puVar2[0xb] - (int)param_1;
        }
        if ((param_1 == (uint *)puVar2[0xb]) && (puVar10 = (uint *)puVar2[10], puVar8 != puVar10)) {
          param_1 = puVar10;
          if (puVar10 < puVar8) {
            local_24 = (int)puVar8 + (-1 - (int)puVar10);
          }
          else {
            local_24 = (int)puVar2[0xb] - (int)puVar10;
          }
        }
        if (local_24 == 0) {
          puVar2[8] = local_28;
          puVar2[7] = uVar7;
          iVar3 = *param_2;
          param_2[1] = local_30;
          *param_2 = local_2c;
          param_2[2] = param_2[2] + (local_2c - iVar3);
          puVar2[0xd] = (uint)param_1;
          puVar5 = (undefined *)inflate_flush(puVar2,param_2,uVar4);
          return puVar5;
        }
      }
    }
    param_3 = 0;
    uVar9 = puVar2[1];
    if (local_30 < puVar2[1]) {
      uVar9 = local_30;
    }
    if (local_24 < uVar9) {
      uVar9 = local_24;
    }
    puVar8 = (uint *)local_2c;
    puVar10 = param_1;
    for (uVar6 = uVar9 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *puVar10 = *puVar8;
      puVar8 = puVar8 + 1;
      puVar10 = puVar10 + 1;
    }
    local_24 = local_24 - uVar9;
    for (uVar6 = uVar9 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(char *)puVar10 = (char)*puVar8;
      puVar8 = (uint *)((int)puVar8 + 1);
      puVar10 = (uint *)((int)puVar10 + 1);
    }
    local_2c = local_2c + uVar9;
    uVar6 = puVar2[1];
    local_30 = local_30 - uVar9;
    param_1 = (uint *)((int)param_1 + uVar9);
    puVar2[1] = uVar6 - uVar9;
    if (uVar6 - uVar9 != 0) goto switchD_004c7d01_default;
    break;
  case 3:
    for (; local_2c = (uint)pbVar12, uVar7 < 0xe; uVar7 = uVar7 + 8) {
      if (local_30 == 0) {
LAB_004c8686:
        puVar2[8] = uVar9;
        puVar2[7] = uVar7;
        param_2[1] = 0;
        param_2[2] = (int)(pbVar12 + (param_2[2] - *param_2));
        *param_2 = (int)pbVar12;
        puVar2[0xd] = (uint)param_1;
        puVar5 = (undefined *)inflate_flush(puVar2,param_2,param_3);
        return puVar5;
      }
      local_30 = local_30 - 1;
      param_3 = 0;
      uVar9 = uVar9 | (uint)*pbVar12 << ((byte)uVar7 & 0x1f);
      pbVar12 = pbVar12 + 1;
    }
    puVar2[1] = uVar9 & 0x3fff;
    if ((0x1d < (uVar9 & 0x1f)) || (0x3a0 < (uVar9 & 0x3e0))) {
      *puVar2 = 9;
      param_2[6] = (int)s_too_many_length_or_distance_symb_004f1ffc;
      puVar2[8] = uVar9;
      puVar2[7] = uVar7;
      param_2[1] = local_30;
      param_2[2] = (int)(pbVar12 + (param_2[2] - *param_2));
      *param_2 = (int)pbVar12;
      puVar2[0xd] = (uint)param_1;
      puVar5 = (undefined *)inflate_flush(puVar2,param_2,0xfffffffd);
      return puVar5;
    }
    uVar6 = (*(code *)param_2[8])
                      (param_2[10],((uVar9 & 0x3fff) >> 5 & 0x1f) + 0x102 + (uVar9 & 0x1f),4);
    puVar2[3] = uVar6;
    if (uVar6 == 0) goto LAB_004c8562;
    uVar9 = uVar9 >> 0xe;
    uVar7 = uVar7 - 0xe;
    puVar2[2] = 0;
    *puVar2 = 4;
    pbVar11 = pbVar12;
    goto LAB_004c7ff2;
  case 4:
LAB_004c7ff2:
    if (puVar2[2] < (puVar2[1] >> 10) + 4) {
      do {
        for (; uVar7 < 3; uVar7 = uVar7 + 8) {
          if (local_30 == 0) {
LAB_004c8647:
            puVar2[8] = uVar9;
            puVar2[7] = uVar7;
            param_2[1] = 0;
            param_2[2] = (int)(pbVar11 + (param_2[2] - *param_2));
            *param_2 = (int)pbVar11;
            puVar2[0xd] = (uint)param_1;
            puVar5 = (undefined *)inflate_flush(puVar2,param_2,param_3);
            return puVar5;
          }
          local_30 = local_30 - 1;
          param_3 = 0;
          uVar9 = uVar9 | (uint)*pbVar11 << ((byte)uVar7 & 0x1f);
          pbVar11 = pbVar11 + 1;
          local_2c = (uint)pbVar11;
        }
        uVar6 = uVar9 & 7;
        uVar7 = uVar7 - 3;
        uVar9 = uVar9 >> 3;
        *(uint *)(puVar2[3] + *(int *)(&DAT_004d9ca8 + puVar2[2] * 4) * 4) = uVar6;
        uVar6 = puVar2[2];
        puVar2[2] = uVar6 + 1;
      } while (uVar6 + 1 < (puVar2[1] >> 10) + 4);
    }
    uVar6 = puVar2[2];
    while (uVar6 < 0x13) {
      *(undefined4 *)(puVar2[3] + *(int *)(&DAT_004d9ca8 + puVar2[2] * 4) * 4) = 0;
      uVar6 = puVar2[2] + 1;
      puVar2[2] = uVar6;
    }
    puVar2[4] = 7;
    local_28 = inflate_trees_bits(puVar2[3],puVar2 + 4,puVar2 + 5,puVar2[9],param_2);
    if (local_28 != 0) {
      (*(code *)param_2[9])(param_2[10],puVar2[3]);
      if (local_28 == 0xfffffffd) {
        *puVar2 = 9;
      }
      puVar2[8] = uVar9;
      puVar2[7] = uVar7;
      param_2[1] = local_30;
      param_2[2] = (int)(pbVar11 + (param_2[2] - *param_2));
      *param_2 = (int)pbVar11;
      puVar2[0xd] = (uint)param_1;
      puVar5 = (undefined *)inflate_flush(puVar2,param_2,local_28);
      return puVar5;
    }
    puVar2[2] = 0;
    *puVar2 = 5;
    local_28 = 0;
LAB_004c80d9:
    if (puVar2[2] < (puVar2[1] & 0x1f) + 0x102 + (puVar2[1] >> 5 & 0x1f)) {
      do {
        for (; uVar7 < puVar2[4]; uVar7 = uVar7 + 8) {
          if (local_30 == 0) goto LAB_004c8647;
          local_30 = local_30 - 1;
          param_3 = 0;
          uVar9 = uVar9 | (uint)*pbVar11 << ((byte)uVar7 & 0x1f);
          pbVar11 = pbVar11 + 1;
          local_2c = (uint)pbVar11;
        }
        bVar1 = *(byte *)(puVar2[5] + 1 + (*(uint *)(&DAT_004f32c8 + puVar2[4] * 4) & uVar9) * 8);
        local_28 = (uint)bVar1;
        local_c = *(uint *)(puVar2[5] + (*(uint *)(&DAT_004f32c8 + puVar2[4] * 4) & uVar9) * 8 + 4);
        if (local_c < 0x10) {
          uVar7 = uVar7 - local_28;
          uVar9 = uVar9 >> (bVar1 & 0x1f);
          *(uint *)(puVar2[3] + puVar2[2] * 4) = local_c;
          puVar2[2] = puVar2[2] + 1;
        }
        else {
          local_24 = 7;
          if (local_c != 0x12) {
            local_24 = local_c - 0xe;
          }
          local_10 = local_24 + local_28;
          pbVar12 = pbVar11;
          pbVar11 = (byte *)local_2c;
          for (; local_2c = (uint)pbVar11, uVar7 < local_10; uVar7 = uVar7 + 8) {
            if (local_30 == 0) goto LAB_004c8686;
            local_30 = local_30 - 1;
            param_3 = 0;
            uVar9 = uVar9 | (uint)*pbVar12 << ((byte)uVar7 & 0x1f);
            pbVar12 = pbVar12 + 1;
            pbVar11 = pbVar12;
          }
          uVar9 = uVar9 >> (bVar1 & 0x1f);
          iVar3 = (-(uint)(local_c != 0x12) & 0xfffffff8) + 0xb +
                  (*(uint *)(&DAT_004f32c8 + local_24 * 4) & uVar9);
          uVar9 = uVar9 >> ((byte)local_24 & 0x1f);
          uVar7 = uVar7 - (local_24 + local_28);
          local_24 = puVar2[2];
          if (((puVar2[1] & 0x1f) + 0x102 + (puVar2[1] >> 5 & 0x1f) < local_24 + iVar3) ||
             ((local_c == 0x10 && (local_24 == 0)))) {
            (*(code *)param_2[9])(param_2[10],puVar2[3]);
            *puVar2 = 9;
            param_2[6] = (int)s_invalid_bit_length_repeat_004f1fe0;
            puVar2[8] = uVar9;
            puVar2[7] = uVar7;
            param_2[1] = local_30;
            param_2[2] = (int)(pbVar12 + (param_2[2] - *param_2));
            *param_2 = (int)pbVar12;
            puVar2[0xd] = (uint)param_1;
            puVar5 = (undefined *)inflate_flush(puVar2,param_2,0xfffffffd);
            return puVar5;
          }
          uVar6 = local_24;
          if (local_c == 0x10) {
            uVar4 = *(undefined4 *)((puVar2[3] - 4) + local_24 * 4);
          }
          else {
            uVar4 = 0;
          }
          do {
            uVar6 = uVar6 + 1;
            iVar3 = iVar3 + -1;
            *(undefined4 *)((puVar2[3] - 4) + uVar6 * 4) = uVar4;
          } while (iVar3 != 0);
          puVar2[2] = uVar6;
        }
      } while (puVar2[2] < (puVar2[1] & 0x1f) + 0x102 + (puVar2[1] >> 5 & 0x1f));
    }
    puVar2[5] = 0;
    local_2c = 9;
    local_24 = 6;
    local_28 = inflate_trees_dynamic
                         ((puVar2[1] & 0x1f) + 0x101,(puVar2[1] >> 5 & 0x1f) + 1,puVar2[3],&local_2c
                          ,&local_24,&local_4,&local_8,puVar2[9],param_2);
    (*(code *)param_2[9])(param_2[10],puVar2[3]);
    if (local_28 != 0) {
      if (local_28 == 0xfffffffd) {
        *puVar2 = 9;
      }
      puVar2[8] = uVar9;
      puVar2[7] = uVar7;
      param_2[1] = local_30;
      param_2[2] = (int)(pbVar11 + (param_2[2] - *param_2));
      *param_2 = (int)pbVar11;
      puVar2[0xd] = (uint)param_1;
      puVar5 = (undefined *)inflate_flush(puVar2,param_2,local_28);
      return puVar5;
    }
    puVar5 = inflate_codes_new((char)local_2c,(char)local_24,local_4,local_8,(int)param_2);
    if (puVar5 == (undefined *)0x0) {
      puVar2[8] = uVar9;
      puVar2[7] = uVar7;
      param_2[1] = local_30;
      param_2[2] = (int)(pbVar11 + (param_2[2] - *param_2));
      *param_2 = (int)pbVar11;
      puVar2[0xd] = (uint)param_1;
      puVar5 = (undefined *)inflate_flush(puVar2,param_2,0xfffffffc);
      return puVar5;
    }
    puVar2[1] = (uint)puVar5;
    *puVar2 = 6;
LAB_004c8328:
    puVar2[8] = uVar9;
    puVar2[7] = uVar7;
    iVar3 = *param_2;
    param_2[1] = local_30;
    *param_2 = (int)pbVar11;
    param_2[2] = (int)(pbVar11 + (param_2[2] - iVar3));
    puVar2[0xd] = (uint)param_1;
    puVar5 = inflate_codes((uint)puVar2,(byte *)param_2,param_3);
    if (puVar5 != (undefined *)0x1) {
      puVar5 = (undefined *)inflate_flush(puVar2,param_2,puVar5);
      return puVar5;
    }
    param_3 = 0;
    inflate_codes_free(puVar2[1],param_2);
    local_30 = param_2[1];
    local_2c = *param_2;
    local_28 = puVar2[8];
    uVar7 = puVar2[7];
    param_1 = (uint *)puVar2[0xd];
    if (param_1 < (uint *)puVar2[0xc]) {
      local_24 = (int)puVar2[0xc] + (-1 - (int)param_1);
    }
    else {
      local_24 = puVar2[0xb] - (int)param_1;
    }
    if (puVar2[6] != 0) {
      *puVar2 = 7;
LAB_004c87d3:
      uVar9 = local_2c;
      puVar2[0xd] = (uint)param_1;
      uVar4 = inflate_flush(puVar2,param_2,param_3);
      param_1 = (uint *)puVar2[0xd];
      if ((uint *)puVar2[0xc] != param_1) {
        puVar2[7] = uVar7;
        puVar2[8] = local_28;
        param_2[1] = local_30;
        param_2[2] = param_2[2] + (uVar9 - *param_2);
        *param_2 = uVar9;
        puVar2[0xd] = (uint)param_1;
        puVar5 = (undefined *)inflate_flush(puVar2,param_2,uVar4);
        return puVar5;
      }
      *puVar2 = 8;
LAB_004c883a:
      puVar2[8] = local_28;
      puVar2[7] = uVar7;
      param_2[1] = local_30;
      param_2[2] = param_2[2] + (uVar9 - *param_2);
      *param_2 = uVar9;
      puVar2[0xd] = (uint)param_1;
      puVar5 = (undefined *)inflate_flush(puVar2,param_2,1);
      return puVar5;
    }
    *puVar2 = 0;
    goto switchD_004c7d01_default;
  case 5:
    goto LAB_004c80d9;
  case 6:
    goto LAB_004c8328;
  case 7:
    goto LAB_004c87d3;
  case 8:
    uVar9 = local_2c;
    goto LAB_004c883a;
  case 9:
    puVar2[8] = local_28;
    puVar2[7] = uVar7;
    iVar3 = *param_2;
    param_2[1] = local_30;
    *param_2 = local_2c;
    param_2[2] = param_2[2] + (local_2c - iVar3);
    puVar2[0xd] = (uint)param_1;
    puVar5 = (undefined *)inflate_flush(puVar2,param_2,0xfffffffd);
    return puVar5;
  default:
    puVar2[8] = local_28;
    puVar2[7] = uVar7;
    iVar3 = *param_2;
    param_2[1] = local_30;
    *param_2 = local_2c;
    param_2[2] = param_2[2] + (local_2c - iVar3);
    puVar2[0xd] = (uint)param_1;
    puVar5 = (undefined *)inflate_flush(puVar2,param_2,0xfffffffe);
    return puVar5;
  }
  *puVar2 = -(uint)(puVar2[6] != 0) & 7;
  goto switchD_004c7d01_default;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_28
#undef local_2c
#undef local_30
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x004c8940  inflate_blocks_free ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 inflate_blocks_free(int param_1,int param_2)

{
  inflate_blocks_reset(param_1,param_2,0);
  (**(code **)(param_2 + 0x24))(*(undefined4 *)(param_2 + 0x28),*(undefined4 *)(param_1 + 0x28));
  (**(code **)(param_2 + 0x24))(*(undefined4 *)(param_2 + 0x28),*(undefined4 *)(param_1 + 0x24));
  (**(code **)(param_2 + 0x24))(*(undefined4 *)(param_2 + 0x28),param_1);
  return 0;
}
#endif


/* ---- 0x004c8ac0  _tr_init ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* trees.c; the first call is the empty tr_static_init */

void _tr_init(int param_1)

{
  Lua_Stub();
  *(int *)(param_1 + 0xb10) = param_1 + 0x8c;
  *(int *)(param_1 + 0xb28) = param_1 + 0xa74;
  *(undefined ***)(param_1 + 0xb18) = &PTR_DAT_004f2058;
  *(int *)(param_1 + 0xb1c) = param_1 + 0x980;
  *(undefined ***)(param_1 + 0xb24) = &PTR_DAT_004f2070;
  *(undefined **)(param_1 + 0xb30) = &DAT_004f2088;
  *(undefined2 *)(param_1 + 0x16b0) = 0;
  *(undefined4 *)(param_1 + 0x16b4) = 0;
  *(undefined4 *)(param_1 + 0x16ac) = 8;
  init_block(param_1);
  return;
}
#endif


/* ---- 0x004c8b30  init_block ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void init_block(int param_1)

{
  undefined2 *puVar1;
  int iVar2;
  
  iVar2 = 0x11e;
  puVar1 = (undefined2 *)(param_1 + 0x8c);
  do {
    *puVar1 = 0;
    puVar1 = puVar1 + 2;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  puVar1 = (undefined2 *)(param_1 + 0x980);
  iVar2 = 0x1e;
  do {
    *puVar1 = 0;
    puVar1 = puVar1 + 2;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  puVar1 = (undefined2 *)(param_1 + 0xa74);
  iVar2 = 0x13;
  do {
    *puVar1 = 0;
    puVar1 = puVar1 + 2;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  *(undefined2 *)(param_1 + 0x48c) = 1;
  *(undefined4 *)(param_1 + 0x16a4) = 0;
  *(undefined4 *)(param_1 + 0x16a0) = 0;
  *(undefined4 *)(param_1 + 0x16a8) = 0;
  *(undefined4 *)(param_1 + 0x1698) = 0;
  return;
}
#endif


/* ---- 0x004c8c40  _tr_align ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void _tr_align(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x16b4);
  if (iVar1 < 0xe) {
    *(ushort *)(param_1 + 0x16b0) =
         *(ushort *)(param_1 + 0x16b0) | (ushort)(2 << ((byte)iVar1 & 0x1f));
    *(int *)(param_1 + 0x16b4) = iVar1 + 3;
  }
  else {
    *(ushort *)(param_1 + 0x16b0) =
         *(ushort *)(param_1 + 0x16b0) | (ushort)(2 << ((byte)iVar1 & 0x1f));
    *(undefined1 *)(*(int *)(param_1 + 0x14) + *(int *)(param_1 + 8)) =
         *(undefined1 *)(param_1 + 0x16b0);
    iVar1 = *(int *)(param_1 + 0x14) + 1;
    *(int *)(param_1 + 0x14) = iVar1;
    *(undefined1 *)(iVar1 + *(int *)(param_1 + 8)) = *(undefined1 *)(param_1 + 0x16b1);
    *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
    iVar1 = *(int *)(param_1 + 0x16b4);
    *(int *)(param_1 + 0x16b4) = iVar1 + -0xd;
    *(ushort *)(param_1 + 0x16b0) = 2 >> (0x10U - (char)iVar1 & 0x1f);
  }
  iVar1 = *(int *)(param_1 + 0x16b4);
  if (iVar1 < 10) {
    *(ushort *)(param_1 + 0x16b0) =
         *(ushort *)(param_1 + 0x16b0) | (ushort)(0x70000 << ((byte)iVar1 & 0x1f));
    iVar1 = iVar1 + 7;
  }
  else {
    *(ushort *)(param_1 + 0x16b0) =
         *(ushort *)(param_1 + 0x16b0) | (ushort)(0 << ((byte)iVar1 & 0x1f));
    *(undefined1 *)(*(int *)(param_1 + 0x14) + *(int *)(param_1 + 8)) =
         *(undefined1 *)(param_1 + 0x16b0);
    iVar1 = *(int *)(param_1 + 0x14) + 1;
    *(int *)(param_1 + 0x14) = iVar1;
    *(undefined1 *)(iVar1 + *(int *)(param_1 + 8)) = *(undefined1 *)(param_1 + 0x16b1);
    *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
    iVar1 = *(int *)(param_1 + 0x16b4) + -9;
    *(ushort *)(param_1 + 0x16b0) = 0 >> (0x10U - (char)*(int *)(param_1 + 0x16b4) & 0x1f);
  }
  *(int *)(param_1 + 0x16b4) = iVar1;
  bi_flush(param_1);
  iVar1 = *(int *)(param_1 + 0x16b4);
  if ((*(int *)(param_1 + 0x16ac) - iVar1) + 0xb < 9) {
    if (iVar1 < 0xe) {
      *(ushort *)(param_1 + 0x16b0) =
           *(ushort *)(param_1 + 0x16b0) | (ushort)(2 << ((byte)iVar1 & 0x1f));
      *(int *)(param_1 + 0x16b4) = iVar1 + 3;
    }
    else {
      *(ushort *)(param_1 + 0x16b0) =
           *(ushort *)(param_1 + 0x16b0) | (ushort)(2 << ((byte)iVar1 & 0x1f));
      *(undefined1 *)(*(int *)(param_1 + 0x14) + *(int *)(param_1 + 8)) =
           *(undefined1 *)(param_1 + 0x16b0);
      iVar1 = *(int *)(param_1 + 0x14) + 1;
      *(int *)(param_1 + 0x14) = iVar1;
      *(undefined1 *)(iVar1 + *(int *)(param_1 + 8)) = *(undefined1 *)(param_1 + 0x16b1);
      *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
      iVar1 = *(int *)(param_1 + 0x16b4);
      *(int *)(param_1 + 0x16b4) = iVar1 + -0xd;
      *(ushort *)(param_1 + 0x16b0) = 2 >> (0x10U - (char)iVar1 & 0x1f);
    }
    iVar1 = *(int *)(param_1 + 0x16b4);
    if (iVar1 < 10) {
      *(ushort *)(param_1 + 0x16b0) =
           *(ushort *)(param_1 + 0x16b0) | (ushort)(0x70000 << ((byte)iVar1 & 0x1f));
      iVar1 = iVar1 + 7;
    }
    else {
      *(ushort *)(param_1 + 0x16b0) =
           *(ushort *)(param_1 + 0x16b0) | (ushort)(0 << ((byte)iVar1 & 0x1f));
      *(undefined1 *)(*(int *)(param_1 + 0x14) + *(int *)(param_1 + 8)) =
           *(undefined1 *)(param_1 + 0x16b0);
      iVar1 = *(int *)(param_1 + 0x14) + 1;
      *(int *)(param_1 + 0x14) = iVar1;
      *(undefined1 *)(iVar1 + *(int *)(param_1 + 8)) = *(undefined1 *)(param_1 + 0x16b1);
      *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
      iVar1 = *(int *)(param_1 + 0x16b4) + -9;
      *(ushort *)(param_1 + 0x16b0) = 0 >> (0x10U - (char)*(int *)(param_1 + 0x16b4) & 0x1f);
    }
    *(int *)(param_1 + 0x16b4) = iVar1;
    bi_flush(param_1);
  }
  *(undefined4 *)(param_1 + 0x16ac) = 7;
  return;
}
#endif


/* ---- 0x004ca480  bi_flush ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void bi_flush(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x16b4) == 0x10) {
    *(undefined1 *)(*(int *)(param_1 + 0x14) + *(int *)(param_1 + 8)) =
         *(undefined1 *)(param_1 + 0x16b0);
    iVar1 = *(int *)(param_1 + 0x14) + 1;
    *(int *)(param_1 + 0x14) = iVar1;
    *(undefined1 *)(*(int *)(param_1 + 8) + iVar1) = *(undefined1 *)(param_1 + 0x16b1);
    *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
    *(undefined2 *)(param_1 + 0x16b0) = 0;
    *(undefined4 *)(param_1 + 0x16b4) = 0;
    return;
  }
  if (7 < *(int *)(param_1 + 0x16b4)) {
    *(undefined1 *)(*(int *)(param_1 + 8) + *(int *)(param_1 + 0x14)) =
         *(undefined1 *)(param_1 + 0x16b0);
    *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
    *(ushort *)(param_1 + 0x16b0) = (ushort)*(byte *)(param_1 + 0x16b1);
    *(int *)(param_1 + 0x16b4) = *(int *)(param_1 + 0x16b4) + -8;
  }
  return;
}
#endif


/* ---- 0x004ca510  bi_windup ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void bi_windup(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x16b4) < 9) {
    if (*(int *)(param_1 + 0x16b4) < 1) goto LAB_004ca55f;
    *(undefined1 *)(*(int *)(param_1 + 8) + *(int *)(param_1 + 0x14)) =
         *(undefined1 *)(param_1 + 0x16b0);
  }
  else {
    *(undefined1 *)(*(int *)(param_1 + 0x14) + *(int *)(param_1 + 8)) =
         *(undefined1 *)(param_1 + 0x16b0);
    iVar1 = *(int *)(param_1 + 0x14) + 1;
    *(int *)(param_1 + 0x14) = iVar1;
    *(undefined1 *)(*(int *)(param_1 + 8) + iVar1) = *(undefined1 *)(param_1 + 0x16b1);
  }
  *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
LAB_004ca55f:
  *(undefined2 *)(param_1 + 0x16b0) = 0;
  *(undefined4 *)(param_1 + 0x16b4) = 0;
  return;
}
#endif


/* ---- 0x004ca580  copy_block ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void copy_block(int param_1,undefined1 *param_2,int param_3,int param_4)

{
  byte bVar1;
  int iVar2;
  
  bi_windup(param_1);
  *(undefined4 *)(param_1 + 0x16ac) = 8;
  if (param_4 != 0) {
    *(byte *)(*(int *)(param_1 + 0x14) + *(int *)(param_1 + 8)) = (byte)param_3;
    iVar2 = *(int *)(param_1 + 0x14) + 1;
    *(int *)(param_1 + 0x14) = iVar2;
    bVar1 = (byte)((uint)param_3 >> 8);
    *(byte *)(*(int *)(param_1 + 8) + iVar2) = bVar1;
    iVar2 = *(int *)(param_1 + 0x14) + 1;
    *(int *)(param_1 + 0x14) = iVar2;
    *(byte *)(*(int *)(param_1 + 8) + iVar2) = ~(byte)param_3;
    iVar2 = *(int *)(param_1 + 0x14) + 1;
    *(int *)(param_1 + 0x14) = iVar2;
    *(byte *)(*(int *)(param_1 + 8) + iVar2) = ~bVar1;
    *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
  }
  for (; param_3 != 0; param_3 = param_3 + -1) {
    *(undefined1 *)(*(int *)(param_1 + 0x14) + *(int *)(param_1 + 8)) = *param_2;
    param_2 = param_2 + 1;
    *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
  }
  return;
}
#endif


/* ---- 0x004ca620  inflate_codes_new ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined * __cdecl
inflate_codes_new(undefined1 param_1,undefined1 param_2,uint param_3,uint param_4,int param_5)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)(**(code **)(param_5 + 0x20))(*(undefined4 *)(param_5 + 0x28),1,0x1c);
  if (puVar1 != (undefined4 *)0x0) {
    *(undefined1 *)(puVar1 + 4) = param_1;
    *(undefined1 *)((int)puVar1 + 0x11) = param_2;
    *puVar1 = 0;
    puVar1[5] = param_3;
    puVar1[6] = param_4;
  }
  return (undefined *)puVar1;
}
#endif


/* ---- 0x004ca660  inflate_codes ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined * __cdecl inflate_codes(uint param_1,byte *param_2,int param_3)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  byte *pbVar5;
  uint uVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined *puVar9;
  byte bVar10;
  undefined1 *puVar11;
  undefined1 *puVar12;
  uint uVar13;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  pbVar5 = param_2;
  uVar6 = param_1;
  local_14 = *(uint *)(param_2 + 4);
  piVar1 = *(int **)(param_1 + 4);
  puVar12 = *(undefined1 **)(param_1 + 0x34);
  uVar13 = *(uint *)(param_1 + 0x1c);
  if (puVar12 < *(undefined1 **)(param_1 + 0x30)) {
    local_10 = (uint)(*(undefined1 **)(param_1 + 0x30) + (-1 - (int)puVar12));
    param_1 = *(uint *)(param_1 + 0x20);
    param_2 = *(byte **)param_2;
  }
  else {
    local_10 = *(int *)(param_1 + 0x2c) - (int)puVar12;
    param_1 = *(uint *)(param_1 + 0x20);
    param_2 = *(byte **)param_2;
  }
  do {
    switch(*piVar1) {
    case 0:
      if ((0x101 < local_10) && (9 < local_14)) {
        *(uint *)(uVar6 + 0x20) = param_1;
        *(uint *)(uVar6 + 0x1c) = uVar13;
        iVar4 = *(int *)pbVar5;
        *(uint *)(pbVar5 + 4) = local_14;
        *(byte **)pbVar5 = param_2;
        *(byte **)(pbVar5 + 8) = param_2 + (*(int *)(pbVar5 + 8) - iVar4);
        *(undefined1 **)(uVar6 + 0x34) = puVar12;
        param_3 = inflate_fast((char)piVar1[4],*(undefined1 *)((int)piVar1 + 0x11),piVar1[5],
                               piVar1[6],uVar6,pbVar5);
        local_14 = *(uint *)(pbVar5 + 4);
        param_2 = *(byte **)pbVar5;
        uVar13 = *(uint *)(uVar6 + 0x1c);
        param_1 = *(uint *)(uVar6 + 0x20);
        puVar12 = *(undefined1 **)(uVar6 + 0x34);
        if (puVar12 < *(undefined1 **)(uVar6 + 0x30)) {
          local_10 = (uint)(*(undefined1 **)(uVar6 + 0x30) + (-1 - (int)puVar12));
        }
        else {
          local_10 = *(int *)(uVar6 + 0x2c) - (int)puVar12;
        }
        if (param_3 != 0) {
          *piVar1 = (-(uint)(param_3 != 1) & 2) + 7;
          break;
        }
      }
      piVar1[2] = piVar1[5];
      piVar1[3] = (uint)*(byte *)(piVar1 + 4);
      *piVar1 = 1;
    case 1:
      uVar7 = piVar1[3];
      if (uVar13 < uVar7) {
        do {
          if (local_14 == 0) {
            *(uint *)(uVar6 + 0x1c) = uVar13;
            *(uint *)(uVar6 + 0x20) = param_1;
            iVar4 = *(int *)pbVar5;
            iVar3 = *(int *)(pbVar5 + 8);
            pbVar5[4] = 0;
            pbVar5[5] = 0;
            pbVar5[6] = 0;
            pbVar5[7] = 0;
            *(byte **)pbVar5 = param_2;
            *(byte **)(pbVar5 + 8) = param_2 + (iVar3 - iVar4);
            *(undefined1 **)(uVar6 + 0x34) = puVar12;
            puVar9 = (undefined *)inflate_flush(uVar6,pbVar5,param_3);
            return puVar9;
          }
          local_14 = local_14 - 1;
          param_3 = 0;
          bVar10 = (byte)uVar13;
          uVar13 = uVar13 + 8;
          param_1 = param_1 | (uint)*param_2 << (bVar10 & 0x1f);
          uVar7 = piVar1[3];
          param_2 = param_2 + 1;
        } while (uVar13 < uVar7);
      }
      local_c = piVar1[2] + (*(uint *)(&DAT_004f32c8 + uVar7 * 4) & param_1) * 8;
      param_1 = param_1 >> (*(byte *)(local_c + 1) & 0x1f);
      uVar13 = uVar13 - *(byte *)(local_c + 1);
      bVar10 = *(byte *)local_c;
      uVar7 = (uint)bVar10;
      if (uVar7 == 0) {
        piVar1[2] = *(int *)(local_c + 4);
        *piVar1 = 6;
      }
      else if ((bVar10 & 0x10) == 0) {
        if ((bVar10 & 0x40) == 0) {
LAB_004ca979:
          piVar1[3] = uVar7;
          piVar1[2] = local_c + *(int *)(local_c + 4) * 8;
        }
        else {
          if ((bVar10 & 0x20) == 0) {
            *piVar1 = 9;
            *(char **)(pbVar5 + 0x18) = s_invalid_literal_length_code_004f20b4;
switchD_004ca6ad_caseD_9:
            *(uint *)(uVar6 + 0x20) = param_1;
            *(uint *)(uVar6 + 0x1c) = uVar13;
            iVar4 = *(int *)pbVar5;
            *(uint *)(pbVar5 + 4) = local_14;
            *(byte **)pbVar5 = param_2;
            *(byte **)(pbVar5 + 8) = param_2 + (*(int *)(pbVar5 + 8) - iVar4);
            *(undefined1 **)(uVar6 + 0x34) = puVar12;
            puVar9 = (undefined *)inflate_flush(uVar6,pbVar5,0xfffffffd);
            return puVar9;
          }
          *piVar1 = 7;
        }
      }
      else {
        piVar1[2] = bVar10 & 0xf;
        piVar1[1] = *(int *)(local_c + 4);
        *piVar1 = 2;
      }
      break;
    case 2:
      uVar7 = piVar1[2];
      if (uVar13 < uVar7) {
        do {
          if (local_14 == 0) goto LAB_004cac79;
          local_14 = local_14 - 1;
          bVar10 = (byte)uVar13;
          uVar13 = uVar13 + 8;
          param_3 = 0;
          param_1 = param_1 | (uint)*param_2 << (bVar10 & 0x1f);
          uVar7 = piVar1[2];
          param_2 = param_2 + 1;
        } while (uVar13 < uVar7);
      }
      piVar1[1] = piVar1[1] + (*(uint *)(&DAT_004f32c8 + uVar7 * 4) & param_1);
      param_1 = param_1 >> ((byte)piVar1[2] & 0x1f);
      *piVar1 = 3;
      uVar13 = uVar13 - piVar1[2];
      piVar1[2] = piVar1[6];
      piVar1[3] = (uint)*(byte *)((int)piVar1 + 0x11);
    case 3:
      uVar7 = piVar1[3];
      if (uVar13 < uVar7) {
        do {
          if (local_14 == 0) {
LAB_004cac79:
            *(uint *)(uVar6 + 0x1c) = uVar13;
            *(uint *)(uVar6 + 0x20) = param_1;
            iVar4 = *(int *)pbVar5;
            iVar3 = *(int *)(pbVar5 + 8);
            pbVar5[4] = 0;
            pbVar5[5] = 0;
            pbVar5[6] = 0;
            pbVar5[7] = 0;
            *(byte **)pbVar5 = param_2;
            *(byte **)(pbVar5 + 8) = param_2 + (iVar3 - iVar4);
            *(undefined1 **)(uVar6 + 0x34) = puVar12;
            puVar9 = (undefined *)inflate_flush(uVar6,pbVar5,param_3);
            return puVar9;
          }
          local_14 = local_14 - 1;
          param_3 = 0;
          bVar10 = (byte)uVar13;
          uVar13 = uVar13 + 8;
          param_1 = param_1 | (uint)*param_2 << (bVar10 & 0x1f);
          uVar7 = piVar1[3];
          param_2 = param_2 + 1;
        } while (uVar13 < uVar7);
      }
      local_c = piVar1[2] + (*(uint *)(&DAT_004f32c8 + uVar7 * 4) & param_1) * 8;
      param_1 = param_1 >> (*(byte *)(local_c + 1) & 0x1f);
      uVar13 = uVar13 - *(byte *)(local_c + 1);
      bVar10 = *(byte *)local_c;
      uVar7 = (uint)bVar10;
      if ((bVar10 & 0x10) == 0) {
        if ((bVar10 & 0x40) != 0) {
          *piVar1 = 9;
          *(char **)(pbVar5 + 0x18) = s_invalid_distance_code_004f209c;
          goto switchD_004ca6ad_caseD_9;
        }
        goto LAB_004ca979;
      }
      piVar1[2] = bVar10 & 0xf;
      piVar1[3] = *(int *)(local_c + 4);
      *piVar1 = 4;
      break;
    case 4:
      uVar7 = piVar1[2];
      if (uVar13 < uVar7) {
        do {
          if (local_14 == 0) goto LAB_004cac79;
          local_14 = local_14 - 1;
          bVar10 = (byte)uVar13;
          uVar13 = uVar13 + 8;
          param_3 = 0;
          param_1 = param_1 | (uint)*param_2 << (bVar10 & 0x1f);
          uVar7 = piVar1[2];
          param_2 = param_2 + 1;
        } while (uVar13 < uVar7);
      }
      piVar1[3] = piVar1[3] + (*(uint *)(&DAT_004f32c8 + uVar7 * 4) & param_1);
      param_1 = param_1 >> ((byte)piVar1[2] & 0x1f);
      *piVar1 = 5;
      uVar13 = uVar13 - piVar1[2];
    case 5:
      if ((uint)((int)puVar12 - *(int *)(uVar6 + 0x28)) < (uint)piVar1[3]) {
        iVar4 = (*(int *)(uVar6 + 0x2c) - *(int *)(uVar6 + 0x28)) - piVar1[3];
      }
      else {
        iVar4 = -piVar1[3];
      }
      local_8 = (int)puVar12 + iVar4;
      if (piVar1[1] == 0) {
LAB_004cabd4:
        *piVar1 = 0;
      }
      else {
        do {
          if (local_10 == 0) {
            if (puVar12 == *(undefined1 **)(uVar6 + 0x2c)) {
              puVar11 = *(undefined1 **)(uVar6 + 0x30);
              puVar2 = *(undefined1 **)(uVar6 + 0x28);
              if (puVar11 != puVar2) {
                puVar12 = puVar2;
                if (puVar2 < puVar11) {
                  local_10 = (uint)(puVar11 + (-1 - (int)puVar2));
                }
                else {
                  local_10 = (uint)(*(undefined1 **)(uVar6 + 0x2c) + -(int)puVar2);
                }
              }
            }
            if ((undefined1 *)local_10 == (undefined1 *)0x0) {
              *(undefined1 **)(uVar6 + 0x34) = puVar12;
              param_3 = inflate_flush(uVar6,pbVar5,param_3);
              puVar12 = *(undefined1 **)(uVar6 + 0x34);
              puVar11 = *(undefined1 **)(uVar6 + 0x30);
              if (puVar12 < puVar11) {
                local_10 = (uint)(puVar11 + (-1 - (int)puVar12));
              }
              else {
                local_10 = *(int *)(uVar6 + 0x2c) - (int)puVar12;
              }
              if ((puVar12 == *(undefined1 **)(uVar6 + 0x2c)) &&
                 (puVar2 = *(undefined1 **)(uVar6 + 0x28), puVar11 != puVar2)) {
                puVar12 = puVar2;
                if (puVar2 < puVar11) {
                  local_10 = (uint)(puVar11 + (-1 - (int)puVar2));
                }
                else {
                  local_10 = (uint)(*(undefined1 **)(uVar6 + 0x2c) + -(int)puVar2);
                }
              }
              if ((undefined1 *)local_10 == (undefined1 *)0x0) goto LAB_004cacb8;
            }
          }
          puVar11 = puVar12 + 1;
          param_3 = 0;
          *puVar12 = *(undefined1 *)local_8;
          local_8 = local_8 + 1;
          local_10 = local_10 + -1;
          if (local_8 == *(uint *)(uVar6 + 0x2c)) {
            local_8 = *(uint *)(uVar6 + 0x28);
          }
          iVar4 = piVar1[1];
          piVar1[1] = iVar4 + -1;
          puVar12 = puVar11;
        } while (iVar4 + -1 != 0);
        *piVar1 = 0;
      }
      break;
    case 6:
      if (local_10 == 0) {
        if (puVar12 == *(undefined1 **)(uVar6 + 0x2c)) {
          puVar11 = *(undefined1 **)(uVar6 + 0x30);
          puVar2 = *(undefined1 **)(uVar6 + 0x28);
          if (puVar11 != puVar2) {
            puVar12 = puVar2;
            if (puVar2 < puVar11) {
              local_10 = (uint)(puVar11 + (-1 - (int)puVar2));
            }
            else {
              local_10 = (uint)(*(undefined1 **)(uVar6 + 0x2c) + -(int)puVar2);
            }
          }
        }
        if ((undefined1 *)local_10 == (undefined1 *)0x0) {
          *(undefined1 **)(uVar6 + 0x34) = puVar12;
          param_3 = inflate_flush(uVar6,pbVar5,param_3);
          puVar12 = *(undefined1 **)(uVar6 + 0x34);
          puVar11 = *(undefined1 **)(uVar6 + 0x30);
          if (puVar12 < puVar11) {
            local_10 = (uint)(puVar11 + (-1 - (int)puVar12));
          }
          else {
            local_10 = *(int *)(uVar6 + 0x2c) - (int)puVar12;
          }
          if ((puVar12 == *(undefined1 **)(uVar6 + 0x2c)) &&
             (puVar2 = *(undefined1 **)(uVar6 + 0x28), puVar11 != puVar2)) {
            puVar12 = puVar2;
            if (puVar2 < puVar11) {
              local_10 = (uint)(puVar11 + (-1 - (int)puVar2));
            }
            else {
              local_10 = (uint)(*(undefined1 **)(uVar6 + 0x2c) + -(int)puVar2);
            }
          }
          if ((undefined1 *)local_10 == (undefined1 *)0x0) {
LAB_004cacb8:
            *(uint *)(uVar6 + 0x20) = param_1;
            *(uint *)(uVar6 + 0x1c) = uVar13;
            iVar4 = *(int *)pbVar5;
            *(uint *)(pbVar5 + 4) = local_14;
            *(byte **)pbVar5 = param_2;
            *(byte **)(pbVar5 + 8) = param_2 + (*(int *)(pbVar5 + 8) - iVar4);
            *(undefined1 **)(uVar6 + 0x34) = puVar12;
            puVar9 = (undefined *)inflate_flush(uVar6,pbVar5,param_3);
            return puVar9;
          }
        }
      }
      param_3 = 0;
      *puVar12 = (char)piVar1[2];
      puVar12 = puVar12 + 1;
      local_10 = local_10 + -1;
      goto LAB_004cabd4;
    case 7:
      if (7 < uVar13) {
        uVar13 = uVar13 - 8;
        local_14 = local_14 + 1;
        param_2 = param_2 + -1;
      }
      *(undefined1 **)(uVar6 + 0x34) = puVar12;
      uVar8 = inflate_flush(uVar6,pbVar5,param_3);
      puVar12 = *(undefined1 **)(uVar6 + 0x34);
      if (*(undefined1 **)(uVar6 + 0x30) != puVar12) {
        *(uint *)(uVar6 + 0x1c) = uVar13;
        *(uint *)(uVar6 + 0x20) = param_1;
        iVar4 = *(int *)pbVar5;
        *(uint *)(pbVar5 + 4) = local_14;
        *(byte **)pbVar5 = param_2;
        *(byte **)(pbVar5 + 8) = param_2 + (*(int *)(pbVar5 + 8) - iVar4);
        *(undefined1 **)(uVar6 + 0x34) = puVar12;
        puVar9 = (undefined *)inflate_flush(uVar6,pbVar5,uVar8);
        return puVar9;
      }
      *piVar1 = 8;
    case 8:
      goto switchD_004ca6ad_caseD_8;
    case 9:
      goto switchD_004ca6ad_caseD_9;
    default:
      *(uint *)(uVar6 + 0x20) = param_1;
      *(uint *)(uVar6 + 0x1c) = uVar13;
      iVar4 = *(int *)pbVar5;
      *(uint *)(pbVar5 + 4) = local_14;
      *(byte **)pbVar5 = param_2;
      *(byte **)(pbVar5 + 8) = param_2 + (*(int *)(pbVar5 + 8) - iVar4);
      *(undefined1 **)(uVar6 + 0x34) = puVar12;
      puVar9 = (undefined *)inflate_flush(uVar6,pbVar5,0xfffffffe);
      return puVar9;
    }
  } while( true );
switchD_004ca6ad_caseD_8:
  *(uint *)(uVar6 + 0x20) = param_1;
  *(uint *)(uVar6 + 0x1c) = uVar13;
  iVar4 = *(int *)pbVar5;
  *(uint *)(pbVar5 + 4) = local_14;
  *(byte **)pbVar5 = param_2;
  *(byte **)(pbVar5 + 8) = param_2 + (*(int *)(pbVar5 + 8) - iVar4);
  *(undefined1 **)(uVar6 + 0x34) = puVar12;
  puVar9 = (undefined *)inflate_flush(uVar6,pbVar5,1);
  return puVar9;
}
#undef local_10
#undef local_14
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x004cae10  inflate_codes_free ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void inflate_codes_free(undefined4 param_1,int param_2)

{
  (**(code **)(param_2 + 0x24))(*(undefined4 *)(param_2 + 0x28),param_1);
  return;
}
#endif


/* ---- 0x004cae30  inflate_trees_bits ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int inflate_trees_bits(undefined4 param_1,int *param_2,undefined4 param_3,undefined4 param_4,
                      int param_5)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0;
  iVar1 = (**(code **)(param_5 + 0x20))(*(undefined4 *)(param_5 + 0x28),0x13,4);
  if (iVar1 == 0) {
    return -4;
  }
  iVar2 = huft_build(param_1,0x13,0x13,0,0,param_3,param_2,param_4,&local_4,iVar1);
  if (iVar2 == -3) {
    *(char **)(param_5 + 0x18) = s_oversubscribed_dynamic_bit_lengt_004f31fc;
    (**(code **)(param_5 + 0x24))(*(undefined4 *)(param_5 + 0x28),iVar1);
    return -3;
  }
  if ((iVar2 == -5) || (*param_2 == 0)) {
    *(char **)(param_5 + 0x18) = s_incomplete_dynamic_bit_lengths_t_004f31d8;
    iVar2 = -3;
  }
  (**(code **)(param_5 + 0x24))(*(undefined4 *)(param_5 + 0x28),iVar1);
  return iVar2;
}
#undef local_4

#endif


/* ---- 0x004caee0  huft_build ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4
huft_build(int *param_1,uint param_2,uint param_3,int param_4,int param_5,uint *param_6,
          uint *param_7,int param_8,uint *param_9,uint param_10)

{
  unsigned char _frame[0x100] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  char cVar2;
  undefined2 uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint *puVar8;
  int *piVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  int iVar14;
  uint uVar15;
  byte bVar16;
  int iVar17;
  #define local_f0 (*(uint *)(_frame + (0x100 - 0xf0)))
  #define local_ec (*(uint *)(_frame + (0x100 - 0xec)))
  #define local_e8 (*(uint *)(_frame + (0x100 - 0xe8)))
  #define local_e4 (*(uint *)(_frame + (0x100 - 0xe4)))
  #define local_e0 (*(uint *)(_frame + (0x100 - 0xe0)))
  #define local_dc (*(uint *)(_frame + (0x100 - 0xdc)))
  #define local_d8 (*(uint *)(_frame + (0x100 - 0xd8)))
  #define local_d4 (*(uint *)(_frame + (0x100 - 0xd4)))
  #define local_d0 (*(uint *)(_frame + (0x100 - 0xd0)))
  #define local_cc (*(uint *)(_frame + (0x100 - 0xcc)))
  #define local_c8 (*(uint *)(_frame + (0x100 - 0xc8)))
  #define local_c4 (*(uint *)(_frame + (0x100 - 0xc4)))
  #define local_c0 (*(uint *)(_frame + (0x100 - 0xc0)))
  #define local_bc (*(uint *)(_frame + (0x100 - 0xbc)))
  #define local_b8 (*(uint *)(_frame + (0x100 - 0xb8)))
  #define local_b4 (*(uint *)(_frame + (0x100 - 0xb4)))
  #define local_b0 (*(uint *)(_frame + (0x100 - 0xb0)))
  #define local_ac (*(uint *)(_frame + (0x100 - 0xac)))
  #define local_a8 (*(uint *)(_frame + (0x100 - 0xa8)))
  #define local_a4 (*(uint *)(_frame + (0x100 - 0xa4)))
  #define local_a0 (*(uint *)(_frame + (0x100 - 0xa0)))
  #define local_9c (*(uint *)(_frame + (0x100 - 0x9c)))
  #define local_98 (*(uint *)(_frame + (0x100 - 0x98)))
  #define local_94 (*(uint *)(_frame + (0x100 - 0x94)))
  #define local_90 (*(uint *)(_frame + (0x100 - 0x90)))
  #define local_8c (*(uint *)(_frame + (0x100 - 0x8c)))
  #define local_88 (*(uint *)(_frame + (0x100 - 0x88)))
  #define local_84 (*(uint *)(_frame + (0x100 - 0x84)))
  #define local_80 (*(uint *)(_frame + (0x100 - 0x80)))
  #define local_7c (*(uint *)(_frame + (0x100 - 0x7c)))
  #define local_78 (*(uint *)(_frame + (0x100 - 0x78)))
  #define aiStack_74 (*(int (*)[13])(_frame + (0x100 - 0x74)))
  #define iStack_40 (*(int *)(_frame + (0x100 - 0x40)))
  #define local_3c (*(uint *)(_frame + (0x100 - 0x3c)))
  
  local_bc = 0;
  local_b8 = 0;
  local_b4 = 0;
  local_b0 = 0;
  local_ac = 0;
  local_a8 = 0;
  local_a4 = 0;
  local_a0 = 0;
  local_9c = 0;
  local_98 = 0;
  local_94 = 0;
  local_90 = 0;
  local_8c = 0;
  local_88 = 0;
  local_84 = 0;
  local_80 = 0;
  piVar9 = param_1;
  uVar13 = param_2;
  do {
    iVar17 = *piVar9;
    piVar9 = piVar9 + 1;
    uVar13 = uVar13 - 1;
    (&local_bc)[iVar17] = (&local_bc)[iVar17] + 1;
  } while (uVar13 != 0);
  if (local_bc == param_2) {
    *param_6 = 0;
    *param_7 = 0;
    return 0;
  }
  local_ec = 1;
  puVar8 = &local_b8;
  do {
    if (*puVar8 != 0) break;
    local_ec = local_ec + 1;
    puVar8 = puVar8 + 1;
  } while (local_ec < 0x10);
  local_f0 = *param_7;
  if (*param_7 < local_ec) {
    local_f0 = local_ec;
  }
  uVar13 = 0xf;
  puVar8 = &local_80;
  do {
    if (*puVar8 != 0) break;
    uVar13 = uVar13 - 1;
    puVar8 = puVar8 + -1;
  } while (uVar13 != 0);
  if (uVar13 < local_f0) {
    local_f0 = uVar13;
  }
  *param_7 = local_f0;
  iVar17 = 1 << ((byte)local_ec & 0x1f);
  if (local_ec < uVar13) {
    puVar8 = &local_bc + local_ec;
    uVar10 = local_ec;
    do {
      uVar15 = *puVar8;
      if ((int)(iVar17 - uVar15) < 0) {
        return 0xfffffffd;
      }
      uVar10 = uVar10 + 1;
      puVar8 = puVar8 + 1;
      iVar17 = (iVar17 - uVar15) * 2;
    } while (uVar10 < uVar13);
  }
  iVar17 = iVar17 - (&local_bc)[uVar13];
  if (iVar17 < 0) {
    return 0xfffffffd;
  }
  local_78 = 0;
  (&local_bc)[uVar13] = (&local_bc)[uVar13] + iVar17;
  iVar11 = 0;
  iVar14 = uVar13 - 1;
  if (iVar14 != 0) {
    iVar5 = 0;
    do {
      iVar11 = iVar11 + *(int *)((int)&local_b8 + iVar5);
      iVar14 = iVar14 + -1;
      *(int *)((int)aiStack_74 + iVar5) = iVar11;
      iVar5 = iVar5 + 4;
    } while (iVar14 != 0);
  }
  uVar10 = 0;
  do {
    iVar11 = *param_1;
    param_1 = param_1 + 1;
    if (iVar11 != 0) {
      uVar15 = (&local_7c)[iVar11];
      *(uint *)(param_10 + uVar15 * 4) = uVar10;
      (&local_7c)[iVar11] = uVar15 + 1;
    }
    uVar15 = 0;
    uVar10 = uVar10 + 1;
  } while (uVar10 < param_2);
  iVar11 = -local_f0;
  uVar10 = (&local_7c)[uVar13];
  local_dc = 0;
  local_7c = 0;
  local_e4 = param_10;
  local_e8 = 0xffffffff;
  local_3c = 0;
  local_c4 = 0;
  if ((int)local_ec <= (int)uVar13) {
    local_d8 = (uint)(&local_bc + local_ec);
    do {
      uVar7 = *(uint *)local_d8;
      uVar12 = local_d0;
      while (local_d0 = uVar12, uVar7 != 0) {
        local_e0 = uVar7 - 1;
        PIECE(local_d0,2,2) = (undefined2)(uVar12 >> 0x10);
        uVar3 = PIECE(local_d0,2,2);
        iVar14 = iVar11;
        while (iVar14 = iVar14 + local_f0, iVar14 < (int)local_ec) {
          iVar11 = iVar11 + local_f0;
          local_e8 = local_e8 + 1;
          uVar15 = uVar13 - iVar11;
          if (local_f0 < uVar13 - iVar11) {
            uVar15 = local_f0;
          }
          uVar12 = local_ec - iVar11;
          uVar4 = 1 << ((byte)uVar12 & 0x1f);
          if ((uVar7 < uVar4) &&
             (iVar5 = uVar4 + (-1 - local_e0), uVar4 = local_d8, uVar12 < uVar15)) {
            while (uVar12 = uVar12 + 1, uVar12 < uVar15) {
              uVar1 = *(uint *)(uVar4 + 4);
              uVar6 = iVar5 * 2;
              if (uVar6 < uVar1 || uVar6 - uVar1 == 0) break;
              iVar5 = uVar6 - uVar1;
              uVar4 = uVar4 + 4;
            }
          }
          local_c4 = 1 << ((byte)uVar12 & 0x1f);
          uVar4 = local_c4 + *param_9;
          if (0x5a0 < uVar4) {
            return 0xfffffffc;
          }
          uVar15 = param_8 + *param_9 * 8;
          *param_9 = uVar4;
          (&local_3c)[local_e8] = uVar15;
          if (local_e8 == 0) {
            *param_6 = uVar15;
          }
          else {
            (&local_7c)[local_e8] = local_dc;
            PIECE(local_d0,2,2) = (undefined2)(local_d0 >> 0x10);
            PIECE(local_d0,0,2) = CONCAT11((char)local_f0,(byte)uVar12);
            uVar12 = local_dc >> ((char)iVar11 - (char)local_f0 & 0x1fU);
            iVar5 = (&iStack_40)[local_e8];
            local_cc = ((int)(uVar15 - iVar5) >> 3) - uVar12;
            *(uint *)(iVar5 + uVar12 * 8) = local_d0;
            *(uint *)(iVar5 + 4 + uVar12 * 8) = local_cc;
          }
          uVar3 = PIECE(local_d0,2,2);
        }
        cVar2 = (char)local_ec;
        bVar16 = (byte)iVar11;
        if (local_e4 < (uint *)(param_10 + uVar10 * 4)) {
          local_cc = *(uint *)local_e4;
          if (local_cc < param_3) {
            PIECE(local_d0,0,1) = (-(local_cc < 0x100) & 0xa0U) + 0x60;
          }
          else {
            iVar14 = (local_cc - param_3) * 4;
            PIECE(local_d0,0,1) = *(char *)(param_5 + iVar14) + 'P';
            local_cc = *(uint *)(param_4 + iVar14);
          }
          local_e4 = local_e4 + 4;
        }
        else {
          PIECE(local_d0,0,1) = -0x40;
        }
        local_d0 = CONCAT31(CONCAT21(uVar3,cVar2 - bVar16),(char)local_d0);
        iVar14 = 1 << (cVar2 - bVar16 & 0x1f);
        uVar7 = local_dc >> (bVar16 & 0x1f);
        if (uVar7 < local_c4) {
          puVar8 = (uint *)(uVar15 + uVar7 * 8);
          do {
            uVar7 = uVar7 + iVar14;
            *puVar8 = local_d0;
            puVar8[1] = local_cc;
            puVar8 = puVar8 + iVar14 * 2;
          } while (uVar7 < local_c4);
        }
        uVar12 = 1 << (cVar2 - 1U & 0x1f);
        uVar7 = local_dc & uVar12;
        while (uVar7 != 0) {
          local_dc = local_dc ^ uVar12;
          uVar12 = uVar12 >> 1;
          uVar7 = local_dc & uVar12;
        }
        local_dc = local_dc ^ uVar12;
        puVar8 = &local_7c + local_e8;
        uVar7 = local_e0;
        uVar12 = local_d0;
        if (((1 << (bVar16 & 0x1f)) - 1U & local_dc) != (&local_7c)[local_e8]) {
          do {
            puVar8 = puVar8 + -1;
            local_e8 = local_e8 - 1;
            iVar11 = iVar11 - local_f0;
          } while (((1 << ((byte)iVar11 & 0x1f)) - 1U & local_dc) != *puVar8);
        }
      }
      local_ec = local_ec + 1;
      local_d8 = local_d8 + 4;
    } while ((int)local_ec <= (int)uVar13);
  }
  if ((iVar17 != 0) && (uVar13 != 1)) {
    return 0xfffffffb;
  }
  return 0;
}
#undef aiStack_74
#undef iStack_40
#undef local_3c
#undef local_78
#undef local_7c
#undef local_80
#undef local_84
#undef local_88
#undef local_8c
#undef local_90
#undef local_94
#undef local_98
#undef local_9c
#undef local_a0
#undef local_a4
#undef local_a8
#undef local_ac
#undef local_b0
#undef local_b4
#undef local_b8
#undef local_bc
#undef local_c0
#undef local_c4
#undef local_c8
#undef local_cc
#undef local_d0
#undef local_d4
#undef local_d8
#undef local_dc
#undef local_e0
#undef local_e4
#undef local_e8
#undef local_ec
#undef local_f0

#endif


/* ---- 0x004cb390  inflate_trees_dynamic ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int inflate_trees_dynamic
              (uint param_1,undefined4 param_2,int param_3,int *param_4,int *param_5,
              undefined4 param_6,undefined4 param_7,undefined4 param_8,int param_9)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0;
  iVar1 = (**(code **)(param_9 + 0x20))(*(undefined4 *)(param_9 + 0x28),0x120,4);
  if (iVar1 == 0) {
    return -4;
  }
  iVar2 = huft_build(param_3,param_1,0x101,&DAT_004da768,&DAT_004da7e8,param_6,param_4,param_8,
                     &local_4,iVar1);
  if ((iVar2 != 0) || (*param_4 == 0)) {
    if (iVar2 == -3) {
      *(char **)(param_9 + 0x18) = s_oversubscribed_literal_length_tr_004f3244;
      (**(code **)(param_9 + 0x24))(*(undefined4 *)(param_9 + 0x28),iVar1);
      return -3;
    }
    if (iVar2 != -4) {
      *(char **)(param_9 + 0x18) = s_incomplete_literal_length_tree_004f3224;
      iVar2 = -3;
    }
    (**(code **)(param_9 + 0x24))(*(undefined4 *)(param_9 + 0x28),iVar1);
    return iVar2;
  }
  iVar2 = huft_build(param_3 + param_1 * 4,param_2,0,&DAT_004da868,&DAT_004da8e0,param_7,param_5,
                     param_8,&local_4,iVar1);
  if ((iVar2 == 0) && ((*param_5 != 0 || (param_1 < 0x102)))) {
    (**(code **)(param_9 + 0x24))(*(undefined4 *)(param_9 + 0x28),iVar1);
    return 0;
  }
  if (iVar2 == -3) {
    *(char **)(param_9 + 0x18) = s_oversubscribed_distance_tree_004f32a8;
    (**(code **)(param_9 + 0x24))(*(undefined4 *)(param_9 + 0x28),iVar1);
    return -3;
  }
  if (iVar2 == -5) {
    *(char **)(param_9 + 0x18) = s_incomplete_distance_tree_004f328c;
    (**(code **)(param_9 + 0x24))(*(undefined4 *)(param_9 + 0x28),iVar1);
    return -3;
  }
  if (iVar2 != -4) {
    *(char **)(param_9 + 0x18) = s_empty_distance_tree_with_lengths_004f3268;
    iVar2 = -3;
  }
  (**(code **)(param_9 + 0x24))(*(undefined4 *)(param_9 + 0x28),iVar1);
  return iVar2;
}
#undef local_4

#endif


/* ---- 0x004cb520  inflate_trees_fixed ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 inflate_trees_fixed(uint *param_1,uint *param_2,undefined4 *param_3,undefined4 *param_4)

{
  *param_1 = UINT_004f20d0;
  *param_2 = UINT_004f20d4;
  *param_3 = &DAT_004f20d8;
  *param_4 = &DAT_004f30d8;
  return 0;
}
#endif


/* ---- 0x004cb550  inflate_flush ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int inflate_flush(int param_1,int param_2,int param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined1 *puVar2;
  uint uVar3;
  undefined4 *puVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  puVar4 = *(undefined4 **)(param_1 + 0x34);
  puVar6 = *(undefined4 **)(param_1 + 0x30);
  puVar8 = *(undefined4 **)(param_2 + 0xc);
  if (puVar4 < puVar6) {
    puVar4 = *(undefined4 **)(param_1 + 0x2c);
  }
  uVar3 = *(uint *)(param_2 + 0x10);
  uVar5 = (int)puVar4 - (int)puVar6;
  if (uVar3 < (uint)((int)puVar4 - (int)puVar6)) {
    uVar5 = uVar3;
  }
  if ((uVar5 != 0) && (param_3 == -5)) {
    param_3 = 0;
  }
  *(uint *)(param_2 + 0x10) = uVar3 - uVar5;
  *(uint *)(param_2 + 0x14) = *(int *)(param_2 + 0x14) + uVar5;
  if (*(code **)(param_1 + 0x38) != (code *)0x0) {
    uVar1 = (**(code **)(param_1 + 0x38))(*(undefined4 *)(param_1 + 0x3c),puVar6,uVar5);
    *(undefined4 *)(param_1 + 0x3c) = uVar1;
    *(undefined4 *)(param_2 + 0x30) = uVar1;
  }
  puVar4 = puVar6;
  puVar7 = puVar8;
  for (uVar3 = uVar5 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *puVar7 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar7 = puVar7 + 1;
  }
  puVar2 = (undefined1 *)((int)puVar6 + uVar5);
  for (uVar3 = uVar5 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined1 *)puVar7 = *(undefined1 *)puVar4;
    puVar4 = (undefined4 *)((int)puVar4 + 1);
    puVar7 = (undefined4 *)((int)puVar7 + 1);
  }
  local_4 = (int)puVar8 + uVar5;
  if (puVar2 == *(undefined1 **)(param_1 + 0x2c)) {
    puVar4 = *(undefined4 **)(param_1 + 0x28);
    if (*(undefined1 **)(param_1 + 0x34) == *(undefined1 **)(param_1 + 0x2c)) {
      *(undefined4 **)(param_1 + 0x34) = puVar4;
    }
    uVar5 = *(int *)(param_1 + 0x34) - (int)puVar4;
    uVar3 = *(uint *)(param_2 + 0x10);
    if (uVar3 < uVar5) {
      uVar5 = uVar3;
    }
    if ((uVar5 != 0) && (param_3 == -5)) {
      param_3 = 0;
    }
    *(uint *)(param_2 + 0x10) = uVar3 - uVar5;
    *(uint *)(param_2 + 0x14) = *(int *)(param_2 + 0x14) + uVar5;
    if (*(code **)(param_1 + 0x38) != (code *)0x0) {
      uVar1 = (**(code **)(param_1 + 0x38))(*(undefined4 *)(param_1 + 0x3c),puVar4,uVar5);
      *(undefined4 *)(param_1 + 0x3c) = uVar1;
      *(undefined4 *)(param_2 + 0x30) = uVar1;
    }
    puVar6 = puVar4;
    puVar8 = (undefined4 *)local_4;
    for (uVar3 = uVar5 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *puVar8 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar8 = puVar8 + 1;
    }
    local_4 = local_4 + uVar5;
    puVar2 = (undefined1 *)((int)puVar4 + uVar5);
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined1 *)puVar8 = *(undefined1 *)puVar6;
      puVar6 = (undefined4 *)((int)puVar6 + 1);
      puVar8 = (undefined4 *)((int)puVar8 + 1);
    }
  }
  *(uint *)(param_2 + 0xc) = local_4;
  *(undefined1 **)(param_1 + 0x30) = puVar2;
  return param_3;
}
#undef local_4

#endif


/* ---- 0x004cb690  inflate_fast ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 inflate_fast(int param_1,uint param_2,int param_3,int param_4,int param_5,int *param_6)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  byte *pbVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  undefined1 *puVar11;
  undefined1 *puVar12;
  undefined1 *puVar13;
  int iVar14;
  byte *pbVar15;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  puVar11 = *(undefined1 **)(param_5 + 0x34);
  uVar8 = *(uint *)(param_5 + 0x20);
  pbVar15 = (byte *)*param_6;
  local_14 = param_6[1];
  uVar3 = *(uint *)(param_5 + 0x1c);
  if (puVar11 < *(undefined1 **)(param_5 + 0x30)) {
    local_10 = (uint)(*(undefined1 **)(param_5 + 0x30) + (-1 - (int)puVar11));
  }
  else {
    local_10 = *(int *)(param_5 + 0x2c) - (int)puVar11;
  }
  uVar7 = *(uint *)(&DAT_004f32c8 + param_1 * 4);
  uVar2 = *(uint *)(&DAT_004f32c8 + param_2 * 4);
  local_c = (uint)pbVar15;
  do {
    for (; uVar3 < 0x14; uVar3 = uVar3 + 8) {
      local_14 = local_14 - 1;
      uVar8 = uVar8 | (uint)*pbVar15 << ((byte)uVar3 & 0x1f);
      pbVar15 = pbVar15 + 1;
      local_c = (uint)pbVar15;
    }
    bVar1 = *(byte *)(param_3 + (uVar7 & uVar8) * 8);
    uVar10 = (uint)bVar1;
    iVar14 = param_3 + (uVar7 & uVar8) * 8;
    if (uVar10 == 0) {
LAB_004cb8bb:
      uVar8 = uVar8 >> (*(byte *)(iVar14 + 1) & 0x1f);
      uVar3 = uVar3 - *(byte *)(iVar14 + 1);
      *puVar11 = *(undefined1 *)(iVar14 + 4);
      puVar11 = puVar11 + 1;
      local_10 = local_10 - 1;
    }
    else {
      uVar8 = uVar8 >> (*(byte *)(iVar14 + 1) & 0x1f);
      uVar3 = uVar3 - *(byte *)(iVar14 + 1);
      while ((bVar1 & 0x10) == 0) {
        if ((uVar10 & 0x40) != 0) {
          if ((uVar10 & 0x20) != 0) {
            uVar7 = param_6[1] - local_14;
            if (uVar3 >> 3 < param_6[1] - local_14) {
              uVar7 = uVar3 >> 3;
            }
            *(uint *)(param_5 + 0x20) = uVar8;
            *(uint *)(param_5 + 0x1c) = uVar3 + uVar7 * -8;
            iVar14 = *param_6;
            param_6[1] = uVar7 + local_14;
            *param_6 = (int)pbVar15 - uVar7;
            param_6[2] = param_6[2] + (((int)pbVar15 - uVar7) - iVar14);
            *(undefined1 **)(param_5 + 0x34) = puVar11;
            return 1;
          }
          param_6[6] = (int)s_invalid_literal_length_code_004f20b4;
          param_2 = uVar3 >> 3;
          uVar7 = param_6[1] - local_14;
          if (param_2 < param_6[1] - local_14) goto LAB_004cb9ef;
          goto LAB_004cb9eb;
        }
        iVar4 = (*(uint *)(&DAT_004f32c8 + uVar10 * 4) & uVar8) + *(int *)(iVar14 + 4);
        bVar1 = *(byte *)(iVar14 + iVar4 * 8);
        uVar10 = (uint)bVar1;
        iVar14 = iVar14 + iVar4 * 8;
        if (uVar10 == 0) goto LAB_004cb8bb;
        uVar8 = uVar8 >> (*(byte *)(iVar14 + 1) & 0x1f);
        uVar3 = uVar3 - *(byte *)(iVar14 + 1);
      }
      uVar10 = uVar10 & 0xf;
      uVar5 = (*(uint *)(&DAT_004f32c8 + uVar10 * 4) & uVar8) + *(int *)(iVar14 + 4);
      uVar9 = uVar8 >> (sbyte)uVar10;
      for (uVar3 = uVar3 - uVar10; uVar3 < 0xf; uVar3 = uVar3 + 8) {
        local_14 = local_14 - 1;
        uVar9 = uVar9 | (uint)*pbVar15 << ((byte)uVar3 & 0x1f);
        pbVar15 = pbVar15 + 1;
        local_c = (uint)pbVar15;
      }
      iVar14 = param_4 + (uVar2 & uVar9) * 8;
      uVar8 = uVar9 >> (*(byte *)(iVar14 + 1) & 0x1f);
      uVar3 = uVar3 - *(byte *)(iVar14 + 1);
      bVar1 = *(byte *)(param_4 + (uVar2 & uVar9) * 8);
      while ((bVar1 & 0x10) == 0) {
        if ((bVar1 & 0x40) != 0) {
          param_6[6] = (int)s_invalid_distance_code_004f209c;
          param_2 = uVar3 >> 3;
          uVar7 = param_6[1] - local_14;
          if (param_6[1] - local_14 <= param_2) {
LAB_004cb9eb:
            param_2 = uVar7;
          }
LAB_004cb9ef:
          *(uint *)(param_5 + 0x20) = uVar8;
          *(uint *)(param_5 + 0x1c) = uVar3 + param_2 * -8;
          param_6[1] = param_2 + local_14;
          iVar14 = *param_6;
          *param_6 = (int)pbVar15 - param_2;
          param_6[2] = param_6[2] + (((int)pbVar15 - param_2) - iVar14);
          *(undefined1 **)(param_5 + 0x34) = puVar11;
          return 0xfffffffd;
        }
        iVar4 = (*(uint *)(&DAT_004f32c8 + (uint)bVar1 * 4) & uVar8) + *(int *)(iVar14 + 4);
        pbVar6 = (byte *)(iVar14 + iVar4 * 8);
        iVar14 = iVar14 + iVar4 * 8;
        uVar8 = uVar8 >> (*(byte *)(iVar14 + 1) & 0x1f);
        uVar3 = uVar3 - *(byte *)(iVar14 + 1);
        bVar1 = *pbVar6;
      }
      uVar10 = bVar1 & 0xf;
      pbVar6 = pbVar15;
      pbVar15 = (byte *)local_c;
      for (; uVar3 < uVar10; uVar3 = uVar3 + 8) {
        local_14 = local_14 - 1;
        uVar8 = uVar8 | (uint)*pbVar6 << ((byte)uVar3 & 0x1f);
        pbVar6 = pbVar15 + 1;
        pbVar15 = pbVar6;
      }
      uVar3 = uVar3 - uVar10;
      uVar9 = (*(uint *)(&DAT_004f32c8 + uVar10 * 4) & uVar8) + *(int *)(iVar14 + 4);
      uVar8 = uVar8 >> (sbyte)uVar10;
      local_10 = local_10 - uVar5;
      if ((uint)((int)puVar11 - *(int *)(param_5 + 0x28)) < uVar9) {
        uVar10 = (uVar9 - (int)puVar11) + *(int *)(param_5 + 0x28);
        puVar13 = (undefined1 *)(*(int *)(param_5 + 0x2c) - uVar10);
        if (uVar10 < uVar5) {
          uVar5 = uVar5 - uVar10;
          do {
            *puVar11 = *puVar13;
            puVar11 = puVar11 + 1;
            puVar13 = puVar13 + 1;
            uVar10 = uVar10 - 1;
          } while (uVar10 != 0);
          puVar13 = *(undefined1 **)(param_5 + 0x28);
        }
      }
      else {
        puVar12 = puVar11 + -uVar9;
        *puVar11 = *puVar12;
        puVar13 = puVar12 + 2;
        puVar11[1] = puVar12[1];
        uVar5 = uVar5 - 2;
        puVar11 = puVar11 + 2;
      }
      do {
        *puVar11 = *puVar13;
        puVar11 = puVar11 + 1;
        puVar13 = puVar13 + 1;
        uVar5 = uVar5 - 1;
        local_c = (uint)pbVar15;
      } while (uVar5 != 0);
    }
    if ((local_10 < 0x102) || (local_14 < 10)) {
      uVar7 = param_6[1] - local_14;
      if (uVar3 >> 3 < param_6[1] - local_14) {
        uVar7 = uVar3 >> 3;
      }
      *(uint *)(param_5 + 0x20) = uVar8;
      *(uint *)(param_5 + 0x1c) = uVar3 + uVar7 * -8;
      iVar14 = *param_6;
      param_6[1] = uVar7 + local_14;
      *param_6 = (int)pbVar15 - uVar7;
      param_6[2] = param_6[2] + (((int)pbVar15 - uVar7) - iVar14);
      *(undefined1 **)(param_5 + 0x34) = puVar11;
      return 0;
    }
  } while( true );
}
#undef local_10
#undef local_14
#undef local_4
#undef local_8
#undef local_c

#endif

