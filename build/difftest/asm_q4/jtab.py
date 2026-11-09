"""Resolve the texture-width switches of the FlatLit drivers: width -> span filler, from the byte index table in .text
and the jump table of the assembly.  usage: python -I jtab.py <driver name>"""
import os, re, sys

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", "..")
text = open(os.path.join(ROOT, "raw", "GRIMFANDANGO.EXE", "sections", "text.bin"), "rb").read()
src = open(os.path.join(ROOT, "src", "GRIMFANDANGO.EXE", "asm_funcs.s")).read()
name = sys.argv[1]
fb = re.search(r"(?ms)^_%s:.*?(?=^\t\.def )" % re.escape(name), src).group(0)
lines = fb.splitlines()
for i, l in enumerate(lines):
    m = re.search(r"(lea|add) EAX,\[E[A-Z]X\+-0x([0-9a-f]+)\]|add EAX,-0x([0-9a-f]+)", l)
    m2 = re.search(r"b?y?t?e? ?ptr \[EAX\+_sect_text\+0x([0-9a-f]+)\]", l)
    if m2:
        # bias: the instruction that subtracts from the width a few lines above
        bias = None
        for k in range(i - 1, i - 6, -1):
            mb = re.search(r"\[E[A-Z]X\+-0x([0-9a-f]+)\]|add EAX,-0x([0-9a-f]+)", lines[k])
            if mb:
                bias = int(mb.group(1) or mb.group(2), 16)
                break
        mc = re.search(r"cmp EAX,0x([0-9a-f]+)", "\n".join(lines[i - 4:i]))
        lim = int(mc.group(1), 16)
        tab = 0x401000 + int(m2.group(1), 16)
        jt = re.search(r"jmp dword ptr \[e[a-z]x\*4\+(\.Ljt_\w+)\]", lines[i + 1]).group(1)
        targets = re.search(r"(?ms)^%s:\n((?:\t\.long [^\n]*\n)+)" % re.escape(jt), src).group(1)
        targets = re.findall(r"\.long (\S+)", targets)
        res = {}
        for w in range(bias, bias + lim + 1):
            idx = text[tab - 0x401000 + w - bias]
            lab = targets[idx]
            mm = re.search(r"(?m)^%s:\t.*offset _(\w+)" % re.escape(lab), fb)
            res.setdefault(mm.group(1) if mm else lab, []).append(w)
        print("table at %x, bias %d, limit %d:" % (tab, bias, lim))
        for k, v in res.items():
            print("   %-32s %s" % (k, v if len(v) < 10 else "%d widths (default)" % len(v)))
