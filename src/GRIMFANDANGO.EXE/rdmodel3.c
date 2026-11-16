/* GRIMFANDANGO.EXE :: rdmodel3.c
 * functions 0x0040a8c0 .. 0x0040ce90 (16 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0040a8c0  rdModel3_NewEntry ---- */
/* Clears a 0x90-byte model record and names it UNKNOWN. Source file Rdmodel3.c
   (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */

void __cdecl rdModel3_NewEntry(rdModel3 *model)

{
  int iVar1;
  rdModel3 *prVar2;
  
  prVar2 = model;
  for (iVar1 = 0x24; iVar1 != 0; iVar1 = iVar1 + -1) {
    prVar2->aName[0] = '\0';
    prVar2->aName[1] = '\0';
    prVar2->aName[2] = '\0';
    prVar2->aName[3] = '\0';
    prVar2 = (rdModel3 *)(prVar2->aName + 4);
  }
  strncpy((uint *)model,(uint *)s_UNKNOWN_004ddb8c,0x1f);
  model->aName[0x1f] = '\0';
  model->nCurGeoset = 0;
  return;
}

/* ---- 0x0040a8f0  rdModel3_Load ---- */
/* Loads a model: calls the custom loader hook if one is installed, otherwise allocates the record,
   rdModel3_Load, then rdModel3_LoadPostProcess. Source file Rdmodel3.c
   (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). Original name rdModel3_Load (the remaster's
   GrimFandango (Linux): same body (loader hook, 0x90-byte model, load, post-process, free on
   failure); sputResource_ModelHandler's call); was rdModel3_New. */

undefined4 * __cdecl rdModel3_Load(uint name)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  
  if (g_dwModel3Loader != 0) {
    puVar1 = (undefined4 *)(*(code *)g_dwModel3Loader)(name,0);
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
    uVar2 = rdModel3_LoadEntry(name,(uint)puVar1);
    if (uVar2 != 0) {
      rdModel3_LoadPostProcess((uint)puVar1);
      return puVar1;
    }
  }
  rdModel3_Free((int)puVar1);
  return (undefined4 *)0x0;
}

/* ---- 0x0040a980  rdModel3_LoadEntry ---- */
/* Opens the file; the magic 'MODL' selects rdModel3_LoadBinary, anything else is parsed by
   rdModel3_LoadText. Source file Rdmodel3.c (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c).
   Original name rdModel3_LoadEntry (the remaster's GrimFandango (Linux): same body (open, 'LDOM'
   magic -> LoadEntryBinary else LoadEntryText)); was rdModel3_Load. */

uint __cdecl rdModel3_LoadEntry(int name,uint model)

{
  int path;
  int f;
  uint uVar1;
  
  path = name;
  f = (*g_pRdroid_HS->pFopen)(name,s_rb_004ddb18);
  if (f == 0) {
    return 0;
  }
  (*g_pRdroid_HS->pFread)(f,&name,4);
  if (name == 0x4d4f444c) {
    uVar1 = rdModel3_LoadEntryBinary(f,model);
    if (uVar1 != 0) {
      (*g_pRdroid_HS->pFclose)(f);
      return 1;
    }
    (*g_pRdroid_HS->pFclose)(f);
    return 0;
  }
  (*g_pRdroid_HS->pFclose)(f);
  uVar1 = rdModel3_LoadEntryText((char *)path,(rdModel3 *)model);
  return uVar1;
}

/* ---- 0x0040aa20  rdModel3_LoadEntryText ---- */
/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */
/* Parser of the text .3do format (stdConffile 'section:' lines). Source file Rdmodel3.c
   (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */

uint __cdecl rdModel3_LoadEntryText(char *path,rdModel3 *model)

{
  unsigned char _frame[0x20420] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  rdMaterial *prVar5;
  rdMesh *prVar6;
  float *pfVar7;
  undefined4 *puVar8;
  int iVar9;
  void *pvVar10;
  undefined *puVar11;
  char *pcVar12;
  undefined *puVar13;
  rdHierarchyNode *prVar14;
  uint uVar15;
  undefined *puVar16;
  uint *puVar17;
  char *pcVar18;
  char *pcVar19;
  uint uVar20;
  uint uStack_20488;
  float fStack_20484;
  float fStack_20480;
  float fStack_2047c;
  int iStack_20478;
  uint uStack_20474;
  uint uStack_20470;
  uint uStack_2046c;
  uint uStack_20468;
  rdMesh **pprStack_20464;
  uint uStack_20460;
  int iStack_2045c;
  uint uStack_20458;
  uint uStack_20454;
  uint *puStack_20450;
  uint uStack_2044c;
  uint uStack_20448;
  float fStack_20444;
  float fStack_20440;
  float fStack_2043c;
  float flIntensity;
  float fStack_20434;
  float fStack_20430;
  float fStack_2042c;
  int iStack_20428;
  float fStack_20424;
  int iStack_20420;
  float fStack_2041c;
  float fStack_20418;
  uint uStack_20414;
  int iStack_20410;
  #define uStack_2040c (*(uint *)(_frame + (0x20420 - 0x2040c)))
  int nVersionMinor;
  int nVersionMajor;
  #define acStack_20400 (*(char (*)[1024])(_frame + (0x20420 - 0x20400)))
  #define acStack_20000 (*(char (*)[131072])(_frame + (0x20420 - 0x20000)))
  
  rdModel3_NewEntry(model);
  uVar20 = 0x1f;
  puVar2 = (uint *)stdFileFromPath(path);
  strncpy((uint *)model,puVar2,uVar20);
  model->aName[0x1f] = '\0';
  uVar20 = stdConffile_Open((uint)path);
  if (uVar20 == 0) {
    return 0;
  }
  uVar20 = stdConffile_ReadLine();
  if (((uVar20 != 0) &&
      (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_section___s_004ddd64,&g_bStd_genBuffer),
      iVar3 == 1)) && (uVar20 = stdConffile_ReadLine(), uVar20 != 0)) {
    sscanf((char *)g_dwStdConffile_aLine,s_3do__d__d_004ddd58,&nVersionMajor,&nVersionMinor);
    uVar20 = stdConffile_ReadLine();
    if (((uVar20 != 0) &&
        (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_section___s_004ddd64,&g_bStd_genBuffer),
        iVar3 == 1)) &&
       ((uVar20 = stdConffile_ReadLine(), uVar20 != 0 &&
        (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_materials__d_004ddd48,&uStack_20474),
        iVar3 == 1)))) {
      if (uStack_20474 != 0) {
        if (0x7f < uStack_20474) {
          (*g_pRdroid_HS->pAssertFail)
                    (s_numMaterials___MAX_MATS_004ddd30,s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,
                     DAT_004ddb80 + 0x46);
        }
        iVar3 = (*g_pRdroid_HS->pAlloc)
                          (uStack_20474 * 4,s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,
                           DAT_004ddb80 + 0x49);
        *(int *)&model->field_0x48 = iVar3;
        if (iVar3 == 0) goto LAB_0040b8c4;
        uVar20 = 0;
        if (uStack_20474 != 0) {
          do {
            uVar4 = stdConffile_ReadLine();
            if ((uVar4 == 0) ||
               (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s__d___s_004ddd28,&iStack_20478,
                               acStack_20400), iVar3 != 2)) goto LAB_0040b8c4;
            uVar4 = 0xffffffff;
            pcVar18 = acStack_20400;
            do {
              pcVar12 = pcVar18;
              if (uVar4 == 0) break;
              uVar4 = uVar4 - 1;
              pcVar12 = pcVar18 + 1;
              cVar1 = *pcVar18;
              pcVar18 = pcVar12;
            } while (cVar1 != '\0');
            uVar4 = ~uVar4;
            pcVar18 = pcVar12 + -uVar4;
            pcVar12 = acStack_20000 + iStack_20478 * 0x400;
            for (uVar15 = uVar4 >> 2; uVar15 != 0; uVar15 = uVar15 - 1) {
              *(undefined4 *)pcVar12 = *(undefined4 *)pcVar18;
              pcVar18 = pcVar18 + 4;
              pcVar12 = pcVar12 + 4;
            }
            uVar20 = uVar20 + 1;
            for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
              *pcVar12 = *pcVar18;
              pcVar18 = pcVar18 + 1;
              pcVar12 = pcVar12 + 1;
            }
          } while (uVar20 < uStack_20474);
        }
        uVar20 = 0;
        if (uStack_20474 != 0) {
          pcVar18 = acStack_20000;
          do {
            prVar5 = rdMaterial_Load(pcVar18,0,0);
            *(rdMaterial **)(*(int *)&model->field_0x48 + uVar20 * 4) = prVar5;
            if (*(int *)(*(int *)&model->field_0x48 + uVar20 * 4) == 0) goto LAB_0040b8c4;
            uVar20 = uVar20 + 1;
            pcVar18 = pcVar18 + 0x400;
          } while (uVar20 < uStack_20474);
        }
      }
      *(uint *)&model->field_0x4c = uStack_20474;
      uVar20 = stdConffile_ReadLine();
      if ((((uVar20 != 0) &&
           (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_section___s_004ddd64,&g_bStd_genBuffer),
           iVar3 == 1)) && (uVar20 = stdConffile_ReadLine(), uVar20 != 0)) &&
         (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_radius__f_004ddd1c,&fStack_20444),
         iVar3 == 1)) {
        model->flRadius = fStack_20444;
        uVar20 = stdConffile_ReadLine();
        if ((uVar20 != 0) &&
           (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_insert_offset__f__f__f_004ddd04,
                           &fStack_2047c,&fStack_20484,&fStack_20480), iVar3 == 3)) {
          *(float *)&model->field_0x84 = PUN(int,(float)(fStack_2047c));
          *(float *)&model->field_0x88 = PUN(int,(float)(fStack_20484));
          *(float *)&model->field_0x8c = PUN(int,(float)(fStack_20480));
          uVar20 = stdConffile_ReadLine();
          if ((uVar20 != 0) &&
             (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_geosets__d_004ddcf8,&uStack_20448),
             iVar3 == 1)) {
            uStack_2044c = 0;
            model->dwGeosets = uStack_20448;
            if (uStack_20448 != 0) {
              pprStack_20464 = &model->aGeosets[0].pMeshes;
              do {
                uVar20 = stdConffile_ReadLine();
                if (((uVar20 == 0) ||
                    (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_geoset__d_004ddcec,&iStack_20478
                                   ), iVar3 != 1)) ||
                   ((uVar20 = stdConffile_ReadLine(), uVar20 == 0 ||
                    (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_meshes__d_004ddce0,&uStack_20470
                                   ), iVar3 != 1)))) goto LAB_0040b8c4;
                prVar6 = (rdMesh *)
                         (*g_pRdroid_HS->pAlloc)
                                   (uStack_20470 * 0x7c,s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,
                                    DAT_004ddb80 + 0xa1);
                *pprStack_20464 = prVar6;
                if (prVar6 == (rdMesh *)0x0) goto LAB_0040b8c4;
                uStack_20454 = 0;
                for (uVar20 = uStack_20470 * 0x1f & 0x3fffffff; uVar20 != 0; uVar20 = uVar20 - 1) {
                  prVar6->aName[0] = '\0';
                  prVar6->aName[1] = '\0';
                  prVar6->aName[2] = '\0';
                  prVar6->aName[3] = '\0';
                  prVar6 = (rdMesh *)(prVar6->aName + 4);
                }
                for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
                  prVar6->aName[0] = '\0';
                  prVar6 = (rdMesh *)(prVar6->aName + 1);
                }
                ((rdGeoset *)(pprStack_20464 + -1))->dwMeshes = uStack_20470;
                if (uStack_20470 != 0) {
                  iStack_2045c = 0;
                  do {
                    pcVar18 = (*pprStack_20464)->aName + iStack_2045c;
                    *(uint *)(pcVar18 + 0x20) = uStack_20454;
                    uVar20 = stdConffile_ReadLine();
                    if ((((uVar20 == 0) ||
                         (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_mesh__d_004ddcd4,
                                         &g_bStd_genBuffer), iVar3 != 1)) ||
                        (uVar20 = stdConffile_ReadLine(), uVar20 == 0)) ||
                       (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_name__s_004ddcc8,
                                       &g_bStd_genBuffer), iVar3 != 1)) goto LAB_0040b8c4;
                    strncpy((uint *)pcVar18,(uint *)&g_bStd_genBuffer,0x1f);
                    pcVar18[0x1f] = '\0';
                    uVar20 = stdConffile_ReadLine();
                    if (((uVar20 == 0) ||
                        (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_radius__f_004ddd1c,
                                        pcVar18 + 0x60), iVar3 != 1)) ||
                       (uVar20 = stdConffile_ReadLine(), uVar20 == 0)) goto LAB_0040b8c4;
                    iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_shadow__d_004ddcbc,&uStack_20414)
                    ;
                    if (iVar3 == 1) {
                      *(uint *)(pcVar18 + 0x54) = uStack_20414;
                      uVar20 = stdConffile_ReadLine();
                      if (uVar20 == 0) goto LAB_0040b8c4;
                    }
                    iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_geometrymode__d_004ddca8,
                                   pcVar18 + 0x24);
                    if ((((iVar3 != 1) || (uVar20 = stdConffile_ReadLine(), uVar20 == 0)) ||
                        ((iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_lightingmode__d_004ddc94,
                                         pcVar18 + 0x28), iVar3 != 1 ||
                         (((uVar20 = stdConffile_ReadLine(), uVar20 == 0 ||
                           (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_texturemode__d_004ddc84,
                                           pcVar18 + 0x2c), iVar3 != 1)) ||
                          (uVar20 = stdConffile_ReadLine(), uVar20 == 0)))))) ||
                       ((iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_vertices__d_004ddc74,
                                        &uStack_20488), iVar3 != 1 || (0x200 < uStack_20488))))
                    goto LAB_0040b8c4;
                    *(float **)(pcVar18 + 0x30) = (float *)0x0;
                    *(uint *)(pcVar18 + 0x38) = 0;
                    *(uint *)(pcVar18 + 0x3c) = 0;
                    if (uStack_20488 != 0) {
                      pfVar7 = (float *)(*g_pRdroid_HS->pAlloc)
                                                  (uStack_20488 * 0xc,
                                                   s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,
                                                   DAT_004ddb80 + 0xf5);
                      *(float **)(pcVar18 + 0x30) = pfVar7;
                      if (pfVar7 == (float *)0x0) goto LAB_0040b8c4;
                      uVar20 = (*g_pRdroid_HS->pAlloc)
                                         (uStack_20488 * 4,
                                          s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,
                                          DAT_004ddb80 + 0xfa);
                      *(uint *)(pcVar18 + 0x38) = uVar20;
                      if (uVar20 == 0) goto LAB_0040b8c4;
                      puVar8 = (undefined4 *)
                               (*g_pRdroid_HS->pAlloc)
                                         (uStack_20488 * 4,
                                          s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,
                                          DAT_004ddb80 + 0xfe);
                      *(undefined4 **)(pcVar18 + 0x3c) = puVar8;
                      if (puVar8 == (undefined4 *)0x0) goto LAB_0040b8c4;
                      for (uVar20 = uStack_20488 >> 2; uVar20 != 0; uVar20 = uVar20 - 1) {
                        *puVar8 = 0;
                        puVar8 = puVar8 + 1;
                      }
                      for (uVar20 = uStack_20488 & 3; uVar20 != 0; uVar20 = uVar20 - 1) {
                        *(undefined1 *)puVar8 = 0;
                        puVar8 = (undefined4 *)((int)puVar8 + 1);
                      }
                    }
                    pfVar7 = *(float **)(pcVar18 + 0x30);
                    uVar20 = 0;
                    if (uStack_20488 != 0) {
                      do {
                        uVar4 = stdConffile_ReadLine();
                        if ((uVar4 == 0) ||
                           (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s__d___f__f__f__f_004ddc60,
                                           &iStack_20478,&fStack_2047c,&fStack_20484,&fStack_20480,
                                           &flIntensity), iVar3 != 5)) goto LAB_0040b8c4;
                        *pfVar7 = fStack_2047c;
                        pfVar7[1] = fStack_20484;
                        pfVar7[2] = fStack_20480;
                        pfVar7 = pfVar7 + 3;
                        *(float *)(*(uint *)(pcVar18 + 0x38) + uVar20 * 4) = flIntensity;
                        uVar20 = uVar20 + 1;
                      } while (uVar20 < uStack_20488);
                    }
                    *(uint *)(pcVar18 + 0x48) = uStack_20488;
                    uVar20 = stdConffile_ReadLine();
                    if (((uVar20 == 0) ||
                        (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_texture_vertices__d_004ddc48
                                        ,&uStack_2046c), iVar3 != 1)) || (0x300 < uStack_2046c))
                    goto LAB_0040b8c4;
                    *(float **)(pcVar18 + 0x34) = (float *)0x0;
                    if (uStack_2046c != 0) {
                      pfVar7 = (float *)(*g_pRdroid_HS->pAlloc)
                                                  (uStack_2046c * 8,
                                                   s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,
                                                   DAT_004ddb80 + 0x128);
                      *(float **)(pcVar18 + 0x34) = pfVar7;
                      if (pfVar7 == (float *)0x0) goto LAB_0040b8c4;
                      uVar20 = 0;
                      if (uStack_2046c != 0) {
                        do {
                          uVar4 = stdConffile_ReadLine();
                          if ((uVar4 == 0) ||
                             (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s__d___f__f_004ddc3c,
                                             &iStack_20478,&fStack_20418,&fStack_20430), iVar3 != 3)
                             ) goto LAB_0040b8c4;
                          *pfVar7 = fStack_20418;
                          pfVar7[1] = fStack_20430;
                          pfVar7 = pfVar7 + 2;
                          uVar20 = uVar20 + 1;
                        } while (uVar20 < uStack_2046c);
                      }
                    }
                    *(uint *)(pcVar18 + 0x4c) = uStack_2046c;
                    uVar20 = stdConffile_ReadLine();
                    if (uVar20 == 0) goto LAB_0040b8c4;
                    *(float **)(pcVar18 + 0x44) = (float *)0x0;
                    if (uStack_20488 != 0) {
                      pfVar7 = (float *)(*g_pRdroid_HS->pAlloc)
                                                  (uStack_20488 * 0xc,
                                                   s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,
                                                   DAT_004ddb80 + 0x148);
                      *(float **)(pcVar18 + 0x44) = pfVar7;
                      if (pfVar7 == (float *)0x0) goto LAB_0040b8c4;
                    }
                    uVar20 = 0;
                    if (uStack_20488 != 0) {
                      iVar3 = 0;
                      do {
                        uVar4 = stdConffile_ReadLine();
                        if ((uVar4 == 0) ||
                           (iVar9 = sscanf((char *)g_dwStdConffile_aLine,s__d___f__f__f_004ddc2c,
                                           &iStack_20478,&fStack_2047c,&fStack_20484,&fStack_20480),
                           iVar9 != 4)) goto LAB_0040b8c4;
                        uVar20 = uVar20 + 1;
                        *(float *)(iVar3 + (int)*(float **)(pcVar18 + 0x44)) = fStack_2047c;
                        *(float *)(iVar3 + 4 + (int)*(float **)(pcVar18 + 0x44)) = fStack_20484;
                        *(float *)(iVar3 + 8 + (int)*(float **)(pcVar18 + 0x44)) = fStack_20480;
                        iVar3 = iVar3 + 0xc;
                      } while (uVar20 < uStack_20488);
                    }
                    uVar20 = stdConffile_ReadLine();
                    if (((uVar20 == 0) ||
                        (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_faces__d_004ddc20,
                                        &uStack_20468), iVar3 != 1)) || (0x200 < uStack_20468))
                    goto LAB_0040b8c4;
                    *(uint *)(pcVar18 + 0x50) = uStack_20468;
                    *(void **)(pcVar18 + 0x40) = (void *)0x0;
                    if (uStack_20468 != 0) {
                      pvVar10 = (void *)(*g_pRdroid_HS->pAlloc)
                                                  (uStack_20468 * 0x4c,
                                                   s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,
                                                   DAT_004ddb80 + 0x16d);
                      *(void **)(pcVar18 + 0x40) = pvVar10;
                      if (pvVar10 == (void *)0x0) goto LAB_0040b8c4;
                    }
                    puVar2 = *(uint **)(pcVar18 + 0x40);
                    uStack_20460 = 0;
                    puStack_20450 = puVar2;
                    if (uStack_20468 != 0) {
                      puVar17 = puVar2 + 2;
                      do {
                        puStack_20450 = puVar2;
                        uVar20 = stdConffile_ReadLine();
                        if (uVar20 == 0) goto LAB_0040b8c4;
                        rdFace_NewEntry(puVar2);
                        strtok((byte *)g_dwStdConffile_aLine,(byte *)s__004dd918);
                        uVar20 = strtok((byte *)0x0,(byte *)s__004dd918);
                        puVar11 = atoi(uVar20);
                        *puVar2 = uStack_20460;
                        if (puVar11 == (undefined *)0xffffffff) {
                          puVar17[6] = 0;
                        }
                        else {
                          puVar17[6] = *(uint *)(*(int *)&model->field_0x48 + (int)puVar11 * 4);
                        }
                        puVar2 = puVar17 + -1;
                        pcVar19 = s__x_004ddc1c;
                        pcVar12 = (char *)strtok((byte *)0x0,(byte *)s__004dd918);
                        iVar3 = sscanf(pcVar12,pcVar19,puVar2);
                        if (iVar3 != 1) goto LAB_0040b8c4;
                        pcVar19 = s__d_004ddc18;
                        puVar2 = puVar17;
                        pcVar12 = (char *)strtok((byte *)0x0,(byte *)s__004dd918);
                        iVar3 = sscanf(pcVar12,pcVar19,puVar2);
                        if (iVar3 != 1) goto LAB_0040b8c4;
                        puVar2 = puVar17 + 1;
                        pcVar19 = s__d_004ddc18;
                        pcVar12 = (char *)strtok((byte *)0x0,(byte *)s__004dd918);
                        iVar3 = sscanf(pcVar12,pcVar19,puVar2);
                        if (iVar3 != 1) goto LAB_0040b8c4;
                        puVar2 = puVar17 + 2;
                        pcVar19 = s__d_004ddc18;
                        pcVar12 = (char *)strtok((byte *)0x0,(byte *)s__004dd918);
                        iVar3 = sscanf(pcVar12,pcVar19,puVar2);
                        if (iVar3 != 1) goto LAB_0040b8c4;
                        puVar2 = &uStack_2040c;
                        pcVar19 = s__f_004ddc14;
                        pcVar12 = (char *)strtok((byte *)0x0,(byte *)s__004dd918);
                        iVar3 = sscanf(pcVar12,pcVar19,puVar2);
                        if (iVar3 != 1) goto LAB_0040b8c4;
                        puVar17[10] = uStack_2040c;
                        uVar20 = strtok((byte *)0x0,(byte *)s__004dd918);
                        puVar11 = atoi(uVar20);
                        if ((puVar11 == (undefined *)0x0) || ((undefined *)0x18 < puVar11))
                        goto LAB_0040b8c4;
                        puVar17[3] = (uint)puVar11;
                        uVar20 = (*g_pRdroid_HS->pAlloc)
                                           ((int)puVar11 * 4,
                                            s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,
                                            DAT_004ddb80 + 0x1a9);
                        puVar17[4] = uVar20;
                        if (uVar20 == 0) goto LAB_0040b8c4;
                        if (((byte *)puVar17[6] == (byte *)0x0) || ((*(byte *)puVar17[6] & 2) == 0))
                        {
                          puVar16 = (undefined *)0x0;
                          if (puVar11 != (undefined *)0x0) {
                            do {
                              uVar20 = strtok((byte *)0x0,(byte *)s___004ddc10);
                              puVar13 = atoi(uVar20);
                              *(undefined **)(puVar17[4] + (int)puVar16 * 4) = puVar13;
                              strtok((byte *)0x0,(byte *)s___004ddc10);
                              puVar16 = puVar16 + 1;
                            } while (puVar16 < puVar11);
                          }
                        }
                        else {
                          uVar20 = (*g_pRdroid_HS->pAlloc)
                                             ((int)puVar11 * 4,
                                              s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,
                                              DAT_004ddb80 + 0x1b0);
                          puVar17[5] = uVar20;
                          if (uVar20 == 0) goto LAB_0040b8c4;
                          puVar16 = (undefined *)0x0;
                          if (puVar11 != (undefined *)0x0) {
                            do {
                              uVar20 = strtok((byte *)0x0,(byte *)s___004ddc10);
                              puVar13 = atoi(uVar20);
                              *(undefined **)(puVar17[4] + (int)puVar16 * 4) = puVar13;
                              uVar20 = strtok((byte *)0x0,(byte *)s___004ddc10);
                              puVar13 = atoi(uVar20);
                              *(undefined **)(puVar17[5] + (int)puVar16 * 4) = puVar13;
                              puVar16 = puVar16 + 1;
                            } while (puVar16 < puVar11);
                          }
                        }
                        puVar2 = puStack_20450 + 0x13;
                        puVar17 = puVar17 + 0x13;
                        uStack_20460 = uStack_20460 + 1;
                        puStack_20450 = puVar2;
                      } while (uStack_20460 < uStack_20468);
                    }
                    uVar20 = stdConffile_ReadLine();
                    if (uVar20 == 0) goto LAB_0040b8c4;
                    uVar20 = 0;
                    if (*(uint *)(pcVar18 + 0x50) != 0) {
                      pfVar7 = (float *)((int)*(void **)(pcVar18 + 0x40) + 0x44);
                      do {
                        uVar4 = stdConffile_ReadLine();
                        if ((uVar4 == 0) ||
                           (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s__d___f__f__f_004ddc2c,
                                           &iStack_20478,&fStack_2047c,&fStack_20484,&fStack_20480),
                           iVar3 != 4)) goto LAB_0040b8c4;
                        pfVar7[-1] = fStack_2047c;
                        *pfVar7 = fStack_20484;
                        pfVar7[1] = fStack_20480;
                        pfVar7 = pfVar7 + 0x13;
                        uVar20 = uVar20 + 1;
                      } while (uVar20 < *(uint *)(pcVar18 + 0x50));
                    }
                    uStack_20454 = uStack_20454 + 1;
                    iStack_2045c = iStack_2045c + 0x7c;
                  } while (uStack_20454 < uStack_20470);
                }
                uStack_2044c = uStack_2044c + 1;
                pprStack_20464 = pprStack_20464 + 2;
              } while (uStack_2044c < uStack_20448);
            }
            uVar20 = stdConffile_ReadLine();
            if ((((uVar20 != 0) &&
                 (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_section___s_004ddd64,
                                 &g_bStd_genBuffer), iVar3 == 1)) &&
                (uVar20 = stdConffile_ReadLine(), uVar20 != 0)) &&
               (iVar3 = sscanf((char *)g_dwStdConffile_aLine,s_hierarchy_nodes__d_004ddbfc,
                               &uStack_20458), iVar3 == 1)) {
              prVar14 = (rdHierarchyNode *)
                        (*g_pRdroid_HS->pAlloc)
                                  (uStack_20458 * 0xb8,s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,
                                   DAT_004ddb80 + 0x1ef);
              model->pHierarchyNodes = prVar14;
              if (prVar14 != (rdHierarchyNode *)0x0) {
                uVar20 = 0;
                model->nNumHierarchyNodes = uStack_20458;
                if (uStack_20458 != 0) {
                  iVar3 = 0;
                  do {
                    prVar14 = model->pHierarchyNodes;
                    *(uint *)((int)prVar14->aPivot + iVar3 + -0x20) = uVar20;
                    pcVar18 = prVar14->aName + iVar3;
                    uVar4 = stdConffile_ReadLine();
                    if ((uVar4 == 0) ||
                       (iVar9 = sscanf((char *)g_dwStdConffile_aLine,
                                       s__d___x__x__d__d__d__d__d__f__f___004ddbc4,&iStack_20478,
                                       pcVar18 + 0x40,pcVar18 + 0x48,pcVar18 + 0x4c,&iStack_20428,
                                       &iStack_20410,&iStack_20420,pcVar18 + 0x58,&fStack_2047c,
                                       &fStack_20484,&fStack_20480,&fStack_20440,&fStack_2043c,
                                       &fStack_20434,&fStack_2042c,&fStack_20424,&fStack_2041c,
                                       pcVar18), iVar9 != 0x12)) goto LAB_0040b8c4;
                    if (iStack_20428 == -1) {
                      *(rdHierarchyNode **)(pcVar18 + 0x54) = (rdHierarchyNode *)0x0;
                    }
                    else {
                      *(rdHierarchyNode **)(pcVar18 + 0x54) = model->pHierarchyNodes + iStack_20428;
                    }
                    if (iStack_20410 == -1) {
                      *(rdHierarchyNode **)(pcVar18 + 0x5c) = (rdHierarchyNode *)0x0;
                    }
                    else {
                      *(rdHierarchyNode **)(pcVar18 + 0x5c) = model->pHierarchyNodes + iStack_20410;
                    }
                    if (iStack_20420 == -1) {
                      *(rdHierarchyNode **)(pcVar18 + 0x60) = (rdHierarchyNode *)0x0;
                    }
                    else {
                      *(rdHierarchyNode **)(pcVar18 + 0x60) = model->pHierarchyNodes + iStack_20420;
                    }
                    uVar20 = uVar20 + 1;
                    *(float *)(pcVar18 + 0x70) = fStack_2047c;
                    *(float *)(pcVar18 + 0x74) = fStack_20484;
                    *(float *)(pcVar18 + 0x78) = fStack_20480;
                    *(float *)(pcVar18 + 0x7c) = fStack_20440;
                    *(float *)(pcVar18 + 0x80) = fStack_2043c;
                    *(float *)(pcVar18 + 0x84) = fStack_20434;
                    *(float *)(pcVar18 + 100) = fStack_2042c;
                    *(float *)(pcVar18 + 0x68) = fStack_20424;
                    *(float *)(pcVar18 + 0x6c) = fStack_2041c;
                    iVar3 = iVar3 + 0xb8;
                  } while (uVar20 < uStack_20458);
                }
                rdModel3_CountNodeChildren((int)model);
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
#undef acStack_20000
#undef acStack_20400
#undef uStack_2040c


/* ---- 0x0040b8e0  rdModel3_LoadEntryBinary ---- */
/* Reader of the binary 'MODL' model format (materials, geometry sets, meshes, hierarchy nodes).
   Source file Rdmodel3.c (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). Original name
   rdModel3_LoadEntryBinary (the remaster's GrimFandango (Linux): the only unmatched callee of
   rdModel3_LoadEntry; 2 matched neighbours agree, 1 disagree); was rdModel3_LoadBinary. */

uint __cdecl rdModel3_LoadEntryBinary(int f,int model)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  rdMaterial *prVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int *piVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  char *name;
  int iStack_24;
  uint local_1c;
  int iStack_18;
  int iStack_14;
  int iStack_c;
  int local_8;
  undefined4 uStack_4;
  
  iVar12 = model;
  iVar9 = f;
  uVar14 = 0;
  local_1c = 0;
  rdModel3_NewEntry((rdModel3 *)model);
  (*g_pRdroid_HS->pFread)(f,&local_8,4);
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
      (*g_pRdroid_HS->pFread)(f,uVar10,0x20);
      uVar10 = uVar10 + 0x20;
      uVar14 = uVar14 + 1;
    } while (uVar14 < *(uint *)(iVar12 + 0x4c));
  }
  (*g_pRdroid_HS->pFread)(f,iVar12,0x20);
  (*g_pRdroid_HS->pFread)(f,iVar12 + 0x20,4);
  piVar1 = (int *)(iVar12 + 0x44);
  (*g_pRdroid_HS->pFread)(f,piVar1,4);
  f = 0;
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
          iVar12 = model;
        } while (iStack_24 < *piVar11);
      }
      f = f + 1;
      piVar11 = piVar11 + 2;
    } while (f < *piVar1);
  }
  (*g_pRdroid_HS->pFread)(iVar9,iVar12 + 0x50,4);
  piVar11 = (int *)(iVar12 + 0x54);
  (*g_pRdroid_HS->pFread)(iVar9,piVar11,4);
  uVar5 = (*g_pRdroid_HS->pAlloc)
                    (*piVar11 * 0xb8,s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94,DAT_004ddb84 + 0x6c
                    );
  *(undefined4 *)(iVar12 + 0x58) = uVar5;
  iVar8 = 0;
  f = 0;
  if (0 < *piVar11) {
    do {
      iVar13 = iVar8 + *(int *)(iVar12 + 0x58);
      (*g_pRdroid_HS->pFread)(iVar9,iVar13,0xb8);
      if (*(int *)(iVar13 + 0x54) != 0) {
        (*g_pRdroid_HS->pFread)(iVar9,&model,4);
        *(int *)(iVar13 + 0x54) = *(int *)(iVar12 + 0x58) + model * 0xb8;
      }
      if (*(int *)(iVar13 + 0x5c) != 0) {
        (*g_pRdroid_HS->pFread)(iVar9,&model,4);
        *(int *)(iVar13 + 0x5c) = *(int *)(iVar12 + 0x58) + model * 0xb8;
      }
      if (*(int *)(iVar13 + 0x60) != 0) {
        (*g_pRdroid_HS->pFread)(iVar9,&model,4);
        *(int *)(iVar13 + 0x60) = *(int *)(iVar12 + 0x58) + model * 0xb8;
      }
      f = f + 1;
      iVar8 = iVar8 + 0xb8;
    } while (f < *(int *)(iVar12 + 0x54));
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
      prVar6 = rdMaterial_Load(name,0,0);
      name = name + 0x20;
      *(rdMaterial **)(*(int *)(iVar12 + 0x48) + uVar14 * 4) = prVar6;
      uVar14 = uVar14 + 1;
    } while (uVar14 < *(uint *)(iVar12 + 0x4c));
  }
  f = 0;
  if (0 < *piVar1) {
    piVar11 = (int *)(iVar12 + 0x24);
    do {
      iStack_24 = 0;
      if (0 < *piVar11) {
        model = 0;
        do {
          iVar8 = 0;
          iVar9 = model + piVar11[1];
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
          model = model + 0x7c;
        } while (iStack_24 < *piVar11);
      }
      f = f + 1;
      piVar11 = piVar11 + 2;
    } while (f < *piVar1);
  }
  if (local_1c != 0) {
    (*g_pRdroid_HS->pFree)(local_1c);
  }
  return 1;
}

/* ---- 0x0040c090  rdModel3_LoadPostProcess ---- */
/* Computes everything derived after loading: bounding boxes, radii, face and vertex normals, node
   child counts. Source file Rdmodel3.c (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */

void __cdecl rdModel3_LoadPostProcess(uint model)

{
  rdModel3_CalcBoundingBoxes(model);
  rdModel3_CalcRadii(model);
  rdModel3_CalcFaceNormals(model);
  rdModel3_CalcVertexNormals(model);
  rdModel3_CountNodeChildren(model);
  rdModel3_BuildShadowModel(model);
  return;
}

/* ---- 0x0040c0d0  rdModel3_Free ---- */
/* Frees a model (custom free hook if installed, else rdModel3_FreeEntry and the record). Source
   file Rdmodel3.c (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */

void __cdecl rdModel3_Free(int model)

{
  if (model != 0) {
    if (g_dwModel3Unloader != 0) {
      (*(code *)g_dwModel3Unloader)(model);
      return;
    }
    rdModel3_FreeEntry(model);
    (*g_pRdroid_HS->pFree)(model);
  }
  return;
}

/* ---- 0x0040c100  rdModel3_FreeEntry ---- */
/* Frees the contents of a model: materials, geometry sets, meshes, vertices, faces, hierarchy
   nodes. Source file Rdmodel3.c (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */

void __cdecl rdModel3_FreeEntry(int model)

{
  uint uVar1;
  uint *puVar2;
  int *piVar3;
  int face;
  uint local_8;
  uint local_4;
  
  if (model != 0) {
    puVar2 = (uint *)(model + 0x24);
    local_4 = 0;
    if (*(int *)(model + 0x44) != 0) {
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
            face = piVar3[3];
            if (face != 0) {
              uVar1 = 0;
              if (piVar3[7] != 0) {
                do {
                  rdFace_FreeEntry(face);
                  face = face + 0x4c;
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
      } while (local_4 < *(uint *)(model + 0x44));
    }
    if (*(int *)(model + 0x58) != 0) {
      (*g_pRdroid_HS->pFree)(*(int *)(model + 0x58));
    }
    uVar1 = 0;
    if (*(int *)(model + 0x4c) != 0) {
      do {
        rdMaterial_Free(*(uint *)(*(int *)(model + 0x48) + uVar1 * 4));
        uVar1 = uVar1 + 1;
      } while (uVar1 < *(uint *)(model + 0x4c));
    }
    if (*(int *)(model + 0x48) != 0) {
      (*g_pRdroid_HS->pFree)(*(int *)(model + 0x48));
    }
  }
  return;
}

/* ---- 0x0040c280  rdModel3_BuildShadowModel ---- */
/* Allocates 0xc0 bytes per mesh and fills the 8 corner points of its bounding box from the min/max
   values. Source file Rdmodel3.c (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). Original name
   rdModel3_BuildShadowModel (the remaster's GrimFandango (Linux): aligned call in
   rdModel3_LoadPostProcess); was rdModel3_BuildBoundingBoxCorners. */

void __cdecl rdModel3_BuildShadowModel(int model)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint *puVar5;
  uint local_4;
  
  local_4 = 0;
  if (*(int *)(model + 0x44) == 0) {
    return;
  }
  puVar5 = (uint *)(model + 0x24);
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
    if (*(uint *)(model + 0x44) <= local_4) {
      return;
    }
  } while( true );
}

/* ---- 0x0040c520  rdModel3_CalcBoundingBoxes ---- */
/* Computes the min/max box of every mesh, of the whole model (through
   rdModel3_CalcModelBoundingBox), and the model's center and radius. Source file Rdmodel3.c
   (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */

void __cdecl rdModel3_CalcBoundingBoxes(uint model)

{
  float fVar1;
  float fVar2;
  float fVar3;
  uint model_00;
  int iVar4;
  float *pfVar5;
  int iVar6;
  int iVar7;
  uint *puVar8;
  uint local_4;
  
  model_00 = model;
  *(undefined4 *)(model + 0x60) = 0x7f7fc99e;
  *(undefined4 *)(model + 100) = 0x7f7fc99e;
  *(undefined4 *)(model + 0x68) = 0x7f7fc99e;
  *(undefined4 *)(model + 0x6c) = 0xff7fc99e;
  *(undefined4 *)(model + 0x70) = 0xff7fc99e;
  *(undefined4 *)(model + 0x74) = 0xff7fc99e;
  local_4 = 0;
  if (*(int *)(model + 0x44) != 0) {
    puVar8 = (uint *)(model + 0x24);
    do {
      iVar6 = 0;
      model = 0;
      if (*puVar8 != 0) {
        do {
          iVar4 = iVar6 + puVar8[1];
          iVar7 = *(int *)(iVar4 + 0x48);
          *(undefined4 *)(iVar4 + 100) = 0x7f7fc99e;
          *(undefined4 *)(iVar4 + 0x68) = 0x7f7fc99e;
          *(undefined4 *)(iVar4 + 0x6c) = 0x7f7fc99e;
          *(undefined4 *)(iVar4 + 0x70) = 0xff7fc99e;
          *(undefined4 *)(iVar4 + 0x74) = 0xff7fc99e;
          *(undefined4 *)(iVar4 + 0x78) = 0xff7fc99e;
          if (iVar7 != 0) {
            pfVar5 = *(float **)(iVar4 + 0x30);
            do {
              if (*pfVar5 < *(float *)(iVar4 + 100)) {
                *(float *)(iVar4 + 100) = *pfVar5;
              }
              if (pfVar5[1] < *(float *)(iVar4 + 0x68)) {
                *(float *)(iVar4 + 0x68) = pfVar5[1];
              }
              if (pfVar5[2] < *(float *)(iVar4 + 0x6c)) {
                *(float *)(iVar4 + 0x6c) = pfVar5[2];
              }
              if (*(float *)(iVar4 + 0x70) < *pfVar5) {
                *(float *)(iVar4 + 0x70) = *pfVar5;
              }
              if (*(float *)(iVar4 + 0x74) < pfVar5[1]) {
                *(float *)(iVar4 + 0x74) = pfVar5[1];
              }
              if (*(float *)(iVar4 + 0x78) < pfVar5[2]) {
                *(float *)(iVar4 + 0x78) = pfVar5[2];
              }
              pfVar5 = pfVar5 + 3;
              iVar7 = iVar7 + -1;
            } while (iVar7 != 0);
          }
          model = model + 1;
          iVar6 = iVar6 + 0x7c;
        } while (model < *puVar8);
      }
      local_4 = local_4 + 1;
      puVar8 = puVar8 + 2;
    } while (local_4 < *(uint *)(model_00 + 0x44));
  }
  *(undefined4 *)(model_00 + 0x60) = 0x7f7fc99e;
  *(undefined4 *)(model_00 + 100) = 0x7f7fc99e;
  *(undefined4 *)(model_00 + 0x68) = 0x7f7fc99e;
  *(undefined4 *)(model_00 + 0x6c) = 0xff7fc99e;
  *(undefined4 *)(model_00 + 0x70) = 0xff7fc99e;
  *(undefined4 *)(model_00 + 0x74) = 0xff7fc99e;
  rdModel3_CalcModelBoundingBox(model_00,*(int *)(model_00 + 0x58),g_flRdroid_identMatrix34);
  fVar3 = *(float *)(model_00 + 0x60) - *(float *)(model_00 + 0x6c);
  fVar1 = *(float *)(model_00 + 100) - *(float *)(model_00 + 0x70);
  fVar2 = *(float *)(model_00 + 0x68) - *(float *)(model_00 + 0x74);
  *(float *)(model_00 + 0x78) =
       (*(float *)(model_00 + 0x6c) - *(float *)(model_00 + 0x60)) * 0.5f +
       *(float *)(model_00 + 0x60);
  *(float *)(model_00 + 0x7c) =
       (*(float *)(model_00 + 0x70) - *(float *)(model_00 + 100)) * 0.5f + *(float *)(model_00 + 100)
  ;
  *(float *)(model_00 + 0x80) =
       (*(float *)(model_00 + 0x74) - *(float *)(model_00 + 0x68)) * 0.5f +
       *(float *)(model_00 + 0x68);
  *(float *)(model_00 + 0x5c) = SQRT(fVar2 * fVar2 + fVar1 * fVar1 + fVar3 * fVar3) * 0.5f;
  return;
}

/* ---- 0x0040c710  rdModel3_CalcModelBoundingBox ---- */
/* Recursively composes the node matrices (angles, offset, pivot) and accumulates the transformed
   mesh boxes into the model bounds. Source file Rdmodel3.c
   (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). Original name rdModel3_CalcModelBoundingBox (the
   remaster's GrimFandango (Linux): the only unmatched callee of rdModel3_CalcBoundingBoxes; 1
   matched neighbours agree, 0 disagree); was rdModel3_AccumulateNodeBounds. */

void __cdecl rdModel3_CalcModelBoundingBox(int model,int node,float *matrix)

{
  unsigned char _frame[0xc0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  float *a;
  uint uVar2;
  int iVar3;
  #define local_a8 (*(float (*)[3])(_frame + (0xc0 - 0xa8)))
  #define local_9c (*(float (*)[3])(_frame + (0xc0 - 0x9c)))
  #define local_90 (*(float (*)[12])(_frame + (0xc0 - 0x90)))
  #define local_60 (*(float (*)[12])(_frame + (0xc0 - 0x60)))
  #define local_30 (*(float (*)[12])(_frame + (0xc0 - 0x30)))
  
  rdMatrix_Build34(local_30,(uint *)(node + 0x7c),(float *)(node + 0x70));
  rdMatrix_BuildTranslate34(local_90,(float *)(node + 100));
  rdMatrix_PostMultiply34(local_90,local_30);
  iVar3 = *(int *)(node + 0x54);
  if (iVar3 != 0) {
    local_9c[0] = -*(float *)(iVar3 + 100);
    local_9c[1] = -*(float *)(iVar3 + 0x68);
    local_9c[2] = -*(float *)(iVar3 + 0x6c);
    rdMatrix_PostTranslate34((int)local_90,local_9c);
  }
  rdMatrix_Multiply34(local_60,matrix,local_90);
  iVar3 = *(int *)(node + 0x4c);
  if (iVar3 != -1) {
    iVar1 = *(int *)(model + 0x28);
    uVar2 = 0;
    a = *(float **)(iVar1 + 0x30 + iVar3 * 0x7c);
    if (*(int *)(iVar1 + 0x48 + iVar3 * 0x7c) != 0) {
      do {
        rdMatrix_TransformPoint34(local_a8,a,local_60);
        if (*(float *)(model + 0x6c) < local_a8[0]) {
          *(float *)(model + 0x6c) = local_a8[0];
        }
        if (*(float *)(model + 0x70) < local_a8[1]) {
          *(float *)(model + 0x70) = local_a8[1];
        }
        if (*(float *)(model + 0x74) < local_a8[2]) {
          *(float *)(model + 0x74) = local_a8[2];
        }
        if (local_a8[0] < *(float *)(model + 0x60)) {
          *(float *)(model + 0x60) = local_a8[0];
        }
        if (local_a8[1] < *(float *)(model + 100)) {
          *(float *)(model + 100) = local_a8[1];
        }
        if (local_a8[2] < *(float *)(model + 0x68)) {
          *(float *)(model + 0x68) = local_a8[2];
        }
        a = a + 3;
        uVar2 = uVar2 + 1;
      } while (uVar2 < *(uint *)(iVar1 + iVar3 * 0x7c + 0x48));
    }
  }
  if (*(int *)(node + 0x58) != 0) {
    iVar3 = *(int *)(node + 0x5c);
    uVar2 = 0;
    if (*(int *)(node + 0x58) != 0) {
      do {
        rdModel3_CalcModelBoundingBox(model,iVar3,local_60);
        iVar3 = *(int *)(iVar3 + 0x60);
        uVar2 = uVar2 + 1;
      } while (uVar2 < *(uint *)(node + 0x58));
    }
  }
  return;
}
#undef local_30
#undef local_60
#undef local_90
#undef local_9c
#undef local_a8


/* ---- 0x0040c8c0  rdModel3_CalcRadii ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Computes the bounding radius of every mesh (largest vertex distance) and of the model. Source
   file Rdmodel3.c (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */

void __cdecl rdModel3_CalcRadii(int model)

{
  float fVar1;
  float fVar2;
  float *pfVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  uint local_4;
  
  uVar6 = 0;
  if (*(int *)(model + 0x24) != 0) {
    piVar4 = (int *)(*(int *)(model + 0x28) + 0x48);
    do {
      pfVar3 = (float *)piVar4[-6];
      fVar1 = 0.0f;
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
    } while (uVar6 < *(uint *)(model + 0x24));
  }
  _g_dwMaxGeoRadius = 0;
  rdModel3_BuildExpandedRadius(model,*(int *)(model + 0x58),g_flRdroid_identMatrix34);
  return;
}
#endif


/* ---- 0x0040c970  rdModel3_BuildExpandedRadius ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Recursive helper of rdModel3_CalcRadii: composes node matrices and updates the radius. Source
   file Rdmodel3.c (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). Original name
   rdModel3_BuildExpandedRadius (the remaster's GrimFandango (Linux): the only unmatched callee of
   rdModel3_CalcRadii; 1 matched neighbours agree, 0 disagree); was rdModel3_AccumulateNodeRadius.
    */

void __cdecl rdModel3_BuildExpandedRadius(int model,int node,float *matrix)

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
  
  rdMatrix_Build34(local_30,(uint *)(node + 0x7c),(float *)(node + 0x70));
  rdMatrix_BuildTranslate34(local_90,(float *)(node + 100));
  rdMatrix_PostMultiply34(local_90,local_30);
  iVar4 = *(int *)(node + 0x54);
  if (iVar4 != 0) {
    local_9c[0] = -*(float *)(iVar4 + 100);
    local_9c[1] = -*(float *)(iVar4 + 0x68);
    local_9c[2] = -*(float *)(iVar4 + 0x6c);
    rdMatrix_PostTranslate34((int)local_90,local_9c);
  }
  rdMatrix_Multiply34(local_60,matrix,local_90);
  iVar4 = *(int *)(node + 0x4c);
  if (iVar4 != -1) {
    iVar1 = *(int *)(model + 0x28);
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
  if (*(int *)(node + 0x58) != 0) {
    iVar4 = *(int *)(node + 0x5c);
    uVar3 = 0;
    if (*(int *)(node + 0x58) != 0) {
      do {
        rdModel3_BuildExpandedRadius(model,iVar4,local_60);
        iVar4 = *(int *)(iVar4 + 0x60);
        uVar3 = uVar3 + 1;
      } while (uVar3 < *(uint *)(node + 0x58));
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

void __cdecl rdModel3_CalcFaceNormals(uint model)

{
  uint uVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  uint uVar5;
  int *piVar6;
  uint uVar7;
  uint *puVar8;
  uint local_18;
  uint local_14;
  uint local_10;
  uint local_c;
  uint local_8;
  uint local_4;
  
  local_4 = 0;
  puVar3 = (uint *)(model + 0x24);
  uVar5 = model;
  if (*(int *)(model + 0x44) != 0) {
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
    } while (local_4 < *(uint *)(model + 0x44));
  }
  return;
}

/* ---- 0x0040cc30  rdModel3_CalcVertexNormals ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Averages the normals of the faces that share a vertex (or builds one from the neighbouring edges)
   and normalises. Source file Rdmodel3.c (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */

void __cdecl rdModel3_CalcVertexNormals(int model)

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
  float *v;
  uint *puVar16;
  #define local_44 (*(float (*)[3])(_frame + (0x60 - 0x44)))
  #define local_38 (*(uint *)(_frame + (0x60 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x60 - 0x34)))
  uint local_30;
  #define local_2c (*(uint *)(_frame + (0x60 - 0x2c)))
  uint local_28;
  #define local_20 (*(float (*)[2])(_frame + (0x60 - 0x20)))
  uint local_14;
  uint local_10;
  uint local_4;
  
  puVar15 = (uint *)(model + 0x24);
  local_2c = 0;
  if (*(int *)(model + 0x44) != 0) {
    do {
      local_34 = 0;
      if (*puVar15 != 0) {
        puVar13 = (undefined4 *)(puVar15[1] + 0x30);
        do {
          v = (float *)puVar13[5];
          local_38 = 0;
          if (puVar13[6] != 0) {
            do {
              local_20[0] = 0.0f;
              local_20[1] = 0.0f;
              fVar1 = 0.0f;
              fVar2 = 0.0f;
              fVar3 = 0.0f;
              fVar4 = 0.0f;
              local_44[0] = 0.0f;
              if (PUN(float,puVar13[8]) == 0.0f) {
                fVar1 = 0.0f;
              }
              else {
                puVar16 = (uint *)(puVar13[4] + 0x14);
                fVar12 = PUN(float,puVar13[8]);
                do {
                  local_44[0] = fVar12;
                  uVar11 = 0;
                  if (*puVar16 != 0) {
                    puVar14 = (uint *)puVar16[1];
                    do {
                      if (*puVar14 == local_38) {
                        fVar1 = PUN(float,puVar16[0xb]) + fVar1;
                        fVar2 = PUN(float,puVar16[0xc]) + fVar2;
                        fVar3 = PUN(float,puVar16[0xd]) + fVar3;
                        fVar4 = fVar4 - -1.0f;
                        break;
                      }
                      uVar11 = uVar11 + 1;
                      puVar14 = puVar14 + 1;
                    } while (uVar11 < *puVar16);
                  }
                  puVar16 = puVar16 + 0x13;
                  fVar12 = PUN(float,(PUN(int,(float)local_44[0]) + -1));
                  local_44[0] = fVar4;
                  local_20[0] = fVar2;
                  local_20[1] = fVar3;
                } while (fVar12 != 0.0f);
              }
              if (local_44[0] == 0.0f) {
                *v = 1.0f;
                v[1] = 0.0f;
                v[2] = 0.0f;
              }
              else if (local_44[0] == 1.0f) {
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
                v[1] = (pfVar9[1] - pfVar9[iVar8 * 3 + 1]) + (pfVar9[1] - pfVar9[iVar10 * 3 + 1]);
                v[2] = (fVar1 - fVar6) + (fVar2 - fVar12);
                *v = (fVar4 - fVar5) + (fVar3 - fVar7);
                rdVector_Normalize3Acc(v);
              }
              else {
                *v = fVar1 / local_44[0];
                v[1] = local_20[0] / local_44[0];
                v[2] = local_20[1] / local_44[0];
                rdVector_Normalize3Acc(v);
              }
              v = v + 3;
              local_38 = local_38 + 1;
            } while (local_38 < (uint)puVar13[6]);
          }
          puVar13 = puVar13 + 0x1f;
          local_34 = local_34 + 1;
        } while (local_34 < *puVar15);
      }
      puVar15 = puVar15 + 2;
      local_2c = local_2c + 1;
    } while (local_2c < *(uint *)(model + 0x44));
  }
  return;
}
#undef local_20
#undef local_2c
#undef local_34
#undef local_38
#undef local_44

#endif


/* ---- 0x0040ce90  rdModel3_CountNodeChildren ---- */
/* Counts the children of every hierarchy node (follows the sibling chain at +0x54). Source file
   Rdmodel3.c (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */

void __cdecl rdModel3_CountNodeChildren(int node)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  
  uVar5 = 0;
  if (*(int *)(node + 0x54) != 0) {
    iVar4 = 0;
    do {
      iVar2 = *(int *)(node + 0x58);
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
    } while (uVar5 < *(uint *)(node + 0x54));
  }
  return;
}
