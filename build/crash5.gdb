python
import gdb
gdb.execute('set pagination off')
gdb.execute('run')
gdb.execute('x/6i 0x43e570')
gdb.execute('info registers eip')
gdb.execute('x/3i *(int*)0x43e578')
end
