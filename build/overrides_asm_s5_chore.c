/* Readable C for CHORE.DLL costume loader functions of slice 5 (agent asm_s5; see docs/notes/asm_s5.md).
 *
 * No function of this slice is written in C yet, so all five stay assembled:
 *   Cos_LoadEntry (0x10001770)  Ghidra output has an unfinished goto into the duplicate-component loop, which reads a
 *                               register-carried value (unaff_retaddr) as its loop state; the continuation is not clear enough.
 *   Cos_ReadTagsSection (0x100041e0)   parses with format strings at 0x10010538 / 0x10010524 that are unnamed .data text, and stores
 *                               into g_aTagLookups by index; the parse results are read from the stack in a register-carried order.
 *   Cos_ReadComponentsSection (0x10004390)   reads unaff_retaddr as the costume index inside a loop (register-carried), with absolute
 *                               .data buffers 0x10013e10 and the format strings at 0x10010574 / 0x10010544 unnamed.
 *   Cos_ReadChoresSection (0x100047f0)   parses records into a 0x2c-byte table at +0x34 with the unnamed format strings at 0x100105c0 /
 *                               0x100105ac; the rest of the body is not visible in the dump, so it was not checked end to end.
 *   Cos_ReadKeysSection (0x10004970)   not ported (its dump was not checked in this pass).
 * Each function stays in src/CHORE.DLL/asm_funcs.s.
 *
 * Functions added here later need an OVERRIDES marker line before the definition and a block header with the address. */
#include "ghidra_types.h"

#ifdef GRIM_CHORE
#include "globals.h"
#include "functions.h"

#endif /* GRIM_CHORE */
