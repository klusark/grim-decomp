/* The DirectDraw display on a machine that has no 16-bit display modes (Windows 8 and later list only 32-bit ones, and
 * SetDisplayMode(w, h, 16) answers E_NOTIMPL). The original's DirectDraw and Direct3D renderers draw in 16 bits
 * (5:6:5): a 32-bit mode gives them a primary surface they do not handle (the dirty-rectangle blits of a 16-bit clean
 * buffer ran off its end). When the display lists no 16-bit mode, these three functions emulate one:
 *
 *   DDraw_Create          after the original's enumeration, each 32-bit mode is offered once more as a 16-bit 5:6:5
 *                         mode, through the original callback (DDraw_EnumModesCallback);
 *   DDraw_CreateSurfaces  for such a mode the display is set to the same size at 32 bits, and the game's primary (and
 *                         back buffer) are 16-bit off-screen surfaces in video memory that a Direct3D HAL device can
 *                         render to; the real primary surface is kept apart;
 *   DDraw_Flip            converts the game's back buffer (its primary when it has no back buffer) to the real primary.
 *
 * GRIM_3D=1 (Display_InitFromConfig: the Direct3D renderer) draws the same way in the game's window: DirectDraw's
 * cooperative level stays DDSCL_NORMAL, the display mode is never changed, there is no real primary surface, and each
 * flip copies the picture into the window with GDI (SetDIBitsToDevice). GRIM_3D=2 is fullscreen.
 *
 * The game's surfaces are not swapped on a flip (the Direct3D device stays bound to the back buffer): the back buffer
 * keeps the frame just shown instead of the one before, which the dirty-rectangle repair handles (it repaints a superset
 * of what changed). Everything else (the modes, the cooperative levels, the surfaces' formats as the game sees them) is
 * the original's. With 16-bit modes on the display and without GRIM_3D=1 the functions do what the original does.
 * (stdDisplay_VBufferNew gives its DirectDraw surfaces an explicit 8- or 16-bit format while such a mode is open:
 * without one a surface gets the real display's 32 bits.)
 * tools/build_src.py puts the decompiled text of every function defined here under `#if 0`. */
#include "ghidra_types.h"

#ifdef GRIM_EXE
#include "globals.h"
#include "functions.h"

/* COM method call through the vtable at byte offset `off` */
#define COMX(obj, off, ...) ((int (__stdcall *)())(*(void ***)(obj))[(off) / 4])((obj), ##__VA_ARGS__)
/* IDirectDraw */
#define DD_CREATEPALETTE      0x14
#define DD_CREATESURFACE      0x18
#define DD_ENUMDISPLAYMODES   0x20
#define DD_SETCOOPERATIVELEVEL 0x50
#define DD_SETDISPLAYMODE     0x54
/* IDirectDrawSurface */
#define DDS_RELEASE           0x08
#define DDS_BLT               0x14
#define DDS_FLIP              0x2c
#define DDS_GETATTACHEDSURFACE 0x30
#define DDS_GETSURFACEDESC    0x58
#define DDS_LOCK              0x64
#define DDS_RESTORE           0x6c
#define DDS_SETPALETTE        0x7c
#define DDS_UNLOCK            0x80
#define DDERR_SURFACELOST     (-0x7789fe3e)
#define DDERR_WASSTILLDRAWING (-0x7789fde4)

/* DDSURFACEDESC offsets the enumeration callback reads */
#define SD_FLAGS   0x04
#define SD_HEIGHT  0x08
#define SD_WIDTH   0x0c
#define SD_PITCH   0x10
#define SD_PF      0x48     /* DDPIXELFORMAT: size, flags, fourcc, bit count, r / g / b / a masks */

static int g_bDDraw16Emu;            /* the display has no 16-bit mode: the 16-bit modes are emulated */
static int g_bDDraw16Window;         /* GRIM_3D=1: the DirectDraw display in the game's window (GRIM_DDraw16SetWindowed) */
static int g_bDDraw16Open;           /* an emulated or windowed 16-bit mode is open */
static void *g_pDDraw16RealPrimary;  /* while an emulated fullscreen mode is open: the real (32-bit) primary surface */
static void *g_pDDraw16Spare;        /* the third 16-bit surface DDraw_Flip swaps the front and back buffers through */

/* 1 while an emulated 16-bit mode is open: stdDisplay_VBufferNew gives its DirectDraw surfaces an explicit 5:6:5 format */
int GRIM_DDraw16Active(void)
{
    return g_bDDraw16Open;
}

/* GRIM_3D=1: the DirectDraw device's modes are drawn in the game's window: the cooperative level stays DDSCL_NORMAL, the
 * display mode is not changed, the game's surfaces are 16-bit off-screen surfaces and every flip copies the picture into
 * the window with GDI (Display_InitFromConfig selects the Direct3D renderer). GRIM_3D=2: fullscreen, as the original. */
extern unsigned long __attribute__((stdcall)) GRIM_GetEnv16(const char *, char *, unsigned long)
    __asm__("_GetEnvironmentVariableA@12");

static void ddraw16_read_env(void)
{
    char e[4] = "";
    GRIM_GetEnv16("GRIM_3D", e, sizeof e);
    g_bDDraw16Window = e[0] == '1';
}

/* ==== DDraw_Create (0x004760d0) ====
 * Creates the DirectDraw object of the selected device and enumerates its display modes (the 320 x 200 Mode X ones
 * with DDSCL_ALLOWMODEX, then the others) into the mode table (UINT_00901760, 0x54 bytes each). Then, when none of the
 * modes is 16 bits, every 32-bit mode is added again as 16-bit 5:6:5. */
int __cdecl DDraw_Create(uint device)
{
    byte *guid = g_pDisplayDevice->nPrimary == 0 ? g_pDisplayDevice->aGuid : (byte *)0;
    uint n, i, have16 = 0;

    g_bDDraw16Emu = 0;
    ddraw16_read_env();
    if (DirectDrawCreate((int)guid, (unsigned)(uintptr_t)&g_pDirectDraw, 0) != 0)
        return 0;
    g_dwVideoModeCount = 0;
    /* (windowed: DDSCL_NORMAL throughout; the Mode X modes are not enumerated) */
    if (COMX(g_pDirectDraw, DD_SETCOOPERATIVELEVEL, device, g_bDDraw16Window ? 8 : 0x51) != 0)
        return 0;
    if (!g_bDDraw16Window && COMX(g_pDirectDraw, DD_ENUMDISPLAYMODES, 0, 0, 0, DDraw_EnumModesCallback320) != 0)
        return 0;
    if (COMX(g_pDirectDraw, DD_SETCOOPERATIVELEVEL, device, g_bDDraw16Window ? 8 : 0x11) != 0)
        return 0;
    if (COMX(g_pDirectDraw, DD_ENUMDISPLAYMODES, 0, 0, 0, DDraw_EnumModesCallback) != 0)
        return 0;
    n = g_dwVideoModeCount;
    for (i = 0; i < n; i++)
        if (((VideoMode *)&UINT_00901760)[i].format.colorFormat.nBpp == 16)
            have16 = 1;
    if (g_bDDraw16Window)
        have16 = 0;                                         /* (the desktop's depth decides nothing in a window) */
    if (!have16) {
        for (i = 0; i < n; i++) {
            VideoMode *m = &((VideoMode *)&UINT_00901760)[i];
            uint sd[0x6c / 4];
            if (m->format.colorFormat.nBpp != 32)
                continue;
            memset(sd, 0, sizeof sd);
            sd[0] = 0x6c;
            sd[SD_FLAGS / 4] = 0x100e;                      /* DDSD_HEIGHT | WIDTH | PITCH | PIXELFORMAT */
            sd[SD_HEIGHT / 4] = m->format.nHeight;
            sd[SD_WIDTH / 4] = m->format.nWidth;
            sd[SD_PITCH / 4] = m->format.nWidth * 2;
            sd[SD_PF / 4] = 0x20;
            sd[SD_PF / 4 + 1] = 0x40;                       /* DDPF_RGB */
            sd[SD_PF / 4 + 3] = 16;
            sd[SD_PF / 4 + 4] = 0xf800;
            sd[SD_PF / 4 + 5] = 0x07e0;
            sd[SD_PF / 4 + 6] = 0x001f;
            if (((int (__stdcall *)(void *, void *))DDraw_EnumModesCallback)(sd, 0) == 0)
                break;                                      /* (the table is full) */
            g_bDDraw16Emu = 1;
        }
    }
    return COMX(g_pDirectDraw, DD_SETCOOPERATIVELEVEL, device, 8) == 0;
}

/* a 16-bit 5:6:5 off-screen surface in video memory for a Direct3D HAL device, into the record `rec` */
static int ddraw16_make_surface(DDrawSurfaceRec *rec, uint width, uint height)
{
    uint *d = (uint *)&rec->desc;

    memset(d, 0, 0x6c);
    d[0] = 0x6c;
    d[SD_FLAGS / 4] = 0x1007;                                /* DDSD_CAPS | HEIGHT | WIDTH | PIXELFORMAT */
    d[SD_HEIGHT / 4] = height;
    d[SD_WIDTH / 4] = width;
    d[SD_PF / 4] = 0x20;
    d[SD_PF / 4 + 1] = 0x40;
    d[SD_PF / 4 + 3] = 16;
    d[SD_PF / 4 + 4] = 0xf800;
    d[SD_PF / 4 + 5] = 0x07e0;
    d[SD_PF / 4 + 6] = 0x001f;
    rec->desc.dwCaps = 0x6040;                               /* OFFSCREENPLAIN | 3DDEVICE | VIDEOMEMORY */
    rec->pPalette = (void *)0;
    if (COMX(g_pDirectDraw, DD_CREATESURFACE, &rec->desc, rec, 0) != 0)
        return 0;
    return COMX(rec->pSurface, DDS_GETSURFACEDESC, &rec->desc) == 0;
}

/* ==== DDraw_CreateSurfaces (0x004767d0) ====
 * Sets the cooperative level (exclusive fullscreen, with Mode X when the mode is fullscreen and Mode X is allowed) and
 * the display mode, and creates the primary surface (with one back buffer when UINT_00803f9c is set: a flipping chain)
 * into the front buffer's VBuffer (g_dwStdDisplay_frontBuffer, its DDrawSurfaceRec at UINT_009016e4) and the back
 * buffer's (g_dwStdDisplay_backBuffer, PTR_00905644), and for an 8-bit mode the palette. Without a back buffer the back
 * buffer's VBuffer is a copy of the front one. An emulated 16-bit mode (DDraw_Create) sets the display to 32 bits and
 * gives the game 16-bit off-screen surfaces instead (see the top of the file). */
undefined4 __cdecl DDraw_CreateSurfaces(undefined4 hwnd, VideoMode *mode, byte *palette)
{
    VBufferFormat *src = &mode->format;
    byte entries[0x400];
    uint coop = 0x11, bytes;
    int emu = (g_bDDraw16Emu || g_bDDraw16Window) && mode->format.colorFormat.nBpp == 16;
    int i;

    if (UINT_00803f9c != 0 && mode->nFullscreen != 0)
        coop = 0x51;
    if (g_bDDraw16Window)
        coop = 8;                                                 /* DDSCL_NORMAL */
    if (COMX(g_pDirectDraw, DD_SETCOOPERATIVELEVEL, hwnd, coop) != 0)
        return 0;
    UINT_00803fb0 = coop;
    if (!g_bDDraw16Window &&
        COMX(g_pDirectDraw, DD_SETDISPLAYMODE, src->nWidth, src->nHeight, emu ? 32 : src->colorFormat.nBpp) != 0)
        return 0;
    bytes = (uint)src->colorFormat.nBpp >> 3;
    g_dwStdDisplay_frontBuffer = 1;
    _DAT_00901684 = 0;
    _DAT_00901688 = 0;
    Mem_Copy(&DAT_0090168c, src, 0x4c);
    _DAT_009016d8 = palette;
    UINT_009016dc = 0;
    g_pDDrawPrimary = (DDrawSurfaceRec *)&UINT_009016e4;
    if (emu) {
        uint *d = (uint *)&g_pDDrawPrimary->desc;
        g_pDDraw16RealPrimary = 0;
        if (!g_bDDraw16Window) {
            /* the real primary surface: simple, 32 bits (windowed: none, the picture goes to the window through GDI) */
            memset(d, 0, 0x6c);
            d[0] = 0x6c;
            d[SD_FLAGS / 4] = 1;
            g_pDDrawPrimary->desc.dwCaps = 0x200;
            if (COMX(g_pDirectDraw, DD_CREATESURFACE, &g_pDDrawPrimary->desc, &g_pDDraw16RealPrimary, 0) != 0)
                return 0;
        }
        if (!ddraw16_make_surface(g_pDDrawPrimary, src->nWidth, src->nHeight))
            return 0;
        if (UINT_00803f9c != 0) {
            /* the spare surface of the flip (DDraw_Flip swaps the contents of the front and back buffers through it) */
            DDrawSurfaceRec spare;
            if (!ddraw16_make_surface(&spare, src->nWidth, src->nHeight))
                return 0;
            g_pDDraw16Spare = spare.pSurface;
        }
        g_bDDraw16Open = 1;
        g_dwStdDisplay_numDrawBuffers = UINT_00803f9c != 0 ? 2 : 1;
    } else {
        memset(&UINT_009016ec, 0, 0x1b * 4);
        g_pDDrawPrimary->desc.dwWidth = src->nWidth;
        g_pDDrawPrimary->desc.dwHeight = src->nHeight;
        g_pDDrawPrimary->desc.dwSize = 0x6c;
        g_pDDrawPrimary->pPalette = (void *)0;
        if (UINT_00803f9c == 0) {
            g_pDDrawPrimary->desc.dwFlags = 1;
            g_pDDrawPrimary->desc.dwCaps = 0x2200;
        } else {
            g_pDDrawPrimary->desc.dwBackBufferCount = 1;
            g_pDDrawPrimary->desc.dwFlags = 0x21;
            g_pDDrawPrimary->desc.dwCaps = 0x2218;
        }
        if (COMX(g_pDirectDraw, DD_CREATESURFACE, &g_pDDrawPrimary->desc, g_pDDrawPrimary, 0) != 0)
            return 0;
        if (COMX(g_pDDrawPrimary->pSurface, DDS_GETSURFACEDESC, &g_pDDrawPrimary->desc) != 0)
            return 0;
        g_dwStdDisplay_numDrawBuffers = g_pDDrawPrimary->desc.dwBackBufferCount + 1;
    }
    UINT_00901698 = g_pDDrawPrimary->desc.nPitch;
    _DAT_0090169c = UINT_00901698 / bytes;
    if ((g_pDDrawPrimary->desc.dwCaps & 0x4000) != 0)
        _DAT_00901688 = 1;
    if (UINT_00803f9c != 0) {
        g_dwStdDisplay_backBuffer = 1;
        _DAT_009055e4 = 0;
        _DAT_009055e8 = 0;
        Mem_Copy(&UINT_009055ec, src, 0x4c);
        _DAT_00905638 = palette;
        UINT_0090563c = 0;
        g_pDDrawBack = (DDrawSurfaceRec *)&PTR_00905644;
        if (emu) {
            if (!ddraw16_make_surface(g_pDDrawBack, src->nWidth, src->nHeight))
                return 0;
        } else {
            memset(&UINT_0090564c, 0, 0x1b * 4);
            g_pDDrawBack->desc.dwWidth = src->nWidth;
            g_pDDrawBack->desc.dwHeight = src->nHeight;
            g_pDDrawBack->desc.dwSize = 0x6c;
            g_pDDrawBack->desc.dwFlags = 0x21;
            g_pDDrawBack->desc.dwCaps = 4;
            g_pDDrawBack->desc.dwBackBufferCount = 1;
            if (COMX(g_pDDrawPrimary->pSurface, DDS_GETATTACHEDSURFACE, &g_pDDrawBack->desc.dwCaps, g_pDDrawBack) != 0)
                return 0;
            if (COMX(g_pDDrawBack->pSurface, DDS_GETSURFACEDESC, &g_pDDrawBack->desc) != 0)
                return 0;
        }
        if ((g_pDDrawBack->desc.dwCaps & 0x4000) != 0)
            _DAT_009055e8 = 1;
        UINT_009055f8 = g_pDDrawBack->desc.nPitch;
        _DAT_009055fc = UINT_009055f8 / bytes;
        g_pDDrawBack->pPalette = (void *)0;
    }
    if (mode->format.colorFormat.nColorMode == 0) {
        int dc = GetDC(0);
        GetSystemPaletteEntries(dc, 0, 0x100, (int)entries);
        ReleaseDC(0, dc);
        for (i = 0; i < 0x100; i++) {
            entries[i * 4] = palette[i * 3];
            entries[i * 4 + 1] = palette[i * 3 + 1];
            entries[i * 4 + 2] = palette[i * 3 + 2];
            entries[i * 4 + 3] = 1;
        }
        if (COMX(g_pDirectDraw, DD_CREATEPALETTE, 0x4c, entries, &g_pDDrawPrimary->pPalette, 0) != 0)
            return 0;
        if (COMX(g_pDDrawPrimary->pSurface, DDS_SETPALETTE, g_pDDrawPrimary->pPalette) != 0)
            return 0;
        if (UINT_00803f9c == 0)
            goto single;
        if (COMX(g_pDDrawBack->pSurface, DDS_SETPALETTE, g_pDDrawPrimary->pPalette) != 0)
            return 0;
    }
    if (UINT_00803f9c != 0)
        return 1;
single:
    Mem_Copy(&g_dwStdDisplay_backBuffer, &g_dwStdDisplay_frontBuffer, 0xd8);
    return 1;
}

/* lock a surface for reading or writing, restoring it when it was lost; the pixels and the pitch, or 0 */
static byte *ddraw16_lock(void *surface, uint *desc)
{
    int r, tries;

    memset(desc, 0, 0x6c);
    desc[0] = 0x6c;
    for (tries = 0; tries < 4; tries++) {
        r = COMX(surface, DDS_LOCK, 0, desc, 1, 0);          /* DDLOCK_WAIT */
        if (r == 0)
            return (byte *)desc[0x24 / 4];
        if (r != DDERR_SURFACELOST || COMX(surface, DDS_RESTORE) != 0)
            return 0;
    }
    return 0;
}

/* 5:6:5 to X8R8G8B8, one row */
static void ddraw16_row(uint *dp, const unsigned short *sp, uint w)
{
    uint x;

    for (x = 0; x < w; x++) {
        uint p = sp[x];
        uint r = (p >> 11) & 0x1f, g = (p >> 5) & 0x3f, b = p & 0x1f;
        dp[x] = ((r << 3 | r >> 2) << 16) | ((g << 2 | g >> 4) << 8) | (b << 3 | b >> 2);
    }
}

extern int __attribute__((stdcall)) GRIM_SetDIBitsToDevice(int, int, int, uint, uint, int, int, uint, uint,
                                                          const void *, const void *, uint)
    __asm__("_SetDIBitsToDevice@48");
extern void *GRIM_host_malloc16(unsigned) __asm__("_malloc");

/* the game's 16-bit picture onto the real primary surface, or (windowed) into the game's window */
static uint ddraw16_present(void)
{
    DDrawSurfaceRec *src = UINT_00803f9c != 0 ? g_pDDrawBack : g_pDDrawPrimary;
    uint sd[0x6c / 4], dd[0x6c / 4];
    byte *s, *d;
    uint w, h, y, ok = 0;

    if (!g_bDDraw16Open || (s = ddraw16_lock(src->pSurface, sd)) == 0)
        return 0;
    w = sd[SD_WIDTH / 4];
    h = sd[SD_HEIGHT / 4];
    if (g_bDDraw16Window) {
        static uint *pix;
        static uint pixSize;
        uint bmi[10];                                           /* BITMAPINFOHEADER, top-down 32-bit */
        int dc;
        if (pixSize < w * h) {
            pix = (uint *)GRIM_host_malloc16(w * h * 4);
            pixSize = pix ? w * h : 0;
        }
        if (pix != 0) {
            for (y = 0; y < h; y++)
                ddraw16_row(pix + y * w, (const unsigned short *)(s + y * (int)sd[SD_PITCH / 4]), w);
            memset(bmi, 0, sizeof bmi);
            bmi[0] = 40;
            bmi[1] = w;
            bmi[2] = (uint)-(int)h;
            bmi[3] = 1 | (32 << 16);                            /* planes, bits per pixel */
            dc = GetDC((int)Win_GetMainHwnd());
            GRIM_SetDIBitsToDevice(dc, 0, 0, w, h, 0, 0, 0, h, pix, bmi, 0);
            ReleaseDC((int)Win_GetMainHwnd(), dc);
            ok = 1;
        }
    } else if ((d = ddraw16_lock(g_pDDraw16RealPrimary, dd)) != 0) {
        if (w > dd[SD_WIDTH / 4])
            w = dd[SD_WIDTH / 4];
        if (h > dd[SD_HEIGHT / 4])
            h = dd[SD_HEIGHT / 4];
        for (y = 0; y < h; y++)
            ddraw16_row((uint *)(d + y * (int)dd[SD_PITCH / 4]), (const unsigned short *)(s + y * (int)sd[SD_PITCH / 4]),
                        w);
        COMX(g_pDDraw16RealPrimary, DDS_UNLOCK, 0);
        ok = 1;
    }
    COMX(src->pSurface, DDS_UNLOCK, 0);
    return ok;
}

/* ==== DDraw_Flip (0x00476c90) ====
 * Flips the primary chain (restoring it when it was lost, retrying while the hardware is still drawing); returns 1
 * when it flipped. An emulated 16-bit mode shows the back buffer (ddraw16_present) and then swaps the contents of the
 * front and back buffers as a flip does (the surfaces themselves stay: the Direct3D device is bound to the back buffer):
 * the game's next frame starts from the frame before the one just shown, which is what its dirty-rectangle repair and
 * a picture of the back buffer (sputRender_SaveDrawBuffer) expect. */
uint __cdecl DDraw_Flip(void)
{
    int r;

    if (g_bDDraw16Open) {
        uint ok = ddraw16_present();
        if (g_pDDraw16Spare != 0) {
            COMX(g_pDDraw16Spare, DDS_BLT, 0, g_pDDrawBack->pSurface, 0, 0x1000000, 0);           /* DDBLT_WAIT */
            COMX(g_pDDrawBack->pSurface, DDS_BLT, 0, g_pDDrawPrimary->pSurface, 0, 0x1000000, 0);
            COMX(g_pDDrawPrimary->pSurface, DDS_BLT, 0, g_pDDraw16Spare, 0, 0x1000000, 0);
        }
        return ok;
    }
    do {
        r = COMX(g_pDDrawPrimary->pSurface, DDS_FLIP, 0, 0);
        if (r == 0)
            return 1;
        if (r == DDERR_SURFACELOST) {
            if (COMX(g_pDDrawPrimary->pSurface, DDS_RESTORE) != 0)
                return 0;
            r = 0;
        }
    } while (r == DDERR_WASSTILLDRAWING);
    return 0;
}

/* ==== DDraw_ReleaseSurfaces (0x00476bc0) ====
 * Releases the back buffer (when there is one: its VBuffer's record pointer is cleared first) and the front buffer;
 * and the real primary surface of an emulated 16-bit mode. */
void __cdecl DDraw_ReleaseSurfaces(void)
{
    if (UINT_00803f9c != 0) {
        UINT_00905648 = 0;
        Surface_Release((VBuffer *)&g_dwStdDisplay_backBuffer);
    }
    Surface_Release((VBuffer *)&g_dwStdDisplay_frontBuffer);
    if (g_pDDraw16RealPrimary != 0) {
        COMX(g_pDDraw16RealPrimary, DDS_RELEASE);
        g_pDDraw16RealPrimary = 0;
    }
    if (g_pDDraw16Spare != 0) {
        COMX(g_pDDraw16Spare, DDS_RELEASE);
        g_pDDraw16Spare = 0;
    }
    g_bDDraw16Open = 0;
}

#endif /* GRIM_EXE */
