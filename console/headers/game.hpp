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
#include <iostream>
#include <iomanip> // Include the header for std::setw
#include <numeric> // For accumulate
#include <thread>
#include <map>
#include <unordered_map>
#include <ctime>
#include <unordered_set>
#include <cstdlib>
#include <chrono>
#include <utility>
#include <algorithm>
#include <random>

#include "astar.hpp"
#include "randomBot.hpp"
#include "minimax.hpp"
#include <memory>  // Include the <memory> header for std::shared_ptr

// class GameState; //Forward dec

using std::vector;
using std::string;
using std::pair;



class Game {
public:

    string MoveKeyValues;
    string WallKeyValues;

    double sim_delay;
    int rounds;
    bool verbose;
    bool is_user_sim;

    std::shared_ptr<GameState> game_state_p;
    vector<string> player_simulation_algorithms = {"randomBot", "path-search"};
    vector<string> algorithms = {"randomBot", "impatientBot", "minimax", "path-search", "online-bot"};
    vector<int> wins = {0, 0};
    vector<pair<vector<double>, vector<double>>> execution_times;
    vector< pair< vector< vector<int> >, vector< vector<int> > > > hist_per_round;

    Game(bool user_sim, bool verbose, int rounds, double sim_delay = 0.5);

    void print_commands();

    void Initialize();

    void quick_run(const string& bot1, const string& bot2) ;

    void player_user();

    vector<int> randombot_agent();

    vector<int> minimax_agent(const int depth = 1);

    vector<int> pathsearch_agent();

    void execute_action( vector<int>& action);

    bool player_simulation(bool printOut = true, bool recordMoves = true);

    void play();

    void GUI_play(string player1type, string player2type, float *sim_delay, int *rounds, bool printOut = false, bool recordMoves = false);

    static void print_colored_output(const string& text, const string& color);
};



#endif // GAME_H