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

    std::vector<Button*> buttons;
    Button* buttonBegin = new Button(window.renderer, 100, 200, 200, 50, "Start", 30);
    Button* buttonPlay = new Button(window.renderer, 600, 600, 200, 50, "Play", 30);
    Button* buttonLevel1 = new Button(window.renderer, 250, 200, 100, 80, "1", 30);
    Button* buttonLevel2 = new Button(window.renderer, 650, 200, 100, 80, "2", 30);
    Button* buttonLevel3 = new Button(window.renderer, 1050, 200, 100, 80, "3", 30);

    buttons.push_back(buttonBegin);
    buttons.push_back(buttonPlay);
    buttons.push_back(buttonLevel1);
    buttons.push_back(buttonLevel2);
    buttons.push_back(buttonLevel3);

    mainLoop(window, grid, buttons, car);

    std::cout << "la fenetre est fermée" << std::endl;
    grid.~Grid();
    window.~Window();
    car.~Car();
    for (Button* button : buttons){
        button->~Button();
    }
    closeGraphic();
    window.~Window();


    return EXIT_SUCCESS;
}

