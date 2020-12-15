#pragma once

#include <algorithm>
#include <vector>

#include "commonTypes.h"

class DSU
{
private:

    std::vector<int> parent;
    std::vector<int> height;

public:

    DSU(int n)
    {
        for (int i = 0; i < n; i++)
        {
            parent.emplace_back(i);
            height.emplace_back(1);
        }
    };

    int find(int x)
    {
        if (parent[x] != x)
        {
            x = find(parent[x]);
        }
        return x;
    }

    void join(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (height[x] < height[y])
        {
            parent[x] = y;
        }
        else if (height[x] == height[y])
        {
            parent[x] = y;
            height[y]++;
        }
        else
        {
            parent[y] = x;
        }
    }
};

// O(V + E log V)
int kruskal(incidences edgeList, int v, int e)
{
    DSU dsu(v);
    int weight = 0;
    std::sort(edgeList.begin(), edgeList.end(), smallerThan());

    for (int i = 0; i < e; i++)
    {
        const edge edge = edgeList[i];
        if (dsu.find(std::get<0>(edge)) != dsu.find(std::get<1>(edge)))
        {
            weight += std::get<2>(edge);
            dsu.join(std::get<0>(edge), std::get<1>(edge));
        }
    }

    return weight;
}
