r"""usage: python -I longsoak.py <exe-dir> <seconds>: cycles through 40 sets with movies in between; reports progress and whether it survived"""
import subprocess, time, os, sys
D=r'C:\Users\Joel'; exe=sys.argv[1]; dur=float(sys.argv[2])
here=os.path.dirname(os.path.abspath(__file__)); HERE=here.replace(chr(92),'/')
subprocess.run(['bash',HERE+'/ctl.sh','stop'])
env=dict(os.environ, GRIM_MULTI='agentC', GRIM_ACTIVE='1', GRIM_LUA_FILE=D+r'\agentC_cmd.lua', GRIM_LUA_LOG=D+r'\agentC_log.txt', _NO_DEBUG_HEAP='1')
env.pop('GRIM_NOMOVIE',None)
open(D+r'\agentC_cmd.lua','w').close()
try: os.remove(D+r'\agentC_log.txt')
except OSError: pass
p=subprocess.Popen([exe+r'\grimfandango.exe'],cwd=r'C:\GOG Games\GRIMDATA',env=env,stdout=subprocess.DEVNULL,stderr=subprocess.DEVNULL)
def log():
    try: return open(D+r'\agentC_log.txt',errors='replace').read().splitlines()
    except OSError: return []
while not any('lua hook active' in l for l in log()): time.sleep(0.2)
open(D+r'\agentC_cmd.lua','a').write(open(here+r'\soak_sets.lua').read())
t0=time.time(); k=0
movies=['funny','ga_in','eledown','hb','lxtop']
while time.time()-t0<dur and p.poll() is None:
    time.sleep(1)
    if int(time.time()-t0)%25==24:
        m=movies[k%5]; k+=1
        open(D+chr(92)+'agentC_cmd.lua','a').write('function SoakMov() StartFullscreenMovie("%s.snm") while IsMoviePlaying() do break_here() end grimlog("MOVIE %s done") end'%(m,m)+chr(10)+'start_script(SoakMov)'+chr(10))
        time.sleep(2)
L=log(); soak=[l for l in L if l.startswith('SOAK')]
errs=[l for l in L if l.startswith('rc=') and not l.startswith('rc=0')]
print('alive' if p.poll() is None else 'DIED rc=%s'%p.returncode, '| last', soak[-1] if soak else 'none', '| lua errors', len(errs), errs[:2])
if p.poll() is None: subprocess.run(['bash',HERE+'/ctl.sh','stop'])
