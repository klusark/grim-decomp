r"""Peephole pass over src/<prog>/asm_funcs.s (run by link.py before assembling; GRIM_NO_PEEPHOLE=1 skips it).

The assembled MSVC code converts floats to integers by switching the x87 control word around every conversion:

    fldcw [floor]; fld dword [m]; fistp dword [d]; fldcw [default]            (1807 sites in the EXE)
    fldcw [ceil];  fld dword [m]; frndint; fstp dword [d]; fldcw [default]    (102 sites)

A fldcw drains the x87 pipeline on current CPUs, and these sites sit in the rasteriser's per-scanline edge set-up
(rdRaster_SpanR_Flat_*), which was the single hottest code in every scene. They are replaced by SSE4.1 rounding with
the same result (floor/ceil are exact in single precision; out-of-range gives 0x80000000 in both). The control word
variables are the EXE's DAT_00900524 (default) / ...526 (floor, 0x077f) / ...52a (ceil, 0x0b7f), set by
stdStartup. Only EXE sequences whose interior labels are not jump targets are rewritten. The CRT's `_ftol`
(fstcw / fldcw trunc / fistp qword / fldcw) becomes one `fisttp` (SSE3).

Proposed fix (agent q5, docs/notes/asm_q5.md; build/peephole.py itself is unchanged): the perspective span fillers
load the truncating 24-bit control word (DAT_00900528) at their start and rely on the `fldcw [default]` at the end of
their first conversion to go back to the default precision and rounding.  In a function that loads DAT_00900528 the
rewritten sequences therefore keep their final `fldcw [default]` (the SSE conversion does not depend on the control
word, so keeping it on every conversion of such a function, whichever runs first, gives the original's behaviour).

usage: python -I peephole.py in.s out.s"""
import re, sys

LBL = r"(?:(\.L\w+):)?"
CW = {"0x423524": "def", "0x423526": "floor", "0x42352a": "ceil"}
FLDCW = re.compile(r"^" + LBL + r"\s*fldcw word ptr \[_sect_data\+(0x423524|0x423526|0x42352a)\]\s*$")
FLD = re.compile(r"^" + LBL + r"\s*fld dword ptr (\[[^\]]+\])\s*$")
FISTP = re.compile(r"^" + LBL + r"\s*fistp dword ptr (\[[^\]]+\])\s*$")
FRNDINT = re.compile(r"^" + LBL + r"\s*frndint\s*$")
FSTP = re.compile(r"^" + LBL + r"\s*fstp dword ptr (\[[^\]]+\])\s*$")
REF = re.compile(r"\.L[0-9a-f]+_[0-9a-f]+")
FUNC = re.compile(r"^([_@][\w@]+):\s+#")
TRUNC = "fldcw word ptr [_sect_data+0x423528]"


def main(src, dst):
    text = open(src, encoding="utf-8", errors="replace", newline="").read()
    lines = text.split("\n")
    # label references (operands), definitions excluded
    refs = {}
    for l in lines:
        body = re.sub(r"^\.L\w+:", "", l)
        for m in REF.findall(body):
            refs[m] = refs.get(m, 0) + 1
    # functions that load the truncating 24-bit control word, and the function of each line
    func_of, cur, trunc_funcs = [], None, set()
    for l in lines:
        m = FUNC.match(l)
        if m:
            cur = m.group(1)
        func_of.append(cur)
        if TRUNC in l:
            trunc_funcs.add(cur)
    out = []
    i = 0
    n = len(lines)
    stats = {"floor": 0, "ceil": 0, "ftol": 0, "skipped": 0, "kept_default": 0}

    def lab(m):
        return m.group(1) if m and m.group(1) else None

    def emit(label, ins):
        out.append((label + ":" if label else "") + "\t" + ins)

    while i < n:
        l = lines[i].rstrip("\r")
        m1 = FLDCW.match(l)
        if m1 and CW[m1.group(2)] in ("floor", "ceil") and i + 3 < n:
            kind = CW[m1.group(2)]
            a = [lines[i + k].rstrip("\r") for k in range(1, 5 if kind == "ceil" else 4)]
            labels = [lab(m1)]
            ok = False
            if kind == "floor" and len(a) == 3:
                m2, m3, m4 = FLD.match(a[0]), FISTP.match(a[1]), FLDCW.match(a[2])
                if m2 and m3 and m4 and CW[m4.group(2)] == "def":
                    ok = True
                    labels += [lab(m2), lab(m3), lab(m4)]
                    src_m, dst_m = m2.group(2), m3.group(2)
                    code = ["movss xmm0, dword ptr " + src_m, "roundss xmm0, xmm0, 9",
                            "cvttps2dq xmm0, xmm0", "movd dword ptr " + dst_m + ", xmm0"]
            elif kind == "ceil" and len(a) == 4:
                m2, m3, m4, m5 = FLD.match(a[0]), FRNDINT.match(a[1]), FSTP.match(a[2]), FLDCW.match(a[3])
                if m2 and m3 and m4 and m5 and CW[m5.group(2)] == "def":
                    ok = True
                    labels += [lab(m2), lab(m3), lab(m4), lab(m5)]
                    code = ["movss xmm0, dword ptr " + m2.group(2), "roundss xmm0, xmm0, 10",
                            "movss dword ptr " + m4.group(2) + ", xmm0"]
            if ok:
                if any(lb and refs.get(lb, 0) for lb in labels[1:]):
                    stats["skipped"] += 1
                    ok = False
            if ok:
                for k, ins in enumerate(code):
                    emit(labels[0] if k == 0 else None, ins)
                for lb in labels[1:] + ([] if labels[0] else []):
                    if lb:
                        out.append(lb + ":")
                if func_of[i] in trunc_funcs:
                    emit(None, "fldcw word ptr [_sect_data+0x423524]")
                    stats["kept_default"] += 1
                stats[kind] += 1
                i += 1 + (4 if kind == "ceil" else 3)
                continue
        out.append(lines[i])
        i += 1
    res = "\n".join(out)
    # _ftol: standard MSVC (fstcw, fldcw trunc, fistp qword, fldcw) -> fisttp
    pat = re.compile(r"(__ftol:  # _ftol\n)(?:.*\n){1,40}?(\.L4ac6f0_4ac716:\tret\r?\n)")
    m = pat.search(res)
    if m and "fistp qword ptr [EBP+-0xc]" in m.group(0):
        new = (m.group(1) + ".L4ac6f0_4ac6f0:\tsub ESP,8\n\tfisttp qword ptr [ESP]\n\tmov EAX,dword ptr [ESP]\n"
               "\tmov EDX,dword ptr [ESP+4]\n\tadd ESP,8\n" + m.group(2))
        res = res[:m.start()] + new + res[m.end():]
        stats["ftol"] = 1
    open(dst, "w", encoding="utf-8", newline="").write(res)
    print("peephole: " + ", ".join("%s %d" % kv for kv in stats.items()))


if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2])
