//
// Created by socra_000 on 5/12/2017.
//
#include <iostream>
#include <list>

using namespace std;

#ifndef SHORTESTPATH_UNDIRECTEDSHORTESTPATH_H
#define SHORTESTPATH_UNDIRECTEDSHORTESTPATH_H

typedef pair<int, int> weightPair;

struct Edges {
    int source, dest, weight;
};

class UndirectedGraph {
    int numberOfVertices;
    list<int> *adjacent;
    list<weightPair> *adjacentWeight; //Including weight.
    struct Edges* edgeGoing;
    struct Edges* edgeComing;
    int numberOfEdges = 0;

public:
    UndirectedGraph(int numberOfVertices, int numberOfEdges);
    void addEdge(int source, int dest, int weight, int edgeCount);
    void BFS(int source);
    void Dijkstra(int source);
    void Bellman(int source);
    int getEdges();

};


#endif //SHORTESTPATH_UNDIRECTEDSHORTESTPATH_H
