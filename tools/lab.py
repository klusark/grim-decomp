"""List / extract / pack LucasArts LABN archives (the DATA*.LAB, VOX*.LAB, ... files of Grim Fandango).

Format: "LABN", u32 version (0x10000), u32 file count, u32 name-table size, then count entries
{u32 name offset, u32 data offset, u32 size, u32 0}, then the NUL-separated name table; file data follows.

  python -I tools/lab.py list DATA000.LAB [substring]
  python -I tools/lab.py extract DATA000.LAB name [outdir]       (name = exact file name, case-insensitive; `*` = all)
  python -I tools/lab.py pack out.lab file1 file2 ...            (new archive from loose files)
"""
import os, struct, sys


def read_lab(path):
    d = open(path, "rb").read()
    if d[:4] != b"LABN":
        raise SystemExit(f"{path}: not a LABN archive")
    ver, n, nlen = struct.unpack_from("<III", d, 4)
    names_at = 16 + 16 * n
    names = d[names_at:names_at + nlen]
    out = []
    for i in range(n):
        no, off, size, _ = struct.unpack_from("<IIII", d, 16 + 16 * i)
        name = names[no:names.index(b"\0", no)].decode("latin-1")
        out.append((name, off, size))
    return d, out


def pack(path, files):
    names = b"".join(os.path.basename(f).encode("latin-1") + b"\0" for f in files)
    hdr = 16 + 16 * len(files) + len(names)
    entries, blob, no, off = b"", b"", 0, hdr
    for f in files:
        data = open(f, "rb").read()
        entries += struct.pack("<IIII", no, off, len(data), 0)
        no += len(os.path.basename(f)) + 1
        off += len(data)
        blob += data
    open(path, "wb").write(b"LABN" + struct.pack("<III", 0x10000, len(files), len(names)) + entries + names + blob)


if __name__ == "__main__":
    cmd = sys.argv[1]
    if cmd == "pack":
        pack(sys.argv[2], sys.argv[3:])
    else:
        d, ents = read_lab(sys.argv[2])
        if cmd == "list":
            sub = sys.argv[3].lower() if len(sys.argv) > 3 else ""
            for name, off, size in ents:
                if sub in name.lower():
                    print(f"{size:9d}  {name}")
        elif cmd == "extract":
            want, outdir = sys.argv[3].lower(), (sys.argv[4] if len(sys.argv) > 4 else ".")
            os.makedirs(outdir, exist_ok=True)
            for name, off, size in ents:
                if want == "*" or name.lower() == want:
                    open(os.path.join(outdir, name), "wb").write(d[off:off + size])
                    print("extracted", name, size)
