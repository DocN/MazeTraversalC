#ifndef CELL_H
#define CELL_H

#include <iostream>

// for Lab VI in CPSC 2150 by Gladys Monagan

// a cell stores two values corresponding to the row and column
struct Cell {
   public:
	int i,j;
	bool left,right,up,down;
};

// define the insertion operator << to have the cell formatted as (i,j)
std::ostream& operator << (std::ostream& out, Cell  x); 

#endif  

