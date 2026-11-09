"""Take the functions of q5_funcs.h out of the assembly: their addresses out of names/asm_funcs.json (GRIMFANDANGO.EXE)
and their bodies out of src/GRIMFANDANGO.EXE/asm_funcs.s (with build/difftest/asm_p2/strip_asm.py).  The addresses
come from out/base_asm_funcs.s (the 2df265d assembly, made by run_all.sh).
usage: python -I take_out.py [--dry]"""
import json, os, re, subprocess, sys

ROOT = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", ".."))
D = os.path.join(ROOT, "build", "difftest", "asm_q5")
names = ["rdRaster_" + n for n in re.findall(r"^FN\(\w+, *(\w+)\)", open(os.path.join(D, "q5_funcs.h")).read(), re.M)]
asm = os.path.join(ROOT, "src", "GRIMFANDANGO.EXE", "asm_funcs.s")
text = open(asm).read()
btext = open(os.path.join(D, "out", "base_asm_funcs.s")).read()
addr = {}
for n in names:
    m = re.search(r"(?m)^_%s:\s+#.*\n\.L([0-9a-f]+)_" % re.escape(n), btext)
    addr[n] = "%08x" % int(m.group(1), 16)
still = [n for n in names if re.search(r"(?m)^_%s:" % re.escape(n), text)]
print("%d functions, %d still in the assembly" % (len(names), len(still)))
if "--dry" in sys.argv:
    sys.exit()
jpath = os.path.join(ROOT, "names", "asm_funcs.json")
raw = open(jpath).read()
j = json.loads(raw)
before = len(j["GRIMFANDANGO.EXE"])
drop = set(addr.values())
j["GRIMFANDANGO.EXE"] = [a for a in j["GRIMFANDANGO.EXE"] if a not in drop]
print("asm_funcs.json: %d -> %d" % (before, len(j["GRIMFANDANGO.EXE"])))
open(jpath, "w", newline="\n").write(json.dumps(j, indent=1) + ("\n" if raw.endswith("\n") else ""))
if still:
    subprocess.run([sys.executable, "-I", os.path.join(ROOT, "build", "difftest", "asm_p2", "strip_asm.py"), asm, asm] +
                   still, check=True)
