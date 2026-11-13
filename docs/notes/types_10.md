# Types, round 10 (2026-11-12): the walk sectors, WalkPlane

Rounds 1 to 3 typed the actor, its extra record and its walker (`Puck`), whose `pSector` stayed `void *`. The sectors
it points to were read by offset in about 160 places (sector.c, walker.c, the Lua sector functions). This round types
them. Batch: `names/types_walkplane.json`; `names/types_puck.json` retypes `Puck.pSector`.

## WalkPlane (0x84)

One sector of the set file (WalkPlane.cpp; the remaster's demangled symbols name the class `WalkPlane`, its layout is
not in them). `ParseCollection` allocates 0x84 bytes and calls `WalkPlane_Construct`.

| off | field | from |
|---|---|---|
| 0x00 | `char aName[32]` | `WalkPlane_SetName`, `WalkPlane_PlaneNamed` |
| 0x20 | `int nId` | the file's `id`, `WalkPlane_PlaneNumbered` |
| 0x24 | `uint dwType` | `WalkPlane_SetType`: 0x1000 walk, 0x1100 funnel, 0x2000 camera, 0x4000 special, 0x8000 chernobyl (the keywords `ParseCollection` compares) |
| 0x28 | `int nVisible` | the file's `default visibility`; `ShrinkBoxes` clears it for a sector it cannot shrink, the cache restores it |
| 0x2c | `int nActive` | 1 at load, `WalkPlane_AllActive`, Lua `MakeSectorActive`; `Planner_SharedSector` clears it while it searches |
| 0x30 | `float flHeight` | `WalkPlane_Within`'s distance from the plane: 0.005 for walk sectors, 9999 else |
| 0x34 | `int nNumVerts` | 3 to 10 |
| 0x38 | `WalkVertex *aVerts[10]` | records of the vertex pool |
| 0x60 | `float aNormal[3]` | Newell's normal, normalised |
| 0x6c / 0x70 | `WalkPlane *pPrev, *pNext` | the list `g_pWalkPlane_wp_head` |
| 0x74 | `int nHitEdge` | the edge `WalkPlane_Intersection` crossed last, -1 none; `JumpOut` / `GetConstraintVector` step it |
| 0x78 | `int nLongEdge` | funnel sectors: first vertex of the long edge, 0 to 3 |
| 0x7c / 0x80 | `int nAxisU, nAxisV` | the two axes the polygon is projected on for the 2-D tests |

Three more records: `WalkVertex` (16: `int nRefs`, `float aPos[3]`), the pool's record, which `WalkPlane_AddVertex`
shares between sectors whose corners are closer than 1e-4; `WalkPlaneCache` (0x34) and `WalkVertexCache` (0x14), what
`WalkPlane_BuildCache` saves before `ShrinkBoxes` and `WalkPlane_RestoreCache` puts back.

Typed with them: the `this` of the 13 `__thiscall` sector methods, `WalkPlane_Destruct`,
`WalkPlane_RemoveShortEdge`, `FindExitPoints`, `Planner_PortalPoint` (its two sectors, `float *point`, `float *out`),
`Planner_FindPath`; the results of `Construct`,
`PlaneAt`, `PlaneNamed`, `PlaneNumbered`, `PlaneClosest`, `Planner_SharedSector` (three of them through `protos`:
their signatures were not committed); the globals `g_pWalkPlane_wp_head`, `g_pWalkPlaneCache`, `g_pVertexCache`, and
the pool itself, `g_aWalkPlane_vert_db` (`WalkVertex[1024]` at 0x008cb0b0, which was `FLOAT_008cb0b0`,
`UINT_008cb0b4`, `UINT_008cb0b8` and `UINT_008cb0bc[16372]`). 66 exported functions use the types.

The generated code reads sectors by field: `for (p = g_pWalkPlane_wp_head; p != 0 && p->nId != id; p = p->pNext)`,
`if ((this->dwType & mask) == 0 || ...)`, `g_aWalkPlane_vert_db[i].nRefs = (pWVar3->vert).nRefs`.

## Four regressions the typing introduced

Typing changes how Ghidra prints a function, and four of its new spellings meant something else in C. The first two
were found reading the generated code; the clean-room found the other two (106 tests differing, then 2), against
0 of 5167 for `main`'s build.

* **The pool's reference count as a float.** With the cache typed, `WalkPlane_RestoreCache` read
  `FLOAT_008cb0b0[i * 4] = (float)cache->vert.nRefs`: in C a conversion of the count to a float (1 becomes
  0x3f800000), where the original copies the word. The first word of a pool record is the count everywhere (the
  float was Ghidra's guess); typing the pool as `WalkVertex[1024]` makes the copy an `int` one, and makes
  `WalkPlane_AddVertex` read like the original (`pWVar4->nRefs = pWVar4->nRefs + 1`). Its first loop still tests the
  count as a float (`(float)...->nRefs != 0.0`, the original's `fld` / `fcomp`), which is true for every count the
  pool can hold, as before.
* **Float members copied as words.** `WalkPlane_BuildCache`, `WalkPlane_RemoveShortEdge`, `Puck_Forward` and
  `FindExitPoints` copy a vertex's position into integer slots; Ghidra prints `piVar1[1] = (int)pWVar2->aPos[0]`, again a conversion in C. `fix_casts` already makes
  `(int)<float>` a `PUN` in functions without FIST / CVTT (`int_float_conversions`), but `type_of` does not know the
  types of members (round 9 tried that and rewrote 61 files). `tools/build_src.py`'s `float_member` now answers for
  that branch only: a member that is `float` in every structure of `structs.json` that has it, or an element of a
  `float[N]` one (the array itself, `(int)p->aPos`, is an address, not a float). It changed eleven lines in sector.c
  and walker.c and nothing else.
* **A pool index from the original's address.** `WalkPlane_BuildCache` turns a vertex pointer into a pool index,
  `sub eax, 0x8cb0b0; sar eax, 4`. Untyped, Ghidra wrote `ptr - (int)&FLOAT_008cb0b0 >> 4`; with a `WalkVertex *` it
  folds the address into element units, `(int)(*ppWVar4 + -0x8cb0b) >> 4`, and the symbol is gone. The rebuilt pool is
  at 0x8ca130, so every index was 248 too small and `WalkPlane_RestoreCache` wrote the vertices in front of the pool:
  `shrink_pos` and `shrink_boxes` crashed, and so did the text tests of `zz_args.lua` (its sets and actors follow
  boxes). `ptrdiff` already rewrote that pattern for `int *` (an address divided by 4); `struct_ptrdiff` does it for a
  pointer to a structure of `structs.json` (the declaration gives the type, the structure's size the scale):
  `(WalkVertex *)((char *)*ppWVar4 - IMG_ADDR(0x008cb0b0))`, which datagen turns into the pool's name. Four places,
  in `WalkPlane_BuildCache` and in the decompiled `ShrinkBoxes` (not built: overrides_logic.c has it).
* **A point copied through `undefined4 *`.** `Planner_PortalPoint` writes the nearest shared vertex to its fourth
  parameter, `*param_4 = pWVar1->aPos[0]`: no cast for `fix_casts` to see, an implicit conversion in C. The caller
  reads the slots as floats, so each coordinate became its integer part's bits (a denormal, or a NaN for a negative
  one), and the walk ended at NaN (`path_back`, `amc_path_back`). The parameter is `float *out` now.
  GCC's `-Wfloat-conversion` finds this kind: on the files this round changed it reports 6 (all of them here) before
  the fix and 0 after, as for `main`.

## Hand-written code

`WalkPlane_DistToEdge` (overrides.c), `WalkPlane_Within` (overrides_asm_o2.c) and `WalkPlane_ClosestPoint`
(overrides_cleanroom.c) take `WalkPlane *this`; their bodies read by offset through `(int)this` and are unchanged.
`ShrinkBoxes` (overrides_logic.c) casts its byte pointer for the calls and takes the pool as `g_aWalkPlane_vert_db`;
`GetShrinkPos` (overrides_exe.c) holds a `WalkPlane *`.

## Other changes

* `tools/datagen.py`: an all-zero array of structures is `= {0}` (the pool took 1024 lines of `{0},`).
* The journal's `*struct*` (the `Puck` field) was cut to the nine functions whose export mentions `pSector`.

## Checks

* All four programs compile and link; no new stub (EXE 32, LUA 35, IMUSE 8, CHORE 14, as `main`).
* `datacmp.py` against `main`'s build: 0 differences, 0 moved, 0 missing in all four. LUA.DLL, IMUSE.DLL and CHORE.DLL
  are byte-identical; only the EXE's code changes.
* `-Wfloat-conversion` on the eight EXE files this round changed: 0, as for `main`.
* Clean-room against grim_tools' knowngood (5167 tests): all 5167 the same as the reference, as `main`'s build. The
  first build had 106 differing (the shrink crashes and the `zz_args.lua` text tests), the second 2 (`path_back`,
  `amc_path_back`); see above.
