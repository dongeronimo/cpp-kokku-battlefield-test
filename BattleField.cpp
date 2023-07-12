#include "Grid.h"
#include "BattleField.h"
#include "Types.h"
#include "Character.h"
#include <iostream>
#include "BattleField.h"
#include <list>
#include <string>
#include <random>
using namespace std;

//Gerador de numeros aleat�rios da STL
random_device rd;
std::mt19937 rng(rd());

BattleField::BattleField(int lines, int rows, CharacterClass playerClassId) 
{    
    grid = new Grid(lines, rows);
    AllPlayers = new list<Character>();
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
    PlayerCharacter->BaseDamage = 20;
    PlayerCharacter->PlayerIndex = 1;
    //n�o � correto chamar startGame aqui. N�o � responsabilidade desse m�todo;
    //StartGame();

}

void BattleField::StartGame()
{
    ////populates the character variables and targets
    //EnemyCharacter->target = PlayerCharacter;
    //PlayerCharacter->target = EnemyCharacter;
    //AllPlayers->push_back(PlayerCharacter);
    //AllPlayers->push_back(EnemyCharacter);
    //AlocatePlayers();
    //StartTurn();

}

void BattleField::StartTurn() {

    if (currentTurn == 0)
    {
        //AllPlayers.Sort();  
    }
    std::list<Character>::iterator it;

    for (it = AllPlayers->begin(); it != AllPlayers->end(); ++it) {
        it->StartTurn(grid);
    }

    currentTurn++;
    HandleTurn();
}

void BattleField::HandleTurn()
{
    //if (PlayerCharacter->Health == 0)
    //{
    //    return;
    //}
    //else if (EnemyCharacter->Health == 0)
    //{
    //    printf("\n");

    //    // endgame?

    //    printf("\n");

    //    return;
    //}
    //else
    //{
    //    printf("\n");
    //    printf("Click on any key to start the next turn...\n");
    //    printf("\n");

    //    //TODO
    //    //ConsoleKeyInfo key = Console.ReadKey();
    //    StartTurn();
    //}
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
    AlocatePlayerCharacter();

}

void BattleField::AlocatePlayerCharacter()
{
    //int random = 0;
    //auto l_front = grid->grids.begin();
    //advance(l_front, random);
    //Types::GridBox* RandomLocation = &*l_front;

    //if (!RandomLocation->ocupied)
    //{
    //    //Types::GridBox* PlayerCurrentLocation = RandomLocation;
    //    PlayerCurrentLocation = &*l_front;
    //    l_front->ocupied = true;
    //    PlayerCharacter->currentBox = *l_front;
    //    AlocateEnemyCharacter();
    //}
    //else
    //{
    //    AlocatePlayerCharacter();
    //}
}

void BattleField::AlocateEnemyCharacter()
{
    
    //int random = 24;
    //auto l_front = grid->grids.begin();
    //advance(l_front, random);
    //Types::GridBox* RandomLocation = &*l_front;
    //
    //if (!RandomLocation->ocupied)
    //{
    //    EnemyCurrentLocation = &*l_front;
    //    l_front->ocupied = true;
    //    EnemyCharacter->currentBox = *l_front;
    //    grid->drawBattlefield(5, 5);
    //}
    //else
    //{
    //    AlocateEnemyCharacter();
    //}


}