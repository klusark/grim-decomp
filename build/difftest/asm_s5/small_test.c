/* Differential test of the small functions of build/overrides_asm_o2.c against the original machine code:
 * FUN_004d5fd0 / FUN_004d5e50 (memset), FUN_004d5f70 (log ring vsprintf), Rle_Decode, FUN_004965b0 (callback),
 * stdGif_LzwInitEncoder / stdGif_LzwEncodePixel (whole encode runs with the compiled C stdGif_LzwWriteCode /
 * ClearTable / FinishEncode of the current build and a recorder fwrite).
 * Build: EXTRA_OBJ="build/obj/GRIMFANDANGO.EXE/rle.o build/obj/GRIMFANDANGO.EXE/stdgif.o" build/difftest/asm_s5/build.sh \
 *   build/difftest/asm_s5/small_test.c build/difftest/asm_s5/out/small_test.exe FUN_004d5fd0 FUN_004d5e50 FUN_004d5f70 \
 *   Rle_Decode FUN_004965b0 stdGif_LzwInitEncoder stdGif_LzwEncodePixel
 * Run: small_test.exe <cases> */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "fx.h"

extern void o_fill(void *, int, int) __asm__("@orig_FUN_004d5fd0@20");
extern void n_fill(void *, int, int) __asm__("@FUN_004d5fd0@20");
extern int orig_FUN_004d5e50(void *, int, int), FUN_004d5e50(void *, int, int);
extern int orig_FUN_004d5f70(const char *, ...), FUN_004d5f70(const char *, ...);
extern void orig_Rle_Decode(void *, void *, int), Rle_Decode(void *, void *, int);
extern int orig_FUN_004965b0(int, int, int, int, void *), FUN_004965b0(int, int, int, int, void *);
extern unsigned orig_stdGif_LzwInitEncoder(int, int), stdGif_LzwInitEncoder(int, int);
extern unsigned orig_stdGif_LzwEncodePixel(int, unsigned char), stdGif_LzwEncodePixel(int, unsigned char);
extern unsigned stdGif_LzwFinishEncode(int);

static unsigned R(unsigned n) { return (unsigned)(fx_rnd() % n); }

/* callees */
void Mem_DumpLogX(void) __asm__("_Mem_DumpLog");
void Mem_DumpLogX(void) {}
int my_vsprintf(char *d, const char *f, va_list ap) __asm__("_vsprintf");
int my_vsprintf(char *d, const char *f, va_list ap) { return _vsnprintf(d, 199, f, ap); }

static unsigned char buf_a[70000], buf_b[70000], buf_0[70000];

static void cmpbuf(const char *what, long i)
{
    if (memcmp(buf_a, buf_b, sizeof buf_a)) fx_fail(what, i);
}

static void *fwrite_thunk;
static int fwrite_fail_at, fwrite_calls;
static unsigned fwrite_hash;
static int fwrite_effect(int tag, unsigned *a)
{
    (void)tag;
    for (unsigned k = 0; k < a[2] && k < 4096; k++) fwrite_hash = fwrite_hash * 33 + ((unsigned char *)a[1])[k];
    if (++fwrite_calls == fwrite_fail_at) return 0;
    return (int)a[2];
}

int main(int argc, char **argv)
{
    long n = argc > 1 ? atol(argv[1]) : 10000, i;
    static void *svc[0x20];

    /* memset */
    for (i = 0; i < n; i++) {
        int cnt = R(4) == 0 ? (int)(R(4) * 20000 + R(9) - 4) : (int)R(65000);
        int off = R(16), val = (int)fx_rnd();
        int ra, rb;
        if (cnt < 0) cnt = 0;
        for (int k = 0; k < (int)sizeof buf_0; k++) buf_0[k] = (unsigned char)fx_rnd();
        memcpy(buf_a, buf_0, sizeof buf_0); memcpy(buf_b, buf_0, sizeof buf_0);
        if (i & 1) { o_fill(buf_a + off, val, cnt); n_fill(buf_b + off, val, cnt); ra = rb = 0; }
        else { ra = orig_FUN_004d5e50(buf_a + off, val, cnt); rb = FUN_004d5e50(buf_b + off, val, cnt); }
        if (ra != rb) fx_fail("memset ret", i);
        cmpbuf("memset", i);
        fx_cases++;
    }
    /* log ring */
    fx_region(FXDATA(0x8dcdc8), 0x8ddd70 - 0x8dcdc8);
    for (i = 0; i < n; i++) {
        int ra, rb, x = (int)fx_rnd(), y = (int)R(1000);
        FXU32(0x8ddd68) = R(5) == 0 ? R(30) : R(20);
        FXU32(0x8ddd6c) = R(5) == 0 ? (unsigned)fx_rnd() : R(22);
        fx_save();
        ra = orig_FUN_004d5f70("x=%d y=%08x s=%s", x, y, "abc");
        fx_snap_a(); fx_restore();
        rb = FUN_004d5f70("x=%d y=%08x s=%s", x, y, "abc");
        if (ra != rb) fx_fail("log ret", i);
        if (fx_cmp_a()) fx_fail("log mem", i);
        fx_cases++;
    }
    fx_region_reset();
    /* Rle_Decode */
    fx_region(FXDATA(0x8dcdb8), 0x10);
    for (i = 0; i < n; i++) {
        static unsigned char src[8192];
        int cnt = R(3000), off = R(8);
        for (int k = 0; k < (int)sizeof src; k++) src[k] = (unsigned char)(R(3) ? fx_rnd() : R(4));
        for (int k = 0; k < (int)sizeof buf_0; k++) buf_0[k] = (unsigned char)fx_rnd();
        memcpy(buf_a, buf_0, sizeof buf_0); memcpy(buf_b, buf_0, sizeof buf_0);
        for (int k = 0; k < 16; k++) *FXDATA(0x8dcdb8 + k) = (unsigned char)fx_rnd();
        fx_save();
        orig_Rle_Decode(buf_a + off, src, cnt);
        fx_snap_a(); fx_restore();
        Rle_Decode(buf_b + off, src, cnt);
        cmpbuf("rle", i);
        if (fx_cmp_a()) fx_fail("rle state", i);
        fx_cases++;
    }
    fx_region_reset();
    /* FUN_004965b0 */
    {
        void *cb = fx_thunk(1, 2, 0);
        for (i = 0; i < n; i++) {
            int a[5], ra, rb;
            for (int k = 0; k < 4; k++) a[k] = (int)fx_rnd();
            fx_reset();
            ra = orig_FUN_004965b0(a[0], a[1], a[2], a[3], cb);
            fx_snap_a(); fx_reset();
            rb = FUN_004965b0(a[0], a[1], a[2], a[3], cb);
            if (ra != rb) fx_fail("cb ret", i);
            if (fx_cmp_log()) fx_fail("cb log", i);
            fx_cases++;
        }
    }
    /* GIF LZW encoder */
    fwrite_thunk = fx_thunk(2, 3, 0);
    fx_effect(2, fwrite_effect);
    fx_ignmask(2, 2);
    svc[0x40 / 4] = fwrite_thunk;
    FXU32(0x905ac0) = (unsigned)(uintptr_t)svc;
    fx_region(FXDATA(0x80cb00), 0x815700 - 0x80cb00);
    for (i = 0; i < n / 10 + 1; i++) {
        int bits = 1 + R(8), npix = R(R(4) ? 3000 : 30000), file = (int)fx_rnd(), pass;
        unsigned seed = (unsigned)fx_rnd(), ret[2][64];
        int nret[2];
        int range = R(2) ? (1 << bits) : 1 + R(1 << bits);
        int fail_at = R(4) == 0 ? (int)R(200) : -1;
        for (unsigned k = 0x80cb00; k < 0x815700; k += 4) FXU32(k) = (unsigned)fx_rnd();
        if (R(2)) FXU32(0x812ecc) = 0;
        fx_save();
        for (pass = 0; pass < 2; pass++) {
            unsigned s = seed, r, acc = 0;
            int k;
            fx_reset(); fwrite_calls = 0; fwrite_hash = 0; fwrite_fail_at = fail_at; nret[pass] = 0;
            r = pass ? stdGif_LzwInitEncoder(file, bits) : orig_stdGif_LzwInitEncoder(file, bits);
            ret[pass][nret[pass]++] = r & 0xffff;
            for (k = 0; k < npix; k++) {
                s = s * 1103515245u + 12345u;
                unsigned char px = (unsigned char)((s >> 16) % range);
                if (((s >> 8) & 7) == 0) px = (unsigned char)(s >> 24);   /* out of range pixel now and then */
                r = pass ? stdGif_LzwEncodePixel(file, px) : orig_stdGif_LzwEncodePixel(file, px);
                acc = acc * 31 + (r & 0xffff);
            }
            ret[pass][nret[pass]++] = acc;
            ret[pass][nret[pass]++] = stdGif_LzwFinishEncode(file) & 0xffff;
            ret[pass][nret[pass]++] = fwrite_hash;
            if (pass == 0) { fx_snap_a(); fx_restore(); }
        }
        if (memcmp(ret[0], ret[1], sizeof(unsigned) * nret[0])) fx_fail("gif ret", i);
        if (fx_cmp_a()) fx_fail("gif mem", i);
        if (fx_cmp_log()) fx_fail("gif log", i);
        fx_cases++;
    }
    printf("small_test: %ld cases, %ld differences\n", fx_cases, fx_fails);
    return fx_fails != 0;
}
