set pagination off
break *rdCamera_SetProjectType
commands
silent
printf ">> SetProjectType cam=%x ret=%x\n", *(int*)($esp+4), *(int*)$esp
info symbol *(int*)$esp
continue
end
run
