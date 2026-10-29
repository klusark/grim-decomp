python
import gdb
gdb.execute('set pagination off')
gdb.Breakpoint('Display_Select'); gdb.execute('run')
last = None
for i in range(400):
    try:
        f = gdb.selected_frame()
        if f.name() != 'Display_Select': break
        print('>> line', f.find_sal().line)
        gdb.execute('next', to_string=True)
    except gdb.error as e:
        print('>>', e); break
end
