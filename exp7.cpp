#include <iostream>
#include <climits> // For INT_MAX
using namespace std;

const int MAX_N = 10; // Maximum number of cities (adjust as needed)

// Function to solve TSP using Dynamic Programming
int tsp(int mask, int pos, int dist[MAX_N][MAX_N], int dp[MAX_N][1 << MAX_N], int n) {
    // If all cities have been visited, return to the starting city
    if (mask == (1 << n) - 1) {
        return dist[pos][0];
    }

    // Return cached result if already computed
    if (dp[pos][mask] != -1) {
        return dp[pos][mask];
    }

    int ans = INT_MAX;

    // Try to visit all cities
    for (int city = 0; city < n; city++) {
        // If the city has not been visited yet
        if ((mask & (1 << city)) == 0) {
            // Calculate the cost of visiting this city
            int newAns = dist[pos][city] + tsp(mask | (1 << city), city, dist, dp, n);
            ans = min(ans, newAns);
        }
    }

    return dp[pos][mask] = ans; // Cache the result
}

int main() {
    // Example graph represented as a distance matrix
    int dist[MAX_N][MAX_N] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    int n = 4; // Number of cities
    int dp[MAX_N][1 << MAX_N];

    // Initialize dp array with -1 (indicating no computed value)
    for (int i = 0; i < MAX_N; i++) {
        for (int j = 0; j < (1 << MAX_N); j++) {
            dp[i][j] = -1;
        }
    }

    // Set starting city as city 0 and initial mask as 1 (only city 0 is visited)
    int mask = 1;
    int startCity = 0;

    cout << "The minimum cost to visit all cities is: " << tsp(mask, startCity, dist, dp, n) << endl;

    return 0;
}
