#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "Grid.hpp" 
#include <SDL2/SDL.h>

Grid::Grid(int r, int c, int mr, int mc, int d) //make empty grid with r rows, c cols, and mover, at row mr, col mc, and facing direction d
{
   if(r < 0 || c < 0)
   {
      maxRow = 1;
      maxCol = 1;
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

   path = true;
   
   for(int i = 0; i < maxRow; i++)
      for(int j = 0; j < maxCol; j++)
         grid[i][j] = '_';
   
   if(mr > maxRow)
      mr = maxRow-1;
   else if(mr < 0)
      mr = 0;
   
   if(mc > maxCol)
      mc = maxCol-1;
   else if(mc < 0)
      mc = 0;
      
   mover_r = mr;
   mover_c = mc;
   mover_d = d;
}


void Grid::Display() const	// display the grid on terminal
{
   cout << "The Grid:\n";
   
   for(int i = 0; i < maxRow; i++)
   {
      for(int j = 0; j < maxCol; j++)
      {
         if(i == mover_r && j == mover_c)
         {
            if(grid[i][j] == '0')
               cout << '@';
            else
               switch(mover_d)
               {
                  case NORTH:
                     cout << '^';
                     break;
                  case WEST:
                     cout << '<';
                     break;
                  case SOUTH:
                     cout << 'v';
                     break;
                  case EAST:
                     cout << '>';
                     break;
               }
         }
         else if(grid[i][j] == ' ' && path == false)
               cout << '.';
         else if(path == true)
            cout << grid[i][j];
            
         cout << " ";
      }
      cout << endl;
   }
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
            // std::cout << grid[i][j];
            rect.x = j*110;
            rect.y = i*110;
            
            if(i == mover_r && j == mover_c)
            {
                switch(mover_d)
                {
                    case NORTH:
                        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                        break;
                    case WEST:
                        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                        break;
                    case SOUTH:
                        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                        break;
                    case EAST:
                        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                        break;
                }
            }
            else if(grid[i][j] == '_')
            {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
            }

            SDL_RenderFillRect(renderer, &rect);
        }
        // cout << endl;
    }
    SDL_RenderPresent(renderer);
}



