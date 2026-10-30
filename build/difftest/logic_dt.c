/* Differential test of the game-logic functions that agent P (docs/notes/logic.md) converted from assembly to C by hand:
 * the original machine code (extracted from an all-assembly build by tools/gen_asm_dual.py, symbol <name>__orig) and the C
 * version run on random inputs inside the same process and their outputs are compared bit for bit.
 *
 * Use (not part of the normal build):
 *   python -I tools/gen_asm_dual.py <asm_funcs.s of the all-assembly build> build/obj/dual.s <names...>      (see DT_FUNCS)
 *   cp build/difftest/logic_dt.c build/overrides_logic_dt.c ; make -C build link
 *   GRIM_LOGIC_DT=<result file> build/obj/GRIMFANDANGO.EXE/grimfandango.exe     (the constructor below runs before WinMain, writes
 *   the result file and exits the process)
 * The file name of the extracted assembly is DT_ASM (default build/obj/dual.s next to the source tree root). */
#include "ghidra_types.h"

#ifdef GRIM_EXE
#include "globals.h"
#include "functions.h"
/* (no system headers: their prototypes clash with Ghidra's; the functions come from functions.h / compat.h) */
#define FILE void

#ifndef DT_ASM
#define DT_ASM "C:/Users/Joel/grimP_work/dual.s"
#endif
__asm__(".include \"" DT_ASM "\"\n"
        "\t.att_syntax prefix\n"
        "\t.att_mnemonic\n"
        "\t.text\n");

extern undefined8 __cdecl rdColormap_Build16bitTables__orig(undefined2 *, ushort *, uint, uint, uint, int);
extern void rdroid_BuildMathTables__orig(void);
extern void Math_SinCosTable__orig(float, float *, float *);
extern float10 Math_SinDeg__orig(float);
extern void Palette_FromFloatTable__orig(byte *, byte *, int, double);
extern void __cdecl Pixel_Convert__orig(ushort *, int, ushort *, int, uint);
extern int Pixel_ConvertOne__orig(int, undefined4, int);
extern void Render_BuildColorTable__orig(int, float);
extern void __cdecl Input_SetAxisRange__orig(int, int, int, float);

static unsigned long long rngs = 88172645463325252ull;
static unsigned long long rnd(void)
{
    rngs ^= rngs << 13;
    rngs ^= rngs >> 7;
    rngs ^= rngs << 17;
    return rngs;
}
static float rndf(float lo, float hi)
{
    return lo + (hi - lo) * (float)((rnd() >> 11) & 0xffffff) / 16777216.0f;
}

static FILE *log_;
static int bad_;
static void report(const char *fn, long trials, long bad, const char *first)
{
    fprintf(log_, "%-34s %8ld trials %6ld differences%s%s\n", fn, trials, bad, bad ? "  first: " : "", bad ? first : "");
    bad_ += bad != 0;
}

/* pixel format records: [1] bits per pixel, [2..4] bits per channel, [5..7] channel shifts, [8..10] shifts that drop (16 bit)
 * or restore (24 bit) the low bits */
static void make_fmt(int *f, int kind)
{
    memset(f, 0, 12 * sizeof(int));
    switch (kind) {
    case 0: /* 565 */
        f[1] = 16; f[2] = 5; f[3] = 6; f[4] = 5; f[5] = 11; f[6] = 5; f[7] = 0; f[8] = 3; f[9] = 2; f[10] = 3;
        break;
    case 1: /* 555 */
        f[1] = 16; f[2] = 5; f[3] = 5; f[4] = 5; f[5] = 10; f[6] = 5; f[7] = 0; f[8] = 3; f[9] = 3; f[10] = 3;
        break;
    case 2: /* 24 bit */
        f[1] = 24; f[2] = 8; f[3] = 8; f[4] = 8; f[5] = 16; f[6] = 8; f[7] = 0; f[8] = 0; f[9] = 0; f[10] = 0;
        break;
    default: /* 444 */
        f[1] = 16; f[2] = 4; f[3] = 4; f[4] = 4; f[5] = 8; f[6] = 4; f[7] = 0; f[8] = 4; f[9] = 4; f[10] = 4;
        break;
    }
}

static void run_tests(void)
{
    long i, bad, n;
    char first[160];
    int fmt[12], fmt2[12];

    /* rdColormap_Build16bitTables */
    {
        static ushort ta[64 * 256 + 64], tb[64 * 256 + 64];
        byte pal[768];
        bad = 0;
        first[0] = 0;
        for (n = 0; n < 400; n++) {
            for (i = 0; i < 768; i++)
                pal[i] = (byte)rnd();
            make_fmt(fmt, (int)(rnd() % 4));
            if (fmt[1] != 16)
                make_fmt(fmt, 0);
            memset(ta, 0xa5, sizeof(ta));
            memset(tb, 0xa5, sizeof(tb));
            {
                uint r = (uint)rnd(), g = (uint)rnd(), b = (uint)rnd();
                rdColormap_Build16bitTables__orig(ta, (ushort *)pal, r, g, b, (int)fmt);
                rdColormap_Build16bitTables(tb, (ushort *)pal, r, g, b, (int)fmt);
            }
            if (memcmp(ta, tb, sizeof(ta)) != 0) {
                bad++;
                if (!first[0])
                    sprintf(first, "trial %ld", n);
            }
        }
        report("rdColormap_Build16bitTables", n, bad, first);
    }
    /* rdroid_BuildMathTables: the three tables 0x008fbfc0..0x00900000 */
    {
        static byte sa[0x4040], sb[0x4040];
        byte *base = (byte *)&DAT_008fbfc0;
        memset(base, 0, 0x4040);
        rdroid_BuildMathTables__orig();
        memcpy(sa, base, 0x4040);
        memset(base, 0, 0x4040);
        rdroid_BuildMathTables();
        memcpy(sb, base, 0x4040);
        report("rdroid_BuildMathTables", 1, memcmp(sa, sb, 0x4040) != 0, "tables differ");
    }
    /* Math_SinCosTable / Math_SinDeg */
    {
        long bad1 = 0, bad2 = 0, bad3 = 0;
        char f1[160] = "", f2[160] = "", f3[160] = "";
        for (n = 0; n < 4000000; n++) {
            float a, s1, c1, s2, c2;
            switch (n & 7) {
            case 0: a = rndf(-720.0f, 720.0f); break;
            case 1: a = (float)(int)(rnd() % 1440) - 720.0f; break;
            case 2: a = (float)(rnd() % 8) * 90.0f + rndf(-0.01f, 0.01f); break;
            case 3: a = rndf(0.0f, 360.0f); break;
            case 4: a = 360.0f - rndf(0.0f, 0.05f); break;
            case 5: a = rndf(-5.0f, 5.0f); break;
            case 6: { unsigned int u = (unsigned int)rnd(); memcpy(&a, &u, 4); if (!(a > -1e5f && a < 1e5f)) a = 1.0f; break; }
            default: a = rndf(-360.0f, 360.0f); break;
            }
            s1 = c1 = s2 = c2 = 12345.0f;
            Math_SinCosTable__orig(a, &s1, &c1);
            Math_SinCosTable(a, &s2, &c2);
            if (memcmp(&s1, &s2, 4) != 0 || memcmp(&c1, &c2, 4) != 0) {
                bad1++;
                if (!f1[0])
                    sprintf(f1, "angle %a sin %a/%a cos %a/%a", a, s1, s2, c1, c2);
            }
            {
                float r1 = (float)Math_SinDeg__orig(a), r2 = (float)Math_SinDeg(a);
                if (memcmp(&r1, &r2, 4) != 0) {
                    bad2++;
                    if (!f2[0])
                        sprintf(f2, "angle %a: %a/%a", a, r1, r2);
                }
            }
        }
        (void)bad3; (void)f3;
        report("Math_SinCosTable", n, bad1, f1);
        report("Math_SinDeg", n, bad2, f2);
    }
    /* Palette_FromFloatTable */
    {
        byte in[300], oa[300], ob[300];
        bad = 0;
        first[0] = 0;
        for (n = 0; n < 20000; n++) {
            int cnt = 1 + (int)(rnd() % 100);
            double gamma = (n & 1) ? (double)rndf(0.1f, 4.0f) : (double)(1 + rnd() % 4) / 2.0;
            for (i = 0; i < 300; i++)
                in[i] = (byte)rnd();
            memset(oa, 0x77, sizeof(oa));
            memset(ob, 0x77, sizeof(ob));
            Palette_FromFloatTable__orig(oa, in, cnt, gamma);
            Palette_FromFloatTable(ob, in, cnt, gamma);
            if (memcmp(oa, ob, 300) != 0) {
                bad++;
                if (!first[0])
                    sprintf(first, "gamma %g count %d", gamma, cnt);
            }
        }
        report("Palette_FromFloatTable", n, bad, first);
    }
    /* Pixel_Convert / Pixel_ConvertOne */
    {
        static byte src[4096 * 3], da[4096 * 4], db[4096 * 4];
        bad = 0;
        first[0] = 0;
        for (n = 0; n < 6000; n++) {
            int sk = (int)(rnd() % 4), dk = (int)(rnd() % 4);
            uint cnt = 1 + (uint)(rnd() % 2000);
            uint counter = (uint)rnd();
            make_fmt(fmt, sk);
            make_fmt(fmt2, dk);
            for (i = 0; i < (long)sizeof(src); i++)
                src[i] = (byte)rnd();
            memset(da, 0x33, sizeof(da));
            memset(db, 0x33, sizeof(db));
            UINT_00806c80 = counter;
            Pixel_Convert__orig((ushort *)da, (int)fmt2, (ushort *)src, (int)fmt, cnt);
            {
                uint after = UINT_00806c80;
                UINT_00806c80 = counter;
                Pixel_Convert((ushort *)db, (int)fmt2, (ushort *)src, (int)fmt, cnt);
                if (UINT_00806c80 != after || memcmp(da, db, sizeof(da)) != 0) {
                    bad++;
                    if (!first[0])
                        sprintf(first, "src fmt %d dst fmt %d count %u", sk, dk, cnt);
                }
            }
        }
        report("Pixel_Convert", n, bad, first);
        bad = 0;
        first[0] = 0;
        for (n = 0; n < 200000; n++) {
            int sk = (int)(rnd() % 4), dk = (int)(rnd() % 4);
            uint px = (uint)rnd(), counter = (uint)rnd();
            int r1, r2;
            make_fmt(fmt, sk);
            make_fmt(fmt2, dk);
            UINT_00806c80 = counter;
            r1 = Pixel_ConvertOne__orig((int)fmt2, px, (int)fmt);
            UINT_00806c80 = counter;
            r2 = Pixel_ConvertOne((int)fmt2, px, (int)fmt);
            /* the upper bytes come from the format pointer (a different address in the two calls only if they differ) */
            if (r1 != r2) {
                bad++;
                if (!first[0])
                    sprintf(first, "src %d dst %d px %08x: %08x/%08x", sk, dk, px, r1, r2);
            }
        }
        report("Pixel_ConvertOne", n, bad, first);
    }
    /* Render_BuildColorTable */
    {
        static ushort ta[65536], tb[65536];
        bad = 0;
        first[0] = 0;
        for (n = 0; n < 12; n++) {
            float gamma = (n == 0) ? 1.0f : rndf(0.3f, 3.0f);
            make_fmt(fmt, (int)(n % 2));
            memset(&g_wColorTable, 0, sizeof(ta));
            Render_BuildColorTable__orig((int)fmt, gamma);
            memcpy(ta, &g_wColorTable, sizeof(ta));
            memset(&g_wColorTable, 0, sizeof(ta));
            Render_BuildColorTable((int)fmt, gamma);
            memcpy(tb, &g_wColorTable, sizeof(tb));
            if (memcmp(ta, tb, sizeof(ta)) != 0) {
                bad++;
                if (!first[0])
                    sprintf(first, "gamma %g", gamma);
            }
        }
        report("Render_BuildColorTable", n, bad, first);
    }
    /* Input_SetAxisRange */
    {
        bad = 0;
        first[0] = 0;
        for (n = 0; n < 200000; n++) {
            int axis = (int)(rnd() % 4), mn = (int)(rnd() % 20001) - 10000, mx = mn + (int)(rnd() % 40000);
            float dz = (n & 3) == 0 ? 0.0f : rndf(0.0f, 1.0f);
            byte ra[24], rb[24];
            memset((char *)&UINT_00901500 + axis * 0x18, 0, 24);
            Input_SetAxisRange__orig(axis, mn, mx, dz);
            memcpy(ra, (char *)&UINT_00901500 + axis * 0x18, 24);
            memset((char *)&UINT_00901500 + axis * 0x18, 0, 24);
            Input_SetAxisRange(axis, mn, mx, dz);
            memcpy(rb, (char *)&UINT_00901500 + axis * 0x18, 24);
            if (memcmp(ra, rb, 24) != 0) {
                bad++;
                if (!first[0])
                    sprintf(first, "axis %d range %d..%d dead %g", axis, mn, mx, dz);
            }
        }
        report("Input_SetAxisRange", n, bad, first);
    }
}

__attribute__((constructor)) static void logic_dt_main(void)
{
    const char *out = getenv("GRIM_LOGIC_DT");

    if (out == (const char *)0)
        return;
    log_ = fopen(out, "w");
    if (log_ == (FILE *)0)
        return;
    run_tests();
    fprintf(log_, "%s\n", bad_ ? "SOME FUNCTIONS DIFFER" : "ALL IDENTICAL");
    fclose(log_);
    exit(bad_ != 0);
}
#endif /* GRIM_EXE */
