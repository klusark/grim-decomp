#!/bin/bash
# mutate.sh [cases]: sensitivity check of r1_test - each mutant of build/overrides_imuse_r1.c changes one detail (a stack word
# the original passes to ImSetTrigger, a rounding / compare point) and must be caught.
cd "$(dirname "$0")/../../.."
N=${1:-200000}
M=build/difftest/imuse_r1/out/mut; mkdir -p $M
i=0
while IFS='|' read -r from to; do
  i=$((i+1))
  python -I -c "import sys; t=open('build/overrides_imuse_r1.c').read(); a,b=sys.argv[1],sys.argv[2]; assert t.count(a)>=1, a; open(sys.argv[3],'w',newline='\n').write(t.replace(a,b,1))" "$from" "$to" $M/m$i.c || continue
  OVR=$M/m$i.c bash build/difftest/imuse_r1/build.sh $M/m$i.exe > /dev/null 2>&1 || { echo "m$i: does not build"; continue; }
  r=$($M/m$i.exe $N | tail -n 1)
  echo "m$i [$from -> $to]: $r"
done <<'EOF'
0xffffffffu, 0x100065f3u|0xffffffffu, 0x100065f4u
Im_SetSequence(0, 0);|Im_SetSequence(0, 0xffffffffu);
(int)((uint)fade * 3u) / 50|(int)((uint)fade * 3u) / 49
if (hook == 100)|if (hook == 99)
ImSetTrigger(old, mk, 0xc, snd, 0x400, 4, 0, 0, 0, 0, 0, 0, fade);|ImSetTrigger(old, mk, 0xc, snd, 0x400, 4, 0, 0, 0, 0, 0, 0, hook);
ImSetTrigger(old, s_clear_1001e7f4, 0xf, old, 0x80, 0, 0, 0, 0, 0, 0, 0, no_attr);|ImSetTrigger(old, s_clear_1001e7f4, 0xf, old, 0x80, 0, 0, 0, 0, 0, 0, 0, fade);
*(int *)(entry + 0x44) > 1)|*(int *)(entry + 0x44) >= 1)
case 5:|case 15:
EOF
