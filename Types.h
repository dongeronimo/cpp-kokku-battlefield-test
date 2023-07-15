#pragma once
#include <vector>
using namespace std;
class Types
{
public:
    enum GameResult { Victory, Defeat };
    struct GridBox
    {
        int xIndex;
        int yIndex;
        bool ocupied;
        int Index;
        //Normalizando nomenclatura
        const int Line() const { return yIndex; }
        const int Column() const { return xIndex; }
        GridBox() {
            xIndex = 0;
            yIndex = 0;
            ocupied = false;
            Index = 0;
        }
        GridBox(int x, int y, bool isOcupied, int index)
        {
            xIndex = x;
            yIndex = y;
            ocupied = isOcupied;
            Index = index;
        }
    };
    enum CharacterClass
    {
        Paladin = 1,
        Warrior = 2,
        Cleric = 3,
        Archer = 4
    };
    /// <summary>
    /// Guarda os parâmetros escolhidos pelo player.
    /// </summary>
    struct GameSetupParameters {
        int GridLines;
        int GridRows;
        int NumberOfCharactersInEnemyTeam;
        int NumberOfCharactersInPlayerTeam;
        //Não vou ter o sofrimento de lidar com arrays dinâmicas de baixo nível, malloc, calloc, free se eu posso usar uma 
        //estrutura de alto nivel ne? E o custo da passagem por valor é irrelevante já que isso não será usado num loop quente
        //do jogo.
        std::vector<CharacterClass> PlayerTeamClassIds;
    };


};

