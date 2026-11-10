#!/bin/bash
# Mutation check of the s1 differential test: each mutant of build/overrides_s1_chore.c must make s1_test fail.
cd "$(dirname "$0")/../../.."
W=build/difftest/s1/out; mkdir -p $W
mut() {   # mut <name> <sed expression>
  sed -E "$2" build/overrides_s1_chore.c > $W/mut_$1.c
  cmp -s build/overrides_s1_chore.c $W/mut_$1.c && { echo "$1: sed did not apply"; return; }
  OVR=$W/mut_$1.c bash build/difftest/s1/build.sh $W/mut_$1.exe > /dev/null 2>&1 || { echo "$1: does not build"; return; }
  if $W/mut_$1.exe 200000 7 > $W/mut_$1.txt; then echo "$1: NOT caught"; else echo "$1: caught ($(cat $W/mut_$1.txt))"; fi
}
mut init_from_used   's/for \(i = old; i < S1_COS_SIZE/for (i = S1_COS_USED; i < S1_COS_SIZE/'
mut inst_from_used   's/for \(i = old; i < S1_INST_SIZE/for (i = S1_INST_USED; i < S1_INST_SIZE/'
mut return_old       '0,/    i = S1_COS_USED;/s//    i = old < S1_COS_USED ? old : S1_COS_USED;/'
mut grow_16          '0,/S1_COS_SIZE = S1_COS_SIZE \+ 8;/s//S1_COS_SIZE = S1_COS_SIZE + 16;/'
mut no_count         '0,/S1_COS_USED = S1_COS_USED \+ 1;/s//;/'
mut flag_2           '0,/\+ 0x38\) = 1;/s//+ 0x38) = 2;/'
mut first_free_last  's/for \(i = 0; i < S1_INST_SIZE; i\+\+\)/for (i = S1_INST_SIZE - 1; i >= 0; i--)/'
