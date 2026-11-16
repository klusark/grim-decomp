/* IMUSE.DLL :: imuse.c
 * functions 0x10001000 .. 0x1000be80 (115 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10001000  AudioLib_DetectRawFormat ---- */
/* Compressed (VIMA-style ADPCM) block decoder using the step/index tables; identity inferred from
   structure Original name AudioLib_DetectRawFormat (the remaster's GrimFandango (Linux):
   AudioLib_ParseWaveFileHeader's only callee; same byte-delta statistics over the 8-bit samples);
   was Im_VimaDecodeBlock. */

void __cdecl
AudioLib_DetectRawFormat
          (ushort *data,uint size,undefined4 *outBits,undefined4 *outChannels,undefined4 *outFlags)

{
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
  uint local_24;
  uint local_20;
  uint local_1c;
  uint local_18;
  uint local_14;
  uint local_10;
  
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_24 = 0;
  local_14 = 0;
  local_10 = 0;
  iVar20 = (byte)*data - 0x80;
  iVar6 = (size >> 1) - 1;
  iVar16 = iVar20;
  puVar17 = data;
  for (iVar18 = iVar6; iVar18 != 0; iVar18 = iVar18 + -1) {
    puVar17 = (ushort *)((int)puVar17 + 1);
    uVar7 = (*(byte *)puVar17 - 0x80) - iVar16;
    uVar11 = (int)uVar7 >> 0x1f;
    local_20 = local_20 + ((uVar7 ^ uVar11) - uVar11) * 0x100;
    iVar16 = *(byte *)puVar17 - 0x80;
  }
  iVar18 = (size >> 3) - 2;
  if (iVar18 != 0) {
    pbVar19 = (byte *)((int)data + 3);
    iVar16 = *(byte *)((int)data + 1) - 0x80;
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
  uVar4 = *data;
  iVar18 = (int)(short)uVar4;
  puVar17 = data;
  for (iVar20 = iVar6; iVar20 != 0; iVar20 = iVar20 + -1) {
    puVar17 = puVar17 + 1;
    uVar7 = (short)*puVar17 - iVar18;
    uVar11 = (int)uVar7 >> 0x1f;
    local_18 = local_18 + ((uVar7 ^ uVar11) - uVar11);
    iVar18 = (int)(short)*puVar17;
  }
  uVar11 = (uint)(uVar4 >> 8) | (uint)(byte)uVar4 << 8;
  uVar7 = uVar11;
  puVar17 = data;
  for (; iVar6 != 0; iVar6 = iVar6 + -1) {
    puVar17 = puVar17 + 1;
    uVar12 = (uint)(byte)*puVar17 << 8 | (uint)(*puVar17 >> 8);
    uVar7 = uVar12 - uVar7;
    uVar13 = (int)uVar7 >> 0x1f;
    local_24 = local_24 + ((uVar7 ^ uVar13) - uVar13);
    uVar7 = uVar12;
  }
  uVar5 = data[1];
  puVar8 = (ushort *)(size >> 2);
  puVar17 = puVar8 + -1;
  if (puVar17 != (ushort *)0x0) {
    puVar9 = data + 3;
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
    puVar17 = data + 3;
    uVar7 = (uint)(uVar5 >> 8) | (uVar5 & 0xff) << 8;
    data = puVar8;
    do {
      uVar14 = (uint)(byte)puVar17[-1] << 8 | (uint)(puVar17[-1] >> 8);
      uVar15 = (uint)(byte)*puVar17 << 8 | (uint)(*puVar17 >> 8);
      uVar11 = uVar14 - uVar11;
      uVar12 = (int)uVar11 >> 0x1f;
      uVar7 = uVar15 - uVar7;
      uVar13 = (int)uVar7 >> 0x1f;
      local_10 = ((uVar7 ^ uVar13) - uVar13) + local_10 + ((uVar11 ^ uVar12) - uVar12);
      data = (ushort *)((int)data + -1);
      puVar17 = puVar17 + 2;
      uVar11 = uVar14;
      uVar7 = uVar15;
    } while (data != (ushort *)0x0);
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
    if (outBits != (undefined4 *)0x0) {
      *outBits = 8;
    }
    if (outChannels != (undefined4 *)0x0) {
      *outChannels = 1;
    }
    break;
  case 1:
    if (outBits != (undefined4 *)0x0) {
      *outBits = 8;
    }
    goto joined_r0x10001355;
  case 2:
    if (outBits != (undefined4 *)0x0) {
      *outBits = 0x10;
    }
    if (outChannels != (undefined4 *)0x0) {
      *outChannels = 1;
    }
    break;
  case 3:
    if (outBits != (undefined4 *)0x0) {
      *outBits = 0x10;
    }
    if (outChannels != (undefined4 *)0x0) {
      *outChannels = 1;
    }
    if (outFlags == (undefined4 *)0x0) {
      return;
    }
    *outFlags = 0;
    return;
  case 4:
    if (outBits != (undefined4 *)0x0) {
      *outBits = 0x10;
    }
joined_r0x10001355:
    if (outChannels != (undefined4 *)0x0) {
      *outChannels = 2;
    }
    break;
  case 5:
    if (outBits != (undefined4 *)0x0) {
      *outBits = 0x10;
    }
    if (outChannels != (undefined4 *)0x0) {
      *outChannels = 2;
    }
    if (outFlags != (undefined4 *)0x0) {
      *outFlags = 0;
    }
  default:
    goto switchD_100012ad_default;
  }
  if (outFlags != (undefined4 *)0x0) {
    *outFlags = 1;
    return;
  }
switchD_100012ad_default:
  return;
}

/* ---- 0x100013c0  AudioLib_ParseWaveFileHeader ---- */
/* Drives Im_VimaDecodeBlock over a compressed sound chunk Original name
   AudioLib_ParseWaveFileHeader (the remaster's GrimFandango (Linux): same body start (an MCMP
   header is skipped, RIFF / 'WAVEfmt ' checked, *param_2 = 0 first); callers CacheGetSoundId, the
   dispatcher's region change and the sound start agree; not a VIMA decoder); was Im_VimaDecompress.
    */

uint * __cdecl
AudioLib_ParseWaveFileHeader
          (uint *header,int *outFormat,uint *outRate,uint *outBits,uint *outChannels,int *outFlags,
          uint *outDataSize)

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
  
  if (outFormat != (int *)0x0) {
    *outFormat = 0;
  }
  if (header == (uint *)0x0) {
    return (uint *)0x0;
  }
  iVar3 = 4;
  bVar9 = true;
  puVar6 = header;
  pcVar8 = s_MCMP_10017098;
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    bVar9 = (char)*puVar6 == *pcVar8;
    puVar6 = (uint *)((int)puVar6 + 1);
    pcVar8 = pcVar8 + 1;
  } while (bVar9);
  if (bVar9) {
    uVar2 = (uint)(ushort)((ushort)header[1] >> 8) | (uint)(byte)(ushort)header[1] << 8;
    uVar1 = *(ushort *)((int)header + uVar2 * 9 + 6);
    header = (uint *)((int)header + ((uint)(byte)uVar1 << 8 | (uint)(uVar1 >> 8)) + uVar2 * 9 + 8);
  }
  iVar3 = 4;
  bVar10 = true;
  puVar6 = header;
  pcVar8 = &DAT_10017090;
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    bVar10 = (char)*puVar6 == *pcVar8;
    puVar6 = (uint *)((int)puVar6 + 1);
    pcVar8 = pcVar8 + 1;
  } while (bVar10);
  if (bVar10) {
    puVar6 = (uint *)(header[1] + 8 + (int)header);
    iVar3 = 8;
    bVar10 = true;
    puVar5 = header + 2;
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
    if ((short)header[5] != 1) {
      return (uint *)0x0;
    }
    if (outFormat != (int *)0x0) {
      *outFormat = bVar9 + 5;
    }
    uVar2 = header[4];
    puVar5 = header + 4;
    if (outRate != (uint *)0x0) {
      *outRate = header[6];
    }
    if (outBits != (uint *)0x0) {
      *outBits = (int)*(short *)((int)header + 0x22);
    }
    if (outChannels != (uint *)0x0) {
      *outChannels = (int)*(short *)((int)header + 0x16);
    }
    if (outFlags != (int *)0x0) {
      *outFlags = 1;
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
      if (outDataSize != (uint *)0x0) {
        *outDataSize = uVar2;
      }
      return puVar5 + 1;
    }
  }
  else {
    iVar3 = 4;
    bVar10 = true;
    puVar6 = header;
    pcVar8 = (char *)&DAT_10017074;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      bVar10 = (char)*puVar6 == *pcVar8;
      puVar6 = (uint *)((int)puVar6 + 1);
      pcVar8 = pcVar8 + 1;
    } while (bVar10);
    if (bVar10) {
      uVar2 = header[3];
      uVar2 = (uVar2 & 0xff00 | uVar2 << 0x10) << 8 | (uVar2 & 0xff0000 | uVar2 >> 0x10) >> 8;
      iVar3 = 4;
      bVar10 = true;
      puVar6 = header + 4;
      pcVar8 = (char *)&DAT_1001706c;
      do {
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        bVar10 = (char)*puVar6 == *pcVar8;
        puVar6 = (uint *)((int)puVar6 + 1);
        pcVar8 = pcVar8 + 1;
      } while (bVar10);
      if (bVar10) {
        if (outFormat != (int *)0x0) {
          *outFormat = bVar9 + 3;
        }
        puVar6 = header + 8;
        if (outBits != (uint *)0x0) {
          uVar4 = *puVar6;
          *outBits = (uVar4 & 0xff00 | uVar4 << 0x10) << 8 | (uVar4 & 0xff0000 | uVar4 >> 0x10) >> 8
          ;
        }
        if (outRate != (uint *)0x0) {
          uVar4 = header[9];
          *outRate = (uVar4 & 0xff00 | uVar4 << 0x10) << 8 | (uVar4 >> 0x10 | uVar4 & 0xff0000) >> 8
          ;
        }
        if (outChannels != (uint *)0x0) {
          uVar4 = header[10];
          *outChannels = (uVar4 & 0xff00 | uVar4 << 0x10) << 8 |
                         (uVar4 & 0xff0000 | uVar4 >> 0x10) >> 8;
        }
        if (outFlags != (int *)0x0) {
          *outFlags = 0;
        }
        if (outDataSize != (uint *)0x0) {
          uVar4 = *(uint *)((uVar2 - 0xc) + (int)puVar6);
          *outDataSize = (uVar4 & 0xff00 | uVar4 << 0x10) << 8 |
                         (uVar4 & 0xff0000 | uVar4 >> 0x10) >> 8;
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
    puVar6 = header;
    pcVar8 = &DAT_10017064;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      bVar9 = (char)*puVar6 == *pcVar8;
      puVar6 = (uint *)((int)puVar6 + 1);
      pcVar8 = pcVar8 + 1;
    } while (bVar9);
    if (bVar9) {
      uVar2 = header[1];
      bVar9 = true;
      puVar6 = (uint *)(((uVar2 & 0xff00 | uVar2 << 0x10) << 8 |
                        (uVar2 >> 0x10 | uVar2 & 0xff0000) >> 8) + 8 + (int)header);
      iVar3 = 8;
      puVar5 = header + 2;
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
      if (outFormat != (int *)0x0) {
        *outFormat = 7;
      }
      uVar2 = header[4];
      puVar5 = header + 4;
      uVar2 = (uVar2 & 0xff00 | uVar2 << 0x10) << 8 | (uVar2 & 0xff0000 | uVar2 >> 0x10) >> 8;
      if (outRate != (uint *)0x0) {
        if (*(char *)((int)header + 0x1d) == '\x0e') {
          uVar4 = 0xac44;
        }
        else {
          uVar4 = (-(uint)(*(char *)((int)header + 0x1d) != '\f') & 0x2b11) + 0x2b11;
        }
        *outRate = uVar4;
      }
      if (outBits != (uint *)0x0) {
        *outBits = (uint)*(byte *)((int)header + 0x1b);
      }
      if (outChannels != (uint *)0x0) {
        *outChannels = (uint)*(byte *)((int)header + 0x15);
      }
      if (outFlags != (int *)0x0) {
        *outFlags = 0;
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
        if (outDataSize != (uint *)0x0) {
          *outDataSize = uVar2 - 8;
        }
        return puVar5 + 3;
      }
    }
    else {
      AudioLib_DetectRawFormat((ushort *)header,0x2000,outBits,outChannels,outFlags);
      if ((outBits == (uint *)0x0) || (*outBits == 0x10)) {
        if ((outFlags != (int *)0x0) &&
           ((outFormat != (int *)0x0 && (*outFormat = 2 - (uint)(*outFlags != 0), *outRate != 0))))
        {
          *outRate = 0xac44;
        }
        return header;
      }
    }
  }
  return (uint *)0x0;
}

/* ---- 0x100017e0  AudioLib_CreateWaveFileHeader ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Original name AudioLib_CreateWaveFileHeader (the remaster's GrimFandango (Linux): same body
   (buffer, type, rate, bits, channels, size: type 3 the iMUS header with MAP / FRMT / REGN / STOP /
   DATA and big-endian sizes, type 5 RIFF / WAVEfmt / data, type 7 FORM / AIFF / COMM with the
   0x2b11 / 0xac44 rate words and SSND; returns the header length); callers agree (the region fetch
   inlined in the remaster's GoToNextRegion, CacheGetSoundId, MxEndMix)); was Im_DecodeSoundBlock.
    */

int __cdecl
AudioLib_CreateWaveFileHeader
          (undefined4 *header,int format,uint rate,uint byteRate,uint blockAlign,uint dataSize)

{
  uint uVar1;
  undefined4 *puVar2;
  uint uVar3;
  
  if (format == 3) {
    *header = DAT_10017074;
    uVar1 = dataSize + 0x50;
    header[1] = (uVar1 & 0xff00 | uVar1 * 0x10000) << 8 | (uVar1 & 0xff0000 | uVar1 >> 0x10) >> 8;
    header[2] = DAT_100170b8;
    header[3] = 0x38000000;
    header[4] = DAT_1001706c;
    header[5] = 0x14000000;
    header[6] = 0x50000000;
    header[7] = 0;
    header[8] = (byteRate & 0xff00 | byteRate << 0x10) << 8 |
                (byteRate & 0xff0000 | byteRate >> 0x10) >> 8;
    header[9] = (rate & 0xff00 | rate << 0x10) << 8 | (rate & 0xff0000 | rate >> 0x10) >> 8;
    header[10] = (blockAlign & 0xff00 | blockAlign << 0x10) << 8 |
                 (blockAlign & 0xff0000 | blockAlign >> 0x10) >> 8;
    header[0xb] = DAT_100170b0;
    header[0xc] = 0x8000000;
    header[0xd] = 0x50000000;
    uVar3 = (dataSize & 0xff00 | dataSize << 0x10) << 8 |
            (dataSize & 0xff0000 | dataSize >> 0x10) >> 8;
    header[0xe] = uVar3;
    header[0xf] = DAT_100170a8;
    header[0x10] = 0x4000000;
    header[0x11] = (uVar1 & 0xff00 | uVar1 * 0x10000) << 8 | (uVar1 & 0xff0000 | uVar1 >> 0x10) >> 8
    ;
    header[0x12] = DAT_100170a0;
    header[0x13] = uVar3;
    puVar2 = header + 0x14;
  }
  else {
    if (format == 5) {
      *header = _DAT_10017090;
      header[1] = dataSize + 0x24;
      header[2] = _DAT_10017084;
      header[3] = DAT_10017088;
      header[4] = 0x10;
      *(undefined2 *)(header + 5) = 1;
      *(short *)((int)header + 0x16) = (short)blockAlign;
      header[6] = rate;
      header[7] = blockAlign * rate * (byteRate >> 3);
      *(short *)(header + 8) = (short)blockAlign * (short)(byteRate >> 3);
      *(short *)((int)header + 0x22) = (short)byteRate;
      header[9] = DAT_1001707c;
      header[10] = dataSize;
      return 0x2c;
    }
    puVar2 = header;
    if (format == 7) {
      *header = _DAT_10017064;
      uVar1 = dataSize + 0x36;
      header[1] = (uVar1 & 0xff00 | uVar1 * 0x10000) << 8 | (uVar1 & 0xff0000 | uVar1 >> 0x10) >> 8;
      header[2] = DAT_10017058;
      header[3] = DAT_1001705c;
      header[4] = 0x12000000;
      *(ushort *)(header + 5) = CONCAT11((char)blockAlign,(char)(blockAlign >> 8));
      uVar1 = dataSize / ((byteRate >> 3) * blockAlign);
      puVar2 = header + 7;
      *(uint *)((int)header + 0x16) =
           (uVar1 & 0xff00 | uVar1 << 0x10) << 8 | (uVar1 & 0xff0000 | uVar1 >> 0x10) >> 8;
      *(ushort *)((int)header + 0x1a) = CONCAT11((char)byteRate,(char)(byteRate >> 8));
      if (rate == 0x2b11) {
        *puVar2 = 0x44ac0c40;
        header[8] = 0;
      }
      else if (rate == 0xac44) {
        *puVar2 = 0x44ac0e40;
        header[8] = 0;
      }
      else {
        *puVar2 = 0x44ac0d40;
        header[8] = 0;
      }
      *(undefined2 *)(header + 9) = 0;
      uVar1 = dataSize + 8;
      *(undefined4 *)((int)header + 0x26) = DAT_10017050;
      *(uint *)((int)header + 0x2a) =
           (uVar1 & 0xff00 | uVar1 * 0x10000) << 8 | (uVar1 & 0xff0000 | uVar1 >> 0x10) >> 8;
      *(undefined4 *)((int)header + 0x2e) = 0;
      *(undefined4 *)((int)header + 0x32) = 0;
      return 0x36;
    }
  }
  return (int)puVar2 - (int)header;
}

/* ---- 0x10001ba0  AudioLib_ResetCompressor ---- */
/* Unidentified function of compressed audio decoding (VIMA/ADPCM style tables) - module name
   inferred Original name AudioLib_ResetCompressor (the remaster's GrimFandango (Linux): aligned
   call in iRes_FOPEN); was Im_CodecInit. */

void __cdecl AudioLib_ResetCompressor(undefined1 *state)

{
  state[1] = 0;
  *state = 0;
  *(undefined2 *)(state + 4) = 0;
  *(undefined2 *)(state + 2) = 0;
  return;
}

/* ---- 0x10001bc0  AudioLib_UncompressBlock ---- */
/* Unidentified function of compressed audio decoding (VIMA/ADPCM style tables) - module name
   inferred Original name AudioLib_UncompressBlock (the remaster's GrimFandango (Linux): aligned
   call in iRes_FREAD); was Im_ConvertBlock. */

void __cdecl AudioLib_UncompressBlock(byte *dst,undefined2 *src,byte *local_c,uint size)

{
  byte bVar1;
  byte *codes;
  uint channels;
  
  bVar1 = *local_c;
  channels = 1;
  *dst = bVar1;
  if ((char)bVar1 < '\0') {
    *dst = ~bVar1;
    channels = 2;
  }
  codes = local_c + 3;
  *(ushort *)(dst + 2) =
       CONCAT11((char)*(undefined2 *)(local_c + 1),(char)((ushort)*(undefined2 *)(local_c + 1) >> 8)
               );
  if (1 < channels) {
    dst[1] = *codes;
    codes = local_c + 6;
    *(ushort *)(dst + 4) =
         CONCAT11((char)*(undefined2 *)(local_c + 4),
                  (char)((ushort)*(undefined2 *)(local_c + 4) >> 8));
  }
  Im_ConvertBlockImpl((short *)dst,src,codes,size / (channels * 2),channels,1);
  return;
}

/* ---- 0x10001c30  Im_ConvertBlockImpl ---- */
/* Unidentified function of compressed audio decoding (VIMA/ADPCM style tables) - module name
   inferred */

void __cdecl
Im_ConvertBlockImpl(short *dst,undefined2 *src,byte *codes,int count,uint channels,int step)

{
  byte bVar1;
  ushort uVar2;
  uint uVar3;
  uint uVar4;
  short sVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  short *psVar9;
  short *psVar10;
  uint local_24;
  short *local_20;
  undefined2 *local_1c;
  int local_18;
  uint local_14;
  uint local_8;
  
  iVar7 = 0;
  if (DAT_10024dc0 == 0) {
    uVar8 = 0;
    local_20 = &DAT_10022140;
    do {
      psVar9 = g_wAdpcmStepTable;
      psVar10 = local_20;
      do {
        uVar2 = *psVar9;
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
        psVar9 = psVar9 + 1;
        psVar10 = psVar10 + 0x40;
      } while (psVar9 < &DAT_100152da);
      uVar8 = uVar8 + 1;
      local_20 = local_20 + 1;
    } while (local_20 < &DAT_100221c0);
    DAT_10024dc0 = 1;
  }
  if (step == 0) {
    *(undefined1 *)((int)dst + 1) = 0;
    *(undefined1 *)dst = 0;
    dst[2] = 0;
    dst[1] = 0;
  }
  local_24 = (uint)CONCAT11(*codes,codes[1]);
  codes = codes + 2;
  local_14 = 0;
  if (channels != 0) {
    local_20 = src;
    psVar10 = dst;
    do {
      psVar10 = psVar10 + 1;
      local_1c = local_20;
      step = (int)*(char *)(local_14 + (int)dst);
      uVar8 = (uint)*psVar10;
      if (count != 0) {
        local_18 = count;
        do {
          bVar1 = g_abAdpcmStepBits[step];
          iVar7 = iVar7 + (uint)bVar1;
          uVar6 = 1 << (bVar1 - 1 & 0x1f);
          local_8 = (uint)(byte)((char)uVar6 - 1);
          uVar3 = (local_24 & 0xffff) >> (0x10U - (char)iVar7 & 0x1f) & (uVar6 | local_8);
          if (7 < iVar7) {
            local_24 = (local_24 & 0xff) << 8 |
                       CONCAT22((short)((uint)codes >> 0x10),(ushort)*codes);
            codes = codes + 1;
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
                    (ushort)(CONCAT11((undefined1)local_24,*codes) >> (8 - (byte)iVar7 & 0x1f)) &
                    0xff;
            local_24 = (uint)CONCAT11(*codes,codes[1]);
            codes = codes + 2;
          }
          else {
            uVar4 = (uint)(ushort)(&DAT_10022140)[uVar3 << (7 - bVar1 & 0x1f) | step << 6];
            if (uVar3 != 0) {
              uVar4 = uVar4 + ((ushort)g_wAdpcmStepTable[step] >> (bVar1 - 1 & 0x1f));
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
          local_1c = local_1c + channels;
          step = step + g_apAdpcmIndexAdjust[bVar1][uVar3];
          if (step < 0) {
            step = 0;
          }
          else if (0x58 < step) {
            step = 0x58;
          }
          local_18 = local_18 + -1;
        } while (local_18 != 0);
      }
      *(undefined1 *)(local_14 + (int)dst) = (undefined1)step;
      *psVar10 = (short)uVar8;
      local_14 = local_14 + 1;
      local_20 = local_20 + 1;
    } while (local_14 < channels);
  }
  return;
}

/* ---- 0x10001f10  DpInitialize ---- */
/* iMUSE_Dispatch.c: allocates the dispatch slots Original name DpInitialize (the remaster's
   GrimFandango (Linux): aligned call in TrInitialize); was Im_DispatchInit. */

undefined4 DpInitialize(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  g_dwMemAddr = (**(code **)(g_dwSounds_pHS + 0x20))
                          (g_dwImLargeFadeCount * g_dwImLargeFadeSize +
                           g_dwImSmallFadeCount * g_dwImSmallFadeSize +
                           (g_dwImSmallFadeCount + g_dwImLargeFadeCount) * 4,
                           s_C__grimsrc_libs_iMUSE_Dispatch_c_100170c0,0x41);
  if (g_dwMemAddr == 0) {
    return 0xffffffff;
  }
  g_dwSmallFadeBufs = g_dwMemAddr + g_dwImLargeFadeCount * g_dwImLargeFadeSize;
  g_pSmallFadeFlags =
       (int *)((g_dwImLargeFadeSize + 4) * g_dwImLargeFadeCount + g_dwMemAddr +
              g_dwImSmallFadeCount * g_dwImSmallFadeSize);
  PTR_10024dc8 = (int *)(g_dwMemAddr + g_dwImSmallFadeCount * g_dwImSmallFadeSize +
                        g_dwImLargeFadeCount * g_dwImLargeFadeSize);
  g_dwLargeFadeBufs = g_dwMemAddr;
  *PTR_10024dc8 = 0;
  *g_pSmallFadeFlags = 0;
  puVar2 = &g_dwStreamZones;
  for (iVar1 = 300; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  return 0;
}

/* ---- 0x10002260  DpSwitchStream ---- */
/* Body of ImSwitchStream (sound, offset, fade, flags) Original name DpSwitchStream (the remaster's
   GrimFandango (Linux): case 0x1a of ImSoundCall calls it where the v1.01 dispatcher calls the
   exported API that calls this function); was Im_SwitchStreamImpl. */

undefined4 __cdecl DpSwitchStream(int sound,undefined4 offset,uint fade,uint flags,uint hookFlags)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  uint uVar6;
  int *dp;
  undefined4 *puVar7;
  
  dp = &g_dwDispatches;
  ImWaveHalt();
  if (2000 < fade) {
    fade = 2000;
  }
  iVar2 = 0;
  if (0 < g_dwTrackCount) {
    do {
      if (((sound != 0) && (sound == *(int *)(*dp + 0xc))) && (dp[0x207] != 0)) break;
      iVar2 = iVar2 + 1;
      dp = dp + 0x215;
    } while (iVar2 < g_dwTrackCount);
  }
  if (iVar2 == g_dwTrackCount) {
    ImWaveProceed();
    return 0xffffffff;
  }
  if (dp[0x209] != 0) {
    if (dp[1] == 0) {
      ImWaveProceed();
      return 0xffffffff;
    }
    if (dp[0x20b] != 0) {
      iMUSE_Dispatch__3640(dp[0x20b]);
    }
    uVar3 = ((fade * dp[2]) / 1000) * dp[1] * dp[3] >> 3;
    if (*(uint *)(dp[0x209] + 0x10) <= uVar3) {
      uVar3 = *(uint *)(dp[0x209] + 0x10);
    }
    g_dwLargeFadeFlags = uVar3 - ((dp[1] >> 3) * dp[3] - 1U & uVar3);
    iVar2 = iMUSE_Dispatch__35a0(&g_dwLargeFadeFlags);
    dp[0x20b] = iVar2;
    uVar3 = g_dwLargeFadeFlags;
    if (iVar2 != 0) {
      dp[0x20e] = dp[1];
      dp[0x210] = dp[3];
      dp[0x20c] = 0;
      dp[0x211] = hookFlags | flags;
      uVar4 = 0;
      dp[0x20d] = 0;
      dp[0x20f] = dp[2];
      dp[0x212] = 0;
      dp[0x213] = 0x7f0000;
      dp[0x214] = 0;
      if (uVar3 != 0) {
        do {
          uVar4 = uVar3 - uVar4;
          if (0x3fff < uVar4) {
            uVar4 = 0x4000;
          }
          puVar5 = (undefined4 *)StReadData(dp[0x207],uVar4);
          if (puVar5 < (undefined4 *)0x10000) {
            uVar4 = g_dwLargeFadeFlags - dp[0x20d];
            puVar5 = (undefined4 *)(dp[0x20d] + dp[0x20b]);
            for (uVar3 = uVar4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
              *puVar5 = 0;
              puVar5 = puVar5 + 1;
            }
            for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
              *(undefined1 *)puVar5 = 0;
              puVar5 = (undefined4 *)((int)puVar5 + 1);
            }
            dp[0x20d] = g_dwLargeFadeFlags;
            break;
          }
          puVar7 = (undefined4 *)(dp[0x20b] + dp[0x20d]);
          for (uVar3 = uVar4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
            *puVar7 = *puVar5;
            puVar5 = puVar5 + 1;
            puVar7 = puVar7 + 1;
          }
          for (uVar6 = uVar4 & 3; uVar3 = g_dwLargeFadeFlags, uVar6 != 0; uVar6 = uVar6 - 1) {
            *(undefined1 *)puVar7 = *(undefined1 *)puVar5;
            puVar5 = (undefined4 *)((int)puVar5 + 1);
            puVar7 = (undefined4 *)((int)puVar7 + 1);
          }
          uVar4 = dp[0x20d] + uVar4;
          dp[0x20d] = uVar4;
        } while (uVar4 < uVar3);
      }
    }
  }
  FdStopFade(*(int *)(*dp + 0xc),-1);
  TgClearTrigger(*(int *)(*dp + 0xc),(byte *)0xffffffff,-1);
  *(undefined4 *)(*dp + 0xc) = offset;
  uVar3 = StGetValidSize(dp[0x207]);
  StEraseFromFront(dp[0x207],uVar3);
  if ((hookFlags != 0) && (piVar1 = dp + 0x209, dp[0x209] != 0)) {
    StSpliceStream((undefined4 *)dp[0x207],offset,dp[5]);
    iVar2 = *(int *)(*piVar1 + 4);
    while (iVar2 != 0) {
      *(undefined4 *)(iVar2 + 8) = 0;
      UtRemoveFromList((int *)(*piVar1 + 4),*(int **)(*piVar1 + 4));
      iVar2 = *(int *)(*piVar1 + 4);
    }
    *(undefined4 *)(*piVar1 + 0x10) = 0;
    ImWaveProceed();
    return 0;
  }
  StSpliceStream((undefined4 *)dp[0x207],offset,0);
  piVar1 = dp + 0x209;
  iVar2 = dp[0x209];
  while (iVar2 != 0) {
    *(undefined4 *)(iVar2 + 8) = 0;
    UtRemoveFromList(piVar1,(int *)*piVar1);
    iVar2 = *piVar1;
  }
  *(undefined1 *)(dp + 7) = 0;
  dp[6] = 0;
  dp[5] = 0;
  iVar2 = GoToNextRegion(dp);
  if ((iVar2 != 0) && (iVar2 != -3)) {
    TrStopTrack((int *)*dp);
    ImWaveProceed();
    return 0xffffffff;
  }
  ImWaveProceed();
  return 0;
}

/* ---- 0x10002570  DpProcessTrack ---- */
/* WARNING: Removing unreachable block (ram,0x10002950) */
/* Pulls decoded data for one track and mixes it (Im_MixSamples) Original name DpProcessTrack (the
   remaster's GrimFandango (Linux): aligned call in TrIntHandler); was Im_DispatchMixTrack. */

void __cdecl
DpProcessTrack(int *track,uint trIntHandler_outFramesNeeded,uint trIntHandler_outSampleRate)

{
  int *dp;
  uint uVar1;
  uint uVar2;
  int iVar3;
  short *src;
  uint uVar4;
  uint uVar5;
  uint local_8;
  uint local_4;
  
  dp = (int *)track[2];
  if ((dp[0x207] != 0) && (dp[0x209] != 0)) {
    PredictStream(dp);
  }
  if (dp[0x20b] != 0) {
    uVar1 = (uint)(dp[0x20d] << 3) / (uint)(dp[0x20e] * dp[0x210]);
    local_8 = dp[0x20f] * track[0xc] >> 8;
    uVar2 = (trIntHandler_outFramesNeeded * local_8) / trIntHandler_outSampleRate;
    if (uVar1 < uVar2) {
      local_8 = (uVar1 * trIntHandler_outSampleRate) / local_8;
      uVar2 = uVar1;
    }
    else {
      local_8 = trIntHandler_outFramesNeeded;
    }
    if (uVar2 != 0) {
      uVar1 = uVar2 * dp[0x20e] * dp[0x210] >> 3;
      iVar3 = iMUSE_Dispatch__3510(dp,uVar1);
      Mixer_MxMix((short *)(dp[0x20b] + dp[0x20c]),uVar2,dp[0x20e],dp[0x210],dp[4],local_8,0,iVar3,
                  track[9]);
      iVar3 = dp[0x20d];
      dp[0x20c] = dp[0x20c] + uVar1;
      dp[0x20d] = iVar3 - uVar1;
      if (iVar3 - uVar1 != 0) goto LAB_10002693;
    }
    iMUSE_Dispatch__3640(dp[0x20b]);
    dp[0x20b] = 0;
  }
LAB_10002693:
  local_4 = 0;
  do {
    if (dp[6] == 0) {
      g_dwFadeStartedFlag = 0;
      iVar3 = GoToNextRegion(dp);
      if (iVar3 != 0) {
        if (iVar3 == -1) {
          TrStopTrack(track);
        }
        if (dp[0x20b] == 0) {
          return;
        }
        if (dp[0x211] == 0) {
          return;
        }
        dp[0x212] = dp[0x212] + trIntHandler_outFramesNeeded;
        return;
      }
      if (g_dwFadeStartedFlag != 0) {
        uVar1 = (uint)(dp[0x20d] << 3) / (uint)(dp[0x20e] * dp[0x210]);
        uVar4 = dp[0x20f] * track[0xc] >> 8;
        uVar2 = (trIntHandler_outFramesNeeded * uVar4) / trIntHandler_outSampleRate;
        local_8 = trIntHandler_outFramesNeeded;
        if (uVar1 < uVar2) {
          local_8 = (uVar1 * trIntHandler_outSampleRate) / uVar4;
          uVar2 = uVar1;
        }
        uVar1 = uVar2 * dp[0x20e] * dp[0x210] >> 3;
        iVar3 = iMUSE_Dispatch__3510(dp,uVar1);
        Mixer_MxMix((short *)(dp[0x20b] + dp[0x20c]),uVar2,dp[0x20e],dp[0x210],dp[4],local_8,local_4
                    ,iVar3,track[9]);
        iVar3 = dp[0x20d];
        dp[0x20c] = dp[0x20c] + uVar1;
        dp[0x20d] = iVar3 - uVar1;
        if (iVar3 - uVar1 == 0) {
          iMUSE_Dispatch__3640(dp[0x20b]);
          dp[0x20b] = 0;
        }
      }
    }
    if (trIntHandler_outFramesNeeded == 0) {
      return;
    }
    uVar1 = (uint)(dp[6] << 3) / (uint)(dp[3] * dp[1]);
    uVar4 = dp[2] * track[0xc] >> 8;
    local_8 = (trIntHandler_outFramesNeeded * uVar4) / trIntHandler_outSampleRate;
    uVar2 = trIntHandler_outFramesNeeded;
    if (uVar1 < local_8) {
      uVar2 = (uVar1 * trIntHandler_outSampleRate) / uVar4;
      local_8 = uVar1;
    }
    if (local_8 == 0) {
      TrStopTrack(track);
      return;
    }
    uVar1 = local_8 * dp[3] * dp[1] >> 3;
    if (dp[0x207] == 0) {
      iVar3 = FmGetSoundAddr(track[3]);
      if (iVar3 == 0) {
        return;
      }
      src = (short *)(iVar3 + dp[5]);
    }
    else {
      src = (short *)StReadData(dp[0x207],uVar1);
      if (src == (short *)0x0) {
        dp[0x20a] = 1;
        if ((dp[0x20b] != 0) && (dp[0x211] != 0)) {
          dp[0x212] = dp[0x212] + trIntHandler_outFramesNeeded;
        }
        StQueryStream(dp[0x207],(undefined4 *)&g_dwDpProcessTrack_bufSize,
                      (undefined4 *)&g_dwDpProcessTrack_critSize,(int *)&g_dwDpProcessTrack_curLevel
                      ,(undefined4 *)&g_dwDpProcessTrack_pauseFlag);
        return;
      }
      *(uint *)(dp[0x209] + 0xc) = *(int *)(dp[0x209] + 0xc) + uVar1;
      *(uint *)(dp[0x209] + 0x10) = *(int *)(dp[0x209] + 0x10) - uVar1;
      dp[0x20a] = 0;
    }
    if (dp[0x20b] == 0) {
LAB_100028ef:
      iVar3 = track[8];
    }
    else {
      if ((dp[0x211] != 0) && (uVar4 = dp[0x212], uVar4 != 0)) {
        uVar5 = uVar4;
        if (uVar2 <= uVar4) {
          uVar5 = uVar2;
        }
        uVar2 = uVar2 - uVar5;
        dp[0x212] = uVar4 - uVar5;
        local_8 = ((dp[2] * track[0xc] >> 8) * uVar2) / trIntHandler_outSampleRate;
        src = (short *)((int)src + (uVar1 - (local_8 * dp[3] * dp[1] >> 3)));
      }
      if (dp[0x20b] == 0) goto LAB_100028ef;
      iVar3 = iMUSE_Dispatch__34b0(dp);
    }
    Mixer_MxMix(src,local_8,dp[1],dp[3],dp[4],uVar2,local_4,iVar3,track[9]);
    local_4 = local_4 + uVar2;
    dp[5] = dp[5] + uVar1;
    dp[6] = dp[6] - uVar1;
    trIntHandler_outFramesNeeded = trIntHandler_outFramesNeeded - uVar2;
  } while( true );
}

/* ---- 0x10002a60  GoToNextRegion ---- */
/* WARNING: Removing unreachable block (ram,0x10002cfb) */
/* Original name GoToNextRegion (the remaster's GrimFandango (Linux): aligned call in
   DpProcessTrack, DpStartSound, DpSwitchStream); was Im_DispatchAllocBuffers. */

int __cdecl GoToNextRegion(int *dp)

{
  int *head;
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  uint size;
  int *prev;
  undefined4 *puVar5;
  int local_4;
  
  local_4 = -1;
  if (DAT_1002d814 == 0) {
    InitializeCriticalSection(((unsigned)(uintptr_t)&DAT_1002d7f0));
    DAT_1002d814 = 1;
  }
  EnterCriticalSection(((unsigned)(uintptr_t)&DAT_1002d7f0));
  iVar1 = Im_DispatchFetchNext(dp);
  if (((iVar1 == 0) && (iVar1 = local_4, dp[6] == 0)) &&
     ((dp[0x207] == 0 || (dp[5] == *(int *)(dp[0x209] + 0xc))))) {
    prev = (int *)0x0;
    do {
      do {
        while( true ) {
          prev = (int *)iMUSE_Dispatch__30d0((int)(dp + 7),dp[5],(int)prev);
          if (prev == (int *)0x0) goto LAB_10002d11;
          iVar2 = *prev;
          if (0x4a554d50 < iVar2) break;
          if (iVar2 == 0x4a554d50) {
            iVar2 = UtCheckHook((int *)(*dp + 0x38),prev[4]);
            if (iVar2 == 0) {
              dp[5] = prev[3];
              if (dp[0x207] != 0) {
                puVar3 = (undefined4 *)dp[0x209];
                head = dp + 0x209;
                if ((puVar3[4] != 0) || (puVar3[1] == 0)) {
                  PrepareToJump(dp,puVar3,(int)prev,1);
                }
                *(undefined4 *)(*head + 8) = 0;
                UtRemoveFromList(head,(int *)*head);
                if (*(int *)(*head + 0x14) != 0) {
                  if (dp[0x20b] != 0) {
                    iMUSE_Dispatch__3640(dp[0x20b]);
                  }
                  g_dwGoToNextRegion_fadeSize = *(uint *)(*head + 0x10);
                  iVar2 = iMUSE_Dispatch__35a0(&g_dwGoToNextRegion_fadeSize);
                  dp[0x20b] = iVar2;
                  if (iVar2 != 0) {
                    dp[0x20c] = 0;
                    dp[0x20d] = 0;
                    dp[0x20e] = dp[1];
                    dp[0x20f] = dp[2];
                    dp[0x210] = dp[3];
                    dp[0x211] = 0;
                    dp[0x212] = 0;
                    dp[0x213] = 0x7f0000;
                    dp[0x214] = 0;
                    if (g_dwGoToNextRegion_fadeSize != 0) {
                      do {
                        size = g_dwGoToNextRegion_fadeSize - dp[0x20d];
                        if (0x3fff < size) {
                          size = 0x4000;
                        }
                        puVar3 = (undefined4 *)StReadData(dp[0x207],size);
                        puVar5 = (undefined4 *)(dp[0x20d] + dp[0x20b]);
                        for (uVar4 = size >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
                          *puVar5 = *puVar3;
                          puVar3 = puVar3 + 1;
                          puVar5 = puVar5 + 1;
                        }
                        for (uVar4 = size & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
                          *(undefined1 *)puVar5 = *(undefined1 *)puVar3;
                          puVar3 = (undefined4 *)((int)puVar3 + 1);
                          puVar5 = (undefined4 *)((int)puVar5 + 1);
                        }
                        iVar2 = dp[0x20d];
                        dp[0x20d] = iVar2 + size;
                      } while (iVar2 + size < g_dwGoToNextRegion_fadeSize);
                    }
                    g_dwFadeStartedFlag = 1;
                  }
                  *(undefined4 *)(dp[0x209] + 8) = 0;
                  UtRemoveFromList(dp + 0x209,(int *)dp[0x209]);
                }
              }
              prev = (int *)0x0;
            }
          }
          else {
            if (iVar2 != 0x46524d54) goto LAB_10002d11;
            dp[4] = (uint)(prev[3] == 0);
            dp[1] = prev[4];
            dp[2] = prev[5];
            dp[3] = prev[6];
          }
        }
        if (iVar2 == 0x5245474e) {
          dp[6] = prev[3];
          goto LAB_10002d0d;
        }
      } while (iVar2 == 0x53594e43);
      if (iVar2 != 0x54455854) goto LAB_10002d11;
      iVar2 = *(int *)(*dp + 0xc);
      TgProcessMarker(iVar2,(char *)(prev + 3));
      if (iVar2 != *(int *)(*dp + 0xc)) {
        local_4 = -3;
        iVar1 = local_4;
        goto LAB_10002d11;
      }
    } while (dp[6] == 0);
LAB_10002d0d:
    local_4 = 0;
    iVar1 = local_4;
  }
LAB_10002d11:
  local_4 = iVar1;
  LeaveCriticalSection(((unsigned)(uintptr_t)&DAT_1002d7f0));
  return local_4;
}

/* ---- 0x10002d30  Im_DispatchFetchNext ---- */
/* Advances a dispatch through its sound regions / jumps and fetches the next data */

int __cdecl Im_DispatchFetchNext(int *dp)

{
  unsigned char _frame[0x70] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *dst;
  uint size;
  int *piVar1;
  int *piVar2;
  undefined1 *p;
  int iVar3;
  uint *header;
  uint *puVar4;
  undefined4 *puVar5;
  char *pcVar6;
  bool bVar7;
  #define local_58 (*(uint *)(_frame + (0x70 - 0x58)))
  #define local_54 (*(uint *)(_frame + (0x70 - 0x54)))
  #define local_50 (*(undefined4 (*)[7])(_frame + (0x70 - 0x50)))
  #define local_31 (*(undefined1 *)(_frame + (0x70 - 0x31)))
  
  piVar2 = dp;
  dst = dp + 7;
  if (dp[7] == 0x4d415020) {
    if (dp[0x207] == 0) {
      return 0;
    }
    if (dp[0x209] != 0) {
      return 0;
    }
  }
  if (dp[5] != 0) {
    return -1;
  }
  piVar1 = dp + 0x207;
  if (*piVar1 == 0) {
    p = (undefined1 *)FmGetMapAddr(*(uint *)(*dp + 0xc));
    if (p == (undefined1 *)0x0) {
      return -1;
    }
    iVar3 = UtReadLongHilo(p);
    if (iVar3 != 0x694d5553) {
      return -1;
    }
    iVar3 = UtReadLongHilo(p + 8);
    if (iVar3 != 0x4d415020) {
      return -1;
    }
    iVar3 = UtReadLongHilo(p + 0xc);
    piVar2[5] = iVar3 + 0x18;
    iVar3 = ConvertMap((undefined4 *)(p + 8),dst);
    if (iVar3 != 0) {
      return -1;
    }
    if (piVar2[9] != 0x46524d54) {
      return -1;
    }
    return -(uint)(piVar2[5] != piVar2[0xb]);
  }
  dp = (int *)0x0;
  header = (uint *)StViewData(*piVar1,0,0x40);
  if (header == (uint *)0x0) {
    return -3;
  }
  iVar3 = 4;
  bVar7 = true;
  puVar4 = header;
  pcVar6 = &DAT_10017090;
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    bVar7 = (char)*puVar4 == *pcVar6;
    puVar4 = (uint *)((int)puVar4 + 1);
    pcVar6 = pcVar6 + 1;
  } while (bVar7);
  if (bVar7) {
    iVar3 = 8;
    bVar7 = true;
    puVar4 = header + 2;
    pcVar6 = &DAT_10017084;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      bVar7 = (char)*puVar4 == *pcVar6;
      puVar4 = (uint *)((int)puVar4 + 1);
      pcVar6 = pcVar6 + 1;
    } while (bVar7);
    if (bVar7) {
      puVar4 = AudioLib_ParseWaveFileHeader
                         (header,(int *)0x0,&local_54,(uint *)0x0,&local_58,(int *)0x0,(uint *)&dp);
      piVar2[5] = (int)puVar4 - (int)header;
      iVar3 = StReadData(piVar2[0x207],(int)puVar4 - (int)header);
      if (iVar3 == 0) {
        return -1;
      }
      AudioLib_CreateWaveFileHeader(local_50,3,local_54,0x10,local_58,(uint)dp);
      local_31 = 1;
      puVar5 = local_50;
      goto LAB_10002f3c;
    }
  }
  iVar3 = 4;
  bVar7 = true;
  puVar4 = header;
  pcVar6 = (char *)&DAT_10017074;
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    bVar7 = (char)*puVar4 == *pcVar6;
    puVar4 = (uint *)((int)puVar4 + 1);
    pcVar6 = pcVar6 + 1;
  } while (bVar7);
  if (!bVar7) {
    return -1;
  }
  iVar3 = 4;
  bVar7 = true;
  puVar4 = header + 2;
  pcVar6 = (char *)&DAT_100170b8;
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    bVar7 = (char)*puVar4 == *pcVar6;
    puVar4 = (uint *)((int)puVar4 + 1);
    pcVar6 = pcVar6 + 1;
  } while (bVar7);
  if (!bVar7) {
    return -1;
  }
  iVar3 = UtReadLongHilo((undefined1 *)(header + 3));
  size = iVar3 + 0x18;
  iVar3 = StViewData(piVar2[0x207],0,size);
  if (iVar3 == 0) {
    return -3;
  }
  puVar5 = (undefined4 *)StReadData(piVar2[0x207],size);
  if (puVar5 == (undefined4 *)0x0) {
    return -1;
  }
  piVar2[5] = size;
LAB_10002f3c:
  iVar3 = ConvertMap(puVar5 + 2,piVar2 + 7);
  if (iVar3 == 0) {
    if (dp != (int *)0x0) {
      piVar2[0xb] = piVar2[5];
      piVar2[0x12] = piVar2[5];
      piVar2[0x16] = (int)dp + piVar2[5];
    }
    if (((piVar2[9] == 0x46524d54) && (piVar2[5] == piVar2[0xb])) && (piVar2[0x209] == 0)) {
      puVar5 = iMUSE_Dispatch__3570();
      piVar2[0x209] = (int)puVar5;
      if (puVar5 != (undefined4 *)0x0) {
        puVar5[3] = piVar2[5];
        iVar3 = StGetValidSize(piVar2[0x207]);
        *(int *)(piVar2[0x209] + 0x10) = iVar3;
        *(undefined4 *)(piVar2[0x209] + 0x14) = 0;
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


/* ---- 0x100036b0  DwInitialize ---- */
/* iMUSE_dsound.c Original name DwInitialize (the remaster's GrimFandango (Linux): aligned call in
   TrInitialize); was Im_DSoundInit. */

undefined4 __cdecl DwInitialize(undefined4 services,undefined4 *trInitialize_waveDriverInfo)

{
  int iVar1;
  int *piVar2;
  
  PTR_1002d830 = (int *)(**(code **)(g_dwSounds_pHS + 0x20))
                                  (0x3000,s_C__grimsrc_libs_iMUSE_dsound_c_10017104,0x50);
  DAT_1002d818 = PTR_1002d830 + 0x600;
  PTR_1002d834 = DAT_100336bc;
  Im_DSoundCreateBuffer(3);
  *trInitialize_waveDriverInfo = 2;
  trInitialize_waveDriverInfo[2] = 0x1800;
  trInitialize_waveDriverInfo[3] = 0;
  trInitialize_waveDriverInfo[1] = PTR_1002d830;
  piVar2 = PTR_1002d830;
  for (iVar1 = 0xc00; iVar1 != 0; iVar1 = iVar1 + -1) {
    *piVar2 = 0;
    piVar2 = piVar2 + 1;
  }
  DAT_1002d844 = 0;
  return 0;
}

/* ---- 0x10003730  DwQuery ---- */
/* Fills the DirectSound stream buffer from the mixer once per tick Original name DwQuery (the
   remaster's GrimFandango (Linux): aligned call in TrIntHandler); was Im_DSoundHeartbeat. */

int __cdecl DwQuery(int **buf_out,uint *count_out,int *rate_out)

{
  int iVar1;
  int **ppiVar2;
  int **ppiVar3;
  uint uVar4;
  uint uVar5;
  int *piVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  
  *count_out = 0;
  uVar5 = DAT_1002d82c;
  ppiVar3 = DAT_1002d840;
  if ((DAT_1002d840 == (int **)0x0) && (ppiVar3 = DAT_1002d844, DAT_1002d844 == (int **)0x0)) {
    DAT_1002d848 = DAT_1002d848 ^ 1;
    if (DAT_1002d848 == 0) {
      ppiVar3 = (int **)0x0;
      if (g_dwCurrentWriteIndex != 0) {
        DAT_1002d848 = 0;
        if ((DAT_1002d854 != (undefined4 *)0x0) && (DAT_1002d820 != 0)) {
          piVar6 = DAT_1002d818;
          ppiVar3 = DAT_1002d850;
          for (uVar4 = DAT_1002d82c >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
            *ppiVar3 = (int *)*piVar6;
            piVar6 = piVar6 + 1;
            ppiVar3 = ppiVar3 + 1;
          }
          for (uVar5 = uVar5 & 3; uVar4 = DAT_1002d820, uVar5 != 0; uVar5 = uVar5 - 1) {
            *(char *)ppiVar3 = (char)*piVar6;
            piVar6 = (int *)((int)piVar6 + 1);
            ppiVar3 = (int **)((int)ppiVar3 + 1);
          }
          puVar7 = (undefined4 *)(DAT_1002d82c + (int)DAT_1002d818);
          puVar8 = DAT_1002d854;
          for (uVar5 = DAT_1002d820 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
            *puVar8 = *puVar7;
            puVar7 = puVar7 + 1;
            puVar8 = puVar8 + 1;
          }
          for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
            *(undefined1 *)puVar8 = *(undefined1 *)puVar7;
            puVar7 = (undefined4 *)((int)puVar7 + 1);
            puVar8 = (undefined4 *)((int)puVar8 + 1);
          }
        }
        iVar1 = (**(code_std **)(*PTR_1002d83c + 0x4c))
                          (PTR_1002d83c,DAT_1002d850,DAT_1002d82c,DAT_1002d854,DAT_1002d820);
        g_dwCurrentWriteIndex = 0;
        return iVar1;
      }
    }
    else {
      ppiVar2 = (int **)iMUSE_dsound__3a80();
      ppiVar3 = ppiVar2;
      if (ppiVar2 != (int **)0xffffffff) {
        ppiVar3 = (int **)(((int)PTR_100170ec + 1) / DAT_1002d824);
        if (ppiVar2 != (int **)(((int)PTR_100170ec + 1) % DAT_1002d824)) {
          if ((int)PTR_100170ec < 0) {
            PTR_100170ec = (int *)ppiVar2;
          }
          PTR_100170ec = (int *)((int)((int)PTR_100170ec + 1) % DAT_1002d824);
          ppiVar3 = (int **)(**(code_std **)(*PTR_1002d83c + 0x2c))
                                      (PTR_1002d83c,(int)PTR_100170ec * 0x1800,0x1800,&DAT_1002d850,
                                       &DAT_1002d82c,&DAT_1002d854,&DAT_1002d820,0);
          ppiVar2 = DAT_1002d850;
          if (ppiVar3 == (int **)0x0) {
            if ((DAT_1002d854 == (undefined4 *)0x0) || (DAT_1002d820 == 0)) {
              *buf_out = (int *)DAT_1002d850;
              *count_out = DAT_1002d82c >> 2;
            }
            else {
              *buf_out = DAT_1002d818;
              *count_out = 0x600;
              ppiVar2 = buf_out;
            }
            *rate_out = 0x5622;
            g_dwCurrentWriteIndex = 1;
            ppiVar3 = ppiVar2;
          }
        }
      }
    }
  }
  return (int)ppiVar3;
}

/* ---- 0x100038d0  DwTerminate ---- */
/* Original name DwTerminate (the remaster's GrimFandango (Linux): called by TrTerminate at the same
   place); was Im_DSoundShutdown. */

undefined4 DwTerminate(void)

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
  (**(code **)(g_dwSounds_pHS + 0x24))(PTR_1002d830);
  return 0;
}

/* ---- 0x10003930  Im_DSoundCreateBuffer ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Unidentified function of iMUSE_dsound.c (DirectSound output) */

void __cdecl Im_DSoundCreateBuffer(int blocks)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  #define uStack_20 (*(uint *)(_frame + (0x30 - 0x20)))
  #define uStack_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define puStack_18 (*(undefined4 **)(_frame + (0x30 - 0x18)))
  #define uStack_14 (*(undefined4 *)(_frame + (0x30 - 0x14)))
  #define uStack_10 (*(undefined4 *)(_frame + (0x30 - 0x10)))
  #define iStack_c (*(int *)(_frame + (0x30 - 0xc)))
  #define uStack_8 (*(undefined4 *)(_frame + (0x30 - 0x8)))
  #define puStack_4 (*(undefined **)(_frame + (0x30 - 0x4)))
  
  DAT_1002d840 = 1;
  if (PTR_1002d83c != (int *)0x0) {
    (**(code_std **)(*PTR_1002d83c + 8))(PTR_1002d83c);
  }
  PTR_1002d83c = (int *)0x0;
  DAT_1002d824 = blocks;
  if (blocks < 3) {
    DAT_1002d824 = 3;
  }
  if (0x10 < DAT_1002d824) {
    DAT_1002d824 = 0x10;
  }
  uStack_14 = 0x14;
  uStack_10 = 0x18080;
  iStack_c = DAT_1002d824 * 0x1800;
  uStack_8 = 0;
  puStack_4 = &DAT_100170f0;
  iVar1 = (**(code_std **)(*PTR_1002d834 + 0xc))(PTR_1002d834,&uStack_14,&PTR_1002d83c,0);
  if (iVar1 == 0) {
    (**(code_std **)(*PTR_1002d83c + 0x3c))(PTR_1002d83c,0);
    iVar1 = (**(code_std **)(*PTR_1002d83c + 0x2c))
                      (PTR_1002d83c,0,DAT_1002d824 * 0x1800,&puStack_18,&uStack_1c,&blocks,
                       &uStack_20,0);
    if (iVar1 == 0) {
      puVar3 = puStack_18;
      for (uVar2 = uStack_1c >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar3 = 0;
        puVar3 = puVar3 + 1;
      }
      for (uVar2 = uStack_1c & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *(undefined1 *)puVar3 = 0;
        puVar3 = (undefined4 *)((int)puVar3 + 1);
      }
      if (blocks != 0) {
        puVar3 = (undefined4 *)blocks;
        for (uVar2 = uStack_20 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
          *puVar3 = 0;
          puVar3 = puVar3 + 1;
        }
        for (uVar2 = uStack_20 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
          *(undefined1 *)puVar3 = 0;
          puVar3 = (undefined4 *)((int)puVar3 + 1);
        }
      }
      (**(code_std **)(*PTR_1002d83c + 0x4c))(PTR_1002d83c,puStack_18,uStack_1c,blocks,uStack_20);
    }
    (**(code_std **)(*PTR_1002d83c + 0x30))(PTR_1002d83c,0,0,1);
  }
  DAT_1002d840 = 0;
  return;
}
#undef iStack_c
#undef puStack_18
#undef puStack_4
#undef uStack_10
#undef uStack_14
#undef uStack_1c
#undef uStack_20
#undef uStack_8

#endif


/* ---- 0x10003ac0  FdInitialize ---- */
/* Original name FdInitialize (the remaster's GrimFandango (Linux): aligned call in ImInitialize);
   was Im_DSoundReset. */

undefined4 FdInitialize(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &g_dwFades;
  for (iVar1 = 0xa0; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  g_dwFadesOn = 0;
  return 0;
}

/* ---- 0x10003ae0  FdSave ---- */
/* Original name FdSave (the remaster's GrimFandango (Linux): aligned call in ImSave); was
   Im_DSoundSave. */

undefined4 __cdecl FdSave(undefined4 *buf,uint size)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (size < 0x280) {
    return 0xfffffffb;
  }
  puVar2 = &g_dwFades;
  for (iVar1 = 0xa0; iVar1 != 0; iVar1 = iVar1 + -1) {
    *buf = *puVar2;
    puVar2 = puVar2 + 1;
    buf = buf + 1;
  }
  return 0x280;
}

/* ---- 0x10003b10  FdRestore ---- */
/* Original name FdRestore (the remaster's GrimFandango (Linux): aligned call in ImRestore); was
   Im_DSoundRestore. */

undefined4 __cdecl FdRestore(undefined4 *buf)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &g_dwFades;
  for (iVar1 = 0xa0; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *buf;
    buf = buf + 1;
    puVar2 = puVar2 + 1;
  }
  g_dwFadesOn = 1;
  return 0x280;
}

/* ---- 0x10003b40  FdFadeParam ---- */
/* Body of ImFadeParam: allocates a fade slot for (sound, param, target, duration) Original name
   FdFadeParam (the remaster's GrimFandango (Linux): case 0xe of ImSoundCall calls it where the
   v1.01 dispatcher calls the exported API that calls this function); was Im_FadeParamImpl. */

undefined4 __cdecl FdFadeParam(int sound,int param,uint value,int time)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  
  piVar4 = &g_dwFades;
  if (((sound == 0) || (time < 0)) ||
     ((param != 0x500 && (((param != 0x600 && (param != 0x700)) && (param != 0x800)))))) {
    return 0xfffffffb;
  }
  iVar1 = (time * 5) / 6;
  FdStopFade(sound,param);
  if (iVar1 != 0) {
    iVar2 = 0;
    do {
      if (*piVar4 == 0) {
        piVar4[1] = sound;
        piVar4[2] = param;
        uVar3 = ImGetParam(sound,param);
        piVar4[3] = uVar3;
        iVar2 = value - uVar3;
        piVar4[5] = iVar1;
        piVar4[4] = iVar1;
        piVar4[9] = ((-1 < iVar2) - 1 & 0xfffffffe) + 1;
        piVar4[6] = iVar2 / iVar1;
        if (iVar2 < 0) {
          iVar2 = -iVar2;
        }
        piVar4[8] = 0;
        *piVar4 = 1;
        g_dwFadesOn = 1;
        piVar4[7] = iVar2 % iVar1;
        return 0;
      }
      iVar2 = iVar2 + 1;
      piVar4 = piVar4 + 10;
    } while (iVar2 < 0x10);
    return 0xfffffffa;
  }
  if ((param == 0x600) && (value == 0)) {
    ImStopSound(sound);
    return 0;
  }
  ImSetParam(sound,param,value);
  return 0;
}

/* ---- 0x10003c70  FdStopFade ---- */
/* Original name FdStopFade (the remaster's GrimFandango (Linux): aligned call in DpSwitchStream,
   FdFadeParam, TrStopTrack); was Im_FadesClearSound. */

void __cdecl FdStopFade(int sound,int param)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = &g_dwFades;
  iVar2 = 0x10;
  do {
    if (((*piVar1 != 0) && (piVar1[1] == sound)) && ((piVar1[2] == param || (param == -1)))) {
      *piVar1 = 0;
    }
    piVar1 = piVar1 + 10;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}

/* ---- 0x10003cb0  FdIntHandler ---- */
/* Steps every active fade and applies the parameter Original name FdIntHandler (the remaster's
   GrimFandango (Linux): aligned call in ImHeartbeat); was Im_FadesHeartbeat. */

uint FdIntHandler(void)

{
  uint uVar1;
  uint value;
  uint uVar2;
  uint *puVar3;
  int iVar4;
  
  uVar1 = g_dwFadesOn;
  if (g_dwFadesOn != 0) {
    g_dwFadesOn = 0;
    puVar3 = &DAT_1002d880;
    iVar4 = 0x10;
    do {
      if (puVar3[-8] != 0) {
        uVar1 = puVar3[-4];
        g_dwFadesOn = 1;
        puVar3[-4] = uVar1 - 1;
        if (uVar1 - 1 == 0) {
          puVar3[-8] = 0;
        }
        value = puVar3[-2] + puVar3[-5];
        uVar2 = *puVar3 + puVar3[-1];
        *puVar3 = uVar2;
        uVar1 = uVar2;
        if (puVar3[-3] <= uVar2) {
          uVar1 = puVar3[1];
          *puVar3 = uVar2 - puVar3[-3];
          value = value + uVar1;
        }
        if (value != puVar3[-5]) {
          uVar1 = (int)puVar3[-4] / 5;
          puVar3[-5] = value;
          if ((int)puVar3[-4] % 5 == 0) {
            if ((puVar3[-6] == 0x600) && (value == 0)) {
              uVar1 = ImStopSound(puVar3[-7]);
            }
            else {
              uVar1 = ImSetParam(puVar3[-7],puVar3[-6],value);
            }
          }
        }
      }
      puVar3 = puVar3 + 10;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  return uVar1;
}

/* ---- 0x10004820  Im_ApplyFXPreset ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* HMI SOS FX preset processing on a mixed block */

undefined4 __cdecl
Im_ApplyFXPreset(undefined2 *src,uint frames,undefined2 *dst,int *outBuf,int *outSize,int stereo)

{
  undefined2 uVar1;
  int iVar2;
  uint uVar3;
  
  if (DAT_1002dd74 == 0) {
    if (stereo != 0) {
      iVar2 = hmiFXMalloc(frames * DAT_1002dd62);
      *outBuf = iVar2;
      if (iVar2 == 0) {
        return DAT_1002dd7c;
      }
      *outSize = frames * DAT_1002dd62;
      dst = (undefined2 *)*outBuf;
    }
    if (dst != (undefined2 *)0x0) {
      uVar3 = frames >> 1;
      if (DAT_1002dd62 == 2) {
        if (uVar3 != 0) {
          do {
            *dst = *src;
            dst[1] = *src;
            dst = dst + 2;
            uVar3 = uVar3 - 1;
            src = src + 1;
          } while (uVar3 != 0);
          return DAT_1002dd7c;
        }
      }
      else if (uVar3 != 0) {
        do {
          uVar1 = *src;
          src = src + 1;
          *dst = uVar1;
          dst = dst + 1;
          uVar3 = uVar3 - 1;
        } while (uVar3 != 0);
        return DAT_1002dd7c;
      }
    }
  }
  else {
    _DAT_1002dd08 = 0x19;
    if (stereo != 0) {
      _DAT_1002dd08 = 0x9d;
    }
    _DAT_1002dd0c = DAT_1002dd74;
    _DAT_1002dd24 = &DAT_1002dd30;
    _DAT_1002dd28 = &DAT_1002dd60;
    _DAT_1002dd1c = src;
    UINT_1002dd20 = frames;
    if (stereo == 0) {
      DAT_1002dd14 = dst;
    }
    hmiFXPresetProcess(DAT_1002dd2c,&DAT_1002dd08);
    if (stereo != 0) {
      *outBuf = (int)DAT_1002dd14;
      *outSize = DAT_1002dd18;
    }
  }
  return DAT_1002dd7c;
}

/* ---- 0x10004970  ImFx_Terminate ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Stops the HMI voice-effects library: releases the preset, frees the preset library and calls
   hmiFXUnInitSystem (when ImFx_Initialize ran); was FUN_10004970. */

void __cdecl ImFx_Terminate(void)

{
  if (_DAT_1002dd78 != 0) {
    _DAT_1002dd78 = 0;
    if (DAT_1002dd74 != 0) {
      hmiFXPresetRelease(DAT_1002dd74);
    }
    if (DAT_1002dd2c != 0) {
      hmiFXPresetFreeLibrary(DAT_1002dd2c);
    }
    hmiFXUnInitSystem(((unsigned)(uintptr_t)&DAT_1002dd48));
  }
  return;
}

/* ---- 0x100049b0  GrInitialize ---- */
/* Original name GrInitialize (the remaster's GrimFandango (Linux): aligned call in ImInitialize);
   was Im_GroupsInit. */

undefined4 GrInitialize(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &g_dwGroupEffVols;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0x7f;
    puVar2 = puVar2 + 1;
  }
  puVar2 = &g_dwGroupVols;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0x7f;
    puVar2 = puVar2 + 1;
  }
  return 0;
}

/* ---- 0x100049e0  GrSetGroupVol ---- */
/* Original name GrSetGroupVol (the remaster's GrimFandango (Linux): aligned call in ImHeartbeat,
   ImSetGroupVol); was Im_SetGroupVolImpl. */

undefined4 __cdecl GrSetGroupVol(uint group,uint vol)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  if (0xf < group) {
    return 0xfffffffb;
  }
  if (vol == 0xffffffff) {
    return (&g_dwGroupVols)[group];
  }
  if (0x7f < vol) {
    return 0xfffffffb;
  }
  uVar1 = (&g_dwGroupVols)[group];
  if (group == 0) {
    g_dwGroupVols = vol;
    g_dwGroupEffVols = vol;
    iVar2 = 0;
    do {
      iVar3 = iVar2 + 4;
      *(int *)((int)&DAT_1002ddc4 + iVar2) =
           (int)((*(int *)((int)&DAT_1002dd84 + iVar2) + 1) * vol) >> 7;
      iVar2 = iVar3;
    } while (iVar3 < 0x3c);
    ImWaveHalt();
    TrUpdateVols();
    ImWaveProceed();
    return uVar1;
  }
  (&g_dwGroupVols)[group] = vol;
  (&g_dwGroupEffVols)[group] = (int)((vol + 1) * g_dwGroupVols) >> 7;
  ImWaveHalt();
  TrUpdateVols();
  ImWaveProceed();
  return uVar1;
}

/* ---- 0x10004a80  GrGetGroupEffVol ---- */
/* Original name GrGetGroupEffVol (the remaster's GrimFandango (Linux): aligned call in TrSetParam,
   TrStartSound, TrUpdateVols); was Im_GetGroupVol. */

undefined4 __cdecl GrGetGroupEffVol(uint group)

{
  if (0xf < group) {
    return 0xfffffffb;
  }
  return (&g_dwGroupEffVols)[group];
}

/* ---- 0x10004f50  ImWaveHalt ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Guard enter: INC [g_dwWvSlicingHalted], NOT atomic (no LOCK) and NOT a lock: it does not exclude
   any thread, ImHeartbeat only skips itself while it is nonzero. Called at the start of most Im*
   entry points. Original name ImWaveHalt (the remaster's GrimFandango (Linux): aligned call in
   ImGetParam, ImStartStream, ImStopAllSounds); was Im_GuardEnter. */

void ImWaveHalt(void)

{
  g_dwWvSlicingHalted = g_dwWvSlicingHalted + 1;
  return;
}
#endif


/* ---- 0x10004f60  ImWaveProceed ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Guard leave: load, if nonzero decrement, store (three separate steps, not atomic). Two threads
   leaving at the same moment both read 2 and both store 1: the counter stays 1 for good (a lost
   update), and ImHeartbeat (which only runs at 0) never runs again: every track freezes and every
   wait for a sound spins forever. Seen on the original with the heartbeat (WINMM timer thread) and
   ImGetParam of the main thread 171 us apart. Original name ImWaveProceed (the remaster's
   GrimFandango (Linux): aligned call in ImGetParam, ImStartStream, ImStopAllSounds); was
   Im_GuardLeave. */

int ImWaveProceed(void)

{
  if (g_dwWvSlicingHalted != 0) {
    g_dwWvSlicingHalted = g_dwWvSlicingHalted + -1;
  }
  return g_dwWvSlicingHalted;
}
#endif


/* ---- 0x10004f70  ImSoundCall ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Single-entry command dispatcher: switches on the command id and calls the Im* API Original name
   ImSoundCall (the remaster's GrimFandango (Linux): the command switch: the same case numbers
   0..0x1d call the same API (ImSoundCall calls the Tr, Fd and Tg handlers, the API inlined)); was
   Im_DispatchCommand. */

uint __cdecl
ImSoundCall(uint cmd,int a2,int a3,int a4,int a5,int a6,int a7,int a8,int a9,int a10,int a11)

{
  uint uVar1;
  int in_stack_0000003c;
  
  if (g_dwIm_initialized != 0) {
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


/* ---- 0x10005360  MxInitialize ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* iMUSE_Mixer.c Original name MxInitialize (the remaster's GrimFandango (Linux): called by
   TrInitialize (paired) at the same place); was Im_MixerInit. */

undefined4 __cdecl MxInitialize(undefined4 *info)

{
  undefined2 *puVar1;
  int iVar2;
  undefined1 *puVar3;
  longlong lVar4;
  int local_4;
  
  iVar2 = 0;
  puVar3 = &g_bPanTable;
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
  g_dwOutChannelCount = *info;
  g_dwMixBufSize = info[2] << 1;
  g_pMixBuf = (int *)(**(code **)(g_dwSounds_pHS + 0x20))
                               (info[2] << 1,s_C__grimsrc_libs_iMUSE_Mixer_c_100172c8,0x7a);
  _DAT_1002df28 = info[3];
  puVar1 = (undefined2 *)
           (**(code **)(g_dwSounds_pHS + 0x20))
                     (g_dwImWaveMixCount << 0x10,s_C__grimsrc_libs_iMUSE_Mixer_c_100172c8,0x7f);
  g_dwSoftLTable = puVar1;
  if (puVar1 == (undefined2 *)0x0) {
    return 0xffffffff;
  }
  iVar2 = 0;
  if (0 < g_dwImWaveMixCount << 0xf) {
    do {
      lVar4 = hmi__bae0();
      *puVar1 = (short)lVar4;
      puVar1 = puVar1 + 1;
      iVar2 = iVar2 + 1;
    } while (iVar2 < g_dwImWaveMixCount * 0x8000);
  }
  return 0;
}
#endif


/* ---- 0x10005490  MxTerminate ---- */
/* Original name MxTerminate (the remaster's GrimFandango (Linux): called by TrTerminate at the same
   place, body similarity); was Im_MixerReset. */

undefined4 MxTerminate(void)

{
  (**(code **)(g_dwSounds_pHS + 0x24))(g_dwSoftLTable);
  (**(code **)(g_dwSounds_pHS + 0x24))(g_pMixBuf);
  return 0;
}

/* ---- 0x100054c0  MxBeginMix ---- */
/* Original name MxBeginMix (the remaster's GrimFandango (Linux): aligned call in TrIntHandler); was
   Im_MixerHeartbeat. */

undefined4 MxBeginMix(void)

{
  uint uVar1;
  uint uVar2;
  int *piVar3;
  
  uVar2 = g_dwMixBufSize;
  piVar3 = g_pMixBuf;
  for (uVar1 = g_dwMixBufSize >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
    *piVar3 = 0;
    piVar3 = piVar3 + 1;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *(undefined1 *)piVar3 = 0;
    piVar3 = (int *)((int)piVar3 + 1);
  }
  return 0;
}

/* ---- 0x100054f0  Mixer_MxMix ---- */
/* Dispatches to the four mix loops by channel count and volume mode Original name MxMix, written
   Mixer_MxMix (the mixer module; the bridge refuses the bare name) (the remaster's GrimFandango
   (Linux): aligned call in DpProcessTrack); was Im_MixSamples. */

void __cdecl
Mixer_MxMix(short *src,int frames,int bits,int channels,int compressed,uint rate,uint outPos,int vol
           ,int pan)

{
  uint uVar1;
  int iVar2;
  
  if ((((g_pMixBuf != (int *)0x0) && (src != (short *)0x0)) && (frames != 0)) &&
     ((bits == 0x10 && (0 < vol)))) {
    if ((channels == 1) && (g_dwOutChannelCount == 2)) {
      uVar1 = vol >> 3;
      if (vol != 0) {
        uVar1 = uVar1 + 1;
      }
      if (0x10 < uVar1) {
        uVar1 = 0x10;
      }
      iVar2 = (pan >> 3) + -8;
      if (0x40 < pan) {
        iVar2 = (pan >> 3) + -7;
      }
      if (compressed != 0) {
        Im_MixLoopC(src,frames,rate,outPos,(uint)(byte)(&DAT_10033568)[uVar1 * 0x11 - iVar2],
                    (uint)(byte)(&DAT_10033568)[uVar1 * 0x11 + iVar2]);
        return;
      }
      Im_MixLoopA(src,frames,rate,outPos,(uint)(byte)(&DAT_10033568)[uVar1 * 0x11 - iVar2],
                  (uint)(byte)(&DAT_10033568)[uVar1 * 0x11 + iVar2]);
      return;
    }
    if (compressed != 0) {
      Im_MixLoopD(src,frames,rate,outPos,vol + 1);
      return;
    }
    Im_MixLoopB(src,frames,rate,outPos,vol + 1);
  }
  return;
}

/* ---- 0x10005610  MxEndMix ---- */
/* Reads and decodes the next block of a sound through the file layer Original name MxEndMix (the
   remaster's GrimFandango (Linux): converts the mix buffer to 16-bit output through the soft
   limiter table (mixBuf, outChannelCount, softLTable) and feeds the recorder (recordState), as the
   remaster's MxEndMix); was Im_ReadSoundData. */

undefined4 __cdecl MxEndMix(int *trIntHandler_outPtr,int trIntHandler_outFramesNeeded)

{
  int *piVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  
  if (((g_pMixBuf != (int *)0x0) && (trIntHandler_outPtr != (int *)0x0)) &&
     (trIntHandler_outFramesNeeded != 0)) {
    piVar5 = trIntHandler_outPtr;
    iVar3 = trIntHandler_outFramesNeeded;
    piVar1 = g_pMixBuf;
    if (g_dwOutChannelCount == 2) {
      iVar3 = trIntHandler_outFramesNeeded << 1;
    }
    for (; iVar3 != 0; iVar3 = iVar3 + -1) {
      iVar4 = *piVar1 >> 7;
      if (iVar4 < 0) {
        sVar2 = -*(short *)(g_dwSoftLTable - (iVar4 * 2 + 2));
      }
      else {
        sVar2 = *(short *)(g_dwSoftLTable + iVar4 * 2);
      }
      *(short *)piVar5 = sVar2;
      piVar5 = (int *)((int)piVar5 + 2);
      piVar1 = piVar1 + 1;
    }
    if (g_dwRecordState != 0) {
      piVar5 = trIntHandler_outPtr;
      iVar3 = trIntHandler_outFramesNeeded;
      if (g_dwRecordState == 1) {
        while( true ) {
          iVar3 = iVar3 + -1;
          if (*piVar5 != 0) break;
          piVar5 = piVar5 + 1;
          if (iVar3 == 0) {
            return 0;
          }
        }
        g_dwRecordState = 2;
      }
      else if (g_dwRecordState != 2) {
        if (g_dwRecordState != 3) {
          return 0;
        }
        while( true ) {
          iVar3 = iVar3 + -1;
          if (*piVar5 != 0) break;
          piVar5 = piVar5 + 1;
          if (iVar3 == 0) {
            if (g_dwRecordFile != (int *)0x0) {
              ImFile_Read(g_dwRecordFile,0,0);
              AudioLib_CreateWaveFileHeader
                        ((undefined4 *)&g_aMxEndMix_wavHeader,5,0x5622,0x10,2,g_dwDataSizeInBytes);
              ImFile_Open(&g_aMxEndMix_wavHeader,0x2c,1,g_dwRecordFile);
              ImFile_Close(g_dwRecordFile);
              g_dwRecordFile = (int *)0x0;
            }
            g_dwRecordState = 0;
            return 0;
          }
        }
      }
      if (g_dwRecordFile != (int *)0x0) {
        ImFile_Open((char *)trIntHandler_outPtr,trIntHandler_outFramesNeeded * 4,1,g_dwRecordFile);
      }
      g_dwDataSizeInBytes = g_dwDataSizeInBytes + trIntHandler_outFramesNeeded * 4;
    }
    return 0;
  }
  return 0xffffffff;
}

/* ---- 0x100057a0  Im_MixLoopA ---- */
/* Mix loop variant (16-bit source); exact channel layout not verified */

void __cdecl Im_MixLoopA(short *src,int frames,uint rate,uint outPos,int volL,int volR)

{
  short sVar1;
  uint uVar2;
  int *piVar3;
  uint uVar4;
  uint uVar5;
  
  piVar3 = g_pMixBuf + outPos * 2;
  uVar2 = (uint)(frames << 0x10) / rate;
  if (uVar2 == 0x8000) {
    while (frames = frames + -1, frames != 0) {
      *piVar3 = *piVar3 + volL * *src;
      piVar3[1] = piVar3[1] + volR * *src;
      piVar3[2] = piVar3[2] + ((int)*src + (int)src[2] >> 1) * volL;
      piVar3[3] = piVar3[3] + ((int)*src + (int)src[2] >> 1) * volR;
      piVar3 = piVar3 + 4;
      src = src + 1;
    }
    *piVar3 = *piVar3 + volL * *src;
    piVar3[1] = piVar3[1] + volR * *src;
    piVar3[2] = piVar3[2] + volL * *src;
    piVar3[3] = piVar3[3] + volR * *src;
  }
  else if (uVar2 == 0x10000) {
    if (rate != 0) {
      do {
        *piVar3 = *piVar3 + volL * *src;
        rate = rate - 1;
        piVar3[1] = piVar3[1] + volR * *src;
        src = src + 1;
        piVar3 = piVar3 + 2;
      } while (rate != 0);
      return;
    }
  }
  else if (uVar2 == 0x20000) {
    if (rate != 0) {
      do {
        *piVar3 = *piVar3 + volL * *src;
        sVar1 = *src;
        src = src + 2;
        rate = rate - 1;
        piVar3[1] = piVar3[1] + volR * sVar1;
        piVar3 = piVar3 + 2;
      } while (rate != 0);
      return;
    }
  }
  else {
    uVar4 = 0;
    if (rate != 0) {
      outPos = rate;
      do {
        uVar5 = uVar4 + uVar2;
        *piVar3 = *piVar3 + volL * *src;
        piVar3[1] = piVar3[1] + volR * *src;
        uVar4 = uVar5 & 0xffff;
        src = src + ((int)uVar5 >> 0x10);
        outPos = outPos - 1;
        piVar3 = piVar3 + 2;
      } while (outPos != 0);
      return;
    }
  }
  return;
}

/* ---- 0x100059a0  Im_MixLoopB ---- */
/* Unidentified function of iMUSE_Mixer.c (software mixing / resampling) */

void __cdecl Im_MixLoopB(short *src,int frames,uint rate,uint outPos,int vol)

{
  short sVar1;
  uint uVar2;
  short *psVar3;
  int *piVar4;
  uint uVar5;
  int iVar6;
  
  piVar4 = g_pMixBuf + outPos * 2;
  uVar2 = (uint)(frames << 0x10) / rate;
  if (uVar2 == 0x8000) {
    while (frames = frames + -1, frames != 0) {
      *piVar4 = *piVar4 + vol * *src;
      piVar4[1] = piVar4[1] + vol * src[1];
      piVar4[2] = piVar4[2] + ((int)src[2] + (int)*src >> 1) * vol;
      piVar4[3] = piVar4[3] + ((int)src[3] + (int)src[1] >> 1) * vol;
      piVar4 = piVar4 + 4;
      src = src + 2;
    }
    *piVar4 = *piVar4 + vol * *src;
    piVar4[1] = piVar4[1] + vol * src[1];
    piVar4[2] = piVar4[2] + vol * *src;
    piVar4[3] = piVar4[3] + vol * src[1];
  }
  else if (uVar2 == 0x10000) {
    iVar6 = rate * 2;
    if (iVar6 != 0) {
      do {
        sVar1 = *src;
        src = src + 1;
        iVar6 = iVar6 + -1;
        *piVar4 = *piVar4 + vol * sVar1;
        piVar4 = piVar4 + 1;
      } while (iVar6 != 0);
      return;
    }
  }
  else if (uVar2 == 0x20000) {
    if (rate != 0) {
      do {
        psVar3 = src + 1;
        *piVar4 = *piVar4 + vol * *src;
        src = src + 4;
        rate = rate - 1;
        piVar4[1] = piVar4[1] + vol * *psVar3;
        piVar4 = piVar4 + 2;
      } while (rate != 0);
      return;
    }
  }
  else {
    uVar5 = 0;
    if (rate != 0) {
      outPos = rate;
      do {
        uVar5 = uVar5 + uVar2 * 2;
        *piVar4 = *piVar4 + vol * *src;
        piVar4[1] = piVar4[1] + src[1] * vol;
        piVar4 = piVar4 + 2;
        src = src + ((int)uVar5 >> 0x10);
        uVar5 = uVar5 & 0xffff;
        outPos = outPos - 1;
      } while (outPos != 0);
      return;
    }
  }
  return;
}

/* ---- 0x10005b80  Im_MixLoopC ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Unidentified function of iMUSE_Mixer.c (software mixing / resampling) */

void __cdecl Im_MixLoopC(undefined2 *src,int frames,uint count,int out,int wl,int wr)

{
  undefined2 uVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  
  piVar4 = g_pMixBuf + out * 2;
  uVar2 = (uint)(frames << 0x10) / count;
  if (uVar2 == 0x8000) {
    while (frames = frames + -1, frames != 0) {
      uVar1 = src[2];
      iVar5 = (int)CONCAT11((char)*src,(char)((ushort)*src >> 8));
      *piVar4 = *piVar4 + wl * iVar5;
      src = src + 1;
      iVar3 = (int)(short)(CONCAT11((char)uVar1,(char)((ushort)uVar1 >> 8)) + iVar5 >> 1);
      piVar4[1] = piVar4[1] + wr * iVar5;
      piVar4[2] = piVar4[2] + wl * iVar3;
      piVar4[3] = piVar4[3] + wr * iVar3;
      piVar4 = piVar4 + 4;
    }
    iVar5 = (int)CONCAT11((char)*src,(char)((ushort)*src >> 8));
    iVar3 = wl * iVar5;
    iVar5 = wr * iVar5;
    *piVar4 = *piVar4 + iVar3;
    piVar4[1] = piVar4[1] + iVar5;
    piVar4[2] = piVar4[2] + iVar3;
    piVar4[3] = piVar4[3] + iVar5;
  }
  else if (uVar2 == 0x10000) {
    if (count != 0) {
      do {
        iVar3 = (int)CONCAT11((char)*src,(char)((ushort)*src >> 8));
        *piVar4 = *piVar4 + wl * iVar3;
        src = src + 1;
        piVar4[1] = piVar4[1] + wr * iVar3;
        count = count - 1;
        piVar4 = piVar4 + 2;
      } while (count != 0);
      return;
    }
  }
  else if (uVar2 == 0x20000) {
    if (count != 0) {
      do {
        iVar3 = (int)CONCAT11((char)*src,(char)((ushort)*src >> 8));
        *piVar4 = *piVar4 + wl * iVar3;
        src = src + 2;
        piVar4[1] = piVar4[1] + wr * iVar3;
        count = count - 1;
        piVar4 = piVar4 + 2;
      } while (count != 0);
      return;
    }
  }
  else {
    uVar6 = 0;
    if (count != 0) {
      do {
        iVar3 = (int)CONCAT11((char)*src,(char)((ushort)*src >> 8));
        *piVar4 = *piVar4 + wl * iVar3;
        uVar7 = uVar6 + uVar2;
        piVar4[1] = piVar4[1] + wr * iVar3;
        piVar4 = piVar4 + 2;
        uVar6 = uVar7 & 0xffff;
        src = src + ((int)uVar7 >> 0x10);
        count = count - 1;
      } while (count != 0);
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

void __cdecl Im_MixLoopD(undefined2 *src,int frames,uint count,uint out,int vol)

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
  
  piVar4 = g_pMixBuf + out * 2;
  uVar3 = (uint)(frames << 0x10) / count;
  if (uVar3 == 0x8000) {
    while (frames = frames + -1, frames != 0) {
      uVar1 = src[2];
      iVar7 = (int)CONCAT11((char)*src,(char)((ushort)*src >> 8));
      uVar2 = src[3];
      iVar5 = (int)CONCAT11((char)src[1],(char)((ushort)src[1] >> 8));
      src = src + 2;
      *piVar4 = *piVar4 + vol * iVar7;
      piVar4[1] = piVar4[1] + vol * iVar5;
      piVar4[2] = piVar4[2] +
                  (short)(CONCAT11((char)uVar1,(char)((ushort)uVar1 >> 8)) + iVar7 >> 1) * vol;
      piVar4[3] = piVar4[3] +
                  (short)(CONCAT11((char)uVar2,(char)((ushort)uVar2 >> 8)) + iVar5 >> 1) * vol;
      piVar4 = piVar4 + 4;
    }
    iVar5 = CONCAT11((char)*src,(char)((ushort)*src >> 8)) * vol;
    iVar7 = CONCAT11((char)src[1],(char)((ushort)src[1] >> 8)) * vol;
    *piVar4 = *piVar4 + iVar5;
    piVar4[1] = piVar4[1] + iVar7;
    piVar4[2] = piVar4[2] + iVar5;
    piVar4[3] = piVar4[3] + iVar7;
  }
  else if (uVar3 == 0x10000) {
    iVar7 = count * 2;
    if (iVar7 != 0) {
      do {
        uVar1 = *src;
        src = src + 1;
        *piVar4 = *piVar4 + CONCAT11((char)uVar1,(char)((ushort)uVar1 >> 8)) * vol;
        iVar7 = iVar7 + -1;
        piVar4 = piVar4 + 1;
      } while (iVar7 != 0);
      return;
    }
  }
  else if (uVar3 == 0x20000) {
    if (count != 0) {
      do {
        puVar6 = src + 1;
        *piVar4 = *piVar4 + CONCAT11((char)*src,(char)((ushort)*src >> 8)) * vol;
        src = src + 4;
        piVar4[1] = piVar4[1] + CONCAT11((char)*puVar6,(char)((ushort)*puVar6 >> 8)) * vol;
        count = count - 1;
        piVar4 = piVar4 + 2;
      } while (count != 0);
      return;
    }
  }
  else {
    uVar8 = 0;
    if (count != 0) {
      out = count;
      do {
        uVar1 = src[1];
        *piVar4 = *piVar4 + vol * CONCAT11((char)*src,(char)((ushort)*src >> 8));
        uVar9 = uVar8 + uVar3 * 2;
        piVar4[1] = piVar4[1] + vol * CONCAT11((char)uVar1,(char)((ushort)uVar1 >> 8));
        uVar8 = uVar9 & 0xffff;
        src = src + ((int)uVar9 >> 0x10);
        out = out - 1;
        piVar4 = piVar4 + 2;
      } while (out != 0);
      return;
    }
  }
  return;
}
#endif


/* ---- 0x10006070  ScriptCall ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Original name ScriptCall (the remaster's GrimFandango (Linux): strings: 'ERROR:unrecognized
   opcode in script...' | 'ERROR:script not initialized...' | 'ERROR:script already
   initialized...'); was FUN_10006070. */

undefined4 __cdecl ScriptCall(int cmd,...)

{
  unsigned char _frame[0x40];  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *puVar1;
  undefined4 uVar2;
  char **ppcVar3;
  int iVar4;
  #define local_28 (*(char *(*)[2])(_frame + (0x40 - 0x28)))
  #define uStack_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define uStack_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define uStack_18 (*(uint *)(_frame + (0x40 - 0x18)))
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
    ImPrintf(s_ERROR_script_not_initialized____1001e6d8);
    return 0xffffffff;
  }
  switch(cmd) {
  case 0:
    break;
  case 1:
    _DAT_1002e330 = 0;
    uVar2 = Script_Terminate();
    return uVar2;
  case 2:
    iVar4 = Script_Save((undefined4 *)local_28[0],(int)local_28[1]);
    return iVar4;
  case 3:
    iVar4 = Script_Restore((undefined4 *)local_28[0]);
    return iVar4;
  case 4:
    uVar2 = Script_Update();
    return uVar2;
  case 5:
    uVar2 = Script_SetState((int)local_28[0]);
    return uVar2;
  case 6:
    uVar2 = Script_SetSequence((int)local_28[0]);
    return uVar2;
  case 7:
    uVar2 = Script_NullCallback();
    return uVar2;
  case 8:
    uVar2 = Script_Attribute((uint)local_28[0],local_28[1]);
    return uVar2;
  default:
    ImPrintf(s_ERROR_unrecognized_opcode_in_scr_1001e68c);
    return 0xffffffff;
  }
  if (_DAT_1002e330 != 0) {
    ImPrintf(s_ERROR_script_already_initialized_1001e6b4);
    return 0xffffffff;
  }
  _DAT_1002e330 = 1;
  uVar2 = Script_Init((int)local_28[0],(uint)local_28[1],uStack_20,uStack_1c,uStack_18,uStack_14,
                      uStack_10,uStack_c);
  return uVar2;
}
#undef local_28
#undef uStack_10
#undef uStack_14
#undef uStack_18
#undef uStack_1c
#undef uStack_20
#undef uStack_c


/* ---- 0x10006360  Script_Init ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Initialises the music script: installs Script_Callback as the trigger callback, takes the
   local-music flag, sets up the file list (ImInitFilelist) and the two host callbacks, clears the
   0xe4 attributes and the current state / sequence / cue point; was FUN_10006360. */

undefined4 __cdecl
Script_Init(int callbacks,uint loadSound,uint unloadSound,uint openSound,uint closeSound,
           undefined4 hostCallback1,undefined4 hostCallback2,undefined4 localMusic)

{
  int iVar1;
  undefined4 *puVar2;
  
  *(code **)(callbacks + 8) = Script_Callback;
  g_dwLocalMusic = localMusic;
  ImInitFilelist(loadSound,unloadSound,openSound,closeSound);
  _DAT_1002df68 = hostCallback1;
  _DAT_1002df6c = hostCallback2;
  puVar2 = &DAT_1002df78;
  for (iVar1 = 0xe4; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  g_dwCurrentState = 0;
  g_dwCurrentSequence = 0;
  g_dwCurrentCuePoint = 0;
  return 0;
}

/* ---- 0x100063d0  Script_Terminate ---- */
/* Ends the music script: stops the local music (Script_StopLocalMusic) and clears the state, the
   attributes, the sequence and the cue point; was FUN_100063d0. */

undefined4 Script_Terminate(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  Script_StopLocalMusic();
  g_dwCurrentState = 0;
  puVar2 = &DAT_1002df78;
  for (iVar1 = 0xe4; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  g_dwCurrentSequence = 0;
  g_dwCurrentCuePoint = 0;
  return 0;
}

/* ---- 0x10006400  Script_Save ---- */
/* Saves the music script state into `buf` (at least 0x39c bytes): state, sequence, cue point, the
   attributes, then the file list (ImSaveFilelist). Returns the bytes written or -1; was
   FUN_10006400. */

int __cdecl Script_Save(undefined4 *buf,int size)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  
  if (size < 0x39c) {
    ImPrintf(s_SCRIPT_ERR__save_buffer_too_smal_1001e6f8);
    return -1;
  }
  iVar4 = 0xc;
  *buf = g_dwCurrentState;
  buf[1] = g_dwCurrentSequence;
  buf[2] = g_dwCurrentCuePoint;
  puVar2 = &DAT_1002df78;
  do {
    uVar1 = *puVar2;
    puVar2 = puVar2 + 1;
    *(undefined4 *)(iVar4 + (int)buf) = uVar1;
    iVar4 = iVar4 + 4;
  } while ((int)puVar2 < ((unsigned)(uintptr_t)&g_dwCurrentSequence));
  iVar3 = ImSaveFilelist((int *)((int)buf + iVar4),size - iVar4);
  if (-1 < iVar3) {
    iVar3 = iVar3 + iVar4;
  }
  return iVar3;
}

/* ---- 0x10006470  Script_Restore ---- */
/* Restores what Script_Save wrote: unloads and closes everything, reads state, sequence, cue point
   and the attributes, then the file list (ImRestoreFilelist). Returns the bytes read; was
   FUN_10006470. */

int __cdecl Script_Restore(undefined4 *buf)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  
  ImUnloadAll();
  ImCloseAll();
  iVar4 = 0xc;
  g_dwCurrentState = *buf;
  g_dwCurrentSequence = buf[1];
  g_dwCurrentCuePoint = buf[2];
  puVar2 = &DAT_1002df78;
  do {
    puVar1 = (undefined4 *)(iVar4 + (int)buf);
    iVar4 = iVar4 + 4;
    *puVar2 = *puVar1;
    puVar2 = puVar2 + 1;
  } while ((int)puVar2 < ((unsigned)(uintptr_t)&g_dwCurrentSequence));
  iVar3 = ImRestoreFilelist((int *)(iVar4 + (int)buf));
  return iVar4 + iVar3;
}

/* ---- 0x100064d0  Script_Update ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Dispatcher command 4, once per frame: ends a sequence the trigger callback flagged as ended, and
   the current sequence when no music stream is playing; then ImFlushSounds. Hand-written in
   build/overrides_imuse_r1.c (Script_SetSequence takes a register argument); was FUN_100064d0. */

undefined4 Script_Update(void)

{
  uint sound;
  uint uVar1;
  
  if (DAT_1002e304 != 0) {
    Script_SetSequence(0);
    DAT_1002e304 = 0;
  }
  sound = ImGetNextSound(0);
  if (sound != 0) {
    do {
      uVar1 = ImGetParam(sound,0x1800);
      if (uVar1 != 0) {
        uVar1 = ImGetParam(sound,0x1900);
        if (uVar1 == 2) break;
      }
      sound = ImGetNextSound(sound);
    } while (sound != 0);
    if (sound != 0) goto LAB_10006549;
  }
  if (g_dwCurrentSequence != 0) {
    Script_SetSequence(0);
  }
LAB_10006549:
  ImFlushSounds();
  return 0;
}
#endif


/* ---- 0x10006560  Script_SetState ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Sets the music state by id (-1: only returns it): finds the state record, and unless it is
   current or a sequence plays, transitions to its file (Script_Trans). Returns the current state's
   id. Hand-written in build/overrides_imuse_r1.c; was FUN_10006560. */

int __cdecl Script_SetState(int id)

{
  uint uVar1;
  int *piVar2;
  ImMusicEntry *file;
  int unaff_ESI;
  uint state;
  uint unaff_EDI;
  uint unaff_retaddr;
  uint in_stack_00000008;
  
  if (id == -1) {
    return g_aImStateTable[g_dwCurrentState].nId;
  }
  state = 0;
  piVar2 = &g_aImStateTable[0].nId;
  do {
    if (id == *piVar2) {
      ImPrintf(g_aImStateTable[state].aName);
      ImPrintf(s_____100171b0);
      uVar1 = g_dwCurrentState;
      if ((state != g_dwCurrentState) && (uVar1 = state, g_dwCurrentSequence == 0)) {
        if (state == 0) {
          file = (ImMusicEntry *)0x0;
        }
        else {
          file = g_aImStateTable + state;
        }
        ((code *)Script_Trans)(file->aFilename,state,0,unaff_EDI,unaff_ESI,unaff_retaddr,id,in_stack_00000008)
        ;
      }
      g_dwCurrentState = uVar1;
      return g_aImStateTable[g_dwCurrentState].nId;
    }
    piVar2 = piVar2 + 0x15;
    state = state + 1;
  } while ((int)piVar2 < ((unsigned)(uintptr_t)((unsigned char *)&g_aImSeqTable + 0x20)));
  return 0;
}
#endif


/* ---- 0x10006620  Script_SetSequence ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name Script_SetSequence (the remaster's GrimFandango (Linux): the static SetSequence of
   the music script module (prefixed: the bridge refuses the bare name next to ImSetSequence);
   strings: 'SEQ_NULL' | 'ERR: bogus sequence...'); was FUN_10006620. */

int __cdecl Script_SetSequence(int id)

{
  int iVar1;
  int *piVar2;
  ImMusicEntry *file;
  int iVar3;
  int unaff_ESI;
  int iVar4;
  uint unaff_EDI;
  uint unaff_retaddr;
  uint in_stack_00000008;
  
  if (id == -1) {
    return g_aImSeqTable[g_dwCurrentSequence].nId;
  }
  iVar3 = id;
  if (id == 0) {
    iVar3 = 2000;
  }
  iVar4 = 0;
  piVar2 = &g_aImSeqTable[0].nId;
  do {
    if (iVar3 == *piVar2) {
      ImPrintf(g_aImSeqTable[iVar4].aName);
      ImPrintf(s_____100171b0);
      iVar3 = g_dwCurrentSequence;
      iVar1 = g_dwCurrentCuePoint;
      if (iVar4 != g_dwCurrentSequence) {
        if (iVar4 == 0) {
          if (g_dwCurrentCuePoint == 0) {
            if (g_dwCurrentState == 0) {
              file = (ImMusicEntry *)0x0;
            }
            else {
              file = g_aImStateTable + g_dwCurrentState;
            }
            Script_Trans(file->aFilename,g_dwCurrentState,1,unaff_EDI,unaff_ESI,unaff_retaddr,id,
                         in_stack_00000008);
            g_dwCurrentSequence = 0;
            iVar3 = g_dwCurrentSequence;
            iVar1 = g_dwCurrentCuePoint;
          }
          else {
            Script_Trans(g_aImSeqTable[g_dwCurrentCuePoint].aFilename,0,1,unaff_EDI,unaff_ESI,
                         unaff_retaddr,id,in_stack_00000008);
            iVar3 = g_dwCurrentCuePoint;
            g_dwCurrentSequence = g_dwCurrentCuePoint;
            g_dwCurrentCuePoint = 0;
            (&DAT_1002e25c)[iVar3] = 1;
            iVar1 = g_dwCurrentCuePoint;
          }
        }
        else if ((g_dwCurrentSequence == 0) ||
                ((iVar1 = iVar4, g_aImSeqTable[g_dwCurrentSequence].nTransType != 4 &&
                 (g_aImSeqTable[g_dwCurrentSequence].nTransType != 6)))) {
          Script_Trans(g_aImSeqTable[iVar4].aFilename,0,1,unaff_EDI,unaff_ESI,unaff_retaddr,id,
                       in_stack_00000008);
          g_dwCurrentCuePoint = 0;
          (&DAT_1002e25c)[iVar4] = 1;
          iVar3 = iVar4;
          g_dwCurrentSequence = iVar4;
          iVar1 = g_dwCurrentCuePoint;
        }
      }
      g_dwCurrentCuePoint = iVar1;
      return g_aImSeqTable[iVar3].nId;
    }
    piVar2 = piVar2 + 0x15;
    iVar4 = iVar4 + 1;
  } while ((int)piVar2 < ((unsigned)(uintptr_t)((unsigned char *)&g_aImNameAlias + 0x20)));
  ImPrintf(s_ERR__bogus_sequence____1001e720);
  return 0xffffffff;
}
#endif


/* ---- 0x100067a0  Script_NullCallback ---- */
/* Returns 0: passed as the two script callbacks ImInitializeScript takes, and called by the
   dispatcher; was FUN_100067a0. */

undefined4 Script_NullCallback(void)

{
  return 0;
}

/* ---- 0x100067b0  Script_Attribute ---- */
/* Script attributes: (-1, 0 / 1) pauses / resumes, (-1, -1) clears all; (10000, buf) copies the
   state and sequence names into buf and returns 0xde; (n < 0xe4, v) sets attribute n to v (unless v
   is -1) and returns it; was FUN_100067b0. */

undefined4 __cdecl Script_Attribute(uint attr,char *value)

{
  char cVar1;
  int iVar2;
  ImMusicEntry *pIVar3;
  ImMusicEntry *pIVar4;
  undefined4 *puVar5;
  
  if (attr == 0xffffffff) {
    if (value == (char *)0x0) {
      ImPause();
      return 0;
    }
    if (value == (char *)0x1) {
      ImResume();
      return 0;
    }
    if (value == (char *)0xffffffff) {
      puVar5 = &DAT_1002df78;
      for (iVar2 = 0xe4; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar5 = 0;
        puVar5 = puVar5 + 1;
      }
      return 0;
    }
  }
  else {
    if (attr == 10000) {
      pIVar4 = g_aImStateTable;
      do {
        cVar1 = pIVar4->aFilename[0];
        *value = cVar1;
        pIVar3 = pIVar4;
        while (value = value + 1, cVar1 != '\0') {
          pIVar3 = (ImMusicEntry *)(pIVar3->aFilename + 1);
          cVar1 = pIVar3->aFilename[0];
          *value = cVar1;
        }
        pIVar4 = pIVar4 + 1;
      } while ((int)pIVar4 < ((unsigned)(uintptr_t)&DAT_1001ae4c));
      pIVar4 = g_aImSeqTable;
      do {
        iVar2 = 1;
        do {
          cVar1 = pIVar4->aFilename[0];
          *value = cVar1;
          pIVar3 = pIVar4;
          while (value = value + 1, cVar1 != '\0') {
            pIVar3 = (ImMusicEntry *)(pIVar3->aFilename + 1);
            cVar1 = pIVar3->aFilename[0];
            *value = cVar1;
          }
          pIVar4 = pIVar4 + 1;
          iVar2 = iVar2 + -1;
        } while (iVar2 != 0);
      } while ((int)pIVar4 < ((unsigned)(uintptr_t)&DAT_1001bbc4));
      return 0xde;
    }
    if (attr < 0xe4) {
      if (value != (char *)0xffffffff) {
        ImPrintf(s_Set_attr__lu_to__lu____1001e750,attr,value);
        (&DAT_1002df78)[attr] = value;
      }
      return (&DAT_1002df78)[attr];
    }
    ImPrintf(s_ERR__bogus_attribute____1001e738);
  }
  return 0;
}

/* ---- 0x100068b0  Script_Trans ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name Script_Trans (the remaster's GrimFandango (Linux): the static Trans of the music
   script module (prefixed: the bare name is refused as too generic); strings: "1001 - Manny's
   Office" | 'SCRIPT ERR: failed start stream...' | 'SCRIPT ERR: Unable to open ' | 'and
   PAN=%lu...'); was FUN_100068b0. */

void __cdecl
Script_Trans(char *file,uint state,int sequence,uint param_4,int param_5,uint param_6,uint param_7,
            uint param_8)

{
  char *pcVar1;
  char cVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  ImNameAlias *pIVar7;
  int iVar8;
  int unaff_EBX;
  int unaff_EBP;
  int iVar9;
  int unaff_ESI;
  int unaff_EDI;
  ImNameAlias *pIVar10;
  char *pcVar11;
  bool bVar12;
  int unaff_retaddr;
  
  pcVar1 = file;
  if (g_dwLocalMusic == 0) {
    return;
  }
  if (file != (char *)0x0) {
    g_bTrans_name = *file;
    pcVar3 = &DAT_1002e311;
    if (g_bTrans_name != '\0') {
      do {
        cVar2 = pcVar3[(int)(file + -0x1002e310)];
        *pcVar3 = cVar2;
        pcVar3 = pcVar3 + 1;
      } while (cVar2 != '\0');
    }
    pIVar10 = g_aImNameAlias;
    if (g_aImNameAlias[0].aFrom[0] != '\0') {
      iVar9 = 0x12748;
      cVar2 = g_aImNameAlias[0].aFrom[0];
LAB_10006904:
      iVar8 = 0;
      for (pIVar7 = pIVar10; (cVar2 != '\0' && (pIVar7->aFrom[iVar9] == cVar2));
          pIVar7 = (ImNameAlias *)(pIVar7->aFrom + 1)) {
        cVar2 = pIVar7->aFrom[1];
        iVar8 = iVar8 + 1;
      }
      if (((iVar8 == 0) || ((&g_bTrans_name)[iVar8] != '\0')) || (pIVar10->aFrom[iVar8] != '\0'))
      goto LAB_1000692f;
      g_bTrans_name = pIVar10->aTo[0];
      pcVar3 = pIVar10->aTo;
      pcVar11 = &DAT_1002e311;
      cVar2 = g_bTrans_name;
      while (cVar2 != '\0') {
        pcVar3 = pcVar3 + 1;
        cVar2 = *pcVar3;
        *pcVar11 = cVar2;
        pcVar11 = pcVar11 + 1;
      }
    }
  }
LAB_1000695e:
  bVar12 = file != (char *)0x0;
  file = (char *)0x0;
  if ((bVar12) && (state != 0)) {
    if (*(uint *)(pcVar1 + 0x40) != 0) {
      state = *(uint *)(pcVar1 + 0x40);
    }
    file = *(char **)(&DAT_1002df84 + state * 4);
    if (*(int *)(pcVar1 + 0x44) != 0) {
      if ((file == (char *)0x0) && (1 < *(int *)(pcVar1 + 0x44))) {
        *(undefined4 *)(&DAT_1002df84 + state * 4) = 2;
      }
      else {
        *(char **)(&DAT_1002df84 + state * 4) = file + 1;
        if (*(int *)(pcVar1 + 0x44) < (int)(file + 1)) {
          *(undefined4 *)(&DAT_1002df84 + state * 4) = 1;
        }
      }
    }
  }
  if (file == (char *)0x0) {
    file = (char *)0x64;
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
  state = *(uint *)(pcVar1 + 0x48);
  if (state == 0) {
    state = 1000;
  }
  iVar9 = (int)(state * 3) / 0x32;
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
    ImPrintf(&g_bTrans_name);
    ImPrintf(s_____100171b0);
    uVar4 = ImOpenSound(&g_bTrans_name,0);
    if (uVar4 == 0) {
      ImPrintf(s_SCRIPT_ERR__Unable_to_open_1001e830);
      ImPrintf(&g_bTrans_name);
      ImPrintf(s_____100171b0);
      if (uVar5 == 0) {
        return;
      }
      ImFadeParam(uVar5,0x600,0,0x3c);
      return;
    }
    if (*(int *)(pcVar1 + 0x20) == 4) {
      DAT_1002e304 = 0;
      ImSetTrigger(uVar4,s__end_1001e858,0,unaff_EDI,unaff_ESI,unaff_EBP,unaff_EBX,unaff_retaddr,
                   (int)file,state,sequence,param_4,param_5);
    }
    ImPrintf(s_HOOK__lu____1001e824,file);
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
      ImSetHook(uVar4,(uint)file);
      goto LAB_10007019;
    }
    if (*(int *)(pcVar1 + 0x20) == 2) {
      ImSwitchStream(uVar5,uVar4,state,0,0);
      ImPrintf(s_FADE__lu____1001e818,state);
      ImPrintf(s_vol__lu____1001e80c,*(undefined4 *)(pcVar1 + 0x4c));
      ImFadeParam(uVar4,0x600,*(uint *)(pcVar1 + 0x4c),iVar9);
      ImFadeParam(uVar4,0x700,*(uint *)(pcVar1 + 0x50),iVar9);
      ImSetParam(uVar4,0x400,4);
      ImSetHook(uVar4,(uint)file);
      ImProcessStreams();
      goto LAB_10007019;
    }
    if (uVar5 == uVar4) {
      ImFadeParam(uVar4,0x600,*(uint *)(pcVar1 + 0x4c),iVar9);
      ImPrintf(s_fading_VOL__lu____1001e7d0,*(undefined4 *)(pcVar1 + 0x4c));
      if (*(uint *)(pcVar1 + 0x50) != 0) {
        ImFadeParam(uVar4,0x700,*(uint *)(pcVar1 + 0x50),iVar9);
        ImPrintf(s_and_PAN__lu____1001e7c0,*(undefined4 *)(pcVar1 + 0x50));
      }
      goto LAB_10007019;
    }
    if (((sequence == 0) && (*(int *)(pcVar1 + 0x40) != 0)) &&
       (*(int *)(pcVar1 + 0x40) == g_aImStateTable[g_dwCurrentState].nHookSlot)) {
      ImSwitchStream(uVar5,uVar4,state,0,1);
      ImFadeParam(uVar4,0x600,*(uint *)(pcVar1 + 0x4c),iVar9);
      ImFadeParam(uVar4,0x700,*(uint *)(pcVar1 + 0x50),iVar9);
      ImSetParam(uVar4,0x400,4);
      if (file == (char *)0x64) {
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
        ImSetTrigger(uVar5,s_exit_1001e804,0x1a,uVar5,uVar4,state,1,0,unaff_EDI,unaff_ESI,unaff_EBP,
                     unaff_EBX,unaff_retaddr);
        ImSetTrigger(uVar5,s_exit_1001e804,0xe,uVar4,0x600,*(int *)(pcVar1 + 0x4c),iVar9,unaff_EDI,
                     unaff_ESI,unaff_EBP,unaff_EBX,unaff_retaddr,(int)file);
        ImSetTrigger(uVar5,s_exit_1001e804,0xe,uVar4,0x700,*(int *)(pcVar1 + 0x50),iVar9,unaff_EDI,
                     unaff_ESI,unaff_EBP,unaff_EBX,unaff_retaddr,(int)file);
        ImSetTrigger(uVar5,s_exit_1001e804,0xc,uVar4,0x400,4,unaff_EDI,unaff_ESI,unaff_EBP,unaff_EBX
                     ,unaff_retaddr,(int)file,state);
      }
      else {
        if (iVar8 == 0xb) {
          ImSetTrigger(uVar5,s_exit2_1001e7fc,0x1a,uVar5,uVar4,state,1,0,unaff_EDI,unaff_ESI,
                       unaff_EBP,unaff_EBX,unaff_retaddr);
          ImSetTrigger(uVar5,s_exit2_1001e7fc,0xe,uVar4,0x600,*(int *)(pcVar1 + 0x4c),iVar9,
                       unaff_EDI,unaff_ESI,unaff_EBP,unaff_EBX,unaff_retaddr,(int)file);
          ImSetTrigger(uVar5,s_exit2_1001e7fc,0xe,uVar4,0x700,*(int *)(pcVar1 + 0x50),iVar9,
                       unaff_EDI,unaff_ESI,unaff_EBP,unaff_EBX,unaff_retaddr,(int)file);
          ImSetTrigger(uVar5,s_exit2_1001e7fc,0xc,uVar4,0x400,4,unaff_EDI,unaff_ESI,unaff_EBP,
                       unaff_EBX,unaff_retaddr,(int)file,state);
          ImSetTrigger(uVar5,s_exit2_1001e7fc,0xf,uVar4,(int)file,unaff_EDI,unaff_ESI,unaff_EBP,
                       unaff_EBX,unaff_retaddr,(int)file,state,sequence);
          ImProcessStreams();
          goto LAB_10007019;
        }
        if (iVar8 != 0xc) {
          ImSwitchStream(uVar5,uVar4,state,0,0);
          ImPrintf(s_FADE__lu____1001e818,state);
          ImPrintf(s_vol__lu____1001e80c,*(undefined4 *)(pcVar1 + 0x4c));
          ImFadeParam(uVar4,0x600,*(uint *)(pcVar1 + 0x4c),iVar9);
          ImFadeParam(uVar4,0x700,*(uint *)(pcVar1 + 0x50),iVar9);
          ImPrintf(s_set_pan__lu____1001e7e4,*(undefined4 *)(pcVar1 + 0x50));
          ImSetParam(uVar4,0x400,4);
          ImSetHook(uVar4,(uint)file);
          goto LAB_10006f42;
        }
        ImSetHook(uVar5,99);
        ImSetTrigger(uVar5,s_clear_1001e7f4,0xf,uVar5,0x80,unaff_EDI,unaff_ESI,unaff_EBP,unaff_EBX,
                     unaff_retaddr,(int)file,state,sequence);
        ImSetTrigger(uVar5,s_exit_1001e804,0x1a,uVar5,uVar4,state,1,0,unaff_EDI,unaff_ESI,unaff_EBP,
                     unaff_EBX,unaff_retaddr);
        ImSetTrigger(uVar5,s_exit_1001e804,0xe,uVar4,0x600,*(int *)(pcVar1 + 0x4c),iVar9,unaff_EDI,
                     unaff_ESI,unaff_EBP,unaff_EBX,unaff_retaddr,(int)file);
        ImSetTrigger(uVar5,s_exit_1001e804,0xe,uVar4,0x700,*(int *)(pcVar1 + 0x50),iVar9,unaff_EDI,
                     unaff_ESI,unaff_EBP,unaff_EBX,unaff_retaddr,(int)file);
        ImSetTrigger(uVar5,s_exit_1001e804,0xc,uVar4,0x400,4,unaff_EDI,unaff_ESI,unaff_EBP,unaff_EBX
                     ,unaff_retaddr,(int)file,state);
        ImPrintf(s_HOOK__lu____1001e824,file);
      }
      ImSetTrigger(uVar5,s_exit_1001e804,0xf,uVar4,(int)file,unaff_EDI,unaff_ESI,unaff_EBP,unaff_EBX
                   ,unaff_retaddr,(int)file,state,sequence);
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
    ImSetTrigger(0xbc6150,s__end_1001e858,0,unaff_EDI,unaff_ESI,unaff_EBP,unaff_EBX,unaff_retaddr,
                 (int)file,state,sequence,param_4,param_5);
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
    ImSetTrigger(uVar5,s__end_1001e858,0,unaff_EDI,unaff_ESI,unaff_EBP,unaff_EBX,unaff_retaddr,
                 (int)file,state,sequence,param_4,param_5);
    return;
  }
  return;
LAB_1000692f:
  cVar2 = pIVar10[1].aFrom[0];
  pIVar10 = pIVar10 + 1;
  iVar9 = iVar9 + -0x40;
  if (cVar2 == '\0') goto LAB_1000695e;
  goto LAB_10006904;
}
#endif


/* ---- 0x100070e0  Script_Callback ---- */
/* Original name Script_Callback (the remaster's GrimFandango (Linux): the static Callback of the
   music script module (prefixed: the bare name is refused as too generic); strings: "ERR:callback
   got marker != '_end'..." | 'CALLBACK:'); was FUN_100070e0. */

void __cdecl Script_Callback(char *marker)

{
  ImPrintf(s_CALLBACK__1001e898);
  if (*marker == '_') {
    DAT_1002e304 = 1;
    return;
  }
  ImPrintf(s_ERR_callback_got_marker______end_1001e870);
  return;
}

/* ---- 0x10007110  Script_StopLocalMusic ---- */
/* When the music is local (not streamed by the game): stops all sounds, unloads and closes them;
   was FUN_10007110. */

void Script_StopLocalMusic(void)

{
  if (g_dwLocalMusic != 0) {
    ImStopAllSounds();
    ImUnloadAll();
    ImCloseAll();
    return;
  }
  return;
}

/* ---- 0x100089b0  LoadLip ---- */
/* Original name LoadLip (the remaster's GrimFandango (Linux): aligned call in CacheGetSoundId,
   SoundsRegisterVoice); was Im_SoundsFindByName. */

undefined4 __cdecl LoadLip(undefined4 name,char *sound)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  bool bVar5;
  
  iVar3 = -1;
  iVar1 = (**(code **)(g_dwSounds_pHS + 0x30))(name,s_rb_1001e900);
  if (iVar1 == 0) {
    Im_SoundsFreeSlot((int)sound);
  }
  else if (sound != (char *)0x0) {
    if (((sound == g_dwLipSfx1ID) || (sound == g_dwLipSfx2ID)) || (sound == g_dwLipSfx3ID)) {
      (**(code **)(g_dwSounds_pHS + 0x34))(iVar1);
      return 1;
    }
    if (sound == (char *)0x2710) {
      g_dwLipStreamID = sound;
      iVar3 = 0;
      sound = &g_bLipStreamData;
    }
    else if (g_dwLipSfx1ID == (char *)0x0) {
      g_dwLipSfx1ID = sound;
      iVar3 = 1;
      sound = &g_aLipSfx1Data;
    }
    else if (g_dwLipSfx2ID == (char *)0x0) {
      g_dwLipSfx2ID = sound;
      iVar3 = 2;
      sound = &g_aLipSfx2Data;
    }
    else if (g_dwLipSfx3ID == (char *)0x0) {
      g_dwLipSfx3ID = sound;
      iVar3 = 3;
      sound = &g_aLipSfx3Data;
    }
    if (-1 < iVar3) {
      (**(code **)(g_dwSounds_pHS + 0x4c))(iVar1,0,2);
      iVar2 = (**(code **)(g_dwSounds_pHS + 0x48))(iVar1);
      (**(code **)(g_dwSounds_pHS + 0x4c))(iVar1,0,0);
      if (iVar2 < 0x7d1) {
        (**(code **)(g_dwSounds_pHS + 0x38))(iVar1,sound,iVar2);
        iVar2 = 4;
        bVar5 = true;
        pcVar4 = s_LIP__1001e994;
        do {
          if (iVar2 == 0) break;
          iVar2 = iVar2 + -1;
          bVar5 = *sound == *pcVar4;
          sound = sound + 1;
          pcVar4 = pcVar4 + 1;
        } while (bVar5);
        if (!bVar5) {
          switch(iVar3) {
          case 0:
            g_dwLipStreamID = (char *)0x0;
            return 0;
          case 1:
            g_dwLipSfx1ID = (char *)0x0;
            return 0;
          case 2:
            g_dwLipSfx2ID = (char *)0x0;
            return 0;
          case 3:
            g_dwLipSfx3ID = (char *)0x0;
            return 0;
          }
        }
      }
    }
  }
  if (iVar1 != 0) {
    (**(code **)(g_dwSounds_pHS + 0x34))(iVar1);
  }
  return 0;
}

/* ---- 0x10008b60  Im_SoundsFreeSlot ---- */
/* Unidentified function of iMUSE_sounds.c (sound resource slots) */

void __cdecl Im_SoundsFreeSlot(int sound)

{
  if (sound == g_dwLipStreamID) {
    g_dwLipStreamID = 0;
  }
  if (sound == g_dwLipSfx1ID) {
    g_dwLipSfx1ID = 0;
  }
  if (sound == g_dwLipSfx2ID) {
    g_dwLipSfx2ID = 0;
  }
  if (sound == g_dwLipSfx3ID) {
    g_dwLipSfx3ID = 0;
  }
  return;
}

/* ---- 0x10008bb0  iMUSE_GetPhoneme ---- */
int __cdecl iMUSE_GetPhoneme(int sound,int offset)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  
                    /* 0x8bb0  78  iMUSE_GetPhoneme */
  if (sound == g_dwLipStreamID) {
    iVar1 = SoundGetVoiceTime();
    iVar1 = Lip_PhonemeAtTime(sound,iVar1 + offset);
    return iVar1;
  }
  if (((sound == g_dwLipSfx1ID) || (sound == g_dwLipSfx2ID)) || (sound == g_dwLipSfx3ID)) {
    iVar1 = 0;
    iVar4 = 0;
    piVar2 = &DAT_10031548;
    do {
      if (iVar1 != 0) goto LAB_10008c0e;
      if (*piVar2 == sound) {
        iVar1 = iVar4 + 100;
      }
      piVar2 = piVar2 + 0x10;
      iVar4 = iVar4 + 1;
    } while ((int)piVar2 < ((unsigned)(uintptr_t)&DAT_10031d48));
    if (iVar1 != 0) {
LAB_10008c0e:
      uVar3 = ImGetParam(iVar1,0x1a00);
      iVar1 = Lip_PhonemeAtTime(sound,uVar3 + offset);
      return iVar1;
    }
  }
  return 0;
}

/* ---- 0x10008c40  Lip_PhonemeAtTime ---- */
/* The phoneme of the lip-sync track of sound `id` (the stream, 10000, or one of the three sound
   effects) at time t (in 16ths): the entry whose time range holds it, 0x5f (rest) when none does;
   was FUN_10008c40. */

int __cdecl Lip_PhonemeAtTime(int sound,int time)

{
  undefined *puVar1;
  short *psVar2;
  int iVar3;
  int iVar4;
  
  if (sound == 10000) {
    if (g_dwLipStreamID == 0) {
      return 0;
    }
    puVar1 = &g_bLipStreamData;
  }
  else if (sound == g_dwLipSfx1ID) {
    puVar1 = &g_aLipSfx1Data;
  }
  else if (sound == g_dwLipSfx2ID) {
    puVar1 = &g_aLipSfx2Data;
  }
  else {
    if (sound != g_dwLipSfx3ID) {
      return 0;
    }
    puVar1 = &g_aLipSfx3Data;
  }
  iVar3 = time >> 4;
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

/* ---- 0x10008ce0  Timer_Start ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Starts iMUSE's multimedia timer (timeBeginPeriod / timeSetEvent with timer_callback, at least 50
   ms resolution) and waits up to 3 x 4 s for its first tick, restarting it when none comes. Returns
   the tick count, 0 on failure. Hand-written; was FUN_10008ce0. */

int __cdecl Timer_Start(void)

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
    _DAT_10031d28 = timeSetEvent(_DAT_1002e338,0,((unsigned)(uintptr_t)timer_callback),0xf,1);
    iVar3 = timeGetTime();
    _g_dwTimerCounter = 0;
    iVar1 = 2;
    do {
      if (_g_dwTimerCounter != 0) {
        return _g_dwTimerCounter;
      }
      iVar4 = timeGetTime();
      uVar2 = iVar4 - iVar3;
      while (uVar2 < 4000) {
        if (_g_dwTimerCounter != 0) goto LAB_10008de9;
        iVar4 = timeGetTime();
        uVar2 = iVar4 - iVar3;
      }
      if (_g_dwTimerCounter == 0) {
        timeKillEvent(_DAT_10031d28);
        timeEndPeriod(_DAT_10031520);
        timeBeginPeriod(_DAT_10031520);
        _DAT_10031d28 = timeSetEvent(_DAT_1002e338,0,((unsigned)(uintptr_t)timer_callback),0xf,1);
        iVar3 = timeGetTime();
      }
LAB_10008de9:
      bVar5 = iVar1 != 0;
      iVar1 = iVar1 + -1;
    } while (bVar5);
    if (_g_dwTimerCounter != 0) {
      return _g_dwTimerCounter;
    }
  }
  return 0;
}
#undef auStack_8

#endif


/* ---- 0x10008e00  timer_callback ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Original name timer_callback (the remaster's GrimFandango (Linux): the only unmatched caller of
   ImHeartbeat; 1 matched neighbours agree, 0 disagree); was FUN_10008e00. */

undefined4 __stdcall timer_callback(int a1,int a2,int a3,int a4,int a5)

{
  undefined4 uVar1;
  
  _DAT_10031e80 = 1;
  _g_dwTimerCounter = _g_dwTimerCounter + 1;
  uVar1 = ImHeartbeat();
  _DAT_10031e80 = 0;
  return uVar1;
}

/* ---- 0x10008e30  Timer_Stop ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Kills the multimedia timer (timeKillEvent / timeEndPeriod) and runs timer_callback once more; was
   FUN_10008e30. */

void __cdecl Timer_Stop(void)

{
  timeKillEvent(_DAT_10031d28);
  timeEndPeriod(_DAT_10031520);
  timer_callback(1,2,3,4,5);
  return;
}

/* ---- 0x10008e60  Sounds_FreeAll ---- */
/* Frees the 32 sound slots (their sound data through the host's free) and clears the handle counter
   and the sound cache; was FUN_10008e60. */

void __cdecl Sounds_FreeAll(void)

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
        (**(code **)(g_dwSounds_pHS + 0x24))(*(int *)(puVar1 + 0x28));
      }
    }
    puVar1 = puVar1 + -0x40;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  g_dwNextHandle = 0;
  puVar3 = (undefined4 *)&g_bSoundCache;
  for (iVar2 = 0x200; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  return;
}

/* ---- 0x100093d0  Im_SoundsPrepare ---- */
/* Decodes the header/first block of a loaded sound and applies FX */

void __cdecl Im_SoundsPrepare(uint sound)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined2 *dst;
  uint blockAlign;
  int iVar1;
  undefined1 *puVar2;
  bool bVar3;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  if ((0x456 < (int)sound) && ((int)sound < 0x557)) {
    puVar2 = &DAT_10031ce8;
    iVar1 = 0x1f;
    while (*(uint *)(puVar2 + 0x20) != sound) {
      puVar2 = puVar2 + -0x40;
      bVar3 = iVar1 == 0;
      iVar1 = iVar1 + -1;
      if (bVar3) {
        return;
      }
    }
    if ((*(int *)(puVar2 + 0x28) != 0) && (*(int *)(puVar2 + 0x2c) != 0)) {
      AudioLib_ParseWaveFileHeader
                (*(uint **)(puVar2 + 0x30),(int *)0x0,&local_c,&local_8,&local_4,(int *)0x0,&sound);
      if ((local_c == 0x5622) && (((local_8 == 0x10 && (local_4 == 1)) && (0 < (int)sound)))) {
        dst = (undefined2 *)
              (**(code **)(g_dwSounds_pHS + 0x20))
                        (sound * 2 + 0x50,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0x7eb);
        if (dst != (undefined2 *)0x0) {
          blockAlign = Im_ApplyFXPreset((undefined2 *)(*(int *)(puVar2 + 0x2c) + 0x50),sound,dst,
                                        (int *)0x0,(int *)0x0,0);
          (**(code **)(g_dwSounds_pHS + 0x24))(*(undefined4 *)(puVar2 + 0x28));
          *(undefined2 **)(puVar2 + 0x28) = dst;
          if (blockAlign == 2) {
            sound = sound << 1;
          }
          *(uint *)(puVar2 + 0x34) = sound;
          AudioLib_CreateWaveFileHeader
                    ((undefined4 *)(sound + (int)dst),3,0x5622,0x10,blockAlign,sound);
          *(uint *)(puVar2 + 0x30) = sound + *(int *)(puVar2 + 0x28);
          *(undefined1 *)(sound + *(int *)(puVar2 + 0x28) + 0x1f) = 1;
          *(undefined4 *)(puVar2 + 0x38) = 1;
          *(int *)(puVar2 + 0x2c) = *(int *)(puVar2 + 0x28) + -0x50;
        }
        iVar1 = timeGetTime();
        *(int *)(puVar2 + 0x24) = iVar1;
      }
    }
  }
  return;
}
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x10009530  Sounds_GetSoundAddr ---- */
/* The sound data address of sound slot `id` (100..0x84), 0 otherwise; ihost_get_sound_addr returns
   it; was FUN_10009530. */

uint __cdecl Sounds_GetSoundAddr(int sound)

{
  if ((99 < sound) && (sound < 0x85)) {
    return *(uint *)((sound + -100) * 0x40 + ((unsigned)(uintptr_t)&DAT_10031554));
  }
  return 0;
}

/* ---- 0x10009560  Sounds_GetMapAddr ---- */
/* The map address of sound slot `id` (100..0x84), 0 otherwise; ihost_get_map_addr returns it; was
   FUN_10009560. */

uint __cdecl Sounds_GetMapAddr(int sound)

{
  if ((99 < sound) && (sound < 0x85)) {
    return *(uint *)((sound + -100) * 0x40 + ((unsigned)(uintptr_t)&DAT_10031558));
  }
  return 0;
}

/* ---- 0x100095d0  grimSound_LipSyncLoad ---- */
uint * __cdecl grimSound_LipSyncLoad(uint *name)

{
  int *f;
  uint *puVar1;
  uint size;
  undefined4 *buf;
  int iVar2;
  uint *puVar3;
  
                    /* 0x95d0  74  grimSound_LipSyncLoad */
  if (name == (uint *)0x0) {
    (**(code **)(g_dwSounds_pHS + 0x18))(((unsigned)(uintptr_t)&DAT_1001e99c),s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0x845)
    ;
  }
  f = iRes_FOPEN(name,&DAT_1001e900);
  if (f == (int *)0x0) {
    return (uint *)0x0;
  }
  puVar1 = (uint *)(**(code **)(g_dwSounds_pHS + 0x20))
                             (0x28,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0x851);
  puVar3 = puVar1;
  for (iVar2 = 10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  Im_MemCopy(puVar1,name,0x1f);
  *(undefined1 *)((int)puVar1 + 0x1f) = 0;
  iRes_FSEEK((undefined *)f,0,2);
  size = iRes_FTELL((undefined *)f);
  iRes_FSEEK((undefined *)f,0,0);
  puVar1[8] = size;
  buf = (undefined4 *)
        (**(code **)(g_dwSounds_pHS + 0x20))(size,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0x85e);
  puVar1[9] = (uint)buf;
  iRes_FREAD(f,buf,size);
  iRes_FCLOSE(f);
  return puVar1;
}

/* ---- 0x100096b0  grimSound_LipSyncFree ---- */
undefined4 __cdecl grimSound_LipSyncFree(int lip)

{
  undefined4 uVar1;
  
                    /* 0x96b0  73  grimSound_LipSyncFree */
  if (lip == 0) {
    (**(code **)(g_dwSounds_pHS + 0x18))(((unsigned)(uintptr_t)&DAT_1001e9b8),s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0x87c)
    ;
  }
  if (*(int *)(lip + 0x24) != 0) {
    (**(code **)(g_dwSounds_pHS + 0x24))(*(int *)(lip + 0x24));
    *(undefined4 *)(lip + 0x24) = 0;
  }
  uVar1 = (**(code **)(g_dwSounds_pHS + 0x24))(lip);
  return uVar1;
}

/* ---- 0x10009700  Im_DiscardMessage ---- */
/* An empty printf: stored in a table of message functions; was FUN_10009700. */

void __cdecl Im_DiscardMessage(char *fmt,...)

{
  return;
}

/* ---- 0x10009710  iRes_FOPEN ---- */
/* iMUSE_sounds.c: opens the sound file into a slot Original name iRes_FOPEN (the remaster's
   GrimFandango (Linux): aligned call in CacheGetSoundId, SoundsRegisterVoice,
   grimSound_LipSyncLoad); was Im_SoundsLoad. */

int * __cdecl iRes_FOPEN(uint *name,char *mode)

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
  
  if (((*mode == 'w') || (*mode == 'a')) || (mode[1] == '+')) {
    piVar2 = (int *)(**(code **)(g_dwSounds_pHS + 0x30))(name,mode);
    return piVar2;
  }
  piVar2 = (int *)(**(code **)(g_dwSounds_pHS + 0x30))(name,mode);
  if (piVar2 == (int *)0x0) {
    return (int *)0x0;
  }
  (**(code **)(g_dwSounds_pHS + 0x38))(piVar2,acStack_8,4);
  iVar7 = 4;
  bVar12 = true;
  pcVar10 = acStack_8;
  pcVar11 = s_MCMP_10017098;
  do {
    if (iVar7 == 0) break;
    iVar7 = iVar7 + -1;
    bVar12 = *pcVar10 == *pcVar11;
    pcVar10 = pcVar10 + 1;
    pcVar11 = pcVar11 + 1;
  } while (bVar12);
  if (!bVar12) {
    (**(code **)(g_dwSounds_pHS + 0x4c))(piVar2,0,0);
    return piVar2;
  }
  if (g_dwIRes_csInit == 0) {
    InitializeCriticalSection(((unsigned)(uintptr_t)&DAT_1002fbb8));
    g_dwIRes_csInit = 1;
  }
  EnterCriticalSection(((unsigned)(uintptr_t)&DAT_1002fbb8));
  iVar7 = *(int *)(&g_aMcmpFileHandles + g_dwNextToAllocate * 0x8c);
  iVar8 = g_dwNextToAllocate;
  while (iVar7 != 0) {
    uVar9 = (int)(iVar8 + 1U) >> 0x1f;
    iVar3 = ((iVar8 + 1U ^ uVar9) - uVar9 & 0x1f ^ uVar9) - uVar9;
    if (iVar3 == g_dwNextToAllocate) break;
    iVar8 = iVar3;
    iVar7 = *(int *)(&g_aMcmpFileHandles + iVar3 * 0x8c);
  }
  iVar7 = iVar8 * 0x8c;
  if (*(int *)(&g_aMcmpFileHandles + iVar8 * 0x8c) == 0) {
    g_dwNextToAllocate = iVar8;
    LeaveCriticalSection(((unsigned)(uintptr_t)&DAT_1002fbb8));
    *(int **)(&g_aMcmpFileHandles + iVar7) = piVar2;
    *(undefined4 *)(&DAT_100303a8 + iVar7) = 0;
    (**(code **)(g_dwSounds_pHS + 0x38))(piVar2,&mode,2);
    uVar6 = CONCAT11((char)mode,(char)((uint)mode >> 8));
    mode = (char *)(uint)uVar6;
    *(uint *)(&DAT_100303ac + iVar7) = (uint)uVar6;
    (**(code **)(g_dwSounds_pHS + 0x4c))(piVar2,(int)mode * 9 + 6,0);
    PIECE(uStack_14,0,2) = PIECE(uStack_14,1,2);
    (**(code **)(g_dwSounds_pHS + 0x38))(piVar2,&uStack_14,2);
    uStack_14 = (uint)CONCAT11((char)(undefined2)uStack_14,
                               (char)((ushort)(undefined2)uStack_14 >> 8));
    iStack_c = ((uint)mode & 0xffff) * 9;
    pbVar4 = (byte *)(**(code **)(g_dwSounds_pHS + 0x20))
                               (iStack_c,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0x956);
    pbStack_4 = pbVar4;
    iVar3 = (**(code **)(g_dwSounds_pHS + 0x20))
                      ((uStack_14 & 0xffff) + (((uint)mode & 0xffff) + 1) * 0x14,
                       s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0x958);
    *(int *)(&DAT_100303b0 + iVar7) = iVar3;
    iVar8 = iVar3 + (uStack_14 & 0xffff);
    *(int *)(&DAT_100303b4 + iVar7) = iVar8;
    iVar8 = iVar8 + 4 + ((uint)mode & 0xffff) * 4;
    *(int *)(&DAT_100303b8 + iVar7) = iVar8;
    iVar8 = iVar8 + 4 + ((uint)mode & 0xffff) * 4;
    *(int *)(&DAT_100303bc + iVar7) = iVar8;
    iVar8 = iVar8 + 4 + ((uint)mode & 0xffff) * 4;
    *(int *)(&DAT_100303c0 + iVar7) = iVar8;
    *(uint *)(&DAT_100303c4 + iVar7) = iVar8 + 4 + ((uint)mode & 0xffff) * 4;
    (**(code **)(g_dwSounds_pHS + 0x38))(piVar2,iVar3,uStack_14 & 0xffff);
    (**(code **)(g_dwSounds_pHS + 0x4c))(piVar2,6,0);
    (**(code **)(g_dwSounds_pHS + 0x38))(piVar2,pbVar4,iStack_c);
    iVar3 = 0;
    iStack_10 = ((uint)mode & 0xffff) * 9 + 8 + (uStack_14 & 0xffff);
    iVar8 = 0;
    if (((uint)mode & 0xffff) != 0) {
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
      } while (iVar8 < (int)((uint)mode & 0xffff));
    }
    *(int *)(*(int *)(&DAT_100303bc + iVar7) + ((uint)mode & 0xffff) * 4) = iVar3;
    *(int *)(&DAT_100303a4 + iVar7) = iVar3;
    *(int *)(*(int *)(&DAT_100303c4 + iVar7) + ((uint)mode & 0xffff) * 4) = iStack_10;
    (**(code **)(g_dwSounds_pHS + 0x24))(pbStack_4);
    AudioLib_ResetCompressor((undefined1 *)(iVar7 + ((unsigned)(uintptr_t)&DAT_100303d4)));
    *(undefined4 *)(&DAT_100303cc + iVar7) = 0;
    *(undefined4 *)(&DAT_100303d0 + iVar7) = 0;
    *(undefined4 *)(&DAT_100303c8 + iVar7) = 0xffffffff;
    Im_MemCopy((uint *)(iVar7 + ((unsigned)(uintptr_t)&DAT_100303da)),name,0x50);
    (&DAT_10030429)[iVar7] = 0;
    return (int *)(&g_aMcmpFileHandles + iVar7);
  }
  (**(code **)(g_dwSounds_pHS + 0x34))(piVar2);
  return (int *)0x0;
}
#undef acStack_8
#undef iStack_10
#undef iStack_c
#undef pbStack_4
#undef uStack_14


/* ---- 0x10009b20  iRes_FCLOSE ---- */
/* Original name iRes_FCLOSE (the remaster's GrimFandango (Linux): the close of the iRes_FOPEN /
   iRes_FREAD file layer, body similarity); was Im_SoundsUnload. */

undefined4 __cdecl iRes_FCLOSE(undefined4 *f)

{
  undefined4 uVar1;
  int iVar2;
  
  if ((&DAT_1003039f < f) && (f < &DAT_10031520)) {
    uVar1 = *f;
    if (f[4] != 0) {
      (**(code **)(g_dwSounds_pHS + 0x24))(f[4]);
      f[4] = 0;
    }
    if (f[0xc] != 0) {
      (**(code **)(g_dwSounds_pHS + 0x24))(f[0xc]);
    }
    for (iVar2 = 0x23; iVar2 != 0; iVar2 = iVar2 + -1) {
      *f = 0;
      f = f + 1;
    }
    (**(code **)(g_dwSounds_pHS + 0x34))(uVar1);
    return 0;
  }
  uVar1 = (**(code **)(g_dwSounds_pHS + 0x34))(f);
  return uVar1;
}

/* ---- 0x10009b90  iRes_FREAD ---- */
/* Original name iRes_FREAD (the remaster's GrimFandango (Linux): aligned call in CacheGetSoundId,
   grimSound_LipSyncLoad); was Im_SoundsReadBlock. */

uint __cdecl iRes_FREAD(undefined4 *f,undefined4 *buf,uint size)

{
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
  byte *local_c;
  uint local_4;
  
  local_c = (byte *)0x0;
  local_4 = 0;
  if ((f < &g_aMcmpFileHandles) || (&DAT_1003151f < f)) {
    uVar7 = (**(code **)(g_dwSounds_pHS + 0x38))(f,buf,size);
    return uVar7;
  }
  iVar1 = iMUSE_sounds__9eb0((int)f,f[2]);
  iVar2 = iMUSE_sounds__9eb0((int)f,(size - 1) + f[2]);
  if (iVar1 < 0) {
    return 0;
  }
  if (iVar2 < 0) {
    iVar2 = f[3] + -1;
    size = f[1] - f[2];
  }
  iVar8 = iVar1;
  if (size == 0) {
    return 0;
  }
  do {
    if (iVar2 < iVar8) {
      if (local_c != (byte *)0x0) {
        (**(code **)(g_dwSounds_pHS + 0x24))(local_c);
      }
      f[2] = f[2] + size;
      return size;
    }
    if ((f[0xc] == 0) || (iVar8 != f[10])) {
      uVar7 = *(uint *)(f[8] + iVar8 * 4);
      if (local_4 < uVar7) {
        local_c = (byte *)(**(code **)(g_dwSounds_pHS + 0x28))
                                    (local_c,uVar7,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0xa14);
        local_4 = *(uint *)(f[8] + iVar8 * 4);
      }
      (**(code **)(g_dwSounds_pHS + 0x4c))(*f,*(undefined4 *)(f[9] + iVar8 * 4),0);
      (**(code **)(g_dwSounds_pHS + 0x38))(*f,local_c,*(undefined4 *)(f[8] + iVar8 * 4));
      uVar7 = *(uint *)(f[6] + iVar8 * 4);
      puVar4 = (uint *)(f[6] + iVar8 * 4);
      if ((uint)f[0xb] < uVar7) {
        uVar3 = (**(code **)(g_dwSounds_pHS + 0x28))
                          (f[0xc],uVar7,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0xa21);
        f[0xc] = uVar3;
        puVar4 = (uint *)(f[6] + iVar8 * 4);
        f[0xb] = *(undefined4 *)(f[6] + iVar8 * 4);
      }
      uVar7 = *puVar4;
      iVar5 = 4;
      bVar15 = true;
      pcVar9 = *(char **)(f[5] + iVar8 * 4);
      pcVar12 = s_VIMA_1001e9c0;
      do {
        if (iVar5 == 0) break;
        iVar5 = iVar5 + -1;
        bVar15 = *pcVar9 == *pcVar12;
        pcVar9 = pcVar9 + 1;
        pcVar12 = pcVar12 + 1;
      } while (bVar15);
      if (bVar15) {
        AudioLib_UncompressBlock((byte *)(f + 0xd),(undefined2 *)f[0xc],local_c,uVar7);
      }
      else {
        uVar6 = *(uint *)(f[8] + iVar8 * 4);
        if (uVar7 < uVar6) {
          uVar6 = uVar7;
        }
        pbVar10 = local_c;
        pbVar13 = (byte *)f[0xc];
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
      f[10] = iVar8;
    }
    if (iVar1 == iVar2) {
      iVar5 = f[2] - *(int *)(f[7] + iVar8 * 4);
      uVar7 = size;
    }
    else if (iVar8 == iVar1) {
      iVar5 = f[2] - *(int *)(f[7] + iVar8 * 4);
      uVar7 = *(int *)(f[6] + iVar8 * 4) - iVar5;
    }
    else if (iVar8 == iVar2) {
      iVar5 = 0;
      uVar7 = (size - *(int *)(f[7] + iVar8 * 4)) + f[2];
    }
    else {
      iVar5 = 0;
      uVar7 = *(uint *)(f[6] + iVar8 * 4);
    }
    puVar11 = (undefined4 *)(iVar5 + f[0xc]);
    puVar14 = buf;
    for (uVar6 = uVar7 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *puVar14 = *puVar11;
      puVar11 = puVar11 + 1;
      puVar14 = puVar14 + 1;
    }
    buf = (undefined4 *)((int)buf + uVar7);
    iVar8 = iVar8 + 1;
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined1 *)puVar14 = *(undefined1 *)puVar11;
      puVar11 = (undefined4 *)((int)puVar11 + 1);
      puVar14 = (undefined4 *)((int)puVar14 + 1);
    }
  } while( true );
}

/* ---- 0x1000a070  iMUSE_DeclareBufferSizes ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl
iMUSE_DeclareBufferSizes
          (uint voiceBufferSize,uint voiceGulpSize,uint voiceCriticalSize,uint musicBufferSize,
          uint musicGulpSize,uint musicCriticalSize,uint largeFadeSize,uint largeFadeCount,
          uint smallFadeSize,uint smallFadeCount,uint nonPurgeCacheSize,uint waveMixCount)

{
                    /* 0xa070  75  iMUSE_DeclareBufferSizes */
  _g_dwImVoiceBufferSize = voiceBufferSize;
  _g_dwImVoiceGulpSize = voiceGulpSize;
  _g_dwImVoiceCriticalSize = voiceCriticalSize;
  _g_dwImMusicBufferSize = musicBufferSize;
  _g_dwImMusicGulpSize = musicGulpSize;
  _g_dwImMusicCriticalSize = musicCriticalSize;
  g_dwImLargeFadeSize = largeFadeSize;
  g_dwImLargeFadeCount = largeFadeCount;
  g_dwImSmallFadeSize = smallFadeSize;
  g_dwImSmallFadeCount = smallFadeCount;
  _g_dwImNonPurgeCacheSize = nonPurgeCacheSize;
  g_dwImWaveMixCount = waveMixCount;
  _g_dwEffectsHeapSize = 150000;
  return;
}

/* ---- 0x1000a0f0  iMUSE_GetMemoryFootprint ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint __cdecl iMUSE_GetMemoryFootprint(void)

{
                    /* 0xa0f0  77  iMUSE_GetMemoryFootprint */
  return _DAT_10031d4c;
}

/* ---- 0x1000a100  iMUSE_GetSoundCacheSize ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint __cdecl iMUSE_GetSoundCacheSize(void)

{
                    /* 0xa100  79  iMUSE_GetSoundCacheSize */
  return _DAT_10031d48;
}

/* ---- 0x1000a110  iMUSE_SetHook ---- */
uint __cdecl iMUSE_SetHook(uint *name,uint hook)

{
  int sound;
  uint uVar1;
  
                    /* 0xa110  80  iMUSE_SetHook */
  sound = CacheGetSoundId(name);
  if (sound == 0) {
    return 0xffffffff;
  }
  uVar1 = ImSetHook(sound,hook);
  return uVar1;
}

/* ---- 0x1000a140  iMUSE_GetHook ---- */
uint __cdecl iMUSE_GetHook(uint *name)

{
  int sound;
  uint uVar1;
  
                    /* 0xa140  76  iMUSE_GetHook */
  sound = CacheGetSoundId(name);
  if (sound == 0) {
    return 0xffffffff;
  }
  uVar1 = ImGetHook(sound);
  return uVar1;
}

/* ---- 0x1000a160  iMUSE_SetVoiceEffect ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl iMUSE_SetVoiceEffect(uint *name)

{
  int iVar1;
  
                    /* 0xa160  81  iMUSE_SetVoiceEffect */
  Im_MemCopy((uint *)&g_aVoxFxName,name,0x28);
  DAT_10033547 = 0;
  if (_g_dwEffectsHeapSize == 0) {
    DAT_10033547 = 0;
    g_dwUseVoxFx = 0;
    return 0;
  }
  iVar1 = FUN_1000c0a0((int)(char)*name);
  if ((((iVar1 == 0x4f) && (iVar1 = FUN_1000c0a0((int)*(char *)((int)name + 1)), iVar1 == 0x46)) &&
      (iVar1 = FUN_1000c0a0((int)*(char *)((int)name + 2)), iVar1 == 0x46)) &&
     (*(char *)((int)name + 3) == '\0')) {
    g_dwUseVoxFx = 0;
    return 0;
  }
  g_dwUseVoxFx = ImFx_SelectPreset((uint)name);
  return g_dwUseVoxFx;
}

/* ---- 0x1000a1e0  StInitialize ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
   Original name StInitialize (the remaster's GrimFandango (Linux): aligned call in TrInitialize);
   was Im_TracksInit. */

undefined4 StInitialize(void)

{
  undefined4 *puVar1;
  
  puVar1 = &g_dwStreams;
  do {
    *puVar1 = 0;
    puVar1 = puVar1 + 0xc;
  } while ((int)puVar1 < ((unsigned)(uintptr_t)&DAT_10031f28));
  g_dwLastStreamLoaded = 0;
  return 0;
}

/* ---- 0x1000a300  StProcessStreams ---- */
/* Refills every streaming track (Im_RefillStreamTrack) Original name StProcessStreams (the
   remaster's GrimFandango (Linux): case 0x1b of ImSoundCall calls it where the v1.01 dispatcher
   calls the exported API that calls this function); was Im_ProcessStreamsImpl. */

undefined4 StProcessStreams(void)

{
  uint uVar1;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  uint *stream;
  uint *puVar5;
  uint *stream_00;
  
  stream = (uint *)0x0;
  ImWaveHalt();
  DpPredictStreams();
  puVar2 = &g_dwStreams;
  puVar5 = (uint *)0x0;
  do {
    stream_00 = puVar5;
    if ((((*puVar2 != 0) && (puVar2[0xb] == 0)) && (stream_00 = puVar2, puVar5 != (uint *)0x0)) &&
       (stream_00 = puVar5, stream == (uint *)0x0)) {
      stream = puVar2;
    }
    puVar2 = puVar2 + 0xc;
    puVar5 = stream_00;
  } while ((int)puVar2 < ((unsigned)(uintptr_t)&DAT_10031f28));
  if (stream_00 == (uint *)0x0) {
LAB_1000a408:
    if (stream == (uint *)0x0) goto LAB_1000a415;
  }
  else {
    if (stream == (uint *)0x0) {
      if (stream_00 != (uint *)0x0) {
        Stream_LoadData(stream_00);
        ImWaveProceed();
        return 0;
      }
      goto LAB_1000a408;
    }
    uVar3 = StGetValidSize((int)stream_00);
    uVar1 = stream_00[7];
    uVar4 = StGetValidSize((int)stream);
    if (uVar3 < uVar1) {
      if (stream[7] <= uVar4) {
        Stream_LoadData(stream_00);
        ImWaveProceed();
        return 0;
      }
      if (g_dwLastStreamLoaded == stream_00) {
        Stream_LoadData(stream_00);
        Stream_LoadData(stream);
        ImWaveProceed();
        return 0;
      }
      Stream_LoadData(stream);
      Stream_LoadData(stream_00);
      ImWaveProceed();
      return 0;
    }
    if ((stream[7] <= uVar4) && (g_dwLastStreamLoaded == stream_00)) {
      Stream_LoadData(stream_00);
      ImWaveProceed();
      return 0;
    }
  }
  Stream_LoadData(stream);
LAB_1000a415:
  ImWaveProceed();
  return 0;
}

/* ---- 0x1000a580  StGetValidSize ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
   Original name StGetValidSize (the remaster's GrimFandango (Linux): aligned call in PredictStream,
   StQueryStream, StReadData); was Im_FindTrack. */

int __cdecl StGetValidSize(int stream)

{
  int iVar1;
  
  iVar1 = *(int *)(stream + 0x24) - *(int *)(stream + 0x28);
  if (iVar1 < 0) {
    iVar1 = iVar1 + *(int *)(stream + 0x14);
  }
  return iVar1;
}

/* ---- 0x1000a5e0  StQueryStream ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
   Original name StQueryStream (the remaster's GrimFandango (Linux): aligned call in DpProcessTrack,
   TrQueryStream); was Im_QueryStreamTrack. */

undefined4 __cdecl
StQueryStream(int stream,undefined4 *outBufSize,undefined4 *outCriticalSize,int *outFreeSpace,
             undefined4 *outPaused)

{
  int iVar1;
  
  DpPredictStreams();
  *outBufSize = *(undefined4 *)(stream + 0x14);
  *outCriticalSize = *(undefined4 *)(stream + 0x1c);
  iVar1 = StGetValidSize(stream);
  *outFreeSpace = iVar1;
  *outPaused = *(undefined4 *)(stream + 0x2c);
  return 0;
}

/* ---- 0x1000a620  StFeedStream ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
   Original name StFeedStream (the remaster's GrimFandango (Linux): called by TrFeedStream at the
   same place, body similarity); was Im_FeedStreamTrack. */

undefined4 __cdecl StFeedStream(int stream,undefined4 *data,uint size,undefined4 paused)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 *puVar4;
  uint uVar5;
  undefined4 *puVar6;
  
  iVar1 = *(int *)(stream + 0x28) - *(int *)(stream + 0x24);
  if (iVar1 < 1) {
    iVar1 = iVar1 + *(int *)(stream + 0x14);
  }
  if (iVar1 + -4 < (int)size) {
    iVar1 = size - (iVar1 + -4);
    StEraseFromFront(stream,(iVar1 - iVar1 % 0xc) + 0xc);
  }
  if (0 < (int)size) {
    uVar3 = *(uint *)(stream + 0x14);
    do {
      uVar2 = uVar3 - *(int *)(stream + 0x24);
      if ((int)size < (int)uVar2) {
        uVar2 = size;
      }
      size = size - uVar2;
      puVar4 = data;
      puVar6 = (undefined4 *)(*(int *)(stream + 0x10) + *(int *)(stream + 0x24));
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
      data = (undefined4 *)((int)data + uVar2);
      uVar5 = *(int *)(stream + 0x24) + uVar2;
      uVar3 = *(uint *)(stream + 0x14);
      *(uint *)(stream + 4) = *(int *)(stream + 4) + uVar2;
      *(uint *)(stream + 0x24) = uVar5;
      if (uVar3 <= uVar5) {
        *(uint *)(stream + 0x24) = uVar5 - uVar3;
      }
    } while (0 < (int)size);
  }
  *(undefined4 *)(stream + 0x2c) = paused;
  return 0;
}

/* ---- 0x1000a6d0  Stream_LoadData ---- */
/* Refills the stream buffer of one track from its file. Drops the guard (Im_GuardLeave) around the
   blocking read and takes it again after: net 0 only when the caller holds the guard
   (Im_Scheduler_a300 does). Original name LoadData, written Stream_LoadData (the stream module; the
   bridge refuses the bare name) (the remaster's GrimFandango (Linux): aligned call in
   StProcessStreams); was Im_RefillStreamTrack. */

undefined4 __cdecl Stream_LoadData(uint *stream)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  if (stream[2] == 0) {
    uVar1 = FmSeek(*stream,0,2);
    stream[2] = uVar1;
  }
  iVar2 = stream[10] - stream[9];
  if (iVar2 < 1) {
    iVar2 = iVar2 + stream[5];
  }
  uVar1 = stream[6];
  if ((int)(iVar2 - 4U) <= (int)stream[6]) {
    uVar1 = iVar2 - 4U;
  }
  uVar3 = stream[2] - stream[1];
  if ((int)uVar3 <= (int)uVar1) {
    uVar1 = uVar3;
  }
  if ((int)uVar3 < 1) {
    stream[0xb] = 1;
  }
  if (0 < (int)uVar1) {
    while( true ) {
      uVar3 = uVar1;
      if ((int)(stream[5] - stream[9]) <= (int)uVar1) {
        uVar3 = stream[5] - stream[9];
      }
      uVar4 = FmSeek(*stream,stream[1],0);
      if (uVar4 != stream[1]) {
        stream[0xb] = 1;
        return 0;
      }
      g_dwBailFlag = 0;
      ImWaveProceed();
      uVar4 = FmRead(*stream,stream[4] + stream[9],uVar3);
      ImWaveHalt();
      if (g_dwBailFlag != 0) {
        return 0;
      }
      uVar1 = uVar1 - uVar4;
      stream[1] = stream[1] + uVar4;
      g_dwLastStreamLoaded = stream;
      uVar5 = stream[9] + uVar4;
      stream[9] = uVar5;
      if (stream[5] <= uVar5) {
        stream[9] = uVar5 - stream[5];
      }
      if (uVar4 != uVar3) break;
      if ((int)uVar1 < 1) {
        return 0;
      }
    }
    g_dwLastStreamLoaded = (uint *)0x0;
  }
  return 0;
}

/* ---- 0x1000a7e0  TrInitialize ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* DirectSound, mixer, dispatch and track tables Original name TrInitialize (the remaster's
   GrimFandango (Linux): aligned call in ImInitialize); was Im_InitSubsystems. */

undefined4 TrInitialize(void)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  g_dwTrackCount = g_dwImWaveMixCount;
  g_dwPauseTimer = 0;
  g_dwTrackList = 0;
  _DAT_10032308 = 0x5622;
  iVar2 = DwInitialize(0x5622,(undefined4 *)&g_aTrInitialize_waveDriverInfo);
  if (iVar2 != 0) {
    return 0xffffffff;
  }
  iVar2 = MxInitialize((undefined4 *)&g_aTrInitialize_waveDriverInfo);
  if (iVar2 != 0) {
    return 0xffffffff;
  }
  iVar2 = DpInitialize();
  if (iVar2 != 0) {
    return 0xffffffff;
  }
  iVar2 = StInitialize();
  if (iVar2 != 0) {
    return 0xffffffff;
  }
  iVar2 = 0;
  if (0 < g_dwTrackCount) {
    puVar4 = &DAT_10031f30;
    do {
      puVar4[-1] = 0;
      puVar4[-2] = 0;
      puVar3 = DpGetDp(iVar2);
      *puVar4 = puVar3;
      *puVar3 = puVar4 + -2;
      iVar1 = g_dwTrackCount;
      puVar4[1] = 0;
      puVar4 = puVar4 + 0xf;
      iVar2 = iVar2 + 1;
    } while (iVar2 < iVar1);
  }
  return 0;
}

/* ---- 0x1000a8a0  TrTerminate ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
   Original name TrTerminate (the remaster's GrimFandango (Linux): case 0x1 of ImSoundCall calls it
   where the v1.01 dispatcher calls the exported API that calls this function); was
   Im_ShutdownSubsystems. */

int TrTerminate(void)

{
  int iVar1;
  
  TrStopAllSounds();
  iVar1 = DwTerminate();
  if (iVar1 != 0) {
    return -1;
  }
  iVar1 = DpTerminate();
  if (iVar1 != 0) {
    return -1;
  }
  iVar1 = MxTerminate();
  return -(uint)(iVar1 != 0);
}

/* ---- 0x1000a8d0  TrPause ---- */
/* Unidentified function of stream tracks (Stream_LoadData and friends) - module name inferred
   Original name TrPause (the remaster's GrimFandango (Linux): the only unmatched callee of ImPause;
   1 matched neighbours agree, 0 disagree); was Im_PauseImpl. */

void TrPause(void)

{
  ImWaveHalt();
  g_dwPauseTimer = 1;
  ImWaveProceed();
  return;
}

/* ---- 0x1000a8f0  TrResume ---- */
/* Unidentified function of stream tracks (Stream_LoadData and friends) - module name inferred
   Original name TrResume (the remaster's GrimFandango (Linux): the only unmatched callee of
   ImResume; 1 matched neighbours agree, 0 disagree); was Im_ResumeImpl. */

void TrResume(void)

{
  ImWaveHalt();
  g_dwPauseTimer = 0;
  ImWaveProceed();
  return;
}

/* ---- 0x1000a910  TrSave ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
   Original name TrSave (the remaster's GrimFandango (Linux): aligned call in ImSave); was
   Im_SaveImpl. */

int __cdecl TrSave(undefined4 *buf,uint size)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  ImWaveHalt();
  iVar1 = DpSave(buf,size);
  if (iVar1 < 0) {
    ImWaveProceed();
    return iVar1;
  }
  if (size - iVar1 < 0x3c0) {
    ImWaveProceed();
    return -5;
  }
  puVar3 = &DAT_10031f28;
  puVar4 = (undefined4 *)((int)buf + iVar1);
  for (iVar2 = 0xf0; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  ImWaveProceed();
  return iVar1 + 0x3c0;
}

/* ---- 0x1000a970  TrRestore ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
   Original name TrRestore (the remaster's GrimFandango (Linux): aligned call in ImRestore); was
   Im_RestoreImpl. */

int __cdecl TrRestore(undefined4 *buf)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  int *node;
  undefined4 *puVar5;
  
  node = &DAT_10031f28;
  ImWaveHalt();
  g_dwTrackList = 0;
  iVar2 = DpBeginRestore(buf);
  iVar1 = g_dwTrackCount;
  puVar3 = (undefined4 *)((int)buf + iVar2);
  puVar5 = &DAT_10031f28;
  for (iVar4 = 0xf0; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar5 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar5 = puVar5 + 1;
  }
  iVar4 = 0;
  if (0 < iVar1) {
    do {
      *node = 0;
      node[1] = 0;
      puVar3 = DpGetDp(iVar4);
      node[2] = (int)puVar3;
      *puVar3 = node;
      if (node[3] != 0) {
        UtAddToList(&g_dwTrackList,node);
      }
      iVar4 = iVar4 + 1;
      node = node + 0xf;
    } while (iVar4 < g_dwTrackCount);
  }
  DpConcludeRestore();
  ImWaveProceed();
  return iVar2 + 0x3c0;
}

/* ---- 0x1000aa00  TrUpdateVols ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
   Original name TrUpdateVols (the remaster's GrimFandango (Linux): aligned call in GrSetGroupVol);
   was Im_UpdateGroupVolumes. */

undefined4 TrUpdateVols(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = g_dwTrackList;
  ImWaveHalt();
  for (; iVar1 != 0; iVar1 = *(int *)(iVar1 + 4)) {
    iVar2 = GrGetGroupEffVol(*(uint *)(iVar1 + 0x14));
    *(int *)(iVar1 + 0x20) = iVar2 * (*(int *)(iVar1 + 0x1c) + 1) >> 7;
  }
  ImWaveProceed();
  return 0;
}

/* ---- 0x1000aa40  TrIntHandler ---- */
/* Body of ImHeartbeat once its guards pass: refill the streams, advance the 20 ms mixing step for
   every playing track (FUN_10002570), retire finished ones. Original name TrIntHandler (the
   remaster's GrimFandango (Linux): aligned call in ImHeartbeat); was Im_HeartbeatBody. */

void TrIntHandler(void)

{
  int *piVar1;
  int *track;
  
  if (g_dwPauseTimer != 0) {
    if (g_dwPauseTimer + 1 < 3) {
      g_dwPauseTimer = g_dwPauseTimer + 1;
      return;
    }
    g_dwPauseTimer = 3;
  }
  do {
    DpPredictStreams();
    DwQuery(&g_dwTrIntHandler_outPtr,&g_dwTrIntHandler_outFramesNeeded,
            (int *)&g_dwTrIntHandler_outSampleRate);
    DAT_10032310 = g_dwTrIntHandler_outFramesNeeded;
    if (g_dwTrIntHandler_outFramesNeeded != 0) {
      MxBeginMix();
      track = g_dwTrackList;
      if (g_dwPauseTimer == 0) {
        while (track != (int *)0x0) {
          piVar1 = (int *)track[1];
          DpProcessTrack(track,g_dwTrIntHandler_outFramesNeeded,g_dwTrIntHandler_outSampleRate);
          track = piVar1;
        }
      }
      MxEndMix(g_dwTrIntHandler_outPtr,g_dwTrIntHandler_outFramesNeeded);
      DwQuery(&g_dwTrIntHandler_outPtr,&g_dwTrIntHandler_outFramesNeeded,(int *)0x0);
    }
  } while (DAT_10032310 != 0);
  return;
}

/* ---- 0x1000ab00  TrStartSound ---- */
/* Starts a track for a sound id: priority clamped 0..127, Im_AllocTrackOrSteal, fills the track
   (+0xc id, +0x18 priority, +0x1c volume 127, +0x24 pan 64, +0x30 = 0x100 ...), links it into the
   playing list g_dwTrackList. Returns 0, -1 (could not start) or -6 (no track). Original name
   TrStartSound (the remaster's GrimFandango (Linux): aligned call in ImStartSound, ImStartStream);
   was Im_StartSoundImpl. */

undefined4 __cdecl TrStartSound(int sound,int priority,uint group)

{
  int *node;
  int iVar1;
  
  if (priority < 0x80) {
    if (priority < 0) {
      priority = 0;
    }
  }
  else {
    priority = 0x7f;
  }
  node = Im_AllocTrackOrSteal(priority);
  if (node == (int *)0x0) {
    return 0xfffffffa;
  }
  ImWaveHalt();
  node[3] = sound;
  node[4] = 0;
  node[5] = 0;
  node[6] = priority;
  node[7] = 0x7f;
  iVar1 = GrGetGroupEffVol(0);
  node[8] = iVar1;
  node[9] = 0x40;
  node[10] = 0;
  node[0xb] = 0;
  node[0xc] = 0x100;
  node[0xd] = 0;
  node[0xe] = 0;
  iVar1 = DpStartSound((int)node,group);
  if (iVar1 != 0) {
    node[3] = 0;
    ImWaveProceed();
    return 0xffffffff;
  }
  UtAddToList(&g_dwTrackList,node);
  ImWaveProceed();
  return 0;
}

/* ---- 0x1000abb0  TrStopSound ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
   Original name TrStopSound (the remaster's GrimFandango (Linux): case 0x9 of ImSoundCall calls it
   where the v1.01 dispatcher calls the exported API that calls this function); was
   Im_StopSoundImpl. */

undefined4 __cdecl TrStopSound(int sound)

{
  int *piVar1;
  int *track;
  undefined4 uVar2;
  
  piVar1 = g_dwTrackList;
  uVar2 = 0xffffffff;
  ImWaveHalt();
  while (track = piVar1, track != (int *)0x0) {
    piVar1 = (int *)track[1];
    if (track[3] == sound) {
      TrStopTrack(track);
      uVar2 = 0;
    }
  }
  ImWaveProceed();
  return uVar2;
}

/* ---- 0x1000ac00  TrStopAllSounds ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
   Original name TrStopAllSounds (the remaster's GrimFandango (Linux): aligned call in
   ImStopAllSounds, TrTerminate); was Im_StopAllSoundsImpl. */

undefined4 TrStopAllSounds(void)

{
  int *piVar1;
  int *track;
  
  track = g_dwTrackList;
  while (track != (int *)0x0) {
    piVar1 = (int *)track[1];
    TrStopTrack(track);
    track = piVar1;
  }
  return 0;
}

/* ---- 0x1000ac20  TrGetNextSound ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
   Original name TrGetNextSound (the remaster's GrimFandango (Linux): case 0xb of ImSoundCall calls
   it where the v1.01 dispatcher calls the exported API that calls this function); was
   Im_GetNextSoundImpl. */

uint __cdecl TrGetNextSound(uint sound)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = g_dwTrackList;
  uVar3 = 0;
  ImWaveHalt();
  for (; iVar2 != 0; iVar2 = *(int *)(iVar2 + 4)) {
    uVar1 = *(uint *)(iVar2 + 0xc);
    if ((sound < uVar1) && ((uVar3 == 0 || (uVar1 < uVar3)))) {
      uVar3 = uVar1;
    }
  }
  ImWaveProceed();
  return uVar3;
}

/* ---- 0x1000ac60  TrQueryStream ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
   Original name TrQueryStream (the remaster's GrimFandango (Linux): case 0x1c of ImSoundCall calls
   it where the v1.01 dispatcher calls the exported API that calls this function); was
   Im_QueryStreamImpl. */

undefined4 __cdecl
TrQueryStream(int sound,undefined4 *outBufSize,undefined4 *outCriticalSize,int *outFreeSpace,
             undefined4 *outPaused)

{
  int iVar1;
  
  iVar1 = g_dwTrackList;
  ImWaveHalt();
  if (iVar1 == 0) {
    ImWaveProceed();
    return 0xffffffff;
  }
  while (((*(int *)(iVar1 + 0xc) == 0 || (*(int *)(iVar1 + 0xc) != sound)) ||
         (*(int *)(*(int *)(iVar1 + 8) + 0x81c) == 0))) {
    iVar1 = *(int *)(iVar1 + 4);
    if (iVar1 == 0) {
      ImWaveProceed();
      return 0xffffffff;
    }
  }
  StQueryStream(*(int *)(*(int *)(iVar1 + 8) + 0x81c),outBufSize,outCriticalSize,outFreeSpace,
                outPaused);
  ImWaveProceed();
  return 0;
}

/* ---- 0x1000ace0  TrFeedStream ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
   Original name TrFeedStream (the remaster's GrimFandango (Linux): case 0x1d of ImSoundCall calls
   it where the v1.01 dispatcher calls the exported API that calls this function); was
   Im_FeedStreamImpl. */

undefined4 __cdecl TrFeedStream(int sound,undefined4 *data,uint size,undefined4 paused)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = g_dwTrackList;
  ImWaveHalt();
  if (iVar2 == 0) {
    ImWaveProceed();
    return 0xffffffff;
  }
  while (((*(int *)(iVar2 + 0xc) == 0 || (*(int *)(iVar2 + 0xc) != sound)) ||
         (*(int *)(*(int *)(iVar2 + 8) + 0x81c) == 0))) {
    iVar2 = *(int *)(iVar2 + 4);
    if (iVar2 == 0) {
      ImWaveProceed();
      return 0xffffffff;
    }
  }
  ImWaveProceed();
  uVar1 = StFeedStream(*(int *)(*(int *)(iVar2 + 8) + 0x81c),data,size,paused);
  return uVar1;
}

/* ---- 0x1000ad50  TrStopTrack ---- */
/* Releases a track: dispatch, fades, stream Original name TrStopTrack (the remaster's GrimFandango
   (Linux): aligned call in DpProcessTrack, TrStopAllSounds, TrStopSound); was Im_FreeTrack. */

void __cdecl TrStopTrack(int *track)

{
  UtRemoveFromList(&g_dwTrackList,track);
  DpStopTrack((int)track);
  FdStopFade(track[3],-1);
  TgClearTrigger(track[3],(byte *)0xffffffff,-1);
  track[3] = 0;
  return;
}

/* ---- 0x1000ada0  TrSetParam ---- */
/* ImSetParam on a sound id. LEAK: with param 0x400 (group) and a value >= 0x10 it returns without
   Im_GuardLeave: the guard counter stays raised for good (ImStartSound with a group >= 16 reaches
   it too). No Lua script of the game passes such a group. Original name TrSetParam (the remaster's
   GrimFandango (Linux): case 0xc of ImSoundCall calls it where the v1.01 dispatcher calls the
   exported API that calls this function); was Im_SetParamImpl. */

undefined4 __cdecl TrSetParam(int sound,int param,uint value)

{
  int iVar1;
  int iVar2;
  
  iVar2 = g_dwTrackList;
  ImWaveHalt();
  if (iVar2 == 0) {
    ImWaveProceed();
    return 0xfffffffc;
  }
  while (*(int *)(iVar2 + 0xc) != sound) {
    iVar2 = *(int *)(iVar2 + 4);
    if (iVar2 == 0) {
      ImWaveProceed();
      return 0xfffffffc;
    }
  }
  if (param < 0x501) {
    if (param == 0x500) {
      if (value < 0x80) {
        *(uint *)(iVar2 + 0x18) = value;
        ImWaveProceed();
        return 0;
      }
      ImWaveProceed();
      return 0xfffffffb;
    }
    if (param == 0x400) {
      if (value < 0x10) {
        *(uint *)(iVar2 + 0x14) = value;
        iVar1 = GrGetGroupEffVol(value);
        *(int *)(iVar2 + 0x20) = iVar1 * (*(int *)(iVar2 + 0x1c) + 1) >> 7;
        ImWaveProceed();
        return 0;
      }
      return 0xfffffffb;
    }
  }
  else if (param < 0x701) {
    if (param == 0x700) {
      if (value < 0x80) {
        *(uint *)(iVar2 + 0x24) = value;
        ImWaveProceed();
        return 0;
      }
      ImWaveProceed();
      return 0xfffffffb;
    }
    if (param == 0x600) {
      if (value < 0x80) {
        *(uint *)(iVar2 + 0x1c) = value;
        iVar1 = GrGetGroupEffVol(*(uint *)(iVar2 + 0x14));
        *(int *)(iVar2 + 0x20) = (int)(iVar1 * (value + 1)) >> 7;
        ImWaveProceed();
        return 0;
      }
      ImWaveProceed();
      return 0xfffffffb;
    }
  }
  else if (param == 0x800) {
    if ((-0x2401 < (int)value) && ((int)value < 0x2401)) {
      *(uint *)(iVar2 + 0x28) = value;
      *(uint *)(iVar2 + 0x30) = *(int *)(iVar2 + 0x2c) * 0x100 + value;
      ImWaveProceed();
      return 0;
    }
  }
  else {
    if (param != 0x900) {
      if (param == 0xa00) {
        *(uint *)(iVar2 + 0x34) = value;
        ImWaveProceed();
        return 0;
      }
      ImWaveProceed();
      return 0xfffffffb;
    }
    if ((-1 < (int)value) && ((int)value < 0x1000)) {
      *(uint *)(iVar2 + 0x30) = value;
      ImWaveProceed();
      return 0;
    }
  }
  ImWaveProceed();
  return 0xfffffffb;
}

/* ---- 0x1000af50  TrGetParam ---- */
/* ImGetParam on a sound id: walks the list of playing tracks (g_dwTrackList, next at +4) whose +0xc
   equals the id. 0x100 PLAY_COUNT = number of such tracks; the other params read the first match
   (0x300 prio-ish +0x10, 0x400 +0x14, 0x500 +0x18, 0x600 volume +0x1c, 0x700 pan +0x24, 0x800
   +0x28, 0x900 +0x2c, 0xa00 +0x34, 0x1800/0x1900/0x1a00 stream info); no track: 0 for PLAY_COUNT,
   -4 for the rest, -1 for param 0. Original name TrGetParam (the remaster's GrimFandango (Linux):
   aligned call in ImGetParam); was Im_GetParamImpl. */

uint __cdecl TrGetParam(int sound,int param)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = 0;
  iVar1 = g_dwTrackList;
  do {
    if (iVar1 == 0) {
      if (param != 0x100) {
        uVar2 = 0xfffffffc;
      }
      return uVar2;
    }
    if (*(int *)(iVar1 + 0xc) == sound) {
      if (0x100 < param) {
        if (param < 0x301) {
          if (param == 0x300) {
            return *(uint *)(iVar1 + 0x10);
          }
          if (param == 0x200) {
            return 0xffffffff;
          }
        }
        else if (param < 0x501) {
          if (param == 0x500) {
            return *(uint *)(iVar1 + 0x18);
          }
          if (param == 0x400) {
            return *(uint *)(iVar1 + 0x14);
          }
        }
        else if (param < 0x701) {
          if (param == 0x700) {
            return *(uint *)(iVar1 + 0x24);
          }
          if (param == 0x600) {
            return *(uint *)(iVar1 + 0x1c);
          }
        }
        else if (param < 0x901) {
          if (param == 0x900) {
            return *(uint *)(iVar1 + 0x2c);
          }
          if (param == 0x800) {
            return *(uint *)(iVar1 + 0x28);
          }
        }
        else if (param < 0x1801) {
          if (param == 0x1800) {
            return (uint)(*(int *)(*(int *)(iVar1 + 8) + 0x81c) != 0);
          }
          if (param == 0xa00) {
            return *(uint *)(iVar1 + 0x34);
          }
        }
        else {
          if (param == 0x1900) {
            return *(uint *)(*(int *)(iVar1 + 8) + 0x820);
          }
          if (param == 0x1a00) {
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
      if (param != 0x100) {
        if (param == 0) {
          return 0xffffffff;
        }
        return 0xfffffffb;
      }
      uVar2 = uVar2 + 1;
    }
    iVar1 = *(int *)(iVar1 + 4);
  } while( true );
}

/* ---- 0x1000b0a0  TrSetHook ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
   Original name TrSetHook (the remaster's GrimFandango (Linux): case 0xf of ImSoundCall calls it
   where the v1.01 dispatcher calls the exported API that calls this function); was Im_SetHookImpl.
    */

undefined4 __cdecl TrSetHook(int sound,uint hook)

{
  int *piVar1;
  int iVar2;
  
  if (0x80 < hook) {
    return 0xfffffffb;
  }
  iVar2 = g_dwTrackList;
  if (g_dwTrackList == 0) {
    return 0xfffffffc;
  }
  do {
    if (*(int *)(iVar2 + 0xc) == sound) {
      *(uint *)(iVar2 + 0x38) = hook;
      return 0;
    }
    piVar1 = (int *)(iVar2 + 4);
    iVar2 = *piVar1;
  } while (*piVar1 != 0);
  return 0xfffffffc;
}

/* ---- 0x1000b0e0  TrGetHook ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
   Original name TrGetHook (the remaster's GrimFandango (Linux): case 0x10 of ImSoundCall calls it
   where the v1.01 dispatcher calls the exported API that calls this function); was Im_GetHookImpl.
    */

undefined4 __cdecl TrGetHook(int sound)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = g_dwTrackList;
  if (g_dwTrackList == 0) {
    return 0xfffffffc;
  }
  do {
    if (*(int *)(iVar2 + 0xc) == sound) {
      return *(undefined4 *)(iVar2 + 0x38);
    }
    piVar1 = (int *)(iVar2 + 4);
    iVar2 = *piVar1;
  } while (*piVar1 != 0);
  return 0xfffffffc;
}

/* ---- 0x1000b110  Im_AllocTrackOrSteal ---- */
/* Track pool (0x3c bytes each, g_dwTrackCount of them, first at 10031f28): a free track (+0xc == 0),
   else the lowest-priority playing track when its priority <= the new one (it is stopped,
   FUN_1000ad50), else NULL (the start fails with -6). */

int * __cdecl Im_AllocTrackOrSteal(int priority)

{
  int *piVar1;
  int iVar2;
  int *track;
  
  iVar2 = 0;
  piVar1 = &DAT_10031f28;
  if (0 < g_dwTrackCount) {
    do {
      if (piVar1[3] == 0) {
        return piVar1;
      }
      piVar1 = piVar1 + 0xf;
      iVar2 = iVar2 + 1;
    } while (iVar2 < g_dwTrackCount);
  }
  track = (int *)0x0;
  iVar2 = 0x7f;
  for (piVar1 = g_dwTrackList; piVar1 != (int *)0x0; piVar1 = (int *)piVar1[1]) {
    if (piVar1[6] <= iVar2) {
      iVar2 = piVar1[6];
      track = piVar1;
    }
  }
  if ((track != (int *)0x0) && (iVar2 <= priority)) {
    TrStopTrack(track);
    return track;
  }
  return (int *)0x0;
}

/* ---- 0x1000b170  TgInitialize ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
   Original name TgInitialize (the remaster's GrimFandango (Linux): aligned call in ImInitialize);
   was Im_TriggersInit. */

undefined4 TgInitialize(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &g_dwTrigs;
  for (iVar1 = 0x268; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = &DAT_10032cc0;
  for (iVar1 = 0x60; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  g_dwDefersOn = 0;
  g_dwMidProcessing = 0;
  return 0;
}

/* ---- 0x1000b1a0  TgSave ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
   Original name TgSave (the remaster's GrimFandango (Linux): aligned call in ImSave); was
   Im_TriggersSave. */

undefined4 __cdecl TgSave(undefined4 *buf,int size)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  if (size < 0xb20) {
    return 0xfffffffb;
  }
  puVar2 = &g_dwTrigs;
  puVar3 = buf;
  for (iVar1 = 0x268; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar2 = &DAT_10032cc0;
  puVar3 = buf + 0x268;
  for (iVar1 = 0x60; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  return 0xb20;
}

/* ---- 0x1000b1e0  TgRestore ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
   Original name TgRestore (the remaster's GrimFandango (Linux): aligned call in ImRestore); was
   Im_TriggersRestore. */

undefined4 __cdecl TgRestore(undefined4 *buf)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar2 = buf;
  puVar3 = &g_dwTrigs;
  for (iVar1 = 0x268; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar2 = buf + 0x268;
  puVar3 = &DAT_10032cc0;
  for (iVar1 = 0x60; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  g_dwDefersOn = 1;
  return 0xb20;
}

/* ---- 0x1000b220  TgSetTrigger ---- */
/* Unidentified function of stream tracks (Stream_LoadData and friends) - module name inferred
   Original name TgSetTrigger (the remaster's GrimFandango (Linux): the only unmatched callee of
   ImSetTrigger; 1 matched neighbours agree, 0 disagree); was Im_SetTriggerImpl. */

undefined4 __cdecl
TgSetTrigger(int sound,char *marker,int cmd,int p0,int p1,int p2,int p3,int p4,int p5,int p6,int p7,
            int p8,int p9)

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
  
  piVar6 = &g_dwTrigs;
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

/* ---- 0x1000b2e0  TgCheckTrigger ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
   Original name TgCheckTrigger (the remaster's GrimFandango (Linux): case 0x12 of ImSoundCall calls
   it where the v1.01 dispatcher calls the exported API that calls this function); was
   Im_CheckTriggerImpl. */

int __cdecl TgCheckTrigger(int sound,byte *marker,int opcode)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  byte *pbVar4;
  int *piVar5;
  bool bVar6;
  int local_8;
  int local_4;
  
  local_8 = 0;
  piVar5 = &g_dwTrigs;
  local_4 = 8;
  do {
    if ((*piVar5 != 0) && ((sound == -1 || (sound == *piVar5)))) {
      if (marker != (byte *)0xffffffff) {
        pbVar4 = (byte *)(piVar5 + 1);
        pbVar2 = marker;
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
      if ((opcode == -1) || (opcode == piVar5[0x41])) {
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

/* ---- 0x1000b380  TgClearTrigger ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
   Original name TgClearTrigger (the remaster's GrimFandango (Linux): aligned call in
   DpSwitchStream, ImClearTrigger, TrStopTrack); was Im_ClearTriggerImpl. */

undefined4 __cdecl TgClearTrigger(int sound,byte *marker,int opcode)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  byte *pbVar4;
  int *piVar5;
  bool bVar6;
  int local_4;
  
  piVar5 = &g_dwTrigs;
  local_4 = 8;
  do {
    if ((*piVar5 != 0) && ((sound == -1 || (sound == *piVar5)))) {
      if (marker != (byte *)0xffffffff) {
        pbVar4 = (byte *)(piVar5 + 1);
        pbVar2 = marker;
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
      if ((opcode == -1) || (opcode == piVar5[0x41])) {
        if (g_dwMidProcessing == 0) {
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

/* ---- 0x1000b430  TgProcessMarker ---- */
/* Matches a marker name against the trigger table and runs the stored commands Original name
   TgProcessMarker (the remaster's GrimFandango (Linux): the only unpaired user of midProcessing /
   trigs on both sides, same body (copies the marker text to a static, walks the 8 triggers,
   midProcessing count)); was Im_FireTriggers. */

undefined4 * __cdecl TgProcessMarker(int sound,char *marker)

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
  int *slot;
  bool bVar13;
  #define local_100 (*(char (*)[256])(_frame + (0x110 - 0x100)))
  
  uVar7 = 0xffffffff;
  puVar4 = (undefined4 *)0x0;
  pcVar10 = marker;
  do {
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    cVar1 = *pcVar10;
    pcVar10 = pcVar10 + 1;
  } while (cVar1 != '\0');
  if (~uVar7 - 1 < 0x100) {
    uVar7 = 0xffffffff;
    do {
      pcVar10 = marker;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pcVar10 = marker + 1;
      cVar1 = *marker;
      marker = pcVar10;
    } while (cVar1 != '\0');
    uVar7 = ~uVar7;
    iVar9 = 8;
    pcVar10 = pcVar10 + -uVar7;
    pcVar12 = (char *)&g_dwTgProcessMarker_textCopy;
    for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar12 = *(undefined4 *)pcVar10;
      pcVar10 = pcVar10 + 4;
      pcVar12 = pcVar12 + 4;
    }
    g_dwMidProcessing = (undefined4 *)((int)g_dwMidProcessing + 1);
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pcVar12 = *pcVar10;
      pcVar10 = pcVar10 + 1;
      pcVar12 = pcVar12 + 1;
    }
    slot = &g_dwTrigs;
    do {
      if ((*slot != 0) && (sound == *slot)) {
        pbVar11 = (byte *)(slot + 1);
        if ((char)slot[1] != '\0') {
          pbVar5 = (byte *)&g_dwTgProcessMarker_textCopy;
          do {
            bVar2 = *pbVar5;
            bVar13 = bVar2 < *pbVar11;
            if (bVar2 != *pbVar11) {
LAB_1000b4d7:
              iVar6 = (1 - (uint)bVar13) - (uint)(bVar13 != 0);
              goto LAB_1000b4dc;
            }
            if (bVar2 == 0) break;
            bVar2 = pbVar5[1];
            bVar13 = bVar2 < pbVar11[1];
            if (bVar2 != pbVar11[1]) goto LAB_1000b4d7;
            pbVar5 = pbVar5 + 2;
            pbVar11 = pbVar11 + 2;
          } while (bVar2 != 0);
          iVar6 = 0;
LAB_1000b4dc:
          if (iVar6 != 0) goto LAB_1000b52c;
        }
        iVar6 = 0;
        cVar1 = (char)g_dwTgProcessMarker_textCopy;
        while (cVar1 != '\0') {
          local_100[iVar6] = cVar1;
          iVar3 = iVar6 + 1;
          iVar6 = iVar6 + 1;
          cVar1 = *(char *)((int)&g_dwTgProcessMarker_textCopy + iVar3);
        }
        local_100[iVar6] = '\0';
        Im_RunTriggerCommand(slot,&g_dwTgProcessMarker_textCopy);
        iVar6 = 0;
        cVar1 = local_100[0];
        while (cVar1 != '\0') {
          *(char *)((int)&g_dwTgProcessMarker_textCopy + iVar6) = cVar1;
          iVar3 = iVar6 + 1;
          iVar6 = iVar6 + 1;
          cVar1 = local_100[iVar3];
        }
        *(undefined1 *)((int)&g_dwTgProcessMarker_textCopy + iVar6) = 0;
      }
LAB_1000b52c:
      slot = slot + 0x4d;
      iVar9 = iVar9 + -1;
    } while (iVar9 != 0);
    puVar4 = (undefined4 *)((int)g_dwMidProcessing + -1);
    g_dwMidProcessing = puVar4;
    if (puVar4 == (undefined4 *)0x0) {
      iVar9 = 8;
      puVar4 = &g_dwTrigs;
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


/* ---- 0x1000b570  TgDeferCommand ---- */
/* Unidentified function of stream tracks (Stream_LoadData and friends) - module name inferred
   Original name TgDeferCommand (the remaster's GrimFandango (Linux): the only unmatched callee of
   ImDeferCommand; 1 matched neighbours agree, 0 disagree); was Im_DeferCommandImpl. */

undefined4 __cdecl
TgDeferCommand(int time,int cmd,int p0,int p1,int p2,int p3,int p4,int p5,int p6,int p7,int p8,
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
      g_dwDefersOn = 1;
      return 0;
    }
    iVar2 = iVar2 + 1;
    piVar5 = piVar5 + 0xc;
  } while (iVar2 < 8);
  return 0xfffffffa;
}

/* ---- 0x1000b5e0  TgIntHandler ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
   Original name TgIntHandler (the remaster's GrimFandango (Linux): aligned call in ImHeartbeat);
   was Im_ProcessDeferred. */

void TgIntHandler(void)

{
  int iVar1;
  int iVar2;
  int *entry;
  
  entry = &DAT_10032cc0;
  if (g_dwDefersOn != 0) {
    g_dwDefersOn = 0;
    iVar2 = 8;
    do {
      if (*entry != 0) {
        iVar1 = *entry + -1;
        g_dwDefersOn = 1;
        *entry = iVar1;
        if (iVar1 == 0) {
          Im_RunDeferredCommand((int)entry);
        }
      }
      entry = entry + 0xc;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  return;
}

/* ---- 0x1000b630  TgGetPendCount ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
   Original name TgGetPendCount (the remaster's GrimFandango (Linux): aligned call in ImGetParam);
   was Im_GetTriggerParam. */

int __cdecl TgGetPendCount(int sound)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar1 = 0;
  piVar2 = &DAT_10032424;
  iVar3 = 8;
  do {
    if ((piVar2[-0x41] != 0) &&
       (((*piVar2 == 8 && (piVar2[1] == sound)) || ((*piVar2 == 0x1a && (piVar2[2] == sound)))))) {
      iVar1 = iVar1 + 1;
    }
    piVar2 = piVar2 + 0x4d;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  piVar2 = &DAT_10032cc4;
  iVar3 = 8;
  do {
    if ((piVar2[-1] != 0) &&
       (((*piVar2 == 8 && (piVar2[1] == sound)) || ((*piVar2 == 0x1a && (piVar2[2] == sound)))))) {
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

void __cdecl Im_RunTriggerCommand(undefined4 *slot,undefined4 marker)

{
  code *cmd;
  int a2;
  undefined4 uVar1;
  
  cmd = (code *)slot[0x41];
  *slot = 0;
  if (cmd == (code *)0x0) {
    if (DAT_100336a8 != (code *)0x0) {
      uVar1 = slot[0x4b];
      (*DAT_100336a8)(marker,uVar1,uVar1,uVar1,uVar1,uVar1,uVar1,uVar1,uVar1,uVar1,uVar1);
    }
    return;
  }
  a2 = slot[0x4b];
  if (cmd < (code *)0x1e) {
    ImSoundCall((uint)cmd,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2);
    return;
  }
  (*cmd)(marker);
  return;
}
#endif


/* ---- 0x1000b710  Im_RunDeferredCommand ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

void __cdecl Im_RunDeferredCommand(int entry)

{
  code *cmd;
  int a2;
  
  cmd = *(code **)(entry + 4);
  if (cmd == (code *)0x0) {
    if (DAT_100336a8 == (code *)0x0) {
      return;
    }
    a2 = *(int *)(entry + 0x2c);
    cmd = DAT_100336a8;
  }
  else {
    a2 = *(int *)(entry + 0x2c);
    if (cmd < (code *)0x1e) {
      ImSoundCall((uint)cmd,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2);
      return;
    }
  }
  (*cmd)(a2,a2,a2,a2,a2,a2,a2,a2,a2,a2);
  return;
}

/* ---- 0x1000bd50  Im_StrChr ---- */
/* not in the source: names/lib_replace.json (host): the system C runtime (msvcrt.dll) has it */


/* ---- 0x1000bd80  Im_MemCopy ---- */
/* not in the source: names/lib_replace.json (host): the system C runtime (msvcrt.dll) has it */


/* ---- 0x1000be80  Im_StrCmpNoCase ---- */
/* not in the source: names/lib_replace.json (host): the system C runtime (msvcrt.dll) has it */



/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern unsigned char grim_def_DAT_100152da[6] __asm__("_DAT_100152da");
extern unsigned char grim_def_DAT_10017050[8] __asm__("_DAT_10017050");
extern unsigned int grim_def_DAT_10017058 __asm__("_DAT_10017058");
extern unsigned char grim_def_DAT_1001705c[8] __asm__("_DAT_1001705c");
extern unsigned char grim_def_DAT_10017064[8] __asm__("_DAT_10017064");
extern unsigned char grim_def_DAT_1001706c[8] __asm__("_DAT_1001706c");
extern unsigned char grim_def_DAT_1001707c[8] __asm__("_DAT_1001707c");
extern unsigned char grim_def_DAT_10017084[4] __asm__("_DAT_10017084");
extern unsigned char grim_def_DAT_10017088[8] __asm__("_DAT_10017088");
extern unsigned char grim_def_DAT_10017090[8] __asm__("_DAT_10017090");
extern unsigned char grim_def_DAT_100170a0[8] __asm__("_DAT_100170a0");
extern unsigned char grim_def_DAT_100170a8[8] __asm__("_DAT_100170a8");
extern unsigned char grim_def_DAT_100170b0[8] __asm__("_DAT_100170b0");
extern unsigned char grim_def_DAT_100170b8[8] __asm__("_DAT_100170b8");
extern unsigned char grim_def_DAT_100170f0[20] __asm__("_DAT_100170f0");
extern unsigned char grim_def_DAT_1001ae4c[4] __asm__("_DAT_1001ae4c");
extern unsigned char grim_def_DAT_1001bbc4[4] __asm__("_DAT_1001bbc4");
extern unsigned char grim_def_DAT_1001e99c[28] __asm__("_DAT_1001e99c");
extern unsigned char grim_def_DAT_1001e9b8[8] __asm__("_DAT_1001e9b8");
extern unsigned char grim_def_DAT_10022140[128] __asm__("_DAT_10022140");
extern unsigned char grim_def_DAT_100221c0[11264] __asm__("_DAT_100221c0");
extern unsigned char grim_def_DAT_10024dc0[8] __asm__("_DAT_10024dc0");
extern unsigned char grim_def_DAT_1002d7f0[24] __asm__("_DAT_1002d7f0");
extern unsigned int grim_def_DAT_1002d814 __asm__("_DAT_1002d814");
extern unsigned char grim_def_DAT_1002d818[4] __asm__("_DAT_1002d818");
extern unsigned int grim_def_DAT_1002d820 __asm__("_DAT_1002d820");
extern unsigned int grim_def_DAT_1002d82c __asm__("_DAT_1002d82c");
extern unsigned char grim_def_DAT_1002d840[4] __asm__("_DAT_1002d840");
extern unsigned int grim_def_DAT_1002d844 __asm__("_DAT_1002d844");
extern unsigned int grim_def_DAT_1002d848 __asm__("_DAT_1002d848");
extern unsigned char grim_def_DAT_1002d850[4] __asm__("_DAT_1002d850");
extern unsigned char grim_def_DAT_1002d854[4] __asm__("_DAT_1002d854");
extern unsigned char grim_def_DAT_1002d880[608] __asm__("_DAT_1002d880");
extern unsigned char grim_def_DAT_1002dd14[4] __asm__("_DAT_1002dd14");
extern unsigned int grim_def_DAT_1002dd18 __asm__("_DAT_1002dd18");
extern unsigned char grim_def_DAT_1002dd1c[4] __asm__("_DAT_1002dd1c");
extern unsigned char grim_def_DAT_1002dd24[4] __asm__("_DAT_1002dd24");
extern unsigned char grim_def_DAT_1002dd28[4] __asm__("_DAT_1002dd28");
extern unsigned char grim_def_DAT_1002dd84[60] __asm__("_DAT_1002dd84");
extern unsigned char grim_def_DAT_1002ddc4[60] __asm__("_DAT_1002ddc4");
extern unsigned char grim_def_DAT_1002df28[8] __asm__("_DAT_1002df28");
extern unsigned char grim_def_DAT_1002df68[4] __asm__("_DAT_1002df68");
extern unsigned char grim_def_DAT_1002df6c[4] __asm__("_DAT_1002df6c");
extern unsigned char grim_def_DAT_1002df78[12] __asm__("_DAT_1002df78");
extern unsigned char grim_def_DAT_1002df84[728] __asm__("_DAT_1002df84");
extern unsigned char grim_def_DAT_1002e25c[168] __asm__("_DAT_1002e25c");
extern unsigned int grim_def_DAT_1002e304 __asm__("_DAT_1002e304");
extern unsigned char grim_def_DAT_1002e311[31] __asm__("_DAT_1002e311");
extern unsigned char grim_def_DAT_1002e330[8] __asm__("_DAT_1002e330");
extern unsigned char grim_def_DAT_1002e338[8] __asm__("_DAT_1002e338");
extern unsigned char grim_def_DAT_1002fbb8[24] __asm__("_DAT_1002fbb8");
extern unsigned char grim_def_DAT_100303a4[4] __asm__("_DAT_100303a4");
extern unsigned char grim_def_DAT_100303a8[4] __asm__("_DAT_100303a8");
extern unsigned char grim_def_DAT_100303ac[4] __asm__("_DAT_100303ac");
extern unsigned char grim_def_DAT_100303b0[4] __asm__("_DAT_100303b0");
extern unsigned char grim_def_DAT_100303b4[4] __asm__("_DAT_100303b4");
extern unsigned char grim_def_DAT_100303b8[4] __asm__("_DAT_100303b8");
extern unsigned char grim_def_DAT_100303bc[4] __asm__("_DAT_100303bc");
extern unsigned char grim_def_DAT_100303c0[4] __asm__("_DAT_100303c0");
extern unsigned char grim_def_DAT_100303c4[4] __asm__("_DAT_100303c4");
extern unsigned char grim_def_DAT_100303c8[4] __asm__("_DAT_100303c8");
extern unsigned char grim_def_DAT_100303cc[4] __asm__("_DAT_100303cc");
extern unsigned char grim_def_DAT_100303d0[4] __asm__("_DAT_100303d0");
extern unsigned char grim_def_DAT_10031554[4] __asm__("_DAT_10031554");
extern unsigned char grim_def_DAT_10031558[8] __asm__("_DAT_10031558");
extern unsigned char grim_def_DAT_10031e80[4] __asm__("_DAT_10031e80");
extern unsigned char grim_def_DAT_10031f28[8] __asm__("_DAT_10031f28");
extern unsigned char grim_def_DAT_10031f30[952] __asm__("_DAT_10031f30");
extern unsigned char grim_def_DAT_10032308[4] __asm__("_DAT_10032308");
extern unsigned int grim_def_DAT_10032310 __asm__("_DAT_10032310");
extern unsigned char grim_def_DAT_10032424[2204] __asm__("_DAT_10032424");
extern unsigned int grim_def_DAT_10032cc0 __asm__("_DAT_10032cc0");
extern unsigned char grim_def_DAT_10032cc4[380] __asm__("_DAT_10032cc4");
extern unsigned char grim_def_DAT_10032f48[8] __asm__("_DAT_10032f48");
extern unsigned char grim_def_DAT_10033568[312] __asm__("_DAT_10033568");
extern unsigned char grim_def_DAT_100336a8[4] __asm__("_DAT_100336a8");
extern unsigned char grim_def_PTR_100170ec[4] __asm__("_PTR_100170ec");
extern unsigned char grim_def_PTR_1002d830[4] __asm__("_PTR_1002d830");
extern unsigned char grim_def_PTR_1002d834[4] __asm__("_PTR_1002d834");
extern unsigned char grim_def_PTR_1002d838[4] __asm__("_PTR_1002d838");
extern unsigned int grim_def_UINT_1002dd20 __asm__("_UINT_1002dd20");
extern ImNameAlias grim_def_g_aImNameAlias[171] __asm__("_g_aImNameAlias");
extern ImMusicEntry grim_def_g_aImSeqTable[41] __asm__("_g_aImSeqTable");
extern ImMusicEntry grim_def_g_aImStateTable[181] __asm__("_g_aImStateTable");
extern unsigned char grim_def_g_aLipSfx1Data[2000] __asm__("_g_aLipSfx1Data");
extern unsigned char grim_def_g_aLipSfx2Data[2000] __asm__("_g_aLipSfx2Data");
extern unsigned char grim_def_g_aMxEndMix_wavHeader[44] __asm__("_g_aMxEndMix_wavHeader");
extern unsigned char grim_def_g_aTrInitialize_waveDriverInfo[16] __asm__("_g_aTrInitialize_waveDriverInfo");
extern char grim_def_g_abAdpcmIndexAdjust2[] __asm__("_g_abAdpcmIndexAdjust2");
extern char grim_def_g_abAdpcmIndexAdjust3[] __asm__("_g_abAdpcmIndexAdjust3");
extern char grim_def_g_abAdpcmIndexAdjust4[] __asm__("_g_abAdpcmIndexAdjust4");
extern char grim_def_g_abAdpcmIndexAdjust5[] __asm__("_g_abAdpcmIndexAdjust5");
extern char grim_def_g_abAdpcmIndexAdjust6[] __asm__("_g_abAdpcmIndexAdjust6");
extern char grim_def_g_abAdpcmIndexAdjust7[] __asm__("_g_abAdpcmIndexAdjust7");
extern unsigned char grim_def_g_abAdpcmStepBits[89] __asm__("_g_abAdpcmStepBits");
extern void *grim_def_g_apAdpcmIndexAdjust[8] __asm__("_g_apAdpcmIndexAdjust");
extern unsigned char grim_def_g_bLipStreamData[2000] __asm__("_g_bLipStreamData");
extern unsigned char grim_def_g_bPanTable[8] __asm__("_g_bPanTable");
extern char grim_def_g_bTrans_name __asm__("_g_bTrans_name");
extern int grim_def_g_dwCurrentCuePoint __asm__("_g_dwCurrentCuePoint");
extern int grim_def_g_dwCurrentSequence __asm__("_g_dwCurrentSequence");
extern unsigned int grim_def_g_dwCurrentState __asm__("_g_dwCurrentState");
extern unsigned int grim_def_g_dwCurrentWriteIndex __asm__("_g_dwCurrentWriteIndex");
extern unsigned int grim_def_g_dwDefersOn __asm__("_g_dwDefersOn");
extern unsigned char grim_def_g_dwDpProcessTrack_bufSize[4] __asm__("_g_dwDpProcessTrack_bufSize");
extern unsigned char grim_def_g_dwDpProcessTrack_critSize[4] __asm__("_g_dwDpProcessTrack_critSize");
extern unsigned char grim_def_g_dwDpProcessTrack_curLevel[4] __asm__("_g_dwDpProcessTrack_curLevel");
extern unsigned char grim_def_g_dwDpProcessTrack_pauseFlag[4] __asm__("_g_dwDpProcessTrack_pauseFlag");
extern unsigned char grim_def_g_dwFadeStartedFlag[8] __asm__("_g_dwFadeStartedFlag");
extern unsigned char grim_def_g_dwFades[32] __asm__("_g_dwFades");
extern unsigned int grim_def_g_dwFadesOn __asm__("_g_dwFadesOn");
extern unsigned char grim_def_g_dwGoToNextRegion_fadeSize[8] __asm__("_g_dwGoToNextRegion_fadeSize");
extern unsigned int grim_def_g_dwGroupEffVols __asm__("_g_dwGroupEffVols");
extern unsigned int grim_def_g_dwGroupVols __asm__("_g_dwGroupVols");
extern unsigned int grim_def_g_dwIRes_csInit __asm__("_g_dwIRes_csInit");
extern unsigned int grim_def_g_dwImWaveMixCount __asm__("_g_dwImWaveMixCount");
extern unsigned int grim_def_g_dwLargeFadeFlags __asm__("_g_dwLargeFadeFlags");
extern unsigned char grim_def_g_dwLipSfx1ID[4] __asm__("_g_dwLipSfx1ID");
extern unsigned char grim_def_g_dwLipSfx2ID[4] __asm__("_g_dwLipSfx2ID");
extern unsigned char grim_def_g_dwLipSfx3ID[4] __asm__("_g_dwLipSfx3ID");
extern unsigned char grim_def_g_dwLipStreamID[4] __asm__("_g_dwLipStreamID");
extern unsigned int grim_def_g_dwLocalMusic __asm__("_g_dwLocalMusic");
extern unsigned int grim_def_g_dwMidProcessing __asm__("_g_dwMidProcessing");
extern unsigned int grim_def_g_dwMixBufSize __asm__("_g_dwMixBufSize");
extern unsigned int grim_def_g_dwNextToAllocate __asm__("_g_dwNextToAllocate");
extern unsigned int grim_def_g_dwOutChannelCount __asm__("_g_dwOutChannelCount");
extern unsigned int grim_def_g_dwPauseTimer __asm__("_g_dwPauseTimer");
extern unsigned char grim_def_g_dwSoftLTable[4] __asm__("_g_dwSoftLTable");
extern unsigned char grim_def_g_dwTgProcessMarker_textCopy[256] __asm__("_g_dwTgProcessMarker_textCopy");
extern unsigned char grim_def_g_dwTimerCounter[4] __asm__("_g_dwTimerCounter");
extern unsigned int grim_def_g_dwTrIntHandler_outFramesNeeded __asm__("_g_dwTrIntHandler_outFramesNeeded");
extern unsigned char grim_def_g_dwTrIntHandler_outPtr[12] __asm__("_g_dwTrIntHandler_outPtr");
extern unsigned char grim_def_g_dwTrIntHandler_outSampleRate[8] __asm__("_g_dwTrIntHandler_outSampleRate");
extern int grim_def_g_dwTrackList __asm__("_g_dwTrackList");
extern unsigned char grim_def_g_dwTrigs[260] __asm__("_g_dwTrigs");
extern unsigned char grim_def_g_pMixBuf[4] __asm__("_g_pMixBuf");
extern short grim_def_g_wAdpcmStepTable[89] __asm__("_g_wAdpcmStepTable");
extern char grim_def_s_CALLBACK__1001e898[12] __asm__("_s_CALLBACK__1001e898");
extern char grim_def_s_C__grimsrc_libs_iMUSE_Dispatch_c_100170c0[44] __asm__("_s_C__grimsrc_libs_iMUSE_Dispatch_c_100170c0");
extern char grim_def_s_C__grimsrc_libs_iMUSE_Mixer_c_100172c8[32] __asm__("_s_C__grimsrc_libs_iMUSE_Mixer_c_100172c8");
extern char grim_def_s_C__grimsrc_libs_iMUSE_dsound_c_10017104[32] __asm__("_s_C__grimsrc_libs_iMUSE_dsound_c_10017104");
extern char grim_def_s_ERROR_script_already_initialized_1001e6b4[36] __asm__("_s_ERROR_script_already_initialized_1001e6b4");
extern char grim_def_s_ERROR_script_not_initialized____1001e6d8[32] __asm__("_s_ERROR_script_not_initialized____1001e6d8");
extern char grim_def_s_ERROR_unrecognized_opcode_in_scr_1001e68c[40] __asm__("_s_ERROR_unrecognized_opcode_in_scr_1001e68c");
extern char grim_def_s_ERR__bogus_attribute____1001e738[24] __asm__("_s_ERR__bogus_attribute____1001e738");
extern char grim_def_s_ERR__bogus_sequence____1001e720[24] __asm__("_s_ERR__bogus_sequence____1001e720");
extern char grim_def_s_ERR_callback_got_marker______end_1001e870[40] __asm__("_s_ERR_callback_got_marker______end_1001e870");
extern char grim_def_s_FADE__lu____1001e818[12] __asm__("_s_FADE__lu____1001e818");
extern char grim_def_s_HOOK__lu____1001e824[12] __asm__("_s_HOOK__lu____1001e824");
extern char grim_def_s_LIP__1001e994[8] __asm__("_s_LIP__1001e994");
extern char grim_def_s_MCMP_10017098[8] __asm__("_s_MCMP_10017098");
extern char grim_def_s_No_stream_sound____1001e7ac[20] __asm__("_s_No_stream_sound____1001e7ac");
extern char grim_def_s_SCRIPT_ERR__Unable_to_open_1001e830[28] __asm__("_s_SCRIPT_ERR__Unable_to_open_1001e830");
extern char grim_def_s_SCRIPT_ERR__bogus_trans_type____1001e768[32] __asm__("_s_SCRIPT_ERR__bogus_trans_type____1001e768");
extern char grim_def_s_SCRIPT_ERR__failed_start_stream__1001e788[36] __asm__("_s_SCRIPT_ERR__failed_start_stream__1001e788");
extern char grim_def_s_SCRIPT_ERR__save_buffer_too_smal_1001e6f8[40] __asm__("_s_SCRIPT_ERR__save_buffer_too_smal_1001e6f8");
extern char grim_def_s_Set_attr__lu_to__lu____1001e750[24] __asm__("_s_Set_attr__lu_to__lu____1001e750");
extern char grim_def_s_Trans_null____1001e860[16] __asm__("_s_Trans_null____1001e860");
extern char grim_def_s_VIMA_1001e9c0[16] __asm__("_s_VIMA_1001e9c0");
extern char grim_def_s__end_1001e858[8] __asm__("_s__end_1001e858");
extern char grim_def_s_and_PAN__lu____1001e7c0[16] __asm__("_s_and_PAN__lu____1001e7c0");
extern char grim_def_s_clear_1001e7f4[8] __asm__("_s_clear_1001e7f4");
extern char grim_def_s_exit2_1001e7fc[8] __asm__("_s_exit2_1001e7fc");
extern char grim_def_s_exit_1001e804[8] __asm__("_s_exit_1001e804");
extern char grim_def_s_fading_VOL__lu____1001e7d0[20] __asm__("_s_fading_VOL__lu____1001e7d0");
extern char grim_def_s_opening_1001e84c[12] __asm__("_s_opening_1001e84c");
extern char grim_def_s_set_pan__lu____1001e7e4[16] __asm__("_s_set_pan__lu____1001e7e4");
extern char grim_def_s_vol__lu____1001e80c[12] __asm__("_s_vol__lu____1001e80c");
/* 0x10015228, 178 bytes */ GRIM_DATA("10015228") short grim_def_g_wAdpcmStepTable[89] __asm__("_g_wAdpcmStepTable") = {
    7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 19, 21, 23, 25, 28, 31,
    34, 37, 41, 45, 50, 55, 60, 66, 73, 80, 88, 97, 107, 118, 130, 143,
    157, 173, 190, 209, 230, 253, 279, 307, 337, 371, 408, 449, 494, 544, 598, 658,
    724, 796, 876, 963, 1060, 1166, 1282, 1411, 1552, 1707, 1878, 2066, 2272, 2499, 2749, 3024,
    3327, 3660, 4026, 4428, 4871, 5358, 5894, 6484, 7132, 7845, 8630, 9493, 10442, 11487, 12635, 13899,
    15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794, 32767
};
/* 0x100152da, 6 bytes */ GRIM_DATA("10015228") unsigned char grim_def_DAT_100152da[6] __asm__("_DAT_100152da") = {0};
/* 0x100152e0, 184 bytes */ GRIM_DATA("100152e0") unsigned char grim_def_g_abAdpcmStepBits[89] __asm__("_g_abAdpcmStepBits") = {
    0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4,
    0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4,
    0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x5, 0x5, 0x5,
    0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x6, 0x6, 0x6, 0x6, 0x6,
    0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7,
    0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7
};
/* 0x10015339, 95 bytes: the rest of grim_def_g_abAdpcmStepBits's span */ GRIM_DATA("100152e0") static unsigned char g_abAdpcmStepBits__tail[95] __attribute__((used)) = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x0c, 0xac, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x0d, 0xac, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x0e, 0xac, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x6f, 0x12, 0x83, 0xc0, 0xca, 0x21, 0x09, 0x40, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xa0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xbf, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x40, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0x1f, 0x41
};
/* 0x10017030, 32 bytes */ GRIM_DATA("10017030") void *grim_def_g_apAdpcmIndexAdjust[8] __asm__("_g_apAdpcmIndexAdjust") = {
    0, 0, (void *)&grim_def_g_abAdpcmIndexAdjust2, (void *)&grim_def_g_abAdpcmIndexAdjust3,
    (void *)&grim_def_g_abAdpcmIndexAdjust4, (void *)&grim_def_g_abAdpcmIndexAdjust5, (void *)&grim_def_g_abAdpcmIndexAdjust6, (void *)&grim_def_g_abAdpcmIndexAdjust7
};
/* 0x10017050, 8 bytes */ GRIM_DATA("10017050") unsigned char grim_def_DAT_10017050[8] __asm__("_DAT_10017050") = { 0x53, 0x53, 0x4e, 0x44 };
/* 0x10017058, 4 bytes */ GRIM_DATA("10017058") unsigned int grim_def_DAT_10017058 __asm__("_DAT_10017058") = 0x46464941;
/* 0x1001705c, 8 bytes */ GRIM_DATA("1001705c") unsigned char grim_def_DAT_1001705c[8] __asm__("_DAT_1001705c") = { 0x43, 0x4f, 0x4d, 0x4d };
/* 0x10017064, 8 bytes */ GRIM_DATA("10017064") unsigned char grim_def_DAT_10017064[8] __asm__("_DAT_10017064") = { 0x46, 0x4f, 0x52, 0x4d };
/* 0x1001706c, 8 bytes */ GRIM_DATA("1001706c") unsigned char grim_def_DAT_1001706c[8] __asm__("_DAT_1001706c") = { 0x46, 0x52, 0x4d, 0x54 };
/* 0x1001707c, 8 bytes */ GRIM_DATA("1001707c") unsigned char grim_def_DAT_1001707c[8] __asm__("_DAT_1001707c") = { 0x64, 0x61, 0x74, 0x61 };
/* 0x10017084, 4 bytes */ GRIM_DATA("10017084") unsigned char grim_def_DAT_10017084[4] __asm__("_DAT_10017084") = { 0x57, 0x41, 0x56, 0x45 };
/* 0x10017088, 8 bytes */ GRIM_DATA("10017088") unsigned char grim_def_DAT_10017088[8] __asm__("_DAT_10017088") = { 0x66, 0x6d, 0x74, 0x20 };
/* 0x10017090, 8 bytes */ GRIM_DATA("10017090") unsigned char grim_def_DAT_10017090[8] __asm__("_DAT_10017090") = { 0x52, 0x49, 0x46, 0x46 };
/* 0x10017098, 8 bytes */ GRIM_DATA("10017098") char grim_def_s_MCMP_10017098[8] __asm__("_s_MCMP_10017098") = "MCMP";
/* 0x100170a0, 8 bytes */ /* loose */ unsigned char grim_def_DAT_100170a0[8] __asm__("_DAT_100170a0") = { 0x44, 0x41, 0x54, 0x41 };
/* 0x100170a8, 8 bytes */ /* loose */ unsigned char grim_def_DAT_100170a8[8] __asm__("_DAT_100170a8") = { 0x53, 0x54, 0x4f, 0x50 };
static unsigned char grim_anchor_100170b0[0] __attribute__((section(".data$grim_100170b0"), aligned(16), used));
static unsigned char grim_pad_100170b0[0] __attribute__((section(".data$grim_100170b0_"), aligned(4), used));
/* 0x100170b0, 8 bytes */ GRIM_DATA("100170b0z") unsigned char grim_def_DAT_100170b0[8] __asm__("_DAT_100170b0") = { 0x52, 0x45, 0x47, 0x4e };
/* 0x100170b8, 8 bytes */ GRIM_DATA("100170b8") unsigned char grim_def_DAT_100170b8[8] __asm__("_DAT_100170b8") = { 0x4d, 0x41, 0x50, 0x20 };
/* 0x100170c0, 44 bytes */ GRIM_DATA("100170c0") char grim_def_s_C__grimsrc_libs_iMUSE_Dispatch_c_100170c0[44] __asm__("_s_C__grimsrc_libs_iMUSE_Dispatch_c_100170c0") = "C:\\grimsrc\\libs\\iMUSE\\Dispatch.c\000\000\000\000\000\000\000\000\377\377\377\377";
/* 0x100170ec, 4 bytes */ GRIM_DATA("100170ec") unsigned char grim_def_PTR_100170ec[4] __asm__("_PTR_100170ec") = { 0xff, 0xff, 0xff, 0xff };
/* 0x100170f0, 20 bytes */ GRIM_DATA("100170f0") unsigned char grim_def_DAT_100170f0[20] __asm__("_DAT_100170f0") = { 0x01, 0x00, 0x02, 0x00, 0x22, 0x56, 0x00, 0x00, 0x88, 0x58, 0x01, 0x00, 0x04, 0x00, 0x10 };
/* 0x10017104, 32 bytes */ GRIM_DATA("10017104") char grim_def_s_C__grimsrc_libs_iMUSE_dsound_c_10017104[32] __asm__("_s_C__grimsrc_libs_iMUSE_dsound_c_10017104") = "C:\\grimsrc\\libs\\iMUSE\\dsound.c";
/* 0x100172c8, 32 bytes */ GRIM_DATA("100172c8") char grim_def_s_C__grimsrc_libs_iMUSE_Mixer_c_100172c8[32] __asm__("_s_C__grimsrc_libs_iMUSE_Mixer_c_100172c8") = "C:\\grimsrc\\libs\\iMUSE\\Mixer.c";
/* 0x100172e8, 15204 bytes */ GRIM_DATA("100172e8") ImMusicEntry grim_def_g_aImStateTable[181] __asm__("_g_aImStateTable") = {
    { .nId = 1000, .aName = "STATE_NULL", .nVolume = 127 },
    { .nId = 1999, .aName = "stateNoChange", .nVolume = 127 },
    { .aFilename = "1001 - Manny's Office", .nTransType = 3, .nId = 1001, .aName = "stateMO", .nVolume = 127 },
    { .aFilename = "1002 - Mr. Frustration", .nTransType = 3, .nId = 1002, .aName = "stateHA_INTLS", .nHookSlot = 3, .nHookLimit = 8, .nVolume = 20, .nPan = 50 },
    { .aFilename = "1002 - Mr. Frustration", .nTransType = 3, .nId = 1003, .aName = "stateHA_REVLS", .nHookSlot = 3, .nHookLimit = 8, .nVolume = 80, .nPan = 12 },
    { .aFilename = "1002 - Mr. Frustration", .nTransType = 3, .nId = 1004, .aName = "stateHA_ELVOS", .nHookSlot = 3, .nHookLimit = 8, .nVolume = 90, .nPan = 110 },
    { .aFilename = "1002 - Mr. Frustration", .nTransType = 3, .nId = 1005, .aName = "stateHA_MNYCU", .nHookSlot = 3, .nHookLimit = 8, .nVolume = 60, .nPan = 110 },
    { .aFilename = "1002 - Mr. Frustration", .nTransType = 3, .nId = 1006, .aName = "stateHA_EVACU", .nHookSlot = 3, .nHookLimit = 8, .nVolume = 80, .nPan = 64 },
    { .aFilename = "1002 - Mr. Frustration", .nTransType = 3, .nId = 1007, .aName = "stateHA_EVAWS", .nHookSlot = 3, .nHookLimit = 8, .nVolume = 60, .nPan = 60 },
    { .aFilename = "1008 - Domino's Office", .nTransType = 3, .nId = 1008, .aName = "stateDO", .nVolume = 127 },
    { .aFilename = "1009 - Copal's Office", .nTransType = 3, .nId = 1009, .aName = "stateCO", .nVolume = 127 },
    { .aFilename = "1010 - Ledge", .nTransType = 3, .nId = 1010, .aName = "stateLE", .nVolume = 127 },
    { .aFilename = "1011 - Roof", .nTransType = 3, .nId = 1011, .aName = "stateRF", .nVolume = 127 },
    { .aFilename = "1020 - Tube Room", .nTransType = 3, .nId = 1020, .aName = "stateTU", .nVolume = 127 },
    { .aFilename = "1021 - Brennis", .nTransType = 3, .nId = 1021, .aName = "stateTU_BRENNIS", .nVolume = 127 },
    { .aFilename = "1022 - Lobby", .nTransType = 3, .nId = 1022, .aName = "stateLO", .nVolume = 127 },
    { .aFilename = "1023 - Packing Room", .nTransType = 3, .nId = 1023, .aName = "statePK", .nVolume = 127 },
    { .aFilename = "1030 - Garage", .nTransType = 3, .nId = 1030, .aName = "stateGA", .nVolume = 127 },
    { .aFilename = "1031 - Glottis' Shop", .nTransType = 3, .nId = 1031, .aName = "stateGS", .nVolume = 127 },
    { .aFilename = "1030 - Garage", .nTransType = 3, .nId = 1032, .aName = "stateGS_JAIL", .nVolume = 127 },
    { .aFilename = "1040 - Festival Wet", .nTransType = 3, .nId = 1040, .aName = "stateAL", .nHookSlot = 21, .nHookLimit = 4, .nFade = 500, .nVolume = 60 },
    { .aFilename = "1041 - Festival Dry", .nTransType = 3, .nId = 1041, .aName = "stateFE", .nHookSlot = 21, .nHookLimit = 4, .nFade = 200, .nVolume = 127 },
    { .aFilename = "1041 - Festival Dry", .nTransType = 3, .nId = 1042, .aName = "stateST", .nHookSlot = 21, .nHookLimit = 4, .nFade = 200, .nVolume = 60 },
    { .aFilename = "1041 - Festival Dry", .nTransType = 3, .nId = 1043, .aName = "stateOS", .nHookSlot = 21, .nHookLimit = 4, .nFade = 200, .nVolume = 46 },
    { .aFilename = "1040 - Festival Wet", .nTransType = 3, .nId = 1044, .aName = "stateRP", .nHookSlot = 21, .nHookLimit = 4, .nFade = 200, .nVolume = 85 },
    { .aFilename = "1050 - Headquarters", .nTransType = 3, .nId = 1050, .aName = "stateHQ", .nVolume = 127 },
    { .aFilename = "1060 - Real World", .nTransType = 2, .nId = 1060, .aName = "stateLR", .nFade = 300, .nVolume = 80 },
    { .aFilename = "1070 - Stump Room", .nTransType = 2, .nId = 1070, .aName = "stateSM", .nVolume = 127 },
    { .aFilename = "1071 - Signpost Room", .nTransType = 2, .nId = 1071, .aName = "stateSG", .nHookLimit = 3, .nVolume = 127 },
    { .aFilename = "1072 - Navigation", .nTransType = 2, .nId = 1072, .aName = "stateNA", .nVolume = 127 },
    { .aFilename = "1071 - Signpost Room", .nTransType = 2, .nId = 1073, .aName = "stateNA_SOLVED", .nHookLimit = 3, .nVolume = 127 },
    { .aFilename = "1074 - Bone Wagon", .nTransType = 2, .nId = 1074, .aName = "stateOO_BONE", .nVolume = 127 },
    { .aFilename = "1075 - Spider's Eye", .nTransType = 2, .nId = 1075, .aName = "stateSP_ENTLA", .nVolume = 127 },
    { .aFilename = "1076 - Spider Room", .nTransType = 2, .nId = 1076, .aName = "stateSP_WEBWS", .nVolume = 127 },
    { .aFilename = "1077 - Tree Pump Amb", .nTransType = 2, .nId = 1077, .aName = "stateTR_PMPWS", .nVolume = 127 },
    { .aFilename = "1078 - Tree Pump", .nTransType = 2, .nId = 1078, .aName = "stateTR_ESTHA", .nVolume = 127 },
    { .aFilename = "1071 - Signpost Room", .nTransType = 2, .nId = 1079, .aName = "stateTR_SOLVED", .nHookLimit = 3, .nVolume = 127 },
    { .aFilename = "1080 - Beaver Room Lbby", .nTransType = 2, .nId = 1080, .aName = "stateLB", .nVolume = 127 },
    { .aFilename = "1081 - Beaver Dam", .nTransType = 2, .nId = 1081, .aName = "stateBD", .nVolume = 127 },
    { .aFilename = "1083 - Beaver Room", .nTransType = 2, .nId = 1082, .aName = "stateBD_SOLVED", .nVolume = 127 },
    { .aFilename = "1083 - Beaver Room", .nTransType = 2, .nId = 1083, .aName = "stateBV", .nVolume = 127 },
    { .aFilename = "1084 - Foggy Cactus", .nTransType = 2, .nId = 1084, .aName = "stateFC", .nVolume = 80 },
    { .aFilename = "1085 - Rubamat Exterior", .nTransType = 2, .nId = 1085, .aName = "stateRE", .nVolume = 105 },
    { .aFilename = "1087 - Blue Hector", .nTransType = 2, .nId = 1086, .aName = "stateRI", .nHookLimit = 4, .nVolume = 80, .nPan = 30 },
    { .aFilename = "1109 - Cafe Exterior", .nTransType = 2, .nId = 1100, .aName = "stateCB", .nVolume = 127 },
    { .aFilename = "1101 - Cafe Office", .nTransType = 3, .nId = 1101, .aName = "stateCF", .nHookSlot = 45, .nHookLimit = 5, .nFade = 400, .nVolume = 60 },
    { .aFilename = "1102 - Cafe Intercom", .nTransType = 3, .nId = 1102, .aName = "stateCF_INTRCM", .nHookSlot = 45, .nFade = 400, .nVolume = 127 },
    { .aFilename = "1103 - Coat Check", .nTransType = 3, .nId = 1103, .aName = "stateCC", .nHookSlot = 49, .nHookLimit = 4, .nFade = 400, .nVolume = 60, .nPan = 100 },
    { .aFilename = "1104 - Lupe", .nTransType = 2, .nId = 1104, .aName = "stateCC_LUPE", .nFade = 300, .nVolume = 127 },
    { .aFilename = "1106 - Glottis Noodle", .nTransType = 3, .nId = 1105, .aName = "stateCI", .nHookSlot = 49, .nHookLimit = 4, .nFade = 400, .nVolume = 127, .nPan = 75 },
    { .aFilename = "1106 - Glottis Noodle", .nTransType = 3, .nId = 1106, .aName = "stateCI_NOODLE", .nHookSlot = 49, .nHookLimit = 4, .nFade = 400, .nVolume = 127, .nPan = 75 },
    { .aFilename = "1106 - Glottis Noodle", .nTransType = 3, .nId = 1190, .aName = "stateCI_WIDHA", .nHookSlot = 49, .nHookLimit = 4, .nFade = 400, .nVolume = 80, .nPan = 45 },
    { .aFilename = "1106 - Glottis Noodle", .nTransType = 3, .nId = 1191, .aName = "stateCI_BARWS", .nHookSlot = 49, .nHookLimit = 4, .nFade = 400, .nVolume = 127, .nPan = 127 },
    { .aFilename = "1101 - Cafe Office", .nTransType = 3, .nId = 1107, .aName = "stateCI_EMPTY", .nHookSlot = 45, .nHookLimit = 5, .nFade = 400, .nVolume = 127 },
    { .aFilename = "1108 - Casino Interior", .nTransType = 3, .nId = 1108, .aName = "stateCN", .nHookSlot = 45, .nHookLimit = 6, .nFade = 400, .nVolume = 127 },
    { .aFilename = "1109 - Cafe Exterior", .nTransType = 2, .nId = 1109, .aName = "stateCE", .nFade = 400, .nVolume = 127 },
    { .aFilename = "1110 - Cafe Ledge", .nTransType = 2, .nId = 1110, .aName = "stateCL", .nFade = 400, .nVolume = 105 },
    { .aFilename = "1108 - Casino Interior", .nTransType = 3, .nId = 1111, .aName = "stateCN_QUIET", .nFade = 400, .nVolume = 60 },
    { .aFilename = "1112 - Rusty Sans Vox", .nTransType = 2, .nId = 1112, .aName = "stateCI_SONG", .nFade = 400, .nVolume = 127, .nPan = 68 },
    { .aFilename = "1120 - Elevator Station", .nTransType = 2, .nId = 1120, .aName = "stateEV", .nVolume = 127 },
    { .aFilename = "1122 - Blue Exterior", .nTransType = 3, .nId = 1121, .aName = "stateBW", .nFade = 400, .nVolume = 127 },
    { .aFilename = "1122 - Blue Exterior", .nTransType = 3, .nId = 1122, .aName = "stateBE", .nFade = 400, .nVolume = 127 },
    { .aFilename = "1123 - Blue Casket Ins", .nTransType = 2, .nId = 1123, .aName = "stateBI", .nHookLimit = 4, .nFade = 700, .nVolume = 127 },
    { .aFilename = "1124 - Blue Casket Amb", .nTransType = 2, .nId = 1124, .aName = "stateBI_POE", .nVolume = 127 },
    { .aFilename = "1125 - Smooth Hector", .nTransType = 2, .nId = 1125, .aName = "stateBK", .nHookLimit = 4, .nVolume = 80, .nPan = 75 },
    { .aFilename = "1122 - Blue Exterior", .nTransType = 3, .nId = 1126, .aName = "stateHB", .nFade = 400, .nVolume = 127 },
    { .aFilename = "1127 - Limbo Dock", .nTransType = 3, .nId = 1127, .aName = "stateLM", .nHookSlot = 66, .nVolume = 127 },
    { .aFilename = "1128 - Limbo Talk", .nTransType = 2, .nId = 1128, .aName = "stateLM_TALK", .nFade = 400, .nVolume = 127 },
    { .aFilename = "1129 - Limbo Poem", .nTransType = 3, .nId = 1129, .aName = "stateLM_POEM", .nHookSlot = 66, .nVolume = 127 },
    { .aFilename = "1130 - Dry Dock", .nTransType = 2, .nId = 1130, .aName = "stateDD", .nFade = 400, .nVolume = 127 },
    { .aFilename = "1131 - Dry Dock Strike", .nTransType = 2, .nId = 1131, .aName = "stateDD_STRIKE", .nFade = 400, .nVolume = 127 },
    { .aFilename = "1132 - Lighthouse Ext", .nTransType = 2, .nId = 1132, .aName = "stateLX", .nVolume = 127 },
    { .aFilename = "1133 - Lola's Last", .nTransType = 2, .nId = 1133, .aName = "stateLX_LOLA", .nVolume = 127 },
    { .aFilename = "1140 - Police Station", .nTransType = 3, .nId = 1140, .aName = "statePC", .nVolume = 127 },
    { .aFilename = "1141 - Police Interior", .nTransType = 2, .nId = 1141, .aName = "statePI", .nVolume = 105 },
    { .aFilename = "1141 - Police Interior", .nTransType = 2, .nId = 1142, .aName = "statePI_MALLOY", .nVolume = 105 },
    { .aFilename = "1143 - Morgue", .nTransType = 2, .nId = 1143, .aName = "stateMG", .nVolume = 105 },
    { .aFilename = "1140 - Police Station", .nTransType = 3, .nId = 1144, .aName = "stateBP", .nVolume = 105 },
    { .aFilename = "1145 - Bridge Blimp", .nTransType = 2, .nId = 1145, .aName = "stateBB", .nVolume = 127 },
    { .aFilename = "1146 - LOL Security Ext", .nTransType = 2, .nId = 1146, .aName = "stateGT", .nVolume = 80 },
    { .aFilename = "1147 - LOL Security Int", .nTransType = 2, .nId = 1147, .aName = "stateSL", .nVolume = 127 },
    { .aFilename = "1148 - Carla's Life", .nTransType = 2, .nId = 1148, .aName = "stateSL_TALK", .nVolume = 127 },
    { .aFilename = "1149 - Bomb", .nTransType = 2, .nId = 1149, .aName = "stateSL_BOMB", .nFade = 400, .nVolume = 127 },
    { .aFilename = "1152 - Track Stairs", .nTransType = 3, .nId = 1150, .aName = "stateTB", .nHookSlot = 83, .nVolume = 105 },
    { .aFilename = "1152 - Track Stairs", .nTransType = 3, .nId = 1151, .aName = "stateTW", .nHookSlot = 83, .nVolume = 105 },
    { .aFilename = "1152 - Track Stairs", .nTransType = 3, .nId = 1152, .aName = "stateTS", .nHookSlot = 83, .nVolume = 105 },
    { .aFilename = "1153 - Track Base", .nTransType = 2, .nId = 1153, .aName = "stateTX", .nFade = 400, .nVolume = 127 },
    { .aFilename = "1154 - Kitty Hall", .nTransType = 2, .nId = 1154, .aName = "stateKH", .nVolume = 127 },
    { .aFilename = "1155 - Sanspoof", .nTransType = 2, .nId = 1155, .aName = "stateKH_SANS", .nVolume = 127 },
    { .aFilename = "1156 - Kitty Stables", .nTransType = 2, .nId = 1156, .aName = "stateKS", .nVolume = 127 },
    { .aFilename = "1160 - High Roller Hall", .nTransType = 2, .nId = 1160, .aName = "stateHH", .nVolume = 127 },
    { .aFilename = "1161 - High Roller Lnge", .nTransType = 3, .nId = 1161, .aName = "stateHL", .nFade = 400, .nVolume = 127 },
    { .aFilename = "1162 - Glottis Gambling", .nTransType = 2, .nId = 1162, .aName = "stateHL_GLOT", .nVolume = 127 },
    { .aFilename = "1163 - Max's Office", .nTransType = 3, .nId = 1163, .aName = "stateMX", .nFade = 400, .nVolume = 127 },
    { .aFilename = "1125 - Hector Steps Out", .nTransType = 3, .nId = 1164, .aName = "stateHK", .nHookSlot = 94, .nHookLimit = 4, .nFade = 200, .nVolume = 127, .nPan = 80 },
    { .aFilename = "1125 - Hector Steps Out", .nTransType = 3, .nId = 1165, .aName = "stateHP", .nHookSlot = 94, .nHookLimit = 4, .nFade = 200, .nVolume = 20, .nPan = 64 },
    { .aFilename = "1125 - Hector Steps Out", .nTransType = 3, .nId = 1166, .aName = "stateHE", .nHookSlot = 94, .nHookLimit = 4, .nFade = 200, .nVolume = 127, .nPan = 10 },
    { .aFilename = "1167 - Dillopede Elev", .nTransType = 3, .nId = 1167, .aName = "stateDE", .nVolume = 127 },
    { .aFilename = "1167 - Dillopede Elev", .nTransType = 3, .nId = 1168, .aName = "stateDH", .nVolume = 127 },
    { .aFilename = "1167 - Dillopede Elev", .nTransType = 3, .nId = 1169, .aName = "stateWC", .nVolume = 127 },
    { .aFilename = "1170 - Extendo Bridge", .nTransType = 3, .nId = 1170, .aName = "stateXB", .nFade = 400, .nVolume = 105 },
    { .aFilename = "1170 - Extendo Bridge", .nTransType = 3, .nId = 1171, .aName = "stateSD", .nFade = 400, .nVolume = 105 },
    { .aFilename = "1170 - Extendo Bridge", .nTransType = 3, .nId = 1172, .aName = "stateSE", .nFade = 400, .nVolume = 105 },
    { .aFilename = "1173 - Scrimshaw Int", .nTransType = 2, .nId = 1173, .aName = "stateSI", .nFade = 400, .nVolume = 127 },
    { .aFilename = "1174 - Scrim Sleep", .nTransType = 2, .nId = 1174, .aName = "stateSI_SLEEP", .nFade = 400, .nVolume = 127 },
    { .aFilename = "1180 - Note to Manny", .nTransType = 2, .nId = 1180, .aName = "stateNT", .nVolume = 72 },
    { .aFilename = "1155 - Sanspoof", .nTransType = 2, .nId = 1181, .aName = "statePF", .nVolume = 127 },
    { .aFilename = "1201 - Lola Zapata", .nTransType = 2, .nId = 1201, .aName = "stateLZ", .nVolume = 127 },
    { .aFilename = "1202 - Inside The Lola", .nTransType = 2, .nId = 1202, .aName = "stateIL", .nVolume = 127 },
    { .aFilename = "1203 - Engine Room", .nTransType = 2, .nId = 1203, .aName = "stateEI", .nVolume = 127 },
    { .aFilename = "1204 - Porthole", .nTransType = 2, .nId = 1204, .aName = "stateDP", .nVolume = 127 },
    { .aFilename = "1204 - Porthole", .nTransType = 2, .nId = 1205, .aName = "stateOP", .nVolume = 127 },
    { .aFilename = "1210 - Sunken Lola", .nTransType = 2, .nId = 1210, .aName = "stateSU", .nVolume = 127 },
    { .aFilename = "1211 - Pearl Crater Sub", .nTransType = 2, .nId = 1211, .aName = "statePS", .nVolume = 127 },
    { .aFilename = "1220 - Miner's Room", .nTransType = 3, .nId = 1220, .aName = "stateMN", .nVolume = 127 },
    { .aFilename = "1220 - Miner's Room", .nTransType = 3, .nId = 1221, .aName = "stateMN_CHEPITO", .nVolume = 127 },
    { .aFilename = "1222 - Exterior Airlock", .nTransType = 2, .nId = 1222, .aName = "stateEA", .nVolume = 127 },
    { .aFilename = "1223 - Factory Hub", .nTransType = 2, .nId = 1223, .aName = "stateFH", .nHookLimit = 4, .nVolume = 127 },
    { .aFilename = "1224 - Foreman's Office", .nTransType = 2, .nId = 1224, .aName = "stateFO", .nVolume = 127 },
    { .aFilename = "1230 - Vault Door", .nTransType = 2, .nId = 1230, .aName = "stateVD", .nVolume = 127 },
    { .aFilename = "1231 - Outer Vault", .nTransType = 2, .nId = 1231, .aName = "stateVO", .nVolume = 127 },
    { .aFilename = "1232 - Inner Vault", .nTransType = 2, .nId = 1232, .aName = "stateVI", .nVolume = 127 },
    { .aFilename = "1233 - Ashtray Room", .nTransType = 2, .nId = 1233, .aName = "stateAR", .nVolume = 127 },
    { .aFilename = "1234 - Ashtray Scary", .nTransType = 2, .nId = 1234, .aName = "stateAR_SCARY", .nVolume = 127 },
    { .aFilename = "1235 - Ashtray Pensive", .nTransType = 2, .nId = 1235, .aName = "stateAR_PENSV", .nVolume = 127 },
    { .aFilename = "1236 - Domino's Room", .nTransType = 2, .nId = 1236, .aName = "stateDR", .nVolume = 127 },
    { .aFilename = "1240 - Conveyor Under", .nTransType = 3, .nId = 1240, .aName = "stateCY", .nHookLimit = 4, .nVolume = 127 },
    { .aFilename = "1240 - Conveyor Under", .nTransType = 3, .nId = 1241, .aName = "stateCW", .nVolume = 127 },
    { .aFilename = "1241 - Crane Intro", .nTransType = 2, .nId = 1242, .aName = "stateCV", .nVolume = 127 },
    { .aFilename = "1243 - Anchor Room", .nTransType = 3, .nId = 1243, .aName = "stateAC", .nVolume = 127 },
    { .aFilename = "1244 - Glottis Hanging", .nTransType = 2, .nId = 1244, .aName = "stateGH", .nVolume = 127 },
    { .aFilename = "1245 - End of the World", .nTransType = 2, .nId = 1245, .aName = "stateEW", .nVolume = 127 },
    { .aFilename = "1246 - End World Later", .nTransType = 2, .nId = 1246, .aName = "stateEW_LATER", .nVolume = 127 },
    { .aFilename = "1241 - Crane Intro", .nTransType = 2, .nId = 1247, .aName = "stateCU", .nVolume = 127 },
    { .aFilename = "1250 - Upper Beach", .nTransType = 3, .nId = 1250, .aName = "stateBU", .nVolume = 127 },
    { .aFilename = "1250 - Upper Beach", .nTransType = 3, .nId = 1251, .aName = "stateBL", .nVolume = 127 },
    { .aFilename = "1252 - Lower Beach Boat", .nTransType = 3, .nId = 1252, .aName = "stateBL_BOAT", .nVolume = 127 },
    { .aFilename = "1253 - Lamancha Sub", .nTransType = 2, .nId = 1253, .aName = "stateLU", .nVolume = 127 },
    { .aFilename = "1254 - Crane Later", .nTransType = 2, .nId = 1254, .aName = "stateCUV_LATER", .nVolume = 127 },
    { .aFilename = "1301 - Temple Gate", .nTransType = 3, .nId = 1301, .aName = "stateTG", .nVolume = 127 },
    { .aFilename = "1301 - Temple Gate", .nTransType = 3, .nId = 1302, .aName = "stateBS", .nVolume = 127 },
    { .aFilename = "1303 - Truck Depot", .nTransType = 2, .nId = 1303, .aName = "stateTD", .nVolume = 105 },
    { .aFilename = "1306 - Mayan Train Pad", .nTransType = 3, .nId = 1306, .aName = "stateMT_CHEPITO", .nHookSlot = 143, .nVolume = 127 },
    { .aFilename = "1304 - Mayan Train Sta", .nTransType = 3, .nId = 1304, .aName = "stateMT", .nHookSlot = 143, .nVolume = 127 },
    { .aFilename = "1305 - Mayan Workshop", .nTransType = 2, .nId = 1305, .aName = "stateMY", .nVolume = 127 },
    { .aFilename = "1307 - Mechanic's Kitch", .nTransType = 2, .nId = 1307, .aName = "stateMK", .nHookLimit = 4, .nVolume = 40, .nPan = 64 },
    { .aFilename = "1310 - Jello Bomb", .nTransType = 3, .nId = 1310, .aName = "stateJB", .nVolume = 127 },
    { .aFilename = "1310 - Jello Bomb", .nTransType = 3, .nId = 1311, .aName = "stateXB_YEAR4", .nVolume = 127 },
    { .aFilename = "1125 - Smooth Hector", .nTransType = 3, .nId = 1312, .aName = "stateBI_CLBYR4", .nHookSlot = 150, .nHookLimit = 4, .nFade = 200, .nVolume = 20, .nPan = 64 },
    { .aFilename = "1125 - Smooth Hector", .nTransType = 3, .nId = 1313, .aName = "stateBI_KITYR4", .nHookSlot = 150, .nHookLimit = 4, .nFade = 200, .nVolume = 50, .nPan = 32 },
    { .aFilename = "1125 - Smooth Hector", .nTransType = 3, .nId = 1314, .aName = "stateBK_YR4", .nHookSlot = 150, .nHookLimit = 4, .nFade = 200, .nVolume = 105, .nPan = 75 },
    { .aFilename = "1122 - Blue Exterior", .nTransType = 3, .nId = 1315, .aName = "stateHB_YR4", .nVolume = 127 },
    { .aFilename = "1122 - Blue Exterior", .nTransType = 3, .nId = 1316, .aName = "stateBW_YR4", .nVolume = 127 },
    { .aFilename = "1122 - Blue Exterior", .nTransType = 3, .nId = 1317, .aName = "stateBE_YR4", .nVolume = 127 },
    { .aFilename = "1332 - Hector's Foyer", .nTransType = 3, .nId = 1318, .aName = "stateHN", .nVolume = 127 },
    { .aFilename = "1319 - Florist Video", .nTransType = 2, .nId = 1319, .aName = "stateFVID", .nVolume = 127 },
    { .aFilename = "1320 - New LSA HQ", .nTransType = 2, .nId = 1320, .aName = "stateNQ", .nVolume = 127 },
    { .aFilename = "1321 - LSA Sewer", .nTransType = 3, .nId = 1321, .aName = "stateLW", .nVolume = 127 },
    { .aFilename = "1321 - LSA Sewer", .nTransType = 3, .nId = 1322, .aName = "stateSH", .nVolume = 127 },
    { .aFilename = "1323 - Sewer Maze", .nTransType = 3, .nId = 1323, .aName = "stateZW", .nHookLimit = 2, .nVolume = 127 },
    { .aFilename = "1324 - Albinozod", .nTransType = 3, .nId = 1324, .aName = "stateAT", .nVolume = 127 },
    { .aFilename = "1334 - Albino Trap", .nTransType = 3, .nId = 1334, .aName = "stateAT_TRAP", .nVolume = 127 },
    { .aFilename = "1325 - Florist Shop", .nTransType = 3, .nId = 1325, .aName = "stateFP", .nHookSlot = 162, .nVolume = 127 },
    { .aFilename = "1326 - Florist Shop Int", .nTransType = 3, .nId = 1326, .aName = "stateFI", .nHookSlot = 162, .nVolume = 127 },
    { .aFilename = "1327 - Florist OK", .nTransType = 2, .nId = 1327, .aName = "stateFI_OK", .nVolume = 127 },
    { .aFilename = "1323 - Sewer Maze", .nTransType = 3, .nId = 1328, .aName = "stateTE", .nHookLimit = 2, .nVolume = 127 },
    { .aFilename = "1329 - Theater Backstag", .nTransType = 2, .nId = 1329, .aName = "stateTH", .nHookLimit = 4, .nVolume = 127 },
    { .aFilename = "1330 - Lemans Lobby", .nTransType = 2, .nId = 1330, .aName = "stateLY", .nVolume = 127 },
    { .aFilename = "1330 - Lemans Lobby", .nTransType = 2, .nId = 1331, .aName = "stateLY_CHOW", .nVolume = 60 },
    { .aFilename = "1333 - Brennis Talk", .nTransType = 2, .nId = 1333, .aName = "stateLY_BREN", .nVolume = 127 },
    { .aFilename = "1332 - Hector's Foyer", .nTransType = 3, .nId = 1332, .aName = "stateHF", .nVolume = 127 },
    { .aFilename = "1342 - Neon Ledge", .nTransType = 2, .nId = 1340, .aName = "stateNL", .nVolume = 127 },
    { .aFilename = "1350 - Meadow Flowers", .nTransType = 2, .nId = 1350, .aName = "stateMF", .nVolume = 127 },
    { .aFilename = "1351 - Meadow", .nTransType = 2, .nId = 1351, .aName = "stateME", .nVolume = 127 },
    { .aFilename = "1352 - Car Head", .nTransType = 2, .nId = 1352, .aName = "stateHI", .nVolume = 127 },
    { .aFilename = "1353 - Greenhouse Appr", .nTransType = 2, .nId = 1353, .aName = "stateGE", .nVolume = 127 },
    { .aFilename = "1355 - Shootout", .nTransType = 2, .nId = 1355, .aName = "stateSHOOT", .nVolume = 127 },
    { .aFilename = "1354 - Game Ending", .nTransType = 2, .nId = 1354, .aName = "stateEND", .nVolume = 127 },
    { .aFilename = "1400 - Start Credits", .nTransType = 2, .nId = 1400, .aName = "stateOPEN_CRED", .nVolume = 127 },
    { .aFilename = "1401 - Smooth Hector", .nTransType = 2, .nId = 1401, .aName = "stateEND_CRED", .nFade = 20, .nVolume = 105 },
    { .nId = 1500, .aName = "stateMenu", .nVolume = 127 }
};
/* 0x1001ae4c, 4 bytes */ GRIM_DATA("1001ae4c") unsigned char grim_def_DAT_1001ae4c[4] __asm__("_DAT_1001ae4c") = {0};
/* 0x1001ae50, 3444 bytes */ GRIM_DATA("1001ae50") ImMusicEntry grim_def_g_aImSeqTable[41] __asm__("_g_aImSeqTable") = {
    { .nId = 2000, .aName = "SEQ_NULL", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2001 - Climb Rope", .nTransType = 2, .nId = 2001, .aName = "seqClimbRope", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2010 - Glottis OK", .nTransType = 2, .nId = 2010, .aName = "seqGlottisOK", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2020 - Reap Bruno", .nTransType = 2, .nId = 2020, .aName = "seqReapBruno", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2030 - Ledgepeckers", .nTransType = 2, .nId = 2030, .aName = "seqLedgepeckers", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2050 - Glottis Heart", .nTransType = 2, .nId = 2050, .aName = "seqGlottisHeart", .nFade = 300, .nVolume = 105 },
    { .aFilename = "2055 - Slingshot Bone", .nTransType = 2, .nId = 2055, .aName = "seqSlingshotBone", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2060 - Glott Tree Fall", .nTransType = 2, .nId = 2060, .aName = "seqGlottTreeFall", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2070 - Beaver Fly", .nTransType = 2, .nId = 2070, .aName = "seqBeaverFly", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2071 - Beaver Sink", .nTransType = 2, .nId = 2071, .aName = "seqBeaverSink", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2080 - Meet Velasco", .nTransType = 2, .nId = 2080, .aName = "seqMeetVelasco", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2140 - Ooo Bonewagon", .nTransType = 2, .nId = 2140, .aName = "seqGlottSingBone", .nFade = 300, .nVolume = 127, .nPan = 75 },
    { .aFilename = "2141 - Ooo Meche", .nTransType = 2, .nId = 2141, .aName = "seqMannySingMeche", .nFade = 300, .nVolume = 127, .nPan = 75 },
    { .aFilename = "2155 - Find Detector", .nTransType = 2, .nId = 2155, .aName = "seqFindDetector", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2156 - Glott Drink Wine", .nTransType = 2, .nId = 2156, .aName = "seqGlottDrinkWine", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2157 - Glott No Wine", .nTransType = 2, .nId = 2157, .aName = "seqGlottNoWine", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2161 - Raoul Appears", .nTransType = 2, .nId = 2161, .aName = "seqRaoulAppears", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2162 - Raoul KO", .nTransType = 2, .nId = 2162, .aName = "seqRaoulKO", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2163 - Raoul Dissed", .nTransType = 2, .nId = 2163, .aName = "seqRaoulDissed", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2165 - Fake Tix", .nTransType = 2, .nId = 2165, .aName = "seqFakeTix", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2180 - Befriend Commies", .nTransType = 2, .nId = 2180, .aName = "seqBefriendCommies", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2186 - Nick Punchout", .nTransType = 2, .nId = 2186, .aName = "seqNickPunchout", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2200 - Yr 3 Iris", .nTransType = 2, .nId = 2200, .aName = "seqYr3Iris", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2210 - Hit Men", .nTransType = 2, .nId = 2210, .aName = "seqHitMen", .nFade = 700, .nVolume = 127 },
    { .aFilename = "2230 - Open Vault", .nTransType = 2, .nId = 2230, .aName = "seqOpenVault", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2235 - Dead Tix", .nTransType = 2, .nId = 2235, .aName = "seqDeadTix", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2240 - Sprinkler", .nTransType = 2, .nId = 2240, .aName = "seqSprinkler", .nFade = 500, .nVolume = 127 },
    { .aFilename = "2250 - Crane Track", .nTransType = 2, .nId = 2250, .aName = "seqCraneTrack", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2255 - Crane Fall", .nTransType = 2, .nId = 2255, .aName = "seqCraneFall", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2300 - Yr 4 Iris", .nTransType = 2, .nId = 2300, .aName = "seqYr4Iris", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2301 - Pop Bruno Casket", .nTransType = 2, .nId = 2301, .aName = "seqPopBrunoCasket", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2310 - Rocket Idea", .nTransType = 2, .nId = 2310, .aName = "seqRocketIdea", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2320 - Jello Suspense", .nTransType = 2, .nId = 2320, .aName = "seqJelloSuspense", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2325 - Lumbago Lemo", .nTransType = 2, .nId = 2325, .aName = "seqLumbagoLemo", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2327 - Breath Mint", .nTransType = 2, .nId = 2327, .aName = "seqBreathMint", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2330 - Pigeon Fly", .nTransType = 2, .nId = 2330, .aName = "seqPigeonFly", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2340 - Coffee On Boys", .nTransType = 2, .nId = 2340, .aName = "seqCoffeeOnBoys", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2350 - Sprout Aha", .nTransType = 2, .nId = 2350, .aName = "seqSproutAha", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2360 - Chowchilla Bye", .nTransType = 2, .nId = 2360, .aName = "seqChowchillaBye", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2370 - Salvador Death", .nTransType = 2, .nId = 2370, .aName = "seqSalvadorDeath", .nFade = 300, .nVolume = 127 },
    { .aFilename = "2399 - End Credits", .nTransType = 2, .nId = 2399, .aName = "seqEndCredits", .nFade = 200, .nVolume = 127 }
};
/* 0x1001bbc4, 4 bytes */ GRIM_DATA("1001bbc4") unsigned char grim_def_DAT_1001bbc4[4] __asm__("_DAT_1001bbc4") = {0};
/* 0x1001bbc8, 10944 bytes */ GRIM_DATA("1001bbc8") ImNameAlias grim_def_g_aImNameAlias[171] __asm__("_g_aImNameAlias") = {
    { .aFrom = "1001 - Manny's Office", .aTo = "1001 - Manny's Office.IMC" },
    { .aFrom = "1002 - Mr. Frustration", .aTo = "1002 - Mr. Frustration.IMC" },
    { .aFrom = "1008 - Domino's Office", .aTo = "1008 - Domino's Office.IMC" },
    { .aFrom = "1009 - Copal's Office", .aTo = "1009 - Copal's Office.IMC" },
    { .aFrom = "1010 - Ledge", .aTo = "1010 - Ledge.IMC" },
    { .aFrom = "1011 - Roof", .aTo = "1011 - Roof.IMC" },
    { .aFrom = "1020 - Tube Room", .aTo = "1020 - Tube Room.IMC" },
    { .aFrom = "1021 - Brennis", .aTo = "1021 - Brennis.IMC" },
    { .aFrom = "1022 - Lobby", .aTo = "1022 - Lobby.IMC" },
    { .aFrom = "1023 - Packing Room", .aTo = "1023 - Packing Room.IMC" },
    { .aFrom = "1030 - Garage", .aTo = "1030 - Garage.IMC" },
    { .aFrom = "1031 - Glottis' Shop", .aTo = "1031 - Glottis' Shop.IMC" },
    { .aFrom = "1040 - Festival Wet", .aTo = "1040 - Festival Wet.IMC" },
    { .aFrom = "1041 - Festival Dry", .aTo = "1041 - Festival Dry.IMC" },
    { .aFrom = "1050 - Headquarters", .aTo = "1050 - Headquarters.IMC" },
    { .aFrom = "1060 - Real World", .aTo = "1060 - Real World.IMC" },
    { .aFrom = "1070 - Stump Room", .aTo = "1070 - Stump Room.IMC" },
    { .aFrom = "1071 - Signpost Room", .aTo = "1071 - Signpost Room.IMC" },
    { .aFrom = "1072 - Navigation", .aTo = "1072 - Navigation.IMC" },
    { .aFrom = "1074 - Bone Wagon", .aTo = "1074 - Bone Wagon.IMC" },
    { .aFrom = "1075 - Spider's Eye", .aTo = "1075 - Spider's Eye.IMC" },
    { .aFrom = "1076 - Spider Room", .aTo = "1076 - Spider Room.IMC" },
    { .aFrom = "1077 - Tree Pump Amb", .aTo = "1077 - Tree Pump Amb.IMC" },
    { .aFrom = "1078 - Tree Pump", .aTo = "1078 - Tree Pump.IMC" },
    { .aFrom = "1080 - Beaver Room Lbby", .aTo = "1080 - Beaver Room Lbby.IMC" },
    { .aFrom = "1081 - Beaver Dam", .aTo = "1081 - Beaver Dam.IMC" },
    { .aFrom = "1083 - Beaver Room", .aTo = "1083 - Beaver Room.IMC" },
    { .aFrom = "1084 - Foggy Cactus", .aTo = "1084 - Foggy Cactus.IMC" },
    { .aFrom = "1085 - Rubamat Exterior", .aTo = "1085 - Rubamat Exterior.IMC" },
    { .aFrom = "1087 - Blue Hector", .aTo = "1087 - Blue Hector.IMC" },
    { .aFrom = "1101 - Cafe Office", .aTo = "1101 - Cafe Office.IMC" },
    { .aFrom = "1102 - Cafe Intercom", .aTo = "1102 - Cafe Intercom.IMC" },
    { .aFrom = "1103 - Coat Check", .aTo = "1103 - Coat Check.IMC" },
    { .aFrom = "1104 - Lupe", .aTo = "1104 - Lupe.IMC" },
    { .aFrom = "1106 - Glottis Noodle", .aTo = "1106 - Glottis Noodle.IMC" },
    { .aFrom = "1108 - Casino Interior", .aTo = "1108 - Casino Interior.IMC" },
    { .aFrom = "1109 - Cafe Exterior", .aTo = "1109 - Cafe Exterior.IMC" },
    { .aFrom = "1110 - Cafe Ledge", .aTo = "1110 - Cafe Ledge.IMC" },
    { .aFrom = "1112 - Rusty Sans Vox", .aTo = "1112 - Rusty Sans Vox.IMC" },
    { .aFrom = "1120 - Elevator Station", .aTo = "1120 - Elevator Station.IMC" },
    { .aFrom = "1122 - Blue Exterior", .aTo = "1122 - Blue Exterior.IMC" },
    { .aFrom = "1123 - Blue Casket Ins", .aTo = "1123 - Blue Casket Ins.IMC" },
    { .aFrom = "1124 - Blue Casket Amb", .aTo = "1124 - Blue Casket Amb.IMC" },
    { .aFrom = "1125 - Hector Steps Out", .aTo = "1125 - Hector Steps Out.IMC" },
    { .aFrom = "1125 - Smooth Hector", .aTo = "1125 - Smooth Hector.IMC" },
    { .aFrom = "1127 - Limbo Dock", .aTo = "1127 - Limbo Dock.IMC" },
    { .aFrom = "1128 - Limbo Talk", .aTo = "1128 - Limbo Talk.IMC" },
    { .aFrom = "1129 - Limbo Poem", .aTo = "1129 - Limbo Poem.IMC" },
    { .aFrom = "1130 - Dry Dock", .aTo = "1130 - Dry Dock.IMC" },
    { .aFrom = "1131 - Dry Dock Strike", .aTo = "1131 - Dry Dock Strike.IMC" },
    { .aFrom = "1132 - Lighthouse Ext", .aTo = "1132 - Lighthouse Ext.IMC" },
    { .aFrom = "1133 - Lola's Last", .aTo = "1133 - Lola's Last.IMC" },
    { .aFrom = "1140 - Police Station", .aTo = "1140 - Police Station.IMC" },
    { .aFrom = "1141 - Police Interior", .aTo = "1141 - Police Interior.IMC" },
    { .aFrom = "1143 - Morgue", .aTo = "1143 - Morgue.IMC" },
    { .aFrom = "1145 - Bridge Blimp", .aTo = "1145 - Bridge Blimp.IMC" },
    { .aFrom = "1146 - LOL Security Ext", .aTo = "1146 - LOL Security Ext.IMC" },
    { .aFrom = "1147 - LOL Security Int", .aTo = "1147 - LOL Security Int.IMC" },
    { .aFrom = "1148 - Carla's Life", .aTo = "1148 - Carla's Life.IMC" },
    { .aFrom = "1149 - Bomb", .aTo = "1149 - Bomb.IMC" },
    { .aFrom = "1152 - Track Stairs", .aTo = "1152 - Track Stairs.IMC" },
    { .aFrom = "1153 - Track Base", .aTo = "1153 - Track Base.IMC" },
    { .aFrom = "1154 - Kitty Hall", .aTo = "1154 - Kitty Hall.IMC" },
    { .aFrom = "1155 - Sanspoof", .aTo = "1155 - Sanspoof.IMC" },
    { .aFrom = "1156 - Kitty Stables", .aTo = "1156 - Kitty Stables.IMC" },
    { .aFrom = "1160 - High Roller Hall", .aTo = "1160 - High Roller Hall.IMC" },
    { .aFrom = "1161 - High Roller Lnge", .aTo = "1161 - High Roller Lnge.IMC" },
    { .aFrom = "1162 - Glottis Gambling", .aTo = "1162 - Glottis Gambling.IMC" },
    { .aFrom = "1163 - Max's Office", .aTo = "1163 - Max's Office.IMC" },
    { .aFrom = "1167 - Dillopede Elev", .aTo = "1167 - Dillopede Elev.IMC" },
    { .aFrom = "1170 - Extendo Bridge", .aTo = "1170 - Extendo Bridge.IMC" },
    { .aFrom = "1173 - Scrimshaw Int", .aTo = "1173 - Scrimshaw Int.IMC" },
    { .aFrom = "1174 - Scrim Sleep", .aTo = "1174 - Scrim Sleep.IMC" },
    { .aFrom = "1180 - Note to Manny", .aTo = "1180 - Note to Manny.IMC" },
    { .aFrom = "1201 - Lola Zapata", .aTo = "1201 - Lola Zapata.IMC" },
    { .aFrom = "1202 - Inside The Lola", .aTo = "1202 - Inside The Lola.IMC" },
    { .aFrom = "1203 - Engine Room", .aTo = "1203 - Engine Room.IMC" },
    { .aFrom = "1204 - Porthole", .aTo = "1204 - Porthole.IMC" },
    { .aFrom = "1210 - Sunken Lola", .aTo = "1210 - Sunken Lola.IMC" },
    { .aFrom = "1211 - Pearl Crater Sub", .aTo = "1211 - Pearl Crater Sub.IMC" },
    { .aFrom = "1220 - Miner's Room", .aTo = "1220 - Miner's Room.IMC" },
    { .aFrom = "1222 - Exterior Airlock", .aTo = "1222 - Exterior Airlock.IMC" },
    { .aFrom = "1223 - Factory Hub", .aTo = "1223 - Factory Hub.IMC" },
    { .aFrom = "1224 - Foreman's Office", .aTo = "1224 - Foreman's Office.IMC" },
    { .aFrom = "1230 - Vault Door", .aTo = "1230 - Vault Door.IMC" },
    { .aFrom = "1231 - Outer Vault", .aTo = "1231 - Outer Vault.IMC" },
    { .aFrom = "1232 - Inner Vault", .aTo = "1232 - Inner Vault.IMC" },
    { .aFrom = "1233 - Ashtray Room", .aTo = "1233 - Ashtray Room.IMC" },
    { .aFrom = "1234 - Ashtray Scary", .aTo = "1234 - Ashtray Scary.IMC" },
    { .aFrom = "1235 - Ashtray Pensive", .aTo = "1235 - Ashtray Pensive.IMC" },
    { .aFrom = "1236 - Domino's Room", .aTo = "1236 - Domino's Room.IMC" },
    { .aFrom = "1240 - Conveyor Under", .aTo = "1240 - Conveyor Under.IMC" },
    { .aFrom = "1241 - Crane Intro", .aTo = "1241 - Crane Intro.IMC" },
    { .aFrom = "1243 - Anchor Room", .aTo = "1243 - Anchor Room.IMC" },
    { .aFrom = "1244 - Glottis Hanging", .aTo = "1244 - Glottis Hanging.IMC" },
    { .aFrom = "1245 - End of the World", .aTo = "1245 - End of the World.IMC" },
    { .aFrom = "1246 - End World Later", .aTo = "1246 - End World Later.IMC" },
    { .aFrom = "1250 - Upper Beach", .aTo = "1250 - Upper Beach.IMC" },
    { .aFrom = "1252 - Lower Beach Boat", .aTo = "1252 - Lower Beach Boat.IMC" },
    { .aFrom = "1253 - Lamancha Sub", .aTo = "1253 - Lamancha Sub.IMC" },
    { .aFrom = "1254 - Crane Later", .aTo = "1254 - Crane Later.IMC" },
    { .aFrom = "1301 - Temple Gate", .aTo = "1301 - Temple Gate.IMC" },
    { .aFrom = "1303 - Truck Depot", .aTo = "1303 - Truck Depot.IMC" },
    { .aFrom = "1304 - Mayan Train Sta", .aTo = "1304 - Mayan Train Sta.IMC" },
    { .aFrom = "1305 - Mayan Workshop", .aTo = "1305 - Mayan Workshop.IMC" },
    { .aFrom = "1306 - Mayan Train Pad", .aTo = "1306 - Mayan Train Pad.IMC" },
    { .aFrom = "1307 - Mechanic's Kitch", .aTo = "1307 - Mechanic's Kitch.IMC" },
    { .aFrom = "1310 - Jello Bomb", .aTo = "1310 - Jello Bomb.IMC" },
    { .aFrom = "1319 - Florist Video", .aTo = "1319 - Florist Video.IMC" },
    { .aFrom = "1320 - New LSA HQ", .aTo = "1320 - New LSA HQ.IMC" },
    { .aFrom = "1321 - LSA Sewer", .aTo = "1321 - LSA Sewer.IMC" },
    { .aFrom = "1323 - Sewer Maze", .aTo = "1323 - Sewer Maze.IMC" },
    { .aFrom = "1324 - Albinozod", .aTo = "1324 - Albinozod.IMC" },
    { .aFrom = "1325 - Florist Shop", .aTo = "1325 - Florist Shop.IMC" },
    { .aFrom = "1326 - Florist Shop Int", .aTo = "1326 - Florist Shop Int.IMC" },
    { .aFrom = "1327 - Florist OK", .aTo = "1327 - Florist OK.IMC" },
    { .aFrom = "1329 - Theater Backstag", .aTo = "1329 - Theater Backstag.IMC" },
    { .aFrom = "1330 - Lemans Lobby", .aTo = "1330 - Lemans Lobby.IMC" },
    { .aFrom = "1332 - Hector's Foyer", .aTo = "1332 - Hector's Foyer.IMC" },
    { .aFrom = "1333 - Brennis Talk", .aTo = "1333 - Brennis Talk.IMC" },
    { .aFrom = "1334 - Albino Trap", .aTo = "1334 - Albino Trap.IMC" },
    { .aFrom = "1342 - Neon Ledge", .aTo = "1342 - Neon Ledge.IMC" },
    { .aFrom = "1350 - Meadow Flowers", .aTo = "1350 - Meadow Flowers.IMC" },
    { .aFrom = "1351 - Meadow", .aTo = "1351 - Meadow.IMC" },
    { .aFrom = "1352 - Car Head", .aTo = "1352 - Car Head.IMC" },
    { .aFrom = "1353 - Greenhouse Appr", .aTo = "1353 - Greenhouse Appr.IMC" },
    { .aFrom = "1354 - Game Ending", .aTo = "1354 - Game Ending.IMC" },
    { .aFrom = "1355 - Shootout", .aTo = "1355 - Shootout.IMC" },
    { .aFrom = "1400 - Start Credits", .aTo = "1400 - Start Credits.IMC" },
    { .aFrom = "1401 - Smooth Hector", .aTo = "1401 - Smooth Hector.IMC" },
    { .aFrom = "2001 - Climb Rope", .aTo = "2001 - Climb Rope.IMC" },
    { .aFrom = "2010 - Glottis OK", .aTo = "2010 - Glottis OK.IMC" },
    { .aFrom = "2020 - Reap Bruno", .aTo = "2020 - Reap Bruno.IMC" },
    { .aFrom = "2030 - Ledgepeckers", .aTo = "2030 - Ledgepeckers.IMC" },
    { .aFrom = "2050 - Glottis Heart", .aTo = "2050 - Glottis Heart.IMC" },
    { .aFrom = "2055 - Slingshot Bone", .aTo = "2055 - Slingshot Bone.IMC" },
    { .aFrom = "2060 - Glott Tree Fall", .aTo = "2060 - Glott Tree Fall.IMC" },
    { .aFrom = "2070 - Beaver Fly", .aTo = "2070 - Beaver Fly.IMC" },
    { .aFrom = "2071 - Beaver Sink", .aTo = "2071 - Beaver Sink.IMC" },
    { .aFrom = "2080 - Meet Velasco", .aTo = "2080 - Meet Velasco.IMC" },
    { .aFrom = "2140 - Ooo Bonewagon", .aTo = "2140 - Ooo Bonewagon.IMC" },
    { .aFrom = "2141 - Ooo Meche", .aTo = "2141 - Ooo Meche.IMC" },
    { .aFrom = "2155 - Find Detector", .aTo = "2155 - Find Detector.IMC" },
    { .aFrom = "2156 - Glott Drink Wine", .aTo = "2156 - Glott Drink Wine.IMC" },
    { .aFrom = "2157 - Glott No Wine", .aTo = "2157 - Glott No Wine.IMC" },
    { .aFrom = "2161 - Raoul Appears", .aTo = "2161 - Raoul Appears.IMC" },
    { .aFrom = "2162 - Raoul KO", .aTo = "2162 - Raoul KO.IMC" },
    { .aFrom = "2163 - Raoul Dissed", .aTo = "2163 - Raoul Dissed.IMC" },
    { .aFrom = "2165 - Fake Tix", .aTo = "2165 - Fake Tix.IMC" },
    { .aFrom = "2180 - Befriend Commies", .aTo = "2180 - Befriend Commies.IMC" },
    { .aFrom = "2186 - Nick Punchout", .aTo = "2186 - Nick Punchout.IMC" },
    { .aFrom = "2200 - Yr 3 Iris", .aTo = "2200 - Yr 3 Iris.IMC" },
    { .aFrom = "2210 - Hit Men", .aTo = "2210 - Hit Men.IMC" },
    { .aFrom = "2230 - Open Vault", .aTo = "2230 - Open Vault.IMC" },
    { .aFrom = "2235 - Dead Tix", .aTo = "2235 - Dead Tix.IMC" },
    { .aFrom = "2240 - Sprinkler", .aTo = "2240 - Sprinkler.IMC" },
    { .aFrom = "2250 - Crane Track", .aTo = "2250 - Crane Track.IMC" },
    { .aFrom = "2255 - Crane Fall", .aTo = "2255 - Crane Fall.IMC" },
    { .aFrom = "2300 - Yr 4 Iris", .aTo = "2300 - Yr 4 Iris.IMC" },
    { .aFrom = "2301 - Pop Bruno Casket", .aTo = "2301 - Pop Bruno Casket.IMC" },
    { .aFrom = "2310 - Rocket Idea", .aTo = "2310 - Rocket Idea.IMC" },
    { .aFrom = "2320 - Jello Suspense", .aTo = "2320 - Jello Suspense.IMC" },
    { .aFrom = "2325 - Lumbago Lemo", .aTo = "2325 - Lumbago Lemo.IMC" },
    { .aFrom = "2327 - Breath Mint", .aTo = "2327 - Breath Mint.IMC" },
    { .aFrom = "2330 - Pigeon Fly", .aTo = "2330 - Pigeon Fly.IMC" },
    { .aFrom = "2340 - Coffee On Boys", .aTo = "2340 - Coffee On Boys.IMC" },
    { .aFrom = "2350 - Sprout Aha", .aTo = "2350 - Sprout Aha.IMC" },
    { .aFrom = "2360 - Chowchilla Bye", .aTo = "2360 - Chowchilla Bye.IMC" },
    { .aFrom = "2370 - Salvador Death", .aTo = "2370 - Salvador Death.IMC" },
    { .aFrom = "2399 - End Credits", .aTo = "2399 - End Credits.IMC" },
    {0}
};
/* 0x1001e688, 4 bytes */ GRIM_DATA("1001e688") unsigned int grim_def_g_dwLocalMusic __asm__("_g_dwLocalMusic") = 0x1;
/* 0x1001e68c, 40 bytes */ GRIM_DATA("1001e68c") char grim_def_s_ERROR_unrecognized_opcode_in_scr_1001e68c[40] __asm__("_s_ERROR_unrecognized_opcode_in_scr_1001e68c") = "ERROR:unrecognized opcode in script...";
/* 0x1001e6b4, 36 bytes */ GRIM_DATA("1001e6b4") char grim_def_s_ERROR_script_already_initialized_1001e6b4[36] __asm__("_s_ERROR_script_already_initialized_1001e6b4") = "ERROR:script already initialized...";
/* 0x1001e6d8, 32 bytes */ GRIM_DATA("1001e6d8") char grim_def_s_ERROR_script_not_initialized____1001e6d8[32] __asm__("_s_ERROR_script_not_initialized____1001e6d8") = "ERROR:script not initialized...";
/* 0x1001e6f8, 40 bytes */ /* loose */ char grim_def_s_SCRIPT_ERR__save_buffer_too_smal_1001e6f8[40] __asm__("_s_SCRIPT_ERR__save_buffer_too_smal_1001e6f8") = "SCRIPT ERR: save buffer too small...";
/* 0x1001e720, 24 bytes */ /* loose */ char grim_def_s_ERR__bogus_sequence____1001e720[24] __asm__("_s_ERR__bogus_sequence____1001e720") = "ERR: bogus sequence...";
/* 0x1001e738, 24 bytes */ /* loose */ char grim_def_s_ERR__bogus_attribute____1001e738[24] __asm__("_s_ERR__bogus_attribute____1001e738") = "ERR: bogus attribute...";
/* 0x1001e750, 24 bytes */ /* loose */ char grim_def_s_Set_attr__lu_to__lu____1001e750[24] __asm__("_s_Set_attr__lu_to__lu____1001e750") = "Set attr %lu to %lu...";
/* 0x1001e768, 32 bytes */ /* loose */ char grim_def_s_SCRIPT_ERR__bogus_trans_type____1001e768[32] __asm__("_s_SCRIPT_ERR__bogus_trans_type____1001e768") = "SCRIPT ERR: bogus trans type...";
/* 0x1001e788, 36 bytes */ /* loose */ char grim_def_s_SCRIPT_ERR__failed_start_stream__1001e788[36] __asm__("_s_SCRIPT_ERR__failed_start_stream__1001e788") = "SCRIPT ERR: failed start stream...";
/* 0x1001e7ac, 20 bytes */ /* loose */ char grim_def_s_No_stream_sound____1001e7ac[20] __asm__("_s_No_stream_sound____1001e7ac") = "No stream sound...";
/* 0x1001e7c0, 16 bytes */ /* loose */ char grim_def_s_and_PAN__lu____1001e7c0[16] __asm__("_s_and_PAN__lu____1001e7c0") = "and PAN=%lu...";
/* 0x1001e7d0, 20 bytes */ /* loose */ char grim_def_s_fading_VOL__lu____1001e7d0[20] __asm__("_s_fading_VOL__lu____1001e7d0") = "fading VOL=%lu...";
/* 0x1001e7e4, 16 bytes */ /* loose */ char grim_def_s_set_pan__lu____1001e7e4[16] __asm__("_s_set_pan__lu____1001e7e4") = "set pan=%lu...";
/* 0x1001e7f4, 8 bytes */ /* loose */ char grim_def_s_clear_1001e7f4[8] __asm__("_s_clear_1001e7f4") = "clear";
/* 0x1001e7fc, 8 bytes */ /* loose */ char grim_def_s_exit2_1001e7fc[8] __asm__("_s_exit2_1001e7fc") = "exit2";
/* 0x1001e804, 8 bytes */ /* loose */ char grim_def_s_exit_1001e804[8] __asm__("_s_exit_1001e804") = "exit";
/* 0x1001e80c, 12 bytes */ /* loose */ char grim_def_s_vol__lu____1001e80c[12] __asm__("_s_vol__lu____1001e80c") = "vol=%lu...";
/* 0x1001e818, 12 bytes */ /* loose */ char grim_def_s_FADE__lu____1001e818[12] __asm__("_s_FADE__lu____1001e818") = "FADE=%lu...";
/* 0x1001e824, 12 bytes */ /* loose */ char grim_def_s_HOOK__lu____1001e824[12] __asm__("_s_HOOK__lu____1001e824") = "HOOK=%lu...";
/* 0x1001e830, 28 bytes */ /* loose */ char grim_def_s_SCRIPT_ERR__Unable_to_open_1001e830[28] __asm__("_s_SCRIPT_ERR__Unable_to_open_1001e830") = "SCRIPT ERR: Unable to open ";
/* 0x1001e84c, 12 bytes */ /* loose */ char grim_def_s_opening_1001e84c[12] __asm__("_s_opening_1001e84c") = "opening ";
/* 0x1001e858, 8 bytes */ /* loose */ char grim_def_s__end_1001e858[8] __asm__("_s__end_1001e858") = "_end";
/* 0x1001e860, 16 bytes */ /* loose */ char grim_def_s_Trans_null____1001e860[16] __asm__("_s_Trans_null____1001e860") = "Trans null...";
/* 0x1001e870, 40 bytes */ /* loose */ char grim_def_s_ERR_callback_got_marker______end_1001e870[40] __asm__("_s_ERR_callback_got_marker______end_1001e870") = "ERR:callback got marker != '_end'...";
/* 0x1001e898, 12 bytes */ /* loose */ char grim_def_s_CALLBACK__1001e898[12] __asm__("_s_CALLBACK__1001e898") = "CALLBACK:";
/* 0x1001e8d4, 4 bytes */ /* loose */ unsigned int grim_def_g_dwImWaveMixCount __asm__("_g_dwImWaveMixCount") = 0x8;
/* 0x1001e994, 8 bytes */ GRIM_DATA("1001e994") char grim_def_s_LIP__1001e994[8] __asm__("_s_LIP__1001e994") = "LIP!";
/* 0x1001e99c, 28 bytes */ GRIM_DATA("1001e99c") unsigned char grim_def_DAT_1001e99c[28] __asm__("_DAT_1001e99c") = {
    0x70, 0x46, 0x69, 0x6c, 0x65, 0x6e, 0x61, 0x6d, 0x65, 0x20, 0x21, 0x3d, 0x20, 0x28, 0x28, 0x76,
    0x6f, 0x69, 0x64, 0x20, 0x2a, 0x29, 0x30, 0x29
};
/* 0x1001e9b8, 8 bytes */ GRIM_DATA("1001e9b8") unsigned char grim_def_DAT_1001e9b8[8] __asm__("_DAT_1001e9b8") = { 0x70, 0x45, 0x6e, 0x74, 0x72, 0x79 };
/* 0x1001e9c0, 16 bytes */ GRIM_DATA("1001e9c0") char grim_def_s_VIMA_1001e9c0[16] __asm__("_s_VIMA_1001e9c0") = "VIMA\000\000\000\000u\230\000\000s\230";
/* 0x10022140, 128 bytes */ GRIM_DATA("10022140") unsigned char grim_def_DAT_10022140[128] __asm__("_DAT_10022140") = {0};
/* 0x100221c0, 11264 bytes */ GRIM_DATA("100221c0") unsigned char grim_def_DAT_100221c0[11264] __asm__("_DAT_100221c0") = {0};
/* 0x10024dc0, 8 bytes */ GRIM_DATA("10024dc0") unsigned char grim_def_DAT_10024dc0[8] __asm__("_DAT_10024dc0") = {0};
/* 0x10024dd0, 4 bytes */ GRIM_DATA("10024dd0") unsigned int grim_def_g_dwLargeFadeFlags __asm__("_g_dwLargeFadeFlags") = 0x0;
/* 0x10024ddc, 4 bytes */ GRIM_DATA("10024ddc") unsigned char grim_def_g_dwDpProcessTrack_critSize[4] __asm__("_g_dwDpProcessTrack_critSize") = {0};
/* 0x10024de0, 8 bytes */ GRIM_DATA("10024de0") unsigned char grim_def_g_dwFadeStartedFlag[8] __asm__("_g_dwFadeStartedFlag") = {0};
/* 0x1002d7e0, 4 bytes */ GRIM_DATA("1002d7e0") unsigned char grim_def_g_dwDpProcessTrack_curLevel[4] __asm__("_g_dwDpProcessTrack_curLevel") = {0};
/* 0x1002d7e4, 4 bytes */ GRIM_DATA("1002d7e4") unsigned char grim_def_g_dwDpProcessTrack_pauseFlag[4] __asm__("_g_dwDpProcessTrack_pauseFlag") = {0};
/* 0x1002d7e8, 8 bytes */ GRIM_DATA("1002d7e8") unsigned char grim_def_g_dwGoToNextRegion_fadeSize[8] __asm__("_g_dwGoToNextRegion_fadeSize") = {0};
/* 0x1002d7f0, 24 bytes */ GRIM_DATA("1002d7f0") unsigned char grim_def_DAT_1002d7f0[24] __asm__("_DAT_1002d7f0") = {0};
/* 0x1002d810, 4 bytes */ GRIM_DATA("1002d810") unsigned char grim_def_g_dwDpProcessTrack_bufSize[4] __asm__("_g_dwDpProcessTrack_bufSize") = {0};
/* 0x1002d814, 4 bytes */ GRIM_DATA("1002d814") unsigned int grim_def_DAT_1002d814 __asm__("_DAT_1002d814") = 0x0;
/* 0x1002d818, 4 bytes */ GRIM_DATA("1002d818") unsigned char grim_def_DAT_1002d818[4] __asm__("_DAT_1002d818") = {0};
/* 0x1002d820, 4 bytes */ GRIM_DATA("1002d820") unsigned int grim_def_DAT_1002d820 __asm__("_DAT_1002d820") = 0x0;
/* 0x1002d82c, 4 bytes */ GRIM_DATA("1002d82c") unsigned int grim_def_DAT_1002d82c __asm__("_DAT_1002d82c") = 0x0;
/* 0x1002d830, 4 bytes */ GRIM_DATA("1002d830") unsigned char grim_def_PTR_1002d830[4] __asm__("_PTR_1002d830") = {0};
/* 0x1002d834, 4 bytes */ GRIM_DATA("1002d834") unsigned char grim_def_PTR_1002d834[4] __asm__("_PTR_1002d834") = {0};
/* 0x1002d838, 4 bytes */ GRIM_DATA("1002d838") unsigned char grim_def_PTR_1002d838[4] __asm__("_PTR_1002d838") = {0};
/* 0x1002d840, 4 bytes */ GRIM_DATA("1002d840") unsigned char grim_def_DAT_1002d840[4] __asm__("_DAT_1002d840") = {0};
/* 0x1002d844, 4 bytes */ GRIM_DATA("1002d844") unsigned int grim_def_DAT_1002d844 __asm__("_DAT_1002d844") = 0x0;
/* 0x1002d848, 4 bytes */ GRIM_DATA("1002d848") unsigned int grim_def_DAT_1002d848 __asm__("_DAT_1002d848") = 0x0;
/* 0x1002d84c, 4 bytes */ GRIM_DATA("1002d84c") unsigned int grim_def_g_dwCurrentWriteIndex __asm__("_g_dwCurrentWriteIndex") = 0x0;
/* 0x1002d850, 4 bytes */ GRIM_DATA("1002d850") unsigned char grim_def_DAT_1002d850[4] __asm__("_DAT_1002d850") = {0};
/* 0x1002d854, 4 bytes */ GRIM_DATA("1002d854") unsigned char grim_def_DAT_1002d854[4] __asm__("_DAT_1002d854") = {0};
/* 0x1002d858, 8 bytes */ GRIM_DATA("1002d858") unsigned int grim_def_g_dwFadesOn __asm__("_g_dwFadesOn") = 0x0;
/* 0x1002d85c, 4 bytes: the rest of grim_def_g_dwFadesOn's span */ GRIM_DATA("1002d858") static unsigned char g_dwFadesOn__tail[4] __attribute__((used)) = {0};
/* 0x1002d860, 32 bytes */ GRIM_DATA("1002d860") unsigned char grim_def_g_dwFades[32] __asm__("_g_dwFades") = {0};
/* 0x1002d880, 608 bytes */ GRIM_DATA("1002d880") unsigned char grim_def_DAT_1002d880[608] __asm__("_DAT_1002d880") = {0};
/* 0x1002dd14, 4 bytes */ GRIM_DATA("1002dd14") unsigned char grim_def_DAT_1002dd14[4] __asm__("_DAT_1002dd14") = {0};
/* 0x1002dd18, 4 bytes */ GRIM_DATA("1002dd18") unsigned int grim_def_DAT_1002dd18 __asm__("_DAT_1002dd18") = 0x0;
/* 0x1002dd1c, 4 bytes */ GRIM_DATA("1002dd1c") unsigned char grim_def_DAT_1002dd1c[4] __asm__("_DAT_1002dd1c") = {0};
/* 0x1002dd20, 4 bytes */ GRIM_DATA("1002dd20") unsigned int grim_def_UINT_1002dd20 __asm__("_UINT_1002dd20") = 0x0;
/* 0x1002dd24, 4 bytes */ GRIM_DATA("1002dd24") unsigned char grim_def_DAT_1002dd24[4] __asm__("_DAT_1002dd24") = {0};
/* 0x1002dd28, 4 bytes */ GRIM_DATA("1002dd28") unsigned char grim_def_DAT_1002dd28[4] __asm__("_DAT_1002dd28") = {0};
/* 0x1002dd80, 4 bytes */ GRIM_DATA("1002dd80") unsigned int grim_def_g_dwGroupVols __asm__("_g_dwGroupVols") = 0x0;
/* 0x1002dd84, 60 bytes */ GRIM_DATA("1002dd84") unsigned char grim_def_DAT_1002dd84[60] __asm__("_DAT_1002dd84") = {0};
/* 0x1002ddc0, 4 bytes */ GRIM_DATA("1002ddc0") unsigned int grim_def_g_dwGroupEffVols __asm__("_g_dwGroupEffVols") = 0x0;
/* 0x1002ddc4, 60 bytes */ GRIM_DATA("1002ddc4") unsigned char grim_def_DAT_1002ddc4[60] __asm__("_DAT_1002ddc4") = {0};
/* 0x1002df18, 4 bytes */ GRIM_DATA("1002df18") unsigned int grim_def_g_dwOutChannelCount __asm__("_g_dwOutChannelCount") = 0x0;
/* 0x1002df20, 4 bytes */ GRIM_DATA("1002df20") unsigned char grim_def_g_dwSoftLTable[4] __asm__("_g_dwSoftLTable") = {0};
/* 0x1002df24, 4 bytes */ GRIM_DATA("1002df24") unsigned int grim_def_g_dwMixBufSize __asm__("_g_dwMixBufSize") = 0x0;
/* 0x1002df28, 8 bytes */ GRIM_DATA("1002df28") unsigned char grim_def_DAT_1002df28[8] __asm__("_DAT_1002df28") = {0};
/* 0x1002df30, 44 bytes */ GRIM_DATA("1002df30") unsigned char grim_def_g_aMxEndMix_wavHeader[44] __asm__("_g_aMxEndMix_wavHeader") = {0};
/* 0x1002df5c, 4 bytes */ GRIM_DATA("1002df5c") unsigned char grim_def_g_pMixBuf[4] __asm__("_g_pMixBuf") = {0};
/* 0x1002df68, 4 bytes */ GRIM_DATA("1002df68") unsigned char grim_def_DAT_1002df68[4] __asm__("_DAT_1002df68") = {0};
/* 0x1002df6c, 4 bytes */ GRIM_DATA("1002df6c") unsigned char grim_def_DAT_1002df6c[4] __asm__("_DAT_1002df6c") = {0};
/* 0x1002df70, 8 bytes */ GRIM_DATA("1002df70") unsigned int grim_def_g_dwCurrentState __asm__("_g_dwCurrentState") = 0x0;
/* 0x1002df74, 4 bytes: the rest of grim_def_g_dwCurrentState's span */ GRIM_DATA("1002df70") static unsigned char g_dwCurrentState__tail[4] __attribute__((used)) = {0};
/* 0x1002df78, 12 bytes */ GRIM_DATA("1002df78") unsigned char grim_def_DAT_1002df78[12] __asm__("_DAT_1002df78") = {0};
/* 0x1002df84, 728 bytes */ GRIM_DATA("1002df84") unsigned char grim_def_DAT_1002df84[728] __asm__("_DAT_1002df84") = {0};
/* 0x1002e25c, 168 bytes */ GRIM_DATA("1002e25c") unsigned char grim_def_DAT_1002e25c[168] __asm__("_DAT_1002e25c") = {0};
/* 0x1002e304, 4 bytes */ GRIM_DATA("1002e304") unsigned int grim_def_DAT_1002e304 __asm__("_DAT_1002e304") = 0x0;
/* 0x1002e308, 4 bytes */ GRIM_DATA("1002e308") int grim_def_g_dwCurrentSequence __asm__("_g_dwCurrentSequence") = 0;
/* 0x1002e30c, 4 bytes */ GRIM_DATA("1002e30c") int grim_def_g_dwCurrentCuePoint __asm__("_g_dwCurrentCuePoint") = 0;
/* 0x1002e310, 1 bytes */ GRIM_DATA("1002e310") char grim_def_g_bTrans_name __asm__("_g_bTrans_name") = 0;
/* 0x1002e311, 31 bytes */ GRIM_DATA("1002e310") unsigned char grim_def_DAT_1002e311[31] __asm__("_DAT_1002e311") = {0};
/* 0x1002e330, 8 bytes */ GRIM_DATA("1002e330") unsigned char grim_def_DAT_1002e330[8] __asm__("_DAT_1002e330") = {0};
/* 0x1002e338, 8 bytes */ GRIM_DATA("1002e338") unsigned char grim_def_DAT_1002e338[8] __asm__("_DAT_1002e338") = {0};
/* 0x1002e340, 2000 bytes */ GRIM_DATA("1002e340") unsigned char grim_def_g_aLipSfx1Data[2000] __asm__("_g_aLipSfx1Data") = {0};
/* 0x1002ec18, 2000 bytes */ GRIM_DATA("1002ec18") unsigned char grim_def_g_aLipSfx2Data[2000] __asm__("_g_aLipSfx2Data") = {0};
/* 0x1002f3e8, 2000 bytes */ GRIM_DATA("1002f3e8") unsigned char grim_def_g_bLipStreamData[2000] __asm__("_g_bLipStreamData") = {0};
/* 0x1002fbb8, 24 bytes */ GRIM_DATA("1002fbb8") unsigned char grim_def_DAT_1002fbb8[24] __asm__("_DAT_1002fbb8") = {0};
/* 0x100303a4, 4 bytes */ GRIM_DATA("100303a4") unsigned char grim_def_DAT_100303a4[4] __asm__("_DAT_100303a4") = {0};
/* 0x100303a8, 4 bytes */ GRIM_DATA("100303a8") unsigned char grim_def_DAT_100303a8[4] __asm__("_DAT_100303a8") = {0};
/* 0x100303ac, 4 bytes */ GRIM_DATA("100303ac") unsigned char grim_def_DAT_100303ac[4] __asm__("_DAT_100303ac") = {0};
/* 0x100303b0, 4 bytes */ GRIM_DATA("100303b0") unsigned char grim_def_DAT_100303b0[4] __asm__("_DAT_100303b0") = {0};
/* 0x100303b4, 4 bytes */ GRIM_DATA("100303b4") unsigned char grim_def_DAT_100303b4[4] __asm__("_DAT_100303b4") = {0};
/* 0x100303b8, 4 bytes */ GRIM_DATA("100303b8") unsigned char grim_def_DAT_100303b8[4] __asm__("_DAT_100303b8") = {0};
/* 0x100303bc, 4 bytes */ GRIM_DATA("100303bc") unsigned char grim_def_DAT_100303bc[4] __asm__("_DAT_100303bc") = {0};
/* 0x100303c0, 4 bytes */ GRIM_DATA("100303c0") unsigned char grim_def_DAT_100303c0[4] __asm__("_DAT_100303c0") = {0};
/* 0x100303c4, 4 bytes */ GRIM_DATA("100303c4") unsigned char grim_def_DAT_100303c4[4] __asm__("_DAT_100303c4") = {0};
/* 0x100303c8, 4 bytes */ GRIM_DATA("100303c8") unsigned char grim_def_DAT_100303c8[4] __asm__("_DAT_100303c8") = {0};
/* 0x100303cc, 4 bytes */ GRIM_DATA("100303cc") unsigned char grim_def_DAT_100303cc[4] __asm__("_DAT_100303cc") = {0};
/* 0x100303d0, 4 bytes */ GRIM_DATA("100303d0") unsigned char grim_def_DAT_100303d0[4] __asm__("_DAT_100303d0") = {0};
/* 0x10031554, 4 bytes */ GRIM_DATA("10031554") unsigned char grim_def_DAT_10031554[4] __asm__("_DAT_10031554") = {0};
/* 0x10031558, 8 bytes */ GRIM_DATA("10031558") unsigned char grim_def_DAT_10031558[8] __asm__("_DAT_10031558") = {0};
/* 0x10031e70, 4 bytes */ GRIM_DATA("10031e70") unsigned char grim_def_g_dwLipStreamID[4] __asm__("_g_dwLipStreamID") = {0};
/* 0x10031e74, 4 bytes */ GRIM_DATA("10031e74") unsigned char grim_def_g_dwLipSfx1ID[4] __asm__("_g_dwLipSfx1ID") = {0};
/* 0x10031e78, 4 bytes */ GRIM_DATA("10031e78") unsigned char grim_def_g_dwLipSfx2ID[4] __asm__("_g_dwLipSfx2ID") = {0};
/* 0x10031e7c, 4 bytes */ GRIM_DATA("10031e7c") unsigned char grim_def_g_dwLipSfx3ID[4] __asm__("_g_dwLipSfx3ID") = {0};
/* 0x10031e80, 4 bytes */ GRIM_DATA("10031e80") unsigned char grim_def_DAT_10031e80[4] __asm__("_DAT_10031e80") = {0};
/* 0x10031e84, 4 bytes */ GRIM_DATA("10031e84") unsigned char grim_def_g_dwTimerCounter[4] __asm__("_g_dwTimerCounter") = {0};
/* 0x10031e88, 4 bytes */ GRIM_DATA("10031e88") unsigned int grim_def_g_dwNextToAllocate __asm__("_g_dwNextToAllocate") = 0x0;
/* 0x10031e8c, 4 bytes */ GRIM_DATA("10031e8c") unsigned int grim_def_g_dwIRes_csInit __asm__("_g_dwIRes_csInit") = 0x0;
/* 0x10031f28, 8 bytes */ GRIM_DATA("10031f28") unsigned char grim_def_DAT_10031f28[8] __asm__("_DAT_10031f28") = {0};
/* 0x10031f30, 952 bytes */ GRIM_DATA("10031f30") unsigned char grim_def_DAT_10031f30[952] __asm__("_DAT_10031f30") = {0};
/* 0x100322e8, 8 bytes */ GRIM_DATA("100322e8") unsigned char grim_def_g_dwTrIntHandler_outSampleRate[8] __asm__("_g_dwTrIntHandler_outSampleRate") = {0};
/* 0x100322f0, 16 bytes */ GRIM_DATA("100322f0") unsigned char grim_def_g_aTrInitialize_waveDriverInfo[16] __asm__("_g_aTrInitialize_waveDriverInfo") = {0};
/* 0x10032300, 4 bytes */ GRIM_DATA("10032300") int grim_def_g_dwTrackList __asm__("_g_dwTrackList") = 0;
/* 0x10032304, 4 bytes */ GRIM_DATA("10032304") unsigned int grim_def_g_dwTrIntHandler_outFramesNeeded __asm__("_g_dwTrIntHandler_outFramesNeeded") = 0x0;
/* 0x10032308, 4 bytes */ GRIM_DATA("10032308") unsigned char grim_def_DAT_10032308[4] __asm__("_DAT_10032308") = {0};
/* 0x1003230c, 4 bytes */ GRIM_DATA("1003230c") unsigned int grim_def_g_dwPauseTimer __asm__("_g_dwPauseTimer") = 0x0;
/* 0x10032310, 4 bytes */ GRIM_DATA("10032310") unsigned int grim_def_DAT_10032310 __asm__("_DAT_10032310") = 0x0;
/* 0x10032314, 12 bytes */ GRIM_DATA("10032314") unsigned char grim_def_g_dwTrIntHandler_outPtr[12] __asm__("_g_dwTrIntHandler_outPtr") = {0};
/* 0x10032320, 260 bytes */ GRIM_DATA("10032320") unsigned char grim_def_g_dwTrigs[260] __asm__("_g_dwTrigs") = {0};
/* 0x10032424, 2204 bytes */ GRIM_DATA("10032424") unsigned char grim_def_DAT_10032424[2204] __asm__("_DAT_10032424") = {0};
/* 0x10032cc0, 4 bytes */ GRIM_DATA("10032cc0") unsigned int grim_def_DAT_10032cc0 __asm__("_DAT_10032cc0") = 0x0;
/* 0x10032cc4, 380 bytes */ GRIM_DATA("10032cc4") unsigned char grim_def_DAT_10032cc4[380] __asm__("_DAT_10032cc4") = {0};
/* 0x10032e40, 256 bytes */ GRIM_DATA("10032e40") unsigned char grim_def_g_dwTgProcessMarker_textCopy[256] __asm__("_g_dwTgProcessMarker_textCopy") = {0};
/* 0x10032f40, 4 bytes */ GRIM_DATA("10032f40") unsigned int grim_def_g_dwDefersOn __asm__("_g_dwDefersOn") = 0x0;
/* 0x10032f44, 4 bytes */ GRIM_DATA("10032f44") unsigned int grim_def_g_dwMidProcessing __asm__("_g_dwMidProcessing") = 0x0;
/* 0x10032f48, 8 bytes */ GRIM_DATA("10032f48") unsigned char grim_def_DAT_10032f48[8] __asm__("_DAT_10032f48") = {0};
/* 0x10033560, 8 bytes */ GRIM_DATA("10033560") unsigned char grim_def_g_bPanTable[8] __asm__("_g_bPanTable") = {0};
/* 0x10033568, 312 bytes */ GRIM_DATA("10033568") unsigned char grim_def_DAT_10033568[312] __asm__("_DAT_10033568") = {0};
/* 0x100336a8, 4 bytes */ GRIM_DATA("100336a8") unsigned char grim_def_DAT_100336a8[4] __asm__("_DAT_100336a8") = {0};
__asm__(".globl _grim_img_imuse_0x100172e8\n\t.set _grim_img_imuse_0x100172e8, _g_aImStateTable + 0\n");
__asm__(".globl _grim_img_imuse_0x1001ae50\n\t.set _grim_img_imuse_0x1001ae50, _g_aImSeqTable + 0\n");
__asm__(".globl _grim_img_imuse_0x1001bbc8\n\t.set _grim_img_imuse_0x1001bbc8, _g_aImNameAlias + 0\n");
__asm__(".globl _grim_img_imuse_0x1001e688\n\t.set _grim_img_imuse_0x1001e688, _g_dwLocalMusic + 0\n");
__asm__(".globl _grim_img_imuse_0x1001e804\n\t.set _grim_img_imuse_0x1001e804, _s_exit_1001e804 + 0\n");
__asm__(".globl _grim_img_imuse_0x1001e858\n\t.set _grim_img_imuse_0x1001e858, _s__end_1001e858 + 0\n");
__asm__(".globl _grim_img_imuse_0x1002df70\n\t.set _grim_img_imuse_0x1002df70, _g_dwCurrentState + 0\n");
__asm__(".globl _grim_img_imuse_0x1002df84\n\t.set _grim_img_imuse_0x1002df84, _DAT_1002df84 + 0\n");
__asm__(".globl _grim_img_imuse_0x1002e25c\n\t.set _grim_img_imuse_0x1002e25c, _DAT_1002e25c + 0\n");
__asm__(".globl _grim_img_imuse_0x1002e304\n\t.set _grim_img_imuse_0x1002e304, _DAT_1002e304 + 0\n");
__asm__(".globl _grim_img_imuse_0x1002e308\n\t.set _grim_img_imuse_0x1002e308, _g_dwCurrentSequence + 0\n");
__asm__(".globl _grim_img_imuse_0x1002e30c\n\t.set _grim_img_imuse_0x1002e30c, _g_dwCurrentCuePoint + 0\n");
__asm__(".globl _grim_img_imuse_0x1002e310\n\t.set _grim_img_imuse_0x1002e310, _g_bTrans_name + 0\n");
