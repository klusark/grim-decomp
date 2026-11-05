/* stdPic_LoadInto (0x0047d2d0), Libs/Std/General/stdPic.c: loader of Softimage .pic images, written by hand from the
 * machine code of GRIMFANDANGO.EXE 1.01 (see docs/notes/big_stdpic_loadinto.md; verified by the differential test in
 * build/difftest/big_stdpic_loadinto/).
 *
 * File: a 0x68 byte big-endian header (magic 0x5380f634, version float, comment[80], id "PICT", width, height, ratio float,
 * fields, pad), then channel packets of 4 bytes (chained, size, type, channels mask R 0x80 / G 0x40 / B 0x20 / A 0x10),
 * every packet must have size 8, the list ends with chained == 0.  Then for each row, for each packet: width pixels of the
 * packet's channels, type 0 uncompressed, any other type "mixed RLE" (n < 0x80: n + 1 literal pixels; 0x80: 16 bit
 * big-endian count + one pixel; n > 0x80: n - 0x7f copies of one pixel).  The picture is stored 24 bit RGB (3 bytes per
 * pixel, R G B at +0 +1 +2, the surface pitch between rows) in a surface made with Surface_Create; alpha is read and dropped.
 * `bm` (0x7c bytes) gets the file name, the colour format and a 4 byte block holding the surface pointer at +0x78.
 *
 * What the C keeps from the machine code:
 *  - The function's stack frame from ESP+0x60 to ESP+0x15c is one array `fr`: the packet types are stored at
 *    ESP+0x60 + 4 * index with no bound, so a file with more than 4 packets writes its types over the header (packet 27
 *    replaces width / height with type, 0), the colour format block (packets 30-43, which then goes to `bm` and Surface_Create)
 *    and the Surface_Create description (44-62), and the later pixel loop reads those slots back as types.  From 63 packets
 *    on the original overwrites its return address and arguments (and crashes); the C drops such stores (see FR_N).
 *  - The version and ratio floats are byte-swapped the way the original does it: _ftol of the float read in the wrong byte
 *    order, swap the integer, convert back (the operand of _ftol that Ghidra lost is that float).  Dead values, kept.
 *  - Scratch bytes that survive between pixels: the RLE count byte (ESP+0x11, 0xff after a literal run), the 16 bit count
 *    (ESP+0x14, 0xffff after a repeat run), the run colours R / G (ESP+0x12 / 0x13, before the first run: the 0x20 / 0x40
 *    bits of the last packet's channel mask, which the packet loop parks there) and B (ESP+0x1b).  A failed fread leaves
 *    them as they are; they matter only for truncated files.  Bytes the original never initialises are 0 here.
 *  - No fread of the pixel data is checked, x may run past the row end (writes go on into the next row / past the
 *    buffer), an early return does not close the file, failed asserts continue.
 */
#include "ghidra_types.h"
#ifdef GRIM_EXE
#include "globals.h"
#include "functions.h"

typedef int (__cdecl *PicFreadFn)(int fp, void *dst, uint n);

#define FR_N 63                                  /* dwords ESP+0x60 .. ESP+0x158 */
#define FRB(o) ((byte *)fr + ((o) - 0x60))       /* byte at ESP+o of the original frame */
#define FRW(o) (*(ushort *)FRB(o))
#define FRD(o) (*(uint *)FRB(o))

static uint pic_bswap(uint v)
{
    return (v << 24) | ((v & 0xff00) << 8) | ((v >> 8) & 0xff00) | (v >> 24);
}

/* OVERRIDES: stdPic_LoadInto */
undefined4 stdPic_LoadInto(char *path, undefined4 *bm_, int videoMem, int sysMem)
{
    byte *bm = (byte *)bm_;
    uint fr[FR_N + 1];
    PicFreadFn rd;
    int fp, n, i, j, x, row, idxR, idxG, idxB, idxA;
    uint szR = 0, szG = 0, szB = 0, szA = 0, magic, id, pitch, cnt;
    byte chans, colR, colG, colB = 0, cnt11 = 0, cnt14[2] = {0, 0}, alpha[4];
    byte pkt[4];
    byte *line, *p, *surf;
    float raw;
    short lineBase;

    for (i = 0; i <= FR_N; i++) fr[i] = 0;
    FRD(0xe0) = 8; FRD(0xe4) = 8; FRD(0xe8) = 8; FRD(0xf0) = 8;
    FRD(0xd8) = 1; FRD(0xdc) = 0x18; FRD(0xec) = 0x10;  /* colour format: RGB, 24 bit, 8/8/8, shifts 16/8/0 */

    fp = (*g_pSvcMain->pFopen)(path, &DAT_004ddb18);
    if (fp == 0)
        return 0;
    rd = (PicFreadFn)g_pSvcMain->pFread;
    if (rd(fp, FRB(0x70), 0x68) != 0x68)
        return 0;

    magic = pic_bswap(FRD(0x70));
    raw = *(float *)FRB(0x74);
    FRD(0x70) = magic;
    *(float *)FRB(0x74) = (float)(long long)pic_bswap((uint)(long long)raw);
    id = pic_bswap(FRD(0xc8));
    FRW(0xcc) = (ushort)((FRB(0xcc)[0] << 8) | FRB(0xcc)[1]);
    FRW(0xce) = (ushort)((FRB(0xce)[0] << 8) | FRB(0xce)[1]);
    FRD(0xc8) = id;
    raw = *(float *)FRB(0xd0);
    *(float *)FRB(0xd0) = (float)(long long)pic_bswap((uint)(long long)raw);
    FRW(0xd4) = (ushort)((FRB(0xd4)[0] << 8) | FRB(0xd4)[1]);
    FRW(0xd6) = (ushort)((FRB(0xd6)[0] << 8) | FRB(0xd6)[1]);
    if (magic != 0x5380f634)
        return 0;
    if (id != 0x50494354)                        /* "PICT" */
        return 0;

    /* channel packets */
    idxR = idxG = idxB = idxA = -1;
    n = 0;
    if (rd(fp, pkt, 4) != 4)
        return 0;
    for (;;) {
        chans = pkt[3];
        if (chans & 0x80) idxR = n;
        colG = chans & 0x40;
        if (colG) idxG = n;
        colR = chans & 0x20;
        if (colR) idxB = n;
        if (chans & 0x10) idxA = n;
        if (chans & 0x80) szR = pkt[1] >> 3;
        if (colG) szG = pkt[1] >> 3;
        if (colR) szB = pkt[1] >> 3;
        if (chans & 0x10) szA = pkt[1] >> 3;
        if (n < FR_N) fr[n] = pkt[2];
        if (pkt[1] != 8)
            return 0;
        n++;
        if (pkt[0] == 0)
            break;
        if (rd(fp, pkt, 4) != 4)
            return 0;
    }

    /* the bitmap record */
    for (i = 0; i < 0x7c; i++) bm[i] = 0;
    strncpy((uint *)bm, (uint *)Str_FileNameFromPath(path), 0x1f);
    bm[0x1f] = 0;
    *(uint *)(bm + 0x20) = 0;
    *(uint *)(bm + 0x24) = 0;
    *(uint *)(bm + 0x60) = 0;
    *(uint *)(bm + 0x64) = 1;
    *(uint *)(bm + 0x68) = 0;
    for (i = 0; i < 14; i++) ((uint *)(bm + 0x28))[i] = ((uint *)FRB(0xd8))[i];
    lineBase = *(short *)&DAT_004e77d0;
    *(int *)(bm + 0x78) = (*g_pSvcMain->pAlloc)(4, s_C__grimjedi_Libs_Std_General_std_004e77d8, lineBase + 0x6d);
    if (*(int *)(bm + 0x78) == 0)
        (*g_pSvcMain->pAssertFail)(s_Unable_to_allocate_memory__004e76d4, s_C__grimjedi_Libs_Std_General_std_004e77d8,
                                   (int)*(short *)&DAT_004e77d0 + 0x6e);
    /* Surface_Create description at ESP+0x110: width, height, three dwords Surface_Create overwrites, format */
    for (i = 0; i < 14; i++) ((uint *)FRB(0x124))[i] = ((uint *)(bm + 0x28))[i];
    FRD(0x110) = FRW(0xcc);
    FRD(0x114) = FRW(0xce);
    **(void ***)(bm + 0x78) = Surface_Create(FRB(0x110), videoMem, sysMem, 0);
    if (**(void ***)(bm + 0x78) == 0)
        (*g_pSvcMain->pAssertFail)(s_Unable_to_allocate_memory__004e76d4, s_C__grimjedi_Libs_Std_General_std_004e77d8,
                                   (int)*(short *)&DAT_004e77d0 + 0x76);
    if (Surface_Lock(**(void ***)(bm + 0x78)) == 0)
        (*g_pSvcMain->pAssertFail)(s_Unable_to_lock_VBuffer_memory__004e76b4, s_C__grimjedi_Libs_Std_General_std_004e77d8,
                                   (int)*(short *)&DAT_004e77d0 + 0x7c);

    surf = **(byte ***)(bm + 0x78);
    pitch = *(uint *)(surf + 0x18);
    line = *(byte **)(surf + 0x5c);
    for (row = 0; row < (int)FRW(0xce); row++, line += pitch) {
        for (j = 0; j < n; j++) {
            if (fr[j < FR_N ? j : FR_N] == 0) {
                /* uncompressed */
                for (x = 0, p = line + 2; x < (int)FRW(0xcc); x++, p += 3) {
                    if (idxR == j) rd(fp, p - 2, szR);
                    if (idxG == j) rd(fp, p - 1, szG);
                    if (idxB == j) rd(fp, p, szB);
                    if (idxA == j) rd(fp, alpha, szA);
                }
                continue;
            }
            /* mixed RLE */
            x = 0;
            if (FRW(0xcc) == 0)
                continue;
            do {
                rd(fp, &cnt11, 1);
                if (cnt11 < 0x80) {
                    byte c;
                    p = line + x * 3 + 2;
                    do {
                        if (idxR == j) rd(fp, p - 2, szR);
                        if (idxG == j) rd(fp, p - 1, szG);
                        if (idxB == j) rd(fp, p, szB);
                        if (idxA == j) rd(fp, alpha, szA);
                        x++;
                        p += 3;
                        c = cnt11--;
                    } while (c != 0);
                } else {
                    if (cnt11 == 0x80) {
                        rd(fp, cnt14, 2);
                        cnt = ((uint)cnt14[0] << 8) | cnt14[1];
                    } else {
                        cnt = (uint)cnt11 - 0x7f;
                    }
                    if (idxR == j) rd(fp, &colR, szR);
                    if (idxG == j) rd(fp, &colG, szG);
                    if (idxB == j) rd(fp, &colB, szB);
                    if (idxA == j) rd(fp, alpha, szA);
                    cnt &= 0xffff;
                    p = line + x * 3 + 2;
                    x += cnt;
                    for (; cnt != 0; cnt--, p += 3) {
                        if (idxR == j) p[-2] = colR;
                        if (idxG == j) p[-1] = colG;
                        if (idxB == j) p[0] = colB;
                    }
                    cnt14[0] = 0xff;                 /* the count slot ends as 0xffff */
                    cnt14[1] = 0xff;
                }
            } while (x < (int)FRW(0xcc));
        }
    }
    Surface_Unlock(**(void ***)(bm + 0x78));
    (*g_pSvcMain->pFclose)(fp);
    return 1;
}
#endif
