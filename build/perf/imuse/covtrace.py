import gdb, os, json
NAMES = json.load(open("C:/Users/Joel/grimN_work/covnames.json"))
OUT = os.environ.get("COV_OUT", "C:/Users/Joel/grimN_work/cov.txt")
seen = set()
fo = open(OUT, "w")
class B(gdb.Breakpoint):
    def __init__(self, nm):
        super().__init__("*" + nm, internal=True); self.nm = nm
    def stop(self):
        if self.nm not in seen:
            seen.add(self.nm); fo.write(self.nm + "\n"); fo.flush()
            self.enabled = False
        return False
def on_obj(ev):
    if ev.new_objfile.filename.lower().endswith("imuse.dll"):
        for n in NAMES:
            try: B(n)
            except Exception as e: fo.write("ERR %s %s\n" % (n, e))
gdb.events.new_objfile.connect(on_obj)
