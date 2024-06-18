// responsible for the GUI
#include "headers/render.hpp"



Board::Board(Game& game, sf::RenderWindow& window, ImVec2 boardPos) :
game(game),
window(window),
boardPos(boardPos)
{
    game_state_p = (game.game_state_p);
    std::cout << "render " << (game.game_state_p) << std::endl;
    std::cout << game_state_p << std::endl;
}


int Board::start(){
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                this->handleMouseClick(mousePos);
            }
        }

        ImGui::SFML::Update(window, sf::seconds(1.f / 60.f));

        window.clear(sf::Color::White);

        this->render();

        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}

void Board::render() {
    std::cout << "Render begin" << std::endl;
    // Begin ImGui window for board settings
    ImGui::Begin("Board Settings");

    // Dropdowns, buttons, etc.
    ImGui::Combo("Player 1 (Bottom)", &selectedPlayer1Type, playerTypes, IM_ARRAYSIZE(playerTypes));
    ImGui::Combo("Player 2 (Top)", &selectedPlayer2Type, playerTypes, IM_ARRAYSIZE(playerTypes));
    if (ImGui::Button("Run Game")) {
        game.play(); // Call your game's run functiond
    }

    ImGui::End();  // End ImGui window

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

            //player colorings
            if (game_state_p->player1_pos.first == i &&  game_state_p->player1_pos.second == j) {
                cellShape.setFillColor(sf::Color(255, 179, 162));
            }
            // else if (game_state_p->player2_pos == coord) {
            //     cellShape.setFillColor(sf::Color(190, 255, 162));
            // }
            cellShape.setOutlineThickness(1.f);
            cellShape.setOutlineColor(sf::Color::Black);
            window.draw(cellShape);

        }
    }

    // Draw the walls
    for (int i = 0; i < SIZE-1; ++i) {
        for (int j = 0; j < SIZE-1; ++j) {

            float posX = boardPos.x + j * CELL_SIZE;
            float posY = boardPos.y + i * CELL_SIZE;
            float size = CELL_SIZE;

            if(game_state_p->is_ver_wall(i, j)){
                sf::RectangleShape vertWall(sf::Vector2f(2.f, 2*size));
                vertWall.setPosition(posX + size - 2.f, posY + size - 2.f);
                vertWall.setFillColor(sf::Color::Red); // Example color
                window.draw(vertWall);
            }

            if(game_state_p->is_hor_wall(i, j)){
                sf::RectangleShape horWall(sf::Vector2f(2*size, 2.f));
                horWall.setPosition(posX + size - 2.f, posY + size - 2.f);
                horWall.setFillColor(sf::Color::Red); // Example color
                window.draw(horWall);
            }
        }
    }
}

void Board::handleMouseClick(sf::Vector2f mousePos) {
    // Convert mouse position to board coordinates
    int col = static_cast<int>((mousePos.x - boardPos.x) / CELL_SIZE);
    int row = static_cast<int>((mousePos.y - boardPos.y) / CELL_SIZE);

    // Toggle wall type at clicked position
    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE) {
        game_state_p->set_wall(row, col, row%2, 1);
    }
}