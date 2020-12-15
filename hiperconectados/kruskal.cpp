#include "kruskal.h"
using namespace std;

class DSU
{
private:
    vector<int> parent;
    vector<int> height;

public:
    DSU(int n)
    {
        for (size_t i = 0; i < n; i++)
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

    ~DSU() {}
};

// O(V + E log V)
int kruskal(incidences edgeList, int v, int e)
{
    DSU dsu(v);
    int weight = 0;
    sort(edgeList.begin(), edgeList.end(), smallerThan());

    for (size_t i = 0; i < e; i++)
    {
        edge edge = edgeList[i];
        if (dsu.find(get<0>(edge)) != dsu.find(get<1>(edge)))
        {
            weight += get<2>(edge);
            dsu.join(get<0>(edge), get<1>(edge));
        }
    }

    return weight;
}
