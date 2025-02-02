#include "dfs.hpp"
#include "graph.hpp"

#include <iostream>
#include <vector>
#include <limits>
#include <unordered_map>
#include <unordered_set>

const int INF = numeric_limits<int>::max();  // Constante para representar uma distância infinita


pair<int, vector<string>> permutations(Graph& graph){
    pair<int, vector<string>> best_path; // Melhor caminho encontrado até agora 
    best_path.first = INF;   

    vector<string> list_of_vertices; // Lista dos vértices do grafo
    for(const auto& vertice : graph.adj){
        list_of_vertices.push_back(vertice.first);
    }

    // Chamada recursiva para determinar o caminho de menor custo
    permutations_rec(graph, best_path, list_of_vertices, 0, graph.numV() - 1);
    
    return best_path;
};


void permutations_rec(Graph& graph, pair<int, vector<string>>& best_path, vector<string> perm, int start_index, int end_index){
    if(start_index == end_index){
        int current_cost = 0; // Custo inicial do caminho atual
        perm.push_back(perm[0]); // Adiciona o vértice inicial ao final da permutação para contabilizar a aresta de retorno
        for(int i = 0, V = graph.numV(); i < V; i++){
            string from = perm[i];
            string to = perm[i+1];
            for(const auto& neighbour : graph.adj[from]){
                if(neighbour.first == to){
                    current_cost += neighbour.second;
                    break;
                }
            }
        }

        if(current_cost < best_path.first){
            perm.erase(perm.end());
            best_path = make_pair(current_cost, perm);
        }

        return;
    }

    // Gera as permutações recursivamente, computando-as ao desfazer as alterações
    for(int i = start_index; i <= end_index; i++){
        swap(perm[start_index], perm[i]);
        permutations_rec(graph, best_path, perm, start_index + 1, end_index);
        swap(perm[start_index], perm[i]);
    }
};