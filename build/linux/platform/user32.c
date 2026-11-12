/* USER32 on SDL2: the game window, the message queue, keyboard/mouse input, message boxes. Dialogs and hooks (the
 * developer tools: Lua console, light editor) are not available and fail the way Win32 reports failure.
 *
 * The window shows the frames gdi32.c's BitBlt delivers, scaled to the window with the aspect ratio kept.
 * Alt+Enter toggles full screen. */
#define _GNU_SOURCE
#include <SDL.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "platform.h"

typedef LONG (WINAPI *WNDPROC)(HANDLE, UINT, DWORD, LONG);

typedef struct {
    WNDPROC proc;
    DWORD style;
    SDL_Window *sdl;
} Window;

typedef struct { HANDLE hwnd; UINT message; DWORD wParam; LONG lParam; DWORD time; LONG x, y; } MSG;

#define WM_CREATE 0x0001
#define WM_DESTROY 0x0002
#define WM_ACTIVATE 0x0006
#define WM_SETFOCUS 0x0007
#define WM_KILLFOCUS 0x0008
#define WM_CLOSE 0x0010
#define WM_QUIT 0x0012
#define WM_ACTIVATEAPP 0x001c
#define WM_KEYDOWN 0x0100
#define WM_KEYUP 0x0101
#define WM_CHAR 0x0102
#define WM_SYSKEYDOWN 0x0104
#define WM_SYSKEYUP 0x0105
#define WM_MOUSEMOVE 0x0200

static char g_class_name[64];
static WNDPROC g_class_proc;
static HANDLE g_hwnd;
static Window *g_win;
static SDL_Renderer *g_renderer;
static SDL_Texture *g_texture;
static int g_tex_w, g_tex_h;
static int g_sdl_ok = -1;
static BYTE g_vk_down[256];
static int g_cursor_count;

#define QSIZE 512
static MSG g_queue[QSIZE];
static int g_qhead, g_qtail;

static void post(HANDLE hwnd, UINT msg, DWORD w, LONG l)
{
    int next = (g_qtail + 1) % QSIZE;
    if (next == g_qhead) {
        if (msg == WM_MOUSEMOVE)
            return;
        g_qhead = (g_qhead + 1) % QSIZE;   /* full: drop the oldest */
    }
    g_queue[g_qtail] = (MSG){ hwnd, msg, w, l, plat_ms(), 0, 0 };
    g_qtail = next;
}

static LONG send(HANDLE hwnd, UINT msg, DWORD w, LONG l)
{
    Window *win = handle_get(hwnd, H_WINDOW);
    return win && win->proc ? win->proc(hwnd, msg, w, l) : 0;
}

static int sdl_init(void)
{
    if (g_sdl_ok < 0) {
        g_sdl_ok = SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == 0;
        if (!g_sdl_ok)
            plat_log("SDL video: %s (running without a window)", SDL_GetError());
    }
    return g_sdl_ok;
}

void *win_sdl_window(void) { return g_win ? g_win->sdl : NULL; }

/* ---------------- keyboard tables ---------------- */
static const struct { short sdl, dik, vk; } g_keys[] = {
    { SDL_SCANCODE_ESCAPE, 0x01, 0x1b }, { SDL_SCANCODE_1, 0x02, '1' }, { SDL_SCANCODE_2, 0x03, '2' },
    { SDL_SCANCODE_3, 0x04, '3' }, { SDL_SCANCODE_4, 0x05, '4' }, { SDL_SCANCODE_5, 0x06, '5' },
    { SDL_SCANCODE_6, 0x07, '6' }, { SDL_SCANCODE_7, 0x08, '7' }, { SDL_SCANCODE_8, 0x09, '8' },
    { SDL_SCANCODE_9, 0x0a, '9' }, { SDL_SCANCODE_0, 0x0b, '0' }, { SDL_SCANCODE_MINUS, 0x0c, 0xbd },
    { SDL_SCANCODE_EQUALS, 0x0d, 0xbb }, { SDL_SCANCODE_BACKSPACE, 0x0e, 0x08 }, { SDL_SCANCODE_TAB, 0x0f, 0x09 },
    { SDL_SCANCODE_Q, 0x10, 'Q' }, { SDL_SCANCODE_W, 0x11, 'W' }, { SDL_SCANCODE_E, 0x12, 'E' },
    { SDL_SCANCODE_R, 0x13, 'R' }, { SDL_SCANCODE_T, 0x14, 'T' }, { SDL_SCANCODE_Y, 0x15, 'Y' },
    { SDL_SCANCODE_U, 0x16, 'U' }, { SDL_SCANCODE_I, 0x17, 'I' }, { SDL_SCANCODE_O, 0x18, 'O' },
    { SDL_SCANCODE_P, 0x19, 'P' }, { SDL_SCANCODE_LEFTBRACKET, 0x1a, 0xdb }, { SDL_SCANCODE_RIGHTBRACKET, 0x1b, 0xdd },
    { SDL_SCANCODE_RETURN, 0x1c, 0x0d }, { SDL_SCANCODE_LCTRL, 0x1d, 0x11 }, { SDL_SCANCODE_A, 0x1e, 'A' },
    { SDL_SCANCODE_S, 0x1f, 'S' }, { SDL_SCANCODE_D, 0x20, 'D' }, { SDL_SCANCODE_F, 0x21, 'F' },
    { SDL_SCANCODE_G, 0x22, 'G' }, { SDL_SCANCODE_H, 0x23, 'H' }, { SDL_SCANCODE_J, 0x24, 'J' },
    { SDL_SCANCODE_K, 0x25, 'K' }, { SDL_SCANCODE_L, 0x26, 'L' }, { SDL_SCANCODE_SEMICOLON, 0x27, 0xba },
    { SDL_SCANCODE_APOSTROPHE, 0x28, 0xde }, { SDL_SCANCODE_GRAVE, 0x29, 0xc0 }, { SDL_SCANCODE_LSHIFT, 0x2a, 0x10 },
    { SDL_SCANCODE_BACKSLASH, 0x2b, 0xdc }, { SDL_SCANCODE_Z, 0x2c, 'Z' }, { SDL_SCANCODE_X, 0x2d, 'X' },
    { SDL_SCANCODE_C, 0x2e, 'C' }, { SDL_SCANCODE_V, 0x2f, 'V' }, { SDL_SCANCODE_B, 0x30, 'B' },
    { SDL_SCANCODE_N, 0x31, 'N' }, { SDL_SCANCODE_M, 0x32, 'M' }, { SDL_SCANCODE_COMMA, 0x33, 0xbc },
    { SDL_SCANCODE_PERIOD, 0x34, 0xbe }, { SDL_SCANCODE_SLASH, 0x35, 0xbf }, { SDL_SCANCODE_RSHIFT, 0x36, 0x10 },
    { SDL_SCANCODE_KP_MULTIPLY, 0x37, 0x6a }, { SDL_SCANCODE_LALT, 0x38, 0x12 }, { SDL_SCANCODE_SPACE, 0x39, 0x20 },
    { SDL_SCANCODE_CAPSLOCK, 0x3a, 0x14 }, { SDL_SCANCODE_F1, 0x3b, 0x70 }, { SDL_SCANCODE_F2, 0x3c, 0x71 },
    { SDL_SCANCODE_F3, 0x3d, 0x72 }, { SDL_SCANCODE_F4, 0x3e, 0x73 }, { SDL_SCANCODE_F5, 0x3f, 0x74 },
    { SDL_SCANCODE_F6, 0x40, 0x75 }, { SDL_SCANCODE_F7, 0x41, 0x76 }, { SDL_SCANCODE_F8, 0x42, 0x77 },
    { SDL_SCANCODE_F9, 0x43, 0x78 }, { SDL_SCANCODE_F10, 0x44, 0x79 }, { SDL_SCANCODE_NUMLOCKCLEAR, 0x45, 0x90 },
    { SDL_SCANCODE_SCROLLLOCK, 0x46, 0x91 }, { SDL_SCANCODE_KP_7, 0x47, 0x67 }, { SDL_SCANCODE_KP_8, 0x48, 0x68 },
    { SDL_SCANCODE_KP_9, 0x49, 0x69 }, { SDL_SCANCODE_KP_MINUS, 0x4a, 0x6d }, { SDL_SCANCODE_KP_4, 0x4b, 0x64 },
    { SDL_SCANCODE_KP_5, 0x4c, 0x65 }, { SDL_SCANCODE_KP_6, 0x4d, 0x66 }, { SDL_SCANCODE_KP_PLUS, 0x4e, 0x6b },
    { SDL_SCANCODE_KP_1, 0x4f, 0x61 }, { SDL_SCANCODE_KP_2, 0x50, 0x62 }, { SDL_SCANCODE_KP_3, 0x51, 0x63 },
    { SDL_SCANCODE_KP_0, 0x52, 0x60 }, { SDL_SCANCODE_KP_PERIOD, 0x53, 0x6e }, { SDL_SCANCODE_F11, 0x57, 0x7a },
    { SDL_SCANCODE_F12, 0x58, 0x7b }, { SDL_SCANCODE_KP_ENTER, 0x9c, 0x0d }, { SDL_SCANCODE_RCTRL, 0x9d, 0x11 },
    { SDL_SCANCODE_KP_DIVIDE, 0xb5, 0x6f }, { SDL_SCANCODE_PRINTSCREEN, 0xb7, 0x2c }, { SDL_SCANCODE_RALT, 0xb8, 0x12 },
    { SDL_SCANCODE_PAUSE, 0xc5, 0x13 }, { SDL_SCANCODE_HOME, 0xc7, 0x24 }, { SDL_SCANCODE_UP, 0xc8, 0x26 },
    { SDL_SCANCODE_PAGEUP, 0xc9, 0x21 }, { SDL_SCANCODE_LEFT, 0xcb, 0x25 }, { SDL_SCANCODE_RIGHT, 0xcd, 0x27 },
    { SDL_SCANCODE_END, 0xcf, 0x23 }, { SDL_SCANCODE_DOWN, 0xd0, 0x28 }, { SDL_SCANCODE_PAGEDOWN, 0xd1, 0x22 },
    { SDL_SCANCODE_INSERT, 0xd2, 0x2d }, { SDL_SCANCODE_DELETE, 0xd3, 0x2e }, { SDL_SCANCODE_LGUI, 0xdb, 0x5b },
    { SDL_SCANCODE_RGUI, 0xdc, 0x5c },
};

int sdl_scancode_to_dik(int sc)
{
    for (size_t i = 0; i < sizeof g_keys / sizeof g_keys[0]; i++)
        if (g_keys[i].sdl == sc)
            return g_keys[i].dik;
    return 0;
}

int sdl_scancode_to_vk(int sc)
{
    for (size_t i = 0; i < sizeof g_keys / sizeof g_keys[0]; i++)
        if (g_keys[i].sdl == sc)
            return g_keys[i].vk;
    return 0;
}

/* ---------------- events ---------------- */
static void toggle_fullscreen(void)
{
    if (!g_win || !g_win->sdl)
        return;
    Uint32 f = SDL_GetWindowFlags(g_win->sdl);
    SDL_SetWindowFullscreen(g_win->sdl, (f & SDL_WINDOW_FULLSCREEN_DESKTOP) ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP);
}

void win_pump_events(void)
{
    SDL_Event e;
    if (g_sdl_ok != 1)
        return;
    while (SDL_PollEvent(&e)) {
        uint32_t now = plat_ms();
        switch (e.type) {
        case SDL_QUIT:
            post(g_hwnd, WM_CLOSE, 0, 0);
            break;
        case SDL_WINDOWEVENT:
            plat_trace("window event %d", e.window.event);
            if (e.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
                post(g_hwnd, WM_ACTIVATEAPP, 1, 0);
                post(g_hwnd, WM_ACTIVATE, 1, 0);
            } else if (e.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
                post(g_hwnd, WM_ACTIVATE, 0, 0);
                post(g_hwnd, WM_ACTIVATEAPP, 0, 0);
                memset(g_vk_down, 0, sizeof g_vk_down);
            } else if (e.window.event == SDL_WINDOWEVENT_CLOSE) {
                post(g_hwnd, WM_CLOSE, 0, 0);
            }
            break;
        case SDL_KEYDOWN:
        case SDL_KEYUP: {
            int down = e.type == SDL_KEYDOWN, sc = e.key.keysym.scancode;
            int vk = sdl_scancode_to_vk(sc), dik = sdl_scancode_to_dik(sc);
            int alt = (e.key.keysym.mod & KMOD_ALT) != 0;
            if (down && sc == SDL_SCANCODE_RETURN && alt) {
                toggle_fullscreen();
                break;
            }
            plat_trace("key %s scancode %d -> DIK %#x VK %#x", down ? "down" : "up", sc, dik, vk);
            if (!e.key.repeat && dik)
                dinput_key_event(dik, down, now);
            if (vk) {
                LONG lp = 1 | (dik & 0x7f) << 16 | (dik & 0x80 ? 1 << 24 : 0) | (e.key.repeat ? 1 << 30 : 0) |
                          (down ? 0 : 3u << 30);
                g_vk_down[vk] = down;
                post(g_hwnd, alt || vk == 0x12 ? (down ? WM_SYSKEYDOWN : WM_SYSKEYUP) : (down ? WM_KEYDOWN : WM_KEYUP),
                     vk, lp);
            }
            break;
        }
        case SDL_TEXTINPUT: {
            /* UTF-8 -> Latin-1 characters (the game's fonts) */
            const unsigned char *s = (const unsigned char *)e.text.text;
            while (*s) {
                unsigned c = *s++;
                if (c >= 0xc0 && c < 0xe0 && (*s & 0xc0) == 0x80)
                    c = (c & 0x1f) << 6 | (*s++ & 0x3f);
                else if (c >= 0x80)
                    continue;
                if (c < 256)
                    post(g_hwnd, WM_CHAR, c, 1);
            }
            break;
        }
        case SDL_MOUSEMOTION:
            dinput_mouse_motion(e.motion.xrel, e.motion.yrel, 0, now);
            post(g_hwnd, WM_MOUSEMOVE, 0, (e.motion.y & 0xffff) << 16 | (e.motion.x & 0xffff));
            break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP: {
            int b = e.button.button == SDL_BUTTON_LEFT ? 0 : e.button.button == SDL_BUTTON_RIGHT ? 1 : 2;
            int down = e.type == SDL_MOUSEBUTTONDOWN;
            static const UINT msgs[3][2] = { { 0x202, 0x201 }, { 0x205, 0x204 }, { 0x208, 0x207 } };
            dinput_mouse_button(b, down, now);
            post(g_hwnd, msgs[b][down], 0, (e.button.y & 0xffff) << 16 | (e.button.x & 0xffff));
            break;
        }
        case SDL_MOUSEWHEEL:
            dinput_mouse_motion(0, 0, e.wheel.y * 120, now);
            break;
        default:
            break;
        }
    }
}

/* GRIM_SHOT=<file.bmp>: whenever <file.bmp>.req exists, the next frame is written to <file.bmp> and the request
 * file removed (scripted tests and screenshots without a window manager) */
static void write_bmp(const char *path, const uint32_t *argb, int w, int h)
{
    FILE *f = fopen(path, "wb");
    if (!f)
        return;
    {
        uint32_t size = 54 + (uint32_t)w * h * 4;
        uint8_t hdr[54] = { 'B', 'M' };
        int32_t v[] = { (int32_t)size, 0, 54, 40, w, -h };
        memcpy(hdr + 2, v, 12);
        memcpy(hdr + 14, v + 3, 12);
        hdr[26] = 1;
        hdr[28] = 32;
        fwrite(hdr, 1, sizeof hdr, f);
        fwrite(argb, 4, (size_t)w * h, f);
    }
    fclose(f);
}

/* GRIM_SHOT_FRAMES=<n> also writes each of the first n frames to <file.bmp>.<i>.bmp */
static void maybe_screenshot(const uint32_t *argb, int w, int h)
{
    static const char *shot = (const char *)-1;
    static int frames, max_frames;
    char req[1024];
    if (shot == (const char *)-1) {
        shot = getenv("GRIM_SHOT");
        max_frames = getenv("GRIM_SHOT_FRAMES") ? atoi(getenv("GRIM_SHOT_FRAMES")) : 0;
    }
    if (!shot)
        return;
    if (frames < max_frames) {
        snprintf(req, sizeof req, "%s.%d.bmp", shot, frames++);
        write_bmp(req, argb, w, h);
    }
    snprintf(req, sizeof req, "%s.req", shot);
    if (remove(req) == 0)
        write_bmp(shot, argb, w, h);
}

void win_present(const uint32_t *argb, int w, int h)
{
    maybe_screenshot(argb, w, h);
    if (!g_renderer)
        return;
    if (!g_texture || g_tex_w != w || g_tex_h != h) {
        if (g_texture)
            SDL_DestroyTexture(g_texture);
        g_texture = SDL_CreateTexture(g_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, w, h);
        g_tex_w = w;
        g_tex_h = h;
        SDL_RenderSetLogicalSize(g_renderer, w, h);
    }
    SDL_UpdateTexture(g_texture, NULL, argb, w * 4);
    SDL_RenderClear(g_renderer);
    SDL_RenderCopy(g_renderer, g_texture, NULL, NULL);
    SDL_RenderPresent(g_renderer);
}

/* ---------------- window class and window ---------------- */
typedef struct {
    UINT cbSize, style;
    WNDPROC proc;
    int cbClsExtra, cbWndExtra;
    HANDLE hInstance, hIcon, hCursor, hbrBackground;
    const char *menu, *name;
    HANDLE hIconSm;
} WNDCLASSEXA;

WINFN(WORD, RegisterClassExA, (const WNDCLASSEXA *wc))
{
    snprintf(g_class_name, sizeof g_class_name, "%s", wc->name ? wc->name : "");
    g_class_proc = wc->proc;
    return 1;
}

WINFN(HANDLE, FindWindowA, (const char *cls, const char *title)) { (void)cls; (void)title; return NULL; }

static int default_scale(int w, int h)
{
    SDL_DisplayMode dm;
    const char *e = getenv("GRIM_SCALE");
    int s = 1;
    if (e && atoi(e) > 0)
        return atoi(e);
    if (SDL_GetDesktopDisplayMode(0, &dm) == 0)
        while ((s + 1) * w <= dm.w * 9 / 10 && (s + 1) * h <= dm.h * 9 / 10)
            s++;
    return s;
}

WINFN(HANDLE, CreateWindowExA, (DWORD exstyle, const char *cls, const char *title, DWORD style, int x, int y, int w,
                                int h, HANDLE parent, HANDLE menu, HANDLE inst, void *param))
{
    Window *win = calloc(1, sizeof *win);
    HANDLE hwnd;
    (void)exstyle; (void)cls; (void)x; (void)y; (void)parent; (void)menu; (void)inst; (void)param;
    win->proc = g_class_proc;
    win->style = style;
    if (w <= 0 || w > 4096) w = 640;
    if (h <= 0 || h > 4096) h = 480;
    if (sdl_init()) {
        int s = default_scale(640, 480);
        win->sdl = SDL_CreateWindow(title ? title : "Grim Fandango", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    640 * s, 480 * s, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN);
        if (!win->sdl) {
            plat_log("SDL_CreateWindow: %s", SDL_GetError());
        } else {
            g_renderer = SDL_CreateRenderer(win->sdl, -1, SDL_RENDERER_PRESENTVSYNC);
            if (!g_renderer)
                g_renderer = SDL_CreateRenderer(win->sdl, -1, SDL_RENDERER_SOFTWARE);
            if (g_renderer) {
                SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, getenv("GRIM_SHARP") ? "nearest" : "linear");
                SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
            }
            SDL_StartTextInput();
        }
    }
    hwnd = handle_new(H_WINDOW, win);
    if (!g_win) {
        g_win = win;
        g_hwnd = hwnd;
    }
    send(hwnd, WM_CREATE, 0, 0);
    if (style & 0x10000000) {   /* WS_VISIBLE */
        if (win->sdl)
            SDL_ShowWindow(win->sdl);
        send(hwnd, WM_ACTIVATEAPP, 1, 0);
        send(hwnd, WM_ACTIVATE, 1, 0);
    }
    return hwnd;
}

WINFN(BOOL, ShowWindow, (HANDLE hwnd, int cmd))
{
    Window *win = handle_get(hwnd, H_WINDOW);
    if (!win || !win->sdl)
        return 0;
    if (cmd == 0)
        SDL_HideWindow(win->sdl);
    else if (cmd == 2 || cmd == 6 || cmd == 7)
        SDL_MinimizeWindow(win->sdl);
    else {
        SDL_ShowWindow(win->sdl);
        if (cmd == 9)
            SDL_RestoreWindow(win->sdl);
    }
    return 1;
}

WINFN(BOOL, UpdateWindow, (HANDLE hwnd)) { (void)hwnd; return 1; }
WINFN(BOOL, CloseWindow, (HANDLE hwnd)) { return ShowWindow(hwnd, 6); }

WINFN(BOOL, DestroyWindow, (HANDLE hwnd))
{
    Window *win = handle_get(hwnd, H_WINDOW);
    if (!win)
        return 0;
    send(hwnd, WM_DESTROY, 0, 0);
    if (win->sdl) {
        if (win == g_win) {
            if (g_texture)
                SDL_DestroyTexture(g_texture);
            if (g_renderer)
                SDL_DestroyRenderer(g_renderer);
            g_texture = NULL;
            g_renderer = NULL;
        }
        SDL_DestroyWindow(win->sdl);
    }
    if (win == g_win)
        g_win = NULL;
    handle_free(hwnd);
    free(win);
    return 1;
}

WINFN(LONG, SetWindowLongA, (HANDLE hwnd, int index, LONG v))
{
    Window *win = handle_get(hwnd, H_WINDOW);
    LONG old = 0;
    if (win && index == -16) {   /* GWL_STYLE */
        old = (LONG)win->style;
        win->style = (DWORD)v;
    }
    return old;
}

WINFN(BOOL, SetWindowPos, (HANDLE hwnd, HANDLE after, int x, int y, int cx, int cy, UINT flags))
{
    (void)hwnd; (void)after; (void)x; (void)y; (void)cx; (void)cy; (void)flags;
    return 1;   /* the SDL window keeps its own (scaled) size; frames are scaled to it */
}

WINFN(LONG, DefWindowProcA, (HANDLE hwnd, UINT msg, DWORD w, LONG l))
{
    (void)w; (void)l;
    if (msg == WM_CLOSE)
        DestroyWindow(hwnd);
    return 0;
}

WINFN(LONG, SendMessageA, (HANDLE hwnd, UINT msg, DWORD w, LONG l)) { return send(hwnd, msg, w, l); }

/* ---------------- message loop ---------------- */
WINFN(BOOL, PeekMessageA, (MSG *m, HANDLE hwnd, UINT min, UINT max, UINT remove))
{
    (void)hwnd; (void)min; (void)max;
    win_pump_events();
    if (g_qhead == g_qtail)
        return 0;
    *m = g_queue[g_qhead];
    if (remove & 1)
        g_qhead = (g_qhead + 1) % QSIZE;
    return 1;
}

WINFN(BOOL, GetMessageA, (MSG *m, HANDLE hwnd, UINT min, UINT max))
{
    (void)hwnd; (void)min; (void)max;
    for (;;) {
        win_pump_events();
        if (g_qhead != g_qtail)
            break;
        if (g_sdl_ok == 1)
            SDL_WaitEventTimeout(NULL, 10);
        else
            SDL_Delay(10);
    }
    *m = g_queue[g_qhead];
    g_qhead = (g_qhead + 1) % QSIZE;
    return m->message != WM_QUIT;
}

WINFN(BOOL, TranslateMessage, (const MSG *m)) { (void)m; return 0; }   /* WM_CHAR comes from SDL text input */
WINFN(LONG, DispatchMessageA, (const MSG *m)) { return send(m->hwnd, m->message, m->wParam, m->lParam); }
WINFN(void, PostQuitMessage, (int code)) { post(NULL, WM_QUIT, (DWORD)code, 0); }

/* ---------------- focus, cursor, metrics ---------------- */
WINFN(HANDLE, SetFocus, (HANDLE hwnd)) { (void)hwnd; return g_hwnd; }
WINFN(HANDLE, GetFocus, (void)) { return g_hwnd; }
WINFN(HANDLE, SetActiveWindow, (HANDLE hwnd)) { (void)hwnd; return g_hwnd; }
WINFN(BOOL, SetForegroundWindow, (HANDLE hwnd)) { (void)hwnd; return 1; }
WINFN(HANDLE, GetParent, (HANDLE hwnd)) { (void)hwnd; return NULL; }
WINFN(BOOL, IsIconic, (HANDLE hwnd))
{
    Window *win = handle_get(hwnd, H_WINDOW);
    return win && win->sdl && (SDL_GetWindowFlags(win->sdl) & SDL_WINDOW_MINIMIZED);
}
WINFN(DWORD, GetWindowThreadProcessId, (HANDLE hwnd, DWORD *pid))
{
    (void)hwnd;
    if (pid)
        *pid = 1;
    return 1;
}
WINFN(short, GetKeyState, (int vk))
{
    return g_vk_down[vk & 0xff] ? (short)0x8000 : 0;
}

WINFN(HANDLE, SetCursor, (HANDLE c)) { (void)c; return NULL; }
WINFN(int, ShowCursor, (BOOL show))
{
    g_cursor_count += show ? 1 : -1;
    if (g_sdl_ok == 1)
        SDL_ShowCursor(g_cursor_count >= 0 ? SDL_ENABLE : SDL_DISABLE);
    return g_cursor_count;
}
WINFN(HANDLE, LoadCursorA, (HANDLE inst, const char *name)) { (void)inst; (void)name; return (HANDLE)1; }
WINFN(HANDLE, LoadIconA, (HANDLE inst, const char *name)) { (void)inst; (void)name; return (HANDLE)1; }

WINFN(int, GetSystemMetrics, (int index))
{
    SDL_DisplayMode dm;
    switch (index) {
    case 0:
    case 1:
        if (sdl_init() && SDL_GetDesktopDisplayMode(0, &dm) == 0)
            return index ? dm.h : dm.w;
        return index ? 1080 : 1920;
    case 0x2b: return 3;   /* SM_CMOUSEBUTTONS */
    default: return 0;     /* frame and caption sizes: the SDL window's client area is the whole window */
    }
}

WINFN(BOOL, MessageBeep, (UINT type)) { (void)type; return 1; }

/* ---------------- message boxes ---------------- */
WINFN(int, MessageBoxA, (HANDLE hwnd, const char *text, const char *caption, UINT type))
{
    SDL_MessageBoxButtonData buttons[3];
    SDL_MessageBoxData box;
    int n = 0, hit = -1;
    (void)hwnd;
    plat_log("message box \"%s\": %s", caption ? caption : "", text ? text : "");
    switch (type & 0xf) {
    case 1: buttons[n++] = (SDL_MessageBoxButtonData){ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "OK" };
            buttons[n++] = (SDL_MessageBoxButtonData){ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "Cancel" }; break;
    case 3: buttons[n++] = (SDL_MessageBoxButtonData){ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 6, "Yes" };
            buttons[n++] = (SDL_MessageBoxButtonData){ 0, 7, "No" };
            buttons[n++] = (SDL_MessageBoxButtonData){ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "Cancel" }; break;
    case 4: buttons[n++] = (SDL_MessageBoxButtonData){ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 6, "Yes" };
            buttons[n++] = (SDL_MessageBoxButtonData){ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 7, "No" }; break;
    default: buttons[n++] = (SDL_MessageBoxButtonData){ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT |
                                                          SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "OK" }; break;
    }
    memset(&box, 0, sizeof box);
    box.flags = (type & 0x10) ? SDL_MESSAGEBOX_ERROR : (type & 0x30) == 0x30 ? SDL_MESSAGEBOX_WARNING
                                                                              : SDL_MESSAGEBOX_INFORMATION;
    box.window = g_win ? g_win->sdl : NULL;
    box.title = caption ? caption : "Grim Fandango";
    box.message = text ? text : "";
    box.numbuttons = n;
    box.buttons = buttons;
    if (getenv("GRIM_NODIALOGS") || SDL_ShowMessageBox(&box, &hit) != 0 || hit < 0)
        hit = buttons[0].buttonid;
    return hit;
}

/* ---------------- dialogs and hooks: not available ---------------- */
WINFN(HANDLE, CreateDialogParamA, (HANDLE i, const char *t, HANDLE p, void *f, LONG l))
{ (void)i; (void)t; (void)p; (void)f; (void)l; return NULL; }
WINFN(int, DialogBoxIndirectParamA, (HANDLE i, const void *t, HANDLE p, void *f, LONG l))
{ (void)i; (void)t; (void)p; (void)f; (void)l; plat_log("dialog box not available: cancelled"); return 2; }
WINFN(BOOL, IsDialogMessageA, (HANDLE d, MSG *m)) { (void)d; (void)m; return 0; }
WINFN(BOOL, EndDialog, (HANDLE d, int r)) { (void)d; (void)r; return 1; }
WINFN(HANDLE, GetDlgItem, (HANDLE d, int id)) { (void)d; (void)id; return NULL; }
WINFN(UINT, GetDlgItemTextA, (HANDLE d, int id, char *s, int n)) { (void)d; (void)id; if (n > 0) s[0] = 0; return 0; }
WINFN(BOOL, SetDlgItemTextA, (HANDLE d, int id, const char *s)) { (void)d; (void)id; (void)s; return 1; }
WINFN(BOOL, SetDlgItemInt, (HANDLE d, int id, UINT v, BOOL sg)) { (void)d; (void)id; (void)v; (void)sg; return 1; }
WINFN(UINT, GetDlgItemInt, (HANDLE d, int id, BOOL *ok, BOOL sg)) { (void)d; (void)id; (void)sg; if (ok) *ok = 0; return 0; }
WINFN(BOOL, CheckDlgButton, (HANDLE d, int id, UINT c)) { (void)d; (void)id; (void)c; return 1; }
WINFN(UINT, IsDlgButtonChecked, (HANDLE d, int id)) { (void)d; (void)id; return 0; }
WINFN(LONG, SendDlgItemMessageA, (HANDLE d, int id, UINT m, DWORD w, LONG l)) { (void)d; (void)id; (void)m; (void)w; (void)l; return 0; }
WINFN(BOOL, EnableWindow, (HANDLE h, BOOL e)) { (void)h; (void)e; return 0; }
WINFN(BOOL, IsWindowEnabled, (HANDLE h)) { (void)h; return 1; }
WINFN(HANDLE, SetWindowsHookExA, (int id, void *f, HANDLE m, DWORD t)) { (void)id; (void)f; (void)m; (void)t; return NULL; }
WINFN(BOOL, UnhookWindowsHookEx, (HANDLE h)) { (void)h; return 1; }
WINFN(LONG, CallNextHookEx, (HANDLE h, int c, DWORD w, LONG l)) { (void)h; (void)c; (void)w; (void)l; return 0; }
WINFN(BOOL, GetOpenFileNameA, (void *ofn)) { (void)ofn; return 0; }
WINFN(BOOL, GetSaveFileNameA, (void *ofn)) { (void)ofn; return 0; }
