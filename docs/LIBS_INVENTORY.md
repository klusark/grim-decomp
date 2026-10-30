# Library code in the rebuilt game: what is bundled, what is replaced, what could be

This is the inventory of everything in `GRIMFANDANGO.EXE`, `LUA.DLL`, `IMUSE.DLL` and `CHORE.DLL` that is library
code rather than game code, with the system library that could stand in for it, the exact way behaviour could
differ, and what was done about it (see "System libraries instead of the bundled CRT/zlib" in `build/BUILD_NOTES.md`
for the mechanics, `names/lib_replace.json` for the data, `tools/lib_audit.py` for the reachability audit).

Excluded by decision of the project owner: the **Lua 3.1 VM inside LUA.DLL** (lvm/ldo/lgc/lparser/llex/lstring/
ltable/... , about 300 functions). It is the game's own modified Lua; it stays exactly as decompiled. Only the C
runtime *underneath* it (strlen, sprintf, malloc, floor, ...) is in scope, and only as long as the VM's code and
behaviour, number formatting included, stay unchanged.

## 0. Summary

* **The C runtime was already mostly the host's.** `build/link.py` has always left the decompiled MSVC 6 runtime
  module (`crt.c`: 214 functions in the EXE, 233 in LUA.DLL, 52 in IMUSE.DLL, 1 in CHORE.DLL) out of every link; all four
  modules import `malloc/free/realloc/calloc/fopen/printf/qsort/...` from the system `msvcrt.dll` and therefore
  share ONE heap and one set of stdio tables (verified in the import tables, `objdump -p`). What remained were the
  runtime functions Ghidra had **not** named (`crt_unnamed.c`), CRT functions that the assembly-mode selection had
  pulled in anyway (`_snprintf`, `_output`, `_setjmp3`, floor/ceil, ...), and, in CHORE.DLL and IMUSE.DLL, whole
  statically linked runtimes (CHORE.DLL: ~150 functions, its own malloc/sbh heap, sscanf, strncpy, qsort, ...).
* **Done in this work** (all verified, see BUILD_NOTES): 
  * 558 functions of original runtime code that nothing live can reach (start-up, locale, `_ioinit`, `__sbh_*`
    heap, signal, C++ EH internals, ...) removed from the four binaries (`dead`); 
  * 33 live runtime functions replaced by their msvcrt.dll equivalents (`host`): printf (`_snprintf`),
    `_CIfmod`, `strncat`, `fgetws`, `setjmp3`, `floor`/`ceil` (the Ghidra names are swapped, see section 5), the
    Lua number functions `asin`/`acos`/`rand`/`srand`/`strstr`, CHORE.DLL's strncpy/strrchr/strchr/memmove/bsearch/sscanf/stricmp,
    IMUSE.DLL's strrchr/strncpy/stricmp/toupper/vsprintf/fopen/fseek/fwrite/fclose;
  * the game's **bundled zlib 1.1.3** (53 functions: inflate, deflate, trees, crc32) replaced by the system
    **zlib 1.3.2** (`mingw-w64-i686-zlib`, linked statically as `libz.a`; no DLL added);
  * three latent traps fixed on the way (functions that called trap stubs of the removed runtime), one real bug
    fixed (`asin`/`acos` returned 0), one default restored (`rand()` start seed 1 instead of 0). All listed in section 5.
* **Not replaced, and why:** `_ftol` (EXE, one `fisttp`, faster than msvcrt's and bit-identical), `_alloca_probe`
  (not exported by msvcrt.dll), CHORE.DLL's qsort (msvcrt's qsort orders equal keys differently, measured), the ctype
  table lookups of the Lua lexer (four 13-line functions), the C++ EH funclets, and everything in section 4.

## 1. How library code gets into the binaries

```
raw/<prog>/functions/*.c   Ghidra's decompilation (system of record: Ghidra project 'grim')
 -> tools/build_src.py     src/<prog>/<module>.c, crt.c = named runtime, crt_unnamed.c = unnamed leftovers
 -> tools/gen_asm.py       functions that cannot be compiled faithfully are re-assembled (src/<prog>/asm_funcs.s)
 -> build/link.py          objects + overrides + host libs; crt.o is NOT linked; unresolved symbols -> trap stubs
```

`names/lib_replace.json` (new) takes functions out of that pipeline: `build_src.py` puts their C text under `#if 0`,
`gen_asm.py` never assembles them, and `link.py` adds one-jump thunks (`jmp *__imp_<msvcrt name>`) for the unnamed or
mis-named ones (`aliases`) and `-lz` for the zlib category. `python -I tools/lib_audit.py build/obj/<PROG>/<file>`
answers "which functions of the linked image can run at all" (call graph from the disassembly of the final PE, data
tables followed only when something live references them); it found the dead set and, as a by-product, the trap stubs
that live code still reaches.

## 2. C runtime, per group

Counts are functions of the Ghidra project (named runtime functions + unnamed leftovers in the runtime's address
range). "Host" = resolved from msvcrt.dll at link time.

| group | EXE (0x4ac550-0x4bd29f, 0x4d5430-0x4d61ff) | LUA.DLL (0x1000ef80-0x10021fff) | IMUSE.DLL (0x1000b900-0x100147ff) | CHORE.DLL (0x10005f50-0x1000dbff, plus 4 above it) |
|---|---|---|---|---|
| string / memory (strncpy, strchr, strrchr, strncmp, memmove, _stricmp, strtok, _strupr/_strlwr, strstr, wcslen, ...) | 18 named | 27 | 1 | 7 unnamed |
| printf engine (`_output`, `_flsbuf`, `_stbuf`, `write_*`, `__strgtold12`, `_cftoe/f/g`, `_fltin`, ...) | 28 | 29 | 0 (1 `_output` unnamed) | 1 |
| scanf engine (`_input`, `_inc`, `_whiteout`, ...) | 5 | 5 | 0 | 1 (`_input`, forwarded to msvcrt `sscanf` by `build/overrides.c`) |
| stdio / low-level I/O (`fopen`, `fread`, `_sopen`, `_read`, `_write`, `_lseek`, `_commit`, `_findfirst`, `getenv`, ...) | 64 | 31 | 20 | 0 |
| malloc / heap (`malloc`, `free`, `__sbh_*` small-block heap, `_heap_alloc`, `_callnewh`) | 16 | 17 | 13 | ~25 unnamed (own heap) |
| math / x87 (`_ftol`, `_CIpow`, `_pow`, `floor`, `ceil`, `_frnd`, `_ctrlfp`, `_handle_exc`, `_except1`, `_aulldiv`, ...) | 13 | 17 | 0 | 0 |
| time (`time`, `mktime`, `localtime`, `_tzset`, `_isindst`) | 9 | 7 | 0 | 0 |
| locale / ctype / mbcs (`_isctype`, `tolower`, `__crtLCMapStringA`, `GetLcid*`, `wctomb`, ...) | 11 | 18 | 4 | ~6 |
| start-up / exit / abort (`entry`, `exit`, `doexit`, `_initterm`, `_amsg_exit`, `_NMSG_WRITE`, `raise`, `terminate`) | 19 | 16 | 9 | 1 (`entry`) |
| SEH / C++ EH / setjmp (`_global_unwind2`, `_local_unwind2`, `__CxxFrameHandler`, `FindHandler`, `_setjmp3`, `longjmp`) | 17 | 17 | 0 | 0 |
| locks / thread data (`_lock`, `_lock_file`, `_getptd`, `_initptd`) | 8 | 6 | 2 | ~3 |
| qsort / bsearch / rand / atoi / strtol | 6 | 5 | 3 | 3 qsort + 1 bsearch |
| LUA.DLL only: `system`, `remove`, `rename`, `tmpnam`, `_Strftime`, `_spawn*`, `_access`, `_mtinit`, `_ioinit`, `_cinit`, `__lc_*` | | 38 | | |

Code kind: in the EXE the runtime is C (decompiled) except 21 functions that were assembly-mode before this work (57);
LUA.DLL 61 assembly-mode runtime functions before, 5 after; IMUSE.DLL 34 before, 4 after; CHORE.DLL 149 before
(it is assembled completely, `names/asm_extra.json`), 0 after. Every named runtime function (`crt.c`) is C text that
is never compiled into the program.

### 2.1 What happened to each group

| group | status before | status now | risk of the system version (exact differences) |
|---|---|---|---|
| strings / memory (`strncpy`, `strchr`, `strrchr`, `strncat`, `memmove`, `_stricmp`, `strstr`, `toupper`) | named ones host; unnamed copies live in CHORE.DLL, IMUSE.DLL (`Im_StrChr` is strrchr, `Im_MemCopy` is strncpy), LUA.DLL (strstr), EXE (strncat) | all host. Verified bit-identical by running the ORIGINAL machine code against msvcrt on 0.3-0.5 million random inputs (build/perf tools, section 6). | `memcpy` with overlap: the original (and mingw's host) `memcpy` entry is a `memmove`; no difference. `_stricmp` returns the byte difference, the copies returned -1/0/1: only the sign leaves the function (wrapper in `overrides.c` where a caller declares `char`). Locale: both are the "C" locale (nothing calls `setlocale`). |
| printf engine | named host; the EXE's assembled `_snprintf` + `_output` (the original engine, calling trap stubs `write_char`...) and IMUSE.DLL's `_output` (behind `ImPrintf`) were live | host `_snprintf` / `vsprintf` | `%f/%e/%g` of a double: msvcrt.dll prints the same digits as the old CRT for at most 17 significant digits; beyond that the old CRT pads with zeros and the Windows 11 msvcrt prints exact digits. `%.14g` (Lua `tostring`) never reaches that. Only log/debug text uses the replaced engines. The Lua number formatter was already the host's before this work and is unchanged (probe lines P1-P23 identical). |
| scanf engine | `_input` forwarded to msvcrt `sscanf` (override) | unchanged; CHORE.DLL's wrapper chain removed, `sscanf` called directly | none (same call as before) |
| stdio / I/O | host | host; the live trap stubs (`_flush`, `_ftell_lk`, `_dosmaperr`, `_write_lk` ...) are gone; `_dosmaperr` (not exported by msvcrt.dll) is a small table in `build/win32_shims.c` | the FILE structures come from msvcrt, so the original IMUSE `fseek/fwrite/fclose` could only ever work with msvcrt's layout; now they are msvcrt's |
| malloc / heap | host (EXE, LUA, IMUSE); CHORE.DLL had its own sbh heap | host everywhere (CHORE's heap became unreachable) | alignment: msvcrt returns 8-byte aligned blocks, MSVC 6's sbh 8 as well (16 with the Windows heap on x64 only). Zeroing: `malloc` never zeroes, `calloc` does, same as before. Cross-module `free`: all four modules use msvcrt.dll's single heap, so a pointer may be freed by any of them. |
| math / x87 | `floor/ceil/_ftol/_CIfmod/_CIasin/_CIacos` assembled or decompiled copies, `_CIpow/_pow` already forwarded to msvcrt | host, except `_ftol` in the EXE | `floor`, `ceil`, `fmod`, `_ftol`: IEEE-exact operations, bit-identical (4 million random inputs, all special values; section 6). `pow`/`asin`/`acos`: libm quality, result is stored in a float by Lua. x87 control word: the game sets precision/rounding words itself (`Services_SetCurrent`); msvcrt's `floor` etc. do not depend on them. The EXE's own `_ftol` stays peepholed (`fisttp`, SSE3). |
| time / locale / ctype | host | unchanged | the four ctype table wrappers of the Lua lexer remain (13 lines each, table lookups on the original static C-locale table) |
| start-up / exit / SEH / C++ EH | host start-up (`WinMainCRTStartup`, `startup.c`); the original `entry`, `_cinit`, `_ioinit`, `__sbh_*`, `signal`, `_amsg_exit` chains were dead | removed (dead) | the 6 compiler-generated C++ unwind funclets and `__CxxFrameHandler` thunk of the game code stay: they are game code |
| setjmp / longjmp | `longjmp` host, `_setjmp3` the original assembly | both host | same `_JUMP_BUFFER` layout ('VC20' cookie, 16 dwords); mixed original/host pairs were the risk, not the replacement |
| qsort / bsearch | EXE/LUA/IMUSE: host (since the first runnable build); CHORE.DLL: original | CHORE.DLL `bsearch` host (bit-identical on 100000 arrays), CHORE.DLL `qsort` **kept** | **msvcrt's `qsort` and the MSVC 6 `qsort` give different orders for equal keys** (measured: 18673 of 20000 random arrays with ties differ). The EXE has used msvcrt's `qsort` since the first runnable build (mesh depth sort `rdCache`, registry names); a tie-sensitive difference there is possible but never observed (pixel comparisons of 12 sets: only animation phase). |
| `rand/srand` | LUA.DLL's own copy over a zeroed `ptd` block: first `rand()` after start-up used seed 0 | host `rand/srand` (default seed 1 like the original) | same LCG (`x*214013+2531011`, `>>16 & 0x7fff`). **Changes the sequence of unseeded `random()`** relative to the previous rebuild (to the original's) |

Net effect on the binaries: `.text` EXE 932496 -> 905424 bytes (the system zlib is linked in again), LUA.DLL 105184 -> 75168,
IMUSE.DLL 121376 -> 77712, CHORE.DLL 50464 -> 21488. Trap stubs reachable from live code (`tools/lib_audit.py`): before, the
EXE's `_filwbuf` plus the `_output` helpers (bound to LUA.DLL's exported stubs) and 7 in IMUSE.DLL; now 3 in the EXE (data-table
fragments of the `_pow` special cases, only reachable from the original `_pow`, which msvcrt replaced), 2 table entries in CHORE.DLL, 0 elsewhere.

## 3. zlib

| item | value |
|---|---|
| where | `GRIMFANDANGO.EXE` 0x4c6040-0x4cb9ff: 53 functions (deflateInit2_/deflate/deflateEnd/deflateReset, inflateInit2_/inflate/inflateEnd/inflateReset, crc32, the tree/huffman/inflate_blocks/inflate_codes/inflate_trees/inflate_fast internals, zcalloc/zcfree), version string "1.1.3". LUA.DLL, IMUSE.DLL and CHORE.DLL contain no zlib. |
| used by | only the save game / temp-save layer: `gz_open/gzread/gzwrite/gzseek/gzclose` (the game's own gzio.c, file I/O routed through its `zfilio` service table), reached from `Engine_SaveGame/LoadGame`, `SaveGame_LoadThumbnail`, `IMuse_SaveToTemp`. The LAB archives, textures and movies are NOT zlib (LAB = plain archive, bitmaps = `stdCompress` LZSS, movies = Smush). |
| kept | the gzio layer (`gz_*`, 15 functions): it owns the `z_stream` (same 56-byte layout in 1.3.2, version string "1" passes `inflateInit2_`'s check) and the game's file service table |
| replaced by | `libz.a` of `mingw-w64-i686-zlib` 1.3.2 (`pacman -S mingw-w64-i686-zlib`), linked with `-Wl,-Bstatic -lz`. `GRIM_BUNDLED_ZLIB=1` (with regenerated `src/`) builds the old one again. |
| equivalence | inflate: same output for any valid stream (all 76 original saves load, `build/perf/oldsaves.py`). crc32: same value. deflate: **not byte-identical**: zlib 1.3.2's deflate makes different (equally valid) block/matching decisions than 1.1.3, so a rebuilt save differs in its compressed bytes (typ. 860 KB vs 877 KB for the same 2.78 MB payload, uncompressed content identical) and decodes identically with both zlibs and with Python `gzip`. Raw deflate (`-MAX_WBITS`), memLevel 8, default level 6 as before. Allocation: `zalloc = 0` so zlib uses msvcrt `malloc/calloc` (the old `zcalloc` was `calloc`). |
| risk | low; deflate output differences are invisible to the game |

## 4. Other libraries and library-like code (candidate list)

Risk is the risk of replacing it with a system component while keeping bit-for-bit behaviour; "no" means no
system library implements the same thing.

| code | where (range, functions, kind) | system replacement | behaviour difference / why risky | verdict |
|---|---|---|---|---|
| **Lua 3.1 VM** | LUA.DLL 0x10001000-0x1000ef7f, ~300 functions, mostly C (about 100 assembled) | none (a stock Lua 3.1/5.x would not load the game's chunks/saves) | modified bytecode, `lua_Save/Restore`, tag methods | **excluded by the owner**; unchanged |
| GIF decoder | EXE `stdgif.c` 0x47db00-0x47ec40, 12 fns (2 asm): LZW decoder + palette | WIC (`windowscodecs.dll`) / GDI+ | game wants an 8-bit palette image with its own transparent index and interlace order; WIC converts pixel formats; frame/palette quirks | medium-high, no gain |
| PCX decoder | `stdpcx.c` 0x47b710-0x47ef10, 5 fns | none in Windows (WIC has no PCX) | - | no |
| BMP loader | `stdbmp.c` 0x47cb20, 3 fns; `stdbitmap.c` 0x473630-0x47b5f0, 17 fns (format dispatch, colour maps) | GDI `LoadImage` / WIC | palette order, bottom-up rows, the game's own `.bm` format is not BMP | medium |
| ILBM/LBM decoder | `stdlbm.c` 0x47f120-0x47fc80, 5 fns | none | - | no |
| `stdCompress` LZSS | `stdfileutil.c` 0x473a00 `stdCompress_Decompress/DecompressLoop`, 2 fns | none (not zlib, not LZNT1) | LucasArts' own LZ variant; the intermittent write-past-end after Load was seen here | no (do not replace) |
| LAB archive reader | `lab.c` 0x480120-0x482020, 12 fns; `labdir.c` | none | custom container (`LABN`); uses CRT stdio | no |
| Smush/Insane movie player + codecs | EXE `smush.c`, `insane.c`, `sputsmush.c`, `smushcomponent.c`, LecShare module chain, ~30 fns (5 asm), `Insane_Blit*` | Media Foundation / DirectShow | `.snm` is a proprietary stream (video codecs 1/2/..., VIMA audio), timing is driven by the engine | no |
| VIMA ADPCM + iMUSE mixer | IMUSE.DLL `Im_VimaDecompress`, `Im_VimaDecodeBlock`, `Im_CodecInit`, `Im_ConvertBlock`, `Im_MixLoopA-D`, 0x10001000-0x10006000, ~40 fns | Windows ACM IMA-ADPCM (`imaadp32.acm`) | VIMA is a variable-bit-width IMA variant, not ACM-compatible | no |
| software mixer | EXE `mixer.c` 0x4c0ed0-0x4d40d0, 21 fns (20 asm): voice mixing into a DirectSound stream buffer | XAudio2 / WASAPI mixing | rounding/clipping of the mixing loops is part of the sound | high, no |
| RDroid software rasteriser | EXE `rdraster.c` 0x40ea50-0x4710e0, 372 fns (all asm), `rdclip`, `rdprimit*`, `rdcanvas` | Direct3D / OpenGL | pixel-exact output, x87 floor/ceil edge set-up | no |
| DirectX wrappers | EXE `stddisplay.c` 60 fns, `std3d.c` 35, `stdinput.c` 22, `mixer.c` DSound part | system `ddraw/dinput/dsound/d3d` (already the case: they ARE the system libraries, called through COM) | - | already system |
| HMI SOS FX (`HMIFXLIB.DLL`, `HMIFXFP.DLL`) | 3rd-party DLLs next to the game, import libraries generated by `build/hmi/` | none | binary-only | n/a |
| registry / dialogs / file dialogs | `reg.c` 15 fns, `plat.c`, `dlg.c` | Win32 `Reg*`, `GetOpenFileName` (already used) | - | already system |
| directory scan / file find | `dirscan.c` 4, `stdfileutil.c` 18 (`FindFirstFile` wrappers), `_findfirst` (host) | Win32 | - | already system |
| wildcard / case-insensitive strings | `string.c` 14 fns (`Str_WildcardMatch` 0x4c1c30, `Str_CompareNoCase`, `Str_StripNonPrintable`) | `PathMatchSpecA` (shlwapi), `_stricmp` | glob semantics (`*?`, case, '/' vs '\\') differ in corners | low gain, medium risk |
| memory manager | `memory.c` 12 fns, `stdmemory.c` 4 | `malloc` (it already wraps it) | guard words, pool statistics | n/a |
| math helpers | `math.c` 11, `math3d.c` 36 (vector/matrix), `Math_Floor` etc. | DirectXMath / `<cmath>` | float rounding order differs; the code is tuned for x87 evaluation order (GetShrinkPos failed when reordered, BUILD_NOTES) | high |
| Win32 time / timers | `timer.c`, `clock.c`, `sputtime.c` | system (already `timeGetTime`, `time`) | - | already system |
| localisation tables | `polyglot.c` 2 fns | none | game data | n/a |
| debug log text engine | `debuglog.c` 8 fns, `Svc_Printf*` | `vsprintf` (already) | see printf row | already host |
| LecShare module registry | `lecshare.c` 14 fns | none | LucasArts component system | no |
| phoneme / lip-sync | `phoneme.c`, `grimSound_LipSync*` | none | game data format | no |

No JPEG, MPEG or Huffman code exists in any of the four modules; the only general-purpose compressors are zlib
(saves) and the `stdCompress` LZSS (bitmaps); the only audio codec is VIMA.

## 5. Findings that changed results (all found by differential tests against the ORIGINAL code or by the audit)

1. **Ghidra's `floor` and `ceil` in LUA.DLL are swapped** (0x10011ef0 is really `ceil`, 0x10011ff0 `floor`; the callers
   are swapped consistently, so the game was right). Replacing by name would have inverted every Lua `floor`/`ceil`;
   `names/lib_replace.json` aliases `_floor` -> msvcrt `ceil` and `_ceil` -> msvcrt `floor`. Names left unchanged in Ghidra.
2. **IMUSE.DLL `Im_StrChr` is `strrchr`** (the structural match said `strchr`: it scans backwards), `Im_MemCopy` is
   `strncpy`, `ImFile_Read/Open/Close` are `fseek/fwrite/fclose` (used by the recording code, `ImStartRecording`),
   `FUN_1000ba60` is `fopen`, `FUN_1000b8d0` is `vsprintf`, `FUN_1000c0a0` is `toupper`. CHORE.DLL's `FUN_100055a0`
   strncpy, `FUN_100056a0` strrchr, `FUN_10005e90` strchr, `FUN_10005860` memmove, `FUN_10005de0` bsearch,
   `FUN_10005ba0` qsort, `FUN_10005740` `_stricmp`. LUA.DLL `FUN_100129a0` is `strstr`, `FUN_10012350/60` are `srand/rand`;
   the symbols `_CIsqrt` (0x10011d50) and `_sqrt` (0x10011d6d) are really `_CIasin`/`_asin`, `FUN_10011e20` is `_CIacos`.
   EXE `FUN_004ae410` is `strncat`, `FUN_004adef0` `fgetws`, `FUN_004d54b4` `_CIfmod`, `FUN_004addf0` `_alloca_probe`,
   `FUN_004c3e10`/`FUN_004d5fd0` are LecShare's own memcpy/memset (not the CRT's).
3. **Lua `asin`/`acos` returned 0** in every earlier rebuild: `asin` called the assembled copy of `_asin` with a lost x87
   argument path, `acos` was a C function that dropped the `luaL_check_number` result in ST0. Fixed by the host
   `_CIasin/_CIacos` and by assembling `FUN_10006f80` (names/asm_extra.json). Not used by the shipped scripts as far as
   the suite shows.
4. **Latent traps** (functions that call trap stubs of the removed runtime): the EXE's `_snprintf` (every `DebugLog_*`
   call would have executed `__builtin_trap` in `write_char`), `fgetws` (service table slot), the file helpers'
   `_dosmaperr`. All now go to msvcrt or to a real implementation.
5. **`rand()` start seed**: the shim `_getptd` returns a zeroed block, so LUA.DLL's copy of `rand` started from seed 0, the
   original from 1; the host `rand` restores 1 (after `randomseed(n)` the sequences are identical, probes R2/R3).
6. **qsort is not interchangeable** (section 2.1).
7. **Windows' msvcrt.dll does not export `_alloca_probe` or `_dosmaperr`** (they stay: assembly resp. a table in
   `win32_shims.c`).

## 6. How equivalence was shown

* `build/perf/libcheck.py`: boots to Manny's office with a fixed 17 ms frame, runs Lua probes (23 numbers through
  `tostring`, 10 `format` conversions, floor/ceil/sqrt/mod/pow/trig/log/exp, asin/acos, random, string functions,
  `tonumber`), a walk, 5 set switches, a Save/Load round trip and the engine's debug log; the text of two builds is
  compared line by line, shots pixel-wise. `--movie` plays `funny.snm` to the end.
* differential tests of single functions: the original code (from the rebuilt baseline DLLs, or the bytes of
  `raw/GRIMFANDANGO.EXE/sections/text.bin` executed from a VirtualAlloc'ed page) against msvcrt.dll on random inputs:
  floor/ceil/_ftol 4 000 000 inputs (all doubles incl. NaN/inf/denormals/-0): 0 differences; `_CIfmod` 3 000 000: 0;
  strncat 500 000: 0; strchr/strrchr/strncpy/_stricmp/memmove 200 000-300 000 each: 0; bsearch 100 000: 0; qsort: differs on ties.
* the project suites (`grim_tools/autorun`: unit 120/0, walk 88/0, move 192/0, coll 308/4 (the known four), misc 80/0, rules 786/0) and the 76 saves of the original game (`oldsaves.py`).
