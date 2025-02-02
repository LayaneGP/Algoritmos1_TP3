#pragma once

#include "graph.hpp"

#include <iostream>
#include <vector>

// Função principal da busca em profundidade
pair<int, vector<string>> permutations(Graph& graph);

// Função recursiva da busca em profundidade
void permutations_rec(Graph& graph, pair<int, vector<string>>& best_path, vector<string> perm, int start_index, int end_index);