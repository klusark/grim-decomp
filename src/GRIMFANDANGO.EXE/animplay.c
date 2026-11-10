/* GRIMFANDANGO.EXE :: animplay.c
 * functions 0x004c23c0 .. 0x004c3d30 (5 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004c23c0  anm_Start ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Creates the AnimPlay frame player: allocates it, opens the streamer and the file, starts the
   clock and frame timers; returns 0 or -1 Original name anm_Start (the remaster's GrimFandango
   (Linux): strings: 'AnimPlay Module: Cannot open file %s' | 'AnimPlay Module: Cannot init
   Animation module' | 'AnimPlay Module: Cannot allocate sync timer' | 'AnimPlay Module: Cannot
   allocate frame timer'); was AnimPlay_Create. */

int __cdecl anm_Start(void **out,char *name,int fps,int streamArg1,int streamArg2,uint flags)

{
  int *p;
  int iVar1;
  
  p = (int *)(*(code *)*g_pAnimMemory)(0x70,s_C__grimsrc_libs_lecsmush_insane__004f1608,0x140);
  if (p == (int *)0x0) goto LAB_004c257d;
  iVar1 = (*(code *)*g_pAnimStreamer)(p + 0x18,streamArg1,streamArg2);
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
    iVar1 = AnimPlay_ResetState(p);
    if (iVar1 == 0) {
      iVar1 = AnimPlay_OpenFile(*out,name,flags,-1,-1,0);
      if (iVar1 == 0) {
        iVar1 = (*(code *)*g_pAnimTimer)(FUN_004c2a70,1,2,p);
        *p = iVar1;
        if (iVar1 == 0) {
          if ((g_pAnimDebug == (int *)0x0) || ((UINT_008d6f20 & 0x20000) == 0)) goto LAB_004c251c;
          (*(code *)g_pAnimDebug[3])(s_AnimPlay_Module__Cannot_allocate_004f15ac);
          ((code *)Mem_DumpLog)(*out);
        }
        else {
          iVar1 = (*(code *)*g_pAnimTimer)(FUN_004c2a80,p[7],8,p);
          p[1] = iVar1;
          if (iVar1 != 0) {
            p[4] = 0;
            return 0;
          }
          if ((g_pAnimDebug != (int *)0x0) && ((UINT_008d6f20 & 0x20000) != 0)) {
            (*(code *)g_pAnimDebug[3])(s_AnimPlay_Module__Cannot_allocate_004f15d8);
          }
          (*(code *)g_pAnimTimer[1])(*p);
          ((code *)Mem_DumpLog)(*out);
        }
      }
      else {
        (*(code *)g_pAnimDebug[3])(s_AnimPlay_Module__Cannot_open_fil_004f1584,name);
LAB_004c251c:
        ((code *)Mem_DumpLog)(*out);
      }
    }
    else {
      (*(code *)g_pAnimDebug[3])(s_AnimPlay_Module__Cannot_init_Ani_004f1554);
    }
    (*(code *)g_pAnimStreamer[1])(p + 0x18);
  }
  else if ((g_pAnimDebug != (int *)0x0) && ((UINT_008d6f20 & 0x20000) != 0)) {
    (*(code *)g_pAnimDebug[3])(s_AnimPlay_Module__Cannot_allocate_004f1520);
  }
  (*(code *)g_pAnimMemory[1])(p,s_C__grimsrc_libs_lecsmush_insane__004f1608,0x175);
LAB_004c257d:
  *out = (void *)0x0;
  return -1;
}
#endif


/* ---- 0x004c2690  AnimPlay_Destroy ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Stops the timers of an AnimPlay frame player, closes the streamer and frees it */

void __cdecl AnimPlay_Destroy(void **pp)

{
  undefined4 *puVar1;
  
  puVar1 = *pp;
  (*(code *)g_pAnimTimer[1])(*puVar1);
  (*(code *)g_pAnimTimer[1])(puVar1[1]);
  if ((UINT_008d6f24 != 0) && (g_pAnimLipsync != (int *)0x0)) {
    (*(code *)g_pAnimLipsync[3])();
  }
  ((code *)Mem_DumpLog)(puVar1);
  (*(code *)g_pAnimStreamer[1])(puVar1 + 0x18);
  if (*pp != (void *)0x0) {
    (*(code *)g_pAnimMemory[1])(*pp,s_C__grimsrc_libs_lecsmush_insane__004f1608,0x1d4);
  }
  *pp = (void *)0x0;
  (*(code *)*g_pAnimFrame)();
  return;
}
#endif


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
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 uVar7;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar8;
  
  if (*(int *)((int)p + 0x68) == 5) {
    iVar2 = anm_animator_Render(p,a2,a3,a4,a5,a6,a7,a8,*(undefined4 *)((int)p + 8),a9,a10);
    *(int *)((int)p + 0x68) = iVar2;
    if (iVar2 < 0) {
      *(undefined4 *)((int)p + 0x10) = 1;
      return iVar2;
    }
  }
  else if (*(int *)((int)p + 0x14) == 0) {
    iVar2 = 6;
  }
  else {
    uVar3 = (*(code *)g_pAnimStreamer[7])(*(undefined4 *)((int)p + 0x60));
    if (*(int *)((int)p + 0x6c) == 0) {
      g_nAnimFramesDecoded = 0;
      UINT_008d6f28 = 0;
    }
    UINT_008d6f28 = UINT_008d6f28 + *(int *)((int)p + 0x20);
    Sound_VoiceSampleCount(0);
    lVar8 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    iVar2 = (int)lVar8;
    *(int *)((int)p + 0x18) = *(int *)((int)p + 0x18) + -1;
    *(undefined4 *)((int)p + 0x14) = 0;
    if ((((iVar2 < 1) && (iVar5 = *(int *)((int)p + 0x68), iVar5 != 2)) && (iVar5 != 3)) &&
       (iVar5 != 4)) {
      if (iVar2 < 0) {
        iVar5 = *(int *)((int)p + 0x1c);
        if (*(int *)((int)p + 0x20) < iVar5) {
          *(int *)((int)p + 0x20) = iVar5;
        }
        if (iVar2 == -1) {
          iVar4 = (int)(iVar5 + (iVar5 >> 0x1f & 0xfU)) >> 4;
        }
        else {
          iVar4 = (int)(iVar5 + (iVar5 >> 0x1f & 7U)) >> 3;
        }
        *(int *)((int)p + 0x20) = *(int *)((int)p + 0x20) + iVar4;
        iVar5 = (iVar5 << 2) / 3;
        if (iVar5 < *(int *)((int)p + 0x20)) {
          *(int *)((int)p + 0x20) = iVar5;
        }
      }
    }
    else {
      iVar5 = *(int *)((int)p + 0x1c);
      if (iVar5 < *(int *)((int)p + 0x20)) {
        *(int *)((int)p + 0x20) = iVar5;
      }
      if (iVar2 == 1) {
        iVar4 = (int)(iVar5 + (iVar5 >> 0x1f & 0xfU)) >> 4;
      }
      else {
        iVar4 = (int)(iVar5 + (iVar5 >> 0x1f & 7U)) >> 3;
      }
      iVar4 = *(int *)((int)p + 0x20) - iVar4;
      *(int *)((int)p + 0x20) = iVar4;
      if (iVar4 < 1) {
        *(undefined4 *)((int)p + 0x20) = 1;
      }
      iVar5 = (int)(iVar5 * 3 + (iVar5 * 3 >> 0x1f & 3U)) >> 2;
      if (*(int *)((int)p + 0x20) < iVar5) {
        *(int *)((int)p + 0x20) = iVar5;
      }
    }
    (*(code *)g_pAnimTimer[4])(*(undefined4 *)p,*(undefined4 *)((int)p + 0x20));
    if (iVar2 < 3) {
      if (iVar2 < 1) {
        *(undefined4 *)((int)p + 100) = 0;
      }
    }
    else {
      *(undefined4 *)((int)p + 100) = 1;
    }
    if ((*(int *)((int)p + 100) == 0) || ((*(uint *)((int)p + 8) & 2) != 0)) {
      uVar6 = *(uint *)((int)p + 8);
    }
    else {
      uVar6 = *(uint *)((int)p + 8) | 0x8000;
    }
    uVar7 = anm_animator_Render(p,a2,a3,a4,a5,a6,a7,a8,uVar6,a9,a10);
    *(undefined4 *)((int)p + 0x68) = uVar7;
    if ((g_pAnimDebug != (int *)0x0) && ((UINT_008d6f20 & 0xc0000000) != 0)) {
      piVar1 = g_pAnimDebug + 5;
      uVar7 = (*(code *)g_pAnimDebug[7])(4,0x20);
      (*(code *)*piVar1)(0,10,uVar7);
      (*(code *)*g_pAnimDebug)(0,10);
      (*(code *)g_pAnimDebug[3])(s_Buffer___ld___004f1694,uVar3);
      (*(code *)g_pAnimDebug[3])
                (s_Frame_Delay___ld___ld_target__004f1670,*(undefined4 *)((int)p + 0x20),
                 *(undefined4 *)((int)p + 0x1c));
      (*(code *)g_pAnimDebug[3])(s_Sync_Ticks___ld_004f1658,*(undefined4 *)((int)p + 0x18));
      (*(code *)g_pAnimDebug[3])(s_State___d_004f1640,*(undefined4 *)((int)p + 0x68));
    }
    iVar2 = *(int *)((int)p + 0x68);
    if (iVar2 < 0) {
      *(undefined4 *)((int)p + 0x10) = 1;
    }
    if (iVar2 == 1) {
      *(undefined4 *)((int)p + 0x6c) = 1;
      return 1;
    }
  }
  return iVar2;
}
#endif


/* ---- 0x004c36b0  AnimPlay_ResetState ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Resets the decoder state fields of an AnimPlay frame player and its streamer */

int __cdecl AnimPlay_ResetState(void *p)

{
  (*(code *)g_pAnimStreamer[6])(*(undefined4 *)((int)p + 0x60));
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
#endif


/* ---- 0x004c3d30  AnimPlay_OpenFile ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Opens the movie file of an AnimPlay frame player through the streamer */

int __cdecl AnimPlay_OpenFile(void *p,char *name,uint flags,int a4,int a5,int a6)

{
  int iVar1;
  
  *(int *)((int)p + 0x40) = a6;
  *(uint *)((int)p + 0x3c) = flags;
  iVar1 = (*(code *)g_pAnimStreamer[2])(*(undefined4 *)((int)p + 0x60),name,8);
  if (iVar1 != 0) {
    return -1;
  }
  *(undefined4 *)((int)p + 0x38) = 1;
  ((code *)zlibVersion)(*(undefined4 *)((int)p + 0x60));
  FUN_004c3d90(p,a4,a5);
  return 0;
}
#endif

