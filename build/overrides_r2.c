/* Round r2 (2026-11-09): the last assembled functions of GRIMFANDANGO.EXE that are not ordinary code paths.
 * Notes, reachability evidence and the differential tests: docs/notes/r2.md, build/difftest/r2/.
 *
 * Only two symbols need a definition here; the rest of the round is names/ data:
 *   - the eleven SEH / C++ unwind funclets (0x4d5e1c-0x4d6100), FUN_0042003c and the seven LUA.DLL unwind funclets are
 *     in names/lib_replace.json "dead" (their only references are entries of exception tables in the data image that
 *     nothing in the rebuilt programs reads; the entries resolve to link.py's trap stubs);
 *   - _ftol is in names/lib_replace.json "host" (msvcrt.dll exports the same machine code).
 */
#ifdef GRIM_EXE

/* OVERRIDES: FUN_004addf0 */
/* __chkstk / _alloca_probe of the MSVC 6 runtime (0x004addf0): EAX = the number of bytes to allocate on the stack; it
 * touches every page from the caller's ESP down to ESP - EAX in order (so that the guard page grows the stack), sets
 * ESP = caller's ESP - EAX, keeps ECX and returns through the saved return address.  The register calling convention
 * cannot be written in C, and msvcrt.dll does not export it; libgcc's ___chkstk (alias __alloca) has the same
 * interface: same final ESP and ECX, the same pages probed in the same order.  Differences that no caller can see: it
 * probes with `or dword [ecx], 0` (a store of the unchanged value) where the original reads (`test [ecx], eax`),
 * for a multiple of 4 KiB the original probes the last page twice, and EAX on return is the old ESP instead of the
 * return address (EAX is scratch for __chkstk callers).  Nothing in the rebuilt exe calls it (its three callers,
 * rdModel3_LoadText, SectorList_ShrinkWalkSectors and the runtime's _chsize, are gcc C or dead); the symbol stays
 * defined so that any future reference gets a working probe.  A tail jump: the stack is untouched, so ___chkstk sees
 * exactly the entry state the original saw. */
__asm__(".text\n"
        "\t.globl _FUN_004addf0\n"
        "_FUN_004addf0:\n"
        "\tjmp ___chkstk\n");

/* OVERRIDES: FUN_004d60e9 */
/* The exception handler that ObjectState_Construct (0x004aa410) registers in fs:[0] around the construction of its two
 * StateImage members.  In the original it is a two-instruction thunk, `mov eax, 0x004dacc8 (FuncInfo); jmp
 * __CxxFrameHandler`, whose table points to the unwind funclets 0x004d60d0 / 0x004d60db (StateImage_Release of the
 * members on [EBP-0x10], an MSVC frame layout gcc does not have).  The decompiled C of the thunk lost the EAX load
 * (`__CxxFrameHandler();` without its FuncInfo), and the compiled ObjectState_Construct still links the frame (the
 * seh_strip rule of tools/build_src.py does not match its frame_locals macros), so an exception or a longjmp unwinding
 * through the constructor would have called msvcrt's __CxxFrameHandler with a garbage FuncInfo.  This version is a
 * valid SEH handler that declines: ExceptionContinueSearch (1), for dispatch and unwind alike, i.e. the frame behaves
 * as if it were not there.  The game never throws (the exe has no _CxxThrowException) and nothing the constructor
 * calls (StateImage_Init -> Resource_Load ...) enters Lua, the only source of a longjmp, so the original cleanup never
 * ran in practice either. */
__asm__(".text\n"
        "\t.globl _FUN_004d60e9\n"
        "_FUN_004d60e9:\n"
        "\tmovl $1, %eax\n"
        "\tret\n");

#endif
