# Types, round 5 (2026-11-12): structures in the data; iMUSE's music tables

Round 4 (types_4.md) gave `data.c` values for scalars and arrays of scalars. This round adds structures and types the
largest block of the data that was still bytes: iMUSE's music tables, 26 KB of IMUSE.DLL's 48. Batches:
`names/types_imuse_music.json` (new), `names/types_data_exe.json` and `names/types_text.json` (extended).

## datagen: structures

* A span declared as a structure or an array of structures of `raw/<prog>/structs.json` is written with designated
  initialisers: `{ .aFilename = "1002 - Mr. Frustration", .nTransType = 3, .nId = 1002, ... }`. The field names are
  the ones `ghidra_types.h` declares (`datagen.struct_fields` repeats `build_src.struct_defs`' rules: undefined bytes
  are padding, a repeated name gets its offset); structures `build/compat.h` defines by hand are left out.
* Field values: scalars as in round 4; `char[N]` as a string when it is text, numbers otherwise; arrays of scalars;
  nested structures; pointers only where the data has a relocation (or zero). Zero fields are left to C's zero fill,
  non-zero padding is written as `._pad_<off>`. Anything else (a pointer in a field typed otherwise, a nonzero pointer
  without a relocation, two dimensions) keeps the span's old form.
* `data.c` includes `ghidra_types.h` when it uses a structure.
* A declared structure covers its extent like a declared array: a label inside it that has no type of its own is an
  alias, not a new span. That is what joined `g_PrintLineTextCtx` and `g_SubtitleTextCtx` (round 3) with the labels
  of their `pFont` fields (`UINT_004e84a0`, `UINT_004e84d0`).

## iMUSE's music tables (IMUSE.DLL)

`ImMusicEntry` (0x54), one record of the state table and of the sequence table:

| off | field | |
|---|---|---|
| 0x00 | `char aFilename[32]` | the sound file, renamed through the alias table; empty: no music |
| 0x20 | `int nTransType` | transition type, `Script_Trans`'s jump table (0..12); the game uses 0, 2, 3 |
| 0x24 | `int nId` | state 1000.., sequence 2000.. |
| 0x28 | `char aName[24]` | `stateMO`, `seqClimbRope`, ... |
| 0x40 | `int nHookSlot` | hook counter slot |
| 0x44 | `int nHookLimit` | the hook counter cycles up to this |
| 0x48 | `int nFade` | fade time; the volume / pan step is nFade * 3 / 50 |
| 0x4c | `int nVolume` | 127 full |
| 0x50 | `int nPan` | |

`ImNameAlias` (0x40): `char aFrom[32]`, `char aTo[32]`.

| address | type | name |
|---|---|---|
| 0x100172e8 | `ImMusicEntry[181]` | `g_aImStateTable` (ids 1000..1500; ends at 0x1001ae4c, the loop bound of `FUN_100067b0`) |
| 0x1001ae50 | `ImMusicEntry[41]` | `g_aImSeqTable` (ids 2000..2399; ends at 0x1001bbc4) |
| 0x1001bbc8 | `ImNameAlias[171]` | `g_aImNameAlias` (170 entries and the empty one that ends it; up to `g_dwLocalMusic`) |

The layout is the one `build/overrides_imuse_r1.c` had worked out for `Script_Trans` (`STATE_TAB`, `SEQ_TAB`,
`NAME_ALIAS`). The code addressed the columns by number, so Ghidra had labels in the records: `DAT_1001730c` (the
first record's `nId`), `DAT_10017310` (`aName`), `DAT_10017328` (`nHookSlot`), `DAT_1001ae70` / `DAT_1001ae74`
(the sequence table's `nTransType` / `nId`), `DAT_1001bbe8` (the first alias's `aTo`). With the tables typed they are
gone, and `Script_SetSequence` reads `g_aImSeqTable[g_dwCurrentSequence].nId`, `g_aImSeqTable[iVar5].aName`,
`g_aImSeqTable[g_dwCurrentSequence].nTransType`. Its committed return type became `int` (the record's `nId`); the
hand-written `Script_SetSequence` of overrides_imuse_r1.c follows.

The bridge's naming policy refuses the `a` prefix for globals; as `tools/apply_names.py` does when the policy
refuses a name, the three names are labels made with `create_label`.

## EXE

* `g_TextObjectCtx` (0x004e84f8), declared `uint`, is the third `TextContext` (`sputText_MakeTextObjectL` copies its
  12 dwords). `TextContext` got a field at +0x00, `void *pUnused`: all three contexts hold a pointer there
  (0x008a94b8), which the code copies but never reads; as padding it kept the contexts from being written as
  structures. A structure change re-exports the whole program (11 minutes).
* `PhonemeEntry` (8): `uint dwPhoneme` (the phoneme's IPA code point: 0x5f `_` silence, 0x251, 0xe6, 0x28c, ...),
  `ushort wTalkChore` (the costume's talk chore). `g_aPhonemeTable` (0x004e9c88, was `g_dwPhonemeTable`) holds 46:
  `Phoneme_ToTalkChore`'s `bsearch`, sorted by `sputActor_Startup`.
* `BlockyMotionVector` (4): `short nX`, `short nY` (the policy names short fields `n...`).
  `g_aBlockyMotionVectors` (0x004f34e8) holds Blocky16's 255; `fob_blk16_configure` turns each into
  `nY * stride + nX` in `g_asBlockyMotion` (`pBVar2->nY * sVar8 + pBVar2->nX`).

## Checks

* All four programs compile and link; no new stub (against main's CI build).
* `datacmp.py` against the previous build: 0 differences, 0 moved, 0 missing in all four, every unused span zero.
* Sections: CHORE.DLL and LUA.DLL identical; IMUSE.DLL's code too (only its export table, the new names); the EXE's
  code changes where the retyped users compile differently (the text functions after the `TextContext` export,
  `fob_blk16_configure`, `Phoneme_ToTalkChore`, `sputActor_Startup`).
* Untyped initialised bytes: EXE 46,228 -> 44,724, IMUSE 46,029 -> 19,922; IMUSE's `data.c` 339 -> 206 KB.
* Clean-room against grim_tools' knowngood (5167 tests, no install file in the run folder): all 5167 the same as
  the reference; against the previous build's log only the three lab tests differ, which this run passed (their
  failure is not deterministic, data_unused.md). Every other test the same.

## Next

* The EXE's remaining tables: `UINT_004eca04` (1.5 KB, the text code's rune table), `DAT_004d86a0` (the colour
  conversion's 4x4 dither matrices), `g_dwGrimlib_PerfData`. (`PTR_RegQueryInfoKeyA_004d7000`, 1.3 KB, is the import
  address table: nothing to type.)
* Lua's `g_aValidevents` (two dimensions: datagen needs `T name[A][B]`) and `g_aOpcodeDirectory`.
* The C runtime's own tables (locale, ctype, time names) in all four programs.
