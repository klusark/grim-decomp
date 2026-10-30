"""Change the return type of functions in Ghidra, keeping name, calling convention and parameters.

  python -I set_return_type.py PROG[:type] addr [addr[:type] ...]      e.g.  LUA.DLL 10009410:uint* 1000c7b0

Used for functions Ghidra declared `void` whose callers use EAX (found by the arity/void scans): the decompilation of every
caller then sees the result and the function itself returns it explicitly.  Default type: int."""
import os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g
import export_raw

prog = sys.argv[1]
path = export_raw.PROGRAMS[prog]
g.ensure_current(path)
for spec in sys.argv[2:]:
    addr, _, ty = spec.partition(":")
    ty = (ty or "int").replace("*", " *")
    txt = g.get("get_function_by_address", program=path, address=addr)
    m = re.search(r"^Signature: (.*)$", txt, re.M)
    if not m:
        print(addr, "no function", txt[:80])
        continue
    sig = m.group(1)
    cc = re.search(r"__(stdcall|fastcall|thiscall|cdecl)", sig)
    # `ret [cc] name(params)`
    mm = re.match(r"^(.*?)\s*(?:__\w+\s+)?(\*?[A-Za-z_]\w*)\((.*)\)$", sig)
    if not mm:
        print(addr, "cannot parse", sig)
        continue
    name, params = mm.group(2), mm.group(3)
    proto = "%s %s(%s)" % (ty, name, params)
    r = g.set_prototype(path, addr, proto, ("__" + cc.group(1)) if cc else "")
    print(addr, sig, "->", proto, "|", str(r)[:70])
