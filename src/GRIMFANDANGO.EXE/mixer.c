/* GRIMFANDANGO.EXE :: mixer.c
 * functions 0x004c0ed0 .. 0x004d40d0 (21 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004c0ed0  DSound_Init ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Creates the DirectSound object, sets the cooperative level on the main window and creates the
   primary buffer */

undefined4 DSound_Init(void)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 uVar2;
  #define pvStack_4c (*(void **)(_frame + (0x60 - 0x4c)))
  #define puStack_48 (*(undefined4 **)(_frame + (0x60 - 0x48)))
  #define ppvStack_44 (*(void ***)(_frame + (0x60 - 0x44)))
  #define uStack_40 (*(undefined4 *)(_frame + (0x60 - 0x40)))
  #define uStack_20 (*(undefined4 *)(_frame + (0x60 - 0x20)))
  #define uStack_1c (*(undefined4 *)(_frame + (0x60 - 0x1c)))
  #define uStack_18 (*(undefined4 *)(_frame + (0x60 - 0x18)))
  #define uStack_14 (*(undefined4 *)(_frame + (0x60 - 0x14)))
  #define uStack_10 (*(undefined4 *)(_frame + (0x60 - 0x10)))
  
  if (g_pDirectSound != (void *)0x0) {
    return 0;
  }
  DAT_008d3664 = 0;
  uStack_40 = 0x4c0efa;
  iVar1 = DirectSoundCreate(0,IMG_ADDR(0x008d365c),0);
  if (iVar1 < 0) {
    g_pDirectSound = (void *)0x0;
    return 0;
  }
  uVar2 = Win_GetMainHwnd();
  uStack_40 = 0x4c0f21;
  iVar1 = (**(code_std **)(*(int *)g_pDirectSound + 0x18))();
  if (-1 < iVar1) {
    uStack_20 = 0x14;
    uStack_18 = 0;
    uStack_1c = 0x81;
    uStack_14 = 0;
    uStack_10 = 0;
    if (DAT_008d3664 != 0) {
      uStack_1c = 0x91;
    }
    uStack_40 = 0;
    puStack_48 = &uStack_20;
    ppvStack_44 = &g_pDSoundPrimary;
    pvStack_4c = g_pDirectSound;
    DAT_008d3654 = uVar2;
    iVar1 = (**(code_std **)(*(int *)g_pDirectSound + 0xc))();
    if (iVar1 < 0) {
      g_pDSoundPrimary = (void *)0x0;
      return 1;
    }
    (**(code_std **)(*(int *)g_pDSoundPrimary + 0x18))(g_pDSoundPrimary,&DAT_008d3658);
    iVar1 = 0x5622;
    pvStack_4c = (void *)0x20001;
    puStack_48 = (undefined4 *)0x5622;
    if (DAT_008d3660 != 0) {
      iVar1 = 0x2b11;
      puStack_48 = (undefined4 *)0x2b11;
    }
    ppvStack_44 = (void **)(iVar1 << 2);
    uStack_40 = 0x100004;
    (**(code_std **)(*(int *)g_pDSoundPrimary + 0x38))(g_pDSoundPrimary,&pvStack_4c);
    DSound_SetPrimaryVolume(DAT_004f1000);
    if (DAT_008d3664 != 0) {
      iVar1 = (*(code_std *)**(undefined4 **)g_pDSoundPrimary)
                        (g_pDSoundPrimary,&DAT_004d8510,&PTR_008d3674);
      if (iVar1 < 0) {
        DAT_008d3664 = 0;
        PTR_008d3674 = (int *)0x0;
      }
      else {
        (**(code_std **)(*PTR_008d3674 + 0x2c))(PTR_008d3674,0x3f000000,1);
        (**(code_std **)(*PTR_008d3674 + 0x3c))(PTR_008d3674,0,1);
      }
    }
    (**(code_std **)(*(int *)g_pDSoundPrimary + 0x30))(g_pDSoundPrimary,0,0,0);
    (**(code_std **)(*(int *)g_pDirectSound + 0x18))(g_pDirectSound,uVar2,3);
  }
  return 1;
}
#undef ppvStack_44
#undef puStack_48
#undef pvStack_4c
#undef uStack_10
#undef uStack_14
#undef uStack_18
#undef uStack_1c
#undef uStack_20
#undef uStack_40

#endif


/* ---- 0x004c1090  DSound_Shutdown ---- */
void DSound_Shutdown(void)

{
  if (PTR_008d3674 != (int *)0x0) {
    (**(code_std **)(*PTR_008d3674 + 8))(PTR_008d3674);
    PTR_008d3674 = (int *)0x0;
  }
  if (g_pDSoundPrimary != (void *)0x0) {
    (**(code_std **)(*(int *)g_pDirectSound + 0x18))(g_pDirectSound,DAT_008d3654,2);
    (**(code_std **)(*(int *)g_pDSoundPrimary + 0x3c))(g_pDSoundPrimary,DAT_008d3658);
    (**(code_std **)(*(int *)g_pDSoundPrimary + 8))(g_pDSoundPrimary);
    g_pDSoundPrimary = (void *)0x0;
  }
  if (g_pDirectSound != (void *)0x0) {
    (**(code_std **)(*(int *)g_pDirectSound + 8))(g_pDirectSound);
    g_pDirectSound = (void *)0x0;
  }
  return;
}

/* ---- 0x004c1110  DSound_SetPrimaryVolume ---- */
/* IDirectSoundBuffer::SetVolume on the primary buffer under priority cooperative level */

void __cdecl DSound_SetPrimaryVolume(int volume)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  
  if (g_pDSoundPrimary != (void *)0x0) {
    uVar1 = _ftol();
    uVar2 = Win_GetMainHwnd();
    iVar3 = (**(code_std **)(*(int *)g_pDirectSound + 0x18))(g_pDirectSound,uVar2,2);
    if (-1 < iVar3) {
      (**(code_std **)(*(int *)g_pDSoundPrimary + 0x3c))(g_pDSoundPrimary,uVar1);
      (**(code_std **)(*(int *)g_pDirectSound + 0x18))(g_pDirectSound,uVar2,3);
    }
  }
  return;
}

/* ---- 0x004cddf0  Mixer_TimerThread ---- */
/* Software sound mixer thread: wakes every 16 ms (timeGetTime) while g_nMixerRunning and refills
   the DirectSound stream buffer */

undefined4 __stdcall Mixer_TimerThread(int a1)

{
  int a1_00;
  int iVar1;
  
  a1_00 = CreateEventA(0,1,0,0);
  DAT_008da864 = timeGetTime();
  while (DAT_008da874 != 0) {
    iVar1 = timeGetTime();
    if (iVar1 - DAT_008da864 < 0x11) {
      iVar1 = 0x10 - (iVar1 - DAT_008da864);
    }
    else {
      DAT_008da864 = DAT_008da864 + 0x10;
      Mixer_Update();
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
  return 0;
}

/* ---- 0x004ce060  Mixer_Update ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Advances the mixer clock and mixes every active voice into the accumulator */

void Mixer_Update(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  DAT_008da5c8 = DAT_008da5c8 + DAT_008da860;
  if (DAT_008da878 == 0) {
    iVar4 = 1;
    _DAT_008da86c = 1;
    DAT_008da870 = DAT_008da868;
    DAT_008da868 = 0;
    piVar3 = &DAT_008da60c;
    do {
      iVar2 = DAT_008da860;
      if (piVar3[-5] != 0) {
        *piVar3 = *piVar3 + DAT_008da860;
        piVar3[2] = piVar3[2] + iVar2;
        if (((((byte)piVar3[-3] & 5) == 1) && (iVar2 = piVar3[-4], iVar2 != 0)) &&
           (iVar1 = *piVar3, iVar2 <= iVar1)) {
          do {
            *piVar3 = iVar1 - iVar2;
            if ((*(byte *)(piVar3 + -3) & 2) != 0) {
              piVar3[-4] = 0;
              (*(code_std *)piVar3[-5])(iVar4,piVar3[-2]);
              break;
            }
            (*(code_std *)piVar3[-5])(iVar4,piVar3[-2]);
            iVar1 = *piVar3;
            iVar2 = piVar3[-4];
          } while (iVar2 <= iVar1);
        }
      }
      piVar3 = piVar3 + 8;
      iVar4 = iVar4 + 1;
    } while ((int)piVar3 < IMG_ADDR(0x008da86c));
    iVar4 = 1;
    piVar3 = &DAT_008da60c;
    do {
      if (((piVar3[-5] != 0) && ((*(byte *)(piVar3 + -3) & 5) == 0)) &&
         ((piVar3[-4] != 0 && (piVar3[-1] == 0)))) {
        piVar3[-1] = 1;
        iVar2 = *piVar3;
        iVar1 = piVar3[-4];
        if (iVar1 <= iVar2) {
          do {
            *piVar3 = iVar2 - iVar1;
            if ((*(byte *)(piVar3 + -3) & 2) != 0) {
              piVar3[-4] = 0;
              (*(code_std *)piVar3[-5])(iVar4,piVar3[-2]);
              break;
            }
            (*(code_std *)piVar3[-5])(iVar4,piVar3[-2]);
            iVar2 = *piVar3;
            iVar1 = piVar3[-4];
          } while (iVar1 <= iVar2);
        }
        piVar3[-1] = 0;
      }
      piVar3 = piVar3 + 8;
      iVar4 = iVar4 + 1;
    } while ((int)piVar3 < IMG_ADDR(0x008da86c));
    DAT_008da868 = DAT_008da870;
    _DAT_008da86c = 0;
    if ((DAT_008da880 == 0) && (DAT_008da87c == 0)) {
      DAT_008da880 = 1;
      Mixer_ServiceVoices();
      DAT_008da880 = 0;
    }
  }
  return;
}

/* ---- 0x004ce1d0  Mixer_ServiceVoices ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* setjmp-protected per-tick voice servicing */

void Mixer_ServiceVoices(void)

{
  int iVar1;
  
  if ((DAT_008da88c == 0) || (DAT_008da88c = DAT_008da88c + -1, DAT_008da88c == 0)) {
    iVar1 = ((code *)_setjmp3)(&DAT_008da548,0);
    if (iVar1 == 0) {
      if (DAT_008da884 != 0) {
        DAT_008da884 = 0;
        _DAT_008da888 = 1;
        ((code *)_except_handler3)(&DAT_008da588,1);
      }
      DAT_008da884 = 0;
      _DAT_008da888 = 1;
      Mixer_ScheduleVoices();
      _DAT_008da888 = 0;
      _DAT_008da5d0 = DAT_008da5d4;
      ((code *)_except_handler3)(&DAT_008da548,2);
    }
    DAT_008da868 = 0;
  }
  return;
}

/* ---- 0x004ce260  Mixer_ScheduleVoices ---- */
void Mixer_ScheduleVoices(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  iVar4 = 1;
  piVar3 = &DAT_008da60c;
  do {
    piVar3[1] = 1;
    if ((((piVar3[-5] != 0) && (((byte)piVar3[-3] & 5) == 4)) && (iVar2 = piVar3[-4], iVar2 != 0))
       && (iVar1 = *piVar3, iVar2 <= iVar1)) {
      do {
        *piVar3 = iVar1 - iVar2;
        if ((*(byte *)(piVar3 + -3) & 2) != 0) {
          piVar3[-4] = 0;
          (*(code_std *)piVar3[-5])(iVar4,piVar3[-2]);
          break;
        }
        (*(code_std *)piVar3[-5])(iVar4,piVar3[-2]);
        iVar1 = *piVar3;
        iVar2 = piVar3[-4];
      } while (iVar2 <= iVar1);
    }
    piVar3[1] = 0;
    piVar3 = piVar3 + 8;
    iVar4 = iVar4 + 1;
    if (IMG_ADDR(0x008da86b) < (int)piVar3) {
      return;
    }
  } while( true );
}

/* ---- 0x004d27d0  DSound_FillStreamBuffer ---- */
/* Locks the next 0x1800-byte block(s) of the streaming buffer behind the play cursor and fills them
   from the mixer */

void DSound_FillStreamBuffer(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(undefined4 **)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(undefined4 **)(_frame + (0x20 - 0x4)))
  
  iVar1 = DSound_GetPlayBlock();
  if (iVar1 != -1) {
    if (iVar1 != (DAT_004f3f94 + 1) % DAT_008db420) {
      if (DAT_004f3f94 < 0) {
        DAT_004f3f94 = iVar1;
      }
      DAT_004f3f94 = (DAT_004f3f94 + 1) % DAT_008db420;
      iVar1 = (**(code_std **)(*PTR_008dcc48 + 0x2c))
                        (PTR_008dcc48,DAT_004f3f94 * 0x1800,0x1800,&local_4,&local_8,&local_c,
                         &local_10,0);
      if (iVar1 == 0) {
        if ((local_c == (undefined4 *)0x0) || (local_10 == 0)) {
          iVar1 = (int)(local_8 + ((int)local_8 >> 0x1f & 3U)) >> 2;
          puVar3 = local_4;
        }
        else {
          iVar1 = 0x600;
          puVar3 = &DAT_008db438;
        }
        ((code *)Mixer_ClearAccumulator)(iVar1);
        (*DAT_008db410)(iVar1,FUN_004d2d90);
        Mixer_Output(puVar3,iVar1);
        if ((local_c != (undefined4 *)0x0) && (local_10 != 0)) {
          puVar3 = &DAT_008db438;
          puVar4 = local_4;
          for (uVar2 = local_8 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
            *puVar4 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar4 = puVar4 + 1;
          }
          for (uVar2 = local_8 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
            *(undefined1 *)puVar4 = *(undefined1 *)puVar3;
            puVar3 = (undefined4 *)((int)puVar3 + 1);
            puVar4 = (undefined4 *)((int)puVar4 + 1);
          }
          puVar3 = (undefined4 *)((int)&DAT_008db438 + local_8);
          puVar4 = local_c;
          for (uVar2 = local_10 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
            *puVar4 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar4 = puVar4 + 1;
          }
          for (uVar2 = local_10 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
            *(undefined1 *)puVar4 = *(undefined1 *)puVar3;
            puVar3 = (undefined4 *)((int)puVar3 + 1);
            puVar4 = (undefined4 *)((int)puVar4 + 1);
          }
        }
        (**(code_std **)(*PTR_008dcc48 + 0x4c))(PTR_008dcc48,local_4,local_8,local_c,local_10);
      }
    }
  }
  (*(code_std *)PTR_008db424[4])
            (DAT_008dcc54,
             (int)(0x1234dc /
                  (longlong)((int)(DAT_004f3f98 + (DAT_004f3f98 >> 0x1f & 0x3ffU)) >> 10)));
  return;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004d2c60  DSound_GetPlayBlock ---- */
/* IDirectSoundBuffer::GetCurrentPosition / 0x1800 modulo the block count */

int DSound_GetPlayBlock(void)

{
  int iVar1;
  
  if (PTR_008dcc48 != (int *)0x0) {
    iVar1 = (**(code_std **)(*PTR_008dcc48 + 0x10))(PTR_008dcc48,&DAT_008db428,&DAT_008db418);
    if (iVar1 == 0) {
      return (DAT_008db428 / 0x1800) % DAT_008db420;
    }
  }
  return -1;
}

/* ---- 0x004d2e60  Mixer_Output ---- */
void Mixer_Output(undefined4 param_1,undefined4 param_2)

{
  Mixer_ConvertTo16(param_1,param_2);
  return;
}

/* ---- 0x004d3010  Mixer_ClearAccumulator ---- */
/* Zeroes the 32-bit mix accumulator at g_pMixAccum */

undefined4 Mixer_ClearAccumulator(void)

{
  uint uVar1;
  uint uVar2;
  int *piVar3;
  
  uVar2 = DAT_008dcd9c;
  piVar3 = g_pMixAccum;
  for (uVar1 = DAT_008dcd9c >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
    *piVar3 = 0;
    piVar3 = piVar3 + 1;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *(undefined1 *)piVar3 = 0;
    piVar3 = (int *)((int)piVar3 + 1);
  }
  return 0;
}

/* ---- 0x004d3040  Mixer_MixVoice ---- */
/* Dispatches to the Mixer_Mix* resamplers by sample format, channel count and volume mode */

void Mixer_MixVoice(byte *param_1,int param_2,int param_3,int param_4,uint param_5,int param_6,
                   int param_7,int param_8,int param_9,int param_10)

{
  int iVar1;
  uint uVar2;
  uint volL;
  
  if (((g_pMixAccum != (int *)0x0) && (param_1 != (byte *)0x0)) && (param_2 != 0)) {
    if (param_4 == 1) {
      uVar2 = param_7 >> 3;
      if (param_7 != 0) {
        uVar2 = uVar2 + 1;
      }
      if (0x10 < uVar2) {
        uVar2 = 0x10;
      }
      iVar1 = (param_8 >> 3) + -8;
      if (0x40 < param_8) {
        iVar1 = (param_8 >> 3) + -7;
      }
      volL = (uint)(byte)(&DAT_008dcc78)[uVar2 * 0x11 - iVar1];
      uVar2 = (uint)(byte)(&DAT_008dcc78)[uVar2 * 0x11 + iVar1];
      if (param_3 == 8) {
        Mixer_Mix8MonoLR(param_1,param_2,param_5,param_6,volL,uVar2);
        return;
      }
      if (param_9 == 0) {
        Mixer_MixStereoLR_A(param_1,param_2,param_5,param_6,volL,uVar2);
        return;
      }
      if (param_10 != 0) {
        ((code *)Mixer_MixStereoLR_B)(param_1,param_2,param_5,param_6);
        return;
      }
      Mixer_Mix16MonoLR(param_1,param_2,param_5,param_6,volL,uVar2);
      return;
    }
    if (param_3 == 8) {
      Mixer_Mix8Mono(param_1,param_2,param_5,param_6,param_7 + 1);
      return;
    }
    if (param_9 == 0) {
      Mixer_MixStereo_A(param_1,param_2,param_5,param_6,param_7 + 1);
      return;
    }
    if (param_10 != 0) {
      Mixer_MixStereo_B(param_1,param_2,param_5,param_6,param_7 + 1);
      return;
    }
    Mixer_Mix16Mono(param_1,param_2,param_5,param_6,param_7 + 1);
  }
  return;
}

/* ---- 0x004d31d0  Mixer_ConvertTo16 ---- */
/* Accumulator >> 7 clamped to 16 bits into the output block */

undefined4 Mixer_ConvertTo16(undefined2 *param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  if (((g_pMixAccum != (int *)0x0) && (param_1 != (undefined2 *)0x0)) && (param_2 != 0)) {
    piVar1 = g_pMixAccum;
    if (DAT_008dcc60 == 2) {
      param_2 = param_2 << 1;
    }
    for (; param_2 != 0; param_2 = param_2 + -1) {
      iVar2 = *piVar1 >> 7;
      if (iVar2 < -0x8000) {
        iVar2 = -0x8000;
      }
      if (0x7fff < iVar2) {
        iVar2 = 0x7fff;
      }
      *param_1 = (short)iVar2;
      param_1 = param_1 + 1;
      piVar1 = piVar1 + 1;
    }
    return 0;
  }
  return 0xffffffff;
}

/* ---- 0x004d3240  Mixer_Mix8MonoLR ---- */
/* Resampling mix of unsigned 8-bit mono samples with separate left/right volumes */

void __cdecl Mixer_Mix8MonoLR(byte *src,int count,uint rateFrac,int accumOffset,int volL,int volR)

{
  byte *pbVar1;
  byte bVar2;
  uint uVar3;
  int *piVar4;
  uint uVar5;
  
  piVar4 = g_pMixAccum + accumOffset * 2;
  uVar3 = (uint)(count << 0x10) / rateFrac;
  if (uVar3 == 0x8000) {
    while (count = count + -1, count != 0) {
      *piVar4 = *piVar4 + (*src ^ 0x80) * 0x100 * volL;
      piVar4[1] = piVar4[1] + (*src ^ 0x80) * 0x100 * volR;
      piVar4[2] = piVar4[2] + (((uint)*src + (uint)src[2]) * 0x80 ^ 0x8000) * volL;
      bVar2 = *src;
      pbVar1 = src + 2;
      src = src + 1;
      piVar4[3] = piVar4[3] + (((uint)bVar2 + (uint)*pbVar1) * 0x80 ^ 0x8000) * volR;
      piVar4 = piVar4 + 4;
    }
    *piVar4 = *piVar4 + (*src ^ 0x80) * 0x100 * volL;
    piVar4[1] = piVar4[1] + (*src ^ 0x80) * 0x100 * volR;
    piVar4[2] = piVar4[2] + (*src ^ 0x80) * 0x100 * volL;
    piVar4[3] = piVar4[3] + (*src ^ 0x80) * 0x100 * volR;
  }
  else if (uVar3 == 0x10000) {
    if (rateFrac != 0) {
      do {
        *piVar4 = *piVar4 + (*src ^ 0x80) * 0x100 * volL;
        bVar2 = *src;
        src = src + 1;
        piVar4[1] = piVar4[1] + (bVar2 ^ 0x80) * 0x100 * volR;
        rateFrac = rateFrac - 1;
        piVar4 = piVar4 + 2;
      } while (rateFrac != 0);
      return;
    }
  }
  else if (uVar3 == 0x20000) {
    if (rateFrac != 0) {
      do {
        *piVar4 = *piVar4 + (*src ^ 0x80) * 0x100 * volL;
        bVar2 = *src;
        src = src + 2;
        piVar4[1] = piVar4[1] + (bVar2 ^ 0x80) * 0x100 * volR;
        rateFrac = rateFrac - 1;
        piVar4 = piVar4 + 2;
      } while (rateFrac != 0);
      return;
    }
  }
  else {
    uVar5 = 0;
    if (rateFrac != 0) {
      do {
        *piVar4 = *piVar4 + (*src ^ 0x80) * 0x100 * volL;
        piVar4[1] = piVar4[1] + (*src ^ 0x80) * 0x100 * volR;
        src = src + ((int)(uVar5 + uVar3) >> 0x10);
        uVar5 = uVar5 + uVar3 & 0xffff;
        rateFrac = rateFrac - 1;
        piVar4 = piVar4 + 2;
      } while (rateFrac != 0);
      return;
    }
  }
  return;
}

/* ---- 0x004d34a0  Mixer_Mix8Mono ---- */
void Mixer_Mix8Mono(byte *param_1,int param_2,uint param_3,int param_4,int param_5)

{
  byte bVar1;
  uint uVar2;
  byte *pbVar3;
  byte *pbVar4;
  int *piVar5;
  uint uVar6;
  int iVar7;
  
  piVar5 = g_pMixAccum + param_4 * 2;
  uVar2 = (uint)(param_2 << 0x10) / param_3;
  if (uVar2 == 0x8000) {
    while (param_2 = param_2 + -1, param_2 != 0) {
      *piVar5 = *piVar5 + (*param_1 ^ 0x80) * 0x100 * param_5;
      piVar5[1] = piVar5[1] + (param_1[1] ^ 0x80) * 0x100 * param_5;
      pbVar4 = param_1 + 1;
      piVar5[2] = piVar5[2] + (((uint)param_1[2] + (uint)*param_1) * 0x80 ^ 0x8000) * param_5;
      pbVar3 = param_1 + 3;
      param_1 = param_1 + 2;
      piVar5[3] = piVar5[3] + (((uint)*pbVar3 + (uint)*pbVar4) * 0x80 ^ 0x8000) * param_5;
      piVar5 = piVar5 + 4;
    }
    *piVar5 = *piVar5 + (*param_1 ^ 0x80) * 0x100 * param_5;
    piVar5[1] = piVar5[1] + (param_1[1] ^ 0x80) * 0x100 * param_5;
    piVar5[2] = piVar5[2] + (*param_1 ^ 0x80) * 0x100 * param_5;
    piVar5[3] = piVar5[3] + (param_1[1] ^ 0x80) * 0x100 * param_5;
  }
  else if (uVar2 == 0x10000) {
    iVar7 = param_3 * 2;
    if (iVar7 != 0) {
      do {
        bVar1 = *param_1;
        param_1 = param_1 + 1;
        *piVar5 = *piVar5 + (bVar1 ^ 0x80) * 0x100 * param_5;
        iVar7 = iVar7 + -1;
        piVar5 = piVar5 + 1;
      } while (iVar7 != 0);
      return;
    }
  }
  else if (uVar2 == 0x20000) {
    if (param_3 != 0) {
      do {
        pbVar3 = param_1 + 1;
        *piVar5 = *piVar5 + (*param_1 ^ 0x80) * 0x100 * param_5;
        param_1 = param_1 + 4;
        param_3 = param_3 - 1;
        piVar5[1] = piVar5[1] + (*pbVar3 ^ 0x80) * 0x100 * param_5;
        piVar5 = piVar5 + 2;
      } while (param_3 != 0);
      return;
    }
  }
  else {
    uVar6 = 0;
    if (param_3 != 0) {
      do {
        uVar6 = uVar6 + uVar2 * 2;
        *piVar5 = *piVar5 + (*param_1 ^ 0x80) * 0x100 * param_5;
        piVar5[1] = piVar5[1] + (param_1[1] ^ 0x80) * 0x100 * param_5;
        param_1 = param_1 + ((int)uVar6 >> 0x10);
        uVar6 = uVar6 & 0xffff;
        param_3 = param_3 - 1;
        piVar5 = piVar5 + 2;
      } while (param_3 != 0);
      return;
    }
  }
  return;
}

/* ---- 0x004d36e0  Mixer_Mix16MonoLR ---- */
void Mixer_Mix16MonoLR(short *param_1,int param_2,uint param_3,int param_4,int param_5,int param_6)

{
  uint uVar1;
  int *piVar2;
  uint uVar3;
  uint uVar4;
  
  piVar2 = g_pMixAccum + param_4 * 2;
  uVar1 = (uint)(param_2 << 0x10) / param_3;
  if (uVar1 == 0x8000) {
    while (param_2 = param_2 + -1, param_2 != 0) {
      *piVar2 = *piVar2 + *param_1 * param_5;
      piVar2[1] = piVar2[1] + *param_1 * param_6;
      piVar2[2] = piVar2[2] + ((int)*param_1 + (int)param_1[2] >> 1) * param_5;
      piVar2[3] = piVar2[3] + ((int)*param_1 + (int)param_1[2] >> 1) * param_6;
      piVar2 = piVar2 + 4;
      param_1 = param_1 + 1;
    }
    *piVar2 = *piVar2 + *param_1 * param_5;
    piVar2[1] = piVar2[1] + *param_1 * param_6;
    piVar2[2] = piVar2[2] + *param_1 * param_5;
    piVar2[3] = piVar2[3] + *param_1 * param_6;
  }
  else if (uVar1 == 0x10000) {
    if (param_3 != 0) {
      do {
        *piVar2 = *piVar2 + *param_1 * param_5;
        piVar2[1] = piVar2[1] + *param_1 * param_6;
        piVar2 = piVar2 + 2;
        param_3 = param_3 - 1;
        param_1 = param_1 + 1;
      } while (param_3 != 0);
      return;
    }
  }
  else if (uVar1 == 0x20000) {
    if (param_3 != 0) {
      do {
        *piVar2 = *piVar2 + *param_1 * param_5;
        piVar2[1] = piVar2[1] + *param_1 * param_6;
        piVar2 = piVar2 + 2;
        param_3 = param_3 - 1;
        param_1 = param_1 + 2;
      } while (param_3 != 0);
      return;
    }
  }
  else {
    uVar3 = 0;
    if (param_3 != 0) {
      do {
        *piVar2 = *piVar2 + *param_1 * param_5;
        piVar2[1] = piVar2[1] + *param_1 * param_6;
        uVar4 = uVar3 + uVar1;
        piVar2 = piVar2 + 2;
        uVar3 = uVar4 & 0xffff;
        param_3 = param_3 - 1;
        param_1 = param_1 + ((int)uVar4 >> 0x10);
      } while (param_3 != 0);
      return;
    }
  }
  return;
}

/* ---- 0x004d38a0  Mixer_Mix16Mono ---- */
void Mixer_Mix16Mono(short *param_1,int param_2,uint param_3,int param_4,int param_5)

{
  short sVar1;
  uint uVar2;
  int *piVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  
  piVar3 = g_pMixAccum + param_4 * 2;
  uVar2 = (uint)(param_2 << 0x10) / param_3;
  if (uVar2 == 0x8000) {
    while (param_2 = param_2 + -1, param_2 != 0) {
      *piVar3 = *piVar3 + *param_1 * param_5;
      piVar3[1] = piVar3[1] + param_5 * param_1[1];
      piVar3[2] = piVar3[2] + ((int)param_1[2] + (int)*param_1 >> 1) * param_5;
      piVar3[3] = piVar3[3] + ((int)param_1[3] + (int)param_1[1] >> 1) * param_5;
      piVar3 = piVar3 + 4;
      param_1 = param_1 + 2;
    }
    *piVar3 = *piVar3 + *param_1 * param_5;
    piVar3[1] = piVar3[1] + param_5 * param_1[1];
    piVar3[2] = piVar3[2] + *param_1 * param_5;
    piVar3[3] = piVar3[3] + param_5 * param_1[1];
  }
  else if (uVar2 == 0x10000) {
    iVar6 = param_3 * 2;
    if (iVar6 != 0) {
      do {
        sVar1 = *param_1;
        param_1 = param_1 + 1;
        *piVar3 = *piVar3 + sVar1 * param_5;
        piVar3 = piVar3 + 1;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
      return;
    }
  }
  else if (uVar2 == 0x20000) {
    if (param_3 != 0) {
      do {
        *piVar3 = *piVar3 + *param_1 * param_5;
        piVar3[1] = piVar3[1] + param_1[1] * param_5;
        piVar3 = piVar3 + 2;
        param_3 = param_3 - 1;
        param_1 = param_1 + 4;
      } while (param_3 != 0);
      return;
    }
  }
  else {
    uVar4 = 0;
    if (param_3 != 0) {
      do {
        *piVar3 = *piVar3 + *param_1 * param_5;
        piVar3[1] = piVar3[1] + param_1[1] * param_5;
        uVar5 = uVar4 + uVar2 * 2;
        piVar3 = piVar3 + 2;
        uVar4 = uVar5 & 0xffff;
        param_3 = param_3 - 1;
        param_1 = param_1 + ((int)uVar5 >> 0x10);
      } while (param_3 != 0);
      return;
    }
  }
  return;
}

/* ---- 0x004d3a60  Mixer_MixStereoLR_A ---- */
/* Stereo sample-pair resampler with left/right volumes (format A) */

void Mixer_MixStereoLR_A(ushort *param_1,int param_2,uint param_3,uint param_4,int param_5,
                        int param_6)

{
  ushort uVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  
  piVar3 = g_pMixAccum + param_4 * 2;
  uVar2 = (uint)(param_2 << 0x10) / param_3;
  if (uVar2 == 0x8000) {
    while (param_2 = param_2 + -1, param_2 != 0) {
      uVar1 = param_1[2];
      iVar4 = (int)(short)(*param_1 ^ 0x8000);
      *piVar3 = *piVar3 + param_5 * iVar4;
      piVar3[1] = piVar3[1] + param_6 * iVar4;
      iVar4 = (short)(uVar1 ^ 0x8000) + iVar4 >> 1;
      piVar3[2] = piVar3[2] + param_5 * iVar4;
      param_1 = param_1 + 1;
      piVar3[3] = piVar3[3] + param_6 * iVar4;
      piVar3 = piVar3 + 4;
    }
    param_5 = param_5 * (short)(*param_1 ^ 0x8000);
    param_6 = param_6 * (short)(*param_1 ^ 0x8000);
    *piVar3 = *piVar3 + param_5;
    piVar3[1] = piVar3[1] + param_6;
    piVar3[2] = piVar3[2] + param_5;
    piVar3[3] = piVar3[3] + param_6;
  }
  else if (uVar2 == 0x10000) {
    if (param_3 != 0) {
      do {
        uVar1 = *param_1;
        *piVar3 = *piVar3 + param_5 * (short)(uVar1 ^ 0x8000);
        param_1 = param_1 + 1;
        piVar3[1] = piVar3[1] + param_6 * (short)(uVar1 ^ 0x8000);
        piVar3 = piVar3 + 2;
        param_3 = param_3 - 1;
      } while (param_3 != 0);
      return;
    }
  }
  else if (uVar2 == 0x20000) {
    if (param_3 != 0) {
      do {
        uVar1 = *param_1;
        *piVar3 = *piVar3 + param_5 * (short)(uVar1 ^ 0x8000);
        param_1 = param_1 + 2;
        piVar3[1] = piVar3[1] + param_6 * (short)(uVar1 ^ 0x8000);
        param_3 = param_3 - 1;
        piVar3 = piVar3 + 2;
      } while (param_3 != 0);
      return;
    }
  }
  else {
    uVar5 = 0;
    if (param_3 != 0) {
      param_4 = param_3;
      do {
        uVar1 = *param_1;
        *piVar3 = *piVar3 + param_5 * (short)(uVar1 ^ 0x8000);
        uVar6 = uVar5 + uVar2;
        piVar3[1] = piVar3[1] + param_6 * (short)(uVar1 ^ 0x8000);
        piVar3 = piVar3 + 2;
        uVar5 = uVar6 & 0xffff;
        param_1 = param_1 + ((int)uVar6 >> 0x10);
        param_4 = param_4 - 1;
      } while (param_4 != 0);
      return;
    }
  }
  return;
}

/* ---- 0x004d3c40  Mixer_MixStereo_A ---- */
void Mixer_MixStereo_A(ushort *param_1,int param_2,uint param_3,uint param_4,int param_5)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  uint uVar5;
  int *piVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  
  piVar6 = g_pMixAccum + param_4 * 2;
  uVar5 = (uint)(param_2 << 0x10) / param_3;
  if (uVar5 == 0x8000) {
    while (param_2 = param_2 + -1, param_2 != 0) {
      uVar1 = param_1[2];
      uVar2 = param_1[1];
      uVar3 = *param_1;
      uVar4 = param_1[3];
      *piVar6 = *piVar6 + param_5 * (short)(uVar3 ^ 0x8000);
      piVar6[1] = piVar6[1] + param_5 * (short)(uVar2 ^ 0x8000);
      param_1 = param_1 + 2;
      piVar6[2] = piVar6[2] +
                  ((int)(((int)(short)uVar1 ^ 0xffff8000U) + (int)(short)(uVar3 ^ 0x8000)) >> 1) *
                  param_5;
      piVar6[3] = piVar6[3] +
                  ((int)(short)(uVar4 ^ 0x8000) + (int)(short)(uVar2 ^ 0x8000) >> 1) * param_5;
      piVar6 = piVar6 + 4;
    }
    iVar7 = (short)(*param_1 ^ 0x8000) * param_5;
    param_5 = (short)(param_1[1] ^ 0x8000) * param_5;
    *piVar6 = *piVar6 + iVar7;
    piVar6[1] = piVar6[1] + param_5;
    piVar6[2] = piVar6[2] + iVar7;
    piVar6[3] = piVar6[3] + param_5;
  }
  else if (uVar5 == 0x10000) {
    iVar7 = param_3 * 2;
    if (iVar7 != 0) {
      do {
        uVar1 = *param_1;
        param_1 = param_1 + 1;
        *piVar6 = *piVar6 + ((int)(short)uVar1 ^ 0xffff8000U) * param_5;
        piVar6 = piVar6 + 1;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
      return;
    }
  }
  else if (uVar5 == 0x20000) {
    if (param_3 != 0) {
      do {
        uVar1 = param_1[1];
        *piVar6 = *piVar6 + ((int)(short)*param_1 ^ 0xffff8000U) * param_5;
        param_1 = param_1 + 4;
        piVar6[1] = piVar6[1] + ((int)(short)uVar1 ^ 0xffff8000U) * param_5;
        piVar6 = piVar6 + 2;
        param_3 = param_3 - 1;
      } while (param_3 != 0);
      return;
    }
  }
  else {
    uVar8 = 0;
    if (param_3 != 0) {
      param_4 = param_3;
      do {
        uVar1 = param_1[1];
        *piVar6 = *piVar6 + ((int)(short)*param_1 ^ 0xffff8000U) * param_5;
        uVar9 = uVar8 + uVar5 * 2;
        piVar6[1] = piVar6[1] + (short)(uVar1 ^ 0x8000) * param_5;
        piVar6 = piVar6 + 2;
        uVar8 = uVar9 & 0xffff;
        param_1 = param_1 + ((int)uVar9 >> 0x10);
        param_4 = param_4 - 1;
      } while (param_4 != 0);
      return;
    }
  }
  return;
}

/* ---- 0x004d3e60  Mixer_MixStereoLR_B ---- */
void Mixer_MixStereoLR_B(ushort *param_1,int param_2,uint param_3,uint param_4,int param_5,
                        int param_6)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  uint uVar6;
  
  piVar4 = g_pMixAccum + param_4 * 2;
  uVar2 = (uint)(param_2 << 0x10) / param_3;
  if (uVar2 == 0x8000) {
    while (param_2 = param_2 + -1, param_2 != 0) {
      *piVar4 = *piVar4 + ((uint)(*param_1 >> 8) | (uint)(byte)*param_1 << 8) * param_5;
      piVar4[1] = piVar4[1] + ((uint)(*param_1 >> 8) | (uint)(byte)*param_1 << 8) * param_6;
      iVar3 = (int)(short)param_1[2] + (int)(short)*param_1 >> 1;
      iVar3 = (int)(short)CONCAT31((int3)iVar3,(char)((uint)iVar3 >> 8));
      piVar4[2] = piVar4[2] + param_5 * iVar3;
      piVar4[3] = piVar4[3] + param_6 * iVar3;
      piVar4 = piVar4 + 4;
      param_1 = param_1 + 1;
    }
    iVar3 = (int)CONCAT11((char)*param_1,(char)(*param_1 >> 8));
    param_5 = param_5 * iVar3;
    param_6 = param_6 * iVar3;
    *piVar4 = *piVar4 + param_5;
    piVar4[1] = piVar4[1] + param_6;
    piVar4[2] = piVar4[2] + param_5;
    piVar4[3] = piVar4[3] + param_6;
  }
  else if (uVar2 == 0x10000) {
    if (param_3 != 0) {
      param_4 = param_3;
      do {
        *piVar4 = *piVar4 + ((uint)(*param_1 >> 8) | (uint)(byte)*param_1 << 8) * param_5;
        uVar1 = *param_1;
        param_1 = param_1 + 1;
        piVar4[1] = piVar4[1] + ((uint)(uVar1 >> 8) | (uint)(byte)uVar1 << 8) * param_6;
        param_4 = param_4 - 1;
        piVar4 = piVar4 + 2;
      } while (param_4 != 0);
      return;
    }
  }
  else if (uVar2 == 0x20000) {
    if (param_3 != 0) {
      do {
        *piVar4 = *piVar4 + ((uint)(*param_1 >> 8) | (uint)(byte)*param_1 << 8) * param_5;
        uVar1 = *param_1;
        param_1 = param_1 + 2;
        piVar4[1] = piVar4[1] + ((uint)(uVar1 >> 8) | (uint)(byte)uVar1 << 8) * param_6;
        param_3 = param_3 - 1;
        piVar4 = piVar4 + 2;
      } while (param_3 != 0);
      return;
    }
  }
  else {
    uVar5 = 0;
    if (param_3 != 0) {
      param_4 = param_3;
      do {
        *piVar4 = *piVar4 + ((uint)(*param_1 >> 8) | (uint)(byte)*param_1 << 8) * param_5;
        uVar6 = uVar5 + uVar2;
        piVar4[1] = piVar4[1] + ((uint)(*param_1 >> 8) | (uint)(byte)*param_1 << 8) * param_6;
        piVar4 = piVar4 + 2;
        uVar5 = uVar6 & 0xffff;
        param_4 = param_4 - 1;
        param_1 = param_1 + ((int)uVar6 >> 0x10);
      } while (param_4 != 0);
      return;
    }
  }
  return;
}

/* ---- 0x004d40d0  Mixer_MixStereo_B ---- */
void Mixer_MixStereo_B(ushort *param_1,int param_2,uint param_3,uint param_4,int param_5)

{
  uint uVar1;
  int *piVar2;
  ushort *puVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  
  piVar2 = g_pMixAccum + param_4 * 2;
  uVar1 = (uint)(param_2 << 0x10) / param_3;
  if (uVar1 == 0x8000) {
    while (param_2 = param_2 + -1, param_2 != 0) {
      *piVar2 = *piVar2 + ((uint)(*param_1 >> 8) | (uint)(byte)*param_1 << 8) * param_5;
      piVar2[1] = piVar2[1] + ((uint)(param_1[1] >> 8) | (uint)(byte)param_1[1] << 8) * param_5;
      uVar1 = (int)(short)param_1[2] + (int)(short)*param_1 >> 1;
      piVar2[2] = piVar2[2] + ((uVar1 & 0xff) << 8 | (uVar1 & 0xffff) >> 8) * param_5;
      uVar1 = (int)(short)param_1[3] + (int)(short)param_1[1] >> 1;
      piVar2[3] = piVar2[3] + ((uVar1 & 0xff) << 8 | (uVar1 & 0xffff) >> 8) * param_5;
      piVar2 = piVar2 + 4;
      param_1 = param_1 + 2;
    }
    *piVar2 = *piVar2 + ((uint)(*param_1 >> 8) | (uint)(byte)*param_1 << 8) * param_5;
    piVar2[1] = piVar2[1] + ((uint)(param_1[1] >> 8) | (uint)(byte)param_1[1] << 8) * param_5;
    piVar2[2] = piVar2[2] + ((uint)(*param_1 >> 8) | (uint)(byte)*param_1 << 8) * param_5;
    piVar2[3] = piVar2[3] + ((uint)(param_1[1] >> 8) | (uint)(byte)param_1[1] << 8) * param_5;
  }
  else if (uVar1 == 0x10000) {
    iVar4 = param_3 * 2;
    if (iVar4 != 0) {
      do {
        iVar4 = iVar4 + -1;
        *piVar2 = *piVar2 + ((uint)(*param_1 >> 8) | (uint)(byte)*param_1 << 8) * param_5;
        piVar2 = piVar2 + 1;
      } while (iVar4 != 0);
      return;
    }
  }
  else if (uVar1 == 0x20000) {
    if (param_3 != 0) {
      do {
        puVar3 = param_1 + 1;
        *piVar2 = *piVar2 + ((uint)(*param_1 >> 8) | (uint)(byte)*param_1 << 8) * param_5;
        param_1 = param_1 + 4;
        piVar2[1] = piVar2[1] + ((uint)(*puVar3 >> 8) | (uint)(byte)*puVar3 << 8) * param_5;
        piVar2 = piVar2 + 2;
        param_3 = param_3 - 1;
      } while (param_3 != 0);
      return;
    }
  }
  else {
    uVar5 = 0;
    if (param_3 != 0) {
      param_4 = param_3;
      do {
        *piVar2 = *piVar2 + ((uint)(*param_1 >> 8) | (uint)(byte)*param_1 << 8) * param_5;
        uVar6 = uVar5 + uVar1 * 2;
        piVar2[1] = piVar2[1] + ((uint)(param_1[1] >> 8) | (uint)(byte)param_1[1] << 8) * param_5;
        uVar5 = uVar6 & 0xffff;
        param_4 = param_4 - 1;
        param_1 = param_1 + ((int)uVar6 >> 0x10);
        piVar2 = piVar2 + 2;
      } while (param_4 != 0);
      return;
    }
  }
  return;
}
