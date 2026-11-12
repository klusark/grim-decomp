# Types, round 9 (2026-11-12): Grim's Lua state, LState

Round 8 (types_8.md) typed Lua's objects; the state they live in was `int *g_pLuaState`, read by number in 117
functions. This round types it. Batch: `names/types_lua_state.json`.

## LState (0xd4)

One per Lua task (lstate.c, the remaster's `LState::LState`); `g_pLuaState` is the running task, `g_dwL_Main` the
first. Lua 3.1's lua_State (stack, C stack, error jump, parser states, C blocks) with the fields Grim adds for tasks.

| off | field | from |
|---|---|---|
| 0x00 | `void *pExecutionState` | the task's chain of execution states (call frames, linked through their +0x0c): `luaD_call`, `lua_updatetasks`; lapi.cpp's assert names it `L->pExecutionState` |
| 0x04 | `void *pResumeState` | the execution state the task goes on in after `luaI_breakhere` (`luaD_call` saves and takes it) |
| 0x08 | `int nPreventBreak` | `luaI_breakhere` yields only while 0; `luaD_protectedrun`, C calls and lbuiltin's calls raise it |
| 0x0c | `int nUnread` | `LState_Construct` sets it to 1, nothing reads it |
| 0x10 | `int nUpdated` | `lua_updatetasks`: cleared for every task when a round starts, set when the task yields, so it runs once a round |
| 0x14 | `int nPaused` | `lua_pausetasks` sets it on every task but the running one, `lua_unpausetasks` clears it; the updater skips the task |
| 0x18 | `int nNestingLevel` | nested `luaV_execute` calls ("WARNING: Lua nesting level now ...") |
| 0x1c / 0x20 / 0x24 | `TObject *pTop, *pStack, *pLast` | the stack (`LState_Construct`: 0x400 bytes, last = stack + 0x7f) |
| 0x28 | `CLuaStack Cstack` | the running C function's frame: `nBase`, `nLua2C`, `nNum` (`lua_lua2C`, `checkCparams`) |
| 0x34 | `void *pErrorJmp` | `lua_error` longjmps through it; `luaD_protectedrun` and the updater set it |
| 0x38 / 0x3c / 0x40 | `void *pMainState, *pCurrState, *pLexState` | the parser (lparser.c: the main and current FuncState, 0x168 bytes each, and the lexer's state) |
| 0x44 | `CLuaStack aCblocks[10]` | `lua_beginblock` saves `Cstack` here, `lua_endblock` takes it back |
| 0xbc | `int nNumCblocks` | at most 10 |
| 0xc0 | `int nTaskId` | serial number from `g_dwLState_numThreads`, passed to the task hook |
| 0xc4 | `TObject taskFunc` | the function the task runs (`lua_updatetasks` pushes it) |
| 0xcc / 0xd0 | `LState *pNext, *pPrev` | the task list (`LState_attach` / `detach` / `next`) |

`CLuaStack` (12) is Lua 3.1's `C_Lua_Stack`. Typed with them: `g_pLuaState`, `g_dwL_Main` (`LState *`),
`LState_Construct`, `LState_detach`, `LState_next`, `LState_Destruct`. `LState_attach` (`__thiscall`) and
`lua_newstate` are hand-written and keep their signatures for now.

The generated code reads the state by field now (376 uses): `g_pLuaState->pStack + param_1 + -1`,
`luaV_pack((g_pLuaState->Cstack).nLua2C, (g_pLuaState->Cstack).nNum, g_pLuaState->pTop)`,
`if (g_pLuaState->pLast <= g_pLuaState->pTop)`.

A first version left +0x0c as padding; `LState_Construct` writes it, and Ghidra then printed `L->field_0xc`, which
does not compile (the function became a stub). It is a field now. The journal's whole-program entry for that
change was cut to `LState_Construct`, the only function that touches it.

## A regression: Lua numbers read as integers

The first build of this round did not start: an assert with a garbled file and line, then nothing (the clean-room
killed it after 30 s, 0 tests). Linking LUA.DLL with round 8's objects module by module found `lapi.c`. With the stack
typed, `lua_getnumber` read the number as `(float)g_pLuaState->pStack[param_1 + -1].dwValue`: in Ghidra's notation a
reinterpretation of the bits, in C a conversion of the integer's value. Round 8 read `*(float *)(g_pLuaState[8] - 4 +
param_1 * 8)`. The same happened to the VM's number comparison (`comparison`: `(float)pTVar2[-1].dwValue <=
(float)pTVar2[-2].dwValue`), which the start-up did not reach.

`TObject.dwValue` is the union of the original, kept as its bits (round 8). `tools/build_src.py` now knows that:
`FLOAT_BITS_MEMBERS` (`dwValue`) are members that hold a float's bits, so every float cast on one is a `PUN`, read
(`fix_casts`: `PUN(float, x.dwValue)`) or write (`fix_float_bits_members`: `x.dwValue = PUN(uint,(float)(f))`), whatever
conversions the function has (`fix_casts` otherwise reads `(float)int` as a conversion when the function has a FILD).
In the generated code only LUA.DLL changed: `lua_getnumber`, `comparison`, and the writes that were `PUN`s already.

(A first try taught `type_of` the members of every structure; that also changed 61 EXE files, mainly the service
calls through GrimServices, which `fix_fnptr_calls` then cast to `code *`. Not for this round: it is out again.)

## Overrides

`build/overrides.c` and `overrides_lua_core.c` read the state as words, as written from the original
(`g_pLuaState[7]`, `*g_pLuaState`). overrides.c gets a word view, `#define LSW ((int *)g_pLuaState)` (17 index and
22 dereference uses), overrides_lua_core.c had one already (`GL`); the places that store a task into
`g_pLuaState` cast to `LState *`. The bodies are unchanged.

overrides_lua_core.c's notes called +0x10 / +0x14 "paused" / "running elsewhere" and the start of an update round
"clear its paused flag"; `lua_pausetasks` / `lua_unpausetasks` show +0x14 is the paused flag and +0x10 the updated
one. The comments say so now.

## Checks

* All four programs compile and link; no new stub.
* `datacmp.py` against round 8's build: 0 differences, 0 moved, 0 missing in all four, every unused span zero.
* Sections: the EXE (but its build-time string), CHORE.DLL and IMUSE.DLL identical; LUA.DLL's code changes.
* Clean-room against grim_tools' knowngood (5167 tests, no install file in the run folder): all 5167 the same as the
  reference; against round 8's log only the three lab tests differ, which this run passed (not deterministic,
  data_unused.md). Every other test the same.
