/* Differential test of rdModel3_LoadText (build/overrides_asm_q3.c) against the original 1.01 machine code (sliced
 * from the assembly of 2df265d).
 *
 * Inputs: the text .3do files of the game data (the ten "# MODEL" files of DATA*.LAB, extracted to a directory given
 * on the command line), each case one of them with random mutations: lines deleted, duplicated, swapped, truncated,
 * junk lines, numbers replaced (0, -1, the 0x18 / 0x200 / 0x300 / 0x80 limits and their neighbours, large values,
 * floats, words), the "shadow" line dropped, material lines permuted; plus a failing allocation, a failing
 * rdMaterial_Load, a failing open, and materials with the 0x2 flag (uv index lists).  Material slots are kept a
 * permutation of 0..n-1 and face material indexes in -1..n-1: the original keeps the material names in uninitialised
 * stack slots, so a hole would compare stack garbage.
 * Each case runs the original and the C on the same start state and compares: the return value, the model record and
 * every allocation (one arena, same addresses in both runs), the global scan buffer DAT_009056c0, and the call log of
 * every callee (stdConffile_*, sscanf with the format, the input string and the target pointers (stack targets as
 * one marker), strtok, atoi, strncpy, rdMaterial_Load, the allocator with size / file / line, the assertion).
 * The stand-ins: stdConffile_ReadLine gives the lines (lower-cased, comments and blank lines skipped) in the buffer
 * UINT_00900520 points to; sscanf / strtok / atoi / strncpy forward to msvcrt (strtok and atoi accept NULL here,
 * returning NULL / 0, so a mutated line cannot crash the test).
 * usage: model_test.exe [cases] [dir with the .3do files] */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>
#include "fx.h"

typedef unsigned uint;
extern uint orig_rdModel3_LoadText(char *, char *), rdModel3_LoadText(char *, char *);

/* ---- arena: model record (with slack) and every allocation ---- */
#define ARSZ (48 << 20)
#define MREC 0x10000
static unsigned char *ar, *ar0, *arA;
static uint used, usedA;
static uint64_t ss;
static uint snext(void) { ss ^= ss << 13; ss ^= ss >> 7; ss ^= ss << 17; return (uint)(ss >> 17); }
static uint R(uint n) { return (uint)(fx_rnd() % n); }

/* ---- call log ---- */
#define MAXLG (1 << 21)
static uint *lg, *lgA; static int nlg, nlgA;
static void L(uint v) { if (nlg < MAXLG) lg[nlg++] = v; }
static uint hstr(const char *s)
{
    uint h = 2166136261u;
    if (!s) return 0xdead0000;
    while (*s) h = (h ^ (unsigned char)*s++) * 16777619u;
    return h;
}
static char linebuf[0x1000];
/* a pointer argument: arena, image or line buffer as its value, anything else (the stack) as one marker */
static uint P(const void *p)
{
    uintptr_t u = (uintptr_t)p;
    if (!p) return 0;
    if (u >= (uintptr_t)ar && u < (uintptr_t)ar + ARSZ) return (uint)u;
    if (u >= (uintptr_t)fx_data && u < (uintptr_t)fx_data + 0x527ca0) return (uint)u;
    if (u >= (uintptr_t)linebuf && u < (uintptr_t)linebuf + sizeof linebuf) return (uint)u;
    return 0x57ac0000;
}

/* ---- the input of a case ---- */
#define MAXL 20000
static char *flines[16][MAXL]; static int fnl[16]; static char fname[16][64]; static int nfiles;
static char *cl[MAXL + 64]; static int ncl, rdpos;
static int alloc_fail_at, nalloc, mat_fail_at, nmat, open_fail;

/* ---- stand-ins ---- */
static int (__cdecl *r_sscanf)(const char *, const char *, ...);
static char *(__cdecl *r_strtok)(char *, const char *);
static int (__cdecl *r_atoi)(const char *);
static char *(__cdecl *r_strncpy)(char *, const char *, size_t);

int __cdecl my_sscanf(const char *s, const char *fmt, ...) __asm__("_sscanf");
int __cdecl my_sscanf(const char *s, const char *fmt, ...)
{
    va_list ap;
    void *a[20];
    int n = 0, r, i;
    const char *f;
    for (f = fmt; *f; f++)
        if (*f == '%' && f[1] != '%') n++;
    va_start(ap, fmt);
    for (i = 0; i < 20; i++) a[i] = i < n ? va_arg(ap, void *) : 0;
    va_end(ap);
    L(0x55c00000 | n); L(hstr(fmt)); L(hstr(s));
    for (i = 0; i < n; i++) L(P(a[i]));
    if (!s) r = -1;
    else r = r_sscanf(s, fmt, a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11], a[12], a[13],
                      a[14], a[15], a[16], a[17], a[18], a[19]);
    L(r);
    return r;
}
char *__cdecl my_strtok(char *s, const char *d) __asm__("_strtok");
char *__cdecl my_strtok(char *s, const char *d)
{
    char *r;
    L(0x570c0000); L(P(s)); L(hstr(d));
    r = r_strtok(s, d);
    L(P(r)); L(hstr(r));
    return r;
}
int __cdecl my_atoi(const char *s) __asm__("_atoi");
int __cdecl my_atoi(const char *s)
{
    int r = s ? r_atoi(s) : 0;
    L(0xa7010000); L(P(s)); L(r);
    return r;
}
char *__cdecl my_strncpy(char *d, const char *s, size_t n) __asm__("_strncpy");
char *__cdecl my_strncpy(char *d, const char *s, size_t n)
{
    L(0x5c900000); L(P(d)); L(hstr(s)); L(n);
    return r_strncpy(d, s, n);
}
void __cdecl rdModel3_NewEntry(uint *m)
{
    int i;
    L(0x4e400000); L(P(m));
    for (i = 0; i < 0x24; i++) m[i] = 0;
    r_strncpy((char *)m, "UNKNOWN", 0x1f);
}
char *__cdecl Str_FileNameFromPath(char *p)
{
    char *r = p, *q;
    for (q = p; *q; q++) if (*q == '\\' || *q == '/') r = q + 1;
    L(0xf11e0000); L(P(p)); L(P(r));
    return r;
}
int __cdecl stdConffile_OpenRead(char *p) { L(0x09e40000); L(hstr(p)); rdpos = 0; return !open_fail; }
void __cdecl stdConffile_Close(void) { L(0xc105e000); }
int __cdecl stdConffile_ReadLine(void)
{
    char *dst = *(char **)FXDATA(0x900520);
    L(0x4ead0000 | (rdpos & 0xffff));
    if (rdpos >= ncl) return 0;
    strcpy(dst, cl[rdpos++]);
    return 1;
}
void *__cdecl rdMaterial_Load(char *name, int a, int b)
{
    void *r;
    L(0x3a700000); L(hstr(name)); L(a); L(b);
    if (++nmat == mat_fail_at) return 0;
    r = ar + used;
    used += 16;
    ((uint *)r)[0] = hstr(name) & 3;   /* flag 0x2: the face lists uv indexes too */
    ((uint *)r)[1] = 0x3a7;
    return r;
}
uint __cdecl FUN_00450220(uint *p)
{
    L(0x45022000); L(P(p));
    p[0] = p[1] = p[5] = p[6] = p[7] = p[8] = 0; p[9] = 0xffffffff;
    p[0x10] = p[0x11] = p[0x12] = p[10] = p[0xb] = p[0xc] = 0;
    return 1;
}
void __cdecl rdModel3_CountNodeChildren(int m) { L(0xcc000000); L(P((void *)m)); }
static void *__cdecl svc_alloc(uint size, char *file, int line)
{
    void *r;
    uint i;
    L(0xa1100000); L(size); L(hstr(file)); L(line);
    if (++nalloc == alloc_fail_at || size > ARSZ - used - 64) { L(0); return 0; }
    r = ar + used;
    for (i = 0; i < size; i++) ((unsigned char *)r)[i] = (unsigned char)(0xa5 ^ i ^ nalloc);
    used = (used + size + 7) & ~7u;
    L(P(r));
    return r;
}
static void __cdecl svc_assert(char *msg, char *file, int line) { L(0xa5500000); L(hstr(msg)); L(hstr(file)); L(line); }
static void __cdecl svc_bad(void) { printf("unexpected service call\n"); exit(3); }
static void *svc[64];

/* ---- inputs ---- */
static void load_files(const char *dir)
{
    WIN32_FIND_DATAA fd;
    char pat[512], path[512];
    HANDLE h;
    sprintf(pat, "%s\\*.3do", dir);
    h = FindFirstFileA(pat, &fd);
    if (h == INVALID_HANDLE_VALUE) { printf("no .3do files in %s\n", dir); exit(2); }
    do {
        FILE *f;
        char buf[4096];
        int n = 0;
        if (nfiles >= 16) break;
        sprintf(path, "%s\\%s", dir, fd.cFileName);
        f = fopen(path, "rb");
        if (!f) continue;
        while (fgets(buf, sizeof buf, f) && n < MAXL) {
            char *p = buf, *e;
            while (*p == ' ' || *p == '\t') p++;
            for (e = p; *e; e++) { if (*e == '\r' || *e == '\n') { *e = 0; break; } *e = (char)tolower((unsigned char)*e); }
            if (*p == 0 || *p == '#') continue;
            flines[nfiles][n++] = _strdup(p);
        }
        fclose(f);
        fnl[nfiles] = n;
        strncpy(fname[nfiles], fd.cFileName, 63);
        nfiles++;
    } while (FindNextFileA(h, &fd));
    FindClose(h);
}
static char pool[1 << 22]; static uint npool;
static char *pdup(const char *s) { size_t n = strlen(s) + 1; char *r = pool + npool; if (npool + n > sizeof pool) npool = 0, r = pool; memcpy(r, s, n); npool += n; return r; }
static const char *numval(void)
{
    static const char *t[] = {"0", "1", "-1", "2", "7", "24", "25", "512", "513", "768", "769", "127", "128", "129",
                              "100000", "1.5", "-0.0", "1e30", "x", "", "3", "0x0010", "-2", "4294967295"};
    return t[R(sizeof t / sizeof t[0])];
}
/* replace the k-th whitespace token of line s */
static char *retoken(const char *s, int k, const char *v)
{
    char out[4096], *o = out;
    const char *p = s;
    int t = 0;
    while (*p && o < out + 3000) {
        while (*p == ' ' || *p == '\t') *o++ = *p++;
        if (!*p) break;
        if (t++ == k) { strcpy(o, v); o += strlen(v); while (*p && *p != ' ' && *p != '\t') p++; }
        else while (*p && *p != ' ' && *p != '\t') *o++ = *p++;
    }
    *o = 0;
    return pdup(out);
}
static int ntokens(const char *s)
{
    int n = 0;
    while (*s) { while (*s == ' ' || *s == '\t') s++; if (!*s) break; n++; while (*s && *s != ' ' && *s != '\t') s++; }
    return n;
}
static void make_case(int fi)
{
    int i, k, nm, nmats = 0, matfirst = -1, n;
    char **src = flines[fi];
    ncl = fnl[fi];
    for (i = 0; i < ncl; i++) cl[i] = src[i];
    for (i = 0; i < ncl; i++)
        if (!strncmp(cl[i], "materials", 9)) { nmats = atoi(cl[i] + 9); matfirst = i + 1; break; }
    nm = R(4) == 0 ? 0 : 1 + R(3);
    for (k = 0; k < nm; k++) {
        int l = ncl ? R(ncl) : 0;
        switch (R(12)) {
        case 0: if (ncl > 1) { memmove(cl + l, cl + l + 1, (ncl - l - 1) * sizeof *cl); ncl--; } break;   /* delete */
        case 1: if (ncl < MAXL) { memmove(cl + l + 1, cl + l, (ncl - l) * sizeof *cl); ncl++; } break;    /* duplicate */
        case 2: ncl = l; break;                                                                         /* truncate */
        case 3: { int l2 = R(ncl ? ncl : 1); char *t = cl[l]; cl[l] = cl[l2]; cl[l2] = t; } break;      /* swap */
        case 4: if (ncl < MAXL) { memmove(cl + l + 1, cl + l, (ncl - l) * sizeof *cl); cl[l] = pdup(R(2) ? "junk 1 2 3" : "section: x"); ncl++; } break;
        case 6: case 7: /* a limit or a special value on a count line, a face's vertex count, a node's links */
            for (i = l; i < ncl; i++) {
                static const char *lim[] = {"511", "512", "513", "767", "768", "769", "0", "1"};
                static const char *fv[] = {"23", "24", "25", "0", "1", "-1"};
                static const char *nl[] = {"-1", "-2", "0", "1", "1000", "-1000"};
                n = ntokens(cl[i]);
                if (!strncmp(cl[i], "vertices", 8) || !strncmp(cl[i], "faces", 5) || !strncmp(cl[i], "hierarchy", 9)) {
                    cl[i] = retoken(cl[i], n - 1, lim[R(8)]); break;
                }
                if (!strncmp(cl[i], "texture", 7)) { cl[i] = retoken(cl[i], 2, lim[R(8)]); break; }
                if (n > 9 && cl[i][0] >= '0' && cl[i][0] <= '9' && strchr(cl[i], ',')) { cl[i] = retoken(cl[i], 7, fv[R(6)]); break; }
                if (n == 18) { cl[i] = retoken(cl[i], 4 + R(3), nl[R(6)]); break; }
            }
            break;
        case 5: /* drop the shadow line of a mesh */
            for (i = l; i < ncl; i++) if (!strncmp(cl[i], "shadow", 6)) { memmove(cl + i, cl + i + 1, (ncl - i - 1) * sizeof *cl); ncl--; break; }
            break;
        default: /* replace a number */
            if (ncl == 0) break;
            n = ntokens(cl[l]);
            if (n == 0) break;
            if (matfirst >= 0 && l >= matfirst - 1 && l < matfirst + nmats) break;   /* the material count and slots */
            {
                int t = R(n);
                /* a face line: keep the material index in -1..n-1 */
                if (t == 1 && n > 8 && cl[l][0] >= '0' && cl[l][0] <= '9') {
                    char v[16]; sprintf(v, "%d", (int)R(nmats + 1) - 1);
                    cl[l] = retoken(cl[l], 1, v);
                } else
                    cl[l] = retoken(cl[l], t, numval());
            }
            break;
        }
    }
    /* material lines: sometimes permuted (the slots stay a permutation of 0..n-1) */
    if (matfirst >= 0 && nmats > 1 && R(4) == 0 && matfirst + nmats <= ncl) {
        for (i = 0; i < nmats; i++) {
            int j = i + R(nmats - i);
            char *t = cl[matfirst + i]; cl[matfirst + i] = cl[matfirst + j]; cl[matfirst + j] = t;
        }
    }
    if (matfirst >= 0 && R(30) == 0 && matfirst >= 1) {
        /* the assertion: 0x80 or more materials (the next line then fails to parse) */
        cl[matfirst - 1] = pdup(R(2) ? "materials 128" : "materials 200");
    }
    /* follow the loader to its material slots: an index outside 0..0x7f is a write past the original's stack slots,
     * and a hole among the slots it then loads is a read of uninitialised stack; such a case goes back unmutated */
    {
        char tmp[4096];
        int nm2 = 0, idx, bad = 0, ok = 1;
        static unsigned char seen[0x80];
        if (ncl >= 4 && r_sscanf(cl[0], " section: %s", tmp) == 1 && r_sscanf(cl[2], " section: %s", tmp) == 1
            && r_sscanf(cl[3], " materials %d", &nm2) == 1 && nm2 != 0) {
            memset(seen, 0, sizeof seen);
            for (i = 0; i < nm2; i++) {
                if (4 + i >= ncl || r_sscanf(cl[4 + i], " %d: %s", &idx, tmp) != 2) { ok = 0; break; }
                if ((uint)idx >= 0x80) { bad = 1; break; }
                seen[idx] = 1;
            }
            if (ok && !bad)
                for (i = 0; i < nm2; i++) if ((uint)i >= 0x80 || !seen[i]) { bad = 1; break; }
        }
        if (bad) {
            ncl = fnl[fi];
            for (i = 0; i < ncl; i++) cl[i] = src[i];
        }
    }
    alloc_fail_at = R(8) == 0 ? 1 + R(40) : -1;
    mat_fail_at = R(10) == 0 ? 1 + R(6) : -1;
    open_fail = R(60) == 0;
}

static uint get_cw(void) { unsigned short cw; __asm__ volatile("fnstcw %0" : "=m"(cw)); return cw; }
static uint get_sw(void) { unsigned short sw; __asm__ volatile("fnstsw %0" : "=m"(sw)); return sw; }
static unsigned char sbufA[0x800], sbuf0[0x800];

int main(int argc, char **argv)
{
    long n = argc > 1 ? atol(argv[1]) : 10000, i, nf = 0, nok = 0, nfail_ret = 0;
    const char *dir = argc > 2 ? argv[2] : "build/difftest/asm_q3/out/3do";
    HMODULE crt = GetModuleHandleA("msvcrt.dll");
    char path[128];
    char *model;
    int k;
    r_sscanf = (void *)GetProcAddress(crt, "sscanf");
    r_strtok = (void *)GetProcAddress(crt, "strtok");
    r_atoi = (void *)GetProcAddress(crt, "atoi");
    r_strncpy = (void *)GetProcAddress(crt, "strncpy");
    ar = VirtualAlloc(0, ARSZ, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    ar0 = malloc(ARSZ); arA = malloc(ARSZ);
    lg = malloc(MAXLG * 4); lgA = malloc(MAXLG * 4);
    load_files(dir);
    for (k = 0; k < 64; k++) svc[k] = (void *)svc_bad;
    svc[0x18 / 4] = (void *)svc_assert;
    svc[0x20 / 4] = (void *)svc_alloc;
    FXU32(0x900004) = (uint)(uintptr_t)svc;
    FXU32(0x900520) = (uint)(uintptr_t)linebuf;
    for (i = 0; i < n; i++) {
        uint ra, rb, cwA, swA, cw, sw;
        int fi = R(nfiles);
        /* the big files less often */
        if (fnl[fi] > 3000 && R(8)) fi = R(nfiles);
        if (fnl[fi] > 3000 && R(4)) fi = R(nfiles);
        make_case(fi);
        sprintf(path, R(2) ? "3do\\%s" : "%s", fname[fi]);
        for (k = 0; k < MREC; k++) ar[k] = (unsigned char)fx_rnd();
        memcpy(ar0, ar, MREC);
        for (k = 0; k < 0x800; k++) FXDATA(0x9056c0)[k] = (unsigned char)fx_rnd();
        memcpy(sbuf0, FXDATA(0x9056c0), 0x800);
        model = (char *)ar + 0x100;
        /* original */
        used = MREC; nlg = 0; nalloc = 0; nmat = 0;
        ra = orig_rdModel3_LoadText(path, model);
        cwA = get_cw(); swA = get_sw();
        usedA = used; memcpy(arA, ar, used); nlgA = nlg; memcpy(lgA, lg, nlg * 4); memcpy(sbufA, FXDATA(0x9056c0), 0x800);
        /* C */
        memcpy(ar, ar0, MREC); memcpy(FXDATA(0x9056c0), sbuf0, 0x800);
        used = MREC; nlg = 0; nalloc = 0; nmat = 0;
        rb = rdModel3_LoadText(path, model);
        cw = get_cw(); sw = get_sw();
        {
            const char *what = 0;
            if (ra != rb) what = "return";
            else if (used != usedA) what = "arena size";
            else if (memcmp(ar, arA, used)) what = "model / allocations";
            else if (nlg != nlgA || memcmp(lg, lgA, nlg * 4)) what = "call log";
            else if (memcmp(sbufA, FXDATA(0x9056c0), 0x800)) what = "scan buffer DAT_009056c0";
            else if (cw != cwA || ((sw >> 11) & 7) != ((swA >> 11) & 7)) what = "x87 control word / stack top";
            if (what) {
                if (nf++ < 5) {
                    printf("DIFF rdModel3_LoadText case %ld (%s): %s\n", i, fname[fi], what);
                    if (getenv("P3DBG")) {
                        for (k = 0; k < nlg && k < nlgA; k++) if (lg[k] != lgA[k]) { printf("  log[%d] orig %08x C %08x\n", k, lgA[k], lg[k]); break; }
                        for (k = 0; k < (int)used && k < (int)usedA; k++) if (ar[k] != arA[k]) { printf("  arena+%x orig %02x C %02x\n", k, arA[k], ar[k]); break; }
                    }
                }
            }
        }
        if (ra) nok++; else nfail_ret++;
    }
    printf("%-32s %8ld cases (%ld loaded, %ld rejected), %ld differences; %d files\n", "rdModel3_LoadText", n, nok,
           nfail_ret, nf, nfiles);
    return nf != 0;
}
