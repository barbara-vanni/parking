#ifndef GAMELOOP_HPP
#define GAMELOOP_HPP

#include <vector>
#include "graphic_game/hpp_files/Button.hpp"
#include "graphic_game/hpp_files/Window.hpp"
#include "Grid.hpp"

// Prototype de la fonction gameLoop
void mainLoop(Window& window, Grid& grid, std::vector<Button>& buttons);
void introPage(Window& window, std::vector<Button>& buttons);

#endif 
