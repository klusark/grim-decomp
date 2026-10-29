python
import gdb
gdb.execute('set pagination off')
gdb.execute('run')
gdb.execute('x/12i 0x9ccce8')
gdb.execute('x/8wx 0x9ccd00')
end
