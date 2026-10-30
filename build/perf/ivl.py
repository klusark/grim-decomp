import gdb, time, threading, collections
ts=[]
class B(gdb.Breakpoint):
    def stop(s): ts.append(time.perf_counter()); return False
B('Display_Flip',internal=True)
def kicker(): time.sleep(4); gdb.interrupt()
threading.Thread(target=kicker,daemon=True).start()
try: gdb.execute('continue')
except gdb.error: pass
d=[(b-a)*1000 for a,b in zip(ts,ts[1:])]
h=collections.Counter(round(x*2)/2 for x in d)
print('RESULT n',len(ts),'mean %.2f'%(sum(d)/len(d)),sorted(h.items())[:20])
gdb.execute('detach'); gdb.execute('quit')
