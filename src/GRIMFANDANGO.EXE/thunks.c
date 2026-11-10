/* GRIMFANDANGO.EXE: jump thunks. Each is a single `JMP target` instruction in the
   original; Ghidra marks them as thunks and decompiles no body. */

/* Svc_Fn2c @ 0x00403700 */
__asm__(".text\n.globl _Svc_Fn2c\n_Svc_Fn2c:\n\tjmp _Clock_ElapsedMs\n");
/* sputLua_BuildCache @ 0x00498e30 */
__asm__(".text\n.globl _sputLua_BuildCache\n_sputLua_BuildCache:\n\tjmp _SectorList_SaveForShrink\n");
/* sputLua_RevertCache @ 0x00498e40 */
__asm__(".text\n.globl _sputLua_RevertCache\n_sputLua_RevertCache:\n\tjmp _SectorList_RestoreAfterShrink\n");
/* sputLua_DumpMemoryLogL @ 0x00498ff0 */
__asm__(".text\n.globl _sputLua_DumpMemoryLogL\n_sputLua_DumpMemoryLogL:\n\tjmp _Mem_DumpLog\n");
/* sputLua_StopMovieL @ 0x0049e850 */
__asm__(".text\n.globl _sputLua_StopMovieL\n_sputLua_StopMovieL:\n\tjmp _Movie_Stop\n");
/* sputLua_SpewStartup @ 0x0049efa0 */
__asm__(".text\n.globl _sputLua_SpewStartup\n_sputLua_SpewStartup:\n\tjmp _Spew_Startup\n");
/* sputLua_SpewShutdown @ 0x0049efb0 */
__asm__(".text\n.globl _sputLua_SpewShutdown\n_sputLua_SpewShutdown:\n\tjmp _Spew_Shutdown\n");
/* sputLua_ImStopRecording @ 0x004a0f70 */
__asm__(".text\n.globl _sputLua_ImStopRecording\n_sputLua_ImStopRecording:\n\tjmp _ImStopRecording\n");
/* sputLua_ImStopAllSounds @ 0x004a1080 */
__asm__(".text\n.globl _sputLua_ImStopAllSounds\n_sputLua_ImStopAllSounds:\n\tjmp _ImStopAllSounds\n");
/* sputLua_ImStopVoice @ 0x004a1630 */
__asm__(".text\n.globl _sputLua_ImStopVoice\n_sputLua_ImStopVoice:\n\tjmp _SoundStopVoiceStream\n");
/* sputLua_ImPause @ 0x004a1790 */
__asm__(".text\n.globl _sputLua_ImPause\n_sputLua_ImPause:\n\tjmp _ImPause\n");
/* sputLua_ImResume @ 0x004a17a0 */
__asm__(".text\n.globl _sputLua_ImResume\n_sputLua_ImResume:\n\tjmp _ImResume\n");
/* sputLua_CleanBuffer @ 0x004a1ac0 */
__asm__(".text\n.globl _sputLua_CleanBuffer\n_sputLua_CleanBuffer:\n\tjmp _Render_CleanBuffer\n");
/* sputLua_Display @ 0x004a1ad0 */
__asm__(".text\n.globl _sputLua_Display\n_sputLua_Display:\n\tjmp _Render_Present\n");
/* sputLua_ResetTexturesL @ 0x004a3ad0 */
__asm__(".text\n.globl _sputLua_ResetTexturesL\n_sputLua_ResetTexturesL:\n\tjmp _D3D_ResetTextures\n");
/* sputLua_SaveIMuse @ 0x004a3bc0 */
__asm__(".text\n.globl _sputLua_SaveIMuse\n_sputLua_SaveIMuse:\n\tjmp _IMuse_SaveToTemp\n");
/* sputLua_RestoreIMuse @ 0x004a3bd0 */
__asm__(".text\n.globl _sputLua_RestoreIMuse\n_sputLua_RestoreIMuse:\n\tjmp _IMuse_RestoreFromTemp\n");
