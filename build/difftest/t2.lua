-- is Manny drawn?  (the screen box of the actor is only valid once the actor was rendered)
function main_t2()
  local i = 0
  while i < 30 do break_here() i = i + 1 end
  local l, t, w, h = GetActorRect(manny.hActor)
  if l and w and w > 0 and h > 0 then grimlog("RECT ok") else grimlog("RECT empty "..tostring(l)..","..tostring(w)) end
  grimlog("DONE")
end
start_script(main_t2)
