set pagination off
break Lua_MakeCurrentSet
run
delete
python
import gdb, struct
inf = gdb.selected_inferior()
p = struct.unpack('<I', bytes(inf.read_memory(int(gdb.parse_and_eval('(int)&PTR_1002bf6c')), 4)))[0]
st = struct.unpack('<I', bytes(inf.read_memory(p + 32, 4)))[0]
gdb.execute('set $slot = %d' % (st + 288))
print('>> st', hex(st))
end
watch *(int*)$slot
commands
silent
printf ">> W %x\n", *(int*)$slot
bt 5
continue
end
break Lua_PutActorAt
commands
python
p = struct.unpack('<I', bytes(inf.read_memory(int(gdb.parse_and_eval('(int)&PTR_1002bf6c')), 4)))[0]
st2 = struct.unpack('<I', bytes(inf.read_memory(p + 32, 4)))[0]
print('>> st at put', hex(st2), 'slot value', [hex(x) for x in struct.unpack('<3I', bytes(inf.read_memory(st2+288, 12)))])
end
end
continue
