//#pragma once
//#include "Constants.h"
//#include <vector>
//#include "Types.h"
////Movi o processo de configura��o do jogo para fora do Battlefield pq 
////1) precisava encontrar um ponto por onde puxar o fio da tarefa
////2) ter o processo de configura��o do battlefield dentro do proprio
////battlefield viola a Single Responsability. � o configurador que tem q
////saber configurar, etc.
//// n�o � uma classe pq c++ n � java, eu tenho a liberdade de fazer fun��es
////e n�o preciso apertar verbos em substantivos.
//
//
//
///// <summary>
///// Pede que o player escolha a classe e o tamanho do mapa.
///// </summary>
///// <returns>Os par�metros v�lidos</returns>
//Types::GameSetupParameters AskForParameters();
//
//bool AskIfWantToPlayAgain();