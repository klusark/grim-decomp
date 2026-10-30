function WFX(n) local i = 0 while i < n do break_here() i = i + 1 end end
function S3() while not (manny and manny.hActor and system.currentSet) do break_here() end WFX(40) ImSetState(1000) WFX(250) ImSetState(1001) WFX(250) ImSetState(1004) WFX(250) ImSetState(1007) WFX(250) ImSetState(1022) WFX(250) ImSetState(1040) WFX(250) ImSetState(1042) WFX(250) ImSetState(1121) WFX(250) ImSetState(1010) WFX(250) ImSetState(1002) WFX(250) ImSetState(1000) WFX(100) grimlog("DONE") end
start_script(S3)
