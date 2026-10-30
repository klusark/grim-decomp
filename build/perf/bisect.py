r"""Find the modules that can be compiled at -O2 without changing behaviour (delta-debugging style greedy search).
usage: python -I bisect.py <PROG> [more PROGs...] [--flags "-O2 -fno-omit-frame-pointer"] [--accepted file.mk]
Each trial writes perf/trial.mk, builds into obj_t/, runs check.py quick against the reference tag `base`.
Accepted modules are appended to the result file (default perf/accepted.mk)."""
import subprocess, sys, os, glob, re, shutil, time
HERE=os.path.dirname(os.path.abspath(__file__)); BUILD=os.path.dirname(HERE)
args=sys.argv[1:]
flags="-O2 -fno-omit-frame-pointer"; acc_file=os.path.join(HERE,'accepted.mk'); progs=[]
i=0
while i<len(args):
    if args[i]=='--flags': flags=args[i+1]; i+=2
    elif args[i]=='--accepted': acc_file=args[i+1]; i+=2
    else: progs.append(args[i]); i+=1
SKIP={'crt','crt_unnamed'}
def modules(p): return [os.path.basename(f)[:-2] for f in sorted(glob.glob(os.path.join(BUILD,'..','src',p,'*.c'))) if os.path.basename(f)[:-2] not in SKIP]
def read_acc():
    acc=[]
    if os.path.exists(acc_file):
        for l in open(acc_file):
            m=re.match(r'^OPT_(\S+) :=',l)
            if m: acc.append(m.group(1))
    return acc
def build_and_test(mods):
    with open(os.path.join(HERE,'trial.mk'),'w') as f:
        for m in mods: f.write('OPT_%s := %s\n'%(m,flags))
    env=dict(os.environ); env['PATH']='/ucrt64/bin:'+env['PATH']
    r=subprocess.run(['bash','-c','cd %s && make OBJ=obj_t OPTMK=perf/trial.mk link -j14 2>&1 | grep -c LINKED'%BUILD.replace(chr(92),'/')],capture_output=True,text=True)
    if r.stdout.strip()!='4': return False,'build failed'
    os.makedirs(os.path.join(HERE,'trial'),exist_ok=True)
    for p,n in (('GRIMFANDANGO.EXE','grimfandango.exe'),('LUA.DLL','lua.dll'),('IMUSE.DLL','imuse.dll'),('CHORE.DLL','chore.dll')):
        shutil.copy(os.path.join(BUILD,'obj_t',p,n),os.path.join(HERE,'trial',n))
    r=subprocess.run([sys.executable,'-I',os.path.join(HERE,'check.py'),os.path.join(HERE,'trial'),'trial','base','quick'],capture_output=True,text=True)
    out=r.stdout
    ok=out.startswith('OK')
    bd=[float(x) for x in re.findall(r'differing>24 ([\d.]+)%',out)]
    if len(bd)<2 or max(bd)>0.5: ok=False
    pos=re.search(r'POS (\S+) (\S+)',out)
    if not pos or abs(float(pos.group(2))-1.4)>0.15 or abs(float(pos.group(1))-0.2)>0.15: ok=False
    if 'boot to office' in out:
        t=float(re.search(r'boot to office ([\d.]+)s',out).group(1))
        if t>20: ok=False
    return ok,out.replace('\n',' | ')
def log(*a):
    print(time.strftime('%H:%M:%S'),*a,flush=True)
def add(accepted,chunk):
    ok,out=build_and_test(accepted+chunk)
    log('test +%d modules (%s%s): %s'%(len(chunk),chunk[0],'..' if len(chunk)>1 else '','PASS' if ok else 'FAIL'),'' if ok else out[:200])
    return ok
def search(accepted,chunk):
    """returns the subset of chunk accepted"""
    if not chunk: return []
    if add(accepted,chunk): return list(chunk)
    if len(chunk)==1:
        log('REJECT',chunk[0]); return []
    h=len(chunk)//2
    a=search(accepted,chunk[:h])
    b=search(accepted+a,chunk[h:])
    return a+b
accepted=read_acc()
for p in progs:
    cands=[p+'/'+m for m in modules(p) if p+'/'+m not in accepted]
    log(p,len(cands),'candidates')
    got=search(accepted,cands)
    accepted+=got
    with open(acc_file,'w') as f:
        for m in accepted: f.write('OPT_%s := %s\n'%(m,flags))
    log(p,'accepted',len(got),'of',len(cands),'->',acc_file)
