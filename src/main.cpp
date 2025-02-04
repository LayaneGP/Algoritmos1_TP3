#include "./../include/greedy.hpp"
#include "./../include/bruteForce.hpp"
#include "./../include/dynamic.hpp"
#include "./../include/graph.hpp"

#include <iostream>
#include <limits>
#include <vector>

using namespace std;

const int INF = numeric_limits<int>::max();  // Constante para representar uma distância infinita

// Função main para rodar os algoritmos como solicitado
int main(){
    char type_algorithm;
    int V = 0, E = 0, dist = 0;
    string start, end;

    cin >> type_algorithm >> V >> E;

    Graph graph(V);

    pair<int, string> min_distance = make_pair(INF, ""); // Menor peso de aresta no grafo e seu vértice inicial (o inserido primeiro)

    for(int i = 0; i < E; i++){
        cin >> start >> end >> dist;
        graph.addEdge(start, end, dist);
        graph.addEdge(end, start, dist);

        if(dist < min_distance.first){
            min_distance = make_pair(dist, start);
        }
    }

    // Par que armazena a menor distância e o caminho encontrado para solucionar o problema
    pair<int, vector<string>> path;

    switch (type_algorithm){
        case 'b':       // Força bruta
            path = permutations(graph);
            break;

        case 'd':       // Programação dinâmica
            path = dynamic(graph);
            break;

        case 'g':       // Algoritmo guloso
            path = greedy_bfs(graph, start);
            break;
        
        default:
            break;
    }

    cout << path.first << endl;
    for(const string& vertice : path.second){
        cout << vertice << " ";
    }
    cout << endl;

    return 0;
}



/*
// Função main e bibliotecas adicionais para gerar a análise experimental

#include <fstream>
#include <sstream>
#include <string>
#include <chrono>

using namespace std;

int main() {
    int type_algorithm = 1; // Iterador para decidir o algoritmo a ser usado (1 = d; 2 = g; 3 = b)

    while(type_algorithm <= 3){
        int test_number = 0; // Número do teste atual
        
        ifstream inputFile("input.txt");
        if (!inputFile) {
            cerr << "Erro ao abrir o arquivo." << endl;
            return 1;
        }
    
        cout << "Algoritmo: " << type_algorithm << endl;
        cout << "Teste | Tempo | Custo" << endl;
        
        // Enquanto houver dados no arquivo
        while (!inputFile.eof()) {
            test_number++;

            int V = 0, E = 0;
            string start_point; // Ponto de partida do algoritmo guloso
            
            // Lê os dados de vértice e arestas
            if (!(inputFile >> V >> E)) {
                break; // Sai se não conseguir ler
            }
            Graph graph(V); // Grafo criado
            
            pair<int, string> min_distance = make_pair(INF, ""); // Menor peso de aresta no grafo e seu vértice inicial (o inserido primeiro)
            
            // Ignora o restante da linha para preparar a leitura das arestas
            inputFile.ignore(numeric_limits<streamsize>::max(), '\n');
                    
            // Lê as arestas nas próximas linhas
            for (int i = 0; i < E; i++) {
                string line;
                if (!getline(inputFile, line)) {
                    cerr << "Fim do arquivo alcançado inesperadamente." << endl;
                    break;
                }
                
                istringstream iss(line);
                string start, end;
                int dist = 0;
                
                if (!(iss >> start >> end >> dist)) {
                    cerr << "Formato invalido na linha: " << line << endl;
                    continue;
                }

                // Inserção da aresta no grafo
                graph.addEdge(start, end, dist);
                graph.addEdge(end, start, dist);

                if(dist < min_distance.first){
                    start_point = start;
                    min_distance = make_pair(dist, start_point);
                }
            }

            // Par que armazena a menor distância e o caminho encontrado para solucionar o problema
            pair<int, vector<string>> path;

            std::chrono::high_resolution_clock::time_point time_start; // Tempo de início
            std::chrono::high_resolution_clock::time_point time_end; // Tempo de término
            std::chrono::duration<double, std::milli> interval; // Duração em milissegundos

            switch (type_algorithm){
                case 1:       // Programação dinâmica
                    time_start = chrono::high_resolution_clock::now(); // Tempo de início
                    path = dynamic(graph);
                    time_end = chrono::high_resolution_clock::now(); // Tempo de término
                    break;

                case 2:       // Algoritmo guloso
                    time_start = chrono::high_resolution_clock::now(); // Tempo de início
                    path = greedy_bfs(graph, start_point);
                    time_end = chrono::high_resolution_clock::now(); // Tempo de término
                    break;
                
                case 3:       // Força bruta
                    time_start = chrono::high_resolution_clock::now(); // Tempo de início
                    path = permutations(graph);
                    time_end = chrono::high_resolution_clock::now(); // Tempo de término
                    break;

                default:
                    break;
            }
            interval = time_end - time_start;

            cout << test_number << "       " << interval.count() << "        " << path.first << endl;
        }
        cout << "-----------------------------" << endl;
        
        inputFile.close();
        type_algorithm++;
    }
    
    return 0;
}
*/