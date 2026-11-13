"""usage: python -I boot.py <exe-dir> [k=v env ...]: launch the game, report seconds until the Lua hook is live and until Manny's set exists."""
import subprocess, time, os, sys
D=r'C:\Users\Joel'
exe=sys.argv[1]
env=dict(os.environ, GRIM_MULTI='agentC', GRIM_NOMOVIE='1', GRIM_LUA_FILE=D+r'\agentC_cmd.lua', GRIM_LUA_LOG=D+r'\agentC_log.txt', _NO_DEBUG_HEAP='1', GRIM_PERFLOG='1')
for a in sys.argv[2:]:
    k,v=a.split('=',1); env[k]=v
open(D+r'\agentC_cmd.lua','w').close()
try: os.remove(D+r'\agentC_log.txt')
except OSError: pass
t0=time.time()
p=subprocess.Popen([exe+r'\grimfandango.exe'],cwd=r'C:\GOG Games\GRIMDATA',env=env,stdout=subprocess.DEVNULL,stderr=subprocess.DEVNULL)
hook=None
while time.time()-t0<180:
    try: log=open(D+r'\agentC_log.txt',errors='replace').read()
    except OSError: log=''
    if hook is None and 'lua hook active' in log: hook=time.time()-t0
    if hook is not None:
        open(D+r'\agentC_cmd.lua','a').write('if manny and GetCurrentSet and GetCurrentSet() then grimlog("OFFICE") end\n')
    if 'OFFICE' in log:
        print('hook live %.1fs, office %.1fs'%(hook,time.time()-t0)); break
    time.sleep(0.2)
else: print('timeout')
print('pid',p.pid)
