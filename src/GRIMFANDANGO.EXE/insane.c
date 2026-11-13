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

int SmushPlay_GetMovieTime(void)

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

undefined4 SmushPlay_SysInitialize(uint param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  g_dwSmushPlayHS = param_1;
  uVar1 = 1;
  if (g_dwSmushPlaySysInitialized == 0) {
    g_pSmushPlay_share_services =
         (int *)LecShare_Initialize(0,&g_pShl_modules,s_FILIO_insane_zfilio_004f0ca0,&DAT_004f5a98);
    if (g_pSmushPlay_share_services == (int *)0x0) {
      return 1;
    }
    g_dwSmushPlaySysInitialized = 1;
    if (param_2 != (undefined4 *)0x0) {
      *param_2 = SmushPlay_SysInitialize;
      param_2[1] = SmushPlay_SysTerminate;
      param_2[2] = SmushPlay_SysStartup;
      param_2[3] = SmushPlay_SysShutdown;
      param_2[4] = 0;
      param_2[5] = 0;
      param_2[6] = 0;
      param_2[7] = 0;
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

void SmushPlay_SysTerminate(void)

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

undefined4 SmushPlay_SysStartup(void)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 1;
  if ((g_dwSmushPlaySysInitialized != 0) && (g_dwSmushPlaySysStarted == 0)) {
    ((code *)fle_zfilio_config)(1,&DAT_004f0cc4,0);
    ((code *)fle_zfilio_config)(1,&DAT_004f0cbc,0);
    ((code *)fle_zfilio_config)(1,&DAT_004f0cb8,0);
    ((code *)fle_zfilio_config)(1,&DAT_004f0cb4,0);
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

void SmushPlay_SysShutdown(void)

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

void SmushPlay_SysSetVideoCallbacks(uint *param_1)

{
  int iVar1;
  uint *puVar2;
  
  puVar2 = &g_dwVideoCallbacks;
  for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *param_1;
    param_1 = param_1 + 1;
    puVar2 = puVar2 + 1;
  }
  return;
}

/* ---- 0x004bd7c0  smushplay_GetInfo ---- */
/* Reads a packed 0x16-byte header field by field through the file io vtable at g_pInsaneFileOps
   Original name smushplay_GetInfo (the remaster's GrimFandango (Linux): aligned call in
   SmushPlay_GetMovieLength); was Insane_ReadFrameHeader. */

undefined4 smushplay_GetInfo(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    return 0;
  }
  uVar1 = (*(code *)g_pSmushPlay_file_services[4])(param_1);
  (*(code *)g_pSmushPlay_file_services[5])(param_1,0x10,0);
  (*(code *)g_pSmushPlay_file_services[2])(param_1,param_2,1);
  (*(code *)g_pSmushPlay_file_services[2])(param_1,param_2 + 1,1);
  (*(code *)g_pSmushPlay_file_services[2])(param_1,param_2 + 2,2);
  (*(code *)g_pSmushPlay_file_services[2])(param_1,param_2 + 4,2);
  (*(code *)g_pSmushPlay_file_services[2])(param_1,param_2 + 6,2);
  (*(code *)g_pSmushPlay_file_services[2])(param_1,(short *)(param_2 + 8),2);
  (*(code *)g_pSmushPlay_file_services[2])(param_1,(short *)(param_2 + 10),2);
  (*(code *)g_pSmushPlay_file_services[2])(param_1,param_2 + 0xc,2);
  (*(code *)g_pSmushPlay_file_services[2])(param_1,param_2 + 0xe,4);
  (*(code *)g_pSmushPlay_file_services[2])(param_1,(int *)(param_2 + 0x12),4);
  (*(code *)g_pSmushPlay_file_services[2])(param_1,param_2 + 0x16,0x400);
  (*(code *)g_pSmushPlay_file_services[2])(param_1,param_2 + 0x416,2);
  if (((0 < *(short *)(param_2 + 8)) && (0 < *(short *)(param_2 + 10))) &&
     (0 < *(int *)(param_2 + 0x12))) {
    (*(code *)g_pSmushPlay_file_services[5])(param_1,uVar1,0);
    return 0;
  }
  return 0xfffffffe;
}

/* ---- 0x004bdb00  Insane_PrepareFrame ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Validates the frame against the output size and chooses the blit mode bits in g_dwInsaneBlitFlags
    */

undefined4 Insane_PrepareFrame(int *param_1,undefined4 *param_2,uint *param_3)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  ushort *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  
  if ((param_1 != (int *)0x0) && (param_2 != (undefined4 *)0x0)) {
    _DAT_008d16c0 = 0;
    if ((_g_bMovieFlags & 1) != 0) {
      _g_bMovieFlags = _g_bMovieFlags & 0xfffffff9;
      if ((int)param_3[2] / 2 < (int)UINT_008d11e8) {
        if ((int)UINT_008d11ec < (int)param_3[3]) {
          _g_bMovieFlags = _g_bMovieFlags | 2;
        }
      }
      else {
        _g_bMovieFlags = _g_bMovieFlags | 4;
      }
    }
    iVar7 = ((_g_bMovieFlags & 6) != 0) + 1;
    iVar5 = ((_g_bMovieFlags & 4) != 0) + 1;
    iVar6 = iVar5 * UINT_008d11e8;
    iVar3 = UINT_008d11ec * iVar7;
    uVar1 = *param_3;
    uVar9 = UINT_008d11e0;
    if ((int)UINT_008d11e0 < (int)uVar1) {
      iVar6 = iVar6 + (UINT_008d11e0 - uVar1);
      uVar9 = uVar1;
    }
    if ((int)(uVar1 + param_3[2]) < (int)(uVar9 + iVar6)) {
      iVar6 = (uVar1 + param_3[2]) - uVar9;
    }
    uVar1 = param_3[1];
    uVar8 = UINT_008d11e4;
    if ((int)UINT_008d11e4 < (int)uVar1) {
      iVar3 = iVar3 + (UINT_008d11e4 - uVar1);
      uVar8 = uVar1;
    }
    if ((int)(uVar1 + param_3[3]) < (int)(uVar8 + iVar3)) {
      iVar3 = (uVar1 + param_3[3]) - uVar8;
    }
    iVar4 = (iVar6 / iVar5) * param_2[3];
    iVar6 = param_1[5];
    puVar2 = (ushort *)*param_2;
    iVar5 = param_1[3] * uVar9 * iVar5 + uVar8 * iVar7 * iVar6 + *param_1;
    if ((_g_bMovieFlags & 4) == 0) {
      if ((_g_bMovieFlags & 2) == 0) {
        Insane_BlitRows16(puVar2,param_2[5],iVar5,iVar6,iVar4,iVar3 / iVar7);
      }
      else {
        ((code *)Insane_BlitRowsDual)(puVar2);
      }
    }
    else {
      ((code *)Insane_Blit8To16Doubled)(puVar2,param_2[5],iVar5,iVar6,iVar4,iVar3 / iVar7);
    }
  }
  _DAT_008d16ac = 0;
  return 0;
}
#undef local_14
#undef local_18
#undef local_8


/* ---- 0x004bdca0  Insane_Blit8To16Doubled ---- */
/* Pixel-doubling conversion of 8-bit frame rows into a 16-bit destination */

undefined8 __fastcall
Insane_Blit8To16Doubled
          (undefined4 param_1,undefined4 param_2,uint *param_3,int param_4,uint *param_5,int param_6
          ,int param_7,int param_8)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  uint uVar3;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  
  local_10 = 0;
  do {
    iVar1 = (int)param_3 + param_7;
    do {
      uVar3 = *param_3;
      uVar2 = (uVar3 & 0xff00) << 8 | uVar3 & 0xff;
      uVar2 = uVar2 << 8 | uVar2;
      *param_5 = uVar2;
      param_5 = (uint *)((int)param_5 + param_6);
      uVar3 = uVar3 & 0xff000000 | uVar3 >> 8 & 0xff00;
      *param_5 = uVar2;
      param_3 = param_3 + 1;
      uVar3 = uVar3 | uVar3 >> 8;
      param_5[1] = uVar3;
      param_5 = (uint *)((int)param_5 + (8 - param_6));
      param_5[-1] = uVar3;
    } while ((int)param_3 < iVar1);
    param_3 = (uint *)((int)param_3 + (param_4 - param_7));
    param_5 = (uint *)((int)param_5 + param_7 * -2 + param_6 * 2);
    local_10 = local_10 + 1;
  } while ((int)local_10 < param_8);
  return CONCAT44(param_2,param_4 - param_7);
}
#undef local_10
#undef local_14
#undef local_8
#undef local_c


/* ---- 0x004bdd50  Insane_BlitRowsDual ---- */
/* Copies frame rows to two destinations (front and back buffer) */

void Insane_BlitRowsDual(int param_1,int param_2,undefined4 *param_3,int param_4,int param_5,
                        int param_6)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  
  for (; param_6 != 0; param_6 = param_6 + -1) {
    if (param_5 >> 2 != 0) {
      puVar2 = param_3;
      iVar3 = param_5 >> 2;
      do {
        uVar1 = *(undefined4 *)((int)puVar2 + (param_1 - (int)param_3));
        *(undefined4 *)((int)puVar2 + param_4) = uVar1;
        *puVar2 = uVar1;
        puVar2 = puVar2 + 1;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    param_1 = param_1 + param_2;
    param_3 = (undefined4 *)((int)param_3 + param_4 * 2);
  }
  return;
}

/* ---- 0x004bddb0  Insane_BlitRows16 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void __cdecl
Insane_BlitRows16(ushort *param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  ushort *puVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  iVar2 = param_5 >> 2;
  if (g_dwSmushPlay_TranslationTable == 0) {
    if (param_6 != 0) {
      param_5 = param_6;
      do {
        if (iVar2 != 0) {
          puVar1 = param_1;
          iVar3 = iVar2;
          do {
            *(undefined4 *)((int)puVar1 + (param_3 - (int)param_1)) = *(undefined4 *)puVar1;
            puVar1 = puVar1 + 2;
            iVar3 = iVar3 + -1;
          } while (iVar3 != 0);
        }
        param_1 = (ushort *)((int)param_1 + param_2);
        param_3 = param_3 + param_4;
        param_5 = param_5 + -1;
      } while (param_5 != 0);
    }
  }
  else {
    uVar4 = g_dwSmushPlay_TranslationTable;
    if (param_6 != 0) {
      do {
        if (iVar2 != 0) {
          puVar1 = param_1;
          iVar3 = iVar2;
          do {
            iVar3 = iVar3 + -1;
            *(uint *)((int)puVar1 + (param_3 - (int)param_1)) =
                 CONCAT22(*(undefined2 *)(uVar4 + (uint)puVar1[1] * 2),
                          *(undefined2 *)(uVar4 + (uint)*puVar1 * 2));
            puVar1 = puVar1 + 2;
            uVar4 = g_dwSmushPlay_TranslationTable;
          } while (iVar3 != 0);
        }
        param_3 = param_3 + param_4;
        param_1 = (ushort *)((int)param_1 + param_2);
        param_6 = param_6 + -1;
      } while (param_6 != 0);
      return;
    }
  }
  return;
}
#endif


/* ---- 0x004c3df0  msc_MemCopy ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name msc_MemCopy (the remaster's GrimFandango (Linux): aligned call in anm_DecodeBody,
   fle_StreamerDispense); was Insane_MemCopyCdecl. */

void __cdecl msc_MemCopy(void *dst,void *src,uint n)

{
  Insane_MemCopy(dst,src,n);
  return;
}
#endif


/* ---- 0x004c3e10  Insane_MemCopy ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
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
#endif

