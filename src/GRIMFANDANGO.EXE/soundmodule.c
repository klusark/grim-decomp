/* GRIMFANDANGO.EXE :: soundmodule.c
 * functions 0x004d0300 .. 0x004d2340 (29 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004d0300  SoundModule_Register ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Entry of LECMODULE insane_sound: the Smush sound track manager (SOUND insane) */

int __cdecl SoundModule_Register(int *services,uint moduleSize)

{
  bool bVar1;
  uint *puVar2;
  uint *puVar3;
  int iVar4;
  
  PTR_008dacf8 = services;
  UINT_008db098 = moduleSize;
  (*(code *)*services)(s_LECMODULE_insane_sound_004f3e5c,&g_apfnSoundModule);
  (*(code *)*PTR_008dacf8)(s_SOUND_insane_004f3e4c,&g_apfnSoundInterface);
  iVar4 = 0;
  PTR_008dacf0 = (int *)0x0;
  UINT_008db09c = 0x5622;
  UINT_008dacfc = 64000;
  _DAT_008db1e8 = 0;
  UINT_008dad50 = 0;
  UINT_008dacf4 = 0;
  UINT_008db0a0 = 0;
  puVar2 = &UINT_008dacb0;
  do {
    bVar1 = 0 < iVar4;
    puVar3 = puVar2 + 1;
    iVar4 = iVar4 + 1;
    *puVar2 = bVar1 - 1 & 100000;
    puVar2 = puVar3;
  } while ((int)puVar3 < IMG_ADDR(0x008dacf0));
  UINT_008dacb0 = 500000;
  return 0;
}
#endif


/* ---- 0x004d03a0  SoundModule_Unregister ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SoundModule_Unregister(void)

{
  (*(code *)PTR_008dacf8[1])(s_SOUND_insane_004f3e4c);
  (*(code *)PTR_008dacf8[1])(s_LECMODULE_insane_sound_004f3e5c);
  return;
}
#endif


/* ---- 0x004d03d0  SoundModule_Init ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SoundModule_Init(void)

{
  uint uVar1;
  int iVar2;
  
  PTR_008da8a8 = (int *)(*(code *)PTR_008dacf8[2])(s_MEMORY_workspace_004f14ec,UINT_008db098);
  UINT_008dad48 = (*(code *)PTR_008dacf8[2])(s_TIMER_external_sync_004f3f1c,UINT_008db098);
  uVar1 = UINT_008db0a0;
  if (UINT_008db0a0 == 0) {
    uVar1 = UINT_008db098;
  }
  PTR_008dacf0 = (int *)(*(code *)PTR_008dacf8[2])(s_SNDDRIVER_driver_004f3f08,uVar1);
  if (PTR_008da8a8 == (int *)0x0) {
    (*(code *)PTR_008dacf8[8])(s_Sound_Module__Cannot_allocate_me_004f3ed8);
    return -1;
  }
  if (UINT_008dad48 == 0) {
    (*(code *)PTR_008dacf8[8])(s_Sound_Module__Cannot_allocate_ti_004f3ea8);
    return -1;
  }
  if (PTR_008dacf0 == (int *)0x0) {
    (*(code *)PTR_008dacf8[8])(s_Sound_Module__Cannot_allocate_sn_004f3e74);
    return -1;
  }
  iVar2 = SoundModule_Open(UINT_008db09c,UINT_008dacfc,UINT_008dacb0,UINT_008dacb4,UINT_008dacb8,
                           UINT_008dacbc,UINT_008dacc0,UINT_008dacc4,UINT_008dacc8,UINT_008daccc,
                           UINT_008dacd0,UINT_008dacd4,UINT_008dacd8,UINT_008dacdc,UINT_008dace0,
                           UINT_008dace4,UINT_008dace8,UINT_008dacec,0);
  return iVar2;
}
#endif


/* ---- 0x004d0510  SoundModule_Shutdown ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SoundModule_Shutdown(void)

{
  (*(code *)PTR_008dacf8[3])(PTR_008da8a8);
  (*(code *)PTR_008dacf8[3])(PTR_008dacf0);
  (*(code *)PTR_008dacf8[3])(UINT_008dad48);
  SoundModule_Close();
  return;
}
#endif


/* ---- 0x004d0550  SoundModule_Open ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Zero-terminated list of track buffer sizes follows the three fixed arguments */

int __cdecl SoundModule_Open(int rate,int limit,uint size,...)

{
  int iVar1;
  uint *puVar2;
  
  UINT_004f3e30 = 0;
  UINT_004f3e34 = 0x7f;
  iVar1 = 0;
  do {
    (&DAT_008db0e8)[iVar1] = 0;
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x100);
  puVar2 = (uint *)&STACK0X(0x00000010);
  while( true ) {
    if (size == 0) {
      iVar1 = (*(code *)*PTR_008dacf0)(rate,UINT_004f3e30,SoundModule_MixCallback);
      UINT_008db1f0 = (uint)(iVar1 == 0);
      UINT_004f3e38 = (*(code *)PTR_008dacf0[5])();
      UINT_008dacf4 = 0;
      UINT_008dad40 = 1;
      UINT_008dad4c = 1;
      UINT_008dad44 = 1;
      (**(code **)(UINT_008dad48 + 0x20))(0);
      return 0;
    }
    iVar1 = SoundModule_AddTrackBuffer(size & 0xfffffffc,limit);
    if (iVar1 != 0) break;
    size = *puVar2;
    puVar2 = puVar2 + 1;
  }
  SoundModule_Close();
  return -1;
}
#endif


/* ---- 0x004d0610  SoundModule_Close ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SoundModule_Close(void)

{
  uint uVar1;
  uint *puVar2;
  int iVar3;
  
  if (UINT_008db1f0 != 0) {
    (*(code *)PTR_008dacf0[1])();
    UINT_008db1f0 = 0;
  }
  iVar3 = 0;
  if (0 < (int)UINT_004f3e30) {
    puVar2 = &UINT_008dad5c;
    do {
      if (puVar2[-1] != 0) {
        (*(code *)PTR_008da8a8[1])(puVar2[-1],s_C__grimsrc_libs_lecsmush_insane__004f3f30,0x1a8);
      }
      puVar2[-1] = 0;
      if (*puVar2 != 0) {
        (*(code *)PTR_008da8a8[1])(*puVar2,s_C__grimsrc_libs_lecsmush_insane__004f3f30,0x1a9);
      }
      uVar1 = UINT_004f3e30;
      *puVar2 = 0;
      iVar3 = iVar3 + 1;
      puVar2 = puVar2 + 0xd;
    } while (iVar3 < (int)uVar1);
  }
  UINT_004f3e30 = 0;
  return UINT_008dacf4;
}
#endif


/* ---- 0x004d06a0  SoundModule_AddTrackBuffer ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
int __cdecl SoundModule_AddTrackBuffer(uint size,int limit)

{
  uint uVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  piVar2 = PTR_008da8a8;
  uVar1 = UINT_004f3e30;
  iVar5 = UINT_004f3e30 * 0x34;
  (&DAT_008dad6e)[iVar5] = 0;
  (&UINT_008dad84)[uVar1 * 0xd] = 0;
  (&UINT_008dad70)[uVar1 * 0xd] = 0;
  (&UINT_008dad74)[uVar1 * 0xd] = 0xffffff01;
  (&UINT_008dad58)[uVar1 * 0xd] = 0;
  (&UINT_008dad5c)[uVar1 * 0xd] = 0;
  *(uint *)(iVar5 + IMG_ADDR(0x008dad68)) = size & 0xfffffffc;
  uVar3 = (*(code *)*piVar2)(0x1800,s_C__grimsrc_libs_lecsmush_insane__004f3f30,0x1cf);
  (&UINT_008dad5c)[uVar1 * 0xd] = uVar3;
  if (uVar3 == 0) {
    return -1;
  }
  uVar3 = (*(code *)*PTR_008da8a8)
                    (*(undefined4 *)(iVar5 + IMG_ADDR(0x008dad68)),s_C__grimsrc_libs_lecsmush_insane__004f3f30,
                     0x1d1);
  (&UINT_008dad58)[uVar1 * 0xd] = uVar3;
  if (uVar3 == 0) {
    iVar4 = *(int *)(iVar5 + IMG_ADDR(0x008dad68));
    while (limit < iVar4) {
      uVar3 = (*(code *)*PTR_008da8a8)
                        (*(undefined4 *)(iVar5 + IMG_ADDR(0x008dad68)),
                         s_C__grimsrc_libs_lecsmush_insane__004f3f30,0x1d7);
      (&UINT_008dad58)[uVar1 * 0xd] = uVar3;
      if (uVar3 != 0) break;
      iVar4 = *(int *)(iVar5 + IMG_ADDR(0x008dad68)) + -10000;
      *(int *)(iVar5 + IMG_ADDR(0x008dad68)) = iVar4;
    }
    uVar3 = *(uint *)(iVar5 + IMG_ADDR(0x008dad68)) & 0xfffffffc;
    *(uint *)(iVar5 + IMG_ADDR(0x008dad68)) = uVar3;
    if (limit < (int)uVar3) {
      if ((&UINT_008dad58)[uVar1 * 0xd] != 0) {
        (*(code *)PTR_008da8a8[1])
                  ((&UINT_008dad58)[uVar1 * 0xd],s_C__grimsrc_libs_lecsmush_insane__004f3f30,0x1e2);
      }
      (&UINT_008dad58)[uVar1 * 0xd] = 0;
      piVar2 = PTR_008da8a8;
      iVar4 = *(int *)(iVar5 + IMG_ADDR(0x008dad68)) - limit;
      *(int *)(iVar5 + IMG_ADDR(0x008dad68)) = iVar4;
      uVar3 = (*(code *)*piVar2)(iVar4,s_C__grimsrc_libs_lecsmush_insane__004f3f30,0x1e5);
      (&UINT_008dad58)[uVar1 * 0xd] = uVar3;
      if (uVar3 != 0) goto LAB_004d0827;
    }
    if ((&UINT_008dad5c)[uVar1 * 0xd] != 0) {
      (*(code *)PTR_008da8a8[1])
                ((&UINT_008dad5c)[uVar1 * 0xd],s_C__grimsrc_libs_lecsmush_insane__004f3f30,0x1ee);
    }
    (&UINT_008dad5c)[uVar1 * 0xd] = 0;
    return -2;
  }
LAB_004d0827:
  FUN_004d5e50((&UINT_008dad58)[uVar1 * 0xd],0x7f,*(undefined4 *)(iVar5 + IMG_ADDR(0x008dad68)));
  UINT_004f3e30 = UINT_004f3e30 + 1;
  return 0;
}
#endif


/* ---- 0x004d0860  SoundModule_PlayChunk ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Dispatches a sound chunk by its four-character tag: Crea(tive VOC), PSAD / SAUD (Smush audio) */

void __cdecl SoundModule_PlayChunk(byte *p,int id,int volume,int pan,uint flags)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  
  if (UINT_008db1f0 != 0) {
    uVar2 = CONCAT31(CONCAT21(CONCAT11(*p,p[1]),p[2]),p[3]);
    if (uVar2 < 0x50534145) {
      if (uVar2 != 0x50534144) {
        if (uVar2 != 0x43726561) {
          return;
        }
        iVar3 = (uint)p[0x15] * 0x100 + (uint)p[0x14];
        bVar1 = p[iVar3 + 1];
        SoundModule_PlayVoc(p + iVar3 + 6,(uint)CONCAT11(bVar1,bVar1) * 0x100 + (uint)bVar1,id,
                            volume,pan,flags);
        return;
      }
    }
    else if (uVar2 != 0x50564f43) {
      if (uVar2 != 0x53415544) {
        return;
      }
      SoundModule_PlaySaud
                (p,CONCAT31(CONCAT21(CONCAT11(p[4],p[5]),p[6]),p[7]) + 8,id,volume,pan,flags,0,0,1,0
                );
      return;
    }
    if ((((p[8] == 0) && (p[9] == 0)) && (p[0xc] == 0)) &&
       (((p[0xd] == 0 && (p[0x10] == 0)) && (p[0x11] == 0)))) {
      SoundModule_PlaySaud
                (p + 0x14,CONCAT31(CONCAT21(CONCAT11(p[4],p[5]),p[6]),p[7]) + -0xc,id,volume,pan,
                 flags,(uint)CONCAT11(p[10],p[0xb]),(uint)CONCAT11(p[0xe],p[0xf]),
                 (uint)CONCAT11(p[0x12],p[0x13]),1);
      return;
    }
    if ((char)p[0x11] < -0x7f) {
      iVar3 = 0x80;
    }
    else {
      iVar3 = pan + (char)p[0x11];
    }
    SoundModule_PlaySaud
              (p + 0x12,CONCAT31(CONCAT21(CONCAT11(p[4],p[5]),p[6]),p[7]) + -10,id,
               (int)((uint)p[0x10] * volume) >> 7,iVar3,(int)*(short *)(p + 0xe) | flags,
               (int)*(short *)(p + 8),(int)*(short *)(p + 10),(int)*(short *)(p + 0xc),1);
  }
  return;
}
#endif


/* ---- 0x004d0a50  SoundModule_StopSound ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void __cdecl SoundModule_StopSound(uint id)

{
  uint *puVar1;
  uint uVar2;
  
  if (0 < (int)UINT_004f3e30) {
    puVar1 = &UINT_008dad74;
    uVar2 = UINT_004f3e30;
    do {
      if (*puVar1 == id) {
        *(undefined1 *)((int)puVar1 + -6) = 0;
        *puVar1 = 0xffffff01;
      }
      puVar1 = puVar1 + 0xd;
      uVar2 = uVar2 - 1;
    } while (uVar2 != 0);
  }
  return;
}
#endif


/* ---- 0x004d0a80  SoundModule_Pause ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SoundModule_Pause(void)

{
  UINT_008db1ec = UINT_008db1ec + 1;
  return;
}
#endif


/* ---- 0x004d0a90  SoundModule_Resume ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SoundModule_Resume(void)

{
  if (UINT_008db1ec != 0) {
    UINT_008db1ec = UINT_008db1ec - 1;
  }
  return;
}
#endif


/* ---- 0x004d0aa0  SoundModule_StopAll ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SoundModule_StopAll(void)

{
  uint *puVar1;
  uint uVar2;
  
  if (0 < (int)UINT_004f3e30) {
    puVar1 = &UINT_008dad74;
    uVar2 = UINT_004f3e30;
    do {
      *(undefined1 *)((int)puVar1 + -6) = 0;
      *puVar1 = 0xffffff01;
      puVar1 = puVar1 + 0xd;
      uVar2 = uVar2 - 1;
    } while (uVar2 != 0);
  }
  return;
}
#endif


/* ---- 0x004d0ad0  SoundModule_SetVolume ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void __cdecl SoundModule_SetVolume(int id,uint volume)

{
  undefined1 *puVar1;
  uint uVar2;
  
  if (id == -0xff) {
    UINT_004f3e34 = volume;
    return;
  }
  if (0 < (int)UINT_004f3e30) {
    puVar1 = &DAT_008dad6c;
    uVar2 = UINT_004f3e30;
    do {
      if (*(int *)(puVar1 + 8) == id) {
        *puVar1 = (undefined1)volume;
      }
      puVar1 = puVar1 + 0x34;
      uVar2 = uVar2 - 1;
    } while (uVar2 != 0);
  }
  return;
}
#endif


/* ---- 0x004d0b10  SoundModule_GetVolume ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
uint __cdecl SoundModule_GetVolume(uint id)

{
  int iVar1;
  uint *puVar2;
  
  if (id == 0xffffff01) {
    return UINT_004f3e34;
  }
  iVar1 = 0;
  if (0 < (int)UINT_004f3e30) {
    puVar2 = &UINT_008dad74;
    do {
      if (*puVar2 == id) {
        return (int)(char)(&DAT_008dad6c)[iVar1 * 0x34];
      }
      iVar1 = iVar1 + 1;
      puVar2 = puVar2 + 0xd;
    } while (iVar1 < (int)UINT_004f3e30);
    return 0xffffffff;
  }
  return 0xffffffff;
}
#endif


/* ---- 0x004d0b60  SoundModule_SetPan ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void __cdecl SoundModule_SetPan(int id,byte pan)

{
  byte *pbVar1;
  uint uVar2;
  
  if (0 < (int)UINT_004f3e30) {
    pbVar1 = &DAT_008dad6d;
    uVar2 = UINT_004f3e30;
    do {
      if (*(int *)(pbVar1 + 7) == id) {
        *pbVar1 = pan;
      }
      pbVar1 = pbVar1 + 0x34;
      uVar2 = uVar2 - 1;
    } while (uVar2 != 0);
  }
  return;
}
#endif


/* ---- 0x004d0b90  SoundModule_GetPan ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
int __cdecl SoundModule_GetPan(uint id)

{
  int iVar1;
  uint *puVar2;
  
  iVar1 = 0;
  if ((int)UINT_004f3e30 < 1) {
    return -1;
  }
  puVar2 = &UINT_008dad74;
  do {
    if (*puVar2 == id) {
      return (int)(char)(&DAT_008dad6d)[iVar1 * 0x34];
    }
    iVar1 = iVar1 + 1;
    puVar2 = puVar2 + 0xd;
  } while (iVar1 < (int)UINT_004f3e30);
  return -1;
}
#endif


/* ---- 0x004d0bd0  SoundModule_DriverCommand2 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void __cdecl SoundModule_DriverCommand2(int arg)

{
  if (PTR_008dacf0 != (int *)0x0) {
    (*(code *)PTR_008dacf0[2])(arg);
  }
  return;
}
#endif


/* ---- 0x004d0bf0  SoundModule_DriverCommand3 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SoundModule_DriverCommand3(void)

{
  int iVar1;
  
  if (PTR_008dacf0 != (int *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x004d0bf9. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = (*(code *)PTR_008dacf0[3])();
    return iVar1;
  }
  return -1;
}
#endif


/* ---- 0x004d0c00  SoundModule_SetDriverRate ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void __cdecl SoundModule_SetDriverRate(uint rate)

{
  UINT_004f3e38 = rate;
  if (PTR_008dacf0 != (int *)0x0) {
    (*(code *)PTR_008dacf0[4])(rate);
  }
  return;
}
#endif


/* ---- 0x004d0c30  SoundModule_GetPosition ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
int __cdecl SoundModule_GetPosition(uint id)

{
  int iVar1;
  char *pcVar2;
  uint *puVar3;
  
  if (id == 0xffffff01) {
    iVar1 = 0;
    if (0 < (int)UINT_004f3e30) {
      pcVar2 = &DAT_008dad6e;
      do {
        if (*pcVar2 != '\0') {
          return (&UINT_008dad84)[iVar1 * 0xd] + 1;
        }
        iVar1 = iVar1 + 1;
        pcVar2 = pcVar2 + 0x34;
      } while (iVar1 < (int)UINT_004f3e30);
      return 0;
    }
  }
  else if (((int)id < 0) && ((int)(-1 - id) < (int)UINT_004f3e30)) {
    if ((&DAT_008dad6e)[(id + 1) * -0x34] != '\0') {
      return (&UINT_008dad84)[(id + 1) * -0xd] + 1;
    }
  }
  else {
    iVar1 = 0;
    if (0 < (int)UINT_004f3e30) {
      puVar3 = &UINT_008dad74;
      while (*puVar3 != id) {
        iVar1 = iVar1 + 1;
        puVar3 = puVar3 + 0xd;
        if ((int)UINT_004f3e30 <= iVar1) {
          return 0;
        }
      }
      if ((&DAT_008dad6e)[iVar1 * 0x34] != '\0') {
        return (&UINT_008dad84)[iVar1 * 0xd] + 1;
      }
    }
  }
  return 0;
}
#endif


/* ---- 0x004d0d70  SoundModule_SetParam ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
int __cdecl SoundModule_SetParam(int unused,int which,uint a,uint b)

{
  switch(which) {
  case 1:
    SoundModule_SetChannelVolume((byte)a,(byte)b);
    return 0;
  case 2:
    if (a != 0) {
      UINT_004f3e3c = a;
    }
    if (b != 0) {
      UINT_004f3e40 = b;
      return 0;
    }
    break;
  case 3:
    UINT_008dad40 = a;
    return 0;
  case 4:
    UINT_008dad4c = a;
    return 0;
  case 5:
    UINT_008dad44 = a;
    break;
  default:
    return -1;
  }
  return 0;
}
#endif


/* ---- 0x004d0e00  SoundModule_GetParam ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
int __cdecl SoundModule_GetParam(int unused,int which,uint *a,uint *b)

{
  byte bVar1;
  
  switch(which) {
  case 1:
    if (a != (uint *)0x0) {
      bVar1 = SoundModule_GetChannelVolume((byte)b);
      *a = (uint)bVar1;
      return 0;
    }
    break;
  case 2:
    if (a != (uint *)0x0) {
      *a = UINT_004f3e3c;
    }
    if (b != (uint *)0x0) {
      *b = UINT_004f3e40;
      return 0;
    }
    break;
  case 3:
    if (a != (uint *)0x0) {
      *a = UINT_008dad40;
      return 0;
    }
    break;
  case 4:
    if (a != (uint *)0x0) {
      *a = UINT_008dad4c;
      return 0;
    }
    break;
  case 5:
    if (a != (uint *)0x0) {
      *a = UINT_008dad44;
    }
    break;
  default:
    return -1;
  }
  return 0;
}
#endif


/* ---- 0x004d0eb0  SoundModule_GetChannelVolume ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
uint __cdecl SoundModule_GetChannelVolume(byte channel)

{
  if (channel == 0xff) {
    return (byte)UINT_004f3e34;
  }
  return (&DAT_008db0e8)[channel];
}
#endif


/* ---- 0x004d0ed0  SoundModule_SetChannelVolume ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void __cdecl SoundModule_SetChannelVolume(byte channel,byte value)

{
  if (channel == 0xff) {
    UINT_004f3e34 = (uint)value;
  }
  (&DAT_008db0e8)[channel] = value;
  return;
}
#endif


/* ---- 0x004d0f00  SoundModule_PlayVoc ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void __cdecl SoundModule_PlayVoc(byte *src,uint size,int id,int volume,int pan,uint flags)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  int iVar2;
  int *piVar3;
  uint *puVar4;
  char *pcVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  #define local_48 (*(uint *)(_frame + (0x60 - 0x48)))
  #define local_44 (*(uint *)(_frame + (0x60 - 0x44)))
  #define aiStack_40 (*(int (*)[16])(_frame + (0x60 - 0x40)))
  
  iVar2 = UINT_004f3e30 - 1;
  local_44 = 0;
  if (-1 < iVar2) {
    puVar4 = (uint *)(iVar2 * 0x34 + IMG_ADDR(0x008dad68));
    uVar6 = UINT_004f3e30;
    do {
      if ((int)local_44 < (int)*puVar4) {
        local_44 = *puVar4;
      }
      puVar4 = puVar4 + -0xd;
      uVar6 = uVar6 - 1;
    } while (uVar6 != 0);
  }
  iVar8 = 10000000;
  if (-1 < iVar2) {
    puVar4 = (uint *)(iVar2 * 0x34 + IMG_ADDR(0x008dad68));
    uVar6 = UINT_004f3e30;
    do {
      uVar1 = *puVar4;
      iVar7 = uVar1 - size;
      iVar9 = iVar7;
      if (iVar7 < 0) {
        iVar9 = size - uVar1;
      }
      if (((iVar9 < iVar8) && ((int)size < (int)uVar1)) &&
         (iVar8 = iVar7, local_44 = uVar1, iVar7 < 0)) {
        iVar8 = size - uVar1;
      }
      puVar4 = puVar4 + -0xd;
      uVar6 = uVar6 - 1;
    } while (uVar6 != 0);
  }
  if (-1 < iVar2) {
    piVar3 = aiStack_40 + iVar2;
    pcVar5 = &DAT_008dad6e + iVar2 * 0x34;
    uVar6 = UINT_004f3e30;
    do {
      uVar1 = *(uint *)(pcVar5 + -6);
      *piVar3 = 0;
      if ((uVar1 == local_44) &&
         (((*pcVar5 == '\0' || (*pcVar5 == '\x03')) || (*(int *)(pcVar5 + 2) <= (int)flags)))) {
        if (*pcVar5 == '\0') {
          *piVar3 = 0x1000;
        }
        uVar1 = *(uint *)(pcVar5 + 2);
        if ((int)uVar1 < (int)flags) {
          *piVar3 = *piVar3 + 0x800;
        }
        if (uVar1 == flags) {
          *piVar3 = *piVar3 + 0x400;
        }
        if (*pcVar5 == '\x03') {
          *piVar3 = *piVar3 + 0x200;
        }
        *piVar3 = *piVar3 + *(int *)(pcVar5 + 10) + 1;
      }
      pcVar5 = pcVar5 + -0x34;
      piVar3 = piVar3 + -1;
      uVar6 = uVar6 - 1;
    } while (uVar6 != 0);
  }
  iVar8 = 0;
  iVar9 = -1;
  if (-1 < iVar2) {
    piVar3 = aiStack_40 + iVar2;
    iVar7 = iVar2;
    do {
      if (iVar8 < *piVar3) {
        iVar8 = *piVar3;
        iVar9 = iVar7;
      }
      iVar7 = iVar7 + -1;
      piVar3 = piVar3 + -1;
    } while (-1 < iVar7);
  }
  if (-1 < iVar9) {
    if (-1 < iVar2) {
      piVar3 = (int *)(iVar2 * 0x34 + IMG_ADDR(0x008dad78));
      uVar6 = UINT_004f3e30;
      do {
        if (*piVar3 < 0x100) {
          *piVar3 = *piVar3 + 1;
        }
        piVar3 = piVar3 + -0xd;
        uVar6 = uVar6 - 1;
      } while (uVar6 != 0);
    }
    iVar2 = iVar9 * 0x34;
    *(undefined4 *)(iVar2 + IMG_ADDR(0x008dad78)) = 0;
    (&DAT_008dad6e)[iVar2] = 0;
    *(undefined1 *)(&UINT_008dad58)[iVar9 * 0xd] = 1;
    *(undefined1 *)((&UINT_008dad58)[iVar9 * 0xd] + 1) = 8;
    uVar6 = (&UINT_008dad58)[iVar9 * 0xd];
    *(undefined1 *)(uVar6 + 2) = 0;
    *(undefined1 *)(uVar6 + 3) = 0;
    *(undefined1 *)(uVar6 + 4) = 0;
    *(undefined1 *)(uVar6 + 5) = 0;
    uVar6 = (&UINT_008dad58)[iVar9 * 0xd];
    *(char *)(uVar6 + 6) = (char)(size >> 0x18);
    *(char *)(uVar6 + 7) = (char)(size >> 0x10);
    *(char *)(uVar6 + 8) = (char)(size >> 8);
    *(char *)(uVar6 + 9) = (char)size;
    *(undefined1 *)((&UINT_008dad58)[iVar9 * 0xd] + 10) = 0;
    *(undefined1 *)((&UINT_008dad58)[iVar9 * 0xd] + 0xb) = 0;
    Insane_MemCopyCdecl((void *)((&UINT_008dad58)[iVar9 * 0xd] + 0xc),src,size);
    (&UINT_008dad60)[iVar9 * 0xd] = (&UINT_008dad58)[iVar9 * 0xd];
    (&UINT_008dad64)[iVar9 * 0xd] = (&UINT_008dad58)[iVar9 * 0xd] + 0xc;
    (&UINT_008dad7c)[iVar9 * 0xd] = *(int *)(iVar2 + IMG_ADDR(0x008dad68)) - 0xc;
    (&UINT_008dad80)[iVar9 * 0xd] = size;
    (&UINT_008dad74)[iVar9 * 0xd] = id;
    (&DAT_008dad6c)[iVar2] = (undefined1)volume;
    (&DAT_008dad6d)[iVar2] = (undefined1)pan;
    (&UINT_008dad70)[iVar9 * 0xd] = flags;
    (&UINT_008dad84)[iVar9 * 0xd] = 0;
    (&DAT_008dad6e)[iVar2] = 2;
  }
  return;
}
#undef aiStack_40
#undef local_44
#undef local_48

#endif


/* ---- 0x004d1180  SoundModule_PlaySaud ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Receives one chunk of a Smush audio stream (first chunk: picks a voice; later chunks: appended to
   its ring buffer). Per-voice stream state lives in g_anSndStreamKey, g_anSndStreamKind and
   g_anSndChunkCount. */

void __cdecl
SoundModule_PlaySaud
          (byte *data,int size,int id,int volume,int pan,uint flags,int key,int chunkNo,int kind,
          int whole)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  uint uVar5;
  int iVar6;
  int *piVar7;
  char *pcVar8;
  uint uVar9;
  void *dst;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  #define local_44 (*(uint *)(_frame + (0x60 - 0x44)))
  #define aiStack_40 (*(int (*)[16])(_frame + (0x60 - 0x40)))
  
  if (chunkNo == 0) {
    if ((kind != 1) || (iVar10 = 0, whole != 0)) {
      iVar10 = CONCAT31(CONCAT21(CONCAT11(data[4],data[5]),data[6]),data[7]);
    }
    iVar11 = 0;
    chunkNo = 0;
    if (-1 < (int)(UINT_004f3e30 - 1)) {
      piVar7 = (int *)((UINT_004f3e30 - 1) * 0x34 + IMG_ADDR(0x008dad68));
      uVar9 = UINT_004f3e30;
      do {
        if (iVar11 < *piVar7) {
          iVar11 = *piVar7;
        }
        piVar7 = piVar7 + -0xd;
        uVar9 = uVar9 - 1;
        chunkNo = iVar11;
      } while (uVar9 != 0);
    }
    iVar11 = 10000000;
    if ((flags & 0xc0) == 0x40) {
      if (1 < kind) {
        SoundModule_SyncClock();
      }
    }
    else if (-1 < (int)(UINT_004f3e30 - 1)) {
      local_44 = UINT_004f3e30;
      piVar7 = (int *)((UINT_004f3e30 - 1) * 0x34 + IMG_ADDR(0x008dad68));
      do {
        iVar13 = *piVar7;
        iVar12 = iVar13 - iVar10;
        iVar6 = iVar12;
        if (iVar12 < 0) {
          iVar6 = iVar10 - iVar13;
        }
        if ((iVar6 < iVar11) && ((iVar10 * 2) / 3 < iVar13)) {
          iVar6 = size;
          if (1 < kind) {
            iVar6 = size * 2;
          }
          if ((iVar6 < iVar13) && (iVar11 = iVar12, chunkNo = iVar13, iVar12 < 0)) {
            iVar11 = iVar10 - iVar13;
          }
        }
        piVar7 = piVar7 + -0xd;
        local_44 = local_44 - 1;
      } while (local_44 != 0);
    }
    iVar10 = UINT_004f3e30 - 1;
    if (-1 < iVar10) {
      piVar7 = aiStack_40 + iVar10;
      pcVar8 = &DAT_008dad6e + iVar10 * 0x34;
      uVar9 = UINT_004f3e30;
      do {
        iVar11 = *(int *)(pcVar8 + -6);
        *piVar7 = 0;
        if (iVar11 == chunkNo) {
          if (*pcVar8 == '\0') {
LAB_004d12e0:
            *piVar7 = 0x1000;
          }
          else {
            if ((*pcVar8 != '\x03') && ((int)flags < *(int *)(pcVar8 + 2))) goto LAB_004d130e;
            if (*pcVar8 == '\0') goto LAB_004d12e0;
          }
          uVar5 = *(uint *)(pcVar8 + 2);
          if ((int)uVar5 < (int)flags) {
            *piVar7 = *piVar7 + 0x800;
          }
          if (uVar5 == flags) {
            *piVar7 = *piVar7 + 0x400;
          }
          if (*pcVar8 == '\x03') {
            *piVar7 = *piVar7 + 0x200;
          }
          *piVar7 = *piVar7 + *(int *)(pcVar8 + 10) + 1;
        }
LAB_004d130e:
        pcVar8 = pcVar8 + -0x34;
        piVar7 = piVar7 + -1;
        uVar9 = uVar9 - 1;
      } while (uVar9 != 0);
    }
    iVar13 = -1;
    iVar11 = -1;
    if (-1 < iVar10) {
      piVar7 = aiStack_40 + iVar10;
      iVar6 = iVar10;
      do {
        iVar12 = *piVar7;
        if ((iVar12 != 0) && (iVar13 < iVar12)) {
          iVar11 = iVar6;
          iVar13 = iVar12;
        }
        iVar6 = iVar6 + -1;
        piVar7 = piVar7 + -1;
      } while (-1 < iVar6);
    }
    if (-1 < iVar11) {
      if (-1 < iVar10) {
        piVar7 = (int *)(iVar10 * 0x34 + IMG_ADDR(0x008dad78));
        uVar9 = UINT_004f3e30;
        do {
          if (*piVar7 < 0xff) {
            *piVar7 = *piVar7 + 1;
          }
          piVar7 = piVar7 + -0xd;
          uVar9 = uVar9 - 1;
        } while (uVar9 != 0);
      }
      g_anSndStreamKey[iVar11] = key;
      g_anSndStreamKind[iVar11] = kind;
      iVar13 = iVar11 * 0x34;
      g_anSndChunkCount[iVar11] = 0;
      *(undefined4 *)(iVar13 + IMG_ADDR(0x008dad78)) = 0;
      (&DAT_008dad6e)[iVar13] = 0;
      iVar10 = CONCAT31(CONCAT21(CONCAT11(data[0xc],data[0xd]),data[0xe]),data[0xf]);
      bVar1 = data[iVar10 + 0x15];
      bVar2 = data[iVar10 + 0x16];
      bVar3 = data[iVar10 + 0x14];
      bVar4 = data[iVar10 + 0x17];
      if ((kind == 1) && (whole == 0)) {
        (&UINT_008dad60)[iVar11 * 0xd] = (uint)(data + 0x10);
        iVar6 = size;
      }
      else {
        uVar9 = *(uint *)(iVar13 + IMG_ADDR(0x008dad68));
        if (size < (int)*(uint *)(iVar13 + IMG_ADDR(0x008dad68))) {
          uVar9 = size;
        }
        Insane_MemCopyCdecl((void *)(&UINT_008dad58)[iVar11 * 0xd],data,uVar9);
        (&UINT_008dad60)[iVar11 * 0xd] = (&UINT_008dad58)[iVar11 * 0xd] + 0x10;
        iVar6 = *(int *)(iVar13 + IMG_ADDR(0x008dad68));
      }
      (&UINT_008dad7c)[iVar11 * 0xd] = (iVar6 - iVar10) - 0x18;
      (&UINT_008dad64)[iVar11 * 0xd] = iVar10 + 8 + (&UINT_008dad60)[iVar11 * 0xd];
      (&UINT_008dad80)[iVar11 * 0xd] = (size - iVar10) - 0x18;
      (&UINT_008dad88)[iVar11 * 0xd] = CONCAT31(CONCAT21(CONCAT11(bVar3,bVar1),bVar2),bVar4);
      (&UINT_008dad74)[iVar11 * 0xd] = id;
      (&DAT_008dad6c)[iVar13] = 0x7f;
      (&DAT_008dad6d)[iVar13] = 0;
      if ((-1 < volume) && (volume < 0x80)) {
        (&DAT_008dad6c)[iVar13] = (char)volume;
      }
      if ((-0x80 < pan) && (pan < 0x80)) {
        (&DAT_008dad6d)[iVar13] = (char)pan;
      }
      (&UINT_008dad70)[iVar11 * 0xd] = flags;
      (&UINT_008dad84)[iVar11 * 0xd] = 0;
      (&DAT_008dad6e)[iVar13] = 2;
      uVar9 = (&UINT_008dad64)[iVar11 * 0xd];
      uVar9 = CONCAT31(CONCAT21(CONCAT11(*(undefined1 *)(uVar9 - 8),*(undefined1 *)(uVar9 - 7)),
                                *(undefined1 *)(uVar9 - 6)),*(undefined1 *)(uVar9 - 5));
      if (uVar9 < 0x5336535b) {
        if (uVar9 == 0x5336535a) {
          (&DAT_008dad6f)[iVar13] = 5;
          return;
        }
        if (uVar9 == 0x53364d5a) {
          (&DAT_008dad6f)[iVar13] = 4;
          return;
        }
LAB_004d153e:
        (&DAT_008dad6f)[iVar13] = 0;
        return;
      }
      if (uVar9 < 0x53443254) {
        if (uVar9 != 0x53443253) {
          (&DAT_008dad6f)[iVar13] = 0;
          return;
        }
      }
      else {
        if (uVar9 == 0x5344364d) {
          (&DAT_008dad6f)[iVar13] = 2;
          return;
        }
        if (uVar9 == 0x53443653) {
          (&DAT_008dad6f)[iVar13] = 3;
          return;
        }
        if (uVar9 != 0x53443853) goto LAB_004d153e;
      }
      (&DAT_008dad6f)[iVar13] = 1;
      return;
    }
  }
  else {
    iVar10 = UINT_004f3e30 - 1;
    if (-1 < iVar10) {
      piVar7 = g_anSndStreamKind + iVar10;
      pcVar8 = &DAT_008dad6e + iVar10 * 0x34;
      while ((((*pcVar8 == '\0' || (key != g_anSndStreamKey[iVar10])) ||
              (chunkNo != g_anSndChunkCount[iVar10] + 1)) || (kind != *piVar7))) {
        iVar10 = iVar10 + -1;
        pcVar8 = pcVar8 + -0x34;
        piVar7 = piVar7 + -1;
        if (iVar10 < 0) {
          return;
        }
      }
      g_anSndChunkCount[iVar10] = g_anSndChunkCount[iVar10] + 1;
      uVar9 = (&UINT_008dad7c)[iVar10 * 0xd];
      iVar11 = (int)(&UINT_008dad80)[iVar10 * 0xd] % (int)uVar9;
      if ((int)uVar9 < iVar11 + size) {
        Insane_MemCopyCdecl((void *)(iVar11 + (&UINT_008dad64)[iVar10 * 0xd]),data,uVar9 - iVar11);
        data = data + ((&UINT_008dad7c)[iVar10 * 0xd] - iVar11);
        dst = (void *)(&UINT_008dad64)[iVar10 * 0xd];
        uVar9 = (iVar11 + size) - (&UINT_008dad7c)[iVar10 * 0xd];
      }
      else {
        dst = (void *)((&UINT_008dad64)[iVar10 * 0xd] + iVar11);
        uVar9 = size;
      }
      Insane_MemCopyCdecl(dst,data,uVar9);
      if ((-1 < volume) && (volume < 0x7f)) {
        (&DAT_008dad6c)[iVar10 * 0x34] = (char)volume;
      }
      if ((-0x80 < pan) && (pan < 0x80)) {
        (&DAT_008dad6d)[iVar10 * 0x34] = (char)pan;
      }
      (&UINT_008dad80)[iVar10 * 0xd] = (&UINT_008dad80)[iVar10 * 0xd] + size;
    }
  }
  return;
}
#undef aiStack_40
#undef local_44

#endif


/* ---- 0x004d1690  SoundModule_SyncClock ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SoundModule_SyncClock(void)

{
  UINT_008db1f8 = (**(code **)(UINT_008dad48 + 0x18))();
  return;
}
#endif


/* ---- 0x004d16a0  SoundModule_MixCallback ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Mixes all active tracks into the driver buffer (called by DSound_FillStreamBuffer through the
   driver) */

void __cdecl SoundModule_MixCallback(int frames,void *mix)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  undefined1 uVar2;
  byte bVar3;
  void *dst;
  undefined1 *puVar4;
  bool bVar5;
  bool bVar6;
  uint *puVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  int iVar15;
  bool bVar16;
  #define local_24 (*(int *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(int *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(int *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(int *)(_frame + (0x40 - 0x18)))
  #define local_10 (*(int *)(_frame + (0x40 - 0x10)))
  
  UINT_008dacf4 = UINT_008dacf4 + 1;
  SoundModule_AdvanceClock(((double)frames * 1193180.0) / (double)(int)UINT_004f3e38);
  if (UINT_008db1ec == 0) {
    if (UINT_004f3e48 != 0) {
      UINT_004f3e48 = 0;
      puVar7 = &UINT_008da928;
      do {
        puVar7[-4] = 0;
        *puVar7 = 0;
        puVar7 = puVar7 + 0xf;
      } while ((int)puVar7 < IMG_ADDR(0x008dace8));
    }
    bVar6 = false;
    local_10 = 0;
    if (0 < (int)UINT_004f3e30) {
      do {
        iVar15 = local_10 * 0x34;
        uVar13 = (&UINT_008dad70)[local_10 * 0xd] & 0xc0;
        if ((((uVar13 == 0x80) && (UINT_008dad4c != 0)) ||
            ((uVar13 == 0x40 && (UINT_008dad40 != 0)))) || ((uVar13 == 0 && (UINT_008dad44 != 0))))
        {
          bVar5 = true;
        }
        else {
          bVar5 = false;
        }
        local_20 = (int)(UINT_004f3e34 * (int)(char)(&DAT_008dad6c)[iVar15]) / 0x7f;
        if ((uVar13 == 0x40) && (UINT_008dad4c != 0)) {
          local_20 = (int)(local_20 * UINT_004f3e44) >> 8;
        }
        if (((&DAT_008dad6e)[iVar15] == '\x02') && ((&UINT_008da90c)[local_10 * 0xf] == 1)) {
          uVar13 = (&UINT_008da8fc)[local_10 * 0xf];
          uVar9 = (&UINT_008da8f8)[local_10 * 0xf];
          cVar1 = (&DAT_008dad6c)[iVar15];
          (&UINT_008da918)[local_10 * 0xf] = 0x1800;
          (&UINT_008da914)[local_10 * 0xf] = (int)cVar1;
          dst = (void *)(&UINT_008dad5c)[local_10 * 0xd];
          (&DAT_008da91c)[local_10 * 0x3c] = (&DAT_008dad6f)[iVar15];
          (&UINT_008da910)[local_10 * 0xf] = (&UINT_008da904)[local_10 * 0xf];
          Dsnd_MemFillCdecl(dst,0x80,0x1800);
          uVar8 = (&UINT_008da8f8)[local_10 * 0xf] - (int)uVar13 % (int)uVar9;
          if (0x1800 < (int)uVar8) {
            uVar8 = 0x1800;
          }
          Dsnd_MemCopyCdecl((void *)(&UINT_008dad5c)[local_10 * 0xd],
                            (void *)((&UINT_008da8f4)[local_10 * 0xf] + (int)uVar13 % (int)uVar9),
                            uVar8);
          (&UINT_008da920)[local_10 * 0xf] = 0;
        }
        else if (((&DAT_008dad6e)[iVar15] == '\x01') &&
                ((uVar13 = (&UINT_008dad80)[local_10 * 0xd],
                 (int)(&UINT_008da8fc)[local_10 * 0xf] <
                 (int)((uVar13 - (&UINT_008dad7c)[local_10 * 0xd]) + 15000) &&
                 (uVar9 = (&UINT_008dad88)[local_10 * 0xd], (int)uVar13 < (int)uVar9)))) {
          (&UINT_008da920)[local_10 * 0xf] = 0;
          uVar8 = (&UINT_008da8fc)[local_10 * 0xf];
          uVar13 = (uVar13 - uVar8) - 15000;
          if ((int)(&UINT_008da900)[local_10 * 0xf] < (int)uVar13) {
            uVar13 = (&UINT_008da900)[local_10 * 0xf];
          }
          iVar14 = uVar9 - (&UINT_008da8f8)[local_10 * 0xf];
          if (iVar14 < (int)(uVar13 + uVar8)) {
            uVar13 = iVar14 - uVar8;
          }
          if (0 < (int)uVar13) {
            (&UINT_008da918)[local_10 * 0xf] = 0x1800;
            (&UINT_008da910)[local_10 * 0xf] = (&UINT_008da904)[local_10 * 0xf];
            Dsnd_MemCopyCdecl((void *)(&UINT_008dad5c)[local_10 * 0xd],
                              (void *)((&UINT_008da8f4)[local_10 * 0xf] +
                                      (int)(&UINT_008da8fc)[local_10 * 0xf] %
                                      (int)(&UINT_008da8f8)[local_10 * 0xf]),0x1800);
            (&UINT_008da8fc)[local_10 * 0xf] = (&UINT_008da8fc)[local_10 * 0xf] + uVar13;
            (&UINT_008da900)[local_10 * 0xf] = (&UINT_008da900)[local_10 * 0xf] - uVar13;
          }
        }
        iVar14 = local_10 * 0x3c;
        uVar13 = (&UINT_008da918)[local_10 * 0xf];
        if (*(int *)(&DAT_004f3e18 + (uint)(byte)(&DAT_008da91c)[iVar14] * 4) < (int)uVar13) {
          local_1c = 0;
          uVar9 = (int)(frames * *(int *)(&DAT_004f3e18 + (uint)(byte)(&DAT_008da91c)[iVar14] * 4) *
                       (&UINT_008da910)[local_10 * 0xf]) / (int)UINT_004f3e38;
          if ((int)uVar9 <= (int)uVar13) {
            uVar13 = uVar9;
          }
          uVar8 = (int)uVar13 >> 0x1f;
          for (uVar13 = uVar13 - (((uVar13 ^ uVar8) - uVar8 & 3 ^ uVar8) - uVar8); 3 < (int)uVar13;
              uVar13 = uVar13 - uVar8) {
            uVar8 = uVar13;
            if (0x400 < (int)uVar13) {
              uVar8 = 0x400;
            }
            if (uVar8 == uVar9) {
              local_24 = frames;
            }
            else {
              local_24 = (int)(((int)uVar8 /
                               *(int *)(&DAT_004f3e18 + (uint)(byte)(&DAT_008da91c)[iVar14] * 4)) *
                              UINT_004f3e38) / (int)(&UINT_008da910)[local_10 * 0xf];
            }
            if (bVar5) {
              iVar10 = (int)(char)(&DAT_008dad6d)[iVar15];
              if (UINT_008dad50 != 0) {
                iVar10 = -iVar10;
              }
              (*(code *)mix)(((&UINT_008dad5c)[local_10 * 0xd] - (&UINT_008da918)[local_10 * 0xf]) + 0x1800,
                     local_1c,local_24,uVar8,1,
                     (int)(UINT_004f3e34 * (&UINT_008da918)[local_10 * 0xf] *
                          (&UINT_008da914)[local_10 * 0xf]) / 0xbe800,iVar10);
            }
            local_1c = local_1c + local_24;
            (&UINT_008da918)[local_10 * 0xf] = (&UINT_008da918)[local_10 * 0xf] - uVar8;
          }
        }
        if ((&DAT_008dad6e)[iVar15] == '\x02') {
          if ((&UINT_008da90c)[local_10 * 0xf] != 1) {
            (&UINT_008da920)[local_10 * 0xf] = 0x10;
          }
          uVar13 = (&UINT_008dad64)[local_10 * 0xd];
          uVar9 = (&UINT_008dad7c)[local_10 * 0xd];
          (&UINT_008da8f0)[local_10 * 0xf] = (&UINT_008dad60)[local_10 * 0xd];
          uVar2 = (&DAT_008dad6f)[iVar15];
          (&UINT_008da8f4)[local_10 * 0xf] = uVar13;
          (&UINT_008da8f8)[local_10 * 0xf] = uVar9;
          (&DAT_008da908)[iVar14] = uVar2;
          (&UINT_008da900)[local_10 * 0xf] = 0;
          (&UINT_008da928)[local_10 * 0xf] = 0;
          (&DAT_008dad6e)[iVar15] = 1;
        }
        if ((&DAT_008dad6e)[iVar15] != '\0') {
          local_18 = 0;
          local_24 = frames;
          while (0 < local_24) {
            uVar13 = (&UINT_008da900)[local_10 * 0xf];
            if (0 < (int)uVar13) {
              uVar9 = (&UINT_008da8f8)[local_10 * 0xf];
              iVar10 = (int)(&UINT_008da8fc)[local_10 * 0xf] % (int)uVar9;
              uVar8 = (int)(*(int *)(&DAT_004f3e18 + (uint)(byte)(&DAT_008da908)[iVar14] * 4) *
                            local_24 * (&UINT_008da904)[local_10 * 0xf]) / (int)UINT_004f3e38;
              if ((int)uVar8 <= (int)uVar13) {
                uVar13 = uVar8;
              }
              if ((int)uVar9 < (int)(iVar10 + uVar13)) {
                uVar13 = uVar9 - iVar10;
              }
              uVar9 = (&UINT_008da920)[local_10 * 0xf];
              if ((int)(&UINT_008dad80)[local_10 * 0xd] <
                  (int)((&UINT_008da8fc)[local_10 * 0xf] + uVar13)) {
                if (uVar9 != 0) {
                  (&UINT_008da920)[local_10 * 0xf] = uVar9 - 1;
                }
                (&DAT_008dad6e)[iVar15] = 3;
                if (0x400 < (int)uVar13) {
                  uVar13 = 0x400;
                }
                (&UINT_008da8fc)[local_10 * 0xf] = (&UINT_008da8fc)[local_10 * 0xf] - uVar13;
                (&UINT_008da900)[local_10 * 0xf] = (&UINT_008da900)[local_10 * 0xf] + uVar13;
                iVar10 = (int)(&UINT_008da8fc)[local_10 * 0xf] %
                         (int)(&UINT_008da8f8)[local_10 * 0xf];
              }
              else {
                if ((int)uVar9 < 0x10) {
                  (&UINT_008da920)[local_10 * 0xf] = uVar9 + 1;
                }
                if (0x400 < (int)uVar13) {
                  uVar13 = 0x400;
                }
                (&DAT_008dad6e)[iVar15] = 1;
                if (((byte)(&UINT_008dad70)[local_10 * 0xd] & 0xc0) == 0x80) {
                  bVar6 = true;
                }
              }
              iVar12 = local_24;
              if (uVar13 != uVar8) {
                iVar12 = (int)(((int)uVar13 /
                               *(int *)(&DAT_004f3e18 + (uint)(byte)(&DAT_008da908)[iVar14] * 4)) *
                              UINT_004f3e38) / (int)(&UINT_008da904)[local_10 * 0xf];
              }
              if (bVar5) {
                iVar11 = (int)(char)(&DAT_008dad6d)[iVar15];
                if (UINT_008dad50 != 0) {
                  iVar11 = -iVar11;
                }
                (*(code *)mix)((&UINT_008da8f4)[local_10 * 0xf] + iVar10,local_18,iVar12,uVar13,1,
                       (int)(local_20 * (&UINT_008da920)[local_10 * 0xf]) >> 4,iVar11);
              }
              local_24 = local_24 - iVar12;
              (&UINT_008da900)[local_10 * 0xf] = (&UINT_008da900)[local_10 * 0xf] - uVar13;
              local_18 = local_18 + iVar12;
              (&UINT_008da8fc)[local_10 * 0xf] = (&UINT_008da8fc)[local_10 * 0xf] + uVar13;
            }
            uVar13 = (&UINT_008da900)[local_10 * 0xf];
            uVar9 = UINT_004f3e34;
            while (UINT_004f3e34 = uVar9, (int)uVar13 < 1) {
              if (local_24 == 0) goto LAB_004d2124;
              puVar4 = (undefined1 *)(&UINT_008da8f0)[local_10 * 0xf];
              switch(*puVar4) {
              case 1:
                (&UINT_008da928)[local_10 * 0xf] = 0;
                uVar13 = (&UINT_008da8f0)[local_10 * 0xf];
                uVar8 = (&UINT_008dad7c)[local_10 * 0xd];
                (&UINT_008da8fc)[local_10 * 0xf] =
                     CONCAT31(CONCAT21(CONCAT11(*(undefined1 *)(uVar13 + 2),
                                                *(undefined1 *)(uVar13 + 3)),
                                       *(undefined1 *)(uVar13 + 4)),*(undefined1 *)(uVar13 + 5));
                uVar9 = UINT_004f3e38;
                uVar13 = (&UINT_008da8f0)[local_10 * 0xf];
                (&UINT_008da900)[local_10 * 0xf] =
                     CONCAT31(CONCAT21(CONCAT11(*(undefined1 *)(uVar13 + 6),
                                                *(undefined1 *)(uVar13 + 7)),
                                       *(undefined1 *)(uVar13 + 8)),*(undefined1 *)(uVar13 + 9));
                (&UINT_008da904)[local_10 * 0xf] = uVar9;
                (&UINT_008da8f0)[local_10 * 0xf] =
                     *(byte *)((&UINT_008da8f0)[local_10 * 0xf] + 1) + 2 +
                     (&UINT_008da8f0)[local_10 * 0xf];
                uVar13 = (&UINT_008dad80)[local_10 * 0xd];
                uVar9 = (&UINT_008da8fc)[local_10 * 0xf];
                if ((int)(((((int)(&UINT_008dad88)[local_10 * 0xd] <= (int)uVar13) - 1 & 15000) +
                          uVar13) - uVar8) <= (int)uVar9) break;
                iVar10 = ((uVar13 - uVar9) - uVar8) + 15000;
                if (iVar10 <= (int)(&UINT_008da900)[local_10 * 0xf]) goto LAB_004d1ebb;
                goto LAB_004d1ea1;
              case 2:
              case 8:
              case 9:
              case 10:
              case 0xb:
                bVar3 = puVar4[4];
                if (bVar3 == 0xff) {
                  PIECE(UINT_004f3e34,0,1) = (byte)uVar9;
                }
                else if (bVar3 == 0xfe) {
                  PIECE(UINT_004f3e34,0,1) = (&DAT_008dad6c)[iVar15];
                }
                else if (bVar3 == 0xfd) {
                  PIECE(UINT_004f3e34,0,1) = (&DAT_008dad6d)[iVar15];
                }
                else {
                  PIECE(UINT_004f3e34,0,1) = (&DAT_008db0e8)[bVar3];
                }
                switch(*puVar4) {
                case 2:
                  if (((byte)UINT_004f3e34 != 0) || (bVar3 == 0)) {
                    PIECE(UINT_004f3e34,0,1) = 1;
                  }
                  break;
                case 8:
                  PIECE(UINT_004f3e34,0,1) = (byte)puVar4[5] < (byte)UINT_004f3e34;
                  break;
                case 9:
                  PIECE(UINT_004f3e34,0,1) = (byte)UINT_004f3e34 < (byte)puVar4[5];
                  break;
                case 10:
                  PIECE(UINT_004f3e34,0,1) = (byte)UINT_004f3e34 == puVar4[5];
                  break;
                case 0xb:
                  PIECE(UINT_004f3e34,0,1) = (byte)UINT_004f3e34 != puVar4[5];
                }
                bVar16 = (byte)UINT_004f3e34 == 0;
                if (bVar16) {
LAB_004d20e0:
                  (&UINT_008da8f0)[local_10 * 0xf] = (uint)(puVar4 + (byte)puVar4[1] + 2);
                }
                else {
                  (&UINT_008da8f0)[local_10 * 0xf] =
                       (uint)(puVar4 + ((uint)(byte)puVar4[3] |
                                       (int)(short)((ushort)(byte)puVar4[2] << 8)));
                }
                break;
              case 3:
                bVar3 = puVar4[2];
                if (bVar3 == 0xff) {
                  UINT_004f3e34 = (uint)(byte)puVar4[3];
                  (&UINT_008da8f0)[local_10 * 0xf] = (uint)(puVar4 + (byte)puVar4[1] + 2);
                }
                else if (bVar3 == 0xfe) {
                  cVar1 = puVar4[3];
                  (&DAT_008dad6c)[iVar15] = cVar1;
                  local_20 = (int)(uVar9 * (int)cVar1) / 0x7f;
                  if ((((byte)(&UINT_008dad70)[local_10 * 0xd] & 0xc0) != 0x40) ||
                     (UINT_008dad4c == 0)) goto LAB_004d20e0;
                  local_20 = (int)(local_20 * UINT_004f3e44) >> 8;
                  (&UINT_008da8f0)[local_10 * 0xf] = (uint)(puVar4 + (byte)puVar4[1] + 2);
                }
                else if (bVar3 == 0xfd) {
                  (&DAT_008dad6d)[iVar15] = puVar4[3];
                  (&UINT_008da8f0)[local_10 * 0xf] = (uint)(puVar4 + (byte)puVar4[1] + 2);
                }
                else {
                  (&DAT_008db0e8)[bVar3] = puVar4[3];
                  (&UINT_008da8f0)[local_10 * 0xf] = (uint)(puVar4 + (byte)puVar4[1] + 2);
                }
                break;
              case 4:
                bVar3 = puVar4[2];
                if (bVar3 == 0xff) {
                  UINT_004f3e34 = uVar9 + (byte)puVar4[3];
                  (&UINT_008da8f0)[local_10 * 0xf] = (uint)(puVar4 + (byte)puVar4[1] + 2);
                }
                else if (bVar3 == 0xfe) {
                  (&DAT_008dad6c)[iVar15] = (&DAT_008dad6c)[iVar15] + puVar4[3];
                  (&UINT_008da8f0)[local_10 * 0xf] = (uint)(puVar4 + (byte)puVar4[1] + 2);
                }
                else {
                  if (bVar3 != 0xfd) {
                    (&DAT_008db0e8)[bVar3] = puVar4[3] + (&DAT_008db0e8)[bVar3];
                    goto LAB_004d20e0;
                  }
                  (&DAT_008dad6d)[iVar15] = (&DAT_008dad6d)[iVar15] + puVar4[3];
                  (&UINT_008da8f0)[local_10 * 0xf] = (uint)(puVar4 + (byte)puVar4[1] + 2);
                }
                break;
              default:
                (&DAT_008dad6e)[iVar15] = 0;
                (&UINT_008dad74)[local_10 * 0xd] = 0xffffff01;
                local_24 = 0;
                break;
              case 6:
                (&UINT_008da928)[local_10 * 0xf] = 0;
                uVar13 = (&UINT_008da8f0)[local_10 * 0xf];
                (&UINT_008da8fc)[local_10 * 0xf] =
                     CONCAT31(CONCAT21(CONCAT11(*(undefined1 *)(uVar13 + 2),
                                                *(undefined1 *)(uVar13 + 3)),
                                       *(undefined1 *)(uVar13 + 4)),*(undefined1 *)(uVar13 + 5));
                uVar13 = (&UINT_008da8f0)[local_10 * 0xf];
                (&UINT_008da900)[local_10 * 0xf] =
                     CONCAT31(CONCAT21(CONCAT11(*(undefined1 *)(uVar13 + 6),
                                                *(undefined1 *)(uVar13 + 7)),
                                       *(undefined1 *)(uVar13 + 8)),*(undefined1 *)(uVar13 + 9));
                uVar13 = (&UINT_008da8f0)[local_10 * 0xf];
                (&UINT_008da904)[local_10 * 0xf] =
                     CONCAT31(CONCAT21(CONCAT11(*(undefined1 *)(uVar13 + 10),
                                                *(undefined1 *)(uVar13 + 0xb)),
                                       *(undefined1 *)(uVar13 + 0xc)),*(undefined1 *)(uVar13 + 0xd))
                ;
                uVar13 = (&UINT_008da8f0)[local_10 * 0xf];
LAB_004d1e4f:
                (&UINT_008da8f0)[local_10 * 0xf] = *(byte *)(uVar13 + 1) + 2 + uVar13;
                goto LAB_004d1e5e;
              case 7:
                if ((&UINT_008da928)[local_10 * 0xf] == 0) {
                  (&UINT_008da928)[local_10 * 0xf] =
                       CONCAT31(CONCAT21(CONCAT11(puVar4[6],puVar4[7]),puVar4[8]),puVar4[9]);
                  (&UINT_008da924)[local_10 * 0xf] = 0;
                }
                uVar13 = (&UINT_008da8f0)[local_10 * 0xf];
                (&UINT_008da8fc)[local_10 * 0xf] =
                     CONCAT31(CONCAT21(CONCAT11(*(undefined1 *)(uVar13 + 2),
                                                *(undefined1 *)(uVar13 + 3)),
                                       *(undefined1 *)(uVar13 + 4)),*(undefined1 *)(uVar13 + 5)) +
                     (&UINT_008da924)[local_10 * 0xf];
                uVar13 = (&UINT_008da8f0)[local_10 * 0xf];
                uVar13 = CONCAT31(CONCAT21(CONCAT11(*(undefined1 *)(uVar13 + 0xe),
                                                    *(undefined1 *)(uVar13 + 0xf)),
                                           *(undefined1 *)(uVar13 + 0x10)),
                                  *(undefined1 *)(uVar13 + 0x11));
                if ((&UINT_008da928)[local_10 * 0xf] < uVar13) {
                  uVar13 = (&UINT_008da928)[local_10 * 0xf];
                }
                (&UINT_008da900)[local_10 * 0xf] = uVar13;
                uVar13 = (&UINT_008da8f0)[local_10 * 0xf];
                (&UINT_008da904)[local_10 * 0xf] =
                     CONCAT31(CONCAT21(CONCAT11(*(undefined1 *)(uVar13 + 10),
                                                *(undefined1 *)(uVar13 + 0xb)),
                                       *(undefined1 *)(uVar13 + 0xc)),*(undefined1 *)(uVar13 + 0xd))
                ;
                (&UINT_008da928)[local_10 * 0xf] =
                     (&UINT_008da928)[local_10 * 0xf] - (&UINT_008da900)[local_10 * 0xf];
                (&UINT_008da924)[local_10 * 0xf] =
                     (&UINT_008da924)[local_10 * 0xf] + (&UINT_008da900)[local_10 * 0xf];
                uVar13 = (&UINT_008da8f0)[local_10 * 0xf];
                if ((&UINT_008da928)[local_10 * 0xf] != 0) goto LAB_004d1e4f;
                (&UINT_008da8f0)[local_10 * 0xf] =
                     ((uint)*(byte *)(uVar13 + 0x13) |
                     (int)(short)((ushort)*(byte *)(uVar13 + 0x12) << 8)) + uVar13;
LAB_004d1e5e:
                uVar13 = (&UINT_008dad80)[local_10 * 0xd];
                uVar9 = (&UINT_008da8fc)[local_10 * 0xf];
                if ((int)uVar9 <
                    (int)(((((int)(&UINT_008dad88)[local_10 * 0xd] <= (int)uVar13) - 1 & 15000) +
                          uVar13) - (&UINT_008dad7c)[local_10 * 0xd])) {
                  iVar10 = ((uVar13 - uVar9) - (&UINT_008dad7c)[local_10 * 0xd]) + 15000;
                  if ((int)(&UINT_008da900)[local_10 * 0xf] < iVar10) {
LAB_004d1ea1:
                    (&DAT_008dad6e)[iVar15] = 0;
                    (&UINT_008dad74)[local_10 * 0xd] = 0xffffff01;
                    local_24 = 0;
                  }
                  else {
LAB_004d1ebb:
                    (&UINT_008da8fc)[local_10 * 0xf] = uVar9 + iVar10;
                    (&UINT_008da900)[local_10 * 0xf] = (&UINT_008da900)[local_10 * 0xf] - iVar10;
                  }
                }
              }
              uVar9 = UINT_004f3e34;
              uVar13 = (&UINT_008da900)[local_10 * 0xf];
            }
          }
        }
LAB_004d2124:
        uVar13 = UINT_004f3e30;
        (&UINT_008dad84)[local_10 * 0xd] = (&UINT_008da8fc)[local_10 * 0xf];
        (&UINT_008da90c)[local_10 * 0xf] = (uint)(byte)(&DAT_008dad6e)[iVar15];
        local_10 = local_10 + 1;
      } while (local_10 < (int)uVar13);
    }
    if (bVar6) {
      if (((int)UINT_004f3e3c < (int)UINT_004f3e44) &&
         (UINT_004f3e44 = UINT_004f3e44 - ((int)(frames * UINT_004f3e40) >> 0xd),
         (int)UINT_004f3e44 < (int)UINT_004f3e3c)) {
        UINT_004f3e44 = UINT_004f3e3c;
        return;
      }
    }
    else if (((int)UINT_004f3e44 < 0x100) &&
            (UINT_004f3e44 = UINT_004f3e44 + ((int)(frames * UINT_004f3e40) >> 0xf),
            0x100 < (int)UINT_004f3e44)) {
      UINT_004f3e44 = 0x100;
    }
  }
  return;
}
#undef local_10
#undef local_18
#undef local_1c
#undef local_20
#undef local_24

#endif


/* ---- 0x004d2340  SoundModule_AdvanceClock ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl SoundModule_AdvanceClock(double ticks)

{
  int iVar1;
  uint uVar2;
  longlong lVar3;
  undefined4 unaff_retaddr;
  
  _DAT_008db200 = _DAT_008db200 + ticks;
  if (UINT_008db1f8 != 0) {
    iVar1 = (**(code **)(UINT_008dad48 + 0x18))();
    if ((int)UINT_008db1f8 < iVar1) {
      uVar2 = iVar1 - UINT_008db1f8;
      ticks = (double)(ulonglong)uVar2;
      if ((int)uVar2 / 5 < 0x1234dc) {
        UINT_008db1f8 = 0;
        _DAT_008db200 = _DAT_008db200 - (double)(int)uVar2;
        ticks = (double)(ulonglong)uVar2;
      }
    }
  }
  lVar3 = _ftol((double)CONCAT44(PIECE(ticks,0,4),unaff_retaddr));
  (**(code **)(UINT_008dad48 + 0x20))((int)lVar3);
  lVar3 = _ftol((double)CONCAT44(PIECE(ticks,0,4),unaff_retaddr));
  _DAT_008db200 = _DAT_008db200 - (double)(int)lVar3;
  return;
}
#endif

