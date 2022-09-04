#pragma once
#include <iostream>
using namespace std;

class Graph {
private:
    int** adjMatrix;
    int numVertices;

public:
    // Initialize the matrix to zero
    Graph(int numVertices) {
        this->numVertices = numVertices;
        adjMatrix = new int* [numVertices];
        for (int i = 0; i < numVertices; i++) {
            adjMatrix[i] = new int[numVertices];
            for (int j = 0; j < numVertices; j++)
                adjMatrix[i][j] = -1;
        }
    }

    // Add edges
    void addEdge(int i, int j,int val) {
        adjMatrix[i][j] = val;
        adjMatrix[j][i] = val;
    }

    int getEdge(int i, int j) {
        return adjMatrix[i][j];
    }

    // Remove edges
    void removeEdge(int i, int j) {
        adjMatrix[i][j] = -1;
        adjMatrix[j][i] = -1;
    }

    // Print the martix
    void toString() {
        for (int i = 0; i < numVertices; i++) {
            cout << i << " : ";
            for (int j = 0; j < numVertices; j++)
                cout << adjMatrix[i][j] << " ";
            cout << "\n";
            
        }
    }

    ~Graph() {
        for (int i = 0; i < numVertices; i++)
            delete[] adjMatrix[i];
        delete[] adjMatrix;
    }
};
