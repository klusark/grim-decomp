"""Collect the decorated stdcall names (`_CreateFileA@28`) of the Win32/DirectX
import libraries into build/stdcall_names.json.

tools/build_src.py declares each Win32 import with that exact asm label, so the
decompiled code's calls bind to the import library without relying on the
linker's fuzzy stdcall fix-up (which cannot look inside archive members).

usage: python -I gen_stdcall_names.py [/mingw32/lib]"""
import json
import os
import re
import subprocess
import sys

LIBS = ["kernel32", "user32", "gdi32", "winmm", "ddraw", "dinput", "dinput8", "dsound",
        "advapi32", "comdlg32", "ole32", "shell32", "version", "comctl32"]
here = os.path.dirname(os.path.abspath(__file__))
libdir = sys.argv[1] if len(sys.argv) > 1 else "/mingw32/lib"
if not os.path.isdir(libdir):  # a native-Windows python/nm does not see MSYS paths
    try:
        libdir = subprocess.run(["cygpath", "-m", libdir], capture_output=True, text=True).stdout.strip() or libdir
    except OSError:
        pass
names = {}
for lib in LIBS:
    path = os.path.join(libdir, "lib%s.a" % lib)
    if not os.path.exists(path):
        continue
    out = subprocess.run(["nm", path], capture_output=True, text=True).stdout
    for m in re.finditer(r"\bT\s+_(\w+)@(\d+)\s*$", out, re.M):
        names.setdefault(m.group(1), "_%s@%s" % (m.group(1), m.group(2)))
for n, b in (("InterlockedIncrement", 4), ("InterlockedDecrement", 4), ("InterlockedExchange", 8)):
    names.setdefault(n, "_%s@%d" % (n, b))
json.dump(names, open(os.path.join(here, "stdcall_names.json"), "w"), indent=0, sort_keys=True)
print(len(names), "decorated names")
