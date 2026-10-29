set pagination off
break EngineModule_Init
run
finish
p/x *(int*)&UINT_008dde28
info symbol *(int*)&UINT_008dde28
