#include "Grid.h"
#include "Types.h"
#include <iostream>

using namespace std;
Grid::Grid(int Lines, int Columns)
    :xLenght(Columns), yLength(Lines)
{
    for (int i = 0; i < Lines; i++)
    {
        for (int j = 0; j < Columns; j++)
        {
            Types::GridBox newBox(i, j, false, (Columns * i + j));
            grids.push_back(newBox);
            cout<<newBox.Index<<endl;
        }
    }
    cout << "the battlefield has been created" << endl;
	//drawBattlefield(Lines, Columns);
}

Grid::~Grid() 
{

}

void Grid::drawBattlefield(int Lines, int Columns)
{
    for (int i = 0; i < Lines; i++)
    {
        for (int j = 0; j < Columns; j++)
        {
            Types::GridBox* currentgrid = new Types::GridBox();
            if (currentgrid->ocupied)
            {
                //if()
                printf("[X]\t");
            }
            else
            {
                printf("[ ]\t");
            }
        }
        printf("\n");
    }
    printf("\n");
}