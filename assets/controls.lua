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

-- within first checkpoint
if position.x >= -100 and position.x < 0 and position.y >= -10 and position.y < 10 and need_first_checkpoint then
    need_first_checkpoint = false

    laps_completed = laps_completed + 1

    if laps_completed == 3 then
        PlaySound("yahoo")
    end
end

-- within second checkpoint
if position.x >= 0 and position.x < 100 and position.y >= -10 and position.y < 10 and not need_first_checkpoint then
    need_first_checkpoint = true
end

for k, v in pairs(asteroids) do
    local d = Distance(GetPosition(entity), GetPosition(v))

    if d < GetSprite(v).scale then
        GetSprite(entity).name = "explosion"
        if can_awawa then
            PlaySound("awawa")
            can_awawa = false
        end
    end
end

if GetKeyDown(KEYBOARD.ESC) then
    Quit()
end