#pragma once

#include "commonTypes.h"

void relax(std::vector<std::vector<int>> &dists, int from, int middle, int to)
{
    if (dists[from][to] > dists[from][middle] + dists[middle][to])
    {
        dists[from][to] = dists[from][middle] + dists[middle][to];
    }
}

// O(v^3)
std::vector<std::vector<int>> dantzig(const incidences &edgeList, const int nodes, const int)
{
    std::vector<std::vector<int>> distances(nodes, std::vector<int>(nodes, INF));

    // Paso los ejes a la matriz
    for (const auto &e : edgeList)
    {
        distances[std::get<0>(e)][std::get<1>(e)] = std::get<2>(e);
    }

    // Pongo en 0 las distancias con fila=columna en la matriz
    for (size_t i = 0; i < nodes; ++i)
    {
        distances[i][i] = 0;
    }

    // Primer loop de Dantzig (ver pseudocódigo teórica)
    for (int k = 0; k < nodes - 1; ++k)
    {
        // Voy agrandando la parte de la matriz que voy actualizando, es el segundo loop
        for (int i = 0; i <= k; ++i)
        {
            for (int j = 0; j <= k; ++j)
            {
                relax(distances, i, j, k + 1);
                relax(distances, k + 1, j, i);
            }
        }
        // Tercer y cuarto loop de Dantzig
        for (int i = 0; i <= k; ++i)
        {
            for (int j = 0; j <= k; ++j)
            {
                relax(distances, i, k + 1, j);
            }
        }
    }

    return distances;
}
