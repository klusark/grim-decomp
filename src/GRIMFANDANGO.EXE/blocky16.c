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

uint __cdecl fob_flobdec_blocky16_module(int *services,uint config)

{
  g_pBlocky16_share_services = services;
  g_dwBlocky16_share_config = config;
  (*(code *)*services)
            (s_LECMODULE_insane_blocky16_flobde_004f3a04,&PTR_fob_flobdec_blocky16_module_004f34b8);
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

void __cdecl Blocky16_module_terminate(void)

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

uint __cdecl Blocky16_module_startup(void)

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

void __cdecl Blocky16_module_shutdown(void)

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

char * __cdecl Blocky16_flobdec_Info(int what)

{
  if (what == 0) {
    return s_Blocky16_Tile_004f3ab0;
  }
  if (what != 1) {
    if (what != 2) {
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

uint __cdecl Blocky16_flobdec_GetID(void)

{
  return 0x426c3136;
}

/* ---- 0x004cc3c0  Blocky16_flobdec_DecodeHeader ---- */
/* Reallocates the three frame buffers when the frame size or depth of the header differs from the
   current ones Original name Blocky16_flobdec_DecodeHeader (the remaster's GrimFandango (Linux):
   slot 4 of the "FLOBDEC=insane_blocky16" service table; flobdec_DecodeHeader is a static several
   LEC modules have, written with the module prefix); was Blocky16_Prepare. */

uint __cdecl Blocky16_flobdec_DecodeHeader(int hdr)

{
  short sVar1;
  uint height;
  
  sVar1 = *(short *)(hdr + 2);
  height = (int)*(short *)(hdr + 4) + 7U & 0xfffffff8;
  if ((((*(short *)(hdr + 6) != g_nGlobal_bm_type) || (g_pBlkBitmap0 == (LecPixelFormat *)0x0)) ||
      ((int)sVar1 != *(int *)&g_pBlkBitmap0->field_0x4)) ||
     (height != *(uint *)&g_pBlkBitmap0->field_0x8)) {
    Blocky16_flobdec_Reset();
    AllocBuffers((int)sVar1,height,(int)*(short *)(hdr + 6));
  }
  return 0;
}

/* ---- 0x004cc410  AllocBuffers ---- */
/* Allocates the three frame buffers (current, previous, before) for a frame size and clears them;
   sets up the display expand table memory Original name AllocBuffers (the remaster's GrimFandango
   (Linux): same body (three bitmaps, maketiles(4)/(8), shift = 0); blocky16 flobdec_DecodeHeader's
   callee); was Blocky16_AllocBuffers. */

int __cdecl AllocBuffers(int width,int height,int depth)

{
  int iVar1;
  
  g_nFob_buffersize = height * width;
  fob_block_maketiles(4);
  fob_block_maketiles(8);
  g_nFob_translation_shiftr = 0;
  g_nFob_translation_shiftg = 0;
  g_nFob_translation_shiftb = 0;
  iVar1 = (*(code *)*g_pBlocky16_bitmap_services)(&g_pBlkBitmap0,width,height,depth);
  if (iVar1 == 0) {
    iVar1 = (*(code *)*g_pBlocky16_bitmap_services)(&g_pBlkBitmap1,width,height,depth);
    if (iVar1 == 0) {
      iVar1 = (*(code *)*g_pBlocky16_bitmap_services)(&g_pBlkBitmap2,width,height,depth);
      if (iVar1 == 0) {
        g_nGlobal_bm_type = depth;
        g_pFob_blk16_key_buffer = *(byte **)g_pBlkBitmap0;
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

void __cdecl Blocky16_flobdec_Reset(void)

{
  if (g_pBlkBitmap0 != (LecPixelFormat *)0x0) {
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

void __cdecl
Blocky16_flobdec_DecodeBody
          (void *dst,uint *clip,int x,int y,int palette,byte *hdr,uint size,byte flags)

{
  Blocky16_DecodeFrame(dst,clip,x,y,palette,hdr,flags);
  return;
}

/* ---- 0x004cc650  Blocky16_flobdec_GetVal ---- */
/* Reads four 16 bit fields of a frame header of the right size (0x100), returns -1 for any other
   size Original name Blocky16_flobdec_GetVal (the remaster's GrimFandango (Linux): slot 7 of the
   "FLOBDEC=insane_blocky16" service table; flobdec_GetVal is a static several LEC modules have,
   written with the module prefix); was Blocky16_GetFrameInfo. */

uint __cdecl
Blocky16_flobdec_GetVal(short *hdr,int what,int *outWidth,int *outHeight,int *outX,int *outY)

{
  if (what != 0x100) {
    return 0xffffffff;
  }
  if (outWidth != (int *)0x0) {
    *outWidth = (int)*hdr;
  }
  if (outHeight != (int *)0x0) {
    *outHeight = (int)hdr[2];
  }
  if (outX != (int *)0x0) {
    *outX = (int)hdr[4];
  }
  if (outY != (int *)0x0) {
    *outY = (int)hdr[6];
  }
  return 0;
}

/* ---- 0x004cc6a0  fob_blk16_configure ---- */
/* Makes the pixel offsets of the split masks and the motion vectors for a frame width, once per
   width Original name fob_blk16_configure (the remaster's GrimFandango (Linux): same body (skips
   when the width equals the static old_mod, rebuilds the motion offsets and the 4x4 / 8x8 tile
   tables for the width); the same call in the decoder when header +0x10 is 0, before the two
   gra_SetBuffer calls); was Blocky16_BuildPixelOffsets. */

void __cdecl fob_blk16_configure(uint width)

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
  
  if (width != g_dwFob_blk16_configure_old_mod) {
    g_dwFob_blk16_configure_old_mod = width;
    pBVar2 = g_aBlockyMotionVectors;
    psVar4 = &g_asBlockyMotion;
    do {
      pBVar3 = pBVar2 + 1;
      sVar8 = (short)width;
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
  unsigned char _frame[0x110] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
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
  uint local_168;
  uint local_164;
  uint local_160;
  uint local_15c;
  uint local_158;
  uint local_154;
  uint local_150;
  uint local_14c;
  uint local_148;
  uint local_144;
  uint local_140;
  uint local_13c;
  uint local_138;
  uint local_134;
  uint local_130;
  uint local_12c;
  uint local_128;
  uint local_124;
  uint local_120;
  uint local_11c;
  uint local_118;
  uint local_114;
  uint local_110;
  uint local_10c;
  uint local_108;
  uint local_104;
  #define auStack_100 (*(undefined4 (*)[15])(_frame + (0x110 - 0x100)))
  #define local_c4 (*(uint *)(_frame + (0x110 - 0xc4)))
  uint local_4;
  
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
#undef local_c4

#endif


/* ---- 0x004ccd00  Blocky16_DecodeFrame ---- */
/* Decodes one Blocky16 frame into the buffers g_pFob_blk16_render_buffer, g_pFob_blk16_delta_buffer
   and g_pFob_blk16_key_buffer using g_stBlockyDecState, g_asBlockyMotion, g_aBlockySplit4 and
   g_aBlockySplit8 and gives it to the output g_pFob_blit_routine; bitmaps g_pBlkBitmap0,
   g_pBlkBitmap1, g_pBlkBitmap2; tables g_pbBlkExpand, g_nFob_translation_shiftr,
   g_nFob_translation_shiftg, g_nFob_translation_shiftb, g_pbBlkOutput, g_nBlkLastSeq */

int __cdecl Blocky16_DecodeFrame(void *dst,uint *clip,int x,int y,int palette,byte *hdr,byte flags)

{
  ushort uVar1;
  byte *pbVar2;
  byte *pbVar3;
  int iVar4;
  int iVar5;
  ushort *src;
  byte *pbVar6;
  int extraout_ECX;
  int iVar7;
  uint uVar8;
  LecPixelFormat *srcFmt;
  uint local_8;
  uint local_4;
  
  uVar8 = (uint)*(short *)(hdr + 8);
  iVar7 = (int)*(short *)(hdr + 0xc);
  src = (ushort *)(hdr + 0x230);
  if (((g_pBlkBitmap0 == (LecPixelFormat *)0x0) || (uVar8 != *(uint *)&g_pBlkBitmap0->field_0x4)) ||
     ((iVar7 + 7U & 0xfffffff8) != *(uint *)&g_pBlkBitmap0->field_0x8)) {
    Blocky16_flobdec_Reset();
    iVar4 = (int)*(short *)(hdr + 0x228);
    if (*(short *)(hdr + 0x228) == 0) {
      iVar4 = 8;
    }
    AllocBuffers(uVar8,iVar7 + 7U & 0xfffffff8,iVar4);
  }
  iVar4 = (int)g_pFob_blk16_delta_buffer - (int)g_pFob_blk16_render_buffer;
  iVar5 = (int)g_pFob_blk16_key_buffer - (int)g_pFob_blk16_render_buffer;
  if (dst != (void *)0x0) {
    Blocky16_BuildExpandTable(dst);
  }
  if (*(short *)(hdr + 0x10) == 0) {
    fob_blk16_configure(uVar8);
    gra_SetBuffer((char *)g_pFob_blk16_key_buffer,(int)g_pBlkBitmap0,
                  *(int *)&g_pBlkBitmap0->field_0x4 * *(int *)&g_pBlkBitmap0->field_0x8,
                  (char *)(hdr + 0x20));
    gra_SetBuffer((char *)g_pFob_blk16_delta_buffer,(int)g_pBlkBitmap0,
                  *(int *)&g_pBlkBitmap0->field_0x4 * *(int *)&g_pBlkBitmap0->field_0x8,
                  (char *)(hdr + 0x20));
    g_nBlkLastSeq = -1;
  }
  g_nBretsFrameCount = g_nBretsFrameCount + 1;
  switch(hdr[0x12]) {
  case 0:
    goto LAB_004ccf61;
  case 1:
    Blocky16_DecodeHalfRows16(g_pFob_blk16_render_buffer,src,uVar8,iVar7);
    g_pbBlkOutput = g_pFob_blk16_render_buffer;
    break;
  case 2:
    if (((flags & 4) != 0) && (hdr[0x13] == 0)) {
      g_nBlkLastSeq = (int)*(short *)(hdr + 0x10);
      return 0;
    }
    if ((int)*(short *)(hdr + 0x10) == g_nBlkLastSeq + 1) {
      Blocky16_DecodeBlocks
                (g_pFob_blk16_render_buffer,(byte *)src,iVar4 >> 1,iVar5 >> 1,uVar8,
                 &g_asBlockyMotion,(short *)(hdr + 0x18),iVar7,uVar8 * 9 - (uVar8 & 0xfffffff8),
                 (byte *)&g_aBlockySplit4,(byte *)&g_aBlockySplit8,(ushort *)(hdr + 0x28));
      g_pbBlkOutput = g_pFob_blk16_render_buffer;
    }
    break;
  case 3:
    src = (ushort *)g_pFob_blk16_delta_buffer;
    if (((flags & 4) != 0) && (hdr[0x13] == 0)) {
      g_nBlkLastSeq = (int)*(short *)(hdr + 0x10);
      return 0;
    }
    goto LAB_004ccf61;
  case 4:
    src = (ushort *)g_pFob_blk16_key_buffer;
    if (((flags & 4) != 0) && (hdr[0x13] == 0)) {
      g_nBlkLastSeq = (int)*(short *)(hdr + 0x10);
      return 0;
    }
LAB_004ccf61:
    msc_MemCopy(g_pFob_blk16_render_buffer,src,uVar8 * iVar7 * 2);
LAB_004ccf67:
    g_pbBlkOutput = g_pFob_blk16_render_buffer;
    break;
  case 5:
    msc_rle_DecompressBlock(g_pFob_blk16_render_buffer,(uint)src,*(int *)(hdr + 0x24));
    goto LAB_004ccf67;
  case 6:
    iVar7 = uVar8 * iVar7;
    pbVar6 = g_pFob_blk16_render_buffer;
    g_pbBlkOutput = g_pFob_blk16_render_buffer;
    if (iVar7 != 0) {
      do {
        uVar1 = *src;
        src = (ushort *)((int)src + 1);
        iVar7 = iVar7 + -1;
        *(undefined2 *)pbVar6 = *(undefined2 *)(hdr + (uint)(byte)uVar1 * 2 + 0x28);
        pbVar6 = pbVar6 + 2;
      } while (iVar7 != 0);
      g_pbBlkOutput = g_pFob_blk16_render_buffer;
    }
    break;
  case 7:
    Blocky16_DecodeHalfRows8(g_pFob_blk16_render_buffer,(byte *)src,uVar8,iVar7,(int)(hdr + 0x28));
    g_pbBlkOutput = g_pFob_blk16_render_buffer;
    break;
  case 8:
    msc_rle_DecompressInitialize((int *)src);
    iVar7 = uVar8 * iVar7;
    iVar4 = iVar7;
    pbVar6 = g_pFob_blk16_render_buffer;
    for (; iVar7 != 0; iVar7 = iVar7 + -1) {
      uVar8 = msc_rle_DecompressGetbyte(iVar4);
      *(undefined2 *)pbVar6 = *(undefined2 *)(hdr + (uVar8 & 0xff) * 2 + 0x28);
      iVar4 = extraout_ECX;
      pbVar6 = pbVar6 + 2;
    }
    Mem_DumpLog();
    g_pbBlkOutput = g_pFob_blk16_render_buffer;
  }
  if ((g_pbBlkOutput != (byte *)0x0) && (dst != (void *)0x0)) {
    pbVar6 = g_pbBlkExpand;
    if ((g_nFob_translation_shiftr == 0) && (g_nFob_translation_shiftg == 0)) {
      pbVar6 = (byte *)0x0;
    }
    if (g_pFob_blit_routine == (void *)0x0) {
      srcFmt = g_pBlkBitmap0;
      if (((g_pbBlkOutput == *(byte **)g_pBlkBitmap0) ||
          (srcFmt = (LecPixelFormat *)g_pBlkBitmap1, g_pbBlkOutput == (byte *)*g_pBlkBitmap1)) ||
         (srcFmt = (LecPixelFormat *)g_pBlkBitmap2, g_pbBlkOutput == (byte *)*g_pBlkBitmap2)) {
        gra_BlitRectLookup(dst,clip,x,y,(int *)srcFmt,(byte *)palette,pbVar6);
      }
      palette = 1;
    }
    else if (g_pbBlkOutput == *(byte **)g_pBlkBitmap0) {
      palette = (*(code *)g_pFob_blit_routine)(dst,clip,x,y,g_pBlkBitmap0,palette,pbVar6);
    }
    else if (g_pbBlkOutput == (byte *)*g_pBlkBitmap1) {
      palette = (*(code *)g_pFob_blit_routine)(dst,clip,x,y,g_pBlkBitmap1,palette,pbVar6);
    }
    else if (g_pbBlkOutput == (byte *)*g_pBlkBitmap2) {
      palette = (*(code *)g_pFob_blit_routine)(dst,clip,x,y,g_pBlkBitmap2,palette,pbVar6);
    }
  }
  pbVar3 = g_pFob_blk16_delta_buffer;
  pbVar2 = g_pFob_blk16_key_buffer;
  pbVar6 = g_pFob_blk16_render_buffer;
  if ((int)*(short *)(hdr + 0x10) == g_nBlkLastSeq + 1) {
    if (hdr[0x13] == 1) {
      g_pFob_blk16_delta_buffer = g_pFob_blk16_render_buffer;
      g_pFob_blk16_render_buffer = pbVar3;
      g_nBlkLastSeq = (int)*(short *)(hdr + 0x10);
      return palette;
    }
    if (hdr[0x13] == 2) {
      g_pFob_blk16_key_buffer = g_pFob_blk16_delta_buffer;
      g_pFob_blk16_render_buffer = pbVar2;
      g_pFob_blk16_delta_buffer = pbVar6;
    }
  }
  g_nBlkLastSeq = (int)*(short *)(hdr + 0x10);
  return palette;
}

/* ---- 0x004cd1e0  Blocky16_BuildExpandTable ---- */
/* Makes the 64K entry table that converts 16 bit pixels to the display format when the display
   channel shifts change */

void __cdecl Blocky16_BuildExpandTable(LecPixelFormat *fmt)

{
  uint local_8;
  
  if (((((g_pbBlkExpand != (byte *)0x0) && (fmt->nBytesPerPixel == 2)) &&
       ((fmt->nColorMode == 1 || (fmt->nColorMode == 2)))) &&
      (((fmt->nRedShift != g_pBlkBitmap0->nRedShift ||
        (fmt->nBlueShift != g_pBlkBitmap0->nBlueShift)) ||
       (fmt->nGreenShift != g_pBlkBitmap0->nGreenShift)))) &&
     (((fmt->nRedShift != g_nFob_translation_shiftr ||
       (fmt->nBlueShift != g_nFob_translation_shiftb)) ||
      (fmt->nGreenShift != g_nFob_translation_shiftg)))) {
    g_nFob_translation_shiftr = fmt->nRedShift;
    g_nFob_translation_shiftg = fmt->nGreenShift;
    g_nFob_translation_shiftb = fmt->nBlueShift;
    for (local_8 = 0; (int)local_8 < 0x10000; local_8 = local_8 + 1) {
      *(undefined2 *)(g_pbBlkExpand + local_8 * 2) = (undefined2)local_8;
    }
    gra_ConvertCopy(g_pbBlkExpand,g_pBlkBitmap0,0x10000,(byte *)0x0,g_pbBlkExpand,fmt,(byte *)0x0);
  }
  return;
}

/* ---- 0x004cd300  Blocky16_DecodeHalfRows16 ---- */
/* Decodes a method 1 frame: 16 bit pixels of every second row, the rows between are averaged */

void __cdecl Blocky16_DecodeHalfRows16(void *dst,ushort *src,int width,int height)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  undefined2 *puVar10;
  uint *puVar11;
  undefined4 *puVar12;
  uint local_10;
  uint local_c;
  uint local_8;
  uint local_4;
  
  uVar7 = width * 2;
  if (0 < height) {
    local_10 = height + 1U >> 1;
    puVar12 = (undefined4 *)((int)dst + uVar7);
    do {
      puVar11 = puVar12 + 1;
      uVar1 = *src;
      src = src + 1;
      *puVar12 = CONCAT22(uVar1,uVar1);
      if (0 < width + -2) {
        uVar8 = width - 1U >> 1;
        uVar5 = (uint)uVar1;
        do {
          uVar9 = (uint)*src;
          src = src + 1;
          uVar5 = FUN_004cd3f0(uVar5,uVar9);
          *puVar11 = uVar5 & 0xffff | uVar9 << 0x10;
          puVar11 = puVar11 + 1;
          uVar8 = uVar8 - 1;
          uVar5 = uVar9;
        } while (uVar8 != 0);
      }
      puVar12 = (undefined4 *)((int)puVar11 + uVar7);
      local_10 = local_10 - 1;
    } while (local_10 != 0);
  }
  msc_MemCopy(dst,(undefined4 *)((int)dst + uVar7),uVar7);
  puVar10 = (undefined2 *)((int)dst + width * 4);
  if (height != 2 && -1 < height + -2) {
    uVar7 = height - 1U >> 1;
    iVar2 = width;
    uVar3 = extraout_ECX;
    uVar4 = extraout_EDX;
    do {
      for (; iVar2 != 0; iVar2 = iVar2 + -1) {
        iVar6 = FUN_004cd3f0(CONCAT22((short)((uint)uVar4 >> 0x10),puVar10[width]),
                             CONCAT22((short)((uint)uVar3 >> 0x10),puVar10[-width]));
        *puVar10 = (short)iVar6;
        puVar10 = puVar10 + 1;
        uVar3 = extraout_ECX_00;
        uVar4 = extraout_EDX_00;
      }
      puVar10 = puVar10 + width;
      uVar7 = uVar7 - 1;
      iVar2 = width;
    } while (uVar7 != 0);
  }
  return;
}

/* ---- 0x004cd450  Blocky16_DecodeHalfRows8 ---- */
/* Decodes a method 7 frame: 8 bit indexes of every second row through a colour table, the rows
   between are averaged */

void __cdecl Blocky16_DecodeHalfRows8(void *dst,byte *src,int width,int height,int palette)

{
  byte bVar1;
  ushort uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  uint uVar6;
  int iVar7;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  undefined2 *puVar11;
  uint *puVar12;
  undefined4 *puVar13;
  uint local_10;
  uint local_c;
  uint local_8;
  uint local_4;
  
  uVar8 = width * 2;
  if (0 < height) {
    local_10 = height + 1U >> 1;
    puVar13 = (undefined4 *)((int)dst + uVar8);
    do {
      bVar1 = *src;
      src = src + 1;
      puVar12 = puVar13 + 1;
      uVar2 = *(ushort *)(palette + (uint)bVar1 * 2);
      *puVar13 = CONCAT22(uVar2,uVar2);
      if (0 < width + -2) {
        uVar9 = width - 1U >> 1;
        uVar6 = (uint)uVar2;
        do {
          bVar1 = *src;
          src = src + 1;
          uVar10 = (uint)*(ushort *)(palette + (uint)bVar1 * 2);
          uVar6 = FUN_004cd3f0(uVar6,uVar10);
          *puVar12 = uVar6 & 0xffff | uVar10 << 0x10;
          puVar12 = puVar12 + 1;
          uVar9 = uVar9 - 1;
          uVar6 = uVar10;
        } while (uVar9 != 0);
      }
      puVar13 = (undefined4 *)((int)puVar12 + uVar8);
      local_10 = local_10 - 1;
    } while (local_10 != 0);
  }
  msc_MemCopy(dst,(undefined4 *)((int)dst + uVar8),uVar8);
  puVar11 = (undefined2 *)((int)dst + width * 4);
  if (height != 2 && -1 < height + -2) {
    uVar8 = height - 1U >> 1;
    iVar3 = width;
    uVar4 = extraout_ECX;
    uVar5 = extraout_EDX;
    do {
      for (; iVar3 != 0; iVar3 = iVar3 + -1) {
        iVar7 = FUN_004cd3f0(CONCAT22((short)((uint)uVar5 >> 0x10),puVar11[width]),
                             CONCAT22((short)((uint)uVar4 >> 0x10),puVar11[-width]));
        *puVar11 = (short)iVar7;
        puVar11 = puVar11 + 1;
        uVar4 = extraout_ECX_00;
        uVar5 = extraout_EDX_00;
      }
      puVar11 = puVar11 + width;
      uVar8 = uVar8 - 1;
      iVar3 = width;
    } while (uVar8 != 0);
  }
  return;
}

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
  INT_00906c60 = width;
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



/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern char f_Blocky16_flobdec_DecodeBody[] __asm__("_Blocky16_flobdec_DecodeBody");
extern char f_Blocky16_flobdec_DecodeHeader[] __asm__("_Blocky16_flobdec_DecodeHeader");
extern char f_Blocky16_flobdec_GetID[] __asm__("_Blocky16_flobdec_GetID");
extern char f_Blocky16_flobdec_GetVal[] __asm__("_Blocky16_flobdec_GetVal");
extern char f_Blocky16_flobdec_Info[] __asm__("_Blocky16_flobdec_Info");
extern char f_Blocky16_flobdec_Reset[] __asm__("_Blocky16_flobdec_Reset");
extern char f_Blocky16_module_shutdown[] __asm__("_Blocky16_module_shutdown");
extern char f_Blocky16_module_startup[] __asm__("_Blocky16_module_startup");
extern char f_Blocky16_module_terminate[] __asm__("_Blocky16_module_terminate");
extern char f_FUN_004cbf40[] __asm__("_FUN_004cbf40");
extern char f_LecShare_Nop[] __asm__("_LecShare_Nop");
extern char f_fob_flobdec_blocky16_module[] __asm__("_fob_flobdec_blocky16_module");
extern unsigned char grim_def_DAT_00906c50[4] __asm__("_DAT_00906c50");
extern unsigned char grim_def_DAT_00906c58[4] __asm__("_DAT_00906c58");
extern unsigned char grim_def_DAT_00906c5c __asm__("_DAT_00906c5c");
extern unsigned char grim_def_DAT_00906c5d[3] __asm__("_DAT_00906c5d");
extern unsigned char grim_def_DAT_00906c64[4] __asm__("_DAT_00906c64");
extern unsigned char grim_def_DAT_00906c70[4] __asm__("_DAT_00906c70");
extern unsigned char grim_def_DAT_00906d80[64] __asm__("_DAT_00906d80");
extern unsigned char grim_def_DAT_00906dc0[64] __asm__("_DAT_00906dc0");
extern unsigned char grim_def_DAT_00906e00 __asm__("_DAT_00906e00");
extern unsigned char grim_def_DAT_00906e01[98943] __asm__("_DAT_00906e01");
extern unsigned char grim_def_DAT_0091f0e0[16] __asm__("_DAT_0091f0e0");
extern unsigned char grim_def_DAT_0091f0f0[16] __asm__("_DAT_0091f0f0");
extern unsigned char grim_def_DAT_0091f100 __asm__("_DAT_0091f100");
extern unsigned char grim_def_DAT_0091f101[255] __asm__("_DAT_0091f101");
extern unsigned char grim_def_DAT_0091f200[1] __asm__("_DAT_0091f200");
extern unsigned char grim_def_DAT_0091f201[32415] __asm__("_DAT_0091f201");
extern unsigned char grim_def_DAT_00927100[1] __asm__("_DAT_00927100");
extern unsigned char grim_def_DAT_00927101[415] __asm__("_DAT_00927101");
extern int grim_def_INT_00906c60 __asm__("_INT_00906c60");
extern void *grim_def_PTR_fob_flobdec_blocky16_module_004f34b8[4] __asm__("_PTR_fob_flobdec_blocky16_module_004f34b8");
extern unsigned int grim_def_UINT_00906c4c __asm__("_UINT_00906c4c");
extern unsigned int grim_def_UINT_00906c54 __asm__("_UINT_00906c54");
extern unsigned int grim_def_UINT_00906c68 __asm__("_UINT_00906c68");
extern unsigned int grim_def_UINT_00906c6c __asm__("_UINT_00906c6c");
extern BlockyMotionVector grim_def_g_aBlockyMotionVectors[255] __asm__("_g_aBlockyMotionVectors");
extern unsigned char grim_def_g_aBlockySplit4[64] __asm__("_g_aBlockySplit4");
extern unsigned char grim_def_g_aBlockySplit8[256] __asm__("_g_aBlockySplit8");
extern int grim_def_g_anBlockySplit4X[16] __asm__("_g_anBlockySplit4X");
extern int grim_def_g_anBlockySplit4Y[16] __asm__("_g_anBlockySplit4Y");
extern int grim_def_g_anBlockySplit8X[16] __asm__("_g_anBlockySplit8X");
extern int grim_def_g_anBlockySplit8Y[16] __asm__("_g_anBlockySplit8Y");
extern short grim_def_g_asBlockyMotion __asm__("_g_asBlockyMotion");
extern unsigned int grim_def_g_dwBlocky16_share_config __asm__("_g_dwBlocky16_share_config");
extern unsigned int grim_def_g_dwFob_blk16_configure_old_mod __asm__("_g_dwFob_blk16_configure_old_mod");
extern int grim_def_g_nBlkLastSeq __asm__("_g_nBlkLastSeq");
extern int grim_def_g_nFob_buffersize __asm__("_g_nFob_buffersize");
extern int grim_def_g_nFob_translation_shiftb __asm__("_g_nFob_translation_shiftb");
extern int grim_def_g_nFob_translation_shiftg __asm__("_g_nFob_translation_shiftg");
extern int grim_def_g_nFob_translation_shiftr __asm__("_g_nFob_translation_shiftr");
extern int grim_def_g_nGlobal_bm_type __asm__("_g_nGlobal_bm_type");
extern unsigned char grim_def_g_pBlkBitmap0[4] __asm__("_g_pBlkBitmap0");
extern unsigned char grim_def_g_pBlkBitmap1[4] __asm__("_g_pBlkBitmap1");
extern unsigned char grim_def_g_pBlkBitmap2[4] __asm__("_g_pBlkBitmap2");
extern void *grim_def_g_pBlock16_flobdec_services[8] __asm__("_g_pBlock16_flobdec_services");
extern unsigned char grim_def_g_pBlocky16_bitmap_services[4] __asm__("_g_pBlocky16_bitmap_services");
extern unsigned char grim_def_g_pBlocky16_memory_services[4] __asm__("_g_pBlocky16_memory_services");
extern unsigned char grim_def_g_pBlocky16_share_services[4] __asm__("_g_pBlocky16_share_services");
extern unsigned char grim_def_g_pFob_blit_routine[4] __asm__("_g_pFob_blit_routine");
extern unsigned char grim_def_g_pFob_blk16_delta_buffer[32] __asm__("_g_pFob_blk16_delta_buffer");
extern unsigned char grim_def_g_pFob_blk16_key_buffer[12] __asm__("_g_pFob_blk16_key_buffer");
extern unsigned char grim_def_g_pFob_blk16_render_buffer[4] __asm__("_g_pFob_blk16_render_buffer");
extern unsigned char grim_def_g_pbBlkExpand[4] __asm__("_g_pbBlkExpand");
extern unsigned char grim_def_g_pbBlkOutput[8] __asm__("_g_pbBlkOutput");
extern unsigned int grim_def_g_stBlockyDecState __asm__("_g_stBlockyDecState");
extern char grim_def_s_BITMAP_clear_004f3aa0[16] __asm__("_s_BITMAP_clear_004f3aa0");
extern char grim_def_s_Blocky16_Tile_004f3ab0[16] __asm__("_s_Blocky16_Tile_004f3ab0");
extern char grim_def_s_C__grimsrc_libs_lecsmush_insane__004f3bbc[60] __asm__("_s_C__grimsrc_libs_lecsmush_insane__004f3bbc");
extern char grim_def_s_Decompresses_a_block16_tile_vide_004f3ac0[44] __asm__("_s_Decompresses_a_block16_tile_vide_004f3ac0");
extern char grim_def_s_FLOBDEC_insane_blocky16_004f39ec[24] __asm__("_s_FLOBDEC_insane_blocky16_004f39ec");
extern char grim_def_s_FlobDec_Blocky16_Module__Cannot_a_004f3a28[60] __asm__("_s_FlobDec_Blocky16_Module__Cannot_a_004f3a28");
extern char grim_def_s_FlobDec_Blocky16_Module__Cannot_a_004f3a64[60] __asm__("_s_FlobDec_Blocky16_Module__Cannot_a_004f3a64");
extern char grim_def_s_LECMODULE_insane_blocky16_flobde_004f3a04[36] __asm__("_s_LECMODULE_insane_blocky16_flobde_004f3a04");
extern char grim_def_s_This_module_decompresses_the_blo_004f3aec[208] __asm__("_s_This_module_decompresses_the_blo_004f3aec");
/* 0x004f34b8, 16 bytes */ GRIM_DATA("004f34b8") void *grim_def_PTR_fob_flobdec_blocky16_module_004f34b8[4] __asm__("_PTR_fob_flobdec_blocky16_module_004f34b8") = {
    (void *)f_fob_flobdec_blocky16_module, (void *)f_Blocky16_module_terminate, (void *)f_Blocky16_module_startup, (void *)f_Blocky16_module_shutdown
};
/* 0x004f34c8, 32 bytes */ GRIM_DATA("004f34c8") void *grim_def_g_pBlock16_flobdec_services[8] __asm__("_g_pBlock16_flobdec_services") = {
    (void *)f_Blocky16_flobdec_Info, (void *)f_Blocky16_flobdec_GetID, (void *)f_LecShare_Nop, (void *)f_Blocky16_flobdec_Reset,
    (void *)f_Blocky16_flobdec_DecodeHeader, (void *)f_Blocky16_flobdec_DecodeBody, (void *)f_FUN_004cbf40, (void *)f_Blocky16_flobdec_GetVal
};
/* 0x004f34e8, 1020 bytes */ GRIM_DATA("004f34e8") BlockyMotionVector grim_def_g_aBlockyMotionVectors[255] __asm__("_g_aBlockyMotionVectors") = {
    {0},
    { .nX = -1, .nY = -43 },
    { .nX = 6, .nY = -43 },
    { .nX = -9, .nY = -42 },
    { .nX = 13, .nY = -41 },
    { .nX = -16, .nY = -40 },
    { .nX = 19, .nY = -39 },
    { .nX = -23, .nY = -36 },
    { .nX = 26, .nY = -34 },
    { .nX = -2, .nY = -33 },
    { .nX = 4, .nY = -33 },
    { .nX = -29, .nY = -32 },
    { .nX = -9, .nY = -32 },
    { .nX = 11, .nY = -31 },
    { .nX = -16, .nY = -29 },
    { .nX = 32, .nY = -29 },
    { .nX = 18, .nY = -28 },
    { .nX = -34, .nY = -26 },
    { .nX = -22, .nY = -25 },
    { .nX = -1, .nY = -25 },
    { .nX = 3, .nY = -25 },
    { .nX = -7, .nY = -24 },
    { .nX = 8, .nY = -24 },
    { .nX = 24, .nY = -23 },
    { .nX = 36, .nY = -23 },
    { .nX = -12, .nY = -22 },
    { .nX = 13, .nY = -21 },
    { .nX = -38, .nY = -20 },
    { .nY = -20 },
    { .nX = -27, .nY = -19 },
    { .nX = -4, .nY = -19 },
    { .nX = 4, .nY = -19 },
    { .nX = -17, .nY = -18 },
    { .nX = -8, .nY = -17 },
    { .nX = 8, .nY = -17 },
    { .nX = 18, .nY = -17 },
    { .nX = 28, .nY = -17 },
    { .nX = 39, .nY = -17 },
    { .nX = -12, .nY = -15 },
    { .nX = 12, .nY = -15 },
    { .nX = -21, .nY = -14 },
    { .nX = -1, .nY = -14 },
    { .nX = 1, .nY = -14 },
    { .nX = -41, .nY = -13 },
    { .nX = -5, .nY = -13 },
    { .nX = 5, .nY = -13 },
    { .nX = 21, .nY = -13 },
    { .nX = -31, .nY = -12 },
    { .nX = -15, .nY = -11 },
    { .nX = -8, .nY = -11 },
    { .nX = 8, .nY = -11 },
    { .nX = 15, .nY = -11 },
    { .nX = -2, .nY = -10 },
    { .nX = 1, .nY = -10 },
    { .nX = 31, .nY = -10 },
    { .nX = -23, .nY = -9 },
    { .nX = -11, .nY = -9 },
    { .nX = -5, .nY = -9 },
    { .nX = 4, .nY = -9 },
    { .nX = 11, .nY = -9 },
    { .nX = 42, .nY = -9 },
    { .nX = 6, .nY = -8 },
    { .nX = 24, .nY = -8 },
    { .nX = -18, .nY = -7 },
    { .nX = -7, .nY = -7 },
    { .nX = -3, .nY = -7 },
    { .nX = -1, .nY = -7 },
    { .nX = 2, .nY = -7 },
    { .nX = 18, .nY = -7 },
    { .nX = -43, .nY = -6 },
    { .nX = -13, .nY = -6 },
    { .nX = -4, .nY = -6 },
    { .nX = 4, .nY = -6 },
    { .nX = 8, .nY = -6 },
    { .nX = -33, .nY = -5 },
    { .nX = -9, .nY = -5 },
    { .nX = -2, .nY = -5 },
    { .nY = -5 },
    { .nX = 2, .nY = -5 },
    { .nX = 5, .nY = -5 },
    { .nX = 13, .nY = -5 },
    { .nX = -25, .nY = -4 },
    { .nX = -6, .nY = -4 },
    { .nX = -3, .nY = -4 },
    { .nX = 3, .nY = -4 },
    { .nX = 9, .nY = -4 },
    { .nX = -19, .nY = -3 },
    { .nX = -7, .nY = -3 },
    { .nX = -4, .nY = -3 },
    { .nX = -2, .nY = -3 },
    { .nX = -1, .nY = -3 },
    { .nY = -3 },
    { .nX = 1, .nY = -3 },
    { .nX = 2, .nY = -3 },
    { .nX = 4, .nY = -3 },
    { .nX = 6, .nY = -3 },
    { .nX = 33, .nY = -3 },
    { .nX = -14, .nY = -2 },
    { .nX = -10, .nY = -2 },
    { .nX = -5, .nY = -2 },
    { .nX = -3, .nY = -2 },
    { .nX = -2, .nY = -2 },
    { .nX = -1, .nY = -2 },
    { .nY = -2 },
    { .nX = 1, .nY = -2 },
    { .nX = 2, .nY = -2 },
    { .nX = 3, .nY = -2 },
    { .nX = 5, .nY = -2 },
    { .nX = 7, .nY = -2 },
    { .nX = 14, .nY = -2 },
    { .nX = 19, .nY = -2 },
    { .nX = 25, .nY = -2 },
    { .nX = 43, .nY = -2 },
    { .nX = -7, .nY = -1 },
    { .nX = -3, .nY = -1 },
    { .nX = -2, .nY = -1 },
    { .nX = -1, .nY = -1 },
    { .nY = -1 },
    { .nX = 1, .nY = -1 },
    { .nX = 2, .nY = -1 },
    { .nX = 3, .nY = -1 },
    { .nX = 10, .nY = -1 },
    { .nX = -5 },
    { .nX = -3 },
    { .nX = -2 },
    { .nX = -1 },
    { .nX = 1 },
    { .nX = 2 },
    { .nX = 3 },
    { .nX = 5 },
    { .nX = 7 },
    { .nX = -10, .nY = 1 },
    { .nX = -7, .nY = 1 },
    { .nX = -3, .nY = 1 },
    { .nX = -2, .nY = 1 },
    { .nX = -1, .nY = 1 },
    { .nY = 1 },
    { .nX = 1, .nY = 1 },
    { .nX = 2, .nY = 1 },
    { .nX = 3, .nY = 1 },
    { .nX = -43, .nY = 2 },
    { .nX = -25, .nY = 2 },
    { .nX = -19, .nY = 2 },
    { .nX = -14, .nY = 2 },
    { .nX = -5, .nY = 2 },
    { .nX = -3, .nY = 2 },
    { .nX = -2, .nY = 2 },
    { .nX = -1, .nY = 2 },
    { .nY = 2 },
    { .nX = 1, .nY = 2 },
    { .nX = 2, .nY = 2 },
    { .nX = 3, .nY = 2 },
    { .nX = 5, .nY = 2 },
    { .nX = 7, .nY = 2 },
    { .nX = 10, .nY = 2 },
    { .nX = 14, .nY = 2 },
    { .nX = -33, .nY = 3 },
    { .nX = -6, .nY = 3 },
    { .nX = -4, .nY = 3 },
    { .nX = -2, .nY = 3 },
    { .nX = -1, .nY = 3 },
    { .nY = 3 },
    { .nX = 1, .nY = 3 },
    { .nX = 2, .nY = 3 },
    { .nX = 4, .nY = 3 },
    { .nX = 19, .nY = 3 },
    { .nX = -9, .nY = 4 },
    { .nX = -3, .nY = 4 },
    { .nX = 3, .nY = 4 },
    { .nX = 7, .nY = 4 },
    { .nX = 25, .nY = 4 },
    { .nX = -13, .nY = 5 },
    { .nX = -5, .nY = 5 },
    { .nX = -2, .nY = 5 },
    { .nY = 5 },
    { .nX = 2, .nY = 5 },
    { .nX = 5, .nY = 5 },
    { .nX = 9, .nY = 5 },
    { .nX = 33, .nY = 5 },
    { .nX = -8, .nY = 6 },
    { .nX = -4, .nY = 6 },
    { .nX = 4, .nY = 6 },
    { .nX = 13, .nY = 6 },
    { .nX = 43, .nY = 6 },
    { .nX = -18, .nY = 7 },
    { .nX = -2, .nY = 7 },
    { .nY = 7 },
    { .nX = 2, .nY = 7 },
    { .nX = 7, .nY = 7 },
    { .nX = 18, .nY = 7 },
    { .nX = -24, .nY = 8 },
    { .nX = -6, .nY = 8 },
    { .nX = -42, .nY = 9 },
    { .nX = -11, .nY = 9 },
    { .nX = -4, .nY = 9 },
    { .nX = 5, .nY = 9 },
    { .nX = 11, .nY = 9 },
    { .nX = 23, .nY = 9 },
    { .nX = -31, .nY = 10 },
    { .nX = -1, .nY = 10 },
    { .nX = 2, .nY = 10 },
    { .nX = -15, .nY = 11 },
    { .nX = -8, .nY = 11 },
    { .nX = 8, .nY = 11 },
    { .nX = 15, .nY = 11 },
    { .nX = 31, .nY = 12 },
    { .nX = -21, .nY = 13 },
    { .nX = -5, .nY = 13 },
    { .nX = 5, .nY = 13 },
    { .nX = 41, .nY = 13 },
    { .nX = -1, .nY = 14 },
    { .nX = 1, .nY = 14 },
    { .nX = 21, .nY = 14 },
    { .nX = -12, .nY = 15 },
    { .nX = 12, .nY = 15 },
    { .nX = -39, .nY = 17 },
    { .nX = -28, .nY = 17 },
    { .nX = -18, .nY = 17 },
    { .nX = -8, .nY = 17 },
    { .nX = 8, .nY = 17 },
    { .nX = 17, .nY = 18 },
    { .nX = -4, .nY = 19 },
    { .nY = 19 },
    { .nX = 4, .nY = 19 },
    { .nX = 27, .nY = 19 },
    { .nX = 38, .nY = 20 },
    { .nX = -13, .nY = 21 },
    { .nX = 12, .nY = 22 },
    { .nX = -36, .nY = 23 },
    { .nX = -24, .nY = 23 },
    { .nX = -8, .nY = 24 },
    { .nX = 7, .nY = 24 },
    { .nX = -3, .nY = 25 },
    { .nX = 1, .nY = 25 },
    { .nX = 22, .nY = 25 },
    { .nX = 34, .nY = 26 },
    { .nX = -18, .nY = 28 },
    { .nX = -32, .nY = 29 },
    { .nX = 16, .nY = 29 },
    { .nX = -11, .nY = 31 },
    { .nX = 9, .nY = 32 },
    { .nX = 29, .nY = 32 },
    { .nX = -4, .nY = 33 },
    { .nX = 2, .nY = 33 },
    { .nX = -26, .nY = 34 },
    { .nX = 23, .nY = 36 },
    { .nX = -19, .nY = 39 },
    { .nX = 16, .nY = 40 },
    { .nX = -13, .nY = 41 },
    { .nX = 9, .nY = 42 },
    { .nX = -6, .nY = 43 },
    { .nX = 1, .nY = 43 },
    {0},
    {0},
    {0}
};
/* 0x004f38e4, 4 bytes */ GRIM_DATA("004f38e4") unsigned int grim_def_g_dwFob_blk16_configure_old_mod __asm__("_g_dwFob_blk16_configure_old_mod") = 0xffffffff;
/* 0x004f38e8, 64 bytes */ GRIM_DATA("004f38e8") int grim_def_g_anBlockySplit4Y[16] __asm__("_g_anBlockySplit4Y") = {
    0, 1, 2, 3, 3, 3, 3, 2,
    1, 0, 0, 0, 1, 2, 2, 1
};
/* 0x004f3928, 64 bytes */ GRIM_DATA("004f3928") int grim_def_g_anBlockySplit4X[16] __asm__("_g_anBlockySplit4X") = {
    0, 0, 0, 0, 1, 2, 3, 3,
    3, 3, 2, 1, 1, 1, 2, 2
};
/* 0x004f3968, 64 bytes */ GRIM_DATA("004f3968") int grim_def_g_anBlockySplit8Y[16] __asm__("_g_anBlockySplit8Y") = {
    0, 2, 5, 7, 7, 7, 7, 7,
    7, 5, 2
};
/* 0x004f39a8, 64 bytes */ GRIM_DATA("004f39a8") int grim_def_g_anBlockySplit8X[16] __asm__("_g_anBlockySplit8X") = {
    0, 0, 0, 0, 1, 3, 4, 6,
    7, 7, 7, 7, 6, 4, 3, 1
};
/* 0x004f39e8, 4 bytes */ /* loose */ int grim_def_g_nBlkLastSeq __asm__("_g_nBlkLastSeq") = -1;
/* 0x004f39ec, 24 bytes */ /* loose */ char grim_def_s_FLOBDEC_insane_blocky16_004f39ec[24] __asm__("_s_FLOBDEC_insane_blocky16_004f39ec") = "FLOBDEC=insane_blocky16";
/* 0x004f3a04, 36 bytes */ /* loose */ char grim_def_s_LECMODULE_insane_blocky16_flobde_004f3a04[36] __asm__("_s_LECMODULE_insane_blocky16_flobde_004f3a04") = "LECMODULE=insane_blocky16_flobdec";
/* 0x004f3a28, 60 bytes */ /* loose */ char grim_def_s_FlobDec_Blocky16_Module__Cannot_a_004f3a28[60] __asm__("_s_FlobDec_Blocky16_Module__Cannot_a_004f3a28") = "FlobDec-Blocky16 Module: Cannot allocate memory services.";
/* 0x004f3a64, 60 bytes */ /* loose */ char grim_def_s_FlobDec_Blocky16_Module__Cannot_a_004f3a64[60] __asm__("_s_FlobDec_Blocky16_Module__Cannot_a_004f3a64") = "FlobDec-Blocky16 Module: Cannot allocate bitmap services.";
/* 0x004f3aa0, 16 bytes */ /* loose */ char grim_def_s_BITMAP_clear_004f3aa0[16] __asm__("_s_BITMAP_clear_004f3aa0") = "BITMAP.clear";
/* 0x004f3ab0, 16 bytes */ /* loose */ char grim_def_s_Blocky16_Tile_004f3ab0[16] __asm__("_s_Blocky16_Tile_004f3ab0") = "Blocky16-Tile";
/* 0x004f3ac0, 44 bytes */ /* loose */ char grim_def_s_Decompresses_a_block16_tile_vide_004f3ac0[44] __asm__("_s_Decompresses_a_block16_tile_vide_004f3ac0") = "Decompresses a block16-tile video frame.";
/* 0x004f3aec, 208 bytes */ /* loose */ char grim_def_s_This_module_decompresses_the_blo_004f3aec[208] __asm__("_s_This_module_decompresses_the_blo_004f3aec") = "This module decompresses the block16-tile compressed animations used in Outlaws, Monkey Island III, and Shadows of the Empire PC. Images are deltad, so they must be decompressed sequentially from frame 0.";
/* 0x004f3bbc, 60 bytes */ /* loose */ char grim_def_s_C__grimsrc_libs_lecsmush_insane__004f3bbc[60] __asm__("_s_C__grimsrc_libs_lecsmush_insane__004f3bbc") = "C:\\grimsrc\\libs\\lecsmush\\insane\\source\\flobject\\D_bloc16.c";
/* 0x008da4f8, 4 bytes */ /* loose */ unsigned char grim_def_g_pBlocky16_memory_services[4] __asm__("_g_pBlocky16_memory_services") = {0};
/* 0x008da4fc, 4 bytes */ /* loose */ unsigned char grim_def_g_pBlocky16_bitmap_services[4] __asm__("_g_pBlocky16_bitmap_services") = {0};
/* 0x008da500, 4 bytes */ /* loose */ unsigned char grim_def_g_pBlocky16_share_services[4] __asm__("_g_pBlocky16_share_services") = {0};
/* 0x008da504, 4 bytes */ /* loose */ unsigned int grim_def_g_dwBlocky16_share_config __asm__("_g_dwBlocky16_share_config") = 0x0;
/* 0x008da508, 4 bytes */ /* loose */ unsigned char grim_def_g_pFob_blit_routine[4] __asm__("_g_pFob_blit_routine") = {0};
/* 0x008da50c, 4 bytes */ /* loose */ unsigned char grim_def_g_pFob_blk16_render_buffer[4] __asm__("_g_pFob_blk16_render_buffer") = {0};
/* 0x008da510, 4 bytes */ /* loose */ unsigned char grim_def_g_pbBlkExpand[4] __asm__("_g_pbBlkExpand") = {0};
/* 0x008da514, 4 bytes */ /* loose */ int grim_def_g_nFob_translation_shiftr __asm__("_g_nFob_translation_shiftr") = 0;
/* 0x008da518, 4 bytes */ /* loose */ int grim_def_g_nFob_translation_shiftg __asm__("_g_nFob_translation_shiftg") = 0;
/* 0x008da51c, 4 bytes */ /* loose */ int grim_def_g_nFob_translation_shiftb __asm__("_g_nFob_translation_shiftb") = 0;
static unsigned char grim_anchor_008da520[0] __attribute__((section(".data$grim_008da520"), aligned(16), used));
static unsigned char grim_pad_008da520[0] __attribute__((section(".data$grim_008da520_"), aligned(4), used));
/* 0x008da520, 8 bytes */ GRIM_DATA("008da520z") int grim_def_g_nGlobal_bm_type __asm__("_g_nGlobal_bm_type") = 0;
/* 0x008da524, 4 bytes: the rest of grim_def_g_nGlobal_bm_type's span */ GRIM_DATA("008da520z") static unsigned char g_nGlobal_bm_type__tail[4] __attribute__((used)) = {0};
/* 0x008da528, 4 bytes */ GRIM_DATA("008da528") unsigned char grim_def_g_pBlkBitmap0[4] __asm__("_g_pBlkBitmap0") = {0};
/* 0x008da52c, 4 bytes */ GRIM_DATA("008da52c") unsigned char grim_def_g_pBlkBitmap1[4] __asm__("_g_pBlkBitmap1") = {0};
/* 0x008da530, 4 bytes */ GRIM_DATA("008da530") unsigned char grim_def_g_pBlkBitmap2[4] __asm__("_g_pBlkBitmap2") = {0};
/* 0x008da534, 4 bytes */ GRIM_DATA("008da534") int grim_def_g_nFob_buffersize __asm__("_g_nFob_buffersize") = 0;
/* 0x008da538, 8 bytes */ GRIM_DATA("008da538") unsigned char grim_def_g_pbBlkOutput[8] __asm__("_g_pbBlkOutput") = {0};
/* 0x00906c48, 4 bytes */ /* loose */ unsigned int grim_def_g_stBlockyDecState __asm__("_g_stBlockyDecState") = 0x0;
/* 0x00906c4c, 4 bytes */ /* loose */ unsigned int grim_def_UINT_00906c4c __asm__("_UINT_00906c4c") = 0x0;
/* 0x00906c50, 4 bytes */ /* loose */ unsigned char grim_def_DAT_00906c50[4] __asm__("_DAT_00906c50") = {0};
/* 0x00906c54, 4 bytes */ /* loose */ unsigned int grim_def_UINT_00906c54 __asm__("_UINT_00906c54") = 0x0;
/* 0x00906c58, 4 bytes */ /* loose */ unsigned char grim_def_DAT_00906c58[4] __asm__("_DAT_00906c58") = {0};
static unsigned char grim_anchor_00906c5c[0] __attribute__((section(".data$grim_00906c5c"), aligned(16), used));
static unsigned char grim_pad_00906c5c[12] __attribute__((section(".data$grim_00906c5c_"), aligned(4), used));
/* 0x00906c5c, 1 bytes */ GRIM_DATA("00906c5cz") unsigned char grim_def_DAT_00906c5c __asm__("_DAT_00906c5c") = 0x0;
/* 0x00906c5d, 3 bytes */ GRIM_DATA("00906c5cz") unsigned char grim_def_DAT_00906c5d[3] __asm__("_DAT_00906c5d") = {0};
/* 0x00906c60, 4 bytes */ /* loose */ int grim_def_INT_00906c60 __asm__("_INT_00906c60") = 0;
/* 0x00906c64, 4 bytes */ /* loose */ unsigned char grim_def_DAT_00906c64[4] __asm__("_DAT_00906c64") = {0};
/* 0x00906c68, 4 bytes */ /* loose */ unsigned int grim_def_UINT_00906c68 __asm__("_UINT_00906c68") = 0x0;
/* 0x00906c6c, 4 bytes */ /* loose */ unsigned int grim_def_UINT_00906c6c __asm__("_UINT_00906c6c") = 0x0;
/* 0x00906c70, 4 bytes */ /* loose */ unsigned char grim_def_DAT_00906c70[4] __asm__("_DAT_00906c70") = {0};
static unsigned char grim_anchor_00906c74[0] __attribute__((section(".data$grim_00906c74"), aligned(16), used));
static unsigned char grim_pad_00906c74[4] __attribute__((section(".data$grim_00906c74_"), aligned(4), used));
/* 0x00906c74, 12 bytes */ GRIM_DATA("00906c74z") unsigned char grim_def_g_pFob_blk16_key_buffer[12] __asm__("_g_pFob_blk16_key_buffer") = {0};
/* 0x00906c80, 256 bytes */ GRIM_DATA("00906c80") unsigned char grim_def_g_aBlockySplit8[256] __asm__("_g_aBlockySplit8") = {0};
/* 0x00906d80, 64 bytes */ GRIM_DATA("00906d80") unsigned char grim_def_DAT_00906d80[64] __asm__("_DAT_00906d80") = {0};
/* 0x00906dc0, 64 bytes */ GRIM_DATA("00906dc0") unsigned char grim_def_DAT_00906dc0[64] __asm__("_DAT_00906dc0") = {0};
/* 0x00906e00, 1 bytes */ GRIM_DATA("00906e00") unsigned char grim_def_DAT_00906e00 __asm__("_DAT_00906e00") = 0x0;
/* 0x00906e01, 98943 bytes */ GRIM_DATA("00906e00") unsigned char grim_def_DAT_00906e01[98943] __asm__("_DAT_00906e01") = {0};
/* 0x0091f080, 32 bytes */ GRIM_DATA("0091f080") unsigned char grim_def_g_pFob_blk16_delta_buffer[32] __asm__("_g_pFob_blk16_delta_buffer") = {0};
/* 0x0091f0a0, 64 bytes */ GRIM_DATA("0091f0a0") unsigned char grim_def_g_aBlockySplit4[64] __asm__("_g_aBlockySplit4") = {0};
/* 0x0091f0e0, 16 bytes */ GRIM_DATA("0091f0e0") unsigned char grim_def_DAT_0091f0e0[16] __asm__("_DAT_0091f0e0") = {0};
/* 0x0091f0f0, 16 bytes */ GRIM_DATA("0091f0f0") unsigned char grim_def_DAT_0091f0f0[16] __asm__("_DAT_0091f0f0") = {0};
/* 0x0091f100, 1 bytes */ GRIM_DATA("0091f100") unsigned char grim_def_DAT_0091f100 __asm__("_DAT_0091f100") = 0x0;
/* 0x0091f101, 255 bytes */ GRIM_DATA("0091f100") unsigned char grim_def_DAT_0091f101[255] __asm__("_DAT_0091f101") = {0};
/* 0x0091f200, 1 bytes */ GRIM_DATA("0091f200") unsigned char grim_def_DAT_0091f200[1] __asm__("_DAT_0091f200") = {0};
/* 0x0091f201, 32415 bytes */ GRIM_DATA("0091f200") unsigned char grim_def_DAT_0091f201[32415] __asm__("_DAT_0091f201") = {0};
/* 0x009270a0, 96 bytes */ GRIM_DATA("009270a0") short grim_def_g_asBlockyMotion __asm__("_g_asBlockyMotion") = 0;
/* 0x009270a2, 94 bytes: the rest of grim_def_g_asBlockyMotion's span */ GRIM_DATA("009270a0") static unsigned char g_asBlockyMotion__tail[94] __attribute__((used)) = {0};
/* 0x00927100, 1 bytes */ GRIM_DATA("00927100") unsigned char grim_def_DAT_00927100[1] __asm__("_DAT_00927100") = {0};
/* 0x00927101, 415 bytes */ GRIM_DATA("00927100") unsigned char grim_def_DAT_00927101[415] __asm__("_DAT_00927101") = {0};
