#pragma once

#include "graph.hpp"

#include <iostream>
#include <vector>

// Busca em largura gulosa para encontrar o menor caminho no grafo que passe por todos os vértices, e uma única vez
pair<int, vector<string>> greedy_bfs(Graph& graph, string start);