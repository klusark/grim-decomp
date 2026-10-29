set pagination off
set environment _NO_DEBUG_HEAP=1
run
thread 1
p (int)g_nInputAcquired
p (unsigned)g_pDInputKeyboard
p (unsigned)g_pDirectInput
p (int)UINT_00805fa0
p (unsigned)g_pDInputMouse
kill
