"""In-process-free sampling profiler for the 32-bit game: suspends every thread of PID repeatedly,
reads EIP (+ ebp-chain callers), aggregates by symbol from `nm` of the rebuilt images.
usage: python -I sampler.py PID seconds [interval_ms] [rundir]"""
import ctypes, ctypes.wintypes as w, sys, time, subprocess, bisect, collections, struct, os, re
k=ctypes.WinDLL('kernel32',use_last_error=True)
PID=int(sys.argv[1]); DUR=float(sys.argv[2]); IV=float(sys.argv[3])/1000 if len(sys.argv)>3 else 0.001
RUN=sys.argv[4] if len(sys.argv)>4 else r'C:\Users\Joel\grim-agentC\build\run'
TH32CS_SNAPTHREAD=4; TH32CS_SNAPMODULE=8; TH32CS_SNAPMODULE32=0x10
class TE(ctypes.Structure): _fields_=[("sz",w.DWORD),("u",w.DWORD),("tid",w.DWORD),("owner",w.DWORD),("pri",w.LONG),("dpri",w.LONG),("fl",w.DWORD)]
class ME(ctypes.Structure): _fields_=[("sz",w.DWORD),("mid",w.DWORD),("pid",w.DWORD),("gu",w.DWORD),("pu",w.DWORD),("base",ctypes.c_void_p),("size",w.DWORD),("h",w.HANDLE),("name",ctypes.c_char*256),("path",ctypes.c_char*260)]
k.OpenThread.restype=w.HANDLE; k.OpenProcess.restype=w.HANDLE
def threads():
    s=k.CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD,0); te=TE(); te.sz=ctypes.sizeof(te); out=[]
    ok=k.Thread32First(s,ctypes.byref(te))
    while ok:
        if te.owner==PID: out.append(te.tid)
        ok=k.Thread32Next(s,ctypes.byref(te))
    k.CloseHandle(s); return out
def modules(all_=False):
    s=k.CreateToolhelp32Snapshot(TH32CS_SNAPMODULE|TH32CS_SNAPMODULE32,PID); me=ME(); me.sz=ctypes.sizeof(me); out={}
    ok=k.Module32First(s,ctypes.byref(me))
    while ok:
        out[me.name.decode().lower()]=(me.base or 0,me.size); ok=k.Module32Next(s,ctypes.byref(me))
    k.CloseHandle(s); return out
mods=modules()
allmods=sorted((b,n) for n,(b,sz) in mods.items())
def modname(a):
    i=bisect.bisect_right([b for b,_ in allmods],a)-1
    return allmods[i][1] if i>=0 and a<allmods[i][0]+mods[allmods[i][1]][1] else '?'

syms={}
def load(name,exe):
    base=mods.get(name,(None,))[0]
    if base is None: return
    pe=os.path.join(RUN,name)
    out=subprocess.run(['nm','-n','--defined-only',pe],capture_output=True,text=True).stdout
    # nm for a PE reports link addresses (preferred base); subtract the preferred base, add the real one
    ib=int(re.search(r'ImageBase\s+([0-9a-f]+)',subprocess.run(['objdump','-p',pe],capture_output=True,text=True).stdout).group(1),16)
    L=[]
    for line in out.splitlines():
        p=line.split()
        if len(p)==3 and p[1] in 'TtDdBb' :
            L.append((int(p[0],16)-ib+base,p[2].lstrip('_') if p[2].startswith('_') else p[2]))
    L.sort(); syms[name]=(base,mods[name][1],[a for a,_ in L],[n for _,n in L])
for n in ('grimfandango.exe','lua.dll','imuse.dll','chore.dll'): load(n,0)
CSYMS=set()
for p in ('GRIMFANDANGO.EXE','LUA.DLL','IMUSE.DLL','CHORE.DLL'):
    try: CSYMS|=set(open(os.path.join(os.path.dirname(os.path.abspath(__file__)),'csyms_'+p+'.txt')).read().split())
    except OSError: pass
def tag(n):
    b=re.sub(r'@\d+$','',n.lstrip('@'))
    return ('C  ' if (b in CSYMS or n in CSYMS) else 'asm')+' '+n
def sym(a):
    for n,(b,sz,A,N) in syms.items():
        if b<=a<b+sz:
            i=bisect.bisect_right(A,a)-1
            return N[i] if i>=0 else n+'+?'
    return '<ext>'
hp=k.OpenProcess(0x1F0FFF,False,PID)
CTX=ctypes.create_string_buffer(716)
def ctx(h):
    struct.pack_into('<I',CTX,0,0x10007)  # CONTEXT_i386|CONTROL|INTEGER
    if not k.Wow64GetThreadContext(h,CTX): return None
    return struct.unpack_from('<I',CTX,184)[0],struct.unpack_from('<I',CTX,180)[0],struct.unpack_from('<I',CTX,196)[0]
def rd(a):
    b=ctypes.create_string_buffer(8); n=ctypes.c_size_t()
    if k.ReadProcessMemory(hp,ctypes.c_void_p(a),b,8,ctypes.byref(n)) and n.value==8: return struct.unpack('<II',b.raw)
    return None
tids=threads()
hs={t:k.OpenThread(0x1FFFFF,False,t) for t in tids}
extcaller=collections.Counter(); ext=collections.Counter(); thn=collections.Counter(); self_c=collections.Counter(); incl=collections.Counter(); perth=collections.Counter(); N=0
end=time.time()+DUR
while time.time()<end:
    for t,h in hs.items():
        if k.SuspendThread(h)==0xFFFFFFFF: continue
        c=ctx(h)
        chain=[]
        if c:
            eip,ebp,esp=c; chain=[eip]
            for _ in range(8):
                r=rd(ebp) if ebp else None
                if not r or r[0]<=ebp or r[0]-ebp>0x10000: break
                chain.append(r[1]); ebp=r[0]
        k.ResumeThread(h)
        if not chain: continue
        s0=sym(chain[0]); perth[t]+=1
        if s0=='<ext>' :
            ext[(t,modname(chain[0]))]+=1
            b=ctypes.create_string_buffer(512); n=ctypes.c_size_t()
            if k.ReadProcessMemory(hp,ctypes.c_void_p(esp),b,512,ctypes.byref(n)):
                for v in struct.unpack('<128I',b.raw):
                    if syms['grimfandango.exe'][0]<=v<syms['grimfandango.exe'][0]+syms['grimfandango.exe'][1]:
                        extcaller[(modname(chain[0]),sym(v))]+=1; break
            continue
        thn[t]+=1
        N+=1; self_c[s0]+=1
        seen=set()
        for a in chain:
            s=sym(a)
            if s not in seen and s!='<ext>': seen.add(s); incl[s]+=1
    time.sleep(IV)
print('samples (non-system):',N,' per thread',dict(perth))
print('game-code samples per thread',dict(thn))
print('--- system-module samples of busiest game threads (module)')
busy=[t for t,_ in thn.most_common(2)]
for (t,m),c in ext.most_common(400):
    if t in busy: print('  tid',t,m,c)
print('--- system samples: nearest game-code return address on the stack')
for (m,sy),c in extcaller.most_common(12): print('  ',m,sy,c)
print('--- self'); 
for s,c in self_c.most_common(40): print('%5.1f%% %s'%(100*c/N,tag(s)))
print('self time in C-compiled functions: %.1f%%, asm: %.1f%%'%(100*sum(c for s,c in self_c.items() if tag(s).startswith('C'))/N,100*sum(c for s,c in self_c.items() if not tag(s).startswith('C'))/N))
print('--- inclusive (ebp chain, approximate)')
for s,c in incl.most_common(30): print('%5.1f%% %s'%(100*c/N,tag(s)))
