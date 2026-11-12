/* Entry point, logging, clocks and the handle table of the native Linux build. */
#define _GNU_SOURCE
#include <pthread.h>
#include <signal.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "platform.h"

int plat_verbose;
static char g_cmdline[1024];
static struct timespec g_t0;

void plat_log(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    fputs("grim: ", stderr);
    vfprintf(stderr, fmt, ap);
    fputc('\n', stderr);
    va_end(ap);
}

void plat_trace(const char *fmt, ...)
{
    va_list ap;
    if (!plat_verbose)
        return;
    va_start(ap, fmt);
    fputs("grim: ", stderr);
    vfprintf(stderr, fmt, ap);
    fputc('\n', stderr);
    va_end(ap);
}

uint64_t plat_us(void)
{
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return (uint64_t)(t.tv_sec - g_t0.tv_sec) * 1000000u + (t.tv_nsec - g_t0.tv_nsec) / 1000;
}

uint32_t plat_ms(void)
{
    /* starts at 1 s: some code treats a time of 0 as "never" */
    return (uint32_t)(plat_us() / 1000) + 1000;
}

void plat_init(int argc, char **argv)
{
    clock_gettime(CLOCK_MONOTONIC, &g_t0);
    plat_verbose = getenv("GRIM_PLATLOG") != NULL;
    for (int i = 1; i < argc; i++) {
        if (i > 1)
            strncat(g_cmdline, " ", sizeof g_cmdline - strlen(g_cmdline) - 1);
        strncat(g_cmdline, argv[i], sizeof g_cmdline - strlen(g_cmdline) - 1);
    }
    registry_load();
}

char *plat_command_line(void) { return g_cmdline; }

/* ---- handles ---- */
#define MAX_HANDLES 4096
static struct { int type; void *obj; } g_handles[MAX_HANDLES];
static pthread_mutex_t g_handle_lock = PTHREAD_MUTEX_INITIALIZER;
/* values look like Win32 handles: small multiples of 4, never 0 or -1 */
#define H_BASE 0x1000

HANDLE handle_new(int type, void *obj)
{
    HANDLE h = 0;
    pthread_mutex_lock(&g_handle_lock);
    for (int i = 0; i < MAX_HANDLES; i++) {
        if (g_handles[i].type == H_FREE) {
            g_handles[i].type = type;
            g_handles[i].obj = obj;
            h = (HANDLE)(intptr_t)(H_BASE + i * 4);
            break;
        }
    }
    pthread_mutex_unlock(&g_handle_lock);
    if (!h)
        plat_log("out of handles");
    return h;
}

static int handle_index(HANDLE h)
{
    intptr_t v = (intptr_t)h - H_BASE;
    if (v < 0 || (v & 3) || v / 4 >= MAX_HANDLES)
        return -1;
    return (int)(v / 4);
}

void *handle_get(HANDLE h, int type)
{
    int i = handle_index(h);
    void *r = NULL;
    if (i < 0)
        return NULL;
    pthread_mutex_lock(&g_handle_lock);
    if (g_handles[i].type == type)
        r = g_handles[i].obj;
    pthread_mutex_unlock(&g_handle_lock);
    return r;
}

int handle_type(HANDLE h)
{
    int i = handle_index(h);
    return i < 0 ? H_FREE : g_handles[i].type;
}

void handle_free(HANDLE h)
{
    int i = handle_index(h);
    if (i < 0)
        return;
    pthread_mutex_lock(&g_handle_lock);
    g_handles[i].type = H_FREE;
    g_handles[i].obj = NULL;
    pthread_mutex_unlock(&g_handle_lock);
}

/* ---- entry point ---- */
int WINAPI Win_WinMain(void *hInstance, void *hPrevInstance, char *cmdLine, int nCmdShow) __asm__("G_Win_WinMain");

static void crash_handler(int sig, siginfo_t *si, void *ctx)
{
    char buf[160];
    int n = snprintf(buf, sizeof buf, "grim: fatal signal %d at address %p (run under gdb for a backtrace)\n", sig,
                     si->si_addr);
    (void)ctx;
    if (write(2, buf, n) < 0) {}
    signal(sig, SIG_DFL);
    raise(sig);
}

int main(int argc, char **argv)
{
    struct sigaction sa;
    memset(&sa, 0, sizeof sa);
    sa.sa_sigaction = crash_handler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGSEGV, &sa, NULL);
    sigaction(SIGILL, &sa, NULL);
    sigaction(SIGFPE, &sa, NULL);
    sigaction(SIGBUS, &sa, NULL);
    plat_init(argc, argv);
    plat_fpu_windows();
    return Win_WinMain((void *)0x400000, NULL, plat_command_line(), 1);
}
