mutable struct Game
    file_path::String
    board_size::Int
    horizontal_placement::Array{Bool, 2}
    vertical_placement::Array{Bool, 2}
    player1_pos::Tuple{Int, Int}
    player2_pos::Tuple{Int, Int}
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
    player1_pos = (0, div(board_size, 2))
    player2_pos = (board_size-1, div(board_size, 2))


    winner_info = split(lines[end], " ")
    p1_won = winner_info[2] == "P1"

    game_over = false;
    line_counter = 6;

    return Game(file_path, board_size, horizontal_placement, vertical_placement, player1_pos, player2_pos, p1_walls_left, p2_walls_left, game_over, p1_won, lines, line_counter)
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


function next_move!(game::Game)
    line = game.lines[game.line_counter]

    if startswith(line, "Won")
        game.game_over = true;
        return
    end

    # Split each line by the comma
    parts = split(line, " ")

    # Parse the vector part (move) and ignore the time part
    move = parse_move(parts[1])
    # println(move)

    # Categorize the move
    if length(move) == 2
        if game.line_counter % 2 == 0
            game.player1_pos = (move[1] + 1, move[2] + 1)
        else
            game.player2_pos = (move[1] + 1, move[2] + 1)
        end
    elseif length(move) == 3
        x, y, placement_type = move
        if placement_type == 0
            game.horizontal_placement[x+1, y+1] = true
        elseif placement_type == 1
            game.vertical_placement[x+1, y+1] = true
        end

        # decrement walls left
        if game.line_counter % 2 == 0
            game.p1_walls_left -= 1
        else
            game.p2_walls_left -= 1
        end
    end
    game.line_counter += 1;
end