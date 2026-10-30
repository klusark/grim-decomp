/* Hand-written replacements for functions whose decompilation cannot be
 * compiled faithfully. tools/build_src.py puts the decompiled version of every
 * function defined here under `#if 0` and link.py links this file instead.
 * Keep each entry short and say why it is here. */
#include "ghidra_types.h"

/* stdMemory_CheckMagic (0x47fe20): asserts the 0x12345678 guard word in front
 * of an allocation. MSVC called it without pushing an argument because the
 * pointer already sat in the right stack slot; the C call site therefore
 * passes nothing and the decompiled body reads garbage. The guard is only an
 * assertion, so skip it. */
void stdMemory_CheckMagic(int p)
{
    (void)p;
}

/* COM calls through a vtable. Ghidra loses the arguments of `CALL [reg+off]` when it cannot type
 * the interface: the pushes show up as stack variables (including the return address) and the
 * call itself passes nothing. The functions below are rewritten from the disassembly. */
#define COM(obj, off, ...) ((int (__stdcall *)())(*(void ***)(obj))[(off) / 4])((obj), ##__VA_ARGS__)

#ifdef GRIM_EXE
extern int lua_dostring(const char *);   /* LUA.DLL */
extern char *GRIM_getenv(const char *) __asm__("_getenv");   /* host C runtime */
#include "globals.h"
#include "functions.h"


/* Test hook: run Lua statements in the game without any keyboard or mouse events. If the environment
 * variable GRIM_LUA_FILE names a file, every complete line appended to it is executed with
 * lua_dostring once per frame (at the start of Lua_UpdateFrame); the result (0 = ok) is appended to the file named
 * by GRIM_LUA_LOG. Nothing is sent to other windows or processes. The call sits at the start of
 * Lua_UpdateFrame (names/asm_patches.json). */
static void *lua_cmd_file;
static int lua_cmd_state;   /* 0 = not looked at yet, 1 = enabled, -1 = disabled */

static void lua_cmd_log(const char *text)
{
    const char *path = GRIM_getenv("GRIM_LUA_LOG");
    void *h;
    unsigned wrote;
    if (path == 0)
        return;
    h = CreateFileA(path, 4, 3, 0, 4, 0x80, 0);   /* FILE_APPEND_DATA */
    if (h != (void *)-1) {
        WriteFile(h, text, __builtin_strlen(text), &wrote, 0);
        CloseHandle(h);
    }
}

/* grimlog("text") from a command line appends the text to the log file */
static int grim_log_cfn(void)
{
    int arg = lua_lua2C(1);
    if (lua_isstring(arg)) {
        lua_cmd_log((const char *)lua_getstring(arg));
        lua_cmd_log("\r\n");
    }
    return 0;
}

void GRIM_lua_cmd_poll(void)
{
    static char line[1024];
    static int len;
    char buf[256];
    unsigned got, i;
    static int nomovie = -1;
    /* GRIM_NOMOVIE=1 (test runs): movies are skipped the way StartSmush=FALSE does it; the engine sets the flag
     * during start-up, so it is cleared again here, in every frame */
    if (nomovie < 0)
        nomovie = GRIM_getenv("GRIM_NOMOVIE") != 0;
    if (nomovie)
        g_nMovieAvailable = 0;
    /* GRIM_ACTIVE=1: draw and present even when the window is not the foreground window (the engine only
     * draws while WM_ACTIVATEAPP says the application is active); lets a test run behind other windows */
    if (GRIM_getenv("GRIM_ACTIVE")) {
        UINT_008d0a70 = 1;
        UINT_008d0a6c = 1;
    }
    if (lua_cmd_state < 0)
        return;
    if (lua_cmd_state == 0) {
        const char *path = GRIM_getenv("GRIM_LUA_FILE");
        lua_cmd_state = -1;
        if (path == 0)
            return;
        lua_cmd_file = CreateFileA(path, 0x80000000, 3, 0, 4, 0x80, 0);   /* read, share r/w, OPEN_ALWAYS */
        if (lua_cmd_file == (void *)-1)
            return;
        lua_cmd_state = 1;
        lua_pushCclosure((void *)grim_log_cfn, 0);
        lua_setglobal("grimlog");
        lua_cmd_log("lua hook active\r\n");
    }
    while (ReadFile(lua_cmd_file, buf, sizeof buf, &got, 0) && got) {
        for (i = 0; i < got; i++) {
            if (buf[i] == '\n' || len >= 1023) {
                char msg[1100];
                int rc;
                line[len] = 0;
                if (len) {
                    /* a Load replaces the whole Lua state: define grimlog again for every command */
                    lua_pushCclosure((void *)grim_log_cfn, 0);
                    lua_setglobal("grimlog");
                    rc = lua_dostring(line);
                    wsprintfA(msg, "rc=%d: %s\r\n", rc, line);
                    lua_cmd_log(msg);
                }
                len = 0;
            } else if (buf[i] != '\r') {
                line[len++] = buf[i];
            }
        }
    }
}

/* Input_CreateKeyboard (0x477530): system keyboard, c_dfDIKeyboard format,
 * buffered input of 32 events (DIPROP_BUFFERSIZE). */
void Input_CreateKeyboard(void)
{
    unsigned prop[5] = { 0x14, 0x10, 0, 0, 0x20 };
    char msg[96];
    int r1, r2, r3, r4;
    if (g_pDirectInput == 0)
        return;
    r1 = COM(g_pDirectInput, 0xc, &DAT_004d8350, &g_pDInputKeyboard, 0);
    r2 = r3 = r4 = -1;
    if (r1 == 0) {
        r2 = COM(g_pDInputKeyboard, 0x2c, &DAT_004d5370);
        /* the original never sets a cooperative level (DirectInput 5 assumed foreground, shared); current
         * DirectInput refuses Acquire without one (E_INVALIDARG) */
        r3 = COM(g_pDInputKeyboard, 0x34, Win_GetMainHwnd(), 6);
        r4 = COM(g_pDInputKeyboard, 0x18, 1, prop);
    }
    wsprintfA(msg, "grim: keyboard create=%x format=%x coop=%x bufsize=%x\n", r1, r2, r3, r4);
    OutputDebugStringA(msg);
}

/* Input_CreateMouse (0x4775a0): system mouse, c_dfDIMouse format, exclusive
 * foreground access, buffered input; axes 12/13/14 are x, y, wheel. */
void Input_CreateMouse(void)
{
    unsigned prop[5] = { 0x14, 0x10, 0, 0, 0x20 };
    if (g_pDirectInput == 0)
        return;
    GetSystemMetrics(0x2b);
    if (COM(g_pDirectInput, 0xc, &DAT_004d8340, &g_pDInputMouse, 0) != 0)
        return;
    if (COM(g_pDInputMouse, 0x2c, &DAT_004d5400) != 0)
        return;
    if (COM(g_pDInputMouse, 0x34, Win_GetMainHwnd(), 5) != 0)
        return;
    COM(g_pDInputMouse, 0x18, 1, prop);
    Input_SetAxisRange(0xc, -0xfa, 0xfa, 0.0);
    Input_SetAxisRange(0xd, -200, 200, 0.0);
    Input_SetAxisRange(0xe, -0x14, 0x14, 0.0);
}

/* DSound_Init (0x4c0ed0): DirectSound object, priority cooperative level,
 * primary buffer (22050 or 11025 Hz 16-bit stereo), optional 3D listener. */
undefined4 DSound_Init(void)
{
    struct { unsigned size, flags, bytes, reserved, format; } desc;
    struct { unsigned short tag, channels; unsigned rate, avg; unsigned short align, bits, cb; } wfx;
    unsigned hwnd;
    int rate;

    if (g_pDirectSound != 0)
        return 0;
    UINT_008d3664 = 0;
    if (DirectSoundCreate(0, &g_pDirectSound, 0) < 0) {
        g_pDirectSound = 0;
        return 0;
    }
    hwnd = (unsigned)Win_GetMainHwnd();
    if (COM(g_pDirectSound, 0x18, hwnd, 2) < 0)
        return 1;
    desc.size = 0x14;
    desc.flags = UINT_008d3664 ? 0x91 : 0x81;   /* PRIMARYBUFFER | CTRLVOLUME [| CTRL3D] */
    desc.bytes = 0;
    desc.reserved = 0;
    desc.format = 0;
    UINT_008d3654 = hwnd;
    if (COM(g_pDirectSound, 0xc, &desc, &g_pDSoundPrimary, 0) < 0) {
        g_pDSoundPrimary = 0;
        return 1;
    }
    COM(g_pDSoundPrimary, 0x18, &UINT_008d3658);          /* GetVolume */
    rate = UINT_008d3660 ? 0x2b11 : 0x5622;
    wfx.tag = 1;
    wfx.channels = 2;
    wfx.rate = rate;
    wfx.avg = rate << 2;
    wfx.align = 4;
    wfx.bits = 0x10;
    wfx.cb = 0;
    COM(g_pDSoundPrimary, 0x38, &wfx);                   /* SetFormat */
    DSound_SetPrimaryVolume(UINT_004f1000);
    if (UINT_008d3664 != 0) {
        if (COM(g_pDSoundPrimary, 0, &DAT_004d8510, &PTR_008d3674) < 0) {
            UINT_008d3664 = 0;
            PTR_008d3674 = 0;
        } else {
            COM(PTR_008d3674, 0x2c, 0x3f000000, 1);
            COM(PTR_008d3674, 0x3c, 0, 1);
        }
    }
    COM(g_pDSoundPrimary, 0x30, 0, 0, 0);                /* Play */
    COM(g_pDirectSound, 0x18, hwnd, 3);                  /* SetCooperativeLevel: exclusive */
    return 1;
}

unsigned long __attribute__((stdcall)) GRIM_GetEnv(const char *, char *, unsigned long) __asm__("_GetEnvironmentVariableA@12");

/* Display_InitFromConfig (0x402930): the game normally restores the last display from the registry
 * or picks the closest fullscreen DirectDraw device. This build runs in the software renderer: device
 * 0 is "Window Display Device" (a DIB section in the game window), which works on any machine.
 * GRIM_DISPLAY_DEVICE=<n> selects another enumerated device (1 is the DirectDraw display). */
undefined *Display_InitFromConfig(void)
{
    char e[8] = "";
    int dev;
    GRIM_GetEnv("GRIM_DISPLAY_DEVICE", e, sizeof e);
    dev = (e[0] >= '0' && e[0] <= '9') ? e[0] - '0' : 0;
    unsigned mode;
    if ((unsigned)dev >= (unsigned)g_dwDisplayDeviceCount)
        dev = 0;
    mode = Display_FindClosestMode(&UINT_004f4d38,
                                   (void *)((unsigned *)g_pDisplayModes)[dev * 4 + 1],
                                   ((unsigned *)g_pDisplayModes)[dev * 4]);
    return (undefined *)(unsigned)Display_Select(dev, (int)mode, -1);
}



/* Costume_ApplyScale (0x495510): called before and after the meshes of a scaled actor are drawn; it
 * multiplies the bounding radius of every model (and of every mesh) by actor+0x30 so that the
 * frustum test in rdModel_DrawMesh covers the scaled-up geometry, then stores the reciprocal of the
 * scale in actor+0x30 so that the second call undoes the first. The original code stores the
 * reciprocal inside the per-component loop, so the factor alternates s, 1/s, s, ... from component to
 * component: with an even number of components (Manny has 26) the second call does not undo the
 * first, every call scales the even components by s and the odd ones by 1/s again, and the radii
 * drift by s^2 per frame (to infinity / zero). A model whose radius has shrunk is judged "inside the
 * frustum" although its polygons stick out, rdModel_AddMeshToCache then skips the clipper, and an
 * unclipped polygon on the screen edge makes the span routines write rows outside the z-buffer.
 * Here the factor is the same for all components and is inverted once per call. Non-model
 * components (type != 1, e.g. colormaps) are left alone: the original multiplied a float at +0x5c of
 * whatever object they point to. */
void __cdecl Costume_ApplyScale(void *actor, void *componentList)
{
    float s = *(float *)((char *)actor + 0x30);
    void *c;
    float inv, d;

    if (componentList == 0 || s == 1.0f)
        return;
    for (c = componentList; c != 0; c = *(void **)((char *)c + 400)) {
        int *data = *(int **)((char *)c + 0x40);
        char *model;
        if (data == 0 || data[0] != 1)
            continue;
        model = (char *)data[1];
        *(float *)(model + 0x5c) *= s;
        {
            int set = *(int *)(model + 0x50);
            unsigned n = *(unsigned *)(model + 0x24 + set * 8);
            char *mesh = *(char **)(model + 0x28 + set * 8);
            unsigned i;
            for (i = 0; i < n; i++)
                *(float *)(mesh + i * 0x7c + 0x60) *= s;
        }
    }
    inv = 1.0f / s;
    d = 1.0f - inv;
    *(float *)((char *)actor + 0x30) = inv;
    if ((d < 0 ? -d : d) <= 1e-05f)
        *(float *)((char *)actor + 0x30) = 1.0f;
}

/* stdFile_Open (0x473430): fopen for the engine's file services. The original binary used its own MSVC 6 C runtime;
 * this build links the host msvcrt, whose text-mode ftell() returns 0 after a one-byte fread() (checked with a
 * stand-alone program). Lua's dofile reads the first character of a script, calls ftell and seeks back by one, so
 * every *text* script (a loose _system.lua, mod.lua ...; TextAllowed=TRUE) lost its first character and silently
 * failed to parse. Read-mode opens are therefore done in binary mode (Lua 3.1 treats "\r\n" as white space). */
extern void *GRIM_host_fopen(const char *, const char *) __asm__("_fopen");
undefined * __cdecl stdFile_Open(uint param_1, uint param_2)
{
    const char *name = (const char *)param_1, *mode = (const char *)param_2;
    char m[8];
    int i = 0, has_b = 0, has_plus = 0, is_r = (mode[0] == 'r');
    for (; mode[i] && i < 6; i++) {
        m[i] = mode[i];
        has_b |= (mode[i] == 'b');
        has_plus |= (mode[i] == '+');
    }
    if (is_r && !has_b && !has_plus)
        m[i++] = 'b';
    m[i] = 0;
    return (undefined *)GRIM_host_fopen(name, m);
}


/* ===================================================================================================
 * Example mods (docs/MODDING.md): a C change to the walker and new Lua API functions.
 * =================================================================================================== */

extern double GRIM_atof(const char *) __asm__("_atof");   /* host C runtime */

/* Walk speed scale. Every actor's walk step is dt * timeScale * walkRate (Actor_UpdateWalker); this factor is
 * applied on top. Default 1.0; GRIM_WALK_SCALE=<float> in the environment sets the start value and the Lua function
 * SetWalkSpeedScale(x) changes it at run time. */
static float g_fWalkSpeedScale = 1.0f;
static int g_bWalkScaleInit;

static void walk_scale_init(void)
{
    const char *e;
    if (g_bWalkScaleInit)
        return;
    g_bWalkScaleInit = 1;
    e = GRIM_getenv("GRIM_WALK_SCALE");
    if (e && GRIM_atof(e) > 0.0)
        g_fWalkSpeedScale = (float)GRIM_atof(e);
}

/* float -> its IEEE bits: the original passes float arguments of Walker_TurnHeading/Walker_WalkSectors in int slots */
static int float_bits(float f)
{
    union { float f; int i; } u;
    u.f = f;
    return u.i;
}

#define ACT_I(p, off) (*(int *)((char *)(p) + (off)))
#define ACT_F(p, off) (*(float *)((char *)(p) + (off)))

/* Actor_UpdateWalker (0x491110), rewritten from the disassembly with the walk speed scale added. Actor layout (see the
 * plate comment of Actor_Create): +8 flags (bit 0 = following a path), +0xa4 extra. Extra: +0xc walk-forward flag,
 * +0x10 turn direction (-1/0/1), +0x18 walk rate, +0x1c turn rate, +0x20 yaw done, +0x28 yaw error, +0x1b4 walker,
 * +0x1bc follow-boxes off, +0x41c time scale. */
void Actor_UpdateWalker(int actor)
{
    int extra = ACT_I(actor, 0xa4);
    float *walker = (float *)ACT_I(extra, 0x1b4);
    float dt;

    walk_scale_init();
    if (ACT_I(extra, 0x10) != 0 && (ACT_I(actor, 8) & 1) == 0) {
        dt = Timer_GetFrameSeconds();
        Walker_TurnHeading(walker, float_bits((float)ACT_I(extra, 0x10) * ACT_F(extra, 0x1c) * dt * ACT_F(extra, 0x41c)));
    }
    extra = ACT_I(actor, 0xa4);
    if (ACT_I(extra, 0xc) != 0) {
        int a2, a3;
        dt = Timer_GetFrameSeconds();
        if (ACT_I(extra, 0x1bc) == 0) {
            a3 = ACT_I(extra, 0x10) != 1;
            a2 = ACT_I(extra, 0x10) != -1;
        } else {
            a3 = 1;
            a2 = 1;
        }
        ACT_I(ACT_I(actor, 0xa4), 0xc) =
            (int)Walker_WalkSectors(walker, float_bits(dt * ACT_F(extra, 0x41c) * ACT_F(extra, 0x18) * g_fWalkSpeedScale), a2, a3);
    }
    ACT_I(ACT_I(actor, 0xa4), 0x20) = Walker_UpdateYaw((void *)actor, walker);
    extra = ACT_I(actor, 0xa4);
    if (ACT_I(extra, 0x10) == 0 && ACT_I(extra, 0x20) == 0)
        ACT_I(extra, 0x10) = (ACT_F(extra, 0x28) <= 0.0f) ? 1 : -1;
    ACT_I(actor, 0xc) = ((int *)walker)[0];
    ACT_I(actor, 0x10) = ((int *)walker)[1];
    ACT_I(actor, 0x14) = ((int *)walker)[2];
    ACT_I(actor, 0x34) = 0;
}

/* ---- new Lua API functions ----
 * A Lua C function takes no C arguments: it reads its Lua arguments with lua_lua2C(1..n) (+ lua_getnumber,
 * lua_getstring, lua_isnumber ...) and returns its results by pushing them (lua_pushnumber, lua_pushstring, ...). */
static int Lua_GetEngineVersionString(void)
{
    lua_pushstring("Grim Fandango GOG v1.01 decompilation rebuild, built " __DATE__ " " __TIME__);
    return 0;
}

static int Lua_SetWalkSpeedScale(void)
{
    int arg = lua_lua2C(1);
    walk_scale_init();
    if (lua_isnumber(arg))
        g_fWalkSpeedScale = lua_getnumber(arg);
    return 0;
}

static int Lua_GetWalkSpeedScale(void)
{
    walk_scale_init();
    lua_pushnumber(g_fWalkSpeedScale);
    return 0;
}

/* Table in the same {name, function} format as the engine's own (0x004ea8b0); lua_openlib registers every entry as a
 * global and lua_recognizelib makes the functions known to the save/restore code. */
static struct { const char *name; void *fn; } mod_api[] = {
    { "GetEngineVersionString", (void *)Lua_GetEngineVersionString },
    { "SetWalkSpeedScale",      (void *)Lua_SetWalkSpeedScale },
    { "GetWalkSpeedScale",      (void *)Lua_GetWalkSpeedScale },
};

/* Called right after the engine registered its own table: names/asm_patches.json inserts `call _GRIM_RegisterModApi`
 * into Lua_InitGameLibs (0x49de00), after the Lua_OpenEngineLib call. */
void GRIM_RegisterModApi(void)
{
    lua_openlib(mod_api, sizeof mod_api / sizeof mod_api[0]);
}

#endif /* GRIM_EXE */

#ifdef GRIM_IMUSE
#include "globals.h"
#include "functions.h"

/* The iMUSE re-entrancy guard (DAT_100172c0, Enter/Leave around nearly every Im* call) is a plain counter:
 * Enter is INC without LOCK, Leave is load / test / dec / store. The WINMM heartbeat thread and the main thread
 * leave at the same moment now and then, both read 2 and store 1, and the counter stays 1 for good: ImHeartbeat
 * (which only runs at 0) never runs again, no stream is consumed and SoundsFloodMusicBuffer (Set_LoadResources)
 * spins forever (seen with fast set switches and with the original binary too). Same semantics, made atomic. */
/* OVERRIDES: Im_GuardEnter Im_GuardLeave */
__asm__(".text\n"
        ".def _Im_GuardEnter; .scl 2; .type 32; .endef\n"
        ".globl _Im_GuardEnter\n"
        "_Im_GuardEnter:\n"
        "    lock incl _DAT_100172c0\n"
        "    ret\n"
        ".def _Im_GuardLeave; .scl 2; .type 32; .endef\n"
        ".globl _Im_GuardLeave\n"
        "_Im_GuardLeave:\n"
        "1:  movl _DAT_100172c0, %eax\n"
        "    testl %eax, %eax\n"
        "    jz 2f\n"
        "    leal -1(%eax), %ecx\n"
        "    lock cmpxchgl %ecx, _DAT_100172c0\n"
        "    jnz 1b\n"
        "2:  ret\n");

/* FUN_10008ce0 (iMUSE heartbeat timer start-up): the decompiler lost the TIMECAPS
 * structure it reads back from the stack (wPeriodMin/wPeriodMax became unaff_ESI /
 * unaff_EDI, which made the period 0). Rewritten from the disassembly:
 * period = min(max(wPeriodMin, 50), wPeriodMax). The heartbeat callback
 * (FUN_10008e00, __stdcall with five arguments) must fire within 4 s, retried
 * twice, or the function reports failure. */
int FUN_10008ce0(void)
{
    unsigned caps[2];
    unsigned period, lo;
    int start, tries;

    if (timeGetDevCaps(caps, 8) != 0)
        return 0;
    lo = caps[0] > 0x32 ? caps[0] : 0x32;
    period = (lo >= caps[1]) ? caps[1] : lo;
    _DAT_1002e338 = 1000 / period;
    _DAT_10031520 = period;
    timeBeginPeriod(period);
    _DAT_10031d28 = timeSetEvent(_DAT_1002e338, 0, (void *)FUN_10008e00, 0xf, 1);
    start = timeGetTime();
    _DAT_10031e84 = 0;
    for (tries = 3; tries > 0; tries--) {
        if (_DAT_10031e84 != 0)
            return _DAT_10031e84;
        while ((unsigned)(timeGetTime() - start) < 4000) {
            if (_DAT_10031e84 != 0)
                return _DAT_10031e84;
        }
        if (_DAT_10031e84 == 0) {
            timeKillEvent(_DAT_10031d28);
            timeEndPeriod(_DAT_10031520);
            timeBeginPeriod(_DAT_10031520);
            _DAT_10031d28 = timeSetEvent(_DAT_1002e338, 0, (void *)FUN_10008e00, 0xf, 1);
            start = timeGetTime();
        }
    }
    return _DAT_10031e84;
}

/* Im_DSoundCreateBuffer (0x10003930): secondary streaming buffer of n * 0x1800
 * bytes (n clamped to 3..16), zero-filled and played in a loop. The decompiler lost
 * every COM argument and turned the lock/clear/unlock into stack writes, so it is
 * rewritten from the disassembly. IDirectSoundBuffer slots: 8 Release, 0x2c Lock,
 * 0x30 Play, 0x3c SetVolume, 0x4c Unlock; IDirectSound 0xc CreateSoundBuffer. */
void Im_DSoundCreateBuffer(int n)
{
    struct { unsigned size, flags, bytes, reserved; void *format; } desc;
    void *p1 = 0, *p2 = 0;
    unsigned b1 = 0, b2 = 0;

    DAT_1002d840 = 1;
    if (PTR_1002d83c != 0)
        COM(PTR_1002d83c, 8);
    PTR_1002d83c = 0;
    if (n < 3)
        n = 3;
    if (n > 0x10)
        n = 0x10;
    DAT_1002d824 = n;
    desc.size = 0x14;
    desc.flags = 0x18080;           /* GETCURRENTPOSITION2 | GLOBALFOCUS | CTRLVOLUME */
    desc.bytes = n * 0x1800;
    desc.reserved = 0;
    desc.format = &DAT_100170f0;
    if (COM(PTR_1002d834, 0xc, &desc, &PTR_1002d83c, 0) == 0) {
        COM(PTR_1002d83c, 0x3c, 0);
        if (COM(PTR_1002d83c, 0x2c, 0, n * 0x1800, &p1, &b1, &p2, &b2, 0) == 0) {
            unsigned i;
            for (i = 0; i < b1; i++)
                ((unsigned char *)p1)[i] = 0;
            if (p2 != 0)
                for (i = 0; i < b2; i++)
                    ((unsigned char *)p2)[i] = 0;
            COM(PTR_1002d83c, 0x4c, p1, b1, p2, b2);
        }
        COM(PTR_1002d83c, 0x30, 0, 0, 1);   /* Play, looping */
    }
    DAT_1002d840 = 0;
}
/* FUN_1000c670 is MSVC's _output(FILE *, format, va_list), the printf engine of IMUSE.DLL's own C runtime
 * (the only callers are the sprintf/vsprintf wrappers, which pass a string stream {ptr, cnt, base, flag}).
 * Ghidra splits the function at its jump table, the compiled version jumps into data and crashes the first
 * time iMUSE formats a log line ("opening <file>.IMC"). The host formatter does the same job: format at
 * the stream pointer and advance ptr/cnt like _output would. */
extern int host_vsprintf(char *, const char *, char *) __asm__("___mingw_vsprintf");   /* not the CRT port's own vsprintf */
int FUN_1000c670(int *stream, char *format, undefined4 *args)
{
    int n = host_vsprintf((char *)stream[0], format, (char *)args);
    stream[0] += n;
    stream[1] -= n;
    return n;
}
#endif /* GRIM_IMUSE */

#if defined(GRIM_CHORE) || defined(GRIM_EXE) || defined(GRIM_LUA)
#include "functions.h"
/* FUN_10006b30 (0x10006b30) is MSVC's _input(FILE *, format, va_list), the scanf engine. Ghidra
 * splits its jump-table cases into pieces, so it can neither be decompiled nor assembled from its
 * listing. sscanf calls it on a FILE that wraps a string (_ptr = current position, MSVC layout
 * {_ptr, _cnt, _base, _flag}), so the host's vsscanf on that string does the same job. */
/* (mingw's vsscanf is no help: it rebuilds the call from the format and crashes on these.) Every
 * scanf output is a pointer, so the va_list words are forwarded to msvcrt's sscanf as 32 extra
 * arguments; the callee reads as many as the format needs and the caller pops them all. */
typedef int (*scanf_fn)(const char *, const char *,
                        unsigned, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned,
                        unsigned, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned,
                        unsigned, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned,
                        unsigned, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned);
/* libmsvcrt.a has no import entry for sscanf (mingw has its own), so ask msvcrt.dll for it */
extern void *__attribute__((stdcall)) GRIM_LoadLibraryA(const char *) __asm__("_LoadLibraryA@4");
extern void *__attribute__((stdcall)) GRIM_GetProcAddress(void *, const char *) __asm__("_GetProcAddress@8");
/* OVERRIDES: _input FUN_10006b30 */
#if defined(GRIM_CHORE)
int FUN_10006b30(undefined4 stream, byte *format, undefined4 *a)
#elif defined(GRIM_LUA)
int __cdecl _input(int *stream, byte *format, undefined4 *a)
#else
/* the EXE's own copy of the same function (0x004b3620) */
uint _input(undefined4 stream, byte *format, uint *a)
#endif
{
    static scanf_fn host_sscanf;
    const char *s = *(const char **)(unsigned)stream;
    if (!host_sscanf)
        host_sscanf = (scanf_fn)GRIM_GetProcAddress(GRIM_LoadLibraryA("msvcrt.dll"), "sscanf");
    return host_sscanf(s, (const char *)format,
                         a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7],
                         a[8], a[9], a[10], a[11], a[12], a[13], a[14], a[15],
                         a[16], a[17], a[18], a[19], a[20], a[21], a[22], a[23],
                         a[24], a[25], a[26], a[27], a[28], a[29], a[30], a[31]);
}
#endif /* GRIM_CHORE || GRIM_EXE || GRIM_LUA */

/* MSVC 6 pow family (_CIpow takes its operands on the x87 stack, _pow on the C stack). The CRT's own
 * versions branch through special-case helpers that live in pieces Ghidra cannot stitch together, so
 * both go to the host msvcrt's pow instead. */
/* OVERRIDES: _pow _CIpow */
__asm__(".text\n"
        ".globl __pow\n"
        "__pow:\n"
        "    jmp *__imp__pow\n"
        ".globl __CIpow\n"
        "__CIpow:\n"
        "    subl $16, %esp\n"
        "    fstpl 8(%esp)\n"      /* exponent: ST(0) */
        "    fstpl (%esp)\n"       /* base: ST(1) */
        "    call *__imp__pow\n"
        "    addl $16, %esp\n"
        "    ret\n");

#ifdef GRIM_LUA
/* LUA.DLL's fmod (math.mod): _CIfmod = FUN_100120fa (fastcall, operands on the x87 stack: ST(0) = y, ST(1) = x)
 * funnels through the CRT's _ctrlfp/_handle_exc pieces that Ghidra cannot stitch together (it called through
 * the address -6: crash whenever a script used mod). Host msvcrt's fmod does the job. */
/* OVERRIDES: FUN_100120fa */
__asm__(".text\n"
        ".globl @FUN_100120fa@4\n"
        "@FUN_100120fa@4:\n"
        "    subl $16, %esp\n"
        "    fstpl 8(%esp)\n"     /* y: ST(0) */
        "    fstpl (%esp)\n"      /* x: ST(1) */
        "    call *__imp__fmod\n"
        "    addl $16, %esp\n"
        "    ret\n");
#endif

#ifdef GRIM_EXE
/* OVERRIDES: Win_AbortIfAlreadyRunning */
/* The original quits when a "Grim Fandango" window already exists. Setting GRIM_MULTI lets several
 * test instances run side by side (used when more than one session debugs the game). */
void __cdecl Win_AbortIfAlreadyRunning(void *hInstance, void *hPrevInstance, char *cmdLine,
                                       int nCmdShow, char *appName)
{
    int iVar1;
    int iVar2;

    if (GRIM_getenv("GRIM_MULTI")) {
        /* a different title also passes the check in Win_CreateMainWindow; GRIM_MULTI=<tag> makes it
         * "Grim Fandango (<tag>)" so that several sessions with different tags can run at once */
        static char title[64];
        const char *tag = GRIM_getenv("GRIM_MULTI");
        wsprintfA(title, "Grim Fandango (%s)", tag[0] == '1' && !tag[1] ? "test" : tag);
        appName = title;
    }
    iVar1 = FindWindowA(IMG_ADDR(0x004ed080), (int)appName);
    if (iVar1 != 0) {
        SetForegroundWindow(iVar1);
        ShowWindow(iVar1, 9);
        exit(0xffffffff);
    }
    UINT_008d0a7c = 0;
    g_dwWinDialogCount = 0;
    g_nWinQuit = 0;
    UINT_008d0a8c = 0;
    UINT_008d09e4 = (uint)hInstance;
    _DAT_008d09e0 = nCmdShow;
    Win_CreateMainWindow((uint)hInstance, nCmdShow, (int)appName);
    Win_SetMainHwnd(g_pWinMainHwnd);
    Win_SetInstance(UINT_008d09e4);
    InitCommonControls();
    iVar1 = GetSystemMetrics(0x20);
    UINT_008d0a84 = iVar1 << 1;
    iVar1 = GetSystemMetrics(0x20);
    iVar2 = GetSystemMetrics(0xf);
    UINT_008d0a88 = iVar2 + iVar1 * 2;
    iVar1 = Grim_Init(cmdLine);
    if (iVar1 != 0) {
        UINT_008d0a8c = 1;
        do {
            Win_PumpMessages();
        } while (g_nWinQuit == 0);
    }
}
#endif

#ifdef GRIM_EXE
/* OVERRIDES: Win_CreateMainWindow */
/* Win_CreateMainWindow (0x4ac1f0): the original creates the 'wKernel' window as a borderless WS_POPUP the size of the
 * whole desktop (GetSystemMetrics(0/1)) and shows it at once, because a DirectDraw full-screen device draws into it.
 * The windowed (DIB section) display device that this build selects (Display_InitFromConfig) only shrinks it to
 * 640x480 with a caption in Win_SetWindowedSize at the very end of Display_Select, after DirectDrawEnumerate has
 * probed the DirectDraw devices with SetCooperativeLevel(EXCLUSIVE|FULLSCREEN) / (NORMAL) on that window. Until then
 * the whole screen is covered by a black topmost window (the 'entire screen flickers black at start-up' report,
 * ~0.5 s here, longer on slower starts). So when a windowed device will be used, create the window right away in
 * its final windowed form (the style and size Win_SetWindowedSize would give it for 640x480), at the same place and
 * with the same ShowWindow/UpdateWindow, so the activation order is unchanged; GRIM_DISPLAY_DEVICE=<n> (n > 0, a
 * DirectDraw full-screen device) keeps the original full-screen popup. */
undefined4 Win_CreateMainWindow(uint param_1, undefined4 param_2, int param_3)
{
    unsigned wc[12];
    int iVar1;
    int style, x, y, w, h;
    char e[8] = "";

    wc[0] = 0x30;                         /* cbSize */
    wc[1] = 3;                            /* CS_HREDRAW | CS_VREDRAW */
    wc[2] = (uint)Win_KernelWndProc;
    wc[3] = 0;
    wc[4] = 0;
    wc[5] = param_1;
    wc[6] = LoadIconA(param_1, IMG_ADDR(0x004ed088));
    if (wc[6] == 0)
        wc[6] = LoadIconA(0, 0x7f00);
    wc[7] = LoadCursorA(0, 0x7f00);
    wc[8] = GetStockObject(4);            /* BLACK_BRUSH */
    wc[9] = 0;
    wc[10] = (uint)IMG_ADDR(0x004ed080);  /* "wKernel" */
    wc[11] = LoadIconA(param_1, IMG_ADDR(0x004ed088));
    if (wc[11] == 0)
        wc[11] = LoadIconA(0, 0x7f00);
    iVar1 = RegisterClassExA((int)wc);
    if ((short)iVar1 == 0)
        return 0;
    iVar1 = FindWindowA(IMG_ADDR(0x004ed080), param_3);
    if (iVar1 != 0)
        exit(0xffffffff);

    GRIM_GetEnv("GRIM_DISPLAY_DEVICE", e, sizeof e);
    if (e[0] > '0' && e[0] <= '9') {
        style = -0x70000000;              /* WS_POPUP | WS_VISIBLE, desktop sized (original) */
        x = y = 0;
        w = GetSystemMetrics(0);
        h = GetSystemMetrics(1);
    } else {
        /* same numbers as Win_AbortIfAlreadyRunning / Win_SetWindowedSize: 640x480 client + frame */
        int frame = GetSystemMetrics(0x20);
        style = 0x10cf0000;               /* WS_VISIBLE | WS_OVERLAPPEDWINDOW minus thick frame/maximize */
        x = y = 0;
        w = 640 + frame * 2;
        h = 480 + GetSystemMetrics(0xf) + frame * 2;
    }
    g_pWinMainHwnd = (void *)CreateWindowExA(0x40000, IMG_ADDR(0x004ed080), param_3, style, x, y, w, h, 0, 0, param_1, 0);
    if (g_pWinMainHwnd == (void *)0x0)
        return 0;
    UINT_008d09e4 = param_1;
    ShowWindow((int)g_pWinMainHwnd, 1);
    UpdateWindow((int)g_pWinMainHwnd);
    return 1;
}
#endif

#ifdef GRIM_EXE
/* PrintDebug / PrintWarning / PrintError (0x49ddd0): the retail game registers one empty function for all
 * three. The scripted tests (grim_tools/autorun) read their results from a log, like the grimdlg.dll patch
 * of the original exe does: with GRIM_DEBUGLOG=<file> every message is appended as "[ms since start] DEBUG text"
 * (the level is not known to a shared function, so everything is DEBUG). */
/* OVERRIDES: Lua_Print_NoOp */
void Lua_Print_NoOp(void)
{
    static unsigned t0;
    const char *path = GRIM_getenv("GRIM_DEBUGLOG");
    int arg = lua_lua2C(1);
    if (path == 0 || lua_isnil(arg) || !lua_isstring(arg))
        return;
    {
        const char *text = (const char *)lua_getstring(arg);
        unsigned len = __builtin_strlen(text), wrote;
        char head[40];
        void *h;
        while (len > 0 && (text[len - 1] == '\n' || text[len - 1] == '\r'))
            len--;
        if (!t0)
            t0 = GetTickCount();
        h = CreateFileA(path, 4, 3, 0, 4, 0x80, 0);   /* FILE_APPEND_DATA */
        if (h == (void *)-1)
            return;
        wsprintfA(head, "[%8u] DEBUG ", GetTickCount() - t0);
        WriteFile(h, head, __builtin_strlen(head), &wrote, 0);
        WriteFile(h, text, len, &wrote, 0);
        WriteFile(h, "\r\n", 2, &wrote, 0);
        CloseHandle(h);
    }
}

/* The frame time of Game_FrameUpdate (0x401721 loads the one-shot "fixed frame time" DAT_004f5a48, 0 = wall
 * clock): GRIM_SIMTIME=<ms> makes every frame that long whatever the machine does (the scripted tests compare
 * against values recorded on the original with a fixed 17 ms frame). names/asm_patches.json calls this. */
int GRIM_SimTime(void)
{
    static int ms = -1;
    if (ms < 0) {
        const char *e = GRIM_getenv("GRIM_SIMTIME");
        ms = e ? (int)GRIM_atof(e) : 0;
    }
    return ms;
}
#endif
