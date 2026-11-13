/* GRIMFANDANGO.EXE :: blocky16.c
 * functions 0x004cc210 .. 0x004cdb80 (22 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004cc210  fob_flobdec_blocky16_module ---- */
/* Entry of LECMODULE insane_blocky16_flobdec: stores the module manager services and the workspace
   size, registers the module and the FLOBDEC interface Original name fob_flobdec_blocky16_module
   (the remaster's GrimFandango (Linux): slot 0 of the "LECMODULE=insane_blocky16_flobdec" service
   table); was Blocky16_Register. */

undefined4 fob_flobdec_blocky16_module(int *param_1,uint param_2)

{
  g_pBlocky16_share_services = param_1;
  g_dwBlocky16_share_config = param_2;
  (*(code *)*param_1)(s_LECMODULE_insane_blocky16_flobde_004f3a04,
                      &PTR_fob_flobdec_blocky16_module_004f34b8);
  (*(code *)*g_pBlocky16_share_services)
            (s_FLOBDEC_insane_blocky16_004f39ec,&g_pBlock16_flobdec_services);
  return 0;
}

/* ---- 0x004cc250  fob_flobdec_blocky16_config ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Reads key and value pairs ending with key 0; key 1 sets the output callback g_pFob_blit_routine
   that Blocky16 hands decoded frames to; other keys are an error Original name
   fob_flobdec_blocky16_config (the remaster's GrimFandango (Linux): aligned call in
   SmushPlay_UpdateMovie); was Blocky16_SetOption. */

int __cdecl fob_flobdec_blocky16_config(int key,...)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)REGISTER0X(0x00000010);
  if (key == 0) {
    return 0;
  }
  do {
    if (key != 1) {
      return -1;
    }
    g_pFob_blit_routine = (void *)puVar1[2];
    key = puVar1[3];
    puVar1 = puVar1 + 2;
  } while (key != 0);
  return 0;
}
#endif


/* ---- 0x004cc290  Blocky16_module_terminate ---- */
/* Unregisters the FLOBDEC interface and the module of the Blocky16 decoder Original name
   Blocky16_module_terminate (the remaster's GrimFandango (Linux): slot 1 of the
   "LECMODULE=insane_blocky16_flobdec" service table; module_terminate is a static several LEC
   modules have, written with the module prefix); was Blocky16_Unregister. */

void Blocky16_module_terminate(void)

{
  (*(code *)g_pBlocky16_share_services[1])(s_FLOBDEC_insane_blocky16_004f39ec);
  (*(code *)g_pBlocky16_share_services[1])(s_LECMODULE_insane_blocky16_flobde_004f3a04);
  return;
}

/* ---- 0x004cc2c0  Blocky16_module_startup ---- */
/* Asks the module manager for the BITMAP clear service and the MEMORY workspace service of the
   decoder; -1 if one is missing Original name Blocky16_module_startup (the remaster's GrimFandango
   (Linux): the static module_startup of the Blocky16 module (the remaster has one per module file,
   hence the prefix); strings: 'FlobDec-Blocky16 Module: Cannot allocate bitmap services.' |
   'BITMAP.clear' | 'FlobDec-Blocky16 Module: Cannot allocate memory services.'); was Blocky16_Init.
    */

undefined4 Blocky16_module_startup(void)

{
  g_pBlocky16_bitmap_services =
       (int *)(*(code *)g_pBlocky16_share_services[2])
                        (s_BITMAP_clear_004f3aa0,g_dwBlocky16_share_config);
  g_pBlocky16_memory_services =
       (int *)(*(code *)g_pBlocky16_share_services[2])
                        (s_MEMORY_workspace_004f14ec,g_dwBlocky16_share_config);
  if (g_pBlocky16_bitmap_services == (int *)0x0) {
    (*(code *)g_pBlocky16_share_services[8])(s_FlobDec_Blocky16_Module__Cannot_a_004f3a64);
    return 0xffffffff;
  }
  if (g_pBlocky16_memory_services == (int *)0x0) {
    (*(code *)g_pBlocky16_share_services[8])(s_FlobDec_Blocky16_Module__Cannot_a_004f3a28);
    return 0xffffffff;
  }
  return 0;
}

/* ---- 0x004cc340  Blocky16_module_shutdown ---- */
/* Frees the frame buffers and releases the two services of the Blocky16 decoder Original name
   Blocky16_module_shutdown (the remaster's GrimFandango (Linux): slot 3 of the
   "LECMODULE=insane_blocky16_flobdec" service table; module_shutdown is a static several LEC
   modules have, written with the module prefix); was Blocky16_Shutdown. */

void Blocky16_module_shutdown(void)

{
  Blocky16_flobdec_Reset();
  (*(code *)g_pBlocky16_share_services[3])(g_pBlocky16_bitmap_services);
  (*(code *)g_pBlocky16_share_services[3])(g_pBlocky16_memory_services);
  return;
}

/* ---- 0x004cc370  Blocky16_flobdec_Info ---- */
/* Returns the name, description or help text of the Blocky16 module for index 0, 1 or 2 Original
   name Blocky16_flobdec_Info (the remaster's GrimFandango (Linux): slot 0 of the
   "FLOBDEC=insane_blocky16" service table; flobdec_Info is a static several LEC modules have,
   written with the module prefix); was Blocky16_GetInfoString. */

char * Blocky16_flobdec_Info(int param_1)

{
  if (param_1 == 0) {
    return s_Blocky16_Tile_004f3ab0;
  }
  if (param_1 != 1) {
    if (param_1 != 2) {
      return &DAT_004f5a98;
    }
    return s_This_module_decompresses_the_blo_004f3aec;
  }
  return s_Decompresses_a_block16_tile_vide_004f3ac0;
}

/* ---- 0x004cc3a0  Blocky16_flobdec_GetID ---- */
/* Returns the codec id Bl16 of the decoder Original name Blocky16_flobdec_GetID (the remaster's
   GrimFandango (Linux): slot 1 of the "FLOBDEC=insane_blocky16" service table; flobdec_GetID is a
   static several LEC modules have, written with the module prefix); was Blocky16_GetFourCC. */

undefined4 Blocky16_flobdec_GetID(void)

{
  return 0x426c3136;
}

/* ---- 0x004cc3c0  Blocky16_flobdec_DecodeHeader ---- */
/* Reallocates the three frame buffers when the frame size or depth of the header differs from the
   current ones Original name Blocky16_flobdec_DecodeHeader (the remaster's GrimFandango (Linux):
   slot 4 of the "FLOBDEC=insane_blocky16" service table; flobdec_DecodeHeader is a static several
   LEC modules have, written with the module prefix); was Blocky16_Prepare. */

undefined4 Blocky16_flobdec_DecodeHeader(int param_1)

{
  short sVar1;
  uint uVar2;
  
  sVar1 = *(short *)(param_1 + 2);
  uVar2 = (int)*(short *)(param_1 + 4) + 7U & 0xfffffff8;
  if ((((*(short *)(param_1 + 6) != g_nGlobal_bm_type) || (g_pBlkBitmap0 == (int *)0x0)) ||
      ((int)sVar1 != g_pBlkBitmap0[1])) || (uVar2 != g_pBlkBitmap0[2])) {
    Blocky16_flobdec_Reset();
    AllocBuffers((int)sVar1,uVar2,(int)*(short *)(param_1 + 6));
  }
  return 0;
}

/* ---- 0x004cc410  AllocBuffers ---- */
/* Allocates the three frame buffers (current, previous, before) for a frame size and clears them;
   sets up the display expand table memory Original name AllocBuffers (the remaster's GrimFandango
   (Linux): same body (three bitmaps, maketiles(4)/(8), shift = 0); blocky16 flobdec_DecodeHeader's
   callee); was Blocky16_AllocBuffers. */

int AllocBuffers(int param_1,int param_2,int param_3)

{
  int iVar1;
  
  g_nFob_buffersize = param_2 * param_1;
  fob_block_maketiles(4);
  fob_block_maketiles(8);
  g_nFob_translation_shiftr = 0;
  g_nFob_translation_shiftg = 0;
  g_nFob_translation_shiftb = 0;
  iVar1 = (*(code *)*g_pBlocky16_bitmap_services)(&g_pBlkBitmap0,param_1,param_2,param_3);
  if (iVar1 == 0) {
    iVar1 = (*(code *)*g_pBlocky16_bitmap_services)(&g_pBlkBitmap1,param_1,param_2,param_3);
    if (iVar1 == 0) {
      iVar1 = (*(code *)*g_pBlocky16_bitmap_services)(&g_pBlkBitmap2,param_1,param_2,param_3);
      if (iVar1 == 0) {
        g_nGlobal_bm_type = param_3;
        g_pFob_blk16_key_buffer = (byte *)*g_pBlkBitmap0;
        g_pFob_blk16_delta_buffer = (byte *)*g_pBlkBitmap1;
        g_pFob_blk16_render_buffer = (byte *)*g_pBlkBitmap2;
        msc_MemSet((uint)g_pFob_blk16_key_buffer,0,g_nFob_buffersize * 2);
        msc_MemSet((uint)g_pFob_blk16_delta_buffer,0,g_nFob_buffersize * 2);
        msc_MemSet((uint)g_pFob_blk16_render_buffer,0,g_nFob_buffersize * 2);
        g_pbBlkExpand =
             (byte *)(*(code *)*g_pBlocky16_memory_services)
                               (0x20000,s_C__grimsrc_libs_lecsmush_insane__004f3bbc,0x13e);
        iVar1 = (g_pbBlkExpand != (byte *)0x0) - 1;
        if (iVar1 == 0) {
          return 0;
        }
        (*(code *)g_pBlocky16_bitmap_services[2])(&g_pBlkBitmap2);
      }
      (*(code *)g_pBlocky16_bitmap_services[2])(&g_pBlkBitmap1);
    }
    (*(code *)g_pBlocky16_bitmap_services[2])(&g_pBlkBitmap0);
  }
  return iVar1;
}

/* ---- 0x004cc590  Blocky16_flobdec_Reset ---- */
/* Frees the three frame buffers and the expand table of the Blocky16 decoder Original name
   Blocky16_flobdec_Reset (the remaster's GrimFandango (Linux): the body of slot 3 of the
   "FLOBDEC=insane_blocky16" service table (the slot holds the JMP thunk 0x4cc3b0 to it);
   flobdec_Reset is a static several LEC modules have, written with the module prefix); was
   Blocky16_FreeBuffers. */

void Blocky16_flobdec_Reset(void)

{
  if (g_pBlkBitmap0 != (int *)0x0) {
    (*(code *)g_pBlocky16_bitmap_services[2])(&g_pBlkBitmap0);
  }
  if (g_pBlkBitmap1 != (int *)0x0) {
    (*(code *)g_pBlocky16_bitmap_services[2])(&g_pBlkBitmap1);
  }
  if (g_pBlkBitmap2 != (int *)0x0) {
    (*(code *)g_pBlocky16_bitmap_services[2])(&g_pBlkBitmap2);
  }
  if (g_pbBlkExpand != (byte *)0x0) {
    (*(code *)g_pBlocky16_memory_services[1])
              (g_pbBlkExpand,s_C__grimsrc_libs_lecsmush_insane__004f3bbc,0x156);
    g_pbBlkExpand = (byte *)0x0;
  }
  g_nFob_buffersize = 0;
  return;
}

/* ---- 0x004cc620  Blocky16_flobdec_DecodeBody ---- */
/* Interface entry of the decoder: drops the seventh argument and calls Blocky16_DecodeFrame
   Original name Blocky16_flobdec_DecodeBody (the remaster's GrimFandango (Linux): slot 5 of the
   "FLOBDEC=insane_blocky16" service table; flobdec_DecodeBody is a static several LEC modules have,
   written with the module prefix); was Blocky16_DecodeFrameEntry. */

void Blocky16_flobdec_DecodeBody
               (void *param_1,uint *param_2,int param_3,int param_4,int param_5,byte *param_6,
               undefined4 param_7,byte param_8)

{
  Blocky16_DecodeFrame(param_1,param_2,param_3,param_4,param_5,param_6,param_8);
  return;
}

/* ---- 0x004cc650  Blocky16_flobdec_GetVal ---- */
/* Reads four 16 bit fields of a frame header of the right size (0x100), returns -1 for any other
   size Original name Blocky16_flobdec_GetVal (the remaster's GrimFandango (Linux): slot 7 of the
   "FLOBDEC=insane_blocky16" service table; flobdec_GetVal is a static several LEC modules have,
   written with the module prefix); was Blocky16_GetFrameInfo. */

undefined4
Blocky16_flobdec_GetVal
          (short *param_1,int param_2,int *param_3,int *param_4,int *param_5,int *param_6)

{
  if (param_2 != 0x100) {
    return 0xffffffff;
  }
  if (param_3 != (int *)0x0) {
    *param_3 = (int)*param_1;
  }
  if (param_4 != (int *)0x0) {
    *param_4 = (int)param_1[2];
  }
  if (param_5 != (int *)0x0) {
    *param_5 = (int)param_1[4];
  }
  if (param_6 != (int *)0x0) {
    *param_6 = (int)param_1[6];
  }
  return 0;
}

/* ---- 0x004cc6a0  fob_blk16_configure ---- */
/* Makes the pixel offsets of the split masks and the motion vectors for a frame width, once per
   width Original name fob_blk16_configure (the remaster's GrimFandango (Linux): same body (skips
   when the width equals the static old_mod, rebuilds the motion offsets and the 4x4 / 8x8 tile
   tables for the width); the same call in the decoder when header +0x10 is 0, before the two
   gra_SetBuffer calls); was Blocky16_BuildPixelOffsets. */

void fob_blk16_configure(uint param_1)

{
  int iVar1;
  BlockyMotionVector *pBVar2;
  BlockyMotionVector *pBVar3;
  short *psVar4;
  byte *pbVar5;
  int iVar6;
  byte *pbVar7;
  short sVar8;
  byte *pbVar9;
  
  if (param_1 != g_dwFob_blk16_configure_old_mod) {
    g_dwFob_blk16_configure_old_mod = param_1;
    pBVar2 = g_aBlockyMotionVectors;
    psVar4 = &g_asBlockyMotion;
    do {
      pBVar3 = pBVar2 + 1;
      sVar8 = (short)param_1;
      *psVar4 = pBVar2->nY * sVar8 + pBVar2->nX;
      pBVar2 = pBVar3;
      psVar4 = psVar4 + 1;
    } while ((int)pBVar3 < ((unsigned)(uintptr_t)&g_dwFob_blk16_configure_old_mod));
    pbVar9 = &DAT_00906e00;
    pbVar5 = &DAT_0091f100;
    do {
      iVar6 = 0;
      if (*pbVar5 != 0) {
        pbVar7 = pbVar5 + -0x60;
        do {
          iVar1 = iVar6 + -0x20;
          iVar6 = iVar6 + 1;
          *(ushort *)pbVar7 = (ushort)(pbVar5[iVar1] >> 2) * sVar8 + (pbVar5[iVar1] & 3);
          pbVar7 = pbVar7 + 2;
        } while (iVar6 < (int)(uint)*pbVar5);
      }
      iVar6 = 0;
      if (pbVar5[1] != 0) {
        pbVar7 = pbVar5 + -0x40;
        do {
          *(ushort *)pbVar7 =
               (ushort)(pbVar5[iVar6 + -0x10] >> 2) * sVar8 + (pbVar5[iVar6 + -0x10] & 3);
          iVar6 = iVar6 + 1;
          pbVar7 = pbVar7 + 2;
        } while (iVar6 < (int)(uint)pbVar5[1]);
      }
      iVar6 = 0;
      if (*pbVar9 != 0) {
        pbVar7 = pbVar9 + -0x180;
        do {
          iVar1 = iVar6 + -0x80;
          iVar6 = iVar6 + 1;
          *(ushort *)pbVar7 = (ushort)(pbVar9[iVar1] >> 3) * sVar8 + (pbVar9[iVar1] & 7);
          pbVar7 = pbVar7 + 2;
        } while (iVar6 < (int)(uint)*pbVar9);
      }
      iVar6 = 0;
      if (pbVar9[1] != 0) {
        pbVar7 = pbVar9 + -0x100;
        do {
          *(ushort *)pbVar7 =
               (ushort)(pbVar9[iVar6 + -0x40] >> 3) * sVar8 + (pbVar9[iVar6 + -0x40] & 7);
          iVar6 = iVar6 + 1;
          pbVar7 = pbVar7 + 2;
        } while (iVar6 < (int)(uint)pbVar9[1]);
      }
      pbVar5 = pbVar5 + 0x80;
      pbVar9 = pbVar9 + 0x184;
    } while ((int)pbVar5 < ((unsigned)(uintptr_t)&DAT_00927100));
  }
  return;
}

/* ---- 0x004cc7d0  fob_block_maketiles ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Builds the 8x8 or 4x4 split masks of the Blocky16 codec in g_aBlockySplit8 or g_aBlockySplit4
   from the edge points g_anBlockySplit8X, g_anBlockySplit8Y, g_anBlockySplit4X and
   g_anBlockySplit4Y Original name fob_block_maketiles (the remaster's GrimFandango (Linux):
   AllocBuffers' calls with 4 and 8); was Blocky16_BuildSplitMasks. */

void __cdecl fob_block_maketiles(int size)

{
  unsigned char _frame[0x180] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  int iVar2;
  undefined1 *puVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  int iVar10;
  uint uVar11;
  int iVar12;
  int *piVar13;
  uint *puVar14;
  int iVar15;
  int *piVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  bool bVar20;
  #define local_168 (*(uint *)(_frame + (0x180 - 0x168)))
  #define local_164 (*(uint *)(_frame + (0x180 - 0x164)))
  #define local_160 (*(uint *)(_frame + (0x180 - 0x160)))
  #define local_15c (*(uint *)(_frame + (0x180 - 0x15c)))
  #define local_158 (*(uint *)(_frame + (0x180 - 0x158)))
  #define local_154 (*(uint *)(_frame + (0x180 - 0x154)))
  #define local_150 (*(uint *)(_frame + (0x180 - 0x150)))
  #define local_14c (*(uint *)(_frame + (0x180 - 0x14c)))
  #define local_148 (*(uint *)(_frame + (0x180 - 0x148)))
  #define local_144 (*(uint *)(_frame + (0x180 - 0x144)))
  #define local_140 (*(uint *)(_frame + (0x180 - 0x140)))
  #define local_13c (*(uint *)(_frame + (0x180 - 0x13c)))
  #define local_138 (*(uint *)(_frame + (0x180 - 0x138)))
  #define local_134 (*(uint *)(_frame + (0x180 - 0x134)))
  #define local_130 (*(uint *)(_frame + (0x180 - 0x130)))
  #define local_12c (*(uint *)(_frame + (0x180 - 0x12c)))
  #define local_128 (*(uint *)(_frame + (0x180 - 0x128)))
  #define local_124 (*(uint *)(_frame + (0x180 - 0x124)))
  #define local_120 (*(uint *)(_frame + (0x180 - 0x120)))
  #define local_11c (*(uint *)(_frame + (0x180 - 0x11c)))
  #define local_118 (*(uint *)(_frame + (0x180 - 0x118)))
  #define local_114 (*(uint *)(_frame + (0x180 - 0x114)))
  #define local_110 (*(uint *)(_frame + (0x180 - 0x110)))
  #define local_10c (*(uint *)(_frame + (0x180 - 0x10c)))
  #define local_108 (*(uint *)(_frame + (0x180 - 0x108)))
  #define local_104 (*(uint *)(_frame + (0x180 - 0x104)))
  #define auStack_100 (*(undefined4 (*)[15])(_frame + (0x180 - 0x100)))
  #define local_c4 (*(uint *)(_frame + (0x180 - 0xc4)))
  #define local_4 (*(uint *)(_frame + (0x180 - 0x4)))
  
  if (size == 8) {
    local_164 = (uint)g_anBlockySplit8Y;
    local_148 = (uint)g_anBlockySplit8X;
    puVar3 = &DAT_00906e00;
    do {
      *puVar3 = 0;
      puVar3 = puVar3 + 0x184;
    } while ((int)puVar3 < ((unsigned)(uintptr_t)&DAT_0091f200));
    puVar3 = &DAT_00906e01;
    do {
      *puVar3 = 0;
      puVar3 = puVar3 + 0x184;
    } while ((int)puVar3 < ((unsigned)(uintptr_t)&DAT_0091f201));
  }
  if (size == 4) {
    local_164 = (uint)g_anBlockySplit4Y;
    local_148 = (uint)g_anBlockySplit4X;
    puVar3 = &DAT_0091f100;
    do {
      *puVar3 = 0;
      puVar3 = puVar3 + 0x80;
    } while ((int)puVar3 < ((unsigned)(uintptr_t)&DAT_00927100));
    puVar3 = &DAT_0091f101;
    do {
      *puVar3 = 0;
      puVar3 = puVar3 + 0x80;
    } while ((int)puVar3 < ((unsigned)(uintptr_t)&DAT_00927101));
  }
  iVar4 = size * size;
  iVar18 = local_164 - local_148;
  local_138 = 0;
  local_158 = 0;
  local_150 = 0;
  local_14c = local_148;
  do {
    uVar5 = local_158 + 0x800;
    uVar11 = local_150 + 0x1840;
    local_124 = 0x10;
    piVar16 = (int *)local_164;
    do {
      iVar10 = *(int *)local_14c;
      if (iVar10 == 0) {
        local_168 = 0;
      }
      else if (iVar10 == size + -1) {
        local_168 = 1;
      }
      else if (*(int *)(iVar18 + local_14c) == 0) {
        local_168 = 2;
      }
      else {
        local_168 = (*(int *)(iVar18 + local_14c) != size + -1) + 3;
      }
      iVar2 = *(int *)((local_148 - local_164) + (int)piVar16);
      if (iVar2 == 0) {
        local_160 = 0;
      }
      else if (iVar2 == size + -1) {
        local_160 = 1;
      }
      else if (*piVar16 == 0) {
        local_160 = 2;
      }
      else {
        local_160 = (*piVar16 != size + -1) + 3;
      }
      if (iVar4 != 0) {
        puVar9 = auStack_100 + iVar4 + -1;
        iVar6 = iVar4;
        do {
          *puVar9 = 0;
          iVar6 = iVar6 + -1;
          puVar9 = puVar9 + -1;
        } while (iVar6 != 0);
      }
      iVar6 = *piVar16;
      if (*(int *)(local_138 + local_164) - iVar6 < 0) {
        iVar17 = *(int *)(iVar18 + local_14c);
        iVar7 = iVar6 - iVar17;
      }
      else {
        iVar17 = *(int *)(iVar18 + local_14c);
        iVar7 = iVar17 - iVar6;
      }
      iVar15 = iVar10 - iVar2;
      iVar19 = iVar15;
      if (iVar15 < 0) {
        iVar19 = iVar2 - iVar10;
      }
      if (iVar19 < iVar7) {
        iVar15 = iVar17 - iVar6;
        if (iVar15 < 0) {
          iVar15 = iVar6 - iVar17;
        }
      }
      else if (iVar15 < 0) {
        iVar15 = iVar2 - iVar10;
      }
      uVar1 = iVar15 + 1;
      if (0 < (int)uVar1) {
        local_140 = 0;
        local_144 = 0;
        iVar19 = iVar2 * uVar1;
        iVar7 = uVar1 * iVar6;
        local_130 = uVar1;
        do {
          iVar8 = iVar10;
          iVar12 = iVar17;
          if (1 < (int)uVar1) {
            iVar8 = (int)((iVar19 - iVar2) + local_140 + (iVar15 >> 1)) / iVar15;
            iVar12 = (int)((iVar7 - iVar6) + local_144 + (iVar15 >> 1)) / iVar15;
          }
          puVar9 = auStack_100 + iVar8 * size + iVar12;
          *puVar9 = 1;
          if ((((local_168 == 2) && (local_160 == 3)) || ((local_160 == 2 && (local_168 == 3)))) ||
             ((local_168 == 0 && (local_160 != 1)))) {
LAB_004ccab2:
            if (-1 < iVar8) {
              iVar8 = iVar8 + 1;
              do {
                *puVar9 = 1;
                puVar9 = puVar9 + -size;
                iVar8 = iVar8 + -1;
              } while (iVar8 != 0);
            }
          }
          else if (local_160 == 0) {
            if (local_168 != 1) goto LAB_004ccab2;
LAB_004ccae4:
            if (local_160 == 0) goto LAB_004ccae8;
LAB_004ccaf1:
            if (iVar8 < size) {
              iVar8 = size - iVar8;
              do {
                *puVar9 = 1;
                puVar9 = puVar9 + size;
                iVar8 = iVar8 + -1;
              } while (iVar8 != 0);
            }
          }
          else {
            if (local_168 == 1) goto LAB_004ccae4;
LAB_004ccae8:
            if (local_160 == 1) {
              if (local_168 != 0) goto LAB_004ccaf1;
LAB_004ccb1e:
              if (local_160 != 1) goto LAB_004ccb23;
            }
            else {
              if (local_168 == 0) goto LAB_004ccb1e;
LAB_004ccb23:
              if (((local_160 != 0) || (local_168 != 1)) && ((local_168 != 3 || (local_160 == 2))))
              {
                if (local_160 == 3) {
                  if (local_168 != 2) goto LAB_004ccb40;
LAB_004ccb67:
                  if (local_160 == 3) goto LAB_004ccb6c;
                }
                else {
                  if (local_168 == 2) goto LAB_004ccb67;
LAB_004ccb6c:
                  if ((local_160 != 2) || (local_168 == 3)) goto LAB_004ccb89;
                }
                if (-1 < iVar12) {
                  iVar12 = iVar12 + 1;
                  do {
                    *puVar9 = 1;
                    puVar9 = puVar9 + -1;
                    iVar12 = iVar12 + -1;
                  } while (iVar12 != 0);
                }
                goto LAB_004ccb89;
              }
            }
LAB_004ccb40:
            if (iVar12 < size) {
              for (iVar12 = size - iVar12; iVar12 != 0; iVar12 = iVar12 + -1) {
                *puVar9 = 1;
                puVar9 = puVar9 + 1;
              }
            }
          }
LAB_004ccb89:
          local_144 = local_144 + iVar17;
          local_140 = local_140 + iVar10;
          iVar7 = iVar7 - iVar6;
          iVar19 = iVar19 - iVar2;
          local_130 = local_130 - 1;
        } while (local_130 != 0);
      }
      if (size == 8) {
        iVar10 = 0x3f;
        piVar13 = (int *)REGISTER0X(0x00000010);
        do {
          piVar13 = piVar13 + -1;
          if (*piVar13 == 0) {
            (&DAT_00906dc0)[local_150 + (byte)(&DAT_00906e01)[local_150]] = (char)iVar10;
            (&DAT_00906e01)[local_150] = (&DAT_00906e01)[local_150] + '\x01';
          }
          else {
            (&DAT_00906d80)[local_150 + (byte)(&DAT_00906e00)[local_150]] = (char)iVar10;
            (&DAT_00906e00)[local_150] = (&DAT_00906e00)[local_150] + '\x01';
          }
          bVar20 = iVar10 != 0;
          iVar10 = iVar10 + -1;
        } while (bVar20);
      }
      else if (size == 4) {
        puVar14 = &local_c4;
        iVar10 = 0xf;
        do {
          if (*puVar14 == 0) {
            (&DAT_0091f0f0)[local_158 + (byte)(&DAT_0091f101)[local_158]] = (char)iVar10;
            (&DAT_0091f101)[local_158] = (&DAT_0091f101)[local_158] + '\x01';
          }
          else {
            (&DAT_0091f0e0)[local_158 + (byte)(&DAT_0091f100)[local_158]] = (char)iVar10;
            (&DAT_0091f100)[local_158] = (&DAT_0091f100)[local_158] + '\x01';
          }
          puVar14 = puVar14 + -1;
          bVar20 = iVar10 != 0;
          iVar10 = iVar10 + -1;
        } while (bVar20);
      }
      local_150 = local_150 + 0x184;
      local_158 = local_158 + 0x80;
      piVar16 = piVar16 + 1;
      local_124 = local_124 - 1;
    } while (local_124 != 0);
    local_138 = local_138 + 4;
    local_14c = local_14c + 4;
    local_158 = uVar5;
    local_150 = uVar11;
    if (0x3f < (int)local_138) {
      return;
    }
  } while( true );
}
#undef auStack_100
#undef local_104
#undef local_108
#undef local_10c
#undef local_110
#undef local_114
#undef local_118
#undef local_11c
#undef local_120
#undef local_124
#undef local_128
#undef local_12c
#undef local_130
#undef local_134
#undef local_138
#undef local_13c
#undef local_140
#undef local_144
#undef local_148
#undef local_14c
#undef local_150
#undef local_154
#undef local_158
#undef local_15c
#undef local_160
#undef local_164
#undef local_168
#undef local_4
#undef local_c4

#endif


/* ---- 0x004ccd00  Blocky16_DecodeFrame ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Decodes one Blocky16 frame into the buffers g_pFob_blk16_render_buffer, g_pFob_blk16_delta_buffer
   and g_pFob_blk16_key_buffer using g_stBlockyDecState, g_asBlockyMotion, g_aBlockySplit4 and
   g_aBlockySplit8 and gives it to the output g_pFob_blit_routine; bitmaps g_pBlkBitmap0,
   g_pBlkBitmap1, g_pBlkBitmap2; tables g_pbBlkExpand, g_nFob_translation_shiftr,
   g_nFob_translation_shiftg, g_nFob_translation_shiftb, g_pbBlkOutput, g_nBlkLastSeq */

int __cdecl Blocky16_DecodeFrame(void *dst,uint *clip,int x,int y,int palette,byte *hdr,byte flags)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  byte *pbVar5;
  byte *pbVar6;
  int extraout_ECX;
  int iVar7;
  uint uVar8;
  int *piVar9;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar8 = (uint)*(short *)(hdr + 8);
  iVar7 = (int)*(short *)(hdr + 0xc);
  pbVar5 = hdr + 0x230;
  if (((g_pBlkBitmap0 == (int *)0x0) || (uVar8 != g_pBlkBitmap0[1])) ||
     ((iVar7 + 7U & 0xfffffff8) != g_pBlkBitmap0[2])) {
    Blocky16_flobdec_Reset();
    iVar3 = (int)*(short *)(hdr + 0x228);
    if (*(short *)(hdr + 0x228) == 0) {
      iVar3 = 8;
    }
    AllocBuffers(uVar8,iVar7 + 7U & 0xfffffff8,iVar3);
  }
  iVar3 = (int)g_pFob_blk16_delta_buffer - (int)g_pFob_blk16_render_buffer;
  iVar4 = (int)g_pFob_blk16_key_buffer - (int)g_pFob_blk16_render_buffer;
  if (dst != (void *)0x0) {
    Blocky16_BuildExpandTable(dst);
  }
  if (*(short *)(hdr + 0x10) == 0) {
    fob_blk16_configure(uVar8);
    gra_SetBuffer((char *)g_pFob_blk16_key_buffer,(int)g_pBlkBitmap0,
                  g_pBlkBitmap0[1] * g_pBlkBitmap0[2],(char *)(hdr + 0x20));
    gra_SetBuffer((char *)g_pFob_blk16_delta_buffer,(int)g_pBlkBitmap0,
                  g_pBlkBitmap0[1] * g_pBlkBitmap0[2],(char *)(hdr + 0x20));
    g_nBlkLastSeq = -1;
  }
  g_nBretsFrameCount = g_nBretsFrameCount + 1;
  switch(hdr[0x12]) {
  case 0:
    goto LAB_004ccf61;
  case 1:
    Blocky16_DecodeHalfRows16(g_pFob_blk16_render_buffer,pbVar5,uVar8,iVar7);
    g_pbBlkOutput = g_pFob_blk16_render_buffer;
    break;
  case 2:
    if (((flags & 4) != 0) && (hdr[0x13] == 0)) {
      g_nBlkLastSeq = (int)*(short *)(hdr + 0x10);
      return 0;
    }
    if ((int)*(short *)(hdr + 0x10) == g_nBlkLastSeq + 1) {
      Blocky16_DecodeBlocks
                (g_pFob_blk16_render_buffer,pbVar5,iVar3 >> 1,iVar4 >> 1,uVar8,&g_asBlockyMotion,
                 (short *)(hdr + 0x18),iVar7,uVar8 * 9 - (uVar8 & 0xfffffff8),
                 (byte *)&g_aBlockySplit4,(byte *)&g_aBlockySplit8,(ushort *)(hdr + 0x28));
      g_pbBlkOutput = g_pFob_blk16_render_buffer;
    }
    break;
  case 3:
    pbVar5 = g_pFob_blk16_delta_buffer;
    if (((flags & 4) != 0) && (hdr[0x13] == 0)) {
      g_nBlkLastSeq = (int)*(short *)(hdr + 0x10);
      return 0;
    }
    goto LAB_004ccf61;
  case 4:
    pbVar5 = g_pFob_blk16_key_buffer;
    if (((flags & 4) != 0) && (hdr[0x13] == 0)) {
      g_nBlkLastSeq = (int)*(short *)(hdr + 0x10);
      return 0;
    }
LAB_004ccf61:
    msc_MemCopy(g_pFob_blk16_render_buffer,pbVar5,uVar8 * iVar7 * 2);
LAB_004ccf67:
    g_pbBlkOutput = g_pFob_blk16_render_buffer;
    break;
  case 5:
    msc_rle_DecompressBlock(g_pFob_blk16_render_buffer,(uint)pbVar5,*(int *)(hdr + 0x24));
    goto LAB_004ccf67;
  case 6:
    iVar7 = uVar8 * iVar7;
    pbVar6 = g_pFob_blk16_render_buffer;
    g_pbBlkOutput = g_pFob_blk16_render_buffer;
    if (iVar7 != 0) {
      do {
        bVar1 = *pbVar5;
        pbVar5 = pbVar5 + 1;
        iVar7 = iVar7 + -1;
        *(undefined2 *)pbVar6 = *(undefined2 *)(hdr + (uint)bVar1 * 2 + 0x28);
        pbVar6 = pbVar6 + 2;
      } while (iVar7 != 0);
      g_pbBlkOutput = g_pFob_blk16_render_buffer;
    }
    break;
  case 7:
    Blocky16_DecodeHalfRows8(g_pFob_blk16_render_buffer,pbVar5,uVar8,iVar7,hdr + 0x28);
    g_pbBlkOutput = g_pFob_blk16_render_buffer;
    break;
  case 8:
    msc_rle_DecompressInitialize(pbVar5);
    iVar7 = uVar8 * iVar7;
    iVar3 = iVar7;
    pbVar5 = g_pFob_blk16_render_buffer;
    for (; iVar7 != 0; iVar7 = iVar7 + -1) {
      uVar8 = msc_rle_DecompressGetbyte(iVar3);
      *(undefined2 *)pbVar5 = *(undefined2 *)(hdr + (uVar8 & 0xff) * 2 + 0x28);
      iVar3 = extraout_ECX;
      pbVar5 = pbVar5 + 2;
    }
    Mem_DumpLog();
    g_pbBlkOutput = g_pFob_blk16_render_buffer;
  }
  if ((g_pbBlkOutput != (byte *)0x0) && (dst != (void *)0x0)) {
    pbVar5 = g_pbBlkExpand;
    if ((g_nFob_translation_shiftr == 0) && (g_nFob_translation_shiftg == 0)) {
      pbVar5 = (byte *)0x0;
    }
    if (g_pFob_blit_routine == (void *)0x0) {
      piVar9 = g_pBlkBitmap0;
      if (((g_pbBlkOutput == (byte *)*g_pBlkBitmap0) ||
          (piVar9 = g_pBlkBitmap1, g_pbBlkOutput == (byte *)*g_pBlkBitmap1)) ||
         (piVar9 = g_pBlkBitmap2, g_pbBlkOutput == (byte *)*g_pBlkBitmap2)) {
        gra_BlitRectLookup(dst,clip,x,y,piVar9,palette,pbVar5);
      }
      palette = 1;
    }
    else if (g_pbBlkOutput == (byte *)*g_pBlkBitmap0) {
      palette = (*(code *)g_pFob_blit_routine)(dst,clip,x,y,g_pBlkBitmap0,palette,pbVar5);
    }
    else if (g_pbBlkOutput == (byte *)*g_pBlkBitmap1) {
      palette = (*(code *)g_pFob_blit_routine)(dst,clip,x,y,g_pBlkBitmap1,palette,pbVar5);
    }
    else if (g_pbBlkOutput == (byte *)*g_pBlkBitmap2) {
      palette = (*(code *)g_pFob_blit_routine)(dst,clip,x,y,g_pBlkBitmap2,palette,pbVar5);
    }
  }
  pbVar2 = g_pFob_blk16_delta_buffer;
  pbVar6 = g_pFob_blk16_key_buffer;
  pbVar5 = g_pFob_blk16_render_buffer;
  if ((int)*(short *)(hdr + 0x10) == g_nBlkLastSeq + 1) {
    if (hdr[0x13] == 1) {
      g_pFob_blk16_delta_buffer = g_pFob_blk16_render_buffer;
      g_pFob_blk16_render_buffer = pbVar2;
      g_nBlkLastSeq = (int)*(short *)(hdr + 0x10);
      return palette;
    }
    if (hdr[0x13] == 2) {
      g_pFob_blk16_key_buffer = g_pFob_blk16_delta_buffer;
      g_pFob_blk16_render_buffer = pbVar6;
      g_pFob_blk16_delta_buffer = pbVar5;
    }
  }
  g_nBlkLastSeq = (int)*(short *)(hdr + 0x10);
  return palette;
}
#undef local_4
#undef local_8

#endif


/* ---- 0x004cd1e0  Blocky16_BuildExpandTable ---- */
/* Makes the 64K entry table that converts 16 bit pixels to the display format when the display
   channel shifts change */

void Blocky16_BuildExpandTable(void *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  if (((((g_pbBlkExpand != (byte *)0x0) && (*(int *)((int)param_1 + 0xc) == 2)) &&
       ((*(int *)((int)param_1 + 0x20) == 1 || (*(int *)((int)param_1 + 0x20) == 2)))) &&
      (((*(int *)((int)param_1 + 0x30) != g_pBlkBitmap0[0xc] ||
        (*(int *)((int)param_1 + 0x38) != g_pBlkBitmap0[0xe])) ||
       (*(int *)((int)param_1 + 0x34) != g_pBlkBitmap0[0xd])))) &&
     (((*(int *)((int)param_1 + 0x30) != g_nFob_translation_shiftr ||
       (*(int *)((int)param_1 + 0x38) != g_nFob_translation_shiftb)) ||
      (*(int *)((int)param_1 + 0x34) != g_nFob_translation_shiftg)))) {
    g_nFob_translation_shiftr = *(int *)((int)param_1 + 0x30);
    g_nFob_translation_shiftg = *(int *)((int)param_1 + 0x34);
    g_nFob_translation_shiftb = *(int *)((int)param_1 + 0x38);
    for (local_8 = 0; (int)local_8 < 0x10000; local_8 = local_8 + 1) {
      *(undefined2 *)(g_pbBlkExpand + local_8 * 2) = (undefined2)local_8;
    }
    gra_ConvertCopy(g_pbBlkExpand,g_pBlkBitmap0,0x10000,(byte *)0x0,g_pbBlkExpand,param_1,
                    (byte *)0x0);
  }
  return;
}
#undef local_8


/* ---- 0x004cd300  Blocky16_DecodeHalfRows16 ---- */
/* Decodes a method 1 frame: 16 bit pixels of every second row, the rows between are averaged */

void Blocky16_DecodeHalfRows16(void *param_1,ushort *param_2,int param_3,int param_4)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  ushort uVar1;
  int iVar2;
  undefined2 uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  ushort uVar7;
  undefined2 *puVar8;
  uint *puVar9;
  undefined4 *puVar10;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar5 = param_3 * 2;
  if (0 < param_4) {
    local_10 = param_4 + 1U >> 1;
    puVar10 = (undefined4 *)((int)param_1 + uVar5);
    do {
      puVar9 = puVar10 + 1;
      uVar7 = *param_2;
      param_2 = param_2 + 1;
      *puVar10 = CONCAT22(uVar7,uVar7);
      if (0 < param_3 + -2) {
        uVar6 = param_3 - 1U >> 1;
        do {
          uVar1 = *param_2;
          param_2 = param_2 + 1;
          uVar4 = FUN_004cd3f0(uVar7,uVar1);
          *puVar9 = uVar4 & 0xffff | (uint)uVar1 << 0x10;
          puVar9 = puVar9 + 1;
          uVar6 = uVar6 - 1;
          uVar7 = uVar1;
        } while (uVar6 != 0);
      }
      puVar10 = (undefined4 *)((int)puVar9 + uVar5);
      local_10 = local_10 - 1;
    } while (local_10 != 0);
  }
  msc_MemCopy(param_1,(undefined4 *)((int)param_1 + uVar5),uVar5);
  puVar8 = (undefined2 *)((int)param_1 + param_3 * 4);
  if (param_4 != 2 && -1 < param_4 + -2) {
    uVar5 = param_4 - 1U >> 1;
    iVar2 = param_3;
    do {
      for (; iVar2 != 0; iVar2 = iVar2 + -1) {
        uVar3 = FUN_004cd3f0(puVar8[param_3],puVar8[-param_3]);
        *puVar8 = uVar3;
        puVar8 = puVar8 + 1;
      }
      puVar8 = puVar8 + param_3;
      uVar5 = uVar5 - 1;
      iVar2 = param_3;
    } while (uVar5 != 0);
  }
  return;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004cd450  Blocky16_DecodeHalfRows8 ---- */
/* Decodes a method 7 frame: 8 bit indexes of every second row through a colour table, the rows
   between are averaged */

void Blocky16_DecodeHalfRows8(void *param_1,byte *param_2,int param_3,int param_4,int param_5)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  ushort uVar2;
  int iVar3;
  undefined2 uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  ushort uVar8;
  undefined2 *puVar9;
  uint *puVar10;
  undefined4 *puVar11;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar6 = param_3 * 2;
  if (0 < param_4) {
    local_10 = param_4 + 1U >> 1;
    puVar11 = (undefined4 *)((int)param_1 + uVar6);
    do {
      bVar1 = *param_2;
      param_2 = param_2 + 1;
      puVar10 = puVar11 + 1;
      uVar8 = *(ushort *)(param_5 + (uint)bVar1 * 2);
      *puVar11 = CONCAT22(uVar8,uVar8);
      if (0 < param_3 + -2) {
        uVar7 = param_3 - 1U >> 1;
        do {
          bVar1 = *param_2;
          param_2 = param_2 + 1;
          uVar2 = *(ushort *)(param_5 + (uint)bVar1 * 2);
          uVar5 = FUN_004cd3f0(uVar8,uVar2);
          *puVar10 = uVar5 & 0xffff | (uint)uVar2 << 0x10;
          puVar10 = puVar10 + 1;
          uVar7 = uVar7 - 1;
          uVar8 = uVar2;
        } while (uVar7 != 0);
      }
      puVar11 = (undefined4 *)((int)puVar10 + uVar6);
      local_10 = local_10 - 1;
    } while (local_10 != 0);
  }
  msc_MemCopy(param_1,(undefined4 *)((int)param_1 + uVar6),uVar6);
  puVar9 = (undefined2 *)((int)param_1 + param_3 * 4);
  if (param_4 != 2 && -1 < param_4 + -2) {
    uVar6 = param_4 - 1U >> 1;
    iVar3 = param_3;
    do {
      for (; iVar3 != 0; iVar3 = iVar3 + -1) {
        uVar4 = FUN_004cd3f0(puVar9[param_3],puVar9[-param_3]);
        *puVar9 = uVar4;
        puVar9 = puVar9 + 1;
      }
      puVar9 = puVar9 + param_3;
      uVar6 = uVar6 - 1;
      iVar3 = param_3;
    } while (uVar6 != 0);
  }
  return;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004cd550  Blocky16_DecodeBlocks ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Decodes all 8x8 blocks of a method 2 frame into the current buffer (state in g_stBlockyDecState)
    */

void __cdecl
Blocky16_DecodeBlocks
          (byte *dst,byte *src,int prevOffset,int prev2Offset,int width,short *motion,short *colors,
          int height,int unused,byte *split4,byte *split8,ushort *pairColors)

{
  unsigned char _stkneg[32] __attribute__((aligned(16)));  /* the original frame below the return address */
  byte *unaff_ESI;
  byte *unaff_EDI;
  undefined1 *pitch;
  
  pitch = (_stkneg + 28);
  _DAT_00906c58 = prevOffset * 2;
  UINT_00906c68 = prev2Offset * 2;
  _DAT_00906c60 = width;
  UINT_00906c4c = (uint)motion;
  UINT_00906c54 = (uint)(colors + -0xf9);
  _DAT_00906c70 = split4;
  _DAT_00906c50 = split8;
  UINT_00906c6c = (uint)pairColors;
  DAT_00906c5c = (char)(height + 7U >> 3);
  DAT_00906c64 = (char)(width + 7U >> 3);
  g_stBlockyDecState = width * 0xe;
  do {
    DAT_00906c5d = DAT_00906c64;
    do {
      Blocky16_DecodeBlock8(unaff_EDI,unaff_ESI,(int)pitch);
      DAT_00906c5d = DAT_00906c5d + -1;
    } while (DAT_00906c5d != '\0');
    DAT_00906c5c = DAT_00906c5c + -1;
  } while (DAT_00906c5c != '\0');
  return;
}
#endif


/* ---- 0x004cd610  Blocky16_DecodeBlock8 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Decodes one 8x8 block (register convention in the original: ESI stream, EDI destination, EBP
   pitch) */

byte * __cdecl Blocky16_DecodeBlock8(byte *src,byte *dst,int pitch)

{
  byte bVar1;
  short sVar2;
  bool bVar3;
  undefined2 uVar4;
  ushort *puVar5;
  int iVar6;
  undefined4 uVar7;
  ushort *puVar8;
  int unaff_EBP;
  uint uVar9;
  uint uVar10;
  byte *unaff_ESI;
  byte *pbVar11;
  byte *pbVar12;
  byte *unaff_EDI;
  byte *pbVar13;
  byte *unaff_retaddr;
  
  uVar10 = UINT_00906c68;
  bVar1 = *unaff_ESI;
  if (bVar1 < 0xf6) {
    if (bVar1 == 0xf5) {
      sVar2 = *(short *)(unaff_ESI + 1);
    }
    else {
      sVar2 = *(short *)(UINT_00906c4c + (uint)bVar1 * 2);
    }
    iVar6 = sVar2 * 2 + _DAT_00906c58;
    pbVar11 = unaff_EDI + unaff_EBP * 4;
    uVar7 = *(undefined4 *)(unaff_EDI + iVar6);
    *(undefined4 *)pbVar11 = *(undefined4 *)(pbVar11 + iVar6);
    *(undefined4 *)unaff_EDI = uVar7;
    uVar7 = *(undefined4 *)(unaff_EDI + iVar6 + 4);
    *(undefined4 *)(pbVar11 + 4) = *(undefined4 *)(pbVar11 + iVar6 + 4);
    *(undefined4 *)(unaff_EDI + 4) = uVar7;
    uVar7 = *(undefined4 *)(unaff_EDI + iVar6 + 8);
    *(undefined4 *)(pbVar11 + 8) = *(undefined4 *)(pbVar11 + iVar6 + 8);
    *(undefined4 *)(unaff_EDI + 8) = uVar7;
    uVar7 = *(undefined4 *)(unaff_EDI + iVar6 + 0xc);
    *(undefined4 *)(pbVar11 + 0xc) = *(undefined4 *)(pbVar11 + iVar6 + 0xc);
    *(undefined4 *)(unaff_EDI + 0xc) = uVar7;
    pbVar11 = pbVar11 + unaff_EBP;
    pbVar13 = unaff_EDI + unaff_EBP;
    uVar7 = *(undefined4 *)(pbVar13 + iVar6);
    *(undefined4 *)pbVar11 = *(undefined4 *)(pbVar11 + iVar6);
    *(undefined4 *)pbVar13 = uVar7;
    uVar7 = *(undefined4 *)(pbVar13 + iVar6 + 4);
    *(undefined4 *)(pbVar11 + 4) = *(undefined4 *)(pbVar11 + iVar6 + 4);
    *(undefined4 *)(pbVar13 + 4) = uVar7;
    uVar7 = *(undefined4 *)(pbVar13 + iVar6 + 8);
    *(undefined4 *)(pbVar11 + 8) = *(undefined4 *)(pbVar11 + iVar6 + 8);
    *(undefined4 *)(pbVar13 + 8) = uVar7;
    uVar7 = *(undefined4 *)(pbVar13 + iVar6 + 0xc);
    *(undefined4 *)(pbVar11 + 0xc) = *(undefined4 *)(pbVar11 + iVar6 + 0xc);
    *(undefined4 *)(pbVar13 + 0xc) = uVar7;
    pbVar11 = pbVar11 + unaff_EBP;
    pbVar13 = pbVar13 + unaff_EBP;
    uVar7 = *(undefined4 *)(pbVar13 + iVar6);
    *(undefined4 *)pbVar11 = *(undefined4 *)(pbVar11 + iVar6);
    *(undefined4 *)pbVar13 = uVar7;
    uVar7 = *(undefined4 *)(pbVar13 + iVar6 + 4);
    *(undefined4 *)(pbVar11 + 4) = *(undefined4 *)(pbVar11 + iVar6 + 4);
    *(undefined4 *)(pbVar13 + 4) = uVar7;
    uVar7 = *(undefined4 *)(pbVar13 + iVar6 + 8);
    *(undefined4 *)(pbVar11 + 8) = *(undefined4 *)(pbVar11 + iVar6 + 8);
    *(undefined4 *)(pbVar13 + 8) = uVar7;
    uVar7 = *(undefined4 *)(pbVar13 + iVar6 + 0xc);
    *(undefined4 *)(pbVar11 + 0xc) = *(undefined4 *)(pbVar11 + iVar6 + 0xc);
    *(undefined4 *)(pbVar13 + 0xc) = uVar7;
    pbVar11 = pbVar11 + unaff_EBP;
    pbVar13 = pbVar13 + unaff_EBP;
    uVar7 = *(undefined4 *)(pbVar13 + iVar6);
    *(undefined4 *)pbVar11 = *(undefined4 *)(pbVar11 + iVar6);
    *(undefined4 *)pbVar13 = uVar7;
    uVar7 = *(undefined4 *)(pbVar13 + iVar6 + 4);
    *(undefined4 *)(pbVar11 + 4) = *(undefined4 *)(pbVar11 + iVar6 + 4);
    *(undefined4 *)(pbVar13 + 4) = uVar7;
    uVar7 = *(undefined4 *)(pbVar13 + iVar6 + 8);
    *(undefined4 *)(pbVar11 + 8) = *(undefined4 *)(pbVar11 + iVar6 + 8);
    *(undefined4 *)(pbVar13 + 8) = uVar7;
    pbVar12 = *(byte **)(pbVar11 + iVar6 + 0xc);
    uVar7 = *(undefined4 *)(pbVar13 + iVar6 + 0xc);
    *(byte **)(pbVar11 + 0xc) = pbVar12;
    *(undefined4 *)(pbVar13 + 0xc) = uVar7;
    return pbVar12;
  }
  if (bVar1 == 0xff) {
    block16_RenderBlock4(unaff_EDI,unaff_retaddr,(int)src);
    block16_RenderBlock4(unaff_EDI,unaff_retaddr,(int)src);
    block16_RenderBlock4(unaff_EDI,unaff_retaddr,(int)src);
    pbVar11 = block16_RenderBlock4(unaff_EDI,unaff_retaddr,(int)src);
    return pbVar11;
  }
  if (bVar1 < 0xfe) {
    if (bVar1 == 0xfd) {
      uVar4 = (undefined2)*(undefined4 *)(UINT_00906c6c + (uint)unaff_ESI[1] * 2);
      pbVar11 = (byte *)CONCAT22(uVar4,uVar4);
    }
    else {
      if (bVar1 < 0xf9) {
        if (bVar1 == 0xf8) {
          uVar7 = *(undefined4 *)(unaff_ESI + 2);
          bVar1 = unaff_ESI[1];
        }
        else {
          if (bVar1 != 0xf7) {
            pbVar11 = unaff_EDI + unaff_EBP * 4;
            uVar7 = *(undefined4 *)(unaff_EDI + UINT_00906c68);
            *(undefined4 *)pbVar11 = *(undefined4 *)(pbVar11 + UINT_00906c68);
            *(undefined4 *)unaff_EDI = uVar7;
            uVar7 = *(undefined4 *)(unaff_EDI + uVar10 + 4);
            *(undefined4 *)(pbVar11 + 4) = *(undefined4 *)(pbVar11 + uVar10 + 4);
            *(undefined4 *)(unaff_EDI + 4) = uVar7;
            uVar7 = *(undefined4 *)(unaff_EDI + uVar10 + 8);
            *(undefined4 *)(pbVar11 + 8) = *(undefined4 *)(pbVar11 + uVar10 + 8);
            *(undefined4 *)(unaff_EDI + 8) = uVar7;
            uVar7 = *(undefined4 *)(unaff_EDI + uVar10 + 0xc);
            *(undefined4 *)(pbVar11 + 0xc) = *(undefined4 *)(pbVar11 + uVar10 + 0xc);
            *(undefined4 *)(unaff_EDI + 0xc) = uVar7;
            pbVar11 = pbVar11 + unaff_EBP;
            pbVar13 = unaff_EDI + unaff_EBP;
            uVar7 = *(undefined4 *)(pbVar13 + uVar10);
            *(undefined4 *)pbVar11 = *(undefined4 *)(pbVar11 + uVar10);
            *(undefined4 *)pbVar13 = uVar7;
            uVar7 = *(undefined4 *)(pbVar13 + uVar10 + 4);
            *(undefined4 *)(pbVar11 + 4) = *(undefined4 *)(pbVar11 + uVar10 + 4);
            *(undefined4 *)(pbVar13 + 4) = uVar7;
            uVar7 = *(undefined4 *)(pbVar13 + uVar10 + 8);
            *(undefined4 *)(pbVar11 + 8) = *(undefined4 *)(pbVar11 + uVar10 + 8);
            *(undefined4 *)(pbVar13 + 8) = uVar7;
            uVar7 = *(undefined4 *)(pbVar13 + uVar10 + 0xc);
            *(undefined4 *)(pbVar11 + 0xc) = *(undefined4 *)(pbVar11 + uVar10 + 0xc);
            *(undefined4 *)(pbVar13 + 0xc) = uVar7;
            pbVar11 = pbVar11 + unaff_EBP;
            pbVar13 = pbVar13 + unaff_EBP;
            uVar7 = *(undefined4 *)(pbVar13 + uVar10);
            *(undefined4 *)pbVar11 = *(undefined4 *)(pbVar11 + uVar10);
            *(undefined4 *)pbVar13 = uVar7;
            uVar7 = *(undefined4 *)(pbVar13 + uVar10 + 4);
            *(undefined4 *)(pbVar11 + 4) = *(undefined4 *)(pbVar11 + uVar10 + 4);
            *(undefined4 *)(pbVar13 + 4) = uVar7;
            uVar7 = *(undefined4 *)(pbVar13 + uVar10 + 8);
            *(undefined4 *)(pbVar11 + 8) = *(undefined4 *)(pbVar11 + uVar10 + 8);
            *(undefined4 *)(pbVar13 + 8) = uVar7;
            uVar7 = *(undefined4 *)(pbVar13 + uVar10 + 0xc);
            *(undefined4 *)(pbVar11 + 0xc) = *(undefined4 *)(pbVar11 + uVar10 + 0xc);
            *(undefined4 *)(pbVar13 + 0xc) = uVar7;
            pbVar11 = pbVar11 + unaff_EBP;
            pbVar13 = pbVar13 + unaff_EBP;
            uVar7 = *(undefined4 *)(pbVar13 + uVar10);
            *(undefined4 *)pbVar11 = *(undefined4 *)(pbVar11 + uVar10);
            *(undefined4 *)pbVar13 = uVar7;
            uVar7 = *(undefined4 *)(pbVar13 + uVar10 + 4);
            *(undefined4 *)(pbVar11 + 4) = *(undefined4 *)(pbVar11 + uVar10 + 4);
            *(undefined4 *)(pbVar13 + 4) = uVar7;
            uVar7 = *(undefined4 *)(pbVar13 + uVar10 + 8);
            *(undefined4 *)(pbVar11 + 8) = *(undefined4 *)(pbVar11 + uVar10 + 8);
            *(undefined4 *)(pbVar13 + 8) = uVar7;
            pbVar12 = *(byte **)(pbVar11 + uVar10 + 0xc);
            uVar7 = *(undefined4 *)(pbVar13 + uVar10 + 0xc);
            *(byte **)(pbVar11 + 0xc) = pbVar12;
            *(undefined4 *)(pbVar13 + 0xc) = uVar7;
            return pbVar12;
          }
          uVar7 = CONCAT22(*(undefined2 *)
                            (UINT_00906c6c +
                            (uint)(byte)((ushort)*(undefined2 *)(unaff_ESI + 2) >> 8) * 2),
                           *(undefined2 *)
                            (UINT_00906c6c + (uint)(byte)*(undefined2 *)(unaff_ESI + 2) * 2));
          bVar1 = unaff_ESI[1];
        }
        puVar5 = (ushort *)((uint)bVar1 * 0x184 + _DAT_00906c50);
        puVar8 = puVar5;
        uVar10 = (uint)(byte)puVar5[0xc0];
        do {
          *(short *)(unaff_EDI + (uint)*puVar8 * 2) = (short)uVar7;
          puVar8 = puVar8 + 1;
          uVar9 = uVar10 - 1;
          bVar3 = 0 < (int)uVar10;
          uVar10 = uVar9;
        } while (uVar9 != 0 && bVar3);
        puVar8 = puVar5 + 0x40;
        uVar10 = (uint)*(byte *)((int)puVar5 + 0x181);
        do {
          *(short *)(unaff_EDI + (uint)*puVar8 * 2) = (short)((uint)uVar7 >> 0x10);
          puVar8 = puVar8 + 1;
          uVar9 = uVar10 - 1;
          bVar3 = 0 < (int)uVar10;
          uVar10 = uVar9;
        } while (uVar9 != 0 && bVar3);
        return (byte *)puVar5;
      }
      uVar4 = (undefined2)*(undefined4 *)(UINT_00906c54 + (uint)bVar1 * 2);
      pbVar11 = (byte *)CONCAT22(uVar4,uVar4);
    }
  }
  else {
    pbVar11 = (byte *)CONCAT22((short)*(undefined4 *)(unaff_ESI + 1),
                               (short)*(undefined4 *)(unaff_ESI + 1));
  }
  pbVar12 = unaff_EDI + unaff_EBP * 4;
  *(byte **)pbVar12 = pbVar11;
  *(byte **)unaff_EDI = pbVar11;
  *(byte **)(pbVar12 + 4) = pbVar11;
  *(byte **)(unaff_EDI + 4) = pbVar11;
  *(byte **)(pbVar12 + 8) = pbVar11;
  *(byte **)(unaff_EDI + 8) = pbVar11;
  *(byte **)(pbVar12 + 0xc) = pbVar11;
  *(byte **)(unaff_EDI + 0xc) = pbVar11;
  pbVar12 = pbVar12 + unaff_EBP;
  pbVar13 = unaff_EDI + unaff_EBP;
  *(byte **)pbVar12 = pbVar11;
  *(byte **)pbVar13 = pbVar11;
  *(byte **)(pbVar12 + 4) = pbVar11;
  *(byte **)(pbVar13 + 4) = pbVar11;
  *(byte **)(pbVar12 + 8) = pbVar11;
  *(byte **)(pbVar13 + 8) = pbVar11;
  *(byte **)(pbVar12 + 0xc) = pbVar11;
  *(byte **)(pbVar13 + 0xc) = pbVar11;
  pbVar12 = pbVar12 + unaff_EBP;
  pbVar13 = pbVar13 + unaff_EBP;
  *(byte **)pbVar12 = pbVar11;
  *(byte **)pbVar13 = pbVar11;
  *(byte **)(pbVar12 + 4) = pbVar11;
  *(byte **)(pbVar13 + 4) = pbVar11;
  *(byte **)(pbVar12 + 8) = pbVar11;
  *(byte **)(pbVar13 + 8) = pbVar11;
  *(byte **)(pbVar12 + 0xc) = pbVar11;
  *(byte **)(pbVar13 + 0xc) = pbVar11;
  pbVar12 = pbVar12 + unaff_EBP;
  pbVar13 = pbVar13 + unaff_EBP;
  *(byte **)pbVar12 = pbVar11;
  *(byte **)pbVar13 = pbVar11;
  *(byte **)(pbVar12 + 4) = pbVar11;
  *(byte **)(pbVar13 + 4) = pbVar11;
  *(byte **)(pbVar12 + 8) = pbVar11;
  *(byte **)(pbVar13 + 8) = pbVar11;
  *(byte **)(pbVar12 + 0xc) = pbVar11;
  *(byte **)(pbVar13 + 0xc) = pbVar11;
  return pbVar11;
}
#endif


/* ---- 0x004cd9b0  block16_RenderBlock4 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Decodes one 4x4 block (register convention in the original: ESI stream, EDI destination, EBP
   pitch) Original name block16_RenderBlock4 (the remaster's GrimFandango (Linux): the 4x4 level of
   the blocky16 opcode decoder in both builds (0xf5 motion copy with a 16-bit offset, 0xff splits
   into four 2x2 blocks via block16_RenderBlock2, colour / fill opcodes)); was
   Blocky16_DecodeBlock4. */

byte * __cdecl block16_RenderBlock4(byte *src,byte *dst,int pitch)

{
  byte bVar1;
  short sVar2;
  bool bVar3;
  undefined2 uVar4;
  ushort *puVar5;
  int iVar6;
  undefined4 uVar7;
  ushort *puVar8;
  int unaff_EBP;
  uint uVar9;
  uint uVar10;
  byte *unaff_ESI;
  byte *pbVar11;
  byte *unaff_EDI;
  byte *pbVar12;
  byte *pbVar13;
  byte *unaff_retaddr;
  
  uVar10 = UINT_00906c68;
  bVar1 = *unaff_ESI;
  if (bVar1 < 0xf6) {
    if (bVar1 == 0xf5) {
      sVar2 = *(short *)(unaff_ESI + 1);
    }
    else {
      sVar2 = *(short *)(UINT_00906c4c + (uint)bVar1 * 2);
    }
    iVar6 = sVar2 * 2 + _DAT_00906c58;
    pbVar11 = unaff_EDI + unaff_EBP * 2;
    uVar7 = *(undefined4 *)(unaff_EDI + iVar6);
    *(undefined4 *)pbVar11 = *(undefined4 *)(pbVar11 + iVar6);
    *(undefined4 *)unaff_EDI = uVar7;
    uVar7 = *(undefined4 *)(unaff_EDI + iVar6 + 4);
    *(undefined4 *)(pbVar11 + 4) = *(undefined4 *)(pbVar11 + iVar6 + 4);
    *(undefined4 *)(unaff_EDI + 4) = uVar7;
    pbVar11 = pbVar11 + unaff_EBP;
    pbVar12 = unaff_EDI + unaff_EBP;
    uVar7 = *(undefined4 *)(pbVar12 + iVar6);
    *(undefined4 *)pbVar11 = *(undefined4 *)(pbVar11 + iVar6);
    *(undefined4 *)pbVar12 = uVar7;
    pbVar13 = *(byte **)(pbVar11 + iVar6 + 4);
    uVar7 = *(undefined4 *)(pbVar12 + iVar6 + 4);
    *(byte **)(pbVar11 + 4) = pbVar13;
    *(undefined4 *)(pbVar12 + 4) = uVar7;
    return pbVar13;
  }
  if (bVar1 == 0xff) {
    block16_RenderBlock2(unaff_EDI,unaff_retaddr,(int)src);
    block16_RenderBlock2(unaff_EDI,unaff_retaddr,(int)src);
    block16_RenderBlock2(unaff_EDI,unaff_retaddr,(int)src);
    pbVar11 = block16_RenderBlock2(unaff_EDI,unaff_retaddr,(int)src);
    return pbVar11;
  }
  if (bVar1 < 0xfe) {
    if (bVar1 == 0xfd) {
      uVar4 = (undefined2)*(undefined4 *)(UINT_00906c6c + (uint)unaff_ESI[1] * 2);
      pbVar11 = (byte *)CONCAT22(uVar4,uVar4);
    }
    else {
      if (bVar1 < 0xf9) {
        if (bVar1 == 0xf8) {
          uVar7 = *(undefined4 *)(unaff_ESI + 2);
          bVar1 = unaff_ESI[1];
        }
        else {
          if (bVar1 != 0xf7) {
            pbVar11 = unaff_EDI + unaff_EBP * 2;
            uVar7 = *(undefined4 *)(unaff_EDI + UINT_00906c68);
            *(undefined4 *)pbVar11 = *(undefined4 *)(pbVar11 + UINT_00906c68);
            *(undefined4 *)unaff_EDI = uVar7;
            uVar7 = *(undefined4 *)(unaff_EDI + uVar10 + 4);
            *(undefined4 *)(pbVar11 + 4) = *(undefined4 *)(pbVar11 + uVar10 + 4);
            *(undefined4 *)(unaff_EDI + 4) = uVar7;
            pbVar11 = pbVar11 + unaff_EBP;
            pbVar12 = unaff_EDI + unaff_EBP;
            uVar7 = *(undefined4 *)(pbVar12 + uVar10);
            *(undefined4 *)pbVar11 = *(undefined4 *)(pbVar11 + uVar10);
            *(undefined4 *)pbVar12 = uVar7;
            pbVar13 = *(byte **)(pbVar11 + uVar10 + 4);
            uVar7 = *(undefined4 *)(pbVar12 + uVar10 + 4);
            *(byte **)(pbVar11 + 4) = pbVar13;
            *(undefined4 *)(pbVar12 + 4) = uVar7;
            return pbVar13;
          }
          uVar7 = CONCAT22(*(undefined2 *)
                            (UINT_00906c6c +
                            (uint)(byte)((ushort)*(undefined2 *)(unaff_ESI + 2) >> 8) * 2),
                           *(undefined2 *)
                            (UINT_00906c6c + (uint)(byte)*(undefined2 *)(unaff_ESI + 2) * 2));
          bVar1 = unaff_ESI[1];
        }
        puVar5 = (ushort *)((uint)bVar1 * 0x80 + _DAT_00906c70);
        puVar8 = puVar5;
        uVar10 = (uint)(byte)puVar5[0x30];
        do {
          *(short *)(unaff_EDI + (uint)*puVar8 * 2) = (short)uVar7;
          puVar8 = puVar8 + 1;
          uVar9 = uVar10 - 1;
          bVar3 = 0 < (int)uVar10;
          uVar10 = uVar9;
        } while (uVar9 != 0 && bVar3);
        puVar8 = puVar5 + 0x10;
        uVar10 = (uint)*(byte *)((int)puVar5 + 0x61);
        do {
          *(short *)(unaff_EDI + (uint)*puVar8 * 2) = (short)((uint)uVar7 >> 0x10);
          puVar8 = puVar8 + 1;
          uVar9 = uVar10 - 1;
          bVar3 = 0 < (int)uVar10;
          uVar10 = uVar9;
        } while (uVar9 != 0 && bVar3);
        return (byte *)puVar5;
      }
      uVar4 = (undefined2)*(undefined4 *)(UINT_00906c54 + (uint)bVar1 * 2);
      pbVar11 = (byte *)CONCAT22(uVar4,uVar4);
    }
  }
  else {
    pbVar11 = (byte *)CONCAT22((short)*(undefined4 *)(unaff_ESI + 1),
                               (short)*(undefined4 *)(unaff_ESI + 1));
  }
  *(byte **)unaff_EDI = pbVar11;
  *(byte **)(unaff_EDI + 4) = pbVar11;
  pbVar13 = unaff_EDI + unaff_EBP;
  *(byte **)pbVar13 = pbVar11;
  *(byte **)(unaff_EDI + unaff_EBP + 4) = pbVar11;
  *(byte **)(pbVar13 + unaff_EBP) = pbVar11;
  *(byte **)(unaff_EDI + unaff_EBP * 2 + 4) = pbVar11;
  *(byte **)(pbVar13 + unaff_EBP * 2) = pbVar11;
  *(byte **)(unaff_EDI + unaff_EBP * 3 + 4) = pbVar11;
  return pbVar11;
}
#endif


/* ---- 0x004cdb80  block16_RenderBlock2 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Decodes one 2x2 block (register convention in the original: ESI stream, EDI destination, EBP
   pitch) Original name block16_RenderBlock2 (the remaster's GrimFandango (Linux): the 2x2 level the
   4x4 decoder calls for opcode 0xff in both builds); was Blocky16_DecodeBlock2. */

byte * __cdecl block16_RenderBlock2(byte *src,byte *dst,int pitch)

{
  byte bVar1;
  short sVar2;
  uint uVar3;
  uint uVar4;
  undefined2 uVar5;
  undefined4 in_EAX;
  byte *pbVar6;
  int iVar7;
  undefined4 uVar8;
  int unaff_EBP;
  byte *unaff_ESI;
  undefined4 *unaff_EDI;
  
  uVar4 = UINT_00906c6c;
  uVar3 = UINT_00906c68;
  bVar1 = *unaff_ESI;
  pbVar6 = (byte *)CONCAT31((int3)((uint)in_EAX >> 8),bVar1);
  if (bVar1 < 0xf6) {
    if (bVar1 == 0xf5) {
      sVar2 = *(short *)(unaff_ESI + 1);
    }
    else {
      sVar2 = *(short *)(UINT_00906c4c + (uint)bVar1 * 2);
    }
    iVar7 = sVar2 * 2 + _DAT_00906c58;
    *unaff_EDI = *(undefined4 *)((int)unaff_EDI + iVar7);
    pbVar6 = *(byte **)((int)unaff_EDI + unaff_EBP + iVar7);
    *(byte **)((int)unaff_EDI + unaff_EBP) = pbVar6;
    return pbVar6;
  }
  if ((bVar1 == 0xff) || (bVar1 == 0xf8)) {
    pbVar6 = *(byte **)(unaff_ESI + 1);
    *unaff_EDI = pbVar6;
    *(undefined4 *)((int)unaff_EDI + unaff_EBP) = *(undefined4 *)(unaff_ESI + 5);
    return pbVar6;
  }
  if (0xfd < bVar1) {
    pbVar6 = *(byte **)(unaff_ESI + 1);
    uVar5 = SUB42(pbVar6,0);
    uVar8 = CONCAT22(uVar5,uVar5);
    *unaff_EDI = uVar8;
    *(undefined4 *)((int)unaff_EDI + unaff_EBP) = uVar8;
    return pbVar6;
  }
  if (bVar1 != 0xfd) {
    if (0xf8 < bVar1) {
      pbVar6 = *(byte **)(UINT_00906c54 + (uint)bVar1 * 2);
      uVar5 = SUB42(pbVar6,0);
      uVar8 = CONCAT22(uVar5,uVar5);
      *unaff_EDI = uVar8;
      *(undefined4 *)((int)unaff_EDI + unaff_EBP) = uVar8;
      return pbVar6;
    }
    if (bVar1 == 0xf7) {
      uVar3 = *(uint *)(unaff_ESI + 1);
      *(short *)unaff_EDI = (short)*(undefined4 *)(UINT_00906c6c + (uVar3 & 0xff) * 2);
      *(short *)((int)unaff_EDI + 2) = (short)*(undefined4 *)(uVar4 + (uVar3 >> 8 & 0xff) * 2);
      *(short *)((int)unaff_EDI + unaff_EBP) =
           (short)*(undefined4 *)(uVar4 + (uVar3 >> 0x10 & 0xff) * 2);
      *(short *)((int)unaff_EDI + unaff_EBP + 2) =
           (short)*(undefined4 *)(uVar4 + (int)(uVar3 >> 0x18) * 2);
      return (byte *)(uVar3 >> 0x18);
    }
    if (0xf5 < bVar1) {
      *unaff_EDI = *(undefined4 *)((int)unaff_EDI + UINT_00906c68);
      pbVar6 = *(byte **)((int)unaff_EDI + unaff_EBP + uVar3);
      *(byte **)((int)unaff_EDI + unaff_EBP) = pbVar6;
    }
    return pbVar6;
  }
  pbVar6 = *(byte **)(UINT_00906c6c + (uint)unaff_ESI[1] * 2);
  uVar5 = SUB42(pbVar6,0);
  uVar8 = CONCAT22(uVar5,uVar5);
  *unaff_EDI = uVar8;
  *(undefined4 *)((int)unaff_EDI + unaff_EBP) = uVar8;
  return pbVar6;
}
#endif

