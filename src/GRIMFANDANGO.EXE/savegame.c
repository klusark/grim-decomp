/* GRIMFANDANGO.EXE :: savegame.c
 * functions 0x004831f0 .. 0x00483490 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004831f0  SaveGame_Write ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* gzwrite on the open save file, asserting the byte count */

int __cdecl SaveGame_Write(void *data,int bytes)

{
  int iVar1;
  
  if (bytes != 0) {
    iVar1 = gzwrite(UINT_008a8770,data,bytes);
    if (iVar1 != bytes) {
      (*g_pSputmHS->pAssertFail)
                (s_tot_____int_bytes_004e7fd4,s_C__grimsrc_libs_grimlib_Main_spu_004e7f9c,0x60c);
    }
  }
  return 0;
}
#endif


/* ---- 0x00483470  SaveGame_Read ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
int __cdecl SaveGame_Read(void *buf,int n)

{
  if (n != 0) {
    gzread(UINT_008a8770,buf,n);
  }
  return 0;
}
#endif


/* ---- 0x00483490  sputMain_GetSaveGameImage ---- */
/* Returns a 250x188 16-bit bitmap read from the head of a save file Original name
   sputMain_GetSaveGameImage (the remaster's GrimFandango (Linux): aligned call in
   sputLua_GetSaveGameImage); was SaveGame_LoadThumbnail. */

void * __cdecl sputMain_GetSaveGameImage(char *filename)

{
  unsigned char _frame[0xa0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *pvVar1;
  void *pvVar2;
  int iVar3;
  uint *puVar4;
  uint *puVar5;
  #define local_8c (*(uint *)(_frame + (0xa0 - 0x8c)))
  #define local_88 (*(uint *)(_frame + (0xa0 - 0x88)))
  #define local_84 (*(uint *)(_frame + (0xa0 - 0x84)))
  #define local_80 (*(uint *)(_frame + (0xa0 - 0x80)))
  #define local_7c (*(uint *)(_frame + (0xa0 - 0x7c)))
  #define local_78 (*(uint *)(_frame + (0xa0 - 0x78)))
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
  #define local_40 (*(uint *)(_frame + (0xa0 - 0x40)))
  #define local_3c (*(uint *)(_frame + (0xa0 - 0x3c)))
  #define local_38 (*(uint (*)[14])(_frame + (0xa0 - 0x38)))
  
  local_7c = 5;
  local_74 = 5;
  local_6c = 5;
  local_64 = 3;
  local_5c = 3;
  local_84 = 1;
  local_80 = 0x10;
  local_78 = 6;
  local_70 = 0xb;
  local_68 = 0;
  local_60 = 2;
  local_58 = 0;
  local_54 = 0;
  local_50 = 0;
  pvVar1 = SaveFile_Open(filename,&DAT_004ddb18);
  if (pvVar1 == (void *)0x0) {
    return (void *)0x0;
  }
  gzread(pvVar1,&local_88,4);
  gzseek(pvVar1,local_88,1);
  local_3c = 2;
  local_4c = 0xfa;
  local_48 = 0xbc;
  local_40 = 500;
  puVar4 = &local_84;
  puVar5 = local_38;
  for (iVar3 = 0xe; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar5 = puVar5 + 1;
  }
  pvVar2 = stdDisplay_VBufferNew(&local_4c,0,0,0);
  if (pvVar2 == (void *)0x0) {
    gzclose(pvVar1);
    return (void *)0x0;
  }
  gzread(pvVar1,&local_8c,4);
  if (local_8c != *(uint *)((int)pvVar2 + 0x14)) {
    (*g_pSputmHS->pAssertFail)
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
#undef local_78
#undef local_7c
#undef local_80
#undef local_84
#undef local_88
#undef local_8c

