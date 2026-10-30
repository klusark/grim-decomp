#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef void (*mixAB_t)(void*, int, unsigned, unsigned, int, int);
typedef void (*mixBD_t)(void*, int, unsigned, unsigned, int);
static unsigned rs = 12345;
static unsigned rnd(void) { rs = rs * 1664525u + 1013904223u; return rs >> 8; }
int main(void) {
    HMODULE m[2] = { LoadLibraryA("imuse_a.dll"), LoadLibraryA("imuse_c.dll") };
    if (!m[0] || !m[1]) { printf("load fail\n"); return 1; }
    const char *names[4] = { "Im_MixLoopA", "Im_MixLoopB", "Im_MixLoopC", "Im_MixLoopD" };
    int **accp[2]; void *fn[2][4];
    for (int d = 0; d < 2; d++) {
        accp[d] = (int **)GetProcAddress(m[d], d == 0 ? "DAT_1002df5c" : "PTR_1002df5c");
        for (int k = 0; k < 4; k++) fn[d][k] = GetProcAddress(m[d], names[k]);
        printf("dll %d: acc var %p fns %p %p %p %p\n", d, accp[d], fn[d][0], fn[d][1], fn[d][2], fn[d][3]);
        if (!accp[d]) return 1;
    }
    int bad[4] = {0}, tot[4] = {0};
    for (int iter = 0; iter < 20000; iter++) {
        int k = iter & 3, mode = (iter >> 2) % 4;
        unsigned count = 2 + rnd() % 60; int n;
        switch (mode) { case 0: n = count / 2 + 1; count = 2 * (n - 1) + 2; break; case 1: n = count; break; case 2: n = count / 2; if (n == 0) n = 1; break; default: n = 1 + rnd() % 100; }
        if (mode == 0) { count = 2 * n; }
        if (mode == 2) { count = 2 * n; }
        if (mode == 1) { count = n; }
        int wl = (int)(rnd() % 255), wr = (int)(rnd() % 255), vol = (int)(rnd() % 255), out = rnd() % 16;
        int nsrc = 8 * (count + n) + 64;
        short *src = malloc(nsrc * 2); for (int i = 0; i < nsrc; i++) src[i] = (short)rnd();
        int nacc = 4 * (count + n) + 128;
        int *acc[2];
        for (int d = 0; d < 2; d++) { acc[d] = malloc(nacc * 4); srand(iter); for (int i = 0; i < nacc; i++) acc[d][i] = (int)(i * 7919u + iter); *accp[d] = acc[d]; }
        for (int d = 0; d < 2; d++) {
            if (k == 0 || k == 2) ((mixAB_t)fn[d][k])(src, n, count, out, wl, wr); else ((mixBD_t)fn[d][k])(src, n, count, out, vol);
        }
        tot[k]++;
        if (memcmp(acc[0], acc[1], nacc * 4)) { bad[k]++; if (bad[k] < 3) printf("%s DIFF iter %d mode %d n %d count %u out %d\n", names[k], iter, mode, n, count, out); }
        free(src); free(acc[0]); free(acc[1]);
    }
    for (int k = 0; k < 4; k++) printf("%s: %d calls, %d differ\n", names[k], tot[k], bad[k]);
    return 0;
}
