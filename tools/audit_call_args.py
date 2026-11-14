"""Audit the argument counts of indirect calls: the decompiler's against the machine code (raw/<prog>/disasm.json).

  python -I tools/audit_call_args.py [PROG...] > report.txt        (needs the Ghidra bridge and GHIDRA_MCP_ALLOW_SCRIPTS=1)

For every register-indirect CALL of the programs the expected count is taken from the code: the `ADD ESP,n` right
after the call (a __cdecl call), and the pushes back to the previous call (A: stopping at jumps, B: crossing
conditional jumps). A Ghidra script decompiles each function once and reads the inputs of its CALLIND p-code ops.
A line is printed for every call where they differ, with A, B, ADD and whether the function is hand-written.

Read the report with care (build/BUILD_NOTES.md, "The live-code audit"): a typed service pointer (pFprintf is varargs)
prints more arguments than its p-code inputs; MSVC defers the cleanup of several calls into one ADD ESP; an argument
pushed before a branch serves both paths. A call-site signature (names/callsite_overrides.json) is right only when the
call is not shared and the count is certain: a wrong count shifts the decompiler's stack model for the calls after it.
Functions are decompiled 100 at a time (the decompiler process grows with each one)."""
import glob, json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g
import export_raw

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# (no backslashes: the bridge un-escapes them in the script source)
SCRIPT = """import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.pcode.*;
import java.util.*;
public class CallAudit extends GhidraScript {
  public void run() throws Exception {
    Map<String, Integer> want = new HashMap<>();
    Set<String> fns = new LinkedHashSet<>();
    for (String e : "%s".split(",")) { String[] f = e.split(":"); want.put(f[1], Integer.parseInt(f[2])); fns.add(f[0]); }
    DecompInterface di = new DecompInterface();
    di.openProgram(currentProgram);
    StringBuilder sb = new StringBuilder();
    for (String fa : fns) {
      Function fn = getFunctionAt(toAddr(fa));
      if (fn == null) continue;
      HighFunction hf = di.decompileFunction(fn, 60, monitor).getHighFunction();
      if (hf == null) continue;
      Iterator<PcodeOpAST> it = hf.getPcodeOps();
      while (it.hasNext()) {
        PcodeOpAST op = it.next();
        if (op.getOpcode() != PcodeOp.CALLIND) continue;
        String a = op.getSeqnum().getTarget().toString();
        Integer w = want.get(a);
        if (w != null && op.getNumInputs() - 1 != w) sb.append(fa + ":" + a + ":" + (op.getNumInputs() - 1) + ";");
      }
    }
    di.dispose();
    println("MISMATCH " + sb.toString());
  }
}"""
STOP_A = r"(CALL|RET|JMP|J[A-Z]+ |SUB ESP|LEAVE)"
STOP_B = r"(CALL|RET|JMP|SUB ESP|LEAVE)"
CALL_RE = re.compile(r"([0-9a-f]+): CALL (dword ptr \[E[A-Z]X( \+ 0x[0-9a-f]+)?\]|E[A-Z]X)\s*$")


def pushes(lines, i, stop):
    j, k = i - 1, 0
    while j >= 0:
        s = lines[j].split(": ", 1)[1] if ": " in lines[j] else ""
        if re.match(stop, s):
            break
        if s.startswith("PUSH"):
            k += 1
        j -= 1
    if j < 0:   # back at the function's start: not the registers the prologue saves
        k -= sum(1 for x in lines[:6] if re.search(r": PUSH E(BP|BX|SI|DI)\b", x))
    return max(k, 0)


def add_esp(lines, i):
    for j in range(i + 1, min(i + 5, len(lines))):
        s = lines[j].split(": ", 1)[1]
        m = re.match(r"ADD ESP,0x([0-9a-f]+)", s)
        if m:
            return int(m.group(1), 16) // 4
        if re.match(r"(CALL|PUSH|POP|RET|J)", s):
            return None
    return None


def sites(prog):
    d = json.load(open(os.path.join(ROOT, "raw", prog, "disasm.json")))
    out = []
    for fa, txt in d.items():
        lines = [l.strip() for l in txt.strip().split("\n")]
        for i, l in enumerate(lines):
            m = CALL_RE.match(l)
            if m:
                out.append((fa, m.group(1), pushes(lines, i, STOP_A), pushes(lines, i, STOP_B), add_esp(lines, i)))
    return out


def main():
    progs = [a for a in sys.argv[1:] if not a.startswith("-")] or ["GRIMFANDANGO.EXE", "IMUSE.DLL", "LUA.DLL", "CHORE.DLL"]
    for prog in progs:
        names = {f["address"]: f["name"] for f in json.load(open(os.path.join(ROOT, "raw", prog, "functions.json")))}
        hand = set()
        for f in glob.glob(os.path.join(ROOT, "src", prog, "*.c")):
            text = open(f, encoding="utf-8", errors="replace").read()
            hand |= set(re.findall(r"/\* ---- 0x(\w+)\s+\S+ ---- \*/\n/\* replaced by", text))
        s = sites(prog)
        exp = {c: (a, b, ad) for fa, c, a, b, ad in s}
        fns = sorted({x[0] for x in s})
        for k in range(0, len(fns), 100):
            part = set(fns[k:k + 100])
            spec = ",".join("%s:%s:%d" % (fa, c, ad if ad is not None else a) for fa, c, a, b, ad in s if fa in part)
            r = g.post("run_script_inline", code=SCRIPT % spec, program=export_raw.PROGRAMS[prog])
            txt = str(r.get("_raw", r) if isinstance(r, dict) else r)
            mm = re.search(r"MISMATCH ([^\r\n]*)", txt)
            for e in (mm.group(1).split(";") if mm else []):
                if e.count(":") == 2:
                    fa, c, got = e.split(":")
                    a, b, ad = exp[c]
                    print("%s %-4s %-32s %s got %s A %d B %d ADD %s" % (prog, "hand" if fa in hand else "live",
                          names.get(fa, fa), c, got, a, b, ad))


if __name__ == "__main__":
    main()
