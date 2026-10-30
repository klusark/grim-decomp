"""PrintWindow screenshot of the agentC game window -> raw BGRA .bin + sha, optionally .png (needs PIL).
usage: python -I shot.py out.png [title-substring]"""
import ctypes, ctypes.wintypes as w, sys, hashlib, struct, zlib
u=ctypes.windll.user32; g=ctypes.windll.gdi32
title=sys.argv[2] if len(sys.argv)>2 else "Grim Fandango (agentC)"
found=[]
@ctypes.WINFUNCTYPE(w.BOOL,w.HWND,w.LPARAM)
def cb(h,l):
    n=u.GetWindowTextLengthW(h)
    if n:
        b=ctypes.create_unicode_buffer(n+1); u.GetWindowTextW(h,b,n+1)
        if b.value==title: found.append(h)
    return True
u.EnumWindows(cb,0)
if not found: print("no window"); sys.exit(1)
h=found[0]
r=w.RECT(); u.GetClientRect(h,ctypes.byref(r)); W,H=r.right,r.bottom
dc=u.GetDC(h); mdc=g.CreateCompatibleDC(dc); bm=g.CreateCompatibleBitmap(dc,W,H); g.SelectObject(mdc,bm)
u.PrintWindow(h,mdc,3)
class BIH(ctypes.Structure):
    _fields_=[("biSize",w.DWORD),("biWidth",w.LONG),("biHeight",w.LONG),("biPlanes",w.WORD),("biBitCount",w.WORD),("biCompression",w.DWORD),("biSizeImage",w.DWORD),("x",w.LONG),("y",w.LONG),("c",w.DWORD),("i",w.DWORD)]
bi=BIH(40,W,-H,1,32,0,0,0,0,0,0)
buf=ctypes.create_string_buffer(W*H*4)
g.GetDIBits(mdc,bm,0,H,buf,ctypes.byref(bi),0)
raw=bytes(buf)
print(W,H,hashlib.md5(raw).hexdigest())
def png(path):
    rows=b"".join(b"\0"+bytes(sum(([raw[i+2],raw[i+1],raw[i]] for i in range(y*W*4,(y+1)*W*4,4)),[])) for y in range(H))
    def ch(t,d): c=struct.pack(">I",len(d))+t+d; return c+struct.pack(">I",zlib.crc32(t+d)&0xffffffff)
    open(path,"wb").write(b"\x89PNG\r\n\x1a\n"+ch(b"IHDR",struct.pack(">IIBBBBB",W,H,8,2,0,0,0))+ch(b"IDAT",zlib.compress(rows,6))+ch(b"IEND",b""))
png(sys.argv[1])
open(sys.argv[1]+".raw","wb").write(raw)
