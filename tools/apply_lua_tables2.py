"""Apply names from the smaller Lua registration tables (display, primitives, text, costume)
and from the subsystem init table at 0x004e7dc0 ({fn, name} pairs)."""
import json, os, struct, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g

P = g.EXE
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
tables = {t["table"]: t["entries"] for t in json.load(open(os.path.join(ROOT, "raw", "lua_tables.json")))}
funcs = {f["address"]: f["name"] for f in g.get_json("list_functions_enhanced", program=P, limit=10000)["functions"]}

def ensure_named(addr, name, comment, tags):
    if addr not in funcs:
        r = g.create_function(P, addr)
        if not g.ok(r):
            print("create failed", addr, r); return
        funcs[addr] = "FUN_" + addr
    if funcs[addr] != name:
        r = g.rename_function(P, addr, name)
        if not g.ok(r):
            print("rename failed", addr, name, str(r)[:120]); return
        funcs[addr] = name
    if comment:
        g.set_plate_comment(P, addr, comment)
    g.add_tag(P, addr, tags)

LUA_TABLES = {"004dd350": "src:grimdemo.c", "004e8398": "src:Engine/sputPrimitive.cpp",
              "004e8528": "src:Engine/sputText.cpp", "004ea058": "src:Engine/sputCostume.cpp"}
for taddr, tag in LUA_TABLES.items():
    for e in tables[taddr]:
        ensure_named(e["fn"], "Lua_" + e["name"], f"Lua opcode: {e['name']}", "lua-binding," + tag)
    g.rename_or_label(P, taddr, {"004dd350": "g_displayLuaLib", "004e8398": "g_primitiveLuaLib",
                                 "004e8528": "g_textLuaLib", "004ea058": "g_costumeLuaLib"}[taddr])

# subsystem init table: {fn, name} pairs starting at 0x4e7dc0 (8 entries) and 0x4e7e00 (6 entries)
raw = bytes(g.get_json("read_memory", program=P, address="004e7dc0", length=0x70)["data"])
inits = []
for i in range(14):
    fn, nm = struct.unpack_from("<II", raw, i * 8)
    if not fn:
        continue
    s = bytes(g.get_json("read_memory", program=P, address=f"{nm:08x}", length=48)["data"]).split(b"\0")[0].decode()
    inits.append((f"{fn:08x}", s))
    ensure_named(f"{fn:08x}", s, f"Subsystem init entry registered through grimlib_GameInitialize; fills the module's 8-entry interface {{init, shutdown, save, restore, ...}}", "services,subsystem-init")
    print(f"{fn:08x} {s}")
g.rename_or_label(P, "004e7dc0", "g_engineSubsystemInits")
g.rename_or_label(P, "004e7e00", "g_engineSubsystemInits2")
json.dump(inits, open(os.path.join(ROOT, "raw", "subsystem_inits.json"), "w"), indent=1)
