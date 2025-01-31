#include "dfs.hpp"
#include "graph.hpp"

#include <iostream>
#include <vector>
#include <limits>
#include <unordered_map>

const int INF = numeric_limits<int>::max();  // Constante para representar uma distância infinita


// Função principal da busca em profundidade
/* "colors": 0 = não descoberto
             1 = sendo explorado
             2 = totalmente explorado
*/
pair<int, list<string>> dfs(Graph& graph, string start){
    unordered_map<string, list<pair<string, int>>> vertices = graph.adj; // Cópia da lista de vértices
    unordered_map<string, int> colors; // Mapeamento da situação dos vértices
    
    list<string> path;  // Caminho atual
    list<string> best_path;  // Caminho de menor custo até agora

    int current_dist = 0; // Distância do caminho atual
    int min_dist = INF; // Menor distância até agora

    // Marca todos os vértices como não explorados
    for(const auto& pair : vertices){
        colors[pair.first] = 0;
    }

    for(const auto& pair : vertices){
        if(colors[pair.first] == 0){
            dfs_visit(graph, start, colors, pair.first, path, best_path, current_dist, min_dist);
        }
    }

    return make_pair(min_dist, best_path);
};


// Função recursiva da busca em profundidade
void dfs_visit(Graph& graph, string start, unordered_map<string, int>& colors, string current, list<string>& path, list<string>& best_path, int& current_dist, int& min_dist){
    colors[current] = 1;
            path.push_back(current);

    list<pair<string, int>> neighbours = graph.adj[current]; // Cópia da lista de vizinhos do vértice atual
    
    for(const auto& pair : neighbours){
        if(colors[pair.first] == 0){
            current_dist += pair.second;
            dfs_visit(graph, start, colors, pair.first, path, best_path, current_dist, min_dist);
            
            for(const auto& neigh : graph.adj[current]){
                if(neigh.first == start){
                    current_dist += neigh.second;
                }
            }

            if(current_dist < min_dist){
                best_path = path;
            }
        }
    }

    colors[current] = 2;
};