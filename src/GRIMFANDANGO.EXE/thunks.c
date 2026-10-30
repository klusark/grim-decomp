/* GRIMFANDANGO.EXE: jump thunks. Each is a single `JMP target` instruction in the
   original; Ghidra marks them as thunks and decompiles no body. */

/* Svc_Fn2c @ 0x00403700 */
__asm__(".text\n.globl _Svc_Fn2c\n_Svc_Fn2c:\n\tjmp _Clock_ElapsedMs\n");
/* Lua_BuildCache @ 0x00498e30 */
__asm__(".text\n.globl _Lua_BuildCache\n_Lua_BuildCache:\n\tjmp _SectorList_SaveForShrink\n");
/* Lua_RestoreCache @ 0x00498e40 */
__asm__(".text\n.globl _Lua_RestoreCache\n_Lua_RestoreCache:\n\tjmp _SectorList_RestoreAfterShrink\n");
/* Lua_DumpMemoryLog @ 0x00498ff0 */
__asm__(".text\n.globl _Lua_DumpMemoryLog\n_Lua_DumpMemoryLog:\n\tjmp _Mem_DumpLog\n");
/* Lua_StopMovie @ 0x0049e850 */
__asm__(".text\n.globl _Lua_StopMovie\n_Lua_StopMovie:\n\tjmp _Movie_Stop\n");
/* Lua_SpewStartup @ 0x0049efa0 */
__asm__(".text\n.globl _Lua_SpewStartup\n_Lua_SpewStartup:\n\tjmp _Spew_Startup\n");
/* Lua_SpewShutdown @ 0x0049efb0 */
__asm__(".text\n.globl _Lua_SpewShutdown\n_Lua_SpewShutdown:\n\tjmp _Spew_Shutdown\n");
/* Lua_ImStopRecording @ 0x004a0f70 */
__asm__(".text\n.globl _Lua_ImStopRecording\n_Lua_ImStopRecording:\n\tjmp _ImStopRecording\n");
/* Lua_ImStopAllSounds @ 0x004a1080 */
__asm__(".text\n.globl _Lua_ImStopAllSounds\n_Lua_ImStopAllSounds:\n\tjmp _ImStopAllSounds\n");
/* Lua_ImStopVoice @ 0x004a1630 */
__asm__(".text\n.globl _Lua_ImStopVoice\n_Lua_ImStopVoice:\n\tjmp _SoundStopVoiceStream\n");
/* Lua_ImPause @ 0x004a1790 */
__asm__(".text\n.globl _Lua_ImPause\n_Lua_ImPause:\n\tjmp _ImPause\n");
/* Lua_ImResume @ 0x004a17a0 */
__asm__(".text\n.globl _Lua_ImResume\n_Lua_ImResume:\n\tjmp _ImResume\n");
/* Lua_CleanBuffer @ 0x004a1ac0 */
__asm__(".text\n.globl _Lua_CleanBuffer\n_Lua_CleanBuffer:\n\tjmp _Render_CleanBuffer\n");
/* Lua_Display @ 0x004a1ad0 */
__asm__(".text\n.globl _Lua_Display\n_Lua_Display:\n\tjmp _Render_Present\n");
/* Lua_ResetTextures @ 0x004a3ad0 */
__asm__(".text\n.globl _Lua_ResetTextures\n_Lua_ResetTextures:\n\tjmp _D3D_ResetTextures\n");
/* Lua_SaveIMuse @ 0x004a3bc0 */
__asm__(".text\n.globl _Lua_SaveIMuse\n_Lua_SaveIMuse:\n\tjmp _IMuse_SaveToTemp\n");
/* Lua_RestoreIMuse @ 0x004a3bd0 */
__asm__(".text\n.globl _Lua_RestoreIMuse\n_Lua_RestoreIMuse:\n\tjmp _IMuse_RestoreFromTemp\n");
