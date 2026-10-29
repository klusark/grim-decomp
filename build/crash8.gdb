set pagination off
run
frame 5
p param_1
p (char*)param_1
p/x *(int*)($ebp+16)
p/x *(int*)($ebp+20)
x/s param_2
frame 6
list
