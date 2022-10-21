local entity = ...

local position = GetPosition(entity)
local velocity = GetVelocity(entity)
local sprite = GetSprite(entity)

if GetKey(KEYBOARD.W) then
    velocity.x = Lerp(velocity.x, 2 * -math.sin(sprite.rotation), 0.03)
    velocity.y = Lerp(velocity.y, 2 * math.cos(sprite.rotation), 0.03)
end
if not GetKey(KEYBOARD.W) then
    velocity.x = Lerp(velocity.x, 0, 0.01)
    velocity.y = Lerp(velocity.y, 0, 0.01)
end
if GetKey(KEYBOARD.A) then
    sprite.rotation = sprite.rotation + 0.05
end
if GetKey(KEYBOARD.D) then
    sprite.rotation = sprite.rotation - 0.05
end

position.x = position.x + velocity.x
position.y = position.y + velocity.y

if GetKeyDown(KEYBOARD.SPACE) then
    PlaySound("yahoo")
end

if GetKeyDown(KEYBOARD.ESC) then
    Quit()
end

for k, v in pairs(asteroids) do
    print(k, v[1], v[2], v[3])
end  