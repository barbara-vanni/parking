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

    int gridRows = 6;
    int gridCols = 6;
    Grid grid(gridRows, gridCols, 3, 5);
    StockCar stockCar;

    Car carPlayer(0, 3, 2, 1, true, gridRows, gridCols, true);
    Car car2(4, 2, 1, 2, false, gridRows, gridCols);
    Car car3(3, 1, 1, 3, false, gridRows, gridCols);
    Car car4(3, 4, 2, 1, true, gridRows, gridCols);

    stockCar.addCar(carPlayer);
    stockCar.addCar(car2);
    stockCar.addCar(car3);
    stockCar.addCar(car4);

    std::cout << "nombre de voiture dans stockCar : " << stockCar.getStockCar().size() << std::endl;
    std::cout << "la fenetre est ouverte" << std::endl;

    std::vector<Button> buttons;
    Button buttonBegin(window.renderer, 100, 200, 200, 50, "Jouer", 30);
    buttons.push_back(buttonBegin);

    int selectedCarIndex = -1;
    mainLoop(window, grid, buttons, stockCar, selectedCarIndex);

    std::cout << "la fenetre est fermée" << std::endl;
    grid.~Grid();
    window.~Window();
    stockCar.~StockCar();
    closeGraphic();

    return EXIT_SUCCESS;
}
