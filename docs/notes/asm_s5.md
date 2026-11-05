# Slice 5 (agent asm_s5): assembled functions and reasons

Scope: 88 GRIMFANDANGO.EXE addresses (`exe_slice5.txt`) and the five CHORE.DLL costume loaders.
Result: **0 of 88 EXE functions and 0 of 5 CHORE functions converted to C.** Every function stays in
`src/<PROG>/asm_funcs.s`. The two override files exist, contain only the header comment, and pass
`gcc -fsyntax-only` with the build flags:

* `build/overrides_asm_s5.c` (GRIM_EXE)
* `build/overrides_asm_s5_chore.c` (GRIM_CHORE)

No remaster struct or type definitions were used (the coordinator's update allowing them was received
mid-slice; nothing needed them, since no function was ported).

## Converted functions

None.

## Left assembled

The per-function reason is grouped by family. Names and addresses are Ghidra 1.01 names from `functions.json`.

| Address(es) | Name(s) | Reason |
|---|---|---|
| 0045ba90 - 0045f550 | rdRaster_SpanP16_TexLit_3 ... _9 | Texture span loops with register-carried pointers and the x87 / integer mix; not checked line by line, too large to port faithfully by reading |
| 0045ff10 - 004710e0 (about 45 functions) | rdRaster_Span16_TexLitZw_*, rdRaster_Span16_TexZw_*, rdRaster_Span16_TexZw | Same family: span routines with the Z-buffer and lit variants; the dumps show generated-looking unrolled code, so a faithful port would need the full instruction trace |
| 00474e40 | Display_DrawText | GDI calls with the DIB / DirectDraw DC branch; not checked |
| 004761b0 | FUN_004761b0 | Unnamed, four stack arguments, not identified |
| 004767d0 | DDraw_CreateSurfaces | DirectDraw vtable calls with unnamed slot numbers and a mode-dependent back buffer path |
| 00477730 | Input_PollKeyboard | DirectInput device-data buffer layout (16-byte records) is ambiguous in the dump |
| 00477c20 | Input_PollMouse | Same DirectInput ambiguity |
| 00477dc0 | Input_FlushJoystick | GetDeviceState / GetDeviceData vtable calls, and the state buffer index (`local_10[iVar4 + -0x14]`) is mis-indexed by Ghidra; the dump does not show the buffer layout |
| 00478b40 | D3D_ExecuteBuffer | Execute-buffer vtable slots 0x14 / 0x18 / 0x20 are unnamed in the dump; the stack zeroing (12 dwords) is a D3DEXECUTEDATA-like record, not verified |
| 00479db0 | D3D_InitRenderState | Render-state list built from driver caps bits; the instruction stream and the list layout were not checked |
| 0047a130 | D3D_CreateViewport | D3DVIEWPORT2 fill (11 dwords, 0x2c size) with float / int mixed stores (`(uint)fVar3` value conversion); risk of a wrong cast |
| 0047d2d0 | stdPic_LoadInto | 370-line `.pic` decoder; not ported in this pass |
| 0047e7f0 / 0047ea30 | stdGif_LzwInitEncoder / stdGif_LzwEncodePixel | LZW code tables with byte-level state; not ported in this pass |
| 00484260 | Engine_RenderFrame | Known bad C version (crash at +0x240, see docs/notes/logic.md) |
| 004917e0 | Walker_AvoidActorPath | 405 lines; not ported in this pass |
| 004939f0 | Collision_TestActorAgainstOthers | Known C version crashes at start-up (logic.md) |
| 00496950 | ModelComponent_NewInstance | Calls Cos_InstComponentInfo with addresses of parameter slots as out-arguments (the Ghidra slot-as-output pattern, BUILD_NOTES); the faithful C needs the real prototype |
| 004965b0 | FUN_004965b0 | Uses stack arguments of its caller (`in_stack_*`) and calls through a stack function pointer |
| 004985c0 | FUN_004985c0 | Same slot-as-output pattern for Cos_InstComponentInfo / Cos_InstGetInstanceData |
| 0049de00 | Lua_InitGameLibs | Lua library setup with unnamed `lua_*` globals and an indirect call through `UINT_008cab58`; the exact order and the Reg_GetString defaults were not verified against the binary |
| 004addf0 | FUN_004addf0 | Spacebase / calling-convention warnings in Ghidra; not identified |
| 004a6980 | Sector_ContainsPoint | Known bad C version (1e-5 tolerance differs from x87 original, logic.md) |
| 004ac6f0 | _ftol | CRT helper; the x87 ROUND body is intentional, not ported |
| 004d5e1c / 004d5e30 / 004d5e50 | FUN_004d5e1c, FUN_004d5e30, FUN_004d5e50 | Exception-handler / EBP-frame fragments (unaff_EBP, FS:0 chain); not C-expressible |
| 004d5e70 | Rle_Decode | Calls Rle_NextByte with the count in ECX carried between calls (`extraout_ECX`); the register-passing convention was not verified |
| 004d5f70 | FUN_004d5f70 | vsprintf into a ring buffer with static counters (DAT_008dcdc8 / UINT_008ddd68 / UINT_008ddd6c); a plausible port, but the vsprintf argument order is not verified |
| 004d5fd0 | FUN_004d5fd0 | __fastcall fill of 20000-byte blocks; returns CONCAT44 with the stale EAX, which C cannot reproduce |
| 004d6030 / 004d6050 / 004d6070 / 004d6090 / 004d609e / 004d60ac / 004d60d0 / 004d60db / 004d6100 | FUN_004d6030 ... FUN_004d6100 | Cleanup funnels that read their argument from the EBP frame (`unaff_EBP + -0x10`): Plat_Free / StateImage_Release on a frame slot; not standalone C functions |

## CHORE.DLL (costume loader)

| Address | Name | Reason |
|---|---|---|
| 10001770 | Cos_LoadEntry | Ghidra output has a goto into the duplicate-component loop that reads `unaff_retaddr` as its loop variable; the register-carried control flow is not reproduced faithfully |
| 100041e0 | FUN_100041e0 | Parses fixed format strings from unnamed .data (0x10010538, 0x10010524, 0x1001019c, 0x10010198, 0x10010190); the stored index is `DAT_10014210 + iStack_28*4`; format-string texts not read |
| 10004390 | FUN_10004390 | Uses `unaff_retaddr` as a costume index in a loop, and absolute .data buffers 0x10013e10 / 0x10014210; not safe to port by reading |
| 100047f0 | FUN_100047f0 | Parses records into a 0x2c table with unnamed format strings (0x100105c0, 0x100105ac); the dump is truncated for the rest of the body |
| 10004970 | FUN_10004970 | Not ported; its dump was not read in this pass |

## Verification

* `gcc -m32 -march=i686 ... -fsyntax-only` on both override files: passes (checked with the build flags from
  `build/Makefile` GHIDRA_CFLAGS, `-I. -Ibuild -Isrc/<PROG>` for `ghidra_types.h`).
* Nothing was run or built; no other file was edited.
* Reading only: the reasons above come from the dumps and disassembly, not from a test of the assembled code.
