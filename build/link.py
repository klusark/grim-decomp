"""Stretch goal: link each program from its objects (run by `make link`).

The decompiled code is not a complete program: Ghidra exports no initialised data
(only names and, for some, a type), Windows/DirectX imports are called through
undecorated, unprototyped declarations, and jumps into other functions are
traps. So this links *for completeness*, not to run:

  obj/<prog>/data.c    a definition for every symbol in globals.h (zero-filled;
                       s_ strings are initialised from raw/<prog>/strings.txt)
  obj/<prog>/stubs.c   a trapping definition for every symbol still undefined
                       after that (imports, thunks, FUN_ with no function, LAB_)
  obj/<prog>/<prog>    the linked PE (i686, -nostdlib, at the original image base)

and reports how many symbols each category needed. The DLLs are linked first,
exporting everything, so GRIMFANDANGO.EXE links against the rebuilt LUA.DLL.

usage: python -I link.py <i686-gcc> <srcdir> <objdir> PROG..."""
import glob
import json
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
IMAGE_BASE = {"GRIMFANDANGO.EXE": "0x400000"}
ORDER = ["LUA.DLL", "IMUSE.DLL", "CHORE.DLL", "GRIMFANDANGO.EXE"]
# rebuilt DLLs a program links against (their exports replace stubs)
DLL_IMPORTS = {"GRIMFANDANGO.EXE": ["LUA.DLL", "IMUSE.DLL", "CHORE.DLL"],
               "IMUSE.DLL": [], "CHORE.DLL": []}
try:
    STDCALL_NAMES = json.load(open(os.path.join(os.path.dirname(os.path.abspath(__file__)), "stdcall_names.json")))
except (OSError, ValueError):
    STDCALL_NAMES = {}
WIN32_LIBS = ["-lkernel32", "-luser32", "-lgdi32", "-lwinmm", "-lddraw", "-ldinput", "-ldsound",
              "-ladvapi32", "-lcomdlg32", "-lole32", "-lshell32", "-lcomctl32"]


def run(cmd, env):
    p = subprocess.run(cmd, capture_output=True, text=True, env=env)
    return p.returncode, p.stdout + p.stderr


def c_string(s):
    """strings.txt escapes control characters (\\n, \\r, \\t) but not quotes or
    backslashes (`C:\\grimsrc\\libs`); re-escape those."""
    s = re.sub(r'\\(?![nrt0])', r'\\\\', s)
    return s.replace('"', '\\"').replace("??", "?\\?")


def load_strings(prog):
    out = {}
    path = os.path.join(ROOT, "raw", prog, "strings.txt")
    if os.path.exists(path):
        for line in open(path, encoding="utf-8", errors="replace"):
            m = re.match(r'^([0-9a-f]{8}): "(.*)"\s*$', line)
            if m:
                out[m.group(1)] = m.group(2)
    return out


def data_exports():
    """Exported *variables* of the rebuilt DLLs (lua_savehook, lua_callhook ...):
    export addresses outside the DLL's .text. The EXE reaches them through its
    import address table, which holds the variable's address."""
    names = set()
    for prog in ("LUA.DLL", "IMUSE.DLL", "CHORE.DLL"):
        raw = os.path.join(ROOT, "raw", prog)
        try:
            text_range = None
            for line in open(os.path.join(raw, "segments.txt")):
                if line.startswith(".text:"):
                    lo, hi = line.split(":", 1)[1].strip().split(" - ")
                    text_range = (int(lo, 16), int(hi, 16))
            for line in open(os.path.join(raw, "exports.json"), encoding="utf-8", errors="replace"):
                m = re.match(r"^(\S+) -> ([0-9a-f]{8})", line.strip())
                if m and not m.group(1).startswith("Ordinal_") and text_range:
                    a = int(m.group(2), 16)
                    if not (text_range[0] <= a <= text_range[1]):
                        names.add(m.group(1))
        except OSError:
            pass
    return names


DATA_EXPORTS = None


def data_c(src, prog, in_sections=frozenset()):
    """Turn each `extern T name;` of globals.h (and the _exref slots of
    functions.h) into a definition, except the symbols data.s already places
    inside the dumped sections (`in_sections`)."""
    strings = load_strings(prog)
    lines = ['#include "ghidra_types.h"', '#include "globals.h"', '#include "functions.h"', ""]
    names = set()
    decls = []
    for hdr in ("globals.h", "functions.h"):
        for line in open(os.path.join(src, prog, hdr), encoding="utf-8"):
            m = re.match(r"^extern (.*?);", line)
            if m:
                decls.append(m.group(1))
    for d in decls:
        if d.startswith("code ") and "*" not in d:
            continue  # LAB_ code address: stubbed as a function
        if "_exref" in d:
            # import address table slot: point it at the real import
            name = re.search(r"\*\s*([A-Za-z_]\w*_exref)", d).group(1)
            if name not in names:
                names.add(name)
                # bind through an asm-named alias: works whether the import is declared
                # stdcall, cdecl or not at all (some slots are exported variables)
                base = name[:-6]
                global DATA_EXPORTS
                if DATA_EXPORTS is None:
                    DATA_EXPORTS = data_exports()
                asm_name = STDCALL_NAMES.get(base, "_" + base)
                if base in DATA_EXPORTS:
                    # an exported variable: the original reads its address out of the
                    # import address table slot. Binding to the import library's symbol
                    # would give the address of its code thunk, so fill the slot's value
                    # from __imp_<name> (the loader's resolved address) before main.
                    lines.append(f'extern char *{base}__imp __asm__("__imp_{asm_name}");')
                    lines.append(f"int (STDCALL *{name})();")
                    lines.append(f"__attribute__((constructor)) static void init_{name}(void) {{ {name} = (int (STDCALL *)()){base}__imp; }}")
                else:
                    lines.append(f'extern char {base}__sym __asm__("{asm_name}");')
                    lines.append(f"int (STDCALL *{name})() = (int (STDCALL *)())&{base}__sym;")
            continue
        name = re.search(r"([A-Za-z_]\w*)\s*(\[[^\]]*\])?$", d).group(1)
        if name in names or name in in_sections:
            continue
        names.add(name)
        if d.endswith("[]"):
            addr = name[-8:]
            if name.startswith("s_") and addr in strings:
                lines.append(f'{d} = "{c_string(strings[addr])}";')
            else:
                lines.append(d[:-2] + "[4];")
        else:
            lines.append(d + ";")
    return "\n".join(lines) + "\n", names


def undefined_symbols(log):
    syms = set()
    for m in re.finditer(r"undefined reference to `([^']+)'", log):
        syms.add(m.group(1))
    return syms


def link(cc, src, obj, prog, env):
    d = os.path.join(obj, prog)
    # only objects of modules that still exist in src/ (a regenerated tree can drop some)
    mods = [os.path.basename(c)[:-2] for c in sorted(glob.glob(os.path.join(src, prog, "*.c")))]
    # the decompiled MSVC 6 runtime (crt.c) is left out: the host msvcrt provides
    # malloc/fopen/_stricmp/... and the start-up code (see startup.c)
    objs = [os.path.join(d, m + ".o") for m in mods if m != "crt" and os.path.exists(os.path.join(d, m + ".o"))]
    if not objs:
        print(f"{prog}: no objects (run `make objs` first)")
        return
    cflags = ["-std=gnu11", "-fpermissive", "-w", "-fno-builtin", "-ffreestanding", "-fno-common", "-include",
              os.path.join(os.path.dirname(os.path.abspath(__file__)), "compat.h"),
              "-I" + os.path.join(src, prog)]
    # real section contents (raw/<prog>/sections) with labels and relocations
    here = os.path.dirname(os.path.abspath(__file__))
    in_sections = set()
    gen = subprocess.run([sys.executable, "-I", os.path.join(here, "gendata.py"), prog, src, obj],
                         capture_output=True, text=True, env=env)
    if gen.returncode == 0 and gen.stdout.strip():
        info = json.loads(gen.stdout.strip().splitlines()[-1])
        in_sections = set(info["defined"])
        rc, out = run([cc, "-m32", "-c", os.path.join(d, "data.s"), "-o", os.path.join(d, "data_s.o")], env)
        if rc:
            print(f"{prog}: data.s does not assemble:\n{out[:3000]}")
            return
        objs.append(os.path.join(d, "data_s.o"))
        print(f"{prog}: data.s: {len(in_sections)} symbols placed in the dumped sections, "
              f"relocations {info['stats']}")
    else:
        print(f"{prog}: no section dump (tools/export_data.py), data stays zero-filled\n{gen.stderr[:500]}")
    # Win32 entry points the import libraries lack (intrinsics) + mingwex hooks
    fence = ["-DGRIM_FENCE"] if os.environ.get("GRIM_FENCE") and not prog.endswith(".DLL") else []  # debug allocator, see win32_shims.c
    rc, out = run([cc] + cflags + fence + ["-c", os.path.join(here, "win32_shims.c"), "-o", os.path.join(d, "win32_shims.o")], env)
    if rc:
        print(f"{prog}: win32_shims.c does not compile:\n{out[:2000]}")
        return
    objs.append(os.path.join(d, "win32_shims.o"))
    text, names = data_c(src, prog, in_sections)
    names |= in_sections
    open(os.path.join(d, "data.c"), "w", newline="\n").write(text)
    rc, out = run([cc] + cflags + ["-c", os.path.join(d, "data.c"), "-o", os.path.join(d, "data.o")], env)
    if rc:
        print(f"{prog}: data.c does not compile:\n{out[:3000]}")
        return
    is_dll = prog.endswith(".DLL")
    target = os.path.join(d, prog.lower())
    # linked against the host mingw/msvcrt runtime: it supplies the CRT functions the
    # decompiled code calls and the start-up (DllMainCRTStartup / WinMainCRTStartup)
    ldflags = ["-Wl,--enable-stdcall-fixup", "-Wl,--no-insert-timestamp", "-Wl,--allow-multiple-definition",
               "-Wl,--disable-dynamicbase"]
    if prog in IMAGE_BASE:
        ldflags.append("-Wl,--image-base=" + IMAGE_BASE[prog])
    if is_dll:
        ldflags += ["-shared", "-Wl,--export-all-symbols",
                    "-Wl,--out-implib=" + os.path.join(d, "lib" + prog.split(".")[0].lower() + ".a")]
    else:
        ldflags += ["-mwindows"]
        rc, out = run([cc] + cflags + ["-c", os.path.join(here, "startup.c"), "-o", os.path.join(d, "startup.o")], env)
        if rc:
            print(f"{prog}: startup.c does not compile:\n{out[:2000]}")
            return
        objs.append(os.path.join(d, "startup.o"))
    # hand-written replacements (see overrides.c); compiled per program for its headers
    ov_flags = {"GRIMFANDANGO.EXE": ["-DGRIM_EXE"], "IMUSE.DLL": ["-DGRIM_IMUSE"], "CHORE.DLL": ["-DGRIM_CHORE"]}.get(prog, [])  # per-program sections of overrides.c
    rc, out = run([cc] + cflags + ov_flags + ["-c", os.path.join(here, "overrides.c"), "-o", os.path.join(d, "overrides.o")], env)
    if rc:
        print(f"{prog}: overrides.c does not compile:\n{out[:2000]}")
        return
    objs.append(os.path.join(d, "overrides.o"))
    # functions reassembled from the disassembly (tools/gen_asm.py)
    asm_src = os.path.join(src, prog, "asm_funcs.s")
    if os.path.exists(asm_src):
        rc, out = run([cc, "-m32", "-c", asm_src, "-o", os.path.join(d, "asm_funcs.o")], env)
        if rc:
            print(f"{prog}: asm_funcs.s does not assemble:\n{out[:2000]}")
            return
        objs.append(os.path.join(d, "asm_funcs.o"))
    libs = []
    for dep in DLL_IMPORTS.get(prog, []):
        imp = os.path.join(obj, dep, "lib" + dep.split(".")[0].lower() + ".a")
        if os.path.exists(imp):
            libs.append(imp)
    libs += ["-lmingwex", "-lgcc"]  # x87 math helpers (sinl, exp2l, ldexpl, sqrtl), 64-bit division
    # the real Win32 / DirectX import libraries (mingw-w64-i686); --enable-stdcall-fixup
    # binds the undecorated `_CreateFileA` of the decompiled code to `_CreateFileA@28`
    libs += WIN32_LIBS
    hmi = os.path.join(here, "hmi")  # import libraries built from the game's HMIFX*.DLL
    if os.path.exists(os.path.join(hmi, "libhmifxlib.a")):
        libs += ["-L" + hmi, "-lhmifxlib", "-lhmifxfp"]
    stub_path = os.path.join(d, "stubs.c")
    open(stub_path, "w").write("int mainCRTStartup_stub(void) { __builtin_trap(); }\n")
    stubs = set()
    for attempt in range(4):
        rc, out = run([cc] + cflags + ["-c", stub_path, "-o", os.path.join(d, "stubs.o")], env)
        if rc:
            print(f"{prog}: stubs.c does not compile:\n{out[:2000]}")
            return
        rc, out = run([cc, "-m32"] + ldflags + ["-o", target] + objs
                      + [os.path.join(d, "data.o"), os.path.join(d, "stubs.o")] + libs, env)
        missing = undefined_symbols(out)
        if rc == 0 or not missing:
            break
        new = missing - stubs
        if not new:
            break
        stubs |= new
        body = ["/* GENERATED by build/link.py: symbols the decompiled code references but",
                " * nothing defines (imports, thunks, FUN_/LAB_ addresses without a function). */",
                "int mainCRTStartup_stub(void) { __builtin_trap(); }"]
        for s in sorted(stubs):
            # ld reports C-level names (the i386 '_' prefix stripped); decorated
            # stdcall (`f@8`) / fastcall (`@f@8`) names need an explicit asm label
            if "@" in s:
                asm = s if s.startswith("@") else "_" + s
                c = "stub_" + re.sub(r"\W", "_", s)
                body.append(f'int {c}(void) __asm__("{asm}");')
                body.append(f"int {c}(void) {{ __builtin_trap(); }}")
            else:
                body.append(f"int {s}() {{ __builtin_trap(); }}")
        open(stub_path, "w", newline="\n").write("\n".join(body) + "\n")
    with open(os.path.join(d, "link.log"), "w") as f:
        f.write(out)
    errors = [l for l in out.splitlines() if "error" in l.lower() or "multiple definition" in l]
    try:
        imports = {i["name"] for i in json.load(open(os.path.join(ROOT, "raw", prog, "imports.json")))}
    except (OSError, ValueError):
        imports = set()
    kinds = {}
    for s in stubs:
        c = s.split("@")[0]
        k = ("FUN_" if c.startswith("FUN_") else "LAB_" if c.startswith("LAB_") else
             "import" if c in imports else "entry" if c == "mainCRTStartup_stub" else "other")
        kinds[k] = kinds.get(k, 0) + 1
    with open(os.path.join(d, "stubs.txt"), "w") as f:
        f.write("\n".join(sorted(stubs)) + "\n")
    status = "LINKED" if rc == 0 else "link FAILED"
    print(f"{prog}: {status} -> {os.path.relpath(target)}; {len(objs)} objects, "
          f"{len(names)} data symbols defined, {len(stubs)} symbols stubbed {kinds}")
    if rc:
        for l in errors[:15]:
            print("   ", l)
        print(f"    (full log: {os.path.relpath(os.path.join(d, 'link.log'))})")


def main(cc, src, obj, progs):
    env = dict(os.environ)
    ccdir = os.path.dirname(cc)
    if ccdir:  # the i686 gcc needs its own bin/ first on PATH (cc1, as, ld)
        env["PATH"] = ccdir + os.pathsep + env.get("PATH", "")
    if not os.path.exists(cc) and not os.path.exists(cc + ".exe"):
        print(f"no i686 toolchain at {cc}: install mingw-w64-i686-gcc (pacman -S mingw-w64-i686-gcc)")
        return 1
    for prog in [p for p in ORDER if p in progs]:
        link(cc, src, obj, prog, env)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4:]))
