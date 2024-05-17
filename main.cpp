#include "game/graphic_game/hpp_files/Window.hpp"
#include "game/logic_game/hpp_files/Car.hpp"
#include "game/logic_game/hpp_files/StockCar.hpp"
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
    StockCar stockCar;
    // Car car(2, 2, 2, 1, true);
    Car car1(4, 4, 1, 2, false);
    Car car2(2, 2, 2, 1, true);
    Car car3(1, 1, 3, 1, false);
    stockCar.addCar(car1);
    stockCar.addCar(car2);
    stockCar.addCar(car3);

    std::cout<< "nombre de voiture dans stockCar : " << stockCar.getStockCar().size() << std::endl;

    std::cout << "la fenetre est ouverte" << std::endl;

    std::vector<Button> buttons;
    Button buttonBegin(window.renderer, 100, 200, 200, 50, "Jouer", 30);
    buttons.push_back(buttonBegin);

    mainLoop(window, grid, buttons, stockCar);

    std::cout << "la fenetre est fermée" << std::endl;
    grid.~Grid();
    window.~Window();
    stockCar.~StockCar();
    closeGraphic();
    window.~Window();


    return EXIT_SUCCESS;
}

