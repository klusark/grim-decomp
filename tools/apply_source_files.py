"""Tag EXE functions with the original source file they came from.

Evidence: the engine allocator takes __FILE__/__LINE__, so functions that allocate name their
file outright (raw/exe_filemap.json for grimsrc; grimjedi files are matched by string symbol).
Object files are laid out contiguously by the linker and the known spans do not overlap, so
every function inside a file's [first, last] span is tagged `src:<file>`; functions in the
gaps between spans stay untagged (unknown file). The Lua opcode handlers extend the
sputLua.cpp span."""
import glob, json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
P = g.EXE
RAWF = os.path.join(ROOT, "raw", "GRIMFANDANGO.EXE", "functions")

# address -> short file name, for every C:\grim... source-path string in the binary
strings = {}
for filt in ("grimsrc", "grimjedi"):
    for line in g.get("list_strings", program=P, filter=filt, limit=500).splitlines():
        m = re.match(r'([0-9a-f]{8}): "C:\\grim\w+\\(.*)"', line)
        if m:
            strings[m.group(1)] = m.group(2).replace("\\", "/")
            if strings[m.group(1)].startswith("tools/grimdemo/"):
                strings[m.group(1)] = strings[m.group(1)][len("tools/grimdemo/"):]
            elif strings[m.group(1)].startswith("libs/grimlib/"):
                strings[m.group(1)] = strings[m.group(1)][len("libs/grimlib/"):]
            elif strings[m.group(1)].startswith("Libs/"):
                strings[m.group(1)] = "jedi/" + strings[m.group(1)][len("Libs/"):]
ref_re = re.compile(r"s_C__grim\w*?_(00[0-9a-f]{6})\b(?:,\s*(0x[0-9a-f]+|\d+)\))?")

known = {}   # func addr -> {file: (minline, maxline) or None}
for path in glob.glob(os.path.join(RAWF, "*.c")):
    code = open(path, encoding="utf-8", errors="replace").read()
    addr = os.path.basename(path)[:-2]
    for saddr, line in ref_re.findall(code):
        f = strings.get(saddr)
        if not f:
            continue
        d = known.setdefault(addr, {})
        if line:
            ln = int(line, 0)
            lo, hi = d.get(f) or (ln, ln)
            d[f] = (min(lo, ln), max(hi, ln))
        else:
            d.setdefault(f, None)

# manual anchors from reading the code: functions known to belong to a file although they
# never pass __FILE__ to the allocator (extend the spans)
ANCHORS = {
    "00480230": "Temp/Res.c",
    "004839f0": "Engine/sputRender.cpp",
    "00483d40": "Engine/sputRender.cpp",
    "004888d0": "Temp/Memory.c",
    "00488c80": "Temp/Fileutil.c",
    "00488fb0": "Engine/sputSmush.cpp",
    "00489550": "Engine/sputPrimitive.cpp",
    "0048ac00": "Engine/sputText.cpp",
    "0048cba0": "Engine/sputText.cpp",
    "0048d050": "Engine/sputControl.cpp",
    "0048d340": "Main/sputresource.cpp",
    "0048e0a0": "Main/sputresource.cpp",
    "0048e240": "Engine/sputActor.cpp",
    "0048f920": "Engine/sputActor.cpp",
    "004946b0": "Engine/sputCostume.cpp",
    "00498bf0": "Engine/sputCostume.cpp",
    "00498d80": "Scripts/sputLua.cpp",
    "004a3be0": "Engine/sputTime.cpp",
    "004a3d00": "Engine/sputTime.cpp",
    "004a3db0": "Engine/sputRoom.cpp",
    "004aa070": "Engine/ObjectState.cpp",
    "004aa7b0": "Temp/Text.c",
    "004abe90": "Win95/grimplat.cpp",
    "004ac1f0": "Win95/grimplat.cpp",
    "00487650": "Win95/grimplat.cpp",
}
for addr, f in ANCHORS.items():
    known.setdefault(addr, {}).setdefault(f, None)

ops = json.load(open(os.path.join(ROOT, "raw", "lua_opcodes.json")))
funcs = sorted(g.get_json("list_functions_enhanced", program=P, limit=10000)["functions"],
               key=lambda f: int(f["address"], 16))

spans = {}
for addr, files in known.items():
    a = int(addr, 16)
    for f, lines in files.items():
        s = spans.setdefault(f, [a, a, {}])
        s[0], s[1] = min(s[0], a), max(s[1], a)
        s[2][addr] = lines
lua_addrs = [int(a, 16) for a, _ in ops["engine"] if 0x498d80 <= int(a, 16) <= 0x4a3c00]
s = spans["Scripts/sputLua.cpp"]
s[0], s[1] = min(s[0], min(lua_addrs)), max(s[1], max(lua_addrs))

ordered = sorted(spans.items(), key=lambda kv: kv[1][0])
for i in range(len(ordered) - 1):
    if ordered[i][1][1] >= ordered[i + 1][1][0]:
        print("OVERLAP", ordered[i][0], ordered[i + 1][0], hex(ordered[i][1][1]), hex(ordered[i + 1][1][0]))

assignments, comments = [], 0
for f in funcs:
    a = int(f["address"], 16)
    for file, (lo, hi, kn) in ordered:
        if lo <= a <= hi:
            assignments.append({"function": f["address"], "tags": f"src:{file}"})
            if f["address"] in kn and kn[f["address"]]:
                l0, l1 = kn[f["address"]]
                where = f"line {l0}" if l0 == l1 else f"lines {l0}-{l1}"
                g.set_plate_comment(P, f["address"], f"Source: {file} ({where}, from __FILE__/__LINE__ passed to the allocator)")
                comments += 1
            break
r = g.batch_tags(P, assignments)
print("tagged", r.get("functions_touched"), "functions; plate comments:", comments)
with open(os.path.join(ROOT, "raw", "exe_source_spans.json"), "w") as w:
    json.dump({f: {"first": f"{lo:08x}", "last": f"{hi:08x}", "known": k} for f, (lo, hi, k) in ordered}, w, indent=1)
for file, (lo, hi, k) in ordered:
    n = sum(1 for f in funcs if lo <= int(f["address"], 16) <= hi)
    print(f"{file:32s} {lo:08x}-{hi:08x} {n:4d} functions ({len(k)} proven)")
