/* Readable C for the rest of the assembled functions between 0x004bdf00 and 0x004d4100:
 *   - SmushPlay_GetMovieLength (movie length from the file header),
 *   - the light editor's text field reader and keyboard hook (LightEd_ReadControl, LightEd_KeyboardProc),
 *   - LecShare_Subscribe (lookup of a shared module through the override list),
 *   - AnimPlay, the Smush frame player (create, destroy, once-per-frame update, reset, open),
 *   - the small glue around zlib 1.1.3 gzio.c (gz_open with the file service table, gz_putLong, Zfile_fle_Close) and the
 *     StdFile position helpers.
 * Differential tests: build/mixdiff/misc_test.c (docs/notes/mixer.md). */
#include "ghidra_types.h"

#ifdef GRIM_EXE
#include "globals.h"
#include "functions.h"

/* the services the modules ask the module manager for: tables of function pointers */
#define SVC_CALL(svc, i, ret, args) ((ret(*) args)(((void **)(svc))[i]))

/* ===================================================================================================================
 *  SmushPlay_GetMovieLength
 * =================================================================================================================== */

extern void **g_pInsaneFileOps __asm__("_g_pSmushPlay_file_services");     /* [0] open(path, mode), [1] close, [2] read(file, buf, n), [4] tell, [5] seek */

/* Opens a movie file, reads its header and returns the length in milliseconds (a 16 bit header field times 66.67, the
 * milliseconds of a frame at 15 frames per second); 0 if the file cannot be opened. */
int SmushPlay_GetMovieLength(char *path)
{
    byte header[0x420];
    void *file = SVC_CALL(g_pInsaneFileOps, 0, void *, (char *, const void *))(path, &DAT_004dda54);

    if (file == 0)
        return 0;
    smushplay_GetInfo((int)file, (int)header);
    SVC_CALL(g_pInsaneFileOps, 1, void, (void *))(file);
    return (int)((double)(int)*(short *)(header + 2) * 66.666664f);
}

/* ===================================================================================================================
 *  light editor
 * =================================================================================================================== */

typedef struct LightEdEntry {       /* 20 bytes, array at 0x008d1730 */
    byte *light;                    /* the rdLight: +20 x, +24 y, +28 z (float), +2c angle block, +44 intensity, +4c inner, +54 outer */
    int field4;
    float angle[3];
} LightEdEntry;

extern LightEdEntry g_aLightEdEntries[] __asm__("_UINT_008d1730");

static uint float_bits(float f) { uint u; __builtin_memcpy(&u, &f, 4); return u; }

/* Reads the text of an edit control of the light dialog back into the selected light.  Controls 0x3ec intensity,
 * 0x3ed / 0x3ee inner / outer cone angle (with a slider each: 0x3fb scaled by 1000, 0x3ff / 0x400 by 100), 0x3ef..0x3f1
 * position x y z, 0x3f2 / 0x3f4 / 0x3f5 the three angles. */
void LightEd_ReadControl(int hdlg, int id)
{
    byte text[76];
    float value;
    int slider = 0;

    GetDlgItemTextA(hdlg, id, text, 0x4b);
    value = atof(text);
    if (g_pLightEdSet == 0 || g_nLightEdSelected == -1)
        return;
    switch (id) {
    case 0x3ec:
        *(float *)(g_aLightEdEntries[g_nLightEdSelected].light + 0x44) = value;
        if (g_nLightEdBusy != 0)
            return;
        SendDlgItemMessageA(hdlg, 0x3fb, 0x467, 0, (int)(value * 1000.0f) & 0xffff);
        break;
    case 0x3ed:
        rdLight_SetAngles(g_aLightEdEntries[g_nLightEdSelected].light + 0x2c, value, *(float *)(g_aLightEdEntries[g_nLightEdSelected].light + 0x54));
        if (g_nLightEdBusy != 0)
            return;
        slider = 0x3ff;
        break;
    case 0x3ee:
        rdLight_SetAngles(g_aLightEdEntries[g_nLightEdSelected].light + 0x2c, *(float *)(g_aLightEdEntries[g_nLightEdSelected].light + 0x4c), value);
        if (g_nLightEdBusy != 0)
            return;
        slider = 0x400;
        break;
    case 0x3ef: LightEd_SetLightPosComponent(g_nLightEdSelected, 0, float_bits(value)); break;
    case 0x3f0: LightEd_SetLightPosComponent(g_nLightEdSelected, 1, float_bits(value)); break;
    case 0x3f1: LightEd_SetLightPosComponent(g_nLightEdSelected, 2, float_bits(value)); break;
    case 0x3f2: LightEd_SetLightAngle(g_nLightEdSelected, 0, float_bits(value)); break;
    case 0x3f4: LightEd_SetLightAngle(g_nLightEdSelected, 1, float_bits(value)); break;
    case 0x3f5: LightEd_SetLightAngle(g_nLightEdSelected, 2, float_bits(value)); break;
    }
    if (slider)
        SendDlgItemMessageA(hdlg, slider, 0x467, 0, (int)(value * 100.0f) & 0xffff);
    if (g_nLightEdBusy == 0)
        LightEd_MoveMarkerActor();
}

/* the angle brought back into -180..360 (one wrap only); the first comparison is made on the unrounded sum */
static float wrap_angle(double sum)
{
    float a = (float)sum;

    if (sum > 360.0f)
        a = a - 360.0f;
    else if (a < -180.0)
        a = a - -360.0f;
    return a;
}

/* Keyboard hook of the light editor (installed with SetWindowsHookEx while the dialog is open): with the dialog focused
 * the arrow keys move the selected light (x with left / right, y with up / down, z with alt), the numeric keys 2 4 6 8
 * (VK_NUMPAD2 ..) turn it (the first angle with 8 / 2, the second with 6 / 4, alt: the third).  Holding a key makes the steps
 * grow.  Everything else is passed on. */
int __stdcall LightEd_KeyboardProc(int code, uint wParam, uint lParam)
{
    if (code == 0 && g_hLightEdDialog != 0 && Win_IsFocusWithin(g_hLightEdDialog) != 0 && g_nLightEdSelected != -1) {
        uint high = lParam >> 16;
        uint alt = high & 0x2000;
        uint down = (~high & 0xffff) >> 15;
        LightEdEntry *e = &g_aLightEdEntries[g_nLightEdSelected];
        byte *light = e->light;

        if (down & ((g_dwLightEdLastKey & 0xffff) == wParam)) {
            g_flLightEdMoveStep = g_flLightEdMoveStep - -0.005f;
            g_flLightEdAngleStep = g_flLightEdAngleStep - -0.5f;
        } else {
            g_flLightEdMoveStep = 0.01f;
            g_flLightEdAngleStep = 1.0f;
            g_dwLightEdLastKey = (g_dwLightEdLastKey & 0xffff0000) | (down ? wParam & 0xffff : 0);
        }
        switch (wParam) {
        case 0x12:                                  /* VK_MENU */
            return 1;
        case 0x25:                                  /* left */
            if (down)
                LightEd_SetDlgFloat((int)g_hLightEdDialog, 0x3ef, *(float *)(light + 0x20) - g_flLightEdMoveStep, 1);
            return 1;
        case 0x27:                                  /* right */
            if (down)
                LightEd_SetDlgFloat((int)g_hLightEdDialog, 0x3ef, *(float *)(light + 0x20) + g_flLightEdMoveStep, 1);
            return 1;
        case 0x26:                                  /* up */
            if (down) {
                if (alt)
                    LightEd_SetDlgFloat((int)g_hLightEdDialog, 0x3f1, *(float *)(light + 0x28) + g_flLightEdMoveStep, 1);
                else
                    LightEd_SetDlgFloat((int)g_hLightEdDialog, 0x3f0, *(float *)(light + 0x24) + g_flLightEdMoveStep, 1);
            }
            return 1;
        case 0x28:                                  /* down */
            if (down) {
                if (alt)
                    LightEd_SetDlgFloat((int)g_hLightEdDialog, 0x3f1, *(float *)(light + 0x28) - g_flLightEdMoveStep, 1);
                else
                    LightEd_SetDlgFloat((int)g_hLightEdDialog, 0x3f0, *(float *)(light + 0x24) - g_flLightEdMoveStep, 1);
            }
            return 1;
        case 0x62:                                  /* numpad 2 */
            if (down)
                LightEd_SetDlgFloat((int)g_hLightEdDialog, 0x3f2, wrap_angle((double)e->angle[0] + (double)g_flLightEdAngleStep), 1);
            return 1;
        case 0x68:                                  /* numpad 8 */
            if (down)
                LightEd_SetDlgFloat((int)g_hLightEdDialog, 0x3f2, wrap_angle((double)e->angle[0] - (double)g_flLightEdAngleStep), 1);
            return 1;
        case 0x64:                                  /* numpad 4 */
            if (down) {
                if (alt)
                    LightEd_SetDlgFloat((int)g_hLightEdDialog, 0x3f5, wrap_angle((double)e->angle[2] - (double)g_flLightEdAngleStep), 1);
                else
                    LightEd_SetDlgFloat((int)g_hLightEdDialog, 0x3f4, wrap_angle((double)e->angle[1] - (double)g_flLightEdAngleStep), 1);
            }
            return 1;
        case 0x66:                                  /* numpad 6 */
            if (down) {
                if (alt)
                    LightEd_SetDlgFloat((int)g_hLightEdDialog, 0x3f5, wrap_angle((double)e->angle[2] + (double)g_flLightEdAngleStep), 1);
                else
                    LightEd_SetDlgFloat((int)g_hLightEdDialog, 0x3f4, wrap_angle((double)e->angle[1] + (double)g_flLightEdAngleStep), 1);
            }
            return 1;
        }
    }
    return CallNextHookEx(g_hLightEdHook, code, wParam, lParam);
}

/* ===================================================================================================================
 *  LecShare_Subscribe
 * =================================================================================================================== */

extern int g_nLecShareActive __asm__("_g_dwPrivateData");     /* the override list is in use */
extern char *g_pszLecShareDefault __asm__("_UINT_008d56ec");
extern char *g_pszLecShareOverride __asm__("_UINT_008d56f0");

static void str_append(char *dst, const char *src)
{
    while (*dst)
        dst++;
    while ((*dst++ = *src++) != 0)
        ;
}

/* Looks a shared module up by name: the application's override pattern list (the pattern of the application, the one passed
 * in and the default) may replace the name by "<name>=<replacement>"; without a matching pattern the best of the
 * registered versions is taken.  Returns the entry's pointer and counts the use, or 0. */
void *LecShare_Subscribe(char *name, char *pattern)
{
    char local[100];
    byte *match = 0;
    int length;
    int *entry;

    if (g_nLecShareActive == 0)
        return 0;
    if (g_pszLecShareOverride != 0)
        match = FindMatch(name, g_pszLecShareOverride);
    if (match == 0) {
        if (pattern != 0)
            match = FindMatch(name, pattern);
        if (match == 0 && g_pszLecShareDefault != 0)
            match = FindMatch(name, g_pszLecShareDefault);
    }
    length = Str_ModuleNameLength((byte *)name);
    strncpy((uint *)local, (uint *)name, length);
    local[length] = 0;
    if (match == 0) {
        int count = GetCatalogCount(local);

        if (count == 0)
            return 0;
        strncpy((uint *)local, (uint *)GetCatalogEntry(local, count - 1), 99);
    } else {
        str_append(local, "=");
        str_append(local, (char *)match);
    }
    entry = (int *)LecShare_FindEntry((uint)local);
    if (entry == 0)
        return 0;
    entry[2]++;
    return (void *)entry[1];
}

/* ===================================================================================================================
 *  AnimPlay
 * =================================================================================================================== */

typedef struct AnimPlay {           /* 0x70 bytes */
    int timerSync;                  /* 00 timer id of the clock timer */
    int timerFrame;                 /* 04 timer id of the frame timer */
    uint flags;                     /* 08 */
    int f0c;                        /* 0c (cleared by anm_animator_Initialize) */
    int failed;                     /* 10 set when the player gave up */
    int frameDue;                   /* 14 set by the frame timer: a frame must be shown */
    int syncTicks;                  /* 18 ticks the player is ahead (counted down once per frame) */
    int targetDelay;                /* 1c normal frame delay in timer ticks (1193180 / fps) */
    int delay;                      /* 20 current frame delay, speeds up / slows down to keep sound and picture in sync */
    int f24;
    int f28, f2c, f30, f34, f38, f3c, f40, f44, f48, f4c, f50, f54, f58, f5c;
    void *stream;                   /* 60 streamer handle (the open call fills it in, the others take its value) */
    int lagMode;                    /* 64 */
    int state;                      /* 68 result of the last frame step: <0 error, 1 finished, 5 first step */
    int started;                    /* 6c */
} AnimPlay;

extern uint g_dwAnimDebugFlags __asm__("_UINT_008d6f20");   /* bit 17: report failures, bits 30, 31: draw the sync overlay */
extern int g_nAnimLipsyncOn __asm__("_g_dwAnm_audio_halted");
extern int g_nAnimDelayTotal __asm__("_g_dwRenderHandler_totalTime");     /* sum of the frame delays */

#define ANIM_FILE s_C__grimsrc_libs_lecsmush_insane__004f1608     /* source file name given to the allocator */
#define ANIM_MSG(msg) SVC_CALL(g_pAnm_virtherc_services, 3, void, (const char *, ...))(msg)
#define ANIM_REPORT() (g_pAnm_virtherc_services != 0 && (g_dwAnimDebugFlags & 0x20000) != 0)

/* Creates the player: allocates the AnimPlay object, opens the streamer, sets the frame delay from the frame rate
 * (1193180 / fps, the ticks of the 1.19 MHz clock), resets the state, opens the file and starts the two timers.  Returns
 * 0, or -1 with *out = 0 (and everything released) when a step fails. */
int anm_Start(void **pout, char *name, int fps, int streamArg1, int streamArg2, uint flags)
{
    AnimPlay **out = (AnimPlay **)pout;
    AnimPlay *p = SVC_CALL(g_pAnm_memory_services, 0, AnimPlay *, (int, const char *, int))(0x70, ANIM_FILE, 0x140);
    int delay;

    if (p == 0)
        goto fail;
    if (SVC_CALL(g_pAnm_streamer_services, 0, int, (void *, int, int))(&p->stream, streamArg1, streamArg2) != 0) {
        if (ANIM_REPORT())
            ANIM_MSG(s_AnimPlay_Module__Cannot_allocate_004f1520);
        goto freeObject;
    }
    delay = 0x1234dc / fps;
    p->flags = flags;
    p->syncTicks = 0;
    p->frameDue = 0;
    p->lagMode = 0;
    p->started = 0;
    p->state = 0;
    p->targetDelay = delay;
    p->delay = delay;
    *out = p;
    if (anm_animator_Initialize(p) != 0) {
        ANIM_MSG(s_AnimPlay_Module__Cannot_init_Ani_004f1554);
        goto freeStream;
    }
    if (anm_animator_NewAnim(*out, name, flags, -1, -1, 0) != 0) {
        SVC_CALL(g_pAnm_virtherc_services, 3, void, (const char *, ...))(s_AnimPlay_Module__Cannot_open_fil_004f1584, name);
        Mem_DumpLog();
        goto freeStream;
    }
    p->timerSync = SVC_CALL(g_pAnimPlay_timer_services, 0, int, (void *, int, int, void *))(frame_Timer, 1, 2, p);
    if (p->timerSync == 0) {
        if (ANIM_REPORT())
            ANIM_MSG(s_AnimPlay_Module__Cannot_allocate_004f15ac);
        Mem_DumpLog();
        goto freeStream;
    }
    p->timerFrame = SVC_CALL(g_pAnimPlay_timer_services, 0, int, (void *, int, int, void *))(sync_Timer, p->targetDelay, 8, p);
    if (p->timerFrame != 0) {
        p->failed = 0;
        return 0;
    }
    if (ANIM_REPORT())
        ANIM_MSG(s_AnimPlay_Module__Cannot_allocate_004f15d8);
    SVC_CALL(g_pAnimPlay_timer_services, 1, void, (int))(p->timerSync);
    Mem_DumpLog();
freeStream:
    SVC_CALL(g_pAnm_streamer_services, 1, void, (void *))(&p->stream);
freeObject:
    SVC_CALL(g_pAnm_memory_services, 1, void, (void *, const char *, int))(p, ANIM_FILE, 0x175);
fail:
    *out = 0;
    return -1;
}

/* Stops both timers, closes the file and the streamer and frees the player. */
void anm_Stop(void **ppIn)
{
    AnimPlay **pp = (AnimPlay **)ppIn;
    AnimPlay *p = *pp;

    SVC_CALL(g_pAnimPlay_timer_services, 1, void, (int))(p->timerSync);
    SVC_CALL(g_pAnimPlay_timer_services, 1, void, (int))(p->timerFrame);
    if (g_nAnimLipsyncOn != 0 && g_pAnimPlay_sound_services != 0)
        SVC_CALL(g_pAnimPlay_sound_services, 3, void, (void))();
    Mem_DumpLog();
    SVC_CALL(g_pAnm_streamer_services, 1, void, (void *))(&p->stream);
    if (*pp != 0)
        SVC_CALL(g_pAnm_memory_services, 1, void, (void *, const char *, int))(*pp, ANIM_FILE, 0x1d4);
    *pp = 0;
    SVC_CALL(g_pAnm_animframe_services, 0, void, (void))();
}

/* One step of the player, called from the main loop: shows the next frame when the frame timer has marked one as due
 * (state 5 is the first step: it just starts the frame decoder).  The sound position is compared with the frame counter
 * (66.67 ms per frame) and the frame delay is sped up or slowed down by 1/8 or 1/16 of the nominal delay, within 3/4 .. 4/3
 * of it, to keep the picture in sync.  Returns the state: <0 error, 1 finished, 6 nothing to do. */
int anm_Render(void *pIn, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10)
{
    AnimPlay *p = (AnimPlay *)pIn;
    int lead, buffered, base, step;
    uint flags;

    if (p->state == 5) {
        p->state = anm_animator_Render((int)p, a2, a3, a4, a5, a6, a7, a8, p->flags, a9, a10);
        if (p->state < 0) {
            p->failed = 1;
            return p->state;
        }
        return p->state;
    }
    if (p->frameDue == 0)
        return 6;
    buffered = SVC_CALL(g_pAnm_streamer_services, 7, int, (void *))(p->stream);
    if (p->started == 0) {
        g_nBretsFrameCount = 0;
        g_nAnimDelayTotal = 0;
    }
    g_nAnimDelayTotal += p->delay;
    lead = (int)(((double)sou_engine_QueryTime(0) - (double)g_nBretsFrameCount * 66.66666666667) * 0.0149999999999925);
    p->syncTicks--;
    p->frameDue = 0;
    base = p->targetDelay;
    if (lead < 1 && p->state != 2 && p->state != 3 && p->state != 4) {
        if (lead < 0) {             /* behind: shorten the delay */
            if (p->delay < base)
                p->delay = base;
            step = lead == -1 ? base / 16 : base / 8;
            p->delay += step;
            if (p->delay > base * 4 / 3)
                p->delay = base * 4 / 3;
        }
    } else {                        /* ahead: lengthen the delay */
        if (p->delay > base)
            p->delay = base;
        step = lead == 1 ? base / 16 : base / 8;
        p->delay = p->delay - step;
        if (p->delay < 1)
            p->delay = 1;
        if (p->delay < base * 3 / 4)
            p->delay = base * 3 / 4;
    }
    SVC_CALL(g_pAnimPlay_timer_services, 4, void, (int, int))(p->timerSync, p->delay);
    if (lead > 2)
        p->lagMode = 1;
    else if (lead <= 0)
        p->lagMode = 0;
    flags = p->flags;
    if (p->lagMode != 0 && (flags & 2) == 0)
        flags |= 0x8000;
    p->state = anm_animator_Render((int)p, a2, a3, a4, a5, a6, a7, a8, flags, a9, a10);
    if (g_pAnm_virtherc_services != 0 && (g_dwAnimDebugFlags & 0xc0000000) != 0) {
        void **d = (void **)g_pAnm_virtherc_services;
        int v = SVC_CALL(d, 7, int, (int, int))(4, 0x20);

        SVC_CALL(d, 5, void, (int, int, int))(0, 10, v);
        SVC_CALL(d, 0, void, (int, int))(0, 10);
        SVC_CALL(d, 3, void, (const char *, ...))(s_Buffer___ld___004f1694, buffered);
        SVC_CALL(d, 3, void, (const char *, ...))(s_Frame_Delay___ld___ld_target__004f1670, p->delay, p->targetDelay);
        SVC_CALL(d, 3, void, (const char *, ...))(s_Sync_Ticks___ld_004f1658, p->syncTicks);
        SVC_CALL(d, 3, void, (const char *, ...))(s_State___d_004f1640, p->state);
    }
    if (p->state < 0)
        p->failed = 1;
    if (p->state == 1) {
        p->started = 1;
        return 1;
    }
    return p->state;
}

/* Puts the decoder state of a player back to "no file open" (the object is zeroed in parts; the streamer is reset). */
int anm_animator_Initialize(void *pIn)
{
    AnimPlay *p = (AnimPlay *)pIn;
    SVC_CALL(g_pAnm_streamer_services, 6, void, (void *))(p->stream);
    p->f0c = 0;
    p->f28 = 0;
    p->f34 = 0x6e756c6c;            /* "null" */
    p->f2c = 1;
    p->f38 = 0;
    p->f54 = 0;
    p->f58 = 0;
    p->f40 = 0;
    p->f44 = 0;
    return 0;
}

/* Opens the file through the streamer and hands the decoder its buffers; 0 or -1. */
int anm_animator_NewAnim(void *pIn, char *name, uint flags, int a4, int a5, int a6)
{
    AnimPlay *p = (AnimPlay *)pIn;

    p->f40 = a6;
    p->f3c = flags;
    if (SVC_CALL(g_pAnm_streamer_services, 2, int, (void *, char *, int))(p->stream, name, 8) != 0)
        return -1;
    p->f38 = 1;
    FUN_004c3d90((int)p, a4, a5);
    return 0;
}

/* ===================================================================================================================
 *  zlib glue: gzio.c with its file access routed through the file service, StdFile helpers
 * =================================================================================================================== */


typedef struct GzStream {           /* gz_stream of zlib 1.1.3 gzio.c, 100 bytes (z_stream first) */
    byte *next_in; uint avail_in; uint total_in;
    byte *next_out; uint avail_out; uint total_out;
    char *msg; void *state; void *zalloc; void *zfree; void *opaque;
    int data_type; uint adler; uint reserved;
    int z_err;                      /* 38 */
    int z_eof;                      /* 3c */
    void *file;                     /* 40 */
    byte *inbuf;                    /* 44 */
    byte *outbuf;                   /* 48 */
    uint crc;                       /* 4c */
    char *errmsg;                   /* 50 */
    char *path;                     /* 54 */
    int transparent;                /* 58 */
    char mode;                      /* 5c */
    int startpos;                   /* 60 */
} GzStream;

/* Writes a 32 bit value in little endian order (zlib's putLong). */
void gz_putLong(void *file, uint x)
{
    int n;

    for (n = 0; n < 4; n++) {
        byte c = (byte)x;

        SVC_CALL(g_pZf_filio_services, 3, void, (void *, byte *, int))(file, &c, 1);
        x >>= 8;
    }
}

/* Closes a Zfile: the plain file through the file service, or the gzip stream; then frees the object. */
void Zfile_fle_Close(int *z)
{
    if (z[0] != 0) {
        if (z[1] == 0)
            SVC_CALL(g_pZf_filio_services, 1, void, (int))(z[0]);
        else
            gzclose(z[0]);
    }
    if (z != 0)
        SVC_CALL(g_pZfile_memory_services, 1, void, (int *, const char *, int))(z, s_C__grimsrc_libs_lecsmush_insane__004f1df4, 0x11b);
}

static int strlen_(const char *s)
{
    int n = 0;

    while (s[n])
        n++;
    return n;
}

static void str_copy(char *dst, const char *src)
{
    while ((*dst++ = *src++) != 0)
        ;
}

/* gz_open of zlib 1.1.3 gzio.c: opens a gzip stream for reading ("r") or writing ("w" / "a" and a level digit, "f" filtered,
 * "h" Huffman only); the file is opened through the file service (or from a descriptor).  This version refuses files that
 * are not gzip (transparent mode). */
void *gz_open(char *path, char *mode, int fd)
{
    int level = -1, strategy = 0, err;
    char *p = mode;
    char fmode[80];
    char *m = fmode;
    GzStream *s;
    char c;

    if (path == 0 || mode == 0)
        return 0;
    s = (GzStream *)malloc(100);
    if (s == 0)
        return 0;
    s->zalloc = 0;
    s->zfree = 0;
    s->opaque = 0;
    s->inbuf = 0;
    s->next_in = 0;
    s->outbuf = 0;
    s->next_out = 0;
    s->avail_out = 0;
    s->avail_in = 0;
    s->file = 0;
    s->z_err = 0;
    s->z_eof = 0;
    s->crc = crc32(0, 0, 0);
    s->errmsg = 0;
    s->transparent = 0;
    s->path = (char *)malloc(strlen_(path) + 1);
    if (s->path == 0)
        goto destroy;
    str_copy(s->path, path);
    s->mode = 0;
    do {
        c = *p;
        if (c == 'r')
            s->mode = 'r';
        if (c == 'w' || c == 'a')
            s->mode = 'w';
        if (c >= '0' && c <= '9')
            level = c - '0';
        else if (c == 'f')
            strategy = 1;
        else if (c == 'h')
            strategy = 2;
        else
            *m++ = c;
        p++;
    } while (c != 0 && m != fmode + sizeof(fmode));
    if (s->mode == 0)
        goto destroy;
    if (s->mode == 'w') {
        err = deflateInit2_((int)s, level, 8, -15, 8, strategy, s_1_1_3_004f1a20, 0x38);
        s->outbuf = (byte *)malloc(0x4000);
        s->next_out = s->outbuf;
        if (err != 0 || s->outbuf == 0)
            goto destroy;
    } else {
        s->inbuf = (byte *)malloc(0x4000);
        s->next_in = s->inbuf;
        err = inflateInit2_((int)s, -15, s_1_1_3_004f1a20, 0x38);
        if (err != 0 || s->inbuf == 0)
            goto destroy;
    }
    s->avail_out = 0x4000;
    *(int *)_errno() = 0;
    if (fd < 0)
        s->file = SVC_CALL(g_pZf_filio_services, 0, void *, (char *, char *))(path, fmode);
    else
        s->file = (void *)_fdopen(fd, fmode);
    if (s->file == 0)
        goto destroy;
    if (s->mode == 'w') {
        char header[16];

        sprintf(header, s__c_c_c_c_c_c_c_c_c_c_004f1a08, UINT_004f1a00, UINT_004f1a04, 8, 0, 0, 0, 0, 0, 0, 0xb);
        SVC_CALL(g_pZf_filio_services, 3, void, (void *, char *, int))(s->file, header, 10);
        s->startpos = 10;
        return s;
    }
    gz_check_header((int *)s);
    if (s->transparent == 1)
        goto destroy;
    s->startpos = SVC_CALL(g_pZf_filio_services, 4, int, (void *))(s->file) - s->avail_in;
    return s;
destroy:
    gz_destroy((int)s);
    return 0;
}

/* Position in a StdFile. */
int StdFile_fle_Tell(void *file)
{
    return SVC_CALL(g_pStdFile_filio_services, 4, int, (void *))(file);
}

/* True when the position of a StdFile is at (or past) its size. */
int fle_Eof(void *file)
{
    int size = fle_Size(file);

    return StdFile_fle_Tell(file) >= size;
}

#endif /* GRIM_EXE */
