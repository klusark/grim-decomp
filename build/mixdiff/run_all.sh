#!/bin/bash
# Builds and runs every differential test of the mixer / Smush work (original machine code from the BASELINE assembly against
# the C of build/overrides_mixer*.c).  The baseline assembly is src/GRIMFANDANGO.EXE/asm_funcs.s of the last commit before the
# conversion (git show 223e097:src/GRIMFANDANGO.EXE/asm_funcs.s > /tmp/asm_funcs_base.s), BASE_ASM points at it.
# The data image is build/obj/GRIMFANDANGO.EXE/data_s.o (a build of the current tree).
# usage: build/mixdiff/run_all.sh [quick]      (quick: 1/20 of the cases)
cd "$(dirname "$0")/../.." || exit 1
export BASE_ASM=${BASE_ASM:-/tmp/asm_funcs_base.s}
[ -f "$BASE_ASM" ] || git show 223e097:src/GRIMFANDANGO.EXE/asm_funcs.s > "$BASE_ASM"
div=1; [ "$1" = quick ] && div=20
B=build/mixdiff/build.sh; O=build/mixdiff/out
run() { exe=$1; shift; echo "== $exe"; "$@"; }
unset ORIG_SED EXTRA_CFLAGS
OVERRIDES=build/overrides_mixer.c bash $B build/mixdiff/mix_test.c $O/mix_test.exe Mixer_Mix16Mono Mixer_Mix16MonoLR Mixer_Mix8Mono Mixer_Mix8MonoLR Mixer_MixStereoLR_A Mixer_MixStereoLR_B Mixer_MixStereo_A Mixer_MixStereo_B > /dev/null && run mix_test $O/mix_test.exe $((3000000/div))
OVERRIDES=build/overrides_mixer.c bash $B build/mixdiff/mixcore_test.c $O/mixcore_test.exe FUN_004d2d40 FUN_004d2d90 FUN_004d2e80 FUN_004d2fb0 Mixer_ClearAccumulator Mixer_ConvertTo16 Mixer_MixVoice > /dev/null && run mixcore_test $O/mixcore_test.exe $((1000000/div))
OVERRIDES=build/overrides_mixer_drv.c bash $B build/mixdiff/timer_test.c $O/timer_test.exe FUN_004cdc90 FUN_004cdce0 FUN_004cdd10 FUN_004cdd60 FUN_004cdd80 FUN_004cde80 FUN_004cdef0 FUN_004cdf00 FUN_004cdf10 FUN_004cdf80 FUN_004cdfa0 FUN_004cdfd0 Mixer_ScheduleVoices Mixer_ServiceVoices Mixer_TimerThread Mixer_Update > /dev/null && run timer_test $O/timer_test.exe $((300000/div))
OVERRIDES=build/overrides_mixer_drv.c bash $B build/mixdiff/drv_test.c $O/drv_test.exe DSound_FillStreamBuffer DSound_GetPlayBlock DSound_SetPrimaryVolume DSound_Shutdown FUN_004c3df0 FUN_004c3e10 FUN_004d23e0 FUN_004d2400 FUN_004d2420 FUN_004d2480 FUN_004d24b0 FUN_004d2520 FUN_004d2550 FUN_004d25f0 FUN_004d2630 FUN_004d27b0 FUN_004d27c0 FUN_004d2940 FUN_004d2aa0 FUN_004d2bf0 FUN_004d2cb0 FUN_004d2ce0 > /dev/null && run drv_test $O/drv_test.exe $((300000/div))
OVERRIDES=build/overrides_mixer_snd.c bash $B build/mixdiff/snd_test.c $O/snd_test.exe FUN_004d0300 FUN_004d03a0 FUN_004d03d0 FUN_004d0510 FUN_004d0550 FUN_004d0610 FUN_004d06a0 FUN_004d0860 FUN_004d0a50 FUN_004d0a80 FUN_004d0a90 FUN_004d0aa0 FUN_004d0ad0 FUN_004d0b10 FUN_004d0b60 FUN_004d0b90 FUN_004d0bd0 FUN_004d0bf0 FUN_004d0c00 FUN_004d0c30 FUN_004d0d70 FUN_004d0e00 FUN_004d0eb0 FUN_004d0ed0 FUN_004d0f00 FUN_004d1180 FUN_004d1690 FUN_004d16a0 FUN_004d2340 Sound_VoiceSampleCount > /dev/null && run snd_test bash build/mixdiff/run_resume.sh $O/snd_test.exe $((20000/div))
OVERRIDES=build/overrides_mixer_video.c bash $B build/mixdiff/video_test.c $O/video_test.exe FUN_004ce3e0 FUN_004cedc0 FUN_004cf010 FUN_004cf520 FUN_004cfdb0 FUN_004cfdf0 FUN_004cfea0 FUN_004cff60 FUN_004cffe0 FUN_004d0070 FUN_004d00f0 FUN_004d0180 FUN_004d01f0 FUN_004d0260 > /dev/null && run video_test $O/video_test.exe $((200000/div))
OVERRIDES=build/overrides_mixer_codec.c bash $B build/mixdiff/codec_test.c $O/codec_test.exe FUN_004cc250 FUN_004cc7d0 FUN_004cd550 FUN_004cd610 FUN_004cd9b0 FUN_004cdb80 > /dev/null && for g in 0 1 2; do ONLY=$g run codec_test $O/codec_test.exe $((300000/div)); done
run frame_test bash build/mixdiff/frame_test.sh $((1000000/div))
ORIG_SED='s/_strncpy/_test_strncpy/g; s/_malloc/_test_malloc/g; s/__errno/__test_errno/g' EXTRA_CFLAGS='-Dstrncpy=test_strncpy -Dmalloc=test_malloc -D_errno=test_errno' OVERRIDES=build/overrides_mixer_misc.c bash $B build/mixdiff/misc_test.c $O/misc_test.exe Smush_SetFile LightEd_ReadControl FUN_004bffb0 LecShare_Resolve FUN_004c23c0 FUN_004c2690 FUN_004c27a0 FUN_004c36b0 FUN_004c3d30 gz_open gz_putLong FUN_004c5ab0 FUN_004c5e30 FUN_004c5f50 > /dev/null && run misc_test $O/misc_test.exe $((2000000/div))
