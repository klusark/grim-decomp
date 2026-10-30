/* GRIMFANDANGO.EXE :: insanetimer.c
 * functions 0x004cdc90 .. 0x004ce260 (17 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004cdc90  InsaneTimer_Register ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Entry of LECMODULE insane_timer: stores the service table of the module manager and the workspace
   size, registers the module and the TIMER insane interface */

int __cdecl InsaneTimer_Register(int *services,uint workspaceSize)

{
  g_pTimerServices = services;
  UINT_008da85c = workspaceSize;
  (*(code *)*services)(s_LECMODULE_insane_timer_004f3c40,&g_apfnInsaneTimerModule);
  (*(code *)*g_pTimerServices)(s_TIMER_insane_004f3c30,&g_apfnInsaneTimerInterface);
  UINT_008da544 = 300;
  return 0;
}
#endif


/* ---- 0x004cdce0  InsaneTimer_Unregister ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void InsaneTimer_Unregister(void)

{
  (*(code *)g_pTimerServices[1])(s_TIMER_insane_004f3c30);
  (*(code *)g_pTimerServices[1])(s_LECMODULE_insane_timer_004f3c40);
  return;
}
#endif


/* ---- 0x004cdd10  InsaneTimer_Init ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Allocates the timer workspace and starts the timer thread */

int InsaneTimer_Init(void)

{
  int iVar1;
  
  UINT_008da540 = (*(code *)g_pTimerServices[2])(s_MEMORY_workspace_004f14ec,UINT_008da85c);
  if (UINT_008da540 == 0) {
    (*(code *)g_pTimerServices[8])(s_Timer_Module__Cannot_allocate_me_004f3c58);
    return -1;
  }
  iVar1 = InsaneTimer_StartThread();
  return iVar1;
}
#endif


/* ---- 0x004cdd60  InsaneTimer_Shutdown ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void InsaneTimer_Shutdown(void)

{
  (*(code *)g_pTimerServices[3])(UINT_008da540);
  InsaneTimer_StopThread();
  return;
}
#endif


/* ---- 0x004cdd80  InsaneTimer_StartThread ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* First caller clears the 20 timer slots and creates the high priority thread
   InsaneTimer_ThreadProc */

int InsaneTimer_StartThread(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint *puVar2;
  bool bVar3;
  #define local_4 (*(undefined1 (*)[4])(_frame + (0x20 - 0x4)))
  
  uVar1 = UINT_008da874 + 1;
  bVar3 = UINT_008da874 == 0;
  UINT_008da874 = uVar1;
  if (bVar3) {
    puVar2 = &UINT_008da5f8;
    do {
      *puVar2 = 0;
      puVar2 = puVar2 + 8;
    } while ((int)puVar2 < IMG_ADDR(0x008da858));
    g_dwTimerStep = 0x4dae;
    UINT_008da858 = CreateThread(0,0,((unsigned)(uintptr_t)InsaneTimer_ThreadProc),0,0,(int)local_4);
    SetThreadPriority(UINT_008da858,2);
    _DAT_004f3c2c = 0xffffffff;
  }
  return 0;
}
#undef local_4

#endif


/* ---- 0x004cddf0  InsaneTimer_ThreadProc ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Timer thread: wakes every 16 ms of timeGetTime and runs InsaneTimer_Tick */

undefined * __stdcall InsaneTimer_ThreadProc(int a1)

{
  int a1_00;
  int iVar1;
  
  a1_00 = CreateEventA(0,1,0,0);
  UINT_008da864 = timeGetTime();
  while (UINT_008da874 != 0) {
    iVar1 = timeGetTime();
    if ((int)(iVar1 - UINT_008da864) < 0x11) {
      iVar1 = 0x10 - (iVar1 - UINT_008da864);
    }
    else {
      UINT_008da864 = UINT_008da864 + 0x10;
      InsaneTimer_Tick();
      iVar1 = 10;
    }
    if (iVar1 == 0) {
      iVar1 = 1;
    }
    if (10 < iVar1) {
      iVar1 = 10;
    }
    WaitForSingleObject(a1_00,iVar1);
  }
  CloseHandle(a1_00);
  return (undefined *)0x0;
}
#endif


/* ---- 0x004cde80  InsaneTimer_StopThread ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void InsaneTimer_StopThread(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  unsigned char _stkneg[32] __attribute__((aligned(16)));  /* the original frame below the return address */
  int iVar1;
  int unaff_ESI;
  #define local_4 (*(undefined1 (*)[4])(_frame + (0x20 - 0x4)))
  
  UINT_008da874 = UINT_008da874 - 1;
  if (UINT_008da874 == 0) {
    iVar1 = GetExitCodeThread(UINT_008da858,local_4);
    while ((iVar1 != 0 && (unaff_ESI == 0x103))) {
      OutputDebugStringA(IMG_ADDR(0x004f3c88));
      iVar1 = GetExitCodeThread(UINT_008da858,(_stkneg + 20));
    }
    CloseHandle(UINT_008da858);
  }
  return;
}
#undef local_4

#endif


/* ---- 0x004cdef0  InsaneTimer_Hold ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* TIMER insane: suspends the periodic callbacks (counter) */

void InsaneTimer_Hold(void)

{
  UINT_008da878 = UINT_008da878 + 1;
  return;
}
#endif


/* ---- 0x004cdf00  InsaneTimer_Release ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void InsaneTimer_Release(void)

{
  UINT_008da878 = UINT_008da878 - 1;
  return;
}
#endif


/* ---- 0x004cdf10  InsaneTimer_AddTimer ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Finds a free slot (1..19) and fills in callback, period, flags and user data; returns the slot
   number or 0 */

int __cdecl InsaneTimer_AddTimer(void *callback,int period,uint flags,int user)

{
  int iVar1;
  uint *puVar2;
  int iVar3;
  
  iVar1 = 1;
  puVar2 = &UINT_008da5f8;
  do {
    if (*puVar2 == 0) {
      iVar3 = iVar1 * 0x20;
      *(undefined4 *)(iVar3 + IMG_ADDR(0x008da5e8)) = 0;
      *(undefined4 *)(&DAT_008da5ec + iVar3) = 0;
      *(int *)(iVar3 + IMG_ADDR(0x008da5e4)) = user;
      *(uint *)(iVar3 + IMG_ADDR(0x008da5e0)) = flags;
      *(int *)(&DAT_008da5dc + iVar3) = period;
      *(void **)(&DAT_008da5d8 + iVar3) = callback;
      *(undefined4 *)(iVar3 + IMG_ADDR(0x008da5f0)) = 0;
      *(undefined4 *)(iVar3 + IMG_ADDR(0x008da5f4)) = 0;
      return iVar1;
    }
    puVar2 = puVar2 + 8;
    iVar1 = iVar1 + 1;
  } while ((int)puVar2 < IMG_ADDR(0x008da858));
  return 0;
}
#endif


/* ---- 0x004cdf80  InsaneTimer_RemoveTimer ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void __cdecl InsaneTimer_RemoveTimer(int slot)

{
  if ((0 < slot) && (slot < 0x14)) {
    *(undefined4 *)(&DAT_008da5d8 + slot * 0x20) = 0;
  }
  return;
}
#endif


/* ---- 0x004cdfa0  InsaneTimer_SetPeriod ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void __cdecl InsaneTimer_SetPeriod(int slot,int period)

{
  if ((0 < slot) && (slot < 0x14)) {
    *(int *)(&DAT_008da5dc + slot * 0x20) = period;
    *(undefined4 *)(&DAT_008da5ec + slot * 0x20) = 0;
  }
  return;
}
#endif


/* ---- 0x004cdfd0  InsaneTimer_Run ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Runs InsaneTimer_GetClock-driven steps until the clock has advanced by the given number of ticks
    */

void __cdecl InsaneTimer_Run(int ticks)

{
  int iVar1;
  int iVar2;
  
  iVar2 = g_nTimerClock;
  iVar1 = ticks + g_nTimerClock;
  do {
    if (iVar1 <= g_nTimerClock) {
      return;
    }
    InsaneTimer_GetClock();
  } while (iVar2 <= g_nTimerClock);
  return;
}
#endif


/* ---- 0x004ce000  InsaneTimer_GetClock ---- */
int InsaneTimer_GetClock(void)

{
  return g_nTimerClock;
}

/* ---- 0x004ce060  InsaneTimer_Tick ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Advances the timer clock by one step and runs the due callbacks */

void InsaneTimer_Tick(void)

{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  int iVar4;
  
  g_nTimerClock = g_nTimerClock + g_dwTimerStep;
  if (UINT_008da878 == 0) {
    iVar4 = 1;
    _DAT_008da86c = 1;
    UINT_008da870 = UINT_008da868;
    UINT_008da868 = 0;
    puVar3 = &UINT_008da60c;
    do {
      uVar2 = g_dwTimerStep;
      if (puVar3[-5] != 0) {
        *puVar3 = *puVar3 + g_dwTimerStep;
        puVar3[2] = puVar3[2] + uVar2;
        if (((((byte)puVar3[-3] & 5) == 1) && (uVar2 = puVar3[-4], uVar2 != 0)) &&
           (uVar1 = *puVar3, (int)uVar2 <= (int)uVar1)) {
          do {
            *puVar3 = uVar1 - uVar2;
            if ((puVar3[-3] & 2) != 0) {
              puVar3[-4] = 0;
              (*(code *)puVar3[-5])(iVar4,puVar3[-2]);
              break;
            }
            (*(code *)puVar3[-5])(iVar4,puVar3[-2]);
            uVar1 = *puVar3;
            uVar2 = puVar3[-4];
          } while ((int)uVar2 <= (int)uVar1);
        }
      }
      puVar3 = puVar3 + 8;
      iVar4 = iVar4 + 1;
    } while ((int)puVar3 < IMG_ADDR(0x008da86c));
    iVar4 = 1;
    puVar3 = &UINT_008da60c;
    do {
      if (((puVar3[-5] != 0) && ((puVar3[-3] & 5) == 0)) && ((puVar3[-4] != 0 && (puVar3[-1] == 0)))
         ) {
        puVar3[-1] = 1;
        uVar2 = *puVar3;
        uVar1 = puVar3[-4];
        if ((int)uVar1 <= (int)uVar2) {
          do {
            *puVar3 = uVar2 - uVar1;
            if ((puVar3[-3] & 2) != 0) {
              puVar3[-4] = 0;
              (*(code *)puVar3[-5])(iVar4,puVar3[-2]);
              break;
            }
            (*(code *)puVar3[-5])(iVar4,puVar3[-2]);
            uVar2 = *puVar3;
            uVar1 = puVar3[-4];
          } while ((int)uVar1 <= (int)uVar2);
        }
        puVar3[-1] = 0;
      }
      puVar3 = puVar3 + 8;
      iVar4 = iVar4 + 1;
    } while ((int)puVar3 < IMG_ADDR(0x008da86c));
    UINT_008da868 = UINT_008da870;
    _DAT_008da86c = 0;
    if ((UINT_008da880 == 0) && (UINT_008da87c == 0)) {
      UINT_008da880 = 1;
      InsaneTimer_ServiceDeferred();
      UINT_008da880 = 0;
    }
  }
  return;
}
#endif


/* ---- 0x004ce1d0  InsaneTimer_ServiceDeferred ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* setjmp-protected per-tick voice servicing */

void InsaneTimer_ServiceDeferred(void)

{
  int iVar1;
  
  if ((UINT_008da88c == 0) || (UINT_008da88c = UINT_008da88c - 1, UINT_008da88c == 0)) {
    iVar1 = ((code *)_setjmp3)(&DAT_008da548,0);
    if (iVar1 == 0) {
      if (UINT_008da884 != 0) {
        UINT_008da884 = 0;
        _DAT_008da888 = 1;
        ((code *)longjmp)(&DAT_008da588,1);
      }
      UINT_008da884 = 0;
      _DAT_008da888 = 1;
      InsaneTimer_RunDeferred();
      _DAT_008da888 = 0;
      _DAT_008da5d0 = UINT_008da5d4;
      ((code *)longjmp)(&DAT_008da548,2);
    }
    UINT_008da868 = 0;
  }
  return;
}
#endif


/* ---- 0x004ce260  InsaneTimer_RunDeferred ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void InsaneTimer_RunDeferred(void)

{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  int iVar4;
  
  iVar4 = 1;
  puVar3 = &UINT_008da60c;
  do {
    puVar3[1] = 1;
    if ((((puVar3[-5] != 0) && (((byte)puVar3[-3] & 5) == 4)) && (uVar2 = puVar3[-4], uVar2 != 0))
       && (uVar1 = *puVar3, (int)uVar2 <= (int)uVar1)) {
      do {
        *puVar3 = uVar1 - uVar2;
        if ((puVar3[-3] & 2) != 0) {
          puVar3[-4] = 0;
          (*(code *)puVar3[-5])(iVar4,puVar3[-2]);
          break;
        }
        (*(code *)puVar3[-5])(iVar4,puVar3[-2]);
        uVar1 = *puVar3;
        uVar2 = puVar3[-4];
      } while ((int)uVar2 <= (int)uVar1);
    }
    puVar3[1] = 0;
    puVar3 = puVar3 + 8;
    iVar4 = iVar4 + 1;
    if (IMG_ADDR(0x008da86b) < (int)puVar3) {
      return;
    }
  } while( true );
}
#endif

