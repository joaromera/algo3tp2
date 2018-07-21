#include <fstream>
#include <stdlib.h>
#include <string>

#include "commonTypes.h"
#include "dijkstraold.h"
#include "dijkstra.h"
#include "dijkstrapq.h"
#include "astar.h"
#include "bellmanford.h"
#include "floydwarshall.h"
#include "dantzig.h"

using namespace std;

enum Methods {
    DijkstraOld,
    Dijkstra,
    DijkstraPQ,
    AStar,
    BellmanFord,
    FloydWarshall,
    Dantzig
};

Methods method = DijkstraPQ;

int laps = 1;

vector < edge > hiperauditados(
    const vector < int > & litrebycity,
    const incidences & edgeList,
    const int & states,
    const int & nodes,
    const int & edges
);
    
incidences getGraphFromFile(
    const string & fileName, 
    const int & edges
);

incidences graphToStateGraph(
    const vector < int > & litrebycity, 
    const incidences & edgeList, 
    const int & states
);

void printSolution(
    const vector < int > & distances,
    const int & from,
    const int & nodesWithStates,
    const int & states,
    vector < edge > & results
);

vector < edge > printSolution(
    const vector < vector < int > > & matrix,
    const int & from,
    const int & nodesWithStates,
    const int & states
);

void getProblemFromFile(
    const string & fileName, 
    int & nodes, 
    int & edges,
    vector < int > & litrebycity, 
    incidences & edgeList
);

adjacencies incToAdj(
    const incidences &edgeList,
    const int &v,
    const int &e
);

int main(int argc, char * argv[]) {
    int nodes, edges;
    int states = 61;
    string fileName;

    vector < int > litrebycity;
    incidences edgeList;

    if (argc > 1) {
        fileName = argv[1];
        getProblemFromFile(fileName, nodes, edges, litrebycity, edgeList);
    } else {
        cin >> nodes >> edges;
        for (size_t i = 0; i < nodes; i++) {
            int litrecost;
            cin >> litrecost;
            litrebycity.push_back(litrecost);
        }

        for (size_t i = 0; i < edges; i++) {
            int edgeA, edgeB, weight;
            cin >> edgeA >> edgeB >> weight;
            edgeList.push_back(make_tuple(edgeA, edgeB, weight));
        }
    }

    if (argc > 2) {
        if (string(argv[2]) == "DO") {
            method = DijkstraOld;
        } else if (string(argv[2]) == "D") {
            method = Dijkstra;
        } else if (string(argv[2]) == "DPQ") {
            method = DijkstraPQ;
        } else if (string(argv[2]) == "A") {
            method = AStar;
        } else if (string(argv[2]) == "BF") {
            method = BellmanFord;
        } else if (string(argv[2]) == "FW") {
            method = FloydWarshall;
        } else if (string(argv[2]) == "DZ") {
            method = Dantzig;
        }
    }

    if (argc > 3) {
        laps = atoi(argv[3]);
        switch (method) {
            case DijkstraOld:
                fileName = "dijkstraold_" + to_string(nodes) + "v_" + to_string(edges) + "e.csv";
                break;
            case Dijkstra:
                fileName = "dijkstra_" + to_string(nodes) + "v_" + to_string(edges) + "e.csv";
                break;
            case DijkstraPQ:
                fileName = "dijkstrapq_" + to_string(nodes) + "v_" + to_string(edges) + "e.csv";
                break;
            case AStar:
                fileName = "astar_" + to_string(nodes) + "v_" + to_string(edges) + "e.csv";
                break;
            case BellmanFord:
                fileName = "bellmanford_" + to_string(nodes) + "v_" + to_string(edges) + "e.csv";
                break;
            case FloydWarshall:
                fileName = "floydwarshall_" + to_string(nodes) + "v_" + to_string(edges) + "e.csv";
                break;
            case Dantzig:
                fileName = "dantzig_" + to_string(nodes) + "v_" + to_string(edges) + "e.csv";
                break;
        }

        chrono::duration < double, milli > average = (chrono::duration < double, milli > ) 0;
        ofstream results;
        results.open(fileName, fstream::out);
        for (int i = 1; i <= laps; i++) {
            auto start = chrono::steady_clock::now();
            vector < edge > results = hiperauditados(litrebycity, edgeList, states, nodes, edges);
            auto end = chrono::steady_clock::now();
            auto diff = end - start;
            average += diff;
        }
        
        switch (method) {
            case DijkstraOld:
                results << "Dijkstra Old" << ";";
                break;
            case Dijkstra:
                results << "Dijkstra" << ";";
                break;
            case DijkstraPQ:
                results << "DijkstraPQ" << ";";
                break;
            case AStar:
                results << "AStar" << ";";
                break;
            case BellmanFord:
                results << "BellmanFord" << ";";
                break;
            case FloydWarshall:
                results << "FloydWarshall" << ";";
                break;
            case Dantzig:
                results << "Dantzig" << ";";
                break;
        }

        results << nodes << ";";
        results << edges << ";";
        results << chrono::duration < double, milli > (average / laps).count() << endl;
        results.close();
    } else {
        vector < edge > results = hiperauditados(litrebycity, edgeList, states, nodes, edges);
        for (size_t i = 0; i < results.size(); i++) {
            cout << get < 0 > (results[i]) << " " << get < 1 > (results[i]) << " " << get < 2 > (results[i]) << endl;
        }
    }
    return 0;
}

vector < edge > hiperauditados (
    const vector < int > & litrebycity,
    const incidences & edgeList,
    const int & states,
    const int & nodes,
    const int & edges) {
    
    // Crear grafo de estados a partir del original 
    incidences stateGraph = graphToStateGraph(litrebycity, edgeList, states);               //O(e)

    // Calculo cantidad de nodos y ejes para los nuevos estados
    int nodesWithStates = nodes * states;
    int edgesWithStates = stateGraph.size();
    int from = states - 1; // Punto de partida con tanque lleno

    vector < edge > results;
    vector < vector < int > > matrix;
    vector < int > distances;
	adjacencies adjList;
    
    switch (method) {
        case DijkstraOld:
            // O(v * (v^2 * e + v))
            // O(v^3 * e + v^2)
            // O(v^3 * e)
            for (int i = from; i < nodesWithStates - 1; i += states) {                      // O(v)
                distances = dijkstraOld(stateGraph, nodesWithStates, edgesWithStates, i);       // O(v^2 * e)
                printSolution(distances, i, nodesWithStates, states, results);                  // O(v)
            }
            break;
        case Dijkstra:
            // O(v + e) + O(v * (v^2 + e + v))
            // O(v + e) + O(v^3 + v^2 + e)
            // O(v^3)
            adjList = incToAdj(stateGraph, nodesWithStates, edgesWithStates);               // O(v+e)
            for (int i = from; i < nodesWithStates - 1; i += states) {                      // O(v)
                distances = dijkstra(adjList, nodesWithStates, edgesWithStates, i);             // O(v^2 + e)
				printSolution(distances, i, nodesWithStates, states, results);                  // O(v)
            }
            break;
        case DijkstraPQ:
            //O(v + e) + O(v * (v + e * log(e) + v))
            //O(v + e) + O(v^2 + v * e * log(e) + v^2)
            //O(v + e) + O(v^2 + v * e * log(e))
            //O(v^2 + v * e * log(e))
            adjList = incToAdj(stateGraph, nodesWithStates, edgesWithStates);               // O(v+e)
            for (int i = from; i < nodesWithStates - 1; i += states) {                      // O(v)
                distances = dijkstrapq(adjList, nodesWithStates, edgesWithStates, i);           // O(v) + O(e * log(e))
                printSolution(distances, i, nodesWithStates, states, results);                  // O(v)
            }
            break;
        case AStar:
            //O(v + e) + O(v * (v + e * log(e) + v))
            //O(v + e) + O(v^2 + v * e * log(e) + v^2)
            //O(v + e) + O(v^2 + v * e * log(e))
            //O(v^2 + v * e * log(e))
            adjList = incToAdj(stateGraph, nodesWithStates, edgesWithStates);               // O(v+e)
            for (int i = from; i < nodesWithStates - 1; i += states) {                      // O(v)
                distances = astar(adjList, nodesWithStates, edgesWithStates, i);                // O(v) + O(e * log(e))
                printSolution(distances, i, nodesWithStates, states, results);                  // O(v)
            }
            break;
        case BellmanFord:
            //O(v * (ve + v))
            //O(v^2 * e + v^2)
            //O(v^3)
            for (int i = from; i < nodesWithStates - 1; i += states) {                      // O(v)
                distances = bellmanford(stateGraph, nodesWithStates, edgesWithStates, i);       // O (ve)
                printSolution(distances, i, nodesWithStates, states, results);                  // O (v)
            }
            break;
        case FloydWarshall:
            //O(v^3 + v^2)
            //O(v^3)
            matrix = floydwarshall(stateGraph, nodesWithStates, edgesWithStates);           // O(v^3)
            results = printSolution(matrix, from, nodesWithStates, states);                 // O(v^2)
            break;
        case Dantzig:
            //O(v^3 + v^2)
            //O(v^3)
            matrix = dantzig(stateGraph, nodesWithStates, edgesWithStates);                 // O(v^3)
            results = printSolution(matrix, from, nodesWithStates, states);                 // O(v^2)
            break;
    }
    
    return results;
}

incidences getGraphFromFile (const string & fileName, const int & edges) {
    incidences edgeList;
    ifstream ifs(fileName);
    string skip;
    getline(ifs, skip);

    for (size_t i = 0; i < edges; i++) {
        int edgeA, edgeB, weight;
        ifs >> edgeA >> edgeB >> weight;
        edgeList.push_back(make_tuple(edgeA, edgeB, weight));
    }

    ifs.close();
    return edgeList;
}

void getProblemFromFile (
    const string & fileName, 
    int & nodes, 
    int & edges, 
    vector < int > & litrebycity, 
    incidences & edgeList) {

    ifstream ifs(fileName);
    ifs >> nodes >> edges;
    litrebycity.reserve(nodes);
    edgeList.reserve(edges);

    for (size_t i = 0; i < nodes; i++) {
        int cost_in_city_i;
        ifs >> cost_in_city_i;
        litrebycity.push_back(cost_in_city_i);
    }

    for (size_t i = 0; i < edges; i++) {
        int edgeA, edgeB, weight;
        ifs >> edgeA >> edgeB >> weight;
        edgeList.push_back(make_tuple(edgeA, edgeB, weight));
    }

    ifs.close();
}

incidences graphToStateGraph (
    const vector < int > & litrebycity, 
    const incidences & edgeList, 
    const int & states) {
		
    incidences stateGraph;
	
    for (size_t i = 1; i < states; i++) {
        int j = i-1;
		for (size_t k = 0; k < litrebycity.size(); k++) {
			stateGraph.push_back(make_tuple(j + states * k, i + states * k, litrebycity[k]));
		}
		for (auto e : edgeList) {
			int nodeA = get<0>(e);
			int nodeB = get<1>(e);
			int weight = get<2>(e);
			if (i >= weight) {
                stateGraph.push_back(make_tuple(i + nodeA * states, i - weight + nodeB * states, 0));
                stateGraph.push_back(make_tuple(i + nodeB * states, i - weight + nodeA * states, 0));
            }
        }
    }
    return stateGraph;
}

vector < edge > printSolution (
    const vector < vector < int > > & matrix, 
    const int & from, 
    const int & nodesWithStates, 
    const int & states) {
    
    vector < edge > results;
    
    for (size_t i = from; i < nodesWithStates - 1; i += states) {           // O(v)
        for (int j = i + states; j < nodesWithStates; j += states) {        // O(v)
            int min = INF;
            for (size_t k = j - states; k < j; k++) {                       // O(60)
                if (matrix[i][k] < min) {
                    min = matrix[i][k];
                }
            }
            edge edge = make_tuple(i / states, j / states, min);
            results.push_back(edge);
        }
    }
    
    return results;
}

void printSolution (
    const vector < int > & distances, 
    const int & from, 
    const int & nodesWithStates, 
    const int & states,
    vector < edge > & results) {
    
    edge edge;
    
    for (int j = from + states; j < nodesWithStates; j += states) {                         // O(v)
        int min = * min_element(distances.begin() + j - states, distances.begin() + j);     // O(60)
        edge = make_tuple(from / states, j / states, min);
        results.push_back(edge);
    }
}

// O(v+e)
adjacencies incToAdj(const incidences &edgeList, const int &v, const int &e) {
    adjacencies adjList;
    adjList.reserve(e);                                                         // O(e)
    adjacents nodeAdjacents;
    nodeAdjacents.reserve(v);                                                   // O(v)

    // Armo lista de adyacencias
    for (int i = 0; i < v; i++) {                                               // O(v)
        adjList.push_back(nodeAdjacents);
    }
    // Agrego los adyacentes y los pesos a cada nodo
    for (int h = 0; h < e; h++) {                                               // O(e)
        edge e = edgeList[h];
        adjList[get <0> (e)].push_back(make_tuple(get <1> (e), get <2> (e)));
    }
    return adjList;
}