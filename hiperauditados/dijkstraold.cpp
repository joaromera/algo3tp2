#include "dijkstraold.h"

using namespace std;

//O(v) + O(v) + O(e) + O(v) + O(v * (v + ve + v))
//O(v * (v + ve + v))
//O(v^2 + v^2 * e + v^2)
//O(v^2 * e)
vector<int> dijkstraOld(const incidences &edgeList, const int &nodes, const int &edges, const int &from) {
    vector<int> visited (nodes,-1);                                                     //O(v)
    visited[from] = 0;

    // Actualizo las distancias desde el nodo de partida hasta sus vecinos
    vector<int> solution (nodes, INF);                                                  //O(v)
    for (auto e : edgeList) {                                                           //O(e)
        if (get<0>(e) == from) {
            solution[get<1>(e)] = get<2>(e);
        }
    }
    solution[from] = 0;

    vector<int> solution_tmp = solution;                                                //O(v)
    int checked_nodes = 1;

    // Mientras no hay chequeado todos los nodos                                        //O(v * (v + ve + v))
    while(checked_nodes != nodes) {                                                         //O(v)
        
        auto w = min_element(solution_tmp.begin(), solution_tmp.end());                         //O(v)
        // Si ya lo visité le cambió el valor para buscar otro mínimo
        if (visited[w - solution_tmp.begin()] == 0) {
            *w = INF;
        } else {
            // Lo marco como visitado, aumento la cantidad de nodos chequeados y relajo distancias de sus vecinos
            visited[w - solution_tmp.begin()] = 0;
            checked_nodes++;
            for (size_t i = 0; i < nodes; i++) {                                                //O(v)
                if (visited[i] == -1) {
                    for (auto e : edgeList) {                                                       //O(e)
                        if (get<1>(e) == i && solution[i] > solution[get<0>(e)] + get<2>(e)) {
                            solution[i] = solution[get<0>(e)] + get<2>(e);
                        }
                    }
                }
            }
            solution_tmp = solution;                                                            //O(v)
        }
    }
    return solution;
}