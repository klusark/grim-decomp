/* Readable C for functions of GRIMFANDANGO.EXE (0x401000-0x49ffff) whose raw Ghidra decompilation cannot be compiled as it
 * stands (lost arguments, float bits in integer slots, patched behaviour of the test hooks, ...).  Each function was
 * checked against the original instructions; tools/build_src.py puts the decompiled version of every function defined
 * here under `#if 0`, so the C text in src/ is only a comment for these.  Names, types and offsets are Ghidra's.
 *
 * Layout: one block per function, `==== <Name> (0x<addr>) ====`, with a short note on why it is written by hand.
 * Compiled by build/link.py (only for GRIMFANDANGO.EXE, together with overrides.c). */
#include "ghidra_types.h"

#ifdef GRIM_EXE
#include "globals.h"
#include "functions.h"

extern void GRIM_lua_cmd_poll(void);   /* overrides.c: the Lua test hook */

/* ==== sputLua_Update (0x0049c8f0) ====
 * Per frame: stores system.frameTime and system.movieTime in the Lua "system" table, collects garbage every 10 s and
 * runs the Lua tasks (lua_updatetasks).  Written by hand because the test hook (GRIM_LUA_FILE, see overrides.c) is
 * called from here: the assembled copy got the call through names/asm_patches.json. */
void sputLua_Update(void)
{
    uint frameMs;
    int sys;

    GRIM_lua_cmd_poll();                                /* test hook: run the Lua lines appended to GRIM_LUA_FILE */

    g_dwSputLua_Update_movieTimeMsec = (uint)SmushPlay_GetMovieTime();
    frameMs = sputTime_GetFrameTime();
    g_dwSputLua_Update_collectionTime = g_dwSputLua_Update_collectionTime + frameMs;
    if ((float)g_dwSputLua_Update_collectionTime > 10000.0f) {           /* every 10 seconds */
        lua_collectgarbage(0);
        g_dwSputLua_Update_collectionTime = 0;
    }
    lua_beginblock();
    sys = lua_getref(g_nLrSystemTable);             /* the "system" table */
    lua_pushobject(sys);
    lua_pushstring(s_frameTime_004ec41c);
    lua_pushnumber((float)frameMs);
    lua_settable();
    sys = lua_getref(g_nLrSystemTable);
    lua_pushobject(sys);
    lua_pushstring(s_movieTime_004ec410);
    lua_pushnumber((float)(int)g_dwSputLua_Update_movieTimeMsec);
    lua_settable();
    lua_endblock();
    lua_updatetasks(0);
}

/* ==== Math_Floor (0x0047c100) ====
 * floor(x) for a float.  The code loads the x87 control word DAT_00900526 (round down, set up by stdStartup),
 * executes FRNDINT and restores the default word; the decompiler does not see the FLDCW and printed a plain ROUND(),
 * so the C text rounded to nearest (Manny's initial heading came out 0.04 degrees off). */
float Math_Floor(float x)
{
    float t;
    /* |x| >= 2^23 (or NaN / infinity) has no fractional part: FRNDINT leaves it alone, and a C integer cast would not */
    if (!(x > -8388608.0f && x < 8388608.0f) || x == 0.0f)
        return x;
    t = (float)(int)x;                  /* truncate toward zero */
    return (t > x) ? t - 1.0f : t;      /* ... then down for negative non-integers */
}

extern int GRIM_SimTime(void);   /* overrides.c: GRIM_SIMTIME=<ms> test knob (fixed frame time), 0 = off */
extern void GRIM_SmushSimFrame(int ms);   /* overrides_mixer_drv.c: movies on game time */
extern void GRIM_ImuseSimFrame(int ms);   /* overrides.c: iMUSE on game time */

/* ==== Main_Service (0x004016a0) ====
 * One pass of the main loop: re-selects the display after a mode change, runs the engine for one frame (the frame time
 * in ms is the one-shot global g_fixedFrameMs, 0 = measure it from the wall clock), counts frames, updates the FPS
 * counter once a second, draws the optional FPS / profile overlays and presents.  Written by hand: Ghidra lost the
 * second argument of grimlib_UpdateManual / grimlib_MarkDirtyRect / sputRender_Dim and the second Win_RemoveMessageHook
 * argument is a function pointer; and the GRIM_SIMTIME hook (names/asm_patches.json used to patch the assembled copy)
 * is just a line here. */
void Main_Service(void)
{
    int rect[4] = { 0, 0, 0x50, 0x1e };          /* x, y, width, height of the overlay text box */
    int savedMode = g_dwGrimlib_mode;
    int y = 0x1e;
    int frameMs, now, frames, draw;
    uint *prof;

    if (g_nQuitApp != 0)
        return;

    if (UINT_004f5a50 != 0) {                    /* display change pending: reselect it and dim the back buffer */
        Display_Select(UINT_004dd340, UINT_004dd344, UINT_004dd348);
        g_dwGrimlib_mode = 2;
        ((void (*)(int, int))sputRender_Dim)(1, 2);
        UINT_004f5a50 = 0;
    }
    _g_dwDeadmanCounter = 300;
    g_dwGrimlib_mode = savedMode;

    frameMs = GRIM_SimTime();                    /* test hook: fixed frame time */
    if (frameMs > 0) {                           /* ... and the movies and iMUSE step by it (grimlaunch's frame stub) */
        GRIM_SmushSimFrame(frameMs);
        GRIM_ImuseSimFrame(frameMs);
    }
    if (frameMs == 0)
        frameMs = g_fixedFrameMs;
    /* Not in the original, which draws only while the application is active (WM_ACTIVATEAPP): fullscreen on DirectDraw,
     * whose surfaces are lost when another application takes the screen. A window (this build's default, the DIB
     * section device) draws whether or not it is the foreground one; the game runs on either way, and a window that
     * stopped drawing showed a frozen picture of a running game. Fullscreen keeps the original's rule. */
    draw = g_dwZg_App_bAppActive != 0 || g_bWindowedMode != 0;
    grimlib_UpdateManual(draw, frameMs);
    g_dwMain_Service_frameCount = g_dwMain_Service_frameCount + 1;
    g_fixedFrameMs = 0;

    now = timeGetTime();                         /* (the hook point of the frame limiter of grimdlg.dll) */
    _g_dwMain_Service_frameTime = now;
    if ((uint)(now - g_dwMain_Service_frameTime0) > 1000) {    /* once a second: frames per second */
        frames = g_dwMain_Service_frameCount - UINT_004f5a5c;
        UINT_004f5a5c = g_dwMain_Service_frameCount;
        g_flMain_Service_frameRate = ((float)frames * 1000.0) / (float)(uint)(now - g_dwMain_Service_frameTime0);
        g_dwMain_Service_frameTime0 = now;
    }
    if (_g_bDrawFrameRate != 0) {
        sprintf(&g_bStd_genBuffer, s__02_3f_004dd680, (double)g_flMain_Service_frameRate);
        stdDisplay_TextOut(&g_bStd_genBuffer, 4, 4);
        grimlib_MarkDirtyRect(rect, 0);
    }
    if (g_nDrawPerfData != 0) {                   /* one line per profiled section (PerfBegin/End) */
        prof = &g_dwGrimlib_PerfData;
        do {
            sprintf(&g_bStd_genBuffer, s__s__02_3f_004dd674, prof - 10, *prof);
            stdDisplay_TextOut(&g_bStd_genBuffer, 4, y);
            rect[0] = 4;
            rect[1] = y;
            rect[2] = 0xbe;
            rect[3] = 0x14;
            grimlib_MarkDirtyRect(rect, 0);
            prof[0] = 0;
            prof[1] = 0;
            y += 0x14;
            prof += 0xc;
        } while (y < 0x122);
    }
    if (draw)
        grimlib_Display();
    if (g_nQuitApp != 0) {                  /* quit requested during the frame: tear the window down */
        Win_RemoveMessageHook(Win_WndProc);
        Win_RemoveMessageHook(Win_IsSysCommandBlocked);
        DestroyWindow(Win_GetMainHwnd());
    }
}

/* ==== rdVector_Normalize3 (0x00446920) ====
 * out = v / |v|, or a plain copy of v when |v| is zero (or NaN).  Ghidra shows a void function, but the original leaves
 * the length |v| unrounded in ST0 and WalkPlane_DistToEdge (assembled) reads it from there, so
 * the C pushes the length back on the x87 stack before it returns.  The original keeps the sum of squares, the length
 * and the quotients in extended precision and rounds to float only on the stores; the walk code is sensitive to that last
 * bit, so the C uses long double and the same order of additions (x^2 + (y^2 + z^2)). */
void rdVector_Normalize3(float *out, float *v)
{
    long double x = v[0], y = v[1], z = v[2];
    long double len = x * x + (y * y + z * z);

    __asm__("fsqrt" : "+t"(len));
    if (len == 0.0L || len != len) {                    /* FCOM + "C3 set" is true for equal and for unordered */
        out[0] = v[0];
        out[1] = v[1];
        out[2] = v[2];
    } else {
        out[0] = (float)(x / len);
        out[1] = (float)(y / len);
        out[2] = (float)(z / len);
    }
    __asm__ volatile("fldt %0" : : "m"(len));           /* the hidden return value: ST0 = |v| */
}

/* ==== stdMath_NormalizeAngle (0x0047bc20) ====
 * Angle in degrees brought into [0, 360).  By hand because of the test at the end: the original stores the result in a
 * float local and compares *that* with 360.0 (a value that rounds to 360.0f is turned into 0).  Compiled from Ghidra's
 * text, gcc -O2 compares the 80-bit register value instead, 360 comes through unchanged for angles just below a
 * multiple of 360 and the walker was "held up" on stairs.  The volatile store is the rounding to float.
 * A NaN input takes the negative branch (the x87 compare is unordered), as in the original. */
float stdMath_NormalizeAngle(float degrees)
{
    volatile float result;
    float t;

    if (0.0f <= degrees) {
        if (degrees < 360.0f)
            return degrees;
        result = degrees - Math_Floor(degrees / 360.0f) * 360.0f;
    } else {
        t = -degrees;
        if (360.0f <= t)
            t = t - Math_Floor(t / 360.0f) * 360.0f;
        result = 360.0f - t;
    }
    if (result == 360.0f)
        result = 0.0f;
    return result;
}

/* ==== sputLua_GetShrinkPosition (0x00498ea0) ====
 * GetShrinkPos(x, y, z, amount) returns the point of the walk sectors, shrunk by `amount` metres, nearest to (x, y, z).
 * By hand because Ghidra splits the position into a float[2] and a separate z: the z never reaches the frame that
 * WalkPlane_PlaneClosest / WalkPlane_ClosestPoint read and update, and the z pushed back is the input one.  (Test,
 * ShrinkBoxes and UnShrinkBoxes are generated since 2026-11-13.) */

/* GetShrinkPos(x, y, z, amount) -> x, y, z of the nearest point of the shrunken walk sectors (nil if there is none) */
void sputLua_GetShrinkPosition(void)
{
    int a1 = lua_lua2C(1), a2 = lua_lua2C(2), a3 = lua_lua2C(3), a4 = lua_lua2C(4);
    float pos[3];
    float amount;
    WalkPlane *sector;

    if (!lua_isnumber(a1) || !lua_isnumber(a2) || !lua_isnumber(a3) || !lua_isnumber(a4))
        return;
    pos[0] = lua_getnumber(a1);
    pos[1] = lua_getnumber(a2);
    pos[2] = lua_getnumber(a3);
    amount = lua_getnumber(a4);
    WalkPlane_BuildCache();
    ShrinkBoxes(amount);
    sector = WalkPlane_PlaneClosest(pos, 0x1000);
    if (sector != 0)
        WalkPlane_ClosestPoint(sector, (int)pos);
    sputLua_UnShrinkBoxes();
    if (sector == 0) {
        lua_pushnil();
        return;
    }
    lua_pushnumber(pos[0]);
    lua_pushnumber(pos[1]);
    lua_pushnumber(pos[2]);
}

/* ==== sputLua_EngineDisplay (0x00499280), sputLua_MakeCurrentSetupL (0x0049db70) ====
 * EngineDisplay(n): switch drawing of the 3D scene on/off.  MakeCurrentSetup(n): select camera setup n of the current set.
 * Both convert the Lua number with the CRT _ftol (the float stays in ST(0) between lua_getnumber and _ftol, which the
 * decompiler cannot follow): a C `(int)` cast does the same truncation. */
void sputLua_EngineDisplay(void)
{
    sputRender_SetPageFlip((int)lua_getnumber(lua_lua2C(1)));
}

void sputLua_MakeCurrentSetupL(void)
{
    int arg = lua_lua2C(1);
    if (lua_isnumber(arg))
        grimlib_MakeCurrentSetup((uint)(int)lua_getnumber(arg));
}

#endif /* GRIM_EXE */
