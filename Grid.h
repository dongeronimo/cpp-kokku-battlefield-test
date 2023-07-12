#pragma once
#include <Vector>
#include "Types.h"

class Grid
{
private:
    const int CalculateIndex(int i, int j) const{
        return Columns() * i + j;
    }
public:

    Grid(int Lines, int Columns);
    ~Grid();

    std::vector<Types::GridBox*> grids;
    //Equivale ao J
    const int xLenght;
    //Equivale ao I
    const int yLength;
    
    const int Lines() const {
        return yLength;
    }
    const int Columns() const {
        return xLenght;
    }
    // prints the matrix that indicates the tiles of the battlefield
    void drawBattlefield();
};

