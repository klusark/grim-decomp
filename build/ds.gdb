set pagination off
break DSound_Init
run
p g_pDirectSound
finish
p $eax
p g_pDirectSound
bt 3
