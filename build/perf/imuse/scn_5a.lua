function WFX(n) local i = 0 while i < n do break_here() i = i + 1 end end
function PAR(tag, h) local s = "" local k = 0 while k < 40 do s = s..tostring(ImGetParam(h, k * 256)).."," k = k + 1 end grimlog("P "..tag.." "..s) end
function S5() while not (manny and manny.hActor and system.currentSet) do break_here() end WFX(30) ImSetState(1000) WFX(120) H5 = ImStartSound("me_tank3.wav", 127, 1) WFX(30) grimlog("P0 "..tostring(ImGetMemoryFootprint()).." "..tostring(ImGetSoundCacheSize())) PAR("before", "me_tank3.wav") ImSetCuePoint(1) ImSetAttribute(1, 1) ImSetSequence(1) WFX(40) Save("agentN_sc5.gsv") WFX(150) grimlog("DONEA") end
start_script(S5)
