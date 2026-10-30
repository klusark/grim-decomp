# Smush audio and video, the mixer and the Blocky16 codec as C (0x004bdf00 - 0x004d4100)

All 119 functions of this range that were rebuilt from Ghidra's disassembly are now C: `names/asm_funcs.json` lists none of them
(list: `docs/ASM_REMAINING_mixer.md`, EXE total 638 -> 519).  The C is written by hand from the machine code, not taken from the
decompiler (which lost COM arguments, x87 results and register-passed helpers here), and every part was checked against the
original instructions with a differential test (below).  `tools/build_src.py` puts the decompiled text of every function
that `build/overrides_mixer*.c` defines under `#if 0`, so `src/` still shows what Ghidra printed.

| file | what | functions |
|---|---|---|
| `build/overrides_mixer.c` | software mixer: 8 mixing loops (`#pragma GCC optimize ("O2")`), `Mixer_MixVoice`, `ConvertTo16`, `InitTables`, `Init`, `Free` | 16 |
| `build/overrides_mixer_drv.c` | Smush timer module `InsaneTimer_*`, DirectSound stream driver `DsndDriver_*`, `DSound_*`, memory helpers | 39 |
| `build/overrides_mixer_snd.c` | Smush sound module `SoundModule_*` (voices, tracks, SAUD command interpreter in `SoundModule_MixCallback`), `Sound_VoiceSampleCount` | 29 |
| `build/overrides_mixer_video.c` | pixel format converters of the VIDEO module, `VideoBitmap_Create` / `ConvertPixels` | 17 |
| `build/overrides_mixer_codec.c` | Blocky16 frame decoder, 8x8 / 4x4 / 2x2 block decoders, split masks, option reader | 10 |
| `build/overrides_mixer_misc.c` | AnimPlay (frame player), light editor text field and keyboard hook, `LecShare_Resolve`, zlib `gz_open` glue, StdFile helpers, movie length | 18 |

## How the pieces fit

* **Mixer** (`Mixer_*`).  Voices are added into a 32 bit accumulator (`g_pMixAccum`, interleaved L/R) and
  `Mixer_ConvertTo16` shifts it down (`>> 7`, clamped) into the 16 bit stream.  A voice block is resampled on the fly:
  ratio = `(count << 16) / outFrames`, with special loops for 0x8000 (each source frame twice, the second interpolated), 0x10000 and
  0x20000 and a 16 bit phase accumulator for everything else.  Formats: 8 bit unsigned (`(b ^ 0x80) << 8`, zero extended), 16 bit signed,
  "A" (offset binary) and "B" (byte swapped, zero extended).  Volume and pan come from a 17 x 17 byte table
  (`_DAT_008dcc70`, built by `Mixer_InitTables` with x87 `fsin`, hence the inline `fsin` and `long double`).
* **Timer** (`InsaneTimer_*`).  A thread wakes every 16 ms (`timeGetTime`), and runs up to 19 periodic callbacks (20 slots of 0x20
  bytes at 0x008da5d8, slot 0 unused).  Callbacks may register / remove timers themselves.
* **DirectSound driver** (`DsndDriver_*`, `DSound_*`).  A looping stream buffer of blocks of 0x1800 bytes; the timer callback
  `DSound_FillStreamBuffer` refills the blocks behind the play cursor from the mixer.  COM calls go through `COMX(obj, vtable
  offset, ...)`.
* **Sound module** (`SoundModule_*`).  16 voices (`SndVoice`, 0x34 bytes at 0x008dad58) each own a ring buffer; a chunk (Creative VOC,
  PSAD / PVOC / SAUD) is copied into a free or the least important voice.  The SAUD data is a command stream (1 play a block, 2 / 8 /
  9 / 10 / 11 conditional jumps on variables, 3 set, 4 add, 6 / 7 start a run, anything else ends the voice) run by
  `SoundModule_MixCallback` per `SndTrack` (0x3c bytes at 0x008da8f0), which hands PCM blocks to the mixer function it is given.
* **Video converters** (`Video_*`, `VideoBitmap_*`).  A `VideoBitmap` is a 0x54 byte header (type 0 paletted / 1 RGB / 2 RGB + alpha, bits,
  shifts and loss per channel) followed by pixels.  Conversion runs through RGBA scratch rows of at most 0x500 pixels.
* **Blocky16** (`Blocky16_*`, 0x004cc210-0x004cdb80, module "FlobDec Blocky16", the codec of the 16 bit movies).  Method 2 frames are 8x8
  blocks, each an opcode plus operands: motion copy from the previous frame (00-f5, f5 explicit vector), copy from two frames back (f6),
  two colours and a "split mask" (f7, f8), one colour (f9-fe) or four 4x4 blocks (ff) which in turn can be four 2x2 blocks.
  `Blocky16_BuildSplitMasks` draws a line between two of 16 edge points and fills towards the edge (5 x 5 table of the fill direction by
  the classes of the two edge points); `Blocky16_BuildPixelOffsets` (C already) turns the cell numbers into pixel offsets for the frame
  width.  The block decoders are hand written assembly with a register convention (ESI stream, EDI destination, EBP pitch, state in
  0x00906c48-0x00906c74); in C they take the stream and destination as parameters and return the stream.
* **AnimPlay** (`AnimPlay_*`).  The frame player: a clock timer and a frame timer, `AnimPlay_Update` compares the sound position
  (`Sound_VoiceSampleCount`) with the frame counter (66.67 ms per frame) and lengthens or shortens the frame delay by 1/16 or 1/8 within
  3/4 .. 4/3 of the nominal delay (`1193180 / fps`).  Its services (memory, debug, streamer, frame, timer, lipsync) are tables of function
  pointers asked from the module manager.
* **zlib glue.**  `gz_open` is zlib 1.1.3 gzio.c with file access through the FILIO service and a change: files that are not gzip
  (transparent mode) are refused.  `gz_putLong`, `Zfile_Close`, `StdFile_*` are small helpers.  The save files (`SaveFile_Open`) go
  through `gz_open`.

## Details of the original that the C keeps

* Do-while loops: the leaf pixel converters process one pixel (two for 2 byte pixels) when the count is 0 or odd; the mixing loops
  run 2^32 times for count 0; the split fills write one pixel for a count of 0; the block row / column counters are bytes (0 means 256).
* The 2x case of the 8 bit mono mixers reads `src[2]` while advancing one sample (`U8AVG(src[0], src[2])`).
* Block copies are done one 32 bit word at a time in the original's order (a small displacement overlaps source and destination).
* `FUN_004cfea0` (16 bit index expander) has a doubled prologue and reads its arguments from the wrong stack slots; the C does what it
  was meant to do and the function is left out of the video test.  The 3 byte expanders keep their growing-index bug (only AL / AX of
  the previous index is replaced).
* `VideoBitmap_Create` format 1 stores the pixel pointer as the palette pointer.
* `Smush_GetLengthMs` (was `Smush_SetFile`) returns the 16 bit header field at +2 times 66.67 (a movie length in milliseconds at
  15 frames per second), it does not set anything.  `Mem_DumpLog` is an empty function; callers pass an argument it ignores.
  `zlibVersion` at 0x004c4c40 is really a stub that returns 0 (see its comment); the call in `AnimPlay_OpenFile` was dropped.
* A `ServiceDeferred` setjmp / longjmp pair in the timer module is dead (the second jmp_buf is never initialised) and omitted.
* `Dsnd_MemFill` of the original pops the wrong registers for a count that is not a multiple of 4 (dead code, tested with multiples of 4).
* The light editor's keyboard hook compares the first angle limit on the unrounded sum and the second on the stored float (kept).
* `LecShare_Resolve` copies the module name with `strncpy(local, LecShare_Subscribe(local, n - 1), 99)`: the 99 is left on the stack
  by the `push` before the call of `LecShare_Subscribe`, which only pops 8 bytes.

## Differential tests (`build/mixdiff/`, `run_all.sh`)

`build.sh` cuts the original functions out of the BASELINE assembly (`slice_orig.py`, renamed `orig_<name>`), links them with the
original data image and the C, and a test program runs both from the same random start state: return value, registered memory regions
and the log of every call into recorder thunks (`fx.c`: COM methods, module manager services, imports, callbacks; arguments logged,
return values scripted) are compared.  Stateful code is tested through recorders, not on the real DirectSound.  The tests were
checked for sensitivity with deliberately wrong versions (changed constants, swapped branches, load order of words): each is reported.

| test | covers | cases | differences |
|---|---|---|---|
| `mix_test` | the 8 mixing loops (random buffers, ratios incl. the special ones, volumes, odd counts) | 3000000 (375000 each) | 0 |
| `mixcore_test` | `Mixer_ClearAccumulator`, `ConvertTo16`, `MixVoice`, `MixVoiceByFormat`, `InitTables`, `Init` / `Free` | 1000057 | 0 |
| `timer_test` | `InsaneTimer_*` (slots, counters, self-modifying callbacks) | 300000 | 0 |
| `drv_test` | `DsndDriver_*`, `DSound_*`, memory helpers (fake COM objects) | 300000 | 0 |
| `snd_test` | `SoundModule_*` incl. PlayVoc / PlaySaud / PlayChunk and the command stream mixer callback | 19992 (8 original hangs skipped) | 0 |
| `video_test` | pixel converters, `Video_CopyRect*`, `ConvertPixels`, `VideoBitmap_Create` | 200000 | 0 |
| `codec_test` | `Blocky16_BuildSplitMasks`, `Blocky16_SetOption`, 8x8 / 4x4 / 2x2 block decoders on random opcode streams | 3 x 300000 | 0 |
| `frame_test` | `Blocky16_DecodeFrame` (all methods, buffer rotation, output callback) | 1000000 | 0 |
| `misc_test` | `Smush_GetLengthMs`, light editor, `LecShare_Resolve`, AnimPlay, `gz_open` glue, StdFile | 2000000 | 0 |

Hangs: the original `SoundModule_MixCallback` loops forever on some generated states (stall branch with out == 0); `run_resume.sh`
restarts after the stuck case (29 of about 20000 skipped).

## Runtime checks of the final build (`build/run`, private data copy)

* Scripted suite (autorun copy, GRIM_SIMTIME): unit 120 / 0, walk 88 / 0, move 192 / 0, coll 308 pass / 4 fail (the 4 known), misc 80 / 0,
  rules 786 / 0 - identical to the baseline.
* `build/perf/libcheck.py --movie`: boot to Manny's office, Lua probes, save / load round trip (876925 bytes gz, through `gz_open`), no
  Lua errors, `funny.snm` played to the end with video and audio.
* `build/perf/oldsaves.py --only 12,21,62`: 3 saves, 0 failed.
* `build/perf/audiocheck.py` (movie audio metered per process): peaks 1.31-1.39 against 1.30-1.35 for the baseline.  The meter is
  flaky on this machine for BOTH builds (about 1 run in 8 shows no audio or only a part: other games use the audio device; the
  baseline shows it as often), so compare several runs.
* GRIM_SIMTIME iMUSE: `me_tank3.wav` ends after 412 frames (baseline 414).
* Screenshots of the intro movie frame ("LucasArts Presents", decoded by `Blocky16_DecodeFrame`) are byte identical to the baseline;
  Manny's office: same mean brightness in his region (48.6) and 1190 of 305280 pixels differ (animation phase).

## Ghidra edits (all in `names/mixer_names.json`, `names/mixer_protos.json`; `build/mixdiff/regen.sh` re-exports and rebuilds)

Names and prototypes for every converted function (`Mixer_*`, `InsaneTimer_*`, `DsndDriver_*`, `DSound_*`, `SoundModule_*`, `Video_*`,
`VideoBitmap_*`, `Blocky16_*`, `Rle_*`, `AnimPlay_*`, `LightEd_KeyboardProc`, `Zfile_Close`, `StdFile_*`, `Smush_GetLengthMs`), the
globals of the modules (`g_pMix*`, `g_pStream*`, `g_pTimer*`, `g_pAnim*`, `g_pbBlk*`, `g_pBlkBitmap*`, ...) and labels / arrays
(`g_aBlockySplit8`, `g_asBlockyMotion`, `g_anBlockySplit8X`, ...).  The hand-asm leaf functions that Ghidra took for `__fastcall` have
`__cdecl` prototypes.  `Smush_SetFile` was renamed in `names/exe_movie_primitives.json` too.  Names that the bridge's Hungarian policy
rejects (`g_BlockySplit8`) got a prefix (`g_a...`); float globals need `fl`.  A new label that no decompiled function mentions is not
emitted to `data.s`: the label's name is mentioned in the plate comment of a function that uses it.
