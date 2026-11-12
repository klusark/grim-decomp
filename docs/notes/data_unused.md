# The data nothing reads (2026-11-12): zlib's tables and the dead C runtime's

The build takes 679 original functions out (`names/lib_replace.json`): the bundled zlib 1.1.3, which the system
zlib replaces, the MSVC runtime functions msvcrt.dll replaces, and the dead runtime that nothing live reaches. Their
data stayed in `src/<prog>/data.c` as the original's bytes. `tools/data_unused.py` finds it, writes the list to
`names/data_unused.json`, and `tools/datagen.py` emits those spans as zeros.

## What "unused" means

The layout of the data is still pinned (raw_free_build.md, step 8 is open): the overrides compute addresses from the
section starts, and the code reads tables past their labels. So an unused span is not removed; it keeps its name,
size and place, and loses its content:

    /* 0x004d98a8, 1024 bytes, unused (zlib) */ GRIM_DATA("004d98a8") unsigned char g_aCrc_table[1024];

A span is unused when all of these hold:
* **The built program does not reach it.** No base relocation outside the spans points into it: the code, generated
  or hand-written, the import tables, the overrides' own data. No hex literal of `build/*.c` lies in it (`IMG_ADDR`,
  `SPAN_DATA`, `Q3G` and the other ways the overrides address the original's data). No reached span holds a pointer
  to it. Every absolute address in a PE file has a base relocation, so this is complete for what the code names.
* **Only code taken out of the build names it.** Every original function whose decompiled text names the span (or an
  alias) is in `lib_replace.json`, and every pointer to it sits in a span that is itself unused. A span nothing names
  counts as the rest of the unused span before it.
* **Its neighbour is not live.** The span before it is not reached either. Live code that indexes a table from a label
  in front of it never names the rest: iMUSE reads its state table as `DAT_1001730c[state * 0x15]`, and
  `DAT_10017328`, a column of the first record, is named only by a dead function. The relocations alone call that
  15 KB table unreached; this rule keeps it.

The rules are iterated to a fixed point (strings that only an unused pointer table points at go with it), and the
list only grows: a listed span stays listed unless the build reaches it again, which the tool reports.

## What went

| | unused spans | bytes | with data | by reader |
|---|---|---|---|---|
| EXE | 311 | 16,739 | 269 spans, 15,185 bytes | zlib 9,344, dead runtime 4,407, msvcrt-replaced 152, pointed at by unused data 2,536, rest 300 |
| LUA | 117 | 7,831 | 93, 7,696 | dead runtime 2,249, pointed at 5,148, rest 434 |
| IMUSE | 81 | 7,712 | 30, 1,708 | dead runtime 3,208, pointed at 4,308, rest 196 |
| CHORE | 263 | 13,516 | 185, 7,354 | dead runtime 6,566, pointed at 6,588, rest 362 |

zlib's data is all of it: `configuration_table`, the CRC-32 table, the static trees and descriptors of trees.c, the
length / distance code tables, inflate's fixed tables, `z_errmsg` and every message string, the version string. The
runtime's: locale and ctype tables, the day and month names of `strftime`, the C++ exception-handling tables
(`terminate`), the error message table of `strerror`, and the like.

`data.c` sizes: EXE 1,039 -> 955 KB, LUA 249 -> 203 KB, IMUSE 346 -> 339 KB, CHORE 136 -> 98 KB.

Some dead data stays: the neighbour rule keeps a dead table that follows live data (the spans do not say where an
object ends), and data named by a live function's dead branch counts as reached. Typing (types_4.md onwards) gives
tables extents; with them the neighbour rule can be relaxed.

## Effects on the build

* The zeroed spans held the only pointers to some dead functions: zlib's `deflate_stored` / `deflate_fast` /
  `deflate_slow` (from `configuration_table`), the runtime's `terminate` and exception-handling helpers. Those were
  stubs (`stubs.txt`) and are gone: EXE 42 -> 32, LUA 58 -> 41, IMUSE 9 -> 8, CHORE 16 -> 14; no stub was added. The
  code after them moves, so `.text` differs from round 4's build by addresses.
* `build/datacmp.py` knows the list: a listed span must be zero in the new build; every other span compares as before.

## Checks

* All four programs compile and link.
* `datacmp.py` against round 4's build: 0 differences, 0 moved, 0 missing in all four programs; the 772 unused spans
  are zero; the pointers equal by target are function pointers into the moved code (EXE 35, LUA 33, IMUSE 8,
  CHORE 75).
* `data_unused.py` on the new build finds the same list (a fixed point).
* Clean-room against grim_tools' knowngood (5167 tests, no file of the original install in the run folder), two full
  runs of this build:
  * the second: the same 3 tests differ from the reference as for main's and round 4's builds (`lab_files`,
    `lab_dofile`, `lab_costume`), and its log against round 4's build's: 0 of 5167 differ;
  * the first matched the reference in all 5167: the three lab tests found the members of `cr_extra.lab`. Run alone,
    they fail for this build and for round 4's alike, and the second full run failed them again. So their failure is
    not deterministic: the rebuilt game sometimes does find the members of a second archive. Worth a look of its own;
    it is not this change.

## Running it

After a build: `python -I tools/data_unused.py` (reads `build/obj/<prog>/`; a directory with the four binaries can
be given instead), then `tools/build_src.py` and the build. `--check` prints the counts and writes nothing.
