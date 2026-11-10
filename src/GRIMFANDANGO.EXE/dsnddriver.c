/* GRIMFANDANGO.EXE :: dsnddriver.c
 * functions 0x004d2420 .. 0x004d2bf0 (12 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004d2420  sou_dsnd_module ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Entry of LECMODULE insane_dsnd: registers the DirectSound sound driver (SNDDRIVER insane_dsnd)
   Original name sou_dsnd_module (the remaster's GrimFandango (Linux): slot 0 of the
   "LECMODULE=insane_dsnd" service table); was DsndDriver_Register. */

int __cdecl sou_dsnd_module(int *services,uint moduleSize)

{
  g_pDsndDriver_share_services = services;
  g_dwDsndDriver_share_config = moduleSize;
  (*(code *)*services)(s_LECMODULE_insane_dsnd_004f3fec,&g_apfnDsndDriverModule);
  (*(code *)*g_pDsndDriver_share_services)
            (s_SNDDRIVER_insane_dsnd_004f3fd4,&g_pDsndDriver_snddriver_services);
  _DAT_008db414 = 0xffffffff;
  _DAT_008db20c = 0xffffffff;
  _DAT_008dcc38 = 0xffffffff;
  _DAT_008db42c = 0xffffffff;
  return 0;
}
#endif


/* ---- 0x004d2480  DsndDriver_module_terminate ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Original name DsndDriver_module_terminate (the remaster's GrimFandango (Linux): slot 1 of the
   "LECMODULE=insane_dsnd" service table; module_terminate is a static several LEC modules have,
   written with the module prefix); was DsndDriver_Unregister. */

void DsndDriver_module_terminate(void)

{
  (*(code *)g_pDsndDriver_share_services[1])(s_SNDDRIVER_insane_dsnd_004f3fd4);
  (*(code *)g_pDsndDriver_share_services[1])(s_LECMODULE_insane_dsnd_004f3fec);
  return;
}
#endif


/* ---- 0x004d24b0  DsndDriver_module_startup ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Gets the TIMER clock interface and allocates the mixer table Original name
   DsndDriver_module_startup (the remaster's GrimFandango (Linux): the static module_startup of the
   DsndDriver module (the remaster has one per module file, hence the prefix); strings:
   'MEMORY.mixertable' | 'DirectSoundDriver Module: Cannot allocate timer services.' |
   'TIMER=clock'); was DsndDriver_Init. */

int DsndDriver_module_startup(void)

{
  g_pDsndDriver_timer_services =
       (int *)(*(code *)g_pDsndDriver_share_services[2])
                        (s_TIMER_clock_004f4054,g_dwDsndDriver_share_config);
  if (g_pDsndDriver_timer_services == (int *)0x0) {
    (*(code *)g_pDsndDriver_share_services[8])(s_DirectSoundDriver_Module__Cannot_004f4018);
    return -1;
  }
  g_dwDsndDriver_memory_services =
       (*(code *)g_pDsndDriver_share_services[2])
                 (s_MEMORY_mixertable_004f4004,g_dwDsndDriver_share_config);
  if (g_dwDsndDriver_memory_services == 0) {
    (*(code *)g_pDsndDriver_share_services[8])(s_DirectSoundDriver_Module__Cannot_004f4018);
    return -1;
  }
  return 0;
}
#endif


/* ---- 0x004d2520  DsndDriver_module_shutdown ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Original name DsndDriver_module_shutdown (the remaster's GrimFandango (Linux): slot 3 of the
   "LECMODULE=insane_dsnd" service table; module_shutdown is a static several LEC modules have,
   written with the module prefix); was DsndDriver_Shutdown. */

void DsndDriver_module_shutdown(void)

{
  (*(code *)g_pDsndDriver_share_services[3])(g_pDsndDriver_timer_services);
  (*(code *)g_pDsndDriver_share_services[3])(g_dwDsndDriver_memory_services);
  return;
}
#endif


/* ---- 0x004d2550  dsn_initialize ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Opens DirectSound and the mixer and starts the periodic DSound_FillStreamBuffer timer Original
   name dsn_initialize (the remaster's GrimFandango (Linux): slot 0 of the "SNDDRIVER=insane_dsnd"
   service table); was DsndDriver_Open. */

int __cdecl dsn_initialize(int rate,int unused,void *mix)

{
  int iVar1;
  
  _DAT_008dcc3c = 0;
  if (rate < 0x5622) {
    rate = 0x5622;
  }
  iVar1 = DsndDriver_InitDirectSound();
  if (iVar1 != 0) {
    return -1;
  }
  iVar1 = Mixer_Init((int *)g_dwDsndDriver_memory_services,4,0x400);
  if (iVar1 != 0) {
    return -1;
  }
  g_pfnStreamMix = mix;
  g_dwStreamRate = rate;
  g_nStreamTimerId =
       (*(code *)*g_pDsndDriver_timer_services)
                 (DSound_FillStreamBuffer,
                  (int)(0x1234dc / (longlong)((int)(rate + (rate >> 0x1f & 0x3ffU)) >> 10)),2,0);
  return 0;
}
#endif


/* ---- 0x004d25f0  dsn_terminate ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Original name dsn_terminate (the remaster's GrimFandango (Linux): slot 1 of the
   "SNDDRIVER=insane_dsnd" service table); was DsndDriver_Close. */

void dsn_terminate(void)

{
  if (g_nStreamTimerId != 0) {
    (*(code *)g_pDsndDriver_timer_services[1])(g_nStreamTimerId);
  }
  g_nStreamTimerId = 0;
  sou_mixer_terminate(g_dwDsndDriver_memory_services);
  DsndDriver_ReleaseDirectSound();
  return;
}
#endif


/* ---- 0x004d2630  dsn_setvol ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Removing unreachable block (ram,0x004d2765) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Volume 0..127 through a logarithmic table to IDirectSoundBuffer::SetVolume on the stream buffer
   Original name dsn_setvol (the remaster's GrimFandango (Linux): slot 2 of the
   "SNDDRIVER=insane_dsnd" service table); was DsndDriver_SetVolume. */

void __cdecl dsn_setvol(uint volume)

{
  int iVar1;
  uint *puVar2;
  uint *puVar3;
  int iVar4;
  
  if (UINT_008dcc58 == 0) {
    UINT_008db210 = 0xffffd8f0;
    _DAT_008db214 = 0xffffe4a8;
    _DAT_008db218 = 0xffffe890;
    _DAT_008db21c = 0xffffebb0;
    _DAT_008db220 = 0xffffec78;
    _DAT_008db224 = 0xffffee6c;
    _DAT_008db228 = 0xffffef98;
    _DAT_008db22c = 0xffffeffc;
    UINT_008db230 = 0xfffff060;
    iVar4 = 16000;
    puVar2 = &UINT_008db230;
    do {
      iVar1 = iVar4 + -16000;
      puVar3 = puVar2 + 1;
      iVar4 = iVar4 + 2000;
      *puVar2 = iVar1 / 0x17 - 4000;
      puVar2 = puVar3;
    } while ((int)puVar3 < IMG_ADDR(0x008db290));
    iVar4 = 32000;
    puVar2 = &UINT_008db290;
    do {
      iVar1 = iVar4 + -32000;
      puVar3 = puVar2 + 1;
      iVar4 = iVar4 + 1000;
      *puVar2 = iVar1 / 0x1f - 2000;
      puVar2 = puVar3;
    } while ((int)puVar3 < IMG_ADDR(0x008db310));
    iVar4 = 64000;
    puVar2 = &UINT_008db310;
    do {
      iVar1 = iVar4 + -64000;
      puVar3 = puVar2 + 1;
      iVar4 = iVar4 + 1000;
      *puVar2 = iVar1 / 0x3f - 1000;
      puVar2 = puVar3;
    } while ((int)puVar3 < IMG_ADDR(0x008db410));
    UINT_008dcc58 = 1;
  }
  g_dwCurrentVol = volume & 0x7f;
  if (g_dwCurrentVol < 0x80) {
    (**(code_std **)(*(int *)g_pStreamDSBuffer + 0x3c))
              (g_pStreamDSBuffer,(&UINT_008db210)[g_dwCurrentVol]);
    return;
  }
  (**(code_std **)(*(int *)g_pStreamDSBuffer + 0x3c))(g_pStreamDSBuffer,UINT_008db40c);
  return;
}
#endif


/* ---- 0x004d27b0  dsn_getvol ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Original name dsn_getvol (the remaster's GrimFandango (Linux): slot 3 of the
   "SNDDRIVER=insane_dsnd" service table); was DsndDriver_GetVolume. */

uint dsn_getvol(void)

{
  return g_dwCurrentVol;
}
#endif


/* ---- 0x004d27c0  dsn_getrate ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Original name dsn_getrate (the remaster's GrimFandango (Linux): slot 5 of the
   "SNDDRIVER=insane_dsnd" service table); was DsndDriver_GetSampleRate. */

int dsn_getrate(void)

{
  return 0x5622;
}
#endif


/* ---- 0x004d2940  DsndDriver_InitDirectSound ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int DsndDriver_InitDirectSound(void)

{
  unsigned char _stkneg[48] __attribute__((aligned(16)));  /* the original frame below the return address */
  int iVar1;
  undefined4 uVar2;
  
  if (g_pStreamDS == (void *)0x0) {
    iVar1 = DirectSoundCreate(0,IMG_ADDR(0x008dcc40),0);
    if (iVar1 != 0) {
      g_pStreamDS = (void *)0x0;
      ((code *)Lua_Stub)(s_Cannot_create_DirectSound_object_004f40d0);
      return -1;
    }
    iVar1 = *(int *)g_pStreamDS;
    uVar2 = Win_GetMainHwnd();
    iVar1 = (**(code **)(iVar1 + 0x18))(g_pStreamDS,uVar2);
    if (iVar1 != 0) {
      ((code *)Lua_Stub)(s_DirectSound__Error__08X_while_se_004f4098,iVar1);
      if (iVar1 != 0) {
        return -1;
      }
    }
    iVar1 = (**(code_std **)(*(int *)g_pStreamDS + 0xc))
                      (g_pStreamDS,(_stkneg + 16),&g_pStreamDSPrimary,0);
    if (iVar1 != 0) {
      ((code *)Lua_Stub)(s_DirectSound__Error__08X_while_cr_004f4060,iVar1);
      if (iVar1 != 0) {
        return -1;
      }
    }
    iVar1 = (**(code_std **)(*(int *)g_pStreamDSPrimary + 0x38))(g_pStreamDSPrimary,&DAT_004f3fa8);
    if (iVar1 != 0) {
      return -1;
    }
    iVar1 = (**(code_std **)(*(int *)g_pStreamDSPrimary + 0x18))
                      (g_pStreamDSPrimary,&g_nStreamSavedVolume);
    if (iVar1 != 0) {
      return -1;
    }
    iVar1 = (**(code_std **)(*(int *)g_pStreamDSPrimary + 0x3c))(g_pStreamDSPrimary,0);
    if (iVar1 != 0) {
      return -1;
    }
    DsndDriver_CreateStreamBuffer(3);
    UINT_008dcc50 = 1;
  }
  return 0;
}
#endif


/* ---- 0x004d2aa0  DsndDriver_CreateStreamBuffer ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Creates the looping secondary stream buffer of N blocks of 0x1800 bytes (3..16), clears it and
   starts it */

void __cdecl DsndDriver_CreateStreamBuffer(int blocks)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *pvVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 **ppuVar5;
  undefined4 *puVar6;
  #define puStack_30 (*(undefined4 **)(_frame + (0x40 - 0x30)))
  #define ppvStack_2c (*(void ***)(_frame + (0x40 - 0x2c)))
  #define pvStack_28 (*(void **)(_frame + (0x40 - 0x28)))
  #define uStack_14 (*(undefined4 *)(_frame + (0x40 - 0x14)))
  #define uStack_10 (*(undefined4 *)(_frame + (0x40 - 0x10)))
  #define iStack_c (*(int *)(_frame + (0x40 - 0xc)))
  #define uStack_8 (*(undefined4 *)(_frame + (0x40 - 0x8)))
  #define puStack_4 (*(undefined **)(_frame + (0x40 - 0x4)))
  
  _DAT_008dcc4c = 1;
  if (g_pStreamDSBuffer != (void *)0x0) {
    pvStack_28 = g_pStreamDSBuffer;
    ppvStack_2c = (void **)0x4d2abd;
    (**(code_std **)(*(int *)g_pStreamDSBuffer + 8))();
  }
  pvVar1 = g_pStreamDS;
  g_pStreamDSBuffer = (void *)0x0;
  if (blocks < 3) {
    blocks = 3;
  }
  if (0x10 < blocks) {
    blocks = 0x10;
  }
  uStack_14 = 0x14;
  uStack_10 = 0x10080;
  iStack_c = blocks * 0x1800;
  uStack_8 = 0;
  pvStack_28 = (void *)0x0;
  puStack_30 = &uStack_14;
  puStack_4 = &DAT_004f3fc0;
  ppvStack_2c = &g_pStreamDSBuffer;
  g_nStreamBlocks = blocks;
  iVar2 = (**(code_std **)(*(int *)g_pStreamDS + 0xc))();
  if (iVar2 == 0) {
    (**(code_std **)(*(int *)g_pStreamDSBuffer + 0x3c))(g_pStreamDSBuffer);
    uVar3 = g_nStreamBlocks * 0x1800;
    iVar2 = (**(code_std **)(*(int *)g_pStreamDSBuffer + 0x2c))(g_pStreamDSBuffer);
    if (iVar2 == 0) {
      ppuVar5 = &puStack_30;
      for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *ppuVar5 = (undefined4 *)0x0;
        ppuVar5 = ppuVar5 + 1;
      }
      for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
        *(undefined1 *)ppuVar5 = 0;
        ppuVar5 = (undefined4 **)((int)ppuVar5 + 1);
      }
      if (pvVar1 != (void *)0x0) {
        puVar6 = pvVar1;
        for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar6 = 0;
          puVar6 = puVar6 + 1;
        }
        for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
          *(undefined1 *)puVar6 = 0;
          puVar6 = (undefined4 *)((int)puVar6 + 1);
        }
      }
      (**(code_std **)(*(int *)g_pStreamDSBuffer + 0x4c))(g_pStreamDSBuffer,&puStack_30,uVar3,pvVar1,0);
    }
    (**(code_std **)(*(int *)g_pStreamDSBuffer + 0x30))(g_pStreamDSBuffer,0,0,1);
  }
  _DAT_008dcc4c = 0;
  return;
}
#undef iStack_c
#undef ppvStack_2c
#undef puStack_30
#undef puStack_4
#undef pvStack_28
#undef uStack_10
#undef uStack_14
#undef uStack_8

#endif


/* ---- 0x004d2bf0  DsndDriver_ReleaseDirectSound ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void DsndDriver_ReleaseDirectSound(void)

{
  if (g_pStreamDSBuffer != (void *)0x0) {
    (**(code_std **)(*(int *)g_pStreamDSBuffer + 8))(g_pStreamDSBuffer);
  }
  g_pStreamDSBuffer = (void *)0x0;
  if ((g_pStreamDSPrimary != (void *)0x0) && (UINT_008dcc50 != 0)) {
    (**(code_std **)(*(int *)g_pStreamDSPrimary + 0x3c))(g_pStreamDSPrimary,g_nStreamSavedVolume);
    (**(code_std **)(*(int *)g_pStreamDSPrimary + 8))(g_pStreamDSPrimary);
    g_pStreamDSPrimary = (void *)0x0;
    UINT_008dcc50 = 0;
  }
  if (g_pStreamDS != (void *)0x0) {
    (**(code_std **)(*(int *)g_pStreamDS + 8))(g_pStreamDS);
  }
  g_pStreamDS = (void *)0x0;
  return;
}
#endif

