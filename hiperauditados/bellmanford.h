#pragma once

#include "commonTypes.h"

//O(ve)
std::vector<int> bellmanford(const incidences &edgeList, const int nodes, const int from)
{
    std::vector<int> solution(nodes, INF);
    solution[from] = 0;

    for (int v = 0; v < nodes; ++v)
    {
        for (const auto &e : edgeList)
        {
            const int src = std::get<0>(e);
            const int dst = std::get<1>(e);
            const int cst = std::get<2>(e);

            // Relax distance
            if (solution[src] != INF && solution[src] + cst < solution[dst])
            {
                solution[dst] = solution[src] + cst;
            }
        }
    }

    return solution;
}
