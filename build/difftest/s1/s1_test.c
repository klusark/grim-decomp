/* Differential test of build/overrides_s1_chore.c (FUN_10004e50, FUN_10005090) against the original machine code of
 * CHORE.DLL (slice.py; agent s1).  usage: s1_test.exe [cases] [seed]
 *
 * Each case makes a random table state (size 0..64 records in steps of 8, an in-use count from 0 to size + 7, random
 * free flags, random record bytes) and calls both versions on identical copies; the realloc of the service table is a
 * mock that copies the old block into a new one whose added part is random bytes.  Mode "free garbage": the added
 * records' free flag (+0x38 / +0x10) is random but non-zero, the case where the original's result is defined: return
 * value, size, count and the whole table must be identical.  Mode "zero garbage": the added part is zeros (the bytes
 * the original leaves undefined read as "in use"): the test counts the cases where the original leaves a record between
 * the old size and the count marked in use with stale contents (the crash) and checks the override never does, and that
 * everything else (the returned record, size, count, the records below the old size) is still the original's. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned undefined4;
typedef unsigned char undefined;
undefined4 DAT_100143a8;
undefined DAT_100143ac[4], DAT_100143b0[4], DAT_100143c4[4];
undefined4 DAT_100143b4, DAT_100143c8;
int DAT_100143cc;
char s_C__grimsrc_libs_chore_Costume_c_1001020c[] = "C:\\grimsrc\\libs\\chore\\Costume.c";

int orig_FUN_10004e50(void);
int orig_FUN_10005090(void);
int FUN_10004e50(void);
int FUN_10005090(void);

static unsigned rng;
static unsigned rnd(void) { rng = rng * 1103515245u + 12345u; return rng >> 8; }

static int garbage_mode;     /* 0: added records random with a non-zero free flag; 1: added part zero */
static unsigned garbage_seed;
static int rec_size, flag_off;
static void *blocks[64];
static int nblocks;

static void *mock_realloc(void *old, int size, char *file, int line)
{
    unsigned char *p = malloc(size + 4);
    int oldsize = old ? *((int *)old - 1) : 0, i;
    unsigned g = garbage_seed;
    (void)file; (void)line;
    *(int *)p = size;
    p += 4;
    for (i = 0; i < size; i++) {
        g = g * 1103515245u + 12345u;
        p[i] = garbage_mode ? 0 : (unsigned char)(g >> 16);
    }
    if (!garbage_mode)
        for (i = 0; i + rec_size <= size; i += rec_size)
            *(int *)(p + i + flag_off) = 1;   /* (the value the original's growth loop writes) */
    if (old)
        memcpy(p, old, oldsize < size ? oldsize : size);
    blocks[nblocks++] = p - 4;
    return p;
}

static void *service[16];

struct state { int size, used; unsigned char *table; int bytes; };

static void setup(int which, struct state *s)
{
    unsigned char *t = s->size ? mock_realloc(0, s->size * rec_size, 0, 0) : 0;
    if (t)
        memcpy(t, s->table, s->size * rec_size);
    if (which == 0) {
        *(int *)DAT_100143b0 = s->size; *(int *)DAT_100143ac = s->used; DAT_100143b4 = (undefined4)t;
    } else {
        DAT_100143c8 = s->size; *(int *)DAT_100143c4 = s->used; DAT_100143cc = (int)t;
    }
}

static void get(int which, int *size, int *used, unsigned char **t)
{
    if (which == 0) {
        *size = *(int *)DAT_100143b0; *used = *(int *)DAT_100143ac; *t = (unsigned char *)DAT_100143b4;
    } else {
        *size = DAT_100143c8; *used = *(int *)DAT_100143c4; *t = (unsigned char *)DAT_100143cc;
    }
}

int main(int argc, char **argv)
{
    long cases = argc > 1 ? atol(argv[1]) : 1000000, c;
    long diffs = 0, stale = 0, stale_mine = 0, grown = 0;
    rng = argc > 2 ? strtoul(argv[2], 0, 0) : 1;
    service[0x28 / 4] = (void *)mock_realloc;
    DAT_100143a8 = (undefined4)service;
    for (c = 0; c < cases; c++) {
        int which = c & 1, i, r0, r1, s0, s1, u0, u1, n;
        unsigned char *t0, *t1, *buf;
        struct state st;
        rec_size = which == 0 ? 0x3c : 0x14;
        flag_off = which == 0 ? 0x38 : 0x10;
        garbage_mode = (c >> 1) & 1;
        garbage_seed = rnd();
        st.size = (rnd() % 9) * 8;
        st.used = rnd() % (st.size + 8);
        n = st.size * rec_size;
        buf = malloc(n + 1);
        for (i = 0; i < n; i++)
            buf[i] = rnd();
        for (i = 0; i < st.size; i++)   /* free flags: mostly in use, some free (any non-zero value) */
            *(int *)(buf + i * rec_size + flag_off) = (rnd() % 4 == 0) ? (int)(rnd() % 3 + 1) : 0;
        st.table = buf;
        nblocks = 0;
        setup(which, &st);
        r0 = which == 0 ? orig_FUN_10004e50() : orig_FUN_10005090();
        get(which, &s0, &u0, &t0);
        setup(which, &st);
        r1 = which == 0 ? FUN_10004e50() : FUN_10005090();
        get(which, &s1, &u1, &t1);
        if (s0 != st.size)
            grown++;
        if (r0 != r1 || s0 != s1 || u0 != u1) {
            diffs++;
        } else if (garbage_mode == 0) {
            if (memcmp(t0, t1, s0 * rec_size) != 0)
                diffs++;
        } else {
            /* below the old size identical; the records the original leaves undefined: in use there, free here */
            if (memcmp(t0, t1, st.size * rec_size) != 0)
                diffs++;
            for (i = st.size; i < s0; i++) {
                int f0 = *(int *)(t0 + i * rec_size + flag_off), f1 = *(int *)(t1 + i * rec_size + flag_off);
                if (i == r0) {
                    if (f0 != 0 || f1 != 0)
                        diffs++;
                } else if (i < st.used) {
                    stale += f0 == 0;
                    stale_mine += f1 == 0;
                } else if (f0 != f1) {
                    diffs++;
                }
            }
        }
        if (diffs && diffs < 5 && (r0 != r1 || s0 != s1 || u0 != u1))
            printf("case %ld (%s, mode %d, size %d used %d): orig %d/%d/%d mine %d/%d/%d\n", c, which ? "instances" : "costumes",
                   garbage_mode, st.size, st.used, r0, s0, u0, r1, s1, u1);
        for (i = 0; i < nblocks; i++)
            free(blocks[i]);
        free(buf);
    }
    printf("%ld cases, %ld grew the table, %ld differences; undefined records left in use: original %ld, override %ld\n",
           cases, grown, diffs, stale, stale_mine);
    return diffs != 0 || stale_mine != 0;
}
