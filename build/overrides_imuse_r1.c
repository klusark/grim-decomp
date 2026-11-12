/* IMUSE.DLL, last assembled functions (agent r1): the script layer's music state / sequence transitions.
 *   FUN_10006560 (state), Script_SetSequence (sequence), Script_Trans (the transition itself), FUN_100064d0 (end-of-sequence check,
 *   compiled from the decompiler's C before; written here because it is the one caller that passes another frame word).
 * Written from the disassembly (git show 85dd22f:src/IMUSE.DLL/asm_funcs.s).  Notes: docs/notes/imuse_r1.md.
 *
 * The "five garbage parameters" of Script_Trans.  Ghidra declared Script_Trans with 8 parameters and showed parameters 4..8
 * (the words above the 3 pushed arguments: the caller's saved EDI / ESI, the caller's return address, the caller's argument,
 * a word of the dispatcher's frame) as the fade time of ImSwitchStream and the hook values of ImSetHook.  That is the
 * decompiler's mistake about MSVC's deferred pops (`mov eax,[esp+0x2c]` right after a call whose 5 pushes are still on the
 * stack is the function's own stack slot 0x18, not 0x2c): the function reads only its 3 arguments, and it reuses the slots
 * of arguments 1 and 2 as locals (slot 1 = the hook value, slot 2 = the fade time).  Measured in the game (Script_Trans's
 * calls logged under gdb, build/difftest/imuse_r1/frametrace.py, scenarios 3 and 9): the original DLL and the rebuilt DLL
 * make the same calls with the same arguments although words 4..8 differ (original: EDI, 0xffffffff, return address,
 * state id, ...; rebuilt with the gcc dispatcher: 1, 0x11, ...).
 *
 * What really reads the stack beyond the pushed arguments is ImSetTrigger: it stores its 13th argument word (p9) in all ten
 * parameter words of the trigger (build/overrides_imuse.c), and Script_Trans pushes only 3..8 of the 13.  The 13th word
 * then lies in Script_Trans's own frame or above it, at a place fixed by the number of pushed words n:
 *     n = 3  [entry+0x14] the caller's saved ESI = the ESI register of the caller's caller (FUN_10006560 / Script_SetSequence
 *            push ESI first): 0xffffffff when called from the dispatcher ScriptCall (`or esi,-1` in its prologue;
 *            FUN_100064d0 does not touch ESI before its first call either), 0 at FUN_100064d0's second call
 *     n = 5  [entry+0x0c] argument 3                   n = 6  [entry+0x08] slot 2 = the fade time
 *     n = 7  [entry+0x04] slot 1 = the hook value      n = 8  [entry]      Script_Trans's return address (in the original
 *            image, which loads at its preferred base 0x10000000: 0x100065f3, 0x100066eb, 0x1000672c or 0x10006778)
 * The C passes those values explicitly (parameters caller_esi and ret_word of Script_Trans), so the triggers store what the
 * original stored, independent of the compiler's frames.  The words between the pushed arguments and p9 are not read by
 * ImSetTrigger; the C passes 0 for them.
 * These triggers belong to transition types 4, 6, 9, 10, 11 and 12.  The shipped tables have only types 0, 2 and 3 (state
 * table: 93 x 2, 85 x 3, 3 x 0; sequence table: 40 x 2, 1 x 0), so in the game they never run (dormant code kept exact).
 *
 * Compiled by build/link.py for every program; everything is guarded with GRIM_IMUSE. */
#include "ghidra_types.h"

#ifdef GRIM_IMUSE
#include "globals.h"
#define Script_Trans Script_Trans__ghidra
#include "functions.h"
#undef Script_Trans

/* data of the original image (0x10017000.. = .data) */
#define IMB(a)   ((char *)IMG_ADDR(a))
#define IMW(a)   (*(int *)IMG_ADDR(a))
#define STATE_TAB    0x100172e8   /* 181 entries of 0x54 bytes: +0 sound file name, +0x20 transition type, +0x24 id,      */
#define SEQ_TAB      0x1001ae50   /*  +0x28 name, +0x40 counter slot, +0x44 counter limit, +0x48 fade, +0x4c volume, +0x50 pan */
#define ENT_SIZE     0x54
#define CUR_STATE    0x1002df70   /* index of the current state */
#define CUR_SEQ      0x1002e308   /* index of the current sequence */
#define PENDING_SEQ  0x1002e30c   /* sequence to start when the current one (type 4 / 6) ends */
#define SEQ_PLAYED   0x1002e25c   /* int[41] */
#define SEQ_ENDED    0x1002e304   /* set by the trigger callback Script_Callback */
#define COUNTERS     0x1002df84   /* int[]: hook counters */
#define SND_NAME     0x1002e310   /* char[]: the sound file name being opened */
#define NAME_ALIAS   0x1001bbc8   /* records of 0x40 bytes {char from[0x20]; char to[0x20]}, up to an empty `from` */
#define STR_NL       0x100171b0   /* "\n" */

void Script_Trans(char *entry, int index, int no_attr, uint caller_esi, uint ret_word);

/* ==== Script_Trans (0x100068b0): the transition to a state / sequence table entry ====
 * entry = the table entry (NULL: no music), index = state index (0 for a sequence: no hook counter), no_attr = 1 from the
 * sequence layer (0: a state change may switch to an attribute-matching stream in place).  caller_esi / ret_word: the two
 * stack words of the original that ImSetTrigger reads (header comment).
 * Steps: copy the entry's sound file name (renamed through the alias table), compute the hook value (counter of slot
 * field40 or index, cycled up to field44; 100 if 0), fade out every group-4 sound that is not a stream, find the playing
 * music stream (param 0x1800 set and 0x1900 == 2), then act by the transition type field20 (jump table of 13 entries,
 * unsigned compare: > 12 = "bogus trans type").  Step of the volume / pan fades = fade * 3 / 50 (32-bit wrap of fade * 3,
 * signed division: the imul 0x51eb851f / sar 4 / +sign sequence). */
/* OVERRIDES: Script_Trans */
void Script_Trans(char *entry, int index, int no_attr, uint caller_esi, uint ret_word)
{
    char *name = IMB(SND_NAME);
    char *rec, *src;
    int hook, fade, step, slot, n, type;
    int old, snd;
    uint s;

    if (IMW(0x1001e688) == 0)                 /* script layer not initialised */
        return;
    if (entry != 0) {
        n = 0;
        do { name[n] = entry[n]; } while (entry[n++] != 0);
        for (rec = IMB(NAME_ALIAS); rec[0] != 0; rec += 0x40) {
            for (n = 0; rec[n] != 0 && name[n] == rec[n]; n++)
                ;
            if (n != 0 && name[n] == 0 && rec[n] == 0) {
                src = rec + 0x20;
                n = 0;
                do { name[n] = src[n]; } while (src[n++] != 0);
                break;
            }
        }
    }
    hook = 0;
    if (entry != 0 && index != 0) {
        slot = *(int *)(entry + 0x40) != 0 ? *(int *)(entry + 0x40) : index;
        hook = ((int *)IMB(COUNTERS))[slot];
        if (*(int *)(entry + 0x44) != 0) {
            if (hook == 0 && *(int *)(entry + 0x44) > 1)
                ((int *)IMB(COUNTERS))[slot] = 2;
            else {
                ((int *)IMB(COUNTERS))[slot] = (int)((uint)hook + 1);
                if ((int)((uint)hook + 1) > *(int *)(entry + 0x44))
                    ((int *)IMB(COUNTERS))[slot] = 1;
            }
        }
    }
    if (hook == 0)
        hook = 100;
    for (s = ImGetNextSound(0); s != 0; s = ImGetNextSound(s))
        if (ImGetParam(s, 0x400) == 4 && ImGetParam(s, 0x1800) == 0)
            ImFadeParam(s, 0x600, 0, 0x78);
    old = 0;
    for (s = ImGetNextSound(0); s != 0; s = ImGetNextSound(s))
        if (ImGetParam(s, 0x1800) != 0 && ImGetParam(s, 0x1900) == 2) {
            old = s;
            break;
        }
    if (entry == 0) {
        if (old != 0)
            ImFadeParam(old, 0x600, 0, 0x78);
        return;
    }
    fade = *(int *)(entry + 0x48) != 0 ? *(int *)(entry + 0x48) : 1000;
    step = (int)((uint)fade * 3u) / 50;
    switch ((uint)*(int *)(entry + 0x20)) {
    case 0:
        ImPrintf(s_Trans_null____1001e860);
        return;
    case 5:
        return;
    case 6:
        IMW(SEQ_ENDED) = 0;
        ImSetTrigger(0xbc6150, IMB(0x1001e858), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, caller_esi);
        return;
    case 7:
        if (old != 0)
            ImFadeParam(old, 0x600, 0, 0x3c);
        return;
    case 8:
        if (old != 0)
            ImSetHook(old, 100);
        return;
    case 9:
        if (old != 0)
            ImSetHook(old, 99);
        IMW(SEQ_ENDED) = 0;
        ImSetTrigger(old, IMB(0x1001e858), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, caller_esi);
        return;
    case 2: case 3: case 4: case 10: case 11: case 12:
        break;
    default:                                  /* 1 and > 12 */
        ImPrintf(s_SCRIPT_ERR__bogus_trans_type____1001e768);
        return;
    }

    ImPrintf(s_opening_1001e84c);
    ImPrintf(name);
    ImPrintf(IMB(STR_NL));
    snd = ImOpenSound(name, 0);
    if (snd == 0) {
        ImPrintf(s_SCRIPT_ERR__Unable_to_open_1001e830);
        ImPrintf(name);
        ImPrintf(IMB(STR_NL));
        if (old != 0)
            ImFadeParam(old, 0x600, 0, 0x3c);
        return;
    }
    type = *(int *)(entry + 0x20);
    if (type == 4) {
        IMW(SEQ_ENDED) = 0;
        ImSetTrigger(snd, IMB(0x1001e858), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, caller_esi);
    }
    ImPrintf(s_HOOK__lu____1001e824, hook);
    if (old == 0) {                           /* no music playing: start this one */
        ImPrintf(s_No_stream_sound____1001e7ac);
        if (ImStartStream(snd, 0x7e, 2) != 0)
            ImPrintf(s_SCRIPT_ERR__failed_start_stream__1001e788);
        ImSetParam(snd, 0x600, 0);
        ImFadeParam(snd, 0x600, *(uint *)(entry + 0x4c), step);
        ImSetParam(snd, 0x700, *(uint *)(entry + 0x50));
        ImSetParam(snd, 0x400, 4);
        ImSetHook(snd, hook);
    } else if (*(int *)(entry + 0x20) == 2) {
        ImSwitchStream(old, snd, fade, 0, 0);
        ImPrintf(s_FADE__lu____1001e818, fade);
        ImPrintf(s_vol__lu____1001e80c, *(int *)(entry + 0x4c));
        ImFadeParam(snd, 0x600, *(uint *)(entry + 0x4c), step);
        ImFadeParam(snd, 0x700, *(uint *)(entry + 0x50), step);
        ImSetParam(snd, 0x400, 4);
        ImSetHook(snd, hook);
        ImProcessStreams();
    } else if (old == snd) {                  /* the same music: only fade volume (and pan) */
        ImFadeParam(snd, 0x600, *(uint *)(entry + 0x4c), step);
        ImPrintf(s_fading_VOL__lu____1001e7d0, *(int *)(entry + 0x4c));
        if (*(int *)(entry + 0x50) != 0) {
            ImFadeParam(snd, 0x700, *(uint *)(entry + 0x50), step);
            ImPrintf(s_and_PAN__lu____1001e7c0, *(int *)(entry + 0x50));
        }
    } else if (no_attr == 0 && *(int *)(entry + 0x40) != 0
               && *(int *)(entry + 0x40) == *(int *)(IMB(STATE_TAB + 0x40) + IMW(CUR_STATE) * ENT_SIZE)) {
        ImSwitchStream(old, snd, fade, 0, 1);
        ImFadeParam(snd, 0x600, *(uint *)(entry + 0x4c), step);
        ImFadeParam(snd, 0x700, *(uint *)(entry + 0x50), step);
        ImSetParam(snd, 0x400, 4);
        if (hook == 100)
            ImSetHook(snd, 100);
        ImProcessStreams();
    } else if ((type = *(int *)(entry + 0x20)) == 10 || type == 11 || type == 12) {
        /* switch at the marker "exit" ("exit2" for 11; 12 first clears the old stream's hook): the commands run when the
         * old stream passes the marker.  Last argument = the 13th stack word (header comment). */
        char *mk = type == 11 ? s_exit2_1001e7fc : IMB(0x1001e804);
        if (type == 12) {
            ImSetHook(old, 99);
            ImSetTrigger(old, s_clear_1001e7f4, 0xf, old, 0x80, 0, 0, 0, 0, 0, 0, 0, no_attr);
        }
        ImSetTrigger(old, mk, 0x1a, old, snd, fade, 1, 0, 0, 0, 0, 0, ret_word);
        ImSetTrigger(old, mk, 0xe, snd, 0x600, *(int *)(entry + 0x4c), step, 0, 0, 0, 0, 0, hook);
        ImSetTrigger(old, mk, 0xe, snd, 0x700, *(int *)(entry + 0x50), step, 0, 0, 0, 0, 0, hook);
        ImSetTrigger(old, mk, 0xc, snd, 0x400, 4, 0, 0, 0, 0, 0, 0, fade);
        if (type == 12)
            ImPrintf(s_HOOK__lu____1001e824, hook);
        ImSetTrigger(old, mk, 0xf, snd, hook, 0, 0, 0, 0, 0, 0, 0, no_attr);
        ImProcessStreams();
    } else {                                  /* types 3 and 4: switch now */
        ImSwitchStream(old, snd, fade, 0, 0);
        ImPrintf(s_FADE__lu____1001e818, fade);
        ImPrintf(s_vol__lu____1001e80c, *(int *)(entry + 0x4c));
        ImFadeParam(snd, 0x600, *(uint *)(entry + 0x4c), step);
        ImFadeParam(snd, 0x700, *(uint *)(entry + 0x50), step);
        ImPrintf(s_set_pan__lu____1001e7e4, *(int *)(entry + 0x50));
        ImSetParam(snd, 0x400, 4);
        ImSetHook(snd, hook);
        ImProcessStreams();
    }
    ImCloseSound(snd);
    ImSetParam(snd, 0x400, 4);
}

/* ==== FUN_10006560 (0x10006560): ImSetState through the dispatcher (command 5) ====
 * id = state id (-1: return the current state's id).  Unknown id: 0.  Prints the state's name; a different state starts the
 * transition unless a sequence is playing (then only the current state changes).  Returns the id of the current state.
 * Called only by the dispatcher ScriptCall, whose ESI is 0xffffffff: the word ImSetTrigger reads for n = 3. */
/* OVERRIDES: FUN_10006560 */
undefined4 FUN_10006560(int id)
{
    int i;

    if (id == -1)
        return IMW(STATE_TAB + 0x24 + IMW(CUR_STATE) * ENT_SIZE);
    for (i = 0; id != IMW(STATE_TAB + 0x24 + i * ENT_SIZE); )
        if (++i >= 181)
            return 0;
    ImPrintf(IMB(STATE_TAB + 0x28 + i * ENT_SIZE));
    ImPrintf(IMB(STR_NL));
    if (i != IMW(CUR_STATE)) {
        if (IMW(CUR_SEQ) == 0)
            Script_Trans(i != 0 ? IMB(STATE_TAB + i * ENT_SIZE) : 0, i, 0, 0xffffffffu, 0x100065f3u);
        IMW(CUR_STATE) = i;
    }
    return IMW(STATE_TAB + 0x24 + IMW(CUR_STATE) * ENT_SIZE);
}

/* ==== Script_SetSequence (0x10006620): ImSetSequence (command 5 of the dispatcher, and FUN_100064d0) ====
 * id = sequence id (-1: return the current one's id; 0 = 2000 = no sequence).  Unknown id: prints an error, returns -1.
 * Starting a sequence while the current one is of type 4 or 6 only queues it (PENDING_SEQ).  Sequence 0 ends the sequence:
 * the queued one starts, or the music of the current state comes back.  Returns the id of the current sequence.
 * Im_SetSequence takes the caller's ESI register value (the word ImSetTrigger reads for n = 3; header comment). */
static undefined4 Im_SetSequence(int id, uint caller_esi)
{
    int i, cur;

    if (id == -1)
        return IMW(SEQ_TAB + 0x24 + IMW(CUR_SEQ) * ENT_SIZE);
    if (id == 0)
        id = 2000;
    for (i = 0; id != IMW(SEQ_TAB + 0x24 + i * ENT_SIZE); )
        if (++i >= 41) {
            ImPrintf(s_ERR__bogus_sequence____1001e720);
            return 0xffffffff;
        }
    ImPrintf(IMB(SEQ_TAB + 0x28 + i * ENT_SIZE));
    ImPrintf(IMB(STR_NL));
    cur = IMW(CUR_SEQ);
    if (i == cur)
        return IMW(SEQ_TAB + 0x24 + cur * ENT_SIZE);
    if (i != 0) {
        if (cur != 0) {
            int t = IMW(SEQ_TAB + 0x20 + cur * ENT_SIZE);
            if (t == 4 || t == 6) {
                IMW(PENDING_SEQ) = i;
                return IMW(SEQ_TAB + 0x24 + cur * ENT_SIZE);
            }
        }
        Script_Trans(IMB(SEQ_TAB + i * ENT_SIZE), 0, 1, caller_esi, 0x100066ebu);
        IMW(PENDING_SEQ) = 0;
        ((int *)IMB(SEQ_PLAYED))[i] = 1;
        cur = i;
    } else if (IMW(PENDING_SEQ) != 0) {
        Script_Trans(IMB(SEQ_TAB + IMW(PENDING_SEQ) * ENT_SIZE), 0, 1, caller_esi, 0x1000672cu);
        cur = IMW(PENDING_SEQ);
        IMW(CUR_SEQ) = cur;
        IMW(PENDING_SEQ) = 0;
        ((int *)IMB(SEQ_PLAYED))[cur] = 1;
        return IMW(SEQ_TAB + 0x24 + cur * ENT_SIZE);
    } else {
        int st = IMW(CUR_STATE);
        Script_Trans(st != 0 ? IMB(STATE_TAB + st * ENT_SIZE) : 0, st, 1, caller_esi, 0x10006778u);
        cur = 0;
    }
    IMW(CUR_SEQ) = cur;
    return IMW(SEQ_TAB + 0x24 + cur * ENT_SIZE);
}

/* OVERRIDES: Script_SetSequence */
int Script_SetSequence(int id)   /* (the record's nId: int since types round 5) */
{
    return Im_SetSequence(id, 0xffffffffu);   /* the dispatcher's ESI */
}

/* ==== FUN_100064d0 (0x100064d0): dispatcher command 4, run once per frame by the game ====
 * If the trigger callback flagged the end of a sequence: end it (Script_SetSequence(0)).  Then if no music stream is playing
 * (param 0x1800 set and 0x1900 == 2) while a sequence is current, end the sequence too.  ImFlushSounds, return 0.
 * Its ESI is the dispatcher's (0xffffffff) at the first call and the loop variable (0: no stream found) at the second. */
/* OVERRIDES: FUN_100064d0 */
undefined4 FUN_100064d0(void)
{
    uint s;

    if (IMW(SEQ_ENDED) != 0) {
        Im_SetSequence(0, 0xffffffffu);
        IMW(SEQ_ENDED) = 0;
    }
    for (s = ImGetNextSound(0); s != 0; s = ImGetNextSound(s))
        if (ImGetParam(s, 0x1800) != 0 && ImGetParam(s, 0x1900) == 2)
            break;
    if (s == 0 && IMW(CUR_SEQ) != 0)
        Im_SetSequence(0, 0);
    ImFlushSounds();
    return 0;
}

#endif /* GRIM_IMUSE */
