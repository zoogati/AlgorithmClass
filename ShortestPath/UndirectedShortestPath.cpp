//
// Created by socra_000 on 5/12/2017.
//
#include <iostream>
#include <list>
#include <queue>
#include <cmath>

#include "UndirectedShortestPath.h"


// Constructor for UndirectedGraph class
UndirectedGraph::UndirectedGraph(int numberOfVertices,
                                 int numberOfEdges) {

    this->numberOfVertices = numberOfVertices;
    this->numberOfEdges = numberOfEdges;
    adjacent = new list<int>[numberOfVertices];
    adjacentWeight = new list<weightPair>[numberOfVertices];
    edgeGoing = new Edges[numberOfEdges];
    edgeComing = new Edges[numberOfEdges];

}

// Add more vertices and/or edges to the graph
void UndirectedGraph::addEdge(int source, int dest,
                              int weight, int edgeCount) {

    adjacent[source].push_back(dest);
    adjacentWeight[source].push_back(
            make_pair(dest, weight));
    adjacentWeight[dest].push_back(
            make_pair(source, weight));
    edgeGoing[edgeCount] = {source, dest, weight};
    edgeComing[edgeCount] = {dest, source, weight};
}

int UndirectedGraph::getEdges() {
    return numberOfEdges;
}

// Breadth-First Search (Regardless if directed
// or undirected)
void UndirectedGraph::BFS(int source) {

    bool *visited = new bool[numberOfVertices];
    for (int i = 0; i < numberOfVertices; i++) {
        visited[i] = false;
    }

    int distance[numberOfVertices];
    list<int> queue;

    int edgeNumber = 0, vertexNumber = 0;

    for (int i = 0; i < numberOfVertices; i++) {
        distance[i] = 0;
    }

    //First vertex is always visited
    visited[source] = true;
    //Weight is arbitrary for BFS so choose 0
    queue.push_back(source);

    cout << "Breadth First Search Algorithm: " << endl;

    while (!queue.empty()) {
        source = queue.front();
        vertexNumber++;
        queue.pop_front();

        list<int>::iterator i;
        for (i = adjacent[source].begin();
             i != adjacent[source].end(); ++i)
        {
            edgeNumber++;
            if (!visited[*i]) {
                distance[*i] = distance[source] + 1;
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }

    printf("Best distance from source to end of graph: "
                   "%d\n", distance[numberOfVertices-1]);
    printf("Runtime: %d\n\n", edgeNumber+vertexNumber);

}

// Dijkstra's Algorithm using priority queue.
void UndirectedGraph::Dijkstra(int source) {

    // Creating a min heap from a STD priority queue.
    // Constructor follows following format:
    // <Type, vector<Type>, ComparisonType>
    // Greater sorts in ascending order.

    priority_queue<weightPair, vector <weightPair>,
            greater<weightPair>> priorityQueue;

    //Initialize all distances as infinite.
    vector<int> dist(numberOfVertices, INFINITY);
    int edgeNumber = 0, vertexNumber = 0;

    //Start with source vertex.
    priorityQueue.push(make_pair(0,source));
    dist[source] = 0;

    while (!priorityQueue.empty()) {

        int sourceVertex = priorityQueue.top().second;
        vertexNumber++;
        priorityQueue.pop();

        list<weightPair>::iterator i;
        for(i = adjacentWeight[sourceVertex].begin();
            i != adjacentWeight[sourceVertex].end(); ++i) {

            int adjVertex = (*i).first;
            int weight = (*i).second;

            edgeNumber++;

            if(dist[adjVertex] >
               dist[sourceVertex] + weight) {

                dist[adjVertex] =
                        dist[sourceVertex] + weight;
                priorityQueue.push(make_pair(
                        dist[adjVertex],
                        adjVertex));
            }
        }
    }

    printf("Dijkstra Algorithm: \n");
    printf("Best weight from source to end of graph:"
                   " %d\n", dist[numberOfVertices-1]);
    printf("Runtime: %d\n\n", edgeNumber+vertexNumber);

}

//Bellman-Ford Algorithm
void UndirectedGraph::Bellman(int source) {

    vector<int> dist(numberOfVertices, INFINITY);
    dist[source] = 0;

    int edgeNumber = 0, vertexNumber = 0;

    for (int i = 1; i < numberOfVertices; i++) {

        vertexNumber++;

        for(int j = 0; j < numberOfEdges; j++) {

            edgeNumber++;

            if (edgeComing[j].source < edgeGoing[j].source) {
                int sourceVertex = edgeComing[j].source;
                int adjVertex = edgeComing[j].dest;
                int weight = edgeComing[j].weight;

                if (dist[adjVertex] >
                    dist[sourceVertex] + weight &&
                    dist[sourceVertex] != INFINITY) {
                    edgeNumber++;
                    dist[adjVertex] =
                            dist[sourceVertex] + weight;
                }
            }
            else {
                int sourceVertex = edgeGoing[j].source;
                int adjVertex = edgeGoing[j].dest;
                int weight = edgeGoing[j].weight;

                if (dist[adjVertex] >
                    dist[sourceVertex] + weight &&
                    dist[sourceVertex] != INFINITY) {
                    edgeNumber++;
                    dist[adjVertex] =
                            dist[sourceVertex] + weight;
                }
            }
        }
    }

    vertexNumber++;

    printf("Bellman-Ford Algorithm: \n");
    printf("Best weight from source to end of graph: "
                   "%d\n", dist[numberOfVertices-1]);
    printf("Runtime: %d\n\n", edgeNumber+vertexNumber);

}

