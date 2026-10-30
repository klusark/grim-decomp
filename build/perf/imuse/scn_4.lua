function S4() while not (manny and manny.hActor and system.currentSet) do break_here() end local i = 0 while i < 30 do break_here() i = i + 1 end StartFullscreenMovie("funny.snm") while IsMoviePlaying() do break_here() end grimlog("MOVIEDONE") i = 0 while i < 60 do break_here() i = i + 1 end grimlog("DONE") end
start_script(S4)
