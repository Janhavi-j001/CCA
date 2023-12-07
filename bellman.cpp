// A C++ program for Bellman-Ford's single source
// shortest path algorithm.
#include <bits/stdc++.h>
using namespace std;

// a structure to represent a weighted edge in graph
struct Edge {
	int src, dest, weight;
};

// a structure to represent a connected, directed and
// weighted graph
struct Graph {
	// V-> Number of vertices, E-> Number of edges
	int V, E;

	// graph is represented as an array of edges.
	struct Edge* edge;
};

// Creates a graph with V vertices and E edges
struct Graph* createGraph(int V, int E)
{
	struct Graph* graph = new Graph;
	graph->V = V;
	graph->E = E;
	graph->edge = new Edge[E];
	return graph;
}

// A utility function used to print the solution
void printArr(int dist[], int n)
{
	printf("Vertex Distance from Source\n");
	for (int i = 0; i < n; ++i)
		printf("%d \t\t %d\n", i, dist[i]);
}

// The main function that finds shortest distances from src
// to all other vertices using Bellman-Ford algorithm. The
// function also detects negative weight cycle
void BellmanFord(struct Graph* graph, int src)
{
	int V = graph->V;
	int E = graph->E;
	int dist[V];

	// Step 1: Initialize distances from src to all other
	// vertices as INFINITE
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX;
	dist[src] = 0;

	// Step 2: Relax all edges |V| - 1 times. A simple
	// shortest path from src to any other vertex can have
	// at-most |V| - 1 edges
	for (int i = 1; i <= V - 1; i++) {
		for (int j = 0; j < E; j++) {
			int u = graph->edge[j].src;
			int v = graph->edge[j].dest;
			int weight = graph->edge[j].weight;
			if (dist[u] != INT_MAX
				&& dist[u] + weight < dist[v])
				dist[v] = dist[u] + weight;
		}
	}

	// Step 3: check for negative-weight cycles. The above
	// step guarantees shortest distances if graph doesn't
	// contain negative weight cycle. If we get a shorter
	// path, then there is a cycle.
	for (int i = 0; i < E; i++) {
		int u = graph->edge[i].src;
		int v = graph->edge[i].dest;
		int weight = graph->edge[i].weight;
		if (dist[u] != INT_MAX
			&& dist[u] + weight < dist[v]) {
			printf("Graph contains negative weight cycle");
			return; // If negative cycle is detected, simply
					// return
		}
	}

	printArr(dist, V);

	return;
}

// Driver's code
int main()
{
	/* Let us create the graph given in above example */
	int V = 5; // Number of vertices in graph
	int E = 8; // Number of edges in graph
	struct Graph* graph = createGraph(V, E);

	// add edge 0-1 (or A-B in above figure)
	graph->edge[0].src = 0;
	graph->edge[0].dest = 1;
	graph->edge[0].weight = -1;

	// add edge 0-2 (or A-C in above figure)
	graph->edge[1].src = 0;
	graph->edge[1].dest = 2;
	graph->edge[1].weight = 4;

	// add edge 1-2 (or B-C in above figure)
	graph->edge[2].src = 1;
	graph->edge[2].dest = 2;
	graph->edge[2].weight = 3;

	// add edge 1-3 (or B-D in above figure)
	graph->edge[3].src = 1;
	graph->edge[3].dest = 3;
	graph->edge[3].weight = 2;

	// add edge 1-4 (or B-E in above figure)
	graph->edge[4].src = 1;
	graph->edge[4].dest = 4;
	graph->edge[4].weight = 2;

	// add edge 3-2 (or D-C in above figure)
	graph->edge[5].src = 3;
	graph->edge[5].dest = 2;
	graph->edge[5].weight = 5;

	// add edge 3-1 (or D-B in above figure)
	graph->edge[6].src = 3;
	graph->edge[6].dest = 1;
	graph->edge[6].weight = 1;

	// add edge 4-3 (or E-D in above figure)
	graph->edge[7].src = 4;
	graph->edge[7].dest = 3;
	graph->edge[7].weight = -3;
	
	// Function call
	BellmanFord(graph, 0);

	return 0;
}
...............................................................................................................

	#include <iostream>
#include <climits>

#define MAX_VERTICES 100
#define MAX_EDGES 100

// Structure to represent an edge in the graph
struct Edge {
    int source, destination, weight;
};

// Structure to represent a graph
struct Graph {
    int V, E; // Number of vertices and edges
    Edge edge[MAX_EDGES]; // Array to store edges
};

// Function to initialize a graph with given vertices and edges
void initializeGraph(Graph *graph, int vertices, int edges) {
    graph->V = vertices;
    graph->E = edges;
}

// Function to relax an edge (update the distance if a shorter path is found)
void relax(int dist[], int source, int destination, int weight) {
    if (dist[source] != INT_MAX && dist[source] + weight < dist[destination]) {
        dist[destination] = dist[source] + weight;
    }
}

// Function to perform Bellman-Ford algorithm
void bellmanFord(Graph *graph, int source) {
    int V = graph->V;
    int E = graph->E;
    int dist[MAX_VERTICES];

    // Initialize distances from source to all other vertices as infinity
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
    }
    dist[source] = 0; // Distance from source to itself is 0

    // Relax all edges |V| - 1 times
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            relax(dist, graph->edge[j].source, graph->edge[j].destination, graph->edge[j].weight);
        }
    }

    // Check for negative weight cycles
    for (int i = 0; i < E; i++) {
        int u = graph->edge[i].source;
        int v = graph->edge[i].destination;
        int weight = graph->edge[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            std::cout << "Graph contains negative weight cycle. Bellman-Ford cannot solve it." << std::endl;
            return;
        }
    }

    // Print the distances
    std::cout << "Vertex   Distance from Source" << std::endl;
    for (int i = 0; i < V; i++) {
        std::cout << i << "\t\t" << dist[i] << std::endl;
    }
}

// Driver program to test the functions
int main() {
    Graph graph;
    int vertices, edges, source;

    // Input: Number of vertices, edges, and the source vertex
    std::cout << "Enter the number of vertices: ";
    std::cin >> vertices;

    std::cout << "Enter the number of edges: ";
    std::cin >> edges;

    initializeGraph(&graph, vertices, edges);

    // Input the edges (source, destination, weight)
    for (int i = 0; i < edges; i++) {
        std::cout << "Enter edge " << i + 1 << " (source destination weight): ";
        std::cin >> graph.edge[i].source >> graph.edge[i].destination >> graph.edge[i].weight;
    }

    std::cout << "Enter the source vertex: ";
    std::cin >> source;

    // Perform Bellman-Ford algorithm
    bellmanFord(&graph, source);

    return 0;
}
output :
Enter the number of vertices: 4
Enter the number of edges: 5
Enter edge 1 (source destination weight): 0 1 10
Enter edge 2 (source destination weight): 1 3 15
Enter edge 3 (source destination weight): 2 3 4
Enter edge 4 (source destination weight): 0 2 6
Enter edge 5 (source destination weight): 0 3 5
Enter the source vertex: 0
Vertex   Distance from Source
0               0
1               10
2               6
3               5
