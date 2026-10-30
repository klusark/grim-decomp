function WFX(n) local i = 0 while i < n do break_here() i = i + 1 end end
SETS8 = {"ha.set","ci.set","pc.set","th.set","lm.set","bl.set","sp.set","tr.set","dd.set","cc.set","ac.set","bb.set","cn.set","fo.set","gh.set","hb.set","mo.set"}
function S8() while not (manny and manny.hActor and system.currentSet) do break_here() end WFX(40) local i = 1 while SETS8[i] do local s = system.setTable[SETS8[i]] if s then s:switch_to_set() grimlog("SW "..SETS8[i]) WFX(150) end i = i + 1 end grimlog("DONE") end
start_script(S8)
