local entity = ...

-- using Health for unintended purposes hee hee hoo hoo so nefarious!
health = GetHealth(entity)
health.percent = health.percent + 0.1

position = GetPosition(entity)
position.x = math.sin(health.percent) * 5
position.y = math.cos(health.percent) * 5

sprite = GetSprite(entity)
sprite.rotation = sprite.rotation - 0.001