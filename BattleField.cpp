
#include <list>
#include <string>
#include <conio.h>
#include <algorithm>
#include "Context.h"
#include "Grid.h"
#include "BattleField.h"
#include "Types.h"
#include "Character.h"
#include "UI.h"
using namespace std;


Types::GridBox* BattleField::GetRandomUnocupied() {
    auto randomInteger = CONTEXT->RandomInteger(0, grid->grids.size());
    if (grid->grids[randomInteger]->ocupied == false)
        return grid->grids[randomInteger];
    else
        return GetRandomUnocupied();
}
BattleField::BattleField(const int lines, const int rows, const vector<Types::CharacterClass> playerClassId, const int numberOfEnemies)
{    
    Initialization(lines, rows, playerClassId, numberOfEnemies);
}

void BattleField::Initialization(const int lines, const int rows, const vector<Types::CharacterClass> playerClassId, const int numberOfEnemies)
{
    AllPlayers.clear();
    PlayerTeam.clear();
    EnemyTeam.clear();

    grid = new Grid(lines, rows);
    int currentTurn = 0;
    int numberOfPossibleTiles = grid->grids.size();
    CreatePlayerCharacters(playerClassId);
    CreateEnemyCharacters(numberOfEnemies);
}

void BattleField::CreatePlayerCharacters(vector<Types::CharacterClass> classes)
{
    for(Types::CharacterClass classIndex : classes) {
        //typecast correto.
        auto characterClass = classIndex;
        //troquei printf por cout pq estou mais acostumado com cout
        _UI->PlayerClassChoice(characterClass);
        auto PlayerCharacter = std::make_shared<Character>(characterClass, *this, TeamA);
        PlayerCharacter->Health = 100;
        PlayerCharacter->BaseDamage = 20;
        PlayerCharacter->PlayerIndex = PlayerTeam.size();
        PlayerCharacter->DamageMultiplier = 1.0f;
        PlayerTeam.push_back(PlayerCharacter);
    }
}

void BattleField::CreateEnemyCharacters(const int numberOfEnemies)
{
    for (auto i = 0; i < numberOfEnemies; i++) {
        int randomInteger = CONTEXT->RandomInteger (Types::CharacterClass::Paladin, Types::CharacterClass::Archer);
        Types::CharacterClass enemyClass = static_cast<Types::CharacterClass>(randomInteger);
        _UI->EnemyClassChoice(enemyClass);
        auto EnemyCharacter = std::make_shared<Character>(enemyClass, *this, TeamB);
        EnemyCharacter->Health = 100;
        EnemyCharacter->BaseDamage = 20;
        EnemyCharacter->PlayerIndex = EnemyTeam.size() + PlayerTeam.size();
        EnemyCharacter->DamageMultiplier = 1.0f;
        EnemyTeam.push_back(EnemyCharacter);
    }
}

void BattleField::StartGame()
{   
    AllPlayers.insert(AllPlayers.end(), PlayerTeam.begin(), PlayerTeam.end());
    AllPlayers.insert(AllPlayers.end(), EnemyTeam.begin(), EnemyTeam.end());

    AlocatePlayers();
    StartTurn();

}
void BattleField::DrawBattlefield() {
    grid->drawBattlefield(PlayerTeam, EnemyTeam);
}
Types::GameResult BattleField::StartTurn() {
    std::shuffle(AllPlayers.begin(), AllPlayers.end(), CONTEXT->RNG());
    auto it = AllPlayers.begin();
    for (it = AllPlayers.begin(); it != AllPlayers.end(); ++it) {
        auto character = (*it);
        if (!character->IsDead())
        {
            character->StartTurn(grid);
        }
        else
        {
            //tá morto, libera a casinha.
            if (character->currentBox) {
                character->currentBox->ocupied = false;
                character->currentBox = nullptr;
            }
        }
    }

    grid->drawBattlefield(PlayerTeam, EnemyTeam);

    //a partida acaba se um dos times estiver todo morto
    vector<shared_ptr<Character>> deadPlayers, deadEnemies;
    std::copy_if(PlayerTeam.begin(), PlayerTeam.end(), std::back_inserter(deadPlayers),
        [](auto character) {return character->IsDead(); });
    std::copy_if(EnemyTeam.begin(), EnemyTeam.end(), std::back_inserter(deadEnemies),
        [](auto character) {return character->IsDead(); });
    if (deadPlayers.size() == PlayerTeam.size()) 
        return Types::GameResult::Defeat;
    if (deadEnemies.size() == EnemyTeam.size())
        return Types::GameResult::Victory;

    currentTurn++;
    HandleTurn();
    //Devido à recursão não retorna nada aqui pq o retorno da pilha de recursão é quando 
    //todo mundo de um dos times morreu
}

void BattleField::HandleTurn()
{
    _UI->NextTurnOrQuitPrompt();
    Types::GameResult result = StartTurn();
    _UI->VictoryOrDefeat(result);
    if (_UI->AskIfWantToPlayAgain()) {
        //Modifica os parâmetros e reinicia o ciclo.
        Types::GameSetupParameters newParams = _UI->AskForParameters();
        Initialization(newParams.GridLines, newParams.GridRows, newParams.PlayerTeamClassIds, 
            newParams.NumberOfCharactersInEnemyTeam);
        StartGame();
    }
    else {
        //sai do programa.
        CONTEXT->Quit();
    }
}

void BattleField::AlocatePlayers()
{
    uniform_int_distribution<int> lineDistribution(0, grid->Lines() - 1);
    uniform_int_distribution<int> colDistribution(0, grid->Columns() - 1);
    for (auto character : PlayerTeam) {
        AlocatePlayerCharacter(character);
    }
    for (auto character : EnemyTeam) {
        AlocateEnemyCharacter(character);
    }
    
}

Types::GridBox* BattleField::GetEmptyGridbox() {
    int randomLine = CONTEXT->RandomInteger(0, grid->Lines() - 1);
    int randomCol = CONTEXT->RandomInteger(0, grid->Columns() - 1);
    Types::GridBox* RandomLocation = grid->grids[grid->CalculateIndex(randomLine, randomCol)];
    if (!RandomLocation->ocupied) {
        return RandomLocation;
    }
    else {
        return GetEmptyGridbox();
    }
}

//TODO: Fundir essas duas fn em uma só pq fazem a mesma coisa
void BattleField::AlocatePlayerCharacter(shared_ptr<Character> character)
{
    int randomLine = CONTEXT->RandomInteger(0, grid->Lines() - 1);
    int randomCol = CONTEXT->RandomInteger(0, grid->Columns() - 1);
    //pega o GridBox escolhido aleatoriamente
    Types::GridBox* RandomLocation = grid->grids[grid->CalculateIndex(randomLine, randomCol)];
    //Não está ocupado, por o player e marcar como ocupado.
    if (!RandomLocation->ocupied) {
        character->currentBox = RandomLocation;
        RandomLocation->ocupied = true;
    }
    //está ocupado, recursão
    else {
        AlocatePlayerCharacter(character);
    }
}

void BattleField::AlocateEnemyCharacter(shared_ptr<Character> character)
{
    int randomLine = CONTEXT->RandomInteger(0, grid->Lines() - 1);
    int randomCol = CONTEXT->RandomInteger(0, grid->Columns() - 1);
    Types::GridBox* RandomLocation = grid->grids[grid->CalculateIndex(randomLine, randomCol)];
    if (!RandomLocation->ocupied) {
        character->currentBox = RandomLocation;
        RandomLocation->ocupied = true;
    }
    else {
        AlocateEnemyCharacter(character);
    }
}