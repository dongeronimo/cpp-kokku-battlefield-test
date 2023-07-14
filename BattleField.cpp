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
#include "BattlefieldSetup.h"
#include "Context.h"
using namespace std;

//Gerador de numeros aleat�rios da STL
random_device rd;
std::mt19937 rng(rd());

BattleField::BattleField(const int lines, const int rows, const vector<CharacterClass> playerClassId, const int numberOfEnemies)
{    
    Initialization(lines, rows, playerClassId, numberOfEnemies);
}

void BattleField::Initialization(const int lines, const int rows, const vector<CharacterClass> playerClassId, const int numberOfEnemies)
{
    AllPlayers.clear();
    PlayerTeam.clear();
    EnemyTeam.clear();
    //PlayerCharacter.reset();
    //EnemyCharacter.reset();
    //PlayerCurrentLocation = nullptr;
    //EnemyCurrentLocation = nullptr;
    grid = new Grid(lines, rows);
    int currentTurn = 0;
    int numberOfPossibleTiles = grid->grids.size();
    CreatePlayerCharacters(playerClassId);
    CreateEnemyCharacters(numberOfEnemies);
}

void BattleField::CreatePlayerCharacters(vector<CharacterClass> classes)
{
    for(CharacterClass classIndex : classes) {
        //typecast correto.
        auto characterClass = static_cast<Types::CharacterClass>(classIndex);
        //troquei printf por cout pq estou mais acostumado com cout
        std::cout << "Player Class Choice: " << characterClass;
        auto PlayerCharacter = std::make_shared<Character>(characterClass);
        PlayerCharacter->Health = 100;
        PlayerCharacter->BaseDamage = 20;
        PlayerCharacter->PlayerIndex = 0;
        PlayerCharacter->DamageMultiplier = 1.0f;
        PlayerTeam.push_back(PlayerCharacter);
    }
}

void BattleField::CreateEnemyCharacters(const int numberOfEnemies)
{
    for (auto i = 0; i < numberOfEnemies; i++) {
        int randomInteger = GetRandomInt(PALADIN, ARCHER);
        Types::CharacterClass enemyClass = static_cast<Types::CharacterClass>(randomInteger);
        cout << "Enemy Class Choice:" << enemyClass << endl;
        auto EnemyCharacter = std::make_shared<Character>(enemyClass);
        EnemyCharacter->Health = 100;
        EnemyCharacter->BaseDamage = 20;
        EnemyCharacter->PlayerIndex = 1;
        EnemyCharacter->DamageMultiplier = 1.0f;
        EnemyTeam.push_back(EnemyCharacter);
    }
}

void BattleField::StartGame()
{
    ////populates the character variables and targets
    //Vai ser populado din�micamente
    //EnemyCharacter->target = PlayerCharacter;
    //PlayerCharacter->target = EnemyCharacter;
    
    AllPlayers.insert(AllPlayers.end(), PlayerTeam.begin(), PlayerTeam.end());
    AllPlayers.insert(AllPlayers.end(), EnemyTeam.begin(), EnemyTeam.end());

    AlocatePlayers();
    StartTurn();

}

GameResult BattleField::StartTurn() {
    auto it = AllPlayers.begin();
    for (it = AllPlayers.begin(); it != AllPlayers.end(); ++it) {
        auto character = (*it);
        if (!character->IsDead())
        {
            character->StartTurn(grid);
        }
        else
        {
            //� o player que morreu, game over.
            if (character->PlayerIndex == PlayerCharacter->PlayerIndex) 
            {
                return Defeat;
            }
            else//� o inimigo que morreu.
            {
                return Victory;
            }
        }
    }
    grid->drawBattlefield(PlayerCharacter, EnemyCharacter);
    currentTurn++;
    HandleTurn();
}

void BattleField::HandleTurn()
{
    cout << endl << "Click on any key to start the next turn or Esc to quit..." << endl;
    auto k = _getch();
    if (k == KEY_ESC) {
        Quit();
    }
    else {
        GameResult result = StartTurn();
        if (AskIfWantToPlayAgain()) {
            //Modifica os par�metros e reinicia o ciclo.
            GameSetupParameters newParams = AskForParameters();
            Initialization(newParams.GridLines, newParams.GridRows, newParams.PlayerTeamClassIds, newParams.NumberOfCharactersInEnemyTeam);
            StartGame();
        }
        else {
            //sai do programa.
            Quit();
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
    for (auto character : PlayerTeam) {
        AlocatePlayerCharacter(lineDistribution, colDistribution);
    }
    for (auto character : EnemyTeam) {
        AlocateEnemyCharacter(lineDistribution, colDistribution);
    }
    
}

void BattleField::AlocatePlayerCharacter(uniform_int_distribution<int>& lineDistribution, 
    uniform_int_distribution<int>& colDistribution, 
    shared_ptr<Character> character)
{
    int randomLine = lineDistribution(rng);
    int randomCol = colDistribution(rng);
    //pega o GridBox escolhido aleatoriamente
    Types::GridBox* RandomLocation = grid->grids[grid->CalculateIndex(randomLine, randomCol)];
    //N�o est� ocupado, por o player e marcar como ocupado.
    if (!RandomLocation->ocupied) {
        character->currentBox = RandomLocation;
        RandomLocation->ocupied = true;
    }
    //est� ocupado, recurs�o
    else {
        AlocatePlayerCharacter(lineDistribution, colDistribution);
    }
}

void BattleField::AlocateEnemyCharacter(uniform_int_distribution<int>& lineDistribution,
    uniform_int_distribution<int>& colDistribution, 
    shared_ptr<Character> character)
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