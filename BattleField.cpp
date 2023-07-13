#include "Grid.h"
#include "BattleField.h"
#include "Types.h"
#include "Character.h"
#include <iostream>
#include "BattleField.h"
#include <list>
#include <string>
#include <random>
#include <conio.h>
using namespace std;

//Gerador de numeros aleat�rios da STL
random_device rd;
std::mt19937 rng(rd());

BattleField::BattleField(int lines, int rows, CharacterClass playerClassId) 
{    
    grid = new Grid(lines, rows);
    int currentTurn = 0;
    int numberOfPossibleTiles = grid->grids.size();
    //Setup();
    CreatePlayerCharacter(playerClassId);
    CreateEnemyCharacter();
}

void BattleField::CreatePlayerCharacter(int classIndex)
{
    //typecast correto.
    auto characterClass = static_cast<Types::CharacterClass>(classIndex);;
    //troquei printf por cout pq estou mais acostumado com cout
    std::cout << "Player Class Choice: " << characterClass;
    PlayerCharacter = std::make_shared<Character>(characterClass);
    //
    PlayerCharacter->Health = 100;
    PlayerCharacter->BaseDamage = 20;
    PlayerCharacter->PlayerIndex = 0;
    //n�o � o correto chamar a cria��o de inimigos de dentro da cria��o do 
    // personagem. Uma coisa � uma coisa, outra coisa � outra coisa.

}

void BattleField::CreateEnemyCharacter()
{
    ////randomly choose the enemy class and set up vital variables
    //
    int randomInteger = GetRandomInt(PALADIN, ARCHER);
    Types::CharacterClass enemyClass = static_cast<Types::CharacterClass>(randomInteger);
    cout << "Enemy Class Choice:" << enemyClass<<endl;
    EnemyCharacter = std::make_shared<Character>(enemyClass);
    EnemyCharacter->Health = 100;
    EnemyCharacter->BaseDamage = 20;
    EnemyCharacter->PlayerIndex = 1;
    //n�o � correto chamar startGame aqui. N�o � responsabilidade desse m�todo;
    //StartGame();

}

void BattleField::StartGame()
{
    ////populates the character variables and targets
    EnemyCharacter->target = PlayerCharacter;
    PlayerCharacter->target = EnemyCharacter;
    
    AllPlayers.push_back(PlayerCharacter);
    AllPlayers.push_back(EnemyCharacter);

    AlocatePlayers();
    StartTurn();

}

void BattleField::StartTurn() {
    auto it = AllPlayers.begin();

    for (it = AllPlayers.begin(); it != AllPlayers.end(); ++it) {
        (*it)->StartTurn(grid);
    }
    grid->drawBattlefield(PlayerCharacter, EnemyCharacter);
    currentTurn++;
    HandleTurn();
}

void BattleField::HandleTurn()
{
    cout << "Handle turn" << endl;
    if (PlayerCharacter->Health == 0)
    {
        cout << "TODO: Lidar c a morte do player";
        return;
    }
    else if (EnemyCharacter->Health == 0)
    {
        cout << "TODO: Lidar c a vit�ria";
        return;
    }
    else
    {
        cout << endl << "Click on any key to start the next turn or Esc to quit..." << endl;
        auto k = _getch();
        if (k == KEY_ESC) {
            return;
        }
        else {
            StartTurn();
        }
    }
}

int BattleField::GetRandomInt(int min, int max)
{
    //Refeita do zero para usar o gerador de random da stl.
    uniform_int_distribution<int> uni(min, max);
    auto randomInteger = uni(rng);
    return randomInteger;
}

void BattleField::AlocatePlayers()
{
    uniform_int_distribution<int> lineDistribution(0, grid->Lines() - 1);
    uniform_int_distribution<int> colDistribution(0, grid->Columns() - 1);
    AlocatePlayerCharacter(lineDistribution, colDistribution);
    AlocateEnemyCharacter(lineDistribution, colDistribution);
}

void BattleField::AlocatePlayerCharacter(uniform_int_distribution<int>& lineDistribution,
    uniform_int_distribution<int>& colDistribution)
{
    int randomLine = lineDistribution(rng);
    int randomCol = colDistribution(rng);
    //pega o GridBox escolhido aleatoriamente
    Types::GridBox* RandomLocation = grid->grids[grid->CalculateIndex(randomLine, randomCol)];
    //N�o est� ocupado, por o player e marcar como ocupado.
    if (!RandomLocation->ocupied) {
        PlayerCurrentLocation = RandomLocation;
        PlayerCharacter->currentBox = RandomLocation;
        RandomLocation->ocupied = true;
    }
    //est� ocupado, recurs�o
    else {
        AlocatePlayerCharacter(lineDistribution, colDistribution);
    }
}

void BattleField::AlocateEnemyCharacter(uniform_int_distribution<int>& lineDistribution,
    uniform_int_distribution<int>& colDistribution)
{
    int randomLine = lineDistribution(rng);
    int randomCol = colDistribution(rng);
    Types::GridBox* RandomLocation = grid->grids[grid->CalculateIndex(randomLine, randomCol)];
    if (!RandomLocation->ocupied) {
        EnemyCurrentLocation = RandomLocation;
        EnemyCharacter->currentBox = RandomLocation;
        RandomLocation->ocupied = true;
    }
    else {
        AlocateEnemyCharacter(lineDistribution, colDistribution);
    }
}