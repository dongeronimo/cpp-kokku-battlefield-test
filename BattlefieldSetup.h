#pragma once
#include "Constants.h"
//Movi o processo de configuração do jogo para fora do Battlefield pq 
//1) precisava encontrar um ponto por onde puxar o fio da tarefa
//2) ter o processo de configuração do battlefield dentro do proprio
//battlefield viola a Single Responsability. É o configurador que tem q
//saber configurar, etc.
// não é uma classe pq c++ n é java, eu tenho a liberdade de fazer funções
//e não preciso apertar verbos em substantivos.

/// <summary>
/// Guarda os parâmetros escolhidos pelo player.
/// </summary>
struct GameSetupParameters {
    CharacterClass PlayerClassId;
    int GridLines;
    int GridRows;
};

/// <summary>
/// Pede que o player escolha a classe e o tamanho do mapa.
/// </summary>
/// <returns>Os parâmetros válidos</returns>
GameSetupParameters AskForParameters();

bool AskIfWantToPlayAgain();