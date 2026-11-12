/* GDI32 on memory: device contexts, DIB sections, palettes. A BitBlt to the window's DC shows the frame (user32.c).
 *
 * The game's "Window Display Device" renders into a 16 bpp DIB section selected into a memory DC and copies it to
 * the window with BitBlt (stdDisplay_Update / build/fastpaths.c, which first converts to a 32 bpp DIB). */
#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include "platform.h"

typedef struct { BYTE b, g, r, x; } RGBQUAD;

typedef struct {
    int w, h, bpp, stride, topdown;
    uint32_t rmask, gmask, bmask;
    RGBQUAD pal[256];
    BYTE *bits;
} Bitmap;

typedef struct {
    int is_window;          /* the window's (or the screen's) DC: BitBlt into it presents */
    HANDLE bitmap, font, palette;
} DC;

typedef struct { RGBQUAD e[256]; int n; } Palette;

static uint32_t *g_frame;   /* the window's contents, 32 bpp */
static int g_frame_w, g_frame_h;

WINFN(HANDLE, GetDC, (HANDLE hwnd))
{
    DC *dc = calloc(1, sizeof *dc);
    (void)hwnd;
    dc->is_window = 1;
    return handle_new(H_DC, dc);
}

WINFN(int, ReleaseDC, (HANDLE hwnd, HANDLE hdc))
{
    DC *dc = handle_get(hdc, H_DC);
    (void)hwnd;
    if (!dc)
        return 0;
    free(dc);
    handle_free(hdc);
    return 1;
}

WINFN(HANDLE, CreateCompatibleDC, (HANDLE hdc))
{
    (void)hdc;
    return handle_new(H_DC, calloc(1, sizeof(DC)));
}

WINFN(BOOL, DeleteDC, (HANDLE hdc))
{
    DC *dc = handle_get(hdc, H_DC);
    if (!dc)
        return 0;
    free(dc);
    handle_free(hdc);
    return 1;
}

WINFN(int, GetDeviceCaps, (HANDLE hdc, int index))
{
    (void)hdc;
    switch (index) {
    case 8: return 1920;    /* HORZRES */
    case 10: return 1080;   /* VERTRES */
    case 12: return 32;     /* BITSPIXEL */
    case 14: return 1;      /* PLANES */
    case 24: return -1;     /* NUMCOLORS */
    case 38: return 0x7e99; /* RASTERCAPS: no RC_PALETTE */
    case 88: case 90: return 96;   /* LOGPIXELSX/Y */
    default: return 0;
    }
}

/* BITMAPINFO: header (40 bytes), then masks (BI_BITFIELDS) or the colour table */
WINFN(HANDLE, CreateDIBSection, (HANDLE hdc, const BYTE *bmi, UINT usage, void **bits, HANDLE section, DWORD offset))
{
    const int32_t *hdr = (const int32_t *)bmi;
    Bitmap *b = calloc(1, sizeof *b);
    uint32_t compression;
    (void)hdc; (void)usage; (void)section; (void)offset;
    b->w = hdr[1];
    b->h = hdr[2] < 0 ? -hdr[2] : hdr[2];
    b->topdown = hdr[2] < 0;
    b->bpp = ((const uint16_t *)bmi)[7];
    compression = (uint32_t)hdr[4];
    b->stride = ((b->w * b->bpp + 31) / 32) * 4;
    if (b->bpp == 16) {
        if (compression == 3) {   /* BI_BITFIELDS */
            const uint32_t *m = (const uint32_t *)(bmi + hdr[0]);
            b->rmask = m[0], b->gmask = m[1], b->bmask = m[2];
        } else {
            b->rmask = 0x7c00, b->gmask = 0x03e0, b->bmask = 0x001f;
        }
    } else if (b->bpp == 8) {
        uint32_t used = (uint32_t)hdr[8];
        memcpy(b->pal, bmi + hdr[0], (used && used <= 256 ? used : 256) * 4);
    }
    b->bits = calloc(1, (size_t)b->stride * b->h + 16);
    if (bits)
        *bits = b->bits;
    plat_trace("CreateDIBSection %dx%d %d bpp (masks %x %x %x)", b->w, b->h, b->bpp, b->rmask, b->gmask, b->bmask);
    return handle_new(H_BITMAP, b);
}

WINFN(HANDLE, SelectObject, (HANDLE hdc, HANDLE obj))
{
    DC *dc = handle_get(hdc, H_DC);
    HANDLE old;
    if (!dc)
        return NULL;
    switch (handle_type(obj)) {
    case H_BITMAP:
        old = dc->bitmap;
        dc->bitmap = obj;
        return old;
    case H_FONT:
        old = dc->font;
        dc->font = obj;
        return old;
    default:
        return (HANDLE)1;
    }
}

WINFN(BOOL, DeleteObject, (HANDLE obj))
{
    void *p;
    switch (handle_type(obj)) {
    case H_BITMAP:
        p = handle_get(obj, H_BITMAP);
        free(((Bitmap *)p)->bits);
        free(p);
        handle_free(obj);
        return 1;
    case H_PALETTE:
    case H_FONT:
        free(handle_get(obj, handle_type(obj)));
        handle_free(obj);
        return 1;
    default:
        return 1;
    }
}

WINFN(UINT, SetDIBColorTable, (HANDLE hdc, UINT start, UINT n, const RGBQUAD *colors))
{
    DC *dc = handle_get(hdc, H_DC);
    Bitmap *b = dc ? handle_get(dc->bitmap, H_BITMAP) : NULL;
    if (!b || start >= 256)
        return 0;
    if (start + n > 256)
        n = 256 - start;
    memcpy(b->pal + start, colors, n * 4);
    return n;
}

/* LOGPALETTE: WORD version, WORD count, PALETTEENTRY {r, g, b, flags}[] */
WINFN(HANDLE, CreatePalette, (const WORD *lp))
{
    Palette *p = calloc(1, sizeof *p);
    const BYTE *e = (const BYTE *)(lp + 2);
    p->n = lp[1] > 256 ? 256 : lp[1];
    for (int i = 0; i < p->n; i++)
        p->e[i].r = e[i * 4], p->e[i].g = e[i * 4 + 1], p->e[i].b = e[i * 4 + 2];
    return handle_new(H_PALETTE, p);
}

WINFN(HANDLE, SelectPalette, (HANDLE hdc, HANDLE pal, BOOL bg))
{
    DC *dc = handle_get(hdc, H_DC);
    HANDLE old;
    (void)bg;
    if (!dc)
        return NULL;
    old = dc->palette;
    dc->palette = pal;
    return old;
}

WINFN(UINT, RealizePalette, (HANDLE hdc)) { (void)hdc; return 0; }

WINFN(BOOL, AnimatePalette, (HANDLE pal, UINT start, UINT n, const BYTE *e))
{
    Palette *p = handle_get(pal, H_PALETTE);
    if (!p)
        return 0;
    for (UINT i = 0; i < n && start + i < 256; i++)
        p->e[start + i].r = e[i * 4], p->e[start + i].g = e[i * 4 + 1], p->e[start + i].b = e[i * 4 + 2];
    return 1;
}

WINFN(UINT, GetSystemPaletteEntries, (HANDLE hdc, UINT start, UINT n, BYTE *e))
{
    (void)hdc; (void)start;
    memset(e, 0, n * 4);
    return 0;   /* not a palette device */
}

WINFN(BOOL, GdiFlush, (void)) { return 1; }
WINFN(HANDLE, GetStockObject, (int i)) { (void)i; return handle_new(H_STOCK, NULL); }
WINFN(DWORD, SetTextColor, (HANDLE hdc, DWORD c)) { (void)hdc; (void)c; return 0xffffff; }
WINFN(int, SetBkMode, (HANDLE hdc, int m)) { (void)hdc; (void)m; return 1; }
WINFN(BOOL, TextOutA, (HANDLE hdc, int x, int y, const char *s, int n))
{
    (void)hdc; (void)x; (void)y;
    plat_trace("TextOutA(%.*s)", n, s);   /* the developer overlay text: not drawn */
    return 1;
}
WINFN(HANDLE, CreateFontA, (int h, int w, int esc, int orient, int weight, DWORD it, DWORD ul, DWORD so, DWORD cs,
                            DWORD op, DWORD cp, DWORD q, DWORD pf, const char *face))
{
    (void)h; (void)w; (void)esc; (void)orient; (void)weight; (void)it; (void)ul; (void)so; (void)cs; (void)op; (void)cp;
    (void)q; (void)pf; (void)face;
    return handle_new(H_FONT, calloc(1, 4));
}

static inline uint32_t expand(uint32_t v, uint32_t mask)
{
    int shift = __builtin_ctz(mask), bits = __builtin_popcount(mask);
    uint32_t c = (v & mask) >> shift;
    return bits >= 8 ? c >> (bits - 8) : (c << (8 - bits)) | (c >> (2 * bits - 8 > 0 ? 2 * bits - 8 : 0));
}

static void convert_rows(Bitmap *b, int sx, int sy, int dx, int dy, int w, int h)
{
    for (int y = 0; y < h; y++) {
        int srow = sy + y, drow = dy + y;
        const BYTE *s;
        uint32_t *d;
        if (srow < 0 || srow >= b->h || drow < 0 || drow >= g_frame_h)
            continue;
        s = b->bits + (size_t)(b->topdown ? srow : b->h - 1 - srow) * b->stride;
        d = g_frame + (size_t)drow * g_frame_w;
        for (int x = 0; x < w; x++) {
            int sxx = sx + x, dxx = dx + x;
            uint32_t c;
            if (sxx < 0 || sxx >= b->w || dxx < 0 || dxx >= g_frame_w)
                continue;
            switch (b->bpp) {
            case 32: c = ((const uint32_t *)s)[sxx] | 0xff000000u; break;
            case 24: c = 0xff000000u | s[sxx * 3] | s[sxx * 3 + 1] << 8 | s[sxx * 3 + 2] << 16; break;
            case 16: {
                uint32_t v = ((const uint16_t *)s)[sxx];
                c = 0xff000000u | expand(v, b->rmask) << 16 | expand(v, b->gmask) << 8 | expand(v, b->bmask);
                break;
            }
            case 8: {
                RGBQUAD q = b->pal[s[sxx]];
                c = 0xff000000u | q.r << 16 | q.g << 8 | q.b;
                break;
            }
            default: c = 0xffff00ffu;
            }
            d[dxx] = c;
        }
    }
}

WINFN(BOOL, BitBlt, (HANDLE dst, int x, int y, int w, int h, HANDLE src, int sx, int sy, DWORD rop))
{
    DC *ddc = handle_get(dst, H_DC), *sdc = handle_get(src, H_DC);
    Bitmap *b = sdc ? handle_get(sdc->bitmap, H_BITMAP) : NULL;
    (void)rop;
    if (!ddc || !b)
        return 0;
    if (!ddc->is_window) {
        /* memory to memory: same format only (not used by the game's display path) */
        Bitmap *d = handle_get(ddc->bitmap, H_BITMAP);
        if (!d || d->bpp != b->bpp)
            return 0;
        for (int r = 0; r < h; r++) {
            int srow = sy + r, drow = y + r;
            if (srow < 0 || srow >= b->h || drow < 0 || drow >= d->h)
                continue;
            memcpy(d->bits + (size_t)(d->topdown ? drow : d->h - 1 - drow) * d->stride + x * d->bpp / 8,
                   b->bits + (size_t)(b->topdown ? srow : b->h - 1 - srow) * b->stride + sx * b->bpp / 8,
                   (size_t)w * b->bpp / 8);
        }
        return 1;
    }
    /* to the window: the frame is the size of the source bitmap (the video mode) */
    if (g_frame_w != b->w || g_frame_h != b->h) {
        free(g_frame);
        g_frame_w = b->w;
        g_frame_h = b->h;
        g_frame = calloc((size_t)g_frame_w * g_frame_h, 4);
    }
    convert_rows(b, sx, sy, x, y, w, h);
    win_present(g_frame, g_frame_w, g_frame_h);
    return 1;
}
