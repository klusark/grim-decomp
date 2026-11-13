"""Applies names/logic_protos.json to the live Ghidra project (agent P): function prototypes whose arguments the decompiler
had wrong, so that the callers' decompilation (and tools/export_changed.py) sees the right argument lists.
  python -I tools/apply_logic_protos.py [--dry] [names/<file>.json]   (default names/logic_protos.json)

Setting a prototype on a function whose stack purge is unknown makes Ghidra store the parameter bytes as its purge (a
`__cdecl` function then pops its own arguments in every caller's view). After each program's prototypes the purge of
every function just set is put back to the operand of its RET instructions when they all agree (needs Ghidra started
with GHIDRA_MCP_ALLOW_SCRIPTS=1)."""
import json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g
import export_raw

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# (no backslashes: the bridge un-escapes them in the script source)
PURGE_SCRIPT = """import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.scalar.Scalar;
import java.util.*;
public class ProtoPurge extends GhidraScript {
  public void run() throws Exception {
    int fixed = 0, odd = 0;
    for (String a : "%s".split(",")) {
      Function f = getFunctionAt(toAddr(a));
      if (f == null) continue;
      TreeSet<Long> rets = new TreeSet<>();
      InstructionIterator it = currentProgram.getListing().getInstructions(f.getBody(), true);
      while (it.hasNext()) {
        Instruction i = it.next();
        if (i.getMnemonicString().startsWith("RET")) {
          Scalar s = i.getNumOperands() > 0 ? i.getScalar(0) : null;
          rets.add(s == null ? 0L : s.getValue());
        }
      }
      if (rets.size() != 1) { odd++; continue; }
      int r = rets.first().intValue();
      if (f.getStackPurgeSize() != r) { f.setStackPurgeSize(r); fixed++; println("purge " + a + " " + f.getName() + " -> " + r); }
    }
    println("purges reset: " + fixed + ", no single RET operand: " + odd);
  }
}"""


def fix_purges(path, addrs):
    r = g.post("run_script_inline", code=PURGE_SCRIPT % ",".join(addrs), program=path)
    out = str(r.get("_raw", r) if isinstance(r, dict) else r)
    m = re.search(r"--- SCRIPT OUTPUT ---\s*(.*?)\s*===", out, re.S)
    print((m.group(1) if m else out[:300]).replace("\r", ""))


if __name__ == "__main__":
    files = [a for a in sys.argv[1:] if not a.startswith("--")]
    data = json.load(open(files[0] if files else os.path.join(ROOT, "names", "logic_protos.json")))
    for prog, items in data.items():
        if prog.startswith("_"):
            continue
        path = export_raw.PROGRAMS[prog]
        if "--dry" not in sys.argv:
            g.ensure_current(path)
        for addr, spec in items.items():
            if "--dry" in sys.argv:
                print(prog, addr, spec["proto"])
                continue
            g.ensure_current(path)   # (the bridge's write endpoints act on its current program; other sessions may switch it)
            r = g.set_prototype(path, addr, spec["proto"], spec.get("cc", ""))
            now = g.get("get_function_by_address", program=path, address=addr)
            m = re.search(r"^Signature: (.*)$", now, re.M)
            print(addr, "->", m.group(1) if m else now[:80], "|", str(r)[:60])
        if "--dry" not in sys.argv and items:
            fix_purges(path, list(items))
