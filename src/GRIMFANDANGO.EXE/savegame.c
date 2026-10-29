/* GRIMFANDANGO.EXE :: savegame.c
 * functions 0x004831f0 .. 0x00483490 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004831f0  SaveGame_Write ---- */
/* gzwrite on the open save file, asserting the byte count */

int __cdecl SaveGame_Write(void *data,int bytes)

{
  int iVar1;
  
  if (bytes != 0) {
    iVar1 = gzwrite(DAT_008a8770,data,bytes);
    if (iVar1 != bytes) {
      (*g_pSvcEngineModule->pAssertFail)
                (s_tot_____int_bytes_004e7fd4,s_C__grimsrc_libs_grimlib_Main_spu_004e7f9c,0x60c);
    }
  }
  return 0;
}

/* ---- 0x00483470  SaveGame_Read ---- */
int __cdecl SaveGame_Read(void *data,int bytes)

{
  if (bytes != 0) {
    gzread(DAT_008a8770,data,bytes);
  }
  return 0;
}

/* ---- 0x00483490  SaveGame_Open ---- */
/* sputmain.cpp line 1782: opens a save file for reading and validates the header */

void * SaveGame_Open(char *param_1)

{
  unsigned char _frame[0xa0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *pvVar1;
  void *pvVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  #define local_8c (*(int *)(_frame + (0xa0 - 0x8c)))
  #define local_88 (*(undefined4 *)(_frame + (0xa0 - 0x88)))
  #define local_84 (*(undefined4 (*)[17])(_frame + (0xa0 - 0x84)))
  #define local_40 (*(undefined4 *)(_frame + (0xa0 - 0x40)))
  #define local_3c (*(undefined4 *)(_frame + (0xa0 - 0x3c)))
  #define local_38 (*(undefined4 (*)[14])(_frame + (0xa0 - 0x38)))
  
  local_84[2] = 5;
  local_84[4] = 5;
  local_84[6] = 5;
  local_84[8] = 3;
  local_84[10] = 3;
  local_84[0] = 1;
  local_84[1] = 0x10;
  local_84[3] = 6;
  local_84[5] = 0xb;
  local_84[7] = 0;
  local_84[9] = 2;
  local_84[0xb] = 0;
  local_84[0xc] = 0;
  local_84[0xd] = 0;
  pvVar1 = SaveFile_Open(param_1,&DAT_004ddb18);
  if (pvVar1 == (void *)0x0) {
    return (void *)0x0;
  }
  gzread(pvVar1,&local_88,4);
  gzseek(pvVar1,local_88,1);
  local_3c = 2;
  local_84[0xe] = 0xfa;
  local_84[0xf] = 0xbc;
  local_40 = 500;
  puVar4 = local_84;
  puVar5 = local_38;
  for (iVar3 = 0xe; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar5 = puVar5 + 1;
  }
  pvVar2 = Surface_Create(local_84 + 0xe,0,0,0);
  if (pvVar2 == (void *)0x0) {
    gzclose(pvVar1);
    return (void *)0x0;
  }
  gzread(pvVar1,&local_8c,4);
  if (local_8c != *(int *)((int)pvVar2 + 0x14)) {
    (*g_pSvcEngineModule->pAssertFail)
              (s_size_____int_vbuf__rasterInfo_si_004e7ff4,
               s_C__grimsrc_libs_grimlib_Main_spu_004e7f9c,0x6f6);
  }
  gzread(pvVar1,*(undefined4 *)((int)pvVar2 + 0x5c),local_8c);
  gzclose(pvVar1);
  return pvVar2;
}
#undef local_38
#undef local_3c
#undef local_40
#undef local_84
#undef local_88
#undef local_8c

