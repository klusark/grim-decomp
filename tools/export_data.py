"""Dump the initialised data sections of each program from Ghidra.

Writes raw/<prog>/sections/<name>.bin and raw/<prog>/sections.json
({name, start, size}) for every non-code section (.rdata, .data, .idata ...)
listed in raw/<prog>/segments.txt.  Reads go through the bridge's read_memory
endpoint in 32 KB pieces; bytes Ghidra has no initialised value for come back
as zeros, which is what the loader would give too.

Usage: python -I export_data.py [prog...]   (run from tools/)
"""
import json, os, sys, urllib.request, urllib.parse
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PROGRAMS = {"GRIMFANDANGO.EXE": g.EXE, "LUA.DLL": g.LUA, "IMUSE.DLL": g.IMUSE, "CHORE.DLL": g.CHORE}
SKIP = {"Headers", ".text", ".rsrc", ".reloc"}
CHUNK = 0x8000


def read(prog, addr, n):
    q = urllib.parse.urlencode({"program": prog, "address": "%08x" % addr, "length": n})
    with urllib.request.urlopen("http://127.0.0.1:8089/read_memory?" + q, timeout=120) as r:
        d = json.loads(r.read())
    if "hex" not in d:
        return b"\0" * n
    b = bytes.fromhex(d["hex"])
    return b + b"\0" * (n - len(b)) if len(b) < n else b[:n]


def dump(raw, prog):
    out = os.path.join(ROOT, "raw", raw, "sections")
    os.makedirs(out, exist_ok=True)
    secs = []
    for line in open(os.path.join(ROOT, "raw", raw, "segments.txt")):
        line = line.strip()
        if ":" not in line:
            continue
        name, rng = line.split(":", 1)
        name = name.strip()
        if name in SKIP and name != ".text":
            continue
        lo, hi = [int(x, 16) for x in rng.strip().split(" - ")]
        size = hi - lo + 1
        data = bytearray()
        a = lo
        while a <= hi:
            n = min(CHUNK, hi - a + 1)
            data += read(prog, a, n)
            a += n
        # trailing zeros are the loader-filled part; keep the file short
        stripped = bytes(data).rstrip(b"\0")
        fn = name.strip(".") + ".bin"
        open(os.path.join(out, fn), "wb").write(stripped)
        if name == ".text":
            # the code bytes are kept as a data blob too (build/gendata.py _sect_text): the code section
            # holds data islands (DirectInput's c_dfDIKeyboard, switch tables) that code addresses
            json.dump({"start": "%08x" % lo, "size": size, "file": fn}, open(os.path.join(ROOT, "raw", raw, "textblob.json"), "w"))
            continue
        secs.append({"name": name, "start": "%08x" % lo, "size": size, "file": fn, "initialised": len(stripped)})
        print(f"  {raw} {name}: {size} bytes, {len(stripped)} initialised")
    json.dump(secs, open(os.path.join(ROOT, "raw", raw, "sections.json"), "w"), indent=1)


if __name__ == "__main__":
    progs = sys.argv[1:] or list(PROGRAMS)
    for p in progs:
        dump(p, PROGRAMS[p])
