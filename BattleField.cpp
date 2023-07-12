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

//Gerador de numeros aleatórios da STL
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

//void BattleField::Setup()
//{
//    GetPlayerChoice();
//}

//void BattleField::GetPlayerChoice(CharacterClass classId)
//{//    
//    ////asks for the player to choose between for possible classes via console.
//    //printf("Choose Between One of this Classes:\n");
//
//    //printf("[1] Paladin, [2] Warrior, [3] Cleric, [4] Archer");
//    ////store the player choice in a variable
//    //std::string choice;
//
//    //std::getline(std::cin, choice);
//    //
//    //cin >> choice;
//    //switch ((choice))
//    //{
//    //case "1":
//    //    CreatePlayerCharacter(choice);
//    //    break;
//    //case "2":
//    //    CreatePlayerCharacter(choice);
//    //    break;
//    //case "3":
//    //    CreatePlayerCharacter(choice);
//    //    break;
//    //case "4":
//    //    CreatePlayerCharacter(choice);
//    //    break;
//    //default:
//    //    GetPlayerChoice();
//    //    break;
//    //}
//}

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
    //não é o correto chamar a criação de inimigos de dentro da criação do 
    // personagem. Uma coisa é uma coisa, outra coisa é outra coisa.

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
    PlayerCharacter->BaseDamage = 20;
    PlayerCharacter->PlayerIndex = 1;
    //não é correto chamar startGame aqui. Não é responsabilidade desse método;
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
    //??
    //if (currentTurn == 0)
    //{
    //    //AllPlayers.Sort();  
    //}
    auto it = AllPlayers.begin();

    for (it = AllPlayers.begin(); it != AllPlayers.end(); ++it) {
        (*it)->StartTurn(grid);
    }

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
        cout << "TODO: Lidar c a vitória";
        return;
    }
    else
    {
        cout << endl << "Click on any key to start the next turn or Esc to quit..." << endl;
        auto k = _getch();
        if (k == 27) {
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
    //Não está ocupado, por o player e marcar como ocupado.
    if (!RandomLocation->ocupied) {
        PlayerCurrentLocation = RandomLocation;
        PlayerCharacter->currentBox = RandomLocation;
        RandomLocation->ocupied = true;
    }
    //está ocupado, recursão
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