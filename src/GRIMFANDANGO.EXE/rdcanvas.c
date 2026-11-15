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
  
  iVar4 = g_pRdCamera_CurCamera->pCanvas->nY0;
  _DAT_004f6ef8 = 0xffff0000;
  uVar1 = (g_pRdCamera_CurCamera->pCanvas->nY1 - iVar4) + 1;
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
              fVar7 = (float)iVar10 * 1.5258789e-05f;
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
            piVar2[0x67] = (int)ROUND(fVar7 * 65536.0f);
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
              fVar7 = (float)(piVar13[10] - *(int *)(piVar17[0x7b] + 0x28)) * 1.5258789e-05f *
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
                fVar7 = (float)iVar10 * 1.5258789e-05f;
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
                    fVar7 = (float)(piVar13[10] - *(int *)(piVar15[0x7b] + 0x28)) * 1.5258789e-05f *
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
  ProcEntry *face;
  undefined *puVar8;
  uint uVar9;
  uint *puVar10;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar9 = 0;
  face = g_bRdCache_aProcFaces;
  if (g_dwRdCache_numProcFaces != 0) {
    do {
      rdActive_AddActiveFace((byte *)face);
      face = face + 1;
      uVar9 = uVar9 + 1;
    } while (uVar9 < g_dwRdCache_numProcFaces);
  }
  puVar10 = &UINT_00565f38;
  puVar8 = &DAT_0050df38;
  local_4 = 0;
  if (g_dwNumActiveFaces != 0) {
    do {
      uVar9 = *puVar10;
      uVar4 = *(uint *)(uVar9 + 0x1c);
      uVar7 = 0;
      if (uVar4 != 0) {
        do {
          uVar1 = uVar7 + 1;
          uVar5 = ~-(uint)(uVar4 - 1 < uVar1) & uVar1;
          uVar4 = uVar5;
          if (*(int *)(*puVar10 + 0x50) == 0) {
            uVar4 = uVar7;
            uVar7 = uVar5;
          }
          iVar6 = (*(code *)puVar10[0x7a])(puVar8,puVar10,uVar4,uVar7);
          if (iVar6 != 0) {
            *(uint **)(puVar8 + 4) = puVar10;
            iVar6 = *(int *)(&g_apNewActiveEdges + *(int *)(puVar8 + 8) * 4);
            if ((iVar6 == 0) || (*(int *)(puVar8 + 0x28) <= *(int *)(iVar6 + 0x28))) {
              *(int *)(puVar8 + 0x50) = iVar6;
              *(undefined **)(&g_apNewActiveEdges + *(int *)(puVar8 + 8) * 4) = puVar8;
            }
            else {
              for (iVar3 = *(int *)(iVar6 + 0x50);
                  (iVar3 != 0 && (*(int *)(iVar3 + 0x28) < *(int *)(puVar8 + 0x28)));
                  iVar3 = *(int *)(iVar3 + 0x50)) {
                iVar6 = iVar3;
              }
              *(undefined4 *)(puVar8 + 0x50) = *(undefined4 *)(iVar6 + 0x50);
              *(undefined **)(iVar6 + 0x50) = puVar8;
            }
            uVar7 = *(uint *)(puVar8 + 8);
            uVar4 = *(int *)(puVar8 + 0xc) + -1 + uVar7;
            uVar2 = *(undefined4 *)(&g_apRemoveActiveEdges + uVar4 * 4);
            *(undefined **)(&g_apRemoveActiveEdges + uVar4 * 4) = puVar8;
            *(undefined4 *)(puVar8 + 0x54) = uVar2;
            if (uVar7 < g_dwYMinEdge) {
              g_dwYMinEdge = uVar7;
            }
            if (g_dwYMaxEdge < uVar4) {
              g_dwYMaxEdge = uVar4;
            }
            puVar8 = puVar8 + 0x58;
            g_dwNumActiveEdges = g_dwNumActiveEdges + 1;
          }
          uVar4 = *(uint *)(uVar9 + 0x1c);
          uVar7 = uVar1;
        } while (uVar1 < uVar4);
      }
      puVar10 = puVar10 + 0x81;
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

uint __cdecl rdActive_AddActiveFace(byte *face)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  float *rec;
  float fVar2;
  float fVar3;
  byte *pbVar4;
  float fVar5;
  int iVar6;
  uint uVar7;
  byte *mat;
  int iVar8;
  int iVar9;
  #define local_4 (*(float *)(_frame + (0x20 - 0x4)))
  
  pbVar4 = face;
  uVar7 = g_dwNumActiveFaces;
  if (0x3ff < g_dwNumActiveFaces) {
    return 0;
  }
  local_4 = *(float *)(face + 8);
  if (g_nRdroid_curGeometryMode <= PUN(int,(float)local_4)) {
    local_4 = PUN(float,g_nRdroid_curGeometryMode);
  }
  face = *(byte **)(face + 0xc);
  if (g_nRdroid_curLightingMode <= (int)face) {
    face = (byte *)g_nRdroid_curLightingMode;
  }
  iVar8 = *(int *)(pbVar4 + 0x10);
  if (g_nRdroid_curTextureMode <= *(int *)(pbVar4 + 0x10)) {
    iVar8 = g_nRdroid_curTextureMode;
  }
  if (local_4 == 0.0f) {
    return 0;
  }
  iVar1 = g_dwNumActiveFaces * 0x204;
  rec = (float *)(&UINT_00565f38 + g_dwNumActiveFaces * 0x81);
  *rec = PUN(float,pbVar4);
  (&UINT_005660f0)[uVar7 * 0x81] = 0;
  (&UINT_005660f4)[uVar7 * 0x81] = 0;
  *(undefined4 *)(&DAT_00566124 + iVar1) = 0;
  *(undefined4 *)(&DAT_00566128 + iVar1) = 0;
  *(undefined4 *)(&DAT_00566130 + iVar1) = 0;
  iVar1 = *(int *)(pbVar4 + 0x38);
  fVar5 = local_4;
  if (iVar1 == 0) {
    mat = (byte *)0x0;
    goto LAB_0040585d;
  }
  iVar6 = *(int *)(pbVar4 + 0x3c);
  if (iVar6 == -1) {
    iVar6 = *(int *)(iVar1 + 100);
    if (iVar6 < 0) {
LAB_0040583c:
      iVar6 = 0;
    }
    else {
      iVar9 = *(int *)(iVar1 + 0x60) + -1;
      if (iVar9 < iVar6) {
        iVar6 = iVar9;
      }
    }
  }
  else {
    if (iVar6 < 0) goto LAB_0040583c;
    iVar9 = *(int *)(iVar1 + 0x60) + -1;
    if (iVar9 < iVar6) {
      iVar6 = iVar9;
    }
  }
  mat = *(byte **)(iVar1 + 0x68 + iVar6 * 4);
  if ((local_4 == 5.60519e-45f) && ((*mat & 8) == 0)) {
    fVar5 = 4.2039e-45f;
  }
LAB_0040585d:
  if (((byte)g_dwRdroid_curRenderOptions & 2) == 0) {
    local_4 = 0.0f;
  }
  else {
    local_4 = *(float *)(pbVar4 + 0x40);
  }
  if (fVar5 == 2.8026e-45f) {
    if ((-1 < (int)face) && ((int)face < 5)) {
      if ((*pbVar4 & 1) == 0) {
        if (g_nRdroid_curZBufferMethod == 1) {
          rdAFRaster_SetupNGonLW(rec,(int)mat);
        }
      }
      else {
        (**(code **)(pbVar4 + 0x18))(rec,mat,0);
      }
    }
  }
  else if (fVar5 == 4.2039e-45f) {
    switch((int)(face)) {
    case 0x0:
      if ((*pbVar4 & 1) == 0) {
        if (g_nRdroid_curZBufferMethod == 1) {
          rdAFRaster_SetupNGonLS(rec,(int)mat);
        }
      }
      else {
        (**(code **)(pbVar4 + 0x18))(rec,mat,0);
      }
      break;
    case 0x1:
      if (*(float *)(pbVar4 + 0x48) < 0.0f) {
        fVar5 = 0.0f;
      }
      else if (1.0f < *(float *)(pbVar4 + 0x48)) {
        fVar5 = 1.0f;
      }
      else {
        fVar5 = *(float *)(pbVar4 + 0x48);
      }
      if (local_4 < fVar5) {
        if (*(float *)(pbVar4 + 0x48) < 0.0f) {
          local_4 = 0.0f;
        }
        else if (1.0f < *(float *)(pbVar4 + 0x48)) {
          local_4 = 1.0f;
        }
        else {
          local_4 = *(float *)(pbVar4 + 0x48);
        }
      }
      fVar5 = local_4 * 63.0f;
      *(float *)(pbVar4 + 0x44) = fVar5;
      if ((*pbVar4 & 1) == 0) {
        if (g_nRdroid_curZBufferMethod == 1) {
          rdAFRaster_SetupNGonFS(rec,(int)mat,fVar5);
        }
      }
      else {
        (**(code **)(pbVar4 + 0x18))(rec,mat,fVar5);
      }
      break;
    case 0x2:
      fVar5 = *(float *)(pbVar4 + 0x48) + *(float *)(pbVar4 + 0x44);
      if (fVar5 < 0.0f) {
        fVar2 = 0.0f;
      }
      else {
        fVar2 = fVar5;
        if (1.0f < fVar5) {
          fVar2 = 1.0f;
        }
      }
      if (local_4 < fVar2) {
        if (fVar5 < 0.0f) {
          local_4 = 0.0f;
        }
        else {
          local_4 = fVar5;
          if (1.0f < fVar5) {
            local_4 = 1.0f;
          }
        }
      }
      fVar5 = local_4 * 63.0f;
      *(float *)(pbVar4 + 0x44) = fVar5;
      if ((*pbVar4 & 1) == 0) {
        if (g_nRdroid_curZBufferMethod == 1) {
          rdAFRaster_SetupNGonFS(rec,(int)mat,fVar5);
        }
      }
      else {
        (**(code **)(pbVar4 + 0x18))(rec,mat,fVar5);
      }
      break;
    case 0x3:
      uVar7 = 0;
      if (*(int *)(pbVar4 + 0x1c) != 0) {
        do {
          fVar5 = *(float *)(*(int *)(pbVar4 + 0x28) + uVar7 * 4) + *(float *)(pbVar4 + 0x48);
          iVar8 = uVar7 * 4;
          if (fVar5 < 0.0f) {
            fVar2 = 0.0f;
          }
          else {
            fVar2 = fVar5;
            if (1.0f < fVar5) {
              fVar2 = 1.0f;
            }
          }
          fVar3 = local_4;
          if (local_4 < fVar2) {
            if (fVar5 < 0.0f) {
              fVar3 = 0.0f;
            }
            else {
              fVar3 = fVar5;
              if (1.0f < fVar5) {
                fVar3 = 1.0f;
              }
            }
          }
          uVar7 = uVar7 + 1;
          *(float *)(*(int *)(pbVar4 + 0x28) + iVar8) = fVar3 * 63.0f;
        } while (uVar7 < *(uint *)(pbVar4 + 0x1c));
      }
      if ((*pbVar4 & 1) == 0) {
        if (g_nRdroid_curZBufferMethod == 1) {
          rdAFRaster_SetupNGonGS(rec,(int)mat);
        }
      }
      else {
        (**(code **)(pbVar4 + 0x18))(rec,mat,0);
      }
    }
  }
  else if (fVar5 == 5.60519e-45f) {
    if ((**(byte **)(mat + 0x1c) & 1) == 0) {
      if (iVar8 == 0) {
        switch((int)(face)) {
        case 0x0:
          if ((*pbVar4 & 1) == 0) {
            if (g_nRdroid_curZBufferMethod == 1) {
              rdAFRaster_SetupNGonLAT((int *)rec,(int)mat);
            }
          }
          else {
            (**(code **)(pbVar4 + 0x18))(rec,mat,0);
          }
          break;
        case 0x1:
          if (*(float *)(pbVar4 + 0x48) < 0.0f) {
            fVar5 = 0.0f;
          }
          else if (1.0f < *(float *)(pbVar4 + 0x48)) {
            fVar5 = 1.0f;
          }
          else {
            fVar5 = *(float *)(pbVar4 + 0x48);
          }
          if (local_4 < fVar5) {
            if (*(float *)(pbVar4 + 0x48) < 0.0f) {
              local_4 = 0.0f;
            }
            else if (1.0f < *(float *)(pbVar4 + 0x48)) {
              local_4 = 1.0f;
            }
            else {
              local_4 = *(float *)(pbVar4 + 0x48);
            }
          }
          fVar5 = local_4 * 63.0f;
          *(float *)(pbVar4 + 0x44) = fVar5;
          if ((*pbVar4 & 1) == 0) {
            if (g_nRdroid_curZBufferMethod == 1) {
              rdAFRaster_SetupNGonFAT((int *)rec,(int)mat,fVar5);
            }
          }
          else {
            (**(code **)(pbVar4 + 0x18))(rec,mat,fVar5);
          }
          break;
        case 0x2:
          fVar5 = *(float *)(pbVar4 + 0x48) + *(float *)(pbVar4 + 0x44);
          if (fVar5 < 0.0f) {
            fVar2 = 0.0f;
          }
          else {
            fVar2 = fVar5;
            if (1.0f < fVar5) {
              fVar2 = 1.0f;
            }
          }
          if (local_4 < fVar2) {
            if (fVar5 < 0.0f) {
              local_4 = 0.0f;
            }
            else {
              local_4 = fVar5;
              if (1.0f < fVar5) {
                local_4 = 1.0f;
              }
            }
          }
          fVar5 = local_4 * 63.0f;
          *(float *)(pbVar4 + 0x44) = fVar5;
          if ((*pbVar4 & 1) == 0) {
            if (g_nRdroid_curZBufferMethod == 1) {
              rdAFRaster_SetupNGonFAT((int *)rec,(int)mat,fVar5);
            }
          }
          else {
            (**(code **)(pbVar4 + 0x18))(rec,mat,fVar5);
          }
          break;
        case 0x3:
          uVar7 = 0;
          if (*(int *)(pbVar4 + 0x1c) != 0) {
            do {
              fVar5 = *(float *)(*(int *)(pbVar4 + 0x28) + uVar7 * 4) + *(float *)(pbVar4 + 0x48);
              iVar8 = uVar7 * 4;
              if (fVar5 < 0.0f) {
                fVar2 = 0.0f;
              }
              else {
                fVar2 = fVar5;
                if (1.0f < fVar5) {
                  fVar2 = 1.0f;
                }
              }
              fVar3 = local_4;
              if (local_4 < fVar2) {
                if (fVar5 < 0.0f) {
                  fVar3 = 0.0f;
                }
                else {
                  fVar3 = fVar5;
                  if (1.0f < fVar5) {
                    fVar3 = 1.0f;
                  }
                }
              }
              uVar7 = uVar7 + 1;
              *(float *)(*(int *)(pbVar4 + 0x28) + iVar8) = fVar3 * 63.0f;
            } while (uVar7 < *(uint *)(pbVar4 + 0x1c));
          }
          if ((*pbVar4 & 1) == 0) {
            if (g_nRdroid_curZBufferMethod == 1) {
              rdAFRaster_SetupNGonGAT((int *)rec,(int)mat);
            }
          }
          else {
            (**(code **)(pbVar4 + 0x18))(rec,mat,0);
          }
        }
      }
      else if ((0 < iVar8) && (iVar8 < 3)) {
        switch((int)(face)) {
        case 0x0:
          if ((*pbVar4 & 1) == 0) {
            if (g_nRdroid_curZBufferMethod == 1) {
              rdAFRaster_SetupNGonLIT((int *)rec,(int)mat);
            }
          }
          else {
            (**(code **)(pbVar4 + 0x18))(rec,mat,0);
          }
          break;
        case 0x1:
          if (*(float *)(pbVar4 + 0x48) < 0.0f) {
            fVar5 = 0.0f;
          }
          else if (1.0f < *(float *)(pbVar4 + 0x48)) {
            fVar5 = 1.0f;
          }
          else {
            fVar5 = *(float *)(pbVar4 + 0x48);
          }
          if (local_4 < fVar5) {
            if (*(float *)(pbVar4 + 0x48) < 0.0f) {
              local_4 = 0.0f;
            }
            else if (1.0f < *(float *)(pbVar4 + 0x48)) {
              local_4 = 1.0f;
            }
            else {
              local_4 = *(float *)(pbVar4 + 0x48);
            }
          }
          fVar5 = local_4 * 63.0f;
          *(float *)(pbVar4 + 0x44) = fVar5;
          if ((*pbVar4 & 1) == 0) {
            if (g_nRdroid_curZBufferMethod == 1) {
              rdAFRaster_SetupNGonFIT((int *)rec,(int)mat,fVar5);
            }
          }
          else {
            (**(code **)(pbVar4 + 0x18))(rec,mat,fVar5);
          }
          break;
        case 0x2:
          fVar5 = *(float *)(pbVar4 + 0x48) + *(float *)(pbVar4 + 0x44);
          if (fVar5 < 0.0f) {
            fVar2 = 0.0f;
          }
          else {
            fVar2 = fVar5;
            if (1.0f < fVar5) {
              fVar2 = 1.0f;
            }
          }
          if (local_4 < fVar2) {
            if (fVar5 < 0.0f) {
              local_4 = 0.0f;
            }
            else {
              local_4 = fVar5;
              if (1.0f < fVar5) {
                local_4 = 1.0f;
              }
            }
          }
          fVar5 = local_4 * 63.0f;
          *(float *)(pbVar4 + 0x44) = fVar5;
          if ((*pbVar4 & 1) == 0) {
            if (g_nRdroid_curZBufferMethod == 1) {
              rdAFRaster_SetupNGonFIT((int *)rec,(int)mat,fVar5);
            }
          }
          else {
            (**(code **)(pbVar4 + 0x18))(rec,mat,fVar5);
          }
          break;
        case 0x3:
          uVar7 = 0;
          if (*(int *)(pbVar4 + 0x1c) != 0) {
            do {
              fVar5 = *(float *)(*(int *)(pbVar4 + 0x28) + uVar7 * 4) + *(float *)(pbVar4 + 0x48);
              iVar8 = uVar7 * 4;
              if (fVar5 < 0.0f) {
                fVar2 = 0.0f;
              }
              else {
                fVar2 = fVar5;
                if (1.0f < fVar5) {
                  fVar2 = 1.0f;
                }
              }
              fVar3 = local_4;
              if (local_4 < fVar2) {
                if (fVar5 < 0.0f) {
                  fVar3 = 0.0f;
                }
                else {
                  fVar3 = fVar5;
                  if (1.0f < fVar5) {
                    fVar3 = 1.0f;
                  }
                }
              }
              uVar7 = uVar7 + 1;
              *(float *)(*(int *)(pbVar4 + 0x28) + iVar8) = fVar3 * 63.0f;
            } while (uVar7 < *(uint *)(pbVar4 + 0x1c));
          }
          if ((*pbVar4 & 1) == 0) {
            if (g_nRdroid_curZBufferMethod == 1) {
              rdAFRaster_SetupNGonGIT((int *)rec,(int)mat);
            }
          }
          else {
            (**(code **)(pbVar4 + 0x18))(rec,mat,0);
          }
        }
      }
    }
    else if (iVar8 == 0) {
      switch((int)(face)) {
      case 0x0:
        if ((*pbVar4 & 1) == 0) {
          if (g_nRdroid_curZBufferMethod == 1) {
            rdAFRaster_SetupNGonMLAT((int *)rec,(int)mat);
          }
        }
        else {
          (**(code **)(pbVar4 + 0x18))(rec,mat,0);
        }
        break;
      case 0x1:
        if (*(float *)(pbVar4 + 0x48) < 0.0f) {
          fVar5 = 0.0f;
        }
        else if (1.0f < *(float *)(pbVar4 + 0x48)) {
          fVar5 = 1.0f;
        }
        else {
          fVar5 = *(float *)(pbVar4 + 0x48);
        }
        if (local_4 < fVar5) {
          if (*(float *)(pbVar4 + 0x48) < 0.0f) {
            local_4 = 0.0f;
          }
          else if (1.0f < *(float *)(pbVar4 + 0x48)) {
            local_4 = 1.0f;
          }
          else {
            local_4 = *(float *)(pbVar4 + 0x48);
          }
        }
        fVar5 = local_4 * 63.0f;
        *(float *)(pbVar4 + 0x44) = fVar5;
        if ((*pbVar4 & 1) == 0) {
          if (g_nRdroid_curZBufferMethod == 1) {
            rdAFRaster_SetupNGonMFAT((int *)rec,(int)mat,fVar5);
          }
        }
        else {
          (**(code **)(pbVar4 + 0x18))(rec,mat,fVar5);
        }
        break;
      case 0x2:
        fVar5 = *(float *)(pbVar4 + 0x48) + *(float *)(pbVar4 + 0x44);
        if (fVar5 < 0.0f) {
          fVar2 = 0.0f;
        }
        else {
          fVar2 = fVar5;
          if (1.0f < fVar5) {
            fVar2 = 1.0f;
          }
        }
        if (local_4 < fVar2) {
          if (fVar5 < 0.0f) {
            local_4 = 0.0f;
          }
          else {
            local_4 = fVar5;
            if (1.0f < fVar5) {
              local_4 = 1.0f;
            }
          }
        }
        fVar5 = local_4 * 63.0f;
        *(float *)(pbVar4 + 0x44) = fVar5;
        if ((*pbVar4 & 1) == 0) {
          if (g_nRdroid_curZBufferMethod == 1) {
            rdAFRaster_SetupNGonMFAT((int *)rec,(int)mat,fVar5);
          }
        }
        else {
          (**(code **)(pbVar4 + 0x18))(rec,mat,fVar5);
        }
        break;
      case 0x3:
        uVar7 = 0;
        if (*(int *)(pbVar4 + 0x1c) != 0) {
          do {
            fVar5 = *(float *)(*(int *)(pbVar4 + 0x28) + uVar7 * 4) + *(float *)(pbVar4 + 0x48);
            iVar8 = uVar7 * 4;
            if (fVar5 < 0.0f) {
              fVar2 = 0.0f;
            }
            else {
              fVar2 = fVar5;
              if (1.0f < fVar5) {
                fVar2 = 1.0f;
              }
            }
            fVar3 = local_4;
            if (local_4 < fVar2) {
              if (fVar5 < 0.0f) {
                fVar3 = 0.0f;
              }
              else {
                fVar3 = fVar5;
                if (1.0f < fVar5) {
                  fVar3 = 1.0f;
                }
              }
            }
            uVar7 = uVar7 + 1;
            *(float *)(*(int *)(pbVar4 + 0x28) + iVar8) = fVar3 * 63.0f;
          } while (uVar7 < *(uint *)(pbVar4 + 0x1c));
        }
        if ((*pbVar4 & 1) == 0) {
          if (g_nRdroid_curZBufferMethod == 1) {
            rdAFRaster_SetupNGonMGAT((int *)rec,(int)mat);
          }
        }
        else {
          (**(code **)(pbVar4 + 0x18))(rec,mat,0);
        }
      }
    }
    else if ((0 < iVar8) && (iVar8 < 3)) {
      switch((int)(face)) {
      case 0x0:
        if ((*pbVar4 & 1) == 0) {
          if (g_nRdroid_curZBufferMethod == 1) {
            rdAFRaster_SetupNGonMLIT((int *)rec,(int)mat);
          }
        }
        else {
          (**(code **)(pbVar4 + 0x18))(rec,mat,0);
        }
        break;
      case 0x1:
        if (*(float *)(pbVar4 + 0x48) < 0.0f) {
          fVar5 = 0.0f;
        }
        else if (1.0f < *(float *)(pbVar4 + 0x48)) {
          fVar5 = 1.0f;
        }
        else {
          fVar5 = *(float *)(pbVar4 + 0x48);
        }
        if (local_4 < fVar5) {
          if (*(float *)(pbVar4 + 0x48) < 0.0f) {
            local_4 = 0.0f;
          }
          else if (1.0f < *(float *)(pbVar4 + 0x48)) {
            local_4 = 1.0f;
          }
          else {
            local_4 = *(float *)(pbVar4 + 0x48);
          }
        }
        fVar5 = local_4 * 63.0f;
        *(float *)(pbVar4 + 0x44) = fVar5;
        if ((*pbVar4 & 1) == 0) {
          if (g_nRdroid_curZBufferMethod == 1) {
            rdAFRaster_SetupNGonMFIT((int *)rec,(int)mat,fVar5);
          }
        }
        else {
          (**(code **)(pbVar4 + 0x18))(rec,mat,fVar5);
        }
        break;
      case 0x2:
        fVar5 = *(float *)(pbVar4 + 0x48) + *(float *)(pbVar4 + 0x44);
        if (fVar5 < 0.0f) {
          fVar2 = 0.0f;
        }
        else {
          fVar2 = fVar5;
          if (1.0f < fVar5) {
            fVar2 = 1.0f;
          }
        }
        if (local_4 < fVar2) {
          if (fVar5 < 0.0f) {
            local_4 = 0.0f;
          }
          else {
            local_4 = fVar5;
            if (1.0f < fVar5) {
              local_4 = 1.0f;
            }
          }
        }
        fVar5 = local_4 * 63.0f;
        *(float *)(pbVar4 + 0x44) = fVar5;
        if ((*pbVar4 & 1) == 0) {
          if (g_nRdroid_curZBufferMethod == 1) {
            rdAFRaster_SetupNGonMFIT((int *)rec,(int)mat,fVar5);
          }
        }
        else {
          (**(code **)(pbVar4 + 0x18))(rec,mat,fVar5);
        }
        break;
      case 0x3:
        uVar7 = 0;
        if (*(int *)(pbVar4 + 0x1c) != 0) {
          do {
            fVar5 = *(float *)(*(int *)(pbVar4 + 0x28) + uVar7 * 4) + *(float *)(pbVar4 + 0x48);
            iVar8 = uVar7 * 4;
            if (fVar5 < 0.0f) {
              fVar2 = 0.0f;
            }
            else {
              fVar2 = fVar5;
              if (1.0f < fVar5) {
                fVar2 = 1.0f;
              }
            }
            fVar3 = local_4;
            if (local_4 < fVar2) {
              if (fVar5 < 0.0f) {
                fVar3 = 0.0f;
              }
              else {
                fVar3 = fVar5;
                if (1.0f < fVar5) {
                  fVar3 = 1.0f;
                }
              }
            }
            uVar7 = uVar7 + 1;
            *(float *)(*(int *)(pbVar4 + 0x28) + iVar8) = fVar3 * 63.0f;
          } while (uVar7 < *(uint *)(pbVar4 + 0x1c));
        }
        if ((*pbVar4 & 1) == 0) {
          if (g_nRdroid_curZBufferMethod == 1) {
            rdAFRaster_SetupNGonMGIT((int *)rec,(int)mat);
          }
        }
        else {
          (**(code **)(pbVar4 + 0x18))(rec,mat,0);
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

void __cdecl
rdCanvas_DrawLine(rdCanvas *canvas,int x0,int y0,int x1,int y1,ushort color,uint pattern)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  VBuffer *pVVar2;
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
  pVVar2 = canvas->pVBuffer;
  local_10 = 0x80000000;
  if ((pVVar2->format).colorFormat.nBpp == 8) {
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
      *(undefined1 *)((int)pVVar2->pPixels + iVar3 + (pVVar2->format).nPitch * iVar4) =
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
         ((int)canvas->pVBuffer->pPixels + y0 + (canvas->pVBuffer->format).nPitch * x0) =
             (undefined1)color;
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
      *(ushort *)((int)pVVar2->pPixels + ((pVVar2->format).nStride * iVar4 + iVar3) * 2) = color;
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
         ((int)canvas->pVBuffer->pPixels + ((canvas->pVBuffer->format).nStride * x0 + y0) * 2) =
             color;
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

void __cdecl rdCanvas_DrawPoint(void *canvas,int x,int y,uint radius,float step,int color,int flags)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float deg;
  int y1;
  int iVar1;
  int x2;
  int y2;
  longlong lVar2;
  longlong lVar3;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  lVar2 = FTOL((float10)PUN(float,radius) - (float10)-0.5);
  iVar1 = (int)lVar2;
  if ((((*(int *)((int)canvas + 0x18) <= iVar1 + x) && (x - iVar1 <= *(int *)((int)canvas + 0x20)))
      && (*(int *)((int)canvas + 0x1c) <= iVar1 + y)) && (y - iVar1 <= *(int *)((int)canvas + 0x24))
     ) {
    stdMath_SinCos(0.0f,(float *)&local_4,(float *)&local_8);
    lVar2 = FTOL((float10)PUN(float,local_8) * (float10)PUN(float,radius) - (float10)-0.5);
    lVar3 = FTOL((float10)PUN(float,local_4) * (float10)PUN(float,radius) - (float10)-0.5);
    iVar1 = (int)lVar2 + x;
    y1 = (int)lVar3 + y;
    for (deg = step; deg <= 360.0f; deg = deg + step) {
      stdMath_SinCos(deg,(float *)&local_4,(float *)&local_8);
      lVar2 = FTOL((float10)PUN(float,local_8) * (float10)PUN(float,radius) - (float10)-0.5);
      x2 = (int)lVar2 + x;
      lVar2 = FTOL((float10)PUN(float,local_4) * (float10)PUN(float,radius) - (float10)-0.5);
      y2 = (int)lVar2 + y;
      rdPrimit2_DrawLine(canvas,iVar1,y1,x2,y2,color,flags);
      iVar1 = x2;
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
rdCanvas_New(uint flags,uint surface,uint zSurface,uint x0,uint y0,uint x1,uint y1,uint extra)

{
  rdCanvas *canvas;
  
  canvas = (rdCanvas *)
           (*g_pRdroid_HS->pAlloc)
                     (0x28,s_C__grimjedi_Libs_RDroid_Engine_R_004f0edc,DAT_004f0ed8 + 4);
  if (canvas == (rdCanvas *)0x0) {
    return (uint *)0x0;
  }
  rdCanvas_NewEntry(canvas,flags,surface,zSurface,x0,y0,x1,y1,extra);
  return &canvas->dwFlags;
}

/* ---- 0x004c0550  rdCanvas_NewEntry ---- */
/* flags bit 0: explicit clip rect, otherwise the whole surface Original name rdCanvas_NewEntry (the
   remaster's GrimFandango (Linux): same parameters (canvas, flags, surface, z surface, the
   rectangle, extra) and body); was rdCanvas_Init. */

int __cdecl
rdCanvas_NewEntry(rdCanvas *canvas,uint flags,uint surface,uint zSurface,uint x0,uint y0,uint x1,
                 uint y1,uint extra)

{
  canvas->pZBuffer = (VBuffer *)zSurface;
  canvas->dwFlags = flags;
  canvas->pVBuffer = (VBuffer *)surface;
  canvas->dwExtra = extra;
  if ((flags & 1) == 0) {
    canvas->nX0 = 0;
    canvas->nY0 = 0;
    canvas->nX1 = *(int *)(surface + 0xc) + -1;
    canvas->nY1 = *(int *)(surface + 0x10) + -1;
  }
  else {
    canvas->nX0 = x0;
    canvas->nY0 = y0;
    canvas->nX1 = x1;
    canvas->nY1 = y1;
  }
  canvas->flCenterX = (float)canvas->nX0 + (float)((canvas->nX1 - canvas->nX0) + 1) * 0.5f;
  canvas->flCenterY = (float)canvas->nY0 + (float)((canvas->nY1 - canvas->nY0) + 1) * 0.5f;
  return 1;
}

/* ---- 0x004c0610  rdCanvas_Free ---- */
void __cdecl rdCanvas_Free(int canvas)

{
  if (canvas != 0) {
    Mem_DumpLog();
    (*g_pRdroid_HS->pFree)(canvas);
  }
  return;
}
