# Native Linux build

`make -C build linux` builds `build/obj-linux/grimfandango`: a 32-bit Linux executable (i386 ELF, SDL2) of the same
tree the Windows build compiles. It needs no Wine. The game's code stays 32-bit, because the decompiled code
assumes 4-byte pointers everywhere.

## Prerequisites (Debian / Ubuntu)

```bash
sudo dpkg --add-architecture i386 && sudo apt-get update
sudo apt-get install gcc-multilib libsdl2-dev:i386 zlib1g-dev:i386 pkg-config python3
```

## Build and run

```bash
make -C build linux -j8                     # compile (obj-linux/<prog>/*.o) and link
python3 -I build/linux/smoke_test.py        # headless check without the game data
cd "/path/to/Grim Fandango/GRIMDATA" && /path/to/build/obj-linux/grimfandango
```

Run the game from the directory that holds the game data: the `*.LAB` files, `GRIM.TAB` and `IMUSE.PSL`. That's the
GOG install's `GRIMDATA` folder. File names are matched case-insensitively. You can also start it from a separate
mod directory and point `GRIM_DATA` at the data. That mod directory is the highest-priority resource directory
(docs/MODDING.md, section 6), and it needs `IMUSE.PSL`.

| Variable | Effect |
|---|---|
| `GRIM_DATA=<dir>` | the game data directory (registry value `GrimDataDir`); default: the working directory |
| `GRIM_REGISTRY=<file>` | the registry file; default `~/.config/grimfandango/registry.txt` |
| `GRIM_SCALE=<n>` | initial window size, n × 640×480 (default: the largest that fits the desktop) |
| `GRIM_SHARP=1` | nearest-neighbour scaling instead of linear |
| `GRIM_NOSOUND=1` | no audio device (DirectSoundCreate fails, as on a machine without sound) |
| `GRIM_NODIALOGS=1` | message boxes are only printed, the first button is taken |
| `GRIM_PLATLOG=1` | verbose platform log on stderr: files opened, registry, sound buffers, key events |
| `GRIM_SHOT=<f.bmp>` | touching `<f.bmp>.req` writes the next frame to `<f.bmp>`; `GRIM_SHOT_FRAMES=n` also writes the first n frames to `<f.bmp>.<i>.bmp` |

The Windows build's test knobs work too (`GRIM_LUA_FILE`, `GRIM_LUA_LOG`, `GRIM_DEBUGLOG`, `GRIM_NOMOVIE`, `GRIM_INI`
...). Their paths can be Unix paths. Alt+Enter toggles full screen. Text scripts (`TextAllowed`) are switched on in
the registry file: `smoke_test.py` shows the line.

## How it works

The decompiled programs are linked as they are for Windows. They call the Win32, DirectX and MSVC-runtime functions
they imported, and `platform/` implements those on SDL2 and libc:

| File | What |
|---|---|
| `platform/kernel32.c` | files (`CreateFileA`...), directory search, threads, events, critical sections, clocks, heap |
| `platform/paths.c` | DOS paths: `C:\x` is `/x`; `D:` is a virtual CD whose `GrimData` is the data directory (the start-up check `Grim_FindDataOnDrives`); every path component is matched case-insensitively |
| `platform/registry.c` | the registry, kept in a text file; the game key gets `GrimDataDir` |
| `platform/user32.c` | the game window (SDL), the message queue, keyboard and mouse to window messages, message boxes; dialogs and hooks (developer tools) fail as on a system without them |
| `platform/gdi32.c` | DCs and DIB sections: the game's "Window Display Device" draws into a DIB section and BitBlts it to the window, which shows the frame |
| `platform/dinput.c` | DirectInput 5 keyboard and mouse (COM objects): buffered key events and device state from SDL |
| `platform/dsound.c` | DirectSound (COM objects): every secondary buffer is mixed in the SDL audio callback; the play cursor follows what SDL has consumed |
| `platform/winmm.c` | `timeGetTime`, multimedia timers (iMUSE's tick thread), no joysticks; DirectDraw reports no devices |
| `platform/msvcrt.c` | the MSVC runtime functions that glibc lacks or that behave differently: DOS paths in `fopen`, MSVC's `rand`, `_findfirst`, `_stricmp`, `strftime`'s `struct tm`, `setvbuf` modes, the x87 helpers `_CIacos` / `_CIfmod`, `_setjmp3`, `_chkstk` |

`link_linux.py` explains how the four programs become one executable. Each DLL keeps its own namespace, and the
game's names (all prefixed `G`) resolve to the platform layer or to glibc. `cc.sh` compiles a module and makes the
PE symbol decorations (`_CreateFileA@28`) ELF-safe. The link reports the same 89 stubbed `FUN_` symbols as the
Windows link. Those are runtime functions that `names/lib_replace.json` removes, referenced only from data tables.
Every thread starts with the x87 control word of a Windows process (53-bit precision), so float results match the
Windows build.

Not done yet: joysticks / game controllers, the developer dialogs (Lua console, light editor), the debug text
overlay (`TextOutA`), the DirectDraw / Direct3D display devices (the game uses the window device, as the Windows build
does by default).
