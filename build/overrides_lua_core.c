/* LUA.DLL: the three Lua VM core functions that were still assembled (lua_updatetasks, luaD_protectedrun,
 * protectedparser), written from the original 1.01 machine code (2026-11-09; notes in docs/notes/lua_core.md).
 *
 * All three bracket a call with MSVC's setjmp: `_setjmp3(buf, 0)`, and lua_error (luaD_error) leaves through
 * `longjmp(*L->errorJmp, 1)`. Both come from the host msvcrt.dll (names/lib_replace.json), so the C below makes the
 * same two calls as the original. `_setjmp3` is declared returns_twice, and every local that is read after a longjmp
 * is volatile (msvcrt's longjmp restores EBX/ESI/EDI/EBP/ESP of the setjmp, not values that lived in registers).
 *
 * Offsets in the lua_State (the global L = g_pLuaState, Grim's Lua 3.1 with tasks): +0x00 the root of the C call
 * chain of this task (the "execution state" list linked through +0x0c), +0x08 call depth, +0x10 / +0x14 the "paused" /
 * "running elsewhere" flags of a task, +0x1c stack top, +0x20 stack base, +0x28 / +0x2c / +0x30 the C stack frame
 * (base, lua2C, num), +0x34 errorJmp, +0xc0 the task id passed to the task hook, +0xc4 the task's function. */
#ifdef GRIM_LUA
#include "ghidra_types.h"
#include "globals.h"
#define _setjmp3 _setjmp3__ghidra
#include "functions.h"
#undef _setjmp3

extern int __cdecl _setjmp3(void *buf, int count, ...) __attribute__((returns_twice));

#define LS(p) ((int *)(p))
#define GL LS(g_pLuaState)

/* OVERRIDES: lua_updatetasks */
/* The task scheduler: runs every task (lua_State linked by LState_next = next task) once.
 * First every task's C call chain is marked (ExecutionState_resetcounter) and its "paused" flag cleared.  Then, from the first task on,
 * each task that is neither paused (+0x10) nor marked (+0x14) runs under a setjmp: a new task (no root, +0x00 == 0)
 * calls its function (+0xc4) with the arguments on its stack, a resumed one continues its root call (root+0x10,
 * root+0x14).  A task whose call returns non-zero (yielded) gets +0x10 = 1 and stays; one that finished (0) or raised
 * an error (longjmp: luaD_deletestates unwinds its root, root cleared) is freed (LState_Destruct, luaM_free).  The task hook
 * (lua_taskhook) is told 0 (start), 2 (resume), 1 (yield), 4 (end) or 3 (error).  When a task is freed the scan goes
 * back to the start (the saved L) and continues with the first task that can run.  With param_1 != 0 the whole
 * round repeats while there is any task.  Returns 1 if a task is left, 0 if not.
 * Kept from the machine code: LState_next is __fastcall; the stack-size argument of luaD_openstack is the
 * arithmetic shift ((top - base) >> 3) - cbase; luaD_call gets the C base read BEFORE luaD_openstack, plus 1; the
 * assert (services+0x18, line 0x2fe) only fires for a yield without a root; the global L is re-read after every call. */
int __cdecl lua_updatetasks(int param_1)
{
    int *saved = GL;
    int *t, *c, *nx;
    volatile int hookarg;
    volatile int res;
    int buf[16];

    for (;;) {
        /* 1e23: mark every task's call chain, clear its paused flag */
        for (t = (int *)LState_next((int)g_pLuaState); t != 0; t = (int *)LState_next((int)t)) {
            for (c = (int *)t[0]; c != 0; c = (int *)c[3])
                ExecutionState_resetcounter((int)c);
            t[4] = 0;
        }
        /* 1e5b: the runnable tasks after the current one */
    restart:
        nx = (int *)LState_next((int)g_pLuaState);
        g_pLuaState = nx;
        if (nx != 0) {
            do {
                if (GL[4] != 0 || GL[5] != 0) {
                    nx = (int *)LState_next((int)g_pLuaState);           /* 2019 */
                } else {
                    hookarg = 4;
                    GL[0xd] = (int)buf;
                    if (_setjmp3(buf, 0) == 0) {
                        if (GL[0] == 0) {
                            int base = GL[10];
                            luaD_openstack(((GL[7] - GL[8]) >> 3) - base);
                            luaA_setnormalized((int *)(GL[8] + GL[10] * 8), GL + 0x31);
                            if (lua_taskhook != 0)
                                luaD_taskHook(GL[0x30], 0);
                            res = luaD_call((code *)(base + 1), (void *)0xff);
                        } else {
                            if (lua_taskhook != 0)
                                luaD_taskHook(GL[0x30], 2);
                            res = luaD_call((code *)((int *)GL[0])[4], (void *)((int *)GL[0])[5]);
                        }
                    } else {
                        hookarg = 3;
                        luaD_deletestates(GL[0]);
                        res = 0;
                        GL[0] = 0;
                    }
                    if (res != 0) {
                        if (GL[0] == 0)
                            ((void (__cdecl *)(char *, char *, int))*(int *)(g_dwLuaHS + 0x18))(
                                s_L__pExecutionState_100261dc, s_C__grimsrc_libs_lua_src_lapi_cpp_100260d4, 0x2fe);
                        if (lua_taskhook != 0)
                            luaD_taskHook(GL[0x30], 1);
                        GL[4] = 1;
                        nx = (int *)LState_next((int)g_pLuaState);       /* 201b */
                    } else {
                        int *dead;
                        if (lua_taskhook != 0)
                            luaD_taskHook(GL[0x30], hookarg);
                        nx = (int *)LState_next((int)g_pLuaState);
                        dead = GL;
                        if (dead != 0) {
                            LState_Destruct(dead);
                            luaM_free(dead);
                        }
                    }
                }
                g_pLuaState = nx;                                          /* 2020 */
            } while (nx != 0);
        }
        /* 2030: back at the start; if any later task can run, scan again from the saved L */
        g_pLuaState = saved;
        for (t = (int *)LState_next((int)saved); t != 0; t = (int *)LState_next((int)t)) {
            if (t[4] == 0 && t[5] == 0)
                goto restart;
        }
        /* 2053 */
        if (param_1 == 0 || LState_next((int)g_pLuaState) == 0)
            break;
    }
    return LState_next((int)g_pLuaState) != 0;
}

/* OVERRIDES: luaD_protectedrun */
/* Calls the function on the C stack (luaD_callinc(nResults)) under a setjmp.  On an error (longjmp) it restores the
 * C stack frame (+0x28..+0x30), sets top = base + cbase * 8 and unlinks and frees (ExecutionState_Delete) every entry of the
 * call chain (+0x00, linked through +0x0c) above the one at entry.  The previous errorJmp is put back and the call
 * depth (+0x08, incremented before the setjmp) decremented on both paths.  Returns 0, or 1 after an error. */
undefined4 __cdecl luaD_protectedrun(void *param_1)
{
    volatile int s0, s1, s2, oldjmp, oldroot;
    int status;
    int buf[16];

    s0 = GL[10];
    s1 = GL[11];
    s2 = GL[12];
    oldjmp = GL[0xd];
    oldroot = GL[0];
    GL[0xd] = (int)buf;
    GL[2] = GL[2] + 1;
    if (_setjmp3(buf, 0) == 0) {
        luaD_callinc(param_1);
        status = 0;
    } else {
        GL[10] = s0;
        GL[11] = s1;
        GL[12] = s2;
        GL[7] = GL[8] + GL[10] * 8;
        while (GL[0] != oldroot) {
            int e = GL[0];
            GL[0] = ((int *)e)[3];
            ExecutionState_Delete(e);
        }
        status = 1;
    }
    GL[0xd] = oldjmp;
    GL[2] = GL[2] - 1;
    return status;
}

/* OVERRIDES: protectedparser */
/* Parses (luaY_parser) or undumps (luaU_undump1, param_2 != 0) one chunk from the stream param_1 under a setjmp.
 * Returns 1 after an error, 2 when there was nothing to read (no function), else 0 with a closure of the new
 * function pushed (luaD_adjusttop(cbase + 1); stack[cbase] = {LUA_T_PROTO (-4), tf}; luaV_closure(0)). */
undefined4 __cdecl protectedparser(int *param_1, int param_2)
{
    volatile int oldjmp;
    int status;
    int tf;
    int buf[16];

    oldjmp = GL[0xd];
    GL[0xd] = (int)buf;
    if (_setjmp3(buf, 0) == 0) {
        if (param_2 != 0)
            tf = luaU_undump1(param_1);
        else
            tf = luaY_parser((int)param_1);
        status = 0;
    } else {
        tf = 0;
        status = 1;
    }
    GL[0xd] = oldjmp;
    if (status != 0)
        return 1;
    if (tf == 0)
        return 2;
    luaD_adjusttop(GL[10] + 1);
    *(int *)(GL[8] + GL[10] * 8) = -4;
    *(int *)(GL[8] + GL[10] * 8 + 4) = tf;
    luaV_closure(0);
    return 0;
}
#endif /* GRIM_LUA */
