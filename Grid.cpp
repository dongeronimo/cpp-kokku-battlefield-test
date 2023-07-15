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
Types::GridBox* Grid::GetIfEmpty(int i, int j) const
{
    if (i < 0 || i >= Lines() || j < 0 || j >= Columns())
        return nullptr;
    else if (grids[CalculateIndex(i, j)]->ocupied)
        return nullptr;
    else 
        return grids[CalculateIndex(i, j)];
}
void Grid::drawBattlefield() {
    std::stringstream ss;
    for (int i = 0; i < Lines(); i++) {
        for (int j = 0; j < Columns(); j++) {
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
void Grid::drawBattlefield(vector<shared_ptr<Character>>& players,
    vector<shared_ptr<Character>>& enemies)
{
    //Usando stringstream pra acumular pra reduzir a qtd de operações
    //de output e fazer o output todo de uma vez.
    std::stringstream ss;
    for (int i = 0; i < Lines(); i++)
    {
        for (int j = 0; j < Columns(); j++)
        {
            Types::GridBox* currentGrid = grids[CalculateIndex(i, j)];
            bool drewPlayerOrEnemy = false;
            for (auto player : players) {
                if (player->currentBox && player->currentBox->Line() == i && player->currentBox->Column() == j) {
                    ss << "[A]";//Player por enquanto é alice
                    drewPlayerOrEnemy = true;
                    break;
                }
            }
            for (auto enemy : enemies) {
                if (enemy->currentBox && enemy->currentBox->Line() == i && enemy->currentBox->Column() == j) {
                    ss << "[B]";
                    drewPlayerOrEnemy = true;
                    break;
                }
            }
            if (!drewPlayerOrEnemy) {
                if (currentGrid->ocupied) {
                    ss << "[x]";
                }
                else {
                    ss << "[ ]";
                }
            }
        }
        ss << endl;
    }
    std::cout << ss.str() << endl;
}