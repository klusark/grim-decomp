#!/bin/bash
# Builds and runs the differential test; usage: build/difftest/big_collision_others/run.sh [cases] [seed]
cd "$(dirname "$0")/../../.." || exit 1
bash build/difftest/big_collision_others/build.sh >/dev/null && build/difftest/big_collision_others/out/coll_test.exe ${1:-300000} ${2:-}
