#include "./../include/graph.hpp"

#include <iostream>
#include <list>
#include <limits>
#include <queue>
#include <unordered_set>
#include <unordered_map>

const int INF = numeric_limits<int>::max();  // Constante para representar uma distância infinita

/*
// Busca em largura que retorna a quantidade de camadas (ou -1, se o grafo não for conexo)
int BFS(Graph& graph, string start){
    unordered_set<string> visited; // Set não ordenado para saber se um vértice foi ou não visitado

    queue<string> q; // Fila de vértices descobertos

    int layers = 0; // Profundidade da árvore gerada pela busca

    // Insere o vértice inicial e marca como visitado
    q.push(start); 
    visited.insert(start);

    while(!q.empty()){
        int size = static_cast<int>(q.size());
        layers++;

        // Remove o primeiro vértice da fila até finalizar os que estão na camada atual
        for(int i = 0; i < size; i++){
            string current = q.front();
            q.pop();

            // Se o vizinho do vértice atual não foi visitado, ele é adicionado na fila
            for(const string& neighbour : graph.adj[current]){
                if(visited.find(neighbour) == visited.end()){
                    visited.insert(neighbour);
                    q.push(neighbour);
                }
            }
        }
    }

    // Se todos os vértices foram visitados, retorna a altura da árvore. Caso contrário, retorna valor inválido
    if(static_cast<int>(visited.size()) == graph.numV()){
        return layers;
    } else {
        return -1;
    }
}


// Retorna o melhor vértice para ser a capital
string findCapital(Graph& graph){
    string downtown;
    int numLayers = INF; // Número de camadas da BFS atual 

    unordered_map<string, list<string>> adjascent_list = graph.adj;
    
    for(const auto& pair : adjascent_list){
        int bfsOutput = BFS(graph, pair.first);

        if(bfsOutput != -1 && bfsOutput < numLayers){
            numLayers = bfsOutput;
            downtown = pair.first;
        }
    }

    if(numLayers == INF){
        cout << "Nao foi possivel alcancar todos os vertices." << endl;
    }

    return downtown;
}


// Encontra o melhor vértice entre os candidatos para ser o batalhão de uma CFC
string findBatallion(Graph& scc_graph, list<string>& candidates){
    string representant; // Representante da CFC
    int numLayers_scc = INF; // Número de camadas da BFS atual na CFC

    for(const string& candidate : candidates){
        int bfsOutput_scc = BFS(scc_graph, candidate);
        if(bfsOutput_scc != -1 && bfsOutput_scc < numLayers_scc){
            numLayers_scc = bfsOutput_scc;
            representant = candidate;
        }
    }

    if(numLayers_scc == INF){
        cout << "Nao foi possível alcancar todos os vertices da CFC." << endl;
    }

    return representant;
}


// Itera sobre as CFCs para encontrar os melhores batalhões de cada uma
void findBestBatallions(unordered_map<string, Graph>& initial_sccs, unordered_map<string, Graph>& final_sccs, unordered_map<string, int>& dist){
    // Inclui cada candidato a representante em um map não ordenado cuja chave é o representante atual da SCC
    for(auto& pair : initial_sccs){
        list<string> rep_candidates; // Lista de representantes possíveis para a componente
        rep_candidates.push_back(pair.first);

        // Se a componente tiver apenas um vértice, esse é seu próprio representante
        if(pair.second.numV() == 1){
            final_sccs[pair.first] = initial_sccs[pair.first];
            continue;
        }
        
        int min_dist = dist[pair.first]; // Distância mínima da capital até um vértice da CFC
        // Itera sobre os vértices da CFC e deixa na lista de candidatos apenas os que tiverem a menor distância até a capital
        for(const auto& vert : pair.second.adj){
            if(dist[vert.first] < min_dist){
                rep_candidates.clear(); // O de menor distância é melhor que todos os outros vértices
                rep_candidates.push_back(vert.first);
            } else if(dist[vert.first] == min_dist){
                rep_candidates.push_back(vert.first); // Se tem distância igual à mínima, há mais de um candidato
            }
        }
        // Se tem só um candidato, ele tem distância mínima e é o representante
        // Caso contrário, decide-se pela menor soma das distâncias do candidato aos outros vértices da CFC
        if(rep_candidates.size() == 1 && rep_candidates.front() != pair.first){
            final_sccs[rep_candidates.front()] = initial_sccs[pair.first];

        } else if(rep_candidates.size() > 1) {
            string representant = findBatallion(pair.second, rep_candidates);

            // Se o representante encontrado for diferente do inicial, troca-se
            if(representant != pair.first){
                final_sccs[representant] = initial_sccs[pair.first];
                final_sccs.erase(pair.first);
            }
        }
    }
}
*/


// Busca em largura gulosa para encontrar o menor caminho no grafo que passe por todos os vértices, e uma única vez
pair<int, list<string>> greedy_bfs(Graph& graph, string start){
        
    unordered_set<string> visited; // Set não ordenado para saber se um vértice foi ou não visitado
    list<string> path; // Caminho encontrado
    int total_distance = 0; // Distância total do caminho encontrado

    // Marca o vértice inicial como visitado
    visited.insert(start);

    string current = start;
    path.push_back(start);

    while(static_cast<int>(visited.size()) != graph.numV()){
        int min_dist = INF;  // Distância mínima entre os vizinhos do vértice atual

        // Busca, entre os vértices não visitados, o de menor distância
        for(auto& neighbour : graph.adj[current]){
            if((visited.find(neighbour.first) == visited.end()) && (neighbour.second < min_dist)){
                current = neighbour.first;
                min_dist = neighbour.second;
            }
        }

        path.push_back(current);
        visited.insert(current);
        total_distance += min_dist;
    }

    for(const auto& neighbour : graph.adj[current]){
        if(neighbour.first == start){
            total_distance += neighbour.second;
        }
    }

    if(total_distance == INF){
        cout << "Cuidado! Distancia infinita." << endl;
    }

    return make_pair(total_distance, path);
}
