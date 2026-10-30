#!/bin/bash
# imbuild.sh [destdir]: regenerate + build IMUSE.DLL only, copy imuse.dll to destdir (default build/run)
export PATH=/ucrt64/bin:$PATH
cd /c/Users/Joel/grim-agentN || exit 1
python -I tools/gen_asm.py IMUSE.DLL --select 2>&1 | grep -i "Traceback\|Error" 
python -I tools/build_src.py > /tmp/bs_N.log 2>&1 || { echo build_src failed; tail /tmp/bs_N.log; exit 1; }
cd build
make objs -j14 > /tmp/mk_N.log 2>&1 || { echo make failed; grep -i 'error' /tmp/mk_N.log | head; exit 1; }
python -I link.py /mingw32/bin/gcc ../src obj IMUSE.DLL 2>&1 | grep -i 'error\|LINKED\|undefined' 
grep -i "FAIL|stubbed" /tmp/mk_N.log | head
cp obj/IMUSE.DLL/imuse.dll "${1:-/c/Users/Joel/grim-agentN/build/run}/imuse.dll"
