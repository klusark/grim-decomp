/* Round r2 (2026-11-09): the last assembled functions of GRIMFANDANGO.EXE that are not ordinary code paths.
 * Notes, reachability evidence and the differential tests: docs/notes/r2.md, build/difftest/r2/.
 *
 * Only one symbol needs a definition here; the rest of the round is names/ data:
 *   - the eleven SEH / C++ unwind funclets (0x4d5e1c-0x4d6100), FUN_0042003c and the seven LUA.DLL unwind funclets are
 *     in names/lib_replace.json "dead" (their only references are entries of exception tables in the data image that
 *     nothing in the rebuilt programs reads; the entries resolve to link.py's trap stubs);
 *   - _ftol is in names/lib_replace.json "host" (msvcrt.dll exports the same machine code).
 * (Round r2 also gave FUN_004d60e9, the __CxxFrameHandler thunk that the compiled ObjectState_Construct registered in
 * fs:[0], a declining handler here.  Round s3 made tools/build_src.py's seh_strip rule remove that registration, so
 * nothing references the thunk any more; it and the other handler thunks are names/lib_replace.json "dead",
 * docs/notes/s3.md.)
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

#endif
