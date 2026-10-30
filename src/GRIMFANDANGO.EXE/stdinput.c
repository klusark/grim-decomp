/* GRIMFANDANGO.EXE :: stdinput.c
 * functions 0x00476f10 .. 0x00477e70 (22 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00476f10  Input_Init ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Creates DirectInput, the keyboard and mouse devices and scans the joysticks */

undefined * Input_Init(void)

{
  int iVar1;
  uint *puVar2;
  int a2;
  void **a3;
  int a4;
  
  puVar2 = &UINT_00901500;
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
  a2 = 0x500;
  iVar1 = Win_GetInstance();
  DirectInputCreateA(iVar1,a2,(int)a3,a4);
  Input_CreateKeyboard();
  Input_InitJoysticks();
  Input_CreateMouse();
  Input_ResetState();
  UINT_00805f98 = 1;
  return (undefined *)0x1;
}

/* ---- 0x00476f70  Input_Shutdown ---- */
void Input_Shutdown(void)

{
  if (UINT_00805f98 != 0) {
    UINT_00805f98 = 0;
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

/* ---- 0x00476fc0  Input_Enable ---- */
undefined4 Input_Enable(void)

{
  g_nInputEnabled = 1;
  Input_SetAcquired(1);
  return 1;
}

/* ---- 0x00476fe0  Input_Disable ---- */
undefined4 Input_Disable(void)

{
  if (g_nInputEnabled == 0) {
    return 0;
  }
  Input_SetAcquired(0);
  g_nInputEnabled = 0;
  return 1;
}

/* ---- 0x00477010  Input_Flush ---- */
/* Lua FlushControls: resets keyboard and joystick state */

void Input_Flush(void)

{
  UINT_00805fbc = timeGetTime();
  if (g_pDInputKeyboard != (void *)0x0) {
    Input_FlushKeyboard();
  }
  if (g_pDInputMouse != (void *)0x0) {
    Input_FlushJoystick();
    return;
  }
  return;
}

/* ---- 0x00477040  Input_ResetState ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Input_ResetState(void)

{
  uint *puVar1;
  uint *puVar2;
  
  UINT_004dea40 = 0;
  UINT_00805fb8 = 0;
  UINT_00803fc8 = 0;
  UINT_00804010 = 0x680;
  _DAT_00803fcc = 0;
  _DAT_00804014 = 0x680;
  puVar1 = &UINT_00901500;
  do {
    puVar2 = puVar1 + 6;
    *puVar1 = *puVar1 & 0xfffffffd;
    puVar1 = puVar2;
  } while (puVar2 < &UINT_00901668);
  return;
}

/* ---- 0x00477090  Input_EnableAxis ---- */
/* Axes 0-11 belong to the two joysticks, 12-14 to the mouse */

int __cdecl Input_EnableAxis(uint axis)

{
  if (0xe < axis) {
    return 0;
  }
  if (((&UINT_00901500)[axis * 6] & 1) == 0) {
    return 0;
  }
  (&UINT_00901500)[axis * 6] = (&UINT_00901500)[axis * 6] | 2;
  Input_MarkAxisUsed(axis);
  return 1;
}

/* ---- 0x004770d0  Input_Update ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Once per frame: polls keyboard, joysticks and mouse and records press/release times */

void Input_Update(void)

{
  uint uVar1;
  int iVar2;
  uint *puVar3;
  
  if (g_nInputAcquired != 0) {
    UINT_00805fa4 = 1;
    UINT_00805fbc = timeGetTime();
    uVar1 = UINT_00805fbc - UINT_00805fc0;
    if (uVar1 != 0) {
      _DAT_004dea44 = 1.0 / (float)uVar1;
      puVar3 = &UINT_00803fd0;
      UINT_00805fc8 = uVar1;
      for (iVar2 = 0xf; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = 0;
        puVar3 = puVar3 + 1;
      }
      _DAT_004dea48 = _DAT_004dea44 * 1000.0;
      Input_PollKeyboard();
      if (UINT_00805fb8 != 0) {
        Input_PollJoysticks();
      }
      Input_PollMouse();
      UINT_00805fc0 = UINT_00805fbc;
    }
  }
  return;
}

/* ---- 0x00477160  Input_GetAxis ---- */
float __cdecl Input_GetAxis(int inputId)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  if (g_nInputAcquired == 0) {
    return 0.0;
  }
  iVar5 = inputId * 0x18;
  if (((&UINT_00901500)[inputId * 6] & 2) == 0) {
    return 0.0;
  }
  iVar3 = (&UINT_00803fd0)[inputId] - *(int *)(&DAT_0090150c + iVar5);
  if (iVar3 == 0) {
    return 0.0;
  }
  if ((((&UINT_00901500)[inputId * 6] & 8) == 0) && (*(int *)(&DAT_00901510 + iVar5) != 0)) {
    iVar4 = iVar3;
    if (iVar3 < 0) {
      iVar4 = -iVar3;
    }
    if (iVar4 < *(int *)(&DAT_00901510 + iVar5)) {
      return 0.0;
    }
  }
  fVar1 = (float)iVar3 * *(float *)(&DAT_00901514 + iVar5);
  fVar2 = fVar1;
  if (fVar1 < 0.0) {
    fVar2 = -fVar1;
  }
  if (fVar2 <= 1e-05) {
    fVar1 = 0.0;
  }
  if ((UINT_00805fa4 != 0) && (fVar1 != 0.0)) {
    UINT_00805fa4 = 0;
  }
  return fVar1;
}

/* ---- 0x00477230  Input_GetButtonState ---- */
int __cdecl Input_GetButtonState(int inputId,int *down,int *justPressed)

{
  if ((g_nInputAcquired != 0) && (UINT_00805fa0 == 0)) {
    if ((UINT_00805fa4 != 0) && ((&UINT_00804018)[inputId * 7] != 0)) {
      UINT_00805fa4 = 0;
    }
    if (down != (int *)0x0) {
      *down = (&UINT_0080402c)[inputId * 7];
    }
    if (justPressed != (int *)0x0) {
      *justPressed = (&UINT_00804030)[inputId * 7];
    }
    return (&UINT_00804018)[inputId * 7];
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
  if (g_nInputEnabled != 0) {
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

/* ---- 0x00477380  Input_ShowCursor ---- */
void Input_ShowCursor(int param_1)

{
  ShowCursor(param_1);
  return;
}

/* ---- 0x00477390  Input_InitJoysticks ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Up to two joysticks via joyGetDevCaps; six axes each, POV hat flagged */

void Input_InitJoysticks(void)

{
  unsigned char _frame[0x1c0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint *puVar4;
  int axis;
  uint a1;
  #define local_1a4 (*(undefined1 (*)[16])(_frame + (0x1c0 - 0x1a4)))
  #define local_194 (*(undefined1 (*)[36])(_frame + (0x1c0 - 0x194)))
  #define local_170 (*(uint *)(_frame + (0x1c0 - 0x170)))
  #define local_16c (*(uint *)(_frame + (0x1c0 - 0x16c)))
  #define local_168 (*(uint *)(_frame + (0x1c0 - 0x168)))
  #define local_164 (*(uint *)(_frame + (0x1c0 - 0x164)))
  #define local_160 (*(uint *)(_frame + (0x1c0 - 0x160)))
  #define local_15c (*(uint *)(_frame + (0x1c0 - 0x15c)))
  #define local_14c (*(uint *)(_frame + (0x1c0 - 0x14c)))
  #define local_148 (*(uint *)(_frame + (0x1c0 - 0x148)))
  #define local_144 (*(uint *)(_frame + (0x1c0 - 0x144)))
  #define local_140 (*(uint *)(_frame + (0x1c0 - 0x140)))
  #define local_13c (*(uint *)(_frame + (0x1c0 - 0x13c)))
  #define local_138 (*(uint *)(_frame + (0x1c0 - 0x138)))
  #define local_134 (*(byte *)(_frame + (0x1c0 - 0x134)))
  #define local_128 (*(uint *)(_frame + (0x1c0 - 0x128)))
  
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
      iVar2 = joyGetPos(a1,(int)local_1a4);
      if (iVar2 == 0) {
        iVar2 = joyGetDevCapsA(a1,(int)local_194,0x194);
        if (iVar2 == 0) {
          (&UINT_009014e8)[a1] = 1;
          uVar3 = local_128;
          if (0xd < local_128) {
            uVar3 = 0xe;
          }
          (&UINT_00901668)[a1] = uVar3;
          Input_SetAxisRange(axis + -2,local_170,local_16c,0.1);
          Input_SetAxisRange(axis + -1,local_168,local_164,0.1);
          if ((local_134 & 1) != 0) {
            Input_SetAxisRange(axis,local_160,local_15c,0.1);
          }
          if ((local_134 & 2) != 0) {
            Input_SetAxisRange(axis + 1,local_14c,local_148,0.1);
          }
          if ((local_134 & 4) != 0) {
            Input_SetAxisRange(axis + 2,local_144,local_140,0.1);
          }
          if ((local_134 & 8) != 0) {
            Input_SetAxisRange(axis + 3,local_13c,local_138,0.1);
          }
          if ((local_134 & 0x10) != 0) {
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
#undef local_128
#undef local_134
#undef local_138
#undef local_13c
#undef local_140
#undef local_144
#undef local_148
#undef local_14c
#undef local_15c
#undef local_160
#undef local_164
#undef local_168
#undef local_16c
#undef local_170
#undef local_194
#undef local_1a4


/* ---- 0x00477530  Input_CreateKeyboard ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void Input_CreateKeyboard(void)

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
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Mouse axes 12 (x), 13 (y), 14 (wheel) in relative mode */

void Input_CreateMouse(void)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define uStack_38 (*(undefined4 *)(_frame + (0x50 - 0x38)))
  #define uStack_34 (*(undefined4 *)(_frame + (0x50 - 0x34)))
  #define pvStack_30 (*(void **)(_frame + (0x50 - 0x30)))
  #define puStack_2c (*(undefined **)(_frame + (0x50 - 0x2c)))
  #define pvStack_28 (*(void **)(_frame + (0x50 - 0x28)))
  #define puStack_24 (*(undefined **)(_frame + (0x50 - 0x24)))
  #define ppvStack_20 (*(void ***)(_frame + (0x50 - 0x20)))
  
  if (g_pDirectInput != (void *)0x0) {
    ppvStack_20 = (void **)0x4775b9;
    GetSystemMetrics(0x2b);
    ppvStack_20 = &g_pDInputMouse;
    puStack_24 = &DAT_004d8340;
    pvStack_28 = g_pDirectInput;
    puStack_2c = (undefined *)0x4775d0;
    iVar1 = (**(code_std **)(*(int *)g_pDirectInput + 0xc))();
    if (iVar1 == 0) {
      puStack_2c = &DAT_004d5400;
      pvStack_30 = g_pDInputMouse;
      uStack_34 = 0x4775e8;
      iVar1 = (**(code_std **)(*(int *)g_pDInputMouse + 0x2c))();
      if (iVar1 == 0) {
        uStack_34 = 5;
        iVar1 = *(int *)g_pDInputMouse;
        uStack_38 = 0x4775fe;
        uStack_38 = Win_GetMainHwnd();
        pvStack_30 = (void *)(**(code_std **)(iVar1 + 0x34))(g_pDInputMouse);
        if (pvStack_30 == (void *)0x0) {
          uStack_38 = 0x14;
          uStack_34 = 0x10;
          pvStack_28 = (void *)0x20;
          puStack_2c = pvStack_30;
          (**(code_std **)(*(int *)g_pDInputMouse + 0x18))(g_pDInputMouse,1,&uStack_38);
          Input_SetAxisRange(0xc,-0xfa,0xfa,0.0);
          Input_SetAxisRange(0xd,-200,200,0.0);
          Input_SetAxisRange(0xe,-0x14,0x14,0.0);
        }
      }
    }
  }
  return;
}
#undef ppvStack_20
#undef puStack_24
#undef puStack_2c
#undef pvStack_28
#undef pvStack_30
#undef uStack_34
#undef uStack_38

#endif


/* ---- 0x00477680  Input_MarkAxisUsed ---- */
void Input_MarkAxisUsed(uint param_1)

{
  uint uVar1;
  
  if ((0xb < param_1) && (param_1 < 0xf)) {
    UINT_004dea40 = 1;
    return;
  }
  if (param_1 < 0xc) {
    UINT_00805fb8 = 1;
    uVar1 = (uint)(5 < param_1);
    (&UINT_00803fc8)[uVar1] = 1;
    switch(param_1 + uVar1 * -6) {
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
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Buffered DirectInput key events plus the immediate key state; each key has a 7-dword record {?,
   lastDown, down, downTime, upTime, pressCount, doubleTap} */

void Input_PollKeyboard(void)

{
  unsigned char _frame[0x330] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  unsigned char _stkneg[816] __attribute__((aligned(16)));  /* the original frame below the return address */
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
  
  uVar1 = UINT_00805fbc;
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
            (&UINT_00804018)[uVar1 * 7] = uVar7;
            goto LAB_0047780b;
          }
        }
        puVar4 = puVar4 + 4;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
    if ((iVar5 == 1) &&
       (iVar5 = (**(code_std **)(*(int *)g_pDInputKeyboard + 0x24))
                          (g_pDInputKeyboard,0x100,(_stkneg + 28)), uVar1 = UINT_00805fbc,
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
void Input_FlushKeyboard(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint *puVar2;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0xffffffff;
  if (g_pDInputKeyboard != (void *)0x0) {
    (**(code_std **)(*(int *)g_pDInputKeyboard + 0x28))(g_pDInputKeyboard,0x10,0,&local_4,0);
    uVar1 = UINT_00805fbc;
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

void Input_PollJoysticks(void)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  #define local_44 (*(uint *)(_frame + (0x60 - 0x44)))
  #define local_40 (*(uint *)(_frame + (0x60 - 0x40)))
  #define local_3c (*(uint *)(_frame + (0x60 - 0x3c)))
  #define local_38 (*(uint *)(_frame + (0x60 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x60 - 0x34)))
  #define local_30 (*(uint *)(_frame + (0x60 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x60 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x60 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x60 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x60 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x60 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x60 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x60 - 0x14)))
  #define local_c (*(uint *)(_frame + (0x60 - 0xc)))
  
  local_40 = 1;
  local_38 = 0;
  local_3c = (uint)&UINT_00804010;
  local_44 = (uint)&UINT_00803fd4;
  uVar5 = 0x1c00;
  do {
    if (((&UINT_00803fc8)[local_38] != 0) && ((&UINT_009014e8)[local_38] != 0)) {
      puVar2 = &local_34;
      for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar2 = 0;
        puVar2 = puVar2 + 1;
      }
      local_34 = 0x34;
      local_30 = *(uint *)local_3c;
      iVar3 = joyGetPosEx(local_38,(int)&local_34);
      if (iVar3 != 0) {
        return;
      }
      *(uint *)(local_44 - 4) = local_2c;
      *(uint *)local_44 = local_28;
      if ((local_30 & 4) != 0) {
        *(uint *)(local_44 + 4) = local_24;
      }
      if ((local_30 & 8) != 0) {
        *(uint *)(local_44 + 8) = local_20;
      }
      if ((local_30 & 0x10) != 0) {
        *(uint *)(local_44 + 0xc) = local_1c;
      }
      if ((local_30 & 0x20) != 0) {
        *(uint *)(local_44 + 0x10) = local_18;
      }
      uVar1 = UINT_00805fbc;
      puVar2 = (uint *)((int)&UINT_00804020 + uVar5);
      iVar3 = 10;
      do {
        uVar4 = local_14 & local_40;
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
      if ((local_30 & 0x200) != 0) {
        if (((int)local_c < 0x57e4) || (0x7b0c < (int)local_c)) {
          iVar3 = 0;
        }
        else {
          iVar3 = 1;
        }
        if (iVar3 == *(int *)(uVar5 + IMG_ADDR(0x00804138))) {
          if (iVar3 != 0) {
LAB_00477a8e:
            *(uint *)(uVar5 + IMG_ADDR(0x00804140)) = uVar1;
          }
        }
        else {
          if ((iVar3 != 0) && (uVar1 - *(int *)(uVar5 + IMG_ADDR(0x00804140)) < 200)) {
            *(undefined4 *)(uVar5 + IMG_ADDR(0x00804148)) = 1;
          }
          *(int *)(uVar5 + IMG_ADDR(0x00804138)) = iVar3;
          *(uint *)(uVar5 + IMG_ADDR(0x0080413c)) = uVar1;
          if (iVar3 != 0) {
            *(int *)(uVar5 + IMG_ADDR(0x00804144)) = *(int *)(uVar5 + IMG_ADDR(0x00804144)) + 1;
            *(int *)(uVar5 + IMG_ADDR(0x00804130)) = iVar3;
            goto LAB_00477a8e;
          }
        }
        if (((((int)local_c < 0x7b0c) && (0x1194 < (int)local_c)) || ((int)local_c < 0)) ||
           (local_c == 0xffff)) {
          iVar3 = 0;
        }
        else {
          iVar3 = 1;
        }
        if (iVar3 == *(int *)(uVar5 + IMG_ADDR(0x00804154))) {
          if (iVar3 != 0) {
LAB_00477b03:
            *(uint *)(uVar5 + IMG_ADDR(0x0080415c)) = uVar1;
          }
        }
        else {
          if ((iVar3 != 0) && (uVar1 - *(int *)(uVar5 + IMG_ADDR(0x0080415c)) < 200)) {
            *(undefined4 *)(uVar5 + IMG_ADDR(0x00804164)) = 1;
          }
          *(int *)(uVar5 + IMG_ADDR(0x00804154)) = iVar3;
          *(uint *)(uVar5 + IMG_ADDR(0x00804158)) = uVar1;
          if (iVar3 != 0) {
            *(int *)(uVar5 + IMG_ADDR(0x00804160)) = *(int *)(uVar5 + IMG_ADDR(0x00804160)) + 1;
            *(int *)(uVar5 + IMG_ADDR(0x0080414c)) = iVar3;
            goto LAB_00477b03;
          }
        }
        if (((int)local_c < 0x1194) || (0x34bc < (int)local_c)) {
          iVar3 = 0;
        }
        else {
          iVar3 = 1;
        }
        if (iVar3 == *(int *)(uVar5 + IMG_ADDR(0x00804170))) {
          if (iVar3 != 0) {
LAB_00477b6c:
            *(uint *)(uVar5 + IMG_ADDR(0x00804178)) = uVar1;
          }
        }
        else {
          if ((iVar3 != 0) && (uVar1 - *(int *)(uVar5 + IMG_ADDR(0x00804178)) < 200)) {
            *(undefined4 *)(uVar5 + IMG_ADDR(0x00804180)) = 1;
          }
          *(int *)(uVar5 + IMG_ADDR(0x00804170)) = iVar3;
          *(uint *)(uVar5 + IMG_ADDR(0x00804174)) = uVar1;
          if (iVar3 != 0) {
            *(int *)(uVar5 + IMG_ADDR(0x0080417c)) = *(int *)(uVar5 + IMG_ADDR(0x0080417c)) + 1;
            *(int *)(uVar5 + IMG_ADDR(0x00804168)) = iVar3;
            goto LAB_00477b6c;
          }
        }
        if (((int)local_c < 0x34bc) || (0x57e4 < (int)local_c)) {
          iVar3 = 0;
        }
        else {
          iVar3 = 1;
        }
        if (iVar3 == *(int *)(uVar5 + IMG_ADDR(0x0080418c))) {
          if (iVar3 != 0) {
LAB_00477bd5:
            *(uint *)(uVar5 + IMG_ADDR(0x00804194)) = uVar1;
          }
        }
        else {
          if ((iVar3 != 0) && (uVar1 - *(int *)(uVar5 + IMG_ADDR(0x00804194)) < 200)) {
            *(undefined4 *)(uVar5 + IMG_ADDR(0x0080419c)) = 1;
          }
          *(int *)(uVar5 + IMG_ADDR(0x0080418c)) = iVar3;
          *(uint *)(uVar5 + IMG_ADDR(0x00804190)) = uVar1;
          if (iVar3 != 0) {
            *(int *)(uVar5 + IMG_ADDR(0x00804198)) = *(int *)(uVar5 + IMG_ADDR(0x00804198)) + 1;
            *(int *)(uVar5 + IMG_ADDR(0x00804184)) = iVar3;
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
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_28
#undef local_2c
#undef local_30
#undef local_34
#undef local_38
#undef local_3c
#undef local_40
#undef local_44
#undef local_c


/* ---- 0x00477c20  Input_PollMouse ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
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

void Input_PollMouse(void)

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
    uVar1 = UINT_00805fbc;
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
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void Input_FlushJoystick(void)

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
    uVar1 = UINT_00805fbc;
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
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void __cdecl Input_SetAxisRange(int axis,int min,int max,float deadZone)

{
  int iVar1;
  undefined4 unaff_ESI;
  int iVar2;
  undefined4 unaff_EDI;
  longlong lVar3;
  
  iVar1 = ((max - min) + 1) / 2 + min;
  iVar2 = axis * 0x18;
  (&UINT_00901500)[axis * 6] = (&UINT_00901500)[axis * 6] | 1;
  (&UINT_00901504)[axis * 6] = min;
  *(int *)(&DAT_00901508 + iVar2) = max;
  *(int *)(&DAT_0090150c + iVar2) = iVar1;
  *(float *)(&DAT_00901514 + iVar2) = 1.0 / (float)(max - iVar1);
  if (deadZone != 0.0) {
    lVar3 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    *(int *)(&DAT_00901510 + iVar2) = (int)lVar3;
    return;
  }
  *(undefined4 *)(&DAT_00901510 + iVar2) = 0;
  return;
}
#endif

