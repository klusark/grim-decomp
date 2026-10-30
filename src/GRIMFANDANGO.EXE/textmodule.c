/* GRIMFANDANGO.EXE :: textmodule.c
 * functions 0x004aa7b0 .. 0x004aa8d0 (6 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004aa7b0  TextModule_Init ---- */
int __cdecl TextModule_Init(GrimServices *svc,void *iface)

{
  int iVar1;
  
  g_pSvcText = svc;
  iVar1 = 1;
  if (UINT_008d0980 == 0) {
    UINT_008d0980 = 1;
    if (iface != (void *)0x0) {
      *(code **)iface = TextModule_Init;
      *(code **)((int)iface + 4) = TextModule_Terminate;
      *(code **)((int)iface + 8) = TextModule_Start;
      *(code **)((int)iface + 0xc) = TextModule_Stop;
      *(code **)((int)iface + 0x10) = TextModule_SaveState;
      *(code **)((int)iface + 0x14) = TextModule_CheckHeader;
      *(undefined4 *)((int)iface + 0x18) = 0;
      *(undefined4 *)((int)iface + 0x1c) = 0;
    }
    iVar1 = 0;
  }
  return iVar1;
}

/* ---- 0x004aa810  TextModule_Terminate ---- */
/* Module interface slot 1 (TextModule): called by Engine_ResetSubsystems / when registration fails;
   drops the service table pointer and clears the initialised flag. */

void TextModule_Terminate(void)

{
  UINT_008d0980 = 0;
  return;
}

/* ---- 0x004aa820  TextModule_Start ---- */
/* Module interface slot 2 (TextModule): called by Engine_InitSubsystems, returns 0 on success
   (non-zero makes the whole start-up unwind). _Start fills the identity translation table and wraps
   the default font. */

void TextModule_Start(void)

{
  int iVar1;
  
  if ((UINT_008d0980 != 0) && (UINT_008d0984 == 0)) {
    UINT_008d0984 = 1;
    iVar1 = 0;
    do {
      (&DAT_008d0880)[iVar1] = (char)iVar1;
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0xff);
    Text_WrapLines(&g_pDefaultFont);
  }
  return;
}

/* ---- 0x004aa860  TextModule_Stop ---- */
/* Module interface slot 3 (TextModule): called by Engine_ShutdownSubsystems in reverse order;
   releases what _Start created. */

void TextModule_Stop(void)

{
  (*g_pSvcText->pHFree)(g_pDefaultFont);
  UINT_008d0984 = 0;
  return;
}

/* ---- 0x004aa880  TextModule_SaveState ---- */
/* Module interface slot 4 (TextModule): save-game writer, calls the SaveGame_Write callback it is
   handed for every field. */

undefined4 TextModule_SaveState(code *param_1)

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


/* ---- 0x004aa8d0  TextModule_CheckHeader ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Expects 'TxtB', 1, 0 from the read function */

undefined4 TextModule_CheckHeader(code *param_1)

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
#endif

