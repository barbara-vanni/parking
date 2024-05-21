#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "Grid.hpp" 
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// class Grid implementation
// Constructor to build the grid with r rows, c cols, blocks around edge with random exit


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
    grid[exitRow][exitCol] = ' ';
}

Grid::~Grid()
{
    for(int i = 0; i < maxRow; i++)
        delete [] grid[i];
    delete [] grid;
    if (carPlayerTexture) SDL_DestroyTexture(carPlayerTexture);
    if (verticalCarTexture) SDL_DestroyTexture(verticalCarTexture);
    if (horizontalCarTexture) SDL_DestroyTexture(horizontalCarTexture);
    if (busTexture) SDL_DestroyTexture(busTexture);
    if (horizontalBusTexture) SDL_DestroyTexture(horizontalBusTexture);
}

void Grid::loadCarTextures(SDL_Renderer* renderer) {
   carPlayerTexture = IMG_LoadTexture(renderer, "assets/images/car_player.png");
   verticalCarTexture = IMG_LoadTexture(renderer, "assets/images/cars.png");
   horizontalCarTexture = IMG_LoadTexture(renderer, "assets/images/horizontal_cars.png");
   busTexture = IMG_LoadTexture(renderer, "assets/images/bus.png");
   horizontalBusTexture = IMG_LoadTexture(renderer, "assets/images/horizontal_bus.png");

   if (!carPlayerTexture || !verticalCarTexture || !horizontalCarTexture || !busTexture || !horizontalBusTexture) {
      std::cerr << "Erreur lors du chargement des textures des voitures : " << IMG_GetError() << std::endl;
   }
}

void Grid::renderCars(SDL_Renderer* renderer) const {
    for (const Car& car : stockCar) {
        SDL_Texture* carTexture = nullptr;

        
      if (car.getName() == "carPlayer"){
         carTexture = carPlayerTexture;  
      }if ((car.getWidth() == 3 || car.getHeight() == 3) && car.isHorizontalOrientation()) {
         carTexture = horizontalBusTexture;  
      } if ((car.getWidth() == 3 || car.getHeight() == 3) && !car.isHorizontalOrientation()) {
         carTexture = busTexture; 
      } if (car.getWidth() == 2 && car.getName() == ""){
         carTexture = horizontalCarTexture;  
      } if ((car.getWidth() == 1 && car.getHeight() == 2) && !car.isHorizontalOrientation()) {
         carTexture = verticalCarTexture;  
      }


        if (carTexture) {
            SDL_Rect carRect;
            carRect.x = car.getPosX() * 110;
            carRect.y = car.getPosY() * 110;
            carRect.w = car.getWidth() * 110;
            carRect.h = car.getHeight() * 110;

            SDL_RenderCopy(renderer, carTexture, NULL, &carRect);
        }
    }
}

void Grid::DisplayOnScreen(SDL_Window* window, SDL_Renderer* renderer) const {
    if (renderer == nullptr) {
        std::cerr << "Renderer is null!" << std::endl;
        return;
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect rect;
    rect.w = 100;
    rect.h = 100;

    for (int i = 0; i < maxRow; i++) {
        for (int j = 0; j < maxCol; j++) {
            rect.x = j * 110;
            rect.y = i * 110;
            if (grid[i][j] == '_') {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &rect);
            } else if (grid[i][j] == ' ') {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                SDL_RenderFillRect(renderer, &rect);
            } else {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    renderCars(renderer);

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

