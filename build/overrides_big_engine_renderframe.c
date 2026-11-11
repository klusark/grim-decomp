/* sputRender_Update (GRIMFANDANGO.EXE 1.01, 0x00484260) written by hand from the original machine code.
 * Notes, verification and the cause of the crash of the earlier (decompiled) C version: docs/notes/big_engine_renderframe.md.
 * Differential test: build/difftest/big_engine_renderframe/.
 * tools/build_src.py puts the decompiled text of this function under `#if 0`. */
#include "ghidra_types.h"

#ifdef GRIM_EXE
#include "globals.h"
#include "functions.h"

#define ER_U32(p, off) (*(uint *)((byte *)(p) + (off)))
#define ER_PTR(p, off) (*(byte **)((byte *)(p) + (off)))

/* "Bad Colormap Reference" assertion of sputResource.h, line 0x9f (through the main service table, cdecl) */
static void er_colormap_assert(void)
{
    ((void (__cdecl *)(char *, char *, int))g_pStd_HS->pAssertFail)(s_Bad_Colormap_Reference_004e8090,
                                                                       s_main_sputResource_h_004e80a8, 0x9f);
}

/* Draws one frame.
 *   mode (g_dwGrimlib_mode) 0: nothing.
 *   3: movie playback: polls the movie; when it has ended, mode 2, every buffer gets a full-screen dirty rectangle and a
 *      full redraw is requested; then talking actors are updated, the text objects drawn and the frame presented.
 *   4: if a full redraw is pending the user paint callback runs.  The pending flag is cleared.
 *   other: the set scene.  If the current set or its setup changed (or a full redraw is pending) the dirty rectangles are
 *      cleared and the new setup switched to (post-cam-change Lua handler).  Then the setup's camera is applied, object
 *      states drawn (layer 3 into the background / z-buffer surfaces), dirty rectangles flushed, the movie polled,
 *      primitives (layer 1), object states (layer 1), the actors (costumes touched, debug overlays, then each actor of
 *      the draw list from last to first: scaled frame, colormap, costume draw, or the screen box only for type 1,
 *      frame scaled back), object states (layer 2), primitives (layer 2), debug lights / cameras, the iris and the
 *      text objects.  The pending flag is cleared.
 * Returns nothing (EAX is not used by the callers). */
void sputRender_Update(void)
{
    uint mode = g_dwGrimlib_mode;
    int rect[4];
    uint vec[3];                /* scale vector passed to rdMatrix_PreScale34 (float bit patterns) */
    byte *set, *rec, *os, *actor, *entry, *cm;
    uint *list = &g_dwDrawItems;
    int setup, n, k, cnt;
    void *cur;

    if (mode == 0)
        return;

    if (mode == 3) {
        float dt;
        sputSmush_SetTarget(&g_dwStdDisplay_backBuffer);
        if (sputSmush_Periodic() != 0) {
            cnt = g_nNumPages;
            g_dwGrimlib_mode = 2;
            rect[0] = 0; rect[1] = 0; rect[2] = 0x280; rect[3] = 0x1e0;
            if (cnt > 0) {
                n = 0;
                do {
                    DirtyRect_Add(rect, 1, n);
                    n++;
                } while (n < g_nNumPages);
            }
            sputRender_ForceRefresh();
            g_dwMovieJustFinished = 1;
        }
        dt = sputTime_GetFrameTimeFlex();
        sputActor_UpdateSpeechOnly(dt);
        stdDisplay_VBufferLock(&g_dwStdDisplay_backBuffer);
        UINT_008a94b8 = UINT_0090563c;
        sputText_Update(0);
        stdDisplay_VBufferUnlock(&g_dwStdDisplay_backBuffer);
        sputRender_PageFlip();
        return;
    }

    if (mode == 4) {
        if (g_nSputRender_Reset != 0) {
            grimlib_UserPaint();
            g_nSputRender_Reset = 0;
            return;
        }
        g_nSputRender_Reset = 0;
        return;
    }

    if (UINT_008c9804 != 0)
        lua_printstack(0);
    if (sputRoom_GetCurrentRoom() == 0)
        return;

    /* the original calls sputRoom_GetCurrentRoom before reading each global it is compared with */
    {
        int changed = 0;
        cur = sputRoom_GetCurrentRoom();
        if (g_pRenderedSet != cur)
            changed = 1;
        else {
            cur = sputRoom_GetCurrentRoom();
            if (*(int *)((byte *)cur + 0xb4) != g_nSputRender_Update_RenderSetup || g_nSputRender_Reset != 0)
                changed = 1;
        }
        if (changed) {
            DirtyRect_Clear();
            set = (byte *)sputRoom_GetCurrentRoom();
            g_pRenderedSet = set;
            setup = *(int *)(set + 0xb4);
            g_nSputRender_Update_RenderSetup = setup;
            sputRender_UseSetup(set, setup);
            sputLua_PostCameraChange(g_nSputRender_Update_RenderSetup);
        }
    }

    /* the setup record (300 bytes per setup).  The original keeps this pointer in EBX and spills it to [ESP+0x10], the slot
     * that also holds the frame time (mode 3) and the iris value: it is an address, never a float. */
    setup = g_nSputRender_Update_RenderSetup;
    set = (byte *)g_pRenderedSet;
    rec = (byte *)(ER_U32(set, 0xac) + (uint)setup * 300u);
    sputRender_SyncCamera(set, setup);

    for (os = ER_PTR(rec, 0x128); os != 0; os = ER_PTR(os, 0xf8))
        ObjectState_Update(os, 3, g_pSputRender_CleanBuffer, g_pSputRender_CleanZBuffer);

    PerfBegin(4);
    if (g_nDoTheFlip != 0)
        DirtyRect_Flush(&g_dwStdDisplay_backBuffer, (void *)UINT_008c97a4);
    PerfEnd(4);
    sputSmush_SetTarget(&g_dwStdDisplay_backBuffer);
    sputSmush_Periodic();
    stdDisplay_VBufferLock(&g_dwStdDisplay_backBuffer);
    sputPrimitive_Update(1);
    stdDisplay_VBufferUnlock(&g_dwStdDisplay_backBuffer);
    for (os = ER_PTR(rec, 0x128); os != 0; os = ER_PTR(os, 0xf8))
        ObjectState_Update(os, 1, &g_dwStdDisplay_backBuffer, (void *)UINT_008c97a4);
    rdAdvanceFrame();
    Render_BuildActorDrawList();

    if (g_dwTotDrawItems != 0 || ((byte)g_dwDebugFlags & 1) != 0) {
        PerfBegin(5);
        n = 0;
        if ((int)g_dwTotDrawItems > 0) {
            do {
                entry = (byte *)list[n];
                actor = (byte *)g_pActors + *(int *)(entry + 8) * 0xa8;
                if (entry[0] == 0)
                    sputCostume_Draw2D(*(int *)ER_PTR(actor, 0xa0));
                n++;
            } while (n < (int)g_dwTotDrawItems);
        }
        PerfEnd(5);
        if (((byte)g_dwDebugFlags & 1) != 0) {
            stdDisplay_VBufferLock(&g_dwStdDisplay_backBuffer);
            if (((byte)g_dwDebugFlags & 8) != 0)
                ((void (__cdecl *)(void *))Sector_DrawAllDebug)(sputRoom_GetCurrentRoom());
            else
                Render_DrawDebugGrid();
            stdDisplay_VBufferUnlock(&g_dwStdDisplay_backBuffer);
        }

        PerfBegin(6);
        /* the draw list from the last entry to the first */
        for (k = n; k != 0; k--) {
            entry = (byte *)list[k - 1];
            actor = (byte *)g_pActors + *(int *)(entry + 8) * 0xa8;
            if (ER_U32(actor, 0x30) != 0x3f800000) {          /* integer compare of the float scale with 1.0f */
                vec[0] = ER_U32(actor, 0x30);
                vec[1] = ER_U32(actor, 0x30);
                vec[2] = ER_U32(actor, 0x30);
                rdMatrix_PreScale34(sputActor_GetOrientMatrix(actor), (undefined4)vec);
            }
            switch (*(byte *)list[k - 1]) {
            case 0:
                cm = ER_PTR(actor, 0);
                if (*(int *)cm != 0) {
                    /* the original repeats the test it has just made (dead assertion) */
                    rdroid_SetColormap(*(uint *)(cm + 4));
                    cm = ER_PTR(actor, 0);
                    if (*(int *)cm == 0)
                        er_colormap_assert();
                } else {
                    /* the set's default colormap: set->0x80 is an array of 0x34 byte records, set->0x88 the index */
                    set = (byte *)g_pRenderedSet;
                    cm = ER_PTR(set, 0x80) + *(int *)(set + 0x88) * 0x34;
                    if (*(int *)cm == 0)
                        er_colormap_assert();
                    rdroid_SetColormap(*(uint *)(cm + 4));
                    set = (byte *)g_pRenderedSet;
                    cm = ER_PTR(set, 0x80) + *(int *)(set + 0x88) * 0x34;
                    if (*(int *)cm == 0)
                        er_colormap_assert();
                }
                ((void (__cdecl *)(uint, int))g_dwSputRender_pSetPaletteFunc)(*(uint *)(cm + 4) + 0x30, 0);
                {
                    float *frame = sputActor_GetOrientMatrix(actor);
                    sputCostume_Draw3D(ER_U32(actor, 0xa0), (undefined4)frame);
                }
                if (((byte)g_dwDebugFlags & 1) != 0)
                    Actor_DrawDebugWalker(actor);
                break;
            case 1:
                if (g_nSputRender_b3DAcceleration == 0)
                    stdDisplay_VBufferLock(&g_dwStdDisplay_backBuffer);
                Actor_ComputeScreenBox(actor);
                if (g_nSputRender_b3DAcceleration == 0)
                    stdDisplay_VBufferUnlock(&g_dwStdDisplay_backBuffer);
                sputRender_MarkDirtyRect((int *)(actor + 0x6c), 1);
                break;
            }
            if (ER_U32(actor, 0x30) != 0x3f800000) {
                /* fld 1.0; fdiv [scale]; fst x3: the quotient rounded once to float */
                long double q = 1.0L / (long double)*(float *)(actor + 0x30);
                float r = (float)q;
                vec[0] = *(uint *)&r;
                vec[1] = vec[0];
                vec[2] = vec[0];
                rdMatrix_PreScale34(sputActor_GetOrientMatrix(actor), (undefined4)vec);
            }
        }
        PerfEnd(6);
        PerfBegin(7);
        rdFinishFrame();
        PerfEnd(7);
        for (os = ER_PTR(rec, 0x128); os != 0; os = ER_PTR(os, 0xf8))
            ObjectState_Update(os, 2, &g_dwStdDisplay_backBuffer, (void *)UINT_008c97a4);
    }

    stdDisplay_VBufferLock(&g_dwStdDisplay_backBuffer);
    sputPrimitive_Update(2);
    stdDisplay_VBufferUnlock(&g_dwStdDisplay_backBuffer);
    if (((byte)g_dwDebugFlags & 1) != 0) {
        cur = sputRoom_GetCurrentRoom();
        if (((byte)g_dwDebugFlags & 2) != 0)
            Set_DrawDebugLights((int)cur);
        if (((byte)g_dwDebugFlags & 4) != 0)
            Set_DrawDebugCameras(cur, 0xffffffff);
    }

    if ((g_dwRenderFlags & 4) != 0) {
        /* (uint64)(now - start) / duration in extended precision: the difference is zero-extended (FILD of a qword whose
         * high dword is 0), so a clock behind the start time gives a large positive value, not a negative one.
         * The compares are x87 FCOM + TEST AH: "C0" (below or unordered) and "C0|C3" (below, equal or unordered).
         * `volatile` keeps every step on v as written (at -O2 gcc rewrote the FCHS / 1 - v pair and flipped NaN signs). */
        uint diff = sputTime_GetGameTime() - g_dwIrisStart;
        volatile long double v = (long double)(unsigned long long)diff / (long double)g_flIrisDuration;
        float out;
        if (!(v >= 0.0L))
            v = -v;
        if (!(v > 1.0L))
            g_dwRenderFlags &= ~8u;
        else {
            v = 1.0L;
            if (!(g_flIrisDuration >= 0.0f))
                g_dwRenderFlags &= ~4u;
            else
                g_dwRenderFlags |= 8u;
        }
        if (!(g_flIrisDuration > 0.0f))
            v = 1.0L - v;
        out = (float)v;
        sputRender_DrawIrisEffect(out, g_nIrisX, g_nIrisY);
        if (!(g_flIrisDuration >= 0.0f)) {
            rect[0] = 0; rect[1] = 0; rect[2] = 0x280; rect[3] = 0x1e0;
            MarkDirtyRect(rect, 0);
        }
    }

    stdDisplay_VBufferLock(&g_dwStdDisplay_backBuffer);
    UINT_008a94b8 = UINT_0090563c;
    sputText_Update(1);
    stdDisplay_VBufferUnlock(&g_dwStdDisplay_backBuffer);
    g_nSputRender_Reset = 0;
}
#endif
