# gdb -batch -x build/inittrace.gdb --args <exe>
# Breaks on each step of Grim_Init, runs it to completion with `finish` and
# prints its return value, so the step that makes Grim_Init give up is visible.
python
import gdb
gdb.execute('set pagination off')
steps = ['Grim_ParseCommandLine', 'Services_InitPlatform', 'IMuseModule_Init', 'Polyglot_LoadTable',
         'Grim_OpenRegistry', 'Grim_FindDataOnDrives', 'rdroid_Startup', 'rdroid_Open',
         'Display_EnumDevices', 'Grim_EnumDisplayModes', 'Display_InitFromConfig', 'EngineModule_Init',
         'Resource_OpenArchives', 'Grim_ShowSplash', 'Engine_RunSystemScript', 'Engine_CallSystemFunction',
         'Win_PumpMessages']
for s in steps:
    try:
        gdb.execute('break ' + s)
    except gdb.error:
        print('no symbol', s)
gdb.execute('run')
for i in range(200):
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
    if name in steps:
        print('>> enter', name)
        if name == 'Win_PumpMessages':
            print('>> reached the message loop')
            break
        try:
            gdb.execute('finish')
            print('>> ', name, 'returned eax =', hex(int(gdb.parse_and_eval('$eax')) & 0xffffffff))
        except gdb.error as e:
            print('>> finish failed in', name, e)
            gdb.execute('bt 8')
            break
        try:
            gdb.execute('continue')
        except gdb.error:
            break
        continue
    print('>> stopped in', name)
    gdb.execute('bt 10')
    break
end
