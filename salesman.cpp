#include <iostream>
#include <limits>

#define MAX_CITIES 10

int min(int a, int b) {
    return (a < b) ? a : b;
}

int tsp(int graph[MAX_CITIES][MAX_CITIES], int mask, int current, int n, int dp[MAX_CITIES][1 << MAX_CITIES]) {
    // If all cities have been visited, return the cost to return to the starting city
    if (mask == (1 << n) - 1) {
        return graph[current][0];
    }

    // If the result is already calculated, return it
    if (dp[current][mask] != -1) {
        return dp[current][mask];
    }

    int minCost = std::numeric_limits<int>::max();

    // Try visiting unvisited cities
    for (int city = 0; city < n; city++) {
        if (!(mask & (1 << city))) { // If the city is not visited
            int newMask = mask | (1 << city);
            int cost = graph[current][city] + tsp(graph, newMask, city, n, dp);

            // Update the minimum cost
            minCost = min(minCost, cost);
        }
    }

    // Save the result in the DP table
    dp[current][mask] = minCost;
    return minCost;
}

void printPath(int graph[MAX_CITIES][MAX_CITIES], int dp[MAX_CITIES][1 << MAX_CITIES], int n) {
    int path[MAX_CITIES];
    int current = 0;
    int mask = 1; // Start from the first city

    // Find the optimal path
    for (int step = 1; step < n; step++) {
        int nextCity = -1;
        for (int city = 0; city < n; city++) {
            if (!(mask & (1 << city))) { // If the city is not visited
                int cost = graph[current][city] + dp[city][mask | (1 << city)];
                if (nextCity == -1 || cost < graph[current][nextCity] + dp[nextCity][mask | (1 << nextCity)]) {
                    nextCity = city;
                }
            }
        }
        path[step] = nextCity;
        mask |= (1 << nextCity);
        current = nextCity;
    }

    // Print the optimal path
    std::cout << "Optimal Path: 0 ";
    for (int i = 1; i < n; i++) {
        std::cout << path[i] << " ";
    }
    std::cout << "0" << std::endl;
}

int main() {
    int n;
    int graph[MAX_CITIES][MAX_CITIES];
    int dp[MAX_CITIES][1 << MAX_CITIES];

    // Input: Number of cities
    std::cout << "Enter the number of cities: ";
    std::cin >> n;

    // Input: Cost matrix for traveling between cities
    std::cout << "Enter the cost matrix for traveling between cities:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> graph[i][j];
        }
    }

    // Initialize the DP table
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (1 << n); j++) {
            dp[i][j] = -1;
        }
    }

    // Find the optimal cost using dynamic programming
    int optimalCost = tsp(graph, 1, 0, n, dp);

    // Print the optimal path and cost
    std::cout << "Optimal Cost: " << optimalCost << std::endl;
    printPath(graph, dp, n);

    return 0;
}
