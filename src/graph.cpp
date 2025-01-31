#include "./../include/graph.hpp"

#include <iostream>
#include <map>
#include <list>

using namespace std;

void Graph::addEdge(const string& start, const string& end, const int dist){
    adj[start].push_back(make_pair(end, dist));
}

int Graph::numV(){
    return _V;
}

void Graph::print(){
    for (const auto& edge : adj) {
        cout << edge.first << ": ";
        for (auto neighbour : edge.second) {
            cout << "(" << neighbour.first << ", " << neighbour.second << ") ";
        }
        cout << endl;
    }
    cout << endl;
}

void Graph::setNumV(int n){
    _V = n;
}