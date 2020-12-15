#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "commonTypes.h"
#include "kruskal.h"
#include "prim.h"

enum class Methods {
    Prim,
    Kruskal,
};

Methods method = Methods::Kruskal;

int laps = 1;

incidences getGraphFromFile(std::string filename, int edges);

adjacencies incidencesToAdjacencies(incidences incidences, int v, int e);

std::vector<std::string> hiperconectados(incidences edgeList, int nodes, int edges);

int main(int argc, char *argv[])
{
    std::string fileName;
    int nodes, edges;
    incidences edgeList;

    if (argc > 1)
    {
        fileName = argv[1];
        std::ifstream infile(fileName);
        infile >> nodes >> edges;
        edgeList = getGraphFromFile(fileName, edges);
        infile.close();
    }
    else
    {
        std::cin >> nodes >> edges;

        for (int i = 0; i < edges; i++)
        {
            int edgeA, edgeB, weight;
            std::cin >> edgeA >> edgeB >> weight;
            edgeList.emplace_back(edgeA, edgeB, weight);
        }
    }

    if (argc > 2)
    {
        std::string input_method = argv[2];

        if (input_method == "P")
        {
            method = Methods::Prim;
        }
        else if (input_method == "K")
        {
            method = Methods::Kruskal;
        }
    }

    if (argc > 3)
    {
        laps = atoi(argv[3]);

        switch (method)
        {
        case Methods::Prim:
            fileName = "Methods::Prim_" + std::to_string(nodes) + "v_" + std::to_string(edges) + "e.csv";
            break;
        case Methods::Kruskal:
            fileName = "Methods::Kruskal_" + std::to_string(nodes) + "v_" + std::to_string(edges) + "e.csv";
            break;
        }

        std::chrono::duration<double, std::milli> average = (std::chrono::duration<double, std::milli>)0;
        std::ofstream results;

        results.open(fileName, std::fstream::out);

        for (int i = 1; i <= laps; i++)
        {
            auto start = std::chrono::steady_clock::now();
            std::vector<std::string> edgeStatus = hiperconectados(edgeList, nodes, edges);
            auto end = std::chrono::steady_clock::now();
            auto diff = end - start;
            average += diff;
        }

        switch (method)
        {
        case Methods::Prim:
            results << "Methods::Prim"
                    << ";";
            break;
        case Methods::Kruskal:
            results << "Methods::Kruskal"
                    << ";";
            break;
        }

        results << nodes << ";";
        results << edges << ";";
        results << std::chrono::duration<double, std::milli>(average / laps).count() << std::endl;
        results.close();
    }
    else
    {
        std::vector<std::string> edgeStatus = hiperconectados(edgeList, nodes, edges);

        for (size_t i = 0; i < edgeStatus.size(); i++)
        {
            std::cout << edgeStatus[i] << std::endl;
        }
    }
    return 0;
}

incidences getGraphFromFile(std::string filename, int edges)
{
    incidences edgeList;
    std::ifstream ifs(filename);
    std::string skip;
    std::getline(ifs, skip);

    for (int i = 0; i < edges; i++)
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
        adjacencies[std::get<0>(edge)].emplace_back(std::get<1>(edge), std::get<2>(edge));
        adjacencies[std::get<1>(edge)].emplace_back(std::get<0>(edge), std::get<2>(edge));
    }

    return adjacencies;
}

std::vector<std::string> hiperconectados(incidences edgeList, int nodes, int edges)
{
    //Declaro contenedor de std::strings solución
    std::vector<std::string> solucion;

    //Genera el AGM original y guarda su costo
    int formerAGMCost = 0;
    adjacencies transformed;

    switch (method)
    {
    case Methods::Prim:
        transformed = incidencesToAdjacencies(edgeList, nodes, edges);
        formerAGMCost = prim(transformed, nodes);
        break;
    case Methods::Kruskal:
        formerAGMCost = kruskal(edgeList, nodes, edges);
        break;
    }

    int maxEdgeValue = 1;

    for (int i = 0; i < edges; i++)
    {
        maxEdgeValue += std::get<2>(edgeList[i]);
    }

    for (int i = 0; i < edges; i++)
    {
        //Guarda el costo original del eje
        int edgeCost = std::get<2>(edgeList[i]);

        //Cambia el costo del eje a un valor mayor, genera un nuevo AGM y guarda su costo
        std::get<2>(edgeList[i]) = maxEdgeValue;
        int excludingEdgeCost = 0;

        switch (method)
        {
        case Methods::Prim:
            transformed = incidencesToAdjacencies(edgeList, nodes, edges);
            excludingEdgeCost = prim(transformed, nodes);
            break;
        case Methods::Kruskal:
            excludingEdgeCost = kruskal(edgeList, nodes, edges);
            break;
        }

        //Cambia el costo del eje a cero, genera un nuevo AGM y guarda su costo
        std::get<2>(edgeList[i]) = 0;
        int includingEdgeCost = 0;

        switch (method)
        {
        case Methods::Prim:
            transformed = incidencesToAdjacencies(edgeList, nodes, edges);
            includingEdgeCost = prim(transformed, nodes);
            break;
        case Methods::Kruskal:
            includingEdgeCost = kruskal(edgeList, nodes, edges);
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
        std::get<2>(edgeList[i]) = edgeCost;
    }

    return solucion;
}
