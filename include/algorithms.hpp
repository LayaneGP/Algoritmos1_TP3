#pragma once

#include "./../include/graph.hpp"

#include <list>

// Utiliza força bruta
pair<int, list<string>> brute_force(Graph& graph, string start);


// Utiliza programação dinâmica
pair<int, list<string>> dynamic(Graph& graph, string start);


// Utiliza estratégia gulosa
pair<int, list<string>> greedy(Graph& graph, string start);

