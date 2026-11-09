# LUA.DLL VM core to C (2026-11-09, lead)

The last three LUA.DLL functions that were assembled for a reason other than "not a function":
`lua_updatetasks` (0x10001e10), `luaD_protectedrun` (0x100046e0), `luaD_protectedparser` (0x10004a50). They had been
left as machine code because they are the core of the Lua VM (the task scheduler and the two protected calls), not
because of a technical blocker. They are now C in `build/overrides_lua_core.c`, written from the original machine code.

## How the setjmp works in C

All three bracket a call with MSVC's `_setjmp3(buf, 0)`; Lua errors leave through `longjmp(*L->errorJmp, 1)`. In the
rebuilt DLL both come from the host `msvcrt.dll` (names/lib_replace.json), so the C makes exactly the same two calls:
`_setjmp3` is declared `returns_twice`, the jmp_buf is a 16-dword local like the original's, and every local read after
a longjmp is `volatile`. None of the three functions installs an SEH frame, so the registration chain `_setjmp3` records
is the same as with the original code.

## Converted

| address | name | what it does |
|---|---|---|
| 10001e10 | `lua_updatetasks` | the task scheduler: marks every task's call chain (lvm__de20) and clears its paused flag, then runs each task that is neither paused (+0x10) nor stopped (+0x14) under a setjmp; new tasks call their function (+0xc4), resumed ones continue their root call; a yield (non-zero result) sets the paused flag, an end or an error frees the task (lstate__8c00, luaM_free); the task hook gets 0/2/1/4/3 (start, resume, yield, end, error); with param_1 != 0 it repeats until no task is left |
| 100046e0 | `luaD_protectedrun` | luaD_callinc under a setjmp; after an error restores the C stack frame (+0x28..+0x30), resets top and unwinds the call chain back to the entry root (lvm__dd90); restores errorJmp, decrements the call depth |
| 10004a50 | `luaD_protectedparser` | luaY_parser or luaU_undump1 under a setjmp; returns 1 (error), 2 (nothing to read) or 0 with a closure pushed |

Kept from the machine code: `lstate__8bf0` / `lstate__8c00` / `lvm__de20` are `__fastcall`; luaD_openstack gets the
arithmetic shift `((top - base) >> 3) - cbase`; luaD_call of a new task gets the C base read *before* luaD_openstack,
plus 1; the assert (services+0x18, `L->pExecutionState`, lapi.cpp line 0x2fe) only fires for a yield without a root;
the call chain is unlinked before each entry is freed; the global L is re-read after every call.

Not reproduced (no effect): `lua_updatetasks` leaves `L->errorJmp` pointing at its own jmp_buf after it returns (in both
versions a dangling pointer to a dead stack frame; only the frame offset differs).

## Verification

* Differential test `build/difftest/lua_core/` (`build.sh [cases]`, `core_test.c`, `mutate.py`): the original machine
  code (sliced from the assembly of ea3c1a6) and the C, on random task lists and states in a fixed pool, with stand-in
  callees that log every call and take their decisions from a per-case stream: they push and pop call entries, change
  the C stack frame, nest protected calls and parses (up to 3 deep), yield, finish, and raise errors through msvcrt
  `longjmp(*L->errorJmp, 1)` like lua_error. Compared: return value, the call log, the global L, the whole pool.
  **1,000,000 cases (a third per function, 294,518 of them with an error raised), 0 differences.**
* Mutation check: 12 of 12 caught (one, the restart scan without the stopped-flag test, by a hang where the original
  returns: mutate.py gives each run 120 s).
* Clean-room tests (`run.py decomp`): 5107 of 5107 the same. One of the runs hit the known intermittent save_load crash
  (ResRef_Remove <- ModelComponent_Destroy, EAX = "MMDL"; build/BUILD_NOTES.md, round q), which also happens without this
  change; the rerun of the same binaries passed.

Left assembled in LUA.DLL: the seven C++ exception unwind funclets (0x10021fb0 ... 0x10022050), which run on the frame of
the function that owns them and are reached only through the SEH tables.
