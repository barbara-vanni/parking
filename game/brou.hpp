#ifndef BROU_HPP
#define BROU_HPP

#include <iostream>
#include <SDL2/SDL.h>
using namespace std;

const int NORTH = 0;
const int WEST = 1;
const int SOUTH = 2;
const int EAST = 3;

class Grid
{
public:

   Grid(int r, int c, int mr, int mc, int d, int size); // build empty grid with r rows, c cols, and mover at row mr, col mc, and facing direction d
   void Display() const;
   void DisplayOnScreen(SDL_Window* window, SDL_Renderer* renderer) const;
   bool Move(int s); // move forward s steps
   bool FrontIsClear() const;

private:

   char** grid;
   
   int mover_r, mover_c, mover_d, maxRow, maxCol, mover_size;
   
   bool path;

};

#endif 