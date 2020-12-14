#ifndef COMMONTYPES_H
#define COMMONTYPES_H

#include <algorithm>
#include <chrono>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <tuple>
#include <vector>

const int INF = std::numeric_limits<int>::max();

//Incidences List
typedef std::tuple < int, int, int > edge;
typedef std::vector < edge > incidences;

//Adjacencies List
typedef std::vector < std::tuple < int, int >> adjacents;
typedef std::vector < adjacents > adjacencies;

class heavierThan {
    public:
        bool operator()(const edge & a,
            const edge & b) const {
            return (std::get < 2 > (a) > std::get < 2 > (b));
        }
};

class heavier_Than {
    public:
        bool operator()(const std::tuple < int, int > & a,
            const std::tuple < int, int > & b) const {
            return (std::get < 1 > (a) > std::get < 1 > (b));
        }
};

class heavier_Than_A {
    public:
        bool operator()(const std::tuple < int, int, int > & a,
            const std::tuple < int, int, int > & b) const {
            return (std::get < 2 > (a) > std::get < 2 > (b));
        }
};

class smallerThan {
    public:
        bool operator()(const edge & a,
            const edge & b) const {
            return (std::get < 2 > (a) < std::get < 2 > (b));
        }
};

//Priority Queue
typedef std::priority_queue < edge, std::vector < edge > , heavierThan > priorityQueue;
typedef std::priority_queue < std::tuple < int, int > , std::vector < std::tuple < int, int > > , heavier_Than > priority_Queue;
typedef std::priority_queue < std::tuple < int, int, int > , std::vector < std::tuple < int, int, int > > , heavier_Than_A > priority_Queue_A;

#endif