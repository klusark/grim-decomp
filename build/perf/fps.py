import gdb, threading, time, os
DUR=float(os.environ.get('DUR','10'))
funcs=os.environ.get('FUNCS','Engine_RenderFrame,Display_Flip').split(',')
cnt={}
class B(gdb.Breakpoint):
    def __init__(s,f):
        super().__init__(f,internal=True); s.f=f; cnt[f]=0
    def stop(s):
        cnt[s.f]+=1; return False
for f in funcs: B(f)
def kicker():
    time.sleep(DUR); gdb.interrupt()
threading.Thread(target=kicker,daemon=True).start()
t0=time.time()
try: gdb.execute('continue')
except gdb.error as e: print(e)
dt=time.time()-t0
for f in funcs: print('RESULT %s calls=%d  %.2f/s  %.2f ms'%(f,cnt[f],cnt[f]/dt,1000*dt/max(1,cnt[f])))
gdb.execute('detach')
gdb.execute('quit')
