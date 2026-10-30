#!/bin/bash
# quick differential battery of build/run_t against build/ref: boot+render (t2), movement (t3), Lua API probes, set tour
# usage: oracles.sh   (prints one summary line per oracle; run from anywhere)
cd "$(dirname "$0")" || exit 1
rm -rf out/probe_t out/tour_t.log.shots out/t3_t.log out/t2_t.log
bash run_lua.sh ../run_t ia t2.lua out/t2_t.log 60 >/dev/null; echo "t2 (actors drawn): $(grep -a RECT out/t2_t.log)"
bash run_lua.sh ../run_t ia t3.lua out/t3_t.log 90 >/dev/null; echo "t3 (movement): $(diff out/t3_ref.log out/t3_t.log | grep -c '^<') differing lines"
python -I run_probe.py ../run_t out/probe_t 3 @../../.scratch/probe_funcs.txt > out/probe_t.txt 2>&1
echo "probes: $(python -I cmpprobe.py out/probe_ref out/probe_t | grep '^==' | grep -v 'GetActorNodeLocation\|GetActorRect' | tr '\n' ' ')"
bash run_lua.sh ../run_t ia tour.lua out/tour_t.log 120 >/dev/null; echo "tour: $(python -I cmpshots.py out/tour_ref.log.shots out/tour_t.log.shots | tail -1)"
rm -rf out/t7_t.log.shots; bash run_lua.sh ../run_t ia t7.lua out/t7_t.log 90 >/dev/null; echo "t7 (primitives): $(python -I cmpshots.py out/t7_ref.log.shots out/t7_t.log.shots | tail -1)"
