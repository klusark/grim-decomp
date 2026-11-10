"""Dump a Ghidra program for tools/orig_match.py: functions, call graph edges and decompiled text.

Usage: python -I orig_dump.py <program path> <out.json> [--no-code]      (run from tools/)
e.g.   python -I orig_dump.py /linux/libLua.so C:/tmp/liblua.json

For the v1.01 programs orig_match.py reads the decompiled text from raw/<prog>/functions/*.c instead (--no-code
still dumps their call graph).  The output is a cache, not part of the tree."""
import json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g

EDGE_RE = re.compile(r"^(.*)@([0-9a-f]{8}) -> (.*)@([0-9a-f]{8})\s*$")


def dump(prog, out, code=True):
    funcs = g.get_json("list_functions_enhanced", program=prog, limit=50000)
    funcs = funcs.get("functions", funcs)
    edges = []
    for line in g.get("get_full_call_graph", program=prog, format="edges", limit=1000000).splitlines():
        m = EDGE_RE.match(line)
        if m:
            edges.append([m.group(2), m.group(4)])
    res = {"program": prog, "funcs": funcs, "edges": edges, "code": {}}
    if code:
        todo = [f["address"] for f in funcs if not f["isThunk"] and not f["isExternal"]]
        for i in range(0, len(todo), 20):
            chunk = todo[i:i + 20]
            r = g.get_json("batch_decompile", program=prog, functions=",".join(chunk))
            for a in chunk:
                if isinstance(r.get(a), str):
                    res["code"][a] = r[a]
            if i % 400 == 0:
                print(f"{prog}: {i}/{len(todo)}", flush=True)
    json.dump(res, open(out, "w"))
    print(f"{prog}: {len(funcs)} functions, {len(edges)} edges, {len(res['code'])} decompiled -> {out}")


if __name__ == "__main__":
    dump(sys.argv[1], sys.argv[2], "--no-code" not in sys.argv)
