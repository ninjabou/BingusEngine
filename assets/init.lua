local engine = ...

local toad2 = CreateEntity()
GetPosition(toad2).x = -30
GetPosition(toad2).y = -20;
GetSprite(toad2).z = -1.;
GetSprite(toad2).scale = 10.;
GetSprite(toad2).name = "rocket";
GetScript(toad2).name = "controls";

asteroids = {}

asteroids[0] = CreateEntity()
GetPosition(asteroids[0]).x = -30
GetPosition(asteroids[0]).y = -20;
GetSprite(asteroids[0]).z = 0.;
GetSprite(asteroids[0]).scale = 10.;
GetSprite(asteroids[0]).name = "toad";