function main_t4()
  local i = 0
  while i < 10 do break_here() i = i + 1 end
  local p, yw, r = GetActorRot(manny.hActor)
  grimlog(format("yaw %.1f", yw))
  grimlog("DONE")
end
start_script(main_t4)
