/* GRIMFANDANGO.EXE :: rdlight.c
 * functions 0x00451460 .. 0x00451510 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00451460  rdLight_Init ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
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
#endif


/* ---- 0x004514a0  rdLight_SetAngles ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
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

#endif


/* ---- 0x00451510  rdLight_CalcVertexIntensities ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Blends keyframe node transforms into the puppet's output matrices (returns the weight) */

float __cdecl
rdKeyframe_Interpolate
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
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x40 - 0x4)))
  
  local_28 = 0;
  if (param_9 != 0) {
    local_2c = param_6;
    iVar5 = param_6 - (int)param_5;
    iVar4 = (int)param_7 - (int)param_8;
    pfVar7 = (float *)(param_5 + 2);
    local_1c = param_9;
    do {
      local_24 = 0;
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
            local_c = (uint)(*param_7 - *(float *)local_2c);
            local_8 = (uint)(*(float *)(((int)param_2 - param_3) + -4 + (int)pfVar6) -
                            *(float *)(iVar5 + -4 + (int)pfVar7));
            local_4 = (uint)(*(float *)(((int)param_2 - param_3) + (int)pfVar6) -
                            *(float *)(iVar5 + (int)pfVar7));
            fVar3 = (float)local_4 * (float)local_4 +
                    (float)local_8 * (float)local_8 + (float)local_c * (float)local_c;
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
              fVar8 = Vec3_Normalize((float *)&local_c);
              fVar3 = *pfVar7 * (float)local_4 +
                      pfVar7[-1] * (float)local_8 + pfVar7[-2] * (float)local_c;
              if (0.0 < fVar3) {
                fVar3 = (*(float *)(iVar2 + 0x18) - fVar8 * param_10) * fVar3;
                goto LAB_0045173f;
              }
              break;
            case 3:
              fVar8 = Vec3_Normalize((float *)&local_c);
              fVar3 = *pfVar6 * (float)local_4 +
                      pfVar6[-2] * (float)local_c + pfVar6[-1] * (float)local_8;
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
          local_24 = local_24 + 1;
          param_7 = param_7 + 3;
          pfVar6 = pfVar6 + 3;
        } while (local_24 < param_4);
      }
      pfVar7 = pfVar7 + 3;
      local_28 = (uint)((float)local_28 + *param_8);
      local_2c = local_2c + 0xc;
      param_8 = param_8 + 1;
      local_1c = local_1c - 1;
    } while (local_1c != 0);
  }
  return (float)local_28 / (float)param_9;
}
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_28
#undef local_2c
#undef local_4
#undef local_8
#undef local_c

#endif

