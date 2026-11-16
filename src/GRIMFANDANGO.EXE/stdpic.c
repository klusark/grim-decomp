/* GRIMFANDANGO.EXE :: stdpic.c
 * functions 0x0047d280 .. 0x0047d2d0 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0047d280  stdPic_Load ---- */
/* stdLoadImageData loader for '.pic' (wrapper of stdPic_LoadEntry, allocation string stdPic.c); was
   named stdGif_Load. */

uint __cdecl stdPic_Load(uint name,uint a,uint b)

{
  stdBitmap *bitmap;
  uint uVar1;
  
  bitmap = (stdBitmap *)
           (*g_pStd_HS->pAlloc)(0x7c,s_C__grimjedi_Libs_Std_General_std_004e77d8,DAT_004e77cc + 4);
  if (bitmap == (stdBitmap *)0x0) {
    return 0;
  }
  uVar1 = stdPic_LoadEntry((char *)name,bitmap,a,b);
  return -(uint)(uVar1 != 0) & (uint)bitmap;
}

/* ---- 0x0047d2d0  stdPic_LoadEntry ---- */
/* Decoder of '.pic' files (allocation string stdPic.c)
   Ported to C (build/overrides_big_stdpic_loadinto.c): differential test on generated inputs, 0
   differences (docs/notes/big_stdpic_loadinto.md). Original name stdPic_LoadEntry (the remaster's
   GrimFandango (Linux): the only unmatched callee of stdPic_Load; 1 matched neighbours agree, 0
   disagree); was stdPic_LoadInto. */

uint __cdecl stdPic_LoadEntry(char *path,stdBitmap *bitmap,int videoMem,int sysMem)

{
  unsigned char _frame[0x160] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  short sVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  void *pvVar4;
  byte bVar5;
  int iVar6;
  int iVar7;
  uint *puVar8;
  VBuffer **ppVVar9;
  VBuffer *pVVar10;
  int iVar11;
  undefined1 *puVar12;
  uint uVar13;
  int iVar14;
  ColorFormat *pCVar15;
  stdBitmap *psVar16;
  uint uVar17;
  ColorFormat *pCVar18;
  bool bVar19;
  longlong lVar20;
  uint uVar21;
  byte bStack_14b;
  #define bStack_14a (*(byte *)(_frame + (0x160 - 0x14a)))
  #define bStack_149 (*(byte *)(_frame + (0x160 - 0x149)))
  #define psStack_148 (*(stdBitmap **)(_frame + (0x160 - 0x148)))
  #define uStack_141 (*(undefined1 *)(_frame + (0x160 - 0x141)))
  #define iStack_140 (*(int *)(_frame + (0x160 - 0x140)))
  #define pvStack_13c (*(void **)(_frame + (0x160 - 0x13c)))
  #define iStack_138 (*(int *)(_frame + (0x160 - 0x138)))
  #define iStack_134 (*(int *)(_frame + (0x160 - 0x134)))
  #define iStack_130 (*(int *)(_frame + (0x160 - 0x130)))
  #define iStack_12c (*(int *)(_frame + (0x160 - 0x12c)))
  #define uStack_128 (*(uint *)(_frame + (0x160 - 0x128)))
  #define uStack_124 (*(uint *)(_frame + (0x160 - 0x124)))
  #define puStack_120 (*(uint **)(_frame + (0x160 - 0x120)))
  #define uStack_11c (*(uint *)(_frame + (0x160 - 0x11c)))
  #define uStack_118 (*(uint *)(_frame + (0x160 - 0x118)))
  #define uStack_114 (*(uint *)(_frame + (0x160 - 0x114)))
  #define uStack_110 (*(undefined4 *)(_frame + (0x160 - 0x110)))
  PicChannel channel;
  #define iStack_104 (*(int *)(_frame + (0x160 - 0x104)))
  #define auStack_100 (*(undefined1 (*)[4])(_frame + (0x160 - 0x100)))
  uint aChannelType [4];
  PicHeader header;
  ColorFormat format;
  #define VStack_4c (*(VBufferFormat *)(_frame + (0x160 - 0x4c)))
  
  format.dwRedBits = 8;
  format.dwGreenBits = 8;
  format.dwBlueBits = 8;
  format.dwGreenShift = 8;
  aChannelType[0] = 0;
  aChannelType[1] = 0;
  aChannelType[2] = 0;
  aChannelType[3] = 0;
  format.nColorMode = 1;
  format.nBpp = 0x18;
  format.dwRedShift = 0x10;
  format.dwBlueShift = 0;
  format.dwRedLoss = 0;
  format.dwGreenLoss = 0;
  format.dwBlueLoss = 0;
  format.dwUnknown2c = 0;
  format.dwUnknown30 = 0;
  format.dwUnknown34 = 0;
  iVar6 = (*g_pStd_HS->pFopen)(path,s_rb_004ddb18);
  if (iVar6 == 0) {
    return 0;
  }
  iVar7 = (*g_pStd_HS->pFread)(iVar6,&header,0x68);
  if (iVar7 != 0x68) {
    return 0;
  }
  uVar13 = (header.dwMagic << 0x10 | header.dwMagic & 0xff00) << 8 |
           (header.dwMagic >> 0x10 | header.dwMagic & 0xff0000) >> 8;
  header.dwMagic = uVar13;
  lVar20 = FTOL((float10)header.flVersion);
  uVar3 = (undefined1)header.wHeight;
  uVar2 = (undefined1)header.wWidth;
  uVar21 = (uint)lVar20;
  uStack_110 = 0;
  uStack_114 = (uVar21 & 0xff00 | uVar21 << 0x10) << 8 | (uVar21 >> 0x10 | uVar21 & 0xff0000) >> 8;
  header.flVersion = (float)uStack_114;
  PIECE(header.wWidth,0,1) = PIECE(header.wWidth,1,1);
  PIECE(header.wWidth,1,1) = uVar2;
  uVar17 = (header.dwId << 0x10 | header.dwId & 0xff00) << 8 |
           (header.dwId >> 0x10 | header.dwId & 0xff0000) >> 8;
  PIECE(header.wHeight,0,1) = PIECE(header.wHeight,1,1);
  PIECE(header.wHeight,1,1) = uVar3;
  header.dwId = uVar17;
  lVar20 = FTOL((float10)(float)CONCAT22(PIECE(header.flRatio,2,2),PIECE(header.flRatio,0,2)));
  uVar21 = (uint)lVar20;
  uStack_110 = 0;
  uStack_114 = (uVar21 & 0xff00 | uVar21 << 0x10) << 8 | (uVar21 >> 0x10 | uVar21 & 0xff0000) >> 8;
  header.flRatio = (float)uStack_114;
  header.wFields = CONCAT11((undefined1)header.wFields,PIECE(header.wFields,1,1));
  header.wPad = CONCAT11((undefined1)header.wPad,PIECE(header.wPad,1,1));
  if (uVar13 != 0x5380f634) {
    return 0;
  }
  if (uVar17 == 0x50494354) {
    iStack_140 = -1;
    iStack_138 = -1;
    iStack_134 = -1;
    iStack_130 = -1;
    iVar14 = 0;
    iVar7 = (*g_pStd_HS->pFread)(iVar6,&channel,4);
    if (iVar7 == 4) {
      puVar8 = aChannelType;
      while( true ) {
        if ((PIECE(channel,2,2) & 0x8000) != 0) {
          iStack_140 = iVar14;
        }
        bStack_149 = channel.bChannels & 0x40;
        if ((PIECE(channel,2,2) & 0x4000) != 0) {
          iStack_138 = iVar14;
        }
        bStack_14a = channel.bChannels & 0x20;
        if ((PIECE(channel,2,2) & 0x2000) != 0) {
          iStack_134 = iVar14;
        }
        if ((PIECE(channel,2,2) & 0x1000) != 0) {
          iStack_130 = iVar14;
        }
        uVar21 = (uint)CONCAT21(PIECE(channel,2,2),channel.bSize);
        if ((PIECE(channel,2,2) & 0x8000) != 0) {
          uStack_128 = (uVar21 & 0xff) >> 3;
        }
        if ((PIECE(channel,2,2) & 0x4000) != 0) {
          uStack_118 = (uVar21 & 0xff) >> 3;
        }
        if ((PIECE(channel,2,2) & 0x2000) != 0) {
          uStack_11c = (uVar21 & 0xff) >> 3;
        }
        if ((PIECE(channel,2,2) & 0x1000) != 0) {
          uStack_124 = (uVar21 & 0xff) >> 3;
        }
        *puVar8 = (ushort)PIECE(channel,2,2) & 0xff;
        if (channel.bSize != 8) break;
        iVar14 = iVar14 + 1;
        puVar8 = puVar8 + 1;
        if (channel.bChained == 0) {
          uVar21 = 0x1f;
          psVar16 = bitmap;
          for (iVar7 = 0x1f; iVar7 != 0; iVar7 = iVar7 + -1) {
            psVar16->aName[0] = '\0';
            psVar16->aName[1] = '\0';
            psVar16->aName[2] = '\0';
            psVar16->aName[3] = '\0';
            psVar16 = (stdBitmap *)(psVar16->aName + 4);
          }
          iStack_12c = iVar14;
          puVar8 = (uint *)stdFileFromPath(path);
          strncpy((uint *)bitmap,puVar8,uVar21);
          bitmap->aName[0x1f] = '\0';
          bitmap->nType = 0;
          bitmap->dwPalFlags = 0;
          bitmap->pPalette = (void *)0x0;
          bitmap->nFrames = 1;
          bitmap->nCurFrame = 0;
          pCVar15 = &format;
          pCVar18 = &bitmap->colorFormat;
          for (iVar7 = 0xe; iVar7 != 0; iVar7 = iVar7 + -1) {
            pCVar18->nColorMode = pCVar15->nColorMode;
            pCVar15 = (ColorFormat *)&pCVar15->nBpp;
            pCVar18 = (ColorFormat *)&pCVar18->nBpp;
          }
          ppVVar9 = (VBuffer **)
                    (*g_pStd_HS->pAlloc)
                              (4,s_C__grimjedi_Libs_Std_General_std_004e77d8,DAT_004e77d0 + 0x6d);
          bitmap->ppFrames = ppVVar9;
          if (ppVVar9 == (VBuffer **)0x0) {
            (*g_pStd_HS->pAssertFail)
                      (s_Unable_to_allocate_memory__004e76d4,
                       s_C__grimjedi_Libs_Std_General_std_004e77d8,DAT_004e77d0 + 0x6e);
          }
          VStack_4c.nWidth =
               CONCAT12((undefined1)header.wHeight,
                        CONCAT11(PIECE(header.wWidth,1,1),(undefined1)header.wWidth)) & 0xffff;
          pCVar15 = &bitmap->colorFormat;
          pCVar18 = &VStack_4c.colorFormat;
          for (iVar7 = 0xe; iVar7 != 0; iVar7 = iVar7 + -1) {
            pCVar18->nColorMode = pCVar15->nColorMode;
            pCVar15 = (ColorFormat *)&pCVar15->nBpp;
            pCVar18 = (ColorFormat *)&pCVar18->nBpp;
          }
          VStack_4c.nHeight = (int)CONCAT11(PIECE(header.wHeight,1,1),(undefined1)header.wHeight);
          pVVar10 = stdDisplay_VBufferNew(&VStack_4c,videoMem,sysMem,0);
          *bitmap->ppFrames = pVVar10;
          if (*bitmap->ppFrames == (VBuffer *)0x0) {
            (*g_pStd_HS->pAssertFail)
                      (s_Unable_to_allocate_memory__004e76d4,
                       s_C__grimjedi_Libs_Std_General_std_004e77d8,DAT_004e77d0 + 0x76);
          }
          iVar7 = stdDisplay_VBufferLock(*bitmap->ppFrames);
          if (iVar7 == 0) {
            (*g_pStd_HS->pAssertFail)
                      (s_Unable_to_lock_VBuffer_memory__004e76b4,
                       s_C__grimjedi_Libs_Std_General_std_004e77d8,DAT_004e77d0 + 0x7c);
          }
          iStack_104 = 0;
          uStack_114 = ((*bitmap->ppFrames)->format).nPitch;
          psVar16 = bitmap;
          pvVar4 = (*bitmap->ppFrames)->pPixels;
          if (CONCAT11(PIECE(header.wHeight,1,1),(undefined1)header.wHeight) != 0) {
            do {
              pvStack_13c = pvVar4;
              iVar7 = 0;
              if (0 < iStack_12c) {
                puStack_120 = aChannelType;
                do {
                  if (*puStack_120 == 0) {
                    iVar14 = 0;
                    if (CONCAT11(PIECE(header.wWidth,1,1),(undefined1)header.wWidth) != 0) {
                      psVar16 = (stdBitmap *)((int)pvStack_13c + 2);
                      do {
                        if (iStack_140 == iVar7) {
                          (*g_pStd_HS->pFread)
                                    (iVar6,(undefined1 *)((int)&psVar16[-1].ppFrames + 2),uStack_128
                                    );
                        }
                        if (iStack_138 == iVar7) {
                          (*g_pStd_HS->pFread)
                                    (iVar6,(undefined1 *)((int)&psVar16[-1].ppFrames + 3),uStack_118
                                    );
                        }
                        if (iStack_134 == iVar7) {
                          (*g_pStd_HS->pFread)(iVar6,psVar16,uStack_11c);
                        }
                        if (iStack_130 == iVar7) {
                          (*g_pStd_HS->pFread)(iVar6,auStack_100,uStack_124);
                        }
                        iVar14 = iVar14 + 1;
                        psVar16 = (stdBitmap *)(psVar16->aName + 3);
                      } while (iVar14 < (int)(CONCAT12((undefined1)header.wHeight,
                                                       CONCAT11(PIECE(header.wWidth,1,1),
                                                                (undefined1)header.wWidth)) & 0xffff
                                             ));
                    }
                  }
                  else {
                    iVar14 = 0;
                    if (CONCAT11(PIECE(header.wWidth,1,1),(undefined1)header.wWidth) != 0) {
                      do {
                        (*g_pStd_HS->pFread)(iVar6,&bStack_14b,1);
                        if (bStack_14b < 0x80) {
                          if (bStack_14b != 0xff) {
                            psVar16 = (stdBitmap *)(iVar14 * 3 + 2 + (int)pvStack_13c);
                            do {
                              if (iStack_140 == iVar7) {
                                (*g_pStd_HS->pFread)
                                          (iVar6,(undefined1 *)((int)&psVar16[-1].ppFrames + 2),
                                           uStack_128);
                              }
                              if (iStack_138 == iVar7) {
                                (*g_pStd_HS->pFread)
                                          (iVar6,(undefined1 *)((int)&psVar16[-1].ppFrames + 3),
                                           uStack_118);
                              }
                              if (iStack_134 == iVar7) {
                                (*g_pStd_HS->pFread)(iVar6,psVar16,uStack_11c);
                              }
                              if (iStack_130 == iVar7) {
                                (*g_pStd_HS->pFread)(iVar6,auStack_100,uStack_124);
                              }
                              iVar14 = iVar14 + 1;
                              psVar16 = (stdBitmap *)(psVar16->aName + 3);
                              bVar5 = bStack_14b - 1;
                              bVar19 = bStack_14b != 0;
                              bStack_14b = bVar5;
                            } while (bVar19);
                          }
                        }
                        else {
                          if (bStack_14b == 0x80) {
                            (*g_pStd_HS->pFread)(iVar6,&psStack_148,2);
                            psStack_148 = (stdBitmap *)
                                          (uint)CONCAT11((char)psStack_148,
                                                         (char)((uint)psStack_148 >> 8));
                          }
                          else {
                            psStack_148 = (stdBitmap *)
                                          (CONCAT22((short)((uint)psVar16 >> 0x10),
                                                    (ushort)bStack_14b) - 0x7f);
                          }
                          if (iStack_140 == iVar7) {
                            (*g_pStd_HS->pFread)(iVar6,&bStack_14a,uStack_128);
                          }
                          if (iStack_138 == iVar7) {
                            (*g_pStd_HS->pFread)(iVar6,&bStack_149,uStack_118);
                          }
                          if (iStack_134 == iVar7) {
                            (*g_pStd_HS->pFread)(iVar6,&uStack_141,uStack_11c);
                          }
                          if (iStack_130 == iVar7) {
                            (*g_pStd_HS->pFread)(iVar6,auStack_100,uStack_124);
                          }
                          sVar1 = (short)psStack_148;
                          psVar16 = (stdBitmap *)
                                    ((int)&psStack_148[0x210].colorFormat.dwRedShift + 3);
                          psStack_148 = psVar16;
                          if (sVar1 != 0) {
                            iVar11 = ((uint)psVar16 & 0xffff) + 1;
                            puVar12 = (undefined1 *)(iVar14 * 3 + 2 + (int)pvStack_13c);
                            iVar14 = iVar14 + iVar11;
                            do {
                              if (iStack_140 == iVar7) {
                                puVar12[-2] = bStack_14a;
                              }
                              if (iStack_138 == iVar7) {
                                puVar12[-1] = bStack_149;
                              }
                              if (iStack_134 == iVar7) {
                                *puVar12 = uStack_141;
                              }
                              puVar12 = puVar12 + 3;
                              iVar11 = iVar11 + -1;
                              psVar16 = (stdBitmap *)
                                        ((int)&psVar16[0x210].colorFormat.dwRedShift + 3);
                              psStack_148 = psVar16;
                            } while (iVar11 != 0);
                          }
                        }
                      } while (iVar14 < (int)(CONCAT12((undefined1)header.wHeight,
                                                       CONCAT11(PIECE(header.wWidth,1,1),
                                                                (undefined1)header.wWidth)) & 0xffff
                                             ));
                    }
                  }
                  iVar7 = iVar7 + 1;
                  puStack_120 = puStack_120 + 1;
                } while (iVar7 < iStack_12c);
              }
              iStack_104 = iStack_104 + 1;
              pvStack_13c = (void *)((int)pvStack_13c + uStack_114);
              pvVar4 = pvStack_13c;
            } while (iStack_104 <
                     (int)(uint)CONCAT11(PIECE(header.wHeight,1,1),(undefined1)header.wHeight));
          }
          stdDisplay_VBufferUnlock(*bitmap->ppFrames);
          (*g_pStd_HS->pFclose)(iVar6);
          return 1;
        }
        iVar7 = (*g_pStd_HS->pFread)(iVar6,&channel,4);
        if (iVar7 != 4) {
          return 0;
        }
      }
    }
    return 0;
  }
  return 0;
}
#undef VStack_4c
#undef auStack_100
#undef bStack_149
#undef bStack_14a
#undef iStack_104
#undef iStack_12c
#undef iStack_130
#undef iStack_134
#undef iStack_138
#undef iStack_140
#undef psStack_148
#undef puStack_120
#undef pvStack_13c
#undef uStack_110
#undef uStack_114
#undef uStack_118
#undef uStack_11c
#undef uStack_124
#undef uStack_128
#undef uStack_141

