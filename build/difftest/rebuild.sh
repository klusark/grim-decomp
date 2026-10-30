#!/bin/bash
# regenerate assembly selection + sources, build, copy to build/run_t   (usage: rebuild.sh)
export PATH=/ucrt64/bin:$PATH
cd "$(dirname "$0")/../.." || exit 1
python -I tools/gen_asm.py GRIMFANDANGO.EXE --select 2>&1 | grep -i "functions written\|skipped\|Traceback\|Error" 
python -I tools/build_src.py 2>&1 | grep -i "Traceback\|Error\|stubbed" 
python -I tools/gen_asm.py GRIMFANDANGO.EXE 2>&1 | grep -i "skipped\|Traceback"
cd build && make link -j14 2>&1 | grep -i "error\|does not compile\|LINKED\|undefined" | grep -v "^  CC"
cd ..
cp build/obj/GRIMFANDANGO.EXE/grimfandango.exe build/obj/LUA.DLL/lua.dll build/obj/IMUSE.DLL/imuse.dll build/obj/CHORE.DLL/chore.dll build/run_t/
