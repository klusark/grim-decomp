/* tools/hmifx_check.c - compares build/overrides_hmifx.c (HMI's effects library rebuilt in C) with HMI's own
 * HMIFXLIB.DLL / HMIFXFP.DLL, sample for sample.  A development check: it needs the two DLLs and HMILIBS.INI of the
 * original install, which the build does not.
 *
 *   gcc -m32 -O0 -DHMIFX_STANDALONE tools/hmifx_check.c build/overrides_hmifx.c -o hmifx_check.exe   (i686 toolchain)
 *   hmifx_check.exe "C:/GOG Games/GRIMDATA"
 *
 * It changes to that folder (the DLL reads HMILIBS.INI and IMUSE.PSL from the working directory), then runs every preset
 * of IMUSE.PSL, and of a test file with what IMUSE.PSL leaves out (the other filter types, a stereo reverb, a pre-delay,
 * chains of two effects), through both, the way IMUSE.DLL does: find the preset, lock it, process the input in blocks
 * (flags 0x19), the last one with its tail (0x9d); and once unlocked (each call resets and adds the tail).  Each under
 * three x87 precisions (24, 53, 64 bits).  Ours also runs from its built-in copy of IMUSE.PSL.  Prints the first
 * difference of each case; exit code 1 if there was one. */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

typedef struct __attribute__((packed)) Fmt { uint16_t tag, ch; uint32_t rate, bps; uint16_t align, bits, extra; } Fmt;
typedef struct Sys { uint32_t u[2]; uint32_t heap_size; void *heap; void *(*alloc)(uint32_t); void (*release)(void *); } Sys;
typedef struct Proc { uint32_t flags; void *preset; const char *name; void *out; uint32_t out_bytes; const void *in;
                      uint32_t in_bytes; Fmt *in_fmt; Fmt *out_fmt; } Proc;

typedef struct Api {
    const char *who;
    int (__stdcall *init)(Sys *);
    int (__stdcall *uninit)(Sys *);
    int (__stdcall *load)(void **, const char *);
    int (__stdcall *freelib)(void *);
    int (__stdcall *process)(void *, Proc *);
    int (__stdcall *lock)(void *);
    int (__stdcall *release)(void *);
    void (*free)(void *);
} Api;

/* ours (build/overrides_hmifx.c), by the same link names */
extern int __stdcall o_init(Sys *) __asm__("_hmiFXInitSystem");
extern int __stdcall o_uninit(Sys *) __asm__("_hmiFXUnInitSystem");
extern int __stdcall o_load(void **, const char *) __asm__("_hmiFXPresetLoadLibrary");
extern int __stdcall o_freelib(void *) __asm__("_hmiFXPresetFreeLibrary");
extern int __stdcall o_process(void *, Proc *) __asm__("_hmiFXPresetProcess");
extern int __stdcall o_lock(void *) __asm__("_hmiFXPresetLock");
extern int __stdcall o_release(void *) __asm__("_hmiFXPresetRelease");
extern void o_free(void *) __asm__("_hmiFXFree");

static void *my_alloc(uint32_t n) { return HeapAlloc(GetProcessHeap(), 0, n); }
static void my_release(void *p) { if (p) HeapFree(GetProcessHeap(), 0, p); }

static void set_cw(unsigned short cw) { __asm__ volatile("fldcw %0" : : "m"(cw)); }

#define RATE 22050
#define NSIG (RATE * 3)
static int16_t sig[3][NSIG];

static void make_signals(void)
{
    uint32_t seed = 12345;
    int i;
    for (i = 0; i < NSIG; i++) {
        double t = (double)i / RATE, env = 0.5 + 0.5 * sin(t * 3.1);
        seed = seed * 1103515245 + 12345;
        /* speech-like: a few partials and noise */
        sig[0][i] = (int16_t)(env * (6000 * sin(2 * M_PI * 220 * t) + 3000 * sin(2 * M_PI * 1330 * t)
                                     + 1500 * sin(2 * M_PI * 3100 * t)) + (int)((seed >> 16) & 0x7ff) - 0x400);
        /* loud enough to clip after the effects */
        sig[1][i] = (int16_t)(sin(2 * M_PI * 440 * t) > 0 ? 32000 : -32000) + (int16_t)((seed >> 20) & 0xff);
        /* silence, an impulse every 0.5 s */
        sig[2][i] = (i % (RATE / 2)) == 100 ? 30000 : 0;
    }
}

typedef struct Run { uint8_t *data; uint32_t len; int rc; } Run;

static void add(Run *r, const void *p, uint32_t n)
{
    r->data = realloc(r->data, r->len + n);
    memcpy(r->data + r->len, p, n);
    r->len += n;
}

/* one case through one implementation: all output bytes, prefixed by the return codes */
static Run run_case(const Api *a, const char *psl, const char *preset, int s, int locked, unsigned short cw)
{
    static const uint32_t chunks[] = { 2048, 4096, 1000, 5000, 4410, 9000, 777, 4096, 20000 };
    Run r = { 0, 0, 0 };
    Sys sys = { { 0, 0 }, 150000, 0, my_alloc, my_release };
    void *lib = 0, *p;
    Proc pr;
    Fmt in = { 1, 1, RATE, RATE * 2, 2, 16, 0 }, out;
    uint32_t pos = 0, k = 0, ch = 1;
    int rc;
    static int16_t outbuf[2 * 20000 + 64];

    set_cw(cw);
    rc = a->init(&sys);
    add(&r, &rc, 4);
    {   /* what init did to the control word (the DLL: precision 53 bits), then the precision under test */
        unsigned short got;
        __asm__ volatile("fnstcw %0" : "=m"(got));
        add(&r, &got, 2);
        set_cw(cw);
    }
    if (rc)
        return r;
    rc = a->load(&lib, psl);
    add(&r, &rc, 4);
    if (rc)
        goto out_sys;
    memset(&pr, 0, sizeof pr);
    pr.flags = 0x20;
    pr.name = preset;
    rc = a->process(lib, &pr);
    add(&r, &rc, 4);
    if (rc)
        goto out_lib;
    p = pr.preset;
    {   /* the routing of the last effect, as IMUSE.DLL's FUN_10004750 reads it */
        uint8_t *e = *(uint8_t **)((uint8_t *)p + 0x450);
        uint32_t route = 0;
        while (e) {
            route = *(uint32_t *)(e + 0xc);
            e = *(uint8_t **)(e + 0x18);
        }
        ch = (route & 10) ? 2 : 1;
    }
    out = (Fmt){ 1, (uint16_t)ch, RATE, RATE * 2 * ch, (uint16_t)(2 * ch), 16, 0 };
    if (locked) {
        rc = a->lock(p);
        add(&r, &rc, 4);
    }
    while (pos < NSIG) {
        uint32_t n = chunks[k++ % (sizeof chunks / sizeof chunks[0])];
        int last;
        if (n > NSIG - pos)
            n = NSIG - pos;
        last = pos + n == NSIG;
        memset(&pr, 0, sizeof pr);
        pr.preset = p;
        pr.name = preset;
        pr.in = sig[s] + pos;
        pr.in_bytes = n * 2;
        pr.in_fmt = &in;
        pr.out_fmt = &out;
        if (!locked || last) {
            pr.flags = (locked ? 0x9d : 0x1e);
            rc = a->process(lib, &pr);
            add(&r, &rc, 4);
            add(&r, &pr.out_bytes, 4);
            if (!rc) {
                add(&r, pr.out, pr.out_bytes);
                a->free(pr.out);
            }
        } else {
            pr.flags = 0x19;
            pr.out = outbuf;
            memset(outbuf, 0x55, sizeof outbuf);
            rc = a->process(lib, &pr);
            add(&r, &rc, 4);
            add(&r, outbuf, n * 2 * ch);
        }
        pos += n;
    }
    if (locked) {
        rc = a->release(p);
        add(&r, &rc, 4);
    }
out_lib:
    a->freelib(lib);
out_sys:
    a->uninit(&sys);
    set_cw(0x27f);
    return r;
}

static const char test_psl[] =
    "[LIBRARY]\r\nDescription  =  hmifx_check\r\n\r\n"
    "[INPUTFMT]\r\nRate = 22050\r\nBitsPerSample = 16\r\nChannels = 1\r\n\r\n"
    "[OUTPUTFMT]\r\nRate = 22050\r\nBitsPerSample = 16\r\nChannels = 2\r\n\r\n"
    "[PRESET0000]\r\nDescription = Low\r\nFlags = 0\r\nEffect0000 = 2300, 0, 1, -1, 1024.00, 800.00, 0, 0\r\n\r\n"
    "[PRESET0001]\r\nDescription = LowHigh\r\nFlags = 0\r\nEffect0000 = 2300, 0, 1, -1, 1024.00, 30000.00, 0, 0\r\n\r\n"
    "[PRESET0002]\r\nDescription = High\r\nFlags = 0\r\nEffect0000 = 2300, 0, 1, -1, 1025.00, 2500.00, 0, 0\r\n\r\n"
    "[PRESET0003]\r\nDescription = Notch\r\nFlags = 0\r\nEffect0000 = 2300, 0, 1, -1, 1027.00, 0, 1330.00, 300.00\r\n\r\n"
    "[PRESET0004]\r\nDescription = Wide\r\nFlags = 0\r\nEffect0000 = 2101, 0, 2, -1, 200.00, 20.00, 120.00, 0.50, 0.30\r\n\r\n"
    "[PRESET0005]\r\nDescription = Pre\r\nFlags = 0\r\nEffect0000 = 2101, 0, 1, -1, 180.00, 35.00, 90.00, 0.70, 0.20\r\n\r\n"
    "[PRESET0006]\r\nDescription = Chain\r\nFlags = 0\r\nEffect0000 = 2300, 0, 1, -1, 1026.00, 0, 900.00, 1200.00\r\n"
    "Effect0001 = 2101, 0, 1, -1, 200.00, 0.00, 150.00, 0.62, 0.08\r\n\r\n"
    "[PRESET0007]\r\nDescription = ChainWide\r\nFlags = 0\r\nEffect0000 = 2375, 0, 1, -1, 0.5, 2.0, 1.5, 300.00, 0.5, 0.5\r\n"
    "Effect0001 = 2101, 0, 2, -1, 200.00, 0.00, 60.00, 0.60, 0.30\r\n\r\n"
    "[PRESET0008]\r\nDescription = Phase2\r\nFlags = 0\r\nEffect0000 = 2375, 0, 1, -1, -0.6, 4.0, 2.2, 150.00, 0.4, 0.9\r\n\r\n";

int main(int argc, char **argv)
{
    static const char *const imuse_presets[] = { "Basic Reverb", "Short Reverb", "Intercom Filter", "Stereo Ring Modulator" };
    static const char *const test_presets[] = { "Low", "LowHigh", "High", "Notch", "Wide", "Pre", "Chain", "ChainWide", "Phase2" };
    static const unsigned short cws[] = { 0x27f, 0x07f, 0x37f };
    char test_path[MAX_PATH];
    HMODULE h;
    Api orig, ours = { "ours", o_init, o_uninit, o_load, o_freelib, o_process, o_lock, o_release, o_free };
    int bad = 0, cases = 0, f, i, s, l, c;
    FILE *fp;

    if (argc < 2 || !SetCurrentDirectoryA(argv[1])) {
        fprintf(stderr, "usage: hmifx_check <folder of HMIFXLIB.DLL, HMIFXFP.DLL, HMILIBS.INI, IMUSE.PSL>\n");
        return 2;
    }
    h = LoadLibraryA("HMIFXLIB.DLL");
    if (!h) {
        fprintf(stderr, "HMIFXLIB.DLL not found in %s\n", argv[1]);
        return 2;
    }
    orig.who = "HMIFXLIB.DLL";
    orig.init = (void *)GetProcAddress(h, "hmiFXInitSystem");
    orig.uninit = (void *)GetProcAddress(h, "hmiFXUnInitSystem");
    orig.load = (void *)GetProcAddress(h, "hmiFXPresetLoadLibrary");
    orig.freelib = (void *)GetProcAddress(h, "hmiFXPresetFreeLibrary");
    orig.process = (void *)GetProcAddress(h, "hmiFXPresetProcess");
    orig.lock = (void *)GetProcAddress(h, "hmiFXPresetLock");
    orig.release = (void *)GetProcAddress(h, "hmiFXPresetRelease");
    orig.free = (void *)GetProcAddress(h, "hmiFXFree");
    GetTempPathA(sizeof test_path, test_path);
    strcat(test_path, "hmifx_check.psl");
    fp = fopen(test_path, "wb");
    fwrite(test_psl, 1, sizeof test_psl - 1, fp);
    fclose(fp);
    make_signals();

    for (f = 0; f < 2; f++) {
        const char *psl = f ? test_path : "imuse.psl";
        int np = f ? 9 : 4;
        for (i = 0; i < np; i++)
            for (s = 0; s < 3; s++)
                for (l = 0; l < 2; l++)
                    for (c = 0; c < 3; c++) {
                        const char *name = f ? test_presets[i] : imuse_presets[i];
                        Run a = run_case(&orig, psl, name, s, l, cws[c]);
                        Run b = run_case(&ours, psl, name, s, l, cws[c]);
                        Run d = { 0, 0, 0 };
                        int same = a.len == b.len && memcmp(a.data, b.data, a.len) == 0;
                        if (!f) {   /* ours again, from its built-in IMUSE.PSL */
                            d = run_case(&ours, "no such file.psl", name, s, l, cws[c]);
                            same = same && d.len == a.len && memcmp(d.data, a.data, a.len) == 0;
                        }
                        cases++;
                        if (!same) {
                            uint32_t k = 0, n = a.len < b.len ? a.len : b.len;
                            while (k < n && a.data[k] == b.data[k])
                                k++;
                            printf("DIFF %-22s signal %d %s cw %03x: %u / %u bytes (built-in %u), first difference at %u\n",
                                   name, s, l ? "locked" : "unlocked", cws[c], a.len, b.len, d.len, k);
                            bad++;
                        }
                        free(a.data);
                        free(b.data);
                        free(d.data);
                    }
    }
    printf("%d of %d cases differ\n", bad, cases);
    DeleteFileA(test_path);
    return bad != 0;
}
