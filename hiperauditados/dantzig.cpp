#include "dantzig.h"

using namespace std;

void relax(vector<vector<int> > &dists, int from, int middle, int to) {
	if (dists[from][to] > dists[from][middle] + dists[middle][to]) {
		dists[from][to] = dists[from][middle] + dists[middle][to];
	}
}

// O(v^2) + O(e) + O(v) + O(v * (v^2 + v^2))
// O(v^3 + v^3)
// O(v^3)
vector<vector<int> > dantzig(const incidences &edgeList, const int &nodes, const int &edges) {
    vector<vector<int> > distances (nodes, vector<int> (nodes, INF));   // O(v^2)

    // Paso los ejes a la matriz
    for (auto e : edgeList) {                                           // O(e)
        distances[get<0>(e)][get<1>(e)] = get<2>(e);
    }

    // Pongo en 0 las distancias con fila=columna en la matriz
    for (size_t i = 0; i < nodes; i++) {                                // O(v)
        distances[i][i] = 0;
    }

    // Primer loop de Dantzig (ver pseudocódigo teórica)                // O(v * (v^2 + v^2))
    for (int k = 0; k < nodes - 1; k++) {                                                       // O(v)
        // Voy agrandando la parte de la matriz que voy actualizando, es el segundo loop
        for (int i = 0; i <= k; i++) {                                                          // O(v)
            for (int j = 0; j <= k; j++) {                                                      // O(v)
                relax(distances, i, j, k + 1);
                relax(distances, k + 1, j, i);
            }
        }
        // Tercer y cuarto loop de Dantzig
        for (int i = 0; i <= k; i++) {                                                          // O(v)
            for (int j = 0; j <= k; j++) {                                                      // O(v)
                relax(distances, i, k + 1, j);
            }
        }
    }

    return distances;
}