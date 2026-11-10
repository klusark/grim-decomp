"""Name every Lua opcode handler in GRIMFANDANGO.EXE from the engine's lua_openlib table
(raw/lua_opcodes.json, decoded from the {name, func} array at 0x004ea8b0)."""
import json, os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
data = json.load(open(os.path.join(ROOT, "raw", "lua_opcodes.json")))
P = g.EXE

# handlers shared by several opcodes get one deliberate name
SHARED = {
    "00497830": ("Lua_Stub", "Shared handler for opcodes that the shipped engine does not implement"),
    "0049ddd0": ("Lua_Print_NoOp", "PrintError / PrintWarning / PrintDebug: no-op in the release build"),
    "0049e960": ("Lua_IsMoviePlaying", "also registered as IsFullscreenMoviePlaying"),
    "004a0f80": ("sputLua_ImStartSound", "also registered as `play`"),
    "004a1080": ("sputLua_ImStopAllSounds", "also registered as `quiet`"),
    "004a17b0": ("sputLua_ImSetVoiceEffect", "also registered as `vfx`"),
}
FALLBACK_NAMES = {"concatfallback": "sputLua_ConcatFallback", "typeoverride": "sputLua_TypeOverride"}

funcs = {f["address"]: f for f in g.get_json("list_functions_enhanced", program=P, limit=10000)["functions"]}

by_addr = {}
for addr, name in data["engine"]:
    by_addr.setdefault(addr, []).append(name)
for addr, name in data["fallbacks"]:
    n = name.strip()
    if n in FALLBACK_NAMES:
        by_addr.setdefault(addr, []).append(FALLBACK_NAMES[n])

created = renamed = skipped = failed = 0
tag_assignments = []
for addr, names in sorted(by_addr.items()):
    if addr in SHARED:
        new, comment = SHARED[addr]
        comment = f"Lua opcodes: {', '.join(names)}\n{comment}"
    else:
        n = names[0]
        new = n if n.startswith("Lua_") else "Lua_" + n
        comment = f"Lua opcode: {n}"
    if addr not in funcs:
        r = g.create_function(P, addr)
        if not g.ok(r):
            print("create failed", addr, r); failed += 1; continue
        created += 1
    cur = funcs.get(addr, {}).get("name", "")
    if cur != new:
        r = g.rename_function(P, addr, new)
        if not g.ok(r):
            print("rename failed", addr, new, r); failed += 1; continue
        renamed += 1
    else:
        skipped += 1
    g.set_plate_comment(P, addr, comment)
    tag_assignments.append({"function": addr, "tags": "lua-binding,src:Scripts/sputLua.cpp"})

# the registration wrapper and the tables themselves
g.rename_function(P, "0049ca60", "Lua_OpenEngineLib")
g.set_plate_comment(P, "0049ca60", "lua_openlib() wrapper used to register the 279-entry engine opcode table at 0x004ea8b0")
g.rename_or_label(P, "004ea8b0", "g_engineLuaLib")
g.rename_or_label(P, "004ea890", "g_engineLuaFallbacks")
r = g.batch_tags(P, tag_assignments)
print("tags:", str(r)[:200])
print(f"created {created}, renamed {renamed}, already-named {skipped}, failed {failed}")
