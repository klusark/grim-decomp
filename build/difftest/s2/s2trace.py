# gdb script (agent s2): the music-state transitions of a scenario with their time base.
# At every entry of FUN_10006560 (ImSetState) / Script_SetSequence (ImSetSequence): the id, the wall-clock time, the number of
# frames (GRIM_lua_cmd_poll calls of the rebuilt EXE) and of fade steps (FdIntHandler calls = iMUSE heartbeats) so far;
# the iMUSE calls Script_Trans makes (as build/difftest/imuse_r1/frametrace.py); every ImStopSound with the same stamp.
#   S2_MODE=orig  the original IMUSE.DLL (no symbols, preferred base 0x10000000 moved by the load base)
#   S2_MODE=sym   a rebuilt imuse.dll with symbols (FT_LEN = length of Script_Trans's code, hex)
#   S2_OUT        output file
import gdb, struct, os, time

fo = open(os.environ.get("S2_OUT", "s2.txt"), "w")
MODE = os.environ.get("S2_MODE", "sym")
ORIG = {"Script_Trans": 0x100068b0, "FUN_10006560": 0x10006560, "Script_SetSequence": 0x10006620,
        "ImSwitchStream": 0x10004ec0, "ImSetHook": 0x10004db0, "ImFadeParam": 0x10004d90, "ImSetTrigger": 0x10004de0,
        "ImSetParam": 0x10004d10, "ImStartStream": 0x10004e80, "FdIntHandler": 0x10003cb0, "ImStopSound": 0x10004cd0}
NARGS = {"ImSwitchStream": 5, "ImSetHook": 2, "ImFadeParam": 4, "ImSetTrigger": 13, "ImSetParam": 3, "ImStartStream": 3}
rng = [0, 0]
cnt = {"frames": 0, "hb": 0}
t0 = [None]


def words(a, n):
    return struct.unpack("<%dI" % n, bytes(gdb.selected_inferior().read_memory(a, 4 * n)))


def reg(r):
    return int(gdb.parse_and_eval("$" + r)) & 0xffffffff


def stamp():
    if t0[0] is None:
        t0[0] = time.time()
    return "t=%.3f frame=%d hb=%d" % (time.time() - t0[0], cnt["frames"], cnt["hb"])


class Ent(gdb.Breakpoint):
    def __init__(self, spec, name):
        super().__init__(spec, internal=True)
        self.name = name

    def stop(self):
        if self.name == "FdIntHandler":
            cnt["hb"] += 1
            return False
        if self.name == "frame":
            cnt["frames"] += 1
            return False
        esp = reg("esp")
        if self.name == "ImStopSound":
            v = words(esp, 2)
            fo.write("  ImStopSound(%x) %s\n" % (v[1], stamp()))
        elif self.name == "Script_Trans":
            pass
        elif self.name in ("FUN_10006560", "Script_SetSequence"):
            v = words(esp, 2)
            fo.write("%s(%d) %s\n" % (self.name, v[1], stamp()))
        else:
            v = words(esp, 1 + NARGS[self.name])
            if rng[0] <= v[0] < rng[1]:
                fo.write("  %s(%s)\n" % (self.name, ", ".join("%x" % x for x in v[1:])))
        fo.flush()
        return False


done = [False]


def on_obj(ev):
    fn = ev.new_objfile.filename.lower()
    if done[0] or not fn.endswith("imuse.dll"):
        return
    done[0] = True
    if MODE == "orig":
        base = None
        for line in gdb.execute("info sharedlibrary", to_string=True).splitlines():
            if "imuse.dll" in line.lower():
                base = int(line.split()[0], 16) - 0x1000
        fo.write("BASE %x\n" % base)
        for n, a in ORIG.items():
            Ent("*0x%x" % (a - 0x10000000 + base), n)
        rng[0] = 0x100068b0 - 0x10000000 + base
        rng[1] = 0x100070a0 - 0x10000000 + base
    else:
        for n in ORIG:
            Ent("*" + n, n)
        rng[0] = int(gdb.parse_and_eval("(unsigned)&Script_Trans"))
        rng[1] = rng[0] + int(os.environ.get("FT_LEN", "7f0"), 16)
        fo.write("BASE sym %x\n" % rng[0])
    fo.flush()


Ent("GRIM_lua_cmd_poll", "frame")   # the rebuilt EXE (loaded before this script runs)
gdb.events.new_objfile.connect(on_obj)
