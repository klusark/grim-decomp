/* LUA.DLL :: getsystemcp.c
 * functions 0x1001ce30 .. 0x1001ce30 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x1001ce30  getSystemCP ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl getSystemCP(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if (param_1 == -2) {
    DAT_1002c584 = 1;
                    /* WARNING: Could not recover jumptable at 0x1001ce4d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = GetOEMCP();
    return iVar1;
  }
  if (param_1 == -3) {
    DAT_1002c584 = 1;
                    /* WARNING: Could not recover jumptable at 0x1001ce62. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = GetACP();
    return iVar1;
  }
  bVar2 = param_1 == -4;
  if (bVar2) {
    param_1 = DAT_1002c218;
  }
  DAT_1002c584 = (uint)bVar2;
  return param_1;
}
