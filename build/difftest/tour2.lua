-- more sets (the walker tests' sets): switch, settle, screenshot
SHOTN = 0
function shot(name)
  SHOTN = SHOTN + 1
  grimlog("SHOT "..SHOTN.." "..name)
  local n = 0
  while SHOTOK ~= SHOTN and n < 100000 do break_here() n = n + 1 end
end
function settle(frames) local i = 0 while i < frames do break_here() i = i + 1 end end
function main_tour2()
  settle(20)
  local sets = {"be.set","os.set","si.set","le.set","al.set","rf.set","re.set","hq.set","ha.set","ga.set","ly.set","bi.set"}
  local i = 1
  while sets[i] do
    local st = system.setTable[sets[i]]
    if st then
      st:switch_to_set()
      settle(30)
      shot(sets[i])
    else grimlog("noset "..sets[i]) end
    i = i + 1
  end
  grimlog("DONE")
end
start_script(main_tour2)
