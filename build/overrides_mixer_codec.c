/* Readable C for the assembly part of the Smush "Blocky16" frame decoder (module "FLOBDEC insane blocky16", the codec of
 * the 16 bit video frames; GRIMFANDANGO.EXE 0x004cc250 - 0x004cdb80).
 *
 * A frame (Blocky16_DecodeFrame) is a header (Blocky16Header) followed by the compressed data.  Method 2 is the real
 * codec: the picture is cut into 8x8 pixel blocks, each coded by an opcode byte followed by its operands:
 *     00..f5  copy the block from the previous frame, displaced by a motion vector (index into the table of 255 vectors
 *             g_asBlkMotion, or f5: an explicit 16 bit vector follows)
 *     f6      copy the block from the frame before the previous one (fixed displacement)
 *     f7, f8  two colours (f7: two indexes into the 256 entry colour table of the header, f8: two 16 bit pixels) and the
 *             number of a "split mask" (see fob_block_maketiles): the pixels on one side of the line get the first
 *             colour, the others the second
 *     f9..fc  fill with one of the four colours of the header
 *     fd      fill with a colour of the 256 entry colour table
 *     fe      fill with a 16 bit pixel
 *     ff      the block is cut into four 4x4 blocks, which are coded the same way (opcode set of block16_RenderBlock4)
 * and the 4x4 blocks again can be cut into four 2x2 blocks (block16_RenderBlock2: raw pixels instead of the splits).
 * The three block decoders are hand-written assembly with a register convention in the original (ESI = stream, EDI =
 * destination, EBP = pitch in bytes, state in the globals of g_BlkDec); here they take the stream and destination as
 * parameters and return the advanced stream pointer.  Rows are copied as 32 bit words in the same order as the original so
 * that overlapping copies (a small displacement) give the same pixels.
 *
 * Differential tests: build/mixdiff/codec_test.c (docs/notes/mixer.md). */
#include "ghidra_types.h"

#ifdef GRIM_EXE
#include "globals.h"
#include "functions.h"

typedef struct Blocky16Header {     /* the frame header, followed by the data (0x230 bytes in) */
    byte b00[8];                    /* 00 */
    short width;                    /* 08 */
    short w0a;                      /* 0a */
    short height;                   /* 0c */
    short h0e;                      /* 0e */
    short seq;                      /* 10 frame number (0: first frame, resets the buffers) */
    byte method;                    /* 12 0..8, see Blocky16_DecodeFrame */
    byte swap;                      /* 13 1: swap the current and the previous buffer afterwards, 2: rotate all three */
    byte b14[4];                    /* 14 */
    short colors[4];                /* 18 the four colours of opcodes f9..fc */
    byte fillPixel[4];              /* 20 pixel value (as the display stores it) the buffers are cleared with at frame 0 */
    int dataSize;                   /* 24 size of the run-length coded data (method 5) */
    ushort pairColors[256];         /* 28 colour table (methods 6, 7, 8 and opcodes f7, fd) */
    short depth;                    /* 228 bits per pixel of the output (0: 8) */
    byte b22a[6];                   /* 22a */
    byte data[1];                   /* 230 */
} Blocky16Header;

/* the decoder state shared by the block decoders: set up by Blocky16_DecodeBlocks (0x00906c48 - 0x00906c74) */
typedef struct BlockyDecoderState {
    uint rowSkip;                   /* 00 bytes to skip after a row of blocks (7 pixel rows) */
    short *motion;                  /* 04 motion vector table (255 entries) */
    byte *split8;                   /* 08 8x8 split masks (Blocky8Split, 0x184 bytes each) */
    byte *colors;                   /* 0c the header colours, biased so that colors[opcode * 2] works for f9..fc */
    int prevOffset;                 /* 10 bytes from the current buffer to the previous frame */
    byte rowsLeft;                  /* 14 */
    byte colsLeft;                  /* 15 */
    byte pad16[2];
    uint width;                     /* 18 */
    byte colsPerRow;                /* 1c */
    byte pad1d[3];
    int prev2Offset;                /* 20 bytes from the current buffer to the frame before */
    ushort *pairColors;             /* 24 */
    byte *split4;                   /* 28 4x4 split masks (Blocky4Split, 0x80 bytes each) */
} BlockyDecoderState;

typedef struct Blocky8Split {       /* 0x184 bytes, 256 of them at 0x00906c80 */
    ushort onesPixel[64];           /* 000 pixel offsets (in a frame of the current width) of the cells on one side */
    ushort zerosPixel[64];          /* 080 and of the others */
    byte onesCell[64];              /* 100 cell numbers (row * 8 + column) */
    byte zerosCell[64];             /* 140 */
    byte numOnes, numZeros;         /* 180 */
    byte pad[2];
} Blocky8Split;

typedef struct Blocky4Split {       /* 0x80 bytes, 256 of them at 0x0091f0a0 */
    ushort onesPixel[16];
    ushort zerosPixel[16];
    byte onesCell[16];
    byte zerosCell[16];
    byte numOnes, numZeros;
    byte pad[30];
} Blocky4Split;

extern BlockyDecoderState g_BlkDec __asm__("_g_stBlockyDecState");
extern short g_asBlkMotion[255] __asm__("_g_asBlockyMotion");
extern Blocky8Split g_aBlkSplit8[256] __asm__("_g_aBlockySplit8");
extern Blocky4Split g_aBlkSplit4[256] __asm__("_g_aBlockySplit4");
extern int g_anBlkSplit4X[16] __asm__("_g_anBlockySplit4X");     /* the 16 edge points of a 4x4 block: row ... */
extern int g_anBlkSplit4Y[16] __asm__("_g_anBlockySplit4Y");     /* ... and column */
extern int g_anBlkSplit8X[16] __asm__("_g_anBlockySplit8X");
extern int g_anBlkSplit8Y[16] __asm__("_g_anBlockySplit8Y");

/* the state of the frame decoder (see Blocky16_DecodeFrame) */
extern void *vOutputFn __asm__("_g_pFob_blit_routine");          /* callback receiving the decoded frame (fob_flobdec_blocky16_config) */
extern byte *vCur __asm__("_g_pFob_blk16_render_buffer");                    /* buffer the current frame is decoded into */
extern byte *vExpand __asm__("_g_pbBlkExpand");              /* 64K entry table: 16 bit pixel -> display pixel */
extern int vShiftR __asm__("_g_nFob_translation_shiftr");                 /* channel shifts of the display format the table was made for */
extern int vShiftG __asm__("_g_nFob_translation_shiftg");
extern int vShiftB __asm__("_g_nFob_translation_shiftb");
extern int *vBitmap0 __asm__("_g_pBlkBitmap0");              /* pixel format descriptors of the three buffers: [0] pixels, [1] width, [2] height */
extern int *vBitmap1 __asm__("_g_pBlkBitmap1");
extern int *vBitmap2 __asm__("_g_pBlkBitmap2");
extern byte *vOutput __asm__("_g_pbBlkOutput");              /* the buffer the last frame was left in (0: none yet) */
extern byte *vPrev2 __asm__("_g_pFob_blk16_key_buffer");                /* frame before the previous one */
extern byte *vPrev __asm__("_g_pFob_blk16_delta_buffer");                  /* previous frame */
extern int vLastSeq __asm__("_g_nBlkLastSeq");               /* number of the last frame decoded (-1 at the start) */
extern int vFrameCount __asm__("_g_nBretsFrameCount");

static inline uint ld32(const void *p) { uint v; __builtin_memcpy(&v, p, 4); return v; }
static inline void st32(void *p, uint v) { __builtin_memcpy(p, &v, 4); }
static inline ushort ld16(const void *p) { ushort v; __builtin_memcpy(&v, p, 2); return v; }
static inline void st16(void *p, ushort v) { __builtin_memcpy(p, &v, 2); }

/* ===================================================================================================================
 *  option reader
 * =================================================================================================================== */

/* Reads (key, value) pairs ending with key 0.  Key 1 sets the callback that receives the decoded frame instead of the
 * default blit (see Blocky16_DecodeFrame); any other key is an error (-1). */
int fob_flobdec_blocky16_config(int key, ...)
{
    __builtin_va_list ap;

    __builtin_va_start(ap, key);
    while (key != 0) {
        if (key != 1) {
            __builtin_va_end(ap);
            return -1;
        }
        vOutputFn = (void *)__builtin_va_arg(ap, uint);
        key = __builtin_va_arg(ap, int);
    }
    __builtin_va_end(ap);
    return 0;
}

/* ===================================================================================================================
 *  split masks
 * =================================================================================================================== */

enum { FILL_TOWARDS_ROW0, FILL_TOWARDS_LASTROW, FILL_TOWARDS_COL0, FILL_TOWARDS_LASTCOL, FILL_NONE };

/* Where the edge point of a block lies: 0 left column, 1 last column, 2 top row, 3 bottom row, 4 inside (not on an edge). */
static int edge_class(int row, int col, int size)
{
    if (row == 0)
        return 0;
    if (row == size - 1)
        return 1;
    if (col == 0)
        return 2;
    return (col != size - 1) + 3;
}

/* What is filled in after the line of two edge points of the given classes is drawn, from every cell of the line towards
 * the edge: [class of the first point][class of the second point]. */
static const byte kSplitFill[5][5] = {
    { FILL_TOWARDS_ROW0,    FILL_TOWARDS_LASTCOL, FILL_TOWARDS_ROW0,    FILL_TOWARDS_ROW0,    FILL_TOWARDS_ROW0 },
    { FILL_TOWARDS_LASTCOL, FILL_TOWARDS_LASTROW, FILL_TOWARDS_LASTROW, FILL_TOWARDS_LASTROW, FILL_TOWARDS_LASTROW },
    { FILL_TOWARDS_ROW0,    FILL_TOWARDS_LASTROW, FILL_TOWARDS_COL0,    FILL_TOWARDS_ROW0,    FILL_TOWARDS_COL0 },
    { FILL_TOWARDS_ROW0,    FILL_TOWARDS_LASTROW, FILL_TOWARDS_ROW0,    FILL_TOWARDS_LASTCOL, FILL_TOWARDS_LASTCOL },
    { FILL_TOWARDS_ROW0,    FILL_TOWARDS_LASTROW, FILL_TOWARDS_COL0,    FILL_TOWARDS_LASTCOL, FILL_NONE },
};

/* Builds the "split masks" of the 8x8 (size 8) or 4x4 (size 4) blocks: one for every pair of the 16 edge points (a line
 * from one to the other cuts the block in two).  The cells of the line, and everything between the line and the edge in the
 * direction given by kSplitFill, are "ones"; the other cells "zeros".  Both lists are stored as cell numbers
 * (Blocky8Split / Blocky4Split of g_aBlkSplit8 / g_aBlkSplit4, entry first * 16 + second), in descending order; the pixel
 * offsets the decoder needs are made from them by fob_blk16_configure when the frame width is known. */
void fob_block_maketiles(int size)
{
    int grid[64];
    const int *rowOf, *colOf;
    int cells = size * size;
    int first, second, k;

    if (size == 8) {
        for (k = 0; k < 256; k++)
            g_aBlkSplit8[k].numOnes = g_aBlkSplit8[k].numZeros = 0;
        rowOf = g_anBlkSplit8X;
        colOf = g_anBlkSplit8Y;
    } else if (size == 4) {
        for (k = 0; k < 256; k++)
            g_aBlkSplit4[k].numOnes = g_aBlkSplit4[k].numZeros = 0;
        rowOf = g_anBlkSplit4X;
        colOf = g_anBlkSplit4Y;
    } else {
        return;
    }
    for (first = 0; first < 16; first++) {
        for (second = 0; second < 16; second++) {
            int row0 = rowOf[first], col0 = colOf[first];
            int row1 = rowOf[second], col1 = colOf[second];
            int class0 = edge_class(row0, col0, size), class1 = edge_class(row1, col1, size);
            int drow = row0 > row1 ? row0 - row1 : row1 - row0;
            int dcol = col0 > col1 ? col0 - col1 : col1 - col0;
            int len = drow > dcol ? drow : dcol;
            int step, fill;

            for (k = 0; k < cells; k++)
                grid[k] = 0;
            /* the line from point 0 to point 1, len + 1 cells */
            fill = kSplitFill[class0][class1];
            for (step = 0; step <= len; step++) {
                int row = row0, col = col0, m;

                if (len > 0) {
                    row = (row1 * (len - step) + row0 * step + (len >> 1)) / len;
                    col = (col1 * (len - step) + col0 * step + (len >> 1)) / len;
                }
                grid[row * size + col] = 1;
                switch (fill) {
                case FILL_TOWARDS_ROW0:
                    for (m = row; m >= 0; m--)
                        grid[m * size + col] = 1;
                    break;
                case FILL_TOWARDS_LASTROW:
                    for (m = row; m < size; m++)
                        grid[m * size + col] = 1;
                    break;
                case FILL_TOWARDS_COL0:
                    for (m = col; m >= 0; m--)
                        grid[row * size + m] = 1;
                    break;
                case FILL_TOWARDS_LASTCOL:
                    for (m = col; m < size; m++)
                        grid[row * size + m] = 1;
                    break;
                }
            }
            /* the lists, last cell first */
            if (size == 8) {
                Blocky8Split *s = &g_aBlkSplit8[first * 16 + second];

                for (k = cells - 1; k >= 0; k--) {
                    if (grid[k])
                        s->onesCell[s->numOnes++] = (byte)k;
                    else
                        s->zerosCell[s->numZeros++] = (byte)k;
                }
            } else {
                Blocky4Split *s = &g_aBlkSplit4[first * 16 + second];

                for (k = cells - 1; k >= 0; k--) {
                    if (grid[k])
                        s->onesCell[s->numOnes++] = (byte)k;
                    else
                        s->zerosCell[s->numZeros++] = (byte)k;
                }
            }
        }
    }
}

/* ===================================================================================================================
 *  block decoders
 * =================================================================================================================== */

/* Copies the 32 bit words `bytes` wide of `rows` row pairs: row r + pairDistance of the block first, then row r, both from
 * their position + displacement, one word at a time (the order matters when the displacement is small). */
static void copy_rows(byte *dst, int disp, int pitch, int pairDistance, int rowPairs, int words)
{
    byte *hi = dst + pairDistance * pitch;
    byte *lo = dst;
    int r, d;

    for (r = 0; r < rowPairs; r++) {
        for (d = 0; d < words; d++) {
            uint a = ld32(hi + disp + d * 4);
            uint b = ld32(lo + disp + d * 4);
            st32(hi + d * 4, a);
            st32(lo + d * 4, b);
        }
        hi += pitch;
        lo += pitch;
    }
}

static void fill_rows(byte *dst, uint pair, int pitch, int rows, int words)
{
    int r, d;

    for (r = 0; r < rows; r++)
        for (d = 0; d < words; d++)
            st32(dst + r * pitch + d * 4, pair);
}

/* writes the first colour at the cells of the "ones" list and the second at those of the "zeros" list; the lists are
 * processed as do-while loops (a count of 0 still writes one pixel) */
static void split_fill(ushort *dst, const ushort *onesPixel, int numOnes, const ushort *zerosPixel, int numZeros, uint colors)
{
    do {
        dst[*onesPixel++] = (ushort)colors;
    } while (--numOnes > 0);
    colors >>= 16;
    do {
        dst[*zerosPixel++] = (ushort)colors;
    } while (--numZeros > 0);
}

/* 2x2 block: copy (displaced), four raw pixels (ff, f8), four colours of the table (f7), fill, copy from two frames back */
byte *block16_RenderBlock2(byte *src, byte *dst, int pitch)
{
    byte op = *src;
    int disp;
    uint pair;

    if (op <= 0xf5) {
        if (op == 0xf5) {
            disp = (short)ld16(src + 1) * 2;
            src += 3;
        } else {
            disp = g_BlkDec.motion[op] * 2;
            src += 1;
        }
        disp += g_BlkDec.prevOffset;
    } else if (op == 0xff || op == 0xf8) {
        st32(dst, ld32(src + 1));
        st32(dst + pitch, ld32(src + 5));
        return src + 9;
    } else if (op == 0xf7) {
        const ushort *t = g_BlkDec.pairColors;
        uint v = ld32(src + 1);

        st16(dst, t[v & 0xff]);
        st16(dst + 2, t[(v >> 8) & 0xff]);
        st16(dst + pitch, t[(v >> 16) & 0xff]);
        st16(dst + pitch + 2, t[v >> 24]);
        return src + 5;
    } else if (op == 0xfd) {
        pair = ld16(g_BlkDec.pairColors + src[1]);
        pair |= pair << 16;
        st32(dst, pair);
        st32(dst + pitch, pair);
        return src + 2;
    } else if (op == 0xfe) {
        pair = ld16(src + 1);
        pair |= pair << 16;
        st32(dst, pair);
        st32(dst + pitch, pair);
        return src + 3;
    } else if (op >= 0xf9) {
        pair = ld16(g_BlkDec.colors + op * 2);
        pair |= pair << 16;
        st32(dst, pair);
        st32(dst + pitch, pair);
        return src + 1;
    } else {                          /* f6: from two frames back */
        disp = g_BlkDec.prev2Offset;
        src += 1;
    }
    st32(dst, ld32(dst + disp));
    st32(dst + pitch, ld32(dst + pitch + disp));
    return src;
}

/* 4x4 block (opcode set in the file header comment; ff cuts it into four 2x2 blocks) */
byte *block16_RenderBlock4(byte *src, byte *dst, int pitch)
{
    byte op = *src;
    int disp;
    uint pair;

    if (op <= 0xf5) {
        if (op == 0xf5) {
            disp = (short)ld16(src + 1) * 2;
            src += 3;
        } else {
            disp = g_BlkDec.motion[op] * 2;
            src += 1;
        }
        copy_rows(dst, disp + g_BlkDec.prevOffset, pitch, 2, 2, 2);
        return src;
    }
    if (op == 0xff) {
        src = block16_RenderBlock2(src + 1, dst, pitch);
        src = block16_RenderBlock2(src, dst + 4, pitch);
        src = block16_RenderBlock2(src, dst + pitch * 2, pitch);
        return block16_RenderBlock2(src, dst + pitch * 2 + 4, pitch);
    }
    if (op == 0xf8 || op == 0xf7) {
        uint colors;
        const Blocky4Split *s;

        if (op == 0xf7) {
            const ushort *t = g_BlkDec.pairColors;

            colors = (uint)t[src[3]] << 16 | t[src[2]];
            s = (const Blocky4Split *)(g_BlkDec.split4 + src[1] * 0x80);
            src += 4;
        } else {
            colors = ld32(src + 2);
            s = (const Blocky4Split *)(g_BlkDec.split4 + src[1] * 0x80);
            src += 6;
        }
        split_fill((ushort *)dst, s->onesPixel, s->numOnes, s->zerosPixel, s->numZeros, colors);
        return src;
    }
    if (op == 0xfd) {
        pair = ld16(g_BlkDec.pairColors + src[1]);
        src += 2;
    } else if (op == 0xfe) {
        pair = ld16(src + 1);
        src += 3;
    } else if (op >= 0xf9) {
        pair = ld16(g_BlkDec.colors + op * 2);
        src += 1;
    } else {                          /* f6 */
        copy_rows(dst, g_BlkDec.prev2Offset, pitch, 2, 2, 2);
        return src + 1;
    }
    pair |= pair << 16;
    fill_rows(dst, pair, pitch, 4, 2);
    return src;
}

/* 8x8 block */
byte *Blocky16_DecodeBlock8(byte *src, byte *dst, int pitch)
{
    byte op = *src;
    int disp;
    uint pair;

    if (op <= 0xf5) {
        if (op == 0xf5) {
            disp = (short)ld16(src + 1) * 2;
            src += 3;
        } else {
            disp = g_BlkDec.motion[op] * 2;
            src += 1;
        }
        copy_rows(dst, disp + g_BlkDec.prevOffset, pitch, 4, 4, 4);
        return src;
    }
    if (op == 0xff) {
        src = block16_RenderBlock4(src + 1, dst, pitch);
        src = block16_RenderBlock4(src, dst + 8, pitch);
        src = block16_RenderBlock4(src, dst + pitch * 4, pitch);
        return block16_RenderBlock4(src, dst + pitch * 4 + 8, pitch);
    }
    if (op == 0xf8 || op == 0xf7) {
        uint colors;
        const Blocky8Split *s;

        if (op == 0xf7) {
            const ushort *t = g_BlkDec.pairColors;

            colors = (uint)t[src[3]] << 16 | t[src[2]];
            s = (const Blocky8Split *)(g_BlkDec.split8 + src[1] * 0x184);
            src += 4;
        } else {
            colors = ld32(src + 2);
            s = (const Blocky8Split *)(g_BlkDec.split8 + src[1] * 0x184);
            src += 6;
        }
        split_fill((ushort *)dst, s->onesPixel, s->numOnes, s->zerosPixel, s->numZeros, colors);
        return src;
    }
    if (op == 0xfd) {
        pair = ld16(g_BlkDec.pairColors + src[1]);
        src += 2;
    } else if (op == 0xfe) {
        pair = ld16(src + 1);
        src += 3;
    } else if (op >= 0xf9) {
        pair = ld16(g_BlkDec.colors + op * 2);
        src += 1;
    } else {                          /* f6 */
        copy_rows(dst, g_BlkDec.prev2Offset, pitch, 4, 4, 4);
        return src + 1;
    }
    pair |= pair << 16;
    fill_rows(dst, pair, pitch, 8, 4);
    return src;
}

/* Decodes the 8x8 blocks of a frame of `width` x `height` 16 bit pixels into dst.  The block rows are counted in a byte
 * (like the original: 0 rows or columns means 256).  prevOffset / prev2Offset: distance in pixels from dst to the previous
 * frame and the one before; motion: table of 255 vectors; colors: the four colours of opcodes f9..fc; split4 / split8: split
 * masks; pairColors: 256 colour table. */
void Blocky16_DecodeBlocks(byte *dst, byte *src, int prevOffset, int prev2Offset, int width, short *motion,
                           short *colors, int height, int unused, byte *split4, byte *split8, ushort *pairColors)
{
    int pitch = width * 2;
    byte rows, cols;

    g_BlkDec.prevOffset = prevOffset * 2;
    g_BlkDec.prev2Offset = prev2Offset * 2;
    g_BlkDec.width = width;
    g_BlkDec.motion = motion;
    g_BlkDec.colors = (byte *)colors - 0x1f2;
    g_BlkDec.pairColors = pairColors;
    g_BlkDec.split4 = split4;
    g_BlkDec.split8 = split8;
    rows = (byte)((height + 7) >> 3);
    cols = (byte)((width + 7) >> 3);
    g_BlkDec.colsPerRow = cols;
    g_BlkDec.rowSkip = pitch * 7;
    do {
        byte c = cols;

        do {
            src = Blocky16_DecodeBlock8(src, dst, pitch);
            dst += 16;
        } while (--c != 0);
        dst += pitch * 7;
    } while (--rows != 0);
    g_BlkDec.rowsLeft = 0;
    g_BlkDec.colsLeft = 0;
}

/* ===================================================================================================================
 *  frame decoder
 * =================================================================================================================== */

typedef int (*BlkOutputFn)(void *dst, uint *clip, int x, int y, int *bitmap, int palette, byte *expand);

/* Decodes one frame (header + data) into the current buffer and hands it to the output.  dst is the destination bitmap
 * (0: only decode, keeping the buffers up to date), clip the optional clip rectangle, x / y the position, `palette` is
 * passed through to the output and returned (the return value is 1 after the default output, the callback's result after
 * the callback of fob_flobdec_blocky16_config, 0 if the frame was skipped).
 * Methods (hdr->method): 0 raw 16 bit pixels, 1 8x8 block opcodes of the older codec (Blocky16_DecodeHalfRows16), 2 the block codec
 * (Blocky16_DecodeBlocks; only if it is the frame after the last one), 3 / 4 copy of the previous frame / the one before,
 * 5 run-length coded raw pixels, 6 8 bit indexes into the header's colour table, 7 Blocky16_DecodeHalfRows8, 8 run-length coded
 * indexes.  flags bit 2 (with hdr->swap 0): skip methods 2, 3, 4 (seeking).  After the frame the buffers are swapped
 * (hdr->swap 1: current and previous; 2: current -> previous -> before) if this was the next frame in sequence. */
int Blocky16_DecodeFrame(void *dst, uint *clip, int x, int y, int palette, byte *hdrBytes, byte flags)
{
    Blocky16Header *hdr = (Blocky16Header *)hdrBytes;
    uint width = (uint)(int)hdr->width;
    int height = hdr->height;
    int alignedHeight = (height + 7) & ~7;
    byte *data = hdr->data;
    int prevDelta, prev2Delta;
    int result;
    byte *cur, *tmp;

    if (vBitmap0 == 0 || width != (uint)vBitmap0[1] || (uint)alignedHeight != (uint)vBitmap0[2]) {
        int depth;

        Blocky16_flobdec_Reset();
        depth = hdr->depth;
        if (depth == 0)
            depth = 8;
        AllocBuffers(width, alignedHeight, depth);
    }
    prevDelta = vPrev - vCur;
    prev2Delta = vPrev2 - vCur;
    if (dst != 0)
        Blocky16_BuildExpandTable(dst);
    if (hdr->seq == 0) {
        fob_blk16_configure(width);
        gra_SetBuffer((char *)vPrev2, (int)vBitmap0, vBitmap0[1] * vBitmap0[2], (char *)hdr->fillPixel);
        gra_SetBuffer((char *)vPrev, (int)vBitmap0, vBitmap0[1] * vBitmap0[2], (char *)hdr->fillPixel);
        vLastSeq = -1;
    }
    vFrameCount++;
    switch (hdr->method) {
    case 0:
        msc_MemCopy(vCur, data, width * height * 2);
        vOutput = vCur;
        break;
    case 1:
        Blocky16_DecodeHalfRows16(vCur, (ushort *)data, width, height);
        vOutput = vCur;
        break;
    case 2:
        if ((flags & 4) && hdr->swap == 0) {
            vLastSeq = hdr->seq;
            return 0;
        }
        if (hdr->seq == vLastSeq + 1) {
            Blocky16_DecodeBlocks(vCur, data, prevDelta >> 1, prev2Delta >> 1, width, g_asBlkMotion, (short *)hdr->colors, height,
                                  width * 9 - (width & ~7u), (byte *)g_aBlkSplit4, (byte *)g_aBlkSplit8, hdr->pairColors);
            vOutput = vCur;
        }
        break;
    case 3:
    case 4:
        if ((flags & 4) && hdr->swap == 0) {
            vLastSeq = hdr->seq;
            return 0;
        }
        msc_MemCopy(vCur, hdr->method == 3 ? vPrev : vPrev2, width * height * 2);
        vOutput = vCur;
        break;
    case 5:
        msc_rle_DecompressBlock((undefined1 *)vCur, (undefined4)(uint)data, hdr->dataSize);
        vOutput = vCur;
        break;
    case 6: {
        ushort *out = (ushort *)vCur;
        int n = width * height;

        vOutput = vCur;
        if (n != 0) {
            do {
                *out++ = hdr->pairColors[*data++];
            } while (--n != 0);
        }
        break; }
    case 7:
        Blocky16_DecodeHalfRows8(vCur, (byte *)data, width, height, (int)hdr->pairColors);
        vOutput = vCur;
        break;
    case 8: {
        ushort *out = (ushort *)vCur;
        int n = width * height;

        msc_rle_DecompressInitialize((int *)data);
        for (; n != 0; n--)
            *out++ = hdr->pairColors[msc_rle_DecompressGetbyte(0) & 0xff];
        Mem_DumpLog();
        vOutput = vCur;
        break; }
    }
    result = palette;
    if (vOutput != 0 && dst != 0) {
        byte *expand = vExpand;

        if (vShiftR == 0 && vShiftG == 0)
            expand = 0;
        if (vOutputFn == 0) {
            int *bm = vBitmap0;

            if ((uint)vOutput == (uint)bm[0] || ((bm = vBitmap1), (uint)vOutput == (uint)bm[0]) ||
                ((bm = vBitmap2), (uint)vOutput == (uint)bm[0]))
                gra_BlitRectLookup((int *)dst, clip, x, y, bm, (byte *)palette, expand);
            result = 1;
        } else if ((uint)vOutput == (uint)vBitmap0[0]) {
            result = ((BlkOutputFn)vOutputFn)(dst, clip, x, y, vBitmap0, palette, expand);
        } else if ((uint)vOutput == (uint)vBitmap1[0]) {
            result = ((BlkOutputFn)vOutputFn)(dst, clip, x, y, vBitmap1, palette, expand);
        } else if ((uint)vOutput == (uint)vBitmap2[0]) {
            result = ((BlkOutputFn)vOutputFn)(dst, clip, x, y, vBitmap2, palette, expand);
        }
    }
    /* the next frame in sequence: rotate the buffers as the header asks */
    cur = vCur;
    if (hdr->seq == vLastSeq + 1) {
        if (hdr->swap == 1) {
            tmp = vPrev;
            vPrev = cur;
            vCur = tmp;
            vLastSeq = hdr->seq;
            return result;
        }
        if (hdr->swap == 2) {
            tmp = vPrev2;
            vPrev2 = vPrev;
            vCur = tmp;
            vPrev = cur;
        }
    }
    vLastSeq = hdr->seq;
    return result;
}

#endif /* GRIM_EXE */
