# Walker_AvoidActorPath (0x004917e0) to C

Result: **converted**, `build/overrides_big_walker_avoid.c` (`/* OVERRIDES: Walker_AvoidActorPath */`), verified against
the original machine code by a differential test (`build/difftest/big_walker_avoid/`): 0 differences in 1,000,000
random cases, both with the Makefile's GHIDRA_CFLAGS and with the flags `build/link.py` really uses for `overrides_*.c`.
Nothing was regenerated: the function is still in `src/GRIMFANDANGO.EXE/asm_funcs.s` and leaves it at the next
`build_src.py` / `gen_asm.py --select` run.

## What it does

`Walker_AvoidActorPath(self, other, pts, count, out)` (called from the walker path set-up, walker.c) copies the walk path
`pts[count]` to `out` and makes it go round the collision box of actor `other`.  Returns the number of points written.

* `other == NULL`: plain copy, returns `count` (0 when `count < 1`).
* Radius r = `self->a4->0x3f4 * costume(self)->0x5c`; box of `other` = its costume box (+0x60 .. +0x74) times its
  scale (`other->a4->0x3f4`), grown by r.  Both ends of the path are pushed out of the box (Collision_PushOutOfBox); the
  last point is the target.  No sector at the target: returns 0.
* The segments are copied until one hits the box (Collision_SegmentHitsBox).  No hit: the last point is appended.
* Hit: the four box corners (Collision_BoxCorners, radius r + 0.02, at the snapped height of DAT_008ca320 - frame) get
  a flag "reachable from the segment start without crossing the box and the planner finds a path"; Collision_PickDetour
  picks one; its planner path is appended.  If the target is reachable from there (Collision_PointInBox) the final path is
  appended.  Otherwise the walk goes round the box from the neighbour corner a = idx-1 or b = idx+1 (the reachable one; if
  both, the one with the shorter last point - corner - target squared distance; ties and NaN choose b), corner by corner
  until the target is reachable or it is back at the first corner.  Every planner path is checked against the box; a hit
  returns 0.

Faithfully kept quirks:

* When neither neighbour corner is reachable the original takes the stale frame slot 0x10 (the radius float's bits) as
  the corner index and slot 0x1c (count - 1) as the step.  With r = +-0 that is corner 0 (12 * 0x80000000 wraps to 0);
  otherwise a wild pointer is passed to Planner_PlanPath (the real planner would read it).  The C computes the same
  32-bit address from the same frame layout.
* The locals are one byte array with the original frame layout (the corner flags must follow the corners: PickDetour
  reads them at corner + 0x30; a negative wrapped index reads other locals).  All slot reuses of the original are kept,
  so the frame equals the original's at every call.
* x87: long double for the temporaries the original keeps on the FPU stack, float stores where it stores; the distance
  sums are evaluated in the original's order with its mix of extended and stored-float operands (e.g. `d1x * (float)d1x`).
  Point copies are dword moves (no sNaN quieting).  The box goes to the callees as six dwords (struct by value).

The decompiler missed the box passed by value (six dwords copied with `rep movsd` before the call) to PushOutOfBox,
SegmentHitsBox and PointInBox, the extra arguments pushed before Actor_GetFrame calls and used by the following call,
and the int return of Collision_PickDetour (shown as a float compared with -NaN).

## Verification (`build/difftest/big_walker_avoid/run.sh [cases]`)

`wav_test.c` links the sliced original (`orig_Walker_AvoidActorPath`) and the C with recorders for all 13 callees.  Both
versions run on a private stack filled with the same pattern, from the same start state, with the recorders driven by the
same random stream.  Compared: return value; each call's arguments (test-buffer pointers absolute, frame pointers
relative to the frame base, plus the 3/6/12/16 dwords behind them); a dump of the whole 0x104-byte frame at every call;
the output buffer with guard space; the input points (the push-out recorder writes them); DAT_008ca320.  Inputs: random
actors, scales (often 0 / -0), counts 0..7, NULL actor, values from a coarse grid (exact ties), full-mantissa values,
corners within 1-2 ulp of each other (near ties), 0 / -0 / inf / NaN / sNaN; random hit / plan / in-box results, path
lengths -1..6; x87 precision 24 / 53 / 64 bits by turns.

Coverage in 1,000,000 cases: 82952 NULL actor, 431857 reached the detour, 74907 chose by distance, 100159 walked round
the box, 166824 appended a final path, 52488 used the wild corner pointer.

Sensitivity (mutations, all reported): NaN compare written as `sb <= sa`; `d1x` / `e1x` products with the stored float
only; `e2z` rounded to float; box product rounded before the subtraction; radius rounding; the 0.02 constant; the step
sign; a dropped frame store; the swapped segment ends of the final check; the corner flag not cleared; corner 0 for the
stale index.  Not detected: the two sums rounded to double before the compare (would need sums equal to 53 bits but not
to 64).

## Not covered

* The callees are recorders: the real Planner / Collision / Sector code and their interplay with real sector data are
  not exercised (no in-game run was done; the game was not built).
* The wild-pointer path is compared only as far as the pointer value goes; what the real planner does with it is not.
* Verified at -O0 only (the build's setting for overrides).  At -O2 gcc keeps some float frame stores unrounded and the
  corner choice differs in about 1 case in 1000 (also with -fexcess-precision=standard).
