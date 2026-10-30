-- Differential probe of one Lua API function: calls it with a set of argument patterns inside Manny's office and logs
-- every result plus a state snapshot.  The function name is in PROBE_FUNC (set by run_probe.py through probe_cfg.lua).
-- Everything printed must be deterministic (no addresses): userdata handles are small integers in this engine.
dofile("probe_cfg.lua")

function S(x)
  local t = type(x)
  if t == "number" then
    if x ~= x then return "nan" end
    if x == floor(x) then return format("%d", x) end
    return format("%.4f", x)
  elseif t == "string" then return '"'..x..'"'
  elseif t == "nil" then return "nil"
  elseif t == "table" then
    local s = "{"
    local keys = { "x", "y", "z", "r", "g", "b", "n" }
    local i = 1
    while keys[i] do
      if x[keys[i]] ~= nil then s = s..keys[i].."="..S(x[keys[i]])..", " end
      i = i + 1
    end
    local j = 1
    while x[j] ~= nil and j < 12 do s = s.."["..j.."]="..S(x[j]).."," j = j + 1 end
    return s.."}"
  else return t end
end

function snapshot(tag)
  local a = manny.hActor
  local x, y, z = GetActorPos(a)
  local p, yw, r = GetActorRot(a)
  local cx, cy, cz = GetCameraPosition()
  local ix, iy, iz = GetCameraInterest()
  grimlog("SNAP "..tag.." pos "..S(x)..","..S(y)..","..S(z).." rot "..S(p)..","..S(yw)..","..S(r)
    .." scale "..S(GetActorScale(a)).." wr "..S(GetActorWalkRate(a)).." tr "..S(GetActorTurnRate(a))
    .." cam "..S(cx)..","..S(cy)..","..S(cz).." int "..S(ix)..","..S(iy)..","..S(iz).." fov "..S(GetCameraFOV())
    .." roll "..S(GetCameraRoll()).." mv "..S(IsActorMoving(a)).." tu "..S(IsActorTurning(a)))
end

A = manny.hActor
-- argument patterns; "A" = Manny's actor, V.. = values
PATTERNS = {
  { n=0 },
  { A; n=1 },
  { A, 1.5; n=2 },
  { A, 0; n=2 },
  { A, 10, 20, 30; n=4 },
  { A, "mumble"; n=2 },
  { A, 1, 2, 3, 4; n=5 },
  { 1, 2, 3; n=3 },
  { "str"; n=1 },
  { nil; n=1 },
  { A, A; n=2 },
  { A, "mo_rest", "x"; n=3 },
  { A, 0.25, 0.5, 0.75, 1.0, 2.0; n=6 },
  { -3.5, 7; n=2 },
}

function main_probe()
  snapshot("start")
  local f = getglobal(PROBE_FUNC)
  if not f then grimlog("MISSING "..PROBE_FUNC) grimlog("DONE") return end
  local i = 1
  while PATTERNS[i] do
    local p = PATTERNS[i]
    local as = ""
    local j = 1
    while j <= p.n do as = as..S(p[j]).."," j = j + 1 end
    grimlog("CALL "..i.." "..PROBE_FUNC.."("..as..")")
    local r1, r2, r3, r4, r5 = call(f, p, "x")
    grimlog("  -> "..S(r1).." | "..S(r2).." | "..S(r3).." | "..S(r4).." | "..S(r5))
    snapshot("after"..i)
    break_here()
    break_here()
    snapshot("frame"..i)
    i = i + 1
  end
  sleep_for(200)
  snapshot("end")
  grimlog("DONE")
end
start_script(main_probe)
