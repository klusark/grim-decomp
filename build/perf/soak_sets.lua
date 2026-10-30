soak_sets = {"mo.set","ha.set","ga.set","bi.set","lr.set","mx.set","ce.set","do.set","hf.set","sh.set","vd.set","tu.set"}
function T(n) local s=system.setTable[n] s:switch_to_set() grimlog("SW "..n) end
function Soak() local n=0 while 1 do local i=1 while soak_sets[i] do T(soak_sets[i]) sleep_for(1200) i=i+1 n=n+1 grimlog("SOAK "..n) end end end
start_script(Soak)
