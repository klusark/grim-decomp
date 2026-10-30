r"""Frame time per set: switches through a list of sets (movies off), averages the in-process perf log lines of each dwell.
usage: python -I benchsets.py <exe-dir> [k=v env ...]   e.g. GRIM_SLOWFLIP=1"""
import subprocess, time, os, sys, re, statistics
D=r'C:\Users\Joel'
exe=sys.argv[1]
here=os.path.dirname(os.path.abspath(__file__)); HERE=here.replace(chr(92),'/')
subprocess.run(['bash',HERE+'/ctl.sh','stop'])
env=dict(os.environ, GRIM_MULTI='agentC', GRIM_ACTIVE='1', GRIM_NOMOVIE='1', GRIM_LUA_FILE=D+r'\agentC_cmd.lua', GRIM_LUA_LOG=D+r'\agentC_log.txt', _NO_DEBUG_HEAP='1', GRIM_PERFLOG='1')
for a in sys.argv[2:]:
    k,v=a.split('=',1); env[k]=v
open(D+r'\agentC_cmd.lua','w').close()
try: os.remove(D+r'\agentC_log.txt')
except OSError: pass
p=subprocess.Popen([exe+r'\grimfandango.exe'],cwd=r'C:\GOG Games\GRIMDATA',env=env,stdout=subprocess.DEVNULL,stderr=subprocess.DEVNULL)
def log():
    try: return open(D+r'\agentC_log.txt',errors='replace').read().splitlines()
    except OSError: return []
def cmd(s): open(D+r'\agentC_cmd.lua','a').write(s+'\n')
while not any('lua hook active' in l for l in log()): time.sleep(0.2)
cmd('function T(n) local s=system.setTable[n] s:switch_to_set() grimlog("SW "..n) end')
sets=["mo.set","ha.set","ga.set","bi.set","lr.set","mx.set","ce.set","do.set","hf.set","sh.set","vd.set","tu.set","mo.set"]
tot=[]
for s in sets:
    cmd('T("%s")'%s)
    while not any(l=='SW '+s for l in log()[-200:]): time.sleep(0.1)
    time.sleep(1.0); n0=len(log()); time.sleep(3.0)
    L=[l for l in log()[n0:] if l.startswith('perf')]
    ms=[float(re.search(r'([\d.]+) ms/frame',l).group(1)) for l in L]
    fl=[float(re.search(r'flip (\d+) us',l).group(1)) for l in L]
    if ms:
        print('%-7s %.2f ms/frame (flip %d us)  n=%d'%(s,statistics.median(ms),statistics.median(fl),len(ms))); tot.append(statistics.median(ms))
print('mean of medians: %.3f ms/frame'%(sum(tot)/len(tot)))
subprocess.run(['bash',HERE+'/ctl.sh','stop'])
