/* GRIMFANDANGO.EXE :: stdinput.c
 * functions 0x00476f10 .. 0x00477e70 (22 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00476f10  stdControl_Startup ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Creates DirectInput, the keyboard and mouse devices and scans the joysticks Original name
   stdControl_Startup (the remaster's GrimFandango (Linux): aligned call in sputControl_Startup);
   was Input_Init. */

undefined * stdControl_Startup(void)

{
  uint a1;
  int iVar1;
  uint *puVar2;
  void **a3;
  int a4;
  
  puVar2 = &g_dwStdControl_aAxes;
  for (iVar1 = 0x5a; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  a4 = 0;
  a3 = &g_pDirectInput;
  puVar2 = &UINT_00803fd0;
  for (iVar1 = 0xf; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  iVar1 = 0x500;
  a1 = Win_GetInstance();
  DirectInputCreateA(a1,iVar1,(int)a3,a4);
  Input_CreateKeyboard();
  Input_InitJoysticks();
  Input_CreateMouse();
  stdControl_Reset();
  g_dwStdControl_bStartup = 1;
  return (undefined *)0x1;
}

/* ---- 0x00476f70  stdControl_Shutdown ---- */
/* Original name stdControl_Shutdown (the remaster's GrimFandango (Linux): aligned call in
   sputControl_Shutdown); was Input_Shutdown. */

void __cdecl stdControl_Shutdown(void)

{
  if (g_dwStdControl_bStartup != 0) {
    g_dwStdControl_bStartup = 0;
    if (g_pDInputMouse != (void *)0x0) {
      (**(code_std **)(*(int *)g_pDInputMouse + 8))(g_pDInputMouse);
    }
    if (g_pDInputKeyboard != (void *)0x0) {
      (**(code_std **)(*(int *)g_pDInputKeyboard + 8))(g_pDInputKeyboard);
    }
    if (g_pDirectInput != (void *)0x0) {
      (**(code_std **)(*(int *)g_pDirectInput + 8))(g_pDirectInput);
    }
  }
  return;
}

/* ---- 0x00476fc0  stdControl_Open ---- */
/* Original name stdControl_Open (the remaster's GrimFandango (Linux): the only call of
   sputControl_Open (sets stdControl_bOpen and activates the controls)); was Input_Enable. */

uint __cdecl stdControl_Open(void)

{
  g_nStdControl_bOpen = 1;
  Input_SetAcquired(1);
  return 1;
}

/* ---- 0x00476fe0  stdControl_Close ---- */
/* Original name stdControl_Close (the remaster's GrimFandango (Linux): called by sputControl_Close
   in both builds; clears stdControl_bOpen and returns whether it was open); was Input_Disable. */

uint __cdecl stdControl_Close(void)

{
  if (g_nStdControl_bOpen == 0) {
    return 0;
  }
  Input_SetAcquired(0);
  g_nStdControl_bOpen = 0;
  return 1;
}

/* ---- 0x00477010  stdControl_Flush ---- */
/* Lua FlushControls: resets keyboard and joystick state Original name stdControl_Flush (the
   remaster's GrimFandango (Linux): Lua / module table entry 'FlushControls'); was Input_Flush. */

void __cdecl stdControl_Flush(void)

{
  g_dwCurReadTime = timeGetTime();
  if (g_pDInputKeyboard != (void *)0x0) {
    Input_FlushKeyboard();
  }
  if (g_pDInputMouse != (void *)0x0) {
    Input_FlushJoystick();
    return;
  }
  return;
}

/* ---- 0x00477040  stdControl_Reset ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Original name stdControl_Reset (the remaster's GrimFandango (Linux): same body (clears the mouse
   / joystick read flags, the two 0x680 joystick flags, bit 1 of every axis); called by
   sputControl_Reset in both builds); was Input_ResetState. */

void __cdecl stdControl_Reset(void)

{
  uint *puVar1;
  uint *puVar2;
  
  UINT_004dea40 = 0;
  UINT_00805fb8 = 0;
  UINT_00803fc8 = 0;
  UINT_00804010 = 0x680;
  _DAT_00803fcc = 0;
  _DAT_00804014 = 0x680;
  puVar1 = &g_dwStdControl_aAxes;
  do {
    puVar2 = puVar1 + 6;
    *puVar1 = *puVar1 & 0xfffffffd;
    puVar1 = puVar2;
  } while (puVar2 < &UINT_00901668);
  return;
}

/* ---- 0x00477090  stdControl_EnableAxis ---- */
/* Axes 0-11 belong to the two joysticks, 12-14 to the mouse Original name stdControl_EnableAxis
   (the remaster's GrimFandango (Linux): same body (axis < 0xf, only an available axis (bit 0) gets
   bit 1, then the mouse / joystick read flags; the remaster inlined Input_MarkAxisUsed); called by
   sputControl_EnableControl in both builds); was Input_EnableAxis. */

int __cdecl stdControl_EnableAxis(uint axis)

{
  if (0xe < axis) {
    return 0;
  }
  if (((&g_dwStdControl_aAxes)[axis * 6] & 1) == 0) {
    return 0;
  }
  (&g_dwStdControl_aAxes)[axis * 6] = (&g_dwStdControl_aAxes)[axis * 6] | 2;
  Input_MarkAxisUsed(axis);
  return 1;
}

/* ---- 0x004770d0  stdControl_ReadControls ---- */
/* Once per frame: polls keyboard, joysticks and mouse and records press/release times Original name
   stdControl_ReadControls (the remaster's GrimFandango (Linux): aligned call in
   sputControl_Update); was Input_Update. */

void __cdecl stdControl_ReadControls(void)

{
  uint uVar1;
  int iVar2;
  uint *puVar3;
  
  if (g_nInputAcquired != 0) {
    g_dwStdControl_bControlsIdle = 1;
    g_dwCurReadTime = timeGetTime();
    uVar1 = g_dwCurReadTime - g_dwLastReadTime;
    if (uVar1 != 0) {
      FLOAT_004dea44 = 1.0f / (float)uVar1;
      puVar3 = &UINT_00803fd0;
      UINT_00805fc8 = uVar1;
      for (iVar2 = 0xf; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = 0;
        puVar3 = puVar3 + 1;
      }
      FLOAT_004dea48 = FLOAT_004dea44 * 1000.0f;
      Input_PollKeyboard();
      if (UINT_00805fb8 != 0) {
        Input_PollJoysticks();
      }
      Input_PollMouse();
      g_dwLastReadTime = g_dwCurReadTime;
    }
  }
  return;
}

/* ---- 0x00477160  stdControl_ReadAxis ---- */
/* Original name stdControl_ReadAxis (the remaster's GrimFandango (Linux): aligned call in
   sputLua_GetControlStateL, sputLua_NotifyControlHandlers); was Input_GetAxis. */

float __cdecl stdControl_ReadAxis(int inputId)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  if (g_nInputAcquired == 0) {
    return 0.0f;
  }
  iVar5 = inputId * 0x18;
  if (((&g_dwStdControl_aAxes)[inputId * 6] & 2) == 0) {
    return 0.0f;
  }
  iVar3 = (&UINT_00803fd0)[inputId] - *(int *)(&DAT_0090150c + iVar5);
  if (iVar3 == 0) {
    return 0.0f;
  }
  if ((((&g_dwStdControl_aAxes)[inputId * 6] & 8) == 0) && (*(int *)(&DAT_00901510 + iVar5) != 0)) {
    iVar4 = iVar3;
    if (iVar3 < 0) {
      iVar4 = -iVar3;
    }
    if (iVar4 < *(int *)(&DAT_00901510 + iVar5)) {
      return 0.0f;
    }
  }
  fVar1 = (float)iVar3 * *(float *)(&DAT_00901514 + iVar5);
  fVar2 = fVar1;
  if (fVar1 < 0.0f) {
    fVar2 = -fVar1;
  }
  if (fVar2 <= 1e-05f) {
    fVar1 = 0.0f;
  }
  if ((g_dwStdControl_bControlsIdle != 0) && (fVar1 != 0.0f)) {
    g_dwStdControl_bControlsIdle = 0;
  }
  return fVar1;
}

/* ---- 0x00477230  stdControl_ReadKey ---- */
/* Original name stdControl_ReadKey (the remaster's GrimFandango (Linux): aligned call in
   sputLua_GetControlStateL, sputLua_NotifyControlHandlers, sputRender_ControlHandler); was
   Input_GetButtonState. */

int __cdecl stdControl_ReadKey(int inputId,int *down,int *justPressed)

{
  if ((g_nInputAcquired != 0) && (UINT_00805fa0 == 0)) {
    if ((g_dwStdControl_bControlsIdle != 0) && ((&g_dwKeyInfo)[inputId * 7] != 0)) {
      g_dwStdControl_bControlsIdle = 0;
    }
    if (down != (int *)0x0) {
      *down = (&UINT_0080402c)[inputId * 7];
    }
    if (justPressed != (int *)0x0) {
      *justPressed = (&UINT_00804030)[inputId * 7];
    }
    return (&g_dwKeyInfo)[inputId * 7];
  }
  if (down != (int *)0x0) {
    *down = 0;
  }
  if (justPressed != (int *)0x0) {
    *justPressed = 0;
  }
  return 0;
}

/* ---- 0x00477300  Input_SetAcquired ---- */
void __cdecl Input_SetAcquired(int acquire)

{
  if (g_nStdControl_bOpen != 0) {
    if (acquire != 0) {
      if ((g_pDInputMouse != (void *)0x0) && (UINT_004dea40 != 0)) {
        (**(code_std **)(*(int *)g_pDInputMouse + 0x1c))(g_pDInputMouse);
        ShowCursor(0);
      }
      if (g_pDInputKeyboard != (void *)0x0) {
        (**(code_std **)(*(int *)g_pDInputKeyboard + 0x1c))(g_pDInputKeyboard);
      }
      g_nInputAcquired = 1;
      return;
    }
    if (g_pDInputMouse != (void *)0x0) {
      (**(code_std **)(*(int *)g_pDInputMouse + 0x20))(g_pDInputMouse);
      ShowCursor(1);
    }
    if (g_pDInputKeyboard != (void *)0x0) {
      (**(code_std **)(*(int *)g_pDInputKeyboard + 0x20))(g_pDInputKeyboard);
    }
    g_nInputAcquired = 0;
  }
  return;
}

/* ---- 0x00477380  stdControl_ShowMouseCursor ---- */
/* Original name stdControl_ShowMouseCursor (the remaster's GrimFandango (Linux): the windowed /
   full-screen mouse cursor call of Main_Shutdown (ShowCursor(1)) in both builds; the remaster's is
   a stub); was Input_ShowCursor. */

void __cdecl stdControl_ShowMouseCursor(int show)

{
  ShowCursor(show);
  return;
}

/* ---- 0x00477390  Input_InitJoysticks ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Up to two joysticks via joyGetDevCaps; six axes each, POV hat flagged */

void __cdecl Input_InitJoysticks(void)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint *puVar4;
  int axis;
  uint a1;
  JoyInfo pos;
  JoyCaps caps;
  
  UINT_009014e8 = 0;
  UINT_00901668 = 0;
  UINT_009014e0 = 0;
  _DAT_009014ec = 0;
  _DAT_0090166c = 0;
  _DAT_009014e4 = 0;
  uVar1 = joyGetNumDevs();
  if (1 < uVar1) {
    uVar1 = 2;
  }
  a1 = 0;
  if (uVar1 != 0) {
    puVar4 = &UINT_009014e0;
    axis = 2;
    do {
      iVar2 = joyGetPos(a1,(int)&pos);
      if (iVar2 == 0) {
        iVar2 = joyGetDevCapsA(a1,(int)&caps,0x194);
        if (iVar2 == 0) {
          (&UINT_009014e8)[a1] = 1;
          uVar3 = caps.dwMaxButtons;
          if (0xd < caps.dwMaxButtons) {
            uVar3 = 0xe;
          }
          (&UINT_00901668)[a1] = uVar3;
          Input_SetAxisRange(axis + -2,caps.dwXMin,caps.dwXMax,0.1f);
          Input_SetAxisRange(axis + -1,caps.dwYMin,caps.dwYMax,0.1f);
          if (((byte)caps.dwCaps & 1) != 0) {
            Input_SetAxisRange(axis,caps.dwZMin,caps.dwZMax,0.1f);
          }
          if (((byte)caps.dwCaps & 2) != 0) {
            Input_SetAxisRange(axis + 1,caps.dwRMin,caps.dwRMax,0.1f);
          }
          if (((byte)caps.dwCaps & 4) != 0) {
            Input_SetAxisRange(axis + 2,caps.dwUMin,caps.dwUMax,0.1f);
          }
          if (((byte)caps.dwCaps & 8) != 0) {
            Input_SetAxisRange(axis + 3,caps.dwVMin,caps.dwVMax,0.1f);
          }
          if (((byte)caps.dwCaps & 0x10) != 0) {
            *puVar4 = 1;
          }
        }
      }
      a1 = a1 + 1;
      axis = axis + 6;
      puVar4 = puVar4 + 1;
    } while (a1 < uVar1);
  }
  return;
}

/* ---- 0x00477530  Input_CreateKeyboard ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void __cdecl Input_CreateKeyboard(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define pvStack_2c (*(void **)(_frame + (0x40 - 0x2c)))
  #define puStack_28 (*(undefined **)(_frame + (0x40 - 0x28)))
  #define pvStack_24 (*(void **)(_frame + (0x40 - 0x24)))
  #define puStack_20 (*(undefined **)(_frame + (0x40 - 0x20)))
  #define ppvStack_1c (*(void ***)(_frame + (0x40 - 0x1c)))
  #define uStack_18 (*(undefined4 *)(_frame + (0x40 - 0x18)))
  
  if (g_pDirectInput != (void *)0x0) {
    uStack_18 = 0;
    ppvStack_1c = &g_pDInputKeyboard;
    puStack_20 = &DAT_004d8350;
    pvStack_24 = g_pDirectInput;
    puStack_28 = (undefined *)0x47754e;
    iVar1 = (**(code_std **)(*(int *)g_pDirectInput + 0xc))();
    if (iVar1 == 0) {
      puStack_28 = &DAT_004d5370;
      pvStack_2c = g_pDInputKeyboard;
      (**(code_std **)(*(int *)g_pDInputKeyboard + 0x2c))();
      pvStack_2c = (void *)0x14;
      puStack_28 = (undefined *)0x10;
      pvStack_24 = (void *)0x0;
      puStack_20 = (undefined *)0x0;
      ppvStack_1c = (void **)0x20;
      (**(code_std **)(*(int *)g_pDInputKeyboard + 0x18))(g_pDInputKeyboard,1,&pvStack_2c);
    }
  }
  return;
}
#undef ppvStack_1c
#undef puStack_20
#undef puStack_28
#undef pvStack_24
#undef pvStack_2c
#undef uStack_18

#endif


/* ---- 0x004775a0  Input_CreateMouse ---- */
/* Mouse axes 12 (x), 13 (y), 14 (wheel) in relative mode */

void __cdecl Input_CreateMouse(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  void *a1;
  undefined4 a2;
  #define uStack_14 (*(undefined4 *)(_frame + (0x30 - 0x14)))
  #define uStack_10 (*(undefined4 *)(_frame + (0x30 - 0x10)))
  #define iStack_c (*(int *)(_frame + (0x30 - 0xc)))
  #define iStack_8 (*(int *)(_frame + (0x30 - 0x8)))
  #define uStack_4 (*(undefined4 *)(_frame + (0x30 - 0x4)))
  
  if (g_pDirectInput != (void *)0x0) {
    GetSystemMetrics(0x2b);
    iVar1 = (**(code_std **)(*(int *)g_pDirectInput + 0xc))
                      (g_pDirectInput,&DAT_004d8340,&g_pDInputMouse,0);
    if (iVar1 == 0) {
      iVar1 = (**(code_std **)(*(int *)g_pDInputMouse + 0x2c))(g_pDInputMouse,&DAT_004d5400);
      if (iVar1 == 0) {
        a2 = 5;
        iVar1 = *(int *)g_pDInputMouse;
        a1 = Win_GetMainHwnd();
        iStack_c = (**(code_std **)(iVar1 + 0x34))(g_pDInputMouse,a1,a2);
        if (iStack_c == 0) {
          uStack_14 = 0x14;
          uStack_10 = 0x10;
          uStack_4 = 0x20;
          iStack_8 = iStack_c;
          (**(code_std **)(*(int *)g_pDInputMouse + 0x18))(g_pDInputMouse,1,&uStack_14);
          Input_SetAxisRange(0xc,-0xfa,0xfa,0.0f);
          Input_SetAxisRange(0xd,-200,200,0.0f);
          Input_SetAxisRange(0xe,-0x14,0x14,0.0f);
        }
      }
    }
  }
  return;
}
#undef iStack_8
#undef iStack_c
#undef uStack_10
#undef uStack_14
#undef uStack_4


/* ---- 0x00477680  Input_MarkAxisUsed ---- */
void __cdecl Input_MarkAxisUsed(uint axis)

{
  uint uVar1;
  
  if ((0xb < axis) && (axis < 0xf)) {
    UINT_004dea40 = 1;
    return;
  }
  if (axis < 0xc) {
    UINT_00805fb8 = 1;
    uVar1 = (uint)(5 < axis);
    (&UINT_00803fc8)[uVar1] = 1;
    switch(axis + uVar1 * -6) {
    case 0:
      (&UINT_00804010)[uVar1] = (&UINT_00804010)[uVar1] | 1;
      return;
    case 1:
      (&UINT_00804010)[uVar1] = (&UINT_00804010)[uVar1] | 2;
      return;
    case 2:
      (&UINT_00804010)[uVar1] = (&UINT_00804010)[uVar1] | 4;
      return;
    case 3:
      (&UINT_00804010)[uVar1] = (&UINT_00804010)[uVar1] | 8;
      return;
    case 4:
      (&UINT_00804010)[uVar1] = (&UINT_00804010)[uVar1] | 0x10;
      return;
    case 5:
      (&UINT_00804010)[uVar1] = (&UINT_00804010)[uVar1] | 0x20;
    }
  }
  return;
}

/* ---- 0x00477730  Input_PollKeyboard ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Buffered DirectInput key events plus the immediate key state; each key has a 7-dword record {?,
   lastDown, down, downTime, upTime, pressCount, doubleTap} */

void __cdecl Input_PollKeyboard(void)

{
  unsigned char _frame[0x330] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint uVar2;
  void *pvVar3;
  uint *puVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  #define puStack_320 (*(undefined1 **)(_frame + (0x330 - 0x320)))
  #define puStack_31c (*(uint **)(_frame + (0x330 - 0x31c)))
  #define iStack_318 (*(int *)(_frame + (0x330 - 0x318)))
  #define local_304 (*(uint *)(_frame + (0x330 - 0x304)))
  #define auStack_214 (*(uint (*)[5])(_frame + (0x330 - 0x214)))
  #define local_200 (*(undefined1 (*)[512])(_frame + (0x330 - 0x200)))
  
  uVar1 = g_dwCurReadTime;
  pvVar3 = g_pDInputKeyboard;
  local_304 = 0x20;
  if ((g_pDInputKeyboard != (void *)0x0) && (UINT_00805fa0 == 0)) {
    puVar4 = &UINT_00804020;
    do {
      puVar4[-1] = uVar1;
      puVar4[-2] = *puVar4;
      puVar4[4] = 0;
      puVar4[3] = 0;
      puVar4 = puVar4 + 7;
    } while (puVar4 < &UINT_00805fa0);
    puStack_31c = &local_304;
    iStack_318 = 0;
    puStack_320 = local_200;
    iVar5 = (**(code_std **)(*(int *)pvVar3 + 0x28))(pvVar3,0x10);
    if (iStack_318 != 0) {
      puVar4 = auStack_214 + 1;
      iVar6 = iStack_318;
      do {
        uVar1 = puVar4[-1];
        uVar7 = *puVar4;
        uVar2 = puVar4[1];
        if (uVar7 == (&UINT_00804020)[uVar1 * 7]) {
          if (uVar7 != 0) {
LAB_0047780b:
            (&UINT_00804028)[uVar1 * 7] = uVar2;
          }
        }
        else {
          if ((uVar7 != 0) && (uVar2 - (&UINT_00804028)[uVar1 * 7] < 200)) {
            (&UINT_00804030)[uVar1 * 7] = 1;
          }
          (&UINT_00804020)[uVar1 * 7] = uVar7;
          (&UINT_00804024)[uVar1 * 7] = uVar2;
          if (uVar7 != 0) {
            (&UINT_0080402c)[uVar1 * 7] = (&UINT_0080402c)[uVar1 * 7] + 1;
            (&g_dwKeyInfo)[uVar1 * 7] = uVar7;
            goto LAB_0047780b;
          }
        }
        puVar4 = puVar4 + 4;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
    if ((iVar5 == 1) &&
       (iVar5 = (**(code_std **)(*(int *)g_pDInputKeyboard + 0x24))
                          (g_pDInputKeyboard,0x100,(_frame + (0x330 - 0x314))), uVar1 = g_dwCurReadTime,
       -1 < iVar5)) {
      iVar5 = 0;
      puVar4 = &UINT_00804020;
      do {
        uVar7 = (uint)*(byte *)((int)&puStack_320 + iVar5);
        if (uVar7 == *puVar4) {
          if (uVar7 != 0) {
LAB_00477881:
            puVar4[2] = uVar1;
          }
        }
        else {
          if ((uVar7 != 0) && (uVar1 - puVar4[2] < 200)) {
            puVar4[4] = 1;
          }
          *puVar4 = uVar7;
          puVar4[1] = uVar1;
          if (uVar7 != 0) {
            puVar4[3] = puVar4[3] + 1;
            puVar4[-2] = uVar7;
            goto LAB_00477881;
          }
        }
        puVar4 = puVar4 + 7;
        iVar5 = iVar5 + 1;
      } while (puVar4 < &UINT_00805c20);
    }
  }
  return;
}
#undef auStack_214
#undef iStack_318
#undef local_200
#undef local_304
#undef puStack_31c
#undef puStack_320

#endif


/* ---- 0x004778a0  Input_FlushKeyboard ---- */
void __cdecl Input_FlushKeyboard(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint *puVar2;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0xffffffff;
  if (g_pDInputKeyboard != (void *)0x0) {
    (**(code_std **)(*(int *)g_pDInputKeyboard + 0x28))(g_pDInputKeyboard,0x10,0,&local_4,0);
    uVar1 = g_dwCurReadTime;
    puVar2 = &UINT_00804020;
    do {
      if (*puVar2 != 0) {
        *puVar2 = 0;
        puVar2[1] = uVar1;
      }
      puVar2 = puVar2 + 7;
    } while (puVar2 < &UINT_00805c20);
  }
  return;
}
#undef local_4


/* ---- 0x004778f0  Input_PollJoysticks ---- */
/* joyGetPosEx per stick; the POV hat is mapped onto four virtual buttons */

void __cdecl Input_PollJoysticks(void)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  JoyInfoEx *pJVar6;
  uint local_44;
  #define local_40 (*(uint *)(_frame + (0x50 - 0x40)))
  #define local_3c (*(uint *)(_frame + (0x50 - 0x3c)))
  #define local_38 (*(uint *)(_frame + (0x50 - 0x38)))
  JoyInfoEx info;
  
  local_40 = 1;
  local_38 = 0;
  local_3c = (uint)&UINT_00804010;
  local_44 = (uint)&UINT_00803fd4;
  uVar5 = 0x1c00;
  do {
    if (((&UINT_00803fc8)[local_38] != 0) && ((&UINT_009014e8)[local_38] != 0)) {
      pJVar6 = &info;
      for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
        pJVar6->dwSize = 0;
        pJVar6 = (JoyInfoEx *)&pJVar6->dwFlags;
      }
      info.dwSize = 0x34;
      info.dwFlags = *(uint *)local_3c;
      iVar3 = joyGetPosEx(local_38,(int)&info);
      if (iVar3 != 0) {
        return;
      }
      *(uint *)(local_44 - 4) = info.dwXPos;
      *(uint *)local_44 = info.dwYPos;
      if ((info.dwFlags & 4) != 0) {
        *(uint *)(local_44 + 4) = info.dwZPos;
      }
      if ((info.dwFlags & 8) != 0) {
        *(uint *)(local_44 + 8) = info.dwRPos;
      }
      if ((info.dwFlags & 0x10) != 0) {
        *(uint *)(local_44 + 0xc) = info.dwUPos;
      }
      if ((info.dwFlags & 0x20) != 0) {
        *(uint *)(local_44 + 0x10) = info.dwVPos;
      }
      uVar1 = g_dwCurReadTime;
      puVar2 = (uint *)((int)&UINT_00804020 + uVar5);
      iVar3 = 10;
      do {
        uVar4 = info.dwButtons & local_40;
        if (uVar4 == *puVar2) {
          if (uVar4 != 0) {
LAB_004779fd:
            puVar2[2] = uVar1;
          }
        }
        else {
          if ((uVar4 != 0) && (uVar1 - puVar2[2] < 200)) {
            puVar2[4] = 1;
          }
          *puVar2 = uVar4;
          puVar2[1] = uVar1;
          if (uVar4 != 0) {
            puVar2[3] = puVar2[3] + 1;
            puVar2[-2] = uVar4;
            goto LAB_004779fd;
          }
        }
        puVar2 = puVar2 + 7;
        local_40 = local_40 << 1;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
      if ((info.dwFlags & 0x200) != 0) {
        if (((int)info.dwPOV < 0x57e4) || (0x7b0c < (int)info.dwPOV)) {
          iVar3 = 0;
        }
        else {
          iVar3 = 1;
        }
        if (iVar3 == *(int *)(uVar5 + ((unsigned)(uintptr_t)&DAT_00804138))) {
          if (iVar3 != 0) {
LAB_00477a8e:
            *(uint *)(uVar5 + ((unsigned)(uintptr_t)&DAT_00804140)) = uVar1;
          }
        }
        else {
          if ((iVar3 != 0) && (uVar1 - *(int *)(uVar5 + ((unsigned)(uintptr_t)&DAT_00804140)) < 200)) {
            *(undefined4 *)(uVar5 + ((unsigned)(uintptr_t)&DAT_00804148)) = 1;
          }
          *(int *)(uVar5 + ((unsigned)(uintptr_t)&DAT_00804138)) = iVar3;
          *(uint *)(uVar5 + ((unsigned)(uintptr_t)&DAT_0080413c)) = uVar1;
          if (iVar3 != 0) {
            *(int *)(uVar5 + ((unsigned)(uintptr_t)&DAT_00804144)) = *(int *)(uVar5 + ((unsigned)(uintptr_t)&DAT_00804144)) + 1;
            *(int *)(uVar5 + ((unsigned)(uintptr_t)&DAT_00804130)) = iVar3;
            goto LAB_00477a8e;
          }
        }
        if (((((int)info.dwPOV < 0x7b0c) && (0x1194 < (int)info.dwPOV)) || ((int)info.dwPOV < 0)) ||
           (info.dwPOV == 0xffff)) {
          iVar3 = 0;
        }
        else {
          iVar3 = 1;
        }
        if (iVar3 == *(int *)(uVar5 + ((unsigned)(uintptr_t)&DAT_00804154))) {
          if (iVar3 != 0) {
LAB_00477b03:
            *(uint *)(uVar5 + ((unsigned)(uintptr_t)&DAT_0080415c)) = uVar1;
          }
        }
        else {
          if ((iVar3 != 0) && (uVar1 - *(int *)(uVar5 + ((unsigned)(uintptr_t)&DAT_0080415c)) < 200)) {
            *(undefined4 *)(uVar5 + ((unsigned)(uintptr_t)&DAT_00804164)) = 1;
          }
          *(int *)(uVar5 + ((unsigned)(uintptr_t)&DAT_00804154)) = iVar3;
          *(uint *)(uVar5 + ((unsigned)(uintptr_t)&DAT_00804158)) = uVar1;
          if (iVar3 != 0) {
            *(int *)(uVar5 + ((unsigned)(uintptr_t)&DAT_00804160)) = *(int *)(uVar5 + ((unsigned)(uintptr_t)&DAT_00804160)) + 1;
            *(int *)(uVar5 + ((unsigned)(uintptr_t)&DAT_0080414c)) = iVar3;
            goto LAB_00477b03;
          }
        }
        if (((int)info.dwPOV < 0x1194) || (0x34bc < (int)info.dwPOV)) {
          iVar3 = 0;
        }
        else {
          iVar3 = 1;
        }
        if (iVar3 == *(int *)(uVar5 + ((unsigned)(uintptr_t)&DAT_00804170))) {
          if (iVar3 != 0) {
LAB_00477b6c:
            *(uint *)(uVar5 + ((unsigned)(uintptr_t)&DAT_00804178)) = uVar1;
          }
        }
        else {
          if ((iVar3 != 0) && (uVar1 - *(int *)(uVar5 + ((unsigned)(uintptr_t)&DAT_00804178)) < 200)) {
            *(undefined4 *)(uVar5 + ((unsigned)(uintptr_t)&DAT_00804180)) = 1;
          }
          *(int *)(uVar5 + ((unsigned)(uintptr_t)&DAT_00804170)) = iVar3;
          *(uint *)(uVar5 + ((unsigned)(uintptr_t)&DAT_00804174)) = uVar1;
          if (iVar3 != 0) {
            *(int *)(uVar5 + ((unsigned)(uintptr_t)&DAT_0080417c)) = *(int *)(uVar5 + ((unsigned)(uintptr_t)&DAT_0080417c)) + 1;
            *(int *)(uVar5 + ((unsigned)(uintptr_t)&DAT_00804168)) = iVar3;
            goto LAB_00477b6c;
          }
        }
        if (((int)info.dwPOV < 0x34bc) || (0x57e4 < (int)info.dwPOV)) {
          iVar3 = 0;
        }
        else {
          iVar3 = 1;
        }
        if (iVar3 == *(int *)(uVar5 + ((unsigned)(uintptr_t)&DAT_0080418c))) {
          if (iVar3 != 0) {
LAB_00477bd5:
            *(uint *)(uVar5 + ((unsigned)(uintptr_t)&DAT_00804194)) = uVar1;
          }
        }
        else {
          if ((iVar3 != 0) && (uVar1 - *(int *)(uVar5 + ((unsigned)(uintptr_t)&DAT_00804194)) < 200)) {
            *(undefined4 *)(uVar5 + ((unsigned)(uintptr_t)&DAT_0080419c)) = 1;
          }
          *(int *)(uVar5 + ((unsigned)(uintptr_t)&DAT_0080418c)) = iVar3;
          *(uint *)(uVar5 + ((unsigned)(uintptr_t)&DAT_00804190)) = uVar1;
          if (iVar3 != 0) {
            *(int *)(uVar5 + ((unsigned)(uintptr_t)&DAT_00804198)) = *(int *)(uVar5 + ((unsigned)(uintptr_t)&DAT_00804198)) + 1;
            *(int *)(uVar5 + ((unsigned)(uintptr_t)&DAT_00804184)) = iVar3;
            goto LAB_00477bd5;
          }
        }
      }
    }
    uVar5 = uVar5 + 0x188;
    local_38 = local_38 + 1;
    local_44 = local_44 + 0x18;
    local_3c = local_3c + 4;
    if (0x1f0f < uVar5) {
      return;
    }
  } while( true );
}
#undef local_38
#undef local_3c
#undef local_40


/* ---- 0x00477c20  Input_PollMouse ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Removing unreachable block (ram,0x00477cd3) */
/* WARNING: Removing unreachable block (ram,0x00477cd5) */
/* WARNING: Removing unreachable block (ram,0x00477cdc) */
/* WARNING: Removing unreachable block (ram,0x00477ce1) */
/* WARNING: Removing unreachable block (ram,0x00477d05) */
/* WARNING: Removing unreachable block (ram,0x00477d09) */
/* WARNING: Removing unreachable block (ram,0x00477d19) */
/* WARNING: Removing unreachable block (ram,0x00477d23) */
/* WARNING: Removing unreachable block (ram,0x00477d33) */
/* WARNING: Removing unreachable block (ram,0x00477cff) */
/* WARNING: Removing unreachable block (ram,0x00477d03) */
/* WARNING: Removing unreachable block (ram,0x00477d46) */
/* WARNING: Removing unreachable block (ram,0x00477d4c) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Ported to C (build/overrides_asm_o2.c): differential test, 0 differences (docs/notes/asm_o2.md).
    */

void __cdecl Input_PollMouse(void)

{
  unsigned char _frame[0x230] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  unsigned char _stkneg[560] __attribute__((aligned(16)));  /* the original frame below the return address */
  uint uVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  uint unaff_EBX;
  uint unaff_EBP;
  #define local_214 (*(uint *)(_frame + (0x230 - 0x214)))
  #define local_210 (*(undefined1 (*)[4])(_frame + (0x230 - 0x210)))
  #define auStack_20c (*(undefined1 (*)[524])(_frame + (0x230 - 0x20c)))
  
  if ((UINT_004dea40 != 0) &&
     (iVar2 = (**(code_std **)(*(int *)g_pDInputMouse + 0x24))(g_pDInputMouse,0x10,local_210),
     iVar2 == 0)) {
    _DAT_00804008 = 0x20;
    _DAT_00804000 = unaff_EBP;
    _DAT_00804004 = unaff_EBX;
    if (UINT_00805fc8 < 0x19) {
      _DAT_00804000 = (int)(UINT_00805fcc + unaff_EBP) >> 1;
      _DAT_00804004 = (int)(UINT_00805fd0 + unaff_EBX) >> 1;
    }
    UINT_00805fcc = unaff_EBP;
    UINT_00805fd0 = unaff_EBX;
    iVar2 = (**(code_std **)(*(int *)g_pDInputMouse + 0x28))
                      (g_pDInputMouse,0x10,auStack_20c,(_stkneg + 16));
    uVar1 = g_dwCurReadTime;
    if (iVar2 == 1) {
      iVar2 = 0;
      puVar3 = &UINT_00805f30;
      do {
        uVar4 = (uint)(byte)auStack_20c[iVar2 + -0x18];
        if (uVar4 == *puVar3) {
          if (uVar4 != 0) {
LAB_00477da3:
            puVar3[2] = uVar1;
          }
        }
        else {
          if ((uVar4 != 0) && (uVar1 - puVar3[2] < 200)) {
            puVar3[4] = 1;
          }
          *puVar3 = uVar4;
          puVar3[1] = uVar1;
          if (uVar4 != 0) {
            puVar3[3] = puVar3[3] + 1;
            puVar3[-2] = uVar4;
            goto LAB_00477da3;
          }
        }
        puVar3 = puVar3 + 7;
        iVar2 = iVar2 + 1;
      } while (puVar3 < &UINT_00805fa0);
    }
  }
  return;
}
#undef auStack_20c
#undef local_210
#undef local_214

#endif


/* ---- 0x00477dc0  Input_FlushJoystick ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Ported to C (build/overrides_asm_o2.c): differential test, 0 differences (docs/notes/asm_o2.md).
    */

void __cdecl Input_FlushJoystick(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  unsigned char _stkneg[48] __attribute__((aligned(16)));  /* the original frame below the return address */
  uint uVar1;
  uint *puVar2;
  uint uVar3;
  int iVar4;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(undefined1 (*)[16])(_frame + (0x30 - 0x10)))
  
  if (UINT_004dea40 != 0) {
    (**(code_std **)(*(int *)g_pDInputMouse + 0x24))(g_pDInputMouse,0x10,local_10);
    (**(code_std **)(*(int *)g_pDInputMouse + 0x28))(g_pDInputMouse,0x10,0,(_stkneg + 16),0);
    uVar1 = g_dwCurReadTime;
    iVar4 = 0;
    puVar2 = &UINT_00805f30;
    do {
      uVar3 = (uint)(byte)local_10[iVar4 + -0x14];
      if (uVar3 == *puVar2) {
        if (uVar3 != 0) {
LAB_00477e51:
          puVar2[2] = uVar1;
        }
      }
      else {
        if ((uVar3 != 0) && (uVar1 - puVar2[2] < 200)) {
          puVar2[4] = 1;
        }
        *puVar2 = uVar3;
        puVar2[1] = uVar1;
        if (uVar3 != 0) {
          puVar2[3] = puVar2[3] + 1;
          puVar2[-2] = uVar3;
          goto LAB_00477e51;
        }
      }
      puVar2 = puVar2 + 7;
      iVar4 = iVar4 + 1;
    } while (puVar2 < &UINT_00805fa0);
  }
  return;
}
#undef local_10
#undef local_14

#endif


/* ---- 0x00477e70  Input_SetAxisRange ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Sets up axis scaling for stdControl_ReadAxis: centre = min + (max-min+1)/2, scale =
   1/(max-centre), integer dead zone = deadZone*(max-centre) (0 if deadZone==0). Joysticks use the
   winmm caps range and deadZone 0.1, so axis values are (raw-centre)/(max-centre), about -1..1,
   zero inside 10%, not rescaled past the dead zone. */

void __cdecl Input_SetAxisRange(int axis,int min,int max,float deadZone)

{
  int iVar1;
  int iVar2;
  float10 fVar3;
  longlong lVar4;
  
  iVar1 = ((max - min) + 1) / 2 + min;
  iVar2 = axis * 0x18;
  (&g_dwStdControl_aAxes)[axis * 6] = (&g_dwStdControl_aAxes)[axis * 6] | 1;
  (&UINT_00901504)[axis * 6] = min;
  *(int *)(&DAT_00901508 + iVar2) = max;
  *(int *)(&DAT_0090150c + iVar2) = iVar1;
  fVar3 = (float10)(max - iVar1);
  *(float *)(&DAT_00901514 + iVar2) = (float)((float10)1.0f / fVar3);
  if (deadZone != 0.0f) {
    lVar4 = FTOL((float10)deadZone * fVar3);
    *(int *)(&DAT_00901510 + iVar2) = (int)lVar4;
    return;
  }
  *(undefined4 *)(&DAT_00901510 + iVar2) = 0;
  return;
}
#endif



/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
typedef struct __attribute__((packed)) { unsigned char b0[20]; void *p14; unsigned char b18[8]; } grim_span_004d5370;
typedef struct __attribute__((packed)) { unsigned char b0[20]; void *p14; } grim_span_004d5400;
typedef struct __attribute__((packed)) { unsigned char b0[20]; void *p14; unsigned char b18[4]; void *p1c; unsigned char b20[4]; void *p24; unsigned char b28[4]; void *p2c; unsigned char b30[4]; void *p34; unsigned char b38[4]; void *p3c; unsigned char b40[4]; void *p44; unsigned char b48[4]; void *p4c; unsigned char b50[4]; void *p54; unsigned char b58[4]; void *p5c; unsigned char b60[4]; void *p64; unsigned char b68[4]; void *p6c; unsigned char b70[4]; void *p74; unsigned char b78[4]; void *p7c; unsigned char b80[4]; void *p84; unsigned char b88[4]; void *p8c; unsigned char b90[4]; void *p94; unsigned char b98[4]; void *p9c; unsigned char ba0[4]; void *pa4; unsigned char ba8[4]; void *pac; unsigned char bb0[4]; void *pb4; unsigned char bb8[4]; void *pbc; unsigned char bc0[4]; void *pc4; unsigned char bc8[4]; void *pcc; unsigned char bd0[4]; void *pd4; unsigned char bd8[4]; void *pdc; unsigned char be0[4]; void *pe4; unsigned char be8[4]; void *pec; unsigned char bf0[4]; void *pf4; unsigned char bf8[4]; void *pfc; unsigned char b100[4]; void *p104; unsigned char b108[4]; void *p10c; unsigned char b110[4]; void *p114; unsigned char b118[4]; void *p11c; } grim_span_004dea48;
extern char grim_def_DAT_004d4370[] __asm__("_DAT_004d4370");
extern grim_span_004d5370 grim_def_DAT_004d5370 __asm__("_DAT_004d5370");
extern char grim_def_DAT_004d5390[] __asm__("_DAT_004d5390");
extern grim_span_004d5400 grim_def_DAT_004d5400 __asm__("_DAT_004d5400");
extern unsigned char grim_def_DAT_004d8340[16] __asm__("_DAT_004d8340");
extern unsigned char grim_def_DAT_004d8350[272] __asm__("_DAT_004d8350");
extern char grim_def_DAT_004deb68[] __asm__("_DAT_004deb68");
extern char grim_def_DAT_004deb7c[] __asm__("_DAT_004deb7c");
extern char grim_def_DAT_004deb90[] __asm__("_DAT_004deb90");
extern char grim_def_DAT_004deba8[] __asm__("_DAT_004deba8");
extern char grim_def_DAT_004debc4[] __asm__("_DAT_004debc4");
extern char grim_def_DAT_004debd8[] __asm__("_DAT_004debd8");
extern char grim_def_DAT_004debec[] __asm__("_DAT_004debec");
extern char grim_def_DAT_004debfc[] __asm__("_DAT_004debfc");
extern char grim_def_DAT_004dec10[] __asm__("_DAT_004dec10");
extern char grim_def_DAT_004dec28[] __asm__("_DAT_004dec28");
extern char grim_def_DAT_004dec3c[] __asm__("_DAT_004dec3c");
extern char grim_def_DAT_004dec4c[] __asm__("_DAT_004dec4c");
extern char grim_def_DAT_004dec60[] __asm__("_DAT_004dec60");
extern char grim_def_DAT_004dec70[] __asm__("_DAT_004dec70");
extern char grim_def_DAT_004dec80[] __asm__("_DAT_004dec80");
extern char grim_def_DAT_004dec98[] __asm__("_DAT_004dec98");
extern char grim_def_DAT_004decac[] __asm__("_DAT_004decac");
extern char grim_def_DAT_004decc8[] __asm__("_DAT_004decc8");
extern char grim_def_DAT_004dece0[] __asm__("_DAT_004dece0");
extern char grim_def_DAT_004decf4[] __asm__("_DAT_004decf4");
extern char grim_def_DAT_004ded08[] __asm__("_DAT_004ded08");
extern char grim_def_DAT_004ded18[] __asm__("_DAT_004ded18");
extern char grim_def_DAT_004ded2c[] __asm__("_DAT_004ded2c");
extern char grim_def_DAT_004ded40[] __asm__("_DAT_004ded40");
extern char grim_def_DAT_004ded58[] __asm__("_DAT_004ded58");
extern char grim_def_DAT_004ded68[] __asm__("_DAT_004ded68");
extern char grim_def_DAT_004ded7c[] __asm__("_DAT_004ded7c");
extern char grim_def_DAT_004ded90[] __asm__("_DAT_004ded90");
extern char grim_def_DAT_004dedb0[] __asm__("_DAT_004dedb0");
extern char grim_def_DAT_004dedcc[] __asm__("_DAT_004dedcc");
extern char grim_def_DAT_004deddc[] __asm__("_DAT_004deddc");
extern char grim_def_DAT_004dedec[] __asm__("_DAT_004dedec");
extern char grim_def_DAT_004dee00[] __asm__("_DAT_004dee00");
extern char grim_def_DAT_004dee10[] __asm__("_DAT_004dee10");
extern unsigned char grim_def_DAT_00803fcc[4] __asm__("_DAT_00803fcc");
extern unsigned char grim_def_DAT_00804000[4] __asm__("_DAT_00804000");
extern unsigned char grim_def_DAT_00804004[4] __asm__("_DAT_00804004");
extern unsigned char grim_def_DAT_00804008[8] __asm__("_DAT_00804008");
extern unsigned char grim_def_DAT_00804014[4] __asm__("_DAT_00804014");
extern unsigned char grim_def_DAT_00804130[8] __asm__("_DAT_00804130");
extern unsigned char grim_def_DAT_00804138[4] __asm__("_DAT_00804138");
extern unsigned char grim_def_DAT_0080413c[4] __asm__("_DAT_0080413c");
extern unsigned char grim_def_DAT_00804140[4] __asm__("_DAT_00804140");
extern unsigned char grim_def_DAT_00804144[4] __asm__("_DAT_00804144");
extern unsigned char grim_def_DAT_00804148[4] __asm__("_DAT_00804148");
extern unsigned char grim_def_DAT_0080414c[8] __asm__("_DAT_0080414c");
extern unsigned char grim_def_DAT_00804154[4] __asm__("_DAT_00804154");
extern unsigned char grim_def_DAT_00804158[4] __asm__("_DAT_00804158");
extern unsigned char grim_def_DAT_0080415c[4] __asm__("_DAT_0080415c");
extern unsigned char grim_def_DAT_00804160[4] __asm__("_DAT_00804160");
extern unsigned char grim_def_DAT_00804164[4] __asm__("_DAT_00804164");
extern unsigned char grim_def_DAT_00804168[8] __asm__("_DAT_00804168");
extern unsigned char grim_def_DAT_00804170[4] __asm__("_DAT_00804170");
extern unsigned char grim_def_DAT_00804174[4] __asm__("_DAT_00804174");
extern unsigned char grim_def_DAT_00804178[4] __asm__("_DAT_00804178");
extern unsigned char grim_def_DAT_0080417c[4] __asm__("_DAT_0080417c");
extern unsigned char grim_def_DAT_00804180[4] __asm__("_DAT_00804180");
extern unsigned char grim_def_DAT_00804184[8] __asm__("_DAT_00804184");
extern unsigned char grim_def_DAT_0080418c[4] __asm__("_DAT_0080418c");
extern unsigned char grim_def_DAT_00804190[4] __asm__("_DAT_00804190");
extern unsigned char grim_def_DAT_00804194[4] __asm__("_DAT_00804194");
extern unsigned char grim_def_DAT_00804198[4] __asm__("_DAT_00804198");
extern unsigned char grim_def_DAT_0080419c[6788] __asm__("_DAT_0080419c");
extern unsigned char grim_def_DAT_009014e4[4] __asm__("_DAT_009014e4");
extern unsigned char grim_def_DAT_009014ec[20] __asm__("_DAT_009014ec");
extern unsigned char grim_def_DAT_00901508[4] __asm__("_DAT_00901508");
extern unsigned char grim_def_DAT_0090150c[4] __asm__("_DAT_0090150c");
extern unsigned char grim_def_DAT_00901510[4] __asm__("_DAT_00901510");
extern unsigned char grim_def_DAT_00901514[340] __asm__("_DAT_00901514");
extern unsigned char grim_def_DAT_0090166c[20] __asm__("_DAT_0090166c");
extern float grim_def_FLOAT_004dea44 __asm__("_FLOAT_004dea44");
extern grim_span_004dea48 grim_def_FLOAT_004dea48 __asm__("_FLOAT_004dea48");
extern unsigned int grim_def_UINT_004dea40 __asm__("_UINT_004dea40");
extern unsigned int grim_def_UINT_00803fc8 __asm__("_UINT_00803fc8");
extern unsigned int grim_def_UINT_00803fd0 __asm__("_UINT_00803fd0");
extern unsigned char grim_def_UINT_00803fd4[44] __asm__("_UINT_00803fd4");
extern unsigned int grim_def_UINT_00804010 __asm__("_UINT_00804010");
extern unsigned int grim_def_UINT_00804020 __asm__("_UINT_00804020");
extern unsigned int grim_def_UINT_00804024 __asm__("_UINT_00804024");
extern unsigned int grim_def_UINT_00804028 __asm__("_UINT_00804028");
extern unsigned int grim_def_UINT_0080402c __asm__("_UINT_0080402c");
extern unsigned char grim_def_UINT_00804030[256] __asm__("_UINT_00804030");
extern unsigned char grim_def_UINT_00805c20[784] __asm__("_UINT_00805c20");
extern unsigned char grim_def_UINT_00805f30[104] __asm__("_UINT_00805f30");
extern unsigned int grim_def_UINT_00805fa0 __asm__("_UINT_00805fa0");
extern unsigned int grim_def_UINT_00805fb8 __asm__("_UINT_00805fb8");
extern unsigned int grim_def_UINT_00805fc8 __asm__("_UINT_00805fc8");
extern unsigned int grim_def_UINT_00805fcc __asm__("_UINT_00805fcc");
extern unsigned int grim_def_UINT_00805fd0 __asm__("_UINT_00805fd0");
extern unsigned int grim_def_UINT_009014e0 __asm__("_UINT_009014e0");
extern unsigned int grim_def_UINT_009014e8 __asm__("_UINT_009014e8");
extern unsigned int grim_def_UINT_00901504 __asm__("_UINT_00901504");
extern unsigned int grim_def_UINT_00901668 __asm__("_UINT_00901668");
extern unsigned int grim_def_g_dwCurReadTime __asm__("_g_dwCurReadTime");
extern unsigned char grim_def_g_dwKeyInfo[8] __asm__("_g_dwKeyInfo");
extern unsigned char grim_def_g_dwLastReadTime[8] __asm__("_g_dwLastReadTime");
extern unsigned int grim_def_g_dwStdControl_aAxes __asm__("_g_dwStdControl_aAxes");
extern unsigned int grim_def_g_dwStdControl_bControlsIdle __asm__("_g_dwStdControl_bControlsIdle");
extern int grim_def_g_nInputAcquired __asm__("_g_nInputAcquired");
extern unsigned char grim_def_g_pDInputKeyboard[4] __asm__("_g_pDInputKeyboard");
extern unsigned char grim_def_g_pDInputMouse[4] __asm__("_g_pDInputMouse");
extern unsigned char grim_def_g_pDirectInput[4] __asm__("_g_pDirectInput");
/* 0x004d8340, 16 bytes */ GRIM_DATA("004d8340") unsigned char grim_def_DAT_004d8340[16] __asm__("_DAT_004d8340") = { 0x60, 0x2b, 0x1d, 0x6f, 0xa0, 0xd5, 0xcf, 0x11, 0xbf, 0xc7, 0x44, 0x45, 0x53, 0x54 };
/* 0x004d8350, 272 bytes */ GRIM_DATA("004d8350") unsigned char grim_def_DAT_004d8350[272] __asm__("_DAT_004d8350") = {
    0x61, 0x2b, 0x1d, 0x6f, 0xa0, 0xd5, 0xcf, 0x11, 0xbf, 0xc7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00,
    0x70, 0x2b, 0x1d, 0x6f, 0xa0, 0xd5, 0xcf, 0x11, 0xbf, 0xc7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00,
    0x20, 0x1c, 0x54, 0x13, 0x33, 0x8e, 0xd0, 0x11, 0x9a, 0xd0, 0x00, 0xa0, 0xc9, 0xa0, 0x6e, 0x35,
    0x21, 0x1c, 0x54, 0x13, 0x33, 0x8e, 0xd0, 0x11, 0x9a, 0xd0, 0x00, 0xa0, 0xc9, 0xa0, 0x6e, 0x35,
    0x22, 0x1c, 0x54, 0x13, 0x33, 0x8e, 0xd0, 0x11, 0x9a, 0xd0, 0x00, 0xa0, 0xc9, 0xa0, 0x6e, 0x35,
    0x23, 0x1c, 0x54, 0x13, 0x33, 0x8e, 0xd0, 0x11, 0x9a, 0xd0, 0x00, 0xa0, 0xc9, 0xa0, 0x6e, 0x35,
    0x24, 0x1c, 0x54, 0x13, 0x33, 0x8e, 0xd0, 0x11, 0x9a, 0xd0, 0x00, 0xa0, 0xc9, 0xa0, 0x6e, 0x35,
    0x25, 0x1c, 0x54, 0x13, 0x33, 0x8e, 0xd0, 0x11, 0x9a, 0xd0, 0x00, 0xa0, 0xc9, 0xa0, 0x6e, 0x35,
    0x26, 0x1c, 0x54, 0x13, 0x33, 0x8e, 0xd0, 0x11, 0x9a, 0xd0, 0x00, 0xa0, 0xc9, 0xa0, 0x6e, 0x35,
    0x27, 0x1c, 0x54, 0x13, 0x33, 0x8e, 0xd0, 0x11, 0x9a, 0xd0, 0x00, 0xa0, 0xc9, 0xa0, 0x6e, 0x35,
    0x28, 0x1c, 0x54, 0x13, 0x33, 0x8e, 0xd0, 0x11, 0x9a, 0xd0, 0x00, 0xa0, 0xc9, 0xa0, 0x6e, 0x35,
    0x29, 0x1c, 0x54, 0x13, 0x33, 0x8e, 0xd0, 0x11, 0x9a, 0xd0, 0x00, 0xa0, 0xc9, 0xa0, 0x6e, 0x35,
    0x2a, 0x1c, 0x54, 0x13, 0x33, 0x8e, 0xd0, 0x11, 0x9a, 0xd0, 0x00, 0xa0, 0xc9, 0xa0, 0x6e, 0x35,
    0x2b, 0x1c, 0x54, 0x13, 0x33, 0x8e, 0xd0, 0x11, 0x9a, 0xd0, 0x00, 0xa0, 0xc9, 0xa0, 0x6e, 0x35,
    0xe0, 0x0e, 0xb7, 0xd7, 0x40, 0x43, 0xcf, 0x11, 0xb0, 0x63, 0x00, 0x20, 0xaf, 0xc2, 0xcd, 0x35,
    0xa0, 0x17, 0x38, 0x59, 0xb3, 0x7d, 0xcf, 0x11, 0xa2, 0xde, 0x00, 0xaa, 0x00, 0xb9, 0x33, 0x56,
    0x80, 0xdb, 0x14, 0x6c, 0x33, 0xa7, 0xce, 0x11, 0xa5, 0x21, 0x00, 0x20, 0xaf, 0x0b, 0xe5, 0x60
};
/* 0x004dea40, 4 bytes */ GRIM_DATA("004dea40") unsigned int grim_def_UINT_004dea40 __asm__("_UINT_004dea40") = 0x1;
/* 0x004dea44, 4 bytes */ GRIM_DATA("004dea44") float grim_def_FLOAT_004dea44 __asm__("_FLOAT_004dea44") = 1.0f;
/* 0x004dea48, 288 bytes */ GRIM_DATA("004dea48") grim_span_004dea48 grim_def_FLOAT_004dea48 __asm__("_FLOAT_004dea48") = {
    { 0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x80, 0x3f },
    (void *)&grim_def_DAT_004dee10,
    { 0x01 },
    (void *)&grim_def_DAT_004dee00,
    { 0x01 },
    (void *)&grim_def_DAT_004dedec,
    { 0x01 },
    (void *)&grim_def_DAT_004deddc,
    { 0x02 },
    (void *)&grim_def_DAT_004dedcc,
    { 0x7e, 0x04, 0x07, 0x80 },
    (void *)&grim_def_DAT_004dedb0,
    { 0x81, 0x04, 0x07, 0x80 },
    (void *)&grim_def_DAT_004ded90,
    { 0x77, 0x00, 0x07, 0x80 },
    (void *)&grim_def_DAT_004ded7c,
    { 0x54, 0x01, 0x04, 0x80 },
    (void *)&grim_def_DAT_004ded68,
    { 0x02, 0x00, 0x07, 0x80 },
    (void *)&grim_def_DAT_004ded58,
    { 0x02, 0x00, 0x07, 0x80 },
    (void *)&grim_def_DAT_004ded40,
    { 0x57, 0x00, 0x07, 0x80 },
    (void *)&grim_def_DAT_004ded2c,
    { 0x02, 0x40, 0x00, 0x80 },
    (void *)&grim_def_DAT_004ded18,
    { 0x05, 0x40, 0x00, 0x80 },
    (void *)&grim_def_DAT_004ded08,
    { 0x0e, 0x00, 0x07, 0x80 },
    (void *)&grim_def_DAT_004decf4,
    { 0x01, 0x40, 0x00, 0x80 },
    (void *)&grim_def_DAT_004dece0,
    { 0x15, 0x00, 0x07, 0x80 },
    (void *)&grim_def_DAT_004decc8,
    { 0xdf, 0x04, 0x07, 0x80 },
    (void *)&grim_def_DAT_004decac,
    { 0x10, 0x01, 0x04, 0x80 },
    (void *)&grim_def_DAT_004dec98,
    { 0x05, 0x00, 0x07, 0x80 },
    (void *)&grim_def_DAT_004dec80,
    { 0x1e, 0x00, 0x07, 0x80 },
    (void *)&grim_def_DAT_004dec70,
    { 0xaa, 0x00, 0x07, 0x80 },
    (void *)&grim_def_DAT_004dec60,
    { 0x0c, 0x00, 0x07, 0x80 },
    (void *)&grim_def_DAT_004dec4c,
    { 0x05, 0x00, 0x07, 0x80 },
    (void *)&grim_def_DAT_004dec3c,
    { 0x05, 0x00, 0x07, 0x80 },
    (void *)&grim_def_DAT_004dec28,
    { 0x00, 0x02, 0x04, 0x80 },
    (void *)&grim_def_DAT_004dec10,
    { 0x01, 0x02, 0x04, 0x80 },
    (void *)&grim_def_DAT_004debfc,
    { 0x02, 0x02, 0x04, 0x80 },
    (void *)&grim_def_DAT_004debec,
    { 0x03, 0x02, 0x04, 0x80 },
    (void *)&grim_def_DAT_004debd8,
    { 0x04, 0x02, 0x04, 0x80 },
    (void *)&grim_def_DAT_004debc4,
    { 0x05, 0x02, 0x04, 0x80 },
    (void *)&grim_def_DAT_004deba8,
    { 0x06, 0x02, 0x04, 0x80 },
    (void *)&grim_def_DAT_004deb90,
    { 0x07, 0x02, 0x04, 0x80 },
    (void *)&grim_def_DAT_004deb7c,
    { 0x08, 0x02, 0x04, 0x80 },
    (void *)&grim_def_DAT_004deb68
};
/* 0x00803fc8, 4 bytes */ GRIM_DATA("00803fc8") unsigned int grim_def_UINT_00803fc8 __asm__("_UINT_00803fc8") = 0x0;
/* 0x00803fcc, 4 bytes */ GRIM_DATA("00803fcc") unsigned char grim_def_DAT_00803fcc[4] __asm__("_DAT_00803fcc") = {0};
/* 0x00803fd0, 4 bytes */ GRIM_DATA("00803fd0") unsigned int grim_def_UINT_00803fd0 __asm__("_UINT_00803fd0") = 0x0;
/* 0x00803fd4, 44 bytes */ GRIM_DATA("00803fd4") unsigned char grim_def_UINT_00803fd4[44] __asm__("_UINT_00803fd4") = {0};
/* 0x00804000, 4 bytes */ GRIM_DATA("00804000") unsigned char grim_def_DAT_00804000[4] __asm__("_DAT_00804000") = {0};
/* 0x00804004, 4 bytes */ GRIM_DATA("00804004") unsigned char grim_def_DAT_00804004[4] __asm__("_DAT_00804004") = {0};
/* 0x00804008, 8 bytes */ GRIM_DATA("00804008") unsigned char grim_def_DAT_00804008[8] __asm__("_DAT_00804008") = {0};
/* 0x00804010, 4 bytes */ GRIM_DATA("00804010") unsigned int grim_def_UINT_00804010 __asm__("_UINT_00804010") = 0x0;
/* 0x00804014, 4 bytes */ GRIM_DATA("00804014") unsigned char grim_def_DAT_00804014[4] __asm__("_DAT_00804014") = {0};
/* 0x00804018, 8 bytes */ GRIM_DATA("00804018") unsigned char grim_def_g_dwKeyInfo[8] __asm__("_g_dwKeyInfo") = {0};
/* 0x00804020, 4 bytes */ GRIM_DATA("00804020") unsigned int grim_def_UINT_00804020 __asm__("_UINT_00804020") = 0x0;
/* 0x00804024, 4 bytes */ GRIM_DATA("00804024") unsigned int grim_def_UINT_00804024 __asm__("_UINT_00804024") = 0x0;
/* 0x00804028, 4 bytes */ GRIM_DATA("00804028") unsigned int grim_def_UINT_00804028 __asm__("_UINT_00804028") = 0x0;
/* 0x0080402c, 4 bytes */ GRIM_DATA("0080402c") unsigned int grim_def_UINT_0080402c __asm__("_UINT_0080402c") = 0x0;
/* 0x00804030, 256 bytes */ GRIM_DATA("00804030") unsigned char grim_def_UINT_00804030[256] __asm__("_UINT_00804030") = {0};
/* 0x00804130, 8 bytes */ GRIM_DATA("00804130") unsigned char grim_def_DAT_00804130[8] __asm__("_DAT_00804130") = {0};
/* 0x00804138, 4 bytes */ GRIM_DATA("00804138") unsigned char grim_def_DAT_00804138[4] __asm__("_DAT_00804138") = {0};
/* 0x0080413c, 4 bytes */ GRIM_DATA("0080413c") unsigned char grim_def_DAT_0080413c[4] __asm__("_DAT_0080413c") = {0};
/* 0x00804140, 4 bytes */ GRIM_DATA("00804140") unsigned char grim_def_DAT_00804140[4] __asm__("_DAT_00804140") = {0};
/* 0x00804144, 4 bytes */ GRIM_DATA("00804144") unsigned char grim_def_DAT_00804144[4] __asm__("_DAT_00804144") = {0};
/* 0x00804148, 4 bytes */ GRIM_DATA("00804148") unsigned char grim_def_DAT_00804148[4] __asm__("_DAT_00804148") = {0};
/* 0x0080414c, 8 bytes */ GRIM_DATA("0080414c") unsigned char grim_def_DAT_0080414c[8] __asm__("_DAT_0080414c") = {0};
/* 0x00804154, 4 bytes */ GRIM_DATA("00804154") unsigned char grim_def_DAT_00804154[4] __asm__("_DAT_00804154") = {0};
/* 0x00804158, 4 bytes */ GRIM_DATA("00804158") unsigned char grim_def_DAT_00804158[4] __asm__("_DAT_00804158") = {0};
/* 0x0080415c, 4 bytes */ GRIM_DATA("0080415c") unsigned char grim_def_DAT_0080415c[4] __asm__("_DAT_0080415c") = {0};
/* 0x00804160, 4 bytes */ GRIM_DATA("00804160") unsigned char grim_def_DAT_00804160[4] __asm__("_DAT_00804160") = {0};
/* 0x00804164, 4 bytes */ GRIM_DATA("00804164") unsigned char grim_def_DAT_00804164[4] __asm__("_DAT_00804164") = {0};
/* 0x00804168, 8 bytes */ GRIM_DATA("00804168") unsigned char grim_def_DAT_00804168[8] __asm__("_DAT_00804168") = {0};
/* 0x00804170, 4 bytes */ GRIM_DATA("00804170") unsigned char grim_def_DAT_00804170[4] __asm__("_DAT_00804170") = {0};
/* 0x00804174, 4 bytes */ GRIM_DATA("00804174") unsigned char grim_def_DAT_00804174[4] __asm__("_DAT_00804174") = {0};
/* 0x00804178, 4 bytes */ GRIM_DATA("00804178") unsigned char grim_def_DAT_00804178[4] __asm__("_DAT_00804178") = {0};
/* 0x0080417c, 4 bytes */ GRIM_DATA("0080417c") unsigned char grim_def_DAT_0080417c[4] __asm__("_DAT_0080417c") = {0};
/* 0x00804180, 4 bytes */ GRIM_DATA("00804180") unsigned char grim_def_DAT_00804180[4] __asm__("_DAT_00804180") = {0};
/* 0x00804184, 8 bytes */ GRIM_DATA("00804184") unsigned char grim_def_DAT_00804184[8] __asm__("_DAT_00804184") = {0};
/* 0x0080418c, 4 bytes */ GRIM_DATA("0080418c") unsigned char grim_def_DAT_0080418c[4] __asm__("_DAT_0080418c") = {0};
/* 0x00804190, 4 bytes */ GRIM_DATA("00804190") unsigned char grim_def_DAT_00804190[4] __asm__("_DAT_00804190") = {0};
/* 0x00804194, 4 bytes */ GRIM_DATA("00804194") unsigned char grim_def_DAT_00804194[4] __asm__("_DAT_00804194") = {0};
/* 0x00804198, 4 bytes */ GRIM_DATA("00804198") unsigned char grim_def_DAT_00804198[4] __asm__("_DAT_00804198") = {0};
/* 0x0080419c, 6788 bytes */ GRIM_DATA("0080419c") unsigned char grim_def_DAT_0080419c[6788] __asm__("_DAT_0080419c") = {0};
/* 0x00805c20, 784 bytes */ GRIM_DATA("00805c20") unsigned char grim_def_UINT_00805c20[784] __asm__("_UINT_00805c20") = {0};
/* 0x00805f30, 104 bytes */ GRIM_DATA("00805f30") unsigned char grim_def_UINT_00805f30[104] __asm__("_UINT_00805f30") = {0};
/* 0x00805fa0, 4 bytes */ GRIM_DATA("00805fa0") unsigned int grim_def_UINT_00805fa0 __asm__("_UINT_00805fa0") = 0x0;
/* 0x00805fa4, 4 bytes */ /* loose */ unsigned int grim_def_g_dwStdControl_bControlsIdle __asm__("_g_dwStdControl_bControlsIdle") = 0x0;
static unsigned char grim_anchor_00805fa8[0] __attribute__((section(".data$grim_00805fa8"), aligned(16), used));
static unsigned char grim_pad_00805fa8[8] __attribute__((section(".data$grim_00805fa8_"), aligned(4), used));
/* 0x00805fa8, 4 bytes */ GRIM_DATA("00805fa8z") int grim_def_g_nInputAcquired __asm__("_g_nInputAcquired") = 0;
/* 0x00805fac, 4 bytes */ GRIM_DATA("00805fac") unsigned char grim_def_g_pDirectInput[4] __asm__("_g_pDirectInput") = {0};
/* 0x00805fb0, 4 bytes */ GRIM_DATA("00805fb0") unsigned char grim_def_g_pDInputMouse[4] __asm__("_g_pDInputMouse") = {0};
/* 0x00805fb4, 4 bytes */ GRIM_DATA("00805fb4") unsigned char grim_def_g_pDInputKeyboard[4] __asm__("_g_pDInputKeyboard") = {0};
/* 0x00805fb8, 4 bytes */ GRIM_DATA("00805fb8") unsigned int grim_def_UINT_00805fb8 __asm__("_UINT_00805fb8") = 0x0;
/* 0x00805fbc, 4 bytes */ /* loose */ unsigned int grim_def_g_dwCurReadTime __asm__("_g_dwCurReadTime") = 0x0;
/* 0x00805fc0, 8 bytes */ /* loose */ unsigned char grim_def_g_dwLastReadTime[8] __asm__("_g_dwLastReadTime") = {0};
/* 0x00805fc8, 4 bytes */ /* loose */ unsigned int grim_def_UINT_00805fc8 __asm__("_UINT_00805fc8") = 0x0;
/* 0x00805fcc, 4 bytes */ /* loose */ unsigned int grim_def_UINT_00805fcc __asm__("_UINT_00805fcc") = 0x0;
/* 0x00805fd0, 4 bytes */ /* loose */ unsigned int grim_def_UINT_00805fd0 __asm__("_UINT_00805fd0") = 0x0;
/* 0x009014e0, 4 bytes */ GRIM_DATA("009014e0") unsigned int grim_def_UINT_009014e0 __asm__("_UINT_009014e0") = 0x0;
/* 0x009014e4, 4 bytes */ GRIM_DATA("009014e4") unsigned char grim_def_DAT_009014e4[4] __asm__("_DAT_009014e4") = {0};
/* 0x009014e8, 4 bytes */ GRIM_DATA("009014e8") unsigned int grim_def_UINT_009014e8 __asm__("_UINT_009014e8") = 0x0;
/* 0x009014ec, 20 bytes */ GRIM_DATA("009014ec") unsigned char grim_def_DAT_009014ec[20] __asm__("_DAT_009014ec") = {0};
/* 0x00901500, 4 bytes */ GRIM_DATA("00901500") unsigned int grim_def_g_dwStdControl_aAxes __asm__("_g_dwStdControl_aAxes") = 0x0;
/* 0x00901504, 4 bytes */ GRIM_DATA("00901504") unsigned int grim_def_UINT_00901504 __asm__("_UINT_00901504") = 0x0;
/* 0x00901508, 4 bytes */ GRIM_DATA("00901508") unsigned char grim_def_DAT_00901508[4] __asm__("_DAT_00901508") = {0};
/* 0x0090150c, 4 bytes */ GRIM_DATA("0090150c") unsigned char grim_def_DAT_0090150c[4] __asm__("_DAT_0090150c") = {0};
/* 0x00901510, 4 bytes */ GRIM_DATA("00901510") unsigned char grim_def_DAT_00901510[4] __asm__("_DAT_00901510") = {0};
/* 0x00901514, 340 bytes */ GRIM_DATA("00901514") unsigned char grim_def_DAT_00901514[340] __asm__("_DAT_00901514") = {0};
/* 0x00901668, 4 bytes */ GRIM_DATA("00901668") unsigned int grim_def_UINT_00901668 __asm__("_UINT_00901668") = 0x0;
/* 0x0090166c, 20 bytes */ GRIM_DATA("0090166c") unsigned char grim_def_DAT_0090166c[20] __asm__("_DAT_0090166c") = {0};
/* 0x004d5370, 32 bytes */ GRIM_DATA("t004d5370") grim_span_004d5370 grim_def_DAT_004d5370 __asm__("_DAT_004d5370") = {
    {
            0x18, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
            0x00, 0x01
    },
    (void *)&grim_def_DAT_004d4370,
    { 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc }
};
/* 0x004d5400, 24 bytes */ GRIM_DATA("t004d5400") grim_span_004d5400 grim_def_DAT_004d5400 __asm__("_DAT_004d5400") = {
    {
            0x18, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
            0x07
    },
    (void *)&grim_def_DAT_004d5390
};
__asm__(".globl _grim_img_exe_0x00804000\n\t.set _grim_img_exe_0x00804000, _DAT_00804000 + 0\n");
__asm__(".globl _grim_img_exe_0x00804020\n\t.set _grim_img_exe_0x00804020, _UINT_00804020 + 0\n");
__asm__(".globl _grim_img_exe_0x00805f30\n\t.set _grim_img_exe_0x00805f30, _UINT_00805f30 + 0\n");
__asm__(".globl _grim_img_exe_0x00805fcc\n\t.set _grim_img_exe_0x00805fcc, _UINT_00805fcc + 0\n");
__asm__(".globl _grim_img_exe_0x00805fd0\n\t.set _grim_img_exe_0x00805fd0, _UINT_00805fd0 + 0\n");
