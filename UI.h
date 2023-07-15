#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Types.h"
using namespace std;
struct GridBox;
class Character;
#define _UI UI::Instance()
class UI
{
private:
	static UI* instance;
	UI() {}
	UI(const UI&) {}
	~UI() {}
	int AskForNumberOfCharactersInPlayerTeam();
	vector<Types::CharacterClass> AskForPlayerTeamClasses(int teamSize);
	Types::CharacterClass AskForClass();
	int AskForNumberOfCharactersInEnemyTeam();
	int AskForNumberOfLines();
	int AskForNumberOfRows();
	int ReadPositiveInt(const std::string& text);
	const int CalculateIndex(int i, int j, int cols)const { return cols * i + j; }
public:
	static UI& Instance();
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
	void PrintInt(const int& someInt)const;
	void BattlefieldCreated()const;
	void DrawBattlefield(const std::vector<Types::GridBox*>& grids, const int lines, const int cols)const;
	void DrawBattlefield(const std::vector<Types::GridBox*>& grids, vector<shared_ptr<Character>>& players,
		vector<shared_ptr<Character>>& enemies, const int lines, const int cols);
	void HealApply(const int& target, const int amount)const;
	void StunApply(const int& target)const;
	void PulsaDinuraApply(const int& target) const;
	void StrongAttack(const int& originator)const;
	void Teleport(const int& originator)const;
};

