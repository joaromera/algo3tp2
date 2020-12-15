#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "astar.h"
#include "bellmanford.h"
#include "commonTypes.h"
#include "dantzig.h"
#include "dijkstra.h"
#include "dijkstraold.h"
#include "dijkstrapq.h"
#include "floydwarshall.h"

enum class Methods
{
    DijkstraOld,
    Dijkstra,
    DijkstraPQ,
    AStar,
    BellmanFord,
    FloydWarshall,
    Dantzig
};

Methods method = Methods::DijkstraPQ;

int laps = 1;

std::vector<edge> hiperauditados(
    const std::vector<int> &litrebycity,
    const incidences &edgeList,
    const int &states,
    const int &nodes,
    const int &edges);

incidences getGraphFromFile(
    const std::string &fileName,
    const int &edges);

incidences graphToStateGraph(
    const std::vector<int> &litrebycity,
    const incidences &edgeList,
    const int &states);

void printSolution(
    const std::vector<int> &distances,
    const int &from,
    const int &nodesWithStates,
    const int &states,
    std::vector<edge> &results);

std::vector<edge> printSolution(
    const std::vector<std::vector<int>> &matrix,
    const int &from,
    const int &nodesWithStates,
    const int &states);

void getProblemFromFile(
    const std::string &fileName,
    int &nodes,
    int &edges,
    std::vector<int> &litrebycity,
    incidences &edgeList);

adjacencies incToAdj(
    const incidences &edgeList,
    const int &v,
    const int &e);

int main(int argc, char *argv[])
{
    int nodes, edges;
    int states = 61;
    std::string fileName;

    std::vector<int> litrebycity;
    incidences edgeList;

    if (argc > 1)
    {
        fileName = argv[1];
        getProblemFromFile(fileName, nodes, edges, litrebycity, edgeList);
    }
    else
    {
        std::cin >> nodes >> edges;
        for (int i = 0; i < nodes; i++)
        {
            int litrecost;
            std::cin >> litrecost;
            litrebycity.emplace_back(litrecost);
        }

        for (int i = 0; i < edges; i++)
        {
            int edgeA, edgeB, weight;
            std::cin >> edgeA >> edgeB >> weight;
            edgeList.emplace_back(edgeA, edgeB, weight);
        }
    }

    if (argc > 2)
    {
        const std::string input_method = argv[2];

        if (input_method == "DO")
        {
            method = Methods::DijkstraOld;
        }
        else if (input_method == "D")
        {
            method = Methods::Dijkstra;
        }
        else if (input_method == "DPQ")
        {
            method = Methods::DijkstraPQ;
        }
        else if (input_method == "A")
        {
            method = Methods::AStar;
        }
        else if (input_method == "BF")
        {
            method = Methods::BellmanFord;
        }
        else if (input_method == "FW")
        {
            method = Methods::FloydWarshall;
        }
        else if (input_method == "DZ")
        {
            method = Methods::Dantzig;
        }
    }

    if (argc > 3)
    {
        laps = atoi(argv[3]);
        switch (method)
        {
        case Methods::DijkstraOld:
            fileName = "dijkstraold_" + std::to_string(nodes) + "v_" + std::to_string(edges) + "e.csv";
            break;
        case Methods::Dijkstra:
            fileName = "dijkstra_" + std::to_string(nodes) + "v_" + std::to_string(edges) + "e.csv";
            break;
        case Methods::DijkstraPQ:
            fileName = "dijkstrapq_" + std::to_string(nodes) + "v_" + std::to_string(edges) + "e.csv";
            break;
        case Methods::AStar:
            fileName = "astar_" + std::to_string(nodes) + "v_" + std::to_string(edges) + "e.csv";
            break;
        case Methods::BellmanFord:
            fileName = "bellmanford_" + std::to_string(nodes) + "v_" + std::to_string(edges) + "e.csv";
            break;
        case Methods::FloydWarshall:
            fileName = "floydwarshall_" + std::to_string(nodes) + "v_" + std::to_string(edges) + "e.csv";
            break;
        case Methods::Dantzig:
            fileName = "dantzig_" + std::to_string(nodes) + "v_" + std::to_string(edges) + "e.csv";
            break;
        }

        std::chrono::duration<double, std::milli> average = (std::chrono::duration<double, std::milli>)0;
        std::ofstream results;
        results.open(fileName, std::fstream::out);

        for (int i = 1; i <= laps; i++)
        {
            auto start = std::chrono::steady_clock::now();
            std::vector<edge> results = hiperauditados(litrebycity, edgeList, states, nodes, edges);
            auto end = std::chrono::steady_clock::now();
            auto diff = end - start;
            average += diff;
        }

        switch (method)
        {
        case Methods::DijkstraOld:
            results << "Dijkstra Old" << ";";
            break;
        case Methods::Dijkstra:
            results << "Dijkstra" << ";";
            break;
        case Methods::DijkstraPQ:
            results << "DijkstraPQ" << ";";
            break;
        case Methods::AStar:
            results << "AStar" << ";";
            break;
        case Methods::BellmanFord:
            results << "BellmanFord" << ";";
            break;
        case Methods::FloydWarshall:
            results << "FloydWarshall" << ";";
            break;
        case Methods::Dantzig:
            results << "Dantzig" << ";";
            break;
        }

        results << nodes << ";"
                << edges << ";"
                << std::chrono::duration<double, std::milli>(average / laps).count()
                << std::endl;
        results.close();
    }
    else
    {
        std::vector<edge> results = hiperauditados(litrebycity, edgeList, states, nodes, edges);

        for (size_t i = 0; i < results.size(); i++)
        {
            std::cout << std::get<0>(results[i]) << " "
                      << std::get<1>(results[i]) << " "
                      << std::get<2>(results[i])
                      << std::endl;
        }
    }
    return 0;
}

std::vector<edge> hiperauditados(
    const std::vector<int> &litrebycity,
    const incidences &edgeList,
    const int &states,
    const int &nodes,
    const int &)
{
    incidences stateGraph = graphToStateGraph(litrebycity, edgeList, states);

    const int nodesWithStates = nodes * states;
    const int edgesWithStates = stateGraph.size();
    const int from = states - 1;

    std::vector<edge> results;
    std::vector<std::vector<int>> matrix;
    std::vector<int> distances;
    adjacencies adjList;

    switch (method)
    {
    case Methods::DijkstraOld:
        for (int i = from; i < nodesWithStates - 1; i += states)
        {
            distances = dijkstraOld(stateGraph, nodesWithStates, i);
            printSolution(distances, i, nodesWithStates, states, results);
        }
        break;
    case Methods::Dijkstra:
        adjList = incToAdj(stateGraph, nodesWithStates, edgesWithStates);
        for (int i = from; i < nodesWithStates - 1; i += states)
        {
            distances = dijkstra(adjList, nodesWithStates, i);
            printSolution(distances, i, nodesWithStates, states, results);
        }
        break;
    case Methods::DijkstraPQ:
        adjList = incToAdj(stateGraph, nodesWithStates, edgesWithStates);
        for (int i = from; i < nodesWithStates - 1; i += states)
        {
            distances = dijkstrapq(adjList, nodesWithStates, i);
            printSolution(distances, i, nodesWithStates, states, results);
        }
        break;
    case Methods::AStar:
        adjList = incToAdj(stateGraph, nodesWithStates, edgesWithStates);
        for (int i = from; i < nodesWithStates - 1; i += states)
        {
            distances = astar(adjList, nodesWithStates, i);
            printSolution(distances, i, nodesWithStates, states, results);
        }
        break;
    case Methods::BellmanFord:
        for (int i = from; i < nodesWithStates - 1; i += states)
        {
            distances = bellmanford(stateGraph, nodesWithStates, i);
            printSolution(distances, i, nodesWithStates, states, results);
        }
        break;
    case Methods::FloydWarshall:
        matrix = floydwarshall(stateGraph, nodesWithStates);
        results = printSolution(matrix, from, nodesWithStates, states);
        break;
    case Methods::Dantzig:
        matrix = dantzig(stateGraph, nodesWithStates);
        results = printSolution(matrix, from, nodesWithStates, states);
        break;
    }

    return results;
}

incidences getGraphFromFile(const std::string &fileName, const int &edges)
{
    incidences edgeList;
    std::ifstream ifs(fileName);
    std::string skip;
    std::getline(ifs, skip);

    for (int i = 0; i < edges; i++)
    {
        int edgeA, edgeB, weight;
        ifs >> edgeA >> edgeB >> weight;
        edgeList.emplace_back(edgeA, edgeB, weight);
    }

    ifs.close();
    return edgeList;
}

void getProblemFromFile(
    const std::string &fileName,
    int &nodes,
    int &edges,
    std::vector<int> &litrebycity,
    incidences &edgeList)
{
    std::ifstream ifs(fileName);
    ifs >> nodes >> edges;
    litrebycity.reserve(nodes);
    edgeList.reserve(edges);

    for (int i = 0; i < nodes; i++)
    {
        int cost_in_city_i;
        ifs >> cost_in_city_i;
        litrebycity.emplace_back(cost_in_city_i);
    }

    for (int i = 0; i < edges; i++)
    {
        int edgeA, edgeB, weight;
        ifs >> edgeA >> edgeB >> weight;
        edgeList.emplace_back(edgeA, edgeB, weight);
    }

    ifs.close();
}

incidences graphToStateGraph(
    const std::vector<int> &litrebycity,
    const incidences &edgeList,
    const int &states)
{
    incidences stateGraph;

    for (int i = 1; i < states; i++)
    {
        int j = i - 1;
        for (size_t k = 0; k < litrebycity.size(); k++)
        {
            stateGraph.emplace_back(j + states * k, i + states * k, litrebycity[k]);
        }
        for (auto e : edgeList)
        {
            int nodeA = std::get<0>(e);
            int nodeB = std::get<1>(e);
            int weight = std::get<2>(e);
            if (i >= weight)
            {
                stateGraph.emplace_back(i + nodeA * states, i - weight + nodeB * states, 0);
                stateGraph.emplace_back(i + nodeB * states, i - weight + nodeA * states, 0);
            }
        }
    }
    return stateGraph;
}

std::vector<edge> printSolution(
    const std::vector<std::vector<int>> &matrix,
    const int &from,
    const int &nodesWithStates,
    const int &states)
{
    std::vector<edge> results;

    for (int i = from; i < nodesWithStates - 1; i += states)
    {
        for (int j = i + states; j < nodesWithStates; j += states)
        {
            int min = INF;
            for (int k = j - states; k < j; k++)
            {
                if (matrix[i][k] < min)
                {
                    min = matrix[i][k];
                }
            }
            results.emplace_back(i / states, j / states, min);
        }
    }

    return results;
}

void printSolution(
    const std::vector<int> &distances,
    const int &from,
    const int &nodesWithStates,
    const int &states,
    std::vector<edge> &results)
{
    for (int j = from + states; j < nodesWithStates; j += states)
    {
        int min = *min_element(distances.begin() + j - states, distances.begin() + j);
        results.emplace_back(from / states, j / states, min);
    }
}

// O(v+e)
adjacencies incToAdj(const incidences &edgeList, const int &v, const int &e)
{
    adjacencies adjList;
    adjList.reserve(e);
    adjacents nodeAdjacents;
    nodeAdjacents.reserve(v);

    for (int i = 0; i < v; i++)
    {
        adjList.push_back(nodeAdjacents);
    }

    for (int h = 0; h < e; h++)
    {
        edge e = edgeList[h];
        adjList[std::get<0>(e)].emplace_back(std::get<1>(e), std::get<2>(e));
    }
    return adjList;
}
