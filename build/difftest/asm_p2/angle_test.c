/* Differential test of stdMath_NormalizeAngle (0x47bc20): the original machine code (orig_, sliced by build.sh) against
 * the C linked as stdMath_NormalizeAngle (build/overrides_exe.c, or a generated twin through OVR=).
 *   BASE_ASM=<tools/gen_asm.py output for 0047bc20> build/difftest/asm_p2/build.sh \
 *     build/difftest/asm_p2/angle_test.c OUT.exe stdMath_NormalizeAngle
 * (no commit's asm_funcs.s has the function: names/asm_funcs.json set to ["0047bc20"] for one gen_asm.py run).
 * Inputs: random bit patterns, random angles, and the values a few ULPs around every multiple of 360 up to
 * +-360*4096 (where the result rounds to 360.0f and the compare decides). */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float orig_stdMath_NormalizeAngle(float);
float stdMath_NormalizeAngle(float);
#include <math.h>
/* (Math_Floor is generated C that the original's call reaches too: both sides get the same floor) */
float Math_Floor(float x) { return floorf(x); }

static unsigned bits(float f) { unsigned u; memcpy(&u, &f, 4); return u; }
static float fl(unsigned u) { float f; memcpy(&f, &u, 4); return f; }
static unsigned long long rs = 88172645463325252ULL;
static unsigned rnd(void) { rs ^= rs << 13; rs ^= rs >> 7; rs ^= rs << 17; return (unsigned)rs; }

static long n, diffs, nan_payload;
static void one(float x)
{
    unsigned a = bits(orig_stdMath_NormalizeAngle(x)), b = bits(stdMath_NormalizeAngle(x));
    n++;
    if (a == b)
        return;
    if ((a & 0x7f800000) == 0x7f800000 && (a & 0x7fffff) && (b & 0x7f800000) == 0x7f800000 && (b & 0x7fffff)) {
        nan_payload++;
        return;
    }
    if (diffs++ < 10)
        printf("DIFF x=%08x (%.9g): orig %08x (%.9g) C %08x (%.9g)\n", bits(x), x, a, fl(a), b, fl(b));
}

int main(int argc, char **argv)
{
    long cases = argc > 1 ? atol(argv[1]) : 1000000, i;
    int k, d;
    for (i = 0; i < cases; i++) {
        one(fl(rnd()));
        one((float)((int)rnd() % 100000000) / 1000.0f);
    }
    for (k = -4096; k <= 4096; k++)
        for (d = -16; d <= 16; d++)
            one(fl(bits((float)k * 360.0f) + d));
    printf("stdMath_NormalizeAngle %ld cases, %ld differences, %ld NaN-payload-only\n", n, diffs, nan_payload);
    return diffs != 0;
}
