#pragma once
#include <memory>
#include <string>
#include "Types.h"
using namespace std;
#define _UI UI::Instance()
class UI
{
private:
	static shared_ptr<UI> instance;
	int AskForNumberOfCharactersInPlayerTeam();
	vector<Types::CharacterClass> AskForPlayerTeamClasses(int teamSize);
	Types::CharacterClass AskForClass();
	int AskForNumberOfCharactersInEnemyTeam();
	int AskForNumberOfLines();
	int AskForNumberOfRows();
	int ReadPositiveInt(const std::string& text);
public:
	static shared_ptr<UI> Instance();
	Types::GameSetupParameters AskForParameters();
	bool AskIfWantToPlayAgain()const;
	void Goodbye()const;
	void PlayerClassChoice(const Types::CharacterClass& classIndex)const;
	void EnemyClassChoice(const Types::CharacterClass& classIndex)const;
	/// <summary>
	/// Se a tecla for esc lança o sinal de fim de jogo.
	/// </summary>
	void NextTurnOrQuitPrompt();
	void VictoryOrDefeat(const Types::GameResult& result)const;
	void BowAttack(const int& originatorIndex, const int& targetIndex) const;
	void PlayerIsDead(const int& playerId)const;
	void PlayerWalkTo(const int& playerId, const string& direction)const;
	void PlayerBaseAttack(const int& originator, const int& subject, const float& damage);
	void Charge(const int& originatorIndex, const int& targetIndex) const;
	void SelfHeal(const int& originatorIndex) const;
	void Smite(const int& originator, const int& target)const;
	void Curse(const int& originator)const;
	void Reanimate(const int& originator, const int& chosen)const;
};

