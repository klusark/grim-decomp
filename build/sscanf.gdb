set pagination off
run
thread 1
p (int)sscanf("2.5 7 abc", "%f %d %s", $esp-256, $esp-240, $esp-224)
x/f $esp-256
x/dw $esp-240
x/s $esp-224
p (int)sscanf("1.25", "%f", $esp-256)
x/f $esp-256
