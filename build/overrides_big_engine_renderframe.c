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
    ((void (__cdecl *)(char *, char *, int))g_pSvcMain->pAssertFail)(s_Bad_Colormap_Reference_004e8090,
                                                                       s_main_sputResource_h_004e80a8, 0x9f);
}

/* Draws one frame.
 *   mode (UINT_008a8c40) 0: nothing.
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
    uint mode = UINT_008a8c40;
    int rect[4];
    uint vec[3];                /* scale vector passed to Matrix_BuildTransform2 (float bit patterns) */
    byte *set, *rec, *os, *actor, *entry, *cm;
    uint *list = &UINT_008c9568;
    int setup, n, k, cnt;
    void *cur;

    if (mode == 0)
        return;

    if (mode == 3) {
        float dt;
        Movie_SetTarget(&g_BackBuffer);
        if (Movie_PollPlayback() != 0) {
            cnt = g_nBufferCount;
            UINT_008a8c40 = 2;
            rect[0] = 0; rect[1] = 0; rect[2] = 0x280; rect[3] = 0x1e0;
            if (cnt > 0) {
                n = 0;
                do {
                    DirtyRect_Add(rect, 1, n);
                    n++;
                } while (n < g_nBufferCount);
            }
            sputRender_ForceRefresh();
            UINT_008c97f8 = 1;
        }
        dt = sputTime_GetFrameTimeFlex();
        Actors_UpdateTalking(dt);
        Surface_Lock(&g_BackBuffer);
        UINT_008a94b8 = UINT_0090563c;
        TextObjects_Update(0);
        Surface_Unlock(&g_BackBuffer);
        Render_Present();
        return;
    }

    if (mode == 4) {
        if (g_nFullRedrawPending != 0) {
            grimlib_UserPaint();
            g_nFullRedrawPending = 0;
            return;
        }
        g_nFullRedrawPending = 0;
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
            if (*(int *)((byte *)cur + 0xb4) != g_nRenderedSetup || g_nFullRedrawPending != 0)
                changed = 1;
        }
        if (changed) {
            DirtyRect_Clear();
            set = (byte *)sputRoom_GetCurrentRoom();
            g_pRenderedSet = set;
            setup = *(int *)(set + 0xb4);
            g_nRenderedSetup = setup;
            Set_SwitchSetup(set, setup);
            sputLua_PostCameraChange(g_nRenderedSetup);
        }
    }

    /* the setup record (300 bytes per setup).  The original keeps this pointer in EBX and spills it to [ESP+0x10], the slot
     * that also holds the frame time (mode 3) and the iris value: it is an address, never a float. */
    setup = g_nRenderedSetup;
    set = (byte *)g_pRenderedSet;
    rec = (byte *)(ER_U32(set, 0xac) + (uint)setup * 300u);
    sputRender_SyncCamera(set, setup);

    for (os = ER_PTR(rec, 0x128); os != 0; os = ER_PTR(os, 0xf8))
        ObjectState_Draw(os, 3, g_pBackgroundSurface, g_pZBufferSurface);

    Profile_Begin(4);
    if (g_nDrawEnabled != 0)
        DirtyRect_Flush(&g_BackBuffer, (void *)UINT_008c97a4);
    Profile_End(4);
    Movie_SetTarget(&g_BackBuffer);
    Movie_PollPlayback();
    Surface_Lock(&g_BackBuffer);
    Primitives_DrawAll(1);
    Surface_Unlock(&g_BackBuffer);
    for (os = ER_PTR(rec, 0x128); os != 0; os = ER_PTR(os, 0xf8))
        ObjectState_Draw(os, 1, &g_BackBuffer, (void *)UINT_008c97a4);
    rdroid_BeginFrame();
    Render_BuildActorDrawList();

    if (UINT_008a952c != 0 || ((byte)g_dwRenderDebugFlags & 1) != 0) {
        Profile_Begin(5);
        n = 0;
        if ((int)UINT_008a952c > 0) {
            do {
                entry = (byte *)list[n];
                actor = (byte *)g_pActorTable + *(int *)(entry + 8) * 0xa8;
                if (entry[0] == 0)
                    Costume_TouchComponents(*(int *)ER_PTR(actor, 0xa0));
                n++;
            } while (n < (int)UINT_008a952c);
        }
        Profile_End(5);
        if (((byte)g_dwRenderDebugFlags & 1) != 0) {
            Surface_Lock(&g_BackBuffer);
            if (((byte)g_dwRenderDebugFlags & 8) != 0)
                ((void (__cdecl *)(void *))Sector_DrawAllDebug)(sputRoom_GetCurrentRoom());
            else
                Render_DrawDebugGrid();
            Surface_Unlock(&g_BackBuffer);
        }

        Profile_Begin(6);
        /* the draw list from the last entry to the first */
        for (k = n; k != 0; k--) {
            entry = (byte *)list[k - 1];
            actor = (byte *)g_pActorTable + *(int *)(entry + 8) * 0xa8;
            if (ER_U32(actor, 0x30) != 0x3f800000) {          /* integer compare of the float scale with 1.0f */
                vec[0] = ER_U32(actor, 0x30);
                vec[1] = ER_U32(actor, 0x30);
                vec[2] = ER_U32(actor, 0x30);
                Matrix_BuildTransform2(Actor_GetFrame(actor), (undefined4)vec);
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
                ((void (__cdecl *)(uint, int))UINT_008c97b8)(*(uint *)(cm + 4) + 0x30, 0);
                {
                    float *frame = Actor_GetFrame(actor);
                    Actor_DrawCostumes(ER_U32(actor, 0xa0), (undefined4)frame);
                }
                if (((byte)g_dwRenderDebugFlags & 1) != 0)
                    Actor_DrawDebugWalker(actor);
                break;
            case 1:
                if (g_nZBufferEnabled == 0)
                    Surface_Lock(&g_BackBuffer);
                Actor_ComputeScreenBox(actor);
                if (g_nZBufferEnabled == 0)
                    Surface_Unlock(&g_BackBuffer);
                Render_InvalidateRectLastBuffer((int *)(actor + 0x6c), 1);
                break;
            }
            if (ER_U32(actor, 0x30) != 0x3f800000) {
                /* fld 1.0; fdiv [scale]; fst x3: the quotient rounded once to float */
                long double q = 1.0L / (long double)*(float *)(actor + 0x30);
                float r = (float)q;
                vec[0] = *(uint *)&r;
                vec[1] = vec[0];
                vec[2] = vec[0];
                Matrix_BuildTransform2(Actor_GetFrame(actor), (undefined4)vec);
            }
        }
        Profile_End(6);
        Profile_Begin(7);
        rdroid_EndFrame();
        Profile_End(7);
        for (os = ER_PTR(rec, 0x128); os != 0; os = ER_PTR(os, 0xf8))
            ObjectState_Draw(os, 2, &g_BackBuffer, (void *)UINT_008c97a4);
    }

    Surface_Lock(&g_BackBuffer);
    Primitives_DrawAll(2);
    Surface_Unlock(&g_BackBuffer);
    if (((byte)g_dwRenderDebugFlags & 1) != 0) {
        cur = sputRoom_GetCurrentRoom();
        if (((byte)g_dwRenderDebugFlags & 2) != 0)
            Set_DrawDebugLights((int)cur);
        if (((byte)g_dwRenderDebugFlags & 4) != 0)
            Set_DrawDebugCameras(cur, 0xffffffff);
    }

    if ((g_dwRenderFlags & 4) != 0) {
        /* (uint64)(now - start) / duration in extended precision: the difference is zero-extended (FILD of a qword whose
         * high dword is 0), so a clock behind the start time gives a large positive value, not a negative one.
         * The compares are x87 FCOM + TEST AH: "C0" (below or unordered) and "C0|C3" (below, equal or unordered).
         * `volatile` keeps every step on v as written (at -O2 gcc rewrote the FCHS / 1 - v pair and flipped NaN signs). */
        uint diff = Timer_GetTotalMs() - g_dwIrisStartMs;
        volatile long double v = (long double)(unsigned long long)diff / (long double)g_flIrisDurationMs;
        float out;
        if (!(v >= 0.0L))
            v = -v;
        if (!(v > 1.0L))
            g_dwRenderFlags &= ~8u;
        else {
            v = 1.0L;
            if (!(g_flIrisDurationMs >= 0.0f))
                g_dwRenderFlags &= ~4u;
            else
                g_dwRenderFlags |= 8u;
        }
        if (!(g_flIrisDurationMs > 0.0f))
            v = 1.0L - v;
        out = (float)v;
        Render_DrawIris(out, g_nIrisX, g_nIrisY);
        if (!(g_flIrisDurationMs >= 0.0f)) {
            rect[0] = 0; rect[1] = 0; rect[2] = 0x280; rect[3] = 0x1e0;
            MarkDirtyRect(rect, 0);
        }
    }

    Surface_Lock(&g_BackBuffer);
    UINT_008a94b8 = UINT_0090563c;
    TextObjects_Update(1);
    Surface_Unlock(&g_BackBuffer);
    g_nFullRedrawPending = 0;
}
#endif
