set pagination off
set environment _NO_DEBUG_HEAP=1
run
thread 1
python
import gdb
for h in (6, 7):
    print('>> handle', h, 'chores', gdb.parse_and_eval('(int)Cos_InstCountChores(%d)' % h))
    for i in (0, 1, 2, 8, 22, 23, 33):
        try:
            print('>>   ', h, i, gdb.parse_and_eval('(char*)Cos_InstChoreName(%d, %d)' % (h, i)), 'status', gdb.parse_and_eval('(int)Cos_InstChoreStatus(%d, %d)' % (h, i)))
        except Exception as e:
            print('>> err', e)
end
kill
