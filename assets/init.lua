local engine = ...

local toad2 = CreateEntity()
GetPosition(toad2).x = -30
GetPosition(toad2).y = -20;
GetSprite(toad2).z = -1.;
GetSprite(toad2).scale = 10.;
GetSprite(toad2).name = "rocket";
GetScript(toad2).name = "controls";

asteroids = {}

-- Outer 'stroids
for i = 0, 10 do
    asteroids[i] = CreateEntity()
    GetPosition(asteroids[i]).x = math.cos(i / 1.75) * 100
    GetPosition(asteroids[i]).y = math.sin(i / 1.75) * 100
    GetSprite(asteroids[i]).z = 0
    GetSprite(asteroids[i]).scale = 20
    GetSprite(asteroids[i]).rotation = i / 1.75
    GetSprite(asteroids[i]).name = "asteroid"
end

-- Inner 'stroid
asteroids[11] = CreateEntity()
GetPosition(asteroids[11]).x = 0
GetPosition(asteroids[11]).y = 0
GetSprite(asteroids[11]).z = 0
GetSprite(asteroids[11]).scale = 20
GetSprite(asteroids[11]).name = "asteroid"

finishline = CreateEntity()
GetPosition(finishline).x = -50
GetPosition(finishline).y = 0
GetSprite(finishline).z = -1
GetSprite(finishline).scale = 35
GetSprite(finishline).name = "finishline"

can_awawa = true

need_first_checkpoint = true

laps_completed = 0