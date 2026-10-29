/* GRIMFANDANGO.EXE :: rdpuppet.c
 * functions 0x0040cee0 .. 0x00451800 (16 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0040cee0  rdPuppet_BuildJointMatrices ---- */
void __cdecl rdPuppet_BuildJointMatrices(void *model,float *frame)

{
  int iVar1;
  undefined4 *puVar2;
  uint in_stack_0000000c;
  undefined4 *in_stack_00000010;
  
  if (*(uint *)(*(int *)((int)model + 4) + 0x54) <= in_stack_0000000c) {
    return;
  }
  puVar2 = (undefined4 *)(in_stack_0000000c * 0x30 + *(int *)((int)model + 0x20));
  for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
    *in_stack_00000010 = *puVar2;
    puVar2 = puVar2 + 1;
    in_stack_00000010 = in_stack_00000010 + 1;
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

/* ---- 0x00450780  rdPuppet_FadeOutTrack ---- */
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

/* ---- 0x004507e0  rdPuppet_AdvanceTrack ---- */
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


/* ---- 0x00450a90  rdPuppet_Advance ---- */
void __cdecl rdPuppet_Advance(void *puppet,float seconds)

{
  uint uVar1;
  float fVar2;
  uint *puVar3;
  uint track;
  
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
void __cdecl rdPuppet_UpdateFrame(void *model,float *frame)

{
  unsigned char _frame[0x90] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int *piVar3;
  float fVar4;
  bool bVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  float *pfVar9;
  int iVar10;
  uint *puVar11;
  uint uVar12;
  byte *pbVar13;
  int *piVar14;
  undefined4 *puVar15;
  undefined4 *puVar16;
  float10 fVar17;
  #define local_74 (*(float *)(_frame + (0x90 - 0x74)))
  #define local_70 (*(byte **)(_frame + (0x90 - 0x70)))
  #define local_6c (*(uint *)(_frame + (0x90 - 0x6c)))
  #define local_64 (*(int *)(_frame + (0x90 - 0x64)))
  #define local_60 (*(int *)(_frame + (0x90 - 0x60)))
  #define local_5c (*(int *)(_frame + (0x90 - 0x5c)))
  #define local_58 (*(int *)(_frame + (0x90 - 0x58)))
  #define local_54 (*(uint *)(_frame + (0x90 - 0x54)))
  #define local_50 (*(int *)(_frame + (0x90 - 0x50)))
  #define local_48 (*(float *)(_frame + (0x90 - 0x48)))
  #define local_44 (*(float *)(_frame + (0x90 - 0x44)))
  #define local_40 (*(float *)(_frame + (0x90 - 0x40)))
  #define local_3c (*(float *)(_frame + (0x90 - 0x3c)))
  #define local_38 (*(float *)(_frame + (0x90 - 0x38)))
  #define local_34 (*(float *)(_frame + (0x90 - 0x34)))
  #define local_30 (*(float *)(_frame + (0x90 - 0x30)))
  #define local_2c (*(float *)(_frame + (0x90 - 0x2c)))
  #define local_28 (*(float *)(_frame + (0x90 - 0x28)))
  #define local_24 (*(float *)(_frame + (0x90 - 0x24)))
  #define local_20 (*(float *)(_frame + (0x90 - 0x20)))
  #define local_1c (*(float *)(_frame + (0x90 - 0x1c)))
  #define local_18 (*(float *)(_frame + (0x90 - 0x18)))
  #define local_14 (*(float *)(_frame + (0x90 - 0x14)))
  #define local_10 (*(float *)(_frame + (0x90 - 0x10)))
  #define local_c (*(float *)(_frame + (0x90 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x90 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x90 - 0x4)))
  
  iVar2 = *(int *)((int)model + 4);
  piVar3 = *(int **)((int)model + 0x14);
  if (*(int *)((int)model + 0x18) == 0) {
    if ((piVar3 == (int *)0x0) || (*piVar3 != 0)) {
      uVar12 = 0;
      if (*(int *)(iVar2 + 0x54) != 0) {
        puVar7 = (undefined4 *)(*(int *)(iVar2 + 0x58) + 0x88);
        iVar10 = 0;
        do {
          puVar15 = puVar7;
          puVar16 = (undefined4 *)(iVar10 + *(int *)((int)model + 0x20));
          for (iVar6 = 0xc; iVar6 != 0; iVar6 = iVar6 + -1) {
            *puVar16 = *puVar15;
            puVar15 = puVar15 + 1;
            puVar16 = puVar16 + 1;
          }
          puVar7 = puVar7 + 0x2e;
          uVar12 = uVar12 + 1;
          iVar10 = iVar10 + 0x30;
        } while (uVar12 < *(uint *)(iVar2 + 0x54));
      }
    }
    else {
      local_64 = 6;
      pbVar13 = (byte *)(piVar3 + 2);
      do {
        if (*(int *)pbVar13 != 0) {
          iVar10 = *(int *)(pbVar13 + 0x128);
          local_70 = pbVar13 + 0x20;
          local_6c = 0;
          if (*(int *)(iVar10 + 0x38) != 0) {
            piVar14 = (int *)(*(int *)(iVar10 + 0x3c) + 0x24);
            do {
              bVar5 = false;
              if (*piVar14 != 0) {
                if ((uint)piVar14[-1] < 0x40) {
                  iVar6 = *(int *)(pbVar13 + piVar14[-1] * 4 + 0x20);
                }
                else {
                  iVar6 = 0;
                }
                iVar1 = *piVar14 + -1;
                if (iVar6 != iVar1) {
                  iVar8 = iVar6 + 1;
                  if (*(float *)(piVar14[1] + iVar8 * 0x38) <= *(float *)(pbVar13 + 0x120)) {
                    pfVar9 = (float *)(piVar14[1] + (iVar6 + 2) * 0x38);
                    do {
                      if (iVar8 == iVar1) {
                        bVar5 = true;
                      }
                      else if (*pfVar9 <= *(float *)(pbVar13 + 0x120)) {
                        iVar8 = iVar8 + 1;
                        pfVar9 = pfVar9 + 0xe;
                      }
                      else {
                        bVar5 = true;
                      }
                    } while (!bVar5);
                    if (local_6c < 0x40) {
                      *(int *)local_70 = iVar8;
                    }
                  }
                }
              }
              local_6c = local_6c + 1;
              local_70 = local_70 + 4;
              piVar14 = piVar14 + 0xb;
            } while (local_6c < *(uint *)(iVar10 + 0x38));
          }
        }
        pbVar13 = pbVar13 + 0x134;
        local_64 = local_64 + -1;
      } while (local_64 != 0);
      local_54 = 0;
      if (*(int *)(iVar2 + 0x54) != 0) {
        local_50 = 0;
        local_60 = 0;
        puVar11 = (uint *)(*(int *)(iVar2 + 0x58) + 0x44);
        do {
          local_3c = 0.0;
          local_38 = 0.0;
          local_5c = 0;
          local_6c = 0;
          local_74 = 0.0;
          local_70 = (byte *)0x0;
          local_34 = 0.0;
          local_48 = 0.0;
          local_18 = 0.0;
          local_c = 0.0;
          local_44 = 0.0;
          local_14 = 0.0;
          local_8 = 0.0;
          local_40 = 0.0;
          local_10 = 0.0;
          local_4 = 0.0;
          local_58 = 6;
          pbVar13 = (byte *)(piVar3 + 2);
          do {
            iVar10 = *(int *)(pbVar13 + 0x128);
            if (iVar10 != 0) {
              if ((puVar11[1] & *(uint *)(iVar10 + 0x2c)) == 0) {
                iVar6 = *(int *)(pbVar13 + 8);
              }
              else {
                iVar6 = *(int *)(pbVar13 + 0xc);
              }
              if ((((((*pbVar13 & 2) != 0) && (uVar12 = *puVar11, uVar12 < *(uint *)(iVar10 + 0x38))
                    ) && (iVar1 = *(int *)(iVar10 + 0x3c) + uVar12 * 0x2c,
                         *(int *)(iVar1 + 0x24) != 0)) &&
                  (((int)local_6c <= iVar6 && ((local_5c <= iVar6 || (local_74 < 1.0)))))) &&
                 (uVar12 < *(uint *)(iVar10 + 0x38))) {
                pfVar9 = (float *)(*(int *)(iVar1 + 0x28) +
                                  *(int *)(pbVar13 + uVar12 * 4 + 0x20) * 0x38);
                if ((*(uint *)(iVar10 + 0x24) & 0x100) == 0) {
                  fVar4 = *(float *)(pbVar13 + 0x120) - *pfVar9;
                }
                else {
                  fVar4 = 0.0;
                }
                if (((uint)pfVar9[1] & 1) == 0) {
                  local_24 = pfVar9[2];
                  local_20 = pfVar9[3];
                  local_1c = pfVar9[4];
                }
                else {
                  local_24 = pfVar9[8] * fVar4 + pfVar9[2];
                  local_20 = pfVar9[9] * fVar4 + pfVar9[3];
                  local_1c = pfVar9[10] * fVar4 + pfVar9[4];
                }
                if (((uint)pfVar9[1] & 2) == 0) {
                  local_30 = pfVar9[5];
                  local_2c = pfVar9[6];
                  local_28 = pfVar9[7];
                }
                else {
                  local_30 = pfVar9[0xb] * fVar4 + pfVar9[5];
                  local_2c = pfVar9[0xc] * fVar4 + pfVar9[6];
                  local_28 = pfVar9[0xd] * fVar4 + pfVar9[7];
                }
                local_24 = local_24 - (float)puVar11[0xb];
                local_20 = local_20 - (float)puVar11[0xc];
                local_1c = local_1c - (float)puVar11[0xd];
                local_2c = local_2c - (float)puVar11[0xf];
                local_28 = local_28 - (float)puVar11[0x10];
                fVar17 = (float10)Math_NormalizeAngle180(local_30 - (float)puVar11[0xe]);
                local_30 = (float)fVar17;
                fVar17 = (float10)Math_NormalizeAngle180(local_2c);
                local_2c = (float)fVar17;
                fVar17 = (float10)Math_NormalizeAngle180(local_28);
                local_28 = (float)fVar17;
                if (*(float *)(pbVar13 + 0x18) < 1.0) {
                  local_24 = *(float *)(pbVar13 + 0x18) * local_24;
                  local_20 = *(float *)(pbVar13 + 0x18) * local_20;
                  local_1c = *(float *)(pbVar13 + 0x18) * local_1c;
                  local_30 = *(float *)(pbVar13 + 0x18) * local_30;
                  local_2c = *(float *)(pbVar13 + 0x18) * local_2c;
                  local_28 = *(float *)(pbVar13 + 0x18) * local_28;
                }
                if (iVar6 == local_5c) {
                  local_3c = local_24 + local_3c;
                  local_38 = local_20 + local_38;
                  local_34 = local_1c + local_34;
                  local_48 = local_30 + local_48;
                  local_44 = local_2c + local_44;
                  local_40 = local_28 + local_40;
                  local_74 = local_74 + *(float *)(pbVar13 + 0x18);
                }
                else if (local_5c < iVar6) {
                  local_18 = local_3c;
                  local_14 = local_38;
                  local_10 = local_34;
                  local_c = local_48;
                  local_8 = local_44;
                  local_4 = local_40;
                  local_70 = PUN(byte *,(float)local_74);
                  local_3c = local_24;
                  local_38 = local_20;
                  local_34 = local_1c;
                  local_48 = local_30;
                  local_74 = *(float *)(pbVar13 + 0x18);
                  local_6c = local_5c;
                  local_44 = local_2c;
                  local_40 = local_28;
                  local_5c = iVar6;
                }
                else if ((int)local_6c < iVar6) {
                  local_18 = local_24;
                  local_14 = local_20;
                  local_10 = local_1c;
                  local_c = local_30;
                  local_8 = local_2c;
                  local_70 = *(byte **)(pbVar13 + 0x18);
                  local_4 = local_28;
                  local_6c = iVar6;
                }
                else {
                  local_18 = local_24 + local_18;
                  local_14 = local_20 + local_14;
                  local_10 = local_1c + local_10;
                  local_c = local_30 + local_c;
                  local_8 = local_2c + local_8;
                  local_4 = local_28 + local_4;
                  local_70 = PUN(byte *,(float)(PUN(float,local_70) + *(float *)(pbVar13 + 0x18)));
                }
              }
            }
            pbVar13 = pbVar13 + 0x134;
            local_58 = local_58 + -1;
          } while (local_58 != 0);
          if ((1.0 <= local_74) || (PUN(float,local_70) <= 0.0)) {
            if (1.0 < local_74) {
              local_74 = 1.0 / local_74;
              local_3c = local_3c * local_74;
              local_38 = local_38 * local_74;
              local_34 = local_34 * local_74;
              local_48 = local_48 * local_74;
              local_44 = local_44 * local_74;
              local_40 = local_40 * local_74;
            }
          }
          else {
            if (1.0 < PUN(float,local_70)) {
              fVar4 = 1.0 / PUN(float,local_70);
              local_18 = local_18 * fVar4;
              local_14 = local_14 * fVar4;
              local_10 = local_10 * fVar4;
              local_c = local_c * fVar4;
              local_8 = local_8 * fVar4;
              local_4 = local_4 * fVar4;
            }
            local_74 = 1.0 - local_74;
            local_3c = local_18 * local_74 + local_3c;
            local_38 = local_14 * local_74 + local_38;
            local_34 = local_10 * local_74 + local_34;
            local_48 = local_c * local_74 + local_48;
            local_44 = local_8 * local_74 + local_44;
            local_40 = local_4 * local_74 + local_40;
          }
          fVar17 = (float10)Math_NormalizeAngle180(local_48);
          local_48 = (float)fVar17;
          fVar17 = (float10)Math_NormalizeAngle180(local_44);
          local_44 = (float)fVar17;
          fVar17 = (float10)Math_NormalizeAngle180(local_40);
          local_3c = (float)puVar11[0xb] + local_3c;
          local_38 = (float)puVar11[0xc] + local_38;
          local_34 = (float)puVar11[0xd] + local_34;
          local_48 = (float)puVar11[0xe] + local_48;
          local_44 = (float)puVar11[0xf] + local_44;
          local_40 = (float)puVar11[0x10] + (float)fVar17;
          Angles_ToMatrix(local_50 + *(int *)((int)model + 0x20),&local_48,&local_3c);
          iVar10 = *(int *)((int)model + 0x24) + local_60;
          if (((*(float *)(*(int *)((int)model + 0x24) + local_60) != 0.0) ||
              (*(float *)(iVar10 + 4) != 0.0)) || (*(float *)(iVar10 + 8) != 0.0)) {
            Matrix_BuildTransform(local_50 + *(int *)((int)model + 0x20),iVar10);
          }
          local_54 = local_54 + 1;
          local_60 = local_60 + 0xc;
          local_50 = local_50 + 0x30;
          puVar11 = puVar11 + 0x2e;
        } while (local_54 < *(uint *)(iVar2 + 0x54));
      }
    }
    rdThing_BuildNodeMatrix(model,*(undefined4 *)(iVar2 + 0x58),frame);
    *(undefined4 *)((int)model + 0x1c) = DAT_004f5eb4;
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
#undef local_50
#undef local_54
#undef local_58
#undef local_5c
#undef local_60
#undef local_64
#undef local_6c
#undef local_70
#undef local_74
#undef local_8
#undef local_c


/* ---- 0x00451510  rdKeyframe_Interpolate ---- */
/* Blends keyframe node transforms into the puppet's output matrices (returns the weight) */

float10 rdKeyframe_Interpolate
                  (int *param_1,float *param_2,int param_3,uint param_4,int *param_5,float *param_6,
                  float *param_7,float *param_8,uint param_9,float param_10)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  int iVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  float *pfVar6;
  float *pfVar7;
  float10 fVar8;
  #define local_2c (*(float **)(_frame + (0x40 - 0x2c)))
  #define local_28 (*(float *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_c (*(float *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x40 - 0x4)))
  
  local_28 = 0.0;
  if (param_9 != 0) {
    local_2c = param_6;
    iVar5 = (int)param_6 - (int)param_5;
    iVar4 = (int)param_7 - (int)param_8;
    pfVar7 = (float *)((int)param_5 + 8);
    local_1c = param_9;
    do {
      local_24 = 0;
      *param_8 = *(float *)(iVar4 + (int)param_8);
      if (param_4 != 0) {
        param_5 = param_1;
        param_7 = param_2;
        pfVar6 = (float *)(param_3 + 8);
        do {
          iVar2 = *param_5;
          if (*(int *)(iVar2 + 4) < 2) {
            fVar3 = 0.0;
          }
          else {
            local_c = *param_7 - *local_2c;
            local_8 = *(float *)(((int)param_2 - param_3) + -4 + (int)pfVar6) -
                      *(float *)(iVar5 + -4 + (int)pfVar7);
            local_4 = *(float *)(((int)param_2 - param_3) + (int)pfVar6) -
                      *(float *)(iVar5 + (int)pfVar7);
            fVar3 = local_4 * local_4 + local_8 * local_8 + local_c * local_c;
          }
          if (fVar3 < *(float *)(iVar2 + 0x34) * *(float *)(iVar2 + 0x34)) {
            switch(*(undefined4 *)(iVar2 + 4)) {
            case 0:
            case 1:
              fVar3 = *pfVar6 * *pfVar7 + pfVar6[-1] * pfVar7[-1] + pfVar6[-2] * pfVar7[-2];
              if (0.0 < fVar3) {
                fVar3 = *(float *)(iVar2 + 0x18) * fVar3;
LAB_0045173f:
                *param_8 = fVar3 + *param_8;
              }
              break;
            case 2:
              fVar8 = (float10)((code *)Vec3_Normalize)(&local_c);
              fVar3 = *pfVar7 * local_4 + pfVar7[-1] * local_8 + pfVar7[-2] * local_c;
              if (0.0 < fVar3) {
                fVar3 = (*(float *)(iVar2 + 0x18) - (float)fVar8 * param_10) * fVar3;
                goto LAB_0045173f;
              }
              break;
            case 3:
              fVar8 = (float10)((code *)Vec3_Normalize)(&local_c);
              fVar3 = *pfVar6 * local_4 + pfVar6[-2] * local_c + pfVar6[-1] * local_8;
              if (*(float *)(iVar2 + 0x2c) < fVar3) {
                fVar1 = *(float *)(iVar2 + 0x18);
                if (fVar3 < *(float *)(iVar2 + 0x24)) {
                  fVar1 = (1.0 - (*(float *)(iVar2 + 0x24) - fVar3) * *(float *)(iVar2 + 0x30)) *
                          fVar1;
                }
                fVar3 = (fVar1 - (float)fVar8 * param_10) *
                        (*pfVar7 * *pfVar6 + pfVar6[-2] * pfVar7[-2] + pfVar6[-1] * pfVar7[-1]);
                goto LAB_0045173f;
              }
            }
          }
          if (1.0 < *param_8) {
            *param_8 = 1.0;
          }
          if (*param_8 == 1.0) break;
          param_5 = param_5 + 1;
          local_24 = local_24 + 1;
          param_7 = param_7 + 3;
          pfVar6 = pfVar6 + 3;
        } while (local_24 < param_4);
      }
      pfVar7 = pfVar7 + 3;
      local_28 = local_28 + *param_8;
      local_2c = local_2c + 3;
      param_8 = param_8 + 1;
      local_1c = local_1c - 1;
    } while (local_1c != 0);
  }
  return (float10)local_28 / (float10)param_9;
}
#undef local_1c
#undef local_24
#undef local_28
#undef local_2c
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x00451800  rdKeyframe_InterpolateNode ---- */
float10 rdKeyframe_InterpolateNode
                  (int *param_1,int param_2,undefined4 param_3,uint param_4,int param_5,
                  float *param_6,int param_7,float param_8)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int *piVar2;
  float fVar3;
  uint uVar4;
  float *pfVar5;
  float10 fVar6;
  #define local_10 (*(float *)(_frame + (0x20 - 0x10)))
  #define local_c (*(float *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x20 - 0x4)))
  
  uVar4 = 0;
  local_10 = 0.0;
  if (param_4 != 0) {
    pfVar5 = (float *)(param_2 + 8);
    do {
      iVar1 = *param_1;
      if (*(int *)(iVar1 + 8) != 0) {
        piVar2 = *(int **)(param_5 + 0x18);
        local_c = pfVar5[-2] - *(float *)(param_7 + *piVar2 * 0xc);
        local_8 = pfVar5[-1] - *(float *)(param_7 + 4 + *piVar2 * 0xc);
        local_4 = *pfVar5 - *(float *)(param_7 + 8 + *piVar2 * 0xc);
        if (local_4 * local_4 + local_8 * local_8 + local_c * local_c <
            *(float *)(iVar1 + 0x34) * *(float *)(iVar1 + 0x34)) {
          fVar6 = (float10)((code *)Vec3_Normalize)(&local_c);
          fVar3 = local_c * *param_6 + param_6[1] * local_8 + param_6[2] * local_4;
          if (0.0 < fVar3) {
            local_10 = (*(float *)(iVar1 + 0x18) - (float)fVar6 * param_8) * fVar3 + local_10;
          }
        }
      }
      if (1.0 <= local_10) break;
      uVar4 = uVar4 + 1;
      param_1 = param_1 + 1;
      pfVar5 = pfVar5 + 3;
    } while (uVar4 < param_4);
  }
  return (float10)local_10;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c

