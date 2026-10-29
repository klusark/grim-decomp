"""Compare, for every C-compiled function, the arguments of each call in the decompiled C with the arguments the
original code pushes for it (from the disassembly).  A call whose C argument count is smaller than the number of
pushes is a call the decompiler lost arguments of (the callee then reads stack garbage); a call with more C
arguments than pushes is an invented argument (harmless for cdecl).  Needs raw/<prog>/disasm.json (find_arity_asm.py --fetch).

Usage: python -I find_lost_args.py [prog...]
"""
import json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import find_arity_asm as F

ROOT = F.ROOT
CALL = re.compile(r"(?<![\w>.])([A-Za-z_]\w*)\(")


def split_args(s):
    out, depth, cur = [], 0, ""
    for ch in s:
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur); cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur)
    return out


def c_calls(body):
    res = []
    for m in CALL.finditer(body):
        j, depth = m.end(), 1
        while j < len(body) and depth:
            depth += (body[j] == "(") - (body[j] == ")")
            j += 1
        res.append((m.group(1), len(split_args(body[m.end():j - 1])), body[m.start():j][:90]))
    return res


def main():
    progs = [a for a in sys.argv[1:] if not a.startswith("--")] or F.PROGS
    asm = json.load(open(os.path.join(ROOT, "names", "asm_funcs.json")))
    import build_src
    for prog in progs:
        raw = os.path.join(ROOT, "raw", prog)
        funcs = json.load(open(os.path.join(raw, "functions.json")))
        name_of = {int(f["address"], 16): f["name"] for f in funcs}
        addr_of = {}
        for a, n in name_of.items():
            addr_of.setdefault(n, a)
        dis = {int(a, 16): F.parse(t) for a, t in json.load(open(os.path.join(raw, "disasm.json"))).items()}
        protos = F.protos_of(prog)
        ret_imm = {}
        for a, ins in dis.items():
            rets = [int(o, 16) for (_, mn, o) in ins if mn == "RET" and o.startswith("0x")]
            if rets:
                ret_imm[a] = max(rets)
        for a, n in name_of.items():
            if n in F.DEC:
                ret_imm.setdefault(a, int(F.DEC[n].rsplit("@", 1)[1]))
        asm_set = set(asm.get(prog, []))
        print("====", prog)
        for a, ins in sorted(dis.items()):
            h = "%08x" % a
            if h in asm_set or name_of.get(a) in build_src.OVERRIDES:
                continue
            p = os.path.join(raw, "functions", h + ".c")
            if not os.path.exists(p):
                continue
            body = open(p, encoding="utf-8", errors="replace").read()
            ccalls = {}
            for name, n, text in c_calls(body):
                ccalls.setdefault(name, []).append((n, text))
            acalls = {}
            for i, (ia, mn, ops) in enumerate(ins):
                m = re.fullmatch(r"0x([0-9a-f]+)", ops) if mn == "CALL" else None
                if not m:
                    continue
                t = int(m.group(1), 16)
                nm = name_of.get(t)
                if not nm:
                    continue
                if t in ret_imm and ret_imm[t] and (t not in protos or protos[t][1] == "stdcall"):
                    acalls.setdefault(nm, []).append(ret_imm[t] // 4)
                    continue
                nx = ins[i + 1] if i + 1 < len(ins) else None
                m2 = re.fullmatch(r"ESP,0x([0-9a-f]+)", nx[2]) if nx and nx[1] == "ADD" else None
                if m2:
                    acalls.setdefault(nm, []).append(int(m2.group(1), 16) // 4)
                elif nx and not (nx[1] == "ADD" and nx[2].startswith("ESP")):
                    acalls.setdefault(nm, []).append(None)  # deferred cleanup / no args
            for nm, counts in acalls.items():
                if nm not in ccalls or nm == name_of.get(a):
                    continue
                known = [c for c in counts if c is not None]
                if not known:
                    continue
                cmax = max(n for n, _ in ccalls[nm])
                if cmax < max(known):
                    print("%s %-34s calls %-28s with C args %s, code pushes %s   %s" % (
                        h, name_of.get(a), nm, sorted(n for n, _ in ccalls[nm]), sorted(known), ccalls[nm][0][1]))


if __name__ == "__main__":
    main()
