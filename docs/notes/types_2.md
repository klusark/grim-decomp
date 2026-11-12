# Types, round 2 (2026-11-11): ActorExtra and the shadow slots

Round 1 (types_1.md) typed the actor record and left its `pExtra` untyped. This round types what it points to,
in the same batch (`names/types_actor.json`, which now holds the three structures in dependency order).

## ActorExtra (0x4a0)

Allocated on first use by `sputActor_AllocateActorExtra`, which zeroes it and sets the defaults given below.

| off | field | |
|---|---|---|
| 0x000 | `float aLookAt[3]` | head look-at point (`sputLua_ActorLookAtL`); 0, 0, 0 for none |
| 0x00c | `int nWalking` | a walk chore is wanted this frame (`Actor_UpdateMoveChores` fades it in or out) |
| 0x010 | `int nTurning` | > 0 left, < 0 right |
| 0x014 | `int nResting` | cleared when a walk or turn chore fades in (`IsActorResting`) |
| 0x018 | `float flWalkRate` | 0.4 |
| 0x01c | `float flTurnRate` | 135 |
| 0x020 | `int nAlignTurn` | `sputActor_AlignToPuck`'s result this frame |
| 0x024 | `float flOffsetYaw` | `SetActorOffsetYaw` |
| 0x028 | `float flYawLeft` | yaw still to turn (`IsActorTurning`) |
| 0x02c | `float aWaypoint[3]` | the path node being walked to |
| 0x038 | `float aDest[3]` | the walk's destination |
| 0x044 | `int nPathNodes` | |
| 0x048 | `float aPath[30][3]` | the path (`sputActor_ActorWalkTo` copies `Walker_AvoidActorPath`'s nodes) |
| 0x1b0 | `int nPathIndex` | |
| 0x1b4 | `void *pPuck` | the walker's Puck (0x60) |
| 0x1b8 | `int nFollowBoxes` | |
| 0x1bc | `int nWalkDominate` | |
| 0x1c0 | `float flPuckRadius` | 60, given to `Puck_Construct` |
| 0x1c4 | `int nTalking` | speech, from `sputActor_SayLine` / `sputActor_ShutUp` ... |
| 0x1c8 | `int nVoiceSound` | iMUSE sound of the voice, 10000 for a voice stream |
| 0x1cc | `int nTalkTime` | time left of a line without voice, -1 with one |
| 0x1d0 | `char aMsgId[12]` | message id |
| 0x1dc | `char aVoiceFile[16]` | `<id>.wvc` / `.wav` / `.imc` / `.imu`, empty without voice |
| 0x1ec | `void *pText` | the line's text object |
| 0x1f0 | `int nLipSync` | `iMUSE_GetPhoneme` of the voice |
| 0x1f4 | `int nActiveShadow` | the slot the Lua shadow calls work on |
| 0x1f8 | `ActorShadow aShadows[6]` | |
| 0x3f0 | `int nCollisionMode` | 2: the box test of `Collision_TestActorAgainstOthers` |
| 0x3f4 | `float flCollisionScale` | 1 |
| 0x3f8 | `int nCollided` | set by the collision test, cleared each frame by `sputActor_UpdateActors` |
| 0x3fc | `int nClipPlaneActive` | read by `sputCostume_InternalDraw3D` |
| 0x400 | `float aClipNormal[3]` | 0, 0, 1 (`sputActor_SetClipPlane`) |
| 0x40c | `float aClipPoint[3]` | |
| 0x418 | `uint dwTalkColor` | 0xffffff |
| 0x41c | `float flTimeScale` | 1 |
| 0x420 | `int nInvClipNode` | -1 |

0x424-0x49f is never read or written; it stays a pad.

**ActorShadow (0x54):** `int nActive`, `int nValid` (0 always drawn, -1 / 1 only on that side of the plane),
`float aPlane[4]` (normal and d), `float aPoint[3]` (the light point), `void *aClipPlanes[12]` (WalkPlane sectors the
shadow is clipped to, zero-terminated).

Typed with them: `Actor.pExtra` (`ActorExtra *`), `g_pTalkingActors` (`Actor *[4]`, was one `void *` with the
other three slots reached by address), and the `shadow` parameters of `sputCostume_DrawMeshShadow` and
`sputCostume_OutputShadowPoly` (`ActorShadow *`).

```c
  *(int *)((int)actor->pExtra + (shadowIdx + 6) * 0x54) = active;     actor->pExtra->aShadows[shadowIdx].nActive = active;
  iVar1 = *(int *)((int)actor->pExtra + 0x1b4);                       this = actor->pExtra->pPuck;
```

Two loops keep their byte offsets, written from the start of the record (`(int)pExtra->aLookAt + iVar` with `iVar`
starting at 0x48 or 0x1f8): the path copy of `sputActor_ActorWalkTo` and the shadow loop of
`sputCostume_DrawActorShadow`. The decompiler kept the loop counter as a byte offset.

## Bridge findings (tools/apply_types.py)

* `create_struct` does not parse `float[30][3]`. `create_array_type` (base `float[3]`, length 30) makes the type,
  after which the field resolves by name.
* Retyping a field to a pointer to a structure (`pExtra` to `ActorExtra *`) left the field unnamed, also when the
  structure existed. `apply_types.py` now names such fields again by offset (`offset:N`), and it checks the fields of a
  structure it creates, not only the size.
* The struct change journals `*struct*` (a full export). As in round 1 the journal was cut to what uses the type:
  the 69 functions whose export mentions `pExtra`, plus the touched parameters and globals (123 functions with their
  referrers, then 38 after `sputCostume_OutputShadowPoly`).

## Hand-written overrides

`sputCostume_DrawMeshShadow` (overrides_logic.c) takes `ActorShadow *shadow` and reads `shadow->aPoint` /
`shadow->aPlane[]` in place of the byte offsets. At -O0 the offset now folds into the load (`flds 0x14(%eax)` for
`addl $0x14,%eax; flds (%eax)`); nothing else changes.

## Checks

* All four programs compile and link; stubs unchanged (EXE 42, LUA 58, IMUSE 9, CHORE 16).
* LUA.DLL, IMUSE.DLL, CHORE.DLL byte-identical to main's build.
* EXE against main's build: 65 of 2912 functions differ, plus `sputCostume_DrawActorShadow.part.0` (round 1: 60).
  Against round 1's list:
  * 6 newly different: `sputActor_Initialize` (the four `g_pTalkingActors` stores in another order),
    `Actor_IsVoicePlaying` (another register), `sputActor_SetShadowPlane` (the plane copied with `flds` / `fsts`
    where it moved integers), `sputActor_AddShadowClipPlane` (indexed addressing), `sputActor_ActorWalkTo`
    (the destination copied as floats), `sputCostume_DrawMeshShadow` (the override above).
  * 1 identical to main again: `sputActor_SetShadowPoint`.
  * 9 of round 1's changed their length again: `sputActor_AllocateActorExtra`, `sputActor_EnablePuck`,
    `sputActor_SayLine`, `sputActor_ResetShadows`, `sputCostume_InternalDraw3D`, `sputActor_FreeActor`,
    `sputLua_ActorDistToShadowPlane`, `sputActor_Restore`, and `rdCache_SendFaceListToHardware` (padding only).
  The C of the changed functions was read: field accesses for the byte offsets, `aShadows[idx]` for
  `(idx + 6) * 0x54`, `aPath + nPathIndex` for `(nPathIndex + 6) * 0xc`.
* Clean-room (`run.py decomp`, on the suite of types_1.md's runs, no file of it changed since): the same 33 of 5322
  differ from the reference as for main's build and round 1. The log against main's (`run.py compare`, 5333
  tests): 1 differs, `ims_ids` `id_plus_1` (1 / 0), a value the suite lists as unstable (`expected/unstable.txt`;
  orig-7 saw it flip between builds too).
