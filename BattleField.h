#pragma once
#include "Character.h"
#include "Types.h"
#include <list>
#include "Constants.h"
#include <iostream>
#include "Grid.h"
#include <random>
using namespace std;

class BattleField
{
public:

	BattleField(int lines, int rows, CharacterClass playerClassId);

	Grid* grid;
	Types::GridBox* PlayerCurrentLocation;
	Types::GridBox* EnemyCurrentLocation;
	vector<shared_ptr<Character>> AllPlayers; //Sintaxe estava toda errada aqui. E troquei por vector pq vector tem memória contígua, vão haver poucas inserções e quero acesso random. Nada disso a std::list me dá.
	shared_ptr<Character> PlayerCharacter;

	shared_ptr<Character> EnemyCharacter;
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

	void AlocatePlayerCharacter(uniform_int_distribution<int>& lineDistribution,
		uniform_int_distribution<int>& colDistribution);

	void AlocateEnemyCharacter(uniform_int_distribution<int>& lineDistribution,
		uniform_int_distribution<int>& colDistribution);
};


