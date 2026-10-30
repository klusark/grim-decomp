-- startup state comparison: Manny's pose and the camera after the boot sequence
function snapshot(tag)
  local a = manny.hActor
  local x, y, z = GetActorPos(a)
  local p, yw, r = GetActorRot(a)
  local cx, cy, cz = GetCameraPosition()
  local ix, iy, iz = GetCameraInterest()
  grimlog("SNAP "..tag.." pos "..x..","..y..","..z.." rot "..p..","..yw..","..r.." cam "..cx..","..cy..","..cz.." int "..ix..","..iy..","..iz.." fov "..GetCameraFOV())
end
snapshot("start")
grimlog("DONE")
