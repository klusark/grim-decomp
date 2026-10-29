"""Dump a Grim Fandango precompiled Lua 3.1 chunk (.LUA inside the LAB archives).

Format (from LUA.DLL's lundump.c): ESC "Lua" version, sizeof(real), test number, then a function:
  line (BE word), source (word length + bytes, bit-inverted), code size (two BE words) + code,
  constants (count word; each 'F' | 'N' + float | 'S' + string), locals (count word; each line word +
  string), then any number of '#' + constant slot (word) + function, and a terminating byte.

Usage: python -I luadump.py <file.LUA | LAB:name> [LABFILE]    (prints functions, constants, code hex)
       python -I luadump.py --lab DATA000.LAB name.LUA
"""
import struct, sys


class R:
    def __init__(self, d, p=0):
        self.d, self.p = d, p

    def byte(self):
        b = self.d[self.p]; self.p += 1; return b

    def word(self):
        h = self.byte(); l = self.byte(); return h << 8 | l

    def long(self):
        h = self.word(); l = self.word(); return h << 16 | l

    def block(self, n):
        b = self.d[self.p:self.p + n]; self.p += n; return b

    def string(self):
        n = self.word()
        if n == 0: return None
        return bytes(255 - x for x in self.block(n)).rstrip(b"\0").decode("latin-1")


def func(r, depth=0):
    f = {"line": r.word(), "source": r.string()}
    size = r.long()
    f["code"] = r.block(size)
    f["consts"] = []
    for _ in range(r.word()):
        t = chr(r.byte())
        if t == "N":
            f["consts"].append(("N", struct.unpack("<f", r.block(4))[0]))
        elif t == "S":
            f["consts"].append(("S", r.string()))
        else:
            f["consts"].append((t, None))
    f["locals"] = [(r.word(), r.string()) for _ in range(r.word())]
    f["funcs"] = []
    while True:
        b = r.byte()
        if b != 0x23:
            break
        slot = r.word()
        f["funcs"].append((slot, func(r, depth + 1)))
    return f


def load(data):
    r = R(data)
    assert data[:4] == b"\x1bLua", "not a Lua chunk"
    r.p = 4
    r.byte()            # version
    sizeof_real = r.byte()
    r.block(4 if sizeof_real == 4 else 8)  # test number
    return func(r)


def show(f, depth=0, out=sys.stdout, offset=0):
    pad = "  " * depth
    out.write("%sfunction %s:%d  code=%d bytes\n" % (pad, f["source"], f["line"], len(f["code"])))
    for i, (t, v) in enumerate(f["consts"]):
        out.write("%s  K%d %s %r\n" % (pad, i, t, v))
    if f["locals"]:
        out.write("%s  locals: %s\n" % (pad, ", ".join("%s@%d" % (n, l) for l, n in f["locals"])))
    out.write("%s  code: %s\n" % (pad, f["code"].hex()))
    for slot, sub in f["funcs"]:
        out.write("%s  -- K%d is:\n" % (pad, slot))
        show(sub, depth + 2, out)


def lab_entry(labfile, name):
    d = open(labfile, "rb").read()
    n, sl = struct.unpack("<II", d[8:16])
    names = d[16 + 16 * n:16 + 16 * n + sl]
    for i in range(n):
        no, st, sz, _ = struct.unpack("<IIII", d[16 + 16 * i:32 + 16 * i])
        if names[no:names.index(b"\0", no)].decode().lower() == name.lower():
            return d[st:st + sz]
    raise SystemExit("not in archive: " + name)


if __name__ == "__main__":
    a = sys.argv[1:]
    if a and a[0] == "--lab":
        data = lab_entry(a[1], a[2])
    else:
        data = open(a[0], "rb").read()
    show(load(data))
