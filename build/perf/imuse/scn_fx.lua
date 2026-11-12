function WFX(n) local i = 0 while i < n do break_here() i = i + 1 end end
function SFX() while not (manny and manny.hActor and system.currentSet) do break_here() end WFX(30) ImSetVoiceEffect("Intercom Filter") grimlog("FX on") WFX(5) ImStartVoice("sggl011.wav", 127, 64) WFX(150) ImSetVoiceEffect("Basic Reverb") WFX(5) ImStartVoice("sggl012.wav", 127, 64) WFX(150) ImSetVoiceEffect("Stereo Ring Modulator") WFX(5) ImStartVoice("sggl013.wav", 127, 64) WFX(150) ImSetVoiceEffect("OFF") WFX(5) ImStartVoice("sggl011.wav", 127, 64) WFX(100) grimlog("DONE") end
start_script(SFX)
