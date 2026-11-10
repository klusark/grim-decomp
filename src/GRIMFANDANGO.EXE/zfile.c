/* GRIMFANDANGO.EXE :: zfile.c
 * functions 0x004c5ab0 .. 0x004c5ab0 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004c5ab0  Zfile_Close ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Closes a Zfile object: the plain file or the gzip stream, then frees the object */

void __cdecl Zfile_Close(int *z)

{
  if (*z != 0) {
    if (z[1] == 0) {
      (*(code *)g_pZf_filio_services[1])(*z);
    }
    else {
      ((code *)gzclose)();
    }
  }
  if (z != (int *)0x0) {
    (*(code *)g_pZfile_memory_services[1])(z,s_C__grimsrc_libs_lecsmush_insane__004f1df4,0x11b);
  }
  return;
}
#endif

