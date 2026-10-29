"""Corrections to function names that Ghidra's export gets wrong (the Ghidra names were matched against the
EXE's C runtime by structure and, in LUA.DLL, the case-conversion functions came out swapped).

The build links the host C runtime instead of the decompiled one, so a wrong CRT name is a wrong
behaviour: LUA.DLL's `%d` pattern class called "toupper" (really tolower at 0x10012770), the host
toupper turned the class letter into 'D', no class matched, and string.format/strfind/gsub with
character classes failed. Names are only changed when raw/ still carries the wrong one, so a
re-export with corrected Ghidra names keeps working (and the corrected names in names/*.json
belong in Ghidra too)."""
import json
import os
import re

# address -> (wrong name in raw/, right name)
NAME_FIXES = {
    "LUA.DLL": {
        "10011bc0": ("tolower", "toupper"),         # SUB EAX,0x20 for 'a'..'z'
        "10011c50": ("_tolower_lk", "_toupper_lk"),
        "10012770": ("toupper", "tolower"),         # ADD EAX,0x20 for 'A'..'Z'
        "10012800": ("_toupper_lk", "_tolower_lk"),
        "10020870": ("toupper", "wtoupper"),        # the 16-bit versions (not towupper: that name clashes with wchar.h)
        "10020900": ("_toupper_lk", "_wtoupper_lk"),
    },
}
# names whose text occurrences swap (the two names of the 8-bit functions)
TEXT_SWAP = {"LUA.DLL": ("toupper", "tolower", "_toupper_lk", "_tolower_lk")}


def load_functions(rawdir, prog):
    funcs = json.load(open(os.path.join(rawdir, "functions.json")))
    fixes = NAME_FIXES.get(prog, {})
    by_addr = {f["address"]: f for f in funcs}
    applied = {a for a, (old, new) in fixes.items() if a in by_addr and by_addr[a]["name"] == old}
    if applied:
        for a in applied:
            by_addr[a]["name"] = fixes[a][1]
    return funcs, bool(applied)


def fix_text(prog, text, active):
    if not active or prog not in TEXT_SWAP:
        return text
    a, b, c, d = TEXT_SWAP[prog]
    pat = re.compile(r"\b(%s|%s|%s|%s)\b" % (a, b, c, d))
    swap = {a: b, b: a, c: d, d: c}
    return pat.sub(lambda m: swap[m.group(1)], text)


# function files whose own names are the 16-bit ones (not part of the 8-bit swap)
WIDE_FILES = {"LUA.DLL": {"10020870.c": {"toupper": "wtoupper", "_toupper_lk": "_wtoupper_lk"},
                          "10020900.c": {"toupper": "wtoupper", "_toupper_lk": "_wtoupper_lk"}}}


def fix_file_text(prog, path, text, active):
    if active:
        ren = WIDE_FILES.get(prog, {}).get(os.path.basename(path))
        if ren:
            text = re.sub(r"\b(%s)\b" % "|".join(ren), lambda m: ren[m.group(1)], text)
            return text
    return fix_text(prog, text, active)
