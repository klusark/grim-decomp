/* GRIMFANDANGO.EXE :: rdcanvas.c
 * functions 0x00404c00 .. 0x004c0610 (12 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00404c00  rdCanvas_InitEdgeTables ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Clears the per-scanline edge buckets for the current canvas height */

void rdCanvas_InitEdgeTables(void)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  
  iVar4 = *(int *)(*(int *)((int)g_pRdCurrentCamera + 4) + 0x1c);
  _DAT_004f6ef8 = 0xffff0000;
  uVar1 = (*(int *)(*(int *)((int)g_pRdCurrentCamera + 4) + 0x24) - iVar4) + 1;
  DAT_004f6f20 = &DAT_005e6f40;
  _DAT_005e6f8c = &DAT_004f6ed0;
  puVar5 = (undefined4 *)(&DAT_004f5ec8 + iVar4 * 4);
  for (uVar2 = uVar1 & 0x3fffffff; uVar2 != 0; uVar2 = uVar2 - 1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
    *(undefined1 *)puVar5 = 0;
    puVar5 = (undefined4 *)((int)puVar5 + 1);
  }
  puVar5 = (undefined4 *)(&DAT_0050cf38 + iVar4 * 4);
  for (uVar1 = uVar1 & 0x3fffffff; uVar1 != 0; uVar1 = uVar1 - 1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
    *(undefined1 *)puVar5 = 0;
    puVar5 = (undefined4 *)((int)puVar5 + 1);
  }
  DAT_004f6ec8 = 0x7fffffff;
  DAT_004f6f28 = 0;
  _DAT_004f6f1c = 0;
  _DAT_005e6f68 = 0x7fffffff;
  _DAT_005e6f90 = 0;
  DAT_005e6f3c = 0;
  DAT_005e6f38 = 0;
  DAT_004f6f2c = 0;
  return;
}

/* ---- 0x00404ca0  rdCanvas_ResetPolyCount ---- */
void rdCanvas_ResetPolyCount(void)

{
  DAT_005e6f98 = 0;
  return;
}

/* ---- 0x00404cb0  rdCanvas_ScanConvert ---- */
/* Rdcanvas.c: active-edge scanline loop over all queued polygons; merges edges per scanline, emits
   spans, flushes them */

void rdCanvas_ScanConvert(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  undefined *puVar5;
  undefined *puVar6;
  
  rdCanvas_BuildEdgeLists();
  DAT_0050cf30 = DAT_004f6ec8;
  if (DAT_004f6ec8 <= DAT_004f6f28) {
    do {
      piVar4 = *(int **)(&DAT_004f5ec8 + DAT_0050cf30 * 4);
      puVar5 = DAT_004f6f20;
      while (piVar4 != (int *)0x0) {
        iVar1 = piVar4[10];
        iVar2 = *(int *)(puVar5 + 0x28);
        piVar3 = (int *)piVar4[0x14];
        while ((((iVar2 < iVar1 &&
                 (puVar5 = *(undefined **)(puVar5 + 0x50), *(int *)(puVar5 + 0x28) < iVar1)) &&
                (puVar5 = *(undefined **)(puVar5 + 0x50), *(int *)(puVar5 + 0x28) < iVar1)) &&
               (puVar5 = *(undefined **)(puVar5 + 0x50), *(int *)(puVar5 + 0x28) < iVar1))) {
          puVar5 = *(undefined **)(puVar5 + 0x50);
          iVar2 = *(int *)(puVar5 + 0x28);
        }
        piVar4[0x14] = (int)puVar5;
        piVar4[0x13] = *(int *)(puVar5 + 0x4c);
        *(int **)(*(int *)(puVar5 + 0x4c) + 0x50) = piVar4;
        *(int **)(puVar5 + 0x4c) = piVar4;
        if (*piVar4 == 0) {
          *(int **)(piVar4[1] + 0x1f0) = piVar4;
          piVar4 = piVar3;
        }
        else {
          *(int **)(piVar4[1] + 0x1ec) = piVar4;
          piVar4 = piVar3;
        }
      }
      rdCanvas_EmitSpans();
      for (iVar2 = *(int *)(&DAT_0050cf38 + DAT_0050cf30 * 4); iVar2 != 0;
          iVar2 = *(int *)(iVar2 + 0x54)) {
        *(undefined4 *)(*(int *)(iVar2 + 0x50) + 0x4c) = *(undefined4 *)(iVar2 + 0x4c);
        *(undefined4 *)(*(int *)(iVar2 + 0x4c) + 0x50) = *(undefined4 *)(iVar2 + 0x50);
      }
      puVar5 = DAT_004f6f20;
      if (DAT_004f6f20 != &DAT_005e6f40) {
        do {
          (**(code **)(puVar5 + 0x48))(puVar5);
          if (*(int *)(puVar5 + 0x28) < *(int *)(*(int *)(puVar5 + 0x4c) + 0x28)) {
            puVar6 = *(undefined **)(puVar5 + 0x50);
            *(int *)(puVar6 + 0x4c) = *(int *)(puVar5 + 0x4c);
            *(undefined **)(*(int *)(puVar5 + 0x4c) + 0x50) = puVar6;
            iVar1 = *(int *)(*(int *)(puVar5 + 0x4c) + 0x4c);
            iVar2 = *(int *)(iVar1 + 0x28);
            while (*(int *)(puVar5 + 0x28) < iVar2) {
              iVar1 = *(int *)(iVar1 + 0x4c);
              iVar2 = *(int *)(iVar1 + 0x28);
            }
            iVar2 = *(int *)(iVar1 + 0x50);
            *(int *)(puVar5 + 0x4c) = iVar1;
            *(int *)(puVar5 + 0x50) = iVar2;
            *(undefined **)(iVar2 + 0x4c) = puVar5;
            *(undefined **)(iVar1 + 0x50) = puVar5;
          }
          else {
            puVar6 = *(undefined **)(puVar5 + 0x50);
          }
          puVar5 = puVar6;
        } while (puVar6 != &DAT_005e6f40);
      }
      DAT_0050cf30 = DAT_0050cf30 + 1;
    } while (DAT_0050cf30 <= DAT_004f6f28);
  }
  rdCanvas_FlushSpans();
  return;
}

/* ---- 0x00404e00  rdCanvas_EmitSpans ---- */
/* Walks the active edge list for one scanline, computing 0x2c-byte span records with interpolated
   z/u/v/light */

void rdCanvas_EmitSpans(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  float fVar7;
  bool bVar8;
  undefined4 uVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  int *piVar14;
  uint uVar15;
  int *piVar16;
  int *piVar17;
  int *piVar18;
  #define local_20 (*(int **)(_frame + (0x30 - 0x20)))
  
  if ((DAT_005e6f38 != 0) &&
     (piVar18 = (int *)0x0, piVar14 = DAT_004f6f20, DAT_004f6f20 != (int *)&DAT_005e6f40)) {
    do {
      piVar2 = (int *)piVar14[1];
      if (*piVar14 == 0) {
        iVar11 = piVar2[0x7e];
        piVar2[0x7e] = iVar11 + -1;
        if (iVar11 + -1 == 0) {
          if (piVar2 == piVar18) {
            uVar10 = piVar14[10];
            if ((uVar10 & 0xffff) != 0) {
              uVar10 = uVar10 + 0x10000 & 0xffff0000;
            }
            iVar11 = (int)(uVar10 - piVar18[0x7d]) >> 0x10;
            if (0 < iVar11) {
              if (0x7ff < DAT_004f6f2c) {
                rdCanvas_FlushSpans();
              }
              iVar3 = piVar18[0x7b];
              iVar4 = piVar18[0x7c];
              iVar1 = DAT_004f6f2c * 0x2c;
              piVar2 = (int *)(&DAT_004f6f30 + iVar1);
              DAT_004f6f2c = DAT_004f6f2c + 1;
              *piVar2 = piVar18[0x7d] >> 0x10;
              *(int *)(&DAT_004f6f34 + iVar1) = iVar11;
              *(undefined4 *)(&DAT_004f6f38 + iVar1) = DAT_0050cf30;
              *(undefined4 *)(&DAT_004f6f58 + iVar1) = 0;
              uVar15 = *(uint *)(iVar4 + 0x28);
              if ((uVar15 & 0xffff) != 0) {
                uVar15 = uVar15 + 0x10000 & 0xffff0000;
              }
              uVar12 = *(uint *)(iVar3 + 0x28);
              uVar13 = uVar12;
              if ((uVar12 & 0xffff) != 0) {
                uVar13 = uVar12 + 0x10000 & 0xffff0000;
              }
              uVar15 = uVar15 - uVar13 >> 0x10;
              iVar11 = piVar18[0x7d] - uVar12;
              fVar7 = (float)iVar11 * 1.5258789e-05;
              *(float *)(&DAT_004f6f4c + iVar1) =
                   (float)piVar18[0x61] * fVar7 + *(float *)(iVar3 + 0x10);
              if (*(int *)(*piVar18 + 8) == 4) {
                iVar5 = *(int *)(*piVar18 + 0x10);
                if (iVar5 == 0) {
                  iVar5 = *(int *)(&DAT_008fbfc0 + uVar15 * 4);
                  lVar6 = (longlong)(*(int *)(iVar4 + 0x30) - *(int *)(iVar3 + 0x30)) *
                          (longlong)iVar5;
                  uVar12 = (uint)lVar6 >> 0x10 | (int)((ulonglong)lVar6 >> 0x20) << 0x10;
                  *(int *)(&DAT_004f6f40 + iVar1) = (int)uVar12 >> ((byte)piVar18[0x70] & 0x1f);
                  lVar6 = (longlong)iVar11 * (longlong)(int)uVar12;
                  *(int *)(&DAT_004f6f3c + iVar1) =
                       (int)(*(int *)(iVar3 + 0x30) +
                            ((uint)lVar6 >> 0x10 | (int)((ulonglong)lVar6 >> 0x20) << 0x10)) >>
                       ((byte)piVar18[0x70] & 0x1f);
                  lVar6 = (longlong)(*(int *)(iVar4 + 0x38) - *(int *)(iVar3 + 0x38)) *
                          (longlong)iVar5;
                  uVar12 = (uint)lVar6 >> 0x10 | (int)((ulonglong)lVar6 >> 0x20) << 0x10;
                  *(int *)(&DAT_004f6f48 + iVar1) = (int)uVar12 >> ((byte)piVar18[0x70] & 0x1f);
                  lVar6 = (longlong)iVar11 * (longlong)(int)uVar12;
                  *(int *)(&DAT_004f6f44 + iVar1) =
                       (int)(*(int *)(iVar3 + 0x38) +
                            ((uint)lVar6 >> 0x10 | (int)((ulonglong)lVar6 >> 0x20) << 0x10)) >>
                       ((byte)piVar18[0x70] & 0x1f);
                }
                else if (iVar5 == 1) {
                  *(float *)(&DAT_004f6f3c + iVar1) =
                       (float)piVar18[99] * fVar7 + *(float *)(iVar3 + 0x18);
                  *(float *)(&DAT_004f6f40 + iVar1) =
                       (float)piVar18[0x65] * fVar7 + *(float *)(iVar3 + 0x20);
                }
              }
              else {
                *(int *)(&DAT_004f6f3c + iVar1) = piVar18[0x74];
              }
              if (*(int *)(*piVar18 + 0xc) == 3) {
                lVar6 = (longlong)(*(int *)(iVar4 + 0x40) - *(int *)(iVar3 + 0x40)) *
                        (longlong)*(int *)(&DAT_008fbfc0 + uVar15 * 4);
                uVar15 = (uint)lVar6 >> 0x10 | (int)((ulonglong)lVar6 >> 0x20) << 0x10;
                *(uint *)(&DAT_004f6f54 + iVar1) = uVar15;
                if (((int)uVar15 < 0) && (-0x51e < (int)uVar15)) {
                  *(undefined4 *)(&DAT_004f6f54 + iVar1) = 0;
                }
                *(uint *)(&DAT_004f6f50 + iVar1) =
                     *(int *)(iVar3 + 0x40) +
                     ((uint)((longlong)iVar11 * (longlong)*(int *)(&DAT_004f6f54 + iVar1)) >> 0x10 |
                     (int)((ulonglong)((longlong)iVar11 * (longlong)*(int *)(&DAT_004f6f54 + iVar1))
                          >> 0x20) << 0x10);
              }
              if (piVar18[0x6e] == 0) {
                piVar18[0x6e] = (int)piVar2;
              }
              else {
                *(int **)(piVar18[0x6f] + 0x28) = piVar2;
              }
              piVar18[0x6f] = (int)piVar2;
            }
            piVar18 = (int *)piVar18[0x80];
            if (piVar18 != (int *)0x0) {
              piVar18[0x7d] = uVar10;
              piVar18[0x7f] = 0;
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
        iVar11 = piVar2[0x7e];
        piVar2[0x7e] = iVar11 + 1;
        if (iVar11 + 1 == 1) {
          if ((*(int *)(*piVar2 + 8) != 4) || (*(int *)(*piVar2 + 0x10) != 1)) {
            uVar10 = *(uint *)(piVar2[0x7c] + 0x28);
            if ((uVar10 & 0xffff) != 0) {
              uVar10 = uVar10 + 0x10000 & 0xffff0000;
            }
            uVar15 = *(uint *)(piVar2[0x7b] + 0x28);
            if ((uVar15 & 0xffff) != 0) {
              uVar15 = uVar15 + 0x10000 & 0xffff0000;
            }
            fVar7 = (*(float *)(piVar2[0x7c] + 0x10) - *(float *)(piVar2[0x7b] + 0x10)) *
                    (float)(&DAT_008fe000)[uVar10 - uVar15 >> 0x10];
            piVar2[0x61] = (int)fVar7;
            piVar2[0x67] = (int)ROUND(fVar7 * 65536.0);
          }
          if (piVar18 == (int *)0x0) {
            piVar2[0x7f] = 0;
            piVar2[0x80] = 0;
            uVar10 = piVar14[10];
            if ((uVar10 & 0xffff) != 0) {
              uVar10 = uVar10 + 0x10000 & 0xffff0000;
            }
            piVar2[0x7d] = uVar10;
            piVar18 = piVar2;
          }
          else {
            uVar10 = *(uint *)(*piVar2 + 0x74);
            if (((*(uint *)(*piVar18 + 0x74) ^ uVar10) & 0xffff) == 0) {
              uVar15 = *(uint *)(*piVar18 + 0x74) >> 0x10;
              if (uVar15 < uVar10 >> 0x10) {
                bVar8 = true;
              }
              else {
                if (uVar15 <= uVar10 >> 0x10) goto LAB_00404f44;
                bVar8 = false;
              }
            }
            else {
LAB_00404f44:
              fVar7 = (float)(piVar14[10] - *(int *)(piVar18[0x7b] + 0x28)) * 1.5258789e-05 *
                      (float)piVar18[0x61] + *(float *)(piVar18[0x7b] + 0x10);
              if ((float)piVar14[4] <= fVar7) {
                if (((float)piVar14[4] != fVar7) || ((float)piVar2[0x61] <= (float)piVar18[0x61])) {
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
              uVar10 = piVar14[10];
              if ((uVar10 & 0xffff) != 0) {
                uVar10 = uVar10 + 0x10000 & 0xffff0000;
              }
              iVar11 = (int)(uVar10 - piVar18[0x7d]) >> 0x10;
              if (0 < iVar11) {
                if (0x7ff < DAT_004f6f2c) {
                  rdCanvas_FlushSpans();
                }
                iVar3 = piVar18[0x7b];
                iVar1 = DAT_004f6f2c * 0x2c;
                piVar17 = (int *)(&DAT_004f6f30 + iVar1);
                iVar4 = piVar18[0x7c];
                DAT_004f6f2c = DAT_004f6f2c + 1;
                *piVar17 = piVar18[0x7d] >> 0x10;
                *(int *)(&DAT_004f6f34 + iVar1) = iVar11;
                uVar9 = DAT_0050cf30;
                *(undefined4 *)(&DAT_004f6f58 + iVar1) = 0;
                *(undefined4 *)(&DAT_004f6f38 + iVar1) = uVar9;
                uVar15 = *(uint *)(iVar4 + 0x28);
                if ((uVar15 & 0xffff) != 0) {
                  uVar15 = uVar15 + 0x10000 & 0xffff0000;
                }
                uVar12 = *(uint *)(iVar3 + 0x28);
                if ((uVar12 & 0xffff) != 0) {
                  uVar12 = uVar12 + 0x10000 & 0xffff0000;
                }
                uVar15 = uVar15 - uVar12 >> 0x10;
                iVar11 = piVar18[0x7d] - *(int *)(piVar18[0x7b] + 0x28);
                fVar7 = (float)iVar11 * 1.5258789e-05;
                *(float *)(&DAT_004f6f4c + iVar1) =
                     (float)piVar18[0x61] * fVar7 + *(float *)(iVar3 + 0x10);
                if (*(int *)(*piVar18 + 8) == 4) {
                  iVar5 = *(int *)(*piVar18 + 0x10);
                  if (iVar5 == 0) {
                    iVar5 = *(int *)(&DAT_008fbfc0 + uVar15 * 4);
                    lVar6 = (longlong)(*(int *)(iVar4 + 0x30) - *(int *)(iVar3 + 0x30)) *
                            (longlong)iVar5;
                    uVar12 = (uint)lVar6 >> 0x10 | (int)((ulonglong)lVar6 >> 0x20) << 0x10;
                    *(int *)(&DAT_004f6f40 + iVar1) = (int)uVar12 >> ((byte)piVar18[0x70] & 0x1f);
                    lVar6 = (longlong)iVar11 * (longlong)(int)uVar12;
                    *(int *)(&DAT_004f6f3c + iVar1) =
                         (int)(*(int *)(iVar3 + 0x30) +
                              ((uint)lVar6 >> 0x10 | (int)((ulonglong)lVar6 >> 0x20) << 0x10)) >>
                         ((byte)piVar18[0x70] & 0x1f);
                    lVar6 = (longlong)(*(int *)(iVar4 + 0x38) - *(int *)(iVar3 + 0x38)) *
                            (longlong)iVar5;
                    uVar12 = (uint)lVar6 >> 0x10 | (int)((ulonglong)lVar6 >> 0x20) << 0x10;
                    *(int *)(&DAT_004f6f48 + iVar1) = (int)uVar12 >> ((byte)piVar18[0x70] & 0x1f);
                    lVar6 = (longlong)iVar11 * (longlong)(int)uVar12;
                    *(int *)(&DAT_004f6f44 + iVar1) =
                         (int)(*(int *)(iVar3 + 0x38) +
                              ((uint)lVar6 >> 0x10 | (int)((ulonglong)lVar6 >> 0x20) << 0x10)) >>
                         ((byte)piVar18[0x70] & 0x1f);
                  }
                  else if (iVar5 == 1) {
                    *(float *)(&DAT_004f6f3c + iVar1) =
                         (float)piVar18[99] * fVar7 + *(float *)(iVar3 + 0x18);
                    *(float *)(&DAT_004f6f40 + iVar1) =
                         (float)piVar18[0x65] * fVar7 + *(float *)(iVar3 + 0x20);
                  }
                }
                else {
                  *(int *)(&DAT_004f6f3c + iVar1) = piVar18[0x74];
                }
                if (*(int *)(*piVar18 + 0xc) == 3) {
                  lVar6 = (longlong)(*(int *)(iVar4 + 0x40) - *(int *)(iVar3 + 0x40)) *
                          (longlong)*(int *)(&DAT_008fbfc0 + uVar15 * 4);
                  uVar15 = (uint)lVar6 >> 0x10 | (int)((ulonglong)lVar6 >> 0x20) << 0x10;
                  *(uint *)(&DAT_004f6f54 + iVar1) = uVar15;
                  if (((int)uVar15 < 0) && (-0x51e < (int)uVar15)) {
                    *(undefined4 *)(&DAT_004f6f54 + iVar1) = 0;
                  }
                  *(uint *)(&DAT_004f6f50 + iVar1) =
                       *(int *)(iVar3 + 0x40) +
                       ((uint)((longlong)iVar11 * (longlong)*(int *)(&DAT_004f6f54 + iVar1)) >> 0x10
                       | (int)((ulonglong)
                               ((longlong)iVar11 * (longlong)*(int *)(&DAT_004f6f54 + iVar1)) >>
                              0x20) << 0x10);
                }
                if (piVar18[0x6e] == 0) {
                  piVar18[0x6e] = (int)piVar17;
                }
                else {
                  *(int **)(piVar18[0x6f] + 0x28) = piVar17;
                }
                piVar18[0x6f] = (int)piVar17;
              }
              piVar2[0x80] = (int)piVar18;
              piVar18[0x7f] = (int)piVar2;
              piVar2[0x7f] = 0;
              piVar2[0x7d] = uVar10;
              piVar18 = piVar2;
            }
            else {
              piVar17 = (int *)piVar18[0x80];
              local_20 = piVar18;
              if ((int *)piVar18[0x80] != (int *)0x0) {
                do {
                  piVar16 = piVar17;
                  if (((*(uint *)(*piVar16 + 0x74) ^ uVar10) & 0xffff) == 0) {
                    uVar15 = *(uint *)(*piVar16 + 0x74) >> 0x10;
                    if (uVar15 < uVar10 >> 0x10) {
                      bVar8 = true;
                    }
                    else {
                      if (uVar15 <= uVar10 >> 0x10) goto LAB_00405252;
LAB_004052b3:
                      bVar8 = false;
                    }
                  }
                  else {
LAB_00405252:
                    fVar7 = (float)(piVar14[10] - *(int *)(piVar16[0x7b] + 0x28)) * 1.5258789e-05 *
                            (float)piVar16[0x61] + *(float *)(piVar16[0x7b] + 0x10);
                    if ((float)piVar14[4] <= fVar7) {
                      if (((float)piVar14[4] != fVar7) ||
                         ((float)piVar2[0x61] <= (float)piVar16[0x61])) goto LAB_004052b3;
                      bVar8 = true;
                    }
                    else {
                      bVar8 = true;
                    }
                  }
                  piVar17 = piVar16;
                } while ((!bVar8) &&
                        (piVar17 = (int *)piVar16[0x80], local_20 = piVar16, piVar17 != (int *)0x0))
                ;
                if (piVar17 != (int *)0x0) {
                  piVar2[0x7f] = (int)local_20;
                  local_20[0x80] = (int)piVar2;
                  piVar17[0x7f] = (int)piVar2;
                  piVar2[0x80] = (int)piVar17;
                  goto LAB_004055a9;
                }
              }
              local_20[0x80] = (int)piVar2;
              piVar2[0x7f] = (int)local_20;
              piVar2[0x80] = 0;
            }
          }
        }
      }
LAB_004055a9:
      piVar2 = piVar14 + 0x14;
      piVar14 = (int *)*piVar2;
    } while ((int *)*piVar2 != (int *)&DAT_005e6f40);
  }
  return;
}
#undef local_20


/* ---- 0x004055d0  rdCanvas_FlushSpans ---- */
/* Calls each polygon's span-draw callback for its accumulated spans and resets the span buffer */

void rdCanvas_FlushSpans(void)

{
  int *piVar1;
  uint uVar2;
  
  uVar2 = 0;
  if (DAT_005e6f3c != 0) {
    piVar1 = &DAT_005660f0;
    do {
      if (*piVar1 != 0) {
        (*(code *)piVar1[-1])(piVar1 + -0x6e);
        *piVar1 = 0;
        piVar1[1] = 0;
      }
      piVar1 = piVar1 + 0x81;
      uVar2 = uVar2 + 1;
    } while (uVar2 < DAT_005e6f3c);
  }
  DAT_004f6f2c = 0;
  return;
}

/* ---- 0x00405620  rdCanvas_BuildEdgeLists ---- */
/* For every queued polygon, runs its edge-setup callback on each edge and inserts the edges into
   the per-scanline buckets */

void rdCanvas_BuildEdgeLists(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  undefined1 *puVar8;
  undefined *puVar9;
  uint uVar10;
  int *piVar11;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar10 = 0;
  puVar8 = &DAT_008ddfc0;
  if (g_dwRdCacheMeshCount != 0) {
    do {
      rdCanvas_PreparePolygon(puVar8);
      puVar8 = puVar8 + 0x78;
      uVar10 = uVar10 + 1;
    } while (uVar10 < g_dwRdCacheMeshCount);
  }
  piVar11 = &DAT_00565f38;
  puVar9 = &DAT_0050df38;
  local_4 = 0;
  if (DAT_005e6f3c != 0) {
    do {
      iVar2 = *piVar11;
      uVar10 = *(uint *)(iVar2 + 0x1c);
      uVar7 = 0;
      if (uVar10 != 0) {
        do {
          uVar1 = uVar7 + 1;
          uVar5 = ~-(uint)(uVar10 - 1 < uVar1) & uVar1;
          uVar10 = uVar5;
          if (*(int *)(*piVar11 + 0x50) == 0) {
            uVar10 = uVar7;
            uVar7 = uVar5;
          }
          iVar6 = (*(code *)piVar11[0x7a])(puVar9,piVar11,uVar10,uVar7);
          if (iVar6 != 0) {
            *(int **)(puVar9 + 4) = piVar11;
            iVar6 = *(int *)(&DAT_004f5ec8 + *(int *)(puVar9 + 8) * 4);
            if ((iVar6 == 0) || (*(int *)(puVar9 + 0x28) <= *(int *)(iVar6 + 0x28))) {
              *(int *)(puVar9 + 0x50) = iVar6;
              *(undefined **)(&DAT_004f5ec8 + *(int *)(puVar9 + 8) * 4) = puVar9;
            }
            else {
              for (iVar4 = *(int *)(iVar6 + 0x50);
                  (iVar4 != 0 && (*(int *)(iVar4 + 0x28) < *(int *)(puVar9 + 0x28)));
                  iVar4 = *(int *)(iVar4 + 0x50)) {
                iVar6 = iVar4;
              }
              *(undefined4 *)(puVar9 + 0x50) = *(undefined4 *)(iVar6 + 0x50);
              *(undefined **)(iVar6 + 0x50) = puVar9;
            }
            uVar7 = *(uint *)(puVar9 + 8);
            uVar10 = *(int *)(puVar9 + 0xc) + -1 + uVar7;
            uVar3 = *(undefined4 *)(&DAT_0050cf38 + uVar10 * 4);
            *(undefined **)(&DAT_0050cf38 + uVar10 * 4) = puVar9;
            *(undefined4 *)(puVar9 + 0x54) = uVar3;
            if (uVar7 < DAT_004f6ec8) {
              DAT_004f6ec8 = uVar7;
            }
            if (DAT_004f6f28 < uVar10) {
              DAT_004f6f28 = uVar10;
            }
            puVar9 = puVar9 + 0x58;
            DAT_005e6f38 = DAT_005e6f38 + 1;
          }
          uVar10 = *(uint *)(iVar2 + 0x1c);
          uVar7 = uVar1;
        } while (uVar1 < uVar10);
      }
      piVar11 = piVar11 + 0x81;
      local_4 = local_4 + 1;
    } while (local_4 < DAT_005e6f3c);
  }
  return;
}
#undef local_4


/* ---- 0x00405770  rdCanvas_PreparePolygon ---- */
undefined4 rdCanvas_PreparePolygon(byte *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 *puVar2;
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
  uVar8 = DAT_005e6f3c;
  if (0x3ff < DAT_005e6f3c) {
    return 0;
  }
  local_4 = *(float *)(param_1 + 8);
  if (g_nRdroidGeometryMode <= (int)local_4) {
    local_4 = (float)g_nRdroidGeometryMode;
  }
  param_1 = *(byte **)(param_1 + 0xc);
  if (g_nRdroidLightingMode <= (int)param_1) {
    param_1 = (byte *)g_nRdroidLightingMode;
  }
  iVar10 = *(int *)(pbVar5 + 0x10);
  if (g_nRdroidTextureMode <= *(int *)(pbVar5 + 0x10)) {
    iVar10 = g_nRdroidTextureMode;
  }
  if (local_4 == 0.0) {
    return 0;
  }
  iVar1 = DAT_005e6f3c * 0x204;
  puVar2 = &DAT_00565f38 + DAT_005e6f3c * 0x81;
  *puVar2 = pbVar5;
  (&DAT_005660f0)[uVar8 * 0x81] = 0;
  (&DAT_005660f4)[uVar8 * 0x81] = 0;
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
    fVar6 = (float)3;
  }
LAB_0040585d:
  if (((byte)g_dwRdroidFlags & 2) == 0) {
    local_4 = 0.0;
  }
  else {
    local_4 = *(float *)(pbVar5 + 0x40);
  }
  if (fVar6 == 2.8026e-45) {
    if ((-1 < (int)param_1) && ((int)param_1 < 5)) {
      if ((*pbVar5 & 1) == 0) {
        if (g_nRdroidZBufferMode == 1) {
          rdRaster_Select_Flat(puVar2,pbVar9);
        }
      }
      else {
        (**(code **)(pbVar5 + 0x18))(puVar2,pbVar9,0);
      }
    }
  }
  else if (fVar6 == 4.2039e-45) {
    switch((int)(param_1)) {
    case 0x0:
      if ((*pbVar5 & 1) == 0) {
        if (g_nRdroidZBufferMode == 1) {
          rdRaster_Select_Flat_2(puVar2,pbVar9);
        }
      }
      else {
        (**(code **)(pbVar5 + 0x18))(puVar2,pbVar9,0);
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
      local_4 = local_4 * 63.0;
      *(float *)(pbVar5 + 0x44) = local_4;
      if ((*pbVar5 & 1) == 0) {
        if (g_nRdroidZBufferMode == 1) {
          rdRaster_Select_TexLit(puVar2,pbVar9,local_4);
        }
      }
      else {
        (**(code **)(pbVar5 + 0x18))(puVar2,pbVar9,local_4);
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
      local_4 = local_4 * 63.0;
      *(float *)(pbVar5 + 0x44) = local_4;
      if ((*pbVar5 & 1) == 0) {
        if (g_nRdroidZBufferMode == 1) {
          rdRaster_Select_TexLit(puVar2,pbVar9,local_4);
        }
      }
      else {
        (**(code **)(pbVar5 + 0x18))(puVar2,pbVar9,local_4);
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
        if (g_nRdroidZBufferMode == 1) {
          rdRaster_Select_FlatLit(puVar2,pbVar9);
        }
      }
      else {
        (**(code **)(pbVar5 + 0x18))(puVar2,pbVar9,0);
      }
    }
  }
  else if (fVar6 == 5.60519e-45) {
    if ((**(byte **)(pbVar9 + 0x1c) & 1) == 0) {
      if (iVar10 == 0) {
        switch((int)(param_1)) {
        case 0x0:
          if ((*pbVar5 & 1) == 0) {
            if (g_nRdroidZBufferMode == 1) {
              rdRaster_Select_FlatLit_2(puVar2,pbVar9);
            }
          }
          else {
            (**(code **)(pbVar5 + 0x18))(puVar2,pbVar9,0);
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
          local_4 = local_4 * 63.0;
          *(float *)(pbVar5 + 0x44) = local_4;
          if ((*pbVar5 & 1) == 0) {
            if (g_nRdroidZBufferMode == 1) {
              rdRaster_Select_FlatLit_4(puVar2,pbVar9,local_4);
            }
          }
          else {
            (**(code **)(pbVar5 + 0x18))(puVar2,pbVar9,local_4);
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
          local_4 = local_4 * 63.0;
          *(float *)(pbVar5 + 0x44) = local_4;
          if ((*pbVar5 & 1) == 0) {
            if (g_nRdroidZBufferMode == 1) {
              rdRaster_Select_FlatLit_4(puVar2,pbVar9,local_4);
            }
          }
          else {
            (**(code **)(pbVar5 + 0x18))(puVar2,pbVar9,local_4);
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
            if (g_nRdroidZBufferMode == 1) {
              rdRaster_Select_FlatLit_6(puVar2,pbVar9);
            }
          }
          else {
            (**(code **)(pbVar5 + 0x18))(puVar2,pbVar9,0);
          }
        }
      }
      else if ((0 < iVar10) && (iVar10 < 3)) {
        switch((int)(param_1)) {
        case 0x0:
          if ((*pbVar5 & 1) == 0) {
            if (g_nRdroidZBufferMode == 1) {
              rdRaster_Select_FlatLit_8(puVar2,pbVar9);
            }
          }
          else {
            (**(code **)(pbVar5 + 0x18))(puVar2,pbVar9,0);
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
          local_4 = local_4 * 63.0;
          *(float *)(pbVar5 + 0x44) = local_4;
          if ((*pbVar5 & 1) == 0) {
            if (g_nRdroidZBufferMode == 1) {
              rdRaster_Select_FlatLit_10(puVar2,pbVar9,local_4);
            }
          }
          else {
            (**(code **)(pbVar5 + 0x18))(puVar2,pbVar9,local_4);
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
          local_4 = local_4 * 63.0;
          *(float *)(pbVar5 + 0x44) = local_4;
          if ((*pbVar5 & 1) == 0) {
            if (g_nRdroidZBufferMode == 1) {
              rdRaster_Select_FlatLit_10(puVar2,pbVar9,local_4);
            }
          }
          else {
            (**(code **)(pbVar5 + 0x18))(puVar2,pbVar9,local_4);
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
            if (g_nRdroidZBufferMode == 1) {
              rdRaster_Select_FlatLit_12(puVar2,pbVar9);
            }
          }
          else {
            (**(code **)(pbVar5 + 0x18))(puVar2,pbVar9,0);
          }
        }
      }
    }
    else if (iVar10 == 0) {
      switch((int)(param_1)) {
      case 0x0:
        if ((*pbVar5 & 1) == 0) {
          if (g_nRdroidZBufferMode == 1) {
            rdRaster_Select_FlatLit_3(puVar2,pbVar9);
          }
        }
        else {
          (**(code **)(pbVar5 + 0x18))(puVar2,pbVar9,0);
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
        local_4 = local_4 * 63.0;
        *(float *)(pbVar5 + 0x44) = local_4;
        if ((*pbVar5 & 1) == 0) {
          if (g_nRdroidZBufferMode == 1) {
            rdRaster_Select_FlatLit_5(puVar2,pbVar9,local_4);
          }
        }
        else {
          (**(code **)(pbVar5 + 0x18))(puVar2,pbVar9,local_4);
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
        local_4 = local_4 * 63.0;
        *(float *)(pbVar5 + 0x44) = local_4;
        if ((*pbVar5 & 1) == 0) {
          if (g_nRdroidZBufferMode == 1) {
            rdRaster_Select_FlatLit_5(puVar2,pbVar9,local_4);
          }
        }
        else {
          (**(code **)(pbVar5 + 0x18))(puVar2,pbVar9,local_4);
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
          if (g_nRdroidZBufferMode == 1) {
            rdRaster_Select_FlatLit_7(puVar2,pbVar9);
          }
        }
        else {
          (**(code **)(pbVar5 + 0x18))(puVar2,pbVar9,0);
        }
      }
    }
    else if ((0 < iVar10) && (iVar10 < 3)) {
      switch((int)(param_1)) {
      case 0x0:
        if ((*pbVar5 & 1) == 0) {
          if (g_nRdroidZBufferMode == 1) {
            rdRaster_Select_FlatLit_9(puVar2,pbVar9);
          }
        }
        else {
          (**(code **)(pbVar5 + 0x18))(puVar2,pbVar9,0);
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
        local_4 = local_4 * 63.0;
        *(float *)(pbVar5 + 0x44) = local_4;
        if ((*pbVar5 & 1) == 0) {
          if (g_nRdroidZBufferMode == 1) {
            rdRaster_Select_FlatLit_11(puVar2,pbVar9,local_4);
          }
        }
        else {
          (**(code **)(pbVar5 + 0x18))(puVar2,pbVar9,local_4);
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
        local_4 = local_4 * 63.0;
        *(float *)(pbVar5 + 0x44) = local_4;
        if ((*pbVar5 & 1) == 0) {
          if (g_nRdroidZBufferMode == 1) {
            rdRaster_Select_FlatLit_11(puVar2,pbVar9,local_4);
          }
        }
        else {
          (**(code **)(pbVar5 + 0x18))(puVar2,pbVar9,local_4);
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
          if (g_nRdroidZBufferMode == 1) {
            rdRaster_Select_FlatLit_13(puVar2,pbVar9);
          }
        }
        else {
          (**(code **)(pbVar5 + 0x18))(puVar2,pbVar9,0);
        }
      }
    }
  }
  DAT_005e6f98 = DAT_005e6f98 + 1;
  DAT_005e6f3c = DAT_005e6f3c + 1;
  return 1;
}
#undef local_4


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
  #define local_10 (*(undefined4 *)(_frame + (0x20 - 0x10)))
  
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


/* ---- 0x00451dd0  rdCanvas_DrawPoint ---- */
/* Clips a point with radius against the canvas rect and draws it */

void rdCanvas_DrawPoint(void *param_1,int param_2,int param_3,undefined4 param_4,float param_5,
                       int param_6,int param_7)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  #define local_8 (*(undefined1 (*)[4])(_frame + (0x20 - 0x8)))
  #define local_4 (*(undefined1 (*)[4])(_frame + (0x20 - 0x4)))
  
  iVar2 = _ftol();
  if ((((*(int *)((int)param_1 + 0x18) <= iVar2 + param_2) &&
       (param_2 - iVar2 <= *(int *)((int)param_1 + 0x20))) &&
      (*(int *)((int)param_1 + 0x1c) <= iVar2 + param_3)) &&
     (param_3 - iVar2 <= *(int *)((int)param_1 + 0x24))) {
    Math_SinCosTable(0,local_4,local_8);
    iVar2 = _ftol();
    iVar3 = _ftol();
    iVar2 = iVar2 + param_2;
    iVar3 = iVar3 + param_3;
    for (fVar1 = param_5; fVar1 <= 360.0; fVar1 = fVar1 + param_5) {
      Math_SinCosTable(fVar1,local_4,local_8);
      iVar4 = _ftol();
      iVar5 = _ftol();
      rdPrimit2_DrawLine(param_1,iVar2,iVar3,iVar4 + param_2,iVar5 + param_3,param_6,param_7);
      iVar2 = iVar4 + param_2;
      iVar3 = iVar5 + param_3;
    }
  }
  return;
}
#undef local_4
#undef local_8


/* ---- 0x004c04f0  rdCanvas_New ---- */
/* Rdcanvas.c: allocates a 0x28-byte canvas and initialises it */

uint * rdCanvas_New(uint param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6,
                   uint param_7,uint param_8)

{
  uint *canvas;
  
  canvas = (uint *)(*g_pSvcRdroid->pAlloc)
                             (0x28,s_C__grimjedi_Libs_RDroid_Engine_R_004f0edc,DAT_004f0ed8 + 4);
  if (canvas == (uint *)0x0) {
    return (uint *)0x0;
  }
  rdCanvas_Init(canvas,param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return canvas;
}

/* ---- 0x004c0550  rdCanvas_Init ---- */
/* flags bit 0: explicit clip rect, otherwise the whole surface */

int __cdecl
rdCanvas_Init(uint *canvas,uint flags,uint surface,uint zSurface,uint x0,uint y0,uint x1,uint y1,
             uint extra)

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
  canvas[2] = (uint)((float)(int)canvas[6] + (float)(int)((canvas[8] - canvas[6]) + 1) * 0.5);
  canvas[3] = (uint)((float)(int)canvas[7] + (float)(int)((canvas[9] - canvas[7]) + 1) * 0.5);
  return 1;
}

/* ---- 0x004c0610  rdCanvas_Free ---- */
void rdCanvas_Free(int param_1)

{
  if (param_1 != 0) {
    ((code *)Mem_DumpLog)(param_1);
    (*g_pSvcRdroid->pFree)(param_1);
  }
  return;
}
