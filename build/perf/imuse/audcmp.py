import sys
a=open(sys.argv[1]).read().split('\n')[:-1]; b=open(sys.argv[2]).read().split('\n')[:-1]
n=min(len(a),len(b)); d=[i for i in range(n) if a[i]!=b[i]]
print("lines",len(a),len(b),"common",n,"differ",len(d),"first",d[:3])
if d: print(a[d[0]],'|',b[d[0]])
