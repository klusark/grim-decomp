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
2. **Struct layouts are not exported.** Only `GrimServices` exists in Ghidra
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
* **HMI audio.** Import libraries for the game's `HMIFXLIB.DLL` and
  `HMIFXFP.DLL` are generated in `build/hmi/` with `dlltool` from their
  export tables, so IMUSE.DLL binds to the real DLLs.

Running: copy `obj/GRIMFANDANGO.EXE/grimfandango.exe` and the three rebuilt
DLLs into one folder (`build/run/`) and start the EXE with the game's data
folder (`DATA*.LAB`, `GRIM.TAB`, `HMIFX*.DLL`) as the working directory, e.g.
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
* Functions that break when assembled stay C via `names/asm_exclude.json`: `ModelComponent_Create`
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
window, ignore WM_ACTIVATEAPP), `GRIM_LUA_FILE`/`GRIM_LUA_LOG` (Lua lines per frame; polled from Lua_UpdateFrame and from
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
- Functions patched by `names/asm_patches.json` (`Game_FrameUpdate`, `Input_PollKeyboard`, `Lua_UpdateFrame`, `Lua_InitGameLibs`) need the
  hook in C too (`Game_FrameUpdate`, `Lua_UpdateFrame` are in `overrides_exe.c`).
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
  * q3: rdPuppet_AdvanceTrack, rdPuppet_UpdateFrame, rdModel3_LoadText (now `(char *path, char *model)`, what the
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
  never wrote; game data never reaches them): rdModel3_LoadText with material indices outside 0..0x7f,
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
  sh wg_watch.sh`, one chapter from its checkpoint `sh wr_resume.sh <slot> <tag>`): **FAILED at ch54** (sewer hub:
  `AUTORUN FAIL nav: no way from 0.78 -0.35 to -0.24 -0.07 in sewer hub for 18 seconds`; Manny enters ladderup_box but
  the level never changes). Not a regression: the 2df265d build fails the same way, alone from grim54.gsv and in a full
  run. The autorun itself has 14 commits since its 2026-10-30 pass (nav planner, known links), so it may be autorun
  drift; the 2026-10-30 autorun (grim_tools ca8eb27, grimW_ar1030) did not get past ch51 in its one try (see below).
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
