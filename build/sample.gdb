set pagination off
python
import gdb, threading, time, os
N = int(os.environ.get('SAMPLES', '6')); GAP = float(os.environ.get('GAP', '3')); FIRST = float(os.environ.get('FIRST', '12'))
def kicker():
    time.sleep(FIRST)
    for i in range(N):
        gdb.interrupt()
        time.sleep(GAP)
threading.Thread(target=kicker, daemon=True).start()
gdb.execute('run')
for i in range(N):
    try:
        t = gdb.selected_inferior().threads()
        f = gdb.selected_thread()
        gdb.execute('thread 1', to_string=True)
        print('>> sample', i, [ (fr.name()) for fr in [gdb.newest_frame()]] , end=' ')
        fr = gdb.newest_frame(); names = []
        for k in range(14):
            if fr is None: break
            names.append(fr.name() or '?'); fr = fr.older()
        print(names)
        gdb.execute('continue &' if False else 'continue', to_string=True)
    except gdb.error as e:
        print('>> err', e); break
end
