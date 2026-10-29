/* compat.h - force-included (gcc -include compat.h) before every file in ../src.
 *
 * Holds what the generated headers cannot know: toolchain glue, and the layouts
 * of the few Ghidra structures the code dereferences (Ghidra's struct layouts are
 * not part of the raw/ export, so tools/build_src.py only emits
 * `typedef struct X X;` for them). Keep this file small; anything that can be
 * derived from raw/ belongs in tools/build_src.py. */
#pragma once
#include <stdint.h>
typedef int code();   /* same as ghidra_types.h */
/* COM methods (DirectDraw/Direct3D/DirectInput/DirectSound) are __stdcall: the callee pops
   its arguments. Vtable calls in the DirectX modules go through this type
   (tools/build_src.py rewrites `(**(code **)(` there); with plain `code` the compiler
   assumes caller cleanup and the stack pointer drifts after every call. */
typedef int __attribute__((__stdcall__)) code_std();

/* Calling conventions. MinGW gcc predefines these; other i386 gccs do not. */
#ifndef __cdecl
#define __cdecl    __attribute__((__cdecl__))
#endif
#ifndef __stdcall
#define __stdcall  __attribute__((__stdcall__))
#endif
#ifndef __fastcall
#define __fastcall __attribute__((__fastcall__))
#endif
#ifndef __thiscall
#define __thiscall __attribute__((__thiscall__))
#endif
/* Win32/DirectX imports are declared `int STDCALL f();` in functions.h */
#define STDCALL __attribute__((__stdcall__))

/* GrimServices (0x70): the service table the EXE hands to its modules and DLLs.
 * Layout from the Ghidra project (/v101/GRIMFANDANGO.EXE, data type GrimServices).
 * Ghidra types every slot `void *`; they are declared `code *` here because the
 * decompiled code calls them directly as (*svc->pX)(...). */
typedef struct GrimServices {
    float flVersion;      /* 0x00 */
    code *pPrintf;        /* 0x04 */
    code *pPrintf2;       /* 0x08 */
    code *pWarning;       /* 0x0c */
    code *pError;         /* 0x10 */
    code *pDebug;         /* 0x14 */
    code *pAssertFail;    /* 0x18 */
    code *pFn_1c;         /* 0x1c */
    code *pAlloc;         /* 0x20 */
    code *pFree;          /* 0x24 */
    code *pRealloc;       /* 0x28 */
    code *pGetTimeMs;     /* 0x2c */
    code *pFopen;         /* 0x30 */
    code *pFclose;        /* 0x34 */
    code *pFread;         /* 0x38 */
    code *pFgets;         /* 0x3c */
    code *pFwrite;        /* 0x40 */
    code *pFeof;          /* 0x44 */
    code *pFtell;         /* 0x48 */
    code *pFseek;         /* 0x4c */
    code *pFileSize;      /* 0x50 */
    code *pFprintf;       /* 0x54 */
    code *pFn_58;         /* 0x58 */
    code *pHAlloc;        /* 0x5c */
    code *pHFree;         /* 0x60 */
    code *pHRealloc;      /* 0x64 */
    code *pHLock;         /* 0x68 */
    code *pHUnlock;       /* 0x6c */
} GrimServices;
_Static_assert(sizeof(GrimServices) == 0x70, "GrimServices is 0x70 bytes");

/* The MSVC 6 runtime's memcpy is its memmove (overlapping copies work; Lua's
   luaD_openstack shifts the stack up by one slot with it). The host msvcrt
   memcpy may copy forwards and smear the overlap, so every call goes to memmove. */
#define memcpy memmove

/* float constant given as its IEEE bit pattern (Ghidra prints float arguments as hex) */
#define FBITS(b) (((union { unsigned u; float f; }){ (unsigned)(b) }).f)
