/* Program entry for the rebuilt GRIMFANDANGO.EXE.
 *
 * The original start-up (`entry` at 0x4aca30, MSVC 6 WinMainCRTStartup) and
 * the whole static C runtime are left out of the runnable link; the host
 * mingw/msvcrt runtime does that work and calls this WinMain, which hands over
 * to the game's own WinMain (Win_WinMain at 0x401010 -> Win_Main). */
int __attribute__((stdcall)) Win_WinMain(void *hInstance, void *hPrevInstance, char *cmdLine, int nCmdShow);

int __attribute__((stdcall)) WinMain(void *hInstance, void *hPrevInstance, char *cmdLine, int nCmdShow)
{
    return Win_WinMain(hInstance, hPrevInstance, cmdLine, nCmdShow);
}
