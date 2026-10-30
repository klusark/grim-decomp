# IMUSE.DLL test tools (agent N)

Written for the conversion of IMUSE.DLL from assembly to C (see `docs/notes/imuse.md`).  The shell scripts carry the paths of agent N's
private setup (`C:/Users/Joel/grimN_data` = hard-linked data folder, `C:/Users/Joel/grimN_work` = scratch, `grim-agentN`, the
`GRIM_MULTI=agentN` tag); edit the variables at the top before using them elsewhere.  One game at a time per tag: two runs at once
silently break each other.

| file | what |
|---|---|
| `audtrace.py` | gdb script: CRC and peak of every 0x1800-byte block `Im_DSoundHeartbeat` is about to commit to DirectSound (the final PCM). `AUD_OUT`, `AUD_LIMIT` |
| `audrun.sh` | boots a build under gdb with that script and a Lua scenario (`scn_*.lua`, pre-written to the hook file), runs until the scenario logs `DONE` |
| `audlim.sh` | the same for boot only, stops after N blocks (5-9 s per run); `bisect_audio.py` is a delta-debugging bisect on it |
| `audcmp.py`, `audmask.py`, `audgroups.py` | compare traces; the baseline itself differs between runs in short windows (an ambient sound starts one heartbeat earlier or later), `audmask.py` masks the blocks where the baseline runs disagree |
| `imuse_diff.c` | loads the assembled and the C IMUSE.DLL into one process and compares `Im_VimaDecompress` on every .wav of the data LABs (build: `/mingw32/bin/gcc`, needs `imuse_a.dll`, `imuse_c.dll` and HMIFXLIB.DLL in the working directory) |
| `covtrace.py` | gdb script: which converted functions run in a scenario (an inlined function never shows) |
| `argtrace.py` | gdb script: the stack words at the entry of one function (how the garbage arguments of `FUN_100068b0` were measured) |
| `imbuild.sh` | regenerate + build IMUSE.DLL only (about 25 s), copy it to a run folder |
| `scn_2` .. `scn_7` | Lua scenarios: sfx / voices / fades / pause / group volumes (2), ten music state changes (3), movie (4), Save + Load (5a, 5b), voices (6, 7) |
