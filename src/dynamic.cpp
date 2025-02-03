#include "dynamic.hpp"
#include "graph.hpp"

#include <iostream>
#include <vector>
#include <limits>
#include <unordered_map>
#include <algorithm>

const int INF = std::numeric_limits<int>::max();

pair<int, vector<string>> dynamic(Graph& graph) {
    int num_V = graph.numV(); // Quantidade de vértices no grafo

    // Seleciona o primeiro vértice como inicial
    string start = graph.adj.begin()->first;

    unordered_map<string, int> vertices_to_numbers; // Mapa de um vértice para um inteiro que o representa
    unordered_map<int, string> numbers_to_vertices; // Mapa de um inteiro para o vértice que ele representa

    int v_index = 0;
    for(const auto& v : graph.adj){
        vertices_to_numbers[v.first] = v_index;
        numbers_to_vertices[v_index] = v.first;
        v_index++;
    }

    int start_index = vertices_to_numbers[start]; // Índice correspondente ao vértice de início

    vector<vector<int>> dist(num_V, vector<int>(num_V, INF)); // Matriz de distância dos vértices com valores iniciais infinitos

    // Construção da matriz de distâncias
    for(const auto& pair : graph.adj){
        int from = vertices_to_numbers[pair.first];
        dist[from][from] = 0;
        for(const auto& neighbour : pair.second){
            int to = vertices_to_numbers[neighbour.first];
            dist[from][to] = neighbour.second;
        }
    }

    int total_states = 1 << num_V; // dp[mask][i]: custo mínimo para visitar o conjunto de vértices 'mask' terminando no vértice i

    vector<vector<int>> dp(total_states, vector<int>(num_V, INF)); // Matriz da DP com valores iniciais infinitos
    vector<vector<int>> prev(total_states, vector<int>(num_V, -1)); // Matriz dos antecessores com valores iniciais inválidos

    dp[1 << start_index][start_index] = 0;

    // Itera sobre todos os estados (máscaras)
    for (int mask = 0; mask < total_states; mask++) {
        for (int i = 0; i < num_V; i++) {
            if (dp[mask][i] == INF) continue;  // Estado não alcançado
            // Tenta estender o caminho para cada vértice não visitado
            for (int j = 0; j < num_V; j++) {
                if (mask & (1 << j)) continue;  // Vértice j já foi visitado
                if (dist[i][j] == INF) continue;  // Não há conexão entre i e j
                int next_mask = mask | (1 << j);
                if (dp[mask][i] + dist[i][j] < dp[next_mask][j]) {
                    dp[next_mask][j] = dp[mask][i] + dist[i][j];
                    prev[next_mask][j] = i;
                }
            }
        }
    }

    // Encontra o custo mínimo voltando ao vértice de início
    int best_cost = INF;
    int last = -1;
    int full_mask = (1 << num_V) - 1;
    for (int i = 0; i < num_V; i++) {
        if (dp[full_mask][i] == INF || dist[i][start_index] == INF) continue;
        int cost = dp[full_mask][i] + dist[i][start_index];
        if (cost < best_cost) {
            best_cost = cost;
            last = i;
        }
    }

    vector<int> numeric_path; // Vetor com o caminho numérico

    // Reconstrução do caminho 
    if (last == -1) {  // Caso não haja solução válida
        return make_pair(INF, vector<string>());
    }
    int mask = full_mask;
    int current = last;
    while (mask) {
        numeric_path.push_back(current);
        int temp = prev[mask][current];
        mask = mask & ~(1 << current);
        current = temp;
    }

    // Converte o caminho numérico para os nomes dos vértices
    vector<string> path;
    for (int i : numeric_path) {
        path.push_back(numbers_to_vertices[i]);
    }

    return make_pair(best_cost, path);
}