/* DOS paths as the game writes them <-> Unix paths.
 *
 * The game sees DOS-style paths: the working directory is `C:\home\me\grim`, the data directory (registry value
 * GrimDataDir) `C:\...\GRIMDATA\`. `C:` (or any drive letter but D:) is the Unix root. D: is a virtual CD-ROM whose
 * only entry, `D:\GrimData`, is the data directory: the start-up check Grim_FindDataOnDrives looks for
 * `<CD drive>\GrimData` as the original did with the game CD in the drive.
 *
 * Every existing component of a path is matched case-insensitively (the game asks for `DATA000.LAB`, `Scripts\`,
 * `_system.lua` in whatever case the original data has). */
#define _GNU_SOURCE
#include <ctype.h>
#include <dirent.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <unistd.h>
#include "platform.h"

static char g_data_dir[PATH_MAX];

const char *path_data_dir(void)
{
    if (!g_data_dir[0]) {
        const char *e = getenv("GRIM_DATA");
        if (e && *e && realpath(e, g_data_dir))
            ;
        else if (!getcwd(g_data_dir, sizeof g_data_dir))
            strcpy(g_data_dir, ".");
    }
    return g_data_dir;
}

static int wm(const char *p, const char *s)
{
    if (!*p)
        return !*s;
    if (*p == '*') {
        for (;;) {
            if (wm(p + 1, s))
                return 1;
            if (!*s)
                return 0;
            s++;
        }
    }
    if (!*s || (*p != '?' && tolower((unsigned char)*p) != tolower((unsigned char)*s)))
        return 0;
    return wm(p + 1, s + 1);
}

int wildcard_match(const char *p, const char *s)
{
    if (strcmp(p, "*.*") == 0)      /* also matches names without a dot, as on Windows */
        p = "*";
    return wm(p, s);
}

/* append component `c` (length n) to the Unix path `out`, matching an existing entry case-insensitively */
static void append_component(char *out, size_t cap, const char *c, size_t n)
{
    size_t len = strlen(out);
    char name[NAME_MAX + 1];
    struct stat st;
    if (n > NAME_MAX)
        n = NAME_MAX;
    memcpy(name, c, n);
    name[n] = 0;
    if (len + n + 2 >= cap)
        return;
    if (len == 0 || out[len - 1] != '/')
        out[len++] = '/', out[len] = 0;
    strcpy(out + len, name);
    if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0 || lstat(out, &st) == 0)
        return;
    out[len] = 0;
    DIR *d = opendir(len ? out : "/");
    if (d) {
        struct dirent *e;
        while ((e = readdir(d)) != NULL) {
            if (strcasecmp(e->d_name, name) == 0) {
                strcpy(name, e->d_name);
                break;
            }
        }
        closedir(d);
    }
    strcpy(out + len, name);
}

void path_to_unix(const char *dos, char *out, size_t cap)
{
    const char *p = dos;
    out[0] = 0;
    if (!dos || cap < 2)
        return;
    if (isalpha((unsigned char)p[0]) && p[1] == ':') {
        int drive = toupper((unsigned char)p[0]);
        p += 2;
        while (*p == '\\' || *p == '/')
            p++;
        if (drive == 'D') {
            /* the virtual CD: D:\GrimData is the data directory */
            if (strncasecmp(p, "GrimData", 8) == 0 && (p[8] == 0 || p[8] == '\\' || p[8] == '/')) {
                snprintf(out, cap, "%s", path_data_dir());
                p += 8;
            } else {
                snprintf(out, cap, "/nonexistent-cd");
            }
        } else {
            strcpy(out, "/");
        }
    } else if (*p == '\\' || *p == '/') {
        strcpy(out, "/");
    } else {
        /* relative: resolved against the working directory component by component, kept relative */
        out[0] = 0;
    }
    while (*p) {
        const char *c;
        while (*p == '\\' || *p == '/')
            p++;
        if (!*p)
            break;
        c = p;
        while (*p && *p != '\\' && *p != '/')
            p++;
        if (out[0] == 0) {
            /* first component of a relative path */
            char tmp[PATH_MAX] = ".";
            append_component(tmp, sizeof tmp, c, p - c);
            snprintf(out, cap, "%s", tmp + 2);
        } else {
            append_component(out, cap, c, p - c);
        }
    }
    if (out[0] == 0)
        snprintf(out, cap, "%s", (dos[0] == '\\' || dos[0] == '/' || dos[1] == ':') ? "/" : ".");
    /* keep a trailing separator: "dir\" names a directory */
    {
        size_t l = strlen(dos), o = strlen(out);
        if (l && (dos[l - 1] == '\\' || dos[l - 1] == '/') && o && out[o - 1] != '/' && o + 1 < cap)
            out[o] = '/', out[o + 1] = 0;
    }
}

void path_to_dos(const char *u, char *out, size_t cap)
{
    size_t o = 0;
    if (cap < 4)
        return;
    if (u[0] == '/') {
        out[o++] = 'C';
        out[o++] = ':';
    }
    for (; *u && o + 1 < cap; u++)
        out[o++] = *u == '/' ? '\\' : *u;
    if (o == 2 && out[1] == ':' && o + 1 < cap)
        out[o++] = '\\';
    out[o] = 0;
}
