#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>

using namespace std;

/** generator(int v, int e, int seed, int problem)
 *  v <-- #nodes
 *  e <-- #edges
 *  seed <-- para no generar siempre el mismo grafo 
 *  problem <-- default: 1 hiperconectados, 2 hiperauditados
 * 
 *  el grafo es un vector de e x v tal que
 *  e[i][0] es uno de los vertices que conecta el eje i
 *  e[i][1] es el otro vertice que conecta el eje i
 * 	e[i][2] es el peso del eje
 * 
 * Para el probema 2 elige el costo de la nafta desde 1 a v y las distancias entre 30 y 60.
 * 	
 **/

void saveGraphToFile(const int &v, const int &e, const vector<vector<int>> &edge, const int &problem)
{
    //string fileName = "grafos/" + to_string(v) + "/" + to_string(v) + "v_" + to_string(e) + "e_" + to_string(problem) + ".txt";
    string fileName = to_string(v) + "v_" + to_string(e) + "e_" + to_string(problem) + ".txt";
    ofstream f;
    f.open(fileName, fstream::out);
    f << v << " " << e << endl;

    if (problem == 2)
    {
        for (size_t i = 0; i < v; i++)
        {
            int litreCostInCity_i = (rand() % v) + 1;
            f << litreCostInCity_i << endl;
        }
    }

    for (size_t i = 0; i < edge.size(); i++)
    {
        f << edge[i][0] << " " << edge[i][1] << " " << edge[i][2] << endl;
    }
    f.close();
}

void printGraph(const int &v, const int &e, const vector<vector<int>> &edge)
{
    int i, j, count;
    for (i = 0; i < v; i++)
    {
        count = 0;
        //cout << "\n  " << i << "-> {";
        for (j = 0; j < e; j++)
        {
            if (edge[j][0] == i)
            {
                //cout << " " << edge[j][1] << " ";
                count++;
            }
            else if (edge[j][1] == i)
            {
                //cout << " " << edge[j][0] << " ";
                count++;
            }
            else if (j == e - 1 && count == 0)
                cout << "Isolated Vertex!";
        }
        //cout << "}";
    }
}

void generateRandGraphs(const int &v, const int &e, const int &problem)
{
    vector<vector<int>> edge(e, vector<int>(3));
    int i, j;
    i = 0;

    // Genero el grafo conexo de v nodos y v-1 ejes
    vector<int> n(v, 0);
    for (int k = 0; k < n.size(); k++)
    {
        n[k] = k;
    }
    int a = rand() % n.size();
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
            edge[i][2] = max(rand() % v, rand() % e) + 1;
        }

        na = nb;
        n.erase(n.begin() + b);
        i++;
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
            edge[i][2] = max(rand() % v, rand() % e) + 1;
        }

        if (edge[i][0] == edge[i][1])
            continue;
        else
        {
            for (j = 0; j < i; j++)
            {
                if ((edge[i][0] == edge[j][0] && edge[i][1] == edge[j][1]) || (edge[i][0] == edge[j][1] && edge[i][1] == edge[j][0]))
                {
                    i--;
                }
            }
        }

        i++;
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
            cerr << "Not enough parameters." << endl;
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
        cerr << "The graph has way too many edges." << endl;
        return 0;
    }
    else if (e < v - 1)
    {
        cerr << "Not enough edges." << endl;
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

    //cout << "Random graph generation: ";
    //cout << "\n The graph has " << v << " vertexes.";
    //cout << "\n The graph has " << e << " edges.";

    generateRandGraphs(v, e, problem);
    //cout << endl;
    return 0;
}