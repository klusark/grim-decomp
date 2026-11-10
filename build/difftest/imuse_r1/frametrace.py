# gdb script (agent r1): the stack words at the entry of Script_Trans (and of its two callers) and the arguments of the
# iMUSE calls Script_Trans makes (only calls whose return address lies inside Script_Trans are logged).
#   FT_MODE=orig  the original IMUSE.DLL (no symbols: addresses from its preferred base 0x10000000, moved by the load base)
#   FT_MODE=sym   a rebuilt imuse.dll with symbols; FT_LEN = length of Script_Trans's code (hex)
#   FT_OUT        output file
import gdb, struct, os

fo = open(os.environ.get("FT_OUT", "ft.txt"), "w")
MODE = os.environ.get("FT_MODE", "sym")
ORIG = {"Script_Trans": 0x100068b0, "FUN_10006560": 0x10006560, "Script_SetSequence": 0x10006620,
        "ImSwitchStream": 0x10004ec0, "ImSetHook": 0x10004db0, "ImFadeParam": 0x10004d90, "ImSetTrigger": 0x10004de0,
        "ImSetParam": 0x10004d10, "ImStartStream": 0x10004e80}
NARGS = {"ImSwitchStream": 5, "ImSetHook": 2, "ImFadeParam": 4, "ImSetTrigger": 13, "ImSetParam": 3, "ImStartStream": 3}
rng = [0, 0]


def words(a, n):
    return struct.unpack("<%dI" % n, bytes(gdb.selected_inferior().read_memory(a, 4 * n)))


def reg(r):
    return int(gdb.parse_and_eval("$" + r)) & 0xffffffff


class Ent(gdb.Breakpoint):
    def __init__(self, spec, name):
        super().__init__(spec, internal=True)
        self.name = name

    def stop(self):
        esp = reg("esp")
        if self.name == "Script_Trans":
            v = words(esp, 12)
            fo.write("ENTRY %s | esi=%x edi=%x ebx=%x ebp=%x\n" % (" ".join("%x" % x for x in v), reg("esi"), reg("edi"),
                                                                  reg("ebx"), reg("ebp")))
        elif self.name in ("FUN_10006560", "Script_SetSequence"):
            v = words(esp, 2)
            fo.write("%s ret=%x arg=%x esi=%x edi=%x\n" % (self.name, v[0], v[1], reg("esi"), reg("edi")))
        else:
            v = words(esp, 1 + NARGS[self.name])
            if rng[0] <= v[0] < rng[1]:
                fo.write("  %s(%s) from +%x\n" % (self.name, ", ".join("%x" % x for x in v[1:]), v[0] - rng[0]))
        fo.flush()
        return False


done = [False]


def on_obj(ev):
    if done[0] or not ev.new_objfile.filename.lower().endswith("imuse.dll"):
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


gdb.events.new_objfile.connect(on_obj)
