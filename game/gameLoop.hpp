#ifndef GAMELOOP_HPP
#define GAMELOOP_HPP

#include <vector>
#include "graphic_game/hpp_files/Button.hpp"
#include "graphic_game/hpp_files/Window.hpp"
#include "logic_game/hpp_files/Car.hpp"
#include "Grid.hpp"


void mainLoop(Window& window, Grid& grid, std::vector<Button*>& buttons, Car& car);
void introPage(Window& window, std::vector<Button*>& buttons);
void menuPage(Window& window, std::vector<Button*>& buttons);

#endif 
