# Engine_RenderFrame (GRIMFANDANGO.EXE 1.01, 0x00484260) in C

Port: `build/overrides_big_engine_renderframe.c`, written by hand from the 1.01 machine code.  Test:
`build/difftest/big_engine_renderframe/` (`run.sh [cases]`, `mutate.sh`).

## What it does

One frame of sputRender.cpp, chosen by the mode at 0x008a8c40:

* **0**: nothing.
* **3** (movie): `Movie_SetTarget(&g_BackBuffer)`, `Movie_PollPlayback()`.  When the movie has ended: mode 2, the rectangle
  {0, 0, 640, 480} is added to the dirty list of every buffer (`g_nBufferCount` is reread each iteration), full redraw requested,
  0x008c97f8 = 1.  Then `Actors_UpdateTalking(Timer_GetFrameSeconds())`, text objects (`TextObjects_Update(0)` between
  lock / unlock, 0x008a94b8 = 0x0090563c first), `Render_Present`.  Returns without clearing `g_nFullRedrawPending`.
* **4**: `Engine_CallUserPaint` if a full redraw is pending; the pending flag is cleared.
* **any other**: the set scene.
  1. `lua_printstack(0)` if 0x008c9804 is set; return if there is no current set.
  2. If the current set differs from `g_pRenderedSet`, or its setup (+0xb4) from `g_nRenderedSetup`, or a redraw is pending:
     `DirtyRect_Clear`, store the set and setup, `Set_SwitchSetup`, `Lua_CallPostCamChangeHandler(g_nRenderedSetup)`.
  3. Setup record `rec = set->setups(+0xac) + g_nRenderedSetup * 300`; `Set_ApplySetupCamera(set, setup)`.
  4. Object states of the setup (chain at rec+0x128, next at +0xf8; `__thiscall ObjectState_Draw(os, layer, dst, zdst)`):
     layer 3 into the background / z-buffer surfaces; profile 4 around `DirtyRect_Flush` (if `g_nDrawEnabled`); movie poll;
     primitives layer 1; object states layer 1 into the back buffer; `rdroid_BeginFrame`; `Render_BuildActorDrawList`.
  5. If the draw list (count 0x008a952c, pointers at 0x008c9568 to {type byte, ..., actor index at +8}) is not empty or debug
     flag 1 is set: profile 5: `Costume_TouchComponents(*actor->costume)` for each type-0 entry; debug grid or sector debug
     (flag 8); profile 6: for each entry **from the last to the first**: if the actor's scale (+0x30, compared as the bit
     pattern 0x3f800000) is not 1, `Matrix_BuildTransform2(Actor_GetFrame(a), {s, s, s})`; type 0: colormap (the actor's
     record at +0, or the set's default one `set->+0x80[set->+0x88]`, records of 0x34 bytes; "Bad Colormap Reference" assertion
     if its first dword is 0), `rdroid_SetColormap`, the callback at 0x008c97b8(colormap + 0x30, 0), `Actor_DrawCostumes`,
     debug walker; type 1: `Actor_ComputeScreenBox` (locked unless the z-buffer is on) and `Render_InvalidateRectLastBuffer(a + 0x6c)`;
     then, scale reread, the inverse scale `1.0f / s` (one x87 division, rounded once to float).  Profile 7 around
     `rdroid_EndFrame`; object states layer 2.
  6. Primitives layer 2; debug lights (flag 2) and cameras (flag 4).
  7. Iris (flag 4 of `g_dwRenderFlags`): `v = (uint64)(now - start) / duration` in extended precision, `|v|`; `v > 1` clamps
     to 1 and sets flag 8 (duration >= 0) or clears flag 4 (duration < 0), otherwise clears flag 8; `1 - v` when duration <= 0;
     `Render_DrawIris((float)v, g_nIrisX, g_nIrisY)`; for a negative duration the whole screen is invalidated.
  8. Text objects (`TextObjects_Update(1)`), pending flag cleared.

## Root cause of the crash of the earlier C version

The setup-record pointer lives in EBX and is spilled to `[ESP+0x10]` (the actor loop needs EBX as its counter and reloads it
from there afterwards).  The same slot also holds the frame time (mode 3, float), the iris rectangle and the iris value
(float).  Ghidra gave the slot one type, `float local_1c[3]`, so the pointer became
`fVar8 = (float)(*(int *)(set + 0xac) + setup * 300)`: an **int-to-float conversion of an address**.  The patched text then
read the chains as `*(void **)(PUN(int, fVar8) + 0x128)`, i.e. through the float's bit pattern (a pointer near 0x4c000000;
without the pun, `(int)fVar8` is the address rounded to 24 significant bits, a few bytes off for heap addresses above
16 MB) — a read from a wrong address next to the setup record, then object-state "pointers" that are garbage.  The C here keeps
the record as a `byte *`.  The same text also had: the actor scale converted with `(float)actor[0xc]` (the integer value of the
float's bits) in both scale vectors, the signed difference in the iris (the original zero-extends it: FILD of a qword whose
high dword is 0), the rectangles without their height (480 at `[ESP+0x1c]` was lost), and `Sector_DrawAllDebug` without its
argument.

## A bug in the assembled copy

The export mis-decoded 0x0048483d-0x0048484b: `src/GRIMFANDANGO.EXE/asm_funcs.s` (and `raw/.../disasm.json`) have
`dec ESI; add byte ptr [EAX+0x56097402],CH` where 1.01 has `mov AL,[g_dwRenderDebugFlags]; test AL,2; jz; push ESI`
(bytes a0 78 80 4e 00 a8 02 74 09 56; the first three were skipped).  In the current all-assembly build, debug flag 1 therefore
writes a byte to a random address and calls `Set_DrawDebugLights` with no argument.  Only the debug overlay path is affected.
The C port has the 1.01 behaviour.  The test corrects the slice with `fix_orig.sed`, and `check_slice.py` compares the corrected
slice instruction by instruction (registers and mnemonics; immediates masked) with a disassembly of the real bytes
(0x735 bytes at 0x484260 of the 1.01 text section, which `run.sh` cuts from your own copy, `raw/GRIMFANDANGO.EXE/sections/text.bin`; note that `/GRIMFANDANGO.EXE` in that project
holds other bytes at this address): 528 instructions, identical.  This check is the only reason to believe the reference
is 1.01 and not the export.

## Verification

`run.sh` (same tool chain as `build/difftest/asm_s5/build.sh`): the corrected original (`orig_Engine_RenderFrame`) and the
C run on the same random start state in one process, linked with the game's data image (`build/obj/GRIMFANDANGO.EXE/data_s.o`).
Every callee (41 functions, the `__thiscall` ObjectState_Draw through an asm shim, `lua_printstack` both as import slot and as
symbol, the colormap callback, the assertion through a fake service table) is a recorder in `renderframe_test.c`.  Compared after
each case: the full call log (arguments; stack buffers by content: rectangles and scale vectors; scripted return values) and all
memory the function can touch (the globals 0x004e8060-0x004e8090, 0x008a8c40, 0x008a94b8, 0x008a952c, 0x008c9560-0x008c95a0,
0x008c9770-0x008c9808, 0x008ca758, 0x0090563c, 0x00905ac0, and the sets, setup records, object states, actors, list entries,
colormaps, costumes).

The state is random: modes 0-5, two sets of 4 setups, object-state chains, 8 actors with scales 1.0 / specials (0, -0, NaN,
inf, denormal) / random, 8 list entries (types 0, 1, other), all flag words, iris start / now / duration (positive, negative,
special floats, now before start).  `Set_GetCurrent` returns a scripted sequence (the rendered set, the other set, none on
the first call only).  In two thirds of the cases the recorders have effects that change what the function reads later
(setup indices from `Set_SwitchSetup` and the Lua handler, `g_nBufferCount`, the rectangle, list count, actor scales, colormap
pointers, the rendered set, z-buffer flag, debug flags, object-state links, the iris duration), so the order and number of
rereads is checked.  Each case runs under a random x87 precision control (24 / 53 / 64 bit).

Result: 1 000 000 cases, 0 differences (C at -O0, the build's flags); 200 000 cases with the C at -O2, 0 differences.
Per million cases: 365 000 setup switches, 1.48 million scale matrices, 573 000 costume draws, 576 000 screen boxes, 48 000 colormap
assertions, 41 000 sector / 41 000 grid debug draws, 48 000 debug-light calls, 123 000 iris draws, 38 000 full-screen invalidations.

`mutate.sh` checks that the test notices deliberate errors: signed iris difference, missing rectangle height, a C `<=` instead of
the unordered compare, float-rounded iris quotient, list order, scale or colormap not reread, buffer count cached,
`Sector_DrawAllDebug` without argument, wrong debug bit, mode 3 clearing the pending flag: every one gives differences (58 to
13 573 in 30 000 cases).

## Not verified

* The callees are recorders, not the engine: the test shows the C makes the same calls with the same arguments on the same state
  as the original and writes the same memory, not that a frame looks right.  No game run, no picture comparison was made.
* `Set_GetCurrent` returning NULL after a non-NULL first result (the original then crashes on `+0xb4`) is not tested; the C
  crashes the same way, read for read, but this was not run.
* The register and stack-slot state left behind (the function returns nothing; callers do not read EAX) is not compared.
* The x87 control word is only varied in precision, not in rounding mode.
