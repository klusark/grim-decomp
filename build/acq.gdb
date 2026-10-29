set pagination off
set environment _NO_DEBUG_HEAP=1
run
thread 1
set $kb = (void**)*(unsigned*)&g_pDInputKeyboard
p/x ((int(*)(void*))(*(void***)$kb)[7])($kb)
p g_nInputEnabled
p g_nInputAcquired
kill
