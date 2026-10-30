r"""Reader for the save-game stream trace of the rebuilt engine (GRIM_SAVETRACE=<file>, build/overrides.c).

With the environment variable set, every SaveGame_Write / SaveGame_Read call (the single choke point all modules'
SaveState / RestoreState callbacks go through) appends a 16 byte record to the file:
    u32 stream offset (bytes already written / read through the callbacks; the two gzseek'd blocks of a load, the header
        table and the thumbnail, are not counted), u32 size (bit 31 = write), u32 return address, u32 first dword.
This tool symbolises the return addresses (nm -n of the rebuilt binaries in build/obj) and prints the stream as runs of
consecutive calls from the same function: that is the layout of a save (which module wrote which bytes).

usage: python -I tools/savetrace.py trace.bin [--runs N] [--skip-lua] [--range LO HI]
  --runs N        print the first N runs (default 80, 0 = all)
  --skip-lua      leave out the (very long) Lua state part
  --range LO HI   list the 4 byte records whose value lies in [LO, HI) (hex), with the calling function: finds raw
                  machine addresses in a save, e.g.  --range 401000 930000  for the EXE image
Typical use:  set GRIM_SAVETRACE=C:\x\load.bin, `Load("grimNN.gsv")` in the game (or Save), then run this tool."""
import os, struct, subprocess, sys, bisect

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OBJ = os.path.join(ROOT, 'build', 'obj')
MODS = {'exe': 'GRIMFANDANGO.EXE/grimfandango.exe', 'lua': 'LUA.DLL/lua.dll', 'imuse': 'IMUSE.DLL/imuse.dll',
        'chore': 'CHORE.DLL/chore.dll'}


def image(path):
    d = open(path, 'rb').read(0x400)
    pe = struct.unpack_from('<I', d, 0x3c)[0]
    return struct.unpack_from('<I', d, pe + 0x34)[0], struct.unpack_from('<I', d, pe + 0x50)[0]   # ImageBase, SizeOfImage


tabs = {}
for k, rel in MODS.items():
    p = os.path.join(OBJ, rel)
    if not os.path.exists(p):
        continue
    base, size = image(p)
    out = subprocess.run(['nm', '-n', p], capture_output=True, text=True).stdout
    syms = []
    for line in out.splitlines():
        f = line.split()
        if len(f) == 3 and f[1] in 'TtDdBbRr':
            syms.append((int(f[0], 16), f[2]))
    tabs[k] = (base, size, [a for a, _ in syms], [n for _, n in syms])


def sym(addr):
    for k, (base, size, addrs, names) in tabs.items():
        if base <= addr < base + size:
            i = bisect.bisect_right(addrs, addr) - 1
            return '%s:%s' % (k, names[i].lstrip('_')) if i >= 0 else k
    return '%08x' % addr


def main():
    args = sys.argv[1:]
    if not args:
        print(__doc__); return
    data = open(args[0], 'rb').read()
    recs = [struct.unpack_from('<IIII', data, i) for i in range(0, len(data) - 15, 16)]
    nruns, skip_lua, rng = 80, False, None
    i = 1
    while i < len(args):
        if args[i] == '--runs': nruns = int(args[i + 1]); i += 2
        elif args[i] == '--skip-lua': skip_lua = True; i += 1
        elif args[i] == '--range': rng = (int(args[i + 1], 16), int(args[i + 2], 16)); i += 3
        else: raise SystemExit('unknown argument ' + args[i])
    if rng:
        for off, n, ret, val in recs:
            if n & 0x7fffffff == 4 and rng[0] <= val < rng[1]:
                print('offset %9d  value %08x  %s' % (off, val, sym(ret)))
        return
    runs = []
    for off, n, ret, val in recs:
        f = sym(ret)
        if skip_lua and f.startswith('lua:'):
            continue
        if runs and runs[-1][2] == f:
            runs[-1][1] += n & 0x7fffffff; runs[-1][3] += 1
        else:
            runs.append([off, n & 0x7fffffff, f, 1])
    for r in (runs if nruns == 0 else runs[:nruns]):
        print('offset %9d  %8d bytes  %7d calls  %s' % (r[0], r[1], r[3], r[2]))
    print('%d records, %d runs, %d bytes' % (len(recs), len(runs), recs[-1][0] + (recs[-1][1] & 0x7fffffff) if recs else 0))


main()
