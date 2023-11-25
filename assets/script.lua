enemies = {
    [1] = {type = "in_front",x = 0, y = 0, hp = 3},
    [2] = {type = "behind",x = 800, y = 600, hp = 3},
    [3] = {type = "above",x = 800, y = 0, hp = 3},
    [4] = {type = "under",x = 0, y = 600, hp = 3}
}

function reset_enemy(id)
    if id == 1 then
        enemies[id].x = 0
        enemies[id].y = 0
        print("Enemy with ID " .. id .. " reset to coordinates (" .. x .. ", " .. y .. ")")
    elseif id == 2 then
        enemies[id].x = 800
        enemies[id].y = 600
        print("Enemy with ID " .. id .. " reset to coordinates (" .. x .. ", " .. y .. ")")
    elseif id == 3 then
        enemies[id].x = 800
        enemies[id].y = 0
        print("Enemy with ID " .. id .. " reset to coordinates (" .. x .. ", " .. y .. ")")
    elseif id == 4 then
        enemies[id].x = 0
        enemies[id].y = 600
        print("Enemy with ID " .. id .. " reset to coordinates (" .. x .. ", " .. y .. ")")
    end
end