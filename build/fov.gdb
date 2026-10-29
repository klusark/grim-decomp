set pagination off
break *rdCamera_SetFov
commands
silent
printf ">> SetFov cam=%x fov=%f ret=%x\n", *(int*)($esp+4), *(float*)($esp+8), *(int*)$esp
continue
end
break *rdCamera_SetProjectType
commands
silent
printf ">> SetProjectType cam=%x type=%d\n", *(int*)($esp+4), *(int*)($esp+8)
continue
end
break *rdCamera_SetCanvas
commands
silent
printf ">> SetCanvas cam=%x canvas=%x\n", *(int*)($esp+4), *(int*)($esp+8)
continue
end
run
