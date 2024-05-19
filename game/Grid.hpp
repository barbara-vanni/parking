#ifndef GRID_HPP
#define GRID_HPP

#include <iostream>
#include "logic_game/hpp_files/Car.hpp"
#include "logic_game/hpp_files/StockCar.hpp"
#include <SDL2/SDL.h>
using namespace std;

const int NORTH = 0;
const int WEST = 1;
const int SOUTH = 2;
const int EAST = 3;

class Grid
{
public:
   Grid(int r, int c, int exitRow, int exitCol); // build grid with r rows, c cols,  blocks around edge with random exit
   void setCar(const Car& car);
   void DisplayOnScreen(SDL_Window* window, SDL_Renderer* renderer) const;
   void setStockCar(const std::vector<Car>& stockCar);
   void setSelectedCar(const Car* car);
   int getWidth() const { return maxCol; };
   int getHeight() const { return maxRow; };
   int getExitRow() const { return exitRow; };
   int getExitCol() const { return exitCol; };
   ~Grid();

private:

   char** grid;
   int maxRow, maxCol;
   int exitRow, exitCol;
   bool path;
   const Car* car;
   const Car* selectedCar;
   std::vector<Car> stockCar;

};

#endif 