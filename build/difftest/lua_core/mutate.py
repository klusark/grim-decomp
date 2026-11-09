"""mutate.py: applies each mutation below to a copy of build/overrides_lua_core.c, runs the differential test on it
(build.sh with OVR=, 30,000 cases, 120 s limit: a mutant that hangs where the original returns counts as caught)
and reports whether the test caught it."""
import os, subprocess, sys
ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
SRC = os.path.join(ROOT, "build", "overrides_lua_core.c")
OUT = os.path.join(ROOT, "build", "difftest", "lua_core", "out", "mut.c")
MUT = [
    ("depth not decremented", "    GL[2] = GL[2] - 1;\n", "\n"),
    ("error hook argument 4", "hookarg = 3;", "hookarg = 4;"),
    ("parser: no function -> 1", "return 2;", "return 1;"),
    ("C base read after luaD_openstack", "res = luaD_call((code *)(base + 1)", "res = luaD_call((code *)(GL[10] + 1)"),
    ("top not reset after error", "        GL[7] = GL[8] + GL[10] * 8;\n", "\n"),
    ("errorJmp not restored (run)", "    GL[0xd] = oldjmp;\n    GL[2]", "    GL[2]"),
    ("yield hook before the flag", "GL[4] = 1;", "GL[4] = 2;"),
    ("lvm__de20 chain: next read first", "for (c = (int *)t[0]; c != 0; c = (int *)c[3])\n                lvm__de20((int)c);",
     "for (c = (int *)t[0]; c != 0; ) { int *n2 = (int *)c[3]; lvm__de20((int)c); c = n2; }"),
    ("restart scan ignores the marked flag", "if (t[4] == 0 && t[5] == 0)", "if (t[4] == 0)"),
    ("unwind frees before unlinking", "            GL[0] = ((int *)e)[3];\n            lvm__dd90(e);", "            lvm__dd90(e);\n            GL[0] = ((int *)e)[3];"),
    ("closure tag", "= -4;", "= -3;"),
    ("updatetasks return inverted", "return lstate__8bf0((int)PTR_1002bf6c) != 0;", "return lstate__8bf0((int)PTR_1002bf6c) == 0;"),
]
text = open(SRC).read()
caught = 0
for name, a, b in MUT:
    if a not in text:
        print("NOT APPLIED:", name); continue
    open(OUT, "w", newline="\n").write(text.replace(a, b, 1))
    r = subprocess.run(["bash", "build/difftest/lua_core/build.sh", "30000"], cwd=ROOT, env=dict(os.environ, OVR=OUT, TEST_TIMEOUT="120"),
                       capture_output=True, text=True, timeout=600)
    ok = r.returncode != 0
    caught += ok
    how = "caught (hangs: the original returns)" if r.returncode == 124 else "caught"
    print("%-40s %s" % (name, how if ok else "NOT caught: " + r.stdout.strip().splitlines()[-1]), flush=True)
print("%d of %d caught" % (caught, len(MUT)))
