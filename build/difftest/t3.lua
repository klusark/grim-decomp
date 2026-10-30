-- movement oracle: walk, turn and walk-vector in the office, positions logged every 10 frames (deterministic: fixed frame time)
function P(tag)
  local x, y, z = GetActorPos(manny.hActor)
  local p, yw, r = GetActorRot(manny.hActor)
  grimlog(format("%s pos %.4f %.4f %.4f yaw %.3f mv %s tu %s", tag, x, y, z, yw, tostring(IsActorMoving(manny.hActor)), tostring(IsActorTurning(manny.hActor))))
end
function frames(n, tag)
  local i = 0
  while i < n do
    break_here()
    i = i + 1
    if mod(i, 10) == 0 then P(tag..i) end
  end
end
function main_t3()
  frames(30, "idle")
  manny:walkto(0.4, 1.7, 0)
  frames(300, "walk1_")
  TurnActor(manny.hActor, 1)
  frames(60, "turn_")
  manny:walkto(1.3, 1.6, 0)
  frames(300, "walk2_")
  WalkActorForward(manny.hActor)
  frames(40, "fwd_")
  SetActorWalkRate(manny.hActor, 0.8)
  manny:walkto(0.3, 1.5, 0)
  frames(200, "walk3_")
  PutActorAt(manny.hActor, 0.9, 1.4, 0)
  SetActorRot(manny.hActor, 0, 200, 0)
  frames(20, "put_")
  WalkActorVector(manny.hActor, manny.hActor, 0, 0.5, 0)
  frames(60, "vec_")
  grimlog("DONE")
end
start_script(main_t3)
