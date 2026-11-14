/* GRIMFANDANGO.EXE :: insanetimer.c
 * functions 0x004cdc90 .. 0x004ce260 (17 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004cdc90  sys_timer_module ---- */
/* Entry of LECMODULE insane_timer: stores the service table of the module manager and the workspace
   size, registers the module and the TIMER insane interface Original name sys_timer_module (the
   remaster's GrimFandango (Linux): slot 0 of the "LECMODULE=insane_timer" service table); was
   InsaneTimer_Register. */

int __cdecl sys_timer_module(int *services,uint workspaceSize)

{
  g_pInsaneTimer_share_services = services;
  g_dwInsaneTimer_share_config = workspaceSize;
  (*(code *)*services)(s_LECMODULE_insane_timer_004f3c40,&g_apfnInsaneTimerModule);
  (*(code *)*g_pInsaneTimer_share_services)(s_TIMER_insane_004f3c30,&g_pInsaneTimer_timer_services);
  g_dwTimer_rate = 300;
  return 0;
}

/* ---- 0x004cdce0  InsaneTimer_module_terminate ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Original name InsaneTimer_module_terminate (the remaster's GrimFandango (Linux): slot 1 of the
   "LECMODULE=insane_timer" service table; module_terminate is a static several LEC modules have,
   written with the module prefix); was InsaneTimer_Unregister. */

void InsaneTimer_module_terminate(void)

{
  (*(code *)g_pInsaneTimer_share_services[1])(s_TIMER_insane_004f3c30);
  (*(code *)g_pInsaneTimer_share_services[1])(s_LECMODULE_insane_timer_004f3c40);
  return;
}

/* ---- 0x004cdd10  InsaneTimer_module_startup ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Allocates the timer workspace and starts the timer thread Original name
   InsaneTimer_module_startup (the remaster's GrimFandango (Linux): the static module_startup of the
   InsaneTimer module (the remaster has one per module file, hence the prefix); strings: 'Timer
   Module: Cannot allocate memory services.'); was InsaneTimer_Init. */

int InsaneTimer_module_startup(void)

{
  int iVar1;
  
  g_dwInsaneTimer_memory_services =
       (*(code *)g_pInsaneTimer_share_services[2])
                 (s_MEMORY_workspace_004f14ec,g_dwInsaneTimer_share_config);
  if (g_dwInsaneTimer_memory_services == 0) {
    (*(code *)g_pInsaneTimer_share_services[8])(s_Timer_Module__Cannot_allocate_me_004f3c58);
    return -1;
  }
  iVar1 = InsaneTimer_StartThread();
  return iVar1;
}

/* ---- 0x004cdd60  InsaneTimer_module_shutdown ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Original name InsaneTimer_module_shutdown (the remaster's GrimFandango (Linux): slot 3 of the
   "LECMODULE=insane_timer" service table; module_shutdown is a static several LEC modules have,
   written with the module prefix); was InsaneTimer_Shutdown. */

void InsaneTimer_module_shutdown(void)

{
  (*(code *)g_pInsaneTimer_share_services[3])(g_dwInsaneTimer_memory_services);
  InsaneTimer_StopThread();
  return;
}

/* ---- 0x004cdd80  InsaneTimer_StartThread ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* First caller clears the 20 timer slots and creates the high priority thread timer_thread */

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
    } while ((int)puVar2 < ((unsigned)(uintptr_t)&UINT_008da858));
    g_dwSys_timer_count = 0x4dae;
    UINT_008da858 = CreateThread(0,0,((unsigned)(uintptr_t)timer_thread),0,0,(int)local_4);
    SetThreadPriority(UINT_008da858,2);
    _DAT_004f3c2c = 0xffffffff;
  }
  return 0;
}
#undef local_4

#endif


/* ---- 0x004cddf0  timer_thread ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Timer thread: wakes every 16 ms of timeGetTime and runs InsaneTimer_Tick Original name
   timer_thread (the remaster's GrimFandango (Linux): the timer thread: the 16 ms tick loop
   (lastTime += 0x10, wait up to 10 ms) in both builds; the remaster inlined the tick
   (InsaneTimer_Tick) into it); was InsaneTimer_ThreadProc. */

undefined * __stdcall timer_thread(int a1)

{
  int a1_00;
  int iVar1;
  
  a1_00 = CreateEventA(0,1,0,0);
  g_dwTimer_thread_lastTime = timeGetTime();
  while (UINT_008da874 != 0) {
    iVar1 = timeGetTime();
    if ((int)(iVar1 - g_dwTimer_thread_lastTime) < 0x11) {
      iVar1 = 0x10 - (iVar1 - g_dwTimer_thread_lastTime);
    }
    else {
      g_dwTimer_thread_lastTime = g_dwTimer_thread_lastTime + 0x10;
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
      OutputDebugStringA(((unsigned)(uintptr_t)&s_Waiting_for_timer_thread_to_exit_004f3c88));
      iVar1 = GetExitCodeThread(UINT_008da858,(_stkneg + 20));
    }
    CloseHandle(UINT_008da858);
  }
  return;
}
#undef local_4

#endif


/* ---- 0x004cdef0  sys_Disable ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* TIMER insane: suspends the periodic callbacks (counter) Original name sys_Disable (the remaster's
   GrimFandango (Linux): slot 2 of the "TIMER=insane" service table); was InsaneTimer_Hold. */

void sys_Disable(void)

{
  g_dwSys_disable_flag = g_dwSys_disable_flag + 1;
  return;
}

/* ---- 0x004cdf00  sys_Enable ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Original name sys_Enable (the remaster's GrimFandango (Linux): slot 3 of the "TIMER=insane"
   service table); was InsaneTimer_Release. */

void sys_Enable(void)

{
  g_dwSys_disable_flag = g_dwSys_disable_flag - 1;
  return;
}

/* ---- 0x004cdf10  sys_Alloc ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Finds a free slot (1..19) and fills in callback, period, flags and user data; returns the slot
   number or 0 Original name sys_Alloc (the remaster's GrimFandango (Linux): slot 0 of the
   "TIMER=insane" service table); was InsaneTimer_AddTimer. */

int __cdecl sys_Alloc(void *callback,int period,uint flags,int user)

{
  int iVar1;
  uint *puVar2;
  int iVar3;
  
  iVar1 = 1;
  puVar2 = &UINT_008da5f8;
  do {
    if (*puVar2 == 0) {
      iVar3 = iVar1 * 0x20;
      *(undefined4 *)(iVar3 + ((unsigned)(uintptr_t)&DAT_008da5e8)) = 0;
      *(undefined4 *)(&DAT_008da5ec + iVar3) = 0;
      *(int *)(iVar3 + ((unsigned)(uintptr_t)&DAT_008da5e4)) = user;
      *(uint *)(iVar3 + ((unsigned)(uintptr_t)&DAT_008da5e0)) = flags;
      *(int *)(&DAT_008da5dc + iVar3) = period;
      *(void **)(&DAT_008da5d8 + iVar3) = callback;
      *(undefined4 *)(iVar3 + ((unsigned)(uintptr_t)&DAT_008da5f0)) = 0;
      *(undefined4 *)(iVar3 + ((unsigned)(uintptr_t)&DAT_008da5f4)) = 0;
      return iVar1;
    }
    puVar2 = puVar2 + 8;
    iVar1 = iVar1 + 1;
  } while ((int)puVar2 < ((unsigned)(uintptr_t)&UINT_008da858));
  return 0;
}
#endif


/* ---- 0x004cdf80  sys_Free ---- */
/* Original name sys_Free (the remaster's GrimFandango (Linux): slot 1 of the "TIMER=insane" service
   table); was InsaneTimer_RemoveTimer. */

void __cdecl sys_Free(int slot)

{
  if ((0 < slot) && (slot < 0x14)) {
    *(undefined4 *)(&DAT_008da5d8 + slot * 0x20) = 0;
  }
  return;
}

/* ---- 0x004cdfa0  sys_Reset ---- */
/* Original name sys_Reset (the remaster's GrimFandango (Linux): slot 4 of the "TIMER=insane"
   service table); was InsaneTimer_SetPeriod. */

void __cdecl sys_Reset(int slot,int period)

{
  if ((0 < slot) && (slot < 0x14)) {
    *(int *)(&DAT_008da5dc + slot * 0x20) = period;
    *(undefined4 *)(&DAT_008da5ec + slot * 0x20) = 0;
  }
  return;
}

/* ---- 0x004cdfd0  sys_Delay ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Runs InsaneTimer_GetClock-driven steps until the clock has advanced by the given number of ticks
   Original name sys_Delay (the remaster's GrimFandango (Linux): slot 5 of the "TIMER=insane"
   service table); was InsaneTimer_Run. */

void __cdecl sys_Delay(int ticks)

{
  int iVar1;
  int iVar2;
  
  iVar2 = g_nSys_global_timer;
  iVar1 = ticks + g_nSys_global_timer;
  do {
    if (iVar1 <= g_nSys_global_timer) {
      return;
    }
    sys_GetTime();
  } while (iVar2 <= g_nSys_global_timer);
  return;
}
#endif


/* ---- 0x004ce000  sys_GetTime ---- */
/* Original name sys_GetTime (the remaster's GrimFandango (Linux): slot 6 of the "TIMER=insane"
   service table); was InsaneTimer_GetClock. */

int __cdecl sys_GetTime(void)

{
  return g_nSys_global_timer;
}

/* ---- 0x004ce060  InsaneTimer_Tick ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Advances the timer clock by one step and runs the due callbacks */

void __cdecl InsaneTimer_Tick(void)

{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  int iVar4;
  
  g_nSys_global_timer = g_nSys_global_timer + g_dwSys_timer_count;
  if (g_dwSys_disable_flag == 0) {
    iVar4 = 1;
    _DAT_008da86c = 1;
    UINT_008da870 = UINT_008da868;
    UINT_008da868 = 0;
    puVar3 = &UINT_008da60c;
    do {
      uVar2 = g_dwSys_timer_count;
      if (puVar3[-5] != 0) {
        *puVar3 = *puVar3 + g_dwSys_timer_count;
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
    } while ((int)puVar3 < ((unsigned)(uintptr_t)&DAT_008da86c));
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
    } while ((int)puVar3 < ((unsigned)(uintptr_t)&DAT_008da86c));
    UINT_008da868 = UINT_008da870;
    _DAT_008da86c = 0;
    if ((UINT_008da880 == 0) && (UINT_008da87c == 0)) {
      UINT_008da880 = 1;
      sys_timer_dispatcher();
      UINT_008da880 = 0;
    }
  }
  return;
}
#endif


/* ---- 0x004ce1d0  sys_timer_dispatcher ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* setjmp-protected per-tick voice servicing Original name sys_timer_dispatcher (the remaster's
   GrimFandango (Linux): the deferred-timer dispatcher at the end of the tick in both builds:
   setjmp, run the timers with flags & 5 == 4, longjmp(state, 2); the remaster inlined
   InsaneTimer_RunDeferred into it); was InsaneTimer_ServiceDeferred. */

void __cdecl sys_timer_dispatcher(void)

{
  uint uVar1;
  uint unaff_EBP;
  int unaff_ESI;
  
  if ((UINT_008da88c == 0) || (UINT_008da88c = UINT_008da88c - 1, UINT_008da88c == 0)) {
    uVar1 = _setjmp3((undefined4 *)&DAT_008da548,0,unaff_ESI,unaff_EBP);
    if (uVar1 == 0) {
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
void __cdecl InsaneTimer_RunDeferred(void)

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
    if (((unsigned)(uintptr_t)&DAT_008da86b) < (int)puVar3) {
      return;
    }
  } while( true );
}
#endif

