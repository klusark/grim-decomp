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
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *puVar1;
  void *pvVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  *(uint *)((int)g_pLightEdSet + 0xb8) = UINT_008d3644;
  local_4 = 0;
  if (UINT_008d3644 != 0) {
    local_c = 0;
    local_8 = (uint)&UINT_008d1738;
    iVar5 = 0x15c;
    pvVar2 = g_pLightEdSet;
    do {
      puVar1 = (undefined4 *)((int)&UINT_008d1c30 + local_c);
      puVar6 = (undefined4 *)((int)pvVar2 + local_c + 0xbc);
      for (iVar3 = 0x1a; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar6 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar6 = puVar6 + 1;
      }
      uVar4 = 0;
      if (*(int *)((int)g_pLightEdSet + 0xb0) != 0) {
        iVar3 = 0;
        do {
          puVar1 = (undefined4 *)
                   (*(int *)(*(int *)((int)g_pLightEdSet + 0xac) + 0x48 + iVar3) + iVar5);
          uVar4 = uVar4 + 1;
          iVar3 = iVar3 + 300;
          *puVar1 = *(undefined4 *)((int)&UINT_008d1c50 + local_c);
          puVar1[1] = *(undefined4 *)((int)&UINT_008d1c54 + local_c);
          puVar1[2] = *(undefined4 *)((int)&UINT_008d1c58 + local_c);
        } while (uVar4 < *(uint *)((int)g_pLightEdSet + 0xb0));
      }
      pvVar2 = g_pLightEdSet;
      *(undefined4 *)(local_8 - 4) = 1;
      if (*(int *)(*(int *)(local_8 - 8) + 0x30) == 2) {
        *(undefined4 *)local_8 = 0;
        *(undefined4 *)(local_8 + 4) = 0;
        *(undefined4 *)(local_8 + 8) = 0;
      }
      else {
        LightEd_GetLightAngles(*(int *)(local_8 - 8) + 0x2c,(float *)local_8);
        pvVar2 = g_pLightEdSet;
      }
      local_4 = local_4 + 1;
      iVar5 = iVar5 + 0xc;
      local_c = local_c + 0x68;
      local_8 = local_8 + 0x14;
    } while (local_4 < UINT_008d3644);
  }
  return;
}
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004be4c0  LightEd_ResetLight ---- */
void __cdecl LightEd_ResetLight(int index,int mode)

{
  int *piVar1;
  uint uVar2;
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
    if (*(int *)((int)g_pLightEdSet + 0xb0) != 0) {
      iVar3 = 0;
      do {
        uVar2 = (&UINT_008d1730)[index * 5];
        piVar1 = (int *)(*(int *)((int)g_pLightEdSet + 0xac) + 0x48 + iVar3);
        iVar3 = iVar3 + 300;
        puVar5 = (undefined4 *)(*piVar1 + (index + 0x1d) * 0xc);
        uVar4 = uVar4 + 1;
        *puVar5 = *(undefined4 *)(uVar2 + 0x20);
        puVar5[1] = *(undefined4 *)(uVar2 + 0x24);
        puVar5[2] = *(undefined4 *)(uVar2 + 0x28);
      } while (uVar4 < *(uint *)((int)g_pLightEdSet + 0xb0));
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
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  uint *puVar6;
  int iVar7;
  undefined4 *puVar8;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  if (index < *(uint *)((int)g_pLightEdSet + 0xb8)) {
    local_4 = index + 1;
    if (local_4 < *(uint *)((int)g_pLightEdSet + 0xb8)) {
      iVar2 = local_4 * 0x68;
      puVar6 = &UINT_008d1734 + local_4 * 5;
      iVar7 = (index + 0x1d) * 0xc;
      do {
        puVar8 = (undefined4 *)((int)g_pLightEdSet + iVar2 + 0xbc);
        puVar3 = (undefined4 *)((int)g_pLightEdSet + iVar2 + 0x54);
        for (iVar4 = 0x1a; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar3 = *puVar8;
          puVar8 = puVar8 + 1;
          puVar3 = puVar3 + 1;
        }
        uVar5 = 0;
        if (*(int *)((int)g_pLightEdSet + 0xb0) != 0) {
          iVar4 = 0;
          do {
            iVar4 = iVar4 + 300;
            iVar1 = *(int *)(*(int *)((int)g_pLightEdSet + 0xac) + -0xe4 + iVar4);
            puVar8 = (undefined4 *)(iVar1 + 0xc + iVar7);
            puVar3 = (undefined4 *)(iVar1 + iVar7);
            uVar5 = uVar5 + 1;
            *puVar3 = *puVar8;
            puVar3[1] = puVar8[1];
            puVar3[2] = puVar8[2];
          } while (uVar5 < *(uint *)((int)g_pLightEdSet + 0xb0));
        }
        puVar6[-5] = *puVar6;
        LightEd_GetLightAngles(puVar6[-6] + 0x2c,(float *)(puVar6 + -4));
        local_4 = local_4 + 1;
        iVar7 = iVar7 + 0xc;
        iVar2 = iVar2 + 0x68;
        puVar6 = puVar6 + 5;
      } while (local_4 < *(uint *)((int)g_pLightEdSet + 0xb8));
    }
    uVar5 = 0;
    if (*(int *)((int)g_pLightEdSet + 0xb0) != 0) {
      iVar2 = 0;
      do {
        iVar7 = *(int *)(*(int *)((int)g_pLightEdSet + 0xac) + 0x48 + iVar2);
        iVar2 = iVar2 + 300;
        puVar8 = (undefined4 *)(iVar7 + (*(int *)((int)g_pLightEdSet + 0xb8) + 0x1c) * 0xc);
        *puVar8 = 0;
        puVar8[1] = 0;
        puVar8[2] = 0;
        uVar5 = uVar5 + 1;
        *(int *)(iVar7 + 0x58) = *(int *)(iVar7 + 0x58) + -1;
      } while (uVar5 < *(uint *)((int)g_pLightEdSet + 0xb0));
    }
    puVar8 = (undefined4 *)((int)g_pLightEdSet + *(int *)((int)g_pLightEdSet + 0xb8) * 0x68 + 0x54);
    for (iVar2 = 0x1a; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar8 = 0;
      puVar8 = puVar8 + 1;
    }
    *(int *)((int)g_pLightEdSet + 0xb8) = *(int *)((int)g_pLightEdSet + 0xb8) + -1;
    uVar5 = index;
    if (*(int *)((int)g_pLightEdSet + 0xb8) <= (int)index) {
      uVar5 = *(int *)((int)g_pLightEdSet + 0xb8) - 1;
    }
    SendDlgItemMessageA((int)g_hLightEdDialog,1000,0x182,index,0);
    SendDlgItemMessageA((int)g_hLightEdDialog,1000,0x186,uVar5,0);
    LightEd_UpdateDialog((int)g_hLightEdDialog);
  }
  return;
}
#undef local_4
#undef local_8


/* ---- 0x004be730  LightEd_MakeUniqueName ---- */
/* newlight%d, skipping names already used in the set */

void __cdecl LightEd_MakeUniqueName(int param_1,char *param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  byte *pbVar4;
  
  uVar2 = *(uint *)(param_1 + 0xb8);
  do {
    if (0x3f < uVar2) {
      return;
    }
    sprintf(param_2,s_newlight_d_004f0d6c,uVar2);
    uVar3 = 0;
    if (*(int *)(param_1 + 0xb8) != 0) {
      pbVar4 = (byte *)(param_1 + 0xbc);
      do {
        if ((uVar3 != uVar2) && (iVar1 = _stricmp((byte *)param_2,pbVar4), iVar1 == 0)) break;
        uVar3 = uVar3 + 1;
        pbVar4 = pbVar4 + 0x68;
      } while (uVar3 < *(uint *)(param_1 + 0xb8));
    }
    if (*(uint *)(param_1 + 0xb8) <= uVar3) {
      return;
    }
    uVar2 = uVar2 + 1;
  } while( true );
}

/* ---- 0x004be7b0  LightEd_AddLight ---- */
/* Appends a light to the current set (max 64) and selects it in the dialog */

void __cdecl LightEd_AddLight(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *puVar1;
  undefined4 *puVar2;
  void *pvVar3;
  char cVar4;
  int a4;
  void *pvVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  char *pcVar9;
  char *pcVar10;
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(char (*)[32])(_frame + (0x40 - 0x20)))
  
  if (0x3f < *(uint *)((int)g_pLightEdSet + 0xb8)) {
    MessageBoxA((int)g_hLightEdDialog,((unsigned)(uintptr_t)&s_Maximum_number_of_lights_already_004f0d78),((unsigned)(uintptr_t)&DAT_004f0db8),0x30);
    return;
  }
  a4 = *(int *)((int)g_pLightEdSet + 0xb8);
  LightEd_MakeUniqueName((int)g_pLightEdSet,local_20);
  uVar6 = 0xffffffff;
  iVar8 = a4 * 0x68;
  pcVar9 = local_20;
  do {
    pcVar10 = pcVar9;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar10 = pcVar9 + 1;
    cVar4 = *pcVar9;
    pcVar9 = pcVar10;
  } while (cVar4 != '\0');
  uVar6 = ~uVar6;
  pcVar9 = pcVar10 + -uVar6;
  pcVar10 = (char *)((int)g_pLightEdSet + iVar8 + 0xbc);
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar10 = *(undefined4 *)pcVar9;
    pcVar9 = pcVar9 + 4;
    pcVar10 = pcVar10 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar10 = *pcVar9;
    pcVar9 = pcVar9 + 1;
    pcVar10 = pcVar10 + 1;
  }
  uVar6 = 0;
  puVar1 = (undefined4 *)
           (*(int *)((int)g_pLightEdSet + 0xac) + 0x2c + *(int *)((int)g_pLightEdSet + 0xb4) * 300);
  puVar2 = (undefined4 *)((int)g_pLightEdSet + iVar8 + 0xdc);
  *puVar2 = *puVar1;
  puVar2[1] = puVar1[1];
  puVar2[2] = puVar1[2];
  *(int *)((int)g_pLightEdSet + 0xb8) = *(int *)((int)g_pLightEdSet + 0xb8) + 1;
  pvVar3 = g_pLightEdSet;
  *(undefined4 *)((int)g_pLightEdSet + iVar8 + 0xec) = 2;
  *(undefined4 *)((int)pvVar3 + iVar8 + 0xf0) = 1;
  pvVar3 = (void *)((int)pvVar3 + iVar8 + 0xe8);
  *(undefined4 *)((int)pvVar3 + 0xc) = 0;
  *(undefined4 *)((int)pvVar3 + 0x10) = 0;
  *(undefined4 *)((int)pvVar3 + 0x14) = 0;
  *(undefined4 *)((int)pvVar3 + 0x18) = 0x3f800000;
  *(undefined4 *)((int)pvVar3 + 0x1c) = 0xffffff;
  *(undefined4 *)((int)pvVar3 + 0x20) = 0;
  *(undefined4 *)((int)pvVar3 + 0x24) = 0;
  *(undefined4 *)((int)pvVar3 + 0x28) = 0;
  *(undefined4 *)((int)pvVar3 + 0x2c) = 0;
  pvVar5 = g_pLightEdSet;
  (&UINT_008d1730)[a4 * 5] = (int)g_pLightEdSet + iVar8 + 0xbc;
  (&UINT_008d1734)[a4 * 5] = 1;
  (&UINT_008d1738)[a4 * 5] = 0;
  (&UINT_008d173c)[a4 * 5] = 0;
  (&UINT_008d1740)[a4 * 5] = 0;
  if (*(int *)((int)pvVar5 + 0xb0) != 0) {
    local_24 = 0;
    do {
      rdCamera_AddLight(*(void **)(*(int *)((int)pvVar5 + 0xac) + 0x48 + local_24),pvVar3,
                        (float *)((int)pvVar5 + iVar8 + 0xdc));
      uVar6 = uVar6 + 1;
      local_24 = local_24 + 300;
      pvVar5 = g_pLightEdSet;
    } while (uVar6 < *(uint *)((int)g_pLightEdSet + 0xb0));
  }
  SendDlgItemMessageA((int)g_hLightEdDialog,1000,0x180,0,(int)pvVar5 + iVar8 + 0xbc);
  SendDlgItemMessageA((int)g_hLightEdDialog,1000,0x186,a4,0);
  LightEd_UpdateDialog((int)g_hLightEdDialog);
  return;
}
#undef local_20
#undef local_24


/* ---- 0x004be990  LightEd_SaveSetFile ---- */
/* Rewrites the set file with the edited lights section via a temp file */

void __cdecl LightEd_SaveSetFile(void)

{
  unsigned char _frame[0x370] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  int iVar3;
  uint *puVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  void *file;
  #define local_358 (*(uint *)(_frame + (0x370 - 0x358)))
  #define local_354 (*(uint *)(_frame + (0x370 - 0x354)))
  #define local_350 (*(uint *)(_frame + (0x370 - 0x350)))
  #define local_34c (*(uint *)(_frame + (0x370 - 0x34c)))
  #define local_348 (*(uint *)(_frame + (0x370 - 0x348)))
  #define local_33c (*(uint *)(_frame + (0x370 - 0x33c)))
  #define local_338 (*(uint *)(_frame + (0x370 - 0x338)))
  #define local_334 (*(uint *)(_frame + (0x370 - 0x334)))
  #define local_32c (*(uint *)(_frame + (0x370 - 0x32c)))
  #define local_328 (*(uint *)(_frame + (0x370 - 0x328)))
  #define local_324 (*(uint *)(_frame + (0x370 - 0x324)))
  #define local_31c (*(uint *)(_frame + (0x370 - 0x31c)))
  #define local_318 (*(uint *)(_frame + (0x370 - 0x318)))
  #define local_314 (*(uint *)(_frame + (0x370 - 0x314)))
  #define local_310 (*(uint *)(_frame + (0x370 - 0x310)))
  #define auStack_30c (*(uint (*)[65])(_frame + (0x370 - 0x30c)))
  #define acStack_208 (*(char (*)[260])(_frame + (0x370 - 0x208)))
  #define local_104 (*(char (*)[260])(_frame + (0x370 - 0x104)))
  
  local_358 = 0x4c;
  local_354 = (uint)g_hLightEdDialog;
  local_350 = Win_GetInstance();
  local_33c = (uint)local_104;
  uVar5 = 0xffffffff;
  local_34c = (uint)s_Set_Files____set__004f0e0c;
  local_348 = 0;
  local_338 = 0x104;
  local_334 = 0;
  local_32c = 0;
  local_328 = 0;
  local_324 = 0x8080e;
  local_31c = (uint)&DAT_004ec490;
  local_318 = 0;
  local_314 = 0;
  local_310 = 0;
  pcVar7 = g_pLightEdSet;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = local_104;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  iVar2 = GetSaveFileNameA((int)&local_358);
  if (iVar2 == 0) {
    return;
  }
  iVar2 = (*g_pStd_HS->pFopen)(g_pLightEdSet,&DAT_004ec5bc);
  file = (void *)0x0;
  acStack_208[0] = '\0';
  if (iVar2 == 0) {
    wsprintfA((char *)auStack_30c,s_Could_not_open_file___s___004f0dc8,g_pLightEdSet);
    MessageBoxA(0,(int)auStack_30c,(int)PTR_s_Error_004f0d14,0x30);
    return;
  }
  GetTempPathA(0x104,(int)auStack_30c);
  iVar3 = GetTempFileNameA((int)auStack_30c,((unsigned)(uintptr_t)&DAT_004ec490),0,(int)acStack_208);
  if (iVar3 == 0) {
LAB_004becb0:
    if (file != (void *)0x0) {
      (*g_pStd_HS->pFclose)(file);
      goto LAB_004becd7;
    }
  }
  else {
    file = (void *)(*g_pStd_HS->pFopen)(acStack_208,&DAT_004dee34);
    if (file != (void *)0x0) {
      iVar3 = (*g_pStd_HS->pFeof)(iVar2);
      while (iVar3 == 0) {
        (*g_pStd_HS->pFgets)(iVar2,auStack_30c,0x104);
        puVar4 = String_ContainsSubstring(auStack_30c,s_section__004f0e00);
        if ((puVar4 != (uint *)0x0) &&
           (puVar4 = String_ContainsSubstring(auStack_30c,s_lights_004ec724), puVar4 != (uint *)0x0)
           ) break;
        (*g_pStd_HS->pFprintf)(file,auStack_30c);
        iVar3 = (*g_pStd_HS->pFeof)(iVar2);
      }
      iVar3 = (*g_pStd_HS->pFeof)(iVar2);
      if (iVar3 == 0) {
        LightEd_WriteLightsSection(g_pLightEdSet,file);
        iVar3 = (*g_pStd_HS->pFeof)(iVar2);
        while (iVar3 == 0) {
          (*g_pStd_HS->pFgets)(iVar2,auStack_30c,0x104);
          puVar4 = String_ContainsSubstring(auStack_30c,s_section__004f0e00);
          if (puVar4 != (uint *)0x0) {
            (*g_pStd_HS->pFprintf)(file,auStack_30c);
            break;
          }
          iVar3 = (*g_pStd_HS->pFeof)(iVar2);
        }
        iVar3 = (*g_pStd_HS->pFeof)(iVar2);
        if (iVar3 == 0) {
          iVar3 = (*g_pStd_HS->pFeof)(iVar2);
          while (iVar3 == 0) {
            (*g_pStd_HS->pFgets)(iVar2,auStack_30c,0x104);
            (*g_pStd_HS->pFprintf)(file,auStack_30c);
            iVar3 = (*g_pStd_HS->pFeof)(iVar2);
          }
          (*g_pStd_HS->pFclose)(iVar2);
          (*g_pStd_HS->pFclose)(file);
          iVar2 = (*g_pStd_HS->pFopen)(acStack_208,&DAT_004ec5bc);
          file = (void *)(*g_pStd_HS->pFopen)(local_104,&DAT_004dee34);
          if (iVar2 != 0) {
            if (file == (void *)0x0) goto LAB_004becb4;
            iVar3 = (*g_pStd_HS->pFeof)(iVar2);
            while (iVar3 == 0) {
              (*g_pStd_HS->pFgets)(iVar2,auStack_30c,0x104);
              (*g_pStd_HS->pFprintf)(file,auStack_30c);
              iVar3 = (*g_pStd_HS->pFeof)(iVar2);
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
  (*g_pStd_HS->pFclose)(iVar2);
  if (acStack_208[0] == '\0') {
    return;
  }
  DeleteFileA((int)acStack_208);
  return;
}
#undef acStack_208
#undef auStack_30c
#undef local_104
#undef local_310
#undef local_314
#undef local_318
#undef local_31c
#undef local_324
#undef local_328
#undef local_32c
#undef local_334
#undef local_338
#undef local_33c
#undef local_348
#undef local_34c
#undef local_350
#undef local_354
#undef local_358


/* ---- 0x004bed40  LightEd_WriteLightsSection ---- */
/* Emits 'section: lights' with name/type/position/direction/intensity/angles per light */

void __cdecl LightEd_WriteLightsSection(void *set,void *file)

{
  uint uVar1;
  int iVar2;
  
  (*g_pStd_HS->pFprintf)(file,s_section__lights_004ec6fc);
  (*g_pStd_HS->pFprintf)();
  iVar2 = (int)set + 0xbc;
  uVar1 = 0;
  if (*(int *)((int)set + 0xb8) != 0) {
    do {
      (*g_pStd_HS->pFprintf)();
      (*g_pStd_HS->pFprintf)();
      (*g_pStd_HS->pFprintf)
                (file,s_position__f__f__f_004ec6a4,(double)*(float *)(iVar2 + 0x20),
                 (double)*(float *)(iVar2 + 0x24),(double)*(float *)(iVar2 + 0x28));
      (*g_pStd_HS->pFprintf)
                (file,s_direction__f__f__f_004ec68c,(double)*(float *)(iVar2 + 0x38),
                 (double)*(float *)(iVar2 + 0x3c),(double)*(float *)(iVar2 + 0x40));
      (*g_pStd_HS->pFprintf)(file,s_intensity__f_004ec67c,(double)*(float *)(iVar2 + 0x44));
      (*g_pStd_HS->pFprintf)(file,s_umbraangle__f_004ec668,(double)*(float *)(iVar2 + 0x4c));
      (*g_pStd_HS->pFprintf)(file,s_penumbraangle__f_004ec654,(double)*(float *)(iVar2 + 0x54));
      (*g_pStd_HS->pFprintf)();
      (*g_pStd_HS->pFprintf)(file,&UINT_004ddd74);
      iVar2 = iVar2 + 0x68;
      uVar1 = uVar1 + 1;
    } while (uVar1 < *(uint *)((int)set + 0xb8));
  }
  return;
}

/* ---- 0x004bef10  LightEd_FillListBox ---- */
void __cdecl LightEd_FillListBox(int param_1)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint *puVar2;
  uint uVar3;
  char *a5;
  code *pcVar4;
  #define local_20 (*(char (*)[32])(_frame + (0x30 - 0x20)))
  
  pcVar4 = SendDlgItemMessageA_exref;
  SendDlgItemMessageA(param_1,1000,0x184,0,0);
  uVar3 = 0;
  if (*(int *)((int)g_pLightEdSet + 0xb8) != 0) {
    puVar2 = &UINT_008d1730;
    do {
      a5 = (char *)*puVar2;
      if (*a5 == '\0') {
        a5 = local_20;
        wsprintfA(local_20,s__Light__d__004f0e68,uVar3);
      }
      SendDlgItemMessageA(param_1,1000,0x180,0,(int)a5);
      uVar3 = uVar3 + 1;
      puVar2 = puVar2 + 5;
      pcVar4 = SendDlgItemMessageA_exref;
    } while (uVar3 < *(uint *)((int)g_pLightEdSet + 0xb8));
  }
  iVar1 = (*pcVar4)(param_1,1000,0x18b,0,0);
  if (0 < iVar1) {
    (*pcVar4)(param_1,1000,0x186,0,0);
    LightEd_UpdateDialog(param_1);
    LightEd_ResetLight(0,1);
  }
  return;
}
#undef local_20


/* ---- 0x004befe0  LightEd_UpdateDialog ---- */
/* Refreshes every control from the selected light */

void __cdecl LightEd_UpdateDialog(int param_1)

{
  uint uVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  
  bVar2 = false;
  if (g_pLightEdSet != (void *)0x0) {
    g_nLightEdSelected = SendDlgItemMessageA(param_1,1000,0x188,0,0);
    if (g_nLightEdSelected == -1) {
      LightEd_EnableControls(0);
      bVar2 = false;
    }
    else {
      uVar1 = (&UINT_008d1730)[g_nLightEdSelected * 5];
      LightEd_EnableControls(1);
      CheckDlgButton(param_1,0x3fa,(uint)(*(int *)(uVar1 + 0x34) != 0));
      CheckDlgButton(param_1,0x3fe,(uint)((&UINT_008d1734)[g_nLightEdSelected * 5] != 0));
      LightEd_SetDlgFloat(param_1,0x3ec,*(float *)(uVar1 + 0x44),1);
      LightEd_SetDlgFloat(param_1,0x3ef,*(float *)(uVar1 + 0x20),1);
      LightEd_SetDlgFloat(param_1,0x3f0,*(float *)(uVar1 + 0x24),1);
      LightEd_SetDlgFloat(param_1,0x3f1,*(float *)(uVar1 + 0x28),1);
      if ((*(int *)(uVar1 + 0x30) == 1) || (*(int *)(uVar1 + 0x30) == 0)) {
        iVar3 = 1;
      }
      else {
        iVar3 = 0;
      }
      CheckDlgButton(param_1,0x3e9,iVar3);
      CheckDlgButton(param_1,0x3ea,(uint)(*(int *)(uVar1 + 0x30) == 2));
      CheckDlgButton(param_1,0x3eb,(uint)(*(int *)(uVar1 + 0x30) == 3));
      switch(*(undefined4 *)(uVar1 + 0x30)) {
      case 0:
      case 1:
        iVar4 = 0;
        iVar3 = GetDlgItem(param_1,0x3ed);
        EnableWindow(iVar3,iVar4);
        iVar4 = 0;
        iVar3 = GetDlgItem(param_1,0x3ee);
        EnableWindow(iVar3,iVar4);
        LightEd_SetDlgFloat(param_1,0x3f2,(float)(&UINT_008d1738)[g_nLightEdSelected * 5],0);
        LightEd_SetDlgFloat(param_1,0x3f4,(float)(&UINT_008d173c)[g_nLightEdSelected * 5],0);
        LightEd_SetDlgFloat(param_1,0x3f5,(float)(&UINT_008d1740)[g_nLightEdSelected * 5],0);
        LightEd_MoveMarkerActor();
        bVar2 = true;
        break;
      case 2:
        iVar4 = 0;
        iVar3 = GetDlgItem(param_1,0x3f2);
        EnableWindow(iVar3,iVar4);
        iVar4 = 0;
        iVar3 = GetDlgItem(param_1,0x3f4);
        EnableWindow(iVar3,iVar4);
        iVar4 = 0;
        iVar3 = GetDlgItem(param_1,0x3f5);
        EnableWindow(iVar3,iVar4);
        iVar4 = 0;
        iVar3 = GetDlgItem(param_1,0x3ed);
        EnableWindow(iVar3,iVar4);
        iVar4 = 0;
        iVar3 = GetDlgItem(param_1,0x3ee);
        EnableWindow(iVar3,iVar4);
      default:
        LightEd_MoveMarkerActor();
        bVar2 = true;
        break;
      case 3:
        LightEd_SetDlgFloat(param_1,0x3f2,(float)(&UINT_008d1738)[g_nLightEdSelected * 5],0);
        LightEd_SetDlgFloat(param_1,0x3f4,(float)(&UINT_008d173c)[g_nLightEdSelected * 5],0);
        LightEd_SetDlgFloat(param_1,0x3f5,(float)(&UINT_008d1740)[g_nLightEdSelected * 5],0);
        LightEd_SetDlgFloat(param_1,0x3ed,
                            *(float *)((&UINT_008d1730)[g_nLightEdSelected * 5] + 0x4c),1);
        LightEd_SetDlgFloat(param_1,0x3ee,
                            *(float *)((&UINT_008d1730)[g_nLightEdSelected * 5] + 0x54),1);
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
void __cdecl LightEd_EnableControls(int param_1)

{
  unsigned char _frame[0x70] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint a2;
  int a1;
  uint *puVar1;
  int a2_00;
  #define local_60 (*(uint *)(_frame + (0x70 - 0x60)))
  #define local_5c (*(uint *)(_frame + (0x70 - 0x5c)))
  #define local_58 (*(uint *)(_frame + (0x70 - 0x58)))
  #define local_54 (*(uint *)(_frame + (0x70 - 0x54)))
  #define local_50 (*(uint *)(_frame + (0x70 - 0x50)))
  #define local_4c (*(uint *)(_frame + (0x70 - 0x4c)))
  #define local_48 (*(uint *)(_frame + (0x70 - 0x48)))
  #define local_44 (*(uint *)(_frame + (0x70 - 0x44)))
  #define local_40 (*(uint *)(_frame + (0x70 - 0x40)))
  #define local_3c (*(uint *)(_frame + (0x70 - 0x3c)))
  #define local_38 (*(uint *)(_frame + (0x70 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x70 - 0x34)))
  #define local_30 (*(uint *)(_frame + (0x70 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x70 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x70 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x70 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x70 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x70 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x70 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x70 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x70 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x70 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x70 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x70 - 0x4)))
  
  a2 = 0x3e9;
  local_60 = 0x3e9;
  local_5c = 0x3ea;
  local_58 = 0x3eb;
  local_54 = 0x3ec;
  local_50 = 0x3ed;
  local_4c = 0x3ee;
  local_48 = 0x3ef;
  local_44 = 0x3f0;
  local_40 = 0x3f1;
  local_3c = 0x3f2;
  local_38 = 0x3f4;
  local_34 = 0x3f5;
  local_30 = 0x3f7;
  local_2c = 0x3f9;
  local_28 = 0x3fa;
  local_24 = 0x3fb;
  local_20 = 0x3fc;
  local_1c = 0x3fd;
  local_18 = 0x3fe;
  local_14 = 0x3ff;
  local_10 = 0x400;
  local_c = 0x401;
  local_8 = 0x402;
  local_4 = 0;
  puVar1 = &local_60;
  do {
    a2_00 = param_1;
    a1 = GetDlgItem((int)g_hLightEdDialog,a2);
    EnableWindow(a1,a2_00);
    a2 = puVar1[1];
    puVar1 = puVar1 + 1;
  } while (a2 != 0);
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
#undef local_30
#undef local_34
#undef local_38
#undef local_3c
#undef local_4
#undef local_40
#undef local_44
#undef local_48
#undef local_4c
#undef local_50
#undef local_54
#undef local_58
#undef local_5c
#undef local_60
#undef local_8
#undef local_c


/* ---- 0x004bf3f0  LightEd_SetDlgFloat ---- */
void __cdecl LightEd_SetDlgFloat(int param_1,int param_2,float param_3,int param_4)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_4c (*(char (*)[76])(_frame + (0x60 - 0x4c)))
  
  iVar1 = GetDlgItem(param_1,param_2);
  iVar1 = IsWindowEnabled(iVar1);
  if (iVar1 != 0) {
    sprintf(local_4c,&DAT_004ddc14,(double)param_3);
    if (param_4 == 0) {
      g_nLightEdBusy = 1;
    }
    SetDlgItemTextA(param_1,param_2,(int)local_4c);
    g_nLightEdBusy = 0;
  }
  return;
}
#undef local_4c


/* ---- 0x004bf460  LightEd_RefreshControl ---- */
/* The control id arrives in the float slot (0x3ea..) because of the varargs caller */

void __cdecl LightEd_RefreshControl(int param_1,float param_2,uint param_3,int param_4)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int a2;
  float fVar1;
  #define local_50 (*(uint *)(_frame + (0x60 - 0x50)))
  #define local_4c (*(byte (*)[76])(_frame + (0x60 - 0x4c)))
  
  if (g_nLightEdSelected == -1) {
    return;
  }
  if (g_pLightEdSet == (void *)0x0) {
    return;
  }
  if (param_2 == 1.42792e-42) {
    a2 = 0x3ec;
    local_50 = 1000;
  }
  else if (param_2 == 1.43353e-42) {
    a2 = 0x3ed;
    local_50 = 100;
  }
  else {
    if (param_2 != 1.43493e-42) {
      return;
    }
    a2 = 0x3ee;
    local_50 = 100;
  }
  GetDlgItemTextA(param_1,a2,(int)local_4c,0x4b);
  fVar1 = atof(local_4c);
  switch(param_3) {
  case 0:
    fVar1 = fVar1 * (float)local_50 - -1.0;
    break;
  case 1:
    fVar1 = fVar1 * (float)local_50 - 1.0;
    break;
  default:
    goto switchD_004bf4ef_caseD_2;
  case 4:
  case 5:
    param_2 = (float)param_4 / (float)local_50;
    goto LAB_004bf52e;
  }
  param_2 = fVar1 / (float)local_50;
LAB_004bf52e:
  LightEd_SetDlgFloat(param_1,a2,param_2,0);
switchD_004bf4ef_caseD_2:
  return;
}
#undef local_4c
#undef local_50


/* ---- 0x004bf560  LightEd_ReadControl ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Parses the edited text field back into the light (position, direction, intensity, angles,
   falloff) */

void __cdecl LightEd_ReadControl(int hdlg,int id)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint a5;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar1;
  float outer;
  int a2;
  #define local_4c (*(byte (*)[76])(_frame + (0x60 - 0x4c)))
  
  GetDlgItemTextA(hdlg,id,(int)local_4c,0x4b);
  outer = atof(local_4c);
  if (g_pLightEdSet == (void *)0x0) {
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
    lVar1 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    a5 = (uint)lVar1 & 0xffff;
    a2 = 0x3fb;
    goto LAB_004bf718;
  case 0x3ed:
    rdLight_SetAngles((void *)((&UINT_008d1730)[g_nLightEdSelected * 5] + 0x2c),outer,
                      *(float *)((&UINT_008d1730)[g_nLightEdSelected * 5] + 0x54));
    if (g_nLightEdBusy != 0) {
      return;
    }
    lVar1 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    a5 = (uint)lVar1 & 0xffff;
    a2 = 0x3ff;
    goto LAB_004bf718;
  case 0x3ee:
    rdLight_SetAngles((void *)((&UINT_008d1730)[g_nLightEdSelected * 5] + 0x2c),
                      *(float *)((&UINT_008d1730)[g_nLightEdSelected * 5] + 0x4c),outer);
    if (g_nLightEdBusy != 0) {
      return;
    }
    lVar1 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
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

#endif


/* ---- 0x004bf760  LightEd_SetLightPosComponent ---- */
void __cdecl LightEd_SetLightPosComponent(int param_1,short param_2,uint param_3)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = 0;
  *(uint *)((&UINT_008d1730)[param_1 * 5] + 0x20 + param_2 * 4) = param_3;
  if (*(int *)((int)g_pLightEdSet + 0xb0) != 0) {
    iVar2 = 0;
    do {
      uVar3 = uVar3 + 1;
      piVar1 = (int *)(*(int *)((int)g_pLightEdSet + 0xac) + 0x48 + iVar2);
      iVar2 = iVar2 + 300;
      *(uint *)(*piVar1 + ((int)param_2 + (param_1 + 0x1d) * 3) * 4) = param_3;
    } while (uVar3 < *(uint *)((int)g_pLightEdSet + 0xb0));
  }
  return;
}

/* ---- 0x004bf7d0  LightEd_SetLightAngle ---- */
/* Stores the angle and recomputes the direction vector */

void __cdecl LightEd_SetLightAngle(int param_1,short param_2,uint param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  #define local_c (*(float *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_c = 0.0;
  (&UINT_008d1738)[param_1 * 5 + (int)param_2] = param_3;
  local_8 = 0x3f800000;
  local_4 = 0;
  rdVector_Rotate3Acc(&local_c,(float *)(&UINT_008d1738 + param_1 * 5));
  uVar1 = (&UINT_008d1730)[param_1 * 5];
  *(float *)(uVar1 + 0x38) = local_c;
  *(uint *)(uVar1 + 0x3c) = local_8;
  *(uint *)(uVar1 + 0x40) = local_4;
  return;
}
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004bf850  LightEd_SetAllEnabled ---- */
void __cdecl LightEd_SetAllEnabled(int param_1)

{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  
  if (g_pLightEdSet != (void *)0x0) {
    uVar2 = 0;
    if (*(int *)((int)g_pLightEdSet + 0xb8) != 0) {
      puVar3 = &UINT_008d1730;
      do {
        uVar1 = *puVar3;
        uVar2 = uVar2 + 1;
        puVar3 = puVar3 + 5;
        *(int *)(uVar1 + 0x34) = param_1;
      } while (uVar2 < *(uint *)((int)g_pLightEdSet + 0xb8));
    }
    if ((g_hLightEdDialog != (void *)0x0) && (g_nLightEdSelected != -1)) {
      CheckDlgButton((int)g_hLightEdDialog,0x3fa,(uint)(param_1 != 0));
    }
  }
  return;
}

/* ---- 0x004bf8b0  LightEd_MoveMarkerActor ---- */
/* Moves the marker actor to the selected light and toggles its visibility */

void __cdecl LightEd_MoveMarkerActor(void)

{
  if (((g_pLightEdMarkerActor != (Actor *)0x0) && (g_pLightEdSet != (void *)0x0)) &&
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
void __cdecl LightEd_GetLightAngles(int param_1,float *param_2)

{
  rdVector_ExtractAngles((float *)(param_1 + 0xc),param_2);
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
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  #define local_18 (*(float *)(_frame + (0x30 - 0x18)))
  
  if ((((code == 0) && (g_hLightEdDialog != (void *)0x0)) &&
      (iVar2 = Win_IsFocusWithin(g_hLightEdDialog), iVar2 != 0)) && (g_nLightEdSelected != -1)) {
    uVar4 = lParam >> 0x10 & 0x2000;
    uVar3 = (~(lParam >> 0x10) & 0xffff) >> 0xf;
    uVar1 = (&UINT_008d1730)[g_nLightEdSelected * 5];
    if ((uVar3 & (g_dwLightEdLastKey & 0xffff) == wParam) == 0) {
      g_flLightEdMoveStep = 0.01;
      g_flLightEdAngleStep = 1.0;
      g_dwLightEdLastKey = CONCAT22(PIECE(g_dwLightEdLastKey,2,2),-(ushort)(uVar3 != 0) & (ushort)wParam)
      ;
    }
    else {
      g_flLightEdMoveStep = g_flLightEdMoveStep - -0.005;
      g_flLightEdAngleStep = g_flLightEdAngleStep - -0.5;
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
        if (PUN(float,lParam) <= 360.0) {
          if (PUN(float,lParam) < -180.0) {
            lParam = PUN(uint,(float)(PUN(float,lParam) - -360.0));
          }
        }
        else {
          lParam = PUN(uint,(float)(PUN(float,lParam) - 360.0));
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
          if (PUN(float,lParam) <= 360.0) {
            if (PUN(float,lParam) < -180.0) {
              lParam = PUN(uint,(float)(PUN(float,lParam) - -360.0));
            }
          }
          else {
            lParam = PUN(uint,(float)(PUN(float,lParam) - 360.0));
          }
          LightEd_SetDlgFloat((int)g_hLightEdDialog,0x3f4,PUN(float,lParam),1);
          return 1;
        }
        lParam = PUN(uint,(float)((float)(&UINT_008d1740)[g_nLightEdSelected * 5] - g_flLightEdAngleStep));
        if (PUN(float,lParam) <= 360.0) {
          if (PUN(float,lParam) < -180.0) {
            lParam = PUN(uint,(float)(PUN(float,lParam) - -360.0));
          }
        }
        else {
          lParam = PUN(uint,(float)(PUN(float,lParam) - 360.0));
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
          if (PUN(float,lParam) <= 360.0) {
            if (PUN(float,lParam) < -180.0) {
              lParam = PUN(uint,(float)(PUN(float,lParam) - -360.0));
            }
          }
          else {
            lParam = PUN(uint,(float)(PUN(float,lParam) - 360.0));
          }
          LightEd_SetDlgFloat((int)g_hLightEdDialog,0x3f5,PUN(float,lParam),1);
          return 1;
        }
        lParam = PUN(uint,(float)((float)(&UINT_008d173c)[g_nLightEdSelected * 5] + g_flLightEdAngleStep));
        if (PUN(float,lParam) <= 360.0) {
          if (PUN(float,lParam) < -180.0) {
            lParam = PUN(uint,(float)(PUN(float,lParam) - -360.0));
          }
        }
        else {
          lParam = PUN(uint,(float)(PUN(float,lParam) - 360.0));
        }
        local_18 = PUN(float,lParam);
        iVar2 = 0x3f4;
        goto LAB_004c041f;
      }
      break;
    case 0x68:
      if (uVar3 != 0) {
        lParam = PUN(uint,(float)((float)(&UINT_008d1738)[g_nLightEdSelected * 5] - g_flLightEdAngleStep));
        if (PUN(float,lParam) <= 360.0) {
          if (PUN(float,lParam) < -180.0) {
            lParam = PUN(uint,(float)(PUN(float,lParam) - -360.0));
          }
        }
        else {
          lParam = PUN(uint,(float)(PUN(float,lParam) - 360.0));
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
#undef local_18

#endif

