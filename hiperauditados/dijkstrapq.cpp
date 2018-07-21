#include "dijkstrapq.h"

using namespace std;

// O(v) + O(e * log(e)) + O(v * d(v) * log(e))
// O(v) + O(e * log(e)) + O(e * log(e))
// O(v) + O(e * log(e))
vector<int> dijkstrapq(const adjacencies &adjList, const int &nodes, const int &edges, const int &from) {    
    vector<int> solution (nodes, INF);                              //O(v)
    solution[from] = 0;

    priority_Queue queue;
    queue.push(make_tuple(from,0));

    while (!queue.empty()) {
        tuple<int,int> node = queue.top();                          //O(1) e veces
	    queue.pop();                                                //O(log(e)) e veces

        if (solution[get<0>(node)] < get<1>(node)) continue; //No chequear más de una vez el mismo nodo

        for (auto adj : adjList[get<0>(node)]) {                    //O(d(v)) v veces
            // Relajo las distancias
            if (solution[get<0>(adj)] > solution[get<0>(node)] + get<1>(adj)) {
                solution[get<0>(adj)] = solution[get<0>(node)] + get<1>(adj);
                queue.push(make_tuple(get<0>(adj), solution[get<0>(adj)])); //O(log(e)) d(v) veces v veces
            }
        }
    }

    return solution;
}
