/* differential test: CHORE.DLL's own copies of qsort / bsearch / strncpy / strrchr / _stricmp / strchr / memmove vs msvcrt.dll.
   gcc -m32 -O1 difftest_chore.c -o difftest_chore.exe ; difftest_chore.exe <baseline chore.dll> */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef int (*cmp_t)(const void *, const void *);
typedef void (*qsort_t)(void *, size_t, size_t, cmp_t);
typedef void *(*bsearch_t)(const void *, const void *, size_t, size_t, cmp_t);
typedef struct { int key; int idx; } rec;
static int cmp_key(const void *a, const void *b) { return ((const rec *)a)->key - ((const rec *)b)->key; }
static uint64_t rng = 88172645463325252ull;
static uint64_t rnd(void) { rng ^= rng << 13; rng ^= rng >> 7; rng ^= rng << 17; return rng; }

int main(int argc, char **argv)
{
    HMODULE ch = LoadLibraryA(argv[1]);
    HMODULE crt = LoadLibraryA("msvcrt.dll");
    qsort_t oq = (qsort_t)GetProcAddress(ch, "FUN_10005ba0"), hq = (qsort_t)GetProcAddress(crt, "qsort");
    bsearch_t ob = (bsearch_t)GetProcAddress(ch, "FUN_10005de0"), hb = (bsearch_t)GetProcAddress(crt, "bsearch");
    char *(*ostrncpy)(char *, const char *, size_t) = (void *)GetProcAddress(ch, "FUN_100055a0"), *(*hstrncpy)(char *, const char *, size_t) = (void *)GetProcAddress(crt, "strncpy");
    char *(*ostrrchr)(const char *, int) = (void *)GetProcAddress(ch, "FUN_100056a0"), *(*hstrrchr)(const char *, int) = (void *)GetProcAddress(crt, "strrchr");
    char *(*ostrchr)(const char *, int) = (void *)GetProcAddress(ch, "FUN_10005e90"), *(*hstrchr)(const char *, int) = (void *)GetProcAddress(crt, "strchr");
    int (*ostricmp)(const char *, const char *) = (void *)GetProcAddress(ch, "FUN_10005740"), (*hstricmp)(const char *, const char *) = (void *)GetProcAddress(crt, "_stricmp");
    void *(*omemmove)(void *, const void *, size_t) = (void *)GetProcAddress(ch, "FUN_10005860"), *(*hmemmove)(void *, const void *, size_t) = (void *)GetProcAddress(crt, "memmove");
    printf("q %p %p b %p %p strncpy %p strrchr %p strchr %p stricmp %p memmove %p\n", oq, hq, ob, hb, ostrncpy, ostrrchr, ostrchr, ostricmp, omemmove);
    long bad[8] = {0};
    static rec A[4096], B[4096];
    for (int t = 0; t < 20000; t++) {
        int n = rnd() % 2000, range = 1 + rnd() % (t % 3 == 0 ? 4 : t % 3 == 1 ? 50 : 100000);
        for (int i = 0; i < n; i++) { A[i].key = rnd() % range; A[i].idx = i; B[i] = A[i]; }
        oq(A, n, sizeof(rec), cmp_key); hq(B, n, sizeof(rec), cmp_key);
        if (memcmp(A, B, n * sizeof(rec))) { bad[0]++; if (bad[0] < 3) printf("qsort mismatch n=%d range=%d\n", n, range); }
        /* bsearch on the sorted array with a key (duplicates possible) */
        for (int k = 0; k < 5 && n; k++) {
            rec key = { (int)(rnd() % (range + 2)) - 1, 0 };
            rec *p = ob(&key, A, n, sizeof(rec), cmp_key), *q = hb(&key, A, n, sizeof(rec), cmp_key);
            if (p != q) { bad[1]++; if (bad[1] < 3) printf("bsearch mismatch n=%d key=%d: %p vs %p\n", n, key.key, (void *)p, (void *)q); }
        }
    }
    for (int t = 0; t < 200000; t++) {
        char s[64], d1[80], d2[80], u[64];
        int len = rnd() % 40;
        for (int i = 0; i < len; i++) s[i] = (char)(1 + rnd() % 126);
        s[len] = 0;
        int c = (int)(rnd() % 128);
        char *a = ostrchr(s, c), *b = hstrchr(s, c);
        if ((a == 0) != (b == 0) || (a && a - s != b - s)) bad[2]++;
        a = ostrrchr(s, c); b = hstrrchr(s, c);
        if ((a == 0) != (b == 0) || (a && a - s != b - s)) bad[3]++;
        size_t n = rnd() % 60;
        memset(d1, 'x', sizeof d1); memset(d2, 'x', sizeof d2);
        ostrncpy(d1 + (t & 3), s, n); hstrncpy(d2 + (t & 3), s, n);
        if (memcmp(d1, d2, sizeof d1)) bad[4]++;
        for (int i = 0; i < len; i++) u[i] = (char)(rnd() % 3 ? s[i] ^ 0x20 * (rnd() % 2) : 1 + rnd() % 126);
        u[len] = 0;
        int r1 = ostricmp(s, u), r2 = hstricmp(s, u);
        if ((r1 > 0) != (r2 > 0) || (r1 < 0) != (r2 < 0)) bad[5]++;
        else if (r1 != r2) bad[6]++;   /* same sign, different magnitude */
        /* memmove with overlap */
        unsigned char m1[300], m2[300];
        for (int i = 0; i < 300; i++) m1[i] = m2[i] = (unsigned char)rnd();
        int so = rnd() % 100, dof = rnd() % 100; size_t ln = rnd() % 150;
        omemmove(m1 + dof, m1 + so, ln); hmemmove(m2 + dof, m2 + so, ln);
        if (memcmp(m1, m2, 300)) bad[7]++;
    }
    printf("qsort diff %ld, bsearch diff %ld, strchr diff %ld, strrchr diff %ld, strncpy diff %ld, stricmp sign diff %ld (magnitude only: %ld), memmove diff %ld\n",
           bad[0], bad[1], bad[2], bad[3], bad[4], bad[5], bad[6], bad[7]);
    return 0;
}
