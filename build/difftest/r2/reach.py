"""Reachability evidence for round r2 (docs/notes/r2.md): run after `make -C build link`.
For the linked GRIMFANDANGO.EXE and LUA.DLL it prints
  1. every object that references one of the removed symbols (the funclets, FUN_0042003c, _ftol, FUN_004addf0);
  2. every instruction of the linked image that names their address (call, jmp, immediate);
  3. the exception tables that hold them (the _except_handler3 scope table, the C++ FuncInfo records) and every
     reference to those tables, in code (the rebuilt address as an immediate or displacement) and in the data image
     (data.s `_sect_rdata + off` / `_sect_data + off` entries);
  4. every SEH registration in the linked image (instructions that touch fs:[0] / load the TIB through fs:[0x18]).
usage: python -I build/difftest/r2/reach.py"""
import os
import re
import subprocess

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
OBJ = os.path.join(ROOT, "build", "obj")
GCC_BIN = "C:/msys64/mingw32/bin/"
PROGS = {
    "GRIMFANDANGO.EXE": dict(
        syms=["_FUN_004d5e1c", "_FUN_004d5e30", "_FUN_004d6030", "_FUN_004d6050", "_FUN_004d6070", "_FUN_004d6090",
              "_FUN_004d609e", "_FUN_004d60ac", "_FUN_004d60d0", "_FUN_004d60db", "_FUN_004d6100", "_FUN_0042003c",
              "@FUN_0042003c@8", "__ftol", "_FUN_004addf0"],
        rdata=0x4d7000, data=0x4dd000,
        # original table address -> what it is (parent, how the parent reached it)
        tables={0x4dac00: "scope table of FUN_004d5de0 (push 0x4dac00 / _except_handler3), funclets 4d5e1c 4d5e30",
                0x4dac10: "FuncInfo of PrimitiveList_Append (thunk 4d6046), funclets 4d6030 4d603b",
                0x4dac40: "FuncInfo of Actor_CreateWalker (thunk 4d605b), funclet 4d6050",
                0x4dac68: "FuncInfo of ObjectState_Create (thunk 4d607b), funclet 4d6070",
                0x4dac90: "FuncInfo of SetFile_ParseSectors (thunk 4d60ba), funclets 4d60ac 4d6090 4d609e",
                0x4dacc8: "FuncInfo of ObjectState_Construct (thunk 4d60e9), funclets 4d60d0 4d60db",
                0x4dacf8: "FuncInfo of ObjectState_Destruct (thunk 4d610b), funclet 4d6100"}),
    "LUA.DLL": dict(
        syms=["_FUN_10021fb0", "_FUN_10021fd0", "_FUN_10021fdb", "_FUN_10021ff0", "_FUN_10022010", "_FUN_10022030",
              "_FUN_10022050"],
        rdata=0x10023000, data=0x10026000,
        tables={0x10024df8: "FuncInfo of lbuiltin__3260 (thunk 10021fbb), funclet 10021fb0",
                0x10024e20: "FuncInfo of luaD_call (thunk 10021fe6), funclets 10021fd0 10021fdb",
                0x10024e50: "FuncInfo of lstate__87f0 (thunk 10021ffb), funclet 10021ff0",
                0x10024e78: "FuncInfo of lstate__8ad0 (thunk 1002201b), funclet 10022010",
                0x10024ea0: "FuncInfo of lvm__dbd0 (thunk 1002203b), funclet 10022030",
                0x10024ec8: "FuncInfo of lvm__dd10 (thunk 1002205b), funclet 10022050"}),
}


def run(*cmd):
    return subprocess.run(cmd, capture_output=True, text=True).stdout


for prog, cfg in PROGS.items():
    d = os.path.join(OBJ, prog)
    image = os.path.join(d, prog.lower())
    print("==== %s" % prog)
    objs = sorted(os.path.join(d, f) for f in os.listdir(d) if f.endswith(".o"))
    refs = {}
    for line in run(GCC_BIN + "nm.exe", "-A", *objs).splitlines():
        m = re.match(r"^(.*?):\s+U (\S+)$", line)
        if m and m.group(2) in cfg["syms"]:
            refs.setdefault(m.group(2), []).append(os.path.basename(m.group(1)))
    syms = {}
    for line in run(GCC_BIN + "nm.exe", image).splitlines():
        p = line.split()
        if len(p) == 3:
            syms[p[2]] = int(p[0], 16)
    stubs = set(open(os.path.join(d, "stubs.txt")).read().split())
    print("1. objects that reference the removed symbols (undefined there):")
    for s in cfg["syms"]:
        kind = "trap stub" if s.lstrip("_@").split("@")[0] in stubs else ("defined" if s in syms else "not in the image")
        print("   %-18s %-16s %s" % (s, kind, ", ".join(refs.get(s, [])) or "-"))
    dis = run(GCC_BIN + "objdump.exe", "-d", "--no-show-raw-insn", image)
    func = None
    code_refs = {}
    fs_uses = []
    want = {("%x" % syms[s]): s for s in cfg["syms"] if s in syms}
    sect_rdata = syms.get("_sect_rdata")
    tab_new = {("%x" % (sect_rdata + a - cfg["rdata"])): a for a in cfg["tables"]} if sect_rdata else {}
    tab_hits = {}
    for line in dis.splitlines():
        m = re.match(r"^([0-9a-f]+) <(.*)>:$", line)
        if m:
            func = m.group(2)
            continue
        if "%fs:" in line:
            fs_uses.append((func, line.strip()))
        for h in re.findall(r"0x([0-9a-f]+)|\b([0-9a-f]{6,8}) <", line):
            v = (h[0] or h[1]).lstrip("0")
            if v in want:
                code_refs.setdefault(want[v], []).append("%s: %s" % (func, line.strip()))
            if v in tab_new:
                tab_hits.setdefault(tab_new[v], []).append("%s: %s" % (func, line.strip()))
    print("2. instructions of the linked image that name them: %d" % sum(len(v) for v in code_refs.values()))
    for s, v in code_refs.items():
        for x in v[:5]:
            print("   %s <- %s" % (s, x))
    print("3. the exception tables (rebuilt address = _sect_rdata + offset) and their references:")
    data_s = open(os.path.join(d, "data.s")).read()
    for a, what in cfg["tables"].items():
        off = a - cfg["rdata"]
        n_data = len(re.findall(r"\.long _sect_rdata \+ 0x%x\b" % off, data_s))
        n_code = len(tab_hits.get(a, []))
        print("   %08x %-80s data refs %d, code refs %d" % (a, what, n_data, n_code))
        for x in tab_hits.get(a, [])[:3]:
            f = x.split(":")[0]
            users = [os.path.basename(l.split(":")[0]) for l in run(GCC_BIN + "nm.exe", "-A", *objs).splitlines()
                     if re.search(r"\sU %s$" % re.escape(f), l)]
            ncode = len(re.findall(r"(?:\$0x|call\s+|jmp\s+|,0x)0*%x\b" % syms[f], dis)) if f in syms else 0
            print("        %s\n          (the C text of the thunk; %s is referenced by objects: %s; by instructions: %d)"
                  % (x, f, ", ".join(users) or "none", max(ncode, 0)))
    print("4. fs: accesses (SEH registration needs fs:[0] or the TIB through fs:[0x18]):")
    for f, l in fs_uses:
        print("   %-28s %s" % (f, l))
