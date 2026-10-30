"""Re-export the decompilation of every function in an address range from Ghidra into raw/<prog>/functions/.
raw/ goes stale when prototypes/types are edited in Ghidra (callers are not re-exported by hand edits), so run this
after a batch of Ghidra edits:   python -I export_range.py [lo hi] [--threads N] [addr ...]
Default range: the low half of the EXE, 0x401000-0x49ffff. Individual addresses re-export just those functions.
"""
import json, os, sys, threading, queue
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PROG, PATH = "GRIMFANDANGO.EXE", "/v101/GRIMFANDANGO.EXE"


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    nthreads = 4
    if "--threads" in sys.argv:
        nthreads = int(sys.argv[sys.argv.index("--threads") + 1])
        args = [a for a in args if a != str(nthreads)]
    g.get("switch_program", program=PATH)
    funcs = json.load(open(os.path.join(ROOT, "raw", PROG, "functions.json")))
    if len(args) == 2:
        lo, hi = int(args[0], 16), int(args[1], 16)
        todo = [f["address"] for f in funcs if lo <= int(f["address"], 16) < hi and not f.get("isThunk") and not f.get("isExternal")]
    elif args:
        todo = args
    else:
        todo = [f["address"] for f in funcs if 0x401000 <= int(f["address"], 16) < 0x4a0000 and not f.get("isThunk") and not f.get("isExternal")]
    q = queue.Queue()
    for a in todo:
        q.put(a)
    changed = []
    lock = threading.Lock()

    def work():
        while True:
            try:
                a = q.get_nowait()
            except queue.Empty:
                return
            code = g.get("decompile_function", program=PATH, address=a).replace("\r\n", "\n")
            p = os.path.join(ROOT, "raw", PROG, "functions", a + ".c")
            old = open(p, encoding="utf-8", errors="replace").read() if os.path.exists(p) else ""
            if code != old:
                with open(p, "w", newline="\n", encoding="utf-8") as fh:
                    fh.write(code)
                with lock:
                    changed.append(a)

    ts = [threading.Thread(target=work) for _ in range(nthreads)]
    [t.start() for t in ts]
    [t.join() for t in ts]
    print("re-exported %d functions, %d changed" % (len(todo), len(changed)))
    json.dump(sorted(changed), open(os.path.join(ROOT, "raw", "export_range_changed.json"), "w"))


if __name__ == "__main__":
    main()
