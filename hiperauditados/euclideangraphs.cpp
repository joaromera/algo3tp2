#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <map>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <stdio.h>

using namespace std;
void euclideanGraphs(const int &v, const int &e);
void saveGraphToFile(const int &v, const int &e, const vector<std::tuple<int, int, int> > &edgeList,
                    const vector<std::tuple<int, int> > &nodesList);

int main(int argc, char * argv[]) {
    int v,e,s;
    if (argc == 1) {
        cin >> v >> e;
        srand(time(NULL));  
    } else {
        v = atoi(argv[1]);
        e = atoi(argv[2]);
        s = atoi(argv[3]);
        srand(s);
    }
    euclideanGraphs(v,e);
    return 0;
}

void euclideanGraphs(const int &v, const int &e) {
    vector <vector<int> > matrix (42, vector<int> (42,0));
    vector<std::tuple<int, int, int> > edgeList;
    vector<std::tuple<int, int> > nodesList;
    map<int, std::tuple<int, int> > nodesPosition;
    
    int x = 0;
    int y = 0;
    matrix[x][y] = 1;
    nodesPosition[0] = make_tuple(x,y);
    vector<int> chosensofar;
    chosensofar.push_back(0);
    nodesList.push_back(make_tuple(0,0));

    // Asigno nodos a posiciones y las guardo
    int w,s,x_dist,y_dist,ws_dist;
    int direction[2] = {-1, 1};
    for (int i = 1; i < v; i++) {
        do {
            int index = rand() % 2;
            x = get<0>(nodesPosition[chosensofar[i - 1]]) + (rand() % 42) * direction[index];
            index = rand() % 2;
            y = get<1>(nodesPosition[chosensofar[i - 1]]) + (rand() % 42) * direction[index];
            x_dist = x - get<0>(nodesPosition[i-1]);
            y_dist = y - get<1>(nodesPosition[i-1]);
            ws_dist = sqrt(pow(x_dist,2) + pow(y_dist,2));
        } while (x >= 42 || x < 0 || y < 0 || y >= 42 || ws_dist > 60 || matrix[x][y] != 0);
        matrix[x][y] = 1;
        nodesPosition[i] = make_tuple(x,y);
        chosensofar.push_back(i);
        nodesList.push_back(make_tuple(x,y));
    }
    
    // Genero aristas de un camino simple entre todos los nodos
    for (int i = 0; i < v - 1; i++) {
        x_dist = get<0>(nodesPosition[i]) - get<0>(nodesPosition[i + 1]);
        y_dist = get<1>(nodesPosition[i]) - get<1>(nodesPosition[i + 1]);
        ws_dist = sqrt(pow(x_dist,2) + pow(y_dist,2));
        edgeList.push_back(make_tuple(i, i + 1, ws_dist));
    }
    
    // Todas las posibles combinaciones de aristas entre nodos
    vector<std::tuple<int,int> > possibleEdge;
    for (int i = 0; i < v; i ++) {
        for (int j = i + 1; j < v; j++) {
            if (i + 1 != j) {
                possibleEdge.push_back(make_tuple(i,j));
            }
       }
    }

    // Elegi al azar aristas entre las posibles
    int actualEdges = v - 1;
    for (int i = 0; i < e - v + 1; i++) {
        int index = rand() % possibleEdge.size();
        w = get<0>(possibleEdge[index]);
        s = get<1>(possibleEdge[index]);
        x_dist = get<0>(nodesPosition[w]) - get<0>(nodesPosition[s]);
        y_dist = get<1>(nodesPosition[w]) - get<1>(nodesPosition[s]);
        ws_dist = sqrt(pow(x_dist,2) + pow(y_dist,2));
        if (ws_dist <= 60) {
            actualEdges++;
            edgeList.push_back(make_tuple(w, s, ws_dist));
        }
        possibleEdge.erase(possibleEdge.begin() + index);
    }
    saveGraphToFile(v,actualEdges,edgeList,nodesList);
}

void saveGraphToFile(
    const int &v, 
    const int &e, 
    const vector<std::tuple<int, int, int> > &edgeList,
    const vector<std::tuple<int, int> > &nodesList
    ) {
    string fileName = "euclid_" + to_string(v) + "v_" + to_string(e) + "e_e.txt";
    ofstream f;
    f.open(fileName, fstream::out);
    f << v << " " << e << endl;

    for (size_t i = 0; i < nodesList.size(); i++) {
        f << get<0>(nodesList[i]) << " " << get<1>(nodesList[i]) << endl;
    }

    for (size_t i = 0; i < edgeList.size(); i++) {
        f << get<0>(edgeList[i]) << " " << get<1>(edgeList[i]) << " " << get<2>(edgeList[i]) << endl;
    }
    f.close();
}