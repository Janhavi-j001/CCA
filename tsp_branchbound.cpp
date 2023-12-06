#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

const int INF = std::numeric_limits<int>::max();

class TSP {
public:
    TSP(const std::vector<std::vector<int>>& graph);

    void solve();

private:
    void branchAndBound();
    int calculateBound(const std::vector<int>& path);
    void addToPath(int vertex);
    void removeFromPath(int vertex);
    void printSolution();

    int numVertices;
    std::vector<std::vector<int>> costMatrix;
    std::vector<int> currentPath;
    std::vector<int> bestPath;
    int bestCost;
};

TSP::TSP(const std::vector<std::vector<int>>& graph) {
    numVertices = graph.size();
    costMatrix = graph;
    bestCost = INF;

    // Initialize paths
    currentPath.resize(numVertices);
    bestPath.resize(numVertices);

    for (int i = 0; i < numVertices; ++i) {
        currentPath[i] = bestPath[i] = i;
    }
}

void TSP::solve() {
    branchAndBound();
    printSolution();
}

void TSP::branchAndBound() {
    do {
        int currentCost = calculateBound(currentPath);

        if (currentCost < bestCost) {
            bestCost = currentCost;
            bestPath = currentPath;
        }
    } while (std::next_permutation(currentPath.begin() + 1, currentPath.end()));
}

int TSP::calculateBound(const std::vector<int>& path) {
    int bound = 0;

    for (int i = 0; i < numVertices - 1; ++i) {
        if (costMatrix[path[i]][path[i + 1]] == INF) {
            return INF;
        }
        bound += costMatrix[path[i]][path[i + 1]];
    }

    bound += costMatrix[path.back()][path[0]]; // Return to the starting city

    return bound;
}

void TSP::addToPath(int vertex) {
    for (int i = numVertices - 2; i > 0; --i) {
        currentPath[i + 1] = currentPath[i];
    }
    currentPath[1] = vertex;
}

void TSP::removeFromPath(int vertex) {
    for (int i = 1; i < numVertices - 1; ++i) {
        if (currentPath[i] == vertex) {
            currentPath.erase(currentPath.begin() + i);
            break;
        }
    }
}

void TSP::printSolution() {
    std::cout << "Optimal Path: ";
    for (int vertex : bestPath) {
        std::cout << vertex << " ";
    }
    std::cout << bestPath[0] << std::endl;

    std::cout << "Optimal Cost: " << bestCost << std::endl;
}

int main() {
    // Example graph with distances between cities (INF if not connected)
    std::vector<std::vector<int>> graph = {
        {0, 10, 15, 20},
        {5, 0, 9, 10},
        {6, 13, 0, 12},
        {8, 8, 9, 0}
    };

    TSP tsp(graph);
    tsp.solve();

    return 0;
}
