/* Readable C for the pixel conversion code of the Smush video module (module "VIDEO" of lecsmush: Bitmap.c;
 * GRIMFANDANGO.EXE 0x004ce3e0 - 0x004d0260).
 *
 * A VideoBitmap is a small header (0x54 bytes) in front of the pixels with the description of the pixel format:
 * type 0 = palettised, 1 = RGB, 2 = RGB with alpha; per channel the number of bits, the shift of the channel in the pixel
 * and the loss (8 - bits).  gra_ConvertCopy converts rows of pixels between two formats through a 32 bit RGBA
 * scratch buffer (the "to RGBA" and "from RGBA" converters use the format description), with hand-written fast paths for
 * the common 15 / 16 bit layouts.
 *
 * The leaf converters are hand-written assembly in the original (cdecl, arguments at ebp+8..); they are do-while loops, so a
 * count of 0 (or an odd count) processes more pixels than asked for; the C versions reproduce that.
 * Differential tests: build/mixdiff/video_test.c. */
#include "ghidra_types.h"

#ifdef GRIM_EXE
#include "globals.h"
#include "functions.h"

typedef struct VideoBitmap {
    byte *data;             /* 00 pixels (the header is followed by them) */
    int width;              /* 04 */
    int height;             /* 08 */
    int bytesPerPixel;      /* 0c */
    int bitsPerPixel;       /* 10 */
    int pitch;              /* 14 bytesPerPixel * width */
    int field18;            /* 18 */
    int field1c;            /* 1c */
    int type;               /* 20 0 palettised, 1 RGB, 2 RGB + alpha */
    int bitsR, bitsG, bitsB;        /* 24 28 2c  (type 0: palette pointer, number of entries) */
    int shiftR, shiftG, shiftB;     /* 30 34 38 */
    int lossR, lossG, lossB;        /* 3c 40 44 */
    int bitsA, shiftA, lossA;       /* 48 4c 50 */
} VideoBitmap;

extern uint g_adwVideoMask[9] __asm__("_g_aConvert_bitmask");     /* mask of the top n bits of a byte (n = 0..8) */
extern int *g_pVideoMemory __asm__("_g_pVideo_memory_services");        /* "MEMORY workspace" services: [0] allocate(size, file, line) */
extern int *g_pVideoDisplayFormat __asm__("_g_dwVideo_video_services"); /* [1]() returns the VideoBitmap of the display */
extern uint g_nVideoScratchFlip __asm__("_UINT_008da8a0");
extern byte g_abVideoScratch[2 * 0x1400] __asm__("_DAT_009272a0");   /* RGBA pixel rows (at most 0x500 pixels), two buffers */

/* ===================================================================================================================
 *  leaf converters
 * =================================================================================================================== */

/* byte-indexed palette: dst pixel = table[src byte], 1..4 bytes per pixel.  do-while loops: a count < 1 still converts
 * one pixel (two for 2 bytes per pixel).  `bytesPerPixel` is compared as a byte. */
void Video_ExpandIndexed8(byte *dst, byte *src, int count, int bytesPerPixel, byte *table)
{
    switch ((byte)bytesPerPixel) {
    case 1:
        do {
            *dst++ = table[*src++];
        } while (--count > 0);
        break;
    case 2: {
        int pairs = (int)((uint)count >> 1);
        if (count & 1) {
            *(ushort *)dst = *(ushort *)(table + *src++ * 2);
            dst += 2;
        }
        do {
            uint two = *(ushort *)src;
            *(uint *)dst = (uint)*(ushort *)(table + (two >> 8) * 2) << 16 | *(ushort *)(table + (two & 0xff) * 2);
            src += 2;
            dst += 4;
        } while (--pairs > 0);
        break; }
    case 3: {
        /* (sic) the loop jumps back to after `xor eax,eax`: only AL is replaced, so the high bits of the previous (tripled)
         * index stay and the index grows from pixel to pixel; harmless as long as nobody uses 3 bytes per pixel */
        uint eax = 0;
        do {
            eax = (eax & ~0xffu) | *src++;
            eax *= 3;
            *(uint *)dst = *(uint *)(table + eax);          /* writes one byte too many, overwritten by the next pixel */
            dst += 3;
        } while (--count > 0);
        break; }
    case 4:
        do {
            *(uint *)dst = *(uint *)(table + *src++ * 4);
            dst += 4;
        } while (--count > 0);
        break;
    }
}

/* word-indexed variant */
void Video_ExpandIndexed16(byte *dst, ushort *src, int count, int bytesPerPixel, byte *table)
{
    switch ((byte)bytesPerPixel) {
    case 1:
        do {
            *dst++ = table[*src++];
        } while (--count > 0);
        break;
    case 2: {
        int pairs = (int)((uint)count >> 1);
        if (count & 1) {
            *(ushort *)dst = *(ushort *)(table + *src++ * 2);
            dst += 2;
        }
        do {
            uint two = *(uint *)src;
            *(uint *)dst = (uint)*(ushort *)(table + (two >> 16) * 2) << 16 | *(ushort *)(table + (two & 0xffff) * 2);
            src += 2;
            dst += 4;
        } while (--pairs > 0);
        break; }
    case 3: {
        uint eax = 0;           /* (sic) as above: AX is replaced, the upper half of the previous index stays */
        do {
            eax = (eax & ~0xffffu) | *src++;
            eax *= 3;
            *(uint *)dst = *(uint *)(table + eax);
            dst += 3;
        } while (--count > 0);
        break; }
    case 4:
        do {
            *(uint *)dst = *(uint *)(table + *src++ * 4);
            dst += 4;
        } while (--count > 0);
        break;
    }
}

/* 32 bit pixel (0x00RRGGBB) -> 15 bit 0BBBBBGGGGGRRRRR, two pixels per loop (odd count: one first; a count < 2 still does
 * one pair) */
static ushort pack555(uint p)
{
    uint v = p & 0xf8f8f8;
    return (ushort)((((v & 0xff) >> 3) << 10) | ((((v >> 8) & 0xff) >> 3) << 5) | ((v >> 16) >> 3));
}

void Video_Rgba32To555(ushort *dst, uint *src, uint count)
{
    int pairs = (int)(count >> 1);
    if (count & 1)
        *dst++ = pack555(*src++);
    do {
        uint lo = pack555(src[0]), hi = pack555(src[1]);
        *(uint *)dst = hi << 16 | lo;
        src += 2;
        dst += 2;
    } while (--pairs > 0);
}

/* 32 bit -> 16 bit 565 (BBBBBGGGGGGRRRRR) */
static ushort pack565(uint p)
{
    uint v = p & 0xf8fcf8;
    return (ushort)((((v & 0xff) >> 3) << 11) | ((((v >> 8) & 0xff) >> 2) << 5) | ((v >> 16) >> 3));
}

void Video_Rgba32To565(ushort *dst, uint *src, uint count)
{
    int pairs = (int)(count >> 1);
    if (count & 1)
        *dst++ = pack565(*src++);
    do {
        uint lo = pack565(src[0]), hi = pack565(src[1]);
        *(uint *)dst = hi << 16 | lo;
        src += 2;
        dst += 2;
    } while (--pairs > 0);
}

/* 32 bit -> 16 bit the other way round (shift games on partial registers: AX, AL) */
static ushort pack565alt(uint v)
{
    uint e = v >> 3;
    e = (e & 0xffff0000u) | ((e << 1) & 0xffff);
    e = (e & ~0xffu) | ((e << 2) & 0xff);
    e = (e & 0xffff0000u) | ((e << 2) & 0xffff);
    e >>= 5;
    return (ushort)e;
}

void Video_Rgba32To565Alt(ushort *dst, uint *src, uint count)
{
    int pairs = (int)(count >> 1);
    if (count & 1)
        *dst++ = pack565alt(*src++);
    do {
        uint lo = pack565alt(src[0]), hi = pack565alt(src[1]);
        *(uint *)dst = hi << 16 | lo;
        src += 2;
        dst += 2;
    } while (--pairs > 0);
}

/* 15 bit 555 -> 32 bit RGBA (alpha 255, low bits set) */
static uint unpack555(uint w)
{
    return 0xff000000u | (((w << 3) | 7) & 0xff) << 16 | ((((w << 6) >> 8) | 7) & 0xff) << 8 | ((((w >> 8) & 0x7f) << 1) | 7);
}

void Video_555ToRgba32(uint *dst, ushort *src, uint count)
{
    int pairs = (int)(count >> 1);
    if (count & 1)
        *dst++ = unpack555(*src++);
    do {
        dst[1] = unpack555(src[1]);
        dst[0] = unpack555(src[0]);
        src += 2;
        dst += 2;
    } while (--pairs > 0);
}

/* 16 bit 565 -> 32 bit RGBA */
static uint unpack565(uint w)
{
    return 0xff000000u | (((w << 3) | 7) & 0xff) << 16 | ((((w << 5) >> 8) | 3) & 0xff) << 8 | (((w >> 8) & 0xff) | 7);
}

void Video_565ToRgba32(uint *dst, ushort *src, uint count)
{
    int pairs = (int)(count >> 1);
    if (count & 1)
        *dst++ = unpack565(*src++);
    do {
        dst[1] = unpack565(src[1]);
        dst[0] = unpack565(src[0]);
        src += 2;
        dst += 2;
    } while (--pairs > 0);
}

/* 16 bit -> 32 bit the other way round (partial register shifts) */
static uint unpack565alt(uint w)
{
    uint e = (w & 0xffff) << 5;
    e = (e & 0xffff0000u) | ((e & 0xffff) >> 3);
    e <<= 1;
    e = (e & ~0xffu) | ((e & 0xff) >> 2);
    e <<= 2;
    return e;
}

void Video_565AltToRgba32(uint *dst, ushort *src, uint count)
{
    int pairs = (int)(count >> 1);
    if (count & 1)
        *dst++ = unpack565alt(*src++);
    do {
        dst[1] = unpack565alt(src[1]);
        dst[0] = unpack565alt(src[0]);
        src += 2;
        dst += 2;
    } while (--pairs > 0);
}

/* Copies `rows` rows of `width` bytes from src (at srcX / srcY, pitch srcPitch) to dst.  The row offsets are computed with
 * 16 bit multiplies (MUL BX / MUL DX): y * pitch wraps in the low halves.  Rows are a do-while loop (rows < 1 copies one). */
void Video_CopyRect(byte *src, byte *dst, int srcX, uint srcY, int dstX, uint dstY, uint width, int rows,
                    uint srcPitch, uint dstPitch)
{
    uint prod;
    int srcSkip, dstSkip;
    uint dwords = width >> 2, tail = width & 3;

    prod = (srcY & 0xffff) * (srcPitch & 0xffff);
    src += srcX + ((srcY & 0xffff0000u) | prod);
    prod = (dstY & 0xffff) * (dstPitch & 0xffff);
    dst += dstX + ((dstY & 0xffff0000u) | prod);
    srcSkip = srcPitch - width;
    dstSkip = dstPitch - width;
    if (tail != 0) {
        do {
            uint i;
            for (i = 0; i < dwords; i++) { *(uint *)dst = *(uint *)src; src += 4; dst += 4; }
            for (i = 0; i < tail; i++)    { *dst++ = *src++; }
            dst += dstSkip;
            src += srcSkip;
        } while (--rows > 0);
    } else if (dstSkip != 0) {
        do {
            uint i;
            for (i = 0; i < dwords; i++) { *(uint *)dst = *(uint *)src; src += 4; dst += 4; }
            dst += dstSkip;
            src += srcSkip;
        } while (--rows > 0);
    } else {
        do {
            uint i;
            for (i = 0; i < dwords; i++) { *(uint *)dst = *(uint *)src; src += 4; dst += 4; }
            src += srcSkip;
        } while (--rows > 0);
    }
}

/* the same with the destination first (the Smush callers' argument order) */
void Video_CopyRectDstFirst(byte *dst, byte *src, int dstX, uint dstY, int srcX, uint srcY, uint width, int rows,
                            uint dstPitch, uint srcPitch)
{
    Video_CopyRect(src, dst, srcX, srcY, dstX, dstY, width, rows, srcPitch, dstPitch);
}

/* ===================================================================================================================
 *  generic converters through RGBA
 * =================================================================================================================== */

#define VP(p, o) (*(int *)((byte *)(p) + (o)))

/* pixels in the format `fmt` -> RGBA bytes (R, G, B, A).  Returns 0, or -1 for a format it cannot handle.
 * palette: used for palettised pixels when the format has none. */
int gra_ConvertToLecColor(void *src, void *fmt_, int count, byte *palette, byte *dst)
{
    VideoBitmap *fmt = (VideoBitmap *)fmt_;
    int type = fmt->type;

    if (type == 1 && fmt->bytesPerPixel == 2) {         /* the common 15 / 16 bit layouts */
        if (fmt->shiftR == 10 && fmt->shiftG == 5 && fmt->shiftB == 0) {
            Video_555ToRgba32((uint *)dst, (ushort *)src, count);
            return 0;
        }
        if (fmt->shiftR == 0 && fmt->shiftG == 5 && fmt->shiftB == 0xb) {
            Video_565AltToRgba32((uint *)dst, (ushort *)src, count);
            return 0;
        }
        if (fmt->shiftR == 0xb && fmt->shiftG == 5 && fmt->shiftB == 0) {
            Video_565ToRgba32((uint *)dst, (ushort *)src, count);
            return 0;
        }
    }
    if (type == 0) {
        byte *table = (byte *)fmt->bitsR;               /* the palette of the bitmap, or the caller's */
        if (table == 0 && (table = palette, palette == 0))
            return -1;
        Video_ExpandIndexed8(dst, (byte *)src, count, 4, table);
        return 0;
    }
    if (type != 1 && type != 2)
        return -1;
    {
        byte maskR = (byte)g_adwVideoMask[fmt->bitsR], maskG = (byte)g_adwVideoMask[fmt->bitsG], maskB = (byte)g_adwVideoMask[fmt->bitsB];
        byte maskA = 0;
        int bpp = fmt->bytesPerPixel;

        if (type == 2)
            maskA = (byte)g_adwVideoMask[fmt->bitsA];
        if (bpp != 2 && bpp != 3 && bpp != 4)
            return -1;
        for (; count != 0; count--) {
            uint x;
            if (bpp == 2) { x = *(ushort *)src; src = (byte *)src + 2; }
            else if (bpp == 3) { x = *(uint *)src & 0xffffff; src = (byte *)src + 3; }
            else { x = *(uint *)src; src = (byte *)src + 4; }
            dst[0] = (byte)(((x >> (fmt->shiftR & 0x1f)) << (fmt->lossR & 0x1f)) & maskR);
            dst[1] = (byte)(((x >> (fmt->shiftG & 0x1f)) << (fmt->lossG & 0x1f)) & maskG);
            dst[2] = (byte)(((x >> (fmt->shiftB & 0x1f)) << (fmt->lossB & 0x1f)) & maskB);
            dst[3] = type == 2 ? (byte)(((x >> (fmt->shiftA & 0x1f)) << (fmt->lossA & 0x1f)) & maskA) : 0xff;
            dst += 4;
        }
    }
    return 0;
}

/* RGBA bytes -> pixels in the format `fmt` (1 to 4 bytes per pixel).  Returns 0 or -1. */
int gra_ConvertFromLecColor(void *dst, void *fmt_, int count, int unused, byte *src)
{
    VideoBitmap *fmt = (VideoBitmap *)fmt_;
    int type = fmt->type;

    if (type == 1) {
        if (fmt->bytesPerPixel == 2) {
            if (fmt->shiftR == 10 && fmt->shiftG == 5 && fmt->shiftB == 0) {
                Video_Rgba32To555((ushort *)dst, (uint *)src, count);
                return 0;
            }
            if (fmt->shiftR == 0 && fmt->shiftG == 5 && fmt->shiftB == 0xb) {
                Video_Rgba32To565Alt((ushort *)dst, (uint *)src, count);
                return 0;
            }
            if (fmt->shiftR == 0xb && fmt->shiftG == 5 && fmt->shiftB == 0) {
                Video_Rgba32To565((ushort *)dst, (uint *)src, count);
                return 0;
            }
        }
    } else if (type != 2) {
        return -1;
    }
    {
        byte maskR = (byte)g_adwVideoMask[fmt->bitsR], maskG = (byte)g_adwVideoMask[fmt->bitsG], maskB = (byte)g_adwVideoMask[fmt->bitsB];
        byte maskA = 0;
        int bpp = fmt->bytesPerPixel;

        if (type == 2)
            maskA = (byte)g_adwVideoMask[fmt->bitsA];
        if (bpp < 1 || bpp > 4)
            return -1;
        for (; count != 0; count--) {
            uint pix = (((uint)(src[0] & maskR) << (fmt->shiftR & 0x1f)) >> (fmt->lossR & 0x1f)) |
                       (((uint)(src[1] & maskG) << (fmt->shiftG & 0x1f)) >> (fmt->lossG & 0x1f)) |
                       (((uint)(src[2] & maskB) << (fmt->shiftB & 0x1f)) >> (fmt->lossB & 0x1f));
            if (type == 2)
                pix |= ((uint)(src[3] & maskA) << (fmt->shiftA & 0x1f)) >> (fmt->lossA & 0x1f);
            if (bpp == 1) {
                *(byte *)dst = (byte)pix;
            } else if (bpp == 2) {
                *(ushort *)dst = (ushort)pix;
            } else if (bpp == 3) {
                ((byte *)dst)[0] = (byte)pix;
                ((byte *)dst)[1] = (byte)(pix >> 8);
                ((byte *)dst)[2] = (byte)(pix >> 16);
            } else {
                *(uint *)dst = pix;
            }
            dst = (byte *)dst + bpp;
            src += 4;
        }
    }
    return 0;
}


/* Converts `count` pixels from the format `srcFmt` (src) to `dstFmt` (dst), in pieces of at most 0x500 pixels through the
 * RGBA scratch rows.  Same format: a copy.  `expandTable`: a precomputed table (palette expanded to the destination
 * format, or 16 bit index -> pixel) for the indexed sources.  `palette`: see gra_ConvertToLecColor.  Returns 0 or -1. */
int gra_ConvertCopy(byte *src, void *srcFmt_, int count, byte *palette, byte *dst, void *dstFmt_,
                              byte *expandTable)
{
    VideoBitmap *srcFmt = (VideoBitmap *)srcFmt_, *dstFmt = (VideoBitmap *)dstFmt_;
    int piece;
    int srcRgba, dstRgba;

    if (srcFmt->bitsPerPixel == dstFmt->bitsPerPixel && srcFmt->type == dstFmt->type &&
        ((srcFmt->type != 1 && srcFmt->type != 2) ||
         (srcFmt->shiftR == dstFmt->shiftR && srcFmt->shiftG == dstFmt->shiftG && srcFmt->shiftB == dstFmt->shiftB))) {
        msc_MemCopy(dst, src, dstFmt->bytesPerPixel * count);
        return 0;
    }
    if (expandTable != 0) {
        if (srcFmt->type == 0 && srcFmt->bytesPerPixel == 1) {
            Video_ExpandIndexed8(dst, src, count, dstFmt->bytesPerPixel, expandTable);
            return 0;
        }
        if (srcFmt->bytesPerPixel == 2 && dstFmt->type != 0) {
            Video_ExpandIndexed16(dst, (ushort *)src, count, dstFmt->bytesPerPixel, expandTable);
            return 0;
        }
    }
    /* 32 bit RGBA byte order (R, G, B, A at shifts 0, 8, 16): no conversion needed on that side */
    srcRgba = srcFmt->type == 2 && srcFmt->bytesPerPixel == 4 && srcFmt->shiftR == 0 && srcFmt->shiftG == 8 && srcFmt->shiftB == 0x10;
    dstRgba = dstFmt->type == 2 && dstFmt->bytesPerPixel == 4 && dstFmt->shiftR == 0 && dstFmt->shiftG == 8 && dstFmt->shiftB == 0x10;
    piece = count > 0x4ff ? 0x500 : count;
    if (piece < 1)
        return 0;
    for (;;) {
        int rc;

        if (srcRgba) {
            rc = gra_ConvertFromLecColor(dst, dstFmt, piece, (int)palette, src);
        } else if (dstRgba) {
            rc = gra_ConvertToLecColor(src, srcFmt, piece, palette, dst);
        } else {
            byte *tmp;

            g_nVideoScratchFlip++;
            tmp = g_abVideoScratch + (g_nVideoScratchFlip & 1) * 0x1400;
            if (gra_ConvertToLecColor(src, srcFmt, piece, palette, tmp) != 0)
                return -1;
            rc = gra_ConvertFromLecColor(dst, dstFmt, piece, (int)palette, tmp);
        }
        if (rc != 0)
            return -1;
        count -= piece;
        src += srcFmt->bytesPerPixel * piece;
        dst += dstFmt->bytesPerPixel * piece;
        piece = count > 0x4ff ? 0x500 : count;
        if (piece < 1)
            return 0;
    }
}

/* Allocates a bitmap of `width` x `height` pixels of format `format` (-1: the display's format, 0 / 1: 8 bit without /
 * with a 256 entry palette, 2..12: 15, 16, 24, 16 with alpha and 32 bit variants) through the module's allocator
 * (services[0](size, file, line)); *out receives the header.  Returns 0, -101 (out of memory) or -1 (unknown format). */
#define LOGF ((void (*)(const char *, const char *, int, int))msc_error_SaveString)    /* vsprintf into the Smush log ring */

int bmp_bitmap_Alloc(void *out_, int width, int height, int format)
{
    VideoBitmap **out = (VideoBitmap **)out_;
    int paletteEntries = 0, bytesPerPixel;
    byte *mem;
    VideoBitmap *b;

    switch (format) {
    case -1:
        if (g_pVideoDisplayFormat == 0) {
            LOGF((const char *)IMG_ADDR(0x004f3d40), s_C__grimsrc_libs_lecsmush_insane__004f3d64, 0xbe, format);
            return -1;
        }
        bytesPerPixel = ((VideoBitmap *)((int (*)(void))g_pVideoDisplayFormat[1])())->bytesPerPixel;
        break;
    case 0:  bytesPerPixel = 1; break;
    case 1:  paletteEntries = 0x100; bytesPerPixel = 1; break;
    case 2: case 3: case 5: case 7: case 8: case 10:
        bytesPerPixel = 2; break;
    case 4: case 9:
        bytesPerPixel = 3; break;
    case 6: case 11: case 12:
        bytesPerPixel = 4; break;
    default:
        LOGF((const char *)IMG_ADDR(0x004f3d40), s_C__grimsrc_libs_lecsmush_insane__004f3d64, 0xc4, format);
        return -1;
    }
    mem = ((byte *(*)(int, const char *, int))g_pVideoMemory[0])(bytesPerPixel * height * width + paletteEntries * 4 + 0x5c,
                                                                  s_C__grimsrc_libs_lecsmush_insane__004f3d64, 200);
    if (mem == 0)
        return -101;
    b = (VideoBitmap *)(mem + 8);
    *out = b;
    b->data = mem + 0x5c;
    b->width = width;
    b->pitch = bytesPerPixel * width;
    b->height = height;
    b->bytesPerPixel = bytesPerPixel;
    b->field1c = 0;
    b->field18 = 0;
    switch (format) {
    case -1: {
        VideoBitmap *d;
        d = (VideoBitmap *)((int (*)(void))g_pVideoDisplayFormat[1])();
        b->bitsPerPixel = d->bitsPerPixel;
        d = (VideoBitmap *)((int (*)(void))g_pVideoDisplayFormat[1])();
        b->type = d->type;
        d = (VideoBitmap *)((int (*)(void))g_pVideoDisplayFormat[1])();
        b->bitsR = d->bitsR;
        b->bitsG = d->bitsG;
        d = (VideoBitmap *)((int (*)(void))g_pVideoDisplayFormat[1])();
        memcpy(&b->bitsR, &d->bitsR, 0x30);         /* 12 dwords from +0x24: the channel layout */
        return 0; }
    case 0:
        b->bitsPerPixel = 8;
        b->type = 0;
        b->bitsG = paletteEntries;
        b->bitsR = 0;
        return 0;
    case 1:
        b->bitsPerPixel = 8;
        b->type = 0;
        b->bitsG = paletteEntries;
        b->bitsR = (int)b->data;            /* (sic) the palette pointer is the pixel pointer */
        return 0;
    case 2: case 7:                         /* 15 bit: 5-5-5 */
        b->bitsPerPixel = 15;
        b->type = 1;
        b->bitsR = b->bitsG = b->bitsB = 5;
        b->shiftR = format == 2 ? 10 : 0;
        b->shiftG = 5;
        b->shiftB = format == 2 ? 0 : 10;
        b->lossR = b->lossG = b->lossB = 3;
        return 0;
    case 3: case 8:                         /* 16 bit: 5-6-5 */
        b->bitsPerPixel = 16;
        b->type = 1;
        b->bitsR = 5; b->bitsG = 6; b->bitsB = 5;
        b->shiftR = format == 3 ? 0xb : 0;
        b->shiftG = 5;
        b->shiftB = format == 3 ? 0 : 0xb;
        b->lossR = 3; b->lossG = 2; b->lossB = 3;
        return 0;
    case 4: case 9:                         /* 24 bit */
        b->bitsPerPixel = 0x18;
        b->type = 1;
        b->bitsR = b->bitsG = b->bitsB = 8;
        b->shiftR = format == 4 ? 0x10 : 0;
        b->shiftG = 8;
        b->shiftB = format == 4 ? 0 : 0x10;
        b->lossR = b->lossG = b->lossB = 0;
        return 0;
    case 5: case 10:                        /* 16 bit: 1-5-5-5 with alpha */
        b->bitsPerPixel = 0x10;
        b->type = 2;
        b->bitsR = b->bitsG = b->bitsB = 5;
        b->bitsA = 1;
        b->shiftR = format == 5 ? 10 : 0;
        b->shiftG = 5;
        b->shiftB = format == 5 ? 0 : 10;
        b->shiftA = 0xf;
        b->lossR = b->lossG = b->lossB = 3;
        b->lossA = 7;
        return 0;
    default:                                /* 6, 11, 12: 32 bit with alpha */
        b->bitsPerPixel = 0x20;
        b->type = 2;
        b->bitsR = b->bitsG = b->bitsB = 8;
        b->bitsA = 8;
        b->shiftR = format == 6 ? 0x10 : (format == 11 ? 0 : 0x18);
        b->shiftG = format == 12 ? 0x10 : 8;
        b->shiftB = format != 6 ? 8 : 0;
        b->shiftA = format != 12 ? 0x18 : 0;
        b->lossR = b->lossG = b->lossB = 0;
        b->lossA = 0;
        return 0;
    }
}

#undef VP
#endif /* GRIM_EXE */
