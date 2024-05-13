#include <iostream>
using namespace std;

const int NORTH = 0;
const int WEST = 1;
const int SOUTH = 2;
const int EAST = 3;

class Grid
{
public:

   Grid(int r, int c, int mr, int mc, int d); // build empty grid with r rows, c cols, and mover at row mr, col mc, and facing direction d

   // bool Move(int s);		// move forward s spaces, if possible
   
   // void TogglePath();		// toggle whether or not moved path is shown
   
   // void TurnLeft();		// turn the mover to the left
   
   // bool PickUp();		// pick up item at current position

   void Display() const;	// display the grid on screen. Accessors
   
   // bool FrontIsClear() const;	// check to see if space in front of  mover is clear
   
   // bool RightIsClear() const;	// check to see if space to right of mover is clear
   
   // int GetRow() const;		// return row of the mover
   
   // int GetCol() const;		// return column of the mover
   
   // int GetNumRows() const;	// return number of rows in the grid
   
   // int GetNumCols() const;	// return number of columns in the grid
   
private:

   char** grid;
   
   int mover_r, mover_c, mover_d, maxRow, maxCol;
   
   bool path;

};