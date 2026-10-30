#!/bin/bash
# after Ghidra edits: re-export what changed, check the names, regenerate the assembly selection and src/, build everything
# usage: build/mixdiff/regen.sh [nolink]
export PATH=/ucrt64/bin:$PATH
cd "$(dirname "$0")/../.." || exit 1
python -I tools/export_changed.py GRIMFANDANGO.EXE 2>&1 | tail -2
python -I build/mixdiff/checknames.py names/mixer_names.json names/mixer_protos.json 2>&1 | tail -8
python -I tools/gen_asm.py GRIMFANDANGO.EXE --select 2>&1 | tail -1
python -I tools/build_src.py 2>&1 | grep -i "Traceback\|Error" 
[ "$1" = nolink ] && exit 0
python -I tools/gen_asm.py GRIMFANDANGO.EXE 2>&1 | grep -i "Traceback\|skipped"
cd build && make link -j14 2>&1 | grep -i "error\|does not compile\|LINKED\|undefined" | grep -v "^  CC" | grep -v 'LUA.DLL\|IMUSE.DLL\|CHORE.DLL'
