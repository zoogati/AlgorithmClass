#include <iostream>
#include <list>
#include <queue>
#include <cmath>

#include "DirectedShortestPath.h"

using namespace std;

// Constructor for DirectedGraph class
DirectedGraph::DirectedGraph(int numberOfVertices,
                             int numberOfEdges) {
    this->numberOfVertices = numberOfVertices;
    this->numberOfEdges = numberOfEdges;
    adjacent = new list<int>[numberOfVertices];
    adjacentWeight = new list<weightPair>[numberOfVertices];
    edge = new Edge[numberOfEdges];
}

// Add more vertices and/or edges to the graph
void DirectedGraph::addEdge(int source, int dest,
                            int weight, int edgeCount) {
    adjacent[source].push_back(dest);
    adjacentWeight[source].push_back(
            make_pair(dest, weight));
    edge[edgeCount] = {source, dest, weight};
}

int DirectedGraph::getEdges() {
    return numberOfEdges;
}

// Breadth-First Search (Regardless if directed
// or undirected)
void DirectedGraph::BFS(int source) {

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
    printf("Runtime: %d\n\n", vertexNumber+edgeNumber);
}

// Dijkstra's Algorithm using priority queue.
void DirectedGraph::Dijkstra(int source) {

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
void DirectedGraph::Bellman(int source) {

     vector<int> dist(numberOfVertices, INFINITY);
     dist[source] = 0;

     int edgeNumber = 0, vertexNumber = 0;

     for (int i = 1; i < numberOfVertices; i++) {

         vertexNumber++;

         for(int j = 0; j < numberOfEdges; ++j) {

             edgeNumber++;

             int sourceVertex = edge[j].source;
             int adjVertex = edge[j].dest;
             int weight = edge[j].weight;

             if (dist[adjVertex] >
                     dist[sourceVertex] + weight &&
                     dist[sourceVertex] != INFINITY) {
                 edgeNumber++;
                 dist[adjVertex] =
                         dist[sourceVertex] + weight;
             }
         }
     }

     vertexNumber++;

     printf("Bellman-Ford Algorithm: \n");
     printf("Best weight from source to end of graph: "
                    "%d\n", dist[numberOfVertices-1]);
     printf("Runtime: %d\n\n", edgeNumber+vertexNumber);

 }