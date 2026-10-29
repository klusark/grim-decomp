set pagination off
set environment _NO_DEBUG_HEAP=1
break Lua_MakeCurrentSet
run
python
import gdb
inf = gdb.selected_inferior()
rd = open('C:/Users/Joel/AppData/Local/Claude-Data/claude_pzs8sxrjxfjjc/scratch-workspaces/f0972061-5c14-4333-a255-b15c37c97747/dcb1fc9c-532e-4a3c-9dfb-8af95607d192/scratch-2026-10-28-bb481e/grim-decomp/raw/GRIMFANDANGO.EXE/sections/rdata.bin','rb').read()
dt = open('C:/Users/Joel/AppData/Local/Claude-Data/claude_pzs8sxrjxfjjc/scratch-workspaces/f0972061-5c14-4333-a255-b15c37c97747/dcb1fc9c-532e-4a3c-9dfb-8af95607d192/scratch-2026-10-28-bb481e/grim-decomp/raw/GRIMFANDANGO.EXE/sections/data.bin','rb').read()
base_r = int(gdb.parse_and_eval('(unsigned)&DAT_004d7600')) - 0x600
base_d = int(gdb.parse_and_eval('(unsigned)&DAT_004df600')) - 0x2600
print('>> bases', hex(base_r), hex(base_d), hex(base_d - base_r))
rr = inf.read_memory(base_r, len(rd)).tobytes()
dd = inf.read_memory(base_d, 0x20000).tobytes()
def diffs(a, b, name, org):
    bad = [i for i in range(0, min(len(a), len(b)) - 3, 4) if a[i:i+4] != b[i:i+4]]
    print('>>', name, 'differing dwords', len(bad), [hex(org + i) for i in bad[:12]])
bad = [0x4d7000 + i for i in range(0, len(rd) - 3, 4) if rr[i:i+4] != rd[i:i+4]]
print('>> rdata bad in tables', [hex(x) for x in bad if 0x4d7600 <= x < 0x4db600][:10], len([x for x in bad if 0x4d7600 <= x < 0x4db600]))
bad = [0x4dd000 + i for i in range(0, 0x20000, 4) if dd[i:i+4] != dt[i:i+4]]
print('>> data bad in tables', len([x for x in bad if 0x4df600 <= x < 0x4e7600]), [hex(x) for x in bad if 0x4df600 <= x < 0x4e7600][:10])
diffs(dd, dt[:0x20000], 'data', 0x4dd000)
end
kill
