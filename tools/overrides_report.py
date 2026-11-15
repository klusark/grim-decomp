"""Writes docs/OVERRIDES.md: every function of the four programs that is built from hand-written C (build/overrides*.c)
instead of its generated twin, with the module of the twin, the file of the hand-written version and why it stays.

  python -I tools/overrides_report.py            (after tools/build_src.py; reads src/<prog>/*.c and build/overrides*.c)

The reason is the one names/override_reasons.json gives for the name ({"name": "reason", ...}; "_<group>" keys are
comments), else a category derived from the hand-written code:
  rasteriser   rdraster.c: span fillers built from the original's x87 control-word switches (see BUILD_NOTES.md)
  hook         the build's test and mod hooks (GRIM_SIMTIME, GRIM_MULTI, the debug log, host file and text handling)
  x87          an x87-exact port: values rounded to float through memory where the original stores them, compares
               with the original's FCOMP / TEST AH, results left in ST0
  assembly     a top-level asm() block (a register convention C cannot declare)
  repair       Ghidra's text is wrong (lost arguments, register parameters, unrecovered jump tables): the twin needs a
               fix in the Ghidra project before it can be generated again"""
import glob
import json
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PROGS = ["GRIMFANDANGO.EXE", "LUA.DLL", "IMUSE.DLL", "CHORE.DLL"]
GUARD = {"GRIMFANDANGO.EXE": "GRIM_EXE", "LUA.DLL": "GRIM_LUA", "IMUSE.DLL": "GRIM_IMUSE", "CHORE.DLL": "GRIM_CHORE"}
DEFN = re.compile(r"(?m)^[A-Za-z_][\w *]*?\b(\w+)\s*\([^;{]*\)\s*\{")
HOOK = re.compile(r"GRIM_|grim_|sg_trace|SimOn|getenv|g_fixedFrameMs|GetTickCount")
X87 = re.compile(r"long double|volatile|__asm__|fldcw|FSTP|x87|FCOMP")
HEADERS = {}   # override file -> its first 4000 characters (the file's own description)


def hand_written():
    """name -> list of (override file, body, leading comment)"""
    out = {}
    for path in sorted(glob.glob(os.path.join(ROOT, "build", "overrides*.c"))) + [os.path.join(ROOT, "build", "fastpaths.c")]:
        if not os.path.exists(path):
            continue
        t = open(path, encoding="utf-8", errors="replace").read()
        f = os.path.basename(path)
        HEADERS[f] = t[:4000]
        for m in DEFN.finditer(t):
            i, d = m.end(), 1
            while d and i < len(t):
                d += (t[i] == "{") - (t[i] == "}")
                i += 1
            pre = t[:m.start()].rstrip()
            cm = pre[pre.rfind("/*"):] if pre.endswith("*/") else ""
            out.setdefault(m.group(1), []).append((f, t[m.start():i], cm))
        for m in re.finditer(r"(?m)^/\* OVERRIDES: ([^*]*?)\s*\*/", t):
            k = t.rfind("/*", 0, m.start())
            for n in m.group(1).split():
                out.setdefault(n, []).append((f, "ASM " + t[m.start():m.start() + 600], t[k:m.start()] if k >= 0 else ""))
    return out


def first_sentence(cm):
    s = re.sub(r"/\*+|\*+/|^\s*\*", " ", cm, flags=re.M)
    s = re.sub(r"=+ ?[A-Za-z_]\w* \(0x[0-9a-f]+\)[^=]*=+", " ", s)
    s = re.sub(r"OVERRIDES:[^\n]*", " ", s)
    s = re.sub(r"\s+", " ", s).strip()
    m = re.match(r"(.{20,220}?[.:;])(\s|$)", s)
    return (m.group(1) if m else s[:220]).replace("|", "/")


def main():
    reasons = json.load(open(os.path.join(ROOT, "names", "override_reasons.json"), encoding="utf-8"))
    hand = hand_written()
    rows = []
    for prog in PROGS:
        for f in sorted(glob.glob(os.path.join(ROOT, "src", prog, "*.c"))):
            t = open(f, encoding="utf-8", errors="replace").read()
            for m in re.finditer(r"(?ms)^/\* ---- 0x([0-9a-f]+)  (\S+) ---- \*/\n(.*?)(?=^/\* ---- 0x|\Z)", t):
                addr, name, sec = m.group(1), m.group(2), m.group(3)
                if "replaced by the hand-written version in build/overrides" not in sec[:300]:
                    continue
                cands = hand.get(name, [])
                if len(cands) > 1:   # the same name in several programs' sections: prefer the file of this program
                    tag = {"LUA.DLL": "lua", "IMUSE.DLL": "imuse", "CHORE.DLL": "chore"}.get(prog)
                    cands = [c for c in cands if tag and tag in c[0]] or [c for c in cands if not any(
                        x in c[0] for x in ("lua", "imuse", "chore"))] or cands
                ov, body, cm = cands[0] if cands else ("?", "", "")
                module = os.path.basename(f)
                if name in reasons:
                    cat, why = "documented", reasons[name]
                elif module == "rdraster.c":
                    cat, why = "rasteriser", ""
                elif body.startswith("ASM"):
                    cat, why = "assembly", first_sentence(cm)
                elif HOOK.search(body):
                    cat, why = "hook", first_sentence(cm)
                elif X87.search(body + cm) or (len(body) < 400 and X87.search(HEADERS.get(ov, ""))):
                    cat, why = "x87", first_sentence(cm)
                else:
                    cat, why = "repair", first_sentence(cm)
                rows.append((prog, module, addr, name, ov, cat, why))
    by_cat = {}
    for r in rows:
        by_cat[r[5]] = by_cat.get(r[5], 0) + 1
    out = ["# Hand-written functions", "",
           "Generated by `tools/overrides_report.py` from `src/` and `build/overrides*.c`; do not edit by hand (the reasons "
           "live in `names/override_reasons.json`).", "",
           "Every function below is built from the hand-written C of `build/overrides*.c`; `tools/build_src.py` keeps its "
           "generated twin under `#if 0` in the module. Categories:", "",
           "| Category | Count | Meaning |", "|---|---|---|"]
    meaning = {
        "rasteriser": "rdraster.c span fillers: the original switches the x87 control word part-way through each span "
                      "(24-bit truncation), which generated C cannot express; built from macro templates and tested "
                      "against the original (build/difftest/asm_q4 .. q6). Kept on purpose.",
        "documented": "the reason is recorded (names/override_reasons.json): a twin test result, a deliberate fix, a hook",
        "hook": "the build's own test and mod hooks, host-runtime handling (kept on purpose)",
        "x87": "x87-exact ports (float rounding through memory, FCOMP compares, ST0 results) the generated C does not match",
        "assembly": "top-level asm(): a register convention C cannot declare",
        "repair": "Ghidra's text is wrong for it (lost or register arguments, unrecovered jump tables): needs a fix in the "
                  "Ghidra project before it can be generated again",
    }
    for c in ["rasteriser", "documented", "hook", "x87", "assembly", "repair"]:
        if c in by_cat:
            out.append("| %s | %d | %s |" % (c, by_cat[c], meaning[c]))
    out += ["", "Total: %d." % len(rows), ""]
    for prog in PROGS:
        pr = [r for r in rows if r[0] == prog]
        if not pr:
            continue
        nr = [r for r in pr if r[5] != "rasteriser"]
        out += ["## %s (%d)" % (prog, len(pr)), ""]
        if len(nr) != len(pr):
            out += ["%d rasteriser span fillers of rdraster.c are not listed one by one." % (len(pr) - len(nr)), ""]
        if nr:
            out += ["| Function | Address | Module | Hand-written in | Category | Why |", "|---|---|---|---|---|---|"]
            for r in sorted(nr, key=lambda r: (r[1], r[3])):
                out.append("| `%s` | %s | %s | %s | %s | %s |" % (r[3], r[2], r[1], r[4], r[5], r[6]))
            out.append("")
    open(os.path.join(ROOT, "docs", "OVERRIDES.md"), "w", encoding="utf-8", newline="\n").write("\n".join(out))
    print("docs/OVERRIDES.md:", len(rows), "functions;", ", ".join("%s %d" % kv for kv in sorted(by_cat.items())))


if __name__ == "__main__":
    main()
