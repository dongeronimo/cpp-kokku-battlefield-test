#include "Dikstra.h"

bool IsInsideMatrix(int line, int col, int lines, int cols)
{
	return (line >= 0 && col >= 0 && line < lines && col < cols);
}

vector<Pair> dijkstraShortestPath(const Grid* battlefield,
    const int sourceLine, const int sourceCol,
    const int destLine, const int destCol)
{
    int lines = battlefield->Lines();
    int cols = battlefield->Columns();
    //sem isso há um risco do usuário informar um mapa grande e o valor de infinito n ser grande o suficiente.
    constexpr int INF = std::numeric_limits<int>::max();
    //Preparando o terreno
    vector<vector<int>> distances(lines, vector<int>(cols, INF)); //Mapa de distancias a partir da origem da busca
    vector<vector<Pair>> predecessors(lines, vector<Pair>(cols, { -1, -1 }));
    int directionLines[] = { -1, 1, 0, 0 };
    int directionCols[] = { 0, 0, -1, 1 };
    // Fila ordenada. O ordenador é a distancia entre os nós
    priority_queue<Node, vector<Node>, function<bool(Node, Node)>> priorityQueue(
        [](Node a, Node b) { return a.distance > b.distance; }//lambda q ordena a fila.
    );
    //Começando: distancia do pto de origem é considerada = 0
    distances[sourceLine][sourceCol] = 0;
    priorityQueue.push(Node(sourceLine, sourceCol, 0)); //enfia na fila pra ser o pto inicial do processo.
    //Enquanto houver nós na lista de prioridade...
    while (!priorityQueue.empty()) {
        //Pega o mais longe. No 1o ciclo será o pto inicial
        Node current = priorityQueue.top();
        priorityQueue.pop();//saiu da pilha
        // Cheguei no destino, pára.
        if (current.line == destLine && current.col == destCol) {
            break;
        }
        // Já visitei, pula.
        if (current.distance > distances[current.line][current.col]) {
            continue;
        }
        //Avalia as distancias dos nós vizinhos para o nó atual, que por sua vez sabe a sua distância da origem.
        for (int i = 0; i < 4; i++) {
            int newLine = current.line + directionLines[i];
            int newCol = current.col + directionCols[i];
            // verifica se está dentro da matriz pra n dar access violation
            if (IsInsideMatrix(newLine, newCol, lines, cols)) {
                // Aumenta a distancia em 1. Todos os elementos do grid tem peso 1. No futuro os varios
                //gridboxes poderiam ter pesos diferentes pra representar por ex. pântano.
                int newDist = current.distance + 1;
                auto matrixIsOcupied = battlefield->grids[battlefield->CalculateIndex(newLine, newCol)]->ocupied;
                auto nextPositionIsTheEnd = newLine == destLine && newCol == destCol;
                auto distanceIsSmaller = newDist < distances[newLine][newCol];
                if (distanceIsSmaller //só processa essa posição se ela tiver distância menor que a distância atual.
                    &&  //e se ela não estiver ocupada ou se estiver ocupada se for a posição de fim, que pela forma 
                    (!matrixIsOcupied || (matrixIsOcupied && nextPositionIsTheEnd))) //como o algoritmo é usado no jogo, é onde esta o oponente do char fazendo a navegação
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
        if(!(line == sourceLine && col == sourceCol))
            path.push_back({ line, col });
        Pair pred = predecessors[line][col];
        line = pred.first;
        col = pred.second;
    }

    reverse(path.begin(), path.end());

    return path;
}
