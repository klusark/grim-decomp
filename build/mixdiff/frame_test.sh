#!/bin/bash
# builds and runs the Blocky16_DecodeFrame differential test.  The frame decoder calls Blocky16_DecodeBlocks, which lives in
# the same object file; the test needs that call to reach the recorder, so it builds from a copy in which the definition
# is renamed (a call inside one object file binds to the definition in it).   usage: frame_test.sh [cases]
cd "$(dirname "$0")/../.." || exit 1
mkdir -p build/mixdiff/out
sed 's/^void Blocky16_DecodeBlocks(byte/void Blocky16_DecodeBlocks_unused(byte/' build/overrides_mixer_codec.c > build/mixdiff/out/overrides_frame.c
OVERRIDES=build/mixdiff/out/overrides_frame.c bash build/mixdiff/build.sh build/mixdiff/frame_test.c build/mixdiff/out/frame_test.exe FUN_004ccd00 2>&1 | tail -3
build/mixdiff/out/frame_test.exe ${1:-100000}
