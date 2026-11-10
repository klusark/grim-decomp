/* Differential test of stdPic_LoadEntry (build/overrides_big_stdpic_loadinto.c) against the original machine code
 * (orig_stdPic_LoadEntry, sliced from src/GRIMFANDANGO.EXE/asm_funcs.s together with its _ftol).
 * Build and run: build/difftest/big_stdpic_loadinto/run.sh [cases]
 *
 * Each case builds an in-memory .pic file (valid Softimage PIC images of random size / channel packets / compression,
 * damaged copies of them, random tails, wrong headers, more than 4 and up to 62 packets) and runs both versions on the same
 * start state.  The services (fopen / fread / fclose / alloc / assert) and stdDisplay_VBufferNew / Lock / Unlock,
 * stdFileFromPath and strncpy are fakes that log every call (arguments, return values; pointers into the pixel buffer as
 * offsets, other buffers by class) into a hash.  Compared: return value, call log (count + hash), the 0x7c byte bitmap
 * record plus 0x40 bytes after it, the 4 byte surface block, the stdDisplay_VBufferNew description (all 19 dwords) and the whole
 * reachable pixel buffer.  Before each call 16 KB of stack below the caller are zeroed, so the bytes the original never
 * initialises are 0, as in the C. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

extern unsigned char sect_data[] __asm__("_sect_data");
#define DATA(va) (sect_data + ((va) - 0x4dd000))

extern int orig_stdPic_LoadEntry(char *, void *, int, int);
extern int stdPic_LoadEntry(char *, void *, int, int);

static uint64_t seed = 0x1234567;
static uint32_t rnd(void) { seed ^= seed << 13; seed ^= seed >> 7; seed ^= seed << 17; return (uint32_t)(seed >> 11); }
static uint32_t R(uint32_t n) { return n ? rnd() % n : 0; }

/* ---------------- the file ---------------- */
static unsigned char file[1 << 21];
static int flen, fpos, fread_fail_at, fread_calls, fopen_fail, lock_fail;

/* ---------------- the log ---------------- */
static uint32_t lh, ln;
static void L(uint32_t v) { lh = (lh ^ v) * 16777619u + 0x9e3779b9u; }
static void LOG(int tag, uint32_t a, uint32_t b, uint32_t c, uint32_t r) { L(tag); L(a); L(b); L(c); L(r); ln++; }
static void LOGS(const char *s) { while (*s) L((unsigned char)*s++); L(0); }

#define PIXSZ (8 << 20)
static unsigned char pix[PIXSZ], pix0[PIXSZ];
static unsigned char surfrec[0xd8];
static uint32_t pixoff;
static uint32_t block4[2];
static unsigned char bm[0x7c + 0x40];
static uint32_t desc[19];

static uint32_t cls(void *p)  /* pointer class for the log */
{
    unsigned char *q = p;
    if (q >= pix && q < pix + PIXSZ) return 0x10000000u + (uint32_t)(q - pix);
    if (q >= bm && q < bm + sizeof bm) return 0x20000000u + (uint32_t)(q - bm);
    return 0x30000000u;          /* a local of the function */
}

static int s_fopen(char *path, char *mode) { LOGS(path); LOGS(mode); LOG(1, 0, 0, 0, fopen_fail); return fopen_fail ? 0 : 0x1234; }
static int s_fread(int fp, void *dst, unsigned n)
{
    int k = 0;
    fread_calls++;
    if (fread_calls != fread_fail_at) {
        k = (int)n;
        if (k > flen - fpos) k = flen - fpos;
        if (k < 0) k = 0;
        memcpy(dst, file + fpos, k);
        fpos += k;
    }
    LOG(2, fp, cls(dst), n, k);
    return k;
}
static int s_fclose(int fp) { LOG(3, fp, 0, 0, 0); return 0; }
static void *s_alloc(int n, char *f, int line) { LOGS(f); LOG(4, n, line, 0, 0); block4[0] = 0xdeadbeef; return block4; }
static int s_assert(char *m, char *f, int line) { LOGS(m); LOGS(f); LOG(5, line, 0, 0, 0); return 0; }
static int s_other(void) { LOG(99, 0, 0, 0, 0); return 0; }

void *stdDisplay_VBufferNew(uint32_t *d, int a, int b, int c)
{
    for (int i = 0; i < 19; i++) { desc[i] = d[i]; L(d[i]); }
    LOG(6, a, b, c, 0);
    return surfrec;
}
int stdDisplay_VBufferLock(void *s) { LOG(7, s == surfrec, 0, 0, !lock_fail); return !lock_fail; }
int stdDisplay_VBufferUnlock(void *s) { LOG(8, s == surfrec, 0, 0, 0); return 0; }
char *stdFileFromPath(char *p)
{
    char *r = p;
    for (; *p; p++) if (*p == '\\' || *p == '/' || *p == ':') r = p + 1;
    LOG(9, 0, 0, 0, 0);
    return r;
}
char *strncpy(char *d, const char *s, size_t n)
{
    size_t i;
    LOG(10, cls(d), n, 0, 0);
    for (i = 0; i < n && s[i]; i++) d[i] = s[i];
    for (; i < n; i++) d[i] = 0;
    return d;
}

/* ---------------- run one version ---------------- */
typedef int (*Fn)(char *, void *, int, int);
struct Res { int ret; uint32_t lh, ln; unsigned char bm[sizeof bm]; uint32_t b4[2]; uint32_t desc[19]; };
static uint32_t reach;

__attribute__((noinline)) static void zap(void) { volatile unsigned char b[16384]; for (int i = 0; i < (int)sizeof b; i++) b[i] = 0; }
__attribute__((noinline)) static int call(Fn f, char *path, int a, int b) { zap(); return f(path, bm, a, b); }

static unsigned char bm0[sizeof bm];
static void run(Fn f, char *path, int a, int b, struct Res *r)
{
    lh = 0x811c9dc5; ln = 0; fpos = 0; fread_calls = 0;
    memcpy(bm, bm0, sizeof bm);
    memset(desc, 0xcc, sizeof desc);
    block4[0] = block4[1] = 0x55555555;
    memcpy(pix, pix0, reach);
    r->ret = call(f, path, a, b);
    r->lh = lh; r->ln = ln;
    memcpy(r->bm, bm, sizeof bm);
    memcpy(r->b4, block4, sizeof block4);
    memcpy(r->desc, desc, sizeof desc);
}

/* ---------------- file generators ---------------- */
static unsigned char *wp;
static void put8(int v) { if (wp < file + sizeof file) *wp++ = (unsigned char)v; }
static void put16(int v) { put8(v >> 8); put8(v); }
static void put32(uint32_t v) { put16(v >> 16); put16(v & 0xffff); }
static void putf(float f) { uint32_t u; memcpy(&u, &f, 4); put32(u); }

static int npk, pk_type[80], pk_chan[80];
static void pixel(int chans) { for (int m = 0x80; m >= 0x10; m >>= 1) if (chans & m) put8(R(4) ? R(256) : R(3)); }

static void gen_valid(int w, int h, int overrun)
{
    wp = file;
    put32(0x5380f634);
    { float vs[] = {3.71f, 1.0f, 0.0f, -2.5f, 1e20f, 123456.7f}; putf(vs[R(6)]); }
    for (int i = 0; i < 80; i++) put8(R(3) ? 0 : 'a' + R(26));
    put32(0x50494354);
    put16(w); put16(h);
    { float rs[] = {1.0f, 1.3333f, 0.0f, 3e9f}; putf(rs[R(4)]); }
    put16(R(4)); put16(R(3) ? 0 : R(65536));
    for (int i = 0; i < npk; i++) {
        put8(i + 1 < npk); put8(8); put8(pk_type[i]); put8(pk_chan[i]);
    }
    for (int y = 0; y < h; y++)
        for (int i = 0; i < npk; i++) {
            if (pk_type[i] == 0) { for (int x = 0; x < w; x++) pixel(pk_chan[i]); continue; }
            for (int x = 0; x < w;) {
                int left = w - x, k, m = R(4);
                if (m == 0) {                         /* literal */
                    k = 1 + R(left < 128 ? left : 128);
                    if (overrun && R(8) == 0) k = 1 + R(128);
                    put8(k - 1);
                    for (int q = 0; q < k; q++) pixel(pk_chan[i]);
                } else if (m == 1 || m == 2) {        /* short repeat */
                    k = 2 + R(left < 127 ? left : 127);
                    if (overrun && R(8) == 0) k = 2 + R(127);
                    put8(k + 0x7f);
                    pixel(pk_chan[i]);
                } else {                              /* long repeat */
                    k = 1 + R(left);
                    if (overrun && R(6) == 0) k = R(4) ? R(300) : R(65536);
                    put8(0x80); put16(k);
                    pixel(pk_chan[i]);
                }
                x += k;
            }
        }
    if (R(4) == 0) for (int i = R(64); i > 0; i--) put8(R(256));
    flen = (int)(wp - file);
}

static int chans_of(void)
{
    static const int c[] = {0xe0, 0xf0, 0x80, 0x40, 0x20, 0x10, 0xc0, 0x60, 0xa0, 0x30};
    return R(5) ? c[R(10)] : (int)R(256);
}

/* simulate the packet loop: number of packets the original would store (0 when it stops before) */
static int packets_in_file(void)
{
    int n = 0, o = 0x68;
    if (flen < 0x68) return 0;
    for (;;) {
        if (o + 4 > flen) return n;
        n++;
        if (file[o + 1] != 8) return n;
        if (file[o] == 0) return n;
        o += 4;
    }
}

int main(int argc, char **argv)
{
    long n = argc > 1 ? atol(argv[1]) : 20000, i, fails = 0, ok1 = 0, skipped = 0;
    static void *svc[0x1c];
    static long kinds[8];
    for (i = 0; i < 0x1c; i++) svc[i] = (void *)s_other;
    svc[0x18 / 4] = (void *)s_assert; svc[0x20 / 4] = (void *)s_alloc;
    svc[0x30 / 4] = (void *)s_fopen; svc[0x34 / 4] = (void *)s_fclose; svc[0x38 / 4] = (void *)s_fread;
    *(void **)DATA(0x905ac0) = svc;
    for (i = 0; i < PIXSZ; i++) pix0[i] = (unsigned char)rnd();

    for (i = 0; i < n; i++) {
        int kind = R(8), w, h, pitch;
        char path[200];
        int va = R(3) ? 0 : (int)rnd(), vb = R(3) ? 0 : (int)rnd();
        struct Res a, b;

        /* image */
        w = R(5) ? R(40) : R(300);
        h = R(5) ? R(30) : R(80);
        if (R(20) == 0) w = 0;
        if (R(20) == 0) h = 0;
        npk = 1 + (R(4) ? R(3) : R(8));
        if (kind == 6) npk = 5 + R(58);                  /* > 4 packets: types over the frame */
        for (int k = 0; k < npk; k++) { pk_type[k] = R(3) == 0 ? 0 : (R(4) ? 2 : (int)R(256)); pk_chan[k] = chans_of(); }
        if (kind == 6) { w = R(8); h = R(4); }
        gen_valid(w, h, kind == 2);
        switch (kind) {
        case 3: /* damaged bytes */
            for (int k = 1 + R(8); k > 0; k--) if (flen) file[R(flen)] ^= 1 << R(8);
            break;
        case 4: /* truncated */
            flen = R(flen + 1);
            break;
        case 5: /* random tail after the packets */
            for (int o = 0x68 + 4 * npk; o < flen; o++) file[o] = (unsigned char)rnd();
            break;
        case 7: /* random header fields */
            if (R(2)) { uint32_t *m = (uint32_t *)file; *m ^= 1u << R(32); }
            if (R(2)) file[0x58 + R(4)] ^= 1 << R(8);
            if (R(2)) file[0x68 + 4 * R(npk) + R(4)] = R(256);
            break;
        }
        kinds[kind]++;
        /* stay inside what the original survives: at most 62 packets, a bounded amount of work */
        {
            int np = packets_in_file();
            uint32_t W = flen >= 0x60 ? (file[0x5c] << 8 | file[0x5d]) : 0, H = flen >= 0x60 ? (file[0x5e] << 8 | file[0x5f]) : 0;
            if (np > 62 || (double)W * H * (np ? np : 1) > 400000) { skipped++; continue; }
            if (np >= 28) { W = file[0x68 + 4 * 27 + 2]; H = 0; }
            if (W > 4000) { skipped++; continue; }
            pitch = (int)W * 3;
            switch (R(4)) { case 0: pitch += R(16); break; case 1: pitch = R(pitch + 1); break; }
            *(uint32_t *)(surfrec + 0x18) = pitch;
            pixoff = R(64);
            *(void **)(surfrec + 0x5c) = pix + pixoff;
            reach = pixoff + (H + 1) * (uint32_t)pitch + (W + 65536 + 256) * 3 + 64;
            if (reach > PIXSZ) reach = PIXSZ;
        }
        fopen_fail = R(40) == 0;
        lock_fail = R(10) == 0;
        fread_fail_at = R(6) == 0 ? 1 + R(40) : -1;
        {
            int pl = R(4) ? 3 + R(20) : 25 + R(60);
            strcpy(path, R(2) ? "C:\\grim\\data\\" : "textures/");
            for (int k = 0; k < pl; k++) path[strlen(path) + 1] = 0, path[strlen(path)] = 'a' + R(26);
            strcat(path, ".pic");
        }
        for (int k = 0; k < (int)sizeof bm0; k++) bm0[k] = (unsigned char)rnd();

        run(orig_stdPic_LoadEntry, path, va, vb, &a);
        static unsigned char pa[PIXSZ];
        memcpy(pa, pix, reach);
        run(stdPic_LoadEntry, path, va, vb, &b);
        int bad = 0;
        if (a.ret != b.ret) bad |= 1;
        if (a.lh != b.lh || a.ln != b.ln) bad |= 2;
        if (memcmp(a.bm, b.bm, sizeof a.bm)) bad |= 4;
        if (memcmp(a.b4, b.b4, sizeof a.b4)) bad |= 8;
        if (memcmp(a.desc, b.desc, sizeof a.desc)) bad |= 16;
        if (memcmp(pa, pix, reach)) bad |= 32;
        if (a.ret == 1) ok1++;
        if (bad) {
            if (fails < 20) printf("case %ld kind %d: differences %#x (ret %d/%d, log %u/%u calls)\n", i, kind, bad, a.ret, b.ret, a.ln, b.ln);
            fails++;
        }
    }
    printf("stdPic_LoadEntry: %ld cases (%ld loaded, %ld skipped), %ld with differences; kinds", n, ok1, skipped, fails);
    for (i = 0; i < 8; i++) printf(" %ld", kinds[i]);
    printf("\n");
    return fails != 0;
}
