/* Task 2 of agent q6: cycles per call of the span fillers of build/overrides_asm_o2.c (the C as compiled) and of their
 * original machine code (orig_*), on the same random spans (16 bpp, z-buffered, 1..200 pixels, half of the z-buffer
 * in front), the state restored before every call.  Built by o2span.sh with TIME=1.
 * usage: o2span_time.exe [calls per function] */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

extern char sect_data[] __asm__("_sect_data");
#define G(a) ((void *)(sect_data + ((a) - 0x4dd000)))
#define GU(a) (*(unsigned *)G(a))

typedef void (*SpanFn)(unsigned *, unsigned *);
#define DECL(n) extern void orig_rdRaster_Span16_TexLitZw##n(unsigned *, unsigned *), rdRaster_Span16_TexLitZw##n(unsigned *, unsigned *);
DECL() DECL(_2) DECL(_3) DECL(_4) DECL(_5) DECL(_6) DECL(_7) DECL(_8) DECL(_15) DECL(_16) DECL(_17) DECL(_18) DECL(_19) DECL(_20) DECL(_21) DECL(_22) DECL(_24) DECL(_25) DECL(_26) DECL(_27) DECL(_28) DECL(_29) DECL(_30)
#define P(n) {orig_rdRaster_Span16_TexLitZw##n, rdRaster_Span16_TexLitZw##n, #n}
static struct { SpanFn o, m; const char *n; } fns[] = {P(), P(_2), P(_3), P(_4), P(_5), P(_6), P(_7), P(_8), P(_15), P(_16), P(_17), P(_18), P(_19), P(_20), P(_21), P(_22), P(_24), P(_25), P(_26), P(_27), P(_28), P(_29), P(_30)};
#define NFN ((int)(sizeof fns / sizeof fns[0]))

static uint64_t seed = 88172645463325252ull;
static unsigned rnd(void) { seed ^= seed << 13; seed ^= seed >> 7; seed ^= seed << 17; return (unsigned)(seed >> 11); }
static inline uint64_t rdtsc(void) { uint32_t lo, hi; __asm__ volatile("rdtsc" : "=a"(lo), "=d"(hi)); return ((uint64_t)hi << 32) | lo; }

#define W 640
static unsigned short color[W + 64], zbuf[W + 64], zsave[W + 64];
static unsigned char tex[0x10000 + 0x100];
static unsigned short palbuf[0x4400], *pal = palbuf + 0x200;
static int surf_c[0x20], surf_z[0x20], canvas_inner[8], canvas[4];
static unsigned left[0x11], right[0x11];

int main(int argc, char **argv)
{
    long n = argc > 1 ? atol(argv[1]) : 20000;
    double tot_o = 0, tot_m = 0;
    for (int k = 0; k < 2064; k++) {
        ((int *)G(0x8fbfc0))[k] = k ? 0x10000 / k : 0;
        ((float *)G(0x8fe000))[k] = k ? 1.0f / k : 0;
    }
    for (int k = 0; k < (int)sizeof tex; k++) tex[k] = (unsigned char)rnd();
    for (int k = 0; k < 0x4400; k++) palbuf[k] = (unsigned short)rnd();
    surf_c[0x18 / 4] = W * 2; surf_c[0x5c / 4] = (int)(uintptr_t)color;
    surf_z[0x18 / 4] = W * 2; surf_z[0x5c / 4] = (int)(uintptr_t)zbuf;
    canvas_inner[1] = (int)(uintptr_t)surf_c; canvas_inner[4] = (int)(uintptr_t)surf_z;
    canvas[1] = (int)(uintptr_t)canvas_inner;
    GU(0x7f0fc8) = (unsigned)(uintptr_t)canvas;
    GU(0x8dde7c) = (unsigned)(uintptr_t)tex;
    GU(0x8dde5c) = (unsigned)(uintptr_t)pal;
    *(unsigned short *)G(0x900526) = 0x077f; *(unsigned short *)G(0x900524) = 0x027f;
    for (int f = 0; f < NFN; f++) {
        uint64_t to = 0, tm = 0;
        for (long i = 0; i < n; i++) {
            int x0 = (int)(rnd() % (300 << 16)), len = (int)(rnd() % (200 << 16)) + 0x10000;
            float z0 = (rnd() % 1000) / 1000.0f, z1 = (rnd() % 1000) / 1000.0f;
            memset(left, 0, sizeof left); memset(right, 0, sizeof right);
            left[0] = x0; right[0] = x0 + len;
            memcpy(&left[4], &z0, 4); memcpy(&right[4], &z1, 4);
            left[10] = rnd() & 0x3ffffff; right[10] = rnd() & 0x3ffffff;
            left[12] = rnd() & 0x3ffffff; right[12] = rnd() & 0x3ffffff;
            left[14] = 0x10000 + rnd() % 0x3d0000; right[14] = 0x10000 + rnd() % 0x3d0000;
            GU(0x8dde54) = rnd() % 3; GU(0x8dde78) = 0x8000; GU(0x8dde50) = 0x8000;
            GU(0x8dde58) = 0xff00; GU(0x8dde8c) = 8; GU(0x8dde48) = 0xff0000;
            for (int k = 0; k < W; k++) zsave[k] = (unsigned short)(rnd() & 1 ? rnd() : 0);
            memcpy(zbuf, zsave, sizeof zbuf);
            uint64_t t0 = rdtsc();
            fns[f].o(left, right);
            uint64_t t1 = rdtsc();
            memcpy(zbuf, zsave, sizeof zbuf);
            uint64_t t2 = rdtsc();
            fns[f].m(left, right);
            uint64_t t3 = rdtsc();
            to += t1 - t0; tm += t3 - t2;
        }
        printf("Span16_TexLitZw%-4s original %6.0f  C %6.0f cycles/call\n", fns[f].n, (double)to / n, (double)tm / n);
        tot_o += (double)to / n; tot_m += (double)tm / n;
    }
    printf("mean: original %.0f  C %.0f cycles/call\n", tot_o / NFN, tot_m / NFN);
    return 0;
}
