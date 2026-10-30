/* Readable C for game-logic functions of CHORE.DLL (agent P).  The assembled originals were kept because Ghidra printed the
 * address of a parameter slot as the output of a call (the slot is both an argument and a result), absolute data addresses
 * as numbers and left out stack arguments.  tools/build_src.py puts the decompiled text of every function defined here
 * under `#if 0`.  Names, types and offsets are Ghidra's. */
#include "ghidra_types.h"

#ifdef GRIM_CHORE
#include "globals.h"
#include "functions.h"

#define COS_COUNT (*(int *)&DAT_100143b0)        /* number of costume slots */
#define COS_INST_COUNT (*(int *)&DAT_100143c8)   /* number of costume instance records */

/* ==== Cos_NewStateBasedTag (0x10001e80), Cos_NewIntTag (0x10001f80), Cos_NewFloatTag (0x10001fd0) ====
 * Register a costume tag type (id, name, ..., 28 byte description of its handlers): FUN_10001ed0 creates the table entry
 * (it refuses a duplicate id or a name longer than 31 characters) and returns it through its first argument; the entry gets
 * the kind (0 state based, 1 int, 2 float) and the handler description.  The old text passed the address of the fifth
 * parameter for the result. */
static undefined4 cos_new_tag(int kind, undefined4 id, undefined4 name, undefined4 unused, undefined4 *handlers, int extra)
{
    int entry = extra;

    if (FUN_10001ed0(&entry, id, (char *)name, unused, extra) == 0)
        return 0;
    *(undefined4 *)(entry + 4) = kind;
    memcpy((char *)entry + 0x2c, handlers, 7 * sizeof(undefined4));
    return 1;
}

undefined4 Cos_NewStateBasedTag(undefined4 id, undefined4 name, undefined4 unused, undefined4 *handlers, int extra)
{
    return cos_new_tag(0, id, name, unused, handlers, extra);
}

undefined4 Cos_NewIntTag(undefined4 id, undefined4 name, undefined4 unused, undefined4 *handlers, int extra)
{
    return cos_new_tag(1, id, name, unused, handlers, extra);
}

undefined4 Cos_NewFloatTag(undefined4 id, undefined4 name, undefined4 unused, undefined4 *handlers, int extra)
{
    return cos_new_tag(2, id, name, unused, handlers, extra);
}

/* ==== CosUtil_ComponentInfo (0x10002e40) ====
 * Reads the description of component `index` of costume `cos`: tag id (via the tag table), the two component fields at +0x24 /
 * +0x2c and the tag kind.  It leaves the component record in EAX and Cos_InstComponentInfo passes that on to the EXE (the
 * Ghidra prototype said void; with my first version the callers got garbage, which showed in the pictures of some sets).
 * The two assertion texts are data at 0x1001034c / 0x10010444 that Ghidra left without a name
 * (offsets +0x140 / +0x238 from the file name string). */
int CosUtil_ComponentInfo(int cos, uint index, int *outTag, undefined4 *outA, undefined4 *outB, int *outKind)
{
    char *file = s_C__grimsrc_libs_chore_Costume_c_1001020c;
    int *tag;
    int rec;

    if (cos == 0)
        (**(code **)(DAT_100143a8 + 0x18))(file + 0x140, file, 0x797);
    if (*(uint *)(cos + 0x28) <= index)
        (**(code **)(DAT_100143a8 + 0x18))(file + 0x238, file, 0x798);
    rec = *(int *)(cos + 0x2c) + index * 0x40;
    tag = PTR_100143c0 + *(int *)(rec + 0x20) * 0x17;
    if (outTag != (int *)0)
        *outTag = tag[0];
    if (outA != (undefined4 *)0)
        *outA = *(undefined4 *)(rec + 0x24);
    if (outKind != (int *)0)
        *outKind = tag[1];
    if (outB != (undefined4 *)0)
        *outB = *(undefined4 *)(rec + 0x2c);
    return rec;
}

/* ==== Cos_Save (0x100037a0), Cos_Restore (0x10003970) ====
 * Save game hooks of the costume system.  `io` is the save/load stream function (buffer, size).  Save writes the number of
 * costume slots (0x100143b0), the number of the loaded ones that the optional filter hook (0x100143e8) accepts, for each of
 * them its handle and 32 bytes of name, and the number of costume instances.  Restore frees the loaded costumes, grows the
 * slot table, reloads every saved costume by name under its saved handle (Cos_LoadEntry) and resets the instance table
 * (records of 0x14 bytes with the last field 1).  The old text used the parameter slots as buffers. */
undefined4 Cos_Save(code *io)
{
    int count = 0, i, rec;
    int handle;

    ((void (*)(void *, int))io)(&COS_COUNT, 4);
    for (i = 0; i < COS_COUNT; i++) {
        rec = DAT_100143b4 + i * 0x3c;
        if (*(int *)(rec + 0x38) == 0) {
            if (_DAT_100143e8 != (code *)0 && ((int (*)(int))_DAT_100143e8)(rec) == 0)
                continue;
            count++;
        }
    }
    ((void (*)(void *, int))io)(&count, 4);
    for (i = 0; i < COS_COUNT; i++) {
        rec = DAT_100143b4 + i * 0x3c;
        if (*(int *)(rec + 0x38) == 0) {
            if (_DAT_100143e8 != (code *)0 && ((int (*)(int))_DAT_100143e8)(rec) == 0)
                continue;
            handle = FUN_10005180(i);
            ((void (*)(void *, int))io)(&handle, 4);
            ((void (*)(void *, int))io)((void *)rec, 0x20);
        }
    }
    ((void (*)(void *, int))io)(&DAT_100143c8, 4);
    return 0;
}

undefined4 Cos_Restore(code *io)
{
    int i, n, loaded, handle, rec;
    char name[32];

    for (i = 0; i < COS_COUNT; i++) {
        if (*(int *)(DAT_100143b4 + i * 0x3c + 0x38) == 0)
            Cos_Free(FUN_10005180(i));
    }
    ((void (*)(void *, int))io)(&n, 4);
    if (COS_COUNT < n) {
        DAT_100143b4 = ((int (*)(int, int, char *, int))*(code **)(DAT_100143a8 + 0x28))(DAT_100143b4, n * 0x3c,
                                                                                    s_C__grimsrc_libs_chore_Costume_c_1001020c, 0xa2b);
        while (COS_COUNT < n) {
            *(int *)(DAT_100143b4 + COS_COUNT * 0x3c + 0x38) = 1;
            COS_COUNT = COS_COUNT + 1;
        }
        COS_COUNT = n;
    }
    ((void (*)(void *, int))io)(&loaded, 4);
    for (i = 0; i < loaded; i++) {
        ((void (*)(void *, int))io)(&handle, 4);
        ((void (*)(void *, int))io)(name, 0x20);
        Cos_LoadEntry(name, handle);
        rec = FUN_10005160(handle);
        *(int *)(DAT_100143b4 + rec * 0x3c + 0x38) = 0;
        _DAT_100143ac = _DAT_100143ac + 1;
    }
    ((void (*)(void *, int))io)(&n, 4);
    if (COS_INST_COUNT < n) {
        DAT_100143cc = ((int (*)(int, int, char *, int))*(code **)(DAT_100143a8 + 0x28))(DAT_100143cc, n * 0x14,
                                                                                    s_C__grimsrc_libs_chore_Costume_c_1001020c, 0xa42);
        COS_INST_COUNT = n;
    }
    for (i = 0; i < COS_INST_COUNT; i++) {
        undefined4 *r = (undefined4 *)(DAT_100143cc + i * 0x14);

        r[0] = 0;
        r[1] = 0;
        r[2] = 0;
        r[3] = 0;
        r[4] = 1;
    }
    COS_INST_COUNT = n;
    return 0;
}

#endif /* GRIM_CHORE */
