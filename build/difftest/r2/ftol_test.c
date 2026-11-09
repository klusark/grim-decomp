/* Differential test of _ftol (GRIMFANDANGO.EXE 0x004ac6f0): the original machine code (orig__ftol, sliced from the
 * asm_funcs.s of 85dd22f) against the symbol the rebuilt exe now resolves `_ftol` to: msvcrt.dll's _ftol, linked
 * through the same import library (libmsvcrt.a, `call __ftol` -> `jmp *__imp___ftol`).
 * ABI: the value in ST0 (popped), the result in EDX:EAX; the control word is switched to truncation and back.
 * Compared per case: EAX EDX ECX EBX ESI EDI EBP, ESP balance, the x87 control / status / tag words after the call
 * (fnstenv) and the registers left below ST0.  Inputs: every rounding mode and precision control (with the
 * reserved / infinity-control bits), x87 stack depth 0 / 1 / 7 below the value, and values: random 80-bit patterns
 * (pseudo-denormals, unnormals, pseudo-NaN/inf included), integers and integers +- a few ulps, halves, the int32 /
 * int64 / uint64 bounds +- ulps, +-0, +-inf, quiet / signalling NaNs with payloads, denormals, huge exponents.
 * usage: ftol_test.exe [cases]  (MUT=1: the second function is orig too, a self-check) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

extern void orig__ftol(void);
extern void _ftol(void);             /* asm __ftol: msvcrt.dll through libmsvcrt.a, as the exe links it */
extern void call_ftol(void *fn, const void *x80, unsigned cw, unsigned depth, unsigned *out);

static uint64_t s = 0x9e3779b97f4a7c15ull;
static uint64_t rnd(void) { s ^= s << 13; s ^= s >> 7; s ^= s << 17; return s; }

typedef struct { uint64_t m; uint16_t se; uint16_t pad[3]; } x80;

static x80 from_ld(long double v) { x80 r; memset(&r, 0, sizeof r); memcpy(&r, &v, 10); return r; }
static long double to_ld(x80 x) { long double v = 0; memcpy(&v, &x, 10); return v; }

static x80 nudge(x80 x, int k)   /* k ulps up / down in the 64-bit mantissa (crosses into the next binade crudely) */
{
    long double v = to_ld(x);
    while (k > 0) { v = __builtin_nextafterl(v, __builtin_infl()); k--; }
    while (k < 0) { v = __builtin_nextafterl(v, -__builtin_infl()); k++; }
    return from_ld(v);
}

static x80 gen(uint64_t i)
{
    x80 x;
    memset(&x, 0, sizeof x);
    int sign = (int)(rnd() & 1);
    switch (i % 12) {
    case 0:   /* random bit pattern, anything goes */
        x.m = rnd(); x.se = (uint16_t)rnd();
        break;
    case 1: { /* random value with an exponent around the integer ranges */
        int e = (int)(rnd() % 140) - 70;
        x.m = rnd() | 0x8000000000000000ull; x.se = (uint16_t)((0x3fff + e) | (sign << 15));
        break; }
    case 2: { /* an integer of up to 64 bits, +- a few ulps */
        int bits = (int)(rnd() % 65);
        uint64_t n = bits == 64 ? rnd() : (rnd() & ((1ull << bits) - 1));
        long double v = (long double)n;
        if (sign) v = -v;
        x = nudge(from_ld(v), (int)(rnd() % 7) - 3);
        break; }
    case 3: { /* halves and quarters (ties for the other rounding modes) */
        int64_t n = (int64_t)(rnd() >> (rnd() % 64));
        long double v = (long double)n + ((long double)(rnd() % 4)) * 0.25L;
        x = from_ld(sign ? -v : v);
        break; }
    case 4: { /* the bounds: 2^31, 2^32, 2^63, 2^64 and their neighbours */
        static const int ex[] = {31, 32, 52, 53, 62, 63, 64, 65};
        long double v = __builtin_ldexpl(1.0L, ex[rnd() % 8]);
        x = nudge(from_ld(sign ? -v : v), (int)(rnd() % 9) - 4);
        break; }
    case 5: { /* specials */
        static const long double sp[] = {0.0L, 1.0L, 0.5L, 0.99999999999999999989L, 1e-4950L, 3.6e-4951L};
        int k = (int)(rnd() % 10);
        if (k < 6) x = from_ld(sp[k]);
        else if (k == 6) { x.m = 0x8000000000000000ull; x.se = 0x7fff; }               /* inf */
        else if (k == 7) { x.m = 0xc000000000000000ull | (rnd() >> 2); x.se = 0x7fff; } /* qNaN */
        else if (k == 8) { x.m = 0x8000000000000000ull | (rnd() >> 2) | 1; x.se = 0x7fff; } /* sNaN */
        else { x.m = rnd() >> 1; x.se = 0; }                                             /* denormal */
        x.se |= (uint16_t)(sign << 15);
        break; }
    case 6: { /* a double / float that went through memory (what the game's code converts) */
        double d; uint64_t b = rnd(); memcpy(&d, &b, 8);
        if (rnd() & 1) { float f; uint32_t fb = (uint32_t)b; memcpy(&f, &fb, 4); d = f; }
        x = from_ld((long double)d);
        break; }
    case 7: { /* small magnitudes around +-1 */
        long double v = (long double)(int64_t)(rnd() % 2001 - 1000) / (long double)(1 + rnd() % 1000);
        x = from_ld(v);
        break; }
    case 8: { /* huge exponents */
        x.m = rnd() | 0x8000000000000000ull; x.se = (uint16_t)((0x3fff + 64 + rnd() % 16000) | (sign << 15));
        if ((x.se & 0x7fff) >= 0x7fff) x.se = (uint16_t)(0x7ffe | (sign << 15));
        break; }
    case 9: { /* unnormals / pseudo forms: integer bit clear with a non-zero exponent */
        x.m = rnd() & 0x7fffffffffffffffull; x.se = (uint16_t)rnd();
        break; }
    default: { /* int32 range values */
        long double v = (long double)(int32_t)rnd() + (long double)(rnd() % 1000) / 1000.0L;
        x = from_ld(v);
        break; }
    }
    return x;
}

int main(int argc, char **argv)
{
    setvbuf(stdout, NULL, _IONBF, 0);   /* a crash (the expected result of some mutations) must not eat the report */
    long n = argc > 1 ? atol(argv[1]) : 1000000;
    int self = getenv("MUT") && atoi(getenv("MUT")) == 1;
    void *f1 = (void *)orig__ftol, *f2 = self ? (void *)orig__ftol : (void *)_ftol;
    static const unsigned depths[] = {0, 1, 7};
    long diffs = 0, classes[12] = {0}, nan_ie = 0, trunc_checked = 0;
    for (long i = 0; i < n; i++) {
        x80 x = gen((uint64_t)i);
        unsigned rc = (unsigned)(rnd() & 3), pc = (unsigned)(rnd() & 3);
        unsigned cw = 0x3f | (pc << 8) | (rc << 10) | (unsigned)(rnd() & 0x1040);   /* all masked, + IC / reserved bit */
        unsigned depth = depths[rnd() % 3];
        unsigned a[40], b[40];
        memset(a, 0xcc, sizeof a); memset(b, 0xcc, sizeof b);
        call_ftol(f1, &x, cw, depth, a);
        call_ftol(f2, &x, cw, depth, b);
        /* compare the registers, ESP balance, CW / SW / TW (the instruction / operand pointers of fnstenv name the code
         * addresses, which differ by construction), and the stack left below */
        int bad = memcmp(a, b, 8 * 4) || (a[8] & 0xffff) != (b[8] & 0xffff) || (a[9] & 0xffff) != (b[9] & 0xffff)
                  || (a[10] & 0xffff) != (b[10] & 0xffff) || memcmp(a + 15, b + 15, depth * 12);
        /* sanity of the reference itself: a finite value inside int64 truncates toward zero */
        long double v = to_ld(x);
        if (v == v && __builtin_fabsl(v) < 9.2e18L) {
            long long want = (long long)v;   /* gcc: truncation */
            long long got = (long long)(((uint64_t)a[1] << 32) | a[0]);
            trunc_checked++;
            if (want != got) { bad = 1; if (diffs < 5) printf("reference does not truncate: %Lg -> %lld\n", v, got); }
        }
        if ((a[9] & 1) && a[0] == 0 && a[1] == 0x80000000u) nan_ie++;
        if (a[6] != 0 || b[6] != 0) bad = 1;   /* ESP must balance */
        if (a[2] != 0x44444444 || a[3] != 0x11111111 || a[4] != 0x22222222 || a[5] != 0x33333333 || a[7] != 0x77777777) bad = 1;
        classes[i % 12]++;
        if (bad) {
            if (diffs < 10)
                printf("DIFF case %ld: x=%04x:%016llx cw=%04x depth=%u  orig eax=%08x edx=%08x cw=%04x sw=%04x tw=%04x | "
                       "new eax=%08x edx=%08x cw=%04x sw=%04x tw=%04x\n", i, x.se, (unsigned long long)x.m, cw, depth,
                       a[0], a[1], a[8] & 0xffff, a[9] & 0xffff, a[10] & 0xffff, b[0], b[1], b[8] & 0xffff, b[9] & 0xffff,
                       b[10] & 0xffff);
            diffs++;
        }
    }
    printf("_ftol: %ld cases (%s), %ld differences; %ld finite in-range values checked for truncation, %ld invalid "
           "conversions (IE set, result 0x8000000000000000)\n", n, self ? "orig vs orig" : "orig vs msvcrt.dll _ftol",
           diffs, trunc_checked, nan_ie);
    return diffs != 0;
}
