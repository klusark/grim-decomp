"""Compare two probe output directories (run_probe.py) with a numeric tolerance (Manny's idle animation moves screen-space
and visibility values slightly between runs).  Prints the first differing line pairs per function.
  python -I cmpprobe.py A B [--nosnap] [--only f1,f2] [--tol 0.02]"""
import os,re,sys
num=re.compile(r"-?\d+(?:\.\d+)?(?:e[+-]?\d+)?")
REL=1e-3
def same(x,y,tol=0.02):
    if x.startswith('CRASH') and y.startswith('CRASH'): return True       # addresses differ between builds
    if x==y: return True
    nx,ny=num.findall(x),num.findall(y)
    if num.sub('#',x)!=num.sub('#',y) or len(nx)!=len(ny): return False
    for p,q in zip(nx,ny):
        p,q=float(p),float(q)
        if abs(p-q)>max(tol,abs(p)*REL,4 if (p==int(p) and q==int(q) and abs(p)>20) else 0): return False
    return True
def compare(a,b,nosnap=False,only=None,tol=0.02,verbose=False):
    """-> {function: [(line,A,B),...]} for the functions that differ"""
    res={}
    for f in sorted(os.listdir(a)):
        if not f.endswith('.log'): continue
        if only and f[:-4] not in only: continue
        p=os.path.join(b,f)
        if not os.path.exists(p): res[f[:-4]]=[(0,'missing','')]; continue
        A=open(os.path.join(a,f),errors='replace').read().splitlines(); B=open(p,errors='replace').read().splitlines()
        if len(A)<=2 or len(B)<=2:
            res[f[:-4]]=[(0,'boot failure','A' if len(A)<=2 else 'B')]; continue
        if nosnap: A=[l for l in A if not l.startswith('SNAP')]; B=[l for l in B if not l.startswith('SNAP')]
        d=[(i,x,y) for i,(x,y) in enumerate(zip(A,B)) if not same(x,y,tol)]
        if len(A)!=len(B) or d: res[f[:-4]]=d or [(0,'length','%d/%d'%(len(A),len(B)))]
    return res
if __name__=='__main__':
    a,b=sys.argv[1],sys.argv[2]
    only=sys.argv[sys.argv.index('--only')+1].split(',') if '--only' in sys.argv else None
    tol=float(sys.argv[sys.argv.index('--tol')+1]) if '--tol' in sys.argv else 0.02
    r=compare(a,b,'--nosnap' in sys.argv,only,tol)
    for f,d in r.items():
        print('==',f,'ndiff',len(d))
        for i,x,y in d[:3]: print('  A:',str(x)[:200]); print('  B:',str(y)[:200])
    print(len(r),'functions differ')
