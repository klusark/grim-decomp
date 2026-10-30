import gdb, struct, os
fo = open(os.environ.get("RT_OUT", "C:/Users/Joel/grimN_work/rt.txt"), "w")
SYM = os.environ.get("RT_SYM", "iMUSE_GetPhoneme")
NA = int(os.environ.get("RT_ARGS", "2"))
def u32(a): return struct.unpack("<I", bytes(gdb.selected_inferior().read_memory(a, 4)))[0]
class Ret(gdb.Breakpoint):
    def __init__(self, ra, args):
        super().__init__("*0x%x" % ra, internal=True, temporary=True); self.args = args
    def stop(self):
        eax = int(gdb.parse_and_eval("$eax")) & 0xffffffff
        fo.write("%s -> %x\n" % (" ".join("%x" % a for a in self.args), eax)); fo.flush()
        return False
class Ent(gdb.Breakpoint):
    def stop(self):
        esp = int(gdb.parse_and_eval("$esp")) & 0xffffffff
        v = struct.unpack("<%dI" % (NA + 1), bytes(gdb.selected_inferior().read_memory(esp, 4 * (NA + 1))))
        Ret(v[0], list(v[1:]))
        return False
def on_obj(ev):
    if ev.new_objfile.filename.lower().endswith("imuse.dll"):
        Ent("*" + SYM)
gdb.events.new_objfile.connect(on_obj)
