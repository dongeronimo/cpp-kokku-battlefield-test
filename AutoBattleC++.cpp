// AutoBattleC++.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//
#include "BattleField.h"
#include <iostream>
#include "BattlefieldSetup.h"
using namespace std;

int main()
{
    GameSetupParameters params = AskForParameters();
    //Não havia necessidade de alocá-lo dinamicamente;
    BattleField battlefield(params.GridLines, params.GridRows, params.PlayerClassId);
    battlefield.StartGame();
}




