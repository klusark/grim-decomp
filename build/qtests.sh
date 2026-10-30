#!/bin/sh
# quick regression subset (unit + walk + coll) on this tree's build/run; full suite = rebuilt_all.sh
# usage: build/qtests.sh [tiers...]   default: unit walk coll
AR=/c/Users/Joel/grim_tools/autorun
export REBUILT_DIR="${REBUILT_DIR:-/c/Users/Joel/grim-agentI/build/run}"
EXTRA="nav_known.lua nav_coll_expect.lua nav_slide_expect.lua rules_expect.lua rules_known.lua"
cd "$AR"
tiers="${*:-unit walk coll}"
for name in $tiers; do
	{ echo "AR_NT_TIERS = { $name = 1, }"; cat $EXTRA test_nav.lua; } > logs/rt${QT_TAG:-I}_$name.lua
	sh rebuilt_test.sh "$AR/logs/rt${QT_TAG:-I}_$name.lua" 1800 "$AR/logs/rebuilt${QT_TAG:-I}_$name.log" | tail -1
	echo "$name: $(grep -ac "NAVTEST $name .*PASS" logs/rebuilt${QT_TAG:-I}_$name.log) pass, $(grep -ac "NAVTEST $name .* FAIL" logs/rebuilt${QT_TAG:-I}_$name.log) fail"
done
