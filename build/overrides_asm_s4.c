/* Readable C for a few assembled functions of GRIMFANDANGO.EXE from slice 4 (0x0043c8d0 - 0x0045b1c0).
 *
 * Only the functions that could be checked against the original machine code are here (see docs/notes/asm_s4.md for
 * the list of converted and left-assembled functions).  Each one was read against its disassembly in
 * src/GRIMFANDANGO.EXE/asm_funcs.s: the x87 compares keep the NaN behaviour of FCOM + `TEST AH,...`, and the values the
 * original keeps in extended precision are kept in long double until they are stored to a float slot.
 * tools/build_src.py puts the decompiled text of every function defined here under `#if 0`.
 * Names, types and offsets are Ghidra's, except where a comment says otherwise.
 *
 * The track records of a puppet (rdPuppet_*) are 0x134 bytes each, six per puppet, starting at puppet+8:
 *   +0x00 flags (uint), +0x10 float rate, +0x18 float time, +0x1c float (1/fade seconds, or the fade step per second) */
#include "ghidra_types.h"

#ifdef GRIM_EXE
#include "globals.h"
#include "functions.h"

/* ==== rdPuppet_UpdateTracks (0x00450a90) ====
 * Advances the six tracks of a puppet by `seconds` (scaled by each track's rate at +0x10).  Only when the puppet's first
 * dword is 0.  A track with a non-zero flag word and no 0x200 bit is advanced by rdPuppet_AdvanceTrack (unless 0x10 is
 * set).  A fading-in track (0x4) moves its level at +0x18 up to 1.0 and then clears 0x4; a fading-out track (0x8) moves it
 * down to 0, then stops it, or sets 0x10 when 0x100 is set.  The x87 temporaries stay in long double until the store, and
 * the compares are on the extended values (as FCOM is), so NaN takes the same branch as in the original.
 * The original returns in EAX the number of tracks with a non-zero flag word (0 when the puppet's first dword is set);
 * the decompiled prototype is void and no caller reads that value, so it is not returned here. */
void __cdecl rdPuppet_UpdateTracks(void *puppet, float seconds)
{
    uint *rec;
    int track;

    if (*(int *)puppet != 0)
        return;
    rec = (uint *)((char *)puppet + 8);
    for (track = 0; track < 6; track++, rec += 0x4d) {          /* 0x4d dwords = 0x134 bytes per track */
        float *frec = (float *)rec;
        uint flags = *rec;
        long double t;

        if (flags == 0 || (flags & 0x200) != 0)
            continue;
        if ((flags & 0x10) == 0)
            rdPuppet_AdvanceTrack(puppet, track, (float)((long double)frec[4] * (long double)seconds));

        flags = *rec;
        if ((flags & 4) != 0) {
            /* fading in: level += rate * seconds, clamp to 1.0 once reached */
            t = (long double)frec[7] * (long double)seconds + (long double)frec[6];
            frec[6] = (float)t;
            if (t >= 1.0L) {
                frec[6] = 1.0f;
                *rec = (*rec & 0xfffffffb);
            }
        } else if ((flags & 8) != 0) {
            /* fading out: level -= rate * seconds, stop (or hold, with 0x100) at 0 */
            t = (long double)frec[6] - (long double)frec[7] * (long double)seconds;
            frec[6] = (float)t;
            if (!(t > 0.0L)) {
                if ((*rec & 0x100) == 0)
                    rdPuppet_RemoveTrack(puppet, track);
                else
                    *rec = (*rec & 0xfffffff7) | 0x10;
            }
        }
    }
}
#endif
