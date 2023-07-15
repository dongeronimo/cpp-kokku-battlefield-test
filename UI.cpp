#include "UI.h"
#include <iostream>
#include "stringutils.h"
#include <functional>
#include <string>
using namespace std;
shared_ptr<UI> UI::instance = make_shared<UI>();

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

shared_ptr<UI> UI::Instance() {
	return instance;
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
}