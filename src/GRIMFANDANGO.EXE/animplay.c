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
  int *p;
  int iVar1;
  
  p = (int *)(*(code *)*g_pAnm_memory_services)
                       (0x70,s_C__grimsrc_libs_lecsmush_insane__004f1608,0x140);
  if (p == (int *)0x0) goto LAB_004c257d;
  iVar1 = (*(code *)*g_pAnm_streamer_services)(p + 0x18,streamArg1,streamArg2);
  if (iVar1 == 0) {
    iVar1 = (int)(0x1234dc / (longlong)fps);
    p[2] = flags;
    p[6] = 0;
    p[5] = 0;
    p[0x19] = 0;
    p[0x1b] = 0;
    p[0x1a] = 0;
    p[7] = iVar1;
    p[8] = iVar1;
    *out = p;
    iVar1 = anm_animator_Initialize(p);
    if (iVar1 == 0) {
      iVar1 = anm_animator_NewAnim(*out,name,flags,-1,-1,0);
      if (iVar1 == 0) {
        iVar1 = (*(code *)*g_pAnimPlay_timer_services)(frame_Timer,1,2,p);
        *p = iVar1;
        if (iVar1 == 0) {
          if ((g_pAnm_virtherc_services == (int *)0x0) || ((UINT_008d6f20 & 0x20000) == 0))
          goto LAB_004c251c;
          (*(code *)g_pAnm_virtherc_services[3])(s_AnimPlay_Module__Cannot_allocate_004f15ac);
          Mem_DumpLog();
        }
        else {
          iVar1 = (*(code *)*g_pAnimPlay_timer_services)(sync_Timer,p[7],8,p);
          p[1] = iVar1;
          if (iVar1 != 0) {
            p[4] = 0;
            return 0;
          }
          if ((g_pAnm_virtherc_services != (int *)0x0) && ((UINT_008d6f20 & 0x20000) != 0)) {
            (*(code *)g_pAnm_virtherc_services[3])(s_AnimPlay_Module__Cannot_allocate_004f15d8);
          }
          (*(code *)g_pAnimPlay_timer_services[1])(*p);
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
    (*(code *)g_pAnm_streamer_services[1])(p + 0x18);
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
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* One step of the AnimPlay frame player: shows the next frame if due and adjusts the frame delay to
   keep sound and picture in sync Original name anm_Render (the remaster's GrimFandango (Linux):
   strings: 'Sync Ticks:  %ld    \n' | 'State:       %d    \n' | 'Frame Delay: %ld (%ld target)
   \n' | 'Buffer:      %ld%%    \n'); was AnimPlay_Update. */

int __cdecl anm_Render(void *p,int a2,int a3,int a4,int a5,int a6,int a7,int a8,int a9,int a10)

{
  int *piVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar8;
  
  if (*(int *)((int)p + 0x68) == 5) {
    uVar2 = anm_animator_Render((int)p,a2,a3,a4,a5,a6,a7,a8,*(uint *)((int)p + 8),a9,a10);
    *(uint *)((int)p + 0x68) = uVar2;
    if ((int)uVar2 < 0) {
      *(undefined4 *)((int)p + 0x10) = 1;
      return uVar2;
    }
  }
  else if (*(int *)((int)p + 0x14) == 0) {
    uVar2 = 6;
  }
  else {
    uVar3 = (*(code *)g_pAnm_streamer_services[7])(*(undefined4 *)((int)p + 0x60));
    if (*(int *)((int)p + 0x6c) == 0) {
      g_nBretsFrameCount = 0;
      g_dwRenderHandler_totalTime = 0;
    }
    g_dwRenderHandler_totalTime = g_dwRenderHandler_totalTime + *(int *)((int)p + 0x20);
    sou_engine_QueryTime(0);
    lVar8 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    iVar4 = (int)lVar8;
    *(int *)((int)p + 0x18) = *(int *)((int)p + 0x18) + -1;
    *(undefined4 *)((int)p + 0x14) = 0;
    if ((((iVar4 < 1) && (iVar6 = *(int *)((int)p + 0x68), iVar6 != 2)) && (iVar6 != 3)) &&
       (iVar6 != 4)) {
      if (iVar4 < 0) {
        iVar6 = *(int *)((int)p + 0x1c);
        if (*(int *)((int)p + 0x20) < iVar6) {
          *(int *)((int)p + 0x20) = iVar6;
        }
        if (iVar4 == -1) {
          iVar5 = (int)(iVar6 + (iVar6 >> 0x1f & 0xfU)) >> 4;
        }
        else {
          iVar5 = (int)(iVar6 + (iVar6 >> 0x1f & 7U)) >> 3;
        }
        *(int *)((int)p + 0x20) = *(int *)((int)p + 0x20) + iVar5;
        iVar6 = (iVar6 << 2) / 3;
        if (iVar6 < *(int *)((int)p + 0x20)) {
          *(int *)((int)p + 0x20) = iVar6;
        }
      }
    }
    else {
      iVar6 = *(int *)((int)p + 0x1c);
      if (iVar6 < *(int *)((int)p + 0x20)) {
        *(int *)((int)p + 0x20) = iVar6;
      }
      if (iVar4 == 1) {
        iVar5 = (int)(iVar6 + (iVar6 >> 0x1f & 0xfU)) >> 4;
      }
      else {
        iVar5 = (int)(iVar6 + (iVar6 >> 0x1f & 7U)) >> 3;
      }
      iVar5 = *(int *)((int)p + 0x20) - iVar5;
      *(int *)((int)p + 0x20) = iVar5;
      if (iVar5 < 1) {
        *(undefined4 *)((int)p + 0x20) = 1;
      }
      iVar6 = (int)(iVar6 * 3 + (iVar6 * 3 >> 0x1f & 3U)) >> 2;
      if (*(int *)((int)p + 0x20) < iVar6) {
        *(int *)((int)p + 0x20) = iVar6;
      }
    }
    (*(code *)g_pAnimPlay_timer_services[4])(*(undefined4 *)p,*(undefined4 *)((int)p + 0x20));
    if (iVar4 < 3) {
      if (iVar4 < 1) {
        *(undefined4 *)((int)p + 100) = 0;
      }
    }
    else {
      *(undefined4 *)((int)p + 100) = 1;
    }
    if ((*(int *)((int)p + 100) == 0) || ((*(uint *)((int)p + 8) & 2) != 0)) {
      uVar2 = *(uint *)((int)p + 8);
    }
    else {
      uVar2 = *(uint *)((int)p + 8) | 0x8000;
    }
    uVar2 = anm_animator_Render((int)p,a2,a3,a4,a5,a6,a7,a8,uVar2,a9,a10);
    *(uint *)((int)p + 0x68) = uVar2;
    if ((g_pAnm_virtherc_services != (int *)0x0) && ((UINT_008d6f20 & 0xc0000000) != 0)) {
      piVar1 = g_pAnm_virtherc_services + 5;
      uVar7 = (*(code *)g_pAnm_virtherc_services[7])(4,0x20);
      (*(code *)*piVar1)(0,10,uVar7);
      (*(code *)*g_pAnm_virtherc_services)(0,10);
      (*(code *)g_pAnm_virtherc_services[3])(s_Buffer___ld___004f1694,uVar3);
      (*(code *)g_pAnm_virtherc_services[3])
                (s_Frame_Delay___ld___ld_target__004f1670,*(undefined4 *)((int)p + 0x20),
                 *(undefined4 *)((int)p + 0x1c));
      (*(code *)g_pAnm_virtherc_services[3])
                (s_Sync_Ticks___ld_004f1658,*(undefined4 *)((int)p + 0x18));
      (*(code *)g_pAnm_virtherc_services[3])(s_State___d_004f1640,*(undefined4 *)((int)p + 0x68));
    }
    uVar2 = *(uint *)((int)p + 0x68);
    if ((int)uVar2 < 0) {
      *(undefined4 *)((int)p + 0x10) = 1;
    }
    if (uVar2 == 1) {
      *(undefined4 *)((int)p + 0x6c) = 1;
      return 1;
    }
  }
  return uVar2;
}
#endif


/* ---- 0x004c36b0  anm_animator_Initialize ---- */
/* Resets the decoder state fields of an AnimPlay frame player and its streamer Original name
   anm_animator_Initialize (the remaster's GrimFandango (Linux): aligned call in anm_Start); was
   AnimPlay_ResetState. */

int __cdecl anm_animator_Initialize(void *p)

{
  (*(code *)g_pAnm_streamer_services[6])(*(undefined4 *)((int)p + 0x60));
  *(undefined4 *)((int)p + 0xc) = 0;
  *(undefined4 *)((int)p + 0x28) = 0;
  *(undefined4 *)((int)p + 0x34) = 0x6e756c6c;
  *(undefined4 *)((int)p + 0x2c) = 1;
  *(undefined4 *)((int)p + 0x38) = 0;
  *(undefined4 *)((int)p + 0x54) = 0;
  *(undefined4 *)((int)p + 0x58) = 0;
  *(undefined4 *)((int)p + 0x40) = 0;
  *(undefined4 *)((int)p + 0x44) = 0;
  return 0;
}

/* ---- 0x004c3d30  anm_animator_NewAnim ---- */
/* Opens the movie file of an AnimPlay frame player through the streamer Original name
   anm_animator_NewAnim (the remaster's GrimFandango (Linux): aligned call in anm_Start); was
   AnimPlay_OpenFile. */

int __cdecl anm_animator_NewAnim(void *p,char *name,uint flags,int a4,int a5,int a6)

{
  int iVar1;
  
  *(int *)((int)p + 0x40) = a6;
  *(uint *)((int)p + 0x3c) = flags;
  iVar1 = (*(code *)g_pAnm_streamer_services[2])(*(undefined4 *)((int)p + 0x60),name,8);
  if (iVar1 != 0) {
    return -1;
  }
  *(undefined4 *)((int)p + 0x38) = 1;
  zlibVersion();
  FUN_004c3d90((int)p,a4,a5);
  return 0;
}
