python
import gdb
gdb.execute('set pagination off')
gdb.execute('run')
gdb.execute('x/8i $pc-20')
gdb.execute('info registers')
end
