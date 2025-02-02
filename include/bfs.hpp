#pragma once

#include "graph.hpp"

#include <iostream>
#include <vector>
#include <unordered_map>

/*
// Busca em largura que retorna a quantidade de camadas (ou -1, se o grafo não for conexo)
int BFS(Graph& graph, string start);

// Retorna o melhor vértice para ser a capital
string findCapital(Graph& graph);

// Encontra o melhor vértice para ser o batalhão de uma CFC
string findBatallion(Graph& scc_graph, list<string>& candidates);

// Itera sobre as CFCs para encontrar os melhores batalhões de cada uma
void findBestBatallions(unordered_map<string, Graph>& initial_sccs, unordered_map<string, Graph>& final_sccs, unordered_map<string, int>& dist);

// Busca em largura que usa um map não ordenado de distâncias e não tem retorno
void BFS(Graph& graph, string start, unordered_map<string, int>& dist);
*/

// Busca em largura gulosa para encontrar o menor caminho no grafo que passe por todos os vértices, e uma única vez
pair<int, vector<string>> greedy_bfs(Graph& graph, string start);