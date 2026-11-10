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

/* Test knobs (environment): GRIM_SLOWFLIP=1 uses the original 16 bpp BitBlt, GRIM_NODELTA=1 converts and blits every frame completely; GRIM_PERFLOG=1 appends
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
        fp_knobs = (GRIM_getenv("GRIM_SLOWFLIP") != 0) | ((GRIM_getenv("GRIM_PERFLOG") != 0) << 1) | ((GRIM_getenv("GRIM_NODELTA") != 0) << 2);
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

/* Delta flip: the previously presented 16 bpp frame is kept in fp_prev; only the band of rows that changed is
 * converted and blitted, and nothing at all is done when the frame is identical (the main loop flips every
 * iteration, also in a still scene or while a movie is between two frames). A full blit is forced at least every
 * 100 ms (and after any mode change), in case the window lost its contents. GRIM_NODELTA=1 disables this. */
static unsigned short fp_prev[1280 * 1024];
static int fp_prev_w, fp_prev_h;
static long long fp_last_full;

static int rowdiff(const unsigned short *a, const unsigned short *b, int bytes)
{
    int i;
    for (i = 0; i < bytes; i += 16) {
        __m128i x = _mm_cmpeq_epi8(_mm_loadu_si128((const __m128i *)((const char *)a + i)),
                                   _mm_loadu_si128((const __m128i *)((const char *)b + i)));
        if (_mm_movemask_epi8(x) != 0xffff)
            return 1;
    }
    return 0;
}

static void copyrows(unsigned short *dst, const unsigned short *src, int bytes)
{
    int i;
    for (i = 0; i < bytes; i += 16)
        _mm_storeu_si128((__m128i *)((char *)dst + i), _mm_loadu_si128((const __m128i *)((const char *)src + i)));
}

static int fp_flip_impl(void)
{
    int iVar1;
    if (*(int *)((int)g_pDisplayDevice + 0x100) == 0) {
        int *mode = (int *)g_pVideoMode;
        int w = mode[2], h = mode[3];
        if (!(fp_knobs & 1) && mode[7] == 1 && mode[8] == 16 && UINT_007feae0 != 0 && (w & 7) == 0 && w > 0 && h > 0
            && w <= 1280 && w * h <= 1280 * 1024 && fp_setup(UINT_00803f7c, w, h)) {
            const unsigned short *src = (const unsigned short *)UINT_007feae0;
            int y0 = 0, y1 = h - 1, y;
            long long now;
            GRIM_QPC(&now);
            if (!(fp_knobs & 4) && fp_prev_w == w && fp_prev_h == h && now - fp_last_full < fp_freq / 10) {
                y0 = -1;
                for (y = 0; y < h; y++) {
                    if (rowdiff(src + y * w, fp_prev + y * w, w * 2)) {
                        if (y0 < 0) y0 = y;
                        y1 = y;
                    }
                }
                if (y0 < 0)
                    return 1;       /* identical to what is on the screen */
            } else {
                fp_last_full = now;
            }
            GdiFlush();
            if (mode[10] == 6)
                conv565(src + y0 * w, fp_bits + y0 * w, (y1 - y0 + 1) * w);
            else
                conv555(src + y0 * w, fp_bits + y0 * w, (y1 - y0 + 1) * w);
            copyrows(fp_prev + y0 * w, src + y0 * w, (y1 - y0 + 1) * w * 2);
            fp_prev_w = w;
            fp_prev_h = h;
            BitBlt(UINT_00803f7c, 0, y0, w, y1 - y0 + 1, fp_dc, 0, y0, 0xcc0020);
        } else {
            GdiFlush();
            fp_prev_w = 0;
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


/* Mem_Copy (0x478170): forward copy (the engine relies on that for overlapping ranges, so no memmove semantics).
 * The decompiled version copies 8 bytes per iteration through 64-bit loads; `rep movsb` is the fast forward copy
 * of current CPUs, and large non-overlapping blocks use 16-byte SSE copies. */
FASTFN void __cdecl Mem_Copy(void *dst, void *src, uint n)
{
    if ((int)n <= 0)
        return;
    if (n >= 256 && ((uint)dst - (uint)src) + 16 > 32) {      /* |dst - src| >= 16: chunked copy gives the same bytes */
        char *d = (char *)dst;
        const char *s = (const char *)src;
        uint i;
        for (i = 0; i + 16 <= n; i += 16)
            _mm_storeu_si128((__m128i *)(d + i), _mm_loadu_si128((const __m128i *)(s + i)));
        dst = d + i;
        src = (void *)(s + i);
        n -= i;
    }
    __asm__ volatile("rep movsb" : "+D"(dst), "+S"(src), "+c"(n) : : "memory");
}

/* Insane_BlitRows16 (0x4bddb0): copies `rows` rows of `bytes` bytes (movie frame -> screen buffer), optionally through a
 * 16-bit look-up table (g_dwSmushPlay_TranslationTable). The plain copy dominated a movie loop. */
FASTFN void Insane_BlitRows16(ushort *param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
    int n = param_5 >> 2;
    if (g_dwSmushPlay_TranslationTable == 0) {
        while (param_6 != 0) {
            const char *s = (const char *)param_1;
            char *d = (char *)param_3;
            int i, bytes = n * 4;
            for (i = 0; i + 16 <= bytes; i += 16)
                _mm_storeu_si128((__m128i *)(d + i), _mm_loadu_si128((const __m128i *)(s + i)));
            for (; i < bytes; i += 4)
                *(uint *)(d + i) = *(const uint *)(s + i);
            param_1 = (ushort *)((int)param_1 + param_2);
            param_3 += param_4;
            param_6--;
        }
    } else {
        const ushort *tab = (const ushort *)g_dwSmushPlay_TranslationTable;
        while (param_6 != 0) {
            const ushort *s = param_1;
            uint *d = (uint *)param_3;
            int i;
            for (i = 0; i < n; i++)
                d[i] = (uint)tab[s[2 * i]] | ((uint)tab[s[2 * i + 1]] << 16);
            param_3 += param_4;
            param_1 = (ushort *)((int)param_1 + param_2);
            param_6--;
        }
    }
}

#endif
