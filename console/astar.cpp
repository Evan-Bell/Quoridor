
#include "headers/astar.hpp"

inline double z_asearch(GameState& game_state, const std::pair<int, int> start_pos, const int end_row, const std::pair<int, int> other_player, const bool skip_parity) {

    if (start_pos.first == end_row) {
        return -1;
    }

    int size = game_state.size;
    const int directions[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Up, Down, Left, Right

    std::vector<std::vector<bool>> visited(size, std::vector<bool>(size, false));

    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> p_queue;

    p_queue.emplace(start_pos.first, start_pos.second, 0);

    std::vector<std::vector<int>> gScore(size, std::vector<int>(size, INT_MAX));

    gScore[start_pos.first][start_pos.second] = 0;

    while (!p_queue.empty()) {
        Node current = p_queue.top();
        p_queue.pop();

        int x = current.x;
        int y = current.y;
        std::pair<int, int> cur_pos = std::make_pair(x,y);

        if (x == end_row) {
            return current.fScore;
        }

        if (!visited[x][y]) {
            visited[x][y] = true;

            for (const auto& dir : directions) {
                int newX = x + dir[0];
                int newY = y + dir[1];
                std::pair<int, int> t_pos = std::make_pair(newX, newY);
                if (game_state.is_valid_move(cur_pos, t_pos)) { // Pass the coordinates to is_valid_move
                    int tentativeGScore = gScore[x][y] + 1;

                    if (other_player == t_pos && t_pos.first != end_row && tentativeGScore%2 == skip_parity){
                        tentativeGScore = gScore[x][y];
                    }

                    if (tentativeGScore < gScore[newX][newY]) {
                        gScore[newX][newY] = tentativeGScore;
                        int fScore = tentativeGScore + abs(newX - end_row); // L1 norm
                        p_queue.emplace(newX, newY, fScore);
                    }
                }
            }
        }
    }
    // No path found
    return std::numeric_limits<double>::infinity();
}


inline std::pair<double, double> aStarSearch(GameState& g) {
    double p1 = z_asearch(g, g.player1_pos, 0, g.player2_pos, !g.player1);
    double p2 = z_asearch(g, g.player2_pos, g.size-1, g.player1_pos, g.player1);
    // std::cout << p1 << " " << p2 << std::endl;
    return std::make_pair(p1,p2);
}
