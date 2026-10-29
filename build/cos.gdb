set pagination off
break Actor_SetCostume
commands
silent
printf ">> SetCostume idx=%d name=%s\n", ((int)actor - *(int*)&g_pActorTable)/0xa8, name
finish
end
run
