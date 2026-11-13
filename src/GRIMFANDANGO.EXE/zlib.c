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
  int *piVar2;
  uint uVar3;
  char *pcVar4;
  undefined *puVar5;
  undefined4 *puVar6;
  int iVar7;
  uint uVar8;
  char *pcVar9;
  char *pcVar10;
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
  piVar2 = (int *)malloc(100);
  if (piVar2 == (int *)0x0) {
    return (void *)0x0;
  }
  piVar2[8] = 0;
  piVar2[9] = 0;
  piVar2[10] = 0;
  piVar2[0x11] = 0;
  *piVar2 = 0;
  piVar2[0x12] = 0;
  piVar2[3] = 0;
  piVar2[4] = 0;
  piVar2[1] = 0;
  piVar2[0x10] = 0;
  piVar2[0xe] = 0;
  piVar2[0xf] = 0;
  uVar3 = crc32(0,(byte *)0x0,0);
  piVar2[0x13] = uVar3;
  uVar3 = 0xffffffff;
  piVar2[0x14] = 0;
  piVar2[0x16] = 0;
  pcVar4 = path;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  pcVar4 = malloc(~uVar3);
  piVar2[0x15] = (int)pcVar4;
  if (pcVar4 != (char *)0x0) {
    uVar3 = 0xffffffff;
    pcVar9 = path;
    do {
      pcVar10 = pcVar9;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar10 = pcVar9 + 1;
      cVar1 = *pcVar9;
      pcVar9 = pcVar10;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    pcVar9 = pcVar10 + -uVar3;
    for (uVar8 = uVar3 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar4 = *(undefined4 *)pcVar9;
      pcVar9 = pcVar9 + 4;
      pcVar4 = pcVar4 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar4 = *pcVar9;
      pcVar9 = pcVar9 + 1;
      pcVar4 = pcVar4 + 1;
    }
    *(undefined1 *)(piVar2 + 0x17) = 0;
    pcVar4 = mode;
    mode = local_50;
    do {
      if (*pcVar4 == 'r') {
        *(undefined1 *)(piVar2 + 0x17) = 0x72;
      }
      if ((*pcVar4 == 'w') || (*pcVar4 == 'a')) {
        *(undefined1 *)(piVar2 + 0x17) = 0x77;
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
    if ((char)piVar2[0x17] != '\0') {
      if ((char)piVar2[0x17] == 'w') {
        uVar3 = deflateInit2_((int)piVar2,local_60,8,-0xf,8,local_64,s_1_1_3_004f1a20,0x38);
        puVar5 = malloc(0x4000);
        piVar2[0x12] = (int)puVar5;
        piVar2[3] = (int)puVar5;
        if (uVar3 != 0) goto LAB_004c410c;
        if (puVar5 == (undefined *)0x0) {
          gz_destroy((int)piVar2);
          return (void *)0x0;
        }
      }
      else {
        puVar5 = malloc(0x4000);
        piVar2[0x11] = (int)puVar5;
        *piVar2 = (int)puVar5;
        uVar3 = inflateInit2_((int)piVar2,-0xf,s_1_1_3_004f1a20,0x38);
        if ((uVar3 != 0) || (piVar2[0x11] == 0)) goto LAB_004c410c;
      }
      piVar2[4] = 0x4000;
      puVar6 = (undefined4 *)_errno();
      *puVar6 = 0;
      if (fd < 0) {
        iVar7 = (*(code *)*g_pZf_filio_services)(path);
      }
      else {
        iVar7 = _fdopen(fd,local_50);
      }
      piVar2[0x10] = iVar7;
      if (iVar7 != 0) {
        if ((char)piVar2[0x17] == 'w') {
          local_5b = 0;
          local_57 = 0;
          cStack_5c = DAT_004f5a98;
          uStack_53 = 0;
          sprintf(&cStack_5c,s__c_c_c_c_c_c_c_c_c_c_004f1a08,UINT_004f1a00,UINT_004f1a04,8,0,0,0,0,0
                  ,0,0xb);
          (*(code *)g_pZf_filio_services[3])(piVar2[0x10],&cStack_5c,10);
          piVar2[0x18] = 10;
          return piVar2;
        }
        gz_check_header(piVar2);
        if (piVar2[0x16] != 1) {
          iVar7 = (*(code *)g_pZf_filio_services[4])(piVar2[0x10]);
          piVar2[0x18] = iVar7 - piVar2[1];
          return piVar2;
        }
      }
    }
  }
LAB_004c410c:
  gz_destroy((int)piVar2);
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
void __cdecl gz_check_header(int *param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint *puVar5;
  
  iVar4 = 0;
  puVar5 = &UINT_004f1a00;
  do {
    uVar1 = gz_get_byte(param_1);
    if (uVar1 != *puVar5) {
      if (iVar4 != 0) {
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
    puVar5 = puVar5 + 1;
    iVar4 = iVar4 + 1;
  } while (puVar5 < s__c_c_c_c_c_c_c_c_c_c_004f1a08);
  uVar1 = gz_get_byte(param_1);
  uVar2 = gz_get_byte(param_1);
  if ((uVar1 != 8) || ((uVar2 & 0xe0) != 0)) {
    param_1[0xe] = -3;
    return;
  }
  iVar4 = 6;
  do {
    gz_get_byte(param_1);
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  if ((uVar2 & 4) != 0) {
    uVar1 = gz_get_byte(param_1);
    uVar3 = gz_get_byte(param_1);
    iVar4 = uVar1 + uVar3 * 0x100;
    do {
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      uVar1 = gz_get_byte(param_1);
    } while (uVar1 != 0xffffffff);
  }
  if ((uVar2 & 8) != 0) {
    uVar1 = gz_get_byte(param_1);
    while ((uVar1 != 0 && (uVar1 != 0xffffffff))) {
      uVar1 = gz_get_byte(param_1);
    }
  }
  if ((uVar2 & 0x10) != 0) {
    uVar1 = gz_get_byte(param_1);
    while ((uVar1 != 0 && (uVar1 != 0xffffffff))) {
      uVar1 = gz_get_byte(param_1);
    }
  }
  if ((uVar2 & 2) != 0) {
    iVar4 = 2;
    do {
      gz_get_byte(param_1);
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  param_1[0xe] = -(uint)(param_1[0xf] != 0) & 0xfffffffd;
  return;
}

/* ---- 0x004c4280  gz_get_byte ---- */
uint __cdecl gz_get_byte(undefined4 *param_1)

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
    iVar3 = (*(code *)g_pZf_filio_services[2])(param_1[0x10],param_1[0x11],0x4000);
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
int __cdecl gz_destroy(int param_1)

{
  int *piVar1;
  uint uVar2;
  
  uVar2 = 0;
  if (param_1 != 0) {
    if (*(int *)(param_1 + 0x50) != 0) {
      free(*(int *)(param_1 + 0x50));
    }
    if (*(int *)(param_1 + 0x1c) != 0) {
      if (*(char *)(param_1 + 0x5c) == 'w') {
        uVar2 = deflateEnd(param_1);
      }
      else if (*(char *)(param_1 + 0x5c) == 'r') {
        uVar2 = inflateEnd(param_1);
      }
    }
    if (*(int *)(param_1 + 0x40) != 0) {
      (*(code *)g_pZf_filio_services[1])(*(int *)(param_1 + 0x40));
      piVar1 = (int *)_errno();
      if (*piVar1 != 0x1d) {
        uVar2 = 0xffffffff;
      }
    }
    if ((int)*(uint *)(param_1 + 0x38) < 0) {
      uVar2 = *(uint *)(param_1 + 0x38);
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
    return uVar2;
  }
  return -2;
}

/* ---- 0x004c43a0  gzread ---- */
int __cdecl gzread(int *param_1,int param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined *puVar5;
  uint uVar6;
  uint uVar7;
  byte *pbVar8;
  undefined4 *puVar9;
  
  piVar2 = param_1;
  if ((param_1 == (int *)0x0) || ((char)param_1[0x17] != 'r')) {
    return -2;
  }
  iVar4 = param_1[0xe];
  if ((iVar4 == -3) || (iVar4 == -1)) {
    return -1;
  }
  if (iVar4 == 1) {
    return 0;
  }
  param_1 = (int *)param_2;
  piVar2[3] = param_2;
  piVar2[4] = param_3;
  pbVar8 = (byte *)param_2;
  if (param_3 != 0) {
    do {
      uVar6 = piVar2[1];
      if (piVar2[0x16] != 0) {
        if ((uint)piVar2[4] < uVar6) {
          uVar6 = piVar2[4];
        }
        if (uVar6 != 0) {
          puVar3 = (undefined4 *)*piVar2;
          puVar9 = (undefined4 *)piVar2[3];
          for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
            *puVar9 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar9 = puVar9 + 1;
          }
          for (uVar7 = uVar6 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
            *(undefined1 *)puVar9 = *(undefined1 *)puVar3;
            puVar3 = (undefined4 *)((int)puVar3 + 1);
            puVar9 = (undefined4 *)((int)puVar9 + 1);
          }
          param_1 = (int *)(param_2 + uVar6);
          piVar2[3] = (int)param_1;
          *piVar2 = *piVar2 + uVar6;
          piVar2[4] = piVar2[4] - uVar6;
          piVar2[1] = piVar2[1] - uVar6;
        }
        if (piVar2[4] != 0) {
          iVar4 = (*(code *)g_pZf_filio_services[2])(piVar2[0x10],param_1,piVar2[4]);
          piVar2[4] = piVar2[4] - iVar4;
        }
        iVar4 = param_3 - piVar2[4];
        piVar2[2] = piVar2[2] + iVar4;
        piVar2[5] = piVar2[5] + iVar4;
        if (iVar4 == 0) {
          piVar2[0xf] = 1;
        }
        return iVar4;
      }
      if ((uVar6 == 0) && (piVar2[0xf] == 0)) {
        puVar3 = (undefined4 *)_errno();
        *puVar3 = 0;
        iVar4 = (*(code *)g_pZf_filio_services[2])(piVar2[0x10],piVar2[0x11],0x4000);
        piVar2[1] = iVar4;
        if (iVar4 == 0) {
          piVar2[0xf] = 1;
        }
        *piVar2 = piVar2[0x11];
      }
      puVar5 = inflate(piVar2,0);
      piVar2[0xe] = (int)puVar5;
      if (puVar5 == (undefined *)0x1) {
        uVar6 = crc32(piVar2[0x13],pbVar8,piVar2[3] - (int)pbVar8);
        pbVar8 = (byte *)piVar2[3];
        piVar2[0x13] = uVar6;
        iVar4 = gz_getLong((int)piVar2);
        if (iVar4 == piVar2[0x13]) {
          gz_getLong((int)piVar2);
          gz_check_header(piVar2);
          if (piVar2[0xe] != 0) break;
          iVar4 = piVar2[2];
          iVar1 = piVar2[5];
          inflateReset((int)piVar2);
          piVar2[2] = iVar4;
          piVar2[5] = iVar1;
          uVar6 = crc32(0,(byte *)0x0,0);
          piVar2[0x13] = uVar6;
        }
        else {
          piVar2[0xe] = -3;
        }
      }
      if (((piVar2[0xe] != 0) || (piVar2[0xf] != 0)) || (piVar2[4] == 0)) break;
    } while( true );
  }
  uVar6 = crc32(piVar2[0x13],pbVar8,piVar2[3] - (int)pbVar8);
  piVar2[0x13] = uVar6;
  return param_3 - piVar2[4];
}

/* ---- 0x004c45b0  gzwrite ---- */
int __cdecl gzwrite(undefined4 *param_1,uint param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  
  if ((param_1 == (undefined4 *)0x0) || (*(char *)(param_1 + 0x17) != 'w')) {
    return -2;
  }
  *param_1 = param_2;
  param_1[1] = param_3;
  iVar1 = param_3;
  do {
    if (iVar1 == 0) {
LAB_004c4624:
      uVar2 = crc32(param_1[0x13],(byte *)param_2,param_3);
      param_1[0x13] = uVar2;
      return param_3 - param_1[1];
    }
    if (param_1[4] == 0) {
      param_1[3] = param_1[0x12];
      iVar1 = (*(code *)g_pZf_filio_services[3])(param_1[0x10],param_1[0x12],0x4000);
      if (iVar1 != 0x4000) {
        param_1[0xe] = 0xffffffff;
        goto LAB_004c4624;
      }
      param_1[4] = 0x4000;
    }
    uVar2 = deflate(param_1,0);
    param_1[0xe] = uVar2;
    if (uVar2 != 0) goto LAB_004c4624;
    iVar1 = param_1[1];
  } while( true );
}

/* ---- 0x004c4690  gz_do_flush ---- */
uint __cdecl gz_do_flush(int param_1,uint param_2)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  bVar1 = false;
  if ((param_1 == 0) || (*(char *)(param_1 + 0x5c) != 'w')) {
    return 0xfffffffe;
  }
  *(undefined4 *)(param_1 + 4) = 0;
  do {
    iVar4 = 0x4000 - *(int *)(param_1 + 0x10);
    if (iVar4 != 0) {
      iVar2 = (*(code *)g_pZf_filio_services[3])
                        (*(undefined4 *)(param_1 + 0x40),*(undefined4 *)(param_1 + 0x48),iVar4);
      if (iVar2 != iVar4) {
        *(undefined4 *)(param_1 + 0x38) = 0xffffffff;
        return 0xffffffff;
      }
      *(undefined4 *)(param_1 + 0x10) = 0x4000;
      *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(param_1 + 0x48);
    }
    if (bVar1) break;
    uVar3 = deflate((int *)param_1,param_2);
    *(uint *)(param_1 + 0x38) = uVar3;
    if ((iVar4 == 0) && (uVar3 == 0xfffffffb)) {
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
uint __cdecl gzseek(undefined4 *param_1,uint param_2,int param_3)

{
  undefined4 *puVar1;
  uint uVar2;
  undefined *puVar3;
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
          uVar2 = 0x4000;
          if ((int)param_2 < 0x4000) {
            uVar2 = param_2;
          }
          iVar4 = gzwrite(param_1,param_1[0x11],uVar2);
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
          (*(code *)g_pZf_filio_services[5])(param_1[0x10],param_2,0);
          param_1[5] = param_2;
          param_1[2] = param_2;
          return param_2;
        }
        if (param_2 < (uint)param_1[5]) {
          uVar2 = gzrewind(param_1);
          if ((int)uVar2 < 0) {
            return 0xffffffff;
          }
        }
        else {
          param_2 = param_2 - param_1[5];
        }
        if (param_2 != 0) {
          if (param_1[0x12] == 0) {
            puVar3 = malloc(0x4000);
            param_1[0x12] = puVar3;
          }
          for (; 0 < (int)param_2; param_2 = param_2 - iVar4) {
            uVar2 = 0x4000;
            if ((int)param_2 < 0x4000) {
              uVar2 = param_2;
            }
            iVar4 = gzread(param_1,param_1[0x12],uVar2);
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
uint __cdecl gzrewind(undefined4 *param_1)

{
  uint uVar1;
  
  if ((param_1 != (undefined4 *)0x0) && (*(char *)(param_1 + 0x17) == 'r')) {
    param_1[0xe] = 0;
    param_1[0xf] = 0;
    param_1[1] = 0;
    *param_1 = param_1[0x11];
    uVar1 = crc32(0,(byte *)0x0,0);
    param_1[0x13] = uVar1;
    if (param_1[0x18] == 0) {
      rewind(param_1[0x10]);
      return 0;
    }
    inflateReset((int)param_1);
    uVar1 = (*(code *)g_pZf_filio_services[5])(param_1[0x10],param_1[0x18],0);
    return uVar1;
  }
  return 0xffffffff;
}

/* ---- 0x004c4920  gz_getLong ---- */
int __cdecl gz_getLong(int param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar1 = gz_get_byte((undefined4 *)param_1);
  uVar2 = gz_get_byte((undefined4 *)param_1);
  uVar3 = gz_get_byte((undefined4 *)param_1);
  uVar4 = gz_get_byte((undefined4 *)param_1);
  if (uVar4 == 0xffffffff) {
    *(undefined4 *)(param_1 + 0x38) = 0xfffffffd;
  }
  return uVar4 * 0x1000000 + uVar1 + uVar2 * 0x100 + uVar3 * 0x10000;
}

/* ---- 0x004c4970  gzclose ---- */
uint __cdecl gzclose(int param_1)

{
  uint uVar1;
  
  if (param_1 == 0) {
    return 0xfffffffe;
  }
  if (*(char *)(param_1 + 0x5c) == 'w') {
    uVar1 = gz_do_flush(param_1,4);
    if (uVar1 == 0) {
      gz_putLong(*(void **)(param_1 + 0x40),*(uint *)(param_1 + 0x4c));
      gz_putLong(*(void **)(param_1 + 0x40),*(uint *)(param_1 + 8));
    }
  }
  uVar1 = gz_destroy(param_1);
  return uVar1;
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
    (*(code *)g_pZf_filio_services[3])(pvVar1,&file,1);
    uVar2 = uVar2 >> 8;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return;
}
#endif


/* ---- 0x004c4c40  zlibVersion ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* MSVC CRT default _matherr: returns 0 (was mislabelled zlibVersion) */

undefined4 zlibVersion(void)

{
  return 0;
}

/* ---- 0x004c57d0  fle_zfilio_config ---- */
/* zlib deflate.c helper taking the stream only; exact identity not confirmed Original name
   fle_zfilio_config (the remaster's GrimFandango (Linux): strings: 'Too many zfilio extension
   set'); was deflateParams_or_SetDictionary. */

uint __cdecl fle_zfilio_config(int cmd,...)

{
  undefined *puVar1;
  uint uVar2;
  uint uVar3;
  int *piVar4;
  
  piVar4 = (int *)&STACK0X(0x00000008);
  uVar2 = UINT_004f1c20;
  uVar3 = g_dwZfile_virtherc_services;
  if (cmd == 0) {
    return 0;
  }
  do {
    if (cmd != 1) {
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
      uVar3 = g_dwZfile_virtherc_services;
    }
    cmd = *piVar4;
    piVar4 = piVar4 + 1;
  } while (cmd != 0);
  return 0;
}

/* ---- 0x004c6040  inflateReset ---- */
/* not in the source: names/lib_replace.json (zlib): the system zlib (libz.a) has it */


/* ---- 0x004c6090  inflateEnd ---- */
/* not in the source: names/lib_replace.json (zlib): the system zlib (libz.a) has it */


/* ---- 0x004c60e0  inflateInit2_ ---- */
/* not in the source: names/lib_replace.json (zlib): the system zlib (libz.a) has it */


/* ---- 0x004c61f0  inflate ---- */
/* not in the source: names/lib_replace.json (zlib): the system zlib (libz.a) has it */


/* ---- 0x004c6640  deflateInit2_ ---- */
/* not in the source: names/lib_replace.json (zlib): the system zlib (libz.a) has it */


/* ---- 0x004c6870  deflateReset ---- */
/* not in the source: names/lib_replace.json (zlib): the system zlib (libz.a) has it */


/* ---- 0x004c68f0  deflate ---- */
/* not in the source: names/lib_replace.json (zlib): the system zlib (libz.a) has it */


/* ---- 0x004c6bb0  putShortMSB ---- */
/* not in the source: names/lib_replace.json (zlib): the system zlib (libz.a) has it */


/* ---- 0x004c6be0  flush_pending ---- */
/* not in the source: names/lib_replace.json (zlib): the system zlib (libz.a) has it */


/* ---- 0x004c6c60  deflateEnd ---- */
/* not in the source: names/lib_replace.json (zlib): the system zlib (libz.a) has it */


/* ---- 0x004c6d10  lm_init ---- */
/* not in the source: names/lib_replace.json (zlib): the system zlib (libz.a) has it */


/* ---- 0x004c79b0  crc32 ---- */
/* not in the source: names/lib_replace.json (zlib): the system zlib (libz.a) has it */


/* ---- 0x004c7af0  zcalloc ---- */
/* not in the source: names/lib_replace.json (zlib): the system zlib (libz.a) has it */


/* ---- 0x004c7b20  inflate_blocks_reset ---- */
/* not in the source: names/lib_replace.json (zlib): the system zlib (libz.a) has it */


/* ---- 0x004c7ba0  inflate_blocks_new ---- */
/* not in the source: names/lib_replace.json (zlib): the system zlib (libz.a) has it */


/* ---- 0x004c7c50  inflate_blocks ---- */
/* not in the source: names/lib_replace.json (zlib): the system zlib (libz.a) has it */


/* ---- 0x004c8940  inflate_blocks_free ---- */
/* not in the source: names/lib_replace.json (zlib): the system zlib (libz.a) has it */


/* ---- 0x004c8ac0  _tr_init ---- */
/* not in the source: names/lib_replace.json (zlib): the system zlib (libz.a) has it */


/* ---- 0x004c8b30  init_block ---- */
/* not in the source: names/lib_replace.json (zlib): the system zlib (libz.a) has it */


/* ---- 0x004c8c40  _tr_align ---- */
/* not in the source: names/lib_replace.json (zlib): the system zlib (libz.a) has it */


/* ---- 0x004ca480  bi_flush ---- */
/* not in the source: names/lib_replace.json (zlib): the system zlib (libz.a) has it */


/* ---- 0x004ca510  bi_windup ---- */
/* not in the source: names/lib_replace.json (zlib): the system zlib (libz.a) has it */


/* ---- 0x004ca580  copy_block ---- */
/* not in the source: names/lib_replace.json (zlib): the system zlib (libz.a) has it */


/* ---- 0x004ca620  inflate_codes_new ---- */
/* not in the source: names/lib_replace.json (zlib): the system zlib (libz.a) has it */


/* ---- 0x004ca660  inflate_codes ---- */
/* not in the source: names/lib_replace.json (zlib): the system zlib (libz.a) has it */


/* ---- 0x004cae10  inflate_codes_free ---- */
/* not in the source: names/lib_replace.json (zlib): the system zlib (libz.a) has it */


/* ---- 0x004cae30  inflate_trees_bits ---- */
/* not in the source: names/lib_replace.json (zlib): the system zlib (libz.a) has it */


/* ---- 0x004caee0  huft_build ---- */
/* not in the source: names/lib_replace.json (zlib): the system zlib (libz.a) has it */


/* ---- 0x004cb390  inflate_trees_dynamic ---- */
/* not in the source: names/lib_replace.json (zlib): the system zlib (libz.a) has it */


/* ---- 0x004cb520  inflate_trees_fixed ---- */
/* not in the source: names/lib_replace.json (zlib): the system zlib (libz.a) has it */


/* ---- 0x004cb550  inflate_flush ---- */
/* not in the source: names/lib_replace.json (zlib): the system zlib (libz.a) has it */


/* ---- 0x004cb690  inflate_fast ---- */
/* not in the source: names/lib_replace.json (zlib): the system zlib (libz.a) has it */

