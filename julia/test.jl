# test_functions.jl

using Test

# Include the main.jl file to load the function definitions
include("translateMove.jl")

# Define the test cases
function run_tests_translate()
  for board_size in 5:21
      println("Testing board size: ", board_size)

      @test outputSpace(board_size) == (board_size^2 + 2 * (board_size - 1)^2)

      # Test player moves
      for x in 0:(board_size-1), y in 0:(board_size-1)
          move = [x, y]
          val = move_to_Int(board_size, move)
          @test Int_to_move(board_size, val) == move
      end

      # Test placement moves
      for i in 0:(board_size-2), j in 0:(board_size-2), h in 0:1
          move = [i, j, h]
          val = move_to_Int(board_size, move)
          @test Int_to_move(board_size, val) == move
      end

      # Test invalid moveInt
      invalid_moveInt = outputSpace(board_size) + 1
      @test_throws ErrorException Int_to_move(board_size, invalid_moveInt)
  end
end

# Run the tests
run_tests_translate()
println("All tests passed successfully!")
