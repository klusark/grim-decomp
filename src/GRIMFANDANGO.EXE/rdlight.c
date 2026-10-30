/* GRIMFANDANGO.EXE :: rdlight.c
 * functions 0x00451460 .. 0x00451510 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00451460  rdLight_Init ---- */
/* Defaults: type 2, on, white (0xffffff), intensity 1.0 */

undefined4 rdLight_Init(int param_1)

{
  *(undefined4 *)(param_1 + 4) = 2;
  *(undefined4 *)(param_1 + 8) = 1;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x1c) = 0xffffff;
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  return 1;
}

/* ---- 0x004514a0  rdLight_SetAngles ---- */
/* inner (umbra, degrees) -> +0x20, cos +0x24; outer (penumbra) -> +0x28, cos +0x2c; +0x30 =
   1/(cosInner - cosOuter) only when positive, else left as is (0 from the set load memset => hard
   edge at the penumbra). Called by Set_LoadResources with the raw set values (half angles, not
   halved). */

void __cdecl rdLight_SetAngles(void *light,float inner,float outer)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0;
  *(float *)((int)light + 0x20) = inner;
  *(float *)((int)light + 0x28) = outer;
  Math_SinCosTable(inner,&local_4,(float *)((int)light + 0x24));
  Math_SinCosTable(outer,&local_4,(float *)((int)light + 0x2c));
  fVar1 = *(float *)((int)light + 0x24) - *(float *)((int)light + 0x2c);
  if (0.0 < fVar1) {
    *(float *)((int)light + 0x30) = 1.0 / fVar1;
  }
  return;
}
#undef local_4


/* ---- 0x00451510  rdLight_CalcVertexIntensities ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Per-vertex light level (monochrome, light colour unused). out[v] = base[v] + sum over lights,
   clamped to <= 1 after each light (stops at 1). Returns the mean.
   Lights culled when dist >= light+0x34 (= intensity / 0.2). k = camera+0x45c = 0.2
   (rdCamera_Init).
   type 0/1 direct: I * dot(n, -dir) if > 0.
   type 2 omni: (I - k*dist) * dot(n, L) if > 0.
   type 3 spot: c = dot(-dir, L); if c > cosOuter(+0x2c): I' = I, or I * (1 - (cosInner(+0x24) - c)
   * invRange(+0x30)) when c < cosInner; adds (I' - k*dist) * dot(n, -dir) UNCLAMPED (uses the spot
   axis, not L).
   L = normalised light pos - vertex (model space), -dir = negated beam direction. */

float __cdecl
rdLight_CalcVertexIntensities
          (int *param_1,float *param_2,int param_3,uint param_4,int *param_5,uint param_6,
          float *param_7,float *param_8,uint param_9,float param_10)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  int iVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  float *pfVar6;
  float *pfVar7;
  float fVar8;
  #define local_2c (*(uint *)(_frame + (0x40 - 0x2c)))
  #define local_28 (*(float (*)[3])(_frame + (0x40 - 0x28)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_c (*(float (*)[3])(_frame + (0x40 - 0xc)))
  
  local_28[0] = 0.0;
  if (param_9 != 0) {
    local_2c = param_6;
    iVar5 = param_6 - (int)param_5;
    iVar4 = (int)param_7 - (int)param_8;
    pfVar7 = (float *)(param_5 + 2);
    local_1c = param_9;
    do {
      local_28[1] = 0.0;
      *param_8 = *(float *)(iVar4 + (int)param_8);
      if (param_4 != 0) {
        param_5 = param_1;
        param_7 = param_2;
        pfVar6 = (float *)(param_3 + 8);
        do {
          iVar2 = *param_5;
          if (*(int *)(iVar2 + 4) < 2) {
            fVar3 = 0.0;
          }
          else {
            local_c[0] = *param_7 - *(float *)local_2c;
            local_c[1] = *(float *)(((int)param_2 - param_3) + -4 + (int)pfVar6) -
                         *(float *)(iVar5 + -4 + (int)pfVar7);
            local_c[2] = *(float *)(((int)param_2 - param_3) + (int)pfVar6) -
                         *(float *)(iVar5 + (int)pfVar7);
            fVar3 = local_c[2] * local_c[2] + local_c[1] * local_c[1] + local_c[0] * local_c[0];
          }
          if (fVar3 < *(float *)(iVar2 + 0x34) * *(float *)(iVar2 + 0x34)) {
            switch(*(undefined4 *)(iVar2 + 4)) {
            case 0:
            case 1:
              fVar3 = *pfVar6 * *pfVar7 + pfVar6[-1] * pfVar7[-1] + pfVar6[-2] * pfVar7[-2];
              if (0.0 < fVar3) {
                fVar3 = *(float *)(iVar2 + 0x18) * fVar3;
LAB_0045173f:
                *param_8 = fVar3 + *param_8;
              }
              break;
            case 2:
              fVar8 = Vec3_Normalize(local_c);
              fVar3 = *pfVar7 * local_c[2] + pfVar7[-1] * local_c[1] + pfVar7[-2] * local_c[0];
              if (0.0 < fVar3) {
                fVar3 = (*(float *)(iVar2 + 0x18) - fVar8 * param_10) * fVar3;
                goto LAB_0045173f;
              }
              break;
            case 3:
              fVar8 = Vec3_Normalize(local_c);
              fVar3 = *pfVar6 * local_c[2] + pfVar6[-2] * local_c[0] + pfVar6[-1] * local_c[1];
              if (*(float *)(iVar2 + 0x2c) < fVar3) {
                fVar1 = *(float *)(iVar2 + 0x18);
                if (fVar3 < *(float *)(iVar2 + 0x24)) {
                  fVar1 = (1.0 - (*(float *)(iVar2 + 0x24) - fVar3) * *(float *)(iVar2 + 0x30)) *
                          fVar1;
                }
                fVar3 = (fVar1 - fVar8 * param_10) *
                        (*pfVar7 * *pfVar6 + pfVar6[-2] * pfVar7[-2] + pfVar6[-1] * pfVar7[-1]);
                goto LAB_0045173f;
              }
            }
          }
          if (1.0 < *param_8) {
            *param_8 = 1.0;
          }
          if (*param_8 == 1.0) break;
          param_5 = param_5 + 1;
          local_28[1] = (float)(PUN(int,(float)local_28[1]) + 1);
          param_7 = param_7 + 3;
          pfVar6 = pfVar6 + 3;
        } while (PUN(uint,(float)local_28[1]) < param_4);
      }
      pfVar7 = pfVar7 + 3;
      local_28[0] = local_28[0] + *param_8;
      local_2c = local_2c + 0xc;
      param_8 = param_8 + 1;
      local_1c = local_1c - 1;
    } while (local_1c != 0);
  }
  return local_28[0] / (float)param_9;
}
#undef local_18
#undef local_1c
#undef local_28
#undef local_2c
#undef local_c

#endif

