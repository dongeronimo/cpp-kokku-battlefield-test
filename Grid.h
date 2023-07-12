#pragma once
#include <Vector>
#include "Types.h"

class Grid
{

public:
    const int CalculateIndex(int i, int j) const {
        return Columns() * i + j;
    }
    Grid(int Lines, int Columns);
    ~Grid();
    //voltei c vetor de ptrs pra n ter o custo de passagem por valor em 
    //drawBattlefield.
    std::vector<Types::GridBox*> grids;
    //Equivale ao J
    const int xLenght;
    //Equivale ao I
    const int yLength;
    //Criei pq ficar convertendo entre x/yLength e Linhas e Colunas me dá nó 
    //na cabeça e eu quero linguagem única.
    const int Lines() const {
        return yLength;
    }
    const int Columns() const {
        return xLenght;
    }
    // prints the matrix that indicates the tiles of the battlefield
    void drawBattlefield();
};

