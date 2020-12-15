#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

void euclideanGraphs(const int&, const int&);
void saveGraphToFile(const int&, const int&, const std::vector<std::tuple<int, int, int>>&, const std::vector<std::tuple<int, int>>&);

int main(int argc, char *argv[])
{
    int v, e, s;
    if (argc == 1)
    {
        std::cin >> v >> e;
        srand(time(NULL));
    }
    else
    {
        v = atoi(argv[1]);
        e = atoi(argv[2]);
        s = atoi(argv[3]);
        srand(s);
    }
    euclideanGraphs(v, e);
    return 0;
}

void euclideanGraphs(const int &v, const int &e)
{
    std::vector<std::vector<int>> matrix(42, std::vector<int>(42, 0));
    std::vector<std::tuple<int, int, int>> edgeList;
    std::vector<std::tuple<int, int>> nodesList;
    std::map<int, std::tuple<int, int>> nodesPosition;

    int x = 0;
    int y = 0;
    matrix[x][y] = 1;
    nodesPosition[0] = { x, y };
    std::vector<int> chosensofar;
    chosensofar.emplace_back(0);
    nodesList.emplace_back(0, 0);

    // Assign nodes
    int w, s, x_dist, y_dist, ws_dist;
    int direction[2] = { -1, 1 };

    for (int i = 1; i < v; ++i)
    {
        do
        {
            int index = rand() % 2;
            x = std::get<0>(nodesPosition[chosensofar[i - 1]]) + (rand() % 42) * direction[index];
            index = rand() % 2;
            y = std::get<1>(nodesPosition[chosensofar[i - 1]]) + (rand() % 42) * direction[index];
            x_dist = x - std::get<0>(nodesPosition[i - 1]);
            y_dist = y - std::get<1>(nodesPosition[i - 1]);
            ws_dist = std::sqrt(std::pow(x_dist, 2) + std::pow(y_dist, 2));
        } while (x >= 42 || x < 0 || y < 0 || y >= 42 || ws_dist > 60 || matrix[x][y] != 0);

        matrix[x][y] = 1;
        nodesPosition[i] = { x, y };
        chosensofar.emplace_back(i);
        nodesList.emplace_back(x, y);
    }

    // Generate edges for a single path between all nodes
    for (int i = 0; i < v - 1; ++i)
    {
        x_dist = std::get<0>(nodesPosition[i]) - std::get<0>(nodesPosition[i + 1]);
        y_dist = std::get<1>(nodesPosition[i]) - std::get<1>(nodesPosition[i + 1]);
        ws_dist = std::sqrt(std::pow(x_dist, 2) + std::pow(y_dist, 2));
        edgeList.emplace_back(i, i + 1, ws_dist);
    }

    // Every possible combination of edges between nodes
    std::vector<std::tuple<int, int>> possibleEdge;
    for (int i = 0; i < v; ++i)
    {
        for (int j = i + 1; j < v; ++j)
        {
            if (i + 1 != j)
            {
                possibleEdge.emplace_back(i, j);
            }
        }
    }

    // Pick random edges among possible
    int actualEdges = v - 1;
    for (int i = 0; i < e - v + 1; ++i)
    {
        const int index = rand() % possibleEdge.size();
        w = std::get<0>(possibleEdge[index]);
        s = std::get<1>(possibleEdge[index]);
        x_dist = std::get<0>(nodesPosition[w]) - std::get<0>(nodesPosition[s]);
        y_dist = std::get<1>(nodesPosition[w]) - std::get<1>(nodesPosition[s]);
        ws_dist = std::sqrt(std::pow(x_dist, 2) + std::pow(y_dist, 2));
        if (ws_dist <= 60)
        {
            ++actualEdges;
            edgeList.emplace_back(w, s, ws_dist);
        }
        possibleEdge.erase(possibleEdge.begin() + index);
    }
    saveGraphToFile(v, actualEdges, edgeList, nodesList);
}

void saveGraphToFile(
    const int &v,
    const int &e,
    const std::vector<std::tuple<int, int, int>> &edgeList,
    const std::vector<std::tuple<int, int>> &nodesList)
{
    const std::string fileName = "euclid_" + std::to_string(v) + "v_" + std::to_string(e) + "e_e.txt";
    std::fstream f;
    f.open(fileName, std::fstream::out);
    f << v << " " << e << std::endl;

    for (size_t i = 0; i < nodesList.size(); ++i)
    {
        f << std::get<0>(nodesList[i]) << " " << std::get<1>(nodesList[i]) << std::endl;
    }

    for (size_t i = 0; i < edgeList.size(); ++i)
    {
        f << std::get<0>(edgeList[i]) << " " << std::get<1>(edgeList[i]) << " " << std::get<2>(edgeList[i]) << std::endl;
    }
    f.close();
}
