#include "headers/minimax.hpp"


double minimax_search(GameState& game_state, const int depth, double alpha, double beta, const bool is_max){
    if (game_state.is_goal_state() || depth == 0){
        pair<double, double> dists = aStarSearch(game_state);

        if (dists.first == std::numeric_limits<double>::infinity() || dists.second == std::numeric_limits<double>::infinity()){
            if (is_max){
                return std::numeric_limits<double>::infinity();
            }
            else{
                return -std::numeric_limits<double>::infinity();
            }
        }

        double reward = dists.second - dists.first;// + game_state.walls_per_player.first - game_state.walls_per_player.second;
        return reward;
    }

    else if (is_max){
        double best_val = -std::numeric_limits<double>::infinity();

        vector<vector<int> > available_moves = game_state.get_available_moves();
        for (vector<int>& move : available_moves){
            // Alpha-Beta Pruning
            if (beta <= alpha){
                break;
            }

            pair<int, int> temp = game_state.get_cur_player_pos();
            vector<int> curpos = {temp.first, temp.second};

            game_state.move_piece(move);
            game_state.player1 = !game_state.player1;
            double reward = minimax_search(game_state, depth-1, alpha, beta, false);
            game_state.player1 = !game_state.player1;
            game_state.move_piece(curpos);

            best_val = std::max(best_val, reward);
            alpha = std::max(alpha, best_val);
        }

        vector<vector<int>> wall_placements = game_state.get_available_wall_placements();
        for (vector<int>& wall : wall_placements){
            // Alpha-Beta Pruning
            if (beta <= alpha){
                break;
            }

            int x = wall[0];
            int y = wall[1];
            bool isHorizontal = wall[2];

            game_state.set_wall(x, y, isHorizontal, depth>1);
            game_state.player1 = !game_state.player1;
            double reward = minimax_search(game_state, depth-1, alpha, beta, false);
            game_state.player1 = !game_state.player1;
            game_state.clear_wall(x, y);
            game_state.saved_wall_placements = wall_placements; // reinstate free walls

            best_val = std::max(best_val, reward);
            alpha = std::max(alpha, best_val);
        }

        return (best_val == -std::numeric_limits<double>::infinity())? std::numeric_limits<double>::infinity() : best_val;
    }

    else{
        double best_val = std::numeric_limits<double>::infinity();

        vector<vector<int> > available_moves = game_state.get_available_moves();
        for (vector<int>& move : available_moves){
            // Alpha-Beta Pruning
            if (beta <= alpha){
                break;
            }

            pair<int, int> temp = game_state.get_cur_player_pos();
            vector<int> curpos = {temp.first, temp.second};

            game_state.move_piece(move);
            game_state.player1 = !game_state.player1;
            double reward = minimax_search(game_state, depth-1, alpha, beta, true);
            game_state.player1 = !game_state.player1;
            game_state.move_piece(curpos);

            best_val = std::min(best_val, reward);
            beta = std::min(beta, best_val);
        }

        vector<vector<int>> wall_placements = game_state.get_available_wall_placements();
        for (vector<int>& wall : wall_placements){
            // Alpha-Beta Pruning
            if (beta <= alpha){
                break;
            }

            int x = wall[0];
            int y = wall[1];
            bool isHorizontal = wall[2];

            game_state.set_wall(x, y, isHorizontal, depth>1);
            game_state.player1 = !game_state.player1;
            double reward = minimax_search(game_state, depth-1, alpha, beta, true);
            game_state.player1 = !game_state.player1;
            game_state.clear_wall(x, y);
            game_state.saved_wall_placements = wall_placements; // reinstate free walls

            best_val = std::min(best_val, reward);
            beta = std::min(beta, best_val);
        }

        return (best_val == std::numeric_limits<double>::infinity())? -std::numeric_limits<double>::infinity() : best_val;
    }
}