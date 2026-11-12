/* The MSVC runtime functions whose glibc namesakes differ, or that glibc does not have.
 *
 * Everything else the game calls from the C runtime (memcpy, sprintf, fread, strtod ...) is linked straight to
 * glibc by link_linux.py (G_<name> -> <name>), which is right because those behave the same. */
#define _GNU_SOURCE
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include "platform.h"

#define CRTFN(ret, cname, gname, params) ret cname params EXPORT(gname); ret cname params

/* ---- file names: DOS paths, case-insensitive ---- */
CRTFN(FILE *, crt_fopen, fopen, (const char *name, const char *mode))
{
    char path[PATH_MAX];
    FILE *f;
    path_to_unix(name, path, sizeof path);
    f = fopen(path, mode);
    plat_trace("fopen(%s -> %s, %s) = %p", name, path, mode, (void *)f);
    return f;
}

CRTFN(int, crt_remove, remove, (const char *name))
{
    char path[PATH_MAX];
    path_to_unix(name, path, sizeof path);
    return remove(path);
}

CRTFN(int, crt_rename, rename, (const char *from, const char *to))
{
    char a[PATH_MAX], b[PATH_MAX];
    path_to_unix(from, a, sizeof a);
    path_to_unix(to, b, sizeof b);
    return rename(a, b);
}

CRTFN(int, crt_mkdir, _mkdir, (const char *name))
{
    char path[PATH_MAX];
    path_to_unix(name, path, sizeof path);
    return mkdir(path, 0755);
}

CRTFN(int, crt_access, _access, (const char *name, int mode))
{
    char path[PATH_MAX];
    path_to_unix(name, path, sizeof path);
    return access(path, mode & 6);
}

CRTFN(char *, crt_getcwd, _getcwd, (char *buf, int n))
{
    char cwd[PATH_MAX], dos[PATH_MAX];
    if (!getcwd(cwd, sizeof cwd))
        return NULL;
    path_to_dos(cwd, dos, sizeof dos);
    if (!buf)
        return strdup(dos);
    if ((int)strlen(dos) + 1 > n) {
        errno = ERANGE;
        return NULL;
    }
    return strcpy(buf, dos);
}

CRTFN(int, crt_getdrive, _getdrive, (void)) { return 3; }   /* C: */
CRTFN(int, crt_chdrive, _chdrive, (int d)) { return d == 3 ? 0 : -1; }

CRTFN(char *, crt_tmpnam, tmpnam, (char *buf))
{
    static char s[L_tmpnam + 16];
    static unsigned n;
    char *out = buf ? buf : s;
    sprintf(out, "\\grim%u.tmp", ++n + (unsigned)getpid() * 100);
    return out;
}

CRTFN(int, crt_system, system, (const char *cmd)) { plat_log("system(\"%s\") ignored", cmd ? cmd : ""); return -1; }

/* MSVC's _findfirst/_findnext (32-bit times) */
struct crt_finddata { unsigned attrib; int32_t time_create, time_access, time_write; uint32_t size; char name[260]; };

static int crt_find_fill(FindState *f, struct crt_finddata *d)
{
    char name[NAME_MAX + 1];
    int dir;
    uint32_t size;
    int64_t mtime;
    if (!find_next(f, name, sizeof name, &dir, &size, &mtime))
        return 0;
    memset(d, 0, sizeof *d);
    d->attrib = dir ? 0x10 : 0x20;
    d->time_create = d->time_access = d->time_write = (int32_t)mtime;
    d->size = size;
    snprintf(d->name, sizeof d->name, "%s", name);
    return 1;
}

CRTFN(intptr_t, crt_findfirst, _findfirst, (const char *pattern, struct crt_finddata *d))
{
    FindState *f = find_open(pattern);
    if (!f || !crt_find_fill(f, d)) {
        find_close(f);
        errno = ENOENT;
        return -1;
    }
    return (intptr_t)f;
}

CRTFN(int, crt_findnext, _findnext, (intptr_t h, struct crt_finddata *d))
{
    if (h == -1 || !crt_find_fill((FindState *)h, d)) {
        errno = ENOENT;
        return -1;
    }
    return 0;
}

CRTFN(int, crt_findclose, _findclose, (intptr_t h))
{
    if (h == -1)
        return -1;
    find_close((FindState *)h);
    return 0;
}

CRTFN(FILE *, crt_fdopen, _fdopen, (int fd, const char *mode)) { return fdopen(fd, mode); }

/* wchar_t is 16 bits on Windows */
CRTFN(uint16_t *, crt_fgetws, fgetws, (uint16_t *buf, int n, FILE *f))
{
    int i = 0, c = EOF;
    while (i < n - 1 && (c = fgetc(f)) != EOF) {
        int c2 = fgetc(f);
        if (c2 == EOF)
            break;
        buf[i++] = (uint16_t)(c | c2 << 8);
        if (buf[i - 1] == '\n')
            break;
    }
    if (i == 0 && c == EOF)
        return NULL;
    buf[i] = 0;
    return buf;
}

/* ---- strings ---- */
CRTFN(int, crt_stricmp, _stricmp, (const char *a, const char *b)) { return strcasecmp(a, b); }
CRTFN(int, crt_strnicmp, _strnicmp, (const char *a, const char *b, size_t n)) { return strncasecmp(a, b, n); }
CRTFN(char *, crt_strlwr, _strlwr, (char *s))
{
    for (char *p = s; *p; p++)
        *p = tolower((unsigned char)*p);
    return s;
}
CRTFN(char *, crt_strupr, _strupr, (char *s))
{
    for (char *p = s; *p; p++)
        *p = toupper((unsigned char)*p);
    return s;
}
CRTFN(char *, crt_strdup, _strdup, (const char *s)) { return strdup(s); }

CRTFN(int, crt_snprintf, _snprintf, (char *buf, size_t n, const char *fmt, ...))
{
    va_list ap;
    int r;
    va_start(ap, fmt);
    r = vsnprintf(buf, n, fmt, ap);
    va_end(ap);
    return (r < 0 || (size_t)r >= n) ? -1 : r;   /* MSVC: -1 when the text does not fit */
}

CRTFN(int, crt_vsnprintf, _vsnprintf, (char *buf, size_t n, const char *fmt, va_list ap))
{
    int r = vsnprintf(buf, n, fmt, ap);
    return (r < 0 || (size_t)r >= n) ? -1 : r;
}

CRTFN(int, crt_mingw_vsprintf, __mingw_vsprintf, (char *buf, const char *fmt, va_list ap)) { return vsprintf(buf, fmt, ap); }

CRTFN(int, crt_wsprintfA, wsprintfA, (char *buf, const char *fmt, ...))
{
    va_list ap;
    int r;
    va_start(ap, fmt);
    r = vsprintf(buf, fmt, ap);
    va_end(ap);
    return r;
}

/* _isctype(c, mask): MSVC's classification bits */
CRTFN(int, crt_isctype, _isctype, (int c, int mask))
{
    int r = 0;
    if (c < -1 || c > 255)
        return 0;
    if (isupper(c)) r |= 0x1;
    if (islower(c)) r |= 0x2;
    if (isdigit(c)) r |= 0x4;
    if (isspace(c)) r |= 0x8;
    if (ispunct(c)) r |= 0x10;
    if (iscntrl(c)) r |= 0x20;
    if (c == ' ' || c == '\t') r |= 0x40;
    if (isxdigit(c)) r |= 0x80;
    if (isalpha(c)) r |= 0x100;
    return r & mask;
}

CRTFN(int *, crt_errno, _errno, (void)) { return &errno; }

/* ---- rand: MSVC's generator (RAND_MAX 0x7fff) ---- */
static unsigned g_rand_seed = 1;
CRTFN(void, crt_srand, srand, (unsigned s)) { g_rand_seed = s; }
CRTFN(int, crt_rand, rand, (void))
{
    g_rand_seed = g_rand_seed * 214013u + 2531011u;
    return (g_rand_seed >> 16) & 0x7fff;
}

/* ---- time: struct tm is 36 bytes in MSVC, 44 in glibc ---- */
CRTFN(size_t, crt_strftime, strftime, (char *s, size_t n, const char *fmt, const int *msvc_tm))
{
    struct tm tm;
    memset(&tm, 0, sizeof tm);
    memcpy(&tm, msvc_tm, 9 * sizeof(int));
    return strftime(s, n, fmt, &tm);
}
CRTFN(int32_t, crt_mktime, mktime, (int *msvc_tm))
{
    struct tm tm;
    time_t t;
    memset(&tm, 0, sizeof tm);
    memcpy(&tm, msvc_tm, 9 * sizeof(int));
    t = mktime(&tm);
    memcpy(msvc_tm, &tm, 9 * sizeof(int));
    return (int32_t)t;
}

/* ---- math: the import-table slots of pow / fmod ---- */
void *crt_imp_pow EXPORT(_imp__pow) = (void *)pow;
void *crt_imp_fmod EXPORT(_imp__fmod) = (void *)fmod;

/* ---- helpers MSVC code calls with register / x87 stack arguments ---- */
__asm__(
    "\t.text\n"
    /* _setjmp3(jmp_buf, count, ...): MSVC setjmp; glibc's _setjmp fits in MSVC's 64-byte jmp_buf (28 bytes) and
       takes the buffer at the same place. The game's longjmp is glibc's. */
    "\t.globl G__setjmp3\nG__setjmp3:\n\tjmp _setjmp\n"
    /* _chkstk / _alloca_probe: allocate EAX bytes of stack (the kernel grows the stack on demand) */
    "\t.globl G___chkstk\nG___chkstk:\n\tpopl %ecx\n\tsubl %eax, %esp\n\tjmp *%ecx\n"
    "\t.globl G__alloca_probe\nG__alloca_probe:\n\tpopl %ecx\n\tsubl %eax, %esp\n\tjmp *%ecx\n"
    /* _CIacos / _CIasin: argument and result in ST(0) */
    "\t.globl G__CIacos\nG__CIacos:\n\tsubl $8, %esp\n\tfstpl (%esp)\n\tcall acos\n\taddl $8, %esp\n\tret\n"
    "\t.globl G__CIasin\nG__CIasin:\n\tsubl $8, %esp\n\tfstpl (%esp)\n\tcall asin\n\taddl $8, %esp\n\tret\n"
    "\t.globl G__CIsqrt\nG__CIsqrt:\n\tfsqrt\n\tret\n"
    /* _CIfmod: x in ST(1), y in ST(0) -> fmod(x, y) in ST(0) */
    "\t.globl G__CIfmod\nG__CIfmod:\n\tfxch %st(1)\n1:\tfprem\n\tfnstsw %ax\n\tsahf\n\tjp 1b\n\tfstp %st(1)\n\tret\n"
    /* _CIpow: x in ST(1), y in ST(0) */
    "\t.globl G__CIpow\nG__CIpow:\n\tsubl $16, %esp\n\tfstpl 8(%esp)\n\tfstpl (%esp)\n\tcall pow\n\taddl $16, %esp\n\tret\n"
    /* _ftol: ST(0) -> EAX (EDX:EAX), truncating */
    "\t.globl G__ftol\nG__ftol:\n\tsubl $12, %esp\n\tfnstcw (%esp)\n\tmovw (%esp), %ax\n\torw $0x0c00, %ax\n"
    "\tmovw %ax, 2(%esp)\n\tfldcw 2(%esp)\n\tfistpll 4(%esp)\n\tfldcw (%esp)\n\tmovl 4(%esp), %eax\n\tmovl 8(%esp), %edx\n"
    "\taddl $12, %esp\n\tret\n");

/* setvbuf: MSVC's mode values (_IOFBF 0, _IOLBF 0x40, _IONBF 4) */
CRTFN(int, crt_setvbuf, setvbuf, (FILE *f, char *buf, int mode, size_t size))
{
    return setvbuf(f, buf, mode == 4 ? _IONBF : mode == 0x40 ? _IOLBF : _IOFBF, size);
}
