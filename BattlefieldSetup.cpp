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
GameSetupParameters AskForParameters() {
    bool classChoiceIsOk = false;
    GameSetupParameters response;
    while (classChoiceIsOk == false) {
        cout << "Choose Between One of this Classes:" << endl;
        cout << "[1] Paladin, [2] Warrior, [3] Cleric, [4] Archer " << endl;
        std::string choiceAsStr;
        std::getline(std::cin, choiceAsStr);
        choiceAsStr = trim(choiceAsStr);
        try {
            int choice = std::stoi(choiceAsStr);
            switch (choice) {
            case 1:
                response.PlayerClassId = 1;
                classChoiceIsOk = true;
                break;
            case 2:
                response.PlayerClassId = 1;
                classChoiceIsOk = true;
                break;
            case 3:
                response.PlayerClassId = 1;
                classChoiceIsOk = true;
                break;
            case 4:
                response.PlayerClassId = 1;
                classChoiceIsOk = true;
                break;
            default:
                throw std::invalid_argument("out of range");
            }
        }
        catch (std::invalid_argument const& ex) {
            cout << "Invalid value...";
            classChoiceIsOk = false;
        }
    }
}