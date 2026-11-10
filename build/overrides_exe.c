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
    frameMs = Timer_GetFrameMs();
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

/* ==== sputLua_SetCameraFOVL (0x0049f8d0) ====
 * SetCameraFOV(fov): stores the field of view in the camera setup (float at +0x1c) and in the rdCamera object the
 * setup points to (pointer at +0x28, float at +0x38).  By hand because Ghidra types g_pSputRender_Camera as float *, so the
 * pointer field at +0x28 came out as `(int)g_pSputRender_Camera[10]` (a float -> int conversion of the pointer bits).
 * The original has no `return` after the two lua_pushnil() calls (missing early-outs: it carries on and dereferences
 * a null setup); kept as it is. */
void sputLua_SetCameraFOVL(void)
{
    int arg;
    float *setup;

    if (g_pSputRender_Camera == (float *)0)
        lua_pushnil();
    arg = lua_lua2C(1);
    if (!lua_isnumber(arg))
        lua_pushnil();
    setup = g_pSputRender_Camera;
    setup[7] = lua_getnumber(arg);                                  /* fov */
    *(float *)(*(char **)(setup + 10) + 0x38) = setup[7];           /* rdCamera.fov */
}

/* ==== Math_Floor (0x0047c100) ====
 * floor(x) for a float.  The code loads the x87 control word DAT_00900526 (round down, set up by Services_SetCurrent),
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

/* ==== Main_Service (0x004016a0) ====
 * One pass of the main loop: re-selects the display after a mode change, runs the engine for one frame (the frame time
 * in ms is the one-shot global g_fixedFrameMs, 0 = measure it from the wall clock), counts frames, updates the FPS
 * counter once a second, draws the optional FPS / profile overlays and presents.  Written by hand: Ghidra lost the
 * second argument of Engine_UpdateFrame / Engine_InvalidateRect / sputRender_Dim and the second Win_RemoveMessageHook
 * argument is a function pointer; and the GRIM_SIMTIME hook (names/asm_patches.json used to patch the assembled copy)
 * is just a line here. */
void Main_Service(void)
{
    int rect[4] = { 0, 0, 0x50, 0x1e };          /* x, y, width, height of the overlay text box */
    int savedMode = g_dwGrimlib_mode;
    int y = 0x1e;
    int frameMs, now, frames;
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
    if (frameMs == 0)
        frameMs = g_fixedFrameMs;
    Engine_UpdateFrame(g_dwZg_App_bAppActive, frameMs);
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
        Display_DrawText(&g_bStd_genBuffer, 4, 4);
        Engine_InvalidateRect(rect, 0);
    }
    if (g_nDrawPerfData != 0) {                   /* one line per profiled section (Profile_Begin/End) */
        prof = &g_dwGrimlib_PerfData;
        do {
            sprintf(&g_bStd_genBuffer, s__s__02_3f_004dd674, prof - 10, *prof);
            Display_DrawText(&g_bStd_genBuffer, 4, y);
            rect[0] = 4;
            rect[1] = y;
            rect[2] = 0xbe;
            rect[3] = 0x14;
            Engine_InvalidateRect(rect, 0);
            prof[0] = 0;
            prof[1] = 0;
            y += 0x14;
            prof += 0xc;
        } while (y < 0x122);
    }
    if (g_dwZg_App_bAppActive != 0)
        Engine_PresentFrame();
    if (g_nQuitApp != 0) {                  /* quit requested during the frame: tear the window down */
        Win_RemoveMessageHook(Win_WndProc);
        Win_RemoveMessageHook(Win_IsSysCommandBlocked);
        DestroyWindow(Win_GetMainHwnd());
    }
}

/* ==== Vec3_NormalizeTo (0x00446920) ====
 * out = v / |v|, or a plain copy of v when |v| is zero (or NaN).  Ghidra shows a void function, but the original leaves
 * the length |v| unrounded in ST0 and Sector_EdgeDistance (assembled) reads it from there, so
 * the C pushes the length back on the x87 stack before it returns.  The original keeps the sum of squares, the length
 * and the quotients in extended precision and rounds to float only on the stores; the walk code is sensitive to that last
 * bit, so the C uses long double and the same order of additions (x^2 + (y^2 + z^2)). */
void Vec3_NormalizeTo(float *out, float *v)
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

/* ==== Math_NormalizeAngle360 (0x0047bc20) ====
 * Angle in degrees brought into [0, 360).  By hand because of the test at the end: the original stores the result in a
 * float local and compares *that* with 360.0 (a value that rounds to 360.0f is turned into 0).  Compiled from Ghidra's
 * text, gcc -O2 compares the 80-bit register value instead, 360 comes through unchanged for angles just below a
 * multiple of 360 and the walker was "held up" on stairs.  The volatile store is the rounding to float.
 * A NaN input takes the negative branch (the x87 compare is unordered), as in the original. */
float Math_NormalizeAngle360(float degrees)
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

/* ==== walk-box shrinking: sputLua_Test, sputLua_ShrinkBoxes, sputLua_UnShrinkBoxes, sputLua_GetShrinkPosition (0x00498e20-0x00498fe1) ====
 * ShrinkBoxes(amount) pulls the edges of the walk sectors in by `amount` metres (so a bigger actor does not clip the
 * walls), UnShrinkBoxes() restores them, GetShrinkPos(x, y, z, amount) returns the point of the shrunken sectors nearest
 * to (x, y, z).  By hand because Ghidra gave ShrinkBoxes (0x004a9d00, outside this range) a prototype
 * with 14 parameters; the code pushes just one float. */
extern void SectorList_ShrinkWalkSectors_amount(float amount) __asm__("_ShrinkBoxes");

/* TEST(): the developer test hook of the original, shrinks the boxes by 0.005 */
void sputLua_Test(void)
{
    SectorList_ShrinkWalkSectors_amount(0.005f);
}

/* UnShrinkBoxes(): undo the last shrink and forget the saved geometry */
void sputLua_UnShrinkBoxes(void)
{
    SectorList_RestoreAfterShrink();
    SectorList_FreeShrinkSave();
}

/* ShrinkBoxes(amount): unshrink, save the sectors, shrink by amount; nothing for a nil amount */
void sputLua_ShrinkBoxes(void)
{
    int amount = lua_lua2C(1);
    if (lua_isnil(amount) == 0) {
        sputLua_UnShrinkBoxes();
        SectorList_SaveForShrink();
        SectorList_ShrinkWalkSectors_amount(lua_getnumber(amount));
    }
}

/* GetShrinkPos(x, y, z, amount) -> x, y, z of the nearest point of the shrunken walk sectors (nil if there is none) */
void sputLua_GetShrinkPosition(void)
{
    int a1 = lua_lua2C(1), a2 = lua_lua2C(2), a3 = lua_lua2C(3), a4 = lua_lua2C(4);
    float pos[3];
    float amount;
    void *sector;

    if (!lua_isnumber(a1) || !lua_isnumber(a2) || !lua_isnumber(a3) || !lua_isnumber(a4))
        return;
    pos[0] = lua_getnumber(a1);
    pos[1] = lua_getnumber(a2);
    pos[2] = lua_getnumber(a3);
    amount = lua_getnumber(a4);
    SectorList_SaveForShrink();
    SectorList_ShrinkWalkSectors_amount(amount);
    sector = SectorList_FindNearestPoint(pos, 0x1000);
    if (sector != 0)
        Sector_ClampPoint(sector, (int)pos);
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
    Render_SetDrawEnabled((int)lua_getnumber(lua_lua2C(1)));
}

void sputLua_MakeCurrentSetupL(void)
{
    int arg = lua_lua2C(1);
    if (lua_isnumber(arg))
        Set_ChangeSetup((uint)(int)lua_getnumber(arg));
}

/* ==== costume component tag handlers: NewInstance of the Keyframe, Colormap and Mesh components ====
 * (KeyframeComponent_NewInstance 0x00497d10, CmapComponent_NewInstance 0x00496370, MeshComponent_NewInstance 0x00496d70)
 * Slot 5 of the tag: build (create != 0) or free (create == 0) the per-instance data of one component of a costume
 * instance.  Cos_InstComponentInfo(inst, component, &a, &info, &b) returns the component's record in `info` (for
 * keyframes and colormaps record[0] is the resource-valid flag and record[1] the resource) and the index of the parent
 * component in `b`.  By hand because the original passes the addresses of its own *parameter slots* as the output
 * pointers; Ghidra reused the slots as differently named variables (`&param_3`, `&param_2`, `&param_1`), the C text read
 * the wrong ones. */
int *KeyframeComponent_NewInstance(int inst, int component, int create)
{
    int aux, parent;
    int *info, *data, i;
    void *res;

    if (create == 0) {
        int d = Cos_InstGetInstanceData(inst, component, (int *)0);
        Res_RemoveReference((void *)(d + 4));
        (*g_pSputCosHS->pFree)(d);
        return (int *)0;
    }
    Cos_InstComponentInfo(inst, component, (int)&aux, (int)&info, (int)&parent);
    if (*info == 0)
        (*g_pStd_HS->pAssertFail)(s_Bad_keyframe_Reference_004ea1e0, s_main_sputResource_h_004e80a8, 0xb3);
    res = (void *)info[1];
    data = (int *)(*g_pSputCosHS->pAlloc)(0x40, s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0, 0xed8);
    for (i = 0; i < 0x10; i++)
        data[i] = 0;
    Res_SetReference(data + 1, res, s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0, 0xeda);
    data[0xe] = info[0xd];
    data[0xf] = info[0xe];
    data[0] = Cos_InstGetInstanceData(inst, parent, (int *)0);
    return data;
}

int *CmapComponent_NewInstance(int inst, int component, int create)
{
    int aux, parent, i;
    int *info, *data;

    if (create == 0) {
        int d = Cos_InstGetInstanceData(inst, component, (int *)0);
        Res_RemoveReference((void *)(d + 4));
        (*g_pSputCosHS->pFree)(d);
        return (int *)0;
    }
    data = (int *)(*g_pSputCosHS->pAlloc)(0x38, s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0, 0x8fa);
    Cos_InstComponentInfo(inst, component, (int)&aux, (int)&info, (int)&parent);
    for (i = 0; i < 0xe; i++)
        data[i] = 0;
    if (*info == 0)
        (*g_pStd_HS->pAssertFail)(s_Bad_Colormap_Reference_004e8090, s_main_sputResource_h_004e80a8, 0x9f);
    Res_SetReference(data + 1, (void *)info[1], s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0, 0x8ff);
    data[0] = Cos_InstGetInstanceData(inst, parent, (int *)0);
    return data;
}

int *MeshComponent_NewInstance(int inst, int component, int create)
{
    int aux, parent;
    int *data;

    if (create == 0) {
        (*g_pSputCosHS->pFree)(Cos_InstGetInstanceData(inst, component, (int *)0));
        return (int *)0;
    }
    data = (int *)(*g_pSputCosHS->pAlloc)(0xc, s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0, 0xb54);
    Cos_InstComponentInfo(inst, component, (int)&aux, (int)(data + 1), (int)&parent);   /* data[1] = the component's value */
    data[1] = data[1] >> 16;
    data[0] = Cos_InstGetInstanceData(inst, parent, (int *)0);
    data[2] = 1;
    return data;
}

/* ==== file / save-game helpers: stdFile_ReadByte, stdFile_WriteByte, SaveFile_CheckFUTBHeader, Res_SysSave,
 *      sputPrimitive_SaveState, sputPrimitive_RestoreState (0x004735f0 ... 0x004896b0) ====
 * The save-game code hands every module a callback (`write(buf, n)` / `read(buf, n)`, non-zero result = failure) and
 * each module streams its own state through it.  By hand because all of them pass the address of one of their own
 * *parameter slots* as the buffer (`&param_1`), which Ghidra splits into differently named variables. */
typedef int (*SaveIO)(void *buf, int n);

/* one byte from a file through the main service table (pFread); the byte lands in the low byte of the buffer */
uint stdFile_ReadByte(uint file)
{
    uint value = 0;
    (*g_pStd_HS->pFread)(file, &value, 1);
    return value & 0xff;
}

void stdFile_WriteByte(undefined4 value, undefined4 file)
{
    (*g_pStd_HS->pFwrite)(file, &value, 1);
}

/* the save file starts with 'FUTB', version 1, flags 0; returns 0 when the header matches, 1 otherwise */
undefined4 SaveFile_CheckFUTBHeader(code *readFn)
{
    SaveIO read = (SaveIO)readFn;
    int magic, version, flags;

    read(&magic, 4);
    if (magic != 0x42545546)
        return 1;
    read(&version, 4);
    if (version != 1)
        return 1;
    read(&flags, 4);
    if (flags != 0)
        return 1;
    return 0;
}

/* Resource_Filio module, save-game writer: the list of loaded files (g_pNewestResNode) -> count, then per saved file its name
 * (length + bytes), its flags word and its "loaded" word.  A file is saved when it has a handle (+0x24) and its name
 * does not contain the temporary-file marker, or when bit 3 of its flags is set. */
undefined4 Res_SysSave(code *writeFn)
{
    SaveIO write = (SaveIO)writeFn;
    int count = 0, len;
    int *file;

#define FILE_IS_SAVED(f) ((((f)[9] != 0 && String_ContainsSubstring((uint *)(f)[2], &DAT_004e7b14) == 0) || (*(byte *)((f) + 7) & 8) != 0))
    for (file = g_pNewestResNode; file != 0; file = (int *)*file)
        if (FILE_IS_SAVED(file))
            count++;
    if (write(&count, 4) != 0)
        return 1;
    for (file = g_pNewestResNode; file != 0; file = (int *)*file) {
        if (!FILE_IS_SAVED(file))
            continue;
        len = strlen((char *)file[2]);
        if (write(&len, 4) != 0 || write((void *)file[2], len) != 0 || write(file + 4, 4) != 0)
            return 1;
        file[6] = file[5];
        if (write(file + 6, 4) != 0)
            return 1;
    }
#undef FILE_IS_SAVED
    return 0;
}

/* sputPrimitive module, save-game writer: the screen primitives (list head in g_dwPrimitiveQ, next pointer at +0) */
undefined4 sputPrimitive_SaveState(code *writeFn)
{
    SaveIO write = (SaveIO)writeFn;
    int count = 0, id;
    int *prim;

    for (prim = (int *)g_dwPrimitiveQ; prim != 0; prim = (int *)*prim)
        count++;
    write(&count, 4);
    for (prim = (int *)g_dwPrimitiveQ; prim != 0; prim = (int *)*prim) {
        id = prim[2];
        write(&id, 4);
        write(prim + 3, 4);          /* id used by DrawLine & co */
        write(prim + 4, 4);          /* layer */
        write(prim + 5, 8);          /* x1, y1 */
        write(prim + 7, 8);          /* x2, y2 */
        write(prim + 9, 4);          /* colour */
        write(prim + 10, 4);
        write(prim + 11, 4);
    }
    return 0;
}

/* ... and the reader: clears the list, re-creates every primitive (PrimitiveList_Append) and fills in its fields */
undefined4 sputPrimitive_RestoreState(code *readFn)
{
    SaveIO read = (SaveIO)readFn;
    int count, kind, id, layer, color, f28, f2c;
    int rect[4];
    int *prim;

    PrimitiveList_Clear((int *)&g_dwPrimitiveQ);
    read(&count, 4);
    while (count != 0) {
        count--;
        rect[0] = rect[1] = rect[2] = rect[3] = 0;
        read(&kind, 4);
        read(&id, 4);
        read(&layer, 4);
        read(&rect[0], 8);
        read(&rect[2], 8);
        read(&color, 4);
        read(&f28, 4);
        read(&f2c, 4);
        prim = (int *)PrimitiveList_Append(&g_dwPrimitiveQ, id, layer);
        if (prim != 0) {
            prim[2] = kind;
            prim[5] = rect[0];
            prim[6] = rect[1];
            prim[7] = rect[2];
            prim[8] = rect[3];
            prim[9] = color;
            prim[10] = f28;
            prim[11] = f2c;
        }
        g_nNextPrimitiveId = id + 1;
    }
    return 0;
}

#endif /* GRIM_EXE */
