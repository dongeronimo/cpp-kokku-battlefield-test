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
	BattleField(const int lines, const int rows, const vector<Types::CharacterClass> playerClassId, const int numberOfEnemies);

	void Initialization(const int lines, const int rows, const vector<Types::CharacterClass> playerClassId, const int numberOfEnemies);


	Types::GridBox* GetEmptyGridbox();
	Grid* grid;
	vector<shared_ptr<Character>> AllPlayers; //Sintaxe estava toda errada aqui. E troquei por vector pq vector tem memória contígua, vão haver poucas inserções e quero acesso random. Nada disso a std::list me dá.
	vector<shared_ptr<Character>> PlayerTeam;
	vector<shared_ptr<Character>> EnemyTeam;
	int currentTurn;
	int numberOfPossibleTiles;
	/// <summary>
	/// Instancia o time do player, segundo as classes passadas como parâmetro.
	/// </summary>
	/// <param name="classes"></param>
	void CreatePlayerCharacters(vector<Types::CharacterClass> classes);
	/// <summary>
	/// Cria os inimigos aleatórios.
	/// </summary>
	/// <param name="numberOfEnemies"></param>
	void CreateEnemyCharacters(const int numberOfEnemies);

	void StartGame();

	GameResult StartTurn();

	void HandleTurn();

	void AlocatePlayers();
	//Passando o uniformd_distribution como ref pra n ter nem que criar
	//um novo a cada execução da recursão nem passar por valor (aliás nem sei se
	//uniform_distribution aceita passagem por valor).
	void AlocatePlayerCharacter(shared_ptr<Character> character);

	void AlocateEnemyCharacter( shared_ptr<Character> character);

	Types::GridBox* GetRandomUnocupied();
	void DrawBattlefield();
};


