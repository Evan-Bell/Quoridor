// responsible for the GUI
#include "headers/render.hpp"


#define WALL_THICKNESS 3.f
#define PLAYER1_WALL_COLOR sf::Color(56, 242, 27)
#define PLAYER2_WALL_COLOR sf::Color::Red
#define GUI_BACKGROUND sf::Color(24, 24, 24)

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
    std::cout << "Render begin" << std::endl;
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

        window.clear(GUI_BACKGROUND);
        this->render();

        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}

void Board::render() {
    // Begin ImGui window for board settings
    ImGui::Begin("Board Settings");


    if(!pauseGame) ImGui::SliderFloat("Move Delay (ms)", &moveDelay, 0.0f, 10.0f); // Slider for timer delay

    ImGui::Checkbox("Show Calculation", &showCalculations);
    ImGui::Checkbox("Print Output", &showOutput);
    ImGui::Checkbox("Print Average round move times", &printAverages);



    if(!gameRunning) {
        // Dropdowns, buttons, etc.
        ImGui::Combo("Player 2 (Top)", &selectedPlayer2Type, playerTypes, IM_ARRAYSIZE(playerTypes));
        ImGui::Combo("Player 1 (Bottom)", &selectedPlayer1Type, playerTypes, IM_ARRAYSIZE(playerTypes));
        ImGui::SliderInt("Number of Rounds", rounds_p, 1, 1000); // Slider for number of rounds
    }

    if (!gameRunning && ImGui::Button("Run Rounds")) {

        if (!gameRunning) {
            gameRunning = true;
            // Start a new thread for GUI_play
            std::thread play_thread([&]() {
                game.wins = {0,0};
                int temp_rounds = *rounds_p;
                game.GUI_play(playerTypes[selectedPlayer1Type], playerTypes[selectedPlayer2Type], &moveDelay, rounds_p, &showOutput, &printAverages);
                // Once GUI_play completes, you can perform any follow-up actions here
                // For example, updating UI or setting flags
                gameRunning = false;
                *rounds_p = temp_rounds;
            });

            // Detach the thread so it runs independently
            play_thread.detach();
        }
    }

    if (gameRunning && ImGui::Button("Cancel Run")) {
        *rounds_p = 0;
    }

    ImGui::End();  // End ImGui window

    ImGui::Begin("Current/Last Game Info");
    if (gameRunning) {
        ImGui::Text("Rounds left: %d", *rounds_p);
        ImGui::Text("Player 2 Walls Left: %d", game_state_p->walls_per_player.second);
        ImGui::Text("Player 1 Walls Left: %d", game_state_p->walls_per_player.first);
    }
    else {

        ImGui::Text("Previous Score: %d - %d", game.wins[0], game.wins[1]);
    }
    ImGui::Text("--------------");
    ImGui::Text("Player 2 (Top)    : %s", playerTypes[selectedPlayer2Type]);
    ImGui::Text("Player 1 (Bottom) : %s", playerTypes[selectedPlayer1Type]);
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
            cellShape.setFillColor(GUI_BACKGROUND);
            cellShape.setOutlineThickness(1.f);
            cellShape.setOutlineColor(sf::Color(155,140,119));
            window.draw(cellShape);


            // Draw circles for player positions
            if (game_state_p->player1_pos.first == i && game_state_p->player1_pos.second == j) {
                sf::CircleShape playerCircle(0.5 * size / 2.f);
                playerCircle.setFillColor(PLAYER1_WALL_COLOR);  // Player 1 color
                playerCircle.setPosition(posX + 0.25*size, posY + 0.25*size);
                window.draw(playerCircle);
            }
            else if (game_state_p->player2_pos.first == i && game_state_p->player2_pos.second == j) {
                sf::CircleShape playerCircle(0.5 * size / 2.f);
                playerCircle.setFillColor(PLAYER2_WALL_COLOR);  // Player 2 color
                playerCircle.setPosition(posX + 0.25*size, posY + 0.25*size);
                window.draw(playerCircle);
            }

        }
    }

    // Draw the walls
    for (int i = 0; i < SIZE-1; ++i) {
        for (int j = 0; j < SIZE-1; ++j) {

            float posX = boardPos.x + j * CELL_SIZE;
            float posY = boardPos.y + i * CELL_SIZE;
            float size = CELL_SIZE;
            float cut = 0.8;

            if(game_state_p->is_ver_wall(i, j)){
                sf::RectangleShape vertWall(sf::Vector2f(WALL_THICKNESS, 2*size*cut));
                vertWall.setPosition(posX + size - WALL_THICKNESS/2, posY + (1-cut)*size - WALL_THICKNESS/2);
                int whichPlayerPlaced = game_state_p->whichPlayerPlacedWall(i, j);
                switch (whichPlayerPlaced) {
                    case 0:
                        vertWall.setFillColor(sf::Color::Magenta);
                        break;
                    case 1:
                        vertWall.setFillColor(PLAYER1_WALL_COLOR);
                        break;
                    case 2:
                        vertWall.setFillColor(PLAYER2_WALL_COLOR);
                        break;
                    default:
                        // Handle unexpected values of whichPlayerPlaced
                        // Possibly set a default color or do nothing
                        break;
                }
                if(whichPlayerPlaced || showCalculations) window.draw(vertWall);
            }

            if(game_state_p->is_hor_wall(i, j)){
                sf::RectangleShape horWall(sf::Vector2f(2*size*cut, WALL_THICKNESS));
                horWall.setPosition(posX + (1-cut)*size - WALL_THICKNESS/2, posY + size - WALL_THICKNESS/2);
                int whichPlayerPlaced = game_state_p->whichPlayerPlacedWall(i, j);
                switch (whichPlayerPlaced) {
                    case 0:
                        horWall.setFillColor(sf::Color::Magenta);
                        break;
                    case 1:
                        horWall.setFillColor(PLAYER1_WALL_COLOR);
                        break;
                    case 2:
                        horWall.setFillColor(PLAYER2_WALL_COLOR);
                        break;
                    default:
                        // Handle unexpected values of whichPlayerPlaced
                        // Possibly set a default color or do nothing
                        break;
                }
                if (whichPlayerPlaced || showCalculations) window.draw(horWall);
            }
        }
    }
}

void Board::handleMouseClick(sf::Vector2f mousePos) {
    // Convert mouse position to board coordinates
    int col = static_cast<int>((mousePos.x - boardPos.x) / CELL_SIZE);
    int row = static_cast<int>((mousePos.y - boardPos.y) / CELL_SIZE);

    // Toggle wall type at clicked position
    // if (row >= 0 && row < SIZE && col >= 0 && col < SIZE) {
    //     game_state_p->set_wall(row, col, row%2, 1);
    // }
}

void Board::kill(){
    delete rounds_p;
}
