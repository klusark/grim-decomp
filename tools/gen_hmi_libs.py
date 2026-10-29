"""Build build/hmi/lib<name>.a import libraries for the game's HMIFXLIB.DLL / HMIFXFP.DLL.

The sound library DLLs are not rebuilt; IMUSE.DLL links against import libraries made from their
export tables. The .a files are not tracked (they derive from the game's DLLs), the .def files are
rewritten here.

Usage: python -I tools/gen_hmi_libs.py [game data folder]   (default C:/GOG Games/GRIMDATA)
"""
import os, re, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
game = sys.argv[1] if len(sys.argv) > 1 else "C:/GOG Games/GRIMDATA"
out = os.path.join(ROOT, "build", "hmi")
os.makedirs(out, exist_ok=True)
for stem in ("HMIFXLIB", "HMIFXFP"):
    dump = subprocess.run(["objdump", "-p", os.path.join(game, stem + ".DLL")], capture_output=True, text=True, check=True).stdout
    names = re.findall(r"^\s*\[\s*\d+\] \+base\[\s*\d+\]\s+[0-9a-f]+ (\S+)$", dump, re.M)
    if not names:
        sys.exit("no exports found in " + stem)
    deff = os.path.join(out, stem + ".def")
    open(deff, "w").write("LIBRARY %s.DLL\nEXPORTS\n%s\n" % (stem, "\n".join(names)))
    subprocess.run(["C:/msys64/mingw32/bin/dlltool.exe", "-m", "i386", "-d", deff, "-l", os.path.join(out, "lib%s.a" % stem.lower()), "-k"], check=True)
    print(stem, len(names), "exports")
