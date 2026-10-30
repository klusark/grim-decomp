-- angle normalisation: SetActorRot/GetActorRot and TurnActorTo/GetAngleBetweenVectors with awkward angles
function main_t6()
  local i = 0
  while i < 5 do break_here() i = i + 1 end
  local angs = { -725.5, -360, -359.999, -180.1, -0.001, 0, 0.001, 90, 179.99, 180, 359.99, 360, 360.5, 719.99, 720, 1080.3, 1e5, -1e5, 45.123456 }
  local j = 1
  while angs[j] do
    SetActorRot(manny.hActor, angs[j], angs[j] * 0.5, angs[j] * 2)
    local p, y, r = GetActorRot(manny.hActor)
    grimlog(format("rot %.5f -> %.5f %.5f %.5f", angs[j], p, y, r))
    j = j + 1
  end
  local k = 0
  while k < 12 do
    local v1 = { x = 1, y = 0, z = 0 }
    local a = k * 31.7
    local v2 = { x = cos(a), y = sin(a), z = 0.25 * k }
    grimlog(format("angle %d %.5f", k, GetAngleBetweenVectors(v1, v2)))
    k = k + 1
  end
  grimlog("DONE")
end
start_script(main_t6)
