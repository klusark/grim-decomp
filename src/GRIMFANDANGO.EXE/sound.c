/* GRIMFANDANGO.EXE :: sound.c
 * functions 0x004a3fe0 .. 0x004d0cf0 (7 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004a3fe0  sputRoom_RelocateSounds ---- */
/* Original name sputRoom_RelocateSounds (the remaster's GrimFandango (Linux): aligned call in
   grimlib_MakeCurrentSetup); was PositionedSounds_UpdateAll. */

void __cdecl sputRoom_RelocateSounds(void)

{
  undefined4 *puVar1;
  
  PositionedSounds_DropFinished();
  for (puVar1 = g_pSoundEventList; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
    SetSoundPosition((int)puVar1);
  }
  return;
}

/* ---- 0x004a40a0  sputRoom_SetSoundPosition ---- */
/* Original name sputRoom_SetSoundPosition (the remaster's GrimFandango (Linux): aligned call in
   SoundChanger, sputActor_SayLine, sputLua_SetSoundPosition); was Sound_SetPosition. */

void __cdecl
sputRoom_SetSoundPosition
          (uint param_1,undefined **param_2,uint param_3,uint param_4,uint param_5,uint param_6)

{
  int iVar1;
  undefined *puVar2;
  
  iVar1 = SoundsIsSoundPlaying(param_1);
  if (iVar1 == 0) {
    return;
  }
  puVar2 = PositionedSound_Add(param_1,param_2,param_3,param_4,param_5,param_6);
  SetSoundPosition((int)puVar2);
  return;
}

/* ---- 0x004a4dc0  PositionedSounds_DropFinished ---- */
void __cdecl PositionedSounds_DropFinished(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *item;
  int iVar3;
  
  puVar2 = (undefined4 *)0x0;
  item = g_pSoundEventList;
  while (item != (undefined4 *)0x0) {
    iVar3 = SoundsIsSoundPlaying(item[1]);
    if (iVar3 == 0) {
      puVar1 = (undefined4 *)*item;
      if (item == g_pSoundEventList) {
        g_pSoundEventList = puVar1;
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
  int *piVar1;
  
  PositionedSounds_DropFinished();
  piVar1 = Memory_AllocFixed((int *)g_pSoundPool);
  piVar1[1] = param_1;
  *piVar1 = (int)g_pSoundEventList;
  piVar1[2] = (int)*param_2;
  piVar1[3] = (int)param_2[1];
  piVar1[4] = (int)param_2[2];
  piVar1[5] = param_3;
  piVar1[6] = param_4;
  piVar1[7] = param_5;
  piVar1[8] = param_6;
  g_pSoundEventList = piVar1;
  return (undefined *)piVar1;
}

/* ---- 0x004a4e80  SetSoundPosition ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Moves the volume and pan of one positioned sound (entry: +8..0x10 pos, +0x14 min, +0x18 max,
   +0x1c scale, +0x20 near distance 0.8). d = pos - camera pos (current setup, set+0xac, setup
   stride 300), normalised by Vec3_NormalizeApprox (which returns the rough length). If len - near
   >= 0: volume = ftol((scale - t) * (max - min) / scale + min) with t = len - near, clamped as
   UNSIGNED values to [min, max] (so a negative result comes out as max); param 0x600. Pan =
   ftol((clamp(dot(cameraRight(setup+0x50), d) * set+0x1b00 (1.5), -1, 1) + 1) * 64), at most 127;
   param 0x700. Original name SetSoundPosition (the remaster's GrimFandango (Linux): aligned call in
   sputRoom_RelocateSounds, sputRoom_SetSoundPosition); was PositionedSound_Apply. */

uint __cdecl SetSoundPosition(int param_1)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  void *pvVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  float10 fVar6;
  longlong lVar7;
  float fVar8;
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
    fVar8 = rdVector_Normalize3QuickAcc(&local_c);
    fVar6 = (float10)fVar8 - (float10)*(float *)(param_1 + 0x20);
    if ((float10)0.0 <= fVar6) {
      uVar5 = *(uint *)(param_1 + 0x18);
      uVar4 = *(uint *)(param_1 + 0x14);
      lVar7 = FTOL(((float10)*(float *)(param_1 + 0x1c) - fVar6) *
                    ((float10)(uVar5 - uVar4) / (float10)*(float *)(param_1 + 0x1c)) +
                    (float10)(int)uVar4);
      uVar3 = (uint)lVar7;
      if ((uVar4 <= uVar3) && (uVar4 = uVar3, uVar5 < uVar3)) {
        uVar4 = uVar5;
      }
      SoundsSetParam(*(int *)(param_1 + 4),0x600,uVar4);
    }
    fVar6 = ((float10)*(float *)(iVar1 + 0x38) * (float10)local_4 +
            (float10)*(float *)(iVar1 + 0x34) * (float10)local_8 +
            (float10)*(float *)(iVar1 + 0x30) * (float10)local_c) *
            (float10)*(float *)((int)pvVar2 + 0x1b00);
    if (fVar6 < (float10)-1.0) {
      fVar6 = (float10)-1.0;
    }
    else if ((float10)1.0 < fVar6) {
      fVar6 = (float10)1.0;
    }
    lVar7 = FTOL((fVar6 - (float10)-1.0) * (float10)64.0);
    uVar5 = (uint)lVar7;
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


/* ---- 0x004d0c20  sou_engine_GetRate ---- */
/* Calls entry +0x14 of the installed sound driver vtable Original name sou_engine_GetRate (the
   remaster's GrimFandango (Linux): slot 11 of the "SOUND=insane" service table); was
   Sound_DriverQuery. */

uint __cdecl sou_engine_GetRate(void)

{
  uint uVar1;
  
  if (g_pSoundModule_snddriver_services != (int *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x004d0c29. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (*(code *)g_pSoundModule_snddriver_services[5])();
    return uVar1;
  }
  return 0xffffffff;
}

/* ---- 0x004d0cf0  sou_engine_QueryTime ---- */
/* Converts the byte count of a 0x34-byte voice record to samples depending on its format code
   (halved for 8/16-bit mono formats 1,2,4) Original name sou_engine_QueryTime (the remaster's
   GrimFandango (Linux): aligned call in SmushPlay_GetMovieTime, anm_Render); was
   Sound_VoiceSampleCount. */

int __cdecl sou_engine_QueryTime(int voice)

{
  uint uVar1;
  longlong lVar2;
  
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
  uVar1 = sou_engine_GetRate();
  lVar2 = FTOL((float10)voice / ((float10)(int)uVar1 * (float10)0.001));
  return (int)lVar2;
}
