#!/bin/bash
# Builds and runs every differential test of build/overrides_asm_o2.c and build/overrides_asm_o2_chore.c against the
# original machine code (sliced from the current src/<PROG>/asm_funcs.s, where these functions are still assembled;
# after the conversion is applied by the build, point BASE_ASM at an older copy of asm_funcs.s).
# Data images: build/obj/<PROG>/data_s.o of a build of the tree.  usage: build/difftest/asm_s5/run_all.sh [quick]
cd "$(dirname "$0")/../../.." || exit 1
d=1; [ "$1" = quick ] && d=20
B=build/difftest/asm_s5/build.sh; T=build/difftest/asm_s5; O=$T/out
E=build/obj/GRIMFANDANGO.EXE
EXTRA_OBJ="$E/rle.o $E/stdgif.o" bash $B $T/small_test.c $O/small_test.exe FUN_004d5fd0 FUN_004d5e50 FUN_004d5f70 Rle_Decode MaterialInstanceSaveLoad stdGif_LzwInitEncoder stdGif_LzwEncodePixel >/dev/null && $O/small_test.exe $((3000/d))
bash $B $T/dx_test.c $O/dx_test.exe Input_PollKeyboard Input_PollMouse Input_FlushJoystick std3D_DrawRenderList D3D_CreateViewport >/dev/null && $O/dx_test.exe $((50000/d)) | tail -1
bash $B $T/cos_test.c $O/cos_test.exe ThingInstancer SpriteInstancer >/dev/null && $O/cos_test.exe $((200000/d))
bash $B $T/lua_test.c $O/lua_test.exe sputLua_Startup >/dev/null && $O/lua_test.exe $((5000/d)) | tail -1
bash $B $T/display_test.c $O/display_test.exe FUN_004761b0 stdDisplay_TextOut D3D_InitRenderState DDraw_CreateSurfaces >/dev/null && $O/display_test.exe $((40000/d))
bash $B $T/sector_test.c $O/sector_test.exe Sector_ContainsPoint >/dev/null && $O/sector_test.exe $((3000000/d)) | tail -1
N="rdRaster_Span16_TexLitZw"; for k in 2 3 4 5 6 7 8 15 16 17 18 19 20 21 22 24 25 26 27 28 29 30; do N="$N rdRaster_Span16_TexLitZw_$k"; done
bash $B $T/span_test.c $O/span_test.exe $N >/dev/null && $O/span_test.exe $((460000/d))
PROG=CHORE.DLL DEF=GRIM_CHORE OVERRIDES=build/overrides_asm_o2_chore.c EXTRA_OBJ="build/obj/CHORE.DLL/costume.o build/obj/CHORE.DLL/lib_alias.o build/obj/CHORE.DLL/overrides.o" \
  bash $B $T/chore_test.c $O/chore_test.exe Cos_LoadEntry FUN_100041e0 FUN_10004390 FUN_100047f0 FUN_10004970 >/dev/null && $O/chore_test.exe $((100000/d)) | tail -1
