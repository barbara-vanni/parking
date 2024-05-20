#include "game/graphic_game/hpp_files/Window.hpp"
#include "game/logic_game/hpp_files/Car.hpp"
#include "game/logic_game/hpp_files/StockCar.hpp"
#include "game/Grid.hpp"
#include "game/gameLoop.hpp"
#include "game/graphic_game/hpp_files/graphicInit.hpp"
#include "game/graphic_game/hpp_files/Button.hpp"
#include <iostream>
#include <vector>
#include <vld.h>

int main(int argc, char *argv[]) {
    if (!initGraphic()) {
        std::cout << "Failed to initialize graphics. Exiting." << std::endl;
        return 1;
    }

    Window window("Intro", 1500, 720);
    // int* leak = new int[100]; 

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

    std::vector<Button*> buttons;
    Button* buttonBegin = new Button(window.renderer, 650, 600, 200, 50, "Start", 30);
    Button* buttonPlay = new Button(window.renderer, 1250, 650, 200, 50, "Play", 30);
    Button* buttonLevel1 = new Button(window.renderer, 300, 550, 100, 80, "1", 30);
    Button* buttonLevel2 = new Button(window.renderer, 700, 550, 100, 80, "2", 30);
    Button* buttonLevel3 = new Button(window.renderer, 1100, 550, 100, 80, "3", 30);

    buttons.push_back(buttonBegin);
    buttons.push_back(buttonPlay);
    buttons.push_back(buttonLevel1);
    buttons.push_back(buttonLevel2);
    buttons.push_back(buttonLevel3);

    int selectedCarIndex = -1;
    mainLoop(window, grid, buttons, stockCar, selectedCarIndex);

    if(VLDReportLeaks() == 0)
        std::cout << "No Memory Leaks" << std::endl;
    else
        std::cout << "Memory Leaks" << std::endl;



    std::cout << "la fenetre est fermée" << std::endl;
    grid.~Grid();
    window.~Window();
    stockCar.~StockCar();
    closeGraphic();

    return EXIT_SUCCESS;
}
