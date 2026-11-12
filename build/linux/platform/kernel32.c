/* KERNEL32 on libc / pthreads: files, directory search, threads, events, critical sections, time, memory. */
#define _GNU_SOURCE
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <pthread.h>
#include <sched.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <time.h>
#include <unistd.h>
#include "platform.h"

/* ---------------- files ---------------- */
typedef struct { int fd; } FileObj;

#define GENERIC_READ 0x80000000u
#define GENERIC_WRITE 0x40000000u
#define FILE_APPEND_DATA 4u

WINFN(HANDLE, CreateFileA, (const char *name, DWORD access, DWORD share, void *sec, DWORD disposition, DWORD flags,
                            HANDLE tmpl))
{
    char path[PATH_MAX];
    int oflags, fd;
    (void)share; (void)sec; (void)flags; (void)tmpl;
    path_to_unix(name, path, sizeof path);
    if ((access & GENERIC_READ) && (access & (GENERIC_WRITE | FILE_APPEND_DATA)))
        oflags = O_RDWR;
    else if (access & (GENERIC_WRITE | FILE_APPEND_DATA))
        oflags = O_WRONLY;
    else
        oflags = O_RDONLY;
    if ((access & FILE_APPEND_DATA) && !(access & GENERIC_WRITE))
        oflags |= O_APPEND;
    switch (disposition) {
    case 1: oflags |= O_CREAT | O_EXCL; break;    /* CREATE_NEW */
    case 2: oflags |= O_CREAT | O_TRUNC; break;   /* CREATE_ALWAYS */
    case 4: oflags |= O_CREAT; break;             /* OPEN_ALWAYS */
    case 5: oflags |= O_TRUNC; break;             /* TRUNCATE_EXISTING */
    default: break;                               /* OPEN_EXISTING */
    }
    fd = open(path, oflags, 0644);
    plat_trace("CreateFileA(%s -> %s) = %d", name, path, fd);
    if (fd < 0)
        return INVALID_HANDLE;
    FileObj *f = malloc(sizeof *f);
    f->fd = fd;
    return handle_new(H_FILE, f);
}

WINFN(BOOL, ReadFile, (HANDLE h, void *buf, DWORD n, DWORD *got, void *ovl))
{
    FileObj *f = handle_get(h, H_FILE);
    ssize_t r;
    (void)ovl;
    if (got)
        *got = 0;
    if (!f)
        return 0;
    r = read(f->fd, buf, n);
    if (r < 0)
        return 0;
    if (got)
        *got = (DWORD)r;
    return 1;
}

WINFN(BOOL, WriteFile, (HANDLE h, const void *buf, DWORD n, DWORD *put, void *ovl))
{
    FileObj *f = handle_get(h, H_FILE);
    ssize_t r;
    (void)ovl;
    if (put)
        *put = 0;
    if (!f)
        return 0;
    r = write(f->fd, buf, n);
    if (r < 0)
        return 0;
    if (put)
        *put = (DWORD)r;
    return 1;
}

WINFN(DWORD, SetFilePointer, (HANDLE h, LONG dist, LONG *high, DWORD method))
{
    FileObj *f = handle_get(h, H_FILE);
    off_t r;
    if (!f)
        return 0xffffffffu;
    r = lseek(f->fd, dist, method == 1 ? SEEK_CUR : method == 2 ? SEEK_END : SEEK_SET);
    if (high)
        *high = 0;
    return r < 0 ? 0xffffffffu : (DWORD)r;
}

WINFN(DWORD, GetFileSize, (HANDLE h, DWORD *high))
{
    FileObj *f = handle_get(h, H_FILE);
    struct stat st;
    if (high)
        *high = 0;
    if (!f || fstat(f->fd, &st) != 0)
        return 0xffffffffu;
    return (DWORD)st.st_size;
}

/* thread.c / events below release their handles here too */
static void close_sync_object(HANDLE h);

WINFN(BOOL, CloseHandle, (HANDLE h))
{
    FileObj *f;
    switch (handle_type(h)) {
    case H_FILE:
        f = handle_get(h, H_FILE);
        close(f->fd);
        free(f);
        handle_free(h);
        return 1;
    case H_EVENT:
    case H_THREAD:
        close_sync_object(h);
        return 1;
    default:
        return 0;
    }
}

WINFN(BOOL, DeleteFileA, (const char *name))
{
    char path[PATH_MAX];
    path_to_unix(name, path, sizeof path);
    return unlink(path) == 0;
}

WINFN(BOOL, MoveFileA, (const char *from, const char *to))
{
    char a[PATH_MAX], b[PATH_MAX];
    path_to_unix(from, a, sizeof a);
    path_to_unix(to, b, sizeof b);
    return rename(a, b) == 0;
}

/* ---------------- directory search ---------------- */
struct FindState {
    DIR *dir;                  /* NULL: a single entry (single_name), already resolved */
    char dirpath[PATH_MAX];
    char pattern[NAME_MAX + 1];
    char single_name[NAME_MAX + 1];
    int single_left;
    struct stat single_st;
};

FindState *find_open(const char *dos_pattern)
{
    char dospart[PATH_MAX], unixdir[PATH_MAX];
    const char *slash = NULL, *p;
    FindState *f;
    for (p = dos_pattern; *p; p++)
        if (*p == '\\' || *p == '/' || (*p == ':' && p == dos_pattern + 1))
            slash = p;
    if (slash) {
        size_t n = slash - dos_pattern + 1;
        if (n >= sizeof dospart)
            return NULL;
        memcpy(dospart, dos_pattern, n);
        dospart[n] = 0;
        path_to_unix(dospart, unixdir, sizeof unixdir);
        p = slash + 1;
    } else {
        strcpy(unixdir, ".");
        p = dos_pattern;
    }
    f = calloc(1, sizeof *f);
    if (*p && !strpbrk(p, "*?")) {
        /* no wildcard: the path itself (this also finds D:\GrimData, the virtual CD's only entry) */
        char full[PATH_MAX];
        path_to_unix(dos_pattern, full, sizeof full);
        if (stat(full, &f->single_st) != 0) {
            free(f);
            return NULL;
        }
        snprintf(f->single_name, sizeof f->single_name, "%s", strrchr(full, '/') ? strrchr(full, '/') + 1 : full);
        f->single_left = 1;
        return f;
    }
    snprintf(f->dirpath, sizeof f->dirpath, "%s", unixdir);
    snprintf(f->pattern, sizeof f->pattern, "%s", *p ? p : "*");
    /* no wildcard: the entry itself, matched case-insensitively by the wildcard compare */
    f->dir = opendir(unixdir);
    if (!f->dir) {
        free(f);
        return NULL;
    }
    return f;
}

int find_next(FindState *f, char *name, size_t n, int *is_dir, uint32_t *size, int64_t *mtime)
{
    struct dirent *e;
    if (!f->dir) {
        if (!f->single_left)
            return 0;
        f->single_left = 0;
        snprintf(name, n, "%s", f->single_name);
        *is_dir = S_ISDIR(f->single_st.st_mode);
        *size = (uint32_t)f->single_st.st_size;
        *mtime = f->single_st.st_mtime;
        return 1;
    }
    while ((e = readdir(f->dir)) != NULL) {
        char full[PATH_MAX * 2];
        struct stat st;
        if (!wildcard_match(f->pattern, e->d_name))
            continue;
        snprintf(full, sizeof full, "%s/%s", f->dirpath, e->d_name);
        if (stat(full, &st) != 0)
            continue;
        snprintf(name, n, "%s", e->d_name);
        *is_dir = S_ISDIR(st.st_mode);
        *size = (uint32_t)st.st_size;
        *mtime = st.st_mtime;
        return 1;
    }
    return 0;
}

void find_close(FindState *f)
{
    if (f) {
        if (f->dir)
            closedir(f->dir);
        free(f);
    }
}

#pragma pack(push, 1)
typedef struct {
    DWORD dwFileAttributes;
    uint64_t ftCreationTime, ftLastAccessTime, ftLastWriteTime;
    DWORD nFileSizeHigh, nFileSizeLow, dwReserved0, dwReserved1;
    char cFileName[260];
    char cAlternateFileName[14];
} WIN32_FIND_DATAA;
#pragma pack(pop)

static uint64_t unix_to_filetime(int64_t t) { return (uint64_t)(t + 11644473600LL) * 10000000ULL; }

static int fill_find_data(FindState *f, WIN32_FIND_DATAA *d)
{
    char name[NAME_MAX + 1];
    int dir;
    uint32_t size;
    int64_t mtime;
    if (!find_next(f, name, sizeof name, &dir, &size, &mtime))
        return 0;
    memset(d, 0, sizeof *d);
    d->dwFileAttributes = dir ? 0x10 : 0x20;   /* DIRECTORY / ARCHIVE */
    d->ftCreationTime = d->ftLastAccessTime = d->ftLastWriteTime = unix_to_filetime(mtime);
    d->nFileSizeLow = size;
    snprintf(d->cFileName, sizeof d->cFileName, "%s", name);
    return 1;
}

WINFN(HANDLE, FindFirstFileA, (const char *pattern, WIN32_FIND_DATAA *d))
{
    FindState *f = find_open(pattern);
    plat_trace("FindFirstFileA(%s) -> %s", pattern, f ? "dir" : "none");
    if (!f)
        return INVALID_HANDLE;
    if (!fill_find_data(f, d)) {
        find_close(f);
        return INVALID_HANDLE;
    }
    return handle_new(H_FIND, f);
}

WINFN(BOOL, FindNextFileA, (HANDLE h, WIN32_FIND_DATAA *d))
{
    FindState *f = handle_get(h, H_FIND);
    return f && fill_find_data(f, d);
}

WINFN(BOOL, FindClose, (HANDLE h))
{
    FindState *f = handle_get(h, H_FIND);
    if (!f)
        return 0;
    find_close(f);
    handle_free(h);
    return 1;
}

/* ---------------- directories, drives ---------------- */
WINFN(DWORD, GetCurrentDirectoryA, (DWORD n, char *buf))
{
    char cwd[PATH_MAX], dos[PATH_MAX];
    if (!getcwd(cwd, sizeof cwd))
        strcpy(cwd, "/");
    path_to_dos(cwd, dos, sizeof dos);
    if (strlen(dos) + 1 > n)
        return (DWORD)strlen(dos) + 1;
    strcpy(buf, dos);
    return (DWORD)strlen(dos);
}

WINFN(BOOL, SetCurrentDirectoryA, (const char *dir))
{
    char path[PATH_MAX];
    path_to_unix(dir, path, sizeof path);
    return chdir(path) == 0;
}

WINFN(DWORD, GetFullPathNameA, (const char *name, DWORD n, char *buf, char **filepart))
{
    char cwd[PATH_MAX] = "", full[PATH_MAX * 2];
    DWORD len;
    if (!(name[0] && name[1] == ':') && name[0] != '\\' && name[0] != '/') {
        GetCurrentDirectoryA(sizeof cwd, cwd);
        snprintf(full, sizeof full, "%s\\%s", cwd, name);
    } else {
        snprintf(full, sizeof full, "%s", name);
    }
    len = (DWORD)strlen(full);
    if (len + 1 > n)
        return len + 1;
    strcpy(buf, full);
    if (filepart) {
        char *s = strrchr(buf, '\\');
        *filepart = s ? s + 1 : buf;
    }
    return len;
}

WINFN(DWORD, GetTempPathA, (DWORD n, char *buf))
{
    const char *t = getenv("TMPDIR");
    char dos[PATH_MAX];
    path_to_dos(t && *t ? t : "/tmp", dos, sizeof dos - 1);
    strcat(dos, "\\");
    if (strlen(dos) + 1 > n)
        return (DWORD)strlen(dos) + 1;
    strcpy(buf, dos);
    return (DWORD)strlen(dos);
}

WINFN(UINT, GetTempFileNameA, (const char *dir, const char *prefix, UINT unique, char *out))
{
    static unsigned counter;
    char path[PATH_MAX];
    for (int tries = 0; tries < 1000; tries++) {
        unsigned u = unique ? unique : (unsigned)(getpid() + ++counter) & 0xffff;
        snprintf(out, 260, "%s%s%.3s%04X.TMP", dir,
                 (dir[0] && dir[strlen(dir) - 1] != '\\') ? "\\" : "", prefix, u);
        if (unique)
            return u;
        path_to_unix(out, path, sizeof path);
        int fd = open(path, O_CREAT | O_EXCL | O_WRONLY, 0644);
        if (fd >= 0) {
            close(fd);
            return u;
        }
    }
    return 0;
}

WINFN(BOOL, GetDiskFreeSpaceA, (const char *root, DWORD *spc, DWORD *bps, DWORD *freec, DWORD *total))
{
    (void)root;
    if (spc) *spc = 8;
    if (bps) *bps = 512;
    if (freec) *freec = 0x40000;    /* 1 GB: enough for any save, small enough for 32-bit products */
    if (total) *total = 0x80000;
    return 1;
}

WINFN(UINT, GetDriveTypeA, (const char *root))
{
    int d = root && root[0] ? (root[0] & ~0x20) : 'C';
    if (d == 'C')
        return 3;   /* DRIVE_FIXED */
    if (d == 'D')
        return 5;   /* DRIVE_CDROM: the virtual game CD (paths.c) */
    return 1;       /* DRIVE_NO_ROOT_DIR */
}

WINFN(DWORD, GetLogicalDriveStringsA, (DWORD n, char *buf))
{
    static const char drives[] = "C:\\\0D:\\\0";   /* + the final NUL */
    if (n < sizeof drives)
        return sizeof drives;
    memcpy(buf, drives, sizeof drives);
    return sizeof drives - 1;
}

/* ---------------- modules, environment, misc ---------------- */
WINFN(HANDLE, GetModuleHandleA, (const char *name)) { return name ? NULL : (HANDLE)0x400000; }
WINFN(HANDLE, LoadLibraryA, (const char *name)) { plat_trace("LoadLibraryA(%s): not available", name); return NULL; }
WINFN(void *, GetProcAddress, (HANDLE mod, const char *name)) { (void)mod; (void)name; return NULL; }
WINFN(BOOL, FreeLibrary, (HANDLE mod)) { (void)mod; return 1; }

WINFN(DWORD, GetModuleFileNameA, (HANDLE mod, char *buf, DWORD n))
{
    char exe[PATH_MAX], dos[PATH_MAX];
    ssize_t r = readlink("/proc/self/exe", exe, sizeof exe - 1);
    (void)mod;
    exe[r > 0 ? r : 0] = 0;
    path_to_dos(exe, dos, sizeof dos);
    snprintf(buf, n, "%s", dos);
    return (DWORD)strlen(buf);
}

WINFN(DWORD, GetEnvironmentVariableA, (const char *name, char *buf, DWORD n))
{
    const char *v = getenv(name);
    size_t l;
    if (!v)
        return 0;
    l = strlen(v);
    if (l + 1 > n)
        return (DWORD)l + 1;
    memcpy(buf, v, l + 1);
    return (DWORD)l;
}

WINFN(void, OutputDebugStringA, (const char *s)) { plat_trace("debug: %s", s); }
WINFN(void, DebugBreak, (void)) { plat_log("DebugBreak"); }
WINFN(DWORD, GetLastError, (void)) { return 0; }
WINFN(void, SetLastError, (DWORD e)) { (void)e; }
WINFN(DWORD, GetCurrentThreadId, (void)) { return (DWORD)(uintptr_t)pthread_self(); }
WINFN(HANDLE, GetCurrentProcess, (void)) { return (HANDLE)(intptr_t)-1; }
WINFN(DWORD, GetVersion, (void)) { return 0x0a280105; }   /* Windows XP-ish: 5.1 */

WINFN(int, MultiByteToWideChar, (UINT cp, DWORD flags, const char *src, int srclen, uint16_t *dst, int dstlen))
{
    int n = srclen < 0 ? (int)strlen(src) + 1 : srclen;
    (void)cp; (void)flags;
    if (dstlen == 0)
        return n;
    if (n > dstlen)
        n = dstlen;
    for (int i = 0; i < n; i++)
        dst[i] = (unsigned char)src[i];   /* Latin-1, the game's text */
    return n;
}

WINFN(int, WideCharToMultiByte, (UINT cp, DWORD flags, const uint16_t *src, int srclen, char *dst, int dstlen,
                                 const char *def, BOOL *used))
{
    int n = srclen;
    (void)cp; (void)flags; (void)def;
    if (used)
        *used = 0;
    if (n < 0) {
        n = 0;
        while (src[n])
            n++;
        n++;
    }
    if (dstlen == 0)
        return n;
    if (n > dstlen)
        n = dstlen;
    for (int i = 0; i < n; i++)
        dst[i] = src[i] < 256 ? (char)src[i] : '?';
    return n;
}

WINFN(int, GetLocaleInfoA, (DWORD lcid, DWORD type, char *buf, int n)) { (void)lcid; (void)type; (void)buf; (void)n; return 0; }

typedef struct { WORD wYear, wMonth, wDayOfWeek, wDay, wHour, wMinute, wSecond, wMilliseconds; } SYSTEMTIME;
WINFN(void, GetLocalTime, (SYSTEMTIME *st))
{
    struct timespec ts;
    struct tm tm;
    clock_gettime(CLOCK_REALTIME, &ts);
    localtime_r(&ts.tv_sec, &tm);
    st->wYear = tm.tm_year + 1900;
    st->wMonth = tm.tm_mon + 1;
    st->wDayOfWeek = tm.tm_wday;
    st->wDay = tm.tm_mday;
    st->wHour = tm.tm_hour;
    st->wMinute = tm.tm_min;
    st->wSecond = tm.tm_sec;
    st->wMilliseconds = ts.tv_nsec / 1000000;
}

/* ---------------- time ---------------- */
WINFN(DWORD, GetTickCount, (void)) { return plat_ms(); }
WINFN(BOOL, QueryPerformanceFrequency, (int64_t *f)) { *f = 1000000; return 1; }
WINFN(BOOL, QueryPerformanceCounter, (int64_t *c)) { *c = (int64_t)plat_us(); return 1; }
WINFN(void, Sleep, (DWORD ms)) { struct timespec t = { ms / 1000, (ms % 1000) * 1000000L }; nanosleep(&t, NULL); }

/* ---------------- memory ---------------- */
WINFN(HANDLE, GetProcessHeap, (void)) { return (HANDLE)0x10000; }
WINFN(void *, HeapAlloc, (HANDLE heap, DWORD flags, DWORD n))
{
    (void)heap;
    return (flags & 8) ? calloc(1, n ? n : 1) : malloc(n ? n : 1);   /* HEAP_ZERO_MEMORY */
}
WINFN(BOOL, HeapFree, (HANDLE heap, DWORD flags, void *p)) { (void)heap; (void)flags; free(p); return 1; }

typedef struct {
    DWORD dwLength, dwMemoryLoad, dwTotalPhys, dwAvailPhys, dwTotalPageFile, dwAvailPageFile, dwTotalVirtual,
        dwAvailVirtual;
} MEMORYSTATUS;
WINFN(void, GlobalMemoryStatus, (MEMORYSTATUS *m))
{
    m->dwLength = sizeof *m;
    m->dwMemoryLoad = 10;
    m->dwTotalPhys = m->dwTotalPageFile = m->dwTotalVirtual = 0x40000000u;   /* 1 GB: fits the game's ints */
    m->dwAvailPhys = m->dwAvailPageFile = m->dwAvailVirtual = 0x30000000u;
}

/* ---------------- critical sections: the game's 24-byte CRITICAL_SECTION holds a pthread mutex pointer -------- */
static pthread_mutex_t g_cs_init = PTHREAD_MUTEX_INITIALIZER;

static pthread_mutex_t *cs_mutex(void **cs)
{
    pthread_mutex_t *m = __atomic_load_n(cs, __ATOMIC_ACQUIRE);
    if (m)
        return m;
    pthread_mutex_lock(&g_cs_init);
    m = *cs;
    if (!m) {
        pthread_mutexattr_t a;
        m = malloc(sizeof *m);
        pthread_mutexattr_init(&a);
        pthread_mutexattr_settype(&a, PTHREAD_MUTEX_RECURSIVE);
        pthread_mutex_init(m, &a);
        __atomic_store_n(cs, m, __ATOMIC_RELEASE);
    }
    pthread_mutex_unlock(&g_cs_init);
    return m;
}

WINFN(void, InitializeCriticalSection, (void **cs)) { memset(cs, 0, 24); cs_mutex(cs); }
WINFN(void, EnterCriticalSection, (void **cs)) { pthread_mutex_lock(cs_mutex(cs)); }
WINFN(void, LeaveCriticalSection, (void **cs)) { pthread_mutex_unlock(cs_mutex(cs)); }
WINFN(void, DeleteCriticalSection, (void **cs))
{
    pthread_mutex_t *m = *cs;
    if (m) {
        pthread_mutex_destroy(m);
        free(m);
        *cs = NULL;
    }
}

WINFN(LONG, InterlockedIncrement, (LONG *p)) { return __sync_add_and_fetch(p, 1); }
WINFN(LONG, InterlockedDecrement, (LONG *p)) { return __sync_sub_and_fetch(p, 1); }
WINFN(LONG, InterlockedExchange, (LONG *p, LONG v)) { return __sync_lock_test_and_set(p, v); }

/* ---------------- events and threads ---------------- */
typedef struct {
    pthread_mutex_t m;
    pthread_cond_t c;
    int manual, signaled;      /* event */
    int is_thread, done;       /* thread */
    DWORD exit_code;
    pthread_t tid;
    DWORD (WINAPI *start)(void *);
    void *arg;
    int refs;                  /* the handle + the running thread */
} SyncObj;

static SyncObj *sync_new(int is_thread)
{
    SyncObj *s = calloc(1, sizeof *s);
    pthread_mutex_init(&s->m, NULL);
    pthread_cond_init(&s->c, NULL);
    s->is_thread = is_thread;
    s->exit_code = 0x103;    /* STILL_ACTIVE */
    s->refs = 1;
    return s;
}

static void sync_unref(SyncObj *s)
{
    pthread_mutex_lock(&s->m);
    int left = --s->refs;
    pthread_mutex_unlock(&s->m);
    if (left == 0) {
        pthread_mutex_destroy(&s->m);
        pthread_cond_destroy(&s->c);
        free(s);
    }
}

static void close_sync_object(HANDLE h)
{
    SyncObj *s = handle_get(h, handle_type(h));
    handle_free(h);
    if (s)
        sync_unref(s);
}

WINFN(HANDLE, CreateEventA, (void *sec, BOOL manual, BOOL initial, const char *name))
{
    SyncObj *s = sync_new(0);
    (void)sec; (void)name;
    s->manual = manual;
    s->signaled = initial;
    return handle_new(H_EVENT, s);
}

WINFN(BOOL, SetEvent, (HANDLE h))
{
    SyncObj *s = handle_get(h, H_EVENT);
    if (!s)
        return 0;
    pthread_mutex_lock(&s->m);
    s->signaled = 1;
    pthread_cond_broadcast(&s->c);
    pthread_mutex_unlock(&s->m);
    return 1;
}

WINFN(BOOL, ResetEvent, (HANDLE h))
{
    SyncObj *s = handle_get(h, H_EVENT);
    if (!s)
        return 0;
    pthread_mutex_lock(&s->m);
    s->signaled = 0;
    pthread_mutex_unlock(&s->m);
    return 1;
}

WINFN(DWORD, WaitForSingleObject, (HANDLE h, DWORD ms))
{
    SyncObj *s = handle_get(h, handle_type(h) == H_THREAD ? H_THREAD : H_EVENT);
    struct timespec until;
    DWORD r = 0;
    if (!s)
        return 0xffffffffu;   /* WAIT_FAILED */
    clock_gettime(CLOCK_REALTIME, &until);
    until.tv_sec += ms / 1000;
    until.tv_nsec += (ms % 1000) * 1000000L;
    if (until.tv_nsec >= 1000000000L)
        until.tv_sec++, until.tv_nsec -= 1000000000L;
    pthread_mutex_lock(&s->m);
    while (!(s->is_thread ? s->done : s->signaled)) {
        if (ms == 0xffffffffu)
            pthread_cond_wait(&s->c, &s->m);
        else if (pthread_cond_timedwait(&s->c, &s->m, &until) == ETIMEDOUT) {
            r = 0x102;   /* WAIT_TIMEOUT */
            break;
        }
    }
    if (r == 0 && !s->is_thread && !s->manual)
        s->signaled = 0;
    pthread_mutex_unlock(&s->m);
    return r;
}

static void *thread_main(void *p)
{
    SyncObj *s = p;
    DWORD code;
    plat_fpu_windows();
    code = s->start(s->arg);
    pthread_mutex_lock(&s->m);
    s->exit_code = code;
    s->done = 1;
    pthread_cond_broadcast(&s->c);
    pthread_mutex_unlock(&s->m);
    sync_unref(s);
    return NULL;
}

WINFN(HANDLE, CreateThread, (void *sec, DWORD stack, DWORD (WINAPI *start)(void *), void *arg, DWORD flags,
                             DWORD *id))
{
    SyncObj *s = sync_new(1);
    pthread_attr_t a;
    (void)sec; (void)flags;
    s->start = start;
    s->arg = arg;
    s->refs = 2;
    pthread_attr_init(&a);
    pthread_attr_setstacksize(&a, stack > 0x100000 ? stack : 0x100000);
    pthread_attr_setdetachstate(&a, PTHREAD_CREATE_DETACHED);
    if (pthread_create(&s->tid, &a, thread_main, s) != 0) {
        pthread_attr_destroy(&a);
        free(s);
        return NULL;
    }
    pthread_attr_destroy(&a);
    if (id)
        *id = (DWORD)(uintptr_t)s->tid;
    return handle_new(H_THREAD, s);
}

WINFN(BOOL, GetExitCodeThread, (HANDLE h, DWORD *code))
{
    SyncObj *s = handle_get(h, H_THREAD);
    if (!s)
        return 0;
    pthread_mutex_lock(&s->m);
    *code = s->exit_code;
    pthread_mutex_unlock(&s->m);
    if (*code == 0x103)
        sched_yield();
    return 1;
}

WINFN(BOOL, SetThreadPriority, (HANDLE h, int prio)) { (void)h; (void)prio; return 1; }
