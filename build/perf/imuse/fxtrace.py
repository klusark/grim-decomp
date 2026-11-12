# gdb script: CRC of the input and the output of every Im_ApplyFXPreset call (IMUSE.DLL's voice effect step).
# FX_OUT (in gdb's own environment) names the output file: one line per call, `n ret <caller> in <bytes> <crc> ch <channels>
# last <flag> out <bytes> <crc>`. The return-address check assumes the rebuilt imuse.dll at its link base 0x6b340000.
# Used with scn_fx.lua to compare build/overrides_hmifx.c with the real HMIFXLIB.DLL (build/BUILD_NOTES.md, 2026-11-12).
import gdb, struct, zlib, os
OUT = os.environ["FX_OUT"]
fo = open(OUT, "w")
n = [0]


def u32(inf, a):
    return struct.unpack("<I", bytes(inf.read_memory(a, 4)))[0]


class Ret(gdb.Breakpoint):
    def __init__(self, addr, args):
        super().__init__("*0x%x" % addr, internal=True, temporary=True)
        self.args = args
        self.ret = addr

    def stop(self):
        try:
            inf = gdb.selected_inferior()
            src, nbytes, out, pout, psize, last = self.args
            eax = int(gdb.parse_and_eval("$eax")) & 0xffffffff
            if last:
                out = u32(inf, pout) if pout else 0
                size = u32(inf, psize) if psize else 0
            else:
                size = nbytes * eax
            data = bytes(inf.read_memory(out, size)) if out and size else b""
            ind = bytes(inf.read_memory(src, nbytes)) if src and nbytes else b""
            fo.write("%d ret %08x in %d %08x ch %d last %d out %d %08x\n" % (n[0], self.ret, nbytes, zlib.crc32(ind), eax,
                                                                           last, size, zlib.crc32(data)))
            fo.flush()
            n[0] += 1
        except Exception as e:
            fo.write("ERR %s\n" % e)
            fo.flush()
        return False


class Entry(gdb.Breakpoint):
    def stop(self):
        try:
            inf = gdb.selected_inferior()
            # (gdb stops after the prologue `push ebp; mov ebp, esp; sub esp, ...`: the frame is at ebp)
            bp = int(gdb.parse_and_eval("$ebp")) & 0xffffffff
            ret = u32(inf, bp + 4)
            args = tuple(u32(inf, bp + 8 + 4 * i) for i in range(6))
            if not (0x6b340000 <= ret < 0x6b400000):
                fo.write("ERR return address %08x\n" % ret)
                fo.flush()
                return False
            Ret(ret, args)
        except Exception as e:
            fo.write("ERR entry %s\n" % e)
            fo.flush()
        return False


Entry("Im_ApplyFXPreset")
