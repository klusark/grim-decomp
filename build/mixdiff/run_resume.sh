#!/bin/bash
# Runs a differential test that can hang on a state the ORIGINAL code loops on forever (its watchdog prints
# "STUCK <case> cases <n> differences <d>" and exits with 3): restarts after the stuck case with another random
# sequence and adds the counts up.   usage: ONLY=13 run_resume.sh <test.exe> <total cases>
exe=$1; total=$2
start=0; cases=0; diffs=0; stuck=0
while true; do
  out=$(START=$start $exe $total 2>&1)
  rc=$?
  echo "$out" | grep -v '^STUCK\|^WATCHDOG\|cases [0-9]* *differences [0-9]*$' | head -30
  if [ $rc -eq 3 ]; then
    line=$(echo "$out" | grep '^STUCK')
    n=$(echo "$line" | awk '{print $2}'); c=$(echo "$line" | awk '{print $4}'); d=$(echo "$line" | awk '{print $6}')
    cases=$((cases + c)); diffs=$((diffs + d)); stuck=$((stuck + 1)); start=$((n + 1))
    [ $start -ge $total ] && break
  else
    line=$(echo "$out" | grep 'cases [0-9]* *differences [0-9]*$' | tail -1)
    c=$(echo "$line" | sed 's/.*cases \([0-9]*\).*/\1/'); d=$(echo "$line" | sed 's/.*differences \([0-9]*\)$/\1/')
    cases=$((cases + c)); diffs=$((diffs + d))
    break
  fi
done
echo "TOTAL cases $cases  differences $diffs  (original hung on $stuck generated states and was skipped)"
[ $diffs -eq 0 ]
