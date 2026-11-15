# twinsrc.py <src module.c> <out.c> [names...]: the module with the generated twins of the named (or, with no names, all)
# hand-written functions switched on (#if 0 -> #if 1); prints the names switched on
import re, sys

t = open(sys.argv[1], encoding='utf-8').read()
names = set(sys.argv[3:])
on = []


def twin_name(b):
    b = re.sub(r'/\*.*?\*/', '', b, flags=re.S)
    b = re.sub(r'\n\s*\n', '\n', b)
    m = re.search(r'^[A-Za-z_][^;{]*?\b(\w+)\s*\(', b, re.M)
    return m.group(1) if m else '?'


def rep(m):
    n = twin_name(m.group(2))
    if not names or n in names:
        on.append(n)
        return m.group(1) + '#if 1\n' + m.group(2)
    return m.group(0)


t2 = re.sub(r'(replaced by the hand-written version in build/overrides[^\n]*\*/\n)#if 0\n((?:(?!\n#endif).)*)', rep, t, flags=re.S)
open(sys.argv[2], 'w', encoding='utf-8', newline='\n').write(t2)
print('twins on:', ' '.join(on))
