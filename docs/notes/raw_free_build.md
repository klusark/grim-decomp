# Plan: the program data as C, with no data.s and no raw/ at build time

## Done (2026-11-12): steps 1 to 6

The build reads nothing of `raw/`, and `data.s` is gone. `build/gendata.py` is deleted; `tools/datagen.py`, called by
`tools/build_src.py`, writes `src/<prog>/data.c` and `src/<DLL>/exports.json`. `.github/workflows/build.yml` builds and
links the four programs from a plain checkout, after checking that there is no `raw/`.

| | EXE | LUA | IMUSE | CHORE |
|---|---|---|---|---|
| spans (definitions in data.c) | 3861 | 945 | 686 | 434 |
| scalars typed from globals.h | 822 | 117 | 73 | 10 |
| strings | 823 | 292 | 28 | 2 |
| pointers / pointer tables / mixed structs | 35 / 79 / 40 | 21 / 38 / 23 | 14 / 10 / 9 | 12 / 10 / 8 |
| byte arrays with data / all zero | 958 / 1104 | 343 / 111 | 291 / 261 | 289 / 103 |
| untyped initialised bytes | 92,905 | 26,208 | 47,662 | 20,818 |
| `IMG_ADDR` uses rewritten to names | 247 | 113 | 178 | 172 |
| `data.c` size | 1.15 MB | 0.26 MB | 0.35 MB | 0.14 MB |

What was done differently from the steps below:
* **Step 3.** `python -I tools/datagen.py report [PROG]` prints the table above per program. The export has no offset
  xrefs, so "read past its end" is approximated: the report lists the globals whose span is longer than their
  declared type and holds data after it (EXE 288, LUA 107, IMUSE 71, CHORE 37; the largest are `g_aSinTable` and
  `g_aTanTable`, 16 KB each, declared `undefined`).
* **Step 4.** The generated code no longer uses `IMG_ADDR`: the 710 uses name the span at their address (`&DAT_...`,
  declared in `globals.h` under "data the code addressed by number"). The hand-written overrides keep their 84 uses:
  many compute the address at run time (`IMW(STATE_TAB + 0x24 + i * ENT_SIZE)`, `Q3G(va)`), which needs a base, not a
  name. `sect_rdata` / `sect_data` therefore stay, as labels on the first span of each section; the layout is pinned,
  so `sect_data + (a - 0x004dd000)` is still the original's address `a`. Removing them is part of step 8.
* **Step 5.** The DLLs' code copies are gone. For the EXE, the three items in the code section are DirectInput's
  keyboard and mouse data formats (`DAT_004d5370`, `DAT_004d5400`) and a jump table of `bmp_bitmap_Alloc`
  (`DAT_004ce808`, used only by the decompiled text, which an override replaces). They come from the dump like the
  rest, with what they point at: the two object-format arrays (0x4d4370, 0x4d5388), whose GUID pointers point into
  `.rdata`. 4.4 KB instead of the 853 KB copy. A jump-table entry that points into code keeps its value. mingw's
  `c_dfDIKeyboard` was not used, so that the data check below stays exact.
* **Step 6.** One `data.c` per program, not two files: a single translation unit declares every span first, so the
  pointers can refer forward. The layout:
  * an input section is at least 4-aligned, and the assembler pads a section's end to its alignment;
  * so a section key is opened only at a 4-aligned span, and the spans that follow share it, kept in order by
    `no_reorder`; `aligned(1)` stops gcc from padding large arrays;
  * an empty 16-aligned anchor (`.data$grim_0`) sorts first, so the data starts 16-aligned as `data.s` did.
  `link.py` writes its own definitions (import slots, names outside the sections) to `obj/<prog>/link_data.c` now.
* **Checks.**
  * `build/datacmp.py OLD NEW` compares the data of two builds span by span. Against the round-3 build with
    `data.s`, all four programs: 0 differences, 0 spans moved, 0 missing; EXE 4,537,216 bytes and 2065 pointers equal
    by target, LUA 471, IMUSE 249, CHORE 241 pointers.
  * The binaries shrink by the code copies: EXE 6.78 -> 6.17 MB, LUA 407 -> 351 KB, IMUSE 408 -> 382 KB,
    CHORE 170 -> 159 KB. Stubs unchanged (EXE 42, LUA 58, IMUSE 9, CHORE 16).
  * A copy of the tree without `raw/` (the tracked and new files only) compiles and links. Its binaries equal the
    local build's, apart from the build time and `imuse.dll`'s symbol table, as the HMI import library is rebuilt.
  * Clean-room: against grim_tools' `knowngood` branch (390662d, exported, with a49fb55's `run.py decomp` applied, the only
    change; 5167 tests), main's build and this one back to back: both differ from the reference in the same 3 tests
    (`lab_files`, `lab_dofile`, `lab_costume`). Their logs against each other: 1 value, `sound_fade` `after`
    ("1 0 1 64 127 64" vs "1 0 1 64 120 67"). Rerun alone, main's build gave 127 64 in 9 of 9 runs, this one in 7 of 10.
    The test fades on iMUSE's real-time clock while the game runs on simulated 17 ms frames, so the value depends
    on how fast the frames run; this build's code differs from main's (the 710 `IMG_ADDR` calls are constant
    addresses now), its data does not. Round 7 of BUILD_NOTES saw main's own build give 120 67.
* `build/link.py` also built the HMI import libraries with the i686 toolchain's own `dlltool`, run inside `build/hmi`,
  because `dlltool` fails when the output path is long. Since the same day there are none: the HMI library is C,
  `build/overrides_hmifx.c` (build/BUILD_NOTES.md, "The HMI effects library in C").

Step 7 (typing the data in Ghidra) has started: types_4.md types the first tables and teaches datagen.py arrays,
tails and Ghidra-typed tables the code does not name. Step 8 (releasing the layout) is open. Every typed table turns a byte array of
`data.c` into values, and `datacmp.py` proves it unchanged.

## The plan

Today `build/gendata.py` turns the original's dumped sections (`raw/<prog>/sections/*.bin`) into `obj/<prog>/data.s`
at link time:
* one blob per section (`_sect_rdata`, `_sect_data`, and for every program a copy of its code, `_sect_text`);
* a label at each global the C references;
* `.long` relocations where a dword points into the image.

The C reaches the data in two ways: by name (`extern int DAT_004f5a2c;` in `globals.h`) and by original address
(`IMG_ADDR(0x004dd728)`, which `img_addr_` in `ghidra_types.h` turns into `sect_data + offset`).

The goal is that `data.s` goes away, neither tracked nor generated. Every initialised global becomes a C definition
with its value in `src/`, written by `tools/build_src.py` from Ghidra's types and the dumped bytes, like the functions
are. With it go the nine raw files that `gendata.py` reads. The two other uses of `raw/` at build time get small
changes of their own (steps 1 and 2).

## Where it stands (2026-11-12)

| | EXE | LUA | IMUSE | CHORE |
|---|---|---|---|---|
| initialised `.rdata` + `.data` bytes | 117,441 | 36,028 | 53,264 | 22,284 |
| covered by a Ghidra data item | 31,144 | 12,454 | 5,180 | 3,366 |
| labels referenced by the C (`.rdata` / `.data`) | 51 / 953 | 32 / 293 | 9 / 120 | 9 / 31 |
| `IMG_ADDR` uses (distinct addresses) | 247 (159) | 113 (68) | 178 (102) | 172 (113) |
| symbols in the code-section copy | 3 (65 relocations) | 0 | 0 | 0 |

The hand-written overrides use `IMG_ADDR` 84 more times. Most of the Ghidra items that exist are strings (23 KB of
the EXE's 31 KB). About three quarters of the initialised bytes have no type at all.

## Steps

Each step either keeps the binaries the same or changes only code that computes an address.
* **Data check:** for every global, the bytes at its address in the new build must equal the bytes at its address in
  the previous build, with pointers compared by the symbol they point at. A script, `build/datacmp.py`, does this
  from the two link maps (`-Wl,-Map`). It replaces "identical `.data`" once the layout is allowed to move.
* **Cleanroom:** every step that changes a binary gets `run.py decomp`, against the same 33 differences as main.

### 1. The stub report reads `src/<prog>/imports.h`

`link.py` takes its import names from the tracked `imports.h` instead of `raw/<prog>/imports.json`. No output change.

### 2. DLL export facts in a tracked file

`build_src.py` writes `src/<DLL>/exports.json`: each named export, its decorated name if it pops its arguments (from
`stdcall_funcs.json`, minus `names/not_stdcall.json`), and whether it is a variable. `dllnames.py` and `link.py`'s
`data_exports` read it in place of the DLLs' `stdcall_funcs.json`, `exports.json` and `segments.txt`. No output change.

### 3. A data report

`tools/data_report.py`, on the export side, splits each section of each program at:
* every referenced label;
* every `IMG_ADDR` target;
* every relocation target (the places `gendata.py` emits `_sect_x + off` today).

For each resulting span it gives:
* the Ghidra type and size, if one exists, and whether the span is longer than that type;
* whether anything refers into it: by label, by `IMG_ADDR`, or from another span's pointer;
* whether the C reads past its end. This comes from Ghidra's offset xrefs and `access_sizes.json`; the known case is
  `stdMath_SinCos` reading the sine/cosine quadrant tables from `.rdata` on into `.data`.

The report's totals are the progress numbers for what follows, like the stub counts: untyped bytes,
`IMG_ADDR` uses, spans that are read past. It also lists the spans nothing refers to, such as the original's import
tables and padding. Those spans need no C at all.

### 4. `IMG_ADDR` and section-relative pointers become symbol references

`build_src.py` rewrites `IMG_ADDR(0xADDR)` as `((unsigned)&SYM + off)`, where SYM is the span that holds ADDR. An
address with no span (a code address, or one outside the image) keeps its literal value. The same rewrite goes over
the 84 uses in the overrides, by a one-off script, with the result reviewed. `gendata.py`'s `_sect_x + off`
relocations become `SYM + off` the same way.

This step still builds with `data.s` and can land on its own. Because `img_addr_` disappears, `ghidra_types.h` no
longer needs `sect_rdata` / `sect_data`. The code changes (a symbol address in place of a range check), so check it
with the cleanroom; the data is unchanged.

### 5. The code-section copy

* **DLLs:** nothing uses their copies, so `gendata.py` stops emitting them.
* **EXE:** the three symbols and the island they sit in (0x4ce800-0x4d5800, about 28 KB) get identified in Ghidra.
  `c_dfDIKeyboard` is DirectInput's keyboard data format, which mingw's `libdinput` defines; it is linked from there
  instead of copied. What is left becomes typed data like the rest, emitted by step 6.

After this step no build output holds the original's code bytes.

### 6. Definitions in C, layout pinned

`build_src.py` emits a definition with an initialiser for every span that is referenced:
* **Values come from the Ghidra type:**
  * integers;
  * floats as hex-float literals, so the bits are exact (`__builtin_nanf("0x...")` for a NaN);
  * strings;
  * pointers as `&SYM + off` or a function name;
  * structs (the types of `ghidra_types.h`) with designated initialisers.
* **Untyped bytes** go out as `unsigned char` arrays. A span longer than its type gets the rest as a tail object right
  behind it.
* **Uninitialised globals** (the zero part of `.data`, defined by `link.py`'s `data_c` today) are emitted the same
  way, so `data_c` goes too.

For a start the definitions go into `src/<prog>/data_rdata.c` and `data_data.c`, in address order. Moving each one to
the module that uses it can come later, because of how the order is kept:

* **Layout pinned:** every definition gets `__attribute__((section(".data$<order>")))`, with order = the original
  section and address. The i686 `ld` script collects `*(SORT(.data$*))` (and `.rdata$*`) in name order. The globals
  therefore keep the original order whatever file they are in.
* **Gaps:** a span starts where the previous one ended, so there are none. Alignment padding would shift what follows,
  so every definition gets its own `.data$` section, and the check below catches any padding. A global whose original
  offset is not a multiple of its type's alignment is emitted through a packed typedef. On a variable, `aligned` can
  only raise the alignment, never lower it.
* **Layout check:** `build/datacmp.py` also checks that every global sits at its original offset from the first
  global of its section. Until step 8, a build where one moved fails.

`link.py` stops running `gendata.py`, and `data.s` is gone. So are the nine raw files it read. The data check of this
step must pass with no difference at all, apart from what step 5 removed.

### 7. Typing rounds

Not needed for steps 1-6, and it is what makes the data readable: Ghidra typing rounds for the data, like the struct
rounds. The report of step 3 chooses what comes next:
* the Lua registration tables (`{name, function}` pairs);
* the float tables;
* the costume and chore tables;
* the iMUSE tables, which make up most of IMUSE's 48 KB;
* the remaining `undefined4` globals (769 in the EXE).

Every typed table turns a byte array into C values. The data check proves that each one is unchanged.

### 8. Releasing the layout

A global that the report shows is never read past its end, and never reached through another global's address, can
drop its pinned section. The linker then places it where it likes. Globals that are read across (the quadrant tables)
stay pinned, or are joined into one typed array. Done in batches, each checked by the cleanroom. This step is not
needed to remove `data.s` and can wait indefinitely.

## Order

Steps 1, 2 and 4 are independent, and 4 is the largest change to the code. Step 3 is the tool for steps 4 to 8, so it
comes first. Step 5 can go any time before step 6. Step 6 is the switch: from there on the build reads no file of
`raw/`. CI can build from a plain checkout from then on, and fails if anything opens `raw/` (make the helpers raise
on a missing file instead of skipping, as `gendata.py`'s `os.path.exists` on `textblob.json` does now).

## Size in git

The untyped bytes are the largest part of step 6's output at first: about 86 KB for the EXE, 180 KB for all four, in
`0x..` array initialisers, roughly 1 MB of C. That falls with every typing round. The data is still the original's,
now as C values in `src/`, as the functions are C from the original's code.
