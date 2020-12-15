#pragma once

#include <algorithm>
#include "commonTypes.h"

//O(v^2 * e)
std::vector<int> dijkstraOld(const incidences &edgeList, const int nodes, const int from)
{
    std::vector<int> visited(nodes, -1);
    visited[from] = 0;

    // Update distanes from source node to its neighbors
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

    for (int checked_nodes = 1; checked_nodes != nodes; )
    {
        auto w = std::min_element(solution_tmp.begin(), solution_tmp.end());

        // If already visited change its value and look for other minimum
        if (visited[w - solution_tmp.begin()] == 0)
        {
            *w = INF;
        }
        else
        {
            visited[w - solution_tmp.begin()] = 0;
            ++checked_nodes;
            for (int i = 0; i < nodes; ++i)
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
