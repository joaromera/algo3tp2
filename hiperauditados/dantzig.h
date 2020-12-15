#pragma once

#include "commonTypes.h"

// O(v^3)
std::vector<std::vector<int>> dantzig(const incidences &edgeList, const int nodes)
{
    std::vector<std::vector<int>> distances(nodes, std::vector<int>(nodes, INF));

    // Build matrix
    for (const auto &e : edgeList)
    {
        distances[std::get<0>(e)][std::get<1>(e)] = std::get<2>(e);
    }

    // Zero out distances where srt and dst match
    for (int i = 0; i < nodes; ++i)
    {
        distances[i][i] = 0;
    }

    for (int k = 0; k < nodes - 1; ++k)
    {
        for (int i = 0; i <= k; ++i)
        {
            for (int j = 0; j <= k; ++j)
            {
                relax(distances, i, j, k + 1);
                relax(distances, k + 1, j, i);
            }
        }

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
