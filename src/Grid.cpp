#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "hpp/Grid.hpp" 

using namespace std;



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
      maxRow = r;    //initialization of maxRow and maxCol
      maxCol = c;
   }
   
   grid = new char* [maxRow];
   for(int i = 0; i < maxRow; i++)
      grid[i] = new char [maxCol];

   path = true;
   
   //set up grid
   for(int i = 0; i < maxRow; i++)
      for(int j = 0; j < maxCol; j++)
         grid[i][j] = '.';
   
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


void Grid::Display() const {
    for (int i = 0; i < maxRow; i++) {
        for (int j = 0; j < maxCol; j++) {
            std::cout << grid[i][j] << " *";
        }
        std::cout << std::endl;
    }
}

