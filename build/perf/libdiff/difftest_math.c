/* differential test: the original (assembled/decompiled) LUA.DLL math helpers vs msvcrt.dll
   gcc -m32 -O1 difftest_math.c -o difftest_math.exe ; difftest_math.exe <path to the baseline lua.dll> */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

typedef double (*d_d)(double);
typedef long long (*ftol_t)(void);
static double ci_call(void *f, double x)   /* ST0 -> ST0, MSVC _CI* convention */
{
    double r;
    __asm__ volatile("fldl %1\n\tcall *%2\n\tfstpl %0\n\t" : "=m"(r) : "m"(x), "r"(f) : "eax", "ecx", "edx", "memory", "st", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)", "cc");
    return r;
}
static long long ftol_call(void *f, double x)   /* ST0 -> EDX:EAX */
{
    unsigned lo, hi;
    __asm__ volatile("fldl %2\n\tcall *%3\n\t" : "=a"(lo), "=d"(hi) : "m"(x), "r"(f) : "ecx", "memory", "st", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)", "cc");
    return ((long long)hi << 32) | lo;
}
static uint64_t bits(double d) { uint64_t u; memcpy(&u, &d, 8); return u; }
static uint64_t rng = 88172645463325252ull;
static uint64_t rnd(void) { rng ^= rng << 13; rng ^= rng >> 7; rng ^= rng << 17; return rng; }
static int same(double a, double b) { return bits(a) == bits(b) || (isnan(a) && isnan(b)); }

int main(int argc, char **argv)
{
    HMODULE lua = LoadLibraryA(argv[1]);
    HMODULE crt = LoadLibraryA("msvcrt.dll");
    if (!lua || !crt) { printf("load failed\n"); return 2; }
    d_d ofloor = (d_d)GetProcAddress(lua, "_floor"), oceil = (d_d)GetProcAddress(lua, "_ceil");
    void *ofl = GetProcAddress(lua, "floor"), *ocl = GetProcAddress(lua, "ceil");
    if (!ofloor) ofloor = (d_d)ofl;
    if (!oceil) oceil = (d_d)ocl;
    void *oasin = GetProcAddress(lua, "_CIsqrt"), *oacos = GetProcAddress(lua, "_FUN_10011e20");
    void *oftol = GetProcAddress(lua, "_ftol");
    d_d hfloor = (d_d)GetProcAddress(crt, "floor"), hceil = (d_d)GetProcAddress(crt, "ceil");
    void *hasin = GetProcAddress(crt, "_CIasin"), *hacos = GetProcAddress(crt, "_CIacos"), *hftol = GetProcAddress(crt, "_ftol");
    printf("orig floor %p ceil %p asin %p acos %p ftol %p | host %p %p %p %p %p\n", ofloor, oceil, oasin, oacos, oftol, hfloor, hceil, hasin, hacos, hftol);
    long bad[8] = {0}, n = 4000000;
    int shown[8] = {0};
    for (long i = 0; i < n; i++) {
        double x;
        switch (i % 5) {
        case 0: { uint64_t u = rnd(); memcpy(&x, &u, 8); break; }                       /* any double */
        case 1: { float f; uint32_t u = (uint32_t)rnd(); memcpy(&f, &u, 4); x = f; break; }  /* any float */
        case 2: x = ((double)(int64_t)rnd()) / 4294967296.0; break;                      /* +-2^31 range with fractions */
        case 3: x = ((int)(rnd() % 2001) - 1000) / 8.0; break;                          /* multiples of 1/8 */
        default: x = ((double)(rnd() % 2000001) / 1000000.0) - 1.0; break;                /* [-1,1] */
        }
        double a, b;
        a = ofloor(x); b = hceil(x); if (!same(a, b)) { bad[0]++; if (shown[0]++ < 3) printf("floor(%a): orig %a host %a\n", x, a, b); }
        a = oceil(x); b = hfloor(x); if (!same(a, b)) { bad[1]++; if (shown[1]++ < 3) printf("ceil(%a): orig %a host %a\n", x, a, b); }
        if (oasin) { a = ci_call(oasin, x); b = ci_call(hasin, x);
            if (!same(a, b)) { bad[2]++; if ((float)a != (float)b && !(isnan(a) && isnan(b))) bad[3]++; if (shown[2]++ < 3) printf("asin(%a): orig %a host %a\n", x, a, b); } }
        if (oacos) { a = ci_call(oacos, x); b = ci_call(hacos, x);
            if (!same(a, b)) { bad[4]++; if ((float)a != (float)b && !(isnan(a) && isnan(b))) bad[5]++; if (shown[4]++ < 3) printf("acos(%a): orig %a host %a\n", x, a, b); } }
        if (oftol && fabs(x) < 1e18) { long long p = ftol_call(oftol, x), q = ftol_call(hftol, x); if (p != q) { bad[6]++; if (shown[6]++ < 3) printf("ftol(%a): orig %lld host %lld\n", x, p, q); } }
    }
    printf("n=%ld  floor diff %ld  ceil diff %ld  asin diff %ld (as float32: %ld)  acos diff %ld (as float32: %ld)  ftol diff %ld\n", n, bad[0], bad[1], bad[2], bad[3], bad[4], bad[5], bad[6]);
    return 0;
}
