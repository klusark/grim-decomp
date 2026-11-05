"""check_slice.py <orig.bin> <slice.o>: compares the instruction sequence of the sliced (re-assembled) function with a
disassembly of the original 1.01 bytes (orig_bytes.hex, read from Ghidra /v101/GRIMFANDANGO.EXE).  Immediates and
displacements are replaced by N (addresses differ after relocation; GAS picks other encodings), registers and mnemonics
must match.  Prints a unified diff; empty = same instructions."""
import difflib, re, subprocess, sys
def norm(lines):
    out = []
    for l in lines:
        m = re.match(r'^\s+[0-9a-f]+:\s+(?:[0-9a-f]{2} )+\s*(\S.*)$', l)
        if not m: continue
        s = re.sub(r'<[^>]*>', '', m.group(1))
        s = re.sub(r'(0x[0-9a-f]+|\b(?=[0-9a-f]*\d)[0-9a-f]{3,}\b)', 'N', s)
        s = re.sub(r'\s+', ' ', s).strip()
        s = re.sub(r'^(j\w+|call) .*', r'\1 T', s)
        if s != 'nop': out.append(s)   # alignment padding after the ret
    return out
a = norm(subprocess.run(['objdump', '-D', '-b', 'binary', '-mi386', '-Mintel', sys.argv[1]], capture_output=True, text=True).stdout.splitlines())
b = norm(subprocess.run(['objdump', '-d', '-Mintel', sys.argv[2]], capture_output=True, text=True).stdout.splitlines())
d = list(difflib.unified_diff(a, b, 'original', 'slice', lineterm='', n=1))
print('\n'.join(d) if d else 'same instruction sequence (%d instructions)' % len(a))
