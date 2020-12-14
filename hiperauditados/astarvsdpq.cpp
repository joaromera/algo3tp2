#include <fstream>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <tuple>
#include "commonTypes.h"

using namespace std;

enum Methods { DijkstraPQ,
    AStar };
Methods method = AStar;

int laps = 1;

// Definitions
vector<edge> hiperauditados(const vector<std::tuple<int, int>> &nodesPosition, const incidences &edgeList, const int &nodes, const int &edges);
void getProblemFromFile(const string &fileName, int &nodes, int &edges, vector<std::tuple<int, int>> &nodesPosition, incidences &edgeList);
adjacencies incToAdj(const incidences &edgeList, const int &v, const int &e);
int dijkstrapq(const adjacencies &adjList, const vector<std::tuple<int, int>> &nodesPosition, const int &edges, const int &from, const int &goal);
int astar(const adjacencies &adjList, const vector<std::tuple<int, int>> &nodesPosition, const int &edges, const int &from, const int &goal);

int main(int argc, char *argv[])
{
    int nodes, edges;
    string fileName;

    vector<std::tuple<int, int>> nodesPosition;
    incidences edgeList;

    if (argc > 1)
    {
        fileName = argv[1];
        getProblemFromFile(fileName, nodes, edges, nodesPosition, edgeList);
    }
    else
    {
        cin >> nodes >> edges;
        for (size_t i = 0; i < nodes; i++)
        {
            int x;
            int y;
            cin >> x >> y;
            nodesPosition.emplace_back(x, y);
        }

        for (size_t i = 0; i < edges; i++)
        {
            int edgeA, edgeB, weight;
            cin >> edgeA >> edgeB >> weight;
            edgeList.emplace_back(edgeA, edgeB, weight);
        }
    }

    if (argc > 2)
    {
        if (string(argv[2]) == "DPQ")
        {
            method = DijkstraPQ;
        }
        else if (string(argv[2]) == "A")
        {
            method = AStar;
        }
    }

    if (argc > 3)
    {
        laps = atoi(argv[3]);
        switch (method)
        {
        case DijkstraPQ:
            fileName = "dijkstrapq_" + to_string(nodes) + "v_" + to_string(edges) + "e.csv";
            break;
        case AStar:
            fileName = "astar_" + to_string(nodes) + "v_" + to_string(edges) + "e.csv";
            break;
        }

        chrono::duration<double, milli> average = (chrono::duration<double, milli>)0;
        ofstream results;
        results.open(fileName, fstream::out);
        for (int i = 1; i <= laps; i++)
        {
            auto start = chrono::steady_clock::now();
            vector<edge> results = hiperauditados(nodesPosition, edgeList, nodes, edges);
            auto end = chrono::steady_clock::now();
            auto diff = end - start;
            average += diff;
        }

        switch (method)
        {
        case DijkstraPQ:
            results << "DijkstraPQ"
                    << ";";
            break;
        case AStar:
            results << "AStar"
                    << ";";
            break;
        }

        results << nodes << ";";
        results << edges << ";";
        results << chrono::duration<double, milli>(average / laps).count() << endl;
        results.close();
    }
    else
    {
        vector<edge> results = hiperauditados(nodesPosition, edgeList, nodes, edges);
        for (size_t i = 0; i < results.size(); i++)
        {
            cout << get<0>(results[i]) << " " << get<1>(results[i]) << " " << get<2>(results[i]) << endl;
        }
    }
    return 0;
}

vector<edge> hiperauditados(
    const vector<std::tuple<int, int>> &nodesPosition,
    const incidences &edgeList,
    const int &nodes,
    const int &edges)
{

    adjacencies adjList = incToAdj(edgeList, nodes, edges);
    vector<edge> results;
    results.reserve(nodesPosition.size() * (nodesPosition.size() - 1) / 2);

    switch (method)
    {
    case DijkstraPQ:
        for (int from = 0; from < nodes - 1; from++)
        {
            for (int goal = from + 1; goal < nodes; goal++)
            {
                int distance = dijkstrapq(adjList, nodesPosition, edges, from, goal);
                results.emplace_back(from, goal, distance);
                // cout << from << " " << goal << " " << distance << endl;
            }
        }
        break;
    case AStar:
        for (int from = 0; from < nodes - 1; from++)
        {
            for (int goal = from + 1; goal < nodes; goal++)
            {
                int distance = astar(adjList, nodesPosition, edges, from, goal);
                results.emplace_back(from, goal, distance);
                // cout << from << " " << goal << " " << distance << endl;
            }
        }
        break;
    }

    return results;
}

void getProblemFromFile(
    const string &fileName,
    int &nodes,
    int &edges,
    vector<std::tuple<int, int>> &nodesPosition,
    incidences &edgeList)
{

    ifstream ifs(fileName);
    ifs >> nodes >> edges;
    nodesPosition.reserve(nodes);
    edgeList.reserve(edges);

    for (size_t i = 0; i < nodes; i++)
    {
        int x;
        int y;
        ifs >> x >> y;
        nodesPosition.emplace_back(x, y);
    }

    for (size_t i = 0; i < edges; i++)
    {
        int edgeA, edgeB, weight;
        ifs >> edgeA >> edgeB >> weight;
        edgeList.emplace_back(edgeA, edgeB, weight);
    }

    ifs.close();
}

adjacencies incToAdj(const incidences &edgeList, const int &v, const int &e)
{
    adjacencies adjList;
    adjList.reserve(e);
    adjacents nodeAdjacents;
    nodeAdjacents.reserve(v);

    // Armo lista de adyacencias
    for (int i = 0; i < v; i++)
    {
        adjList.push_back(nodeAdjacents);
    }
    // Agrego los adyacentes y los pesos a cada nodo
    for (int h = 0; h < e; h++)
    {
        edge e = edgeList[h];
        adjList[get<0>(e)].emplace_back(get<1>(e), get<2>(e));
    }
    return adjList;
}

// O(v) + O(e * log(e)) + O(v * d(v) * log(e))
int astar(const adjacencies &adjList, const vector<std::tuple<int, int>> &nodesPosition, const int &, const int &from, const int &goal)
{
    vector<int> solution(nodesPosition.size(), INF);
    solution[from] = 0;

    priority_Queue_A queue;
    queue.emplace(from, 0, 0);

    int goal_x = get<0>(nodesPosition[goal]);
    int goal_y = get<1>(nodesPosition[goal]);

    while (!queue.empty())
    {
        tuple<int, int, int> node = queue.top();
        queue.pop();

        if (solution[get<0>(node)] < get<1>(node)) continue;//No chequear más de una vez el mismo nodo

        if (get<0>(node) == goal)
        {// Cuando llegamos al objetivo termina
            return get<1>(node);
        }

        for (auto adj : adjList[get<0>(node)])
        {

            int new_cost = solution[get<0>(node)] + get<1>(adj);

            if (solution[get<0>(adj)] == INF || (new_cost < solution[get<0>(adj)]))
            {
                solution[get<0>(adj)] = new_cost;
                int x = get<0>(nodesPosition[get<0>(adj)]);
                int y = get<1>(nodesPosition[get<0>(adj)]);
                int dst_x = goal_x - x;
                int dst_y = goal_y - y;
                int priority = sqrt(pow(dst_x, 2) + pow(dst_y, 2));

                queue.emplace(get<0>(adj), new_cost, priority);
            }
        }
    }
    return solution[goal];
}

// O(v) + O(e * log(e)) + O(v * d(v) * log(e))
int dijkstrapq(const adjacencies &adjList, const vector<std::tuple<int, int>> &nodesPosition, const int &, const int &from, const int &goal)
{
    vector<int> solution(nodesPosition.size(), INF);
    solution[from] = 0;

    priority_Queue queue;
    queue.emplace(from, 0);

    while (!queue.empty())
    {
        tuple<int, int> node = queue.top();
        queue.pop();

        if (solution[get<0>(node)] < get<1>(node)) continue;//No chequear más de una vez el mismo nodo

        if (get<0>(node) == goal)
        {// Cuando llegamos al objetivo termina
            return get<1>(node);
        }

        for (auto adj : adjList[get<0>(node)])
        {
            // Relajo las distancias
            if (solution[get<0>(adj)] > solution[get<0>(node)] + get<1>(adj))
            {
                solution[get<0>(adj)] = solution[get<0>(node)] + get<1>(adj);
                queue.emplace(get<0>(adj), solution[get<0>(adj)]);
            }
        }
    }

    return solution[goal];
}