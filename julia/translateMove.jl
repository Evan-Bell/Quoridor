# Function to calculate the total number of possible moves
function outputSpace(board_size::Int)::Int
  playermoves = board_size^2
  placements = 2 * (board_size - 1)^2
  return playermoves + placements
end

# Define the function that takes an integer and a move
function move_to_Int(board_size::Int, move::Vector{Int})::Int
  if length(move) == 2
    return move[1]*board_size + move[2]
  elseif length(move) == 3
    playermove_base = board_size^2
    ishorizontal_base = move[3] * (board_size - 1)^2
    index_base = move[1]*(board_size - 1) + move[2]
    return playermove_base + ishorizontal_base + index_base
  else
    throw(ErrorException("move is not valid"))
  end
end

# Function to convert an integer back to a move
function Int_to_move(board_size::Int, moveInt::Int)::Vector{Int}
  if moveInt >= outputSpace(board_size) || moveInt < 0
      throw(ErrorException("moveInt is out of valid range"))
  end

  # Player move
  if moveInt < board_size^2
      row = div(moveInt, board_size)
      col = moveInt % board_size
      return [row, col]
  else # Placement move
      placementInt = moveInt - board_size^2
      isHorizontal = (placementInt < (board_size - 1)^2) ? 0 : 1
      placementInt = placementInt % ((board_size - 1)^2)
      row = div(placementInt, board_size - 1)
      col = placementInt % (board_size - 1)
      return [row, col, isHorizontal]
  end
end