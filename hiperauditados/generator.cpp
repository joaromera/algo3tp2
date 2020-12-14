#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <vector>

/** generator(int v, int e, int seed, int problem)
 *  v <-- #nodes
 *  e <-- #edges
 *  seed <-- para no generar siempre el mismo grafo 
 *  problem <-- default: 1 hiperconectados, 2 hiperauditados
 * 
 *  el grafo es un std::vector de e x v tal que
 *  e[i][0] es uno de los vertices que conecta el eje i
 *  e[i][1] es el otro vertice que conecta el eje i
 * 	e[i][2] es el peso del eje
 * 
 * Para el probema 2 elige el costo de la nafta desde 1 a v y las distancias entre 30 y 60.
 * 	
 **/
void saveGraphToFile(const int &v, const int &e, const std::vector<std::vector<int>> &edge, const int &problem)
{
    const std::string fileName = std::to_string(v) + "v_" + std::to_string(e) + "e_" + std::to_string(problem) + ".txt";
    std::fstream f;
    f.open(fileName, std::fstream::out);
    f << v << " " << e << std::endl;

    if (problem == 2)
    {
        for (size_t i = 0; i < v; ++i)
        {
            const int litreCostInCity_i = (rand() % v) + 1;
            f << litreCostInCity_i << std::endl;
        }
    }

    for (size_t i = 0; i < edge.size(); ++i)
    {
        f << edge[i][0] << " " << edge[i][1] << " " << edge[i][2] << std::endl;
    }
    f.close();
}

void printGraph(const int &v, const int &e, const std::vector<std::vector<int>> &edge)
{
    int i, j, count;
    for (i = 0; i < v; ++i)
    {
        count = 0;
        for (j = 0; j < e; ++j)
        {
            if (edge[j][0] == i)
            {
                ++count;
            }
            else if (edge[j][1] == i)
            {
                ++count;
            }
        }
    }
}

void generateRandGraphs(const int &v, const int &e, const int &problem)
{
    std::vector<std::vector<int>> edge(e, std::vector<int>(3));
    int i = 0;

    // Genero el grafo conexo de v nodos y v-1 ejes
    std::vector<int> n(v, 0);
    for (int k = 0; k < n.size(); ++k)
    {
        n[k] = k;
    }

    const int a = rand() % n.size();
    int na = n[a];
    n.erase(n.begin() + a);

    while (i < v - 1)
    {
        int b = rand() % n.size();
        int nb = n[b];
        edge[i][0] = na;
        edge[i][1] = nb;

        if (problem == 2)
        {
            edge[i][2] = (rand() % 30) + 31;
        }
        else
        {
            edge[i][2] = std::max(rand() % v, rand() % e) + 1;
        }

        na = nb;
        n.erase(n.begin() + b);
        ++i;
    }

    // Completa el grafo con los ejes que faltan
    while (i < e)
    {
        edge[i][0] = rand() % v;
        edge[i][1] = rand() % v;

        if (problem == 2)
        {
            edge[i][2] = (rand() % 30) + 31;
        }
        else
        {
            edge[i][2] = std::max(rand() % v, rand() % e) + 1;
        }

        if (edge[i][0] == edge[i][1])
            continue;
        else
        {
            for (int j = 0; j < i; ++j)
            {
                if ((edge[i][0] == edge[j][0] && edge[i][1] == edge[j][1]) || (edge[i][0] == edge[j][1] && edge[i][1] == edge[j][0]))
                {
                    i--;
                }
            }
        }
        ++i;
    }

    printGraph(v, e, edge);
    saveGraphToFile(v, e, edge, problem);
}

int main(int argc, char *argv[])
{
    int v, e, seed;
    int problem = 1;
    if (argc < 3)
    {
        if (argc == 2)
        {
            e = (atoi(argv[1]) * (atoi(argv[1]) - 1)) / 2;
        }
        else
        {
            std::cerr << "Not enough parameters." << std::endl;
            return 0;
        }
    }
    else
    {
        e = atoi(argv[2]);
    }

    v = atoi(argv[1]);

    if (e > (v * (v - 1)) / 2)
    {
        std::cerr << "The graph has way too many edges." << std::endl;
        return 0;
    }
    else if (e < v - 1)
    {
        std::cerr << "Not enough edges." << std::endl;
        return 0;
    }

    if (argc == 4)
    {
        seed = atoi(argv[3]);
        srand(time(NULL));
    }

    if (argc == 5)
    {
        problem = atoi(argv[4]);
        seed = atoi(argv[3]);
        srand(seed);
    }

    generateRandGraphs(v, e, problem);
    return 0;
}
