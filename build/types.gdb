python
import gdb, struct
gdb.execute('set pagination off')
b = gdb.Breakpoint('Resource_RegisterTypes')
gdb.execute('run')
gdb.execute('finish')
b.delete()
b = gdb.Breakpoint('Res_LoadInternal'); b.condition = 'type == 1414418246'
gdb.execute('continue')
inf = gdb.selected_inferior()
head = int(gdb.parse_and_eval('(int)UINT_008a85cc'))
print('>> head', hex(head), 'pool', hex(int(gdb.parse_and_eval('(int)UINT_008a85c8'))))
p = head; n = 0
while p and n < 40:
    w = struct.unpack('<4I', bytes(inf.read_memory(p, 16)))
    print('>>  rec %#x next=%#x prev=%#x fourcc=%s handler=%#x' % (p, w[0], w[1], struct.pack('<I', w[2])[::-1], w[3]))
    p = w[0]; n += 1
end
