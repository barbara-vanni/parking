#ifndef GAMELOOP_HPP
#define GAMELOOP_HPP
#include <vector>
#include "graphic_game/hpp_files/Button.hpp"
#include "graphic_game/hpp_files/Window.hpp"
#include "logic_game/hpp_files/Car.hpp"
#include "logic_game/hpp_files/StockCar.hpp"
#include "Grid.hpp"

void mainLoop(Window& window, Grid& grid, std::vector<Button*>& buttons, StockCar& stockCar, int& selectedCarIndex);
void introPage(Window& window, std::vector<Button*>& buttons, std::vector<SDL_Texture*>& gifFrames, int currentFrame);
void menuPage(Window& window, std::vector<Button*>& buttons, bool& levelSelected);
#endif 
