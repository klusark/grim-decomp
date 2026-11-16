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

uint __cdecl defaultStatusPrint(char *fmt,...)

{
  uint uVar1;
  
  uVar1 = vsprintf(((unsigned)(uintptr_t)&g_aBuffer),(uint)fmt,(uint)&STACK0X(0x00000008));
  printf(s__s_004dda18,&g_aBuffer);
  return uVar1;
}

/* ---- 0x004035e0  defaultMessagePrint ---- */
/* Original name defaultMessagePrint (the remaster's GrimFandango (Linux): slot 2 of
   defaultHostServices (g_aDefaultHostServices)); was Svc_Printf2. */

uint __cdecl defaultMessagePrint(char *fmt,...)

{
  uint uVar1;
  
  uVar1 = vsprintf(((unsigned)(uintptr_t)&g_aBuffer),(uint)fmt,(uint)&STACK0X(0x00000008));
  printf(s__s_004dda18,&g_aBuffer);
  return uVar1;
}

/* ---- 0x00403610  defaultWarningPrint ---- */
/* Default GrimServices.warning: prints 'WARNING: %s' Original name defaultWarningPrint (the
   remaster's GrimFandango (Linux): strings: 'WARNING: %s'); was Svc_Warning. */

uint __cdecl defaultWarningPrint(char *fmt,...)

{
  uint uVar1;
  
  uVar1 = vsprintf(((unsigned)(uintptr_t)&g_aBuffer),(uint)fmt,(uint)&STACK0X(0x00000008));
  printf(s_WARNING___s_004dda1c,&g_aBuffer);
  return uVar1;
}

/* ---- 0x00403640  defaultErrorPrint ---- */
/* Default GrimServices.error: prints 'ERROR: %s' Original name defaultErrorPrint (the remaster's
   GrimFandango (Linux): strings: 'ERROR: %s'); was Svc_Error. */

uint __cdecl defaultErrorPrint(char *fmt,...)

{
  uint uVar1;
  
  uVar1 = vsprintf(((unsigned)(uintptr_t)&g_aBuffer),(uint)fmt,(uint)&STACK0X(0x00000008));
  printf(s_ERROR___s_004dda28,&g_aBuffer);
  return uVar1;
}

/* ---- 0x00403670  defaultDebugPrint ---- */
/* Default GrimServices.debug: prints 'DEBUG: %s' Original name defaultDebugPrint (the remaster's
   GrimFandango (Linux): strings: 'DEBUG: %s'); was Svc_Debug. */

uint __cdecl defaultDebugPrint(char *fmt,...)

{
  uint uVar1;
  
  uVar1 = vsprintf(((unsigned)(uintptr_t)&g_aBuffer),(uint)fmt,(uint)&STACK0X(0x00000008));
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

void __cdecl defaultAtExit(uint fn)

{
  atexit(fn);
  return;
}

/* ---- 0x004036e0  Svc_Realloc ---- */
void * __cdecl Svc_Realloc(void *p,uint size)

{
  undefined4 *puVar1;
  
  puVar1 = realloc(p,size);
  return puVar1;
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

void __cdecl defaultFileClose(uint f)

{
  fclose(f);
  return;
}

/* ---- 0x00403740  defaultFileRead ---- */
/* Original name defaultFileRead (the remaster's GrimFandango (Linux): slot 14 of
   defaultHostServices (g_aDefaultHostServices)); was Svc_Fread. */

int __cdecl defaultFileRead(void *file,void *buf,int size)

{
  uint uVar1;
  
  uVar1 = fread((uint)buf,1,size,(uint)file);
  return uVar1;
}

/* ---- 0x00403760  defaultFileGets ---- */
/* Original name defaultFileGets (the remaster's GrimFandango (Linux): slot 15 of
   defaultHostServices (g_aDefaultHostServices)); was Svc_Fgets. */

char * __cdecl defaultFileGets(void *file,char *buf,int size)

{
  char *pcVar1;
  
  pcVar1 = fgets(buf,size,file);
  return pcVar1;
}

/* ---- 0x00403780  defaultFileWrite ---- */
/* Original name defaultFileWrite (the remaster's GrimFandango (Linux): slot 16 of
   defaultHostServices (g_aDefaultHostServices)); was Svc_Fwrite. */

int __cdecl defaultFileWrite(void *file,void *buf,int size)

{
  uint uVar1;
  
  uVar1 = fwrite((uint)buf,1,size,(uint)file);
  return uVar1;
}

/* ---- 0x004037a0  defaultFileEOF ---- */
/* Original name defaultFileEOF (the remaster's GrimFandango (Linux): slot 17 of defaultHostServices
   (g_aDefaultHostServices)); was Svc_Feof. */

uint __cdecl defaultFileEOF(int f)

{
  return *(uint *)(f + 0xc) & 0x10;
}

/* ---- 0x004037b0  defaultFileTell ---- */
/* Original name defaultFileTell (the remaster's GrimFandango (Linux): slot 18 of
   defaultHostServices (g_aDefaultHostServices)); was Svc_Ftell. */

void __cdecl defaultFileTell(uint f)

{
  ftell(f);
  return;
}

/* ---- 0x004037c0  defaultFileSeek ---- */
/* Original name defaultFileSeek (the remaster's GrimFandango (Linux): slot 19 of
   defaultHostServices (g_aDefaultHostServices)); was Svc_Fseek. */

int __cdecl defaultFileSeek(void *file,int offset,int whence)

{
  uint uVar1;
  
  uVar1 = fseek((uint)file,offset,whence);
  return uVar1;
}

/* ---- 0x004037e0  defaultFileSize ---- */
/* Original name defaultFileSize (the remaster's GrimFandango (Linux): slot 20 of
   defaultHostServices (g_aDefaultHostServices)); was Svc_FileSize. */

int __cdecl defaultFileSize(char *name)

{
  undefined *puVar1;
  uint uVar2;
  
  puVar1 = fopen((uint)name,((unsigned)(uintptr_t)&s_r_004dda54));
  if (puVar1 != (undefined *)0x0) {
    fseek((uint)puVar1,0,2);
    uVar2 = ftell((uint)puVar1);
    fclose((int)puVar1);
    return uVar2;
  }
  return 0;
}

/* ---- 0x00403830  defaultFilePrintf ---- */
/* Original name defaultFilePrintf (the remaster's GrimFandango (Linux): slot 21 of
   defaultHostServices (g_aDefaultHostServices)); was Svc_Fprintf. */

void __cdecl defaultFilePrintf(void *fp,char *fmt,...)

{
  vfprintf((uint)fp,(uint)fmt,(uint)&STACK0X(0x0000000c));
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
  free((int)p);
  return;
}

/* ---- 0x00403870  defaultLockHandle ---- */
/* Default GrimServices.translate: returns its argument unchanged Original name defaultLockHandle
   (the remaster's GrimFandango (Linux): slot 26 of defaultHostServices (g_aDefaultHostServices));
   was Svc_Identity. */

uint __cdecl defaultLockHandle(uint handle)

{
  return handle;
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

void __cdecl stdInitServices(GrimServices *svc)

{
  stdPlatform_InitServices(svc);
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
  svc->flVersion = 1000.0f;
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


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern char f_LecShare_Nop[] __asm__("_LecShare_Nop");
extern char f_Lua_Stub[] __asm__("_Lua_Stub");
extern char f_Svc_Free[] __asm__("_Svc_Free");
extern char f_Svc_Malloc[] __asm__("_Svc_Malloc");
extern char f_Svc_Realloc[] __asm__("_Svc_Realloc");
extern char f_defaultAssert[] __asm__("_defaultAssert");
extern char f_defaultAtExit[] __asm__("_defaultAtExit");
extern char f_defaultDebugPrint[] __asm__("_defaultDebugPrint");
extern char f_defaultErrorPrint[] __asm__("_defaultErrorPrint");
extern char f_defaultFileClose[] __asm__("_defaultFileClose");
extern char f_defaultFileEOF[] __asm__("_defaultFileEOF");
extern char f_defaultFileGets[] __asm__("_defaultFileGets");
extern char f_defaultFileOpen[] __asm__("_defaultFileOpen");
extern char f_defaultFilePrintf[] __asm__("_defaultFilePrintf");
extern char f_defaultFileRead[] __asm__("_defaultFileRead");
extern char f_defaultFileSeek[] __asm__("_defaultFileSeek");
extern char f_defaultFileSize[] __asm__("_defaultFileSize");
extern char f_defaultFileTell[] __asm__("_defaultFileTell");
extern char f_defaultFileWrite[] __asm__("_defaultFileWrite");
extern char f_defaultGetTimerTick[] __asm__("_defaultGetTimerTick");
extern char f_defaultLockHandle[] __asm__("_defaultLockHandle");
extern char f_defaultMessagePrint[] __asm__("_defaultMessagePrint");
extern char f_defaultStatusPrint[] __asm__("_defaultStatusPrint");
extern char f_defaultWarningPrint[] __asm__("_defaultWarningPrint");
extern unsigned char grim_def_DAT_007f6490[8] __asm__("_DAT_007f6490");
extern unsigned short grim_def_DAT_00900528 __asm__("_DAT_00900528");
extern unsigned short grim_def_DAT_0090052a __asm__("_DAT_0090052a");
extern unsigned char grim_def_g_aBuffer[1024] __asm__("_g_aBuffer");
extern void *grim_def_g_aDefaultHostServices[28] __asm__("_g_aDefaultHostServices");
extern char grim_def_s_ASSERT____s__d___s_004dda40[20] __asm__("_s_ASSERT____s__d___s_004dda40");
extern char grim_def_s_DEBUG___s_004dda34[12] __asm__("_s_DEBUG___s_004dda34");
extern char grim_def_s_ERROR___s_004dda28[12] __asm__("_s_ERROR___s_004dda28");
extern char grim_def_s_WARNING___s_004dda1c[12] __asm__("_s_WARNING___s_004dda1c");
extern char grim_def_s__s_004dda18[4] __asm__("_s__s_004dda18");
/* 0x004dd9a8, 112 bytes */ GRIM_DATA("004dd9a8") void *grim_def_g_aDefaultHostServices[28] __asm__("_g_aDefaultHostServices") = {
    (void *)0x447a0000, (void *)f_defaultStatusPrint, (void *)f_defaultMessagePrint, (void *)f_defaultWarningPrint,
    (void *)f_defaultErrorPrint, (void *)f_defaultDebugPrint, (void *)f_defaultAssert, (void *)f_defaultAtExit,
    (void *)f_Svc_Malloc, (void *)f_Svc_Free, (void *)f_Svc_Realloc, (void *)f_defaultGetTimerTick,
    (void *)f_defaultFileOpen, (void *)f_defaultFileClose, (void *)f_defaultFileRead, (void *)f_defaultFileGets,
    (void *)f_defaultFileWrite, (void *)f_defaultFileEOF, (void *)f_defaultFileTell, (void *)f_defaultFileSeek,
    (void *)f_defaultFileSize, (void *)f_defaultFilePrintf, (void *)f_LecShare_Nop, (void *)f_Svc_Malloc,
    (void *)f_Svc_Free, (void *)f_Svc_Realloc, (void *)f_defaultLockHandle, (void *)f_Lua_Stub
};
/* 0x004dda18, 4 bytes */ GRIM_DATA("004dda18") char grim_def_s__s_004dda18[4] __asm__("_s__s_004dda18") = "%s";
/* 0x004dda1c, 12 bytes */ GRIM_DATA("004dda1c") char grim_def_s_WARNING___s_004dda1c[12] __asm__("_s_WARNING___s_004dda1c") = "WARNING: %s";
/* 0x004dda28, 12 bytes */ GRIM_DATA("004dda28") char grim_def_s_ERROR___s_004dda28[12] __asm__("_s_ERROR___s_004dda28") = "ERROR: %s";
/* 0x004dda34, 12 bytes */ GRIM_DATA("004dda34") char grim_def_s_DEBUG___s_004dda34[12] __asm__("_s_DEBUG___s_004dda34") = "DEBUG: %s";
/* 0x004dda40, 20 bytes */ GRIM_DATA("004dda40") char grim_def_s_ASSERT____s__d___s_004dda40[20] __asm__("_s_ASSERT____s__d___s_004dda40") = "ASSERT! (%s:%d) %s";
/* 0x004f5aa0, 1024 bytes */ GRIM_DATA("004f5aa0") unsigned char grim_def_g_aBuffer[1024] __asm__("_g_aBuffer") = {0};
/* 0x007f6490, 8 bytes */ GRIM_DATA("007f6490") unsigned char grim_def_DAT_007f6490[8] __asm__("_DAT_007f6490") = {0};
/* 0x00900528, 2 bytes */ GRIM_DATA("00900528") unsigned short grim_def_DAT_00900528 __asm__("_DAT_00900528") = 0x0;
/* 0x0090052a, 2 bytes */ GRIM_DATA("00900528") unsigned short grim_def_DAT_0090052a __asm__("_DAT_0090052a") = 0x0;
