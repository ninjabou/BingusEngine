local entity = ...

local position = GetPosition(entity)

if GetKey(KEYBOARD.W) then
    position.y = position.y + 1
end
if GetKey(KEYBOARD.A) then
    position.x = position.x - 1
end
if GetKey(KEYBOARD.S) then
    position.y = position.y - 1
end
if GetKey(KEYBOARD.D) then
    position.x = position.x + 1
end

if GetKeyDown(KEYBOARD.SPACE) then
    PlaySound("yahoo")
end

if GetKeyDown(KEYBOARD.ESC) then
    Quit()
end