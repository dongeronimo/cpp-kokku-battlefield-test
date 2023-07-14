#pragma once
#include "Character.h"
#include "Types.h"
#include <list>
#include "Constants.h"
#include <iostream>
#include "Grid.h"
#include <random>
using namespace std;
enum GameResult {Victory, Defeat};
class BattleField
{
public:
	BattleField(const int lines, const int rows, const vector<CharacterClass> playerClassId, const int numberOfEnemies);

	void Initialization(const int lines, const int rows, const vector<CharacterClass> playerClassId, const int numberOfEnemies);

	Grid* grid;
	//Types::GridBox* PlayerCurrentLocation;
	//Types::GridBox* EnemyCurrentLocation;
	vector<shared_ptr<Character>> AllPlayers; //Sintaxe estava toda errada aqui. E troquei por vector pq vector tem memória contígua, vão haver poucas inserções e quero acesso random. Nada disso a std::list me dá.
	vector<shared_ptr<Character>> PlayerTeam;
	vector<shared_ptr<Character>> EnemyTeam;
	//shared_ptr<Character> PlayerCharacter;
	//shared_ptr<Character> EnemyCharacter;
	int currentTurn;
	int numberOfPossibleTiles;

	//Desnecessária depois do meu refactor.
	//void Setup();
	//Desnecessária depois do meu refactor.
	//void GetPlayerChoice(CharacterClass classId);

	/// <summary>
	/// Instancia o time do player, segundo as classes passadas como parâmetro.
	/// </summary>
	/// <param name="classes"></param>
	void CreatePlayerCharacters(vector<CharacterClass> classes);
	/// <summary>
	/// Cria os inimigos aleatórios.
	/// </summary>
	/// <param name="numberOfEnemies"></param>
	void CreateEnemyCharacters(const int numberOfEnemies);

	void StartGame();

	GameResult StartTurn();

	void HandleTurn();

	int GetRandomInt(int min, int max);

	void AlocatePlayers();
	//Passando o uniformd_distribution como ref pra n ter nem que criar
	//um novo a cada execução da recursão nem passar por valor (aliás nem sei se
	//uniform_distribution aceita passagem por valor).
	void AlocatePlayerCharacter(uniform_int_distribution<int>& lineDistribution,
		uniform_int_distribution<int>& colDistribution, shared_ptr<Character> character);

	void AlocateEnemyCharacter(uniform_int_distribution<int>& lineDistribution,
		uniform_int_distribution<int>& colDistribution, shared_ptr<Character> character);
};


