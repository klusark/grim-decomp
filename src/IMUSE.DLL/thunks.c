/* IMUSE.DLL: jump thunks. Each is a single `JMP target` instruction in the
   original; Ghidra marks them as thunks and decompiles no body. */

/* ImTerminate @ 0x10004b10 */
__asm__(".text\n.globl _ImTerminate\n_ImTerminate:\n\tjmp _Im_ShutdownSubsystems\n");
/* ImProcessStreams @ 0x10004ef0 */
__asm__(".text\n.globl _ImProcessStreams\n_ImProcessStreams:\n\tjmp _Im_ProcessStreamsImpl\n");
