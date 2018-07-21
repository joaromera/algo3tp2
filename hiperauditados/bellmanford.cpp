#include "bellmanford.h"

using namespace std;

//O(v + ve)
//O(ve)
vector<int> bellmanford(const incidences &edgeList, const int &nodes, const int &edges, const int &from) {
    vector<int> solution (nodes, INF); 							// O(v)
    solution[from] = 0;
																// O(ve)
	for (size_t v = 0; v < nodes; v++) { 									// O(v)
		for (auto e : edgeList) {											// O(e)
			int src = get<0>(e);
			int dst = get<1>(e);
			int cst = get<2>(e);
			// Relajo la distancia
			if (solution[src] != INF && solution[src] + cst < solution[dst]) {
				solution[dst] = solution[src] + cst;
			}
		}
	}

    return solution;
}