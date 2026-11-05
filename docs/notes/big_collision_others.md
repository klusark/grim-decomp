# Collision_TestActorAgainstOthers (0x004939f0) in C (agent big_collision_others)

Result: **converted**, `build/overrides_big_collision_others.c` (`/* OVERRIDES: Collision_TestActorAgainstOthers */`).
Checked against the original machine code by a differential test (`build/difftest/big_collision_others/`).
Nothing was regenerated (no build_src.py, gen_asm.py or make), so the function is still in `src/GRIMFANDANGO.EXE/asm_funcs.s`
and will leave it at the next regeneration. The test slices the original from the current `asm_funcs.s`; once the
assembly is gone, run it with `BASE_ASM=<older copy>` (`git show HEAD:src/GRIMFANDANGO.EXE/asm_funcs.s`).

## What it does

`Collision_TestActorAgainstOthers(actor)` loops over the drawable actor list (`g_pDrawableActors` 0x008ca358, count
`g_nDrawableActorCount` 0x008ca330, reread on every pass). It skips the actor itself, actors with no walker record
(`+0xa4`) and actors whose collision mode (`walker+0x3f0`) is 0. Layout used (every field marked "f" is a float, and
the code always reads and writes it with x87 or as a dword bit copy, never through an int conversion):

* actor: `+0x08` flags (int; bit 0 = walking), `+0x0c` position f[3], `+0x18` previous position f[3], `+0x34` frame
  valid, `+0x38` frame f[12] (Actor_GetFrame), `+0xa0` costume (`->+4->+4` = model), `+0xa4` walker record.
* walker: `+0x38` path, `+0x3c + 12*i` path points f[3], `+0x44` current point index (int), `+0x3f0` collision mode
  (int), `+0x3f4` collision scale f, `+0x3f8` collided flag (int).
* model: `+0x5c` radius f, `+0x60..+0x74` box f[6] (min xyz, max xyz), `+0x78` centre f[3].
* globals: 0x008ca348 position before f[3], 0x008ca320 hit point f[3] (also written by Collision_BoxSlide), 0x008ca338
  position after f[3].

For each other actor: world centres A (self) and B (other), radii r0 = radius*scale (self) and r1 (other). If
`sqrt(|A-B|^2) < r0 + r1` (or the comparison is unordered: NaN goes on):

* mode 2 (sphere): both collided flags are set, self is put at `A + n*(1 - (dist - r1)/r0)*r0 - c0` (n = unit vector from
  B to A, c0 = self's rotated model centre) through Actor_SetPositionClamped. The walking bit is read before the call and ORed back afterwards.
* other modes (box): self's centre goes into the other's model space (P) and is tested against the other's box grown by
  r0 (strictly inside the minimum, `<` or unordered for the maximum). If inside: self's collided flag is set, the
  previous centre is transformed the same way (Q), `Collision_BoxSlide(P, Q, box, out)` (if it returns 0:
  `Collision_PushOutOfBox(P, box, frame, &other.pos)` and out = P), out and the hit point are rotated back to world space with
  Vec3_Rotate3x3, previous position = position, Actor_SetPositionClamped(self, out), and a walking actor gets
  bit 0 ORed back and `Walker_ReplanPath(self, copy of path point [idx], walker+0x38, other)`.
* then `Sector_IntersectSegment(self, other, 0x8ca348, 0x8ca320, 0x8ca338)`.

Returns 1.

## x87 details that matter (all checked by mutation, see below)

* The squared distance is `(dx*float(dx) + dy*dy) + dz*float(dz)`. The compiler multiplied one operand from a float
  spill slot (dx and dz rounded) and the other from the register (extended); dy is squared in the register.
  The sqrt and r1 stay extended for the comparison. `t` uses the stored float copies of dist and r1.
* The x component of the previous-centre vector is `c0.x + prev.x - B.x` in one extended expression; y and z are
  rounded to float in between.
* Box limits, P, Q, the push target, the out vector and the hit point are each rounded once at their store.
* Vec3_Normalize leaves the length in ST0; the original pops it (fstp st0). The C calls it as a `float` function, so gcc pops it too.
* Every store to a float slot goes through `cto_st()` (a volatile float). gcc's default `-fexcess-precision=fast`
  rounds neither an assignment nor a `(float)` cast when optimised. The test showed it: at -O2 with plain assignments,
  4116 of 30000 cases differed; with `cto_st` there were 0 differences at -O0, at -O2 and at OPT_FAST.

## Root cause of the old start-up crash

The earlier C was the decompiled text (`src/GRIMFANDANGO.EXE/collision.c`, after `fix_casts`). It had two defects.

1. **Lost call arguments.** `((code *)Actor_SetPositionClamped)()`, `Walker_ReplanPath()` and `Sector_IntersectSegment()`
   are called with no arguments, and `Collision_BoxSlide(local_a4)` and `Collision_PushOutOfBox(local_a4)` with one instead of
   nine. The original pushes them (the decompiler kept only stray traces such as `pvStack_d0 = param_1`). The callees read
   whatever is on the stack, so Actor_SetPositionClamped writes a position through a garbage pointer. This is the most likely crash.
2. **Float structs through int lvalues.** The vectors 0x008ca320/338/348 are only named as `_DAT_008ca3xx`, i.e.
   `(*(undefined4 *)&DAT_...)`. So `_DAT_008ca348 = *pfVar6` truncates the float position to an integer *value*, and
   `_DAT_008ca320 = _DAT_008ca320 - local_98[0]` turns the float bits into an integer, subtracts and converts back. Every
   segment handed to Sector_IntersectSegment, and the hit point, were garbage. (The loop counter and list cursor in
   float-typed stack slots, `local_5c[2]` / `local_74[1]`, were already turned into bit puns by `fix_casts`. In the raw
   decompilation they are value conversions too: `(float)&g_pDrawableActors`.)

The C here gives every slot its real type: int counters, a `void **` cursor, `float *` views of the three global
vectors, and bit copies where the original uses MOV.

I did not reproduce the old crash in the game. The diagnosis comes from reading the generated text.

## Verification

`build/difftest/big_collision_others/run.sh [cases] [seed]`: `build.sh` slices `orig_Collision_TestActorAgainstOthers`
from `asm_funcs.s` (build/mixdiff/slice_orig.py) and compiles the override with the build's GHIDRA_CFLAGS (`EXTRA_CFLAGS=-O2`
to try another level). It links both with the original data image (`build/obj/GRIMFANDANGO.EXE/data_s.o`) and `coll_test.c`.

* Each case builds a random world: 1-7 actors in the list, with the tested actor in it, absent from it, or listed twice. Each
  actor has a costume chain, a model, a frame (a rotation about a random axis, sometimes a non-orthonormal matrix), a
  walker record or none, modes 0/1/2/other, and random scales and radii. A third of the cases place two sphere centres at r0 + r1
  to within a few ulps. Special values (+-0, +-NaN, +-inf, 1e-30, 3e38) are mixed into positions, model data, scales
  and frames. The cases cycle through x87 precision control 24, 53 and 64 bits.
* The callees are models defined in the test; both implementations call the same ones. The Vec3 helpers use the
  formulas of the originals. Vec3_Normalize returns the length in ST0. Actor_SetPositionClamped moves the actor; scripted
  per case, it sometimes clamps, flips flag bit 0 or other bits, or marks the frame dirty. Collision_BoxSlide returns 0 or 1 and
  writes out and the hit point. Collision_PushOutOfBox moves P. Walker_ReplanPath sometimes sets a flag.
* Compared: the return value; the call log, which records every call with the contents of its pointer arguments, global and
  heap pointers by value, and box floats by bits; all actor, walker, model and costume memory; and the data block
  0x008ca300-0x008ca3a0.
* Result: 600000 cases at -O0 (seed default and 12345), 300000 at -O2 and 100000 at OPT_FAST: **0 differences**.
  Branch counts per 300000: about 136000 sphere pushes, 181000 box hits, 61000 push-outs and 102000 replans.
* Sensitivity: 27 deliberate mutations (each comparison's NaN sense, the six box tests, extended against rounded
  temporaries, the order of the flag read and the call, the path-point index, the argument order, a dropped store, the wrong
  source vector) were all detected (22 to 33000 differing cases each). The one undetected mutation (capping the loop at 8)
  is equivalent within the test's list sizes.

## Not verified

* The real callees. The models stand in for Actor_SetPositionClamped, Collision_BoxSlide, Collision_PushOutOfBox,
  Walker_ReplanPath and Sector_IntersectSegment, so only the arguments and their order are checked, not the game's result.
  Actor_GetFrame never rebuilds the matrix in the test.
* Callees that change the actor list or its count during the loop. The C rereads the count each pass like the original,
  but no test case does this.
* No game run: no boot, no qtests coll suite, no oracles. Those need a rebuild, which this task did not do.
