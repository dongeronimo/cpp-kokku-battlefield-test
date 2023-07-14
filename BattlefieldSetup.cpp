#include "BattlefieldSetup.h"
#include <iostream>
#include <string>
#include "stringutils.h"
#include <functional>
using namespace std;
/// <summary>
/// Função genérica pra fazer o loop de pedir resultado.
/// </summary>
/// <typeparam name="ReturnValue">O tipo do que o prompt retorna</typeparam>
/// <param name="bar">A função do prompt. Seu bool& deve retornar true se o prompt foi preeenchido c/sucesso
/// ou false caso contrário pq ele é o usado pra continuar o loop ou não</param>
/// <returns></returns>
template<typename ReturnValue>
ReturnValue foo(ReturnValue(*bar)(bool&)) {
	bool validChoice = false;
	while (!validChoice) {
		ReturnValue result = bar(validChoice);
		if (validChoice)
			return result;
	}
}

int AskForNumberOfCharactersInPlayerTeam();

/// <summary>
/// Encapsula o processo de pedir a classe ao player.
/// </summary>
/// <returns></returns>
CharacterClass ChooseClass();
/// <summary>
/// Encapsula o processo de pedir o numero de linhas do mapa
/// </summary>
/// <returns></returns>
int ChooseLines();
/// <summary>
/// Encapsula o processo de pedir o numero de colunas do mapa
/// </summary>
/// <returns></returns>
int ChooseRows();


GameSetupParameters AskForParameters() {
	GameSetupParameters response;
	int numberOfCharactersInPlayersTeam = AskForNumberOfCharactersInPlayerTeam();
	response.PlayerClassId = ChooseClass();
	response.GridLines = ChooseLines();
	response.GridRows = ChooseRows();
	return response;
}

bool AskIfWantToPlayAgain()
{
	bool validChoice = false;
	bool response = false;
	while (!validChoice) {
		cout << "Game is over. Would you like to play again? [y/n] " << endl;
		string choiceAsStr;
		std::getline(std::cin, choiceAsStr);
		choiceAsStr = trim(choiceAsStr);
		if (choiceAsStr == "y" || choiceAsStr == "Y") {
			response = true;
			validChoice = true;
		}
		else if (choiceAsStr == "n" || choiceAsStr == "N")
		{
			response = false;
			validChoice = true;
		}
		else {
			cout << "Invalid option:" << choiceAsStr << endl;
		}
	}
	return response;
}
int ReadPositiveInt(const std::string& text) {
	bool validChoice = false;
	int result = -1;
	while (validChoice == false) {
		cout << text << endl;
		std::string choiceAsStr;
		std::getline(std::cin, choiceAsStr);
		choiceAsStr = trim(choiceAsStr);
		try {
			int choice = std::stoi(choiceAsStr);
			if (choice > 0) {
				result = choice;
				validChoice = true;
			}
			else {
				throw std::invalid_argument("must be above 0");
			}
		}
		catch (std::invalid_argument const& ex) {
			cout << "Invalid Value..." << ex.what() << endl;
			validChoice = false;
		}
	}
	return result;

}
int ChooseLines()
{
	return ReadPositiveInt("How many lines?");
}
int ChooseRows() {
	return ReadPositiveInt("How many rows?");
}
CharacterClass ChooseClass()
{
	bool classChoiceIsOk = false;
	CharacterClass result = PALADIN;
	while (classChoiceIsOk == false) {
		cout << "Choose Between One of this Classes:" << endl;
		cout << "[1] Paladin, [2] Warrior, [3] Cleric, [4] Archer " << endl;
		std::string choiceAsStr;
		std::getline(std::cin, choiceAsStr);
		choiceAsStr = trim(choiceAsStr);
		try {
			CharacterClass choice = std::stoi(choiceAsStr);
			classChoiceIsOk = (choice == PALADIN || choice == WARRIOR || choice == CLERIC || choice == ARCHER);
			if (!classChoiceIsOk)
				throw std::invalid_argument("out of range");
			result = choice;
		}
		catch (std::invalid_argument const& ex) {
			cout << "Invalid value..." << ex.what() << endl;
			classChoiceIsOk = false;
		}
	}
	return result;
}
int AskForNumberOfCharactersInPlayerTeam() {
	return foo<int>([](bool& validInput)->int
		{
			try {
				cout << "How many characters on your team? " << endl;
				string choiceAsStr;
				std::getline(std::cin, choiceAsStr);
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