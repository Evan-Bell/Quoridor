#include "game.hpp"
#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include <iostream>

// responsible for the GUI



class Board{
private:
  int selectedWallType = 0; // Index of selected wall type
  bool showGrid = true;

public:
  GameState game_state;

  Board();

  void render(sf::RenderWindow& window, ImVec2 boardPos);

  void handleMouseClick(sf::Vector2f mousePos, ImVec2 boardPos);
};