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
    iVar1 = gzwrite((undefined4 *)UINT_008a8770,(uint)data,bytes);
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
    gzread((int *)UINT_008a8770,(int)buf,n);
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
  int *file;
  VBuffer *pVVar1;
  int iVar2;
  ColorFormat *pCVar3;
  ColorFormat *pCVar4;
  uint local_8c;
  uint local_88;
  ColorFormat format;
  VBufferFormat bufferFormat;
  
  format.dwRedBits = 5;
  format.dwBlueBits = 5;
  format.dwGreenShift = 5;
  format.dwRedLoss = 3;
  format.dwBlueLoss = 3;
  format.nColorMode = 1;
  format.nBpp = 0x10;
  format.dwGreenBits = 6;
  format.dwRedShift = 0xb;
  format.dwBlueShift = 0;
  format.dwGreenLoss = 2;
  format.dwUnknown2c = 0;
  format.dwUnknown30 = 0;
  format.dwUnknown34 = 0;
  file = SaveFile_Open(filename,s_rb_004ddb18);
  if (file == (int *)0x0) {
    return (void *)0x0;
  }
  gzread(file,(int)&local_88,4);
  gzseek(file,local_88,1);
  bufferFormat.nStride = 2;
  bufferFormat.nWidth = 0xfa;
  bufferFormat.nHeight = 0xbc;
  bufferFormat.nPitch = 500;
  pCVar3 = &format;
  pCVar4 = &bufferFormat.colorFormat;
  for (iVar2 = 0xe; iVar2 != 0; iVar2 = iVar2 + -1) {
    pCVar4->nColorMode = pCVar3->nColorMode;
    pCVar3 = (ColorFormat *)&pCVar3->nBpp;
    pCVar4 = (ColorFormat *)&pCVar4->nBpp;
  }
  pVVar1 = stdDisplay_VBufferNew(&bufferFormat,0,0,0);
  if (pVVar1 == (VBuffer *)0x0) {
    gzclose((int)file);
    return (void *)0x0;
  }
  gzread(file,(int)&local_8c,4);
  if (local_8c != (pVVar1->format).dwSize) {
    (*g_pSputmHS->pAssertFail)
              (s_size_____int_vbuf__rasterInfo_si_004e7ff4,
               s_C__grimsrc_libs_grimlib_Main_spu_004e7f9c,0x6f6);
  }
  gzread(file,(int)pVVar1->pPixels,local_8c);
  gzclose((int)file);
  return pVVar1;
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern char grim_def_s_size_____int_vbuf__rasterInfo_si_004e7ff4[36] __asm__("_s_size_____int_vbuf__rasterInfo_si_004e7ff4");
extern char grim_def_s_tot_____int_bytes_004e7fd4[20] __asm__("_s_tot_____int_bytes_004e7fd4");
/* 0x004e7fd4, 20 bytes */ /* loose */ char grim_def_s_tot_____int_bytes_004e7fd4[20] __asm__("_s_tot_____int_bytes_004e7fd4") = "tot == (int)bytes";
/* 0x004e7ff4, 36 bytes */ /* loose */ char grim_def_s_size_____int_vbuf__rasterInfo_si_004e7ff4[36] __asm__("_s_size_____int_vbuf__rasterInfo_si_004e7ff4") = "size == (int)vbuf->rasterInfo.size";
