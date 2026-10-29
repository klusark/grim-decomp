# gdb -batch -x build/calltrace.gdb --args <exe>
# Prints the name of every engine function entered (breakpoints on the main
# prefixes), one per line, until the program ends; the last lines before an
# early exit show where initialisation gave up.
python
import gdb
gdb.execute('set pagination off')
gdb.execute('rbreak ^(Grim_|Engine_|Render_|Resource_|Res_|Lua_Init|Lua_Run|Lua_Open|Display_|DDraw_|D3D_|Services_|Set_Load|Set_SetCurrent|Sound_|Movie_|Control_|Input_|Timer_|Config_|Polyglot_|Mem_Init|Pool_Create|LAB_File|Resource)')
gdb.execute('run')
last = None
for i in range(3000):
    try:
        f = gdb.newest_frame()
        name = f.name() or '?'
    except gdb.error:
        break
    if 'ZwClose' in name or 'NtClose' in name:
        gdb.execute('return')
        gdb.execute('set $eax = 0')
        gdb.execute('signal 0')
        continue
    if name != last:
        print('>>', name)
        last = name
    try:
        gdb.execute('continue')
    except gdb.error:
        break
end
