/* Differential test of sputLua_Startup (build/overrides_asm_o2.c) against the original machine code (with the build's
 * asm patches).  Every callee is a recorder (LUA.DLL imports through their __imp__ slots for the original and their
 * plain names for the C), the exported variables lua_assume_binary / lua_savehook / lua_restorehook are test variables.
 * Build: build/difftest/asm_s5/build.sh build/difftest/asm_s5/lua_test.c build/difftest/asm_s5/out/lua_test.exe sputLua_Startup */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fx.h"

extern int orig_sputLua_Startup(void), sputLua_Startup(void);
static unsigned R(unsigned n) { return (unsigned)(fx_rnd() % n); }
static void *th[64];

#define REC(tag, name, n)                                                                                          \
    int name##_X(int a, int b, int c, int d) __asm__("_" #name);                                                     \
    int name##_X(int a, int b, int c, int d) { return ((int (*)(int, int, int, int))th[tag])(a, b, c, d); }          \
    void *name##_imp __asm__("__imp__" #name) = name##_X;
REC(1, lua_iolibopen, 0)
REC(2, lua_strlibopen, 0)
REC(3, lua_mathlibopen, 0)
REC(4, lua_recognizelib, 2)
REC(5, lua_getglobal, 1)
REC(6, lua_pushobject, 1)
REC(7, lua_ref, 1)
REC(8, lua_pushCclosure, 2)
REC(9, lua_setglobal, 1)
REC(10, lua_pushnumber, 1)
REC(11, lua_setfallback, 2)
REC(12, wuRegistry_GetStr, 4)
REC(13, sputLua_RegisterFunctions, 2)
REC(14, Lua_CreateSystemTable, 0)
REC(15, sputControl_AddCallback, 1)
REC(16, GRIM_RegisterModApiLib, 0)
REC(17, GRIM_RegisterModApi, 0)
REC(18, _stricmp, 2)
int v_binary, v_save, v_restore;
int *assume_imp __asm__("__imp__lua_assume_binary") = &v_binary;
int *save_imp __asm__("__imp__lua_savehook") = &v_save;
int *restore_imp __asm__("__imp__lua_restorehook") = &v_restore;
int *lua_assume_binary_exref = &v_binary, *lua_savehook_exref = &v_save, *lua_restorehook_exref = &v_restore;

static int reg_mode;
static int eff(int tag, unsigned *a)
{
    if (tag == 12) {   /* wuRegistry_GetStr(name, buf, size, default) */
        const char *s = reg_mode == 0 ? (const char *)FXDATA(0x4ec554) : reg_mode == 1 ? "TRUE" : (const char *)a[3];
        strncpy((char *)a[1], s, a[2] - 1); ((char *)a[1])[a[2] - 1] = 0;
        return 1;
    }
    if (tag == 18) return lstrcmpiA((const char *)a[0], (const char *)a[1]) != 0;
    return -12345678;
}

int main(int argc, char **argv)
{
    long n = argc > 1 ? atol(argv[1]) : 1000, i;
    int nargs[19] = {0, 0, 0, 0, 2, 1, 1, 1, 2, 1, 1, 2, 4, 2, 0, 1, 0, 0, 2};
    for (int t = 1; t < 20; t++) { th[t] = fx_thunk(t, t < 19 ? nargs[t] : 0, 0); fx_effect(t, eff); }
    fx_ignmask(12, 2); fx_strmask(12, 9); fx_ignmask(18, 1); fx_strmask(18, 2);
    fx_strmask(5, 1); fx_strmask(9, 1); fx_strmask(11, 1);
    printf("strings: %s %s %s\n", (char *)FXDATA(0x4ec55c), (char *)FXDATA(0x4ec554), (char *)FXDATA(0x4ec54c));
    fx_region(FXDATA(0x8cab40), 0x50);
    fx_region(&v_binary, 4); fx_region(&v_save, 4); fx_region(&v_restore, 4);
    for (i = 0; i < n; i++) {
        int ret[2];
        FXU32(0x8cab80) = R(4) == 0;
        FXU32(0x8cab58) = (unsigned)(uintptr_t)th[19];
        reg_mode = R(3);
        for (int t = 1; t < 18; t++) fx_ret(t, (int)fx_rnd());
        v_binary = R(2); v_save = 0; v_restore = 0;
        fx_save();
        fx_reset();
        ret[0] = orig_sputLua_Startup();
        fx_snap_a(); fx_restore(); fx_reset();
        ret[1] = sputLua_Startup();
        if (ret[0] != ret[1]) fx_fail("ret", i);
        if (fx_cmp_a()) fx_fail("mem", i);
        if (fx_cmp_log()) fx_fail("log", i);
        if (i == 1) printf("log entries %d\n", fx_nlog);
        fx_cases++;
    }
    printf("lua_test: %ld cases, %ld differences\n", fx_cases, fx_fails);
    return fx_fails != 0;
}
