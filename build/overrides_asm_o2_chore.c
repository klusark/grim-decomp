/* Readable C for CHORE.DLL costume loader functions of slice 5, second pass (agent asm_o2; see docs/notes/asm_o2.md).
 *
 * Written by hand from the original machine code (src/CHORE.DLL/asm_funcs.s) and checked against it with a
 * differential test in build/difftest/asm_s5/ (chore_test.c).  The text costume format is read line by line with
 * Cos_ReadLine (read a line of at most 0x400 bytes into the buffer at 0x10013e10) and msvc_sscanf (sscanf); the
 * format strings are unnamed .data strings, quoted in the comments.  Ghidra's text of these functions used parameter
 * slots that the original reuses as locals (the tag count, loop counters) and lost a register-held value; the C below
 * uses locals for them.  tools/build_src.py puts the decompiled text of every function defined here under `#if 0`. */
#include "ghidra_types.h"

#ifdef GRIM_CHORE
#include "globals.h"
#include "functions.h"

#define COS_LINE ((char *)IMG_ADDR(0x10013e10))          /* line buffer, 0x400 bytes */
#define COS_TAG_IDS ((uint *)&g_aTagLookups)               /* tag index -> tag type, filled by Cos_ReadTagsSection */
#define COS_SVC_ALLOC(n, line) (((int (*)(int, char *, int))g_pSvcChore->pAlloc)((n), s_C__grimsrc_libs_chore_Costume_c_1001020c, (line)))
#define COS_SVC_ASSERT(msg, line) (((void (*)(char *, char *, int))g_pSvcChore->pAssertFail)((msg), s_C__grimsrc_libs_chore_Costume_c_1001020c, (line)))

/* ==== Cos_ReadTagsSection (0x100041e0): costume tag section ====
 * Reads " numtags %d" and that many lines " %d '%4c' %s %[^\n\r]" (index, four-character tag id, type "fs" / "int" /
 * "float" = 0 / 1 / 2, name); Cos_FindTag(id, name, type) gives the tag type, stored at COS_TAG_IDS[index].  An unknown
 * type or a short line returns 0.  Only the first parameter (the file) is used; the original scans the count into the
 * first parameter's slot after copying the file to a register.  Locals keep the original frame layout (the type
 * string runs into the name buffer when it is longer than 11 characters). */
undefined4 Cos_ReadTagsSection(undefined4 file, undefined4 unused2, uint unused3)
{
    struct {
        int id;          /* '%4c' */
        int index;
        char type[12];
        char name[32];
    } f;
    uint count = file;
    uint i;
    int kind;

    if (Cos_ReadLine(file, COS_LINE, 0x400) == 0)
        return 0;
    if (msvc_sscanf(COS_LINE, (char *)IMG_ADDR(0x10010538), &count) != 1)    /* " numtags %d" */
        return 0;
    for (i = 0; i < count; i++) {
        if (Cos_ReadLine(file, COS_LINE, 0x400) == 0)
            return 0;
        if (msvc_sscanf(COS_LINE, (char *)IMG_ADDR(0x10010524), &f.index, &f.id, f.type, f.name) != 4)
            return 0;
        if (msvc_stricmp((byte *)f.type, (byte *)IMG_ADDR(0x1001019c)) == 0)          /* "fs" */
            kind = 0;
        else if (msvc_stricmp((byte *)f.type, (byte *)IMG_ADDR(0x10010198)) == 0)     /* "int" */
            kind = 1;
        else if (msvc_stricmp((byte *)f.type, (byte *)IMG_ADDR(0x10010190)) == 0)     /* "float" */
            kind = 2;
        else
            return 0;
        COS_TAG_IDS[f.index] = Cos_FindTag(f.id, f.name, kind);
    }
    return 1;
}

/* ==== Cos_ReadChoresSection (0x100047f0): costume chore headers ====
 * Reads " numchores %d" into costume +0x30, allocates the chores (0x2c bytes each, +0x34; on failure the count is set
 * to 0 and 0 returned), initialises each with Cos_InitChore and reads one line per chore " %d %d %d %[^\n\r]" (index,
 * ignored; length +0x28; track count +0x20; name +0).  The tracks (16 bytes each) are allocated at +0x24; a failed
 * allocation is only reported ("pChore->aChoreTracks != ((void *)0)").  Returns 1, 0 on a short file or line.
 * The original keeps the chore counter in the second parameter's slot. */
undefined4 Cos_ReadChoresSection(undefined4 file, int costume, undefined4 unused3)
{
    uint *count = (uint *)(costume + 0x30);
    int index;
    byte *chore;
    uint i;
    int ret;

    ret = Cos_ReadLine(file, COS_LINE, 0x400);
    if (ret == 0)
        return ret;
    if (msvc_sscanf(COS_LINE, (char *)IMG_ADDR(0x100105c0), count) != 1)    /* " numchores %d" */
        return 0;
    if (*count != 0) {
        *(int *)(costume + 0x34) = COS_SVC_ALLOC(*count * 0x2c, 0xc7e);
        if (*(int *)(costume + 0x34) == 0) {
            *count = 0;
            return 0;
        }
    } else
        *(int *)(costume + 0x34) = 0;
    chore = *(byte **)(costume + 0x34);
    for (i = 0; i < *count; i++, chore += 0x2c)
        Cos_InitChore((int)chore);
    chore = *(byte **)(costume + 0x34);
    for (i = 0; i < *count; i++, chore += 0x2c) {
        if (Cos_ReadLine(file, COS_LINE, 0x400) == 0)
            return 0;
        if (msvc_sscanf(COS_LINE, (char *)IMG_ADDR(0x100105ac), &index, chore + 0x28, chore + 0x20, chore) != 4)
            return 0;    /* " %d %d %d %[^\n\r]" */
        if (*(uint *)(chore + 0x20) != 0) {
            *(int *)(chore + 0x24) = COS_SVC_ALLOC(*(uint *)(chore + 0x20) << 4, 0xca1);
            if (*(int *)(chore + 0x24) == 0)
                COS_SVC_ASSERT((char *)IMG_ADDR(0x10010588), 0xca2);
        } else
            *(int *)(chore + 0x24) = 0;
    }
    return 1;
}

/* ==== Cos_ReadKeysSection (0x10004970): costume chore tracks and keys ====
 * For each chore of the costume: " chore %d" gives the chore index; for each of its tracks (16 bytes: +0 component,
 * +4 last key time, +8 key count, +0xc keys) " %d %d" gives the component (translated through the table at
 * g_aComponentLookups) and the key count; the keys (8 bytes: time, value) are allocated (failure only reported:
 * "pCTrack->aKeys != ((void *)0)") and read with " %d %d", or " %d %f" when the tag type of the component
 * (component +0x20, tag type records of 0x5c bytes at ((int *)g_aComponentTags), kind at +4) is a float tag.  The track's +4 is the
 * time of its last key (0 without keys).  Returns 1, 0 on a short file or line. */
undefined4 Cos_ReadKeysSection(undefined4 file, int costume)
{
    uint i;
    uint j;
    uint k;
    int index;
    byte *chore;
    uint *track;
    uint *key;
    int *tagtype;

    for (i = 0; i < *(uint *)(costume + 0x30); i++) {
        if (Cos_ReadLine(file, COS_LINE, 0x400) == 0)
            return 0;
        if (msvc_sscanf(COS_LINE, (char *)IMG_ADDR(0x10010600), &index) != 1)    /* " chore %d" */
            return 0;
        chore = *(byte **)(costume + 0x34) + index * 0x2c;
        track = *(uint **)(chore + 0x24);
        for (j = 0; j < *(uint *)(chore + 0x20); j++, track += 4) {
            if (Cos_ReadLine(file, COS_LINE, 0x400) == 0)
                return 0;
            if (msvc_sscanf(COS_LINE, (char *)IMG_ADDR(0x100105f8), &track[0], &track[2]) != 2)    /* " %d %d" */
                return 0;
            track[0] = (*(uint **)&g_aComponentLookups)[track[0]];
            if (track[2] != 0) {
                track[3] = COS_SVC_ALLOC(track[2] << 3, 0xcda);
                if (track[3] == 0)
                    COS_SVC_ASSERT((char *)IMG_ADDR(0x100105d8), 0xcdb);
            } else
                track[3] = 0;
            key = (uint *)track[3];
            tagtype = ((int *)g_aComponentTags) + *(int *)(*(int *)(costume + 0x2c) + track[0] * 0x40 + 0x20) * 0x17;
            for (k = 0; k < track[2]; k++, key += 2) {
                if (Cos_ReadLine(file, COS_LINE, 0x400) == 0)
                    return 0;
                if (tagtype[1] == 0 || tagtype[1] == 1) {
                    if (msvc_sscanf(COS_LINE, (char *)IMG_ADDR(0x100105f8), &key[0], &key[1]) != 2)    /* " %d %d" */
                        return 0;
                } else {
                    if (msvc_sscanf(COS_LINE, (char *)IMG_ADDR(0x100105d0), &key[0], &key[1]) != 2)    /* " %d %f" */
                        return 0;
                }
            }
            track[1] = track[2] != 0 ? ((uint *)track[3])[track[2] * 2 - 2] : 0;
        }
    }
    return 1;
}


/* ==== Cos_ReadComponentsSection (0x10004390): costume component section ====
 * Reads " numcomponents %d" and that many lines " %d %d %d %d %[^\n\r]" into a temporary array of 64 byte records
 * (index, ignored; tag index -> +0x20 through COS_TAG_IDS; +0x28; parent index +0x2c (-1 for none); name +0).  0
 * components, a failed allocation ("aComponents != ((void *)0)"), a short file or line return 0 (the array is not
 * freed then).  The index map g_aComponentLookups (g_dwNumComponentLookups entries) grows to the component count.  The depth of every
 * component in the parent tree is counted ("aTreeDepths != ((void *)0)" if that array cannot be allocated) and the
 * components are added level by level: Cos_FindComponentWithParent looks for an existing one; if there is none the component is
 * added under its parent's component (Cos_FindComponent finds the parent's, CosUtil_AddComponent with the parent's +0x24 and
 * tag type) or as a root, and its index (Cos_FindComponent) goes into the map.  Failures free both arrays and return 0;
 * success frees them and returns 1.  The original keeps the component array in the first parameter's slot. */
undefined4 Cos_ReadComponentsSection(undefined4 file, undefined4 handle, undefined4 unused3, undefined4 unused4)
{
    int costume = CosUtil_PtrFromHandle(handle);
    uint n;
    int index;
    int tag;
    byte *comps;
    byte *comp;
    uint *depth;
    uint maxdepth;
    uint level;
    uint i;
    int p;
    int r;

#define TAGTYPE0(t) (((int *)g_aComponentTags)[(t) * 0x17])     /* first dword of a tag type record (0x5c bytes) */
    if (Cos_ReadLine(file, COS_LINE, 0x400) == 0)
        return 0;
    if (msvc_sscanf(COS_LINE, (char *)IMG_ADDR(0x10010574), &n) != 1)    /* " numcomponents %d" */
        return 0;
    comps = 0;
    if (n != 0) {
        comps = (byte *)COS_SVC_ALLOC(n << 6, 0xbdf);
        if (comps == 0)
            COS_SVC_ASSERT((char *)IMG_ADDR(0x10010558), 0xbe0);
    }
    if (comps == 0)
        return 0;
    if (g_dwNumComponentLookups < n) {
        *(int *)&g_aComponentLookups = ((int (*)(int, int, char *, int))g_pSvcChore->pRealloc)((int)g_aComponentLookups, n * 4,
                                                                                             s_C__grimsrc_libs_chore_Costume_c_1001020c, 0xbeb);
        g_dwNumComponentLookups = n;
    }
    for (i = 0; i < n; i++) {
        comp = comps + i * 0x40;
        if (Cos_ReadLine(file, COS_LINE, 0x400) == 0)
            return 0;
        if (msvc_sscanf(COS_LINE, (char *)IMG_ADDR(0x10010544), &index, &tag, comp + 0x28, comp + 0x2c, comp) != 5)
            return 0;    /* " %d %d %d %d %[^\n\r]" */
        *(uint *)(comp + 0x20) = COS_TAG_IDS[tag];
    }
    depth = (uint *)COS_SVC_ALLOC(n * 4, 0xc02);
    if (depth == 0)
        COS_SVC_ASSERT((char *)IMG_ADDR(0x10010288), 0xc03);
    maxdepth = 0;
    for (i = 0; i < n; i++) {
        depth[i] = 0;
        for (p = *(int *)(comps + i * 0x40 + 0x2c); p != -1; p = *(int *)(comps + p * 0x40 + 0x2c))
            depth[i] = depth[i] + 1;
        if (maxdepth <= depth[i])
            maxdepth = depth[i];
    }
    level = 0;
    do {
        for (i = 0; i < n; i++) {
            comp = comps + i * 0x40;
            if (depth[i] != level)
                continue;
            p = *(int *)(comp + 0x2c);
            r = Cos_FindComponentWithParent(costume, TAGTYPE0(*(int *)(comp + 0x20)), *(int *)(comp + 0x28), comp, p);
            if (r >= 0)
                continue;
            if (p >= 0) {
                byte *pc = comps + p * 0x40;
                byte *cc;

                r = Cos_FindComponent(costume, TAGTYPE0(*(int *)(pc + 0x20)), *(int *)(pc + 0x28), pc);
                if (r < 0)
                    goto fail;
                cc = (byte *)(*(int *)(costume + 0x2c) + r * 0x40);
                if (CosUtil_AddComponent(handle, comp, TAGTYPE0(*(int *)(comp + 0x20)), *(undefined4 *)(cc + 0x24),
                                         TAGTYPE0(*(int *)(cc + 0x20))) == 0)
                    goto fail;
            } else {
                if (CosUtil_AddComponent(handle, comp, TAGTYPE0(*(int *)(comp + 0x20)), 0, 0) == 0)
                    goto fail;
            }
            (*(int **)&g_aComponentLookups)[i] = Cos_FindComponent(costume, TAGTYPE0(*(int *)(comp + 0x20)), *(int *)(comp + 0x28), comp);
            if ((*(int **)&g_aComponentLookups)[i] < 0)
                goto fail;
        }
        level++;
    } while (level <= maxdepth);
    (g_pSvcChore->pFree)(comps);
    (g_pSvcChore->pFree)(depth);
    return 1;
fail:
    (g_pSvcChore->pFree)(comps);
    (g_pSvcChore->pFree)(depth);
    return 0;
#undef TAGTYPE0
}


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
