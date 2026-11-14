/* GRIMFANDANGO.EXE :: rdcanvas.c
 * functions 0x00404c00 .. 0x004c0610 (12 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00404c00  rdActive_AdvanceFrame ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Clears the per-scanline edge buckets for the current canvas height Original name
   rdActive_AdvanceFrame (the remaster's GrimFandango (Linux): aligned call in rdCache_Flush); was
   rdCanvas_InitEdgeTables. */

void __cdecl rdActive_AdvanceFrame(void)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  
  iVar4 = *(int *)(*(int *)((int)g_pRdCamera_CurCamera + 4) + 0x1c);
  _DAT_004f6ef8 = 0xffff0000;
  uVar1 = (*(int *)(*(int *)((int)g_pRdCamera_CurCamera + 4) + 0x24) - iVar4) + 1;
  UINT_004f6f20 = (uint)&g_aActiveEdgeTail;
  _DAT_005e6f8c = &g_aActiveEdgeHead;
  puVar5 = (undefined4 *)(&g_apNewActiveEdges + iVar4 * 4);
  for (uVar2 = uVar1 & 0x3fffffff; uVar2 != 0; uVar2 = uVar2 - 1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
    *(undefined1 *)puVar5 = 0;
    puVar5 = (undefined4 *)((int)puVar5 + 1);
  }
  puVar5 = (undefined4 *)(&g_apRemoveActiveEdges + iVar4 * 4);
  for (uVar1 = uVar1 & 0x3fffffff; uVar1 != 0; uVar1 = uVar1 - 1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
    *(undefined1 *)puVar5 = 0;
    puVar5 = (undefined4 *)((int)puVar5 + 1);
  }
  g_dwYMinEdge = 0x7fffffff;
  g_dwYMaxEdge = 0;
  _DAT_004f6f1c = 0;
  _DAT_005e6f68 = 0x7fffffff;
  _DAT_005e6f90 = 0;
  g_dwNumActiveFaces = 0;
  g_dwNumActiveEdges = 0;
  g_dwNumActiveSpans = 0;
  return;
}

/* ---- 0x00404ca0  rdActive_ClearFrameCounters ---- */
/* Original name rdActive_ClearFrameCounters (the remaster's GrimFandango (Linux): the second
   counter reset of rdClearPreStatistics (clears rdActive_drawnFaces, counted in
   rdActive_AddActiveFace)); was rdCanvas_ResetPolyCount. */

void __cdecl rdActive_ClearFrameCounters(void)

{
  g_dwRdActive_drawnFaces = 0;
  return;
}

/* ---- 0x00404cb0  rdActive_DrawScene ---- */
/* Rdcanvas.c: active-edge scanline loop over all queued polygons; merges edges per scanline, emits
   spans, flushes them Original name rdActive_DrawScene (the remaster's GrimFandango (Linux):
   aligned call in rdCache_Flush); was rdCanvas_ScanConvert. */

void rdActive_DrawScene(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  uint uVar5;
  undefined *puVar6;
  undefined *puVar7;
  
  rdActive_BuildEdges();
  g_dwYCurScanLine = g_dwYMinEdge;
  if (g_dwYMinEdge <= g_dwYMaxEdge) {
    do {
      piVar4 = *(int **)(&g_apNewActiveEdges + g_dwYCurScanLine * 4);
      uVar5 = UINT_004f6f20;
      while (piVar4 != (int *)0x0) {
        iVar1 = piVar4[10];
        iVar2 = *(int *)(uVar5 + 0x28);
        piVar3 = (int *)piVar4[0x14];
        while ((((iVar2 < iVar1 && (uVar5 = *(uint *)(uVar5 + 0x50), *(int *)(uVar5 + 0x28) < iVar1)
                 ) && (uVar5 = *(uint *)(uVar5 + 0x50), *(int *)(uVar5 + 0x28) < iVar1)) &&
               (uVar5 = *(uint *)(uVar5 + 0x50), *(int *)(uVar5 + 0x28) < iVar1))) {
          uVar5 = *(uint *)(uVar5 + 0x50);
          iVar2 = *(int *)(uVar5 + 0x28);
        }
        piVar4[0x14] = uVar5;
        piVar4[0x13] = *(int *)(uVar5 + 0x4c);
        *(int **)(*(int *)(uVar5 + 0x4c) + 0x50) = piVar4;
        *(int **)(uVar5 + 0x4c) = piVar4;
        if (*piVar4 == 0) {
          *(int **)(piVar4[1] + 0x1f0) = piVar4;
          piVar4 = piVar3;
        }
        else {
          *(int **)(piVar4[1] + 0x1ec) = piVar4;
          piVar4 = piVar3;
        }
      }
      rdActive_BuildSpans();
      for (iVar2 = *(int *)(&g_apRemoveActiveEdges + g_dwYCurScanLine * 4); iVar2 != 0;
          iVar2 = *(int *)(iVar2 + 0x54)) {
        *(undefined4 *)(*(int *)(iVar2 + 0x50) + 0x4c) = *(undefined4 *)(iVar2 + 0x4c);
        *(undefined4 *)(*(int *)(iVar2 + 0x4c) + 0x50) = *(undefined4 *)(iVar2 + 0x50);
      }
      puVar6 = (undefined *)UINT_004f6f20;
      if ((undefined *)UINT_004f6f20 != &g_aActiveEdgeTail) {
        do {
          (**(code **)(puVar6 + 0x48))(puVar6);
          if (*(int *)(puVar6 + 0x28) < *(int *)(*(int *)(puVar6 + 0x4c) + 0x28)) {
            puVar7 = *(undefined **)(puVar6 + 0x50);
            *(int *)(puVar7 + 0x4c) = *(int *)(puVar6 + 0x4c);
            *(undefined **)(*(int *)(puVar6 + 0x4c) + 0x50) = puVar7;
            iVar1 = *(int *)(*(int *)(puVar6 + 0x4c) + 0x4c);
            iVar2 = *(int *)(iVar1 + 0x28);
            while (*(int *)(puVar6 + 0x28) < iVar2) {
              iVar1 = *(int *)(iVar1 + 0x4c);
              iVar2 = *(int *)(iVar1 + 0x28);
            }
            iVar2 = *(int *)(iVar1 + 0x50);
            *(int *)(puVar6 + 0x4c) = iVar1;
            *(int *)(puVar6 + 0x50) = iVar2;
            *(undefined **)(iVar2 + 0x4c) = puVar6;
            *(undefined **)(iVar1 + 0x50) = puVar6;
          }
          else {
            puVar7 = *(undefined **)(puVar6 + 0x50);
          }
          puVar6 = puVar7;
        } while (puVar7 != &g_aActiveEdgeTail);
      }
      g_dwYCurScanLine = g_dwYCurScanLine + 1;
    } while (g_dwYCurScanLine <= g_dwYMaxEdge);
  }
  rdActive_FlushSpans();
  return;
}

/* ---- 0x00404e00  rdActive_BuildSpans ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Walks the active edge list for one scanline, computing 0x2c-byte span records with interpolated
   z/u/v/light Original name rdActive_BuildSpans (the remaster's GrimFandango (Linux): aligned call
   in rdActive_DrawScene); was rdCanvas_EmitSpans. */

void __cdecl rdActive_BuildSpans(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  float fVar7;
  bool bVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  int *piVar13;
  uint uVar14;
  int *piVar15;
  int *piVar16;
  int *piVar17;
  #define local_2c (*(uint *)(_frame + (0x40 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  
  if ((g_dwNumActiveEdges != 0) &&
     (piVar17 = (int *)0x0, piVar13 = (int *)UINT_004f6f20,
     (undefined *)UINT_004f6f20 != &g_aActiveEdgeTail)) {
    do {
      piVar2 = (int *)piVar13[1];
      if (*piVar13 == 0) {
        iVar10 = piVar2[0x7e];
        piVar2[0x7e] = iVar10 + -1;
        if (iVar10 + -1 == 0) {
          if (piVar2 == piVar17) {
            uVar9 = piVar13[10];
            if ((uVar9 & 0xffff) != 0) {
              uVar9 = uVar9 + 0x10000 & 0xffff0000;
            }
            iVar10 = (int)(uVar9 - piVar17[0x7d]) >> 0x10;
            if (0 < iVar10) {
              if (0x7ff < g_dwNumActiveSpans) {
                rdActive_FlushSpans();
              }
              iVar3 = piVar17[0x7b];
              iVar4 = piVar17[0x7c];
              iVar1 = g_dwNumActiveSpans * 0x2c;
              piVar2 = (int *)(&DAT_004f6f30 + iVar1);
              g_dwNumActiveSpans = g_dwNumActiveSpans + 1;
              *piVar2 = piVar17[0x7d] >> 0x10;
              *(int *)(&DAT_004f6f34 + iVar1) = iVar10;
              *(uint *)(&DAT_004f6f38 + iVar1) = g_dwYCurScanLine;
              *(undefined4 *)(&DAT_004f6f58 + iVar1) = 0;
              uVar14 = *(uint *)(iVar4 + 0x28);
              if ((uVar14 & 0xffff) != 0) {
                uVar14 = uVar14 + 0x10000 & 0xffff0000;
              }
              uVar11 = *(uint *)(iVar3 + 0x28);
              uVar12 = uVar11;
              if ((uVar11 & 0xffff) != 0) {
                uVar12 = uVar11 + 0x10000 & 0xffff0000;
              }
              uVar14 = uVar14 - uVar12 >> 0x10;
              iVar10 = piVar17[0x7d] - uVar11;
              fVar7 = (float)iVar10 * 1.5258789e-05;
              *(float *)(&DAT_004f6f4c + iVar1) =
                   (float)piVar17[0x61] * fVar7 + *(float *)(iVar3 + 0x10);
              if (*(int *)(*piVar17 + 8) == 4) {
                iVar5 = *(int *)(*piVar17 + 0x10);
                if (iVar5 == 0) {
                  iVar5 = *(int *)(&g_aRdRaster_OneOverNFixed + uVar14 * 4);
                  lVar6 = (longlong)(*(int *)(iVar4 + 0x30) - *(int *)(iVar3 + 0x30)) *
                          (longlong)iVar5;
                  uVar11 = (uint)lVar6 >> 0x10 | (int)((ulonglong)lVar6 >> 0x20) << 0x10;
                  *(int *)(&DAT_004f6f40 + iVar1) = (int)uVar11 >> ((byte)piVar17[0x70] & 0x1f);
                  lVar6 = (longlong)iVar10 * (longlong)(int)uVar11;
                  *(int *)(&DAT_004f6f3c + iVar1) =
                       (int)(*(int *)(iVar3 + 0x30) +
                            ((uint)lVar6 >> 0x10 | (int)((ulonglong)lVar6 >> 0x20) << 0x10)) >>
                       ((byte)piVar17[0x70] & 0x1f);
                  lVar6 = (longlong)(*(int *)(iVar4 + 0x38) - *(int *)(iVar3 + 0x38)) *
                          (longlong)iVar5;
                  uVar11 = (uint)lVar6 >> 0x10 | (int)((ulonglong)lVar6 >> 0x20) << 0x10;
                  *(int *)(&DAT_004f6f48 + iVar1) = (int)uVar11 >> ((byte)piVar17[0x70] & 0x1f);
                  lVar6 = (longlong)iVar10 * (longlong)(int)uVar11;
                  *(int *)(&DAT_004f6f44 + iVar1) =
                       (int)(*(int *)(iVar3 + 0x38) +
                            ((uint)lVar6 >> 0x10 | (int)((ulonglong)lVar6 >> 0x20) << 0x10)) >>
                       ((byte)piVar17[0x70] & 0x1f);
                }
                else if (iVar5 == 1) {
                  *(float *)(&DAT_004f6f3c + iVar1) =
                       (float)piVar17[99] * fVar7 + *(float *)(iVar3 + 0x18);
                  *(float *)(&DAT_004f6f40 + iVar1) =
                       (float)piVar17[0x65] * fVar7 + *(float *)(iVar3 + 0x20);
                }
              }
              else {
                *(int *)(&DAT_004f6f3c + iVar1) = piVar17[0x74];
              }
              if (*(int *)(*piVar17 + 0xc) == 3) {
                lVar6 = (longlong)(*(int *)(iVar4 + 0x40) - *(int *)(iVar3 + 0x40)) *
                        (longlong)*(int *)(&g_aRdRaster_OneOverNFixed + uVar14 * 4);
                uVar14 = (uint)lVar6 >> 0x10 | (int)((ulonglong)lVar6 >> 0x20) << 0x10;
                *(uint *)(&DAT_004f6f54 + iVar1) = uVar14;
                if (((int)uVar14 < 0) && (-0x51e < (int)uVar14)) {
                  *(undefined4 *)(&DAT_004f6f54 + iVar1) = 0;
                }
                *(uint *)(&DAT_004f6f50 + iVar1) =
                     *(int *)(iVar3 + 0x40) +
                     ((uint)((longlong)iVar10 * (longlong)*(int *)(&DAT_004f6f54 + iVar1)) >> 0x10 |
                     (int)((ulonglong)((longlong)iVar10 * (longlong)*(int *)(&DAT_004f6f54 + iVar1))
                          >> 0x20) << 0x10);
              }
              if (piVar17[0x6e] == 0) {
                piVar17[0x6e] = (int)piVar2;
              }
              else {
                *(int **)(piVar17[0x6f] + 0x28) = piVar2;
              }
              piVar17[0x6f] = (int)piVar2;
            }
            piVar17 = (int *)piVar17[0x80];
            if (piVar17 != (int *)0x0) {
              piVar17[0x7d] = uVar9;
              piVar17[0x7f] = 0;
            }
          }
          else {
            if (piVar2[0x80] != 0) {
              *(int *)(piVar2[0x80] + 0x1fc) = piVar2[0x7f];
            }
            if (piVar2[0x7f] != 0) {
              *(int *)(piVar2[0x7f] + 0x200) = piVar2[0x80];
            }
          }
        }
      }
      else {
        iVar10 = piVar2[0x7e];
        piVar2[0x7e] = iVar10 + 1;
        if (iVar10 + 1 == 1) {
          if ((*(int *)(*piVar2 + 8) != 4) || (*(int *)(*piVar2 + 0x10) != 1)) {
            uVar9 = *(uint *)(piVar2[0x7c] + 0x28);
            if ((uVar9 & 0xffff) != 0) {
              uVar9 = uVar9 + 0x10000 & 0xffff0000;
            }
            uVar14 = *(uint *)(piVar2[0x7b] + 0x28);
            if ((uVar14 & 0xffff) != 0) {
              uVar14 = uVar14 + 0x10000 & 0xffff0000;
            }
            fVar7 = (*(float *)(piVar2[0x7c] + 0x10) - *(float *)(piVar2[0x7b] + 0x10)) *
                    (float)(&g_dwRdRaster_aOneOverNFlex)[uVar9 - uVar14 >> 0x10];
            piVar2[0x61] = (int)fVar7;
            piVar2[0x67] = (int)ROUND(fVar7 * 65536.0);
          }
          if (piVar17 == (int *)0x0) {
            piVar2[0x7f] = 0;
            piVar2[0x80] = 0;
            uVar9 = piVar13[10];
            if ((uVar9 & 0xffff) != 0) {
              uVar9 = uVar9 + 0x10000 & 0xffff0000;
            }
            piVar2[0x7d] = uVar9;
            piVar17 = piVar2;
          }
          else {
            uVar9 = *(uint *)(*piVar2 + 0x74);
            if (((*(uint *)(*piVar17 + 0x74) ^ uVar9) & 0xffff) == 0) {
              uVar14 = *(uint *)(*piVar17 + 0x74) >> 0x10;
              if (uVar14 < uVar9 >> 0x10) {
                bVar8 = true;
              }
              else {
                if (uVar14 <= uVar9 >> 0x10) goto LAB_00404f44;
                bVar8 = false;
              }
            }
            else {
LAB_00404f44:
              fVar7 = (float)(piVar13[10] - *(int *)(piVar17[0x7b] + 0x28)) * 1.5258789e-05 *
                      (float)piVar17[0x61] + *(float *)(piVar17[0x7b] + 0x10);
              if ((float)piVar13[4] <= fVar7) {
                if (((float)piVar13[4] != fVar7) || ((float)piVar2[0x61] <= (float)piVar17[0x61])) {
                  bVar8 = false;
                }
                else {
                  bVar8 = true;
                }
              }
              else {
                bVar8 = true;
              }
            }
            if (bVar8) {
              uVar9 = piVar13[10];
              if ((uVar9 & 0xffff) != 0) {
                uVar9 = uVar9 + 0x10000 & 0xffff0000;
              }
              iVar10 = (int)(uVar9 - piVar17[0x7d]) >> 0x10;
              if (0 < iVar10) {
                if (0x7ff < g_dwNumActiveSpans) {
                  rdActive_FlushSpans();
                }
                iVar3 = piVar17[0x7b];
                iVar1 = g_dwNumActiveSpans * 0x2c;
                piVar16 = (int *)(&DAT_004f6f30 + iVar1);
                iVar4 = piVar17[0x7c];
                g_dwNumActiveSpans = g_dwNumActiveSpans + 1;
                *piVar16 = piVar17[0x7d] >> 0x10;
                *(int *)(&DAT_004f6f34 + iVar1) = iVar10;
                uVar14 = g_dwYCurScanLine;
                *(undefined4 *)(&DAT_004f6f58 + iVar1) = 0;
                *(uint *)(&DAT_004f6f38 + iVar1) = uVar14;
                uVar14 = *(uint *)(iVar4 + 0x28);
                if ((uVar14 & 0xffff) != 0) {
                  uVar14 = uVar14 + 0x10000 & 0xffff0000;
                }
                uVar11 = *(uint *)(iVar3 + 0x28);
                if ((uVar11 & 0xffff) != 0) {
                  uVar11 = uVar11 + 0x10000 & 0xffff0000;
                }
                uVar14 = uVar14 - uVar11 >> 0x10;
                iVar10 = piVar17[0x7d] - *(int *)(piVar17[0x7b] + 0x28);
                fVar7 = (float)iVar10 * 1.5258789e-05;
                *(float *)(&DAT_004f6f4c + iVar1) =
                     (float)piVar17[0x61] * fVar7 + *(float *)(iVar3 + 0x10);
                if (*(int *)(*piVar17 + 8) == 4) {
                  iVar5 = *(int *)(*piVar17 + 0x10);
                  if (iVar5 == 0) {
                    iVar5 = *(int *)(&g_aRdRaster_OneOverNFixed + uVar14 * 4);
                    lVar6 = (longlong)(*(int *)(iVar4 + 0x30) - *(int *)(iVar3 + 0x30)) *
                            (longlong)iVar5;
                    uVar11 = (uint)lVar6 >> 0x10 | (int)((ulonglong)lVar6 >> 0x20) << 0x10;
                    *(int *)(&DAT_004f6f40 + iVar1) = (int)uVar11 >> ((byte)piVar17[0x70] & 0x1f);
                    lVar6 = (longlong)iVar10 * (longlong)(int)uVar11;
                    *(int *)(&DAT_004f6f3c + iVar1) =
                         (int)(*(int *)(iVar3 + 0x30) +
                              ((uint)lVar6 >> 0x10 | (int)((ulonglong)lVar6 >> 0x20) << 0x10)) >>
                         ((byte)piVar17[0x70] & 0x1f);
                    lVar6 = (longlong)(*(int *)(iVar4 + 0x38) - *(int *)(iVar3 + 0x38)) *
                            (longlong)iVar5;
                    uVar11 = (uint)lVar6 >> 0x10 | (int)((ulonglong)lVar6 >> 0x20) << 0x10;
                    *(int *)(&DAT_004f6f48 + iVar1) = (int)uVar11 >> ((byte)piVar17[0x70] & 0x1f);
                    lVar6 = (longlong)iVar10 * (longlong)(int)uVar11;
                    *(int *)(&DAT_004f6f44 + iVar1) =
                         (int)(*(int *)(iVar3 + 0x38) +
                              ((uint)lVar6 >> 0x10 | (int)((ulonglong)lVar6 >> 0x20) << 0x10)) >>
                         ((byte)piVar17[0x70] & 0x1f);
                  }
                  else if (iVar5 == 1) {
                    *(float *)(&DAT_004f6f3c + iVar1) =
                         (float)piVar17[99] * fVar7 + *(float *)(iVar3 + 0x18);
                    *(float *)(&DAT_004f6f40 + iVar1) =
                         (float)piVar17[0x65] * fVar7 + *(float *)(iVar3 + 0x20);
                  }
                }
                else {
                  *(int *)(&DAT_004f6f3c + iVar1) = piVar17[0x74];
                }
                if (*(int *)(*piVar17 + 0xc) == 3) {
                  lVar6 = (longlong)(*(int *)(iVar4 + 0x40) - *(int *)(iVar3 + 0x40)) *
                          (longlong)*(int *)(&g_aRdRaster_OneOverNFixed + uVar14 * 4);
                  uVar14 = (uint)lVar6 >> 0x10 | (int)((ulonglong)lVar6 >> 0x20) << 0x10;
                  *(uint *)(&DAT_004f6f54 + iVar1) = uVar14;
                  if (((int)uVar14 < 0) && (-0x51e < (int)uVar14)) {
                    *(undefined4 *)(&DAT_004f6f54 + iVar1) = 0;
                  }
                  *(uint *)(&DAT_004f6f50 + iVar1) =
                       *(int *)(iVar3 + 0x40) +
                       ((uint)((longlong)iVar10 * (longlong)*(int *)(&DAT_004f6f54 + iVar1)) >> 0x10
                       | (int)((ulonglong)
                               ((longlong)iVar10 * (longlong)*(int *)(&DAT_004f6f54 + iVar1)) >>
                              0x20) << 0x10);
                }
                if (piVar17[0x6e] == 0) {
                  piVar17[0x6e] = (int)piVar16;
                }
                else {
                  *(int **)(piVar17[0x6f] + 0x28) = piVar16;
                }
                piVar17[0x6f] = (int)piVar16;
              }
              piVar2[0x80] = (int)piVar17;
              piVar17[0x7f] = (int)piVar2;
              piVar2[0x7f] = 0;
              piVar2[0x7d] = uVar9;
              piVar17 = piVar2;
            }
            else {
              piVar16 = (int *)piVar17[0x80];
              local_20 = (uint)piVar17;
              if ((int *)piVar17[0x80] != (int *)0x0) {
                do {
                  piVar15 = piVar16;
                  if (((*(uint *)(*piVar15 + 0x74) ^ uVar9) & 0xffff) == 0) {
                    uVar14 = *(uint *)(*piVar15 + 0x74) >> 0x10;
                    if (uVar14 < uVar9 >> 0x10) {
                      bVar8 = true;
                    }
                    else {
                      if (uVar14 <= uVar9 >> 0x10) goto LAB_00405252;
LAB_004052b3:
                      bVar8 = false;
                    }
                  }
                  else {
LAB_00405252:
                    fVar7 = (float)(piVar13[10] - *(int *)(piVar15[0x7b] + 0x28)) * 1.5258789e-05 *
                            (float)piVar15[0x61] + *(float *)(piVar15[0x7b] + 0x10);
                    if ((float)piVar13[4] <= fVar7) {
                      if (((float)piVar13[4] != fVar7) ||
                         ((float)piVar2[0x61] <= (float)piVar15[0x61])) goto LAB_004052b3;
                      bVar8 = true;
                    }
                    else {
                      bVar8 = true;
                    }
                  }
                  piVar16 = piVar15;
                } while ((!bVar8) &&
                        (piVar16 = (int *)piVar15[0x80], local_20 = (uint)piVar15,
                        piVar16 != (int *)0x0));
                if (piVar16 != (int *)0x0) {
                  piVar2[0x7f] = local_20;
                  *(int **)(local_20 + 0x200) = piVar2;
                  piVar16[0x7f] = (int)piVar2;
                  piVar2[0x80] = (int)piVar16;
                  goto LAB_004055a9;
                }
              }
              *(int **)(local_20 + 0x200) = piVar2;
              piVar2[0x7f] = local_20;
              piVar2[0x80] = 0;
            }
          }
        }
      }
LAB_004055a9:
      piVar2 = piVar13 + 0x14;
      piVar13 = (int *)*piVar2;
    } while ((int *)*piVar2 != (int *)&g_aActiveEdgeTail);
  }
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_28
#undef local_2c
#undef local_8
#undef local_c

#endif


/* ---- 0x004055d0  rdActive_FlushSpans ---- */
/* Calls each polygon's span-draw callback for its accumulated spans and resets the span buffer
   Original name rdActive_FlushSpans (the remaster's GrimFandango (Linux): the only unpaired user of
   numActiveFaces / numActiveSpans on both sides, same body); was rdCanvas_FlushSpans. */

void __cdecl rdActive_FlushSpans(void)

{
  uint *puVar1;
  uint uVar2;
  
  uVar2 = 0;
  if (g_dwNumActiveFaces != 0) {
    puVar1 = &UINT_005660f0;
    do {
      if (*puVar1 != 0) {
        (*(code *)puVar1[-1])(puVar1 + -0x6e);
        *puVar1 = 0;
        puVar1[1] = 0;
      }
      puVar1 = puVar1 + 0x81;
      uVar2 = uVar2 + 1;
    } while (uVar2 < g_dwNumActiveFaces);
  }
  g_dwNumActiveSpans = 0;
  return;
}

/* ---- 0x00405620  rdActive_BuildEdges ---- */
/* For every queued polygon, runs its edge-setup callback on each edge and inserts the edges into
   the per-scanline buckets Original name rdActive_BuildEdges (the remaster's GrimFandango (Linux):
   aligned call in rdActive_DrawScene); was rdCanvas_BuildEdgeLists. */

void __cdecl rdActive_BuildEdges(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  byte *pbVar8;
  undefined *puVar9;
  uint uVar10;
  uint *puVar11;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar10 = 0;
  pbVar8 = &g_bRdCache_aProcFaces;
  if (g_dwRdCache_numProcFaces != 0) {
    do {
      rdActive_AddActiveFace(pbVar8);
      pbVar8 = pbVar8 + 0x78;
      uVar10 = uVar10 + 1;
    } while (uVar10 < g_dwRdCache_numProcFaces);
  }
  puVar11 = &UINT_00565f38;
  puVar9 = &DAT_0050df38;
  local_4 = 0;
  if (g_dwNumActiveFaces != 0) {
    do {
      uVar10 = *puVar11;
      uVar4 = *(uint *)(uVar10 + 0x1c);
      uVar7 = 0;
      if (uVar4 != 0) {
        do {
          uVar1 = uVar7 + 1;
          uVar5 = ~-(uint)(uVar4 - 1 < uVar1) & uVar1;
          uVar4 = uVar5;
          if (*(int *)(*puVar11 + 0x50) == 0) {
            uVar4 = uVar7;
            uVar7 = uVar5;
          }
          iVar6 = (*(code *)puVar11[0x7a])(puVar9,puVar11,uVar4,uVar7);
          if (iVar6 != 0) {
            *(uint **)(puVar9 + 4) = puVar11;
            iVar6 = *(int *)(&g_apNewActiveEdges + *(int *)(puVar9 + 8) * 4);
            if ((iVar6 == 0) || (*(int *)(puVar9 + 0x28) <= *(int *)(iVar6 + 0x28))) {
              *(int *)(puVar9 + 0x50) = iVar6;
              *(undefined **)(&g_apNewActiveEdges + *(int *)(puVar9 + 8) * 4) = puVar9;
            }
            else {
              for (iVar3 = *(int *)(iVar6 + 0x50);
                  (iVar3 != 0 && (*(int *)(iVar3 + 0x28) < *(int *)(puVar9 + 0x28)));
                  iVar3 = *(int *)(iVar3 + 0x50)) {
                iVar6 = iVar3;
              }
              *(undefined4 *)(puVar9 + 0x50) = *(undefined4 *)(iVar6 + 0x50);
              *(undefined **)(iVar6 + 0x50) = puVar9;
            }
            uVar7 = *(uint *)(puVar9 + 8);
            uVar4 = *(int *)(puVar9 + 0xc) + -1 + uVar7;
            uVar2 = *(undefined4 *)(&g_apRemoveActiveEdges + uVar4 * 4);
            *(undefined **)(&g_apRemoveActiveEdges + uVar4 * 4) = puVar9;
            *(undefined4 *)(puVar9 + 0x54) = uVar2;
            if (uVar7 < g_dwYMinEdge) {
              g_dwYMinEdge = uVar7;
            }
            if (g_dwYMaxEdge < uVar4) {
              g_dwYMaxEdge = uVar4;
            }
            puVar9 = puVar9 + 0x58;
            g_dwNumActiveEdges = g_dwNumActiveEdges + 1;
          }
          uVar4 = *(uint *)(uVar10 + 0x1c);
          uVar7 = uVar1;
        } while (uVar1 < uVar4);
      }
      puVar11 = puVar11 + 0x81;
      local_4 = local_4 + 1;
    } while (local_4 < g_dwNumActiveFaces);
  }
  return;
}
#undef local_4


/* ---- 0x00405770  rdActive_AddActiveFace ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name rdActive_AddActiveFace (the remaster's GrimFandango (Linux): aligned call in
   rdActive_BuildEdges); was rdCanvas_PreparePolygon. */

uint __cdecl rdActive_AddActiveFace(byte *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  float *pfVar2;
  float fVar3;
  float fVar4;
  byte *pbVar5;
  float fVar6;
  int iVar7;
  uint uVar8;
  byte *pbVar9;
  int iVar10;
  int iVar11;
  #define local_4 (*(float *)(_frame + (0x20 - 0x4)))
  
  pbVar5 = param_1;
  uVar8 = g_dwNumActiveFaces;
  if (0x3ff < g_dwNumActiveFaces) {
    return 0;
  }
  local_4 = *(float *)(param_1 + 8);
  if (g_nRdroid_curGeometryMode <= PUN(int,(float)local_4)) {
    local_4 = PUN(float,g_nRdroid_curGeometryMode);
  }
  param_1 = *(byte **)(param_1 + 0xc);
  if (g_nRdroid_curLightingMode <= (int)param_1) {
    param_1 = (byte *)g_nRdroid_curLightingMode;
  }
  iVar10 = *(int *)(pbVar5 + 0x10);
  if (g_nRdroid_curTextureMode <= *(int *)(pbVar5 + 0x10)) {
    iVar10 = g_nRdroid_curTextureMode;
  }
  if (local_4 == 0.0) {
    return 0;
  }
  iVar1 = g_dwNumActiveFaces * 0x204;
  pfVar2 = (float *)(&UINT_00565f38 + g_dwNumActiveFaces * 0x81);
  *pfVar2 = PUN(float,pbVar5);
  (&UINT_005660f0)[uVar8 * 0x81] = 0;
  (&UINT_005660f4)[uVar8 * 0x81] = 0;
  *(undefined4 *)(&DAT_00566124 + iVar1) = 0;
  *(undefined4 *)(&DAT_00566128 + iVar1) = 0;
  *(undefined4 *)(&DAT_00566130 + iVar1) = 0;
  iVar1 = *(int *)(pbVar5 + 0x38);
  fVar6 = local_4;
  if (iVar1 == 0) {
    pbVar9 = (byte *)0x0;
    goto LAB_0040585d;
  }
  iVar7 = *(int *)(pbVar5 + 0x3c);
  if (iVar7 == -1) {
    iVar7 = *(int *)(iVar1 + 100);
    if (iVar7 < 0) {
LAB_0040583c:
      iVar7 = 0;
    }
    else {
      iVar11 = *(int *)(iVar1 + 0x60) + -1;
      if (iVar11 < iVar7) {
        iVar7 = iVar11;
      }
    }
  }
  else {
    if (iVar7 < 0) goto LAB_0040583c;
    iVar11 = *(int *)(iVar1 + 0x60) + -1;
    if (iVar11 < iVar7) {
      iVar7 = iVar11;
    }
  }
  pbVar9 = *(byte **)(iVar1 + 0x68 + iVar7 * 4);
  if ((local_4 == 5.60519e-45) && ((*pbVar9 & 8) == 0)) {
    fVar6 = 4.2039e-45;
  }
LAB_0040585d:
  if (((byte)g_dwRdroid_curRenderOptions & 2) == 0) {
    local_4 = 0.0;
  }
  else {
    local_4 = *(float *)(pbVar5 + 0x40);
  }
  if (fVar6 == 2.8026e-45) {
    if ((-1 < (int)param_1) && ((int)param_1 < 5)) {
      if ((*pbVar5 & 1) == 0) {
        if (g_nRdroid_curZBufferMethod == 1) {
          rdAFRaster_SetupNGonLW(pfVar2,(int)pbVar9);
        }
      }
      else {
        (**(code **)(pbVar5 + 0x18))(pfVar2,pbVar9,0);
      }
    }
  }
  else if (fVar6 == 4.2039e-45) {
    switch((int)(param_1)) {
    case 0x0:
      if ((*pbVar5 & 1) == 0) {
        if (g_nRdroid_curZBufferMethod == 1) {
          rdAFRaster_SetupNGonLS(pfVar2,(int)pbVar9);
        }
      }
      else {
        (**(code **)(pbVar5 + 0x18))(pfVar2,pbVar9,0);
      }
      break;
    case 0x1:
      if (*(float *)(pbVar5 + 0x48) < 0.0) {
        fVar6 = 0.0;
      }
      else if (1.0 < *(float *)(pbVar5 + 0x48)) {
        fVar6 = 1.0;
      }
      else {
        fVar6 = *(float *)(pbVar5 + 0x48);
      }
      if (local_4 < fVar6) {
        if (*(float *)(pbVar5 + 0x48) < 0.0) {
          local_4 = 0.0;
        }
        else if (1.0 < *(float *)(pbVar5 + 0x48)) {
          local_4 = 1.0;
        }
        else {
          local_4 = *(float *)(pbVar5 + 0x48);
        }
      }
      fVar6 = local_4 * 63.0;
      *(float *)(pbVar5 + 0x44) = fVar6;
      if ((*pbVar5 & 1) == 0) {
        if (g_nRdroid_curZBufferMethod == 1) {
          rdAFRaster_SetupNGonFS(pfVar2,(int)pbVar9,fVar6);
        }
      }
      else {
        (**(code **)(pbVar5 + 0x18))(pfVar2,pbVar9,fVar6);
      }
      break;
    case 0x2:
      fVar6 = *(float *)(pbVar5 + 0x48) + *(float *)(pbVar5 + 0x44);
      if (fVar6 < 0.0) {
        fVar3 = 0.0;
      }
      else {
        fVar3 = fVar6;
        if (1.0 < fVar6) {
          fVar3 = 1.0;
        }
      }
      if (local_4 < fVar3) {
        if (fVar6 < 0.0) {
          local_4 = 0.0;
        }
        else {
          local_4 = fVar6;
          if (1.0 < fVar6) {
            local_4 = 1.0;
          }
        }
      }
      fVar6 = local_4 * 63.0;
      *(float *)(pbVar5 + 0x44) = fVar6;
      if ((*pbVar5 & 1) == 0) {
        if (g_nRdroid_curZBufferMethod == 1) {
          rdAFRaster_SetupNGonFS(pfVar2,(int)pbVar9,fVar6);
        }
      }
      else {
        (**(code **)(pbVar5 + 0x18))(pfVar2,pbVar9,fVar6);
      }
      break;
    case 0x3:
      uVar8 = 0;
      if (*(int *)(pbVar5 + 0x1c) != 0) {
        do {
          fVar6 = *(float *)(*(int *)(pbVar5 + 0x28) + uVar8 * 4) + *(float *)(pbVar5 + 0x48);
          iVar10 = uVar8 * 4;
          if (fVar6 < 0.0) {
            fVar3 = 0.0;
          }
          else {
            fVar3 = fVar6;
            if (1.0 < fVar6) {
              fVar3 = 1.0;
            }
          }
          fVar4 = local_4;
          if (local_4 < fVar3) {
            if (fVar6 < 0.0) {
              fVar4 = 0.0;
            }
            else {
              fVar4 = fVar6;
              if (1.0 < fVar6) {
                fVar4 = 1.0;
              }
            }
          }
          uVar8 = uVar8 + 1;
          *(float *)(*(int *)(pbVar5 + 0x28) + iVar10) = fVar4 * 63.0;
        } while (uVar8 < *(uint *)(pbVar5 + 0x1c));
      }
      if ((*pbVar5 & 1) == 0) {
        if (g_nRdroid_curZBufferMethod == 1) {
          rdAFRaster_SetupNGonGS(pfVar2,(int)pbVar9);
        }
      }
      else {
        (**(code **)(pbVar5 + 0x18))(pfVar2,pbVar9,0);
      }
    }
  }
  else if (fVar6 == 5.60519e-45) {
    if ((**(byte **)(pbVar9 + 0x1c) & 1) == 0) {
      if (iVar10 == 0) {
        switch((int)(param_1)) {
        case 0x0:
          if ((*pbVar5 & 1) == 0) {
            if (g_nRdroid_curZBufferMethod == 1) {
              rdAFRaster_SetupNGonLAT((int *)pfVar2,(int)pbVar9);
            }
          }
          else {
            (**(code **)(pbVar5 + 0x18))(pfVar2,pbVar9,0);
          }
          break;
        case 0x1:
          if (*(float *)(pbVar5 + 0x48) < 0.0) {
            fVar6 = 0.0;
          }
          else if (1.0 < *(float *)(pbVar5 + 0x48)) {
            fVar6 = 1.0;
          }
          else {
            fVar6 = *(float *)(pbVar5 + 0x48);
          }
          if (local_4 < fVar6) {
            if (*(float *)(pbVar5 + 0x48) < 0.0) {
              local_4 = 0.0;
            }
            else if (1.0 < *(float *)(pbVar5 + 0x48)) {
              local_4 = 1.0;
            }
            else {
              local_4 = *(float *)(pbVar5 + 0x48);
            }
          }
          fVar6 = local_4 * 63.0;
          *(float *)(pbVar5 + 0x44) = fVar6;
          if ((*pbVar5 & 1) == 0) {
            if (g_nRdroid_curZBufferMethod == 1) {
              rdAFRaster_SetupNGonFAT((int *)pfVar2,(int)pbVar9,fVar6);
            }
          }
          else {
            (**(code **)(pbVar5 + 0x18))(pfVar2,pbVar9,fVar6);
          }
          break;
        case 0x2:
          fVar6 = *(float *)(pbVar5 + 0x48) + *(float *)(pbVar5 + 0x44);
          if (fVar6 < 0.0) {
            fVar3 = 0.0;
          }
          else {
            fVar3 = fVar6;
            if (1.0 < fVar6) {
              fVar3 = 1.0;
            }
          }
          if (local_4 < fVar3) {
            if (fVar6 < 0.0) {
              local_4 = 0.0;
            }
            else {
              local_4 = fVar6;
              if (1.0 < fVar6) {
                local_4 = 1.0;
              }
            }
          }
          fVar6 = local_4 * 63.0;
          *(float *)(pbVar5 + 0x44) = fVar6;
          if ((*pbVar5 & 1) == 0) {
            if (g_nRdroid_curZBufferMethod == 1) {
              rdAFRaster_SetupNGonFAT((int *)pfVar2,(int)pbVar9,fVar6);
            }
          }
          else {
            (**(code **)(pbVar5 + 0x18))(pfVar2,pbVar9,fVar6);
          }
          break;
        case 0x3:
          uVar8 = 0;
          if (*(int *)(pbVar5 + 0x1c) != 0) {
            do {
              fVar6 = *(float *)(*(int *)(pbVar5 + 0x28) + uVar8 * 4) + *(float *)(pbVar5 + 0x48);
              iVar10 = uVar8 * 4;
              if (fVar6 < 0.0) {
                fVar3 = 0.0;
              }
              else {
                fVar3 = fVar6;
                if (1.0 < fVar6) {
                  fVar3 = 1.0;
                }
              }
              fVar4 = local_4;
              if (local_4 < fVar3) {
                if (fVar6 < 0.0) {
                  fVar4 = 0.0;
                }
                else {
                  fVar4 = fVar6;
                  if (1.0 < fVar6) {
                    fVar4 = 1.0;
                  }
                }
              }
              uVar8 = uVar8 + 1;
              *(float *)(*(int *)(pbVar5 + 0x28) + iVar10) = fVar4 * 63.0;
            } while (uVar8 < *(uint *)(pbVar5 + 0x1c));
          }
          if ((*pbVar5 & 1) == 0) {
            if (g_nRdroid_curZBufferMethod == 1) {
              rdAFRaster_SetupNGonGAT((int *)pfVar2,(int)pbVar9);
            }
          }
          else {
            (**(code **)(pbVar5 + 0x18))(pfVar2,pbVar9,0);
          }
        }
      }
      else if ((0 < iVar10) && (iVar10 < 3)) {
        switch((int)(param_1)) {
        case 0x0:
          if ((*pbVar5 & 1) == 0) {
            if (g_nRdroid_curZBufferMethod == 1) {
              rdAFRaster_SetupNGonLIT((int *)pfVar2,(int)pbVar9);
            }
          }
          else {
            (**(code **)(pbVar5 + 0x18))(pfVar2,pbVar9,0);
          }
          break;
        case 0x1:
          if (*(float *)(pbVar5 + 0x48) < 0.0) {
            fVar6 = 0.0;
          }
          else if (1.0 < *(float *)(pbVar5 + 0x48)) {
            fVar6 = 1.0;
          }
          else {
            fVar6 = *(float *)(pbVar5 + 0x48);
          }
          if (local_4 < fVar6) {
            if (*(float *)(pbVar5 + 0x48) < 0.0) {
              local_4 = 0.0;
            }
            else if (1.0 < *(float *)(pbVar5 + 0x48)) {
              local_4 = 1.0;
            }
            else {
              local_4 = *(float *)(pbVar5 + 0x48);
            }
          }
          fVar6 = local_4 * 63.0;
          *(float *)(pbVar5 + 0x44) = fVar6;
          if ((*pbVar5 & 1) == 0) {
            if (g_nRdroid_curZBufferMethod == 1) {
              rdAFRaster_SetupNGonFIT((int *)pfVar2,(int)pbVar9,fVar6);
            }
          }
          else {
            (**(code **)(pbVar5 + 0x18))(pfVar2,pbVar9,fVar6);
          }
          break;
        case 0x2:
          fVar6 = *(float *)(pbVar5 + 0x48) + *(float *)(pbVar5 + 0x44);
          if (fVar6 < 0.0) {
            fVar3 = 0.0;
          }
          else {
            fVar3 = fVar6;
            if (1.0 < fVar6) {
              fVar3 = 1.0;
            }
          }
          if (local_4 < fVar3) {
            if (fVar6 < 0.0) {
              local_4 = 0.0;
            }
            else {
              local_4 = fVar6;
              if (1.0 < fVar6) {
                local_4 = 1.0;
              }
            }
          }
          fVar6 = local_4 * 63.0;
          *(float *)(pbVar5 + 0x44) = fVar6;
          if ((*pbVar5 & 1) == 0) {
            if (g_nRdroid_curZBufferMethod == 1) {
              rdAFRaster_SetupNGonFIT((int *)pfVar2,(int)pbVar9,fVar6);
            }
          }
          else {
            (**(code **)(pbVar5 + 0x18))(pfVar2,pbVar9,fVar6);
          }
          break;
        case 0x3:
          uVar8 = 0;
          if (*(int *)(pbVar5 + 0x1c) != 0) {
            do {
              fVar6 = *(float *)(*(int *)(pbVar5 + 0x28) + uVar8 * 4) + *(float *)(pbVar5 + 0x48);
              iVar10 = uVar8 * 4;
              if (fVar6 < 0.0) {
                fVar3 = 0.0;
              }
              else {
                fVar3 = fVar6;
                if (1.0 < fVar6) {
                  fVar3 = 1.0;
                }
              }
              fVar4 = local_4;
              if (local_4 < fVar3) {
                if (fVar6 < 0.0) {
                  fVar4 = 0.0;
                }
                else {
                  fVar4 = fVar6;
                  if (1.0 < fVar6) {
                    fVar4 = 1.0;
                  }
                }
              }
              uVar8 = uVar8 + 1;
              *(float *)(*(int *)(pbVar5 + 0x28) + iVar10) = fVar4 * 63.0;
            } while (uVar8 < *(uint *)(pbVar5 + 0x1c));
          }
          if ((*pbVar5 & 1) == 0) {
            if (g_nRdroid_curZBufferMethod == 1) {
              rdAFRaster_SetupNGonGIT((int *)pfVar2,(int)pbVar9);
            }
          }
          else {
            (**(code **)(pbVar5 + 0x18))(pfVar2,pbVar9,0);
          }
        }
      }
    }
    else if (iVar10 == 0) {
      switch((int)(param_1)) {
      case 0x0:
        if ((*pbVar5 & 1) == 0) {
          if (g_nRdroid_curZBufferMethod == 1) {
            rdAFRaster_SetupNGonMLAT((int *)pfVar2,(int)pbVar9);
          }
        }
        else {
          (**(code **)(pbVar5 + 0x18))(pfVar2,pbVar9,0);
        }
        break;
      case 0x1:
        if (*(float *)(pbVar5 + 0x48) < 0.0) {
          fVar6 = 0.0;
        }
        else if (1.0 < *(float *)(pbVar5 + 0x48)) {
          fVar6 = 1.0;
        }
        else {
          fVar6 = *(float *)(pbVar5 + 0x48);
        }
        if (local_4 < fVar6) {
          if (*(float *)(pbVar5 + 0x48) < 0.0) {
            local_4 = 0.0;
          }
          else if (1.0 < *(float *)(pbVar5 + 0x48)) {
            local_4 = 1.0;
          }
          else {
            local_4 = *(float *)(pbVar5 + 0x48);
          }
        }
        fVar6 = local_4 * 63.0;
        *(float *)(pbVar5 + 0x44) = fVar6;
        if ((*pbVar5 & 1) == 0) {
          if (g_nRdroid_curZBufferMethod == 1) {
            rdAFRaster_SetupNGonMFAT((int *)pfVar2,(int)pbVar9,fVar6);
          }
        }
        else {
          (**(code **)(pbVar5 + 0x18))(pfVar2,pbVar9,fVar6);
        }
        break;
      case 0x2:
        fVar6 = *(float *)(pbVar5 + 0x48) + *(float *)(pbVar5 + 0x44);
        if (fVar6 < 0.0) {
          fVar3 = 0.0;
        }
        else {
          fVar3 = fVar6;
          if (1.0 < fVar6) {
            fVar3 = 1.0;
          }
        }
        if (local_4 < fVar3) {
          if (fVar6 < 0.0) {
            local_4 = 0.0;
          }
          else {
            local_4 = fVar6;
            if (1.0 < fVar6) {
              local_4 = 1.0;
            }
          }
        }
        fVar6 = local_4 * 63.0;
        *(float *)(pbVar5 + 0x44) = fVar6;
        if ((*pbVar5 & 1) == 0) {
          if (g_nRdroid_curZBufferMethod == 1) {
            rdAFRaster_SetupNGonMFAT((int *)pfVar2,(int)pbVar9,fVar6);
          }
        }
        else {
          (**(code **)(pbVar5 + 0x18))(pfVar2,pbVar9,fVar6);
        }
        break;
      case 0x3:
        uVar8 = 0;
        if (*(int *)(pbVar5 + 0x1c) != 0) {
          do {
            fVar6 = *(float *)(*(int *)(pbVar5 + 0x28) + uVar8 * 4) + *(float *)(pbVar5 + 0x48);
            iVar10 = uVar8 * 4;
            if (fVar6 < 0.0) {
              fVar3 = 0.0;
            }
            else {
              fVar3 = fVar6;
              if (1.0 < fVar6) {
                fVar3 = 1.0;
              }
            }
            fVar4 = local_4;
            if (local_4 < fVar3) {
              if (fVar6 < 0.0) {
                fVar4 = 0.0;
              }
              else {
                fVar4 = fVar6;
                if (1.0 < fVar6) {
                  fVar4 = 1.0;
                }
              }
            }
            uVar8 = uVar8 + 1;
            *(float *)(*(int *)(pbVar5 + 0x28) + iVar10) = fVar4 * 63.0;
          } while (uVar8 < *(uint *)(pbVar5 + 0x1c));
        }
        if ((*pbVar5 & 1) == 0) {
          if (g_nRdroid_curZBufferMethod == 1) {
            rdAFRaster_SetupNGonMGAT((int *)pfVar2,(int)pbVar9);
          }
        }
        else {
          (**(code **)(pbVar5 + 0x18))(pfVar2,pbVar9,0);
        }
      }
    }
    else if ((0 < iVar10) && (iVar10 < 3)) {
      switch((int)(param_1)) {
      case 0x0:
        if ((*pbVar5 & 1) == 0) {
          if (g_nRdroid_curZBufferMethod == 1) {
            rdAFRaster_SetupNGonMLIT((int *)pfVar2,(int)pbVar9);
          }
        }
        else {
          (**(code **)(pbVar5 + 0x18))(pfVar2,pbVar9,0);
        }
        break;
      case 0x1:
        if (*(float *)(pbVar5 + 0x48) < 0.0) {
          fVar6 = 0.0;
        }
        else if (1.0 < *(float *)(pbVar5 + 0x48)) {
          fVar6 = 1.0;
        }
        else {
          fVar6 = *(float *)(pbVar5 + 0x48);
        }
        if (local_4 < fVar6) {
          if (*(float *)(pbVar5 + 0x48) < 0.0) {
            local_4 = 0.0;
          }
          else if (1.0 < *(float *)(pbVar5 + 0x48)) {
            local_4 = 1.0;
          }
          else {
            local_4 = *(float *)(pbVar5 + 0x48);
          }
        }
        fVar6 = local_4 * 63.0;
        *(float *)(pbVar5 + 0x44) = fVar6;
        if ((*pbVar5 & 1) == 0) {
          if (g_nRdroid_curZBufferMethod == 1) {
            rdAFRaster_SetupNGonMFIT((int *)pfVar2,(int)pbVar9,fVar6);
          }
        }
        else {
          (**(code **)(pbVar5 + 0x18))(pfVar2,pbVar9,fVar6);
        }
        break;
      case 0x2:
        fVar6 = *(float *)(pbVar5 + 0x48) + *(float *)(pbVar5 + 0x44);
        if (fVar6 < 0.0) {
          fVar3 = 0.0;
        }
        else {
          fVar3 = fVar6;
          if (1.0 < fVar6) {
            fVar3 = 1.0;
          }
        }
        if (local_4 < fVar3) {
          if (fVar6 < 0.0) {
            local_4 = 0.0;
          }
          else {
            local_4 = fVar6;
            if (1.0 < fVar6) {
              local_4 = 1.0;
            }
          }
        }
        fVar6 = local_4 * 63.0;
        *(float *)(pbVar5 + 0x44) = fVar6;
        if ((*pbVar5 & 1) == 0) {
          if (g_nRdroid_curZBufferMethod == 1) {
            rdAFRaster_SetupNGonMFIT((int *)pfVar2,(int)pbVar9,fVar6);
          }
        }
        else {
          (**(code **)(pbVar5 + 0x18))(pfVar2,pbVar9,fVar6);
        }
        break;
      case 0x3:
        uVar8 = 0;
        if (*(int *)(pbVar5 + 0x1c) != 0) {
          do {
            fVar6 = *(float *)(*(int *)(pbVar5 + 0x28) + uVar8 * 4) + *(float *)(pbVar5 + 0x48);
            iVar10 = uVar8 * 4;
            if (fVar6 < 0.0) {
              fVar3 = 0.0;
            }
            else {
              fVar3 = fVar6;
              if (1.0 < fVar6) {
                fVar3 = 1.0;
              }
            }
            fVar4 = local_4;
            if (local_4 < fVar3) {
              if (fVar6 < 0.0) {
                fVar4 = 0.0;
              }
              else {
                fVar4 = fVar6;
                if (1.0 < fVar6) {
                  fVar4 = 1.0;
                }
              }
            }
            uVar8 = uVar8 + 1;
            *(float *)(*(int *)(pbVar5 + 0x28) + iVar10) = fVar4 * 63.0;
          } while (uVar8 < *(uint *)(pbVar5 + 0x1c));
        }
        if ((*pbVar5 & 1) == 0) {
          if (g_nRdroid_curZBufferMethod == 1) {
            rdAFRaster_SetupNGonMGIT((int *)pfVar2,(int)pbVar9);
          }
        }
        else {
          (**(code **)(pbVar5 + 0x18))(pfVar2,pbVar9,0);
        }
      }
    }
  }
  g_dwRdActive_drawnFaces = g_dwRdActive_drawnFaces + 1;
  g_dwNumActiveFaces = g_dwNumActiveFaces + 1;
  return 1;
}
#undef local_4

#endif


/* ---- 0x00451950  rdCanvas_DrawLine ---- */
/* Bresenham line, 8 and 16 bpp, with a 32-bit stipple pattern */

void __cdecl rdCanvas_DrawLine(void *canvas,int x0,int y0,int x1,int y1,ushort color,uint pattern)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar4 = y0;
  iVar3 = x0;
  iVar2 = *(int *)((int)canvas + 4);
  local_10 = 0x80000000;
  if (*(int *)(iVar2 + 0x24) == 8) {
    iVar9 = x1 - x0;
    iVar7 = y1 - y0;
    y0 = x0;
    x0 = iVar4;
    iVar5 = ((iVar9 < 1) - 1 & 2) - 1;
    iVar6 = ((iVar7 < 1) - 1 & 2) - 1;
    if (iVar5 < 0) {
      iVar7 = -iVar7;
    }
    if (0 < iVar6) {
      iVar9 = -iVar9;
    }
    if ((pattern & 0x80000000) != 0) {
      *(undefined1 *)(*(int *)(iVar2 + 0x18) * iVar4 + *(int *)(iVar2 + 0x5c) + iVar3) =
           (undefined1)color;
    }
    uVar8 = 0;
    while ((y0 != x1 || (x0 != y1))) {
      local_10 = local_10 >> 1;
      if (local_10 == 0) {
        local_10 = 0x80000000;
      }
      uVar1 = uVar8 + iVar7;
      uVar8 = uVar8 + iVar9;
      if ((int)((uVar1 ^ (int)uVar1 >> 0x1f) - ((int)uVar1 >> 0x1f)) <
          (int)((uVar8 ^ (int)uVar8 >> 0x1f) - ((int)uVar8 >> 0x1f))) {
        y0 = y0 + iVar5;
        uVar8 = uVar1;
      }
      else {
        x0 = x0 + iVar6;
      }
      if ((pattern & local_10) != 0) {
        *(undefined1 *)
         (*(int *)(*(int *)((int)canvas + 4) + 0x18) * x0 +
          *(int *)(*(int *)((int)canvas + 4) + 0x5c) + y0) = (undefined1)color;
      }
    }
  }
  else {
    iVar9 = x1 - x0;
    iVar7 = y1 - y0;
    y0 = x0;
    x0 = iVar4;
    iVar5 = ((iVar9 < 1) - 1 & 2) - 1;
    iVar6 = ((iVar7 < 1) - 1 & 2) - 1;
    if (iVar5 < 0) {
      iVar7 = -iVar7;
    }
    if (0 < iVar6) {
      iVar9 = -iVar9;
    }
    if ((pattern & 0x80000000) != 0) {
      *(ushort *)(*(int *)(iVar2 + 0x5c) + (*(int *)(iVar2 + 0x1c) * iVar4 + iVar3) * 2) = color;
    }
    uVar8 = 0;
    while ((y0 != x1 || (x0 != y1))) {
      local_10 = local_10 >> 1;
      if (local_10 == 0) {
        local_10 = 0x80000000;
      }
      uVar1 = uVar8 + iVar7;
      uVar8 = uVar8 + iVar9;
      if ((int)((uVar1 ^ (int)uVar1 >> 0x1f) - ((int)uVar1 >> 0x1f)) <
          (int)((uVar8 ^ (int)uVar8 >> 0x1f) - ((int)uVar8 >> 0x1f))) {
        y0 = y0 + iVar5;
        uVar8 = uVar1;
      }
      else {
        x0 = x0 + iVar6;
      }
      if ((pattern & local_10) != 0) {
        *(ushort *)
         (*(int *)(*(int *)((int)canvas + 4) + 0x5c) +
         (*(int *)(*(int *)((int)canvas + 4) + 0x1c) * x0 + y0) * 2) = color;
      }
    }
  }
  return;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x00451dd0  rdCanvas_DrawPoint ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Clips a point with radius against the canvas rect and draws it */

void __cdecl
rdCanvas_DrawPoint(void *param_1,int param_2,int param_3,uint param_4,float param_5,int param_6,
                  int param_7)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  int y1;
  int iVar2;
  int x2;
  int y2;
  longlong lVar3;
  longlong lVar4;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  lVar3 = FTOL((float10)PUN(float,param_4) - (float10)-0.5);
  iVar2 = (int)lVar3;
  if ((((*(int *)((int)param_1 + 0x18) <= iVar2 + param_2) &&
       (param_2 - iVar2 <= *(int *)((int)param_1 + 0x20))) &&
      (*(int *)((int)param_1 + 0x1c) <= iVar2 + param_3)) &&
     (param_3 - iVar2 <= *(int *)((int)param_1 + 0x24))) {
    stdMath_SinCos(0.0,(float *)&local_4,(float *)&local_8);
    lVar3 = FTOL((float10)PUN(float,local_8) * (float10)PUN(float,param_4) - (float10)-0.5);
    lVar4 = FTOL((float10)PUN(float,local_4) * (float10)PUN(float,param_4) - (float10)-0.5);
    iVar2 = (int)lVar3 + param_2;
    y1 = (int)lVar4 + param_3;
    for (fVar1 = param_5; fVar1 <= 360.0; fVar1 = fVar1 + param_5) {
      stdMath_SinCos(fVar1,(float *)&local_4,(float *)&local_8);
      lVar3 = FTOL((float10)PUN(float,local_8) * (float10)PUN(float,param_4) - (float10)-0.5);
      x2 = (int)lVar3 + param_2;
      lVar3 = FTOL((float10)PUN(float,local_4) * (float10)PUN(float,param_4) - (float10)-0.5);
      y2 = (int)lVar3 + param_3;
      rdPrimit2_DrawLine(param_1,iVar2,y1,x2,y2,param_6,param_7);
      iVar2 = x2;
      y1 = y2;
    }
  }
  return;
}
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x004c04f0  rdCanvas_New ---- */
/* Rdcanvas.c: allocates a 0x28-byte canvas and initialises it */

uint * __cdecl
rdCanvas_New(uint param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6,
            uint param_7,uint param_8)

{
  uint *canvas;
  
  canvas = (uint *)(*g_pRdroid_HS->pAlloc)
                             (0x28,s_C__grimjedi_Libs_RDroid_Engine_R_004f0edc,DAT_004f0ed8 + 4);
  if (canvas == (uint *)0x0) {
    return (uint *)0x0;
  }
  rdCanvas_NewEntry(canvas,param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return canvas;
}

/* ---- 0x004c0550  rdCanvas_NewEntry ---- */
/* flags bit 0: explicit clip rect, otherwise the whole surface Original name rdCanvas_NewEntry (the
   remaster's GrimFandango (Linux): same parameters (canvas, flags, surface, z surface, the
   rectangle, extra) and body); was rdCanvas_Init. */

int __cdecl
rdCanvas_NewEntry(uint *canvas,uint flags,uint surface,uint zSurface,uint x0,uint y0,uint x1,uint y1
                 ,uint extra)

{
  canvas[4] = zSurface;
  *canvas = flags;
  canvas[1] = surface;
  canvas[5] = extra;
  if ((flags & 1) == 0) {
    canvas[6] = 0;
    canvas[7] = 0;
    canvas[8] = *(int *)(surface + 0xc) - 1;
    canvas[9] = *(int *)(surface + 0x10) - 1;
  }
  else {
    canvas[6] = x0;
    canvas[7] = y0;
    canvas[8] = x1;
    canvas[9] = y1;
  }
  canvas[2] = PUN(uint,(float)((float)(int)canvas[6] + (float)(int)((canvas[8] - canvas[6]) + 1) * 0.5));
  canvas[3] = PUN(uint,(float)((float)(int)canvas[7] + (float)(int)((canvas[9] - canvas[7]) + 1) * 0.5));
  return 1;
}

/* ---- 0x004c0610  rdCanvas_Free ---- */
void __cdecl rdCanvas_Free(int param_1)

{
  if (param_1 != 0) {
    Mem_DumpLog();
    (*g_pRdroid_HS->pFree)(param_1);
  }
  return;
}
