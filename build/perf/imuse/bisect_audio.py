"""ddmin over IMUSE functions: python bisect.py  -> finds minimal sets that must stay assembled.
state in bisect_state.json: {"keep": [addresses forced to stay assembled], "results": {key: bool}}"""
import json, subprocess, sys, os, hashlib
ROOT = r"C:\Users\Joel\grim-agentN"
EX = os.path.join(ROOT, "names", "asm_exclude_imuse.json")
ALL = json.load(open("C:/Users/Joel/grimN_work/excl_full.json"))["IMUSE.DLL"]
ST = "bisect2_state.json"
state = json.load(open(ST)) if os.path.exists(ST) else {"keep": [], "results": {}}
def save(): json.dump(state, open(ST, "w"), indent=1)
def sh(cmd, timeout=1500):
    return subprocess.run(["bash", "-c", cmd], capture_output=True, text=True, timeout=timeout)
def test(conv):
    """conv = set of addresses compiled as C (others assembled). True = unit tier 120/0."""
    conv = sorted(set(conv) - set(state["keep"]))
    key = hashlib.md5(",".join(conv).encode()).hexdigest()
    if key in state["results"]:
        return state["results"][key]
    json.dump({"IMUSE.DLL": conv}, open(EX, "w"), indent=1)
    r = sh("/c/Users/Joel/grimN_work/imbuild.sh")
    if "failed" in r.stdout:
        print("BUILD FAILED", r.stdout[-500:]); sys.exit(1)
    r = sh("cd /c/Users/Joel/grimN_work && ./audlim.sh /c/Users/Joel/grim-agentN/build/run ln 300 && python audcmp.py aud_lb.txt aud_ln.txt")
    ok = "differ 0 " in r.stdout and "lines 300 300" in r.stdout
    print(f"test {len(conv)} funcs -> {ok}  [{r.stdout.strip().splitlines()[-2:] if r.stdout.strip() else r.stderr[-200:]}]", flush=True)
    state["results"][key] = ok; save()
    return ok
def ddmin(items):
    """smallest subset of items whose conversion (together with nothing else) fails, given that converting all items fails"""
    n = 2
    while len(items) >= 2:
        chunk = max(1, len(items) // n)
        subsets = [items[i:i + chunk] for i in range(0, len(items), chunk)]
        reduced = False
        for s in subsets:
            if not test(s):
                items = s; n = 2; reduced = True; break
        if reduced: continue
        for s in subsets:
            comp = [x for x in items if x not in s]
            if comp and not test(comp):
                items = comp; n = max(n - 1, 2); reduced = True; break
        if reduced: continue
        if n >= len(items): break
        n = min(len(items), n * 2)
    return items
if __name__ == "__main__":
    while True:
        rest = [a for a in ALL if a not in state["keep"]]
        if test(rest):
            print("ALL OK; keep assembled:", state["keep"]); break
        c = ddmin(rest)
        print("culprit set:", c, flush=True)
        state["keep"] += c; save()
