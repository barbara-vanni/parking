#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "Grid.hpp" 
#include <SDL2/SDL.h>

Grid::Grid(int r, int c, int exitRow, int exitCol) : exitRow(exitRow), exitCol(exitCol) {
    if(r < 4 || c < 4) {
        maxRow = 3;
        maxCol = 3;
    } else if(r > 40 || c > 40) {
        maxRow = 40;
        maxCol = 40;
    } else {
        maxRow = r;
        maxCol = c;
    }
    grid = new char* [maxRow];
    for(int i = 0; i < maxRow; i++)
        grid[i] = new char [maxCol];

    // Remplit la grille avec '#' et '.'
    for(int i = 0; i < maxRow; i++) {
        for(int j = 0; j < maxCol; j++) {
            if(i == 0 || i == maxRow-1)
                grid[i][j] = '#';
            else if(j == 0 || j == maxCol-1)
                grid[i][j] = '#';
            else
                grid[i][j] = '.';
        }
    }

    path = true;
    grid [exitRow][exitCol] = ' ';
    selectedCar = nullptr;

    // Place la sortie aux coordonnées spécifiées
    grid[exitRow][exitCol] = ' ';
}

Grid::~Grid()
{
    for(int i = 0; i < maxRow; i++)
        delete [] grid[i];
    delete [] grid;
}

void Grid::DisplayOnScreen(SDL_Window* window, SDL_Renderer* renderer) const
{
   if (renderer == nullptr) {
      std::cerr << "Renderer is null!" << std::endl;
      return;
   }

   SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
   SDL_RenderClear(renderer);

   SDL_Rect rect;
   rect.w = 100;
   rect.h = 100;
   
   for(int i = 0; i < maxRow; i++)
   {
      for(int j = 0; j < maxCol; j++)
      {
         rect.x = j * 110;
         rect.y = i * 110;

         if(grid[i][j] == '_')
         {
               SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
               SDL_RenderFillRect(renderer, &rect);
         }
         else if(grid[i][j] == ' ')
         {
               SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
               SDL_RenderFillRect(renderer, &rect);
         }
         else
         {
               SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
               SDL_RenderFillRect(renderer, &rect);
         }
      }
   }
   if (car != nullptr) {
      SDL_Rect carRect;
      if (car == selectedCar){
         SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
      } else {
         SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
      }
      if (car->isHorizontalOrientation()) {
         // Si horizontalOrientation est true
         carRect.w = car->getWidth() * 105;
         carRect.h = car->getHeight() * 100;
      } else {
         // Si horizontalOrientation est false
         carRect.w = car->getWidth() * 100;
         carRect.h = car->getHeight() * 105;
      }
      carRect.x = car->getPosX() * 110;
      carRect.y = car->getPosY() * 110;

      SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); 
      SDL_RenderFillRect(renderer, &carRect);
   }
      for (const Car& otherCar : stockCar) {
      SDL_Rect carRect;
      if (otherCar.isHorizontalOrientation() && otherCar.getWidth() == 3) {
         carRect.w = otherCar.getWidth() * 107;
         carRect.h = otherCar.getHeight() * 100;
      } else if (!otherCar.isHorizontalOrientation() && otherCar.getHeight() == 3) {
         carRect.w = otherCar.getWidth() * 100;
         carRect.h = otherCar.getHeight() * 107;
      }
      else if (otherCar.isHorizontalOrientation() && otherCar.getWidth() == 2){
         carRect.w = otherCar.getWidth() * 105;
         carRect.h = otherCar.getHeight() * 100;
      } else if (!otherCar.isHorizontalOrientation() && otherCar.getHeight() == 2){
         carRect.w = otherCar.getWidth() * 100;
         carRect.h = otherCar.getHeight() * 105;
      }
      else {
         carRect.w = otherCar.getWidth() * 100;
         carRect.h = otherCar.getHeight() * 105;
      }
      carRect.x = otherCar.getPosX() * 110;
      carRect.y = otherCar.getPosY() * 110;

      SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); 
      SDL_RenderFillRect(renderer, &carRect);
   }
   SDL_RenderPresent(renderer);
}

void Grid::setCar(const Car& car){
   this->car = &car;
}

void Grid::setStockCar(const std::vector<Car>& stockCar) {
    this->stockCar = stockCar;
}

void Grid::setSelectedCar(const Car* car){
   selectedCar = car;
}

