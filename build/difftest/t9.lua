-- walk-box shrinking: GetShrinkPos at several points / amounts (the "rules" tier of the scripted suite checks it)
function main_t9()
  local i = 0
  while i < 10 do break_here() i = i + 1 end
  local pts = { {1.3, 1.6, 0}, {0.5, 1.9, 0}, {0, 0, 0}, {2, 2, 0}, {-1, 1, 0} }
  local amts = { 0.005, 0.1, 0.3 }
  local a = 1
  while pts[a] do
    local b = 1
    while amts[b] do
      local x, y, z = GetShrinkPos(pts[a][1], pts[a][2], pts[a][3], amts[b])
      grimlog(format("shrink %d %d -> %s %s %s", a, b, tostring(x), tostring(y), tostring(z)))
      b = b + 1
    end
    a = a + 1
  end
  ShrinkBoxes(0.1)
  UnShrinkBoxes()
  grimlog("DONE")
end
start_script(main_t9)
