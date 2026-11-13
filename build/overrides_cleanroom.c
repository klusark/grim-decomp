/* Fixes found with the clean-room tests of grim_tools/cleanroom (`run.py decomp`, see build/cleanroom/README.md): each
 * function here differed from the original v1.01 exe in a test. They are written from the original machine code
 * (raw/GRIMFANDANGO.EXE/disasm.json) and the decompiled C, and say what the decompiled C got wrong. */
#include "ghidra_types.h"

#ifdef GRIM_EXE
#include "globals.h"
#include "functions.h"

/* x87 conventions (as in overrides_asm_p2.c): `long double` is a value the original keeps on the x87 stack, cr_st_f()
 * a store of it to a float slot (FSTP m32). An FCOMP / FNSTSW / TEST AH,mask branch is unordered-aware: with a NaN
 * operand C3, C2 and C0 are all set, so "equal" (0x40), "less" (0x01) and "less or equal" (0x41) are all true. */
#define CR_EQ_U(a, b) (!((long double)(a) < (long double)(b) || (long double)(a) > (long double)(b)))
#define CR_LT_U(a, b) (!((long double)(a) >= (long double)(b)))
#define CR_LE_U(a, b) (!((long double)(a) > (long double)(b)))
#define CR_FLT(addr) (*(float *)IMG_ADDR(addr))   /* a float constant of the original's .rdata */

static inline float cr_st_f(long double x)
{
    volatile float f = (float)x;
    return f;
}

/* stdMath_FlexPower's result as the x87 register it is returned in (not rounded to float by the caller) */
extern long double cr_PowInt(float x, int n) __asm__("_stdMath_FlexPower");
extern long double cr_NormalizeAngle360(float a) __asm__("_stdMath_NormalizeAngle");

/* FSQRT of a float argument, the x87 result as it is */
static inline long double cr_fsqrt(float x)
{
    long double r = x;
    __asm__("fsqrt" : "+t"(r));
    return r;
}

/* ==== the small math helpers (math.c) ====
 * The game's angle code runs through these; the decompiled C rounded where the original does not (and the reverse),
 * which moved turning, walking and the sphere collision tests of grim_tools/cleanroom by up to 1e-4 (turn_key,
 * actor_turn, sight_turn, mf_*_sphere, cm_to_*). Each is written from its machine code: a float slot is stored where
 * the original stores one (FSTP m32), a compare is the original's FCOMP / TEST AH. */

/* Math_Sqrt (0x47c490): FLD x; FSQRT; RET - the result stays an x87 value; the callers that are still assembled use it
 * unrounded, and a C body rounded it to float on return. */
/* OVERRIDES: Math_Sqrt */
__asm__(".text\n"
        ".globl _Math_Sqrt\n"
        "_Math_Sqrt:\n"
        "    flds 4(%esp)\n"
        "    fsqrt\n"
        "    ret\n");

/* stdMath_FlexPower (0x47bbe0): x^n by n - 1 multiplications, each stored to the float result (the first is x's dword) */
float stdMath_FlexPower(float x, int n)
{
    float r;
    int i;
    *(uint *)&r = *(uint *)&x;
    for (i = 0; i < n - 1; i++)
        r = cr_st_f((long double)r * x);
    return r;
}

/* stdMath_ArcSin1 (0x47c3b0): asin(x) in degrees, x - x^3 series near 0, through sqrt(1 - x^2) near 1 */
float stdMath_ArcSin1(float x)
{
    float ax, v;
    int neg = CR_LT_U(x, CR_FLT(0x004d872c));
    if (neg)
        ax = cr_st_f(-(long double)x);
    else
        *(uint *)&ax = *(uint *)&x;
    if (!CR_LE_U(ax, CR_FLT(0x004d8730))) {
        ax = cr_st_f(cr_fsqrt(cr_st_f((long double)CR_FLT(0x004d8734) - (long double)ax * ax)));
        v = cr_st_f((long double)CR_FLT(0x004d8740) - (cr_PowInt(ax, 3) * CR_FLT(0x004d8738) + ax) * CR_FLT(0x004d873c));
    } else {
        v = cr_st_f((cr_PowInt(ax, 3) * CR_FLT(0x004d8738) + ax) * CR_FLT(0x004d873c));
    }
    return neg ? -v : v;
}

/* stdMath_ArcSin3 (0x47c4a0): asin(x) in degrees from the series x + x^3/6 + 3x^5/40 + ... */
float stdMath_ArcSin3(float x)
{
    float ax, t1, t2, v;
    int neg = CR_LT_U(x, CR_FLT(0x004d8744));
    if (neg)
        ax = cr_st_f(-(long double)x);
    else
        *(uint *)&ax = *(uint *)&x;
    if (!CR_LE_U(ax, CR_FLT(0x004d8748))) {
        ax = cr_st_f(cr_fsqrt(cr_st_f((long double)CR_FLT(0x004d874c) - (long double)ax * ax)));
        t1 = cr_st_f(cr_PowInt(ax, 3) / CR_FLT(0x004d8750) + ax);
        t2 = cr_st_f(cr_PowInt(ax, 5) * CR_FLT(0x004d8754) + t1);
        v = cr_st_f((long double)CR_FLT(0x004d8760) - (cr_PowInt(ax, 7) * CR_FLT(0x004d8758) + t2) * CR_FLT(0x004d875c));
    } else {
        t1 = cr_st_f(cr_PowInt(ax, 3) / CR_FLT(0x004d8750) + ax);
        t2 = cr_st_f(cr_PowInt(ax, 5) * CR_FLT(0x004d8754) + t1);
        v = cr_st_f((cr_PowInt(ax, 7) * CR_FLT(0x004d8758) + t2) * CR_FLT(0x004d875c));
    }
    return neg ? -v : v;
}

/* stdMath_NormalizeAngleAcute (0x47bce0): the angle in (-180, 180]; the compare uses stdMath_NormalizeAngle's x87 result,
 * the arithmetic its float copy */
float stdMath_NormalizeAngleAcute(float a)
{
    long double r = cr_NormalizeAngle360(a);
    float v = cr_st_f(r);
    if (!CR_LE_U(r, CR_FLT(0x004d8700)))
        v = cr_st_f(-((long double)CR_FLT(0x004d8704) - v));
    return v;
}

/* stdMath_ArcTan4 (0x47c5f0): atan2 in degrees from a series, with the original's sign convention (0 is +y, the result
 * negated for x >= 0). Every compare of the original is FCOMP + TEST AH: the decompiled C read them as ordinary C
 * compares, which are false for a NaN where the original's are true. With NaN coordinates (the look-at of a head whose
 * target is straight ahead or behind: Actor_UpdateLookAt rotates about a zero axis) the original takes the "x == 0 and
 * y == 0" branch and returns 0, and the head stays at rest; the C went on and turned the head (grim_tools/cleanroom
 * head_look_front, head_look_behind). Written from the machine code, with its stores to float slots. */
float stdMath_ArcTan4(float y, float x)
{
    float ay, ax, q, t28, t2c, t30, c;
    int negY, negX;

    if (CR_EQ_U(x, CR_FLT(0x004d8764)) && CR_EQ_U(y, CR_FLT(0x004d8764)))
        return CR_FLT(0x004d8764);
    negY = CR_LT_U(y, CR_FLT(0x004d8764));
    if (negY)
        ay = cr_st_f(-(long double)y);
    else
        *(uint *)&ay = *(uint *)&y;
    negX = CR_LT_U(x, CR_FLT(0x004d8764));
    if (negX)
        ax = cr_st_f(-(long double)x);
    else
        *(uint *)&ax = *(uint *)&x;
    if (CR_LE_U(ax, ay))
        q = cr_st_f((long double)ax / ay);
    else
        q = cr_st_f((long double)ay / ax);
    if (CR_LT_U(q, CR_FLT(0x004d8764)))
        q = cr_st_f(-(long double)q);
    t28 = cr_st_f((long double)q - cr_PowInt(q, 3) / CR_FLT(0x004d8768));
    t2c = cr_st_f(cr_PowInt(q, 5) / CR_FLT(0x004d876c) + t28);
    t30 = cr_st_f((long double)t2c - cr_PowInt(q, 7) / CR_FLT(0x004d8770));
    c = cr_st_f((cr_PowInt(q, 9) * CR_FLT(0x004d8774) + t30) * CR_FLT(0x004d8778));
    if (!CR_LT_U(ay, ax))
        c = cr_st_f((long double)CR_FLT(0x004d877c) - c);
    c = cr_st_f((long double)CR_FLT(0x004d877c) - c);
    if (negY)
        c = cr_st_f((long double)CR_FLT(0x004d8780) - c);
    if (!negX)
        c = cr_st_f(-(long double)c);
    return c;
}

/* sputActor_DrawToClean (0x4937c0, Lua ActorToClean): draws the actor's costumes into the clean background with the colormap of
 * the actor (or of the set). The original pushes (colormap + 0x30, 0) for sputRender_SetPaletteFunc, which takes no
 * arguments and returns the palette callback (0x8c97b8), then calls that callback with the same two words still on the
 * stack (CALL EAX; ADD ESP,8). The decompiled C passed the two words to sputRender_SetPaletteFunc and called the callback
 * with none, so it read whatever was on the stack. */
void __cdecl sputActor_DrawToClean(Actor *actor_)
{
    /* the body still works on byte offsets (names/types_actor.json typed the parameter) */
    void *actor = (void *)actor_;
    int setup, bg, cmap, scale[3];
    void *set;
    int *pal;
    uint savedZ, savedBg;

    set = sputRoom_GetCurrentRoom();
    setup = *(int *)((int)set + 0xac) + *(int *)((int)set + 0xb4) * 300;
    bg = *(int *)(*(int *)(setup + 0x48) + 4);
    if (bg == 0)
        return;
    savedZ = *(uint *)(bg + 0x10);
    savedBg = *(uint *)(bg + 4);
    *(uint *)(*(int *)(*(int *)(setup + 0x48) + 4) + 4) = sputRender_CleanArtBuffer();
    *(uint *)(*(int *)(*(int *)(setup + 0x48) + 4) + 0x10) = sputRender_CleanZBuffer();
    pal = *(int **)actor;
    if (*pal == 0) {   /* no colormap of its own: the set's */
        set = sputRoom_GetCurrentRoom();
        pal = (int *)(*(int *)((int)set + 0x80) + *(int *)((int)set + 0x88) * 0x34);
        if (*pal == 0)
            (*g_pStd_HS->pAssertFail)(s_Bad_Colormap_Reference_004e8090, s_main_sputResource_h_004e80a8, 0x9f);
        rdroid_SetColormap(pal[1]);
        set = sputRoom_GetCurrentRoom();
        pal = (int *)(*(int *)((int)set + 0x80) + *(int *)((int)set + 0x88) * 0x34);
        if (*pal == 0)
            (*g_pStd_HS->pAssertFail)(s_Bad_Colormap_Reference_004e8090, s_main_sputResource_h_004e80a8, 0x9f);
    } else {
        rdroid_SetColormap(pal[1]);
        pal = *(int **)actor;
        if (*pal == 0)
            (*g_pStd_HS->pAssertFail)(s_Bad_Colormap_Reference_004e8090, s_main_sputResource_h_004e80a8, 0x9f);
    }
    cmap = pal[1];
    ((void (*)(int, int))sputRender_SetPaletteFunc())(cmap + 0x30, 0);
    if (*(int *)((int)actor + 0x30) != 0x3f800000) {
        scale[0] = scale[1] = scale[2] = *(int *)((int)actor + 0x30);
        rdMatrix_PreScale34(sputActor_GetOrientMatrix(actor), (undefined4)scale);
    }
    sputCostume_Draw3D(*(undefined4 *)((int)actor + 0xa0), (undefined4)sputActor_GetOrientMatrix(actor));
    *(undefined4 *)((int)actor + 0x34) = 0;
    rdCache_Flush();
    *(uint *)(*(int *)(*(int *)(setup + 0x48) + 4) + 4) = savedBg;
    *(uint *)(*(int *)(*(int *)(setup + 0x48) + 4) + 0x10) = savedZ;
}

/* res_FindDirectoryEntry (0x481cf0): a directory opened as an archive: finds `name` (lower case, with its hash) in the file
 * list LabDir_Open made (entries of {hash, name, -} from dir + 0x118), remembers the hit in the 16-entry cache, and fills
 * the entry: type, the name at +0x14, the path "<dir>\<name>" at +0x115, not in an archive (+4 = 0), the file size
 * (+8), offset and flag 0. Written from the machine code; before res_FindInternalFile passed its arguments this was never
 * reached with a valid hash, and the decompiled C of it misread entries (grim_tools/cleanroom save_load, tp_*). */
extern int GRIM_host_sprintf(char *, const char *, ...) __asm__("_sprintf");
undefined4 res_FindDirectoryEntry(int param_1, undefined4 param_2, byte *param_3, int param_4, undefined4 *param_5)
{
    int *e = *(int **)(param_1 + 0x118);
    uint n;

    if (e == 0)
        return 0;
    for (; e[1] != 0; e += 3) {
        const byte *a, *b;
        if (e[0] != param_4)
            continue;
        for (a = param_3, b = (const byte *)e[1]; *a == *b && *a != 0; a++, b++)
            ;
        if (*a == *b) {
            *(int **)((int)&g_aFoundFiles + g_dwLastFound * 4) = e;
            *(int *)((int)&g_aFoundFileNodes + g_dwLastFound * 4) = param_1;
            g_dwLastFound = (g_dwLastFound + 1) & 0xf;
            break;
        }
    }
    if (e[1] == 0)
        return 0;
    n = __builtin_strlen((const char *)param_3) + 1;
    memmove((char *)param_5 + 0x14, param_3, n);
    *param_5 = param_2;
    GRIM_host_sprintf((char *)param_5 + 0x115, (const char *)IMG_ADDR(0x004e7af8), (char *)(param_1 + 8), (char *)param_3);
    param_5[1] = 0;
    param_5[2] = (undefined4)(*(code **)(g_dwLowLevelHS + 0x50))((char *)param_5 + 0x115);
    param_5[3] = 0;
    param_5[4] = 0;
    return 1;
}

/* res_FindInternalFile (0x481630): looks the name up in every open archive, front to back. The original passes the same five
 * arguments (archive, 0, lower-case name, hash, entry) to Lab_FindEntry for a .LAB and to res_FindDirectoryEntry for a
 * directory opened as an archive; the decompiled C passed only three to res_FindDirectoryEntry, which then compared the
 * hash with garbage and never found a loose file: a name that is both loose in the working directory and in a .LAB
 * was read from the .LAB, where the original reads the loose file, the directory being in front of the archives
 * (grim_tools/cleanroom lab_dofile, docs/MODDING.md section 6). */
int __cdecl res_FindInternalFile(char *name, void *outEntry)
{
    char lower[260];
    uint hash = Res_HashName(name, lower);
    int *lab, found = 0;

    for (lab = g_pResFileList; lab != 0 && found == 0; lab = (int *)*lab) {
        if ((*(byte *)((int)lab + 0x114) & 2) == 0)
            found = res_FindDirectoryEntry((int)lab, 0, (byte *)lower, (int)hash, (undefined4 *)outEntry);
        else
            found = Lab_FindEntry(lab, 0, lower, hash, outEntry);
    }
    return found;
}

/* WalkPlane_ClosestPoint (0x4a6b30, __thiscall sector, point): moves `pt` onto the sector's edge it is outside of (for each
 * edge prev -> cur with the point on its outer side, the foot of the perpendicular; clamped to the edge's ends). The
 * decompiled C rounded every intermediate to float and used C compares; the original keeps the distance, the edge
 * length and the new x on the x87 stack, rounds only where it stores (n0 = -dy, n1 = dx, d, the new y), compares
 * unordered-aware, and copies an end vertex as three dwords. With huge coordinates (GetShrinkPos(0, 1e30, 0)) the values
 * overflow to inf / NaN and only that order gives the original's point (grim_tools/cleanroom args_GetShrinkPos_p1_big). */
int __thiscall WalkPlane_ClosestPoint(WalkPlane *this, int a1)
{
    float *pt = (float *)a1, *prev, *cur;
    float n0, n1, d, sy, e24;
    long double dist, L, sel, t, nx, ny, ex, r;
    int i;

    WalkPlane_Project(this, a1);
    prev = (float *)(*(int *)((int)this + *(int *)((int)this + 0x34) * 4 + 0x34) + 4);
    for (i = 0; i < *(int *)((int)this + 0x34); i++, prev = cur) {
        cur = (float *)(*(int *)((int)this + 0x38 + i * 4) + 4);
        n0 = cr_st_f(-((long double)cur[1] - prev[1]));
        n1 = cr_st_f((long double)cur[0] - prev[0]);
        dist = ((long double)pt[0] - prev[0]) * n0 + ((long double)pt[1] - prev[1]) * n1;
        d = cr_st_f(dist);
        if (!CR_LT_U(dist, 0.0f))
            continue;
        L = -((long double)n0 * n0) - (long double)n1 * n1;
        t = CR_LT_U(L, 0.0f) ? -L : L;
        sel = CR_LE_U(t, CR_FLT(0x004d891c)) ? (long double)CR_FLT(0x004d8918) : L;
        if (CR_EQ_U(sel, 0.0f))
            continue;
        t = (long double)d / L;
        nx = t * n0 + pt[0];
        ny = t * n1 + pt[1];
        sy = cr_st_f(ny);
        pt[0] = cr_st_f(nx);
        pt[1] = cr_st_f(ny);
        ex = (long double)cur[0] - prev[0];
        e24 = cr_st_f((long double)cur[1] - prev[1]);
        if (!CR_LE_U(CR_LT_U(ex, 0.0f) ? -ex : ex, CR_LT_U(e24, 0.0f) ? -(long double)e24 : (long double)e24))
            r = (nx - prev[0]) / ex;
        else
            r = ((long double)sy - prev[1]) / e24;
        if (i == *(int *)((int)this + 0x34) - 1 && !CR_LE_U(r, CR_FLT(0x004d8928))) {
            ((uint *)pt)[0] = ((uint *)cur)[0];
            ((uint *)pt)[1] = ((uint *)cur)[1];
            ((uint *)pt)[2] = ((uint *)cur)[2];
        } else if (CR_LT_U(r, 0.0f)) {
            ((uint *)pt)[0] = ((uint *)prev)[0];
            ((uint *)pt)[1] = ((uint *)prev)[1];
            ((uint *)pt)[2] = ((uint *)prev)[2];
        } else {
            WalkPlane_Project(this, a1);
        }
    }
    return *(int *)((int)this + 0x34);
}
#endif
