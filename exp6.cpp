#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to solve the 0/1 Knapsack problem using Dynamic Programming
int knapsack(int W, int weights[], int values[], int n) {
    int dp[n + 1][W + 1];
    
    // Initialize the dp array
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0; // Base case
            } else if (weights[i - 1] <= w) {
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    return dp[n][W];
}

int main() {
    int values[] = {60, 100, 120};
    int weights[] = {10, 20, 30};
    int W = 50; // Maximum weight capacity of the knapsack
    int n = sizeof(values) / sizeof(values[0]);

    cout << "Maximum value in Knapsack = " << knapsack(W, weights, values, n) << endl;
    return 0;
}
