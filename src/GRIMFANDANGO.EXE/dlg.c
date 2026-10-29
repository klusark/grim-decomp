/* GRIMFANDANGO.EXE :: dlg.c
 * functions 0x00488010 .. 0x004886f0 (5 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00488010  Dlg_MakeItemTemplate ---- */
/* Builds a DLGITEMTEMPLATE (style, x, y, w, h, id, text, class) in a malloc'd block, size returned
   through the last argument */

undefined4 *
Dlg_MakeItemTemplate
          (undefined4 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
          undefined2 param_5,undefined2 param_6,int param_7,int param_8,uint *param_9)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *a5;
  undefined4 *puVar4;
  uint uVar5;
  uint uVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  
  uVar1 = CONCAT22(param_3,param_2);
  uVar2 = CONCAT22(param_5,param_4);
  if (param_8 == 0) {
    PIECE(param_2,0,4) = 2;
    PIECE(param_4,0,4) = (undefined4 *)malloc(2);
    *(undefined2 *)PIECE(param_4,0,4) = 0;
  }
  else {
    iVar3 = MultiByteToWideChar(0,1,param_8,-1,0,0);
    PIECE(param_2,0,4) = iVar3 * 2;
    PIECE(param_4,0,4) = (undefined4 *)malloc(PIECE(param_2,0,4));
    MultiByteToWideChar(0,1,param_8,-1,(int)PIECE(param_4,0,4),iVar3);
  }
  if (param_7 == 0) {
    PIECE(param_3,0,4) = 2;
    a5 = (undefined4 *)malloc(2);
    *(undefined2 *)a5 = 0;
  }
  else {
    iVar3 = MultiByteToWideChar(0,1,param_7,-1,0,0);
    PIECE(param_3,0,4) = iVar3 * 2;
    a5 = (undefined4 *)malloc(PIECE(param_3,0,4));
    MultiByteToWideChar(0,1,param_7,-1,(int)a5,iVar3);
  }
  uVar6 = PIECE(param_2,0,4) + 0x13 + PIECE(param_3,0,4);
  *param_9 = uVar6;
  if ((uVar6 & 3) != 0) {
    do {
      *param_9 = *param_9 + 1;
    } while ((*param_9 & 3) != 0);
  }
  puVar4 = (undefined4 *)malloc(*param_9);
  uVar6 = *param_9;
  puVar7 = puVar4;
  for (uVar5 = uVar6 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined1 *)puVar7 = 0;
    puVar7 = (undefined4 *)((int)puVar7 + 1);
  }
  *puVar4 = param_1;
  puVar4[1] = 0;
  puVar4[2] = uVar1;
  puVar4[3] = uVar2;
  *(undefined2 *)(puVar4 + 4) = param_6;
  puVar7 = PIECE(param_4,0,4);
  puVar8 = (undefined4 *)((int)puVar4 + 0x12);
  for (uVar6 = PIECE(param_2,0,4) >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *puVar8 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar8 = puVar8 + 1;
  }
  for (uVar6 = PIECE(param_2,0,4) & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined1 *)puVar8 = *(undefined1 *)puVar7;
    puVar7 = (undefined4 *)((int)puVar7 + 1);
    puVar8 = (undefined4 *)((int)puVar8 + 1);
  }
  puVar7 = a5;
  puVar8 = (undefined4 *)(PIECE(param_2,0,4) + (int)puVar4 + 0x12);
  for (uVar6 = PIECE(param_3,0,4) >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *puVar8 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar8 = puVar8 + 1;
  }
  for (PIECE(param_3,0,4) = PIECE(param_3,0,4) & 3; PIECE(param_3,0,4) != 0; PIECE(param_3,0,4) = PIECE(param_3,0,4) - 1) {
    *(undefined1 *)puVar8 = *(undefined1 *)puVar7;
    puVar7 = (undefined4 *)((int)puVar7 + 1);
    puVar8 = (undefined4 *)((int)puVar8 + 1);
  }
  free(a5);
  free(PIECE(param_4,0,4));
  return puVar4;
}

/* ---- 0x004881a0  Dlg_MakeDialogTemplate ---- */
/* Builds a DLGTEMPLATE header (style, item count, x, y, w, h, title, font, point size) */

uint * Dlg_MakeDialogTemplate
                 (undefined4 *param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
                 undefined2 param_5,undefined2 param_6,int param_7,int param_8,undefined2 param_9,
                 uint *param_10)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  uint uVar2;
  int iVar3;
  uint *puVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  undefined2 *puVar8;
  undefined4 *puVar9;
  uint *puVar10;
  undefined4 *puVar11;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  
  local_14 = (uint)param_1;
  if (param_8 != 0) {
    local_14 = (uint)param_1 | 0x40;
  }
  uVar7 = CONCAT22(param_3,param_2);
  uVar2 = CONCAT22(param_5,param_4);
  if (param_7 == 0) {
    PIECE(param_2,0,4) = 2;
    PIECE(param_4,0,4) = (undefined4 *)malloc(2);
    *(undefined2 *)PIECE(param_4,0,4) = 0;
  }
  else {
    iVar3 = MultiByteToWideChar(0,1,param_7,-1,0,0);
    PIECE(param_2,0,4) = iVar3 * 2;
    PIECE(param_4,0,4) = (undefined4 *)malloc(PIECE(param_2,0,4));
    MultiByteToWideChar(0,1,param_7,-1,(int)PIECE(param_4,0,4),iVar3);
  }
  if (param_8 == 0) {
    PIECE(param_3,0,4) = 0;
    param_1 = (undefined4 *)0x0;
    param_5 = 0;
  }
  else {
    iVar3 = MultiByteToWideChar(0,1,param_8,-1,0,0);
    PIECE(param_3,0,4) = iVar3 * 2;
    param_1 = (undefined4 *)malloc(PIECE(param_3,0,4));
    MultiByteToWideChar(0,1,param_8,-1,(int)param_1,iVar3);
    param_5 = param_9;
  }
  *param_10 = PIECE(param_2,0,4) + 0x16;
  if (param_8 != 0) {
    *param_10 = PIECE(param_3,0,4) + 2 + PIECE(param_2,0,4) + 0x16;
  }
  bVar1 = (byte)*param_10;
  while ((bVar1 & 3) != 0) {
    *param_10 = *param_10 + 1;
    bVar1 = (byte)*param_10;
  }
  puVar4 = (uint *)malloc(*param_10);
  uVar6 = *param_10;
  puVar10 = puVar4;
  for (uVar5 = uVar6 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *puVar10 = 0;
    puVar10 = puVar10 + 1;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined1 *)puVar10 = 0;
    puVar10 = (uint *)((int)puVar10 + 1);
  }
  *puVar4 = local_14;
  puVar4[1] = 0;
  puVar4[2] = uVar7;
  puVar4[3] = uVar2;
  *(undefined2 *)(puVar4 + 4) = param_6;
  *(undefined2 *)((int)puVar4 + 0x12) = 0;
  *(undefined2 *)(puVar4 + 5) = 0;
  puVar9 = PIECE(param_4,0,4);
  puVar11 = (undefined4 *)((int)puVar4 + 0x16);
  for (uVar7 = PIECE(param_2,0,4) >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *puVar11 = *puVar9;
    puVar9 = puVar9 + 1;
    puVar11 = puVar11 + 1;
  }
  for (uVar7 = PIECE(param_2,0,4) & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined1 *)puVar11 = *(undefined1 *)puVar9;
    puVar9 = (undefined4 *)((int)puVar9 + 1);
    puVar11 = (undefined4 *)((int)puVar11 + 1);
  }
  free(PIECE(param_4,0,4));
  if (param_8 != 0) {
    puVar8 = (undefined2 *)((int)puVar4 + 0x16 + PIECE(param_2,0,4));
    *puVar8 = param_5;
    puVar9 = param_1;
    puVar11 = (undefined4 *)(puVar8 + 1);
    for (uVar7 = PIECE(param_3,0,4) >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *puVar11 = *puVar9;
      puVar9 = puVar9 + 1;
      puVar11 = puVar11 + 1;
    }
    for (PIECE(param_3,0,4) = PIECE(param_3,0,4) & 3; PIECE(param_3,0,4) != 0; PIECE(param_3,0,4) = PIECE(param_3,0,4) - 1) {
      *(undefined1 *)puVar11 = *(undefined1 *)puVar9;
      puVar9 = (undefined4 *)((int)puVar9 + 1);
      puVar11 = (undefined4 *)((int)puVar11 + 1);
    }
    free(param_1);
  }
  return puVar4;
}
#undef local_14


/* ---- 0x00488370  FUN_00488370 ---- */
undefined4 __stdcall FUN_00488370(int a1,int a2,int a3,int a4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (a2 == 0x110) {
    if (0 < DAT_008c9854) {
      iVar2 = 0;
      iVar3 = 0x450;
      do {
        SetDlgItemInt(a1,iVar3 + -100,*(int *)(DAT_008c9850 + iVar2),1);
        SendDlgItemMessageA(a1,iVar3,0x465,0,0x7f);
        iVar2 = iVar2 + 4;
        iVar1 = iVar3 + -0x44f;
        iVar3 = iVar3 + 1;
      } while (iVar1 < DAT_008c9854);
    }
  }
  else if (a2 == 0x111) {
    if ((a3 & 0xffffU) == 1) {
      iVar3 = 0;
      if (0 < DAT_008c9854) {
        do {
          iVar2 = GetDlgItemInt(a1,iVar3 + 0x3ec,0,1);
          iVar3 = iVar3 + 1;
          *(int *)(DAT_008c9850 + -4 + iVar3 * 4) = iVar2;
        } while (iVar3 < DAT_008c9854);
      }
      EndDialog(a1,1);
      return 1;
    }
    if ((a3 & 0xffffU) == 2) {
      EndDialog(a1,2);
      return 1;
    }
  }
  return 0;
}

/* ---- 0x00488460  FUN_00488460 ---- */
undefined4 __stdcall FUN_00488460(int a1,int a2,int a3,int a4)

{
  unsigned char _frame[0x70] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined4 *puVar7;
  int iVar8;
  char *pcVar9;
  #define local_58 (*(undefined4 *)(_frame + (0x70 - 0x58)))
  #define local_54 (*(int *)(_frame + (0x70 - 0x54)))
  #define local_48 (*(undefined4 *)(_frame + (0x70 - 0x48)))
  #define local_44 (*(uint *)(_frame + (0x70 - 0x44)))
  #define local_30 (*(int (*)[6])(_frame + (0x70 - 0x30)))
  #define local_18 (*(int *)(_frame + (0x70 - 0x18)))
  
  if (a2 == 0x110) {
    uVar6 = 0;
    DAT_008c9828 = 0;
    puVar7 = DAT_004e813c;
    iVar2 = DAT_004e8140;
    if (0 < DAT_004e8140) {
      do {
        uVar5 = 0xffffffff;
        pcVar9 = (char *)*puVar7;
        do {
          if (uVar5 == 0) break;
          uVar5 = uVar5 - 1;
          cVar1 = *pcVar9;
          pcVar9 = pcVar9 + 1;
        } while (cVar1 != '\0');
        if (uVar6 <= ~uVar5) {
          uVar6 = 0xffffffff;
          pcVar9 = (char *)*puVar7;
          do {
            if (uVar6 == 0) break;
            uVar6 = uVar6 - 1;
            cVar1 = *pcVar9;
            pcVar9 = pcVar9 + 1;
          } while (cVar1 != '\0');
          uVar6 = ~uVar6;
          DAT_008c9828 = uVar6;
        }
        iVar2 = iVar2 + -1;
        puVar7 = puVar7 + 1;
      } while (iVar2 != 0);
    }
    DAT_008c982c = malloc(uVar6);
    if (DAT_004e8138 != 0) {
      SendMessageA(a1,0xc,0,DAT_004e8138);
    }
    iVar3 = GetDlgItem(a1,0x3ea);
    iVar8 = 0;
    local_30[0] = -0x10000;
    local_30[1] = 0xffff0002;
    iVar2 = 0;
    if (0 < DAT_004e8140) {
      do {
        iVar4 = strpbrk_or_strspn(DAT_004e813c[iVar8],&DAT_004e81c4);
        if (iVar2 < iVar4) {
          local_30[0] = a1;
        }
        if (iVar4 < iVar2) {
          iVar2 = iVar2 - iVar4;
          do {
            local_30[0] = SendMessageA(iVar3,0x110a,3,local_30[0]);
            iVar2 = iVar2 + -1;
          } while (iVar2 != 0);
        }
        local_18 = DAT_004e813c[iVar8] + iVar4;
        local_30[2] = 1;
        a1 = SendMessageA(iVar3,0x1100,0,(int)local_30);
        iVar8 = iVar8 + 1;
        iVar2 = iVar4;
      } while (iVar8 < DAT_004e8140);
    }
    SetFocus(iVar3);
  }
  else if (a2 == 0x111) {
    if ((a3 & 0xffffU) == 1) {
      iVar2 = GetDlgItem(a1,0x3ea);
      local_54 = SendMessageA(iVar2,0x110a,9,0);
      if (local_54 == 0) {
        Plat_MessageBox(s_Not_so_fast__004e81c8,s_No_item_was_picked__004e81d8,0);
        return 1;
      }
      local_48 = DAT_008c982c;
      local_44 = DAT_008c9828;
      local_58 = 0x11;
      SendMessageA(iVar2,0x110c,0,(int)&local_58);
      iVar2 = 0;
      if (0 < DAT_004e8140) {
        do {
          iVar3 = String_ContainsSubstring(DAT_004e813c[iVar2],DAT_008c982c);
          if (iVar3 != 0) break;
          iVar2 = iVar2 + 1;
        } while (iVar2 < DAT_004e8140);
      }
      DAT_004e8144 = iVar2;
      iVar2 = GetDlgItem(a1,0x3eb);
      if (iVar2 != 0) {
        iVar2 = SendMessageA(iVar2,0xf0,0,0);
        DAT_004e8148 = (uint)(iVar2 == 1);
      }
      free(DAT_008c982c);
      EndDialog(a1,1);
      return 1;
    }
    if ((a3 & 0xffffU) == 2) {
      free(DAT_008c982c);
      EndDialog(a1,2);
      return 1;
    }
  }
  return 0;
}
#undef local_18
#undef local_30
#undef local_44
#undef local_48
#undef local_54
#undef local_58


/* ---- 0x004886f0  FUN_004886f0 ---- */
undefined4 __stdcall FUN_004886f0(int a1,int a2,int a3,int a4)

{
  undefined1 *puVar1;
  int a1_00;
  
  if (a2 == 0x110) {
    if (DAT_008c9830 != 0) {
      SendMessageA(a1,0xc,0,DAT_008c9830);
    }
    puVar1 = DAT_008c9834;
    if (DAT_008c9834 == (undefined1 *)0x0) {
      puVar1 = &DAT_004f5a98;
    }
    SetDlgItemTextA(a1,0x3e9,(int)puVar1);
    if (1 < DAT_008c983c) {
      SendDlgItemMessageA(a1,1000,0xc5,DAT_008c983c + -1,0);
    }
    puVar1 = DAT_008c9840;
    if (DAT_008c9840 == (undefined1 *)0x0) {
      puVar1 = &DAT_004f5a98;
    }
    SetDlgItemTextA(a1,1000,(int)puVar1);
    SendDlgItemMessageA(a1,1000,0xb1,0,-1);
    a1_00 = GetDlgItem(a1,1000);
    SetFocus(a1_00);
  }
  else if (a2 == 0x111) {
    if ((a3 & 0xffffU) == 1) {
      GetDlgItemTextA(a1,1000,DAT_008c9838,DAT_008c983c + -1);
      EndDialog(a1,1);
      return 1;
    }
    if ((a3 & 0xffffU) == 2) {
      EndDialog(a1,2);
      return 1;
    }
  }
  return 0;
}
