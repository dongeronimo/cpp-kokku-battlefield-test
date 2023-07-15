#include "UI.h"
#include <iostream>
#include "stringutils.h"
#include <functional>
#include <string>
#include <conio.h>
#include "Context.h"
#include <sstream>
#include "Character.h"
#define KEY_ESC 27
using namespace std;
UI* UI::instance = nullptr;

template<typename ReturnValue>
ReturnValue PromptLoop(function<ReturnValue(bool&)> Prompt) {
	bool validChoice = false;
	while (!validChoice) {
		ReturnValue result = Prompt(validChoice);
		if (validChoice)
			return result;
	}
}

int UI::AskForNumberOfCharactersInPlayerTeam()
{
	return PromptLoop<int>([](bool& validInput)->int
		{
			try {
				cout << "How many characters on your team? " << endl;
				string choiceAsStr;
				std::getline(std::cin, choiceAsStr);
				choiceAsStr = trim(choiceAsStr);
				int choiceAsNumber = stoi(choiceAsStr);
				if (choiceAsNumber <= 0)
					throw std::invalid_argument("Must have at least one character on the team");
				validInput = true;
				return choiceAsNumber;
			}
			catch (std::invalid_argument const& ex) {
				cout << "Invalid Value..." << ex.what() << endl;
				validInput = false;
				return -1;
			}
		});
}

vector<Types::CharacterClass> UI::AskForPlayerTeamClasses(int teamSize)
{
	vector<Types::CharacterClass> classes;
	for (auto i = 0; i < teamSize; i++) {
		classes.push_back(AskForClass());
	}
	return classes;
}

Types::CharacterClass UI::AskForClass()
{
	return PromptLoop<Types::CharacterClass>([](bool& validInput)->Types::CharacterClass {
		cout << "Choose Between One of this Classes:" << endl;
		cout << "[1] Paladin, [2] Warrior, [3] Cleric, [4] Archer " << endl;
		std::string choiceAsStr;
		std::getline(std::cin, choiceAsStr);
		choiceAsStr = trim(choiceAsStr);
		try {
			Types::CharacterClass choice = static_cast<Types::CharacterClass>(std::stoi(choiceAsStr));
			bool classChoiceIsOk = (choice == Types::CharacterClass::Paladin || 
				choice == Types::CharacterClass::Warrior || choice == Types::CharacterClass::Cleric || 
				choice == Types::CharacterClass::Archer);
			if (!classChoiceIsOk)
				throw std::invalid_argument("out of range");
			validInput = true;
			return choice;
		}
		catch (std::invalid_argument const& ex) {
			cout << "Invalid value..." << ex.what() << endl;
			validInput = false;
			return Types::CharacterClass::Paladin;
		}
		});
}

int UI::AskForNumberOfCharactersInEnemyTeam()
{
	return PromptLoop<int>([](bool& validInput)->int
		{
			try {
				cout << "How many characters on the enemy team? " << endl;
				string choiceAsStr;
				std::getline(std::cin, choiceAsStr);
				choiceAsStr = trim(choiceAsStr);
				int choiceAsNumber = stoi(choiceAsStr);
				if (choiceAsNumber <= 0)
					throw std::invalid_argument("Must have at least one character on the team");
				validInput = true;
				return choiceAsNumber;
			}
			catch (std::invalid_argument const& ex) {
				cout << "Invalid Value..." << ex.what() << endl;
				validInput = false;
				return -1;
			}
		});
}

int UI::AskForNumberOfLines()
{
	
	return ReadPositiveInt("How many lines?");
}

int UI::AskForNumberOfRows()
{
	return ReadPositiveInt("How many rows?");
}

int UI::ReadPositiveInt(const std::string& text)
{
	return PromptLoop<int>([&text](bool& validInput)->int {
		cout << text << endl;
		std::string choiceAsStr;
		std::getline(std::cin, choiceAsStr);
		choiceAsStr = trim(choiceAsStr);
		try {
			int choice = std::stoi(choiceAsStr);
			if (choice > 0) {
				validInput = true;
				return choice;
			}
			else {
				throw std::invalid_argument("must be above 0");
			}
		}
		catch (std::invalid_argument const& ex) {
			cout << "Invalid Value..." << ex.what() << endl;
			validInput = false;
			return -1;
		}
		});

}

UI& UI::Instance() {
	if (instance == nullptr) {
		instance = new UI();
	}
	return *instance;
}

void UI::PlayerClassChoice(const Types::CharacterClass& classIndex) const
{
	string choice = "";
	switch (classIndex) {
	case Types::CharacterClass::Paladin:
		choice = "Paladin";
		break;
	case Types::CharacterClass::Warrior:
		choice = "Warrior";
		break;
	case Types::CharacterClass::Archer:
		choice = "Archer";
		break;
	case Types::CharacterClass::Cleric:
		choice = "Cleric";
		break;
	}
	std::cout << "Player Class Choice: " << choice << endl;
}

void UI::EnemyClassChoice(const Types::CharacterClass& classIndex) const
{
	string choice = "";
	switch (classIndex) {
	case Types::CharacterClass::Paladin:
		choice = "Paladin";
		break;
	case Types::CharacterClass::Warrior:
		choice = "Warrior";
		break;
	case Types::CharacterClass::Archer:
		choice = "Archer";
		break;
	case Types::CharacterClass::Cleric:
		choice = "Cleric";
		break;
	}
	cout << "Enemy Class Choice:" << choice << endl;
}

void UI::NextTurnOrQuitPrompt()
{
	cout << endl << "Click on any key to start the next turn or Esc to quit..." << endl;
	auto k = _getch();
	if (k == KEY_ESC) {
		CONTEXT.Quit();
	}
}

void UI::VictoryOrDefeat(const Types::GameResult& result) const
{
	switch (result)
	{
	case Types::GameResult::Victory:
		cout << "VICTORY! All enemies are dead." << endl;
		break;
	case Types::GameResult::Defeat:
		cout << "DEFEAT! All your characters are dead." << endl;
		break;
	}
}

void UI::BowAttack(const int& originatorIndex, const int& targetIndex) const
{
	cout << "Player " << originatorIndex << " is firing arrows at " << targetIndex << endl;
}

void UI::PlayerIsDead(const int& playerId) const
{
	cout << "Player " << playerId << " is dead." << endl;
}

void UI::PlayerWalkTo(const int& playerId, const string& direction) const
{
	cout << "Player " << playerId << " walked " << direction << endl;
}

void UI::PlayerBaseAttack(const int& originator, const int& subject, const float& damage)
{
	cout << "Player " << originator << " did " << damage << " to Player " << subject << endl;
}

void UI::Charge(const int& originatorIndex, const int& targetIndex) const
{
	cout << "Player " << originatorIndex << " is charging against " << targetIndex << endl;
}

void UI::SelfHeal(const int& originatorIndex) const
{
	cout << "Player " << originatorIndex << " is using self-heal" << endl;
}

void UI::Smite(const int& originator, const int& target) const
{
	cout << "Player " << originator << " is smiting " << target << endl;
}

void UI::Curse(const int& originator) const
{
	cout << "Player " << originator << " is cursing enemies and blessing friends." << endl;
}

void UI::Reanimate(const int& originator, const int& chosen) const
{
	cout << "Player " << originator << " ressurected " << chosen << endl;
}

void UI::PrintInt(const int& someInt) const
{
	cout << someInt << endl;
}

void UI::BattlefieldCreated() const
{
	cout << "the battlefield has been created" << endl;
}

void UI::DrawBattlefield(const std::vector<Types::GridBox*>& grids, const int lines, const int cols) const
{
	stringstream ss;
	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < cols; j++) {
			Types::GridBox* currentGrid = grids[CalculateIndex(i, j, cols)];
			if (currentGrid->ocupied) {
				ss << "[x]";
			}
			else {
				ss << "[ ]";
			}
		}
		ss << endl;
	}
	std::cout << ss.str() << endl;
}

void UI::DrawBattlefield(const std::vector<Types::GridBox*>& grids, vector<shared_ptr<Character>>& players, vector<shared_ptr<Character>>& enemies, const int lines, const int cols)
{
	std::stringstream ss;
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			Types::GridBox* currentGrid = grids[CalculateIndex(i, j, cols)];
			bool drewPlayerOrEnemy = false;
			for (std::shared_ptr<Character>& player : players) {
				if (player->IsDead())
					continue;
				if (player->currentBox && player->currentBox->Line() == i && player->currentBox->Column() == j) {
					switch (player->GetCharacterClass()) {
					case Types::Archer:
						ss << "[A]";
						break;
					case Types::Cleric:
						ss << "[C]";
						break;
					case Types::Paladin:
						ss << "[P]";
						break;
					case Types::Warrior:
						ss << "[W]";
						break;
					}
					drewPlayerOrEnemy = true;
					break;
				}
			}
			for (std::shared_ptr<Character>& enemy : enemies) {
				if (enemy->IsDead())
					continue;
				if (enemy->currentBox && enemy->currentBox->Line() == i && enemy->currentBox->Column() == j) {
					switch (enemy->GetCharacterClass()) {
					case Types::Archer:
						ss << "[a]";
						break;
					case Types::Cleric:
						ss << "[c]";
						break;
					case Types::Paladin:
						ss << "[p]";
						break;
					case Types::Warrior:
						ss << "[w]";
						break;
					}
					drewPlayerOrEnemy = true;
					break;
				}
			}
			if (!drewPlayerOrEnemy) {
				if (currentGrid->ocupied) {
					ss << "[x]";
				}
				else {
					ss << "[ ]";
				}
			}
		}
		ss << endl;
	}
	std::cout << ss.str() << endl;
}

void UI::HealApply(const int& target, const float amount)const
{
	cout << "Player " << target << " will heal " << amount << endl;
}

void UI::StunApply(const int& target) const
{
	cout << "Player " << target << " is stunned" << endl;
}

void UI::PulsaDinuraApply(const int& target) const
{
	cout << "Player " << target << " is burning from curse" << endl;
}

void UI::StrongAttack(const int& originator) const
{
	cout << "Player " << originator << " will do a strong attack!" << endl;
}

void UI::Teleport(const int& originator) const
{
	cout << "Player " << originator << " will teleport away!" << endl;
}

Types::GameSetupParameters UI::AskForParameters()
{
	Types::GameSetupParameters response;
	response.NumberOfCharactersInPlayerTeam = AskForNumberOfCharactersInPlayerTeam();
	response.PlayerTeamClassIds = AskForPlayerTeamClasses(response.NumberOfCharactersInPlayerTeam);
	response.NumberOfCharactersInEnemyTeam = AskForNumberOfCharactersInEnemyTeam();
	response.GridLines = AskForNumberOfLines();
	response.GridRows = AskForNumberOfRows();
	return response;
}

bool UI::AskIfWantToPlayAgain()const
{
	return PromptLoop<bool>([](bool& validInput)->bool {
		cout << "Game is over. Would you like to play again? [y/n] " << endl;
		string choiceAsStr;
		std::getline(std::cin, choiceAsStr);
		choiceAsStr = trim(choiceAsStr);
		if (choiceAsStr == "y" || choiceAsStr == "Y") {
			validInput = true;
			return true;
			
		}
		else if (choiceAsStr == "n" || choiceAsStr == "N")
		{
			validInput = true;
			return false;
		}
		else {
			cout << "Invalid option:" << choiceAsStr << endl;
			validInput = false;
			return false;
		}

	});
}

void UI::Goodbye()const {
	cout << "Goodbye";
	delete instance;
}