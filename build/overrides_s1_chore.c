/* CHORE.DLL slot allocators, round s (agent s1, docs/notes/s1.md): the fix of the intermittent clean-room crash in
 * save_load (Res_RemoveReference <- ModelComponent_Destroy <- Cos_FreeComponent <- Cos_FreeCostume <- Cos_Free <- Cos_Restore).
 *
 * Both functions hand out a free record of a table that grows by 8 records: the costume slots (0x3c bytes, +0x38 = 1 when
 * free; size 0x100143b0, table 0x100143b4, records in use 0x100143ac) and the costume instance records (0x14 bytes, +0x10
 * = 1 when free; size 0x100143c8, table 0x100143cc, in use 0x100143c4).  The original (checked against its machine code)
 * marks only the records from the in-use COUNT up to the new size as free after the realloc, and returns the record at
 * the in-use count.  The count is not the number of records in use: Cos_Load does not lower it when a costume fails to
 * load (Cos_FreeCostume frees the slot but leaves the count), so after a failed load the count is above the old size when the
 * table grows, and the records between the old size and the count keep whatever the reallocated block held.  In the
 * clean-room suite one costume fails before the table grows from 32 to 40 slots (used 33), so slot 32 (handle 0x21) is
 * such a record: when the heap gives the realloc a block that held zeros it reads as an empty costume in use (harmless),
 * when it gives a reused block it reads as a costume in use with a stale component array, and the next Cos_Restore
 * (Engine_LoadGame) frees those components: Res_RemoveReference(NULL) on a zeroed record whose type index 0 is MMDL.  Which
 * block the heap returns depends on the other threads' allocations (iMUSE, sound), hence 0 to 50 % of the runs.
 *
 * The C below is the original with the new records marked free from the OLD size on (the ones below the count were
 * undefined; the original's runs only worked when their bytes happened to be non-zero at +0x38 / +0x10, i.e. free), and
 * with the table grown until the returned record is inside it (the original grows by 8 once and would write past the
 * end after more than 8 failed loads).  The record returned, and so every handle, is the original's. */
#include "ghidra_types.h"

#ifdef GRIM_CHORE
#include "globals.h"
#include "functions.h"

#define S1_COS_SIZE (*(int *)&g_nMaxCostumes)        /* costume slots allocated */
#define S1_COS_USED (*(int *)&g_nCostumes)        /* costume slots counted in use */
#define S1_INST_SIZE (*(int *)&g_nMaxInstances)       /* instance records allocated */
#define S1_INST_USED (*(int *)&g_nInstances)       /* instance records counted in use */

/* ==== Cos_AllocCostumeSlot (0x10004e50): a free costume slot ==== */
/* OVERRIDES: Cos_AllocCostumeSlot */
int Cos_AllocCostumeSlot(void)
{
    int i, old;

    for (i = 0; i < S1_COS_SIZE; i++) {
        if (*(int *)((int)g_aCostumes + i * 0x3c + 0x38) != 0) {
            *(int *)((int)g_aCostumes + i * 0x3c + 0x38) = 0;
            S1_COS_USED = S1_COS_USED + 1;
            return i;
        }
    }
    if (S1_COS_SIZE < S1_COS_USED + 1) {
        old = S1_COS_SIZE;
        do
            S1_COS_SIZE = S1_COS_SIZE + 8;
        while (S1_COS_SIZE < S1_COS_USED + 1);
        *(int *)&g_aCostumes = ((int (*)(int, int, char *, int))g_pSvcChore->pRealloc)((int)g_aCostumes, S1_COS_SIZE * 0x3c,
                                                                                         s_C__grimsrc_libs_chore_Costume_c_1001020c, 0xed0);
        for (i = old; i < S1_COS_SIZE; i++)
            *(int *)((int)g_aCostumes + i * 0x3c + 0x38) = 1;
    }
    i = S1_COS_USED;
    S1_COS_USED = S1_COS_USED + 1;
    *(int *)((int)g_aCostumes + i * 0x3c + 0x38) = 0;
    return i;
}

/* ==== Cos_AllocInstanceSlot (0x10005090): a free costume instance record (the same allocator) ==== */
/* OVERRIDES: Cos_AllocInstanceSlot */
int Cos_AllocInstanceSlot(void)
{
    int i, old;

    for (i = 0; i < S1_INST_SIZE; i++) {
        if (*(int *)((int)g_aCostumeInstances + i * 0x14 + 0x10) != 0) {
            *(int *)((int)g_aCostumeInstances + i * 0x14 + 0x10) = 0;
            S1_INST_USED = S1_INST_USED + 1;
            return i;
        }
    }
    if (S1_INST_SIZE < S1_INST_USED + 1) {
        old = S1_INST_SIZE;
        do
            S1_INST_SIZE = S1_INST_SIZE + 8;
        while (S1_INST_SIZE < S1_INST_USED + 1);
        *(int *)&g_aCostumeInstances = ((int (*)(int, int, char *, int))g_pSvcChore->pRealloc)((int)g_aCostumeInstances, S1_INST_SIZE * 0x14,
                                                                                         s_C__grimsrc_libs_chore_Costume_c_1001020c, 0xf3a);
        for (i = old; i < S1_INST_SIZE; i++)
            *(int *)((int)g_aCostumeInstances + i * 0x14 + 0x10) = 1;
    }
    i = S1_INST_USED;
    S1_INST_USED = S1_INST_USED + 1;
    *(int *)((int)g_aCostumeInstances + i * 0x14 + 0x10) = 0;
    return i;
}

#endif /* GRIM_CHORE */
