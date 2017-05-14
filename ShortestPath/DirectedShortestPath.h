//
// Created by socra_000 on 5/12/2017.
//

#include <iostream>
#include <list>

using namespace std;

#ifndef SHORTESTPATH_DIRECTEDSHORTESTPATH_H
#define SHORTESTPATH_DIRECTEDSHORTESTPATH_H

// Easier management of pairs.
typedef pair<int, int> weightPair;

struct Edge {
    int source, dest, weight;
};

// DirectedGraph class that will store input vertices and edges.
class DirectedGraph {
    int numberOfVertices;
    list<int> *adjacent;
    list<weightPair> *adjacentWeight; //Including weight.
    struct Edge* edge;
    int numberOfEdges = 0;

public:
    DirectedGraph(int numberOfVertices, int numberOfEdges);
    void addEdge(int source, int dest, int weight, int edgeCount);
    void BFS(int source);
    void Dijkstra(int source);
    void Bellman(int source);
    int getEdges();

};

#endif //SHORTESTPATH_DIRECTEDSHORTESTPATH_H
