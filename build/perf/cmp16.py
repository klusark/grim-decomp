import struct
d=open('C:/Users/Joel/agentC_dib.bin','rb').read(); r=open('C:/Users/Joel/agentC_cmp.png.raw','rb').read()
W,H=640,477
def e(v,b): return (v<<(8-b))|(v>>(2*b-8))
bad=0;maxd=0;tot=0
for y in range(H):
    for x in range(W):
        p=struct.unpack_from('<H',d,(y*640+x)*2)[0]
        exp=(e((p>>11)&31,5),e((p>>5)&63,6),e(p&31,5))
        i=(y*W+x)*4; got=(r[i+2],r[i+1],r[i])
        dd=max(abs(a-b) for a,b in zip(exp,got)); tot+=1
        if dd: bad+=1; maxd=max(maxd,dd)
print('pixels differing from replicate-expansion: %d / %d, max channel diff %d'%(bad,tot,maxd))
