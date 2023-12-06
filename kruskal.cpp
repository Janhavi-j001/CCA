
#include <bits/stdc++.h> 
using namespace std; 
  
// DSU data structure 
// path compression + rank by union 
class DSU { 
    int* parent; 
    int* rank; 
  
public: 
    DSU(int n) 
    { 
        parent = new int[n]; 
        rank = new int[n]; 
  
        for (int i = 0; i < n; i++) { 
            parent[i] = -1; 
            rank[i] = 1; 
        } 
    } 
  
    // Find function 
    int find(int i) 
    { 
        if (parent[i] == -1) 
            return i; 
  
        return parent[i] = find(parent[i]); 
    } 
  
    // Union function 
    void unite(int x, int y) 
    { 
        int s1 = find(x); 
        int s2 = find(y); 
  
        if (s1 != s2) { 
            if (rank[s1] < rank[s2]) { 
                parent[s1] = s2; 
            } 
            else if (rank[s1] > rank[s2]) { 
                parent[s2] = s1; 
            } 
            else { 
                parent[s2] = s1; 
                rank[s1] += 1; 
            } 
        } 
    } 
}; 
  
class Graph { 
    vector<vector<int> > edgelist; 
    int V; 
  
public: 
    Graph(int V) { this->V = V; } 
  
    // Function to add edge in a graph 
    void addEdge(int x, int y, int w) 
    { 
        edgelist.push_back({ w, x, y }); 
    } 
  
    void kruskals_mst() 
    { 
        // Sort all edges 
        sort(edgelist.begin(), edgelist.end()); 
  
        // Initialize the DSU 
        DSU s(V); 
        int ans = 0; 
        cout << "Following are the edges in the "
                "constructed MST"
             << endl; 
        for (auto edge : edgelist) { 
            int w = edge[0]; 
            int x = edge[1]; 
            int y = edge[2]; 
  
            // Take this edge in MST if it does 
            // not forms a cycle 
            if (s.find(x) != s.find(y)) { 
                s.unite(x, y); 
                ans += w; 
                cout << x << " -- " << y << " == " << w 
                     << endl; 
            } 
        } 
        cout << "Minimum Cost Spanning Tree: " << ans; 
    } 
}; 
  
// Driver code 
int main() 
{ 
    Graph g(4); 
    g.addEdge(0, 1, 10); 
    g.addEdge(1, 3, 15); 
    g.addEdge(2, 3, 4); 
    g.addEdge(2, 0, 6); 
    g.addEdge(0, 3, 5); 
  
    // Function call 
    g.kruskals_mst(); 
  
    return 0; 
}
.....................................................................................................

#include <iostream>
#include <algorithm>

#define MAX_VERTICES 100
#define MAX_EDGES 100

// Structure to represent an edge in the graph
struct Edge {
    int source, destination, weight;
};

// Structure to represent a subset for union-find
struct Subset {
    int parent, rank;
};

// Function to compare two edges based on their weights (used for sorting)
bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

// Function to find the subset of an element (uses path compression)
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Function to perform union of two subsets (uses union by rank)
void unionSets(Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank)
        subsets[rootX].parent = rootY;
    else if (subsets[rootX].rank > subsets[rootY].rank)
        subsets[rootY].parent = rootX;
    else {
        subsets[rootX].parent = rootY;
        subsets[rootY].rank++;
    }
}

// Function to find the minimum cost spanning tree using Kruskal's algorithm
void kruskal(Edge edges[], int V, int E) {
    Edge result[MAX_VERTICES]; // To store the result (the minimum spanning tree)
    Subset subsets[MAX_VERTICES]; // To store the subsets for union-find
    int resultIndex = 0; // Index for the result[] array

    // Step 1: Sort all the edges in non-decreasing order of their weights
    std::sort(edges, edges + E, compareEdges);

    // Step 2: Initialize subsets for each vertex
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Step 3: Iterate through all the edges and add the minimum weight edges that don't form a cycle
    for (int e = 0; e < E; e++) {
        int rootX = find(subsets, edges[e].source);
        int rootY = find(subsets, edges[e].destination);

        if (rootX != rootY) {
            // This edge doesn't form a cycle, add it to the result
            result[resultIndex++] = edges[e];
            unionSets(subsets, rootX, rootY);
        }
    }

    // Print the result (minimum spanning tree)
    std::cout << "Edges in the Minimum Spanning Tree:\n";
    for (int i = 0; i < resultIndex; i++) {
        std::cout << "(" << result[i].source << " - " << result[i].destination << ") Weight: " << result[i].weight << "\n";
    }
}

// Driver program to test the functions
int main() {
    int V, E;

    // Input: Number of vertices and edges
    std::cout << "Enter the number of vertices: ";
    std::cin >> V;

    std::cout << "Enter the number of edges: ";
    std::cin >> E;

    // Input the edges (source, destination, weight)
    Edge edges[MAX_EDGES];
    std::cout << "Enter the edges (source destination weight):\n";
    for (int i = 0; i < E; i++) {
        std::cin >> edges[i].source >> edges[i].destination >> edges[i].weight;
    }

    // Perform Kruskal's algorithm
    kruskal(edges, V, E);

    return 0;
}

input : 

Enter the number of vertices: 4
Enter the number of edges: 5
Enter the edges (source destination weight):
0 1 10
0 2 6
0 3 5
1 3 15
2 3 4

output:

Edges in the Minimum Spanning Tree:
(2 - 3) Weight: 4
(0 - 3) Weight: 5
(0 - 1) Weight: 10
