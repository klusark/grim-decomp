/* GRIMFANDANGO.EXE :: animplay.c
 * functions 0x004c23c0 .. 0x004c3d30 (5 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004c23c0  anm_Start ---- */
/* Creates the AnimPlay frame player: allocates it, opens the streamer and the file, starts the
   clock and frame timers; returns 0 or -1 Original name anm_Start (the remaster's GrimFandango
   (Linux): strings: 'AnimPlay Module: Cannot open file %s' | 'AnimPlay Module: Cannot init
   Animation module' | 'AnimPlay Module: Cannot allocate sync timer' | 'AnimPlay Module: Cannot
   allocate frame timer'); was AnimPlay_Create. */

int __cdecl anm_Start(void **out,char *name,int fps,int streamArg1,int streamArg2,uint flags)

{
  AnimPlayer *p;
  int iVar1;
  
  p = (AnimPlayer *)
      (*(code *)*g_pAnm_memory_services)(0x70,s_C__grimsrc_libs_lecsmush_insane__004f1608,0x140);
  if (p == (AnimPlayer *)0x0) goto LAB_004c257d;
  iVar1 = (*(code *)*g_pAnm_streamer_services)(&p->pStream,streamArg1,streamArg2);
  if (iVar1 == 0) {
    iVar1 = (int)(0x1234dc / (longlong)fps);
    p->dwFlags = flags;
    p->nSyncTicks = 0;
    p->nFrameDue = 0;
    p->nLagMode = 0;
    p->nStarted = 0;
    p->nState = 0;
    p->nTargetDelay = iVar1;
    p->nDelay = iVar1;
    *out = p;
    iVar1 = anm_animator_Initialize(p);
    if (iVar1 == 0) {
      iVar1 = anm_animator_NewAnim(*out,name,flags,-1,-1,0);
      if (iVar1 == 0) {
        iVar1 = (*(code *)*g_pAnimPlay_timer_services)(frame_Timer,1,2,p);
        p->nTimerSync = iVar1;
        if (iVar1 == 0) {
          if ((g_pAnm_virtherc_services == (int *)0x0) || ((UINT_008d6f20 & 0x20000) == 0))
          goto LAB_004c251c;
          (*(code *)g_pAnm_virtherc_services[3])(s_AnimPlay_Module__Cannot_allocate_004f15ac);
          Mem_DumpLog();
        }
        else {
          iVar1 = (*(code *)*g_pAnimPlay_timer_services)(sync_Timer,p->nTargetDelay,8,p);
          p->nTimerFrame = iVar1;
          if (iVar1 != 0) {
            p->nFailed = 0;
            return 0;
          }
          if ((g_pAnm_virtherc_services != (int *)0x0) && ((UINT_008d6f20 & 0x20000) != 0)) {
            (*(code *)g_pAnm_virtherc_services[3])(s_AnimPlay_Module__Cannot_allocate_004f15d8);
          }
          (*(code *)g_pAnimPlay_timer_services[1])(p->nTimerSync);
          Mem_DumpLog();
        }
      }
      else {
        (*(code *)g_pAnm_virtherc_services[3])(s_AnimPlay_Module__Cannot_open_fil_004f1584,name);
LAB_004c251c:
        Mem_DumpLog();
      }
    }
    else {
      (*(code *)g_pAnm_virtherc_services[3])(s_AnimPlay_Module__Cannot_init_Ani_004f1554);
    }
    (*(code *)g_pAnm_streamer_services[1])(&p->pStream);
  }
  else if ((g_pAnm_virtherc_services != (int *)0x0) && ((UINT_008d6f20 & 0x20000) != 0)) {
    (*(code *)g_pAnm_virtherc_services[3])(s_AnimPlay_Module__Cannot_allocate_004f1520);
  }
  (*(code *)g_pAnm_memory_services[1])(p,s_C__grimsrc_libs_lecsmush_insane__004f1608,0x175);
LAB_004c257d:
  *out = (void *)0x0;
  return -1;
}

/* ---- 0x004c2690  anm_Stop ---- */
/* Stops the timers of an AnimPlay frame player, closes the streamer and frees it Original name
   anm_Stop (the remaster's GrimFandango (Linux): slot 5 of the "ANIMPLAY=insane" service table);
   was AnimPlay_Destroy. */

void __cdecl anm_Stop(void **pp)

{
  undefined4 *puVar1;
  
  puVar1 = *pp;
  (*(code *)g_pAnimPlay_timer_services[1])(*puVar1);
  (*(code *)g_pAnimPlay_timer_services[1])(puVar1[1]);
  if ((g_dwAnm_audio_halted != 0) && (g_pAnimPlay_sound_services != (int *)0x0)) {
    (*(code *)g_pAnimPlay_sound_services[3])();
  }
  Mem_DumpLog();
  (*(code *)g_pAnm_streamer_services[1])(puVar1 + 0x18);
  if (*pp != (void *)0x0) {
    (*(code *)g_pAnm_memory_services[1])(*pp,s_C__grimsrc_libs_lecsmush_insane__004f1608,0x1d4);
  }
  *pp = (void *)0x0;
  (*(code *)*g_pAnm_animframe_services)();
  return;
}

/* ---- 0x004c27a0  anm_Render ---- */
/* One step of the AnimPlay frame player: shows the next frame if due and adjusts the frame delay to
   keep sound and picture in sync Original name anm_Render (the remaster's GrimFandango (Linux):
   strings: 'Sync Ticks:  %ld    \n' | 'State:       %d    \n' | 'Frame Delay: %ld (%ld target)
   \n' | 'Buffer:      %ld%%    \n'); was AnimPlay_Update. */

int __cdecl
anm_Render(AnimPlayer *p,int a2,int a3,int a4,int a5,int a6,int a7,int a8,int a9,int a10)

{
  int *piVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  longlong lVar8;
  
  if (p->nState == 5) {
    uVar2 = anm_animator_Render((int)p,a2,a3,a4,a5,a6,a7,a8,p->dwFlags,a9,a10);
    p->nState = uVar2;
    if ((int)uVar2 < 0) {
      p->nFailed = 1;
      return uVar2;
    }
  }
  else if (p->nFrameDue == 0) {
    uVar2 = 6;
  }
  else {
    uVar3 = (*(code *)g_pAnm_streamer_services[7])(p->pStream);
    if (p->nStarted == 0) {
      g_nBretsFrameCount = 0;
      g_dwRenderHandler_totalTime = 0;
    }
    g_dwRenderHandler_totalTime = g_dwRenderHandler_totalTime + p->nDelay;
    iVar4 = sou_engine_QueryTime(0);
    lVar8 = FTOL(((float10)iVar4 - (float10)g_nBretsFrameCount * (float10)66.66666666667) *
                  (float10)0.0149999999999925);
    iVar4 = (int)lVar8;
    p->nSyncTicks = p->nSyncTicks + -1;
    p->nFrameDue = 0;
    if ((((iVar4 < 1) && (iVar6 = p->nState, iVar6 != 2)) && (iVar6 != 3)) && (iVar6 != 4)) {
      if (iVar4 < 0) {
        iVar6 = p->nTargetDelay;
        if (p->nDelay < iVar6) {
          p->nDelay = iVar6;
        }
        if (iVar4 == -1) {
          iVar5 = (int)(iVar6 + (iVar6 >> 0x1f & 0xfU)) >> 4;
        }
        else {
          iVar5 = (int)(iVar6 + (iVar6 >> 0x1f & 7U)) >> 3;
        }
        p->nDelay = p->nDelay + iVar5;
        iVar6 = (iVar6 << 2) / 3;
        if (iVar6 < p->nDelay) {
          p->nDelay = iVar6;
        }
      }
    }
    else {
      iVar6 = p->nTargetDelay;
      if (iVar6 < p->nDelay) {
        p->nDelay = iVar6;
      }
      if (iVar4 == 1) {
        iVar5 = (int)(iVar6 + (iVar6 >> 0x1f & 0xfU)) >> 4;
      }
      else {
        iVar5 = (int)(iVar6 + (iVar6 >> 0x1f & 7U)) >> 3;
      }
      iVar5 = p->nDelay - iVar5;
      p->nDelay = iVar5;
      if (iVar5 < 1) {
        p->nDelay = 1;
      }
      iVar6 = (int)(iVar6 * 3 + (iVar6 * 3 >> 0x1f & 3U)) >> 2;
      if (p->nDelay < iVar6) {
        p->nDelay = iVar6;
      }
    }
    (*(code *)g_pAnimPlay_timer_services[4])(p->nTimerSync,p->nDelay);
    if (iVar4 < 3) {
      if (iVar4 < 1) {
        p->nLagMode = 0;
      }
    }
    else {
      p->nLagMode = 1;
    }
    if ((p->nLagMode == 0) || ((p->dwFlags & 2) != 0)) {
      uVar2 = p->dwFlags;
    }
    else {
      uVar2 = p->dwFlags | 0x8000;
    }
    uVar2 = anm_animator_Render((int)p,a2,a3,a4,a5,a6,a7,a8,uVar2,a9,a10);
    p->nState = uVar2;
    if ((g_pAnm_virtherc_services != (int *)0x0) && ((UINT_008d6f20 & 0xc0000000) != 0)) {
      piVar1 = g_pAnm_virtherc_services + 5;
      uVar7 = (*(code *)g_pAnm_virtherc_services[7])(4,0x20);
      (*(code *)*piVar1)(0,10,uVar7);
      (*(code *)*g_pAnm_virtherc_services)(0,10);
      (*(code *)g_pAnm_virtherc_services[3])(s_Buffer___ld___004f1694,uVar3);
      (*(code *)g_pAnm_virtherc_services[3])
                (s_Frame_Delay___ld___ld_target__004f1670,p->nDelay,p->nTargetDelay);
      (*(code *)g_pAnm_virtherc_services[3])(s_Sync_Ticks___ld_004f1658,p->nSyncTicks);
      (*(code *)g_pAnm_virtherc_services[3])(s_State___d_004f1640,p->nState);
    }
    uVar2 = p->nState;
    if ((int)uVar2 < 0) {
      p->nFailed = 1;
    }
    if (uVar2 == 1) {
      p->nStarted = 1;
      return 1;
    }
  }
  return uVar2;
}

/* ---- 0x004c36b0  anm_animator_Initialize ---- */
/* Resets the decoder state fields of an AnimPlay frame player and its streamer Original name
   anm_animator_Initialize (the remaster's GrimFandango (Linux): aligned call in anm_Start); was
   AnimPlay_ResetState. */

int __cdecl anm_animator_Initialize(AnimPlayer *p)

{
  (*(code *)g_pAnm_streamer_services[6])(p->pStream);
  p->nDecoderC = 0;
  p->nDecoder28 = 0;
  p->dwCodec = 0x6e756c6c;
  p->nDecoder2c = 1;
  p->nOpen = 0;
  p->nDecoder54 = 0;
  p->nDecoder58 = 0;
  p->nOpenArg = 0;
  p->nDecoder44 = 0;
  return 0;
}

/* ---- 0x004c3d30  anm_animator_NewAnim ---- */
/* Opens the movie file of an AnimPlay frame player through the streamer Original name
   anm_animator_NewAnim (the remaster's GrimFandango (Linux): aligned call in anm_Start); was
   AnimPlay_OpenFile. */

int __cdecl anm_animator_NewAnim(AnimPlayer *p,char *name,uint flags,int a4,int a5,int a6)

{
  int iVar1;
  
  p->nOpenArg = a6;
  p->dwOpenFlags = flags;
  iVar1 = (*(code *)g_pAnm_streamer_services[2])(p->pStream,name,8);
  if (iVar1 != 0) {
    return -1;
  }
  p->nOpen = 1;
  zlibVersion();
  FUN_004c3d90((int)p,a4,a5);
  return 0;
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern unsigned char grim_def_g_dwRenderHandler_totalTime[8] __asm__("_g_dwRenderHandler_totalTime");
extern char grim_def_s_AnimPlay_Module__Cannot_allocate_004f1520[52] __asm__("_s_AnimPlay_Module__Cannot_allocate_004f1520");
extern char grim_def_s_AnimPlay_Module__Cannot_allocate_004f15ac[44] __asm__("_s_AnimPlay_Module__Cannot_allocate_004f15ac");
extern char grim_def_s_AnimPlay_Module__Cannot_allocate_004f15d8[48] __asm__("_s_AnimPlay_Module__Cannot_allocate_004f15d8");
extern char grim_def_s_AnimPlay_Module__Cannot_init_Ani_004f1554[48] __asm__("_s_AnimPlay_Module__Cannot_init_Ani_004f1554");
extern char grim_def_s_AnimPlay_Module__Cannot_open_fil_004f1584[40] __asm__("_s_AnimPlay_Module__Cannot_open_fil_004f1584");
extern char grim_def_s_Buffer___ld___004f1694[24] __asm__("_s_Buffer___ld___004f1694");
extern char grim_def_s_C__grimsrc_libs_lecsmush_insane__004f1608[56] __asm__("_s_C__grimsrc_libs_lecsmush_insane__004f1608");
extern char grim_def_s_Frame_Delay___ld___ld_target__004f1670[36] __asm__("_s_Frame_Delay___ld___ld_target__004f1670");
extern char grim_def_s_State___d_004f1640[24] __asm__("_s_State___d_004f1640");
extern char grim_def_s_Sync_Ticks___ld_004f1658[24] __asm__("_s_Sync_Ticks___ld_004f1658");
/* 0x004f1520, 52 bytes */ /* loose */ char grim_def_s_AnimPlay_Module__Cannot_allocate_004f1520[52] __asm__("_s_AnimPlay_Module__Cannot_allocate_004f1520") = "AnimPlay Module: Cannot allocate streamer buffers";
/* 0x004f1554, 48 bytes */ /* loose */ char grim_def_s_AnimPlay_Module__Cannot_init_Ani_004f1554[48] __asm__("_s_AnimPlay_Module__Cannot_init_Ani_004f1554") = "AnimPlay Module: Cannot init Animation module";
/* 0x004f1584, 40 bytes */ /* loose */ char grim_def_s_AnimPlay_Module__Cannot_open_fil_004f1584[40] __asm__("_s_AnimPlay_Module__Cannot_open_fil_004f1584") = "AnimPlay Module: Cannot open file %s";
/* 0x004f15ac, 44 bytes */ /* loose */ char grim_def_s_AnimPlay_Module__Cannot_allocate_004f15ac[44] __asm__("_s_AnimPlay_Module__Cannot_allocate_004f15ac") = "AnimPlay Module: Cannot allocate sync timer";
/* 0x004f15d8, 48 bytes */ /* loose */ char grim_def_s_AnimPlay_Module__Cannot_allocate_004f15d8[48] __asm__("_s_AnimPlay_Module__Cannot_allocate_004f15d8") = "AnimPlay Module: Cannot allocate frame timer";
/* 0x004f1608, 56 bytes */ /* loose */ char grim_def_s_C__grimsrc_libs_lecsmush_insane__004f1608[56] __asm__("_s_C__grimsrc_libs_lecsmush_insane__004f1608") = "C:\\grimsrc\\libs\\lecsmush\\insane\\source\\animate\\Pcplay.c";
/* 0x004f1640, 24 bytes */ /* loose */ char grim_def_s_State___d_004f1640[24] __asm__("_s_State___d_004f1640") = "State:       %d    \n";
/* 0x004f1658, 24 bytes */ /* loose */ char grim_def_s_Sync_Ticks___ld_004f1658[24] __asm__("_s_Sync_Ticks___ld_004f1658") = "Sync Ticks:  %ld    \n";
/* 0x004f1670, 36 bytes */ /* loose */ char grim_def_s_Frame_Delay___ld___ld_target__004f1670[36] __asm__("_s_Frame_Delay___ld___ld_target__004f1670") = "Frame Delay: %ld (%ld target)     \n";
/* 0x004f1694, 24 bytes */ /* loose */ char grim_def_s_Buffer___ld___004f1694[24] __asm__("_s_Buffer___ld___004f1694") = "Buffer:      %ld%%    \n";
static unsigned char grim_anchor_008d6f28[0] __attribute__((section(".data$grim_008d6f28"), aligned(16), used));
static unsigned char grim_pad_008d6f28[8] __attribute__((section(".data$grim_008d6f28_"), aligned(4), used));
/* 0x008d6f28, 8 bytes */ GRIM_DATA("008d6f28z") unsigned char grim_def_g_dwRenderHandler_totalTime[8] __asm__("_g_dwRenderHandler_totalTime") = {0};
