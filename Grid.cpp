#include "Grid.h"
#include "Types.h"
#include <iostream>
#include <sstream>
#include "Character.h"
using namespace std;

Grid::Grid(int Lines, int Columns)
    :xLenght(Columns), yLength(Lines)//Inicializa��o passou a ser aqui pq to usando dimens�es constantes. O que n�o muda deve ser sempre constante
{
    for (int i = 0; i < Lines; i++)
    {
        for (int j = 0; j < Columns; j++)
        {
            Types::GridBox* newBox = new Types::GridBox(j, i, false, CalculateIndex(i,j));
            grids.push_back(newBox);
            cout<<newBox->Index<<endl;
        }
    }
    cout << "the battlefield has been created" << endl;
	drawBattlefield();
}

Grid::~Grid() 
{
    //O c�digo original n�o tinha dealoca��o do que foi alocado no ctor.
    for (auto i : grids) {
        delete(i);
    }
}

void Grid::drawBattlefield(shared_ptr<Character> player, 
    shared_ptr<Character> enemy)
{
    //Usando stringstream pra acumular pra reduzir a qtd de opera��es
    //de output e fazer o output todo de uma vez.
    std::stringstream ss;
    for (int i = 0; i < Lines(); i++)
    {
        for (int j = 0; j < Columns(); j++)
        {
            if (player != nullptr) {
                if (player->currentBox->Line() == i && player->currentBox->Column() == j) {
                    ss << "[A]";//Player por enquanto � alice
                }
            }
            if (enemy != nullptr) {
                if (enemy->currentBox->Line() == i && enemy->currentBox->Column() == j) {
                    ss << "[B]"; // inimigo, q por enquanto � s� 1, � Bob
                }
            }
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