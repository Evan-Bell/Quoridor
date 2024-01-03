#ifndef B2BE7B1E_B3A8_4EEE_A17B_293DCDB25035
#define B2BE7B1E_B3A8_4EEE_A17B_293DCDB25035

#include "game_state.hpp"

struct Node {
    int x, y, fScore;
    Node(int x, int y, int fScore) : x(x), y(y), fScore(fScore) {}
    bool operator>(const Node& other) const {
        return fScore > other.fScore;
    }
};

double z_asearch(GameState& game_state, const std::pair<int, int> start_pos, const int end_row, const std::pair<int, int> other_player, const bool skip_parity);

std::pair<double, double> aStarSearch(GameState& g);

#endif /* B2BE7B1E_B3A8_4EEE_A17B_293DCDB25035 */
