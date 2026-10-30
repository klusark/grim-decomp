#!/bin/bash
# Create a mod working directory: the game is started with this directory as its working directory, which makes it the
# highest-priority resource directory (see docs/MODDING.md, "Where the game finds its files"). The LAB archives stay in
# the installation (registry value GrimDataDir); only the audio libraries the engine loads from its working directory
# are copied.
#   tools/mkmoddir.sh <dir> [INSTALLDIR]
set -e
DIR="$1"; INST="${2:-C:/GOG Games/GRIMDATA}"
[ -n "$DIR" ] || { echo "usage: $0 <dir> [installdir]"; exit 1; }
mkdir -p "$DIR"
for f in HMIFXLIB.DLL HMIFXFP.DLL HMILIBS.INI IMUSE.PSL; do cp -n "$INST/$f" "$DIR/"; done
echo "mod directory ready: $DIR"
