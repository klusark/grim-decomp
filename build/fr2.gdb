set pagination off
break rdModel_DrawMesh
run
p g_pRdCurrentCamera
p &g_pRdCurrentCamera
info symbol &g_pRdCurrentCamera
x/2wx &g_pRdCurrentCamera
x/12i $eip
bt 3
kill
