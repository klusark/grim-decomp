python
import gdb
gdb.execute('set pagination off')
gdb.execute('run')
gdb.execute('x/12i 0x45ca32')
gdb.execute('info registers eax edx esp ebp')
gdb.execute('x/6wx $ebp+8')
end
