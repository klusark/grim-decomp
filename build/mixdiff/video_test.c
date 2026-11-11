/* Differential test of the pixel conversion code of the Smush video module (Video_*, VideoBitmap_*): original machine code
 * against build/overrides_mixer_video.c.  Random pixel data, counts (including the 0 / odd ones the do-while loops of the
 * original handle in their own way), strides and formats; the formats come from bmp_bitmap_Alloc itself, which is tested
 * against the original too.  ONLY=<n> selects a group. */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fx.h"

typedef struct VB { unsigned char *data; int w, h, bpp, bits, pitch, f18, f1c, type, bR, bG, bB, sR, sG, sB, lR, lG, lB, bA, sA, lA; } VB;

extern void orig_FUN_004cfdf0(unsigned char *, unsigned char *, int, int, unsigned char *), Video_ExpandIndexed8(unsigned char *, unsigned char *, int, int, unsigned char *);
extern void orig_FUN_004cfea0(unsigned char *, unsigned short *, int, int, unsigned char *), Video_ExpandIndexed16(unsigned char *, unsigned short *, int, int, unsigned char *);
extern void orig_FUN_004cff60(unsigned short *, unsigned *, unsigned), Video_Rgba32To555(unsigned short *, unsigned *, unsigned);
extern void orig_FUN_004cffe0(unsigned *, unsigned short *, unsigned), Video_555ToRgba32(unsigned *, unsigned short *, unsigned);
extern void orig_FUN_004d0070(unsigned short *, unsigned *, unsigned), Video_Rgba32To565(unsigned short *, unsigned *, unsigned);
extern void orig_FUN_004d00f0(unsigned *, unsigned short *, unsigned), Video_565ToRgba32(unsigned *, unsigned short *, unsigned);
extern void orig_FUN_004d0180(unsigned short *, unsigned *, unsigned), Video_Rgba32To565Alt(unsigned short *, unsigned *, unsigned);
extern void orig_FUN_004d01f0(unsigned *, unsigned short *, unsigned), Video_565AltToRgba32(unsigned *, unsigned short *, unsigned);
extern void orig_FUN_004d0260(unsigned char *, unsigned char *, int, unsigned, int, unsigned, unsigned, int, unsigned, unsigned);
extern void Video_CopyRect(unsigned char *, unsigned char *, int, unsigned, int, unsigned, unsigned, int, unsigned, unsigned);
extern void orig_FUN_004cfdb0(unsigned char *, unsigned char *, int, unsigned, int, unsigned, unsigned, int, unsigned, unsigned);
extern void Video_CopyRectDstFirst(unsigned char *, unsigned char *, int, unsigned, int, unsigned, unsigned, int, unsigned, unsigned);
extern int orig_FUN_004cf010(void *, void *, int, unsigned char *, unsigned char *), gra_ConvertToLecColor(void *, void *, int, unsigned char *, unsigned char *);
extern int orig_FUN_004cf520(void *, void *, int, int, unsigned char *), gra_ConvertFromLecColor(void *, void *, int, int, unsigned char *);
extern int orig_FUN_004cedc0(unsigned char *, void *, int, unsigned char *, unsigned char *, void *, unsigned char *);
extern int gra_ConvertCopy(unsigned char *, void *, int, unsigned char *, unsigned char *, void *, unsigned char *);
extern int orig_FUN_004ce3e0(void *, int, int, int), bmp_bitmap_Alloc(void *, int, int, int);

enum { T_ALLOC = 1, T_DISPFMT, T_LOG };
static void *th_log;
int msc_error_SaveString(void) { return 0; }                    /* replaced below by the recorder */
void FUN_004c3df0(void *d, void *s, unsigned n) { memcpy(d, s, n); }
void Insane_MemCopyCdecl(void *d, void *s, unsigned n) { memcpy(d, s, n); }

static unsigned char pool[1 << 20];
static unsigned pool_used;
static int alloc_fail;
static int alloc_effect(int tag, unsigned *args)
{
    unsigned n = (args[0] + 15) & ~15u;
    if (alloc_fail || pool_used + n > sizeof pool) return 0;
    pool_used += n;
    return (int)(intptr_t)(pool + pool_used - n);
}
static VB dispfmt;
static int dispfmt_effect(int tag, unsigned *args) { return (int)(intptr_t)&dispfmt; }

static int dbg1, dbg2, dbg3;
static unsigned R(unsigned n) { return (unsigned)(fx_rnd() % n); }

#define BUF 0x4400
static unsigned char srcb[BUF * 4], dstb[BUF * 4];
static unsigned char table[65536 * 4 + 16];
static unsigned char hdrA[16][0x60], hdrB[16][0x60];

int main(int argc, char **argv)
{
    long n = argc > 1 ? atol(argv[1]) : 100000;
    int neg = argc > 2;
    int only = getenv("ONLY") ? atoi(getenv("ONLY")) : -1;
    int i;
    int svc_mem[2], svc_disp[4];
    VB fmts[13];            /* descriptors made by bmp_bitmap_Alloc (mine) */
    unsigned char *tmpdata;

    setvbuf(stdout, 0, _IONBF, 0);
    svc_mem[0] = (int)(intptr_t)fx_thunk(T_ALLOC, 3, 0); fx_effect(T_ALLOC, alloc_effect); fx_strmask(T_ALLOC, 2);
    svc_disp[1] = (int)(intptr_t)fx_thunk(T_DISPFMT, 0, 0); fx_effect(T_DISPFMT, dispfmt_effect);
    th_log = fx_thunk(T_LOG, 4, 0); fx_strmask(T_LOG, 3);
    FXU32(0x8da890) = (unsigned)(uintptr_t)svc_mem;
    (void)tmpdata;

    /* descriptors for every format, made by the original */
    for (i = 0; i < 13; i++) {
        VB *p = 0;
        pool_used = 0; alloc_fail = 0;
        if (orig_FUN_004ce3e0(&p, 10, 4, i) != 0) { printf("create %d failed\n", i); return 2; }
        memcpy(&fmts[i], p, sizeof(VB));
    }
    memset(&dispfmt, 0, sizeof dispfmt);
    dispfmt.bpp = 2; dispfmt.bits = 16; dispfmt.type = 1; dispfmt.bR = 5; dispfmt.bG = 6; dispfmt.bB = 5; dispfmt.sR = 11; dispfmt.sG = 5;
    dispfmt.lR = 3; dispfmt.lG = 2; dispfmt.lB = 3;

    fx_region(srcb, sizeof srcb); fx_region(dstb, sizeof dstb);
    fx_region(FXDATA(0x9272a0), 0x2800);          /* RGBA scratch rows */
    fx_region(FXDATA(0x8da8a0), 4);
    fx_region(pool, 4096);

    for (long it = 0; it < n; it++) {
        int f = only >= 0 ? only : (int)(it % 15); if (f == 1) f = 2;     /* (group 1 = the broken 16 bit expander is not tested) */
        int ra = 0, rb = 0;
        int count = R(8) == 0 ? (int)R(3) : (int)R(60);
        unsigned long long cseed = fx_rnd();
        (void)cseed;

        for (i = 0; i < BUF * 4; i++) { srcb[i] = (unsigned char)fx_rnd(); dstb[i] = (unsigned char)fx_rnd(); }
        for (i = 0; i < 65536 * 4; i += 8) *(unsigned long long *)(table + i) = fx_rnd();
        memset(FXDATA(0x9272a0), 0xcc, 0x2800);
        FXU32(0x8da8a0) = R(10);
        pool_used = 0; alloc_fail = 0;
        memset(pool, 0xee, 4096);
        fx_clear_queues(); fx_reset();
        fx_save();

#define RUN(CALL_O, CALL_M) do { \
            fx_reset(); ra = (CALL_O); fx_snap_a(); \
            fx_restore(); fx_reset(); rb = (CALL_M) + neg; } while (0)
        switch (f) {
        case 0: { int bpp = R(7); unsigned char *s = srcb + 5 + R(3), *d = dstb + R(4);
            if (bpp == 3 && count > 4) count = 4;
            fx_save();
            RUN((orig_FUN_004cfdf0(d, s, count, bpp, table), 0), (Video_ExpandIndexed8(d, s, count, bpp, table), 0)); break; }
        case 1: { int bpp = R(7); unsigned char *s = srcb + 6 + R(3) * 2, *d = dstb + R(4);
            if (bpp == 3 && count > 3) count = 3;
            dbg1 = bpp; dbg2 = count; dbg3 = (int)((uintptr_t)s & 3);
            fx_save();
            RUN((orig_FUN_004cfea0(d, (unsigned short *)s, count, bpp, table), 0), (Video_ExpandIndexed16(d, (unsigned short *)s, count, bpp, table), 0)); break; }
        case 2: { unsigned char *s = srcb + R(4), *d = dstb + R(4);
            fx_save();
            switch (R(6)) {
            case 0: RUN((orig_FUN_004cff60((unsigned short *)d, (unsigned *)s, count), 0), (Video_Rgba32To555((unsigned short *)d, (unsigned *)s, count), 0)); break;
            case 1: RUN((orig_FUN_004d0070((unsigned short *)d, (unsigned *)s, count), 0), (Video_Rgba32To565((unsigned short *)d, (unsigned *)s, count), 0)); break;
            case 2: RUN((orig_FUN_004d0180((unsigned short *)d, (unsigned *)s, count), 0), (Video_Rgba32To565Alt((unsigned short *)d, (unsigned *)s, count), 0)); break;
            case 3: RUN((orig_FUN_004cffe0((unsigned *)d, (unsigned short *)s, count), 0), (Video_555ToRgba32((unsigned *)d, (unsigned short *)s, count), 0)); break;
            case 4: RUN((orig_FUN_004d00f0((unsigned *)d, (unsigned short *)s, count), 0), (Video_565ToRgba32((unsigned *)d, (unsigned short *)s, count), 0)); break;
            default: RUN((orig_FUN_004d01f0((unsigned *)d, (unsigned short *)s, count), 0), (Video_565AltToRgba32((unsigned *)d, (unsigned short *)s, count), 0)); break;
            }
            break; }
        case 3: case 4: { /* CopyRect and the wrapper */
            unsigned sp = 4 + R(300), dp = 4 + R(300), w = R(5) ? R(sp < dp ? sp : dp) : (R(2) ? 0 : 4 * R(30));
            int rows = R(10) ? 1 + (int)R(8) : (int)R(2);
            int sx = R(40), dx = R(40);
            unsigned sy = R(6) ? R(60) : R(70000), dy = R(6) ? R(60) : R(70000);
            if (w > sp) w = sp; if (w > dp) w = dp;
            sp = (sp & 0xffff); dp = (dp & 0xffff);
            if ((sy & 0xffff) * sp + (sy & 0xffff0000) + sx + sp * rows + w > BUF * 4 - 64) sy = R(20);
            if ((dy & 0xffff) * dp + (dy & 0xffff0000) + dx + dp * rows + w > BUF * 4 - 64) dy = R(20);
            fx_save();
            if (f == 3) RUN((orig_FUN_004d0260(srcb, dstb, sx, sy, dx, dy, w, rows, sp, dp), 0), (Video_CopyRect(srcb, dstb, sx, sy, dx, dy, w, rows, sp, dp), 0));
            else RUN((orig_FUN_004cfdb0(dstb, srcb, dx, dy, sx, sy, w, rows, dp, sp), 0), (Video_CopyRectDstFirst(dstb, srcb, dx, dy, sx, sy, w, rows, dp, sp), 0));
            break; }
        case 5: case 6: case 7: case 8: case 9: { /* ToRgba / FromRgba / ConvertPixels */
            VB *sf = &fmts[R(13)], *df = &fmts[R(13)];
            unsigned char *pal = R(3) ? 0 : table;
            dbg1 = (int)(sf - fmts); dbg2 = count; dbg3 = pal != 0;
            if (sf->type == 0 && R(2)) { sf->bR = (int)(intptr_t)table; }
            fx_save();
            if (f == 5) { int so = (int)R(2); RUN(orig_FUN_004cf010(srcb + so, sf, count, pal, dstb), gra_ConvertToLecColor(srcb + so, sf, count, pal, dstb)); }
            else if (f == 6) RUN(orig_FUN_004cf520(dstb + 3, df, count, 0, srcb), gra_ConvertFromLecColor(dstb + 3, df, count, 0, srcb));
            else {
                unsigned char *tab = R(3) ? 0 : table;
                int cnt = R(4) ? count : (int)R(2000);
                /* not testable: the 16 bit expander (FUN_004cfea0) takes its arguments from the wrong stack slots (doubled prologue) and the
                   3 byte per pixel expanders read a growing index */
                if (tab && sf->bpp == 2 && df->type != 0) tab = 0;
                if (tab && sf->type == 0 && sf->bpp == 1 && df->bpp == 3 && cnt > 4) cnt = 4;
                RUN(orig_FUN_004cedc0(srcb + 1, sf, cnt, pal, dstb + 2, df, tab), gra_ConvertCopy(srcb + 1, sf, cnt, pal, dstb + 2, df, tab));
            }
            break; }
        default: { /* Create */
            int fmt = (int)R(16) - 2, w = 1 + R(40), h = 1 + R(20);
            VB *pa = 0, *pb = 0;
            int fail = R(8) == 0;
            FXU32(0x8da89c) = R(4) ? (unsigned)(uintptr_t)svc_disp : 0;
            fx_save();
            alloc_fail = fail; pool_used = 0; fx_reset(); ra = orig_FUN_004ce3e0(&pa, w, h, fmt); fx_snap_a();
            if (ra == 0) memcpy(hdrA[0], pa, 0x60);
            fx_restore(); alloc_fail = fail; pool_used = 0; fx_reset(); rb = bmp_bitmap_Alloc(&pb, w, h, fmt) + neg;
            if (ra == 0 && rb == neg) {
                /* headers are compared apart from the data pointers (pool addresses are the same: bump allocator) */
                if (memcmp(hdrA[0], pb, 0x60)) fx_fail("bitmap header", it);
            }
            if (ra == rb && (ra == 0)) break;
            break; }
        }
        fx_cases++;
        if (ra != rb) fx_fail("return value", it * 100 + f);
        else if (fx_cmp_a() || fx_cmp_log()) { if (fx_fails < 3) printf("  f=%d dbg %d %d %d" "%c", f, dbg1, dbg2, dbg3, 10); fx_fail("state/calls", it * 100 + f); }
    }
    printf("video cases %ld  differences %ld\n", fx_cases, fx_fails);
    return fx_fails != 0;
}
