#pragma once
#include <Vector>
#include "Types.h"
#include <memory>
using namespace std;
class Character;
class Grid
{

public:
    
    Grid(int Lines, int Columns);
    ~Grid();
    
    const int CalculateIndex(int i, int j) const {
        return Columns() * i + j;
    }
    /// <summary>
    /// Se está dentro do mapa e está vazio, retorna o gridbox. Senão retorna null
    /// </summary>
    /// <param name="i">a linha no grid</param>
    /// <param name="j">a coluna no gridbox</param>
    /// <returns>nullptr se i ou j fora do range ou se a gridbox estiver ocupada</returns>
    Types::GridBox* GetIfEmpty(int i, int j) const;
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
    void drawBattlefield(vector<shared_ptr<Character>>& player,
        vector<shared_ptr<Character>>& enemy);

};

