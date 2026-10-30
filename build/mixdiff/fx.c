/* implementation of the trace harness, see fx.h */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fx.h"

FxEv fx_log[FX_MAXLOG];
int fx_nlog;
static FxEv kept[FX_MAXLOG];
static int nkept;
uint64_t fx_seed = 88172645463325252ull;
long fx_fails, fx_cases;

uint64_t fx_rnd(void)
{
    fx_seed ^= fx_seed << 13; fx_seed ^= fx_seed >> 7; fx_seed ^= fx_seed << 17;
    return fx_seed;
}

void fx_fail(const char *what, long i)
{
    if (fx_fails++ < 20)
        printf("DIFF %s (case %ld)\n", what, i);
}

#define MAXTAG 16384
#define MAXQ 64
static int retval[MAXTAG];
static int queue[MAXTAG][MAXQ], qlen[MAXTAG], qpos[MAXTAG];
static FxEffect effect[MAXTAG];
static int strmask[MAXTAG], ignmask[MAXTAG], derefmask[MAXTAG];

void fx_ret(int tag, int value) { retval[tag] = value; }
void fx_queue(int tag, int value) { if (qlen[tag] < MAXQ) queue[tag][qlen[tag]++] = value; }
void fx_effect(int tag, FxEffect fn) { effect[tag] = fn; }
void fx_strmask(int tag, int mask) { strmask[tag] = mask; }
void fx_ignmask(int tag, int mask) { ignmask[tag] = mask; }
void fx_derefmask(int tag, int mask) { derefmask[tag] = mask; }
void fx_reset(void)
{
    fx_nlog = 0;
    memset(qpos, 0, sizeof qpos);
}
void fx_clear_queues(void)
{
    memset(qlen, 0, sizeof qlen); memset(qpos, 0, sizeof qpos);
}
void fx_clear_all(void)
{
    memset(retval, 0, sizeof retval); memset(qlen, 0, sizeof qlen); memset(qpos, 0, sizeof qpos);
    memset(effect, 0, sizeof effect); memset(strmask, 0, sizeof strmask); memset(ignmask, 0, sizeof ignmask); memset(derefmask, 0, sizeof derefmask);
    fx_nlog = 0;
}

static int __cdecl fx_handler(int tag, unsigned *args, int nargs)
{
    int ret = retval[tag];
    FxEv *e = fx_nlog < FX_MAXLOG ? &fx_log[fx_nlog] : &fx_log[FX_MAXLOG - 1];
    int i;

    memset(e, 0, sizeof *e);
    e->tag = tag;
    for (i = 0; i < 10 && i < nargs; i++) {
        if (strmask[tag] & (1 << i)) {
            const char *s = (const char *)args[i];
            if (s) { strncpy(e->str[i < 3 ? i : 2], s, 63); }
            e->a[i] = 0;
        } else if (i < 4 && (derefmask[tag] & (1 << i))) {
            memcpy(e->deref[i], (void *)args[i], 20);
            e->a[i] = 0;
        } else if (ignmask[tag] & (1 << i)) {
            e->a[i] = 0;
        } else {
            e->a[i] = args[i];
        }
    }
    if (qpos[tag] < qlen[tag])
        ret = queue[tag][qpos[tag]++];
    if (effect[tag]) {
        int r = effect[tag](tag, args);
        if (r != -12345678)
            ret = r;
    }
    e->ret = ret;
    fx_nlog++;
    return ret;
}

void *fx_thunk(int tag, int nargs, int stdcall_)
{
    static unsigned char *page;
    static int used;
    unsigned char *p;
    unsigned h = (unsigned)(uintptr_t)fx_handler;

    if (!page)
        page = VirtualAlloc(0, 1 << 20, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    p = page + used;
    *p++ = 0xB8; memcpy(p, &tag, 4); p += 4;                       /* mov eax, tag */
    *p++ = 0x8D; *p++ = 0x54; *p++ = 0x24; *p++ = 0x04;            /* lea edx, [esp+4] */
    *p++ = 0x6A; *p++ = (unsigned char)nargs;                       /* push nargs */
    *p++ = 0x52;                                                    /* push edx */
    *p++ = 0x50;                                                    /* push eax */
    *p++ = 0xB9; memcpy(p, &h, 4); p += 4;                         /* mov ecx, handler */
    *p++ = 0xFF; *p++ = 0xD1;                                       /* call ecx */
    *p++ = 0x83; *p++ = 0xC4; *p++ = 0x0C;                          /* add esp, 12 */
    if (stdcall_ && nargs) { unsigned short n = (unsigned short)(nargs * 4); *p++ = 0xC2; memcpy(p, &n, 2); p += 2; }
    else *p++ = 0xC3;
    {
        void *r = page + used;
        used = (int)((p - page + 15) & ~15);
        return r;
    }
}

void *fx_com(int objtag, int nmethods, const int *nargs)
{
    void **obj = calloc(1, 16), **vtbl = calloc(nmethods, sizeof(void *));
    int i;
    for (i = 0; i < nmethods; i++)
        vtbl[i] = fx_thunk(objtag * 100 + i, nargs[i], 1);
    obj[0] = vtbl;
    return obj;
}

/* regions */
typedef struct { unsigned char *p; unsigned len; unsigned char *start, *a; } Rgn;
static Rgn rg[64];
static int nrg;

void fx_region(void *p, unsigned len)
{
    rg[nrg].p = p; rg[nrg].len = len;
    rg[nrg].start = malloc(len); rg[nrg].a = malloc(len);
    nrg++;
}
void fx_region_reset(void)
{
    int i;
    for (i = 0; i < nrg; i++) { free(rg[i].start); free(rg[i].a); }
    nrg = 0;
}
void fx_save(void) { int i; for (i = 0; i < nrg; i++) memcpy(rg[i].start, rg[i].p, rg[i].len); }
void fx_restore(void) { int i; for (i = 0; i < nrg; i++) memcpy(rg[i].p, rg[i].start, rg[i].len); }
void fx_snap_a(void)
{
    int i;
    for (i = 0; i < nrg; i++) memcpy(rg[i].a, rg[i].p, rg[i].len);
    memcpy(kept, fx_log, sizeof(FxEv) * (fx_nlog < FX_MAXLOG ? fx_nlog : FX_MAXLOG));
    nkept = fx_nlog;
}
int fx_cmp_a(void)
{
    int i, bad = 0;
    for (i = 0; i < nrg; i++)
        if (memcmp(rg[i].a, rg[i].p, rg[i].len)) {
            unsigned k;
            for (k = 0; k < rg[i].len; k++) if (rg[i].a[k] != rg[i].p[k]) break;
            if (fx_fails < 20) printf("  region %d differs at +0x%x (orig %02x mine %02x)\n", i, k, rg[i].a[k], rg[i].p[k]);
            bad = 1;
        }
    return bad;
}
int fx_cmp_log(void)
{
    int i;
    if (getenv("FXDEBUG") && fx_fails == 0 && nkept != 0) {
        for (i = 0; i < nkept || i < fx_nlog; i++) {
            if (i < nkept) printf("  O%d tag %d [%x %x %x] ret %d\n", i, kept[i].tag, kept[i].a[0], kept[i].a[1], kept[i].a[2], kept[i].ret);
            if (i < fx_nlog) printf("  M%d tag %d [%x %x %x] ret %d\n", i, fx_log[i].tag, fx_log[i].a[0], fx_log[i].a[1], fx_log[i].a[2], fx_log[i].ret);
        }
    }
    if (nkept != fx_nlog) {
        if (fx_fails < 20) {
            printf("  call logs differ in length: orig %d mine %d\n", nkept, fx_nlog);
            for (i = 0; i < nkept || i < fx_nlog; i++) {
                if (i < nkept && i < fx_nlog && !memcmp(&kept[i], &fx_log[i], sizeof(FxEv))) continue;
                if (i < nkept) printf("   orig[%d] tag %d a0 %x a1 %x a2 %x ret %d\n", i, kept[i].tag, kept[i].a[0], kept[i].a[1], kept[i].a[2], kept[i].ret);
                if (i < fx_nlog) printf("   mine[%d] tag %d a0 %x a1 %x a2 %x ret %d\n", i, fx_log[i].tag, fx_log[i].a[0], fx_log[i].a[1], fx_log[i].a[2], fx_log[i].ret);
                break;
            }
        }
        return 1;
    }
    for (i = 0; i < nkept; i++)
        if (memcmp(&kept[i], &fx_log[i], sizeof(FxEv))) {
            if (fx_fails < 20)
                printf("  call %d differs: orig tag %d (%x %x %x %x) ret %d / mine tag %d (%x %x %x %x) ret %d\n", i,
                       kept[i].tag, kept[i].a[0], kept[i].a[1], kept[i].a[2], kept[i].a[3], kept[i].ret,
                       fx_log[i].tag, fx_log[i].a[0], fx_log[i].a[1], fx_log[i].a[2], fx_log[i].a[3], fx_log[i].ret);
            return 1;
        }
    return 0;
}
