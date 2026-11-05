/* Readable C for CHORE.DLL costume loader functions of slice 5, second pass (agent asm_o2; see docs/notes/asm_o2.md).
 *
 * Written by hand from the original machine code (src/CHORE.DLL/asm_funcs.s) and checked against it with a
 * differential test in build/difftest/asm_s5/ (chore_test.c).  The text costume format is read line by line with
 * FUN_10004bb0 (read a line of at most 0x400 bytes into the buffer at 0x10013e10) and FUN_10005810 (sscanf); the
 * format strings are unnamed .data strings, quoted in the comments.  Ghidra's text of these functions used parameter
 * slots that the original reuses as locals (the tag count, loop counters) and lost a register-held value; the C below
 * uses locals for them.  tools/build_src.py puts the decompiled text of every function defined here under `#if 0`. */
#include "ghidra_types.h"

#ifdef GRIM_CHORE
#include "globals.h"
#include "functions.h"

#define COS_LINE ((char *)IMG_ADDR(0x10013e10))          /* line buffer, 0x400 bytes */
#define COS_TAG_IDS ((uint *)&DAT_10014210)               /* tag index -> tag type, filled by FUN_100041e0 */
#define COS_SVC_ALLOC(n, line) (((int (*)(int, char *, int))*(code **)(DAT_100143a8 + 0x20))((n), s_C__grimsrc_libs_chore_Costume_c_1001020c, (line)))
#define COS_SVC_ASSERT(msg, line) (((void (*)(char *, char *, int))*(code **)(DAT_100143a8 + 0x18))((msg), s_C__grimsrc_libs_chore_Costume_c_1001020c, (line)))

/* ==== FUN_100041e0 (0x100041e0): costume tag section ====
 * Reads " numtags %d" and that many lines " %d '%4c' %s %[^\n\r]" (index, four-character tag id, type "fs" / "int" /
 * "float" = 0 / 1 / 2, name); FUN_10004320(id, name, type) gives the tag type, stored at COS_TAG_IDS[index].  An unknown
 * type or a short line returns 0.  Only the first parameter (the file) is used; the original scans the count into the
 * first parameter's slot after copying the file to a register.  Locals keep the original frame layout (the type
 * string runs into the name buffer when it is longer than 11 characters). */
undefined4 FUN_100041e0(undefined4 file, undefined4 unused2, uint unused3)
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

    if (FUN_10004bb0(file, COS_LINE, 0x400) == 0)
        return 0;
    if (FUN_10005810(COS_LINE, (char *)IMG_ADDR(0x10010538), &count) != 1)    /* " numtags %d" */
        return 0;
    for (i = 0; i < count; i++) {
        if (FUN_10004bb0(file, COS_LINE, 0x400) == 0)
            return 0;
        if (FUN_10005810(COS_LINE, (char *)IMG_ADDR(0x10010524), &f.index, &f.id, f.type, f.name) != 4)
            return 0;
        if (FUN_10005740((byte *)f.type, (byte *)IMG_ADDR(0x1001019c)) == 0)          /* "fs" */
            kind = 0;
        else if (FUN_10005740((byte *)f.type, (byte *)IMG_ADDR(0x10010198)) == 0)     /* "int" */
            kind = 1;
        else if (FUN_10005740((byte *)f.type, (byte *)IMG_ADDR(0x10010190)) == 0)     /* "float" */
            kind = 2;
        else
            return 0;
        COS_TAG_IDS[f.index] = FUN_10004320(f.id, f.name, kind);
    }
    return 1;
}

/* ==== FUN_100047f0 (0x100047f0): costume chore headers ====
 * Reads " numchores %d" into costume +0x30, allocates the chores (0x2c bytes each, +0x34; on failure the count is set
 * to 0 and 0 returned), initialises each with FUN_10004140 and reads one line per chore " %d %d %d %[^\n\r]" (index,
 * ignored; length +0x28; track count +0x20; name +0).  The tracks (16 bytes each) are allocated at +0x24; a failed
 * allocation is only reported ("pChore->aChoreTracks != ((void *)0)").  Returns 1, 0 on a short file or line.
 * The original keeps the chore counter in the second parameter's slot. */
undefined4 FUN_100047f0(undefined4 file, int costume, undefined4 unused3)
{
    uint *count = (uint *)(costume + 0x30);
    int index;
    byte *chore;
    uint i;
    int ret;

    ret = FUN_10004bb0(file, COS_LINE, 0x400);
    if (ret == 0)
        return ret;
    if (FUN_10005810(COS_LINE, (char *)IMG_ADDR(0x100105c0), count) != 1)    /* " numchores %d" */
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
        FUN_10004140((int)chore);
    chore = *(byte **)(costume + 0x34);
    for (i = 0; i < *count; i++, chore += 0x2c) {
        if (FUN_10004bb0(file, COS_LINE, 0x400) == 0)
            return 0;
        if (FUN_10005810(COS_LINE, (char *)IMG_ADDR(0x100105ac), &index, chore + 0x28, chore + 0x20, chore) != 4)
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

/* ==== FUN_10004970 (0x10004970): costume chore tracks and keys ====
 * For each chore of the costume: " chore %d" gives the chore index; for each of its tracks (16 bytes: +0 component,
 * +4 last key time, +8 key count, +0xc keys) " %d %d" gives the component (translated through the table at
 * DAT_100143d0) and the key count; the keys (8 bytes: time, value) are allocated (failure only reported:
 * "pCTrack->aKeys != ((void *)0)") and read with " %d %d", or " %d %f" when the tag type of the component
 * (component +0x20, tag type records of 0x5c bytes at PTR_100143c0, kind at +4) is a float tag.  The track's +4 is the
 * time of its last key (0 without keys).  Returns 1, 0 on a short file or line. */
undefined4 FUN_10004970(undefined4 file, int costume)
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
        if (FUN_10004bb0(file, COS_LINE, 0x400) == 0)
            return 0;
        if (FUN_10005810(COS_LINE, (char *)IMG_ADDR(0x10010600), &index) != 1)    /* " chore %d" */
            return 0;
        chore = *(byte **)(costume + 0x34) + index * 0x2c;
        track = *(uint **)(chore + 0x24);
        for (j = 0; j < *(uint *)(chore + 0x20); j++, track += 4) {
            if (FUN_10004bb0(file, COS_LINE, 0x400) == 0)
                return 0;
            if (FUN_10005810(COS_LINE, (char *)IMG_ADDR(0x100105f8), &track[0], &track[2]) != 2)    /* " %d %d" */
                return 0;
            track[0] = (*(uint **)&DAT_100143d0)[track[0]];
            if (track[2] != 0) {
                track[3] = COS_SVC_ALLOC(track[2] << 3, 0xcda);
                if (track[3] == 0)
                    COS_SVC_ASSERT((char *)IMG_ADDR(0x100105d8), 0xcdb);
            } else
                track[3] = 0;
            key = (uint *)track[3];
            tagtype = PTR_100143c0 + *(int *)(*(int *)(costume + 0x2c) + track[0] * 0x40 + 0x20) * 0x17;
            for (k = 0; k < track[2]; k++, key += 2) {
                if (FUN_10004bb0(file, COS_LINE, 0x400) == 0)
                    return 0;
                if (tagtype[1] == 0 || tagtype[1] == 1) {
                    if (FUN_10005810(COS_LINE, (char *)IMG_ADDR(0x100105f8), &key[0], &key[1]) != 2)    /* " %d %d" */
                        return 0;
                } else {
                    if (FUN_10005810(COS_LINE, (char *)IMG_ADDR(0x100105d0), &key[0], &key[1]) != 2)    /* " %d %f" */
                        return 0;
                }
            }
            track[1] = track[2] != 0 ? ((uint *)track[3])[track[2] * 2 - 2] : 0;
        }
    }
    return 1;
}


/* ==== FUN_10004390 (0x10004390): costume component section ====
 * Reads " numcomponents %d" and that many lines " %d %d %d %d %[^\n\r]" into a temporary array of 64 byte records
 * (index, ignored; tag index -> +0x20 through COS_TAG_IDS; +0x28; parent index +0x2c (-1 for none); name +0).  0
 * components, a failed allocation ("aComponents != ((void *)0)"), a short file or line return 0 (the array is not
 * freed then).  The index map DAT_100143d0 (DAT_100143d4 entries) grows to the component count.  The depth of every
 * component in the parent tree is counted ("aTreeDepths != ((void *)0)" if that array cannot be allocated) and the
 * components are added level by level: FUN_10004770 looks for an existing one; if there is none the component is
 * added under its parent's component (FUN_10004170 finds the parent's, CosUtil_AddComponent with the parent's +0x24 and
 * tag type) or as a root, and its index (FUN_10004170) goes into the map.  Failures free both arrays and return 0;
 * success frees them and returns 1.  The original keeps the component array in the first parameter's slot. */
undefined4 FUN_10004390(undefined4 file, undefined4 handle, undefined4 unused3, undefined4 unused4)
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

#define TAGTYPE0(t) (PTR_100143c0[(t) * 0x17])     /* first dword of a tag type record (0x5c bytes) */
    if (FUN_10004bb0(file, COS_LINE, 0x400) == 0)
        return 0;
    if (FUN_10005810(COS_LINE, (char *)IMG_ADDR(0x10010574), &n) != 1)    /* " numcomponents %d" */
        return 0;
    comps = 0;
    if (n != 0) {
        comps = (byte *)COS_SVC_ALLOC(n << 6, 0xbdf);
        if (comps == 0)
            COS_SVC_ASSERT((char *)IMG_ADDR(0x10010558), 0xbe0);
    }
    if (comps == 0)
        return 0;
    if (_DAT_100143d4 < n) {
        _DAT_100143d0 = ((int (*)(int, int, char *, int))*(code **)(DAT_100143a8 + 0x28))(_DAT_100143d0, n * 4,
                                                                                             s_C__grimsrc_libs_chore_Costume_c_1001020c, 0xbeb);
        _DAT_100143d4 = n;
    }
    for (i = 0; i < n; i++) {
        comp = comps + i * 0x40;
        if (FUN_10004bb0(file, COS_LINE, 0x400) == 0)
            return 0;
        if (FUN_10005810(COS_LINE, (char *)IMG_ADDR(0x10010544), &index, &tag, comp + 0x28, comp + 0x2c, comp) != 5)
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
            r = FUN_10004770(costume, TAGTYPE0(*(int *)(comp + 0x20)), *(int *)(comp + 0x28), comp, p);
            if (r >= 0)
                continue;
            if (p >= 0) {
                byte *pc = comps + p * 0x40;
                byte *cc;

                r = FUN_10004170(costume, TAGTYPE0(*(int *)(pc + 0x20)), *(int *)(pc + 0x28), pc);
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
            (*(int **)&DAT_100143d0)[i] = FUN_10004170(costume, TAGTYPE0(*(int *)(comp + 0x20)), *(int *)(comp + 0x28), comp);
            if ((*(int **)&DAT_100143d0)[i] < 0)
                goto fail;
        }
        level++;
    } while (level <= maxdepth);
    (*(code **)(DAT_100143a8 + 0x24))(comps);
    (*(code **)(DAT_100143a8 + 0x24))(depth);
    return 1;
fail:
    (*(code **)(DAT_100143a8 + 0x24))(comps);
    (*(code **)(DAT_100143a8 + 0x24))(depth);
    return 0;
#undef TAGTYPE0
}


/* ==== Cos_LoadEntry (0x10001770) ====
 * Loads the text costume `name` into the costume of `handle`: the costume is reset (FUN_100010d0) and named after the
 * file name without its directory (at most 32 characters, else an error), the file is opened ("r", service +0x30) and
 * read as " costume v%d.%d" (version, not checked), " section tags" (FUN_100041e0), " section components"
 * (FUN_10004390), " section chores" (FUN_100047f0), " section keys" (FUN_10004970, only with chores).  Then each chore
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

    FUN_100010d0(costume);
    base = FUN_100056a0(name, '\\');
    base = base != 0 ? base + 1 : name;
    for (len = 0; base[len] != 0; len++)
        ;
    if (len > 0x20)
        goto fail;
    FUN_100055a0((uint *)costume, (uint *)base, 0x1f);
    *(byte *)(costume + 0x1f) = 0;
    file = (*(code **)(DAT_100143a8 + 0x30))(name, IMG_ADDR(0x10010280));     /* "r" */
    if (file == 0) {
        *(int *)(costume + 0x38) = 1;
        return 0;
    }
    _DAT_100143ec = 0;
    if (FUN_10004bb0(file, COS_LINE, 0x400) == 0)
        goto fail;
    FUN_10005810(COS_LINE, (char *)IMG_ADDR(0x10010270), &version[1], &version[0]);    /* " costume v%d.%d" */
    if (FUN_10004bb0(file, COS_LINE, 0x400) == 0 || FUN_10005810(COS_LINE, (char *)IMG_ADDR(0x10010260)) != 0)
        goto fail;
    if (FUN_100041e0(file, costume, (uint)name) == 0)
        goto fail;
    if (FUN_10004bb0(file, COS_LINE, 0x400) == 0 || FUN_10005810(COS_LINE, (char *)IMG_ADDR(0x1001024c)) != 0)
        goto fail;
    if (FUN_10004390(file, handle, name, 0) == 0)
        goto fail;
    if (FUN_10004bb0(file, COS_LINE, 0x400) == 0 || FUN_10005810(COS_LINE, (char *)IMG_ADDR(0x1001023c)) != 0)
        goto fail;
    if (FUN_100047f0(file, costume, name) == 0)
        goto fail;
    if (FUN_10004bb0(file, COS_LINE, 0x400) == 0 || FUN_10005810(COS_LINE, (char *)IMG_ADDR(0x1001022c)) != 0)
        goto fail;
    if (*(uint *)(costume + 0x30) != 0 && FUN_10004970(file, costume) == 0)
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
    (*(code **)(DAT_100143a8 + 0x34))(file);
    return 1;
fail:
    *(int *)(costume + 0x38) = 1;
    (*(code **)(DAT_100143a8 + 0x34))(file);
    return 0;
}

#endif /* GRIM_CHORE */
