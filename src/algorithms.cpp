#include "./../include/bfs.hpp"
#include "./../include/dfs.hpp"
#include "./../include/graph.hpp"
#include "./../include/algorithms.hpp"

#include <vector>

// Utiliza força bruta
pair<int, vector<string>> brute_force(Graph& graph){
    return permutations(graph);
};


// Utiliza programação dinâmica
pair<int, vector<string>> dynamic(Graph& graph, string start){

};


// Utiliza estratégia gulosa
pair<int, vector<string>> greedy(Graph& graph, string start){
    return greedy_bfs(graph, start);
};

