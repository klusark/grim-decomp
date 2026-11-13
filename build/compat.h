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

/* CHORE.DLL (C:\grimsrc\libs\chore\Costume.c): the costume / chore / key records.
 * Layouts from the Ghidra project (/CHORE.DLL, data types of the same names; field names follow the bridge's Hungarian
 * convention), see docs/notes/chore_naming.md. Handler slots are `code *` for the same reason as in GrimServices. */
typedef struct ChoreKey {           /* 0x08: one key of a chore track */
    unsigned int dwTime;            /* 0x00 ms from the chore start */
    int nValue;                     /* 0x04 key value (float bits for float tags) */
} ChoreKey;
typedef struct ChoreTrack {         /* 0x10: the keys of one component in one chore */
    int nCompNum;                   /* 0x00 component index in the costume (-1 while being deleted) */
    unsigned int dwLastKeyTime;     /* 0x04 time of the last key */
    unsigned int dwNumKeys;         /* 0x08 */
    ChoreKey *pKeys;                /* 0x0c sorted by time (aKeys) */
} ChoreTrack;
typedef struct Chore {              /* 0x2c */
    char aName[32];                 /* 0x00 */
    unsigned int dwNumTracks;       /* 0x20 */
    ChoreTrack *pChoreTracks;       /* 0x24 (aChoreTracks) */
    unsigned int dwLength;          /* 0x28 ms */
} Chore;
typedef struct CosStateBitmap {     /* 0x14: one state of a state-based component */
    int aDesc[4];                   /* 0x00 the EXE's 16-byte description */
    int nMunged;                    /* 0x10 result of the bitmap munger (CosUtil_RegisterBitmapMunger) */
} CosStateBitmap;
typedef struct CosComponent {       /* 0x40 */
    char aName[32];                 /* 0x00 */
    int nTag;                       /* 0x20 index into g_aComponentTags */
    int nData;                      /* 0x24 the EXE's component data (Cos_RegisterComponent) */
    int nHash;                      /* 0x28 number of earlier components with the same tag and name */
    int nParent;                    /* 0x2c parent component index, -1 for a root */
    unsigned int dwNumStates;       /* 0x30 state-based tags only */
    int *pStateValues;              /* 0x34 */
    char **ppStateNames;            /* 0x38 */
    CosStateBitmap **apStateBitmaps; /* 0x3c */
} CosComponent;
typedef struct Costume {            /* 0x3c: one record of g_aCostumes, handle = index + 1 */
    char aName[32];                 /* 0x00 file name without directory */
    unsigned int dwField_0x20;      /* 0x20 not used by CHORE.DLL */
    int nId;                        /* 0x24 serial number (Cos_NewEntry) */
    unsigned int dwNumComponents;   /* 0x28 */
    CosComponent *pComponents;      /* 0x2c (aComponents) */
    unsigned int dwNumChores;       /* 0x30 */
    Chore *pChores;                 /* 0x34 */
    int nFree;                      /* 0x38 1: slot free (or the load failed) */
} Costume;
typedef struct ChoreInstance {      /* 0x0c: the state of one chore in a costume instance */
    unsigned int dwFlags;           /* 0x00 1 playing, 2 looping, 4 advanced by Cos_InstUpdateChores */
    int nChore;                     /* 0x04 chore index */
    int nTime;                      /* 0x08 ms played */
} ChoreInstance;
typedef struct CosInstance {        /* 0x14: one record of g_aCostumeInstances, handle = index + 1 */
    int nCostume;                   /* 0x00 costume index, -1 when free */
    ChoreInstance *pChoreInstances; /* 0x04 one per chore (aChoreInstances) */
    int nUserData;                  /* 0x08 the EXE's (Cos_InstSetUserData) */
    int *pInstanceData;             /* 0x0c one per component (aInstanceData), from the tag's NewInstance handler */
    int nFree;                      /* 0x10 1: record free */
} CosInstance;
typedef struct ComponentTag {       /* 0x5c: one record of g_aComponentTags */
    int nId;                        /* 0x00 four-character tag id */
    int nKind;                      /* 0x04 0 state based, 1 int, 2 float */
    char aName[32];                 /* 0x08 */
    int nUserData;                  /* 0x28 */
    code *pfnOnKey;                 /* 0x2c slot 0: a key was passed (Chore_ApplyKey) */
    code *pfnCreate;                /* 0x30 slot 1: build a component (CosUtil_AddComponent) */
    code *pfnDestroy;               /* 0x34 slot 2: free the component data (Cos_FreeComponent) */
    code *pfnStop;                  /* 0x38 slot 3: chore stopped (Cos_InstStopChore(s)) */
    code *pfnEdit;                  /* 0x3c slot 4: editor dialog (CosUtil_AdjustComponent) */
    code *pfnNewInstance;           /* 0x40 slot 5: create / free the instance data */
    code *pfnSave;                  /* 0x44 slot 6: save / restore the instance data */
    unsigned int aField_0x48[5];    /* 0x48 not used by CHORE.DLL */
} ComponentTag;
_Static_assert(sizeof(ChoreKey) == 0x08 && sizeof(ChoreTrack) == 0x10 && sizeof(Chore) == 0x2c &&
               sizeof(CosStateBitmap) == 0x14 && sizeof(CosComponent) == 0x40 && sizeof(Costume) == 0x3c &&
               sizeof(ChoreInstance) == 0x0c && sizeof(CosInstance) == 0x14 && sizeof(ComponentTag) == 0x5c,
               "CHORE.DLL record sizes");

/* The MSVC 6 runtime's memcpy is its memmove (overlapping copies work; Lua's
   luaD_openstack shifts the stack up by one slot with it). The host msvcrt
   memcpy may copy forwards and smear the overlap, so every call goes to memmove. */
#define memcpy memmove

/* float constant given as its IEEE bit pattern (Ghidra prints float arguments as hex) */
#define FBITS(b) (((union { unsigned u; float f; }){ (unsigned)(b) }).f)

/* host getenv for the test knobs */
extern char *GRIM_getenv(const char *) __asm__("_getenv");
