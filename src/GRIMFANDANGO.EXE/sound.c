/* GRIMFANDANGO.EXE :: sound.c
 * functions 0x004a3fe0 .. 0x004d0cf0 (7 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004a3fe0  PositionedSounds_UpdateAll ---- */
void PositionedSounds_UpdateAll(void)

{
  undefined4 *puVar1;
  
  PositionedSounds_DropFinished();
  for (puVar1 = g_pPositionedSoundList; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1)
  {
    PositionedSound_Apply(puVar1);
  }
  return;
}

/* ---- 0x004a40a0  Sound_SetPosition ---- */
void Sound_SetPosition(uint param_1,undefined **param_2,uint param_3,uint param_4,uint param_5,
                      uint param_6)

{
  int iVar1;
  undefined *puVar2;
  
  iVar1 = SoundsIsSoundPlaying(param_1);
  if (iVar1 == 0) {
    return;
  }
  puVar2 = PositionedSound_Add(param_1,param_2,param_3,param_4,param_5,param_6);
  PositionedSound_Apply(puVar2);
  return;
}

/* ---- 0x004a4dc0  PositionedSounds_DropFinished ---- */
void PositionedSounds_DropFinished(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *item;
  int iVar3;
  
  puVar2 = (undefined4 *)0x0;
  item = g_pPositionedSoundList;
  while (item != (undefined4 *)0x0) {
    iVar3 = SoundsIsSoundPlaying(item[1]);
    if (iVar3 == 0) {
      puVar1 = (undefined4 *)*item;
      if (item == g_pPositionedSoundList) {
        g_pPositionedSoundList = puVar1;
        Pool_Free(item);
        puVar2 = (undefined4 *)0x0;
        item = puVar1;
      }
      else {
        *puVar2 = puVar1;
        Pool_Free(item);
        item = puVar1;
      }
    }
    else {
      puVar2 = item;
      item = (undefined4 *)*item;
    }
  }
  return;
}

/* ---- 0x004a4e20  PositionedSound_Add ---- */
undefined * __cdecl
PositionedSound_Add(uint param_1,undefined **param_2,uint param_3,uint param_4,uint param_5,
                   uint param_6)

{
  undefined4 *puVar1;
  
  PositionedSounds_DropFinished();
  puVar1 = (undefined4 *)Pool_Alloc(g_pPositionedSoundPool);
  puVar1[1] = param_1;
  *puVar1 = g_pPositionedSoundList;
  puVar1[2] = *param_2;
  puVar1[3] = param_2[1];
  puVar1[4] = param_2[2];
  puVar1[5] = param_3;
  puVar1[6] = param_4;
  puVar1[7] = param_5;
  puVar1[8] = param_6;
  g_pPositionedSoundList = puVar1;
  return (undefined *)puVar1;
}

/* ---- 0x004a4e80  PositionedSound_Apply ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Moves the volume and pan of one positioned sound (entry: +8..0x10 pos, +0x14 min, +0x18 max,
   +0x1c scale, +0x20 near distance 0.8). d = pos - camera pos (current setup, set+0xac, setup
   stride 300), normalised by Vec3_NormalizeApprox (which returns the rough length). If len - near
   >= 0: volume = ftol((scale - t) * (max - min) / scale + min) with t = len - near, clamped as
   UNSIGNED values to [min, max] (so a negative result comes out as max); param 0x600. Pan =
   ftol((clamp(dot(cameraRight(setup+0x50), d) * set+0x1b00 (1.5), -1, 1) + 1) * 64), at most 127;
   param 0x700. */

undefined4 PositionedSound_Apply(int param_1)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  void *pvVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 unaff_EBP;
  undefined4 unaff_ESI;
  longlong lVar6;
  float fVar7;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_c (*(float *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x30 - 0x4)))
  
  pvVar2 = sputRoom_GetCurrentRoom();
  if (pvVar2 != (void *)0x0) {
    local_c = *(float *)(param_1 + 8) -
              *(float *)(*(int *)((int)pvVar2 + 0xac) + 0x20 + *(int *)((int)pvVar2 + 0xb4) * 300);
    iVar1 = *(int *)((int)pvVar2 + 0xac) + 0x20 + *(int *)((int)pvVar2 + 0xb4) * 300;
    local_8 = *(float *)(param_1 + 0xc) - *(float *)(iVar1 + 4);
    local_4 = *(float *)(param_1 + 0x10) - *(float *)(iVar1 + 8);
    fVar7 = Vec3_NormalizeApprox(&local_c);
    if (0.0 <= fVar7 - *(float *)(param_1 + 0x20)) {
      uVar5 = *(uint *)(param_1 + 0x18);
      uVar4 = *(uint *)(param_1 + 0x14);
      lVar6 = _ftol((double)CONCAT44(unaff_ESI,unaff_EBP));
      uVar3 = (uint)lVar6;
      if ((uVar4 <= uVar3) && (uVar4 = uVar3, uVar5 < uVar3)) {
        uVar4 = uVar5;
      }
      SoundsSetParam(*(int *)(param_1 + 4),0x600,uVar4);
    }
    lVar6 = _ftol((double)CONCAT44(unaff_ESI,unaff_EBP));
    uVar5 = (uint)lVar6;
    if (0x7f < uVar5) {
      uVar5 = 0x7f;
    }
    SoundsSetParam(*(int *)(param_1 + 4),0x700,uVar5);
    return 1;
  }
  return 0;
}
#undef local_18
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x004d0c20  Sound_DriverQuery ---- */
/* Calls entry +0x14 of the installed sound driver vtable */

undefined4 Sound_DriverQuery(void)

{
  undefined4 uVar1;
  
  if (PTR_008dacf0 != (int *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x004d0c29. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (*(code *)PTR_008dacf0[5])();
    return uVar1;
  }
  return 0xffffffff;
}

/* ---- 0x004d0cf0  Sound_VoiceSampleCount ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Converts the byte count of a 0x34-byte voice record to samples depending on its format code
   (halved for 8/16-bit mono formats 1,2,4) */

int __cdecl Sound_VoiceSampleCount(int voice)

{
  uint uVar1;
  longlong lVar2;
  double x;
  
  uVar1 = (&UINT_008dad84)[voice * 0xd];
  switch((&DAT_008dad6f)[voice * 0x34]) {
  case 0:
    break;
  case 1:
  case 2:
  case 4:
    uVar1 = (int)uVar1 >> 1;
    break;
  case 3:
  case 5:
    uVar1 = (int)uVar1 >> 2;
    break;
  default:
    goto switchD_004d0d15_default;
  }
  voice = uVar1;
switchD_004d0d15_default:
  x = (double)voice;
  Sound_DriverQuery();
  lVar2 = _ftol(x);
  return (int)lVar2;
}
#endif

