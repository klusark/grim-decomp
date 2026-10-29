python
import gdb
gdb.execute('set pagination off')
gdb.execute('run')
gdb.execute('x/14i $pc-40')
gdb.execute('info registers eax ebx ecx edx esi edi esp ebp')
end
