function WFX(n) local i = 0 while i < n do break_here() i = i + 1 end end
function S7() while not (manny and manny.hActor and system.currentSet) do break_here() end WFX(30) SetSpeechMode(VOICE_AND_TEXT) manny:say_line("/sugl150/") WFX(200) manny:say_line("/sugl151/") WFX(200) manny:say_line("/sugl152/") WFX(200) grimlog("DONE") end
start_script(S7)
