#pragma once
#include "Constants.h"
/// <summary>
/// Guarda os par�metros escolhidos pelo player.
/// </summary>
struct GameSetupParameters {
    CharacterClass PlayerClassId;
    int GridLines;
    int GridRows;
};

/// <summary>
/// Pede que o player escolha a classe e o tamanho do mapa.
/// </summary>
/// <returns>Os par�metros v�lidos</returns>
GameSetupParameters AskForParameters();
