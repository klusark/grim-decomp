-- screen primitives: lines/rectangles/polygons with a colour table, then change, move and kill them
SHOTN = 0
function shot(name)
  SHOTN = SHOTN + 1
  grimlog("SHOT "..SHOTN.." "..name)
  local n = 0
  while SHOTOK ~= SHOTN and n < 100000 do break_here() n = n + 1 end
end
function settle(frames) local i = 0 while i < frames do break_here() i = i + 1 end end
function main_t7()
  settle(20)
  local c1 = MakeColor(255, 0, 0)
  local c2 = MakeColor(0, 255, 0)
  local c3 = MakeColor(255, 255, 0)
  local l1 = DrawLine(10, 10, 600, 400, { color = c1, layer = 2 })
  local r1 = DrawRectangle(100, 100, 300, 220, { color = c2, layer = 2, filled = TRUE })
  local p1 = DrawPolygon({ { x = 400, y = 50 }, { x = 500, y = 80 }, { x = 450, y = 150 } }, { color = c3, layer = 2 })
  grimlog("ids "..tostring(l1).." "..tostring(r1).." "..tostring(p1))
  settle(10)
  shot("prims1")
  ChangePrimitive(r1, { color = c3 })
  ChangePrimitive(l1, { color = c2, layer = 1 })
  settle(10)
  shot("prims2")
  KillPrimitive(l1)
  KillPrimitive(p1)
  settle(10)
  shot("prims3")
  PurgePrimitiveQueue()
  settle(10)
  shot("prims4")
  grimlog("DONE")
end
start_script(main_t7)
