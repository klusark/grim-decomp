# Building the reconstruction

`src/` is generated. Everything that makes it compile lives in
`tools/build_src.py` (text fix-ups, header generation) and in this directory
(`Makefile`, `compat.h`, `stubify.py`, `summary.py`, `link.py`). Nothing under
`src/` is edited by hand, so this always works:

```bash
rm -f src/*/*.[ch] src/*/*.md && python -I tools/build_src.py && make -C build -j8
make -C build link        # stretch goal: link all four PE files
```

`src/<prog>/asm_funcs.s` is the exception: `tools/gen_asm.py` writes it from `names/asm_funcs.json` and needs the
Ghidra bridge, `build_src.py` does not touch it, so do not delete it (`rm -rf src` builds without the assembled
functions: they are silently stubbed and the game does not run). Without Ghidra, a function converted to C can be
taken out of the committed file with `build/difftest/asm_p2/strip_asm.py`.

Other targets: `make -C build syntax` (`-fsyntax-only`, no fallback),
`summary`, `errors` (histogram of the diagnostics behind stubbed modules),
`clean`. Variables: `OPT=-O2`, `EXTRA_CFLAGS=...`, `STUBS=0` (no stub
fallback), `SRC=`/`OBJ=` (build another tree, e.g. one written with
`GRIM_SRC_DIR=build/tsrc python -I tools/build_src.py`).
`python -I tools/build_src.py --raw` writes Ghidra's text without fix-ups.

## Toolchain

* Compile: MSYS2 UCRT64 `gcc` 16.2 with **`-m32 -march=i686`**. The x86_64
  compiler emits i386 COFF objects fine; it only lacks 32-bit libraries.
  `ghidra_types.h` has `_Static_assert(sizeof(void *) == 4)` because Ghidra's
  `(int)ptr + 0x10` arithmetic is everywhere (define `GHIDRA_ALLOW_64BIT` to
  get past it on a 64-bit target; the code would not be correct).
* Link: the i686 toolchain in `/mingw32/bin` (`mingw-w64-i686-gcc`), used only
  by `make link`.
* Flags: `-std=gnu11 -fpermissive -w -fno-builtin -fno-strict-aliasing -fwrapv
  -fno-common -ffreestanding -include compat.h`. `-fpermissive` makes GCC >= 14
  accept int/pointer conversions and implicit declarations again; gnu11 keeps
  `int f();` unprototyped (C23 would not).

## Result (raw export of 2026-10-28 11:3x)

| program | modules | clean | objects | functions | compile as decompiled | stubbed |
|---|---|---|---|---|---|---|
| GRIMFANDANGO.EXE | 130 | 128 | 130 | 1991 | 1988 | 3 |
| LUA.DLL | 29 | 29 | 29 | 435 | 435 | 0 |
| IMUSE.DLL | 8 | 8 | 8 | 218 | 218 | 0 |
| CHORE.DLL | 2 | 2 | 2 | 5 | 5 | 0 |
| **total** | **169** | **167** | **169** | **2649** | **2646** | **3** |

Full build: ~17 s with `-j8`, also clean at `-O2`. Starting point (same
headers, no fix-ups): 7 of 153 modules and about 1260 of 2612 functions
without an error.

"Stubbed": `stubify.py` replaces the body of a function with a compiler error
by `__builtin_trap()` (the original stays under `#if 0` in
`obj/<prog>/<mod>.stub.c`) so the module still yields an object. The three:

| function | why | fix (in Ghidra) |
|---|---|---|
| `_onexit` (crt.c) | `DAT_00906c10`/`DAT_00906c14` are dereferenced as pointers and used as `int` in `(int)a + (4 - b)` | type both as `PVFV *` (onexit table begin/end) |
| `rdRaster_Grad_Flat_2` (rdraster.c) | `DAT_007f42fc` (vertex count) is copied into a `float` local in one function, so it is inferred as `float` | type it `int` (and `DAT_007f4308` as a vertex pointer) |
| `_pow` (crt.c) | `auStack_e = (undefined1 [10])in_ST7;` (x87 spill as array assignment) | none needed; CRT internals |

`make link` links all four (`obj/<prog>/<prog>.dll/.exe`, PE32 i386, `-nostdlib`,
the DLLs with `--export-all-symbols`, the EXE against the rebuilt DLLs' import
libraries). It is a completeness check, not a runnable build:

| program | data symbols defined (`data.c`) | stubbed symbols (`stubs.txt`) |
|---|---|---|
| LUA.DLL | 241 | 53: 39 Win32 imports, 14 `LAB_` |
| IMUSE.DLL | 228 | 35: 32 imports, 1 `LAB_`, `ImProcessStreams`, `ImTerminate` |
| CHORE.DLL | 7 | 0 |
| GRIMFANDANGO.EXE | 1988 | 293: 169 imports (Win32/DirectX, plus DLL exports that have no Ghidra function, see below), 123 `LAB_`, `sqrtl` |

`data.c` zero-fills every global (Ghidra exports names, not contents); `s_`
strings are initialised from `raw/<prog>/strings.txt`. Imports are declared
`int f();` (cdecl, undecorated), so even a real import library would not
match their `__stdcall` decorations; they are trap stubs.

## What tools/build_src.py does to the decompiled text

All rewrites are local and use macros from the generated `ghidra_types.h`, so
the code stays readable. Counts are for the current tree.

| Ghidra idiom | rewrite | count |
|---|---|---|
| call whose argument count disagrees with the prototype, or result of a `void` function used | `((code *)F)(args)`; if the callee is `__thiscall`/`__fastcall` or a float is passed, an explicit cast such as `((void (__thiscall *)(float))F)(x)` so no float is promoted to double | 529 |
| one register used as pointer and float: `(float)ptr_var`, `(float *)(float_expr)`, float parameter given a pointer | `PUN(float, ptr_var)`, `PUN(float *, (float)expr)` (bit reinterpretation through a union) | 590 |
| `x._1_2_` sub-piece | `PIECE(x,1,2)` (packed bit-field lvalue, also 3/5/6/7 bytes) | 173 |
| `stack0x00000008` | `STACK0X(0x00000008)` = entry ESP + offset via `__builtin_frame_address` | 84 |
| `register0x00000010` (ESP) | `REGISTER0X(0x10)` | 6 |
| `_local_4` (other-width view of a local) | `PIECE(local_4,0,4)` | |
| `goto LAB_x` to a label outside the function | `JUMPOUT(LAB_x)` (trap) | 0 now |
| `switch (ptr)`, `case (byte *)0x1:` | `switch ((int)(ptr))`, `case 0x1:` | |
| `(*fn)(x)` with `void *fn` | `(*(code *)fn)(x)` | |
| `NAN(x)` (unordered test) vs `NAN` constant | `ISNAN(x)` / `NAN` | |
| string labels with punctuation `s_Resource_<__12s>_004e79f4`, `s_(i_004dd7a4` | non-word characters -> `_` | |
| `iRam00000002` | `(*(int *)0x00000002)` | |
| two functions with one name (`rdThing_Draw` @0x00471d80, `stdBitmap_Load` @0x0047aab0) | second definition renamed `<name>_<addr>`; calls bind to the first | 2 |

Headers:

* `ghidra_types.h`: all Ghidra primitives (`undefinedN`, `uint3`, `float10`,
  `unkbyte10`, `code` as the unprototyped `int code()`), every
  `SUBnm`/`CONCATnm`/`ZEXTnm`/`SEXTnm`/`CARRYn`/`SCARRYn`/`SBORROWn`,
  `ROUND`/`SQRT`/`f2xm1`/`fscale`/`fsin` as x87 builtins, the macros above,
  and `typedef struct X X;` for every non-primitive type named in prototypes
  or globals.
* `globals.h`: named globals with their Ghidra type (from `globals.json`);
  `undefinedN`-typed ones and all `DAT_`/`PTR_`/`s_`/... symbols get a type
  inferred from use: called -> `code *`, dereferenced -> pointer, copied
  to/from a typed local -> that type, only address-taken -> `undefined` (byte, so
  `&DAT_x + n` keeps Ghidra's byte stride). `_DAT_x`, `_g_name` and `DAT_x_2`
  become macros viewing the base symbol at another width/offset.
* `functions.h`: as before, plus `int F();` for referenced thunks, imports
  and `FUN_` addresses with no function, and `extern code *X_exref;` for IAT
  slots.

`build/compat.h` (force-included) holds what raw/ cannot provide: calling
convention fallbacks for non-MinGW i386 compilers and the `GrimServices`
layout (0x70, copied from the Ghidra project; slots declared `code *` because
the code calls them directly).

Also fixed in `tools/build_src.py` (affects the layout of `src/`):

* `IMPORT_NAMES` was shared between programs, so when LUA.DLL was processed
  after the EXE its own `lua_*` functions (EXE imports) were filed under
  `_thunks` and silently dropped: LUA.DLL now has 435 functions in src/ instead
  of 408.
* CRT names starting with `_` (`_stricmp`, `_ftol`, ...) produced a module
  called `.c`; they now go to `crt.c`.
* functions listed in `functions.json` without a `raw/<prog>/functions/*.c`
  (export in progress) are skipped with a warning instead of crashing.

## Remaining blockers / caveats

1. **Semantics are best-effort.** The objects are not a faithful program:
   inferred global types can be wrong (see the three stubs), `unaff_*`,
   `in_*`, `extraout_*` are uninitialised locals, the SEH prologues read an
   uninitialised `unaff_FS_OFFSET`, `STACK0X` assumes a frame pointer, and
   `PUN`/`((code *)F)` reproduce what Ghidra printed, which is wrong wherever
   Ghidra's prototype is wrong.
2. *(Fixed by types round 1, docs/notes/types_1.md: `raw/<prog>/structs.json`, emitted into ghidra_types.h.)*
   **Struct layouts are not exported.** Only `GrimServices` exists in Ghidra
   today and is copied by hand into `compat.h`. When more structs are applied,
   either extend `tools/export_raw.py` to dump layouts (e.g. `get_struct_layout`)
   and emit them from `build_src.py`, or add them to `compat.h`; otherwise
   `p->field` accesses will fail to compile.
3. **DLL exports with no Ghidra function** (export address is not a function
   start): LUA.DLL 35 (`lua_Initialize`, `lua_gettable`, `lua_settable`,
   `lua_beginblock`, `lua_ref`, `lua_getref`, ... and `entry`), IMUSE.DLL 50
   (`ImLoadSound`, `ImSetState`, `SoundsPeriodic`, ...), CHORE.DLL 64 (almost
   the whole `Cos_*`/`CosUtil_*` API: this is why CHORE.DLL looks like a
   five-function stub). These are decompilation gaps for the Ghidra side
   (create functions at the export addresses); the EXE's calls to them are
   stubbed at link time.
4. **Data is not initialised** (except strings) and imports are not real, so
   `make link` produces PE files that link but cannot run.
5. If a regenerated tree introduces a new error class, `make` still produces
   every object (stub fallback) and `make summary`/`make errors` show what to
   add to `tools/build_src.py`; `STUBS=0` makes the build fail instead.

## Real data and real imports (added 2026-10-28, evening)

`make link` no longer zero-fills the data or traps the imports:

* **Section contents.** `tools/export_data.py` dumps every non-code section
  (`.rdata`, `.data`) of each program from Ghidra into
  `raw/<prog>/sections/*.bin` (+ `sections.json`). `build/gendata.py` turns
  them into `obj/<prog>/data.s`: the original bytes (zero tails as `.zero`),
  a label for every global the decompiled code references at its original
  offset, and link-time relocations for every dword that points into the
  image: `.long _Function` for function starts, `.long _sect_data + off` for
  data pointers. Pointers into code that are not function starts (jump
  tables, thunks, code labels) keep their original value with a comment.
  `data.c` now only defines what lies outside the dumped sections (code
  labels, import address table slots, which point at the real imports).
* **Imports.** Win32/DirectX imports are declared
  `int STDCALL f() __asm__("_f@N");` in `functions.h`, with `N` taken from
  `build/stdcall_names.json` (generated by `build/gen_stdcall_names.py` from
  the mingw-w64-i686 import libraries with `nm`). The link adds
  `-lkernel32 -luser32 -lgdi32 -lwinmm -lddraw -ldinput -ldsound -ladvapi32
  -lcomdlg32 -lole32 -lshell32 -lcomctl32`; `build/win32_shims.c` provides
  `InterlockedIncrement/Decrement/Exchange` (intrinsics in today's headers,
  not in the import libraries) and two mingwex hooks. The game's own DLL
  imports (`lua_*`, `Im*`, `Sounds*`, `Cos*`) stay cdecl and bind to the
  rebuilt DLLs' import libraries.
* **Entry points.** The call targets the DLL code reached through
  `func_0x...` (addresses with no Ghidra function) were turned into functions
  in Ghidra (IMUSE.DLL +72, CHORE.DLL +110), so those DLLs now link without
  code stubs.

Result:

| program | symbols placed in dumped data | relocations (code / data) | still stubbed |
|---|---|---|---|
| GRIMFANDANGO.EXE | 1976 | 373 / 1613 | 123 `LAB_` code labels |
| LUA.DLL | 422 | 18 / 471 | 25 `LAB_`, `_pow` (undecompilable), `fpatan`, `builtin_strncpy` |
| IMUSE.DLL | 331 | 1 / 250 | 4 `hmiFX*` (HMI SOS library, not available), 2 `LAB_`, `ImProcessStreams`/`ImTerminate` (one-instruction thunks), `builtin_strncpy` |
| CHORE.DLL | 92 | 0 / 241 | none |

Caveats: the pointer scan is a heuristic (any aligned dword whose value falls
inside the image); an integer or float that happens to look like an address
becomes a relocation. `.rsrc` (dialog templates of the light editor, icons)
is not dumped. The EXE entry point is still a trap: running the result is the
next milestone (CRT start-up through the decompiled `_CRT_INIT`/`entry`, then
the 123 code labels and the `unaff_*`/`in_*` register semantics).

## Runnable link (2026-10-28, night)

`make link` now produces binaries that start:

* **Host C runtime.** The decompiled MSVC 6 runtime module (`crt.c`) is left
  out of every link; `-nostdlib` is gone, so the mingw-w64 start-up and
  msvcrt.dll provide `malloc`, `fopen`, `_stricmp`, `_ftol`, `_CIpow`,
  `_setjmp3`, `_except_handler3` and friends. Runtime internals the engine
  still names (`_getptd`, C++ EH helpers) stay as trap stubs.
* **Entry.** `build/startup.c` defines `WinMain`, which calls the game's
  `Win_WinMain` (0x401010, a wrapper around `Win_Main` at 0x4abf40, the real
  WinMain body). The EXE links with `-mwindows`; the DLLs get mingw's
  `DllMainCRTStartup`.
* **SEH frames.** Ghidra's uninitialised `unaff_FS_OFFSET` local is now
  initialised to the TEB base (`TEB_BASE()` in `ghidra_types.h`,
  `movl %fs:0x18`), so the `*unaff_FS_OFFSET = &frame` prologues register a
  real SEH frame instead of writing through garbage.
* **Code labels.** Every `LAB_` address the code uses as a function pointer
  (121 in the EXE, 23 in LUA.DLL, 2 in IMUSE.DLL) was turned into a function
  in Ghidra; the first run showed they are real entry points (e.g. the
  `stdFile_Read` slot of the service table at 0x473460).
* **HMI audio.** IMUSE.DLL used to bind to the game's real `HMIFXLIB.DLL` /
  `HMIFXFP.DLL` through import libraries generated in `build/hmi/`; since
  2026-11-12 `overrides_hmifx.c` is that library in C (section at the end).

Running: copy `obj/GRIMFANDANGO.EXE/grimfandango.exe` and the three rebuilt
DLLs into one folder (`build/run/`) and start the EXE with the game's data
folder (`DATA*.LAB`, `GRIM.TAB`) as the working directory, e.g.
under gdb: `cd "C:/GOG Games/GRIMDATA" && gdb -batch -ex run -ex bt --args
.../build/run/grimfandango.exe`. A `__builtin_trap()` (SIGILL) in a `LAB_`,
`FUN_` or `stub_` symbol means a stub was reached; `bt` names the caller.

### Two things the first runs taught (2026-10-28, late)

* **Imports need prototypes in Ghidra.** The Win32 imports had none, so the
  decompiler guessed each call's argument count from the pushes it saw and
  got the stack purge wrong (`RegOpenKeyExA` with 4 of its 5 arguments);
  every later stack access in the caller was then off by one slot
  (`Reg_SetString` read its arguments as `unaff_EDI` / `local_4`). The
  decorated names in `stdcall_names.json` give the argument byte count, so
  every import now carries `int f(int a1, ..., int aN)` `__stdcall`
  (`wsprintfA` cdecl varargs). 294 import prototypes were set this way; the
  whole tree was re-exported afterwards. If an import ever decompiles with
  the wrong count again, fix its prototype at its `EXTERNAL:` address.
* **Strings are not pointers.** The relocation scan took the bytes `Dir\0`
  of `GrimDataDir` for an address inside `.data`. `gendata.py` now skips
  every dword inside a string Ghidra knows (`strings.txt`, extended to the
  NUL) and any dword that is 3+ printable characters.
* `build/run.gdb` runs the game under gdb and steps over the debugger-only
  `STATUS_INVALID_HANDLE` exceptions `RegCloseKey` raises when the LucasArts
  registry key is missing; the real game behaves the same outside a debugger.

## Playable (2026-10-29)

The rebuilt EXE runs the opening scene in the software renderer (windowed, `build/run/`, working
directory `C:\GOG Games\GRIMDATA`): Manny stands in his office (`docs/manny.png`), the arrow keys walk
him (Up = forward, Left/Right = turn, like the original), the rest chore plays. Movies play (see
"Movies, LecShare and the repne bug" below); sound has not been verified by ear.

What it took, in the order the bugs showed up (each is a class that will recur):

* **Float bits stored through int slots.** Ghidra types a dword as `undefined4`/`uint` that really
  holds a float (`puVar[1] = fVar6` in `luaU_LoadConstants`, `(float)ref[-0x21]` in
  `Set_LoadResources`): gcc converts the value (4.0 -> 4) where the original copied bits. Lua numbers
  became integers, actors had denormal positions, the camera FOV clamped to 179. Find them with
  `tools/find_float_stores.py`; the cure is assembly mode (`names/asm_extra.json`).
* **Parameter slots reused as locals** (`sscanf(buf, "...", &param_1)` then `param_1` read back
  under another name): `tools/find_param_addr.py`. CHORE.DLL is assembled completely for this reason.
* **Lost x87 results**: `lua_getnumber(x); _ftol(garbage)` (`Lua_PlayActorChore` played chore 0),
  `in_FPUControlWord` (`Services_SetCurrent` must save the control word that `Math_Round` etc. load).
* **`_input`** (the scanf engine) is split by Ghidra's jump table; EXE/LUA/CHORE forward it to the
  host `sscanf` (`overrides.c`). Do not test it with gdb's own `sscanf` symbol, that is the host's.
* **Section layout is part of the code.** `.rdata` is linked directly in front of `.data` at the
  original distance (tables run across the boundary); table bases like `[idx*4+0x4d3600]` point
  *outside* every section and are only valid with the original layout, so `gen_asm.py` rewrites a
  base inside `.text` relative to `_sect_data`; the code bytes themselves are linked as `_sect_text`
  so data islands in the code section (DirectInput's `c_dfDIKeyboard`, switch data) exist.
* **DirectInput** refuses `Acquire` without `SetCooperativeLevel` (the original never set one for the
  keyboard); `SetDataFormat` failed (E_INVALIDARG) until `c_dfDIKeyboard` was real data.
* Debugging tips: `set environment _NO_DEBUG_HEAP=1` in gdb (the debug heap's 0xBAADF00D fills change
  behaviour), `OutputDebugStringA` shows up as a gdb warning, `PrintWindow` captures the game window
  even when it is behind others, `rdModel_DrawMesh` arguments (mesh, matrix) show whether node
  matrices are sane, `Cos_InstChoreName/Status` show which chores run.
* Functions that break when assembled stay C via `names/asm_exclude.json`: `ThingRequester`
  (0x496e20), `luaS_newlstr`/`lstring__9180`, two EXE CRT functions. Whole-EXE assembly (`--all`)
  still hangs at start-up (black window); the working set is the rendering/math/actor/walker modules
  plus the artifact-driven picks.


## Movies, LecShare and the repne bug (2026-10-29, later)

The LucasArts logo and the intro movie (`.snm`, Smush) now play with the rebuilt EXE. Root causes, all
of them general classes:

* **`gen_asm.py` turned every `repne scasb` (inlined `strlen`) into `rep scasb`** (the prefix regex
  matched `REP` before `REPNE`). Every assembled `strcat`/`strlen` computed length 1; LecShare's
  `LecShare_Resolve` built `"iILIO"` instead of `"FILIO=insane_zfilio"`, so the StdFile/zfile modules
  never started (this was also the cause of the Save Game crash through `gz_open`).
* **Void-declared functions whose result is used** (`FUN_004c36b0` ...): found by scanning callers of
  `void` definitions; assemble them.
* **Register-convention helpers** (`in_EAX`): memcpy/memset-style helpers (`FUN_004c3e10`,
  `FUN_004d5fd0`, ...) and their wrappers (`FUN_004c3df0`, `FUN_004d5e50`/`70`) must all be assembled
  together, a C wrapper calling an assembled helper passes registers the helper does not expect.
* **Varargs readers** (`REGISTER0X(0x10)` in the C source: `FUN_004cc250`, `FUN_004cc7d0`) read their
  extra arguments through the stack pointer; assemble them.
* **Jump tables Ghidra could not recover** (`FUN_004ce3e0`: `jmp [ecx*4+table]`): in Ghidra add
  `COMPUTED_JUMP` references from the jump to each target (`add_memory_reference`), disassemble the
  blocks, delete and re-create the function, then `gen_asm.py GRIMFANDANGO.EXE --select`. Ghidra is the
  system of record, so the fix belongs there.
* Regenerating after any change to `names/asm_extra.json`: `python -I tools/gen_asm.py <PROG> --select
  && python -I tools/build_src.py && make -C build link`.
* `GRIM_MULTI=1` lets several instances run side by side (the original quits if a "Grim Fandango"
  window exists; with the variable the window is titled "Grim Fandango (test)").
* Test hook: `GRIM_LUA_FILE` (file whose appended lines run as Lua once per frame) and
  `GRIM_LUA_LOG` (target of `grimlog()`); pass Windows paths with backslashes, forward-slash msys
  paths made the hook silently skip the file.
* After the logo there is a long pause (about a minute) before the intro movie starts; the main thread
  is inside the Lua VM (`Lua_GetVisibleThings`, `Lua_TurnActor`, ...), cause not yet analysed.

## Save / Load (2026-10-29)

`Save("name.gsv")` / `Load("name.gsv")` (Lua, also what the menu calls) write and restore a complete game
(thumbnail, costumes, module hooks, Lua state) with the rebuilt EXE: verified by saving, changing a Lua
global and Manny's position, loading, and getting both back (`GetSaveGameData` returns the header table).
Three bugs were in the way:

* **Void function whose result is used.** `lstring__9410` (list of dead strings) returns the list head in
  EAX but is declared void, so the assembled `lua_close` walked garbage in `luaC_strcallIM` (Load calls
  `lua_close` on the running state). Fixed by assembling it; the whole of `lstate.c` (pointer-id tables,
  `lua_Restore`) is assembled as well.
* **Data pointers to internal thunks.** `gendata.py` refused to relocate pointers to `thunk_*` functions,
  so the LecShare file-ops table held the original address 0x004cc3b0 and the first gz call after Save
  jumped into the middle of an unrelated function. Thunks defined in `thunks.c` are valid targets now.
* The Lua test hook defines `grimlog` again before each command (Load replaces the whole Lua state).

Saves made by the original game (`saves_old_numbering/`) load too since 2026-10-30, see "Saves of the original
game" at the end of this file.
## Gameplay checks (2026-10-29, agent B)

Test knobs (environment, all optional): `GRIM_MULTI=<tag>` (window title "Grim Fandango (<tag>)", several instances),
`GRIM_NOMOVIE=1` (movies off, set every frame), `GRIM_ACTIVE=1` (draw and present although the window is not the foreground
window, ignore WM_ACTIVATEAPP; dropped on 2026-11-13: a window always draws), `GRIM_LUA_FILE`/`GRIM_LUA_LOG` (Lua lines per frame; polled from sputLua_Update and from
Game_FrameUpdate, so it also works while the engine is paused in a menu). An unhandled exception writes `grim_crash.txt`
(registers, three frame arguments, stack) in the working directory; resolve addresses with `nm`.

Verified by script (Lua hook + PrintWindow screenshots + audio meter): walking and camera cuts (`manny:walkto`), set changes
through the game's door scripts (office, hallway, elevator, garage), the Glottis dialogue (choice menu, spoken lines with text
and audio, responses), inventory open/close and holding an item (ShrinkBoxes), the F1 menu and its actions (options, help,
save, load, cutscenes, transcript), Save and Load of a game, and `format`/`strfind`/`gsub` in Lua.

Bug classes found on the way (each is a pattern to grep for when something else misbehaves):

* **Wrong CRT names** (Ghidra's structural match swapped `toupper`/`tolower` in LUA.DLL; the build links the host CRT, so the
  name decides the behaviour: `%d` in a pattern never matched): fixed in Ghidra itself now (toupper/tolower, LUA.DLL `strcmp` was `strpbrk`, EXE `memcmp` was `strncmp`; the namefix workaround is gone).
* **Phantom parameters** (`lua_setfallback` got a third parameter from a stack-offset slip, `str_push_captures` a second one: the
  C body read garbage): assemble the callee.
* **Sign extension of a byte result**: `Text_NextChar` returns the byte zero-extended in EAX, the C callers used `char`.
* **Void-declared functions whose result is used** (`lstring__9410`, `io_getfileparam`, ...): `scan_void.py`-style check of the asm
  callers; assembled now.
* **Code pointers pushed as immediates that are no function** (IMUSE callback 0x10007a90, two SEH handlers): gen_asm links them
  to the unrelocated `_sect_text` copy; create the function in Ghidra (names the symbol) instead.
* **`DAT_` arrays typed `undefined4` although Ghidra scaled pointer arithmetic by their element** (`DAT_1002bf68 + 1`): every proto id
  of a savegame was read at a byte offset; `infer_global_types` now types such globals from the frame-local they are added to.
* **Address literals in integer arithmetic** (`iVar + -0x8cb0b0 >> 4`, an index into a static pool): relocated with `IMG_ADDR`.
* **printf engine of IMUSE's own CRT** (`FUN_1000c670`) jumps into data: replaced by the host formatter.

* **Prototype vs code audit** (`tools/find_arity_asm.py`, `tools/find_lost_args.py`, need `raw/<prog>/disasm.json` from `find_arity_asm.py --fetch`): compares each C
  prototype / C call site with the original code. Real finding: `luaY_error`/`lparser__a730` took no parameters in Ghidra, so the compiled C passed only the
  format string to `luaL_verror` (garbage error messages); the remaining reports are assembled callees (harmless), CRT code that is not linked, or split
  functions/jump tables where the stack-slot scan is blind.

## Eyes / 128-texel textures (2026-10-29, agent E)

Symptom: Manny's face was a white box with only a nose and teeth (no eye sockets, brows, side outlines) and his suit a flat
tile texture. Cause: `gen_asm.py` turned the immediate `and ecx,0x7f0000` (the u mask of every 128-texel-wide texture, 24 sites
in the `rdRaster_Span*` / `Span16_*` family) into `and ecx,offset _sect_data+0x313000`, because 0x7f0000 lies inside the original
image (bss). The texel column was masked with an address, so 128-wide textures (m_eye.mat face, m_s_chest suit, ...) were sampled
at the wrong columns. Rule now: AND/OR/XOR/TEST immediates whose low 16 bits are zero are masks, never relocated.
How it was found: gdb watchpoint on one framebuffer pixel (`*(short*)addr`, write) showed the span routine writing texel index 23
(white) where the .mat has index 8 (black) -> the texel address computation was wrong. General lesson: an asm-mode immediate that
is a plain number in the original but happens to fall into 0x401000..0x940000 is silently relocated; grep the generated
`asm_funcs.s` for `offset _sect_` in non-address positions (`and/or/xor/test/cmp/imul/shl` immediates).

Known remaining issue (pre-existing, not fixed): a polygon that crosses the top/bottom screen edge with a close camera and a
large (scaled-up) actor can reach the span routines unclipped (z-buffer row pointer far outside the buffer, SIGSEGV in
`rdRaster_Span16_TexLitZw_5/7`); repro: office set, `SetActorScale(manny.hActor, 1.8); PutActorAt(manny.hActor,1.15,2.0,0)`.

## Loose files, naming pass 3 (2026-10-29, agent D)

* **Where the game finds files** is documented in `docs/MODDING.md` (6): `ResFile_Open` asks the archive list first
  (`Lab_FindFile`), then `fopen`; `Resource_OpenArchives` builds the list from `GrimDataDir`, the extra data directory and
  the working directory, each directory contributing its `*.LAB`, itself as a pseudo-archive and the 30 `g_ppRequiredLabs`
  subdirectories (`Scripts\`, `DEBUG_Scripts\`, ...). Directories are indexed once at start-up.
* **Text scripts silently failed**: the host msvcrt's text-mode `ftell()` returns 0 after a one-byte `fread()`, Lua's
  `dofile` reads the first byte and seeks back by one, so the first character of every text script was lost.
  `stdFile_Open` (`overrides.c`) now opens read-mode files in binary mode; loose `.lua`/`.set` files work.
* **Examples** (`docs/MODDING.md`, 10): `Actor_UpdateWalker` rewritten in `overrides.c` with a walk speed factor
  (`GRIM_WALK_SCALE`, `SetWalkSpeedScale`), new Lua functions registered through `GRIM_RegisterModApi` (called from
  `Lua_InitGameLibs` by `names/asm_patches.json`), loose `_local.lua` and `mo.set`.
* **Generated C is marked**: functions that are assembled carry `/* NOT COMPILED: ... */`, the ones replaced in
  `overrides.c` keep `/* replaced by the hand-written version ... */` (they used to share one misleading comment).
* **Naming pass 3**: `names/exe_pass3.json` (221 functions): module interface slots (`<Module>_Terminate/_Start/_Stop/
  _SaveState/_RestoreState`), costume tag handlers, rdCamera projections, `Rdmodel3.c`/`Rdkeyframe.c` loaders,
  `Stdconffile.c`, set-file section handlers, resource type handlers, service slots, ... The evidence is the registration
  tables (module interface, `Cos_NewStateBasedTag`, `g_ResTypeTable`, `Services_InitPlatformTable`, `stdBitmap_LoadFile`'s
  extension chain) and the source-file strings in the allocation calls. It also **corrected names that were shifted by
  one**: the five bitmap loaders (`.pic` -> `stdPic_Load`, `.gif` -> `stdGif_Load`, `.pcx` -> `stdPcx_Load`, `.lbm` ->
  `stdLbm_Load`), the costume component handlers (mesh / material / bitmap / keyframe / sprite `Destroy` and
  `NewInstance`), `Std_ParseCommandLine` -> `stdConffile_ReadLine`.
* **Three regeneration lessons.** (1) After renames run `build_src.py`, then `gen_asm.py --select`, then `build_src.py`
  (gen_asm takes symbols from `functions.h`); a stale `asm_funcs.s` leaves undefined `FUN_` symbols. (2) A function that
  only stores the address of a renamed function in a table is not re-exported by `export_changed.py` (put it in
  `raw/touched.json`). (3) Never re-apply a subset of `names/*.json`: the batches lag behind edits made in Ghidra and
  an old batch restores stale names; this produced a second function called `stdBitmap_Load`, calls bound to the wrong
  one, and a stack overflow while loading `splash.bm` before it was found and undone.
* Known: `SetActorScale(manny, 1.6)` crashes in `rdRaster_Span16_TexLitZw_6` (software span rasterizer).

## Coverage pass (2026-10-29, agent B, second round)

Verified by script (hook + PrintWindow + audio peak meter, `GRIM_MULTI=agentB`): all 124 regular sets switch and render with
models, costumes and text (`system.setTable[n]:switch_to_set()`, screenshots per set; `op`, `dp`, `tp`, `ul`, `testroom`
replace `CommonEnter` and break later switches, they are not engine bugs); Manny walking/turning (`manny:walkto`, poll
`IsActorMoving`), the office tube/cards/inventory, dialogue text with voice; movies (intro with audio, ~25 short/medium
`.snm` through `StartFullscreenMovie`); music state per set (`music_state.cur_state`, audible in each) and SFX (`start_sfx`,
`sound_playing`); credits (`credits_menu:run("ingame.txt")`) and `start_script(exit_the_game)` (exit code 0, no crash report);
a 36 minute soak (set hopping, office walking, SFX, movies; private bytes 53 -> 65 MB then flat, 506-595 handles, 9 threads).

Bug classes found (all root-caused, see git log):

* **x87 CRT helpers with lost control-word arguments**: `floor`/`ceil` (`_ctrlfp(DAT_..., 0xffff)` call dropped by Ghidra:
  Lua `floor(2.7)` was 3), assembled; `_CIfmod` (`FUN_100120fa`, Lua `mod`) went through unstitched CRT pieces and called
  address -6: host `fmod` override.
* **Varargs callee with lost arguments**: `luaY_error` (`luaL_verror(fmt)` without message/token: syntax errors printed
  garbage). `scan_varargs.py`-style check: format strings with `%` specifiers and fewer call arguments (only that one left).
* **Non-atomic iMUSE guard**: `Im_GuardEnter/Leave` (`inc [mem]` / load-dec-store) lose an update when the WINMM heartbeat
  thread and the main thread leave together; the counter then stays 1, `ImHeartbeat` never runs again and
  `SoundsFloodMusicBuffer` (called by `Set_LoadResources`) spins forever (two hangs in fast set switching). Now `lock inc` /
  `lock cmpxchg` (overrides.c). The race exists in the original binary too.
* **Movie (Smush) audio silent**: the EXE's own DirectSound stream mixer (`FUN_004d2aa0` creates the stream buffer with COM
  calls through function pointers, `FUN_004d2630` volume, ...) was C with lost arguments: buffer never created, so nothing was
  mixed; and the C `Mixer_Mix*` resampling loops zero-extended 8-bit samples (`*src ^ 0x80`, original sign-extends: huge DC
  offset, clipping). 0x4cdc00-0x4cdfff, 0x4d0000-0x4d40ff are assembled now.
* **Code pointer to a `jmp [mem]` that has no Ghidra function** (Smush shutdown slot 0x4891a0): the symbol became data in
  the non-executable `_sect_text` copy, so quitting crashed (`Engine_ResetSubsystems` called it). `gendata.py` emits a jump
  stub for such symbols; the proper fix is a function at 0x4891a0 in Ghidra.
* Test knobs: the crash report is `grim_crash_<GRIM_MULTI>.txt`. `exit()` from the Lua hook sets `g_quitRequested` before
  `Game_FrameUpdate` tests it, so the window is never destroyed: quit through `start_script(exit_the_game)` instead.
  Hook lines are limited to ~400 characters (longer ones are cut and fail to parse); `getn` does not exist in this Lua.
## Performance (2026-10-29, agent C)

Everything below is measured on the same machine with the in-process counter of `Display_Flip` (`GRIM_PERFLOG=1`,
see "Tools"); "ms/frame" is one pass of the main loop (the engine does not wait for anything, so the frame rate is
`1000 / ms`). Baseline = the tree as it was (all C at -O0, original `Display_Flip` = `GRIM_SLOWFLIP=1`, no peephole).

| scene (movies off, idle unless noted) | before | after |
|---|---|---|
| Manny's office, idle | 1.30 ms (770 fps) | 0.35 ms (2800 fps) |
| office, Manny walking | 1.27 ms | 0.34 ms |
| tour of 12 sets, mean of the per-set medians | 1.24 ms | 0.33 ms (3.8x) |
| busiest sets: do.set / hf.set / vd.set / mx.set | 2.41 / 2.22 / 1.83 / 1.62 ms | 0.96 / 0.53 / 0.62 / 0.38 ms |
| still scenes (nothing moves) | 0.55 ms | 0.04 ms |
| movie playback loop (intro cutscene) | 0.57 ms | 0.08 ms |

Start-up to a rendering Manny's office is about 1 s (movies off), so loading is not an issue.

### Where the time went (sampling profile, `perf/sampler.py`)

* About 89% of the game-code time in every scene is **assembled original code** (the rasteriser, rdCache, rdModel,
  keyframes, Sector_*, Vec3/Matrix), which is already optimised machine code; the C that is compiled from the decompilation
  is about 10% (Lua VM, Mem_Copy, Plane_*, Insane blit/decode).
* **`Display_Flip` was 35-40% of every frame**: the back buffer is a 16 bpp (565) DIB section, and `BitBlt` to the 32 bpp
  window DC made GDI convert it pixel by pixel in the kernel (`win32u` was the top "function").
* After that the hottest functions were **`rdRaster_SpanR_Flat_11/12` (30-35% of rendering)**: the scan-line edge set-up, which
  turns floats into ints with `fldcw floor; fld; fistp; fldcw default` (and `fldcw ceil; frndint`). `fldcw` serialises the
  x87 unit on current CPUs; 1807 floor and 100 ceil sites like this exist in the assembled EXE, plus `_ftol` itself
  (`fstcw / fldcw trunc / fistp qword / fldcw`).
* In movies `Insane_BlitRows16` (a 4-byte copy loop at -O0, run once per main-loop pass) was 58% and `Display_Flip` 27%.

### What was done (each is a separate mechanism)

1. **`Display_Flip` (build/fastpaths.c).** A 32 bpp DIB section (same size, top-down) is kept next to the game's 16 bpp one;
   the 565 (or 555) pixels are expanded with SSE2 (`x<<3 | x>>2`, which is exactly what GDI produced: screenshots of the old
   and the new path differ only where Manny's animation differs) and `BitBlt` then copies same-format pixels. On top of that the
   previous 16 bpp frame is kept: only the band of rows that changed is converted and blitted, an identical frame costs a
   compare of 600 KB (about 20 us) and no GDI call at all, and a full blit is forced every 100 ms (and after any mode change) in
   case the window lost its contents. Falls back to the original BitBlt for 8 bpp modes, DirectDraw, odd widths.
   Knobs: `GRIM_SLOWFLIP=1` original BitBlt, `GRIM_NODELTA=1` full conversion + blit every frame, `GRIM_PERFLOG=1` appends
   `perf: 256 frames, x ms/frame (fps), flip y us/frame` to the `GRIM_LUA_LOG` file every 256 flips.
2. **x87 control-word peephole (build/peephole.py, run by link.py on `src/GRIMFANDANGO.EXE/asm_funcs.s`, output
   `obj/GRIMFANDANGO.EXE/asm_funcs_fast.s`).** The control words are `DAT_00900524` (default), `...526` (floor, 0x077f), `...528`
   (truncate, 0x0c7f) and `...52a` (ceil, 0x0b7f), set by `Services_SetCurrent`. The two dominant shapes become
   `movss xmm0,[m]; roundss xmm0,xmm0,9; cvttps2dq xmm0,xmm0; movd [d],xmm0` (floor) and `movss; roundss ,10; movss [d],xmm0`
   (ceil): the same result (floor/ceil of a single are exact, out-of-range gives 0x80000000 in both), no control-word change, no
   stack effect. A sequence is only rewritten when none of its interior labels is a jump target (0 skipped). The CRT `_ftol` becomes one
   `fisttp`. 1807 + 100 sites and `_ftol`; the roughly 90 remaining `fldcw trunc` pairs (once per perspective span: `rdRaster_SpanP*`,
   `Span_Tex*`, precision control) were left. **Requires SSE4.1 (roundss) and SSE3 (fisttp)**; `GRIM_NO_PEEPHOLE=1 make link` links the
   untouched assembly. This one change took the office from 0.67 to 0.30 ms.
3. **Per-module -O2 for the C code (build/opt.mk).** `Makefile` includes `opt.mk` (override with `OPTMK=file`), which holds one
   line per module, `OPT_<PROG>/<module> := $(OPT_FAST)`, with `OPT_FAST := -O2 -fno-omit-frame-pointer
   -fno-delete-null-pointer-checks` (frame pointer: `STACK0X` and the Ghidra `_frame` idiom assume one; the pointer-check flag
   is a precaution). The flags are appended after `$(OPT)` so the last -O wins, and the complete flag string of every object is
   stored in `obj/<prog>/<module>.flags` (rewritten only when it changes), so editing `opt.mk` or passing `OPT_ALL=-O1` / `EXTRA_CFLAGS=`
   rebuilds exactly the modules affected. 162 of 164 candidate modules are on (all 29 LUA.DLL, all 11 IMUSE.DLL, all 4 CHORE.DLL,
   118 of 120 EXE modules; `crt` / `crt_unnamed` are not linked). **Left at -O0: `GRIMFANDANGO.EXE/lecshare` and
   `GRIMFANDANGO.EXE/resource`** (with either at -O2 the game hangs at a black screen or dies at start-up; not investigated further, neither is
   hot). A blanket -O2 without `-fno-omit-frame-pointer` crashes at start-up; with it only those two modules fail.
   The list was found by `perf/bisect.py` (greedy delta debugging: each trial builds into `obj_t/`, boots, walks, compares screenshots
   with the -O0 reference) and then verified with `perf/soak.py` and `perf/longsoak.py`.
4. **Hand-written replacements (build/fastpaths.c, compiled -O2 -msse2 and linked into every program; `tools/build_src.py` puts the
   decompiled version of every function defined there under `#if 0`, like overrides.c):** `Display_Flip`, `Mem_Copy` (forward
   `rep movsb`; blocks of 256 bytes or more that do not overlap closer than 16 bytes use 16-byte SSE copies), `Insane_BlitRows16` (SSE row copies,
   the 16-bit look-up-table variant kept as a plain loop).

### Verification

* `perf/check.py <dir> <tag> base [quick]`: boots with the Lua hook, waits for Manny's office, takes PrintWindow shots (idle, after
  `manny:walkto`), compares with the shots of the reference build (the -O0 build against itself: 0.005% of pixels differ by more than 24, the
  optimised build 0.02-0.4%, all of it Manny's animation phase), checks Manny's position and the Lua error count.
* `perf/soak.py <dir> <tag> base`: tours 12 sets through `system.setTable[...]:switch_to_set()`, plays `funny.snm`, `Save`s, changes a
  global, `Load`s and checks the global came back. `perf/longsoak.py <dir> 200`: 167 set changes and 15 movies in 200 s without a crash.
* The -O0 reference (`perf/base`, and `perf/o0` for the in-process timings) is built with `GRIM_NO_PEEPHOLE=1 make OBJ=obj_o0 OPTMK=perf/empty.mk link`.

### Tools (build/perf/)

`ctl.sh start|stop|pid` (launches and kills only builds under grim-agentC; `GRIM_NOMOVIE=0` = movies on), `shot.py` (PrintWindow to PNG + raw BGRA),
`sampler.py PID seconds interval_ms` (suspends every thread, reads EIP and the ebp chain, resolves with `nm`, marks functions that are compiled C and
assembled ones; `gen_csyms.sh` writes the C symbol lists), `benchsets.py` (frame time per set), `bench.sh`, `boot.py`, `check.py`, `soak.py`,
`longsoak.py`, `bisect.py`, `fps.sh` / `ivl.sh` (gdb breakpoint counters; gdb distorts frame times by a factor 3-5, use the in-process log).

### Not done / observations

* The rest of a frame is the original rasteriser's per-pixel span code (`rdRaster_Span16_TexLitZw_*`, `Span16_FlatZ_2`: 40-50%), keyframe
  interpolation and polygon clipping, all original machine code. Only a rewrite (SIMD spans) would speed it up.
* The main loop never waits: it spins at 100% of one core (2800 passes/s in the office, 12000 in a movie), as the original does. Sleeping
  when `Display_Flip` found an identical frame would cut the CPU load; it was not added because it changes the timing of input polling.
* The Lua test line `T(soak_sets[1 + mod(n-1, 12)])` (a float index returned by `mod`) kills the Lua VM in the -O0 baseline as well; use an
  integer loop counter in test scripts. Not looked at.
Known remaining issue (fixed later, see "Scaled actors" below): a polygon that crosses the top/bottom screen edge with a close camera and a
large (scaled-up) actor can reach the span routines unclipped (z-buffer row pointer far outside the buffer, SIGSEGV in
`rdRaster_Span16_TexLitZw_5/7`); repro: office set, `SetActorScale(manny.hActor, 1.8); PutActorAt(manny.hActor,1.15,2.0,0)`.

## Scaled actors: the "unclipped polygon" crash (2026-10-29, agent F)

Symptom (office, `SetActorScale(manny.hActor,1.8); PutActorAt(manny.hActor,1.15,2.0,0)`): SIGSEGV in
`rdRaster_Span16_TexLitZw_5/_7`, the z-buffer row pointer a few rows above the buffer (y = -2.4 -> unmapped page in front of the
VirtualAlloc'd z-buffer). The clip stages themselves are fine (rdClip_*, rdPrimit3_ClipFace, rdCache_AddMesh, the frustum block at
camera+0x48 and the asm of all of them match the Ghidra disassembly). The polygon was simply never sent to the clipper:
`rdModel_DrawMesh` runs `Frustum_TestSphere(frustum, centre, mesh+0x60)`, a result of 0 ("fully inside") makes
`rdModel_AddMeshToCache` use `rdPrimit3_CopyFaceVerts` instead of `rdPrimit3_ClipFace`, and the radius it tested was wrong.

Cause: `Costume_ApplyScale` (0x495510), called before and after the meshes of an actor are drawn, multiplies the radius of every model
and mesh by `actor+0x30` (so the sphere test covers the scaled geometry) and then stores the reciprocal in `actor+0x30` so that the second
call undoes the first. The original code (decompiled and disassembly agree) stores the reciprocal *inside* the per-component loop, so the
factor alternates s, 1/s, s, ... from component to component. With one component the second call is an exact undo; Manny's costume has 26
components, so every call multiplied the even components by s and the odd ones by 1/s again: the radii drifted by s^2 per frame (comp 18:
0.369 -> 0.664 -> 1.195, comp 1: 0.011 -> 0.0061 -> 0.0034 ...). A component whose radius had shrunk is "inside" although its polygons stick
out of the screen, and the span routines then write outside the buffers (in the original this overwrites neighbouring heap quietly; the
rebuilt layout has an unmapped page in front of the z-buffer). Not a rebuild artefact as such, a latent bug of the original code that only
shows with a scale != 1 and components > 1.

Fix (`build/overrides.c`, hand-written `Costume_ApplyScale`): the same factor for all components, the reciprocal stored once per call;
non-model components (type != 1, e.g. the first component of Manny's list) are skipped (the original multiplied a float at +0x5c of
whatever they point to). Identical to the original for costumes with exactly one model component.

How it was found (reusable): gdb python breakpoints (script in the notes of this session: `agentF_run4.gdb`, not committed) at
`rdModel_DrawMesh` (matrix, radius, `Frustum_TestSphere` result and relative centre), `rdModel_AddMeshToCache`/`rdCache_AddMesh` (clip flag
`UINT_007f1898`, projected and camera-space vertices, flag BAD when an unclipped polygon leaves [0,640]x[0,480]) and `Costume_ApplyScale`
(list of components with model/mesh radii at entry and exit). The stored radius of a mesh divided by the largest vertex distance was exactly
1.1/1.8 for every mesh of Manny (radius = 1.1 x extent in the file, then wrongly divided by the actor scale), which pointed at the scale
code; the gdb crash handler (`handle SIGTRAP nostop noprint`, then a python loop that executes command files after the crash) allows
inspecting the dead process repeatedly without restarting the 40 s boot.

Verified (Lua hook + PrintWindow, gdb attached, no SIGSEGV): the repro; Manny scale 1.8 and 2.5 at 12 positions around the camera (head,
legs, arms crossing every edge); scale 1.0 and 0.5 close-ups; 900 frames of walking at scale 1.8 (radii stay constant, 910 polygons outside the
guard band were all sent through the clipper, none unclipped); Glottis in the garage at scale 1.8 .. 14 (huge, crossing the top and side
edges); boot to the office, walking (`WalkActorForward`), the F1 menu (`main_menu:run()`).

## Scripted test suite on the rebuilt engine (2026-10-29, agent G)

`grim_tools/autorun/rebuilt_test.sh` / `rebuilt_all.sh` (REBUILT_DIR=<this tree>/build/run) run the user's Lua test tiers
against the rebuilt exe. The earlier "stalls" of the turn tier of `test_nav.lua` and of the whole of `test_rules.lua` were a
test-environment problem, not an engine bug: the hand-made sets (`t_flat.set` ...) live in `grim_tools/autorun/tests/sets/DATAUSR.LAB`,
the install keeps that archive parked as `DATAUSR.LAB.bak`, so `Set:create`/`switch_to_set` found no file (`Ack!  No idea what CD
t_flat.set is on!` in the log) and the script waited for a set that never came. `rebuilt_test.sh` now installs the archive in GRIMDATA
for the run. With it: unit 60/60, walk 44/44, rules 393/393 (every recorded value of the original within 3e-4 m), turn 31/31, slide
9/9 (corner/wall slides within 6 mm of the original, stair-wall slides identical to 4 decimals), coll 157/162 (the 4 diagonal
head-on box slides go to the other side of the approach line, the same chaos as the cases in `nav_known.lua`).
The `move` tier fails for the 24 cases that start on the stair of `ly` (72/96): the current `ar_nav.lua` plans a 4 point way
(an extra point along Manny's heading before the stair link) where the logs recorded on the original have 3; the constrained walker
is then held up at the stair top 7 times. With the extra point dropped all 96 pass on the rebuilt engine.
Debug trick: `lua31.exe` of `autorun/tools/lua31` takes the DLL as its first argument, so the original and the rebuilt `lua.dll` can be
compared on the planner without starting a game (identical results).

## Start-up: the whole screen flashing black (2026-10-29, agent L)

Symptom (user): the entire screen goes black for a moment when the game starts. Reproduced with
`tools/desktop_watch.c` (gcc -O2 -o watch.exe desktop_watch.c -lgdi32 -luser32) (a desktop sampler: 192x108 thumbnail of the whole screen plus
`GetWindowRect`/style/topmost of every `wKernel` window every ~30 ms, started before the game): about 0.5 s after the window
appears, the game window is 3072x1728 (the whole desktop), black, and flips `WS_EX_TOPMOST` on and off twice; then it shrinks to
656x516. Nothing else (no `ChangeDisplaySettings`, no monitor mode change).

Two causes, both in the original code that the rebuild runs unchanged:

1. `Win_CreateMainWindow` (0x4ac1f0) creates the `wKernel` window as a visible desktop-sized WS_POPUP (the shape a DirectDraw
   full-screen device needs). The windowed DIB device that this build selects (`Display_InitFromConfig`) only turns it into a
   640x480 captioned window at the very end of `Display_Select` (`Win_SetWindowedSize`), i.e. after the whole device/mode
   enumeration. Until then a black screen-sized window covers the desktop.
2. Even with a small window, the enumeration of the DirectDraw devices does it again: `FUN_004761b0` (DirectDrawEnumerate callback,
   needs only `GetCaps`) and `DDraw_Create` (`EnumDisplayModes`, run for every device from `Grim_EnumDisplayModes`) call
   `SetCooperativeLevel(hwnd, DDSCL_EXCLUSIVE|FULLSCREEN[|ALLOWMODEX])` (0x11 / 0x51) on the game window and then NORMAL (8).
   ddraw makes the window topmost and resizes it to the desktop (gdb: `SetWindowPos(hwnd, 0,0,0, 0xc00, 0x6c0)` from
   `DDraw_Create`), and back; on real fullscreen hardware this is also what blanks the monitor.

Fix:
* `build/overrides.c`: hand-written `Win_CreateMainWindow` creates the window directly in its final windowed form (style
  0x10cf0000, 640x480 client + the same frame metrics `Win_SetWindowedSize` uses, so that call becomes a no-op), at the same place
  with the same `ShowWindow`/`UpdateWindow` (activation order unchanged). `GRIM_DISPLAY_DEVICE=<n>` with n > 0 (a DirectDraw
  full-screen device) keeps the original desktop-sized popup.
* `names/asm_patches.json`: the three `SetCooperativeLevel` flag pushes of the probing code (`FUN_004761b0` @0x476297,
  `DDraw_Create` @0x476111 and @0x476145) get `mov dword ptr [esp],8` (NORMAL) after the `push`. The caps and mode lists do not
  need exclusive mode; the real full-screen open (`DDraw_CreateSurfaces`) still sets 0x11/0x51 itself. Known difference: the
  Mode-X (320x240) modes that only `DDSCL_ALLOWMODEX` lists are no longer enumerated for DirectDraw devices.

Verification: same sampler before/after (the window stays 656x516, never topmost, for the whole 30 s of a normal start with the
logo movie: `chg.sh`), boot, `manny:walkto`, F1 menu and the logo screenshots, autorun unit 60/60 and walk 44/44.
Not tested: the DirectDraw full-screen device (`GRIM_DISPLAY_DEVICE=1`) on this shared machine.
Side note, not changed: the client area is 640x477, not 480: `UINT_008d0a88` uses `SM_CXSIZEFRAME*2` and ignores the padded border of Windows 10/11 (the original code does the same).

## Saves of the original game (2026-10-30, agent K)

The 76 saves of the original v1.01 EXE in `GRIMDATA/saves_old_numbering/` (`grim00-03`, `grim10-80`, `grim90`; the autorun
checkpoints of `grim_tools`) load in the rebuilt engine: scene, Manny's position, text, inventory/Lua state and the playing
sounds come back, the game keeps running (Lua tasks, walking, set changes), and a rebuilt save made from such a state
reloads. `python -I build/perf/oldsaves.py build/run [--only NN,..]` checks this per save in a fresh game (details below).

### Layout of a save (same code writes and reads it, so rebuilt saves have the same layout)

The file is gzip (`gz*` of the EXE) around a stream with **no magic and no version**; `Engine_SaveGame` (0x482fe0) /
`Engine_LoadGame` (0x483240) pass `SaveGame_Write` / `SaveGame_Read` to each module in turn. `GRIM_SAVETRACE=<file>`
(build/overrides.c, `tools/savetrace.py` reads it) logs every call (offset, size, calling function), which gives the layout:

| part | writer (restore = the matching `*_RestoreState`) | content |
|---|---|---|
| header | `Lua_CallSaveGameCallback` | dword length + length-prefixed strings = the table `GetSaveGameData` returns (autorun: name, flags, set). Skipped (`gzseek`) by Load |
| thumbnail | `Engine_SaveGame` | dword 94000 + 250x188 RGB565 pixels (`SaveGame_LoadThumbnail` reads it for the menu). Skipped by Load |
| costumes | `Cos_Save` (CHORE.DLL) | costume registry: id + 32 byte name |
| resources | `Resource_Filio_SaveState` | per resource: name, type fourcc, id (the data pointer of the saving process) |
| text objects | `sputText_SaveState` | the live `TextObject`s field by field, 3 default fonts |
| set / actors / render / primitives / movie | `Set_SaveState`, `sputActor_SaveState` (+ `Cos_SaveInstance`), `Render_SaveState`, `sputPrimitive_SaveState`, `Movie_SaveState` | state per module, one `SaveGame_Write` per field (a typical save is ~500 000 calls) |
| dword | `Engine_SetSavedValue` | `UINT_008a8c48` |
| Lua | `lua_Save` (LUA.DLL, `lstate.c`) | the whole Lua state: string / closure / proto / table / task objects with their heap address as id, then the tables of `TObject`s (tag, value) |
| iMUSE | `FUN_10008250` (IMUSE.DLL via `g_pfnIMuseSaveHook`) | 40 byte reverb name ("OFF", "Basic Reverb", ...); dword 38564 + blob = 4 + fades 0x280 + triggers 0xb20 + 16 dispatch tracks x 0x854 + 16 stream-track records x 60; dword 984 + script blob; dword n + n x 40 (sound name[32], id, param 0x7c) + n x 12 (id, `SoundsGetParam` 0x600 and 0x700) + n x 8 (id, hook) |

### What is stored as a machine address (and what it needs)

Scanning all 76 saves (module images in the saving process: the EXE at its fixed 0x400000, `IMUSE.DLL` at **0x01070000,
0x01090000, 0x010a0000 or 0x01140000, never at its preferred 0x10000000**) found these classes. The original game had to cope
with all of them being stale after a restart (DLLs at a different base, heap at different addresses), which is why nearly
everything is harmless:

1. **Lua C functions: `(index of its library, counted from the NEWEST) << 16 | index in the library`** (`lua_FuncPtrToID` /
   `lua_IDToFuncPtr`, the "pointer-id tables" `DAT_1002bf60/68`, `lstate__7830` / `lstate__78b0`). This is not an address but
   it depends on the registration order of the libraries: the original has 14 (ids up to `0xd001b` occur: base library =
   lib 13, `stderrorim` 12, strings 9, io 10/11, engine table 6, ...). **This was the crash**: `GRIM_RegisterModApi` (mod example
   10 b) registered a 15th table after the engine table, so every older library moved by one and a saved global such as
   `type` (`0xd001b`) or `dofile` (`0xd0004`) hit `stderrorim` (a 1-entry table): null function pointer, crash in `ldo__44e0`
   a few frames after `Load`. Fix: the mod table is registered **first** (`GRIM_RegisterModApiLib` = `lua_recognizelib` at the start of
   `Lua_InitGameLibs`, before `lua_open` registered the base library) so it is the oldest and no id changes; the globals
   are created by `GRIM_RegisterModApi` where it was before (names/asm_patches.json).
2. **iMUSE blob: raw pointers into `IMUSE.DLL`, all rewritten or only tested for non-zero by the restore**. Fields (offsets in
   the 0x854 byte dispatch track): +0x000 pointer to its stream-track record (`DAT_10031f28 + 60 i`; `Im_RestoreImpl` writes it
   again), +0x81c pointer to the stream object (`&DAT_10031e98` in every save; `iMUSE_Dispatch__20c0` only tests it for
   non-zero and creates a new stream), +0x824 pointer into the 50 entry pool `DAT_10024df0` (re-allocated by `20c0` when
   +0x18 is set, otherwise unused); the 60 byte stream-track records hold the list links (cleared by `Im_RestoreImpl`) and the
   dispatch pointer (rewritten). Nothing in the blob is dereferenced before it is rewritten, so **no translation is needed**: the
   rebuilt restore re-creates streams in the rebuilt image (verified: every sound of the saves has play count 1 after load, e.g.
   `ImGetParam(1317, 256)`; gdb on the track table shows the music stream of track 0 running and sfx tracks ending). The value
   quoted in the task (`&DAT_1001e900`) does not occur in any save.
3. **Text objects point to their speaker with a raw heap pointer** (`TextObject+0x254`, flag 4 at +0x258; written by
   `Actor_SayLine`): the saves hold 0x04d7a21c, 0x04d966fc, 0x1004c88c, ... (the actor table moves between runs and
   `Actor_Create` reallocs it). Nothing remaps it on load, so the original zeroed a word of whatever heap block the stale
   pointer hit when `ExpireText` ran; in the rebuilt engine the same pointer faulted (grim62, "I bet Glottis would know.").
   Fix: `Engine_LoadGame` is overridden (build/overrides.c, `GRIM_FixTextActors`): after the restore hooks, every actor whose
   extra data `+0x1ec` names a text object (that link *is* remapped by `sputActor_RestoreState` through
   `TextObject_FindBySelf`) is stored in that object's `+0x254`; speech text objects without a speaker lose flag 4.
4. **Ids that are heap pointers by design** (Lua object ids; resource ids = data pointer of the saving process, mapped back by
   `Res_DataFromHandle` / `TextObject_FindBySelf`; text object "self" at +0x25c; the font handles of a text object): fine.
5. **EXE addresses**: only the text object's `+0x208` (`&UINT_008a94b8`, written raw into the file, rewritten by
   `sputText_RestoreState`) and `+0x20c` (self pointer + 0x240, rewritten). No other field of a module's state lies in the
   EXE image (scan of every 4 byte read of three traced loads: only that and float / colour values), so the different section layout of
   the rebuilt EXE needs no translation layer.

Rebuilt saves are written in the same format. Saves made by a build between the mod API commit (agent D) and this one carry
the shifted library numbering of the old registration order (a test file of agent C, `agentC_soak.gsv`, loads but calls wrong
C functions later); saves of earlier builds (before the mod API) and of the original are fine.

### Verification (`build/perf/oldsaves.py <exe-dir>`)

76 / 76 saves: loads without a crash (before the fixes every save crashed: Lua null call; after the first one grim62 still
died in `Lua_ExpireText`), scene state readable,
every sound listed in the iMUSE tail playing (22 sounds in 22 saves), a Lua task runs, Manny walks 0.5 m (reported only), a
`Save` of the loaded game plus a Lua marker and the scene survive `Load` of that save (original -> rebuilt -> reload), a set
change through `switch_to_set` works and the game still runs. Screenshots were checked for ga.set (grim01), ha.set (grim12),
bl.set (grim62). The script starts a fresh game per save (`GRIM_MULTI`, Lua hook, no OS input; private copies of the saves in
the data folder are deleted at the end), retries a boot that failed because the previous instance's window was still there
and prints the crash header of `grim_crash_<tag>.txt` on a failure.

Remaining / notes:
* **An intermittent crash after a load** (3 of about 380 loads of fresh games, always a write fault exactly at a page boundary):
  `grim38` and `grim72`: `Set_SwitchSetup` (first frame after `Load`) -> `Render_ConvertBackground` -> `Surface_CopyConvert` ->
  `stdCompress_Decompress` -> `stdCompress_DecompressLoop` +0xf5 writes past the end of the 0x4b000 byte destination (the LZSS
  loop of the set's background / z-buffer bitmap into `g_pTempSurface`); `grim90` once in `Mem_Copy` (0x280 bytes). Neither
  reproduces when the same save is loaded again (60 + 250 loads in one game, 40 fresh games each for grim38 and grim72, with and
  without CPU load, 76 fresh games one per save): not a function of the save contents. Looks like a stale /
  too small temp surface or a purged resource under memory-budget pressure, not like a load-format problem, and it is not
  understood. `oldsaves.py` keeps the full crash report in `%TEMP%\grim_<tag>_lastcrash.txt`, retries a crashed save once and
  prints "FLAKY" when the retry passes.
* No dialect detection for the saves of the in-between builds: a marker would change the format, and as it is original and
  rebuilt saves are interchangeable in layout.
* Ghidra: nothing required. Useful names for the next naming pass: `TextObject+0x254` speaker actor, `+0x258` flags
  (1 keep, 2 hidden, 4 speech, 8 always draw), `+0x25c` self id; an `Engine_LoadGame` comment "text object speaker pointers are
  not remapped (original bug), see GRIM_FixTextActors".

## Less assembly in the EXE low half (2026-10-30, agent I)

Scope: `GRIMFANDANGO.EXE` 0x401000-0x49ffff.  Functions that the build rebuilt from Ghidra's disassembly (`asm_funcs.s`)
went from 1046 to 473 (372 of those are the software rasteriser, see `docs/ASM_REMAINING.md` for every remaining function and the
reason).  About 570 functions are compiled C again; about 20 of them are written by hand in `build/overrides_exe.c`.

**How a function is moved from assembly to C**
1. Add its address to `names/asm_exclude_exe_lo.json` (read by `tools/gen_asm.py` together with `asm_exclude.json`), or define it in
   `build/overrides_exe.c` / `overrides.c` / `fastpaths.c` (then it drops out of the selection by itself and `build_src.py` puts the
   decompiled text under `#if 0`).
2. `python -I tools/gen_asm.py GRIMFANDANGO.EXE --select && python -I tools/build_src.py && cd build && make link -j14`
   (`build/difftest/rebuild.sh` does all of it and copies the result to `build/run_t`).
3. Verify (below).  To go back, delete the address / the C block and rebuild.

**Why a decompiled function was assembled (and the fixes)**: float bits kept in `uint` slots (retype the local or parameter in Ghidra:
`tools/fix_float_locals.py`, `fix_float_params.py`; the heuristics are not perfect, look at the diff), `_ftol` of a lost x87 result
(`tools/ftol_fold.py` folds `F(args); x = _ftol(CONCAT44(..))` into `x = (longlong)F(args)`), hex float literals passed as ints
(`FBITS()` in `build_src.py`), prototypes with stack arguments the decompiler dropped, `__thiscall` methods, rounding-mode switches
(`FLDCW`: `Math_Round` was really a floor and is now `Math_Floor`), parameter slots reused as output buffers, COM vtable calls.

**Traps found by the tests** (all compile and boot, but differ):
- Hidden x87 results: `Vec3_NormalizeTo` is `void` in Ghidra but leaves |v| in ST0 for an assembled caller; the C version must push it
  back (`fldt`).  The lengths, sums and quotients must stay in extended precision with the original order of additions
  (`GetShrinkPos` fails otherwise).
- gcc forwarding stores through pointer walks (wireframe actors): `build/opt.mk` disables `-ftree-fre/-pre/-dominator-opts/-dse` for
  the `-O2` modules.
- `Math_NormalizeAngle360` needs the intermediate rounded to float (volatile), `Walker_UpdateYaw` (scale 0 / NaN) and
  `Collision_TestActorAgainstOthers` differ in NaN compares: kept assembled.
- Functions patched by `names/asm_patches.json` (`Game_FrameUpdate`, `Input_PollKeyboard`, `sputLua_Update`, `Lua_InitGameLibs`) need the
  hook in C too (`Game_FrameUpdate`, `sputLua_Update` are in `overrides_exe.c`).
- Shared Ghidra edits by other agents change prototypes under you (the `Walker_*` floats): re-export (`tools/export_changed.py`) and look
  at `overrides.c`.

**Verification used** (`build/difftest/`): `run_lua.sh <rundir> <tag> <script.lua> <log>` boots to Manny's office with a fixed frame time
(`GRIM_SIMTIME=17`) and runs a Lua script through the `GRIM_LUA_FILE` hook, so the converted build (`build/run_t`) can be diffed against the
all-assembly reference (`build/ref`): `t2` actors drawn, `t3` walking, `t7` primitives, `t8` save/load round trip (`FOLLOW=`),
`t9` GetShrinkPos, probes of ~100 Lua functions (`run_probe.py`/`cmpprobe.py`), `tour.lua` pixel comparison of every set (`cmpshots.py`).
`oracles.sh` runs the battery.  `bisect.py` finds the one function of a conversion list that breaks a test (the predicate is a probe, a
log diff or a `suite:` of `build/qtests.sh`).  The scripted suite `grim_tools/autorun/rebuilt_all.sh` is the final gate.
`build/qtests.sh` is its quick subset (unit 120 / walk 88 / coll 314 pass, 8 known coll differences).
Rare (about 4 percent) boot segfaults also happen with the all-assembly reference; the harness retries.

## System libraries instead of the bundled CRT/zlib (2026-10-30, agent M)

Inventory, risk ratings and the list of other replaceable libraries: `docs/LIBS_INVENTORY.md`.  What the starting point
really was: `link.py` had always left the decompiled MSVC 6 runtime module `crt.c` out of the link (all four modules
import `malloc/free/fopen/printf/qsort/...` from the system `msvcrt.dll`, so there is ONE heap for EXE, LUA.DLL, IMUSE.DLL
and CHORE.DLL), but the runtime functions Ghidra had not named (`crt_unnamed.c`), runtime functions the assembly selection
had pulled in (`_snprintf`+`_output`, `_setjmp3`, `floor/ceil`, `_CIfmod`, ...) and the statically linked runtimes of
CHORE.DLL and IMUSE.DLL were still compiled from the original code.  The game's zlib 1.1.3 was bundled in the EXE.
(UCRT is not an option: MSYS2 has no 32-bit UCRT toolchain; msvcrt.dll is on every Windows.)

**Mechanism (`names/lib_replace.json`, read by `tools/build_src.py`, `tools/gen_asm.py`, `build/link.py`)**

| key | meaning |
|---|---|
| `<PROG>.dead` | addresses of original runtime code that no live code can reach: `build_src.py` writes the C text under `#if 0`, `gen_asm.py` never assembles it, the symbol (if anything dead still names it) becomes a trap stub |
| `<PROG>.host` | live functions that the system library replaces; same removal, the symbol then resolves to the msvcrt import (same name) or to an alias |
| `<PROG>.zlib` | the bundled zlib; the symbols (`_inflate`, `_deflateInit2_`, `_crc32`, ...) resolve to `libz.a` (`-Wl,-Bstatic -lz`) |
| `aliases.<PROG>` | `{C symbol: msvcrt symbol}`: `link.py` writes `obj/<prog>/lib_alias.s` with `sym: jmp *__imp_<name>` (through the import table, so the thunk can never loop back to a symbol of this link: needed for the swapped `_floor`/`_ceil`) |

Adding a function: put its address in `host` (and an alias if the name differs or Ghidra has no name), `python -I tools/gen_asm.py
<PROG>` (use `--select` when the function is also defined in `build/overrides.c`: the selection must be re-derived), `python -I
tools/build_src.py`, `make -C build link`.  **Check the semantics first**: the Ghidra names of unnamed runtime functions are
guesses (floor/ceil swapped, `strchr` that is `strrchr`, `_sqrt` that is `asin`; all in LIBS_INVENTORY section 5).  The
safe method is a differential test against the original code: load the baseline DLL (`--export-all-symbols` exports every
function) or execute the bytes of `raw/<prog>/sections/text.bin` from a VirtualAlloc'ed page and compare with msvcrt.dll on
random inputs (the test programs are quoted in the inventory; each function above was run on 10^5-4x10^6 inputs).
`python -I tools/lib_audit.py build/obj/<PROG>/<file> [--orig-exports raw/<PROG>/exports.json] [--json out]` lists the functions of
the linked image that cannot be reached (DLLs: roots are the exports of the ORIGINAL dll, the rebuilt ones export everything)
and, via `WHY=<sym>` / `WHYSTUB=<sym>`, why a function is live.  Stubs that are still reachable are latent traps: after this
work only three pow special-case fragments in an EXE data table and two CHORE.DLL start-up table entries remain, none callable.

**Results (build to build, all verified; baselines are the tree of commit 9b9f546)**

| | before | after |
|---|---|---|
| runtime functions removed as unreachable (`dead`) | 0 | 558 (EXE 133, LUA.DLL 153, IMUSE.DLL 120, CHORE.DLL 152) |
| live runtime functions replaced by msvcrt (`host`) | 0 | 33 + 1 sign wrapper (EXE 9, LUA.DLL 9, IMUSE.DLL 9, CHORE.DLL 6) |
| zlib | bundled 1.1.3, 53 functions | system 1.3.2, static, no new DLL |
| .text EXE / LUA / IMUSE / CHORE | 932496 / 105184 / 121376 / 50464 | 905424 / 75168 / 77712 / 21488 |
| reachable trap stubs (static) | EXE 2 + the `_output` helpers (bound to LUA.DLL's stubs), IMUSE.DLL 7 | EXE 3 (data-table fragments of `_pow`), CHORE 2 (init table), IMUSE 0, LUA 0 |

What was deliberately kept: EXE `_ftol` (peephole `fisttp`, build/peephole.py), `_alloca_probe` (msvcrt.dll does not export it),
`_CIpow`/`_pow`/LUA `_CIfmod` (overrides.c, already msvcrt), CHORE.DLL's three-function `qsort` (msvcrt's orders equal keys differently:
measured on 20000 random arrays), the four ctype table wrappers of the Lua lexer, `rdraster`/mixer/codecs (not library code).

**Behaviour changes, each its own commit so they can be dropped**: `acos()` in Lua returned 0 (FUN_10006f80 dropped the x87 argument; now
assembled, `asin`/`acos` use msvcrt) and `rand()` starts at seed 1 like the original (the `_getptd` shim block is zero), so an unseeded
`random()` sequence differs from the previous rebuild (identical after `randomseed`).  Saves written by the rebuild are valid gzip
but not byte-identical to 1.1.3's output (zlib 1.3.2 deflates differently, 877 KB vs 860 KB for the same payload); the original saves
inflate identically.

**New knobs**: `GRIM_BUNDLED_ZLIB=1` for `build_src.py` / `gen_asm.py` / `make link` (regenerate `src/` with it to build the game's own zlib 1.1.3 again);
`build/perf/libcheck.py <exe-dir> <tag> [--movie] [--data DIR]` (boot, Lua probes, walk, 5 sets, Save/Load, debug log, movie; `--diff A B`,
`LIBCHECK_SKIP=A,RU` ignores the lines that are expected to differ).

**Test setup notes** (for running next to other sessions): a private data dir made of hard links to the LABs works (`--data`); the
autorun scripts of `grim_tools` find `GRIMDATA/autorun_all.lua` of the shared install first even when started from a private dir
(cause not analysed), so a private copy must use another file name (`agentM_all.lua` in `build_original.sh`/`rebuilt_test.sh`).

## Less assembly (2026-10-30, agent J)

Scope: GRIMFANDANGO.EXE >= 0x004a0000, LUA.DLL, IMUSE.DLL, CHORE.DLL.  Counts and the reason for every function that is still
assembled are in docs/ASM_REMAINING_2.md.

How a function leaves the assembly selection
- `names/asm_exclude_agentJ.json` (one address per line, per program) forces a function to be compiled from the decompiler's
  C; `names/asm_extra_agentJ.json` keeps functions assembled that the artifact rule would otherwise convert.
- A function defined in `build/overrides.c` is always C (hand-written, commented).  The blocks added by agent J are delimited
  by `agentJ:` comments.

Root causes fixed at the source (Ghidra, then `tools/export_changed.py`)
- Import prototypes (`tools/set_import_protos.py`, `names/import_protos.json`): the EXE's calls into LUA.DLL and IMUSE.DLL
  now pass the right arguments.
- Return types (`tools/set_return_type.py`): functions declared `void` whose callers use EAX, and bool/char returns.
  `tools/build_src.py` also widens bool/char/short returns to int (a gcc function leaves the upper bits of EAX undefined; MSVC
  callers, and assembled callers, test all of EAX).
- Float values stored in int slots (`float_retype2.py`): locals whose bits are a float are retyped in Ghidra; the generator
  turns `(float)int_var` into a bit reinterpretation (PUN) in functions that never use FILD.
- x87 values that Ghidra loses between instructions (`_ftol()` without an argument, `lua_getnumber` results): the common
  patterns are rewritten by `fix_ftol`; the rest are hand-written in overrides.c.
- Test oracles: `build/jtmp` (kept out of git) has hostdiff.py (original vs rebuilt LUA.DLL under the stand-alone host), the
  Lua scenario traces and a delta-debugging bisect.  Lesson: a bisect whose check silently skips a tier looks like it works;
  verify the final set with the real suite.

## Whole-game run, lighting and game-time audio (2026-10-30, lead)

* **Whole-game autorun passes** (ch01-ch65, `AUTORUN RESULT PASSED`, ~514 s of wall time, movies off, TEXT_ONLY) on the rebuilt engine
  with a private copy of the `grim_tools` autorun: `nav_setfile.lua` ends with `readfrom()` (not `readfrom(old)`: the set file stays
  open and the 128-slot ResFile table fills up, then the game asks for a CD), `ch36` also accepts being in Lola's set (no movie, the
  cutscene is over before the poll), `DATA006.LAB` in the data folder, and the re-entry threshold of the hallway walk of chapter 1
  at 1500 ms (1000 ms is missed by one frame: the walk is the same on ScummVM, which passes by one frame, the rebuilt engine by -1).
  Run it on a private hard-linked data folder with its own script file name (`dofile("autorun_all.lua")` finds the shared copy first).
* **Int/float casts of the converted functions** (`tools/build_src.py fix_casts`). Ghidra types a stack slot or parameter that the
  compiler reused for an int and a float as `float`; whether `(int)x` / `(float)i` is a value conversion or a bit copy depends on the
  function (FILD/FIST in the original: `int_float_conversions`). The rewrite is per cast, so a function with a FILD gets the read
  side as PUN (bits) and the write side as a value conversion: `rdLight_CalcVertexIntensities` (loop counter in a float slot) lit most
  vertices wrong (characters nearly black), `Actor_PuckOrient(float param_1)` (an actor pointer) crashed (original save grim21),
  `Lua_DispatchControlHandlers` and `Lua_GetActor*Chores` (object handles) crashed. The 12 functions that had both kinds of cast were put
  back to the original machine code (names/asm_exclude_exe_lo.json): rdCanvas_PreparePolygon, rdLight_CalcVertexIntensities,
  Actor_CreateSubtitle, Actor_UpdateMovement, Actor_PuckOrient, Lua_GetDiskFreeSpace, Lua_WorldToScreen, Lua_SetCameraFOV,
  Lua_GetActorChores, Lua_GetActorLoopingChores, Lua_DispatchControlHandlers, D3D_CreateViewport. `type_of` also knows that an
  import without a prototype is `extern int f()`.
  Check after any change of that rule: `build/perf/shot.py` of Manny's office (the mean brightness of Manny's region is ~44; it was 14
  with the bug) and original save grim21.
* **iMUSE in game time** (`GRIM_SIMTIME`, see the block in build/overrides.c). iMUSE was paced by the hardware: a WINMM timer thread
  calls ImHeartbeat every 20 ms of real time and a block of the DirectSound ring is refilled when the play cursor has left it, so a
  7 s sound lasted 7 s of real time = 700 s of game time at the ~100x of a scripted run, and the scripts that wait for the end of a
  sound timed out (ch64: the water tower, `me_tank3.wav`). With GRIM_SIMTIME set there is no timer thread, the play cursor is a byte
  counter advanced by game time, and the EXE calls `GRIM_ImSimStep(ms)` (exported by IMUSE.DLL) once per frame from
  `GRIM_lua_cmd_poll`: one ImHeartbeat per 20 ms of game time. The ring is still written (muted). The two loops that wait for the
  heartbeat tick it themselves. `me_tank3.wav` now ends after 410-412 frames (7.0 s of game time). The guard counter
  (Im_GuardEnter/Leave) was already atomic; the sound is not a race: it lasted a constant 6.8 s of real time (6 trials).

## Assembly to C, round 3 (2026-10-30/31: agents O and P, lead)

* Every `build/overrides_<topic>.c` is compiled and its functions replace the assembled ones (link.py, build_src.load_overrides);
  one file per work stream keeps parallel work conflict-free. Notes per stream: docs/notes/mixer.md (agent O: the whole
  0x4bdf00-0x4d4100 range, DirectSound/software mixer, Smush video and Blocky16 codec, AnimPlay, zlib glue; differential tests in
  build/mixdiff/, millions of random cases, 0 differences) and docs/notes/logic.md (agent P: game logic below 0x4a0000 outside the
  rasteriser, 0x4a0000-0x4bf000, six CHORE.DLL functions; differential harness build/difftest/logic_dt.c). What is still assembled
  and why: docs/ASM_REMAINING_mixer.md, docs/ASM_REMAINING_logic.md (EXE: 440 functions, of which the software rasteriser is ~395).
* A hand-written function is only recognised as an override if its definition line matches build_src.load_overrides' regex
  (return type on its own line is missed: add a `/* OVERRIDES: name */` line), otherwise the assembled copy is linked as well and
  `--allow-multiple-definition` silently picks it: the C was never run (found by agent P in Collision_BoxSlide).
* Two agents edit the same Ghidra project: when both retype one function the last write wins (TextObject_New is 4 parameters, the
  last two unused, since agent O; agent P's 2-parameter calls pass 0, 0). After merging agents, re-export with a clean raw/
  (`rm raw/<PROG>/functions/*.c` first: export_raw.py skips files that exist), regenerate, build.
* **IMUSE.DLL is C** (agent N, round 3): 4 of 243 functions stay assembled (three music state/sequence transitions that read
  arguments their callers never push, and the dead `_ftol`), 13 are hand-written in build/overrides_imuse.c. Notes and the
  per-function reasons: docs/notes/imuse.md, docs/ASM_REMAINING_imuse.md; the PCM oracle and differential tests: build/perf/imuse/.
  Root causes found on the way: four untyped pointer globals (Ghidra printed byte offsets, C scaled them by 4: the mixer accumulator
  was written 36 KB past its buffer: names/imuse_ptr_types.json, tools/type_pointer_globals.py), DirectSound COM calls and `hmiFX*`
  imports are __stdcall, address literals inside arithmetic need IMG_ADDR, lost `movsx` in Im_MixLoopC/D (negative samples twice as
  loud), lost x87 values in Im_MixerInit. The game-time iMUSE block (GRIM_SIMTIME) is unchanged: me_tank3.wav ends after 414 frames.

## Merge of rounds asm-p1 / asm-p2 (2026-11-09)

* `build/overrides_asm_p1.c` (13 functions, docs/notes/asm_p1.md) and `build/overrides_asm_p2.c` (7, docs/notes/asm_p2.md)
  merged; the 20 addresses are out of `names/asm_funcs.json` and their bodies out of `src/GRIMFANDANGO.EXE/asm_funcs.s`
  (taken out with `build/difftest/asm_p2/strip_asm.py`: the Ghidra bridge was not running, so `gen_asm.py` could not
  regenerate it). Assembled now: EXE 271 (243 of them the rasteriser), LUA.DLL 10, IMUSE.DLL 4, CHORE.DLL 0.
* Checks: libcheck all PASS; the office shot's Manny region has mean brightness 42.8; `oldsaves.py`: 76 of 76 original saves
  pass. grim33 crashed once (a null `%s` in the Lua function-description format `%s '%s' (%s:%d)` inside the C runtime's
  sprintf) and passed on the retry and in 8 more fresh games; it is not the LZSS crash above, cause unknown.
* The FUN_00410330 shot difference that asm-p1 reported does not reproduce on top of a09980a (docs/notes/asm_p1.md).
* `rm -rf src` before `build_src.py` deletes `asm_funcs.s`, which only `gen_asm.py` (Ghidra) writes; the instructions at the
  top of this file and in the README now delete only the generated `.c` / `.h` / `.md` files.


## Assembly to C, round q (2026-11-09: agents q1-q6, lead)

* Six work streams, one override file and one notes file each (docs/notes/asm_q1.md ... asm_q6.md), differential
  tests in build/difftest/asm_q1 ... asm_q6 against the original machine code sliced from the 2df265d assembly
  (1,000,000 cases per function, 0 differences, mutation checks). Every merge on main was checked with the clean-room
  tests (`grim_tools/cleanroom`, `run.py decomp`): 5107 of 5107 the same after each merge and at the end.
  * q1 / q2: rdClip_Line2D and the ten rdClip_Face3_* frustum clippers (one shared plane pass each file).
  * q3: rdPuppet_AdvanceTrack, rdPuppet_UpdateFrame, rdModel3_LoadEntryText (now `(char *path, char *model)`, what the
    caller passes; tested on the game's 10 text .3do files and mutations of them), rdCache_DrawMeshList3D.
  * q4 / q5 / q6: the whole software rasteriser, as macro templates per feature flag (long double for x87 values,
    volatile stores at the original's `fstp dword`, SSE4.1 `roundss` for the FLDCW floor/ceil conversions;
    overrides_asm_q4.c and q5 are compiled with `#pragma GCC optimize("O2")` + target sse4.1, q6 at -O0).
    q4: the z-buffered affine half (67, everything normal play calls); q5: the perspective half (108); q6: the
    non-z-buffered renderer, points and wireframe (67).
  * q6 also compiles the span section of overrides_asm_o2.c (rdRaster_Span16_TexLitZw*, the per-scanline fillers of
    the main textured drivers) at -O2 with volatile float stores at the original rounding points: bit-exact
    (23,000,000 cases; an in-game self-check of -O0 against -O2 over 34 million calls), libcheck 1.7 -> 1.0 ms/frame.
    Together with q4 (2.23 -> 2.13 ms/frame) the software renderer is faster than the assembled build was.
* Assembled now: EXE 14 (`_ftol`, `__chkstk`, the SEH filter / unwind funclets at 0x4d5e1c-0x4d6100 and
  FUN_0042003c, the dead loop tail of rdRaster_Span_Tex_5), LUA.DLL 10, IMUSE.DLL 4, CHORE.DLL 0 (from EXE 271).
* **peephole.py bug, fixed by the port:** the original perspective span fillers set the 24-bit truncating control word
  at their start, and their first float -> int conversion restores the default one; peephole.py removed those
  control-word loads, so until now the whole filler ran at 24 bits and the perspective divides differed from the
  original in the low bits. The C follows the original. build/difftest/asm_q5/peephole_fix.py is a fix for
  peephole.py itself; no assembled function needs it any more.
* Original behaviour kept (notes per stream): 1-pixel spans drawn with leftover register / global values, `colour << 8`
  table indexing in Span16_TexZ_5/_7 and Span16_Tex_13/_15. Not reproducible in C (the original reads stack slots it
  never wrote; game data never reaches them): rdModel3_LoadEntryText with material indices outside 0..0x7f,
  rdCache_DrawMeshList3D's mip level / first vertex colour in two odd modes, Grad_Flat_2 / SetupPolyTex when the
  vertex next to the top is the bottom.
* Merging: each stream removes lines from names/asm_funcs.json and bodies from asm_funcs.s, so parallel branches
  conflict there; resolve by taking main's file and applying the branch's removals
  (`build/difftest/asm_p2/strip_asm.py <asm_funcs.s> <asm_funcs.s> <names>` and dropping the addresses from the json).
* **Intermittent crash in the clean-room test save_load** (twice in about ten full runs, once under heavy machine
  load; the rerun of the same binaries passed both times, and `--only save_load` passes): an access violation in
  ResRef_Remove <- ModelComponent_Destroy <- Engine_LoadGame in one report, inside a system DLL under Surface_Unlock
  (load progress bar) in the other. The 84 "differences" of such a run are its after-effects (the run restarts at
  save_load without the earlier state). Not caused by this round's functions (none on either stack); cause unknown.

## LUA.DLL VM core in C (2026-11-09, lead)

* lua_updatetasks, luaD_protectedrun, luaD_protectedparser are C (build/overrides_lua_core.c, docs/notes/lua_core.md):
  the same `_setjmp3(buf, 0)` / msvcrt `longjmp` as the original, volatile locals across the longjmp. Differential test
  build/difftest/lua_core (1,000,000 random scheduler / protected-call cases with nested calls and raised errors,
  0 differences; 12 of 12 mutations caught); clean-room tests 5107 of 5107. Assembled now: LUA.DLL 7 (the C++ unwind
  funclets), EXE 14, IMUSE.DLL 4, CHORE.DLL 0.

## No assembly left (2026-11-09, round r: agents r1 / r2, lead)

* names/asm_funcs.json is empty for all four programs; every function is C (or, for dead code and runtime helpers,
  the host runtime / a trap stub). Clean-room tests 5107 of 5107 on the merged tree.
* r2 (docs/notes/r2.md): EXE `_ftol` -> msvcrt.dll's `_ftol` (names/lib_replace.json "host"; no caller left, compiled C
  uses FTOL()), `__chkstk` -> libgcc `___chkstk` (build/overrides_r2.c); the 11 EXE and 7 LUA.DLL exception funclets
  and FUN_0042003c are dead (only named by scope tables / FuncInfo records no rebuilt code installs; no C++ throw in
  either binary): lib_replace "dead", proved with trap stubs under the clean-room suite. ObjectState_Construct still
  registers an fs:[0] frame (the seh_strip rule of build_src.py misses it: its locals are frame_locals #defines); its
  handler is now one that returns ExceptionContinueSearch. Open: fix the strip rule itself.
* r2 also found false relocations in the data image: gendata relocated values that only look like addresses (the
  VIMA/IMA ADPCM step table at 0x4daa58 used by the Smush audio decoder held relocated addresses in entries 22-31; font
  glyph bits of Text_WrapLines; runtime / deflate tables) and missed 4 real pointers. names/data_relocs.json corrects
  the EXE against the original .reloc table (build/difftest/r2/relocheck.py). Movie sound was not re-measured.
  IMUSE.DLL has one more false pointer (0x100153c4), not fixed.
* r1 (docs/notes/imuse_r1.md): FUN_10006560 / FUN_10006620 / FUN_100068b0 are C. The "parameters 4..8" Ghidra showed
  are the function's own argument slots reused after MSVC's late pops; the stack garbage is ImSetTrigger's 13th word,
  which the C now passes as the original's value (the caller's ESI or a fixed return address). Only transition types
  4, 6, 9-12 reach it and the shipped tables have none. hmi__bae0 (_ftol) dropped as dead. Seen on the way, already
  in 85dd22f and not followed up: after ImSetState(1000) and 250 frames the original still finds the fading stream at
  ImSetState(1001), the rebuilt DLL starts it again (docs/notes/imuse_r1.md).

## Round s: open problems after the last assembly (2026-11-09, agents s1-s3, lead)

* **The intermittent save_load crash is fixed** (s1, docs/notes/s1.md, build/overrides_s1_chore.c). A latent bug of
  the original CHORE.DLL: the costume and instance slot allocators (FUN_10004e50, FUN_10005090) mark the records of a
  grown table free from the "in use" count, not from the old size, and Cos_Load does not lower that count when a load
  fails. After the suite's `LoadCostume("no_such.cos")` the 33rd costume grows the table 32 -> 40 with used = 33, so
  record 32 keeps the bytes of the reallocated heap block; when they read as "in use", Cos_Restore (first Load())
  frees a costume of garbage: ResRef_Remove(NULL), or heap corruption seen later under the progress bar. The bytes
  depend on the heap and the other threads, hence intermittent and more frequent under load. The C marks from the old
  size and grows in steps of 8 until the record fits (the original grows once and would write past the end after more
  than 8 failed loads); handles, counts and realloc sizes are the original's. Before: 7 crashes in 16 harness runs;
  after: 0 in 32, and 12 full clean-room runs in a row (8 of them under extra load), 5107 of 5107 each.
  This is a deliberate difference from the original (the original has the bug; its heap usually hands back zeroed or
  harmless bytes there).
* Not this bug, still open: one boot crashed in the splash screen (Mem_Copy <- Surface_BlitSoftware <-
  Grim_ShowSplash) while the clean-room suite ran (s2); seen once.
* iMUSE (s2, docs/notes/s2.md): the scenario-3 "fade" difference of round r is the time base of the test (the rebuilt DLL
  heartbeats on game time under GRIM_SIMTIME, the original DLL has no GRIM_ImSimStep and stays on its real-time timer);
  on the same time base both give identical calls. The fade code is the original's (1,000,000 differential cases).
  IMUSE.DLL's false pointer 0x100153c4 (printf class table) is in names/data_relocs.json; relocheck: IMUSE.DLL and
  CHORE.DLL 0 false / 0 missed, LUA.DLL 0 false and 68 "missed" that are jump-table entries of dead runtime code.
  Note: C:\GOG Games\GRIMDATA\IMUSE.DLL is a patched copy (Im_GuardEnter/Leave made atomic, one extra .reloc entry);
  IMUSE.DLL.unpatched beside it is the shipped file and matches raw/IMUSE.DLL.
* SEH (s3, docs/notes/s3.md): the seh_strip rule of build_src.py now handles the CONCAT31 / `_0_1_` state stores and
  handler / state stores on both sides of the fs:[0] registration; no rebuilt function touches fs:[0] or references an
  exception handler any more (build/difftest/s3/seh_scan.py: 47 instructions at 6da2d60, 0 now). The
  __CxxFrameHandler thunks are lib_replace "dead"; r2's ExceptionContinueSearch handler is gone.
* **Movie sound was broken before 6da2d60** (s3): with the relocated VIMA step table entries 22-31 the Smush audio
  decoder produced wrong samples in every loud passage (7 of 8 tested movies: 4.7-25% of samples wrong, about half
  clipped at +-32767; intro +8.5 dB error over signal). Since 6da2d60 all 8 movies decode identically to the original
  exe (build/difftest/s3/vimadiff.c loads the original or rebuilt exe in a suspended child and feeds the Wave chunks).
* build/link.py: a program whose file does not compile is reported as "NOT linked" and `make link` fails (it used to
  return 0 and keep the previous binary).

## Whole-game autorun again, shutdown crash (2026-11-09, lead)

* Whole-game autorun on 045e8bd (private copies in C:\Users\Joel\grimW_*, commands in grimW_work: `sh wg_start.sh &&
  sh wg_watch.sh`, one chapter from its checkpoint `sh wr_resume.sh <slot> <tag>`): ch01-ch53 pass, **ch54 fails**
  (`AUTORUN FAIL nav: no way from 0.78 -0.35 to -0.24 -0.07 in sewer hub for 18 seconds`). **Not the engine** (agent t1,
  docs/notes/t1.md): from the same checkpoint the ORIGINAL 1.01 exe walks Manny through the same 310 (x, y, yaw) states
  to 4 decimals, stops at the same points and fails with the same message. It is autorun drift: ar_nav_door_hot lists
  every hot sector of the door object, sh.lua maps both ladderup_box and ladderdn_box (the top of the ladder, z 2.95)
  to sh.te_ladder, and ar_w_in_goal_hot is 2-D, so the walk ends in ladderdn_box's floor footprint 0.11 m short of
  ladderup_box and the climb never starts. Fixed in grim_tools abc5620 (ar_w_in_goal_hot checks the height of Manny's
  real position with ar_w_hot_zok); with it the rebuilt engine (da70a81 binaries) plays ch54 from its checkpoint
  through ch65: `AUTORUN RESULT PASSED`, no crash on exit. So the whole game passes again (ch01-ch53 in the full run,
  ch54-ch65 from grim54.gsv). Also found: the install's GRIMFANDANGO.exe is
  gfupd/v101_clean.exe (no grimdlg.dll: no log, no F12), so resume_original.sh runs an original that never logs; t1's
  working recipe (grimlaunch.exe with its own patch.dll, CRLF grimrun.lua) is in docs/notes/t1.md.
* Seen once: access violation in Render_BuildActorDrawList (`fsubs (%eax)`, eax = g_pCameraSetup) on the first frame
  after the switch to "temple back stairs" in ch49: a stale camera setup pointer across a set switch. Not reproduced.
* **Every exit of the rebuilt game crashed** (fixed in da70a81): CHORE.DLL's hand-written FUN_10004970 had turned
  IMUSE.DLL's unrelated FUN_10004970 (same name: the DLLs share the image base) into a trap stub, and iMUSE's shutdown
  calls it. That is the c000001d in imuse.dll of the autorun's ca8eb27 attempt and the 0xC000041D exit code of every
  clean-room run; clean-room runs now exit with 0. build_src.load_overrides() is per program now.
* Seen once in the clean-room suite: access violation in Lua_GetCameraLookVector (test args_GetCameraLookVector_num).
  With a number argument it reads setup[n] (n * 300 bytes into the set's setup array) without a bounds check, so a set
  with one setup is read past its end; the original does the same and survives because its heap leaves readable memory
  there. Heap-layout dependent, like the CHORE.DLL slot bug; reruns passed.

## CHORE.DLL named, EXE caught up with the Ghidra project (2026-11-10, agent chore-naming, lead)

* CHORE.DLL: 67 -> 112 named; the 152 `FUN_` left are exactly the dead MSVC runtime copies of names/lib_replace.json.
  The remaster's `libchore.so` is not stripped and gives the original static and global names; field names come from
  the asserts. Batches names/chore_{functions,globals,types,comments}.json; Costume / CosComponent / Chore / ChoreTrack /
  ChoreKey / CosInstance / ChoreInstance / ComponentTag / CosStateBitmap in Ghidra and build/compat.h (size asserts).
  Private runtime copies are `msvc_<name>` so build_src does not drop them into crt.c and the exported symbols do not
  capture the EXE's own qsort / _stricmp. Details: docs/notes/chore_naming.md.
* **Locking a prototype can silently break the callers' decompilation**: Ghidra then trusts the callee's stored stack
  purge, which was wrong (4 / 16 bytes) for Cos_AddKey, CosUtil_PtrFromHandle, Cos_HandleToIndex and
  Cos_InstIndexToHandle (all `__cdecl` with a plain RET), so callers read their parameters at the wrong offset
  (`in_stack_`, and one silent swap in Cos_InstRescue). First clean-room run of the typed build: 321 differ. The 11
  affected functions are hand-written in build/overrides_chore_naming.c (main's checked bodies, new names); they can go
  once `setStackPurgeSize(0)` is run on those callees (no bridge endpoint for it). After any prototype batch, look for
  new `in_stack_` / changed parameter uses in the callers.
* tools/ghidra_api.py: writes put `program` in the query string; the bridge ignored it in the JSON body and wrote to
  its current program (the EXE). `ok()` now sees plain-text "Failed ..." answers.
* The Ghidra EXE had 34 renames made outside any batch and never exported (original-style names: `sputLua_*`,
  `*Requester`, `KeyframeAdjuster`, `stdLbm_Write`, and corrections: Vec3_Sub -> Matrix34_TransformPoint (it is a
  3x4 matrix times point), Matrix_Transpose -> Matrix34_InvertRigid, rdKeyframe_InterpolateNode ->
  rdLight_CalcFaceIntensity) plus pending edits (Display_OpenMode, D3D_SelectDriver). The EXE src is regenerated from
  the project; the old names are replaced in build/overrides*.c, the names/exe_*.json batches (so re-applying them does
  not undo the renames), tools and docs; build_src.PREFIX_MAP keeps Matrix34_* in math3d.c and the costume tag handlers
  in their component files.
* Clean-room (`run.py decomp`): 5118 of 5118 the same (the suite has 5118 tests now).

## Original names from the remaster's Linux build (2026-11-10, agent orig-names, lead)

* The remaster's `GrimFandango` (9428 symbols, iMUSE linked in) and `libLua.so` (797) are not stripped; both are in
  the Ghidra project under /linux. 625 functions renamed to their original names: LUA.DLL 158, EXE 455 (265 Lua
  bindings matched through the registration tables, `Lua_X` -> `sputLua_XL` etc.; 190 engine / LEC library), IMUSE 12.
  477 of them replace existing names (several were wrong: `luaU_str2number` is luaV_tonumber, `luaV_execute` is
  ExecutionState_CrunchOpcodes, luaT_realtag / luaT_checktag were swapped); each plate comment keeps "was X" and the
  evidence, each batch entry an "old" field. Batches names/orig_{lua,exe_lua,exe_engine,imuse}.json; matcher
  tools/orig_dump.py / orig_match.py / orig_batch.py; tools/rename_refs.py carries a rename into the hand-written code
  (overrides, build/cleanroom, the other batches, tools, docs; respects the #ifdef GRIM_* guards).
* names/orig_modules.json pins renamed functions to their old module file (build_src reads it before PREFIX_MAP).
  build_src.fix_stdcall no longer edits a plate comment that contains `Name (`.
* Names and comments only (no prototypes). Regenerated src is the old src after the renames; stubs unchanged (EXE 42,
  LUA 58, IMUSE 9, CHORE 16). Clean-room 5118 of 5118 the same.
* Left: globals (the remaster names them: pLuaHS, LState::refArray, ...), the 351 generated rdRaster_* names, most iMUSE
  internals (92 pair up), ~29 doubtful candidates (docs/notes/orig_names.md), build/difftest harnesses still use old
  names.

## Original names for globals (2026-11-10, agent orig-globals, lead)

* Globals named after the remaster's data symbols (`g_` + the bridge's Hungarian prefix + original name, e.g.
  `g_dwLState_refArray`, `g_pRdroid_HS`): EXE 271 -> 463 of 2274, LUA.DLL 11 -> 69 of 367, IMUSE.DLL 0 -> 51 of 366
  (counted over src/<prog>/globals.h without strings / labels). 87 earlier EXE `g_` guesses replaced. Matched by
  token-aligning each paired function's decompilation with the remaster's (string literals as anchors). Batches
  names/orig_{lua,exe,imuse}_globals*.json (tools/orig_gbatch.py). Names and comments only, no types.
* The globals settled 29 more function names (names/orig_exe_leftovers.json, orig_imuse_leftovers.json), e.g. the
  SmushPlay module interface (the old SmushPlay_SysShutdown was the terminate slot), LecShare_* shifted by one,
  SoundModule_Open -> engine_Initialize, Display_SetPalette3D -> std3D_SetCurrentPalette.
* tools/build_src.py: a renamed global whose Ghidra type is still its "oldtype" is generated as before (declaration,
  inferred DAT_ type, fix-ups) and only the name changes in the output; retype it in Ghidra and it is taken as named.
  tools/rename_refs.py carries global renames (`_X`, `X_2`, asm labels) and finds the owners of shared DAT_1000xxxx
  names from each program's data. Bridge quirks: `dry_run` and `strict_mode` are read only from the query string (a
  "dry" rename in the JSON body is real); `rename_or_label` on a no-data label adds a second label (apply_names uses
  rename_label now).
* Regenerated src equals the previous src after the renames; stubs unchanged. Clean-room: 5167 of 5167 the same (the
  suite has 5167 tests now).
* Left: struct-field globals (`aView`+n, ...), the rdRaster_* names, most iMUSE internals (94 pair), build/difftest.

## Original names, round 3 (2026-11-10, agent orig-3, lead)

* EXE functions 2338 -> 2344 named (325 renames, 319 replace hand-made names: module slots `sputX_Start`/`_Stop` ->
  `_Startup`/`_Shutdown`, the Jedi libraries `Matrix_*`/`Vec3_*` -> `rdMatrix_*`/`rdVector_*`, `Surface_*` ->
  `stdDisplay_VBuffer*`, `rdCanvas_*` -> `rdActive_*`, `D3D_*` -> `std3D_*`, `Reg_*` -> `wuRegistry_*`; some were wrong:
  `Math_SinDeg` is stdMath_Tan, `Vec3_Copy` rdMatrix_TransformVector34), globals 463 -> 590. IMUSE.DLL functions
  293 -> 301 (60 hand-made names replaced, `Im_DispatchCommand` -> ImSoundCall, ...), globals 51 -> 92. LUA.DLL: 63 -> 8
  generated `l<module>__<addr>` names (Lua 3.1 source names for what gcc inlined; luaY_error / luaY_syntaxerror /
  close_func and luaF_freeproto / luaF_freeclosure / freefunc were swapped). Batches names/orig3_*.json.
* build/difftest carries the renames of all three rounds (tools/orig_history.py: earliest -> current name per
  address); asm_p1, clipface and lua_core harnesses build and run again (0 differences). asm_s5 / big_* slice from the
  now empty asm_funcs.s and s1 needs the pre-naming CHORE globals: broken on main too, not by the names.
* Code, data and rdata of the four binaries are byte-identical to main's (only build time, export tables and import
  hints differ). Clean-room: the suite grew to 5319 tests from another session's uncommitted grim_tools expected/
  files; 2 of the new tests (gco_kf_badj, ims_ids|id_plus_1) differ for main's build and this one alike.
* Left: rdRaster_* (the remaster's rdNRaster_* / rdZRaster_* pair 86 of them at 0.45-0.85 similarity: not done), LUA.DLL
  globals beyond the 69, the doubtful list in docs/notes/orig_3.md.

## Original names, round 4 (2026-11-10, agent orig-4, lead)

* The software rasteriser: the three dispatchers (rdCache_DrawFaceN, rdCache_DrawFaceZ, rdActive_AddActiveFace) test
  geometry / lighting / texture mode, the mask bit and the translucency bit in the same order in both builds, so each
  v1.01 call pairs with the remaster's call under the same conditions (32 + 32 DrawNGon*, 16 rdAFRaster_SetupNGon*);
  their callees pair by role (gradients, left / right edge set-up, 8 / 16-bit span, advance by side flag). 260 of the
  351 generated `rdRaster_*` names and 15 FUN_ are original now; orig-3's similarity votes had crossed pairs
  (`rdRaster_Draw16_TexLit_4` is DrawNGonLAT, not TLAT). Left: 86 per-texture-width span fillers only v1.01 has, 2
  z-write spans the remaster inlined, 3 copies the linker folded.
* EXE functions 2344 -> 2359 named, auto/module-level 378 -> 119, 59 hand-made names replaced (`rdroid_Open` -> rdOpen,
  `Grim_Init` -> Main_Startup, `IMuseModule_Init` -> PolyglotInitialize, `Display_Flip` -> stdDisplay_Update,
  `DebugLog_*` -> grimdemo_*Print, ...); globals 590 -> 727 (36 renamed, the rdRaster vertex globals -> rdNRaster's).
  IMUSE.DLL: `Im_FireTriggers` -> TgProcessMarker, globals 92 -> 100, 10031e78 / 10031e7c corrected to lipSfx2ID /
  lipSfx3ID; its 150 FUN_ are 124 MSVC runtime + 26 iMUSE code nobody pairs. LUA.DLL: nothing new (the unnamed globals
  are runtime-only, literals taken by address, LState pieces). Batches names/orig4_*.json, notes docs/notes/orig_4.md.
* asm_q4 / q5 / q6 pasted `rdRaster_##n`: their *_funcs.h now list the full names. The lead carried the renames into
  build/difftest/logic_dt.c (`__orig`), build/mixdiff/snd_test.c and build/perf (breakpoints by name).
* Code and data of the four binaries are byte-identical to main's (rdata: the build-time string only).
* Clean-room (5319 tests, the other session's uncommitted expected/ files): 10 differ for this build and 10 for main's
  (built in a worktree from main with raw/ mapped back to the old names; code and data byte-identical to this one). 9
  differ identically in both (gco_kf_badj, gco_cos_bitmap, gco_font_kerned, gco_font_perm, gco_text_keys,
  gl1_sound_pos_actor, gl1_sound_pos_max_below_min, ims_save_voice, smv_save_movie: the new / changing tests); the
  rest is timing noise one run each (sound_fade on main, ims_ids|id_plus_1 here, as in round 3).

## Original names, round 5 (2026-11-10, agent orig-5, lead)

* The LEC library registers its service tables under the same strings in both builds ("LECMODULE=insane_x",
  "ANIMPLAY=insane", ...): read from both binaries, they pair slot by slot, and so do the tables reached through
  matched globals (shl_modules, lecShareServices, defaultHostServices, sputVideoCallBacks, the resource type table by
  its four-letter tags). Callee / caller propagation and five more alignment passes did the rest; every pair was read
  in both texts.
* EXE functions 2359 -> 2462 named (FUN_ 312 -> 209; 212 renames, 109 replace hand-made names: `InsaneTimer_*` ->
  `sys_*`, `SoundModule_*` -> `sou_engine_*`, `DsndDriver_*` -> `dsn_*`, `Svc_*` -> `default*`, `Rle_*` ->
  `msc_rle_*`, `Blocky16_*` -> `fob_*` / `flobdec_*`, `LecShare_Register` / `_Unregister` / `_Release` ->
  `LecShare_Publish` / `_Unpublish` / `_Unsubscribe`), globals 727 -> 764. IMUSE.DLL 301 -> 302. Batches
  names/orig5_*.json, notes docs/notes/orig_5.md.
* The doubtful list: settled `Resource_OpenArchivesInDir` (AddResourcePath, with Res_FileOpen / Res_FileMoveToFront),
  `Actor_DrawShadowPlane` (sputCostume_DrawMeshShadow), `SetFile_ParseSectors` (ParseCollection), `rdThing_DrawAlt`
  (rdThing_Draw; the old rdThing_Draw is rdModel3_Draw), `rdModel3_New` (rdModel3_Load; the old one is
  rdModel3_LoadEntry), `Im_VimaDecompress` (AudioLib_ParseWaveFileHeader: a wave header parser), and an orig-names
  mistake (0x4a49a0 is sputRoom_LoadRoom, 0x4a4b00 SetFile_Parse again). Kept, with reasons in the notes: Win_WinMain,
  Display_Select, Lab_ReadDirectory, LightEd_*, Collision_TestActorAgainstOthers, LecShare_Reset, the dirty-rect
  statics, loadLastSave, mlListSize.
* What is left is mostly not nameable from the remaster: the EXE's 209 FUN_ are 187 C runtime / zlib (144 of them dead
  copies) or folded copies and 22 LEC / game code with no remaster symbol; the generated names are v1.01-only spans,
  Grim's own Lua undump checks and helpers the remaster inlined; of the 1510 unnamed EXE globals ~716 look like real
  statics, mostly of v1.01-only code. The remaster's ELFs have only .symtab (no DWARF): object sizes and C++ parameter
  types of 2053 + 137 functions, no struct layouts or field names.
* rename_refs covers neither build/mixdiff nor build/perf; the agent carried the names there too and a repo-wide scan
  finds no old name. Code and data of the four binaries are byte-identical to main's (rdata: the build time).
* Clean-room (5322 tests, the other session's uncommitted expected/ files): this build 7 differ, main's 6, compare of
  the two logs 1 (ims_cache|keep_after "1" for main, "0" here). Run alone (`--only ims_cache`, three times each) both
  builds give "0": a timing-dependent new test, not the names. The others are the other session's new tests and
  sound_fade timing noise, the same for both builds.

## Original names, round 6 (2026-11-11, agent orig-6, lead)

* Hand-made names replaced where the remaster has a symbol: EXE 593 -> 402 hand-made (194 renames: 191 hand-made, 2
  FUN_, and a correction: 0x473630 `stdBitmap_Load` is stdLoadImage, the remaster's stdBitmap_Load is 0x47aa50). From
  a call-sequence alignment and the remaster's C++ classes (methods in the same file order as v1.01): WalkPlane_* x23,
  Puck_* x9, the path planner (BuildPath, Planner_FindPath, FindExitPoints, TightenPath), PrimitiveQueue_* x21,
  ObjectState* x15, the Main_Shutdown chain, stdFile* x11, stdGif / stdBitmap / stdPlatform / stdMath, the rdroid
  setters; in the LEC library the mixer (sou_mixer_*, dsn_fill_thread), the video converters (gra_*), blocky16 and the
  timer. EXE globals 764 -> 775 (+10 hand-made g_ names replaced). IMUSE.DLL: iRes_FTELL / iRes_FSEEK, iMUSE_Malloc /
  iMUSE_Free, mlEntries / mlEntryCount / mlListSize (settles the contested one). LUA.DLL: lgc.c's markall, globalmark,
  travlock, strmark. Batches names/orig6_*.json, notes docs/notes/orig_6.md.
* `Video_CopyRectDstFirst` stays (it is gra_CopyRect): with the shorter name the generated call lost its `(code *)`
  cast and .text changed.
* Left: 402 EXE hand-made names (131 platform layer, 176 helpers the remaster inlined, 61 LEC helpers, 24 light editor,
  10 import thunks); IMUSE.DLL 29 hand-made, 14 generated, 23 FUN_; LUA.DLL 65 hand-made, 56 of them Lua-3.1-style
  names that the Lua 3.1 sources could still check.
* The agent's commit carried 18 build outputs of build/mixdiff/out (executables, objects); the lead dropped them from
  the commit and ignores the folder. Code and data of the four binaries are byte-identical to main's (rdata: the build
  time).
* Clean-room (5322 tests, the other session's uncommitted expected/ files): 6 differ for this build and 6 for main's
  (run right after); compare of the two logs: 0 of 5324 differ.

## Original names, round 7 (2026-11-11, agent orig-7, lead)

* LUA.DLL: 52 hand-made names replaced by Lua 3.1 source names (lapi, lbuffer, ldo, liolib, lstring, lstrlib,
  lua.stx, ltable, ltm, lundump, lvm), several of them wrong before (`str_matchbalance` is matchitem, `str_expand`
  matchbalance, `luaT_gettm` validevent, `luaU_LoadCode` LoadSize, `lua_ioregister` openwithtags); hand-made 65 -> 13
  (runtime and thunks, luaM_malloc / luaM_free, luaU_LoadNumber). Globals 69 -> 73 (validevents, iolibtag,
  checkcond::opts, opcodeDirectory). No Lua 3.1 source is on the machine: the names were checked against libLua.so
  and ScummVM's port of Grim's Lua (names only).
* IMUSE.DLL: UtReadLongHilo, UtCheckHook, StViewData, ConvertMap, ihost_close_sound, and `Im_DecodeSoundBlock` is
  AudioLib_CreateWaveFileHeader (it builds the header). EXE: no pairs for the light editor (the remaster registers its
  Lua functions as DoNothing) or the LEC leftovers.
* docs/notes/orig_summary.md sums up the seven rounds: per program what has an original name, what is hand-made /
  FUN_ / generated, and why the rest stays (platform layer, inlined helpers, v1.01-only code, runtime).
* build/perf/imuse/imuse_diff_codec.c looks a function up by export name; like the earlier renames there it needs an
  imuse_a.dll assembled with the current names. Code and data of the four binaries are byte-identical to main's.
* Clean-room (5322 tests): 5 differ for this build, 7 for main's (run right after); compare of the two logs: 2
  (sound_fade, ims_cache: ids -225 vs 31, keep_after). Run alone three times per build, both give the same values
  (sound_fade "120 67" every time, keep_after flipping alike, ids as the reference): timing, not the names.

## The data as C, no raw/ at build time (2026-11-12)

* `build/gendata.py` and `obj/<prog>/data.s` are gone. `tools/datagen.py` (called by `tools/build_src.py`) writes
  `src/<prog>/data.c`: one C definition per span of the original's `.rdata` / `.data`, in the original layout (section
  keys `.data$grim_<address>` sorted by the i686 ld script, `no_reorder` within a 4-aligned run, an empty 16-aligned
  anchor first). Pointers are `&span + offset` or a function, by gendata's old rules. The 710 `IMG_ADDR` uses of the
  generated code name the span at their address; the overrides keep `IMG_ADDR` through `sect_rdata` / `sect_data`,
  now labels on the first span. The code-section copies are dropped; the EXE keeps the DirectInput data formats from
  it.
* `link.py` reads no raw/ file: the stub report takes `src/<prog>/imports.h`, the DLLs' exported variables come from
  `src/<DLL>/exports.json`, and its own definitions go to `obj/<prog>/link_data.c`. (It built the HMI import libraries
  with the i686 `dlltool`, inside `build/hmi`; those are gone since, see the next section.)
* `build/datacmp.py` checks the data of two builds span by span (bytes, pointer targets, offsets): against the data.s
  build, no difference in any of the four programs. `.github/workflows/build.yml` builds from a plain checkout.
* Details and numbers: docs/notes/raw_free_build.md. Clean-room against grim_tools' knowngood (with run.py decomp): 3 of 5167 differ for
  this build and for main's (lab_files, lab_dofile, lab_costume); the logs differ only in sound_fade's timing.

## The HMI effects library in C, no original DLL at run time (2026-11-12)

* `build/overrides_hmifx.c` is what IMUSE.DLL imported from HMI's `HMIFXLIB.DLL`, plus the three effects of
  `HMIFXFP.DLL` that `IMUSE.PSL` names (Reverb 1 = 2101, Filter 1 = 2300, Phasor = 2375). Decompiled with a headless
  Ghidra in a scratch project (not the shared one) and checked against the x87 instruction order: `long double` where
  the original keeps a value on the FPU stack, `float` where it stores one, `fptan` / `fcos` / `fyl2x` / `fistp` as
  the instructions, MSVC's `__ftol` as a truncating 64-bit conversion. The structures keep their offsets (IMUSE.DLL
  reads a preset's effect list at +0x450 and an effect's routing / link at +0x0c / +0x18 itself). The presets come
  from `IMUSE.PSL` in the working directory, a data file of the install, as for the original; nothing of it is built
  in. Without it `hmiFXPresetLoadLibrary` returns the DLL's error 10 (no library), IMUSE.DLL keeps a NULL
  library, and the first `ImSetVoiceEffect` crashes in `hmiFXPresetProcess`, as the original does (HMI's DLL faults on
  the NULL library too). `tools/hmifx_check.c` compares the failed load with the DLL. The clean-room suite writes its
  own `IMUSE.PSL` (one preset of its own, grim_tools `assets.PRESET_LIBRARY`) for every engine. `HMILIBS.INI` is not needed (it only named
  `HMIFXFP.DLL`).
* The game itself uses one preset: `ImSetVoiceEffect("Intercom Filter")` in the sets cf and nq (and in `_options`),
  a band-pass at 1326 Hz, 2000 Hz wide. The two reverbs and "Stereo Ring Modulator" are defined but no script calls
  them. Left out: the other six effects of HMIFXFP.DLL, 8-bit samples, the parameter getters and the fifteen exports
  IMUSE.DLL does not import.
* A side effect kept: loading `HMIFXFP.DLL` (in `hmiFXInitSystem`, freed again by `hmiFXUnInitSystem`) sets the x87
  precision to 53 bits through its C runtime start-up, other control-word bits unchanged (measured: 0x007f -> 0x027f,
  0x0c7f -> 0x0e7f). `hmiFX_InitSystem` does the same.
* `hmiFXMalloc` / `hmiFXFree` are cdecl (IMUSE.DLL pops the argument after the call); `tools/build_src.py` had declared
  all `hmiFX*` imports stdcall, harmless only because the callers have frame pointers. Fixed (`HMI_CDECL`); the other
  seven are stdcall.
* `build/link.py` no longer builds or links HMI import libraries; `build/hmi/` and `tools/gen_hmi_libs.py` are gone.
  The rebuilt `imuse.dll` imports ADVAPI32, KERNEL32, msvcrt and WINMM only. No file of the original install is loaded
  at run time any more besides the game data (`NULLMUSE.DLL` and `grimdlg.dll` were never loaded by the rebuilt exe).
* Checks:
  * `tools/hmifx_check.c` runs both libraries side by side the way IMUSE.DLL does (find, lock, blocks with flags 0x19,
    the last with its tail 0x9d; and unlocked, flags 0x1e), every preset of IMUSE.PSL plus a test file with the other
    filter types, a stereo reverb, a pre-delay and chains of two effects, three signals, x87 precision 24 / 53 / 64
    bits: 234 cases, all identical byte for byte, the control word after init included. Ours also from its built-in
    IMUSE.PSL.
  * In the game (`build/perf/imuse/fxtrace.py`, `scn_fx.lua`): the CRC of every `Im_ApplyFXPreset` output while
    Glottis' lines play through Intercom Filter, Basic Reverb, Stereo Ring Modulator and OFF: the build with the real
    DLLs and this one give the same 7028 outputs in the same order.
  * Data: `datacmp.py` against the previous build, no difference. EXE / LUA / CHORE only grow by the compiler ident of
    one more (empty) object.
  * Clean-room against grim_tools' knowngood, in a run folder whose `HMIFXLIB.DLL`, `HMIFXFP.DLL`, `HMILIBS.INI`,
    `NULLMUSE.DLL` and `grimdlg.dll` were empty files: 3 of 5167 differ (lab_files, lab_dofile, lab_costume, as
    before); against the previous build's log only sound_fade's timing.
* A trap for the gdb tools: `break <function>` stops after the prologue, so `[esp]` is not the return address there.
  A first version of the trace set a breakpoint on such a stale stack word, which was the address of the voice's MCMP
  handle; the `int3` byte then overwrote the handle's file number and `Res_FSeek` asserted. It looked like a crash of
  the voice-effect path in every build; read the frame through `ebp` instead.

## The C runtime out of the source (2026-11-12)

What the four programs still used of the original's C runtime, from `tools/lib_audit.py` on the linked programs (the
DLLs with only their original exports as roots, since the rebuilt ones export everything) and a link map:
* EXE: seven drive / directory functions the LEC file layer calls (`fle_Rename`, `fle_Remove`, `fle_DirectoryGetCWD`
  and the drive helpers): `_getdrive` (0x4d56f0), `_chdrive` (0x4d5740), `rename` (0x4d57c0), `remove` (0x4d5800),
  `_getcwd` (0x4d5830) and, behind it, `_getdcwd` (0x4d5860) and `_validdrive` (0x4d5990); and `strpbrk_or_strspn`
  (0x4ae220), which is `strspn` (it counts the leading characters that are in the set), called by the tree-select
  dialog. All are host now (`names/lib_replace.json` aliases), `_getdcwd` / `_validdrive` dead.
* LUA.DLL: the lexer's four ctype wrappers (0x1000f5c0..0x1000f650, `_isctype` with the locale check), kept.
* CHORE.DLL: `qsort` (msvcrt's orders equal keys differently), kept; `msvc_fpmath`, `msvc_fpclear`,
  `msvc_cfltcvt_init`, which its runtime's `_cinit` table points at, kept so that no pointer of the data becomes a stub.
* IMUSE.DLL: nothing (aliases to msvcrt, `heap_alloc` hand-written).
Also dead and now in the list: LUA.DLL's locale / start-up helpers (`GetLcidFrom*`, `getSystemCP`, `setSBCS`,
`setSBUpLow`, `parse_cmdline`, `tmpnam_genfname`, `TranslateName`), IMUSE.DLL's 0x1000c130, CHORE.DLL's
`msvc_CPtoLCID`. Two the audit called unlinked are live (it matches names, and these are only called by name):
`strpbrk_or_strspn` and LUA's 0x1000f5c0; the stub list caught both.

`tools/build_src.py` no longer writes the C of a function `names/lib_replace.json` takes out (dead runtime, host
runtime, zlib 1.1.3) or of the `crt` module, which `build/link.py` never linked: only the function's header and a
one-line note. A hand-written replacement of such a function leaves the same kind of note. `src/` loses about 52,000
lines (EXE 159.7 -> 140.4 K, LUA 32.8 -> 15.8 K, IMUSE 19.2 -> 10.9 K, CHORE 12.9 -> 5.2 K).

The dropped code addressed data by number (`IMG_ADDR`): those addresses start spans of `data.c`. `build_src.py` now
hands them to `datagen.generate`, which keeps starting spans there and declares them in `globals.h` as before, so
`data.c`, `globals.h`, `datacmp.py` and `data_unused.py` see the same spans as without the change. (A first run
without that merged spans and undid two entries of `names/data_unused.json`, which the stub list showed:
IMUSE.DLL's `FUN_1000d130` came back through a pointer in `DAT_10017000`.)

Checks: `data.c` and `globals.h` are as on main. `datacmp.py` against main's build: 0 differences, 0 moved, 0 missing,
every unused span zero. Stubs: no new one; LUA.DLL 41 -> 35 (functions only the dropped code called). Clean-room against
grim_tools' knowngood (no install file in the run folder, the suite's own `IMUSE.PSL`): the same 3 of 5167 differ from
the reference as before (`lab_files`, `lab_dofile`, `lab_costume`), 0 of 5167 from the previous build's log.

## Clean room on grim_tools main, the menu, the whole game (2026-11-13)

* grim_tools' main records the original with movies and sound on game time and runs four games at once. Against it:
  movies on game time under GRIM_SIMTIME (overrides_mixer_drv.c, grimlaunch's smushtime), iMUSE's timeGetTime on game
  time (cleanroom.c), the window device's mode matched after selecting the device (Display_InitFromConfig: mode 0,
  320x200x8, was picked now and then and the first background blit overran the clean buffer onto the dirty-rectangle
  pool), the CRT names of 0x4ac720 / 0x4adf70 swapped back (the assert handler crashed), sounds_restore by hand (the pan
  was not restored). 5333 of 5333 (e4a5c75).
* The menu (driven with CRKEY key presses, ea2976c): moving, choosing, the option gauges, saving with a typed name,
  loading, the cutscenes and the quit query work. grim_tools' new `tests/grim/menu.lua` (the menu's engine features:
  BlastText modes, gauges, DimRegion / DimScreen, userPaintHandler, the settings, the devices) gives the original's
  values: 5340 of 5340. The menu runs unthrottled (no frame limit in the window device: 1000+ frames a second, so the
  frame-counted fades of the credits are instant).
* Whole-game autorun (grimW_work/wg_start.sh, private autorun copy grimW_ar with `readfrom()` in nav_setfile.lua):
  `AUTORUN RESULT PASSED`, ch01-ch65 in 423 s. Fixed on the way: the stale camera of the ch49 crash noted above
  (sputRender_Update compares the camera pointer with the current setup's: a new set at the freed set's address kept
  the old setups' camera). With grim_tools' own nav_setfile.lua (`readfrom(old)`) the run dies in ch19: the 128 file
  slots fill up and the forklift's material is not found (sputResource_MatLoader, as the original, does not check).

## grim_tools' clean-room CI (decomp-cleanroom.yml) against main (2026-11-13)

The workflow of grim_tools (github.com/klusark/grim-autorun) that builds main and runs `run.py decomp` on a Windows
runner failed with 5 of 5333: `camera`, `camera_set` and `setups` crashed the game, `args_random_none` and
`args_random_num` differed. Both causes depend on the machine, which is why the desk runs showed all the same.

* The crashes: access violation in `sputLua_GetCameraPositionL` (and `GetCameraFOV`), `g_pSputRender_Camera` 0. Each was
  the first test of a fresh game (MakeCurrentSet, one frame, then the camera): that frame ran its Lua but did not draw,
  because `grimlib_UpdateManual` takes the active flag by value from `Main_Service` and skips `sputRender_Update` when it
  is 0, and the GRIM_ACTIVE knob forced the flag only from the Lua hook, inside the frame. On the runner the windows are
  not the foreground one at start-up, and the four games side by side take the activation from each other.
  GRIM_ACTIVE is gone: `Main_Service` draws whenever the display is a window (`g_bWindowedMode`), active or not, and
  only fullscreen keeps the original's rule (it drew only while active: DirectDraw's surfaces are lost to another
  application). The game ran on behind other windows anyway; it only stopped drawing. The window procedure handles
  WM_ACTIVATEAPP as the original again (windowed: input released and acquired; build_src.py no longer patches it out),
  and the CRKEY key presses of the clean room read the keyboard unacquired already. (The camera getters push nil and
  then read through the 0 pointer anyway: Ghidra's C has no return after `lua_pushnil`, not changed here.)
* `random()`: LUA.DLL's rand had its own seed in the original (its own linked MSVC runtime), the host msvcrt's rand is
  shared with the whole process, and on the runner something else draws from it on the main thread first (0.865932
  instead of 41/32767). math_random / math_randomseed use their own MSVC-style generator now (seed 1).

## Stack purges from the RET instruction; Ghidra project restored (2026-11-13)

* `run_script_inline` works now (Ghidra started with GHIDRA_MCP_ALLOW_SCRIPTS=1). A scan of every function's RET against its
  stored stack purge found 104 wrong ones in the DLLs (CHORE 89, IMUSE 13, LUA 2; the EXE has none), all `RET` without
  operand but a purge of 4..36 stored. They are 0 now. CHORE.DLL's generated text has no `in_stack_` read left (111
  before), so build/overrides_chore_naming.c (11 functions) is gone: clean room 0 of 5327 differ. Two CRT entry stubs that
  tail-jump into a __stdcall DllMain keep 12 / 16.
* The "X86 Function Callee Purge" and "Call Convention ID" analyzers are switched off in all four programs: they run
  after every edit and put back wrong purges (the cause of the locked-prototype breakage of the chore-naming round) and
  `__cdecl` on functions whose convention is unknown.
* **Save the project after edits** (`save_all_programs`). It had last been saved on 2026-11-11; a restart lost types
  rounds 1-10 and some name batches. Recovery: replay names/*.json in the order the batches were created (replaying an
  old batch after a newer one puts back its old comments, prototypes and global types), apply names/types_*.json, then
  restore what src/ had where old batches disagree with it. The EXE is /v101/GRIMFANDANGO.EXE (a stale /GRIMFANDANGO.EXE
  is in the project too); from Git Bash set MSYS_NO_PATHCONV=1 or /v101/ paths get mangled.
* `make -j14` sometimes fails every file with ccache "execute_noreturn of gcc failed" (process creation); -j8 and a
  rerun work.


## Override sweep: hand-written functions generated again (2026-11-13)

* Candidates: overrides whose decompiled twin shows no failure marker (`in_stack_`, `unaff_`, `extraout_`, `CONCAT`,
  `_ftol`, warnings). Each was disabled, built from the generated text and run through the clean room, and its
  generated text was read against the hand-written one: the clean room does not reach every path.
* **Generated now (30):** EXE PolyglotConfigure, SoundChanger, ThingAdjuster, sputLua_GetDiskFreeSpaceL,
  sputPrimitive_ChangePrimitive, sputResource_FontHandler, stdColor_ColorConvertOnePixel (overrides_logic.c);
  sputLua_SetCameraFOVL, sputLua_Test, sputLua_ShrinkBoxes, sputLua_UnShrinkBoxes, Keyframe/Colormap/MeshInstancer,
  stdFGetc, stdFPutc, FileUtil_SysRestore, Res_SysSave, sputPrimitive_Save / Restore (overrides_exe.c); CHORE
  Cos_New{StateBased,Int,Float}Tag, CosUtil_ComponentInfo, Cos_Save, Cos_Restore (overrides_logic_chore.c, removed),
  Cos_Read{Tags,Chores,Keys,Components}Section (overrides_asm_o2_chore.c). Clean room 0 of 5327 differ.
  Most were hand-written because they pass the address of a parameter slot as a call's output; the types rounds made
  Ghidra print those as plain `&param` uses, which is valid C.
* **Kept, generated text still wrong:** Palette_FromFloatTable (`_CIpow()` with an empty x87 stack; passes the clean
  room, gamma is never set), stdDisplay_VBufferNew (palette argument and the allocations' file / line lost; the video
  memory path is not run), sputLua_GetShrinkPosition (the position split into float[2] + z, so z never reaches the
  frame), Collision_PointInBox (TestCollision with 3 of 10 arguments, BuildPath with none: walk tests crash),
  sputActor_AlignToPuck (float compares, NaN taken the other way), Math_Floor / rdVector_Normalize3 and the
  overrides_cleanroom.c math (x87 rounding), sputActor_DrawToClean and res_FindInternalFile (the
  sputRender_SetPaletteFunc and res_FindDirectoryEntry prototypes in Ghidra; fixed later the same day, below), the iMUSE candidates (sound tests crash;
  docs/notes/imuse*.md give the reasons) and the renderer functions of overrides_logic.c (draw tests crash).
* Not swept: the rasteriser rounds (overrides_asm_*.c), whose differential tests in build/difftest/ are the oracle
  (the clean room only logs the box of the bright pixels), and overrides.c / overrides_mixer*.c, which carry host
  changes.
* **Prototypes Ghidra never had.** Many EXE functions have signature source DEFAULT: no stored prototype, so every
  caller guesses its own argument list from the pushes it sees (pushes shared across a branch get lost, a returned
  callback gets the arguments of the call that returned it). names/sweep_protos.json locks 17 of them (`__cdecl`;
  replay with `tools/apply_logic_protos.py names/sweep_protos.json`): sputRender_SetPaletteFunc (returns `code *`),
  res_FindDirectoryEntry, TestCollision, BuildPath, GetPath, GetOuttaTheBox, Collision_BoxSlide, sputLua_CollisionHandler,
  Mem_DumpLog, grimlib_MakeCurrentSetup / MarkDirtyRect / UpdateManual, sputRender_RestoreCacheRect (one ignored int:
  the caller pushes it), Win_RemoveMessageHook, Win_GetMainHwnd, rdClip_CalcOutcode2, plus rdClip_Line2 and
  Walker_AvoidActorPath locked to their overrides' signatures (their inferred ones moved with the callees'). Clean room
  0 of 5327 with the prototypes alone (75 functions re-exported).
* build_src's fix_ftol also takes `_ftol(in_stack_00000000)` as the lost ST0 operand (a caller with no saved register
  to show as CONCAT44).
* Generated again after that: sputActor_DrawToClean, res_FindInternalFile, res_FindDirectoryEntry
  (overrides_cleanroom.c), sputLua_MakeCurrentSetupL, sputLua_EngineDisplay (overrides_exe.c), sputLua_DimRegion,
  sputLua_RestoreCacheRect (overrides_logic.c). Clean room 0 of 5327. Collision_PointInBox stays: its `rep movsd` copies
  the box to the outgoing arguments before the moved end point is stored over the box's parameter slots, and Ghidra
  orders the stores first. The anm_* movie functions (overrides_mixer_misc.c) are readable rewrites on an AnimPlay
  struct that Ghidra lacks; they stay until the struct is in Ghidra.

## A stored prototype for every EXE function (2026-11-13)

* 1,906 of the EXE's 2,671 functions had no prototype in Ghidra (signature source DEFAULT). The decompiler then guesses
  per view: the function's own text from the stack slots its body reads, each caller from the pushes it sees, and both
  guesses move whenever a neighbour changes (gra_SetBuffer's turned into a 6-parameter `__fastcall` after other
  functions were locked). names/protos_all_exe.json now stores 1,863 of them (dumped from the project; replay with
  `tools/apply_logic_protos.py names/protos_all_exe.json` after names/sweep_protos.json). Clean room 0 of 5327 after each
  of the four address ranges and at the end.
* Source: main's src/GRIMFANDANGO.EXE/functions.h, i.e. the inference the validated build compiled against, not a fresh
  inference (which had already drifted), `__cdecl` (every callee-pop function already had a prototype).
* `undefinedN` parameters are not type-locked in Ghidra: a locked `undefined4` still became `int *` or `char *`. Scalar
  ones are stored as uint / ushort / byte / ulonglong. Pointer types stay as they were for generated functions: a
  concrete `byte *` made VbrAdpcm_Uncompress print `p[0x4dab10]` for `g_abAdpcmStepBits[i]` (the slot is reused as an
  index), a raw address the relocated build cannot map. Functions with a hand-written override get fully concrete types
  and a locked return (their declaration must match the override; a void return left `undefined` came back as
  `float10`).
* Not the override's own signature: overrides_asm_p2.c declares rdMatrix_BuildFromVectorAngle34's angle `uint` (it reads
  the bits) and hides functions.h's `float` with a #define; stored as `uint`, every C caller converted the float
  numerically (collision tests 26 off).
* A void return of a generated function stays `undefined`, so callers keep inferring whether they use EAX.
* By hand: Lua_Stub is the game's no-op print, `(char *fmt, ...)` (as `(void)` its callers lost the format strings that
  hand-written code still names); fle_zfilio_config reads its extension list from the stack, `(int cmd, ...)` (as
  `(int)` the movie player registered no zfilio extensions and no movie played); qsort / bsearch take `void *` (with
  `uint` the tables' addresses came out as numbers, which datagen maps back to symbols that globals.h then no longer
  declared).
* Left DEFAULT (27): VbrAdpcm_Uncompress, x87 returns (float10 / unkbyte10), functions without RET (purge unknown),
  the six whose view in main was `__fastcall`, and thunks.
* Printf-style functions declared with one parameter (grimdemo_*Print, default*Print, stdFilePrintf, fle_PrintF,
  Text_DrawFormatted, msc_error_SaveString) read their arguments with STACK0X; they are `(char *fmt, ...)` now (see
  "Printf-style functions varargs" below).

## Characters above 0x7f: Text_NextChar's byte zero-extended (2026-11-13)

* The whole-game autorun crashed in Font_GlyphAdvance on a 0xa1 in ch19 (and main's build at the start, in
  Glyph_Blit16Clipped). Text_NextChar returns its byte zero-extended (`XOR ECX,ECX; MOV CL,[EAX]`); Ghidra's callers
  print `ch = CONCAT31(extraout_var, cVar)`, and build_src turned that into `(uint)(cVar)`, which sign-extends a char:
  0x80..0xff became negative glyph indexes (text_FindNextBreak, Text_GetStringWidth, Text_DrawString). The rewrite is
  `(uint)(byte)(cVar)` now (the other users of the pattern return 0/1).
* Clean-room reproducers in grim_tools (tests/grim/text.lua): `text_high_chars` (sizes of text objects with
  0x80..0xff and the 0xfe break; the old build crashed or measured memory before the glyph table) and `text_high_drawn`
  (the same characters drawn over cr_flat; the old build crashed).

## Printf-style functions varargs (2026-11-13)

* grimdemo_{Message,Status,Error,Warning,Debug}Print, default{Message,Warning,Error,Debug}Print, stdFilePrintf,
  fle_PrintF, Text_DrawFormatted and msc_error_SaveString are stored as `(..., char *fmt, ...)` in
  names/protos_all_exe.json (they were `(char *)` / `(uint)`, msc_error_SaveString had Ghidra's "unknown calling
  convention" `(void)`). Their bodies still read the arguments with STACK0X; all other calls go through the host-service
  tables, so only the declarations change.
* msc_error_SaveString's one caller, bmp_bitmap_Alloc, now decompiles with its four pushes (format, file, line, type)
  instead of none, and datagen splits "%s, line %s:  Type %d not supported" (0x004f3d40) off the "VIDEO.getbm" string
  it had been merged into.
* msc_error_SaveString's hand-written version (overrides_asm_o2.c) is gone: the generated text is the same function.
  bmp_bitmap_Alloc stays hand-written (its tail is a jump table Ghidra could not recover); it calls msc_error_SaveString
  and the new string symbol directly instead of a cast and IMG_ADDR(0x004f3d40).

## A stored prototype for every DLL function (2026-11-13)

* IMUSE.DLL (106), LUA.DLL (124) and CHORE.DLL (149) functions without a prototype (signature source DEFAULT) get the
  one main's src/<dll>/functions.h showed, `__cdecl`, scalar `undefinedN` made concrete, like the EXE round above;
  names/protos_all_dlls.json (replay after names/protos_all_exe.json). Left DEFAULT: 6 functions without RET, 6 LUA
  functions returning float10 / unkbyte10, 12 IMUSE thunks.
* **Purge.** Their stack purge was unknown (the DLLs' "X86 Function Callee Purge" analyzer is off), and setting a
  prototype on such a function stores the parameter bytes as its purge: SoundsRegisterVoice got 4, so every caller lost
  4 bytes of stack and SoundStartVoiceStream's twin read the volume from the pan's slot. Every one ends in a plain RET:
  all purges were reset to 0 after the prototypes were set (IMUSE 80, LUA 18, CHORE 113).
* By hand: IMUSE FUN_10009700, the empty debug print sounds_restore calls with "Before", "After Stopall", ...: as
  `(void)` the calls lost the strings and datagen merged them into one block that overrides_imuse.c no longer found, so
  `(char *fmt, ...)`; SoundStartVoiceStream `char *name` (its stored `undefined4` was re-typed from SoundsRegisterVoice;
  the override follows); LUA luaD_call `(int pos, int nres)` (main showed `code *, void *`; the override and its two
  callers in overrides_lua_core.c lose their casts) and lua_Restore `(void *readFunc)`; CHORE msvc_qsort /
  msvc_shortsort / msvc_bsearch take their comparator as `void *` (the DLLs have no `code` type).
* CHORE's GrimServices.pFopen is a `SvcFopen *` (`int SvcFopen(char *name, char *mode)`, created in the CHORE.DLL
  project; not in names/, re-create it after a replay): with the field a plain `pointer` the decompiler inferred the
  call's arguments from the pushes and CosUtil_Write's fopen lost its "wt+" (the string then merged into "# %s
").
  Checked with an arity comparison of every indirect call before / after (casts excluded): no other call in the
  three DLLs changed its argument count.
* build/link.py now fails the link when a function is defined both by a hand-written override and by the generated
  code: with --allow-multiple-definition the first object won silently. It happened here: a comment between `)` and
  `{` of luaD_call's override hid it from build_src, which then left the twin compiled.
* sputLua_GetVisibleThingsL is hand-written (overrides_logic.c): with an argument that is neither nil nor an actor
  the original reads its viewer from a stack slot it never wrote. The LUA.DLL changes left a null pointer there and the
  clean room's args_GetVisibleThings_tab crashed (the other args_* tests of the file then ran in a restarted game
  and differed: no in-place ".lbm" on the interned "cr", another globals order). Such an argument now means the
  selected actor; none selected: the empty table.
* SoundStartVoiceStream compiles from the generated text again (its hand-written version in overrides_imuse.c is
  gone): with the callees' purges at 0 the twin reads the volume and pan from the right slots. Clean room 0 of 5329.
* Whole-game autorun on this build (IMUSE + LUA + CHORE prototypes, before the SoundStartVoiceStream removal): PASSED,
  433 s.


## Generated again after the DLL prototypes (2026-11-13)

* Re-sweep of the overrides outside the rasteriser / mixer / host files whose twin shows no failure marker, now that
  every function has a stored prototype. Generated now: Actor_UpdateMovement (overrides_logic.c; the twin uses the typed
  Actor / ActorExtra / CostumeNode fields at the offsets the hand-written body read), Script_Callback and
  Im_RunDeferredCommand (overrides_imuse.c; the twins are the hand-written functions).
* Kept: Im_RunTriggerCommand (the twin still calls a callback with the marker alone; the code pushes eleven words),
  FUN_100064d0 (reads the dispatcher's ESI), DwTerminate / DwQuery (COM calls through `code *` lose their __stdcall),
  ihost_get_buffer_info (the slot table's address is a plain number in an arithmetic expression),
  Cos_AllocCostumeSlot / Cos_AllocInstanceSlot (deliberate fix: the original leaves records undefined after a failed
  load), and those listed as kept in "Override sweep" above.
* Overrides whose decompiled twin is now the same text (comments and whitespace aside), generated again:
  rdCache_DrawFaceZ (the eleven lost rasteriser arguments are back with the stored prototypes; only the 0.0f
  literal of the TFS call differs from the hand-patched text), rdModel3_DrawFace (only a local's type differs:
  `undefined1 *` for `int`); the edge steps rdRaster_EdgeStepFlat, FUN_004104b0, FUN_00411b70, FUN_004129f0,
  FUN_00415180, FUN_004151c0, rdAFRaster_Advance{Left,Right}EdgeNGonGIT (overrides_asm_s1.c); the wrappers
  Dsnd_Mem{Copy,Fill}Cdecl, msc_MemCopy, dsn_getvol, dsn_getrate (overrides_mixer_drv.c) and sou_mixer_end
  (overrides_mixer.c). Clean room 0 of 5329.
* The SMUSH module glue of overrides_mixer_drv.c is generated again: sou_dsnd_module, sys_timer_module,
  DsndDriver_module_{startup,shutdown,terminate}, InsaneTimer_module_{shutdown,terminate}. The twins call the same
  service slots on the same globals (the hand-written code named them through `__asm__` aliases, g_dwDsndModuleSize for
  g_dwDsndDriver_share_config and so on). dsn_terminate stays: its twin calls sou_mixer_terminate where the hand-written
  one calls Mixer_Free. Clean room 0 of 5329.

## Coverage build, and the results that only lived in EAX (2026-11-14)

* `make COVERAGE=1 OBJ=obj-cov` (+ `link`) builds the four programs with gcov (`--coverage -fprofile-update=atomic -g`, also
  for the hand-written files: link.py, GRIM_COVERAGE); `tools/coverage.sh` builds it, runs grim_tools' clean-room suite on
  it (`run.py decomp`) and writes `build/coverage/` with `tools/covreport.py` (summary.md per program and file,
  functions.tsv per function, gcov's annotated text per module). Each module keeps its opt.mk level: with every module at
  -O0 (`OPT_ALL=-O0`, coverage or not) 31 clean-room tests differ (x87 results of the walker and turning code), 0 with
  opt.mk. A coverage DLL keeps libgcov to itself (`--exclude-libs,libgcov.a`: with --export-all-symbols the exe took
  `__gcov_init` from lua.dll), and the crash filter (startup.c) writes the counters of a game that crashes.
* It runs on Linux too: mingw-w64 i686 cross compiler, Wine with Xvfb and a PulseAudio null sink (grim_tools
  cleanroom/README.md, "The decomp on Linux"). GCC 13 there wanted `__stdcall` on LightEd_KeyboardProc's definition (its
  declaration in functions.h has it).
* The first coverage build did not start ("could not initialize your hardware"), then crashed in 4 places in 70 tests: 30
  functions reached through a function pointer (service tables, host callbacks, resource and costume handlers, Lua's
  traversal callback) were `void` although their body ends in a call whose value the callers use. In the original each is
  `call ...; ret`, so the callee's EAX is the result; the rebuilt programs passed it on only because nothing touched EAX
  between the call and the return, which gcov's counter update after the call does (and any other change of code
  generation could). mem_Alloc returned garbage (the SMUSH memory service: the movie module did not start), the file
  services (stdFileWrite, stdFseek, stdFileGetws, the stdio/stdfile module thunks), stdPlatform_AllocHandle /
  ReallocHandle (Text_BuildLineTable), sputRoom_LoadZBuffer (sputResource_ZBufferHandler), stdConffile_Open,
  Resource_CountCostumeRefs, iMUSE's ihost_get_map_addr / ihost_get_sound_addr / iMUSE_Free, LUA.DLL's checkfunc
  (lua_getobjname: FunctionName gave "tag method 'gettable'"), LuaSaveWriter, luaL_openlib. They return `uint` now:
  names/exe_service_thunk_protos.json holds the prototypes for Ghidra (`tools/apply_logic_protos.py
  names/exe_service_thunk_protos.json`), and src/ was edited to what the decompiler prints with them, so that the tree builds
  before the next export. Found by bisecting the objects of the coverage build (crt_unnamed.o), then the functions
  (no_profile_instrument_function), then from the crash reports. Clean room 0 of 5327 on both builds afterwards.
* Coverage of the suite on 2026-11-14 (before / after the tests added that day: images.lua, funnel.lua, zz_ims_fx.lua):
  EXE 61.4% / 63.0% of 47,893 lines, LUA.DLL 88.7%, IMUSE.DLL 67.4% / 71.9%, CHORE.DLL 58.1% (most of the rest is the
  costume editor's API, which nothing calls). Large parts the suite cannot reach: Direct3D (std3d.c, the hardware
  renderer), the registry (reg.c: GRIM_INI replaces it), dialogs, joysticks, the light editor.
* The costume editor is kept in the build but left out of the totals: tools/coverage_exclude.json lists the functions
  the shipped game cannot run (CHORE.DLL's CosUtil_* editor API but the five the costume loader uses, the Cos_* functions
  only the editor calls or nothing imports, the exe's sputCostume_SaveHook), each with its reason. covreport.py shows
  their lines in an Excluded column (functions.tsv marks them) and counts everything with --no-exclude. With the list:
  CHORE.DLL 85.0% of 1,698 lines (785 excluded), EXE 63.1% (67 excluded).
* 2026-11-14, more clean-room tests (grim_tools: shadow_mesh.lua, movie_modes.lua modes 1 and 7, the voice effect presets
  of zz_ims_fx.lua, lua6.lua): EXE 64.2%, LUA.DLL 90.4%, IMUSE.DLL 75.6%, CHORE.DLL 85.0% (with the exclusions). Found on
  the way: `setfallback("function", f)` and then calling a number hangs the rebuilt exe in luaD_call (it returns to the
  same stack slot after the tag method, as the original's decompilation reads); not tested yet whether the original does.
## ScreenCoord: sputLua_WorldToScreenL generated again (2026-11-14)

* rdPrimit3_GetScreenCoord writes two integers (x, y, truncated) and the depth as a float; its output parameter was
  `float *`, so callers converted the integer bits as floats. names/types_screencoord.json creates
  `ScreenCoord {int nX; int nY; float flZ;}`, types the parameter `ScreenCoord *` and sputLua_WorldToScreenL's local
  `local_c` as a ScreenCoord (`locals`, new in tools/apply_types.py: a stack local by its Ghidra name; local types
  used to be set ad hoc, now they replay with the batch). The twin then pushes `(float)local_c.nX / nY`, and the
  hand-written version is removed. The overrides of rdPrimit3_GetScreenCoord and sputText_CreateActorText take
  the struct. Clean room 0 of 5329.

## Prototype fixes: GetActorHandle, Res_Touch, Str_ToLower (2026-11-14)

* names/protos_fix_1.json (replay after names/protos_all_dlls.json): sputActor_GetActorHandle takes the actor only
  (the inferred `int tag` was the tag the callers push for the following lua_pushusertag; sputActor_SetSelectedActor
  then passed unaff_retaddr, the costume callbacks unaff_EDI / unaff_EBX); Res_Touch and Str_ToLower return void (no
  caller uses the value; EAX at their end is what the last callee left). The hand-written sputActor_SetSelectedActor,
  Res_Touch and Str_ToLower (overrides_logic.c) are gone: their twins are now the same functions.
* names/types_rdmodel3.json records rdModel3 (0x90), rdGeoset and rdMesh (0x7c) with the fields
  rdModel3_CalcRadii / CalcVertexNormals read. Typing CalcRadii's parameter did not make its twin right (the decompiler
  walks a pointer into the middle of each mesh and stores the radius through it as uint), so no function uses them yet.
* Clean room 0 of 5329.

## Palette_ApplyGamma generated again: an 8-byte stack argument (2026-11-14)

* Palette_FromFloatTable(out, in, n, double gamma) takes the double at [esp+0x10]; Ghidra's x86 `__cdecl` model
  aligns 8-byte stack arguments to 8 and put it at 0x14, so Palette_ApplyGamma's pushes of the table entry were read
  as one table dword plus the return address. A scan of every EXE function found only this one misplaced parameter.
  names/protos_fix_1.json now carries `"stack": {"gamma": 16}` for it: tools/apply_logic_protos.py switches such a
  function to custom storage and moves the named parameters.
* names/types_gamma.json types the table pointer (0x00803fc0) `double *` (Ghidra names it PTR_00803fc0; nothing in
  the program sets it). tools/apply_types.py records a pointer type given to an unnamed global in
  raw/<prog>/ptr_types.json, as tools/type_pointer_globals.py does, so build_src declares it with that type (as
  `undefined *` the decompiler's `PTR + idx - 1` stepped in bytes).
* build_src.py's fix_double_pieces: `(double)CONCAT44(hi, lo)` (a double loaded as two dwords) becomes
  `PUN(double, CONCAT44(hi, lo))`; the cast converted the 64-bit integer numerically. The lost-x87 `_ftol(` /
  `_frnd(` forms are left to fix_ftol. Compiled code affected: Palette_ApplyGamma only (PerfEnd's text changes too,
  under its override).
* The hand-written Palette_ApplyGamma (overrides_logic.c) is gone; Palette_FromFloatTable stays (`_CIpow` on an
  empty x87 stack). Clean room 0 of 5329; the gamma path is never run (the pointer is 0), so the generated text was
  checked against the machine code.
* raw/GRIMFANDANGO.EXE/data_items.txt (tools/export_data_items.py; export_changed.py does not refresh it) was a day
  old: a fresh dump differs in 1,626 lines (later names, new arrays) but changes nothing in src/.
* TextObject_New takes (ctx, text) only (names/protos_fix_1.json): its body reads two stack arguments; the inferred
  durationMs / flags were pushes for later calls, so sputText_MakeTextObjectL and sputText_BlastText (compiled from
  the generated text) passed unaff_EBX / unaff_EDI / unaff_EBP garbage. sputText_CreateActorText stays hand-written:
  its anchor rectangle (ints) is still typed float and read through an `Actor *`. Clean room 0 of 5329.

## LUA.DLL math library generated again; x87 pseudo-ops fptan / fpatan / log2 (2026-11-14)

* raw/ was behind src/ for the 30 functions of names/exe_service_thunk_protos.json (src/ had been edited by hand to
  return `uint`): the prototypes are now in Ghidra (`tools/apply_logic_protos.py names/exe_service_thunk_protos.json`,
  LUA.DLL / IMUSE.DLL / CHORE.DLL had to be opened in the bridge first) and re-exported, so build_src.py regenerates the
  same tree (only local names differ: `uVar1` for `uRet`).
* math_sin, cos, tan, atan, atan2, exp, log, log10, sqrt, deg, rad, min, max and luaFGetc (overrides.c) are generated
  again: their twins compute on the x87 values as the original does (fsin, fpatan, f2xm1 / fscale, FYL2X), where the
  hand-written versions used double precision. Kept: math_abs (its local is `undefined4`, compared as an integer),
  asin / acos / pow (`_CIasin()` etc. with an empty x87 stack), ceil / floor (the CRT call takes the double as two
  dwords), mod.
* ghidra_types.h (build_src.py) lacked `fptan`, `fpatan` and `log2`: the compiler took them as implicit `int`
  functions and link.py stubbed fptan / fpatan as traps (tan, atan and atan2 crashed the clean room's numbers tests),
  log2 resolved to nothing useful (log(10) was 1.6e8). They are builtins on long double now. A syntax pass over every
  src/ module with -Wimplicit-function-declaration finds no other implicit declaration. Clean room 0 of 5390.

## Smush sound engine accessors generated again (2026-11-14)

* sou_engine_GetPan / GetParam / GetVol / Query / SetPan / SetParam / SetRate / SetVol / Stop / SetHVol and
  SoundModule_GetChannelVolume / SetChannelVolume (overrides_mixer_snd.c) use their twins: the same loops over the 16
  voices (0x34 bytes at 0x008dad58, reached through the fields' own globals) and the same globals. sou_sound_module
  stays (its twin ends the buffer-size loop at the original address 0x8dacf0); the rest of the file is unchanged.
* build/mixdiff no longer runs on the current tree (snd_test exits before its first case with data.o for the old
  data_s.o), so these were read against the hand-written text and checked with the clean room's movie tests.
* Clean room: the 6 render_g* tests grim_tools added on 2026-11-14 differ with and without this change (5451 of
  5457 the same both times).

## Small Smush helpers generated again (2026-11-14)

* sys_Free, sys_Reset, Insane_MemCopy (overrides_mixer_drv.c), Mixer_Free (overrides_mixer.c), fle_Eof and
  StdFile_fle_Tell (overrides_mixer_misc.c) use their twins (the same stores and service calls; Insane_MemCopy copies
  the head bytes, then dwords, as the original, where the hand-written one called memcpy).
* Kept: sys_Alloc (its twin stores to `iVar3 + 0x8da5e8`, integer addresses of the original image), sys_Delay (the
  GRIM_SIMTIME tick), msc_MemSet (returns the count; the twin is void), Zfile_fle_Close (the twin calls the close service
  without its argument).
* Clean room 5451 of 5457, the same 6 render_g* tests as without the change.

## LUA.DLL chunk loader and VM helpers generated again (2026-11-14)

* luaV_pack, luaV_tonumber, LState_SaveObject, luaU_LoadNumber, LoadHeader and LoadConstants (overrides.c) use their
  twins: build_src's PUN rewrites (fix_float_bits_members, fix_casts) already turn their float stores through
  TObject.dwValue and their reused parameter slots into bit copies, which is what the hand-written versions did.
* Kept: luaO_equalObj (`TEST AH,0x40` after FCOMPP: an unordered compare counts as equal, the twin's `==` does not),
  message (the error tag method object is 8 bytes, the twin's local holds 4), match / lua_printstack (not compared yet).
* A TObject value union (float / uint) in Ghidra was tried and taken back: ghidra_types.h has structures only, and the
  pointer stores became `(TValue)ptr` casts.
* Clean room 5451 of 5457, the same 6 render_g* tests as without the change.
