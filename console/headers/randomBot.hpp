// randomBot.hpp

#ifndef RANDOMBOT_H
#define RANDOMBOT_H

#include "game_state.hpp"
#include <iostream>
#include <vector>
#include <random>

std::vector<int> randombot_action(GameState& game_state);

#endif // RANDOMBOT_H