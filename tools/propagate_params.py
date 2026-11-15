"""Proposes types and names for Ghidra's untyped parameters (`param_N`) from the calls that pass them on.

  python -I tools/propagate_params.py <prog> [out.json]     (reads src/<prog>/functions.h and src/<prog>/*.c)

A parameter `param_N` of type int / uint / undefined4 / void * that a function passes, unchanged, as argument k of a call
to G, where G's parameter k has a real type (a pointer to a structure or another typed pointer) and a real name, takes
that type and name - when every such call of the function agrees on the type. The name is G's, or G's with a number
when the function already has a parameter of that name. Repeated until nothing changes (a parameter typed in one round
can type its own callers' parameters in the next). Pointer types only: an int parameter that G takes as `float` or
`short` is a conversion in the call, not the parameter's type.

Writes a types batch for tools/apply_types.py (`params`: addr, index, type, name; index counts `this` of a __thiscall
function, as functions.h lists it) and prints a summary."""
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PROGRAMS = {"GRIMFANDANGO.EXE": "/v101/GRIMFANDANGO.EXE", "LUA.DLL": "/LUA.DLL", "IMUSE.DLL": "/v101/IMUSE.DLL",
            "CHORE.DLL": "/CHORE.DLL"}
UNTYPED = {"int", "uint", "undefined4", "void *", "undefined *", "int *", "uint *", "undefined4 *"}
WEAK_TYPES = UNTYPED | {"char *", "byte *", "undefined1 *", "code *", "short *", "ushort *", "float *", "double *",
                        "undefined2 *", "undefined8 *", "float10 *"}
PROTO_RE = re.compile(r"^(?P<ret>[^;()]*?)\b(?P<cc>__cdecl|__stdcall|__thiscall|__fastcall)?\s*(?P<name>[A-Za-z_]\w*)\s*"
                      r"\((?P<params>[^;]*)\)\s*;\s*/\* 0x(?P<addr>[0-9a-f]{8}) \*/")


def split_params(s):
    s = s.strip()
    if s in ("", "void"):
        return []
    out, depth, cur = [], 0, ""
    for c in s:
        if c == "(" :
            depth += 1
        elif c == ")":
            depth -= 1
        if c == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
        else:
            cur += c
    out.append(cur.strip())
    res = []
    for p in out:
        if p == "...":
            res.append(("...", "..."))
            continue
        m = re.match(r"^(.*?)([A-Za-z_]\w*)\s*(\[[^\]]*\])?$", p)
        if not m:
            res.append((p, ""))
            continue
        t = re.sub(r"\s+", " ", m.group(1)).strip().replace(" *", " *")
        t = re.sub(r"\s*\*", " *", t).replace("* *", "**").strip()
        res.append((t, m.group(2)))
    return res


def load_protos(prog):
    protos = {}
    for line in open(os.path.join(ROOT, "src", prog, "functions.h"), encoding="utf-8", errors="replace"):
        m = PROTO_RE.match(line.strip())
        if m:
            protos[m.group("name")] = {"addr": m.group("addr"), "params": split_params(m.group("params"))}
    return protos


def norm(t):
    return re.sub(r"\s+", " ", t.replace("*", " * ")).replace(" * *", " **").strip().replace("* *", "**")


def is_good(t):
    t = norm(t)
    return t.endswith("*") and norm(t) not in {norm(x) for x in WEAK_TYPES} and "undefined" not in t


def call_args(body, start):
    """the argument strings of the call whose '(' is at body[start]"""
    depth, i, cur, args = 0, start, "", []
    while i < len(body):
        c = body[i]
        if c == "(":
            depth += 1
            if depth == 1:
                i += 1
                continue
        elif c == ")":
            depth -= 1
            if depth == 0:
                args.append(cur.strip())
                return args
        if c == "," and depth == 1:
            args.append(cur.strip())
            cur = ""
        else:
            cur += c
        i += 1
    return None


def main():
    prog = sys.argv[1]
    out_path = sys.argv[2] if len(sys.argv) > 2 else None
    protos = load_protos(prog)
    bodies = {}
    for f in os.listdir(os.path.join(ROOT, "src", prog)):
        if not f.endswith(".c") or f == "data.c":
            continue
        t = open(os.path.join(ROOT, "src", prog, f), encoding="utf-8", errors="replace").read()
        for m in re.finditer(r"(?ms)^/\* ---- 0x([0-9a-f]+)  (\S+) ---- \*/\n(.*?)(?=^/\* ---- 0x|\Z)", t):
            if "#if 0" in m.group(3)[:300]:
                continue        # overridden: the generated text is not built
            bodies[m.group(2)] = m.group(3)
    assigned = {}    # (fn, index) -> (type, name)
    callre = re.compile(r"\b([A-Za-z_]\w*)\s*\(")
    for rnd in range(6):
        changed = 0
        for fn, body in bodies.items():
            pr = protos.get(fn)
            if not pr:
                continue
            ps = pr["params"]
            for idx, (pt, pn) in enumerate(ps):
                if not re.fullmatch(r"param_\d+", pn) or norm(pt) not in {norm(x) for x in UNTYPED}:
                    continue
                if (fn, idx) in assigned:
                    continue
                cands = set()
                bad = False
                uses = len(re.findall(r"\b%s\b" % pn, body.split("\n{", 1)[-1]))
                for cm in callre.finditer(body):
                    g = cm.group(1)
                    gp = protos.get(g)
                    if not gp:
                        continue
                    args = call_args(body, cm.end() - 1)
                    if not args:
                        continue
                    for k, a in enumerate(args):
                        a2 = re.sub(r"^\((?:[A-Za-z_][\w ]*\*?\s*\**)\)\s*", "", a).strip()
                        if a2 != pn:
                            continue
                        if k >= len(gp["params"]) or gp["params"][k][0] == "...":
                            bad = True
                            continue
                        gt, gn = gp["params"][k]
                        key = (g, k)
                        if key in assigned:
                            gt, gn = assigned[key]
                        if is_good(gt) and gn and not re.fullmatch(r"param_\d+|a\d+|this", gn):
                            cands.add((norm(gt), gn))
                        elif is_good(gt):
                            cands.add((norm(gt), None))
                        else:
                            bad = True
                if bad or not cands:
                    continue
                types = {t for t, _ in cands}
                if len(types) != 1:
                    continue
                t = types.pop()
                names = sorted({n for _, n in cands if n})
                name = names[0] if len(names) == 1 else None
                if not name:
                    base = re.sub(r"\W", "", t.split()[0])
                    name = "p" + base[:1].upper() + base[1:]
                others = {n for _, n in ps if n} | {v[1] for (f2, _), v in assigned.items() if f2 == fn}
                if name in others:
                    continue
                if re.search(r"\b%s\b" % re.escape(name), body):
                    continue        # the name is taken by a local or a global the function uses
                assigned[(fn, idx)] = (t, name)
                changed += 1
        print("round %d: %d parameters" % (rnd + 1, changed))
        if not changed:
            break
    # names only (the type stays, so the generated code does not change): a scalar param_N passed on as a parameter
    # that has a real name (forward), or a param_N to which every caller passes a variable of the same real name
    # (reverse: locals, parameters and globals of the callers, `&x` and casts stripped)
    named = {}       # (fn, index) -> name
    SCALAR = {"int", "uint", "undefined4", "float", "short", "ushort", "char", "byte", "undefined1", "undefined2",
              "bool", "long", "ulong", "undefined", "dword", "word", "longlong", "ulonglong", "undefined8"}
    calls_to = {}    # callee -> list of (caller, args)
    for fn, body in bodies.items():
        for cm in callre.finditer(body):
            g = cm.group(1)
            if g in protos and g != fn:
                args = call_args(body, cm.end() - 1)
                if args is not None:
                    calls_to.setdefault(g, []).append((fn, args))

    def taken(fn, name):
        ps = protos[fn]["params"]
        others = {n for _, n in ps if n} | {v[1] for (f2, _), v in assigned.items() if f2 == fn} | \
                 {v for (f2, _), v in named.items() if f2 == fn}
        return name in others or re.search(r"\b%s\b" % re.escape(name), bodies.get(fn, ""))

    def real(n):
        return n and not re.fullmatch(r"(param|local|uVar|iVar|pvVar|puVar|piVar|pcVar|pbVar|fVar|dVar|bVar|cVar|sVar|"
                                      r"lVar|uStack|iStack|pStack|in_stack|unaff|extraout|auStack|a)_?\w*\d+\w*|this",
                                      n) and not re.match(r"(DAT|UINT|PTR|FUN|LAB|s|_DAT|FLOAT|DOUBLE)_", n)             and not re.fullmatch(r"\w*Var\d+|\w*Stack_?\w*", n)
    for rnd in range(6):
        changed = 0
        for fn, body in bodies.items():
            pr = protos.get(fn)
            if not pr:
                continue
            for idx, (pt, pn) in enumerate(pr["params"]):
                if not re.fullmatch(r"param_\d+", pn) or (fn, idx) in assigned or (fn, idx) in named:
                    continue
                cands = set()
                for cm in callre.finditer(body):        # forward
                    g = cm.group(1)
                    gp = protos.get(g)
                    if not gp:
                        continue
                    args = call_args(body, cm.end() - 1)
                    for k, a in enumerate(args or []):
                        a2 = re.sub(r"^\((?:[A-Za-z_][\w ]*\*?\s*\**)\)\s*", "", a).strip()
                        if a2 == pn and k < len(gp["params"]) and gp["params"][k][0] != "...":
                            gn = assigned.get((g, k), (None, gp["params"][k][1]))[1]
                            gn = named.get((g, k), gn)
                            if real(gn):
                                cands.add(gn)
                if not cands:                            # reverse
                    rs = set()
                    calls = calls_to.get(fn, [])
                    for caller, args in calls:
                        if idx >= len(args):
                            rs.add(None)
                            continue
                        a = re.sub(r"^\((?:[A-Za-z_][\w ]*\*?\s*\**)\)\s*", "", args[idx]).strip().lstrip("&")
                        m = re.fullmatch(r"(?:[A-Za-z_]\w*(?:->|\.))*([A-Za-z_]\w*)", a)
                        rs.add(m.group(1) if m and real(m.group(1)) else None)
                    if len(calls) >= 1 and len(rs) == 1 and None not in rs:
                        n = rs.pop()
                        n = re.sub(r"^g_[a-z]*(?=[A-Z])", "", n)            # a global's name without g_ and its prefix
                        n = n[:1].lower() + n[1:] if re.match(r"[A-Z][a-z]", n) else n
                        cands.add(n)
                if len(cands) != 1:
                    continue
                name = cands.pop()
                if taken(fn, name):
                    continue        # (a numbered copy of a name the function has already says nothing)
                named[(fn, idx)] = name
                changed += 1
        print("names round %d: %d parameters" % (rnd + 1, changed))
        if not changed:
            break
    params = [{"addr": protos[fn]["addr"], "index": idx, "type": t, "name": n, "_fn": fn}
              for (fn, idx), (t, n) in sorted(assigned.items())]
    params += [{"addr": protos[fn]["addr"], "index": idx, "type": protos[fn]["params"][idx][0], "name": n, "_fn": fn,
                "_names_only": True} for (fn, idx), n in sorted(named.items())]
    from collections import Counter
    c = Counter(p["type"] for p in params)
    print(len(params), "parameters in", len({p["_fn"] for p in params}), "functions;", c.most_common(12))
    if out_path:
        json.dump({"_comment": "Parameter types and names propagated from the calls that pass them on "
                               "(tools/propagate_params.py, 2026-11-15).",
                   "program": PROGRAMS[prog], "params": params}, open(out_path, "w", encoding="utf-8", newline="\n"),
                  indent=1)


if __name__ == "__main__":
    main()
