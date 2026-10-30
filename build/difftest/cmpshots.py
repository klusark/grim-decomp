"""Compare two directories of raw BGRA window shots (run_lua.sh <log>.shots): python -I cmpshots.py A B
Prints per file the percentage of differing pixels and of pixels differing by more than 24 in any channel."""
import os,sys
def compare(a,b,region=None):
    """-> {name: percentage of pixels differing by > 24}"""
    res={}
    for f in sorted(os.listdir(a)):
        if not f.endswith('.raw'): continue
        p=os.path.join(b,f)
        if not os.path.exists(p): res[f[:-8]]=100.0; continue
        A=open(os.path.join(a,f),'rb').read(); B=open(p,'rb').read()
        if len(A)!=len(B): res[f[:-8]]=100.0; continue
        big=0; n=0
        W=640
        for i in range(0,len(A),4):
            if region:
                x=(i//4)%W; y=(i//4)//W
                if not (region[0]<=x<region[2] and region[1]<=y<region[3]): continue
            n+=1
            if A[i:i+3]!=B[i:i+3] and max(abs(A[i]-B[i]),abs(A[i+1]-B[i+1]),abs(A[i+2]-B[i+2]))>24: big+=1
        res[f[:-8]]=100*big/max(n,1)
    return res
if __name__=='__main__':
    r=compare(sys.argv[1],sys.argv[2])
    for k,v in r.items(): print('%-18s >24: %.3f%%'%(k,v))
    print('worst >24: %.3f%%'%max(r.values()))
