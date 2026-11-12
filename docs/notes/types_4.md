# Types, round 4 (2026-11-12): the first data tables

Rounds 1 to 3 typed records the code passes around. This round starts step 7 of raw_free_build.md: typing the data
itself, so that `src/<prog>/data.c` holds values instead of byte lists. It needed `tools/datagen.py` to emit typed data
at all, and two batches of tables whose meaning is clear: `names/types_data_exe.json`, `names/types_data_lua.json`.

## datagen: typed spans

Until now `datagen.py` gave a value only to a span whose declared type was a single scalar of exactly the span's size;
every array, and every scalar followed by undeclared bytes, stayed an `unsigned char` list.

* **Arrays of scalars.** A span declared `T name[N]` (int, uint, short, float, double, sbyte, ...) is emitted with its
  N values; an array without a size takes as many whole elements as the span holds. Placeholder types (`undefined`,
  `undefined4`, ...) never split a span: they keep their byte lists unless they fit exactly, as before.
* **Tails.** When a span is longer than its type, the rest follows as `static unsigned char <name>__tail[]
  __attribute__((used))`, in the same section run, so the layout does not move. The tails are static because the DLLs
  export every global symbol: as globals they grew `.edata` and moved IMUSE.DLL's import table.
* **Floats** are written as the shortest decimal that reads back as the same bits (gcc rounds a decimal constant
  correctly; `datacmp.py` checks every one). The sine table reads `0.0f, 0.000383f, 0.000767f, ...`: the original's
  source evidently had six decimals. Infinities are `__builtin_inff()`, negative zero `-0.0f`; a NaN keeps the bytes.
* **char arrays** are text unless they hold control bytes, then numbers.
* **Ghidra-typed arrays the code never names** start a span of their own (`raw/<prog>/globals.json`): yacc's yydefgoto
  and yypgoto below, which the code reaches only through a biased base.
* **Labels inside an array.** A point inside a declared array that names no typed global of its own starts no span;
  its names become aliases at their offset (`.set name, owner + off`). Nothing uses this after this round's batches
  (the biased labels dropped out of the code, see below), but a pointer or label into a typed table no longer cuts it.

With no Ghidra change, the new datagen typed 47 more EXE spans (the arrays `globals.h` already declared, such as
`g_flRdroid_identMatrix34` and the four `g_anBlockySplit*`, and scalars with a tail); the build was byte-identical
apart from the build time.

## The tables

| program | address | type | name | |
|---|---|---|---|---|
| EXE | 0x004df600 | `float[4096]` | `g_aSinTable` | sine, a quarter wave at 90/4096-degree steps (stdMath_SinCos; cosine reads it backwards) |
| EXE | 0x004e3600 | `float[4096]` | `g_aTanTable` | tangent, the same steps (stdMath_Tan) |
| EXE | 0x004d98a8 | `uint[256]` | `g_aCrc_table` | zlib 1.1.3's CRC-32 table (0, 0x77073096, ...) |
| LUA | 0x10023188 | `sbyte[285]` | `g_aYytranslate` | token -> symbol |
| LUA | 0x100232a8 / 0x10023378 | `short[103]` | `g_aYyr1` / `g_aYyr2` | rule -> lhs symbol / rhs length |
| LUA | 0x10023448 / 0x10023610 | `short[184]` | `g_wYydefact` / `g_wYypact` | per state |
| LUA | 0x100235b8 / 0x10023780 | `short[44]` | `g_wYydefgoto` / `g_wYypgoto` | per nonterminal (new names) |
| LUA | 0x100237d8 / 0x100239e8 | `short[263]` | `g_aYytable` / `g_aYycheck` | YYLAST 262 |
| LUA | 0x100270e8 | `int[23]` | `g_dwDimensions` | lobject.c's hash sizes, 5 ... 13158023, MAX_INT (INT_MAX - 2) |

The parser tables are bison 1.x output of Lua 3.1's `lua.stx`: YYNTBASE 49 (the smallest `yyr1`), 102 rules, 184
states, 44 nonterminals, tokens up to 284 (`yytranslate`'s bound in `luaY_parse`). Each table's length follows from the
next one's start, and the pairs agree (`yydefact` / `yypact`, `yydefgoto` / `yypgoto`, `yytable` / `yycheck`).

* **The biased bases.** The code indexes `yydefgoto[yyr1[n] - YYNTBASE]` and `yypgoto[...]`; the compiler folded the
  subtraction into the base, so it addresses 0x10023556 and 0x1002371e, 98 bytes before the tables, inside `yydefact`
  and `yypact`. Ghidra had put the labels `g_aYydefgoto` / `g_aYypgoto` there. They are now `g_wYydefgoto_biased` /
  `g_wYypgoto_biased`, and the names without the suffix are on the real tables (the bridge's naming policy wants a
  prefix; `w` as for `g_wYydefact`). With `yydefact` / `yypact` typed, the decompiler no longer uses the labels: it
  prints the reads as `g_wYydefact[g_aYyr1[n] + 0x87]` and `g_wYypact[g_aYyr1[n] + 0x87]` (135 = 184 - 49). That is
  the memory the original reads (the layout is pinned, `yydefgoto` follows `yydefact`), but it reads like an index past
  the end of `yydefact`; the C before this round was no better (`*(short *)(&g_aYydefgoto + yyr1 * 2)` on a one-byte
  `undefined`).
* **yytranslate as `char[285]`** made the decompiler print `(int)""[local_be0]`: a char array whose first byte is 0 is
  an empty string to it, and the C indexed an empty string literal. `sbyte[285]` (signed, as bison's `char` is on
  MSVC) gives `(int)g_aYytranslate[local_be0]`. `datagen` knows `sbyte` / `schar` as `signed char`.
* `yycheck`'s span holds 54 bytes after the table: the parser's floating-point constants, now its tail.

`stdMath_SinCos` and `stdMath_Tan` are hand-written overrides (overrides_logic.c) that read the tables through
`(const float *)&g_aSinTable`; they compile unchanged. The CRC function is the bundled zlib's, which the system zlib
replaces, so it is not linked.

## Checks

* All four programs compile and link; stubs unchanged (EXE 42, LUA 58, IMUSE 9, CHORE 16).
* `build/datacmp.py` against main's build: 0 differences, 0 moved, 0 missing in all four programs (LUA.DLL: 100
  pointers equal by target, the functions after `luaY_parse` moved).
* Sections against main's build: CHORE.DLL and IMUSE.DLL identical, the EXE's code and data identical (`.idata`: import
  hints into LUA.DLL's export table, which has new names; `.rdata`: the build time). LUA.DLL's code changes in
  `luaY_parse` and `luaO_redimension`, which read the tables as arrays now.
* Untyped initialised bytes (`datagen.py report`): EXE 92,905 -> 58,741, LUA 26,208 -> 23,438, IMUSE and CHORE
  unchanged (47,661 and 20,818).
* Clean-room against grim_tools' knowngood (5167 tests, run with no file of the original install in the run folder):
  the same 3 tests differ from the reference as for main's build (`lab_files`, `lab_dofile`, `lab_costume`), and the
  log against main's build's: 0 of 5167 differ.
* `src/GRIMFANDANGO.EXE/stddisplay.c`: `Palette_FromFloatTable`'s `FTOL(_CIpow())` became `(longlong)_CIpow()`.
  `tools/ftol_fold.py` takes the float-returning functions from the previous `functions.h`, so a run of `build_src.py`
  after the one that typed `_CIpow` folds one more call; `FTOL(x)` is `((long long)(x))`, the same code.

## Next

* IMUSE.DLL's music tables, about 26 KB of its 48 KB: arrays of 0x54-byte records (state and sequence tables; the
  track name, a type at +0x20, +0x40, volume and pan at +0x4c / +0x50) at 0x10017328 and 0x1001ae50 / 0x1001bbe8. A
  struct round of its own.
* The EXE's remaining tables over 1 KB (0x004f20d8, 0x004eca04, 0x004d9e50, 0x004f34e8), `g_dwPhonemeTable`,
  `g_dwGrimlib_PerfData`; Lua's `g_aValidevents` (`char[8][18]`: datagen does not handle two dimensions yet) and
  `g_aOpcodeDirectory`.
* The C runtime's tables (day and month names, ctype) in all four programs.
