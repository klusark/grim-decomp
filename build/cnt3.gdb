set pagination off
set environment _NO_DEBUG_HEAP=1
break GRIM_lua_cmd_poll
commands
silent
python
import gdb
n=globals().get('N',0)+1
globals()['N']=n
if n<=3 or n%200==0: print('poll',n)
gdb.execute('continue')
end
end
run
