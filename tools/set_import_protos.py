"""Give the EXE's imports of the three game DLLs (lua_*, Cos_*, Im*/Sounds*) real prototypes in Ghidra.

The EXTERNAL placeholders of those imports had none (`undefined lua_getnumber(void)`), so calls lost
their arguments (`lua_getnumber();` with the pushed object gone) and float results (ST0).  The
prototypes are copied from the DLLs' own functions (src/<DLL>/functions.h) with the types cleaned up
(undefined4 -> int, byte * -> char *), calling convention cdecl; names/import_protos.json overrides
single entries.   Usage: python -I set_import_protos.py [--apply]"""
import json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
P = g.EXE
DLLS = ["LUA.DLL", "IMUSE.DLL", "CHORE.DLL"]


def clean_type(t):
    t = t.strip()
    t = re.sub(r"\bundefined4\b|\bundefined\b", "int", t)
    t = re.sub(r"\bbyte \*", "char *", t)
    t = re.sub(r"\bbool\b", "int", t)
    return t


def dll_protos():
    out = {}
    for p in DLLS:
        txt = open(os.path.join(ROOT, "src", p, "functions.h"), encoding="utf-8").read()
        txt = re.sub(r"\n\s+", " ", txt)  # joined continuation lines
        for line in txt.split("\n"):
            m = re.match(r"^(.*?)\b([A-Za-z_]\w*)\s*\((.*)\);\s*/\* 0x([0-9a-f]+)", line)
            if not m:
                continue
            head, name, params, addr = m.groups()
            head = re.sub(r"__\w+", "", head)
            ps = [] if params.strip() in ("void", "") else [x.strip() for x in params.split(",")]
            if p == "IMUSE.DLL" and name != "grimSound_LipSyncLoad":
                ps = [re.sub(r"uint \*", "int ", x) for x in ps]  # sound ids / names, not pointers to uint
            out[name] = (clean_type(head), [clean_type(x) for x in ps])
    return out


def main():
    apply = "--apply" in sys.argv
    over = {}
    op = os.path.join(ROOT, "names", "import_protos.json")
    if os.path.exists(op):
        over = json.load(open(op))
    protos = dll_protos()
    imports = g.get_json("list_imports", program=P, limit=1000)
    imports = imports if isinstance(imports, list) else imports.get("imports", imports)
    if apply:
        g.ensure_current(P)
    n = 0
    for imp in imports:
        name, addr = imp["name"], imp["address"]
        if name not in protos and name not in over:
            continue
        cur = g.get("get_function_by_address", program=P, address=addr)
        if ("Signature: undefined " not in cur or "(void)" not in cur) and "--force" not in sys.argv:
            continue  # already has a prototype
        if name in over:
            proto = over[name]
        else:
            ret, ps = protos[name]
            proto = "%s %s(%s)" % (ret, name, ", ".join(ps) if ps else "void")
        # name the parameters
        def namep(i, p):
            return p if re.search(r"\w\s*$", p) and not re.fullmatch(r"[\w ]+\*?", p.split("*")[-1].strip() or "") else p
        print(addr, proto)
        if apply:
            r = g.set_prototype(P, addr, proto, "__cdecl")
            if "Successfully" not in str(r):
                print("   FAILED", r)
        n += 1
    print(n, "prototypes", "applied" if apply else "(dry run)")


main()
