// Game.hpp
#ifndef GAME_H
#define GAME_H

// #include <iostream>
// #include <iomanip> // Include the header for std::setw
#include <vector>
// #include <numeric> // For accumulate
// #include <thread>
#include <string>
// #include <ctime>
// #include <unordered_set>
// #include <cstdlib>
// #include <chrono>
// #include <thread>
// #include <utility>
// #include <algorithm>

#include "color.hpp" // Include the Color header
#include "constants.hpp" // Include the constants.h header file
#include "game_state.hpp"
#include "randomBot.hpp"

using std::vector;
using std::string;


const string DEFAULT_WALL_COLOR = Color::PINK;
const string PLAYER1COLOR = Color::LIGHT_BLUE;
const string PLAYER2COLOR = Color::LIGHT_RED;

class Game {
public:
    
    string MoveKeyValues;
    string WallKeyValues;

    int sim_delay;
    int rounds;
    bool verbose;
    bool is_user_sim;

    GameState game_state;
    vector<string> player_simulation_algorithms = {"randomBot", "randomBot"};
    vector<string> algorithms = {"randomBot", "impatientBot", "minimax-alpha-beta-pruning", "path-search", "online-bot"};
    vector< pair< vector<int>, vector<int> > > execution_times;
    vector<int> wins = {0, 0};
    vector< pair< vector<vector<int>>, vector<vector<int>> > >  hist_per_round;

    Game(bool user_sim, bool verbose, int rounds, int sim_delay = 500);

    void print_commands();

    void Initialize();

    void quick_run(const string& bot1, const string& bot2) ;

    void player1_user();

    vector<int> randombot_agent();

    void execute_action( vector<int> action);

    bool player_simulation();

    void play();
    
    void print_game_stats();

    void print_board();

    static string getWallColor(GameState& g, int i, int j);

    static void print_colored_output(const string& text, const string& color, bool wipe = false, const string& _end = "\n");
    // Add other member functions and variables here.
};



#endif // GAME_H