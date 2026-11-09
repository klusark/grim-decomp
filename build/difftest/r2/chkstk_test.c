/* Differential test of __chkstk / _alloca_probe (GRIMFANDANGO.EXE 0x004addf0, FUN_004addf0): the original machine code
 * (orig_FUN_004addf0, sliced from the asm_funcs.s of 85dd22f) against what the rebuilt exe's symbol is now:
 * _FUN_004addf0 of build/overrides_r2.c (compiled like build/link.py compiles overrides), a jump to libgcc's ___chkstk.
 * ABI: EAX = bytes to allocate; returns with ESP = (ESP before the call) - EAX, every page in between touched from the
 * top down, ECX kept.
 *   part 1: every register after the call, ESP, and the memory around the old and new stack top (pattern-filled
 *           before the call: the probes must not change it, only the return slot is written), on a private
 *           committed stack (the TIB stack limits are pointed at it), sizes around every page multiple and random;
 *   part 2: the probe sequence, traced with the trap flag (a vectored handler records ECX at each probe instruction);
 *   part 3: guard-page growth on real thread stacks (a fresh thread per size, 16 MiB reserved, the default commit):
 *           the allocated block is then written from its low end, which faults if a page was skipped.
 * Expected differences, not counted: EAX after the call (the original leaves the return address, libgcc the old
 * ESP; EAX is scratch for every __chkstk caller), the original probes the lowest page twice when EAX is a multiple
 * of 4 KiB (compared after merging repeated probes of one address), and libgcc's probe is a store of the unchanged
 * value (`or dword [ecx], 0`) where the original reads (`test [ecx], eax`).
 * usage: chkstk_test.exe [cases] [traced cases] [thread sizes]   (MUT=1: orig vs orig) */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

extern void orig_FUN_004addf0(void);
extern void FUN_004addf0(void);
extern void call_chk(void *fn, unsigned size, void *top, void *limit, unsigned *out, int trace);
extern unsigned call_chk_here(void *fn, unsigned size);
extern char chk_ret[];

static uint64_t s = 0x2545f4914f6cdd1dull;
static uint64_t rnd(void) { s ^= s << 13; s ^= s >> 7; s ^= s << 17; return s; }

#define REGION (40u << 20)
#define MAXSZ  (32u << 20)
static unsigned char *region;

/* ---- probe tracing ---- */
static volatile int tracing;
static unsigned probes[20000], nprobe;
static LONG CALLBACK veh(EXCEPTION_POINTERS *ep)
{
    if (!tracing || ep->ExceptionRecord->ExceptionCode != EXCEPTION_SINGLE_STEP)
        return EXCEPTION_CONTINUE_SEARCH;
    CONTEXT *c = ep->ContextRecord;
    unsigned char *ip = (unsigned char *)c->Eip;
    /* stop before `mov esp, ecx` (89 cc / 8b e1): every probe comes before it, and from there on both versions read the
     * saved ECX and return address from below the new ESP when EAX < 8, where the trap frames of the tracing itself
     * would overwrite them */
    if (ip == (unsigned char *)chk_ret || (ip[0] == 0x89 && ip[1] == 0xcc) || (ip[0] == 0x8b && ip[1] == 0xe1)) {
        c->EFlags &= ~0x100u;
        tracing = 0;
        return EXCEPTION_CONTINUE_EXECUTION;
    }
    /* original: 85 01 test [ecx],eax; libgcc: 83 09 00 or dword [ecx],0 */
    if ((ip[0] == 0x85 && ip[1] == 0x01) || (ip[0] == 0x83 && ip[1] == 0x09 && ip[2] == 0x00))
        if (nprobe < sizeof probes / sizeof probes[0]) probes[nprobe++] = c->Ecx;
    c->EFlags |= 0x100u;
    return EXCEPTION_CONTINUE_EXECUTION;
}

static unsigned pick_size(void)
{
    switch (rnd() % 6) {
    case 0: return (unsigned)(rnd() % 0x3000);
    case 1: { long v = (long)(rnd() % 64) * 0x1000 + (long)(rnd() % 17) - 8; return v < 0 ? 0 : (unsigned)v; }
    case 2: { long v = (long)(rnd() % 2048) * 0x1000 + (long)(rnd() % 17) - 8; return v < 0 ? 0 : (unsigned)v; }
    case 3: return (unsigned)(rnd() % MAXSZ);
    case 4: return (unsigned)((rnd() % (MAXSZ / 0x1000)) * 0x1000);
    default: return (unsigned)(rnd() % 0x20000);
    }
}

static int one(void *fn, unsigned size, unsigned top_off, unsigned *out, int trace, uint32_t *win_lo, uint32_t *win_hi)
{
    unsigned char *top = region + REGION - top_off;
    /* pattern around the new and old stack top */
    unsigned char *lo = top - size - 64, *hi = top - 64;
    for (int k = 0; k < 32; k++) { ((uint32_t *)lo)[k] = 0xa5000000u + k; ((uint32_t *)hi)[k] = 0x5a000000u + k; }
    if (trace) { nprobe = 0; tracing = 1; }
    call_chk(fn, size, top, region, out, trace);
    memcpy(win_lo, lo, 128);
    memcpy(win_hi, hi, 128);
    return 0;
}

static unsigned merge(unsigned *p, unsigned n)
{
    unsigned m = 0;
    for (unsigned i = 0; i < n; i++)
        if (m == 0 || p[m - 1] != p[i]) p[m++] = p[i];
    return m;
}

static void *g_fn; static unsigned g_size, g_got;
static DWORD WINAPI thr(void *arg) { (void)arg; g_got = call_chk_here(g_fn, g_size); return 0; }

int main(int argc, char **argv)
{
    setvbuf(stdout, NULL, _IONBF, 0);   /* a crash (the expected result of some mutations) must not eat the report */
    long n = argc > 1 ? atol(argv[1]) : 1000000, nt = argc > 2 ? atol(argv[2]) : 20000, nth = argc > 3 ? atol(argv[3]) : 300;
    int self = getenv("MUT") && atoi(getenv("MUT")) == 1;
    void *f1 = (void *)orig_FUN_004addf0, *f2 = self ? (void *)orig_FUN_004addf0 : (void *)FUN_004addf0;
    region = VirtualAlloc(NULL, REGION, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (!region) { printf("VirtualAlloc failed\n"); return 2; }
    AddVectoredExceptionHandler(1, veh);
    long diffs = 0, eax_diff = 0;
    for (long i = 0; i < n; i++) {
        unsigned size = pick_size(), top_off = 0x100 + (unsigned)(rnd() % 0x2000) * 4;
        unsigned a[9], b[9];
        uint32_t la[32], ha[32], lb[32], hb[32];
        one(f1, size, top_off, a, 0, la, ha);
        one(f2, size, top_off, b, 0, lb, hb);
        unsigned esp0 = a[8];
        int bad = memcmp(a + 1, b + 1, 8 * 4) != 0 || memcmp(la, lb, 128) || memcmp(ha, hb, 128);
        if (a[7] != esp0 - size) bad = 1;               /* ESP after = ESP before the call - size */
        if (a[1] != 0x44444444u || a[2] != 0x55555555u || a[3] != 0x11111111u || a[4] != 0x22222222u
            || a[5] != 0x33333333u || a[6] != 0x77777777u) bad = 1;
        if (a[0] != b[0]) eax_diff++;
        if (bad) {
            if (diffs < 10)
                printf("DIFF size=%#x: orig ecx=%08x esp=%08x | new ecx=%08x esp=%08x (esp0 %08x)\n", size, a[1], a[7],
                       b[1], b[7], esp0);
            diffs++;
        }
    }
    printf("__chkstk part 1: %ld cases (%s), %ld differences in ECX EDX EBX ESI EDI EBP ESP and the stack memory; "
           "EAX differs in %ld (expected: return address vs old ESP)\n", n, self ? "orig vs orig" : "orig vs libgcc via _FUN_004addf0",
           diffs, eax_diff);

    long pdiffs = 0, raw_extra = 0, nprobes_total = 0;
    static unsigned pa[20000], pb[20000];
    for (long i = 0; i < nt; i++) {
        unsigned size = i < 64 ? (unsigned)(i * 0x800) : pick_size() % (40u << 12);   /* traced: up to 160 KiB */
        unsigned top_off = 0x100 + (unsigned)(rnd() % 0x400) * 4;
        unsigned a[9], b[9];
        uint32_t w[4][32];
        if (getenv("DBG")) fprintf(stderr, "traced case %ld size %#x top_off %#x\n", i, size, top_off);
        one(f1, size, top_off, a, 1, w[0], w[1]);
        unsigned na = nprobe; memcpy(pa, probes, na * 4);
        one(f2, size, top_off, b, 1, w[2], w[3]);
        unsigned nb = nprobe; memcpy(pb, probes, nb * 4);
        if (na != nb) raw_extra++;
        unsigned ma = merge(pa, na), mb = merge(pb, nb);
        nprobes_total += ma;
        int bad = ma != mb || memcmp(pa, pb, ma * 4) != 0;
        /* and the expected shape: one probe per page from the top down, the last at the new ESP */
        unsigned top = a[8];
        for (unsigned k = 0; k < ma && !bad; k++) {
            unsigned want = k + 1 == ma ? top - size : top - (k + 1) * 0x1000;
            if (pa[k] != want) bad = 1;
        }
        if (ma != (size >> 12) + ((size & 0xfff) || !size ? 1 : 0)) bad = 1;
        if (bad) {
            if (pdiffs < 10) printf("PROBE DIFF size=%#x: orig %u probes, new %u\n", size, ma, mb);
            pdiffs++;
        }
    }
    printf("__chkstk part 2: %ld traced cases, %ld probes compared, %ld differences in the probe sequence; "
           "%ld cases where only the original repeats its last probe\n", nt, nprobes_total, pdiffs, raw_extra);

    long tfail = 0;
    for (long i = 0; i < nth; i++) {
        unsigned size = i < 40 ? (unsigned)(i * 0x1000 * 37 + (i & 3) * 0x7ff) : (unsigned)(rnd() % (12u << 20));
        for (int w = 0; w < 2; w++) {
            g_fn = w ? f2 : f1; g_size = size; g_got = 0;
            HANDLE h = CreateThread(NULL, 16u << 20, thr, NULL, STACK_SIZE_PARAM_IS_A_RESERVATION, NULL);
            WaitForSingleObject(h, INFINITE);
            DWORD code = 1;
            GetExitCodeThread(h, &code);
            CloseHandle(h);
            if (code != 0 || g_got != size) { if (tfail < 10) printf("THREAD FAIL %s size=%#x got %#x\n", w ? "new" : "orig", size, g_got); tfail++; }
        }
    }
    printf("__chkstk part 3: %ld sizes on fresh 16 MiB thread stacks, both versions: %ld failures\n", nth, tfail);
    return diffs || pdiffs || tfail;
}
