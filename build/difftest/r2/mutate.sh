#!/bin/bash
# Mutation check of build/difftest/r2: each mutation changes one instruction of the ORIGINAL (sliced) machine code; the
# tests must then report differences against the unchanged replacement (msvcrt _ftol / libgcc ___chkstk).
cd "$(dirname "$0")/../../.."
caught=0; total=0
run() {
  total=$((total + 1))
  if ORIG_SED="$2" bash build/difftest/r2/build.sh 20000 20000 300 10 > build/difftest/r2/out/mut.log 2>&1; then
    echo "NOT CAUGHT: $1"
  else
    if grep -q "Error:" build/difftest/r2/out/mut.log; then echo "BUILD FAILED: $1"; return; fi
    caught=$((caught + 1)); echo "caught: $1 ($(grep -c 'DIFF\|FAIL\|reference' build/difftest/r2/out/mut.log) difference lines$(grep -q 'Segmentation\|core dumped' build/difftest/r2/out/mut.log && echo ', the test process crashed'))"
  fi
}
run "_ftol rounds down instead of truncating"      's/or AH,0xc$/or AH,0x4/'
run "_ftol keeps the truncating control word"       '/4ac70c:/d'
run "_ftol leaves a copy of the value on the x87 stack" 's/^\(.L4ac6f0_4ac709:\t\)/\1fld st(0)\n\t/' 
run "_ftol returns only the low word"               's/mov EDX,dword ptr \[EBP+-0x8\]/xor EDX,EDX/'
run "__chkstk steps 8 KiB per probe"                's/^\(.L4addf0_4addfc:\tsub ECX,\)0x1000/\10x2000/'
run "__chkstk does not restore ECX"                 '/4ade18:/d'
run "__chkstk loop does not probe"                  '/4ade07:/d'
run "__chkstk skips the page loop"                  's/jc .L4addf0_4ade10/jmp .L4addf0_4ade10/'
echo "$caught of $total mutations caught"
