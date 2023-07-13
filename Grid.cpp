#include "Grid.h"
#include "Types.h"
#include <iostream>
#include <sstream>
#include "Character.h"
using namespace std;

Grid::Grid(int Lines, int Columns)
    :xLenght(Columns), yLength(Lines)//Inicialização passou a ser aqui pq to usando dimensões constantes. O que não muda deve ser sempre constante
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
    //O código original não tinha dealocação do que foi alocado no ctor.
    for (auto i : grids) {
        delete(i);
    }
}

void Grid::drawBattlefield(shared_ptr<Character> player, 
    shared_ptr<Character> enemy)
{
    //Usando stringstream pra acumular pra reduzir a qtd de operações
    //de output e fazer o output todo de uma vez.
    std::stringstream ss;
    for (int i = 0; i < Lines(); i++)
    {
        for (int j = 0; j < Columns(); j++)
        {
            if (player != nullptr) {
                if (player->currentBox->Line() == i && player->currentBox->Column() == j) {
                    ss << "[A]";//Player por enquanto é alice
                }
            }
            if (enemy != nullptr) {
                if (enemy->currentBox->Line() == i && enemy->currentBox->Column() == j) {
                    ss << "[B]"; // inimigo, q por enquanto é só 1, é Bob
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