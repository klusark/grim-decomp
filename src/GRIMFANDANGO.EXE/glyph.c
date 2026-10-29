/* GRIMFANDANGO.EXE :: glyph.c
 * functions 0x004ab910 .. 0x004abc80 (4 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004ab910  Glyph_Blit16 ---- */
void Glyph_Blit16(int param_1,undefined4 param_2,int *param_3)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined2 uVar8;
  int iVar9;
  undefined1 *puVar10;
  undefined2 *puVar11;
  int iVar12;
  char *pcVar13;
  undefined2 *puVar14;
  
  iVar2 = *(int *)(param_1 + 0xc);
  iVar9 = *(int *)(param_1 + 0x10);
  pcVar13 = *(char **)(param_1 + 8);
  piVar3 = (int *)*param_3;
  iVar4 = piVar3[5];
  iVar5 = piVar3[3];
  puVar14 = (undefined2 *)
            (((int)*(char *)(param_1 + 5) + param_3[3]) * iVar5 +
             ((int)*(char *)(param_1 + 6) + param_3[4]) * iVar4 + *piVar3);
  puVar10 = (undefined1 *)param_3[0xb];
  if (puVar10 == (undefined1 *)0x0) {
    puVar10 = &DAT_008d0880;
  }
  iVar6 = param_3[5];
  iVar7 = param_3[7];
  do {
    if (iVar9 == 0) {
      return;
    }
    puVar11 = puVar14;
    iVar12 = iVar2;
    if (0 < iVar2) {
      do {
        cVar1 = *pcVar13;
        pcVar13 = pcVar13 + 1;
        if (cVar1 == '\0') {
LAB_004ab9b2:
          puVar11 = (undefined2 *)((int)puVar11 + iVar5);
        }
        else {
          if (cVar1 == -0x80) {
            uVar8 = *(undefined2 *)(puVar10 + iVar7 * iVar5);
LAB_004ab9af:
            *puVar11 = uVar8;
            goto LAB_004ab9b2;
          }
          if (cVar1 == -1) {
            uVar8 = *(undefined2 *)(puVar10 + iVar6 * iVar5);
            goto LAB_004ab9af;
          }
        }
        iVar12 = iVar12 + -1;
      } while (iVar12 != 0);
    }
    puVar14 = (undefined2 *)((int)puVar14 + iVar4);
    iVar9 = iVar9 + -1;
  } while( true );
}

/* ---- 0x004ab9d0  Glyph_Blit8 ---- */
void Glyph_Blit8(int param_1,int param_2,int *param_3)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  int iVar6;
  byte *pbVar7;
  int iVar8;
  undefined1 *puVar9;
  int iVar10;
  
  iVar8 = *(int *)(param_1 + 0x10);
  iVar2 = *(int *)(param_1 + 0xc);
  pbVar7 = *(byte **)(param_1 + 8);
  iVar3 = ((int *)*param_3)[5];
  iVar6 = (int)*(char *)(param_1 + 6) - *(int *)(param_2 + 0x14);
  puVar9 = (undefined1 *)param_3[0xb];
  puVar4 = (undefined1 *)
           ((param_3[4] + *(int *)(param_2 + 0x14)) * iVar3 + (int)*(char *)(param_1 + 5) +
            param_3[3] + *(int *)*param_3);
  if (puVar9 == (undefined1 *)0x0) {
    puVar9 = &DAT_008d0880;
  }
  for (; iVar6 != 0; iVar6 = iVar6 + -1) {
    puVar5 = puVar4;
    iVar10 = iVar2;
    if (0 < iVar2) {
      do {
        *puVar5 = *puVar9;
        iVar10 = iVar10 + -1;
        puVar5 = puVar5 + 1;
      } while (iVar10 != 0);
    }
    puVar4 = puVar4 + iVar3;
  }
  iVar6 = (*(int *)(param_2 + 0x18) - iVar8) - (int)*(char *)(param_1 + 6);
  for (; iVar8 != 0; iVar8 = iVar8 + -1) {
    puVar5 = puVar4;
    iVar10 = iVar2;
    if (0 < iVar2) {
      do {
        bVar1 = *pbVar7;
        pbVar7 = pbVar7 + 1;
        iVar10 = iVar10 + -1;
        *puVar5 = puVar9[bVar1];
        puVar5 = puVar5 + 1;
      } while (iVar10 != 0);
    }
    puVar4 = puVar4 + iVar3;
  }
  for (; iVar6 != 0; iVar6 = iVar6 + -1) {
    puVar5 = puVar4;
    iVar8 = iVar2;
    if (0 < iVar2) {
      do {
        *puVar5 = *puVar9;
        iVar8 = iVar8 + -1;
        puVar5 = puVar5 + 1;
      } while (iVar8 != 0);
    }
    puVar4 = puVar4 + iVar3;
  }
  return;
}

/* ---- 0x004abae0  Glyph_Blit16Clipped ---- */
void Glyph_Blit16Clipped(int param_1,undefined4 param_2,int *param_3)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  undefined1 *puVar7;
  undefined2 *puVar8;
  int iVar9;
  char *pcVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  undefined2 *puVar16;
  char *pcVar17;
  #define local_1c (*(int *)(_frame + (0x30 - 0x1c)))
  
  iVar2 = *(int *)(*param_3 + 0xc);
  iVar3 = *(int *)(*param_3 + 0x14);
  piVar4 = (int *)param_3[1];
  iVar12 = (int)*(char *)(param_1 + 6) + param_3[4];
  iVar6 = (int)*(char *)(param_1 + 5) + param_3[3];
  iVar9 = *piVar4;
  iVar11 = iVar6;
  if (iVar6 <= iVar9) {
    iVar11 = iVar9;
  }
  iVar5 = piVar4[1];
  iVar11 = iVar11 - iVar6;
  iVar13 = iVar5;
  if (iVar5 < iVar12) {
    iVar13 = iVar12;
  }
  iVar13 = iVar13 - iVar12;
  iVar14 = *(int *)(param_1 + 0xc) + iVar6;
  if (piVar4[2] + iVar9 <= iVar14) {
    iVar14 = piVar4[2] + iVar9;
  }
  iVar15 = *(int *)(param_1 + 0x10) + iVar12;
  iVar9 = piVar4[3] + iVar5;
  if (iVar15 < piVar4[3] + iVar5) {
    iVar9 = iVar15;
  }
  if ((iVar11 < iVar14 - iVar6) && (iVar13 < iVar9 - iVar12)) {
    pcVar10 = (char *)(iVar13 * *(int *)(param_1 + 0xc) + *(int *)(param_1 + 8) + iVar11);
    puVar7 = (undefined1 *)param_3[0xb];
    puVar16 = (undefined2 *)((iVar11 + iVar6) * iVar2 + iVar3 * iVar12 + *(int *)*param_3);
    if (puVar7 == (undefined1 *)0x0) {
      puVar7 = &DAT_008d0880;
    }
    iVar5 = param_3[5];
    iVar15 = param_3[7];
    iVar11 = (iVar14 - iVar6) - iVar11;
    for (iVar13 = (iVar9 - iVar12) - iVar13; iVar13 != 0; iVar13 = iVar13 + -1) {
      if (((piVar4[1] <= iVar12) && (iVar12 < piVar4[1] + piVar4[3])) &&
         (puVar8 = puVar16, pcVar17 = pcVar10, local_1c = iVar11, 0 < iVar11)) {
        do {
          cVar1 = *pcVar17;
          if (cVar1 == '\0') {
LAB_004abc47:
            puVar8 = (undefined2 *)((int)puVar8 + iVar2);
          }
          else {
            iVar9 = iVar15;
            if ((cVar1 == -0x80) || (iVar9 = iVar5, cVar1 == -1)) {
              *puVar8 = *(undefined2 *)(puVar7 + iVar9 * iVar2);
              goto LAB_004abc47;
            }
          }
          local_1c = local_1c + -1;
          pcVar17 = pcVar17 + 1;
        } while (local_1c != 0);
      }
      puVar16 = (undefined2 *)((int)puVar16 + iVar3);
      pcVar10 = pcVar10 + *(int *)(param_1 + 0xc);
      iVar12 = iVar12 + 1;
    }
  }
  return;
}
#undef local_1c


/* ---- 0x004abc80  Glyph_Blit8Clipped ---- */
void Glyph_Blit8Clipped(int param_1,int param_2,int *param_3)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined1 *puVar7;
  int iVar8;
  undefined1 *puVar9;
  int iVar10;
  undefined1 *puVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  
  iVar10 = *(int *)(param_1 + 0x10);
  iVar8 = param_3[3] + (int)*(char *)(param_1 + 5);
  iVar1 = *(int *)(*param_3 + 0x14);
  piVar2 = (int *)param_3[1];
  iVar13 = (int)*(char *)(param_1 + 6) - *(int *)(param_2 + 0x14);
  iVar12 = param_3[4] + *(int *)(param_2 + 0x14);
  iVar14 = *piVar2;
  iVar4 = iVar8;
  if (iVar8 <= iVar14) {
    iVar4 = iVar14;
  }
  iVar4 = iVar4 - iVar8;
  iVar3 = piVar2[1];
  iVar5 = iVar3;
  if (iVar3 < iVar12) {
    iVar5 = iVar12;
  }
  iVar6 = *(int *)(param_1 + 0xc) + iVar8;
  if (iVar14 + piVar2[2] <= iVar6) {
    iVar6 = iVar14 + piVar2[2];
  }
  iVar14 = piVar2[3] + iVar3;
  if (iVar10 + iVar12 < piVar2[3] + iVar3) {
    iVar14 = iVar10 + iVar12;
  }
  if ((iVar4 < iVar6 - iVar8) && (iVar5 - iVar12 < iVar14 - iVar12)) {
    puVar11 = (undefined1 *)param_3[0xb];
    iVar14 = *(int *)(param_1 + 8) + iVar4;
    puVar7 = (undefined1 *)(iVar1 * iVar12 + *(int *)*param_3 + iVar4 + iVar8);
    if (puVar11 == (undefined1 *)0x0) {
      puVar11 = &DAT_008d0880;
    }
    iVar4 = (iVar6 - iVar8) - iVar4;
    for (; iVar13 != 0; iVar13 = iVar13 + -1) {
      if (((piVar2[1] <= iVar12) && (iVar12 < piVar2[1] + piVar2[3])) &&
         (puVar9 = puVar7, iVar8 = iVar4, 0 < iVar4)) {
        do {
          *puVar9 = *puVar11;
          puVar9 = puVar9 + 1;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
      puVar7 = puVar7 + iVar1;
      iVar12 = iVar12 + 1;
    }
    iVar13 = (*(int *)(param_2 + 0x18) - iVar10) - (int)*(char *)(param_1 + 6);
    for (; iVar10 != 0; iVar10 = iVar10 + -1) {
      if (((piVar2[1] <= iVar12) && (iVar12 < piVar2[1] + piVar2[3])) && (0 < iVar4)) {
        puVar9 = puVar7;
        iVar8 = iVar4;
        do {
          iVar8 = iVar8 + -1;
          *puVar9 = puVar11[(byte)puVar9[iVar14 - (int)puVar7]];
          puVar9 = puVar9 + 1;
        } while (iVar8 != 0);
      }
      iVar14 = iVar14 + *(int *)(param_1 + 0xc);
      puVar7 = puVar7 + iVar1;
      iVar12 = iVar12 + 1;
    }
    for (; iVar13 != 0; iVar13 = iVar13 + -1) {
      if (((piVar2[1] <= iVar12) && (iVar12 < piVar2[1] + piVar2[3])) &&
         (puVar9 = puVar7, iVar10 = iVar4, 0 < iVar4)) {
        do {
          *puVar9 = *puVar11;
          iVar10 = iVar10 + -1;
          puVar9 = puVar9 + 1;
        } while (iVar10 != 0);
      }
      puVar7 = puVar7 + iVar1;
      iVar12 = iVar12 + 1;
    }
  }
  return;
}
