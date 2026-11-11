/* Test patches for grim_tools/cleanroom (see README.md in this folder).
 *
 * The clean-room tests start the original v1.01 exe through grimlaunch.exe, which patches its code in memory. Those
 * patches look for the original's bytes at fixed addresses, so they cannot work on this rebuilt exe. Here are the
 * same patches written against the decompiled functions instead. The link wraps the functions named on the WRAPS line
 * (ld --wrap, see build/link.py): every call of X goes to __wrap_X here, which calls __real_X (the decompiled X) unless
 * its test knob is set. Nothing changes without the environment variables below.
 *
 *   GRIM_INI=<file>       the settings come from and go to this ini file, not the registry (grimlaunch's "config" patch,
 *                         launcher/config.c). Without it the game reads GrimDataDir from the registry and would find the
 *                         real game's data.
 *   GRIM_DEBUGLOG=<file>  (overrides.c writes PrintDebug's text there) and PrintDebug("CRSNAP:<file>") saves the screen
 *                         to <file> (a .bmp, relative to the working directory) with the game's own screenshot code,
 *                         like patch.dll's GrimLogDebug.
 *
 * The other grimlaunch patches are knobs of this build already: simtime is GRIM_SIMTIME=<ms> (overrides_exe.c), the game
 * runs windowed by default (Win_CreateMainWindow in overrides.c), and GRIM_ACTIVE=1 keeps it drawing behind other
 * windows. */

#ifdef GRIM_EXE
/* WRAPS: Reg_Open wuRegistry_Shutdown Reg_HasValue Reg_GetInt wuRegistry_GetFloat Reg_GetBinary wuRegistry_GetStr wuRegistry_QueryType */
/* WRAPS: Reg_SetInt wuRegistry_SaveFloat Reg_SetBinary wuRegistry_SaveStr Lua_Print_NoOp */

/* the host C runtime (msvcrt); no system headers: compat.h and the decompiled code define their own names */
typedef struct _iobuf FILE;
extern char *getenv(const char *);
extern FILE *fopen(const char *, const char *);
extern int fclose(FILE *);
extern char *fgets(char *, int, FILE *);
extern int fputs(const char *, FILE *);
extern int fprintf(FILE *, const char *, ...);
extern int sprintf(char *, const char *, ...);
extern double strtod(const char *, char **);
extern void *malloc(unsigned);
extern void *realloc(void *, unsigned);
extern void free(void *);
extern char *_strdup(const char *);
extern int _stricmp(const char *, const char *);
extern int strncmp(const char *, const char *, unsigned);
extern char *strchr(const char *, int);
extern char *strncpy(char *, const char *, unsigned);
extern int tolower(int);
extern int isspace(int);
extern void *memmove(void *, const void *, unsigned);

/* LUA.DLL */
extern int lua_lua2C(int);
extern int lua_isstring(int);
extern char *lua_getstring(int);

/* the decompiled functions (the originals of the wrappers below) */
extern void __real_Reg_Open(void *root, unsigned subkey, char *version);
extern void __real_wuRegistry_Shutdown(void);
extern int __real_Reg_HasValue(char *name);
extern int __real_Reg_GetInt(char *name, int def);
extern float __real_wuRegistry_GetFloat(char *name, float def);
extern int __real_Reg_GetBinary(char *name, void *data, int size);
extern int __real_wuRegistry_GetStr(char *name, char *buf, int size, char *def);
extern int __real_wuRegistry_QueryType(char *name);
extern int __real_Reg_SetInt(char *name, int value);
extern int __real_wuRegistry_SaveFloat(char *name, float value);
extern int __real_Reg_SetBinary(char *name, void *data, int size);
extern void __real_wuRegistry_SaveStr(char *name, char *value);
extern void __real_Lua_Print_NoOp(void);
extern void sputRender_SaveDrawBuffer(char *filename);

/* ---- GRIM_INI: the settings in a file (the format of grimlaunch's grim.ini) ----
 * One `name=value` per line; [sections] and lines starting with ; or # are ignored; names are not case sensitive:
 *   name=text               a string (the registry's REG_SZ)
 *   name="3"                a string that looks like a number
 *   name=3, name=1.5        a number (what the game writes with SetInt / SetFloat; REG_BINARY in the registry)
 *   name=hex:0a0b0c         bytes (SetBinary), and what a number of 4 bytes may look like */

typedef struct { char *name, *value; } IniEntry;
static IniEntry *ini_entries;
static int ini_count, ini_cap, ini_opened;
static char ini_path[1024];

static int ini_on(void)
{
    static int on = -1;
    if (on < 0) {
        const char *e = getenv("GRIM_INI");
        on = e != 0 && e[0] != 0;
        if (on) {
            strncpy(ini_path, e, sizeof ini_path - 1);
            ini_path[sizeof ini_path - 1] = 0;
        }
    }
    return on;
}

static void ini_trim(char *s)
{
    char *a = s, *e;
    while (isspace((unsigned char)*a))
        a++;
    memmove(s, a, __builtin_strlen(a) + 1);
    e = s + __builtin_strlen(s);
    while (e > s && isspace((unsigned char)e[-1]))
        *--e = 0;
}

static IniEntry *ini_find(const char *name)
{
    int i;
    for (i = 0; i < ini_count; i++)
        if (!_stricmp(ini_entries[i].name, name))
            return &ini_entries[i];
    return 0;
}

static IniEntry *ini_lookup(const char *name)
{
    return ini_opened ? ini_find(name) : 0;
}

static void ini_store(const char *name, const char *value)
{
    IniEntry *e = ini_find(name);
    if (e) {
        free(e->value);
    } else {
        if (ini_count == ini_cap) {
            ini_cap = ini_cap ? ini_cap * 2 : 32;
            ini_entries = (IniEntry *)realloc(ini_entries, ini_cap * sizeof *ini_entries);
        }
        e = &ini_entries[ini_count++];
        e->name = _strdup(name);
    }
    e->value = _strdup(value);
}

static void ini_save(void)
{
    FILE *f = fopen(ini_path, "wb");
    int i;
    if (!f)
        return;
    fputs("[Grim]\r\n", f);
    for (i = 0; i < ini_count; i++)
        fprintf(f, "%s=%s\r\n", ini_entries[i].name, ini_entries[i].value);
    fclose(f);
}

static void ini_load(void)
{
    FILE *f = fopen(ini_path, "rb");
    char line[2048];
    ini_count = 0;
    if (!f)
        return;
    while (fgets(line, sizeof line, f)) {
        char *eq;
        ini_trim(line);
        if (!*line || *line == ';' || *line == '#' || *line == '[')
            continue;
        eq = strchr(line, '=');
        if (!eq)
            continue;
        *eq = 0;
        ini_trim(line);
        ini_trim(eq + 1);
        if (*line)
            ini_store(line, eq + 1);
    }
    fclose(f);
}

enum { T_NONE = 0, T_STRING = 1, T_NUMBER = 3 };   /* the registry's types the game uses: REG_SZ and REG_BINARY */

static int ini_is_number(const char *s)
{
    char *end;
    if (!*s)
        return 0;
    strtod(s, &end);
    return !*end;
}

static int ini_is_quoted(const char *s)
{
    unsigned n = __builtin_strlen(s);
    return n >= 2 && s[0] == '"' && s[n - 1] == '"';
}

static int ini_is_hex(const char *s)
{
    return !strncmp(s, "hex:", 4);
}

static int ini_type(const char *value)
{
    if (ini_is_quoted(value))
        return T_STRING;
    return ini_is_hex(value) || ini_is_number(value) ? T_NUMBER : T_STRING;
}

static int ini_hex_byte(const char *p)
{
    int v = 0, i;
    for (i = 0; i < 2; i++) {
        int c = tolower((unsigned char)p[i]);
        if (c >= '0' && c <= '9')
            v = v * 16 + c - '0';
        else if (c >= 'a' && c <= 'f')
            v = v * 16 + c - 'a' + 10;
        else
            return -1;
    }
    return v;
}

/* the bytes of a hex: value, -1 if it is not valid */
static int ini_hex_bytes(const char *value, unsigned char *out, int size)
{
    int n = 0;
    const char *p = value + 4;
    while (p[0] && p[1]) {
        int b = ini_hex_byte(p);
        if (b < 0 || n >= size)
            return -1;
        out[n++] = (unsigned char)b;
        p += 2;
    }
    return *p ? -1 : n;
}

/* ---- the registry wrapper of the game (wuregistry: Reg_Open, Reg_GetInt, ...) ---- */

void __wrap_Reg_Open(void *root, unsigned subkey, char *version)
{
    if (!ini_on()) {
        __real_Reg_Open(root, subkey, version);
        return;
    }
    ini_load();
    ini_opened = 1;
}

void __wrap_wuRegistry_Shutdown(void)
{
    if (!ini_on()) {
        __real_wuRegistry_Shutdown();
        return;
    }
    ini_opened = 0;
}

int __wrap_Reg_HasValue(char *name)
{
    if (!ini_on())
        return __real_Reg_HasValue(name);
    return ini_opened ? ini_find(name) != 0 : 1;   /* before Reg_Open the original says yes to everything */
}

int __wrap_Reg_GetInt(char *name, int def)
{
    IniEntry *e;
    unsigned char b[4];
    if (!ini_on())
        return __real_Reg_GetInt(name, def);
    if (!(e = ini_lookup(name)))
        return def;
    if (ini_is_hex(e->value))
        return ini_hex_bytes(e->value, b, 4) == 4 ? (int)(b[0] | b[1] << 8 | b[2] << 16 | (unsigned)b[3] << 24) : def;
    return ini_type(e->value) == T_NUMBER ? (int)strtod(e->value, 0) : def;
}

float __wrap_wuRegistry_GetFloat(char *name, float def)
{
    IniEntry *e;
    union { unsigned char b[4]; float f; } u;
    if (!ini_on())
        return __real_wuRegistry_GetFloat(name, def);
    if (!(e = ini_lookup(name)))
        return def;
    if (ini_is_hex(e->value))
        return ini_hex_bytes(e->value, u.b, 4) == 4 ? u.f : def;
    return ini_type(e->value) == T_NUMBER ? (float)strtod(e->value, 0) : def;
}

int __wrap_wuRegistry_GetStr(char *name, char *buf, int size, char *def)
{
    IniEntry *e;
    const char *v;
    unsigned n;
    if (!ini_on())
        return __real_wuRegistry_GetStr(name, buf, size, def);
    if (!(e = ini_lookup(name)) || size < 1)
        return 0;   /* like the original, the buffer is left alone when the value does not exist */
    v = e->value;
    n = __builtin_strlen(v);
    if (ini_is_quoted(v)) {
        v++;
        n -= 2;
    }
    if ((int)n > size - 1)
        n = size - 1;
    memmove(buf, v, n);
    buf[n] = 0;
    return 1;
}

int __wrap_Reg_GetBinary(char *name, void *data, int size)
{
    IniEntry *e;
    if (!ini_on())
        return __real_Reg_GetBinary(name, data, size);
    e = ini_lookup(name);
    return e && ini_is_hex(e->value) && ini_hex_bytes(e->value, (unsigned char *)data, size) >= 0;
}

int __wrap_wuRegistry_QueryType(char *name)
{
    IniEntry *e;
    if (!ini_on())
        return __real_wuRegistry_QueryType(name);
    e = ini_lookup(name);
    return e ? ini_type(e->value) : T_NONE;
}

int __wrap_Reg_SetInt(char *name, int value)
{
    char s[32];
    if (!ini_on())
        return __real_Reg_SetInt(name, value);
    sprintf(s, "%d", value);
    ini_store(name, s);
    ini_save();
    return 1;
}

int __wrap_wuRegistry_SaveFloat(char *name, float value)
{
    char s[32];
    if (!ini_on())
        return __real_wuRegistry_SaveFloat(name, value);
    sprintf(s, "%.9g", (double)value);
    ini_store(name, s);
    ini_save();
    return 1;
}

void __wrap_wuRegistry_SaveStr(char *name, char *value)
{
    unsigned n;
    char *s;
    if (!ini_on()) {
        __real_wuRegistry_SaveStr(name, value);
        return;
    }
    n = __builtin_strlen(value);
    s = (char *)malloc(n + 3);
    /* a string that would read back as something else is quoted */
    if (ini_is_number(value) || ini_is_hex(value) || *value == '"' || isspace((unsigned char)*value) ||
        (n && isspace((unsigned char)value[n - 1])))
        sprintf(s, "\"%s\"", value);
    else
        memmove(s, value, n + 1);
    ini_store(name, s);
    free(s);
    ini_save();
}

int __wrap_Reg_SetBinary(char *name, void *data, int size)
{
    char *s;
    int i;
    if (!ini_on())
        return __real_Reg_SetBinary(name, data, size);
    s = (char *)malloc(4 + 2 * size + 1);
    memmove(s, "hex:", 5);
    for (i = 0; i < size; i++)
        sprintf(s + 4 + 2 * i, "%02x", ((const unsigned char *)data)[i]);
    ini_store(name, s);
    free(s);
    ini_save();
    return 1;
}

/* ---- PrintDebug("CRSNAP:<file>"): a picture of the screen (sputRender_SaveDrawBuffer, the Backspace+S debug key) ---- */

void __wrap_Lua_Print_NoOp(void)
{
    if (getenv("GRIM_DEBUGLOG")) {
        int arg = lua_lua2C(1);
        if (lua_isstring(arg)) {
            char *s = lua_getstring(arg);
            if (!strncmp(s, "CRSNAP:", 7)) {
                sputRender_SaveDrawBuffer(s + 7);
                return;
            }
        }
    }
    __real_Lua_Print_NoOp();
}
#endif
