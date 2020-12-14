#pragma once

#include "commonTypes.h"

// O(v) + O(e * log(e))
std::vector<int> dijkstrapq(const adjacencies &adjList, const int nodes, const int from)
{
    std::vector<int> solution(nodes, INF);
    solution[from] = 0;

    priority_Queue queue;
    queue.emplace(from, 0);

    while (!queue.empty())
    {
        const std::tuple<int, int> node = queue.top();
        queue.pop();

        // Check each node only once
        if (solution[std::get<0>(node)] < std::get<1>(node)) continue;

        for (const auto &adj : adjList[std::get<0>(node)])
        {
            // Relax distances
            if (solution[std::get<0>(adj)] > solution[std::get<0>(node)] + std::get<1>(adj))
            {
                solution[std::get<0>(adj)] = solution[std::get<0>(node)] + std::get<1>(adj);
                queue.emplace(std::get<0>(adj), solution[std::get<0>(adj)]);
            }
        }
    }

    return solution;
}
