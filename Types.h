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
    struct ClassBaseAttributes {
        float Health;
        float BaseDamage;
        float DamageMultiplier;
    };
    struct AbilitiesAndEffecsAttributes {
        float STRONG_ATTACK_PROC_CHANCE = 0.33f;
        float TELEPORT_PROC_CHANCE = 0.33f;
        float TELEPORT_PROC_DISTANCE = 3;
        float SELF_HEAL_PROC_CHANCE = 0.33f;
        float BOW_ATTACK_PROC_CHANCE = 0.75f;
        float BOW_ATTACK_PROC_MAX_DISTANCE = 5 
;       float SMITE_PROC_CHANCE = 0.8f;
        float SMITE_MAX_HP_PROC = 60;
        float CHARGE_PROC_CHANCE = 0.5f;
        float CURSE_PROC_CHANCE = 0.33f;
        float CURSE_RANGE = 3;
        float REANIMATE_PROC_CHANCE = 0.05f;
        int HEAL_DURATION =2;
        int STUN_DURATION =3;
        int  CURSE_DURATION =2;
        float CURSE_DAMAGE = 20;
    };

};

