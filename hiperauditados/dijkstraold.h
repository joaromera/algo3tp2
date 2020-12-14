#pragma once

#include "commonTypes.h"

//O(v^2 * e)
std::vector<int> dijkstraOld(const incidences &edgeList, const int nodes, const int, const int from)
{
    std::vector<int> visited(nodes, -1);
    visited[from] = 0;

    // Actualizo las distancias desde el nodo de partida hasta sus vecinos
    std::vector<int> solution(nodes, INF);
    for (const auto &e : edgeList)
    {
        if (std::get<0>(e) == from)
        {
            solution[std::get<1>(e)] = std::get<2>(e);
        }
    }
    solution[from] = 0;

    std::vector<int> solution_tmp = solution;

    // Mientras no hay chequeado todos los nodos
    for (int checked_nodes = 1; checked_nodes != nodes; )
    {
        auto w = std::min_element(solution_tmp.begin(), solution_tmp.end());

        // Si ya lo visité le cambió el valor para buscar otro mínimo
        if (visited[w - solution_tmp.begin()] == 0)
        {
            *w = INF;
        }
        else
        {
            // Lo marco como visitado, aumento la cantidad de nodos chequeados
            // y relajo distancias de sus vecinos
            visited[w - solution_tmp.begin()] = 0;
            ++checked_nodes;
            for (size_t i = 0; i < nodes; ++i)
            {
                if (visited[i] == -1)
                {
                    for (const auto &e : edgeList)
                    {
                        if (std::get<1>(e) == i && solution[i] > solution[std::get<0>(e)] + std::get<2>(e))
                        {
                            solution[i] = solution[std::get<0>(e)] + std::get<2>(e);
                        }
                    }
                }
            }
            solution_tmp = solution;
        }
    }
    return solution;
}
