#!/bin/bash
# Install the example mod into a mod directory (see docs/MODDING.md, example mod c).
#   mods/magenta_manny/install.sh <moddir> [installdir]
set -e
HERE="$(cd "$(dirname "$0")" && pwd)"; ROOT="$HERE/../.."
DIR="$1"; INST="${2:-C:/GOG Games/GRIMDATA}"
[ -n "$DIR" ] || { echo "usage: $0 <moddir> [installdir]"; exit 1; }
# the original script, precompiled Lua 3.1, comes out of the game's own archive (not redistributed here)
python -I "$ROOT/tools/lab.py" extract "$INST/DATA000.LAB" _local.LUA "$DIR"
mv -f "$DIR/_local.LUA" "$DIR/_local_orig.lua"
cp "$HERE/_local.lua" "$DIR/_local.lua"
echo "installed: $DIR/_local.lua (+ _local_orig.lua)"
