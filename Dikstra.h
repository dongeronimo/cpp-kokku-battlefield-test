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

vector<Pair> dijkstraShortestPath(const Grid* battlefield,
	int sourceLine, int sourceCol,
	int destLine, int destCol);