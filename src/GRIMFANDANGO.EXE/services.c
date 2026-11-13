/* GRIMFANDANGO.EXE :: services.c
 * functions 0x004035b0 .. 0x00478080 (27 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004035b0  defaultStatusPrint ---- */
/* Default GrimServices.printf: vsprintf into the shared buffer then printf Original name
   defaultStatusPrint (the remaster's GrimFandango (Linux): slot 1 of defaultHostServices
   (g_aDefaultHostServices)); was Svc_Printf. */

undefined4 __cdecl defaultStatusPrint(char *fmt,...)

{
  undefined4 uVar1;
  
  uVar1 = vsprintf(&g_aBuffer,fmt,&STACK0X(0x00000008));
  printf(&DAT_004dda18,&g_aBuffer);
  return uVar1;
}

/* ---- 0x004035e0  defaultMessagePrint ---- */
/* Original name defaultMessagePrint (the remaster's GrimFandango (Linux): slot 2 of
   defaultHostServices (g_aDefaultHostServices)); was Svc_Printf2. */

uint __cdecl defaultMessagePrint(uint param_1)

{
  uint uVar1;
  
  uVar1 = vsprintf(&g_aBuffer,param_1,&STACK0X(0x00000008));
  printf(&DAT_004dda18,&g_aBuffer);
  return uVar1;
}

/* ---- 0x00403610  defaultWarningPrint ---- */
/* Default GrimServices.warning: prints 'WARNING: %s' Original name defaultWarningPrint (the
   remaster's GrimFandango (Linux): strings: 'WARNING: %s'); was Svc_Warning. */

uint __cdecl defaultWarningPrint(uint param_1)

{
  uint uVar1;
  
  uVar1 = vsprintf(&g_aBuffer,param_1,&STACK0X(0x00000008));
  printf(s_WARNING___s_004dda1c,&g_aBuffer);
  return uVar1;
}

/* ---- 0x00403640  defaultErrorPrint ---- */
/* Default GrimServices.error: prints 'ERROR: %s' Original name defaultErrorPrint (the remaster's
   GrimFandango (Linux): strings: 'ERROR: %s'); was Svc_Error. */

uint __cdecl defaultErrorPrint(uint param_1)

{
  uint uVar1;
  
  uVar1 = vsprintf(&g_aBuffer,param_1,&STACK0X(0x00000008));
  printf(s_ERROR___s_004dda28,&g_aBuffer);
  return uVar1;
}

/* ---- 0x00403670  defaultDebugPrint ---- */
/* Default GrimServices.debug: prints 'DEBUG: %s' Original name defaultDebugPrint (the remaster's
   GrimFandango (Linux): strings: 'DEBUG: %s'); was Svc_Debug. */

uint __cdecl defaultDebugPrint(uint param_1)

{
  uint uVar1;
  
  uVar1 = vsprintf(&g_aBuffer,param_1,&STACK0X(0x00000008));
  printf(s_DEBUG___s_004dda34,&g_aBuffer);
  return uVar1;
}

/* ---- 0x004036a0  defaultAssert ---- */
/* Default GrimServices.assertFail: prints 'ASSERT: %s, %d: %s' and exit(1) Original name
   defaultAssert (the remaster's GrimFandango (Linux): strings: 'ASSERT! (%s:%d) %s'); was
   Svc_AssertFail. */

void __cdecl defaultAssert(char *expr,char *file,int line)

{
  printf(s_ASSERT____s__d___s_004dda40,file,line,expr);
  exit(1);
  return;
}

/* ---- 0x004036d0  defaultAtExit ---- */
/* Original name defaultAtExit (the remaster's GrimFandango (Linux): slot 7 of defaultHostServices
   (g_aDefaultHostServices)); was Svc_Fn1c. */

void __cdecl defaultAtExit(uint param_1)

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

/* ---- 0x00403710  defaultFileOpen ---- */
/* Original name defaultFileOpen (the remaster's GrimFandango (Linux): slot 12 of
   defaultHostServices (g_aDefaultHostServices)); was Svc_Fopen. */

void * __cdecl defaultFileOpen(char *name,char *mode)

{
  undefined *puVar1;
  
  puVar1 = fopen((uint)name,(uint)mode);
  return puVar1;
}

/* ---- 0x00403730  defaultFileClose ---- */
/* Original name defaultFileClose (the remaster's GrimFandango (Linux): slot 13 of
   defaultHostServices (g_aDefaultHostServices)); was Svc_Fclose. */

void __cdecl defaultFileClose(uint param_1)

{
  fclose(param_1);
  return;
}

/* ---- 0x00403740  defaultFileRead ---- */
/* Original name defaultFileRead (the remaster's GrimFandango (Linux): slot 14 of
   defaultHostServices (g_aDefaultHostServices)); was Svc_Fread. */

int __cdecl defaultFileRead(void *file,void *buf,int size)

{
  int iVar1;
  
  iVar1 = fread(buf,1,size,file);
  return iVar1;
}

/* ---- 0x00403760  defaultFileGets ---- */
/* Original name defaultFileGets (the remaster's GrimFandango (Linux): slot 15 of
   defaultHostServices (g_aDefaultHostServices)); was Svc_Fgets. */

char * __cdecl defaultFileGets(void *file,char *buf,int size)

{
  char *pcVar1;
  
  pcVar1 = (char *)fgets(buf,size,file);
  return pcVar1;
}

/* ---- 0x00403780  defaultFileWrite ---- */
/* Original name defaultFileWrite (the remaster's GrimFandango (Linux): slot 16 of
   defaultHostServices (g_aDefaultHostServices)); was Svc_Fwrite. */

int __cdecl defaultFileWrite(void *file,void *buf,int size)

{
  int iVar1;
  
  iVar1 = fwrite(buf,1,size,file);
  return iVar1;
}

/* ---- 0x004037a0  defaultFileEOF ---- */
/* Original name defaultFileEOF (the remaster's GrimFandango (Linux): slot 17 of defaultHostServices
   (g_aDefaultHostServices)); was Svc_Feof. */

uint __cdecl defaultFileEOF(int param_1)

{
  return *(uint *)(param_1 + 0xc) & 0x10;
}

/* ---- 0x004037b0  defaultFileTell ---- */
/* Original name defaultFileTell (the remaster's GrimFandango (Linux): slot 18 of
   defaultHostServices (g_aDefaultHostServices)); was Svc_Ftell. */

void __cdecl defaultFileTell(uint param_1)

{
  ftell(param_1);
  return;
}

/* ---- 0x004037c0  defaultFileSeek ---- */
/* Original name defaultFileSeek (the remaster's GrimFandango (Linux): slot 19 of
   defaultHostServices (g_aDefaultHostServices)); was Svc_Fseek. */

int __cdecl defaultFileSeek(void *file,int offset,int whence)

{
  int iVar1;
  
  iVar1 = fseek(file,offset,whence);
  return iVar1;
}

/* ---- 0x004037e0  defaultFileSize ---- */
/* Original name defaultFileSize (the remaster's GrimFandango (Linux): slot 20 of
   defaultHostServices (g_aDefaultHostServices)); was Svc_FileSize. */

int __cdecl defaultFileSize(char *name)

{
  undefined *puVar1;
  int iVar2;
  
  puVar1 = fopen((uint)name,((unsigned)(uintptr_t)&DAT_004dda54));
  if (puVar1 != (undefined *)0x0) {
    fseek(puVar1,0,2);
    iVar2 = ftell(puVar1);
    fclose(puVar1);
    return iVar2;
  }
  return 0;
}

/* ---- 0x00403830  defaultFilePrintf ---- */
/* Original name defaultFilePrintf (the remaster's GrimFandango (Linux): slot 21 of
   defaultHostServices (g_aDefaultHostServices)); was Svc_Fprintf. */

void __cdecl defaultFilePrintf(void *fp,char *fmt,...)

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

/* ---- 0x00403870  defaultLockHandle ---- */
/* Default GrimServices.translate: returns its argument unchanged Original name defaultLockHandle
   (the remaster's GrimFandango (Linux): slot 26 of defaultHostServices (g_aDefaultHostServices));
   was Svc_Identity. */

uint __cdecl defaultLockHandle(uint param_1)

{
  return param_1;
}

/* ---- 0x00403880  HostServicesInitialize ---- */
/* Copies the 28-entry default service table (mostly stubs) from 0x004dd9a8 Original name
   HostServicesInitialize (the remaster's GrimFandango (Linux): the first call of Main_Startup, same
   body (copies the default host-service table)); was Services_InitDefaults. */

void __cdecl HostServicesInitialize(GrimServices *svc)

{
  int iVar1;
  GrimServices *pGVar2;
  
  pGVar2 = &g_aDefaultHostServices;
  for (iVar1 = 0x1c; iVar1 != 0; iVar1 = iVar1 + -1) {
    svc->flVersion = pGVar2->flVersion;
    pGVar2 = (GrimServices *)&pGVar2->pPrintf;
    svc = (GrimServices *)&svc->pPrintf;
  }
  return;
}

/* ---- 0x004733a0  stdStartup ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Stores the module service table in g_pServices and captures the FPU control words used for
   rounding modes Original name stdStartup (the remaster's GrimFandango (Linux): called from
   Main_Startup with hs before PolyglotInitialize, stores std_pHS then starts the platform layer);
   was Services_SetCurrent. */

void __cdecl stdStartup(GrimServices *svc)

{
  undefined1 uVar1;
  uint uVar2;
  undefined2 in_FPUControlWord;
  
  g_pStd_HS = svc;
  uVar2 = Plat_ReturnTrue();
  if (uVar2 == 0) {
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


/* ---- 0x00473400  stdShutdown ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Original name stdShutdown (the remaster's GrimFandango (Linux): the last call of Main_Shutdown in
   both builds; clears the services pointer stdStartup sets); was Services_Clear. */

void __cdecl stdShutdown(void)

{
  _DAT_007f6490 = 0;
  return;
}

/* ---- 0x00473420  stdInitServices ---- */
/* Original name stdInitServices (the remaster's GrimFandango (Linux): the host-service set-up call
   of Main_Startup before stdStartup); was Services_InitPlatform. */

void __cdecl stdInitServices(GrimServices *param_1)

{
  stdPlatform_InitServices(param_1);
  return;
}

/* ---- 0x00478000  stdPlatform_Printf ---- */
/* Platform service printf: formats into g_szDebugBuffer and OutputDebugString Original name
   stdPlatform_Printf (the remaster's GrimFandango (Linux): the formatter all five grimdemo print
   callbacks call (formats into std_genBuffer)); was Svc_DebugPrintf. */

undefined4 __cdecl stdPlatform_Printf(char *fmt,...)

{
  _vsnprintf(&g_bStd_genBuffer,0x400,fmt,&STACK0X(0x00000008));
  OutputDebugStringA(((unsigned)(uintptr_t)&g_bStd_genBuffer));
  return 1;
}

/* ---- 0x00478080  stdPlatform_InitServices ---- */
/* Win95 platform service table: debug printf, stdMemory alloc/free/realloc, timeGetTime, stdFile
   I/O, handle memory stubs Original name stdPlatform_InitServices (the remaster's GrimFandango
   (Linux): same body (the four print services stdPlatform_Printf, version 1000.0,
   stdPlatform_Assert, the memory and time services)); was Services_InitPlatformTable. */

void __cdecl stdPlatform_InitServices(GrimServices *svc)

{
  svc->pPrintf2 = stdPlatform_Printf;
  svc->pPrintf = stdPlatform_Printf;
  svc->pWarning = stdPlatform_Printf;
  svc->pError = stdPlatform_Printf;
  svc->flVersion = 1000.0;
  svc->pDebug = (void *)0x0;
  svc->pAssertFail = stdPlatform_Assert;
  svc->pFn_1c = (void *)0x0;
  svc->pAlloc = stdMemory_Alloc;
  svc->pFree = stdMemory_Free;
  svc->pRealloc = stdMemory_Realloc;
  svc->pGetTimeMs = timeGetTime;
  svc->pFopen = stdFileOpen;
  svc->pFclose = stdFileClose;
  svc->pFread = stdFileRead;
  svc->pFgets = stdFileGets;
  svc->pFwrite = stdFileWrite;
  svc->pFeof = stdFeof;
  svc->pFtell = stdFtell;
  svc->pFseek = stdFseek;
  svc->pFileSize = stdFileSize;
  svc->pFprintf = stdFilePrintf;
  svc->pFn_58 = stdFileGetws;
  svc->pHAlloc = stdPlatform_AllocHandle;
  svc->pHFree = stdPlatform_FreeHandle;
  svc->pHRealloc = stdPlatform_ReallocHandle;
  svc->pHLock = stdPlatform_LockHandle;
  svc->pHUnlock = Mem_DumpLog;
  return;
}
