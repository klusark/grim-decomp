set pagination off
set environment _NO_DEBUG_HEAP=1
run
thread 1
p (unsigned)g_pDirectSound
p (unsigned)PTR_1002d83c
p (int)DAT_1002d840
bt 1
kill
