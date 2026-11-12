/* WINMM: the clock, multimedia timers (iMUSE's tick) and the joystick API (no joysticks); DDRAW: no devices. */
#define _GNU_SOURCE
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "platform.h"

WINFN(DWORD, timeGetTime, (void)) { return plat_ms(); }
WINFN(UINT, timeBeginPeriod, (UINT p)) { (void)p; return 0; }
WINFN(UINT, timeEndPeriod, (UINT p)) { (void)p; return 0; }
WINFN(UINT, timeGetDevCaps, (UINT *caps, UINT size))
{
    if (size >= 8) {
        caps[0] = 1;          /* wPeriodMin */
        caps[1] = 1000000;    /* wPeriodMax */
    }
    return 0;
}

/* timeSetEvent: a thread that calls the callback every `delay` ms (TIME_PERIODIC) or once */
typedef void (WINAPI *TimerProc)(UINT id, UINT msg, DWORD user, DWORD dw1, DWORD dw2);
typedef struct Timer {
    UINT id, delay, periodic;
    TimerProc cb;
    DWORD user;
    volatile int stop;
    pthread_t thread;
    struct Timer *next;
} Timer;
static Timer *g_timers;
static UINT g_next_timer = 1;
static pthread_mutex_t g_timer_lock = PTHREAD_MUTEX_INITIALIZER;

static void *timer_main(void *p)
{
    Timer *t = p;
    struct timespec next;
    plat_fpu_windows();
    clock_gettime(CLOCK_MONOTONIC, &next);
    do {
        next.tv_nsec += (long)t->delay * 1000000L;
        while (next.tv_nsec >= 1000000000L)
            next.tv_sec++, next.tv_nsec -= 1000000000L;
        while (clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &next, NULL) != 0) {}
        if (t->stop)
            break;
        t->cb(t->id, 0, t->user, 0, 0);
        {   /* behind by more than a few periods (debugger, slow frame): do not run a burst of catch-up ticks */
            struct timespec now;
            clock_gettime(CLOCK_MONOTONIC, &now);
            if ((now.tv_sec - next.tv_sec) * 1000 + (now.tv_nsec - next.tv_nsec) / 1000000 > 5 * (long)t->delay)
                next = now;
        }
    } while (t->periodic && !t->stop);
    return NULL;
}

WINFN(UINT, timeSetEvent, (UINT delay, UINT res, TimerProc cb, DWORD user, UINT flags))
{
    Timer *t = calloc(1, sizeof *t);
    (void)res;
    t->delay = delay ? delay : 1;
    t->periodic = flags & 1;
    t->cb = cb;
    t->user = user;
    pthread_mutex_lock(&g_timer_lock);
    t->id = g_next_timer++;
    t->next = g_timers;
    g_timers = t;
    pthread_mutex_unlock(&g_timer_lock);
    if (pthread_create(&t->thread, NULL, timer_main, t) != 0)
        return 0;
    return t->id;
}

WINFN(UINT, timeKillEvent, (UINT id))
{
    Timer *t = NULL;
    pthread_mutex_lock(&g_timer_lock);
    for (Timer **p = &g_timers; *p; p = &(*p)->next) {
        if ((*p)->id == id) {
            t = *p;
            *p = t->next;
            break;
        }
    }
    pthread_mutex_unlock(&g_timer_lock);
    if (!t)
        return 97;   /* MMSYSERR_INVALPARAM */
    t->stop = 1;
    if (pthread_equal(t->thread, pthread_self()))
        pthread_detach(t->thread);
    else
        pthread_join(t->thread, NULL);
    /* (a detached timer thread still reads t until it returns: leaked on purpose) */
    if (!pthread_equal(t->thread, pthread_self()))
        free(t);
    return 0;
}

/* joysticks: none (SDL game controllers are not wired up yet) */
#define JOYERR_UNPLUGGED 167
WINFN(UINT, joyGetNumDevs, (void)) { return 0; }
WINFN(UINT, joyGetDevCapsA, (UINT id, void *caps, UINT size)) { (void)id; (void)caps; (void)size; return JOYERR_UNPLUGGED; }
WINFN(UINT, joyGetPos, (UINT id, void *pos)) { (void)id; (void)pos; return JOYERR_UNPLUGGED; }
WINFN(UINT, joyGetPosEx, (UINT id, void *pos)) { (void)id; (void)pos; return JOYERR_UNPLUGGED; }

/* DirectDraw: no devices. The game always adds its own "Window Display Device" (a DIB section, gdi32.c) first. */
WINFN(HRESULT, DirectDrawEnumerateA, (void *cb, void *ctx)) { (void)cb; (void)ctx; return 0; }
WINFN(HRESULT, DirectDrawCreate, (void *guid, void **dd, void *outer))
{
    (void)guid; (void)outer;
    if (dd)
        *dd = NULL;
    return 0x887600ffu;   /* DDERR_NODIRECTDRAWHW */
}

/* comctl32 */
WINFN(void, InitCommonControls, (void)) {}
