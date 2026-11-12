# Types, round 1 (2026-11-11): struct layouts in the generated tree, Actor

The names series (orig_summary.md) changed no types. This round adds the machinery for struct types and types the
first structure, the actor record, as the pilot.

## Machinery

* **Layouts out of Ghidra.** `tools/export_raw.py` writes `raw/<prog>/structs.json` (every structure of the program's
  own data types, from `get_struct_layout`; the PE / DOS loader types and `IMAGE_*` are left out). Both `export_raw.py`
  and `export_changed.py` refresh it.
* **Layouts into src.** `tools/build_src.py` emits each structure into `ghidra_types.h`: a forward typedef for all of
  them, then the definitions in dependency order (a structure held by value comes first). Gaps become
  `uint8_t _pad_<off>[n]`; every field offset and the size are checked by `_Static_assert`, so a wrong export cannot
  move a field silently. A misaligned field makes the structure `packed`. Field types Ghidra has and C does not
  (function definitions, `pointer`, ...) become `void *` or bytes of the same size. Structures that `build/compat.h`
  defines by hand (GrimServices, CHORE.DLL's costume records) keep the hand-written definition and are only declared.
  This closes BUILD_NOTES' blocker 2 ("struct layouts are not exported").
* **Field comments.** Ghidra's layout listing has no comments, so `build_src.py` takes the structure and field
  comments from the types batches (`names/types_*.json`).
* **Types batches.** `tools/apply_types.py names/types_<x>.json` applies, idempotently:
  * `structs`: creates a new structure (no export needed: nothing uses it yet), or renames / retypes / adds fields of an
    existing one in place (`modify_struct_field`, `add_struct_field`, which takes the undefined bytes at its offset and
    moves nothing). It never recreates a used structure: that detaches every parameter and global typed with it.
  * `params`: parameter types and names by index. A function with no committed signature (Ghidra shows
    `undefined f(void)` and the decompiler infers the parameters) gets the decompiler's inferred prototype committed
    as `__cdecl` with the parameter retyped (21 of the 51 Actor parameters).
  * `protos`: a whole prototype, for functions whose committed signature is incomplete. `returns`: a return type,
    refused when the committed signature lacks the parameters the decompiler shows (setting only the return type of
    `sputActor_ActorDeref` dropped its `int handle`; it is a `protos` entry now).
  * `globals`: data types of globals.
  All writes name their program in the query string, so the bridge's current program is never switched (another
  session had Monkey4.exe open in the same Ghidra).
* **Bridge naming policy.** The bridge rewrites field names to its Hungarian rules (`afPos` -> `aAfPos`,
  `bInUse` -> `nInUse`): arrays `a...`, `int` `n...`, `uint` `dw...`, `float` `fl...`, pointers `p...`. The batches use
  names that pass unchanged; `apply_types.py` reports any field that does not end up as asked.

## Actor (0xa8, names/types_actor.json)

| off | field | |
|---|---|---|
| 0x00 | `void *pColormapRef` | 0x34-byte resource reference of the colormap |
| 0x04 | `uint dwFlags` | 2, 4 (has a speech text), 8, 0x10 (ActorPuckOrient) |
| 0x08 | `uint dwMoveFlags` | 1 path walk active, 2 turning |
| 0x0c | `float aPos[3]` | |
| 0x18 | `float aPrevPos[3]` | position at the start of the frame |
| 0x24 | `float aRot[3]` | pitch, yaw, roll |
| 0x30 | `float flScale` | |
| 0x34 | `int nMatrixDirty` | |
| 0x38 | `float aOrient[12]` | rdMatrix34 |
| 0x68 | `int nScreenBoxValid` | |
| 0x6c | `int aScreenBox[4]` | x, y, width, height |
| 0x7c | `char aSetName[32]` | |
| 0x9c | `int nInUse` | |
| 0xa0 | `void *pCostumes` | costume stack |
| 0xa4 | `void *pExtra` | ActorExtra (0x4a0), still untyped |

Typed with it: 51 parameters (every `sputActor_*` / `Actor_*` taking an actor, `sputRoom_AddActor`,
`sputText_CreateActorText`, `sputCostume_DrawActorShadow`, both actors of `sputActor_CanActorSeeActor`), named `actor`;
`Actor * sputActor_ActorDeref(int handle)`; the globals `g_pActors`, `g_pSelectedActor`, `g_pLightEdMarkerActor`.
The decompiler propagated the type into two functions with uncommitted signatures, `Collision_TestActorAgainstOthers`
and `Walker_AvoidActorPath`. `g_pTalkingActors` (four actor pointers) is left for the next round.

Decompilation, before and after (`sputActor_FreeActor`):

```c
  if (*(char *)((int)actor + 0x7c) != '\0') {            if (actor->aSetName[0] != '\0') {
    sputRoom_RemoveActor((char *)((int)actor + 0x7c),        sputRoom_RemoveActor(actor->aSetName,actor);
  ...                                                     ...
  *(undefined4 *)((int)actor + 0x9c) = 0;                 actor->nInUse = 0;
```

Indexing became C pointer arithmetic (`g_pActors + handle`, was `(int)g_pActors + handle * 0xa8`). The re-export
covered the 54 touched addresses and their callers (181 functions, 129 after the ActorDeref fix).

## Hand-written overrides

Nine overrides implement functions whose prototype now takes `Actor *` (`Actor_UpdateWalker`, `Actor_UpdateMovement`,
`Actor_PuckOrient`, `sputActor_UpdateActorSpeech`, `sputText_CreateActorText`, `sputActor_AlignToPuck`,
`sputActor_DrawToClean`, `Collision_TestActorAgainstOthers`, `Walker_AvoidActorPath`). Their parameter is `Actor *x_`
now and the body starts with the old untyped `x` (`void *x = (void *)x_;`, `int` for Actor_UpdateWalker), so the
bodies, which work on byte offsets, are unchanged. Rewriting them on the fields is later work.

## Checks

* All four programs compile and link; stubs unchanged (EXE 42, LUA 58, IMUSE 9, CHORE 16).
* LUA.DLL, IMUSE.DLL, CHORE.DLL: .text / .data / .rdata byte-identical to main's build.
* EXE, function by function against main's build (objdump of both, code addresses that moved normalised): 60 of
  2912 functions differ, 1 new (`sputCostume_DrawActorShadow.part.0`, gcc split the function).
  * 7 padding only, 2 branch offsets only, 8 the same instructions in another order.
  * 9 the overrides above (-O0: the alias costs one stack slot).
  * 34 generated functions, compiled differently: register choice and scheduling; pointer subtraction
    (`actor - g_pActors`, exact division) where `/ 0xa8` was; position copies that moved integers (`movl`) now load and
    store floats (`flds` / `fstps`; the same bits for every value but a signalling NaN); gcc's partial inlining of
    `sputCostume_DrawActorShadow`. Their C diffs were read: field accesses for byte offsets, scaled indexing for
    `* 0xa8`, the zeroing loops written as an `Actor *` stepping four bytes (`p = (Actor *)&p->dwFlags`), which
    clears what it cleared before.
* Clean-room (`run.py decomp`, 5322 tests against the reference, 11 new tests not in it yet): the typed build and
  main's build, run back to back on an unchanged suite, differ from the reference in the same 33 tests (27 `cm_*`,
  which the suite's own changes of the day brought in, and sound_fade, gl1_say_right_edge, ims_voices, ims_save,
  ims_save_voice, rnd_say_low, the six orig-7 saw). The two logs compared with each other (`run.py compare`,
  5333 tests): 1 differs, `ims_cache` `ids` (-225 / 31, the Lua ids turning round at 256), a value the suite lists
  as unstable (`expected/unstable.txt`).
