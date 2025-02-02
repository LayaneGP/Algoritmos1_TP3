#include "dynamic.hpp"
#include "graph.hpp"

#include <iostream>
#include <vector>
#include <limits>
#include <unordered_map>

const int INF = numeric_limits<int>::max();  // Constante para representar uma distância infinita

// Programação dinâmica
pair<int, vector<string>> dynamic(Graph& graph, string start){
    int num_V = graph.numV(); // Quantidade de vértices no grafo

    unordered_map<string, int> vertices_to_numbers; // Mapa de um vértice para um inteiro que o representa
    unordered_map<int, string> numbers_to_vertices; // Mapa de um inteiro para o vértice que ele representa

    vertices_to_numbers[start] = 0;
    int v_index = 1;
    for(const auto& v : graph.adj){
        if(v.first != start){
            vertices_to_numbers[v.first] = v_index;
            numbers_to_vertices[v_index] = v.first;
            v_index++;
        }
    }
    vertices_to_numbers[start] = 0;
    numbers_to_vertices[0] = start;

    vector<vector<int>> dist(num_V, vector<int>(num_V, 0)); // Matriz de distância dos vértices com valores iniciais infinitos

    // Construção da matriz de distâncias
    for(const auto& pair : graph.adj){
        int from = vertices_to_numbers[pair.first];
        dist[from][from] = 0;
        for(const auto& neighbour : pair.second){
            int to = vertices_to_numbers[neighbour.first];
            dist[from][to] = neighbour.second;
        }
    }

    vector<vector<int>> dp(num_V, vector<int>(num_V, INF)); // Matriz da DP com valores iniciais infinitos
    vector<vector<int>> prev(num_V, vector<int>(num_V, -1)); // Matriz dos antecessores com valores iniciais inválidos

    for (int i = 0; i < num_V; i++) {
        dp[0][i] = dist[0][i]; // Custo de ir do vértice inicial a cada outro
        prev[1][i] = 0; // O caminho percorrendo um vértice vem de 0 (start)
    }


    // Preenchendo as tabelas dp e prev
    // k = quantidade de vértices visitados
    // i = vértice atual
    // j = próximo vértice
    for(int k = 1; k < num_V; k++){
        for(int j = 0; j < num_V; j++){
            for(int i = 0; i < num_V; i++){
                if(i != j && dist[i][j] != INF && dp[k-1][i] != INF) {
                    if(dp[k-1][i] + dist[i][j] < dp[k][j]){
                        dp[k][j] = dp[k-1][i] + dist[i][j];
                        prev[k][j] = i;
                    }
                }
            }
        }
    }

    int min_cost = INF; // Menor custo até agora
    int last_vertice = -1; // Último vértice no caminho

    // Encontra o último vértice no caminho
    for(int i = 0; i < num_V; i++){
        if(dp[num_V - 1][i] + dist[i][0] < min_cost){
            min_cost = dp[num_V - 1][i] + dist[i][0];
            last_vertice = i;
        }
    }

    vector<int> numeric_path; // Vetor com o caminho numérico

    // Reconstroi o caminho
    for(int k = num_V - 1; k > 0; k--){
        numeric_path.push_back(last_vertice);
        last_vertice = prev[k][last_vertice];
    }
    numeric_path.push_back(0); // Adiciona o vértice inicial

    vector<string> path; // Caminho a ser retornado

    for(int i = num_V - 1; i >= 0; i--){
        path.push_back(numbers_to_vertices[i]);
    }

    cout << endl;
    for(const auto& v : vertices_to_numbers){
        cout << v.first << ": " << v.second << endl;
    }

    cout << "Matriz de distâncias:" << endl;
    for (int i = 0; i < num_V; i++) {
        for (int j = 0; j < num_V; j++) {
            if (dist[i][j] == INF) cout << "INF ";
            else cout << dist[i][j] << " ";
        }
        cout << endl;
    }

        cout << endl;
    cout << "Matriz dp:" << endl;
    for(int i = 0; i < num_V; i++){
        for(int j = 0; j < num_V; j++){
            cout << dp[i][j] << "   ";
        }
        cout << endl;
    }



    return make_pair(min_cost, path);
};