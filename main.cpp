#include "game/graphic_game/hpp_files/Window.hpp"
#include "game/logic_game/hpp_files/Car.hpp"
#include "game/Grid.hpp"
#include "game/gameLoop.hpp" 
#include "game/graphic_game/hpp_files/graphicInit.hpp"
#include "game/graphic_game/hpp_files/Button.hpp"
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
    
    if (!initGraphic()) {
        std::cout << "Failed to initialize graphics. Exiting." << std::endl;
        return 1;
    }

    Window window("Intro", 1500, 720);

    Grid grid(6, 6, 3, 5);

    Car car(2, 2, 2, 1, true);
    // Car car(4, 4, 1, 2, false);

    std::cout << "la fenetre est ouverte" << std::endl;

    std::vector<Button> buttons;
    Button buttonBegin(window.renderer, 100, 200, 200, 50, "Jouer", 30);
    buttons.push_back(buttonBegin);

    mainLoop(window, grid, buttons, car);

    std::cout << "la fenetre est fermée" << std::endl;
    grid.~Grid();
    window.~Window();
    car.~Car();
    closeGraphic();
    window.~Window();


    return EXIT_SUCCESS;
}

