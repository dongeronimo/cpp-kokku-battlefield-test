#pragma once

/// <summary>
/// Guarda os parâmetros escolhidos pelo player.
/// </summary>
struct GameSetupParameters {
    int PlayerClassId;
    int GridLines;
    int GridRows;
};

/// <summary>
/// Pede que o player escolha a classe e o tamanho do mapa.
/// </summary>
/// <returns>Os parâmetros válidos</returns>
GameSetupParameters AskForParameters();
