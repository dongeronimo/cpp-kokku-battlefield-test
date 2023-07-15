#include "Grid.h"
#include "Types.h"
#include "UI.h"
//#include <iostream>
//#include <sstream>
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
            _UI->PrintInt(newBox->Index);
        }
    }
    _UI->BattlefieldCreated();
    _UI->DrawBattlefield(grids, this->Lines(), this->Columns());
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

void Grid::drawBattlefield(vector<shared_ptr<Character>>& players,
    vector<shared_ptr<Character>>& enemies)
{
    _UI->DrawBattlefield(grids, players, enemies, Lines(), Columns());
    //Usando stringstream pra acumular pra reduzir a qtd de operações
    //de output e fazer o output todo de uma vez.
    /*std::stringstream ss;
    for (int i = 0; i < Lines(); i++)
    {
        for (int j = 0; j < Columns(); j++)
        {
            Types::GridBox* currentGrid = grids[CalculateIndex(i, j)];
            bool drewPlayerOrEnemy = false;
            for (auto player : players) {
                if (player->IsDead())
                    continue;
                if (player->currentBox && player->currentBox->Line() == i && player->currentBox->Column() == j) {
                    switch (player->GetCharacterClass()) {
                    case Types::Archer:
                        ss << "[A]";
                        break;
                    case Types::Cleric:
                        ss << "[C]";
                        break;
                    case Types::Paladin:
                        ss << "[P]";
                        break;
                    case Types::Warrior:
                        ss << "[W]";
                        break;
                    }
                    drewPlayerOrEnemy = true;
                    break;
                }
            }
            for (auto enemy : enemies) {
                if (enemy->IsDead())
                    continue;
                if (enemy->currentBox && enemy->currentBox->Line() == i && enemy->currentBox->Column() == j) {
                    switch (enemy->GetCharacterClass()) {
                    case Types::Archer:
                        ss << "[a]";
                        break;
                    case Types::Cleric:
                        ss << "[c]";
                        break;
                    case Types::Paladin:
                        ss << "[p]";
                        break;
                    case Types::Warrior:
                        ss << "[w]";
                        break;
                    }
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
    std::cout << ss.str() << endl;*/
}