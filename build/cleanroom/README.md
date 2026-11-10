# Clean-room test patches

What `grim_tools/cleanroom` needs from the rebuilt game, so that `run.py decomp` can run its tests on this build
directly. The original v1.01 exe is started through `grimlaunch.exe`, which patches its code in memory at fixed
addresses. Those patches cannot apply to this rebuilt exe, because its code is in other places.

Everything here is off unless its environment variable is set, so a normal run of the game does not change.

| grimlaunch patch | here | knob |
|---|---|---|
| `config`: grim.ini instead of the registry | `cleanroom.c` wraps `Reg_Open` ... `Reg_SetString` | `GRIM_INI=<file>` |
| `debuglog`: PrintDebug to a log | `Lua_Print_NoOp` in `../overrides.c` | `GRIM_DEBUGLOG=<file>` |
| patch.dll's `CRSNAP:<file>` screenshots | `cleanroom.c` wraps `Lua_Print_NoOp` | `GRIM_DEBUGLOG` set |
| `simtime`: fixed frame time | `Main_Service` in `../overrides_exe.c` | `GRIM_SIMTIME=17` |
| (sound on real time, as the original's simtime patch leaves it) | `GRIM_ImSimOn` in `../overrides.c` | `GRIM_IMUSE_REALTIME=1` |
| `windowed` | the build is windowed by default (`Win_CreateMainWindow` in `../overrides.c`) | (none) |
| (drawing behind other windows) | `../overrides.c` | `GRIM_ACTIVE=1` |

Without `GRIM_INI` the game reads `GrimDataDir` from the registry and finds the real game's data, which a clean-room
run must never see.

## How it is linked

`../link.py` compiles every `.c` in this folder into each program (with `-DGRIM_EXE` and the like, as for the
`overrides_*.c` files). Its `/* WRAPS: a b c */` lines become `-Wl,--wrap=a` and so on for GRIMFANDANGO.EXE. A wrapper
`__wrap_a` gets every call of `a` from the other objects, and `__real_a` is the decompiled `a`. The decompiled functions
stay in `src/` as they are, and `tools/build_src.py` does not need to know about this folder.

Differences from the original's patches:

- All three of PrintDebug, PrintWarning and PrintError log as `DEBUG`, because the game registers one function for
  all three.
- `GRIM_SIMTIME` alone also runs iMUSE on game time (see `../overrides.c`); `run.py decomp` adds
  `GRIM_IMUSE_REALTIME=1`, because the reference was recorded with sound on real time.
- There is no `grimcrash.dmp`. A crash writes `grim_crash.txt` in the working directory (`../startup.c`).
