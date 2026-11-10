/* Differential test of the Blocky16 codec code (build/overrides_mixer_codec.c): split mask builder, option reader and the
 * block decoders (through Blocky16_DecodeBlocks, which runs the 8x8, 4x4 and 2x2 decoders on random opcode streams).  The
 * original machine code against the C version, same start state; compared: return value, written memory.
 * ONLY=<n> selects a group: 0 split masks, 1 option reader, 2 block decoders. */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fx.h"

extern void orig_FUN_004cc7d0(int), fob_block_maketiles(int);
extern int orig_FUN_004cc250(int, ...), Blocky16_SetOption(int, ...);
extern void orig_4cd550(unsigned char *, unsigned char *, int, int, int, short *, short *, int, int, unsigned char *, unsigned char *, unsigned short *) __asm__("@orig_FUN_004cd550@56");
extern void Blocky16_DecodeBlocks(unsigned char *, unsigned char *, int, int, int, short *, short *, int, int, unsigned char *, unsigned char *, unsigned short *);

/* only referenced by Blocky16_DecodeFrame, which is not part of this test */
unsigned __attribute__((fastcall)) msc_rle_DecompressGetbyte(unsigned x) { return x; }

static unsigned R(unsigned n) { return (unsigned)(fx_rnd() % n); }

#define ARENA 0x40000
static unsigned char arena[ARENA];
static unsigned char stream[32768];
static short motion[255];
static short colors[4];
static unsigned short pairColors[260];

static void fill_splits(void)
{
    unsigned char *s8 = FXDATA(0x906c80), *s4 = FXDATA(0x91f0a0);
    int i, k;

    for (i = 0; i < 256; i++) {
        unsigned short *p = (unsigned short *)(s8 + i * 0x184);
        for (k = 0; k < 128; k++) p[k] = (unsigned short)R(456);
        for (k = 0; k < 0x184 - 256; k++) s8[i * 0x184 + 256 + k] = (unsigned char)fx_rnd();
        s8[i * 0x184 + 0x180] = (unsigned char)(R(8) ? 1 + R(63) : R(2) ? 0 : 64);
        s8[i * 0x184 + 0x181] = (unsigned char)(R(8) ? 1 + R(63) : R(2) ? 0 : 64);
        p = (unsigned short *)(s4 + i * 0x80);
        for (k = 0; k < 32; k++) p[k] = (unsigned short)R(456);
        for (k = 0x40; k < 0x80; k++) s4[i * 0x80 + k] = (unsigned char)fx_rnd();
        s4[i * 0x80 + 0x60] = (unsigned char)(R(8) ? 1 + R(15) : R(2) ? 0 : 16);
        s4[i * 0x80 + 0x61] = (unsigned char)(R(8) ? 1 + R(15) : R(2) ? 0 : 16);
    }
}

int main(int argc, char **argv)
{
    long n = argc > 1 ? atol(argv[1]) : 100000;
    int neg = argc > 2;
    int only = getenv("ONLY") ? atoi(getenv("ONLY")) : -1;
    long it;
    int i;

    setvbuf(stdout, 0, _IONBF, 0);
    fx_region(arena, sizeof arena);
    fx_region(FXDATA(0x906c48), 0x2c);              /* the decoder state */
    fx_region(FXDATA(0x8da508), 4);
    fx_region(FXDATA(0x4f38e8), 0x100);             /* edge point tables */
    fx_region(FXDATA(0x906c80), 0x18400);           /* 8x8 split masks */
    fx_region(FXDATA(0x91f0a0), 0x8000);            /* 4x4 split masks */
    fill_splits();

    for (it = 0; it < n; it++) {
        int f = only >= 0 ? only : (int)(it % 4 == 3 ? 1 : (it % 4 == 2 ? 0 : 2));
        int ra = 0, rb = 0;

        fx_clear_queues(); fx_reset();
        switch (f) {
        case 0: {   /* split masks: random edge points (in range), sometimes the real ones */
            int size = R(2) ? 8 : 4;
            if (it > 8) {
                for (i = 0; i < 16; i++) {
                    FXI32(0x4f38e8 + i * 4) = R(size == 4 ? 4 : 8);
                    FXI32(0x4f3928 + i * 4) = R(size == 4 ? 4 : 8);
                    FXI32(0x4f3968 + i * 4) = R(8);
                    FXI32(0x4f39a8 + i * 4) = R(8);
                    if (R(3) == 0) {   /* points on the edges */
                        int e = size == 4 ? 3 : 7;
                        switch (R(4)) {
                        case 0: FXI32(0x4f3928 + i * 4) = FXI32(0x4f39a8 + i * 4) = 0; break;
                        case 1: FXI32(0x4f38e8 + i * 4) = FXI32(0x4f3968 + i * 4) = 0; break;
                        case 2: FXI32(0x4f3928 + i * 4) = FXI32(0x4f39a8 + i * 4) = e; break;
                        default: FXI32(0x4f38e8 + i * 4) = FXI32(0x4f3968 + i * 4) = e; break;
                        }
                    }
                }
            }
            for (i = 0; i < 0x18400; i++) FXDATA(0x906c80)[i] = (unsigned char)fx_rnd();
            fx_save();
            fx_reset(); orig_FUN_004cc7d0(size); fx_snap_a();
            fx_restore(); fx_reset(); fob_block_maketiles(size);
            break; }
        case 1: {   /* option reader */
            unsigned v1 = (unsigned)fx_rnd(), v2 = (unsigned)fx_rnd();
            int k1 = (int)R(4), k2 = (int)R(4);
            FXU32(0x8da508) = (unsigned)fx_rnd();
            fx_save();
            fx_reset(); ra = orig_FUN_004cc250(k1, v1, k2, v2, 0, 0); fx_snap_a();
            fx_restore(); fx_reset(); rb = Blocky16_SetOption(k1, v1, k2, v2, 0, 0) + neg;
            break; }
        default: {  /* block decoders */
            int width = 1 + (int)R(64), height = 1 + (int)R(40);
            int prev = (int)R(8000) - 4000, prev2 = (int)R(8000) - 4000;
            unsigned char *dst = arena + 0x20000 + R(4) * 2;
            int pitch = width * 2;
            (void)pitch;
            for (i = 0; i < (int)sizeof stream; i++) {
                unsigned char b = (unsigned char)fx_rnd();
                stream[i] = (R(5) < 2) ? (unsigned char)(0xf6 + R(10)) : b;
            }
            if (R(3) == 0) for (i = 0; i < 40; i++) stream[i * 3] = (unsigned char)(0xf5 + (R(3) == 0 ? 0 : R(2)));
            for (i = 0; i < 255; i++) motion[i] = (short)((int)R(R(2) ? 400 : 6000) - 200);
            for (i = 0; i < 4; i++) colors[i] = (short)fx_rnd();
            for (i = 0; i < 260; i++) pairColors[i] = (unsigned short)fx_rnd();
            for (i = 0; i < ARENA; i += 8) *(unsigned long long *)(arena + i) = fx_rnd();
            if (R(50) == 0) fill_splits();
            fx_save();
            fx_reset(); orig_4cd550(dst, stream, prev, prev2, width, motion, colors, height, 0, FXDATA(0x91f0a0), FXDATA(0x906c80), pairColors); fx_snap_a();
            fx_restore(); fx_reset(); Blocky16_DecodeBlocks(dst, stream, prev, prev2, width, motion, colors, height, 0, FXDATA(0x91f0a0), FXDATA(0x906c80), pairColors);
            break; }
        }
        fx_cases++;
        if (ra != rb) fx_fail("return value", it * 100 + f);
        else if (fx_cmp_a() || fx_cmp_log()) fx_fail("state/calls", it * 100 + f);
    }
    printf("codec cases %ld  differences %ld\n", fx_cases, fx_fails);
    return fx_fails != 0;
}
