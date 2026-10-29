set pagination off
set environment _NO_DEBUG_HEAP=1
break hooked_GetDeviceData
run
python
import gdb
for i in range(60):
    try:
        out = gdb.execute('next', to_string=True)
    except gdb.error as e:
        print('>> err', e); break
    print('>>', out.strip().splitlines()[-1][:120])
    if 'received signal' in out: break
end
