import sys, hashlib
g = {}
for f in sys.argv[1:]:
    h = hashlib.md5(open(f, 'rb').read()).hexdigest()[:8]
    g.setdefault(h, []).append(f.replace('aud_', '').replace('.txt', ''))
for h, fs in sorted(g.items(), key=lambda x: -len(x[1])): print(h, len(fs), ' '.join(fs))
