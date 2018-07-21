#include "floydwarshall.h"

using namespace std;

void relax(vector<vector<int> > &dists, int &from, int &middle, int &to) {
	if (dists[from][to] > dists[from][middle] + dists[middle][to]) {
		dists[from][to] = dists[from][middle] + dists[middle][to];
	}
}

// O(v^2) + O(e) + O(v) + O(v^3)
// O(v^3)
vector<vector<int> > floydwarshall(const incidences &edgeList, const int &nodes, const int &edges) {
    // Inicializo la matriz con INF en todas las posiciones
    vector<vector<int> > distances (nodes, vector<int> (nodes, INF));           // O(v^2)

    // Por cada arista actualizo la distancia de los nodos que conecta
    for (auto e : edgeList) {                                                   // O(e)
        distances[get<0>(e)][get<1>(e)] = get<2>(e);
    }

    // Para cada nodo pongo en 0 la distancia a sí mismo
    for (size_t i = 0; i < nodes; i++) {                                        // O(v)
        distances[i][i] = 0;
    }

    // Triple for de Dantzig, ver pseudocódigo teórica
    for (int k = 0; k < nodes; k++) {                                           // O(v^3)
        for (int i = 0; i < nodes; i++) {
            if (i != k && distances[i][k] != INF) {
                for (int j = 0; j < nodes; j++) {
                    if (j != k && j != i) {
                        relax(distances, i, k, j);
                    }
                }
            }
        }
    }

    return distances;
}