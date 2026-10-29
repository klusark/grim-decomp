import gdb, threading, time, os, collections
N=int(os.environ.get('N','40')); GAP=float(os.environ.get('GAP','0.15'))
agg=collections.Counter()
def kicker():
    for i in range(N):
        time.sleep(GAP); gdb.interrupt()
        while not stopped.is_set(): time.sleep(0.005)
        stopped.clear()
        # main thread resumes via main-loop continue
stopped=threading.Event()
res=[]
th=threading.Thread(target=kicker,daemon=True)
def sample():
    try:
        gdb.execute('thread 1',to_string=True)
        fr=gdb.newest_frame(); names=[]
        for k in range(12):
            if fr is None: break
            names.append(fr.name() or '?'); fr=fr.older()
        res.append(names)
    except gdb.error as e: res.append(['err '+str(e)])
th.start()
for i in range(N):
    try: gdb.execute('continue',to_string=True)
    except gdb.error as e: pass
    sample(); stopped.set()
for names in res:
    print(' <- '.join(names[:9]))
gdb.execute('detach'); gdb.execute('quit')
