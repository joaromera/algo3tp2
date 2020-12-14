#pragma once

#include "commonTypes.h"

namespace FloydWarshall_NS {

void relax(std::vector<std::vector<int>> &dists, int &from, int &middle, int &to)
{
    if (dists[from][to] > dists[from][middle] + dists[middle][to])
    {
        dists[from][to] = dists[from][middle] + dists[middle][to];
    }
}

}

// O(v^3)
std::vector<std::vector<int>> floydwarshall(const incidences &edgeList, const int &nodes)
{
    std::vector<std::vector<int>> distances(nodes, std::vector<int>(nodes, INF));

    // Por cada arista actualizo la distancia de los nodos que conecta
    for (const auto &e : edgeList)
    {
        distances[std::get<0>(e)][std::get<1>(e)] = std::get<2>(e);
    }

    // Para cada nodo pongo en 0 la distancia a sí mismo
    for (size_t i = 0; i < nodes; ++i)
    {
        distances[i][i] = 0;
    }

    // Triple for de Dantzig, ver pseudocódigo teórica
    for (int k = 0; k < nodes; ++k)
    {
        for (int i = 0; i < nodes; ++i)
        {
            if (i != k && distances[i][k] != INF)
            {
                for (int j = 0; j < nodes; ++j)
                {
                    if (j != k && j != i)
                    {
                        FloydWarshall_NS::relax(distances, i, k, j);
                    }
                }
            }
        }
    }

    return distances;
}
