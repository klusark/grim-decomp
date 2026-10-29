set pagination off
set breakpoint pending on
python
import gdb, collections, time
hist = collections.Counter(); seq = collections.deque(maxlen=60)
class BP(gdb.Breakpoint):
    def stop(self):
        fn = int(gdb.parse_and_eval('*(int*)($ebp+8)'))
        try: nm = gdb.execute('info symbol %d' % fn, to_string=True).split(' in ')[0].strip()
        except gdb.error: nm = hex(fn)
        hist[nm] += 1; seq.append(nm)
        return False
BP('ldo__44e0')
import threading
def stopper():
    time.sleep(float(__import__('os').environ.get('T','25'))); gdb.post_event(lambda: None)
gdb.execute('run')
print('>> top calls', hist.most_common(15))
print('>> last', list(seq)[-25:])
end
