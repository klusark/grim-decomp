/* Differential test of the display set-up functions of build/overrides_asm_o2.c against the original machine code:
 * FUN_004761b0 (DirectDrawEnumerate callback), stdDisplay_TextOut, D3D_InitRenderState, DDraw_CreateSurfaces.
 * DirectDraw / Direct3D objects are recorder COM objects (fx_com) whose effects write the out parameters; the Win32
 * imports are recorders reached through their __imp__ slots (original) and their decorated names (C).
 * Build: build/difftest/asm_s5/build.sh build/difftest/asm_s5/display_test.c build/difftest/asm_s5/out/display_test.exe \
 *   FUN_004761b0 stdDisplay_TextOut D3D_InitRenderState DDraw_CreateSurfaces */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fx.h"

extern int __stdcall orig_enum(int, int, int, int) __asm__("_orig_FUN_004761b0@16");
extern int __stdcall new_enum(int, int, int, int) __asm__("_FUN_004761b0@16");
extern int orig_stdDisplay_TextOut(char *, int, int), stdDisplay_TextOut(char *, int, int);
extern int orig_D3D_InitRenderState(void), D3D_InitRenderState(void);
extern int orig_DDraw_CreateSurfaces(int, int *, unsigned char *), DDraw_CreateSurfaces(int, int *, unsigned char *);

static unsigned R(unsigned n) { return (unsigned)(fx_rnd() % n); }
enum { T_DDC = 1, T_HWND, T_SELOBJ, T_BKMODE, T_TXTCOL, T_TEXTOUT, T_GETDC, T_SYSPAL, T_RELDC, T_FILTER, T_MEMCPY, T_STRNCPY, T_LAST };
static void *th[T_LAST];

#define STD(tag, sym, name, n, ...)                                                                                     \
    int __stdcall name##_X(__VA_ARGS__) __asm__(sym);                                                                   \
    void *name##_imp __asm__("__imp_" sym) = name##_X;
#define FWD2 { return ((int (__stdcall *)(int, int))th[tag_])(a, b); }
int __stdcall DDC_X(int a, int b, int c) __asm__("_DirectDrawCreate@12");
int __stdcall DDC_X(int a, int b, int c) { return ((int (__stdcall *)(int, int, int))th[T_DDC])(a, b, c); }
void *DDC_imp __asm__("__imp__DirectDrawCreate@12") = DDC_X;
int __stdcall SelObj_X(int a, int b) __asm__("_SelectObject@8");
int __stdcall SelObj_X(int a, int b) { return ((int (__stdcall *)(int, int))th[T_SELOBJ])(a, b); }
void *SelObj_imp __asm__("__imp__SelectObject@8") = SelObj_X;
int __stdcall BkMode_X(int a, int b) __asm__("_SetBkMode@8");
int __stdcall BkMode_X(int a, int b) { return ((int (__stdcall *)(int, int))th[T_BKMODE])(a, b); }
void *BkMode_imp __asm__("__imp__SetBkMode@8") = BkMode_X;
int __stdcall TxtCol_X(int a, int b) __asm__("_SetTextColor@8");
int __stdcall TxtCol_X(int a, int b) { return ((int (__stdcall *)(int, int))th[T_TXTCOL])(a, b); }
void *TxtCol_imp __asm__("__imp__SetTextColor@8") = TxtCol_X;
int __stdcall TextOut_X(int a, int b, int c, int d, int e) __asm__("_TextOutA@20");
int __stdcall TextOut_X(int a, int b, int c, int d, int e) { return ((int (__stdcall *)(int, int, int, int, int))th[T_TEXTOUT])(a, b, c, d, e); }
void *TextOut_imp __asm__("__imp__TextOutA@20") = TextOut_X;
int __stdcall GetDC_X(int a) __asm__("_GetDC@4");
int __stdcall GetDC_X(int a) { return ((int (__stdcall *)(int))th[T_GETDC])(a); }
void *GetDC_imp __asm__("__imp__GetDC@4") = GetDC_X;
int __stdcall SysPal_X(int a, int b, int c, int d) __asm__("_GetSystemPaletteEntries@16");
int __stdcall SysPal_X(int a, int b, int c, int d) { return ((int (__stdcall *)(int, int, int, int))th[T_SYSPAL])(a, b, c, d); }
void *SysPal_imp __asm__("__imp__GetSystemPaletteEntries@16") = SysPal_X;
int __stdcall RelDC_X(int a, int b) __asm__("_ReleaseDC@8");
int __stdcall RelDC_X(int a, int b) { return ((int (__stdcall *)(int, int))th[T_RELDC])(a, b); }
void *RelDC_imp __asm__("__imp__ReleaseDC@8") = RelDC_X;
int Hwnd_X(void) __asm__("_Win_GetMainHwnd");
int Hwnd_X(void) { return ((int (*)(void))th[T_HWND])(); }
int Filter_X(int a) __asm__("_D3D_FilterBitsToEnum");
int Filter_X(int a) { return ((int (*)(int))th[T_FILTER])(a & 0xff); }
void MemCopy_X(void *d, void *s, unsigned n) __asm__("_Mem_Copy");
void MemCopy_X(void *d, void *s, unsigned n) { memmove(d, s, n); ((int (*)(void *, void *, unsigned))th[T_MEMCPY])(d, s, n); }
char *Strncpy_X(char *d, char *s, unsigned n) __asm__("_strncpy");
char *Strncpy_X(char *d, char *s, unsigned n) { unsigned k = 0; for (; k < n && s[k]; k++) d[k] = s[k]; for (; k < n; k++) d[k] = 0; ((int (*)(void *, void *, unsigned))th[T_STRNCPY])(d, s, n); return d; }

static unsigned eff_seed;
static unsigned er(void) { eff_seed = eff_seed * 1664525u + 1013904223u; return eff_seed >> 8; }
static unsigned cap[512];
static int ncap;
static void *dd_obj, *surf_obj, *surf2_obj, *pal_obj, *eb_obj;
static unsigned char ebuf[0x1000];
static int fail_method;      /* tag of the method that fails (returns 0x80004005) */

static void capture(void *p, unsigned n) { if (p && ncap + n / 4 < 512) { memcpy(cap + ncap, p, n); ncap += n / 4; } }

/* object tags: 20 DirectDraw, 21 primary surface, 22 back surface, 23 palette, 24 D3D device, 25 execute buffer */
static int eff(int tag, unsigned *a)
{
    int obj = tag / 100, m = tag % 100, fail = tag == fail_method ? (int)0x80004005 : 0;
    if (tag == T_DDC) { *(void **)a[1] = dd_obj; return fail; }
    if (tag == T_SYSPAL) { for (unsigned k = 0; k < 0x400; k++) ((unsigned char *)a[3])[k] = (unsigned char)er(); return 256; }
    if (tag == T_TEXTOUT) { capture((void *)a[3], a[4] < 64 ? a[4] : 64); return 1; }
    if (tag == T_MEMCPY || tag == T_STRNCPY) return -12345678;
    if (obj == 20 && m == 11) {   /* GetCaps */
        capture((void *)a[1], 0x16c); capture((void *)a[2], 0x16c);
        for (int k = 1; k < 0x5b; k++) ((unsigned *)a[1])[k] = er() & ((er() & 1) ? 1 : 0xffffffff);
        return fail;
    }
    if (obj == 20 && m == 6) {    /* CreateSurface(desc, &surf, outer) */
        capture((void *)a[1], 0x6c); *(void **)a[2] = surf_obj; return fail;
    }
    if ((obj == 21 || obj == 22) && m == 22) {   /* GetSurfaceDesc */
        unsigned *d = (unsigned *)a[1];
        capture(d, 0x6c);
        d[4] = 1 + er() % 5000; d[5] = er() % 3; d[0x68 / 4] = er();
        return fail;
    }
    if (obj == 21 && m == 12) { capture((void *)a[1], 4); *(void **)a[2] = surf2_obj; return fail; }   /* GetAttachedSurface */
    if (obj == 20 && m == 5) { capture((void *)a[2], 0x400); *(void **)a[3] = pal_obj; return fail; }   /* CreatePalette */
    if ((obj == 21 || obj == 22) && m == 17) { *(int *)a[1] = 0x5000 + obj; return fail; }   /* GetDC */
    if (obj == 24 && m == 6) {    /* CreateExecuteBuffer(desc, &eb, outer) */
        unsigned *d = (unsigned *)a[1];
        capture(d, 0x14); *(void **)a[2] = eb_obj; return fail;
    }
    if (obj == 25 && m == 4) { ((unsigned *)a[1])[4] = (unsigned)(uintptr_t)ebuf; return fail; }   /* Lock: lpData */
    if (obj == 25 && m == 6) { capture((void *)a[1], 0x30); return fail; }
    if (obj >= 20) return fail;
    return -12345678;
}

static int na_dd[24] = {1, 1, 1, 1, 4, 5, 4, 3, 5, 5, 1, 3, 2, 2, 2, 2, 2, 1, 2, 2, 3, 4, 2, 3};
static int na_surf[40] = {1, 1, 1, 2, 2, 6, 3, 6, 2, 2, 4, 2, 3, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 6, 2, 1, 2, 2, 2, 2, 3, 6, 2, 3, 2, 2, 2, 2};
static int na_dev[24] = {1, 1, 1, 4, 3, 3, 4, 2, 4, 2, 2, 4, 3, 3, 3, 3, 3, 3, 2, 1, 1, 3, 3, 3};
static int na_eb[16] = {1, 1, 1, 3, 2, 1, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2};

int main(int argc, char **argv)
{
    long n = argc > 1 ? atol(argv[1]) : 10000, i;
    int nargs[T_LAST] = {0, 3, 0, 2, 2, 2, 5, 1, 4, 2, 1, 3, 3};
    static unsigned capsave[512];
    int ncapsave;
    for (int t = 1; t < T_LAST; t++) { th[t] = fx_thunk(t, nargs[t], t >= T_DDC && t != T_HWND && t != T_FILTER && t != T_MEMCPY && t != T_STRNCPY); fx_effect(t, eff); }
    dd_obj = fx_com(20, 24, na_dd); surf_obj = fx_com(21, 40, na_surf); surf2_obj = fx_com(22, 40, na_surf);
    pal_obj = fx_com(23, 8, na_eb); { void *dev = fx_com(24, 24, na_dev); FXU32(0x8061e4) = (unsigned)(uintptr_t)dev; }
    eb_obj = fx_com(25, 16, na_eb);
    for (int o = 20; o <= 25; o++) for (int m = 0; m < 40; m++) fx_effect(o * 100 + m, eff);
    /* stack addresses are not logged */
    fx_ignmask(T_DDC, 2); fx_ignmask(T_TEXTOUT, 8); fx_ignmask(T_SYSPAL, 8); fx_ignmask(T_MEMCPY, 3); fx_ignmask(T_STRNCPY, 2);
    fx_ignmask(2011, 6); fx_ignmask(2005, 4); fx_ignmask(2117, 2); fx_ignmask(2217, 2); fx_ignmask(2406, 6);
    fx_ignmask(2504, 2); fx_ignmask(2506, 2);
    fx_region(FXDATA(0x803f80), 0x40);
    fx_region(FXDATA(0x806600), 0x10); fx_region(FXDATA(0x806920), 0x10);
    fx_region(FXDATA(0x901680), 0x0e0); fx_region(FXDATA(0x9055e0), 0x0e0);
    fx_region(FXDATA(0x902c60), 0x298 * 16);
    fx_region(ebuf, sizeof ebuf);
    for (i = 0; i < n; i++) {
        int which = i % 4, pass, ret[2];
        unsigned seed = (unsigned)fx_rnd();
        static int mode[21];
        static unsigned char palette[768], guid[16];
        static char desc[200], name[200], text[100];
        static unsigned char devrec[0x120];
        int a_guid = R(3) ? (int)(uintptr_t)guid : 0;
        int x = (int)R(640), y = (int)R(480), hwnd = (int)fx_rnd();
        for (int k = 0; k < 21; k++) mode[k] = (int)fx_rnd();
        mode[0] = R(2); mode[2] = 320 + R(1000); mode[3] = 200 + R(800); mode[7] = R(2); mode[8] = 8 << R(3);
        for (int k = 0; k < 768; k++) palette[k] = (unsigned char)fx_rnd();
        for (int k = 0; k < 16; k++) guid[k] = (unsigned char)fx_rnd();
        for (int k = 0; k < 199; k++) { desc[k] = (char)('a' + R(26)); name[k] = (char)('A' + R(26)); }
        desc[R(199)] = 0; name[R(199)] = 0; desc[199] = name[199] = 0;
        for (int k = 0; k < 99; k++) text[k] = (char)(' ' + R(90)); text[R(99)] = 0; text[99] = 0;
        for (unsigned k = 0x803f80; k < 0x803fc0; k += 4) FXU32(k) = (unsigned)fx_rnd();
        for (unsigned k = 0x901680; k < 0x901760; k += 4) FXU32(k) = (unsigned)fx_rnd();
        for (unsigned k = 0x9055e0; k < 0x9056c0; k += 4) FXU32(k) = (unsigned)fx_rnd();
        for (unsigned k = 0; k < sizeof ebuf; k++) ebuf[k] = (unsigned char)fx_rnd();
        FXU32(0x803f8c) = R(20);
        FXU32(0x803f9c) = R(2);
        FXU32(0x803fa4) = (unsigned)(uintptr_t)dd_obj;
        *(unsigned *)(devrec + 0x100) = R(5) ? R(2) : R(5);
        FXU32(0x803f90) = (unsigned)(uintptr_t)devrec;
        { static void *pp, *bp; pp = surf_obj; bp = surf2_obj; FXU32(0x803fa8) = (unsigned)(uintptr_t)&pp; FXU32(0x803fac) = (unsigned)(uintptr_t)&bp; }
        FXU32(0x806920) = (unsigned)fx_rnd();
        { static unsigned drv[8]; drv[5] = R(2); FXU32(0x80692c) = (unsigned)(uintptr_t)drv; }
        FXU32(0x900534) = R(256);
        FXU32(0x4dee60) = R(2);
        FXU32(0x80660c) = (unsigned)fx_rnd();
        fail_method = R(3) == 0 ? -1 : (int)(R(2) ? T_DDC : (20 + R(6)) * 100 + R(40));
        fx_ret(T_HWND, (int)fx_rnd()); fx_ret(T_SELOBJ, (int)fx_rnd()); fx_ret(T_FILTER, (int)R(5)); fx_ret(T_GETDC, (int)fx_rnd());
        fx_save();
        for (pass = 0; pass < 2; pass++) {
            eff_seed = seed; ncap = 0; memset(cap, 0, sizeof cap); fx_reset();
            switch (which) {
            case 0: ret[pass] = pass ? new_enum(a_guid, (int)(uintptr_t)desc, (int)(uintptr_t)name, 7) : orig_enum(a_guid, (int)(uintptr_t)desc, (int)(uintptr_t)name, 7); break;
            case 1: ret[pass] = pass ? stdDisplay_TextOut(text, x, y) : orig_stdDisplay_TextOut(text, x, y); break;
            case 2: ret[pass] = pass ? D3D_InitRenderState() : orig_D3D_InitRenderState(); break;
            case 3: ret[pass] = pass ? DDraw_CreateSurfaces(hwnd, mode, palette) : orig_DDraw_CreateSurfaces(hwnd, mode, palette); break;
            }
            if (pass == 0) { fx_snap_a(); fx_restore(); memcpy(capsave, cap, sizeof cap); ncapsave = ncap; }
        }
        if (ret[0] != ret[1]) fx_fail("ret", i);
        if (fx_cmp_a()) fx_fail("mem", i);
        if (fx_cmp_log()) fx_fail("log", i);
        if (ncap != ncapsave || memcmp(cap, capsave, sizeof cap)) fx_fail("captured", i);
        fx_cases++;
    }
    printf("display_test: %ld cases, %ld differences\n", fx_cases, fx_fails);
    return fx_fails != 0;
}
