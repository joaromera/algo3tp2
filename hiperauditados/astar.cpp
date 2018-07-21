#include "astar.h"
#include <map>
#include <math.h>

using namespace std;

// O(v) + O(e * log(e)) + O(v * d(v) * log(e)) [Igual a Dijkstra PQ]
vector<int> astar(const adjacencies &adjList, const int &nodes, const int &edges, const int &from) {    
    vector<int> solution (nodes, INF);
    solution[from] = 0;

    priority_Queue_A queue;
    queue.push(make_tuple(from,0,0));

    while (!queue.empty()) {
        tuple<int,int,int> node = queue.top(); queue.pop();

        if (solution[get<0>(node)] < get<1>(node)) continue; //No chequear más de una vez el mismo nodo
        
        for (auto adj : adjList[get<0>(node)]) {

            int new_cost = solution[get<0>(node)] + get<1>(adj);

            if (solution[get<0>(adj)] == INF || (new_cost < solution[get<0>(adj)]) ) {
                solution[get<0>(adj)] = new_cost;
                int priority = new_cost;    //usamos new_cost ya que para este tipo de entradas no disponemos
                                            //de la información necesaria para la heurística
                                            //o sea, es igual a Dijkstra PQ.
                queue.push(make_tuple(get<0>(adj), new_cost, priority));
            }
        }
    }
    return solution;
}