# IMUSE.DLL, the last four assembled functions (agent r1, 2026-11-09)

Base: main at 85dd22f (4 IMUSE.DLL functions assembled, cleanroom 5107 of 5107).  Result: **nothing of IMUSE.DLL is assembled
any more.**  Three functions are hand-written C (differential test against the original machine code: 0 differences in
1,000,000 cases, -O0 as link.py compiles and -O2), the fourth (`hmi__bae0`, MSVC `_ftol`) is dead code and dropped.
Cleanroom: **5107 of 5107 the same**.

Files:

* `build/overrides_imuse_r1.c`: the C (GRIM_IMUSE), one `/* OVERRIDES: name */` line before each definition.
* `build/difftest/imuse_r1/`: `r1_test.c` + `thunks.s` + `build.sh` (differential test), `mutate.sh` (sensitivity check),
  `frametrace.py` + `ftrun.sh` (gdb: stack words at the entry of FUN_100068b0 and the calls it makes, in the game; `aud` mode
  runs the PCM oracle `build/perf/imuse/audtrace.py`), `audcmp_r1.py` (PCM trace comparison).
* `names/asm_funcs.json` (IMUSE.DLL list now empty), `src/IMUSE.DLL/asm_funcs.s` (bodies stripped with
  `build/difftest/asm_p2/strip_asm.py`), `names/lib_replace.json` (`1000bae0` added to IMUSE.DLL `dead`),
  `names/imuse_asm_reasons.json` + `tools/gen_asm_remaining_imuse.py` (a `_done` note printed when nothing is left),
  `docs/ASM_REMAINING_imuse.md` regenerated, a pointer line in `docs/notes/imuse.md`.

## Converted

| address | name | what it does | verification |
|---|---|---|---|
| 10006560 | FUN_10006560 | ImSetState (dispatcher command 5): look up the state id (181 entries at 0x100172e8), print its name, start the transition unless a sequence plays, return the current state's id | 199,559 of the 1,000,000 cases, 0 differences |
| 10006620 | FUN_10006620 | ImSetSequence (command 6; 0 = 2000 = end of sequence): queue behind a type-4/6 sequence, start the pending one, or return to the state's music | 200,546, 0 |
| 100068b0 | FUN_100068b0 | the transition: sound name (alias table 0x1001bbc8), hook counter, fade-out of non-stream group-4 sounds, find the playing music stream, then the 13 transition types (switch now, at the marker "exit"/"exit2" through triggers, fade, hooks, end-of-sequence callback trigger) | 199,344 direct + every call from the two above, 0 |
| 100064d0 | FUN_100064d0 | (was compiled from the decompiler's C) end-of-sequence check once per frame; hand-written because its second call of FUN_10006620 has another ESI (below) | 400,551, 0 |
| 1000bae0 | hmi__bae0 | MSVC `_ftol`: no caller left (the two calls were in Im_MixerInit, C since agent N), no pointer to it in the data image (no `0x1000bae0` dword in the original file, no relocation in `data_s.o`): `names/lib_replace.json` IMUSE.DLL `dead` ("nothing, for dead code") | `tools/lib_audit.py`: not in the rebuilt image, nothing unresolved |

## The "parameters 4..8" of FUN_100068b0

Ghidra declared FUN_100068b0 with 8 parameters and showed parameters 4..8 (the words above the 3 pushed arguments) as the fade
time of ImSwitchStream and the hook values of ImSetHook; agent N kept the three functions assembled for that reason.  The
disassembly says otherwise: every `[esp+0x2c]` / `[esp+0x20]` read after a call is taken while the call's pushes are still on
the stack (MSVC pops late), so they are the function's own slots of arguments 1 and 2, which it reuses as locals (slot 1 = the
hook value, slot 2 = the fade time).  **FUN_100068b0 reads only its three arguments.**

Measured in the game (`ftrun.sh`, scenarios `build/perf/imuse/scn_3.lua` (ten state changes) and `scn_9.lua` (states and
sequences); the rebuilt EXE / LUA / CHORE with (a) the original IMUSE.DLL of the game folder, loaded at its preferred base
0x10000000, (b) the 85dd22f build, (c) this build):

* words 4..8 at the entry of FUN_100068b0: original `EDI-of-dispatcher, 0xffffffff, 0x1000625f / 0x1000629d (return into the
  dispatcher), the state / sequence id, a dispatcher frame word`; 85dd22f build `1, 0x11, ...` for states and
  `0x102eed4c, 0, ...` for sequences (the gcc dispatcher's EDI / ESI).  Agent N's "1, 0x11" were measured in a rebuilt DLL.
* the calls FUN_100068b0 makes (ImStartStream / ImSwitchStream / ImFadeParam / ImSetParam / ImSetHook with their arguments):
  scenario 9 identical in all three (68 calls); scenario 3 identical between (b) and (c) (62 calls), and (a) gives 57 calls in
  two runs: after `ImSetState(1000)` (fade out over 0x78) and 250 frames, the original DLL still finds the old music stream at
  `ImSetState(1001)` and fades it back in, both rebuilt DLLs find none and start it anew.  That is the state of the sound
  engine (ImGetNextSound / ImGetParam answers), not these functions (the same in the build where they are still the original
  machine code); a pre-existing difference of the rebuilt DLL or of its timing under gdb, not followed up here.

What does read the stack beyond the pushed arguments is **ImSetTrigger**: it stores its 13th argument word (p9) in all ten
parameter words of the trigger (`build/overrides_imuse.c`), and FUN_100068b0 pushes 3 to 8 of the 13.  The 13th word then lies
at a place fixed by the number n of pushed words:

| n | word | value in the original | calls |
|---|---|---|---|
| 3 | [entry+0x14] = the caller's saved ESI | the ESI register of FUN_10006560's / FUN_10006620's caller: 0xffffffff from the dispatcher (`or esi,-1` in its prologue, also at FUN_100064d0's first call, which keeps the dispatcher's ESI), 0 at FUN_100064d0's second call (its loop variable) | types 4, 6, 9 (command 0 = the script callback) |
| 5 | [entry+0x0c] | argument 3 | 0xf (set hook) of types 10-12, "clear" of 12 |
| 6 | [entry+0x08] | slot 2 = the fade time | 0xc (set param) of 10-12 |
| 7 | [entry+0x04] | slot 1 = the hook value | 0xe (fade param) of 10-12 |
| 8 | [entry] | FUN_100068b0's return address: 0x100065f3, 0x100066eb, 0x1000672c, 0x10006778 | 0x1a (switch stream) of 10-12 |

The C passes these values explicitly (`FUN_100068b0(entry, index, no_attr, caller_esi, ret_word)`; `Im_SetSequence(id,
caller_esi)` behind FUN_10006620), so the triggers store what the original stored.  The 85dd22f build stored the gcc
frames' contents instead (0x11 / 0 for the n = 3 triggers, an address of the rebuilt DLL for n = 8).  The words between the
pushed ones and p9 are not read by ImSetTrigger; the C passes 0.  All of this is dormant in the game: the shipped tables hold
only transition types 0, 2 and 3 (state table 93 x 2, 85 x 3, 3 x 0; sequence table 40 x 2, 1 x 0; read from the DLL file),
and nothing else calls these functions with other entries.

Prototype change: FUN_100068b0 has 5 parameters (above); the functions.h prototype is renamed while it is included.

Behaviour kept from the original that looks odd:

* Transition type 1 prints "bogus trans type" like any value > 12 (the jump table sends 1 there); type 5 does nothing.
* Type 6 sets a trigger on the sound id 0xbc6150 (a constant in the code).
* The hook counter: `field44 > 1` (signed) with a zero counter sets it to 2, otherwise counter + 1, wrapped to 1 above field44;
  the counter slot is field40 if set, else the state index (no bounds check).
* The fade step is `(fade * 3) / 50` with a 32-bit wrap of `fade * 3` and signed division.
* The attribute-match path calls ImSetHook(snd, 100) only when the hook value is 100.
* The sound name is copied with strcpy semantics from the entry's 0x20-byte field (it runs on if the field has no NUL).

## Differential test

`build/difftest/imuse_r1/build.sh` slices FUN_10006560 / FUN_10006620 / FUN_100068b0 from `git show
85dd22f:src/IMUSE.DLL/asm_funcs.s` (renamed orig_*; their return addresses after the calls of FUN_100068b0 are exported as
`_orig_ret_<original address>`), links the C compiled with link.py's override flags, the original data image
(`build/obj/IMUSE.DLL/data_s.o`) and `thunks.s`: the original callers' frames (ESI = 0xffffffff and a random EDI as in the
dispatcher; for FUN_100068b0 direct, the two caller words at entry+0x10 / +0x14 and a known return address) and FUN_100064d0
transcribed from the original DLL (it has no copy in the base assembly).  Stand-ins log every iMUSE call (ImSetTrigger: sound,
marker text, command, the pushed words and p9, an orig_ret_* address mapped to the original one) and answer from a random
per-case model (sound list, parameters, ImOpenSound / ImStartStream results).  Each case re-randomises table entries (all 16
transition types and invalid ones, counters, fades, names with and without NUL, alias records), the globals 0x1002df00..
0x1002e400 and the flag at 0x1001e688, and compares the return value, the call log and those globals.

```
build/difftest/imuse_r1/build.sh && build/difftest/imuse_r1/out/r1_test.exe 1000000 1
cases 1000000: FUN_10006560 199559, FUN_10006620 200546, FUN_100064d0 400551, FUN_100068b0 199344
ImSetTrigger: 51261 calls, 2881 with p9 = a return address of FUN_10006560/10006620, 18606 command-0 triggers (p9 = caller ESI), 104 of them with ESI 0
FUN_100068b0 entry types 0..14,other: 5306 3702 56216 30830 3766 3885 3889 3835 3692 3801 6432 6386 6362 3896 0 7485
0 differences
EXTRA_CFLAGS=-O2 build/difftest/imuse_r1/build.sh build/difftest/imuse_r1/out/r1_test_o2.exe && .../r1_test_o2.exe 1000000 2
... 51371 calls, 2836 ..., 18477 ..., 113 ...   0 differences
```

Mutation check (`mutate.sh 200000`), each caught: return word 0x100065f3 -> 0x100065f4 (232 differences), ESI 0 -> -1 at
FUN_100064d0's second call (32), step / 50 -> / 49 (27878), `hook == 100` -> `== 99` (2), the n = 6 word fade -> hook (1280),
the "clear" trigger's word no_attr -> fade (426), `field44 > 1` -> `>= 1` (303), type 5 no longer a no-op (1363).

## Music in the game (PCM oracle)

`ftrun.sh <run> <tag> build/perf/imuse/scn_{3,9}.lua aud` (agent N's `audtrace.py`: CRC and peak of every 0x1800-byte block
Im_DSoundHeartbeat commits to DirectSound), two runs each of the 85dd22f build and this build, `audcmp_r1.py`:

* scenario 3 (ten state changes): 893 blocks compared, the two baseline runs identical, both runs of this build identical to
  them (0 blocks differ, nothing masked).
* scenario 9 (states and sequences): 822 blocks, the same: 0 differences.

## Commands and results

```
rm -f src/*/*.[ch] src/*/*.md && python -I tools/build_src.py && make -C build -j8 && make -C build link
python -I tools/lib_audit.py build/obj/IMUSE.DLL/imuse.dll --orig-exports raw/IMUSE.DLL/exports.json   (none of the four dead, hmi__bae0 absent)
python -I tools/gen_asm_remaining_imuse.py                                   0 assembled, 0 without a reason
cd grim_tools/cleanroom && GRIM_DECOMP=<worktree>/build/run python run.py decomp
    0 of 5107 tests differ, 0 are close (within 0.001), 5107 the same
```

Side effect in generated sources: `tools/build_src.py` collects override names for all programs, so CHORE.DLL's own (dead)
FUN_100064d0 / FUN_100068b0 now carry the "replaced by the hand-written version" comment instead of the lib_replace one; the
code stays under `#if 0` and chore.dll is unchanged apart from the section layout every new override object causes.
