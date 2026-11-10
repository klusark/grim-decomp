/* GRIMFANDANGO.EXE :: plane.c
 * functions 0x00486a10 .. 0x00486a10 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00486a10  sputRender_SegmentPlaneIntersect ---- */
/* Original name sputRender_SegmentPlaneIntersect (the remaster's GrimFandango (Linux): same body
   (plane distance of both points, |d| < 0.1 test, lerp); sputCostume_DrawMeshShadow's call); was
   Plane_IntersectSegment. */

int __cdecl
sputRender_SegmentPlaneIntersect(float *out,float *p1,float *p2,float a,float b,float c,float d)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  fVar1 = p2[1];
  fVar2 = p1[1];
  fVar3 = p2[2];
  fVar4 = p1[2];
  fVar5 = a * *p1 + c * p1[2] + b * p1[1] + d;
  fVar6 = fVar5 - (a * *p2 + c * p2[2] + b * p2[1] + d);
  fVar7 = fVar6;
  if (fVar6 < 0.0) {
    fVar7 = -fVar6;
  }
  if (fVar7 < 0.1) {
    return 0;
  }
  fVar5 = fVar5 / fVar6;
  *out = fVar5 * (*p2 - *p1) + *p1;
  out[1] = fVar5 * (fVar1 - fVar2) + p1[1];
  out[2] = fVar5 * (fVar3 - fVar4) + p1[2];
  return 1;
}
#undef local_4
#undef local_8

