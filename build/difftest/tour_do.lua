-- one render shot of the "do" set (two actors in view)
SHOTN = 0
function shot(name)
  SHOTN = SHOTN + 1
  grimlog("SHOT "..SHOTN.." "..name)
  local n = 0
  while SHOTOK ~= SHOTN and n < 100000 do break_here() n = n + 1 end
end
function main_tour()
  local i = 0
  system.setTable["do.set"]:switch_to_set()
  while i < 40 do break_here() i = i + 1 end
  shot("do.set")
  grimlog("DONE")
end
start_script(main_tour)
