#include "./../include/graph.hpp"

#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <unordered_set>
#include <unordered_map>

const int INF = numeric_limits<int>::max();  // Constante para representar uma distância infinita

// Busca em largura gulosa para encontrar o menor caminho no grafo que passe por todos os vértices, e uma única vez
pair<int, vector<string>> greedy_bfs(Graph& graph, string start){
        
    unordered_set<string> visited; // Set não ordenado para saber se um vértice foi ou não visitado
    vector<string> path; // Caminho encontrado
    int total_distance = 0; // Distância total do caminho encontrado

    // Marca o vértice inicial como visitado
    visited.insert(start);

    string current = start;
    path.push_back(start);

    while(static_cast<int>(visited.size()) != graph.numV()){
        int min_dist = INF;  // Distância mínima entre os vizinhos do vértice atual

        // Busca, entre os vértices não visitados, o de menor distância
        for(auto& neighbour : graph.adj[current]){
            if((visited.find(neighbour.first) == visited.end()) && (neighbour.second < min_dist)){
                current = neighbour.first;
                min_dist = neighbour.second;
            }
        }

        path.push_back(current);
        visited.insert(current);
        total_distance += min_dist;
    }

    for(const auto& neighbour : graph.adj[current]){
        if(neighbour.first == start){
            total_distance += neighbour.second;
        }
    }

    if(total_distance == INF){
        cout << "Cuidado! Distancia infinita." << endl;
    }

    return make_pair(total_distance, path);
}
