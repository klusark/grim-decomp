"""Movie sound differential test (docs/notes/s3.md): decode the Wave (VIMA) audio of real SNM movies with the Smush Wave codec
(FUN_004cbc00 -> FUN_004cbf50) of the original GRIMFANDANGO.EXE and of rebuilt exes, compare the PCM.

usage: python -I moviesound.py <vimadiff.exe> <workdir> <movie.snm>... -- <name>=<rebuilt grimfandango.exe>...
  The movies are gzip'ed SNM files (tools/lab.py extract MOVIE0x.LAB <name>).  For every movie and image: the Wave chunks are
  run through vimadiff.exe (built from vimadiff.c, see there), the buffers the codec hands to the SOUND service are split
  into header and 16 bit PCM, and every rebuilt image is compared with the original: chunks / samples that differ, the
  largest difference, the RMS of the difference against the RMS of the signal (dB), the first differing chunk.
"""
import gzip
import math
import os
import struct
import subprocess
import sys

ORIG = "C:/GOG Games/GRIMDATA/GRIMFANDANGO.exe"
ORIG_ADDRS = ("4cbc00", "8da4ec", "8da4f0", "8d7860")
NM = "C:/msys64/mingw32/bin/nm.exe"
SYMS = ("_FUN_004cbc00", "_UINT_008da4ec", "_PTR_008da4f0", "_UINT_008d7860")


def addrs_of(image):
    syms = {}
    for line in subprocess.run([NM, image], capture_output=True, text=True).stdout.splitlines():
        p = line.split()
        if len(p) == 3:
            syms[p[2]] = p[0]
    return tuple(syms[s] for s in SYMS)


def waves_of(movie, out):
    """write the Wave chunks of a movie; return (count, FLHD Wave sample total)"""
    d = gzip.open(movie).read()
    assert d[:4] == b"SANM"
    pos, waves, total = 8, [], 0
    while pos + 8 <= len(d):
        tag, size = d[pos:pos + 4], struct.unpack(">I", d[pos + 4:pos + 8])[0]
        body = d[pos + 8:pos + 8 + size]
        if tag == b"FLHD":
            i = 0
            while i + 8 <= len(body):
                t2, s2 = body[i:i + 4], struct.unpack(">I", body[i + 4:i + 8])[0]
                if t2 == b"Wave":
                    total = struct.unpack_from("<I", body, i + 8 + 8)[0] if s2 >= 12 else 0
                i += 8 + s2
        if tag == b"FRME":
            i = 0
            while i + 8 <= len(body):
                t2, s2 = body[i:i + 4], struct.unpack(">I", body[i + 4:i + 8])[0]
                if t2 == b"Wave":
                    waves.append(body[i + 8:i + 8 + s2])
                i += 8 + s2 + (s2 & 1)
        pos += 8 + size + (size & 1)
    with open(out, "wb") as w:
        w.write(struct.pack("<I", len(waves)))
        for b in waves:
            w.write(struct.pack("<I", len(b)) + b)
    return len(waves), total


def records(path):
    """[(header bytes, pcm samples, return value)] per chunk"""
    d = open(path, "rb").read()
    out, pos, cur = [], 0, None
    while pos < len(d):
        tag = d[pos:pos + 4]
        if tag == b"CALL":
            n = struct.unpack_from("<I", d, pos + 4)[0]
            cur = d[pos + 8:pos + 8 + n]
            pos += 8 + n
        else:
            r = struct.unpack_from("<I", d, pos + 4)[0]
            pos += 8
            if cur is None:
                out.append((b"", (), r))
            else:
                hl = 0x36 if cur[10:12] == b"\0\0" else 0x12  # chunk counter 0 (first chunk of a stream): long header
                pcm = struct.unpack("<%dh" % ((len(cur) - hl) // 2), cur[hl:hl + (len(cur) - hl) // 2 * 2])
                out.append((cur[:hl], pcm, r))
            cur = None
    return out


def run(vima, image, addrs, total, waves, out):
    r = subprocess.run([vima, image, *addrs, str(total), waves, out], capture_output=True, text=True)
    if r.returncode:
        sys.exit("%s failed on %s: %s %s" % (vima, image, r.stdout, r.stderr))


def main():
    a = sys.argv[1:]
    vima, work = a[0], a[1]
    sep = a.index("--")
    movies, images = a[2:sep], [x.split("=", 1) for x in a[sep + 1:]]
    os.makedirs(work, exist_ok=True)
    for movie in movies:
        name = os.path.splitext(os.path.basename(movie))[0]
        wv = os.path.join(work, name + ".waves")
        n, total = waves_of(movie, wv)
        if not n:
            print("%-10s no Wave chunks" % name)
            continue
        ref_path = os.path.join(work, name + ".orig.bin")
        run(vima, ORIG, ORIG_ADDRS, total, wv, ref_path)
        ref = records(ref_path)
        nsamp = sum(len(p) for _, p, _ in ref)
        sig = math.sqrt(sum(x * x for _, p, _ in ref for x in p) / max(nsamp, 1))
        clip0 = sum(1 for _, p, _ in ref for x in p if x in (32767, -32768))
        print("%-10s %4d chunks (%.1f s of frames at 15 fps), %8d samples (16 bit), signal RMS %.1f, clipped samples %d"
              % (name, n, n / 15.0, nsamp, sig, clip0))
        for label, image in images:
            p = os.path.join(work, "%s.%s.bin" % (name, label))
            run(vima, image, addrs_of(image), total, wv, p)
            got = records(p)
            dch = dsm = hdr = ret = 0
            maxd, sq, first = 0, 0.0, None
            for k, ((h0, p0, r0), (h1, p1, r1)) in enumerate(zip(ref, got)):
                hdr += h0 != h1
                ret += r0 != r1
                if p0 != p1:
                    dch += 1
                    if first is None:
                        first = k
                    for x, y in zip(p0, p1):
                        if x != y:
                            dsm += 1
                            maxd = max(maxd, abs(x - y))
                            sq += (x - y) ** 2
                    if len(p0) != len(p1):
                        dsm += abs(len(p0) - len(p1))
            if len(got) != len(ref):
                print("   %-8s chunk count %d vs %d" % (label, len(got), len(ref)))
            if not (dch or hdr or ret):
                print("   %-8s identical (headers, PCM, return values)" % label)
            else:
                rms = math.sqrt(sq / max(nsamp, 1))
                db = 20 * math.log10(rms / sig) if rms and sig else float("-inf")
                clip = sum(1 for _, p, _ in got for x in p if x in (32767, -32768))
                print("   %-8s %d chunks (%.1f s) / %d samples (%.2f%%) differ, max |diff| %d, diff RMS %.1f (%+.1f dB vs signal), "
                      "clipped samples %d, first chunk %s; headers differ %d, return values %d"
                      % (label, dch, dch / 15.0, dsm, 100.0 * dsm / max(nsamp, 1), maxd, rms, db, clip, first, hdr, ret))


main()
