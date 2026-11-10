#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static unsigned rs = 777;
static unsigned rnd(void) { rs = rs * 1664525u + 1013904223u; return rs >> 8; }
typedef int (*dsb_t)(unsigned*, int, unsigned, unsigned, unsigned, unsigned);
typedef void (*cvb_t)(unsigned char*, short*, unsigned char*, unsigned);
typedef void (*vdb_t)(unsigned short*, unsigned, unsigned*, unsigned*, int*);
typedef unsigned (*scmp_t)(unsigned char*, unsigned char*);
int main(void) { setvbuf(stdout, NULL, _IONBF, 0);
    HMODULE m[2] = { LoadLibraryA("imuse_a.dll"), LoadLibraryA("imuse_c.dll") };
    if (!m[0] || !m[1]) { printf("load fail\n"); return 1; }
    int bad;
    /* Im_DecodeSoundBlock */
    bad = 0;
    for (int it = 0; it < 30000; it++) {
        int mode = (int[]){3, 5, 7, 1, 4}[it % 5];
        unsigned rate = (unsigned[]){0x5622, 0x2b11, 0xac44, 8000, rnd()}[rnd() % 5], bits = (unsigned[]){8, 16, 8 + (rnd() & 63)}[rnd() % 3], ch = 1 + rnd() % 3, size = rnd() % 100000;
        unsigned char buf[2][400]; int r[2];
        for (int d = 0; d < 2; d++) { memset(buf[d], 0xAA, 400); dsb_t f = (dsb_t)GetProcAddress(m[d], "Im_DecodeSoundBlock"); r[d] = f((unsigned*)buf[d], mode, rate, bits, ch, size); }
        if (r[0] != r[1] || memcmp(buf[0], buf[1], 400)) { bad++; if (bad < 3) printf("DecodeSoundBlock DIFF mode %d rate %u bits %u ch %u size %u: ret %d vs %d\n", mode, rate, bits, ch, size, r[0], r[1]); }
    }
    printf("Im_DecodeSoundBlock: %d differ\n", bad);
    /* Im_ConvertBlock */
    bad = 0;
    for (int it = 0; it < 4000; it++) {
        unsigned count = 2 * (1 + rnd() % 512) * (1 + rnd() % 2);
        unsigned char *src[2]; short *out[2]; unsigned char hdr[2][16];
        int nsrc = 40000; unsigned char *s0 = malloc(nsrc); for (int i = 0; i < nsrc; i++) s0[i] = rnd();
        if (rnd() % 2) { s0[0] = 0xff - rnd() % 0x59; s0[3] = rnd() % 0x59; } else s0[0] = rnd() % 0x59;
        for (int d = 0; d < 2; d++) {
            src[d] = malloc(nsrc); memcpy(src[d], s0, nsrc); out[d] = calloc(20000, 2); memset(hdr[d], 0x5A, 16);
            cvb_t f = (cvb_t)GetProcAddress(m[d], "Im_ConvertBlock"); f(hdr[d], out[d], src[d], count);
        }
        if (memcmp(out[0], out[1], 40000) || memcmp(hdr[0], hdr[1], 16)) { bad++; if (bad < 3) printf("ConvertBlock DIFF count %u first byte %02x\n", count, s0[0]); }
        for (int d = 0; d < 2; d++) { free(src[d]); free(out[d]); } free(s0);
    }
    printf("Im_ConvertBlock: %d differ\n", bad);
    /* AudioLib_DetectRawFormat: random data */
    bad = 0;
    for (int it = 0; it < 4000; it++) {
        int nsrc = 20000; unsigned char *s0 = malloc(nsrc + 64); for (int i = 0; i < nsrc + 64; i++) s0[i] = rnd();
        unsigned o[2][3]; unsigned char *sb[2];
        for (int d = 0; d < 2; d++) { sb[d] = malloc(nsrc + 64); memcpy(sb[d], s0, nsrc + 64); o[d][0] = o[d][1] = o[d][2] = 0xCAFEBABE; vdb_t f = (vdb_t)GetProcAddress(m[d], "AudioLib_DetectRawFormat"); f((unsigned short*)sb[d], 0x2000, &o[d][0], &o[d][1], (int*)&o[d][2]); }
        if (memcmp(o[0], o[1], 12) || memcmp(sb[0], sb[1], nsrc)) { bad++; if (bad < 3) printf("VimaDecodeBlock DIFF %x %x %x | %x %x %x\n", o[0][0], o[0][1], o[0][2], o[1][0], o[1][1], o[1][2]); }
        free(s0); free(sb[0]); free(sb[1]);
    }
    printf("AudioLib_DetectRawFormat: %d differ\n", bad);
    /* Im_StrCmpNoCase */
    bad = 0;
    for (int it = 0; it < 20000; it++) {
        unsigned char a[16], b[16]; int la = rnd() % 12, lb = rnd() % 12;
        for (int i = 0; i < 16; i++) { a[i] = 'A' + rnd() % 30; b[i] = (rnd() % 3 == 0) ? 'A' + rnd() % 30 : (a[i] ^ ((rnd() % 4 == 0) ? 0x20 : 0)); }
        if (rnd() % 2) memcpy(b, a, 16);
        a[la] = 0; b[lb] = (rnd() % 2) ? 0 : b[lb]; b[15] = 0;
        unsigned r[2]; for (int d = 0; d < 2; d++) { scmp_t f = (scmp_t)GetProcAddress(m[d], "Im_StrCmpNoCase"); r[d] = f(a, b); }
        if (r[0] != r[1]) { bad++; if (bad < 3) printf("StrCmpNoCase DIFF: %d %d\n", (int)r[0], (int)r[1]); }
    }
    printf("Im_StrCmpNoCase: %d differ\n", bad);
    return 0;
}
