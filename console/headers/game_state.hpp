// game_state.hpp
#ifndef GAMESTATE_H
#define GAMESTATE_H

// #include <iostream>
// #include <iomanip> // Include the header for std::setw
#include <vector>
// #include <numeric> // For accumulate
// #include <thread>
// #include <string>
// #include <ctime>
// #include <unordered_set>
// #include <cstdlib>
// #include <chrono>
// #include <utility>
// #include <algorithm>

#include <iostream>
#include <iomanip> // Include the header for std::setw
// #include <vector>
#include <numeric> // For accumulate
#include <thread>
#include <string>
#include <ctime>
#include <unordered_set>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <utility>
#include <algorithm>



#include "constants.hpp"
#include "color.hpp"

using std::vector;
using std::pair;

class GameState {
public:
    bool player1;
    int size;
    int num_walls;
    int walls_dim;
    bool calculating = false;
    pair<int, int> player1_pos;
    pair<int, int> player2_pos;
    pair<int, int> walls_per_player;
    bool check_wall_blocks_exit_on_gen;
    vector<int> ver_walls; // vertical walls (ints of 1's and 0's)
    vector<int> hor_walls; //horizontal walls (ints of 1's and 0's)
    vector<int> player1_walls;
    vector<int> player2_walls;
    vector< vector<int> > saved_wall_placements;

    GameState();

    void reinitialize();

    // void copy(GameState& game_state);

    /**
     * Checks if a horizontal wall is present at (x,y) where (0,0) is the bottom right intersection of the top left square
     * @param x the x value
     * @param y the y value
    */
    bool is_hor_wall(const int x, const int y);

    /**
     * Checks if a vertical wall is present at (x,y) where (0,0) is the bottom right intersection of the top left square
     * @param x the x value
     * @param y the y value
     */
    bool is_ver_wall(const int x, const int y);

    /**
     * Sets a wall at (x,y) where (0,0) is the bottom right intersection of the top left squared
     * @param x the x value
     * @param y the y value
     * @param isHorizontal whether to place a horizontal wall or not
     * @param computeNewWallPlacements whether to recalculate new wall placements, defaults TRUE
     */
    void set_wall(const int x, const int y, const bool isHorizontal, bool computeNewWallPlacements = true);

    /**
     * Sets which player placed a wall at a given index
     * @param x the x value
     * @param y the y value
     * @param isPlayer1 whether player 1 placed the wall (as opposed to player 2)
     */
    void set_which_player_placed_wall(const int x, const int y, const bool isPlayer1);

    /**
     * Removes a wall from an index
     * @param x the x value
     * @param y the y value
     */
    void clear_wall(const int x, const int y);

    /**
     * Checks if a wall exists between two locations the player is looking to move.
     * Includes checking when the move is multi-step, like jumps
     * @param pos the starting position {x,y}
     * @param new_pos the new position to move to {x,y}
     *
     * DOES NOT ACTUALLY MOVE PLAYER
     */
    bool is_wall_blocking_move(const pair<int,int>& pos, const pair<int,int>& new_pos);

    /**
     * Checks is a given move is valid (in bounds and not blocked)
     * @param pos the starting position {x,y}
     * @param new_pos the new position to move to {x,y}
     *
     * DOES NOT ACTUALLY MOVE PLAYER
     */
    bool is_valid_move(pair<int,int>& pos, pair<int,int>& new_pos);

    /**
     * Returns a vector of available moves for the given player, includes all directional moves, including jumps
     */
    vector<vector<int>> get_available_moves();

    /**
     * Checks if a given wall placement location is possible
     * @param pos the pos of the wall {x,y}
     * @param isHorizontal whether the wall should be horizontal
     *
     * @note the class variable "check_wall_blocks_on_gen" will enable exit checking in this function, where the wall will be checked
     * to ensure it doesn't block a player from reaching the other side (which is illegal). THIS CHECK WILL USE SET WALL, CAN CREATE INFINITE LOOP
     */
    bool is_wall_placement_valid(const pair<int,int>& pos, const bool isHorizontal);

    /**
     * Checks if the wall would block the exit for either player, which is illegal
     * @param pos the pos of the wall {x,y}
     * @param isHorizontal whether the wall should be horizontal
     *
     */
    bool is_wall_blocking_exit(const pair<int, int>& pos, const int isHorizontal);

    /**
     * Gets all spots for available wall placements, and saves/gets them into/from "saved_wall_placements" for reuse, to be efficient
     */
    vector<vector<int>> get_available_wall_placements();

    /**
     * Prunes the current saved_wall_placements, checking if each is still valid
     */
    void update_available_wall_placements();

    /**
     * Checks whether a player has reached the goal rank (i.e won)
     */
    bool is_goal_state();

    /**
     * Gets which player won
     * @returns 1 if player1 ---- OR ---- 0 if player2
     */
    int get_winner();

    /**
     * Places a wall at the specified location, more permanent then set_wall()
     * @param inp the location {x, y, isHorizontal} of the specified wall
     * @param checkIfValid whether to perform is_wall_placement_valid(), can cause loop, defaults TRUE
     * @param computeNewWallPlacements whether to compute the new wall placements, otherwise wipes "saved_wall_placements", defaults TRUE
     *
     * @note modifies that player placed wall too, updating a player's walls
     */
    void place_wall(vector<int> inp, bool checkIfValid = true, bool compute_new_wall_placements = true);

    /**
     * Moves a piece for the current active player
     * @param new_move the new {x,y} to move to
     *
     * @note This updates the "saved_wall_placements" with changes to nearby wall indexes
     */
    void move_piece(vector<int> new_move);

    /**
     * Prints out stats of the game, like number of walls left
     */
    void print_game_stats();

    /**
     * Prints out a board representation
     */
    void print_board();

    /**
     * Used for print_board mostly, gets the color of a wall based on which player placed it
     */
    std::string getWallColor(int i, int j);

    /**
     * Gets which player placed a wall
     * @param x the x index
     * @param x the x index
     * @note placed is considered actual wall place using "place_wall()",
     * while "set_wall()" is considered a temporary place for the purpose of calculating
     * @returns player1 returns 1  ~~~~~~  player 2 returns 2 ~~~~~~ otherwise 0
     */
    int whichPlayerPlacedWall(int x, int y);

    /**
     * Gets the current position of the current active player
     */
    pair<int, int> get_cur_player_pos();
};

#endif // GAMESTATE_H