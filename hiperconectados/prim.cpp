#include "prim.h"

using namespace std;

//O(v^2 + v + v*(v*log(v) + e*log(v) + log(v)))
//O(v^2 + v + v*log(v)*(v + e + 1))
//O(v^2 + v + v*log(v)*(v + e))
//O(v^2 + v + v^2*log(v))
//O(v^2*log(v))
int prim(adjacencies edgeList, int v, int e) {
    int weight = 0;
    priorityQueue queue;
    vector <int> visited;

    //Initializing data
    for (size_t i = 0; i < v; i++) { //O(v)
        visited.push_back(-1);
    }
    visited[0] = 0;
    int current = 0;

    //O(v*(d(vi)*log(v) + d(vi)*log(v) + log(v)))
    //O(e*log(v) + e*log(v) + v*log(v))
    //O(e*log(v))
    for (int i = 0; i < v - 1; i++) { //O(v)
        adjacents adjacents = edgeList[current];

        //Add neighbours to the queue O(d(vi)*log(v))
        for (int j = 0; j < adjacents.size(); j++) { //O(d(vi))
            if (visited[get <0> (adjacents[j])] == -1) {  
                edge adyacente = make_tuple(current, get <0> (adjacents[j]), get <1> (adjacents[j]));
                queue.push(adyacente); //O(log(v))
            }
        }

        //Find the minimun from the unvisited //O(e*log(v))
        int candidate = get <1> (queue.top());
        while (queue.size() > 0 && visited[candidate] != -1) { //O(e)
            queue.pop(); //O(log(v))
            candidate = get <1> (queue.top());
        }

        //Mark the node as visited
        visited[candidate] = get <0> (queue.top());

        //The tree grows bigger
        weight += get <2> (queue.top());

        //Current gets updated
        current = candidate;

        //Once confirmed its removed
        queue.pop(); //O(log(v))
    }
    
    return weight;
}