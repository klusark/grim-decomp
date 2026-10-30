#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
static uint64_t rng = 88172645463325252ull;
static uint64_t rnd(void) { rng ^= rng << 13; rng ^= rng >> 7; rng ^= rng << 17; return rng; }
int main(int argc, char **argv)
{
    setvbuf(stdout, 0, _IONBF, 0);
    HMODULE im = LoadLibraryA(argv[1]);
    HMODULE crt = LoadLibraryA("msvcrt.dll");
    printf("im %p\n", im);
    char *(*ostrncpy)(char *, const char *, size_t) = (void *)GetProcAddress(im, "Im_MemCopy"), *(*hstrncpy)(char *, const char *, size_t) = (void *)GetProcAddress(crt, "strncpy");
    char *(*ostrchr)(const char *, int) = (void *)GetProcAddress(im, "Im_StrChr"), *(*hstrchr)(const char *, int) = (void *)GetProcAddress(crt, "strrchr");
    int (*ostricmp)(const char *, const char *) = (void *)GetProcAddress(im, "Im_StrCmpNoCase"), (*hstricmp)(const char *, const char *) = (void *)GetProcAddress(crt, "_stricmp");
    printf("%p %p %p\n", ostrncpy, ostrchr, ostricmp);
    long bad[4] = {0};
    for (int t = 0; t < 300000; t++) {
        char s[64], d1[80], d2[80], u[64];
        int len = rnd() % 40;
        for (int i = 0; i < len; i++) s[i] = (char)(1 + rnd() % 126);
        s[len] = 0;
        int c = (int)(rnd() % 128);
        char *a = ostrchr(s, c), *b = hstrchr(s, c);
        if ((a == 0) != (b == 0) || (a && a - s != b - s)) bad[0]++;
        size_t n = rnd() % 60;
        memset(d1, 'x', sizeof d1); memset(d2, 'x', sizeof d2);
        ostrncpy(d1 + (t & 3), s, n); hstrncpy(d2 + (t & 3), s, n);
        if (memcmp(d1, d2, sizeof d1)) bad[1]++;
        for (int i = 0; i < len; i++) u[i] = (char)(rnd() % 3 ? s[i] ^ 0x20 * (rnd() % 2) : 1 + rnd() % 126);
        u[len] = 0;
        int r1 = ostricmp(s, u), r2 = hstricmp(s, u);
        if ((r1 > 0) != (r2 > 0) || (r1 < 0) != (r2 < 0)) bad[2]++;
    }
    printf("strchr diff %ld, strncpy diff %ld, stricmp sign diff %ld\n", bad[0], bad[1], bad[2]);
    return 0;
}
