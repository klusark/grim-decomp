#!/bin/bash
# usage: build/difftest/big_engine_renderframe/mutate.sh
# Sensitivity check of renderframe_test: deliberately wrong copies of the port must give differences.
cd "$(dirname "$0")/../../.." || exit 1
T=build/difftest/big_engine_renderframe; W=$T/out; S=build/overrides_big_engine_renderframe.c; mkdir -p $W
mut() {
  name=$1
  python3 - "$S" "$W/mut_$name.c" "$2" "$3" <<'E' || return
import sys
s = open(sys.argv[1]).read(); old, new = sys.argv[3], sys.argv[4]
if old not in s: sys.exit("pattern not found: " + old)
open(sys.argv[2], 'w').write(s.replace(old, new, 1))
E
  echo "$name: $(OVERRIDE=$W/mut_$name.c bash $T/run.sh 30000 2>&1 | grep -o '[0-9]* differences')"
  rm -f $W/mut_$name.c
}
mut signed_diff '(long double)(unsigned long long)diff' '(long double)(long long)(int)diff'
mut no_rect_height 'rect[2] = 0x280; rect[3] = 0x1e0;
            if (cnt' 'rect[2] = 0x280;
            if (cnt'
mut nan_compare 'if (!(v > 1.0L))' 'if (v <= 1.0L)'
mut float_quotient 'volatile long double v = (long double)(unsigned long long)diff / (long double)g_flIrisDuration;' 'volatile float vf = (float)((long double)(unsigned long long)diff / (long double)g_flIrisDuration); volatile long double v = vf;'
mut list_forward 'entry = (byte *)list[k - 1];' 'entry = (byte *)list[n - k];'
mut scale_not_reread 'if (ER_U32(actor, 0x30) != 0x3f800000) {
                /* fld' 'if (vec[0] != 0x3f800000) {
                /* fld'
mut colormap_not_reread '                    cm = ER_PTR(actor, 0);
                    if (*(int *)cm == 0)' '                    if (*(int *)cm == 0)'
mut buffer_count_cached 'while (n < g_nNumPages);' 'while (n < cnt);'
mut sector_debug_no_arg '((void (__cdecl *)(void *))Sector_DrawAllDebug)(sputRoom_GetCurrentRoom())' 'Sector_DrawAllDebug()'
mut lights_bit 'g_dwDebugFlags & 2) != 0)
            Set_DrawDebugLights' 'g_dwDebugFlags & 1) != 0)
            Set_DrawDebugLights'
mut mode3_clears_pending '        sputRender_PageFlip();
        return;' '        sputRender_PageFlip();
        g_nSputRender_Reset = 0;
        return;'
