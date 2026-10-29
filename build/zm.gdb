set pagination off
break *rdCamera_SetZoom
commands
silent
printf ">> SetZoom cam=%x p2=%x (%f) ret=%x\n", *(int*)($esp+4), *(int*)($esp+8), *(float*)($esp+8), *(int*)$esp
continue
end
break *Set_ApplySetupCamera
commands
silent
printf ">> ApplySetupCamera\n"
continue
end
run
