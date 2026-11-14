/* GRIMFANDANGO.EXE :: rdmodel3.c
 * functions 0x0040a8c0 .. 0x0040ce90 (16 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0040a8c0  rdModel3_NewEntry ---- */
/* Clears a 0x90-byte model record and names it UNKNOWN. Source file Rdmodel3.c
   (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */

void __cdecl rdModel3_NewEntry(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = param_1;
  for (iVar1 = 0x24; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  strncpy(param_1,(uint *)s_UNKNOWN_004ddb8c,0x1f);
  *(undefined1 *)((int)param_1 + 0x1f) = 0;
  param_1[0x14] = 0;
  return;
}

/* ---- 0x0040a8f0  rdModel3_Load ---- */
/* Loads a model: calls the custom loader hook if one is installed, otherwise allocates the record,
   rdModel3_Load, then rdModel3_LoadPostProcess. Source file Rdmodel3.c
   (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). Original name rdModel3_Load (the remaster's
   GrimFandango (Linux): same body (loader hook, 0x90-byte model, load, post-process, free on
   failure); sputResource_ModelHandler's call); was rdModel3_New. */

undefined4 * __cdecl rdModel3_Load(uint param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  
  if (g_dwModel3Loader != 0) {
    puVar1 = (undefined4 *)(*(code *)g_dwModel3Loader)(param_1,0);
    if (puVar1 == (undefined4 *)0x0) {
      return (undefined4 *)0x0;
    }
    rdModel3_LoadPostProcess((uint)puVar1);
    return puVar1;
  }
  puVar1 = (undefined4 *)
           (*g_pRdroid_HS->pAlloc)
                     (0x90,s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,DAT_004ddb7c + 0xc);
  if (puVar1 != (undefined4 *)0x0) {
    puVar4 = puVar1;
    for (iVar3 = 0x24; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    uVar2 = rdModel3_LoadEntry(param_1,(uint)puVar1);
    if (uVar2 != 0) {
      rdModel3_LoadPostProcess((uint)puVar1);
      return puVar1;
    }
  }
  rdModel3_Free((int)puVar1);
  return (undefined4 *)0x0;
}

/* ---- 0x0040a980  rdModel3_LoadEntry ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Opens the file; the magic 'MODL' selects rdModel3_LoadBinary, anything else is parsed by
   rdModel3_LoadText. Source file Rdmodel3.c (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c).
   Original name rdModel3_LoadEntry (the remaster's GrimFandango (Linux): same body (open, 'LDOM'
   magic -> LoadEntryBinary else LoadEntryText)); was rdModel3_Load. */

uint __cdecl rdModel3_LoadEntry(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int unaff_ESI;
  uint unaff_EDI;
  uint unaff_retaddr;
  uint in_stack_0000000c;
  
  iVar1 = param_1;
  iVar2 = (*g_pRdroid_HS->pFopen)(param_1,&DAT_004ddb18);
  if (iVar2 == 0) {
    return 0;
  }
  (*g_pRdroid_HS->pFread)(iVar2,&param_1,4);
  if (param_1 == 0x4d4f444c) {
    uVar3 = rdModel3_LoadEntryBinary(iVar2,param_2);
    if (uVar3 != 0) {
      (*g_pRdroid_HS->pFclose)();
      return 1;
    }
    (*g_pRdroid_HS->pFclose)(iVar2);
    return 0;
  }
  (*g_pRdroid_HS->pFclose)(iVar2);
  uVar3 = rdModel3_LoadEntryText
                    (iVar1,param_2,unaff_EDI,unaff_ESI,unaff_retaddr,param_1,param_2,
                     in_stack_0000000c);
  return uVar3;
}
#endif


/* ---- 0x0040aa20  rdModel3_LoadEntryText ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Parser of the text .3do format (stdConffile 'section:' lines). Source file Rdmodel3.c
   (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */

uint __cdecl
rdModel3_LoadEntryText
          (uint param_1,uint param_2,uint param_3,int param_4,uint param_5,uint param_6,uint param_7
          ,uint param_8)

{
  char cVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  void *pvVar5;
  undefined4 *puVar6;
  int iVar7;
  undefined *puVar8;
  undefined *puVar9;
  int iVar10;
  uint uVar11;
  undefined *puVar12;
  uint *puVar13;
  uint *puVar14;
  char *pcVar15;
  uint unaff_retaddr;
  uint *puStack00000024;
  uint uStack00000028;
  int iStack0000002c;
  uint in_stack_00000030;
  uint uStack00000034;
  uint uStack0000003c;
  uint in_stack_00000040;
  uint in_stack_00000044;
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
  uint in_stack_00000074;
  int in_stack_00000078;
  uint in_stack_0000007c;
  char *in_stack_0002048c;
  uint *in_stack_00020490;
  char *pcVar16;
  uint uVar17;
  
  FUN_004addf0();
  rdModel3_NewEntry(in_stack_00020490);
  uVar17 = 0x1f;
  puVar2 = (uint *)stdFileFromPath(in_stack_0002048c);
  strncpy(in_stack_00020490,puVar2,uVar17);
  *(undefined1 *)((int)in_stack_00020490 + 0x1f) = 0;
  uVar17 = stdConffile_Open((uint)in_stack_0002048c);
  if (uVar17 == 0) {
    return 0;
  }
  uVar17 = stdConffile_ReadLine();
  if (((uVar17 != 0) &&
      (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_section___s_004ddd64), iVar3 == 1)) &&
     (uVar17 = stdConffile_ReadLine(), uVar17 != 0)) {
    sscanf((char *)g_dwStdConffile_aLine,s_3do__d__d_004ddd58);
    uVar17 = stdConffile_ReadLine();
    if (((uVar17 != 0) &&
        (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_section___s_004ddd64), iVar3 == 1)) &&
       ((uVar17 = stdConffile_ReadLine(), uVar17 != 0 &&
        (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_materials__d_004ddd48), iVar3 == 1)))) {
      if (param_5 != 0) {
        if (0x7f < param_5) {
          (*g_pRdroid_HS->pAssertFail)();
        }
        uVar17 = (*g_pRdroid_HS->pAlloc)();
        in_stack_00020490[0x12] = uVar17;
        if (uVar17 == 0) goto LAB_0040b8c4;
        uVar17 = 0;
        if (param_5 != 0) {
          do {
            uVar4 = stdConffile_ReadLine();
            if ((uVar4 == 0) ||
               (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s__d___s_004ddd28), iVar3 != 2))
            goto LAB_0040b8c4;
            uVar4 = 0xffffffff;
            pcVar15 = &STACK0X(0x00000088);
            do {
              pcVar16 = pcVar15;
              if (uVar4 == 0) break;
              uVar4 = uVar4 - 1;
              pcVar16 = pcVar15 + 1;
              cVar1 = *pcVar15;
              pcVar15 = pcVar16;
            } while (cVar1 != '\0');
            uVar4 = ~uVar4;
            pcVar15 = pcVar16 + -uVar4;
            pcVar16 = &STACK0X(0x00000488) + param_4 * 0x400;
            for (uVar11 = uVar4 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
              *(undefined4 *)pcVar16 = *(undefined4 *)pcVar15;
              pcVar15 = pcVar15 + 4;
              pcVar16 = pcVar16 + 4;
            }
            uVar17 = uVar17 + 1;
            for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
              *pcVar16 = *pcVar15;
              pcVar15 = pcVar15 + 1;
              pcVar16 = pcVar16 + 1;
            }
          } while (uVar17 < param_5);
        }
        uVar17 = 0;
        if (param_5 != 0) {
          pcVar15 = &STACK0X(0x00000488);
          do {
            pvVar5 = rdMaterial_Load(pcVar15,0,0);
            *(void **)(in_stack_00020490[0x12] + uVar17 * 4) = pvVar5;
            if (*(int *)(in_stack_00020490[0x12] + uVar17 * 4) == 0) goto LAB_0040b8c4;
            uVar17 = uVar17 + 1;
            pcVar15 = pcVar15 + 0x400;
          } while (uVar17 < param_5);
        }
      }
      in_stack_00020490[0x13] = param_5;
      uVar17 = stdConffile_ReadLine();
      if ((((uVar17 != 0) &&
           (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_section___s_004ddd64), iVar3 == 1)) &&
          (uVar17 = stdConffile_ReadLine(), uVar17 != 0)) &&
         (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_radius__f_004ddd1c), iVar3 == 1)) {
        in_stack_00020490[0x17] = in_stack_00000044;
        uVar17 = stdConffile_ReadLine();
        if ((uVar17 != 0) &&
           (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_insert_offset__f__f__f_004ddd04),
           iVar3 == 3)) {
          in_stack_00020490[0x21] = param_3;
          in_stack_00020490[0x22] = param_1;
          in_stack_00020490[0x23] = param_2;
          uVar17 = stdConffile_ReadLine();
          if ((uVar17 != 0) &&
             (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_geosets__d_004ddcf8), iVar3 == 1)) {
            uStack0000003c = 0;
            in_stack_00020490[0x11] = in_stack_00000040;
            if (in_stack_00000040 != 0) {
              puStack00000024 = in_stack_00020490 + 10;
              do {
                uVar17 = stdConffile_ReadLine();
                if (((uVar17 == 0) ||
                    (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_geoset__d_004ddcec), iVar3 != 1)
                    ) || ((uVar17 = stdConffile_ReadLine(), uVar17 == 0 ||
                          (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_meshes__d_004ddce0),
                          iVar3 != 1)))) goto LAB_0040b8c4;
                puVar6 = (undefined4 *)(*g_pRdroid_HS->pAlloc)();
                *puStack00000024 = (uint)puVar6;
                if (puVar6 == (undefined4 *)0x0) goto LAB_0040b8c4;
                uStack00000034 = 0;
                for (uVar17 = param_6 * 0x1f & 0x3fffffff; uVar17 != 0; uVar17 = uVar17 - 1) {
                  *puVar6 = 0;
                  puVar6 = puVar6 + 1;
                }
                for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
                  *(undefined1 *)puVar6 = 0;
                  puVar6 = (undefined4 *)((int)puVar6 + 1);
                }
                puStack00000024[-1] = param_6;
                if (param_6 != 0) {
                  iStack0000002c = 0;
                  do {
                    puVar2 = (uint *)(*puStack00000024 + iStack0000002c);
                    puVar2[8] = uStack00000034;
                    uVar17 = stdConffile_ReadLine();
                    if ((((uVar17 == 0) ||
                         (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_mesh__d_004ddcd4),
                         iVar3 != 1)) || (uVar17 = stdConffile_ReadLine(), uVar17 == 0)) ||
                       (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_name__s_004ddcc8), iVar3 != 1
                       )) goto LAB_0040b8c4;
                    strncpy(puVar2,(uint *)&g_bStd_genBuffer,0x1f);
                    *(undefined1 *)((int)puVar2 + 0x1f) = 0;
                    uVar17 = stdConffile_ReadLine();
                    if (((uVar17 == 0) ||
                        (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_radius__f_004ddd1c),
                        iVar3 != 1)) || (uVar17 = stdConffile_ReadLine(), uVar17 == 0))
                    goto LAB_0040b8c4;
                    iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_shadow__d_004ddcbc);
                    if (iVar3 == 1) {
                      puVar2[0x15] = in_stack_00000074;
                      uVar17 = stdConffile_ReadLine();
                      if (uVar17 == 0) goto LAB_0040b8c4;
                    }
                    iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_geometrymode__d_004ddca8);
                    if ((((iVar3 != 1) || (uVar17 = stdConffile_ReadLine(), uVar17 == 0)) ||
                        ((iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_lightingmode__d_004ddc94),
                         iVar3 != 1 ||
                         (((uVar17 = stdConffile_ReadLine(), uVar17 == 0 ||
                           (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_texturemode__d_004ddc84),
                           iVar3 != 1)) || (uVar17 = stdConffile_ReadLine(), uVar17 == 0)))))) ||
                       ((iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_vertices__d_004ddc74),
                        iVar3 != 1 || (0x200 < unaff_retaddr)))) goto LAB_0040b8c4;
                    puVar2[0xc] = 0;
                    puVar2[0xe] = 0;
                    puVar2[0xf] = 0;
                    if (unaff_retaddr != 0) {
                      uVar17 = (*g_pRdroid_HS->pAlloc)();
                      puVar2[0xc] = uVar17;
                      if (uVar17 == 0) goto LAB_0040b8c4;
                      uVar17 = (*g_pRdroid_HS->pAlloc)();
                      puVar2[0xe] = uVar17;
                      if (uVar17 == 0) goto LAB_0040b8c4;
                      puVar6 = (undefined4 *)(*g_pRdroid_HS->pAlloc)();
                      puVar2[0xf] = (uint)puVar6;
                      if (puVar6 == (undefined4 *)0x0) goto LAB_0040b8c4;
                      for (uVar17 = unaff_retaddr >> 2; uVar17 != 0; uVar17 = uVar17 - 1) {
                        *puVar6 = 0;
                        puVar6 = puVar6 + 1;
                      }
                      for (uVar17 = unaff_retaddr & 3; uVar17 != 0; uVar17 = uVar17 - 1) {
                        *(undefined1 *)puVar6 = 0;
                        puVar6 = (undefined4 *)((int)puVar6 + 1);
                      }
                    }
                    puVar14 = (uint *)puVar2[0xc];
                    uVar17 = 0;
                    if (unaff_retaddr != 0) {
                      do {
                        uVar4 = stdConffile_ReadLine();
                        if ((uVar4 == 0) ||
                           (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s__d___f__f__f__f_004ddc60)
                           , iVar3 != 5)) goto LAB_0040b8c4;
                        *puVar14 = param_3;
                        puVar14[1] = param_1;
                        puVar14[2] = param_2;
                        puVar14 = puVar14 + 3;
                        *(undefined4 *)(puVar2[0xe] + uVar17 * 4) = in_stack_00000050;
                        uVar17 = uVar17 + 1;
                      } while (uVar17 < unaff_retaddr);
                    }
                    puVar2[0x12] = unaff_retaddr;
                    uVar17 = stdConffile_ReadLine();
                    if (((uVar17 == 0) ||
                        (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_texture_vertices__d_004ddc48
                                       ), iVar3 != 1)) || (0x300 < param_7)) goto LAB_0040b8c4;
                    puVar2[0xd] = 0;
                    if (param_7 != 0) {
                      puVar6 = (undefined4 *)(*g_pRdroid_HS->pAlloc)();
                      puVar2[0xd] = (uint)puVar6;
                      if (puVar6 == (undefined4 *)0x0) goto LAB_0040b8c4;
                      uVar17 = 0;
                      if (param_7 != 0) {
                        do {
                          uVar4 = stdConffile_ReadLine();
                          if ((uVar4 == 0) ||
                             (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s__d___f__f_004ddc3c),
                             iVar3 != 3)) goto LAB_0040b8c4;
                          *puVar6 = in_stack_00000070;
                          puVar6[1] = in_stack_00000058;
                          puVar6 = puVar6 + 2;
                          uVar17 = uVar17 + 1;
                        } while (uVar17 < param_7);
                      }
                    }
                    puVar2[0x13] = param_7;
                    uVar17 = stdConffile_ReadLine();
                    if (uVar17 == 0) goto LAB_0040b8c4;
                    puVar2[0x11] = 0;
                    if (unaff_retaddr != 0) {
                      uVar17 = (*g_pRdroid_HS->pAlloc)();
                      puVar2[0x11] = uVar17;
                      if (uVar17 == 0) goto LAB_0040b8c4;
                    }
                    uVar17 = 0;
                    if (unaff_retaddr != 0) {
                      iVar3 = 0;
                      do {
                        uVar4 = stdConffile_ReadLine();
                        if ((uVar4 == 0) ||
                           (iVar7 = sscanf((char *)g_dwStdConffile_aLine,s__d___f__f__f_004ddc2c),
                           iVar7 != 4)) goto LAB_0040b8c4;
                        uVar17 = uVar17 + 1;
                        *(uint *)(iVar3 + puVar2[0x11]) = param_3;
                        *(uint *)(iVar3 + 4 + puVar2[0x11]) = param_1;
                        *(uint *)(iVar3 + 8 + puVar2[0x11]) = param_2;
                        iVar3 = iVar3 + 0xc;
                      } while (uVar17 < unaff_retaddr);
                    }
                    uVar17 = stdConffile_ReadLine();
                    if (((uVar17 == 0) ||
                        (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_faces__d_004ddc20),
                        iVar3 != 1)) || (0x200 < param_8)) goto LAB_0040b8c4;
                    puVar2[0x14] = param_8;
                    puVar2[0x10] = 0;
                    if (param_8 != 0) {
                      uVar17 = (*g_pRdroid_HS->pAlloc)();
                      puVar2[0x10] = uVar17;
                      if (uVar17 == 0) goto LAB_0040b8c4;
                    }
                    puVar14 = (uint *)puVar2[0x10];
                    uStack00000028 = 0;
                    if (param_8 != 0) {
                      puVar13 = puVar14 + 2;
                      do {
                        uVar17 = stdConffile_ReadLine();
                        if (uVar17 == 0) goto LAB_0040b8c4;
                        FUN_00450220(puVar14);
                        strtok((byte *)g_dwStdConffile_aLine,&DAT_004dd918);
                        uVar17 = strtok((byte *)0x0,&DAT_004dd918);
                        puVar8 = atoi(uVar17);
                        *puVar14 = uStack00000028;
                        if (puVar8 == (undefined *)0xffffffff) {
                          puVar13[6] = 0;
                        }
                        else {
                          puVar13[6] = *(uint *)(in_stack_00020490[0x12] + (int)puVar8 * 4);
                        }
                        pcVar16 = &DAT_004ddc1c;
                        pcVar15 = (char *)strtok((byte *)0x0,&DAT_004dd918);
                        iVar3 = sscanf(pcVar15,pcVar16);
                        if (iVar3 != 1) goto LAB_0040b8c4;
                        pcVar16 = &DAT_004ddc18;
                        pcVar15 = (char *)strtok((byte *)0x0,&DAT_004dd918);
                        iVar3 = sscanf(pcVar15,pcVar16);
                        if (iVar3 != 1) goto LAB_0040b8c4;
                        pcVar16 = &DAT_004ddc18;
                        pcVar15 = (char *)strtok((byte *)0x0,&DAT_004dd918);
                        iVar3 = sscanf(pcVar15,pcVar16);
                        if (iVar3 != 1) goto LAB_0040b8c4;
                        pcVar16 = &DAT_004ddc18;
                        pcVar15 = (char *)strtok((byte *)0x0,&DAT_004dd918);
                        iVar3 = sscanf(pcVar15,pcVar16);
                        if (iVar3 != 1) goto LAB_0040b8c4;
                        pcVar16 = &DAT_004ddc14;
                        pcVar15 = (char *)strtok((byte *)0x0,&DAT_004dd918);
                        iVar3 = sscanf(pcVar15,pcVar16);
                        if (iVar3 != 1) goto LAB_0040b8c4;
                        puVar13[10] = in_stack_0000007c;
                        uVar17 = strtok((byte *)0x0,&DAT_004dd918);
                        puVar8 = atoi(uVar17);
                        if ((puVar8 == (undefined *)0x0) || ((undefined *)0x18 < puVar8))
                        goto LAB_0040b8c4;
                        puVar13[3] = (uint)puVar8;
                        uVar17 = (*g_pRdroid_HS->pAlloc)();
                        puVar13[4] = uVar17;
                        if (uVar17 == 0) goto LAB_0040b8c4;
                        if (((byte *)puVar13[6] == (byte *)0x0) || ((*(byte *)puVar13[6] & 2) == 0))
                        {
                          puVar12 = (undefined *)0x0;
                          if (puVar8 != (undefined *)0x0) {
                            do {
                              uVar17 = strtok((byte *)0x0,&DAT_004ddc10);
                              puVar9 = atoi(uVar17);
                              *(undefined **)(puVar13[4] + (int)puVar12 * 4) = puVar9;
                              strtok((byte *)0x0,&DAT_004ddc10);
                              puVar12 = puVar12 + 1;
                            } while (puVar12 < puVar8);
                          }
                        }
                        else {
                          uVar17 = (*g_pRdroid_HS->pAlloc)();
                          puVar13[5] = uVar17;
                          if (uVar17 == 0) goto LAB_0040b8c4;
                          puVar12 = (undefined *)0x0;
                          if (puVar8 != (undefined *)0x0) {
                            do {
                              uVar17 = strtok((byte *)0x0,&DAT_004ddc10);
                              puVar9 = atoi(uVar17);
                              *(undefined **)(puVar13[4] + (int)puVar12 * 4) = puVar9;
                              uVar17 = strtok((byte *)0x0,&DAT_004ddc10);
                              puVar9 = atoi(uVar17);
                              *(undefined **)(puVar13[5] + (int)puVar12 * 4) = puVar9;
                              puVar12 = puVar12 + 1;
                            } while (puVar12 < puVar8);
                          }
                        }
                        puVar14 = puVar14 + 0x13;
                        puVar13 = puVar13 + 0x13;
                        uStack00000028 = uStack00000028 + 1;
                      } while (uStack00000028 < param_8);
                    }
                    uVar17 = stdConffile_ReadLine();
                    if (uVar17 == 0) goto LAB_0040b8c4;
                    uVar17 = 0;
                    if (puVar2[0x14] != 0) {
                      puVar14 = (uint *)(puVar2[0x10] + 0x44);
                      do {
                        uVar4 = stdConffile_ReadLine();
                        if ((uVar4 == 0) ||
                           (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s__d___f__f__f_004ddc2c),
                           iVar3 != 4)) goto LAB_0040b8c4;
                        puVar14[-1] = param_3;
                        *puVar14 = param_1;
                        puVar14[1] = param_2;
                        puVar14 = puVar14 + 0x13;
                        uVar17 = uVar17 + 1;
                      } while (uVar17 < puVar2[0x14]);
                    }
                    uStack00000034 = uStack00000034 + 1;
                    iStack0000002c = iStack0000002c + 0x7c;
                  } while (uStack00000034 < param_6);
                }
                uStack0000003c = uStack0000003c + 1;
                puStack00000024 = puStack00000024 + 2;
              } while (uStack0000003c < in_stack_00000040);
            }
            uVar17 = stdConffile_ReadLine();
            if ((((uVar17 != 0) &&
                 (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_section___s_004ddd64), iVar3 == 1))
                && (uVar17 = stdConffile_ReadLine(), uVar17 != 0)) &&
               (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_hierarchy_nodes__d_004ddbfc),
               iVar3 == 1)) {
              uVar17 = (*g_pRdroid_HS->pAlloc)();
              in_stack_00020490[0x16] = uVar17;
              if (uVar17 != 0) {
                uVar17 = 0;
                in_stack_00020490[0x15] = in_stack_00000030;
                if (in_stack_00000030 != 0) {
                  iVar3 = 0;
                  do {
                    uVar4 = in_stack_00020490[0x16];
                    *(uint *)(iVar3 + 0x44 + uVar4) = uVar17;
                    iVar7 = iVar3 + uVar4;
                    uVar4 = stdConffile_ReadLine();
                    if ((uVar4 == 0) ||
                       (iVar10 = sscanf((char *)g_dwStdConffile_aLine,
                                        s__d___x__x__d__d__d__d__d__f__f___004ddbc4), iVar10 != 0x12
                       )) goto LAB_0040b8c4;
                    if (in_stack_00000060 == -1) {
                      *(undefined4 *)(iVar7 + 0x54) = 0;
                    }
                    else {
                      *(uint *)(iVar7 + 0x54) = in_stack_00020490[0x16] + in_stack_00000060 * 0xb8;
                    }
                    if (in_stack_00000078 == -1) {
                      *(undefined4 *)(iVar7 + 0x5c) = 0;
                    }
                    else {
                      *(uint *)(iVar7 + 0x5c) = in_stack_00020490[0x16] + in_stack_00000078 * 0xb8;
                    }
                    if (in_stack_00000068 == -1) {
                      *(undefined4 *)(iVar7 + 0x60) = 0;
                    }
                    else {
                      *(uint *)(iVar7 + 0x60) = in_stack_00020490[0x16] + in_stack_00000068 * 0xb8;
                    }
                    uVar17 = uVar17 + 1;
                    *(uint *)(iVar7 + 0x70) = param_3;
                    *(uint *)(iVar7 + 0x74) = param_1;
                    *(uint *)(iVar7 + 0x78) = param_2;
                    *(undefined4 *)(iVar7 + 0x7c) = in_stack_00000048;
                    *(undefined4 *)(iVar7 + 0x80) = in_stack_0000004c;
                    *(undefined4 *)(iVar7 + 0x84) = in_stack_00000054;
                    *(undefined4 *)(iVar7 + 100) = in_stack_0000005c;
                    *(undefined4 *)(iVar7 + 0x68) = in_stack_00000064;
                    *(undefined4 *)(iVar7 + 0x6c) = in_stack_0000006c;
                    iVar3 = iVar3 + 0xb8;
                  } while (uVar17 < in_stack_00000030);
                }
                rdModel3_CountNodeChildren((int)in_stack_00020490);
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


/* ---- 0x0040b8e0  rdModel3_LoadEntryBinary ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Reader of the binary 'MODL' model format (materials, geometry sets, meshes, hierarchy nodes).
   Source file Rdmodel3.c (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). Original name
   rdModel3_LoadEntryBinary (the remaster's GrimFandango (Linux): the only unmatched callee of
   rdModel3_LoadEntry; 2 matched neighbours agree, 1 disagree); was rdModel3_LoadBinary. */

uint __cdecl rdModel3_LoadEntryBinary(int param_1,int param_2)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  int *piVar2;
  int *piVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  void *pvVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int *piVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  char *name;
  #define iStack_24 (*(int *)(_frame + (0x40 - 0x24)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define iStack_18 (*(int *)(_frame + (0x40 - 0x18)))
  #define iStack_14 (*(int *)(_frame + (0x40 - 0x14)))
  #define iStack_c (*(int *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(int *)(_frame + (0x40 - 0x8)))
  #define uStack_4 (*(undefined4 *)(_frame + (0x40 - 0x4)))
  
  iVar12 = param_2;
  iVar9 = param_1;
  uVar14 = 0;
  local_1c = 0;
  rdModel3_NewEntry((undefined4 *)param_2);
  (*g_pRdroid_HS->pFread)(param_1,&local_8,4);
  *(int *)(iVar12 + 0x4c) = local_8;
  *(undefined4 *)(iVar12 + 0x48) = 0;
  if (local_8 != 0) {
    local_1c = (*g_pRdroid_HS->pAlloc)
                         (local_8 << 5,s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,
                          DAT_004ddb84 + 0x10);
  }
  uVar10 = local_1c;
  if (*(int *)(iVar12 + 0x4c) != 0) {
    do {
      (*g_pRdroid_HS->pFread)(param_1,uVar10,0x20);
      uVar10 = uVar10 + 0x20;
      uVar14 = uVar14 + 1;
    } while (uVar14 < *(uint *)(iVar12 + 0x4c));
  }
  (*g_pRdroid_HS->pFread)(param_1,iVar12,0x20);
  (*g_pRdroid_HS->pFread)(param_1,iVar12 + 0x20,4);
  piVar1 = (int *)(iVar12 + 0x44);
  (*g_pRdroid_HS->pFread)(param_1,piVar1,4);
  param_1 = 0;
  if (0 < *piVar1) {
    piVar11 = (int *)(iVar12 + 0x24);
    do {
      (*g_pRdroid_HS->pFread)(iVar9,piVar11,4);
      puVar4 = (undefined4 *)
               (*g_pRdroid_HS->pAlloc)
                         (*piVar11 * 0x7c,s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,
                          DAT_004ddb84 + 0x20);
      piVar11[1] = (int)puVar4;
      for (uVar14 = *piVar11 * 0x1f & 0x3fffffff; uVar14 != 0; uVar14 = uVar14 - 1) {
        *puVar4 = 0;
        puVar4 = puVar4 + 1;
      }
      for (iVar8 = 0; iVar8 != 0; iVar8 = iVar8 + -1) {
        *(undefined1 *)puVar4 = 0;
        puVar4 = (undefined4 *)((int)puVar4 + 1);
      }
      iStack_24 = 0;
      if (0 < *piVar11) {
        iStack_14 = 0;
        do {
          iVar12 = piVar11[1] + iStack_14;
          (*g_pRdroid_HS->pFread)(iVar9,iVar12,0x20);
          (*g_pRdroid_HS->pFread)(iVar9,iVar12 + 0x20,4);
          (*g_pRdroid_HS->pFread)(iVar9,iVar12 + 0x24,4);
          (*g_pRdroid_HS->pFread)(iVar9,iVar12 + 0x28,4);
          (*g_pRdroid_HS->pFread)(iVar9,iVar12 + 0x2c,4);
          piVar2 = (int *)(iVar12 + 0x48);
          (*g_pRdroid_HS->pFread)(iVar9,piVar2,4);
          (*g_pRdroid_HS->pFread)(iVar9,iVar12 + 0x4c,4);
          piVar3 = (int *)(iVar12 + 0x50);
          (*g_pRdroid_HS->pFread)(iVar9,piVar3,4);
          if (*piVar2 != 0) {
            uVar5 = (*g_pRdroid_HS->pAlloc)
                              (*piVar2 * 0xc,s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,
                               DAT_004ddb84 + 0x30);
            *(undefined4 *)(iVar12 + 0x30) = uVar5;
            uVar5 = (*g_pRdroid_HS->pAlloc)
                              (*piVar2 << 2,s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,
                               DAT_004ddb84 + 0x31);
            *(undefined4 *)(iVar12 + 0x38) = uVar5;
            uVar5 = (*g_pRdroid_HS->pAlloc)
                              (*piVar2 << 2,s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,
                               DAT_004ddb84 + 0x32);
            *(undefined4 *)(iVar12 + 0x3c) = uVar5;
          }
          if (*(int *)(iVar12 + 0x4c) != 0) {
            uVar5 = (*g_pRdroid_HS->pAlloc)
                              (*(int *)(iVar12 + 0x4c) * 8,
                               s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,DAT_004ddb84 + 0x36);
            *(undefined4 *)(iVar12 + 0x34) = uVar5;
          }
          (*g_pRdroid_HS->pFread)(iVar9,*(undefined4 *)(iVar12 + 0x30),*piVar2 * 0xc);
          (*g_pRdroid_HS->pFread)(iVar9,*(undefined4 *)(iVar12 + 0x34),*(int *)(iVar12 + 0x4c) << 3)
          ;
          (*g_pRdroid_HS->pFread)(iVar9,*(undefined4 *)(iVar12 + 0x38),*piVar2 << 2);
          (*g_pRdroid_HS->pFread)(iVar9,*(undefined4 *)(iVar12 + 0x3c),*piVar2 << 2);
          if (*piVar3 != 0) {
            puVar4 = (undefined4 *)
                     (*g_pRdroid_HS->pAlloc)
                               (*piVar3 * 0x4c,s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,
                                DAT_004ddb84 + 0x40);
            *(undefined4 **)(iVar12 + 0x40) = puVar4;
            for (uVar14 = *piVar3 * 0x13 & 0x3fffffff; uVar14 != 0; uVar14 = uVar14 - 1) {
              *puVar4 = 0;
              puVar4 = puVar4 + 1;
            }
            for (iVar8 = 0; iVar8 != 0; iVar8 = iVar8 + -1) {
              *(undefined1 *)puVar4 = 0;
              puVar4 = (undefined4 *)((int)puVar4 + 1);
            }
          }
          iStack_c = 0;
          if (0 < *(int *)(iVar12 + 0x50)) {
            iStack_18 = 0;
            do {
              iVar8 = iStack_18 + *(int *)(iVar12 + 0x40);
              (*g_pRdroid_HS->pFread)(iVar9,iVar8,0x4c);
              if (*(int *)(iVar8 + 0x14) != 0) {
                uVar5 = (*g_pRdroid_HS->pAlloc)
                                  (*(int *)(iVar8 + 0x14) * 4,
                                   s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,DAT_004ddb84 + 0x49);
                *(undefined4 *)(iVar8 + 0x18) = uVar5;
                (*g_pRdroid_HS->pFread)(iVar9,uVar5,*(int *)(iVar8 + 0x14) << 2);
              }
              if (*(int *)(iVar8 + 0x1c) != 0) {
                uVar5 = (*g_pRdroid_HS->pAlloc)
                                  (*(int *)(iVar8 + 0x14) << 2,
                                   s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,DAT_004ddb84 + 0x4e);
                *(undefined4 *)(iVar8 + 0x1c) = uVar5;
                (*g_pRdroid_HS->pFread)(iVar9,uVar5,*(int *)(iVar8 + 0x14) << 2);
              }
              if (*(int *)(iVar8 + 0x20) == 0) {
                *(undefined4 *)(iVar8 + 0x20) = 0xffffffff;
              }
              else {
                (*g_pRdroid_HS->pFread)(iVar9,&uStack_4,4);
                *(undefined4 *)(iVar8 + 0x20) = uStack_4;
              }
              iStack_c = iStack_c + 1;
              iStack_18 = iStack_18 + 0x4c;
            } while (iStack_c < *(int *)(iVar12 + 0x50));
          }
          *(undefined4 *)(iVar12 + 0x44) = 0;
          if (*piVar2 != 0) {
            uVar5 = (*g_pRdroid_HS->pAlloc)
                              (*piVar2 * 0xc,s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,
                               DAT_004ddb84 + 0x5f);
            *(undefined4 *)(iVar12 + 0x44) = uVar5;
          }
          (*g_pRdroid_HS->pFread)(iVar9,*(undefined4 *)(iVar12 + 0x44),*piVar2 * 0xc);
          (*g_pRdroid_HS->pFread)(iVar9,iVar12 + 0x54,4);
          (*g_pRdroid_HS->pFread)(iVar9,iVar12 + 0x5c,4);
          (*g_pRdroid_HS->pFread)(iVar9,iVar12 + 0x60,4);
          (*g_pRdroid_HS->pFread)(iVar9,iVar12 + 100,0x18);
          iStack_14 = iStack_14 + 0x7c;
          iStack_24 = iStack_24 + 1;
          iVar12 = param_2;
        } while (iStack_24 < *piVar11);
      }
      param_1 = param_1 + 1;
      piVar11 = piVar11 + 2;
    } while (param_1 < *piVar1);
  }
  (*g_pRdroid_HS->pFread)(iVar9,iVar12 + 0x50,4);
  piVar11 = (int *)(iVar12 + 0x54);
  (*g_pRdroid_HS->pFread)(iVar9,piVar11,4);
  uVar5 = (*g_pRdroid_HS->pAlloc)
                    (*piVar11 * 0xb8,s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,DAT_004ddb84 + 0x6c
                    );
  *(undefined4 *)(iVar12 + 0x58) = uVar5;
  iVar8 = 0;
  param_1 = 0;
  if (0 < *piVar11) {
    do {
      iVar13 = iVar8 + *(int *)(iVar12 + 0x58);
      (*g_pRdroid_HS->pFread)(iVar9,iVar13,0xb8);
      if (*(int *)(iVar13 + 0x54) != 0) {
        (*g_pRdroid_HS->pFread)(iVar9,&param_2,4);
        *(int *)(iVar13 + 0x54) = *(int *)(iVar12 + 0x58) + param_2 * 0xb8;
      }
      if (*(int *)(iVar13 + 0x5c) != 0) {
        (*g_pRdroid_HS->pFread)(iVar9,&param_2,4);
        *(int *)(iVar13 + 0x5c) = *(int *)(iVar12 + 0x58) + param_2 * 0xb8;
      }
      if (*(int *)(iVar13 + 0x60) != 0) {
        (*g_pRdroid_HS->pFread)(iVar9,&param_2,4);
        *(int *)(iVar13 + 0x60) = *(int *)(iVar12 + 0x58) + param_2 * 0xb8;
      }
      param_1 = param_1 + 1;
      iVar8 = iVar8 + 0xb8;
    } while (param_1 < *(int *)(iVar12 + 0x54));
  }
  (*g_pRdroid_HS->pFread)(iVar9,iVar12 + 0x5c,4);
  (*g_pRdroid_HS->pFread)(iVar9,iVar12 + 0x60,0x18);
  (*g_pRdroid_HS->pFread)(iVar9,iVar12 + 0x78,0xc);
  (*g_pRdroid_HS->pFread)(iVar9,iVar12 + 0x84,0xc);
  if (*(int *)(iVar12 + 0x4c) != 0) {
    uVar5 = (*g_pRdroid_HS->pAlloc)
                      (*(int *)(iVar12 + 0x4c) * 4,s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,
                       DAT_004ddb84 + 0x8e);
    *(undefined4 *)(iVar12 + 0x48) = uVar5;
  }
  uVar14 = 0;
  name = (char *)local_1c;
  if (*(int *)(iVar12 + 0x4c) != 0) {
    do {
      pvVar6 = rdMaterial_Load(name,0,0);
      name = name + 0x20;
      *(void **)(*(int *)(iVar12 + 0x48) + uVar14 * 4) = pvVar6;
      uVar14 = uVar14 + 1;
    } while (uVar14 < *(uint *)(iVar12 + 0x4c));
  }
  param_1 = 0;
  if (0 < *piVar1) {
    piVar11 = (int *)(iVar12 + 0x24);
    do {
      iStack_24 = 0;
      if (0 < *piVar11) {
        param_2 = 0;
        do {
          iVar8 = 0;
          iVar9 = param_2 + piVar11[1];
          if (0 < *(int *)(iVar9 + 0x50)) {
            iVar13 = 0;
            do {
              iVar7 = iVar13 + *(int *)(iVar9 + 0x40);
              if (*(int *)(iVar7 + 0x20) < 0) {
                *(undefined4 *)(iVar7 + 0x20) = 0;
              }
              else {
                *(undefined4 *)(iVar7 + 0x20) =
                     *(undefined4 *)(*(int *)(iVar12 + 0x48) + *(int *)(iVar7 + 0x20) * 4);
              }
              iVar8 = iVar8 + 1;
              iVar13 = iVar13 + 0x4c;
            } while (iVar8 < *(int *)(iVar9 + 0x50));
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
    (*g_pRdroid_HS->pFree)(local_1c);
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

void __cdecl rdModel3_LoadPostProcess(uint param_1)

{
  rdModel3_CalcBoundingBoxes(param_1);
  rdModel3_CalcRadii(param_1);
  rdModel3_CalcFaceNormals(param_1);
  rdModel3_CalcVertexNormals(param_1);
  rdModel3_CountNodeChildren(param_1);
  rdModel3_BuildShadowModel(param_1);
  return;
}

/* ---- 0x0040c0d0  rdModel3_Free ---- */
/* Frees a model (custom free hook if installed, else rdModel3_FreeEntry and the record). Source
   file Rdmodel3.c (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */

void __cdecl rdModel3_Free(int param_1)

{
  if (param_1 != 0) {
    if (g_dwModel3Unloader != 0) {
      (*(code *)g_dwModel3Unloader)();
      return;
    }
    rdModel3_FreeEntry(param_1);
    (*g_pRdroid_HS->pFree)(param_1);
  }
  return;
}

/* ---- 0x0040c100  rdModel3_FreeEntry ---- */
/* Frees the contents of a model: materials, geometry sets, meshes, vertices, faces, hierarchy
   nodes. Source file Rdmodel3.c (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */

void __cdecl rdModel3_FreeEntry(int param_1)

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
              (*g_pRdroid_HS->pFree)(piVar3[-1]);
            }
            if (*piVar3 != 0) {
              (*g_pRdroid_HS->pFree)(*piVar3);
            }
            iVar4 = piVar3[3];
            if (iVar4 != 0) {
              uVar1 = 0;
              if (piVar3[7] != 0) {
                do {
                  rdFace_FreeEntry(iVar4);
                  iVar4 = iVar4 + 0x4c;
                  uVar1 = uVar1 + 1;
                } while (uVar1 < (uint)piVar3[7]);
              }
              (*g_pRdroid_HS->pFree)(piVar3[3]);
            }
            if (piVar3[1] != 0) {
              (*g_pRdroid_HS->pFree)(piVar3[1]);
            }
            if (piVar3[2] != 0) {
              (*g_pRdroid_HS->pFree)(piVar3[2]);
            }
            if (piVar3[4] != 0) {
              (*g_pRdroid_HS->pFree)(piVar3[4]);
            }
            if (piVar3[9] != 0) {
              (*g_pRdroid_HS->pFree)(piVar3[9]);
            }
            piVar3 = piVar3 + 0x1f;
            local_8 = local_8 + 1;
          } while (local_8 < *puVar2);
        }
        if (puVar2[1] != 0) {
          (*g_pRdroid_HS->pFree)(puVar2[1]);
        }
        puVar2 = puVar2 + 2;
        local_4 = local_4 + 1;
      } while (local_4 < *(uint *)(param_1 + 0x44));
    }
    if (*(int *)(param_1 + 0x58) != 0) {
      (*g_pRdroid_HS->pFree)(*(int *)(param_1 + 0x58));
    }
    uVar1 = 0;
    if (*(int *)(param_1 + 0x4c) != 0) {
      do {
        rdMaterial_Free(*(uint *)(*(int *)(param_1 + 0x48) + uVar1 * 4));
        uVar1 = uVar1 + 1;
      } while (uVar1 < *(uint *)(param_1 + 0x4c));
    }
    if (*(int *)(param_1 + 0x48) != 0) {
      (*g_pRdroid_HS->pFree)(*(int *)(param_1 + 0x48));
    }
  }
  return;
}
#undef local_4
#undef local_8


/* ---- 0x0040c280  rdModel3_BuildShadowModel ---- */
/* Allocates 0xc0 bytes per mesh and fills the 8 corner points of its bounding box from the min/max
   values. Source file Rdmodel3.c (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). Original name
   rdModel3_BuildShadowModel (the remaster's GrimFandango (Linux): aligned call in
   rdModel3_LoadPostProcess); was rdModel3_BuildBoundingBoxCorners. */

void __cdecl rdModel3_BuildShadowModel(int param_1)

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
            (*g_pRdroid_HS->pFree)(*(int *)(iVar4 + 0x58));
          }
          puVar1 = (undefined4 *)
                   (*g_pRdroid_HS->pAlloc)
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
   rdModel3_CalcModelBoundingBox), and the model's center and radius. Source file Rdmodel3.c
   (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */

void __cdecl rdModel3_CalcBoundingBoxes(uint param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  int iVar5;
  float *pfVar6;
  int iVar7;
  int iVar8;
  uint *puVar9;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar4 = param_1;
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
    } while (local_4 < *(uint *)(uVar4 + 0x44));
  }
  *(undefined4 *)(uVar4 + 0x60) = 0x7f7fc99e;
  *(undefined4 *)(uVar4 + 100) = 0x7f7fc99e;
  *(undefined4 *)(uVar4 + 0x68) = 0x7f7fc99e;
  *(undefined4 *)(uVar4 + 0x6c) = 0xff7fc99e;
  *(undefined4 *)(uVar4 + 0x70) = 0xff7fc99e;
  *(undefined4 *)(uVar4 + 0x74) = 0xff7fc99e;
  rdModel3_CalcModelBoundingBox(uVar4,*(int *)(uVar4 + 0x58),g_flRdroid_identMatrix34);
  fVar3 = *(float *)(uVar4 + 0x60) - *(float *)(uVar4 + 0x6c);
  fVar1 = *(float *)(uVar4 + 100) - *(float *)(uVar4 + 0x70);
  fVar2 = *(float *)(uVar4 + 0x68) - *(float *)(uVar4 + 0x74);
  *(float *)(uVar4 + 0x78) =
       (*(float *)(uVar4 + 0x6c) - *(float *)(uVar4 + 0x60)) * 0.5 + *(float *)(uVar4 + 0x60);
  *(float *)(uVar4 + 0x7c) =
       (*(float *)(uVar4 + 0x70) - *(float *)(uVar4 + 100)) * 0.5 + *(float *)(uVar4 + 100);
  *(float *)(uVar4 + 0x80) =
       (*(float *)(uVar4 + 0x74) - *(float *)(uVar4 + 0x68)) * 0.5 + *(float *)(uVar4 + 0x68);
  *(float *)(uVar4 + 0x5c) = SQRT(fVar2 * fVar2 + fVar1 * fVar1 + fVar3 * fVar3) * 0.5;
  return;
}
#undef local_4


/* ---- 0x0040c710  rdModel3_CalcModelBoundingBox ---- */
/* Recursively composes the node matrices (angles, offset, pivot) and accumulates the transformed
   mesh boxes into the model bounds. Source file Rdmodel3.c
   (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). Original name rdModel3_CalcModelBoundingBox (the
   remaster's GrimFandango (Linux): the only unmatched callee of rdModel3_CalcBoundingBoxes; 1
   matched neighbours agree, 0 disagree); was rdModel3_AccumulateNodeBounds. */

void __cdecl rdModel3_CalcModelBoundingBox(int param_1,int param_2,float *param_3)

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
  #define local_30 (*(float (*)[12])(_frame + (0xc0 - 0x30)))
  
  rdMatrix_Build34(local_30,(uint *)(param_2 + 0x7c),(float *)(param_2 + 0x70));
  rdMatrix_BuildTranslate34(local_90,(float *)(param_2 + 100));
  rdMatrix_PostMultiply34(local_90,local_30);
  iVar3 = *(int *)(param_2 + 0x54);
  if (iVar3 != 0) {
    local_9c[0] = -*(float *)(iVar3 + 100);
    local_9c[1] = -*(float *)(iVar3 + 0x68);
    local_9c[2] = -*(float *)(iVar3 + 0x6c);
    rdMatrix_PostTranslate34((int)local_90,local_9c);
  }
  rdMatrix_Multiply34(local_60,param_3,local_90);
  iVar3 = *(int *)(param_2 + 0x4c);
  if (iVar3 != -1) {
    iVar1 = *(int *)(param_1 + 0x28);
    uVar2 = 0;
    a = *(float **)(iVar1 + 0x30 + iVar3 * 0x7c);
    if (*(int *)(iVar1 + 0x48 + iVar3 * 0x7c) != 0) {
      do {
        rdMatrix_TransformPoint34(&local_a8,a,local_60);
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
        rdModel3_CalcModelBoundingBox(param_1,iVar3,local_60);
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
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Computes the bounding radius of every mesh (largest vertex distance) and of the model. Source
   file Rdmodel3.c (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */

void __cdecl rdModel3_CalcRadii(int param_1)

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
      piVar4[6] = PUN(int,(float)(fVar1 * 0.1f + fVar1));
      piVar4 = piVar4 + 0x1f;
    } while (uVar6 < *(uint *)(param_1 + 0x24));
  }
  _g_dwMaxGeoRadius = 0;
  rdModel3_BuildExpandedRadius(param_1,*(int *)(param_1 + 0x58),g_flRdroid_identMatrix34);
  return;
}
#undef local_4

#endif


/* ---- 0x0040c970  rdModel3_BuildExpandedRadius ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Recursive helper of rdModel3_CalcRadii: composes node matrices and updates the radius. Source
   file Rdmodel3.c (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). Original name
   rdModel3_BuildExpandedRadius (the remaster's GrimFandango (Linux): the only unmatched callee of
   rdModel3_CalcRadii; 1 matched neighbours agree, 0 disagree); was rdModel3_AccumulateNodeRadius.
    */

void __cdecl rdModel3_BuildExpandedRadius(int param_1,int param_2,float *param_3)

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
  #define local_30 (*(float (*)[12])(_frame + (0xc0 - 0x30)))
  
  rdMatrix_Build34(local_30,(uint *)(param_2 + 0x7c),(float *)(param_2 + 0x70));
  rdMatrix_BuildTranslate34(local_90,(float *)(param_2 + 100));
  rdMatrix_PostMultiply34(local_90,local_30);
  iVar4 = *(int *)(param_2 + 0x54);
  if (iVar4 != 0) {
    local_9c[0] = -*(float *)(iVar4 + 100);
    local_9c[1] = -*(float *)(iVar4 + 0x68);
    local_9c[2] = -*(float *)(iVar4 + 0x6c);
    rdMatrix_PostTranslate34((int)local_90,local_9c);
  }
  rdMatrix_Multiply34(local_60,param_3,local_90);
  iVar4 = *(int *)(param_2 + 0x4c);
  if (iVar4 != -1) {
    iVar1 = *(int *)(param_1 + 0x28);
    uVar3 = 0;
    a = *(float **)(iVar1 + 0x30 + iVar4 * 0x7c);
    if (*(int *)(iVar1 + 0x48 + iVar4 * 0x7c) != 0) {
      do {
        rdMatrix_TransformPoint34(local_a8,a,local_60);
        fVar2 = SQRT(local_a8[2] * local_a8[2] +
                     local_a8[1] * local_a8[1] + local_a8[0] * local_a8[0]);
        if (*(float *)&g_dwMaxGeoRadius < fVar2) {
          *(float *)&g_dwMaxGeoRadius = fVar2;
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
        rdModel3_BuildExpandedRadius(param_1,iVar4,local_60);
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
/* Computes the normal of every face from three non-collinear vertices (rdMath_CalcSurfaceNormal,
   rdMath_PointsCollinear). Source file Rdmodel3.c (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c).
    */

void __cdecl rdModel3_CalcFaceNormals(uint param_1)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  int iVar2;
  uint *puVar3;
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
  puVar3 = (uint *)(param_1 + 0x24);
  uVar5 = param_1;
  if (*(int *)(param_1 + 0x44) != 0) {
    do {
      local_c = 0;
      if (*puVar3 != 0) {
        piVar6 = (int *)(puVar3[1] + 0x30);
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
                  iVar2 = *piVar6;
                  uVar4 = rdMath_PointsCollinear
                                    ((float *)(iVar2 + *(int *)(uVar4 + uVar7 * 4) * 0xc),
                                     (float *)(iVar2 + *(int *)(uVar4 + uVar5 * 4) * 0xc),
                                     (float *)(iVar2 + *(int *)(uVar4 + local_18 * 4) * 0xc));
                } while ((uVar4 != 0) && (uVar4 = *puVar8, uVar7 = uVar1, (int)uVar1 < (int)uVar4));
              }
              if ((int)uVar7 < (int)*puVar8) {
                uVar4 = puVar8[1];
                iVar2 = *piVar6;
                rdMath_CalcSurfaceNormal
                          ((float *)(puVar8 + 0xb),
                           (float *)(iVar2 + *(int *)(uVar4 + uVar7 * 4) * 0xc),
                           (float *)(iVar2 + *(int *)(uVar4 + uVar5 * 4) * 0xc),
                           (float *)(iVar2 + *(int *)(uVar4 + local_18 * 4) * 0xc));
              }
              puVar8 = puVar8 + 0x13;
              local_10 = local_10 + 1;
            } while (local_10 < (uint)piVar6[8]);
          }
          piVar6 = piVar6 + 0x1f;
          local_c = local_c + 1;
        } while (local_c < *puVar3);
      }
      puVar3 = puVar3 + 2;
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
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Averages the normals of the faces that share a vertex (or builds one from the neighbouring edges)
   and normalises. Source file Rdmodel3.c (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */

void __cdecl rdModel3_CalcVertexNormals(int param_1)

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
                rdVector_Normalize3Acc(pfVar16);
              }
              else {
                *pfVar16 = fVar1 / local_44[0];
                pfVar16[1] = local_20[0] / local_44[0];
                pfVar16[2] = local_20[1] / local_44[0];
                rdVector_Normalize3Acc(pfVar16);
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

void __cdecl rdModel3_CountNodeChildren(int param_1)

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
