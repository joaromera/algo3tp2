#pragma once

#include "commonTypes.h"

// O(v^3)
std::vector<std::vector<int>> floydwarshall(const incidences &edgeList, const int &nodes)
{
    std::vector<std::vector<int>> distances(nodes, std::vector<int>(nodes, INF));

    for (const auto &e : edgeList)
    {
        distances[std::get<0>(e)][std::get<1>(e)] = std::get<2>(e);
    }

    for (int i = 0; i < nodes; ++i)
    {
        distances[i][i] = 0;
    }

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
                        relax(distances, i, k, j);
                    }
                }
            }
        }
    }

    return distances;
}
