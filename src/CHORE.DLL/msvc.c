/* CHORE.DLL :: msvc.c
 * functions 0x100055a0 .. 0x10008520 (15 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x100055a0  msvc_strncpy ---- */
/* NOT COMPILED: names/lib_replace.json (host): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* MSVC 6 C runtime strncpy, CHORE.DLL's private copy; not compiled: build/link.py binds it to the
   system strncpy (names/lib_replace.json host + aliases). The msvc_ prefix marks CHORE.DLL's
   private runtime copies (a plain strncpy would bind the callers to the host's own definition,
   mingw's for sscanf, and the rebuilt chore.dll would export it). */

uint * msvc_strncpy(uint *param_1,uint *param_2,uint param_3)

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
        goto joined_r0x100055de;
      }
    }
    do {
      if (((uint)puVar5 & 3) == 0) {
        uVar4 = param_3 >> 2;
        cVar3 = '\0';
        if (uVar4 == 0) goto LAB_1000561b;
        goto LAB_10005689;
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
joined_r0x10005685:
          while( true ) {
            uVar4 = uVar4 - 1;
            puVar5 = puVar5 + 1;
            if (uVar4 == 0) break;
LAB_10005689:
            *puVar5 = 0;
          }
          cVar3 = '\0';
          param_3 = param_3 & 3;
          if (param_3 != 0) goto LAB_1000561b;
          return param_1;
        }
        if ((char)(uVar2 >> 8) == '\0') {
          *puVar5 = uVar2 & 0xff;
          goto joined_r0x10005685;
        }
        if ((uVar2 & 0xff0000) == 0) {
          *puVar5 = uVar2 & 0xffff;
          goto joined_r0x10005685;
        }
        if ((uVar2 & 0xff000000) == 0) {
          *puVar5 = uVar2;
          goto joined_r0x10005685;
        }
      }
      *puVar5 = uVar2;
      puVar5 = puVar5 + 1;
      uVar4 = uVar4 - 1;
joined_r0x100055de:
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
LAB_1000561b:
        *(char *)puVar5 = cVar3;
        puVar5 = (uint *)((int)puVar5 + 1);
      }
      return param_1;
    }
    param_3 = param_3 - 1;
  } while (param_3 != 0);
  return param_1;
}
#endif


/* ---- 0x100056a0  msvc_strrchr ---- */
/* NOT COMPILED: names/lib_replace.json (host): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* MSVC 6 C runtime strrchr, CHORE.DLL's private copy; not compiled: build/link.py binds it to the
   system strrchr (names/lib_replace.json host + aliases). The msvc_ prefix marks CHORE.DLL's
   private runtime copies (a plain strrchr would bind the callers to the host's own definition,
   mingw's for sscanf, and the rebuilt chore.dll would export it). */

char * msvc_strrchr(char *param_1,char param_2)

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
#endif


/* ---- 0x100056d0  msvc_fpmath ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* MSVC 6 C runtime _fpmath (fpinit.c), CHORE.DLL's private copy: msvc_cfltcvt_init, _adjust_fdiv =
   _ms_p5_mp_test_fdiv(), _setdefaultprecision. Reached only from the original start-up code. */

void msvc_fpmath(void)

{
  msvc_cfltcvt_init();
  _DAT_100143f8 = FUN_100061d0();
  FUN_10006160();
  return;
}

/* ---- 0x100056f0  msvc_fpclear ---- */
/* MSVC 6 C runtime _fpclear (fpinit.c), private copy: empty on x86. Not referenced. */

void msvc_fpclear(void)

{
  return;
}

/* ---- 0x10005700  msvc_cfltcvt_init ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* MSVC 6 C runtime _cfltcvt_init (fpinit.c), private copy: fills the floating-point conversion
   table (_cfltcvt, _cropzeros, _fassign, _forcdecpt, _positive) that printf / scanf use. */

void msvc_cfltcvt_init(void)

{
  _DAT_100106cc = FUN_10006260;
  _DAT_100106c8 = FUN_100066c0;
  _DAT_100106d0 = FUN_100062f0;
  _DAT_100106d4 = FUN_10006200;
  _DAT_100106d8 = FUN_100062d0;
  _DAT_100106dc = FUN_100066c0;
  return;
}

/* ---- 0x10005740  msvc_stricmp ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* MSVC 6 C runtime _stricmp, CHORE.DLL's private copy (returns -1 / 0 / 1). The msvc_ prefix keeps
   it out of crt.c (a named C runtime function there is served by the host runtime and not linked)
   and keeps the rebuilt chore.dll, which exports every symbol, from exporting an _stricmp the EXE
   would bind to. Hand-written in build/overrides.c (the host _stricmp, sign only). */

int __cdecl msvc_stricmp(byte *a,byte *b)

{
  bool bVar1;
  uint uVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  char cVar6;
  uint uVar8;
  int iVar7;
  
  iVar7 = _DAT_10015af0;
  if (_DAT_10014478 == 0) {
    bVar5 = 0xff;
    do {
      do {
        cVar6 = '\0';
        if (bVar5 == 0) goto LAB_1000578e;
        bVar5 = *b;
        b = b + 1;
        bVar4 = *a;
        a = a + 1;
      } while (bVar4 == bVar5);
      bVar3 = bVar5 + 0xbf + (-((byte)(bVar5 + 0xbf) < 0x1a) & 0x20U) + 0x41;
      bVar4 = bVar4 + 0xbf;
      bVar5 = bVar4 + (-(bVar4 < 0x1a) & 0x20U) + 0x41;
    } while (bVar5 == bVar3);
    cVar6 = (bVar5 < bVar3) * -2 + '\x01';
LAB_1000578e:
    iVar7 = (int)cVar6;
  }
  else {
    LOCK();
    _DAT_10015af0 = _DAT_10015af0 + 1;
    UNLOCK();
    bVar1 = 0 < _DAT_10015aec;
    if (bVar1) {
      LOCK();
      UNLOCK();
      _DAT_10015af0 = iVar7;
      FUN_10006810(0x13);
    }
    uVar8 = (uint)bVar1;
    iVar7 = 0xff;
    do {
      do {
        if ((char)iVar7 == '\0') goto LAB_100057ef;
        bVar5 = *b;
        iVar7 = CONCAT31((int3)((uint)iVar7 >> 8),bVar5);
        b = b + 1;
        bVar4 = *a;
        a = a + 1;
      } while (bVar5 == bVar4);
      bVar5 = ((code *)FUN_10006a30)(bVar4,iVar7);
      iVar7 = ((code *)FUN_10006a30)();
    } while (bVar5 == (byte)iVar7);
    uVar2 = (uint)(bVar5 < (byte)iVar7);
    iVar7 = (1 - uVar2) - (uint)(uVar2 != 0);
LAB_100057ef:
    if (uVar8 == 0) {
      LOCK();
      _DAT_10015af0 = _DAT_10015af0 + -1;
      UNLOCK();
    }
    else {
      FUN_10006890();
    }
  }
  return iVar7;
}
#endif


/* ---- 0x10005810  msvc_sscanf ---- */
/* NOT COMPILED: names/lib_replace.json (host): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* MSVC 6 C runtime sscanf, CHORE.DLL's private copy; not compiled: build/link.py binds it to the
   system sscanf (names/lib_replace.json host + aliases). The msvc_ prefix marks CHORE.DLL's private
   runtime copies (a plain sscanf would bind the callers to the host's own definition, mingw's for
   sscanf, and the rebuilt chore.dll would export it). */

int __cdecl msvc_sscanf(char *param_1,char *param_2,...)

{
  unsigned char _frame[0x30];  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  uint uVar3;
  #define pcStack_20 (*(char **)(_frame + (0x30 - 0x20)))
  #define iStack_1c (*(int *)(_frame + (0x30 - 0x1c)))
  #define pcStack_18 (*(char **)(_frame + (0x30 - 0x18)))
  #define uStack_14 (*(undefined4 *)(_frame + (0x30 - 0x14)))
  
  uVar3 = 0xffffffff;
  pcStack_18 = param_1;
  pcStack_20 = param_1;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *param_1;
    param_1 = param_1 + 1;
  } while (cVar1 != '\0');
  iStack_1c = ~uVar3 - 1;
  uStack_14 = 0x49;
  iVar2 = FUN_10006b30(&pcStack_20,param_2,&STACK0X(0x0000000c));
  return iVar2;
}
#undef iStack_1c
#undef pcStack_18
#undef pcStack_20
#undef uStack_14

#endif


/* ---- 0x10005860  msvc_memmove ---- */
/* NOT COMPILED: names/lib_replace.json (host): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* MSVC 6 C runtime memmove, CHORE.DLL's private copy; not compiled: build/link.py binds it to the
   system memmove (names/lib_replace.json host + aliases). The msvc_ prefix marks CHORE.DLL's
   private runtime copies (a plain memmove would bind the callers to the host's own definition,
   mingw's for sscanf, and the rebuilt chore.dll would export it). */

undefined4 * msvc_memmove(undefined4 *param_1,undefined4 *param_2,uint param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  
  if ((param_2 < param_1) && (param_1 < (undefined4 *)(param_3 + (int)param_2))) {
    param_2 = (undefined4 *)((param_3 - 4) + (int)param_2);
    puVar2 = (undefined4 *)((param_3 - 4) + (int)param_1);
    if (((uint)puVar2 & 3) == 0) {
      uVar1 = param_3 >> 2;
      param_3 = param_3 & 3;
      if (7 < uVar1) {
        for (; uVar1 != 0; uVar1 = uVar1 - 1) {
          *puVar2 = *param_2;
          param_2 = param_2 + -1;
          puVar2 = puVar2 + -1;
        }
        switch(param_3) {
        case 0:
          return param_1;
        case 2:
          goto code_r0x10005b68;
        case 3:
          goto code_r0x10005b7c;
        }
        goto code_r0x10005b58;
      }
    }
    else {
      switch(param_3) {
      case 0:
        goto code_r0x10005b50;
      case 1:
        goto code_r0x10005b58;
      case 2:
        goto code_r0x10005b68;
      case 3:
        goto code_r0x10005b7c;
      default:
        uVar1 = param_3 - ((uint)puVar2 & 3);
        switch((uint)puVar2 & 3) {
        case 1:
          param_3 = uVar1 & 3;
          *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
          param_2 = (undefined4 *)((int)param_2 + -1);
          uVar1 = uVar1 >> 2;
          puVar2 = (undefined4 *)((int)puVar2 - 1);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar2 = *param_2;
              param_2 = param_2 + -1;
              puVar2 = puVar2 + -1;
            }
            switch(param_3) {
            case 0:
              return param_1;
            case 2:
              goto code_r0x10005b68;
            case 3:
              goto code_r0x10005b7c;
            }
            goto code_r0x10005b58;
          }
          break;
        case 2:
          param_3 = uVar1 & 3;
          *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
          uVar1 = uVar1 >> 2;
          *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
          param_2 = (undefined4 *)((int)param_2 + -2);
          puVar2 = (undefined4 *)((int)puVar2 - 2);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar2 = *param_2;
              param_2 = param_2 + -1;
              puVar2 = puVar2 + -1;
            }
            switch(param_3) {
            case 0:
              return param_1;
            case 2:
              goto code_r0x10005b68;
            case 3:
              goto code_r0x10005b7c;
            }
            goto code_r0x10005b58;
          }
          break;
        case 3:
          param_3 = uVar1 & 3;
          *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
          *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
          uVar1 = uVar1 >> 2;
          *(undefined1 *)((int)puVar2 + 1) = *(undefined1 *)((int)param_2 + 1);
          param_2 = (undefined4 *)((int)param_2 + -3);
          puVar2 = (undefined4 *)((int)puVar2 - 3);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar2 = *param_2;
              param_2 = param_2 + -1;
              puVar2 = puVar2 + -1;
            }
            switch(param_3) {
            case 0:
              return param_1;
            case 2:
              goto code_r0x10005b68;
            case 3:
              goto code_r0x10005b7c;
            }
            goto code_r0x10005b58;
          }
        }
      }
    }
    switch(uVar1) {
    case 7:
      puVar2[7 - uVar1] = param_2[7 - uVar1];
    case 6:
      puVar2[6 - uVar1] = param_2[6 - uVar1];
    case 5:
      puVar2[5 - uVar1] = param_2[5 - uVar1];
    case 4:
      puVar2[4 - uVar1] = param_2[4 - uVar1];
    case 3:
      puVar2[3 - uVar1] = param_2[3 - uVar1];
    case 2:
      puVar2[2 - uVar1] = param_2[2 - uVar1];
    case 1:
      puVar2[1 - uVar1] = param_2[1 - uVar1];
      param_2 = param_2 + -uVar1;
      puVar2 = puVar2 + -uVar1;
    }
    switch(param_3) {
    case 1:
code_r0x10005b58:
      *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
      return param_1;
    case 2:
code_r0x10005b68:
      *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
      *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
      return param_1;
    case 3:
code_r0x10005b7c:
      *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
      *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
      *(undefined1 *)((int)puVar2 + 1) = *(undefined1 *)((int)param_2 + 1);
      return param_1;
    }
code_r0x10005b50:
    return param_1;
  }
  puVar2 = param_1;
  if (((uint)param_1 & 3) == 0) {
    uVar1 = param_3 >> 2;
    param_3 = param_3 & 3;
    if (7 < uVar1) {
      for (; uVar1 != 0; uVar1 = uVar1 - 1) {
        *puVar2 = *param_2;
        param_2 = param_2 + 1;
        puVar2 = puVar2 + 1;
      }
      switch(param_3) {
      case 0:
        return param_1;
      case 2:
        goto code_r0x100059cc;
      case 3:
        goto code_r0x100059e0;
      }
      goto code_r0x100059c0;
    }
  }
  else {
    switch(param_3) {
    case 0:
      goto code_r0x100059b8;
    case 1:
      goto code_r0x100059c0;
    case 2:
      goto code_r0x100059cc;
    case 3:
      goto code_r0x100059e0;
    default:
      uVar1 = (param_3 - 4) + ((uint)param_1 & 3);
      switch((uint)param_1 & 3) {
      case 1:
        param_3 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        *(undefined1 *)((int)param_1 + 1) = *(undefined1 *)((int)param_2 + 1);
        uVar1 = uVar1 >> 2;
        *(undefined1 *)((int)param_1 + 2) = *(undefined1 *)((int)param_2 + 2);
        param_2 = (undefined4 *)((int)param_2 + 3);
        puVar2 = (undefined4 *)((int)param_1 + 3);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar2 = *param_2;
            param_2 = param_2 + 1;
            puVar2 = puVar2 + 1;
          }
          switch(param_3) {
          case 0:
            return param_1;
          case 2:
            goto code_r0x100059cc;
          case 3:
            goto code_r0x100059e0;
          }
          goto code_r0x100059c0;
        }
        break;
      case 2:
        param_3 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        uVar1 = uVar1 >> 2;
        *(undefined1 *)((int)param_1 + 1) = *(undefined1 *)((int)param_2 + 1);
        param_2 = (undefined4 *)((int)param_2 + 2);
        puVar2 = (undefined4 *)((int)param_1 + 2);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar2 = *param_2;
            param_2 = param_2 + 1;
            puVar2 = puVar2 + 1;
          }
          switch(param_3) {
          case 0:
            return param_1;
          case 2:
            goto code_r0x100059cc;
          case 3:
            goto code_r0x100059e0;
          }
          goto code_r0x100059c0;
        }
        break;
      case 3:
        param_3 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        param_2 = (undefined4 *)((int)param_2 + 1);
        uVar1 = uVar1 >> 2;
        puVar2 = (undefined4 *)((int)param_1 + 1);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar2 = *param_2;
            param_2 = param_2 + 1;
            puVar2 = puVar2 + 1;
          }
          switch(param_3) {
          case 0:
            return param_1;
          case 2:
            goto code_r0x100059cc;
          case 3:
            goto code_r0x100059e0;
          }
          goto code_r0x100059c0;
        }
      }
    }
  }
  switch(uVar1) {
  case 7:
    puVar2[uVar1 - 7] = param_2[uVar1 - 7];
  case 6:
    puVar2[uVar1 - 6] = param_2[uVar1 - 6];
  case 5:
    puVar2[uVar1 - 5] = param_2[uVar1 - 5];
  case 4:
    puVar2[uVar1 - 4] = param_2[uVar1 - 4];
  case 3:
    puVar2[uVar1 - 3] = param_2[uVar1 - 3];
  case 2:
    puVar2[uVar1 - 2] = param_2[uVar1 - 2];
  case 1:
    puVar2[uVar1 - 1] = param_2[uVar1 - 1];
    param_2 = param_2 + uVar1;
    puVar2 = puVar2 + uVar1;
  }
  switch(param_3) {
  case 1:
code_r0x100059c0:
    *(undefined1 *)puVar2 = *(undefined1 *)param_2;
    return param_1;
  case 2:
code_r0x100059cc:
    *(undefined1 *)puVar2 = *(undefined1 *)param_2;
    *(undefined1 *)((int)puVar2 + 1) = *(undefined1 *)((int)param_2 + 1);
    return param_1;
  case 3:
code_r0x100059e0:
    *(undefined1 *)puVar2 = *(undefined1 *)param_2;
    *(undefined1 *)((int)puVar2 + 1) = *(undefined1 *)((int)param_2 + 1);
    *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
    return param_1;
  }
code_r0x100059b8:
  return param_1;
}
#endif


/* ---- 0x10005ba0  msvc_qsort ---- */
/* MSVC 6 C runtime qsort, CHORE.DLL's private copy, still compiled (Cos_AddKey sorts the keys of a
   track with it). The msvc_ prefix keeps it out of crt.c (named C runtime functions there are
   served by the host runtime and not linked) and keeps the rebuilt chore.dll, which exports every
   symbol, from exporting a qsort that the EXE would bind to. */

void msvc_qsort(uint param_1,uint param_2,uint param_3,code *param_4)

{
  unsigned char _frame[0x110] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  int iVar2;
  uint uVar3;
  #define uStack_100 (*(uint *)(_frame + (0x110 - 0x100)))
  #define puStack_fc (*(uint **)(_frame + (0x110 - 0xfc)))
  #define puStack_f8 (*(uint **)(_frame + (0x110 - 0xf8)))
  #define iStack_f4 (*(int *)(_frame + (0x110 - 0xf4)))
  #define auStack_f0 (*(uint (*)[30])(_frame + (0x110 - 0xf0)))
  #define auStack_78 (*(uint (*)[30])(_frame + (0x110 - 0x78)))
  
  if ((param_2 < 2) || (param_3 == 0)) {
    return;
  }
  uStack_100 = (param_2 - 1) * param_3 + param_1;
  puStack_fc = auStack_f0;
  puStack_f8 = auStack_78;
  iStack_f4 = 0;
LAB_10005bf4:
  uVar1 = (uStack_100 - param_1) / param_3 + 1;
  if (8 < uVar1) {
    msvc_qsort_swap((uVar1 >> 1) * param_3 + param_1,param_1,param_3);
    uVar3 = uStack_100 + param_3;
    uVar1 = param_1;
LAB_10005c6e:
    uVar1 = uVar1 + param_3;
    if (uVar1 <= uStack_100) goto code_r0x10005c78;
    goto LAB_10005c88;
  }
  msvc_shortsort(param_1,uStack_100,param_3,param_4);
  goto LAB_10005c15;
code_r0x10005c78:
  iVar2 = (*param_4)(uVar1,param_1);
  if (iVar2 < 1) goto LAB_10005c6e;
LAB_10005c88:
  do {
    uVar3 = uVar3 - param_3;
    if (uVar3 <= param_1) break;
    iVar2 = (*param_4)(uVar3,param_1);
  } while (-1 < iVar2);
  if (uVar1 <= uVar3) {
    msvc_qsort_swap(uVar1,uVar3,param_3);
    goto LAB_10005c6e;
  }
  msvc_qsort_swap(param_1,uVar3,param_3);
  if ((int)((uVar3 - param_1) + -1) < (int)(uStack_100 - uVar1)) {
    if (uVar1 < uStack_100) {
      *puStack_f8 = uVar1;
      *puStack_fc = uStack_100;
      iStack_f4 = iStack_f4 + 1;
      puStack_f8 = puStack_f8 + 1;
      puStack_fc = puStack_fc + 1;
    }
    if (param_1 + param_3 < uVar3) {
      uStack_100 = uVar3 - param_3;
      goto LAB_10005bf4;
    }
  }
  else {
    if (param_1 + param_3 < uVar3) {
      *puStack_f8 = param_1;
      *puStack_fc = uVar3 - param_3;
      iStack_f4 = iStack_f4 + 1;
      puStack_f8 = puStack_f8 + 1;
      puStack_fc = puStack_fc + 1;
    }
    param_1 = uVar1;
    if (uVar1 < uStack_100) goto LAB_10005bf4;
  }
LAB_10005c15:
  iStack_f4 = iStack_f4 + -1;
  puStack_f8 = puStack_f8 + -1;
  puStack_fc = puStack_fc + -1;
  if (iStack_f4 < 0) {
    return;
  }
  uStack_100 = *puStack_fc;
  param_1 = *puStack_f8;
  goto LAB_10005bf4;
}
#undef auStack_78
#undef auStack_f0
#undef iStack_f4
#undef puStack_f8
#undef puStack_fc
#undef uStack_100


/* ---- 0x10005d50  msvc_shortsort ---- */
/* MSVC 6 C runtime (qsort.c, static shortsort): selection sort of a short range for msvc_qsort */

void msvc_shortsort(uint param_1,uint param_2,int param_3,code *param_4)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  for (; uVar2 = param_1, uVar1 = param_1, param_1 < param_2; param_2 = param_2 - param_3) {
    while (uVar1 = param_3 + uVar1, uVar1 <= param_2) {
      iVar3 = (*param_4)(uVar1,uVar2);
      if (0 < iVar3) {
        uVar2 = uVar1;
      }
    }
    msvc_qsort_swap(uVar2,param_2,param_3);
  }
  return;
}

/* ---- 0x10005db0  msvc_qsort_swap ---- */
/* MSVC 6 C runtime (qsort.c, static swap): exchanges two elements byte by byte for msvc_qsort */

void msvc_qsort_swap(undefined1 *param_1,undefined1 *param_2,int param_3)

{
  undefined1 uVar1;
  
  if (param_1 != param_2) {
    for (; param_3 != 0; param_3 = param_3 + -1) {
      uVar1 = *param_1;
      *param_1 = *param_2;
      param_1 = param_1 + 1;
      *param_2 = uVar1;
      param_2 = param_2 + 1;
    }
  }
  return;
}

/* ---- 0x10005de0  msvc_bsearch ---- */
/* NOT COMPILED: names/lib_replace.json (host): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* MSVC 6 C runtime bsearch, CHORE.DLL's private copy; not compiled: build/link.py binds it to the
   system bsearch (names/lib_replace.json host + aliases). The msvc_ prefix marks CHORE.DLL's
   private runtime copies (a plain bsearch would bind the callers to the host's own definition,
   mingw's for sscanf, and the rebuilt chore.dll would export it). */

uint msvc_bsearch(undefined4 param_1,uint param_2,uint param_3,int param_4,code *param_5)

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
      iVar2 = (*param_5)(param_1,uVar5);
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
      iVar2 = (*param_5)(param_1,uVar4);
      return ~-(uint)(iVar2 != 0) & uVar4;
    }
  }
  return 0;
}
#endif


/* ---- 0x10005e90  msvc_strchr ---- */
/* NOT COMPILED: names/lib_replace.json (host): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* MSVC 6 C runtime strchr, CHORE.DLL's private copy; not compiled: build/link.py binds it to the
   system strchr (names/lib_replace.json host + aliases). The msvc_ prefix marks CHORE.DLL's private
   runtime copies (a plain strchr would bind the callers to the host's own definition, mingw's for
   sscanf, and the rebuilt chore.dll would export it). */

uint * msvc_strchr(uint *param_1,char param_2)

{
  uint uVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  
  while (((uint)param_1 & 3) != 0) {
    uVar1 = *param_1;
    if ((char)uVar1 == param_2) {
      return param_1;
    }
    param_1 = (uint *)((int)param_1 + 1);
    if ((char)uVar1 == '\0') {
      return (uint *)0x0;
    }
  }
  while( true ) {
    while( true ) {
      uVar1 = *param_1;
      uVar4 = uVar1 ^ CONCAT22(CONCAT11(param_2,param_2),CONCAT11(param_2,param_2));
      uVar3 = uVar1 ^ 0xffffffff ^ uVar1 + 0x7efefeff;
      puVar5 = param_1 + 1;
      if (((uVar4 ^ 0xffffffff ^ uVar4 + 0x7efefeff) & 0x81010100) != 0) break;
      param_1 = puVar5;
      if ((uVar3 & 0x81010100) != 0) {
        if ((uVar3 & 0x1010100) != 0) {
          return (uint *)0x0;
        }
        if ((uVar1 + 0x7efefeff & 0x80000000) == 0) {
          return (uint *)0x0;
        }
      }
    }
    uVar1 = *param_1;
    if ((char)uVar1 == param_2) {
      return param_1;
    }
    if ((char)uVar1 == '\0') {
      return (uint *)0x0;
    }
    cVar2 = (char)(uVar1 >> 8);
    if (cVar2 == param_2) {
      return (uint *)((int)param_1 + 1);
    }
    if (cVar2 == '\0') {
      return (uint *)0x0;
    }
    cVar2 = (char)(uVar1 >> 0x10);
    if (cVar2 == param_2) {
      return (uint *)((int)param_1 + 2);
    }
    if (cVar2 == '\0') break;
    cVar2 = (char)(uVar1 >> 0x18);
    if (cVar2 == param_2) {
      return (uint *)((int)param_1 + 3);
    }
    param_1 = puVar5;
    if (cVar2 == '\0') {
      return (uint *)0x0;
    }
  }
  return (uint *)0x0;
}
#endif


/* ---- 0x10005f50  FUN_10005f50 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __stdcall FUN_10005f50(int a1,int a2,int a3)

{
  int iVar1;
  
  if (a2 != 1) {
    if (a2 != 0) {
      if (a2 == 3) {
        FUN_10007be0(0);
      }
      return 1;
    }
    if (0 < _DAT_100143fc) {
      _DAT_100143fc = _DAT_100143fc + -1;
      if (_DAT_100144d4 == 0) {
        FUN_100079a0();
      }
      FUN_10007ea0();
      FUN_10007b10();
      FUN_10008950();
      return 1;
    }
    return 0;
  }
  _DAT_1001449c = GetVersion();
  iVar1 = FUN_10008910();
  if (iVar1 == 0) {
    return 0;
  }
  _DAT_100144a8 = _DAT_1001449c >> 8 & 0xff;
  _DAT_100144a4 = _DAT_1001449c & 0xff;
  _DAT_100144a0 = _DAT_100144a4 * 0x100 + _DAT_100144a8;
  _DAT_1001449c = _DAT_1001449c >> 0x10;
  iVar1 = FUN_10007ab0();
  if (iVar1 == 0) {
    FUN_10008950();
    return 0;
  }
  _DAT_10015af4 = GetCommandLineA();
  _DAT_10014400 = FUN_100087b0();
  if ((_DAT_10015af4 != 0) && (_DAT_10014400 != 0)) {
    FUN_10007c90();
    FUN_100087a0();
    FUN_10007ff0();
    FUN_10007f00();
    FUN_10007950();
    _DAT_100143fc = _DAT_100143fc + 1;
    return 1;
  }
  FUN_10007b10();
  FUN_10008950();
  return 0;
}
#endif


/* ---- 0x10008520  msvc_CPtoLCID ---- */
/* MSVC 6 C runtime CPtoLCID (mbctype.c, static), private copy: code page -> locale id for the four
   multibyte code pages (932, 936, 949, 950). Reached only from _setmbcp, which no live code calls.
    */

undefined4 msvc_CPtoLCID(undefined4 param_1)

{
  switch(param_1) {
  case 0x3a4:
    return 0x411;
  default:
    return 0;
  case 0x3a8:
    return 0x804;
  case 0x3b5:
    return 0x412;
  case 0x3b6:
    return 0x404;
  }
}
