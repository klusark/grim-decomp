set pagination off
break Grim_Init
run
finish
p $eax
break Engine_CallSystemFunction
break Engine_RunSystemScript
