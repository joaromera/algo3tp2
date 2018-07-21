#include "dijkstra.h"

using namespace std;

// O(v) + O(v) + O(d(from)) + O(v^2 + e)
// O(v) + O(v) + O(v) + O(v^2 + e)
// O(v^2 + e)
vector<int> dijkstra(const adjacencies &adjList, const int &nodes, const int &edges, const int &from) {
    vector<bool> visited (nodes,false);                                         //O(v)
    visited[from] = true;

    // Actualizo las distancias desde el nodo de partida hasta sus vecinos
    vector<int> solution (nodes, INF);                                          //O(v)
    for (auto adj : adjList[from]) {                                            //O(d(from))
		solution[get<0>(adj)] = get<1>(adj);
    }
    solution[from] = 0;

    vector<int> solution_tmp = solution;
    int checked_nodes = 1;

    // Mientras no haya chequeado todos los nodos
    while(checked_nodes != nodes) {                                             //O(v^2 + e)
        std::tuple < int, int > minNode = make_tuple(from, INF);
        // Busco el nodo con mínima distancia que aun no haya sido visitado
        for (size_t i = 0; i < nodes; i++) {                                                    //O(v)
			int minNodeW = get <1> (minNode);
			if (!visited[i] && minNodeW >= solution[i]) {
				minNode = make_tuple(i, solution[i]);
			}
		}
		int minNodeIndex = get <0> (minNode);
		visited[minNodeIndex] = true;
        checked_nodes++;
		for (auto adj : adjList[minNodeIndex]) {                                                //O(d(V))
			int adjIndex = get <0> (adj);
			int adjW = get <1> (adj);
			if (solution[adjIndex] > solution[minNodeIndex] + adjW) {
				solution[adjIndex] = solution[minNodeIndex] + adjW;
			}
		}
    }
    return solution;
}