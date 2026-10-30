/* Differential test of Blocky16_DecodeFrame (build/overrides_mixer_codec.c) against the original machine code.  Every function
 * the frame decoder calls is a recorder (fx_thunk) that logs its arguments; the buffer allocation does what the real one
 * does to the decoder's globals (three buffers, three bitmap descriptors).  Random headers (method, sequence, swap mode, size),
 * random start states (buffer rotation, bitmaps present or not, output callback or not, display format flags).
 * Compared: return value, the buffers, the descriptors, the decoder globals, the sequence of calls. */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fx.h"

extern int orig_FUN_004ccd00(void *, unsigned *, int, int, int, unsigned char *, unsigned char), Blocky16_DecodeFrame(void *, unsigned *, int, int, int, unsigned char *, unsigned char);

enum { T_FREE = 1, T_ALLOC, T_OFFS, T_EXPAND, T_HALF16, T_HALF8, T_BLIT, T_FILL, T_RLEDEC, T_RLEBEGIN, T_DUMP, T_BLOCKS, T_CB };
static void *th[16];

#define ARENA 0x6000
static unsigned char arena[ARENA];           /* three 0x2000 buffers */
static int bitmaps[3][8];                    /* [0] pixels [1] width [2] height */
static unsigned char hdrbuf[0x230 + 8192];
static unsigned rle_counter;
static unsigned long long rle_calls;
static int dstdummy[8];

static unsigned R(unsigned n) { return (unsigned)(fx_rnd() % n); }

#define CALL0(t) ((int (*)(void))th[t])()
#define CALLN(t, T, ...) ((int (*)T)th[t])(__VA_ARGS__)

int FUN_004cc590(void) { return CALL0(T_FREE); }
int Blocky16_FreeBuffers(void) { return CALL0(T_FREE); }
int FUN_004cc410(int a, int b, int c) { return CALLN(T_ALLOC, (int, int, int), a, b, c); }
int Blocky16_AllocBuffers(int a, int b, int c) { return CALLN(T_ALLOC, (int, int, int), a, b, c); }
int FUN_004cc6a0(int a) { return CALLN(T_OFFS, (int), a); }
int Blocky16_BuildPixelOffsets(int a) { return CALLN(T_OFFS, (int), a); }
int FUN_004cd1e0(void *a) { return CALLN(T_EXPAND, (void *), a); }
int Blocky16_BuildExpandTable(void *a) { return CALLN(T_EXPAND, (void *), a); }
int FUN_004cd300(void *a, void *b, int c, int d) { return CALLN(T_HALF16, (void *, void *, int, int), a, b, c, d); }
int Blocky16_DecodeHalfRows16(void *a, void *b, int c, int d) { return CALLN(T_HALF16, (void *, void *, int, int), a, b, c, d); }
int FUN_004cd450(void *a, void *b, int c, int d, int e) { return CALLN(T_HALF8, (void *, void *, int, int, int), a, b, c, d, e); }
int Blocky16_DecodeHalfRows8(void *a, void *b, int c, int d, int e) { return CALLN(T_HALF8, (void *, void *, int, int, int), a, b, c, d, e); }
int FUN_004cea30(void *a, void *b, int c, int d, void *e, void *f, void *g) { return CALLN(T_BLIT, (void *, void *, int, int, void *, void *, void *), a, b, c, d, e, f, g); }
int Video_BlitConvert(void *a, void *b, int c, int d, void *e, void *f, void *g) { return CALLN(T_BLIT, (void *, void *, int, int, void *, void *, void *), a, b, c, d, e, f, g); }
int FUN_004cec40(void *a, void *b, int c, void *d) { return CALLN(T_FILL, (void *, void *, int, void *), a, b, c, d); }
int Video_FillPixels(void *a, void *b, int c, void *d) { return CALLN(T_FILL, (void *, void *, int, void *), a, b, c, d); }
int FUN_004d5e70(void *a, void *b, int c) { return CALLN(T_RLEDEC, (void *, void *, int), a, b, c); }
int Rle_Decode(void *a, void *b, int c) { return CALLN(T_RLEDEC, (void *, void *, int), a, b, c); }
int FUN_004d5eb0(void *a) { rle_counter = 0; return CALLN(T_RLEBEGIN, (void *), a); }
int Rle_Begin(void *a) { rle_counter = 0; return CALLN(T_RLEBEGIN, (void *), a); }
unsigned __attribute__((fastcall)) FUN_004d5ed0(unsigned x) { rle_calls++; return (rle_counter++ * 2654435761u) >> 13; }
unsigned __attribute__((fastcall)) Rle_NextByte(unsigned x) { rle_calls++; return (rle_counter++ * 2654435761u) >> 13; }
int Mem_DumpLog(void) { return CALL0(T_DUMP); }
void FUN_004c3df0(void *d, void *s, unsigned n) { memcpy(d, s, n); }
void Insane_MemCopyCdecl(void *d, void *s, unsigned n) { memcpy(d, s, n); }
void blocks_stub(void *a, void *b, int c, int d, int e, void *f, void *g, int h, int i, void *j, void *k, void *l) __asm__("@FUN_004cd550@56");
void blocks_stub(void *a, void *b, int c, int d, int e, void *f, void *g, int h, int i, void *j, void *k, void *l)
{
    ((int (*)(void *, void *, int, int, int, void *, void *, int, int, void *, void *, void *))th[T_BLOCKS])(a, b, c, d, e, f, g, h, i, j, k, l);
}
void Blocky16_DecodeBlocks(void *a, void *b, int c, int d, int e, void *f, void *g, int h, int i, void *j, void *k, void *l)
{
    ((int (*)(void *, void *, int, int, int, void *, void *, int, int, void *, void *, void *))th[T_BLOCKS])(a, b, c, d, e, f, g, h, i, j, k, l);
}

/* what the real buffer allocation leaves behind */
static int alloc_effect(int tag, unsigned *args)
{
    int i;
    for (i = 0; i < 3; i++) {
        bitmaps[i][0] = (int)(intptr_t)(arena + i * 0x2000);
        bitmaps[i][1] = (int)args[0];
        bitmaps[i][2] = (int)args[1];
    }
    FXU32(0x8da528) = (unsigned)(uintptr_t)bitmaps[0];
    FXU32(0x8da52c) = (unsigned)(uintptr_t)bitmaps[1];
    FXU32(0x8da530) = (unsigned)(uintptr_t)bitmaps[2];
    FXU32(0x8da50c) = (unsigned)(uintptr_t)arena;
    FXU32(0x91f080) = (unsigned)(uintptr_t)(arena + 0x2000);
    FXU32(0x906c74) = (unsigned)(uintptr_t)(arena + 0x4000);
    FXU32(0x8da510) = 0x1234;
    FXU32(0x8da520) = args[2];
    FXU32(0x8da534) = args[0] * args[1];
    return 0;
}

int main(int argc, char **argv)
{
    long n = argc > 1 ? atol(argv[1]) : 100000;
    long it;
    int i;

    setvbuf(stdout, 0, _IONBF, 0);
    for (i = 1; i <= T_CB; i++) {
        int nargs[] = { 0, 0, 3, 1, 1, 4, 5, 7, 4, 3, 1, 0, 12, 7 };
        th[i] = fx_thunk(i, nargs[i], 0);
    }
    fx_effect(T_ALLOC, alloc_effect);
    fx_region(arena, sizeof arena);
    fx_region(bitmaps, sizeof bitmaps);
    fx_region(FXDATA(0x8da508), 0x38);
    fx_region(FXDATA(0x906c74), 4);
    fx_region(FXDATA(0x91f080), 4);
    fx_region(FXDATA(0x4f39e8), 4);
    fx_region(FXDATA(0x8d6f1c), 4);
    fx_region(&rle_calls, 8);

    for (it = 0; it < n; it++) {
        int ra, rb, na, nb, ta[32], tb[32];
        int W = 8 + (int)R(33), H = 1 + (int)R(32), AH = (H + 7) & ~7;
        int perm[3] = { 0, 1, 2 };
        int lastSeq = R(3) ? (int)R(5) - 1 : (int)R(200);
        int seq = R(3) ? (R(4) ? lastSeq + 1 : 0) : (int)R(200);
        int method = (int)R(10), swap = (int)R(3);
        unsigned char flags = (unsigned char)(R(2) ? 4 : R(8));
        void *dst = R(5) ? (void *)dstdummy : 0;
        int palette = (int)fx_rnd();
        unsigned long long k;

        for (i = 2; i > 0; i--) { int j = (int)R(i + 1), t = perm[i]; perm[i] = perm[j]; perm[j] = t; }
        for (k = 0; k < sizeof hdrbuf; k++) hdrbuf[k] = (unsigned char)fx_rnd();
        *(short *)(hdrbuf + 8) = (short)W;
        *(short *)(hdrbuf + 0xc) = (short)H;
        *(short *)(hdrbuf + 0x10) = (short)seq;
        hdrbuf[0x12] = (unsigned char)method;
        hdrbuf[0x13] = (unsigned char)swap;
        *(int *)(hdrbuf + 0x24) = (int)R(500);
        *(short *)(hdrbuf + 0x228) = (short)(R(3) ? 0 : 8 + R(25));
        for (k = 0; k < sizeof arena; k += 8) *(unsigned long long *)(arena + k) = fx_rnd();
        for (i = 0; i < 3; i++) {
            int ok = R(5) != 0;                  /* descriptor of the right size? */
            bitmaps[i][0] = (int)(intptr_t)(arena + perm[i] * 0x2000 * 0 + i * 0x2000);
            bitmaps[i][1] = ok ? W : (int)R(50);
            bitmaps[i][2] = ok ? AH : (int)R(50);
            if (i > 0) { bitmaps[i][1] = bitmaps[0][1]; bitmaps[i][2] = bitmaps[0][2]; }
        }
        FXU32(0x8da528) = R(8) ? (unsigned)(uintptr_t)bitmaps[0] : 0;
        FXU32(0x8da52c) = (unsigned)(uintptr_t)bitmaps[1];
        FXU32(0x8da530) = (unsigned)(uintptr_t)bitmaps[2];
        FXU32(0x8da50c) = (unsigned)(uintptr_t)(arena + perm[0] * 0x2000);
        FXU32(0x91f080) = (unsigned)(uintptr_t)(arena + perm[1] * 0x2000);
        FXU32(0x906c74) = (unsigned)(uintptr_t)(arena + perm[2] * 0x2000);
        FXU32(0x8da538) = R(4) == 0 ? 0 : (R(5) == 0 ? (unsigned)(uintptr_t)(arena + 0x10) : (unsigned)(uintptr_t)(arena + R(3) * 0x2000));
        FXU32(0x8da508) = R(2) ? (unsigned)(uintptr_t)th[T_CB] : 0;
        FXU32(0x8da510) = (unsigned)fx_rnd();
        FXU32(0x8da514) = R(2) ? 0 : (unsigned)fx_rnd();
        FXU32(0x8da518) = R(2) ? 0 : (unsigned)fx_rnd();
        FXU32(0x8da51c) = (unsigned)fx_rnd();
        FXU32(0x8da520) = (unsigned)fx_rnd();
        FXU32(0x8da534) = (unsigned)fx_rnd();
        FXI32(0x4f39e8) = lastSeq;
        FXU32(0x8d6f1c) = (unsigned)fx_rnd();
        fx_clear_queues(); fx_reset();
        fx_ret(T_CB, (int)fx_rnd());
        fx_ret(T_ALLOC, 0);
        rle_calls = 0; rle_counter = 0;
        fx_save();
        fx_reset(); rle_calls = 0; rle_counter = 0;
        ra = orig_FUN_004ccd00(dst, (unsigned *)(arena + 0x20), 3, 4, palette, hdrbuf, flags); fx_snap_a(); na = fx_nlog; for (i = 0; i < na && i < 32; i++) ta[i] = fx_log[i].tag;
        fx_restore(); fx_reset(); rle_calls = 0; rle_counter = 0;
        rb = Blocky16_DecodeFrame(dst, (unsigned *)(arena + 0x20), 3, 4, palette, hdrbuf, flags); nb = fx_nlog; for (i = 0; i < nb && i < 32; i++) tb[i] = fx_log[i].tag;
        fx_cases++;
        if (ra != rb) { if (fx_fails < 3) printf("  ret %d %d method %d seq %d last %d swap %d\n", ra, rb, method, seq, lastSeq, swap); fx_fail("return value", it); }
        else if (fx_cmp_a() || fx_cmp_log()) { if (fx_fails < 3) printf("  method %d seq %d last %d swap %d\n", method, seq, lastSeq, swap); { int q; printf("  orig calls:"); for (q = 0; q < na && q < 32; q++) printf(" %d", ta[q]); printf("\n  mine calls:"); for (q = 0; q < nb && q < 32; q++) printf(" %d", tb[q]); printf("\n"); } fx_fail("state/calls", it); }
    }
    printf("frame cases %ld  differences %ld\n", fx_cases, fx_fails);
    return fx_fails != 0;
}
