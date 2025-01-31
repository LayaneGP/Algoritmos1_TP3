#pragma once

#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

// Classe que representa um grafo direcionado usando lista de adjacência
class Graph {
    public:
        unordered_map<string, list<pair<string, int>>> adj; // lista de adjacência do tipo: vértice, vizinho, distância

        // Construtores
        Graph(){}
        Graph(int v){
            this->_V = v;
        }

        // Adiciona arestas no grafo
        void addEdge(const string& start, const string& end, const int dist);

        // Retorna o número de vértices no grafo
        int numV();

        // Imprime o grafo em ordem de inserção dos vértices
        void print();

        // Atualiza a quantidade de vértices
        void setNumV(int n);
    
    private:
        int _V; // número de vértices
};