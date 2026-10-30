r"""Broader behavioural check: set changes through the game's own set switcher, a fullscreen movie, Save/Load.
usage: python -I soak.py <exe-dir> <tag> [ref-tag]   (shots agentC_soak_<tag>_<n>.png.raw; stats against ref-tag's shots)"""
import subprocess, time, os, sys
D=r'C:\Users\Joel'
exe,tag=sys.argv[1],sys.argv[2]; ref=sys.argv[3] if len(sys.argv)>3 else None
here=os.path.dirname(os.path.abspath(__file__)); HERE=here.replace(chr(92),'/')
subprocess.run(['bash',HERE+'/ctl.sh','stop'])
env=dict(os.environ, GRIM_MULTI='agentC', GRIM_ACTIVE='1', GRIM_NOMOVIE='0', GRIM_LUA_FILE=D+r'\agentC_cmd.lua', GRIM_LUA_LOG=D+r'\agentC_log.txt', _NO_DEBUG_HEAP='1', GRIM_PERFLOG='1')
del env['GRIM_NOMOVIE']   # movies on (the knob zeroes them when merely set)
open(D+r'\agentC_cmd.lua','w').close()
try: os.remove(D+r'\agentC_log.txt')
except OSError: pass
p=subprocess.Popen([exe+r'\grimfandango.exe'],cwd=r'C:\GOG Games\GRIMDATA',env=env,stdout=subprocess.DEVNULL,stderr=subprocess.DEVNULL)
def log():
    try: return open(D+r'\agentC_log.txt',errors='replace').read()
    except OSError: return ''
def cmd(s): open(D+r'\agentC_cmd.lua','a').write(s+'\n')
def wait(pat,timeout):
    t=time.time()
    while time.time()-t<timeout:
        if pat in log(): return True
        if p.poll() is not None: return False
        time.sleep(0.2)
    return False
def shot(name):
    out=D+r'\agentC_soak_%s_%s.png'%(tag,name)
    subprocess.run([sys.executable,'-I',here+r'\shot.py',out],capture_output=True)
    return D+r'\agentC_soak_%s_%s.png.raw'%(tag,name)
def stats(a,b):
    if not (os.path.exists(a) and os.path.exists(b)): return 'missing shot'
    A=open(a,'rb').read(); B=open(b,'rb').read()
    big=sum(1 for i in range(0,len(A),4) if max(abs(A[i]-B[i]),abs(A[i+1]-B[i+1]),abs(A[i+2]-B[i+2]))>24)
    return '%.2f%% pixels differ >24'%(100*big/(len(A)//4))
res=[]; fail=False
# the intro cutscene plays by itself when movies are on: skip it with the set switcher once the hook is live
wait('lua hook active',60)
cmd('function T(n) local s=system.setTable[n] s:switch_to_set() grimlog("SW "..n) end')
sets=["mo.set","ha.set","ga.set","bi.set","lr.set","mx.set","ce.set","do.set","hf.set","sh.set","vd.set","tu.set"]
cmd('soak_list = {'+','.join('"%s"'%s for s in sets)+'}')
cmd('function SoakRun() local i=1 while soak_list[i] do T(soak_list[i]) sleep_for(2500) i=i+1 end grimlog("SOAKDONE") end')
cmd('start_script(SoakRun)')
t0=time.time()
for i,s in enumerate(sets):
    if not wait('SW '+s,30): res.append('set %s never reached'%s); fail=True; break
    time.sleep(2.0)
    if p.poll() is not None: break
    r=shot('set%02d'%i)
    if ref: res.append('%s: %s'%(s,stats(r,r.replace('soak_'+tag,'soak_'+ref))))
res.append('set tour %.1fs'%(time.time()-t0))
if not fail:
    cmd('function SoakMov() StartFullscreenMovie("funny.snm") while IsMoviePlaying() do break_here() end grimlog("MOVIEDONE") end')
    cmd('start_script(SoakMov)')
    time.sleep(4); r=shot('movie1')
    if ref: res.append('movie frame: %s'%stats(r,r.replace('soak_'+tag,'soak_'+ref)))
    ok=wait('MOVIEDONE',120); res.append('movie finished: %s'%ok); fail|=not ok
    cmd('zz=5')
    cmd('Save("agentC_soak.gsv")'); time.sleep(4)
    cmd('zz=7'); time.sleep(0.5)
    cmd('Load("agentC_soak.gsv")')
    time.sleep(5); cmd('grimlog("ZZ="..tostring(zz))'); time.sleep(1.5)
    z=[l for l in log().splitlines() if l.startswith('ZZ=')]
    res.append('save/load: '+(z[-1] if z else 'no ZZ'))
    if not z or z[-1]!='ZZ=5': fail=True
errs=[l for l in log().splitlines() if l.startswith('rc=') and not l.startswith('rc=0')]
res.append('lua errors: %d %s'%(len(errs),errs[:2]))
if p.poll() is not None: res.append('PROCESS DIED rc=%s'%p.returncode); fail=True
else: subprocess.run(['bash',HERE+'/ctl.sh','stop'])
print(('FAIL ' if fail else 'OK ')+tag); print('\n'.join(res))
