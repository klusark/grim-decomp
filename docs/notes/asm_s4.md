# Slice 4: GRIMFANDANGO.EXE 88 addresses, 0x0043c8d0 - 0x0045b1c0

Status: 3 of 88 converted. The file is `build/overrides_asm_s4.c`. It was checked with `gcc -m32 -fsyntax-only`
against the generated `src/GRIMFANDANGO.EXE/ghidra_types.h`, `globals.h` and `functions.h` (with `-DGRIM_EXE`
and `-include build/compat.h`). It compiles with no errors. Nothing was built, linked or run, and no differential test
was made. The three conversions were checked by reading the decompile and the assembly in `src/GRIMFANDANGO.EXE/asm_funcs.s`.

Remaster types: none taken. The coordinator's note allowing remaster struct definitions was received during the work,
but the three conversions only use raw puppet offsets (the 0x134-byte track record), so no remaster type was needed.

## Converted

| address | name | how it was checked |
|---|---|---|
| 0x00450720 | `rdPuppet_FadeInTrack` | Read against the assembly: record at puppet+8+track*0x134, flags `(f & ~8) \| 6`, `1/seconds` computed in long double and rounded to float at the store (x87 `fdiv` then `fstp`), 1.0 otherwise, returns 1. Compare is `0.0 < seconds` with the same NaN result as the C. |
| 0x00450780 | `rdPuppet_FadeOutTrack` | As FadeInTrack with flags `(f & ~4) \| 8`. Read against the assembly. |
| 0x00450a90 | `rdPuppet_Advance` | Read against the assembly, track by track. Kept the x87 details: the level updates are computed in long double and the compares (`>= 1.0` for fade-in, `!(> 0)` for fade-out, which is also true for NaN) are on the extended value, not on the float stored. The return value (count of tracks with non-zero flags, 0 when the puppet's first dword is set) is dropped: the prototype in `functions.h` is `void`, and the caller in `costume.c` and `overrides_logic.c` ignores it. Only the return value differs from the original; it is not returned in this C. |

## Left assembled

| address range | count | reason |
|---|---|---|
| `rdRaster_SpanR16_*` (21), `rdRaster_SpanR_*` (6), `rdRaster_SpanP16_*` (14), `rdRaster_Span8_*` (6), `rdRaster_Span16_*` (8), `rdRaster_Span_TexZ*` (2) | 57 | Software rasteriser span loops. They run on shared globals (`UINT_007f4b*`, `UINT_008ddf*`, `PTR_007f44fc`) with 16.16 fixed-point steps and `ROUND`, and the decompile shows the pixel-format shifts only as masks. The register-passed setup and the global state were not confirmed by reading each one, so none was converted. The same family is left assembled in docs/notes/asm_s3.md. |
| `rdRaster_Draw_*` (8) | 8 | Per-pixel light and Z paths that take a float parameter and the camera chain. Not checked in detail. |
| `rdClip_Face3_Pos`, `_PosB`, `_Pos_2`, `_PosB_2`, `_PosUvLit`, `_PosUvLit_2`, `_PosUv`, `_PosUvFlags` (8) | 8 | Face clipping with float vertex arrays copied into fixed-size locals and x87 intersection maths. Not checked in detail; the 1.01 assembly writes into parameter slots, which needs the same handling as Collision_BoxSlide (docs/notes/logic.md). |
| `rdClip_Line2D` | 1 | Uses `_ftol` with its operands lost by Ghidra (`unaff_ESI`/`unaff_EDI` in the decompile). Cannot be written faithfully from the decompile. |
| `rdCanvas_DrawPoint` | 1 | Same: `_ftol` calls with lost operands (`unaff_ESI`/`unaff_EDI`). |
| `rdPuppet_AdvanceTrack` (0x004507e0) | 1 | Would be convertible (the fade and loop logic is read above), but it calls a table of callbacks with arguments from the track record and uses `ROUND` for the loop count. Not converted in this pass. |
| `rdPuppet_UpdateFrame` (0x00450ba0) | 1 | 305 lines of decompile, not read in detail. |
| `Frustum_TestSphere` (0x0044e7d0) | 1 | The assembly stores a float to an int slot by copying bits (`mov [ESP+0x1c],EAX`) in the orthographic branch and mixes that with extended-precision compares. Not converted: the bit copy and the NaN paths must be matched exactly. |
| `Angles_ToMatrix` (0x0044eeb0), `Angles_ToMatrixNoPos` (0x0044f080) | 2 | The decompile reuses the parameter slot `param_2` as the output of `Math_SinCosTable` and reads it back as a float. Several x87 temporaries are stored to float between operations, so the rounding points must follow the assembly exactly. Not converted. |
| `Matrix_AxisAngle` (0x0044f210) | 1 | x87 intermediates stored to float at several points, plus the `1e-05` tolerance tests. Not checked in detail. |
| `Polygon_ClipToPlane` (0x0044ea50) | 1 | Not read in detail. |
| 0x0044c9d0, 0x0044da40 (two-line signatures, 557 and 475 lines) | 2 | Not read in detail. Large clip functions with several float output pointers. |
| 0x00451510 (per-vertex light level) | 1 | Not read in detail. Its comment describes a light loop with a clamp to 1 and a mean return value. |

## Doubtful or not checked

* The three conversions above are verified by reading only. A differential test (as in docs/notes/logic.md, `logic_dt.c`
  with `tools/gen_asm_dual.py`) is the next step, and `rdPuppet_Advance` is the one to test first because its return
  value is the only thing not reproduced.
* `rdPuppet_Advance` is void in `functions.h`. If the count returned in EAX is ever read by a caller, that caller
  needs the original return value (EAX = number of tracks with a non-zero flag word).
