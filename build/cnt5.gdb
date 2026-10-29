set pagination off
set environment _NO_DEBUG_HEAP=1
break FUN_004c2a70
break FUN_004c2a80
commands 1
silent
python
n=globals().get('A',0)+1; globals()['A']=n
if n<=5 or n%100==0: print('cb2a70',n)
gdb.execute('continue')
end
end
commands 2
silent
python
n=globals().get('B',0)+1; globals()['B']=n
if n<=5 or n%100==0: print('cb2a80',n)
gdb.execute('continue')
end
end
run
