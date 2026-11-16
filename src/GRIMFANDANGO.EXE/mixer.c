/* GRIMFANDANGO.EXE :: mixer.c
 * functions 0x004c0ed0 .. 0x004d40d0 (21 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004c0ed0  DSound_Init ---- */
/* Creates the DirectSound object, sets the cooperative level on the main window and creates the
   primary buffer */

uint __cdecl DSound_Init(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  void *a1;
  #define uStack_28 (*(undefined4 *)(_frame + (0x40 - 0x28)))
  #define uStack_24 (*(undefined4 *)(_frame + (0x40 - 0x24)))
  #define iStack_20 (*(int *)(_frame + (0x40 - 0x20)))
  #define uStack_1c (*(undefined4 *)(_frame + (0x40 - 0x1c)))
  #define uStack_18 (*(undefined2 *)(_frame + (0x40 - 0x18)))
  #define uStack_14 (*(undefined4 *)(_frame + (0x40 - 0x14)))
  #define uStack_10 (*(undefined4 *)(_frame + (0x40 - 0x10)))
  #define uStack_c (*(undefined4 *)(_frame + (0x40 - 0xc)))
  #define uStack_8 (*(undefined4 *)(_frame + (0x40 - 0x8)))
  #define uStack_4 (*(undefined4 *)(_frame + (0x40 - 0x4)))
  
  if (g_pDirectSound != (void *)0x0) {
    return 0;
  }
  UINT_008d3664 = 0;
  iVar1 = DirectSoundCreate(0,((unsigned)(uintptr_t)&g_pDirectSound),0);
  if (iVar1 < 0) {
    g_pDirectSound = (void *)0x0;
    return 0;
  }
  a1 = Win_GetMainHwnd();
  iVar1 = (**(code_std **)(*(int *)g_pDirectSound + 0x18))(g_pDirectSound,a1,2);
  if (-1 < iVar1) {
    uStack_14 = 0x14;
    uStack_c = 0;
    uStack_10 = 0x81;
    uStack_8 = 0;
    uStack_4 = 0;
    if (UINT_008d3664 != 0) {
      uStack_10 = 0x91;
    }
    UINT_008d3654 = (uint)a1;
    iVar1 = (**(code_std **)(*(int *)g_pDirectSound + 0xc))
                      (g_pDirectSound,&uStack_14,&g_pDSoundPrimary,0);
    if (iVar1 < 0) {
      g_pDSoundPrimary = (void *)0x0;
      return 1;
    }
    (**(code_std **)(*(int *)g_pDSoundPrimary + 0x18))(g_pDSoundPrimary,&UINT_008d3658);
    iStack_20 = 0x5622;
    uStack_28 = 0x20001;
    uStack_18 = 0;
    uStack_24 = 0x5622;
    if (UINT_008d3660 != 0) {
      iStack_20 = 0x2b11;
      uStack_24 = 0x2b11;
    }
    iStack_20 = iStack_20 << 2;
    uStack_1c = 0x100004;
    (**(code_std **)(*(int *)g_pDSoundPrimary + 0x38))(g_pDSoundPrimary,&uStack_28);
    DSound_SetPrimaryVolume(UINT_004f1000);
    if (UINT_008d3664 != 0) {
      iVar1 = (*(code_std *)**(undefined4 **)g_pDSoundPrimary)
                        (g_pDSoundPrimary,&DAT_004d8510,&PTR_008d3674);
      if (iVar1 < 0) {
        UINT_008d3664 = 0;
        PTR_008d3674 = (int *)0x0;
      }
      else {
        (**(code_std **)(*PTR_008d3674 + 0x2c))(PTR_008d3674,0x3f000000,1);
        (**(code_std **)(*PTR_008d3674 + 0x3c))(PTR_008d3674,0,1);
      }
    }
    (**(code_std **)(*(int *)g_pDSoundPrimary + 0x30))(g_pDSoundPrimary,0,0,0);
    (**(code_std **)(*(int *)g_pDirectSound + 0x18))(g_pDirectSound,a1,3);
  }
  return 1;
}
#undef iStack_20
#undef uStack_10
#undef uStack_14
#undef uStack_18
#undef uStack_1c
#undef uStack_24
#undef uStack_28
#undef uStack_4
#undef uStack_8
#undef uStack_c


/* ---- 0x004c1090  DSound_Shutdown ---- */
void __cdecl DSound_Shutdown(void)

{
  if (PTR_008d3674 != (int *)0x0) {
    (**(code_std **)(*PTR_008d3674 + 8))(PTR_008d3674);
    PTR_008d3674 = (int *)0x0;
  }
  if (g_pDSoundPrimary != (void *)0x0) {
    (**(code_std **)(*(int *)g_pDirectSound + 0x18))(g_pDirectSound,UINT_008d3654,2);
    (**(code_std **)(*(int *)g_pDSoundPrimary + 0x3c))(g_pDSoundPrimary,UINT_008d3658);
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
  void *pvVar1;
  int iVar2;
  longlong lVar3;
  
  if (g_pDSoundPrimary != (void *)0x0) {
    lVar3 = FTOL(((float10)1.0f - (float10)PUN(float,volume)) * ((float10)1.0f - (float10)PUN(float,volume))
                  * (float10)-5000.0);
    pvVar1 = Win_GetMainHwnd();
    iVar2 = (**(code_std **)(*(int *)g_pDirectSound + 0x18))(g_pDirectSound,pvVar1,2);
    if (-1 < iVar2) {
      (**(code_std **)(*(int *)g_pDSoundPrimary + 0x3c))(g_pDSoundPrimary,(int)lVar3);
      (**(code_std **)(*(int *)g_pDirectSound + 0x18))(g_pDirectSound,pvVar1,3);
    }
  }
  return;
}

/* ---- 0x004d27d0  dsn_fill_thread ---- */
/* Locks the next 0x1800-byte block(s) of the streaming buffer behind the play cursor and fills them
   from the mixer Original name dsn_fill_thread (the remaster's GrimFandango (Linux): the fill
   routine dsn_initialize starts (a timer callback here, a thread in the remaster's platform layer):
   sou_mixer_start, dsn_fill_func(0x600, sou_mixer_mix), sou_mixer_end into the 0x1800-byte block);
   was DSound_FillStreamBuffer. */

void __cdecl dsn_fill_thread(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  uint *puVar3;
  undefined4 *puVar4;
  uint *puVar5;
  undefined4 *puVar6;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(undefined4 **)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint **)(_frame + (0x20 - 0x4)))
  
  iVar1 = DSound_GetPlayBlock();
  if (iVar1 != -1) {
    if (iVar1 != (g_nStreamLastBlock + 1) % g_nStreamBlocks) {
      if (g_nStreamLastBlock < 0) {
        g_nStreamLastBlock = iVar1;
      }
      g_nStreamLastBlock = (g_nStreamLastBlock + 1) % g_nStreamBlocks;
      iVar1 = (**(code_std **)(*(int *)g_pStreamDSBuffer + 0x2c))
                        (g_pStreamDSBuffer,g_nStreamLastBlock * 0x1800,0x1800,&local_4,&local_8,
                         &local_c,&local_10,0);
      if (iVar1 == 0) {
        if ((local_c == (undefined4 *)0x0) || (local_10 == 0)) {
          iVar1 = (int)(local_8 + ((int)local_8 >> 0x1f & 3U)) >> 2;
          puVar3 = local_4;
        }
        else {
          iVar1 = 0x600;
          puVar3 = &UINT_008db438;
        }
        sou_mixer_start();
        (*(code_std *)g_pfnStreamMix)(iVar1,sou_mixer_mix);
        sou_mixer_end((short *)puVar3,iVar1);
        if ((local_c != (undefined4 *)0x0) && (local_10 != 0)) {
          puVar3 = &UINT_008db438;
          puVar5 = local_4;
          for (uVar2 = local_8 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
            *puVar5 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar5 = puVar5 + 1;
          }
          for (uVar2 = local_8 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
            *(char *)puVar5 = (char)*puVar3;
            puVar3 = (uint *)((int)puVar3 + 1);
            puVar5 = (uint *)((int)puVar5 + 1);
          }
          puVar4 = (undefined4 *)((int)&UINT_008db438 + local_8);
          puVar6 = local_c;
          for (uVar2 = local_10 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
            *puVar6 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar6 = puVar6 + 1;
          }
          for (uVar2 = local_10 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
            *(undefined1 *)puVar6 = *(undefined1 *)puVar4;
            puVar4 = (undefined4 *)((int)puVar4 + 1);
            puVar6 = (undefined4 *)((int)puVar6 + 1);
          }
        }
        (**(code_std **)(*(int *)g_pStreamDSBuffer + 0x4c))
                  (g_pStreamDSBuffer,local_4,local_8,local_c,local_10);
      }
    }
  }
  (*(code_std *)g_pDsndDriver_timer_services[4])
            (g_nStreamTimerId,
             (int)(0x1234dc /
                  (longlong)((int)(g_dwStreamRate + ((int)g_dwStreamRate >> 0x1f & 0x3ffU)) >> 10)))
  ;
  return;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004d2c60  DSound_GetPlayBlock ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* IDirectSoundBuffer::GetCurrentPosition / 0x1800 modulo the block count */

int __cdecl DSound_GetPlayBlock(void)

{
  int iVar1;
  
  if (g_pStreamDSBuffer != (void *)0x0) {
    iVar1 = (**(code_std **)(*(int *)g_pStreamDSBuffer + 0x10))
                      (g_pStreamDSBuffer,&UINT_008db428,&DAT_008db418);
    if (iVar1 == 0) {
      return ((int)UINT_008db428 / 0x1800) % g_nStreamBlocks;
    }
  }
  return -1;
}
#endif


/* ---- 0x004d2d40  sou_mixer_initialize ---- */
/* Original name sou_mixer_initialize (the remaster's GrimFandango (Linux): dsn_initialize calls it
   with (memory_services, 4, frames) right after the driver set-up in both builds; it sets the table
   count (waveMixCount) and builds the mix tables (Mixer.c), the remaster inlined Mixer_InitTables
   into it); was Mixer_Init. */

int __cdecl sou_mixer_initialize(int *services,uint tableUnits,int frames)

{
  int iVar1;
  
  g_dwWaveMixCount = tableUnits;
  iVar1 = Mixer_InitTables(services,2,frames * 4,0);
  return iVar1;
}

/* ---- 0x004d2d90  sou_mixer_mix ---- */
/* Callback handed to the driver: format code 0..5 (8/16 bit, mono/stereo, offset binary) to
   Mixer_MixVoice parameters Original name sou_mixer_mix (the remaster's GrimFandango (Linux): the
   mix function the fill routine passes to the fill callback in both builds; the same format switch
   0..5 (8/16 bit, mono/stereo, signed) and parameters (data, offset, frames, bytes, -, volume, pan,
   format); the remaster inlined Mixer_MixVoice and the per-format mixers); was
   Mixer_MixVoiceByFormat. */

void __cdecl
sou_mixer_mix(byte *data,int accumOffset,uint outFrames,int srcBytes,int unused,int volume,int pan,
             int format)

{
  int bits;
  int channels;
  
  bits = format;
  channels = format;
  switch(format) {
  case 0:
    format = 1;
    bits = 8;
    channels = 1;
    break;
  case 1:
    format = 1;
    bits = 8;
    channels = 2;
    break;
  case 2:
    format = 0;
    bits = 0x10;
    channels = 1;
    break;
  case 3:
    format = 0;
    bits = 0x10;
    channels = 2;
    break;
  case 4:
    format = 1;
    bits = 0x10;
    channels = 1;
    break;
  case 5:
    format = 1;
    bits = 0x10;
    channels = 2;
  }
  Mixer_MixVoice(data,srcBytes / ((bits >> 3) * channels),bits,channels,outFrames,accumOffset,volume
                 ,(pan + 0x7f) / 2,format,0);
  return;
}

/* ---- 0x004d2e60  sou_mixer_end ---- */
/* Original name sou_mixer_end (the remaster's GrimFandango (Linux): the fill routine's last call
   (dst, frames) in both builds: clamps the accumulator (>> 7) to 16-bit output; the remaster
   inlined Mixer_ConvertTo16); was Mixer_Output. */

void __cdecl sou_mixer_end(short *dst,int frames)

{
  Mixer_ConvertTo16(dst,frames);
  return;
}

/* ---- 0x004d2e80  Mixer_InitTables ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Builds the 17x17 volume/pan table and the compander table and allocates the accumulator */

int __cdecl Mixer_InitTables(int *services,uint channels,int frames4,int unused)

{
  uint uVar1;
  undefined2 *puVar2;
  undefined1 *puVar3;
  float10 fVar4;
  float10 fVar5;
  float10 extraout_ST0;
  longlong lVar6;
  uint local_4;
  
  puVar3 = &DAT_008dcc70;
  local_4 = 0;
  do {
    uVar1 = local_4;
    fVar4 = (float10)(int)local_4;
    local_4 = 0;
    do {
      fVar5 = (float10)fsin((float10)(int)local_4 * (float10)3.1415 * (float10)0.03125);
      lVar6 = FTOL((fVar5 * fVar4 - (float10)-0.5) * (float10)8.0);
      *puVar3 = (char)lVar6;
      puVar3 = puVar3 + 1;
      local_4 = local_4 + 1;
      fVar4 = extraout_ST0;
    } while ((int)local_4 < 0x11);
    local_4 = uVar1 + 1;
  } while ((int)local_4 < 0x11);
  g_dwMixer_outChannelCount = channels;
  g_dwMixer_mixBufSize = frames4 * 4;
  g_pMixer_mixBuf =
       (int *)(*(code_std *)*services)
                        (g_dwMixer_mixBufSize,s_C__grimsrc_libs_lecsmush_insane__004f4158,0x356);
  if (g_pMixer_mixBuf == (int *)0x0) {
    return -1;
  }
  INT_008dcda0 = unused;
  puVar2 = (undefined2 *)
           (*(code_std *)*services)
                     (g_dwWaveMixCount << 0x10,s_C__grimsrc_libs_lecsmush_insane__004f4158,0x35c);
  g_pMixer_softLTable = puVar2;
  if (puVar2 == (undefined2 *)0x0) {
    return -1;
  }
  local_4 = 0;
  if (0 < (int)(g_dwWaveMixCount << 0xf)) {
    do {
      lVar6 = FTOL((((float10)(int)local_4 * (float10)524272.0) /
                     ((float10)262136.0 - (float10)(int)local_4 * (float10)-7.0) - (float10)-1.0) *
                    (float10)0.5);
      *puVar2 = (short)lVar6;
      puVar2 = puVar2 + 1;
      local_4 = local_4 + 1;
    } while ((int)local_4 < (int)(g_dwWaveMixCount * 0x8000));
  }
  return 0;
}
#endif


/* ---- 0x004d2fb0  Mixer_Free ---- */
int __cdecl Mixer_Free(int *services)

{
  if (g_pMixer_softLTable != (void *)0x0) {
    (*(code_std *)services[1])(g_pMixer_softLTable,s_C__grimsrc_libs_lecsmush_insane__004f4158,0x379);
  }
  g_pMixer_softLTable = (void *)0x0;
  if (g_pMixer_mixBuf != (int *)0x0) {
    (*(code_std *)services[1])(g_pMixer_mixBuf,s_C__grimsrc_libs_lecsmush_insane__004f4158,0x37a);
  }
  g_pMixer_mixBuf = (int *)0x0;
  return 0;
}

/* ---- 0x004d3010  sou_mixer_start ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Zeroes the 32-bit mix accumulator at g_pMixer_mixBuf Original name sou_mixer_start (the
   remaster's GrimFandango (Linux): the fill routine's first call in both builds (dsn_fill_thread:
   sou_mixer_start, fill callback, sou_mixer_end): clears the mix accumulator (mixBuf, mixBufSize
   bytes)); was Mixer_ClearAccumulator. */

int sou_mixer_start(void)

{
  uint uVar1;
  uint uVar2;
  int *piVar3;
  
  uVar2 = g_dwMixer_mixBufSize;
  piVar3 = g_pMixer_mixBuf;
  for (uVar1 = g_dwMixer_mixBufSize >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
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

void __cdecl
Mixer_MixVoice(byte *data,int count,int bits,int channels,uint outFrames,int accumOffset,int volume,
              int pan,int offsetBinary,int byteSwapped)

{
  int iVar1;
  uint uVar2;
  uint volL;
  
  if (((g_pMixer_mixBuf != (int *)0x0) && (data != (byte *)0x0)) && (count != 0)) {
    if (channels == 1) {
      uVar2 = volume >> 3;
      if (volume != 0) {
        uVar2 = uVar2 + 1;
      }
      if (0x10 < uVar2) {
        uVar2 = 0x10;
      }
      iVar1 = (pan >> 3) + -8;
      if (0x40 < pan) {
        iVar1 = (pan >> 3) + -7;
      }
      volL = (uint)(byte)(&DAT_008dcc78)[uVar2 * 0x11 - iVar1];
      uVar2 = (uint)(byte)(&DAT_008dcc78)[uVar2 * 0x11 + iVar1];
      if (bits == 8) {
        Mixer_Mix8MonoLR(data,count,outFrames,accumOffset,volL,uVar2);
        return;
      }
      if (offsetBinary == 0) {
        Mixer_MixStereoLR_A((ushort *)data,count,outFrames,accumOffset,volL,uVar2);
        return;
      }
      if (byteSwapped != 0) {
        Mixer_MixStereoLR_B((ushort *)data,count,outFrames,accumOffset,volL,uVar2);
        return;
      }
      Mixer_Mix16MonoLR((short *)data,count,outFrames,accumOffset,volL,uVar2);
      return;
    }
    if (bits == 8) {
      Mixer_Mix8Mono(data,count,outFrames,accumOffset,volume + 1);
      return;
    }
    if (offsetBinary == 0) {
      Mixer_MixStereo_A((ushort *)data,count,outFrames,accumOffset,volume + 1);
      return;
    }
    if (byteSwapped != 0) {
      Mixer_MixStereo_B((ushort *)data,count,outFrames,accumOffset,volume + 1);
      return;
    }
    Mixer_Mix16Mono((short *)data,count,outFrames,accumOffset,volume + 1);
  }
  return;
}

/* ---- 0x004d31d0  Mixer_ConvertTo16 ---- */
/* Accumulator >> 7 clamped to 16 bits into the output block */

int __cdecl Mixer_ConvertTo16(short *dst,int frames)

{
  int *piVar1;
  int iVar2;
  
  if (((g_pMixer_mixBuf != (int *)0x0) && (dst != (short *)0x0)) && (frames != 0)) {
    piVar1 = g_pMixer_mixBuf;
    if (g_dwMixer_outChannelCount == 2) {
      frames = frames << 1;
    }
    for (; frames != 0; frames = frames + -1) {
      iVar2 = *piVar1 >> 7;
      if (iVar2 < -0x8000) {
        iVar2 = -0x8000;
      }
      if (0x7fff < iVar2) {
        iVar2 = 0x7fff;
      }
      *dst = (short)iVar2;
      dst = dst + 1;
      piVar1 = piVar1 + 1;
    }
    return 0;
  }
  return -1;
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
  
  piVar4 = g_pMixer_mixBuf + accumOffset * 2;
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
void __cdecl Mixer_Mix8Mono(byte *data,int count,uint outFrames,int accumOffset,int vol)

{
  byte bVar1;
  uint uVar2;
  byte *pbVar3;
  byte *pbVar4;
  int *piVar5;
  uint uVar6;
  int iVar7;
  
  piVar5 = g_pMixer_mixBuf + accumOffset * 2;
  uVar2 = (uint)(count << 0x10) / outFrames;
  if (uVar2 == 0x8000) {
    while (count = count + -1, count != 0) {
      *piVar5 = *piVar5 + (*data ^ 0x80) * 0x100 * vol;
      piVar5[1] = piVar5[1] + (data[1] ^ 0x80) * 0x100 * vol;
      pbVar4 = data + 1;
      piVar5[2] = piVar5[2] + (((uint)data[2] + (uint)*data) * 0x80 ^ 0x8000) * vol;
      pbVar3 = data + 3;
      data = data + 2;
      piVar5[3] = piVar5[3] + (((uint)*pbVar3 + (uint)*pbVar4) * 0x80 ^ 0x8000) * vol;
      piVar5 = piVar5 + 4;
    }
    *piVar5 = *piVar5 + (*data ^ 0x80) * 0x100 * vol;
    piVar5[1] = piVar5[1] + (data[1] ^ 0x80) * 0x100 * vol;
    piVar5[2] = piVar5[2] + (*data ^ 0x80) * 0x100 * vol;
    piVar5[3] = piVar5[3] + (data[1] ^ 0x80) * 0x100 * vol;
  }
  else if (uVar2 == 0x10000) {
    iVar7 = outFrames * 2;
    if (iVar7 != 0) {
      do {
        bVar1 = *data;
        data = data + 1;
        *piVar5 = *piVar5 + (bVar1 ^ 0x80) * 0x100 * vol;
        iVar7 = iVar7 + -1;
        piVar5 = piVar5 + 1;
      } while (iVar7 != 0);
      return;
    }
  }
  else if (uVar2 == 0x20000) {
    if (outFrames != 0) {
      do {
        pbVar3 = data + 1;
        *piVar5 = *piVar5 + (*data ^ 0x80) * 0x100 * vol;
        data = data + 4;
        outFrames = outFrames - 1;
        piVar5[1] = piVar5[1] + (*pbVar3 ^ 0x80) * 0x100 * vol;
        piVar5 = piVar5 + 2;
      } while (outFrames != 0);
      return;
    }
  }
  else {
    uVar6 = 0;
    if (outFrames != 0) {
      do {
        uVar6 = uVar6 + uVar2 * 2;
        *piVar5 = *piVar5 + (*data ^ 0x80) * 0x100 * vol;
        piVar5[1] = piVar5[1] + (data[1] ^ 0x80) * 0x100 * vol;
        data = data + ((int)uVar6 >> 0x10);
        uVar6 = uVar6 & 0xffff;
        outFrames = outFrames - 1;
        piVar5 = piVar5 + 2;
      } while (outFrames != 0);
      return;
    }
  }
  return;
}

/* ---- 0x004d36e0  Mixer_Mix16MonoLR ---- */
void __cdecl
Mixer_Mix16MonoLR(short *data,int count,uint outFrames,int accumOffset,int volL,int volR)

{
  uint uVar1;
  int *piVar2;
  uint uVar3;
  uint uVar4;
  
  piVar2 = g_pMixer_mixBuf + accumOffset * 2;
  uVar1 = (uint)(count << 0x10) / outFrames;
  if (uVar1 == 0x8000) {
    while (count = count + -1, count != 0) {
      *piVar2 = *piVar2 + *data * volL;
      piVar2[1] = piVar2[1] + *data * volR;
      piVar2[2] = piVar2[2] + ((int)*data + (int)data[2] >> 1) * volL;
      piVar2[3] = piVar2[3] + ((int)*data + (int)data[2] >> 1) * volR;
      piVar2 = piVar2 + 4;
      data = data + 1;
    }
    *piVar2 = *piVar2 + *data * volL;
    piVar2[1] = piVar2[1] + *data * volR;
    piVar2[2] = piVar2[2] + *data * volL;
    piVar2[3] = piVar2[3] + *data * volR;
  }
  else if (uVar1 == 0x10000) {
    if (outFrames != 0) {
      do {
        *piVar2 = *piVar2 + *data * volL;
        piVar2[1] = piVar2[1] + *data * volR;
        piVar2 = piVar2 + 2;
        outFrames = outFrames - 1;
        data = data + 1;
      } while (outFrames != 0);
      return;
    }
  }
  else if (uVar1 == 0x20000) {
    if (outFrames != 0) {
      do {
        *piVar2 = *piVar2 + *data * volL;
        piVar2[1] = piVar2[1] + *data * volR;
        piVar2 = piVar2 + 2;
        outFrames = outFrames - 1;
        data = data + 2;
      } while (outFrames != 0);
      return;
    }
  }
  else {
    uVar3 = 0;
    if (outFrames != 0) {
      do {
        *piVar2 = *piVar2 + *data * volL;
        piVar2[1] = piVar2[1] + *data * volR;
        uVar4 = uVar3 + uVar1;
        piVar2 = piVar2 + 2;
        uVar3 = uVar4 & 0xffff;
        outFrames = outFrames - 1;
        data = data + ((int)uVar4 >> 0x10);
      } while (outFrames != 0);
      return;
    }
  }
  return;
}

/* ---- 0x004d38a0  Mixer_Mix16Mono ---- */
void __cdecl Mixer_Mix16Mono(short *data,int count,uint outFrames,int accumOffset,int vol)

{
  short sVar1;
  uint uVar2;
  int *piVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  
  piVar3 = g_pMixer_mixBuf + accumOffset * 2;
  uVar2 = (uint)(count << 0x10) / outFrames;
  if (uVar2 == 0x8000) {
    while (count = count + -1, count != 0) {
      *piVar3 = *piVar3 + *data * vol;
      piVar3[1] = piVar3[1] + vol * data[1];
      piVar3[2] = piVar3[2] + ((int)data[2] + (int)*data >> 1) * vol;
      piVar3[3] = piVar3[3] + ((int)data[3] + (int)data[1] >> 1) * vol;
      piVar3 = piVar3 + 4;
      data = data + 2;
    }
    *piVar3 = *piVar3 + *data * vol;
    piVar3[1] = piVar3[1] + vol * data[1];
    piVar3[2] = piVar3[2] + *data * vol;
    piVar3[3] = piVar3[3] + vol * data[1];
  }
  else if (uVar2 == 0x10000) {
    iVar6 = outFrames * 2;
    if (iVar6 != 0) {
      do {
        sVar1 = *data;
        data = data + 1;
        *piVar3 = *piVar3 + sVar1 * vol;
        piVar3 = piVar3 + 1;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
      return;
    }
  }
  else if (uVar2 == 0x20000) {
    if (outFrames != 0) {
      do {
        *piVar3 = *piVar3 + *data * vol;
        piVar3[1] = piVar3[1] + data[1] * vol;
        piVar3 = piVar3 + 2;
        outFrames = outFrames - 1;
        data = data + 4;
      } while (outFrames != 0);
      return;
    }
  }
  else {
    uVar4 = 0;
    if (outFrames != 0) {
      do {
        *piVar3 = *piVar3 + *data * vol;
        piVar3[1] = piVar3[1] + data[1] * vol;
        uVar5 = uVar4 + uVar2 * 2;
        piVar3 = piVar3 + 2;
        uVar4 = uVar5 & 0xffff;
        outFrames = outFrames - 1;
        data = data + ((int)uVar5 >> 0x10);
      } while (outFrames != 0);
      return;
    }
  }
  return;
}

/* ---- 0x004d3a60  Mixer_MixStereoLR_A ---- */
/* Stereo sample-pair resampler with left/right volumes (format A) */

void __cdecl
Mixer_MixStereoLR_A(ushort *data,int count,uint outFrames,uint accumOffset,int volL,int volR)

{
  ushort uVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  
  piVar3 = g_pMixer_mixBuf + accumOffset * 2;
  uVar2 = (uint)(count << 0x10) / outFrames;
  if (uVar2 == 0x8000) {
    while (count = count + -1, count != 0) {
      uVar1 = data[2];
      iVar5 = (int)(short)(*data ^ 0x8000);
      *piVar3 = *piVar3 + volL * iVar5;
      piVar3[1] = piVar3[1] + volR * iVar5;
      iVar5 = (short)(uVar1 ^ 0x8000) + iVar5 >> 1;
      piVar3[2] = piVar3[2] + volL * iVar5;
      data = data + 1;
      piVar3[3] = piVar3[3] + volR * iVar5;
      piVar3 = piVar3 + 4;
    }
    iVar4 = volL * (short)(*data ^ 0x8000);
    iVar5 = volR * (short)(*data ^ 0x8000);
    *piVar3 = *piVar3 + iVar4;
    piVar3[1] = piVar3[1] + iVar5;
    piVar3[2] = piVar3[2] + iVar4;
    piVar3[3] = piVar3[3] + iVar5;
  }
  else if (uVar2 == 0x10000) {
    if (outFrames != 0) {
      do {
        uVar1 = *data;
        *piVar3 = *piVar3 + volL * (short)(uVar1 ^ 0x8000);
        data = data + 1;
        piVar3[1] = piVar3[1] + volR * (short)(uVar1 ^ 0x8000);
        piVar3 = piVar3 + 2;
        outFrames = outFrames - 1;
      } while (outFrames != 0);
      return;
    }
  }
  else if (uVar2 == 0x20000) {
    if (outFrames != 0) {
      do {
        uVar1 = *data;
        *piVar3 = *piVar3 + volL * (short)(uVar1 ^ 0x8000);
        data = data + 2;
        piVar3[1] = piVar3[1] + volR * (short)(uVar1 ^ 0x8000);
        outFrames = outFrames - 1;
        piVar3 = piVar3 + 2;
      } while (outFrames != 0);
      return;
    }
  }
  else {
    uVar6 = 0;
    if (outFrames != 0) {
      accumOffset = outFrames;
      do {
        uVar1 = *data;
        *piVar3 = *piVar3 + volL * (short)(uVar1 ^ 0x8000);
        uVar7 = uVar6 + uVar2;
        piVar3[1] = piVar3[1] + volR * (short)(uVar1 ^ 0x8000);
        piVar3 = piVar3 + 2;
        uVar6 = uVar7 & 0xffff;
        data = data + ((int)uVar7 >> 0x10);
        accumOffset = accumOffset - 1;
      } while (accumOffset != 0);
      return;
    }
  }
  return;
}

/* ---- 0x004d3c40  Mixer_MixStereo_A ---- */
void __cdecl Mixer_MixStereo_A(ushort *data,int count,uint outFrames,uint accumOffset,int vol)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  uint uVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  
  piVar6 = g_pMixer_mixBuf + accumOffset * 2;
  uVar5 = (uint)(count << 0x10) / outFrames;
  if (uVar5 == 0x8000) {
    while (count = count + -1, count != 0) {
      uVar1 = data[2];
      uVar2 = data[1];
      uVar3 = *data;
      uVar4 = data[3];
      *piVar6 = *piVar6 + vol * (short)(uVar3 ^ 0x8000);
      piVar6[1] = piVar6[1] + vol * (short)(uVar2 ^ 0x8000);
      data = data + 2;
      piVar6[2] = piVar6[2] +
                  ((int)(((int)(short)uVar1 ^ 0xffff8000U) + (int)(short)(uVar3 ^ 0x8000)) >> 1) *
                  vol;
      piVar6[3] = piVar6[3] +
                  ((int)(short)(uVar4 ^ 0x8000) + (int)(short)(uVar2 ^ 0x8000) >> 1) * vol;
      piVar6 = piVar6 + 4;
    }
    iVar8 = (short)(*data ^ 0x8000) * vol;
    iVar7 = (short)(data[1] ^ 0x8000) * vol;
    *piVar6 = *piVar6 + iVar8;
    piVar6[1] = piVar6[1] + iVar7;
    piVar6[2] = piVar6[2] + iVar8;
    piVar6[3] = piVar6[3] + iVar7;
  }
  else if (uVar5 == 0x10000) {
    iVar7 = outFrames * 2;
    if (iVar7 != 0) {
      do {
        uVar1 = *data;
        data = data + 1;
        *piVar6 = *piVar6 + ((int)(short)uVar1 ^ 0xffff8000U) * vol;
        piVar6 = piVar6 + 1;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
      return;
    }
  }
  else if (uVar5 == 0x20000) {
    if (outFrames != 0) {
      do {
        uVar1 = data[1];
        *piVar6 = *piVar6 + ((int)(short)*data ^ 0xffff8000U) * vol;
        data = data + 4;
        piVar6[1] = piVar6[1] + ((int)(short)uVar1 ^ 0xffff8000U) * vol;
        piVar6 = piVar6 + 2;
        outFrames = outFrames - 1;
      } while (outFrames != 0);
      return;
    }
  }
  else {
    uVar9 = 0;
    if (outFrames != 0) {
      accumOffset = outFrames;
      do {
        uVar1 = data[1];
        *piVar6 = *piVar6 + ((int)(short)*data ^ 0xffff8000U) * vol;
        uVar10 = uVar9 + uVar5 * 2;
        piVar6[1] = piVar6[1] + (short)(uVar1 ^ 0x8000) * vol;
        piVar6 = piVar6 + 2;
        uVar9 = uVar10 & 0xffff;
        data = data + ((int)uVar10 >> 0x10);
        accumOffset = accumOffset - 1;
      } while (accumOffset != 0);
      return;
    }
  }
  return;
}

/* ---- 0x004d3e60  Mixer_MixStereoLR_B ---- */
void __cdecl
Mixer_MixStereoLR_B(ushort *data,int count,uint outFrames,uint accumOffset,int volL,int volR)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  
  piVar4 = g_pMixer_mixBuf + accumOffset * 2;
  uVar2 = (uint)(count << 0x10) / outFrames;
  if (uVar2 == 0x8000) {
    while (count = count + -1, count != 0) {
      *piVar4 = *piVar4 + ((uint)(*data >> 8) | (uint)(byte)*data << 8) * volL;
      piVar4[1] = piVar4[1] + ((uint)(*data >> 8) | (uint)(byte)*data << 8) * volR;
      iVar3 = (int)(short)data[2] + (int)(short)*data >> 1;
      iVar3 = (int)(short)CONCAT31((int3)iVar3,(char)((uint)iVar3 >> 8));
      piVar4[2] = piVar4[2] + volL * iVar3;
      piVar4[3] = piVar4[3] + volR * iVar3;
      piVar4 = piVar4 + 4;
      data = data + 1;
    }
    iVar3 = (int)CONCAT11((char)*data,(char)(*data >> 8));
    iVar5 = volL * iVar3;
    iVar3 = volR * iVar3;
    *piVar4 = *piVar4 + iVar5;
    piVar4[1] = piVar4[1] + iVar3;
    piVar4[2] = piVar4[2] + iVar5;
    piVar4[3] = piVar4[3] + iVar3;
  }
  else if (uVar2 == 0x10000) {
    if (outFrames != 0) {
      accumOffset = outFrames;
      do {
        *piVar4 = *piVar4 + ((uint)(*data >> 8) | (uint)(byte)*data << 8) * volL;
        uVar1 = *data;
        data = data + 1;
        piVar4[1] = piVar4[1] + ((uint)(uVar1 >> 8) | (uint)(byte)uVar1 << 8) * volR;
        accumOffset = accumOffset - 1;
        piVar4 = piVar4 + 2;
      } while (accumOffset != 0);
      return;
    }
  }
  else if (uVar2 == 0x20000) {
    if (outFrames != 0) {
      do {
        *piVar4 = *piVar4 + ((uint)(*data >> 8) | (uint)(byte)*data << 8) * volL;
        uVar1 = *data;
        data = data + 2;
        piVar4[1] = piVar4[1] + ((uint)(uVar1 >> 8) | (uint)(byte)uVar1 << 8) * volR;
        outFrames = outFrames - 1;
        piVar4 = piVar4 + 2;
      } while (outFrames != 0);
      return;
    }
  }
  else {
    uVar6 = 0;
    if (outFrames != 0) {
      accumOffset = outFrames;
      do {
        *piVar4 = *piVar4 + ((uint)(*data >> 8) | (uint)(byte)*data << 8) * volL;
        uVar7 = uVar6 + uVar2;
        piVar4[1] = piVar4[1] + ((uint)(*data >> 8) | (uint)(byte)*data << 8) * volR;
        piVar4 = piVar4 + 2;
        uVar6 = uVar7 & 0xffff;
        accumOffset = accumOffset - 1;
        data = data + ((int)uVar7 >> 0x10);
      } while (accumOffset != 0);
      return;
    }
  }
  return;
}

/* ---- 0x004d40d0  Mixer_MixStereo_B ---- */
void __cdecl Mixer_MixStereo_B(ushort *data,int count,uint outFrames,uint accumOffset,int vol)

{
  uint uVar1;
  int *piVar2;
  ushort *puVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  
  piVar2 = g_pMixer_mixBuf + accumOffset * 2;
  uVar1 = (uint)(count << 0x10) / outFrames;
  if (uVar1 == 0x8000) {
    while (count = count + -1, count != 0) {
      *piVar2 = *piVar2 + ((uint)(*data >> 8) | (uint)(byte)*data << 8) * vol;
      piVar2[1] = piVar2[1] + ((uint)(data[1] >> 8) | (uint)(byte)data[1] << 8) * vol;
      uVar1 = (int)(short)data[2] + (int)(short)*data >> 1;
      piVar2[2] = piVar2[2] + ((uVar1 & 0xff) << 8 | (uVar1 & 0xffff) >> 8) * vol;
      uVar1 = (int)(short)data[3] + (int)(short)data[1] >> 1;
      piVar2[3] = piVar2[3] + ((uVar1 & 0xff) << 8 | (uVar1 & 0xffff) >> 8) * vol;
      piVar2 = piVar2 + 4;
      data = data + 2;
    }
    *piVar2 = *piVar2 + ((uint)(*data >> 8) | (uint)(byte)*data << 8) * vol;
    piVar2[1] = piVar2[1] + ((uint)(data[1] >> 8) | (uint)(byte)data[1] << 8) * vol;
    piVar2[2] = piVar2[2] + ((uint)(*data >> 8) | (uint)(byte)*data << 8) * vol;
    piVar2[3] = piVar2[3] + ((uint)(data[1] >> 8) | (uint)(byte)data[1] << 8) * vol;
  }
  else if (uVar1 == 0x10000) {
    iVar4 = outFrames * 2;
    if (iVar4 != 0) {
      do {
        iVar4 = iVar4 + -1;
        *piVar2 = *piVar2 + ((uint)(*data >> 8) | (uint)(byte)*data << 8) * vol;
        piVar2 = piVar2 + 1;
      } while (iVar4 != 0);
      return;
    }
  }
  else if (uVar1 == 0x20000) {
    if (outFrames != 0) {
      do {
        puVar3 = data + 1;
        *piVar2 = *piVar2 + ((uint)(*data >> 8) | (uint)(byte)*data << 8) * vol;
        data = data + 4;
        piVar2[1] = piVar2[1] + ((uint)(*puVar3 >> 8) | (uint)(byte)*puVar3 << 8) * vol;
        piVar2 = piVar2 + 2;
        outFrames = outFrames - 1;
      } while (outFrames != 0);
      return;
    }
  }
  else {
    uVar5 = 0;
    if (outFrames != 0) {
      accumOffset = outFrames;
      do {
        *piVar2 = *piVar2 + ((uint)(*data >> 8) | (uint)(byte)*data << 8) * vol;
        uVar6 = uVar5 + uVar1 * 2;
        piVar2[1] = piVar2[1] + ((uint)(data[1] >> 8) | (uint)(byte)data[1] << 8) * vol;
        uVar5 = uVar6 & 0xffff;
        accumOffset = accumOffset - 1;
        data = data + ((int)uVar6 >> 0x10);
        piVar2 = piVar2 + 2;
      } while (accumOffset != 0);
      return;
    }
  }
  return;
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
typedef struct __attribute__((packed)) { unsigned char b0[12]; void *pc; unsigned char b10[4]; void *p14; unsigned char b18[4]; void *p1c; unsigned char b20[4]; void *p24; unsigned char b28[4]; void *p2c; unsigned char b30[4]; void *p34; unsigned char b38[4]; void *p3c; unsigned char b40[4]; void *p44; unsigned char b48[4]; void *p4c; unsigned char b50[4]; void *p54; unsigned char b58[4]; void *p5c; unsigned char b60[4]; void *p64; unsigned char b68[4]; void *p6c; unsigned char b70[4]; void *p74; unsigned char b78[4]; void *p7c; unsigned char b80[4]; void *p84; } grim_span_004f1000;
typedef struct __attribute__((packed)) { unsigned char b0[72]; void *p48; unsigned char b4c[4]; void *p50; unsigned char b54[4]; void *p58; unsigned char b5c[4]; void *p60; unsigned char b64[4]; void *p68; void *p6c; unsigned char b70[4]; void *p74; unsigned char b78[8]; void *p80; unsigned char b84[4]; } grim_span_004f4158;
extern char f_FUN_004b4ad4[] __asm__("_FUN_004b4ad4");
extern char f_FUN_004b4b0d[] __asm__("_FUN_004b4b0d");
extern char f_FUN_004b4b0f[] __asm__("_FUN_004b4b0f");
extern char f_FUN_004d54b4[] __asm__("_FUN_004d54b4");
extern unsigned char grim_def_DAT_004d8510[96] __asm__("_DAT_004d8510");
extern char grim_def_DAT_004f1088[] __asm__("_DAT_004f1088");
extern char grim_def_DAT_004f109c[] __asm__("_DAT_004f109c");
extern char grim_def_DAT_004f10b4[] __asm__("_DAT_004f10b4");
extern char grim_def_DAT_004f10c8[] __asm__("_DAT_004f10c8");
extern char grim_def_DAT_004f10e0[] __asm__("_DAT_004f10e0");
extern char grim_def_DAT_004f10f4[] __asm__("_DAT_004f10f4");
extern char grim_def_DAT_004f1104[] __asm__("_DAT_004f1104");
extern char grim_def_DAT_004f1118[] __asm__("_DAT_004f1118");
extern char grim_def_DAT_004f112c[] __asm__("_DAT_004f112c");
extern char grim_def_DAT_004f1140[] __asm__("_DAT_004f1140");
extern char grim_def_DAT_004f1150[] __asm__("_DAT_004f1150");
extern char grim_def_DAT_004f1168[] __asm__("_DAT_004f1168");
extern char grim_def_DAT_004f117c[] __asm__("_DAT_004f117c");
extern char grim_def_DAT_004f118c[] __asm__("_DAT_004f118c");
extern char grim_def_DAT_004f11a8[] __asm__("_DAT_004f11a8");
extern char grim_def_DAT_004f11b8[] __asm__("_DAT_004f11b8");
extern unsigned char grim_def_DAT_008db418[4] __asm__("_DAT_008db418");
extern unsigned char grim_def_DAT_008dcc70[8] __asm__("_DAT_008dcc70");
extern unsigned char grim_def_DAT_008dcc78[292] __asm__("_DAT_008dcc78");
extern int grim_def_INT_008dcda0 __asm__("_INT_008dcda0");
extern unsigned char grim_def_PTR_008d3674[12] __asm__("_PTR_008d3674");
extern grim_span_004f1000 grim_def_UINT_004f1000 __asm__("_UINT_004f1000");
extern unsigned int grim_def_UINT_008d3654 __asm__("_UINT_008d3654");
extern unsigned int grim_def_UINT_008d3658 __asm__("_UINT_008d3658");
extern unsigned int grim_def_UINT_008d3660 __asm__("_UINT_008d3660");
extern unsigned char grim_def_UINT_008d3664[12] __asm__("_UINT_008d3664");
extern unsigned int grim_def_UINT_008db428 __asm__("_UINT_008db428");
extern unsigned char grim_def_UINT_008db438[6144] __asm__("_UINT_008db438");
extern unsigned int grim_def_g_dwMixer_mixBufSize __asm__("_g_dwMixer_mixBufSize");
extern unsigned int grim_def_g_dwMixer_outChannelCount __asm__("_g_dwMixer_outChannelCount");
extern unsigned int grim_def_g_dwWaveMixCount __asm__("_g_dwWaveMixCount");
extern int grim_def_g_nStreamLastBlock __asm__("_g_nStreamLastBlock");
extern unsigned char grim_def_g_pDSoundPrimary[4] __asm__("_g_pDSoundPrimary");
extern unsigned char grim_def_g_pMixer_mixBuf[8] __asm__("_g_pMixer_mixBuf");
extern unsigned char grim_def_g_pMixer_softLTable[12] __asm__("_g_pMixer_softLTable");
extern grim_span_004f4158 grim_def_s_C__grimsrc_libs_lecsmush_insane__004f4158 __asm__("_s_C__grimsrc_libs_lecsmush_insane__004f4158");
/* 0x004d8510, 96 bytes */ GRIM_DATA("004d8510") unsigned char grim_def_DAT_004d8510[96] __asm__("_DAT_004d8510") = {
    0x84, 0xfa, 0x9a, 0x27, 0x81, 0x49, 0xce, 0x11, 0xa5, 0x21, 0x00, 0x20, 0xaf, 0x0b, 0xe5, 0x60,
    0x86, 0xfa, 0x9a, 0x27, 0x81, 0x49, 0xce, 0x11, 0xa5, 0x21, 0x00, 0x20, 0xaf, 0x0b, 0xe5, 0x60,
    0x81, 0x07, 0x21, 0xb0, 0xcd, 0x89, 0xd0, 0x11, 0xaf, 0x08, 0x00, 0xa0, 0xc9, 0x25, 0xcd, 0x16,
    0x82, 0x07, 0x21, 0xb0, 0xcd, 0x89, 0xd0, 0x11, 0xaf, 0x08, 0x00, 0xa0, 0xc9, 0x25, 0xcd, 0x16,
    0x83, 0x07, 0x21, 0xb0, 0xcd, 0x89, 0xd0, 0x11, 0xaf, 0x08, 0x00, 0xa0, 0xc9, 0x25, 0xcd, 0x16,
    0x30, 0xac, 0xef, 0x31, 0x5c, 0x51, 0xd0, 0x11, 0xa9, 0xaa, 0x00, 0xaa, 0x00, 0x61, 0xbe, 0x93
};
static unsigned char grim_anchor_004f1000[0] __attribute__((section(".data$grim_004f1000"), aligned(16), used));
static unsigned char grim_pad_004f1000[0] __attribute__((section(".data$grim_004f1000_"), aligned(4), used));
/* 0x004f1000, 136 bytes */ GRIM_DATA("004f1000z") grim_span_004f1000 grim_def_UINT_004f1000 __asm__("_UINT_004f1000") = {
    { 0xcd, 0xcc, 0x4c, 0x3f },
    (void *)&grim_def_DAT_004f11b8,
    { 0x0a, 0x00, 0x78, 0x88 },
    (void *)&grim_def_DAT_004f11a8,
    { 0x82, 0x00, 0x78, 0x88 },
    (void *)&grim_def_DAT_004f118c,
    { 0x64, 0x00, 0x78, 0x88 },
    (void *)&grim_def_DAT_004f117c,
    { 0x96, 0x00, 0x78, 0x88 },
    (void *)&grim_def_DAT_004f1168,
    { 0x1e, 0x00, 0x78, 0x88 },
    (void *)&grim_def_DAT_004f1150,
    { 0x05, 0x40, 0x00, 0x80 },
    (void *)&grim_def_DAT_004f1140,
    { 0x57, 0x00, 0x07, 0x80 },
    (void *)&grim_def_DAT_004f112c,
    { 0x32, 0x00, 0x78, 0x88 },
    (void *)&grim_def_DAT_004f1118,
    { 0x10, 0x01, 0x04, 0x80 },
    (void *)&grim_def_DAT_004f1104,
    { 0x78, 0x00, 0x78, 0x88 },
    (void *)&grim_def_DAT_004f10f4,
    { 0x01, 0x40, 0x00, 0x80 },
    (void *)&grim_def_DAT_004f10e0,
    { 0x46, 0x00, 0x78, 0x88 },
    (void *)&grim_def_DAT_004f10c8,
    { 0x0e, 0x00, 0x07, 0x80 },
    (void *)&grim_def_DAT_004f10b4,
    { 0xa0, 0x00, 0x78, 0x88 },
    (void *)&grim_def_DAT_004f109c,
    { 0xaa, 0x00, 0x78, 0x88 },
    (void *)&grim_def_DAT_004f1088
};
/* 0x004f3f94, 4 bytes */ GRIM_DATA("004f3f94") int grim_def_g_nStreamLastBlock __asm__("_g_nStreamLastBlock") = -1;
static unsigned char grim_anchor_004f40f8[0] __attribute__((section(".data$grim_004f40f8"), aligned(16), used));
static unsigned char grim_pad_004f40f8[8] __attribute__((section(".data$grim_004f40f8_"), aligned(4), used));
/* 0x004f40f8, 96 bytes */ GRIM_DATA("004f40f8z") unsigned int grim_def_g_dwWaveMixCount __asm__("_g_dwWaveMixCount") = 0x4;
/* 0x004f40fc, 92 bytes: the rest of grim_def_g_dwWaveMixCount's span */ GRIM_DATA("004f40f8z") static unsigned char g_dwWaveMixCount__tail[92] __attribute__((used)) = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0x06, 0x08, 0x0a, 0x0c, 0x0e, 0x10, 0x12, 0x13, 0x14,
    0x15, 0x16, 0x17, 0x18, 0x18, 0x19, 0x1a, 0x1a, 0x1b, 0x1c, 0x1c, 0x1d, 0x1e, 0x1e, 0x1f, 0x1f,
    0x20, 0x20, 0x20, 0x20, 0x00, 0x01, 0x02, 0x05, 0x07, 0x14, 0x23, 0x32, 0x41, 0x50, 0x55, 0x5a,
    0x5f, 0x64, 0x69, 0x6e, 0x70, 0x72, 0x74, 0x76, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
    0x80, 0x80, 0x80, 0x80, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01
};
/* 0x004f4158, 136 bytes */ GRIM_DATA("004f4158") grim_span_004f4158 grim_def_s_C__grimsrc_libs_lecsmush_insane__004f4158 __asm__("_s_C__grimsrc_libs_lecsmush_insane__004f4158") = {
    {
            0x43, 0x3a, 0x5c, 0x67, 0x72, 0x69, 0x6d, 0x73, 0x72, 0x63, 0x5c, 0x6c, 0x69, 0x62, 0x73, 0x5c,
            0x6c, 0x65, 0x63, 0x73, 0x6d, 0x75, 0x73, 0x68, 0x5c, 0x69, 0x6e, 0x73, 0x61, 0x6e, 0x65, 0x5c,
            0x73, 0x6f, 0x75, 0x72, 0x63, 0x65, 0x5c, 0x73, 0x6f, 0x75, 0x6e, 0x64, 0x5c, 0x4d, 0x69, 0x78,
            0x65, 0x72, 0x2e, 0x63, 0x00, 0x00, 0x00, 0x00, 0x04, 0x66, 0x6d, 0x6f, 0x64, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x16
    },
    (void *)f_FUN_004d54b4,
    { 0x76, 0x4b, 0x4b },
    (void *)f_FUN_004b4b0f,
    { 0x76, 0x4b, 0x4b },
    (void *)f_FUN_004b4ad4,
    { 0x76, 0x4b, 0x4b },
    (void *)f_FUN_004b4b0f,
    { 0x76, 0x4b, 0x4b },
    (void *)f_FUN_004b4b0d,
    (void *)f_FUN_004b4b0d,
    { 0x37, 0x4b, 0x4b },
    (void *)f_FUN_004b4b0d,
    { 0x76, 0x4b, 0x4b, 0x00, 0x76, 0x4b, 0x4b },
    (void *)f_FUN_004b4b0f,
    { 0x76, 0x4b, 0x4b }
};
/* 0x008d3654, 4 bytes */ GRIM_DATA("008d3654") unsigned int grim_def_UINT_008d3654 __asm__("_UINT_008d3654") = 0x0;
/* 0x008d3658, 4 bytes */ GRIM_DATA("008d3658") unsigned int grim_def_UINT_008d3658 __asm__("_UINT_008d3658") = 0x0;
/* 0x008d3660, 4 bytes */ GRIM_DATA("008d3660") unsigned int grim_def_UINT_008d3660 __asm__("_UINT_008d3660") = 0x0;
/* 0x008d3664, 12 bytes */ GRIM_DATA("008d3664") unsigned char grim_def_UINT_008d3664[12] __asm__("_UINT_008d3664") = {0};
/* 0x008d3670, 4 bytes */ GRIM_DATA("008d3670") unsigned char grim_def_g_pDSoundPrimary[4] __asm__("_g_pDSoundPrimary") = {0};
/* 0x008d3674, 12 bytes */ GRIM_DATA("008d3674") unsigned char grim_def_PTR_008d3674[12] __asm__("_PTR_008d3674") = {0};
/* 0x008db418, 4 bytes */ GRIM_DATA("008db418") unsigned char grim_def_DAT_008db418[4] __asm__("_DAT_008db418") = {0};
/* 0x008db428, 4 bytes */ GRIM_DATA("008db428") unsigned int grim_def_UINT_008db428 __asm__("_UINT_008db428") = 0x0;
/* 0x008db438, 6144 bytes */ GRIM_DATA("008db438") unsigned char grim_def_UINT_008db438[6144] __asm__("_UINT_008db438") = {0};
/* 0x008dcc60, 4 bytes */ GRIM_DATA("008dcc60") unsigned int grim_def_g_dwMixer_outChannelCount __asm__("_g_dwMixer_outChannelCount") = 0x0;
/* 0x008dcc64, 12 bytes */ GRIM_DATA("008dcc64") unsigned char grim_def_g_pMixer_softLTable[12] __asm__("_g_pMixer_softLTable") = {0};
/* 0x008dcc70, 8 bytes */ GRIM_DATA("008dcc70") unsigned char grim_def_DAT_008dcc70[8] __asm__("_DAT_008dcc70") = {0};
/* 0x008dcc78, 292 bytes */ GRIM_DATA("008dcc78") unsigned char grim_def_DAT_008dcc78[292] __asm__("_DAT_008dcc78") = {0};
/* 0x008dcd9c, 4 bytes */ GRIM_DATA("008dcd9c") unsigned int grim_def_g_dwMixer_mixBufSize __asm__("_g_dwMixer_mixBufSize") = 0x0;
/* 0x008dcda0, 16 bytes */ GRIM_DATA("008dcda0") int grim_def_INT_008dcda0 __asm__("_INT_008dcda0") = 0;
/* 0x008dcda4, 12 bytes: the rest of grim_def_INT_008dcda0's span */ GRIM_DATA("008dcda0") static unsigned char INT_008dcda0__tail[12] __attribute__((used)) = {0};
/* 0x008dcdb0, 8 bytes */ GRIM_DATA("008dcdb0") unsigned char grim_def_g_pMixer_mixBuf[8] __asm__("_g_pMixer_mixBuf") = {0};
