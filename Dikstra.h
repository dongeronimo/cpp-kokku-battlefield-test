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
    int destLine, int destCol) {
    int lines = battlefield->Lines();
    int cols = battlefield->Columns();
    //sem isso h� um risco do usu�rio informar um mapa grande e o valor de infinito n ser grande o suficiente.
    constexpr int INF = std::numeric_limits<int>::max();
    //Preparando o terreno
    vector<vector<int>> distances(lines, vector<int>(cols, INF)); //Mapa de distancias a partir da origem da busca
    vector<vector<Pair>> predecessors(lines, vector<Pair>(cols, { -1, -1 })); 
    int directionLines[] = { -1, 1, 0, 0 };
    int directionCols[] = { 0, 0, -1, 1 };
    // Fila ordenada. O ordenador � a distancia entre os n�s
    priority_queue<Node, vector<Node>, function<bool(Node, Node)>> priorityQueue(
        [](Node a, Node b) { return a.distance > b.distance; }//lambda q ordena a fila.
    );
    //Come�ando: distancia do pto de origem � considerada = 0
    distances[sourceLine][sourceCol] = 0;
    priorityQueue.push(Node(sourceLine, sourceCol, 0)); //enfia na fila pra ser o pto inicial do processo.
    //Enquanto houver n�s na lista de prioridade...
    while (!priorityQueue.empty()) {
        //Pega o mais longe. No 1o ciclo ser� o pto inicial
        Node current = priorityQueue.top();
        priorityQueue.pop();//saiu da pilha
        // Cheguei no destino, p�ra.
        if (current.line == destLine && current.col == destCol) {
            break;
        }
        // J� visitei, pula.
        if (current.distance > distances[current.line][current.col]) {
            continue;
        }
        //Avalia as distancias dos n�s vizinhos para o n� atual, que por sua vez sabe a sua dist�ncia da origem.
        for (int i = 0; i < 4; i++) {
            int newLine = current.line + directionLines[i];
            int newCol = current.col + directionCols[i];
            // verifica se est� dentro da matriz pra n dar access violation
            if (IsInsideMatrix(newLine, newCol, lines, cols)) {
                // Aumenta a distancia em 1. Todos os elementos do grid tem peso 1. No futuro os varios
                //gridboxes poderiam ter pesos diferentes pra representar por ex. p�ntano.
                int newDist = current.distance + 1;
                auto matrixIsOcupied = battlefield->grids[battlefield->CalculateIndex(newLine, newCol)]->ocupied;
                auto nextPositionIsTheEnd = newLine == destLine && newCol == destCol;
                auto distanceIsSmaller = newDist < distances[newLine][newCol];
                if (distanceIsSmaller //s� processa essa posi��o se ela tiver dist�ncia menor que a dist�ncia atual.
                    &&  //e se ela n�o estiver ocupada ou se estiver ocupada se for a posi��o de fim, que pela forma 
                    (!matrixIsOcupied || (matrixIsOcupied && nextPositionIsTheEnd))) //como o algoritmo � usado no jogo, � onde esta o oponente do char fazendo a navega��o
                {
                    distances[newLine][newCol] = newDist;
                    priorityQueue.push(Node(newLine, newCol, newDist));
                    predecessors[newLine][newCol] = { current.line, current.col };
                }
            }
        }
    }
    // Menor caminho
    vector<Pair> path;
    int line = destLine;
    int col = destCol;

    while (line != -1 && col != -1) {
        path.push_back({ line, col });
        Pair pred = predecessors[line][col];
        line = pred.first;
        col = pred.second;
    }

    reverse(path.begin(), path.end());

    return path;
}
