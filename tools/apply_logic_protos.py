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


# Ghidra's x86 __cdecl model aligns an 8-byte stack argument to 8; MSVC does not (Palette_FromFloatTable's double after
# three dwords sits at [esp+0x10], Ghidra put it at 0x14). An entry {"stack": {"<param>": <offset>}} switches the
# function to custom storage and puts each named parameter at its offset (the others keep theirs).
STORAGE_SCRIPT = """import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.SourceType;
public class ProtoStack extends GhidraScript {
  public void run() throws Exception {
    Function f = getFunctionAt(toAddr("%s"));
    f.setCustomVariableStorage(true);
    String[] want = "%s".split(",");
    for (Parameter p : f.getParameters()) {
      for (String w : want) {
        String[] kv = w.split("=");
        if (!kv[0].equals(p.getName())) continue;
        VariableStorage st = new VariableStorage(currentProgram, Integer.parseInt(kv[1]), p.getLength());
        p.setDataType(p.getDataType(), st, true, SourceType.USER_DEFINED);
      }
    }
    for (Parameter p : f.getParameters()) println(p.getName() + " " + p.getVariableStorage());
  }
}"""


# An entry {"registers": {"<param>": "<register>"}} puts the named parameters in registers (custom storage): LUA.DLL's
# _ftol takes its operand in ST0, which the decompiler then shows as the call's argument. The key "<return>" puts the
# return value in a register too (the x87 helpers return in ST0; without it Ghidra stores a float10 result through a
# hidden __return_storage_ptr__, which is dropped).
REGISTER_SCRIPT = """import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.SourceType;
import java.util.*;
public class ProtoRegs extends GhidraScript {
  public void run() throws Exception {
    Function f = getFunctionAt(toAddr("%s"));
    Map<String, String> want = new HashMap<>();
    for (String w : "%s".split(",")) { String[] kv = w.split("="); want.put(kv[0], kv[1]); }
    ghidra.program.model.data.DataType rt = f.getReturnType();
    List<Parameter> ps = new ArrayList<>();
    for (Parameter p : f.getParameters()) {
      if (p.getName().equals("__return_storage_ptr__")) {   // (the hidden result pointer: the result's own type)
        if (p.getDataType() instanceof ghidra.program.model.data.Pointer)
          rt = ((ghidra.program.model.data.Pointer) p.getDataType()).getDataType();
        continue;
      }
      String r = want.get(p.getName());
      VariableStorage st = r == null ? p.getVariableStorage()
          : new VariableStorage(currentProgram, currentProgram.getRegister(r));
      ps.add(new ParameterImpl(p.getName(), p.getDataType(), st, currentProgram));
    }
    f.setCustomVariableStorage(true);
    f.replaceParameters(ps, Function.FunctionUpdateType.CUSTOM_STORAGE, true, SourceType.USER_DEFINED);
    if (want.containsKey("<return>"))
      f.setReturn(rt, new VariableStorage(currentProgram, currentProgram.getRegister(want.get("<return>"))),
                  SourceType.USER_DEFINED);
    for (Parameter p : f.getParameters()) println(p.getName() + " " + p.getVariableStorage());
    println("return " + f.getReturn().getVariableStorage());
  }
}"""


def fix_registers(path, addr, regs):
    r = g.post("run_script_inline", code=REGISTER_SCRIPT % (addr, ",".join("%s=%s" % kv for kv in regs.items())),
               program=path)
    out = str(r.get("_raw", r) if isinstance(r, dict) else r)
    m = re.search(r"--- SCRIPT OUTPUT ---\s*(.*?)\s*===", out, re.S)
    print(addr, "registers:", (m.group(1) if m else out[:300]).replace(chr(13), "").replace(chr(10), "; "))


def fix_stack(path, addr, stack):
    r = g.post("run_script_inline", code=STORAGE_SCRIPT % (addr, ",".join("%s=%d" % kv for kv in stack.items())),
               program=path)
    out = str(r.get("_raw", r) if isinstance(r, dict) else r)
    m = re.search(r"--- SCRIPT OUTPUT ---\s*(.*?)\s*===", out, re.S)
    print(addr, "stack:", (m.group(1) if m else out[:300]).replace(chr(13), "").replace(chr(10), "; "))


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
            if spec.get("stack"):
                fix_stack(path, addr, spec["stack"])
            if spec.get("registers"):
                fix_registers(path, addr, spec["registers"])
        if "--dry" not in sys.argv and items:
            fix_purges(path, list(items))
