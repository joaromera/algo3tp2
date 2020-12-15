#pragma once

#include <vector>

#include "commonTypes.h"

// O(v^2*log(v))
int prim(adjacencies edgeList, int v)
{
    int weight = 0;
    priorityQueue queue;
    std::vector<int> visited;

    for (int i = 0; i < v; i++)
    {
        visited.emplace_back(-1);
    }

    visited[0] = 0;
    int current = 0;

    for (int i = 0; i < v - 1; i++)
    {
        adjacents adjacents = edgeList[current];

        // Add neighbours to the queue
        for (size_t j = 0; j < adjacents.size(); j++)
        {
            if (visited[std::get<0>(adjacents[j])] == -1)
            {
                queue.emplace(
                    current, std::get<0>(adjacents[j]),
                    std::get<1>(adjacents[j])
                );
            }
        }

        // Find the minimun from the unvisited
        int candidate = std::get<1>(queue.top());
        while (queue.size() > 0 && visited[candidate] != -1)
        {
            queue.pop();
            candidate = std::get<1>(queue.top());
        }

        // Mark the node as visited
        visited[candidate] = std::get<0>(queue.top());

        // The tree grows bigger
        weight += std::get<2>(queue.top());

        // Current std::gets updated
        current = candidate;

        //Once confirmed its removed
        queue.pop();
    }

    return weight;
}
