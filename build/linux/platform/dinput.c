/* DirectInput 5 (keyboard and mouse) as COM objects over the SDL events user32.c delivers.
 *
 * The game reads the keyboard with GetDeviceData (buffered key events, DIK scan codes) plus GetDeviceState (256 key
 * bytes), and the mouse with GetDeviceState (DIMOUSESTATE, relative axes) and GetDeviceData. */
#define _GNU_SOURCE
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "platform.h"

typedef struct { DWORD ofs, data, time, seq; } DIDEVICEOBJECTDATA;

#define BUF 256
typedef struct Device {
    void **vtbl;
    int refs;
    int is_mouse;
    DIDEVICEOBJECTDATA events[BUF];
    int head, tail, overflow;
} Device;

typedef struct { void **vtbl; int refs; } DInput;

static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;
static BYTE g_keys[256];
static LONG g_mouse_dx, g_mouse_dy, g_mouse_dz;
static BYTE g_mouse_buttons[4];
static Device *g_keyboard, *g_mouse;
static DWORD g_seq;

static void push(Device *d, DWORD ofs, DWORD data, DWORD time)
{
    int next;
    if (!d)
        return;
    next = (d->tail + 1) % BUF;
    if (next == d->head) {
        d->overflow = 1;
        d->head = (d->head + 1) % BUF;
    }
    d->events[d->tail] = (DIDEVICEOBJECTDATA){ ofs, data, time, ++g_seq };
    d->tail = next;
}

void dinput_key_event(int dik, int down, uint32_t time)
{
    pthread_mutex_lock(&g_lock);
    g_keys[dik & 0xff] = down ? 0x80 : 0;
    push(g_keyboard, dik & 0xff, down ? 0x80 : 0, time);
    pthread_mutex_unlock(&g_lock);
}

void dinput_mouse_motion(int dx, int dy, int dz, uint32_t time)
{
    pthread_mutex_lock(&g_lock);
    g_mouse_dx += dx;
    g_mouse_dy += dy;
    g_mouse_dz += dz;
    if (dx) push(g_mouse, 0, (DWORD)dx, time);
    if (dy) push(g_mouse, 4, (DWORD)dy, time);
    if (dz) push(g_mouse, 8, (DWORD)dz, time);
    pthread_mutex_unlock(&g_lock);
}

void dinput_mouse_button(int b, int down, uint32_t time)
{
    pthread_mutex_lock(&g_lock);
    if (b >= 0 && b < 4) {
        g_mouse_buttons[b] = down ? 0x80 : 0;
        push(g_mouse, 12 + b, down ? 0x80 : 0, time);
    }
    pthread_mutex_unlock(&g_lock);
}

/* ---- IDirectInputDeviceA ---- */
#define E_NOINTERFACE 0x80004002u
#define E_FAIL 0x80004005u

static HRESULT WINAPI dev_QueryInterface(Device *d, const void *iid, void **out) { (void)d; (void)iid; *out = NULL; return E_NOINTERFACE; }
static DWORD WINAPI dev_AddRef(Device *d) { return ++d->refs; }
static DWORD WINAPI dev_Release(Device *d)
{
    int r = --d->refs;
    if (r == 0) {
        pthread_mutex_lock(&g_lock);
        if (d == g_keyboard) g_keyboard = NULL;
        if (d == g_mouse) g_mouse = NULL;
        pthread_mutex_unlock(&g_lock);
        free(d);
    }
    return r;
}
static HRESULT WINAPI dev_GetCapabilities(Device *d, DWORD *caps) { (void)d; (void)caps; return 0; }
static HRESULT WINAPI dev_EnumObjects(Device *d, void *cb, void *ref, DWORD flags) { (void)d; (void)cb; (void)ref; (void)flags; return 0; }
static HRESULT WINAPI dev_GetProperty(Device *d, const void *prop, void *hdr) { (void)d; (void)prop; (void)hdr; return E_FAIL; }
static HRESULT WINAPI dev_SetProperty(Device *d, const void *prop, const void *hdr) { (void)d; (void)prop; (void)hdr; return 0; }
static HRESULT WINAPI dev_Acquire(Device *d) { (void)d; return 0; }
static HRESULT WINAPI dev_Unacquire(Device *d) { (void)d; return 0; }

static HRESULT WINAPI dev_GetDeviceState(Device *d, DWORD size, void *data)
{
    pthread_mutex_lock(&g_lock);
    if (!d->is_mouse) {
        memset(data, 0, size);
        memcpy(data, g_keys, size < 256 ? size : 256);
    } else {
        LONG st[4] = { g_mouse_dx, g_mouse_dy, g_mouse_dz, 0 };
        memcpy(&st[3], g_mouse_buttons, 4);
        memset(data, 0, size);
        memcpy(data, st, size < sizeof st ? size : sizeof st);
        g_mouse_dx = g_mouse_dy = g_mouse_dz = 0;
    }
    pthread_mutex_unlock(&g_lock);
    return 0;
}

static HRESULT WINAPI dev_GetDeviceData(Device *d, DWORD objsize, DIDEVICEOBJECTDATA *out, DWORD *inout, DWORD flags)
{
    DWORD n = 0, want = inout ? *inout : 0;
    int pos;
    HRESULT r;
    pthread_mutex_lock(&g_lock);
    pos = d->head;
    while (pos != d->tail && n < want) {
        if (out)
            memcpy((BYTE *)out + n * objsize, &d->events[pos], objsize < sizeof(DIDEVICEOBJECTDATA) ? objsize : sizeof(DIDEVICEOBJECTDATA));
        pos = (pos + 1) % BUF;
        n++;
    }
    if (!(flags & 1))   /* DIGDD_PEEK */
        d->head = pos;
    r = d->overflow ? 1 : 0;   /* DI_BUFFEROVERFLOW */
    d->overflow = 0;
    pthread_mutex_unlock(&g_lock);
    if (inout)
        *inout = n;
    return r;
}

static HRESULT WINAPI dev_SetDataFormat(Device *d, const void *fmt) { (void)d; (void)fmt; return 0; }
static HRESULT WINAPI dev_SetEventNotification(Device *d, HANDLE e) { (void)d; (void)e; return 0; }
static HRESULT WINAPI dev_SetCooperativeLevel(Device *d, HANDLE w, DWORD f) { (void)d; (void)w; (void)f; return 0; }
static HRESULT WINAPI dev_GetObjectInfo(Device *d, void *o, DWORD a, DWORD b) { (void)d; (void)o; (void)a; (void)b; return E_FAIL; }
static HRESULT WINAPI dev_GetDeviceInfo(Device *d, void *i) { (void)d; (void)i; return E_FAIL; }
static HRESULT WINAPI dev_RunControlPanel(Device *d, HANDLE w, DWORD f) { (void)d; (void)w; (void)f; return 0; }
static HRESULT WINAPI dev_Initialize(Device *d, HANDLE i, DWORD v, const void *g) { (void)d; (void)i; (void)v; (void)g; return 0; }

static void *g_dev_vtbl[] = {
    dev_QueryInterface, dev_AddRef, dev_Release, dev_GetCapabilities, dev_EnumObjects, dev_GetProperty,
    dev_SetProperty, dev_Acquire, dev_Unacquire, dev_GetDeviceState, dev_GetDeviceData, dev_SetDataFormat,
    dev_SetEventNotification, dev_SetCooperativeLevel, dev_GetObjectInfo, dev_GetDeviceInfo, dev_RunControlPanel,
    dev_Initialize,
};

/* ---- IDirectInputA ---- */
static HRESULT WINAPI di_QueryInterface(DInput *d, const void *iid, void **out) { (void)d; (void)iid; *out = NULL; return E_NOINTERFACE; }
static DWORD WINAPI di_AddRef(DInput *d) { return ++d->refs; }
static DWORD WINAPI di_Release(DInput *d)
{
    int r = --d->refs;
    if (r == 0)
        free(d);
    return r;
}

/* GUID_SysMouse {6F1D2B60-D5A0-11CF-BFC7-444553540000}, GUID_SysKeyboard {6F1D2B61-...} */
static HRESULT WINAPI di_CreateDevice(DInput *di, const BYTE *guid, Device **out, void *outer)
{
    static const BYTE tail[12] = { 0xa0, 0xd5, 0xcf, 0x11, 0xbf, 0xc7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00 };
    Device *d;
    (void)di; (void)outer;
    *out = NULL;
    if (memcmp(guid + 4, tail, 12) != 0 || (guid[0] != 0x60 && guid[0] != 0x61) || guid[1] != 0x2b ||
        guid[2] != 0x1d || guid[3] != 0x6f)
        return 0x80040154u;   /* REGDB_E_CLASSNOTREG: no such device */
    d = calloc(1, sizeof *d);
    d->vtbl = g_dev_vtbl;
    d->refs = 1;
    d->is_mouse = guid[0] == 0x60;
    pthread_mutex_lock(&g_lock);
    if (d->is_mouse)
        g_mouse = d;
    else
        g_keyboard = d;
    pthread_mutex_unlock(&g_lock);
    *out = d;
    return 0;
}

static HRESULT WINAPI di_EnumDevices(DInput *d, DWORD type, void *cb, void *ref, DWORD flags) { (void)d; (void)type; (void)cb; (void)ref; (void)flags; return 0; }
static HRESULT WINAPI di_GetDeviceStatus(DInput *d, const void *g) { (void)d; (void)g; return 1; }
static HRESULT WINAPI di_RunControlPanel(DInput *d, HANDLE w, DWORD f) { (void)d; (void)w; (void)f; return 0; }
static HRESULT WINAPI di_Initialize(DInput *d, HANDLE i, DWORD v) { (void)d; (void)i; (void)v; return 0; }

static void *g_di_vtbl[] = {
    di_QueryInterface, di_AddRef, di_Release, di_CreateDevice, di_EnumDevices, di_GetDeviceStatus,
    di_RunControlPanel, di_Initialize,
};

WINFN(HRESULT, DirectInputCreateA, (HANDLE inst, DWORD version, DInput **out, void *outer))
{
    DInput *d = calloc(1, sizeof *d);
    (void)inst; (void)version; (void)outer;
    d->vtbl = g_di_vtbl;
    d->refs = 1;
    *out = d;
    return 0;
}
