#include "headers/render.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(900, 800), "Quoridor Bot Runner");
    ImGui::SFML::Init(window);

    Game game = Game(false, true, 1, 0.00);

    ImVec2 boardPosition(5.f, 5.f);
    Board board = Board(game, window, boardPosition);

    board.start();
    board.kill();

}


int sim_game(){

}

/*
Thoughts:

train net on board path connections (is there a block) could be good for computing possible moves (each one now requires check of paths)

train net on evaluating positions, do a simple depth 2 mini_max with that value to obtain good ideas

train net on best move response to positions

*/