/* GRIMFANDANGO.EXE :: textmodule.c
 * functions 0x004aa7b0 .. 0x004aa8d0 (6 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004aa7b0  Text_SysInitialize ---- */
/* Original name Text_SysInitialize (the remaster's GrimFandango (Linux): aligned call in
   sputText_Initialize); was TextModule_Init. */

int __cdecl Text_SysInitialize(GrimServices *svc,void *iface)

{
  int iVar1;
  
  g_pSvcText = svc;
  iVar1 = 1;
  if (g_dwTextSysInitialized == 0) {
    g_dwTextSysInitialized = 1;
    if (iface != (void *)0x0) {
      *(code **)iface = Text_SysInitialize;
      *(code **)((int)iface + 4) = Text_SysTerminate;
      *(code **)((int)iface + 8) = Text_SysStartup;
      *(code **)((int)iface + 0xc) = Text_SysShutdown;
      *(code **)((int)iface + 0x10) = Text_SysSave;
      *(code **)((int)iface + 0x14) = Text_SysRestore;
      *(undefined4 *)((int)iface + 0x18) = 0;
      *(undefined4 *)((int)iface + 0x1c) = 0;
    }
    iVar1 = 0;
  }
  return iVar1;
}

/* ---- 0x004aa810  Text_SysTerminate ---- */
/* Module interface slot 1 (TextModule): called by Engine_ResetSubsystems / when registration fails;
   drops the service table pointer and clears the initialised flag. Original name Text_SysTerminate
   (the remaster's GrimFandango (Linux): aligned call in Text_SysInitialize); was
   TextModule_Terminate. */

void Text_SysTerminate(void)

{
  g_dwTextSysInitialized = 0;
  return;
}

/* ---- 0x004aa820  Text_SysStartup ---- */
/* Module interface slot 2 (TextModule): called by Engine_InitSubsystems, returns 0 on success
   (non-zero makes the whole start-up unwind). _Start fills the identity translation table and wraps
   the default font. Original name Text_SysStartup (the remaster's GrimFandango (Linux): aligned
   call in Text_SysInitialize); was TextModule_Start. */

void Text_SysStartup(void)

{
  int iVar1;
  
  if ((g_dwTextSysInitialized != 0) && (g_dwTextSysStarted == 0)) {
    g_dwTextSysStarted = 1;
    iVar1 = 0;
    do {
      (&g_bLookup)[iVar1] = (char)iVar1;
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0xff);
    Text_WrapLines(&g_pDefaultFont);
  }
  return;
}

/* ---- 0x004aa860  Text_SysShutdown ---- */
/* Module interface slot 3 (TextModule): called by Engine_ShutdownSubsystems in reverse order;
   releases what _Start created. Original name Text_SysShutdown (the remaster's GrimFandango
   (Linux): aligned call in Text_SysInitialize); was TextModule_Stop. */

void Text_SysShutdown(void)

{
  (*g_pSvcText->pHFree)(g_pDefaultFont);
  g_dwTextSysStarted = 0;
  return;
}

/* ---- 0x004aa880  Text_SysSave ---- */
/* Module interface slot 4 (TextModule): save-game writer, calls the SaveGame_Write callback it is
   handed for every field. Original name Text_SysSave (the remaster's GrimFandango (Linux): aligned
   call in Text_SysInitialize); was TextModule_SaveState. */

undefined4 Text_SysSave(code *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0x42747854;
  (*param_1)(&local_4,4);
  local_4 = 1;
  (*param_1)(&local_4,4);
  local_4 = 0;
  (*param_1)(&local_4,4);
  return 0;
}
#undef local_4


/* ---- 0x004aa8d0  Text_SysRestore ---- */
/* Expects 'TxtB', 1, 0 from the read function Original name Text_SysRestore (the remaster's
   GrimFandango (Linux): aligned call in Text_SysInitialize); was TextModule_CheckHeader. */

undefined4 Text_SysRestore(code *param_1)

{
  code *pcVar1;
  undefined4 uVar2;
  
  pcVar1 = param_1;
  uVar2 = 1;
  (*param_1)(&param_1,4);
  if (param_1 == (code *)0x42747854) {
    (*pcVar1)(&param_1,4);
    if (param_1 == (code *)0x1) {
      (*pcVar1)(&param_1,4);
      if (param_1 == (code *)0x0) {
        uVar2 = 0;
      }
    }
  }
  return uVar2;
}
