#include "game.hpp"
#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/System/Clock.hpp>
#include <string> // For std::to_string
#include <memory>

// responsible for the GUI

#define CELL_SIZE (400/WALLS)


class Board {
private:
  int selectedPlayer1Type = 0; // Index of selected player 1
  int selectedPlayer2Type = 0; // Index of selected player 2
  const char* playerTypes[3] = { "random", "alpha-beta-minimax", "simple path search"};
  bool gameRunning = false;

public:
  Game game;
  sf::RenderWindow& window;
  ImVec2 boardPos;

  std::shared_ptr<GameState> game_state_p;

  Board(Game& game, sf::RenderWindow& window, ImVec2 boardPos);

  int start();

  void render();

  void handleMouseClick(sf::Vector2f mousePos);
};