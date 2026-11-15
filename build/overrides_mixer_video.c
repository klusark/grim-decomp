/* Readable C for bmp_bitmap_Alloc, the bitmap allocator of the Smush video module (module "VIDEO" of lecsmush: Bitmap.c;
 * GRIMFANDANGO.EXE 0x004ce3e0).
 *
 * A VideoBitmap is a small header (0x54 bytes) in front of the pixels with the description of the pixel format:
 * type 0 = palettised, 1 = RGB, 2 = RGB with alpha; per channel the number of bits, the shift of the channel in the pixel
 * and the loss (8 - bits).
 *
 * The rest of the module (the leaf converters Video_*, gra_ConvertToLecColor / FromLecColor / gra_ConvertCopy, the rect
 * copies) is generated from Ghidra again: build/mixdiff/video_test.c finds no difference between it and the original
 * machine code.  bmp_bitmap_Alloc stays: its second switch (on the format, at 0x004ce4a6) has no bounds check of its own,
 * so the decompiler cannot recover the jump table, and a jump-table override prints only the first case of each shared
 * destination (formats 7..12 would fall through).  Differential test: build/mixdiff/video_test.c. */
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

extern int *g_pVideoMemory __asm__("_g_pVideo_memory_services");        /* "MEMORY workspace" services: [0] allocate(size, file, line) */
extern int *g_pVideoDisplayFormat __asm__("_g_dwVideo_video_services"); /* [1]() returns the VideoBitmap of the display */


/* Allocates a bitmap of `width` x `height` pixels of format `format` (-1: the display's format, 0 / 1: 8 bit without /
 * with a 256 entry palette, 2..12: 15, 16, 24, 16 with alpha and 32 bit variants) through the module's allocator
 * (services[0](size, file, line)); *out receives the header.  Returns 0, -101 (out of memory) or -1 (unknown format, logged
 * with msc_error_SaveString into the Smush log ring). */

int bmp_bitmap_Alloc(void *out_, int width, int height, int format)
{
    VideoBitmap **out = (VideoBitmap **)out_;
    int paletteEntries = 0, bytesPerPixel;
    byte *mem;
    VideoBitmap *b;

    switch (format) {
    case -1:
        if (g_pVideoDisplayFormat == 0) {
            msc_error_SaveString(s__s__line__s__Type__d_not_support_004f3d40, s_C__grimsrc_libs_lecsmush_insane__004f3d64, 0xbe, format);
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
        msc_error_SaveString(s__s__line__s__Type__d_not_support_004f3d40, s_C__grimsrc_libs_lecsmush_insane__004f3d64, 0xc4, format);
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
#endif /* GRIM_EXE */
