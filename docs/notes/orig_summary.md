# Original names: summary of the series (2026-11-10 .. 11-11)

Seven rounds gave the four programs the original names of Grim Fandango's source where a source for them exists:
the remaster's unstripped Linux binaries (`GrimFandango` with iMUSE linked in, `libLua.so`, `libchore.so`, their ELF
`.symtab`, demangled), the Lua 3.1 source names for what gcc inlined in `libLua.so`, and the assert / allocator strings
of the v1.01 binaries. Names and comments only: no types or prototypes were changed by the series; the regenerated
src was the previous src after the renames each time, and the code and data of the four binaries stayed
byte-identical to the build before each round. Exports, the MSVC runtime and zlib keep their names.

| round | notes | what it did |
|---|---|---|
| orig-names | [orig_names.md](orig_names.md) | matcher (tools/orig_dump.py, orig_match.py, orig_batch.py): anchors, the Lua registration tables, unique strings, call-graph propagation; 625 functions (LUA 158, EXE 455, IMUSE 12) |
| orig-globals | [orig_globals.md](orig_globals.md) | globals by token alignment of paired functions (tools/orig_gbatch.py, build_src's global aliases); LUA 58, EXE 279 + 5, IMUSE 51; 29 functions the globals settled |
| orig-3 | [orig_3.md](orig_3.md) | anchored alignment fed back to a fixpoint; EXE 325, IMUSE 92 (the iMUSE module prefixes Dp / Dw / Fd / Fm / Gr / Mx / St / Tg / Tr / Ut), LUA 62 (Lua 3.1 names for the generated `l<module>__` names); build/difftest carried (tools/orig_history.py) |
| orig-4 | [orig_4.md](orig_4.md) | the software rasteriser by the dispatchers' switch structure (260 of 351 rdRaster_), the start-up chain, 150 + 26 EXE globals |
| orig-5 | [orig_5.md](orig_5.md) | the LEC library's service tables slot by slot, the module tables, the doubtful lists; EXE 212 |
| orig-6 | [orig_6.md](orig_6.md) | the hand-made names left: call-sequence alignment, the C++ classes in file order (WalkPlane, Puck, PrimitiveQueue, ObjectState); EXE 194 |
| orig-7 | [orig_7.md](orig_7.md) | LUA.DLL against Lua 3.1 (52), LUA globals (4), the last iMUSE pass (6), LEC / light editor (none) |
| (chore round) | [chore_naming.md](chore_naming.md) | CHORE.DLL from libchore.so and the asserts (before the series) |

## Where the names stand

Functions by origin of the name (scratchpad `o7/classify.py`, the classifier of orig-6: FUN_; the runtime (MSVC,
zlib, names/lib_replace.json copies); generated `<module>__<addr>` / `rdRaster_*`; original (a remaster symbol,
`Class::Method` as `Class_Method`, set by an orig batch, or a Lua 3.1 source name); hand-made (the rest)):

| program | functions | original | hand-made | FUN_ | generated | runtime / lib (named) |
|---|---|---|---|---|---|---|
| GRIMFANDANGO.EXE | 2671 | 1594 | 400 | 207 | 91 | 379 |
| LUA.DLL | 852 | 430 (115 of them Lua 3.1 source names) | 13 | 163 | 8 | 238 |
| IMUSE.DLL | 451 | 201 | 28 | 146 | 10 | 66 |
| CHORE.DLL | 264 | 72 | 33 | 152 | 0 | 7 |

Globals referenced by the decompiled code (src/<prog>/globals.h without strings, code labels and Ghidra's stack
artefacts; original = set by an orig / chore globals batch or equal to a remaster data symbol; scratchpad
`o7/gsum.py`):

| program | referenced | original | hand-made `g_` | DAT_ / PTR_ / UINT_ |
|---|---|---|---|---|
| GRIMFANDANGO.EXE | 2267 | 660 | 108 | 1499 |
| LUA.DLL | 363 | 69 | 0 | 294 |
| IMUSE.DLL | 366 | 103 | 0 | 263 |
| CHORE.DLL | 126 | 23 | 0 | 103 |

(`python -I tools/stats.py`: EXE 2464 named / 207 FUN_, LUA.DLL 689 / 163, IMUSE.DLL 305 / 146, CHORE.DLL 112 / 152;
`gcount.py`, which counts the stack artefacts as named: EXE 775 of 2274, LUA.DLL 73 of 367, IMUSE.DLL 103 of 366,
CHORE.DLL 25 of 128.)

## What stays unnamed or hand-made, and why

**The platform layer.** The remaster replaced v1.01's Win32 / DirectX layer with its own (`zg_*`, OpenGL, SDL,
Steam). The DirectDraw / Direct3D / DirectInput / DirectSound code, the window procedure, WinMain, the registry and the
dialogs keep their hand-made names (EXE: about 131 functions, orig-6), and so do iMUSE's DirectSound and HMI FX glue
and the LEC library's DirectSound driver, timer thread and assembler helpers. Only the slots that still exist in the
remaster (its stubs: std3D_*, stdDisplay_*, stdControl_*, wuRegistry_Shutdown, ...) were named, by their call slot.

**Helpers the remaster's compiler inlined.** gcc inlined statics that MSVC 6 kept: no symbol is left for them.
* EXE: about 176 engine helpers (Lua glue, resource, render, actor, set, text, gif, lab helpers), the 61 LEC helpers
  (the mixer's per-format loops, the pixel converters, the blocky16 levels, LecShare_* and the Str_* of lecshare.c,
  SoundModule_*), the 86 per-texture-width span fillers and 2 z-write spans of the rasteriser (rdRaster_*: one generic
  span per variant in the remaster) and 5 folded edge advances.
* LUA.DLL: the 115 statics with Lua 3.1 source names (named from the sources, "not in the remaster" in the plate
  comment); left are Grim's own undump / opcode helpers (`lundump__*`, `lstate__85e0`, `lzio__*`) and
  `luaU_LoadNumber`, `luaM_malloc` / `luaM_free` (Lua 3.1 macros made functions), `luaI_checkevent` (already the
  3.1 name).
* IMUSE.DLL: the dispatcher's region / jump / fade helpers (inlined into GoToNextRegion, PredictStream,
  DpProcessTrack), the music-script cases of ScriptCall, the memory list and timer set-up of sounds.c, the mixer loops
  and the codec loop (MxMix, AudioLib_UncompressBlock), the file manager's list copies; three v1.01 functions for the
  one query_music_stream.

**v1.01-only code.** The light editor (24 functions: `LightEd_*`, `LightMgr_*`, `Lua_LightMgr*`; the remaster
registers LightMgrStartup / Shutdown / SetChange as DoNothing), the debug drawing of sets and sectors, the dirty
rectangles of MarkDirtyRect, Grim's once-flags (luaT_setfallback), the HMI FX presets. Shared empty functions that sit
in several slots (`LecShare_Nop`, `Lua_Stub`, `CostumeTag_Nop`, `Mem_DumpLog`, `Plat_ReturnTrue`, iMUSE's
FUN_100067a0) keep their names: no single original name fits.

**The runtime.** The MSVC 6 runtime copies (EXE 187 of the 207 FUN_ are runtime, zlib and folded copies; LUA.DLL all
163 FUN_; IMUSE.DLL 117 of 146 (the other 29 are the iMUSE helpers above, orig_7.md); CHORE.DLL all 152), zlib 1.1.3 and the import thunks. They are not renamed (some are
replaced by the host runtime, names/lib_replace.json). Of the unnamed referenced globals most belong to the runtime or
are literals the code takes by address (float constants, format strings, string and pointer tables), struct pieces
(`symbol+offset` that Ghidra shows as separate DAT_ globals; only referenced bases were named) or real statics of the
v1.01-only code above (classes of the EXE's globals: orig_5.md, target 4).

**Types.** The remaster's ELFs have no DWARF (only .symtab / .strtab): object sizes and the C++ parameter types of the
mangled names, no struct layouts or field names (orig_5.md, target 5).

## Doubtful / contested, left as they are

`Video_CopyRectDstFirst` (gra_CopyRect; the shorter name changes Ghidra's line wrapping and the generated cast),
`rdroid_SetColormap`, `Controls_DebugKeysHook`, the Engine_*Subsystems helpers, the dirty-rect statics,
`loadLastSave`, `printBuffer`, `stdDisplay_bOpen`, `compressorState.2/.3`, the Blocky16 split tables, the struct-field
votes; the reasons are in the round that looked at them (orig_names.md .. orig_7.md).

## Tools of the series

tools/orig_dump.py, orig_match.py (matcher), orig_batch.py / orig_gbatch.py (batches with "old", plate comment "was
X"), orig_history.py (earliest -> current name per address, for build/difftest), rename_refs.py (carries a batch into
the hand-written code; once per batch), names/orig_modules.json (keeps a renamed function in its source file),
build_src.py's global aliases (a renamed global is generated under its old name while its Ghidra type is unchanged).
