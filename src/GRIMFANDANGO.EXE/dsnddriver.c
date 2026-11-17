/* GRIMFANDANGO.EXE :: dsnddriver.c
 * functions 0x004d2420 .. 0x004d2bf0 (12 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004d2420  sou_dsnd_module ---- */
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

/* ---- 0x004d2480  DsndDriver_module_terminate ---- */
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

/* ---- 0x004d24b0  DsndDriver_module_startup ---- */
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

/* ---- 0x004d2520  DsndDriver_module_shutdown ---- */
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

/* ---- 0x004d2550  dsn_initialize ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Opens DirectSound and the mixer and starts the periodic dsn_fill_thread timer Original name
   dsn_initialize (the remaster's GrimFandango (Linux): slot 0 of the "SNDDRIVER=insane_dsnd"
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
  iVar1 = sou_mixer_initialize((int *)g_dwDsndDriver_memory_services,4,0x400);
  if (iVar1 != 0) {
    return -1;
  }
  g_pfnStreamMix = mix;
  g_dwStreamRate = rate;
  g_nStreamTimerId =
       (*(code *)*g_pDsndDriver_timer_services)
                 (dsn_fill_thread,
                  (int)(0x1234dc / (longlong)((int)(rate + (rate >> 0x1f & 0x3ffU)) >> 10)),2,0);
  return 0;
}

/* ---- 0x004d25f0  dsn_terminate ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Original name dsn_terminate (the remaster's GrimFandango (Linux): slot 1 of the
   "SNDDRIVER=insane_dsnd" service table); was DsndDriver_Close. */

void dsn_terminate(void)

{
  if (g_nStreamTimerId != 0) {
    (*(code *)g_pDsndDriver_timer_services[1])(g_nStreamTimerId);
  }
  g_nStreamTimerId = 0;
  sou_mixer_terminate((int *)g_dwDsndDriver_memory_services);
  DsndDriver_ReleaseDirectSound();
  return;
}

/* ---- 0x004d2630  dsn_setvol ---- */
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
    } while ((int)puVar3 < ((unsigned)(uintptr_t)&UINT_008db290));
    iVar4 = 32000;
    puVar2 = &UINT_008db290;
    do {
      iVar1 = iVar4 + -32000;
      puVar3 = puVar2 + 1;
      iVar4 = iVar4 + 1000;
      *puVar2 = iVar1 / 0x1f - 2000;
      puVar2 = puVar3;
    } while ((int)puVar3 < ((unsigned)(uintptr_t)&UINT_008db310));
    iVar4 = 64000;
    puVar2 = &UINT_008db310;
    do {
      iVar1 = iVar4 + -64000;
      puVar3 = puVar2 + 1;
      iVar4 = iVar4 + 1000;
      *puVar2 = iVar1 / 0x3f - 1000;
      puVar2 = puVar3;
    } while ((int)puVar3 < ((unsigned)(uintptr_t)&g_pfnStreamMix));
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

/* ---- 0x004d27b0  dsn_getvol ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Original name dsn_getvol (the remaster's GrimFandango (Linux): slot 3 of the
   "SNDDRIVER=insane_dsnd" service table); was DsndDriver_GetVolume. */

uint dsn_getvol(void)

{
  return g_dwCurrentVol;
}

/* ---- 0x004d27c0  dsn_getrate ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Original name dsn_getrate (the remaster's GrimFandango (Linux): slot 5 of the
   "SNDDRIVER=insane_dsnd" service table); was DsndDriver_GetSampleRate. */

int dsn_getrate(void)

{
  return 0x5622;
}

/* ---- 0x004d2940  DsndDriver_InitDirectSound ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int DsndDriver_InitDirectSound(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  void *a1;
  undefined4 a2;
  #define uStack_14 (*(undefined4 *)(_frame + (0x30 - 0x14)))
  #define uStack_10 (*(undefined4 *)(_frame + (0x30 - 0x10)))
  #define uStack_c (*(undefined4 *)(_frame + (0x30 - 0xc)))
  #define uStack_8 (*(undefined4 *)(_frame + (0x30 - 0x8)))
  #define uStack_4 (*(undefined4 *)(_frame + (0x30 - 0x4)))
  
  if (g_pStreamDS == (void *)0x0) {
    iVar1 = DirectSoundCreate(0,((unsigned)(uintptr_t)&g_pStreamDS),0);
    if (iVar1 != 0) {
      g_pStreamDS = (void *)0x0;
      Lua_Stub(s_Cannot_create_DirectSound_object_004f40d0,iVar1);
      return -1;
    }
    a2 = 3;
    iVar1 = *(int *)g_pStreamDS;
    a1 = Win_GetMainHwnd();
    iVar1 = (**(code **)(iVar1 + 0x18))(g_pStreamDS,a1,a2);
    if (iVar1 != 0) {
      Lua_Stub(s_DirectSound__Error__08X_while_se_004f4098,iVar1);
      if (iVar1 != 0) {
        return -1;
      }
    }
    uStack_14 = 0x14;
    uStack_10 = 0x81;
    uStack_c = 0;
    uStack_8 = 0;
    uStack_4 = 0;
    iVar1 = (**(code_std **)(*(int *)g_pStreamDS + 0xc))(g_pStreamDS,&uStack_14,&g_pStreamDSPrimary,0);
    if (iVar1 != 0) {
      Lua_Stub(s_DirectSound__Error__08X_while_cr_004f4060,iVar1);
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
#undef uStack_10
#undef uStack_14
#undef uStack_4
#undef uStack_8
#undef uStack_c


/* ---- 0x004d2aa0  DsndDriver_CreateStreamBuffer ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Creates the looping secondary stream buffer of N blocks of 0x1800 bytes (3..16), clears it and
   starts it */

void __cdecl DsndDriver_CreateStreamBuffer(int blocks)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  #define uStack_20 (*(uint *)(_frame + (0x30 - 0x20)))
  #define uStack_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define puStack_18 (*(undefined4 **)(_frame + (0x30 - 0x18)))
  #define uStack_14 (*(undefined4 *)(_frame + (0x30 - 0x14)))
  #define uStack_10 (*(undefined4 *)(_frame + (0x30 - 0x10)))
  #define iStack_c (*(int *)(_frame + (0x30 - 0xc)))
  #define uStack_8 (*(undefined4 *)(_frame + (0x30 - 0x8)))
  #define puStack_4 (*(undefined **)(_frame + (0x30 - 0x4)))
  
  _DAT_008dcc4c = 1;
  if (g_pStreamDSBuffer != (void *)0x0) {
    (**(code_std **)(*(int *)g_pStreamDSBuffer + 8))(g_pStreamDSBuffer);
  }
  g_pStreamDSBuffer = (void *)0x0;
  g_nStreamBlocks = blocks;
  if (blocks < 3) {
    g_nStreamBlocks = 3;
  }
  if (0x10 < g_nStreamBlocks) {
    g_nStreamBlocks = 0x10;
  }
  uStack_14 = 0x14;
  uStack_10 = 0x10080;
  iStack_c = g_nStreamBlocks * 0x1800;
  uStack_8 = 0;
  puStack_4 = &DAT_004f3fc0;
  iVar1 = (**(code_std **)(*(int *)g_pStreamDS + 0xc))(g_pStreamDS,&uStack_14,&g_pStreamDSBuffer,0);
  if (iVar1 == 0) {
    (**(code_std **)(*(int *)g_pStreamDSBuffer + 0x3c))(g_pStreamDSBuffer,0);
    iVar1 = (**(code_std **)(*(int *)g_pStreamDSBuffer + 0x2c))
                      (g_pStreamDSBuffer,0,g_nStreamBlocks * 0x1800,&puStack_18,&uStack_1c,&blocks,
                       &uStack_20,0);
    if (iVar1 == 0) {
      puVar3 = puStack_18;
      for (uVar2 = uStack_1c >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar3 = 0;
        puVar3 = puVar3 + 1;
      }
      for (uVar2 = uStack_1c & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *(undefined1 *)puVar3 = 0;
        puVar3 = (undefined4 *)((int)puVar3 + 1);
      }
      if (blocks != 0) {
        puVar3 = (undefined4 *)blocks;
        for (uVar2 = uStack_20 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
          *puVar3 = 0;
          puVar3 = puVar3 + 1;
        }
        for (uVar2 = uStack_20 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
          *(undefined1 *)puVar3 = 0;
          puVar3 = (undefined4 *)((int)puVar3 + 1);
        }
      }
      (**(code_std **)(*(int *)g_pStreamDSBuffer + 0x4c))
                (g_pStreamDSBuffer,puStack_18,uStack_1c,blocks,uStack_20);
    }
    (**(code_std **)(*(int *)g_pStreamDSBuffer + 0x30))(g_pStreamDSBuffer,0,0,1);
  }
  _DAT_008dcc4c = 0;
  return;
}
#undef iStack_c
#undef puStack_18
#undef puStack_4
#undef uStack_10
#undef uStack_14
#undef uStack_1c
#undef uStack_20
#undef uStack_8


/* ---- 0x004d2bf0  DsndDriver_ReleaseDirectSound ---- */
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


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern char f_DsndDriver_module_shutdown[] __asm__("_DsndDriver_module_shutdown");
extern char f_DsndDriver_module_startup[] __asm__("_DsndDriver_module_startup");
extern char f_DsndDriver_module_terminate[] __asm__("_DsndDriver_module_terminate");
extern char f_LecShare_Nop[] __asm__("_LecShare_Nop");
extern char f_dsn_getrate[] __asm__("_dsn_getrate");
extern char f_dsn_getvol[] __asm__("_dsn_getvol");
extern char f_dsn_initialize[] __asm__("_dsn_initialize");
extern char f_dsn_setvol[] __asm__("_dsn_setvol");
extern char f_dsn_terminate[] __asm__("_dsn_terminate");
extern char f_sou_dsnd_module[] __asm__("_sou_dsnd_module");
extern unsigned char grim_def_DAT_004f3fa8[24] __asm__("_DAT_004f3fa8");
extern unsigned char grim_def_DAT_004f3fc0[20] __asm__("_DAT_004f3fc0");
extern unsigned char grim_def_DAT_008db20c[4] __asm__("_DAT_008db20c");
extern unsigned char grim_def_DAT_008db214[4] __asm__("_DAT_008db214");
extern unsigned char grim_def_DAT_008db218[4] __asm__("_DAT_008db218");
extern unsigned char grim_def_DAT_008db21c[4] __asm__("_DAT_008db21c");
extern unsigned char grim_def_DAT_008db220[4] __asm__("_DAT_008db220");
extern unsigned char grim_def_DAT_008db224[4] __asm__("_DAT_008db224");
extern unsigned char grim_def_DAT_008db228[4] __asm__("_DAT_008db228");
extern unsigned char grim_def_DAT_008db22c[4] __asm__("_DAT_008db22c");
extern unsigned char grim_def_DAT_008db414[4] __asm__("_DAT_008db414");
extern unsigned char grim_def_DAT_008db42c[4] __asm__("_DAT_008db42c");
extern unsigned char grim_def_DAT_008dcc38[4] __asm__("_DAT_008dcc38");
extern unsigned char grim_def_DAT_008dcc3c[4] __asm__("_DAT_008dcc3c");
extern unsigned char grim_def_DAT_008dcc4c[4] __asm__("_DAT_008dcc4c");
extern unsigned int grim_def_UINT_008db210 __asm__("_UINT_008db210");
extern unsigned char grim_def_UINT_008db230[96] __asm__("_UINT_008db230");
extern unsigned char grim_def_UINT_008db290[128] __asm__("_UINT_008db290");
extern unsigned char grim_def_UINT_008db310[252] __asm__("_UINT_008db310");
extern unsigned int grim_def_UINT_008db40c __asm__("_UINT_008db40c");
extern unsigned int grim_def_UINT_008dcc50 __asm__("_UINT_008dcc50");
extern unsigned char grim_def_UINT_008dcc58[8] __asm__("_UINT_008dcc58");
extern void *grim_def_g_apfnDsndDriverModule[4] __asm__("_g_apfnDsndDriverModule");
extern unsigned int grim_def_g_dwCurrentVol __asm__("_g_dwCurrentVol");
extern unsigned int grim_def_g_dwDsndDriver_memory_services __asm__("_g_dwDsndDriver_memory_services");
extern unsigned int grim_def_g_dwDsndDriver_share_config __asm__("_g_dwDsndDriver_share_config");
extern int grim_def_g_nStreamSavedVolume __asm__("_g_nStreamSavedVolume");
extern unsigned char grim_def_g_pDsndDriver_share_services[4] __asm__("_g_pDsndDriver_share_services");
extern void *grim_def_g_pDsndDriver_snddriver_services[7] __asm__("_g_pDsndDriver_snddriver_services");
extern unsigned char grim_def_g_pStreamDS[4] __asm__("_g_pStreamDS");
extern unsigned char grim_def_g_pStreamDSPrimary[4] __asm__("_g_pStreamDSPrimary");
extern char grim_def_s_Cannot_create_DirectSound_object_004f40d0[40] __asm__("_s_Cannot_create_DirectSound_object_004f40d0");
extern char grim_def_s_DirectSoundDriver_Module__Cannot_004f4018[60] __asm__("_s_DirectSoundDriver_Module__Cannot_004f4018");
extern char grim_def_s_DirectSound__Error__08X_while_cr_004f4060[56] __asm__("_s_DirectSound__Error__08X_while_cr_004f4060");
extern char grim_def_s_DirectSound__Error__08X_while_se_004f4098[56] __asm__("_s_DirectSound__Error__08X_while_se_004f4098");
extern char grim_def_s_LECMODULE_insane_dsnd_004f3fec[24] __asm__("_s_LECMODULE_insane_dsnd_004f3fec");
extern char grim_def_s_MEMORY_mixertable_004f4004[20] __asm__("_s_MEMORY_mixertable_004f4004");
extern char grim_def_s_SNDDRIVER_insane_dsnd_004f3fd4[24] __asm__("_s_SNDDRIVER_insane_dsnd_004f3fd4");
extern char grim_def_s_TIMER_clock_004f4054[12] __asm__("_s_TIMER_clock_004f4054");
static unsigned char grim_anchor_004f3f68[0] __attribute__((section(".data$grim_004f3f68"), aligned(16), used));
static unsigned char grim_pad_004f3f68[8] __attribute__((section(".data$grim_004f3f68_"), aligned(4), used));
/* 0x004f3f68, 16 bytes */ GRIM_DATA("004f3f68z") void *grim_def_g_apfnDsndDriverModule[4] __asm__("_g_apfnDsndDriverModule") = {
    (void *)f_sou_dsnd_module, (void *)f_DsndDriver_module_terminate, (void *)f_DsndDriver_module_startup, (void *)f_DsndDriver_module_shutdown
};
/* 0x004f3f78, 28 bytes */ GRIM_DATA("004f3f78") void *grim_def_g_pDsndDriver_snddriver_services[7] __asm__("_g_pDsndDriver_snddriver_services") = {
    (void *)f_dsn_initialize, (void *)f_dsn_terminate, (void *)f_dsn_setvol, (void *)f_dsn_getvol,
    (void *)f_LecShare_Nop, (void *)f_dsn_getrate, (void *)0xffffffff
};
/* 0x004f3f9c, 4 bytes */ GRIM_DATA("004f3f9c") unsigned int grim_def_g_dwCurrentVol __asm__("_g_dwCurrentVol") = 0x7f;
/* 0x004f3fa0, 8 bytes */ GRIM_DATA("004f3fa0") int grim_def_g_nStreamSavedVolume __asm__("_g_nStreamSavedVolume") = -5000;
/* 0x004f3fa4, 4 bytes: the rest of grim_def_g_nStreamSavedVolume's span */ GRIM_DATA("004f3fa0") static unsigned char g_nStreamSavedVolume__tail[4] __attribute__((used)) = {0};
/* 0x004f3fa8, 24 bytes */ GRIM_DATA("004f3fa8") unsigned char grim_def_DAT_004f3fa8[24] __asm__("_DAT_004f3fa8") = { 0x01, 0x00, 0x02, 0x00, 0x22, 0x56, 0x00, 0x00, 0x88, 0x58, 0x01, 0x00, 0x04, 0x00, 0x10 };
/* 0x004f3fc0, 20 bytes */ GRIM_DATA("004f3fc0") unsigned char grim_def_DAT_004f3fc0[20] __asm__("_DAT_004f3fc0") = { 0x01, 0x00, 0x02, 0x00, 0x22, 0x56, 0x00, 0x00, 0x88, 0x58, 0x01, 0x00, 0x04, 0x00, 0x10 };
/* 0x004f3fd4, 24 bytes */ GRIM_DATA("004f3fd4") char grim_def_s_SNDDRIVER_insane_dsnd_004f3fd4[24] __asm__("_s_SNDDRIVER_insane_dsnd_004f3fd4") = "SNDDRIVER=insane_dsnd";
/* 0x004f3fec, 24 bytes */ /* loose */ char grim_def_s_LECMODULE_insane_dsnd_004f3fec[24] __asm__("_s_LECMODULE_insane_dsnd_004f3fec") = "LECMODULE=insane_dsnd";
/* 0x004f4004, 20 bytes */ /* loose */ char grim_def_s_MEMORY_mixertable_004f4004[20] __asm__("_s_MEMORY_mixertable_004f4004") = "MEMORY.mixertable";
/* 0x004f4018, 60 bytes */ /* loose */ char grim_def_s_DirectSoundDriver_Module__Cannot_004f4018[60] __asm__("_s_DirectSoundDriver_Module__Cannot_004f4018") = "DirectSoundDriver Module: Cannot allocate timer services.";
/* 0x004f4054, 12 bytes */ /* loose */ char grim_def_s_TIMER_clock_004f4054[12] __asm__("_s_TIMER_clock_004f4054") = "TIMER=clock";
/* 0x004f4060, 56 bytes */ /* loose */ char grim_def_s_DirectSound__Error__08X_while_cr_004f4060[56] __asm__("_s_DirectSound__Error__08X_while_cr_004f4060") = "DirectSound: Error %08X while creating primary buffer";
/* 0x004f4098, 56 bytes */ /* loose */ char grim_def_s_DirectSound__Error__08X_while_se_004f4098[56] __asm__("_s_DirectSound__Error__08X_while_se_004f4098") = "DirectSound: Error %08X while setting cooperative level";
/* 0x004f40d0, 40 bytes */ /* loose */ char grim_def_s_Cannot_create_DirectSound_object_004f40d0[40] __asm__("_s_Cannot_create_DirectSound_object_004f40d0") = "Cannot create DirectSound object (%d)";
/* 0x008db208, 4 bytes */ /* loose */ unsigned int grim_def_g_dwDsndDriver_memory_services __asm__("_g_dwDsndDriver_memory_services") = 0x0;
static unsigned char grim_anchor_008db20c[0] __attribute__((section(".data$grim_008db20c"), aligned(16), used));
static unsigned char grim_pad_008db20c[12] __attribute__((section(".data$grim_008db20c_"), aligned(4), used));
/* 0x008db20c, 4 bytes */ GRIM_DATA("008db20cz") unsigned char grim_def_DAT_008db20c[4] __asm__("_DAT_008db20c") = {0};
/* 0x008db210, 4 bytes */ GRIM_DATA("008db210") unsigned int grim_def_UINT_008db210 __asm__("_UINT_008db210") = 0x0;
/* 0x008db214, 4 bytes */ GRIM_DATA("008db214") unsigned char grim_def_DAT_008db214[4] __asm__("_DAT_008db214") = {0};
/* 0x008db218, 4 bytes */ GRIM_DATA("008db218") unsigned char grim_def_DAT_008db218[4] __asm__("_DAT_008db218") = {0};
/* 0x008db21c, 4 bytes */ GRIM_DATA("008db21c") unsigned char grim_def_DAT_008db21c[4] __asm__("_DAT_008db21c") = {0};
/* 0x008db220, 4 bytes */ GRIM_DATA("008db220") unsigned char grim_def_DAT_008db220[4] __asm__("_DAT_008db220") = {0};
/* 0x008db224, 4 bytes */ GRIM_DATA("008db224") unsigned char grim_def_DAT_008db224[4] __asm__("_DAT_008db224") = {0};
/* 0x008db228, 4 bytes */ GRIM_DATA("008db228") unsigned char grim_def_DAT_008db228[4] __asm__("_DAT_008db228") = {0};
/* 0x008db22c, 4 bytes */ GRIM_DATA("008db22c") unsigned char grim_def_DAT_008db22c[4] __asm__("_DAT_008db22c") = {0};
/* 0x008db230, 96 bytes */ GRIM_DATA("008db230") unsigned char grim_def_UINT_008db230[96] __asm__("_UINT_008db230") = {0};
/* 0x008db290, 128 bytes */ GRIM_DATA("008db290") unsigned char grim_def_UINT_008db290[128] __asm__("_UINT_008db290") = {0};
/* 0x008db310, 252 bytes */ GRIM_DATA("008db310") unsigned char grim_def_UINT_008db310[252] __asm__("_UINT_008db310") = {0};
/* 0x008db40c, 4 bytes */ GRIM_DATA("008db40c") unsigned int grim_def_UINT_008db40c __asm__("_UINT_008db40c") = 0x0;
/* 0x008db414, 4 bytes */ GRIM_DATA("008db414") unsigned char grim_def_DAT_008db414[4] __asm__("_DAT_008db414") = {0};
/* 0x008db41c, 4 bytes */ GRIM_DATA("008db41c") unsigned char grim_def_g_pDsndDriver_share_services[4] __asm__("_g_pDsndDriver_share_services") = {0};
/* 0x008db42c, 4 bytes */ GRIM_DATA("008db42c") unsigned char grim_def_DAT_008db42c[4] __asm__("_DAT_008db42c") = {0};
/* 0x008db430, 8 bytes */ GRIM_DATA("008db430") unsigned int grim_def_g_dwDsndDriver_share_config __asm__("_g_dwDsndDriver_share_config") = 0x0;
/* 0x008db434, 4 bytes: the rest of grim_def_g_dwDsndDriver_share_config's span */ GRIM_DATA("008db430") static unsigned char g_dwDsndDriver_share_config__tail[4] __attribute__((used)) = {0};
/* 0x008dcc38, 4 bytes */ GRIM_DATA("008dcc38") unsigned char grim_def_DAT_008dcc38[4] __asm__("_DAT_008dcc38") = {0};
/* 0x008dcc3c, 4 bytes */ GRIM_DATA("008dcc3c") unsigned char grim_def_DAT_008dcc3c[4] __asm__("_DAT_008dcc3c") = {0};
/* 0x008dcc40, 4 bytes */ GRIM_DATA("008dcc40") unsigned char grim_def_g_pStreamDS[4] __asm__("_g_pStreamDS") = {0};
/* 0x008dcc44, 4 bytes */ GRIM_DATA("008dcc44") unsigned char grim_def_g_pStreamDSPrimary[4] __asm__("_g_pStreamDSPrimary") = {0};
/* 0x008dcc4c, 4 bytes */ GRIM_DATA("008dcc4c") unsigned char grim_def_DAT_008dcc4c[4] __asm__("_DAT_008dcc4c") = {0};
/* 0x008dcc50, 4 bytes */ GRIM_DATA("008dcc50") unsigned int grim_def_UINT_008dcc50 __asm__("_UINT_008dcc50") = 0x0;
/* 0x008dcc58, 8 bytes */ GRIM_DATA("008dcc58") unsigned char grim_def_UINT_008dcc58[8] __asm__("_UINT_008dcc58") = {0};
