/* Differential test of the DirectInput / Direct3D functions of build/overrides_asm_o2.c against the original machine code:
 * Input_PollKeyboard, Input_PollMouse, Input_FlushJoystick, D3D_ExecuteBuffer, D3D_CreateViewport.  The COM objects are
 * recorder objects (fx_com); their effects fill the caller's buffers (device state, buffered events, counts) from a
 * seed that is the same for both runs, and capture the structures passed in (D3DEXECUTEDATA, D3DVIEWPORT).
 * Build: build/difftest/asm_s5/build.sh build/difftest/asm_s5/dx_test.c build/difftest/asm_s5/out/dx_test.exe \
 *   Input_PollKeyboard Input_PollMouse Input_FlushJoystick D3D_ExecuteBuffer D3D_CreateViewport */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fx.h"

extern void orig_Input_PollKeyboard(void), Input_PollKeyboard(void);
extern void orig_Input_PollMouse(void), Input_PollMouse(void);
extern void orig_Input_FlushJoystick(void), Input_FlushJoystick(void);
extern int orig_D3D_ExecuteBuffer(void), D3D_ExecuteBuffer(void);
extern int orig_D3D_CreateViewport(unsigned, unsigned), D3D_CreateViewport(unsigned, unsigned);

static unsigned R(unsigned n) { return (unsigned)(fx_rnd() % n); }

/* D3D_SetViewportRect is compiled C in std3d.o; record it instead */
static unsigned rect_seen[4];
void SetRectX(unsigned *r) __asm__("_D3D_SetViewportRect");
void SetRectX(unsigned *r) { memcpy(rect_seen, r, 16); }

static unsigned eff_seed, eff_cnt;
static unsigned cap[64];
static int ncap;
static unsigned er(void) { eff_seed = eff_seed * 1664525u + 1013904223u; return eff_seed >> 8; }
static int ret_state, ret_data, kb_mode;
static void *viewport;

/* object tags: 10 keyboard, 11 mouse, 12 execute buffer, 13 device, 14 direct3d, 15 viewport */
static int eff(int tag, unsigned *a)
{
    int obj = tag / 100, m = tag % 100;
    if ((obj == 10 || obj == 11) && m == 9) {           /* GetDeviceState(this, size, buf) */
        unsigned char *b = (unsigned char *)a[2];
        for (unsigned k = 0; k < a[1]; k++) b[k] = (er() % 3 == 0) ? (unsigned char)er() : ((er() & 1) ? 0x80 : 0);
        if (obj == 11) for (unsigned k = 0; k < 3; k++) ((int *)b)[k] = (int)(er() % 2001) - 1000;
        return ret_state;
    }
    if ((obj == 10 || obj == 11) && m == 10) {          /* GetDeviceData(this, size, data, &count, flags) */
        unsigned *cnt = (unsigned *)a[3], *d = (unsigned *)a[2];
        cap[ncap++] = *cnt;
        if (d) {
            unsigned n = kb_mode == 2 ? *cnt : er() % (*cnt + 1);
            for (unsigned k = 0; k < n; k++) {
                d[k * 4 + 0] = obj == 10 ? er() % 256 : (er() % 4 ? 0xc + er() % 4 : er() % 32);
                d[k * 4 + 1] = (er() & 1) ? 0x80 : (er() % 4 ? 0 : er());
                d[k * 4 + 2] = FXU32(0x805fbc) - 300 + er() % 600;
                d[k * 4 + 3] = er();
            }
            if (kb_mode != 2) *cnt = n;   /* mode 2: count left unchanged (failure) */
        } else
            *cnt = 0;
        return ret_data;
    }
    if (obj == 12 && m == 6) { memcpy(cap + ncap, (void *)a[1], 0x30); ncap += 12; return 0; }
    if (obj == 14 && m == 7) { *(void **)a[1] = viewport; cap[ncap++] = a[2]; return -12345678; }
    if (obj == 15 && m == 5) { extern long nvp_g; extern unsigned vp_g[11]; nvp_g++; memcpy(vp_g, (void *)a[1], 0x2c); memcpy(cap + ncap, (void *)a[1], 0x2c); ncap += 11; return -12345678; }
    return -12345678;
}

long nvp_g; unsigned vp_g[11];
static int nargs16[16] = {1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 5, 3, 3, 3, 3, 3};
static int nargs_eb[16] = {1, 1, 1, 3, 3, 1, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3};
static int nargs_d3d[16] = {1, 1, 1, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
static int nargs_dev[16] = {1, 1, 1, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2};

int main(int argc, char **argv)
{
    long n = argc > 1 ? atol(argv[1]) : 10000, i;
    void *kb = fx_com(10, 16, nargs16), *mouse = fx_com(11, 16, nargs16);
    void *eb = fx_com(12, 16, nargs_eb), *dev = fx_com(13, 16, nargs_dev), *d3d = fx_com(14, 16, nargs_d3d);
    int capsave[64], ncapsave;
    unsigned rectsave[4];
    viewport = fx_com(15, 16, nargs16);
    for (int o = 10; o <= 15; o++) for (int m = 0; m < 16; m++) fx_effect(o * 100 + m, eff);
    fx_ignmask(1009, 4); fx_ignmask(1010, 0xc); fx_ignmask(1109, 4); fx_ignmask(1110, 0xc);
    fx_ignmask(1206, 2); fx_ignmask(1507, 2); fx_ignmask(1505, 2); fx_ignmask(1407, 0);
    { extern unsigned char sect_rdata[] __asm__("_sect_rdata"); printf("rdata+0x1694 = %g\n", *(float *)(sect_rdata + 0x1694)); }
    static long nvp; static unsigned vplast[11];
    fx_region(FXDATA(0x804000), 0x805fe0 - 0x804000);
    fx_region(FXDATA(0x806600), 0x10);
    fx_region(FXDATA(0x806918), 8);
    for (i = 0; i < n; i++) {
        int which = i % 5, pass, ret[2];
        unsigned seed = (unsigned)fx_rnd();
        static unsigned char ibuf[64];
        unsigned w = R(4) ? R(2000) : (unsigned)fx_rnd(), h = R(4) ? R(2000) : (unsigned)fx_rnd();
        for (unsigned k = 0x804000; k < 0x805fe0; k += 4) FXU32(k) = R(3) ? R(2) * 0x80 : (unsigned)fx_rnd();
        FXU32(0x805fbc) = (unsigned)fx_rnd();
        for (unsigned k = 0x805f28; k < 0x805fa0; k += 4) if (R(2)) FXU32(k) = FXU32(0x805fbc) - R(400);
        for (unsigned k = 0x804018; k < 0x805c20; k += 4) if (R(2)) FXU32(k) = FXU32(0x805fbc) - R(400);
        FXU32(0x805fa0) = R(8) == 0;
        FXU32(0x805fc8) = R(50);
        FXU32(0x4dea40) = R(8) != 0;
        FXU32(0x805fb4) = R(10) ? (unsigned)(uintptr_t)kb : 0;
        FXU32(0x805fb0) = (unsigned)(uintptr_t)mouse;
        FXU32(0x806954) = (unsigned)(uintptr_t)eb;
        FXU32(0x8061e4) = (unsigned)(uintptr_t)dev;
        FXU32(0x806608) = (unsigned)(uintptr_t)d3d;
        FXU32(0x80660c) = (unsigned)(uintptr_t)viewport;
        FXU32(0x806918) = (unsigned)(uintptr_t)(ibuf + R(16));
        FXU32(0x80691c) = (unsigned)(uintptr_t)ibuf + R(8);
        FXU32(0x8063ec) = (unsigned)(uintptr_t)ibuf - R(1000);
        FXU32(0x80695c) = (unsigned)fx_rnd();
        ret_state = R(4) ? 0 : (R(2) ? 1 : (int)0x80004005);
        ret_data = R(3) == 0 ? 1 : (R(3) ? 0 : (int)0x8007001e);
        kb_mode = R(4) == 0 ? 2 : 0;
        for (int m = 0; m < 16; m++) { fx_ret(1200 + m, R(3) ? 0 : 1); fx_ret(1300 + m, R(3) ? 0 : 5); fx_ret(1400 + m, R(4) ? 0 : 7); fx_ret(1500 + m, R(4) ? 0 : 3); }
        fx_save();
        for (pass = 0; pass < 2; pass++) {
            eff_seed = seed; ncap = 0; memset(cap, 0, sizeof cap); memset(rect_seen, 0, 16); fx_reset();
            ret[pass] = 0;
            switch (which) {
            case 0: pass ? Input_PollKeyboard() : orig_Input_PollKeyboard(); break;
            case 1: pass ? Input_PollMouse() : orig_Input_PollMouse(); break;
            case 2: pass ? Input_FlushJoystick() : orig_Input_FlushJoystick(); break;
            case 3: ret[pass] = pass ? D3D_ExecuteBuffer() : orig_D3D_ExecuteBuffer(); break;
            case 4: ret[pass] = pass ? D3D_CreateViewport(w, h) : orig_D3D_CreateViewport(w, h); break;
            }
            if (pass == 0) {
                fx_snap_a(); fx_restore();
                memcpy(capsave, cap, sizeof cap); ncapsave = ncap; memcpy(rectsave, rect_seen, 16);
            }
        }
        if (ret[0] != ret[1]) fx_fail("ret", i);
        if (fx_cmp_a()) fx_fail("mem", i);
        if (fx_cmp_log()) fx_fail("log", i);
        if (ncap != ncapsave || memcmp(cap, capsave, sizeof cap)) fx_fail("captured struct", i);
        if (memcmp(rect_seen, rectsave, 16)) fx_fail("rect", i);
        fx_cases++;
    }
    printf("SetViewport calls %ld, last: %u %u %u %u %u %g %g %g %g\n", nvp_g, vp_g[0], vp_g[1], vp_g[2], vp_g[3], vp_g[4], ((float*)vp_g)[5], ((float*)vp_g)[6], ((float*)vp_g)[7], ((float*)vp_g)[8]);
    printf("dx_test: %ld cases, %ld differences\n", fx_cases, fx_fails);
    return fx_fails != 0;
}
