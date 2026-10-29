"""Scan .rdata/.data for arrays of {char *name, function *fn} pairs (Lua registration tables)
and report every table with its entries and the current Ghidra name of each function."""
import json, os, struct, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g

P = g.EXE
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
funcs = {int(f["address"], 16): f["name"] for f in g.get_json("list_functions_enhanced", program=P, limit=10000)["functions"]}
TEXT = (0x401000, 0x4D6200)

def read(addr, n):
    out = bytearray()
    while n > 0:
        k = min(n, 65536)
        out += bytes(g.get_json("read_memory", program=P, address=f"{addr:08x}", length=k)["data"])
        addr += k; n -= k
    return bytes(out)

regions = [(0x4D7000, 0x4DCA00), (0x4DD000, 0x4F6000)]
mem = {}
for lo, hi in regions:
    mem[lo] = read(lo, hi - lo)

def in_data(a):
    return any(lo <= a < lo + len(b) for lo, b in mem.items())

def cstr(a):
    for lo, b in mem.items():
        if lo <= a < lo + len(b):
            end = b.find(b"\0", a - lo)
            if end < 0 or end - (a - lo) > 64:
                return None
            s = b[a - lo:end]
            if len(s) == 0 or not all(32 <= c < 127 for c in s):
                return None
            return s.decode()
    return None

tables = []
for lo, b in mem.items():
    i = 0
    while i + 8 <= len(b):
        p, f = struct.unpack_from("<II", b, i)
        s = cstr(p) if in_data(p) else None
        if s and TEXT[0] <= f < TEXT[1]:
            start = i
            entries = []
            while i + 8 <= len(b):
                p, f = struct.unpack_from("<II", b, i)
                s = cstr(p) if in_data(p) else None
                if not (s and TEXT[0] <= f < TEXT[1]):
                    break
                entries.append((s, f))
                i += 8
            if len(entries) >= 2:
                tables.append((lo + start, entries))
            continue
        i += 4

for addr, entries in tables:
    print(f"== table at {addr:08x}: {len(entries)} entries")
    for s, f in entries:
        print(f"   {f:08x} {funcs.get(f, '(not a function)'):40s} {s}")
json.dump([{"table": f"{a:08x}", "entries": [{"name": s, "fn": f"{f:08x}"} for s, f in e]} for a, e in tables],
          open(os.path.join(ROOT, "raw", "lua_tables.json"), "w"), indent=1)
