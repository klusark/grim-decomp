/* Readable C for game-logic functions of GRIMFANDANGO.EXE (agent P, "less assembly in the game logic").
 *
 * Each function below replaces a function that used to be rebuilt from Ghidra's disassembly because its decompilation was
 * wrong (an x87 value that crossed a call to _ftol, register-passed values, a C++ frame, ...).  The C text was written
 * against the original instructions; docs/notes/logic.md has the checks that were made for each (differential tests,
 * picture comparisons).  tools/build_src.py puts the decompiled text of every function defined here under `#if 0`.
 * Names, types and offsets are Ghidra's.  Compiled with build/overrides.c into every program (guarded per program). */
#include "ghidra_types.h"

#ifdef GRIM_EXE
#include "globals.h"
#include "functions.h"

/* The MSVC conversion of `(int)(x + 0.5)` / `(int)(x - 0.5)` as the game's code does it: the operand is compared with
 * 0.0f, 0.5 is added when it is positive and subtracted when it is not (or unordered), then _ftol truncates it
 * (the low dword of a 64-bit FISTP, EAX).  Evaluated in long double like the original's x87 stack. */
static inline int round_half_away(long double x)
{
    return (int)(long long)(x > 0.0L ? x - (-0.5L) : x - 0.5L);
}

/* ==== rdColormap_BuildRGB16 (0x004047e0) ====
 * Builds the colour look-up tables of a 16 bit display from a 256 entry RGB palette: 64 light levels of 256 entries
 * each (512 bytes per level).  The first 8 palette entries are only shifted into the pixel format (the same value on
 * every level); the other 248 fade from the palette colour (level 63) towards the colour (r, g, b) (level 0) in 64
 * equal steps.  `fmt` holds the pixel format: left shifts of red / green / blue at +0x14 / +0x18 / +0x1c and the right
 * shifts that drop the unused low bits of an 8 bit channel at +0x20 / +0x24 / +0x28.  The decompiler lost the operands of
 * the three _ftol calls.  (All arithmetic is exact: multiples of 1/64 below 256.)  Returns 1. */
undefined8 __cdecl rdColormap_BuildRGB16(undefined2 *table, ushort *palette, uint r, uint g, uint b, int fmt)
{
    const int *f = (const int *)fmt;
    const byte *pal = (const byte *)palette;
    ushort *out = (ushort *)table;
    int i, level;

    for (i = 0; i < 8; i++) {
        uint pr = pal[0], pg = pal[1], pb = pal[2];
        ushort v = (ushort)(((pg >> (f[9] & 31)) << (f[6] & 31)) | ((pr >> (f[8] & 31)) << (f[5] & 31)) |
                            ((pb >> (f[10] & 31)) << (f[7] & 31)));
        for (level = 0; level < 64; level++)
            out[level * 256 + i] = v;
        pal += 3;
    }
    for (i = 8; i < 256; i++) {
        long double cr = pal[0], cg = pal[1], cb = pal[2];
        long double dr = ((long double)(float)(r & 0xff) - cr) * 0.015625f;
        long double dg = ((long double)(float)(g & 0xff) - cg) * 0.015625f;
        float db = (float)(((long double)(float)(b & 0xff) - cb) * 0.015625f);   /* the one step the code stores as a float */
        pal += 3;
        for (level = 63; level >= 0; level--) {
            int ir, ig, ib;
            cr += dr;
            cg += dg;
            cb += db;
            ir = round_half_away(cr);
            ig = round_half_away(cg);
            ib = round_half_away(cb);
            out[level * 256 + i] = (ushort)(((ig >> (f[9] & 31)) << (f[6] & 31)) | ((ib >> (f[10] & 31)) << (f[7] & 31)) |
                                            ((ir >> (f[8] & 31)) << (f[5] & 31)));
        }
    }
    return 1;
}

/* ==== rdroid_BuildMathTables (0x00404b80) ====
 * Reciprocal tables of the rasteriser: float 1/n for n = 1..2047 (entry 0 = FLT_MAX) at 0x008fe000, the same value as a
 * 16.16 fixed point integer (entry 0 = INT_MAX) at 0x008fbfc0, and the first 16 entries scaled by 65536 at 0x008fdfc0.
 * The decompiler lost the operand of _ftol (the extended precision 65536/n, truncated). */
void rdroid_BuildMathTables(void)
{
    float *recip = (float *)&g_dwRdRaster_aOneOverNFlex;
    int *fixed = (int *)&g_aRdRaster_OneOverNFixed;
    float *scaled = (float *)&UINT_008fdfc0;
    int n;

    recip[0] = *(float *)&(uint){0x7f7fc99e};
    fixed[0] = 0x7fffffff;
    for (n = 1; n < 2048; n++) {
        long double inv = 1.0L / (long double)n;
        recip[n] = (float)inv;
        fixed[n] = (int)(long long)(inv * 65536.0f);
    }
    for (n = 0; n < 16; n++)
        scaled[n] = recip[n] * *(float *)&DAT_004ddb30;
}

/* ==== rdCamera_BuildFOV (0x0040a280) ====
 * Computes the projection of an rdCamera from its canvas size and the frustum planes (the record the camera points to at
 * +0x48).  Camera fields: +0 projection type (0 orthographic, 1 perspective), +4 canvas, +0x38 field of view (degrees), +0x3c
 * perspective scale (output), +0x40 aspect ratio, +0x44 orthographic scale.  Canvas fields +0x18 / +0x1c / +0x20 / +0x24 are the
 * pixel rectangle.  Written by hand: Ghidra typed the camera record int[], so every float field came out as a float -> int
 * conversion of its bits.  Half sizes and the scale go through float variables where the code stores them (hh, hw, scale, the
 * sine), everything else is extended precision like the x87 code. */
undefined4 __cdecl rdCamera_BuildFOV(int *cam)
{
    char *c = (char *)cam;
    char *canvas = *(char **)(c + 4);
    float *pl;
    float hw, hh, aspect;
    int wRaw, hRaw;

    if (canvas == (char *)0)
        return 0;
    wRaw = *(int *)(canvas + 0x20) - *(int *)(canvas + 0x18);
    hRaw = *(int *)(canvas + 0x24) - *(int *)(canvas + 0x1c);
    aspect = *(float *)(c + 0x40);
    if (cam[0] == 0) {                                  /* orthographic */
        long double s = *(float *)(c + 0x44);

        pl = *(float **)(c + 0x48);
        hw = (float)((long double)wRaw * 0.5f);
        hh = (float)((long double)hRaw * 0.5f);
        pl[3] = (float)(-((long double)hw / s));
        pl[4] = (float)(((long double)hh / s) / aspect);
        pl[5] = (float)((long double)hw / s);
        pl[6] = (float)((-((long double)hh / s)) / aspect);
        *(undefined4 *)(c + 0x3c) = 0;
        pl[7] = 0.0f;
        pl[8] = 0.0f;
        pl[9] = 0.0f;
        pl[10] = 0.0f;
    } else if (cam[0] == 1) {                           /* perspective */
        float halfFov = *(float *)(c + 0x38) * 0.5f, sine, scale;

        pl = *(float **)(c + 0x48);
        hw = (float)((long double)wRaw * 0.5f);
        hh = (float)((long double)hRaw * 0.5f);
        sine = (float)stdMath_Tan(halfFov);
        scale = (float)((long double)hw / sine);
        *(float *)(c + 0x3c) = scale;
        pl[7] = (float)(((long double)hh / scale) / aspect);
        pl[9] = (float)(-(long double)hw / scale);
        pl[8] = (float)((-(long double)hh / scale) / aspect);
        pl[10] = (float)((long double)hw / scale);
        pl[11] = (float)((((long double)hh - (-1.0f)) / scale) / aspect);
        pl[12] = (float)((-((long double)hw - (-1.0f))) / scale);
    }
    return 1;
}

/* ==== rdPrimit3_ClipFace (0x0040deb0) ====
 * Gathers the vertices of one face into the clip work buffers and clips them against the frustum.  `src` (param_5) is the
 * face: +0 vertex count, +4 position index per vertex, +8 texture index per vertex, +0xc position pool (3 floats per entry),
 * +0x10 texture pool (2 floats), +0x14 intensity pool (1 float per position index), +0x18 extra intensity per vertex (or 0).
 * `dst` (param_6) receives: +0 the clipped vertex count, +0xc positions, +0x10 texture coordinates, +0x14 intensities.
 * `uvoff` (param_7) is added to every texture coordinate.  param_2 is the geometry mode, param_3 the lighting mode, param_4
 * is not used.  What is gathered and which clipper runs (the first one for a perspective camera, camera type 1, the second
 * for any other):
 *   geometry 0, or 3 with lighting 0..2   positions                        rdClip_Face3S / rdClip_Face3SOrtho
 *   geometry 1, 2                         positions                        rdClip_Face3W   / rdClip_Face3WOrtho
 *   geometry 3, lighting 3                positions, intensity             rdClip_Face3GS   / rdClip_Face3GSOrtho
 *   geometry 4, lighting 0..2             positions, uv                    rdClip_Face3T / rdClip_Face3TOrtho
 *   geometry 4, lighting 3                positions, uv, intensity         rdClip_Face3GT / rdClip_Face3GTOrtho
 *   anything else                         nothing (dst untouched)
 * The intensity is the pool value (plus the extra one when src+0x18 is set, summed in extended precision) clamped to 0..1.
 * Every clipper is cdecl, takes (frustum, positions, [uv,] [intensities,] count) and returns the new vertex count in EAX,
 * which is stored in dst+0.  Ghidra typed three of them (PosUvLit, PosUvLit_2, PosUvLitColor) as returning float; calling
 * them through that prototype reads the count from the empty x87 stack (0, so every lit face of a perspective view was
 * dropped, and the x87 stack was left one entry off).  They are therefore called through int-returning pointers here.
 * (The clipper names are Ghidra's guesses and do not match the attribute sets they get.) */
typedef uint (*rdClipFn3)(undefined4 frustum, float *pos, uint n);
typedef uint (*rdClipFn4)(undefined4 frustum, float *pos, float *attr, uint n);
typedef uint (*rdClipFn5)(undefined4 frustum, float *pos, float *uv, float *light, uint n);

static void clipface_copy_pos(const uint *src, uint *dst)
{
    uint i;
    for (i = 0; i < src[0]; i++) {
        const float *p = (const float *)src[3] + ((const int *)src[1])[i] * 3;
        float *o = (float *)dst[3] + i * 3;
        o[0] = p[0];
        o[1] = p[1];
        o[2] = p[2];
    }
}

static void clipface_copy_uv(const uint *src, uint *dst, const float *uvoff, uint i)
{
    const float *t = (const float *)src[4] + ((const int *)src[2])[i] * 2;
    float *o = (float *)dst[4] + i * 2;
    o[0] = t[0];
    o[1] = t[1];
    o[0] = uvoff[0] + o[0];
    o[1] = o[1] + uvoff[1];
}

static void clipface_light(const uint *src, uint *dst, uint i)
{
    float v = ((const float *)src[5])[((const int *)src[1])[i]];
    float *o = (float *)dst[5] + i;
    if (src[6] != 0) {
        long double s = (long double)v + ((const float *)src[6])[i];
        *o = !(s >= 0.0L) ? 0.0f : (s > 1.0L ? 1.0f : (float)s);   /* NaN -> 0, as the x87 compares do */
    } else {
        *o = !(v >= 0.0f) ? 0.0f : (v > 1.0f ? 1.0f : v);
    }
}

/* the camera type is read after the vertices are gathered, like the original does */
static int clipface_persp(void) { return *(int *)g_pRdCamera_CurCamera == 1; }

void rdPrimit3_ClipFace(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,
                       uint *param_5,undefined4 *param_6,float *param_7)
{
    uint *src = param_5;
    uint *dst = (uint *)param_6;
    uint i;

    (void)param_4;
    switch (param_2) {
    case 1:
    case 2:
        clipface_copy_pos(src, dst);
        dst[0] = (clipface_persp() ? (rdClipFn3)rdClip_Face3W : (rdClipFn3)rdClip_Face3WOrtho)(param_1, (float *)dst[3], src[0]);
        return;
    case 0:
        break;
    case 3:
        if (param_3 < 0 || param_3 > 3)
            return;
        if (param_3 == 3) {
            for (i = 0; i < src[0]; i++) {
                const float *p = (const float *)src[3] + ((const int *)src[1])[i] * 3;
                float *o = (float *)dst[3] + i * 3;
                o[0] = p[0];
                o[1] = p[1];
                o[2] = p[2];
                clipface_light(src, dst, i);
            }
            dst[0] = (clipface_persp() ? (rdClipFn4)rdClip_Face3GS : (rdClipFn4)rdClip_Face3GSOrtho)(
                param_1, (float *)dst[3], (float *)dst[5], src[0]);
            return;
        }
        break;
    case 4:
        if (param_3 < 0 || param_3 > 3)
            return;
        for (i = 0; i < src[0]; i++) {
            const float *p = (const float *)src[3] + ((const int *)src[1])[i] * 3;
            float *o = (float *)dst[3] + i * 3;
            o[0] = p[0];
            o[1] = p[1];
            o[2] = p[2];
            clipface_copy_uv(src, dst, param_7, i);
            if (param_3 == 3)
                clipface_light(src, dst, i);
        }
        if (param_3 == 3)
            dst[0] = (clipface_persp() ? (rdClipFn5)rdClip_Face3GT : (rdClipFn5)rdClip_Face3GTOrtho)(
                param_1, (float *)dst[3], (float *)dst[4], (float *)dst[5], src[0]);
        else
            dst[0] = (clipface_persp() ? (rdClipFn4)rdClip_Face3T : (rdClipFn4)rdClip_Face3TOrtho)(
                param_1, (float *)dst[3], (float *)dst[4], src[0]);
        return;
    default:
        return;
    }
    /* geometry 0, geometry 3 with lighting 0..2 */
    clipface_copy_pos(src, dst);
    dst[0] = (clipface_persp() ? (rdClipFn3)rdClip_Face3S : (rdClipFn3)rdClip_Face3SOrtho)(param_1, (float *)dst[3], src[0]);
}
/* ==== rdModel3_DrawFace (0x0040d880) ====
 * Allocates a draw cache entry for a mesh of a model, copies its geometry / lighting modes (capped by the global limits),
 * runs the vertices through the clipper or the plain copy (rdPrimit3_ClipFace / rdPrimit3_NoClipFace, 7 and 6 arguments),
 * clips the polygon against the extra plane, derives the lighting mode from the mesh alpha and the keyframe interpolation,
 * and queues it with rdCache_AddProcFace.  The compiler pushed the arguments of the two vertex routines before the branch that
 * selects one of them, so the decompiler printed the call of rdPrimit3_ClipFace with its first argument only (the C version
 * therefore crashed at start-up). */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 rdModel3_DrawFace(int param_1,int param_2)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  byte flags;
  int iVar2;
  uint uVar3;
  float *pfVar4;
  int iVar5;
  bool bVar6;
  float fVar7;
  #define local_24 (*(float *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(float (*)[2])(_frame + (0x40 - 0x20)))
  #define local_18 (*(float (*)[3])(_frame + (0x40 - 0x18)))
  #define local_c (*(float (*)[3])(_frame + (0x40 - 0xc)))
  
  iVar2 = rdCache_GetProcEntry();
  if (iVar2 == 0) {
    return 0;
  }
  uVar3 = *(uint *)(param_1 + 8);
  if ((int)g_dwGeometryMode < (int)*(uint *)(param_1 + 8)) {
    uVar3 = g_dwGeometryMode;
  }
  *(uint *)(iVar2 + 8) = uVar3;
  uVar3 = *(uint *)(param_1 + 0xc);
  if ((int)g_dwLightingMode < (int)*(uint *)(param_1 + 0xc)) {
    uVar3 = g_dwLightingMode;
  }
  *(uint *)(iVar2 + 0xc) = uVar3;
  uVar3 = *(uint *)(param_1 + 0x10);
  if ((int)g_dwTextureMode < (int)*(uint *)(param_1 + 0x10)) {
    uVar3 = g_dwTextureMode;
  }
  *(uint *)(iVar2 + 0x10) = uVar3;
  if ((*(byte *)(param_1 + 4) & 0x10) != 0) {
    *(undefined4 *)(iVar2 + 0xc) = 1;
  }
  UINT_007f1490 = *(uint *)(iVar2 + 0x20);
  UINT_007f1478 = *(uint *)(iVar2 + 0x24);
  UINT_007f147c = *(uint *)(iVar2 + 0x28);
  _g_aVertexSrc = *(undefined4 *)(param_1 + 0x14);
  _DAT_007f30ac = *(undefined4 *)(param_1 + 0x18);
  _DAT_007f30b0 = *(undefined4 *)(param_1 + 0x1c);
  if (g_dwMeshFrustrumCull == 0) {
    rdPrimit3_NoClipFace
              (*(undefined4 *)(iVar2 + 8),*(undefined4 *)(iVar2 + 0xc),*(undefined4 *)(iVar2 + 0x10)
               ,&g_aVertexSrc,&g_dwVertexDst,param_1 + 0x28);
  }
  else {
    rdPrimit3_ClipFace(*(undefined4 *)((int)g_pRdCamera_CurCamera + 0x48),*(undefined4 *)(iVar2 + 8),*(int *)(iVar2 + 0xc),
               *(undefined4 *)(iVar2 + 0x10),(uint *)&g_aVertexSrc,&g_dwVertexDst,(float *)(param_1 + 0x28));
  }
  if (g_dwVertexDst < 3) {
    return 0;
  }
  if (g_dwClipPlaneActive != 0) {
    rdMatrix_TransformVector34(local_c,(float *)&DAT_004ddb70,(float *)((int)g_pRdCamera_CurCamera + 8));
    rdMatrix_TransformPoint34(local_18,(float *)&DAT_007f3208,(float *)((int)g_pRdCamera_CurCamera + 8));
    uVar3 = rdClip_FaceToPlane(local_c,local_18,UINT_007f1474,UINT_007f1478,UINT_007f147c,
                                g_dwVertexDst);
    if ((int)uVar3 < 2) {
      return 0;
    }
    g_dwVertexDst = uVar3;
    *(uint *)(iVar2 + 0x1c) = uVar3;
  }
  if (*(int *)(iVar2 + 0xc) == 2) {
    if (param_2 == 0) {
      fVar7 = *(float *)((int)g_pRdCamera_CurCamera + 0x45c);
      iVar5 = *(int *)((int)g_pCurMesh + 0x30);
      pfVar4 = (float *)(param_1 + 0x40);
    }
    else {
      local_24 = -*(float *)(param_1 + 0x40);
      local_20[0] = -*(float *)(param_1 + 0x44);
      local_20[1] = -*(float *)(param_1 + 0x48);
      fVar7 = *(float *)((int)g_pRdCamera_CurCamera + 0x45c);
      iVar5 = *(int *)((int)g_pCurMesh + 0x30);
      pfVar4 = &local_24;
    }
    fVar7 = rdLight_CalcFaceIntensity
                      ((int *)&UINT_007f30e0,IMG_ADDR(0x007f1598),IMG_ADDR(0x007f1168),g_dwNumMeshLights,param_1,pfVar4,iVar5,
                       fVar7);
    *(float *)(iVar2 + 0x44) = fVar7;
  }
  (**(code **)((int)g_pRdCamera_CurCamera + 0x50))(UINT_007f1490,UINT_007f1474,g_dwVertexDst);
  if (((byte)g_dwRdroid_curRenderOptions & 2) == 0) {
    *(undefined4 *)(iVar2 + 0x40) = 0;
  }
  else {
    *(undefined4 *)(iVar2 + 0x40) = *(undefined4 *)((int)g_pRdCamera_CurCamera + 0x54);
  }
  iVar5 = *(int *)(param_1 + 0x24);
  if ((iVar5 == -1) && (*(int *)(param_1 + 0x20) != 0)) {
    iVar5 = *(int *)(*(int *)(param_1 + 0x20) + 100);
  }
  *(int *)(iVar2 + 0x3c) = iVar5;
  bVar6 = g_dwRdColormap_pIdentityMap != g_dwRdColormap_pCurMap;
  if (*(float *)(iVar2 + 0x40) < 1.0) {
    if (*(int *)(iVar2 + 0xc) == 2) {
      if ((*(float *)(iVar2 + 0x44) < 1.0) || (bVar6)) {
        if (*(float *)(iVar2 + 0x44) <= 0.0) {
          *(undefined4 *)(iVar2 + 0xc) = 1;
        }
      }
      else {
        *(undefined4 *)(iVar2 + 0xc) = 0;
      }
      goto LAB_0040dbd3;
    }
    if (*(int *)(iVar2 + 0xc) != 3) goto LAB_0040dbd3;
    pfVar4 = *(float **)(iVar2 + 0x28);
    fVar7 = *pfVar4;
    uVar3 = 1;
    if (1 < g_dwVertexDst) {
      do {
        pfVar4 = pfVar4 + 1;
        fVar1 = *pfVar4 - fVar7;
        if (fVar1 < 0.0) {
          fVar1 = -fVar1;
        }
      } while ((fVar1 <= 0.015625) && (uVar3 = uVar3 + 1, uVar3 < g_dwVertexDst));
    }
    if (uVar3 != g_dwVertexDst) goto LAB_0040dbd3;
    if (fVar7 != 1.0) {
      if (fVar7 == 0.0) {
        *(undefined4 *)(iVar2 + 0xc) = 1;
        *(undefined4 *)(iVar2 + 0x44) = 0;
      }
      else {
        *(undefined4 *)(iVar2 + 0xc) = 2;
        *(float *)(iVar2 + 0x44) = fVar7;
      }
      goto LAB_0040dbd3;
    }
    if (!bVar6) {
      *(undefined4 *)(iVar2 + 0xc) = 0;
      goto LAB_0040dbd3;
    }
  }
  else if (!bVar6) {
    *(undefined4 *)(iVar2 + 0xc) = 0;
    goto LAB_0040dbd3;
  }
  *(undefined4 *)(iVar2 + 0xc) = 2;
  *(undefined4 *)(iVar2 + 0x44) = 0x3f800000;
LAB_0040dbd3:
  flags = 1;
  if (3 < *(int *)(iVar2 + 8)) {
    flags = 3;
  }
  if (2 < *(int *)(iVar2 + 0xc)) {
    flags = flags | 4;
  }
  *(int *)(iVar2 + 0x50) = param_2;
  *(undefined4 *)(iVar2 + 4) = *(undefined4 *)(param_1 + 4);
  *(undefined4 *)(iVar2 + 0x48) = *(undefined4 *)(param_1 + 0x30);
  *(undefined4 *)(iVar2 + 0x38) = *(undefined4 *)(param_1 + 0x20);
  rdCache_AddProcFace((void *)0x0,g_dwVertexDst,flags);
  return 1;
}
#undef local_18
#undef local_20
#undef local_24
#undef local_c
/* ==== rdCache_DrawFaceZ (0x00408af0) ====
 * Draws one cache entry with the z-buffered rasteriser: the polygon mode and the lighting mode select the rdRaster_Draw_*
 * routine (flat or textured, lit or unlit, colour keyed, with or without the alpha pass).  Eleven of the calls were printed
 * without their arguments (find_lost_args: the compiler pushed (cache entry, polygon) once before a conditional jump): they
 * take the same two arguments as their neighbours, and rdRaster_Draw_TexLitZ_2 in the case 1 path a third, 0.0f. */
/* Software path with z-buffer */

int __cdecl rdCache_DrawFaceZ(void *mesh)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  float fVar2;
  float fVar3;
  void *pvVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  byte *pbVar10;
  float fVar11;
  #define local_4 (*(float *)(_frame + (0x20 - 0x4)))
  
  pvVar4 = mesh;
  iVar7 = *(int *)((int)mesh + 8);
  if (g_nRdroidGeometryMode <= *(int *)((int)mesh + 8)) {
    iVar7 = g_nRdroidGeometryMode;
  }
  iVar8 = *(int *)((int)mesh + 0xc);
  if (g_nRdroid_curLightingMode <= *(int *)((int)mesh + 0xc)) {
    iVar8 = g_nRdroid_curLightingMode;
  }
  mesh = *(void **)((int)mesh + 0x10);
  if (g_nRdroid_curTextureMode <= (int)mesh) {
    mesh = (void *)g_nRdroid_curTextureMode;
  }
  if (iVar7 == 0) {
    return 0;
  }
  iVar1 = *(int *)((int)pvVar4 + 0x38);
  if (iVar1 == 0) {
    pbVar10 = (byte *)0x0;
  }
  else {
    iVar5 = *(int *)((int)pvVar4 + 0x3c);
    if (iVar5 == -1) {
      iVar5 = *(int *)(iVar1 + 100);
      if (iVar5 < 0) {
LAB_00408b6e:
        iVar5 = 0;
      }
      else {
        iVar9 = *(int *)(iVar1 + 0x60) + -1;
        if (iVar9 < iVar5) {
          iVar5 = iVar9;
        }
      }
    }
    else {
      if (iVar5 < 0) goto LAB_00408b6e;
      iVar9 = *(int *)(iVar1 + 0x60) + -1;
      if (iVar9 < iVar5) {
        iVar5 = iVar9;
      }
    }
    pbVar10 = *(byte **)(iVar1 + 0x68 + iVar5 * 4);
    if ((iVar7 == 4) && ((*pbVar10 & 8) == 0)) {
      iVar7 = 3;
    }
  }
  if (((byte)g_dwRdroid_curRenderOptions & 2) == 0) {
    local_4 = 0.0;
  }
  else {
    local_4 = *(float *)((int)pvVar4 + 0x40);
  }
  switch(iVar7) {
  case 1:
    if ((-1 < iVar8) && (iVar8 < 5)) {
      rdRaster_DrawPointsZ(pvVar4,pbVar10);
      return 1;
    }
    break;
  case 2:
    if ((-1 < iVar8) && (iVar8 < 5)) {
      rdRaster_DrawWireframeZ(pvVar4,pbVar10);
      return 1;
    }
    break;
  case 3:
    switch(iVar8) {
    case 0:
      if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
        rdRaster_Draw_FlatLitZ(pvVar4,pbVar10);
        return 1;
      }
      rdRaster_Draw_TexLitZ(pvVar4,pbVar10);
      return 1;
    case 1:
      fVar11 = 0.0;
      *(undefined4 *)((int)pvVar4 + 0x44) = 0;
      if ((*(byte *)((int)pvVar4 + 4) & 2) != 0) {
        rdRaster_Draw_TexLitZ_2(pvVar4,pbVar10,fVar11);
        return 1;
      }
      break;
    case 2:
      fVar11 = *(float *)((int)pvVar4 + 0x48) + *(float *)((int)pvVar4 + 0x44);
      if (fVar11 < 0.0) {
        fVar2 = 0.0;
      }
      else {
        fVar2 = fVar11;
        if (1.0 < fVar11) {
          fVar2 = 1.0;
        }
      }
      if (local_4 < fVar2) {
        if (fVar11 < 0.0) {
          local_4 = 0.0;
        }
        else {
          local_4 = fVar11;
          if (1.0 < fVar11) {
            local_4 = 1.0;
          }
        }
      }
      fVar11 = local_4 * 63.0;
      *(float *)((int)pvVar4 + 0x44) = fVar11;
      if ((*(byte *)((int)pvVar4 + 4) & 2) != 0) {
        rdRaster_Draw_TexLitZ_2(pvVar4,pbVar10,fVar11);
        return 1;
      }
      break;
    case 3:
      uVar6 = 0;
      if (*(int *)((int)pvVar4 + 0x1c) != 0) {
        do {
          fVar11 = *(float *)(*(int *)((int)pvVar4 + 0x28) + uVar6 * 4) +
                   *(float *)((int)pvVar4 + 0x48);
          iVar7 = uVar6 * 4;
          if (fVar11 < 0.0) {
            fVar2 = 0.0;
          }
          else {
            fVar2 = fVar11;
            if (1.0 < fVar11) {
              fVar2 = 1.0;
            }
          }
          fVar3 = local_4;
          if (local_4 < fVar2) {
            if (fVar11 < 0.0) {
              fVar3 = 0.0;
            }
            else {
              fVar3 = fVar11;
              if (1.0 < fVar11) {
                fVar3 = 1.0;
              }
            }
          }
          uVar6 = uVar6 + 1;
          *(float *)(*(int *)((int)pvVar4 + 0x28) + iVar7) = fVar3 * 63.0;
        } while (uVar6 < *(uint *)((int)pvVar4 + 0x1c));
      }
      if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
        rdRaster_Draw_FlatLitZ_3(pvVar4,pbVar10);
        return 1;
      }
      rdRaster_Draw_TexLitZ_3(pvVar4,pbVar10);
      return 1;
    default:
      goto switchD_00408bad_default;
    }
    rdRaster_Draw_FlatLitZ_2(pvVar4,pbVar10,fVar11);
    return 1;
  case 4:
    if (mesh == (void *)0x0) {
      switch(iVar8) {
      case 0:
        if ((**(byte **)(pbVar10 + 0x1c) & 1) == 0) {
          if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
            rdRaster_Draw_FlatLit_7(pvVar4,pbVar10);
            return 1;
          }
          rdRaster_Draw_TexLitZ_4(pvVar4,pbVar10);
          return 1;
        }
        if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
          rdRaster_Draw_TexLitKeyZw(pvVar4,pbVar10);
          return 1;
        }
        rdRaster_Draw_TexLitKeyZw_2(pvVar4,pbVar10);
        return 1;
      case 1:
        if (*(float *)((int)pvVar4 + 0x48) < 0.0) {
          fVar11 = 0.0;
        }
        else if (1.0 < *(float *)((int)pvVar4 + 0x48)) {
          fVar11 = 1.0;
        }
        else {
          fVar11 = *(float *)((int)pvVar4 + 0x48);
        }
        if (local_4 < fVar11) {
          if (*(float *)((int)pvVar4 + 0x48) < 0.0) {
            local_4 = 0.0;
          }
          else if (1.0 < *(float *)((int)pvVar4 + 0x48)) {
            local_4 = 1.0;
          }
          else {
            local_4 = *(float *)((int)pvVar4 + 0x48);
          }
        }
        fVar11 = local_4 * 63.0;
        *(float *)((int)pvVar4 + 0x44) = fVar11;
        if ((**(byte **)(pbVar10 + 0x1c) & 1) == 0) {
          if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
            rdRaster_Draw_FlatLit_8(pvVar4,pbVar10,fVar11);
            return 1;
          }
          rdRaster_Draw_TexLitZ_5(pvVar4,pbVar10,fVar11);
          return 1;
        }
        if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
          rdRaster_Draw_TexLitKeyZw_3(pvVar4,pbVar10,fVar11);
          return 1;
        }
        rdRaster_Draw_TexLitKeyZw_4(pvVar4,pbVar10,fVar11);
        return 1;
      case 2:
        fVar11 = *(float *)((int)pvVar4 + 0x48) + *(float *)((int)pvVar4 + 0x44);
        if (fVar11 < 0.0) {
          fVar2 = 0.0;
        }
        else {
          fVar2 = fVar11;
          if (1.0 < fVar11) {
            fVar2 = 1.0;
          }
        }
        if (local_4 < fVar2) {
          if (fVar11 < 0.0) {
            local_4 = 0.0;
          }
          else {
            local_4 = fVar11;
            if (1.0 < fVar11) {
              local_4 = 1.0;
            }
          }
        }
        fVar11 = local_4 * 63.0;
        *(float *)((int)pvVar4 + 0x44) = fVar11;
        if ((**(byte **)(pbVar10 + 0x1c) & 1) == 0) {
          if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
            rdRaster_Draw_FlatLit_8(pvVar4,pbVar10,fVar11);
            return 1;
          }
          rdRaster_Draw_TexLitZ_5(pvVar4,pbVar10,fVar11);
          return 1;
        }
        if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
          rdRaster_Draw_TexLitKeyZw_3(pvVar4,pbVar10,fVar11);
          return 1;
        }
        rdRaster_Draw_TexLitKeyZw_4(pvVar4,pbVar10,fVar11);
        return 1;
      case 3:
        uVar6 = 0;
        if (*(int *)((int)pvVar4 + 0x1c) != 0) {
          do {
            fVar11 = *(float *)(*(int *)((int)pvVar4 + 0x28) + uVar6 * 4) +
                     *(float *)((int)pvVar4 + 0x48);
            iVar7 = uVar6 * 4;
            if (fVar11 < 0.0) {
              fVar2 = 0.0;
            }
            else {
              fVar2 = fVar11;
              if (1.0 < fVar11) {
                fVar2 = 1.0;
              }
            }
            fVar3 = local_4;
            if (local_4 < fVar2) {
              if (fVar11 < 0.0) {
                fVar3 = 0.0;
              }
              else {
                fVar3 = fVar11;
                if (1.0 < fVar11) {
                  fVar3 = 1.0;
                }
              }
            }
            uVar6 = uVar6 + 1;
            *(float *)(*(int *)((int)pvVar4 + 0x28) + iVar7) = fVar3 * 63.0;
          } while (uVar6 < *(uint *)((int)pvVar4 + 0x1c));
        }
        if ((**(byte **)(pbVar10 + 0x1c) & 1) != 0) {
          if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
            rdRaster_Draw_TexLitKeyZw_5(pvVar4,pbVar10);
            return 1;
          }
          rdRaster_Draw_TexLitKeyZw_6(pvVar4,pbVar10);
          return 1;
        }
        if ((*(byte *)((int)pvVar4 + 4) & 2) != 0) {
          rdRaster_Draw_TexLitZ_6(pvVar4,pbVar10);
          return 1;
        }
        rdRaster_Draw_FlatLit_9(pvVar4,pbVar10);
      }
    }
    else if (mesh == (void *)0x1) {
      switch(iVar8) {
      case 0:
        if ((**(byte **)(pbVar10 + 0x1c) & 1) == 0) {
          if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
            rdRaster_Draw_FlatLit_10(pvVar4,pbVar10);
            return 1;
          }
          rdRaster_Draw_TexLitZ_7(pvVar4,pbVar10);
          return 1;
        }
        if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
          rdRaster_Draw_TexLitKeyZw_7(pvVar4,pbVar10);
          return 1;
        }
        rdRaster_Draw_TexLitKeyZw_8(pvVar4,pbVar10);
        return 1;
      case 1:
        if (*(float *)((int)pvVar4 + 0x48) < 0.0) {
          fVar11 = 0.0;
        }
        else if (1.0 < *(float *)((int)pvVar4 + 0x48)) {
          fVar11 = 1.0;
        }
        else {
          fVar11 = *(float *)((int)pvVar4 + 0x48);
        }
        if (local_4 < fVar11) {
          if (*(float *)((int)pvVar4 + 0x48) < 0.0) {
            local_4 = 0.0;
          }
          else if (1.0 < *(float *)((int)pvVar4 + 0x48)) {
            local_4 = 1.0;
          }
          else {
            local_4 = *(float *)((int)pvVar4 + 0x48);
          }
        }
        fVar11 = local_4 * 63.0;
        *(float *)((int)pvVar4 + 0x44) = fVar11;
        if ((**(byte **)(pbVar10 + 0x1c) & 1) == 0) {
          if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
            rdRaster_Draw_FlatLit_11(pvVar4,pbVar10,fVar11);
            return 1;
          }
          rdRaster_Draw_TexLitZ_8(pvVar4,pbVar10,fVar11);
          return 1;
        }
        if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
          rdRaster_Draw_TexLitKeyZw_9(pvVar4,pbVar10,fVar11);
          return 1;
        }
        rdRaster_Draw_TexLitKeyZw_10(pvVar4,pbVar10,fVar11);
        return 1;
      case 2:
        fVar11 = *(float *)((int)pvVar4 + 0x48) + *(float *)((int)pvVar4 + 0x44);
        if (fVar11 < 0.0) {
          fVar2 = 0.0;
        }
        else {
          fVar2 = fVar11;
          if (1.0 < fVar11) {
            fVar2 = 1.0;
          }
        }
        if (local_4 < fVar2) {
          if (fVar11 < 0.0) {
            local_4 = 0.0;
          }
          else {
            local_4 = fVar11;
            if (1.0 < fVar11) {
              local_4 = 1.0;
            }
          }
        }
        fVar11 = local_4 * 63.0;
        *(float *)((int)pvVar4 + 0x44) = fVar11;
        if ((**(byte **)(pbVar10 + 0x1c) & 1) == 0) {
          if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
            rdRaster_Draw_FlatLit_11(pvVar4,pbVar10,fVar11);
            return 1;
          }
          rdRaster_Draw_TexLitZ_8(pvVar4,pbVar10,fVar11);
          return 1;
        }
        if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
          rdRaster_Draw_TexLitKeyZw_9(pvVar4,pbVar10,fVar11);
          return 1;
        }
        rdRaster_Draw_TexLitKeyZw_10(pvVar4,pbVar10,fVar11);
        return 1;
      case 3:
        uVar6 = 0;
        if (*(int *)((int)pvVar4 + 0x1c) != 0) {
          do {
            fVar11 = *(float *)(*(int *)((int)pvVar4 + 0x28) + uVar6 * 4) +
                     *(float *)((int)pvVar4 + 0x48);
            iVar7 = uVar6 * 4;
            if (fVar11 < 0.0) {
              fVar2 = 0.0;
            }
            else {
              fVar2 = fVar11;
              if (1.0 < fVar11) {
                fVar2 = 1.0;
              }
            }
            fVar3 = local_4;
            if (local_4 < fVar2) {
              if (fVar11 < 0.0) {
                fVar3 = 0.0;
              }
              else {
                fVar3 = fVar11;
                if (1.0 < fVar11) {
                  fVar3 = 1.0;
                }
              }
            }
            uVar6 = uVar6 + 1;
            *(float *)(*(int *)((int)pvVar4 + 0x28) + iVar7) = fVar3 * 63.0;
          } while (uVar6 < *(uint *)((int)pvVar4 + 0x1c));
        }
        if ((**(byte **)(pbVar10 + 0x1c) & 1) == 0) {
          if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
            rdRaster_Draw_FlatLit_12(pvVar4,pbVar10);
            return 1;
          }
          rdRaster_Draw_TexLitZ_9(pvVar4,pbVar10);
          return 1;
        }
        if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
          rdRaster_Draw_TexLitKeyZw_11(pvVar4,pbVar10);
          return 1;
        }
        rdRaster_Draw_TexLitKeyZw_12(pvVar4,pbVar10);
        return 1;
      }
    }
  }
switchD_00408bad_default:
  return 1;
}
#undef local_4
/* ==== rdModel3_Load (0x0040a980) ====
 * Opens the model file; the magic 'MODL' selects rdModel3_LoadEntryBinary, anything else is parsed by rdModel3_LoadEntryText.  The
 * magic was read into the parameter slot of the file name (the C text lost the name for the text loader); both close
 * calls take the file.  Source file Rdmodel3.c (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */
undefined4 rdModel3_Load(int name, undefined4 model)
{
    int file, ok;
    int magic;

    file = (*g_pRdroid_HS->pFopen)(name, &DAT_004ddb18);
    if (file == 0)
        return 0;
    (*g_pRdroid_HS->pFread)(file, &magic, 4);
    if (magic == 0x4d4f444c) {
        ok = rdModel3_LoadEntryBinary(file, model);
        (*g_pRdroid_HS->pFclose)(file);
        return ok != 0;
    }
    (*g_pRdroid_HS->pFclose)(file);
    return ((undefined4 (*)(int, undefined4))rdModel3_LoadEntryText)(name, model);
}
/* ==== rdPrimit3_DrawPolygon (0x00409d50) ====
 * Draws a world-space polygon with the 3D primitives: the vertices are moved into camera space (up to 32 on the stack), clipped
 * against the frustum with the position-only clipper, projected through the camera's function (+0x50) into a cache entry,
 * which gets the material and a back-face flag from the plane through the first three camera-space vertices (dot of its
 * normal with the centroid > 0).  The decompiler printed the stack arrays as separate locals that the C compiler does not lay
 * out one after the other (the vertex array ran over the neighbouring variables). */
void * __cdecl rdPrimit3_DrawPolygon(float *verts, int count, void *material)
{
    float cv[96], proj[96], cen[3], e1[3], e2[3], n[3], avg[3];
    char *cam = (char *)g_pRdCamera_CurCamera;
    uint *e;
    uint vc;
    int i;

    cen[0] = 0.0f;
    cen[1] = 0.0f;
    cen[2] = 0.0f;
    for (i = 0; i < count; i++) {
        float *out = cv + 3 * i;

        rdMatrix_TransformPoint34(out, verts + 3 * i, (float *)(cam + 8));
        cen[0] = cen[0] + out[0];
        cen[1] = out[1] + cen[1];
        cen[2] = out[2] + cen[2];
    }
    vc = rdClip_Face3S(*(undefined4 *)(cam + 0x48), cv, count);
    if ((int)vc < 3)
        return (void *)0;
    (**(code **)(cam + 0x50))(proj, cv, vc);
    e = (uint *)rdCache_GetProcEntry();
    e[0] = 0;
    e[0x11] = 0;
    e[0x12] = 0;
    e[0xf] = 0;
    e[1] = 1;
    e[3] = 1;
    e[2] = 3;
    e[7] = vc;
    memcpy((void *)e[8], proj, vc * 3 * sizeof(uint));
    e[0xf] = 0xffffffff;
    e[0xe] = (uint)material;
    e1[0] = cv[3] - cv[0];
    e1[1] = cv[4] - cv[1];
    e1[2] = cv[5] - cv[2];
    e2[0] = cv[6] - cv[3];
    e2[1] = cv[7] - cv[4];
    e2[2] = cv[8] - cv[5];
    Vec3_Cross(n, e1, e2);
    avg[0] = (float)((long double)cen[0] / count);
    avg[1] = (float)((long double)cen[1] / count);
    avg[2] = (float)((long double)cen[2] / count);
    e[0x14] = (((long double)n[0] * avg[0] + (long double)n[1] * avg[1]) + (long double)n[2] * avg[2]) > 0.0L ? 1 : 0;
    rdCache_AddProcFace((void *)0, vc, 1);
    return e;
}
/* ==== rdModel3_CalcRadii (0x0040c8c0) ====
 * Computes the bounding radius of every mesh of a model (the largest vertex distance from the origin, kept in a float
 * between vertices, then times 1.1) into +0x60 of the 0x7c byte mesh record, and the radius of the model through
 * rdModel3_BuildExpandedRadius.  The decompiler stored the float radius with a float -> int conversion (the C version
 * therefore gave integer radii).  Source file Rdmodel3.c (C:\grimjedi\Libs\RDroid\Primitives\Rdmodel3.c). */
static inline long double fsqrt_ld(long double x)
{
    __asm__("fsqrt" : "+t"(x));
    return x;
}

void rdModel3_CalcRadii(int model)
{
    uint i;
    char *rec = *(char **)(model + 0x28);

    for (i = 0; i < *(uint *)(model + 0x24); i++, rec += 0x7c) {
        float *v = *(float **)(rec + 0x30);
        uint n = *(uint *)(rec + 0x48);
        float mx = 0.0f;

        for (; n != 0; n--, v += 3) {
            long double d = fsqrt_ld(((long double)v[1] * v[1] + (long double)v[2] * v[2]) + (long double)v[0] * v[0]);

            if (d > (long double)mx)
                mx = (float)d;
        }
        *(float *)(rec + 0x60) = (float)((long double)mx * 0.1f + mx);
    }
    _g_dwMaxGeoRadius = 0;
    rdModel3_BuildExpandedRadius(model, *(undefined4 *)(model + 0x58), g_flRdroid_identMatrix34);
}
/* ==== rdModel3_CalcVertexNormals (0x0040cc30) ====
 * Averages the normals of the faces that share a vertex into the mesh's vertex normal array and normalises them.  For every
 * set (8 byte records at model+0x24, count at +0x44) and mesh (0x7c bytes; vertices +0x30, vertex count +0x48, normals +0x44,
 * faces +0x40 (0x4c bytes: index count +0x14, index array +0x18, face normal +0x40..), face count +0x50) the face normals
 * of the faces that list the vertex are summed (extended precision accumulators, as on the x87 stack; the y / z sums and the
 * count are rounded to float before the division, the x sum is not).  No face: (1, 0, 0); exactly one face: the normal is
 * built from the vertex 0 position and the neighbours (previous / next index of the first face) of the mesh - this is what the
 * code does, not a typo here; more: sum / count.  The decompiler typed the face counter and the accumulators float, which
 * made the converted loop count in the wrong type. */
void rdModel3_CalcVertexNormals(int model)
{
    uint *set = (uint *)(model + 0x24);
    uint s, m, v;

    for (s = 0; s < *(uint *)(model + 0x44); s++, set += 2) {
        char *mesh = (char *)set[1] + 0x30;

        for (m = 0; m < set[0]; m++, mesh += 0x7c) {
            float *nrm = *(float **)(mesh + 0x14);
            uint nverts = *(uint *)(mesh + 0x18);

            for (v = 0; v < nverts; v++, nrm += 3) {
                long double ax = 0.0f, ay = 0.0f, az = 0.0f, cnt = 0.0f;
                int nfaces = *(int *)(mesh + 0x20);
                float cnt_f, ay_f, az_f;

                if (nfaces != 0) {
                    char *face = *(char **)(mesh + 0x10);
                    int f;

                    for (f = nfaces; f != 0; f--, face += 0x4c) {
                        uint nidx = *(uint *)(face + 0x14);
                        uint *idx = *(uint **)(face + 0x18);
                        uint k;

                        for (k = 0; k < nidx; k++) {
                            if (idx[k] == v) {
                                ax += *(float *)(face + 0x40);
                                ay += *(float *)(face + 0x44);
                                az += *(float *)(face + 0x48);
                                cnt = cnt - (-1.0f);
                                break;
                            }
                        }
                    }
                }
                cnt_f = (float)cnt;
                ay_f = (float)ay;
                az_f = (float)az;
                if (cnt_f == 0.0f) {
                    nrm[0] = 1.0f;
                    nrm[1] = 0.0f;
                    nrm[2] = 0.0f;
                } else if (cnt_f == 1.0f) {
                    char *face0 = *(char **)(mesh + 0x10);
                    uint n = *(uint *)(face0 + 0x14);
                    int *idx = *(int **)(face0 + 0x18);
                    float *p = *(float **)mesh;
                    int prev = idx[n - 1];
                    int next = idx[1 % n];

                    nrm[1] = (float)(((long double)p[1] - p[next * 3 + 1]) + ((long double)p[1] - p[prev * 3 + 1]));
                    nrm[2] = (float)(((long double)p[2] - p[next * 3 + 2]) + ((long double)p[2] - p[prev * 3 + 2]));
                    nrm[0] = (float)(((long double)p[0] - p[prev * 3]) + ((long double)p[0] - p[next * 3]));
                    rdVector_Normalize3Acc(nrm);
                } else {
                    nrm[0] = (float)(ax / cnt_f);
                    nrm[1] = (float)((long double)ay_f / cnt_f);
                    nrm[2] = (float)((long double)az_f / cnt_f);
                    rdVector_Normalize3Acc(nrm);
                }
            }
        }
    }
}
/* ==== rdSprite_DrawThing (0x00472640) ====
 * Billboard: builds the camera-space matrix of the thing's sprite, transforms the sprite's centre points, and for every one
 * adds a camera-facing quad (side 2 * size, +0x34 of the sprite data) to the draw cache: the quad is clipped with the
 * position-only clipper, projected, and queued with the lighting mode (0 when the camera is fully opaque, 1 when it is fully
 * transparent, otherwise the sprite's own mode, capped by it) and the camera alpha.  Written by hand: Ghidra reused the
 * parameter slots for the lighting mode (int) and the alpha (float), so the C version mixed up bit copies and conversions. */
int __cdecl rdSprite_DrawThing(void *thing, void *sprite)
{
    char *t = (char *)thing;
    char *data = *(char **)(t + 4);
    char *cam = (char *)g_pRdCamera_CurCamera;
    float campos[3], mat[12];
    float alpha, size;
    int visible, mode;
    uint k, count;
    float *pt;

    rdMatrix_TransformPoint34(campos, (float *)((char *)sprite + 0x24), (float *)(cam + 8));
    if ((g_bRdroid_curCullFlags & 2) == 0)
        visible = *(int *)(t + 0x44);
    else
        visible = rdClip_SphereInFrustrum(*(undefined4 *)(cam + 0x48), campos, *(float *)(data + 0x3c));   /* (the radius's bits, not a conversion: grim_tools/cleanroom) */
    if (visible == 2)
        return 0;
    rdMatrix_Multiply34(mat, (float *)(cam + 8), sprite);
    alpha = ((byte)g_dwRdroid_curRenderOptions & 2) == 0 ? 0.0f : *(float *)(cam + 0x54);
    if (alpha < 1.0f)
        mode = (0.0f < alpha) ? *(int *)(data + 0x20) : 1;
    else
        mode = 0;
    if (*(int *)(data + 0x20) <= mode)
        mode = *(int *)(data + 0x20);
    count = *(uint *)(data + 0x24);
    rdMatrix_TransformPointLst34(mat, *(float **)(data + 0x28), (float *)&UINT_007f5180, count);
    size = *(float *)(data + 0x34);
    pt = (float *)&UINT_007f5180;
    for (k = 0; k < count; k++, pt += 3) {
        char *e = (char *)rdCache_GetProcEntry();
        float *q = (float *)&DAT_007f5000;
        uint vc;

        if (e == (char *)0)
            return 0;
        q[0] = pt[0] - size;  q[1] = pt[1];  q[2] = pt[2] - size;
        q[3] = pt[0] + size;  q[4] = pt[1];  q[5] = pt[2] - size;
        q[6] = pt[0] + size;  q[7] = pt[1];  q[8] = pt[2] + size;
        q[9] = pt[0] - size;  q[10] = pt[1]; q[11] = pt[2] + size;
        vc = rdClip_Face3S(*(undefined4 *)(cam + 0x48), q, 4);
        if (2 < vc) {
            (**(code **)(cam + 0x50))(*(undefined4 *)(e + 0x20), q, vc);
            *(int *)(e + 0xc) = mode;
            *(float *)(e + 0x40) = alpha;
            *(undefined4 *)(e + 8) = 3;
            *(undefined4 *)(e + 4) = 0;
            *(undefined4 *)(e + 0x38) = *(undefined4 *)(data + 0x38);
            *(undefined4 *)(e + 0x3c) = *(undefined4 *)(*(int *)(data + 0x2c) + k * 4);
            *(undefined4 *)(e + 0x50) = 0;
            rdCache_AddProcFace((void *)0, vc, 1);
        }
    }
    return 1;
}
/* ==== stdMath_SinCos (0x0047bd20), stdMath_Tan (0x0047c120) ====
 * Sine / cosine of an angle in degrees from a quarter-wave table of 4096 floats (0x004df600, cosine = the same table
 * read backwards; stdMath_Tan has its own table at 0x004e3600) with linear interpolation: `index = angle * 16384 / 360`
 * runs over four quadrants of 4096 entries.  The code reads the table through biased base addresses
 * (0x004db600 = table - 0x4000 bytes, ...) which the decompiler printed as string addresses; they are the plain
 * `table[i - 4096 * quadrant]`.  Two details of the original are kept: every intermediate that the code stores in a
 * float local is rounded to float (volatile here), the interpolation runs in extended precision.  Neither function
 * clamps the index, an angle that rounds to 360 reads one entry past the table. */
static inline float sincos_lerp(float v0, float v1, float frac)
{
    return (float)((((long double)v1 - v0) * frac) + v0);
}

void stdMath_SinCos(float deg, float *outSin, float *outCos)
{
    const float *T = (const float *)&g_aSinTable;
    volatile float a, t, frac;
    int q, i1, i2;
    float v0, v1;

    a = Math_NormalizeAngle360(deg);
    q = (a < 90.0f) ? 0 : (a < 180.0f) ? 1 : (a < 270.0f) ? 2 : 3;
    t = a * 45.511112f;
    frac = t - Math_Floor(t);
    i1 = (int)(long long)t;
    i2 = i1 + 1;
    switch (q) {
    case 0:
        v0 = T[i1];
        v1 = (i2 >= 0x1000) ? T[0xfff - (i2 - 0x1000)] : T[i2];
        *outSin = sincos_lerp(v0, v1, frac);
        v0 = T[0xfff - i1];
        v1 = (i2 >= 0x1000) ? -T[i2 - 0x1000] : T[0xfff - i2];
        *outCos = sincos_lerp(v0, v1, frac);
        break;
    case 1:
        v0 = T[0xfff - (i1 - 0x1000)];
        v1 = (i2 >= 0x2000) ? -T[i2 - 0x2000] : T[0xfff - (i2 - 0x1000)];
        *outSin = sincos_lerp(v0, v1, frac);
        v0 = -T[i1 - 0x1000];
        v1 = (i2 >= 0x2000) ? -T[0xfff - (i2 - 0x2000)] : -T[i2 - 0x1000];
        *outCos = sincos_lerp(v0, v1, frac);
        break;
    case 2:
        v0 = -T[i1 - 0x2000];
        v1 = (i2 >= 0x3000) ? -T[0xfff - (i2 - 0x3000)] : -T[i2 - 0x2000];
        *outSin = sincos_lerp(v0, v1, frac);
        v0 = -T[0xfff - (i1 - 0x2000)];
        v1 = (i2 >= 0x3000) ? T[i2 - 0x3000] : -T[0xfff - (i2 - 0x2000)];
        *outCos = sincos_lerp(v0, v1, frac);
        break;
    default:
        v0 = -T[0xfff - (i1 - 0x3000)];
        v1 = (i2 >= 0x4000) ? T[i2 - 0x4000] : -T[0xfff - (i2 - 0x3000)];
        *outSin = sincos_lerp(v0, v1, frac);
        v0 = T[i1 - 0x3000];
        v1 = (i2 >= 0x4000) ? T[0xfff - (i2 - 0x4000)] : T[i2 - 0x3000];
        *outCos = sincos_lerp(v0, v1, frac);
        break;
    }
}

float10 stdMath_Tan(float deg)
{
    const float *U = (const float *)&g_aTanTable;
    volatile float a, t, frac, r;
    int q, i1, i2;
    float v0, v1;

    a = Math_NormalizeAngle360(deg);
    q = (a < 90.0f) ? 0 : (a < 180.0f) ? 1 : (a < 270.0f) ? 2 : 3;
    t = (float)(((long double)a / 360.0f) * 16384.0f);
    frac = t - Math_Floor(t);
    i1 = (int)(long long)t;
    i2 = i1 + 1;
    switch (q) {
    case 0:
        v0 = U[i1];
        v1 = (i2 >= 0x1000) ? -U[0xfff - (i2 - 0x1000)] : U[i2];
        break;
    case 1:
        v0 = -U[0xfff - (i1 - 0x1000)];
        v1 = (i2 >= 0x2000) ? U[i2 - 0x2000] : -U[0xfff - (i2 - 0x1000)];
        break;
    case 2:
        v0 = U[i1 - 0x2000];
        v1 = (i2 >= 0x3000) ? -U[0xfff - (i2 - 0x3000)] : U[i2 - 0x2000];
        break;
    default:
        v0 = -U[0xfff - (i1 - 0x3000)];
        v1 = (i2 >= 0x4000) ? U[i2 - 0x4000] : -U[0xfff - (i2 - 0x3000)];
        break;
    }
    r = sincos_lerp(v0, v1, frac);
    return (float10)r;
}

/* ==== rdPrimit3_GetScreenCoord (0x0040dc30) ====
 * Lua WorldToScreen helper: moves the world point into camera space, rejects it when the view frustum does not contain it
 * and otherwise runs the camera's projection (function pointer at +0x4c) on it.  The screen position is stored as two
 * integers (x and y truncated by _ftol, the decompiler lost both operands) followed by the depth as a float. */
int rdPrimit3_GetScreenCoord(float *world, float *outScreen)
{
    char *cam = (char *)g_pRdCamera_CurCamera;
    float local[3], proj[3];

    rdMatrix_TransformPoint34(local, world, (float *)(cam + 8));
    if (rdClip_Point3(*(void **)(cam + 0x48), local) == 0)
        return 0;
    ((void (*)(float *, float *))*(code **)(cam + 0x4c))(proj, local);
    if (outScreen != (float *)0) {
        ((int *)outScreen)[0] = (int)(long long)proj[0];
        ((int *)outScreen)[1] = (int)(long long)proj[1];
        outScreen[2] = proj[2];
    }
    return 1;
}

/* ==== rdPrimit3_DrawPoint (0x0040dde0) ====
 * Draws a world-space point as a screen dot: projects the point and the point moved by `radius` along camera x (when it is
 * in front of the camera, y > 0), the on-screen distance of the two is the dot size, and rdCanvas_DrawPoint gets the
 * screen position (x + 0.5, y + 0.5 truncated) and the size.  The prototype in Ghidra lacked the two trailing arguments. */
void rdPrimit3_DrawPoint(float *world, float radius, uint a3, uint a4, uint a5)
{
    char *cam = (char *)g_pRdCamera_CurCamera;
    float p[3], q[3], s1[3], s2[3], size;
    int ix, iy;

    rdMatrix_TransformPoint34(p, world, (float *)(cam + 8));
    q[0] = p[0] + radius;
    q[1] = p[1];
    q[2] = p[2];
    if (p[1] > 0.0f) {
        ((void (*)(float *, float *))*(code **)(cam + 0x4c))(s1, p);
        ((void (*)(float *, float *))*(code **)(cam + 0x4c))(s2, q);
        size = s2[0] - s1[0];
        iy = (int)(long long)((long double)s1[1] - (-0.5L));        /* the code subtracts the double -0.5: round half up */
        ix = (int)(long long)((long double)s1[0] - (-0.5L));
        ((void (*)(void *, int, int, float, uint, uint, uint))rdCanvas_DrawPoint)(*(void **)(cam + 4), ix, iy, size, a3, a4, a5);
    }
}
/* msvcrt's pow, called the way the game's _CIpow does (overrides.c): the operands are rounded to double */
extern double (*msvcrt_pow)(double, double) __asm__("__imp__pow");   /* the import table slot of msvcrt's pow */
#define host_pow(x, y) ((*msvcrt_pow)((x), (y)))

/* ==== rdPrimit3_DrawLine (0x0040dcc0) ====
 * Draws a world-space line: moves both end points into camera space, clips the segment against the view frustum
 * (rdClip_Line3, which also reports which end was clipped), projects the end points and hands the integer screen
 * positions (truncated by _ftol) to rdCanvas_DrawLine.  The optional outA / outB receive x, y (integers) and the
 * depth (float bits) of the end points.  param_7 is a full dword in the original (the Ghidra prototype said ushort). */
undefined4 rdPrimit3_DrawLine(float *a, float *b, int *outA, int *outB, int *clipA, int *clipB, uint color, uint pattern)
{
    char *cam = (char *)g_pRdCamera_CurCamera;
    float v1[3], v2[3], s1[3], s2[3];
    int x1, y1, x2, y2;

    rdMatrix_TransformPoint34(v1, a, (float *)(cam + 8));
    rdMatrix_TransformPoint34(v2, b, (float *)(cam + 8));
    if (rdClip_Line3(*(void **)(cam + 0x48), v1, v2, clipA, clipB) == 0)
        return 0;
    ((void (*)(float *, float *))*(code **)(cam + 0x4c))(s1, v1);
    ((void (*)(float *, float *))*(code **)(cam + 0x4c))(s2, v2);
    x1 = (int)(long long)s1[0];
    y1 = (int)(long long)s1[1];
    if (outA != (int *)0) {
        outA[0] = x1;
        outA[1] = y1;
        outA[2] = ((int *)s1)[2];
    }
    x2 = (int)(long long)s2[0];
    y2 = (int)(long long)s2[1];
    if (outB != (int *)0) {
        outB[0] = x2;
        outB[1] = y2;
        outB[2] = ((int *)s2)[2];
    }
    ((void (*)(void *, int, int, int, int, uint, uint))rdCanvas_DrawLine)(*(void **)(cam + 4), x1, y1, x2, y2, color, pattern);
    return 1;
}

/* ==== Input_SetAxisRange (0x00477e70) ====
 * Sets up the range of a joystick axis (24 byte record at 0x00901500): flag, min, max, centre, dead zone (in axis
 * units, truncated by _ftol; 0 when the dead zone is 0.0 or NaN) and the reciprocal of the half range. */
void Input_SetAxisRange(int axis, int min, int max, float deadZone)
{
    uint *ax = (uint *)((char *)&UINT_00901500 + axis * 0x18);
    int mid = ((max - min) + 1) / 2 + min;

    ax[0] |= 1;
    ax[1] = min;
    ax[2] = max;
    ax[3] = mid;
    *(float *)&ax[5] = (float)(1.0L / (long double)(max - mid));
    if (deadZone > 0.0f || deadZone < 0.0f)
        ax[4] = (uint)(int)(long long)((long double)deadZone * (long double)(max - mid));
    else
        ax[4] = 0;
}

/* ==== Palette_FromFloatTable (0x0047b610) ====
 * Applies a gamma curve to `n` RGB byte triplets: out = min(255, pow(in / 255, gamma) * 255), truncated.  The Ghidra
 * prototype lacked the double argument (gamma, at +0x14 of the frame) and the operands of _ftol / _CIpow. */
void Palette_FromFloatTable(byte *out, byte *in, int n, double gamma)
{
    int i;

    for (i = 0; i < n * 3; i++) {
        double x = (double)in[i] * 0.00392156862745098;
        long double v = (long double)host_pow(x, gamma) * 255.0L;
        if (v > 255.0L)
            v = 255.0L;
        out[i] = (byte)(int)(long long)v;
    }
}

/* ==== stdColor_ColorConvertOneRow (0x0047b8a0), stdColor_ColorConvertOnePixel (0x0047bbb0) ====
 * Converts `count` pixels between the RGB layouts described by two format records (bits per pixel at +4, bits per channel
 * at +8 / +0xc / +0x10, left shifts at +0x14 / +0x18 / +0x1c, expansion shifts for 24 bit at +0x20 / +0x24 / +0x28).
 * 24 -> 16: each channel is scaled with a 16.16 factor dst_max / src_max and an ordered-dither offset from the 4x4 table
 * at 0x004d86a0 (rows by a counter that advances per call, columns by the pixel count), blue lands at bit 0; 16 -> 16:
 * the same scaling without dither; 16 -> 24: shifts the channels up to 8 bits.  The factors are computed on the x87 stack
 * (dst_max * (1 / src_max) * 65536, truncated); the decompiler lost them.  Any other combination does nothing. */
void stdColor_ColorConvertOneRow(ushort *dst, int dstFormat, ushort *src, int srcFormat, uint count)
{
    const int *d = (const int *)dstFormat;
    const int *s = (const int *)srcFormat;
    int scaleR, scaleG, scaleB;

    g_dwStdColor_ColorConvertOneRow_row = g_dwStdColor_ColorConvertOneRow_row + 1;
    {
        long double inv;
        inv = 1.0L / (long double)((1 << (s[2] & 31)) - 1);
        scaleR = (int)(long long)(((long double)((1 << (d[2] & 31)) - 1) * inv) * 65536.0L);
        inv = 1.0L / (long double)((1 << (s[3] & 31)) - 1);
        scaleG = (int)(long long)(((long double)((1 << (d[3] & 31)) - 1) * inv) * 65536.0L);
        inv = 1.0L / (long double)((1 << (s[4] & 31)) - 1);
        scaleB = (int)(long long)(((long double)((1 << (d[4] & 31)) - 1) * inv) * 65536.0L);
    }
    if (s[1] == 0x18 && d[1] == 0x10) {
        const byte *p = (const byte *)src;
        const int *dither = (const int *)&DAT_004d86a0 + (g_dwStdColor_ColorConvertOneRow_row & 3) * 4;
        do {
            int dv = dither[count & 3];
            *dst = (ushort)((((int)(p[0] * scaleR + dv) >> 16) << (d[5] & 31)) |
                            (((int)(p[1] * scaleG + dv) >> 16) << (d[6] & 31)) |
                            ((int)(p[2] * scaleB + dv) >> 16));
            p += 3;
            dst++;
        } while (--count != 0);
        return;
    }
    if (s[1] != 0x10)
        return;
    if (d[1] == 0x10) {
        uint mr = 0xffffffffu >> ((32 - s[2]) & 31), mg = 0xffffffffu >> ((32 - s[3]) & 31), mb = 0xffffffffu >> ((32 - s[4]) & 31);
        do {
            uint px = *src++;
            *dst++ = (ushort)(((int)(((px >> (s[5] & 31)) & mr) * scaleR) >> 16 << (d[5] & 31)) |
                              ((int)(((px >> (s[6] & 31)) & mg) * scaleG) >> 16 << (d[6] & 31)) |
                              ((int)((px & mb) * scaleB) >> 16));
        } while (--count != 0);
        return;
    }
    if (d[1] == 0x18) {
        uint mr = 0xffffffffu >> ((32 - s[2]) & 31), mg = 0xffffffffu >> ((32 - s[3]) & 31), mb = 0xffffffffu >> ((32 - s[4]) & 31);
        byte *o = (byte *)dst;
        do {
            uint px = *src++;
            o[0] = (byte)(((px >> (s[5] & 31)) & mr) << (s[8] & 31));
            o[1] = (byte)(((px >> (s[6] & 31)) & mg) << (s[9] & 31));
            o[2] = (byte)((px & mb) << (s[10] & 31));
            o += 3;
        } while (--count != 0);
    }
}

/* Converts one pixel: the converted value is written over the third argument (the format pointer passed in its slot), so
 * the bytes it does not set (the upper ones) are the upper bytes of that pointer. */
int stdColor_ColorConvertOnePixel(int dstFormat, undefined4 pixel, int srcFormat)
{
    uint in = pixel;
    uint out = srcFormat;
    stdColor_ColorConvertOneRow((ushort *)&out, dstFormat, (ushort *)&in, srcFormat, 1);
    return out;
}
/* ==== Palette_ApplyGamma (0x00474dd0) ====
 * Copies a 256 entry RGB palette, through the gamma curve number `gammaIdx` (a table of doubles, 8 bytes each, at
 * UINT_00803fc0 - 8) when one is selected.  Written by hand because Palette_FromFloatTable takes the gamma as a double
 * (two stack dwords): Ghidra's new prototype made the decompiler print the double built from one dword. */
int __cdecl Palette_ApplyGamma(void *dst, void *src, int count, int gammaIdx)
{
    if (UINT_00803fc0 == 0) {
        Mem_Copy(dst, src, 0x300);
        return 0;
    }
    if (gammaIdx != 0) {
        Palette_FromFloatTable((byte *)dst, (byte *)src, 0x100, *(double *)((char *)UINT_00803fc0 + gammaIdx * 8 - 8));
        return 1;
    }
    Mem_Copy(dst, src, 0x300);
    return 1;
}

/* ==== Render_BuildColorTable (0x004864a0) ====
 * Builds the 65536 entry colour remap table g_wSputRender_ColorLookup for a gamma value: every RGB565 value is split into its
 * channels, each channel is normalised (r, b / 31, g / 63), raised to `gamma` (msvcrt pow, rounded to float like the
 * stores of the original), scaled to the channel size of the display format `fmt` (bits at +8 / +0xc / +0x10, left shifts
 * at +0x14 / +0x18 / +0x1c) and truncated.  The decompiler lost the operands of _CIpow and _ftol. */
void Render_BuildColorTable(int fmt, float gamma)
{
    const int *f = (const int *)fmt;
    int i;

    for (i = 0; i < 0x10000; i++) {
        float fr = (float)((long double)((i >> 11) & 0x1f) / 31.0f);
        float fg = (float)((long double)((i >> 5) & 0x3f) / 63.0f);
        float fb = (float)((long double)(i & 0x1f) / 31.0f);

        fr = (float)host_pow((double)fr, (double)gamma);
        fg = (float)host_pow((double)fg, (double)gamma);
        fb = (float)host_pow((double)fb, (double)gamma);
        fr = (float)((long double)((1 << (f[2] & 31)) - 1) * fr);
        fg = (float)((long double)((1 << (f[3] & 31)) - 1) * fg);
        fb = (float)((long double)((1 << (f[4] & 31)) - 1) * fb);
        (&g_wSputRender_ColorLookup)[i] = (ushort)((((int)(long long)fr) << (f[5] & 31)) |
                                       (((int)(long long)fg) << (f[6] & 31)) |
                                       (((int)(long long)fb) << (f[7] & 31)));
    }
    g_flSputRender_GammaCorrection = gamma;
}

/* ==== sputRender_DimRegion (0x004870e0) ====
 * Scales the brightness of a rectangle of the 16 bit back buffer: every pixel is split into its channels with the
 * display's masks and shifts (UINT_00905608.. / 00905614..), each channel is multiplied by `scale` and truncated.
 * (The Ghidra prototype had three float arguments; the code only reads one, used for all channels.) */
void sputRender_DimRegion(int x, int y, int w, int h, float scale)
{
    const uint *fmt = (const uint *)&g_dwStdDisplay_backBuffer;   /* the back buffer record: bits per channel at +0x28.., shifts at +0x34.. */
    uint mr = 0xffffffffu >> ((32 - fmt[10]) & 31);
    uint mg = 0xffffffffu >> ((32 - fmt[11]) & 31);
    uint mb = 0xffffffffu >> ((32 - fmt[12]) & 31);
    ushort *row;
    int cy, cx;

    stdDisplay_VBufferLock(&g_dwStdDisplay_backBuffer);
    row = (ushort *)(UINT_0090563c + y * UINT_009055f8 + x * 2);
    for (cy = h; cy > 0; cy--) {
        ushort *p = row;
        for (cx = w; cx > 0; cx--) {
            uint px = *p;
            int r = (int)(long long)((long double)(int)((px >> (fmt[13] & 31)) & mr & 0xffff) * scale);
            int g = (int)(long long)((long double)(int)((px >> (fmt[14] & 31)) & mg & 0xffff) * scale);
            int b = (int)(long long)((long double)(int)((px >> (fmt[15] & 31)) & mb & 0xffff) * scale);
            *p++ = (ushort)((b << (fmt[15] & 31)) | (g << (fmt[14] & 31)) | (r << (fmt[13] & 31)));
        }
        row = (ushort *)((char *)row + UINT_009055f8);
    }
    stdDisplay_VBufferUnlock(&g_dwStdDisplay_backBuffer);
}

/* ==== Render_DrawProgressBar (0x004873d0) ====
 * Save / load progress bar on the primary surface: a yellow (0xffe0, remapped for the display) frame of 540 x 14 pixels at
 * (50, 455) whose inner 12 rows are filled for `fraction` (0..1) of the width.  The decompiler lost the operand of the
 * _ftol that turns fraction * 540 into the number of filled pixels. */
void Render_DrawProgressBar(float fraction)
{
    uint color = 0xffe0;
    int filled, rows, n;
    char *line;
    ushort *p;

    if (1.0f < fraction)
        fraction = 1.0f;
    filled = (int)(long long)((long double)fraction * 540.0f);
    sputRender_ColorCorrect((ushort *)&color, 1);
    stdDisplay_VBufferLock(&g_dwStdDisplay_frontBuffer);
    line = (char *)(UINT_00901698 * 0x1c7 + UINT_009016dc);
    p = (ushort *)(line + 100);
    for (n = 0x21c; n != 0; n--)
        *p++ = (ushort)color;
    for (rows = 12; rows != 0; rows--) {
        line += UINT_00901698 & 0xfffffffe;
        p = (ushort *)(line + 100);
        *(ushort *)(line + 0x49a) = 0xffe0;
        *p = 0xffe0;
        if (0x32 < filled + 0x32) {
            for (n = filled; n != 0; n--)
                *p++ = (ushort)color;
        }
    }
    p = (ushort *)(line + 100);
    for (n = 0x21c; n != 0; n--)
        *p++ = (ushort)color;
    stdDisplay_VBufferUnlock(&g_dwStdDisplay_frontBuffer);
}

/* ==== sputRender_DrawIrisEffect (0x00486d00) ====
 * Blacks out the 640 x 480 back buffer outside a rectangle around (x, y) that has closed by `percent` (0 = open):
 * (y * p) rows at the top, ((480 - y) * p) rows at the bottom, and in the rows between (x * p) pixels at the left and
 * ((640 - x) * p) at the right.  The decompiler lost the four _ftol operands.  The surface address and pitch are read
 * before the surface is locked, as in the original. */
void sputRender_DrawIrisEffect(float percent, int x, int y)
{
    int top, left, bottom, right, row;
    uint pitch, base;
    char *p;

    if (!(percent >= 0.0f) || percent > 1.0f) {
        (*g_pSputRendHS->pAssertFail)(s__percent____0_0f______percent____004e80ec, s_C__grimsrc_libs_grimlib_Engine_s_004e80bc, 0x9f2);
    }
    top = (int)(long long)((long double)y * percent);
    left = (int)(long long)((long double)x * percent);
    bottom = (int)(long long)((long double)(0x1e0 - y) * percent);
    right = (int)(long long)((long double)(0x280 - x) * percent);
    base = UINT_0090563c;
    pitch = UINT_009055f8;
    stdDisplay_VBufferLock(&g_dwStdDisplay_backBuffer);
    for (row = 0; row < top; row++)                   /* top rows: all black */
        memset((char *)base + (uint)row * pitch, 0, 0x500);
    if (row < 0)
        row = 0;
    if (row < 0x1e0 - bottom) {                       /* middle rows: left and right bands */
        for (; row < 0x1e0 - bottom; row++) {
            p = (char *)base + row * pitch;
            if (left > 0)
                memset(p, 0, (uint)left * 2);
            if (right > 0)
                memset(p + (0x280 - (uint)right) * 2, 0, (uint)right * 2);
        }
    }
    for (; row < 0x1e0; row++)                         /* bottom rows: all black */
        memset((char *)base + row * pitch, 0, 0x500);
    stdDisplay_VBufferUnlock(&g_dwStdDisplay_backBuffer);
}

/* ==== sputRender_ScreenShot (0x00486f90) ====
 * Renders a dimmed frame, then makes a new w x h surface and fills it with the background scaled down by point sampling:
 * the source column / row is the truncated running sum of 640 / w and 480 / h (the sums stay in extended precision on
 * the x87 stack, the steps are floats).  Returns the new surface (save game thumbnail). */
void *sputRender_ScreenShot(int w, int h)
{
    uint savedMode = g_dwGrimlib_mode;
    void *bg, *thumb;
    uint info[0x13];
    float stepX, stepY;
    long double yacc = 0.0f;
    int row, col;

    g_dwGrimlib_mode = 2;
    g_nSputRender_Reset = 1;
    ((void (*)(int, int))sputRender_Dim)(1, 0);
    bg = g_pSputRender_CleanBuffer;
    memcpy(info, (char *)bg + 0xc, 0x4c);
    info[0] = w;
    info[1] = h;
    g_dwGrimlib_mode = savedMode;
    thumb = stdDisplay_VBufferNew(info, 0, 0, 0);
    stepX = (float)(640.0f / (long double)w);
    stepY = (float)(480.0f / (long double)h);
    stdDisplay_VBufferLock(thumb);
    stdDisplay_VBufferLock(bg);
    for (row = 0; row < h; row++) {
        char *src = (char *)(*(int *)((char *)bg + 0x5c) + (int)(long long)yacc * *(int *)((char *)bg + 0x18));
        ushort *dst = (ushort *)(*(int *)((char *)thumb + 0x5c) + row * *(int *)((char *)thumb + 0x18));
        long double xacc = 0.0f;

        for (col = 0; col < w; col++) {
            *dst++ = *(ushort *)(src + (int)(long long)xacc * 2);
            xacc += stepX;
        }
        yacc += stepY;
    }
    stdDisplay_VBufferUnlock(thumb);
    stdDisplay_VBufferUnlock(bg);
    g_nSputRender_Reset = 1;
    return thumb;
}
/* ==== sputLua_DimRegion (0x004a1a00), sputLua_RestoreCacheRect (0x004a26b0) ====
 * Lua DimRegion(x, y, w, h, amount) scales the brightness of a screen rectangle (sputRender_DimRegion); the first four numbers
 * are truncated by _ftol, the decompiler lost their operands.  RestoreCacheRect(rect) takes a cache rect userdata (tag
 * word 0x11111111), reads its number (truncated, passed on to sputRender_RestoreCacheRect which ignores it). */
void sputLua_DimRegion(void)
{
    int a1 = lua_lua2C(1);
    int a2 = lua_lua2C(2);
    int a3 = lua_lua2C(3);
    int a4 = lua_lua2C(4);
    int a5 = lua_lua2C(5);
    int x, y, w, h;
    float amount;

    x = (int)(long long)lua_getnumber(a1);
    y = (int)(long long)lua_getnumber(a2);
    w = (int)(long long)lua_getnumber(a3);
    h = (int)(long long)lua_getnumber(a4);
    amount = lua_getnumber(a5);
    sputRender_DimRegion(x, y, w, h, amount);
}

void sputLua_RestoreCacheRect(void)
{
    int arg = lua_lua2C(1);
    int *rect = (int *)lua_getuserdata(arg);

    if (rect != (int *)0 && *rect == 0x11111111)
        ((void (*)(int))sputRender_RestoreCacheRect)((int)(long long)lua_getnumber(arg));
}

/* ==== SetSoundPosition (0x004a4e80) ====
 * Moves the volume and pan of one positioned sound (entry: +8..0x10 position, +0x14 min, +0x18 max, +0x1c scale,
 * +0x20 near distance).  d = position - camera position (current setup of the current set, set+0xac, stride 300),
 * normalised by rdVector_Normalize3QuickAcc (which returns the rough length).  With t = length - near >= 0 the volume is
 * (max - min) / scale * (scale - t) + min, truncated, clamped as UNSIGNED values to [min, max] (so a negative result comes
 * out as max); parameter 0x600.  The pan is (clamp(dot(camera right vector, d) * set+0x1b00, -1, 1) + 1) * 64, at most
 * 127; parameter 0x700.  The sums stay in extended precision.  The decompiler lost the operands of both _ftol. */
undefined4 SetSoundPosition(int entry)
{
    char *set = (char *)sputRoom_GetCurrentRoom();
    char *cam;
    float d[3];
    long double t, dot;

    if (set == (char *)0)
        return 0;
    cam = (char *)(*(int *)(set + 0xac) + *(int *)(set + 0xb4) * 300 + 0x20);
    d[0] = *(float *)(entry + 8) - *(float *)cam;
    d[1] = *(float *)(entry + 0xc) - *(float *)(cam + 4);
    d[2] = *(float *)(entry + 0x10) - *(float *)(cam + 8);
    t = (long double)rdVector_Normalize3QuickAcc(d) - *(float *)(entry + 0x20);
    if (t >= 0.0L) {
        uint max = *(uint *)(entry + 0x18), min = *(uint *)(entry + 0x14);
        float scale = *(float *)(entry + 0x1c);
        uint v = (uint)(int)(long long)((((long double)(unsigned long long)(uint)(max - min) / scale) * ((long double)scale - t)) +
                                        (long double)(int)min);
        if (v < min)
            v = min;
        else if (v > max)
            v = max;
        SoundsSetParam(*(int *)(entry + 4), 0x600, v);
    }
    dot = ((long double)*(float *)(cam + 0x30) * d[0] + (long double)*(float *)(cam + 0x34) * d[1]) +
          (long double)*(float *)(cam + 0x38) * d[2];
    dot = dot * *(float *)(set + 0x1b00);
    if (!(dot >= -1.0L))
        dot = -1.0L;
    else if (dot > 1.0L)
        dot = 1.0L;
    {
        uint pan = (uint)(int)(long long)((dot - (-1.0L)) * 64.0f);
        if (pan > 0x7f)
            pan = 0x7f;
        SoundsSetParam(*(int *)(entry + 4), 0x700, pan);
    }
    return 1;
}

/* ==== Smush_SetFile (0x004bdf00) ====
 * Opens the video file `id` through the file table (g_pSmushPlay_file_services), reads the header of its first frame, closes it again
 * and returns (short at +2 of the header) * 66.666664, truncated (the decompiler lost the operand of the _ftol). */
undefined * __cdecl Smush_SetFile(uint id)
{
    byte hdr[0x428];
    int h = (*(code *)*g_pSmushPlay_file_services)(id, &DAT_004dda54);

    if (h == 0)
        return (undefined *)0;
    smushplay_GetInfo(h, (int)hdr);
    (*(code *)g_pSmushPlay_file_services[1])(h);
    return (undefined *)(int)(long long)((long double)(int)*(short *)(hdr + 2) * 66.666664f);
}

/* ==== PerfEnd (0x00482e80) ====
 * Stops the stopwatch of profile slot 0..12: elapsed = (counter - start) / frequency * 1000 milliseconds, stored in the slot
 * record (48 bytes at 0x004e7b48: start at +0, result at +8) and returned truncated (the operand of _ftol was lost). */
undefined * __cdecl PerfEnd(int slot)
{
    long long freq, now;
    double freq_d;
    long double ms;
    char *rec;

    if (slot < 0 || 0xc < slot) {
        (*g_pSvcEngineModule->pAssertFail)(s_slot____1____slot___PerfTotalEnt_004e7f74, s_C__grimsrc_libs_grimlib_Main_spu_004e7f9c, 0x5b6);
    }
    QueryPerformanceFrequency((int)&freq);
    freq_d = (double)freq;
    QueryPerformanceCounter((int)&now);
    rec = (char *)&DAT_004e7b48 + slot * 0x30;
    ms = (((long double)now - *(double *)rec) / freq_d) * 1000.0;
    *(double *)(rec + 8) = (double)ms;
    return (undefined *)(int)(long long)ms;
}

/* ==== sputActor_UpdateActorSpeech (0x00490210) ====
 * Lip sync: while the actor speaks (talk flag +0x1dc, voice handle +0x1c8) the current phoneme is read from iMUSE and the
 * matching talk chore is completed; the text timer (+0x1cc) runs down by dt * 1000 (the decompiler lost the operand of
 * that _ftol) and ends the speech with the voice or when it expires. */
void __cdecl sputActor_UpdateActorSpeech(void *actor, float dt)
{
    char *talk = *(char **)((char *)actor + 0xa4);
    int phoneme;
    uint chore;
    int *node;

    if (*(int *)(talk + 0x1c4) == 0)
        return;
    if (*(char *)(talk + 0x1dc) != '\0' && *(int *)(talk + 0x1f0) != 0 && *(int *)((char *)actor + 0xa0) != 0) {
        phoneme = iMUSE_GetPhoneme(*(int *)(talk + 0x1c8), 0);
        if (phoneme == 0) {
            sputActor_ShutUp(actor);
        } else {
            chore = Phoneme_ToTalkChore(actor, phoneme);
            node = *(int **)((char *)actor + 0xa0);
            if (node != (int *)0) {
                int key = node[1];
                do {
                    if (node[1] != key || -1 < node[chore + 0xe])
                        break;
                    node = (int *)node[0x2c];
                } while (node != (int *)0);
                if (node != (int *)0 && node[1] == key)
                    Cos_InstCompleteChore(*node, node[chore + 0xe]);
            }
        }
    }
    talk = *(char **)((char *)actor + 0xa4);
    *(int *)(talk + 0x1cc) = *(int *)(talk + 0x1cc) + (int)(long long)((long double)dt * -1000.0f);
    if (*(char *)(*(int *)((char *)actor + 0xa4) + 0x1dc) == '\0' || Actor_IsVoicePlaying(actor) != 0) {
        if (*(char *)(*(int *)((char *)actor + 0xa4) + 0x1dc) != '\0')
            return;
        if (-1 < *(int *)(*(int *)((char *)actor + 0xa4) + 0x1cc))
            return;
    }
    sputActor_ShutUp(actor);
}

/* ==== rdCache_AddProcFace (0x00406860) ====
 * Appends a mesh to the draw cache (entries of 0x78 bytes at 0x008ddfc0, at most 1024) and computes its bounds from the
 * vertex array (entry +0x20, 12 bytes per vertex): x / y min and max (the indices of the lowest and highest y vertex go to
 * +0x6c / +0x70), z min / max (+0x64 / +0x68).  Meshes with an empty x or y extent are not added.  The integer screen box
 * (+0x54 left, +0x58 right, +0x5c top, +0x60 bottom) is the bounds rounded UP (FRNDINT with the round-up control word, then
 * _ftol; the decompiler printed neither), and widens the global draw box.  Returns 1 when the mesh was added. */
static inline int ceil_to_int(float x)
{
    if (x > -8388608.0f && x < 8388608.0f) {
        float t = (float)(int)x;
        x = (t < x) ? t + 1.0f : t;
    }
    return (int)(long long)x;
}

int rdCache_AddProcFace(void *mesh, uint vertexCount, byte flags)
{
    uint idx = g_dwRdCache_numProcFaces;
    char *e;
    float *v;
    float xlo, xhi, ylo, yhi, zlo, zhi;
    uint i;

    if (idx >= 0x400)
        return 0;
    e = (char *)&g_bRdCache_aProcFaces + idx * 0x78;
    v = *(float **)(e + 0x20);
    *(void **)e = mesh;
    *(uint *)(e + 0x1c) = vertexCount;
    *(uint *)(e + 0x74) = UINT_00900054;
    xlo = xhi = v[0];
    ylo = yhi = v[1];
    zlo = zhi = v[2];
    *(uint *)(e + 0x70) = 0;
    *(uint *)(e + 0x6c) = 0;
    for (i = 1; i < vertexCount; i++) {
        float x = v[3 * i], y = v[3 * i + 1], z = v[3 * i + 2];

        if (!(x >= xlo))
            xlo = x;
        else if (x > xhi)
            xhi = x;
        if (!(y >= ylo)) {
            ylo = y;
            *(uint *)(e + 0x6c) = i;
        } else if (y > yhi) {
            *(uint *)(e + 0x70) = i;
            yhi = y;
        }
        if (!(z >= zlo))
            zlo = z;
        else if (z > zhi)
            zhi = z;
    }
    *(float *)(e + 0x64) = zlo;
    *(float *)(e + 0x68) = zhi;
    if (xlo >= xhi)
        return 0;
    if (ylo >= yhi)
        return 0;
    *(int *)(e + 0x54) = ceil_to_int(xlo);
    *(int *)(e + 0x58) = ceil_to_int(xhi);
    *(int *)(e + 0x5c) = ceil_to_int(ylo);
    *(int *)(e + 0x60) = ceil_to_int(yhi);
    if (flags & 1)
        g_dwNumUsedVertices = g_dwNumUsedVertices + vertexCount;
    if (flags & 2)
        g_dwNumUsedTexVertices = g_dwNumUsedTexVertices + vertexCount;
    if (flags & 4)
        g_dwNumUsedIntensities = g_dwNumUsedIntensities + vertexCount;
    *(uint *)(e + 0x4c) = g_dwRdColormap_pIdentityMap;
    g_dwRdCache_numProcFaces = g_dwRdCache_numProcFaces + 1;
    if (*(uint *)(e + 0x54) < (uint)g_nDrawBoxMinX)
        g_nDrawBoxMinX = *(uint *)(e + 0x54);
    if ((uint)g_nDrawBoxMaxX < *(uint *)(e + 0x58))
        g_nDrawBoxMaxX = *(uint *)(e + 0x58);
    if (*(uint *)(e + 0x5c) < (uint)g_nDrawBoxMinY)
        g_nDrawBoxMinY = *(uint *)(e + 0x5c);
    if ((uint)g_nDrawBoxMaxY < *(uint *)(e + 0x60))
        g_nDrawBoxMaxY = *(uint *)(e + 0x60);
    return 1;
}

/* ==== sputPrimitive_ChangePrimitive (0x00489fe0) ====
 * ChangePrimitive(id, {color, layer, xoffset, yoffset, ..., width, height}): changes the properties of a screen primitive.
 * The numbers are truncated by _ftol (the decompiler lost the operand of every one); the colour (userdata with tag
 * 0x524c4f43) is converted to the display format channel by channel (bits dropped, shifted to the channel position).
 * The first attempt at a C version crashed in the colour packing (PIECE() on a stack slot). */

void sputPrimitive_ChangePrimitive(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  longlong lVar7;
  uint local_8;
  uint local_4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isnumber(iVar1);
  if (iVar3 == 0) {
    return;
  }
  iVar3 = lua_istable(iVar2);
  if (iVar3 != 0) {
    lVar7 = (longlong)lua_getnumber(iVar1);
    iVar1 = (int)lVar7;
    lua_pushobject(iVar2);
    lua_pushstring(PTR_s_color_004e8368);
    iVar3 = lua_gettable();
    iVar4 = lua_isuserdata(iVar3);
    if ((iVar4 != 0) && (iVar4 = lua_tag(iVar3), iVar4 == 0x524c4f43)) {
      uVar5 = lua_getuserdata(iVar3);
      /* the Lua colour is 0x00BBGGRR-style bytes; each channel loses its low bits and moves to the display's channel position */
      Primitive_SetColor(&g_dwPrimitiveQ,iVar1,
                         ((((uVar5 >> 16) & 0xff) >> (UINT_004ddac8 & 0x1f)) << (UINT_004ddabc & 0x1f) & 0xffff) |
                         ((((uVar5 >> 8) & 0xff) >> (UINT_004ddac4 & 0x1f)) << (UINT_004ddab8 & 0x1f) & 0xffff) |
                         (((uVar5 & 0xff) >> (UINT_004ddac0 & 0x1f)) << (UINT_004ddab4 & 0x1f) & 0xffff));
    }
    lua_pushobject(iVar2);
    lua_pushstring(PTR_s_layer_004e8390);
    iVar3 = lua_gettable();
    iVar4 = lua_isnumber(iVar3);
    if (iVar4 != 0) {
      lVar7 = (longlong)lua_getnumber(iVar3);
      Primitive_SetLayer(&g_dwPrimitiveQ,iVar1,(int)lVar7);
    }
    lua_pushobject(iVar2);
    lua_pushstring(PTR_s_xoffset_004e836c);
    iVar3 = lua_gettable();
    lua_pushobject(iVar2);
    lua_pushstring(PTR_s_yoffset_004e8370);
    iVar4 = lua_gettable();
    iVar6 = lua_isnumber(iVar3);
    if ((iVar6 != 0) || (iVar6 = lua_isnumber(iVar4), iVar6 != 0)) {
      local_8 = 0;
      iVar6 = lua_isnumber(iVar3);
      if (iVar6 != 0) {
        lVar7 = (longlong)lua_getnumber(iVar3);
        local_8 = (uint)lVar7;
      }
      iVar3 = lua_isnumber(iVar4);
      if (iVar3 == 0) {
        iVar3 = 0;
      }
      else {
        lVar7 = (longlong)lua_getnumber(iVar4);
        iVar3 = (int)lVar7;
      }
      Primitive_Offset(&g_dwPrimitiveQ,iVar1,local_8,iVar3);
    }
    lua_pushobject(iVar2);
    lua_pushstring(PTR_DAT_004e8374);
    iVar3 = lua_gettable();
    lua_pushobject(iVar2);
    lua_pushstring(PTR_DAT_004e8378);
    iVar4 = lua_gettable();
    iVar6 = lua_isnumber(iVar3);
    if ((iVar6 != 0) || (iVar6 = lua_isnumber(iVar4), iVar6 != 0)) {
      local_8 = 0xffffffff;
      iVar6 = lua_isnumber(iVar3);
      if (iVar6 != 0) {
        lVar7 = (longlong)lua_getnumber(iVar3);
        local_8 = (uint)lVar7;
      }
      iVar3 = lua_isnumber(iVar4);
      if (iVar3 == 0) {
        iVar3 = -1;
      }
      else {
        lVar7 = (longlong)lua_getnumber(iVar4);
        iVar3 = (int)lVar7;
      }
      Primitive_MoveTo(&g_dwPrimitiveQ,iVar1,local_8,iVar3);
    }
    lua_pushobject(iVar2);
    lua_pushstring(PTR_DAT_004e837c);
    iVar3 = lua_gettable();
    lua_pushobject(iVar2);
    lua_pushstring(PTR_DAT_004e8380);
    iVar4 = lua_gettable();
    iVar6 = lua_isnumber(iVar3);
    if ((iVar6 != 0) || (iVar6 = lua_isnumber(iVar4), iVar6 != 0)) {
      local_8 = 0xffffffff;
      iVar6 = lua_isnumber(iVar3);
      if (iVar6 != 0) {
        lVar7 = (longlong)lua_getnumber(iVar3);
        local_8 = (uint)lVar7;
      }
      iVar3 = lua_isnumber(iVar4);
      if (iVar3 == 0) {
        iVar3 = -1;
      }
      else {
        lVar7 = (longlong)lua_getnumber(iVar4);
        iVar3 = (int)lVar7;
      }
      Primitive_SetEnd(&g_dwPrimitiveQ,iVar1,local_8,iVar3);
    }
    lua_pushobject(iVar2);
    lua_pushstring(PTR_s_width_004e8384);
    iVar3 = lua_gettable();
    lua_pushobject(iVar2);
    lua_pushstring(PTR_s_height_004e8388);
    iVar2 = lua_gettable();
    iVar4 = lua_isnumber(iVar3);
    if ((iVar4 == 0) && (iVar4 = lua_isnumber(iVar2), iVar4 == 0)) {
      return;
    }
    iVar6 = -1;
    iVar4 = lua_isnumber(iVar3);
    if (iVar4 == 0) {
      iVar3 = -1;
    }
    else {
      lVar7 = (longlong)lua_getnumber(iVar3);
      iVar3 = (int)lVar7;
    }
    iVar4 = lua_isnumber(iVar2);
    if (iVar4 != 0) {
      lVar7 = (longlong)lua_getnumber(iVar2);
      iVar6 = (int)lVar7;
    }
    Primitive_SetSize(&g_dwPrimitiveQ,iVar1,iVar3,iVar6);
    return;
  }
  return;
}

/* ==== Services_SetCurrent (0x004733a0) ====
 * Stores the module service table and captures the x87 control word the game runs with: the other three words used by the
 * rounding helpers keep its low byte and replace the high byte (rounding control): 0x0b = round up (0x0090052a), 0x07 =
 * round down (0x00900526), 0x0c = truncate (0x00900528).  The decompiler printed FNSTCW as a read of an undefined register. */
void __cdecl Services_SetCurrent(GrimServices *svc)
{
    ushort cw;

    g_pStd_HS = svc;
    if (Plat_ReturnTrue() == 0)
        return;
    __asm__ volatile("fnstcw %0" : "=m"(cw));
    DAT_00900524 = cw;
    DAT_0090052a = (ushort)((cw & 0xff) | 0x0b00);
    DAT_00900526 = (ushort)((cw & 0xff) | 0x0700);
    DAT_00900528 = (ushort)((cw & 0xff) | 0x0c00);
    _DAT_007f6490 = 1;
}

/* ==== sputCostume_Update (0x00495730) ====
 * Per frame: the frame time in seconds is rounded to whole milliseconds (round half away from zero, as the code does it
 * with +-0.5 and _ftol), every costume of the list gets Cos_InstUpdateChores(cos, ms) and every puppet of the second list
 * advances by ms * 0.001 seconds.  The decompiler lost the operand of the _ftol and the double bias constants. */
void __cdecl sputCostume_Update(void *costumeList, float dt)
{
    uint ms = (uint)round_half_away((long double)dt * 1000.0f);
    float seconds = (float)((long double)(unsigned long long)ms * 0.001f);
    int *node;
    int key, item;

    if (costumeList == (void *)0)
        return;
    node = (int *)costumeList;
    key = node[1];
    do {
        if (node[1] != key)
            break;
        Cos_InstUpdateChores(*node, ms);
        node = (int *)node[0x2c];
    } while (node != (int *)0);
    for (item = *(int *)((int)costumeList + 8); item != 0; item = *(int *)(item + 400)) {
        void *puppet = *(void **)(*(int *)(item + 0x40) + 0x14);
        if (puppet != (void *)0)
            rdPuppet_UpdateTracks(puppet, seconds);
    }
}

/* ==== SpriteAdjuster (0x004986e0) ====
 * Costume editor dialog for a sprite key ("Width", "Height" and three more fields).  The values shown are the sprite's
 * floats times 100 (+ 0.2, truncated: the decompiler lost the five _ftol operands); on OK they are stored back as
 * value * 0.01 (plus the half sizes) and the key's text "name w h ..." is rewritten. */
undefined4 SpriteAdjuster(undefined4 *param_1, undefined4 param_2)
{
    char *labels[5];
    int vals[5];
    char text[32];
    char *key = *(char **)*param_1;    /* the sprite data: the component's first field */
    int tok;

    labels[0] = s_Width_004ea87c;
    labels[1] = s_Height_004ea874;
    labels[2] = (char *)&DAT_004ea870;
    labels[3] = (char *)&DAT_004ea86c;
    labels[4] = (char *)&DAT_004ea868;
    vals[0] = (int)(long long)((long double)*(float *)(key + 0x4c) * 100.0f - (-0.2f));
    vals[1] = (int)(long long)((long double)*(float *)(key + 0x50) * 100.0f - (-0.2f));
    vals[2] = (int)(long long)((long double)*(float *)(key + 0xac) * 100.0f - (-0.2f));
    vals[3] = (int)(long long)((long double)*(float *)(key + 0xb0) * 100.0f - (-0.2f));
    vals[4] = (int)(long long)((long double)*(float *)(key + 0xb4) * 100.0f - (-0.2f));
    if (grimPlat_SpinDialog(param_2, (int)labels, (undefined4 *)vals, 5) == 0)
        return 0;
    *(float *)(key + 0x4c) = (float)vals[0] * 0.01f;
    *(float *)(key + 0x50) = (float)vals[1] * 0.01f;
    *(float *)(key + 0x54) = *(float *)(key + 0x4c) * 0.5f;
    *(float *)(key + 0x58) = *(float *)(key + 0x50) * 0.5f;
    *(float *)(key + 0xac) = (float)vals[2] * 0.01f;
    *(float *)(key + 0xb0) = (float)vals[3] * 0.01f;
    *(float *)(key + 0xb4) = (float)vals[4] * 0.01f;
    tok = strtok(param_2, &DAT_004ea52c);
    sprintf(text, s__s__d__d__d__d__d_004ea854, tok, vals[0], vals[1], vals[2], vals[3], vals[4]);
    strncpy(tok, text, 0x1f);
    *(undefined1 *)(tok + 0x1f) = 0;
    return 1;
}

/* ==== Actor_DrawShadowPlane (0x00494940) ====
 * Draws the actor's shadow onto one shadow plane: for every mesh of every model of the costume list the 16 corner points of
 * the bounding boxes are projected through the plane (Plane_IntersectSegment along the shadow direction; a miss ends the
 * whole function) and the four boxes' faces are clipped to the plane's sectors and drawn with shadow.mat / shadow.cmp
 * (Shadow_DrawClippedPoly accumulates the screen box in min / max).  Afterwards the touched screen rectangle
 * (x, y, w, h = truncated min and max - min) is invalidated.  The decompiler lost the operands of the four _ftol.
 * Like the original, max.y is never initialised before the first polygon. */
void Actor_DrawShadowPlane(void *costumeList, void *shadow)
{
    float pts[48];
    float minXY[2], maxXY[3];
    int rect[4];
    int item;

    if (costumeList == (void *)0)
        return;
    item = *(int *)((int)costumeList + 8);
    minXY[0] = 640.0f;
    minXY[1] = 480.0f;
    maxXY[0] = 0.0f;
    maxXY[2] = 0.0f;
    for (; item != 0; item = *(int *)(item + 400)) {
        int model = *(int *)(item + 0x40);
        int geom = *(int *)(model + 4);
        int meshIdx, pointOff, hdrOff;

        if (*(int *)(item + 0x38) == 0 || *(int *)(item + 0x34) != 0 || *(int *)(geom + 0x54) <= 0)
            continue;
        pointOff = 0;
        hdrOff = 0;
        for (meshIdx = 0; meshIdx < *(int *)(geom + 0x54); meshIdx++, hdrOff += 0xb8, pointOff += 0x30) {
            int node = *(int *)(hdrOff + 0x4c + *(int *)(geom + 0x58));
            int rec, k;

            if (node == -1)
                continue;
            rec = *(int *)(geom + 0x28);
            if (*(int *)(rec + 0x54 + node * 0x7c) == 0)
                continue;
            if (*(int *)(*(int *)(model + 0x2c) + node * 4) == 0)
                continue;
            for (k = 0; k < 0xc0; k += 0xc) {
                float *out = (float *)((char *)pts + k);
                rdMatrix_TransformPoint34(out, (float *)(k + *(int *)(rec + node * 0x7c + 0x58)), (float *)(pointOff + *(int *)(model + 0x20)));
                if (Plane_IntersectSegment(out, (float *)((char *)shadow + 0x18), out, *(float *)((char *)shadow + 8),
                                           *(float *)((char *)shadow + 0xc), *(float *)((char *)shadow + 0x10),
                                           *(float *)((char *)shadow + 0x14)) == 0)
                    return;
            }
            if (g_pShadowMaterial == (void *)0)
                g_pShadowMaterial = rdMaterial_Load(s_shadow_mat_004ea19c, 0, 0);
            if (g_pShadowColormap == (void *)0)
                g_pShadowColormap = rdColormap_Load(s_shadow_cmp_004ea190);
            if (g_pShadowMaterial != (void *)0) {
                rdroid_SetColormap((uint)g_pShadowColormap);
                if (g_nSputRender_b3DAcceleration != 0)
                    std3D_SetCurrentPalette((void *)((int)g_pShadowColormap + 0x30), 0);
                Shadow_DrawClippedPoly(pts, 4, minXY, maxXY, shadow);
                Shadow_DrawClippedPoly(pts + 12, 4, minXY, maxXY, shadow);
                Shadow_DrawClippedPoly(pts + 24, 4, minXY, maxXY, shadow);
                Shadow_DrawClippedPoly(pts + 36, 4, minXY, maxXY, shadow);
            }
        }
    }
    if (minXY[0] <= maxXY[0]) {
        rect[0] = (int)(long long)minXY[0];
        rect[1] = (int)(long long)minXY[1];
        rect[2] = (int)(long long)((long double)maxXY[0] - minXY[0]);
        rect[3] = (int)(long long)((long double)maxXY[1] - minXY[1]);
        Render_InvalidateRectLastBuffer(rect, 1);
    }
}
/* ==== ShrinkBoxes (0x004a9d00) ====
 * ShrinkBoxes(radius), called by Lua ShrinkBoxes after SectorList_SaveForShrink.  For every active walk
 * sector (type & 0x1000, flag +0x28) each vertex is moved inward along the bisector of its two edges by radius / sin(a),
 * a = 90 - asin(bisector . next edge) degrees.  The move is valid when the new point is inside the sector
 * (Sector_ContainsPoint) and at least radius - 0.001 from the line of every edge (Sector_EdgeDistance); when it is not,
 * Sector_CollapseShortestEdge is tried and the sector is processed again, and when nothing can be collapsed the sector is
 * switched off (+0x28 = 0).  The shifts are summed per pool vertex (the pool at 0x008cb0b0 has 16 byte records, the
 * vertices of the sectors share them) and every pool vertex moves by the mean of its shifts, so all sectors that share it
 * move together.  Undone by SectorList_RestoreAfterShrink.
 * Rewritten from the instructions: the Ghidra prototype had 14 parameters because the decompiler took the 16 KB frame of
 * the function (shift sums, counts, a table of 10 shifts) for stack arguments.  The new point uses the extended precision
 * scale for x and the scale rounded to float for y and z, as the x87 code does. */
void __cdecl ShrinkBoxes(float radius)
{
    float acc[1024 * 3];
    int cnt[1024];
    float shift[10][3];
    char *pool = (char *)&UINT_008cb0b8 - 8;
    char *s;
    int idx;

    if (!(radius >= 0.0f))
        return;
    memset(acc, 0, sizeof(acc));
    memset(cnt, 0, sizeof(cnt));
    for (s = (char *)g_pWalkPlane_wp_head; s != (char *)0; s = *(char **)(s + 0x70)) {
        if ((*(uint *)(s + 0x24) & 0x1000) == 0 || *(int *)(s + 0x28) == 0)
            continue;
        for (;;) {
            int n = *(int *)(s + 0x34);
            float *prev, *cur;
            int i, valid = 1, k;

            memset(shift, 0, sizeof(shift));
            cur = (float *)(*(char **)(s + 0x38) + 4);
            prev = (float *)(*(char **)(s + 0x34 + n * 4) + 4);
            for (i = 0; i < n; i++) {
                float *next = (float *)(*(char **)(s + 0x38 + ((i + 1) % n) * 4) + 4);
                float A[3], B[3], P[3], sinv, cosv, ang, d, sc;
                long double sc_ext;
                int ok;

                A[0] = prev[0] - cur[0];
                A[1] = prev[1] - cur[1];
                A[2] = prev[2] - cur[2];
                rdVector_Normalize3Acc(A);
                B[0] = next[0] - cur[0];
                B[1] = next[1] - cur[1];
                B[2] = next[2] - cur[2];
                rdVector_Normalize3Acc(B);
                A[0] = B[0] + A[0];
                A[1] = B[1] + A[1];
                A[2] = B[2] + A[2];
                rdVector_Normalize3Acc(A);
                d = (float)(((long double)B[0] * A[0] + (long double)B[1] * A[1]) + (long double)B[2] * A[2]);
                ang = (float)(90.0L - (long double)stdMath_ArcSin3(d));
                stdMath_SinCos(ang, &sinv, &cosv);
                sc_ext = (long double)radius / sinv;
                sc = (float)sc_ext;
                P[0] = (float)(sc_ext * A[0] + cur[0]);
                P[1] = (float)((long double)sc * A[1] + cur[1]);
                P[2] = (float)((long double)sc * A[2] + cur[2]);
                ok = Sector_ContainsPoint(s, P, 1) != 0;
                if (ok) {
                    double thr = (double)((long double)radius - (long double)0.001);
                    for (k = 0; k < *(int *)(s + 0x34); k++) {
                        if (!((long double)Sector_EdgeDistance(s, k, P) >= (long double)thr)) {
                            ok = 0;
                            break;
                        }
                    }
                }
                if (!ok) {
                    valid = 0;
                    break;
                }
                shift[i][0] = (float)((long double)sc * A[0]);
                shift[i][1] = (float)((long double)sc * A[1]);
                shift[i][2] = (float)((long double)sc * A[2]);
                prev = cur;
                cur = next;
            }
            if (!valid) {
                if (Sector_CollapseShortestEdge(s) != 0)
                    continue;                   /* an edge was collapsed: shift the smaller sector again */
                *(int *)(s + 0x28) = 0;         /* nothing to collapse: the sector is switched off */
                break;
            }
            n = *(int *)(s + 0x34);
            for (k = 0; k < n; k++) {
                int pv = (int)((*(char **)(s + 0x38 + k * 4)) - pool) >> 4;

                acc[pv * 3] = shift[k][0] + acc[pv * 3];
                acc[pv * 3 + 1] = acc[pv * 3 + 1] + shift[k][1];
                acc[pv * 3 + 2] = shift[k][2] + acc[pv * 3 + 2];
                cnt[pv] = cnt[pv] + 1;
            }
            break;
        }
    }
    for (idx = 0; idx < 1024; idx++) {
        if (cnt[idx] != 0) {
            long double inv = 1.0f / (long double)cnt[idx];
            float *p = (float *)(pool + idx * 16 + 4);

            p[0] = (float)((long double)acc[idx * 3] * inv + p[0]);
            p[1] = (float)((long double)acc[idx * 3 + 1] * inv + p[1]);
            p[2] = (float)((long double)acc[idx * 3 + 2] * inv + p[2]);
        }
    }
}

/* ==== Str_ToLower (0x0047b5c0), Res_Touch (0x00482200), sputActor_SetSelectedActor (0x00490320) ====
 * Small functions the decompiler got wrong only in what they return: Str_ToLower ends with 0 (the last character, the
 * terminator, in EAX), Res_Touch returns whatever Res_MoveToFront left in EAX (that function is declared void) and
 * sputActor_SetSelectedActor passes the actor to sputActor_GetActorHandle without a second argument. */
char * __cdecl Str_ToLower(char *s)
{
    for (; *s != '\0'; s++)
        *s = (char)tolower((int)(char)*s);
    return (char *)0;
}

undefined * __cdecl Res_Touch(void *data)
{
    void *res = Res_FindByData(data);

    if (res == (void *)0)
        return (undefined *)0;
    return (undefined *)((int (*)(void *))Res_MoveToFront)(res);
}

int __cdecl sputActor_SetSelectedActor(int handle)
{
    int old = -1;

    if (g_pSelectedActor != (void *)0)
        old = ((int (*)(void *))sputActor_GetActorHandle)(g_pSelectedActor);
    if (-1 < handle && handle < g_nMaxActors)
        g_pSelectedActor = (void *)((int)g_pActors + handle * 0xa8);
    return old;
}
/* ==== sputLua_GetDiskFreeSpaceL (0x00498da0) ====
 * GetDiskFreeSpace() -> megabytes free on the current drive: bytes per sector / 1024 * sectors per cluster / 1024 * free
 * clusters.  Written by hand because Ghidra typed the output slots as float (the cast rewrite then mixed bit copies and
 * conversions). */
void sputLua_GetDiskFreeSpaceL(void)
{
    uint v[4];       /* bytes per sector, sectors per cluster, free clusters, total clusters */
    long double mb;

    GetDiskFreeSpaceA(0, (int)&v[1], (int)&v[0], (int)&v[2], (int)&v[3]);
    mb = (long double)(unsigned long long)v[0] * 0.0009765625f;
    mb = mb * (int)v[1];
    mb = mb * 0.0009765625f;
    mb = mb * (int)v[2];
    lua_pushnumber((float)mb);
}

/* ==== sputLua_GetActorChoresL (0x00499ff0), sputLua_GetActorLoopingChoresL (0x0049a2a0) ====
 * GetActorChores(actor, costume) returns a table {[i] = i for every chore i of the costume that is playing (status bit 0),
 * count = n}; the looping variant also needs status bit 1.  Written by hand: Ghidra reused one stack slot for the chore
 * index, the count and the table size and typed it float. */
static int actor_chores_table(int statusMask)
{
    int arg = lua_lua2C(1);
    void *luaObj = (void *)lua_lua2C(2);
    int *costume = (int *)0;
    int tab, total, count = 0;
    uint i;

    if (lua_isuserdata(arg) != 0 && lua_tag(arg) == 0x52544341) {
        arg = lua_getuserdata(arg);
        arg = (int)sputActor_ActorDeref(arg);
        if (FindCostumeInStack(luaObj, *(void **)(arg + 0xa0), (void **)&costume) == 0)
            return 0;
        if (costume != (int *)0) {
            tab = lua_createtable();
            total = Cos_InstCountChores(*costume);
            if (total != 0) {
                i = 0;
                do {
                    uint status = Cos_InstChoreStatus(*costume, i);
                    if ((status & statusMask) == (uint)statusMask) {
                        lua_pushobject(tab);
                        lua_pushnumber((float)i);
                        lua_pushnumber((float)i);
                        lua_settable();
                        count++;
                    }
                    i++;
                } while (i < (uint)total);
            }
            lua_pushobject(tab);
            lua_pushstring(s_count_004ec384);
            lua_pushnumber((float)(uint)count);
            lua_settable();
            lua_pushobject(tab);
            return 0;
        }
    }
    lua_pushnil();
    return 0;
}

void sputLua_GetActorChoresL(void)
{
    actor_chores_table(1);
}

void sputLua_GetActorLoopingChoresL(void)
{
    actor_chores_table(3);
}

/* ==== sputLua_WorldToScreenL (0x0049cf60) ====
 * WorldToScreen(x, y, z) -> screen x, y as numbers, or two nils when the point is not visible.  (rdPrimit3_GetScreenCoord
 * stores the screen position as two integers.) */
void sputLua_WorldToScreenL(void)
{
    int a1 = lua_lua2C(1);
    int a2 = lua_lua2C(2);
    int a3 = lua_lua2C(3);
    float world[3];
    int screen[3];

    if (lua_isnumber(a1) == 0 || lua_isnumber(a2) == 0 || lua_isnumber(a3) == 0)
        return;
    world[0] = lua_getnumber(a1);
    world[1] = lua_getnumber(a2);
    world[2] = lua_getnumber(a3);
    if (rdPrimit3_GetScreenCoord(world, (float *)screen) != 0) {
        lua_pushnumber((float)screen[0]);
        lua_pushnumber((float)screen[1]);
        return;
    }
    lua_pushnil();
    lua_pushnil();
}

/* ==== sputLua_NotifyControlHandlers (0x0049e0b0) ====
 * Calls system.buttonHandler / system.axisHandler (a function, or a table holding the function under the same name, which
 * is then called with the table as first argument) for every enabled control (16 byte records at 0x004e87c8: flags, input
 * id, last value) whose state changed.  Button controls (flags & 4) report (index, 1 or nil, x, y); axis controls report
 * (index, value).  The last value of a button is its integer state, that of an axis the float (the same slot).  Ghidra
 * typed the loop counter and the handler references float, which broke the conversions. */
undefined4 sputLua_NotifyControlHandlers(void)
{
    int btnIsMethod = 0, axisIsMethod = 0;
    int hasBtn = 0, hasAxis = 0;
    int sys, btnTab, btnFunc = 0, axisTab, axisFunc = 0;
    uint i;
    uint *rec;

    lua_beginblock();
    sys = lua_getref(g_nLrSystemTable);
    lua_pushobject(sys);
    lua_pushstring(s_buttonHandler_004ec574);
    btnTab = lua_gettable();
    if (lua_istable(btnTab) == 0) {
        if (lua_isfunction(btnTab) != 0) {
            btnIsMethod = 0;
            hasBtn = 1;
            btnFunc = btnTab;
        }
    } else {
        lua_pushobject(btnTab);
        lua_pushstring(s_buttonHandler_004ec574);
        btnFunc = lua_gettable();
        if (lua_isfunction(btnFunc) != 0) {
            btnIsMethod = 1;
            hasBtn = 1;
        }
    }
    sys = lua_getref(g_nLrSystemTable);
    lua_pushobject(sys);
    lua_pushstring(s_axisHandler_004ec568);
    axisTab = lua_gettable();
    if (lua_istable(axisTab) == 0) {
        if (lua_isfunction(axisTab) != 0) {
            axisIsMethod = 0;
            hasAxis = 1;
            axisFunc = axisTab;
        }
    } else {
        lua_pushobject(axisTab);
        lua_pushstring(s_axisHandler_004ec568);
        axisFunc = lua_gettable();
        if (lua_isfunction(axisFunc) != 0) {
            axisIsMethod = 1;
            hasAxis = 1;
        }
    }
    rec = &UINT_004e87d0;
    for (i = 0; i < (uint)g_nSputControl_numControlSymbols; i++, rec += 4) {
        if ((rec[-2] & 1) == 0)
            continue;
        if ((rec[-2] & 4) == 0) {
            float v = stdControl_ReadAxis(rec[-1]);

            if ((rec[-2] & 8) != 0)
                v = -v;
            if ((v < *(float *)rec || v > *(float *)rec) && hasAxis != 0) {
                if (axisIsMethod != 0)
                    lua_pushobject(axisTab);
                lua_pushnumber((float)i);
                lua_pushnumber(v);
                lua_callfunction(axisFunc);
                *(float *)rec = v;
            }
        } else {
            uint x = 0;
            int y;
            int state = stdControl_ReadKey(rec[-1], (int *)&x, &y);

            if (state != (int)*rec && hasBtn != 0) {
                if (btnIsMethod != 0)
                    lua_pushobject(btnTab);
                lua_pushnumber((float)i);
                if (state == 0)
                    lua_pushnil();
                else
                    lua_pushnumber(1.0f);
                lua_pushnumber((float)x);
                lua_pushnumber((float)y);
                lua_callfunction(btnFunc);
                *rec = (uint)state;
            }
        }
    }
    lua_endblock();
    return 0;
}

/* ==== Actor_UpdateMovement (0x0048fd90) ====
 * Per frame: remembers the position, rescues the costume, follows the path (actor+8 bit 0), updates the walker, the
 * movement chores, the costumes (dt scaled by the actor's time scale), the look-at (bit 1) and the puck orientation
 * (actor+4 bit 4).  Its callee Actor_PuckOrient takes the actor (Ghidra had typed that parameter float). */
void Actor_UpdateMovement(void *actor, float dt)
{
    char *a = (char *)actor;
    int costume;

    if (*(int *)(a + 0xa4) != 0)
        dt = *(float *)(*(int *)(a + 0xa4) + 0x41c) * dt;
    costume = *(int *)(a + 0xa0);
    *(undefined4 *)(a + 0x18) = *(undefined4 *)(a + 0xc);
    *(undefined4 *)(a + 0x1c) = *(undefined4 *)(a + 0x10);
    *(undefined4 *)(a + 0x20) = *(undefined4 *)(a + 0x14);
    if (costume != 0 && *(int *)(costume + 0x7c) != 0) {
        if (*(int *)(costume + 0x7c) == 0) {
            (*g_pStd_HS->pAssertFail)(s_Bad_costume_Reference_004e9e90, s_main_sputResource_h_004e80a8, 0xb8);
        }
        Cos_InstRescue(**(int **)(a + 0xa0), *(int *)(costume + 0x80));
    }
    if ((*(byte *)(a + 8) & 1) != 0)
        Actor_FollowPath(actor);
    if (*(int *)(a + 0xa4) != 0 && *(int *)(*(int *)(a + 0xa4) + 0x1b4) != 0)
        Actor_UpdateWalker(actor);
    Actor_UpdateMoveChores(actor);
    sputCostume_Update(*(void **)(a + 0xa0), dt);
    if ((*(byte *)(a + 8) & 2) != 0)
        Actor_UpdateLookAt(actor, dt);
    if ((*(byte *)(a + 4) & 0x10) != 0)
        Actor_PuckOrient(actor);
}

/* ==== Actor_PuckOrient (0x00490f50) ====
 * ActorPuckOrient, at the end of the actor update when actor+4 & 0x10: rebuilds the actor matrix, takes the angle between its
 * up row (actor+0x50) and the up vector of the walker frame (walker+0x24); over 2 degrees the actor turns about
 * up x normal by min(angle, frame seconds * turn rate (actor+0xa4 +0x1c)), multiplies the matrices (rdMatrix_PostMultiply34) and
 * sets the three angles from the matrix (rdMatrix_ExtractAngles34).  The Ghidra prototype typed the actor parameter float, which
 * made the generated code treat the pointer as a number (crash with the original save grim21); it is a pointer. */
void __cdecl Actor_PuckOrient(void *actor)
{
    char *a = (char *)actor;
    char *state, *walker;
    float up[3], fu[3], axis[3], rot[12];
    volatile float dot;
    float ang;
    long double angx, limit;

    if (actor == (void *)0)
        return;
    state = *(char **)(a + 0xa4);
    if (state == (char *)0)
        return;
    walker = *(char **)(state + 0x1b4);
    if (walker == (char *)0)
        return;
    rdMatrix_Build34(a + 0x38, a + 0x24, a + 0xc);
    up[0] = *(float *)(a + 0x50);
    up[1] = *(float *)(a + 0x54);
    up[2] = *(float *)(a + 0x58);
    fu[0] = *(float *)(walker + 0x24);
    fu[1] = *(float *)(walker + 0x28);
    fu[2] = *(float *)(walker + 0x2c);
    dot = rdVector_Dot3(up, fu);
    angx = 90.0L - (long double)stdMath_ArcSin3(dot);     /* the test below uses the unrounded value */
    ang = (float)angx;
    if (!(((angx < 0.0L) ? -angx : angx) > 2.0L))
        return;
    limit = (long double)sputTime_GetFrameTimeFlex() * *(float *)(state + 0x1c);
    if (ang > 0.0f && limit < (long double)ang)
        ang = (float)limit;
    if (ang < 0.0f && -limit > (long double)ang)
        ang = (float)-limit;
    axis[0] = (float)((long double)fu[2] * up[1] - (long double)fu[1] * up[2]);
    axis[1] = (float)((long double)fu[0] * up[2] - (long double)fu[2] * up[0]);
    axis[2] = (float)((long double)fu[1] * up[0] - (long double)fu[0] * up[1]);
    rdVector_Normalize3Acc(axis);
    rdMatrix_BuildFromVectorAngle34(rot, axis, ang);
    rdMatrix_PostMultiply34(a + 0x38, rot);
    rdMatrix_ExtractAngles34(a + 0x38, a + 0x24);
    rdMatrix_Build34(a + 0x38, a + 0x24, a + 0xc);
}
/* ==== sputText_CreateActorText (0x0048b2e0) ====
 * Creates the speech text object above the actor and clamps it to the screen: the anchor is the actor's stored speech
 * position (actor+0x6c) while it speaks off screen, otherwise the projected head position (when the actor is in the
 * current set and visible), otherwise the default position; x defaults to the anchor's centre, y to the anchor's top minus
 * the text height; the text box keeps 40 / 10 pixels from the screen edges.  There is no floating point in it: Ghidra typed
 * the integer anchor float, which the cast rewrite then converted.  The text context is a copy of g_SubtitleTextCtx
 * (12 dwords) with the clip rectangle pointer at [1] and the text colour at [5]. */
void * __cdecl sputText_CreateActorText(void *actor, char *text, int x, int y)
{
    char *a = (char *)actor;
    int rect[4], ctx[12], pt[3], proj[3];
    int *anchor, half, h;
    void *obj;

    rect[0] = 0;
    rect[1] = 0;
    rect[2] = UINT_008a94bc;
    rect[3] = UINT_008a94c0;
    pt[0] = g_nSubtitleDefaultX;
    pt[1] = g_nSubtitleDefaultY;
    pt[2] = UINT_004e8490;
    memcpy(ctx, &g_SubtitleTextCtx, sizeof(ctx));
    ctx[1] = (int)rect;
    ctx[5] = *(int *)(*(int *)(a + 0xa4) + 0x418);
    ctx[6] = 0;
    ctx[7] = 0;
    if (*(int *)(a + 0x68) == 0 || g_dwGrimlib_mode == 3) {
        anchor = pt;
        if (*(int *)(a + 0xa0) == 0 || (*(byte *)(a + 4) & 2) != 0) {
            char *setName = sputRoom_GetCurrentRoomName();

            if (_stricmp((int)(a + 0x7c), setName) == 0 && rdPrimit3_GetScreenCoord((float *)(a + 0xc), (float *)proj) != 0) {
                pt[0] = proj[0];
                pt[1] = proj[1];
            }
        }
    } else {
        anchor = (int *)(a + 0x6c);
    }
    half = Text_GetStringWidth(ctx, text) / 2;
    if (x == -1)
        x = anchor[2] / 2 + anchor[0];
    if (x - half < 0x28)
        x = half + 0x28;
    if ((int)(UINT_008a94bc - 0x28) < half + x)
        x = (UINT_008a94bc - half) - 0x28;
    ctx[4] = *(int *)(*(int *)ctx[2] + 8);
    ctx[3] = x;
    h = Text_GetStringHeight(ctx, text);
    if (y == -1)
        y = anchor[1] - h;
    if (y < 10)
        y = 10;
    if ((int)(UINT_008a94c0 - 10) < y + h)
        y = (UINT_008a94c0 - h) + -10;
    ctx[4] = *(int *)(*(int *)ctx[2] + 8) + y;
    ctx[3] = x;
    obj = TextObject_New(ctx, text, 0, 0);   /* (the last two parameters are not read: the prototype has them since agent O's rename)*/
    *(void **)((char *)obj + 0x254) = actor;
    *(uint *)(a + 4) = *(uint *)(a + 4) | 4;
    return obj;
}
/* ==== sputText_PrintLineL (0x0048b830) ====
 * PrintLine(text, table): shows a line of text on screen with the options of the table (position, colour, duration ...).  When
 * the table gives no duration it is (characters * ms per character + base ms) * 16.666668 - the two values at 0x004e8470 /
 * 0x004e8474 are in front of UINT_004e8480.  The decompiler lost the operand of that _ftol. */

void sputText_PrintLineL(void)

{
  char cVar1;
  int iVar2;
  void *pvVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  uint *puVar7;
  uint *puVar8;
  uint local_5c;
  int local_58;
  char local_50 [32];
  uint local_30 [12];
  
  iVar2 = lua_lua2C(1);
  pvVar3 = (void *)lua_lua2C(2);
  local_58 = -1;
  if ((int)UINT_008a94bc <= (int)UINT_004e8480) {
    UINT_004e8480 = UINT_008a94bc;
  }
  if ((int)UINT_008a94c0 <= (int)UINT_004e8484) {
    UINT_004e8484 = UINT_008a94c0;
  }
  iVar4 = lua_isstring(iVar2);
  if (((iVar4 != 0) || (iVar4 = lua_isnil(iVar2), iVar4 != 0)) &&
     ((iVar4 = lua_istable((int)pvVar3), iVar4 != 0 || (iVar4 = lua_isnil((int)pvVar3), iVar4 != 0))
     )) {
    iVar4 = lua_isnil(iVar2);
    if (iVar4 == 0) {
      local_5c = (uint)local_30;
      puVar7 = &g_PrintLineTextCtx;
      puVar8 = local_30;
      for (iVar4 = 0xc; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar8 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar8 = puVar8 + 1;
      }
    }
    else {
      local_5c = (uint)&g_PrintLineTextCtx;
    }
    iVar4 = lua_istable((int)pvVar3);
    if (iVar4 != 0) {
      local_58 = GetTextParamsFromTable((void *)local_5c,pvVar3,(void *)0x0);
    }
    iVar4 = lua_isstring(iVar2);
    if (iVar4 != 0) {
      pcVar6 = local_50;
      pcVar5 = (char *)lua_getstring(iVar2);
      pcVar6 = sputText_ExtractSayLineData(pcVar5,pcVar6);
      if (local_58 < 0) {
        /* display time: (length * ms per character + base ms) * 16.666668 truncated */
        uint *msTab = (uint *)&UINT_004e8480 - 4;
        uint len = strlen(pcVar6);
        local_58 = (int)(long long)((long double)(unsigned long long)(len * msTab[1] + msTab[0]) * 16.666668f);
      }
      iVar2 = 0;
      pvVar3 = TextObject_New((void *)local_5c,pcVar6,0,0);
      sputText_AddToQueue(pvVar3,local_58,iVar2);
    }
  }
  return;
}

/* ==== stdDisplay_VBufferNew (0x00474480) ====
 * Std/Win95/Stddisplay.c: creates a surface record (0xd8 bytes) from a 19-dword format / size description `info` (copied to
 * +0xc: width +0xc, height +0x10, bits per pixel +0x24) and, when `videoMem` is set and the display device is a DirectDraw one,
 * a DirectDraw surface (offscreen plain, in system memory when `b` is 0) with its palette built from the 256 RGB triplets of
 * `palette` (entries 0 and 255 flagged 0x40, 1..254 flagged 1).  Otherwise the pixels are a plain memory block.  The Ghidra
 * text had dropped the file / line arguments of both allocations (the allocator stores them in the block header) and
 * printed the palette entries as unnamed stack slots.  The line numbers are a base word (0x004de1d0, in front of the file
 * name string's data) plus 0xd / 0x2a, like in the other allocations of this file. */
void * __cdecl stdDisplay_VBufferNew(void *info, int videoMem, int b, int palette)
{
    char *file = s_C__grimjedi_Libs_Std_Win95_Stddi_004dea18;
    int lineBase = (int)*(short *)(file - 0x848);
    uint *s;
    uint bpp8;
    int size;
    uint *desc;
    int hr, i;
    const byte *pal;
    byte entries[256 * 4];

    s = (uint *)(*g_pStd_HS->pAlloc)(0xd8, file, lineBase + 0xd);
    if (s == (uint *)0)
        return (void *)0;
    s[0x16] = palette;
    s[0x17] = 0;
    s[1] = 0;
    Mem_Copy(s + 3, info, 0x4c);
    bpp8 = s[9] >> 3;
    s[6] = bpp8 * s[3];
    s[0x18] = 0;
    s[7] = s[6] / bpp8;
    size = bpp8 * s[3] * s[4];
    s[5] = size;
    if (videoMem == 0 || g_nDisplayDeviceOpen == 0 || *(int *)((char *)g_pDisplayDevice + 0x100) != 1) {
        s[0] = 0;
        s[2] = 0;
        s[0x17] = (uint)(*g_pStd_HS->pAlloc)(size, file, lineBase + 0x2a);
        if (s[0x17] == 0)
            return (void *)0;
        s[1] = 1;
        return s;
    }
    /* a DirectDraw surface */
    s[2] = 0;
    s[0] = 1;
    desc = s + 0x1b;                         /* DDSURFACEDESC at +0x6c */
    memset(desc, 0, 0x1b * sizeof(uint));
    desc[0] = 0x6c;                          /* dwSize */
    desc[1] = 7;                             /* dwFlags: caps, height, width */
    s[0x35] = 0x40;                          /* ddsCaps: offscreen plain */
    if (b == 0)
        s[0x35] = 0x840;                     /* ... in system memory */
    s[0x1e] = s[3];                          /* dwWidth */
    s[0x1d] = s[4];                          /* dwHeight */
    hr = (**(int (__stdcall **)(void *, void *, void *, void *))(*(int *)g_pDirectDraw + 0x18))(g_pDirectDraw, desc, &s[0x19], (void *)0);
    if (hr != 0)
        return (void *)0;
    hr = (**(int (__stdcall **)(void *, void *))(*(int *)s[0x19] + 0x58))((void *)s[0x19], desc);   /* GetSurfaceDesc */
    if (hr != 0)
        return (void *)0;
    if ((s[0x35] & 0x4000) != 0)
        s[2] = 1;                            /* video memory */
    s[6] = s[0x1f];                          /* lPitch */
    s[7] = s[0x1f] / bpp8;
    if (palette == 0) {
        s[0x1a] = 0;
        return s;
    }
    pal = (const byte *)palette + 3;
    entries[3] = 0x40;
    entries[255 * 4 + 3] = 0x40;
    for (i = 1; i < 255; i++) {
        entries[i * 4] = pal[0];
        entries[i * 4 + 1] = pal[1];
        entries[i * 4 + 2] = pal[2];
        entries[i * 4 + 3] = 1;
        pal += 3;
    }
    hr = (**(int (__stdcall **)(void *, int, void *, void *, void *))(*(int *)g_pDirectDraw + 0x14))(g_pDirectDraw, 0xc, entries, &s[0x1a], (void *)0);   /* CreatePalette */
    if (hr != 0)
        return (void *)0;
    hr = (**(int (__stdcall **)(void *, void *))(*(int *)s[0x19] + 0x7c))((void *)s[0x19], (void *)s[0x1a]);   /* SetPalette */
    if (hr != 0)
        return (void *)0;
    return s;
}
/* ==== Walker_UpdateYaw (0x00491230) ====
 * Walker_UpdateYaw(actor, pos): eases the visible yaw (actor+0x28) toward the walker heading.  Done (returns 1) when under
 * 0.5 degrees.  step = rate * frame seconds * time scale; if the remaining angle is larger than the step it becomes
 * (remaining - step) * 0.1 + step.  A rate <= 0 (snap) jumps the whole way and negates the rate.  The x87 code takes the
 * unordered result of a compare (NaN, e.g. an actor with scale 0) the same way as "equal" / "less or equal", which is why
 * the first and last tests are written as they are: this is the behaviour the decompiled C missed.  The step stays in
 * extended precision, the remaining angle is a float. */
undefined4 Walker_UpdateYaw(void *actor, float *pos)
{
    char *a = (char *)actor;
    char *st;
    float *frame = sputActor_GetOrientMatrix(actor);
    float v[3], rot[12], ang, rate;
    long double angx, step;

    v[0] = frame[3];
    v[1] = frame[4];
    v[2] = frame[5];
    st = *(char **)(a + 0xa4);
    rate = *(float *)(st + 0x24);                       /* roll about the frame's up axis */
    if (rate < 0.0f || rate > 0.0f) {
        rdMatrix_BuildFromVectorAngle34(rot, sputActor_GetOrientMatrix(actor) + 6, rate);
        rdMatrix_TransformVector34Acc(v, rot);
    }
    v[0] = v[0] + pos[0];
    v[1] = pos[1] + v[1];
    v[2] = pos[2] + v[2];
    Walker_ToLocalSpace(pos, v);
    v[2] = 0.0f;
    rdVector_Normalize3Acc(v);
    angx = 90.0L - (long double)stdMath_ArcSin3(v[1]);
    ang = (float)angx;
    if (!(angx >= 0.5L)) {
        *(undefined4 *)(*(char **)(a + 0xa4) + 0x28) = 0;
        return 1;
    }
    st = *(char **)(a + 0xa4);
    *(float *)(st + 0x28) = ang;
    rate = *(float *)(st + 0x1c);
    if (!(rate > 0.0f)) {
        *(float *)(st + 0x1c) = (float)((long double)rate * -1.0f);     /* snap: all the way, and the rate comes back positive */
        step = 3.4028234663852886e+38L;
    } else {
        step = (long double)sputTime_GetFrameTimeFlex() * *(float *)(st + 0x41c) * *(float *)(st + 0x1c);
    }
    if ((long double)ang > step)
        ang = (float)(((long double)ang - step) * 0.1f + step);
    {
        float yaw = *(float *)(a + 0x28);

        if (v[0] > 0.0f)
            yaw = (float)((long double)yaw + ang);
        else
            yaw = (float)((long double)yaw - ang);
        *(float *)(a + 0x28) = yaw;
    }
    *(undefined4 *)(a + 0x34) = 0;
    return 0;
}
/* ==== ResType_FontHandler (0x0048dbd0) ====
 * Resource type handler for 'FONT' (entry of g_ResTypeTable): op 1 loads (Font_LoadFile, registered and kept locked), op 2
 * frees, op 3 reports the size.  Font_LoadFile returns the font through a pointer: the old text passed the address of the
 * parameter slot. */
void * ResType_FontHandler(int *rec)
{
    int *font;

    if (rec[2] != 0x544e4f46)
        return (void *)0;
    if (rec[0] == 1) {
        if (Font_LoadFile((char *)rec[1], &font) == 0) {
            void *res = Res_SysAddHandle(rec[2], (char *)rec[1], font);

            Res_SetPurgable(font, 0);
            return res;
        }
    } else if (rec[0] == 2) {
        Text_FreeFont((void *)rec[3]);
        return (void *)1;
    } else if (rec[0] == 3) {
        rec[4] = 1;
        return (void *)1;
    }
    return (void *)0;
}

/* ==== ThingAdjuster (0x00496890) ====
 * Editor dialog 'Resolve parent offset': a one field dialog on the component's flag at +0x34; on OK the key text becomes
 * "<name> <value>". */
undefined4 ThingAdjuster(int *component, undefined4 text)
{
    int obj = *component;
    char *labels[1];
    int value;
    int tok;
    char out[32];

    labels[0] = s_Resolve_parent_offset__0___off__004ea5e0;
    value = (*(int *)(obj + 0x34) != 0);
    if (grimPlat_SpinDialog(text, (int)labels, (undefined4 *)&value, 1) == 0)
        return 0;
    tok = strtok(text, &DAT_004ea52c);
    *(int *)(obj + 0x34) = value;
    sprintf(out, s__s__d_004ea5d8, tok, value);
    strncpy(tok, out, 0x1f);
    *(undefined1 *)(tok + 0x1f) = 0;
    return 1;
}

/* ==== Polyglot_LoadTable (0x00483720) ====
 * polyglot.c: loads the language table (text id -> translated string) from the file `name`: 4 magic bytes ('RCNE' = the rest
 * is XOR 0xdd encrypted), then lines "ID<TAB>text" ended by CR LF.  The line start pointers are kept in a table that is
 * sorted for lookups.  The old text read the magic into the parameter slot. */
void Polyglot_LoadTable(undefined *name)
{
    int file, size, i;
    char *p, *end;
    undefined *magic;
    undefined1 *tab;

    PTR_s_language_tab_004e8024 = name;
    file = (*g_pSvcIMuseModule->pFopen)(name, &DAT_004ddb18);
    if (file == 0)
        return;
    (*g_pSvcIMuseModule->pFread)(file, &magic, 4);
    (*g_pSvcIMuseModule->pFseek)(file, 0, 2);
    size = (*g_pSvcIMuseModule->pFtell)(file);
    (*g_pSvcIMuseModule->pFseek)(file, 0, 0);
    g_pPolyglotText = (char *)(*g_pSvcIMuseModule->pAlloc)(size, s_C__grimsrc_libs_grimlib_Engine_p_004e8038, 0x8f);
    (*g_pSvcIMuseModule->pFread)(file, g_pPolyglotText, size);
    (*g_pSvcIMuseModule->pFclose)(file);
    p = g_pPolyglotText;
    if (magic == (undefined *)0x454e4352) {
        size -= 4;
        for (i = 0; i < size; i++)
            g_pPolyglotText[i] = g_pPolyglotText[i + 4] ^ 0xdd;
        p = g_pPolyglotText;
    }
    do {                                    /* count the lines */
        tab = Str_FindChar(p, 0xd);
        UINT_008a8ca4 = UINT_008a8ca4 + 1;
        p = (char *)tab + 2;
    } while (p < g_pPolyglotText + size - 1);
    UINT_008a8c9c = (*g_pSvcIMuseModule->pAlloc)(UINT_008a8ca4 * 4, s_C__grimsrc_libs_grimlib_Engine_p_004e8038, 0xa2);
    i = 0;
    p = g_pPolyglotText;
    do {                                    /* terminate every line and its id, upper case the id, store the pointer */
        char *tabc;

        end = (char *)Str_FindChar(p, 0xd);
        *end = 0;
        tabc = (char *)strchr(p, 9);
        if (tabc != (char *)0)
            *tabc = 0;
        _strupr(p);
        *(char **)(UINT_008a8c9c + i) = p;
        p = end + 2;
        i += 4;
    } while (p < g_pPolyglotText + size - 1);
    qsort(UINT_008a8c9c, UINT_008a8ca4, 4, Str_ComparePtrs);
}

/* ==== SoundChanger (0x004971a0) ====
 * Costume tag handler for 'iMuse Streamed / Resident Sound FX' (registered by sputCostume_Startup through
 * Cos_NewStateBasedTag / Cos_NewIntTag): when the chore key fires it starts the sound unless it already plays (state 0 and
 * not playing): a streamed sound ('imss') through SoundStartVoiceStream, a resident one ('imls') through
 * SoundsLoadStartSound with positional parameters from the current set; state 1 stops it again, state 2 sets iMUSE hook 0x80.
 * Arguments: tag, sound record, -, state slot, -, -, -, costume instance.  The five outputs of sputRoom_GetSoundParameters were
 * written over spent parameter slots in the original; Ghidra typed the sound pointer and the slot float. */
void __cdecl SoundChanger(int tag, int snd, undefined4 p3, int slot, uint p5, uint p6, uint p7, uint inst)
{
    int actor = Cos_InstGetUserData(inst);
    void *actors = g_pActors;
    const uint *state = (const uint *)&g_aSoundCommands;
    float o1, o4, o5;
    uint o2 = 0, o3 = 0, loud;
    byte quiet;
    void *set;
    int handle;

    if (state[slot] == 0 && SoundsIsSoundPlaying(snd) == 0) {
        if (tag != 0x736c6d69) {
            if (tag != 0x73736d69)
                return;
            SoundStartVoiceStream(snd, (uint) * (byte *)(snd + 0x20), (int)*(char *)(snd + 0x21));
            SoundsSetParam(snd, 0x400, 1);
            SoundsSetParam(snd, 0x500, *(uint *)(snd + 0x24));
            return;
        }
        set = sputRoom_GetCurrentRoom();
        handle = SoundsLoadStartSound(snd, *(int *)(snd + 0x24), 1);
        if (set == (void *)0)
            return;
        sputRoom_GetSoundParameters(set, &o1, (char *)&o2, (char *)&o3, &o4, &o5);
        quiet = *(byte *)(snd + 0x20);
        if ((byte)o3 < quiet)
            quiet = (byte)o3;
        loud = o2 & 0xff;
        if ((int)loud <= (int)*(uint *)(snd + 0x28))
            loud = *(uint *)(snd + 0x28);
        sputRoom_SetSoundPosition(handle, (int)actors + actor * 0xa8 + 0xc, loud, quiet, *(uint *)&o1, *(uint *)&o5);   /* (the floats' bits) */
        return;
    }
    if (state[slot] == 1) {
        if (tag == 0x736c6d69) {
            SoundsStopSound(snd);
            return;
        }
        if (tag == 0x73736d69) {
            SoundStopVoiceStream();
            return;
        }
    } else if (state[slot] == 2) {
        iMUSE_SetHook(snd, 0x80);
    }
}
/* ==== Collision_PointInBox (0x00492510) ====
 * True when the segment from `a` to `b` (both moved by `offset`) does not hit the box (xmin, ymin, zmin, xmax, ymax, zmax
 * passed by value, then one more pointer for Collision_SegmentHitsBox) and Planner_PlanPath accepts a plan between the two
 * points.  The Ghidra prototype took the box as six unsigned integers; they are floats. */
undefined4 __cdecl Collision_PointInBox(float *a, float *b, float *p3, float bx0, float by0, float bz0, float bx1, float by1,
                                        float bz1, float *p10, float *offset)
{
    float pa[3], pb[3];

    pa[0] = offset[0] + a[0];
    pa[1] = a[1] + offset[1];
    pa[2] = a[2] + offset[2];
    pb[0] = offset[0] + b[0];
    pb[1] = b[1] + offset[1];
    pb[2] = b[2] + offset[2];
    if (((int (*)(float *, float *, float *, float, float, float, float, float, float, float *))Collision_SegmentHitsBox)(
            pa, pb, p3, bx0, by0, bz0, bx1, by1, bz1, p10) != 0)
        return 0;
    return Planner_PlanPath(a, b, 0);
}
/* OVERRIDES: Collision_BoxSlide */
/* ==== Collision_BoxSlide (0x00494100) ====
 * Box collision response (entry face from the move, slide along the face): finds the face of the box (xmin param_3, xmax
 * param_6 ... ) that the move from param_2 towards param_1 enters first, the hit point (also stored in 0x008ca320..28), and
 * turns the remaining move about up x normal by the angle between the move and the face.  Head-on slides depend on float
 * noise of a zero rotation axis, either side.  The decompiler reused the parameter slots param_3..5 for the rotation axis;
 * that is a local array here. */
undefined4
Collision_BoxSlide(float *param_1,float *param_2,float param_3,float param_4,float param_5,
                  float param_6,float param_7,float param_8,float *param_9)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float *pfVar8;
  int iVar9;
  float fVar10;
  float fVar11;
  float axis[3];
  float vv[3];          /* Ghidra local_48 / local_44[2]: the move vector, three consecutive floats */
  float nn[3];          /* Ghidra local_3c / local_38[2]: the face normal */
  float local_30 [12];
  
  pfVar8 = param_9;
  iVar9 = 0;
  fVar10 = *param_1 - *param_2;
  fVar1 = param_1[1] - param_2[1];
  fVar3 = param_1[2] - param_2[2];
  fVar11 = fVar10 * -10.0 + *param_2;
  fVar2 = fVar1 * -10.0 + param_2[1];
  fVar6 = fVar3 * -10.0 + param_2[2];
  *param_2 = fVar11;
  fVar5 = 3.4028235e+38;
  param_2[1] = fVar2;
  param_2[2] = fVar6;
  if (param_6 - 0.002 < fVar11) {
    fVar4 = fVar10;
    if (fVar10 < 0.0) {
      fVar4 = -fVar10;
    }
    fVar4 = (param_6 - *param_1) / fVar4;
    fVar7 = fVar4;
    if (fVar4 < 0.0) {
      fVar7 = -fVar4;
    }
    fVar5 = 3.4028235e+38;
    if (fVar7 < 3.4028235e+38) {
      fVar5 = -fVar4;
      iVar9 = 1;
      nn[0] = 1.0;
      nn[1] = 0.0;
      nn[2] = 0.0;
    }
  }
  if (fVar11 < param_3 - -0.002) {
    fVar11 = fVar10;
    if (fVar10 < 0.0) {
      fVar11 = -fVar10;
    }
    fVar11 = (param_3 - *param_1) / fVar11;
    fVar4 = fVar11;
    if (fVar11 < 0.0) {
      fVar4 = -fVar11;
    }
    fVar7 = fVar5;
    if (fVar5 < 0.0) {
      fVar7 = -fVar5;
    }
    if (fVar4 < fVar7) {
      iVar9 = 2;
      nn[0] = -1.0;
      nn[1] = 0.0;
      nn[2] = 0.0;
      fVar5 = fVar11;
    }
  }
  if (param_7 - 0.002 < fVar2) {
    fVar11 = fVar1;
    if (fVar1 < 0.0) {
      fVar11 = -fVar1;
    }
    fVar11 = (param_7 - param_1[1]) / fVar11;
    fVar4 = fVar11;
    if (fVar11 < 0.0) {
      fVar4 = -fVar11;
    }
    fVar7 = fVar5;
    if (fVar5 < 0.0) {
      fVar7 = -fVar5;
    }
    if (fVar4 < fVar7) {
      fVar5 = -fVar11;
      iVar9 = 3;
      nn[0] = 0.0;
      nn[1] = 1.0;
      nn[2] = 0.0;
    }
  }
  if (fVar2 < param_4 - -0.002) {
    fVar11 = fVar1;
    if (fVar1 < 0.0) {
      fVar11 = -fVar1;
    }
    fVar11 = (param_4 - param_1[1]) / fVar11;
    fVar2 = fVar11;
    if (fVar11 < 0.0) {
      fVar2 = -fVar11;
    }
    fVar4 = fVar5;
    if (fVar5 < 0.0) {
      fVar4 = -fVar5;
    }
    if (fVar2 < fVar4) {
      iVar9 = 4;
      nn[0] = 0.0;
      nn[1] = -1.0;
      nn[2] = 0.0;
      fVar5 = fVar11;
    }
  }
  if (param_8 - 0.002 < fVar6) {
    fVar11 = fVar3;
    if (fVar3 < 0.0) {
      fVar11 = -fVar3;
    }
    fVar11 = (param_8 - param_1[2]) / fVar11;
    fVar2 = fVar11;
    if (fVar11 < 0.0) {
      fVar2 = -fVar11;
    }
    fVar4 = fVar5;
    if (fVar5 < 0.0) {
      fVar4 = -fVar5;
    }
    if (fVar2 < fVar4) {
      fVar5 = -fVar11;
      iVar9 = 5;
      nn[0] = 0.0;
      nn[1] = 0.0;
      nn[2] = 1.0;
    }
  }
  if (fVar6 < param_5 - -0.002) {
    fVar11 = fVar3;
    if (fVar3 < 0.0) {
      fVar11 = -fVar3;
    }
    fVar11 = (param_5 - param_1[2]) / fVar11;
    fVar2 = fVar11;
    if (fVar11 < 0.0) {
      fVar2 = -fVar11;
    }
    fVar6 = fVar5;
    if (fVar5 < 0.0) {
      fVar6 = -fVar5;
    }
    if (fVar2 < fVar6) {
      iVar9 = 6;
      nn[0] = 0.0;
      nn[1] = 0.0;
      nn[2] = -1.0;
      fVar5 = fVar11;
    }
  }
  if (iVar9 == 0) {
    return 0;
  }
  *param_9 = fVar5 * fVar10 + *param_1;
  param_9[1] = fVar5 * fVar1 + param_1[1];
  param_9[2] = fVar5 * fVar3 + param_1[2];
  *(float *)&DAT_008ca320 = *param_9;   /* (the floats themselves: an undefined4 view converted them, grim_tools/cleanroom) */
  *(float *)&DAT_008ca324 = param_9[1];
  *(float *)&DAT_008ca328 = param_9[2];
  fVar11 = fVar5;
  if (fVar5 < 0.0) {
    fVar11 = -fVar5;
  }
  vv[0] = fVar10 * fVar11;
  fVar10 = fVar5;
  if (fVar5 < 0.0) {
    fVar10 = -fVar5;
  }
  vv[1] = fVar1 * fVar10;
  if (fVar5 < 0.0) {
    fVar5 = -fVar5;
  }
  vv[2] = fVar3 * fVar5;
  fVar10 = rdVector_Normalize3Acc(vv);
  fVar11 = rdVector_Dot3(vv,nn);
  fVar11 = stdMath_ArcSin3(fVar11);
  if (90.0 - fVar11 < 90.0) {
    return 0;
  }
  axis[0] = nn[2] * vv[1] - nn[1] * vv[2];
  axis[1] = nn[0] * vv[2] - nn[2] * vv[0];
  axis[2] = nn[1] * vv[0] - nn[0] * vv[1];
  rdVector_Normalize3Acc(axis);
  rdMatrix_BuildFromVectorAngle34(local_30,axis,(90.0 - fVar11) - 90.0);
  rdMatrix_TransformVector34Acc(vv,local_30);
  *pfVar8 = fVar10 * vv[0] + *pfVar8;
  pfVar8[1] = fVar10 * vv[1] + pfVar8[1];
  pfVar8[2] = fVar10 * vv[2] + pfVar8[2];
  return 1;
}
#endif /* GRIM_EXE */
