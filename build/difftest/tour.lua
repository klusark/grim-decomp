-- Render diff: visit a few sets, wait for the scene to settle and ask the harness for a screenshot of each.
SHOTN = 0
function shot(name)
  SHOTN = SHOTN + 1
  grimlog("SHOT "..SHOTN.." "..name)
  local n = 0
  while SHOTOK ~= SHOTN and n < 100000 do break_here() n = n + 1 end
end
function settle(frames)
  local i = 0
  while i < frames do break_here() i = i + 1 end
end
function main_tour()
  settle(30)
  shot("office")
  SetActorRot(manny.hActor, 0, 135, 0)
  PutActorAt(manny.hActor, 0.6, 1.3, 0)
  settle(30)
  shot("office2")
  SetCameraFOV(60)
  settle(5)
  shot("fov60")
  local sets = {"ha.set","ga.set","bi.set","lr.set","mx.set","ce.set","do.set","hf.set","sh.set","vd.set","tu.set","mo.set"}
  local i = 1
  while sets[i] do
    local st = system.setTable[sets[i]]
    st:switch_to_set()
    settle(40)
    shot(sets[i])
    i = i + 1
  end
  grimlog("DONE")
end
start_script(main_tour)
