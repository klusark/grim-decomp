/* Readable C for the CHORE.DLL costume loader Cos_LoadEntry, slice 5, second pass (agent asm_o2; see docs/notes/asm_o2.md).
 *
 * Written by hand from the original machine code (src/CHORE.DLL/asm_funcs.s) and checked against it with a
 * differential test in build/difftest/asm_s5/ (chore_test.c).  The text costume format is read line by line with
 * Cos_ReadLine (read a line of at most 0x400 bytes into the buffer at 0x10013e10) and msvc_sscanf (sscanf); the
 * format strings are unnamed .data strings, quoted in the comments.  Ghidra's text of these functions used parameter
 * slots that the original reuses as locals and lost a register-held value; the C below uses locals for them.  The four
 * section readers (Cos_Read*Section) are generated again since 2026-11-13 (the parameter slots are plain C there).
 * tools/build_src.py puts the decompiled text of every function defined here under `#if 0`. */
#include "ghidra_types.h"

#ifdef GRIM_CHORE
#include "globals.h"
#include "functions.h"

#define COS_LINE ((char *)IMG_ADDR(0x10013e10))          /* line buffer, 0x400 bytes */

/* ==== Cos_LoadEntry (0x10001770) ====
 * Loads the text costume `name` into the costume of `handle`: the costume is reset (Cos_NewEntry) and named after the
 * file name without its directory (at most 32 characters, else an error), the file is opened ("r", service +0x30) and
 * read as " costume v%d.%d" (version, not checked), " section tags" (Cos_ReadTagsSection), " section components"
 * (Cos_ReadComponentsSection), " section chores" (Cos_ReadChoresSection), " section keys" (Cos_ReadKeysSection, only with chores).  Then each chore
 * gets its length (CosUtil_SetChoreLength) and two tracks of one chore on the same component are an error.  An error
 * sets costume +0x38 (load failed), closes the file (service +0x34) and returns 0; success closes it and returns 1.
 * A file that cannot be opened only sets +0x38 (returns 0).  Kept from the original: when the name is too long the
 * "file" closed is the handle (the original's file variable is the second parameter's slot, not yet overwritten), and
 * the track check of the original compares every ordered pair (a, b), a != b. */
undefined4 Cos_LoadEntry(char *name, int handle)
{
    int costume = CosUtil_PtrFromHandle(handle);
    int file = handle;      /* the second parameter's slot holds the file later */
    int version[2];
    char *base;
    uint len;
    uint c, a, b;
    byte *chore;

    Cos_NewEntry(costume);
    base = msvc_strrchr(name, '\\');
    base = base != 0 ? base + 1 : name;
    for (len = 0; base[len] != 0; len++)
        ;
    if (len > 0x20)
        goto fail;
    msvc_strncpy((uint *)costume, (uint *)base, 0x1f);
    *(byte *)(costume + 0x1f) = 0;
    file = (g_pSvcChore->pFopen)(name, IMG_ADDR(0x10010280));     /* "r" */
    if (file == 0) {
        *(int *)(costume + 0x38) = 1;
        return 0;
    }
    g_nLineNum = 0;
    if (Cos_ReadLine(file, COS_LINE, 0x400) == 0)
        goto fail;
    msvc_sscanf(COS_LINE, (char *)IMG_ADDR(0x10010270), &version[1], &version[0]);    /* " costume v%d.%d" */
    if (Cos_ReadLine(file, COS_LINE, 0x400) == 0 || msvc_sscanf(COS_LINE, (char *)IMG_ADDR(0x10010260)) != 0)
        goto fail;
    if (Cos_ReadTagsSection(file, costume, (uint)name) == 0)
        goto fail;
    if (Cos_ReadLine(file, COS_LINE, 0x400) == 0 || msvc_sscanf(COS_LINE, (char *)IMG_ADDR(0x1001024c)) != 0)
        goto fail;
    if (Cos_ReadComponentsSection(file, handle, name, 0) == 0)
        goto fail;
    if (Cos_ReadLine(file, COS_LINE, 0x400) == 0 || msvc_sscanf(COS_LINE, (char *)IMG_ADDR(0x1001023c)) != 0)
        goto fail;
    if (Cos_ReadChoresSection(file, costume, name) == 0)
        goto fail;
    if (Cos_ReadLine(file, COS_LINE, 0x400) == 0 || msvc_sscanf(COS_LINE, (char *)IMG_ADDR(0x1001022c)) != 0)
        goto fail;
    if (*(uint *)(costume + 0x30) != 0 && Cos_ReadKeysSection(file, costume) == 0)
        goto fail;
    chore = *(byte **)(costume + 0x34);
    for (c = 0; c < *(uint *)(costume + 0x30); c++, chore += 0x2c) {
        uint n;
        byte *tracks;

        CosUtil_SetChoreLength(costume, c, *(uint *)(chore + 0x28));
        n = *(uint *)(chore + 0x20);
        for (a = 0; a < n; a++)
            for (b = 0; b < n; b++) {
                if (a == b)
                    continue;
                tracks = *(byte **)(chore + 0x24);
                if (*(int *)(tracks + a * 0x10) == *(int *)(tracks + b * 0x10))
                    goto fail;
            }
    }
    (g_pSvcChore->pFclose)(file);
    return 1;
fail:
    *(int *)(costume + 0x38) = 1;
    (g_pSvcChore->pFclose)(file);
    return 0;
}

#endif /* GRIM_CHORE */
