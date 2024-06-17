#include "headers/render.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(900, 800), "Quoridor Bot Runner");
    ImGui::SFML::Init(window);

    Game game = Game(false, true, 1, 0.00);

    ImVec2 boardPosition(5.f, 5.f);
    Board board = Board(game, window, boardPosition);

    board.start();

}