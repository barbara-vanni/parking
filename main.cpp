#include "game/graphic_game/hpp_files/Window.hpp"
#include "game/Grid.hpp"
#include "game/gameLoop.hpp" 
#include "game/graphic_game/hpp_files/graphicInit.hpp"

int main(int argc, char *argv[]) {
    
    if (!initGraphic()) {
        std::cout << "Failed to initialize graphics. Exiting." << std::endl;
        return 1;
    }

    Window window("Intro", 1500, 720);

    Grid grid(6, 6, 3, 0, 3, 1);

    std::cout << "la fenetre est ouverte" << std::endl;

    mainLoop(window, grid);

    std::cout << "la fenetre est fermée" << std::endl;

    closeGraphic();

    window.~Window();

    return EXIT_SUCCESS;
}

