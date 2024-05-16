#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "Grid.hpp" 
#include <SDL2/SDL.h>

Grid::Grid(int r, int c, int exitRow, int exitCol)
{
    if(r < 4 || c < 4)
    {
        maxRow = 3;
        maxCol = 3;
    }
    else if(r > 40 || c > 40)
    {
        maxRow = 40;
        maxCol = 40;
    }
    else
    {
        maxRow = r;
        maxCol = c;
    }
    grid = new char* [maxRow];
    for(int i = 0; i < maxRow; i++)
        grid[i] = new char [maxCol];

    // Remplit la grille avec '#' et '.'
    for(int i = 0; i <  maxRow; i++)
    {
        for(int j = 0; j < maxCol; j++)
        {
            if(i == 0 || i == maxRow-1)
                grid[i][j] = '#';
            else if(j == 0 || j == maxCol-1)
                grid[i][j] = '#';
            else
                grid[i][j] = '.';
        }
    }

    path = true;

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
               // Dessiner une case vide
               SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
               SDL_RenderFillRect(renderer, &rect);
         }
         else if(grid[i][j] == ' ')
         {
               // Dessiner la sortie
               SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
               SDL_RenderFillRect(renderer, &rect);
         }
         else
         {
               // Dessiner un mur
               SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
               SDL_RenderFillRect(renderer, &rect);
         }
      }
   }
   if (car != nullptr) {
      SDL_Rect carRect;
      carRect.w = car->getWidth() * 105; // Ajuster la taille en fonction de la taille de la voiture et de la grille
      carRect.h = car->getHeight() * 100;
      carRect.x = car->getPosX() * 110; // Ajuster les coordonnées en fonction de la position de la voiture et de la grille
      carRect.y = car->getPosY() * 110;

      SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Dessiner la voiture en bleu par exemple
      SDL_RenderFillRect(renderer, &carRect);
   }
   SDL_RenderPresent(renderer);
}

void Grid::setCar(const Car& car){
   this->car = &car;
}

// bool Grid::FrontIsClear() const	// check to see if space in front of mover is clear
// {
//    switch(mover_d)
//    {
//       case NORTH:
//          if(grid[mover_r-1][mover_c] != '#')
//             return true;
//          else
//             return false;
//          break;
//       case WEST:
//          if(grid[mover_r][mover_c-1] != '#')
//             return true;
//          else
//             return false;
//          break;
//       case EAST:
//          if(grid[mover_r][mover_c+1] != '#')
//             return true;
//          else
//             return false;
//          break;
//       case SOUTH:
//          if(grid[mover_r+1][mover_c] != '#')
//             return true;
//          else
//             return false;
//          break;
//    }
//    return false;
// }


// bool Grid::Move(int s)	// move forward s spaces, if possible
// {
//    int temp;
//    bool flag = false;
   
//    switch(mover_d) {
      
//       case NORTH:
//          if(s > 0) {
            
//             if(mover_r - s >= 0) {
               
//                temp = mover_r;
               
//                for(int i = 0; i < s; i++)
//                {
//                   if( FrontIsClear())
//                   {
//                      flag = true;
//                      if(grid[mover_r][mover_c] != '0')
//                         grid[mover_r][mover_c] = ' ';
//                      mover_r--;
                     
//                   } else    flag = false;
//                }
               
//                if(flag == false)  mover_r = temp;
               
//                else return true;
//             }
//          }
//          return false;
//          break;
//       case SOUTH:
//         if(s > 0) {
           
//             if(mover_r + s <= maxRow)
//             {
//                temp = mover_r;
//                for(int i = 0; i < s; i++)
//                {
//                   if( FrontIsClear())  {
                     
//                      flag = true;
//                      if(grid[mover_r][mover_c] != '0')
//                         grid[mover_r][mover_c] = ' ';
//                      mover_r++; 
                     
//                   } else flag = false;
//                }
               
//                if(flag == false) mover_r = temp;
               
//                else  return true;
//             }
//          }
//          return false;
//          break;
//       case EAST:
//       if(s > 0)
//          {
//             if(mover_c + s <= maxCol)
//             {
//                temp = mover_c;
//                for(int i = 0; i < s; i++)
//                {
//                   if( FrontIsClear())
//                   {
//                      flag = true;
//                      if(grid[mover_r][mover_c] != '0')
//                         grid[mover_r][mover_c] = ' ';
//                      mover_c++;
                     
//                   } else flag = false;
//                }
               
//                if(flag == false)
//                   mover_c = temp;
                  
//                else  return true;
//             }
//          }
//          return false;
//          break;
//       case WEST:
//       if(s > 0)
//          {
//             if(mover_c - s >= 0) {
               
//                temp = mover_c;
//               for(int i = 0; i < s; i++)
//               {
//                   if( FrontIsClear())
//                   {
//                      flag = true;
//                      if(grid[mover_r][mover_c] != '0')
//                         grid[mover_r][mover_c] = ' ';
//                      mover_c--; 
                     
//                   } else flag = false;
//                }
               
//                if(flag == false)
//                   mover_c = temp;
                  
//                else  return true;
//             }
//          }
//          break;
//    }
//     return false;
// } 

