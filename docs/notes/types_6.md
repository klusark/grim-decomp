# Types, round 6 (2026-11-12): two-dimensional arrays; ADPCM, dither and Lua's validevents

Batches: `names/types_data_exe.json` and `names/types_data_lua.json` (extended).

## Tooling

* **datagen: `T name[A][B]`.** A declaration with more than one dimension (globals.h, or a Ghidra type `T[A][B]` of
  `globals.json`) counts A * B elements; their dimensions are kept apart (`datagen.DIMS`), so every other user of a
  declaration still sees (base, is array, count). Two dimensions are written one row per line; more stay bytes.
* **apply_types.py: multi-dimensional types.** The bridge's `apply_data_type` parses one dimension (`T[N]`) and
  answered `ERROR: Unknown data type: sbyte[8][18]`. `apply_global` now builds the array types first,
  innermost out (`create_array_type`: `sbyte[18]`, then `sbyte[8][18]`), then applies the type.
* **ghidra_api.ok** took `ERROR: ...` for success (it looked for `Error` / `Failed` only), so the first run of the
  batch printed no FAIL although the two types were not applied; the check ignores case now.
* **build/link.py** parsed a global's name with a one-dimension pattern and stopped at `g_anColorDither[4][4]`.

## The tables

| program | address | type | name | |
|---|---|---|---|---|
| EXE | 0x004daa58 | `short[89]` | `g_wAdpcmStepTable` | IMA ADPCM step sizes, 7 .. 32767 (`VbrAdpcm_Uncompress`) |
| EXE | 0x004dab10 | `byte[89]` | `g_abAdpcmStepBits` | bits per sample for each step index, 4 .. 7: the variable-bit-rate part of VbrAdpcm |
| EXE | 0x004d86a0 | `int[4][4]` | `g_anColorDither` | the 4x4 ordered-dither matrix of 24 -> 16 bit colour conversion (16.16 offsets; `stdColor_ColorConvertOneRow`, row = line & 3, column = pixel & 3) |
| LUA | 0x10027db0 | `sbyte[8][18]` | `g_aValidevents` | ltm.c's `validevents[tag][event]`: which of the 18 tag methods each of the 8 tags allows (0 / 1), indexed with `-tag` |

The three EXE tables had only Ghidra's automatic names; named, they reach `globals.json` with their types (an
automatic `DAT_` name does not, and `globals.h` then declared them from the code's use: `undefined4 *`, `byte`).
`g_aValidevents` is signed bytes for the reason `g_aYytranslate` is (types_4.md): as `char`, Ghidra may print a
table as a string. The C now reads `g_aValidevents[-param_1][param_2]`, `g_anColorDither[uVar9][count & 3]`,
`g_abAdpcmStepBits[(int)param_2]`; the hand-written colour conversion (overrides_logic.c) takes its row as
`g_anColorDither[row & 3]`.

Both ADPCM spans run past their tables (`g_abAdpcmStepBits` into the doubles of the x87 helpers): the rest is the
tail, as before.

## Checks

* All four programs compile and link; no new stub.
* `datacmp.py` against round 5's build: 0 differences, 0 moved, 0 missing in all four, every unused span zero.
* Sections: CHORE.DLL and IMUSE.DLL identical; the EXE's and LUA.DLL's code change in the functions that read the
  tables as arrays (`VbrAdpcm_Uncompress`, `stdColor_ColorConvertOneRow`, ltm.c's validevents check).
* Clean-room against grim_tools' knowngood (5167 tests, no install file in the run folder): all 5167 the same as the
  reference, and 0 of 5167 differ from round 5's log.

## Left alone

* LUA's `g_aOpcodeDirectory` (129 records of three ints, the first an instruction size): the other two fields are
  not understood yet.
* The DirectX GUIDs (`DAT_004d8350`, 17 of them, `GUID_SysKeyboard` first; `D3D_*`, `DSound_Init`): a Windows type;
  `ghidra_types.h` exports only the program's own structures.
* `UINT_004eca04` (1.5 KB of dwords after a count word, copied whole by `Text_WrapLines`): an embedded bitmap,
  nothing a type would explain.
