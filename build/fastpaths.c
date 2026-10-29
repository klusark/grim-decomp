/* Hand-written fast paths (compiled with -O2 -msse2, see link.py / BUILD_NOTES.md "Performance").
 * Same rules as overrides.c: tools/build_src.py puts the decompiled version of every function
 * defined here under `#if 0`. Only GRIMFANDANGO.EXE has entries. */
#include "ghidra_types.h"

#ifdef GRIM_EXE
#include "globals.h"
#include "functions.h"
#define _MM_MALLOC_H_INCLUDED   /* mm_malloc.h would declare malloc/free with the host prototypes */
#include <emmintrin.h>

/* functions that use SSE: the engine calls them with only 4-byte stack alignment */
#define FASTFN __attribute__((force_align_arg_pointer, target("sse2")))

/* Display_Flip (0x474420), DIB path. The back buffer is a 16 bpp (565) DIB section; BitBlt from it to the
 * 32 bpp window DC makes GDI convert every pixel inside the kernel, which took about 40% of a frame in
 * the office scene. The conversion is done here with SSE2 into a 32 bpp DIB section of the same size,
 * which BitBlt then copies without any format conversion. Anything unusual (8 bpp modes, DirectDraw,
 * widths that are not a multiple of 8, failed allocations) falls back to the original BitBlt. */
static uint fp_dc, fp_bmp;
static uint *fp_bits;
static int fp_w, fp_h;

static void fp_release(void)
{
    if (fp_dc) DeleteDC(fp_dc);
    if (fp_bmp) DeleteObject(fp_bmp);
    fp_dc = fp_bmp = 0;
    fp_bits = 0;
}

static int fp_setup(uint hdc, int w, int h)
{
    unsigned bi[11];
    void *bits = 0;
    int i;
    if (fp_bits && fp_w == w && fp_h == h)
        return 1;
    fp_release();
    for (i = 0; i < 11; i++) bi[i] = 0;
    bi[0] = 40;
    bi[1] = w;
    bi[2] = -h;                 /* top-down, like the game's 16 bpp DIB */
    bi[3] = 1 | (32 << 16);     /* planes, bit count */
    fp_bmp = CreateDIBSection(hdc, (int)bi, 0, (int)&bits, 0, 0);
    if (fp_bmp == 0 || bits == 0) {
        if (fp_bmp) DeleteObject(fp_bmp);
        fp_bmp = 0;
        return 0;
    }
    fp_dc = CreateCompatibleDC(hdc);
    if (fp_dc == 0) {
        DeleteObject(fp_bmp);
        fp_bmp = 0;
        return 0;
    }
    SelectObject(fp_dc, fp_bmp);
    fp_bits = (uint *)bits;
    fp_w = w;
    fp_h = h;
    return 1;
}

/* 8 pixels per iteration. Channel expansion replicates the top bits (x << 3 | x >> 2), which maps 31 to 255 */
static void conv565(const unsigned short *src, uint *dst, int n)
{
    const __m128i m5 = _mm_set1_epi16(0x1f), m6 = _mm_set1_epi16(0x3f);
    int i;
    for (i = 0; i < n; i += 8) {
        __m128i v = _mm_loadu_si128((const __m128i *)(src + i));
        __m128i r = _mm_and_si128(_mm_srli_epi16(v, 11), m5);
        __m128i g = _mm_and_si128(_mm_srli_epi16(v, 5), m6);
        __m128i b = _mm_and_si128(v, m5);
        __m128i r8, g8, b8, lo, hi;
        r8 = _mm_or_si128(_mm_slli_epi16(r, 3), _mm_srli_epi16(r, 2));
        g8 = _mm_or_si128(_mm_slli_epi16(g, 2), _mm_srli_epi16(g, 4));
        b8 = _mm_or_si128(_mm_slli_epi16(b, 3), _mm_srli_epi16(b, 2));
        lo = _mm_or_si128(b8, _mm_slli_epi16(g8, 8));   /* G:B per 16-bit lane */
        hi = r8;                                        /* 0:R */
        _mm_storeu_si128((__m128i *)(dst + i), _mm_unpacklo_epi16(lo, hi));
        _mm_storeu_si128((__m128i *)(dst + i + 4), _mm_unpackhi_epi16(lo, hi));
    }
}

static void conv555(const unsigned short *src, uint *dst, int n)
{
    const __m128i m5 = _mm_set1_epi16(0x1f);
    int i;
    for (i = 0; i < n; i += 8) {
        __m128i v = _mm_loadu_si128((const __m128i *)(src + i));
        __m128i r = _mm_and_si128(_mm_srli_epi16(v, 10), m5);
        __m128i g = _mm_and_si128(_mm_srli_epi16(v, 5), m5);
        __m128i b = _mm_and_si128(v, m5);
        __m128i r8, g8, b8, lo;
        r8 = _mm_or_si128(_mm_slli_epi16(r, 3), _mm_srli_epi16(r, 2));
        g8 = _mm_or_si128(_mm_slli_epi16(g, 3), _mm_srli_epi16(g, 2));
        b8 = _mm_or_si128(_mm_slli_epi16(b, 3), _mm_srli_epi16(b, 2));
        lo = _mm_or_si128(b8, _mm_slli_epi16(g8, 8));
        _mm_storeu_si128((__m128i *)(dst + i), _mm_unpacklo_epi16(lo, r8));
        _mm_storeu_si128((__m128i *)(dst + i + 4), _mm_unpackhi_epi16(lo, r8));
    }
}

/* Test knobs (environment): GRIM_SLOWFLIP=1 uses the original 16 bpp BitBlt; GRIM_PERFLOG=1 appends
 * "perf: ..." lines (frame rate, time spent in Display_Flip) to the file named by GRIM_LUA_LOG every 256 frames. */
extern char *GRIM_getenv(const char *) __asm__("_getenv");
extern int __attribute__((stdcall)) GRIM_QPC(long long *) __asm__("_QueryPerformanceCounter@4");
extern int __attribute__((stdcall)) GRIM_QPF(long long *) __asm__("_QueryPerformanceFrequency@4");
static int fp_knobs = -1;   /* bit0 slow flip, bit1 perf log */
static long long fp_t0, fp_flip, fp_freq;
static int fp_frames;

static void fp_perf_log(const char *text)
{
    const char *path = GRIM_getenv("GRIM_LUA_LOG");
    void *h;
    unsigned wrote;
    if (path == 0) return;
    h = CreateFileA(path, 4, 3, 0, 4, 0x80, 0);
    if (h != (void *)-1) {
        WriteFile(h, text, __builtin_strlen(text), &wrote, 0);
        CloseHandle(h);
    }
}

static int fp_flip_impl(void);

FASTFN int Display_Flip(void)
{
    long long a, b;
    int r;
    if (fp_knobs < 0) {
        fp_knobs = (GRIM_getenv("GRIM_SLOWFLIP") != 0) | ((GRIM_getenv("GRIM_PERFLOG") != 0) << 1);
        GRIM_QPF(&fp_freq);
    }
    if (!(fp_knobs & 2))
        return fp_flip_impl();
    GRIM_QPC(&a);
    r = fp_flip_impl();
    GRIM_QPC(&b);
    fp_flip += b - a;
    if (fp_frames == 0) fp_t0 = a;
    if (++fp_frames == 256) {
        char msg[200];
        double secs = (double)(b - fp_t0) / (double)fp_freq;
        wsprintfA(msg, "perf: 256 frames, %d.%02d ms/frame (%d fps), flip %d us/frame\r\n",
                  (int)(secs * 1000 / 256), (int)(secs * 100000 / 256) % 100, (int)(256 / secs),
                  (int)((double)fp_flip * 1e6 / (double)fp_freq / 256));
        fp_perf_log(msg);
        fp_frames = 0;
        fp_flip = 0;
    }
    return r;
}

static int fp_flip_impl(void)
{
    int iVar1;
    if (*(int *)((int)g_pDisplayDevice + 0x100) == 0) {
        int *mode = (int *)g_pVideoMode;
        int w = mode[2], h = mode[3];
        GdiFlush();
        if (!(fp_knobs & 1) && mode[7] == 1 && mode[8] == 16 && UINT_007feae0 != 0 && (w & 7) == 0 && w > 0 && h > 0
            && fp_setup(UINT_00803f7c, w, h)) {
            if (mode[10] == 6)
                conv565((const unsigned short *)UINT_007feae0, fp_bits, w * h);
            else
                conv555((const unsigned short *)UINT_007feae0, fp_bits, w * h);
            BitBlt(UINT_00803f7c, 0, 0, w, h, fp_dc, 0, 0, 0xcc0020);
        } else {
            BitBlt(UINT_00803f7c, 0, 0, w, h, UINT_007f6498, 0, 0, 0xcc0020);
        }
    }
    else {
        iVar1 = *(int *)((int)g_pDisplayDevice + 0x100) + -1;
        if (iVar1 != 0) {
            return iVar1;
        }
        if (UINT_00803f9c != 0) {
            iVar1 = DDraw_Flip();
            return iVar1;
        }
    }
    return 1;
}

#endif
