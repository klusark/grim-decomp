#!/bin/bash
# Sensitivity of fade_test (agent s2): each mutation of the original slice must give differences.  usage: mutate.sh [cases]
cd "$(dirname "$0")/../../.."
N=${1:-20000}; ok=0; all=0
while IFS= read -r m; do
  [ -z "$m" ] && continue
  all=$((all+1))
  MUTSED="$m" bash build/difftest/s2/build.sh build/difftest/s2/out/fade_mut.exe > /dev/null || { echo "build failed: $m"; continue; }
  r=$(build/difftest/s2/out/fade_mut.exe $N 3 | tail -1)
  echo "$m -> $r"; [ "$r" != "0 differences" ] && ok=$((ok+1))
done <<'M'
s/mov EBP,0x5$/mov EBP,0x4/
s/(10003cb0_10003d06:\t)jc/\1jl/
s/mov EAX,0x2aaaaaab/mov EAX,0x2aaaaaac/
s/setge DL/setg DL/
s/(10003cb0_10003d2b:\tcmp EAX,)0x600/\10x700/
s/(10003c70_10003c92:\tcmp ECX,)-0x1/\1-0x2/
s/(10003b40_10003b5b:\t)jl/\1jle/
s/(10003cb0_10003ce9:\t)jnz/\1jns/
M
echo "$ok of $all mutations caught"
