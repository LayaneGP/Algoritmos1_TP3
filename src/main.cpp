#include "./../include/bfs.hpp"
#include "./../include/bruteForce.hpp"
#include "./../include/dynamic.hpp"
#include "./../include/graph.hpp"

#include <iostream>
#include <list>
#include <limits>
#include <stack>
#include <vector>
#include <unordered_map>

using namespace std;

const int INF = numeric_limits<int>::max();  // Constante para representar uma distância infinita

int main(){
    char type_algorithm;
    int V = 0, E = 0, dist = 0;
    string start, end;

    cin >> type_algorithm >> V >> E;

    Graph graph(V);

    pair<int, string> min_distance = make_pair(INF, ""); // Distância mínima no grafo e o vértice de saída (o inserido primeiro)

    for(int i = 0; i < E; i++){
        cin >> start >> end >> dist;
        graph.addEdge(start, end, dist);
        graph.addEdge(end, start, dist);

        if(dist < min_distance.first){
            min_distance = make_pair(dist, start);
        }
    }

    // Par que armazena a menor distância e o caminho encontrado para solucionar o problema
    pair<int, vector<string>> path;

    switch (type_algorithm){
        case 'b':       // Força bruta
            path = permutations(graph);
            break;

        case 'd':       // Programação dinâmica
            path = dynamic(graph, start);
            break;

        case 'g':       // Algoritmo guloso
            path = greedy_bfs(graph, start);
            break;
        
        default:
            break;
    }

    cout << path.first << endl;
    for(const string& vertice : path.second){
        cout << vertice << " ";
    }
    cout << endl;

    return 0;
}