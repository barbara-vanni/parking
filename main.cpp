#include "game/graphic_game/hpp_files/Window.hpp"
#include "game/logic_game/hpp_files/Car.hpp"
#include "game/Grid.hpp"
#include "game/gameLoop.hpp" 
#include "game/graphic_game/hpp_files/graphicInit.hpp"

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

    mainLoop(window, grid, car);

    std::cout << "la fenetre est fermée" << std::endl;
    grid.~Grid();
    window.~Window();
    car.~Car();
    closeGraphic();
    return EXIT_SUCCESS;
}

