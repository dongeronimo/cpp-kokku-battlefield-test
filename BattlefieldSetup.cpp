#include "BattlefieldSetup.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

using namespace std;
//Obtido de https://stackoverflow.com/questions/216823/how-to-trim-an-stdstring, pq a stl n tem
// trim de string por default e eu quero trimar a string.
//  
// trim from start
std::string& ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
        std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string& rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
        std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
std::string& trim(std::string& s) {
    return ltrim(rtrim(s));
}
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
    response.PlayerClassId = ChooseClass();
    response.GridLines = ChooseLines();
    response.GridRows = ChooseRows();
    return response;
}
int ReadPositiveInt(const std::string& text) {
    bool choiceOk = false;
    int result = -1;
    while (choiceOk == false) {
        cout << text << endl;
        std::string choiceAsStr;
        std::getline(std::cin, choiceAsStr);
        choiceAsStr = trim(choiceAsStr);
        try {
            int choice = std::stoi(choiceAsStr);
            if (choice > 0) {
                result = choice;
                choiceOk = true;
            }
            else {
                throw std::invalid_argument("must be above 0");
            }
        }
        catch (std::invalid_argument const& ex) {
            cout << "Invalid Value..."<<ex.what() << endl;
            choiceOk = false;
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
            if(!classChoiceIsOk)
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