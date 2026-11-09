"""SEH frame scan of the linked programs (docs/notes/s3.md): run after `make -C build link`.
For GRIMFANDANGO.EXE, LUA.DLL, IMUSE.DLL and CHORE.DLL it prints, from objdump -d of the linked image:
  * every instruction that touches the segment register fs (fs:[0] = ExceptionList, fs:[0x18] = the TIB pointer:
    an SEH registration needs one of them);
  * every instruction that names an exception handler of the runtime (__CxxFrameHandler, __InternalCxxFrameHandler,
    _except_handler2/3/4, _CxxThrowException, their import slots __imp_*), then every instruction that names a function
    found that way (a thunk), and so on;
  * which object file defines each of those functions (nm of build/obj/<PROG>/*.o; "(library)" = mingw / libgcc /
    an import library, i.e. not rebuilt code).
usage: python -I build/difftest/s3/seh_scan.py   (exit status 1 when rebuilt code, i.e. not the mingw start-up code
       or a library, touches fs: or references a handler)"""
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
OBJ = os.path.join(ROOT, "build", "obj")
GCC_BIN = "C:/msys64/mingw32/bin/"
HANDLER_RE = re.compile(r"(?:CxxFrameHandler\d?|except_handler[234]?(?:_common)?|CxxThrowException)$")
# mingw-w64 start-up / CRT code that is part of the toolchain, not of the rebuilt game
TOOLCHAIN = re.compile(r"^(?:___tmainCRTStartup|__CRT_INIT@12|_?__mingw\w*|___gcc_\w*|___chkstk\w*|__alloca)$")


def run(*cmd):
    return subprocess.run(cmd, capture_output=True, text=True).stdout


bad = 0
for prog in ("GRIMFANDANGO.EXE", "LUA.DLL", "IMUSE.DLL", "CHORE.DLL"):
    d = os.path.join(OBJ, prog)
    image = os.path.join(d, prog.lower())
    print("==== %s" % prog)
    syms = {}
    for line in run(GCC_BIN + "nm.exe", image).splitlines():
        p = line.split()
        if len(p) == 3:
            syms.setdefault(int(p[0], 16), []).append(p[2])
    handlers = {a: n for a, ns in syms.items() for n in ns if HANDLER_RE.search(n.split("@")[0])}
    print("handler symbols in the image: %s" % (", ".join("%s=%x" % (n, a) for a, n in sorted(handlers.items())) or "none"))
    objs = sorted(os.path.join(d, f) for f in os.listdir(d) if f.endswith(".o"))
    defined_in = {}
    for line in run(GCC_BIN + "nm.exe", "-A", *objs).splitlines():
        m = re.match(r"^(.*?):[0-9a-f]+\s+[TtDdBbRr] (\S+)$", line)
        if m:
            defined_in.setdefault(m.group(2), os.path.basename(m.group(1)))
    dis = run(GCC_BIN + "objdump.exe", "-d", "--no-show-raw-insn", image)
    func = None
    body = {}
    fs_uses = []
    for line in dis.splitlines():
        m = re.match(r"^([0-9a-f]+) <(.*)>:$", line)
        if m:
            func = m.group(2)
            body.setdefault(func, [])
            continue
        if func and re.match(r"^\s*[0-9a-f]+:", line):
            body[func].append(line.strip())
            if "%fs:" in line:
                fs_uses.append((func, line.strip()))

    def refs_to(addrs):
        out = []
        for f, ls in body.items():
            for l in ls:
                ins = l.split(":", 1)[1]
                for h in re.findall(r"0x([0-9a-f]+)|\b([0-9a-f]{6,8}) <", ins):
                    if int(h[0] or h[1], 16) in addrs:
                        out.append((f, l))
                        break
        return out

    print("fs: accesses:")
    for f, l in fs_uses:
        tool = bool(TOOLCHAIN.match(f)) or f not in defined_in
        if not tool:
            bad += 1
        print("   %-7s %-28s %-24s %s" % ("" if tool else "REBUILT", f, defined_in.get(f, "(library)"), l))
    level = dict(handlers)
    seen = set(level)
    depth = 0
    while level:
        depth += 1
        hits = refs_to(set(level))
        what = "the handlers" if depth == 1 else "the functions above"
        if not hits:
            print("references to %s: none" % what)
            break
        print("references to %s:" % what)
        nxt = {}
        for f, l in hits:
            lib = f not in defined_in
            print("   %-7s %-28s %-24s %s" % ("" if lib else "REBUILT", f, defined_in.get(f, "(library)"), l))
            if not lib:
                bad += 1
            for a, ns in syms.items():
                if f in ns and a not in seen:
                    nxt[a] = f
                    seen.add(a)
        level = nxt
print("rebuilt code that touches fs: or references a handler: %d instruction(s)" % bad)
sys.exit(1 if bad else 0)
