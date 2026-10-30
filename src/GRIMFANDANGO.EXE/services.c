/* GRIMFANDANGO.EXE :: services.c
 * functions 0x004035b0 .. 0x00478080 (31 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004035b0  Svc_Printf ---- */
/* Default GrimServices.printf: vsprintf into the shared buffer then printf */

undefined4 __cdecl Svc_Printf(char *fmt,...)

{
  undefined4 uVar1;
  
  uVar1 = vsprintf(&DAT_004f5aa0,fmt,&STACK0X(0x00000008));
  printf(&DAT_004dda18,&DAT_004f5aa0);
  return uVar1;
}

/* ---- 0x004035e0  Svc_Printf2 ---- */
undefined4 Svc_Printf2(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = vsprintf(&DAT_004f5aa0,param_1,&STACK0X(0x00000008));
  printf(&DAT_004dda18,&DAT_004f5aa0);
  return uVar1;
}

/* ---- 0x00403610  Svc_Warning ---- */
/* Default GrimServices.warning: prints 'WARNING: %s' */

undefined4 Svc_Warning(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = vsprintf(&DAT_004f5aa0,param_1,&STACK0X(0x00000008));
  printf(s_WARNING___s_004dda1c,&DAT_004f5aa0);
  return uVar1;
}

/* ---- 0x00403640  Svc_Error ---- */
/* Default GrimServices.error: prints 'ERROR: %s' */

undefined4 Svc_Error(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = vsprintf(&DAT_004f5aa0,param_1,&STACK0X(0x00000008));
  printf(s_ERROR___s_004dda28,&DAT_004f5aa0);
  return uVar1;
}

/* ---- 0x00403670  Svc_Debug ---- */
/* Default GrimServices.debug: prints 'DEBUG: %s' */

undefined4 Svc_Debug(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = vsprintf(&DAT_004f5aa0,param_1,&STACK0X(0x00000008));
  printf(s_DEBUG___s_004dda34,&DAT_004f5aa0);
  return uVar1;
}

/* ---- 0x004036a0  Svc_AssertFail ---- */
/* Default GrimServices.assertFail: prints 'ASSERT: %s, %d: %s' and exit(1) */

void __cdecl Svc_AssertFail(char *expr,char *file,int line)

{
  printf(s_ASSERT____s__d___s_004dda40,file,line,expr);
  exit(1);
  return;
}

/* ---- 0x004036d0  Svc_Fn1c ---- */
void Svc_Fn1c(undefined4 param_1)

{
  atexit(param_1);
  return;
}

/* ---- 0x004036e0  Svc_Realloc ---- */
void * __cdecl Svc_Realloc(void *p,uint size)

{
  void *pvVar1;
  
  pvVar1 = (void *)realloc(p,size);
  return pvVar1;
}

/* ---- 0x00403710  Svc_Fopen ---- */
void * __cdecl Svc_Fopen(char *name,char *mode)

{
  undefined *puVar1;
  
  puVar1 = fopen((uint)name,(uint)mode);
  return puVar1;
}

/* ---- 0x00403730  Svc_Fclose ---- */
void Svc_Fclose(undefined4 param_1)

{
  fclose(param_1);
  return;
}

/* ---- 0x00403740  Svc_Fread ---- */
int __cdecl Svc_Fread(void *file,void *buf,int size)

{
  int iVar1;
  
  iVar1 = fread(buf,1,size,file);
  return iVar1;
}

/* ---- 0x00403760  Svc_Fgets ---- */
char * __cdecl Svc_Fgets(void *file,char *buf,int size)

{
  char *pcVar1;
  
  pcVar1 = (char *)fgets(buf,size,file);
  return pcVar1;
}

/* ---- 0x00403780  Svc_Fwrite ---- */
int __cdecl Svc_Fwrite(void *file,void *buf,int size)

{
  int iVar1;
  
  iVar1 = fwrite(buf,1,size,file);
  return iVar1;
}

/* ---- 0x004037a0  Svc_Feof ---- */
uint Svc_Feof(int param_1)

{
  return *(uint *)(param_1 + 0xc) & 0x10;
}

/* ---- 0x004037b0  Svc_Ftell ---- */
void Svc_Ftell(undefined4 param_1)

{
  ftell(param_1);
  return;
}

/* ---- 0x004037c0  Svc_Fseek ---- */
int __cdecl Svc_Fseek(void *file,int offset,int whence)

{
  int iVar1;
  
  iVar1 = fseek(file,offset,whence);
  return iVar1;
}

/* ---- 0x004037e0  Svc_FileSize ---- */
int __cdecl Svc_FileSize(char *name)

{
  undefined *puVar1;
  int iVar2;
  
  puVar1 = fopen((uint)name,IMG_ADDR(0x004dda54));
  if (puVar1 != (undefined *)0x0) {
    fseek(puVar1,0,2);
    iVar2 = ftell(puVar1);
    fclose(puVar1);
    return iVar2;
  }
  return 0;
}

/* ---- 0x00403830  Svc_Fprintf ---- */
void __cdecl Svc_Fprintf(void *fp,char *fmt,...)

{
  vfprintf(fp,fmt,&STACK0X(0x0000000c));
  return;
}

/* ---- 0x00403850  Svc_Malloc ---- */
void * __cdecl Svc_Malloc(uint size)

{
  undefined *puVar1;
  
  puVar1 = malloc(size);
  return puVar1;
}

/* ---- 0x00403860  Svc_Free ---- */
void __cdecl Svc_Free(void *p)

{
  free(p);
  return;
}

/* ---- 0x00403870  Svc_Identity ---- */
/* Default GrimServices.translate: returns its argument unchanged */

undefined4 Svc_Identity(undefined4 param_1)

{
  return param_1;
}

/* ---- 0x00403880  Services_InitDefaults ---- */
/* Copies the 28-entry default service table (mostly stubs) from 0x004dd9a8 */

void __cdecl Services_InitDefaults(GrimServices *svc)

{
  int iVar1;
  GrimServices *pGVar2;
  
  pGVar2 = &GrimServices_004dd9a8;
  for (iVar1 = 0x1c; iVar1 != 0; iVar1 = iVar1 + -1) {
    svc->flVersion = pGVar2->flVersion;
    pGVar2 = (GrimServices *)&pGVar2->pPrintf;
    svc = (GrimServices *)&svc->pPrintf;
  }
  return;
}

/* ---- 0x004733a0  Services_SetCurrent ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Stores the module service table in g_pServices and captures the FPU control words used for
   rounding modes */

void __cdecl Services_SetCurrent(GrimServices *svc)

{
  undefined1 uVar1;
  int iVar2;
  undefined2 in_FPUControlWord;
  
  g_pSvcMain = svc;
  iVar2 = Plat_ReturnTrue();
  if (iVar2 == 0) {
    return;
  }
  DAT_00900524 = in_FPUControlWord;
  uVar1 = (undefined1)in_FPUControlWord;
  DAT_0090052a = CONCAT11(0xb,uVar1);
  DAT_00900526 = CONCAT11(7,uVar1);
  DAT_00900528 = CONCAT11(0xc,uVar1);
  _DAT_007f6490 = 1;
  return;
}
#endif


/* ---- 0x00473400  Services_Clear ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Services_Clear(void)

{
  _DAT_007f6490 = 0;
  return;
}

/* ---- 0x00473420  Services_InitPlatform ---- */
void Services_InitPlatform(GrimServices *param_1)

{
  Services_InitPlatformTable(param_1);
  return;
}

/* ---- 0x00478000  Svc_DebugPrintf ---- */
/* Platform service printf: formats into g_szDebugBuffer and OutputDebugString */

undefined4 __cdecl Svc_DebugPrintf(char *fmt,...)

{
  _snprintf(&DAT_009056c0,0x400,fmt,&STACK0X(0x00000008));
  OutputDebugStringA(IMG_ADDR(0x009056c0));
  return 1;
}

/* ---- 0x00478030  FUN_00478030 ---- */
void FUN_00478030(uint param_1)

{
  malloc(param_1);
  return;
}

/* ---- 0x00478040  FUN_00478040 ---- */
void FUN_00478040(undefined4 param_1)

{
  free(param_1);
  return;
}

/* ---- 0x00478050  FUN_00478050 ---- */
void FUN_00478050(undefined4 param_1,undefined4 param_2)

{
  realloc(param_1,param_2);
  return;
}

/* ---- 0x00478070  FUN_00478070 ---- */
undefined4 FUN_00478070(undefined4 param_1)

{
  return param_1;
}

/* ---- 0x00478080  Services_InitPlatformTable ---- */
/* Win95 platform service table: debug printf, stdMemory alloc/free/realloc, timeGetTime, stdFile
   I/O, handle memory stubs */

void __cdecl Services_InitPlatformTable(GrimServices *svc)

{
  svc->pPrintf2 = Svc_DebugPrintf;
  svc->pPrintf = Svc_DebugPrintf;
  svc->pWarning = Svc_DebugPrintf;
  svc->pError = Svc_DebugPrintf;
  svc->flVersion = 1000.0;
  svc->pDebug = (void *)0x0;
  svc->pAssertFail = FUN_00477f10;
  svc->pFn_1c = (void *)0x0;
  svc->pAlloc = stdMemory_Alloc;
  svc->pFree = stdMemory_Free;
  svc->pRealloc = stdMemory_Realloc;
  svc->pGetTimeMs = timeGetTime;
  svc->pFopen = stdFile_Open;
  svc->pFclose = stdFile_Close;
  svc->pFread = FUN_00473460;
  svc->pFgets = FUN_004734a0;
  svc->pFwrite = stdFile_Write;
  svc->pFeof = FUN_004734e0;
  svc->pFtell = stdFile_Tell;
  svc->pFseek = stdFile_Seek;
  svc->pFileSize = FUN_00473520;
  svc->pFprintf = FUN_00473570;
  svc->pFn_58 = FUN_004734c0;
  svc->pHAlloc = FUN_00478030;
  svc->pHFree = FUN_00478040;
  svc->pHRealloc = FUN_00478050;
  svc->pHLock = FUN_00478070;
  svc->pHUnlock = Mem_DumpLog;
  return;
}
