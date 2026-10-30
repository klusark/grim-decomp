# Building the reconstruction

`src/` is generated. Everything that makes it compile lives in
`tools/build_src.py` (text fix-ups, header generation) and in this directory
(`Makefile`, `compat.h`, `stubify.py`, `summary.py`, `link.py`). Nothing under
`src/` is edited by hand, so this always works:

```bash
rm -rf src && python -I tools/build_src.py && make -C build -j8
make -C build link        # stretch goal: link all four PE files
```

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
# Building the reconstruction

`src/` is generated. Everything that makes it compile lives in
`tools/build_src.py` (text fix-ups, header generation) and in this directory
(`Makefile`, `compat.h`, `stubify.py`, `summary.py`, `link.py`). Nothing under
`src/` is edited by hand, so this always works:

```bash
rm -rf src && python -I tools/build_src.py && make -C build -j8
make -C build link        # stretch goal: link all four PE files
```

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
him (Up = forward, Left/Right = turn, like the original), the rest chore plays. Movies are off (the
Smush/LecShare chain is not reproduced), sound has not been verified by ear.

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

Known limit: saves made by the original game (`saves_old_numbering/`) contain raw pointers into the original
IMUSE.DLL image (e.g. `&DAT_1001e900`) and crash the rebuilt iMUSE restore; saves written by the rebuilt
game load fine.
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
