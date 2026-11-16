/* GRIMFANDANGO.EXE :: insane.c
 * functions 0x004bd370 .. 0x004c3e10 (13 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004bd370  SmushPlay_GetMovieTime ---- */
/* INSANE (SMUSH) movie player glue: steps the player when the file io, decoder and output modules
   are all registered Original name SmushPlay_GetMovieTime (the remaster's GrimFandango (Linux):
   tests fSmushPlaySysInitialized and fSmushPlaySysStarted and returns the playing movie's time
   (sputLua_Update's movieTimeMsec)); was Insane_Poll. */

int __cdecl SmushPlay_GetMovieTime(void)

{
  int iVar1;
  
  if (((g_dwSmushPlaySysInitialized != 0) && (g_dwSmushPlaySysStarted != 0)) &&
     (g_dwMovieIsPlaying != 0)) {
    iVar1 = sou_engine_QueryTime(0);
    return iVar1;
  }
  return 0;
}

/* ---- 0x004bd3a0  SmushPlay_SysInitialize ---- */
/* Registers the 'FILIO' LecShare module ('insane zfilio') and fills the caller's vtable with the
   open/read/seek/close entry points Original name SmushPlay_SysInitialize (the remaster's
   GrimFandango (Linux): stores pSmushPlayHS, LecShare_Initialize(0, modules, "FILIO=insane_zfilio",
   ...), sets fSmushPlaySysInitialized, fills the module interface {Initialize, Terminate, Startup,
   Shutdown}); was Insane_RegisterFilio. */

uint __cdecl SmushPlay_SysInitialize(uint services,undefined4 *smushPlayMS)

{
  uint uVar1;
  
  g_dwSmushPlayHS = services;
  uVar1 = 1;
  if (g_dwSmushPlaySysInitialized == 0) {
    g_pSmushPlay_share_services =
         (int *)LecShare_Initialize((undefined *)0x0,&g_pShl_modules,((unsigned)(uintptr_t)&s_FILIO_insane_zfilio_004f0ca0),((unsigned)(uintptr_t)&DAT_004f5a98));
    if ((undefined **)g_pSmushPlay_share_services == (undefined **)0x0) {
      return 1;
    }
    g_dwSmushPlaySysInitialized = 1;
    if (smushPlayMS != (undefined4 *)0x0) {
      *smushPlayMS = SmushPlay_SysInitialize;
      smushPlayMS[1] = SmushPlay_SysTerminate;
      smushPlayMS[2] = SmushPlay_SysStartup;
      smushPlayMS[3] = SmushPlay_SysShutdown;
      smushPlayMS[4] = 0;
      smushPlayMS[5] = 0;
      smushPlayMS[6] = 0;
      smushPlayMS[7] = 0;
    }
    uVar1 = 0;
  }
  return uVar1;
}

/* ---- 0x004bd430  SmushPlay_SysTerminate ---- */
/* Module interface slot 1 (Insane): called by Engine_ResetSubsystems / when registration fails;
   drops the service table pointer and clears the initialised flag. Original name
   SmushPlay_SysShutdown (the remaster's GrimFandango (Linux): the only unmatched caller of
   LecShare_Shutdown; 1 matched neighbours agree, 0 disagree); was Insane_Terminate. Original name
   SmushPlay_SysTerminate (the remaster's GrimFandango (Linux): slot 1 of the SmushPlay module
   interface SmushPlay_SysInitialize fills; clears fSmushPlaySysInitialized after
   LecShare_Terminate); was SmushPlay_SysShutdown. */

void __cdecl SmushPlay_SysTerminate(void)

{
  LecShare_Terminate();
  g_dwSmushPlaySysInitialized = 0;
  return;
}

/* ---- 0x004bd440  SmushPlay_SysStartup ---- */
/* Module interface slot 2 (Insane): called by Engine_InitSubsystems, returns 0 on success (non-zero
   makes the whole start-up unwind). _Start starts the LecShare module chain of the INSANE/Smush
   player. Original name SmushPlay_SysStartup (the remaster's GrimFandango (Linux): strings: '.SNM'
   | '.gz' | '.GZ'); was Insane_Start. */

uint __cdecl SmushPlay_SysStartup(void)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = 1;
  if ((g_dwSmushPlaySysInitialized != 0) && (g_dwSmushPlaySysStarted == 0)) {
    fle_zfilio_config(1,s__snm_004f0cc4,0);
    fle_zfilio_config(1,s__SNM_004f0cbc,0);
    fle_zfilio_config(1,s__GZ_004f0cb8,0);
    fle_zfilio_config(1,s__gz_004f0cb4,0);
    iVar1 = LecShare_Startup();
    if (iVar1 == 0) {
      iVar1 = (*(code *)g_pSmushPlay_share_services[4])(&g_pSubscription_info,0);
      if (iVar1 == 0) {
        g_dwSmushPlaySysStarted = 1;
        uVar2 = 0;
      }
    }
  }
  return uVar2;
}

/* ---- 0x004bd4d0  SmushPlay_SysShutdown ---- */
/* Module interface slot 3 (Insane): called by Engine_ShutdownSubsystems in reverse order; releases
   what _Start created. Original name SmushPlay_SysShutdown (the remaster's GrimFandango (Linux):
   slot 3 of the module interface; clears fSmushPlaySysStarted after LecShare_Shutdown
   (share_services +0x14 unsubscribe first)); was Insane_Stop. */

void __cdecl SmushPlay_SysShutdown(void)

{
  if (g_dwSmushPlaySysStarted != 0) {
    (*(code *)g_pSmushPlay_share_services[5])(&g_pSubscription_info);
    LecShare_Shutdown();
    g_dwSmushPlaySysStarted = 0;
  }
  return;
}

/* ---- 0x004bd540  SmushPlay_SysSetVideoCallbacks ---- */
/* Copies six dwords (destination surface geometry) into g_InsaneOutput Original name
   SmushPlay_SysSetVideoCallbacks (the remaster's GrimFandango (Linux): aligned call in
   sputSmush_Initialize); was Insane_SetOutputParams. */

void __cdecl SmushPlay_SysSetVideoCallbacks(uint *sputVideoCallBacks)

{
  int iVar1;
  uint *puVar2;
  
  puVar2 = &g_dwVideoCallbacks;
  for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *sputVideoCallBacks;
    sputVideoCallBacks = sputVideoCallBacks + 1;
    puVar2 = puVar2 + 1;
  }
  return;
}

/* ---- 0x004bd7c0  smushplay_GetInfo ---- */
/* Reads a packed 0x16-byte header field by field through the file io vtable at g_pInsaneFileOps
   Original name smushplay_GetInfo (the remaster's GrimFandango (Linux): aligned call in
   SmushPlay_GetMovieLength); was Insane_ReadFrameHeader. */

uint __cdecl smushplay_GetInfo(int file,int header)

{
  undefined4 uVar1;
  
  if (file == 0) {
    return 0;
  }
  uVar1 = (*(code *)g_pSmushPlay_file_services[4])(file);
  (*(code *)g_pSmushPlay_file_services[5])(file,0x10,0);
  (*(code *)g_pSmushPlay_file_services[2])(file,header,1);
  (*(code *)g_pSmushPlay_file_services[2])(file,header + 1,1);
  (*(code *)g_pSmushPlay_file_services[2])(file,header + 2,2);
  (*(code *)g_pSmushPlay_file_services[2])(file,header + 4,2);
  (*(code *)g_pSmushPlay_file_services[2])(file,header + 6,2);
  (*(code *)g_pSmushPlay_file_services[2])(file,(short *)(header + 8),2);
  (*(code *)g_pSmushPlay_file_services[2])(file,(short *)(header + 10),2);
  (*(code *)g_pSmushPlay_file_services[2])(file,header + 0xc,2);
  (*(code *)g_pSmushPlay_file_services[2])(file,header + 0xe,4);
  (*(code *)g_pSmushPlay_file_services[2])(file,(int *)(header + 0x12),4);
  (*(code *)g_pSmushPlay_file_services[2])(file,header + 0x16,0x400);
  (*(code *)g_pSmushPlay_file_services[2])(file,header + 0x416,2);
  if (((0 < *(short *)(header + 8)) && (0 < *(short *)(header + 10))) &&
     (0 < *(int *)(header + 0x12))) {
    (*(code *)g_pSmushPlay_file_services[5])(file,uVar1,0);
    return 0;
  }
  return 0xfffffffe;
}

/* ---- 0x004bdb00  Insane_PrepareFrame ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Validates the frame against the output size and chooses the blit mode bits in g_dwInsaneBlitFlags
    */

uint __cdecl Insane_PrepareFrame(int *player,undefined4 *smush_pInternalBitmap,uint *rect)

{
  uint uVar1;
  int srcPitch;
  uint *src;
  int iVar2;
  int width;
  int iVar3;
  int iVar4;
  uint *dst;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint local_18;
  uint local_14;
  uint local_8;
  
  if ((player != (int *)0x0) && (smush_pInternalBitmap != (undefined4 *)0x0)) {
    _DAT_008d16c0 = 0;
    if ((_g_bMovieFlags & 1) != 0) {
      _g_bMovieFlags = _g_bMovieFlags & 0xfffffff9;
      if ((int)rect[2] / 2 < (int)UINT_008d11e8) {
        if ((int)UINT_008d11ec < (int)rect[3]) {
          _g_bMovieFlags = _g_bMovieFlags | 2;
        }
      }
      else {
        _g_bMovieFlags = _g_bMovieFlags | 4;
      }
    }
    iVar5 = ((_g_bMovieFlags & 6) != 0) + 1;
    iVar3 = ((_g_bMovieFlags & 4) != 0) + 1;
    iVar4 = iVar3 * UINT_008d11e8;
    iVar2 = UINT_008d11ec * iVar5;
    uVar1 = *rect;
    uVar7 = UINT_008d11e0;
    if ((int)UINT_008d11e0 < (int)uVar1) {
      iVar4 = iVar4 + (UINT_008d11e0 - uVar1);
      uVar7 = uVar1;
    }
    if ((int)(uVar1 + rect[2]) < (int)(uVar7 + iVar4)) {
      iVar4 = (uVar1 + rect[2]) - uVar7;
    }
    uVar1 = rect[1];
    uVar6 = UINT_008d11e4;
    if ((int)UINT_008d11e4 < (int)uVar1) {
      iVar2 = iVar2 + (UINT_008d11e4 - uVar1);
      uVar6 = uVar1;
    }
    if ((int)(uVar1 + rect[3]) < (int)(uVar6 + iVar2)) {
      iVar2 = (uVar1 + rect[3]) - uVar6;
    }
    iVar2 = iVar2 / iVar5;
    srcPitch = smush_pInternalBitmap[5];
    width = (iVar4 / iVar3) * smush_pInternalBitmap[3];
    iVar4 = player[5];
    src = (uint *)*smush_pInternalBitmap;
    dst = (uint *)(player[3] * uVar7 * iVar3 + uVar6 * iVar5 * iVar4 + *player);
    if ((_g_bMovieFlags & 4) == 0) {
      if ((_g_bMovieFlags & 2) == 0) {
        Insane_BlitRows16((ushort *)src,srcPitch,(int)dst,iVar4,width,iVar2);
      }
      else {
        Insane_BlitRowsDual((int)src,srcPitch,dst,iVar4,width,iVar2);
      }
    }
    else {
      Insane_Blit8To16Doubled(src,srcPitch,dst,iVar4,width,iVar2);
    }
  }
  _DAT_008d16ac = 0;
  return 0;
}

/* ---- 0x004bdca0  Insane_Blit8To16Doubled ---- */
/* Pixel-doubling conversion of 8-bit frame rows into a 16-bit destination */

void __cdecl
Insane_Blit8To16Doubled(uint *src,int srcPitch,uint *dst,int dstPitch,int width,int rows)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  uint local_14;
  uint local_10;
  uint local_c;
  uint local_8;
  
  local_10 = 0;
  do {
    iVar1 = (int)src + width;
    do {
      uVar3 = *src;
      uVar2 = (uVar3 & 0xff00) << 8 | uVar3 & 0xff;
      uVar2 = uVar2 << 8 | uVar2;
      *dst = uVar2;
      puVar4 = (uint *)((int)dst + dstPitch);
      uVar3 = uVar3 & 0xff000000 | uVar3 >> 8 & 0xff00;
      *puVar4 = uVar2;
      src = src + 1;
      uVar3 = uVar3 | uVar3 >> 8;
      puVar4[1] = uVar3;
      dst = (uint *)((int)puVar4 + (8 - dstPitch));
      dst[-1] = uVar3;
    } while ((int)src < iVar1);
    src = (uint *)((int)src + (srcPitch - width));
    dst = (uint *)((int)dst + width * -2 + dstPitch * 2);
    local_10 = local_10 + 1;
  } while ((int)local_10 < rows);
  return;
}

/* ---- 0x004bdd50  Insane_BlitRowsDual ---- */
/* Copies frame rows to two destinations (front and back buffer) */

void __cdecl
Insane_BlitRowsDual(int src,int srcPitch,undefined4 *dst,int dstPitch,int width,int rows)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  
  for (; rows != 0; rows = rows + -1) {
    if (width >> 2 != 0) {
      puVar2 = dst;
      iVar3 = width >> 2;
      do {
        uVar1 = *(undefined4 *)((int)puVar2 + (src - (int)dst));
        *(undefined4 *)((int)puVar2 + dstPitch) = uVar1;
        *puVar2 = uVar1;
        puVar2 = puVar2 + 1;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    src = src + srcPitch;
    dst = (undefined4 *)((int)dst + dstPitch * 2);
  }
  return;
}

/* ---- 0x004bddb0  Insane_BlitRows16 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void __cdecl Insane_BlitRows16(ushort *src,int srcPitch,int dst,int dstPitch,int width,int rows)

{
  ushort *puVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  iVar2 = width >> 2;
  if (g_dwSmushPlay_TranslationTable == 0) {
    if (rows != 0) {
      width = rows;
      do {
        if (iVar2 != 0) {
          puVar1 = src;
          iVar3 = iVar2;
          do {
            *(undefined4 *)((int)puVar1 + (dst - (int)src)) = *(undefined4 *)puVar1;
            puVar1 = puVar1 + 2;
            iVar3 = iVar3 + -1;
          } while (iVar3 != 0);
        }
        src = (ushort *)((int)src + srcPitch);
        dst = dst + dstPitch;
        width = width + -1;
      } while (width != 0);
    }
  }
  else {
    uVar4 = g_dwSmushPlay_TranslationTable;
    if (rows != 0) {
      do {
        if (iVar2 != 0) {
          puVar1 = src;
          iVar3 = iVar2;
          do {
            iVar3 = iVar3 + -1;
            *(uint *)((int)puVar1 + (dst - (int)src)) =
                 CONCAT22(*(undefined2 *)(uVar4 + (uint)puVar1[1] * 2),
                          *(undefined2 *)(uVar4 + (uint)*puVar1 * 2));
            puVar1 = puVar1 + 2;
            uVar4 = g_dwSmushPlay_TranslationTable;
          } while (iVar3 != 0);
        }
        dst = dst + dstPitch;
        src = (ushort *)((int)src + srcPitch);
        rows = rows + -1;
      } while (rows != 0);
      return;
    }
  }
  return;
}
#endif


/* ---- 0x004c3df0  msc_MemCopy ---- */
/* Original name msc_MemCopy (the remaster's GrimFandango (Linux): aligned call in anm_DecodeBody,
   fle_StreamerDispense); was Insane_MemCopyCdecl. */

void __cdecl msc_MemCopy(void *dst,void *src,uint n)

{
  Insane_MemCopy(dst,src,n);
  return;
}

/* ---- 0x004c3e10  Insane_MemCopy ---- */
/* memcpy for the lecsmush code; __fastcall with two unused register arguments (ECX, EDX): copies
   the unaligned head first, then dwords */

void __cdecl Insane_MemCopy(void *dst,void *src,uint n)

{
  uint uVar1;
  
  for (uVar1 = n & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
    *(undefined1 *)dst = *(undefined1 *)src;
    src = (undefined4 *)((int)src + 1);
    dst = (undefined4 *)((int)dst + 1);
  }
  for (uVar1 = n >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
    *(undefined4 *)dst = *(undefined4 *)src;
    src = (undefined4 *)((int)src + 4);
    dst = (undefined4 *)((int)dst + 4);
  }
  return;
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern char f_anm_animframe_module[] __asm__("_anm_animframe_module");
extern char f_anm_animplay_module[] __asm__("_anm_animplay_module");
extern char f_bmp_bitmap_module[] __asm__("_bmp_bitmap_module");
extern char f_fle_directory_module[] __asm__("_fle_directory_module");
extern char f_fle_stdfile_module[] __asm__("_fle_stdfile_module");
extern char f_fle_streamer_module[] __asm__("_fle_streamer_module");
extern char f_fle_zfilio_module[] __asm__("_fle_zfilio_module");
extern char f_fob_flobdec_blocky16_module[] __asm__("_fob_flobdec_blocky16_module");
extern char f_fob_flobdec_wave_module[] __asm__("_fob_flobdec_wave_module");
extern char f_grimio_stdio_module[] __asm__("_grimio_stdio_module");
extern char f_grimmem_memory_module[] __asm__("_grimmem_memory_module");
extern char f_sou_dsnd_module[] __asm__("_sou_dsnd_module");
extern char f_sou_sound_module[] __asm__("_sou_sound_module");
extern char f_sys_timer_module[] __asm__("_sys_timer_module");
extern char grim_def_DAT_004f0c78[] __asm__("_DAT_004f0c78");
extern char grim_def_DAT_004f0c88[] __asm__("_DAT_004f0c88");
extern char grim_def_DAT_004f0c94[] __asm__("_DAT_004f0c94");
extern unsigned char grim_def_DAT_008d16ac[4] __asm__("_DAT_008d16ac");
extern unsigned char grim_def_DAT_008d16c0[8] __asm__("_DAT_008d16c0");
extern char grim_def_g_dwAnimplay_services[] __asm__("_g_dwAnimplay_services");
extern unsigned int grim_def_g_dwSmushPlaySysInitialized __asm__("_g_dwSmushPlaySysInitialized");
extern unsigned int grim_def_g_dwSmushPlaySysStarted __asm__("_g_dwSmushPlaySysStarted");
extern char grim_def_g_dwSmushPlay_sound_services[] __asm__("_g_dwSmushPlay_sound_services");
extern void *grim_def_g_pShl_modules[30] __asm__("_g_pShl_modules");
extern char grim_def_g_pSmushPlay_file_services[] __asm__("_g_pSmushPlay_file_services");
extern void *grim_def_g_pSubscription_info[12] __asm__("_g_pSubscription_info");
extern char grim_def_s_FILIO_insane_stdio_004f0c64[] __asm__("_s_FILIO_insane_stdio_004f0c64");
extern char grim_def_s__GZ_004f0cb8[4] __asm__("_s__GZ_004f0cb8");
extern char grim_def_s__SNM_004f0cbc[8] __asm__("_s__SNM_004f0cbc");
extern char grim_def_s__gz_004f0cb4[4] __asm__("_s__gz_004f0cb4");
extern char grim_def_s__snm_004f0cc4[8] __asm__("_s__snm_004f0cc4");
/* 0x004f0b70, 48 bytes */ GRIM_DATA("004f0b70") void *grim_def_g_pSubscription_info[12] __asm__("_g_pSubscription_info") = {
    (void *)&grim_def_g_pSmushPlay_file_services, (void *)&grim_def_DAT_004f0c94, 0, (void *)&grim_def_g_dwSmushPlay_sound_services,
    (void *)&grim_def_DAT_004f0c88, 0, (void *)&grim_def_g_dwAnimplay_services, (void *)&grim_def_DAT_004f0c78,
    0, 0, 0, 0
};
/* 0x004f0ba0, 120 bytes */ GRIM_DATA("004f0ba0") void *grim_def_g_pShl_modules[30] __asm__("_g_pShl_modules") = {
    (void *)f_grimmem_memory_module, 0, (void *)f_sys_timer_module, 0,
    (void *)f_bmp_bitmap_module, 0, (void *)f_grimio_stdio_module, 0,
    (void *)f_fle_stdfile_module, 0, (void *)f_fle_zfilio_module, (void *)&grim_def_s_FILIO_insane_stdio_004f0c64,
    (void *)f_fle_directory_module, 0, (void *)f_fob_flobdec_blocky16_module, 0,
    (void *)f_fob_flobdec_wave_module, 0, (void *)f_sou_dsnd_module, 0,
    (void *)f_sou_sound_module, 0, (void *)f_fle_streamer_module, 0,
    (void *)f_anm_animframe_module, 0, (void *)f_anm_animplay_module, 0,
    0, 0
};
/* 0x004f0cb4, 4 bytes */ /* loose */ char grim_def_s__gz_004f0cb4[4] __asm__("_s__gz_004f0cb4") = ".gz";
/* 0x004f0cb8, 4 bytes */ /* loose */ char grim_def_s__GZ_004f0cb8[4] __asm__("_s__GZ_004f0cb8") = ".GZ";
/* 0x004f0cbc, 8 bytes */ /* loose */ char grim_def_s__SNM_004f0cbc[8] __asm__("_s__SNM_004f0cbc") = ".SNM";
/* 0x004f0cc4, 8 bytes */ /* loose */ char grim_def_s__snm_004f0cc4[8] __asm__("_s__snm_004f0cc4") = ".snm";
/* 0x008d16a0, 4 bytes */ GRIM_DATA("008d16a0") unsigned int grim_def_g_dwSmushPlaySysInitialized __asm__("_g_dwSmushPlaySysInitialized") = 0x0;
/* 0x008d16a4, 4 bytes */ GRIM_DATA("008d16a4") unsigned int grim_def_g_dwSmushPlaySysStarted __asm__("_g_dwSmushPlaySysStarted") = 0x0;
/* 0x008d16ac, 4 bytes */ GRIM_DATA("008d16ac") unsigned char grim_def_DAT_008d16ac[4] __asm__("_DAT_008d16ac") = {0};
/* 0x008d16c0, 8 bytes */ GRIM_DATA("008d16c0") unsigned char grim_def_DAT_008d16c0[8] __asm__("_DAT_008d16c0") = {0};
