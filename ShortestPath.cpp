#include <iostream>
#include <list>

using namespace std;

//Graph class that will store input vertices and edges.
class Graph {
    int numberOfVertices;
    list<int> *adjacent;

public:
    Graph(int numberOfVertices);
    void addEdge(int u, int v);
    void BFS(int source);
};

//Constructor for Graph class
Graph::Graph(int numberOfVertices) {
    this->numberOfVertices = numberOfVertices;
    adjacent = new list<int>[numberOfVertices];
}

//Add more vertices and/or edges to the graph
void Graph::addEdge(int u, int v) {
    adjacent[u].push_back(v);
}

//Breadth-First Search for Graph (Regardless if directed or undirected)
void Graph::BFS(int source) {

    bool *visited = new bool[numberOfVertices];
    for (int i = 0; i < numberOfVertices; i++) {
        visited[i] = false;
    }

    list<int> queue;

    //First vertex is always visited
    visited[source] = true;
    queue.push_back(source);

    while (!queue.empty()) {
        source = queue.front();
        cout << source << " ";
        queue.pop_front();

        for (list<int>::iterator i = adjacent[source].begin();
                i != adjacent[source].end(); i++)
        {
            if (!visited[*i]) {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
}

int main() {
    //TODO: Read the file and create the graph
    return 0;
}