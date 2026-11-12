/* ADVAPI32 registry on a text file.
 *
 * File: $GRIM_REGISTRY, else $XDG_CONFIG_HOME/grimfandango/registry.txt (~/.config/...). One line per value:
 *     <key path>\t<value name>\t<type>\t<data as hex>
 * Key paths are lower-cased, with the root key as a number (80000002 = HKEY_LOCAL_MACHINE). Every key whose path ends
 * in `grim fandango\...` gets GrimDataDir (the data directory, see paths.c) when it has none, so the game finds its
 * data without an installer. */
#define _GNU_SOURCE
#include <ctype.h>
#include <limits.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include "platform.h"

typedef struct Value { char *key, *name; DWORD type, size; BYTE *data; struct Value *next; } Value;
typedef struct { char path[512]; } KeyObj;

static Value *g_values;
static char g_file[PATH_MAX];
static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;

static void lower(char *s) { for (; *s; s++) *s = tolower((unsigned char)*s); }

static Value *find_value(const char *key, const char *name)
{
    for (Value *v = g_values; v; v = v->next)
        if (strcmp(v->key, key) == 0 && strcasecmp(v->name, name) == 0)
            return v;
    return NULL;
}

static void set_value(const char *key, const char *name, DWORD type, const void *data, DWORD size)
{
    Value *v = find_value(key, name);
    if (!v) {
        v = calloc(1, sizeof *v);
        v->key = strdup(key);
        v->name = strdup(name);
        v->next = g_values;
        g_values = v;
    }
    free(v->data);
    v->data = malloc(size ? size : 1);
    memcpy(v->data, data, size);
    v->size = size;
    v->type = type;
}

static void save(void)
{
    char tmp[PATH_MAX + 8];
    FILE *f;
    snprintf(tmp, sizeof tmp, "%s.tmp", g_file);
    f = fopen(tmp, "w");
    if (!f)
        return;
    for (Value *v = g_values; v; v = v->next) {
        fprintf(f, "%s\t%s\t%u\t", v->key, v->name, v->type);
        for (DWORD i = 0; i < v->size; i++)
            fprintf(f, "%02x", v->data[i]);
        fputc('\n', f);
    }
    fclose(f);
    rename(tmp, g_file);
}

void registry_load(void)
{
    const char *e = getenv("GRIM_REGISTRY");
    char line[4096];
    FILE *f;
    if (e && *e) {
        snprintf(g_file, sizeof g_file, "%s", e);
    } else {
        const char *x = getenv("XDG_CONFIG_HOME"), *h = getenv("HOME");
        char dir[PATH_MAX];
        if (x && *x)
            snprintf(dir, sizeof dir, "%s/grimfandango", x);
        else
            snprintf(dir, sizeof dir, "%s/.config/grimfandango", h ? h : ".");
        if (!(x && *x)) {
            char parent[PATH_MAX];
            snprintf(parent, sizeof parent, "%s/.config", h ? h : ".");
            mkdir(parent, 0755);
        }
        mkdir(dir, 0755);
        snprintf(g_file, sizeof g_file, "%s/registry.txt", dir);
    }
    f = fopen(g_file, "r");
    if (!f)
        return;
    while (fgets(line, sizeof line, f)) {
        char *key = strtok(line, "\t"), *name = strtok(NULL, "\t"), *type = strtok(NULL, "\t"),
             *hex = strtok(NULL, "\t\r\n");
        BYTE data[2048];
        DWORD n = 0;
        if (!key || !name || !type)
            continue;
        for (; hex && hex[0] && hex[1] && n < sizeof data; hex += 2) {
            unsigned b;
            sscanf(hex, "%2x", &b);
            data[n++] = (BYTE)b;
        }
        set_value(key, name, (DWORD)atoi(type), data, n);
    }
    fclose(f);
    plat_trace("registry: %s", g_file);
}

static void key_path(HANDLE root, const char *sub, char *out, size_t n)
{
    KeyObj *k = handle_get(root, H_KEY);
    if (k)
        snprintf(out, n, "%s%s%s", k->path, sub && *sub ? "\\" : "", sub ? sub : "");
    else
        snprintf(out, n, "%08x%s%s", (unsigned)(uintptr_t)root, sub && *sub ? "\\" : "", sub ? sub : "");
    lower(out);
}

static HANDLE open_key(const char *path)
{
    KeyObj *k = calloc(1, sizeof *k);
    snprintf(k->path, sizeof k->path, "%s", path);
    /* the game key: the data directory */
    if (strstr(path, "grim fandango") && !find_value(path, "GrimDataDir")) {
        char dos[PATH_MAX];
        path_to_dos(path_data_dir(), dos, sizeof dos - 1);
        if (dos[strlen(dos) - 1] != '\\')
            strcat(dos, "\\");
        set_value(path, "GrimDataDir", 1, dos, (DWORD)strlen(dos) + 1);
        plat_log("registry: GrimDataDir = %s (set GRIM_DATA=<dir> or run in the data directory)", dos);
    }
    return handle_new(H_KEY, k);
}

WINFN(LONG, RegOpenKeyExA, (HANDLE root, const char *sub, DWORD opt, DWORD sam, HANDLE *out))
{
    char path[512];
    (void)opt; (void)sam;
    key_path(root, sub, path, sizeof path);
    pthread_mutex_lock(&g_lock);
    *out = open_key(path);
    pthread_mutex_unlock(&g_lock);
    return 0;
}

WINFN(LONG, RegCreateKeyExA, (HANDLE root, const char *sub, DWORD res, char *cls, DWORD opt, DWORD sam, void *sec,
                              HANDLE *out, DWORD *disp))
{
    (void)res; (void)cls; (void)sec;
    if (disp)
        *disp = 2;   /* REG_OPENED_EXISTING_KEY */
    return RegOpenKeyExA(root, sub, opt, sam, out);
}

WINFN(LONG, RegCloseKey, (HANDLE h))
{
    KeyObj *k = handle_get(h, H_KEY);
    if (k) {
        free(k);
        handle_free(h);
    }
    return 0;
}

WINFN(LONG, RegDeleteKeyA, (HANDLE root, const char *sub))
{
    char path[512];
    key_path(root, sub, path, sizeof path);
    pthread_mutex_lock(&g_lock);
    for (Value **p = &g_values; *p;) {
        if (strcmp((*p)->key, path) == 0) {
            Value *v = *p;
            *p = v->next;
            free(v->key), free(v->name), free(v->data), free(v);
        } else {
            p = &(*p)->next;
        }
    }
    save();
    pthread_mutex_unlock(&g_lock);
    return 0;
}

WINFN(LONG, RegQueryValueExA, (HANDLE h, const char *name, DWORD *res, DWORD *type, BYTE *data, DWORD *size))
{
    char path[512];
    Value *v;
    LONG r = 0;
    (void)res;
    key_path(h, NULL, path, sizeof path);
    pthread_mutex_lock(&g_lock);
    v = find_value(path, name ? name : "");
    if (!v) {
        r = 2;   /* ERROR_FILE_NOT_FOUND */
    } else {
        if (type)
            *type = v->type;
        if (data) {
            if (!size || *size < v->size)
                r = 234;   /* ERROR_MORE_DATA */
            else
                memcpy(data, v->data, v->size);
        }
        if (size)
            *size = v->size;
    }
    pthread_mutex_unlock(&g_lock);
    return r;
}

WINFN(LONG, RegSetValueExA, (HANDLE h, const char *name, DWORD res, DWORD type, const BYTE *data, DWORD size))
{
    char path[512];
    (void)res;
    key_path(h, NULL, path, sizeof path);
    pthread_mutex_lock(&g_lock);
    if ((type == 1 || type == 2) && (size == 0 || data[size - 1] != 0)) {
        /* REG_SZ stored with its terminator, as RegSetValueExA does (the game passes strlen() bytes) */
        BYTE *t = malloc(size + 1);
        memcpy(t, data, size);
        t[size] = 0;
        set_value(path, name ? name : "", type, t, size + 1);
        free(t);
    } else {
        set_value(path, name ? name : "", type, data, size);
    }
    save();
    pthread_mutex_unlock(&g_lock);
    return 0;
}

WINFN(LONG, RegEnumValueA, (HANDLE h, DWORD index, char *name, DWORD *namelen, DWORD *res, DWORD *type, BYTE *data,
                            DWORD *size))
{
    char path[512];
    DWORD i = 0;
    LONG r = 259;   /* ERROR_NO_MORE_ITEMS */
    (void)res;
    key_path(h, NULL, path, sizeof path);
    pthread_mutex_lock(&g_lock);
    for (Value *v = g_values; v; v = v->next) {
        if (strcmp(v->key, path) != 0)
            continue;
        if (i++ != index)
            continue;
        if (strlen(v->name) + 1 > *namelen) {
            r = 234;
            break;
        }
        strcpy(name, v->name);
        *namelen = (DWORD)strlen(v->name);
        if (type)
            *type = v->type;
        if (data && size && *size >= v->size)
            memcpy(data, v->data, v->size);
        if (size)
            *size = v->size;
        r = 0;
        break;
    }
    pthread_mutex_unlock(&g_lock);
    return r;
}

WINFN(LONG, RegQueryInfoKeyA, (HANDLE h, char *cls, DWORD *clslen, DWORD *res, DWORD *subkeys, DWORD *maxsub,
                               DWORD *maxcls, DWORD *values, DWORD *maxname, DWORD *maxdata, DWORD *sec, void *time))
{
    char path[512];
    DWORD n = 0, mn = 0, md = 0;
    (void)res; (void)time;
    key_path(h, NULL, path, sizeof path);
    pthread_mutex_lock(&g_lock);
    for (Value *v = g_values; v; v = v->next) {
        if (strcmp(v->key, path) != 0)
            continue;
        n++;
        if (strlen(v->name) > mn)
            mn = (DWORD)strlen(v->name);
        if (v->size > md)
            md = v->size;
    }
    pthread_mutex_unlock(&g_lock);
    if (cls && clslen && *clslen)
        cls[0] = 0;
    if (clslen) *clslen = 0;
    if (subkeys) *subkeys = 0;
    if (maxsub) *maxsub = 0;
    if (maxcls) *maxcls = 0;
    if (values) *values = n;
    if (maxname) *maxname = mn;
    if (maxdata) *maxdata = md;
    if (sec) *sec = 0;
    return 0;
}
