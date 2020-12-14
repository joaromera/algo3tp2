#pragma once

#include "commonTypes.h"

// O(v) + O(e * log(e)) + O(v * d(v) * log(e)) [Same as Dijkstra PQ]
std::vector<int> astar(const adjacencies &adjList, const int nodes, const int edges, const int from)
{
    std::vector<int> solution(nodes, INF);
    solution[from] = 0;

    priority_Queue_A queue;
    queue.emplace(from, 0, 0);

    while (!queue.empty())
    {
        const std::tuple<int, int, int> node = queue.top();
        queue.pop();

        if (solution[std::get<0>(node)] < std::get<1>(node)) continue; // Check nodes only once

        for (const auto &adj : adjList[std::get<0>(node)])
        {
            const int new_cost = solution[std::get<0>(node)] + std::get<1>(adj);

            if (solution[std::get<0>(adj)] == INF || (new_cost < solution[std::get<0>(adj)]))
            {
                //usamos new_cost ya que para este tipo de entradas no disponemos
                //de la información necesaria para la heurística
                //o sea, es igual a Dijkstra PQ.
                solution[std::get<0>(adj)] = new_cost;
                const int priority = new_cost;
                queue.emplace(std::get<0>(adj), new_cost, priority);
            }
        }
    }
    return solution;
}
