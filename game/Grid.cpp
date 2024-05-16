#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "Grid.hpp" 
#include <SDL2/SDL.h>

// Grid::Grid(int r, int c, int mr, int mc, int d, int size)
// : mover_size(size) //make empty grid with r rows, c cols, and mover, at row mr, col mc, and facing direction d
// {
//    if(r < 0 || c < 0)
//    {
//       maxRow = 1;
//       maxCol = 1;
//    }
//    else if(r > 40 || c > 40)
//    {
//       maxRow = 40;
//       maxCol = 40;
//    }
//    else
//    {
//       maxRow = r;    
//       maxCol = c;
//    }
   
//    grid = new char* [maxRow];
//    for(int i = 0; i < maxRow; i++)
//       grid[i] = new char [maxCol];

//    path = true;
   
//    for(int i = 0; i < maxRow; i++)
//       for(int j = 0; j < maxCol; j++)
//          grid[i][j] = '_';
   
//    if(mr > maxRow)
//       mr = maxRow-1;
//    else if(mr < 0)
//       mr = 0;
   
//    if(mc > maxCol)
//       mc = maxCol-1;
//    else if(mc < 0)
//       mc = 0;
      
//    mover_r = mr;
//    mover_c = mc;
//    mover_d = d;
// }

Grid::Grid()			// check task: build the grid with mover in only square, facing east
{
   grid = new char* [1];    // may I need to remove * in order to make this less painfull 
   grid[0] = new char [1];
   mover_r = 0;
   mover_c = 0;
   mover_d = EAST;
   path = true;
}

Grid::Grid(int r, int c) // build grid with r rows, c cols,  blocks around edge with random exit
// and random mover position and direction
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
   
   //populates grid with '#' and '.'
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
   srand(time(0));

   int r_n = rand() % maxRow,
   r_exit = rand() % maxRow,
   c_n = rand() % maxCol,
   c_exit = rand() % maxCol,
   direction = rand() % 4,
   edge = rand() % 4;
   
   //exit
   switch(edge)
   {
      case NORTH:
         grid[0][c_exit] = ' ';
         break;
      case SOUTH:
         grid[maxRow-1][c_exit] = ' ';
         break;
      case WEST:
         grid[r_exit][0] = ' ';
         break;
      case EAST:
         grid[r_exit][maxCol-1] = ' ';
         break;
   }
   //mover placement
   mover_r = r_n;
   mover_c = c_n;
   mover_d = direction;
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
            
            if(i == mover_r && j >= mover_c && j < mover_c + mover_size)
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

bool Grid::FrontIsClear() const	// check to see if space in front of mover is clear
{
   switch(mover_d)
   {
      case NORTH:
         if(grid[mover_r-1][mover_c] != '#')
            return true;
         else
            return false;
         break;
      case WEST:
         if(grid[mover_r][mover_c-1] != '#')
            return true;
         else
            return false;
         break;
      case EAST:
         if(grid[mover_r][mover_c+1] != '#')
            return true;
         else
            return false;
         break;
      case SOUTH:
         if(grid[mover_r+1][mover_c] != '#')
            return true;
         else
            return false;
         break;
   }
}


bool Grid::Move(int s)	// move forward s spaces, if possible
{
   int temp;
   bool flag = false;
   
   switch(mover_d) {
      
      case NORTH:
         if(s > 0) {
            
            if(mover_r - s >= 0) {
               
               temp = mover_r;
               
               for(int i = 0; i < s; i++)
               {
                  if( FrontIsClear())
                  {
                     flag = true;
                     if(grid[mover_r][mover_c] != '0')
                        grid[mover_r][mover_c] = ' ';
                     mover_r--;
                     
                  } else    flag = false;
               }
               
               if(flag == false)  mover_r = temp;
               
               else return true;
            }
         }
         return false;
         break;
      case SOUTH:
        if(s > 0) {
           
            if(mover_r + s <= maxRow)
            {
               temp = mover_r;
               for(int i = 0; i < s; i++)
               {
                  if( FrontIsClear())  {
                     
                     flag = true;
                     if(grid[mover_r][mover_c] != '0')
                        grid[mover_r][mover_c] = ' ';
                     mover_r++; 
                     
                  } else flag = false;
               }
               
               if(flag == false) mover_r = temp;
               
               else  return true;
            }
         }
         return false;
         break;
      case EAST:
      if(s > 0)
         {
            if(mover_c + s <= maxCol)
            {
               temp = mover_c;
               for(int i = 0; i < s; i++)
               {
                  if( FrontIsClear())
                  {
                     flag = true;
                     if(grid[mover_r][mover_c] != '0')
                        grid[mover_r][mover_c] = ' ';
                     mover_c++;
                     
                  } else flag = false;
               }
               
               if(flag == false)
                  mover_c = temp;
                  
               else  return true;
            }
         }
         return false;
         break;
      case WEST:
      if(s > 0)
         {
            if(mover_c - s >= 0) {
               
               temp = mover_c;
              for(int i = 0; i < s; i++)
              {
                  if( FrontIsClear())
                  {
                     flag = true;
                     if(grid[mover_r][mover_c] != '0')
                        grid[mover_r][mover_c] = ' ';
                     mover_c--; 
                     
                  } else flag = false;
               }
               
               if(flag == false)
                  mover_c = temp;
                  
               else  return true;
            }
         }
         return false;
         break;
   }
} 


