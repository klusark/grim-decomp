/* GRIM_WATCH: a debug knob of the rebuilt EXE. GRIM_WATCH=<hex address>[,<hex address>...] (up to 4, each a 4-byte
 * span) arms a hardware write breakpoint (DR0..DR3) on those addresses in every thread of the game, and logs each
 * write that hits one: the address, the new value and the writing instruction (EIP, and the words on the stack) to
 * GRIM_WATCH_LOG (default grim_watch.txt in the current directory). The game runs on: the log shows who wrote, as a
 * data breakpoint in a debugger would, without one (the clean-room harness launches the game itself, and no 32-bit
 * debugger comes with the toolchain).
 *
 * A watcher thread re-arms the registers of all threads every 20 ms, so threads started later (the timer thread, the
 * sound threads) are watched too. Linked by build/link.py into the EXE; it does nothing unless GRIM_WATCH is set.
 * The addresses are the rebuilt ones: take them from `nm` of the build (the original's address is in the symbol
 * name, `_UINT_008da5f8`).
 *
 * It keeps out of the way of the program's own layout, since the bugs it is for depend on that layout: no C runtime
 * (wsprintfA and WriteFile, not stdio, which would pull in mingw's printf), and its code and data in sections of
 * their own (.gwatch, .gwatchd, .gwatchr), which the linker places after the program's. */
#include <windows.h>
#include <tlhelp32.h>

#define GW_CODE __attribute__((section(".gwatch")))
#define GW_DATA __attribute__((section(".gwatchd")))
#define GW_RO __attribute__((section(".gwatchr")))

static DWORD watch_addr[4] GW_DATA = {0};
static int watch_n GW_DATA = 0;
static HANDLE watch_log GW_DATA = 0;
static const char fmt_hit[] GW_RO = "write %08lx = %08lx  eip %08lx  thread %lu  stack %08lx %08lx %08lx %08lx %08lx %08lx\r\n";
static const char fmt_start[] GW_RO = "watching %d address(es) from %08lx\r\n";
static const char default_log[] GW_RO = "grim_watch.txt";
static const char env_watch[] GW_RO = "GRIM_WATCH";
static const char env_log[] GW_RO = "GRIM_WATCH_LOG";

static GW_CODE void watch_write(const char *s)
{
    DWORD n;
    WriteFile(watch_log, s, lstrlenA(s), &n, NULL);
}

static GW_CODE LONG CALLBACK watch_handler(EXCEPTION_POINTERS *ep)
{
    CONTEXT *c = ep->ContextRecord;
    char line[256];
    int i;
    if (ep->ExceptionRecord->ExceptionCode != EXCEPTION_SINGLE_STEP || !(c->Dr6 & 0xf))
        return EXCEPTION_CONTINUE_SEARCH;
    for (i = 0; i < watch_n; i++) {
        if (c->Dr6 & (1u << i)) {
            DWORD *sp = (DWORD *)c->Esp;
            wsprintfA(line, fmt_hit, watch_addr[i], *(DWORD *)watch_addr[i], c->Eip, GetCurrentThreadId(),
                      sp[0], sp[1], sp[2], sp[3], sp[4], sp[5]);
            watch_write(line);
        }
    }
    c->Dr6 = 0;
    return EXCEPTION_CONTINUE_EXECUTION;
}

static GW_CODE void arm(HANDLE th)
{
    CONTEXT c;
    int i;
    c.ContextFlags = CONTEXT_DEBUG_REGISTERS;
    if (!GetThreadContext(th, &c))
        return;
    c.Dr7 = 0;
    for (i = 0; i < watch_n; i++) {
        (&c.Dr0)[i] = watch_addr[i];
        c.Dr7 |= (1u << (2 * i))            /* local enable */
               | (1u << (16 + 4 * i))       /* RW = 01: break on writes */
               | (3u << (18 + 4 * i));      /* LEN = 11: 4 bytes */
    }
    SetThreadContext(th, &c);
}

static GW_CODE DWORD WINAPI watcher(void *arg)
{
    DWORD self = GetCurrentThreadId(), pid = GetCurrentProcessId();
    (void)arg;
    for (;;) {
        HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
        THREADENTRY32 te;
        te.dwSize = sizeof te;
        if (snap != INVALID_HANDLE_VALUE && Thread32First(snap, &te)) {
            do {
                if (te.th32OwnerProcessID == pid && te.th32ThreadID != self) {
                    HANDLE th = OpenThread(THREAD_GET_CONTEXT | THREAD_SET_CONTEXT | THREAD_SUSPEND_RESUME, FALSE,
                                           te.th32ThreadID);
                    if (th) {
                        SuspendThread(th);
                        arm(th);
                        ResumeThread(th);
                        CloseHandle(th);
                    }
                }
            } while (Thread32Next(snap, &te));
        }
        if (snap != INVALID_HANDLE_VALUE)
            CloseHandle(snap);
        Sleep(20);
    }
    return 0;
}

static GW_CODE DWORD hex(const char **s)
{
    DWORD v = 0;
    for (;; (*s)++) {
        char ch = **s;
        if (ch >= '0' && ch <= '9') v = v * 16 + (ch - '0');
        else if (ch >= 'a' && ch <= 'f') v = v * 16 + (ch - 'a' + 10);
        else if (ch >= 'A' && ch <= 'F') v = v * 16 + (ch - 'A' + 10);
        else return v;
    }
}

__attribute__((constructor)) static GW_CODE void grim_watch_init(void)
{
    char spec[128], path[260], line[96];
    const char *s = spec;
    if (!GetEnvironmentVariableA(env_watch, spec, sizeof spec) || !spec[0])
        return;
    while (*s && watch_n < 4) {
        const char *b = s;
        DWORD a = hex(&s);
        if (s == b)
            break;
        watch_addr[watch_n++] = a & ~3u;
        if (*s == ',')
            s++;
    }
    if (!GetEnvironmentVariableA(env_log, path, sizeof path) || !path[0])
        lstrcpyA(path, default_log);
    watch_log = CreateFileA(path, FILE_APPEND_DATA, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, 0, NULL);
    if (watch_log == INVALID_HANDLE_VALUE)
        return;
    wsprintfA(line, fmt_start, watch_n, watch_addr[0]);
    watch_write(line);
    AddVectoredExceptionHandler(1, watch_handler);
    CreateThread(NULL, 0, watcher, NULL, 0, NULL);
}
