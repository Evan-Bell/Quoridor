// responsible for the GUI
#include "headers/render.hpp"



Board::Board() {
    Game g = Game(false, true, 2, 0.00);
    GameState game_state = g.game_state;
}

void Board::render(sf::RenderWindow& window, ImVec2 boardPos) {
    ImGui::Begin("Board Settings");

    // Dropdown for selecting wall type
    static const char* wallTypes[] = { "Empty", "Type 1", "Type 2", "Type 3" };
    ImGui::Combo("Wall Type", &selectedWallType, wallTypes, IM_ARRAYSIZE(wallTypes));

    // Checkbox to toggle grid display
    ImGui::Checkbox("Show Grid", &showGrid);

    ImGui::End();

    // Draw the board
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            // Calculate position and size for each cell
            float posX = boardPos.x + j * CELL_SIZE;
            float posY = boardPos.y + i * CELL_SIZE;
            float size = CELL_SIZE;

            // Draw cell background
            sf::RectangleShape cellShape(sf::Vector2f(size, size));
            cellShape.setPosition(posX, posY);
            cellShape.setFillColor(sf::Color::White);
            cellShape.setOutlineThickness(1.f);
            cellShape.setOutlineColor(sf::Color::Black);
            window.draw(cellShape);

            // Draw walls based on board array
            auto temp = std::make_pair(i, j);
            if (game_state.player1_pos == temp || game_state.player2_pos == temp) {
                sf::RectangleShape wall(sf::Vector2f(size, 2.f));
                wall.setPosition(posX, posY + size / 2.f - 1.f);
                wall.setFillColor(sf::Color::Black);
                window.draw(wall);
            }
        }
    }
}

void Board::handleMouseClick(sf::Vector2f mousePos, ImVec2 boardPos) {
    // Convert mouse position to board coordinates
    int col = static_cast<int>((mousePos.x - boardPos.x) / CELL_SIZE);
    int row = static_cast<int>((mousePos.y - boardPos.y) / CELL_SIZE);

    // Toggle wall type at clicked position
    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE) {
        game_state.set_wall(row, col, 1, 1);
    }
}