#pragma once
#include "Character.h"
#include "Types.h"
#include <list>
#include "Constants.h"
#include <iostream>
#include "Grid.h"
using namespace std;
class BattleField
{
public:

	BattleField(int lines, int rows, CharacterClass playerClassId);

	Grid* grid;
	Types::GridBox* PlayerCurrentLocation;
	Types::GridBox* EnemyCurrentLocation;
	list<Character>* AllPlayers;
	shared_ptr<Character> PlayerCharacter;

	shared_ptr<Character>* EnemyCharacter;
	int currentTurn;
	int numberOfPossibleTiles;

	//Desnecessária depois do meu refactor.
	//void Setup();
	//Desnecessária depois do meu refactor.
	//void GetPlayerChoice(CharacterClass classId);

	void CreatePlayerCharacter(int classIndex);

	void CreateEnemyCharacter();

	void StartGame();

	void StartTurn();

	void HandleTurn();

	int GetRandomInt(int min, int max);

	void AlocatePlayers();

	void AlocatePlayerCharacter();

	void AlocateEnemyCharacter();
};


