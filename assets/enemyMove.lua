function update_enemies(speed, player_x, player_y)
    for _, enemy in ipairs(enemies) do
        local target_x, target_y

        if enemy.type == "in_front" then
            target_x = player_x + 50  -- Move slightly in front
            target_y = player_y
        elseif enemy.type == "behind" then
            target_x = player_x - 50  -- Move slightly behind
            target_y = player_y
        elseif enemy.type == "above" then
            target_x = player_x
            target_y = player_y + 50  -- Move slightly above
        elseif enemy.type == "under" then
            target_x = player_x
            target_y = player_y - 50
        end

        -- Move towards the target
        local angle = math.atan2(target_y - enemy.y, target_x - enemy.x)
        enemy.x = enemy.x + speed * math.cos(angle)
        enemy.y = enemy.y + speed * math.sin(angle)
    end
end
