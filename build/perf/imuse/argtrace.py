import gdb, struct, os
fo = open(os.environ.get("AT_OUT", "C:/Users/Joel/grimN_work/at.txt"), "w")
SYM = os.environ.get("AT_SYM", "FUN_100068b0")
NW = int(os.environ.get("AT_WORDS", "16"))
class Ent(gdb.Breakpoint):
    def stop(self):
        esp = int(gdb.parse_and_eval("$esp")) & 0xffffffff
        v = struct.unpack("<%dI" % NW, bytes(gdb.selected_inferior().read_memory(esp, 4 * NW)))
        fo.write("%s %s\n" % (SYM, " ".join("%x" % x for x in v))); fo.flush()
        return False
def on_obj(ev):
    if ev.new_objfile.filename.lower().endswith("imuse.dll"):
        Ent("*" + SYM)
gdb.events.new_objfile.connect(on_obj)
