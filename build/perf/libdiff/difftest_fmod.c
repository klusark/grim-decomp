#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
static double ci2(void *f, double x, double y)   /* ST1 = x, ST0 = y -> ST0 */
{
    double r;
    __asm__ volatile("fldl %1\n\tfldl %2\n\tcall *%3\n\tfstpl %0\n\t" : "=m"(r) : "m"(x), "m"(y), "r"(f) : "eax", "ecx", "edx", "memory", "st", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)", "cc");
    return r;
}
static uint64_t rng = 88172645463325252ull;
static uint64_t rnd(void) { rng ^= rng << 13; rng ^= rng >> 7; rng ^= rng << 17; return rng; }
static uint64_t bits(double d) { uint64_t u; memcpy(&u, &d, 8); return u; }
int main(int argc, char **argv)
{
    setvbuf(stdout, 0, _IONBF, 0);
    HMODULE lua = LoadLibraryA(argv[1]), crt = LoadLibraryA("msvcrt.dll");
    void *o = GetProcAddress(lua, "FUN_10012104"), *h = GetProcAddress(crt, "_CIfmod");
    printf("%p %p\n", o, h);
    long bad = 0, n = 3000000;
    for (long i = 0; i < n; i++) {
        double x, y;
        switch (i % 4) {
        case 0: { uint64_t u = rnd(); memcpy(&x, &u, 8); u = rnd(); memcpy(&y, &u, 8); break; }
        case 1: { float f; uint32_t u = (uint32_t)rnd(); memcpy(&f, &u, 4); x = f; u = (uint32_t)rnd(); memcpy(&f, &u, 4); y = f; break; }
        case 2: x = ((int64_t)rnd() % 2000000) / 64.0; y = ((int)(rnd() % 4000) - 2000) / 16.0; break;
        default: x = (double)(int)(rnd() % 100000) / 7.0; y = 0.3 * (1 + rnd() % 20); break;
        }
        double a = ci2(o, x, y), b = ci2(h, x, y);
        int same = bits(a) == bits(b) || (isnan(a) && isnan(b));
        if (!same) { bad++; if (bad < 6) printf("fmod(%a,%a): orig %a host %a  c-lib %a\n", x, y, a, b, fmod(x, y)); }
    }
    printf("fmod n=%ld diffs=%ld\n", n, bad);
    return 0;
}
