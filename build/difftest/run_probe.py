"""Run probe.lua for many Lua API functions on one build, in parallel game instances.
  python -I run_probe.py <rundir> <outdir> <workers> <func> [<func> ...]      (or @file with names, one per line)
Each function gets a fresh game boot (state cannot leak between functions); the log lands in <outdir>/<func>.log.
Compare two builds with:  diff -r <outdirA> <outdirB>
"""
import os,subprocess,sys,threading,queue,shutil
HERE=os.path.dirname(os.path.abspath(__file__)).replace(chr(92),'/')
run=os.path.abspath(sys.argv[1]).replace(chr(92),'/'); out=os.path.abspath(sys.argv[2]); n=int(sys.argv[3])
funcs=[]
for a in sys.argv[4:]:
    if a.startswith('@'): funcs+=[l.strip() for l in open(a[1:]) if l.strip()]
    else: funcs.append(a)
os.makedirs(out,exist_ok=True)
q=queue.Queue()
for f in funcs: q.put(f)
def worker(k):
    tag=os.environ.get('TAGPFX','pw')+str(k)
    dd='C:/Users/Joel/grim-agentI-data-'+tag
    if not os.path.isdir(dd):
        subprocess.run(['bash',HERE+'/../../tools/mkmoddir.sh',dd],capture_output=True)
    while True:
        try: f=q.get_nowait()
        except queue.Empty: return
        open(dd+'/probe_cfg.lua','w').write('PROBE_FUNC = "%s"\n'%f)
        for old in ('grim_crash_%s.txt'%tag,):
            try: os.remove(dd+'/'+old)
            except OSError: pass
        o='%s/%s.log'%(out,f)
        for attempt in range(3):   # a boot occasionally fails when several instances start together
            r=subprocess.run(['bash',HERE+'/run_lua.sh',run,tag,HERE+'/probe.lua',o,'60'],capture_output=True,text=True)
            if 'boot failed' not in r.stdout: break
        crash=dd+'/grim_crash_%s.txt'%tag
        if os.path.exists(crash):
            with open(o,'a') as fh: fh.write('CRASH '+open(crash).readline())
        print(f,r.stdout.strip().splitlines()[-1] if r.stdout.strip() else r.stderr[-200:],flush=True)
ts=[threading.Thread(target=worker,args=(k,)) for k in range(n)]
[t.start() for t in ts]; [t.join() for t in ts]
