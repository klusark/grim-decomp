# Types, round 7 (2026-11-12): VIMA's tables in both programs; names in the batches

Batches: `names/types_data_exe.json` (extended), `names/types_data_imuse.json` (new); names added to
`types_data_lua.json` and `types_imuse_music.json`.

## Tooling: a global's name in the batch

`apply_types.py` typed globals, and the names were given by hand afterwards (rounds 4 to 6). A `globals` entry now
takes `"name"`: after the type, `apply_global_name` reads the current name (`audit_global`), renames a user label in
place (`rename_label`), and otherwise goes through the bridge's naming policy, then `create_label` when the policy
refuses (the `a` prefix of an array global), as `tools/apply_names.py` does. Re-applying is a no-op. The globals of
rounds 4 to 6 carry their names now, so every data batch is complete on its own. (The two biased labels of yacc's
tables, `g_wYydefgoto_biased` / `g_wYypgoto_biased`, are labels without a type and stay outside the batches.)

## VIMA

The Smush videos' audio (the EXE's `VbrAdpcm_Uncompress`) and iMUSE's compressed voices and music (IMUSE.DLL's
`Im_ConvertBlockImpl`) share one codec, VIMA: IMA ADPCM with a variable number of bits per sample. Each program has
its own copy of its tables, at the same relative places:

| table | EXE | IMUSE.DLL | type | name |
|---|---|---|---|---|
| index adjustment per code, 2 bits | 0x004da958 | 0x10015128 | `sbyte[4]` | `g_abAdpcmIndexAdjust2` |
| ... 3 bits | 0x004da960 | 0x10015130 | `sbyte[8]` | `g_abAdpcmIndexAdjust3` |
| ... 4 bits | 0x004da968 | 0x10015138 | `sbyte[16]` | `g_abAdpcmIndexAdjust4` |
| ... 5 bits | 0x004da978 | 0x10015148 | `sbyte[32]` | `g_abAdpcmIndexAdjust5` |
| ... 6 bits | 0x004da998 | 0x10015168 | `sbyte[64]` | `g_abAdpcmIndexAdjust6` |
| ... 7 bits | 0x004da9d8 | 0x100151a8 | `sbyte[128]` | `g_abAdpcmIndexAdjust7` |
| the six by bits per sample (0, 1 unused) | 0x004f3348 | 0x10017030 | `sbyte *[8]` | `g_apAdpcmIndexAdjust` |
| IMA step sizes, 7 .. 32767 | 0x004daa58 | 0x10015228 | `short[89]` | `g_wAdpcmStepTable` (EXE: round 6) |
| bits per sample for each step index, 4 .. 7 | 0x004dab10 | 0x100152e0 | `byte[89]` | `g_abAdpcmStepBits` (EXE: round 6) |

An index-adjustment table has one entry per code of its width, the sign bit included: -1 for the small magnitudes,
then rising (the 4-bit one: -1 x4, 1, 2, 4, 6 and the same for the negative half). The code reaches them only
through the pointer table: `g_apAdpcmIndexAdjust[bits][code]`, as the EXE's decoder now reads. `pointer[8]` (Ghidra's
generic pointer) has no C spelling in `ghidra_types.h`; `sbyte *[8]` does.

## Checks

* All four programs compile and link; no new stub.
* `datacmp.py` against round 6's build: 0 differences, 0 moved, 0 missing in all four, every unused span zero.
* Sections: CHORE.DLL and LUA.DLL identical, IMUSE.DLL's code too (its export table has the new names); the EXE's
  code changes in `VbrAdpcm_Uncompress`.
* Untyped initialised bytes: EXE 44,393 -> 44,137, IMUSE 19,922 -> 19,399.
* Clean-room against grim_tools' knowngood (5167 tests, no install file in the run folder): all 5167 the same as the
  reference, and 0 of 5167 differ from round 6's log.
