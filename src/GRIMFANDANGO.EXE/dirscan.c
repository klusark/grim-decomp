/* GRIMFANDANGO.EXE :: dirscan.c
 * functions 0x00488de0 .. 0x00488ee0 (4 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00488de0  DirScan_Create ---- */
/* Temp/Fileutil.c: allocates a 0x20c-byte directory scanner. mode 0-2: pattern dir\*.*, mode 3:
   dir\*.ext (leading '.' stripped). */

uint * __cdecl DirScan_Create(uint param_1,int param_2,char *param_3)

{
  uint *puVar1;
  int iVar2;
  uint *puVar3;
  
  puVar1 = (uint *)(*g_pSvcFileutil->pAlloc)
                             (0x20c,s_C__grimsrc_libs_grimlib_Temp_Fil_004e830c,0x16e);
  if (puVar1 == (uint *)0x0) {
    return (uint *)0x0;
  }
  puVar3 = puVar1;
  for (iVar2 = 0x83; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  if (-1 < param_2) {
    if (param_2 < 3) {
      sprintf((char *)(puVar1 + 2),s__s____004e82fc,param_1);
    }
    else if (param_2 == 3) {
      if (*param_3 == '.') {
        param_3 = param_3 + 1;
      }
      sprintf((char *)(puVar1 + 2),s__s___s_004e8304,param_1,param_3);
      return puVar1;
    }
  }
  return puVar1;
}

/* ---- 0x00488e70  DirScan_Destroy ---- */
void __cdecl DirScan_Destroy(int param_1)

{
  if (param_1 != 0) {
    if (*(int *)(param_1 + 4) != 0) {
      _findclose(*(undefined4 *)(param_1 + 0x208));
    }
    if (param_1 != 0) {
      (*g_pSvcFileutil->pFree)(param_1);
    }
  }
  return;
}

/* ---- 0x00488eb0  DirScan_Reset ---- */
/* Closes the find handle so the next DirScan_Next restarts with _findfirst */

void __cdecl DirScan_Reset(int param_1)

{
  if ((param_1 != 0) && (*(int *)(param_1 + 4) != 0)) {
    _findclose(*(undefined4 *)(param_1 + 0x208));
  }
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 4) = 0;
  }
  return;
}

/* ---- 0x00488ee0  DirScan_Next ---- */
/* _findfirst/_findnext wrapper. Copies the entry name into out, out+0x104 = is-directory flag
   (attrib & 0x10), out+0x108 = file size. */

uint __cdecl DirScan_Next(int param_1,char *param_2)

{
  unsigned char _frame[0x130] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  #define local_118 (*(uint *)(_frame + (0x130 - 0x118)))
  #define local_10c (*(uint *)(_frame + (0x130 - 0x10c)))
  #define local_104 (*(char (*)[260])(_frame + (0x130 - 0x104)))
  
  if (param_1 == 0) {
    return 0;
  }
  iVar2 = *(int *)(param_1 + 4);
  *(int *)(param_1 + 4) = iVar2 + 1;
  if (iVar2 == 0) {
    iVar2 = _findfirst(param_1 + 8,&local_118);
    *(int *)(param_1 + 0x208) = iVar2;
  }
  else {
    iVar2 = _findnext(*(undefined4 *)(param_1 + 0x208),&local_118);
  }
  if (iVar2 == -1) {
    return 0;
  }
  uVar3 = 0xffffffff;
  pcVar5 = local_104;
  do {
    pcVar6 = pcVar5;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar6 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar6;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar5 = pcVar6 + -uVar3;
  pcVar6 = param_2;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar6 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar6 = pcVar6 + 1;
  }
  *(uint *)(param_2 + 0x108) = local_10c;
  *(uint *)(param_2 + 0x104) = local_118 & 0x10;
  return 1;
}
#undef local_104
#undef local_10c
#undef local_118

