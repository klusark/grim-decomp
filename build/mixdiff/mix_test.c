/* Differential test of the software mixer loops: the original machine code (orig_*, sliced from the baseline assembly)
 * against build/overrides_mixer.c on random buffers, ratios, volumes.  Build with build/mixdiff/build.sh. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

extern int *g_pMixer_mixBuf;
#define DECL(name, srct, ...) \
    extern void orig_##name(srct *, int, unsigned, int, __VA_ARGS__); \
    extern void name(srct *, int, unsigned, int, __VA_ARGS__);
DECL(Mixer_Mix8MonoLR, unsigned char, int, int)
DECL(Mixer_Mix8Mono, unsigned char, int)
DECL(Mixer_Mix16MonoLR, short, int, int)
DECL(Mixer_Mix16Mono, short, int)
DECL(Mixer_MixStereoLR_A, unsigned short, int, int)
DECL(Mixer_MixStereo_A, unsigned short, int)
DECL(Mixer_MixStereoLR_B, unsigned short, int, int)
DECL(Mixer_MixStereo_B, unsigned short, int)

static uint64_t rng = 88172645463325252ull;
static uint64_t rnd(void) { rng ^= rng << 13; rng ^= rng >> 7; rng ^= rng << 17; return rng; }

#define MAXFR 80
#define SRCB 2048
static unsigned char srcbuf[SRCB + 64];
static int accA[(MAXFR + 24) * 2], accB[(MAXFR + 24) * 2];

int main(int argc, char **argv)
{
    long n = argc > 1 ? atol(argv[1]) : 1000000;
    int neg = argc > 2;   /* negative control: perturb the C side, every function must then report differences */
    long bad[8] = {0}, done[8] = {0};
    const char *names[8] = {"8MonoLR", "8Mono", "16MonoLR", "16Mono", "StereoLR_A", "Stereo_A", "StereoLR_B", "Stereo_B"};
    for (long it = 0; it < n; it++) {
        int f = it % 8;
        int rate = 1 + rnd() % MAXFR, count, off = rnd() % 8, volL, volR;
        switch (rnd() % 6) {
        case 0: count = rate / 2; if (count < 1) { rate = 2; count = 1; } rate = count * 2; break;   /* ratio 0x8000 */
        case 1: count = rate; break;                                                                  /* 0x10000 */
        case 2: count = rate * 2; break;                                                              /* 0x20000 */
        default: count = 1 + rnd() % (rate * 3); break;
        }
        if ((rnd() & 3) == 0) { volL = (int)rnd(); volR = (int)rnd(); } else { volL = rnd() % 300; volR = rnd() % 300; }
        int sh = rnd() & 3;
        for (int i = 0; i < SRCB + 64; i++) srcbuf[i] = (unsigned char)((rnd() & 7) == 0 ? (rnd() & 1 ? 0x80 : 0x7f) : rnd());
        for (unsigned i = 0; i < sizeof accA / 4; i++) accA[i] = accB[i] = (int)rnd();
        unsigned char *src = srcbuf + sh;
        g_pMixer_mixBuf = accA; int *ga = accA;
        switch (f) {
        case 0: orig_Mixer_Mix8MonoLR(src, count, rate, off, volL, volR); break;
        case 1: orig_Mixer_Mix8Mono(src, count, rate, off, volL); break;
        case 2: orig_Mixer_Mix16MonoLR((short *)src, count, rate, off, volL, volR); break;
        case 3: orig_Mixer_Mix16Mono((short *)src, count, rate, off, volL); break;
        case 4: orig_Mixer_MixStereoLR_A((unsigned short *)src, count, rate, off, volL, volR); break;
        case 5: orig_Mixer_MixStereo_A((unsigned short *)src, count, rate, off, volL); break;
        case 6: orig_Mixer_MixStereoLR_B((unsigned short *)src, count, rate, off, volL, volR); break;
        case 7: orig_Mixer_MixStereo_B((unsigned short *)src, count, rate, off, volL); break;
        }
        g_pMixer_mixBuf = accB; (void)ga; if (neg) volL += 1;
        switch (f) {
        case 0: Mixer_Mix8MonoLR(src, count, rate, off, volL, volR); break;
        case 1: Mixer_Mix8Mono(src, count, rate, off, volL); break;
        case 2: Mixer_Mix16MonoLR((short *)src, count, rate, off, volL, volR); break;
        case 3: Mixer_Mix16Mono((short *)src, count, rate, off, volL); break;
        case 4: Mixer_MixStereoLR_A((unsigned short *)src, count, rate, off, volL, volR); break;
        case 5: Mixer_MixStereo_A((unsigned short *)src, count, rate, off, volL); break;
        case 6: Mixer_MixStereoLR_B((unsigned short *)src, count, rate, off, volL, volR); break;
        case 7: Mixer_MixStereo_B((unsigned short *)src, count, rate, off, volL); break;
        }
        done[f]++;
        if (memcmp(accA, accB, sizeof accA)) {
            if (bad[f]++ < 3) printf("DIFF %s: count=%d rate=%d off=%d volL=%d volR=%d sh=%d\n", names[f], count, rate, off, volL, volR, sh);
        }
    }
    long tot = 0;
    for (int f = 0; f < 8; f++) { printf("%-12s cases %9ld  differences %ld\n", names[f], done[f], bad[f]); tot += bad[f]; }
    printf("TOTAL differences: %ld of %ld\n", tot, n);
    return tot != 0;
}
