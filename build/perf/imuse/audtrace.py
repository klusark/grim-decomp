# gdb script: CRC + peak of every block Im_DSoundHeartbeat is about to commit to DirectSound (final PCM), in both the assembled and the C build
import gdb, struct, zlib, os
OUT = os.environ.get("AUD_OUT", "C:/Users/Joel/grimN_work/aud.txt")
fo = open(OUT, "w")
LIMIT = int(os.environ.get("AUD_LIMIT", "0"))
n = [0]
A = {}
def rd(inf, name):
    if name not in A:
        A[name] = int(gdb.parse_and_eval("&" + name)) & 0xffffffff
    return struct.unpack("<I", bytes(inf.read_memory(A[name], 4)))[0]
class HB(gdb.Breakpoint):
    def stop(self):
        try:
            inf = gdb.selected_inferior()
            if rd(inf, "DAT_1002d848") == 1 and rd(inf, "DAT_1002d84c") == 1:
                p1 = rd(inf, "DAT_1002d850"); l1 = rd(inf, "DAT_1002d82c"); p2 = rd(inf, "DAT_1002d854"); l2 = rd(inf, "DAT_1002d820")
                if p2 and l2:
                    data = bytes(inf.read_memory(rd(inf, "DAT_1002d818"), 0x1800))
                else:
                    data = bytes(inf.read_memory(p1, l1))
                s = struct.unpack("<%dh" % (len(data) // 2), data[:len(data) // 2 * 2])
                fo.write("%d %d %08x %d\n" % (n[0], len(data), zlib.crc32(data), max(abs(x) for x in s) if s else 0)); n[0] += 1
                fo.flush()
                if LIMIT and n[0] >= LIMIT:
                    fo.flush(); return True
        except Exception as e:
            fo.write("ERR %s\n" % e)
        return False
HB("Im_DSoundHeartbeat")
