mutable struct Game
    file_path::String
    board_size::Int
    horizontal_placement::Array{Bool, 2}
    vertical_placement::Array{Bool, 2}
    player_pos::Array{Int, 2}
    p1_walls_left::Int;
    p2_walls_left::Int;
    game_over::Bool
    p1_won::Bool
    lines::Vector{String}
    line_counter::Int
end

function Game(file_path::String)
    lines = readlines(file_path)

    # get size
    val = split(lines[1], " ")
    board_size = parse(Int, val[2])

    temp = split(lines[2], " ")
    walls = parse(Int, temp[2])
    p1_walls_left = walls;
    p2_walls_left = walls;

    #set vars
    horizontal_placement = falses(board_size, board_size)
    vertical_placement = falses(board_size, board_size)
    player_pos = zeros(Int, board_size, board_size)
    player_pos[1, div(board_size, 2) + 1] = 1
    player_pos[end, div(board_size, 2) + 1] = -1


    winner_info = split(lines[end], " ")
    p1_won = winner_info[2] == "P1"

    game_over = false;
    line_counter = 6;

    return Game(file_path, board_size, horizontal_placement, vertical_placement, player_pos, p1_walls_left, p2_walls_left, game_over, p1_won, lines, line_counter)
end

function parse_move(move_str)
    move_str = replace(move_str, '[' => "")
    move_str = replace(move_str, ']' => "")
    move_vec = parse.(Int, split(move_str, ","))
    return move_vec
end

function plural_next_moves!(g::Game, iters::Int)
    for _ in 0:iters
        next_move!(g)
    end
end


function next_move!(g::Game)
    line = g.lines[g.line_counter]

    if startswith(line, "Won")
        g.game_over = true;
        return
    end

    # Split each line by the comma
    parts = split(line, " ")

    # Parse the vector part (move) and ignore the time part
    move = parse_move(parts[1])
    # println(move)

    # Categorize the move
    if length(move) == 2
        if g.line_counter % 2 == 0
            # Unset the other value of 1 in the matrix
            g.player_pos[g.player_pos .== 1] .= 0
            g.player_pos[move[1] + 1, move[2] + 1] = 1
        else
            # Unset the other value of -1 in the matrix
            g.player_pos[g.player_pos .== -1] .= 0
            g.player_pos[move[1] + 1, move[2] + 1] = -1
        end
    elseif length(move) == 3
        x, y, placement_type = move
        if placement_type == 0
            g.horizontal_placement[x+1, y+1] = true
        elseif placement_type == 1
            g.vertical_placement[x+1, y+1] = true
        end

        # decrement walls left
        if g.line_counter % 2 == 0
            g.p1_walls_left -= 1
        else
            g.p2_walls_left -= 1
        end
    end
    g.line_counter += 1;
end