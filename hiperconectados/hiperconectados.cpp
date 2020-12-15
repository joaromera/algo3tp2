#include <fstream>
#include <stdlib.h>
#include <string>

#include "commonTypes.h"
#include "kruskal.h"
#include "kruskalpc.h"
#include "prim.h"

using namespace std;

enum Methods {
    Prim,
    Kruskal,
    KruskalPC
};

Methods method = KruskalPC;

int laps = 1;

incidences getGraphFromFile(string filename, int edges);

adjacencies incidencesToAdjacencies(incidences incidences, int v, int e);

vector<string> hiperconectados(incidences edgeList, int nodes, int edges);

int main(int argc, char *argv[])
{
    string fileName;
    int nodes, edges;
    incidences edgeList;

    if (argc > 1)
    {
        fileName = argv[1];
        ifstream infile(fileName);
        if (infile.good())
        {
            infile >> nodes >> edges;
        }
        infile.close();
        edgeList = getGraphFromFile(fileName, edges);
    }
    else
    {
        cin >> nodes >> edges;

        for (size_t i = 0; i < edges; i++)
        {
            int edgeA, edgeB, weight;
            cin >> edgeA >> edgeB >> weight;
            edgeList.emplace_back(edgeA, edgeB, weight);
        }
    }

    if (argc > 2)
    {
        if (string(argv[2]) == "P")
        {
            method = Prim;
        }
        else if (string(argv[2]) == "K")
        {
            method = Kruskal;
        }
        else if (string(argv[2]) == "KPC")
        {
            method = KruskalPC;
        }
    }

    if (argc > 3)
    {
        laps = atoi(argv[3]);
        switch (method)
        {
        case Prim:
            fileName = "prim_" + to_string(nodes) + "v_" + to_string(edges) + "e.csv";
            break;
        case Kruskal:
            fileName = "kruskal_" + to_string(nodes) + "v_" + to_string(edges) + "e.csv";
            break;
        case KruskalPC:
            fileName = "kruskalpc_" + to_string(nodes) + "v_" + to_string(edges) + "e.csv";
            break;
        }
        chrono::duration<double, milli> average = (chrono::duration<double, milli>)0;
        ofstream results;
        results.open(fileName, fstream::out);
        for (int i = 1; i <= laps; i++)
        {
            auto start = chrono::steady_clock::now();
            vector<string> edgeStatus = hiperconectados(edgeList, nodes, edges);
            auto end = chrono::steady_clock::now();
            auto diff = end - start;
            average += diff;
        }
        switch (method)
        {
        case Prim:
            results << "Prim"
                    << ";";
            break;
        case Kruskal:
            results << "Kruskal"
                    << ";";
            break;
        case KruskalPC:
            results << "KruskalPC"
                    << ";";
            break;
        }
        results << nodes << ";";
        results << edges << ";";
        results << chrono::duration<double, milli>(average / laps).count() << endl;
        results.close();
    }
    else
    {
        vector<string> edgeStatus = hiperconectados(edgeList, nodes, edges);
        for (size_t i = 0; i < edgeStatus.size(); i++)
        {
            cout << edgeStatus[i] << endl;
        }
    }
    return 0;
}

incidences getGraphFromFile(string filename, int edges)
{
    incidences edgeList;
    ifstream ifs(filename);
    string skip;
    getline(ifs, skip);

    for (size_t i = 0; i < edges; i++)
    {
        int edgeA, edgeB, weight;
        ifs >> edgeA >> edgeB >> weight;
        edgeList.emplace_back(edgeA, edgeB, weight);
    }

    ifs.close();
    return edgeList;
}

adjacencies incidencesToAdjacencies(incidences incidences, int v, int e)
{
    adjacencies adjacencies;
    adjacents adjacents;

    for (int i = 0; i < v; i++)
    {
        adjacencies.push_back(adjacents);
    }

    for (int h = 0; h < e; h++)
    {
        edge edge = incidences[h];
        adjacencies[get<0>(edge)].emplace_back(get<1>(edge), get<2>(edge));
        adjacencies[get<1>(edge)].emplace_back(get<0>(edge), get<2>(edge));
    }

    return adjacencies;
}

vector<string> hiperconectados(incidences edgeList, int nodes, int edges)
{
    //Declaro contenedor de strings solución
    vector<string> solucion;

    //Genera el AGM original y guarda su costo
    int formerAGMCost = 0;
    adjacencies transformed;
    switch (method)
    {
    case Prim:
        transformed = incidencesToAdjacencies(edgeList, nodes, edges);//O(v+e)
        formerAGMCost = prim(transformed, nodes, edges);//O(prim)
        break;
    case Kruskal:
        formerAGMCost = kruskal(edgeList, nodes, edges);//O(kruskal)
        break;
    case KruskalPC:
        formerAGMCost = kruskalpc(edgeList, nodes, edges);//O(kruskalpc)
        break;
    }

    int maxEdgeValue = 1;
    //O(E)
    for (size_t i = 0; i < edges; i++)
    {
        maxEdgeValue += get<2>(edgeList[i]);
    }

    //O(E)
    for (size_t i = 0; i < edges; i++)
    {
        //Guarda el costo original del eje
        int edgeCost = get<2>(edgeList[i]);

        //Cambia el costo del eje a un valor mayor, genera un nuevo AGM y guarda su costo
        get<2>(edgeList[i]) = maxEdgeValue;
        int excludingEdgeCost = 0;
        switch (method)
        {
        case Prim:
            transformed = incidencesToAdjacencies(edgeList, nodes, edges);//O(v+e)
            excludingEdgeCost = prim(transformed, nodes, edges);//O(prim)
            break;
        case Kruskal:
            excludingEdgeCost = kruskal(edgeList, nodes, edges);//O(kruskal)
            break;
        case KruskalPC:
            excludingEdgeCost = kruskalpc(edgeList, nodes, edges);//O(kruskalpc)
            break;
        }

        //Cambia el costo del eje a cero, genera un nuevo AGM y guarda su costo
        get<2>(edgeList[i]) = 0;
        int includingEdgeCost = 0;
        switch (method)
        {
        case Prim:
            transformed = incidencesToAdjacencies(edgeList, nodes, edges);//O(v+e)
            includingEdgeCost = prim(transformed, nodes, edges);//O(prim)
            break;
        case Kruskal:
            includingEdgeCost = kruskal(edgeList, nodes, edges);//O(kruskal)
            break;
        case KruskalPC:
            includingEdgeCost = kruskalpc(edgeList, nodes, edges);//O(kruskalpc)
            break;
        }

        //Compara el valor del AGM original con los obtenidos
        if (excludingEdgeCost > formerAGMCost)
        {
            solucion.emplace_back("toda");
        }
        else if (includingEdgeCost > formerAGMCost - edgeCost)
        {
            solucion.emplace_back("ninguna");
        }
        else
        {
            solucion.emplace_back("alguna");
        }

        //Le devuelve el valor original al eje
        get<2>(edgeList[i]) = edgeCost;
    }

    return solucion;
}
