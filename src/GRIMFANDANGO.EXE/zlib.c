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
  int *s;
  uint uVar2;
  char *pcVar3;
  undefined *puVar4;
  undefined4 *puVar5;
  int iVar6;
  uint uVar7;
  char *pcVar8;
  char *pcVar9;
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
  s = (int *)malloc(100);
  if (s == (int *)0x0) {
    return (void *)0x0;
  }
  s[8] = 0;
  s[9] = 0;
  s[10] = 0;
  s[0x11] = 0;
  *s = 0;
  s[0x12] = 0;
  s[3] = 0;
  s[4] = 0;
  s[1] = 0;
  s[0x10] = 0;
  s[0xe] = 0;
  s[0xf] = 0;
  uVar2 = crc32(0,(byte *)0x0,0);
  s[0x13] = uVar2;
  uVar2 = 0xffffffff;
  s[0x14] = 0;
  s[0x16] = 0;
  pcVar3 = path;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  pcVar3 = malloc(~uVar2);
  s[0x15] = (int)pcVar3;
  if (pcVar3 != (char *)0x0) {
    uVar2 = 0xffffffff;
    pcVar8 = path;
    do {
      pcVar9 = pcVar8;
      if (uVar2 == 0) break;
      uVar2 = uVar2 - 1;
      pcVar9 = pcVar8 + 1;
      cVar1 = *pcVar8;
      pcVar8 = pcVar9;
    } while (cVar1 != '\0');
    uVar2 = ~uVar2;
    pcVar8 = pcVar9 + -uVar2;
    for (uVar7 = uVar2 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar3 = *(undefined4 *)pcVar8;
      pcVar8 = pcVar8 + 4;
      pcVar3 = pcVar3 + 4;
    }
    for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *pcVar3 = *pcVar8;
      pcVar8 = pcVar8 + 1;
      pcVar3 = pcVar3 + 1;
    }
    *(undefined1 *)(s + 0x17) = 0;
    pcVar3 = mode;
    mode = local_50;
    do {
      if (*pcVar3 == 'r') {
        *(undefined1 *)(s + 0x17) = 0x72;
      }
      if ((*pcVar3 == 'w') || (*pcVar3 == 'a')) {
        *(undefined1 *)(s + 0x17) = 0x77;
      }
      cVar1 = *pcVar3;
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
      pcVar3 = pcVar3 + 1;
    } while ((cVar1 != '\0') && (mode != &STACK0X(0x00000000)));
    if ((char)s[0x17] != '\0') {
      if ((char)s[0x17] == 'w') {
        uVar2 = deflateInit2_((int)s,local_60,8,-0xf,8,local_64,s_1_1_3_004f1a20,0x38);
        puVar4 = malloc(0x4000);
        s[0x12] = (int)puVar4;
        s[3] = (int)puVar4;
        if (uVar2 != 0) goto LAB_004c410c;
        if (puVar4 == (undefined *)0x0) {
          gz_destroy((int)s);
          return (void *)0x0;
        }
      }
      else {
        puVar4 = malloc(0x4000);
        s[0x11] = (int)puVar4;
        *s = (int)puVar4;
        uVar2 = inflateInit2_((int)s,-0xf,s_1_1_3_004f1a20,0x38);
        if ((uVar2 != 0) || (s[0x11] == 0)) goto LAB_004c410c;
      }
      s[4] = 0x4000;
      puVar5 = (undefined4 *)_errno();
      *puVar5 = 0;
      if (fd < 0) {
        iVar6 = (*(code *)*g_pZf_filio_services)(path);
      }
      else {
        iVar6 = _fdopen(fd,local_50);
      }
      s[0x10] = iVar6;
      if (iVar6 != 0) {
        if ((char)s[0x17] == 'w') {
          local_5b = 0;
          local_57 = 0;
          cStack_5c = DAT_004f5a98;
          uStack_53 = 0;
          sprintf(&cStack_5c,s__c_c_c_c_c_c_c_c_c_c_004f1a08,UINT_004f1a00,UINT_004f1a04,8,0,0,0,0,0
                  ,0,0xb);
          (*(code *)g_pZf_filio_services[3])(s[0x10],&cStack_5c,10);
          s[0x18] = 10;
          return s;
        }
        gz_check_header(s);
        if (s[0x16] != 1) {
          iVar6 = (*(code *)g_pZf_filio_services[4])(s[0x10]);
          s[0x18] = iVar6 - s[1];
          return s;
        }
      }
    }
  }
LAB_004c410c:
  gz_destroy((int)s);
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
void __cdecl gz_check_header(int *s)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint *puVar5;
  
  iVar4 = 0;
  puVar5 = &UINT_004f1a00;
  do {
    uVar1 = gz_get_byte(s);
    if (uVar1 != *puVar5) {
      if (iVar4 != 0) {
        s[1] = s[1] + 1;
        *s = *s + -1;
      }
      if (uVar1 != 0xffffffff) {
        s[1] = s[1] + 1;
        *s = *s + -1;
        s[0x16] = 1;
      }
      s[0xe] = (uint)(s[1] == 0);
      return;
    }
    puVar5 = puVar5 + 1;
    iVar4 = iVar4 + 1;
  } while (puVar5 < s__c_c_c_c_c_c_c_c_c_c_004f1a08);
  uVar1 = gz_get_byte(s);
  uVar2 = gz_get_byte(s);
  if ((uVar1 != 8) || ((uVar2 & 0xe0) != 0)) {
    s[0xe] = -3;
    return;
  }
  iVar4 = 6;
  do {
    gz_get_byte(s);
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  if ((uVar2 & 4) != 0) {
    uVar1 = gz_get_byte(s);
    uVar3 = gz_get_byte(s);
    iVar4 = uVar1 + uVar3 * 0x100;
    do {
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      uVar1 = gz_get_byte(s);
    } while (uVar1 != 0xffffffff);
  }
  if ((uVar2 & 8) != 0) {
    uVar1 = gz_get_byte(s);
    while ((uVar1 != 0 && (uVar1 != 0xffffffff))) {
      uVar1 = gz_get_byte(s);
    }
  }
  if ((uVar2 & 0x10) != 0) {
    uVar1 = gz_get_byte(s);
    while ((uVar1 != 0 && (uVar1 != 0xffffffff))) {
      uVar1 = gz_get_byte(s);
    }
  }
  if ((uVar2 & 2) != 0) {
    iVar4 = 2;
    do {
      gz_get_byte(s);
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  s[0xe] = -(uint)(s[0xf] != 0) & 0xfffffffd;
  return;
}

/* ---- 0x004c4280  gz_get_byte ---- */
uint __cdecl gz_get_byte(undefined4 *s)

{
  byte bVar1;
  undefined4 *puVar2;
  int iVar3;
  
  if (s[0xf] != 0) {
    return 0xffffffff;
  }
  if (s[1] == 0) {
    puVar2 = (undefined4 *)_errno();
    *puVar2 = 0;
    iVar3 = (*(code *)g_pZf_filio_services[2])(s[0x10],s[0x11],0x4000);
    s[1] = iVar3;
    if (iVar3 == 0) {
      s[0xf] = 1;
      return 0xffffffff;
    }
    *s = s[0x11];
  }
  s[1] = s[1] + -1;
  bVar1 = *(byte *)*s;
  *s = (byte *)*s + 1;
  return (uint)bVar1;
}

/* ---- 0x004c42f0  gz_destroy ---- */
int __cdecl gz_destroy(int s)

{
  int *piVar1;
  uint uVar2;
  
  uVar2 = 0;
  if (s != 0) {
    if (*(int *)(s + 0x50) != 0) {
      free(*(int *)(s + 0x50));
    }
    if (*(int *)(s + 0x1c) != 0) {
      if (*(char *)(s + 0x5c) == 'w') {
        uVar2 = deflateEnd(s);
      }
      else if (*(char *)(s + 0x5c) == 'r') {
        uVar2 = inflateEnd(s);
      }
    }
    if (*(int *)(s + 0x40) != 0) {
      (*(code *)g_pZf_filio_services[1])(*(int *)(s + 0x40));
      piVar1 = (int *)_errno();
      if (*piVar1 != 0x1d) {
        uVar2 = 0xffffffff;
      }
    }
    if ((int)*(uint *)(s + 0x38) < 0) {
      uVar2 = *(uint *)(s + 0x38);
    }
    if (*(int *)(s + 0x44) != 0) {
      free(*(int *)(s + 0x44));
    }
    if (*(int *)(s + 0x48) != 0) {
      free(*(int *)(s + 0x48));
    }
    if (*(int *)(s + 0x54) != 0) {
      free(*(int *)(s + 0x54));
    }
    free(s);
    return uVar2;
  }
  return -2;
}

/* ---- 0x004c43a0  gzread ---- */
int __cdecl gzread(int *file,int buf,int len)

{
  int iVar1;
  int *s;
  undefined4 *puVar2;
  int iVar3;
  undefined *puVar4;
  uint uVar5;
  uint uVar6;
  byte *pbVar7;
  undefined4 *puVar8;
  
  s = file;
  if ((file == (int *)0x0) || ((char)file[0x17] != 'r')) {
    return -2;
  }
  iVar3 = file[0xe];
  if ((iVar3 == -3) || (iVar3 == -1)) {
    return -1;
  }
  if (iVar3 == 1) {
    return 0;
  }
  file = (int *)buf;
  s[3] = buf;
  s[4] = len;
  pbVar7 = (byte *)buf;
  if (len != 0) {
    do {
      uVar5 = s[1];
      if (s[0x16] != 0) {
        if ((uint)s[4] < uVar5) {
          uVar5 = s[4];
        }
        if (uVar5 != 0) {
          puVar2 = (undefined4 *)*s;
          puVar8 = (undefined4 *)s[3];
          for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
            *puVar8 = *puVar2;
            puVar2 = puVar2 + 1;
            puVar8 = puVar8 + 1;
          }
          for (uVar6 = uVar5 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
            *(undefined1 *)puVar8 = *(undefined1 *)puVar2;
            puVar2 = (undefined4 *)((int)puVar2 + 1);
            puVar8 = (undefined4 *)((int)puVar8 + 1);
          }
          file = (int *)(buf + uVar5);
          s[3] = (int)file;
          *s = *s + uVar5;
          s[4] = s[4] - uVar5;
          s[1] = s[1] - uVar5;
        }
        if (s[4] != 0) {
          iVar3 = (*(code *)g_pZf_filio_services[2])(s[0x10],file,s[4]);
          s[4] = s[4] - iVar3;
        }
        iVar3 = len - s[4];
        s[2] = s[2] + iVar3;
        s[5] = s[5] + iVar3;
        if (iVar3 == 0) {
          s[0xf] = 1;
        }
        return iVar3;
      }
      if ((uVar5 == 0) && (s[0xf] == 0)) {
        puVar2 = (undefined4 *)_errno();
        *puVar2 = 0;
        iVar3 = (*(code *)g_pZf_filio_services[2])(s[0x10],s[0x11],0x4000);
        s[1] = iVar3;
        if (iVar3 == 0) {
          s[0xf] = 1;
        }
        *s = s[0x11];
      }
      puVar4 = inflate(s,0);
      s[0xe] = (int)puVar4;
      if (puVar4 == (undefined *)0x1) {
        uVar5 = crc32(s[0x13],pbVar7,s[3] - (int)pbVar7);
        pbVar7 = (byte *)s[3];
        s[0x13] = uVar5;
        iVar3 = gz_getLong((int)s);
        if (iVar3 == s[0x13]) {
          gz_getLong((int)s);
          gz_check_header(s);
          if (s[0xe] != 0) break;
          iVar3 = s[2];
          iVar1 = s[5];
          inflateReset((int)s);
          s[2] = iVar3;
          s[5] = iVar1;
          uVar5 = crc32(0,(byte *)0x0,0);
          s[0x13] = uVar5;
        }
        else {
          s[0xe] = -3;
        }
      }
      if (((s[0xe] != 0) || (s[0xf] != 0)) || (s[4] == 0)) break;
    } while( true );
  }
  uVar5 = crc32(s[0x13],pbVar7,s[3] - (int)pbVar7);
  s[0x13] = uVar5;
  return len - s[4];
}

/* ---- 0x004c45b0  gzwrite ---- */
int __cdecl gzwrite(undefined4 *file,uint buf,int len)

{
  int iVar1;
  uint uVar2;
  
  if ((file == (undefined4 *)0x0) || (*(char *)(file + 0x17) != 'w')) {
    return -2;
  }
  *file = buf;
  file[1] = len;
  iVar1 = len;
  do {
    if (iVar1 == 0) {
LAB_004c4624:
      uVar2 = crc32(file[0x13],(byte *)buf,len);
      file[0x13] = uVar2;
      return len - file[1];
    }
    if (file[4] == 0) {
      file[3] = file[0x12];
      iVar1 = (*(code *)g_pZf_filio_services[3])(file[0x10],file[0x12],0x4000);
      if (iVar1 != 0x4000) {
        file[0xe] = 0xffffffff;
        goto LAB_004c4624;
      }
      file[4] = 0x4000;
    }
    uVar2 = deflate(file,0);
    file[0xe] = uVar2;
    if (uVar2 != 0) goto LAB_004c4624;
    iVar1 = file[1];
  } while( true );
}

/* ---- 0x004c4690  gz_do_flush ---- */
uint __cdecl gz_do_flush(int file,uint flush)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  bVar1 = false;
  if ((file == 0) || (*(char *)(file + 0x5c) != 'w')) {
    return 0xfffffffe;
  }
  *(undefined4 *)(file + 4) = 0;
  do {
    iVar4 = 0x4000 - *(int *)(file + 0x10);
    if (iVar4 != 0) {
      iVar2 = (*(code *)g_pZf_filio_services[3])
                        (*(undefined4 *)(file + 0x40),*(undefined4 *)(file + 0x48),iVar4);
      if (iVar2 != iVar4) {
        *(undefined4 *)(file + 0x38) = 0xffffffff;
        return 0xffffffff;
      }
      *(undefined4 *)(file + 0x10) = 0x4000;
      *(undefined4 *)(file + 0xc) = *(undefined4 *)(file + 0x48);
    }
    if (bVar1) break;
    uVar3 = deflate((int *)file,flush);
    *(uint *)(file + 0x38) = uVar3;
    if ((iVar4 == 0) && (uVar3 == 0xfffffffb)) {
      *(undefined4 *)(file + 0x38) = 0;
    }
    if ((*(int *)(file + 0x10) == 0) && (*(int *)(file + 0x38) != 1)) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
  } while ((*(int *)(file + 0x38) == 0) || (*(int *)(file + 0x38) == 1));
  return -(uint)(*(uint *)(file + 0x38) != 1) & *(uint *)(file + 0x38);
}

/* ---- 0x004c4750  gzseek ---- */
uint __cdecl gzseek(undefined4 *file,uint offset,int whence)

{
  undefined4 *puVar1;
  uint uVar2;
  undefined *puVar3;
  int iVar4;
  
  if ((((file != (undefined4 *)0x0) && (whence != 2)) && (file[0xe] != -1)) && (file[0xe] != -3)) {
    if (*(char *)(file + 0x17) == 'w') {
      if (whence == 0) {
        offset = offset - file[2];
      }
      if (-1 < (int)offset) {
        if (file[0x11] == 0) {
          puVar1 = (undefined4 *)malloc(0x4000);
          file[0x11] = puVar1;
          for (iVar4 = 0x1000; iVar4 != 0; iVar4 = iVar4 + -1) {
            *puVar1 = 0;
            puVar1 = puVar1 + 1;
          }
        }
        while( true ) {
          if ((int)offset < 1) {
            return file[2];
          }
          uVar2 = 0x4000;
          if ((int)offset < 0x4000) {
            uVar2 = offset;
          }
          iVar4 = gzwrite(file,file[0x11],uVar2);
          if (iVar4 == 0) break;
          offset = offset - iVar4;
        }
      }
    }
    else {
      if (whence == 1) {
        offset = offset + file[5];
      }
      if (-1 < (int)offset) {
        if (file[0x16] != 0) {
          file[1] = 0;
          *file = file[0x11];
          (*(code *)g_pZf_filio_services[5])(file[0x10],offset,0);
          file[5] = offset;
          file[2] = offset;
          return offset;
        }
        if (offset < (uint)file[5]) {
          uVar2 = gzrewind(file);
          if ((int)uVar2 < 0) {
            return 0xffffffff;
          }
        }
        else {
          offset = offset - file[5];
        }
        if (offset != 0) {
          if (file[0x12] == 0) {
            puVar3 = malloc(0x4000);
            file[0x12] = puVar3;
          }
          for (; 0 < (int)offset; offset = offset - iVar4) {
            uVar2 = 0x4000;
            if ((int)offset < 0x4000) {
              uVar2 = offset;
            }
            iVar4 = gzread(file,file[0x12],uVar2);
            if (iVar4 < 1) {
              return 0xffffffff;
            }
          }
        }
        return file[5];
      }
    }
  }
  return 0xffffffff;
}

/* ---- 0x004c48a0  gzrewind ---- */
uint __cdecl gzrewind(undefined4 *file)

{
  uint uVar1;
  
  if ((file != (undefined4 *)0x0) && (*(char *)(file + 0x17) == 'r')) {
    file[0xe] = 0;
    file[0xf] = 0;
    file[1] = 0;
    *file = file[0x11];
    uVar1 = crc32(0,(byte *)0x0,0);
    file[0x13] = uVar1;
    if (file[0x18] == 0) {
      rewind(file[0x10]);
      return 0;
    }
    inflateReset((int)file);
    uVar1 = (*(code *)g_pZf_filio_services[5])(file[0x10],file[0x18],0);
    return uVar1;
  }
  return 0xffffffff;
}

/* ---- 0x004c4920  gz_getLong ---- */
int __cdecl gz_getLong(int s)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar1 = gz_get_byte((undefined4 *)s);
  uVar2 = gz_get_byte((undefined4 *)s);
  uVar3 = gz_get_byte((undefined4 *)s);
  uVar4 = gz_get_byte((undefined4 *)s);
  if (uVar4 == 0xffffffff) {
    *(undefined4 *)(s + 0x38) = 0xfffffffd;
  }
  return uVar4 * 0x1000000 + uVar1 + uVar2 * 0x100 + uVar3 * 0x10000;
}

/* ---- 0x004c4970  gzclose ---- */
uint __cdecl gzclose(int file)

{
  uint uVar1;
  
  if (file == 0) {
    return 0xfffffffe;
  }
  if (*(char *)(file + 0x5c) == 'w') {
    uVar1 = gz_do_flush(file,4);
    if (uVar1 == 0) {
      gz_putLong(*(void **)(file + 0x40),*(uint *)(file + 0x4c));
      gz_putLong(*(void **)(file + 0x40),*(uint *)(file + 8));
    }
  }
  uVar1 = gz_destroy(file);
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



/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern unsigned int grim_def_UINT_004f1a00 __asm__("_UINT_004f1a00");
extern unsigned int grim_def_UINT_004f1a04 __asm__("_UINT_004f1a04");
extern char grim_def_s_1_1_3_004f1a20[8] __asm__("_s_1_1_3_004f1a20");
extern char grim_def_s_Too_many_zfilio_extension_set_004f1d3c[32] __asm__("_s_Too_many_zfilio_extension_set_004f1d3c");
extern char grim_def_s__c_c_c_c_c_c_c_c_c_c_004f1a08[24] __asm__("_s__c_c_c_c_c_c_c_c_c_c_004f1a08");
static unsigned char grim_anchor_004f1a00[0] __attribute__((section(".data$grim_004f1a00"), aligned(16), used));
static unsigned char grim_pad_004f1a00[0] __attribute__((section(".data$grim_004f1a00_"), aligned(4), used));
/* 0x004f1a00, 4 bytes */ GRIM_DATA("004f1a00z") unsigned int grim_def_UINT_004f1a00 __asm__("_UINT_004f1a00") = 0x1f;
/* 0x004f1a04, 4 bytes */ GRIM_DATA("004f1a04") unsigned int grim_def_UINT_004f1a04 __asm__("_UINT_004f1a04") = 0x8b;
/* 0x004f1a08, 24 bytes */ GRIM_DATA("004f1a08") char grim_def_s__c_c_c_c_c_c_c_c_c_c_004f1a08[24] __asm__("_s__c_c_c_c_c_c_c_c_c_c_004f1a08") = "%c%c%c%c%c%c%c%c%c%c";
/* 0x004f1a20, 8 bytes */ /* loose */ char grim_def_s_1_1_3_004f1a20[8] __asm__("_s_1_1_3_004f1a20") = "1.1.3";
/* 0x004f1d3c, 32 bytes */ /* loose */ char grim_def_s_Too_many_zfilio_extension_set_004f1d3c[32] __asm__("_s_Too_many_zfilio_extension_set_004f1d3c") = "Too many zfilio extension set";
