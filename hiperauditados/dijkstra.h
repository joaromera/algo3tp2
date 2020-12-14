#pragma once

#include "commonTypes.h"

// O(v^2 + e)
std::vector<int> dijkstra(const adjacencies &adjList, const int nodes, const int, const int from)
{
    std::vector<bool> visited(nodes, false);
    visited[from] = true;

    // Actualizo las distancias desde el nodo de partida hasta sus vecinos
    std::vector<int> solution(nodes, INF);
    for (const auto &adj : adjList[from])
    {
        solution[std::get<0>(adj)] = std::get<1>(adj);
    }
    solution[from] = 0;

    std::vector<int> solution_tmp = solution;

    // Mientras no haya chequeado todos los nodos
    for (int checked_nodes = 1; checked_nodes != nodes; )
    {
        std::tuple<int, int> minNode = { from, INF };

        // Busco el nodo con mínima distancia que aun no haya sido visitado
        for (size_t i = 0; i < nodes; ++i)
        {
            const int minNodeW = std::get<1>(minNode);
            if (!visited[i] && minNodeW >= solution[i])
            {
                minNode = { i, solution[i] };
            }
        }

        const int minNodeIndex = std::get<0>(minNode);
        visited[minNodeIndex] = true;
        ++checked_nodes;

        for (const auto &adj : adjList[minNodeIndex])
        {
            const int adjIndex = std::get<0>(adj);
            const int adjW     = std::get<1>(adj);
            if (solution[adjIndex] > solution[minNodeIndex] + adjW)
            {
                solution[adjIndex] = solution[minNodeIndex] + adjW;
            }
        }
    }
    return solution;
}
