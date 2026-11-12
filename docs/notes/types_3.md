# Types, round 3 (2026-11-12): Puck, CostumeNode, TextContext and TextObject

Rounds 1 and 2 (types_1.md, types_2.md) typed the actor record and its ActorExtra. This round types the three records
they still pointed to as `void *`: the walker puck (`ActorExtra.pPuck`), the costume stack (`Actor.pCostumes`) and
the speech text object (`ActorExtra.pText`), with the text context a text object holds. One batch each:
`names/types_puck.json`, `names/types_costume.json`, `names/types_text.json`; `names/types_actor.json` retypes the
three pointers.

## Puck (0x60, Walker.cpp)

| off | field | |
|---|---|---|
| 0x00 | `float aPos[3]` | |
| 0x0c | `float aFrame[12]` | rdMatrix34: right, forward (+0x18), up (+0x24), position (+0x30); `Puck_SetPos` writes both positions |
| 0x3c | `float flRadius` | 60 for an actor |
| 0x40 | `float flStep` | the last step of `Puck_Forward` |
| 0x44 | `float aConstraint[3]` | the sector's constraint vector (`Puck_Constrain`), 0, 1, 0 at first |
| 0x50 | `int nConstrained` | |
| 0x54 | `Puck *pPrev` | the list `g_dwPuck_p_head` (now `Puck *`) |
| 0x58 | `Puck *pNext` | |
| 0x5c | `void *pSector` | the WalkPlane sector under the puck (`Puck_Validate`) |

The four `__fastcall` methods take `Puck *puck`. The eleven `__thiscall` ones (`Puck_Construct`, which now returns
`Puck *`, `Puck_SetPos`, `Puck_Xform`, `Puck_InvXform`, `Puck_Rotate`, `Puck_PointAt`, `Puck_Constrain`,
`Puck_Forward`, `Puck_OrientToPlane`, `Puck_Draw`, `Puck_GetYawToPoint`) get a typed `this`.

## CostumeNode (0xb4, sputCostume.cpp)

One costume of the stack, from the pool `g_pCosNodePool`; `Costume_InitRecord` sets the defaults.

| off | field | |
|---|---|---|
| 0x00 | `uint dwInstance` | CHORE.DLL costume instance |
| 0x04 | `void *pMainModel` | a pushed costume with the same model takes over the head settings below |
| 0x08 | `void *pComponents` | model / sprite components drawn with the actor, linked at +0x190 |
| 0x0c | `int aHeadJoints[3]` | `SetActorHead`, -1 none |
| 0x18 | `float flLookRate` | 360 (`SetActorLookRate`) |
| 0x1c | `float flMaxPitch` | 30 |
| 0x20 | `float flMaxYaw` | 90 |
| 0x24 | `float flViewCos` | -0.35: cosine of half the view cone (`sputActor_CanActorSeePoint`) |
| 0x28 | `int nWalkChore` | -1 none |
| 0x2c | `int nTurnLeftChore` | |
| 0x30 | `int nTurnRightChore` | |
| 0x34 | `int nRestChore` | |
| 0x38 | `int aTalkChores[16]` | mouth shapes, [0] closed |
| 0x78 | `int nMumbleChore` | |
| 0x7c | `uint aCostumeRef[13]` | the costume's 0x34-byte resource reference |
| 0xb0 | `CostumeNode *pNext` | the costume below |

Typed with it: the stack functions (`sputCostume_PushCostume` / `PopCostume` / `SetCostume`, which return the new
top, `sputCostume_FreeCostumeNodes`, `Costume_AllocRecord`, `Costume_InitRecord`, `sputCostume_PrintCostumeInfo`,
`FindCostumeInStack`), the `costume` of `sputActor_SetWalkChore` / `SetTurnChores` / `SetRestChore`, and the costume
list of `sputCostume_Update` and `sputCostume_DrawMeshShadow`.

## TextContext (0x30) and TextObject (0x260, sputText.cpp)

`TextContext` says how a text is drawn: +0x04 `int *pClipRect`, +0x08 `void *pFont` (a font handle),
+0x0c / +0x10 `nX` / `nY`, +0x14 / +0x18 / +0x1c foreground / background / effect colour (0xRRGGBB; while drawing, an
index into +0x2c `pColormap`), +0x20 / +0x24 `nScaleX` / `nScaleY` (16.16), +0x28 `dwFlags` (justification: 4 left,
5 centre, 6 right). +0x00 is copied but never read. `g_SubtitleTextCtx` and `g_PrintLineTextCtx`, 0x30 bytes apart,
are typed `TextContext`; their bytes in the data image do not change.

`TextObject`: +0x000 `pNext` / +0x004 `pPrev` (the queue `g_pTextQueue`, now `TextObject *`), +0x008 `char aText[512]`,
+0x208 `TextContext ctx` (a copy, with `ctx.pClipRect` pointing at `aRect`), +0x238 / +0x23c `nX` / `nY` as given,
+0x240 `int aRect[4]`, +0x250 `nDuration` (ms, -1 until killed), +0x254 `Actor *pActor` (the speaker), +0x258
`dwFlags` (1 keep, 2 hidden, 4 speech, 8 always draw), +0x25c `nSerial` (its own address, kept in save games).

Typed with them: `TextObject_New` (takes a `TextContext *`, returns `TextObject *`), `TextObject_Draw`,
`sputText_AddToQueue`, `sputText_FindSerialNumber`, `sputText_CreateActorText` (returns `TextObject *`),
`GetTextParamsFromTable`, and the `ctx` of `Text_GetStringWidth`, `Text_GetStringHeight`, `Text_GetCharKernedWidth`,
`Font_GlyphAdvance` and `Text_DrawString`. `Text_DrawChar` keeps `void *ctx`: the function reuses the parameter's
stack slot for an integer, and typed, Ghidra writes that as `&ctx->field_0x0 + n` (byte arithmetic through the unnamed
+0x00), which does not compile.

## Tooling

* **`this` entries.** Ghidra's `this` is an auto-parameter typed from the function's class namespace. The bridge's
  `set_function_this_type` moves the function into a class `Puck`, after which the decompiler prints
  `Puck::Puck_SetPos` at the definition and the calls. `tools/build_src.py` drops a qualifier that repeats the
  function's own prefix (`X::X_...`), so comments such as "Puck::SetPos in the remaster" stay. `ghidra_api.py`
  journals `set_function_this_type`. Setting the return type of the `__thiscall` `Puck_Construct` kept its `this`.
* **Structures across batches.** `apply_types.py` now applies the structures of all the batches given first, sorted
  so a structure held by value comes first, and creates new ones with their pointers to other batch structures as
  `void *`, typed in a second pass. The pointers form cycles (Actor -> ActorExtra -> TextObject -> Actor). Usage is
  now `apply_types.py names/types_*.json`.
* The bridge renames a pointer field `hFont` to `pFont` (its naming policy); the batch uses `pFont`.
* As in round 2 the journal's `*struct*` was replaced by the users: the 109 functions whose export mentions
  `pCostumes`, `pPuck`, `pText` or `->pExtra`, plus the touched functions and globals, 222 functions with their
  referrers.

## A regression the clean-room run caught: sputText_MakeTextObjectL

The first clean-room run of this round differed from main's build in four text tests (text_objects,
gco_font_kerned, gco_text_keys, gl1_text_long_word: the size of a wrapped text). `sputText_MakeTextObjectL` copies
`g_TextObjectCtx` into a local text context at Stack[-0x30] and points the copy's clip rectangle (Stack[-0x2c],
`local_2c`) at a local rectangle. With `TextObject_New` and `GetTextParamsFromTable` taking a `TextContext *`, Ghidra
dropped the variable `local_30` (it is left as a one-byte phantom, which `set_local_variable_type` refuses) and prints
the slot as `&stack0xffffffd0`. `tools/build_src.py` put such addresses in a separate array `_stkneg`, so the copy no
longer shared memory with `local_2c` and the text was wrapped at the default rectangle.

`build_src.py` now maps a `STACK0X(0xffff....)` offset into `_frame` when it lies among the frame's own locals (no
deeper than the deepest one): the same memory as the local of that offset, as in the original. Offsets below the
locals stay in `_stkneg`. Of the functions compiled from Ghidra's output only `sputText_MakeTextObjectL` changes
(`entry` and LUA.DLL's `FUN_10017ee0` use offsets below their locals; the rest are overrides); it now compiles
to the same code as on main.

## Hand-written overrides

* `Puck_PointAt`, `Puck_GetYawToPoint` (overrides.c): `Puck *this`, `this->pSector` for `*(void **)((int)this + 0x5c)`.
* `sputCostume_Update`, `sputCostume_DrawMeshShadow` (overrides_logic.c): `CostumeNode *costumeList`; the bodies are
  unchanged.
* `sputText_CreateActorText` (overrides_logic.c): returns `TextObject *`; its local 12-int context is passed as
  `(TextContext *)ctx`.

## Checks

* All four programs compile and link; stubs unchanged (EXE 42, LUA 58, IMUSE 9, CHORE 16).
* LUA.DLL, IMUSE.DLL, CHORE.DLL byte-identical to main's build.
* EXE `.data` / `.rdata`: every difference from main's build is a code address that moved (659 + 171 words), plus
  the build time string; `.bss` identical.
* EXE functions against main's build: 93 of 2912 differ, plus `sputCostume_DrawActorShadow.part.0` (round 2: 65).
  * 28 newly different: the typed functions themselves (the costume stack and chore setters, the text queue and
    drawing functions, `Puck_Construct`, `Puck_Destruct`, `Puck_Normalize`, `Puck_Forward`, `Puck_OrientToPlane`,
    the two Puck overrides), `sputText_Startup` / `Restore` / `Update`,
    `sputLua_RestoreIndirector`, and `sputLua_ConcatFallback`, `sputLua_InputDialog`, `TightenPath` (blocks in
    another order).
  * 3 of the earlier ones changed again: `sputActor_CanActorSeePoint` and `Actor_UpdateLookAt` (the head fields),
    `rdNRaster_DrawNGonGIT` (padding only).
  * What changes, as in the earlier rounds: register choice and scheduling, block order, `flds` / `fstps` where
    integers were moved, indexed addressing. The typed C of the record initialisers (`Costume_InitRecord`,
    `Puck_Construct`, `TextObject_New`) and the overrides was read: the same stores, the float constants with the
    same bits (30, 90, -0.35, 360, 1), the context copy still a 12-dword loop.
* Clean-room (`run.py decomp`, the suite unchanged since types_1.md's runs): with the fix above, the same 33 of 5322
  differ from the reference as for main's build. The log against main's (`run.py compare`, 5333 tests): 1 differs,
  `ims_ids` `id_plus_1`, unstable as in round 2. Before the fix: 37, the four text tests above.
