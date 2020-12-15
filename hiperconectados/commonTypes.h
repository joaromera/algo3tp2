#pragma once

#include <limits>
#include <queue>
#include <tuple>
#include <vector>

constexpr int INF = std::numeric_limits<int>::max();

//Incidences List
typedef std::tuple<int, int, int> edge;
typedef std::vector<edge> incidences;

//Adjacencies List
typedef std::vector<std::tuple<int, int>> adjacents;
typedef std::vector<adjacents> adjacencies;

class EdgeHeavierThan
{
public:
    bool operator()(const edge &a, const edge &b) const
    {
        return (std::get<2>(a) > std::get<2>(b));
    }
};

class TupleHeavierThan
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
    bool operator()(const edge & a, const edge & b) const
    {
        return (std::get < 2 > (a) < std::get < 2 > (b));
    }
};

//Priority Queue
using priorityQueue = std::priority_queue<edge, std::vector<edge>, EdgeHeavierThan>;
using priority_Queue = std::priority_queue<std::tuple<int, int>, std::vector<std::tuple<int, int>>, TupleHeavierThan>;
using priority_Queue_A = std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, heavier_Than_A>;
