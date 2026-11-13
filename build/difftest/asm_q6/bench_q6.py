r"""Frame time per set for the rasteriser port (agent q4; copy for agent q6 with its own command / log files and window name): like build/perf/benchsets.py, but with its own command / log
files and window title (other agents may run games at the same time) and it kills only the process it started.
Office idle, office with Manny walking, then a tour of 12 sets (movies off); prints the median in-process
`perf:` ms/frame of each dwell (GRIM_PERFLOG=1, see build/fastpaths.c).

usage: python -I bench_q4.py <exe-dir> [dwell_s] [k=v env ...]
"""
import os, re, statistics, subprocess, sys, time

D = os.path.join(os.path.dirname(os.path.abspath(__file__)), "out")
os.makedirs(D, exist_ok=True)
CMD = os.path.join(D, "q6_cmd.lua")
LOG = os.path.join(D, "q6_log.txt")
GAME = r"C:\GOG Games\GRIMDATA"
exe = sys.argv[1]
dwell = float(sys.argv[2]) if len(sys.argv) > 2 and "=" not in sys.argv[2] else 4.0
env = dict(os.environ, GRIM_MULTI="q6bench", GRIM_NOMOVIE="1", GRIM_LUA_FILE=CMD, GRIM_LUA_LOG=LOG,
           _NO_DEBUG_HEAP="1", GRIM_PERFLOG="1")
for a in sys.argv[2:]:
    if "=" in a:
        k, v = a.split("=", 1)
        env[k] = v
open(CMD, "w").close()
try:
    os.remove(LOG)
except OSError:
    pass


def log():
    try:
        return open(LOG, errors="replace").read().splitlines()
    except OSError:
        return []


def cmd(s):
    open(CMD, "a").write(s + "\n")


def measure(tag):
    time.sleep(1.0)
    n0 = len(log())
    time.sleep(dwell)
    ms = [float(re.search(r"([\d.]+) ms/frame", l).group(1)) for l in log()[n0:] if l.startswith("perf")]
    if ms:
        print("%-12s %.3f ms/frame  n=%d" % (tag, statistics.median(ms), len(ms)), flush=True)
        return statistics.median(ms)
    print("%-12s no perf lines" % tag, flush=True)
    return None


p = subprocess.Popen([os.path.join(exe, "grimfandango.exe")], cwd=GAME, env=env,
                     stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
try:
    t0 = time.time()
    while not any("lua hook active" in l for l in log()):
        if time.time() - t0 > 60:
            sys.exit("no lua hook")
        time.sleep(0.2)
    time.sleep(2.0)
    res = {}
    res["office"] = measure("office idle")
    cmd(open(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", "perf", "walk.lua")).read().strip().replace("\n", " "))
    res["walk"] = measure("office walk")
    cmd('function T(n) local s=system.setTable[n] s:switch_to_set() grimlog("SW "..n) end')
    sets = ["mo.set", "ha.set", "ga.set", "bi.set", "lr.set", "mx.set", "ce.set", "do.set", "hf.set", "sh.set", "vd.set",
            "tu.set"]
    tot = []
    for s in sets:
        cmd('T("%s")' % s)
        t0 = time.time()
        while not any(l == "SW " + s for l in log()[-300:]):
            if time.time() - t0 > 30:
                break
            time.sleep(0.1)
        m = measure(s)
        if m is not None:
            tot.append(m)
    if tot:
        print("mean of set medians: %.3f ms/frame (%d sets)" % (sum(tot) / len(tot), len(tot)))
finally:
    p.kill()
