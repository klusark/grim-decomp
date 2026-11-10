/* CHORE.DLL :: chore.c
 * functions 0x100053e0 .. 0x10005530 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x100053e0  Chore_AdvanceTime ---- */
/* Advances chore `choreNum` of the instance by `dt` ms: every key with time in [time, time + dt) is
   passed to its component's OnKey handler (Chore_ApplyKey); the first update after
   Cos_InstPlayChore already takes dt (no zero-length first frame). time >= length ends the chore
   (flags and time cleared); a looping chore carries the remainder over from time 0. Original static
   name AdvanceChoreTracks2 (libchore.so). */

void __cdecl Chore_AdvanceTime(Costume *pCostume,CosInstance *pInst,int choreNum,int dt,int hInst)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  ChoreInstance *pCVar1;
  ChoreKey *pKey;
  Chore *pCVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  iVar3 = choreNum;
  pCVar2 = pCostume->pChores;
  pCVar1 = pInst->pChoreInstances + choreNum;
  if (dt == 0) {
    return;
  }
  do {
    local_4 = 0;
    if (0 < (int)pCVar2[iVar3].dwNumTracks) {
      choreNum = 0;
      do {
        piVar5 = (int *)((int)&(pCVar2[iVar3].pChoreTracks)->nCompNum + choreNum);
        iVar6 = piVar5[2];
        if (iVar6 != 0) {
          iVar7 = 0;
          if (0 < iVar6) {
            piVar4 = (int *)piVar5[3];
            do {
              if (pCVar1->nTime <= *piVar4) break;
              iVar7 = iVar7 + 1;
              piVar4 = piVar4 + 2;
            } while (iVar7 < iVar6);
          }
          if (iVar7 < iVar6) {
            do {
              iVar6 = *(int *)(piVar5[3] + iVar7 * 8);
              pKey = (ChoreKey *)(piVar5[3] + iVar7 * 8);
              if (dt + pCVar1->nTime <= iVar6) break;
              Chore_ApplyKey(2,g_aComponentTags + pCostume->pComponents[*piVar5].nTag,
                             pInst->pInstanceData[*piVar5],pKey,(dt + pCVar1->nTime) - iVar6,pKey,0,
                             hInst);
              iVar7 = iVar7 + 1;
            } while (iVar7 < piVar5[2]);
          }
        }
        local_4 = local_4 + 1;
        choreNum = choreNum + 0x10;
      } while (local_4 < (int)pCVar2[iVar3].dwNumTracks);
    }
    iVar6 = pCVar1->nTime + dt;
    pCVar1->nTime = iVar6;
    if (iVar6 < (int)pCVar2[iVar3].dwLength) {
      return;
    }
    if ((pCVar1->dwFlags & 2) == 0) {
      pCVar1->dwFlags = 0;
      pCVar1->nTime = 0;
      return;
    }
    dt = iVar6 - pCVar2[iVar3].dwLength;
    pCVar1->nTime = 0;
  } while( true );
}
#undef local_4


/* ---- 0x10005530  Chore_ApplyKey ---- */
/* Calls the OnKey handler (ComponentTag +0x2c, slot 0) of the component's tag for one key that
   Chore_AdvanceTime passed: (tag id, instance data, reason, key value, ms since the key, key value,
   0, user parameter). Chore_AdvanceTime passes reason 2 and the same key twice. An unknown tag kind
   only asserts. */

void __cdecl
Chore_ApplyKey(int reason,ComponentTag *pTag,int instData,ChoreKey *pKey,int dt,ChoreKey *pKey2,
              int zero,int user)

{
  int iVar1;
  
  iVar1 = pTag->nKind;
  if (((iVar1 != 0) && (iVar1 != 1)) && (iVar1 != 2)) {
    (*(code *)g_pSvcChore->pAssertFail)
              (&DAT_10010284,s_C__grimsrc_libs_chore_Costume_c_1001020c,0xd67);
    return;
  }
  (*(code *)pTag->pfnOnKey)(pTag->nId,instData,reason,pKey->nValue,dt,pKey2->nValue,zero,user);
  return;
}
