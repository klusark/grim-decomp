-- Loose-file override of the game's last boot script (_local.lua).
-- The original (precompiled) script was extracted from DATA000.LAB to _local_orig.lua and is run first.
dofile("_local_orig.lua")

-- ---- the mod: Manny talks in magenta and walks and runs faster ----
MOD_LOADED = 1
MANNY_WALK_RATE = 0.8     -- was 0.4; _manny.lua passes these to set_walk_rate() whenever the walk chore changes
MANNY_RUN_RATE = 2.4      -- was 1.5
if not MOD_orig_manny_default then
  MOD_orig_manny_default = manny.default
  function manny:default()          -- Manny's per-scene reset: run the original, then re-apply the colour
    MOD_orig_manny_default(self)
    self:set_talk_color(Magenta)
  end
end
manny:set_talk_color(Magenta)
PrintDebug("loose _local.lua active\n")
