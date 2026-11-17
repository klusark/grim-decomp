/* GRIMFANDANGO.EXE :: lighted.c
 * functions 0x004be3b0 .. 0x004bffb0 (19 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004be3b0  LightEd_SyncFromSet ---- */
/* In-game light editor (Win32 dialog): rebuilds the edit entries (5 dwords each at
   g_LightEdEntries) from the set's light array */

void __cdecl LightEd_SyncFromSet(void)

{
  undefined4 *puVar1;
  Set *pSVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  uint local_c;
  uint local_8;
  uint local_4;
  
  g_pLightEdSet->nLights = UINT_008d3644;
  local_4 = 0;
  if (UINT_008d3644 != 0) {
    local_c = 0;
    local_8 = (uint)&UINT_008d1738;
    iVar5 = 0x15c;
    pSVar2 = g_pLightEdSet;
    do {
      puVar1 = (undefined4 *)((int)&UINT_008d1c30 + local_c);
      pcVar6 = pSVar2->aLights[0].aName + local_c;
      for (iVar3 = 0x1a; iVar3 != 0; iVar3 = iVar3 + -1) {
        *(undefined4 *)pcVar6 = *puVar1;
        puVar1 = puVar1 + 1;
        pcVar6 = pcVar6 + 4;
      }
      uVar4 = 0;
      if (g_pLightEdSet->nSetups != 0) {
        iVar3 = 0;
        do {
          puVar1 = (undefined4 *)
                   (*(int *)((int)g_pLightEdSet->pSetups->aPos + iVar3 + 0x28) + iVar5);
          uVar4 = uVar4 + 1;
          iVar3 = iVar3 + 300;
          *puVar1 = *(undefined4 *)((int)&UINT_008d1c50 + local_c);
          puVar1[1] = *(undefined4 *)((int)&UINT_008d1c54 + local_c);
          puVar1[2] = *(undefined4 *)((int)&UINT_008d1c58 + local_c);
        } while (uVar4 < (uint)g_pLightEdSet->nSetups);
      }
      pSVar2 = g_pLightEdSet;
      *(undefined4 *)(local_8 - 4) = 1;
      if (*(int *)(*(int *)(local_8 - 8) + 0x30) == 2) {
        *(undefined4 *)local_8 = 0;
        *(undefined4 *)(local_8 + 4) = 0;
        *(undefined4 *)(local_8 + 8) = 0;
      }
      else {
        LightEd_GetLightAngles(*(int *)(local_8 - 8) + 0x2c,(float *)local_8);
        pSVar2 = g_pLightEdSet;
      }
      local_4 = local_4 + 1;
      iVar5 = iVar5 + 0xc;
      local_c = local_c + 0x68;
      local_8 = local_8 + 0x14;
    } while (local_4 < UINT_008d3644);
  }
  return;
}

/* ---- 0x004be4c0  LightEd_ResetLight ---- */
void __cdecl LightEd_ResetLight(int index,int mode)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  uint *puVar6;
  uint *puVar7;
  
  if (mode == 0) {
    puVar6 = &UINT_008d16c8;
    puVar7 = (uint *)(&UINT_008d1730)[index * 5];
    for (iVar3 = 0x1a; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar7 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar7 = puVar7 + 1;
    }
    uVar4 = 0;
    if (g_pLightEdSet->nSetups != 0) {
      iVar3 = 0;
      do {
        uVar1 = (&UINT_008d1730)[index * 5];
        iVar2 = iVar3 + 0x28;
        iVar3 = iVar3 + 300;
        puVar5 = (undefined4 *)
                 (*(int *)((int)g_pLightEdSet->pSetups->aPos + iVar2) + (index + 0x1d) * 0xc);
        uVar4 = uVar4 + 1;
        *puVar5 = *(undefined4 *)(uVar1 + 0x20);
        puVar5[1] = *(undefined4 *)(uVar1 + 0x24);
        puVar5[2] = *(undefined4 *)(uVar1 + 0x28);
      } while (uVar4 < (uint)g_pLightEdSet->nSetups);
      return;
    }
  }
  else {
    puVar6 = (uint *)(&UINT_008d1730)[index * 5];
    puVar7 = &UINT_008d16c8;
    for (iVar3 = 0x1a; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar7 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar7 = puVar7 + 1;
    }
  }
  return;
}

/* ---- 0x004be560  LightEd_DeleteLight ---- */
/* Shifts the following 0x68-byte light records and edit entries down */

void __cdecl LightEd_DeleteLight(uint index)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  uint uVar6;
  uint *puVar7;
  int iVar8;
  char *pcVar9;
  char *pcVar10;
  uint local_8;
  uint local_4;
  
  if (index < (uint)g_pLightEdSet->nLights) {
    local_4 = index + 1;
    if (local_4 < (uint)g_pLightEdSet->nLights) {
      iVar3 = local_4 * 0x68;
      puVar7 = &UINT_008d1734 + local_4 * 5;
      iVar8 = (index + 0x1d) * 0xc;
      do {
        pcVar9 = g_pLightEdSet->aLights[0].aName + iVar3;
        pcVar10 = g_pLightEdSet->aColormapName + iVar3 + -0x38;
        for (iVar5 = 0x1a; iVar5 != 0; iVar5 = iVar5 + -1) {
          *(undefined4 *)pcVar10 = *(undefined4 *)pcVar9;
          pcVar9 = pcVar9 + 4;
          pcVar10 = pcVar10 + 4;
        }
        uVar6 = 0;
        if (g_pLightEdSet->nSetups != 0) {
          iVar5 = 0;
          do {
            iVar2 = *(int *)((int)g_pLightEdSet->pSetups->aPos + iVar5 + 0x28);
            puVar1 = (undefined4 *)(iVar2 + 0xc + iVar8);
            puVar4 = (undefined4 *)(iVar2 + iVar8);
            uVar6 = uVar6 + 1;
            *puVar4 = *puVar1;
            puVar4[1] = puVar1[1];
            puVar4[2] = puVar1[2];
            iVar5 = iVar5 + 300;
          } while (uVar6 < (uint)g_pLightEdSet->nSetups);
        }
        puVar7[-5] = *puVar7;
        LightEd_GetLightAngles(puVar7[-6] + 0x2c,(float *)(puVar7 + -4));
        local_4 = local_4 + 1;
        iVar8 = iVar8 + 0xc;
        iVar3 = iVar3 + 0x68;
        puVar7 = puVar7 + 5;
      } while (local_4 < (uint)g_pLightEdSet->nLights);
    }
    uVar6 = 0;
    if (g_pLightEdSet->nSetups != 0) {
      iVar3 = 0;
      do {
        iVar8 = *(int *)((int)g_pLightEdSet->pSetups->aPos + iVar3 + 0x28);
        iVar3 = iVar3 + 300;
        puVar1 = (undefined4 *)(iVar8 + (g_pLightEdSet->nLights + 0x1c) * 0xc);
        *puVar1 = 0;
        puVar1[1] = 0;
        puVar1[2] = 0;
        uVar6 = uVar6 + 1;
        *(int *)(iVar8 + 0x58) = *(int *)(iVar8 + 0x58) + -1;
      } while (uVar6 < (uint)g_pLightEdSet->nSetups);
    }
    pcVar9 = g_pLightEdSet->aColormapName + g_pLightEdSet->nLights * 0x68 + -0x38;
    for (iVar3 = 0x1a; iVar3 != 0; iVar3 = iVar3 + -1) {
      pcVar9[0] = '\0';
      pcVar9[1] = '\0';
      pcVar9[2] = '\0';
      pcVar9[3] = '\0';
      pcVar9 = pcVar9 + 4;
    }
    g_pLightEdSet->nLights = g_pLightEdSet->nLights + -1;
    uVar6 = index;
    if (g_pLightEdSet->nLights <= (int)index) {
      uVar6 = g_pLightEdSet->nLights - 1;
    }
    SendDlgItemMessageA((int)g_hLightEdDialog,1000,0x182,index,0);
    SendDlgItemMessageA((int)g_hLightEdDialog,1000,0x186,uVar6,0);
    LightEd_UpdateDialog((int)g_hLightEdDialog);
  }
  return;
}

/* ---- 0x004be730  LightEd_MakeUniqueName ---- */
/* newlight%d, skipping names already used in the set */

void __cdecl LightEd_MakeUniqueName(int lightEdSet,char *buf)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  byte *pbVar4;
  
  uVar2 = *(uint *)(lightEdSet + 0xb8);
  do {
    if (0x3f < uVar2) {
      return;
    }
    sprintf(buf,s_newlight_d_004f0d6c,uVar2);
    uVar3 = 0;
    if (*(int *)(lightEdSet + 0xb8) != 0) {
      pbVar4 = (byte *)(lightEdSet + 0xbc);
      do {
        if ((uVar3 != uVar2) && (iVar1 = _stricmp((byte *)buf,pbVar4), iVar1 == 0)) break;
        uVar3 = uVar3 + 1;
        pbVar4 = pbVar4 + 0x68;
      } while (uVar3 < *(uint *)(lightEdSet + 0xb8));
    }
    if (*(uint *)(lightEdSet + 0xb8) <= uVar3) {
      return;
    }
    uVar2 = uVar2 + 1;
  } while( true );
}

/* ---- 0x004be7b0  LightEd_AddLight ---- */
/* Appends a light to the current set (max 64) and selects it in the dialog */

void __cdecl LightEd_AddLight(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined1 *puVar1;
  float *pfVar2;
  rdLight *light;
  char cVar3;
  int a4;
  Set *pSVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  SetLight *pSVar9;
  uint local_24;
  #define local_20 (*(char (*)[32])(_frame + (0x30 - 0x20)))
  
  if (0x3f < (uint)g_pLightEdSet->nLights) {
    MessageBoxA((int)g_hLightEdDialog,((unsigned)(uintptr_t)&s_Maximum_number_of_lights_already_004f0d78),((unsigned)(uintptr_t)&DAT_004f0db8),0x30);
    return;
  }
  a4 = g_pLightEdSet->nLights;
  LightEd_MakeUniqueName((int)g_pLightEdSet,local_20);
  uVar5 = 0xffffffff;
  pcVar7 = local_20;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar3 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar3 != '\0');
  uVar5 = ~uVar5;
  pcVar7 = pcVar8 + -uVar5;
  pSVar9 = g_pLightEdSet->aLights + a4;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pSVar9->aName = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pSVar9 = (SetLight *)(pSVar9->aName + 4);
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    pSVar9->aName[0] = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pSVar9 = (SetLight *)(pSVar9->aName + 1);
  }
  uVar5 = 0;
  puVar1 = &g_pLightEdSet->pSetups[g_pLightEdSet->nCurSetup].field_0x2c;
  pfVar2 = g_pLightEdSet->aLights[a4].aPos;
  *pfVar2 = *(float *)puVar1;
  pfVar2[1] = *(float *)(puVar1 + 4);
  pfVar2[2] = *(float *)(puVar1 + 8);
  g_pLightEdSet->nLights = g_pLightEdSet->nLights + 1;
  pSVar4 = g_pLightEdSet;
  g_pLightEdSet->aLights[a4].light.nType = 2;
  pSVar4->aLights[a4].light.nActive = 1;
  light = &pSVar4->aLights[a4].light;
  light->aDirection[0] = 0.0f;
  light->aDirection[1] = 0.0f;
  light->aDirection[2] = 0.0f;
  light->flIntensity = 1.0f;
  light->dwColor = 0xffffff;
  light->flInnerAngle = 0.0f;
  light->flCosInner = 0.0f;
  light->flOuterAngle = 0.0f;
  light->flCosOuter = 0.0f;
  pSVar4 = g_pLightEdSet;
  (&UINT_008d1730)[a4 * 5] = (uint)(g_pLightEdSet->aLights + a4);
  (&UINT_008d1734)[a4 * 5] = 1;
  (&UINT_008d1738)[a4 * 5] = 0;
  (&UINT_008d173c)[a4 * 5] = 0;
  (&UINT_008d1740)[a4 * 5] = 0;
  if (pSVar4->nSetups != 0) {
    local_24 = 0;
    do {
      rdCamera_AddLight(*(rdCamera **)((int)pSVar4->pSetups->aPos + local_24 + 0x28),light,
                        pSVar4->aLights[a4].aPos);
      uVar5 = uVar5 + 1;
      local_24 = local_24 + 300;
      pSVar4 = g_pLightEdSet;
    } while (uVar5 < (uint)g_pLightEdSet->nSetups);
  }
  SendDlgItemMessageA((int)g_hLightEdDialog,1000,0x180,0,(int)(pSVar4->aLights + a4));
  SendDlgItemMessageA((int)g_hLightEdDialog,1000,0x186,a4,0);
  LightEd_UpdateDialog((int)g_hLightEdDialog);
  return;
}
#undef local_20


/* ---- 0x004be990  LightEd_SaveSetFile ---- */
/* Rewrites the set file with the edited lights section via a temp file */

void __cdecl LightEd_SaveSetFile(void)

{
  unsigned char _frame[0x220] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  Set *pSVar7;
  Set *pSVar8;
  char *pcVar9;
  void *file;
  OpenFileName ofn;
  char aLine [260];
  #define acStack_208 (*(char (*)[260])(_frame + (0x220 - 0x208)))
  char aPath [260];
  
  ofn.dwStructSize = 0x4c;
  ofn.pOwner = g_hLightEdDialog;
  ofn.pInstance = (void *)Win_GetInstance();
  ofn.pFile = aPath;
  uVar4 = 0xffffffff;
  ofn.pFilter = s_Set_Files____set__004f0e0c;
  ofn.pCustomFilter = (char *)0x0;
  ofn.dwMaxFile = 0x104;
  ofn.pFileTitle = (char *)0x0;
  ofn.pInitialDir = (char *)0x0;
  ofn.pTitle = (char *)0x0;
  ofn.dwFlags = 0x8080e;
  ofn.pDefExt = s_set_004ec490;
  ofn.dwCustData = 0;
  ofn.pHook = (void *)0x0;
  ofn.pTemplateName = (char *)0x0;
  pSVar7 = g_pLightEdSet;
  do {
    pSVar8 = pSVar7;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pSVar8 = (Set *)(pSVar7->aName + 1);
    pcVar6 = pSVar7->aName;
    pSVar7 = pSVar8;
  } while (*pcVar6 != '\0');
  uVar4 = ~uVar4;
  pcVar6 = (char *)((int)pSVar8 - uVar4);
  pcVar9 = aPath;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar9 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar9 = pcVar9 + 1;
  }
  iVar1 = GetSaveFileNameA((int)&ofn);
  if (iVar1 == 0) {
    return;
  }
  iVar1 = (*g_pStd_HS->pFopen)(g_pLightEdSet,s_rt_004ec5bc);
  file = (void *)0x0;
  acStack_208[0] = '\0';
  if (iVar1 == 0) {
    wsprintfA(aLine,s_Could_not_open_file___s___004f0dc8,g_pLightEdSet);
    MessageBoxA(0,(int)aLine,(int)PTR_s_Error_004f0d14,0x30);
    return;
  }
  GetTempPathA(0x104,(int)aLine);
  iVar2 = GetTempFileNameA((int)aLine,((unsigned)(uintptr_t)&s_set_004ec490),0,(int)acStack_208);
  if (iVar2 == 0) {
LAB_004becb0:
    if (file != (void *)0x0) {
      (*g_pStd_HS->pFclose)(file);
      goto LAB_004becd7;
    }
  }
  else {
    file = (void *)(*g_pStd_HS->pFopen)(acStack_208,s_wt_004dee34);
    if (file != (void *)0x0) {
      iVar2 = (*g_pStd_HS->pFeof)(iVar1);
      while (iVar2 == 0) {
        (*g_pStd_HS->pFgets)(iVar1,aLine,0x104);
        puVar3 = String_ContainsSubstring((uint *)aLine,s_section__004f0e00);
        if ((puVar3 != (uint *)0x0) &&
           (puVar3 = String_ContainsSubstring((uint *)aLine,s_lights_004ec724),
           puVar3 != (uint *)0x0)) break;
        (*g_pStd_HS->pFprintf)(file,aLine);
        iVar2 = (*g_pStd_HS->pFeof)(iVar1);
      }
      iVar2 = (*g_pStd_HS->pFeof)(iVar1);
      if (iVar2 == 0) {
        LightEd_WriteLightsSection(g_pLightEdSet,file);
        iVar2 = (*g_pStd_HS->pFeof)(iVar1);
        while (iVar2 == 0) {
          (*g_pStd_HS->pFgets)(iVar1,aLine,0x104);
          puVar3 = String_ContainsSubstring((uint *)aLine,s_section__004f0e00);
          if (puVar3 != (uint *)0x0) {
            (*g_pStd_HS->pFprintf)(file,aLine);
            break;
          }
          iVar2 = (*g_pStd_HS->pFeof)(iVar1);
        }
        iVar2 = (*g_pStd_HS->pFeof)(iVar1);
        if (iVar2 == 0) {
          iVar2 = (*g_pStd_HS->pFeof)(iVar1);
          while (iVar2 == 0) {
            (*g_pStd_HS->pFgets)(iVar1,aLine,0x104);
            (*g_pStd_HS->pFprintf)(file,aLine);
            iVar2 = (*g_pStd_HS->pFeof)(iVar1);
          }
          (*g_pStd_HS->pFclose)(iVar1);
          (*g_pStd_HS->pFclose)(file);
          iVar1 = (*g_pStd_HS->pFopen)(acStack_208,s_rt_004ec5bc);
          file = (void *)(*g_pStd_HS->pFopen)(aPath,s_wt_004dee34);
          if (iVar1 != 0) {
            if (file == (void *)0x0) goto LAB_004becb4;
            iVar2 = (*g_pStd_HS->pFeof)(iVar1);
            while (iVar2 == 0) {
              (*g_pStd_HS->pFgets)(iVar1,aLine,0x104);
              (*g_pStd_HS->pFprintf)(file,aLine);
              iVar2 = (*g_pStd_HS->pFeof)(iVar1);
            }
          }
        }
      }
      goto LAB_004becb0;
    }
  }
LAB_004becb4:
  MessageBoxA(0,((unsigned)(uintptr_t)&DAT_004f0de4),(int)PTR_s_Error_004f0d14,0x30);
LAB_004becd7:
  (*g_pStd_HS->pFclose)(iVar1);
  if (acStack_208[0] == '\0') {
    return;
  }
  DeleteFileA((int)acStack_208);
  return;
}
#undef acStack_208


/* ---- 0x004bed40  LightEd_WriteLightsSection ---- */
/* Emits 'section: lights' with name/type/position/direction/intensity/angles per light */

void __cdecl LightEd_WriteLightsSection(Set *set,void *file)

{
  uint uVar1;
  SetLight *pSVar2;
  
  (*g_pStd_HS->pFprintf)(file,s_section__lights_004ec6fc);
  (*g_pStd_HS->pFprintf)();
  pSVar2 = set->aLights;
  uVar1 = 0;
  if (set->nLights != 0) {
    do {
      (*g_pStd_HS->pFprintf)();
      (*g_pStd_HS->pFprintf)();
      (*g_pStd_HS->pFprintf)
                (file,s_position__f__f__f_004ec6a4,(double)pSVar2->aPos[0],(double)pSVar2->aPos[1],
                 (double)pSVar2->aPos[2]);
      (*g_pStd_HS->pFprintf)
                (file,s_direction__f__f__f_004ec68c,(double)(pSVar2->light).aDirection[0],
                 (double)(pSVar2->light).aDirection[1],(double)(pSVar2->light).aDirection[2]);
      (*g_pStd_HS->pFprintf)(file,s_intensity__f_004ec67c,(double)(pSVar2->light).flIntensity);
      (*g_pStd_HS->pFprintf)(file,s_umbraangle__f_004ec668,(double)(pSVar2->light).flInnerAngle);
      (*g_pStd_HS->pFprintf)(file,s_penumbraangle__f_004ec654,(double)(pSVar2->light).flOuterAngle);
      (*g_pStd_HS->pFprintf)();
      (*g_pStd_HS->pFprintf)(file,&UINT_004ddd74);
      pSVar2 = pSVar2 + 1;
      uVar1 = uVar1 + 1;
    } while (uVar1 < (uint)set->nLights);
  }
  return;
}

/* ---- 0x004bef10  LightEd_FillListBox ---- */
void __cdecl LightEd_FillListBox(int hDlg)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint *puVar2;
  uint uVar3;
  char *a5;
  code *pcVar4;
  #define local_20 (*(char (*)[32])(_frame + (0x30 - 0x20)))
  
  pcVar4 = SendDlgItemMessageA_exref;
  SendDlgItemMessageA(hDlg,1000,0x184,0,0);
  uVar3 = 0;
  if (g_pLightEdSet->nLights != 0) {
    puVar2 = &UINT_008d1730;
    do {
      a5 = (char *)*puVar2;
      if (*a5 == '\0') {
        a5 = local_20;
        wsprintfA(local_20,s__Light__d__004f0e68,uVar3);
      }
      SendDlgItemMessageA(hDlg,1000,0x180,0,(int)a5);
      uVar3 = uVar3 + 1;
      puVar2 = puVar2 + 5;
      pcVar4 = SendDlgItemMessageA_exref;
    } while (uVar3 < (uint)g_pLightEdSet->nLights);
  }
  iVar1 = (*pcVar4)(hDlg,1000,0x18b,0,0);
  if (0 < iVar1) {
    (*pcVar4)(hDlg,1000,0x186,0,0);
    LightEd_UpdateDialog(hDlg);
    LightEd_ResetLight(0,1);
  }
  return;
}
#undef local_20


/* ---- 0x004befe0  LightEd_UpdateDialog ---- */
/* Refreshes every control from the selected light */

void __cdecl LightEd_UpdateDialog(int hDlg)

{
  uint uVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  
  bVar2 = false;
  if (g_pLightEdSet != (Set *)0x0) {
    g_nLightEdSelected = SendDlgItemMessageA(hDlg,1000,0x188,0,0);
    if (g_nLightEdSelected == -1) {
      LightEd_EnableControls(0);
      bVar2 = false;
    }
    else {
      uVar1 = (&UINT_008d1730)[g_nLightEdSelected * 5];
      LightEd_EnableControls(1);
      CheckDlgButton(hDlg,0x3fa,(uint)(*(int *)(uVar1 + 0x34) != 0));
      CheckDlgButton(hDlg,0x3fe,(uint)((&UINT_008d1734)[g_nLightEdSelected * 5] != 0));
      LightEd_SetDlgFloat(hDlg,0x3ec,*(float *)(uVar1 + 0x44),1);
      LightEd_SetDlgFloat(hDlg,0x3ef,*(float *)(uVar1 + 0x20),1);
      LightEd_SetDlgFloat(hDlg,0x3f0,*(float *)(uVar1 + 0x24),1);
      LightEd_SetDlgFloat(hDlg,0x3f1,*(float *)(uVar1 + 0x28),1);
      if ((*(int *)(uVar1 + 0x30) == 1) || (*(int *)(uVar1 + 0x30) == 0)) {
        iVar3 = 1;
      }
      else {
        iVar3 = 0;
      }
      CheckDlgButton(hDlg,0x3e9,iVar3);
      CheckDlgButton(hDlg,0x3ea,(uint)(*(int *)(uVar1 + 0x30) == 2));
      CheckDlgButton(hDlg,0x3eb,(uint)(*(int *)(uVar1 + 0x30) == 3));
      switch(*(undefined4 *)(uVar1 + 0x30)) {
      case 0:
      case 1:
        iVar4 = 0;
        iVar3 = GetDlgItem(hDlg,0x3ed);
        EnableWindow(iVar3,iVar4);
        iVar4 = 0;
        iVar3 = GetDlgItem(hDlg,0x3ee);
        EnableWindow(iVar3,iVar4);
        LightEd_SetDlgFloat(hDlg,0x3f2,(float)(&UINT_008d1738)[g_nLightEdSelected * 5],0);
        LightEd_SetDlgFloat(hDlg,0x3f4,(float)(&UINT_008d173c)[g_nLightEdSelected * 5],0);
        LightEd_SetDlgFloat(hDlg,0x3f5,(float)(&UINT_008d1740)[g_nLightEdSelected * 5],0);
        LightEd_MoveMarkerActor();
        bVar2 = true;
        break;
      case 2:
        iVar4 = 0;
        iVar3 = GetDlgItem(hDlg,0x3f2);
        EnableWindow(iVar3,iVar4);
        iVar4 = 0;
        iVar3 = GetDlgItem(hDlg,0x3f4);
        EnableWindow(iVar3,iVar4);
        iVar4 = 0;
        iVar3 = GetDlgItem(hDlg,0x3f5);
        EnableWindow(iVar3,iVar4);
        iVar4 = 0;
        iVar3 = GetDlgItem(hDlg,0x3ed);
        EnableWindow(iVar3,iVar4);
        iVar4 = 0;
        iVar3 = GetDlgItem(hDlg,0x3ee);
        EnableWindow(iVar3,iVar4);
      default:
        LightEd_MoveMarkerActor();
        bVar2 = true;
        break;
      case 3:
        LightEd_SetDlgFloat(hDlg,0x3f2,(float)(&UINT_008d1738)[g_nLightEdSelected * 5],0);
        LightEd_SetDlgFloat(hDlg,0x3f4,(float)(&UINT_008d173c)[g_nLightEdSelected * 5],0);
        LightEd_SetDlgFloat(hDlg,0x3f5,(float)(&UINT_008d1740)[g_nLightEdSelected * 5],0);
        LightEd_SetDlgFloat(hDlg,0x3ed,*(float *)((&UINT_008d1730)[g_nLightEdSelected * 5] + 0x4c),1
                           );
        LightEd_SetDlgFloat(hDlg,0x3ee,*(float *)((&UINT_008d1730)[g_nLightEdSelected * 5] + 0x54),1
                           );
        LightEd_MoveMarkerActor();
        bVar2 = true;
      }
    }
  }
  if ((g_pLightEdMarkerActor != (Actor *)0x0) && (!bVar2)) {
    g_pLightEdMarkerActor->dwFlags = g_pLightEdMarkerActor->dwFlags | 2;
  }
  return;
}

/* ---- 0x004bf2f0  LightEd_EnableControls ---- */
void __cdecl LightEd_EnableControls(int hDlg)

{
  uint a2;
  int a1;
  uint *puVar1;
  int a2_00;
  uint aControlIds [24];
  
  a2 = 0x3e9;
  aControlIds[0] = 0x3e9;
  aControlIds[1] = 0x3ea;
  aControlIds[2] = 0x3eb;
  aControlIds[3] = 0x3ec;
  aControlIds[4] = 0x3ed;
  aControlIds[5] = 0x3ee;
  aControlIds[6] = 0x3ef;
  aControlIds[7] = 0x3f0;
  aControlIds[8] = 0x3f1;
  aControlIds[9] = 0x3f2;
  aControlIds[10] = 0x3f4;
  aControlIds[0xb] = 0x3f5;
  aControlIds[0xc] = 0x3f7;
  aControlIds[0xd] = 0x3f9;
  aControlIds[0xe] = 0x3fa;
  aControlIds[0xf] = 0x3fb;
  aControlIds[0x10] = 0x3fc;
  aControlIds[0x11] = 0x3fd;
  aControlIds[0x12] = 0x3fe;
  aControlIds[0x13] = 0x3ff;
  aControlIds[0x14] = 0x400;
  aControlIds[0x15] = 0x401;
  aControlIds[0x16] = 0x402;
  aControlIds[0x17] = 0;
  puVar1 = aControlIds;
  do {
    a2_00 = hDlg;
    a1 = GetDlgItem((int)g_hLightEdDialog,a2);
    EnableWindow(a1,a2_00);
    a2 = puVar1[1];
    puVar1 = puVar1 + 1;
  } while (a2 != 0);
  return;
}

/* ---- 0x004bf3f0  LightEd_SetDlgFloat ---- */
void __cdecl LightEd_SetDlgFloat(int hDlg,int id,float value,int force)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_4c (*(char (*)[76])(_frame + (0x60 - 0x4c)))
  
  iVar1 = GetDlgItem(hDlg,id);
  iVar1 = IsWindowEnabled(iVar1);
  if (iVar1 != 0) {
    sprintf(local_4c,s__f_004ddc14,(double)value);
    if (force == 0) {
      g_nLightEdBusy = 1;
    }
    SetDlgItemTextA(hDlg,id,(int)local_4c);
    g_nLightEdBusy = 0;
  }
  return;
}
#undef local_4c


/* ---- 0x004bf460  LightEd_RefreshControl ---- */
/* The control id arrives in the float slot (0x3ea..) because of the varargs caller */

void __cdecl LightEd_RefreshControl(int hDlg,float id,uint kind,int pos)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int a2;
  float fVar1;
  uint local_50;
  #define local_4c (*(byte (*)[76])(_frame + (0x60 - 0x4c)))
  
  if (g_nLightEdSelected == -1) {
    return;
  }
  if (g_pLightEdSet == (Set *)0x0) {
    return;
  }
  if (id == 1.42792e-42f) {
    a2 = 0x3ec;
    local_50 = 1000;
  }
  else if (id == 1.43353e-42f) {
    a2 = 0x3ed;
    local_50 = 100;
  }
  else {
    if (id != 1.43493e-42f) {
      return;
    }
    a2 = 0x3ee;
    local_50 = 100;
  }
  GetDlgItemTextA(hDlg,a2,(int)local_4c,0x4b);
  fVar1 = atof(local_4c);
  switch(kind) {
  case 0:
    fVar1 = fVar1 * (float)local_50 - -1.0f;
    break;
  case 1:
    fVar1 = fVar1 * (float)local_50 - 1.0f;
    break;
  default:
    goto switchD_004bf4ef_caseD_2;
  case 4:
  case 5:
    id = (float)pos / (float)local_50;
    goto LAB_004bf52e;
  }
  id = fVar1 / (float)local_50;
LAB_004bf52e:
  LightEd_SetDlgFloat(hDlg,a2,id,0);
switchD_004bf4ef_caseD_2:
  return;
}
#undef local_4c


/* ---- 0x004bf560  LightEd_ReadControl ---- */
/* Parses the edited text field back into the light (position, direction, intensity, angles,
   falloff) */

void __cdecl LightEd_ReadControl(int hdlg,int id)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint a5;
  longlong lVar1;
  float outer;
  int a2;
  #define local_4c (*(byte (*)[76])(_frame + (0x60 - 0x4c)))
  
  GetDlgItemTextA(hdlg,id,(int)local_4c,0x4b);
  outer = atof(local_4c);
  if (g_pLightEdSet == (Set *)0x0) {
    return;
  }
  if (g_nLightEdSelected == -1) {
    return;
  }
  switch(id) {
  case 0x3ec:
    *(float *)((&UINT_008d1730)[g_nLightEdSelected * 5] + 0x44) = outer;
    if (g_nLightEdBusy != 0) {
      return;
    }
    lVar1 = FTOL((float10)outer * (float10)1000.0f);
    a5 = (uint)lVar1 & 0xffff;
    a2 = 0x3fb;
    goto LAB_004bf718;
  case 0x3ed:
    rdLight_SetAngles((rdLight *)((&UINT_008d1730)[g_nLightEdSelected * 5] + 0x2c),outer,
                      *(float *)((&UINT_008d1730)[g_nLightEdSelected * 5] + 0x54));
    if (g_nLightEdBusy != 0) {
      return;
    }
    lVar1 = FTOL((float10)outer * (float10)100.0f);
    a5 = (uint)lVar1 & 0xffff;
    a2 = 0x3ff;
    goto LAB_004bf718;
  case 0x3ee:
    rdLight_SetAngles((rdLight *)((&UINT_008d1730)[g_nLightEdSelected * 5] + 0x2c),
                      *(float *)((&UINT_008d1730)[g_nLightEdSelected * 5] + 0x4c),outer);
    if (g_nLightEdBusy != 0) {
      return;
    }
    lVar1 = FTOL((float10)outer * (float10)100.0f);
    a5 = (uint)lVar1 & 0xffff;
    a2 = 0x400;
LAB_004bf718:
    SendDlgItemMessageA(hdlg,a2,0x467,0,a5);
    break;
  case 0x3ef:
    LightEd_SetLightPosComponent(g_nLightEdSelected,0,PUN(uint,(float)outer));
    break;
  case 0x3f0:
    LightEd_SetLightPosComponent(g_nLightEdSelected,1,PUN(uint,(float)outer));
    break;
  case 0x3f1:
    LightEd_SetLightPosComponent(g_nLightEdSelected,2,PUN(uint,(float)outer));
    break;
  case 0x3f2:
    LightEd_SetLightAngle(g_nLightEdSelected,0,PUN(uint,(float)outer));
    break;
  case 0x3f4:
    LightEd_SetLightAngle(g_nLightEdSelected,1,PUN(uint,(float)outer));
    break;
  case 0x3f5:
    LightEd_SetLightAngle(g_nLightEdSelected,2,PUN(uint,(float)outer));
  }
  if (g_nLightEdBusy == 0) {
    LightEd_MoveMarkerActor();
  }
  return;
}
#undef local_4c


/* ---- 0x004bf760  LightEd_SetLightPosComponent ---- */
void __cdecl LightEd_SetLightPosComponent(int lightEdSelected,short axis,uint value)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = 0;
  *(uint *)((&UINT_008d1730)[lightEdSelected * 5] + 0x20 + axis * 4) = value;
  if (g_pLightEdSet->nSetups != 0) {
    iVar2 = 0;
    do {
      uVar3 = uVar3 + 1;
      iVar1 = iVar2 + 0x28;
      iVar2 = iVar2 + 300;
      *(uint *)(*(int *)((int)g_pLightEdSet->pSetups->aPos + iVar1) +
               ((int)axis + (lightEdSelected + 0x1d) * 3) * 4) = value;
    } while (uVar3 < (uint)g_pLightEdSet->nSetups);
  }
  return;
}

/* ---- 0x004bf7d0  LightEd_SetLightAngle ---- */
/* Stores the angle and recomputes the direction vector */

void __cdecl LightEd_SetLightAngle(int lightEdSelected,short axis,uint value)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  #define local_c (*(float (*)[3])(_frame + (0x20 - 0xc)))
  
  local_c[0] = 0.0f;
  (&UINT_008d1738)[lightEdSelected * 5 + (int)axis] = value;
  local_c[1] = 1.0f;
  local_c[2] = 0.0f;
  rdVector_Rotate3Acc(local_c,(float *)(&UINT_008d1738 + lightEdSelected * 5));
  uVar1 = (&UINT_008d1730)[lightEdSelected * 5];
  *(float *)(uVar1 + 0x38) = local_c[0];
  *(float *)(uVar1 + 0x3c) = local_c[1];
  *(float *)(uVar1 + 0x40) = local_c[2];
  return;
}
#undef local_c


/* ---- 0x004bf850  LightEd_SetAllEnabled ---- */
void __cdecl LightEd_SetAllEnabled(int enabled)

{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  
  if (g_pLightEdSet != (Set *)0x0) {
    uVar2 = 0;
    if (g_pLightEdSet->nLights != 0) {
      puVar3 = &UINT_008d1730;
      do {
        uVar1 = *puVar3;
        uVar2 = uVar2 + 1;
        puVar3 = puVar3 + 5;
        *(int *)(uVar1 + 0x34) = enabled;
      } while (uVar2 < (uint)g_pLightEdSet->nLights);
    }
    if ((g_hLightEdDialog != (void *)0x0) && (g_nLightEdSelected != -1)) {
      CheckDlgButton((int)g_hLightEdDialog,0x3fa,(uint)(enabled != 0));
    }
  }
  return;
}

/* ---- 0x004bf8b0  LightEd_MoveMarkerActor ---- */
/* Moves the marker actor to the selected light and toggles its visibility */

void __cdecl LightEd_MoveMarkerActor(void)

{
  if (((g_pLightEdMarkerActor != (Actor *)0x0) && (g_pLightEdSet != (Set *)0x0)) &&
     (g_nLightEdSelected != -1)) {
    sputActor_SetActorPosition
              (g_pLightEdMarkerActor,(float *)((&UINT_008d1730)[g_nLightEdSelected * 5] + 0x20));
    sputActor_SetActorRotation(g_pLightEdMarkerActor,&UINT_008d1738 + g_nLightEdSelected * 5,1);
    if ((&UINT_008d1734)[g_nLightEdSelected * 5] != 0) {
      g_pLightEdMarkerActor->dwFlags = g_pLightEdMarkerActor->dwFlags & 0xfffffffd;
      return;
    }
    g_pLightEdMarkerActor->dwFlags = g_pLightEdMarkerActor->dwFlags | 2;
  }
  return;
}

/* ---- 0x004bf930  LightEd_GetLightAngles ---- */
void __cdecl LightEd_GetLightAngles(int light,float *outAngles)

{
  rdVector_ExtractAngles((float *)(light + 0xc),outAngles);
  return;
}

/* ---- 0x004bffb0  LightEd_KeyboardProc ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_18 */
/* Keyboard hook of the light editor: arrow keys move the selected light, numpad 2 4 6 8 turn it,
   steps grow while a key is held */

int __stdcall LightEd_KeyboardProc(int code,uint wParam,uint lParam)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  float local_18;
  
  if ((((code == 0) && (g_hLightEdDialog != (void *)0x0)) &&
      (iVar2 = Win_IsFocusWithin(g_hLightEdDialog), iVar2 != 0)) && (g_nLightEdSelected != -1)) {
    uVar4 = lParam >> 0x10 & 0x2000;
    uVar3 = (~(lParam >> 0x10) & 0xffff) >> 0xf;
    uVar1 = (&UINT_008d1730)[g_nLightEdSelected * 5];
    if ((uVar3 & (g_dwLightEdLastKey & 0xffff) == wParam) == 0) {
      g_flLightEdMoveStep = 0.01f;
      g_flLightEdAngleStep = 1.0f;
      g_dwLightEdLastKey = CONCAT22(PIECE(g_dwLightEdLastKey,2,2),-(ushort)(uVar3 != 0) & (ushort)wParam)
      ;
    }
    else {
      g_flLightEdMoveStep = g_flLightEdMoveStep - -0.005f;
      g_flLightEdAngleStep = g_flLightEdAngleStep - -0.5f;
    }
    switch(wParam) {
    case 0x12:
      break;
    default:
      goto switchD_004c008d_caseD_13;
    case 0x25:
      if (uVar3 != 0) {
        local_18 = *(float *)(uVar1 + 0x20) - g_flLightEdMoveStep;
        iVar2 = 0x3ef;
LAB_004c0263:
        LightEd_SetDlgFloat((int)g_hLightEdDialog,iVar2,local_18,1);
        return 1;
      }
      break;
    case 0x26:
      if (uVar3 != 0) {
        if (uVar4 != 0) {
          local_18 = *(float *)(uVar1 + 0x28) + g_flLightEdMoveStep;
          iVar2 = 0x3f1;
          goto LAB_004c041f;
        }
        local_18 = *(float *)(uVar1 + 0x24) + g_flLightEdMoveStep;
        iVar2 = 0x3f0;
        goto LAB_004c0263;
      }
      break;
    case 0x27:
      if (uVar3 != 0) {
        LightEd_SetDlgFloat((int)g_hLightEdDialog,0x3ef,
                            *(float *)(uVar1 + 0x20) + g_flLightEdMoveStep,1);
        return 1;
      }
      break;
    case 0x28:
      if (uVar3 != 0) {
        if (uVar4 != 0) {
          LightEd_SetDlgFloat((int)g_hLightEdDialog,0x3f1,
                              *(float *)(uVar1 + 0x28) - g_flLightEdMoveStep,1);
          return 1;
        }
        LightEd_SetDlgFloat((int)g_hLightEdDialog,0x3f0,
                            *(float *)(uVar1 + 0x24) - g_flLightEdMoveStep,1);
        return 1;
      }
      break;
    case 0x62:
      if (uVar3 != 0) {
        lParam = PUN(uint,(float)((float)(&UINT_008d1738)[g_nLightEdSelected * 5] + g_flLightEdAngleStep));
        if (PUN(float,lParam) <= 360.0f) {
          if (PUN(float,lParam) < -180.0) {
            lParam = PUN(uint,(float)(PUN(float,lParam) - -360.0f));
          }
        }
        else {
          lParam = PUN(uint,(float)(PUN(float,lParam) - 360.0f));
        }
        local_18 = PUN(float,lParam);
        iVar2 = 0x3f2;
        goto LAB_004c0263;
      }
      break;
    case 100:
      if (uVar3 != 0) {
        if (uVar4 == 0) {
          lParam = PUN(uint,(float)((float)(&UINT_008d173c)[g_nLightEdSelected * 5] - g_flLightEdAngleStep));
          if (PUN(float,lParam) <= 360.0f) {
            if (PUN(float,lParam) < -180.0) {
              lParam = PUN(uint,(float)(PUN(float,lParam) - -360.0f));
            }
          }
          else {
            lParam = PUN(uint,(float)(PUN(float,lParam) - 360.0f));
          }
          LightEd_SetDlgFloat((int)g_hLightEdDialog,0x3f4,PUN(float,lParam),1);
          return 1;
        }
        lParam = PUN(uint,(float)((float)(&UINT_008d1740)[g_nLightEdSelected * 5] - g_flLightEdAngleStep));
        if (PUN(float,lParam) <= 360.0f) {
          if (PUN(float,lParam) < -180.0) {
            lParam = PUN(uint,(float)(PUN(float,lParam) - -360.0f));
          }
        }
        else {
          lParam = PUN(uint,(float)(PUN(float,lParam) - 360.0f));
        }
        local_18 = PUN(float,lParam);
        iVar2 = 0x3f5;
LAB_004c041f:
        LightEd_SetDlgFloat((int)g_hLightEdDialog,iVar2,local_18,1);
        return 1;
      }
      break;
    case 0x66:
      if (uVar3 != 0) {
        if (uVar4 != 0) {
          lParam = PUN(uint,(float)((float)(&UINT_008d1740)[g_nLightEdSelected * 5] + g_flLightEdAngleStep));
          if (PUN(float,lParam) <= 360.0f) {
            if (PUN(float,lParam) < -180.0) {
              lParam = PUN(uint,(float)(PUN(float,lParam) - -360.0f));
            }
          }
          else {
            lParam = PUN(uint,(float)(PUN(float,lParam) - 360.0f));
          }
          LightEd_SetDlgFloat((int)g_hLightEdDialog,0x3f5,PUN(float,lParam),1);
          return 1;
        }
        lParam = PUN(uint,(float)((float)(&UINT_008d173c)[g_nLightEdSelected * 5] + g_flLightEdAngleStep));
        if (PUN(float,lParam) <= 360.0f) {
          if (PUN(float,lParam) < -180.0) {
            lParam = PUN(uint,(float)(PUN(float,lParam) - -360.0f));
          }
        }
        else {
          lParam = PUN(uint,(float)(PUN(float,lParam) - 360.0f));
        }
        local_18 = PUN(float,lParam);
        iVar2 = 0x3f4;
        goto LAB_004c041f;
      }
      break;
    case 0x68:
      if (uVar3 != 0) {
        lParam = PUN(uint,(float)((float)(&UINT_008d1738)[g_nLightEdSelected * 5] - g_flLightEdAngleStep));
        if (PUN(float,lParam) <= 360.0f) {
          if (PUN(float,lParam) < -180.0) {
            lParam = PUN(uint,(float)(PUN(float,lParam) - -360.0f));
          }
        }
        else {
          lParam = PUN(uint,(float)(PUN(float,lParam) - 360.0f));
        }
        LightEd_SetDlgFloat((int)g_hLightEdDialog,0x3f2,PUN(float,lParam),1);
        return 1;
      }
    }
    return 1;
  }
switchD_004c008d_caseD_13:
  iVar2 = CallNextHookEx((int)g_hLightEdHook,code,wParam,lParam);
  return iVar2;
}
#endif



/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern unsigned char grim_def_DAT_004f0db8[16] __asm__("_DAT_004f0db8");
extern unsigned char grim_def_DAT_004f0de4[28] __asm__("_DAT_004f0de4");
extern void *grim_def_PTR_s_Error_004f0d14 __asm__("_PTR_s_Error_004f0d14");
extern unsigned int grim_def_UINT_004ddd74 __asm__("_UINT_004ddd74");
extern unsigned char grim_def_UINT_008d16c8[104] __asm__("_UINT_008d16c8");
extern unsigned int grim_def_UINT_008d1738 __asm__("_UINT_008d1738");
extern unsigned int grim_def_UINT_008d173c __asm__("_UINT_008d173c");
extern unsigned char grim_def_UINT_008d1740[1264] __asm__("_UINT_008d1740");
extern unsigned int grim_def_UINT_008d1c50 __asm__("_UINT_008d1c50");
extern unsigned int grim_def_UINT_008d1c54 __asm__("_UINT_008d1c54");
extern unsigned char grim_def_UINT_008d1c58[6616] __asm__("_UINT_008d1c58");
extern unsigned int grim_def_g_dwLightEdLastKey __asm__("_g_dwLightEdLastKey");
extern float grim_def_g_flLightEdAngleStep __asm__("_g_flLightEdAngleStep");
extern float grim_def_g_flLightEdMoveStep __asm__("_g_flLightEdMoveStep");
extern int grim_def_g_nLightEdBusy __asm__("_g_nLightEdBusy");
extern char grim_def_s_Could_not_open_file___s___004f0dc8[28] __asm__("_s_Could_not_open_file___s___004f0dc8");
extern char grim_def_s_Error_004f0d20[] __asm__("_s_Error_004f0d20");
extern char grim_def_s_Maximum_number_of_lights_already_004f0d78[64] __asm__("_s_Maximum_number_of_lights_already_004f0d78");
extern char grim_def_s_Set_Files____set__004f0e0c[48] __asm__("_s_Set_Files____set__004f0e0c");
extern char grim_def_s__Light__d__004f0e68[12] __asm__("_s__Light__d__004f0e68");
extern char grim_def_s_direction__f__f__f_004ec68c[24] __asm__("_s_direction__f__f__f_004ec68c");
extern char grim_def_s_intensity__f_004ec67c[16] __asm__("_s_intensity__f_004ec67c");
extern char grim_def_s_newlight_d_004f0d6c[12] __asm__("_s_newlight_d_004f0d6c");
extern char grim_def_s_penumbraangle__f_004ec654[20] __asm__("_s_penumbraangle__f_004ec654");
extern char grim_def_s_position__f__f__f_004ec6a4[88] __asm__("_s_position__f__f__f_004ec6a4");
extern char grim_def_s_section__004f0e00[12] __asm__("_s_section__004f0e00");
extern char grim_def_s_section__lights_004ec6fc[20] __asm__("_s_section__lights_004ec6fc");
extern char grim_def_s_umbraangle__f_004ec668[20] __asm__("_s_umbraangle__f_004ec668");
/* 0x004ddd74, 4 bytes */ /* loose */ unsigned int grim_def_UINT_004ddd74 __asm__("_UINT_004ddd74") = 0xa0a;
/* 0x004ec654, 20 bytes */ GRIM_DATA("004ec654") char grim_def_s_penumbraangle__f_004ec654[20] __asm__("_s_penumbraangle__f_004ec654") = "\tpenumbraangle\t%f\n";
/* 0x004ec668, 20 bytes */ /* loose */ char grim_def_s_umbraangle__f_004ec668[20] __asm__("_s_umbraangle__f_004ec668") = "\tumbraangle\t\t%f\n";
/* 0x004ec67c, 16 bytes */ /* loose */ char grim_def_s_intensity__f_004ec67c[16] __asm__("_s_intensity__f_004ec67c") = "\tintensity\t%f\n";
/* 0x004ec68c, 24 bytes */ /* loose */ char grim_def_s_direction__f__f__f_004ec68c[24] __asm__("_s_direction__f__f__f_004ec68c") = "\tdirection\t%f\t%f\t%f\n";
static unsigned char grim_anchor_004ec6a4[0] __attribute__((section(".data$grim_004ec6a4"), aligned(16), used));
static unsigned char grim_pad_004ec6a4[4] __attribute__((section(".data$grim_004ec6a4_"), aligned(4), used));
/* 0x004ec6a4, 88 bytes */ GRIM_DATA("004ec6a4z") char grim_def_s_position__f__f__f_004ec6a4[88] __asm__("_s_position__f__f__f_004ec6a4") = "\tposition\t\t%f\t%f\t%f\n\000\000\000\000\ttype\t\t%s\n\000\000direct\000\000spot\t\000\000\000omni\t\000\000\000\tlight\t\t%s\n\000\tnumlights\t%d\n\n";
/* 0x004ec6fc, 20 bytes */ GRIM_DATA("004ec6fc") char grim_def_s_section__lights_004ec6fc[20] __asm__("_s_section__lights_004ec6fc") = "section: lights\n";
/* 0x004f0d14, 4 bytes */ GRIM_DATA("004f0d14") void *grim_def_PTR_s_Error_004f0d14 __asm__("_PTR_s_Error_004f0d14") = (void *)&grim_def_s_Error_004f0d20;
/* 0x004f0d18, 4 bytes */ GRIM_DATA("004f0d18") float grim_def_g_flLightEdMoveStep __asm__("_g_flLightEdMoveStep") = 0.01f;
/* 0x004f0d1c, 4 bytes */ GRIM_DATA("004f0d1c") float grim_def_g_flLightEdAngleStep __asm__("_g_flLightEdAngleStep") = 1.0f;
/* 0x004f0d6c, 12 bytes */ /* loose */ char grim_def_s_newlight_d_004f0d6c[12] __asm__("_s_newlight_d_004f0d6c") = "newlight%d";
/* 0x004f0d78, 64 bytes */ /* loose */ char grim_def_s_Maximum_number_of_lights_already_004f0d78[64] __asm__("_s_Maximum_number_of_lights_already_004f0d78") = "Maximum number of lights already in room.  Try deleting a few.";
/* 0x004f0db8, 16 bytes */ /* loose */ unsigned char grim_def_DAT_004f0db8[16] __asm__("_DAT_004f0db8") = { 0x43, 0x61, 0x6e, 0x27, 0x74, 0x20, 0x41, 0x64, 0x64, 0x20, 0x4c, 0x69, 0x67, 0x68, 0x74 };
/* 0x004f0dc8, 28 bytes */ /* loose */ char grim_def_s_Could_not_open_file___s___004f0dc8[28] __asm__("_s_Could_not_open_file___s___004f0dc8") = "Could not open file \"%s\".";
/* 0x004f0de4, 28 bytes */ /* loose */ unsigned char grim_def_DAT_004f0de4[28] __asm__("_DAT_004f0de4") = {
    0x43, 0x6f, 0x75, 0x6c, 0x64, 0x20, 0x6e, 0x6f, 0x74, 0x20, 0x63, 0x72, 0x65, 0x61, 0x74, 0x65,
    0x20, 0x74, 0x65, 0x6d, 0x70, 0x20, 0x66, 0x69, 0x6c, 0x65, 0x2e
};
/* 0x004f0e00, 12 bytes */ /* loose */ char grim_def_s_section__004f0e00[12] __asm__("_s_section__004f0e00") = "section:";
static unsigned char grim_anchor_004f0e0c[0] __attribute__((section(".data$grim_004f0e0c"), aligned(16), used));
static unsigned char grim_pad_004f0e0c[12] __attribute__((section(".data$grim_004f0e0c_"), aligned(4), used));
/* 0x004f0e0c, 48 bytes */ GRIM_DATA("004f0e0cz") char grim_def_s_Set_Files____set__004f0e0c[48] __asm__("_s_Set_Files____set__004f0e0c") = "Set Files (*.set)\000*.set\000All Files (*.*)\000*.*";
/* 0x004f0e68, 12 bytes */ /* loose */ char grim_def_s__Light__d__004f0e68[12] __asm__("_s__Light__d__004f0e68") = "<Light %d>";
/* 0x008d16c8, 104 bytes */ GRIM_DATA("008d16c8") unsigned char grim_def_UINT_008d16c8[104] __asm__("_UINT_008d16c8") = {0};
/* 0x008d1738, 4 bytes */ GRIM_DATA("008d1738") unsigned int grim_def_UINT_008d1738 __asm__("_UINT_008d1738") = 0x0;
/* 0x008d173c, 4 bytes */ GRIM_DATA("008d173c") unsigned int grim_def_UINT_008d173c __asm__("_UINT_008d173c") = 0x0;
/* 0x008d1740, 1264 bytes */ GRIM_DATA("008d1740") unsigned char grim_def_UINT_008d1740[1264] __asm__("_UINT_008d1740") = {0};
/* 0x008d1c50, 4 bytes */ GRIM_DATA("008d1c50") unsigned int grim_def_UINT_008d1c50 __asm__("_UINT_008d1c50") = 0x0;
/* 0x008d1c54, 4 bytes */ GRIM_DATA("008d1c54") unsigned int grim_def_UINT_008d1c54 __asm__("_UINT_008d1c54") = 0x0;
/* 0x008d1c58, 6616 bytes */ GRIM_DATA("008d1c58") unsigned char grim_def_UINT_008d1c58[6616] __asm__("_UINT_008d1c58") = {0};
/* 0x008d3640, 4 bytes */ GRIM_DATA("008d3640") int grim_def_g_nLightEdBusy __asm__("_g_nLightEdBusy") = 0;
/* 0x008d3648, 4 bytes */ GRIM_DATA("008d3648") unsigned int grim_def_g_dwLightEdLastKey __asm__("_g_dwLightEdLastKey") = 0x0;
