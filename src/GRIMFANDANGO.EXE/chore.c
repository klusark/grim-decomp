/* GRIMFANDANGO.EXE :: chore.c
 * functions 0x00498990 .. 0x00498ad0 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00498990  Chore_FadeIn ---- */
void __cdecl Chore_FadeIn(void *cosInst,int chore,int ms)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int *piVar3;
  int track;
  int iVar4;
  #define local_c (*(int *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(undefined4 *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  Cos_InstGetCostume(cosInst,&local_8);
  iVar2 = CosUtil_PtrFromHandle(local_8);
  if (chore <= *(int *)(iVar2 + 0x30)) {
    iVar2 = *(int *)(iVar2 + 0x34) + chore * 0x2c;
    local_c = 0;
    if (0 < *(int *)(iVar2 + 0x20)) {
      chore = 0;
      do {
        piVar3 = (int *)Cos_InstGetInstanceData
                                  (cosInst,*(undefined4 *)(*(int *)(iVar2 + 0x24) + chore),&local_4)
        ;
        if (local_4 == 0x4659454b) {
          track = 0;
          iVar4 = 0;
          do {
            iVar1 = *(int *)(*(int *)(*piVar3 + 0x40) + 0x14) + 8 + iVar4;
            if (piVar3[1] == 0) {
              (*g_pSvcMain->pAssertFail)
                        (s_Bad_keyframe_Reference_004ea1e0,s_main_sputResource_h_004e80a8,0xb3);
            }
            if (*(int *)(iVar1 + 0x128) == piVar3[2]) {
              if (*(int *)(iVar1 + 0x18) == 0x3f800000) {
                *(undefined4 *)(iVar1 + 0x18) = 0;
              }
              rdPuppet_FadeInTrack
                        (*(void **)(*(int *)(*piVar3 + 0x40) + 0x14),track,(float)ms * 0.001);
              break;
            }
            iVar4 = iVar4 + 0x134;
            track = track + 1;
          } while (iVar4 < 0x738);
        }
        local_c = local_c + 1;
        chore = chore + 0x10;
      } while (local_c < *(int *)(iVar2 + 0x20));
    }
  }
  return;
}
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x00498ad0  Chore_FadeOut ---- */
void __cdecl Chore_FadeOut(void *cosInst,int chore,int ms)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int *piVar3;
  int track;
  int iVar4;
  #define local_c (*(int *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(undefined4 *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  Cos_InstGetCostume(cosInst,&local_8);
  iVar2 = CosUtil_PtrFromHandle(local_8);
  if (chore <= *(int *)(iVar2 + 0x30)) {
    iVar2 = *(int *)(iVar2 + 0x34) + chore * 0x2c;
    local_c = 0;
    if (0 < *(int *)(iVar2 + 0x20)) {
      chore = 0;
      do {
        piVar3 = (int *)Cos_InstGetInstanceData
                                  (cosInst,*(undefined4 *)(*(int *)(iVar2 + 0x24) + chore),&local_4)
        ;
        if (local_4 == 0x4659454b) {
          track = 0;
          iVar4 = 0;
          do {
            iVar1 = *(int *)(*(int *)(*piVar3 + 0x40) + 0x14);
            if (piVar3[1] == 0) {
              (*g_pSvcMain->pAssertFail)
                        (s_Bad_keyframe_Reference_004ea1e0,s_main_sputResource_h_004e80a8,0xb3);
            }
            if (*(int *)(iVar1 + iVar4 + 0x130) == piVar3[2]) {
              rdPuppet_FadeOutTrack
                        (*(void **)(*(int *)(*piVar3 + 0x40) + 0x14),track,(float)ms * 0.001);
              break;
            }
            iVar4 = iVar4 + 0x134;
            track = track + 1;
          } while (iVar4 < 0x738);
        }
        local_c = local_c + 1;
        chore = chore + 0x10;
      } while (local_c < *(int *)(iVar2 + 0x20));
    }
  }
  return;
}
#undef local_4
#undef local_8
#undef local_c

