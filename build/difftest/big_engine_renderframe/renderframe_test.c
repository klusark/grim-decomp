/* Differential test of sputRender_Update (build/overrides_big_engine_renderframe.c) against the original 1.01 machine code
 * (orig_sputRender_Update, sliced from src/GRIMFANDANGO.EXE/asm_funcs.s and corrected with fix_orig.sed, see run.sh).
 *
 * Both run on the same random start state: the globals the function reads and writes (data image), two sets with
 * setup records (300 bytes each) and object-state chains, an actor table of 8 actors (0xa8 bytes), the draw list
 * (pointers at 0x008c9568 to {type byte, ..., actor index at +8}), colormap records, a fake service table.
 * Every callee is a recorder defined here (both versions call the same symbols): it logs its arguments (pointers to
 * stack buffers by content: rectangles, scale vectors) and runs an effect from a per-run random stream that changes
 * state the function reads afterwards (set / setup indices, actor scale, colormap pointers, buffer count, the draw-list
 * count), so the order and number of reloads are checked.  Compared: all registered memory and the call log.
 * Each case also runs under a random x87 precision control (24 / 53 / 64 bit). */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fx.h"

extern void orig_sputRender_Update(void);
extern void sputRender_Update(void);

static unsigned R(unsigned n) { return (unsigned)(fx_rnd() % n); }
static unsigned eseed;
static unsigned E(unsigned n) { eseed = eseed * 1664525u + 1013904223u; return (eseed >> 8) % n; }

enum { T_SETTARGET = 1, T_POLL, T_DRADD, T_FULLREDRAW, T_FRAMESEC, T_TALK, T_LOCK, T_UNLOCK, T_TEXT, T_PRESENT, T_USERPAINT,
       T_PRINTSTACK, T_GETSET, T_DRCLEAR, T_SWITCH, T_POSTCAM, T_APPLYCAM, T_OSDRAW, T_PBEGIN, T_PEND, T_DRFLUSH, T_PRIMS,
       T_BEGIN, T_BUILDLIST, T_TOUCH, T_SECTORDBG, T_GRID, T_GETFRAME, T_MATRIX, T_SCREENBOX, T_INVLAST, T_SETCMAP,
       T_DRAWCOS, T_DBGWALKER, T_END, T_LIGHTS, T_CAMS, T_TOTALMS, T_IRIS, T_INVRECT, T_CMAPCB, T_ASSERT };

static FxEv *ev(int tag, int n, unsigned a0, unsigned a1, unsigned a2, unsigned a3)
{
    FxEv *e = &fx_log[fx_nlog < FX_MAXLOG ? fx_nlog : FX_MAXLOG - 1];
    memset(e, 0, sizeof *e);
    e->tag = tag;
    if (n > 0) e->a[0] = a0;
    if (n > 1) e->a[1] = a1;
    if (n > 2) e->a[2] = a2;
    if (n > 3) e->a[3] = a3;
    fx_nlog++;
    return e;
}
#define U(p) ((unsigned)(uintptr_t)(p))

/* ---- the world ---- */
#define NSET 2
#define NSETUP 4
#define NOS 6
#define NACT 8
#define NENT 8
static unsigned char sets[NSET][0x100];
static unsigned char setups[NSET][NSETUP * 300];
static unsigned char objs[NOS][0x100];
static unsigned char actors[NACT * 0xa8];
static unsigned char ents[NENT][16];
static unsigned cmaps[NACT + 4][2];           /* actor colormap records {valid, value} */
static unsigned char setcm[NSET][4 * 0x34];  /* set colormap records */
static int costumes[NACT];
static float frames[NACT][16];
static unsigned svc[16];
static int setq[8], nsetq, posq;             /* sputRoom_GetCurrentRoom results, then the last one repeats */
static int poll_ret, poll2_ret, mode_effects;
static unsigned total_ms;
static unsigned frame_sec_bits;

static unsigned rndfloat(void)
{
    static const unsigned special[] = {0x3f800000, 0, 0x80000000, 0x7fc00000, 0xffc00000, 0x7f800000, 0xff800000,
                                       0x3f000000, 0xbf800000, 0x00000001, 0x7f7fffff, 0x3f800001, 0x3f7fffff, 0x40000000};
    switch (R(4)) {
    case 0: return special[R(sizeof special / 4)];
    case 1: { float f = (float)((int)R(20001) - 10000) / (float)(1 + R(1000)); return *(unsigned *)&f; }
    case 2: return (unsigned)fx_rnd();
    default: { float f = 0.25f + (float)R(1000) / 250.0f; return *(unsigned *)&f; }
    }
}

/* a random pointer to an object of one of the arrays (or 0) */
static void *any_set(void) { return R(8) == 0 ? (void *)0 : sets[R(NSET)]; }

/* ---- recorders ---- */
int sputSmush_SetTarget(void *s) { ev(T_SETTARGET, 1, U(s), 0, 0, 0); return 7; }
int sputSmush_Periodic(void) { int r = posq == -1 ? poll2_ret : poll_ret; ev(T_POLL, 0, 0, 0, 0, 0)->ret = r; posq = posq == -1 ? -2 : posq; return r; }
void DirtyRect_Add(int *rect, int flag, int idx)
{
    FxEv *e = ev(T_DRADD, 2, flag, idx, 0, 0);
    memcpy(e->deref[0], rect, 16);
    if (mode_effects && E(4) == 0) FXI32(0x4e8074) = (int)E(6) - 1;     /* g_nNumPages reread each iteration */
    if (mode_effects && E(8) == 0) rect[E(4)] = (int)E(1000);
}
void sputRender_ForceRefresh(void) { ev(T_FULLREDRAW, 0, 0, 0, 0, 0); }
float sputTime_GetFrameTimeFlex(void) { ev(T_FRAMESEC, 0, 0, 0, 0, 0); return *(float *)&frame_sec_bits; }
void sputActor_UpdateSpeechOnly(unsigned bits) { ev(T_TALK, 1, bits, 0, 0, 0); }
int stdDisplay_VBufferLock(void *s) { ev(T_LOCK, 1, U(s), 0, 0, 0); if (mode_effects && E(6) == 0) FXU32(0x90563c) = E(100000); return 1; }
int stdDisplay_VBufferUnlock(void *s) { ev(T_UNLOCK, 1, U(s), 0, 0, 0); return 1; }
void sputText_Update(int a) { ev(T_TEXT, 2, a, FXU32(0x8a94b8), 0, 0); }
void Render_Present(void) { ev(T_PRESENT, 0, 0, 0, 0, 0); }
void grimlib_UserPaint(void) { ev(T_USERPAINT, 0, 0, 0, 0, 0); }
int lps_fn(int a) __asm__("_lua_printstack");
int lps_fn(int a) { ev(T_PRINTSTACK, 1, a, 0, 0, 0); return 0; }
void *lps_imp __asm__("__imp__lua_printstack") = lps_fn;
void *sputRoom_GetCurrentRoom(void)
{
    void *r;
    if (posq < 0) posq = 0;
    r = posq < nsetq ? (setq[posq] < 0 ? 0 : sets[setq[posq]]) : (setq[nsetq - 1] < 0 ? 0 : sets[setq[nsetq - 1]]);
    posq++;
    ev(T_GETSET, 0, 0, 0, 0, 0)->ret = (int)U(r);
    return r;
}
void DirtyRect_Clear(void) { ev(T_DRCLEAR, 0, 0, 0, 0, 0); }
void sputRender_UseSetup(unsigned char *set, int setup)
{
    ev(T_SWITCH, 2, U(set), setup, 0, 0);
    if (mode_effects && E(3) == 0) *(int *)(set + 0xb4) = (int)E(NSETUP);
}
void sputLua_PostCameraChange(int setup)
{
    ev(T_POSTCAM, 1, setup, 0, 0, 0);
    if (mode_effects && E(3) == 0) FXI32(0x4e8084) = (int)E(NSETUP);       /* g_nSputRender_Update_RenderSetup changed by the handler */
}
void sputRender_SyncCamera(void *set, int setup) { ev(T_APPLYCAM, 2, U(set), setup, 0, 0); }
void __stdcall os_draw(unsigned char *self, int type, void *dst, void *z) __asm__("_os_draw@16");
void __stdcall os_draw(unsigned char *self, int type, void *dst, void *z)
{
    ev(T_OSDRAW, 4, U(self), type, U(dst), U(z));
    if (mode_effects && E(10) == 0) *(void **)(self + 0xf8) = E(2) ? 0 : objs[E(NOS)];  /* chain read again each step */
    if (mode_effects && E(12) == 0) FXU32(0x8c97a4) = E(1000);
}
/* __thiscall ObjectState_Draw(this = ECX, type, dst, zdst): forward to the stdcall recorder with ECX as first argument */
__asm__(".globl _ObjectState_Draw\n_ObjectState_Draw:\n\tpopl %eax\n\tpushl %ecx\n\tpushl %eax\n\tjmp _os_draw@16\n");
void PerfBegin(int a) { ev(T_PBEGIN, 1, a, 0, 0, 0); }
void *PerfEnd(int a) { ev(T_PEND, 1, a, 0, 0, 0); return 0; }
void DirtyRect_Flush(void *d, void *z) { ev(T_DRFLUSH, 2, U(d), U(z), 0, 0); }
void sputPrimitive_Update(unsigned m) { ev(T_PRIMS, 1, m, 0, 0, 0); }
void rdroid_BeginFrame(void) { ev(T_BEGIN, 0, 0, 0, 0, 0); }
void Render_BuildActorDrawList(void)
{
    ev(T_BUILDLIST, 0, 0, 0, 0, 0);
    if (mode_effects && E(4) == 0) FXU32(0x8a952c) = E(NENT + 1);
}
void sputCostume_Draw2D(int c)
{
    ev(T_TOUCH, 1, c, 0, 0, 0);
    if (mode_effects && E(8) == 0) FXU32(0x8a952c) = E(NENT + 1);           /* loop bound reread */
}
void Sector_DrawAllDebug(void *set) { ev(T_SECTORDBG, 1, U(set), 0, 0, 0); }
void Render_DrawDebugGrid(void) { ev(T_GRID, 0, 0, 0, 0, 0); }
float *sputActor_GetOrientMatrix(unsigned char *a)
{
    ev(T_GETFRAME, 1, U(a), 0, 0, 0);
    return frames[((a - actors) / 0xa8) & 7];
}
void rdMatrix_PreScale34(float *m, unsigned *v)
{
    FxEv *e = ev(T_MATRIX, 1, U(m), 0, 0, 0);
    memcpy(e->deref[0], v, 12);
    if (mode_effects && E(5) == 0) { unsigned k = E(NACT); *(unsigned *)(actors + k * 0xa8 + 0x30) = E(2) ? 0x3f800000 : eseed; }
}
void Actor_ComputeScreenBox(unsigned char *a)
{
    ev(T_SCREENBOX, 1, U(a), 0, 0, 0);
    if (mode_effects && E(4) == 0) *(unsigned *)(a + 0x30) = E(2) ? 0x3f800000 : eseed;
    if (mode_effects && E(6) == 0) FXI32(0x8c9784) ^= 1;                   /* g_nSputRender_b3DAcceleration reread */
}
void Render_InvalidateRectLastBuffer(int *r, int f) { ev(T_INVLAST, 2, U(r), f, 0, 0); }
unsigned rdroid_SetColormap(unsigned c)
{
    ev(T_SETCMAP, 1, c, 0, 0, 0);
    if (mode_effects && E(4) == 0) {                                       /* colormap pointers reread after the call */
        switch (E(4)) {
        case 0: *(void **)(actors + E(NACT) * 0xa8) = cmaps[E(NACT + 4)]; break;
        case 1: cmaps[E(NACT + 4)][0] = E(2); break;
        case 2: *(int *)(sets[E(NSET)] + 0x88) = (int)E(4); break;
        default: FXU32(0x8c9800) = U(sets[E(NSET)]); break;
        }
    }
    return 0;
}
void sputCostume_Draw3D(unsigned c, unsigned f)
{
    ev(T_DRAWCOS, 2, c, f, 0, 0);
    if (mode_effects && E(4) == 0) { unsigned k = E(NACT); *(unsigned *)(actors + k * 0xa8 + 0x30) = E(2) ? 0x3f800000 : (E(2) ? 0x3f000000 + E(0x1000000) : eseed); }
    if (mode_effects && E(8) == 0) FXU32(0x4e8078) = E(16);               /* debug flags reread */
}
void Actor_DrawDebugWalker(void *a) { ev(T_DBGWALKER, 1, U(a), 0, 0, 0); }
void rdroid_EndFrame(void) { ev(T_END, 0, 0, 0, 0, 0); }
void Set_DrawDebugLights(void *s) { ev(T_LIGHTS, 1, U(s), 0, 0, 0); if (mode_effects && E(3) == 0) FXU32(0x4e8078) ^= 4; }
void Set_DrawDebugCameras(void *s, unsigned k) { ev(T_CAMS, 2, U(s), k, 0, 0); }
unsigned sputTime_GetGameTime(void) { ev(T_TOTALMS, 0, 0, 0, 0, 0); return total_ms; }
void sputRender_DrawIrisEffect(unsigned bits, int x, int y)
{
    ev(T_IRIS, 3, bits, x, y, 0);
    if (mode_effects && E(4) == 0) { float f = (float)((int)E(2001) - 1000); FXU32(0x8c9778) = *(unsigned *)&f; }
}
void MarkDirtyRect(int *r, int f) { FxEv *e = ev(T_INVRECT, 1, f, 0, 0, 0); memcpy(e->deref[0], r, 16); }
static void cmap_cb(unsigned a, unsigned b) { ev(T_CMAPCB, 2, a, b, 0, 0); }
static void assert_cb(char *a, char *b, int line) { ev(T_ASSERT, 3, U(a), U(b), line, 0); }

static void set_fpu_pc(unsigned short pc)
{
    unsigned short cw;
    __asm__ volatile ("fnstcw %0" : "=m"(cw));
    cw = (unsigned short)((cw & ~0x300) | (pc << 8));
    __asm__ volatile ("fldcw %0" : : "m"(cw));
}

static void randomize(void)
{
    int s, k;
    for (s = 0; s < NSET; s++) {
        for (k = 0; k < 0x100; k++) sets[s][k] = (unsigned char)fx_rnd();
        for (k = 0; k < (int)sizeof setcm[s]; k++) setcm[s][k] = (unsigned char)fx_rnd();
        for (k = 0; k < 4; k++) *(unsigned *)(setcm[s] + k * 0x34) = R(5) ? 1 + R(100) : 0;
        *(void **)(sets[s] + 0x80) = setcm[s];
        *(int *)(sets[s] + 0x88) = (int)R(4);
        *(void **)(sets[s] + 0xac) = setups[s];
        *(int *)(sets[s] + 0xb4) = (int)R(NSETUP);
        for (k = 0; k < (int)sizeof setups[s]; k++) setups[s][k] = (unsigned char)fx_rnd();
        for (k = 0; k < NSETUP; k++) *(void **)(setups[s] + k * 300 + 0x128) = R(3) ? objs[R(NOS)] : 0;
    }
    for (k = 0; k < NOS; k++) {
        int j;
        for (j = 0; j < 0x100; j++) objs[k][j] = (unsigned char)fx_rnd();
        *(void **)(objs[k] + 0xf8) = (k + 1 < NOS && R(3)) ? objs[k + 1 + R(NOS - k - 1)] : 0;   /* acyclic chains */
    }
    for (k = 0; k < NACT + 4; k++) { cmaps[k][0] = R(5) ? 1 + R(9) : 0; cmaps[k][1] = (unsigned)fx_rnd(); }
    for (k = 0; k < NACT; k++) {
        unsigned char *a = actors + k * 0xa8;
        int j;
        for (j = 0; j < 0xa8; j++) a[j] = (unsigned char)fx_rnd();
        *(void **)a = cmaps[R(NACT + 4)];
        *(unsigned *)(a + 0x30) = R(2) ? 0x3f800000 : rndfloat();
        costumes[k] = (int)fx_rnd();
        *(void **)(a + 0xa0) = &costumes[k];
    }
    for (k = 0; k < NENT; k++) {
        int j;
        for (j = 0; j < 16; j++) ents[k][j] = (unsigned char)fx_rnd();
        ents[k][0] = (unsigned char)(R(4) ? R(2) : R(256));
        *(int *)(ents[k] + 8) = (int)R(NACT);
        FXU32(0x8c9568 + 4 * k) = U(ents[R(NENT)]);
    }
    FXU32(0x8ca758) = U(actors);
    FXU32(0x8a952c) = R(4) ? R(NENT + 1) : 0;
    { static const unsigned modes[] = {0, 1, 2, 2, 2, 2, 3, 3, 4, 4, 5}; FXU32(0x8a8c40) = modes[R(11)]; }
    FXU32(0x4e8074) = R(5);                     /* g_nNumPages */
    FXI32(0x8c97f0) = R(3) == 0;                /* g_nSputRender_Reset */
    FXU32(0x8c9804) = R(4) == 0;
    FXU32(0x8c9800) = U(any_set());             /* g_pRenderedSet */
    if (FXU32(0x8c9800) == 0) FXU32(0x8c9800) = U(sets[0]);
    FXI32(0x4e8084) = (int)R(NSETUP);           /* g_nSputRender_Update_RenderSetup */
    FXU32(0x4e8080) = R(2);                     /* g_nDoTheFlip */
    FXU32(0x4e8078) = R(3) ? 0 : (unsigned)fx_rnd();   /* debug flags */
    FXU32(0x8c9784) = R(2);                     /* z-buffer enabled */
    FXU32(0x8c97b0) = (unsigned)fx_rnd(); FXU32(0x8c97b4) = (unsigned)fx_rnd(); FXU32(0x8c97a4) = (unsigned)fx_rnd();
    FXU32(0x8c97b8) = U(cmap_cb);
    svc[6] = U(assert_cb);
    FXU32(0x905ac0) = U(svc);
    FXU32(0x8c9798) = (unsigned)fx_rnd() & (R(2) ? ~0u : ~4u);   /* g_dwRenderFlags */
    FXU32(0x8c9774) = (unsigned)fx_rnd();
    {   /* iris: start and now close together (either order), or anything */
        unsigned st = FXU32(0x8c9774), dur;
        float d;
        total_ms = R(3) ? st + (unsigned)((int)R(4001) - 1000) : (unsigned)fx_rnd();
        switch (R(5)) {
        case 0: dur = rndfloat(); break;
        case 1: d = -(float)(1 + R(3000)); dur = *(unsigned *)&d; break;
        default: d = (float)(1 + R(3000)); dur = *(unsigned *)&d; break;
        }
        FXU32(0x8c9778) = dur;
    }
    FXI32(0x4e8064) = (int)R(640); FXI32(0x4e8068) = (int)R(480);
    FXU32(0x90563c) = (unsigned)fx_rnd(); FXU32(0x8a94b8) = (unsigned)fx_rnd(); FXU32(0x8c97f8) = (unsigned)fx_rnd();
    frame_sec_bits = rndfloat();
    poll_ret = R(2); poll2_ret = R(2);
    /* sputRoom_GetCurrentRoom: mostly the rendered set, sometimes the other one; only the first call may return none (the
     * original dereferences the later results without a test) */
    nsetq = 1 + R(5);
    for (k = 0; k < nsetq; k++) {
        unsigned r = R(10);
        int cur = sets[1] == (unsigned char *)(uintptr_t)FXU32(0x8c9800) ? 1 : 0;
        setq[k] = r == 0 ? (k == 0 ? -1 : cur) : r < 3 ? (int)R(NSET) : cur;
    }
    if (R(2)) for (k = 0; k < NSET; k++) if (U(sets[k]) == FXU32(0x8c9800) && R(2)) *(int *)(sets[k] + 0xb4) = FXI32(0x4e8084);
}

int main(int argc, char **argv)
{
    long n = argc > 1 ? atol(argv[1]) : 100000, i;
    long modes[6] = {0}, iris = 0, actors_drawn = 0;
    static long tagcount[64];
    fx_region(sets, sizeof sets); fx_region(setups, sizeof setups); fx_region(objs, sizeof objs);
    fx_region(actors, sizeof actors); fx_region(ents, sizeof ents); fx_region(cmaps, sizeof cmaps);
    fx_region(setcm, sizeof setcm); fx_region(costumes, sizeof costumes); fx_region(frames, sizeof frames);
    fx_region(FXDATA(0x4e8060), 0x30);          /* iris x/y, g_nNumPages, debug flags, draw enabled, rendered setup */
    fx_region(FXDATA(0x8a8c40), 4); fx_region(FXDATA(0x8a94b8), 4); fx_region(FXDATA(0x8a952c), 4);
    fx_region(FXDATA(0x8c9560), 0x40);          /* draw list */
    fx_region(FXDATA(0x8c9770), 0x98);          /* iris, flags, surfaces, pending, rendered set ... 0x8c9808 */
    fx_region(FXDATA(0x8ca758), 4); fx_region(FXDATA(0x90563c), 4); fx_region(FXDATA(0x905ac0), 4);
    for (i = 0; i < n; i++) {
        unsigned seed = (unsigned)fx_rnd();
        unsigned short pc = (unsigned short)(R(3) == 0 ? 0 : R(2) ? 2 : 3);
        int pass;
        randomize();
        mode_effects = R(3) != 0;
        modes[FXU32(0x8a8c40)]++;
        if ((FXU32(0x8c9798) & 4) && FXU32(0x8a8c40) != 3 && FXU32(0x8a8c40) != 4 && FXU32(0x8a8c40) != 0) iris++;
        actors_drawn += FXU32(0x8a952c);
        fx_save();
        for (pass = 0; pass < 2; pass++) {
            eseed = seed; posq = -1; fx_nlog = 0;
            set_fpu_pc(pc);
            if (pass) sputRender_Update(); else orig_sputRender_Update();
            set_fpu_pc(3);
            if (pass == 0) { fx_snap_a(); fx_restore(); }
        }
        for (int k = 0; k < fx_nlog && k < FX_MAXLOG; k++) tagcount[fx_log[k].tag & 63]++;
        if (fx_cmp_a()) fx_fail("mem", i);
        if (fx_cmp_log()) fx_fail("log", i);
        fx_cases++;
    }
    printf("renderframe_test: %ld cases (modes 0..5: %ld %ld %ld %ld %ld %ld; iris %ld; list entries %ld), %ld differences\n",
           fx_cases, modes[0], modes[1], modes[2], modes[3], modes[4], modes[5], iris, actors_drawn, fx_fails);
    printf("  calls: switch %ld, user paint %ld, present %ld, printstack %ld, dirty add %ld, matrix %ld, costumes %ld, "
           "screen box %ld, colormap assert %ld, sector debug %ld, grid %ld, lights %ld, cameras %ld, iris %ld, invalidate %ld\n",
           tagcount[T_SWITCH], tagcount[T_USERPAINT], tagcount[T_PRESENT], tagcount[T_PRINTSTACK], tagcount[T_DRADD],
           tagcount[T_MATRIX], tagcount[T_DRAWCOS], tagcount[T_SCREENBOX], tagcount[T_ASSERT], tagcount[T_SECTORDBG],
           tagcount[T_GRID], tagcount[T_LIGHTS], tagcount[T_CAMS], tagcount[T_IRIS], tagcount[T_INVRECT]);
    return fx_fails != 0;
}
