/* Differential test of the mixer entry points: ClearAccumulator, ConvertTo16, MixVoice, MixVoiceByFormat, InitTables,
 * Init, Free.  Original machine code (orig_*) against build/overrides_mixer.c on random inputs.
 * usage: mixcore_test.exe [cases] [neg]   (neg = negative control: the C side gets a perturbed volume, must report differences) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <float.h>

extern int *g_pMixer_mixBuf;
extern unsigned g_dwMixer_mixBufSize, g_dwMixer_outChannelCount, g_dwWaveMixCount;
extern void *g_pMixer_softLTable;
extern unsigned char DAT_008dcc70[289];
extern unsigned DAT_008dcda0;

extern int orig_sou_mixer_start(void), sou_mixer_start(void);
extern int orig_Mixer_ConvertTo16(short *, int), Mixer_ConvertTo16(short *, int);
extern void orig_Mixer_MixVoice(unsigned char *, int, int, int, unsigned, int, int, int, int, int);
extern void Mixer_MixVoice(unsigned char *, int, int, int, unsigned, int, int, int, int, int);
extern void orig_FUN_004d2d90(unsigned char *, int, unsigned, int, int, int, int, int);
extern void sou_mixer_mix(unsigned char *, int, unsigned, int, int, int, int, int);
extern int orig_FUN_004d2e80(int *, unsigned, int, int), Mixer_InitTables(int *, unsigned, int, int);
extern int orig_FUN_004d2d40(int *, unsigned, int), sou_mixer_initialize(int *, unsigned, int);
extern int orig_FUN_004d2fb0(int *), Mixer_Free(int *);

static uint64_t rng = 88172645463325252ull;
static uint64_t rnd(void) { rng ^= rng << 13; rng ^= rng >> 7; rng ^= rng << 17; return rng; }

/* allocator / free fakes of the service table of the module manager */
typedef struct { int kind, a, b, c; } ALog;
static ALog alog[64]; static int nalog;
static int fail_alloc;          /* 0 = never, n = the n-th allocation fails */
static int nallocs;
static char heap[3][(1 << 20) + (1 << 18)];
static void *fake_alloc(int size, const char *file, int line)
{
    alog[nalog].kind = 1; alog[nalog].a = size; alog[nalog].b = line; alog[nalog].c = (int)(intptr_t)file; nalog++;
    if (++nallocs == fail_alloc) return 0;
    return heap[nallocs - 1 < 3 ? nallocs - 1 : 2];
}
static void fake_free(void *p, const char *file, int line)
{
    alog[nalog].kind = 2; alog[nalog].a = (int)(intptr_t)p; alog[nalog].b = line; alog[nalog].c = (int)(intptr_t)file; nalog++;
}

#define MAXFR 80
static int accA[(MAXFR + 24) * 2 + 64], accB[(MAXFR + 24) * 2 + 64];
static unsigned char srcbuf[4096];
static long fails, cases[8];

static void fail(const char *what, long i) { if (fails++ < 12) printf("DIFF %s (case %ld)\n", what, i); }

int main(int argc, char **argv)
{
    long n = argc > 1 ? atol(argv[1]) : 200000;
    int neg = argc > 2;
    int svc[16] = {0};
    svc[0] = (int)(intptr_t)fake_alloc; svc[1] = (int)(intptr_t)fake_free;

    /* --- Mixer_InitTables: every x87 precision mode, several sizes, allocation failures --- */
    unsigned pcs[3] = {_PC_24, _PC_53, _PC_64};
    for (int pi = 0; pi < 3; pi++) {
        _controlfp(pcs[pi], _MCW_PC);
        for (int units = 1; units <= 3; units++) for (int ch = 1; ch <= 2; ch++) for (int failing = 0; failing <= 2; failing++) {
            unsigned char tabA[289], tabB[289];
            static short compA[3 * 32768], compB[3 * 32768];
            int ra, rb, nA, nB;
            ALog lA[64], lB[64];
            unsigned bytesA, chA, ptrA, argA, bytesB, chB, ptrB, argB;
            memset(compA, 0x55, sizeof compA); memset(compB, 0x55, sizeof compB);
            memset(DAT_008dcc70, 0xee, 289); g_dwWaveMixCount = units; nalog = 0; nallocs = 0; fail_alloc = failing;
            g_pMixer_mixBuf = 0; g_pMixer_softLTable = 0; DAT_008dcda0 = 0; g_dwMixer_mixBufSize = 0; g_dwMixer_outChannelCount = 0;
            ra = orig_FUN_004d2e80(svc, ch, 40 + units, 77);
            memcpy(tabA, DAT_008dcc70, 289); nA = nalog; memcpy(lA, alog, sizeof lA);
            bytesA = g_dwMixer_mixBufSize; chA = g_dwMixer_outChannelCount; ptrA = (unsigned)(intptr_t)g_pMixer_softLTable; argA = DAT_008dcda0;
            if (g_pMixer_softLTable) memcpy(compA, g_pMixer_softLTable, (size_t)units << 16);
            memset(DAT_008dcc70, 0xee, 289); g_dwWaveMixCount = units; nalog = 0; nallocs = 0; fail_alloc = failing;
            g_pMixer_mixBuf = 0; g_pMixer_softLTable = 0; DAT_008dcda0 = 0; g_dwMixer_mixBufSize = 0; g_dwMixer_outChannelCount = 0;
            rb = Mixer_InitTables(svc, ch, 40 + units, 77);
            memcpy(tabB, DAT_008dcc70, 289); nB = nalog; memcpy(lB, alog, sizeof lB);
            bytesB = g_dwMixer_mixBufSize; chB = g_dwMixer_outChannelCount; ptrB = (unsigned)(intptr_t)g_pMixer_softLTable; argB = DAT_008dcda0;
            if (g_pMixer_softLTable) memcpy(compB, g_pMixer_softLTable, (size_t)units << 16);
            cases[0]++;
            if (ra != rb || memcmp(tabA, tabB, 289) || nA != nB || memcmp(lA, lB, nA * sizeof lA[0]) || bytesA != bytesB || chA != chB
                || ptrA != ptrB || argA != argB || memcmp(compA, compB, (size_t)units << 16)) {
                printf("  pc=%d units=%d ch=%d failing=%d ret %d/%d table %d allocs %d/%d\n", pi, units, ch, failing, ra, rb, memcmp(tabA, tabB, 289), nA, nB);
                fail("InitTables", pi * 100 + units);
            }
        }
        _controlfp(_PC_53, _MCW_PC);
    }
    /* Init / Free with the real tables left in place */
    {
        int ra, rb; unsigned long pa, pb;
        ALog lA[64];
        int nA;
        unsigned bytesA, chA, uA;
        fail_alloc = 0;
        nalog = 0; nallocs = 0; ra = orig_FUN_004d2d40(svc, 2, 50); pa = (unsigned long)g_pMixer_softLTable; nA = nalog;
        bytesA = g_dwMixer_mixBufSize; chA = g_dwMixer_outChannelCount; uA = g_dwWaveMixCount;
        nalog = 0; nallocs = 0; rb = sou_mixer_initialize(svc, 2, 50); pb = (unsigned long)g_pMixer_softLTable;
        if (ra != rb || pa != pb || nA != nalog || bytesA != g_dwMixer_mixBufSize || chA != g_dwMixer_outChannelCount || uA != g_dwWaveMixCount) fail("Init", 0);
        cases[1]++;
        for (int k = 0; k < 2; k++) {
            void *cA, *aA;
            int la;
            nalog = 0; ra = orig_FUN_004d2fb0(svc); la = nalog; memcpy(lA, alog, sizeof lA);
            cA = g_pMixer_softLTable; aA = g_pMixer_mixBuf;
            nallocs = 0; orig_FUN_004d2e80(svc, 2, 100, 0);       /* allocated again (k == 0) / still allocated */
            nalog = 0; rb = Mixer_Free(svc);
            if (ra != rb || la != nalog || memcmp(lA, alog, la * sizeof lA[0]) || cA != g_pMixer_softLTable || aA != g_pMixer_mixBuf) fail("Free", k);
            cases[1]++;
            nallocs = 0; nalog = 0; orig_FUN_004d2e80(svc, 2, 100, 0);   /* leave valid tables for the mixing tests */
        }
    }

    for (long it = 0; it < n; it++) {
        int f = 2 + it % 5;
        for (unsigned i = 0; i < sizeof accA / 4; i++) accA[i] = accB[i] = (int)rnd();
        switch (f) {
        case 2: {   /* ClearAccumulator */
            unsigned nb = rnd() % 200;
            int ra, rb;
            g_pMixer_mixBuf = accA; g_dwMixer_mixBufSize = nb; ra = orig_sou_mixer_start();
            g_pMixer_mixBuf = accB; rb = sou_mixer_start();
            if (ra != rb || memcmp(accA, accB, sizeof accA)) fail("ClearAccumulator", it);
            cases[2]++; break; }
        case 3: {   /* ConvertTo16 */
            short dA[(MAXFR + 24) * 2 + 8], dB[(MAXFR + 24) * 2 + 8];
            int frames = (rnd() & 15) == 0 ? 0 : 1 + rnd() % MAXFR, ra, rb;
            int nullacc = (rnd() & 31) == 0, nulldst = (rnd() & 31) == 0;
            for (unsigned i = 0; i < sizeof dA / 2; i++) dA[i] = dB[i] = (short)rnd();
            g_dwMixer_outChannelCount = 1 + (rnd() & 1);
            if ((rnd() & 3) == 0) for (unsigned i = 0; i < sizeof accA / 4; i++) accA[i] = accB[i] = (int)(rnd() % 70000) * 128 - 4500000;   /* around the clamp limits */
            g_pMixer_mixBuf = nullacc ? 0 : accA; ra = orig_Mixer_ConvertTo16(nulldst ? 0 : dA, frames);
            g_pMixer_mixBuf = nullacc ? 0 : accB; rb = Mixer_ConvertTo16(nulldst ? 0 : dB, frames);
            if (ra != rb || memcmp(dA, dB, sizeof dA) || memcmp(accA, accB, sizeof accA)) fail("ConvertTo16", it);
            cases[3]++; break; }
        case 4: case 5: case 6: {   /* MixVoice (4, 5) / MixVoiceByFormat (6) */
            int rate = 1 + rnd() % MAXFR, count, off = rnd() % 8;
            unsigned char *src;
            int volume, pan;
            switch (rnd() % 5) { case 0: rate = (rate + 1) & ~1; count = rate / 2; break; case 1: count = rate; break; case 2: count = rate * 2; break;
                                 default: count = 1 + rnd() % (rate * 3); }
            for (int i = 0; i < 4096; i++) srcbuf[i] = (unsigned char)rnd();
            src = srcbuf + (rnd() & 3);
            volume = (rnd() & 7) ? (int)(rnd() % 128) : (int)(rnd() % 300) - 20;
            pan = (rnd() & 7) ? (int)(rnd() % 129) : (int)(rnd() % 300) - 20;
            if (f == 6) {
                int format = rnd() % 6, srcBytes = 1 + rnd() % 1000;
                g_pMixer_mixBuf = accA; orig_FUN_004d2d90(src, off, rate, srcBytes, 0, volume, pan, format);
                g_pMixer_mixBuf = accB; sou_mixer_mix(src, off, rate, srcBytes, 0, volume + neg, pan, format);
                if (memcmp(accA, accB, sizeof accA)) fail("MixVoiceByFormat", it);
                cases[6]++;
            } else {
                int bits = (rnd() & 1) ? 8 : 16, ch = 1 + (rnd() & 1), ob = rnd() & 1, sw = rnd() & 1;
                int nullacc = (rnd() & 63) == 0, nullsrc = (rnd() & 63) == 0;
                if ((rnd() & 31) == 0) count = 0;
                g_pMixer_mixBuf = nullacc ? 0 : accA; orig_Mixer_MixVoice(nullsrc ? 0 : src, count, bits, ch, rate, off, volume, pan, ob, sw);
                g_pMixer_mixBuf = nullacc ? 0 : accB; Mixer_MixVoice(nullsrc ? 0 : src, count, bits, ch, rate, off, volume + neg, pan, ob, sw);
                if (memcmp(accA, accB, sizeof accA)) fail("MixVoice", it);
                cases[4]++;
            }
            break; }
        }
    }
    printf("cases: InitTables %ld Init/Free %ld Clear %ld Convert %ld MixVoice %ld ByFormat %ld  differences: %ld\n", cases[0], cases[1], cases[2], cases[3], cases[4], cases[6], fails);
    return fails != 0;
}
