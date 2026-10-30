"""Find the functions whose conversion from assembly to C breaks a test.
  python -I bisect.py <candidates.json> <test.lua> <reference.log> <out.json> [--base base.json]
candidates.json: list of addresses currently to be excluded from assembly (in order). The tool repeatedly finds the
smallest failing prefix, records its last element as a culprit, drops it and continues until the remaining list passes.
Pass = (test 'probe:F1,F2') the probe logs of the named Lua functions equal the reference directory <reference> (ignoring SNAP lines); otherwise the build boots and the test's log equals the reference log (or the reference is '-' : boots and prints DONE).
"""
import json,subprocess,sys,os,shutil
HERE=os.path.dirname(os.path.abspath(__file__)); ROOT=os.path.dirname(os.path.dirname(HERE)).replace(chr(92),'/')
cand=json.load(open(sys.argv[1])); test=sys.argv[2]; ref=sys.argv[3]; outp=sys.argv[4]
base=[]
if '--base' in sys.argv: base=json.load(open(sys.argv[sys.argv.index('--base')+1]))
EXC=ROOT+'/names/asm_exclude_exe_lo.json'
TAG=os.environ.get('BISECT_TAG','ib')
def sh(cmd,**k): return subprocess.run(['bash','-c',cmd],capture_output=True,text=True,**k)
def trial(sub):
    json.dump({"GRIMFANDANGO.EXE":sorted(set(sub)|set(base))},open(EXC,'w'))
    r=sh('bash %s/rebuild.sh'%HERE)
    if 'GRIMFANDANGO.EXE: LINKED' not in r.stdout: print('BUILD FAILED',r.stdout[-800:]); return False
    if test.startswith('suite:'):    # scripted regression tiers of grim_tools/autorun on this clone's build/run_t: 'suite:walk=88,unit=120'
        want=dict(kv.split('=') for kv in test[6:].split(','))
        env_cmd='QT_TAG=I%s REBUILT_DIR=%s/build/run_t sh /c/Users/Joel/grim-agentI/build/qtests.sh %s'%(TAG,ROOT,' '.join(want))
        r=sh(env_cmd)
        ok=True
        for t,n in want.items():
            ok=ok and ('%s: %s pass, 0 fail'%(t,n) in r.stdout)
        return ok
    if test.startswith('probe:'):
        funcs=test[6:].split(',')
        bp=HERE+'/out/bp'
        shutil.rmtree(bp,ignore_errors=True)
        r=sh('python -I %s/run_probe.py %s/build/run_t %s 1 %s'%(HERE,ROOT,bp,' '.join(funcs)))
        sys.path.insert(0,HERE)
        import cmpprobe
        d=cmpprobe.compare(ref,bp,nosnap=True,only=funcs)
        return not d
    o=HERE+'/out/bisect.log'
    if os.path.exists(o): os.remove(o)
    if test.startswith('shot:'):      # reference = directory of reference shots; pass = no shot differs in more than 6% of its pixels
        script=test[5:]
        shutil.rmtree(o+'.shots',ignore_errors=True)
        sh('bash %s/run_lua.sh %s/build/run_t %s %s %s 120'%(HERE,ROOT,TAG,script,o))
        if not os.path.isdir(o+'.shots'): return False
        sys.path.insert(0,HERE)
        import cmpshots
        reg=os.environ.get('BISECT_REGION'); r=cmpshots.compare(ref,o+'.shots',tuple(int(v) for v in reg.split(',')) if reg else None)
        return bool(r) and max(r.values())<float(os.environ.get('BISECT_SHOT_MAX','4.5'))
    r=sh('bash %s/run_lua.sh %s/build/run_t %s %s %s 120'%(HERE,ROOT,TAG,test,o))
    if not os.path.exists(o): return False
    got=open(o,errors='replace').read()
    if 'DONE' not in got or 'GAME EXITED' in got: return False
    if ref!='-':
        want=open(ref,errors='replace').read()
        if os.environ.get('BISECT_TOL'):     # numeric tolerance (absolute, plus 1e-3 relative)
            sys.path.insert(0,HERE)
            import cmpprobe
            cmpprobe.REL=float(os.environ.get('BISECT_REL','1e-3'))
            A=want.splitlines(); B=got.splitlines()
            return len(A)==len(B) and all(cmpprobe.same(x,y,float(os.environ['BISECT_TOL'])) for x,y in zip(A,B))
        return got==want
    return True
bad=[]
cur=list(cand)
if '--noverify' not in sys.argv and not trial([]):
    print('baseline (no function converted) already fails the test: the test is flaky or the reference is stale'); sys.exit(1)
while cur:
    if trial(cur): break
    lo,hi=0,len(cur)   # prefix of length lo passes, hi fails
    while hi-lo>1:
        mid=(lo+hi)//2
        if trial(cur[:mid]): lo=mid
        else: hi=mid
    culprit=cur[hi-1]
    print('culprit',culprit,flush=True)
    bad.append(culprit)
    cur=[a for a in cur if a!=culprit]
    json.dump({'good':cur,'bad':bad},open(outp,'w'))
json.dump({'good':cur,'bad':bad},open(outp,'w'))
print('done; bad =',bad)
