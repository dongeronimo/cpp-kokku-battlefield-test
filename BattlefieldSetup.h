#pragma once
#include "Constants.h"
#include <vector>
//Movi o processo de configura��o do jogo para fora do Battlefield pq 
//1) precisava encontrar um ponto por onde puxar o fio da tarefa
//2) ter o processo de configura��o do battlefield dentro do proprio
//battlefield viola a Single Responsability. � o configurador que tem q
//saber configurar, etc.
// n�o � uma classe pq c++ n � java, eu tenho a liberdade de fazer fun��es
//e n�o preciso apertar verbos em substantivos.

/// <summary>
/// Guarda os par�metros escolhidos pelo player.
/// </summary>
struct GameSetupParameters {
    CharacterClass PlayerClassId;
    int GridLines;
    int GridRows;
    int NumberOfCharactersInEnemyTeam;
    int NumberOfCharactersInPlayerTeam;
    //N�o vou ter o sofrimento de lidar com arrays din�micas de baixo n�vel, malloc, calloc, free se eu posso usar uma 
    //estrutura de alto nivel ne? E o custo da passagem por valor � irrelevante j� que isso n�o ser� usado num loop quente
    //do jogo.
    std::vector<CharacterClass> PlayerTeamClassIds;
};

/// <summary>
/// Pede que o player escolha a classe e o tamanho do mapa.
/// </summary>
/// <returns>Os par�metros v�lidos</returns>
GameSetupParameters AskForParameters();

bool AskIfWantToPlayAgain();