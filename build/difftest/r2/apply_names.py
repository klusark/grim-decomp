"""One-off edit of the names/ json files for round r2 (kept for the record; idempotent):
take the last 21 assembled functions of GRIMFANDANGO.EXE and LUA.DLL out of names/asm_funcs.json, list the dead ones in
names/lib_replace.json ("dead": trap stub if anything still names them), _ftol in "host" (msvcrt.dll's _ftol, the same
machine code), and record what happened in the reasons files.  FUN_004addf0 (__chkstk) becomes a jump to libgcc's
___chkstk in build/overrides_r2.c (no names/ entry needed)."""
import json
import os

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
EXE_FUNCLETS = ["004d5e1c", "004d5e30", "004d6030", "004d6050", "004d6070", "004d6090", "004d609e", "004d60ac",
                "004d60d0", "004d60db", "004d6100"]
LUA_FUNCLETS = ["10021fb0", "10021fd0", "10021fdb", "10021ff0", "10022010", "10022030", "10022050"]
EXE_DEAD = ["0042003c"] + EXE_FUNCLETS
EXE_HOST = ["004ac6f0"]
EXE_OVERRIDE = ["004addf0"]


def load(p):
    return json.load(open(os.path.join(ROOT, p)))


def save(p, d, nl=False):
    open(os.path.join(ROOT, p), "w", newline="\n").write(json.dumps(d, indent=1) + ("\n" if nl else ""))


def add(lst, addrs):
    for a in addrs:
        if a not in lst:
            lst.append(a)


lr = load("names/lib_replace.json")
add(lr["GRIMFANDANGO.EXE"]["dead"], EXE_DEAD)
add(lr["GRIMFANDANGO.EXE"]["host"], EXE_HOST)
add(lr["LUA.DLL"]["dead"], LUA_FUNCLETS)
save("names/lib_replace.json", lr)

af_text = open(os.path.join(ROOT, "names/asm_funcs.json")).read()
af = json.loads(af_text)
gone = set(EXE_DEAD + EXE_HOST + EXE_OVERRIDE + LUA_FUNCLETS)
for prog in ("GRIMFANDANGO.EXE", "LUA.DLL"):
    af[prog] = [a for a in af[prog] if a not in gone]
save("names/asm_funcs.json", af, nl=af_text.endswith("\n"))

why_funclet = ("no longer built (round r2): {kind} of {parent}; reached only through {table} in the data image, which "
               "nothing in the rebuilt program uses (the parent is gcc C and registers no frame that reads it); "
               "names/lib_replace.json \"dead\", the table entry resolves to a trap stub (docs/notes/r2.md)")
EXE_PARENT = {
    "004d5e1c": ("SEH filter funclet", "FUN_004d5de0 (the CRT longjmp's frame probe, dead)", "the _except_handler3 scope table 0x004dac00"),
    "004d5e30": ("SEH handler funclet", "FUN_004d5de0 (the CRT longjmp's frame probe, dead)", "the _except_handler3 scope table 0x004dac00"),
    "004d6030": ("C++ unwind funclet", "PrimitiveList_Append", "the FuncInfo 0x004dac10"),
    "004d6050": ("C++ unwind funclet", "sputActor_EnablePuck", "the FuncInfo 0x004dac40"),
    "004d6070": ("C++ unwind funclet", "sputRoom_AddObjectState", "the FuncInfo 0x004dac68"),
    "004d6090": ("C++ unwind funclet", "SetFile_ParseSectors", "the FuncInfo 0x004dac90"),
    "004d609e": ("C++ unwind funclet", "SetFile_ParseSectors", "the FuncInfo 0x004dac90"),
    "004d60ac": ("C++ unwind funclet", "SetFile_ParseSectors", "the FuncInfo 0x004dac90"),
    "004d60d0": ("C++ unwind funclet", "ObjectState_Construct", "the FuncInfo 0x004dacc8"),
    "004d60db": ("C++ unwind funclet", "ObjectState_Construct", "the FuncInfo 0x004dacc8"),
    "004d6100": ("C++ unwind funclet", "ObjectState_Destruct", "the FuncInfo 0x004dacf8"),
}
LUA_PARENT = {
    "10021fb0": ("luaI_startscript", "0x10024df8"), "10021fd0": ("luaD_call", "0x10024e20"),
    "10021fdb": ("luaD_call", "0x10024e20"), "10021ff0": ("LState_Restore", "0x10024e50"),
    "10022010": ("lua_newstate", "0x10024e78"), "10022030": ("ExecutionState_Restore", "0x10024ea0"),
    "10022050": ("ExecutionState_New", "0x10024ec8"),
}
rl = load("names/asm_reasons_logic.json")
for a, (k, p, t) in EXE_PARENT.items():
    rl["GRIMFANDANGO.EXE"][a] = why_funclet.format(kind=k, parent=p, table=t)
rl["GRIMFANDANGO.EXE"]["004ac6f0"] = ("no longer built (round r2): _ftol has no caller in the rebuilt exe (the C code converts with "
                                      "FTOL()/gcc); names/lib_replace.json \"host\": the symbol resolves to msvcrt.dll's _ftol, "
                                      "the same instructions (differential test build/difftest/r2)")
rl["GRIMFANDANGO.EXE"]["004addf0"] = ("no longer built (round r2): __chkstk has no caller in the rebuilt exe; build/overrides_r2.c "
                                      "makes the symbol a jump to libgcc's ___chkstk (same ABI: EAX = size, moves ESP; "
                                      "differential test build/difftest/r2)")
for a, (p, t) in LUA_PARENT.items():
    rl["LUA.DLL"][a] = why_funclet.format(kind="C++ unwind funclet", parent=p, table="the FuncInfo " + t)
save("names/asm_reasons_logic.json", rl, nl=True)

r = load("names/asm_reasons.json")
r["0042003c"] = ("no longer built (round r2): the dead loop tail of rdNRaster_DrawScanLineNGonTGAT_8 (not a function; nothing calls it, "
                 "its only reference was a false pointer that build/gendata.py made of two entries of the VIMA step table "
                 "0x004daa58); names/lib_replace.json \"dead\"")
save("names/asm_reasons.json", r, nl=True)
print("done")
