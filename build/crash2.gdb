python
import gdb
gdb.execute('set pagination off')
gdb.execute('run')
gdb.execute('frame 1')
gdb.execute('info locals')
gdb.execute('p/x *(int*)pvVar1@6')
gdb.execute('p/x ResType_DefaultHandler')
gdb.execute('x/6i $pc')
gdb.execute('x/12i 0x548630')
end
