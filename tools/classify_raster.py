"""Derive systematic names for the RDroid software rasterizer variants.

The region 0x40e500-0x4731f0 of GRIMFANDANGO.EXE holds ~360 near-identical
triangle drawers, edge walkers and span fillers (one per combination of
bit depth / texturing / lighting / colour key / z-buffer).  Reading each by
hand is not worth it, so this script derives a feature vector from the
decompiled text and emits names/exe_raster_auto.json:

  rdRaster_<Role><Bpp>_<Features>_<n>

Role  : Draw (polygon entry), Edge (edge walker), Span (fills between two
        edge records), SpanP (perspective-subdivided span), SpanR (fills a
        span record), EdgeSetup, Grad (gradient setup)
Bpp   : 8 or 16 (omitted when the function dispatches on both)
Feat  : Tex/Flat, Lit (light interpolant / light table), Key (colour key),
        Z (z compare), Zw (z write only)
<n>   : disambiguator within the same feature class

Usage: python -I classify_raster.py [--dry]  (run from tools/)
"""
import json, os, re, sys, collections
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
FN = os.path.join(ROOT, "raw", "GRIMFANDANGO.EXE", "functions")
LO, HI = 0x40e500, 0x4731f0
# functions in the range that are named by hand elsewhere
SKIP = {0x40e500, 0x40ea50, 0x40ef90, 0x417e90, 0x417ea0, 0x417f30, 0x418360, 0x4183a0, 0x4184a0,
        0x418fe0, 0x419150, 0x42dba0, 0x42dd10, 0x446c10, 0x446e80, 0x446ec0, 0x446f80,
        0x4478c0, 0x448260, 0x4489b0, 0x449350, 0x449aa0, 0x44a6d0, 0x44b0a0, 0x44be80, 0x44c9d0,
        0x44da40, 0x44f1a0, 0x44f1d0, 0x44f8a0, 0x44fa70, 0x44fe50, 0x44fe80, 0x44feb0, 0x450170,
        0x450560, 0x4505a0, 0x4506a0, 0x4506d0, 0x4506f0, 0x450720, 0x450780, 0x4507e0, 0x450b50,
        0x451460, 0x451510, 0x451800, 0x451950, 0x451dd0, 0x471a80, 0x471b10, 0x471d40, 0x471d60,
        0x471e00, 0x471ee0, 0x472360, 0x472640, 0x4728a0, 0x472910, 0x472b50, 0x472b70, 0x472bd0,
        0x4730d0, 0x473180, 0x473270}

SIG_RE = re.compile(r'^[A-Za-z0-9_ *]+?\s*\**FUN_([0-9a-f]+)\(([^)]*)\)', re.M)
CALL_RE = re.compile(r'\b(FUN_[0-9a-f]{8})\(')


def role_of(sig, text, nlines):
    p = [re.sub(r'\s*param_\d+', '', x).strip() for x in sig.split(',')] if sig.strip() and sig.strip() != 'void' else []
    if p == ['uint *', 'uint *']:
        return 'Span'
    if p == ['uint *']:
        return 'SpanP' if nlines > 120 else 'SpanR'
    if p == ['int *']:
        return 'Edge' if 'DAT_007f4308' in text else 'SpanR'
    if p == ['undefined4 *', 'int *', 'int', 'int']:
        return 'EdgeSetup'
    if p == ['float']:
        return 'Grad'
    if p in (['int', 'int'], ['int', 'int', 'float'], ['float *', 'int'], ['int *', 'int'], ['int *', 'int', 'float'], ['float *', 'int', 'float']):
        return 'Select' if 'param_1[0x7a] =' in text or 'param_1[0x6d] =' in text else 'Draw'
    return None


def features(text):
    f = []
    bpp = None
    if re.search(r'0x18\) >> 1\)', text):
        bpp = 16
    elif re.search(r'\(undefined1 \*\)\(|\(char \*\)\(\*\(int \*\)|\(byte \*\)\(\*\(int \*\)', text):
        bpp = 8
    tex = bool(re.search(r'\*\(byte \*\)\(', text)) or 'DAT_008ddf3c' in text
    f.append('Tex' if tex else 'Flat')
    if re.search(r'param_2\[4\] - \(float\)param_1\[4\]|& 0x3f0000|DAT_007f4b30|param_1\[8\] \+|\+ 0x330\)|\+ 0x348\)', text) and tex:
        f.append('Lit')
    if re.search(r"!= '\\0'\)|[cb]Var\d+ != 0\)", text):
        f.append('Key')
    z = bool(re.search(r'DAT_007f0fc8 \+ 4\) \+ 0x10\)', text))
    if z:
        f.append('Z' if re.search(r'if \(\*\w+ <=? |<=? \*\w+\) \{|if \(\(?u?Var\d+ <=? \*', text) else 'Zw')
    return bpp, f


def main():
    dry = '--dry' in sys.argv
    files = sorted(os.listdir(FN))
    info = {}
    for fn in files:
        a = int(fn[:-2], 16)
        if not (LO <= a < HI) or a in SKIP:
            continue
        text = open(os.path.join(FN, fn)).read()
        if 'FUN_%08x' % a not in text.split('\n{')[0]:
            continue  # already named
        m = SIG_RE.search(text)
        if not m:
            continue
        nl = text.count('\n')
        role = role_of(m.group(2), text, nl)
        if role is None:
            print('skip', fn, m.group(2)[:60]); continue
        calls = sorted(set(int(c[4:], 16) for c in CALL_RE.findall(text)) - {a})
        info[a] = dict(role=role, text=text, calls=calls, nl=nl)
    # features: leaf roles from their own text; Draw/Select from callees
    feat = {}
    for a, d in info.items():
        if d['role'] in ('Span', 'SpanP', 'SpanR', 'Edge', 'EdgeSetup', 'Grad'):
            feat[a] = features(d['text'])
    for a, d in info.items():
        if d['role'] in ('Draw', 'Select'):
            fs, bpps = [], set()
            for c in d['calls']:
                if c in feat:
                    b, f = feat[c]
                    fs += f
                    if b: bpps.add(b)
            if not fs:
                b, f = features(d['text']); fs = f
            if re.search(r'\+ 0x330\)|\+ 0x348\)', d['text']) and 'Lit' not in fs:
                fs.append('Lit')
            fs = [x for x in ['Tex', 'Flat', 'Lit', 'Key', 'Z', 'Zw'] if x in fs]
            if 'Tex' in fs and 'Flat' in fs: fs.remove('Flat')
            feat[a] = (bpps.pop() if len(bpps) == 1 else None, fs)
    counters = collections.Counter()
    out = []
    for a in sorted(info):
        d = info[a]; b, fs = feat[a]
        base = 'rdRaster_%s%s_%s' % (d['role'], b or '', ''.join(fs) or 'Plain')
        counters[base] += 1
        name = base if counters[base] == 1 else '%s_%d' % (base, counters[base])
        callees = ', '.join('%08x' % c for c in d['calls'])
        cm = ('Software rasterizer variant (auto-classified from the decompilation: %s%s). ' % (d['role'], ' ' + ' '.join(fs) if fs else '')
              + ('Calls ' + callees + '. ' if callees else '')
              + 'Grimjedi RDroid Rdraster; verify the exact pixel format before relying on the suffix.')
        out.append({'addr': '%08x' % a, 'name': name, 'comment': cm, 'tags': 'rdroid,raster,auto'})
    # second pass: rename the _1 to be stable (first of a class keeps the base name)
    print('classified', len(out))
    print(collections.Counter(re.sub(r'_\d+$', '', o['name']) for o in out).most_common(60))
    if not dry:
        json.dump(out, open(os.path.join(ROOT, 'names', 'exe_raster_auto.json'), 'w', newline="\n"), indent=0)


main()
