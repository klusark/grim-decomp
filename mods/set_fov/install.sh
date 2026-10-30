#!/bin/bash
# Override a set file with a loose copy: Manny's office, first camera setup (mo_ddtws), field of view 75 -> 45 degrees.
#   mods/set_fov/install.sh <moddir> [installdir]
set -e
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
DIR="$1"; INST="${2:-C:/GOG Games/GRIMDATA}"
[ -n "$DIR" ] || { echo "usage: $0 <moddir> [installdir]"; exit 1; }
python -I "$ROOT/tools/lab.py" extract "$INST/DATA001.LAB" mo.set "$DIR"
python -I - "$DIR/mo.set" <<'PY'
import sys
p = sys.argv[1]
s = open(p, newline="").read()
old = "fov\t\t75.178040"          # first occurrence = setup mo_ddtws
assert old in s
open(p, "w", newline="").write(s.replace(old, "fov\t\t45.000000", 1))
PY
echo "installed: $DIR/mo.set"
