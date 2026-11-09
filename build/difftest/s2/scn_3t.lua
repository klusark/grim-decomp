function WMS(ms) local t = 0 while t < ms do break_here() t = t + (system.frameTime or 17) end end
function S3T() while not (manny and manny.hActor and system.currentSet) do break_here() end WMS(680) grimlog("T " .. tostring(system.frameTime)) ImSetState(1000) WMS(4250) ImSetState(1001) WMS(4250) ImSetState(1004) WMS(4250) ImSetState(1007) WMS(4250) ImSetState(1022) WMS(4250) ImSetState(1040) WMS(4250) ImSetState(1042) WMS(4250) ImSetState(1121) WMS(4250) ImSetState(1010) WMS(4250) ImSetState(1002) WMS(4250) ImSetState(1000) WMS(1700) grimlog("DONE") end
start_script(S3T)
