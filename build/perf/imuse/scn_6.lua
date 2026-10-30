function WFX(n) local i = 0 while i < n do break_here() i = i + 1 end end
function S6() while not (manny and manny.hActor and system.currentSet) do break_here() end WFX(30) ImStartVoice("sggl011", 127, 64) WFX(150) ImStartVoice("sggl012.wav", 127, 64) WFX(150) ImStartVoice("SGGL013.WAV", 127, 64) WFX(150) ImStartVoice("sggl014.lip", 127, 64) WFX(100) ImStopVoice() WFX(20) grimlog("DONE") end
start_script(S6)
