function WFX(n) local i = 0 while i < n do break_here() i = i + 1 end end
function PAR(tag, h) local s = "" local k = 0 while k < 40 do s = s..tostring(ImGetParam(h, k * 256)).."," k = k + 1 end grimlog("P "..tag.." "..s) end
function S5B() WFX(30) PAR("after_load", "me_tank3.wav") grimlog("P1 "..tostring(ImGetMemoryFootprint()).." "..tostring(ImGetSoundCacheSize())) WFX(200) PAR("later", "me_tank3.wav") quiet() WFX(30) PAR("quiet", "me_tank3.wav") grimlog("DONE") end
start_script(S5B)
