/* Readable C for the Smush sound module ("insane_sound": SOUND insane, 0x004d0300 - 0x004d2340 and Sound_VoiceSampleCount):
 * the track manager that the Smush movie player feeds with sound chunks and that the DirectSound driver pulls the mixed
 * samples from.  Differential tests against the original machine code: build/mixdiff/snd_test.c (docs/notes/mixer.md).
 *
 * Model: up to 16 "voices" (SndVoice, 0x34 bytes) each own a ring buffer.  A chunk handed to SoundModule_PlayChunk
 * ("Crea" Creative VOC, "PSAD"/"PVOC"/"SAUD" Smush audio) is copied into a free or the least important voice.  The voice
 * data holds a small command stream (SAUD sub-chunks: 1 = play a block of samples, 2/8/9/10/11 = conditional jump on a
 * variable, 3 = set, 4 = add, 6/7 = start a sample run, anything else ends the voice); SoundModule_MixCallback runs it
 * for every voice (SndTrack, 0x3c bytes, the play state) and hands the PCM blocks to the mixer callback it is given. */
#include "ghidra_types.h"

#ifdef GRIM_EXE
#include "globals.h"
#include "functions.h"

typedef struct SndVoice {           /* 0x34 bytes, array at 0x008dad58 */
    byte *buffer;                   /* +00 ring buffer for the chunk data (size bytes) */
    byte *block;                    /* +04 0x1800 byte staging block for the PCM handed to the mixer */
    byte *chunk;                    /* +08 start of the chunk data in the buffer (command stream) */
    byte *pcm;                      /* +0c start of the sample data in the buffer */
    int size;                       /* +10 size of the buffer */
    signed char volume;             /* +14 -128..127 (0x7f = full) */
    signed char pan;                /* +15 */
    byte state;                     /* +16 0 free, 1 playing, 2 started (not yet picked up by the mixer), 3 stalled */
    byte format;                    /* +17 sample format 0..5 (see Mixer_MixVoiceByFormat) */
    uint flags;                     /* +18 bits 6,7: class (0 = effects, 1 = voice-over, 2 = music), low bits: priority */
    uint id;                        /* +1c sound id (0xffffff01 = none) */
    int age;                        /* +20 grows with every new sound, reset for the newest */
    uint ringSize;                  /* +24 bytes of the buffer used for sample data */
    uint received;                  /* +28 bytes of sample data received so far */
    uint position;                  /* +2c bytes played so far (+1 is what SoundModule_GetPosition reports) */
    uint total;                     /* +30 total bytes of the sound (SAUD header) */
} SndVoice;

typedef struct SndTrack {           /* 0x3c bytes, array at 0x008da8f0, one per voice: the play state */
    byte *cmd;                      /* +00 next command */
    byte *pcm;                      /* +04 sample data */
    int ringSize;                   /* +08 */
    int readPos;                    /* +0c read position in the ring */
    int remaining;                  /* +10 samples left in the current run */
    int rate;                       /* +14 sample rate of the current run */
    byte format;                    /* +18 */
    byte pad18[3];
    int prevState;                  /* +1c state of the voice at the end of the last call */
    int prevRate;                   /* +20 */
    int prevVolume;                 /* +24 */
    int blockLeft;                  /* +28 bytes left in the staging block */
    byte blockFormat;               /* +2c */
    byte pad2c[3];
    int fade;                       /* +30 0..16: fade in/out step while the ring runs dry */
    uint skip;                      /* +34 */
    uint skipLeft;                  /* +38 */
} SndTrack;

#define SND_VOICES 16
extern SndVoice g_aSndVoices[SND_VOICES] __asm__("_UINT_008dad58");
extern SndTrack g_aSndTracks[SND_VOICES] __asm__("_UINT_008da8f0");
extern int g_nSndVoiceCount __asm__("_UINT_004f3e30");
extern uint g_dwSndMasterVolume __asm__("_UINT_004f3e34");     /* default volume of sounds without one (0x7f), also read by command streams */
extern uint g_dwSndRate __asm__("_UINT_004f3e38");             /* sample rate the driver mixes at */
extern int g_nSndDuckMin __asm__("_UINT_004f3e3c");
extern uint g_dwSndDuckRate __asm__("_UINT_004f3e40");
extern int g_nSndDuckLevel __asm__("_UINT_004f3e44");          /* 0x100 = voices not ducked by music */
extern int g_bSndClearTracks __asm__("_UINT_004f3e48");
extern int g_anSndFormatBytes[6] __asm__("_DAT_004f3e18");     /* bytes per sample frame of the formats */
extern byte g_abSndVars[256] __asm__("_DAT_008db0e8");         /* variables of the command streams */
extern int g_bSndClass0 __asm__("_UINT_008dad44");             /* play effects / voice-over / music */
extern int g_bSndClass1 __asm__("_UINT_008dad40");
extern int g_bSndClass2 __asm__("_UINT_008dad4c");
extern int g_bSndSwapPan __asm__("_UINT_008dad50");
extern int *g_pSndMemory __asm__("_PTR_008da8a8");             /* "MEMORY workspace": allocator [0](size, file, line), free [1](ptr, file, line) */
extern int *g_pSndDriver __asm__("_PTR_008dacf0");             /* sound driver: [0] open(rate, voices, mixCallback), [1] close, [2], [3], [4] setRate, [5] getRate */
extern int *g_pSndServices __asm__("_PTR_008dacf8");           /* module manager service table */
extern int *g_pSndClock __asm__("_UINT_008dad48");             /* TIMER external_sync: [6] get sync time, [8] set */
extern int g_nSndMixCalls __asm__("_UINT_008dacf4");
extern int g_nSndPause __asm__("_UINT_008db1ec");
extern int g_bSndDriverOpen __asm__("_UINT_008db1f0");
extern int g_nSndSyncTime __asm__("_UINT_008db1f8");
extern double g_dSndClock __asm__("_DAT_008db200");
extern uint g_dwSndModuleSize __asm__("_UINT_008db098");
extern int g_nSndOpenRate __asm__("_UINT_008db09c");
extern uint g_dwSndDriverModuleSize __asm__("_UINT_008db0a0");
extern int g_nSndOpenLimit __asm__("_UINT_008dacfc");
extern uint g_adwSndBufferSizes[16] __asm__("_UINT_008dacb0");
extern int g_nSndTrackExtra __asm__("_DAT_008db1e8");
extern int g_anSndPlayCount[16] __asm__("_g_anSndChunkCount");     /* per voice: number of chunks received for a streamed sound */
extern int g_anSndStreamKeys[16] __asm__("_g_anSndStreamKey");
extern int g_anSndStreamFmt[16] __asm__("_g_anSndStreamKind");

typedef void *(*SndSvcGet)(const char *name, uint size);
typedef void (*SndSvcRegister)(const char *name, void *table);
typedef void (*SndSvcName)(const char *name);
typedef void *(*SndAlloc)(int size, const char *file, int line);
typedef void (*SndFree)(void *p, const char *file, int line);

#define SND_ALLOC(size, line) (((SndAlloc)g_pSndMemory[0])((size), s_C__grimsrc_libs_lecsmush_insane__004f3f30, (line)))
#define SND_FREE(p, line) (((SndFree)g_pSndMemory[1])((p), s_C__grimsrc_libs_lecsmush_insane__004f3f30, (line)))

#define BE32(p) ((uint)((p)[0] << 24 | (p)[1] << 16 | (p)[2] << 8 | (p)[3]))

/* ===================================================================================================================
 *  Module entry points (LECMODULE insane_sound / SOUND insane)
 * =================================================================================================================== */

int SoundModule_Register(int *services, uint moduleSize)
{
    int i;

    g_pSndServices = services;
    g_dwSndModuleSize = moduleSize;
    ((SndSvcRegister)services[0])(s_LECMODULE_insane_sound_004f3e5c, &g_apfnSoundModule);
    ((SndSvcRegister)g_pSndServices[0])(s_SOUND_insane_004f3e4c, &g_apfnSoundInterface);
    g_pSndDriver = 0;
    g_nSndOpenRate = 0x5622;
    g_nSndOpenLimit = 64000;
    g_nSndTrackExtra = 0;
    g_bSndSwapPan = 0;
    g_nSndMixCalls = 0;
    g_dwSndDriverModuleSize = 0;
    for (i = 0; i < 16; i++)
        g_adwSndBufferSizes[i] = (i > 0 ? 0 : 100000);
    g_adwSndBufferSizes[0] = 500000;
    return 0;
}

void SoundModule_Unregister(void)
{
    ((SndSvcName)g_pSndServices[1])(s_SOUND_insane_004f3e4c);
    ((SndSvcName)g_pSndServices[1])(s_LECMODULE_insane_sound_004f3e5c);
}

/* Gets the workspace allocator, the external sync clock and the sound driver from the module manager and opens the
 * sound system with the configured buffer sizes. */
int SoundModule_Init(void)
{
    uint driverSize;

    g_pSndMemory = ((SndSvcGet)g_pSndServices[2])(s_MEMORY_workspace_004f14ec, g_dwSndModuleSize);
    g_pSndClock = ((SndSvcGet)g_pSndServices[2])(s_TIMER_external_sync_004f3f1c, g_dwSndModuleSize);
    driverSize = g_dwSndDriverModuleSize;
    if (driverSize == 0)
        driverSize = g_dwSndModuleSize;
    g_pSndDriver = ((SndSvcGet)g_pSndServices[2])(s_SNDDRIVER_driver_004f3f08, driverSize);
    if (g_pSndMemory == 0) {
        ((SndSvcName)g_pSndServices[8])(s_Sound_Module__Cannot_allocate_me_004f3ed8);
        return -1;
    }
    if (g_pSndClock == 0) {
        ((SndSvcName)g_pSndServices[8])(s_Sound_Module__Cannot_allocate_ti_004f3ea8);
        return -1;
    }
    if (g_pSndDriver == 0) {
        ((SndSvcName)g_pSndServices[8])(s_Sound_Module__Cannot_allocate_sn_004f3e74);
        return -1;
    }
    return SoundModule_Open(g_nSndOpenRate, g_nSndOpenLimit, g_adwSndBufferSizes[0], g_adwSndBufferSizes[1],
                            g_adwSndBufferSizes[2], g_adwSndBufferSizes[3], g_adwSndBufferSizes[4], g_adwSndBufferSizes[5],
                            g_adwSndBufferSizes[6], g_adwSndBufferSizes[7], g_adwSndBufferSizes[8], g_adwSndBufferSizes[9],
                            g_adwSndBufferSizes[10], g_adwSndBufferSizes[11], g_adwSndBufferSizes[12],
                            g_adwSndBufferSizes[13], g_adwSndBufferSizes[14], g_adwSndBufferSizes[15], 0);
}

void SoundModule_Shutdown(void)
{
    ((SndSvcName)g_pSndServices[3])((const char *)g_pSndMemory);
    ((SndSvcName)g_pSndServices[3])((const char *)g_pSndDriver);
    ((SndSvcName)g_pSndServices[3])((const char *)g_pSndClock);
    SoundModule_Close();
}

/* rate / limit, then a zero terminated list of voice buffer sizes (one voice per entry).  Opens the driver with
 * SoundModule_MixCallback.  Returns 0 or -1. */
int SoundModule_Open(int rate, int limit, uint size, ...)
{
    __builtin_va_list ap;
    int i;

    g_nSndVoiceCount = 0;
    g_dwSndMasterVolume = 0x7f;
    for (i = 0; i < 0x100; i++)
        g_abSndVars[i] = 0;
    __builtin_va_start(ap, size);
    while (size != 0) {
        if (SoundModule_AddTrackBuffer(size & 0xfffffffc, limit) != 0) {
            __builtin_va_end(ap);
            SoundModule_Close();
            return -1;
        }
        size = __builtin_va_arg(ap, uint);
    }
    __builtin_va_end(ap);
    g_bSndDriverOpen = (((int (*)(int, int, void *))g_pSndDriver[0])(rate, g_nSndVoiceCount, SoundModule_MixCallback) == 0);
    g_dwSndRate = ((uint (*)(void))g_pSndDriver[5])();
    g_nSndMixCalls = 0;
    g_bSndClass1 = 1;
    g_bSndClass2 = 1;
    g_bSndClass0 = 1;
    ((void (*)(int))g_pSndClock[8])(0);
    return 0;
}

int SoundModule_Close(void)
{
    int i;

    if (g_bSndDriverOpen != 0) {
        ((void (*)(void))g_pSndDriver[1])();
        g_bSndDriverOpen = 0;
    }
    for (i = 0; i < g_nSndVoiceCount; i++) {
        if (g_aSndVoices[i].buffer != 0)
            SND_FREE(g_aSndVoices[i].buffer, 0x1a8);
        g_aSndVoices[i].buffer = 0;
        if (g_aSndVoices[i].block != 0)
            SND_FREE(g_aSndVoices[i].block, 0x1a9);
        g_aSndVoices[i].block = 0;
    }
    g_nSndVoiceCount = 0;
    return g_nSndMixCalls;
}

/* Adds a voice with a ring buffer of `size` bytes (reduced when the allocation fails, but never to less than `limit`
 * bytes; the buffer is filled with 0x7f).  Returns 0, -1 (no staging block) or -2 (no buffer). */
int SoundModule_AddTrackBuffer(uint size, int limit)
{
    SndVoice *v = &g_aSndVoices[g_nSndVoiceCount];
    int cur;

    v->state = 0;
    v->position = 0;
    v->flags = 0;
    v->id = 0xffffff01;
    v->buffer = 0;
    v->block = 0;
    v->size = size & 0xfffffffc;
    v->block = SND_ALLOC(0x1800, 0x1cf);
    if (v->block == 0)
        return -1;
    v->buffer = SND_ALLOC(v->size, 0x1d1);
    if (v->buffer == 0) {
        cur = v->size;
        while (limit < cur) {
            v->buffer = SND_ALLOC(v->size, 0x1d7);
            if (v->buffer != 0)
                break;
            cur = v->size - 10000;
            v->size = cur;
        }
        v->size = v->size & 0xfffffffc;
        if (limit < v->size) {
            if (v->buffer != 0)
                SND_FREE(v->buffer, 0x1e2);
            v->buffer = 0;
            limit = v->size - limit;
            v->size = limit;
            v->buffer = SND_ALLOC(limit, 0x1e5);
            if (v->buffer != 0)
                goto filled;
        }
        if (v->block != 0)
            SND_FREE(v->block, 0x1ee);
        v->block = 0;
        return -2;
    }
filled:
    FUN_004d5e50(v->buffer, 0x7f, v->size);
    g_nSndVoiceCount++;
    return 0;
}

/* ===================================================================================================================
 *  Chunks
 * =================================================================================================================== */

/* A sound chunk: dispatch on its four character tag.  id / volume / pan / flags as for SoundModule_PlaySaud. */
void SoundModule_PlayChunk(byte *p, int id, int volume, int pan, uint flags)
{
    uint tag;

    if (g_bSndDriverOpen == 0)
        return;
    tag = BE32(p);
    if (tag < 0x50534145) {
        if (tag != 0x50534144) {                         /* 'PSAD' */
            byte b;
            int hdr;
            if (tag != 0x43726561)                       /* 'Crea'(tive Voice File) */
                return;
            hdr = p[0x15] * 0x100 + p[0x14];
            b = p[hdr + 1];
            SoundModule_PlayVoc(p + hdr + 6, (ushort)(b << 8 | b) * 0x100 + b, id, volume, pan, flags);
            return;
        }
    } else if (tag != 0x50564f43) {                      /* 'PVOC' */
        if (tag != 0x53415544)                           /* 'SAUD' */
            return;
        SoundModule_PlaySaud(p, BE32(p + 4) + 8, id, volume, pan, flags, 0, 0, 1, 0);
        return;
    }
    if (p[8] == 0 && p[9] == 0 && p[0xc] == 0 && p[0xd] == 0 && p[0x10] == 0 && p[0x11] == 0) {
        SoundModule_PlaySaud(p + 0x14, BE32(p + 4) - 0xc, id, volume, pan, flags, (p[10] << 8) | p[0xb],
                             (p[0xe] << 8) | p[0xf], (p[0x12] << 8) | p[0x13], 1);
        return;
    }
    if ((signed char)p[0x11] < -0x7f)
        pan = 0x80;
    else
        pan = pan + (signed char)p[0x11];
    SoundModule_PlaySaud(p + 0x12, BE32(p + 4) - 10, id, (int)(p[0x10] * (uint)volume) >> 7, pan,
                         (int)*(short *)(p + 0xe) | flags, (int)*(short *)(p + 8), (int)*(short *)(p + 10),
                         (int)*(short *)(p + 0xc), 1);
}

/* ===================================================================================================================
 *  Simple accessors
 * =================================================================================================================== */

/* Stops the sound with the given id */
void SoundModule_StopSound(uint id)
{
    int i;

    for (i = 0; i < g_nSndVoiceCount; i++) {
        if (g_aSndVoices[i].id == id) {
            g_aSndVoices[i].state = 0;
            g_aSndVoices[i].id = 0xffffff01;
        }
    }
}

void SoundModule_Pause(void)
{
    g_nSndPause++;
}

void SoundModule_Resume(void)
{
    if (g_nSndPause != 0)
        g_nSndPause--;
}

void SoundModule_StopAll(void)
{
    int i;

    for (i = 0; i < g_nSndVoiceCount; i++) {
        g_aSndVoices[i].state = 0;
        g_aSndVoices[i].id = 0xffffff01;
    }
}

/* id -255: the default volume for sounds that do not carry one; otherwise the volume of the sound with that id */
void SoundModule_SetVolume(int id, uint volume)
{
    int i;

    if (id == -0xff) {
        g_dwSndMasterVolume = volume;
        return;
    }
    for (i = 0; i < g_nSndVoiceCount; i++) {
        if ((int)g_aSndVoices[i].id == id)
            g_aSndVoices[i].volume = (signed char)volume;
    }
}

uint SoundModule_GetVolume(uint id)
{
    int i;

    if (id == 0xffffff01)
        return g_dwSndMasterVolume;
    for (i = 0; i < g_nSndVoiceCount; i++) {
        if (g_aSndVoices[i].id == id)
            return (int)g_aSndVoices[i].volume;
    }
    return 0xffffffff;
}

void SoundModule_SetPan(int id, byte pan)
{
    int i;

    for (i = 0; i < g_nSndVoiceCount; i++) {
        if ((int)g_aSndVoices[i].id == id)
            g_aSndVoices[i].pan = (signed char)pan;
    }
}

int SoundModule_GetPan(uint id)
{
    int i;

    for (i = 0; i < g_nSndVoiceCount; i++) {
        if (g_aSndVoices[i].id == id)
            return (int)g_aSndVoices[i].pan;
    }
    return -1;
}

void SoundModule_DriverCommand2(int arg)
{
    if (g_pSndDriver != 0)
        ((void (*)(int))g_pSndDriver[2])(arg);
}

int SoundModule_DriverCommand3(void)
{
    if (g_pSndDriver != 0)
        return ((int (*)(void))g_pSndDriver[3])();
    return -1;
}

void SoundModule_SetDriverRate(uint rate)
{
    g_dwSndRate = rate;
    if (g_pSndDriver != 0)
        ((void (*)(uint))g_pSndDriver[4])(rate);
}

/* bytes played of a sound (+1), or of the first playing one (id 0xffffff01); a negative id counts voices from the end */
int SoundModule_GetPosition(uint id)
{
    int i;

    if (id == 0xffffff01) {
        for (i = 0; i < g_nSndVoiceCount; i++) {
            if (g_aSndVoices[i].state != 0)
                return g_aSndVoices[i].position + 1;
        }
        return 0;
    }
    if ((int)id < 0 && (int)(-1 - id) < g_nSndVoiceCount) {
        if (g_aSndVoices[-(int)(id + 1)].state != 0)
            return g_aSndVoices[-(int)(id + 1)].position + 1;
        return 0;
    }
    for (i = 0; i < g_nSndVoiceCount; i++) {
        if (g_aSndVoices[i].id == id) {
            if (g_aSndVoices[i].state != 0)
                return g_aSndVoices[i].position + 1;
            return 0;
        }
    }
    return 0;
}

/* Length of the played part of voice `voice` in milliseconds */
int Sound_VoiceSampleCount(int voice)
{
    int bytes = g_aSndVoices[voice].position;

    switch (g_aSndVoices[voice].format) {
    case 0:
        break;
    case 1:
    case 2:
    case 4:
        bytes = bytes >> 1;
        break;
    case 3:
    case 5:
        bytes = bytes >> 2;
        break;
    default:
        goto count;
    }
    voice = bytes;
count:
    {
        double samples = (double)voice;
        int rate = Sound_DriverQuery();
        return (int)(long long)(samples / ((double)rate * 0.001));
    }
}

int SoundModule_SetParam(int unused, int which, uint a, uint b)
{
    switch (which) {
    case 1:
        SoundModule_SetChannelVolume(a, b);
        return 0;
    case 2:
        if (a != 0)
            g_nSndDuckMin = a;
        if (b != 0) {
            g_dwSndDuckRate = b;
            return 0;
        }
        break;
    case 3:
        g_bSndClass1 = a;
        return 0;
    case 4:
        g_bSndClass2 = a;
        return 0;
    case 5:
        g_bSndClass0 = a;
        break;
    default:
        return -1;
    }
    return 0;
}

int SoundModule_GetParam(int unused, int which, uint *a, uint *b)
{
    switch (which) {
    case 1:
        if (a != 0) {
            *a = SoundModule_GetChannelVolume((byte)(uint)b) & 0xff;
            return 0;
        }
        break;
    case 2:
        if (a != 0)
            *a = g_nSndDuckMin;
        if (b != 0) {
            *b = g_dwSndDuckRate;
            return 0;
        }
        break;
    case 3:
        if (a != 0) {
            *a = g_bSndClass1;
            return 0;
        }
        break;
    case 4:
        if (a != 0) {
            *a = g_bSndClass2;
            return 0;
        }
        break;
    case 5:
        if (a != 0)
            *a = g_bSndClass0;
        break;
    default:
        return -1;
    }
    return 0;
}

uint SoundModule_GetChannelVolume(byte channel)
{
    if (channel == 0xff)
        return (byte)g_dwSndMasterVolume;
    return g_abSndVars[channel];
}

void SoundModule_SetChannelVolume(byte channel, byte value)
{
    if (channel == 0xff)
        g_dwSndMasterVolume = value;
    g_abSndVars[channel] = value;
}

void SoundModule_SyncClock(void)
{
    g_nSndSyncTime = ((int (*)(void))g_pSndClock[6])();
}

/* Adds `ms` (a double count of timer ticks, 1193180 Hz) to the clock and passes the whole ticks to the sync clock;
 * when the clock was resynchronised (g_nSndSyncTime set by SoundModule_SyncClock) and the external time has moved on, the
 * difference is taken off again. */
void SoundModule_AdvanceClock(double ticks)
{
    int ext;
    int whole;

    g_dSndClock = g_dSndClock + ticks;
    if (g_nSndSyncTime != 0) {
        ext = ((int (*)(void))g_pSndClock[6])();
        if (g_nSndSyncTime < ext) {
            int diff = ext - g_nSndSyncTime;
            if (diff / 5 < 0x1234dc) {
                g_nSndSyncTime = 0;
                g_dSndClock = g_dSndClock - (double)diff;
            }
        }
    }
    whole = (int)(long long)g_dSndClock;
    ((void (*)(int))g_pSndClock[8])(whole);
    whole = (int)(long long)g_dSndClock;
    g_dSndClock = g_dSndClock - (double)whole;
}

/* ===================================================================================================================
 *  Receiving sounds
 * =================================================================================================================== */

/* A Creative Voice file payload (raw samples, 8 bit mono) as a one-run sound: picks a voice (free, or stalled, or of
 * lower priority; the one with the smallest buffer that fits the sound wins, then the oldest), writes a minimal SAUD
 * header + `src` into its buffer and starts it. */
void SoundModule_PlayVoc(byte *src, uint size, int id, int volume, int pan, uint flags)
{
    int last = g_nSndVoiceCount - 1;
    int top = 0;
    int i, best, bestDist, idx, score[16];

    for (i = last; i >= 0; i--) {
        if (top < g_aSndVoices[i].size)
            top = g_aSndVoices[i].size;
    }
    /* the smallest buffer that is larger than the sound (top stays the largest buffer when none fits) */
    bestDist = 10000000;
    for (i = last; i >= 0; i--) {
        int sz = g_aSndVoices[i].size;
        int d = sz - (int)size;
        int dist = d < 0 ? (int)size - sz : d;
        if (dist < bestDist && (int)size < sz) {
            bestDist = d < 0 ? (int)size - sz : d;
            top = sz;
        }
    }
    for (i = last; i >= 0; i--) {
        SndVoice *v = &g_aSndVoices[i];
        score[i] = 0;
        if (v->size == top && (v->state == 0 || v->state == 3 || (int)v->flags <= (int)flags)) {
            if (v->state == 0)
                score[i] = 0x1000;
            if ((int)v->flags < (int)flags)
                score[i] += 0x800;
            if (v->flags == flags)
                score[i] += 0x400;
            if (v->state == 3)
                score[i] += 0x200;
            score[i] += v->age + 1;
        }
    }
    best = 0;
    idx = -1;
    for (i = last; i >= 0; i--) {
        if (score[i] > best) {
            idx = i;
            best = score[i];
        }
    }
    if (idx >= 0) {
        SndVoice *v = &g_aSndVoices[idx];
        byte *b;

        for (i = last; i >= 0; i--) {
            if (g_aSndVoices[i].age < 0x100)
                g_aSndVoices[i].age++;
        }
        v->age = 0;
        v->state = 0;
        b = v->buffer;
        b[0] = 1;
        b[1] = 8;
        b[2] = 0; b[3] = 0; b[4] = 0; b[5] = 0;
        b[6] = (byte)(size >> 24);
        b[7] = (byte)(size >> 16);
        b[8] = (byte)(size >> 8);
        b[9] = (byte)size;
        b[10] = 0;
        b[11] = 0;
        Insane_MemCopyCdecl(v->buffer + 12, src, size);
        v->chunk = v->buffer;
        v->pcm = v->buffer + 12;
        v->ringSize = v->size - 12;
        v->received = size;
        v->id = id;
        v->volume = (signed char)volume;
        v->pan = (signed char)pan;
        v->flags = flags;
        v->position = 0;
        v->state = 2;
    }
}

/* One SAUD / PSAD sound chunk.  chunkNo == 0: the first chunk of a sound: choose a voice as SoundModule_PlayVoc does
 * (buffers close in size to the announced length first) and copy the header and what is there.  Otherwise (chunkNo
 * counts the following chunks, key identifies the stream): append the data to the ring buffer of that stream. */
void SoundModule_PlaySaud(byte *data, int size, int id, int volume, int pan, uint flags, int key, int chunkNo,
                          int kind, int whole)
{
    SndVoice *v;
    int i, j, idx, need, top, bestDist, best;
    int score[16];

    if (chunkNo == 0) {
        need = 0;
        if (kind != 1 || whole != 0)
            need = (int)BE32(data + 4);
        top = 0;
        for (i = g_nSndVoiceCount - 1; i >= 0; i--) {
            if (top < g_aSndVoices[i].size)
                top = g_aSndVoices[i].size;
        }
        chunkNo = top;                  /* (the original reuses the parameter) */
        bestDist = 10000000;
        if ((flags & 0xc0) == 0x40) {
            if (1 < kind)
                SoundModule_SyncClock();
        } else {
            for (i = g_nSndVoiceCount - 1; i >= 0; i--) {
                int sz = g_aSndVoices[i].size;
                int d = sz - need;
                int dist = d < 0 ? need - sz : d;
                if (dist < bestDist && (need * 2) / 3 < sz) {
                    int limit = size;
                    if (1 < kind)
                        limit = size * 2;
                    if (limit < sz) {
                        bestDist = d;
                        chunkNo = sz;
                        if (d < 0)
                            bestDist = need - sz;
                    }
                }
            }
        }
        for (i = g_nSndVoiceCount - 1; i >= 0; i--) {
            v = &g_aSndVoices[i];
            score[i] = 0;
            if (v->size == chunkNo) {
                if (v->state == 0) {
                    score[i] = 0x1000;
                } else if (v->state != 3 && (int)flags < (int)v->flags) {
                    continue;
                }
                if ((int)v->flags < (int)flags)
                    score[i] += 0x800;
                if (v->flags == flags)
                    score[i] += 0x400;
                if (v->state == 3)
                    score[i] += 0x200;
                score[i] += v->age + 1;
            }
        }
        best = -1;
        idx = -1;
        for (i = g_nSndVoiceCount - 1; i >= 0; i--) {
            if (score[i] != 0 && best < score[i]) {
                idx = i;
                best = score[i];
            }
        }
        if (idx >= 0) {
            int hdr, bytes;
            byte b0, b1, b2, b3;
            uint magic;

            v = &g_aSndVoices[idx];
            for (i = g_nSndVoiceCount - 1; i >= 0; i--) {
                if (g_aSndVoices[i].age < 0xff)
                    g_aSndVoices[i].age++;
            }
            g_anSndStreamKeys[idx] = key;
            g_anSndStreamFmt[idx] = kind;
            g_anSndPlayCount[idx] = 0;
            v->age = 0;
            v->state = 0;
            hdr = (int)BE32(data + 0xc);
            b1 = data[hdr + 0x15];
            b2 = data[hdr + 0x16];
            b0 = data[hdr + 0x14];
            b3 = data[hdr + 0x17];
            if (kind == 1 && whole == 0) {
                v->chunk = data + 0x10;
                bytes = size;
            } else {
                bytes = v->size;
                if (size < v->size)
                    bytes = size;
                Insane_MemCopyCdecl(v->buffer, data, bytes);
                v->chunk = v->buffer + 0x10;
                bytes = v->size;
            }
            v->ringSize = (bytes - hdr) - 0x18;
            v->pcm = v->chunk + hdr + 8;
            v->received = (size - hdr) - 0x18;
            v->total = (uint)b0 << 24 | (uint)b1 << 16 | (uint)b2 << 8 | b3;
            v->id = id;
            v->volume = 0x7f;
            v->pan = 0;
            if (-1 < volume && volume < 0x80)
                v->volume = (signed char)volume;
            if (-0x80 < pan && pan < 0x80)
                v->pan = (signed char)pan;
            v->flags = flags;
            v->position = 0;
            v->state = 2;
            magic = BE32(v->pcm - 8);
            v->format = 0;
            if (magic == 0x5336535a)         /* 'S6SZ' */
                v->format = 5;
            else if (magic == 0x53364d5a)    /* 'S6MZ' */
                v->format = 4;
            else if (magic == 0x53443253)    /* 'SD2S' */
                v->format = 1;
            else if (magic == 0x5344364d)    /* 'SD6M' */
                v->format = 2;
            else if (magic == 0x53443653)    /* 'SD6S' */
                v->format = 3;
            else if (magic == 0x53443853)    /* 'SD8S' */
                v->format = 1;
        }
    } else {
        for (j = g_nSndVoiceCount - 1; j >= 0; j--) {
            if (g_aSndVoices[j].state != 0 && key == g_anSndStreamKeys[j] && chunkNo == g_anSndPlayCount[j] + 1 &&
                kind == g_anSndStreamFmt[j])
                break;
        }
        if (j < 0)
            return;
        v = &g_aSndVoices[j];
        g_anSndPlayCount[j]++;
        {
            int ring = (int)v->ringSize;
            int off = (int)v->received % ring;
            byte *dst;
            int n;

            if (ring < off + size) {
                Insane_MemCopyCdecl(v->pcm + off, data, ring - off);
                data = (data - off) + v->ringSize;
                dst = v->pcm;
                n = (off + size) - v->ringSize;
            } else {
                dst = v->pcm + off;
                n = size;
            }
            Insane_MemCopyCdecl(dst, data, n);
        }
        if (-1 < volume && volume < 0x7f)
            v->volume = (signed char)volume;
        if (-0x80 < pan && pan < 0x80)
            v->pan = (signed char)pan;
        v->received = v->received + size;
    }
}

/* ===================================================================================================================
 *  Mixing
 * =================================================================================================================== */

typedef void (*SndMixFn)(void *data, int accumOffset, int outFrames, int srcBytes, int unused, int volume, int pan, int format);

/* Called by the driver (DSound_FillStreamBuffer) for every block it needs: `frames` output frames at the driver's rate.
 * Every voice contributes the samples that belong to this time slice through mix() (Mixer_MixVoiceByFormat), after its
 * command stream has been run up to the next sample run. */
void SoundModule_MixCallback(int frames, void *mixFn)
{
    SndMixFn mix = (SndMixFn)mixFn;
    int vi;
    int duck = 0;                           /* a music voice played: lower the others */

    g_nSndMixCalls++;
    SoundModule_AdvanceClock(((double)frames * 1193180.0) / (double)(int)g_dwSndRate);
    if (g_nSndPause != 0)
        return;

    if (g_bSndClearTracks != 0) {
        g_bSndClearTracks = 0;
        for (vi = 0; vi < SND_VOICES; vi++) {
            g_aSndTracks[vi].blockLeft = 0;
            g_aSndTracks[vi].skipLeft = 0;
        }
    }

    for (vi = 0; vi < g_nSndVoiceCount; vi++) {
        SndVoice *v = &g_aSndVoices[vi];
        SndTrack *t = &g_aSndTracks[vi];
        uint prio = v->flags & 0xc0;
        int audible;
        int vol;                            /* volume of the voice 0..127 */
        int outLeft, outPos;

        audible = (prio == 0x80 && g_bSndClass2 != 0) || (prio == 0x40 && g_bSndClass1 != 0) ||
                  (prio == 0 && g_bSndClass0 != 0);
        vol = (int)(g_dwSndMasterVolume * (int)v->volume) / 0x7f;
        if (prio == 0x40 && g_bSndClass2 != 0)
            vol = (vol * g_nSndDuckLevel) >> 8;

        /* -- hand the next block of a freshly started or streaming voice over to the staging block -- */
        if (v->state == 2 && t->prevState == 1) {
            int off = t->readPos % t->ringSize;
            int n;

            t->blockLeft = 0x1800;
            t->prevVolume = (int)v->volume;
            t->blockFormat = v->format;
            t->prevRate = t->rate;
            Dsnd_MemFillCdecl(v->block, 0x80, 0x1800);
            n = t->ringSize - off;
            if (n > 0x1800)
                n = 0x1800;
            Dsnd_MemCopyCdecl(v->block, t->pcm + off, n);
            t->fade = 0;
        } else if (v->state == 1 && t->readPos < (int)((v->received - v->ringSize) + 15000) && (int)v->received < (int)v->total) {
            int n;

            t->fade = 0;
            n = (v->received - t->readPos) - 15000;
            if (t->remaining < n)
                n = t->remaining;
            if ((int)v->total - t->ringSize < n + t->readPos)
                n = ((int)v->total - t->ringSize) - t->readPos;
            if (0 < n) {
                t->blockLeft = 0x1800;
                t->prevRate = t->rate;
                Dsnd_MemCopyCdecl(v->block, t->pcm + t->readPos % t->ringSize, 0x1800);
                t->readPos += n;
                t->remaining -= n;
            }
        }

        /* -- mix what is left of the staging block -- */
        if (g_anSndFormatBytes[t->blockFormat] < t->blockLeft) {
            int want = (frames * g_anSndFormatBytes[t->blockFormat] * t->prevRate) / (int)g_dwSndRate;
            int n = t->blockLeft;

            outPos = 0;
            if (want <= n)
                n = want;
            n = n - (n % 4);
            while (3 < n) {
                int chunk = n;
                int out;

                if (0x400 < chunk)
                    chunk = 0x400;
                if (chunk == want)
                    out = frames;
                else
                    out = ((chunk / g_anSndFormatBytes[t->blockFormat]) * (int)g_dwSndRate) / t->prevRate;
                if (audible) {
                    int pan = (int)v->pan;
                    if (g_bSndSwapPan != 0)
                        pan = -pan;
                    mix((v->block - t->blockLeft) + 0x1800, outPos, out, chunk, 1,
                        (int)(g_dwSndMasterVolume * t->blockLeft * t->prevVolume) / 0xbe800, pan, t->blockFormat);
                }
                outPos += out;
                n -= chunk;
                t->blockLeft -= chunk;
            }
        }

        /* -- a voice that was just started: rewind its command stream -- */
        if (v->state == 2) {
            if (t->prevState != 1)
                t->fade = 0x10;
            t->cmd = v->chunk;
            t->pcm = v->pcm;
            t->ringSize = v->ringSize;
            t->format = v->format;
            t->remaining = 0;
            t->skipLeft = 0;
            v->state = 1;
        }

        /* -- run the voice for this slice -- */
        if (v->state != 0) {
            outPos = 0;
            outLeft = frames;
            while (0 < outLeft) {
                if (0 < t->remaining) {
                    int off = t->readPos % t->ringSize;
                    int bytes = (g_anSndFormatBytes[t->format] * outLeft * t->rate) / (int)g_dwSndRate;
                    int n = t->remaining;
                    int out;

                    if (bytes <= n)
                        n = bytes;
                    if (t->ringSize < off + n)
                        n = t->ringSize - off;
                    if ((int)v->received < t->readPos + n) {
                        /* the data has not arrived yet: step back, fade out */
                        if (t->fade != 0)
                            t->fade--;
                        v->state = 3;
                        if (0x400 < n)
                            n = 0x400;
                        t->readPos -= n;
                        t->remaining += n;
                        off = t->readPos % t->ringSize;
                    } else {
                        if (t->fade < 0x10)
                            t->fade++;
                        if (0x400 < n)
                            n = 0x400;
                        v->state = 1;
                        if ((v->flags & 0xc0) == 0x80)
                            duck = 1;
                    }
                    out = outLeft;
                    if (n != bytes)
                        out = ((n / g_anSndFormatBytes[t->format]) * (int)g_dwSndRate) / t->rate;
                    if (audible) {
                        int pan = (int)v->pan;
                        if (g_bSndSwapPan != 0)
                            pan = -pan;
                        mix(t->pcm + off, outPos, out, n, 1, (vol * t->fade) >> 4, pan, t->format);
                    }
                    outLeft -= out;
                    t->remaining -= n;
                    outPos += out;
                    t->readPos += n;
                }
                /* the next command(s) while no samples are pending */
                while (t->remaining < 1) {
                    byte *c;
                    uint limit;

                    if (outLeft == 0)
                        goto voiceDone;
                    c = t->cmd;
                    switch (c[0]) {
                    case 1:         /* sample run at the driver's rate: pos, count */
                    case 6:         /* sample run: pos, count, rate */
                        t->skipLeft = 0;
                        t->readPos = (int)BE32(c + 2);
                        t->remaining = (int)BE32(c + 6);
                        t->rate = c[0] == 1 ? (int)g_dwSndRate : (int)BE32(c + 10);
                        t->cmd = c + c[1] + 2;
                        goto checkRun;
                    case 7:         /* sample run played in several slices of at most `count` */
                        if (t->skipLeft == 0) {
                            t->skipLeft = BE32(c + 6);
                            t->skip = 0;
                        }
                        t->readPos = (int)(BE32(c + 2) + t->skip);
                        limit = BE32(c + 0xe);
                        if (t->skipLeft < limit)
                            limit = t->skipLeft;
                        t->remaining = (int)limit;
                        t->rate = (int)BE32(c + 10);
                        t->skipLeft -= t->remaining;
                        t->skip += t->remaining;
                        if (t->skipLeft != 0)
                            t->cmd = c + c[1] + 2;
                        else
                            t->cmd = c + (((int)(short)(c[0x12] << 8)) | c[0x13]);
                    checkRun:
                        /* drop the part of the run that the data has not reached yet */
                        limit = v->received + ((int)v->total <= (int)v->received ? 0 : 15000) - v->ringSize;
                        if (t->readPos < (int)limit) {
                            int skip = (v->received - t->readPos - v->ringSize) + 15000;
                            if (skip > t->remaining) {
                                v->state = 0;
                                v->id = 0xffffff01;
                                outLeft = 0;
                            } else {
                                t->readPos += skip;
                                t->remaining -= skip;
                            }
                        }
                        break;
                    case 2: case 8: case 9: case 10: case 11: {   /* if (var <cmp> imm) jump */
                        byte sel = c[4];
                        byte var, res = 0;

                        if (sel == 0xff)
                            var = (byte)g_dwSndMasterVolume;
                        else if (sel == 0xfe)
                            var = (byte)v->volume;
                        else if (sel == 0xfd)
                            var = (byte)v->pan;
                        else
                            var = g_abSndVars[sel];
                        switch (c[0]) {
                        case 2:  res = var != 0 || sel == 0; break;    /* var != 0, or var 0 */
                        case 8:  res = c[5] < var; break;
                        case 9:  res = var < c[5]; break;
                        case 10: res = var == c[5]; break;
                        case 11: res = var != c[5]; break;
                        }
                        if (res != 0)
                            t->cmd = c + (((int)(short)(c[2] << 8)) | c[3]);
                        else
                            t->cmd = c + c[1] + 2;
                        break; }
                    case 3:         /* var = imm */
                        if (c[2] == 0xff) {
                            g_dwSndMasterVolume = c[3];
                        } else if (c[2] == 0xfe) {
                            v->volume = (signed char)c[3];
                            vol = (int)(g_dwSndMasterVolume * (int)(signed char)c[3]) / 0x7f;
                            if ((v->flags & 0xc0) == 0x40 && g_bSndClass2 != 0)
                                vol = (vol * g_nSndDuckLevel) >> 8;
                        } else if (c[2] == 0xfd) {
                            v->pan = (signed char)c[3];
                        } else {
                            g_abSndVars[c[2]] = c[3];
                        }
                        t->cmd = c + c[1] + 2;
                        break;
                    case 4:         /* var += imm */
                        if (c[2] == 0xff)
                            g_dwSndMasterVolume += c[3];
                        else if (c[2] == 0xfe)
                            v->volume += c[3];
                        else if (c[2] == 0xfd)
                            v->pan += c[3];
                        else
                            g_abSndVars[c[2]] += c[3];
                        t->cmd = c + c[1] + 2;
                        break;
                    default:        /* end of the sound */
                        v->state = 0;
                        v->id = 0xffffff01;
                        outLeft = 0;
                        break;
                    }
                }
            }
        }
    voiceDone:
        v->position = t->readPos;
        t->prevState = v->state;
    }

    if (duck) {
        if (g_nSndDuckMin < g_nSndDuckLevel) {
            g_nSndDuckLevel -= (int)(frames * g_dwSndDuckRate) >> 13;
            if (g_nSndDuckLevel < g_nSndDuckMin)
                g_nSndDuckLevel = g_nSndDuckMin;
        }
    } else if (g_nSndDuckLevel < 0x100) {
        g_nSndDuckLevel += (int)(frames * g_dwSndDuckRate) >> 15;
        if (0x100 < g_nSndDuckLevel)
            g_nSndDuckLevel = 0x100;
    }
}


#endif /* GRIM_EXE */
