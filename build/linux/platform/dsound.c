/* DirectSound as COM objects over one SDL audio device.
 *
 * Every secondary buffer the game creates (iMUSE's streaming ring buffer, the movie and sound-effect mixer) is mixed
 * in the SDL audio callback at its own rate, volume and pan. The play cursor advances as SDL consumes samples, so the
 * game's polling of GetCurrentPosition and its Lock / Unlock of the ring work as on Windows. GRIM_NOSOUND=1 makes
 * DirectSoundCreate fail (the game then runs silent). */
#define _GNU_SOURCE
#include <SDL.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "platform.h"

#define E_NOINTERFACE 0x80004002u
#define DSERR_NODRIVER 0x88780078u
#define DSERR_INVALIDPARAM 0x80070057u

typedef struct {
    WORD wFormatTag, nChannels;
    DWORD nSamplesPerSec, nAvgBytesPerSec;
    WORD nBlockAlign, wBitsPerSample, cbSize;
} __attribute__((packed)) WAVEFORMATEX;

typedef struct Buffer {
    void **vtbl;
    int refs;
    int primary;
    WAVEFORMATEX fmt;
    BYTE *data;
    DWORD size;
    int *shared_refs;      /* DuplicateSoundBuffer shares data */
    double pos;            /* play position in frames */
    int playing, looping;
    LONG volume, pan;      /* hundredths of a dB */
    DWORD freq;            /* 0 = the format's rate */
    struct Buffer *next;
} Buffer;

typedef struct { void **vtbl; int refs; } DSound;

static SDL_AudioDeviceID g_dev;
static int g_rate = 44100;
static Buffer *g_buffers;

static float db_to_gain(LONG hundredths) { return hundredths <= -10000 ? 0.0f : powf(10.0f, hundredths / 2000.0f); }

static void mix(void *ud, Uint8 *stream, int len)
{
    int frames = len / 4;
    static int32_t *acc;
    static int acc_frames;
    (void)ud;
    if (acc_frames < frames) {
        free(acc);
        acc = malloc(sizeof(int32_t) * 2 * frames);
        acc_frames = frames;
    }
    memset(acc, 0, sizeof(int32_t) * 2 * frames);
    for (Buffer *b = g_buffers; b; b = b->next) {
        int ch, bits, bpf;
        DWORD nframes;
        double step;
        float g = db_to_gain(b->volume), gl = g, gr = g;
        if (!b->playing || b->primary || !b->data)
            continue;
        ch = b->fmt.nChannels ? b->fmt.nChannels : 1;
        bits = b->fmt.wBitsPerSample == 8 ? 8 : 16;
        bpf = ch * bits / 8;
        nframes = b->size / bpf;
        if (!nframes)
            continue;
        step = (double)(b->freq ? b->freq : b->fmt.nSamplesPerSec) / g_rate;
        if (b->pan > 0)
            gl *= db_to_gain(-b->pan);
        else if (b->pan < 0)
            gr *= db_to_gain(b->pan);
        for (int i = 0; i < frames; i++) {
            DWORD f = (DWORD)b->pos;
            const BYTE *p;
            int l, r;
            if (f >= nframes) {
                if (!b->looping) {
                    b->playing = 0;
                    b->pos = 0;
                    break;
                }
                b->pos -= nframes;
                f = (DWORD)b->pos;
                if (f >= nframes)
                    f = 0, b->pos = 0;
            }
            p = b->data + (size_t)f * bpf;
            if (bits == 16) {
                l = ((const int16_t *)p)[0];
                r = ch > 1 ? ((const int16_t *)p)[1] : l;
            } else {
                l = (p[0] - 128) << 8;
                r = ch > 1 ? (p[1] - 128) << 8 : l;
            }
            acc[i * 2] += (int32_t)(l * gl);
            acc[i * 2 + 1] += (int32_t)(r * gr);
            b->pos += step;
        }
    }
    for (int i = 0; i < frames * 2; i++) {
        int32_t v = acc[i];
        ((int16_t *)stream)[i] = v > 32767 ? 32767 : v < -32768 ? -32768 : (int16_t)v;
    }
}

static void lock(void) { if (g_dev) SDL_LockAudioDevice(g_dev); }
static void unlock(void) { if (g_dev) SDL_UnlockAudioDevice(g_dev); }

/* ---- IDirectSoundBuffer ---- */
static HRESULT WINAPI buf_QueryInterface(Buffer *b, const void *iid, void **out) { (void)b; (void)iid; *out = NULL; return E_NOINTERFACE; }
static DWORD WINAPI buf_AddRef(Buffer *b) { return ++b->refs; }
static DWORD WINAPI buf_Release(Buffer *b)
{
    int r = --b->refs;
    if (r > 0)
        return r;
    lock();
    for (Buffer **p = &g_buffers; *p; p = &(*p)->next)
        if (*p == b) {
            *p = b->next;
            break;
        }
    unlock();
    if (b->shared_refs && --*b->shared_refs == 0) {
        free(b->data);
        free(b->shared_refs);
    }
    free(b);
    return 0;
}

typedef struct { DWORD dwSize, dwFlags, dwBufferBytes, dwUnlockTransferRate, dwPlayCpuOverhead; } DSBCAPS;
static HRESULT WINAPI buf_GetCaps(Buffer *b, DSBCAPS *c)
{
    c->dwFlags = b->primary ? 1 : 0;
    c->dwBufferBytes = b->size;
    c->dwUnlockTransferRate = 0;
    c->dwPlayCpuOverhead = 0;
    return 0;
}

static DWORD byte_pos(Buffer *b)
{
    int bpf = (b->fmt.nChannels ? b->fmt.nChannels : 1) * (b->fmt.wBitsPerSample == 8 ? 1 : 2);
    DWORD p = (DWORD)b->pos * bpf;
    return b->size ? p % b->size : 0;
}

static HRESULT WINAPI buf_GetCurrentPosition(Buffer *b, DWORD *play, DWORD *write)
{
    DWORD p, ahead;
    lock();
    p = byte_pos(b);
    unlock();
    /* the write cursor: about 20 ms ahead of the play cursor, as a hardware buffer reports it */
    ahead = (b->fmt.nAvgBytesPerSec / 50) & ~(DWORD)(b->fmt.nBlockAlign ? b->fmt.nBlockAlign - 1 : 0);
    if (play)
        *play = p;
    if (write)
        *write = b->size ? (p + (b->playing ? ahead : 0)) % b->size : 0;
    return 0;
}

static HRESULT WINAPI buf_GetFormat(Buffer *b, WAVEFORMATEX *f, DWORD size, DWORD *written)
{
    DWORD n = size < sizeof(WAVEFORMATEX) ? size : sizeof(WAVEFORMATEX);
    if (f)
        memcpy(f, &b->fmt, n);
    if (written)
        *written = sizeof(WAVEFORMATEX);
    return 0;
}
static HRESULT WINAPI buf_GetVolume(Buffer *b, LONG *v) { *v = b->volume; return 0; }
static HRESULT WINAPI buf_GetPan(Buffer *b, LONG *v) { *v = b->pan; return 0; }
static HRESULT WINAPI buf_GetFrequency(Buffer *b, DWORD *v) { *v = b->freq ? b->freq : b->fmt.nSamplesPerSec; return 0; }
static HRESULT WINAPI buf_GetStatus(Buffer *b, DWORD *s)
{
    lock();
    *s = b->playing ? (1 | (b->looping ? 4 : 0)) : 0;
    unlock();
    return 0;
}
static HRESULT WINAPI buf_Initialize(Buffer *b, void *ds, const void *desc) { (void)b; (void)ds; (void)desc; return 0; }

static HRESULT WINAPI buf_Lock(Buffer *b, DWORD off, DWORD bytes, void **p1, DWORD *b1, void **p2, DWORD *b2, DWORD flags)
{
    if (!b->data || !b->size)
        return DSERR_INVALIDPARAM;
    if (flags & 1) {   /* DSBLOCK_FROMWRITECURSOR */
        DWORD w;
        buf_GetCurrentPosition(b, NULL, &w);
        off = w;
    }
    if (flags & 2)     /* DSBLOCK_ENTIREBUFFER */
        bytes = b->size;
    off %= b->size;
    if (bytes > b->size)
        bytes = b->size;
    *p1 = b->data + off;
    if (off + bytes <= b->size) {
        *b1 = bytes;
        if (p2) *p2 = NULL;
        if (b2) *b2 = 0;
    } else {
        *b1 = b->size - off;
        if (p2) *p2 = b->data;
        if (b2) *b2 = bytes - *b1;
    }
    return 0;
}

static HRESULT WINAPI buf_Play(Buffer *b, DWORD r1, DWORD prio, DWORD flags)
{
    (void)r1; (void)prio;
    lock();
    b->playing = 1;
    b->looping = flags & 1;
    unlock();
    return 0;
}

static HRESULT WINAPI buf_SetCurrentPosition(Buffer *b, DWORD pos)
{
    int bpf = (b->fmt.nChannels ? b->fmt.nChannels : 1) * (b->fmt.wBitsPerSample == 8 ? 1 : 2);
    lock();
    b->pos = b->size ? (double)((pos % b->size) / bpf) : 0;
    unlock();
    return 0;
}

static HRESULT WINAPI buf_SetFormat(Buffer *b, const WAVEFORMATEX *f) { if (b->primary && f) b->fmt = *f; return 0; }
static HRESULT WINAPI buf_SetVolume(Buffer *b, LONG v) { b->volume = v; return 0; }
static HRESULT WINAPI buf_SetPan(Buffer *b, LONG v) { b->pan = v; return 0; }
static HRESULT WINAPI buf_SetFrequency(Buffer *b, DWORD v) { b->freq = v; return 0; }
static HRESULT WINAPI buf_Stop(Buffer *b)
{
    lock();
    b->playing = 0;
    unlock();
    return 0;
}
static HRESULT WINAPI buf_Unlock(Buffer *b, void *p1, DWORD b1, void *p2, DWORD b2) { (void)b; (void)p1; (void)b1; (void)p2; (void)b2; return 0; }
static HRESULT WINAPI buf_Restore(Buffer *b) { (void)b; return 0; }

static void *g_buf_vtbl[] = {
    buf_QueryInterface, buf_AddRef, buf_Release, buf_GetCaps, buf_GetCurrentPosition, buf_GetFormat, buf_GetVolume,
    buf_GetPan, buf_GetFrequency, buf_GetStatus, buf_Initialize, buf_Lock, buf_Play, buf_SetCurrentPosition,
    buf_SetFormat, buf_SetVolume, buf_SetPan, buf_SetFrequency, buf_Stop, buf_Unlock, buf_Restore,
};

/* ---- IDirectSound ---- */
typedef struct { DWORD dwSize, dwFlags, dwBufferBytes, dwReserved; const WAVEFORMATEX *lpwfxFormat; } DSBUFFERDESC;

static HRESULT WINAPI ds_QueryInterface(DSound *d, const void *iid, void **out) { (void)d; (void)iid; *out = NULL; return E_NOINTERFACE; }
static DWORD WINAPI ds_AddRef(DSound *d) { return ++d->refs; }
static DWORD WINAPI ds_Release(DSound *d)
{
    int r = --d->refs;
    if (r == 0)
        free(d);
    return r;
}

static Buffer *new_buffer(void)
{
    Buffer *b = calloc(1, sizeof *b);
    b->vtbl = g_buf_vtbl;
    b->refs = 1;
    return b;
}

static void add_buffer(Buffer *b)
{
    lock();
    b->next = g_buffers;
    g_buffers = b;
    unlock();
}

static HRESULT WINAPI ds_CreateSoundBuffer(DSound *d, const DSBUFFERDESC *desc, Buffer **out, void *outer)
{
    Buffer *b = new_buffer();
    (void)d; (void)outer;
    if (desc->dwFlags & 1) {   /* DSBCAPS_PRIMARYBUFFER */
        b->primary = 1;
        b->fmt = (WAVEFORMATEX){ 1, 2, (DWORD)g_rate, (DWORD)g_rate * 4, 4, 16, 0 };
    } else {
        if (!desc->lpwfxFormat || !desc->dwBufferBytes) {
            free(b);
            return DSERR_INVALIDPARAM;
        }
        b->fmt = *desc->lpwfxFormat;
        b->size = desc->dwBufferBytes;
        b->data = calloc(1, b->size);
        b->shared_refs = malloc(sizeof(int));
        *b->shared_refs = 1;
        if (b->fmt.wBitsPerSample == 8)
            memset(b->data, 0x80, b->size);
    }
    add_buffer(b);
    plat_trace("CreateSoundBuffer: %s %u bytes, %u Hz %u ch %u bit", b->primary ? "primary" : "secondary", b->size,
               b->fmt.nSamplesPerSec, b->fmt.nChannels, b->fmt.wBitsPerSample);
    *out = b;
    return 0;
}

typedef struct { DWORD dwSize, dwFlags; DWORD rest[22]; } DSCAPS;
static HRESULT WINAPI ds_GetCaps(DSound *d, DSCAPS *c)
{
    (void)d;
    memset(&c->dwFlags, 0, c->dwSize > 4 ? c->dwSize - 4 : 0);
    c->dwFlags = 0x0400 | 0x0200 | 0x0010 | 0x0020;   /* secondary 16 bit / 8 bit, stereo / mono */
    return 0;
}

static HRESULT WINAPI ds_DuplicateSoundBuffer(DSound *d, Buffer *src, Buffer **out)
{
    Buffer *b = new_buffer();
    (void)d;
    b->fmt = src->fmt;
    b->size = src->size;
    b->data = src->data;
    b->shared_refs = src->shared_refs;
    if (b->shared_refs)
        ++*b->shared_refs;
    b->volume = src->volume;
    b->pan = src->pan;
    b->freq = src->freq;
    add_buffer(b);
    *out = b;
    return 0;
}

static HRESULT WINAPI ds_SetCooperativeLevel(DSound *d, HANDLE w, DWORD l) { (void)d; (void)w; (void)l; return 0; }
static HRESULT WINAPI ds_Compact(DSound *d) { (void)d; return 0; }
static HRESULT WINAPI ds_GetSpeakerConfig(DSound *d, DWORD *c) { (void)d; *c = 4; return 0; }
static HRESULT WINAPI ds_SetSpeakerConfig(DSound *d, DWORD c) { (void)d; (void)c; return 0; }
static HRESULT WINAPI ds_Initialize(DSound *d, const void *g) { (void)d; (void)g; return 0; }

static void *g_ds_vtbl[] = {
    ds_QueryInterface, ds_AddRef, ds_Release, ds_CreateSoundBuffer, ds_GetCaps, ds_DuplicateSoundBuffer,
    ds_SetCooperativeLevel, ds_Compact, ds_GetSpeakerConfig, ds_SetSpeakerConfig, ds_Initialize,
};

WINFN(HRESULT, DirectSoundCreate, (const void *guid, DSound **out, void *outer))
{
    (void)guid; (void)outer;
    *out = NULL;
    if (getenv("GRIM_NOSOUND"))
        return DSERR_NODRIVER;
    if (!g_dev) {
        SDL_AudioSpec want, have;
        if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) {
            plat_log("SDL audio: %s (no sound)", SDL_GetError());
            return DSERR_NODRIVER;
        }
        memset(&want, 0, sizeof want);
        want.freq = 44100;
        want.format = AUDIO_S16SYS;
        want.channels = 2;
        want.samples = 1024;
        want.callback = mix;
        g_dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
        if (!g_dev) {
            plat_log("SDL audio device: %s (no sound)", SDL_GetError());
            return DSERR_NODRIVER;
        }
        g_rate = have.freq;
        SDL_PauseAudioDevice(g_dev, 0);
    }
    DSound *d = calloc(1, sizeof *d);
    d->vtbl = g_ds_vtbl;
    d->refs = 1;
    *out = d;
    return 0;
}
