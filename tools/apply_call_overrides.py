"""Applies names/callsite_overrides.json to the live Ghidra project: a signature for each listed indirect call site, so
the decompiler passes the call its arguments (COM vtable calls, service-table calls).

  python -I tools/apply_call_overrides.py [--dry] [names/<file>.json]   (default names/callsite_overrides.json)

An entry {"func": "<function address>", "call": "<CALL address>", "args": n, "cc": "__stdcall" | "__cdecl"} writes a
call-site override (HighFunctionDBUtil.writeOverride) of `undefined4 f(undefined4 a0, .., undefined4 a<n-1>)` in that
calling convention. Every entry is idempotent; the function is journaled for tools/export_changed.py. Needs Ghidra
started with GHIDRA_MCP_ALLOW_SCRIPTS=1."""
import json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g
import export_raw

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# (no backslashes: the bridge un-escapes them in the script source)
SCRIPT = """import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.data.*;
import ghidra.program.model.pcode.HighFunctionDBUtil;
public class CallOverrides extends GhidraScript {
  public void run() throws Exception {
    int done = 0;
    for (String e : "%s".split(",")) {
      String[] f = e.split(":");
      Function fn = getFunctionAt(toAddr(f[0]));
      int n = Integer.parseInt(f[2]);
      FunctionDefinitionDataType sig = new FunctionDefinitionDataType("callsite_" + f[1]);
      ParameterDefinition[] ps = new ParameterDefinition[n];
      for (int i = 0; i < n; i++) ps[i] = new ParameterDefinitionImpl("a" + i, Undefined4DataType.dataType, null);
      sig.setArguments(ps);
      sig.setReturnType(Undefined4DataType.dataType);
      sig.setCallingConvention(f[3]);
      HighFunctionDBUtil.writeOverride(fn, toAddr(f[1]), sig);
      done++;
    }
    println("overrides written: " + done);
  }
}"""


if __name__ == "__main__":
    files = [a for a in sys.argv[1:] if not a.startswith("--")]
    data = json.load(open(files[0] if files else os.path.join(ROOT, "names", "callsite_overrides.json")))
    for prog, items in data.items():
        if prog.startswith("_") or not items:
            continue
        path = export_raw.PROGRAMS[prog]
        spec = ",".join("%s:%s:%d:%s" % (e["func"], e["call"], e["args"], e["cc"]) for e in items)
        if "--dry" in sys.argv:
            print(prog, spec)
            continue
        r = g.post("run_script_inline", code=SCRIPT % spec, program=path)
        out = str(r.get("_raw", r) if isinstance(r, dict) else r)
        m = re.search(r"--- SCRIPT OUTPUT ---\s*(.*?)\s*===", out, re.S)
        print(prog, (m.group(1) if m else out[:600]).replace("\r", ""))
        for a in sorted({e["func"] for e in items}):   # (journaled: the overridden calls change these functions only)
            g._touched.setdefault(path, set()).add(a)
