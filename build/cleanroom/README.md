# Clean-room test patches

What `grim_tools/cleanroom` needs from the rebuilt game, so that `run.py decomp` can run its tests on this build
directly. The original v1.01 exe is started through `grimlaunch.exe`, which patches its code in memory at fixed
addresses. Those patches cannot apply to this rebuilt exe, because its code is in other places.

Everything here is off unless its environment variable is set, so a normal run of the game does not change.

| grimlaunch patch | here | knob |
|---|---|---|
| `config`: grim.ini instead of the registry | `cleanroom.c` wraps `Reg_Open` ... `wuRegistry_SaveStr` | `GRIM_INI=<file>` |
| `debuglog`: PrintDebug to a log | `Lua_Print_NoOp` in `../overrides.c` | `GRIM_DEBUGLOG=<file>` |
| patch.dll's `CRSNAP:<file>` screenshots | `cleanroom.c` wraps `Lua_Print_NoOp` | `GRIM_DEBUGLOG` set |
| `simtime`: fixed frame time | `Main_Service` in `../overrides_exe.c` | `GRIM_SIMTIME=17` |
| `smushtime`: movies on game time | the GRIM_SIMTIME block of `../overrides_mixer_drv.c` | `GRIM_SIMTIME` (off: `GRIM_SMUSH_REALTIME=1`) |
| `imusetime`: music and sound on game time | the GRIM_SIMTIME block of `../overrides.c`; iMUSE's `timeGetTime` is wrapped in `cleanroom.c` | `GRIM_SIMTIME` (off: `GRIM_IMUSE_REALTIME=1`) |
| (an assert writes its text to the log and crashes, instead of a message box that waits) | `cleanroom.c` wraps `stdPlatform_Assert` | `GRIM_DEBUGLOG` set |
| (key presses without the focus: `PrintDebug("CRKEY:<DIK code> <1 down / 0 up>")`, applied by the next frame's keyboard poll; this build only) | `cleanroom.c` wraps `stdControl_ReadControls` | `GRIM_DEBUGLOG` set |
| `windowed` | the build is windowed by default (`Win_CreateMainWindow` in `../overrides.c`) | (none) |
| (drawing behind other windows) | `../overrides.c` | `GRIM_ACTIVE=1` |

Without `GRIM_INI` the game reads `GrimDataDir` from the registry and finds the real game's data, which a clean-room
run must never see.

## How it is linked

`../link.py` compiles every `.c` in this folder into each program (with `-DGRIM_EXE` and the like, as for the
`overrides_*.c` files). Its `/* WRAPS: a b c */` lines become `-Wl,--wrap=a` and so on for GRIMFANDANGO.EXE, and
`/* WRAPS(IMUSE.DLL): ... */` lines for that program. A wrapper `__wrap_a` gets every call of `a` from the other
objects, and `__real_a` is the decompiled `a`. The decompiled functions stay in `src/` as they are, and
`tools/build_src.py` does not need to know about this folder.

Differences from the original's patches:

- All three of PrintDebug, PrintWarning and PrintError log as `DEBUG`, because the game registers one function for
  all three.
- `GRIM_SIMTIME` alone also runs the movies and iMUSE on game time, as grimlaunch's `simtime`, `smushtime` and
  `imusetime` together do: both step once per frame in `Main_Service`, before the frame runs, as the launcher's frame
  stub does (the movies first). `run.py decomp` runs them so, as the reference was recorded.
- There is no `grimcrash.dmp`. A crash writes `grim_crash.txt` in the working directory (`../startup.c`).
