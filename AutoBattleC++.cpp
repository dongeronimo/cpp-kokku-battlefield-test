// AutoBattleC++.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//
#include "BattleField.h"
#include <iostream>
#include "BattlefieldSetup.h"
using namespace std;

int main()
{
    GameSetupParameters params = AskForParameters();
    BattleField* battleField = new BattleField();
    battleField->Setup();
}




