#pragma once

#include <limits>
#include <queue>
#include <tuple>
#include <vector>

constexpr int INF = std::numeric_limits<int>::max();

//Incidences List
using edge = std::tuple<int, int, int>;
using incidences = std::vector<edge>;

//Adjacencies List
using adjacents = std::vector<std::tuple<int, int>>;
using adjacencies = std::vector<adjacents>;

class heavierThan
{
public:
    bool operator()(const edge &a, const edge &b) const
    {
        return (std::get<2>(a) > std::get<2>(b));
    }
};

class heavier_Than
{
public:
    bool operator()(const std::tuple<int, int> &a, const std::tuple<int, int> &b) const
    {
        return (std::get<1>(a) > std::get<1>(b));
    }
};

class heavier_Than_A
{
public:
    bool operator()(const std::tuple<int, int, int> &a, const std::tuple<int, int, int> &b) const
    {
        return (std::get<2>(a) > std::get<2>(b));
    }
};

class smallerThan
{
public:
    bool operator()(const edge &a, const edge &b) const
    {
        return (std::get<2>(a) < std::get<2>(b));
    }
};

//Priority Queue
using priorityQueue    = std::priority_queue<edge, std::vector<edge>, heavierThan>;
using priority_Queue   = std::priority_queue<std::tuple<int, int>, std::vector<std::tuple<int, int>>, heavier_Than>;
using priority_Queue_A = std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, heavier_Than_A>;

void relax(std::vector<std::vector<int>> &dists, int from, int middle, int to)
{
    if (dists[from][to] > dists[from][middle] + dists[middle][to])
    {
        dists[from][to] = dists[from][middle] + dists[middle][to];
    }
}
