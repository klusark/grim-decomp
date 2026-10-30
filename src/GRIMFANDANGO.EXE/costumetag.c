/* GRIMFANDANGO.EXE :: costumetag.c
 * functions 0x00498180 .. 0x00498180 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00498180  CostumeTag_Nop ---- */
/* Empty costume tag handler (returns 1), used for the Destroy slot of mesh/material tags and for
   slots a tag does not need. */

undefined4 CostumeTag_Nop(void)

{
  return 1;
}
