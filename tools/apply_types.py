"""Apply a types batch to Ghidra: structures, then the parameters, return types and globals that use them.

Usage: python -I tools/apply_types.py names/types_*.json [--dry]

A batch is one JSON object:
  {"program": "/v101/GRIMFANDANGO.EXE",
   "structs": [{"name": "Actor", "size": 168, "comment": "...",
                "fields": [[0, "void *", "pColormapRef", "comment"], [4, "uint", "dwFlags", "..."], ...]}],
   "params":  [{"addr": "004947c0", "index": 0, "type": "Actor *", "name": "actor"}],   # name optional
   "protos":  [{"addr": "00490360", "proto": "Actor * sputActor_ActorDeref(int handle)", "cc": "__cdecl"}],
   "returns": [{"addr": "00490380", "type": "Actor *"}],      # only where the committed signature is complete
   "globals": [{"addr": "008ca758", "type": "Actor *"}],
   "this":    [{"addr": "004a8310", "type": "Puck *"}],          # the implicit this of a __thiscall function
   "locals":  [{"addr": "0049cf60", "name": "local_c", "type": "ScreenCoord"}]}   # a stack local, by its Ghidra name
Structures of all the batches given are applied first, in dependency order (held by value before the holder); a new
one is created with its pointers to other batch structures as void * and typed after, so pointer cycles work
(Actor -> ActorExtra -> TextObject -> Actor). Every entry is idempotent. A new structure changes no decompilation by
itself (not journaled); fields of an existing one are renamed, retyped or added in place (never recreated, which would
detach its users), which is journaled as a struct change, so tools/export_changed.py re-exports the whole program
(cut the journal to the structure's users instead, docs/notes/types_2.md). Parameter, return, global and `this` types
are journaled per address. A `this` entry moves the function into the class namespace; tools/build_src.py drops the
`Puck::` qualifier Ghidra then prints. Writes name their program in the query string (ghidra_api.post), so the bridge's
current program is never switched. Field comments are not stored in Ghidra's layout: tools/build_src.py reads them
from these batches (names/types_*.json) when it emits the structure."""
import json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g
import export_raw

DRY = "--dry" in sys.argv


def current_fields(prog, name):
    txt = g.get("get_struct_layout", program=prog, struct_name=name).replace("\r\n", "\n")
    if not txt.startswith("Structure:"):
        return None, 0
    size = int(re.search(r"^Size:\s*(\d+)", txt, re.M).group(1))
    rows = []
    for row in txt.split("Layout:", 1)[-1].splitlines():
        r = export_raw.LAYOUT_ROW.match(row)
        if r and not (r.group(3) in ("undefined", "undefined1") and not r.group(4)):
            rows.append((int(r.group(1)), r.group(3).replace(" ", ""), r.group(4)))
    return rows, size


def apply_struct(prog, s, log):
    want = [(f[0], f[1].replace(" ", ""), f[2]) for f in s["fields"]]
    have, size = current_fields(prog, s["name"])
    if have is not None and [h for h in have if not re.fullmatch(r"field_0x[0-9a-f]+", h[2])] == want \
            and size == s["size"]:
        return "same"
    fields = json.dumps([{"name": f[2], "type": f[1], "offset": f[0]} for f in s["fields"]])
    if DRY:
        return "would " + ("create" if have is None else "recreate")
    for f in s["fields"]:
        ensure_multidim(prog, f[1].replace(" ", ""), f"struct {s['name']}.{f[2]}", log)
    if have is not None and size == s["size"]:
        # rename / retype the fields in place and fill gaps with add_struct_field (which takes the undefined bytes at
        # its offset and moves nothing); recreating the type would detach its users
        by_off = {h[0]: h for h in have}
        out = []
        for off, t, n in want:
            if off not in by_off:
                r = g.post("add_struct_field", program=prog, struct_name=s["name"], field_name=n, field_type=t,
                           offset=off)
                out.append(f"+{n}:{str(r)[:60]}")
                continue
            old = by_off[off]
            # an unnamed field (a retype to a type that did not exist yet clears the name) by its offset
            body = dict(program=prog, struct_name=s["name"],
                        field_name=f"offset:{off}" if old[2] in ("", "(unnamed)") else old[2])
            if old[2] != n:
                body["new_name"] = n
            if old[1] != t:
                body["new_type"] = t
            if len(body) > 3:
                r = g.post("modify_struct_field", **body)
                out.append(f"{old[2]}->{n}:{str(r)[:60]}")
        now, _ = current_fields(prog, s["name"])
        # a retype to a structure pointer leaves the field unnamed (seen with Actor.pExtra -> ActorExtra *):
        # name it again by offset
        for off, t, n in want:
            h = next((x for x in now if x[0] == off), None)
            if h and h[1] == t and h[2] != n:
                r = g.post("modify_struct_field", program=prog, struct_name=s["name"], field_name=f"offset:{off}",
                           new_name=n)
                out.append(f"offset:{off}->{n}:{str(r)[:60]}")
        now, _ = current_fields(prog, s["name"])
        bad = [w for w in want if w not in now]
        if bad:
            log.append(f"FAIL struct {s['name']}: fields not as asked {bad} (the bridge's naming policy?)")
        return "; ".join(out)
    if have is not None:
        log.append(f"FAIL struct {s['name']}: size {size} != {s['size']}, change it by hand (recreating detaches users)")
        return "different"
    # a new type: nothing uses it yet, so no export is needed (bypass the journal's struct marker)
    r = g.post("create_struct", program=prog, name=s["name"], fields=fields)
    g._touched.get(prog, set()).discard("*struct*")
    cur = current_fields(prog, s["name"])[1]
    if g.ok(r) and cur != s["size"]:
        r = g.post("recreate_struct", program=prog, name=s["name"], fields=fields, size=s["size"], force=True)
        g._touched.get(prog, set()).discard("*struct*")
    have, size = current_fields(prog, s["name"])
    if size != s["size"]:
        log.append(f"FAIL struct {s['name']}: size {size} != {s['size']} ({str(r)[:200]})")
    bad = [w for w in want if w not in (have or [])]
    if bad:
        log.append(f"FAIL struct {s['name']}: fields not as asked {bad} (the bridge's naming policy, a type it "
                   f"cannot parse?)")
    return str(r)[:120]


def signature(prog, addr):
    txt = g.get("get_function_by_address", program=prog, address=addr)
    m = re.search(r"^Signature: (.*)$", txt, re.M)
    return m.group(1) if m else None


def raw_text(prog, addr):
    name = next(k for k, v in export_raw.PROGRAMS.items() if v == prog)
    p = os.path.join(export_raw.ROOT, "raw", name, "functions", addr + ".c")
    return open(p, encoding="utf-8").read() if os.path.exists(p) else ""


def inferred_signature(prog, addr):
    """The signature line of the exported decompilation (the decompiler's inferred prototype)."""
    for line in raw_text(prog, addr).splitlines():
        if re.match(r"^[A-Za-z_][^;/{]*\(.*\)\s*$", line):
            return line.strip()
    return None


def split_params(sig):
    inner = sig[sig.index("(") + 1: sig.rindex(")")]
    if inner.strip() in ("", "void"):
        return []
    return [p.strip() for p in inner.split(",")]


def apply_param(prog, e, log):
    sig = signature(prog, e["addr"])
    if not sig:
        log.append(f"FAIL param {e['addr']}: no function")
        return
    ps = split_params(sig)
    if not ps and sig.startswith("undefined "):
        # no committed signature: Ghidra's decompiler infers the parameters. Commit the inferred prototype
        # (raw/<prog>/functions/<addr>.c) as __cdecl with this parameter retyped.
        dsig = inferred_signature(prog, e["addr"])
        dps = split_params(dsig) if dsig else []
        if e["index"] < len(dps) and "Unknown calling convention" not in raw_text(prog, e["addr"]):
            m = re.match(r"^(.*?)\s*(\w+)$", dps[e["index"]])
            dps[e["index"]] = f"{e['type']} {e.get('name') or m.group(2)}"
            mm = re.match(r"^(.*?)\s*((?:__\w+\s+)?)(\*?[A-Za-z_]\w*)\(", dsig)
            proto = f"{mm.group(1)} {mm.group(3)}({','.join(dps)})"
            if DRY:
                print("  would commit", e["addr"], proto)
                return
            r = g.set_prototype(prog, e["addr"], proto, mm.group(2).strip() or "__cdecl")
            if not g.ok(r):
                log.append(f"FAIL proto {e['addr']}: {proto}: {str(r)[:200]}")
            return
    if e["index"] >= len(ps) or ps[e["index"]] == "...":
        log.append(f"FAIL param {e['addr']}#{e['index']}: {sig}")
        return
    m = re.match(r"^(.*?)\s*(\w+)$", ps[e["index"]])
    ptype, pname = m.group(1).replace(" ", ""), m.group(2)
    if ptype != e["type"].replace(" ", "") and not DRY:
        r = g.post("set_parameter_type", program=prog, function_address=e["addr"], parameter_name=pname,
                   new_type=e["type"])
        if not g.ok(r):
            log.append(f"FAIL param type {e['addr']} {pname}: {str(r)[:200]}")
    if e.get("name") and e["name"] != pname and not DRY:
        r = g.post("rename_variable", program=prog, function_address=e["addr"], old_variable_name=pname,
                   new_variable_name=e["name"])
        if not g.ok(r):
            log.append(f"FAIL param name {e['addr']} {pname}: {str(r)[:200]}")


def apply_return(prog, e, log):
    sig = signature(prog, e["addr"])
    mm = sig and re.match(r"^(.*?)\s*((?:__\w+\s+)?)(\*?[A-Za-z_]\w*)\((.*)\)$", sig)
    if not mm:
        log.append(f"FAIL return {e['addr']}: {sig}")
        return
    if mm.group(1).replace(" ", "") == e["type"].replace(" ", "") or DRY:
        return
    inferred = inferred_signature(prog, e["addr"])
    if "Unknown calling convention" in raw_text(prog, e["addr"]) or (
            not split_params(sig) and inferred and split_params(inferred)):
        # the committed signature does not hold the parameters the decompiler shows: setting only the return
        # type would drop them (sputActor_ActorDeref lost its handle that way). Give a full "protos" entry.
        log.append(f"FAIL return {e['addr']}: custom storage or uncommitted parameters, use a protos entry")
        return
    cc = mm.group(2).strip()
    r = g.set_prototype(prog, e["addr"], f"{e['type']} {mm.group(3)}({mm.group(4)})", cc)
    if not g.ok(r):
        log.append(f"FAIL return {e['addr']}: {str(r)[:200]}")


def apply_proto(prog, e, log):
    """A whole prototype, for functions whose committed signature is incomplete."""
    sig = signature(prog, e["addr"]) or ""
    want = re.sub(r"\s+", "", e["proto"])
    have = re.sub(r"\s+|__\w+", "", sig)
    if have == re.sub(r"__\w+", "", want) or DRY:
        return
    r = g.set_prototype(prog, e["addr"], e["proto"], e.get("cc", "__cdecl"))
    if not g.ok(r):
        log.append(f"FAIL proto {e['addr']}: {str(r)[:200]}")


def ensure_multidim(prog, type_name, what, log):
    """The bridge parses one array dimension: for T[A][B] build T[B], then T[A][B] (Ghidra names it so), innermost
    first. Needed before a global or a structure field takes such a type. False (and logged) on failure."""
    dims = re.findall(r"\[(\d+)\]", type_name)
    if len(dims) < 2 or DRY:
        return True
    base = re.sub(r"\[\d+\]", "", type_name).strip()
    t = base
    for d in reversed(dims):
        r = g.post("create_array_type", program=prog, base_type=t, length=int(d))
        if not g.ok(r):
            log.append(f"FAIL {what}: array type {t}[{d}]: {str(r)[:200]}")
            return False
        t = t + "[" + d + "]" if t == base else re.sub(r"^(\w+)", lambda m: m.group(1) + "[" + d + "]", t)
    return True


def apply_global(prog, e, log):
    if DRY:
        return
    if not ensure_multidim(prog, e["type"], f"global {e['addr']}", log):
        return
    r = g.post("apply_data_type", program=prog, address=e["addr"], type_name=e["type"])
    if not g.ok(r):
        log.append(f"FAIL global {e['addr']}: {str(r)[:200]}")
        return
    if e.get("name"):
        apply_global_name(prog, e, log)


def apply_global_name(prog, e, log):
    """The global's name. The bridge's naming policy refuses some (no `a` prefix for an array of globals): then, as
    tools/apply_names.py does, a plain label. A user label of another name at the address is renamed, not doubled."""
    cur = g.get_json("audit_global", program=prog, address=e["addr"])
    old = cur.get("name")
    if old == e["name"]:
        return
    if old and not re.match(r"(?:DAT|PTR|UINT|INT|UNK|LAB|BYTE|WORD|DWORD|FLOAT|DOUBLE|SHORT|CHAR|[A-Z]+_ARRAY)_", old):
        r = g.post("rename_label", program=prog, address=e["addr"], old_name=old, new_name=e["name"])
    else:
        r = g.rename_or_label(prog, e["addr"], e["name"])
        if not g.ok(r):
            r = g.post("create_label", program=prog, address=e["addr"], name=e["name"])
    if not g.ok(r) and "already exists" not in str(r):
        log.append(f"FAIL name {e['addr']} {e['name']}: {str(r)[:200]}")


def apply_this(prog, e, log):
    """The implicit `this` of a __thiscall function: the bridge moves the function into the class namespace of the
    structure, from which Ghidra's auto-parameter takes its type."""
    sig = signature(prog, e["addr"]) or ""
    if "__thiscall" not in sig:
        log.append(f"FAIL this {e['addr']}: not __thiscall: {sig}")
        return
    m = re.search(r"\(([^,)]*?)\s*this\b", sig)
    if (m and m.group(1).replace(" ", "") == e["type"].replace(" ", "")) or DRY:
        return
    r = g.post("set_function_this_type", program=prog, function_address=e["addr"], this_type=e["type"])
    if not g.ok(r):
        log.append(f"FAIL this {e['addr']}: {str(r)[:200]}")


def apply_local(prog, e, log):
    """A stack local of one function (Ghidra's name for it, local_<offset>): the decompiler keeps the type it is given.
    Journaled per function address."""
    if DRY:
        return
    r = g.post("set_local_variable_type", program=prog, function_address=e["addr"], variable_name=e["name"],
               new_type=e["type"])
    if not g.ok(r):
        log.append(f"FAIL local {e['addr']} {e['name']}: {str(r)[:200]}")


def struct_order(items):
    """Structures held by value come before their holders."""
    names = {s["name"] for _, _, s in items}
    done, out = set(), []

    def visit(it, stack=()):
        name = it[2]["name"]
        if name in done or name in stack:
            return
        for f in it[2]["fields"]:
            base = re.sub(r"\[.*\]", "", f[1]).strip()
            if base in names and base != name:
                visit(next(x for x in items if x[2]["name"] == base), stack + (name,))
        done.add(name)
        out.append(it)
    for it in items:
        visit(it)
    return out


def placeholder(s, names):
    """A new structure with its pointers to other structures of the batches as void *: pointers may form cycles
    (Actor -> ActorExtra -> TextObject -> Actor), so the structures are created first and the pointers typed after."""
    fs = []
    for f in s["fields"]:
        base = f[1].replace("*", "").strip()
        fs.append([f[0], "void *" if "*" in f[1] and base in names else f[1], f[2]] + f[3:])
    return dict(s, fields=fs)


def main(paths):
    log = []
    batches = [(p, json.load(open(p))) for p in paths]
    items = struct_order([(p, b.get("program", g.EXE), s) for p, b in batches for s in b.get("structs", [])])
    names = {s["name"] for _, _, s in items}
    for p, prog, s in items:
        if current_fields(prog, s["name"])[0] is None:
            print(p, "struct", s["name"], "(placeholder)", apply_struct(prog, placeholder(s, names), log))
    for p, prog, s in items:
        print(p, "struct", s["name"], apply_struct(prog, s, log))
    for p, b in batches:
        prog = b.get("program", g.EXE)
        for e in b.get("this", []):
            apply_this(prog, e, log)
        for e in b.get("params", []):
            apply_param(prog, e, log)
        for e in b.get("protos", []):
            apply_proto(prog, e, log)
        for e in b.get("returns", []):
            apply_return(prog, e, log)
        for e in b.get("globals", []):
            apply_global(prog, e, log)
        for e in b.get("locals", []):
            apply_local(prog, e, log)
        print(p, "params", len(b.get("params", [])), "returns", len(b.get("returns", [])),
              "globals", len(b.get("globals", [])))
    for line in log:
        print(line)
    return 1 if any(l.startswith("FAIL") for l in log) else 0


if __name__ == "__main__":
    sys.exit(main([a for a in sys.argv[1:] if not a.startswith("--")]))
