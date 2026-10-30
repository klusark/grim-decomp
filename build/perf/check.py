r"""Regression check of one build dir: boots to the office (movies off), screenshots idle, walks Manny to a fixed spot,
screenshots again; with `movie` also lets the intro cutscene run. Prints OK/FAIL and pixel statistics against reference shots.
usage: python -I check.py <exe-dir> <tag> [ref-tag] [movie]
 shots are saved as C:\Users\Joel\agentC_chk_<tag>_<name>.raw ; with ref-tag the stats compare against that tag's shots."""
import subprocess, time, os, sys, struct
D=r'C:\Users\Joel'
exe,tag=sys.argv[1],sys.argv[2]
ref=sys.argv[3] if len(sys.argv)>3 and sys.argv[3]!='-' else None
movie='movie' in sys.argv[3:]
quick='quick' in sys.argv[3:]
here=os.path.dirname(os.path.abspath(__file__))
HERE=here.replace(chr(92),'/')
subprocess.run(['bash',HERE+'/ctl.sh','stop'])
env=dict(os.environ, GRIM_MULTI='agentC', GRIM_ACTIVE='1', GRIM_LUA_FILE=D+r'\agentC_cmd.lua', GRIM_LUA_LOG=D+r'\agentC_log.txt', _NO_DEBUG_HEAP='1', GRIM_PERFLOG='1')
env.pop('GRIM_NOMOVIE',None)
if not movie: env['GRIM_NOMOVIE']='1'
open(D+r'\agentC_cmd.lua','w').close()
try: os.remove(D+r'\agentC_log.txt')
except OSError: pass
t0=time.time()
p=subprocess.Popen([exe+r'\grimfandango.exe'],cwd=r'C:\GOG Games\GRIMDATA',env=env,stdout=subprocess.DEVNULL,stderr=subprocess.DEVNULL)
def log():
    try: return open(D+r'\agentC_log.txt',errors='replace').read()
    except OSError: return ''
def cmd(s): open(D+r'\agentC_cmd.lua','a').write(s+'\n')
def shot(name):
    out=D+r'\agentC_chk_%s_%s.png'%(tag,name)
    r=subprocess.run([sys.executable,'-I',here+r'\shot.py',out],capture_output=True,text=True)
    return out+'.raw'
def alive(): return p.poll() is None
def stats(a,b):
    if not (os.path.exists(a) and os.path.exists(b)): return 'missing shot'
    A=open(a,'rb').read(); B=open(b,'rb').read()
    if len(A)!=len(B): return 'size differs'
    bad=0; big=0; tot=0
    for i in range(0,len(A),4):
        d=max(abs(A[i]-B[i]),abs(A[i+1]-B[i+1]),abs(A[i+2]-B[i+2]))
        if d: bad+=1
        if d>24: big+=1
    return 'differing %.3f%%, differing>24 %.3f%%'%(100*bad/(len(A)//4),100*big/(len(A)//4))
ok=True
res=[]
if not movie:
    for i in range(300):
        if 'lua hook active' in log() or not alive(): break
        time.sleep(0.1)
    for i in range(100 if not quick else 40):
        if not alive(): break
        cmd('if manny and GetCurrentSet and GetCurrentSet() then grimlog("OFFICE") end')
        time.sleep(0.2)
        if 'OFFICE' in log(): break
    boot=time.time()-t0
    res.append('boot to office %.1fs'%boot)
    time.sleep(5 if not quick else 2)
    if alive(): s1=shot('idle')
    cmd('manny:walkto(0.2,1.6,0)')
    time.sleep(7 if not quick else 5)
    if alive(): s2=shot('walk1')
    if not quick:
        cmd('manny:walkto(1.3,1.6,0)')
        time.sleep(7)
        s3=shot('walk2')
    cmd('x,y,z=GetActorPos(manny.hActor); grimlog("POS "..x.." "..y.." "..z)')
    time.sleep(1)
    pos=[l for l in log().splitlines() if l.startswith('POS')]
    res.append(pos[-1] if pos else 'POS none')
    if ref:
        for n in (('idle','walk1') if quick else ('idle','walk1','walk2')):
            res.append('%s vs %s: %s'%(n,ref,stats(D+r'\agentC_chk_%s_%s.png.raw'%(tag,n),D+r'\agentC_chk_%s_%s.png.raw'%(ref,n))))
else:
    time.sleep(30)
    s1=shot('m30'); time.sleep(30); s1=shot('m60'); time.sleep(25); s1=shot('m85')
    if ref:
        for n in ('m30','m60','m85'):
            res.append('%s vs %s: %s'%(n,ref,stats(D+r'\agentC_chk_%s_%s.png.raw'%(tag,n),D+r'\agentC_chk_%s_%s.png.raw'%(ref,n))))
errs=[l for l in log().splitlines() if l.startswith('rc=') and not l.startswith('rc=0')]
perf=[l for l in log().splitlines() if l.startswith('perf')]
res.append('lua errors: %d'%len(errs))
res.append('last perf: '+(perf[-1] if perf else 'none'))
if not alive(): res.append('PROCESS DIED rc=%s'%p.returncode); ok=False
else: subprocess.run(['bash',HERE+'/ctl.sh','stop'])
print(('OK ' if ok else 'FAIL ')+tag); print('\n'.join(res))
