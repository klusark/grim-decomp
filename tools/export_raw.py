"""Pull decompiled functions, signatures, strings and types out of the running
Ghidra instance (ghidra-mcp HTTP bridge on 127.0.0.1:8089) into raw/<prog>/."""
import json, re, os, sys, time, urllib.request, urllib.parse

BASE = "http://127.0.0.1:8089"
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PROGRAMS = {
    "GRIMFANDANGO.EXE": "/v101/GRIMFANDANGO.EXE",
    "LUA.DLL": "/LUA.DLL",
    "IMUSE.DLL": "/v101/IMUSE.DLL",
    "CHORE.DLL": "/CHORE.DLL",
}

def get(path, **params):
    q = urllib.parse.urlencode(params)
    url = f"{BASE}{path}?{q}" if q else f"{BASE}{path}"
    for attempt in range(4):
        try:
            with urllib.request.urlopen(url, timeout=180) as r:
                return r.read().decode("utf-8", "replace")
        except Exception as e:  # noqa
            err = e
            time.sleep(1.5 * (attempt + 1))
    raise RuntimeError(f"{url}: {err}")

def get_json(path, **params):
    txt = get(path, **params)
    try:
        return json.loads(txt)
    except Exception:
        return {"_raw": txt}

def thunk_code(prog_path, fn):
    """Placeholder body for a thunk. A direct `JMP 0xADDR` thunk records its target
    so build_src.py can emit the jump (thunks.c); import thunks (`JMP [IAT]`) and
    EXTERNAL functions stay bare placeholders and resolve to the import library."""
    addr = fn["address"]
    if not fn.get("isExternal"):
        d = get("/disassemble_function", program=prog_path, address=addr) or ""
        lines = d.strip().splitlines()
        m = re.search(r":\s*JMP 0x([0-9a-fA-F]+)\s*$", lines[0]) if lines else None
        if m:
            return f"/* thunk: {fn['name']} @ {addr} -> {int(m.group(1), 16):08x} */\n"
    return f"/* thunk/external: {fn['name']} @ {addr} */\n"

LAYOUT_ROW = re.compile(r"^\s*(\d+)\s*\|\s*(\d+)\s*\|\s*(.+?)\s*\|\s*(\S*)\s*$")


def struct_layouts(prog_path, getter=None):
    """{name: {"size": n, "fields": [[offset, size, type, name], ...]}} for every structure of the
    program's own data types (the PE / DOS header types of the loader are left out). Read by
    tools/build_src.py, which emits the layouts into ghidra_types.h."""
    getter = getter or get
    listing = getter("/list_data_types", program=prog_path, category="", limit=5000)
    out = {}
    for line in listing.replace("\r\n", "\n").splitlines():
        parts = [p.strip() for p in line.split("|")]
        if len(parts) < 4 or "*" in parts[0] or "[" in parts[0]:
            continue
        name, path = parts[0], parts[3]
        if path.startswith(("/PE/", "/DOS/")) or name.startswith("IMAGE_") or not re.fullmatch(r"[A-Za-z_]\w*", name):
            continue
        txt = getter("/get_struct_layout", program=prog_path, struct_name=name).replace("\r\n", "\n")
        if not txt.startswith("Structure:"):
            continue
        m = re.search(r"^Size:\s*(\d+)", txt, re.M)
        fields = []
        for row in txt.split("Layout:", 1)[-1].splitlines():
            r = LAYOUT_ROW.match(row)
            if r:
                fields.append([int(r.group(1)), int(r.group(2)), r.group(3), r.group(4)])
        out[name] = {"size": int(m.group(1)) if m else 0, "fields": fields}
    return out


def dump_structs(prog_name, prog_path, getter=None):
    out = os.path.join(ROOT, "raw", prog_name)
    s = struct_layouts(prog_path, getter)
    with open(os.path.join(out, "structs.json"), "w", newline="\n") as f:
        json.dump(s, f, indent=1, sort_keys=True)
    print(prog_name, len(s), "structures", flush=True)


def dump(prog_name, prog_path):
    out = os.path.join(ROOT, "raw", prog_name)
    os.makedirs(os.path.join(out, "functions"), exist_ok=True)
    funcs = get_json("/list_functions_enhanced", program=prog_path, limit=10000)
    funcs = funcs.get("functions", funcs)
    with open(os.path.join(out, "functions.json"), "w") as f:
        json.dump(funcs, f, indent=1)
    print(prog_name, len(funcs), "functions", flush=True)
    for i, fn in enumerate(funcs):
        addr = fn["address"]
        dst = os.path.join(out, "functions", f"{addr}.c")
        if os.path.exists(dst) and os.path.getsize(dst) > 0:
            continue
        if fn.get("isThunk") or fn.get("isExternal"):
            code = thunk_code(prog_path, fn)
        else:
            code = get("/decompile_function", program=prog_path, address=addr)
        with open(dst, "w", newline="\n") as f:
            f.write(code.replace("\r\n", "\n"))
        if i % 100 == 0:
            print(f"  {prog_name}: {i}/{len(funcs)}", flush=True)
    # auxiliary dumps
    aux = {
        "imports.json": lambda: get("/list_imports", program=prog_path, limit=5000),
        "exports.json": lambda: get("/list_exports", program=prog_path, limit=5000),
        "strings.txt": lambda: get("/list_strings", program=prog_path, limit=100000),
        "segments.txt": lambda: get("/list_segments", program=prog_path, limit=100),
        "globals.json": lambda: get("/list_globals", program=prog_path, limit=100000),
        "data_types.txt": lambda: get("/list_data_types", program=prog_path, category="", limit=5000),
        "classes.txt": lambda: get("/list_classes", program=prog_path, limit=5000),
    }
    for name, fn in aux.items():
        try:
            with open(os.path.join(out, name), "w", newline="\n") as f:
                f.write(fn().replace("\r\n", "\n"))
        except Exception as e:
            print("  aux failed", name, e, flush=True)
    dump_structs(prog_name, prog_path)
    print(prog_name, "done", flush=True)

if __name__ == "__main__":
    names = sys.argv[1:] or list(PROGRAMS)
    for n in names:
        dump(n, PROGRAMS[n])
