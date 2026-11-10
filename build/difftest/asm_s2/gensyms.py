"""usage: python -I gensyms.py <nm -u output> <out.s>
Defines every undefined symbol of the C under test as an absolute symbol at its GRIMFANDANGO.EXE address (from the
/* 0x... */ comments of src/GRIMFANDANGO.EXE/globals.h and functions.h, raw/GRIMFANDANGO.EXE/globals.json for
named globals, or the address in a DAT_/UINT_/PTR_ name)."""
import re, sys
addr = {}
for h in ("src/GRIMFANDANGO.EXE/globals.h", "src/GRIMFANDANGO.EXE/functions.h"):
    for line in open(h):
        m = re.search(r"\b([A-Za-z_]\w*)\s*(\[[^\]]*\])?\s*(\([^;]*\))?\s*;\s*/\*\s*0x([0-9a-fA-F]+)", line)
        if m:
            addr[m.group(1)] = int(m.group(4), 16)
# named globals whose declaration comment gives no address (a renamed DAT_ global: "used by N fn(s), ..."): the
# address from the export of the Ghidra project (raw/GRIMFANDANGO.EXE/globals.json, "<name> @ <addr> ...")
try:
    for line in open("raw/GRIMFANDANGO.EXE/globals.json"):
        m = re.match(r"^(\S+) @ ([0-9a-f]{8}) ", line)
        if m:
            addr.setdefault(m.group(1), int(m.group(2), 16))
except OSError:
    pass
out = []
for s in open(sys.argv[1]).read().split():
    if not s.startswith("_") and not s.startswith("@"):
        continue
    n = s[1:] if s.startswith("_") else s[1:].split("@")[0]
    n = re.sub(r"@\d+$", "", n)
    a = addr.get(n)
    if a is None:
        m = re.search(r"_([0-9a-fA-F]{8})$", n)
        if m and re.match(r"(DAT|UINT|INT|PTR|FLOAT|BYTE|WORD|DWORD|USHORT|SHORT|CHAR|UCHAR|s|u|pu|pp|p|f|d|BOOL|LONG|ULONG|FUN|LAB)", n):
            a = int(m.group(1), 16)
    if a is None:
        continue
    out.append("\t.globl %s\n\t.set %s, 0x%x\n" % (s, s, a))
open(sys.argv[2], "w", newline="\n").write("".join(out))
