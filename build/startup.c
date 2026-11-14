/* Program entry for the rebuilt GRIMFANDANGO.EXE.
 *
 * The original start-up (`entry` at 0x4aca30, MSVC 6 WinMainCRTStartup) and
 * the whole static C runtime are left out of the runnable link; the host
 * mingw/msvcrt runtime does that work and calls this WinMain, which hands over
 * to the game's own WinMain (Win_WinMain at 0x401010 -> Win_Main). */
int __attribute__((stdcall)) Win_WinMain(void *hInstance, void *hPrevInstance, char *cmdLine, int nCmdShow);

int __attribute__((stdcall)) WinMain(void *hInstance, void *hPrevInstance, char *cmdLine, int nCmdShow)
{
    return Win_WinMain(hInstance, hPrevInstance, cmdLine, nCmdShow);
}

/* Crash report: an unhandled exception writes the exception record, the registers and the top of the
 * stack to grim_crash.txt in the working directory (resolve addresses with `nm` on the exe/dlls, or with
 * gdb's `info symbol`), then lets the default handler run. Works without a debugger, which matters for
 * crashes that only happen outside gdb. */
typedef struct { unsigned code, flags; void *chain; void *addr; unsigned nparams, info[15]; } GRIM_EXC_REC;
typedef struct { GRIM_EXC_REC *rec; unsigned *ctx; } GRIM_EXC_PTRS;
extern void *__stdcall CreateFileA(const char *, unsigned, unsigned, void *, unsigned, unsigned, void *);
extern int __stdcall WriteFile(void *, const void *, unsigned, unsigned *, void *);
extern int __stdcall CloseHandle(void *);
extern int __cdecl wsprintfA(char *, const char *, ...);
extern void *__stdcall SetUnhandledExceptionFilter(long (__stdcall *)(GRIM_EXC_PTRS *));
extern int __stdcall IsBadReadPtr(const void *, unsigned);
extern unsigned __stdcall GetEnvironmentVariableA(const char *, char *, unsigned);

#ifdef GRIM_COVERAGE
/* The coverage build (make COVERAGE=1): each program has its own libgcov, and a DLL writes its counters only when it is
 * unloaded, at the end of the process teardown. A game that hangs there (the timer thread's wait) and is killed by run.py
 * loses them: each run counted other lines of the DLLs. So the exe writes all four at exit() and in its crash filter: its
 * own (__gcov_dump) and the DLLs' (grim_cov_dump, link.py's cov_export.c in each). libgcov marks a dump as done, so the one
 * at unload adds nothing twice. */
extern void *__stdcall GetModuleHandleA(const char *);
extern void *__stdcall GetProcAddress(void *, const char *);
static void grim_cov_dump_all(void)
{
    static const char *const dlls[] = { "lua.dll", "imuse.dll", "chore.dll" };
    extern void __gcov_dump(void);
    unsigned i;
    for (i = 0; i < 3; i++) {
        void *h = GetModuleHandleA(dlls[i]);
        void (*dump)(void) = h ? (void (*)(void))GetProcAddress(h, "grim_cov_dump") : 0;
        if (dump)
            dump();
    }
    __gcov_dump();
}
#endif

static long __stdcall grim_crash_filter(GRIM_EXC_PTRS *p)
{
    char buf[256];
    unsigned *c = p->ctx;
    unsigned wrote, i, *sp;
    char name[96] = "grim_crash.txt", tag[48];
    void *h;
    /* GRIM_MULTI=<tag> (parallel test instances): grim_crash_<tag>.txt, so sessions do not mix reports */
    if (GetEnvironmentVariableA("GRIM_MULTI", tag, sizeof tag) && tag[0])
        wsprintfA(name, "grim_crash_%s.txt", tag);
    h = CreateFileA(name, 4, 3, 0, 4, 0x80, 0);   /* FILE_APPEND_DATA, OPEN_ALWAYS */
    if (h == (void *)-1)
        return 0;
    wsprintfA(buf, "exception %08x at %08x (info %08x %08x)\r\n", p->rec->code, (unsigned)p->rec->addr, p->rec->info[0], p->rec->info[1]);
    WriteFile(h, buf, __builtin_strlen(buf), &wrote, 0);
    wsprintfA(buf, "eax=%08x ebx=%08x ecx=%08x edx=%08x esi=%08x edi=%08x ebp=%08x esp=%08x\r\n", c[0xb0 / 4], c[0xa4 / 4], c[0xac / 4], c[0xa8 / 4], c[0xa0 / 4], c[0x9c / 4], c[0xb4 / 4], c[0xc4 / 4]);
    WriteFile(h, buf, __builtin_strlen(buf), &wrote, 0);
    {   /* the first three cdecl arguments of the frame ebp points at, and what they point to */
        unsigned *fp = (unsigned *)c[0xb4 / 4];
        unsigned k, a;
        for (a = 0; a < 3 && !IsBadReadPtr(fp + 2 + a, 4); a++) {
            unsigned *q = (unsigned *)fp[2 + a];
            wsprintfA(buf, "arg%u=%08x:", a, (unsigned)q);
            WriteFile(h, buf, __builtin_strlen(buf), &wrote, 0);
            for (k = 0; k < (a == 1 ? 192 : 16) && !IsBadReadPtr(q + k, 4); k++) {
                wsprintfA(buf, " %08x", q[k]);
                WriteFile(h, buf, __builtin_strlen(buf), &wrote, 0);
            }
            WriteFile(h, "\r\n", 2, &wrote, 0);
        }
    }
    sp = (unsigned *)c[0xc4 / 4];
    for (i = 0; i < 320 && !IsBadReadPtr(sp + i, 4); i++) {
        wsprintfA(buf, "%s%08x", i % 8 ? " " : "stack: ", sp[i]);
        WriteFile(h, buf, __builtin_strlen(buf), &wrote, 0);
        if (i % 8 == 7)
            WriteFile(h, "\r\n", 2, &wrote, 0);
    }
    WriteFile(h, "\r\n", 2, &wrote, 0);
    CloseHandle(h);
#ifdef GRIM_COVERAGE
    grim_cov_dump_all();   /* the coverage build: the counters of a game that crashes count too */
#endif
    return 0;   /* EXCEPTION_CONTINUE_SEARCH */
}

__attribute__((constructor)) static void grim_install_crash_filter(void)
{
    SetUnhandledExceptionFilter(grim_crash_filter);
#ifdef GRIM_COVERAGE
    {
        extern int __cdecl atexit(void (*)(void));
        atexit(grim_cov_dump_all);
    }
#endif
}
