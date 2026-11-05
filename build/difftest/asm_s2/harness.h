/* Case driver of the rasteriser differential tests.  For every case: the family's setup() fills the memory window
 * and the arguments; the state is saved; the ORIGINAL bytes at the function's 1.01 address run; their result (all of
 * .data, the arena, EAX, the x87 control word) is saved; the state is restored and the C runs; both results are
 * compared.  A case where the original faults is skipped (counted); the C faulting where the original does not is a
 * difference. */
#include "rt.h"
typedef void (*setup_fn)(int *args);
typedef struct { const char *name; uint32_t orig; void *mine; setup_fn setup; int cmp_ret; } Fn;
static void *S_init, *S_orig;
/* a test may define harness_fixup() to normalise the C side's memory before the comparison */
void harness_fixup(void) __attribute__((weak));
static int verbose = 1;
static long run_fn(const Fn *f, long n, long *skipped)
{
    long bad = 0, skip = 0;
    if (!S_init) { S_init = malloc(st_size()); S_orig = malloc(st_size()); }
    for (long it = 0; it < n; it++) {
        int a[4] = {0, 0, 0, 0};
        static const unsigned short cws[3] = {0x027f, 0x007f, 0x037f};
        unsigned short cw = cws[rnd() % 3];
        f->setup(a);
        st_save(S_init);
        fpu_set(cw);
        int fo = gcall((void *)(uintptr_t)f->orig, a[0], a[1], a[2], a[3]);
        uint32_t ro = g_ret; unsigned short cwo = fpu_cw();
        if (fo) { skip++; st_load(S_init); continue; }
        st_save(S_orig);
        st_load(S_init);
        fpu_set(cw);
        int fm = gcall(f->mine, a[0], a[1], a[2], a[3]);
        uint32_t rm = g_ret; unsigned short cwm = fpu_cw();
        if (harness_fixup) harness_fixup();
        uint32_t first = 0;
        long d = fm ? -1 : st_cmp_live(S_orig, &first);
        if (d || (f->cmp_ret && ro != rm) || cwo != cwm) {
            if (bad < 4 && verbose) {
                printf("  DIFF %s case %ld: %s words %ld first 0x%08x (orig %08x mine %08x) ret %08x/%08x cw %04x/%04x\n",
                       f->name, it, fm ? "C FAULTED" : "", d, first,
                       d > 0 ? ((uint32_t *)S_orig)[first >= 0x30000000 ? ((DATA_HI - DATA_LO) + first - 0x30000000) / 4 : (first - DATA_LO) / 4] : 0,
                       d > 0 ? *(uint32_t *)(uintptr_t)first : 0, ro, rm, cwo, cwm);
            }
            bad++;
        }
        st_load(S_init);
    }
    *skipped = skip;
    return bad;
}
/* NEG=1 in the environment: negative control, every original is run against the C of the NEXT function of the
 * list (same family and set-up): each line must then report differences. */
static int run_all(const Fn *fns, int nf, long n, const char *only)
{
    long tot = 0;
    int neg = getenv("NEG") != 0;
    for (int i = 0; i < nf; i++) {
        if (only && !strstr(fns[i].name, only)) continue;
        Fn f = fns[i];
        if (neg) f.mine = fns[(i + 1) % nf].mine;
        long sk, b = run_fn(&f, n, &sk);
        printf("%-30s %08x cases %6ld  orig-faults skipped %5ld  differences %ld\n", fns[i].name, fns[i].orig, n - sk, sk, b);
        fflush(stdout);
        tot += b;
    }
    printf("TOTAL differences %ld\n", tot);
    return tot != 0;
}
