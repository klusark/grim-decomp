/* Differential test of ThingInstancer and SpriteInstancer (build/overrides_asm_o2.c) against the original machine
 * code.  The CHORE.DLL imports (Cos_Inst*), the rdThing / ResRef / puppet functions and the costume service table are
 * recorders; instance data, records, rdThings and allocated blocks come from pools inside compared memory regions.
 * Build: build/difftest/asm_s5/build.sh build/difftest/asm_s5/cos_test.c build/difftest/asm_s5/out/cos_test.exe \
 *   ThingInstancer SpriteInstancer */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fx.h"

extern void *orig_ThingInstancer(void *, int, int), *ThingInstancer(void *, int, int);
extern void *orig_SpriteInstancer(int, void *, int), *SpriteInstancer(int, void *, int);

static unsigned R(unsigned n) { return (unsigned)(fx_rnd() % n); }

enum { T_GID = 1, T_CINFO, T_UDATA, T_COUNT, T_RRADD, T_RRREM, T_TFREE, T_TNEW, T_TMODEL, T_PUP, T_POLY, T_ALLOC, T_FREE, T_ASSERT, T_LAST };
static void *th[T_LAST];
#define CALLN(t, T, ...) ((int (*)T)th[t])(__VA_ARGS__)

static struct {
    int inst[16][0x194 / 4];     /* instance data blocks */
    int rec[8][16];              /* component records */
    int things[8][16];           /* rdThings */
    int blocks[8][0x194 / 4];    /* allocations */
    int nthing, nblock;
} pool;
static unsigned script[8];
static const char *names[4] = {"mannyhead.3do", "MANNYHEAD.3DO", "manny_body.3do", "glottis.3do"};

static int eff(int tag, unsigned *a)
{
    switch (tag) {
    case T_GID: return (int)(uintptr_t)pool.inst[(a[0] * 7 + a[1] * 3) % 16];
    case T_CINFO: {
        unsigned h = a[0] * 31 + a[1] * 17 + script[0];
        if (a[2]) *(int *)a[2] = (h >> 3) % 3;
        if (a[3]) *(void **)a[3] = pool.rec[(h >> 5) % 8];
        if (a[4]) *(int *)a[4] = (int)((h >> 7) % 5) - 2;
        return (int)(uintptr_t)names[(h >> 9) % 4];
    }
    case T_TNEW: return (int)(uintptr_t)pool.things[pool.nthing++ % 8];
    case T_ALLOC: return (int)(uintptr_t)pool.blocks[pool.nblock++ % 8];
    }
    return -12345678;
}

int Cos_InstGetInstanceDataX(int a, int b, int c) __asm__("_Cos_InstGetInstanceData");
int Cos_InstGetInstanceDataX(int a, int b, int c) { return CALLN(T_GID, (int, int, int), a, b, c); }
int Cos_InstComponentInfoX(int a, int b, int c, int d, int e) __asm__("_Cos_InstComponentInfo");
int Cos_InstComponentInfoX(int a, int b, int c, int d, int e) { return CALLN(T_CINFO, (int, int, int, int, int), a, b, c, d, e); }
int Cos_InstGetUserDataX(int a) __asm__("_Cos_InstGetUserData");
int Cos_InstGetUserDataX(int a) { return CALLN(T_UDATA, (int), a); }
int Cos_InstCountComponentsX(int a) __asm__("_Cos_InstCountComponents");
int Cos_InstCountComponentsX(int a) { return CALLN(T_COUNT, (int), a); }
void *imp_gid __asm__("__imp__Cos_InstGetInstanceData") = Cos_InstGetInstanceDataX;
void *imp_cinfo __asm__("__imp__Cos_InstComponentInfo") = Cos_InstComponentInfoX;
void *imp_udata __asm__("__imp__Cos_InstGetUserData") = Cos_InstGetUserDataX;
void *imp_count __asm__("__imp__Cos_InstCountComponents") = Cos_InstCountComponentsX;
void ResRef_AddX(void *a, void *b, char *c, int d) __asm__("_Res_SetReference");
void ResRef_AddX(void *a, void *b, char *c, int d) { CALLN(T_RRADD, (void *, void *, char *, int), a, b, c, d); }
void ResRef_RemoveX(void *a) __asm__("_Res_RemoveReference");
void ResRef_RemoveX(void *a) { CALLN(T_RRREM, (void *), a); }
void rdThing_FreeX(int a) __asm__("_rdThing_Free");
void rdThing_FreeX(int a) { CALLN(T_TFREE, (int), a); }
int rdThing_NewX(int a) __asm__("_rdThing_New");
int rdThing_NewX(int a) { return CALLN(T_TNEW, (int), a); }
void rdThing_SetModelX(void *a, void *b) __asm__("_rdThing_SetModel3");
void rdThing_SetModelX(void *a, void *b) { CALLN(T_TMODEL, (void *, void *), a, b); }
int rdPuppet_NewX(void *a) __asm__("_rdPuppet_New");
int rdPuppet_NewX(void *a) { return CALLN(T_PUP, (void *), a); }
int rdThing_SetPolylineX(void *a, int b) __asm__("_rdThing_SetPolyline");
int rdThing_SetPolylineX(void *a, int b) { return CALLN(T_POLY, (void *, int), a, b); }
int my_stricmp(const char *a, const char *b) __asm__("__stricmp");
int my_stricmp(const char *a, const char *b)
{
    for (;; a++, b++) {
        int x = (unsigned char)*a, y = (unsigned char)*b;
        if (x >= 'A' && x <= 'Z') x += 32;
        if (y >= 'A' && y <= 'Z') y += 32;
        if (x != y || !x) return x - y;
    }
}

int main(int argc, char **argv)
{
    long n = argc > 1 ? atol(argv[1]) : 10000, i;
    static void *svc_cos[0x20], *svc_main[0x20];
    int nargs[T_LAST] = {0, 3, 5, 1, 1, 4, 1, 1, 1, 2, 1, 2, 3, 1, 3};
    for (int t = 1; t < T_LAST; t++) { th[t] = fx_thunk(t, nargs[t], 0); fx_effect(t, eff); }
    fx_ignmask(T_CINFO, 0x1c);
    fx_strmask(T_ALLOC, 2); fx_strmask(T_RRADD, 4); fx_strmask(T_ASSERT, 3);
    svc_cos[0x20 / 4] = th[T_ALLOC]; svc_cos[0x24 / 4] = th[T_FREE];
    svc_main[0x18 / 4] = th[T_ASSERT];
    FXU32(0x8ca7a0) = (unsigned)(uintptr_t)svc_cos;
    FXU32(0x905ac0) = (unsigned)(uintptr_t)svc_main;
    fx_region(&pool, sizeof pool);
    for (i = 0; i < n; i++) {
        int pass, create = R(3) ? 1 : 0, idx = R(6), inst = 0x1000 + R(4);
        void *ret[2];
        unsigned char *p = (unsigned char *)&pool;
        for (unsigned k = 0; k < sizeof pool; k++) p[k] = (unsigned char)(R(4) ? 0 : fx_rnd());
        for (int k = 0; k < 16; k++) pool.inst[k][0x50 / 4] = R(3);
        for (int k = 0; k < 8; k++) pool.rec[k][0] = R(5) ? (int)fx_rnd() : 0;
        pool.nthing = R(8); pool.nblock = R(8);
        script[0] = (unsigned)fx_rnd();
        fx_ret(T_UDATA, R(3) ? 0x2000 + R(3) : 0);
        fx_ret(T_COUNT, (int)R(7) - 1);
        fx_ret(T_PUP, (int)fx_rnd());
        fx_save();
        for (pass = 0; pass < 2; pass++) {
            fx_reset();
            if (i & 1)
                ret[pass] = pass ? SpriteInstancer(inst, (void *)(uintptr_t)idx, create) : orig_SpriteInstancer(inst, (void *)(uintptr_t)idx, create);
            else
                ret[pass] = pass ? ThingInstancer((void *)(uintptr_t)inst, idx, create) : orig_ThingInstancer((void *)(uintptr_t)inst, idx, create);
            if (pass == 0) { fx_snap_a(); fx_restore(); }
        }
        if (ret[0] != ret[1]) fx_fail("ret", i);
        if (fx_cmp_a()) fx_fail("mem", i);
        if (fx_cmp_log()) fx_fail("log", i);
        fx_cases++;
    }
    printf("cos_test: %ld cases, %ld differences\n", fx_cases, fx_fails);
    return fx_fails != 0;
}
