"""twinsrc.py <src/<prog>/<module>.c> <out.c> [names...]

Writes a source file holding only the GENERATED TWINS of hand-written functions of the module: the module's header (its
#includes) and, of every function section (`/* ---- 0x<addr>  <name> ---- */`) whose code build_src.py put under
`#if 0` because build/overrides*.c defines it by hand, the ones named (all of them when no name is given) with the
`#if 0` switched on.  Everything else of the module stays out: the test links the module's object of the current build
next to it, so a twin's calls to the other functions of its module go through the linker (an assembler binds a call to
a function of the same object file directly, past the test's recorders).  Prints the twins written."""
import re
import sys

src, out = sys.argv[1], sys.argv[2]
names = set(sys.argv[3:])
text = open(src, encoding='utf-8').read()
parts = re.split(r'(?m)^(?=/\* ---- 0x[0-9a-f]+  \S+ ---- \*/)', text)
head, sections = parts[0], parts[1:]
on = []
body = []
for s in sections:
    name = re.match(r'/\* ---- 0x[0-9a-f]+  (\S+) ---- \*/', s).group(1)
    m = re.search(r'replaced by the hand-written version in build/overrides[^\n]*\*/\n#if 0\n', s)
    if not m or (names and name not in names):
        continue
    on.append(name)
    body.append(s[:m.end() - len('#if 0\n')] + '#if 1\n' + s[m.end():])
open(out, 'w', encoding='utf-8', newline='\n').write(head + ''.join(body))
missing = names - set(on)
print('twins on:', ' '.join(on) + ('   (no twin: %s)' % ' '.join(sorted(missing)) if missing else ''))
