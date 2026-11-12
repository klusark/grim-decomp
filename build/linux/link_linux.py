"""Link the native Linux (i386 ELF) build: `make -C build linux`.

The four PE programs become one ELF executable, obj-linux/grimfandango:

  1. every program is linked like build/link.py links it for Windows (its modules, data.c, link_data.c, the
     overrides_*.c files, cleanroom/, fastpaths.c, lib_alias), but into one relocatable object with `ld -r`;
  2. in that object every global symbol except the program's exports (src/<DLL>/exports.json) is made local,
     so the programs keep the separate namespaces they have as DLLs (each has its own `chore.c`, `data.c`, ...),
     and every symbol gets the prefix `G`;
  3. the four objects are linked with the platform layer (build/linux/platform/*.c: Win32, DirectX and the MSVC
     runtime on SDL2 and libc) into one executable.

Names: the game is compiled with -fleading-underscore so that the COFF-style symbol names the tree uses in asm
labels (`_FUN_004ac690`) work unchanged, and build/linux/cc.sh turns the PE decorations into ELF-safe names
(`_CreateFileA@28` -> `_CreateFileA__at28`, `@f@8` -> `__fc_f__at8`). The `G` prefix keeps the game's names apart
from the system libraries' (the game's `exit` is `_exit`, glibc's `_exit` is another function). The platform layer is
ordinary C that defines the game-side names explicitly (`G_CreateFileA`, `G__stricmp`: EXPORT() in platform.h). The
final link resolves what is still undefined, in order:

  G_X__atN / G__fc_X__atN  -> G_X (gcc does not decorate stdcall/fastcall names on ELF)
  G_X__host                -> G_X (names/lib_replace.json aliases)
  G_X                      -> X of libc/libm/SDL2/zlib (G_exit -> exit, G__exit -> _exit, G_memcpy -> memcpy)
  anything else            -> a trapping stub (ud2), listed in obj-linux/stubs.txt

usage: python3 -I link_linux.py <srcdir> <objdir> <cc-wrapper> <cflags...>"""
import glob
import json
import os
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
BUILD = os.path.dirname(HERE)
ROOT = os.path.dirname(BUILD)
sys.path.insert(0, BUILD)
import link as winlink  # noqa: E402  (data_c, STDCALL_NAMES)

ORDER = ["LUA.DLL", "IMUSE.DLL", "CHORE.DLL", "GRIMFANDANGO.EXE"]
PROG_DEFINE = {"GRIMFANDANGO.EXE": "-DGRIM_EXE", "IMUSE.DLL": "-DGRIM_IMUSE", "CHORE.DLL": "-DGRIM_CHORE",
               "LUA.DLL": "-DGRIM_LUA"}
SYSLIBS = ["-lSDL2", "-lz", "-lm", "-lpthread", "-ldl"]
DECOR = re.compile(r"^(?:__fc_(\w+?)|(_\w+?))__at\d+$")


def run(cmd):
    p = subprocess.run(cmd, capture_output=True, text=True)
    return p.returncode, p.stdout + p.stderr


def must(cmd, what):
    rc, out = run(cmd)
    if rc:
        raise SystemExit("link_linux: %s failed:\n%s\n%s" % (what, " ".join(cmd), out[:4000]))
    return out


def nm(path):
    """({defined global symbols}, {undefined symbols}) of an object."""
    out = must(["nm", "-g", path], "nm " + path)
    defined, undefined = set(), set()
    for line in out.splitlines():
        f = line.split()
        if len(f) == 2 and f[0] == "U":
            undefined.add(f[1])
        elif len(f) == 3:
            defined.add(f[2])
    return defined, undefined


def library_symbols():
    """Dynamic symbols (functions and data) of the system libraries the platform layer links against."""
    names = {}
    for lib in ["libc.so.6", "libm.so.6", "libSDL2-2.0.so.0", "libz.so.1"]:
        path = None
        for d in ["/lib/i386-linux-gnu", "/usr/lib/i386-linux-gnu", "/usr/lib32", "/lib32", "/usr/lib"]:
            if os.path.exists(os.path.join(d, lib)):
                path = os.path.join(d, lib)
                break
        if not path:
            continue
        out = must(["nm", "-D", "--defined-only", path], "nm -D " + lib)
        for line in out.splitlines():
            f = line.split()
            if len(f) == 3:
                names[f[2].split("@")[0]] = f[1]
    return names


def assemble(text, path, out):
    """Assemble `text` (written to `path`) with the PE decorations made ELF names, as cc.sh does for C."""
    text = re.sub(r"\.def [^;]*; *\.scl [^;]*; *\.type [^;]*; *\.endef", "", text)
    text = re.sub(r"@([A-Za-z_]\w*)@(\d+)", r"__fc_\1__at\2", text)
    text = re.sub(r"([A-Za-z_]\w*)@(\d+)", r"\1__at\2", text)
    open(path, "w", newline="\n").write(text)
    must(["gcc", "-m32", "-c", path, "-o", out], "assemble " + os.path.relpath(path, ROOT))


def compile_c(cc, cflags, src, out, extra=()):
    must([cc] + cflags + list(extra) + ["-c", src, "-o", out], "compile " + os.path.relpath(src, ROOT))


def program_object(cc, cflags, src, obj, prog):
    """obj/<prog>/<prog>.r.o: the program as one relocatable object with only its exports global."""
    d = os.path.join(obj, prog)
    mods = [os.path.basename(c)[:-2] for c in sorted(glob.glob(os.path.join(src, prog, "*.c")))]
    objs = [os.path.join(d, m + ".o") for m in mods if m != "crt" and os.path.exists(os.path.join(d, m + ".o"))]
    missing = [m for m in mods if m != "crt" and not os.path.exists(os.path.join(d, m + ".o"))]
    if missing:
        raise SystemExit("link_linux: %s: no object for %s (run the compile step first)" % (prog, ", ".join(missing)))
    pflags = cflags + ["-I" + os.path.join(src, prog), PROG_DEFINE[prog]]

    # the definitions of the globals data.c does not define (zero-filled), as build/link.py writes them
    in_sections = {s[1:] for s in nm(os.path.join(d, "data.o"))[0] if s.startswith("_")}
    text, _ = winlink.data_c(src, prog, in_sections)
    # an import-address-table slot of an exported variable: the variable's address (no __imp_ on ELF)
    text = re.sub(r'extern char \*(\w+)__imp __asm__\("__imp_([^"]+)"\);\n'
                  r'int \(STDCALL \*(\w+)\)\(\);\n__attribute__\(\(constructor\)\)[^\n]*\n',
                  lambda m: 'extern char %s__sym __asm__("%s");\nint (STDCALL *%s)() = (int (STDCALL *)())&%s__sym;\n'
                  % (m.group(1), m.group(2), m.group(3), m.group(1)), text)
    open(os.path.join(d, "link_data.c"), "w", newline="\n").write(text)
    compile_c(cc, pflags, os.path.join(d, "link_data.c"), os.path.join(d, "link_data.o"))
    objs.append(os.path.join(d, "link_data.o"))

    # hand-written replacements, as build/link.py compiles them
    extra = [os.path.join(BUILD, "overrides.c")] + sorted(glob.glob(os.path.join(BUILD, "overrides_*.c"))) \
        + sorted(glob.glob(os.path.join(BUILD, "cleanroom", "*.c")))
    for f in extra:
        stem = ("cleanroom_" if os.path.basename(os.path.dirname(f)) == "cleanroom" else "") \
            + os.path.splitext(os.path.basename(f))[0]
        compile_c(cc, pflags, f, os.path.join(d, stem + ".lnx.o"))
        objs.append(os.path.join(d, stem + ".lnx.o"))
    compile_c(cc, pflags, os.path.join(BUILD, "fastpaths.c"), os.path.join(d, "fastpaths.lnx.o"), ["-O2", "-msse2"])
    objs.append(os.path.join(d, "fastpaths.lnx.o"))

    # functions reassembled from the disassembly (tools/gen_asm.py), with the COFF section names made ELF ones
    asm_src = os.path.join(src, prog, "asm_funcs.s")
    if os.path.exists(asm_src):
        s = open(asm_src, encoding="utf-8").read()
        s = s.replace('.section .rdata,"dr"', ".section .rodata")
        assemble(s, os.path.join(d, "asm_funcs.lnx.s"), os.path.join(d, "asm_funcs.lnx.o"))
        objs.append(os.path.join(d, "asm_funcs.lnx.o"))

    # names/lib_replace.json "aliases": runtime functions the system library provides under another name
    try:
        aliases = json.load(open(os.path.join(ROOT, "names", "lib_replace.json"))).get("aliases", {}).get(prog, {})
    except (OSError, ValueError):
        aliases = {}
    if aliases:
        lines = ["\t.text"]
        for sym, host in sorted(aliases.items()):
            # the host function lives outside the program: platform layer or system library (resolved at the final link)
            lines += ["\t.globl %s" % sym, "%s:\tjmp %s__host" % (sym, host)]
        assemble("\n".join(lines) + "\n", os.path.join(d, "lib_alias.lnx.s"), os.path.join(d, "lib_alias.lnx.o"))
        objs.append(os.path.join(d, "lib_alias.lnx.o"))

    # cleanroom/*.c `/* WRAPS: a b */`: calls of a from the other objects go to __wrap_a, __real_a is a (ld --wrap, done
    # by hand: the objects are renamed copies, because ld -r does not apply --wrap)
    wraps = []
    if prog == "GRIMFANDANGO.EXE":
        for cr in sorted(glob.glob(os.path.join(BUILD, "cleanroom", "*.c"))):
            for m in re.finditer(r"^/\* WRAPS: ([^*]*?)\s*\*/", open(cr, encoding="utf-8").read(), re.M):
                wraps += m.group(1).split()
    if wraps:
        wrapped = []
        for o in objs:
            defined, undefined = nm(o)
            ren = []
            for w in wraps:
                if "_" + w in undefined and "___wrap_" + w not in defined:
                    ren += ["--redefine-sym", "_%s=___wrap_%s" % (w, w)]
                if "___real_" + w in undefined:
                    ren += ["--redefine-sym", "___real_%s=_%s" % (w, w)]
            if ren:
                c = o[:-2] + ".wrap.o"
                must(["objcopy"] + ren + [o, c], "objcopy --redefine-sym " + o)
                o = c
            wrapped.append(o)
        objs = wrapped

    rel = os.path.join(d, prog.lower() + ".r0.o")
    must(["ld", "-m", "elf_i386", "-r", "--allow-multiple-definition", "-o", rel] + objs, "ld -r " + prog)

    # decorated references (asm labels) to functions the program itself defines undecorated
    defined, undefined = nm(rel)
    thunks = []
    for u in sorted(undefined):
        m = DECOR.match(u)
        if m:
            base = "_" + m.group(1) if m.group(1) else m.group(2)
            if base in defined:
                thunks.append((u, base))
    final_in = [rel]
    if thunks:
        assemble("\t.text\n" + "".join("\t.globl %s\n%s:\tjmp %s\n" % (u, u, b) for u, b in thunks),
                 os.path.join(d, "decor.lnx.s"), os.path.join(d, "decor.lnx.o"))
        final_in.append(os.path.join(d, "decor.lnx.o"))
    rel2 = os.path.join(d, prog.lower() + ".r1.o")
    must(["ld", "-m", "elf_i386", "-r", "-o", rel2] + final_in, "ld -r " + prog)

    # keep only the exports global
    keep = set()
    if prog == "GRIMFANDANGO.EXE":
        keep.add("_Win_WinMain")    # called by the platform layer's main()
    if prog.endswith(".DLL"):
        exports = {e["name"] for e in json.load(open(os.path.join(src, prog, "exports.json")))}
        for s in nm(rel2)[0]:
            m = DECOR.match(s)
            base = (m.group(1) or m.group(2)[1:]) if m else s[1:] if s.startswith("_") else None
            if base in exports:
                keep.add(s)
    keepf = os.path.join(d, "keep.txt")
    open(keepf, "w").write("\n".join(sorted(keep)) + "\n")
    out = os.path.join(d, prog.lower() + ".o")
    # G prefix: the program's names (`_exit`, `_tolower`, ...) must not bind to the system libraries' symbols of the same
    # spelling; the final link maps what is left of G_X to the platform layer or to the libraries (see main)
    loc = os.path.join(d, prog.lower() + ".r2.o")
    must(["objcopy", "--keep-global-symbols=" + keepf, rel2, loc], "objcopy " + prog)
    must(["objcopy", "--prefix-symbols=G", loc, out], "objcopy --prefix-symbols " + prog)
    print("%s: %d objects, %d exports kept global" % (prog, len(objs), len(keep)))
    return out


def main(src, obj, cc, cflags):
    progs = [program_object(cc, cflags, src, obj, p) for p in ORDER]
    # the platform layer
    plat = []
    pflags = cflags + ["-I" + os.path.join(HERE, "platform")]
    # the i386 SDL2 (pkg-config of the host architecture knows only the 64-bit one)
    env = dict(os.environ)
    env.setdefault("PKG_CONFIG_PATH", "/usr/lib/i386-linux-gnu/pkgconfig:/usr/lib32/pkgconfig:/usr/lib/pkgconfig")
    try:
        sdl = subprocess.run(["pkg-config", "--cflags", "sdl2"], capture_output=True, text=True, env=env).stdout.split()
    except OSError:
        sdl = []
    if not sdl:
        sdl = ["-I/usr/include/SDL2", "-D_REENTRANT"]
    pdir = os.path.join(obj, "platform")
    os.makedirs(pdir, exist_ok=True)
    for f in sorted(glob.glob(os.path.join(HERE, "platform", "*.c"))):
        o = os.path.join(pdir, os.path.splitext(os.path.basename(f))[0] + ".o")
        # the platform layer is ordinary C against the system headers: no Ghidra flags, no compat.h
        must([cc, "-m32", "-march=i686", "-O1", "-g", "-std=gnu11", "-fno-pic", "-U_FORTIFY_SOURCE",
              "-fno-stack-protector", "-fcf-protection=none", "-msse2", "-mfpmath=387", "-Wall", "-Wno-unused",
              "-I" + os.path.join(HERE, "platform")] + sdl + ["-c", f, "-o", o], "compile " + os.path.relpath(f, ROOT))
        plat.append(o)

    libsyms = library_symbols()
    target = os.path.join(obj, "grimfandango")
    glue_s = os.path.join(obj, "glue.s")
    stubs, thunks, decor = set(), {}, {}
    for attempt in range(8):
        lines = ["\t.text"]
        for u, b in sorted(decor.items()):
            lines += ["\t.globl %s" % u, "%s:\tjmp %s" % (u, b)]
        for u, t in sorted(thunks.items()):
            lines += ["\t.globl %s" % u, "%s:\tjmp %s" % (u, t)]
        for s in sorted(stubs):
            lines += ["\t.globl %s" % s, "%s:\tud2" % s]
        assemble("\n".join(lines) + "\n", glue_s, glue_s[:-2] + ".o")
        rc, out = run(["gcc", "-m32", "-no-pie", "-o", target] + progs + plat + [glue_s[:-2] + ".o"] + SYSLIBS
                      + ["-Wl,-z,noexecstack"])
        missing = set(re.findall(r"undefined reference to `([^']+)'", out))
        if rc == 0 or not missing:
            break
        new = 0
        for u in missing:
            if u in stubs or u in thunks or u in decor:
                continue
            new += 1
            if not u.startswith("G"):
                stubs.add(u)       # not a game symbol: a platform-layer bug, shows up in stubs.txt
                continue
            g = u[1:]
            m = DECOR.match(g)
            if g.endswith("__host"):
                thunks[u] = "G" + g[:-6]       # lib_alias: resolved like any other reference on the next round
            elif m:
                decor[u] = "G_" + m.group(1) if m.group(1) else "G" + m.group(2)
            elif g.startswith("_") and libsyms.get(g[1:], "") in ("T", "W", "i"):
                thunks[u] = g[1:]
            else:
                stubs.add(u)
        if not new:
            break
    with open(os.path.join(obj, "link.log"), "w") as f:
        f.write(out)
    open(os.path.join(obj, "stubs.txt"), "w").write("\n".join(sorted(stubs)) + "\n")
    open(os.path.join(obj, "libc_thunks.txt"), "w").write(
        "\n".join("%s -> %s" % kv for kv in sorted(thunks.items())) + "\n")
    if rc:
        print("link_linux: link FAILED (%s)" % os.path.join(obj, "link.log"))
        for l in [l for l in out.splitlines() if "error" in l.lower() or "multiple definition" in l][:20]:
            print("   ", l)
        return 1
    print("LINKED -> %s; %d stubbed (stubs.txt), %d system library thunks (libc_thunks.txt)"
          % (os.path.relpath(target), len(stubs), len(thunks)))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4:]))
