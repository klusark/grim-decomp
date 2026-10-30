-- save game round trip: Lua globals, a screen primitive (sputPrimitive state), then Save; the harness Loads it back (FOLLOW)
MARK = 42
function main_t8()
  local i = 0
  while i < 20 do break_here() i = i + 1 end
  local r = DrawRectangle(50, 60, 200, 160, { color = MakeColor(0, 0, 255), layer = 2, filled = TRUE })
  local l = DrawLine(0, 0, 100, 100, { color = MakeColor(255, 0, 0) })
  SetActorWalkRate(manny.hActor, 0.77)
  MARK = 43
  Save("t8.gsv")
  MARK = 7
  grimlog("saved, marker now "..MARK.." prims "..r.." "..l)
  grimlog("DONE")
end
start_script(main_t8)
