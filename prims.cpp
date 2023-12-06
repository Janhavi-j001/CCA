#include <iostream>
#include <climits>

using namespace std;

// Structure to represent a graph
struct Graph {
    int V; // Number of vertices
    int** matrix; // Adjacency matrix to store edge weights
};

// Function to initialize a graph
Graph* initializeGraph(int V) {
    Graph* graph = new Graph();
    graph->V = V;

    // Initialize the matrix with INT_MAX (representing infinity)
    graph->matrix = new int*[V];
    for (int i = 0; i < V; i++) {
        graph->matrix[i] = new int[V];
        for (int j = 0; j < V; j++) {
            graph->matrix[i][j] = INT_MAX;
        }
    }

    return graph;
}

// Function to add an edge to the graph
void addEdge(Graph* graph, int source, int destination, int weight) {
    graph->matrix[source][destination] = weight;
    graph->matrix[destination][source] = weight;
}

// Function to find the vertex with the minimum key value
int minKey(int* key, bool* mstSet, int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }

    return min_index;
}

// Function to print the minimum cost spanning tree
void printMST(int* parent, Graph* graph) {
    cout << "Edges in the Minimum Spanning Tree:" << endl;
    for (int i = 1; i < graph->V; i++) {
        cout << "(" << parent[i] << " - " << i << ") Weight: " << graph->matrix[i][parent[i]] << endl;
    }
}

// Function to perform Prim's algorithm
void prim(Graph* graph) {
    int V = graph->V;
    int* parent = new int[V]; // To store the parent of each vertex in the MST
    int* key = new int[V]; // Key values used to pick minimum weight edge

    bool* mstSet = new bool[V]; // Set to keep track of vertices included in the MST
    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    // Start with the first vertex
    key[0] = 0;
    parent[0] = -1; // No parent for the first vertex

    // Construct the MST
    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet, V);

        mstSet[u] = true;

        // Update key values and parent for adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++) {
            if (graph->matrix[u][v] && !mstSet[v] && graph->matrix[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph->matrix[u][v];
            }
        }
    }

    // Print the MST
    printMST(parent, graph);

    // Free allocated memory
    delete[] parent;
    delete[] key;
    delete[] mstSet;
}

// Driver program to test the functions
int main() {
    int V, E;

    // Input: Number of vertices and edges
    cout << "Enter the number of vertices: ";
    cin >> V;

    // Initialize the graph
    Graph* graph = initializeGraph(V);

    // Input: Number of edges
    cout << "Enter the number of edges: ";
    cin >> E;

    // Input the edges and their weights
    cout << "Enter the edges (source destination weight):\n";
    for (int i = 0; i < E; i++) {
        int source, destination, weight;
        cin >> source >> destination >> weight;
        addEdge(graph, source, destination, weight);
    }

    // Perform Prim's algorithm
    prim(graph);

    // Free allocated memory
    for (int i = 0; i < V; i++) {
        delete[] graph->matrix[i];
    }
    delete[] graph->matrix;
    delete graph;

    return 0;
}
input : 

Enter the number of vertices: 5
Enter the number of edges: 7
Enter the edges (source destination weight):
0 1 2
0 2 4
1 2 1
1 3 7
2 3 3
2 4 5
3 4 6

output:

Edges in the Minimum Spanning Tree:
(0 - 1) Weight: 2
(2 - 0) Weight: 4
(1 - 2) Weight: 1
(3 - 2) Weight: 3