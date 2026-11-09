/* IMUSE.DLL :: imuse.c
 * functions 0x10001000 .. 0x1000be80 (115 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10001000  Im_VimaDecodeBlock ---- */
/* Compressed (VIMA-style ADPCM) block decoder using the step/index tables; identity inferred from
   structure */

void __cdecl
Im_VimaDecodeBlock(ushort *param_1,uint param_2,undefined4 *param_3,undefined4 *param_4,
                  undefined4 *param_5)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte *pbVar1;
  ushort *puVar2;
  byte bVar3;
  ushort uVar4;
  ushort uVar5;
  int iVar6;
  uint uVar7;
  ushort *puVar8;
  ushort *puVar9;
  undefined4 uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  int iVar16;
  ushort *puVar17;
  int iVar18;
  byte *pbVar19;
  int iVar20;
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_24 = 0;
  local_14 = 0;
  local_10 = 0;
  iVar20 = (byte)*param_1 - 0x80;
  iVar6 = (param_2 >> 1) - 1;
  iVar16 = iVar20;
  puVar17 = param_1;
  for (iVar18 = iVar6; iVar18 != 0; iVar18 = iVar18 + -1) {
    puVar17 = (ushort *)((int)puVar17 + 1);
    uVar7 = (*(byte *)puVar17 - 0x80) - iVar16;
    uVar11 = (int)uVar7 >> 0x1f;
    local_20 = local_20 + ((uVar7 ^ uVar11) - uVar11) * 0x100;
    iVar16 = *(byte *)puVar17 - 0x80;
  }
  iVar18 = (param_2 >> 3) - 2;
  if (iVar18 != 0) {
    pbVar19 = (byte *)((int)param_1 + 3);
    iVar16 = *(byte *)((int)param_1 + 1) - 0x80;
    do {
      pbVar1 = pbVar19 + -1;
      bVar3 = *pbVar19;
      uVar7 = (*pbVar1 - 0x80) - iVar20;
      pbVar19 = pbVar19 + 2;
      uVar12 = (int)uVar7 >> 0x1f;
      uVar11 = (bVar3 - 0x80) - iVar16;
      uVar13 = (int)uVar11 >> 0x1f;
      local_1c = local_1c + (((uVar7 ^ uVar12) - uVar12) + ((uVar11 ^ uVar13) - uVar13)) * 0x100;
      iVar18 = iVar18 + -1;
      iVar20 = *pbVar1 - 0x80;
      iVar16 = bVar3 - 0x80;
    } while (iVar18 != 0);
  }
  uVar4 = *param_1;
  iVar18 = (int)(short)uVar4;
  puVar17 = param_1;
  for (iVar20 = iVar6; iVar20 != 0; iVar20 = iVar20 + -1) {
    puVar17 = puVar17 + 1;
    uVar7 = (short)*puVar17 - iVar18;
    uVar11 = (int)uVar7 >> 0x1f;
    local_18 = local_18 + ((uVar7 ^ uVar11) - uVar11);
    iVar18 = (int)(short)*puVar17;
  }
  uVar11 = (uint)(uVar4 >> 8) | (uint)(byte)uVar4 << 8;
  uVar7 = uVar11;
  puVar17 = param_1;
  for (; iVar6 != 0; iVar6 = iVar6 + -1) {
    puVar17 = puVar17 + 1;
    uVar12 = (uint)(byte)*puVar17 << 8 | (uint)(*puVar17 >> 8);
    uVar7 = uVar12 - uVar7;
    uVar13 = (int)uVar7 >> 0x1f;
    local_24 = local_24 + ((uVar7 ^ uVar13) - uVar13);
    uVar7 = uVar12;
  }
  uVar5 = param_1[1];
  puVar8 = (ushort *)(param_2 >> 2);
  puVar17 = puVar8 + -1;
  if (puVar17 != (ushort *)0x0) {
    puVar9 = param_1 + 3;
    iVar20 = (int)(short)uVar4;
    iVar18 = (int)(short)uVar5;
    do {
      puVar2 = puVar9 + -1;
      uVar4 = *puVar9;
      puVar9 = puVar9 + 2;
      uVar7 = (short)*puVar2 - iVar20;
      uVar13 = (int)uVar7 >> 0x1f;
      uVar12 = (short)uVar4 - iVar18;
      uVar14 = (int)uVar12 >> 0x1f;
      local_14 = ((uVar12 ^ uVar14) - uVar14) + local_14 + ((uVar7 ^ uVar13) - uVar13);
      puVar17 = (ushort *)((int)puVar17 + -1);
      iVar20 = (int)(short)*puVar2;
      iVar18 = (int)(short)uVar4;
    } while (puVar17 != (ushort *)0x0);
  }
  if (puVar8 != (ushort *)0x0) {
    puVar17 = param_1 + 3;
    uVar7 = (uint)(uVar5 >> 8) | (uVar5 & 0xff) << 8;
    param_1 = puVar8;
    do {
      uVar14 = (uint)(byte)puVar17[-1] << 8 | (uint)(puVar17[-1] >> 8);
      uVar15 = (uint)(byte)*puVar17 << 8 | (uint)(*puVar17 >> 8);
      uVar11 = uVar14 - uVar11;
      uVar12 = (int)uVar11 >> 0x1f;
      uVar7 = uVar15 - uVar7;
      uVar13 = (int)uVar7 >> 0x1f;
      local_10 = ((uVar7 ^ uVar13) - uVar13) + local_10 + ((uVar11 ^ uVar12) - uVar12);
      param_1 = (ushort *)((int)param_1 + -1);
      puVar17 = puVar17 + 2;
      uVar11 = uVar14;
      uVar7 = uVar15;
    } while (param_1 != (ushort *)0x0);
  }
  uVar10 = 3;
  if (local_20 < local_24) {
    uVar10 = 0;
    local_24 = local_20;
  }
  if (local_1c < local_24) {
    uVar10 = 1;
    local_24 = local_1c;
  }
  if (local_18 < local_24) {
    uVar10 = 2;
    local_24 = local_18;
  }
  if (local_14 < local_24) {
    uVar10 = 4;
    local_24 = local_14;
  }
  if (local_10 < local_24) {
    uVar10 = 5;
  }
  switch(uVar10) {
  case 0:
    if (param_3 != (undefined4 *)0x0) {
      *param_3 = 8;
    }
    if (param_4 != (undefined4 *)0x0) {
      *param_4 = 1;
    }
    break;
  case 1:
    if (param_3 != (undefined4 *)0x0) {
      *param_3 = 8;
    }
    goto joined_r0x10001355;
  case 2:
    if (param_3 != (undefined4 *)0x0) {
      *param_3 = 0x10;
    }
    if (param_4 != (undefined4 *)0x0) {
      *param_4 = 1;
    }
    break;
  case 3:
    if (param_3 != (undefined4 *)0x0) {
      *param_3 = 0x10;
    }
    if (param_4 != (undefined4 *)0x0) {
      *param_4 = 1;
    }
    if (param_5 == (undefined4 *)0x0) {
      return;
    }
    *param_5 = 0;
    return;
  case 4:
    if (param_3 != (undefined4 *)0x0) {
      *param_3 = 0x10;
    }
joined_r0x10001355:
    if (param_4 != (undefined4 *)0x0) {
      *param_4 = 2;
    }
    break;
  case 5:
    if (param_3 != (undefined4 *)0x0) {
      *param_3 = 0x10;
    }
    if (param_4 != (undefined4 *)0x0) {
      *param_4 = 2;
    }
    if (param_5 != (undefined4 *)0x0) {
      *param_5 = 0;
    }
  default:
    goto switchD_100012ad_default;
  }
  if (param_5 != (undefined4 *)0x0) {
    *param_5 = 1;
    return;
  }
switchD_100012ad_default:
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24


/* ---- 0x100013c0  Im_VimaDecompress ---- */
/* Drives Im_VimaDecodeBlock over a compressed sound chunk */

uint * __cdecl
Im_VimaDecompress(uint *param_1,int *param_2,uint *param_3,uint *param_4,uint *param_5,int *param_6,
                 uint *param_7)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint *puVar5;
  uint *puVar6;
  uint *puVar7;
  char *pcVar8;
  bool bVar9;
  bool bVar10;
  
  if (param_2 != (int *)0x0) {
    *param_2 = 0;
  }
  if (param_1 == (uint *)0x0) {
    return (uint *)0x0;
  }
  iVar3 = 4;
  bVar9 = true;
  puVar6 = param_1;
  pcVar8 = &DAT_10017098;
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    bVar9 = (char)*puVar6 == *pcVar8;
    puVar6 = (uint *)((int)puVar6 + 1);
    pcVar8 = pcVar8 + 1;
  } while (bVar9);
  if (bVar9) {
    uVar2 = (uint)(ushort)((ushort)param_1[1] >> 8) | (uint)(byte)(ushort)param_1[1] << 8;
    uVar1 = *(ushort *)((int)param_1 + uVar2 * 9 + 6);
    param_1 = (uint *)((int)param_1 + ((uint)(byte)uVar1 << 8 | (uint)(uVar1 >> 8)) + uVar2 * 9 + 8)
    ;
  }
  iVar3 = 4;
  bVar10 = true;
  puVar6 = param_1;
  pcVar8 = &DAT_10017090;
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    bVar10 = (char)*puVar6 == *pcVar8;
    puVar6 = (uint *)((int)puVar6 + 1);
    pcVar8 = pcVar8 + 1;
  } while (bVar10);
  if (bVar10) {
    puVar6 = (uint *)(param_1[1] + 8 + (int)param_1);
    iVar3 = 8;
    bVar10 = true;
    puVar5 = param_1 + 2;
    pcVar8 = &DAT_10017084;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      bVar10 = (char)*puVar5 == *pcVar8;
      puVar5 = (uint *)((int)puVar5 + 1);
      pcVar8 = pcVar8 + 1;
    } while (bVar10);
    if (!bVar10) {
      return (uint *)0x0;
    }
    if ((short)param_1[5] != 1) {
      return (uint *)0x0;
    }
    if (param_2 != (int *)0x0) {
      *param_2 = bVar9 + 5;
    }
    uVar2 = param_1[4];
    puVar5 = param_1 + 4;
    if (param_3 != (uint *)0x0) {
      *param_3 = param_1[6];
    }
    if (param_4 != (uint *)0x0) {
      *param_4 = (int)*(short *)((int)param_1 + 0x22);
    }
    if (param_5 != (uint *)0x0) {
      *param_5 = (int)*(short *)((int)param_1 + 0x16);
    }
    if (param_6 != (int *)0x0) {
      *param_6 = 1;
    }
    do {
      puVar5 = (uint *)((int)puVar5 + uVar2 + 8);
      uVar2 = *puVar5;
      if (puVar6 <= puVar5) {
        return (uint *)0x0;
      }
      iVar3 = 4;
      bVar9 = true;
      puVar7 = puVar5 + -1;
      pcVar8 = (char *)&DAT_1001707c;
      do {
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        bVar9 = (char)*puVar7 == *pcVar8;
        puVar7 = (uint *)((int)puVar7 + 1);
        pcVar8 = pcVar8 + 1;
      } while (bVar9);
    } while (!bVar9);
    if (puVar5 < puVar6) {
      if (param_7 != (uint *)0x0) {
        *param_7 = uVar2;
      }
      return puVar5 + 1;
    }
  }
  else {
    iVar3 = 4;
    bVar10 = true;
    puVar6 = param_1;
    pcVar8 = (char *)&DAT_10017074;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      bVar10 = (char)*puVar6 == *pcVar8;
      puVar6 = (uint *)((int)puVar6 + 1);
      pcVar8 = pcVar8 + 1;
    } while (bVar10);
    if (bVar10) {
      uVar2 = param_1[3];
      uVar2 = (uVar2 & 0xff00 | uVar2 << 0x10) << 8 | (uVar2 & 0xff0000 | uVar2 >> 0x10) >> 8;
      iVar3 = 4;
      bVar10 = true;
      puVar6 = param_1 + 4;
      pcVar8 = (char *)&DAT_1001706c;
      do {
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        bVar10 = (char)*puVar6 == *pcVar8;
        puVar6 = (uint *)((int)puVar6 + 1);
        pcVar8 = pcVar8 + 1;
      } while (bVar10);
      if (bVar10) {
        if (param_2 != (int *)0x0) {
          *param_2 = bVar9 + 3;
        }
        puVar6 = param_1 + 8;
        if (param_4 != (uint *)0x0) {
          uVar4 = *puVar6;
          *param_4 = (uVar4 & 0xff00 | uVar4 << 0x10) << 8 | (uVar4 & 0xff0000 | uVar4 >> 0x10) >> 8
          ;
        }
        if (param_3 != (uint *)0x0) {
          uVar4 = param_1[9];
          *param_3 = (uVar4 & 0xff00 | uVar4 << 0x10) << 8 | (uVar4 >> 0x10 | uVar4 & 0xff0000) >> 8
          ;
        }
        if (param_5 != (uint *)0x0) {
          uVar4 = param_1[10];
          *param_5 = (uVar4 & 0xff00 | uVar4 << 0x10) << 8 | (uVar4 & 0xff0000 | uVar4 >> 0x10) >> 8
          ;
        }
        if (param_6 != (int *)0x0) {
          *param_6 = 0;
        }
        if (param_7 != (uint *)0x0) {
          uVar4 = *(uint *)((uVar2 - 0xc) + (int)puVar6);
          *param_7 = (uVar4 & 0xff00 | uVar4 << 0x10) << 8 | (uVar4 & 0xff0000 | uVar4 >> 0x10) >> 8
          ;
        }
        return (uint *)((uVar2 - 8) + (int)puVar6);
      }
      return (uint *)0x0;
    }
    if (bVar9) {
      return (uint *)0x0;
    }
    iVar3 = 4;
    bVar9 = true;
    puVar6 = param_1;
    pcVar8 = &DAT_10017064;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      bVar9 = (char)*puVar6 == *pcVar8;
      puVar6 = (uint *)((int)puVar6 + 1);
      pcVar8 = pcVar8 + 1;
    } while (bVar9);
    if (bVar9) {
      uVar2 = param_1[1];
      bVar9 = true;
      puVar6 = (uint *)(((uVar2 & 0xff00 | uVar2 << 0x10) << 8 |
                        (uVar2 >> 0x10 | uVar2 & 0xff0000) >> 8) + 8 + (int)param_1);
      iVar3 = 8;
      puVar5 = param_1 + 2;
      pcVar8 = (char *)&DAT_10017058;
      do {
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        bVar9 = (char)*puVar5 == *pcVar8;
        puVar5 = (uint *)((int)puVar5 + 1);
        pcVar8 = pcVar8 + 1;
      } while (bVar9);
      if (!bVar9) {
        return (uint *)0x0;
      }
      if (param_2 != (int *)0x0) {
        *param_2 = 7;
      }
      uVar2 = param_1[4];
      puVar5 = param_1 + 4;
      uVar2 = (uVar2 & 0xff00 | uVar2 << 0x10) << 8 | (uVar2 & 0xff0000 | uVar2 >> 0x10) >> 8;
      if (param_3 != (uint *)0x0) {
        if (*(char *)((int)param_1 + 0x1d) == '\x0e') {
          uVar4 = 0xac44;
        }
        else {
          uVar4 = (-(uint)(*(char *)((int)param_1 + 0x1d) != '\f') & 0x2b11) + 0x2b11;
        }
        *param_3 = uVar4;
      }
      if (param_4 != (uint *)0x0) {
        *param_4 = (uint)*(byte *)((int)param_1 + 0x1b);
      }
      if (param_5 != (uint *)0x0) {
        *param_5 = (uint)*(byte *)((int)param_1 + 0x15);
      }
      if (param_6 != (int *)0x0) {
        *param_6 = 0;
      }
      do {
        puVar5 = (uint *)((int)puVar5 + uVar2 + 8);
        uVar2 = *puVar5;
        uVar2 = (uVar2 & 0xff00 | uVar2 << 0x10) << 8 | (uVar2 & 0xff0000 | uVar2 >> 0x10) >> 8;
        if (puVar6 <= puVar5) {
          return (uint *)0x0;
        }
        iVar3 = 4;
        bVar9 = true;
        puVar7 = puVar5 + -1;
        pcVar8 = (char *)&DAT_10017050;
        do {
          if (iVar3 == 0) break;
          iVar3 = iVar3 + -1;
          bVar9 = (char)*puVar7 == *pcVar8;
          puVar7 = (uint *)((int)puVar7 + 1);
          pcVar8 = pcVar8 + 1;
        } while (bVar9);
      } while (!bVar9);
      if (puVar5 < puVar6) {
        if (param_7 != (uint *)0x0) {
          *param_7 = uVar2 - 8;
        }
        return puVar5 + 3;
      }
    }
    else {
      Im_VimaDecodeBlock((ushort *)param_1,0x2000,param_4,param_5,param_6);
      if ((param_4 == (uint *)0x0) || (*param_4 == 0x10)) {
        if ((param_6 != (int *)0x0) &&
           ((param_2 != (int *)0x0 && (*param_2 = 2 - (uint)(*param_6 != 0), *param_3 != 0)))) {
          *param_3 = 0xac44;
        }
        return param_1;
      }
    }
  }
  return (uint *)0x0;
}

/* ---- 0x100017e0  Im_DecodeSoundBlock ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Unidentified function of compressed audio decoding (VIMA/ADPCM style tables) - module name
   inferred */

int __cdecl
Im_DecodeSoundBlock(undefined4 *param_1,int param_2,uint param_3,uint param_4,uint param_5,
                   uint param_6)

{
  uint uVar1;
  undefined4 *puVar2;
  uint uVar3;
  
  if (param_2 == 3) {
    *param_1 = DAT_10017074;
    uVar1 = param_6 + 0x50;
    param_1[1] = (uVar1 & 0xff00 | uVar1 * 0x10000) << 8 | (uVar1 & 0xff0000 | uVar1 >> 0x10) >> 8;
    param_1[2] = DAT_100170b8;
    param_1[3] = 0x38000000;
    param_1[4] = DAT_1001706c;
    param_1[5] = 0x14000000;
    param_1[6] = 0x50000000;
    param_1[7] = 0;
    param_1[8] = (param_4 & 0xff00 | param_4 << 0x10) << 8 |
                 (param_4 & 0xff0000 | param_4 >> 0x10) >> 8;
    param_1[9] = (param_3 & 0xff00 | param_3 << 0x10) << 8 |
                 (param_3 & 0xff0000 | param_3 >> 0x10) >> 8;
    param_1[10] = (param_5 & 0xff00 | param_5 << 0x10) << 8 |
                  (param_5 & 0xff0000 | param_5 >> 0x10) >> 8;
    param_1[0xb] = DAT_100170b0;
    param_1[0xc] = 0x8000000;
    param_1[0xd] = 0x50000000;
    uVar3 = (param_6 & 0xff00 | param_6 << 0x10) << 8 | (param_6 & 0xff0000 | param_6 >> 0x10) >> 8;
    param_1[0xe] = uVar3;
    param_1[0xf] = DAT_100170a8;
    param_1[0x10] = 0x4000000;
    param_1[0x11] =
         (uVar1 & 0xff00 | uVar1 * 0x10000) << 8 | (uVar1 & 0xff0000 | uVar1 >> 0x10) >> 8;
    param_1[0x12] = DAT_100170a0;
    param_1[0x13] = uVar3;
    puVar2 = param_1 + 0x14;
  }
  else {
    if (param_2 == 5) {
      *param_1 = _DAT_10017090;
      param_1[1] = param_6 + 0x24;
      param_1[2] = _DAT_10017084;
      param_1[3] = DAT_10017088;
      param_1[4] = 0x10;
      *(undefined2 *)(param_1 + 5) = 1;
      *(short *)((int)param_1 + 0x16) = (short)param_5;
      param_1[6] = param_3;
      param_1[7] = param_5 * param_3 * (param_4 >> 3);
      *(short *)(param_1 + 8) = (short)param_5 * (short)(param_4 >> 3);
      *(short *)((int)param_1 + 0x22) = (short)param_4;
      param_1[9] = DAT_1001707c;
      param_1[10] = param_6;
      return 0x2c;
    }
    puVar2 = param_1;
    if (param_2 == 7) {
      *param_1 = _DAT_10017064;
      uVar1 = param_6 + 0x36;
      param_1[1] = (uVar1 & 0xff00 | uVar1 * 0x10000) << 8 | (uVar1 & 0xff0000 | uVar1 >> 0x10) >> 8
      ;
      param_1[2] = DAT_10017058;
      param_1[3] = DAT_1001705c;
      param_1[4] = 0x12000000;
      *(ushort *)(param_1 + 5) = CONCAT11((char)param_5,(char)(param_5 >> 8));
      uVar1 = param_6 / ((param_4 >> 3) * param_5);
      puVar2 = param_1 + 7;
      *(uint *)((int)param_1 + 0x16) =
           (uVar1 & 0xff00 | uVar1 << 0x10) << 8 | (uVar1 & 0xff0000 | uVar1 >> 0x10) >> 8;
      *(ushort *)((int)param_1 + 0x1a) = CONCAT11((char)param_4,(char)(param_4 >> 8));
      if (param_3 == 0x2b11) {
        *puVar2 = 0x44ac0c40;
        param_1[8] = 0;
      }
      else if (param_3 == 0xac44) {
        *puVar2 = 0x44ac0e40;
        param_1[8] = 0;
      }
      else {
        *puVar2 = 0x44ac0d40;
        param_1[8] = 0;
      }
      *(undefined2 *)(param_1 + 9) = 0;
      uVar1 = param_6 + 8;
      *(undefined4 *)((int)param_1 + 0x26) = DAT_10017050;
      *(uint *)((int)param_1 + 0x2a) =
           (uVar1 & 0xff00 | uVar1 * 0x10000) << 8 | (uVar1 & 0xff0000 | uVar1 >> 0x10) >> 8;
      *(undefined4 *)((int)param_1 + 0x2e) = 0;
      *(undefined4 *)((int)param_1 + 0x32) = 0;
      return 0x36;
    }
  }
  return (int)puVar2 - (int)param_1;
}

/* ---- 0x10001ba0  Im_CodecInit ---- */
/* Unidentified function of compressed audio decoding (VIMA/ADPCM style tables) - module name
   inferred */

void __cdecl Im_CodecInit(undefined1 *param_1)

{
  param_1[1] = 0;
  *param_1 = 0;
  *(undefined2 *)(param_1 + 4) = 0;
  *(undefined2 *)(param_1 + 2) = 0;
  return;
}

/* ---- 0x10001bc0  Im_ConvertBlock ---- */
/* Unidentified function of compressed audio decoding (VIMA/ADPCM style tables) - module name
   inferred */

void __cdecl Im_ConvertBlock(byte *param_1,undefined2 *param_2,byte *param_3,uint param_4)

{
  byte bVar1;
  byte *pbVar2;
  uint uVar3;
  
  bVar1 = *param_3;
  uVar3 = 1;
  *param_1 = bVar1;
  if ((char)bVar1 < '\0') {
    *param_1 = ~bVar1;
    uVar3 = 2;
  }
  pbVar2 = param_3 + 3;
  *(ushort *)(param_1 + 2) =
       CONCAT11((char)*(undefined2 *)(param_3 + 1),(char)((ushort)*(undefined2 *)(param_3 + 1) >> 8)
               );
  if (1 < uVar3) {
    param_1[1] = *pbVar2;
    pbVar2 = param_3 + 6;
    *(ushort *)(param_1 + 4) =
         CONCAT11((char)*(undefined2 *)(param_3 + 4),
                  (char)((ushort)*(undefined2 *)(param_3 + 4) >> 8));
  }
  Im_ConvertBlockImpl((short *)param_1,param_2,pbVar2,param_4 / (uVar3 * 2),uVar3,1);
  return;
}

/* ---- 0x10001c30  Im_ConvertBlockImpl ---- */
/* Unidentified function of compressed audio decoding (VIMA/ADPCM style tables) - module name
   inferred */

void __cdecl
Im_ConvertBlockImpl(short *param_1,undefined2 *param_2,byte *param_3,int param_4,uint param_5,
                   int param_6)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  ushort uVar2;
  uint uVar3;
  uint uVar4;
  short sVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  ushort *puVar9;
  short *psVar10;
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(short **)(_frame + (0x40 - 0x20)))
  #define local_1c (*(undefined2 **)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(int *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  
  iVar7 = 0;
  if (DAT_10024dc0 == 0) {
    uVar8 = 0;
    local_20 = &DAT_10022140;
    do {
      puVar9 = &DAT_10015228;
      psVar10 = local_20;
      do {
        uVar2 = *puVar9;
        uVar3 = 0x20;
        sVar5 = 0;
        do {
          if ((uVar8 & uVar3) != 0) {
            sVar5 = sVar5 + uVar2;
          }
          uVar2 = uVar2 >> 1;
          uVar3 = uVar3 >> 1;
        } while (uVar3 != 0);
        *psVar10 = sVar5;
        puVar9 = puVar9 + 1;
        psVar10 = psVar10 + 0x40;
      } while (puVar9 < &DAT_100152da);
      uVar8 = uVar8 + 1;
      local_20 = local_20 + 1;
    } while (local_20 < &DAT_100221c0);
    DAT_10024dc0 = 1;
  }
  if (param_6 == 0) {
    *(undefined1 *)((int)param_1 + 1) = 0;
    *(undefined1 *)param_1 = 0;
    param_1[2] = 0;
    param_1[1] = 0;
  }
  local_24 = (uint)CONCAT11(*param_3,param_3[1]);
  param_3 = param_3 + 2;
  local_14 = 0;
  if (param_5 != 0) {
    local_20 = param_2;
    psVar10 = param_1;
    do {
      psVar10 = psVar10 + 1;
      local_1c = local_20;
      param_6 = (int)*(char *)(local_14 + (int)param_1);
      uVar8 = (uint)*psVar10;
      if (param_4 != 0) {
        local_18 = param_4;
        do {
          bVar1 = (&DAT_100152e0)[param_6];
          iVar7 = iVar7 + (uint)bVar1;
          uVar6 = 1 << (bVar1 - 1 & 0x1f);
          local_8 = (uint)(byte)((char)uVar6 - 1);
          uVar3 = (local_24 & 0xffff) >> (0x10U - (char)iVar7 & 0x1f) & (uVar6 | local_8);
          if (7 < iVar7) {
            local_24 = (local_24 & 0xff) << 8 |
                       CONCAT22((short)((uint)param_3 >> 0x10),(ushort)*param_3);
            param_3 = param_3 + 1;
            iVar7 = iVar7 + -8;
          }
          if ((uVar3 & uVar6) == 0) {
            uVar6 = 0;
          }
          else {
            uVar3 = uVar3 ^ uVar6;
          }
          if (uVar3 == local_8) {
            uVar8 = (int)(short)(local_24 << ((byte)iVar7 & 0x1f)) & 0xffffff00U |
                    (ushort)(CONCAT11((undefined1)local_24,*param_3) >> (8 - (byte)iVar7 & 0x1f)) &
                    0xff;
            local_24 = (uint)CONCAT11(*param_3,param_3[1]);
            param_3 = param_3 + 2;
          }
          else {
            uVar4 = (uint)(ushort)(&DAT_10022140)[uVar3 << (7 - bVar1 & 0x1f) | param_6 << 6];
            if (uVar3 != 0) {
              uVar4 = uVar4 + ((ushort)(&DAT_10015228)[param_6] >> (bVar1 - 1 & 0x1f));
            }
            if (uVar6 != 0) {
              uVar4 = -uVar4;
            }
            uVar8 = uVar8 + uVar4;
            if ((int)uVar8 < -0x8000) {
              uVar8 = 0xffff8000;
            }
            else if (0x7fff < (int)uVar8) {
              uVar8 = 0x7fff;
            }
          }
          *local_1c = (short)uVar8;
          local_1c = local_1c + param_5;
          param_6 = param_6 + *(char *)(*(int *)(&DAT_10017030 + (uint)bVar1 * 4) + uVar3);
          if (param_6 < 0) {
            param_6 = 0;
          }
          else if (0x58 < param_6) {
            param_6 = 0x58;
          }
          local_18 = local_18 + -1;
        } while (local_18 != 0);
      }
      *(undefined1 *)(local_14 + (int)param_1) = (undefined1)param_6;
      *psVar10 = (short)uVar8;
      local_14 = local_14 + 1;
      local_20 = local_20 + 1;
    } while (local_14 < param_5);
  }
  return;
}
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_8


/* ---- 0x10001f10  Im_DispatchInit ---- */
/* iMUSE_Dispatch.c: allocates the dispatch slots */

undefined4 Im_DispatchInit(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  DAT_1002d808 = (**(code **)(DAT_10033510 + 0x20))
                           (DAT_1001e8c4 * DAT_1001e8c0 + DAT_1001e8cc * DAT_1001e8c8 +
                            (DAT_1001e8cc + DAT_1001e8c4) * 4,
                            s_C__grimsrc_libs_iMUSE_Dispatch_c_100170c0,0x41);
  if (DAT_1002d808 == 0) {
    return 0xffffffff;
  }
  DAT_10024dd4 = DAT_1002d808 + DAT_1001e8c4 * DAT_1001e8c0;
  PTR_10025298 = (int *)((DAT_1001e8c0 + 4) * DAT_1001e8c4 + DAT_1002d808 +
                        DAT_1001e8cc * DAT_1001e8c8);
  PTR_10024dc8 = (int *)(DAT_1002d808 + DAT_1001e8cc * DAT_1001e8c8 + DAT_1001e8c4 * DAT_1001e8c0);
  DAT_10024dcc = DAT_1002d808;
  *PTR_10024dc8 = 0;
  *PTR_10025298 = 0;
  puVar2 = &DAT_10024de8;
  for (iVar1 = 300; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  return 0;
}

/* ---- 0x10002260  Im_SwitchStreamImpl ---- */
/* Body of ImSwitchStream (sound, offset, fade, flags) */

undefined4 __cdecl
Im_SwitchStreamImpl(int param_1,undefined4 param_2,uint param_3,uint param_4,uint param_5)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  uint uVar6;
  int *piVar7;
  undefined4 *puVar8;
  
  piVar7 = &DAT_100252a0;
  Im_GuardEnter();
  if (2000 < param_3) {
    param_3 = 2000;
  }
  iVar2 = 0;
  if (0 < DAT_1003350c) {
    do {
      if (((param_1 != 0) && (param_1 == *(int *)(*piVar7 + 0xc))) && (piVar7[0x207] != 0)) break;
      iVar2 = iVar2 + 1;
      piVar7 = piVar7 + 0x215;
    } while (iVar2 < DAT_1003350c);
  }
  if (iVar2 == DAT_1003350c) {
    Im_GuardLeave();
    return 0xffffffff;
  }
  if (piVar7[0x209] != 0) {
    if (piVar7[1] == 0) {
      Im_GuardLeave();
      return 0xffffffff;
    }
    if (piVar7[0x20b] != 0) {
      iMUSE_Dispatch__3640(piVar7[0x20b]);
    }
    uVar3 = ((param_3 * piVar7[2]) / 1000) * piVar7[1] * piVar7[3] >> 3;
    if (*(uint *)(piVar7[0x209] + 0x10) <= uVar3) {
      uVar3 = *(uint *)(piVar7[0x209] + 0x10);
    }
    DAT_10024dd0 = uVar3 - ((piVar7[1] >> 3) * piVar7[3] - 1U & uVar3);
    iVar2 = iMUSE_Dispatch__35a0(&DAT_10024dd0);
    piVar7[0x20b] = iVar2;
    uVar3 = DAT_10024dd0;
    if (iVar2 != 0) {
      piVar7[0x20e] = piVar7[1];
      piVar7[0x210] = piVar7[3];
      piVar7[0x20c] = 0;
      piVar7[0x211] = param_5 | param_4;
      uVar4 = 0;
      piVar7[0x20d] = 0;
      piVar7[0x20f] = piVar7[2];
      piVar7[0x212] = 0;
      piVar7[0x213] = 0x7f0000;
      piVar7[0x214] = 0;
      if (uVar3 != 0) {
        do {
          uVar4 = uVar3 - uVar4;
          if (0x3fff < uVar4) {
            uVar4 = 0x4000;
          }
          puVar5 = (undefined4 *)iMUSE_stream__a420(piVar7[0x207],uVar4);
          if (puVar5 < (undefined4 *)0x10000) {
            uVar4 = DAT_10024dd0 - piVar7[0x20d];
            puVar5 = (undefined4 *)(piVar7[0x20d] + piVar7[0x20b]);
            for (uVar3 = uVar4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
              *puVar5 = 0;
              puVar5 = puVar5 + 1;
            }
            for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
              *(undefined1 *)puVar5 = 0;
              puVar5 = (undefined4 *)((int)puVar5 + 1);
            }
            piVar7[0x20d] = DAT_10024dd0;
            break;
          }
          puVar8 = (undefined4 *)(piVar7[0x20b] + piVar7[0x20d]);
          for (uVar3 = uVar4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
            *puVar8 = *puVar5;
            puVar5 = puVar5 + 1;
            puVar8 = puVar8 + 1;
          }
          for (uVar6 = uVar4 & 3; uVar3 = DAT_10024dd0, uVar6 != 0; uVar6 = uVar6 - 1) {
            *(undefined1 *)puVar8 = *(undefined1 *)puVar5;
            puVar5 = (undefined4 *)((int)puVar5 + 1);
            puVar8 = (undefined4 *)((int)puVar8 + 1);
          }
          uVar4 = piVar7[0x20d] + uVar4;
          piVar7[0x20d] = uVar4;
        } while (uVar4 < uVar3);
      }
    }
  }
  Im_FadesClearSound(*(int *)(*piVar7 + 0xc),-1);
  Im_ClearTriggerImpl(*(int *)(*piVar7 + 0xc),(byte *)0xffffffff,-1);
  *(undefined4 *)(*piVar7 + 0xc) = param_2;
  uVar3 = Im_FindTrack(piVar7[0x207]);
  iMUSE_stream__a500(piVar7[0x207],uVar3);
  if ((param_5 != 0) && (piVar1 = piVar7 + 0x209, piVar7[0x209] != 0)) {
    iMUSE_stream__a5a0((undefined4 *)piVar7[0x207],param_2,piVar7[5]);
    iVar2 = *(int *)(*piVar1 + 4);
    while (iVar2 != 0) {
      *(undefined4 *)(iVar2 + 8) = 0;
      iMUSE_stream__b7a0((int *)(*piVar1 + 4),*(int **)(*piVar1 + 4));
      iVar2 = *(int *)(*piVar1 + 4);
    }
    *(undefined4 *)(*piVar1 + 0x10) = 0;
    Im_GuardLeave();
    return 0;
  }
  iMUSE_stream__a5a0((undefined4 *)piVar7[0x207],param_2,0);
  piVar1 = piVar7 + 0x209;
  iVar2 = piVar7[0x209];
  while (iVar2 != 0) {
    *(undefined4 *)(iVar2 + 8) = 0;
    iMUSE_stream__b7a0(piVar1,(int *)*piVar1);
    iVar2 = *piVar1;
  }
  *(undefined1 *)(piVar7 + 7) = 0;
  piVar7[6] = 0;
  piVar7[5] = 0;
  iVar2 = Im_DispatchAllocBuffers(piVar7);
  if ((iVar2 != 0) && (iVar2 != -3)) {
    Im_FreeTrack((int *)*piVar7);
    Im_GuardLeave();
    return 0xffffffff;
  }
  Im_GuardLeave();
  return 0;
}

/* ---- 0x10002570  Im_DispatchMixTrack ---- */
/* WARNING: Removing unreachable block (ram,0x10002950) */
/* Pulls decoded data for one track and mixes it (Im_MixSamples) */

void __cdecl Im_DispatchMixTrack(int *param_1,uint param_2,uint param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  short *psVar5;
  uint uVar6;
  uint uVar7;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  piVar1 = (int *)param_1[2];
  if ((piVar1[0x207] != 0) && (piVar1[0x209] != 0)) {
    iMUSE_Dispatch__3130(piVar1);
  }
  if (piVar1[0x20b] != 0) {
    uVar2 = (uint)(piVar1[0x20d] << 3) / (uint)(piVar1[0x20e] * piVar1[0x210]);
    local_8 = piVar1[0x20f] * param_1[0xc] >> 8;
    uVar3 = (param_2 * local_8) / param_3;
    if (uVar2 < uVar3) {
      local_8 = (uVar2 * param_3) / local_8;
      uVar3 = uVar2;
    }
    else {
      local_8 = param_2;
    }
    if (uVar3 != 0) {
      uVar2 = uVar3 * piVar1[0x20e] * piVar1[0x210] >> 3;
      iVar4 = iMUSE_Dispatch__3510(piVar1,uVar2);
      Im_MixSamples((short *)(piVar1[0x20b] + piVar1[0x20c]),uVar3,piVar1[0x20e],piVar1[0x210],
                    piVar1[4],local_8,0,iVar4,param_1[9]);
      iVar4 = piVar1[0x20d];
      piVar1[0x20c] = piVar1[0x20c] + uVar2;
      piVar1[0x20d] = iVar4 - uVar2;
      if (iVar4 - uVar2 != 0) goto LAB_10002693;
    }
    iMUSE_Dispatch__3640(piVar1[0x20b]);
    piVar1[0x20b] = 0;
  }
LAB_10002693:
  local_4 = 0;
  do {
    if (piVar1[6] == 0) {
      DAT_10024de0 = 0;
      iVar4 = Im_DispatchAllocBuffers(piVar1);
      if (iVar4 != 0) {
        if (iVar4 == -1) {
          Im_FreeTrack(param_1);
        }
        if (piVar1[0x20b] == 0) {
          return;
        }
        if (piVar1[0x211] == 0) {
          return;
        }
        piVar1[0x212] = piVar1[0x212] + param_2;
        return;
      }
      if (DAT_10024de0 != 0) {
        uVar2 = (uint)(piVar1[0x20d] << 3) / (uint)(piVar1[0x20e] * piVar1[0x210]);
        uVar6 = piVar1[0x20f] * param_1[0xc] >> 8;
        uVar3 = (param_2 * uVar6) / param_3;
        local_8 = param_2;
        if (uVar2 < uVar3) {
          local_8 = (uVar2 * param_3) / uVar6;
          uVar3 = uVar2;
        }
        uVar2 = uVar3 * piVar1[0x20e] * piVar1[0x210] >> 3;
        iVar4 = iMUSE_Dispatch__3510(piVar1,uVar2);
        Im_MixSamples((short *)(piVar1[0x20b] + piVar1[0x20c]),uVar3,piVar1[0x20e],piVar1[0x210],
                      piVar1[4],local_8,local_4,iVar4,param_1[9]);
        iVar4 = piVar1[0x20d];
        piVar1[0x20c] = piVar1[0x20c] + uVar2;
        piVar1[0x20d] = iVar4 - uVar2;
        if (iVar4 - uVar2 == 0) {
          iMUSE_Dispatch__3640(piVar1[0x20b]);
          piVar1[0x20b] = 0;
        }
      }
    }
    if (param_2 == 0) {
      return;
    }
    uVar2 = (uint)(piVar1[6] << 3) / (uint)(piVar1[3] * piVar1[1]);
    uVar6 = piVar1[2] * param_1[0xc] >> 8;
    local_8 = (param_2 * uVar6) / param_3;
    uVar3 = param_2;
    if (uVar2 < local_8) {
      uVar3 = (uVar2 * param_3) / uVar6;
      local_8 = uVar2;
    }
    if (local_8 == 0) {
      Im_FreeTrack(param_1);
      return;
    }
    uVar2 = local_8 * piVar1[3] * piVar1[1] >> 3;
    if (piVar1[0x207] == 0) {
      iVar4 = iMUSE_dsound__4540(param_1[3]);
      if (iVar4 == 0) {
        return;
      }
      psVar5 = (short *)(iVar4 + piVar1[5]);
    }
    else {
      psVar5 = (short *)iMUSE_stream__a420(piVar1[0x207],uVar2);
      if (psVar5 == (short *)0x0) {
        piVar1[0x20a] = 1;
        if ((piVar1[0x20b] != 0) && (piVar1[0x211] != 0)) {
          piVar1[0x212] = piVar1[0x212] + param_2;
        }
        Im_QueryStreamTrack(piVar1[0x207],(undefined4 *)&DAT_1002d810,(undefined4 *)&DAT_10024ddc,
                            (int *)&DAT_1002d7e0,(undefined4 *)&DAT_1002d7e4);
        return;
      }
      *(uint *)(piVar1[0x209] + 0xc) = *(int *)(piVar1[0x209] + 0xc) + uVar2;
      *(uint *)(piVar1[0x209] + 0x10) = *(int *)(piVar1[0x209] + 0x10) - uVar2;
      piVar1[0x20a] = 0;
    }
    if (piVar1[0x20b] == 0) {
LAB_100028ef:
      iVar4 = param_1[8];
    }
    else {
      if ((piVar1[0x211] != 0) && (uVar6 = piVar1[0x212], uVar6 != 0)) {
        uVar7 = uVar6;
        if (uVar3 <= uVar6) {
          uVar7 = uVar3;
        }
        uVar3 = uVar3 - uVar7;
        piVar1[0x212] = uVar6 - uVar7;
        local_8 = ((piVar1[2] * param_1[0xc] >> 8) * uVar3) / param_3;
        psVar5 = (short *)((int)psVar5 + (uVar2 - (local_8 * piVar1[3] * piVar1[1] >> 3)));
      }
      if (piVar1[0x20b] == 0) goto LAB_100028ef;
      iVar4 = iMUSE_Dispatch__34b0(piVar1);
    }
    Im_MixSamples(psVar5,local_8,piVar1[1],piVar1[3],piVar1[4],uVar3,local_4,iVar4,param_1[9]);
    local_4 = local_4 + uVar3;
    piVar1[5] = piVar1[5] + uVar2;
    piVar1[6] = piVar1[6] - uVar2;
    param_2 = param_2 - uVar3;
  } while( true );
}
#undef local_4
#undef local_8


/* ---- 0x10002a60  Im_DispatchAllocBuffers ---- */
/* WARNING: Removing unreachable block (ram,0x10002cfb) */
/* Unidentified function of iMUSE_Dispatch.c (command dispatch, fades, triggers) */

int __cdecl Im_DispatchAllocBuffers(int *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  uint uVar5;
  uint uVar6;
  int *piVar7;
  undefined4 *puVar8;
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  local_4 = -1;
  if (DAT_1002d814 == 0) {
    InitializeCriticalSection(IMG_ADDR(0x1002d7f0));
    DAT_1002d814 = 1;
  }
  EnterCriticalSection(IMG_ADDR(0x1002d7f0));
  iVar2 = Im_DispatchFetchNext(param_1);
  if (((iVar2 == 0) && (iVar2 = local_4, param_1[6] == 0)) &&
     ((param_1[0x207] == 0 || (param_1[5] == *(int *)(param_1[0x209] + 0xc))))) {
    piVar7 = (int *)0x0;
    do {
      do {
        while( true ) {
          piVar7 = (int *)iMUSE_Dispatch__30d0((int)(param_1 + 7),param_1[5],(int)piVar7);
          if (piVar7 == (int *)0x0) goto LAB_10002d11;
          iVar3 = *piVar7;
          if (0x4a554d50 < iVar3) break;
          if (iVar3 == 0x4a554d50) {
            iVar3 = iMUSE_stream__b840((int *)(*param_1 + 0x38),piVar7[4]);
            if (iVar3 == 0) {
              param_1[5] = piVar7[3];
              if (param_1[0x207] != 0) {
                puVar4 = (undefined4 *)param_1[0x209];
                piVar1 = param_1 + 0x209;
                if ((puVar4[4] != 0) || (puVar4[1] == 0)) {
                  iMUSE_Dispatch__3250(param_1,puVar4,(int)piVar7,1);
                }
                *(undefined4 *)(*piVar1 + 8) = 0;
                iMUSE_stream__b7a0(piVar1,(int *)*piVar1);
                if (*(int *)(*piVar1 + 0x14) != 0) {
                  if (param_1[0x20b] != 0) {
                    iMUSE_Dispatch__3640(param_1[0x20b]);
                  }
                  DAT_1002d7e8 = *(uint *)(*piVar1 + 0x10);
                  iVar3 = iMUSE_Dispatch__35a0(&DAT_1002d7e8);
                  param_1[0x20b] = iVar3;
                  if (iVar3 != 0) {
                    param_1[0x20c] = 0;
                    param_1[0x20d] = 0;
                    param_1[0x20e] = param_1[1];
                    param_1[0x20f] = param_1[2];
                    param_1[0x210] = param_1[3];
                    param_1[0x211] = 0;
                    param_1[0x212] = 0;
                    param_1[0x213] = 0x7f0000;
                    param_1[0x214] = 0;
                    if (DAT_1002d7e8 != 0) {
                      do {
                        uVar6 = DAT_1002d7e8 - param_1[0x20d];
                        if (0x3fff < uVar6) {
                          uVar6 = 0x4000;
                        }
                        puVar4 = (undefined4 *)iMUSE_stream__a420(param_1[0x207],uVar6);
                        puVar8 = (undefined4 *)(param_1[0x20d] + param_1[0x20b]);
                        for (uVar5 = uVar6 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
                          *puVar8 = *puVar4;
                          puVar4 = puVar4 + 1;
                          puVar8 = puVar8 + 1;
                        }
                        for (uVar5 = uVar6 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                          *(undefined1 *)puVar8 = *(undefined1 *)puVar4;
                          puVar4 = (undefined4 *)((int)puVar4 + 1);
                          puVar8 = (undefined4 *)((int)puVar8 + 1);
                        }
                        iVar3 = param_1[0x20d];
                        param_1[0x20d] = iVar3 + uVar6;
                      } while (iVar3 + uVar6 < DAT_1002d7e8);
                    }
                    DAT_10024de0 = 1;
                  }
                  *(undefined4 *)(param_1[0x209] + 8) = 0;
                  iMUSE_stream__b7a0(param_1 + 0x209,(int *)param_1[0x209]);
                }
              }
              piVar7 = (int *)0x0;
            }
          }
          else {
            if (iVar3 != 0x46524d54) goto LAB_10002d11;
            param_1[4] = (uint)(piVar7[3] == 0);
            param_1[1] = piVar7[4];
            param_1[2] = piVar7[5];
            param_1[3] = piVar7[6];
          }
        }
        if (iVar3 == 0x5245474e) {
          param_1[6] = piVar7[3];
          goto LAB_10002d0d;
        }
      } while (iVar3 == 0x53594e43);
      if (iVar3 != 0x54455854) goto LAB_10002d11;
      iVar3 = *(int *)(*param_1 + 0xc);
      Im_FireTriggers(iVar3,(char *)(piVar7 + 3));
      if (iVar3 != *(int *)(*param_1 + 0xc)) {
        local_4 = -3;
        iVar2 = local_4;
        goto LAB_10002d11;
      }
    } while (param_1[6] == 0);
LAB_10002d0d:
    local_4 = 0;
    iVar2 = local_4;
  }
LAB_10002d11:
  local_4 = iVar2;
  LeaveCriticalSection(IMG_ADDR(0x1002d7f0));
  return local_4;
}
#undef local_4


/* ---- 0x10002d30  Im_DispatchFetchNext ---- */
/* Advances a dispatch through its sound regions / jumps and fetches the next data */

int __cdecl Im_DispatchFetchNext(int *param_1)

{
  unsigned char _frame[0x70] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  uint uVar2;
  int *piVar3;
  int *piVar4;
  undefined1 *puVar5;
  int iVar6;
  uint *puVar7;
  uint *puVar8;
  undefined4 *puVar9;
  char *pcVar10;
  bool bVar11;
  #define local_58 (*(uint *)(_frame + (0x70 - 0x58)))
  #define local_54 (*(uint *)(_frame + (0x70 - 0x54)))
  #define local_50 (*(undefined4 (*)[7])(_frame + (0x70 - 0x50)))
  #define local_31 (*(undefined1 *)(_frame + (0x70 - 0x31)))
  
  piVar4 = param_1;
  piVar1 = param_1 + 7;
  if (param_1[7] == 0x4d415020) {
    if (param_1[0x207] == 0) {
      return 0;
    }
    if (param_1[0x209] != 0) {
      return 0;
    }
  }
  if (param_1[5] != 0) {
    return -1;
  }
  piVar3 = param_1 + 0x207;
  if (*piVar3 == 0) {
    puVar5 = (undefined1 *)iMUSE_dsound__4570(*(uint *)(*param_1 + 0xc));
    if (puVar5 == (undefined1 *)0x0) {
      return -1;
    }
    iVar6 = iMUSE_stream__b810(puVar5);
    if (iVar6 != 0x694d5553) {
      return -1;
    }
    iVar6 = iMUSE_stream__b810(puVar5 + 8);
    if (iVar6 != 0x4d415020) {
      return -1;
    }
    iVar6 = iMUSE_stream__b810(puVar5 + 0xc);
    piVar4[5] = iVar6 + 0x18;
    iVar6 = iMUSE_Dispatch__2fe0((undefined4 *)(puVar5 + 8),piVar1);
    if (iVar6 != 0) {
      return -1;
    }
    if (piVar4[9] != 0x46524d54) {
      return -1;
    }
    return -(uint)(piVar4[5] != piVar4[0xb]);
  }
  param_1 = (int *)0x0;
  puVar7 = (uint *)iMUSE_stream__a490(*piVar3,0,0x40);
  if (puVar7 == (uint *)0x0) {
    return -3;
  }
  iVar6 = 4;
  bVar11 = true;
  puVar8 = puVar7;
  pcVar10 = &DAT_10017090;
  do {
    if (iVar6 == 0) break;
    iVar6 = iVar6 + -1;
    bVar11 = (char)*puVar8 == *pcVar10;
    puVar8 = (uint *)((int)puVar8 + 1);
    pcVar10 = pcVar10 + 1;
  } while (bVar11);
  if (bVar11) {
    iVar6 = 8;
    bVar11 = true;
    puVar8 = puVar7 + 2;
    pcVar10 = &DAT_10017084;
    do {
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      bVar11 = (char)*puVar8 == *pcVar10;
      puVar8 = (uint *)((int)puVar8 + 1);
      pcVar10 = pcVar10 + 1;
    } while (bVar11);
    if (bVar11) {
      puVar8 = Im_VimaDecompress(puVar7,(int *)0x0,&local_54,(uint *)0x0,&local_58,(int *)0x0,
                                 (uint *)&param_1);
      piVar4[5] = (int)puVar8 - (int)puVar7;
      iVar6 = iMUSE_stream__a420(piVar4[0x207],(int)puVar8 - (int)puVar7);
      if (iVar6 == 0) {
        return -1;
      }
      Im_DecodeSoundBlock(local_50,3,local_54,0x10,local_58,(uint)param_1);
      local_31 = 1;
      puVar9 = local_50;
      goto LAB_10002f3c;
    }
  }
  iVar6 = 4;
  bVar11 = true;
  puVar8 = puVar7;
  pcVar10 = (char *)&DAT_10017074;
  do {
    if (iVar6 == 0) break;
    iVar6 = iVar6 + -1;
    bVar11 = (char)*puVar8 == *pcVar10;
    puVar8 = (uint *)((int)puVar8 + 1);
    pcVar10 = pcVar10 + 1;
  } while (bVar11);
  if (!bVar11) {
    return -1;
  }
  iVar6 = 4;
  bVar11 = true;
  puVar8 = puVar7 + 2;
  pcVar10 = (char *)&DAT_100170b8;
  do {
    if (iVar6 == 0) break;
    iVar6 = iVar6 + -1;
    bVar11 = (char)*puVar8 == *pcVar10;
    puVar8 = (uint *)((int)puVar8 + 1);
    pcVar10 = pcVar10 + 1;
  } while (bVar11);
  if (!bVar11) {
    return -1;
  }
  iVar6 = iMUSE_stream__b810((undefined1 *)(puVar7 + 3));
  uVar2 = iVar6 + 0x18;
  iVar6 = iMUSE_stream__a490(piVar4[0x207],0,uVar2);
  if (iVar6 == 0) {
    return -3;
  }
  puVar9 = (undefined4 *)iMUSE_stream__a420(piVar4[0x207],uVar2);
  if (puVar9 == (undefined4 *)0x0) {
    return -1;
  }
  piVar4[5] = uVar2;
LAB_10002f3c:
  iVar6 = iMUSE_Dispatch__2fe0(puVar9 + 2,piVar4 + 7);
  if (iVar6 == 0) {
    if (param_1 != (int *)0x0) {
      piVar4[0xb] = piVar4[5];
      piVar4[0x12] = piVar4[5];
      piVar4[0x16] = (int)param_1 + piVar4[5];
    }
    if (((piVar4[9] == 0x46524d54) && (piVar4[5] == piVar4[0xb])) && (piVar4[0x209] == 0)) {
      puVar9 = iMUSE_Dispatch__3570();
      piVar4[0x209] = (int)puVar9;
      if (puVar9 != (undefined4 *)0x0) {
        puVar9[3] = piVar4[5];
        iVar6 = Im_FindTrack(piVar4[0x207]);
        *(int *)(piVar4[0x209] + 0x10) = iVar6;
        *(undefined4 *)(piVar4[0x209] + 0x14) = 0;
        return 0;
      }
    }
  }
  return -1;
}
#undef local_31
#undef local_50
#undef local_54
#undef local_58


/* ---- 0x100036b0  Im_DSoundInit ---- */
/* iMUSE_dsound.c */

undefined4 __cdecl Im_DSoundInit(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  int *piVar2;
  
  PTR_1002d830 = (int *)(**(code **)(DAT_10033510 + 0x20))
                                  (0x3000,s_C__grimsrc_libs_iMUSE_dsound_c_10017104,0x50);
  DAT_1002d818 = PTR_1002d830 + 0x600;
  PTR_1002d834 = DAT_100336bc;
  Im_DSoundCreateBuffer(3);
  *param_2 = 2;
  param_2[2] = 0x1800;
  param_2[3] = 0;
  param_2[1] = PTR_1002d830;
  piVar2 = PTR_1002d830;
  for (iVar1 = 0xc00; iVar1 != 0; iVar1 = iVar1 + -1) {
    *piVar2 = 0;
    piVar2 = piVar2 + 1;
  }
  DAT_1002d844 = 0;
  return 0;
}

/* ---- 0x10003730  Im_DSoundHeartbeat ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Fills the DirectSound stream buffer from the mixer once per tick */

int __cdecl Im_DSoundHeartbeat(int **buf_out,uint *count_out,int *rate_out)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  uint uVar4;
  uint uVar5;
  undefined4 *puVar6;
  int *piVar7;
  undefined4 *puVar8;
  
  *count_out = 0;
  uVar5 = DAT_1002d82c;
  piVar3 = DAT_1002d840;
  if ((DAT_1002d840 == (int *)0x0) && (piVar3 = DAT_1002d844, DAT_1002d844 == (int *)0x0)) {
    DAT_1002d848 = DAT_1002d848 ^ 1;
    if (DAT_1002d848 == 0) {
      piVar3 = (int *)0x0;
      if (DAT_1002d84c != 0) {
        DAT_1002d848 = 0;
        if ((DAT_1002d854 != (undefined4 *)0x0) && (DAT_1002d820 != 0)) {
          piVar3 = DAT_1002d818;
          piVar2 = DAT_1002d850;
          for (uVar4 = DAT_1002d82c >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
            *piVar2 = *piVar3;
            piVar3 = piVar3 + 1;
            piVar2 = piVar2 + 1;
          }
          for (uVar5 = uVar5 & 3; uVar4 = DAT_1002d820, uVar5 != 0; uVar5 = uVar5 - 1) {
            *(char *)piVar2 = (char)*piVar3;
            piVar3 = (int *)((int)piVar3 + 1);
            piVar2 = (int *)((int)piVar2 + 1);
          }
          puVar8 = (undefined4 *)(DAT_1002d82c + (int)DAT_1002d818);
          puVar6 = DAT_1002d854;
          for (uVar5 = DAT_1002d820 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
            *puVar6 = *puVar8;
            puVar8 = puVar8 + 1;
            puVar6 = puVar6 + 1;
          }
          for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
            *(undefined1 *)puVar6 = *(undefined1 *)puVar8;
            puVar8 = (undefined4 *)((int)puVar8 + 1);
            puVar6 = (undefined4 *)((int)puVar6 + 1);
          }
        }
        iVar1 = (**(code_std **)(*PTR_1002d83c + 0x4c))
                          (PTR_1002d83c,DAT_1002d850,DAT_1002d82c,DAT_1002d854,DAT_1002d820);
        DAT_1002d84c = 0;
        return iVar1;
      }
    }
    else {
      piVar2 = (int *)iMUSE_dsound__3a80();
      piVar3 = piVar2;
      if (piVar2 != (int *)0xffffffff) {
        piVar3 = (int *)(((int)PTR_100170ec + 1) / DAT_1002d824);
        if (piVar2 != (int *)(((int)PTR_100170ec + 1) % DAT_1002d824)) {
          if ((int)PTR_100170ec < 0) {
            PTR_100170ec = piVar2;
          }
          PTR_100170ec = (int *)(((int)PTR_100170ec + 1) % DAT_1002d824);
          puVar8 = &DAT_1002d820;
          piVar7 = (int *)&DAT_1002d82c;
          piVar3 = (int *)(**(code_std **)(*PTR_1002d83c + 0x2c))
                                    (PTR_1002d83c,(int)PTR_100170ec * 0x1800,0x1800,&DAT_1002d850,
                                     &DAT_1002d82c,&DAT_1002d854,&DAT_1002d820,0);
          piVar2 = DAT_1002d850;
          if (piVar3 == (int *)0x0) {
            if ((DAT_1002d854 == (undefined4 *)0x0) || (DAT_1002d820 == 0)) {
              *piVar7 = (int)DAT_1002d850;
              *count_out = DAT_1002d82c >> 2;
            }
            else {
              *piVar7 = (int)DAT_1002d818;
              *count_out = 0x600;
              piVar2 = piVar7;
            }
            *puVar8 = 0x5622;
            DAT_1002d84c = 1;
            piVar3 = piVar2;
          }
        }
      }
    }
  }
  return (int)piVar3;
}
#endif


/* ---- 0x100038d0  Im_DSoundShutdown ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Unidentified function of iMUSE_dsound.c (DirectSound output) */

undefined4 Im_DSoundShutdown(void)

{
  DAT_1002d844 = 1;
  if (PTR_1002d838 != (int *)0x0) {
    (**(code_std **)(*PTR_1002d838 + 8))(PTR_1002d838);
  }
  PTR_1002d838 = (int *)0x0;
  if (PTR_1002d83c != (int *)0x0) {
    (**(code_std **)(*PTR_1002d83c + 8))(PTR_1002d83c);
  }
  PTR_1002d83c = (int *)0x0;
  (**(code **)(DAT_10033510 + 0x24))(PTR_1002d830);
  return 0;
}
#endif


/* ---- 0x10003930  Im_DSoundCreateBuffer ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Unidentified function of iMUSE_dsound.c (DirectSound output) */

void __cdecl Im_DSoundCreateBuffer(int param_1)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 **ppuVar5;
  int *piVar6;
  #define puStack_30 (*(undefined4 **)(_frame + (0x40 - 0x30)))
  #define ppiStack_2c (*(int ***)(_frame + (0x40 - 0x2c)))
  #define piStack_28 (*(int **)(_frame + (0x40 - 0x28)))
  #define uStack_14 (*(undefined4 *)(_frame + (0x40 - 0x14)))
  #define uStack_10 (*(undefined4 *)(_frame + (0x40 - 0x10)))
  #define iStack_c (*(int *)(_frame + (0x40 - 0xc)))
  #define uStack_8 (*(undefined4 *)(_frame + (0x40 - 0x8)))
  #define puStack_4 (*(undefined **)(_frame + (0x40 - 0x4)))
  
  DAT_1002d840 = 1;
  if (PTR_1002d83c != (int *)0x0) {
    piStack_28 = PTR_1002d83c;
    ppiStack_2c = (int **)0x1000394d;
    (**(code_std **)(*PTR_1002d83c + 8))();
  }
  piVar1 = PTR_1002d834;
  PTR_1002d83c = (int *)0x0;
  if (param_1 < 3) {
    param_1 = 3;
  }
  if (0x10 < param_1) {
    param_1 = 0x10;
  }
  uStack_14 = 0x14;
  uStack_10 = 0x18080;
  iStack_c = param_1 * 0x1800;
  uStack_8 = 0;
  piStack_28 = (int *)0x0;
  puStack_30 = &uStack_14;
  puStack_4 = &DAT_100170f0;
  ppiStack_2c = &PTR_1002d83c;
  DAT_1002d824 = param_1;
  iVar2 = (**(code_std **)(*PTR_1002d834 + 0xc))();
  if (iVar2 == 0) {
    (**(code_std **)(*PTR_1002d83c + 0x3c))(PTR_1002d83c);
    uVar3 = DAT_1002d824 * 0x1800;
    iVar2 = (**(code_std **)(*PTR_1002d83c + 0x2c))(PTR_1002d83c);
    if (iVar2 == 0) {
      ppuVar5 = &puStack_30;
      for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *ppuVar5 = (undefined4 *)0x0;
        ppuVar5 = ppuVar5 + 1;
      }
      for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
        *(undefined1 *)ppuVar5 = 0;
        ppuVar5 = (undefined4 **)((int)ppuVar5 + 1);
      }
      if (piVar1 != (int *)0x0) {
        piVar6 = piVar1;
        for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
          *piVar6 = 0;
          piVar6 = piVar6 + 1;
        }
        for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
          *(undefined1 *)piVar6 = 0;
          piVar6 = (int *)((int)piVar6 + 1);
        }
      }
      (**(code_std **)(*PTR_1002d83c + 0x4c))(PTR_1002d83c,&puStack_30,uVar3,piVar1,0);
    }
    (**(code_std **)(*PTR_1002d83c + 0x30))(PTR_1002d83c,0,0,1);
  }
  DAT_1002d840 = 0;
  return;
}
#undef iStack_c
#undef piStack_28
#undef ppiStack_2c
#undef puStack_30
#undef puStack_4
#undef uStack_10
#undef uStack_14
#undef uStack_8

#endif


/* ---- 0x10003ac0  Im_DSoundReset ---- */
/* Unidentified function of iMUSE_dsound.c (DirectSound output) */

undefined4 Im_DSoundReset(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_1002d860;
  for (iVar1 = 0xa0; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  DAT_1002d858 = 0;
  return 0;
}

/* ---- 0x10003ae0  Im_DSoundSave ---- */
/* Unidentified function of iMUSE_dsound.c (DirectSound output) */

undefined4 __cdecl Im_DSoundSave(undefined4 *param_1,uint param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (param_2 < 0x280) {
    return 0xfffffffb;
  }
  puVar2 = &DAT_1002d860;
  for (iVar1 = 0xa0; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *puVar2;
    puVar2 = puVar2 + 1;
    param_1 = param_1 + 1;
  }
  return 0x280;
}

/* ---- 0x10003b10  Im_DSoundRestore ---- */
/* Unidentified function of iMUSE_dsound.c (DirectSound output) */

undefined4 __cdecl Im_DSoundRestore(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_1002d860;
  for (iVar1 = 0xa0; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *param_1;
    param_1 = param_1 + 1;
    puVar2 = puVar2 + 1;
  }
  DAT_1002d858 = 1;
  return 0x280;
}

/* ---- 0x10003b40  Im_FadeParamImpl ---- */
/* Body of ImFadeParam: allocates a fade slot for (sound, param, target, duration) */

undefined4 __cdecl Im_FadeParamImpl(int param_1,int param_2,uint param_3,int param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  
  piVar4 = &DAT_1002d860;
  if (((param_1 == 0) || (param_4 < 0)) ||
     ((param_2 != 0x500 && (((param_2 != 0x600 && (param_2 != 0x700)) && (param_2 != 0x800)))))) {
    return 0xfffffffb;
  }
  iVar1 = (param_4 * 5) / 6;
  Im_FadesClearSound(param_1,param_2);
  if (iVar1 != 0) {
    iVar2 = 0;
    do {
      if (*piVar4 == 0) {
        piVar4[1] = param_1;
        piVar4[2] = param_2;
        uVar3 = ImGetParam(param_1,param_2);
        piVar4[3] = uVar3;
        iVar2 = param_3 - uVar3;
        piVar4[5] = iVar1;
        piVar4[4] = iVar1;
        piVar4[9] = ((-1 < iVar2) - 1 & 0xfffffffe) + 1;
        piVar4[6] = iVar2 / iVar1;
        if (iVar2 < 0) {
          iVar2 = -iVar2;
        }
        piVar4[8] = 0;
        *piVar4 = 1;
        DAT_1002d858 = 1;
        piVar4[7] = iVar2 % iVar1;
        return 0;
      }
      iVar2 = iVar2 + 1;
      piVar4 = piVar4 + 10;
    } while (iVar2 < 0x10);
    return 0xfffffffa;
  }
  if ((param_2 == 0x600) && (param_3 == 0)) {
    ImStopSound(param_1);
    return 0;
  }
  ImSetParam(param_1,param_2,param_3);
  return 0;
}

/* ---- 0x10003c70  Im_FadesClearSound ---- */
/* Unidentified function of iMUSE_dsound.c (DirectSound output) */

void __cdecl Im_FadesClearSound(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = &DAT_1002d860;
  iVar2 = 0x10;
  do {
    if (((*piVar1 != 0) && (piVar1[1] == param_1)) && ((piVar1[2] == param_2 || (param_2 == -1)))) {
      *piVar1 = 0;
    }
    piVar1 = piVar1 + 10;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}

/* ---- 0x10003cb0  Im_FadesHeartbeat ---- */
/* Steps every active fade and applies the parameter */

uint Im_FadesHeartbeat(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  int iVar5;
  
  uVar1 = DAT_1002d858;
  if (DAT_1002d858 != 0) {
    DAT_1002d858 = 0;
    puVar4 = &DAT_1002d880;
    iVar5 = 0x10;
    do {
      if (puVar4[-8] != 0) {
        uVar1 = puVar4[-4];
        DAT_1002d858 = 1;
        puVar4[-4] = uVar1 - 1;
        if (uVar1 - 1 == 0) {
          puVar4[-8] = 0;
        }
        uVar2 = puVar4[-2] + puVar4[-5];
        uVar3 = *puVar4 + puVar4[-1];
        *puVar4 = uVar3;
        uVar1 = uVar3;
        if (puVar4[-3] <= uVar3) {
          uVar1 = puVar4[1];
          *puVar4 = uVar3 - puVar4[-3];
          uVar2 = uVar2 + uVar1;
        }
        if (uVar2 != puVar4[-5]) {
          uVar1 = (int)puVar4[-4] / 5;
          puVar4[-5] = uVar2;
          if ((int)puVar4[-4] % 5 == 0) {
            if ((puVar4[-6] == 0x600) && (uVar2 == 0)) {
              uVar1 = ImStopSound(puVar4[-7]);
            }
            else {
              uVar1 = ImSetParam(puVar4[-7],puVar4[-6],uVar2);
            }
          }
        }
      }
      puVar4 = puVar4 + 10;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
  }
  return uVar1;
}

/* ---- 0x10004820  Im_ApplyFXPreset ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* HMI SOS FX preset processing on a mixed block */

undefined4 __cdecl
Im_ApplyFXPreset(undefined2 *param_1,uint param_2,undefined2 *param_3,int *param_4,int *param_5,
                int param_6)

{
  undefined2 uVar1;
  int iVar2;
  uint uVar3;
  
  if (DAT_1002dd74 == 0) {
    if (param_6 != 0) {
      iVar2 = hmiFXMalloc(param_2 * DAT_1002dd62);
      *param_4 = iVar2;
      if (iVar2 == 0) {
        return DAT_1002dd7c;
      }
      *param_5 = param_2 * DAT_1002dd62;
      param_3 = (undefined2 *)*param_4;
    }
    if (param_3 != (undefined2 *)0x0) {
      uVar3 = param_2 >> 1;
      if (DAT_1002dd62 == 2) {
        if (uVar3 != 0) {
          do {
            *param_3 = *param_1;
            param_3[1] = *param_1;
            param_3 = param_3 + 2;
            uVar3 = uVar3 - 1;
            param_1 = param_1 + 1;
          } while (uVar3 != 0);
          return DAT_1002dd7c;
        }
      }
      else if (uVar3 != 0) {
        do {
          uVar1 = *param_1;
          param_1 = param_1 + 1;
          *param_3 = uVar1;
          param_3 = param_3 + 1;
          uVar3 = uVar3 - 1;
        } while (uVar3 != 0);
        return DAT_1002dd7c;
      }
    }
  }
  else {
    _DAT_1002dd08 = 0x19;
    if (param_6 != 0) {
      _DAT_1002dd08 = 0x9d;
    }
    _DAT_1002dd0c = DAT_1002dd74;
    _DAT_1002dd24 = &DAT_1002dd30;
    _DAT_1002dd28 = &DAT_1002dd60;
    _DAT_1002dd1c = param_1;
    _DAT_1002dd20 = param_2;
    if (param_6 == 0) {
      DAT_1002dd14 = param_3;
    }
    hmiFXPresetProcess(DAT_1002dd2c,&DAT_1002dd08);
    if (param_6 != 0) {
      *param_4 = (int)DAT_1002dd14;
      *param_5 = DAT_1002dd18;
    }
  }
  return DAT_1002dd7c;
}

/* ---- 0x10004970  FUN_10004970 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_10004970(void)

{
  if (_DAT_1002dd78 != 0) {
    _DAT_1002dd78 = 0;
    if (DAT_1002dd74 != 0) {
      hmiFXPresetRelease(DAT_1002dd74);
    }
    if (DAT_1002dd2c != 0) {
      hmiFXPresetFreeLibrary(DAT_1002dd2c);
    }
    hmiFXUnInitSystem(IMG_ADDR(0x1002dd48));
  }
  return;
}
#endif


/* ---- 0x100049b0  Im_GroupsInit ---- */
/* Unidentified function of iMUSE_dsound.c (DirectSound output) */

undefined4 Im_GroupsInit(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_1002ddc0;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0x7f;
    puVar2 = puVar2 + 1;
  }
  puVar2 = &DAT_1002dd80;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0x7f;
    puVar2 = puVar2 + 1;
  }
  return 0;
}

/* ---- 0x100049e0  Im_SetGroupVolImpl ---- */
/* Unidentified function of iMUSE_dsound.c (DirectSound output) */

undefined4 __cdecl Im_SetGroupVolImpl(uint param_1,uint param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  if (0xf < param_1) {
    return 0xfffffffb;
  }
  if (param_2 == 0xffffffff) {
    return (&DAT_1002dd80)[param_1];
  }
  if (0x7f < param_2) {
    return 0xfffffffb;
  }
  uVar1 = (&DAT_1002dd80)[param_1];
  if (param_1 == 0) {
    DAT_1002dd80 = param_2;
    DAT_1002ddc0 = param_2;
    iVar2 = 0;
    do {
      iVar3 = iVar2 + 4;
      *(int *)((int)&DAT_1002ddc4 + iVar2) =
           (int)((*(int *)((int)&DAT_1002dd84 + iVar2) + 1) * param_2) >> 7;
      iVar2 = iVar3;
    } while (iVar3 < 0x3c);
    Im_GuardEnter();
    Im_UpdateGroupVolumes();
    Im_GuardLeave();
    return uVar1;
  }
  (&DAT_1002dd80)[param_1] = param_2;
  (&DAT_1002ddc0)[param_1] = (int)((param_2 + 1) * DAT_1002dd80) >> 7;
  Im_GuardEnter();
  Im_UpdateGroupVolumes();
  Im_GuardLeave();
  return uVar1;
}

/* ---- 0x10004a80  Im_GetGroupVol ---- */
/* Unidentified function of iMUSE_dsound.c (DirectSound output) */

undefined4 __cdecl Im_GetGroupVol(uint param_1)

{
  if (0xf < param_1) {
    return 0xfffffffb;
  }
  return (&DAT_1002ddc0)[param_1];
}

/* ---- 0x10004f50  Im_GuardEnter ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Guard enter: INC [DAT_100172c0], NOT atomic (no LOCK) and NOT a lock: it does not exclude any
   thread, ImHeartbeat only skips itself while it is nonzero. Called at the start of most Im* entry
   points. */

void Im_GuardEnter(void)

{
  DAT_100172c0 = DAT_100172c0 + 1;
  return;
}
#endif


/* ---- 0x10004f60  Im_GuardLeave ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Guard leave: load, if nonzero decrement, store (three separate steps, not atomic). Two threads
   leaving at the same moment both read 2 and both store 1: the counter stays 1 for good (a lost
   update), and ImHeartbeat (which only runs at 0) never runs again: every track freezes and every
   wait for a sound spins forever. Seen on the original with the heartbeat (WINMM timer thread) and
   ImGetParam of the main thread 171 us apart. */

int Im_GuardLeave(void)

{
  if (DAT_100172c0 != 0) {
    DAT_100172c0 = DAT_100172c0 + -1;
  }
  return DAT_100172c0;
}
#endif


/* ---- 0x10004f70  Im_DispatchCommand ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Single-entry command dispatcher: switches on the command id and calls the Im* API */

uint __cdecl
Im_DispatchCommand(uint cmd,int a2,int a3,int a4,int a5,int a6,int a7,int a8,int a9,int a10,int a11)

{
  uint uVar1;
  int in_stack_0000003c;
  
  if (DAT_1002df0c != 0) {
    switch(cmd) {
    case 0:
      uVar1 = ImInitialize();
      return uVar1;
    case 1:
      uVar1 = ImTerminate();
      return uVar1;
    case 2:
      return cmd;
    case 3:
      uVar1 = ImPause();
      return uVar1;
    case 4:
      uVar1 = ImResume();
      return uVar1;
    case 5:
      uVar1 = ImSave((undefined4 *)a3,a3);
      return uVar1;
    case 6:
      uVar1 = ImRestore((int *)a2);
      return uVar1;
    case 7:
      uVar1 = ImSetGroupVol(a3,a3);
      return uVar1;
    case 8:
      uVar1 = ImStartSound(a3,a3);
      return uVar1;
    case 9:
      uVar1 = ImStopSound(a2);
      return uVar1;
    case 10:
      uVar1 = ImStopAllSounds();
      return uVar1;
    case 0xb:
      uVar1 = ImGetNextSound(a2);
      return uVar1;
    case 0xc:
      uVar1 = ImSetParam(a4,a4,a4);
      return uVar1;
    case 0xd:
      uVar1 = ImGetParam(a3,a3);
      return uVar1;
    case 0xe:
      uVar1 = ImFadeParam(a5,a5,a5,a5);
      return uVar1;
    case 0xf:
      uVar1 = ImSetHook(a3,a3);
      return uVar1;
    case 0x10:
      uVar1 = ImGetHook(a2);
      return uVar1;
    case 0x11:
      uVar1 = ImSetTrigger(in_stack_0000003c,(char *)in_stack_0000003c,in_stack_0000003c,
                           in_stack_0000003c,in_stack_0000003c,in_stack_0000003c,in_stack_0000003c,
                           in_stack_0000003c,in_stack_0000003c,in_stack_0000003c,in_stack_0000003c,
                           in_stack_0000003c,in_stack_0000003c);
      return uVar1;
    case 0x12:
      uVar1 = ImCheckTrigger(a4,(byte *)a4,a4);
      return uVar1;
    case 0x13:
      uVar1 = ImClearTrigger(a4,(byte *)a4,a4);
      return uVar1;
    case 0x14:
      uVar1 = ImDeferCommand(in_stack_0000003c,in_stack_0000003c,in_stack_0000003c,in_stack_0000003c
                             ,in_stack_0000003c,in_stack_0000003c,in_stack_0000003c,
                             in_stack_0000003c,in_stack_0000003c,in_stack_0000003c,in_stack_0000003c
                             ,in_stack_0000003c);
      return uVar1;
    case 0x19:
      uVar1 = ImStartStream(a4,a4,a4);
      return uVar1;
    case 0x1a:
      uVar1 = ImSwitchStream(a6,a6,a6,a6,a6);
      return uVar1;
    case 0x1b:
      uVar1 = ImProcessStreams();
      return uVar1;
    case 0x1c:
      uVar1 = ImQueryStream(a6,(undefined4 *)a6,(undefined4 *)a6,(int *)a6,(undefined4 *)a6);
      return uVar1;
    case 0x1d:
      uVar1 = ImFeedStream(a5,(undefined4 *)a5,a5,a5);
      return uVar1;
    }
  }
  return 0xffffffff;
}
#endif


/* ---- 0x10005360  Im_MixerInit ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* iMUSE_Mixer.c */

undefined4 __cdecl Im_MixerInit(undefined4 *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined2 *puVar1;
  int iVar2;
  undefined1 *puVar3;
  longlong lVar4;
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  iVar2 = 0;
  puVar3 = &DAT_10033560;
  do {
    local_4 = 0;
    do {
      fsin((float10)local_4 * (float10)3.1415 * (float10)0.03125);
      lVar4 = hmi__bae0();
      *puVar3 = (char)lVar4;
      puVar3 = puVar3 + 1;
      local_4 = local_4 + 1;
    } while (local_4 < 0x11);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x11);
  DAT_1002df18 = *param_1;
  DAT_1002df24 = param_1[2] << 1;
  PTR_1002df5c = (int *)(**(code **)(DAT_10033510 + 0x20))
                                  (param_1[2] << 1,s_C__grimsrc_libs_iMUSE_Mixer_c_100172c8,0x7a);
  _DAT_1002df28 = param_1[3];
  puVar1 = (undefined2 *)
           (**(code **)(DAT_10033510 + 0x20))
                     (DAT_1001e8d4 << 0x10,s_C__grimsrc_libs_iMUSE_Mixer_c_100172c8,0x7f);
  DAT_1002df20 = puVar1;
  if (puVar1 == (undefined2 *)0x0) {
    return 0xffffffff;
  }
  iVar2 = 0;
  if (0 < DAT_1001e8d4 << 0xf) {
    do {
      lVar4 = hmi__bae0();
      *puVar1 = (short)lVar4;
      puVar1 = puVar1 + 1;
      iVar2 = iVar2 + 1;
    } while (iVar2 < DAT_1001e8d4 * 0x8000);
  }
  return 0;
}
#undef local_4

#endif


/* ---- 0x10005490  Im_MixerReset ---- */
/* Unidentified function of iMUSE_Mixer.c (software mixing / resampling) */

undefined4 Im_MixerReset(void)

{
  (**(code **)(DAT_10033510 + 0x24))(DAT_1002df20);
  (**(code **)(DAT_10033510 + 0x24))(PTR_1002df5c);
  return 0;
}

/* ---- 0x100054c0  Im_MixerHeartbeat ---- */
/* Unidentified function of iMUSE_Mixer.c (software mixing / resampling) */

undefined4 Im_MixerHeartbeat(void)

{
  uint uVar1;
  uint uVar2;
  int *piVar3;
  
  uVar2 = DAT_1002df24;
  piVar3 = PTR_1002df5c;
  for (uVar1 = DAT_1002df24 >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
    *piVar3 = 0;
    piVar3 = piVar3 + 1;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *(undefined1 *)piVar3 = 0;
    piVar3 = (int *)((int)piVar3 + 1);
  }
  return 0;
}

/* ---- 0x100054f0  Im_MixSamples ---- */
/* Dispatches to the four mix loops by channel count and volume mode */

void __cdecl
Im_MixSamples(short *param_1,int param_2,int param_3,int param_4,int param_5,uint param_6,
             uint param_7,int param_8,int param_9)

{
  uint uVar1;
  int iVar2;
  
  if ((((PTR_1002df5c != (int *)0x0) && (param_1 != (short *)0x0)) && (param_2 != 0)) &&
     ((param_3 == 0x10 && (0 < param_8)))) {
    if ((param_4 == 1) && (DAT_1002df18 == 2)) {
      uVar1 = param_8 >> 3;
      if (param_8 != 0) {
        uVar1 = uVar1 + 1;
      }
      if (0x10 < uVar1) {
        uVar1 = 0x10;
      }
      iVar2 = (param_9 >> 3) + -8;
      if (0x40 < param_9) {
        iVar2 = (param_9 >> 3) + -7;
      }
      if (param_5 != 0) {
        Im_MixLoopC(param_1,param_2,param_6,param_7,
                    (uint)(byte)(&DAT_10033568)[uVar1 * 0x11 - iVar2],
                    (uint)(byte)(&DAT_10033568)[uVar1 * 0x11 + iVar2]);
        return;
      }
      Im_MixLoopA(param_1,param_2,param_6,param_7,(uint)(byte)(&DAT_10033568)[uVar1 * 0x11 - iVar2],
                  (uint)(byte)(&DAT_10033568)[uVar1 * 0x11 + iVar2]);
      return;
    }
    if (param_5 != 0) {
      Im_MixLoopD(param_1,param_2,param_6,param_7,param_8 + 1);
      return;
    }
    Im_MixLoopB(param_1,param_2,param_6,param_7,param_8 + 1);
  }
  return;
}

/* ---- 0x10005610  Im_ReadSoundData ---- */
/* Reads and decodes the next block of a sound through the file layer */

undefined4 __cdecl Im_ReadSoundData(int *param_1,int param_2)

{
  int *piVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  
  if (((PTR_1002df5c != (int *)0x0) && (param_1 != (int *)0x0)) && (param_2 != 0)) {
    piVar5 = param_1;
    iVar3 = param_2;
    piVar1 = PTR_1002df5c;
    if (DAT_1002df18 == 2) {
      iVar3 = param_2 << 1;
    }
    for (; iVar3 != 0; iVar3 = iVar3 + -1) {
      iVar4 = *piVar1 >> 7;
      if (iVar4 < 0) {
        sVar2 = -*(short *)(DAT_1002df20 - (iVar4 * 2 + 2));
      }
      else {
        sVar2 = *(short *)(DAT_1002df20 + iVar4 * 2);
      }
      *(short *)piVar5 = sVar2;
      piVar5 = (int *)((int)piVar5 + 2);
      piVar1 = piVar1 + 1;
    }
    if (DAT_1002df60 != 0) {
      piVar5 = param_1;
      iVar3 = param_2;
      if (DAT_1002df60 == 1) {
        while( true ) {
          iVar3 = iVar3 + -1;
          if (*piVar5 != 0) break;
          piVar5 = piVar5 + 1;
          if (iVar3 == 0) {
            return 0;
          }
        }
        DAT_1002df60 = 2;
      }
      else if (DAT_1002df60 != 2) {
        if (DAT_1002df60 != 3) {
          return 0;
        }
        while( true ) {
          iVar3 = iVar3 + -1;
          if (*piVar5 != 0) break;
          piVar5 = piVar5 + 1;
          if (iVar3 == 0) {
            if (DAT_1002df64 != (int *)0x0) {
              ImFile_Read(DAT_1002df64,0,0);
              Im_DecodeSoundBlock((undefined4 *)&DAT_1002df30,5,0x5622,0x10,2,DAT_1002df1c);
              ImFile_Open(&DAT_1002df30,0x2c,1,DAT_1002df64);
              ImFile_Close(DAT_1002df64);
              DAT_1002df64 = (int *)0x0;
            }
            DAT_1002df60 = 0;
            return 0;
          }
        }
      }
      if (DAT_1002df64 != (int *)0x0) {
        ImFile_Open((char *)param_1,param_2 * 4,1,DAT_1002df64);
      }
      DAT_1002df1c = DAT_1002df1c + param_2 * 4;
    }
    return 0;
  }
  return 0xffffffff;
}

/* ---- 0x100057a0  Im_MixLoopA ---- */
/* Mix loop variant (16-bit source); exact channel layout not verified */

void __cdecl
Im_MixLoopA(short *param_1,int param_2,uint param_3,uint param_4,int param_5,int param_6)

{
  short sVar1;
  uint uVar2;
  int *piVar3;
  uint uVar4;
  uint uVar5;
  
  piVar3 = PTR_1002df5c + param_4 * 2;
  uVar2 = (uint)(param_2 << 0x10) / param_3;
  if (uVar2 == 0x8000) {
    while (param_2 = param_2 + -1, param_2 != 0) {
      *piVar3 = *piVar3 + param_5 * *param_1;
      piVar3[1] = piVar3[1] + param_6 * *param_1;
      piVar3[2] = piVar3[2] + ((int)*param_1 + (int)param_1[2] >> 1) * param_5;
      piVar3[3] = piVar3[3] + ((int)*param_1 + (int)param_1[2] >> 1) * param_6;
      piVar3 = piVar3 + 4;
      param_1 = param_1 + 1;
    }
    *piVar3 = *piVar3 + param_5 * *param_1;
    piVar3[1] = piVar3[1] + param_6 * *param_1;
    piVar3[2] = piVar3[2] + param_5 * *param_1;
    piVar3[3] = piVar3[3] + param_6 * *param_1;
  }
  else if (uVar2 == 0x10000) {
    if (param_3 != 0) {
      do {
        *piVar3 = *piVar3 + param_5 * *param_1;
        param_3 = param_3 - 1;
        piVar3[1] = piVar3[1] + param_6 * *param_1;
        param_1 = param_1 + 1;
        piVar3 = piVar3 + 2;
      } while (param_3 != 0);
      return;
    }
  }
  else if (uVar2 == 0x20000) {
    if (param_3 != 0) {
      do {
        *piVar3 = *piVar3 + param_5 * *param_1;
        sVar1 = *param_1;
        param_1 = param_1 + 2;
        param_3 = param_3 - 1;
        piVar3[1] = piVar3[1] + param_6 * sVar1;
        piVar3 = piVar3 + 2;
      } while (param_3 != 0);
      return;
    }
  }
  else {
    uVar4 = 0;
    if (param_3 != 0) {
      param_4 = param_3;
      do {
        uVar5 = uVar4 + uVar2;
        *piVar3 = *piVar3 + param_5 * *param_1;
        piVar3[1] = piVar3[1] + param_6 * *param_1;
        uVar4 = uVar5 & 0xffff;
        param_1 = param_1 + ((int)uVar5 >> 0x10);
        param_4 = param_4 - 1;
        piVar3 = piVar3 + 2;
      } while (param_4 != 0);
      return;
    }
  }
  return;
}

/* ---- 0x100059a0  Im_MixLoopB ---- */
/* Unidentified function of iMUSE_Mixer.c (software mixing / resampling) */

void __cdecl Im_MixLoopB(short *param_1,int param_2,uint param_3,uint param_4,int param_5)

{
  short sVar1;
  uint uVar2;
  short *psVar3;
  int *piVar4;
  uint uVar5;
  int iVar6;
  
  piVar4 = PTR_1002df5c + param_4 * 2;
  uVar2 = (uint)(param_2 << 0x10) / param_3;
  if (uVar2 == 0x8000) {
    while (param_2 = param_2 + -1, param_2 != 0) {
      *piVar4 = *piVar4 + param_5 * *param_1;
      piVar4[1] = piVar4[1] + param_5 * param_1[1];
      piVar4[2] = piVar4[2] + ((int)param_1[2] + (int)*param_1 >> 1) * param_5;
      piVar4[3] = piVar4[3] + ((int)param_1[3] + (int)param_1[1] >> 1) * param_5;
      piVar4 = piVar4 + 4;
      param_1 = param_1 + 2;
    }
    *piVar4 = *piVar4 + param_5 * *param_1;
    piVar4[1] = piVar4[1] + param_5 * param_1[1];
    piVar4[2] = piVar4[2] + param_5 * *param_1;
    piVar4[3] = piVar4[3] + param_5 * param_1[1];
  }
  else if (uVar2 == 0x10000) {
    iVar6 = param_3 * 2;
    if (iVar6 != 0) {
      do {
        sVar1 = *param_1;
        param_1 = param_1 + 1;
        iVar6 = iVar6 + -1;
        *piVar4 = *piVar4 + param_5 * sVar1;
        piVar4 = piVar4 + 1;
      } while (iVar6 != 0);
      return;
    }
  }
  else if (uVar2 == 0x20000) {
    if (param_3 != 0) {
      do {
        psVar3 = param_1 + 1;
        *piVar4 = *piVar4 + param_5 * *param_1;
        param_1 = param_1 + 4;
        param_3 = param_3 - 1;
        piVar4[1] = piVar4[1] + param_5 * *psVar3;
        piVar4 = piVar4 + 2;
      } while (param_3 != 0);
      return;
    }
  }
  else {
    uVar5 = 0;
    if (param_3 != 0) {
      param_4 = param_3;
      do {
        uVar5 = uVar5 + uVar2 * 2;
        *piVar4 = *piVar4 + param_5 * *param_1;
        piVar4[1] = piVar4[1] + param_1[1] * param_5;
        piVar4 = piVar4 + 2;
        param_1 = param_1 + ((int)uVar5 >> 0x10);
        uVar5 = uVar5 & 0xffff;
        param_4 = param_4 - 1;
      } while (param_4 != 0);
      return;
    }
  }
  return;
}

/* ---- 0x10005b80  Im_MixLoopC ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Unidentified function of iMUSE_Mixer.c (software mixing / resampling) */

void __cdecl
Im_MixLoopC(undefined2 *param_1,int param_2,uint param_3,int param_4,int param_5,int param_6)

{
  undefined2 uVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  
  piVar4 = PTR_1002df5c + param_4 * 2;
  uVar2 = (uint)(param_2 << 0x10) / param_3;
  if (uVar2 == 0x8000) {
    while (param_2 = param_2 + -1, param_2 != 0) {
      uVar1 = param_1[2];
      iVar5 = (int)CONCAT11((char)*param_1,(char)((ushort)*param_1 >> 8));
      *piVar4 = *piVar4 + param_5 * iVar5;
      param_1 = param_1 + 1;
      iVar3 = (int)(short)(CONCAT11((char)uVar1,(char)((ushort)uVar1 >> 8)) + iVar5 >> 1);
      piVar4[1] = piVar4[1] + param_6 * iVar5;
      piVar4[2] = piVar4[2] + param_5 * iVar3;
      piVar4[3] = piVar4[3] + param_6 * iVar3;
      piVar4 = piVar4 + 4;
    }
    iVar5 = (int)CONCAT11((char)*param_1,(char)((ushort)*param_1 >> 8));
    iVar3 = param_5 * iVar5;
    iVar5 = param_6 * iVar5;
    *piVar4 = *piVar4 + iVar3;
    piVar4[1] = piVar4[1] + iVar5;
    piVar4[2] = piVar4[2] + iVar3;
    piVar4[3] = piVar4[3] + iVar5;
  }
  else if (uVar2 == 0x10000) {
    if (param_3 != 0) {
      do {
        iVar3 = (int)CONCAT11((char)*param_1,(char)((ushort)*param_1 >> 8));
        *piVar4 = *piVar4 + param_5 * iVar3;
        param_1 = param_1 + 1;
        piVar4[1] = piVar4[1] + param_6 * iVar3;
        param_3 = param_3 - 1;
        piVar4 = piVar4 + 2;
      } while (param_3 != 0);
      return;
    }
  }
  else if (uVar2 == 0x20000) {
    if (param_3 != 0) {
      do {
        iVar3 = (int)CONCAT11((char)*param_1,(char)((ushort)*param_1 >> 8));
        *piVar4 = *piVar4 + param_5 * iVar3;
        param_1 = param_1 + 2;
        piVar4[1] = piVar4[1] + param_6 * iVar3;
        param_3 = param_3 - 1;
        piVar4 = piVar4 + 2;
      } while (param_3 != 0);
      return;
    }
  }
  else {
    uVar6 = 0;
    if (param_3 != 0) {
      do {
        iVar3 = (int)CONCAT11((char)*param_1,(char)((ushort)*param_1 >> 8));
        *piVar4 = *piVar4 + param_5 * iVar3;
        uVar7 = uVar6 + uVar2;
        piVar4[1] = piVar4[1] + param_6 * iVar3;
        piVar4 = piVar4 + 2;
        uVar6 = uVar7 & 0xffff;
        param_1 = param_1 + ((int)uVar7 >> 0x10);
        param_3 = param_3 - 1;
      } while (param_3 != 0);
      return;
    }
  }
  return;
}
#endif


/* ---- 0x10005db0  Im_MixLoopD ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Unidentified function of iMUSE_Mixer.c (software mixing / resampling) */

void __cdecl Im_MixLoopD(undefined2 *param_1,int param_2,uint param_3,uint param_4,int param_5)

{
  undefined2 uVar1;
  undefined2 uVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  undefined2 *puVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  
  piVar4 = PTR_1002df5c + param_4 * 2;
  uVar3 = (uint)(param_2 << 0x10) / param_3;
  if (uVar3 == 0x8000) {
    while (param_2 = param_2 + -1, param_2 != 0) {
      uVar1 = param_1[2];
      iVar7 = (int)CONCAT11((char)*param_1,(char)((ushort)*param_1 >> 8));
      uVar2 = param_1[3];
      iVar5 = (int)CONCAT11((char)param_1[1],(char)((ushort)param_1[1] >> 8));
      param_1 = param_1 + 2;
      *piVar4 = *piVar4 + param_5 * iVar7;
      piVar4[1] = piVar4[1] + param_5 * iVar5;
      piVar4[2] = piVar4[2] +
                  (short)(CONCAT11((char)uVar1,(char)((ushort)uVar1 >> 8)) + iVar7 >> 1) * param_5;
      piVar4[3] = piVar4[3] +
                  (short)(CONCAT11((char)uVar2,(char)((ushort)uVar2 >> 8)) + iVar5 >> 1) * param_5;
      piVar4 = piVar4 + 4;
    }
    iVar5 = CONCAT11((char)*param_1,(char)((ushort)*param_1 >> 8)) * param_5;
    iVar7 = CONCAT11((char)param_1[1],(char)((ushort)param_1[1] >> 8)) * param_5;
    *piVar4 = *piVar4 + iVar5;
    piVar4[1] = piVar4[1] + iVar7;
    piVar4[2] = piVar4[2] + iVar5;
    piVar4[3] = piVar4[3] + iVar7;
  }
  else if (uVar3 == 0x10000) {
    iVar7 = param_3 * 2;
    if (iVar7 != 0) {
      do {
        uVar1 = *param_1;
        param_1 = param_1 + 1;
        *piVar4 = *piVar4 + CONCAT11((char)uVar1,(char)((ushort)uVar1 >> 8)) * param_5;
        iVar7 = iVar7 + -1;
        piVar4 = piVar4 + 1;
      } while (iVar7 != 0);
      return;
    }
  }
  else if (uVar3 == 0x20000) {
    if (param_3 != 0) {
      do {
        puVar6 = param_1 + 1;
        *piVar4 = *piVar4 + CONCAT11((char)*param_1,(char)((ushort)*param_1 >> 8)) * param_5;
        param_1 = param_1 + 4;
        piVar4[1] = piVar4[1] + CONCAT11((char)*puVar6,(char)((ushort)*puVar6 >> 8)) * param_5;
        param_3 = param_3 - 1;
        piVar4 = piVar4 + 2;
      } while (param_3 != 0);
      return;
    }
  }
  else {
    uVar8 = 0;
    if (param_3 != 0) {
      param_4 = param_3;
      do {
        uVar1 = param_1[1];
        *piVar4 = *piVar4 + param_5 * CONCAT11((char)*param_1,(char)((ushort)*param_1 >> 8));
        uVar9 = uVar8 + uVar3 * 2;
        piVar4[1] = piVar4[1] + param_5 * CONCAT11((char)uVar1,(char)((ushort)uVar1 >> 8));
        uVar8 = uVar9 & 0xffff;
        param_1 = param_1 + ((int)uVar9 >> 0x10);
        param_4 = param_4 - 1;
        piVar4 = piVar4 + 2;
      } while (param_4 != 0);
      return;
    }
  }
  return;
}
#endif


/* ---- 0x10006070  FUN_10006070 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl FUN_10006070(int cmd,...)

{
  unsigned char _frame[0x40];  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *puVar1;
  undefined4 uVar2;
  char **ppcVar3;
  int iVar4;
  #define local_28 (*(char *(*)[4])(_frame + (0x40 - 0x28)))
  #define uStack_18 (*(undefined4 *)(_frame + (0x40 - 0x18)))
  #define uStack_14 (*(undefined4 *)(_frame + (0x40 - 0x14)))
  #define uStack_10 (*(undefined4 *)(_frame + (0x40 - 0x10)))
  #define uStack_c (*(undefined4 *)(_frame + (0x40 - 0xc)))
  
  ppcVar3 = local_28;
  puVar1 = (undefined4 *)&STACK0X(0x00000008);
  iVar4 = 10;
  do {
    uVar2 = *puVar1;
    puVar1 = puVar1 + 1;
    *ppcVar3 = (char *)uVar2;
    ppcVar3 = ppcVar3 + 1;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  if ((_DAT_1002e330 == 0) && (cmd != 0)) {
    ImPrintf((char *)IMG_ADDR(0x1001e6d8));
    return 0xffffffff;
  }
  switch(cmd) {
  case 0:
    break;
  case 1:
    _DAT_1002e330 = 0;
    uVar2 = FUN_100063d0();
    return uVar2;
  case 2:
    iVar4 = FUN_10006400((undefined4 *)local_28[0],(int)local_28[1]);
    return iVar4;
  case 3:
    iVar4 = FUN_10006470((undefined4 *)local_28[0]);
    return iVar4;
  case 4:
    uVar2 = FUN_100064d0();
    return uVar2;
  case 5:
    uVar2 = FUN_10006560((int)local_28[0]);
    return uVar2;
  case 6:
    uVar2 = FUN_10006620((int)local_28[0]);
    return uVar2;
  case 7:
    uVar2 = FUN_100067a0();
    return uVar2;
  case 8:
    uVar2 = FUN_100067b0((uint)local_28[0],local_28[1]);
    return uVar2;
  default:
    ImPrintf((char *)IMG_ADDR(0x1001e68c));
    return 0xffffffff;
  }
  if (_DAT_1002e330 != 0) {
    ImPrintf((char *)IMG_ADDR(0x1001e6b4));
    return 0xffffffff;
  }
  _DAT_1002e330 = 1;
  uVar2 = FUN_10006360((int)local_28[0],local_28[1],local_28[2],local_28[3],uStack_18,uStack_14,
                       uStack_10,uStack_c);
  return uVar2;
}
#undef local_28
#undef uStack_10
#undef uStack_14
#undef uStack_18
#undef uStack_c


/* ---- 0x10006360  FUN_10006360 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl
FUN_10006360(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            ,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  int iVar1;
  undefined4 *puVar2;
  
  *(code **)(param_1 + 8) = FUN_100070e0;
  DAT_1001e688 = param_8;
  ImInitFilelist(param_2,param_3,param_4,param_5);
  _DAT_1002df68 = param_6;
  _DAT_1002df6c = param_7;
  puVar2 = &DAT_1002df78;
  for (iVar1 = 0xe4; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  DAT_1002df70 = 0;
  DAT_1002e308 = 0;
  DAT_1002e30c = 0;
  return 0;
}

/* ---- 0x100063d0  FUN_100063d0 ---- */
undefined4 FUN_100063d0(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  FUN_10007110();
  DAT_1002df70 = 0;
  puVar2 = &DAT_1002df78;
  for (iVar1 = 0xe4; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  DAT_1002e308 = 0;
  DAT_1002e30c = 0;
  return 0;
}

/* ---- 0x10006400  FUN_10006400 ---- */
int __cdecl FUN_10006400(undefined4 *param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  
  if (param_2 < 0x39c) {
    ImPrintf(s_SCRIPT_ERR__save_buffer_too_smal_1001e6f8);
    return -1;
  }
  iVar4 = 0xc;
  *param_1 = DAT_1002df70;
  param_1[1] = DAT_1002e308;
  param_1[2] = DAT_1002e30c;
  puVar2 = &DAT_1002df78;
  do {
    uVar1 = *puVar2;
    puVar2 = puVar2 + 1;
    *(undefined4 *)(iVar4 + (int)param_1) = uVar1;
    iVar4 = iVar4 + 4;
  } while ((int)puVar2 < IMG_ADDR(0x1002e308));
  iVar3 = ImSaveFilelist((int)param_1 + iVar4,param_2 - iVar4);
  if (-1 < iVar3) {
    iVar3 = iVar3 + iVar4;
  }
  return iVar3;
}

/* ---- 0x10006470  FUN_10006470 ---- */
int __cdecl FUN_10006470(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  
  ImUnloadAll();
  ImCloseAll();
  iVar4 = 0xc;
  DAT_1002df70 = *param_1;
  DAT_1002e308 = param_1[1];
  DAT_1002e30c = param_1[2];
  puVar2 = &DAT_1002df78;
  do {
    puVar1 = (undefined4 *)(iVar4 + (int)param_1);
    iVar4 = iVar4 + 4;
    *puVar2 = *puVar1;
    puVar2 = puVar2 + 1;
  } while ((int)puVar2 < IMG_ADDR(0x1002e308));
  iVar3 = ImRestoreFilelist(iVar4 + (int)param_1);
  return iVar4 + iVar3;
}

/* ---- 0x100064d0  FUN_100064d0 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
undefined4 FUN_100064d0(void)

{
  uint uVar1;
  uint uVar2;
  
  if (DAT_1002e304 != 0) {
    FUN_10006620(0);
    DAT_1002e304 = 0;
  }
  uVar1 = ImGetNextSound(0);
  if (uVar1 != 0) {
    do {
      uVar2 = ImGetParam(uVar1,0x1800);
      if (uVar2 != 0) {
        uVar2 = ImGetParam(uVar1,0x1900);
        if (uVar2 == 2) break;
      }
      uVar1 = ImGetNextSound(uVar1);
    } while (uVar1 != 0);
    if (uVar1 != 0) goto LAB_10006549;
  }
  if (DAT_1002e308 != 0) {
    FUN_10006620(0);
  }
LAB_10006549:
  ImFlushSounds();
  return 0;
}
#endif


/* ---- 0x10006560  FUN_10006560 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
undefined4 __cdecl FUN_10006560(int param_1)

{
  uint uVar1;
  int *piVar2;
  char *pcVar3;
  uint uVar4;
  uint unaff_retaddr;
  uint in_stack_00000008;
  uint in_stack_0000000c;
  uint in_stack_00000010;
  
  if (param_1 == -1) {
    return (&DAT_1001730c)[DAT_1002df70 * 0x15];
  }
  uVar4 = 0;
  piVar2 = &DAT_1001730c;
  do {
    if (param_1 == *piVar2) {
      ImPrintf((char *)(uVar4 * 0x54 + IMG_ADDR(0x10017310)));
      ImPrintf(&DAT_100171b0);
      uVar1 = DAT_1002df70;
      if ((uVar4 != DAT_1002df70) && (uVar1 = uVar4, DAT_1002e308 == 0)) {
        if (uVar4 == 0) {
          pcVar3 = (char *)0x0;
        }
        else {
          pcVar3 = &DAT_100172e8 + uVar4 * 0x54;
        }
        FUN_100068b0(pcVar3,uVar4,0,unaff_retaddr,param_1,in_stack_00000008,in_stack_0000000c,
                     in_stack_00000010);
      }
      DAT_1002df70 = uVar1;
      return (&DAT_1001730c)[DAT_1002df70 * 0x15];
    }
    piVar2 = piVar2 + 0x15;
    uVar4 = uVar4 + 1;
  } while ((int)piVar2 < IMG_ADDR(0x1001ae70));
  return 0;
}
#endif


/* ---- 0x10006620  FUN_10006620 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
undefined4 __cdecl FUN_10006620(int param_1)

{
  int iVar1;
  int *piVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  uint unaff_retaddr;
  uint in_stack_00000008;
  uint in_stack_0000000c;
  uint in_stack_00000010;
  
  if (param_1 == -1) {
    return (&DAT_1001ae74)[DAT_1002e308 * 0x15];
  }
  iVar4 = param_1;
  if (param_1 == 0) {
    iVar4 = 2000;
  }
  iVar5 = 0;
  piVar2 = &DAT_1001ae74;
  do {
    if (iVar4 == *piVar2) {
      ImPrintf(s_SEQ_NULL_1001ae78 + iVar5 * 0x54);
      ImPrintf(&DAT_100171b0);
      iVar4 = DAT_1002e308;
      iVar1 = DAT_1002e30c;
      if (iVar5 != DAT_1002e308) {
        if (iVar5 == 0) {
          if (DAT_1002e30c == 0) {
            if (DAT_1002df70 == 0) {
              pcVar3 = (char *)0x0;
            }
            else {
              pcVar3 = &DAT_100172e8 + DAT_1002df70 * 0x54;
            }
            FUN_100068b0(pcVar3,DAT_1002df70,1,unaff_retaddr,param_1,in_stack_00000008,
                         in_stack_0000000c,in_stack_00000010);
            DAT_1002e308 = 0;
            iVar4 = DAT_1002e308;
            iVar1 = DAT_1002e30c;
          }
          else {
            FUN_100068b0(&DAT_1001ae50 + DAT_1002e30c * 0x54,0,1,unaff_retaddr,param_1,
                         in_stack_00000008,in_stack_0000000c,in_stack_00000010);
            iVar4 = DAT_1002e30c;
            DAT_1002e308 = DAT_1002e30c;
            DAT_1002e30c = 0;
            (&DAT_1002e25c)[iVar4] = 1;
            iVar1 = DAT_1002e30c;
          }
        }
        else if ((DAT_1002e308 == 0) ||
                ((iVar1 = iVar5, *(int *)(&DAT_1001ae70 + DAT_1002e308 * 0x54) != 4 &&
                 (*(int *)(&DAT_1001ae70 + DAT_1002e308 * 0x54) != 6)))) {
          FUN_100068b0(&DAT_1001ae50 + iVar5 * 0x54,0,1,unaff_retaddr,param_1,in_stack_00000008,
                       in_stack_0000000c,in_stack_00000010);
          DAT_1002e30c = 0;
          (&DAT_1002e25c)[iVar5] = 1;
          iVar4 = iVar5;
          DAT_1002e308 = iVar5;
          iVar1 = DAT_1002e30c;
        }
      }
      DAT_1002e30c = iVar1;
      return (&DAT_1001ae74)[iVar4 * 0x15];
    }
    piVar2 = piVar2 + 0x15;
    iVar5 = iVar5 + 1;
  } while ((int)piVar2 < IMG_ADDR(0x1001bbe8));
  ImPrintf(s_ERR__bogus_sequence____1001e720);
  return 0xffffffff;
}
#endif


/* ---- 0x100067a0  FUN_100067a0 ---- */
undefined4 FUN_100067a0(void)

{
  return 0;
}

/* ---- 0x100067b0  FUN_100067b0 ---- */
undefined4 __cdecl FUN_100067b0(uint param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  undefined4 *puVar5;
  
  if (param_1 == 0xffffffff) {
    if (param_2 == (char *)0x0) {
      ImPause();
      return 0;
    }
    if (param_2 == (char *)0x1) {
      ImResume();
      return 0;
    }
    if (param_2 == (char *)0xffffffff) {
      puVar5 = &DAT_1002df78;
      for (iVar2 = 0xe4; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar5 = 0;
        puVar5 = puVar5 + 1;
      }
      return 0;
    }
  }
  else {
    if (param_1 == 10000) {
      pcVar4 = &DAT_100172e8;
      do {
        cVar1 = *pcVar4;
        *param_2 = cVar1;
        pcVar3 = pcVar4;
        while (param_2 = param_2 + 1, cVar1 != '\0') {
          pcVar3 = pcVar3 + 1;
          cVar1 = *pcVar3;
          *param_2 = cVar1;
        }
        pcVar4 = pcVar4 + 0x54;
      } while ((int)pcVar4 < IMG_ADDR(0x1001ae4c));
      pcVar4 = &DAT_1001ae50;
      do {
        iVar2 = 1;
        do {
          cVar1 = *pcVar4;
          *param_2 = cVar1;
          pcVar3 = pcVar4;
          while (param_2 = param_2 + 1, cVar1 != '\0') {
            pcVar3 = pcVar3 + 1;
            cVar1 = *pcVar3;
            *param_2 = cVar1;
          }
          pcVar4 = pcVar4 + 0x54;
          iVar2 = iVar2 + -1;
        } while (iVar2 != 0);
      } while ((int)pcVar4 < IMG_ADDR(0x1001bbc4));
      return 0xde;
    }
    if (param_1 < 0xe4) {
      if (param_2 != (char *)0xffffffff) {
        ImPrintf(s_Set_attr__lu_to__lu____1001e750,param_1,param_2);
        (&DAT_1002df78)[param_1] = param_2;
      }
      return (&DAT_1002df78)[param_1];
    }
    ImPrintf(s_ERR__bogus_attribute____1001e738);
  }
  return 0;
}

/* ---- 0x100068b0  FUN_100068b0 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void __cdecl
FUN_100068b0(char *param_1,uint param_2,int param_3,uint param_4,int param_5,uint param_6,
            uint param_7,uint param_8)

{
  char *pcVar1;
  char cVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  undefined1 *puVar7;
  int iVar8;
  int unaff_EBX;
  int unaff_EBP;
  int iVar9;
  int unaff_ESI;
  int unaff_EDI;
  undefined1 *puVar10;
  char *pcVar11;
  bool bVar12;
  int unaff_retaddr;
  int in_stack_00000024;
  
  pcVar1 = param_1;
  if (DAT_1001e688 == 0) {
    return;
  }
  if (param_1 != (char *)0x0) {
    DAT_1002e310 = *param_1;
    pcVar3 = &DAT_1002e311;
    if (DAT_1002e310 != '\0') {
      do {
        cVar2 = pcVar3[(int)(param_1 + -0x1002e310)];
        *pcVar3 = cVar2;
        pcVar3 = pcVar3 + 1;
      } while (cVar2 != '\0');
    }
    puVar10 = &DAT_1001bbc8;
    if (DAT_1001bbc8 != '\0') {
      iVar9 = 0x12748;
      cVar2 = DAT_1001bbc8;
LAB_10006904:
      iVar8 = 0;
      for (puVar7 = puVar10; (cVar2 != '\0' && (puVar7[iVar9] == cVar2)); puVar7 = puVar7 + 1) {
        cVar2 = puVar7[1];
        iVar8 = iVar8 + 1;
      }
      if (((iVar8 == 0) || ((&DAT_1002e310)[iVar8] != '\0')) || (puVar10[iVar8] != '\0'))
      goto LAB_1000692f;
      DAT_1002e310 = puVar10[0x20];
      pcVar3 = puVar10 + 0x20;
      pcVar11 = &DAT_1002e311;
      cVar2 = DAT_1002e310;
      while (cVar2 != '\0') {
        pcVar3 = pcVar3 + 1;
        cVar2 = *pcVar3;
        *pcVar11 = cVar2;
        pcVar11 = pcVar11 + 1;
      }
    }
  }
LAB_1000695e:
  bVar12 = param_1 != (char *)0x0;
  param_1 = (char *)0x0;
  if ((bVar12) && (param_2 != 0)) {
    if (*(uint *)(pcVar1 + 0x40) != 0) {
      param_2 = *(uint *)(pcVar1 + 0x40);
    }
    param_1 = *(char **)(&DAT_1002df84 + param_2 * 4);
    if (*(int *)(pcVar1 + 0x44) != 0) {
      if ((param_1 == (char *)0x0) && (1 < *(int *)(pcVar1 + 0x44))) {
        *(undefined4 *)(&DAT_1002df84 + param_2 * 4) = 2;
      }
      else {
        *(char **)(&DAT_1002df84 + param_2 * 4) = param_1 + 1;
        if (*(int *)(pcVar1 + 0x44) < (int)(param_1 + 1)) {
          *(undefined4 *)(&DAT_1002df84 + param_2 * 4) = 1;
        }
      }
    }
  }
  if (param_1 == (char *)0x0) {
    param_1 = (char *)0x64;
  }
  for (uVar4 = ImGetNextSound(0); uVar4 != 0; uVar4 = ImGetNextSound(uVar4)) {
    uVar5 = ImGetParam(uVar4,0x400);
    if ((uVar5 == 4) && (uVar5 = ImGetParam(uVar4,0x1800), uVar5 == 0)) {
      ImFadeParam(uVar4,0x600,0,0x78);
    }
  }
  uVar4 = ImGetNextSound(0);
  while ((uVar5 = 0, uVar4 != 0 &&
         ((uVar5 = ImGetParam(uVar4,0x1800), uVar5 == 0 ||
          (uVar6 = ImGetParam(uVar4,0x1900), uVar5 = uVar4, uVar6 != 2))))) {
    uVar4 = ImGetNextSound(uVar4);
  }
  if (pcVar1 == (char *)0x0) {
    if (uVar5 == 0) {
      return;
    }
    ImFadeParam(uVar5,0x600,0,0x78);
    return;
  }
  param_2 = *(uint *)(pcVar1 + 0x48);
  if (param_2 == 0) {
    param_2 = 1000;
  }
  iVar9 = (int)(param_2 * 3) / 0x32;
  switch(*(undefined4 *)(pcVar1 + 0x20)) {
  case 0:
    ImPrintf(s_Trans_null____1001e860);
    return;
  default:
    ImPrintf(s_SCRIPT_ERR__bogus_trans_type____1001e768);
    break;
  case 2:
  case 3:
  case 4:
  case 10:
  case 0xb:
  case 0xc:
    ImPrintf(s_opening_1001e84c);
    ImPrintf(&DAT_1002e310);
    ImPrintf(&DAT_100171b0);
    uVar4 = ImOpenSound(&DAT_1002e310,0);
    if (uVar4 == 0) {
      ImPrintf(s_SCRIPT_ERR__Unable_to_open_1001e830);
      ImPrintf(&DAT_1002e310);
      ImPrintf(&DAT_100171b0);
      if (uVar5 == 0) {
        return;
      }
      ImFadeParam(uVar5,0x600,0,0x3c);
      return;
    }
    if (*(int *)(pcVar1 + 0x20) == 4) {
      DAT_1002e304 = 0;
      ImSetTrigger(uVar4,&DAT_1001e858,0,unaff_EBX,unaff_retaddr,(int)param_1,param_2,param_3,
                   param_4,param_5,param_6,param_7,param_8);
    }
    ImPrintf(s_HOOK__lu____1001e824,param_4);
    if (uVar5 == 0) {
      ImPrintf(s_No_stream_sound____1001e7ac);
      iVar8 = ImStartStream(uVar4,0x7e,2);
      if (iVar8 != 0) {
        ImPrintf(s_SCRIPT_ERR__failed_start_stream__1001e788);
      }
      ImSetParam(uVar4,0x600,0);
      ImFadeParam(uVar4,0x600,*(uint *)(pcVar1 + 0x4c),iVar9);
      ImSetParam(uVar4,0x700,*(uint *)(pcVar1 + 0x50));
      ImSetParam(uVar4,0x400,4);
      ImSetHook(uVar4,param_7);
      goto LAB_10007019;
    }
    if (*(int *)(pcVar1 + 0x20) == 2) {
      ImSwitchStream(uVar5,uVar4,param_6,0,0);
      ImPrintf(s_FADE__lu____1001e818,param_6);
      ImPrintf(s_vol__lu____1001e80c);
      ImFadeParam(uVar4,0x600,*(uint *)(pcVar1 + 0x4c),iVar9);
      ImFadeParam(uVar4,0x700,*(uint *)(pcVar1 + 0x50),iVar9);
      ImSetParam(uVar4,0x400,4);
      ImSetHook(uVar4,param_7);
      ImProcessStreams();
      goto LAB_10007019;
    }
    if (uVar5 == uVar4) {
      ImFadeParam(uVar4,0x600,*(uint *)(pcVar1 + 0x4c),iVar9);
      ImPrintf(s_fading_VOL__lu____1001e7d0,*(undefined4 *)(pcVar1 + 0x4c));
      if (*(uint *)(pcVar1 + 0x50) != 0) {
        ImFadeParam(uVar4,0x700,*(uint *)(pcVar1 + 0x50),iVar9);
        ImPrintf(s_and_PAN__lu____1001e7c0);
      }
      goto LAB_10007019;
    }
    if (((param_7 == 0) && (*(int *)(pcVar1 + 0x40) != 0)) &&
       (*(int *)(pcVar1 + 0x40) == *(int *)(&DAT_10017328 + DAT_1002df70 * 0x54))) {
      ImSwitchStream(uVar5,uVar4,param_6,0,1);
      ImFadeParam(uVar4,0x600,*(uint *)(pcVar1 + 0x4c),iVar9);
      ImFadeParam(uVar4,0x700,*(uint *)(pcVar1 + 0x50),iVar9);
      ImSetParam(uVar4,0x400,4);
      if (param_5 == 100) {
        ImSetHook(uVar4,100);
        ImProcessStreams();
        goto LAB_10007019;
      }
LAB_10006f42:
      ImProcessStreams();
    }
    else {
      iVar8 = *(int *)(pcVar1 + 0x20);
      if (iVar8 == 10) {
        ImSetTrigger(uVar5,&DAT_1001e804,0x1a,uVar5,uVar4,param_6,1,0,unaff_retaddr,(int)param_1,
                     param_2,param_3,param_4);
        ImSetTrigger(uVar5,&DAT_1001e804,0xe,uVar4,0x600,*(int *)(pcVar1 + 0x4c),iVar9,unaff_retaddr
                     ,(int)param_1,param_2,param_3,param_4,param_5);
        ImSetTrigger(uVar5,&DAT_1001e804,0xe,uVar4,0x700,*(int *)(pcVar1 + 0x50),iVar9,unaff_retaddr
                     ,(int)param_1,param_2,param_3,param_4,param_5);
        ImSetTrigger(uVar5,&DAT_1001e804,0xc,uVar4,0x400,4,unaff_retaddr,(int)param_1,param_2,
                     param_3,param_4,param_5,param_6);
      }
      else {
        if (iVar8 == 0xb) {
          ImSetTrigger(uVar5,s_exit2_1001e7fc,0x1a,uVar5,uVar4,param_6,1,0,unaff_retaddr,
                       (int)param_1,param_2,param_3,param_4);
          ImSetTrigger(uVar5,s_exit2_1001e7fc,0xe,uVar4,0x600,*(int *)(pcVar1 + 0x4c),iVar9,
                       unaff_retaddr,(int)param_1,param_2,param_3,param_4,param_5);
          ImSetTrigger(uVar5,s_exit2_1001e7fc,0xe,uVar4,0x700,*(int *)(pcVar1 + 0x50),iVar9,
                       unaff_retaddr,(int)param_1,param_2,param_3,param_4,param_5);
          ImSetTrigger(uVar5,s_exit2_1001e7fc,0xc,uVar4,0x400,4,unaff_retaddr,(int)param_1,param_2,
                       param_3,param_4,param_5,param_6);
          ImSetTrigger(uVar5,s_exit2_1001e7fc,0xf,uVar4,param_5,unaff_retaddr,(int)param_1,param_2,
                       param_3,param_4,param_5,param_6,param_7);
          ImProcessStreams();
          goto LAB_10007019;
        }
        if (iVar8 != 0xc) {
          ImSwitchStream(uVar5,uVar4,param_6,0,0);
          ImPrintf(s_FADE__lu____1001e818,param_6);
          ImPrintf(s_vol__lu____1001e80c);
          ImFadeParam(uVar4,0x600,*(uint *)(pcVar1 + 0x4c),iVar9);
          ImFadeParam(uVar4,0x700,*(uint *)(pcVar1 + 0x50),iVar9);
          ImPrintf(s_set_pan__lu____1001e7e4);
          ImSetParam(uVar4,0x400,4);
          ImSetHook(uVar4,param_8);
          goto LAB_10006f42;
        }
        ImSetHook(uVar5,99);
        ImSetTrigger(uVar5,s_clear_1001e7f4,0xf,uVar5,0x80,unaff_retaddr,(int)param_1,param_2,
                     param_3,param_4,param_5,param_6,param_7);
        ImSetTrigger(uVar5,&DAT_1001e804,0x1a,uVar5,uVar4,param_6,1,0,unaff_retaddr,(int)param_1,
                     param_2,param_3,param_4);
        ImSetTrigger(uVar5,&DAT_1001e804,0xe,uVar4,0x600,*(int *)(pcVar1 + 0x4c),iVar9,unaff_retaddr
                     ,(int)param_1,param_2,param_3,param_4,param_5);
        ImSetTrigger(uVar5,&DAT_1001e804,0xe,uVar4,0x700,*(int *)(pcVar1 + 0x50),iVar9,unaff_retaddr
                     ,(int)param_1,param_2,param_3,param_4,param_5);
        ImSetTrigger(uVar5,&DAT_1001e804,0xc,uVar4,0x400,4,unaff_retaddr,(int)param_1,param_2,
                     param_3,param_4,param_5,param_6);
        ImPrintf(s_HOOK__lu____1001e824,param_5);
      }
      ImSetTrigger(uVar5,&DAT_1001e804,0xf,uVar4,(int)param_1,param_2,param_3,param_4,param_5,
                   param_6,param_7,param_8,in_stack_00000024);
      ImProcessStreams();
    }
LAB_10007019:
    ImCloseSound(uVar4);
    ImSetParam(uVar4,0x400,4);
    return;
  case 5:
    break;
  case 6:
    DAT_1002e304 = 0;
    ImSetTrigger(0xbc6150,&DAT_1001e858,0,unaff_EDI,unaff_ESI,unaff_EBP,unaff_EBX,unaff_retaddr,
                 (int)param_1,param_2,param_3,param_4,param_5);
    return;
  case 7:
    if (uVar5 != 0) {
      ImFadeParam(uVar5,0x600,0,0x3c);
      return;
    }
    break;
  case 8:
    if (uVar5 != 0) {
      ImSetHook(uVar5,100);
      return;
    }
    break;
  case 9:
    if (uVar5 != 0) {
      ImSetHook(uVar5,99);
    }
    DAT_1002e304 = 0;
    ImSetTrigger(uVar5,&DAT_1001e858,0,unaff_EDI,unaff_ESI,unaff_EBP,unaff_EBX,unaff_retaddr,
                 (int)param_1,param_2,param_3,param_4,param_5);
    return;
  }
  return;
LAB_1000692f:
  cVar2 = puVar10[0x40];
  puVar10 = puVar10 + 0x40;
  iVar9 = iVar9 + -0x40;
  if (cVar2 == '\0') goto LAB_1000695e;
  goto LAB_10006904;
}
#endif


/* ---- 0x100070e0  FUN_100070e0 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void __cdecl FUN_100070e0(char *marker)

{
  char *in_stack_00000008;
  
  ImPrintf(s_CALLBACK__1001e898);
  if (*in_stack_00000008 == '_') {
    DAT_1002e304 = 1;
    return;
  }
  ImPrintf(s_ERR_callback_got_marker______end_1001e870);
  return;
}
#endif


/* ---- 0x10007110  FUN_10007110 ---- */
void FUN_10007110(void)

{
  if (DAT_1001e688 != 0) {
    ImStopAllSounds();
    ImUnloadAll();
    ImCloseAll();
    return;
  }
  return;
}

/* ---- 0x100089b0  Im_SoundsFindByName ---- */
/* Unidentified function of iMUSE_sounds.c (sound resource slots) */

undefined4 __cdecl Im_SoundsFindByName(undefined4 param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  bool bVar5;
  
  iVar3 = -1;
  iVar1 = (**(code **)(DAT_10033510 + 0x30))(param_1,&DAT_1001e900);
  if (iVar1 == 0) {
    Im_SoundsFreeSlot((int)param_2);
  }
  else if (param_2 != (char *)0x0) {
    if (((param_2 == DAT_10031e74) || (param_2 == DAT_10031e78)) || (param_2 == DAT_10031e7c)) {
      (**(code **)(DAT_10033510 + 0x34))(iVar1);
      return 1;
    }
    if (param_2 == (char *)0x2710) {
      DAT_10031e70 = param_2;
      iVar3 = 0;
      param_2 = &DAT_1002f3e8;
    }
    else if (DAT_10031e74 == (char *)0x0) {
      DAT_10031e74 = param_2;
      iVar3 = 1;
      param_2 = &DAT_1002e340;
    }
    else if (DAT_10031e78 == (char *)0x0) {
      DAT_10031e78 = param_2;
      iVar3 = 2;
      param_2 = &DAT_1002ec18;
    }
    else if (DAT_10031e7c == (char *)0x0) {
      DAT_10031e7c = param_2;
      iVar3 = 3;
      param_2 = &DAT_1002fbd0;
    }
    if (-1 < iVar3) {
      (**(code **)(DAT_10033510 + 0x4c))(iVar1,0,2);
      iVar2 = (**(code **)(DAT_10033510 + 0x48))(iVar1);
      (**(code **)(DAT_10033510 + 0x4c))(iVar1,0,0);
      if (iVar2 < 0x7d1) {
        (**(code **)(DAT_10033510 + 0x38))(iVar1,param_2,iVar2);
        iVar2 = 4;
        bVar5 = true;
        pcVar4 = &DAT_1001e994;
        do {
          if (iVar2 == 0) break;
          iVar2 = iVar2 + -1;
          bVar5 = *param_2 == *pcVar4;
          param_2 = param_2 + 1;
          pcVar4 = pcVar4 + 1;
        } while (bVar5);
        if (!bVar5) {
          switch(iVar3) {
          case 0:
            DAT_10031e70 = (char *)0x0;
            return 0;
          case 1:
            DAT_10031e74 = (char *)0x0;
            return 0;
          case 2:
            DAT_10031e78 = (char *)0x0;
            return 0;
          case 3:
            DAT_10031e7c = (char *)0x0;
            return 0;
          }
        }
      }
    }
  }
  if (iVar1 != 0) {
    (**(code **)(DAT_10033510 + 0x34))(iVar1);
  }
  return 0;
}

/* ---- 0x10008b60  Im_SoundsFreeSlot ---- */
/* Unidentified function of iMUSE_sounds.c (sound resource slots) */

void __cdecl Im_SoundsFreeSlot(int param_1)

{
  if (param_1 == DAT_10031e70) {
    DAT_10031e70 = 0;
  }
  if (param_1 == DAT_10031e74) {
    DAT_10031e74 = 0;
  }
  if (param_1 == DAT_10031e78) {
    DAT_10031e78 = 0;
  }
  if (param_1 == DAT_10031e7c) {
    DAT_10031e7c = 0;
  }
  return;
}

/* ---- 0x10008bb0  iMUSE_GetPhoneme ---- */
int iMUSE_GetPhoneme(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  
                    /* 0x8bb0  78  iMUSE_GetPhoneme */
  if (param_1 == DAT_10031e70) {
    iVar1 = SoundGetVoiceTime();
    iVar1 = FUN_10008c40(param_1,iVar1 + param_2);
    return iVar1;
  }
  if (((param_1 == DAT_10031e74) || (param_1 == DAT_10031e78)) || (param_1 == DAT_10031e7c)) {
    iVar1 = 0;
    iVar4 = 0;
    piVar2 = &DAT_10031548;
    do {
      if (iVar1 != 0) goto LAB_10008c0e;
      if (*piVar2 == param_1) {
        iVar1 = iVar4 + 100;
      }
      piVar2 = piVar2 + 0x10;
      iVar4 = iVar4 + 1;
    } while ((int)piVar2 < IMG_ADDR(0x10031d48));
    if (iVar1 != 0) {
LAB_10008c0e:
      uVar3 = ImGetParam(iVar1,0x1a00);
      iVar1 = FUN_10008c40(param_1,uVar3 + param_2);
      return iVar1;
    }
  }
  return 0;
}

/* ---- 0x10008c40  FUN_10008c40 ---- */
int __cdecl FUN_10008c40(int param_1,int param_2)

{
  undefined *puVar1;
  short *psVar2;
  int iVar3;
  int iVar4;
  
  if (param_1 == 10000) {
    if (DAT_10031e70 == 0) {
      return 0;
    }
    puVar1 = &DAT_1002f3e8;
  }
  else if (param_1 == DAT_10031e74) {
    puVar1 = &DAT_1002e340;
  }
  else if (param_1 == DAT_10031e78) {
    puVar1 = &DAT_1002ec18;
  }
  else {
    if (param_1 != DAT_10031e7c) {
      return 0;
    }
    puVar1 = &DAT_1002fbd0;
  }
  iVar3 = param_2 >> 4;
  psVar2 = (short *)(puVar1 + 8);
  iVar4 = 0;
  if (0 < *(int *)(puVar1 + 4)) {
    while (*psVar2 <= iVar3) {
      if (iVar3 < psVar2[2]) {
        return (int)psVar2[1];
      }
      if (iVar3 < *psVar2) {
        return 0x5f;
      }
      iVar4 = iVar4 + 1;
      psVar2 = psVar2 + 2;
      if (*(int *)(puVar1 + 4) <= iVar4) {
        return 0x5f;
      }
    }
  }
  return 0x5f;
}

/* ---- 0x10008ce0  FUN_10008ce0 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_10008ce0(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint unaff_ESI;
  uint unaff_EDI;
  bool bVar5;
  #define auStack_8 (*(undefined1 (*)[8])(_frame + (0x20 - 0x8)))
  
  iVar1 = timeGetDevCaps(auStack_8,8);
  if (iVar1 == 0) {
    uVar2 = unaff_EDI;
    if (unaff_EDI < 0x33) {
      uVar2 = 0x32;
    }
    if ((uVar2 < unaff_ESI) && (unaff_ESI = unaff_EDI, unaff_EDI < 0x33)) {
      unaff_ESI = 0x32;
    }
    _DAT_1002e338 = (int)(1000 / (ulonglong)unaff_ESI);
    _DAT_10031520 = unaff_ESI;
    timeBeginPeriod(unaff_ESI);
    _DAT_10031d28 = timeSetEvent(_DAT_1002e338,0,((unsigned)(uintptr_t)FUN_10008e00),0xf,1);
    iVar3 = timeGetTime();
    _DAT_10031e84 = 0;
    iVar1 = 2;
    do {
      if (_DAT_10031e84 != 0) {
        return _DAT_10031e84;
      }
      iVar4 = timeGetTime();
      uVar2 = iVar4 - iVar3;
      while (uVar2 < 4000) {
        if (_DAT_10031e84 != 0) goto LAB_10008de9;
        iVar4 = timeGetTime();
        uVar2 = iVar4 - iVar3;
      }
      if (_DAT_10031e84 == 0) {
        timeKillEvent(_DAT_10031d28);
        timeEndPeriod(_DAT_10031520);
        timeBeginPeriod(_DAT_10031520);
        _DAT_10031d28 = timeSetEvent(_DAT_1002e338,0,((unsigned)(uintptr_t)FUN_10008e00),0xf,1);
        iVar3 = timeGetTime();
      }
LAB_10008de9:
      bVar5 = iVar1 != 0;
      iVar1 = iVar1 + -1;
    } while (bVar5);
    if (_DAT_10031e84 != 0) {
      return _DAT_10031e84;
    }
  }
  return 0;
}
#undef auStack_8

#endif


/* ---- 0x10008e00  FUN_10008e00 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __stdcall FUN_10008e00(int a1,int a2,int a3,int a4,int a5)

{
  undefined4 uVar1;
  
  _DAT_10031e80 = 1;
  _DAT_10031e84 = _DAT_10031e84 + 1;
  uVar1 = ImHeartbeat();
  _DAT_10031e80 = 0;
  return uVar1;
}

/* ---- 0x10008e30  FUN_10008e30 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_10008e30(void)

{
  timeKillEvent(_DAT_10031d28);
  timeEndPeriod(_DAT_10031520);
  FUN_10008e00(1,2,3,4,5);
  return;
}

/* ---- 0x10008e60  FUN_10008e60 ---- */
void FUN_10008e60(void)

{
  undefined1 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar1 = &DAT_10031ce8;
  iVar2 = 0x20;
  do {
    if ((puVar1 != (undefined1 *)0x0) && (*(int *)(puVar1 + 0x28) != 0)) {
      Im_SoundsFreeSlot(*(int *)(puVar1 + 0x20));
      if (*(int *)(puVar1 + 0x28) != 0) {
        (**(code **)(DAT_10033510 + 0x24))(*(int *)(puVar1 + 0x28));
      }
    }
    puVar1 = puVar1 + -0x40;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  DAT_10031d3c = 0;
  puVar3 = (undefined4 *)&DAT_10031528;
  for (iVar2 = 0x200; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  return;
}

/* ---- 0x100093d0  Im_SoundsPrepare ---- */
/* Decodes the header/first block of a loaded sound and applies FX */

void __cdecl Im_SoundsPrepare(uint param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined2 *puVar1;
  uint uVar2;
  int iVar3;
  undefined1 *puVar4;
  bool bVar5;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  if ((0x456 < (int)param_1) && ((int)param_1 < 0x557)) {
    puVar4 = &DAT_10031ce8;
    iVar3 = 0x1f;
    while (*(uint *)(puVar4 + 0x20) != param_1) {
      puVar4 = puVar4 + -0x40;
      bVar5 = iVar3 == 0;
      iVar3 = iVar3 + -1;
      if (bVar5) {
        return;
      }
    }
    if ((*(int *)(puVar4 + 0x28) != 0) && (*(int *)(puVar4 + 0x2c) != 0)) {
      Im_VimaDecompress(*(uint **)(puVar4 + 0x30),(int *)0x0,&local_c,&local_8,&local_4,(int *)0x0,
                        &param_1);
      if ((local_c == 0x5622) && (((local_8 == 0x10 && (local_4 == 1)) && (0 < (int)param_1)))) {
        puVar1 = (undefined2 *)
                 (**(code **)(DAT_10033510 + 0x20))
                           (param_1 * 2 + 0x50,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0x7eb);
        if (puVar1 != (undefined2 *)0x0) {
          uVar2 = Im_ApplyFXPreset((undefined2 *)(*(int *)(puVar4 + 0x2c) + 0x50),param_1,puVar1,
                                   (int *)0x0,(int *)0x0,0);
          (**(code **)(DAT_10033510 + 0x24))(*(undefined4 *)(puVar4 + 0x28));
          *(undefined2 **)(puVar4 + 0x28) = puVar1;
          if (uVar2 == 2) {
            param_1 = param_1 << 1;
          }
          *(uint *)(puVar4 + 0x34) = param_1;
          Im_DecodeSoundBlock((undefined4 *)(param_1 + (int)puVar1),3,0x5622,0x10,uVar2,param_1);
          *(uint *)(puVar4 + 0x30) = param_1 + *(int *)(puVar4 + 0x28);
          *(undefined1 *)(param_1 + *(int *)(puVar4 + 0x28) + 0x1f) = 1;
          *(undefined4 *)(puVar4 + 0x38) = 1;
          *(int *)(puVar4 + 0x2c) = *(int *)(puVar4 + 0x28) + -0x50;
        }
        iVar3 = timeGetTime();
        *(int *)(puVar4 + 0x24) = iVar3;
      }
    }
  }
  return;
}
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x10009530  FUN_10009530 ---- */
undefined4 FUN_10009530(int param_1)

{
  if ((99 < param_1) && (param_1 < 0x85)) {
    return *(undefined4 *)((param_1 + -100) * 0x40 + IMG_ADDR(0x10031554));
  }
  return 0;
}

/* ---- 0x10009560  FUN_10009560 ---- */
undefined4 FUN_10009560(int param_1)

{
  if ((99 < param_1) && (param_1 < 0x85)) {
    return *(undefined4 *)((param_1 + -100) * 0x40 + IMG_ADDR(0x10031558));
  }
  return 0;
}

/* ---- 0x100095d0  grimSound_LipSyncLoad ---- */
uint * grimSound_LipSyncLoad(uint *param_1)

{
  int *piVar1;
  uint *puVar2;
  uint uVar3;
  undefined4 *puVar4;
  int iVar5;
  uint *puVar6;
  
                    /* 0x95d0  74  grimSound_LipSyncLoad */
  if (param_1 == (uint *)0x0) {
    (**(code **)(DAT_10033510 + 0x18))(IMG_ADDR(0x1001e99c),s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0x845);
  }
  piVar1 = Im_SoundsLoad(param_1,&DAT_1001e900);
  if (piVar1 == (int *)0x0) {
    return (uint *)0x0;
  }
  puVar2 = (uint *)(**(code **)(DAT_10033510 + 0x20))
                             (0x28,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0x851);
  puVar6 = puVar2;
  for (iVar5 = 10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  Im_MemCopy(puVar2,param_1,0x1f);
  *(undefined1 *)((int)puVar2 + 0x1f) = 0;
  iMUSE_sounds__9e40((undefined *)piVar1,0,2);
  uVar3 = iMUSE_sounds__9e10((undefined *)piVar1);
  iMUSE_sounds__9e40((undefined *)piVar1,0,0);
  puVar2[8] = uVar3;
  puVar4 = (undefined4 *)
           (**(code **)(DAT_10033510 + 0x20))(uVar3,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0x85e)
  ;
  puVar2[9] = (uint)puVar4;
  Im_SoundsReadBlock(piVar1,puVar4,uVar3);
  Im_SoundsUnload(piVar1);
  return puVar2;
}

/* ---- 0x100096b0  grimSound_LipSyncFree ---- */
undefined4 __cdecl grimSound_LipSyncFree(int param_1)

{
  undefined4 uVar1;
  
                    /* 0x96b0  73  grimSound_LipSyncFree */
  if (param_1 == 0) {
    (**(code **)(DAT_10033510 + 0x18))(IMG_ADDR(0x1001e9b8),s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0x87c);
  }
  if (*(int *)(param_1 + 0x24) != 0) {
    (**(code **)(DAT_10033510 + 0x24))(*(int *)(param_1 + 0x24));
    *(undefined4 *)(param_1 + 0x24) = 0;
  }
  uVar1 = (**(code **)(DAT_10033510 + 0x24))(param_1);
  return uVar1;
}

/* ---- 0x10009700  FUN_10009700 ---- */
void FUN_10009700(void)

{
  return;
}

/* ---- 0x10009710  Im_SoundsLoad ---- */
/* iMUSE_sounds.c: opens the sound file into a slot */

int * __cdecl Im_SoundsLoad(uint *param_1,char *param_2)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int *piVar2;
  int iVar3;
  byte *pbVar4;
  uint uVar5;
  ushort uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  char *pcVar10;
  char *pcVar11;
  bool bVar12;
  #define uStack_14 (*(undefined4 *)(_frame + (0x30 - 0x14)))
  #define iStack_10 (*(int *)(_frame + (0x30 - 0x10)))
  #define iStack_c (*(int *)(_frame + (0x30 - 0xc)))
  #define acStack_8 (*(char (*)[4])(_frame + (0x30 - 0x8)))
  #define pbStack_4 (*(byte **)(_frame + (0x30 - 0x4)))
  
  if (((*param_2 == 'w') || (*param_2 == 'a')) || (param_2[1] == '+')) {
    piVar2 = (int *)(**(code **)(DAT_10033510 + 0x30))(param_1,param_2);
    return piVar2;
  }
  piVar2 = (int *)(**(code **)(DAT_10033510 + 0x30))(param_1,param_2);
  if (piVar2 == (int *)0x0) {
    return (int *)0x0;
  }
  (**(code **)(DAT_10033510 + 0x38))(piVar2,acStack_8,4);
  iVar7 = 4;
  bVar12 = true;
  pcVar10 = acStack_8;
  pcVar11 = &DAT_10017098;
  do {
    if (iVar7 == 0) break;
    iVar7 = iVar7 + -1;
    bVar12 = *pcVar10 == *pcVar11;
    pcVar10 = pcVar10 + 1;
    pcVar11 = pcVar11 + 1;
  } while (bVar12);
  if (!bVar12) {
    (**(code **)(DAT_10033510 + 0x4c))(piVar2,0,0);
    return piVar2;
  }
  if (DAT_10031e8c == 0) {
    InitializeCriticalSection(IMG_ADDR(0x1002fbb8));
    DAT_10031e8c = 1;
  }
  EnterCriticalSection(IMG_ADDR(0x1002fbb8));
  iVar7 = *(int *)(&DAT_100303a0 + DAT_10031e88 * 0x8c);
  iVar8 = DAT_10031e88;
  while (iVar7 != 0) {
    uVar9 = (int)(iVar8 + 1U) >> 0x1f;
    iVar3 = ((iVar8 + 1U ^ uVar9) - uVar9 & 0x1f ^ uVar9) - uVar9;
    if (iVar3 == DAT_10031e88) break;
    iVar8 = iVar3;
    iVar7 = *(int *)(&DAT_100303a0 + iVar3 * 0x8c);
  }
  iVar7 = iVar8 * 0x8c;
  if (*(int *)(&DAT_100303a0 + iVar8 * 0x8c) == 0) {
    DAT_10031e88 = iVar8;
    LeaveCriticalSection(IMG_ADDR(0x1002fbb8));
    *(int **)(&DAT_100303a0 + iVar7) = piVar2;
    *(undefined4 *)(&DAT_100303a8 + iVar7) = 0;
    (**(code **)(DAT_10033510 + 0x38))(piVar2,&param_2,2);
    uVar6 = CONCAT11((char)param_2,(char)((uint)param_2 >> 8));
    param_2 = (char *)(uint)uVar6;
    *(uint *)(&DAT_100303ac + iVar7) = (uint)uVar6;
    (**(code **)(DAT_10033510 + 0x4c))(piVar2,(int)param_2 * 9 + 6,0);
    PIECE(uStack_14,0,2) = PIECE(uStack_14,1,2);
    (**(code **)(DAT_10033510 + 0x38))(piVar2,&uStack_14,2);
    uStack_14 = (uint)CONCAT11((char)(undefined2)uStack_14,
                               (char)((ushort)(undefined2)uStack_14 >> 8));
    iStack_c = ((uint)param_2 & 0xffff) * 9;
    pbVar4 = (byte *)(**(code **)(DAT_10033510 + 0x20))
                               (iStack_c,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0x956);
    pbStack_4 = pbVar4;
    iVar3 = (**(code **)(DAT_10033510 + 0x20))
                      ((uStack_14 & 0xffff) + (((uint)param_2 & 0xffff) + 1) * 0x14,
                       s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0x958);
    *(int *)(&DAT_100303b0 + iVar7) = iVar3;
    iVar8 = iVar3 + (uStack_14 & 0xffff);
    *(int *)(&DAT_100303b4 + iVar7) = iVar8;
    iVar8 = iVar8 + 4 + ((uint)param_2 & 0xffff) * 4;
    *(int *)(&DAT_100303b8 + iVar7) = iVar8;
    iVar8 = iVar8 + 4 + ((uint)param_2 & 0xffff) * 4;
    *(int *)(&DAT_100303bc + iVar7) = iVar8;
    iVar8 = iVar8 + 4 + ((uint)param_2 & 0xffff) * 4;
    *(int *)(&DAT_100303c0 + iVar7) = iVar8;
    *(uint *)(&DAT_100303c4 + iVar7) = iVar8 + 4 + ((uint)param_2 & 0xffff) * 4;
    (**(code **)(DAT_10033510 + 0x38))(piVar2,iVar3,uStack_14 & 0xffff);
    (**(code **)(DAT_10033510 + 0x4c))(piVar2,6,0);
    (**(code **)(DAT_10033510 + 0x38))(piVar2,pbVar4,iStack_c);
    iVar3 = 0;
    iStack_10 = ((uint)param_2 & 0xffff) * 9 + 8 + (uStack_14 & 0xffff);
    iVar8 = 0;
    if (((uint)param_2 & 0xffff) != 0) {
      do {
        pcVar10 = *(char **)(&DAT_100303b0 + iVar7);
        for (uVar9 = (uint)*pbVar4; uVar9 != 0; uVar9 = uVar9 - 1) {
          cVar1 = *pcVar10;
          while (pcVar10 = pcVar10 + 1, cVar1 != '\0') {
            cVar1 = *pcVar10;
          }
        }
        *(char **)(*(int *)(&DAT_100303b4 + iVar7) + iVar8 * 4) = pcVar10;
        uVar9 = *(uint *)(pbVar4 + 1);
        uVar5 = (uVar9 & 0xff00 | uVar9 << 0x10) << 8 | (uVar9 >> 0x10 | uVar9 & 0xff0000) >> 8;
        *(uint *)(*(int *)(&DAT_100303b8 + iVar7) + iVar8 * 4) = uVar5;
        *(int *)(*(int *)(&DAT_100303bc + iVar7) + iVar8 * 4) = iVar3;
        uVar9 = *(uint *)(pbVar4 + 5);
        iVar3 = iVar3 + uVar5;
        uVar9 = (uVar9 & 0xff00 | uVar9 << 0x10) << 8 | (uVar9 >> 0x10 | uVar9 & 0xff0000) >> 8;
        *(uint *)(*(int *)(&DAT_100303c0 + iVar7) + iVar8 * 4) = uVar9;
        *(int *)(*(int *)(&DAT_100303c4 + iVar7) + iVar8 * 4) = iStack_10;
        iStack_10 = iStack_10 + uVar9;
        iVar8 = iVar8 + 1;
        pbVar4 = pbVar4 + 9;
        iStack_c = iVar3;
      } while (iVar8 < (int)((uint)param_2 & 0xffff));
    }
    *(int *)(*(int *)(&DAT_100303bc + iVar7) + ((uint)param_2 & 0xffff) * 4) = iVar3;
    *(int *)(&DAT_100303a4 + iVar7) = iVar3;
    *(int *)(*(int *)(&DAT_100303c4 + iVar7) + ((uint)param_2 & 0xffff) * 4) = iStack_10;
    (**(code **)(DAT_10033510 + 0x24))(pbStack_4);
    Im_CodecInit((undefined1 *)(iVar7 + IMG_ADDR(0x100303d4)));
    *(undefined4 *)(&DAT_100303cc + iVar7) = 0;
    *(undefined4 *)(&DAT_100303d0 + iVar7) = 0;
    *(undefined4 *)(&DAT_100303c8 + iVar7) = 0xffffffff;
    Im_MemCopy((uint *)(iVar7 + IMG_ADDR(0x100303da)),param_1,0x50);
    (&DAT_10030429)[iVar7] = 0;
    return (int *)(&DAT_100303a0 + iVar7);
  }
  (**(code **)(DAT_10033510 + 0x34))(piVar2);
  return (int *)0x0;
}
#undef acStack_8
#undef iStack_10
#undef iStack_c
#undef pbStack_4
#undef uStack_14


/* ---- 0x10009b20  Im_SoundsUnload ---- */
/* Unidentified function of iMUSE_sounds.c (sound resource slots) */

undefined4 __cdecl Im_SoundsUnload(undefined4 *param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (((undefined4 *)IMG_ADDR(0x1003039f) < param_1) && (param_1 < &DAT_10031520)) {
    uVar1 = *param_1;
    if (param_1[4] != 0) {
      (**(code **)(DAT_10033510 + 0x24))(param_1[4]);
      param_1[4] = 0;
    }
    if (param_1[0xc] != 0) {
      (**(code **)(DAT_10033510 + 0x24))(param_1[0xc]);
    }
    for (iVar2 = 0x23; iVar2 != 0; iVar2 = iVar2 + -1) {
      *param_1 = 0;
      param_1 = param_1 + 1;
    }
    (**(code **)(DAT_10033510 + 0x34))(uVar1);
    return 0;
  }
  uVar1 = (**(code **)(DAT_10033510 + 0x34))(param_1);
  return uVar1;
}

/* ---- 0x10009b90  Im_SoundsReadBlock ---- */
/* Unidentified function of iMUSE_sounds.c (sound resource slots) */

uint __cdecl Im_SoundsReadBlock(undefined4 *param_1,undefined4 *param_2,uint param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint *puVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  char *pcVar9;
  byte *pbVar10;
  undefined4 *puVar11;
  char *pcVar12;
  byte *pbVar13;
  undefined4 *puVar14;
  bool bVar15;
  #define local_c (*(byte **)(_frame + (0x20 - 0xc)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_c = (byte *)0x0;
  local_4 = 0;
  if ((param_1 < &DAT_100303a0) || ((undefined4 *)IMG_ADDR(0x1003151f) < param_1)) {
    uVar7 = (**(code **)(DAT_10033510 + 0x38))(param_1,param_2,param_3);
    return uVar7;
  }
  iVar1 = iMUSE_sounds__9eb0((int)param_1,param_1[2]);
  iVar2 = iMUSE_sounds__9eb0((int)param_1,(param_3 - 1) + param_1[2]);
  if (iVar1 < 0) {
    return 0;
  }
  if (iVar2 < 0) {
    iVar2 = param_1[3] + -1;
    param_3 = param_1[1] - param_1[2];
  }
  iVar8 = iVar1;
  if (param_3 == 0) {
    return 0;
  }
  do {
    if (iVar2 < iVar8) {
      if (local_c != (byte *)0x0) {
        (**(code **)(DAT_10033510 + 0x24))(local_c);
      }
      param_1[2] = param_1[2] + param_3;
      return param_3;
    }
    if ((param_1[0xc] == 0) || (iVar8 != param_1[10])) {
      uVar7 = *(uint *)(param_1[8] + iVar8 * 4);
      if (local_4 < uVar7) {
        local_c = (byte *)(**(code **)(DAT_10033510 + 0x28))
                                    (local_c,uVar7,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0xa14);
        local_4 = *(uint *)(param_1[8] + iVar8 * 4);
      }
      (**(code **)(DAT_10033510 + 0x4c))(*param_1,*(undefined4 *)(param_1[9] + iVar8 * 4),0);
      (**(code **)(DAT_10033510 + 0x38))(*param_1,local_c,*(undefined4 *)(param_1[8] + iVar8 * 4));
      uVar7 = *(uint *)(param_1[6] + iVar8 * 4);
      puVar4 = (uint *)(param_1[6] + iVar8 * 4);
      if ((uint)param_1[0xb] < uVar7) {
        uVar3 = (**(code **)(DAT_10033510 + 0x28))
                          (param_1[0xc],uVar7,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0xa21);
        param_1[0xc] = uVar3;
        puVar4 = (uint *)(param_1[6] + iVar8 * 4);
        param_1[0xb] = *(undefined4 *)(param_1[6] + iVar8 * 4);
      }
      uVar7 = *puVar4;
      iVar5 = 4;
      bVar15 = true;
      pcVar9 = *(char **)(param_1[5] + iVar8 * 4);
      pcVar12 = &DAT_1001e9c0;
      do {
        if (iVar5 == 0) break;
        iVar5 = iVar5 + -1;
        bVar15 = *pcVar9 == *pcVar12;
        pcVar9 = pcVar9 + 1;
        pcVar12 = pcVar12 + 1;
      } while (bVar15);
      if (bVar15) {
        Im_ConvertBlock((byte *)(param_1 + 0xd),(undefined2 *)param_1[0xc],local_c,uVar7);
      }
      else {
        uVar6 = *(uint *)(param_1[8] + iVar8 * 4);
        if (uVar7 < uVar6) {
          uVar6 = uVar7;
        }
        pbVar10 = local_c;
        pbVar13 = (byte *)param_1[0xc];
        for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
          *(undefined4 *)pbVar13 = *(undefined4 *)pbVar10;
          pbVar10 = pbVar10 + 4;
          pbVar13 = pbVar13 + 4;
        }
        for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
          *pbVar13 = *pbVar10;
          pbVar10 = pbVar10 + 1;
          pbVar13 = pbVar13 + 1;
        }
      }
      param_1[10] = iVar8;
    }
    if (iVar1 == iVar2) {
      iVar5 = param_1[2] - *(int *)(param_1[7] + iVar8 * 4);
      uVar7 = param_3;
    }
    else if (iVar8 == iVar1) {
      iVar5 = param_1[2] - *(int *)(param_1[7] + iVar8 * 4);
      uVar7 = *(int *)(param_1[6] + iVar8 * 4) - iVar5;
    }
    else if (iVar8 == iVar2) {
      iVar5 = 0;
      uVar7 = (param_3 - *(int *)(param_1[7] + iVar8 * 4)) + param_1[2];
    }
    else {
      iVar5 = 0;
      uVar7 = *(uint *)(param_1[6] + iVar8 * 4);
    }
    puVar11 = (undefined4 *)(iVar5 + param_1[0xc]);
    puVar14 = param_2;
    for (uVar6 = uVar7 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *puVar14 = *puVar11;
      puVar11 = puVar11 + 1;
      puVar14 = puVar14 + 1;
    }
    param_2 = (undefined4 *)((int)param_2 + uVar7);
    iVar8 = iVar8 + 1;
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined1 *)puVar14 = *(undefined1 *)puVar11;
      puVar11 = (undefined4 *)((int)puVar11 + 1);
      puVar14 = (undefined4 *)((int)puVar14 + 1);
    }
  } while( true );
}
#undef local_4
#undef local_c


/* ---- 0x1000a070  iMUSE_DeclareBufferSizes ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void iMUSE_DeclareBufferSizes
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
               undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12)

{
                    /* 0xa070  75  iMUSE_DeclareBufferSizes */
  _DAT_1001e8a8 = param_1;
  _DAT_1001e8ac = param_2;
  _DAT_1001e8b0 = param_3;
  _DAT_1001e8b4 = param_4;
  _DAT_1001e8b8 = param_5;
  _DAT_1001e8bc = param_6;
  DAT_1001e8c0 = param_7;
  DAT_1001e8c4 = param_8;
  DAT_1001e8c8 = param_9;
  DAT_1001e8cc = param_10;
  _DAT_1001e8d0 = param_11;
  DAT_1001e8d4 = param_12;
  _DAT_1001e8d8 = 150000;
  return;
}

/* ---- 0x1000a0f0  iMUSE_GetMemoryFootprint ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 iMUSE_GetMemoryFootprint(void)

{
                    /* 0xa0f0  77  iMUSE_GetMemoryFootprint */
  return _DAT_10031d4c;
}

/* ---- 0x1000a100  iMUSE_GetSoundCacheSize ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 iMUSE_GetSoundCacheSize(void)

{
                    /* 0xa100  79  iMUSE_GetSoundCacheSize */
  return _DAT_10031d48;
}

/* ---- 0x1000a110  iMUSE_SetHook ---- */
undefined4 iMUSE_SetHook(uint *param_1,uint param_2)

{
  int iVar1;
  undefined4 uVar2;
  
                    /* 0xa110  80  iMUSE_SetHook */
  iVar1 = Sounds_ResolveName_LoadIfNeeded(param_1);
  if (iVar1 == 0) {
    return 0xffffffff;
  }
  uVar2 = ImSetHook(iVar1,param_2);
  return uVar2;
}

/* ---- 0x1000a140  iMUSE_GetHook ---- */
undefined4 iMUSE_GetHook(uint *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
                    /* 0xa140  76  iMUSE_GetHook */
  iVar1 = Sounds_ResolveName_LoadIfNeeded(param_1);
  if (iVar1 == 0) {
    return 0xffffffff;
  }
  uVar2 = ImGetHook(iVar1);
  return uVar2;
}

/* ---- 0x1000a160  iMUSE_SetVoiceEffect ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl iMUSE_SetVoiceEffect(uint *param_1)

{
  int iVar1;
  
                    /* 0xa160  81  iMUSE_SetVoiceEffect */
  Im_MemCopy((uint *)&DAT_10033520,param_1,0x28);
  DAT_10033547 = 0;
  if (_DAT_1001e8d8 == 0) {
    DAT_10033547 = 0;
    DAT_10031d30 = 0;
    return 0;
  }
  iVar1 = FUN_1000c0a0((int)(char)*param_1);
  if ((((iVar1 == 0x4f) && (iVar1 = FUN_1000c0a0((int)*(char *)((int)param_1 + 1)), iVar1 == 0x46))
      && (iVar1 = FUN_1000c0a0((int)*(char *)((int)param_1 + 2)), iVar1 == 0x46)) &&
     (*(char *)((int)param_1 + 3) == '\0')) {
    DAT_10031d30 = 0;
    return 0;
  }
  DAT_10031d30 = FUN_10004750((uint)param_1);
  return DAT_10031d30;
}

/* ---- 0x1000a1e0  Im_TracksInit ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

undefined4 Im_TracksInit(void)

{
  undefined4 *puVar1;
  
  puVar1 = &DAT_10031e98;
  do {
    *puVar1 = 0;
    puVar1 = puVar1 + 0xc;
  } while ((int)puVar1 < IMG_ADDR(0x10031f28));
  DAT_10031e90 = 0;
  return 0;
}

/* ---- 0x1000a300  Im_ProcessStreamsImpl ---- */
/* Refills every streaming track (Im_RefillStreamTrack) */

undefined4 Im_ProcessStreamsImpl(void)

{
  uint uVar1;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  uint *puVar6;
  uint *puVar7;
  
  puVar5 = (uint *)0x0;
  Im_GuardEnter();
  iMUSE_Dispatch__2a00();
  puVar2 = &DAT_10031e98;
  puVar6 = (uint *)0x0;
  do {
    puVar7 = puVar6;
    if ((((*puVar2 != 0) && (puVar2[0xb] == 0)) && (puVar7 = puVar2, puVar6 != (uint *)0x0)) &&
       (puVar7 = puVar6, puVar5 == (uint *)0x0)) {
      puVar5 = puVar2;
    }
    puVar2 = puVar2 + 0xc;
    puVar6 = puVar7;
  } while ((int)puVar2 < IMG_ADDR(0x10031f28));
  if (puVar7 == (uint *)0x0) {
LAB_1000a408:
    if (puVar5 == (uint *)0x0) goto LAB_1000a415;
  }
  else {
    if (puVar5 == (uint *)0x0) {
      if (puVar7 != (uint *)0x0) {
        Im_RefillStreamTrack(puVar7);
        Im_GuardLeave();
        return 0;
      }
      goto LAB_1000a408;
    }
    uVar3 = Im_FindTrack((int)puVar7);
    uVar1 = puVar7[7];
    uVar4 = Im_FindTrack((int)puVar5);
    if (uVar3 < uVar1) {
      if (puVar5[7] <= uVar4) {
        Im_RefillStreamTrack(puVar7);
        Im_GuardLeave();
        return 0;
      }
      if (DAT_10031e90 == puVar7) {
        Im_RefillStreamTrack(puVar7);
        Im_RefillStreamTrack(puVar5);
        Im_GuardLeave();
        return 0;
      }
      Im_RefillStreamTrack(puVar5);
      Im_RefillStreamTrack(puVar7);
      Im_GuardLeave();
      return 0;
    }
    if ((puVar5[7] <= uVar4) && (DAT_10031e90 == puVar7)) {
      Im_RefillStreamTrack(puVar7);
      Im_GuardLeave();
      return 0;
    }
  }
  Im_RefillStreamTrack(puVar5);
LAB_1000a415:
  Im_GuardLeave();
  return 0;
}

/* ---- 0x1000a580  Im_FindTrack ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

int __cdecl Im_FindTrack(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x24) - *(int *)(param_1 + 0x28);
  if (iVar1 < 0) {
    iVar1 = iVar1 + *(int *)(param_1 + 0x14);
  }
  return iVar1;
}

/* ---- 0x1000a5e0  Im_QueryStreamTrack ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

undefined4 __cdecl
Im_QueryStreamTrack(int param_1,undefined4 *param_2,undefined4 *param_3,int *param_4,
                   undefined4 *param_5)

{
  int iVar1;
  
  iMUSE_Dispatch__2a00();
  *param_2 = *(undefined4 *)(param_1 + 0x14);
  *param_3 = *(undefined4 *)(param_1 + 0x1c);
  iVar1 = Im_FindTrack(param_1);
  *param_4 = iVar1;
  *param_5 = *(undefined4 *)(param_1 + 0x2c);
  return 0;
}

/* ---- 0x1000a620  Im_FeedStreamTrack ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

undefined4 __cdecl
Im_FeedStreamTrack(int param_1,undefined4 *param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 *puVar4;
  uint uVar5;
  undefined4 *puVar6;
  
  iVar1 = *(int *)(param_1 + 0x28) - *(int *)(param_1 + 0x24);
  if (iVar1 < 1) {
    iVar1 = iVar1 + *(int *)(param_1 + 0x14);
  }
  if (iVar1 + -4 < (int)param_3) {
    iVar1 = param_3 - (iVar1 + -4);
    iMUSE_stream__a500(param_1,(iVar1 - iVar1 % 0xc) + 0xc);
  }
  if (0 < (int)param_3) {
    uVar3 = *(uint *)(param_1 + 0x14);
    do {
      uVar2 = uVar3 - *(int *)(param_1 + 0x24);
      if ((int)param_3 < (int)uVar2) {
        uVar2 = param_3;
      }
      param_3 = param_3 - uVar2;
      puVar4 = param_2;
      puVar6 = (undefined4 *)(*(int *)(param_1 + 0x10) + *(int *)(param_1 + 0x24));
      for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
        *puVar6 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar6 = puVar6 + 1;
      }
      for (uVar3 = uVar2 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined1 *)puVar6 = *(undefined1 *)puVar4;
        puVar4 = (undefined4 *)((int)puVar4 + 1);
        puVar6 = (undefined4 *)((int)puVar6 + 1);
      }
      param_2 = (undefined4 *)((int)param_2 + uVar2);
      uVar5 = *(int *)(param_1 + 0x24) + uVar2;
      uVar3 = *(uint *)(param_1 + 0x14);
      *(uint *)(param_1 + 4) = *(int *)(param_1 + 4) + uVar2;
      *(uint *)(param_1 + 0x24) = uVar5;
      if (uVar3 <= uVar5) {
        *(uint *)(param_1 + 0x24) = uVar5 - uVar3;
      }
    } while (0 < (int)param_3);
  }
  *(undefined4 *)(param_1 + 0x2c) = param_4;
  return 0;
}

/* ---- 0x1000a6d0  Im_RefillStreamTrack ---- */
/* Refills the stream buffer of one track from its file. Drops the guard (Im_GuardLeave) around the
   blocking read and takes it again after: net 0 only when the caller holds the guard
   (Im_Scheduler_a300 does). */

undefined4 __cdecl Im_RefillStreamTrack(uint *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  if (param_1[2] == 0) {
    uVar1 = iMUSE_dsound__45c0(*param_1,0,2);
    param_1[2] = uVar1;
  }
  iVar2 = param_1[10] - param_1[9];
  if (iVar2 < 1) {
    iVar2 = iVar2 + param_1[5];
  }
  uVar1 = param_1[6];
  if ((int)(iVar2 - 4U) <= (int)param_1[6]) {
    uVar1 = iVar2 - 4U;
  }
  uVar3 = param_1[2] - param_1[1];
  if ((int)uVar3 <= (int)uVar1) {
    uVar1 = uVar3;
  }
  if ((int)uVar3 < 1) {
    param_1[0xb] = 1;
  }
  if (0 < (int)uVar1) {
    while( true ) {
      uVar3 = uVar1;
      if ((int)(param_1[5] - param_1[9]) <= (int)uVar1) {
        uVar3 = param_1[5] - param_1[9];
      }
      uVar4 = iMUSE_dsound__45c0(*param_1,param_1[1],0);
      if (uVar4 != param_1[1]) {
        param_1[0xb] = 1;
        return 0;
      }
      DAT_10031e94 = 0;
      Im_GuardLeave();
      uVar4 = iMUSE_dsound__4600(*param_1,param_1[4] + param_1[9],uVar3);
      Im_GuardEnter();
      if (DAT_10031e94 != 0) {
        return 0;
      }
      uVar1 = uVar1 - uVar4;
      param_1[1] = param_1[1] + uVar4;
      DAT_10031e90 = param_1;
      uVar5 = param_1[9] + uVar4;
      param_1[9] = uVar5;
      if (param_1[5] <= uVar5) {
        param_1[9] = uVar5 - param_1[5];
      }
      if (uVar4 != uVar3) break;
      if ((int)uVar1 < 1) {
        return 0;
      }
    }
    DAT_10031e90 = (uint *)0x0;
  }
  return 0;
}

/* ---- 0x1000a7e0  Im_InitSubsystems ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* DirectSound, mixer, dispatch and track tables */

undefined4 Im_InitSubsystems(void)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  DAT_1003350c = DAT_1001e8d4;
  DAT_1003230c = 0;
  DAT_10032300 = 0;
  _DAT_10032308 = 0x5622;
  iVar2 = Im_DSoundInit(0x5622,(undefined4 *)&DAT_100322f0);
  if (iVar2 != 0) {
    return 0xffffffff;
  }
  iVar2 = Im_MixerInit((undefined4 *)&DAT_100322f0);
  if (iVar2 != 0) {
    return 0xffffffff;
  }
  iVar2 = Im_DispatchInit();
  if (iVar2 != 0) {
    return 0xffffffff;
  }
  iVar2 = Im_TracksInit();
  if (iVar2 != 0) {
    return 0xffffffff;
  }
  iVar2 = 0;
  if (0 < DAT_1003350c) {
    puVar4 = &DAT_10031f30;
    do {
      puVar4[-1] = 0;
      puVar4[-2] = 0;
      puVar3 = iMUSE_Dispatch__1ff0(iVar2);
      *puVar4 = puVar3;
      *puVar3 = puVar4 + -2;
      iVar1 = DAT_1003350c;
      puVar4[1] = 0;
      puVar4 = puVar4 + 0xf;
      iVar2 = iVar2 + 1;
    } while (iVar2 < iVar1);
  }
  return 0;
}

/* ---- 0x1000a8a0  Im_ShutdownSubsystems ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

int Im_ShutdownSubsystems(void)

{
  int iVar1;
  
  Im_StopAllSoundsImpl();
  iVar1 = Im_DSoundShutdown();
  if (iVar1 != 0) {
    return -1;
  }
  iVar1 = iMUSE_Dispatch__1fd0();
  if (iVar1 != 0) {
    return -1;
  }
  iVar1 = Im_MixerReset();
  return -(uint)(iVar1 != 0);
}

/* ---- 0x1000a8d0  Im_PauseImpl ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

void Im_PauseImpl(void)

{
  Im_GuardEnter();
  DAT_1003230c = 1;
  Im_GuardLeave();
  return;
}

/* ---- 0x1000a8f0  Im_ResumeImpl ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

void Im_ResumeImpl(void)

{
  Im_GuardEnter();
  DAT_1003230c = 0;
  Im_GuardLeave();
  return;
}

/* ---- 0x1000a910  Im_SaveImpl ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

int __cdecl Im_SaveImpl(undefined4 *param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  Im_GuardEnter();
  iVar1 = iMUSE_Dispatch__2010(param_1,param_2);
  if (iVar1 < 0) {
    Im_GuardLeave();
    return iVar1;
  }
  if (param_2 - iVar1 < 0x3c0) {
    Im_GuardLeave();
    return -5;
  }
  puVar3 = &DAT_10031f28;
  puVar4 = (undefined4 *)((int)param_1 + iVar1);
  for (iVar2 = 0xf0; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  Im_GuardLeave();
  return iVar1 + 0x3c0;
}

/* ---- 0x1000a970  Im_RestoreImpl ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

int __cdecl Im_RestoreImpl(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  int *piVar5;
  undefined4 *puVar6;
  
  piVar5 = &DAT_10031f28;
  Im_GuardEnter();
  DAT_10032300 = 0;
  iVar2 = iMUSE_Dispatch__2040(param_1);
  iVar1 = DAT_1003350c;
  puVar3 = (undefined4 *)((int)param_1 + iVar2);
  puVar6 = &DAT_10031f28;
  for (iVar4 = 0xf0; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar6 = puVar6 + 1;
  }
  iVar4 = 0;
  if (0 < iVar1) {
    do {
      *piVar5 = 0;
      piVar5[1] = 0;
      puVar3 = iMUSE_Dispatch__1ff0(iVar4);
      piVar5[2] = (int)puVar3;
      *puVar3 = piVar5;
      if (piVar5[3] != 0) {
        iMUSE_stream__b760(&DAT_10032300,piVar5);
      }
      iVar4 = iVar4 + 1;
      piVar5 = piVar5 + 0xf;
    } while (iVar4 < DAT_1003350c);
  }
  iMUSE_Dispatch__20c0();
  Im_GuardLeave();
  return iVar2 + 0x3c0;
}

/* ---- 0x1000aa00  Im_UpdateGroupVolumes ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

undefined4 Im_UpdateGroupVolumes(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = DAT_10032300;
  Im_GuardEnter();
  for (; iVar1 != 0; iVar1 = *(int *)(iVar1 + 4)) {
    iVar2 = Im_GetGroupVol(*(uint *)(iVar1 + 0x14));
    *(int *)(iVar1 + 0x20) = iVar2 * (*(int *)(iVar1 + 0x1c) + 1) >> 7;
  }
  Im_GuardLeave();
  return 0;
}

/* ---- 0x1000aa40  Im_HeartbeatBody ---- */
/* Body of ImHeartbeat once its guards pass: refill the streams, advance the 20 ms mixing step for
   every playing track (FUN_10002570), retire finished ones. */

void Im_HeartbeatBody(void)

{
  int *piVar1;
  int *piVar2;
  
  if (DAT_1003230c != 0) {
    if (DAT_1003230c + 1 < 3) {
      DAT_1003230c = DAT_1003230c + 1;
      return;
    }
    DAT_1003230c = 3;
  }
  do {
    iMUSE_Dispatch__2a00();
    Im_DSoundHeartbeat(&DAT_10032314,&DAT_10032304,(int *)&DAT_100322e8);
    DAT_10032310 = DAT_10032304;
    if (DAT_10032304 != 0) {
      Im_MixerHeartbeat();
      piVar2 = DAT_10032300;
      if (DAT_1003230c == 0) {
        while (piVar2 != (int *)0x0) {
          piVar1 = (int *)piVar2[1];
          Im_DispatchMixTrack(piVar2,DAT_10032304,DAT_100322e8);
          piVar2 = piVar1;
        }
      }
      Im_ReadSoundData(DAT_10032314,DAT_10032304);
      Im_DSoundHeartbeat(&DAT_10032314,&DAT_10032304,(int *)0x0);
    }
  } while (DAT_10032310 != 0);
  return;
}

/* ---- 0x1000ab00  Im_StartSoundImpl ---- */
/* Starts a track for a sound id: priority clamped 0..127, Im_AllocTrackOrSteal, fills the track
   (+0xc id, +0x18 priority, +0x1c volume 127, +0x24 pan 64, +0x30 = 0x100 ...), links it into the
   playing list DAT_10032300. Returns 0, -1 (could not start) or -6 (no track). */

undefined4 __cdecl Im_StartSoundImpl(int param_1,int param_2,uint param_3)

{
  int *piVar1;
  int iVar2;
  
  if (param_2 < 0x80) {
    if (param_2 < 0) {
      param_2 = 0;
    }
  }
  else {
    param_2 = 0x7f;
  }
  piVar1 = Im_AllocTrackOrSteal(param_2);
  if (piVar1 == (int *)0x0) {
    return 0xfffffffa;
  }
  Im_GuardEnter();
  piVar1[3] = param_1;
  piVar1[4] = 0;
  piVar1[5] = 0;
  piVar1[6] = param_2;
  piVar1[7] = 0x7f;
  iVar2 = Im_GetGroupVol(0);
  piVar1[8] = iVar2;
  piVar1[9] = 0x40;
  piVar1[10] = 0;
  piVar1[0xb] = 0;
  piVar1[0xc] = 0x100;
  piVar1[0xd] = 0;
  piVar1[0xe] = 0;
  iVar2 = iMUSE_Dispatch__2170((int)piVar1,param_3);
  if (iVar2 != 0) {
    piVar1[3] = 0;
    Im_GuardLeave();
    return 0xffffffff;
  }
  iMUSE_stream__b760(&DAT_10032300,piVar1);
  Im_GuardLeave();
  return 0;
}

/* ---- 0x1000abb0  Im_StopSoundImpl ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

undefined4 __cdecl Im_StopSoundImpl(int param_1)

{
  int *piVar1;
  int *piVar2;
  undefined4 uVar3;
  
  piVar1 = DAT_10032300;
  uVar3 = 0xffffffff;
  Im_GuardEnter();
  while (piVar2 = piVar1, piVar2 != (int *)0x0) {
    piVar1 = (int *)piVar2[1];
    if (piVar2[3] == param_1) {
      Im_FreeTrack(piVar2);
      uVar3 = 0;
    }
  }
  Im_GuardLeave();
  return uVar3;
}

/* ---- 0x1000ac00  Im_StopAllSoundsImpl ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

undefined4 Im_StopAllSoundsImpl(void)

{
  int *piVar1;
  int *piVar2;
  
  piVar2 = DAT_10032300;
  while (piVar2 != (int *)0x0) {
    piVar1 = (int *)piVar2[1];
    Im_FreeTrack(piVar2);
    piVar2 = piVar1;
  }
  return 0;
}

/* ---- 0x1000ac20  Im_GetNextSoundImpl ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

uint __cdecl Im_GetNextSoundImpl(uint param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = DAT_10032300;
  uVar3 = 0;
  Im_GuardEnter();
  for (; iVar2 != 0; iVar2 = *(int *)(iVar2 + 4)) {
    uVar1 = *(uint *)(iVar2 + 0xc);
    if ((param_1 < uVar1) && ((uVar3 == 0 || (uVar1 < uVar3)))) {
      uVar3 = uVar1;
    }
  }
  Im_GuardLeave();
  return uVar3;
}

/* ---- 0x1000ac60  Im_QueryStreamImpl ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

undefined4 __cdecl
Im_QueryStreamImpl(int param_1,undefined4 *param_2,undefined4 *param_3,int *param_4,
                  undefined4 *param_5)

{
  int iVar1;
  
  iVar1 = DAT_10032300;
  Im_GuardEnter();
  if (iVar1 == 0) {
    Im_GuardLeave();
    return 0xffffffff;
  }
  while (((*(int *)(iVar1 + 0xc) == 0 || (*(int *)(iVar1 + 0xc) != param_1)) ||
         (*(int *)(*(int *)(iVar1 + 8) + 0x81c) == 0))) {
    iVar1 = *(int *)(iVar1 + 4);
    if (iVar1 == 0) {
      Im_GuardLeave();
      return 0xffffffff;
    }
  }
  Im_QueryStreamTrack(*(int *)(*(int *)(iVar1 + 8) + 0x81c),param_2,param_3,param_4,param_5);
  Im_GuardLeave();
  return 0;
}

/* ---- 0x1000ace0  Im_FeedStreamImpl ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

undefined4 __cdecl
Im_FeedStreamImpl(int param_1,undefined4 *param_2,uint param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = DAT_10032300;
  Im_GuardEnter();
  if (iVar2 == 0) {
    Im_GuardLeave();
    return 0xffffffff;
  }
  while (((*(int *)(iVar2 + 0xc) == 0 || (*(int *)(iVar2 + 0xc) != param_1)) ||
         (*(int *)(*(int *)(iVar2 + 8) + 0x81c) == 0))) {
    iVar2 = *(int *)(iVar2 + 4);
    if (iVar2 == 0) {
      Im_GuardLeave();
      return 0xffffffff;
    }
  }
  Im_GuardLeave();
  uVar1 = Im_FeedStreamTrack(*(int *)(*(int *)(iVar2 + 8) + 0x81c),param_2,param_3,param_4);
  return uVar1;
}

/* ---- 0x1000ad50  Im_FreeTrack ---- */
/* Releases a track: dispatch, fades, stream */

void __cdecl Im_FreeTrack(int *param_1)

{
  iMUSE_stream__b7a0(&DAT_10032300,param_1);
  iMUSE_Dispatch__2200((int)param_1);
  Im_FadesClearSound(param_1[3],-1);
  Im_ClearTriggerImpl(param_1[3],(byte *)0xffffffff,-1);
  param_1[3] = 0;
  return;
}

/* ---- 0x1000ada0  Im_SetParamImpl ---- */
/* ImSetParam on a sound id. LEAK: with param 0x400 (group) and a value >= 0x10 it returns without
   Im_GuardLeave: the guard counter stays raised for good (ImStartSound with a group >= 16 reaches
   it too). No Lua script of the game passes such a group. */

undefined4 __cdecl Im_SetParamImpl(int param_1,int param_2,uint param_3)

{
  int iVar1;
  int iVar2;
  
  iVar2 = DAT_10032300;
  Im_GuardEnter();
  if (iVar2 == 0) {
    Im_GuardLeave();
    return 0xfffffffc;
  }
  while (*(int *)(iVar2 + 0xc) != param_1) {
    iVar2 = *(int *)(iVar2 + 4);
    if (iVar2 == 0) {
      Im_GuardLeave();
      return 0xfffffffc;
    }
  }
  if (param_2 < 0x501) {
    if (param_2 == 0x500) {
      if (param_3 < 0x80) {
        *(uint *)(iVar2 + 0x18) = param_3;
        Im_GuardLeave();
        return 0;
      }
      Im_GuardLeave();
      return 0xfffffffb;
    }
    if (param_2 == 0x400) {
      if (param_3 < 0x10) {
        *(uint *)(iVar2 + 0x14) = param_3;
        iVar1 = Im_GetGroupVol(param_3);
        *(int *)(iVar2 + 0x20) = iVar1 * (*(int *)(iVar2 + 0x1c) + 1) >> 7;
        Im_GuardLeave();
        return 0;
      }
      return 0xfffffffb;
    }
  }
  else if (param_2 < 0x701) {
    if (param_2 == 0x700) {
      if (param_3 < 0x80) {
        *(uint *)(iVar2 + 0x24) = param_3;
        Im_GuardLeave();
        return 0;
      }
      Im_GuardLeave();
      return 0xfffffffb;
    }
    if (param_2 == 0x600) {
      if (param_3 < 0x80) {
        *(uint *)(iVar2 + 0x1c) = param_3;
        iVar1 = Im_GetGroupVol(*(uint *)(iVar2 + 0x14));
        *(int *)(iVar2 + 0x20) = (int)(iVar1 * (param_3 + 1)) >> 7;
        Im_GuardLeave();
        return 0;
      }
      Im_GuardLeave();
      return 0xfffffffb;
    }
  }
  else if (param_2 == 0x800) {
    if ((-0x2401 < (int)param_3) && ((int)param_3 < 0x2401)) {
      *(uint *)(iVar2 + 0x28) = param_3;
      *(uint *)(iVar2 + 0x30) = *(int *)(iVar2 + 0x2c) * 0x100 + param_3;
      Im_GuardLeave();
      return 0;
    }
  }
  else {
    if (param_2 != 0x900) {
      if (param_2 == 0xa00) {
        *(uint *)(iVar2 + 0x34) = param_3;
        Im_GuardLeave();
        return 0;
      }
      Im_GuardLeave();
      return 0xfffffffb;
    }
    if ((-1 < (int)param_3) && ((int)param_3 < 0x1000)) {
      *(uint *)(iVar2 + 0x30) = param_3;
      Im_GuardLeave();
      return 0;
    }
  }
  Im_GuardLeave();
  return 0xfffffffb;
}

/* ---- 0x1000af50  Im_GetParamImpl ---- */
/* ImGetParam on a sound id: walks the list of playing tracks (DAT_10032300, next at +4) whose +0xc
   equals the id. 0x100 PLAY_COUNT = number of such tracks; the other params read the first match
   (0x300 prio-ish +0x10, 0x400 +0x14, 0x500 +0x18, 0x600 volume +0x1c, 0x700 pan +0x24, 0x800
   +0x28, 0x900 +0x2c, 0xa00 +0x34, 0x1800/0x1900/0x1a00 stream info); no track: 0 for PLAY_COUNT,
   -4 for the rest, -1 for param 0. */

uint __cdecl Im_GetParamImpl(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = 0;
  iVar1 = DAT_10032300;
  do {
    if (iVar1 == 0) {
      if (param_2 != 0x100) {
        uVar2 = 0xfffffffc;
      }
      return uVar2;
    }
    if (*(int *)(iVar1 + 0xc) == param_1) {
      if (0x100 < param_2) {
        if (param_2 < 0x301) {
          if (param_2 == 0x300) {
            return *(uint *)(iVar1 + 0x10);
          }
          if (param_2 == 0x200) {
            return 0xffffffff;
          }
        }
        else if (param_2 < 0x501) {
          if (param_2 == 0x500) {
            return *(uint *)(iVar1 + 0x18);
          }
          if (param_2 == 0x400) {
            return *(uint *)(iVar1 + 0x14);
          }
        }
        else if (param_2 < 0x701) {
          if (param_2 == 0x700) {
            return *(uint *)(iVar1 + 0x24);
          }
          if (param_2 == 0x600) {
            return *(uint *)(iVar1 + 0x1c);
          }
        }
        else if (param_2 < 0x901) {
          if (param_2 == 0x900) {
            return *(uint *)(iVar1 + 0x2c);
          }
          if (param_2 == 0x800) {
            return *(uint *)(iVar1 + 0x28);
          }
        }
        else if (param_2 < 0x1801) {
          if (param_2 == 0x1800) {
            return (uint)(*(int *)(*(int *)(iVar1 + 8) + 0x81c) != 0);
          }
          if (param_2 == 0xa00) {
            return *(uint *)(iVar1 + 0x34);
          }
        }
        else {
          if (param_2 == 0x1900) {
            return *(uint *)(*(int *)(iVar1 + 8) + 0x820);
          }
          if (param_2 == 0x1a00) {
            iVar1 = *(int *)(iVar1 + 8);
            if (((*(int *)(iVar1 + 4) != 0) && (*(int *)(iVar1 + 8) != 0)) &&
               (*(int *)(iVar1 + 0xc) != 0)) {
              return (uint)(*(int *)(iVar1 + 0x14) * 5) /
                     (uint)(((*(int *)(iVar1 + 4) >> 3) * *(int *)(iVar1 + 0xc) *
                            *(int *)(iVar1 + 8)) / 200);
            }
            return 0;
          }
        }
        return 0xfffffffb;
      }
      if (param_2 != 0x100) {
        if (param_2 == 0) {
          return 0xffffffff;
        }
        return 0xfffffffb;
      }
      uVar2 = uVar2 + 1;
    }
    iVar1 = *(int *)(iVar1 + 4);
  } while( true );
}

/* ---- 0x1000b0a0  Im_SetHookImpl ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

undefined4 __cdecl Im_SetHookImpl(int param_1,uint param_2)

{
  int *piVar1;
  int iVar2;
  
  if (0x80 < param_2) {
    return 0xfffffffb;
  }
  iVar2 = DAT_10032300;
  if (DAT_10032300 == 0) {
    return 0xfffffffc;
  }
  do {
    if (*(int *)(iVar2 + 0xc) == param_1) {
      *(uint *)(iVar2 + 0x38) = param_2;
      return 0;
    }
    piVar1 = (int *)(iVar2 + 4);
    iVar2 = *piVar1;
  } while (*piVar1 != 0);
  return 0xfffffffc;
}

/* ---- 0x1000b0e0  Im_GetHookImpl ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

undefined4 __cdecl Im_GetHookImpl(int param_1)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = DAT_10032300;
  if (DAT_10032300 == 0) {
    return 0xfffffffc;
  }
  do {
    if (*(int *)(iVar2 + 0xc) == param_1) {
      return *(undefined4 *)(iVar2 + 0x38);
    }
    piVar1 = (int *)(iVar2 + 4);
    iVar2 = *piVar1;
  } while (*piVar1 != 0);
  return 0xfffffffc;
}

/* ---- 0x1000b110  Im_AllocTrackOrSteal ---- */
/* Track pool (0x3c bytes each, DAT_1003350c of them, first at 10031f28): a free track (+0xc == 0),
   else the lowest-priority playing track when its priority <= the new one (it is stopped,
   FUN_1000ad50), else NULL (the start fails with -6). */

int * __cdecl Im_AllocTrackOrSteal(int param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  
  iVar2 = 0;
  piVar1 = &DAT_10031f28;
  if (0 < DAT_1003350c) {
    do {
      if (piVar1[3] == 0) {
        return piVar1;
      }
      piVar1 = piVar1 + 0xf;
      iVar2 = iVar2 + 1;
    } while (iVar2 < DAT_1003350c);
  }
  piVar3 = (int *)0x0;
  iVar2 = 0x7f;
  for (piVar1 = DAT_10032300; piVar1 != (int *)0x0; piVar1 = (int *)piVar1[1]) {
    if (piVar1[6] <= iVar2) {
      iVar2 = piVar1[6];
      piVar3 = piVar1;
    }
  }
  if ((piVar3 != (int *)0x0) && (iVar2 <= param_1)) {
    Im_FreeTrack(piVar3);
    return piVar3;
  }
  return (int *)0x0;
}

/* ---- 0x1000b170  Im_TriggersInit ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

undefined4 Im_TriggersInit(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_10032320;
  for (iVar1 = 0x268; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = &DAT_10032cc0;
  for (iVar1 = 0x60; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  DAT_10032f40 = 0;
  DAT_10032f44 = 0;
  return 0;
}

/* ---- 0x1000b1a0  Im_TriggersSave ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

undefined4 __cdecl Im_TriggersSave(undefined4 *param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  if (param_2 < 0xb20) {
    return 0xfffffffb;
  }
  puVar2 = &DAT_10032320;
  puVar3 = param_1;
  for (iVar1 = 0x268; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar2 = &DAT_10032cc0;
  puVar3 = param_1 + 0x268;
  for (iVar1 = 0x60; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  return 0xb20;
}

/* ---- 0x1000b1e0  Im_TriggersRestore ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

undefined4 __cdecl Im_TriggersRestore(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar2 = param_1;
  puVar3 = &DAT_10032320;
  for (iVar1 = 0x268; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar2 = param_1 + 0x268;
  puVar3 = &DAT_10032cc0;
  for (iVar1 = 0x60; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  DAT_10032f40 = 1;
  return 0xb20;
}

/* ---- 0x1000b220  Im_SetTriggerImpl ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

undefined4 __cdecl
Im_SetTriggerImpl(int sound,char *marker,int cmd,int p0,int p1,int p2,int p3,int p4,int p5,int p6,
                 int p7,int p8,int p9)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  uint uVar5;
  int *piVar6;
  int *piVar7;
  char *pcVar8;
  int *piVar9;
  
  piVar6 = &DAT_10032320;
  if (sound == 0) {
    return 0xfffffffb;
  }
  if (marker == (char *)0x0) {
    marker = &DAT_10032f48;
  }
  uVar4 = 0xffffffff;
  pcVar8 = marker;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar8;
    pcVar8 = pcVar8 + 1;
  } while (cVar1 != '\0');
  if (0xff < ~uVar4 - 1) {
    return 0xfffffffb;
  }
  iVar2 = 0;
  while (*piVar6 != 0) {
    iVar2 = iVar2 + 1;
    piVar6 = piVar6 + 0x4d;
    if (7 < iVar2) {
      return 0xfffffffa;
    }
  }
  piVar6[0x41] = cmd;
  uVar4 = 0xffffffff;
  *piVar6 = sound;
  piVar6[0x4c] = 0;
  do {
    pcVar8 = marker;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar8 = marker + 1;
    cVar1 = *marker;
    marker = pcVar8;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  piVar7 = (int *)(pcVar8 + -uVar4);
  piVar9 = piVar6;
  for (uVar5 = uVar4 >> 2; piVar9 = piVar9 + 1, uVar5 != 0; uVar5 = uVar5 - 1) {
    *piVar9 = *piVar7;
    piVar7 = piVar7 + 1;
  }
  piVar3 = &cmd;
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(char *)piVar9 = (char)*piVar7;
    piVar7 = (int *)((int)piVar7 + 1);
    piVar9 = (int *)((int)piVar9 + 1);
  }
  piVar6 = piVar6 + 0x42;
  iVar2 = 10;
  do {
    piVar9 = piVar3 + 1;
    piVar3 = piVar3 + 1;
    *piVar6 = *piVar9;
    piVar6 = piVar6 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return 0;
}
#endif


/* ---- 0x1000b2e0  Im_CheckTriggerImpl ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

int __cdecl Im_CheckTriggerImpl(int param_1,byte *param_2,int param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  byte *pbVar4;
  int *piVar5;
  bool bVar6;
  #define local_8 (*(int *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  local_8 = 0;
  piVar5 = &DAT_10032320;
  local_4 = 8;
  do {
    if ((*piVar5 != 0) && ((param_1 == -1 || (param_1 == *piVar5)))) {
      if (param_2 != (byte *)0xffffffff) {
        pbVar4 = (byte *)(piVar5 + 1);
        pbVar2 = param_2;
        do {
          bVar1 = *pbVar2;
          bVar6 = bVar1 < *pbVar4;
          if (bVar1 != *pbVar4) {
LAB_1000b345:
            iVar3 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
            goto LAB_1000b34a;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar2[1];
          bVar6 = bVar1 < pbVar4[1];
          if (bVar1 != pbVar4[1]) goto LAB_1000b345;
          pbVar2 = pbVar2 + 2;
          pbVar4 = pbVar4 + 2;
        } while (bVar1 != 0);
        iVar3 = 0;
LAB_1000b34a:
        if (iVar3 != 0) goto LAB_1000b35f;
      }
      if ((param_3 == -1) || (param_3 == piVar5[0x41])) {
        local_8 = local_8 + 1;
      }
    }
LAB_1000b35f:
    piVar5 = piVar5 + 0x4d;
    local_4 = local_4 + -1;
    if (local_4 == 0) {
      return local_8;
    }
  } while( true );
}
#undef local_4
#undef local_8


/* ---- 0x1000b380  Im_ClearTriggerImpl ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

undefined4 __cdecl Im_ClearTriggerImpl(int param_1,byte *param_2,int param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  byte *pbVar4;
  int *piVar5;
  bool bVar6;
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  piVar5 = &DAT_10032320;
  local_4 = 8;
  do {
    if ((*piVar5 != 0) && ((param_1 == -1 || (param_1 == *piVar5)))) {
      if (param_2 != (byte *)0xffffffff) {
        pbVar4 = (byte *)(piVar5 + 1);
        pbVar2 = param_2;
        do {
          bVar1 = *pbVar2;
          bVar6 = bVar1 < *pbVar4;
          if (bVar1 != *pbVar4) {
LAB_1000b3db:
            iVar3 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
            goto LAB_1000b3e0;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar2[1];
          bVar6 = bVar1 < pbVar4[1];
          if (bVar1 != pbVar4[1]) goto LAB_1000b3db;
          pbVar2 = pbVar2 + 2;
          pbVar4 = pbVar4 + 2;
        } while (bVar1 != 0);
        iVar3 = 0;
LAB_1000b3e0:
        if (iVar3 != 0) goto LAB_1000b40c;
      }
      if ((param_3 == -1) || (param_3 == piVar5[0x41])) {
        if (DAT_10032f44 == 0) {
          *piVar5 = 0;
        }
        else {
          piVar5[0x4c] = 1;
        }
      }
    }
LAB_1000b40c:
    piVar5 = piVar5 + 0x4d;
    local_4 = local_4 + -1;
    if (local_4 == 0) {
      return 0;
    }
  } while( true );
}
#undef local_4


/* ---- 0x1000b430  Im_FireTriggers ---- */
/* Matches a marker name against the trigger table and runs the stored commands */

undefined4 * __cdecl Im_FireTriggers(int param_1,char *param_2)

{
  unsigned char _frame[0x110] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  byte bVar2;
  int iVar3;
  undefined4 *puVar4;
  byte *pbVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  char *pcVar10;
  byte *pbVar11;
  char *pcVar12;
  int *piVar13;
  bool bVar14;
  #define local_100 (*(char (*)[256])(_frame + (0x110 - 0x100)))
  
  uVar7 = 0xffffffff;
  puVar4 = (undefined4 *)0x0;
  pcVar10 = param_2;
  do {
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    cVar1 = *pcVar10;
    pcVar10 = pcVar10 + 1;
  } while (cVar1 != '\0');
  if (~uVar7 - 1 < 0x100) {
    uVar7 = 0xffffffff;
    do {
      pcVar10 = param_2;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pcVar10 = param_2 + 1;
      cVar1 = *param_2;
      param_2 = pcVar10;
    } while (cVar1 != '\0');
    uVar7 = ~uVar7;
    iVar9 = 8;
    pcVar10 = pcVar10 + -uVar7;
    pcVar12 = (char *)&DAT_10032e40;
    for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar12 = *(undefined4 *)pcVar10;
      pcVar10 = pcVar10 + 4;
      pcVar12 = pcVar12 + 4;
    }
    DAT_10032f44 = (undefined4 *)((int)DAT_10032f44 + 1);
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pcVar12 = *pcVar10;
      pcVar10 = pcVar10 + 1;
      pcVar12 = pcVar12 + 1;
    }
    piVar13 = &DAT_10032320;
    do {
      if ((*piVar13 != 0) && (param_1 == *piVar13)) {
        pbVar11 = (byte *)(piVar13 + 1);
        if ((char)piVar13[1] != '\0') {
          pbVar5 = (byte *)&DAT_10032e40;
          do {
            bVar2 = *pbVar5;
            bVar14 = bVar2 < *pbVar11;
            if (bVar2 != *pbVar11) {
LAB_1000b4d7:
              iVar6 = (1 - (uint)bVar14) - (uint)(bVar14 != 0);
              goto LAB_1000b4dc;
            }
            if (bVar2 == 0) break;
            bVar2 = pbVar5[1];
            bVar14 = bVar2 < pbVar11[1];
            if (bVar2 != pbVar11[1]) goto LAB_1000b4d7;
            pbVar5 = pbVar5 + 2;
            pbVar11 = pbVar11 + 2;
          } while (bVar2 != 0);
          iVar6 = 0;
LAB_1000b4dc:
          if (iVar6 != 0) goto LAB_1000b52c;
        }
        iVar6 = 0;
        cVar1 = (char)DAT_10032e40;
        while (cVar1 != '\0') {
          local_100[iVar6] = cVar1;
          iVar3 = iVar6 + 1;
          iVar6 = iVar6 + 1;
          cVar1 = *(char *)((int)&DAT_10032e40 + iVar3);
        }
        local_100[iVar6] = '\0';
        Im_RunTriggerCommand(piVar13,&DAT_10032e40);
        iVar6 = 0;
        cVar1 = local_100[0];
        while (cVar1 != '\0') {
          *(char *)((int)&DAT_10032e40 + iVar6) = cVar1;
          iVar3 = iVar6 + 1;
          iVar6 = iVar6 + 1;
          cVar1 = local_100[iVar3];
        }
        *(undefined1 *)((int)&DAT_10032e40 + iVar6) = 0;
      }
LAB_1000b52c:
      piVar13 = piVar13 + 0x4d;
      iVar9 = iVar9 + -1;
    } while (iVar9 != 0);
    puVar4 = (undefined4 *)((int)DAT_10032f44 + -1);
    DAT_10032f44 = puVar4;
    if (puVar4 == (undefined4 *)0x0) {
      iVar9 = 8;
      puVar4 = &DAT_10032320;
      do {
        if (puVar4[0x4c] != 0) {
          *puVar4 = 0;
        }
        puVar4 = puVar4 + 0x4d;
        iVar9 = iVar9 + -1;
      } while (iVar9 != 0);
    }
  }
  return puVar4;
}
#undef local_100


/* ---- 0x1000b570  Im_DeferCommandImpl ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

undefined4 __cdecl
Im_DeferCommandImpl(int time,int cmd,int p0,int p1,int p2,int p3,int p4,int p5,int p6,int p7,int p8,
                   int p9)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  
  piVar5 = &DAT_10032cc0;
  if (time == 0) {
    return 0xfffffffb;
  }
  iVar2 = 0;
  do {
    if (*piVar5 == 0) {
      piVar4 = piVar5 + 2;
      piVar5[1] = cmd;
      piVar3 = &cmd;
      iVar2 = 10;
      do {
        piVar1 = piVar3 + 1;
        piVar3 = piVar3 + 1;
        *piVar4 = *piVar1;
        piVar4 = piVar4 + 1;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
      *piVar5 = time;
      DAT_10032f40 = 1;
      return 0;
    }
    iVar2 = iVar2 + 1;
    piVar5 = piVar5 + 0xc;
  } while (iVar2 < 8);
  return 0xfffffffa;
}
#endif


/* ---- 0x1000b5e0  Im_ProcessDeferred ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

void Im_ProcessDeferred(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  piVar3 = &DAT_10032cc0;
  if (DAT_10032f40 != 0) {
    DAT_10032f40 = 0;
    iVar2 = 8;
    do {
      if (*piVar3 != 0) {
        iVar1 = *piVar3 + -1;
        DAT_10032f40 = 1;
        *piVar3 = iVar1;
        if (iVar1 == 0) {
          Im_RunDeferredCommand((int)piVar3);
        }
      }
      piVar3 = piVar3 + 0xc;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  return;
}

/* ---- 0x1000b630  Im_GetTriggerParam ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

int __cdecl Im_GetTriggerParam(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar1 = 0;
  piVar2 = &DAT_10032424;
  iVar3 = 8;
  do {
    if ((piVar2[-0x41] != 0) &&
       (((*piVar2 == 8 && (piVar2[1] == param_1)) || ((*piVar2 == 0x1a && (piVar2[2] == param_1)))))
       ) {
      iVar1 = iVar1 + 1;
    }
    piVar2 = piVar2 + 0x4d;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  piVar2 = &DAT_10032cc4;
  iVar3 = 8;
  do {
    if ((piVar2[-1] != 0) &&
       (((*piVar2 == 8 && (piVar2[1] == param_1)) || ((*piVar2 == 0x1a && (piVar2[2] == param_1)))))
       ) {
      iVar1 = iVar1 + 1;
    }
    piVar2 = piVar2 + 0xc;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return iVar1;
}

/* ---- 0x1000b6a0  Im_RunTriggerCommand ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

void __cdecl Im_RunTriggerCommand(undefined4 *param_1,undefined4 param_2)

{
  code *cmd;
  int a2;
  undefined4 uVar1;
  
  cmd = (code *)param_1[0x41];
  *param_1 = 0;
  if (cmd == (code *)0x0) {
    if (DAT_100336a8 != (code *)0x0) {
      uVar1 = param_1[0x4b];
      (*DAT_100336a8)(param_2,uVar1,uVar1,uVar1,uVar1,uVar1,uVar1,uVar1,uVar1,uVar1,uVar1);
    }
    return;
  }
  a2 = param_1[0x4b];
  if (cmd < (code *)0x1e) {
    Im_DispatchCommand((uint)cmd,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2);
    return;
  }
  (*cmd)(param_2);
  return;
}
#endif


/* ---- 0x1000b710  Im_RunDeferredCommand ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

void __cdecl Im_RunDeferredCommand(int param_1)

{
  code *cmd;
  int a2;
  
  cmd = *(code **)(param_1 + 4);
  if (cmd == (code *)0x0) {
    if (DAT_100336a8 == (code *)0x0) {
      return;
    }
    a2 = *(int *)(param_1 + 0x2c);
    cmd = DAT_100336a8;
  }
  else {
    a2 = *(int *)(param_1 + 0x2c);
    if (cmd < (code *)0x1e) {
      Im_DispatchCommand((uint)cmd,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2);
      return;
    }
  }
  (*cmd)(a2,a2,a2,a2,a2,a2,a2,a2,a2,a2);
  return;
}
#endif


/* ---- 0x1000bd50  Im_StrChr ---- */
/* NOT COMPILED: names/lib_replace.json (host): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

char * __cdecl Im_StrChr(char *param_1,char param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  
  iVar2 = -1;
  do {
    pcVar4 = param_1;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar4 = param_1 + 1;
    cVar1 = *param_1;
    param_1 = pcVar4;
  } while (cVar1 != '\0');
  iVar2 = -(iVar2 + 1);
  pcVar4 = pcVar4 + -1;
  do {
    pcVar3 = pcVar4;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar3 = pcVar4 + -1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar3;
  } while (param_2 != cVar1);
  pcVar3 = pcVar3 + 1;
  if (*pcVar3 != param_2) {
    pcVar3 = (char *)0x0;
  }
  return pcVar3;
}
#endif


/* ---- 0x1000bd80  Im_MemCopy ---- */
/* NOT COMPILED: names/lib_replace.json (host): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint * __cdecl Im_MemCopy(uint *param_1,uint *param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  char cVar3;
  uint uVar4;
  uint *puVar5;
  
  if (param_3 == 0) {
    return param_1;
  }
  puVar5 = param_1;
  if (((uint)param_2 & 3) != 0) {
    while( true ) {
      uVar4 = *param_2;
      param_2 = (uint *)((int)param_2 + 1);
      *(char *)puVar5 = (char)uVar4;
      puVar5 = (uint *)((int)puVar5 + 1);
      param_3 = param_3 - 1;
      if (param_3 == 0) {
        return param_1;
      }
      if ((char)uVar4 == '\0') break;
      if (((uint)param_2 & 3) == 0) {
        uVar4 = param_3 >> 2;
        goto joined_r0x1000bdbe;
      }
    }
    do {
      if (((uint)puVar5 & 3) == 0) {
        uVar4 = param_3 >> 2;
        cVar3 = '\0';
        if (uVar4 == 0) goto LAB_1000bdfb;
        goto LAB_1000be69;
      }
      *(char *)puVar5 = '\0';
      puVar5 = (uint *)((int)puVar5 + 1);
      param_3 = param_3 - 1;
    } while (param_3 != 0);
    return param_1;
  }
  uVar4 = param_3 >> 2;
  if (uVar4 != 0) {
    do {
      uVar1 = *param_2;
      uVar2 = *param_2;
      param_2 = param_2 + 1;
      if (((uVar1 ^ 0xffffffff ^ uVar1 + 0x7efefeff) & 0x81010100) != 0) {
        if ((char)uVar2 == '\0') {
          *puVar5 = 0;
joined_r0x1000be65:
          while( true ) {
            uVar4 = uVar4 - 1;
            puVar5 = puVar5 + 1;
            if (uVar4 == 0) break;
LAB_1000be69:
            *puVar5 = 0;
          }
          cVar3 = '\0';
          param_3 = param_3 & 3;
          if (param_3 != 0) goto LAB_1000bdfb;
          return param_1;
        }
        if ((char)(uVar2 >> 8) == '\0') {
          *puVar5 = uVar2 & 0xff;
          goto joined_r0x1000be65;
        }
        if ((uVar2 & 0xff0000) == 0) {
          *puVar5 = uVar2 & 0xffff;
          goto joined_r0x1000be65;
        }
        if ((uVar2 & 0xff000000) == 0) {
          *puVar5 = uVar2;
          goto joined_r0x1000be65;
        }
      }
      *puVar5 = uVar2;
      puVar5 = puVar5 + 1;
      uVar4 = uVar4 - 1;
joined_r0x1000bdbe:
    } while (uVar4 != 0);
    param_3 = param_3 & 3;
    if (param_3 == 0) {
      return param_1;
    }
  }
  do {
    cVar3 = (char)*param_2;
    param_2 = (uint *)((int)param_2 + 1);
    *(char *)puVar5 = cVar3;
    puVar5 = (uint *)((int)puVar5 + 1);
    if (cVar3 == '\0') {
      while (param_3 = param_3 - 1, param_3 != 0) {
LAB_1000bdfb:
        *(char *)puVar5 = cVar3;
        puVar5 = (uint *)((int)puVar5 + 1);
      }
      return param_1;
    }
    param_3 = param_3 - 1;
  } while (param_3 != 0);
  return param_1;
}
#endif


/* ---- 0x1000be80  Im_StrCmpNoCase ---- */
/* NOT COMPILED: names/lib_replace.json (host): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl Im_StrCmpNoCase(byte *param_1,byte *param_2)

{
  bool bVar1;
  int iVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  char cVar6;
  uint uVar8;
  uint uVar9;
  uint uVar7;
  
  iVar2 = _DAT_100337f0;
  if (DAT_10032fe0 == 0) {
    bVar5 = 0xff;
    do {
      do {
        cVar6 = '\0';
        if (bVar5 == 0) goto LAB_1000bece;
        bVar5 = *param_2;
        param_2 = param_2 + 1;
        bVar4 = *param_1;
        param_1 = param_1 + 1;
      } while (bVar4 == bVar5);
      bVar3 = bVar5 + 0xbf + (-((byte)(bVar5 + 0xbf) < 0x1a) & 0x20U) + 0x41;
      bVar4 = bVar4 + 0xbf;
      bVar5 = bVar4 + (-(bVar4 < 0x1a) & 0x20U) + 0x41;
    } while (bVar5 == bVar3);
    cVar6 = (bVar5 < bVar3) * -2 + '\x01';
LAB_1000bece:
    uVar7 = (uint)cVar6;
  }
  else {
    LOCK();
    _DAT_100337f0 = _DAT_100337f0 + 1;
    UNLOCK();
    bVar1 = 0 < DAT_100337ec;
    if (bVar1) {
      LOCK();
      UNLOCK();
      _DAT_100337f0 = iVar2;
      ImFile_LockInit(0x13);
    }
    uVar9 = (uint)bVar1;
    uVar7 = 0xff;
    uVar8 = 0;
    do {
      do {
        if ((char)uVar7 == '\0') goto LAB_1000bf2f;
        bVar5 = *param_2;
        uVar7 = CONCAT31((int3)(uVar7 >> 8),bVar5);
        param_2 = param_2 + 1;
        bVar4 = *param_1;
        uVar8 = CONCAT31((int3)(uVar8 >> 8),bVar4);
        param_1 = param_1 + 1;
      } while (bVar5 == bVar4);
      uVar8 = _tolower_lk(uVar8);
      uVar7 = _tolower_lk(uVar7);
    } while ((byte)uVar8 == (byte)uVar7);
    uVar8 = (uint)((byte)uVar8 < (byte)uVar7);
    uVar7 = (1 - uVar8) - (uint)(uVar8 != 0);
LAB_1000bf2f:
    if (uVar9 == 0) {
      LOCK();
      _DAT_100337f0 = _DAT_100337f0 + -1;
      UNLOCK();
    }
    else {
      ImFile_UnlockInner(0x13);
    }
  }
  return uVar7;
}
#endif

