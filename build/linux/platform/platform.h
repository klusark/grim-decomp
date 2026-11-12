/* Native Linux platform layer: the Win32, DirectX and MSVC-runtime functions the decompiled game imports,
 * implemented on SDL2 and libc (see ../README.md).
 *
 * The game's objects are linked with every symbol prefixed `G` (link_linux.py): the game calls CreateFileA as
 * `G_CreateFileA`, its msvcrt `_stricmp` as `G__stricmp`. This layer is ordinary C; EXPORT() gives a function the
 * game-side name. Everything the game calls is cdecl unless WINAPI (stdcall, the callee pops) - as on Windows. */
#pragma once
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define WINAPI __attribute__((stdcall))
/* the game-side name of a symbol: G + its i386 COFF spelling (leading underscore) */
#define EXPORT(name) __asm__("G_" #name)
/* a Win32 function: stdcall, game-side name _<name> */
#define WINFN(ret, name, params) ret WINAPI name params EXPORT(name); ret WINAPI name params

typedef uint32_t DWORD;
typedef int32_t LONG;
typedef uint16_t WORD;
typedef uint8_t BYTE;
typedef int BOOL;
typedef uint32_t UINT;
typedef void *HANDLE;
typedef uint32_t HRESULT;

#define INVALID_HANDLE ((HANDLE)(intptr_t)-1)

/* ---- logging (stderr; GRIM_PLATLOG=1 for the verbose messages) ---- */
void plat_log(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
void plat_trace(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
extern int plat_verbose;

/* ---- start-up (init.c) ---- */
/* the x87 control word of a Windows process: 53-bit precision, round to nearest, all exceptions masked (Linux starts
 * threads with 64-bit precision, which changes the results of the game's float arithmetic) */
static inline void plat_fpu_windows(void)
{
    unsigned short cw = 0x27f;
    __asm__ volatile("fldcw %0" : : "m"(cw));
}
void plat_init(int argc, char **argv);
char *plat_command_line(void);
uint32_t plat_ms(void);              /* ms since start (GetTickCount, timeGetTime) */
uint64_t plat_us(void);              /* us since start */

/* ---- handles (init.c): every Win32 handle the layer hands out ---- */
enum { H_FREE, H_FILE, H_FIND, H_EVENT, H_THREAD, H_DC, H_BITMAP, H_PALETTE, H_FONT, H_STOCK, H_WINDOW, H_KEY };
HANDLE handle_new(int type, void *obj);
void *handle_get(HANDLE h, int type);  /* NULL if h is not a live handle of that type */
int handle_type(HANDLE h);
void handle_free(HANDLE h);

/* ---- paths (paths.c) ---- */
/* A path as the game writes it (DOS style: `C:\dir\file`, `dir\file`, `D:\GrimData`) -> the Unix path, each
 * existing component matched case-insensitively. */
void path_to_unix(const char *dos, char *out, size_t n);
/* A Unix path -> the DOS form the game sees (`/home/x` -> `C:\home\x`). */
void path_to_dos(const char *unix_path, char *out, size_t n);
const char *path_data_dir(void);     /* the game data directory (GRIM_DATA, default: the working directory), Unix form */
int wildcard_match(const char *pattern, const char *name);  /* DOS wildcards, case-insensitive */

/* ---- directory search shared by FindFirstFileA and _findfirst (kernel32.c) ---- */
typedef struct FindState FindState;
FindState *find_open(const char *dos_pattern);
/* the next match: name, is_dir, size, mtime; 0 when there is none */
int find_next(FindState *f, char *name, size_t n, int *is_dir, uint32_t *size, int64_t *mtime);
void find_close(FindState *f);

/* ---- window and events (user32.c) ---- */
void win_pump_events(void);          /* SDL events -> window messages, DirectInput state */
void *win_sdl_window(void);          /* SDL_Window * of the game window, NULL before CreateWindowExA */
void win_present(const uint32_t *argb, int w, int h);   /* show a frame (gdi32.c BitBlt to the window DC) */

/* ---- input state shared by user32.c and dinput.c ---- */
void dinput_key_event(int dik, int down, uint32_t time);
void dinput_mouse_motion(int dx, int dy, int dz, uint32_t time);
void dinput_mouse_button(int button, int down, uint32_t time);
int sdl_scancode_to_dik(int scancode);
int sdl_scancode_to_vk(int scancode);

/* ---- registry defaults (registry.c) ---- */
void registry_load(void);
