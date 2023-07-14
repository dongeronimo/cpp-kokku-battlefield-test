// AutoBattleC++.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//
#include "BattleField.h"
#include <iostream>
#include "Context.h"
#include "BattlefieldSetup.h"
using namespace std;

int main()
{
    //Esse truque com exceção é pq o loop do game é uma recursão e a decisão de parar de jogar
    //normalmente estará bem fundo na recursão gerando um bug onde o player tem q responder 
    //várias vezes que quer sair. O disparo de uma exceção que serve como sinal de fim de jogo
    //é, na prática, igual a um GOTO, mas como GOTOs são proibidos, uso essa técnica com a exceção
    //pra sair da pilha de recursão e sair de maneira correta do jogo. Se eu simplesmente usasse exit()
    //as variáveis de armazanamento automático n são limpas.
    try {
        GameSetupParameters params = AskForParameters();
        //Não havia necessidade de alocá-lo dinamicamente;
        BattleField battlefield(params.GridLines, params.GridRows, params.PlayerTeamClassIds, params.NumberOfCharactersInEnemyTeam);
        battlefield.StartGame();
    }
    catch (QuitGameSignal& ex) {
        cout << "Goodbye";
    }
    return 0;
}




