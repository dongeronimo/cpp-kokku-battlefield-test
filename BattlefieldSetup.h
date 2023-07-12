#pragma once

/// <summary>
/// Guarda os par�metros escolhidos pelo player.
/// </summary>
struct GameSetupParameters {
    int PlayerClassId;
    int GridLines;
    int GridRows;
};

/// <summary>
/// Pede que o player escolha a classe e o tamanho do mapa.
/// </summary>
/// <returns>Os par�metros v�lidos</returns>
GameSetupParameters AskForParameters();
