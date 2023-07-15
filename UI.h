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
};

