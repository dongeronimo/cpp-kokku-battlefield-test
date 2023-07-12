#include "Grid.h"
#include "Types.h"
#include <iostream>
#include <sstream>
using namespace std;

Grid::Grid(int Lines, int Columns)
    :xLenght(Columns), yLength(Lines)//Inicialização passou a ser aqui pq to usando dimensões constantes. O que não muda deve ser sempre constante
{
    for (int i = 0; i < Lines; i++)
    {
        for (int j = 0; j < Columns; j++)
        {
            Types::GridBox* newBox = new Types::GridBox(i, j, false, CalculateIndex(i,j));
            grids.push_back(newBox);
            cout<<newBox->Index<<endl;
        }
    }
    cout << "the battlefield has been created" << endl;
	drawBattlefield();
}

Grid::~Grid() 
{
    //O código original não tinha dealocação do que foi alocado no ctor.
    for (auto i : grids) {
        delete(i);
    }
}

void Grid::drawBattlefield()
{
    //Usando stringstream pra acumular pra reduzir a qtd de operações
    //de output e fazer o output todo de uma vez.
    std::stringstream ss;
    for (int i = 0; i < Lines(); i++)
    {
        for (int j = 0; j < Columns(); j++)
        {
            Types::GridBox* currentGrid = grids[CalculateIndex(i, j)];
            if (currentGrid->ocupied) {
                ss << "[x]";
            }
            else {
                ss << "[ ]";
            }
        }
        ss << endl;
    }
    std::cout << ss.str() << endl;
}