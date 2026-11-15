/* GRIMFANDANGO.EXE :: rdpuppet.c
 * functions 0x0040cee0 .. 0x004c0e70 (20 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0040cee0  rdPuppet_BuildJointMatrices ---- */
void __cdecl rdPuppet_BuildJointMatrices(rdThing *thing,float *frame,uint index,float *out)

{
  int iVar1;
  float *pfVar2;
  
  if ((uint)thing->pModel->nNumHierarchyNodes <= index) {
    return;
  }
  pfVar2 = thing->pHierarchyMatrices + index * 0xc;
  for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
    *out = *pfVar2;
    pfVar2 = pfVar2 + 1;
    out = out + 1;
  }
  return;
}

/* ---- 0x00450500  rdPuppet_New ---- */
undefined4 * __cdecl rdPuppet_New(rdThing *thing)

{
  undefined4 *puppet;
  int iVar1;
  undefined4 *puVar2;
  
  puppet = (undefined4 *)
           (*g_pRdroid_HS->pAlloc)
                     (0x740,s_C__grimjedi_Libs_RDroid_Engine_R_004ddddc,DAT_004dddd8 + 3);
  puVar2 = puppet;
  for (iVar1 = 0x1d0; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  if (puppet != (undefined4 *)0x0) {
    iVar1 = rdPuppet_NewEntry(puppet,thing);
    if (iVar1 != 0) {
      thing->pPuppet = puppet;
      return puppet;
    }
  }
  return (undefined4 *)0x0;
}

/* ---- 0x00450560  rdPuppet_NewEntry ---- */
/* Six tracks of 0x134 bytes starting at +8; all stopped Original name rdPuppet_NewEntry (the
   remaster's GrimFandango (Linux): the only unmatched callee of rdPuppet_New; 1 matched neighbours
   agree, 0 disagree); was rdPuppet_Init. */

int __cdecl rdPuppet_NewEntry(void *puppet,void *thing)

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
    rdPuppet_RemoveTrack(puppet,track);
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
        rdPuppet_RemoveTrack(puppet,track);
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
  rdPuppet_ResetTrack((int)puppet,track);
  return track;
}

/* ---- 0x00450640  rdPuppet_RemoveTrack ---- */
/* Original name rdPuppet_RemoveTrack (the remaster's GrimFandango (Linux): aligned call in
   rdPuppet_AddTrack, rdPuppet_AdvanceTrack, rdPuppet_NewEntry); was rdPuppet_StopTrack. */

void __cdecl rdPuppet_RemoveTrack(void *puppet,int track)

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

/* ---- 0x004506a0  rdPuppet_SetStatus ---- */
/* Original name rdPuppet_SetStatus (the remaster's GrimFandango (Linux): aligned call in
   KeyframeChanger); was rdPuppet_SetTrackFlags. */

uint __cdecl rdPuppet_SetStatus(int puppet,int track,uint flags)

{
  uint *puVar1;
  
  puVar1 = (uint *)(puppet + 8 + track * 0x134);
  *puVar1 = *puVar1 | flags;
  return 1;
}

/* ---- 0x004506d0  rdPuppet_SetCallback ---- */
/* Writes the last dword (+0x12c) of the track record Original name rdPuppet_SetCallback (the
   remaster's GrimFandango (Linux): aligned call in KeyframeChanger); was rdPuppet_SetTrackUserData.
    */

void __cdecl rdPuppet_SetCallback(int puppet,int track,uint callback)

{
  *(uint *)(puppet + (track + 1) * 0x134) = callback;
  return;
}

/* ---- 0x004506f0  rdPuppet_PlayTrack ---- */
/* Status bits: clears 0x10, sets 2, speed 1.0 */

uint __cdecl rdPuppet_PlayTrack(int puppet,int track)

{
  uint *puVar1;
  
  puVar1 = (uint *)(puppet + 8 + track * 0x134);
  *puVar1 = *(uint *)(puppet + 8 + track * 0x134) & 0xffffffef | 2;
  puVar1[6] = 0x3f800000;
  return 1;
}

/* ---- 0x00450720  rdPuppet_FadeInTrack ---- */
/* Ported to C (build/overrides_asm_s4.c): read against the assembly only, NOT differentially tested
   (docs/notes/asm_s*.md). */

int __cdecl rdPuppet_FadeInTrack(void *puppet,int track,float seconds)

{
  uint *puVar1;
  
  puVar1 = (uint *)((int)puppet + track * 0x134 + 8);
  *puVar1 = *(uint *)((int)puppet + track * 0x134 + 8) & 0xfffffff7 | 6;
  if (0.0f < seconds) {
    puVar1[7] = PUN(uint,(float)(1.0f / seconds));
    return 1;
  }
  puVar1[7] = 0x3f800000;
  return 1;
}

/* ---- 0x00450780  rdPuppet_FadeOutTrack ---- */
/* Ported to C (build/overrides_asm_s4.c): read against the assembly only, NOT differentially tested
   (docs/notes/asm_s*.md). */

int __cdecl rdPuppet_FadeOutTrack(void *puppet,int track,float seconds)

{
  uint *puVar1;
  
  puVar1 = (uint *)((int)puppet + track * 0x134 + 8);
  *puVar1 = *(uint *)((int)puppet + track * 0x134 + 8) & 0xfffffffb | 8;
  if (0.0f < seconds) {
    puVar1[7] = PUN(uint,(float)(1.0f / seconds));
    return 1;
  }
  puVar1[7] = 0x3f800000;
  return 1;
}

/* ---- 0x004507e0  rdPuppet_AdvanceTrack ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Advances the track time, handles fades and loops, stops finished tracks */

void __cdecl rdPuppet_AdvanceTrack(void *puppet,int track,float dt)

{
  uint *puVar1;
  float fVar2;
  float fVar3;
  bool bVar4;
  uint uVar5;
  uint uVar6;
  uint *puVar7;
  int iVar8;
  uint local_c;
  float local_8;
  
  local_8 = 0.0f;
  bVar4 = false;
  iVar8 = *(int *)((int)puppet + track * 0x134 + 0x130);
  puVar1 = (uint *)((int)puppet + track * 0x134 + 8);
  if ((iVar8 != 0) && (dt != 0.0f)) {
    fVar2 = dt + (float)puVar1[0x49];
    puVar1[0x48] = PUN(uint,(float)fVar2);
    fVar3 = (float)*(uint *)(iVar8 + 0x34);
    if (fVar3 <= fVar2) {
      uVar5 = *puVar1;
      if ((uVar5 & 0x20) == 0) {
        if ((uVar5 & 0x40) == 0) {
          if ((uVar5 & 0x80) == 0) {
            local_8 = ROUND_DOWN(fVar2 / fVar3);
            puVar1[0x48] = PUN(uint,(float)((float)puVar1[0x48] -
                                 (float)*(uint *)(puVar1[0x4a] + 0x34) * local_8));
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
            puVar1[0x48] = PUN(uint,(float)fVar3);
            rdPuppet_FadeOutTrack(puppet,track,0.25f);
            *puVar1 = *puVar1 | 0x10;
          }
        }
        else {
          puVar1[0x48] = PUN(uint,(float)fVar3);
          *puVar1 = uVar5 | 0x10;
        }
      }
      else {
        puVar1[0x48] = PUN(uint,(float)fVar3);
        bVar4 = true;
      }
    }
    if (puVar1[0x4b] != 0) {
      uVar5 = puVar1[0x4a];
      iVar8 = *(int *)(uVar5 + 0x40);
      if (iVar8 != 0) {
        if (local_8 == 0.0f) {
          uVar6 = 0;
          if (iVar8 != 0) {
            iVar8 = 0x44;
            do {
              if ((float)puVar1[0x48] < *(float *)(iVar8 + uVar5)) break;
              if (((float)puVar1[0x49] < *(float *)(iVar8 + uVar5)) || ((float)puVar1[0x49] == 0.0f))
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
        else if (local_8 <= 1.0f) {
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
      rdPuppet_RemoveTrack(puppet,track);
      return;
    }
    puVar1[0x49] = puVar1[0x48];
  }
  return;
}
#endif


/* ---- 0x00450a90  rdPuppet_UpdateTracks ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_14 */
/* Ported to C (build/overrides_asm_s4.c): read against the assembly only, NOT differentially tested
   (docs/notes/asm_s*.md). Original name rdPuppet_UpdateTracks (the remaster's GrimFandango (Linux):
   the only unmatched caller of rdPuppet_AdvanceTrack; 1 matched neighbours agree, 0 disagree); was
   rdPuppet_Advance. */

void __cdecl rdPuppet_UpdateTracks(void *puppet,float seconds)

{
  uint uVar1;
  float fVar2;
  uint *puVar3;
  uint track;
  uint local_14;
  
  if (*(int *)puppet == 0) {
    track = 0;
    puVar3 = (uint *)((int)puppet + 8);
    do {
      uVar1 = *puVar3;
      if ((uVar1 != 0) && ((uVar1 & 0x200) == 0)) {
        if ((uVar1 & 0x10) == 0) {
          rdPuppet_AdvanceTrack(puppet,track,PUN(float,puVar3[4]) * seconds);
        }
        if ((*puVar3 & 4) == 0) {
          if (((*puVar3 & 8) != 0) &&
             (fVar2 = PUN(float,puVar3[6]) - PUN(float,puVar3[7]) * seconds, puVar3[6] = PUN(uint,(float)fVar2),
             fVar2 <= 0.0f)) {
            if ((*puVar3 & 0x100) == 0) {
              rdPuppet_RemoveTrack(puppet,track);
            }
            else {
              *puVar3 = *puVar3 & 0xfffffff7 | 0x10;
            }
          }
        }
        else {
          fVar2 = PUN(float,puVar3[7]) * seconds + PUN(float,puVar3[6]);
          puVar3[6] = PUN(uint,(float)fVar2);
          if (1.0f <= fVar2) {
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
#endif


/* ---- 0x00450b50  rdPuppet_ResetTrack ---- */
/* Zeroes the 64 node weights of a track and marks it status 3 Original name rdPuppet_ResetTrack
   (the remaster's GrimFandango (Linux): aligned call in KeyframeChanger, rdPuppet_AddTrack); was
   rdPuppet_ClearTrackNodes. */

void __cdecl rdPuppet_ResetTrack(int puppet,int track)

{
  undefined4 *puVar1;
  uint uVar2;
  undefined4 *puVar3;
  
  puVar1 = (undefined4 *)(puppet + 8 + track * 0x134);
  uVar2 = *(uint *)(*(int *)(*(int *)(puppet + 4) + 4) + 0x54);
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
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_88 */

void __cdecl rdPuppet_UpdateFrame(rdThing *thing,float *frame)

{
  unsigned char _frame[0xa0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  float fVar2;
  float fVar3;
  rdModel3 *prVar4;
  int *piVar5;
  float fVar6;
  float fVar7;
  bool bVar8;
  int iVar9;
  float *pfVar10;
  int iVar11;
  int iVar12;
  int *piVar13;
  uint uVar14;
  byte *pbVar15;
  float *pfVar16;
  float *pfVar17;
  float fVar18;
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
  
  prVar4 = thing->pModel;
  piVar5 = thing->pPuppet;
  if (thing->nFrozen == 0) {
    if ((piVar5 == (int *)0x0) || (*piVar5 != 0)) {
      uVar14 = 0;
      if (prVar4->nNumHierarchyNodes != 0) {
        pfVar10 = prVar4->pHierarchyNodes->aMatrix;
        iVar12 = 0;
        do {
          pfVar16 = pfVar10;
          pfVar17 = (float *)(iVar12 + (int)thing->pHierarchyMatrices);
          for (iVar9 = 0xc; iVar9 != 0; iVar9 = iVar9 + -1) {
            *pfVar17 = *pfVar16;
            pfVar16 = pfVar16 + 1;
            pfVar17 = pfVar17 + 1;
          }
          pfVar10 = pfVar10 + 0x2e;
          uVar14 = uVar14 + 1;
          iVar12 = iVar12 + 0x30;
        } while (uVar14 < (uint)prVar4->nNumHierarchyNodes);
      }
    }
    else {
      local_64 = 6;
      pbVar15 = (byte *)(piVar5 + 2);
      do {
        if (*(int *)pbVar15 != 0) {
          iVar12 = *(int *)(pbVar15 + 0x128);
          local_74[1] = PUN(float,(pbVar15 + 0x20));
          local_74[2] = 0.0f;
          if (*(int *)(iVar12 + 0x38) != 0) {
            piVar13 = (int *)(*(int *)(iVar12 + 0x3c) + 0x24);
            do {
              bVar8 = false;
              if (*piVar13 != 0) {
                if ((uint)piVar13[-1] < 0x40) {
                  iVar9 = *(int *)(pbVar15 + piVar13[-1] * 4 + 0x20);
                }
                else {
                  iVar9 = 0;
                }
                iVar1 = *piVar13 + -1;
                if (iVar9 != iVar1) {
                  iVar11 = iVar9 + 1;
                  if (*(float *)(piVar13[1] + iVar11 * 0x38) <= *(float *)(pbVar15 + 0x120)) {
                    pfVar10 = (float *)(piVar13[1] + (iVar9 + 2) * 0x38);
                    do {
                      if (iVar11 == iVar1) {
                        bVar8 = true;
                      }
                      else if (*pfVar10 <= *(float *)(pbVar15 + 0x120)) {
                        iVar11 = iVar11 + 1;
                        pfVar10 = pfVar10 + 0xe;
                      }
                      else {
                        bVar8 = true;
                      }
                    } while (!bVar8);
                    if (PUN(uint,(float)local_74[2]) < 0x40) {
                      *PUN(int *,(float)local_74[1]) = iVar11;
                    }
                  }
                }
              }
              local_74[2] = PUN(float,(PUN(int,(float)local_74[2]) + 1));
              local_74[1] = PUN(float,(PUN(int,(float)local_74[1]) + 4));
              piVar13 = piVar13 + 0xb;
            } while (PUN(uint,(float)local_74[2]) < PUN(uint,(float)*(float *)(iVar12 + 0x38)));
          }
        }
        pbVar15 = pbVar15 + 0x134;
        local_64 = local_64 - 1;
      } while (local_64 != 0);
      local_5c[2] = 0.0f;
      if (prVar4->nNumHierarchyNodes != 0) {
        local_50 = 0;
        local_60 = 0;
        piVar13 = &prVar4->pHierarchyNodes->nIndex;
        do {
          local_3c[0] = 0.0f;
          local_3c[1] = 0.0f;
          local_5c[0] = 0.0f;
          local_74[2] = 0.0f;
          local_74[0] = 0.0f;
          local_74[1] = 0.0f;
          local_3c[2] = 0.0f;
          local_48[0] = 0.0f;
          local_18[0] = 0.0f;
          local_c[0] = 0.0f;
          local_48[1] = 0.0f;
          local_18[1] = 0.0f;
          local_c[1] = 0.0f;
          local_48[2] = 0.0f;
          local_18[2] = 0.0f;
          local_c[2] = 0.0f;
          local_5c[1] = 8.40779e-45f;
          pbVar15 = (byte *)(piVar5 + 2);
          do {
            iVar12 = *(int *)(pbVar15 + 0x128);
            if (iVar12 != 0) {
              if ((piVar13[1] & *(uint *)(iVar12 + 0x2c)) == 0) {
                fVar18 = *(float *)(pbVar15 + 8);
              }
              else {
                fVar18 = *(float *)(pbVar15 + 0xc);
              }
              if ((((((*pbVar15 & 2) != 0) && (uVar14 = *piVar13, uVar14 < *(uint *)(iVar12 + 0x38))
                    ) && (iVar9 = *(int *)(iVar12 + 0x3c) + uVar14 * 0x2c,
                         *(int *)(iVar9 + 0x24) != 0)) &&
                  ((PUN(int,(float)local_74[2]) <= PUN(int,(float)fVar18) &&
                   ((PUN(int,(float)local_5c[0]) <= PUN(int,(float)fVar18) || (local_74[0] < 1.0f)))))) &&
                 (uVar14 < *(uint *)(iVar12 + 0x38))) {
                pfVar10 = (float *)(*(int *)(iVar9 + 0x28) +
                                   *(int *)(pbVar15 + uVar14 * 4 + 0x20) * 0x38);
                if ((*(uint *)(iVar12 + 0x24) & 0x100) == 0) {
                  fVar7 = *(float *)(pbVar15 + 0x120) - *pfVar10;
                }
                else {
                  fVar7 = 0.0f;
                }
                if ((PUN(uint,(float)pfVar10[1]) & 1) == 0) {
                  local_24[0] = pfVar10[2];
                  local_24[1] = pfVar10[3];
                  local_24[2] = pfVar10[4];
                }
                else {
                  local_24[0] = pfVar10[8] * fVar7 + pfVar10[2];
                  local_24[1] = pfVar10[9] * fVar7 + pfVar10[3];
                  local_24[2] = pfVar10[10] * fVar7 + pfVar10[4];
                }
                if ((PUN(uint,(float)pfVar10[1]) & 2) == 0) {
                  local_30[0] = pfVar10[5];
                  fVar6 = pfVar10[6];
                  fVar7 = pfVar10[7];
                }
                else {
                  local_30[0] = pfVar10[0xb] * fVar7 + pfVar10[5];
                  fVar6 = pfVar10[0xc] * fVar7 + pfVar10[6];
                  fVar7 = pfVar10[0xd] * fVar7 + pfVar10[7];
                }
                local_24[0] = local_24[0] - PUN(float,piVar13[0xb]);
                local_24[1] = local_24[1] - PUN(float,piVar13[0xc]);
                local_24[2] = local_24[2] - PUN(float,piVar13[0xd]);
                fVar2 = PUN(float,piVar13[0xf]);
                fVar3 = PUN(float,piVar13[0x10]);
                local_30[0] = stdMath_NormalizeAngleAcute(local_30[0] - PUN(float,piVar13[0xe]));
                local_30[1] = stdMath_NormalizeAngleAcute(fVar6 - fVar2);
                local_30[2] = stdMath_NormalizeAngleAcute(fVar7 - fVar3);
                if (*(float *)(pbVar15 + 0x18) < 1.0f) {
                  local_24[0] = *(float *)(pbVar15 + 0x18) * local_24[0];
                  local_24[1] = *(float *)(pbVar15 + 0x18) * local_24[1];
                  local_24[2] = *(float *)(pbVar15 + 0x18) * local_24[2];
                  local_30[0] = *(float *)(pbVar15 + 0x18) * local_30[0];
                  local_30[1] = *(float *)(pbVar15 + 0x18) * local_30[1];
                  local_30[2] = *(float *)(pbVar15 + 0x18) * local_30[2];
                }
                if (fVar18 == local_5c[0]) {
                  local_3c[0] = local_24[0] + local_3c[0];
                  local_3c[1] = local_24[1] + local_3c[1];
                  local_3c[2] = local_24[2] + local_3c[2];
                  local_48[0] = local_30[0] + local_48[0];
                  local_48[1] = local_30[1] + local_48[1];
                  local_48[2] = local_30[2] + local_48[2];
                  local_74[0] = local_74[0] + *(float *)(pbVar15 + 0x18);
                }
                else if (PUN(int,(float)local_5c[0]) < PUN(int,(float)fVar18)) {
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
                  local_74[0] = *(float *)(pbVar15 + 0x18);
                  local_74[2] = local_5c[0];
                  local_48[1] = local_30[1];
                  local_48[2] = local_30[2];
                  local_5c[0] = fVar18;
                }
                else if (PUN(int,(float)local_74[2]) < PUN(int,(float)fVar18)) {
                  local_18[0] = local_24[0];
                  local_18[1] = local_24[1];
                  local_18[2] = local_24[2];
                  local_c[0] = local_30[0];
                  local_c[1] = local_30[1];
                  local_74[1] = *(float *)(pbVar15 + 0x18);
                  local_c[2] = local_30[2];
                  local_74[2] = fVar18;
                }
                else {
                  local_18[0] = local_24[0] + local_18[0];
                  local_18[1] = local_24[1] + local_18[1];
                  local_18[2] = local_24[2] + local_18[2];
                  local_c[0] = local_30[0] + local_c[0];
                  local_c[1] = local_30[1] + local_c[1];
                  local_c[2] = local_30[2] + local_c[2];
                  local_74[1] = local_74[1] + *(float *)(pbVar15 + 0x18);
                }
              }
            }
            pbVar15 = pbVar15 + 0x134;
            local_5c[1] = PUN(float,(PUN(int,(float)local_5c[1]) + -1));
          } while (local_5c[1] != 0.0f);
          if ((1.0f <= local_74[0]) || (local_74[1] <= 0.0f)) {
            if (1.0f < local_74[0]) {
              fVar18 = 1.0f / local_74[0];
              local_3c[0] = local_3c[0] * fVar18;
              local_3c[1] = local_3c[1] * fVar18;
              local_3c[2] = local_3c[2] * fVar18;
              local_48[0] = local_48[0] * fVar18;
              local_48[1] = local_48[1] * fVar18;
              local_48[2] = local_48[2] * fVar18;
            }
          }
          else {
            if (1.0f < local_74[1]) {
              fVar18 = 1.0f / local_74[1];
              local_18[0] = local_18[0] * fVar18;
              local_18[1] = local_18[1] * fVar18;
              local_18[2] = local_18[2] * fVar18;
              local_c[0] = local_c[0] * fVar18;
              local_c[1] = local_c[1] * fVar18;
              local_c[2] = local_c[2] * fVar18;
            }
            fVar18 = 1.0f - local_74[0];
            local_3c[0] = local_18[0] * fVar18 + local_3c[0];
            local_3c[1] = local_18[1] * fVar18 + local_3c[1];
            local_3c[2] = local_18[2] * fVar18 + local_3c[2];
            local_48[0] = local_c[0] * fVar18 + local_48[0];
            local_48[1] = local_c[1] * fVar18 + local_48[1];
            local_48[2] = local_c[2] * fVar18 + local_48[2];
          }
          local_48[0] = stdMath_NormalizeAngleAcute(local_48[0]);
          local_48[1] = stdMath_NormalizeAngleAcute(local_48[1]);
          fVar18 = stdMath_NormalizeAngleAcute(local_48[2]);
          local_3c[0] = PUN(float,piVar13[0xb]) + local_3c[0];
          local_3c[1] = PUN(float,piVar13[0xc]) + local_3c[1];
          local_3c[2] = PUN(float,piVar13[0xd]) + local_3c[2];
          local_48[0] = PUN(float,piVar13[0xe]) + local_48[0];
          local_48[1] = PUN(float,piVar13[0xf]) + local_48[1];
          local_48[2] = PUN(float,piVar13[0x10]) + fVar18;
          rdMatrix_Build34((float *)(local_50 + (int)thing->pHierarchyMatrices),(uint *)local_48,
                           local_3c);
          uVar14 = (int)thing->pHierarchyRot + local_60;
          if (((*(float *)((int)thing->pHierarchyRot + local_60) != 0.0f) ||
              (*(float *)(uVar14 + 4) != 0.0f)) || (*(float *)(uVar14 + 8) != 0.0f)) {
            Matrix_BuildTransform((float *)(local_50 + (int)thing->pHierarchyMatrices),uVar14);
          }
          local_5c[2] = PUN(float,(PUN(int,(float)local_5c[2]) + 1));
          local_60 = local_60 + 0xc;
          local_50 = local_50 + 0x30;
          piVar13 = piVar13 + 0x2e;
        } while (PUN(uint,(float)local_5c[2]) < (uint)prVar4->nNumHierarchyNodes);
      }
    }
    rdThing_AccumulateMatrices((int)thing,(int)prVar4->pHierarchyNodes,frame);
    thing->dwFrameTrue = g_dwRdroid_frameTrue;
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


/* ---- 0x004c0630  rdKeyframe_NewEntry ---- */
/* Clears a 0x84-byte keyframe record and names it UNKNOWN. Source file Rdkeyframe.c
   (C:\grimjedi\Libs\RDroid\Engine\Rdkeyframe.c). */

void __cdecl rdKeyframe_NewEntry(rdKeyframe *keyframe)

{
  int iVar1;
  rdKeyframe *prVar2;
  
  prVar2 = keyframe;
  for (iVar1 = 0x21; iVar1 != 0; iVar1 = iVar1 + -1) {
    prVar2->aName[0] = '\0';
    prVar2->aName[1] = '\0';
    prVar2->aName[2] = '\0';
    prVar2->aName[3] = '\0';
    prVar2 = (rdKeyframe *)(prVar2->aName + 4);
  }
  strncpy((uint *)keyframe,(uint *)s_UNKNOWN_004ddb8c,0x1f);
  keyframe->aName[0x1f] = '\0';
  return;
}

/* ---- 0x004c0660  rdKeyframe_Load ---- */
/* Loads an animation: custom loader hook if installed, else allocates the 0x84-byte record; the
   magic 'KEYF' selects rdKeyframe_LoadEntryBinary, anything else rdKeyframe_LoadEntry. Source file
   Rdkeyframe.c (C:\grimjedi\Libs\RDroid\Engine\Rdkeyframe.c). */

int __cdecl rdKeyframe_Load(char *name)

{
  char *path;
  int iVar1;
  uint uVar2;
  rdKeyframe *keyframe;
  uint uVar3;
  uint *puVar4;
  
  path = name;
  if (g_dwKeyframeLoader != 0) {
    iVar1 = (*(code *)g_dwKeyframeLoader)(name);
    return iVar1;
  }
  uVar2 = (*g_pRdroid_HS->pFopen)(name,&DAT_004ddb18);
  if (uVar2 != 0) {
    keyframe = (rdKeyframe *)
               (*g_pRdroid_HS->pAlloc)
                         (0x84,s_C__grimjedi_Libs_RDroid_Engine_R_004f0f14,DAT_004f0f08 + 0x11);
    if (keyframe != (rdKeyframe *)0x0) {
      (*g_pRdroid_HS->pFread)(uVar2,&name,4);
      if (name == (char *)0x4b455946) {
        uVar3 = rdKeyframe_LoadEntryBinary(uVar2,(int)keyframe);
        if (uVar3 != 0) {
          uVar3 = 0x1f;
          puVar4 = (uint *)stdFileFromPath(path);
          strncpy((uint *)keyframe,puVar4,uVar3);
          keyframe->aName[0x1f] = '\0';
          (*g_pRdroid_HS->pFclose)(uVar2);
          return (int)keyframe;
        }
        (*g_pRdroid_HS->pFclose)(uVar2);
        rdKeyframe_Free((int)keyframe);
        return 0;
      }
      (*g_pRdroid_HS->pFclose)(uVar2);
      uVar2 = rdKeyframe_LoadEntry(path,keyframe);
      if (uVar2 != 0) {
        return (int)keyframe;
      }
    }
    rdKeyframe_Free((int)keyframe);
  }
  return 0;
}

/* ---- 0x004c0770  rdKeyframe_LoadEntry ---- */
/* Parser of the text .key format (flags, type, frames, fps, joints, entries; stdConffile). Source
   file Rdkeyframe.c (C:\grimjedi\Libs\RDroid\Engine\Rdkeyframe.c). */

uint __cdecl rdKeyframe_LoadEntry(char *path,rdKeyframe *keyframe)

{
  unsigned char _frame[0x80] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  rdKeyframe *prVar2;
  uint *puVar3;
  int iVar4;
  rdKeyframeNode *prVar5;
  byte *pbVar6;
  uint uVar7;
  rdKeyframeEntry *prVar8;
  byte *pbVar9;
  undefined1 *puVar10;
  bool bVar11;
  uint uVar12;
  #define uStack_68 (*(uint *)(_frame + (0x80 - 0x68)))
  #define uStack_64 (*(uint *)(_frame + (0x80 - 0x64)))
  #define uStack_60 (*(uint *)(_frame + (0x80 - 0x60)))
  #define pcStack_5c (*(char **)(_frame + (0x80 - 0x5c)))
  #define local_58 (*(uint *)(_frame + (0x80 - 0x58)))
  #define fStack_54 (*(float *)(_frame + (0x80 - 0x54)))
  #define fStack_50 (*(float *)(_frame + (0x80 - 0x50)))
  #define fStack_4c (*(float *)(_frame + (0x80 - 0x4c)))
  #define fStack_48 (*(float *)(_frame + (0x80 - 0x48)))
  #define fStack_44 (*(float *)(_frame + (0x80 - 0x44)))
  #define fStack_40 (*(float *)(_frame + (0x80 - 0x40)))
  #define fStack_3c (*(float *)(_frame + (0x80 - 0x3c)))
  #define fStack_38 (*(float *)(_frame + (0x80 - 0x38)))
  #define fStack_34 (*(float *)(_frame + (0x80 - 0x34)))
  #define fStack_30 (*(float *)(_frame + (0x80 - 0x30)))
  #define fStack_2c (*(float *)(_frame + (0x80 - 0x2c)))
  #define fStack_28 (*(float *)(_frame + (0x80 - 0x28)))
  #define auStack_24 (*(undefined1 (*)[4])(_frame + (0x80 - 0x24)))
  #define auStack_20 (*(uint (*)[8])(_frame + (0x80 - 0x20)))
  
  prVar2 = keyframe;
  rdKeyframe_NewEntry(keyframe);
  uVar12 = 0x1f;
  puVar3 = (uint *)stdFileFromPath(path);
  strncpy((uint *)prVar2,puVar3,uVar12);
  prVar2->aName[0x1f] = '\0';
  uVar12 = stdConffile_Open((uint)path);
  if (uVar12 == 0) {
    return 0;
  }
  uVar12 = stdConffile_ReadLine();
  if (uVar12 != 0) {
    iVar4 = sscanf((char *)g_dwStdConffile_aLine,s_section___s_004ddd64,&g_bStd_genBuffer);
    if (iVar4 == 1) {
      uVar12 = stdConffile_ReadLine();
      if (uVar12 != 0) {
        iVar4 = sscanf((char *)g_dwStdConffile_aLine,s_flags__x_004f0ff0,&prVar2->dwFlags);
        if (iVar4 == 1) {
          uVar12 = stdConffile_ReadLine();
          if (uVar12 != 0) {
            iVar4 = sscanf((char *)g_dwStdConffile_aLine,s_type__x_004f0fe4,&prVar2->nType);
            if (iVar4 == 1) {
              uVar12 = stdConffile_ReadLine();
              if (uVar12 != 0) {
                iVar4 = sscanf((char *)g_dwStdConffile_aLine,s_frames__d_004f0fd8,
                               &prVar2->nNumFrames);
                if (iVar4 == 1) {
                  uVar12 = stdConffile_ReadLine();
                  if (uVar12 != 0) {
                    iVar4 = sscanf((char *)g_dwStdConffile_aLine,s_fps__f_004f0fd0,&local_58);
                    if (iVar4 == 1) {
                      prVar2->flFps = PUN(float,local_58);
                      uVar12 = stdConffile_ReadLine();
                      if (uVar12 != 0) {
                        iVar4 = sscanf((char *)g_dwStdConffile_aLine,s_joints__d_004f0fc4,&keyframe)
                        ;
                        if (iVar4 == 1) {
                          prVar5 = (rdKeyframeNode *)
                                   (*g_pRdroid_HS->pAlloc)
                                             ((int)keyframe * 0x2c,
                                              s_C__grimjedi_Libs_RDroid_Engine_R_004f0f14,
                                              DAT_004f0f0c + 0x42);
                          prVar2->pNodes = prVar5;
                          if (prVar5 != (rdKeyframeNode *)0x0) {
                            for (uVar12 = (int)keyframe * 0xb & 0x3fffffff; uVar12 != 0;
                                uVar12 = uVar12 - 1) {
                              prVar5->aMeshName[0] = '\0';
                              prVar5->aMeshName[1] = '\0';
                              prVar5->aMeshName[2] = '\0';
                              prVar5->aMeshName[3] = '\0';
                              prVar5 = (rdKeyframeNode *)(prVar5->aMeshName + 4);
                            }
                            for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
                              prVar5->aMeshName[0] = '\0';
                              prVar5 = (rdKeyframeNode *)(prVar5->aMeshName + 1);
                            }
                            *(rdKeyframe **)&prVar2->field_0x28 = keyframe;
                            prVar2->nNumNodes = (int)keyframe;
                            uVar12 = stdConffile_ReadLine();
                            if (uVar12 != 0) {
                              iVar4 = sscanf((char *)g_dwStdConffile_aLine,s_section___s_004ddd64,
                                             &g_bStd_genBuffer);
                              if (iVar4 == 1) {
                                pbVar9 = &DAT_004f0fbc;
                                pbVar6 = &g_bStd_genBuffer;
                                do {
                                  bVar1 = *pbVar6;
                                  bVar11 = bVar1 < *pbVar9;
                                  if (bVar1 != *pbVar9) {
LAB_004c099a:
                                    iVar4 = (1 - (uint)bVar11) - (uint)(bVar11 != 0);
                                    goto LAB_004c099f;
                                  }
                                  if (bVar1 == 0) break;
                                  bVar1 = pbVar6[1];
                                  bVar11 = bVar1 < pbVar9[1];
                                  if (bVar1 != pbVar9[1]) goto LAB_004c099a;
                                  pbVar6 = pbVar6 + 2;
                                  pbVar9 = pbVar9 + 2;
                                } while (bVar1 != 0);
                                iVar4 = 0;
LAB_004c099f:
                                if (iVar4 == 0) {
                                  uVar12 = stdConffile_ReadLine();
                                  if (uVar12 == 0) goto LAB_004c0cbf;
                                  iVar4 = sscanf((char *)g_dwStdConffile_aLine,s_markers__d_004f0fb0
                                                 ,&uStack_68);
                                  if ((iVar4 != 1) || (8 < uStack_68)) goto LAB_004c0cbf;
                                  uVar12 = 0;
                                  *(uint *)&prVar2->field_0x40 = uStack_68;
                                  if (uStack_68 != 0) {
                                    puVar10 = &prVar2->field_0x44;
                                    do {
                                      uVar7 = stdConffile_ReadLine();
                                      if (uVar7 == 0) goto LAB_004c0cbf;
                                      iVar4 = sscanf((char *)g_dwStdConffile_aLine,s__f__d_004f0fa8,
                                                     puVar10,puVar10 + 0x20);
                                      if (iVar4 != 2) goto LAB_004c0cbf;
                                      uVar12 = uVar12 + 1;
                                      puVar10 = puVar10 + 4;
                                    } while (uVar12 < uStack_68);
                                  }
                                  uVar12 = stdConffile_ReadLine();
                                  if (uVar12 == 0) goto LAB_004c0cbf;
                                  iVar4 = sscanf((char *)g_dwStdConffile_aLine,
                                                 s_section___s_004ddd64,&g_bStd_genBuffer);
                                  if (iVar4 != 1) goto LAB_004c0cbf;
                                }
                                uVar12 = stdConffile_ReadLine();
                                if (uVar12 != 0) {
                                  iVar4 = sscanf((char *)g_dwStdConffile_aLine,s_nodes__d_004f0f9c,
                                                 &pcStack_5c);
                                  if (iVar4 == 1) {
                                    path = (char *)0x0;
                                    if (pcStack_5c == (char *)0x0) {
                                      stdConffile_Close();
                                      return 1;
                                    }
                                    while( true ) {
                                      uVar12 = stdConffile_ReadLine();
                                      if (uVar12 == 0) break;
                                      iVar4 = sscanf((char *)g_dwStdConffile_aLine,
                                                     s_node__d_004f0f90,&uStack_64);
                                      if (iVar4 != 1) break;
                                      uVar12 = stdConffile_ReadLine();
                                      if (uVar12 == 0) break;
                                      iVar4 = sscanf((char *)g_dwStdConffile_aLine,
                                                     s_mesh_name__s_004f0f80,auStack_20);
                                      if (iVar4 != 1) break;
                                      prVar5 = prVar2->pNodes + uStack_64;
                                      strncpy((uint *)prVar5,auStack_20,0x1f);
                                      prVar5->aMeshName[0x1f] = '\0';
                                      uVar12 = stdConffile_ReadLine();
                                      if (uVar12 == 0) break;
                                      iVar4 = sscanf((char *)g_dwStdConffile_aLine,
                                                     s_entries__d_004f0f74,&uStack_60);
                                      if (iVar4 != 1) break;
                                      *(uint *)&prVar5->field_0x20 = uStack_64;
                                      prVar5->nNumEntries = uStack_60;
                                      prVar8 = (rdKeyframeEntry *)
                                               (*g_pRdroid_HS->pAlloc)
                                                         (uStack_60 * 0x38,
                                                                                                                    
                                                  s_C__grimjedi_Libs_RDroid_Engine_R_004f0f14,
                                                  DAT_004f0f0c + 0x9b);
                                      prVar5->pEntries = prVar8;
                                      if (prVar8 == (rdKeyframeEntry *)0x0) break;
                                      uVar12 = 0;
                                      if (prVar5->nNumEntries != 0) {
                                        do {
                                          uVar7 = stdConffile_ReadLine();
                                          if (uVar7 == 0) goto LAB_004c0cbf;
                                          iVar4 = sscanf((char *)g_dwStdConffile_aLine,
                                                         s__d___f__x__f__f__f__f__f__f_004f0f54,
                                                         auStack_24,prVar8,&prVar8->dwFlags,
                                                         &fStack_54,&fStack_50,&fStack_4c,&fStack_48
                                                         ,&fStack_44,&fStack_40);
                                          if (iVar4 != 9) goto LAB_004c0cbf;
                                          prVar8->aPos[0] = fStack_54;
                                          prVar8->aPos[1] = fStack_50;
                                          prVar8->aPos[2] = fStack_4c;
                                          prVar8->flPitch = fStack_48;
                                          prVar8->flYaw = fStack_44;
                                          prVar8->flRoll = fStack_40;
                                          uVar7 = stdConffile_ReadLine();
                                          if (uVar7 == 0) goto LAB_004c0cbf;
                                          iVar4 = sscanf((char *)g_dwStdConffile_aLine,
                                                         s__f__f__f__f__f__f_004f0f40,&fStack_3c,
                                                         &fStack_38,&fStack_34,&fStack_30,&fStack_2c
                                                         ,&fStack_28);
                                          if (iVar4 != 6) goto LAB_004c0cbf;
                                          prVar8->aDPos[0] = fStack_3c;
                                          prVar8->aDPos[1] = fStack_38;
                                          prVar8->aDPos[2] = fStack_34;
                                          prVar8->flDPitch = fStack_30;
                                          prVar8->flDYaw = fStack_2c;
                                          prVar8->flDRoll = fStack_28;
                                          prVar8 = prVar8 + 1;
                                          uVar12 = uVar12 + 1;
                                        } while (uVar12 < (uint)prVar5->nNumEntries);
                                      }
                                      path = path + 1;
                                      if (pcStack_5c <= path) {
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
#undef fStack_28
#undef fStack_2c
#undef fStack_30
#undef fStack_34
#undef fStack_38
#undef fStack_3c
#undef fStack_40
#undef fStack_44
#undef fStack_48
#undef fStack_4c
#undef fStack_50
#undef fStack_54
#undef local_58
#undef pcStack_5c
#undef uStack_60
#undef uStack_64
#undef uStack_68


/* ---- 0x004c0ce0  rdKeyframe_LoadEntryBinary ---- */
/* Reader of the binary 'KEYF' animation format. Source file Rdkeyframe.c
   (C:\grimjedi\Libs\RDroid\Engine\Rdkeyframe.c). Original name rdKeyframe_LoadEntryBinary (the
   remaster's GrimFandango (Linux): aligned call in rdKeyframe_Load); was rdKeyframe_LoadBinary. */

uint __cdecl rdKeyframe_LoadEntryBinary(uint f,int keyframe)

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
  
  iVar2 = keyframe;
  (*g_pRdroid_HS->pFread)(f,keyframe,0x84);
  puVar3 = (undefined4 *)
           (*g_pRdroid_HS->pAlloc)
                     (*(int *)(keyframe + 0x38) * 0x2c,s_C__grimjedi_Libs_RDroid_Engine_R_004f0f14,
                      DAT_004f0f10 + 0x16);
  *(undefined4 **)(keyframe + 0x3c) = puVar3;
  if (puVar3 == (undefined4 *)0x0) {
LAB_004c0e2c:
    (*g_pRdroid_HS->pFclose)(f);
    return 0;
  }
  piVar1 = (int *)(keyframe + 0x38);
  keyframe = 0;
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
      (*g_pRdroid_HS->pFread)(f,*(int *)(iVar2 + 0x3c) + iVar7,0x2c);
      iVar9 = 0;
      iVar5 = *(int *)(*(int *)(iVar2 + 0x3c) + 0x24 + iVar7);
      if (iVar5 == 0) {
        *(undefined4 *)(*(int *)(iVar2 + 0x3c) + iVar7 + 0x28) = 0;
      }
      else {
        uVar4 = (*g_pRdroid_HS->pAlloc)
                          (iVar5 * 0x38,s_C__grimjedi_Libs_RDroid_Engine_R_004f0f14,
                           DAT_004f0f10 + 0x21);
        *(undefined4 *)(*(int *)(iVar2 + 0x3c) + 0x28 + iVar7) = uVar4;
        iVar5 = *(int *)(iVar2 + 0x3c) + iVar7;
        if (*(int *)(*(int *)(iVar2 + 0x3c) + 0x28 + iVar7) == 0) goto LAB_004c0e2c;
        if (0 < *(int *)(iVar5 + 0x24)) {
          iVar8 = 0;
          do {
            (*g_pRdroid_HS->pFread)(f,*(int *)(iVar5 + 0x28) + iVar8,0x38);
            iVar5 = *(int *)(iVar2 + 0x3c) + iVar7;
            iVar9 = iVar9 + 1;
            iVar8 = iVar8 + 0x38;
          } while (iVar9 < *(int *)(iVar5 + 0x24));
        }
      }
      keyframe = keyframe + 1;
      iVar7 = iVar7 + 0x2c;
    } while (keyframe < *(int *)(iVar2 + 0x38));
  }
  (*g_pRdroid_HS->pFclose)(f);
  return 1;
}

/* ---- 0x004c0e40  rdKeyframe_Free ---- */
/* Frees a keyframe (custom free hook if installed, else rdKeyframe_FreeEntry and the record).
   Source file Rdkeyframe.c (C:\grimjedi\Libs\RDroid\Engine\Rdkeyframe.c). */

void __cdecl rdKeyframe_Free(int keyframe)

{
  if (keyframe != 0) {
    if (g_dwKeyframeUnloader != 0) {
      (*(code *)g_dwKeyframeUnloader)(keyframe);
      return;
    }
    rdKeyframe_FreeEntry(keyframe);
    (*g_pRdroid_HS->pFree)(keyframe);
  }
  return;
}

/* ---- 0x004c0e70  rdKeyframe_FreeEntry ---- */
/* Frees the per-joint node arrays of a keyframe record. Source file Rdkeyframe.c
   (C:\grimjedi\Libs\RDroid\Engine\Rdkeyframe.c). */

void __cdecl rdKeyframe_FreeEntry(int keyframe)

{
  int *piVar1;
  uint uVar2;
  
  if (*(int *)(keyframe + 0x3c) != 0) {
    uVar2 = 0;
    if (*(int *)(keyframe + 0x38) != 0) {
      piVar1 = (int *)(*(int *)(keyframe + 0x3c) + 0x28);
      do {
        if (*piVar1 != 0) {
          (*g_pRdroid_HS->pFree)(*piVar1);
          *piVar1 = 0;
        }
        piVar1 = piVar1 + 0xb;
        uVar2 = uVar2 + 1;
      } while (uVar2 < *(uint *)(keyframe + 0x38));
    }
    (*g_pRdroid_HS->pFree)(*(undefined4 *)(keyframe + 0x3c));
    *(undefined4 *)(keyframe + 0x3c) = 0;
  }
  return;
}
