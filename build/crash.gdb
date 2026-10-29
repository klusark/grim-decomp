# Runs the game and prints the backtrace + registers at the first native fault.
python
import gdb
gdb.execute('set pagination off')
gdb.execute('run')
try:
    print('>> FAULT in', gdb.newest_frame().name())
    gdb.execute('bt 12'); gdb.execute('info registers eip esp ebp eax ecx edx esi edi')
    gdb.execute('x/8wx $esp')
except gdb.error as e:
    print('>> exited', e)
end
