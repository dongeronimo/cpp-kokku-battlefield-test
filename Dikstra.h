#pragma once
//Implementa��o do algoritmo do dikstra. Inicialmente o jogo usava uma
//busca de caminho entre os characters no mapa bem simpl�ria, assumindo
//mapa sem obst�culos e caminhos abertos, buscando a menor Manhattan Distance
//entre A e B a cada loop. 
//So que um dos requisitos da tarefa q me foi passada � flexibilidade e 
//uma flexibilidade � poder ter um mapa com partes bloqueadas, por ex, paredes.
//Pra isso eu preciso do dikstra. Poderia ter usado o A* mas eu n sei implementar o A* :(

#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include "Grid.h"
#include "Constants.h"
using namespace std;
//O grid bidimensional do jogo � um caso especial de grafo e essa estrutura aqui
//representa os n�s do grafo.
struct Node {
	int line;
	int col;
	int distance;
	Node(int l, int c, int d) :
		line(l), col(c), distance(d) {}
};
//a posi��o est� dentro do mapa?
bool IsInsideMatrix(int line, int col, int lines, int cols);

typedef pair<int, int> Pair;
/// <summary>
/// Retorna a lista de posi��es no grid que v�o de source (n�o incluso) at� dest (incluso).
/// Os pares s�o [linha, coluna], com o first sendo linha e o second sendo coluna.
/// </summary>
vector<Pair> dijkstraShortestPath(const Grid* battlefield,
	const int sourceLine, const int sourceCol,
	const int destLine, const int destCol);