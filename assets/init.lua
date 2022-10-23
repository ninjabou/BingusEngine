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
GetPosition(asteroids[0]).x = 0
GetPosition(asteroids[0]).y = 0
GetSprite(asteroids[0]).z = 0
GetSprite(asteroids[0]).scale = 20
GetSprite(asteroids[0]).name = "asteroid"

asteroids[1] = CreateEntity()
GetPosition(asteroids[1]).x = 100
GetPosition(asteroids[1]).y = 0
GetSprite(asteroids[1]).z = 0
GetSprite(asteroids[1]).scale = 20
GetSprite(asteroids[1]).name = "asteroid"

asteroids[2] = CreateEntity()
GetPosition(asteroids[2]).x = -100
GetPosition(asteroids[2]).y = 0
GetSprite(asteroids[2]).z = 0
GetSprite(asteroids[2]).scale = 20
GetSprite(asteroids[2]).rotation = math.pi
GetSprite(asteroids[2]).name = "asteroid"

asteroids[3] = CreateEntity()
GetPosition(asteroids[3]).x = 0
GetPosition(asteroids[3]).y = 100
GetSprite(asteroids[3]).z = 0
GetSprite(asteroids[3]).scale = 20
GetSprite(asteroids[3]).rotation = math.pi / 2
GetSprite(asteroids[3]).name = "asteroid"

asteroids[4] = CreateEntity()
GetPosition(asteroids[4]).x = 0
GetPosition(asteroids[4]).y = -100
GetSprite(asteroids[4]).z = 0
GetSprite(asteroids[4]).scale = 20
GetSprite(asteroids[4]).rotation = -math.pi / 2
GetSprite(asteroids[4]).name = "asteroid"

asteroids[1] = CreateEntity()
GetPosition(asteroids[1]).x = 65
GetPosition(asteroids[1]).y = 65
GetSprite(asteroids[1]).z = 0
GetSprite(asteroids[1]).scale = 20
GetSprite(asteroids[1]).name = "asteroid"

asteroids[2] = CreateEntity()
GetPosition(asteroids[2]).x = -65
GetPosition(asteroids[2]).y = 65
GetSprite(asteroids[2]).z = 0
GetSprite(asteroids[2]).scale = 20
GetSprite(asteroids[2]).name = "asteroid"

asteroids[3] = CreateEntity()
GetPosition(asteroids[3]).x = 65
GetPosition(asteroids[3]).y = -65
GetSprite(asteroids[3]).z = 0
GetSprite(asteroids[3]).scale = 20
GetSprite(asteroids[3]).name = "asteroid"

asteroids[4] = CreateEntity()
GetPosition(asteroids[4]).x = -65
GetPosition(asteroids[4]).y = -65
GetSprite(asteroids[4]).z = 0
GetSprite(asteroids[4]).scale = 20
GetSprite(asteroids[4]).name = "asteroid"