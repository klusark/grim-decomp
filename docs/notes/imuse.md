# IMUSE.DLL: from assembly to C (agent N, 2026-10-30)

Starting point: all 243 functions of IMUSE.DLL that `tools/gen_asm.py` selects were assembled from Ghidra's disassembly
(`names/asm_extra.json` listed 281 IMUSE addresses; no per-function artifact analysis had ever been done).  End point:
**4 functions assembled** (list and reasons: `docs/ASM_REMAINING_imuse.md`), 13 hand-written in `build/overrides_imuse.c` (reasons below)
and the rest compiled from the decompiled C.

## How a function was moved

* `names/asm_exclude_imuse.json` (read by `tools/gen_asm.py` with every `names/asm_exclude*.json`) lists the addresses compiled
  from the decompiler's C.  A function defined at top level in `build/overrides_imuse.c` replaces the decompiled one (and the
  assembled one) by itself.
* Regenerate: `python -I tools/gen_asm.py IMUSE.DLL --select && python -I tools/build_src.py && cd build && make link -j14`
  (IMUSE only: `make objs`, then `python -I link.py /mingw32/bin/gcc ../src obj IMUSE.DLL`).
* Ghidra edits: `names/imuse_protos.json` + `tools/set_imuse_protos.py` (prototypes), `tools/type_pointer_globals.py` (pointer globals).

## Root causes found (every one of them compiles fine and breaks at run time)

1. **Pointer globals typed `undefined4` in Ghidra** (`tools/type_pointer_globals.py` was never run for IMUSE.DLL).  Ghidra prints
   `*(int *)(DAT_1002dcf8 + 8)` / `(int *)(DAT_1002df5c + param_4 * 8)` with *byte* offsets when the global is an integer;
   `tools/build_src.py` declares the global `int *` (it is assigned from pointers) and C scales the offsets by 4.  Hit:
   `DAT_1002df5c` (the mixer accumulator: 0x3000 bytes, written at a 32-byte instead of 8-byte stride = up to 36 KB behind it),
   `DAT_1002dcf8` (the sound-file list), `DAT_10024dc8`, `DAT_10025298`.  Fix: the four globals are `int *` in Ghidra
   (`raw/IMUSE.DLL/ptr_types.json`), the functions were re-exported (they now read `PTR_1002df5c + param_4 * 2`).
   Measured by putting the old types back: the rebuilt DLL still boots and passes the unit tier (the stray writes land in
   unused heap), but the mixed PCM differs from the original from the 20th block on.  The heap overflow is what agent J
   saw as "out-of-bounds write while a set loads (colormap/raster area)" (the accumulator is on the same heap): it moves around
   with the heap layout, so it crashes in one build and is silent in another.  The other two causes below crash at once
   (stack pointer), whichever functions are converted.
2. **DirectSound COM calls are `__stdcall`.**  The decompiler's `(**(code **)(*obj + 0x4c))(obj, ...)` is compiled cdecl: the
   caller pops the arguments a second time and ESP runs away by 4 * argc per call (crash within the first heartbeats, the stack
   then contains the text "imuse.psl").  `Im_DSoundHeartbeat` and `Im_DSoundShutdown` are written with the `COM()` macro
   (`build/overrides_imuse.c`); `Im_DSoundCreateBuffer` and `iMUSE_dsound__3a80` already were.
3. **The HMI sound library imports (`hmiFXInitSystem`, ...) are `__stdcall`** but `tools/build_src.py` listed the `hmiFX` prefix
   as cdecl (the game's own DLLs are cdecl).  Same ESP drift in `FUN_10004660` (HMI start-up).  Fix in `build_src.py`.
4. **Address literals in arithmetic.**  `return param_1 * 0x10 + 0x1002ebe0;` (`FUN_10007a80`): `fix_image_addrs` leaves a literal
   next to an operator alone, but a DLL is not loaded at 0x10000000 and the table lives in the rebuilt `.data`.  Hand-written
   with `IMG_ADDR`.  (Scan of all compiled IMUSE functions for other such literals: none left.)
5. **Wrong decompilation of stack arguments** (MSVC pops the arguments of a call late: `add esp` after the next instruction, so
   `mov ecx,[esp+0x14]` right after a call is an argument of the caller, but the decompiler counted the pending pop):
   `SoundStartVoiceStream(name, volume, pan)` (volume/pan were swapped and the pan read from a non-existent 4th argument),
   `FUN_100070e0` (marker read from the wrong argument).  Found by comparing the PCM traces below, then by reading.
6. **Lost sign extension**: `Im_MixLoopC` / `Im_MixLoopD` (big-endian 16-bit samples) printed `(int)CONCAT11(lo, hi)`, which is unsigned;
   the code does `movsx eax, ax` after the byte swap.  Negative samples came out as 65536 - |x|: the mix was twice as loud (peak 24114
   instead of 11812 in the first blocks of the set-switch scenario).  Hand-written with a signed byte-swap helper.  Found by the
   PCM trace (the unit tiers cannot hear it); the same CONCAT pattern in the other converted functions only stores unsigned values.
7. **Lost x87 values**: `Im_MixerInit` (two lookup tables: pan weights and volume curve) is written from the disassembly with
   `long double` arithmetic; `hmi__bae0` is MSVC's `_ftol` (argument in ST0).
8. **Wrong prototypes**: `Im_DSoundHeartbeat` has three parameters (out: block pointer, dword count, sample rate), the trigger /
   deferred-command layer takes 13 / 12 / 11 parameters (see below).

## The trigger / command layer is compiled from va_arg expressions evaluated in the wrong order

`ImSetTrigger(sound, marker, cmd, p0..p9)` and `ImDeferCommand(time, cmd, p0..p9)` store ten parameter words, `Im_DispatchCommand`
(command numbers 0..0x1d = the Im* API) runs them later.  In the shipped code every one of those calls passes **the same word
for all of its arguments** (the last one of the group): `ImSave(w, w)`, `ImFadeParam(w, w, w, w)`, `ImSetTrigger(w x13)`; the
wrapper passes `p9` ten times.  (The C source evidently used `va_arg(ap, int)` twice in one argument list; MSVC evaluated both after
the pointer had advanced twice.)  Commands 0x11 / 0x14 additionally read the word at `[esp+0x3c]`, four words beyond what the two
callers push (garbage in the original, the last argument here).  The commands therefore mostly do nothing useful; the code in
`overrides_imuse.c` reproduces the arguments exactly and says so.  Do not "fix" it: the shipped music assets were tuned with it.

## What stays assembled (4 functions)

* `FUN_10006560` / `FUN_10006620` / `FUN_100068b0` (script layer: state / sequence transitions): `FUN_100068b0` reads five parameters
  (4..8) that its two callers never push: it takes them from the caller's stack frame (its return address, the caller's own
  argument, and three words of the dispatcher's frame, `FUN_10006070`).  Used as fade time and hook values of the music
  transitions.  Measured in the original at run time (`build/perf/imuse/argtrace.py`): p4 = 1, p5 = 0x11, p6 = a return address inside
  IMUSE.DLL (so the fade argument of `ImSwitchStream` is always clamped to 2000 ms), p7 = the state id (used as a hook value),
  p8 = 0xc0c01d (hook value of the ordinary transition).  They depend on the exact stack layout of the MSVC-compiled callers, so
  these three stay original machine code.
* `hmi__bae0` (`_ftol`, argument in ST0, 64-bit result in EDX:EAX): no C equivalent; no caller is left (`Im_MixerInit` is C now).

## Verification

* The scripted tiers with the converted DLL: unit 120/0, walk 88/0, move 192/0, coll 308/4 (known), misc 80/0, rules 786/0.
* **Audio oracle** (`build/perf/audtrace.py`, run under gdb): CRC and peak of every 0x1800-byte block that `Im_DSoundHeartbeat`
  is about to commit to DirectSound (the final PCM), compared with the all-assembly build.  The boot (3000 blocks = 60 s of game
  time) differs between runs of the *same* build in a few short windows every ~6.6 s (an ambient sound starts one heartbeat
  earlier or later: the original build shows the same four variants), so blocks that differ between baseline runs are masked.
  Scenarios (`build/perf/scn_*.lua`): sound effect with fade / pan / pause / resume / group volumes / voices / voice effect, and ten music
  state changes.
* Function-level differential test (`build/perf/imuse_diff.c`): both DLLs loaded into one process, `Im_VimaDecompress` called with
  7594 original sounds and four NULL-pointer patterns each: identical.
