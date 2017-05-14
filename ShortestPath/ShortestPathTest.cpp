//
// Created by socra_000 on 5/12/2017.
//

#include <iostream>
#include <fstream>

#include "DirectedShortestPath.h"
#include "UndirectedShortestPath.h"

using namespace std;

int largestVertex = 0;  //Used to find number of vertices required.
int numberOfEdges = 0;

void determineVertices(ifstream &file) {

    int source, destination, weight;

    while (!file.eof()) {
        file >> source >> destination >> weight;
        if (source > largestVertex)
            largestVertex = source;
        else if (destination > largestVertex)
            largestVertex = destination;
        numberOfEdges++;
    }
    file.clear();
    file.seekg(0, ios::beg);
}

void createUndirected (ifstream &file, UndirectedGraph graph) {

    int source, destination, weight;

    int edgeCount = 0;

    while (!file.eof()) {
        file >> source >> destination >> weight;
        graph.addEdge(source,destination,weight, edgeCount);
        edgeCount++;
    }
    file.clear();
    file.seekg(0, ios::beg);

}

void createDirected (ifstream &file, DirectedGraph graph) {

    int source, destination, weight;

    int edgeCount = 0;

    while (!file.eof()) {
        file >> source >> destination >> weight;
        graph.addEdge(source,destination,weight, edgeCount);
        edgeCount++;
    }
    file.clear();
    file.seekg(0, ios::beg);
}

int main() {
    //TODO: Read the file and create the graph

    ifstream file;

    file.open("input.txt"); // Open the file

    // Check if the file is opened or not
    // Exit if not
    if (file.fail()) {
        cout << "Fail to open the file" << endl;
        exit(1);
    }

    determineVertices(file); //Will find largest vertex from file

    //Initialize graph with largestVertex + 1 == size;
    DirectedGraph directedGraph(largestVertex + 1, numberOfEdges);
    UndirectedGraph undirectedGraph(largestVertex +1, numberOfEdges);

    //Will add edges to graph from the file
    createDirected(file,directedGraph);
    createUndirected(file, undirectedGraph);

    file.close(); // Close the file

    //TEST: Try some data with the functions.

    directedGraph.BFS(0);

    directedGraph.Dijkstra(0);

    directedGraph.Bellman(0);

    undirectedGraph.BFS(0);

    undirectedGraph.Dijkstra(0);

    undirectedGraph.Bellman(0);

    return 0;
}

