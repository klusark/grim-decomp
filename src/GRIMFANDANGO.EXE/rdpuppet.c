/* GRIMFANDANGO.EXE :: rdpuppet.c
 * functions 0x0040cee0 .. 0x004c0e70 (21 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0040cee0  rdPuppet_BuildJointMatrices ---- */
void __cdecl rdPuppet_BuildJointMatrices(void *model,float *frame,uint index,float *out)

{
  int iVar1;
  float *pfVar2;
  
  if (*(uint *)(*(int *)((int)model + 4) + 0x54) <= index) {
    return;
  }
  pfVar2 = (float *)(index * 0x30 + *(int *)((int)model + 0x20));
  for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
    *out = *pfVar2;
    pfVar2 = pfVar2 + 1;
    out = out + 1;
  }
  return;
}

/* ---- 0x00450500  rdPuppet_New ---- */
undefined4 * rdPuppet_New(void *param_1)

{
  undefined4 *puppet;
  int iVar1;
  undefined4 *puVar2;
  
  puppet = (undefined4 *)
           (*g_pSvcRdroid->pAlloc)
                     (0x740,s_C__grimjedi_Libs_RDroid_Engine_R_004ddddc,DAT_004dddd8 + 3);
  puVar2 = puppet;
  for (iVar1 = 0x1d0; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  if (puppet != (undefined4 *)0x0) {
    iVar1 = rdPuppet_Init(puppet,param_1);
    if (iVar1 != 0) {
      *(undefined4 **)((int)param_1 + 0x14) = puppet;
      return puppet;
    }
  }
  return (undefined4 *)0x0;
}

/* ---- 0x00450560  rdPuppet_Init ---- */
/* Six tracks of 0x134 bytes starting at +8; all stopped */

int __cdecl rdPuppet_Init(void *puppet,void *thing)

{
  undefined4 *puVar1;
  uint track;
  
  *(undefined4 *)puppet = 0;
  *(void **)((int)puppet + 4) = thing;
  track = 0;
  puVar1 = (undefined4 *)((int)puppet + 300);
  do {
    puVar1[-1] = 0;
    *puVar1 = 0;
    rdPuppet_StopTrack(puppet,track);
    puVar1 = puVar1 + 0x4d;
    track = track + 1;
  } while (track < 6);
  return 1;
}

/* ---- 0x004505a0  rdPuppet_AddTrack ---- */
/* Takes the first free track (status 0) and binds the keyframe to it */

uint __cdecl rdPuppet_AddTrack(void *puppet,uint keyframe,uint lowPri,uint highPri)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  uint track;
  
  track = 0;
  puVar3 = (uint *)((int)puppet + 8);
  puVar2 = puVar3;
  do {
    if (*puVar2 == 0) break;
    track = track + 1;
    puVar2 = puVar2 + 0x4d;
  } while (track < 6);
  if (5 < track) {
    track = 0;
    do {
      if (((*puVar3 & 8) != 0) && ((*puVar3 & 0x140) == 0)) {
        rdPuppet_StopTrack(puppet,track);
        break;
      }
      track = track + 1;
      puVar3 = puVar3 + 0x4d;
    } while (track < 6);
    if (5 < track) {
      return 0xffffffff;
    }
  }
  puVar3 = (uint *)((int)puppet + track * 0x134 + 8);
  uVar1 = *(uint *)(keyframe + 0x30);
  puVar3[0x4a] = keyframe;
  puVar3[2] = lowPri;
  puVar3[4] = uVar1;
  puVar3[6] = 0;
  puVar3[3] = highPri;
  *puVar3 = *puVar3 | 1;
  rdPuppet_ClearTrackNodes(puppet,track);
  return track;
}

/* ---- 0x00450640  rdPuppet_StopTrack ---- */
void __cdecl rdPuppet_StopTrack(void *puppet,int track)

{
  undefined4 *puVar1;
  code *pcVar2;
  
  puVar1 = (undefined4 *)((int)puppet + track * 0x134 + 8);
  pcVar2 = *(code **)((int)puppet + track * 0x134 + 0x134);
  if (pcVar2 != (code *)0x0) {
    (*pcVar2)(*(undefined4 *)(*(int *)((int)puppet + 4) + 0x48),track,0);
  }
  *puVar1 = 0;
  puVar1[0x4a] = 0;
  puVar1[0x4b] = 0;
  return;
}

/* ---- 0x004506a0  rdPuppet_SetTrackFlags ---- */
undefined4 rdPuppet_SetTrackFlags(int param_1,int param_2,uint param_3)

{
  uint *puVar1;
  
  puVar1 = (uint *)(param_1 + 8 + param_2 * 0x134);
  *puVar1 = *puVar1 | param_3;
  return 1;
}

/* ---- 0x004506d0  rdPuppet_SetTrackUserData ---- */
/* Writes the last dword (+0x12c) of the track record */

void rdPuppet_SetTrackUserData(int param_1,int param_2,undefined4 param_3)

{
  *(undefined4 *)(param_1 + (param_2 + 1) * 0x134) = param_3;
  return;
}

/* ---- 0x004506f0  rdPuppet_PlayTrack ---- */
/* Status bits: clears 0x10, sets 2, speed 1.0 */

undefined4 rdPuppet_PlayTrack(int param_1,int param_2)

{
  uint *puVar1;
  
  puVar1 = (uint *)(param_1 + 8 + param_2 * 0x134);
  *puVar1 = *(uint *)(param_1 + 8 + param_2 * 0x134) & 0xffffffef | 2;
  puVar1[6] = 0x3f800000;
  return 1;
}

/* ---- 0x00450720  rdPuppet_FadeInTrack ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
int __cdecl rdPuppet_FadeInTrack(void *puppet,int track,float seconds)

{
  uint *puVar1;
  
  puVar1 = (uint *)((int)puppet + track * 0x134 + 8);
  *puVar1 = *(uint *)((int)puppet + track * 0x134 + 8) & 0xfffffff7 | 6;
  if (0.0 < seconds) {
    puVar1[7] = (uint)(1.0 / seconds);
    return 1;
  }
  puVar1[7] = 0x3f800000;
  return 1;
}
#endif


/* ---- 0x00450780  rdPuppet_FadeOutTrack ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
int __cdecl rdPuppet_FadeOutTrack(void *puppet,int track,float seconds)

{
  uint *puVar1;
  
  puVar1 = (uint *)((int)puppet + track * 0x134 + 8);
  *puVar1 = *(uint *)((int)puppet + track * 0x134 + 8) & 0xfffffffb | 8;
  if (0.0 < seconds) {
    puVar1[7] = (uint)(1.0 / seconds);
    return 1;
  }
  puVar1[7] = 0x3f800000;
  return 1;
}
#endif


/* ---- 0x004507e0  rdPuppet_AdvanceTrack ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Advances the track time, handles fades and loops, stops finished tracks */

void __cdecl rdPuppet_AdvanceTrack(void *puppet,int track,float dt)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint *puVar1;
  float fVar2;
  float fVar3;
  bool bVar4;
  uint uVar5;
  uint uVar6;
  uint *puVar7;
  int iVar8;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x20 - 0x8)))
  
  local_8 = 0.0;
  bVar4 = false;
  iVar8 = *(int *)((int)puppet + track * 0x134 + 0x130);
  puVar1 = (uint *)((int)puppet + track * 0x134 + 8);
  if ((iVar8 != 0) && (dt != 0.0)) {
    fVar2 = dt + (float)puVar1[0x49];
    puVar1[0x48] = (uint)fVar2;
    fVar3 = (float)*(uint *)(iVar8 + 0x34);
    if (fVar3 <= fVar2) {
      uVar5 = *puVar1;
      if ((uVar5 & 0x20) == 0) {
        if ((uVar5 & 0x40) == 0) {
          if ((uVar5 & 0x80) == 0) {
            local_8 = ROUND(fVar2 / fVar3);
            puVar1[0x48] = (uint)((float)puVar1[0x48] -
                                 (float)*(uint *)(puVar1[0x4a] + 0x34) * local_8);
            uVar5 = *(uint *)(*(int *)(*(int *)((int)puppet + 4) + 4) + 0x54);
            if (0x3f < uVar5) {
              uVar5 = 0x40;
            }
            puVar7 = puVar1 + 8;
            for (; uVar5 != 0; uVar5 = uVar5 - 1) {
              *puVar7 = 0;
              puVar7 = puVar7 + 1;
            }
          }
          else {
            puVar1[0x48] = (uint)fVar3;
            rdPuppet_FadeOutTrack(puppet,track,0.25);
            *puVar1 = *puVar1 | 0x10;
          }
        }
        else {
          puVar1[0x48] = (uint)fVar3;
          *puVar1 = uVar5 | 0x10;
        }
      }
      else {
        puVar1[0x48] = (uint)fVar3;
        bVar4 = true;
      }
    }
    if (puVar1[0x4b] != 0) {
      uVar5 = puVar1[0x4a];
      iVar8 = *(int *)(uVar5 + 0x40);
      if (iVar8 != 0) {
        if (local_8 == 0.0) {
          uVar6 = 0;
          if (iVar8 != 0) {
            iVar8 = 0x44;
            do {
              if ((float)puVar1[0x48] < *(float *)(iVar8 + uVar5)) break;
              if (((float)puVar1[0x49] < *(float *)(iVar8 + uVar5)) || ((float)puVar1[0x49] == 0.0))
              {
                (*(code *)puVar1[0x4b])
                          (*(undefined4 *)(*(int *)((int)puppet + 4) + 0x48),track,
                           *(undefined4 *)(iVar8 + 0x20 + uVar5));
              }
              uVar5 = puVar1[0x4a];
              uVar6 = uVar6 + 1;
              iVar8 = iVar8 + 4;
            } while (uVar6 < *(uint *)(uVar5 + 0x40));
          }
        }
        else if (local_8 <= 1.0) {
          uVar6 = 0;
          if (iVar8 != 0) {
            iVar8 = 0x44;
            do {
              if (((float)puVar1[0x49] < *(float *)(iVar8 + uVar5)) ||
                 (*(float *)(iVar8 + uVar5) <= (float)puVar1[0x48])) {
                (*(code *)puVar1[0x4b])
                          (*(undefined4 *)(*(int *)((int)puppet + 4) + 0x48),track,
                           *(undefined4 *)(iVar8 + 0x20 + uVar5));
              }
              uVar5 = puVar1[0x4a];
              uVar6 = uVar6 + 1;
              iVar8 = iVar8 + 4;
            } while (uVar6 < *(uint *)(uVar5 + 0x40));
          }
        }
        else {
          uVar6 = 0;
          if (iVar8 != 0) {
            iVar8 = 100;
            do {
              (*(code *)puVar1[0x4b])
                        (*(undefined4 *)(*(int *)((int)puppet + 4) + 0x48),track,
                         *(undefined4 *)(iVar8 + uVar5));
              uVar5 = puVar1[0x4a];
              uVar6 = uVar6 + 1;
              iVar8 = iVar8 + 4;
            } while (uVar6 < *(uint *)(uVar5 + 0x40));
          }
        }
      }
    }
    if (bVar4) {
      rdPuppet_StopTrack(puppet,track);
      return;
    }
    puVar1[0x49] = puVar1[0x48];
  }
  return;
}
#undef local_8
#undef local_c

#endif


/* ---- 0x00450a90  rdPuppet_Advance ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_14 */

void __cdecl rdPuppet_Advance(void *puppet,float seconds)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  float fVar2;
  uint *puVar3;
  uint track;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  
  if (*(int *)puppet == 0) {
    track = 0;
    puVar3 = (uint *)((int)puppet + 8);
    do {
      uVar1 = *puVar3;
      if ((uVar1 != 0) && ((uVar1 & 0x200) == 0)) {
        if ((uVar1 & 0x10) == 0) {
          rdPuppet_AdvanceTrack(puppet,track,(float)puVar3[4] * seconds);
        }
        if ((*puVar3 & 4) == 0) {
          if (((*puVar3 & 8) != 0) &&
             (fVar2 = (float)puVar3[6] - (float)puVar3[7] * seconds, puVar3[6] = (uint)fVar2,
             fVar2 <= 0.0)) {
            if ((*puVar3 & 0x100) == 0) {
              rdPuppet_StopTrack(puppet,track);
            }
            else {
              *puVar3 = *puVar3 & 0xfffffff7 | 0x10;
            }
          }
        }
        else {
          fVar2 = (float)puVar3[7] * seconds + (float)puVar3[6];
          puVar3[6] = (uint)fVar2;
          if (1.0 <= fVar2) {
            puVar3[6] = 0x3f800000;
            *puVar3 = *puVar3 & 0xfffffffb;
          }
        }
      }
      track = track + 1;
      puVar3 = puVar3 + 0x4d;
    } while (track < 6);
  }
  return;
}
#undef local_14

#endif


/* ---- 0x00450b50  rdPuppet_ClearTrackNodes ---- */
/* Zeroes the 64 node weights of a track and marks it status 3 */

void rdPuppet_ClearTrackNodes(int param_1,int param_2)

{
  undefined4 *puVar1;
  uint uVar2;
  undefined4 *puVar3;
  
  puVar1 = (undefined4 *)(param_1 + 8 + param_2 * 0x134);
  uVar2 = *(uint *)(*(int *)(*(int *)(param_1 + 4) + 4) + 0x54);
  if (0x3f < uVar2) {
    uVar2 = 0x40;
  }
  puVar3 = puVar1 + 8;
  for (; uVar2 != 0; uVar2 = uVar2 - 1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  puVar1[0x48] = 0;
  puVar1[0x49] = 0;
  *puVar1 = 3;
  return;
}

/* ---- 0x00450ba0  rdPuppet_UpdateFrame ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_88 */

void __cdecl rdPuppet_UpdateFrame(void *model,float *frame)

{
  unsigned char _frame[0xa0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int *piVar5;
  float fVar6;
  float fVar7;
  bool bVar8;
  int iVar9;
  undefined4 *puVar10;
  int iVar11;
  float *pfVar12;
  int iVar13;
  uint *puVar14;
  uint uVar15;
  byte *pbVar16;
  int *piVar17;
  undefined4 *puVar18;
  undefined4 *puVar19;
  float fVar20;
  #define local_88 (*(uint *)(_frame + (0xa0 - 0x88)))
  #define local_74 (*(float (*)[3])(_frame + (0xa0 - 0x74)))
  #define local_68 (*(uint *)(_frame + (0xa0 - 0x68)))
  #define local_64 (*(uint *)(_frame + (0xa0 - 0x64)))
  #define local_60 (*(uint *)(_frame + (0xa0 - 0x60)))
  #define local_5c (*(float (*)[3])(_frame + (0xa0 - 0x5c)))
  #define local_50 (*(uint *)(_frame + (0xa0 - 0x50)))
  #define local_4c (*(uint *)(_frame + (0xa0 - 0x4c)))
  #define local_48 (*(float (*)[3])(_frame + (0xa0 - 0x48)))
  #define local_3c (*(float (*)[3])(_frame + (0xa0 - 0x3c)))
  #define local_30 (*(float (*)[3])(_frame + (0xa0 - 0x30)))
  #define local_24 (*(float (*)[3])(_frame + (0xa0 - 0x24)))
  #define local_18 (*(float (*)[3])(_frame + (0xa0 - 0x18)))
  #define local_c (*(float (*)[3])(_frame + (0xa0 - 0xc)))
  
  iVar4 = *(int *)((int)model + 4);
  piVar5 = *(int **)((int)model + 0x14);
  if (*(int *)((int)model + 0x18) == 0) {
    if ((piVar5 == (int *)0x0) || (*piVar5 != 0)) {
      uVar15 = 0;
      if (*(int *)(iVar4 + 0x54) != 0) {
        puVar10 = (undefined4 *)(*(int *)(iVar4 + 0x58) + 0x88);
        iVar13 = 0;
        do {
          puVar18 = puVar10;
          puVar19 = (undefined4 *)(iVar13 + *(int *)((int)model + 0x20));
          for (iVar9 = 0xc; iVar9 != 0; iVar9 = iVar9 + -1) {
            *puVar19 = *puVar18;
            puVar18 = puVar18 + 1;
            puVar19 = puVar19 + 1;
          }
          puVar10 = puVar10 + 0x2e;
          uVar15 = uVar15 + 1;
          iVar13 = iVar13 + 0x30;
        } while (uVar15 < *(uint *)(iVar4 + 0x54));
      }
    }
    else {
      local_64 = 6;
      pbVar16 = (byte *)(piVar5 + 2);
      do {
        if (*(int *)pbVar16 != 0) {
          iVar13 = *(int *)(pbVar16 + 0x128);
          local_74[1] = PUN(float,(pbVar16 + 0x20));
          local_74[2] = 0.0;
          if (*(int *)(iVar13 + 0x38) != 0) {
            piVar17 = (int *)(*(int *)(iVar13 + 0x3c) + 0x24);
            do {
              bVar8 = false;
              if (*piVar17 != 0) {
                if ((uint)piVar17[-1] < 0x40) {
                  iVar9 = *(int *)(pbVar16 + piVar17[-1] * 4 + 0x20);
                }
                else {
                  iVar9 = 0;
                }
                iVar1 = *piVar17 + -1;
                if (iVar9 != iVar1) {
                  iVar11 = iVar9 + 1;
                  if (*(float *)(piVar17[1] + iVar11 * 0x38) <= *(float *)(pbVar16 + 0x120)) {
                    pfVar12 = (float *)(piVar17[1] + (iVar9 + 2) * 0x38);
                    do {
                      if (iVar11 == iVar1) {
                        bVar8 = true;
                      }
                      else if (*pfVar12 <= *(float *)(pbVar16 + 0x120)) {
                        iVar11 = iVar11 + 1;
                        pfVar12 = pfVar12 + 0xe;
                      }
                      else {
                        bVar8 = true;
                      }
                    } while (!bVar8);
                    if ((uint)local_74[2] < 0x40) {
                      *PUN(int *,(float)local_74[1]) = iVar11;
                    }
                  }
                }
              }
              local_74[2] = (float)((int)local_74[2] + 1);
              local_74[1] = (float)((int)local_74[1] + 4);
              piVar17 = piVar17 + 0xb;
            } while ((uint)local_74[2] < (uint)*(float *)(iVar13 + 0x38));
          }
        }
        pbVar16 = pbVar16 + 0x134;
        local_64 = local_64 - 1;
      } while (local_64 != 0);
      local_5c[2] = 0.0;
      if (*(int *)(iVar4 + 0x54) != 0) {
        local_50 = 0;
        local_60 = 0;
        puVar14 = (uint *)(*(int *)(iVar4 + 0x58) + 0x44);
        do {
          local_3c[0] = 0.0;
          local_3c[1] = 0.0;
          local_5c[0] = 0.0;
          local_74[2] = 0.0;
          local_74[0] = 0.0;
          local_74[1] = 0.0;
          local_3c[2] = 0.0;
          local_48[0] = 0.0;
          local_18[0] = 0.0;
          local_c[0] = 0.0;
          local_48[1] = 0.0;
          local_18[1] = 0.0;
          local_c[1] = 0.0;
          local_48[2] = 0.0;
          local_18[2] = 0.0;
          local_c[2] = 0.0;
          local_5c[1] = 8.40779e-45;
          pbVar16 = (byte *)(piVar5 + 2);
          do {
            iVar13 = *(int *)(pbVar16 + 0x128);
            if (iVar13 != 0) {
              if ((puVar14[1] & *(uint *)(iVar13 + 0x2c)) == 0) {
                fVar20 = *(float *)(pbVar16 + 8);
              }
              else {
                fVar20 = *(float *)(pbVar16 + 0xc);
              }
              if ((((((*pbVar16 & 2) != 0) && (uVar15 = *puVar14, uVar15 < *(uint *)(iVar13 + 0x38))
                    ) && (iVar9 = *(int *)(iVar13 + 0x3c) + uVar15 * 0x2c,
                         *(int *)(iVar9 + 0x24) != 0)) &&
                  (((int)local_74[2] <= (int)fVar20 &&
                   (((int)local_5c[0] <= (int)fVar20 || (local_74[0] < 1.0)))))) &&
                 (uVar15 < *(uint *)(iVar13 + 0x38))) {
                pfVar12 = (float *)(*(int *)(iVar9 + 0x28) +
                                   *(int *)(pbVar16 + uVar15 * 4 + 0x20) * 0x38);
                if ((*(uint *)(iVar13 + 0x24) & 0x100) == 0) {
                  fVar7 = *(float *)(pbVar16 + 0x120) - *pfVar12;
                }
                else {
                  fVar7 = 0.0;
                }
                if (((uint)pfVar12[1] & 1) == 0) {
                  local_24[0] = pfVar12[2];
                  local_24[1] = pfVar12[3];
                  local_24[2] = pfVar12[4];
                }
                else {
                  local_24[0] = pfVar12[8] * fVar7 + pfVar12[2];
                  local_24[1] = pfVar12[9] * fVar7 + pfVar12[3];
                  local_24[2] = pfVar12[10] * fVar7 + pfVar12[4];
                }
                if (((uint)pfVar12[1] & 2) == 0) {
                  local_30[0] = pfVar12[5];
                  fVar6 = pfVar12[6];
                  fVar7 = pfVar12[7];
                }
                else {
                  local_30[0] = pfVar12[0xb] * fVar7 + pfVar12[5];
                  fVar6 = pfVar12[0xc] * fVar7 + pfVar12[6];
                  fVar7 = pfVar12[0xd] * fVar7 + pfVar12[7];
                }
                local_24[0] = local_24[0] - (float)puVar14[0xb];
                local_24[1] = local_24[1] - (float)puVar14[0xc];
                local_24[2] = local_24[2] - (float)puVar14[0xd];
                fVar2 = (float)puVar14[0xf];
                fVar3 = (float)puVar14[0x10];
                local_30[0] = Math_NormalizeAngle180(local_30[0] - (float)puVar14[0xe]);
                local_30[1] = Math_NormalizeAngle180(fVar6 - fVar2);
                local_30[2] = Math_NormalizeAngle180(fVar7 - fVar3);
                if (*(float *)(pbVar16 + 0x18) < 1.0) {
                  local_24[0] = *(float *)(pbVar16 + 0x18) * local_24[0];
                  local_24[1] = *(float *)(pbVar16 + 0x18) * local_24[1];
                  local_24[2] = *(float *)(pbVar16 + 0x18) * local_24[2];
                  local_30[0] = *(float *)(pbVar16 + 0x18) * local_30[0];
                  local_30[1] = *(float *)(pbVar16 + 0x18) * local_30[1];
                  local_30[2] = *(float *)(pbVar16 + 0x18) * local_30[2];
                }
                if (fVar20 == local_5c[0]) {
                  local_3c[0] = local_24[0] + local_3c[0];
                  local_3c[1] = local_24[1] + local_3c[1];
                  local_3c[2] = local_24[2] + local_3c[2];
                  local_48[0] = local_30[0] + local_48[0];
                  local_48[1] = local_30[1] + local_48[1];
                  local_48[2] = local_30[2] + local_48[2];
                  local_74[0] = local_74[0] + *(float *)(pbVar16 + 0x18);
                }
                else if ((int)local_5c[0] < (int)fVar20) {
                  local_18[0] = local_3c[0];
                  local_18[1] = local_3c[1];
                  local_18[2] = local_3c[2];
                  local_c[0] = local_48[0];
                  local_c[1] = local_48[1];
                  local_c[2] = local_48[2];
                  local_74[1] = local_74[0];
                  local_3c[0] = local_24[0];
                  local_3c[1] = local_24[1];
                  local_3c[2] = local_24[2];
                  local_48[0] = local_30[0];
                  local_74[0] = *(float *)(pbVar16 + 0x18);
                  local_74[2] = local_5c[0];
                  local_48[1] = local_30[1];
                  local_48[2] = local_30[2];
                  local_5c[0] = fVar20;
                }
                else if ((int)local_74[2] < (int)fVar20) {
                  local_18[0] = local_24[0];
                  local_18[1] = local_24[1];
                  local_18[2] = local_24[2];
                  local_c[0] = local_30[0];
                  local_c[1] = local_30[1];
                  local_74[1] = *(float *)(pbVar16 + 0x18);
                  local_c[2] = local_30[2];
                  local_74[2] = fVar20;
                }
                else {
                  local_18[0] = local_24[0] + local_18[0];
                  local_18[1] = local_24[1] + local_18[1];
                  local_18[2] = local_24[2] + local_18[2];
                  local_c[0] = local_30[0] + local_c[0];
                  local_c[1] = local_30[1] + local_c[1];
                  local_c[2] = local_30[2] + local_c[2];
                  local_74[1] = local_74[1] + *(float *)(pbVar16 + 0x18);
                }
              }
            }
            pbVar16 = pbVar16 + 0x134;
            local_5c[1] = (float)((int)local_5c[1] + -1);
          } while (local_5c[1] != 0.0);
          if ((1.0 <= local_74[0]) || (local_74[1] <= 0.0)) {
            if (1.0 < local_74[0]) {
              fVar20 = 1.0 / local_74[0];
              local_3c[0] = local_3c[0] * fVar20;
              local_3c[1] = local_3c[1] * fVar20;
              local_3c[2] = local_3c[2] * fVar20;
              local_48[0] = local_48[0] * fVar20;
              local_48[1] = local_48[1] * fVar20;
              local_48[2] = local_48[2] * fVar20;
            }
          }
          else {
            if (1.0 < local_74[1]) {
              fVar20 = 1.0 / local_74[1];
              local_18[0] = local_18[0] * fVar20;
              local_18[1] = local_18[1] * fVar20;
              local_18[2] = local_18[2] * fVar20;
              local_c[0] = local_c[0] * fVar20;
              local_c[1] = local_c[1] * fVar20;
              local_c[2] = local_c[2] * fVar20;
            }
            fVar20 = 1.0 - local_74[0];
            local_3c[0] = local_18[0] * fVar20 + local_3c[0];
            local_3c[1] = local_18[1] * fVar20 + local_3c[1];
            local_3c[2] = local_18[2] * fVar20 + local_3c[2];
            local_48[0] = local_c[0] * fVar20 + local_48[0];
            local_48[1] = local_c[1] * fVar20 + local_48[1];
            local_48[2] = local_c[2] * fVar20 + local_48[2];
          }
          local_48[0] = Math_NormalizeAngle180(local_48[0]);
          local_48[1] = Math_NormalizeAngle180(local_48[1]);
          fVar20 = Math_NormalizeAngle180(local_48[2]);
          local_3c[0] = (float)puVar14[0xb] + local_3c[0];
          local_3c[1] = (float)puVar14[0xc] + local_3c[1];
          local_3c[2] = (float)puVar14[0xd] + local_3c[2];
          local_48[0] = (float)puVar14[0xe] + local_48[0];
          local_48[1] = (float)puVar14[0xf] + local_48[1];
          local_48[2] = (float)puVar14[0x10] + fVar20;
          Angles_ToMatrix(local_50 + *(int *)((int)model + 0x20),local_48,local_3c);
          iVar13 = *(int *)((int)model + 0x24) + local_60;
          if (((*(float *)(*(int *)((int)model + 0x24) + local_60) != 0.0) ||
              (*(float *)(iVar13 + 4) != 0.0)) || (*(float *)(iVar13 + 8) != 0.0)) {
            Matrix_BuildTransform(local_50 + *(int *)((int)model + 0x20),iVar13);
          }
          local_5c[2] = (float)((int)local_5c[2] + 1);
          local_60 = local_60 + 0xc;
          local_50 = local_50 + 0x30;
          puVar14 = puVar14 + 0x2e;
        } while ((uint)local_5c[2] < (uint)*(float *)(iVar4 + 0x54));
      }
    }
    rdThing_BuildNodeMatrix(model,*(undefined4 *)(iVar4 + 0x58),frame);
    *(uint *)((int)model + 0x1c) = UINT_004f5eb4;
  }
  return;
}
#undef local_18
#undef local_24
#undef local_30
#undef local_3c
#undef local_48
#undef local_4c
#undef local_50
#undef local_5c
#undef local_60
#undef local_64
#undef local_68
#undef local_74
#undef local_88
#undef local_c

#endif


/* ---- 0x00451800  rdKeyframe_InterpolateNode ---- */
float __cdecl
rdKeyframe_InterpolateNode
          (int *param_1,int param_2,uint param_3,uint param_4,int param_5,float *param_6,int param_7
          ,float param_8)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int *piVar2;
  float fVar3;
  uint uVar4;
  float *pfVar5;
  float fVar6;
  #define local_10 (*(float (*)[3])(_frame + (0x20 - 0x10)))
  #define local_4 (*(float *)(_frame + (0x20 - 0x4)))
  
  uVar4 = 0;
  local_10[0] = 0.0;
  if (param_4 != 0) {
    pfVar5 = (float *)(param_2 + 8);
    do {
      iVar1 = *param_1;
      if (*(int *)(iVar1 + 8) != 0) {
        piVar2 = *(int **)(param_5 + 0x18);
        local_10[1] = pfVar5[-2] - *(float *)(param_7 + *piVar2 * 0xc);
        local_10[2] = pfVar5[-1] - *(float *)(param_7 + 4 + *piVar2 * 0xc);
        fVar3 = *pfVar5 - *(float *)(param_7 + 8 + *piVar2 * 0xc);
        if (fVar3 * fVar3 + local_10[2] * local_10[2] + local_10[1] * local_10[1] <
            *(float *)(iVar1 + 0x34) * *(float *)(iVar1 + 0x34)) {
          fVar6 = Vec3_Normalize(local_10 + 1);
          fVar3 = local_10[1] * *param_6 + param_6[1] * local_10[2] + param_6[2] * fVar3;
          if (0.0 < fVar3) {
            local_10[0] = (*(float *)(iVar1 + 0x18) - fVar6 * param_8) * fVar3 + local_10[0];
          }
        }
      }
      if (1.0 <= local_10[0]) {
        return local_10[0];
      }
      uVar4 = uVar4 + 1;
      param_1 = param_1 + 1;
      pfVar5 = pfVar5 + 3;
    } while (uVar4 < param_4);
  }
  return local_10[0];
}
#undef local_10
#undef local_4


/* ---- 0x004c0630  rdKeyframe_NewEntry ---- */
/* Clears a 0x84-byte keyframe record and names it UNKNOWN. Source file Rdkeyframe.c
   (C:\grimjedi\Libs\RDroid\Engine\Rdkeyframe.c). */

void rdKeyframe_NewEntry(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = param_1;
  for (iVar1 = 0x21; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  strncpy(param_1,s_UNKNOWN_004ddb8c,0x1f);
  *(undefined1 *)((int)param_1 + 0x1f) = 0;
  return;
}

/* ---- 0x004c0660  rdKeyframe_Load ---- */
/* Loads an animation: custom loader hook if installed, else allocates the 0x84-byte record; the
   magic 'KEYF' selects rdKeyframe_LoadBinary, anything else rdKeyframe_LoadText. Source file
   Rdkeyframe.c (C:\grimjedi\Libs\RDroid\Engine\Rdkeyframe.c). */

int rdKeyframe_Load(char *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  undefined4 uVar5;
  
  pcVar4 = param_1;
  if (UINT_008d364c != 0) {
    iVar1 = (*(code *)UINT_008d364c)(param_1);
    return iVar1;
  }
  iVar1 = (*g_pSvcRdroid->pFopen)(param_1,&DAT_004ddb18);
  if (iVar1 != 0) {
    iVar2 = (*g_pSvcRdroid->pAlloc)
                      (0x84,s_C__grimjedi_Libs_RDroid_Engine_R_004f0f14,DAT_004f0f08 + 0x11);
    if (iVar2 != 0) {
      (*g_pSvcRdroid->pFread)(iVar1,&param_1,4);
      if (param_1 == (char *)0x4b455946) {
        iVar3 = rdKeyframe_LoadBinary(iVar1,iVar2);
        if (iVar3 != 0) {
          uVar5 = 0x1f;
          pcVar4 = Str_FileNameFromPath(pcVar4);
          strncpy(iVar2,pcVar4,uVar5);
          *(undefined1 *)(iVar2 + 0x1f) = 0;
          (*g_pSvcRdroid->pFclose)(iVar1);
          return iVar2;
        }
        (*g_pSvcRdroid->pFclose)(iVar1);
        rdKeyframe_Free(iVar2);
        return 0;
      }
      (*g_pSvcRdroid->pFclose)(iVar1);
      iVar1 = rdKeyframe_LoadText(pcVar4,iVar2);
      if (iVar1 != 0) {
        return iVar2;
      }
    }
    rdKeyframe_Free(iVar2);
  }
  return 0;
}

/* ---- 0x004c0770  rdKeyframe_LoadText ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Parser of the text .key format (flags, type, frames, fps, joints, entries; stdConffile). Source
   file Rdkeyframe.c (C:\grimjedi\Libs\RDroid\Engine\Rdkeyframe.c). */

undefined4 rdKeyframe_LoadText(char *param_1,int param_2)

{
  unsigned char _frame[0x80] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  undefined4 *puVar5;
  byte *pbVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  byte *pbVar10;
  bool bVar11;
  undefined4 uVar12;
  #define uStack_68 (*(uint *)(_frame + (0x80 - 0x68)))
  #define iStack_64 (*(int *)(_frame + (0x80 - 0x64)))
  #define iStack_60 (*(int *)(_frame + (0x80 - 0x60)))
  #define uStack_5c (*(uint *)(_frame + (0x80 - 0x5c)))
  #define local_58 (*(uint *)(_frame + (0x80 - 0x58)))
  #define uStack_54 (*(undefined4 *)(_frame + (0x80 - 0x54)))
  #define uStack_50 (*(undefined4 *)(_frame + (0x80 - 0x50)))
  #define uStack_4c (*(undefined4 *)(_frame + (0x80 - 0x4c)))
  #define uStack_48 (*(undefined4 *)(_frame + (0x80 - 0x48)))
  #define uStack_44 (*(undefined4 *)(_frame + (0x80 - 0x44)))
  #define uStack_40 (*(undefined4 *)(_frame + (0x80 - 0x40)))
  #define uStack_3c (*(undefined4 *)(_frame + (0x80 - 0x3c)))
  #define uStack_38 (*(undefined4 *)(_frame + (0x80 - 0x38)))
  #define uStack_34 (*(undefined4 *)(_frame + (0x80 - 0x34)))
  #define uStack_30 (*(undefined4 *)(_frame + (0x80 - 0x30)))
  #define uStack_2c (*(undefined4 *)(_frame + (0x80 - 0x2c)))
  #define uStack_28 (*(undefined4 *)(_frame + (0x80 - 0x28)))
  #define auStack_24 (*(undefined1 (*)[4])(_frame + (0x80 - 0x24)))
  #define auStack_20 (*(undefined1 (*)[32])(_frame + (0x80 - 0x20)))
  
  iVar2 = param_2;
  rdKeyframe_NewEntry(param_2);
  uVar12 = 0x1f;
  pcVar3 = Str_FileNameFromPath(param_1);
  strncpy(iVar2,pcVar3,uVar12);
  *(undefined1 *)(iVar2 + 0x1f) = 0;
  iVar4 = ((code *)stdConffile_OpenRead)(param_1);
  if (iVar4 == 0) {
    return 0;
  }
  iVar4 = stdConffile_ReadLine();
  if (iVar4 != 0) {
    iVar4 = sscanf((char *)UINT_00900520,s_section___s_004ddd64,&DAT_009056c0);
    if (iVar4 == 1) {
      iVar4 = stdConffile_ReadLine();
      if (iVar4 != 0) {
        iVar4 = sscanf((char *)UINT_00900520,s_flags__x_004f0ff0,iVar2 + 0x24);
        if (iVar4 == 1) {
          iVar4 = stdConffile_ReadLine();
          if (iVar4 != 0) {
            iVar4 = sscanf((char *)UINT_00900520,s_type__x_004f0fe4,iVar2 + 0x2c);
            if (iVar4 == 1) {
              iVar4 = stdConffile_ReadLine();
              if (iVar4 != 0) {
                iVar4 = sscanf((char *)UINT_00900520,s_frames__d_004f0fd8,iVar2 + 0x34);
                if (iVar4 == 1) {
                  iVar4 = stdConffile_ReadLine();
                  if (iVar4 != 0) {
                    iVar4 = sscanf((char *)UINT_00900520,s_fps__f_004f0fd0,&local_58);
                    if (iVar4 == 1) {
                      *(uint *)(iVar2 + 0x30) = local_58;
                      iVar4 = stdConffile_ReadLine();
                      if (iVar4 != 0) {
                        iVar4 = sscanf((char *)UINT_00900520,s_joints__d_004f0fc4,&param_2);
                        if (iVar4 == 1) {
                          puVar5 = (undefined4 *)
                                   (*g_pSvcRdroid->pAlloc)
                                             (param_2 * 0x2c,
                                              s_C__grimjedi_Libs_RDroid_Engine_R_004f0f14,
                                              DAT_004f0f0c + 0x42);
                          *(undefined4 **)(iVar2 + 0x3c) = puVar5;
                          if (puVar5 != (undefined4 *)0x0) {
                            for (uVar9 = param_2 * 0xb & 0x3fffffff; uVar9 != 0; uVar9 = uVar9 - 1)
                            {
                              *puVar5 = 0;
                              puVar5 = puVar5 + 1;
                            }
                            for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
                              *(undefined1 *)puVar5 = 0;
                              puVar5 = (undefined4 *)((int)puVar5 + 1);
                            }
                            *(int *)(iVar2 + 0x28) = param_2;
                            *(int *)(iVar2 + 0x38) = param_2;
                            iVar4 = stdConffile_ReadLine();
                            if (iVar4 != 0) {
                              iVar4 = sscanf((char *)UINT_00900520,s_section___s_004ddd64,
                                             &DAT_009056c0);
                              if (iVar4 == 1) {
                                pbVar10 = &DAT_004f0fbc;
                                pbVar6 = &DAT_009056c0;
                                do {
                                  bVar1 = *pbVar6;
                                  bVar11 = bVar1 < *pbVar10;
                                  if (bVar1 != *pbVar10) {
LAB_004c099a:
                                    iVar4 = (1 - (uint)bVar11) - (uint)(bVar11 != 0);
                                    goto LAB_004c099f;
                                  }
                                  if (bVar1 == 0) break;
                                  bVar1 = pbVar6[1];
                                  bVar11 = bVar1 < pbVar10[1];
                                  if (bVar1 != pbVar10[1]) goto LAB_004c099a;
                                  pbVar6 = pbVar6 + 2;
                                  pbVar10 = pbVar10 + 2;
                                } while (bVar1 != 0);
                                iVar4 = 0;
LAB_004c099f:
                                if (iVar4 == 0) {
                                  iVar4 = stdConffile_ReadLine();
                                  if (iVar4 == 0) goto LAB_004c0cbf;
                                  iVar4 = sscanf((char *)UINT_00900520,s_markers__d_004f0fb0,
                                                 &uStack_68);
                                  if ((iVar4 != 1) || (8 < uStack_68)) goto LAB_004c0cbf;
                                  uVar9 = 0;
                                  *(uint *)(iVar2 + 0x40) = uStack_68;
                                  if (uStack_68 != 0) {
                                    iVar4 = iVar2 + 0x44;
                                    do {
                                      iVar7 = stdConffile_ReadLine();
                                      if (iVar7 == 0) goto LAB_004c0cbf;
                                      iVar7 = sscanf((char *)UINT_00900520,s__f__d_004f0fa8,iVar4,
                                                     iVar4 + 0x20);
                                      if (iVar7 != 2) goto LAB_004c0cbf;
                                      uVar9 = uVar9 + 1;
                                      iVar4 = iVar4 + 4;
                                    } while (uVar9 < uStack_68);
                                  }
                                  iVar4 = stdConffile_ReadLine();
                                  if (iVar4 == 0) goto LAB_004c0cbf;
                                  iVar4 = sscanf((char *)UINT_00900520,s_section___s_004ddd64,
                                                 &DAT_009056c0);
                                  if (iVar4 != 1) goto LAB_004c0cbf;
                                }
                                iVar4 = stdConffile_ReadLine();
                                if (iVar4 != 0) {
                                  iVar4 = sscanf((char *)UINT_00900520,s_nodes__d_004f0f9c,
                                                 &uStack_5c);
                                  if (iVar4 == 1) {
                                    param_1 = (char *)0x0;
                                    if (uStack_5c == 0) {
                                      stdConffile_Close();
                                      return 1;
                                    }
                                    while( true ) {
                                      iVar4 = stdConffile_ReadLine();
                                      if (iVar4 == 0) break;
                                      iVar4 = sscanf((char *)UINT_00900520,s_node__d_004f0f90,
                                                     &iStack_64);
                                      if (iVar4 != 1) break;
                                      iVar4 = stdConffile_ReadLine();
                                      if (iVar4 == 0) break;
                                      iVar4 = sscanf((char *)UINT_00900520,s_mesh_name__s_004f0f80,
                                                     auStack_20);
                                      if (iVar4 != 1) break;
                                      iVar4 = *(int *)(iVar2 + 0x3c) + iStack_64 * 0x2c;
                                      strncpy(iVar4,auStack_20,0x1f);
                                      *(undefined1 *)(iVar4 + 0x1f) = 0;
                                      iVar7 = stdConffile_ReadLine();
                                      if (iVar7 == 0) break;
                                      iVar7 = sscanf((char *)UINT_00900520,s_entries__d_004f0f74,
                                                     &iStack_60);
                                      if (iVar7 != 1) break;
                                      *(int *)(iVar4 + 0x20) = iStack_64;
                                      *(int *)(iVar4 + 0x24) = iStack_60;
                                      iVar7 = (*g_pSvcRdroid->pAlloc)
                                                        (iStack_60 * 0x38,
                                                         s_C__grimjedi_Libs_RDroid_Engine_R_004f0f14
                                                         ,DAT_004f0f0c + 0x9b);
                                      *(int *)(iVar4 + 0x28) = iVar7;
                                      if (iVar7 == 0) break;
                                      uVar9 = 0;
                                      if (*(int *)(iVar4 + 0x24) != 0) {
                                        do {
                                          iVar8 = stdConffile_ReadLine();
                                          if (iVar8 == 0) goto LAB_004c0cbf;
                                          iVar8 = sscanf((char *)UINT_00900520,
                                                         s__d___f__x__f__f__f__f__f__f_004f0f54,
                                                         auStack_24,iVar7,iVar7 + 4,&uStack_54,
                                                         &uStack_50,&uStack_4c,&uStack_48,&uStack_44
                                                         ,&uStack_40);
                                          if (iVar8 != 9) goto LAB_004c0cbf;
                                          *(undefined4 *)(iVar7 + 8) = uStack_54;
                                          *(undefined4 *)(iVar7 + 0xc) = uStack_50;
                                          *(undefined4 *)(iVar7 + 0x10) = uStack_4c;
                                          *(undefined4 *)(iVar7 + 0x14) = uStack_48;
                                          *(undefined4 *)(iVar7 + 0x18) = uStack_44;
                                          *(undefined4 *)(iVar7 + 0x1c) = uStack_40;
                                          iVar8 = stdConffile_ReadLine();
                                          if (iVar8 == 0) goto LAB_004c0cbf;
                                          iVar8 = sscanf((char *)UINT_00900520,
                                                         s__f__f__f__f__f__f_004f0f40,&uStack_3c,
                                                         &uStack_38,&uStack_34,&uStack_30,&uStack_2c
                                                         ,&uStack_28);
                                          if (iVar8 != 6) goto LAB_004c0cbf;
                                          *(undefined4 *)(iVar7 + 0x20) = uStack_3c;
                                          *(undefined4 *)(iVar7 + 0x24) = uStack_38;
                                          *(undefined4 *)(iVar7 + 0x28) = uStack_34;
                                          *(undefined4 *)(iVar7 + 0x2c) = uStack_30;
                                          *(undefined4 *)(iVar7 + 0x30) = uStack_2c;
                                          *(undefined4 *)(iVar7 + 0x34) = uStack_28;
                                          iVar7 = iVar7 + 0x38;
                                          uVar9 = uVar9 + 1;
                                        } while (uVar9 < *(uint *)(iVar4 + 0x24));
                                      }
                                      param_1 = (char *)((int)param_1 + 1);
                                      if (uStack_5c <= param_1) {
                                        stdConffile_Close();
                                        return 1;
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
LAB_004c0cbf:
  stdConffile_Close();
  return 0;
}
#undef auStack_20
#undef auStack_24
#undef iStack_60
#undef iStack_64
#undef local_58
#undef uStack_28
#undef uStack_2c
#undef uStack_30
#undef uStack_34
#undef uStack_38
#undef uStack_3c
#undef uStack_40
#undef uStack_44
#undef uStack_48
#undef uStack_4c
#undef uStack_50
#undef uStack_54
#undef uStack_5c
#undef uStack_68

#endif


/* ---- 0x004c0ce0  rdKeyframe_LoadBinary ---- */
/* Reader of the binary 'KEYF' animation format. Source file Rdkeyframe.c
   (C:\grimjedi\Libs\RDroid\Engine\Rdkeyframe.c). */

undefined4 rdKeyframe_LoadBinary(undefined4 param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  
  iVar2 = param_2;
  (*g_pSvcRdroid->pFread)(param_1,param_2,0x84);
  puVar3 = (undefined4 *)
           (*g_pSvcRdroid->pAlloc)
                     (*(int *)(param_2 + 0x38) * 0x2c,s_C__grimjedi_Libs_RDroid_Engine_R_004f0f14,
                      DAT_004f0f10 + 0x16);
  *(undefined4 **)(param_2 + 0x3c) = puVar3;
  if (puVar3 == (undefined4 *)0x0) {
LAB_004c0e2c:
    (*g_pSvcRdroid->pFclose)(param_1);
    return 0;
  }
  piVar1 = (int *)(param_2 + 0x38);
  param_2 = 0;
  for (uVar6 = *piVar1 * 0xb & 0x3fffffff; uVar6 != 0; uVar6 = uVar6 - 1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  for (iVar7 = 0; iVar7 != 0; iVar7 = iVar7 + -1) {
    *(undefined1 *)puVar3 = 0;
    puVar3 = (undefined4 *)((int)puVar3 + 1);
  }
  if (0 < *(int *)(iVar2 + 0x38)) {
    iVar7 = 0;
    do {
      (*g_pSvcRdroid->pFread)(param_1,*(int *)(iVar2 + 0x3c) + iVar7,0x2c);
      iVar9 = 0;
      iVar5 = *(int *)(*(int *)(iVar2 + 0x3c) + 0x24 + iVar7);
      if (iVar5 == 0) {
        *(undefined4 *)(*(int *)(iVar2 + 0x3c) + iVar7 + 0x28) = 0;
      }
      else {
        uVar4 = (*g_pSvcRdroid->pAlloc)
                          (iVar5 * 0x38,s_C__grimjedi_Libs_RDroid_Engine_R_004f0f14,
                           DAT_004f0f10 + 0x21);
        *(undefined4 *)(*(int *)(iVar2 + 0x3c) + 0x28 + iVar7) = uVar4;
        iVar5 = *(int *)(iVar2 + 0x3c) + iVar7;
        if (*(int *)(*(int *)(iVar2 + 0x3c) + 0x28 + iVar7) == 0) goto LAB_004c0e2c;
        if (0 < *(int *)(iVar5 + 0x24)) {
          iVar8 = 0;
          do {
            (*g_pSvcRdroid->pFread)(param_1,*(int *)(iVar5 + 0x28) + iVar8,0x38);
            iVar5 = *(int *)(iVar2 + 0x3c) + iVar7;
            iVar9 = iVar9 + 1;
            iVar8 = iVar8 + 0x38;
          } while (iVar9 < *(int *)(iVar5 + 0x24));
        }
      }
      param_2 = param_2 + 1;
      iVar7 = iVar7 + 0x2c;
    } while (param_2 < *(int *)(iVar2 + 0x38));
  }
  (*g_pSvcRdroid->pFclose)(param_1);
  return 1;
}

/* ---- 0x004c0e40  rdKeyframe_Free ---- */
/* Frees a keyframe (custom free hook if installed, else rdKeyframe_FreeEntry and the record).
   Source file Rdkeyframe.c (C:\grimjedi\Libs\RDroid\Engine\Rdkeyframe.c). */

void rdKeyframe_Free(int param_1)

{
  if (param_1 != 0) {
    if (UINT_008d3650 != 0) {
      (*(code *)UINT_008d3650)();
      return;
    }
    rdKeyframe_FreeEntry(param_1);
    (*g_pSvcRdroid->pFree)(param_1);
  }
  return;
}

/* ---- 0x004c0e70  rdKeyframe_FreeEntry ---- */
/* Frees the per-joint node arrays of a keyframe record. Source file Rdkeyframe.c
   (C:\grimjedi\Libs\RDroid\Engine\Rdkeyframe.c). */

void rdKeyframe_FreeEntry(int param_1)

{
  int *piVar1;
  uint uVar2;
  
  if (*(int *)(param_1 + 0x3c) != 0) {
    uVar2 = 0;
    if (*(int *)(param_1 + 0x38) != 0) {
      piVar1 = (int *)(*(int *)(param_1 + 0x3c) + 0x28);
      do {
        if (*piVar1 != 0) {
          (*g_pSvcRdroid->pFree)(*piVar1);
          *piVar1 = 0;
        }
        piVar1 = piVar1 + 0xb;
        uVar2 = uVar2 + 1;
      } while (uVar2 < *(uint *)(param_1 + 0x38));
    }
    (*g_pSvcRdroid->pFree)(*(undefined4 *)(param_1 + 0x3c));
    *(undefined4 *)(param_1 + 0x3c) = 0;
  }
  return;
}
