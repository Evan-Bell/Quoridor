#include "headers/randomBot.hpp"

std::vector<int> randombot_action(GameState& game_state) {
    double move_prob = 0.3;

    std::vector<std::vector<int>> wall_placements = game_state.get_available_wall_placements();

    std::vector<std::vector<int>> available_moves = game_state.get_available_moves();

    if (wall_placements.empty()) {
        move_prob = 1.0;
    }

    // Initialize a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define a discrete distribution based on probabilities
    std::vector<double> weights = {move_prob, 1 - move_prob};
    std::discrete_distribution<int> dist(weights.begin(), weights.end());

    // Randomly select from available_moves or wall_placements based on probabilities
    int chosen_index = dist(gen);
    const std::vector<std::vector<int>>& chosen_list = (chosen_index == 0) ? available_moves : wall_placements;

    // Randomly select an item from the chosen list
    std::uniform_int_distribution<int> list_dist(0, chosen_list.size() - 1);
    std::vector<int> chosen_action = chosen_list[list_dist(gen)];

    return chosen_action;
}
