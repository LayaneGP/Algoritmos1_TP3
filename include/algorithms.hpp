#pragma once

#include "./../include/graph.hpp"

#include <vector>

// Utiliza força bruta
pair<int, vector<string>> brute_force(Graph& graph);


// Utiliza programação dinâmica
pair<int, vector<string>> dynamic(Graph& graph, string start);


// Utiliza estratégia gulosa
pair<int, vector<string>> greedy(Graph& graph, string start);

