/* GRIMFANDANGO.EXE :: rdmodel3.c
 * functions 0x0040a8c0 .. 0x0040ce90 (16 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0040a8c0  rdModel3_NewEntry ---- */
/* Clears a 0x90-byte model record and names it UNKNOWN. Source file Rdmodel3.c
   (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */

void rdModel3_NewEntry(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = param_1;
  for (iVar1 = 0x24; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  strncpy(param_1,s_UNKNOWN_004ddb8c,0x1f);
  *(undefined1 *)((int)param_1 + 0x1f) = 0;
  param_1[0x14] = 0;
  return;
}

/* ---- 0x0040a8f0  rdModel3_New ---- */
/* Loads a model: calls the custom loader hook if one is installed, otherwise allocates the record,
   rdModel3_Load, then rdModel3_LoadPostProcess. Source file Rdmodel3.c
   (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */

undefined4 * rdModel3_New(undefined4 param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  
  if (UINT_007f31f0 != 0) {
    puVar1 = (undefined4 *)(*(code *)UINT_007f31f0)(param_1,0);
    if (puVar1 == (undefined4 *)0x0) {
      return (undefined4 *)0x0;
    }
    rdModel3_LoadPostProcess(puVar1);
    return puVar1;
  }
  puVar1 = (undefined4 *)
           (*g_pSvcRdroid->pAlloc)
                     (0x90,s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,DAT_004ddb7c + 0xc);
  if (puVar1 != (undefined4 *)0x0) {
    puVar3 = puVar1;
    for (iVar2 = 0x24; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
    }
    iVar2 = rdModel3_Load(param_1,puVar1);
    if (iVar2 != 0) {
      rdModel3_LoadPostProcess(puVar1);
      return puVar1;
    }
  }
  rdModel3_Free(puVar1);
  return (undefined4 *)0x0;
}

/* ---- 0x0040a980  rdModel3_Load ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Opens the file; the magic 'MODL' selects rdModel3_LoadBinary, anything else is parsed by
   rdModel3_LoadText. Source file Rdmodel3.c (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */

undefined4 rdModel3_Load(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = param_1;
  iVar1 = (*g_pSvcRdroid->pFopen)(param_1,&DAT_004ddb18);
  if (iVar1 == 0) {
    return 0;
  }
  (*g_pSvcRdroid->pFread)(iVar1,&param_1,4);
  if (param_1 == 0x4d4f444c) {
    iVar2 = rdModel3_LoadBinary(iVar1,param_2);
    if (iVar2 != 0) {
      (*g_pSvcRdroid->pFclose)();
      return 1;
    }
    (*g_pSvcRdroid->pFclose)(iVar1);
    return 0;
  }
  (*g_pSvcRdroid->pFclose)(iVar1);
  uVar3 = ((code *)rdModel3_LoadText)(iVar2,param_2);
  return uVar3;
}
#endif


/* ---- 0x0040aa20  rdModel3_LoadText ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Parser of the text .3do format (stdConffile 'section:' lines). Source file Rdmodel3.c
   (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */

undefined4
rdModel3_LoadText(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,uint param_5,
                 uint param_6,uint param_7,uint param_8)

{
  char cVar1;
  int iVar2;
  void *pvVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined *puVar6;
  undefined *puVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  undefined *puVar12;
  uint *puVar13;
  char *pcVar14;
  uint *puVar15;
  uint unaff_retaddr;
  int *piStack00000024;
  uint uStack00000028;
  int iStack0000002c;
  uint in_stack_00000030;
  uint uStack00000034;
  uint uStack0000003c;
  uint in_stack_00000040;
  undefined4 in_stack_00000044;
  undefined4 in_stack_00000048;
  undefined4 in_stack_0000004c;
  undefined4 in_stack_00000050;
  undefined4 in_stack_00000054;
  undefined4 in_stack_00000058;
  undefined4 in_stack_0000005c;
  int in_stack_00000060;
  undefined4 in_stack_00000064;
  int in_stack_00000068;
  undefined4 in_stack_0000006c;
  undefined4 in_stack_00000070;
  undefined4 in_stack_00000074;
  int in_stack_00000078;
  uint in_stack_0000007c;
  char *in_stack_0002048c;
  int in_stack_00020490;
  char *pcVar16;
  
  FUN_004addf0();
  ((code *)rdModel3_NewEntry)();
  Str_FileNameFromPath(in_stack_0002048c);
  ((code *)strncpy)();
  *(undefined1 *)(in_stack_00020490 + 0x1f) = 0;
  iVar2 = ((code *)stdConffile_OpenRead)();
  if (iVar2 == 0) {
    return 0;
  }
  iVar2 = stdConffile_ReadLine();
  if (((iVar2 != 0) && (iVar2 = sscanf((char *)UINT_00900520,s_section___s_004ddd64), iVar2 == 1))
     && (iVar2 = stdConffile_ReadLine(), iVar2 != 0)) {
    sscanf((char *)UINT_00900520,s_3do__d__d_004ddd58);
    iVar2 = stdConffile_ReadLine();
    if (((iVar2 != 0) && (iVar2 = sscanf((char *)UINT_00900520,s_section___s_004ddd64), iVar2 == 1))
       && ((iVar2 = stdConffile_ReadLine(), iVar2 != 0 &&
           (iVar2 = sscanf((char *)UINT_00900520,s_materials__d_004ddd48), iVar2 == 1)))) {
      if (param_5 != 0) {
        if (0x7f < param_5) {
          (*g_pSvcRdroid->pAssertFail)();
        }
        iVar2 = (*g_pSvcRdroid->pAlloc)();
        *(int *)(in_stack_00020490 + 0x48) = iVar2;
        if (iVar2 == 0) goto LAB_0040b8c4;
        uVar10 = 0;
        if (param_5 != 0) {
          do {
            iVar2 = stdConffile_ReadLine();
            if ((iVar2 == 0) ||
               (iVar2 = sscanf((char *)UINT_00900520,s__d___s_004ddd28), iVar2 != 2))
            goto LAB_0040b8c4;
            uVar8 = 0xffffffff;
            pcVar14 = &STACK0X(0x00000088);
            do {
              pcVar16 = pcVar14;
              if (uVar8 == 0) break;
              uVar8 = uVar8 - 1;
              pcVar16 = pcVar14 + 1;
              cVar1 = *pcVar14;
              pcVar14 = pcVar16;
            } while (cVar1 != '\0');
            uVar8 = ~uVar8;
            pcVar14 = pcVar16 + -uVar8;
            pcVar16 = &STACK0X(0x00000488) + param_4 * 0x400;
            for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
              *(undefined4 *)pcVar16 = *(undefined4 *)pcVar14;
              pcVar14 = pcVar14 + 4;
              pcVar16 = pcVar16 + 4;
            }
            uVar10 = uVar10 + 1;
            for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
              *pcVar16 = *pcVar14;
              pcVar14 = pcVar14 + 1;
              pcVar16 = pcVar16 + 1;
            }
          } while (uVar10 < param_5);
        }
        uVar10 = 0;
        if (param_5 != 0) {
          pcVar14 = &STACK0X(0x00000488);
          do {
            pvVar3 = rdMaterial_Load(pcVar14,0,0);
            *(void **)(*(int *)(in_stack_00020490 + 0x48) + uVar10 * 4) = pvVar3;
            if (*(int *)(*(int *)(in_stack_00020490 + 0x48) + uVar10 * 4) == 0) goto LAB_0040b8c4;
            uVar10 = uVar10 + 1;
            pcVar14 = pcVar14 + 0x400;
          } while (uVar10 < param_5);
        }
      }
      *(uint *)(in_stack_00020490 + 0x4c) = param_5;
      iVar2 = stdConffile_ReadLine();
      if ((((iVar2 != 0) &&
           (iVar2 = sscanf((char *)UINT_00900520,s_section___s_004ddd64), iVar2 == 1)) &&
          (iVar2 = stdConffile_ReadLine(), iVar2 != 0)) &&
         (iVar2 = sscanf((char *)UINT_00900520,s_radius__f_004ddd1c), iVar2 == 1)) {
        *(undefined4 *)(in_stack_00020490 + 0x5c) = in_stack_00000044;
        iVar2 = stdConffile_ReadLine();
        if ((iVar2 != 0) &&
           (iVar2 = sscanf((char *)UINT_00900520,s_insert_offset__f__f__f_004ddd04), iVar2 == 3)) {
          *(undefined4 *)(in_stack_00020490 + 0x84) = param_3;
          *(undefined4 *)(in_stack_00020490 + 0x88) = param_1;
          *(undefined4 *)(in_stack_00020490 + 0x8c) = param_2;
          iVar2 = stdConffile_ReadLine();
          if ((iVar2 != 0) &&
             (iVar2 = sscanf((char *)UINT_00900520,s_geosets__d_004ddcf8), iVar2 == 1)) {
            uStack0000003c = 0;
            *(uint *)(in_stack_00020490 + 0x44) = in_stack_00000040;
            if (in_stack_00000040 != 0) {
              piStack00000024 = (int *)(in_stack_00020490 + 0x28);
              do {
                iVar2 = stdConffile_ReadLine();
                if (((iVar2 == 0) ||
                    (iVar2 = sscanf((char *)UINT_00900520,s_geoset__d_004ddcec), iVar2 != 1)) ||
                   ((iVar2 = stdConffile_ReadLine(), iVar2 == 0 ||
                    (iVar2 = sscanf((char *)UINT_00900520,s_meshes__d_004ddce0), iVar2 != 1))))
                goto LAB_0040b8c4;
                puVar4 = (undefined4 *)(*g_pSvcRdroid->pAlloc)();
                *piStack00000024 = (int)puVar4;
                if (puVar4 == (undefined4 *)0x0) goto LAB_0040b8c4;
                uStack00000034 = 0;
                for (uVar10 = param_6 * 0x1f & 0x3fffffff; uVar10 != 0; uVar10 = uVar10 - 1) {
                  *puVar4 = 0;
                  puVar4 = puVar4 + 1;
                }
                for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
                  *(undefined1 *)puVar4 = 0;
                  puVar4 = (undefined4 *)((int)puVar4 + 1);
                }
                piStack00000024[-1] = param_6;
                if (param_6 != 0) {
                  iStack0000002c = 0;
                  do {
                    iVar11 = *piStack00000024 + iStack0000002c;
                    *(uint *)(iVar11 + 0x20) = uStack00000034;
                    iVar2 = stdConffile_ReadLine();
                    if ((((iVar2 == 0) ||
                         (iVar2 = sscanf((char *)UINT_00900520,s_mesh__d_004ddcd4), iVar2 != 1)) ||
                        (iVar2 = stdConffile_ReadLine(), iVar2 == 0)) ||
                       (iVar2 = sscanf((char *)UINT_00900520,s_name__s_004ddcc8), iVar2 != 1))
                    goto LAB_0040b8c4;
                    ((code *)strncpy)();
                    *(undefined1 *)(iVar11 + 0x1f) = 0;
                    iVar2 = stdConffile_ReadLine();
                    if (((iVar2 == 0) ||
                        (iVar2 = sscanf((char *)UINT_00900520,s_radius__f_004ddd1c), iVar2 != 1)) ||
                       (iVar2 = stdConffile_ReadLine(), iVar2 == 0)) goto LAB_0040b8c4;
                    iVar2 = sscanf((char *)UINT_00900520,s_shadow__d_004ddcbc);
                    if (iVar2 == 1) {
                      *(undefined4 *)(iVar11 + 0x54) = in_stack_00000074;
                      iVar2 = stdConffile_ReadLine();
                      if (iVar2 == 0) goto LAB_0040b8c4;
                    }
                    iVar2 = sscanf((char *)UINT_00900520,s_geometrymode__d_004ddca8);
                    if ((((iVar2 != 1) || (iVar2 = stdConffile_ReadLine(), iVar2 == 0)) ||
                        ((iVar2 = sscanf((char *)UINT_00900520,s_lightingmode__d_004ddc94),
                         iVar2 != 1 ||
                         (((iVar2 = stdConffile_ReadLine(), iVar2 == 0 ||
                           (iVar2 = sscanf((char *)UINT_00900520,s_texturemode__d_004ddc84),
                           iVar2 != 1)) || (iVar2 = stdConffile_ReadLine(), iVar2 == 0)))))) ||
                       ((iVar2 = sscanf((char *)UINT_00900520,s_vertices__d_004ddc74), iVar2 != 1 ||
                        (0x200 < unaff_retaddr)))) goto LAB_0040b8c4;
                    *(undefined4 *)(iVar11 + 0x30) = 0;
                    *(undefined4 *)(iVar11 + 0x38) = 0;
                    *(undefined4 *)(iVar11 + 0x3c) = 0;
                    if (unaff_retaddr != 0) {
                      iVar2 = (*g_pSvcRdroid->pAlloc)();
                      *(int *)(iVar11 + 0x30) = iVar2;
                      if (iVar2 == 0) goto LAB_0040b8c4;
                      iVar2 = (*g_pSvcRdroid->pAlloc)();
                      *(int *)(iVar11 + 0x38) = iVar2;
                      if (iVar2 == 0) goto LAB_0040b8c4;
                      puVar4 = (undefined4 *)(*g_pSvcRdroid->pAlloc)();
                      *(undefined4 **)(iVar11 + 0x3c) = puVar4;
                      if (puVar4 == (undefined4 *)0x0) goto LAB_0040b8c4;
                      for (uVar10 = unaff_retaddr >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
                        *puVar4 = 0;
                        puVar4 = puVar4 + 1;
                      }
                      for (uVar10 = unaff_retaddr & 3; uVar10 != 0; uVar10 = uVar10 - 1) {
                        *(undefined1 *)puVar4 = 0;
                        puVar4 = (undefined4 *)((int)puVar4 + 1);
                      }
                    }
                    puVar4 = *(undefined4 **)(iVar11 + 0x30);
                    uVar10 = 0;
                    if (unaff_retaddr != 0) {
                      do {
                        iVar2 = stdConffile_ReadLine();
                        if ((iVar2 == 0) ||
                           (iVar2 = sscanf((char *)UINT_00900520,s__d___f__f__f__f_004ddc60),
                           iVar2 != 5)) goto LAB_0040b8c4;
                        *puVar4 = param_3;
                        puVar4[1] = param_1;
                        puVar4[2] = param_2;
                        puVar4 = puVar4 + 3;
                        *(undefined4 *)(*(int *)(iVar11 + 0x38) + uVar10 * 4) = in_stack_00000050;
                        uVar10 = uVar10 + 1;
                      } while (uVar10 < unaff_retaddr);
                    }
                    *(uint *)(iVar11 + 0x48) = unaff_retaddr;
                    iVar2 = stdConffile_ReadLine();
                    if (((iVar2 == 0) ||
                        (iVar2 = sscanf((char *)UINT_00900520,s_texture_vertices__d_004ddc48),
                        iVar2 != 1)) || (0x300 < param_7)) goto LAB_0040b8c4;
                    *(undefined4 *)(iVar11 + 0x34) = 0;
                    if (param_7 != 0) {
                      puVar4 = (undefined4 *)(*g_pSvcRdroid->pAlloc)();
                      *(undefined4 **)(iVar11 + 0x34) = puVar4;
                      if (puVar4 == (undefined4 *)0x0) goto LAB_0040b8c4;
                      uVar10 = 0;
                      if (param_7 != 0) {
                        do {
                          iVar2 = stdConffile_ReadLine();
                          if ((iVar2 == 0) ||
                             (iVar2 = sscanf((char *)UINT_00900520,s__d___f__f_004ddc3c), iVar2 != 3
                             )) goto LAB_0040b8c4;
                          *puVar4 = in_stack_00000070;
                          puVar4[1] = in_stack_00000058;
                          puVar4 = puVar4 + 2;
                          uVar10 = uVar10 + 1;
                        } while (uVar10 < param_7);
                      }
                    }
                    *(uint *)(iVar11 + 0x4c) = param_7;
                    iVar2 = stdConffile_ReadLine();
                    if (iVar2 == 0) goto LAB_0040b8c4;
                    *(undefined4 *)(iVar11 + 0x44) = 0;
                    if (unaff_retaddr != 0) {
                      iVar2 = (*g_pSvcRdroid->pAlloc)();
                      *(int *)(iVar11 + 0x44) = iVar2;
                      if (iVar2 == 0) goto LAB_0040b8c4;
                    }
                    uVar10 = 0;
                    if (unaff_retaddr != 0) {
                      iVar2 = 0;
                      do {
                        iVar5 = stdConffile_ReadLine();
                        if ((iVar5 == 0) ||
                           (iVar5 = sscanf((char *)UINT_00900520,s__d___f__f__f_004ddc2c),
                           iVar5 != 4)) goto LAB_0040b8c4;
                        uVar10 = uVar10 + 1;
                        *(undefined4 *)(iVar2 + *(int *)(iVar11 + 0x44)) = param_3;
                        *(undefined4 *)(iVar2 + 4 + *(int *)(iVar11 + 0x44)) = param_1;
                        *(undefined4 *)(iVar2 + 8 + *(int *)(iVar11 + 0x44)) = param_2;
                        iVar2 = iVar2 + 0xc;
                      } while (uVar10 < unaff_retaddr);
                    }
                    iVar2 = stdConffile_ReadLine();
                    if (((iVar2 == 0) ||
                        (iVar2 = sscanf((char *)UINT_00900520,s_faces__d_004ddc20), iVar2 != 1)) ||
                       (0x200 < param_8)) goto LAB_0040b8c4;
                    *(uint *)(iVar11 + 0x50) = param_8;
                    *(undefined4 *)(iVar11 + 0x40) = 0;
                    if (param_8 != 0) {
                      iVar2 = (*g_pSvcRdroid->pAlloc)();
                      *(int *)(iVar11 + 0x40) = iVar2;
                      if (iVar2 == 0) goto LAB_0040b8c4;
                    }
                    puVar15 = *(uint **)(iVar11 + 0x40);
                    uStack00000028 = 0;
                    if (param_8 != 0) {
                      puVar13 = puVar15 + 2;
                      do {
                        iVar2 = stdConffile_ReadLine();
                        if (iVar2 == 0) goto LAB_0040b8c4;
                        ((code *)FUN_00450220)();
                        ((code *)strtok)();
                        uVar10 = ((code *)strtok)();
                        puVar6 = atoi(uVar10);
                        *puVar15 = uStack00000028;
                        if (puVar6 == (undefined *)0xffffffff) {
                          puVar13[6] = 0;
                        }
                        else {
                          puVar13[6] = *(uint *)(*(int *)(in_stack_00020490 + 0x48) +
                                                (int)puVar6 * 4);
                        }
                        pcVar16 = &DAT_004ddc1c;
                        pcVar14 = (char *)((code *)strtok)();
                        iVar2 = sscanf(pcVar14,pcVar16);
                        if (iVar2 != 1) goto LAB_0040b8c4;
                        pcVar16 = &DAT_004ddc18;
                        pcVar14 = (char *)((code *)strtok)();
                        iVar2 = sscanf(pcVar14,pcVar16);
                        if (iVar2 != 1) goto LAB_0040b8c4;
                        pcVar16 = &DAT_004ddc18;
                        pcVar14 = (char *)((code *)strtok)();
                        iVar2 = sscanf(pcVar14,pcVar16);
                        if (iVar2 != 1) goto LAB_0040b8c4;
                        pcVar16 = &DAT_004ddc18;
                        pcVar14 = (char *)((code *)strtok)();
                        iVar2 = sscanf(pcVar14,pcVar16);
                        if (iVar2 != 1) goto LAB_0040b8c4;
                        pcVar16 = &DAT_004ddc14;
                        pcVar14 = (char *)((code *)strtok)();
                        iVar2 = sscanf(pcVar14,pcVar16);
                        if (iVar2 != 1) goto LAB_0040b8c4;
                        puVar13[10] = in_stack_0000007c;
                        uVar10 = ((code *)strtok)();
                        puVar6 = atoi(uVar10);
                        if ((puVar6 == (undefined *)0x0) || ((undefined *)0x18 < puVar6))
                        goto LAB_0040b8c4;
                        puVar13[3] = (uint)puVar6;
                        uVar10 = (*g_pSvcRdroid->pAlloc)();
                        puVar13[4] = uVar10;
                        if (uVar10 == 0) goto LAB_0040b8c4;
                        if (((byte *)puVar13[6] == (byte *)0x0) || ((*(byte *)puVar13[6] & 2) == 0))
                        {
                          puVar12 = (undefined *)0x0;
                          if (puVar6 != (undefined *)0x0) {
                            do {
                              uVar10 = ((code *)strtok)();
                              puVar7 = atoi(uVar10);
                              *(undefined **)(puVar13[4] + (int)puVar12 * 4) = puVar7;
                              ((code *)strtok)();
                              puVar12 = puVar12 + 1;
                            } while (puVar12 < puVar6);
                          }
                        }
                        else {
                          uVar10 = (*g_pSvcRdroid->pAlloc)();
                          puVar13[5] = uVar10;
                          if (uVar10 == 0) goto LAB_0040b8c4;
                          puVar12 = (undefined *)0x0;
                          if (puVar6 != (undefined *)0x0) {
                            do {
                              uVar10 = ((code *)strtok)();
                              puVar7 = atoi(uVar10);
                              *(undefined **)(puVar13[4] + (int)puVar12 * 4) = puVar7;
                              uVar10 = ((code *)strtok)();
                              puVar7 = atoi(uVar10);
                              *(undefined **)(puVar13[5] + (int)puVar12 * 4) = puVar7;
                              puVar12 = puVar12 + 1;
                            } while (puVar12 < puVar6);
                          }
                        }
                        puVar15 = puVar15 + 0x13;
                        puVar13 = puVar13 + 0x13;
                        uStack00000028 = uStack00000028 + 1;
                      } while (uStack00000028 < param_8);
                    }
                    iVar2 = stdConffile_ReadLine();
                    if (iVar2 == 0) goto LAB_0040b8c4;
                    uVar10 = 0;
                    if (*(int *)(iVar11 + 0x50) != 0) {
                      puVar4 = (undefined4 *)(*(int *)(iVar11 + 0x40) + 0x44);
                      do {
                        iVar2 = stdConffile_ReadLine();
                        if ((iVar2 == 0) ||
                           (iVar2 = sscanf((char *)UINT_00900520,s__d___f__f__f_004ddc2c),
                           iVar2 != 4)) goto LAB_0040b8c4;
                        puVar4[-1] = param_3;
                        *puVar4 = param_1;
                        puVar4[1] = param_2;
                        puVar4 = puVar4 + 0x13;
                        uVar10 = uVar10 + 1;
                      } while (uVar10 < *(uint *)(iVar11 + 0x50));
                    }
                    uStack00000034 = uStack00000034 + 1;
                    iStack0000002c = iStack0000002c + 0x7c;
                  } while (uStack00000034 < param_6);
                }
                uStack0000003c = uStack0000003c + 1;
                piStack00000024 = piStack00000024 + 2;
              } while (uStack0000003c < in_stack_00000040);
            }
            iVar2 = stdConffile_ReadLine();
            if ((((iVar2 != 0) &&
                 (iVar2 = sscanf((char *)UINT_00900520,s_section___s_004ddd64), iVar2 == 1)) &&
                (iVar2 = stdConffile_ReadLine(), iVar2 != 0)) &&
               (iVar2 = sscanf((char *)UINT_00900520,s_hierarchy_nodes__d_004ddbfc), iVar2 == 1)) {
              iVar2 = (*g_pSvcRdroid->pAlloc)();
              *(int *)(in_stack_00020490 + 0x58) = iVar2;
              if (iVar2 != 0) {
                uVar10 = 0;
                *(uint *)(in_stack_00020490 + 0x54) = in_stack_00000030;
                if (in_stack_00000030 != 0) {
                  iVar2 = 0;
                  do {
                    iVar11 = *(int *)(in_stack_00020490 + 0x58);
                    *(uint *)(iVar2 + 0x44 + iVar11) = uVar10;
                    iVar11 = iVar2 + iVar11;
                    iVar5 = stdConffile_ReadLine();
                    if ((iVar5 == 0) ||
                       (iVar5 = sscanf((char *)UINT_00900520,
                                       s__d___x__x__d__d__d__d__d__f__f___004ddbc4), iVar5 != 0x12))
                    goto LAB_0040b8c4;
                    if (in_stack_00000060 == -1) {
                      *(undefined4 *)(iVar11 + 0x54) = 0;
                    }
                    else {
                      *(int *)(iVar11 + 0x54) =
                           *(int *)(in_stack_00020490 + 0x58) + in_stack_00000060 * 0xb8;
                    }
                    if (in_stack_00000078 == -1) {
                      *(undefined4 *)(iVar11 + 0x5c) = 0;
                    }
                    else {
                      *(int *)(iVar11 + 0x5c) =
                           *(int *)(in_stack_00020490 + 0x58) + in_stack_00000078 * 0xb8;
                    }
                    if (in_stack_00000068 == -1) {
                      *(undefined4 *)(iVar11 + 0x60) = 0;
                    }
                    else {
                      *(int *)(iVar11 + 0x60) =
                           *(int *)(in_stack_00020490 + 0x58) + in_stack_00000068 * 0xb8;
                    }
                    uVar10 = uVar10 + 1;
                    *(undefined4 *)(iVar11 + 0x70) = param_3;
                    *(undefined4 *)(iVar11 + 0x74) = param_1;
                    *(undefined4 *)(iVar11 + 0x78) = param_2;
                    *(undefined4 *)(iVar11 + 0x7c) = in_stack_00000048;
                    *(undefined4 *)(iVar11 + 0x80) = in_stack_0000004c;
                    *(undefined4 *)(iVar11 + 0x84) = in_stack_00000054;
                    *(undefined4 *)(iVar11 + 100) = in_stack_0000005c;
                    *(undefined4 *)(iVar11 + 0x68) = in_stack_00000064;
                    *(undefined4 *)(iVar11 + 0x6c) = in_stack_0000006c;
                    iVar2 = iVar2 + 0xb8;
                  } while (uVar10 < in_stack_00000030);
                }
                ((code *)rdModel3_CountNodeChildren)();
                stdConffile_Close();
                return 1;
              }
            }
          }
        }
      }
    }
  }
LAB_0040b8c4:
  stdConffile_Close();
  return 0;
}
#endif


/* ---- 0x0040b8e0  rdModel3_LoadBinary ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Reader of the binary 'MODL' model format (materials, geometry sets, meshes, hierarchy nodes).
   Source file Rdmodel3.c (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */

undefined4 rdModel3_LoadBinary(int param_1,int param_2)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  int *piVar2;
  int *piVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  void *pvVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int *piVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  uint uVar15;
  char *name;
  #define iStack_24 (*(int *)(_frame + (0x40 - 0x24)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define iStack_18 (*(int *)(_frame + (0x40 - 0x18)))
  #define iStack_14 (*(int *)(_frame + (0x40 - 0x14)))
  #define iStack_c (*(int *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(int *)(_frame + (0x40 - 0x8)))
  #define uStack_4 (*(undefined4 *)(_frame + (0x40 - 0x4)))
  
  iVar12 = param_2;
  uVar6 = param_1;
  uVar15 = 0;
  local_1c = 0;
  rdModel3_NewEntry(param_2);
  (*g_pSvcRdroid->pFread)(param_1,&local_8,4);
  *(int *)(iVar12 + 0x4c) = local_8;
  *(undefined4 *)(iVar12 + 0x48) = 0;
  if (local_8 != 0) {
    local_1c = (*g_pSvcRdroid->pAlloc)
                         (local_8 << 5,s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,
                          DAT_004ddb84 + 0x10);
  }
  uVar10 = local_1c;
  if (*(int *)(iVar12 + 0x4c) != 0) {
    do {
      (*g_pSvcRdroid->pFread)(param_1,uVar10,0x20);
      uVar10 = uVar10 + 0x20;
      uVar15 = uVar15 + 1;
    } while (uVar15 < *(uint *)(iVar12 + 0x4c));
  }
  (*g_pSvcRdroid->pFread)(param_1,iVar12,0x20);
  (*g_pSvcRdroid->pFread)(param_1,iVar12 + 0x20,4);
  piVar1 = (int *)(iVar12 + 0x44);
  (*g_pSvcRdroid->pFread)(param_1,piVar1,4);
  param_1 = 0;
  if (0 < *piVar1) {
    piVar11 = (int *)(iVar12 + 0x24);
    do {
      (*g_pSvcRdroid->pFread)(uVar6,piVar11,4);
      puVar4 = (undefined4 *)
               (*g_pSvcRdroid->pAlloc)
                         (*piVar11 * 0x7c,s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,
                          DAT_004ddb84 + 0x20);
      piVar11[1] = (int)puVar4;
      for (uVar15 = *piVar11 * 0x1f & 0x3fffffff; uVar15 != 0; uVar15 = uVar15 - 1) {
        *puVar4 = 0;
        puVar4 = puVar4 + 1;
      }
      for (iVar9 = 0; iVar9 != 0; iVar9 = iVar9 + -1) {
        *(undefined1 *)puVar4 = 0;
        puVar4 = (undefined4 *)((int)puVar4 + 1);
      }
      iStack_24 = 0;
      if (0 < *piVar11) {
        iStack_14 = 0;
        do {
          iVar12 = piVar11[1] + iStack_14;
          (*g_pSvcRdroid->pFread)(uVar6,iVar12,0x20);
          (*g_pSvcRdroid->pFread)(uVar6,iVar12 + 0x20,4);
          (*g_pSvcRdroid->pFread)(uVar6,iVar12 + 0x24,4);
          (*g_pSvcRdroid->pFread)(uVar6,iVar12 + 0x28,4);
          (*g_pSvcRdroid->pFread)(uVar6,iVar12 + 0x2c,4);
          piVar2 = (int *)(iVar12 + 0x48);
          (*g_pSvcRdroid->pFread)(uVar6,piVar2,4);
          (*g_pSvcRdroid->pFread)(uVar6,iVar12 + 0x4c,4);
          piVar3 = (int *)(iVar12 + 0x50);
          (*g_pSvcRdroid->pFread)(uVar6,piVar3,4);
          if (*piVar2 != 0) {
            uVar5 = (*g_pSvcRdroid->pAlloc)
                              (*piVar2 * 0xc,s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,
                               DAT_004ddb84 + 0x30);
            *(undefined4 *)(iVar12 + 0x30) = uVar5;
            uVar5 = (*g_pSvcRdroid->pAlloc)
                              (*piVar2 << 2,s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,
                               DAT_004ddb84 + 0x31);
            *(undefined4 *)(iVar12 + 0x38) = uVar5;
            uVar5 = (*g_pSvcRdroid->pAlloc)
                              (*piVar2 << 2,s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,
                               DAT_004ddb84 + 0x32);
            *(undefined4 *)(iVar12 + 0x3c) = uVar5;
          }
          if (*(int *)(iVar12 + 0x4c) != 0) {
            uVar5 = (*g_pSvcRdroid->pAlloc)
                              (*(int *)(iVar12 + 0x4c) * 8,
                               s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,DAT_004ddb84 + 0x36);
            *(undefined4 *)(iVar12 + 0x34) = uVar5;
          }
          (*g_pSvcRdroid->pFread)(uVar6,*(undefined4 *)(iVar12 + 0x30),*piVar2 * 0xc);
          (*g_pSvcRdroid->pFread)(uVar6,*(undefined4 *)(iVar12 + 0x34),*(int *)(iVar12 + 0x4c) << 3)
          ;
          (*g_pSvcRdroid->pFread)(uVar6,*(undefined4 *)(iVar12 + 0x38),*piVar2 << 2);
          (*g_pSvcRdroid->pFread)(uVar6,*(undefined4 *)(iVar12 + 0x3c),*piVar2 << 2);
          if (*piVar3 != 0) {
            puVar4 = (undefined4 *)
                     (*g_pSvcRdroid->pAlloc)
                               (*piVar3 * 0x4c,s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,
                                DAT_004ddb84 + 0x40);
            *(undefined4 **)(iVar12 + 0x40) = puVar4;
            for (uVar15 = *piVar3 * 0x13 & 0x3fffffff; uVar15 != 0; uVar15 = uVar15 - 1) {
              *puVar4 = 0;
              puVar4 = puVar4 + 1;
            }
            for (iVar9 = 0; iVar9 != 0; iVar9 = iVar9 + -1) {
              *(undefined1 *)puVar4 = 0;
              puVar4 = (undefined4 *)((int)puVar4 + 1);
            }
          }
          iStack_c = 0;
          if (0 < *(int *)(iVar12 + 0x50)) {
            iStack_18 = 0;
            do {
              iVar9 = iStack_18 + *(int *)(iVar12 + 0x40);
              (*g_pSvcRdroid->pFread)(uVar6,iVar9,0x4c);
              if (*(int *)(iVar9 + 0x14) != 0) {
                uVar5 = (*g_pSvcRdroid->pAlloc)
                                  (*(int *)(iVar9 + 0x14) * 4,
                                   s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,DAT_004ddb84 + 0x49);
                *(undefined4 *)(iVar9 + 0x18) = uVar5;
                (*g_pSvcRdroid->pFread)(uVar6,uVar5,*(int *)(iVar9 + 0x14) << 2);
              }
              if (*(int *)(iVar9 + 0x1c) != 0) {
                uVar5 = (*g_pSvcRdroid->pAlloc)
                                  (*(int *)(iVar9 + 0x14) << 2,
                                   s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,DAT_004ddb84 + 0x4e);
                *(undefined4 *)(iVar9 + 0x1c) = uVar5;
                (*g_pSvcRdroid->pFread)(uVar6,uVar5,*(int *)(iVar9 + 0x14) << 2);
              }
              if (*(int *)(iVar9 + 0x20) == 0) {
                *(undefined4 *)(iVar9 + 0x20) = 0xffffffff;
              }
              else {
                (*g_pSvcRdroid->pFread)(uVar6,&uStack_4,4);
                *(undefined4 *)(iVar9 + 0x20) = uStack_4;
              }
              iStack_c = iStack_c + 1;
              iStack_18 = iStack_18 + 0x4c;
            } while (iStack_c < *(int *)(iVar12 + 0x50));
          }
          *(undefined4 *)(iVar12 + 0x44) = 0;
          if (*piVar2 != 0) {
            uVar5 = (*g_pSvcRdroid->pAlloc)
                              (*piVar2 * 0xc,s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,
                               DAT_004ddb84 + 0x5f);
            *(undefined4 *)(iVar12 + 0x44) = uVar5;
          }
          (*g_pSvcRdroid->pFread)(uVar6,*(undefined4 *)(iVar12 + 0x44),*piVar2 * 0xc);
          (*g_pSvcRdroid->pFread)(uVar6,iVar12 + 0x54,4);
          (*g_pSvcRdroid->pFread)(uVar6,iVar12 + 0x5c,4);
          (*g_pSvcRdroid->pFread)(uVar6,iVar12 + 0x60,4);
          (*g_pSvcRdroid->pFread)(uVar6,iVar12 + 100,0x18);
          iStack_14 = iStack_14 + 0x7c;
          iStack_24 = iStack_24 + 1;
          iVar12 = param_2;
        } while (iStack_24 < *piVar11);
      }
      param_1 = param_1 + 1;
      piVar11 = piVar11 + 2;
    } while (param_1 < *piVar1);
  }
  (*g_pSvcRdroid->pFread)(uVar6,iVar12 + 0x50,4);
  piVar11 = (int *)(iVar12 + 0x54);
  (*g_pSvcRdroid->pFread)(uVar6,piVar11,4);
  uVar5 = (*g_pSvcRdroid->pAlloc)
                    (*piVar11 * 0xb8,s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,DAT_004ddb84 + 0x6c
                    );
  *(undefined4 *)(iVar12 + 0x58) = uVar5;
  iVar9 = 0;
  param_1 = 0;
  if (0 < *piVar11) {
    do {
      iVar13 = iVar9 + *(int *)(iVar12 + 0x58);
      (*g_pSvcRdroid->pFread)(uVar6,iVar13,0xb8);
      if (*(int *)(iVar13 + 0x54) != 0) {
        (*g_pSvcRdroid->pFread)(uVar6,&param_2,4);
        *(int *)(iVar13 + 0x54) = *(int *)(iVar12 + 0x58) + param_2 * 0xb8;
      }
      if (*(int *)(iVar13 + 0x5c) != 0) {
        (*g_pSvcRdroid->pFread)(uVar6,&param_2,4);
        *(int *)(iVar13 + 0x5c) = *(int *)(iVar12 + 0x58) + param_2 * 0xb8;
      }
      if (*(int *)(iVar13 + 0x60) != 0) {
        (*g_pSvcRdroid->pFread)(uVar6,&param_2,4);
        *(int *)(iVar13 + 0x60) = *(int *)(iVar12 + 0x58) + param_2 * 0xb8;
      }
      param_1 = param_1 + 1;
      iVar9 = iVar9 + 0xb8;
    } while (param_1 < *(int *)(iVar12 + 0x54));
  }
  (*g_pSvcRdroid->pFread)(uVar6,iVar12 + 0x5c,4);
  (*g_pSvcRdroid->pFread)(uVar6,iVar12 + 0x60,0x18);
  (*g_pSvcRdroid->pFread)(uVar6,iVar12 + 0x78,0xc);
  (*g_pSvcRdroid->pFread)(uVar6,iVar12 + 0x84,0xc);
  if (*(int *)(iVar12 + 0x4c) != 0) {
    uVar6 = (*g_pSvcRdroid->pAlloc)
                      (*(int *)(iVar12 + 0x4c) * 4,s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,
                       DAT_004ddb84 + 0x8e);
    *(undefined4 *)(iVar12 + 0x48) = uVar6;
  }
  uVar15 = 0;
  name = (char *)local_1c;
  if (*(int *)(iVar12 + 0x4c) != 0) {
    do {
      pvVar7 = rdMaterial_Load(name,0,0);
      name = name + 0x20;
      *(void **)(*(int *)(iVar12 + 0x48) + uVar15 * 4) = pvVar7;
      uVar15 = uVar15 + 1;
    } while (uVar15 < *(uint *)(iVar12 + 0x4c));
  }
  param_1 = 0;
  if (0 < *piVar1) {
    piVar11 = (int *)(iVar12 + 0x24);
    do {
      iStack_24 = 0;
      if (0 < *piVar11) {
        param_2 = 0;
        do {
          iVar13 = 0;
          iVar9 = param_2 + piVar11[1];
          if (0 < *(int *)(iVar9 + 0x50)) {
            iVar14 = 0;
            do {
              iVar8 = iVar14 + *(int *)(iVar9 + 0x40);
              if (*(int *)(iVar8 + 0x20) < 0) {
                *(undefined4 *)(iVar8 + 0x20) = 0;
              }
              else {
                *(undefined4 *)(iVar8 + 0x20) =
                     *(undefined4 *)(*(int *)(iVar12 + 0x48) + *(int *)(iVar8 + 0x20) * 4);
              }
              iVar13 = iVar13 + 1;
              iVar14 = iVar14 + 0x4c;
            } while (iVar13 < *(int *)(iVar9 + 0x50));
          }
          iStack_24 = iStack_24 + 1;
          param_2 = param_2 + 0x7c;
        } while (iStack_24 < *piVar11);
      }
      param_1 = param_1 + 1;
      piVar11 = piVar11 + 2;
    } while (param_1 < *piVar1);
  }
  if (local_1c != 0) {
    (*g_pSvcRdroid->pFree)(local_1c);
  }
  return 1;
}
#undef iStack_14
#undef iStack_18
#undef iStack_24
#undef iStack_c
#undef local_1c
#undef local_8
#undef uStack_4

#endif


/* ---- 0x0040c090  rdModel3_LoadPostProcess ---- */
/* Computes everything derived after loading: bounding boxes, radii, face and vertex normals, node
   child counts. Source file Rdmodel3.c (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */

void rdModel3_LoadPostProcess(undefined4 param_1)

{
  rdModel3_CalcBoundingBoxes(param_1);
  rdModel3_CalcRadii(param_1);
  rdModel3_CalcFaceNormals(param_1);
  rdModel3_CalcVertexNormals(param_1);
  rdModel3_CountNodeChildren(param_1);
  rdModel3_BuildBoundingBoxCorners(param_1);
  return;
}

/* ---- 0x0040c0d0  rdModel3_Free ---- */
/* Frees a model (custom free hook if installed, else rdModel3_FreeEntry and the record). Source
   file Rdmodel3.c (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */

void rdModel3_Free(int param_1)

{
  if (param_1 != 0) {
    if (UINT_007f31f4 != 0) {
      (*(code *)UINT_007f31f4)();
      return;
    }
    rdModel3_FreeEntry(param_1);
    (*g_pSvcRdroid->pFree)(param_1);
  }
  return;
}

/* ---- 0x0040c100  rdModel3_FreeEntry ---- */
/* Frees the contents of a model: materials, geometry sets, meshes, vertices, faces, hierarchy
   nodes. Source file Rdmodel3.c (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */

void rdModel3_FreeEntry(int param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint *puVar2;
  int *piVar3;
  int iVar4;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  if (param_1 != 0) {
    puVar2 = (uint *)(param_1 + 0x24);
    local_4 = 0;
    if (*(int *)(param_1 + 0x44) != 0) {
      do {
        local_8 = 0;
        if (*puVar2 != 0) {
          piVar3 = (int *)(puVar2[1] + 0x34);
          do {
            if (piVar3[-1] != 0) {
              (*g_pSvcRdroid->pFree)(piVar3[-1]);
            }
            if (*piVar3 != 0) {
              (*g_pSvcRdroid->pFree)(*piVar3);
            }
            iVar4 = piVar3[3];
            if (iVar4 != 0) {
              uVar1 = 0;
              if (piVar3[7] != 0) {
                do {
                  FUN_00450260(iVar4);
                  iVar4 = iVar4 + 0x4c;
                  uVar1 = uVar1 + 1;
                } while (uVar1 < (uint)piVar3[7]);
              }
              (*g_pSvcRdroid->pFree)(piVar3[3]);
            }
            if (piVar3[1] != 0) {
              (*g_pSvcRdroid->pFree)(piVar3[1]);
            }
            if (piVar3[2] != 0) {
              (*g_pSvcRdroid->pFree)(piVar3[2]);
            }
            if (piVar3[4] != 0) {
              (*g_pSvcRdroid->pFree)(piVar3[4]);
            }
            if (piVar3[9] != 0) {
              (*g_pSvcRdroid->pFree)(piVar3[9]);
            }
            piVar3 = piVar3 + 0x1f;
            local_8 = local_8 + 1;
          } while (local_8 < *puVar2);
        }
        if (puVar2[1] != 0) {
          (*g_pSvcRdroid->pFree)(puVar2[1]);
        }
        puVar2 = puVar2 + 2;
        local_4 = local_4 + 1;
      } while (local_4 < *(uint *)(param_1 + 0x44));
    }
    if (*(int *)(param_1 + 0x58) != 0) {
      (*g_pSvcRdroid->pFree)(*(int *)(param_1 + 0x58));
    }
    uVar1 = 0;
    if (*(int *)(param_1 + 0x4c) != 0) {
      do {
        rdMaterial_Free(*(undefined4 *)(*(int *)(param_1 + 0x48) + uVar1 * 4));
        uVar1 = uVar1 + 1;
      } while (uVar1 < *(uint *)(param_1 + 0x4c));
    }
    if (*(int *)(param_1 + 0x48) != 0) {
      (*g_pSvcRdroid->pFree)(*(int *)(param_1 + 0x48));
    }
  }
  return;
}
#undef local_4
#undef local_8


/* ---- 0x0040c280  rdModel3_BuildBoundingBoxCorners ---- */
/* Allocates 0xc0 bytes per mesh and fills the 8 corner points of its bounding box from the min/max
   values. Source file Rdmodel3.c (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */

void rdModel3_BuildBoundingBoxCorners(int param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint *puVar5;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0;
  if (*(int *)(param_1 + 0x44) == 0) {
    return;
  }
  puVar5 = (uint *)(param_1 + 0x24);
  do {
    uVar3 = 0;
    if (*puVar5 != 0) {
      iVar2 = 0;
      do {
        iVar4 = iVar2 + puVar5[1];
        if (*(int *)(iVar4 + 0x54) != 0) {
          if (*(int *)(iVar4 + 0x58) != 0) {
            (*g_pSvcRdroid->pFree)(*(int *)(iVar4 + 0x58));
          }
          puVar1 = (undefined4 *)
                   (*g_pSvcRdroid->pAlloc)
                             (0xc0,s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,DAT_004ddb88 + 0xf);
          *(undefined4 **)(iVar4 + 0x58) = puVar1;
          if (puVar1 == (undefined4 *)0x0) {
            *(undefined4 *)(iVar4 + 0x54) = 0;
            return;
          }
          *puVar1 = *(undefined4 *)(iVar4 + 0x70);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 4) = *(undefined4 *)(iVar4 + 0x74);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 8) = *(undefined4 *)(iVar4 + 0x78);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0xc) = *(undefined4 *)(iVar4 + 0x70);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x10) = *(undefined4 *)(iVar4 + 0x68);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x14) = *(undefined4 *)(iVar4 + 0x78);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x18) = *(undefined4 *)(iVar4 + 100);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x1c) = *(undefined4 *)(iVar4 + 0x68);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x20) = *(undefined4 *)(iVar4 + 0x78);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x24) = *(undefined4 *)(iVar4 + 100);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x28) = *(undefined4 *)(iVar4 + 0x74);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x2c) = *(undefined4 *)(iVar4 + 0x78);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x30) = *(undefined4 *)(iVar4 + 0x70);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x34) = *(undefined4 *)(iVar4 + 0x74);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x38) = *(undefined4 *)(iVar4 + 0x6c);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x3c) = *(undefined4 *)(iVar4 + 0x70);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x40) = *(undefined4 *)(iVar4 + 0x68);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x44) = *(undefined4 *)(iVar4 + 0x6c);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x48) = *(undefined4 *)(iVar4 + 100);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x4c) = *(undefined4 *)(iVar4 + 0x68);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x50) = *(undefined4 *)(iVar4 + 0x6c);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x54) = *(undefined4 *)(iVar4 + 100);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x58) = *(undefined4 *)(iVar4 + 0x74);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x5c) = *(undefined4 *)(iVar4 + 0x6c);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x60) = *(undefined4 *)(iVar4 + 100);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 100) = *(undefined4 *)(iVar4 + 0x68);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x68) = *(undefined4 *)(iVar4 + 0x6c);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x6c) = *(undefined4 *)(iVar4 + 0x70);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x70) = *(undefined4 *)(iVar4 + 0x74);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x74) = *(undefined4 *)(iVar4 + 0x6c);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x78) = *(undefined4 *)(iVar4 + 0x70);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x7c) = *(undefined4 *)(iVar4 + 0x74);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x80) = *(undefined4 *)(iVar4 + 0x78);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x84) = *(undefined4 *)(iVar4 + 100);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x88) = *(undefined4 *)(iVar4 + 0x68);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x8c) = *(undefined4 *)(iVar4 + 0x78);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x90) = *(undefined4 *)(iVar4 + 100);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x94) = *(undefined4 *)(iVar4 + 0x74);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x98) = *(undefined4 *)(iVar4 + 0x6c);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0x9c) = *(undefined4 *)(iVar4 + 0x70);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0xa0) = *(undefined4 *)(iVar4 + 0x68);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0xa4) = *(undefined4 *)(iVar4 + 0x6c);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0xa8) = *(undefined4 *)(iVar4 + 0x70);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0xac) = *(undefined4 *)(iVar4 + 0x68);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0xb0) = *(undefined4 *)(iVar4 + 0x78);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0xb4) = *(undefined4 *)(iVar4 + 100);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0xb8) = *(undefined4 *)(iVar4 + 0x74);
          *(undefined4 *)(*(int *)(iVar4 + 0x58) + 0xbc) = *(undefined4 *)(iVar4 + 0x78);
        }
        uVar3 = uVar3 + 1;
        iVar2 = iVar2 + 0x7c;
      } while (uVar3 < *puVar5);
    }
    local_4 = local_4 + 1;
    puVar5 = puVar5 + 2;
    if (*(uint *)(param_1 + 0x44) <= local_4) {
      return;
    }
  } while( true );
}
#undef local_4


/* ---- 0x0040c520  rdModel3_CalcBoundingBoxes ---- */
/* Computes the min/max box of every mesh, of the whole model (through
   rdModel3_AccumulateNodeBounds), and the model's center and radius. Source file Rdmodel3.c
   (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */

void rdModel3_CalcBoundingBoxes(uint param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  float *pfVar6;
  int iVar7;
  int iVar8;
  uint *puVar9;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar4 = param_1;
  *(undefined4 *)(param_1 + 0x60) = 0x7f7fc99e;
  *(undefined4 *)(param_1 + 100) = 0x7f7fc99e;
  *(undefined4 *)(param_1 + 0x68) = 0x7f7fc99e;
  *(undefined4 *)(param_1 + 0x6c) = 0xff7fc99e;
  *(undefined4 *)(param_1 + 0x70) = 0xff7fc99e;
  *(undefined4 *)(param_1 + 0x74) = 0xff7fc99e;
  local_4 = 0;
  if (*(int *)(param_1 + 0x44) != 0) {
    puVar9 = (uint *)(param_1 + 0x24);
    do {
      iVar7 = 0;
      param_1 = 0;
      if (*puVar9 != 0) {
        do {
          iVar5 = iVar7 + puVar9[1];
          iVar8 = *(int *)(iVar5 + 0x48);
          *(undefined4 *)(iVar5 + 100) = 0x7f7fc99e;
          *(undefined4 *)(iVar5 + 0x68) = 0x7f7fc99e;
          *(undefined4 *)(iVar5 + 0x6c) = 0x7f7fc99e;
          *(undefined4 *)(iVar5 + 0x70) = 0xff7fc99e;
          *(undefined4 *)(iVar5 + 0x74) = 0xff7fc99e;
          *(undefined4 *)(iVar5 + 0x78) = 0xff7fc99e;
          if (iVar8 != 0) {
            pfVar6 = *(float **)(iVar5 + 0x30);
            do {
              if (*pfVar6 < *(float *)(iVar5 + 100)) {
                *(float *)(iVar5 + 100) = *pfVar6;
              }
              if (pfVar6[1] < *(float *)(iVar5 + 0x68)) {
                *(float *)(iVar5 + 0x68) = pfVar6[1];
              }
              if (pfVar6[2] < *(float *)(iVar5 + 0x6c)) {
                *(float *)(iVar5 + 0x6c) = pfVar6[2];
              }
              if (*(float *)(iVar5 + 0x70) < *pfVar6) {
                *(float *)(iVar5 + 0x70) = *pfVar6;
              }
              if (*(float *)(iVar5 + 0x74) < pfVar6[1]) {
                *(float *)(iVar5 + 0x74) = pfVar6[1];
              }
              if (*(float *)(iVar5 + 0x78) < pfVar6[2]) {
                *(float *)(iVar5 + 0x78) = pfVar6[2];
              }
              pfVar6 = pfVar6 + 3;
              iVar8 = iVar8 + -1;
            } while (iVar8 != 0);
          }
          param_1 = param_1 + 1;
          iVar7 = iVar7 + 0x7c;
        } while (param_1 < *puVar9);
      }
      local_4 = local_4 + 1;
      puVar9 = puVar9 + 2;
    } while (local_4 < *(uint *)(iVar4 + 0x44));
  }
  *(undefined4 *)(iVar4 + 0x60) = 0x7f7fc99e;
  *(undefined4 *)(iVar4 + 100) = 0x7f7fc99e;
  *(undefined4 *)(iVar4 + 0x68) = 0x7f7fc99e;
  *(undefined4 *)(iVar4 + 0x6c) = 0xff7fc99e;
  *(undefined4 *)(iVar4 + 0x70) = 0xff7fc99e;
  *(undefined4 *)(iVar4 + 0x74) = 0xff7fc99e;
  rdModel3_AccumulateNodeBounds(iVar4,*(undefined4 *)(iVar4 + 0x58),g_MatrixIdentity);
  fVar3 = *(float *)(iVar4 + 0x60) - *(float *)(iVar4 + 0x6c);
  fVar1 = *(float *)(iVar4 + 100) - *(float *)(iVar4 + 0x70);
  fVar2 = *(float *)(iVar4 + 0x68) - *(float *)(iVar4 + 0x74);
  *(float *)(iVar4 + 0x78) =
       (*(float *)(iVar4 + 0x6c) - *(float *)(iVar4 + 0x60)) * 0.5 + *(float *)(iVar4 + 0x60);
  *(float *)(iVar4 + 0x7c) =
       (*(float *)(iVar4 + 0x70) - *(float *)(iVar4 + 100)) * 0.5 + *(float *)(iVar4 + 100);
  *(float *)(iVar4 + 0x80) =
       (*(float *)(iVar4 + 0x74) - *(float *)(iVar4 + 0x68)) * 0.5 + *(float *)(iVar4 + 0x68);
  *(float *)(iVar4 + 0x5c) = SQRT(fVar2 * fVar2 + fVar1 * fVar1 + fVar3 * fVar3) * 0.5;
  return;
}
#undef local_4


/* ---- 0x0040c710  rdModel3_AccumulateNodeBounds ---- */
/* Recursively composes the node matrices (angles, offset, pivot) and accumulates the transformed
   mesh boxes into the model bounds. Source file Rdmodel3.c
   (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */

void rdModel3_AccumulateNodeBounds(int param_1,int param_2,float *param_3)

{
  unsigned char _frame[0xc0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  float *a;
  uint uVar2;
  int iVar3;
  #define local_a8 (*(float *)(_frame + (0xc0 - 0xa8)))
  #define local_a4 (*(float (*)[2])(_frame + (0xc0 - 0xa4)))
  #define local_9c (*(float (*)[3])(_frame + (0xc0 - 0x9c)))
  #define local_90 (*(float (*)[12])(_frame + (0xc0 - 0x90)))
  #define local_60 (*(float (*)[12])(_frame + (0xc0 - 0x60)))
  #define local_30 (*(undefined1 (*)[48])(_frame + (0xc0 - 0x30)))
  
  Angles_ToMatrix(local_30,param_2 + 0x7c,param_2 + 0x70);
  Matrix_BuildTranslation(local_90,(float *)(param_2 + 100));
  Matrix_Multiply(local_90,local_30);
  iVar3 = *(int *)(param_2 + 0x54);
  if (iVar3 != 0) {
    local_9c[0] = -*(float *)(iVar3 + 100);
    local_9c[1] = -*(float *)(iVar3 + 0x68);
    local_9c[2] = -*(float *)(iVar3 + 0x6c);
    Matrix_SetTranslation(local_90,local_9c);
  }
  Matrix_Mul34(local_60,param_3,local_90);
  iVar3 = *(int *)(param_2 + 0x4c);
  if (iVar3 != -1) {
    iVar1 = *(int *)(param_1 + 0x28);
    uVar2 = 0;
    a = *(float **)(iVar1 + 0x30 + iVar3 * 0x7c);
    if (*(int *)(iVar1 + 0x48 + iVar3 * 0x7c) != 0) {
      do {
        Vec3_Sub(&local_a8,a,local_60);
        if (*(float *)(param_1 + 0x6c) < local_a8) {
          *(float *)(param_1 + 0x6c) = local_a8;
        }
        if (*(float *)(param_1 + 0x70) < local_a4[0]) {
          *(float *)(param_1 + 0x70) = local_a4[0];
        }
        if (*(float *)(param_1 + 0x74) < local_a4[1]) {
          *(float *)(param_1 + 0x74) = local_a4[1];
        }
        if (local_a8 < *(float *)(param_1 + 0x60)) {
          *(float *)(param_1 + 0x60) = local_a8;
        }
        if (local_a4[0] < *(float *)(param_1 + 100)) {
          *(float *)(param_1 + 100) = local_a4[0];
        }
        if (local_a4[1] < *(float *)(param_1 + 0x68)) {
          *(float *)(param_1 + 0x68) = local_a4[1];
        }
        a = a + 3;
        uVar2 = uVar2 + 1;
      } while (uVar2 < *(uint *)(iVar1 + iVar3 * 0x7c + 0x48));
    }
  }
  if (*(int *)(param_2 + 0x58) != 0) {
    iVar3 = *(int *)(param_2 + 0x5c);
    uVar2 = 0;
    if (*(int *)(param_2 + 0x58) != 0) {
      do {
        rdModel3_AccumulateNodeBounds(param_1,iVar3,local_60);
        iVar3 = *(int *)(iVar3 + 0x60);
        uVar2 = uVar2 + 1;
      } while (uVar2 < *(uint *)(param_2 + 0x58));
    }
  }
  return;
}
#undef local_30
#undef local_60
#undef local_90
#undef local_9c
#undef local_a4
#undef local_a8


/* ---- 0x0040c8c0  rdModel3_CalcRadii ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Computes the bounding radius of every mesh (largest vertex distance) and of the model. Source
   file Rdmodel3.c (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */

void rdModel3_CalcRadii(int param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float *pfVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar6 = 0;
  if (*(int *)(param_1 + 0x24) != 0) {
    piVar4 = (int *)(*(int *)(param_1 + 0x28) + 0x48);
    do {
      pfVar3 = (float *)piVar4[-6];
      fVar1 = 0.0;
      for (iVar5 = *piVar4; iVar5 != 0; iVar5 = iVar5 + -1) {
        fVar2 = SQRT(*pfVar3 * *pfVar3 + pfVar3[2] * pfVar3[2] + pfVar3[1] * pfVar3[1]);
        if (fVar1 < fVar2) {
          fVar1 = fVar2;
        }
        pfVar3 = pfVar3 + 3;
      }
      uVar6 = uVar6 + 1;
      piVar4[6] = PUN(int,(float)(fVar1 * 0.1 + fVar1));
      piVar4 = piVar4 + 0x1f;
    } while (uVar6 < *(uint *)(param_1 + 0x24));
  }
  _DAT_007f3200 = 0;
  rdModel3_AccumulateNodeRadius(param_1,*(undefined4 *)(param_1 + 0x58),g_MatrixIdentity);
  return;
}
#undef local_4

#endif


/* ---- 0x0040c970  rdModel3_AccumulateNodeRadius ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Recursive helper of rdModel3_CalcRadii: composes node matrices and updates the radius. Source
   file Rdmodel3.c (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */

void rdModel3_AccumulateNodeRadius(int param_1,int param_2,float *param_3)

{
  unsigned char _frame[0xc0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  float fVar2;
  float *a;
  uint uVar3;
  int iVar4;
  #define local_a8 (*(float (*)[3])(_frame + (0xc0 - 0xa8)))
  #define local_9c (*(float (*)[3])(_frame + (0xc0 - 0x9c)))
  #define local_90 (*(float (*)[12])(_frame + (0xc0 - 0x90)))
  #define local_60 (*(float (*)[12])(_frame + (0xc0 - 0x60)))
  #define local_30 (*(undefined1 (*)[48])(_frame + (0xc0 - 0x30)))
  
  Angles_ToMatrix(local_30,param_2 + 0x7c,param_2 + 0x70);
  Matrix_BuildTranslation(local_90,(float *)(param_2 + 100));
  Matrix_Multiply(local_90,local_30);
  iVar4 = *(int *)(param_2 + 0x54);
  if (iVar4 != 0) {
    local_9c[0] = -*(float *)(iVar4 + 100);
    local_9c[1] = -*(float *)(iVar4 + 0x68);
    local_9c[2] = -*(float *)(iVar4 + 0x6c);
    Matrix_SetTranslation(local_90,local_9c);
  }
  Matrix_Mul34(local_60,param_3,local_90);
  iVar4 = *(int *)(param_2 + 0x4c);
  if (iVar4 != -1) {
    iVar1 = *(int *)(param_1 + 0x28);
    uVar3 = 0;
    a = *(float **)(iVar1 + 0x30 + iVar4 * 0x7c);
    if (*(int *)(iVar1 + 0x48 + iVar4 * 0x7c) != 0) {
      do {
        Vec3_Sub(local_a8,a,local_60);
        fVar2 = SQRT(local_a8[2] * local_a8[2] +
                     local_a8[1] * local_a8[1] + local_a8[0] * local_a8[0]);
        if (_DAT_007f3200 < fVar2) {
          _DAT_007f3200 = fVar2;
        }
        a = a + 3;
        uVar3 = uVar3 + 1;
      } while (uVar3 < *(uint *)(iVar1 + iVar4 * 0x7c + 0x48));
    }
  }
  if (*(int *)(param_2 + 0x58) != 0) {
    iVar4 = *(int *)(param_2 + 0x5c);
    uVar3 = 0;
    if (*(int *)(param_2 + 0x58) != 0) {
      do {
        rdModel3_AccumulateNodeRadius(param_1,iVar4,local_60);
        iVar4 = *(int *)(iVar4 + 0x60);
        uVar3 = uVar3 + 1;
      } while (uVar3 < *(uint *)(param_2 + 0x58));
    }
  }
  return;
}
#undef local_30
#undef local_60
#undef local_90
#undef local_9c
#undef local_a8


/* ---- 0x0040cad0  rdModel3_CalcFaceNormals ---- */
/* Computes the normal of every face from three non-collinear vertices (Math3D_TriangleNormal,
   Math3D_PointsCollinear). Source file Rdmodel3.c (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c).
    */

void rdModel3_CalcFaceNormals(uint param_1)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int *piVar6;
  uint uVar7;
  uint *puVar8;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  local_4 = 0;
  puVar2 = (uint *)(param_1 + 0x24);
  uVar5 = param_1;
  if (*(int *)(param_1 + 0x44) != 0) {
    do {
      local_c = 0;
      if (*puVar2 != 0) {
        piVar6 = (int *)(puVar2[1] + 0x30);
        do {
          local_10 = 0;
          if (piVar6[8] != 0) {
            puVar8 = (uint *)(piVar6[4] + 0x14);
            do {
              uVar4 = *puVar8;
              uVar7 = 0;
              if (0 < (int)uVar4) {
                do {
                  local_18 = uVar7 - 1;
                  if ((int)local_18 < 0) {
                    local_18 = uVar4 - 1;
                  }
                  uVar1 = uVar7 + 1;
                  uVar5 = uVar1 % uVar4;
                  uVar4 = puVar8[1];
                  iVar3 = *piVar6;
                  iVar3 = Math3D_PointsCollinear
                                    (iVar3 + *(int *)(uVar4 + uVar7 * 4) * 0xc,
                                     iVar3 + *(int *)(uVar4 + uVar5 * 4) * 0xc,
                                     iVar3 + *(int *)(uVar4 + local_18 * 4) * 0xc);
                } while ((iVar3 != 0) && (uVar4 = *puVar8, uVar7 = uVar1, (int)uVar1 < (int)uVar4));
              }
              if ((int)uVar7 < (int)*puVar8) {
                uVar4 = puVar8[1];
                iVar3 = *piVar6;
                Math3D_TriangleNormal
                          (puVar8 + 0xb,iVar3 + *(int *)(uVar4 + uVar7 * 4) * 0xc,
                           iVar3 + *(int *)(uVar4 + uVar5 * 4) * 0xc,
                           iVar3 + *(int *)(uVar4 + local_18 * 4) * 0xc);
              }
              puVar8 = puVar8 + 0x13;
              local_10 = local_10 + 1;
            } while (local_10 < (uint)piVar6[8]);
          }
          piVar6 = piVar6 + 0x1f;
          local_c = local_c + 1;
        } while (local_c < *puVar2);
      }
      puVar2 = puVar2 + 2;
      local_4 = local_4 + 1;
    } while (local_4 < *(uint *)(param_1 + 0x44));
  }
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x0040cc30  rdModel3_CalcVertexNormals ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Averages the normals of the faces that share a vertex (or builds one from the neighbouring edges)
   and normalises. Source file Rdmodel3.c (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */

void rdModel3_CalcVertexNormals(int param_1)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  int iVar8;
  float *pfVar9;
  int iVar10;
  uint uVar11;
  float fVar12;
  undefined4 *puVar13;
  uint *puVar14;
  uint *puVar15;
  float *pfVar16;
  uint *puVar17;
  #define local_44 (*(float (*)[3])(_frame + (0x60 - 0x44)))
  #define local_38 (*(uint *)(_frame + (0x60 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x60 - 0x34)))
  #define local_30 (*(uint *)(_frame + (0x60 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x60 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x60 - 0x28)))
  #define local_20 (*(float (*)[2])(_frame + (0x60 - 0x20)))
  #define local_14 (*(uint *)(_frame + (0x60 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x60 - 0x10)))
  #define local_4 (*(uint *)(_frame + (0x60 - 0x4)))
  
  puVar15 = (uint *)(param_1 + 0x24);
  local_2c = 0;
  if (*(int *)(param_1 + 0x44) != 0) {
    do {
      local_34 = 0;
      if (*puVar15 != 0) {
        puVar13 = (undefined4 *)(puVar15[1] + 0x30);
        do {
          pfVar16 = (float *)puVar13[5];
          local_38 = 0;
          if (puVar13[6] != 0) {
            do {
              local_20[0] = 0.0;
              local_20[1] = 0.0;
              fVar1 = 0.0;
              fVar2 = 0.0;
              fVar3 = 0.0;
              fVar4 = 0.0;
              local_44[0] = 0.0;
              if (PUN(float,puVar13[8]) == 0.0) {
                fVar1 = 0.0;
              }
              else {
                puVar17 = (uint *)(puVar13[4] + 0x14);
                fVar12 = PUN(float,puVar13[8]);
                do {
                  local_44[0] = fVar12;
                  uVar11 = 0;
                  if (*puVar17 != 0) {
                    puVar14 = (uint *)puVar17[1];
                    do {
                      if (*puVar14 == local_38) {
                        fVar1 = PUN(float,puVar17[0xb]) + fVar1;
                        fVar2 = PUN(float,puVar17[0xc]) + fVar2;
                        fVar3 = PUN(float,puVar17[0xd]) + fVar3;
                        fVar4 = fVar4 - -1.0;
                        break;
                      }
                      uVar11 = uVar11 + 1;
                      puVar14 = puVar14 + 1;
                    } while (uVar11 < *puVar17);
                  }
                  puVar17 = puVar17 + 0x13;
                  fVar12 = PUN(float,(PUN(int,(float)local_44[0]) + -1));
                  local_44[0] = fVar4;
                  local_20[0] = fVar2;
                  local_20[1] = fVar3;
                } while (fVar12 != 0.0);
              }
              if (local_44[0] == 0.0) {
                *pfVar16 = 1.0;
                pfVar16[1] = 0.0;
                pfVar16[2] = 0.0;
              }
              else if (local_44[0] == 1.0) {
                iVar8 = puVar13[4];
                uVar11 = *(uint *)(iVar8 + 0x14);
                iVar8 = *(int *)(iVar8 + 0x18);
                pfVar9 = (float *)*puVar13;
                iVar10 = *(int *)(iVar8 + (uVar11 - 1) * 4);
                fVar1 = pfVar9[2];
                fVar2 = pfVar9[2];
                fVar3 = *pfVar9;
                fVar4 = *pfVar9;
                fVar12 = (pfVar9 + iVar10 * 3)[2];
                fVar5 = pfVar9[iVar10 * 3];
                iVar8 = *(int *)(iVar8 + (int)(1 % (ulonglong)uVar11) * 4);
                fVar6 = pfVar9[iVar8 * 3 + 2];
                fVar7 = pfVar9[iVar8 * 3];
                pfVar16[1] = (pfVar9[1] - pfVar9[iVar8 * 3 + 1]) +
                             (pfVar9[1] - pfVar9[iVar10 * 3 + 1]);
                pfVar16[2] = (fVar1 - fVar6) + (fVar2 - fVar12);
                *pfVar16 = (fVar4 - fVar5) + (fVar3 - fVar7);
                Vec3_Normalize(pfVar16);
              }
              else {
                *pfVar16 = fVar1 / local_44[0];
                pfVar16[1] = local_20[0] / local_44[0];
                pfVar16[2] = local_20[1] / local_44[0];
                Vec3_Normalize(pfVar16);
              }
              pfVar16 = pfVar16 + 3;
              local_38 = local_38 + 1;
            } while (local_38 < (uint)puVar13[6]);
          }
          puVar13 = puVar13 + 0x1f;
          local_34 = local_34 + 1;
        } while (local_34 < *puVar15);
      }
      puVar15 = puVar15 + 2;
      local_2c = local_2c + 1;
    } while (local_2c < *(uint *)(param_1 + 0x44));
  }
  return;
}
#undef local_10
#undef local_14
#undef local_20
#undef local_28
#undef local_2c
#undef local_30
#undef local_34
#undef local_38
#undef local_4
#undef local_44

#endif


/* ---- 0x0040ce90  rdModel3_CountNodeChildren ---- */
/* Counts the children of every hierarchy node (follows the sibling chain at +0x54). Source file
   Rdmodel3.c (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */

void rdModel3_CountNodeChildren(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  
  uVar5 = 0;
  if (*(int *)(param_1 + 0x54) != 0) {
    iVar4 = 0;
    do {
      iVar2 = *(int *)(param_1 + 0x58);
      *(undefined4 *)(iVar2 + 0x50 + iVar4) = 0;
      iVar2 = iVar2 + iVar4;
      piVar3 = (int *)(iVar2 + 0x54);
      iVar1 = *(int *)(iVar2 + 0x54);
      while (iVar1 != 0) {
        *(int *)(iVar2 + 0x50) = *(int *)(iVar2 + 0x50) + 1;
        piVar3 = (int *)(*piVar3 + 0x54);
        iVar1 = *piVar3;
      }
      uVar5 = uVar5 + 1;
      iVar4 = iVar4 + 0xb8;
    } while (uVar5 < *(uint *)(param_1 + 0x54));
  }
  return;
}
