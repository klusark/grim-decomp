#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
static uint64_t rng = 88172645463325252ull;
static uint64_t rnd(void) { rng ^= rng << 13; rng ^= rng >> 7; rng ^= rng << 17; return rng; }
int main(int argc, char **argv)
{
    FILE *f = fopen(argv[1], "rb"); unsigned char code[512]; size_t n = fread(code, 1, sizeof code, f); fclose(f);
    void *p = VirtualAlloc(0, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE); memcpy(p, code, n);
    char *(*orig)(char *, const char *, size_t) = p;
    long bad = 0;
    for (int t = 0; t < 500000; t++) {
        char a[200], b[200], s[80];
        int dl = rnd() % 60, sl = rnd() % 70;
        for (int i = 0; i < dl; i++) a[i] = 1 + rnd() % 126; a[dl] = 0;
        for (int i = 0; i < sl; i++) s[i] = 1 + rnd() % 126; s[sl] = 0;
        memset(a + dl + 1, 'q', sizeof a - dl - 1);
        int off = rnd() % 4;
        char A[210], B[210]; memset(A, 'z', sizeof A); memset(B, 'z', sizeof B);
        memcpy(A + off, a, dl + 1); memcpy(B + off, a, dl + 1);
        size_t cnt = rnd() % 90;
        char *sp = s; char S[100]; memcpy(S + (t & 3), s, sl + 1); sp = S + (t & 3);
        char *r1 = orig(A + off, sp, cnt), *r2 = strncat(B + off, sp, cnt);
        if (r1 - A != r2 - B || memcmp(A, B, sizeof A)) { bad++; if (bad < 4) printf("diff dl=%d sl=%d cnt=%zu\n", dl, sl, cnt); }
    }
    printf("strncat diffs: %ld of 500000\n", bad);
    return 0;
}
