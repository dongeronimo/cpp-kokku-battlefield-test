#pragma once
#include <Vector>
#include "Types.h"

class Grid
{

public:

    Grid(int Lines, int Columns);
    ~Grid();

    std::vector<Types::GridBox> grids;
    //Equivale ao J
    const int xLenght;
    //Equivale ao I
    const int yLength;
    
    // prints the matrix that indicates the tiles of the battlefield
    void drawBattlefield();
};

