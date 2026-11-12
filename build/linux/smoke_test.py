"""Smoke test of the native Linux build without the game's data (CI runs it after `make -C build linux`).

Builds a tiny synthetic data directory (a text _system.lua with BOOT, a 640x480 splash.bm, a registry file with
TextAllowed) and runs obj-linux/grimfandango headless (SDL dummy video and audio). Checks that

  * the splash bitmap reaches the screen pixel for pixel (bitmap loader, colour correction, 16 bpp back buffer,
    fastpaths.c's conversion, the GDI BitBlt emulation),
  * _system.lua runs and BOOT is called (Lua, file and path handling, registry),
  * the frame loop runs (the GRIM_LUA_FILE test hook executes a line per frame) and exit() ends the process.

usage: python3 -I build/linux/smoke_test.py [path/to/grimfandango]"""
import os
import struct
import subprocess
import sys
import tempfile
import time

HERE = os.path.dirname(os.path.abspath(__file__))
EXE = sys.argv[1] if len(sys.argv) > 1 else os.path.join(os.path.dirname(HERE), "obj-linux", "grimfandango")
W, H = 640, 480
KEY = "80000002\\software\\lucasarts entertainment company llc\\grim fandango\\v1.0"


def splash_pixel(x, y):
    """RGB565 test pattern: red across, green down, blue checkerboard"""
    r, g, b = x * 31 // (W - 1), y * 63 // (H - 1), 31 if (x // 64 + y // 64) % 2 else 0
    return r, g, b


def write_splash(path):
    hdr = bytearray(128)
    hdr[0:8] = b"BM  F\0\0\0"
    struct.pack_into("<8I", hdr, 8, 0, 0, 1, 0, 0, 0, 1, 16)   # codec 0, 1 image, format 1, 16 bpp
    struct.pack_into("<2I", hdr, 52, W, H)
    px = bytearray()
    for y in range(H):
        for x in range(W):
            r, g, b = splash_pixel(x, y)
            px += struct.pack("<H", r << 11 | g << 5 | b)
    with open(path, "wb") as f:
        f.write(bytes(hdr) + struct.pack("<2I", W, H) + bytes(px))


def read_bmp(path):
    d = open(path, "rb").read()
    off, w, h, bpp = struct.unpack_from("<I", d, 10)[0], *struct.unpack_from("<iiHH", d, 18)[:2], \
        struct.unpack_from("<H", d, 28)[0]
    assert bpp == 32 and h < 0, "unexpected BMP format"
    return w, -h, lambda x, y: struct.unpack_from("<BBB", d, off + (y * w + x) * 4)[::-1]


def main():
    if not os.path.exists(EXE):
        print("smoke_test: %s not found (make -C build linux)" % EXE)
        return 1
    t = tempfile.mkdtemp(prefix="grim_smoke_")
    write_splash(os.path.join(t, "splash.bm"))
    with open(os.path.join(t, "_system.lua"), "w") as f:
        f.write('function BOOT(resumed, arg)\n  booted = 1\nend\n')
    with open(os.path.join(t, "registry.txt"), "w") as f:
        f.write("%s\tTextAllowed\t1\t%s\n" % (KEY, b"true\0".hex()))
    cmd, log, shot = (os.path.join(t, n) for n in ("cmd.lua", "log.txt", "shot.bmp"))
    open(cmd, "w").close()
    env = dict(os.environ, SDL_VIDEODRIVER="dummy", SDL_AUDIODRIVER="dummy", GRIM_REGISTRY=os.path.join(t, "registry.txt"),
               GRIM_NODIALOGS="1", GRIM_LUA_FILE=cmd, GRIM_LUA_LOG=log, GRIM_SHOT=shot, GRIM_SHOT_FRAMES="3")
    p = subprocess.Popen([EXE], cwd=t, env=env, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
    failures = []
    try:
        deadline = time.time() + 30
        while time.time() < deadline and "lua hook active" not in (open(log).read() if os.path.exists(log) else ""):
            if p.poll() is not None:
                break
            time.sleep(0.2)
        with open(cmd, "a") as f:
            f.write('grimlog("booted="..tostring(booted))\n')
        time.sleep(1)
        with open(cmd, "a") as f:
            f.write("exit()\n")
        try:
            out = p.communicate(timeout=15)[0]
        except subprocess.TimeoutExpired:
            p.kill()
            out = p.communicate()[0]
            failures.append("exit() did not end the process")
    finally:
        if p.poll() is None:
            p.kill()
    text = open(log).read() if os.path.exists(log) else ""
    if "booted=1" not in text:
        failures.append("BOOT was not run (log: %r)" % text[-300:])
    frame = shot + ".1.bmp"   # frame 0: the cleared screen; frame 1: the splash
    if not os.path.exists(frame):
        failures.append("no frame was presented")
    else:
        w, h, px = read_bmp(frame)
        for x, y in [(0, 0), (5, 5), (100, 10), (600, 400), (639, 479), (320, 240)]:
            r, g, b = splash_pixel(x, y)
            want = (r << 3 | r >> 2, g << 2 | g >> 4, b << 3 | b >> 2)
            if px(x, y) != want:
                failures.append("splash pixel (%d,%d) is %s, expected %s" % (x, y, px(x, y), want))
    print(out.strip())
    if failures:
        print("smoke_test: FAILED\n  " + "\n  ".join(failures))
        print("  (files in %s)" % t)
        return 1
    print("smoke_test: OK (Lua boot, frame loop, splash on screen, exit)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
