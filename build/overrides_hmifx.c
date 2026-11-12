/* HMI's "Infinite Audio" effects library, rebuilt in C: what IMUSE.DLL imports from HMIFXLIB.DLL, and the three effects of
 * HMIFXFP.DLL that the game's preset file IMUSE.PSL uses (Reverb 1, Filter 1, Phasor).  With it the rebuilt imuse.dll needs
 * neither DLL, nor HMILIBS.INI (which only told HMIFXLIB.DLL to load HMIFXFP.DLL).  IMUSE.PSL is built in; a file of that
 * name in the working directory still wins, as it is the file the original reads.
 *
 * What the game uses: ImSetVoiceEffect("Intercom Filter") in the sets cf and nq (and "OFF"); the voice then goes through
 * Filter 1 as a band-pass (1326 Hz, 2000 Hz wide).  The two reverb presets and "Stereo Ring Modulator" (a Phasor) are
 * defined by IMUSE.PSL but called by no script.
 *
 * Written from the two DLLs of the v1.01 install (Ghidra's decompilation, and the x87 instruction order for every
 * floating-point expression): `long double` is a value the original kept on the x87 stack, `float` one it stored, so the
 * rounding happens at the same points and the samples come out the same bit for bit, under any x87 precision setting the
 * process runs with (tools/hmifx_check.c compares them with the DLLs').  The structures keep the original layouts: IMUSE.DLL
 * reads a preset's effect list (+0x450) and an effect's routing (+0x0c) and link (+0x18) itself (FUN_10004750), and it
 * hands over its own system block (+0x08 heap size, +0x10 / +0x14 allocator) and process block (DAT_1002dd08).
 *
 * The exports are __stdcall, except hmiFXMalloc / hmiFXFree, which are cdecl (in the DLL and at IMUSE.DLL's call sites).
 * Left out, as no path of IMUSE.DLL reaches them: the other six effects of HMIFXFP.DLL (Mono and Stereo Delay, Reverb 2,
 * Ring Modulator, Envelope, Resonator: a preset naming one fails to load with error 7, as an unknown effect does in the
 * original), the effects' parameter getters and editor windows, 8-bit samples (iMUSE always hands 16-bit ones), and the
 * fifteen exports IMUSE.DLL does not import.  Two quirks are kept: the right output buffer of a chain of two or more
 * effects is swapped wrongly (`out_r`, see pfx_swap), and the mono reverb repeats the first input sample while its
 * pre-delay runs (the stereo one does not).
 *
 * Compiled by build/link.py for every program like the other overrides_*.c files; only IMUSE.DLL gets the code
 * (GRIM_IMUSE).  tools/hmifx_check.c includes it with HMIFX_STANDALONE. */
#if defined(GRIM_IMUSE) || defined(HMIFX_STANDALONE)
#include <stdint.h>

/* ---- what this file needs from the host: msvcrt and kernel32, by their link names ---- */
extern double hfx_strtod(const char *, char **) __asm__("_strtod");
extern double hfx_pow(double, double) __asm__("_pow");
extern int hfx_stricmp(const char *, const char *) __asm__("__stricmp");
extern void *__attribute__((stdcall)) hfx_CreateFileA(const char *, uint32_t, uint32_t, void *, uint32_t, uint32_t, void *)
    __asm__("_CreateFileA@28");
extern int __attribute__((stdcall)) hfx_ReadFile(void *, void *, uint32_t, uint32_t *, void *) __asm__("_ReadFile@20");
extern uint32_t __attribute__((stdcall)) hfx_GetFileSize(void *, uint32_t *) __asm__("_GetFileSize@8");
extern int __attribute__((stdcall)) hfx_CloseHandle(void *) __asm__("_CloseHandle@4");
extern void *__attribute__((stdcall)) hfx_GetProcessHeap(void) __asm__("_GetProcessHeap@0");
extern void *__attribute__((stdcall)) hfx_HeapAlloc(void *, uint32_t, uint32_t) __asm__("_HeapAlloc@12");
extern int __attribute__((stdcall)) hfx_HeapFree(void *, uint32_t, void *) __asm__("_HeapFree@12");

#define HFX_STD __attribute__((stdcall))

/* ---- the structures (offsets as in the DLLs) ---- */
typedef struct __attribute__((packed)) HmiWaveFmt {   /* WAVEFORMATEX */
    uint16_t tag;            /* 0x00 */
    uint16_t channels;       /* 0x02 */
    uint32_t rate;           /* 0x04 */
    uint32_t bytes_per_sec;  /* 0x08 */
    uint16_t block_align;    /* 0x0c */
    uint16_t bits;           /* 0x0e */
    uint16_t extra;          /* 0x10 */
} HmiWaveFmt;

typedef struct HmiFxSystem {   /* the caller's block (IMUSE.DLL: DAT_1002dd48) */
    uint32_t unused[2];
    uint32_t heap_size;        /* 0x08 */
    uint8_t *heap;             /* 0x0c: allocated by hmiFXInitSystem */
    void *(*alloc)(uint32_t);  /* 0x10: cdecl; with free, replaces the C runtime's */
    void (*release)(void *);   /* 0x14 */
} HmiFxSystem;

struct HmiFxPreset;
struct HmiFxEffect;
typedef struct HmiFxIface {   /* one effect type (HMIFXFP.DLL's table at 0x10012a70) */
    uint32_t id;
    uint32_t size;                                                 /* of an instance */
    int (*init)(struct HmiFxPreset *, struct HmiFxEffect *);      /* slot 0: allocates */
    int (*done)(struct HmiFxPreset *, struct HmiFxEffect *);      /* slot 1: frees */
    int (*tail)(struct HmiFxEffect *, uint32_t *);                /* slot 2: ms it rings on after the input, or 0 */
    int (*process)(struct HmiFxPreset *, struct HmiFxEffect *);   /* slot 4 */
    int (*reset)(struct HmiFxPreset *, struct HmiFxEffect *);     /* slot 5: coefficients, clears the state */
    int (*set)(struct HmiFxEffect *, uint32_t, float);            /* slot 7 */
} HmiFxIface;

typedef struct HmiFxEffect {   /* the head of every effect instance */
    uint32_t unused;             /* 0x00 */
    int32_t chan_in;             /* 0x04: the three numbers after the id in IMUSE.PSL: 0, */
    int32_t chan_out;            /* 0x08: -1, */
    uint32_t routing;            /* 0x0c: 1 (1: mono, 2: stereo; the last effect's decides the output's channels) */
    uint32_t length;             /* 0x10: samples of the coming pass, set before reset */
    const HmiFxIface *iface;     /* 0x14 */
    struct HmiFxEffect *next;    /* 0x18 */
} HmiFxEffect;

typedef struct HmiFxPreset {
    uint32_t flags;              /* 0x000: 0x80000000 locked (instances from hmiFXMalloc), 0x20000000 reset since */
    char name[0x40];             /* 0x004 */
    uint32_t block_ms;           /* 0x044: 200 */
    float *in_l, *in_r;          /* 0x048 */
    float *out_l, *out_r;        /* 0x050 */
    float *buf_l[2], *buf_r[2];  /* 0x058 */
    uint32_t pingpong;           /* 0x068 */
    uint32_t block;              /* 0x06c: samples per pass */
    uint32_t count;              /* 0x070: samples in this pass */
    uint32_t locks;              /* 0x074 */
    uint32_t heap_used;          /* 0x078 */
    uint8_t unused[0x450 - 0x7c];
    HmiFxEffect *effects;        /* 0x450 */
    HmiWaveFmt *out_fmt;         /* 0x454 */
    HmiWaveFmt *in_fmt;          /* 0x458 */
    struct HmiFxPreset *next;    /* 0x45c */
} HmiFxPreset;

typedef struct HmiFxLibrary {
    char description[0x40];      /* 0x00 */
    char author[0x40];           /* 0x40 */
    uint8_t unused[0x14];
    HmiFxPreset *presets;        /* 0x94: the last one of the file first */
    HmiWaveFmt in_fmt;           /* 0x98: [INPUTFMT] */
    HmiWaveFmt out_fmt;          /* 0xaa: [OUTPUTFMT] */
} HmiFxLibrary;

typedef struct HmiFxProcess {   /* the caller's block (IMUSE.DLL: DAT_1002dd08) */
    uint32_t flags;              /* 0x00: see hmiFX_PresetProcess */
    HmiFxPreset *preset;         /* 0x04 */
    const char *name;            /* 0x08 */
    uint8_t *out;                /* 0x0c */
    uint32_t out_bytes;          /* 0x10 */
    const uint8_t *in;           /* 0x14 */
    uint32_t in_bytes;           /* 0x18 */
    HmiWaveFmt *in_fmt;          /* 0x1c */
    HmiWaveFmt *out_fmt;         /* 0x20 */
} HmiFxProcess;

_Static_assert(sizeof(HmiWaveFmt) == 0x12, "HmiWaveFmt");
_Static_assert(sizeof(HmiFxEffect) == 0x1c, "HmiFxEffect");
_Static_assert(sizeof(HmiFxPreset) == 0x460, "HmiFxPreset");
_Static_assert(sizeof(HmiFxLibrary) == 0xbc, "HmiFxLibrary");
_Static_assert(sizeof(HmiFxProcess) == 0x24, "HmiFxProcess");

/* ---- the x87 operations the original uses as such ---- */
static long double hfx_tan(long double x)   /* fptan (pushes 1.0, which the original never uses) */
{
    long double r;
    __asm__("fptan\n\tfstp %%st(0)" : "=t"(r) : "0"(x));
    return r;
}
static long double hfx_cos(long double x)
{
    long double r;
    __asm__("fcos" : "=t"(r) : "0"(x));
    return r;
}
static long double hfx_sqrt(long double x)
{
    long double r;
    __asm__("fsqrt" : "=t"(r) : "0"(x));
    return r;
}
static long double hfx_ln(long double x)   /* fldln2, fyl2x */
{
    long double r;
    __asm__("fldln2\n\tfxch %%st(1)\n\tfyl2x" : "=t"(r) : "0"(x));
    return r;
}
static int32_t hfx_ftol(long double x)   /* MSVC's __ftol: truncate, to 64 bits, keep the low half */
{
    return (int32_t)(int64_t)x;
}
static int32_t hfx_fistp(float f)   /* fistp dword in the current rounding mode */
{
    int32_t r;
    __asm__("fistpl %0" : "=m"(r) : "t"(f) : "st");
    return r;
}
static int16_t hfx_fistp16(float f)   /* fistp word */
{
    int16_t r;
    __asm__("fistps %0" : "=m"(r) : "t"(f) : "st");
    return r;
}

/* ---- allocation ---- */
static void *(*g_alloc)(uint32_t);
static void (*g_release)(void *);
static uint8_t *g_heap_base, *g_heap_cur, *g_heap_end;   /* the caller's heap: carved, never freed, reset per preset */
static uint32_t g_heap_size;

static void *hfx_default_alloc(uint32_t n) { return hfx_HeapAlloc(hfx_GetProcessHeap(), 0, n); }
static void hfx_default_release(void *p) { if (p) hfx_HeapFree(hfx_GetProcessHeap(), 0, p); }

void *hmiFX_Malloc(uint32_t n) __asm__("_hmiFXMalloc");
void *hmiFX_Malloc(uint32_t n) { return g_alloc(n); }
void hmiFX_Free(void *p) __asm__("_hmiFXFree");
void hmiFX_Free(void *p) { g_release(p); }

static void *heap_alloc(uint32_t n)
{
    uint8_t *p = g_heap_cur;
    if (g_heap_end < g_heap_cur + n)
        return 0;
    g_heap_cur += n;
    return p;
}
static void heap_reset(void) { g_heap_cur = g_heap_base; }

static void zero(void *p, uint32_t n)
{
    uint8_t *b = p;
    while (n--)
        *b++ = 0;
}

/* ==== Filter 1 (effect 2300): a biquad, low-pass / high-pass / band-pass / band-reject ==== */
typedef struct FxFilter {
    HmiFxEffect h;
    int32_t type;                      /* 0x1c: 0x400 low-pass, 0x401 high-pass, 0x402 band-pass, 0x403 band-reject */
    float cutoff;                      /* 0x20: Hz (low / high-pass) */
    float centre;                      /* 0x24: Hz (band) */
    float width;                       /* 0x28: Hz (band) */
    float a0, a1, a2, b1, b2;          /* 0x2c */
    float x1, x2, y1, y2;              /* 0x40 */
    float unused[4];                   /* 0x50: cleared by reset */
} FxFilter;
_Static_assert(sizeof(FxFilter) == 0x60, "FxFilter");

static int filter_nothing(HmiFxPreset *p, HmiFxEffect *e) { (void)p; (void)e; return 0; }

static int filter_reset(HmiFxPreset *p, HmiFxEffect *e)
{
    FxFilter *f = (FxFilter *)e;
    uint32_t rate = p->in_fmt->rate;
    long double c, cc, t, a, w, x;
    double cs2;
    float cf, af;

    f->x1 = f->x2 = f->y1 = f->y2 = 0;
    f->unused[0] = f->unused[1] = f->unused[2] = f->unused[3] = 0;
    switch (f->type) {
    case 0x400:   /* low-pass: Butterworth, cut-off at most half the rate */
    case 0x401:   /* high-pass */
        if ((long double)(uint64_t)(rate >> 1) <= (long double)f->cutoff)
            t = (long double)(uint64_t)(rate >> 1) * 3.14159265 / (long double)(int32_t)rate;
        else
            t = (long double)f->cutoff * 3.14159265 / (long double)(int32_t)rate;
        c = hfx_tan(t);
        if (f->type == 0x400)
            c = 1.0 / c;
        cc = c * c;
        cs2 = (double)(c * hfx_sqrt(2.0));   /* (stored as a double on the stack) */
        a = 1.0 / ((cc + cs2) - -1.0);
        af = (float)a;
        f->a0 = af;
        f->a1 = f->type == 0x400 ? (float)((long double)af + af) : (float)((long double)af * -2.0);
        f->a2 = af;
        x = (f->type == 0x400 ? 1.0 - cc : cc - 1.0) * a;
        f->b1 = (float)(x + x);
        f->b2 = (float)((cc - ((long double)cs2 - 1.0)) * af);
        return 0;
    case 0x402:   /* band-pass */
        f->a1 = 0;
        c = 1.0 / hfx_tan((long double)f->width * 3.14159265 / (long double)(uint64_t)rate);
        w = hfx_cos((long double)f->centre * 6.2831853 / (long double)(uint64_t)rate);
        cf = (float)c;
        a = 1.0 / (c - -1.0);
        af = (float)a;
        f->a0 = af;
        f->a2 = -af;
        f->b1 = (float)-((w + w) * cf * af);
        f->b2 = (float)(((long double)cf - 1.0) * af);
        return 0;
    case 0x403: {   /* band-reject */
        float tf = (float)hfx_tan((long double)f->width * 3.14159265 / (long double)(uint64_t)rate);
        w = hfx_cos((long double)f->centre * 6.2831853 / (long double)(uint64_t)rate);
        a = 1.0 / ((long double)tf - -1.0);
        af = (float)a;
        x = -((w + w) * af);
        f->a0 = af;
        f->a1 = (float)x;
        f->a2 = af;
        f->b1 = (float)x;
        f->b2 = (float)((1.0 - (long double)tf) * af);
        return 0;
    }
    }
    return 0;
}

static int filter_process(HmiFxPreset *p, HmiFxEffect *e)
{
    FxFilter *f = (FxFilter *)e;
    const float *in = p->in_l;
    float *out = p->out_l;
    uint32_t n;
    for (n = p->count; n != 0; n--) {
        float x = *in++;
        long double y = (long double)x * f->a0 + (long double)f->x1 * f->a1;
        float yf;
        y = y + (long double)f->x2 * f->a2;
        y = y - (long double)f->b1 * f->y1;
        y = y - (long double)f->y2 * f->b2;
        yf = (float)y;
        *out++ = yf;
        f->x2 = f->x1;
        f->x1 = x;
        f->y2 = f->y1;
        f->y1 = yf;
    }
    return 0;
}

static int filter_set(HmiFxEffect *e, uint32_t i, float v)
{
    FxFilter *f = (FxFilter *)e;
    switch (i) {
    case 0: f->type = hfx_ftol(v); return 0;
    case 1: f->cutoff = v; return 0;
    case 2: f->centre = v; return 0;
    case 3: f->width = v; return 0;
    }
    return 0xb;
}

/* ==== Reverb 1 (effect 2101): three all-pass delay lines in a row (four for stereo) ==== */
typedef struct FxDelayLine {
    float *buf;                        /* +0x00 */
    int32_t wr, rd, len;               /* +0x04 */
    float out;                         /* +0x10: the last sample read */
    int32_t unused;
} FxDelayLine;

typedef struct FxReverb {
    HmiFxEffect h;
    float max_ms;                      /* 0x1c: sizes the lines */
    float delay_ms;                    /* 0x20 */
    float predelay_ms;                 /* 0x24 */
    int32_t predelay;                  /* 0x28: samples still to go */
    int32_t line_bytes;                /* 0x2c */
    FxDelayLine line[4];               /* 0x30 */
    float dry, wet;                    /* 0x90 */
} FxReverb;
_Static_assert(sizeof(FxReverb) == 0x98, "FxReverb");

static const uint32_t reverb_scale_bits[4] = { 0x3e289507, 0x3f037069, 0x3f800000, 0x3f549a99 };  /* 0.165 0.513 1 0.830 */

static int reverb_init(HmiFxPreset *p, HmiFxEffect *e)
{
    FxReverb *r = (FxReverb *)e;
    int32_t bytes = hfx_ftol((long double)(uint64_t)p->in_fmt->rate * r->max_ms * 0.001) << 2;
    int i;
    r->line_bytes = bytes;
    for (i = 0; i < 4; i++) {
        void *b = (p->flags & 0x80000000) ? hmiFX_Malloc(bytes) : heap_alloc(bytes);
        r->line[i].buf = b;
        if (!b)
            return 1;
    }
    return 0;
}

static int reverb_done(HmiFxPreset *p, HmiFxEffect *e)
{
    FxReverb *r = (FxReverb *)e;
    int i;
    for (i = 0; i < 4; i++)
        if (p->flags & 0x80000000)
            hmiFX_Free(r->line[i].buf);   /* (heap blocks: hmiFXHeapFree, which does nothing) */
    return 0;
}

static int reverb_reset(HmiFxPreset *p, HmiFxEffect *e)
{
    FxReverb *r = (FxReverb *)e;
    long double base = (long double)(uint64_t)p->in_fmt->rate * r->delay_ms * 0.001;
    int i;
    for (i = 0; i < 4; i++) {
        union { uint32_t u; float f; } s = { reverb_scale_bits[i] };
        long double t = base * s.f;
        zero(r->line[i].buf, r->line_bytes);
        r->line[i].len = hfx_ftol(t) - 2;
        r->line[i].wr = 0;
        r->line[i].rd = hfx_ftol(t * 0.5f);
        r->line[i].out = 0;
    }
    r->predelay = hfx_ftol((long double)(uint64_t)p->in_fmt->rate * r->predelay_ms * 0.001);
    return 0;
}

static int reverb_tail(HmiFxEffect *e, uint32_t *ms)   /* until the loop has fallen by 60 dB (0.7 ^ n = 0.001), / 3 */
{
    FxReverb *r = (FxReverb *)e;
    long double k = hfx_ln(0.001) / hfx_ln(0.7);
    *ms = (uint32_t)hfx_ftol(k * ((long double)r->delay_ms * 0.001) * 1000.0) / 3;
    return 0;
}

/* one all-pass step of a line: write `v`, take the sample that comes out */
static void line_step(FxDelayLine *l, float v)
{
    l->buf[l->wr] = v;
    if (++l->wr == l->len)
        l->wr = 0;
    l->out = l->buf[l->rd];
    if (++l->rd == l->len)
        l->rd = 0;
}

static int reverb_process(HmiFxPreset *p, HmiFxEffect *e)
{
    FxReverb *r = (FxReverb *)e;
    FxDelayLine *A = &r->line[0], *B = &r->line[1], *C = &r->line[2], *D = &r->line[3];
    const float *in = p->in_l;
    uint32_t n = p->count;

    if (e->routing & 1) {   /* mono */
        float *out = p->out_l;
        for (; r->predelay != 0 && n != 0; n--) {
            *out++ = (float)((long double)r->wet * *in);   /* (the input does not advance) */
            r->predelay--;
        }
        for (; n != 0; n--) {
            float x = *in++, a = A->out, b, t;
            long double s1 = (long double)a * 0.7 + x, s2;
            line_step(A, (float)s1);
            b = B->out;
            t = (float)((long double)a + s1 * -0.7);
            s2 = (long double)b * 0.7 + t;
            line_step(B, (float)s2);
            line_step(C, (float)((s2 * -0.7 + b) + (long double)C->out * 0.62));
            *out++ = (float)((long double)x * r->dry + (long double)C->out * r->wet);
        }
    }
    if (e->routing & 2) {   /* stereo: a fourth line for the right channel */
        float *out_l = p->out_l, *out_r = p->out_r;
        in = p->in_l;
        n = p->count;
        for (; r->predelay != 0 && n != 0; n--) {
            *out_l++ = (float)((long double)*in * r->wet);
            *out_r++ = (float)((long double)*in * r->wet);
            in++;
            r->predelay--;
        }
        for (; n != 0; n--) {
            float x = *in++, a = A->out, b, t, mf, cw;
            long double s1 = (long double)a * 0.7 + x, s2, m;
            line_step(A, (float)s1);
            b = B->out;
            t = (float)((long double)a + s1 * -0.7);
            s2 = (long double)b * 0.7 + t;
            line_step(B, (float)s2);
            m = b + s2 * -0.7;
            mf = (float)m;
            {
                long double dn = (long double)D->out * -0.71;
                line_step(C, (float)((long double)C->out * 0.62 + m));
                cw = (float)((long double)C->out * r->wet);
                line_step(D, (float)(dn + mf));
            }
            {
                long double xd = (long double)x * r->dry;
                *out_l++ = (float)(xd + cw);
                *out_r++ = (float)((long double)D->out * r->wet + xd);
            }
        }
    }
    return 0;
}

static int reverb_set(HmiFxEffect *e, uint32_t i, float v)
{
    FxReverb *r = (FxReverb *)e;
    switch (i) {
    case 0: r->max_ms = v; return 0;
    case 1: r->predelay_ms = v; return 0;
    case 2: r->delay_ms = v; return 0;
    case 3: r->dry = v; return 0;
    case 4: r->wet = v; return 0;
    }
    return 0xb;
}

/* ==== Phasor (effect 2375): four first-order all-passes whose frequency sweeps up and down ==== */
typedef struct FxPhasor {
    HmiFxEffect h;
    float feedback;                    /* 0x1c */
    float sweep;                       /* 0x20: octaves per second... as a rate, see reset */
    float depth;                       /* 0x24: octaves */
    float freq;                        /* 0x28: Hz, the bottom of the sweep */
    float dry, wet;                    /* 0x2c */
    float w;                           /* 0x34: current all-pass frequency (pi f / rate) */
    float s[8];                        /* 0x38: all-pass state: in / out of the four stages */
    float step;                        /* 0x58: factor applied to w per sample */
    float span;                        /* 0x5c: 2 ^ depth */
    float rate_up;                     /* 0x60 */
    float w_min, w_max;                /* 0x64 */
} FxPhasor;
_Static_assert(sizeof(FxPhasor) == 0x6c, "FxPhasor");

static int phasor_reset(HmiFxPreset *p, HmiFxEffect *e)
{
    FxPhasor *f = (FxPhasor *)e;
    uint32_t rate = p->in_fmt->rate;
    long double w = (long double)f->freq * 3.14159265 / (long double)(uint64_t)rate;
    float span, q;
    int i;
    f->w = (float)w;
    f->w_min = (float)w;
    span = (float)hfx_pow(2.0, f->depth);
    f->span = span;
    f->w_max = (float)((long double)f->freq * span * 3.14159265 / (long double)(uint64_t)rate);
    q = (float)hfx_pow(span, (double)((long double)f->sweep / (long double)(uint64_t)(rate >> 1)));
    f->rate_up = q;
    f->step = q;
    for (i = 0; i < 8; i++)
        f->s[i] = 0;
    return 0;
}

static int phasor_process(HmiFxPreset *p, HmiFxEffect *e)
{
    FxPhasor *f = (FxPhasor *)e;
    const float *in = p->in_l;
    float *out = p->out_l;
    float *s = f->s;   /* s[0] 0x38, s[1] 0x3c, ... s[7] 0x54 */
    uint32_t n;
    for (n = p->count; n != 0; n--) {
        float x = *in++, kf, s4c = s[5], s54 = s[7];
        long double k = (1.0 - (long double)f->w) / ((long double)f->w - -1.0);
        long double u, v, m;
        kf = (float)k;
        u = (long double)s54 * f->feedback + x;
        v = (u + s[1]) * kf - s[0];
        s[0] = (float)u;
        s[1] = (float)v;
        v = ((long double)s[1] + s[3]) * kf - s[2];
        s[2] = s[1];
        s[3] = (float)v;
        v = ((long double)s4c + s[3]) * kf - s[4];
        s[4] = s[3];
        s[5] = (float)v;
        v = ((long double)s54 + s[5]) * kf - s[6];
        s[6] = s[5];
        s[7] = (float)v;
        *out++ = (float)((long double)x * f->dry + (long double)f->wet * s[7]);
        m = (long double)f->step * f->w;
        f->w = (float)m;
        if (m > f->w_max)
            f->step = (float)(1.0 / (long double)f->rate_up);
        else if (!(m >= f->w_min))
            f->step = f->rate_up;
    }
    return 0;
}

static int phasor_set(HmiFxEffect *e, uint32_t i, float v)
{
    FxPhasor *f = (FxPhasor *)e;
    switch (i) {
    case 0: f->feedback = v; return 0;
    case 1: f->sweep = v; return 0;
    case 2: f->depth = v; return 0;
    case 3: f->freq = v; return 0;
    case 4: f->dry = v; return 0;
    case 5: f->wet = v; return 0;
    }
    return 0xb;
}

static const HmiFxIface hfx_ifaces[] = {
    { 2101, sizeof(FxReverb), reverb_init, reverb_done, reverb_tail, reverb_process, reverb_reset, reverb_set },
    { 2300, sizeof(FxFilter), filter_nothing, filter_nothing, 0, filter_process, filter_reset, filter_set },
    { 2375, sizeof(FxPhasor), filter_nothing, filter_nothing, 0, phasor_process, phasor_reset, phasor_set },
};

static const HmiFxIface *find_iface(uint32_t id)
{
    unsigned i;
    for (i = 0; i < sizeof hfx_ifaces / sizeof hfx_ifaces[0]; i++)
        if (hfx_ifaces[i].id == id)
            return &hfx_ifaces[i];
    return 0;
}

/* ==== the library ==== */
static int g_effects_loaded;   /* HMIFXFP.DLL was loaded (from hmiFXInitSystem to hmiFXUnInitSystem) */

int HFX_STD hmiFX_InitSystem(HmiFxSystem *sys) __asm__("_hmiFXInitSystem");
int HFX_STD hmiFX_InitSystem(HmiFxSystem *sys)
{
    /* The DLL first read HMILIBS.INI and loaded the effect DLLs it lists (error 10 if that failed): HMIFXFP.DLL, whose C
     * runtime start-up sets the x87 precision to 53 bits (_controlfp(_PC_53, _MCW_PC)) for the calling thread, when the
     * load is the first one since hmiFXUnInitSystem freed it.  Measured: CW 0x007f -> 0x027f, 0x0c7f -> 0x0e7f. */
    if (!g_effects_loaded) {
        uint16_t cw;
        __asm__ volatile("fnstcw %0" : "=m"(cw));
        cw = (uint16_t)((cw & ~0x300) | 0x200);
        __asm__ volatile("fldcw %0" : : "m"(cw));
        g_effects_loaded = 1;
    }
    g_alloc = sys->alloc;
    if (g_alloc == 0 || sys->release == 0) {
        g_alloc = hfx_default_alloc;
        g_release = hfx_default_release;
    } else {
        g_release = sys->release;
    }
    sys->heap = hmiFX_Malloc(sys->heap_size);
    if (!sys->heap)
        return 1;
    g_heap_base = g_heap_cur = sys->heap;
    g_heap_size = sys->heap_size;
    g_heap_end = sys->heap + sys->heap_size;
    return 0;
}

int HFX_STD hmiFX_UnInitSystem(HmiFxSystem *sys) __asm__("_hmiFXUnInitSystem");
int HFX_STD hmiFX_UnInitSystem(HmiFxSystem *sys)
{
    g_effects_loaded = 0;   /* (FreeLibrary of the effect DLLs) */
    if (sys->heap)
        hmiFX_Free(sys->heap);
    return 0;
}

static int preset_create(HmiFxPreset *p)   /* hmiFXPresetCreate: the four float buffers */
{
    uint32_t n, sz;
    uint8_t *b;
    heap_reset();
    n = (p->block_ms * p->in_fmt->rate) / 1000;
    sz = n * 4 + 0x400;
    p->block = n;
    b = (p->flags & 0x80000000) ? hmiFX_Malloc(sz * 4) : heap_alloc(sz * 4);
    if (!b)
        return 1;
    p->buf_l[0] = p->in_l = (float *)b;
    p->buf_l[1] = p->out_l = (float *)(b + sz);
    p->buf_r[0] = p->in_r = (float *)(b + sz * 2);
    p->buf_r[1] = p->out_r = (float *)(b + sz * 3);
    p->pingpong = 0;
    p->effects = 0;
    return 0;
}

/* ---- the preset file: the DLL's own INI reader, as far as a well-formed file needs it ---- */
typedef struct Ini {
    const char *text, *end;
    const char *section;   /* after the line of the current [section] */
    const char *value;     /* after the `=` of the current key */
    const char *field;     /* the next comma-separated field of it */
} Ini;

static int ini_section(Ini *ini, const char *name)
{
    const char *s;
    for (s = ini->text; s < ini->end; s++) {
        const char *a = s + 1, *b = name;
        if (*s != '[')
            continue;
        while (*b && a < ini->end && *a == *b)
            a++, b++;
        if (*b == 0 && a < ini->end && *a == ']') {
            while (a < ini->end && *a != '\n')
                a++;
            ini->section = a + 1;
            return 1;
        }
    }
    return 0;
}

static int ini_key(Ini *ini, const char *name)   /* the first match from the section start to the next `[` */
{
    const char *s;
    for (s = ini->section; s < ini->end && *s != '['; s++) {
        const char *a = s, *b = name;
        while (*b && a < ini->end && *a == *b)
            a++, b++;
        if (*b)
            continue;
        while (a < ini->end && *a != '=' && *a != '\r')
            a++;
        ini->value = (a < ini->end && *a == '=') ? a + 1 : 0;
        ini->field = 0;
        return 1;
    }
    return 0;
}

static const char *ini_cursor(Ini *ini) { return ini->field ? ini->field : ini->value; }

static int ini_int(Ini *ini, int32_t *out)   /* a field as a number (decimal, or 0x hex) */
{
    const char *s = ini_cursor(ini);
    char tok[32];
    int n = 0;
    if (!s)
        return 0;
    while (*s == ' ')
        s++;
    if (*s == '\r' || *s == 0)
        return 0;
    while (*s != ',' && *s != ' ' && *s != '\r' && *s != 0 && n < 31)
        tok[n++] = *s++;
    tok[n] = 0;
    while (*s == ' ')
        s++;
    if (*s == ',')
        s++;
    ini->field = s;
    if (tok[1] == 'x') {
        int32_t v = 0;
        const char *t;
        for (t = tok + 2; *t; t++) {
            int c = *t, d = c >= '0' && c <= '9' ? c - '0' : c >= 'a' && c <= 'f' ? c - 'a' + 10
                          : c >= 'A' && c <= 'F' ? c - 'A' + 10 : -1;
            v = v * 16 + d;
        }
        *out = v;
    } else {   /* atoi */
        const char *t = tok;
        int32_t v = 0, neg = 0;
        while (*t == ' ' || *t == '\t')
            t++;
        if (*t == '-' || *t == '+')
            neg = *t++ == '-';
        while (*t >= '0' && *t <= '9')
            v = v * 10 + (*t++ - '0');
        *out = neg ? -v : v;
    }
    return 1;
}

static int ini_string(Ini *ini, char *out, uint32_t max)   /* a field as text (`"..."` with `""`, or up to a comma) */
{
    const char *s = ini_cursor(ini);
    uint32_t n = 0;
    if (!s)
        return 0;
    while (*s == ' ')
        s++;
    if (*s == '"') {
        s++;
        while (*s != '\r' && *s != 0 && n < max - 1) {
            if (*s == '"') {
                if (s[1] != '"') {
                    s++;
                    break;
                }
                s++;
            }
            out[n++] = *s++;
        }
    } else {
        while (*s != '\r' && *s != ',' && *s != 0 && n < max - 1)
            out[n++] = *s++;
    }
    out[n] = 0;
    if (n == max - 1)
        while (*s != '\r' && *s != ',' && *s != 0)
            s++;
    ini->field = *s == ',' ? s + 1 : s;
    return 1;
}

static int ini_get_int(Ini *ini, const char *key, int32_t *out) { return ini_key(ini, key) && ini_int(ini, out); }
static int ini_get_string(Ini *ini, const char *key, char *out, uint32_t max)
{
    return ini_key(ini, key) && ini_string(ini, out, max);
}

static void query_string(char *out, const char *prefix, uint32_t n)   /* hmiFXGenerateQueryString: "PRESET0003" */
{
    while (*prefix)
        *out++ = *prefix++;
    out[0] = '0' + n / 1000 % 10;
    out[1] = '0' + n / 100 % 10;
    out[2] = '0' + n / 10 % 10;
    out[3] = '0' + n % 10;
    out[4] = 0;
}

static const char hfx_builtin_psl[] =    /* the text of IMUSE.PSL: not in the repository */
    "";

static char *read_file(const char *path, uint32_t *len)   /* the whole file, NUL-terminated, or 0 */
{
    void *h = hfx_CreateFileA(path, 0x80000000, 1, 0, 3, 0x80, 0);   /* GENERIC_READ, share read, OPEN_EXISTING */
    uint32_t size, got = 0;
    char *buf;
    if (h == (void *)-1)
        return 0;
    size = hfx_GetFileSize(h, 0);
    buf = size == 0xffffffff ? 0 : hfx_default_alloc(size + 1);
    if (buf && (!hfx_ReadFile(h, buf, size, &got, 0) || got != size)) {
        hfx_default_release(buf);
        buf = 0;
    }
    hfx_CloseHandle(h);
    if (buf) {
        buf[size] = 0;
        *len = size;
    }
    return buf;
}

static void wavefmt_read(Ini *ini, HmiWaveFmt *f)
{
    int32_t v = 0;
    uint32_t x;
    ini_get_int(ini, "Rate", &v);
    f->rate = v;
    ini_get_int(ini, "BitsPerSample", &v);
    f->bits = (uint16_t)v;
    ini_get_int(ini, "Channels", &v);
    f->channels = (uint16_t)v;
    f->tag = 1;
    x = (int32_t)(f->bits * f->channels) / 8;
    f->block_align = (uint16_t)x;
    f->bytes_per_sec = (x & 0xffff) * f->rate;
    f->extra = 0;
}

int HFX_STD hmiFX_PresetLoadLibrary(HmiFxLibrary **out, const char *path) __asm__("_hmiFXPresetLoadLibrary");
int HFX_STD hmiFX_PresetLoadLibrary(HmiFxLibrary **out, const char *path)
{
    uint32_t len = 0, np = 0;
    char *file = read_file(path, &len);
    HmiFxLibrary *lib;
    HmiFxPreset *last = 0;
    Ini ini;
    char key[16];
    int rc = 0;

    ini.text = file ? file : hfx_builtin_psl;
    ini.end = ini.text + (file ? len : sizeof hfx_builtin_psl - 1);
    ini.section = ini.value = ini.field = 0;
    lib = hmiFX_Malloc(sizeof *lib);
    if (!lib) {
        rc = 1;
        goto done;
    }
    zero(lib, sizeof *lib);
    if (ini_section(&ini, "LIBRARY")) {
        ini_get_string(&ini, "Description", lib->description, 0x40);
        ini_get_string(&ini, "Author", lib->author, 0x40);
    }
    if (ini_section(&ini, "INPUTFMT"))
        wavefmt_read(&ini, &lib->in_fmt);
    if (ini_section(&ini, "OUTPUTFMT"))
        wavefmt_read(&ini, &lib->out_fmt);
    for (query_string(key, "PRESET", np); ini_section(&ini, key); query_string(key, "PRESET", ++np)) {
        HmiFxPreset *p = hmiFX_Malloc(sizeof *p);
        uint32_t ne = 0;
        if (!p) {
            rc = 1;
            goto done_lib;
        }
        zero(p, sizeof *p);
        p->next = last;
        last = p;
        ini_get_string(&ini, "Description", p->name, 0x40);
        ini_get_int(&ini, "Flags", (int32_t *)&p->flags);
        p->in_fmt = &lib->in_fmt;
        p->out_fmt = &lib->out_fmt;
        p->block_ms = 200;
        if (preset_create(p)) {
            rc = 1;
            goto done_lib;
        }
        for (query_string(key, "Effect", ne); ini_key(&ini, key); query_string(key, "Effect", ++ne)) {
            int32_t id = 0;
            const HmiFxIface *fx;
            HmiFxEffect *e, **link;
            char num[0x40];
            uint32_t i = 0;
            ini_int(&ini, &id);
            fx = find_iface(id);
            if (!fx) {
                rc = 7;
                goto done_lib;
            }
            e = hmiFX_Malloc(fx->size);
            if (!e) {
                rc = 1;
                goto done_lib;
            }
            zero(e, fx->size);
            e->iface = fx;
            ini_int(&ini, &e->chan_in);
            ini_int(&ini, (int32_t *)&e->routing);
            ini_int(&ini, &e->chan_out);
            for (ini_string(&ini, num, 0x40); num[0]; ini_string(&ini, num, 0x40))
                fx->set(e, i++, (float)hfx_strtod(num, 0));
            rc = fx->init(p, e);
            if (rc)
                goto done_lib;
            for (link = &p->effects; *link; link = &(*link)->next)
                ;
            *link = e;
            e->next = 0;
            p->heap_used = g_heap_cur - g_heap_base;
        }
    }
    lib->presets = last;
    rc = last ? 0 : 0xc;
done_lib:
    *out = lib;
done:
    if (file)
        hfx_default_release(file);
    return rc;
}

int HFX_STD hmiFX_PresetFreeLibrary(HmiFxLibrary *lib) __asm__("_hmiFXPresetFreeLibrary");
int HFX_STD hmiFX_PresetFreeLibrary(HmiFxLibrary *lib)
{
    HmiFxPreset *p, *pn;
    if (!lib)
        return 0xc;
    for (p = lib->presets; p; p = pn) {
        HmiFxEffect *e, *en;
        for (e = p->effects; e; e = e->next)
            e->iface->done(p, e);
        if (p->flags & 0x80000000)
            hmiFX_Free(p->buf_l[0]);
        for (e = p->effects; e; e = en) {
            en = e->next;
            hmiFX_Free(e);
        }
        pn = p->next;
        hmiFX_Free(p);
    }
    hmiFX_Free(lib);
    return 0;
}

int HFX_STD hmiFX_PresetLock(HmiFxPreset *p) __asm__("_hmiFXPresetLock");
int HFX_STD hmiFX_PresetLock(HmiFxPreset *p)   /* from now on the instances are the preset's own (hmiFXMalloc) */
{
    HmiFxEffect *e;
    if (!p)
        return 0xf;
    if (p->locks != 0) {
        p->locks++;
        return 0;
    }
    p->locks = 1;
    p->flags &= 0x5fffffff;
    for (e = p->effects; e; e = e->next)
        e->iface->done(p, e);
    p->flags |= 0x80000000;
    for (e = p->effects; e; e = e->next)
        e->iface->init(p, e);
    return 0;
}

int HFX_STD hmiFX_PresetRelease(HmiFxPreset *p) __asm__("_hmiFXPresetRelease");
int HFX_STD hmiFX_PresetRelease(HmiFxPreset *p)   /* back to the shared heap */
{
    HmiFxEffect *e, *list;
    if (!p)
        return 0xf;
    if (--p->locks == 0) {
        for (e = p->effects; e; e = e->next)
            e->iface->done(p, e);
        list = p->effects;
        p->flags &= 0x7fffffff;
        preset_create(p);
        p->effects = list;
        for (e = list; e; e = e->next)
            e->iface->init(p, e);
    }
    return 0;
}

/* float buffers of a pass: 16-bit samples in, 16-bit samples out (rounded, clamped to +-0x7fff unless 0x400) */
static void pfx_in(HmiFxPreset *p, const uint8_t *src, uint32_t n)
{
    const int16_t *s = (const int16_t *)src;
    float *l = p->in_l, *r = p->in_r;
    if (p->in_fmt->bits != 16)
        return;
    if (p->in_fmt->channels == 1) {
        while (n--)
            *l++ = (float)*s++;
    } else {
        while (n--) {
            *l++ = (float)s[0];
            *r++ = (float)s[1];
            s += 2;
        }
    }
}

static int16_t clamp16(float f)
{
    int32_t v = hfx_fistp(f);
    return (int16_t)(v > 0x7fff ? 0x7fff : v < -0x7fff ? -0x7fff : v);
}

static void pfx_out(HmiFxPreset *p, uint8_t *dst, uint32_t n, int clamp)
{
    int16_t *d = (int16_t *)dst;
    const float *l = p->out_l, *r = p->out_r;
    if (p->out_fmt->bits != 16)
        return;
    if (p->out_fmt->channels == 1) {
        while (n--)
            *d++ = clamp ? clamp16(*l++) : hfx_fistp16(*l++);
    } else {
        while (n--) {
            d[0] = clamp ? clamp16(*l++) : hfx_fistp16(*l++);
            d[1] = clamp ? clamp16(*r++) : hfx_fistp16(*r++);
            d += 2;
        }
    }
}

static void pfx_chain(HmiFxPreset *p)   /* every effect on this pass, each reading what the one before wrote */
{
    HmiFxEffect *e = p->effects;
    while (e) {
        uint32_t old;
        e->iface->process(p, e);
        e = e->next;
        if (!e)
            break;
        old = p->pingpong;
        p->pingpong = old ^ 1;
        p->in_l = p->buf_l[p->pingpong];
        p->in_r = p->buf_r[p->pingpong];
        p->out_l = p->buf_l[old];
        p->out_r = p->buf_r[p->pingpong];   /* (sic: the right channel's output is its input) */
    }
}

/* flags: 0x20 find the preset named `name` (-> preset); otherwise run one: 1 the preset given, 2 the one named.
 *        8 / 0x10 / 0x200 use the caller's input / output format (0x200: filled in from the preset's routing);
 *        4 allocate the output (hmiFXMalloc, -> out, out_bytes); 0x40 only tell its size; 0x80 add the tail (always
 *        when not locked); 0x400 no clamping. */
int HFX_STD hmiFX_PresetProcess(HmiFxLibrary *lib, HmiFxProcess *pr) __asm__("_hmiFXPresetProcess");
int HFX_STD hmiFX_PresetProcess(HmiFxLibrary *lib, HmiFxProcess *pr)
{
    HmiFxPreset *p;
    HmiWaveFmt *saved_in = 0, *saved_out = 0;
    HmiFxEffect *e;
    uint32_t samples, tail, maxt = 0, t = 0, size;

    if (pr->flags & 0x20) {
        if (!lib->presets)
            return 0xc;
        pr->preset = 0;
        for (p = lib->presets; p; p = p->next)
            if (hfx_stricmp(p->name, pr->name) == 0) {
                pr->preset = p;
                return 0;
            }
        return 0xd;
    }
    if (pr->flags & 1) {
        p = pr->preset;
    } else if (pr->flags & 2) {
        if (!lib->presets)
            return 0xc;
        for (p = lib->presets; hfx_stricmp(p->name, pr->name) != 0; )
            if (!(p = p->next))
                return 0xd;
    } else {
        return 0xe;
    }
    if (!p->effects)
        return 6;
    if (pr->flags & 8) {
        saved_in = p->in_fmt;
        p->in_fmt = pr->in_fmt;
    }
    if (pr->flags & 0x10) {
        saved_out = p->out_fmt;
        p->out_fmt = pr->out_fmt;
    }
    if (pr->flags & 0x200) {
        HmiWaveFmt *f = pr->out_fmt;
        uint32_t ch, x;
        saved_out = p->out_fmt;
        p->out_fmt = f;
        for (e = p->effects; e->next; e = e->next)
            ;
        ch = (e->routing & 10) ? 2 : 1;
        f->channels = (uint16_t)ch;
        f->bits = p->in_fmt->bits;
        f->rate = p->in_fmt->rate;
        f->tag = 1;
        x = (int32_t)(p->in_fmt->bits * ch) / 8;
        f->block_align = (uint16_t)x;
        f->bytes_per_sec = p->in_fmt->rate * (x & 0xffff);
        f->extra = 0;
    }
    p->block = (p->block_ms * p->in_fmt->rate) / 1000;
    samples = pr->in_bytes / p->in_fmt->block_align;
    for (e = p->effects; e; e = e->next)
        if (e->iface->tail) {
            e->iface->tail(e, &t);
            if (maxt <= t)
                maxt = t;
        }
    if (!(p->flags & 0x80000000) || (pr->flags & 0x80))
        tail = hfx_ftol((long double)(uint64_t)p->in_fmt->rate * (int32_t)maxt * 0.001);
    else
        tail = 0;
    size = tail == 0 ? p->out_fmt->block_align * samples : (tail + samples) * p->out_fmt->block_align;

    if (!(pr->flags & 0x40)) {
        uint8_t *out;
        const uint8_t *in = pr->in;
        int clamp = !(pr->flags & 0x400), last = 0;
        if (pr->flags & 4) {
            out = hmiFX_Malloc(size);
            if (!out)
                return 1;
            pr->out = out;
            pr->out_bytes = size;
        } else {
            out = pr->out;
        }
        p->in_r = p->buf_r[0];
        p->out_l = p->buf_l[1];
        p->in_l = p->buf_l[0];
        p->out_r = p->buf_r[1];
        p->pingpong = 0;
        if (!(p->flags & 0x80000000) || !(p->flags & 0x20000000)) {
            for (e = p->effects; e; e = e->next) {
                e->length = tail + samples + p->block;
                e->iface->reset(p, e);
            }
            if (p->flags & 0x80000000)
                p->flags |= 0x20000000;
        }
        do {
            uint32_t n = p->block <= samples ? p->block : samples;
            uint32_t ia = p->in_fmt->block_align, oa = p->out_fmt->block_align;
            p->count = n;
            pfx_in(p, in, n);
            pfx_chain(p);
            pfx_out(p, out, p->count, clamp);
            out += oa * n;
            in += ia * n;
            if (p->block < samples)
                samples -= p->block;
            else
                last = 1;
        } while (!last);
        while (tail != 0) {
            uint32_t n = p->block <= tail ? p->block : tail, oa = p->out_fmt->block_align;
            p->count = n;
            zero(p->in_l, n * 4);
            zero(p->in_r, n * 4);
            pfx_chain(p);
            pfx_out(p, out, p->count, clamp);
            out += oa * n;
            tail = p->block < tail ? tail - p->block : 0;
        }
    } else {
        pr->out_bytes = size;
    }
    if (pr->flags & 8)
        p->in_fmt = saved_in;
    if (pr->flags & 0x10)
        p->out_fmt = saved_out;
    if (pr->flags & 0x200)
        p->out_fmt = saved_out;
    return 0;
}

#endif /* GRIM_IMUSE || HMIFX_STANDALONE */
