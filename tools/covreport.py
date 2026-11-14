"""Line coverage of the coverage build (make COVERAGE=1, see tools/coverage.sh): gcov on every object of the build, summed
per program and per source file.

usage: python -I tools/covreport.py [--obj build/obj-cov] [--gcov GCOV] [--out DIR] [--prog P] [--uncovered]

Writes DIR/summary.md (per program, per file), DIR/functions.tsv (every function: program, file, line, name, lines, lines run,
calls) and DIR/gcov/<prog>/<file>.gcov (gcov's text: "#####" marks a line never run). --uncovered also prints the largest
functions never called, the places a new test would add the most. Default GCOV: i686-w64-mingw32-gcov, else gcov."""

import argparse
import json
import os
import shutil
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
BUILD = os.path.join(os.path.dirname(HERE), "build")
PROGS = ["GRIMFANDANGO.EXE", "LUA.DLL", "IMUSE.DLL", "CHORE.DLL"]


def run_gcov(gcov, objdir, prog, text_dir):
    """gcov's JSON of every .gcda of one program (files: {source: {line: count}}, functions: [...])."""
    d = os.path.join(objdir, prog)
    gcdas = sorted(f for f in os.listdir(d) if f.endswith(".gcda")) if os.path.isdir(d) else []
    files, funcs = {}, []
    for g in gcdas:
        gp = os.path.abspath(os.path.join(d, g))
        # (from build/, where the objects were compiled: the sources' paths in the .gcno files are relative to it)
        j = subprocess.run([gcov, "-j", "-t", "-o", gp, gp], cwd=BUILD, capture_output=True, text=True).stdout
        for doc in j.splitlines():
            if not doc.startswith("{"):
                continue
            data = json.loads(doc)
            cwd = data.get("current_working_directory", BUILD)
            for fe in data.get("files", []):
                src = os.path.normpath(os.path.join(cwd, fe["file"]))
                lines = files.setdefault(src, {})
                for ln in fe.get("lines", []):
                    lines[ln["line_number"]] = lines.get(ln["line_number"], 0) + ln["count"]
                for fn in fe.get("functions", []):
                    funcs.append((src, fn))
        if text_dir:
            os.makedirs(os.path.join(text_dir, prog), exist_ok=True)
            t = subprocess.run([gcov, "-t", "-o", gp, gp], cwd=BUILD, capture_output=True, text=True).stdout
            open(os.path.join(text_dir, prog, os.path.splitext(g)[0] + ".gcov"), "w").write(t)
    return files, funcs


def rel(src):
    root = os.path.dirname(BUILD)
    return os.path.relpath(src, root) if src.startswith(root) else src


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--obj", default=os.path.join(BUILD, "obj-cov"))
    ap.add_argument("--gcov", default=shutil.which("i686-w64-mingw32-gcov") or "gcov")
    ap.add_argument("--out", default=os.path.join(BUILD, "coverage"))
    ap.add_argument("--prog", action="append")
    ap.add_argument("--uncovered", action="store_true")
    a = ap.parse_args()
    os.makedirs(a.out, exist_ok=True)
    text_dir = os.path.join(a.out, "gcov")
    shutil.rmtree(text_dir, ignore_errors=True)
    summary = ["# Coverage of the clean-room tests", "",
               "| Program | Lines | Run | % | Functions | Called | % |", "|---|---|---|---|---|---|---|"]
    per_file = ["", "| File | Lines | Run | % |", "|---|---|---|---|"]
    rows, never = [], []
    if True:
        for prog in a.prog or PROGS:
            files, funcs = run_gcov(a.gcov, a.obj, prog, text_dir)
            # (a header's inline code is counted once per program: the files are summed over the objects above)
            tl = tr = 0
            for src in sorted(files):
                lines = files[src]
                n, r = len(lines), sum(1 for c in lines.values() if c > 0)
                tl, tr = tl + n, tr + r
                per_file.append("| %s | %d | %d | %.1f |" % (rel(src), n, r, 100.0 * r / n if n else 0))
            seen = {}
            for src, fn in funcs:
                k = (src, fn["name"])
                e = seen.setdefault(k, [fn["start_line"], fn.get("end_line", fn["start_line"]), 0, fn.get("demangled_name", fn["name"])])
                e[2] += fn["execution_count"]
            fc = sum(1 for e in seen.values() if e[2] > 0)
            summary.append("| %s | %d | %d | %.1f | %d | %d | %.1f |" % (prog, tl, tr, 100.0 * tr / tl if tl else 0, len(seen), fc,
                                                                      100.0 * fc / len(seen) if seen else 0))
            for (src, name), (start, end, calls, _) in sorted(seen.items()):
                lines = files.get(src, {})
                body = [c for ln, c in lines.items() if start <= ln <= end]
                rows.append("%s\t%s\t%d\t%s\t%d\t%d\t%d" % (prog, rel(src), start, name, len(body), sum(1 for c in body if c), calls))
                if calls == 0:
                    never.append((len(body), prog, rel(src), start, name))
    open(os.path.join(a.out, "summary.md"), "w").write("\n".join(summary + per_file) + "\n")
    open(os.path.join(a.out, "functions.tsv"), "w").write("prog\tfile\tline\tfunction\tlines\trun\tcalls\n" + "\n".join(rows) + "\n")
    print("\n".join(summary))
    print("(per file: %s; per function: %s)" % (os.path.join(a.out, "summary.md"), os.path.join(a.out, "functions.tsv")))
    if a.uncovered:
        print("\nlargest functions never called:")
        for n, prog, src, start, name in sorted(never, reverse=True)[:60]:
            print("%5d  %-16s %s:%d %s" % (n, prog, src, start, name))


if __name__ == "__main__":
    sys.exit(main())
