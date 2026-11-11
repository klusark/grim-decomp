/* Readable C for GRIMFANDANGO.EXE functions of slice 5 (agent asm_s5; see docs/notes/asm_s5.md).
 *
 * No function of this slice is written in C yet. The slice holds the rdRaster span routines (0x45ba90-0x4710e0, asm-heavy
 * texture spans with register-carried state), the D3D / DirectDraw / DirectInput setup and poll code (their vtable slot
 * numbers and EAX/stack return values are not clear enough to port from the dumps alone), the stdPic / stdGif codecs,
 * sputLua_Startup (unnamed lua_* globals and indirect calls), msc_rle_DecompressBlock (ECX carried between calls), the exception-
 * handler stubs (EBP-frame cleanup funnels), and sputRender_Update / Walker_AvoidActorPath / Collision_TestActorAgainstOthers /
 * WalkPlane_Within, which are already left assembled elsewhere.  Each of those stays in src/GRIMFANDANGO.EXE/asm_funcs.s.
 *
 * Functions added here later need an OVERRIDES marker line before the definition and a block header with the address. */
#include "ghidra_types.h"

#ifdef GRIM_EXE
#include "globals.h"
#include "functions.h"

#endif /* GRIM_EXE */
