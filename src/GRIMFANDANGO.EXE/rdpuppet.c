/* GRIMFANDANGO.EXE :: rdpuppet.c
 * functions 0x0040cee0 .. 0x00451800 (15 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0040cee0  rdPuppet_BuildJointMatrices ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void __cdecl rdPuppet_BuildJointMatrices(void *model,float *frame,uint param_3,uint param_4)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (*(uint *)(*(int *)((int)model + 4) + 0x54) <= param_3) {
    return;
  }
  puVar2 = (undefined4 *)(param_3 * 0x30 + *(int *)((int)model + 0x20));
  for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
    *(undefined4 *)param_4 = *puVar2;
    puVar2 = puVar2 + 1;
    param_4 = (uint)(param_4 + 4);
  }
  return;
}
#endif


/* ---- 0x00450500  rdPuppet_New ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
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
#endif


/* ---- 0x00450560  rdPuppet_Init ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
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
#endif


/* ---- 0x004505a0  rdPuppet_AddTrack ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
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
#endif


/* ---- 0x00450640  rdPuppet_StopTrack ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
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
#endif


/* ---- 0x004506a0  rdPuppet_SetTrackFlags ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
undefined4 rdPuppet_SetTrackFlags(int param_1,int param_2,uint param_3)

{
  uint *puVar1;
  
  puVar1 = (uint *)(param_1 + 8 + param_2 * 0x134);
  *puVar1 = *puVar1 | param_3;
  return 1;
}
#endif


/* ---- 0x004506d0  rdPuppet_SetTrackUserData ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Writes the last dword (+0x12c) of the track record */

void rdPuppet_SetTrackUserData(int param_1,int param_2,undefined4 param_3)

{
  *(undefined4 *)(param_1 + (param_2 + 1) * 0x134) = param_3;
  return;
}
#endif


/* ---- 0x004506f0  rdPuppet_PlayTrack ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Status bits: clears 0x10, sets 2, speed 1.0 */

undefined4 rdPuppet_PlayTrack(int param_1,int param_2)

{
  uint *puVar1;
  
  puVar1 = (uint *)(param_1 + 8 + param_2 * 0x134);
  *puVar1 = *(uint *)(param_1 + 8 + param_2 * 0x134) & 0xffffffef | 2;
  puVar1[6] = 0x3f800000;
  return 1;
}
#endif


/* ---- 0x00450720  rdPuppet_FadeInTrack ---- */
/* replaced by the hand-written version in build/overrides.c */
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
/* replaced by the hand-written version in build/overrides.c */
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
/* replaced by the hand-written version in build/overrides.c */
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
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  local_8 = 0;
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
            local_8 = (uint)ROUND(fVar2 / fVar3);
            puVar1[0x48] = (uint)((float)puVar1[0x48] -
                                 (float)*(uint *)(puVar1[0x4a] + 0x34) * (float)local_8);
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
        if ((float)local_8 == 0.0) {
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
        else if ((float)local_8 <= 1.0) {
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
/* replaced by the hand-written version in build/overrides.c */
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
/* replaced by the hand-written version in build/overrides.c */
#if 0
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
#endif


/* ---- 0x00450ba0  rdPuppet_UpdateFrame ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_88 */

void __cdecl rdPuppet_UpdateFrame(void *model,float *frame)

{
  unsigned char _frame[0xa0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  float fVar5;
  bool bVar6;
  int iVar7;
  undefined4 *puVar8;
  int iVar9;
  float *pfVar10;
  int iVar11;
  uint *puVar12;
  uint uVar13;
  byte *pbVar14;
  int *piVar15;
  undefined4 *puVar16;
  undefined4 *puVar17;
  float fVar18;
  #define local_88 (*(uint *)(_frame + (0xa0 - 0x88)))
  #define local_74 (*(uint *)(_frame + (0xa0 - 0x74)))
  #define local_70 (*(uint *)(_frame + (0xa0 - 0x70)))
  #define local_6c (*(uint *)(_frame + (0xa0 - 0x6c)))
  #define local_68 (*(uint *)(_frame + (0xa0 - 0x68)))
  #define local_64 (*(uint *)(_frame + (0xa0 - 0x64)))
  #define local_60 (*(uint *)(_frame + (0xa0 - 0x60)))
  #define local_5c (*(uint *)(_frame + (0xa0 - 0x5c)))
  #define local_58 (*(uint *)(_frame + (0xa0 - 0x58)))
  #define local_54 (*(uint *)(_frame + (0xa0 - 0x54)))
  #define local_50 (*(uint *)(_frame + (0xa0 - 0x50)))
  #define local_4c (*(uint *)(_frame + (0xa0 - 0x4c)))
  #define local_48 (*(uint *)(_frame + (0xa0 - 0x48)))
  #define local_44 (*(uint *)(_frame + (0xa0 - 0x44)))
  #define local_40 (*(uint *)(_frame + (0xa0 - 0x40)))
  #define local_3c (*(uint *)(_frame + (0xa0 - 0x3c)))
  #define local_38 (*(uint *)(_frame + (0xa0 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0xa0 - 0x34)))
  #define local_30 (*(uint *)(_frame + (0xa0 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0xa0 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0xa0 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0xa0 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0xa0 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0xa0 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0xa0 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0xa0 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0xa0 - 0x10)))
  #define local_c (*(uint *)(_frame + (0xa0 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0xa0 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0xa0 - 0x4)))
  
  iVar2 = *(int *)((int)model + 4);
  piVar3 = *(int **)((int)model + 0x14);
  if (*(int *)((int)model + 0x18) == 0) {
    if ((piVar3 == (int *)0x0) || (*piVar3 != 0)) {
      uVar13 = 0;
      if (*(int *)(iVar2 + 0x54) != 0) {
        puVar8 = (undefined4 *)(*(int *)(iVar2 + 0x58) + 0x88);
        iVar11 = 0;
        do {
          puVar16 = puVar8;
          puVar17 = (undefined4 *)(iVar11 + *(int *)((int)model + 0x20));
          for (iVar7 = 0xc; iVar7 != 0; iVar7 = iVar7 + -1) {
            *puVar17 = *puVar16;
            puVar16 = puVar16 + 1;
            puVar17 = puVar17 + 1;
          }
          puVar8 = puVar8 + 0x2e;
          uVar13 = uVar13 + 1;
          iVar11 = iVar11 + 0x30;
        } while (uVar13 < *(uint *)(iVar2 + 0x54));
      }
    }
    else {
      local_64 = 6;
      pbVar14 = (byte *)(piVar3 + 2);
      do {
        if (*(int *)pbVar14 != 0) {
          iVar11 = *(int *)(pbVar14 + 0x128);
          local_70 = (uint)(pbVar14 + 0x20);
          local_6c = 0;
          if (*(int *)(iVar11 + 0x38) != 0) {
            piVar15 = (int *)(*(int *)(iVar11 + 0x3c) + 0x24);
            do {
              bVar6 = false;
              if (*piVar15 != 0) {
                if ((uint)piVar15[-1] < 0x40) {
                  iVar7 = *(int *)(pbVar14 + piVar15[-1] * 4 + 0x20);
                }
                else {
                  iVar7 = 0;
                }
                iVar1 = *piVar15 + -1;
                if (iVar7 != iVar1) {
                  iVar9 = iVar7 + 1;
                  if (*(float *)(piVar15[1] + iVar9 * 0x38) <= *(float *)(pbVar14 + 0x120)) {
                    pfVar10 = (float *)(piVar15[1] + (iVar7 + 2) * 0x38);
                    do {
                      if (iVar9 == iVar1) {
                        bVar6 = true;
                      }
                      else if (*pfVar10 <= *(float *)(pbVar14 + 0x120)) {
                        iVar9 = iVar9 + 1;
                        pfVar10 = pfVar10 + 0xe;
                      }
                      else {
                        bVar6 = true;
                      }
                    } while (!bVar6);
                    if (local_6c < 0x40) {
                      *(int *)local_70 = iVar9;
                    }
                  }
                }
              }
              local_6c = local_6c + 1;
              local_70 = local_70 + 4;
              piVar15 = piVar15 + 0xb;
            } while (local_6c < *(uint *)(iVar11 + 0x38));
          }
        }
        pbVar14 = pbVar14 + 0x134;
        local_64 = local_64 - 1;
      } while (local_64 != 0);
      local_54 = 0;
      if (*(int *)(iVar2 + 0x54) != 0) {
        local_50 = 0;
        local_60 = 0;
        puVar12 = (uint *)(*(int *)(iVar2 + 0x58) + 0x44);
        do {
          local_3c = 0;
          local_38 = 0;
          local_5c = 0;
          local_6c = 0;
          local_74 = 0;
          local_70 = 0;
          local_34 = 0;
          local_48 = 0;
          local_18 = 0;
          local_c = 0;
          local_44 = 0;
          local_14 = 0;
          local_8 = 0;
          local_40 = 0;
          local_10 = 0;
          local_4 = 0;
          local_58 = 6;
          pbVar14 = (byte *)(piVar3 + 2);
          do {
            iVar11 = *(int *)(pbVar14 + 0x128);
            if (iVar11 != 0) {
              if ((puVar12[1] & *(uint *)(iVar11 + 0x2c)) == 0) {
                uVar13 = *(uint *)(pbVar14 + 8);
              }
              else {
                uVar13 = *(uint *)(pbVar14 + 0xc);
              }
              if ((((((*pbVar14 & 2) != 0) && (uVar4 = *puVar12, uVar4 < *(uint *)(iVar11 + 0x38)))
                   && (iVar7 = *(int *)(iVar11 + 0x3c) + uVar4 * 0x2c, *(int *)(iVar7 + 0x24) != 0))
                  && (((int)local_6c <= (int)uVar13 &&
                      (((int)local_5c <= (int)uVar13 || ((float)local_74 < 1.0)))))) &&
                 (uVar4 < *(uint *)(iVar11 + 0x38))) {
                pfVar10 = (float *)(*(int *)(iVar7 + 0x28) +
                                   *(int *)(pbVar14 + uVar4 * 4 + 0x20) * 0x38);
                if ((*(uint *)(iVar11 + 0x24) & 0x100) == 0) {
                  fVar18 = *(float *)(pbVar14 + 0x120) - *pfVar10;
                }
                else {
                  fVar18 = 0.0;
                }
                if (((uint)pfVar10[1] & 1) == 0) {
                  local_24 = (uint)pfVar10[2];
                  local_20 = (uint)pfVar10[3];
                  local_1c = (uint)pfVar10[4];
                }
                else {
                  local_24 = (uint)(pfVar10[8] * fVar18 + pfVar10[2]);
                  local_20 = (uint)(pfVar10[9] * fVar18 + pfVar10[3]);
                  local_1c = (uint)(pfVar10[10] * fVar18 + pfVar10[4]);
                }
                if (((uint)pfVar10[1] & 2) == 0) {
                  local_30 = (uint)pfVar10[5];
                  fVar5 = pfVar10[6];
                  fVar18 = pfVar10[7];
                }
                else {
                  local_30 = (uint)(pfVar10[0xb] * fVar18 + pfVar10[5]);
                  fVar5 = pfVar10[0xc] * fVar18 + pfVar10[6];
                  fVar18 = pfVar10[0xd] * fVar18 + pfVar10[7];
                }
                local_24 = (uint)((float)local_24 - (float)puVar12[0xb]);
                local_20 = (uint)((float)local_20 - (float)puVar12[0xc]);
                local_1c = (uint)((float)local_1c - (float)puVar12[0xd]);
                local_2c = (uint)(fVar5 - (float)puVar12[0xf]);
                local_28 = (uint)(fVar18 - (float)puVar12[0x10]);
                local_30 = (uint)Math_NormalizeAngle180((float)local_30 - (float)puVar12[0xe]);
                local_2c = (uint)Math_NormalizeAngle180((float)local_2c);
                local_28 = (uint)Math_NormalizeAngle180((float)local_28);
                if (*(float *)(pbVar14 + 0x18) < 1.0) {
                  local_24 = (uint)(*(float *)(pbVar14 + 0x18) * (float)local_24);
                  local_20 = (uint)(*(float *)(pbVar14 + 0x18) * (float)local_20);
                  local_1c = (uint)(*(float *)(pbVar14 + 0x18) * (float)local_1c);
                  local_30 = (uint)(*(float *)(pbVar14 + 0x18) * (float)local_30);
                  local_2c = (uint)(*(float *)(pbVar14 + 0x18) * (float)local_2c);
                  local_28 = (uint)(*(float *)(pbVar14 + 0x18) * (float)local_28);
                }
                if (uVar13 == local_5c) {
                  local_3c = (uint)((float)local_24 + (float)local_3c);
                  local_38 = (uint)((float)local_20 + (float)local_38);
                  local_34 = (uint)((float)local_1c + (float)local_34);
                  local_48 = (uint)((float)local_30 + (float)local_48);
                  local_44 = (uint)((float)local_2c + (float)local_44);
                  local_40 = (uint)((float)local_28 + (float)local_40);
                  local_74 = (uint)((float)local_74 + *(float *)(pbVar14 + 0x18));
                }
                else if ((int)local_5c < (int)uVar13) {
                  local_18 = local_3c;
                  local_14 = local_38;
                  local_10 = local_34;
                  local_c = local_48;
                  local_8 = local_44;
                  local_4 = local_40;
                  local_70 = local_74;
                  local_3c = local_24;
                  local_38 = local_20;
                  local_34 = local_1c;
                  local_48 = local_30;
                  local_74 = *(uint *)(pbVar14 + 0x18);
                  local_6c = local_5c;
                  local_44 = local_2c;
                  local_40 = local_28;
                  local_5c = uVar13;
                }
                else if ((int)local_6c < (int)uVar13) {
                  local_18 = local_24;
                  local_14 = local_20;
                  local_10 = local_1c;
                  local_c = local_30;
                  local_8 = local_2c;
                  local_70 = *(uint *)(pbVar14 + 0x18);
                  local_4 = local_28;
                  local_6c = uVar13;
                }
                else {
                  local_18 = (uint)((float)local_24 + (float)local_18);
                  local_14 = (uint)((float)local_20 + (float)local_14);
                  local_10 = (uint)((float)local_1c + (float)local_10);
                  local_c = (uint)((float)local_30 + (float)local_c);
                  local_8 = (uint)((float)local_2c + (float)local_8);
                  local_4 = (uint)((float)local_28 + (float)local_4);
                  local_70 = (uint)((float)local_70 + *(float *)(pbVar14 + 0x18));
                }
              }
            }
            pbVar14 = pbVar14 + 0x134;
            local_58 = local_58 - 1;
          } while (local_58 != 0);
          if ((1.0 <= (float)local_74) || ((float)local_70 <= 0.0)) {
            if (1.0 < (float)local_74) {
              fVar18 = 1.0 / (float)local_74;
              local_3c = (uint)((float)local_3c * fVar18);
              local_38 = (uint)((float)local_38 * fVar18);
              local_34 = (uint)((float)local_34 * fVar18);
              local_48 = (uint)((float)local_48 * fVar18);
              local_44 = (uint)((float)local_44 * fVar18);
              local_40 = (uint)((float)local_40 * fVar18);
            }
          }
          else {
            if (1.0 < (float)local_70) {
              fVar18 = 1.0 / (float)local_70;
              local_18 = (uint)((float)local_18 * fVar18);
              local_14 = (uint)((float)local_14 * fVar18);
              local_10 = (uint)((float)local_10 * fVar18);
              local_c = (uint)((float)local_c * fVar18);
              local_8 = (uint)((float)local_8 * fVar18);
              local_4 = (uint)((float)local_4 * fVar18);
            }
            fVar18 = 1.0 - (float)local_74;
            local_3c = (uint)((float)local_18 * fVar18 + (float)local_3c);
            local_38 = (uint)((float)local_14 * fVar18 + (float)local_38);
            local_34 = (uint)((float)local_10 * fVar18 + (float)local_34);
            local_48 = (uint)((float)local_c * fVar18 + (float)local_48);
            local_44 = (uint)((float)local_8 * fVar18 + (float)local_44);
            local_40 = (uint)((float)local_4 * fVar18 + (float)local_40);
          }
          local_48 = (uint)Math_NormalizeAngle180((float)local_48);
          local_44 = (uint)Math_NormalizeAngle180((float)local_44);
          fVar18 = Math_NormalizeAngle180((float)local_40);
          local_3c = (uint)((float)puVar12[0xb] + (float)local_3c);
          local_38 = (uint)((float)puVar12[0xc] + (float)local_38);
          local_34 = (uint)((float)puVar12[0xd] + (float)local_34);
          local_48 = (uint)((float)puVar12[0xe] + (float)local_48);
          local_44 = (uint)((float)puVar12[0xf] + (float)local_44);
          local_40 = (uint)((float)puVar12[0x10] + fVar18);
          Angles_ToMatrix(local_50 + *(int *)((int)model + 0x20),&local_48,&local_3c);
          iVar11 = *(int *)((int)model + 0x24) + local_60;
          if (((*(float *)(*(int *)((int)model + 0x24) + local_60) != 0.0) ||
              (*(float *)(iVar11 + 4) != 0.0)) || (*(float *)(iVar11 + 8) != 0.0)) {
            Matrix_BuildTransform(local_50 + *(int *)((int)model + 0x20),iVar11);
          }
          local_54 = local_54 + 1;
          local_60 = local_60 + 0xc;
          local_50 = local_50 + 0x30;
          puVar12 = puVar12 + 0x2e;
        } while (local_54 < *(uint *)(iVar2 + 0x54));
      }
    }
    rdThing_BuildNodeMatrix(model,*(undefined4 *)(iVar2 + 0x58),frame);
    *(uint *)((int)model + 0x1c) = UINT_004f5eb4;
  }
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
#undef local_64
#undef local_68
#undef local_6c
#undef local_70
#undef local_74
#undef local_8
#undef local_88
#undef local_c

#endif


/* ---- 0x00451800  rdKeyframe_InterpolateNode ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
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
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar4 = 0;
  local_10 = 0;
  if (param_4 != 0) {
    pfVar5 = (float *)(param_2 + 8);
    do {
      iVar1 = *param_1;
      if (*(int *)(iVar1 + 8) != 0) {
        piVar2 = *(int **)(param_5 + 0x18);
        local_c = (uint)(pfVar5[-2] - *(float *)(param_7 + *piVar2 * 0xc));
        local_8 = (uint)(pfVar5[-1] - *(float *)(param_7 + 4 + *piVar2 * 0xc));
        local_4 = (uint)(*pfVar5 - *(float *)(param_7 + 8 + *piVar2 * 0xc));
        if ((float)local_4 * (float)local_4 +
            (float)local_8 * (float)local_8 + (float)local_c * (float)local_c <
            *(float *)(iVar1 + 0x34) * *(float *)(iVar1 + 0x34)) {
          fVar6 = Vec3_Normalize((float *)&local_c);
          fVar3 = (float)local_c * *param_6 +
                  param_6[1] * (float)local_8 + param_6[2] * (float)local_4;
          if (0.0 < fVar3) {
            local_10 = (uint)((*(float *)(iVar1 + 0x18) - fVar6 * param_8) * fVar3 + (float)local_10
                             );
          }
        }
      }
      if (1.0 <= (float)local_10) {
        return (float)local_10;
      }
      uVar4 = uVar4 + 1;
      param_1 = param_1 + 1;
      pfVar5 = pfVar5 + 3;
    } while (uVar4 < param_4);
  }
  return (float)local_10;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c

#endif

