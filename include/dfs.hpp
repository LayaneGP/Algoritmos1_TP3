#pragma once

#include "graph.hpp"

#include <iostream>
#include <unordered_map>

// Função principal da busca em profundidade
pair<int, list<string>> dfs(Graph& graph, string start);

// Função recursiva da busca em profundidade
void dfs_visit(Graph& graph, string start, unordered_map<string, int>& colors, string current, list<string>& path, list<string>& best_path, int& current_dist, int& min_dist);