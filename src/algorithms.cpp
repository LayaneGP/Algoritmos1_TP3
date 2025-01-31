#include "./../include/bfs.hpp"
#include "./../include/dfs.hpp"
#include "./../include/graph.hpp"
#include "./../include/algorithms.hpp"

#include <list>

// Utiliza força bruta
pair<int, list<string>> brute_force(Graph& graph, string start){
    return dfs(graph, start);
};


// Utiliza programação dinâmica
pair<int, list<string>> dynamic(Graph& graph, string start){

};


// Utiliza estratégia gulosa
pair<int, list<string>> greedy(Graph& graph, string start){
    return greedy_bfs(graph, start);
};

