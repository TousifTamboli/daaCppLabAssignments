#include <iostream>
#include <queue>
#include <limits.h>
using namespace std;

const int MAX_N = 4; // Maximum number of cities (adjust as needed)

// Define a structure for each state in the Branch and Bound approach
struct Node {
    int reducedMatrix[MAX_N][MAX_N]; // Reduced matrix
    int path[MAX_N]; // Current path taken
    int cost; // Cost of current path
    int vertex; // Current vertex
};

// Function to create a new node
Node* newNode(int parentMatrix[MAX_N][MAX_N], int path[MAX_N], int cost, int vertex) {
    Node* node = new Node;
    // Copy the reduced matrix
    for (int i = 0; i < MAX_N; ++i) {
        for (int j = 0; j < MAX_N; ++j) {
            node->reducedMatrix[i][j] = parentMatrix[i][j];
        }
    }
    // Copy the path
    for (int i = 0; i < MAX_N; ++i) {
        node->path[i] = path[i];
    }
    // Add the current vertex to the path
    node->path[vertex] = 1;
    // Set the current vertex
    node->vertex = vertex;
    // Set the cost of the current path
    node->cost = cost;
    return node;
}

// Function to calculate the lower bound cost
int calculateCost(int reducedMatrix[MAX_N][MAX_N]) {
    int cost = 0;

    // Reduce each row
    for (int i = 0; i < MAX_N; ++i) {
        int rowMin = INT_MAX;
        for (int j = 0; j < MAX_N; ++j) {
            if (reducedMatrix[i][j] < rowMin && i != j) {
                rowMin = reducedMatrix[i][j];
            }
        }
        if (rowMin != INT_MAX) {
            cost += rowMin;
            for (int j = 0; j < MAX_N; ++j) {
                if (reducedMatrix[i][j] != INT_MAX) {
                    reducedMatrix[i][j] -= rowMin;
                }
            }
        }
    }

    // Reduce each column
    for (int j = 0; j < MAX_N; ++j) {
        int colMin = INT_MAX;
        for (int i = 0; i < MAX_N; ++i) {
            if (reducedMatrix[i][j] < colMin && i != j) {
                colMin = reducedMatrix[i][j];
            }
        }
        if (colMin != INT_MAX) {
            cost += colMin;
            for (int i = 0; i < MAX_N; ++i) {
                if (reducedMatrix[i][j] != INT_MAX) {
                    reducedMatrix[i][j] -= colMin;
                }
            }
        }
    }

    return cost;
}

// Comparison function for priority queue
struct comp {
    bool operator()(const Node* lhs, const Node* rhs) const {
        return lhs->cost > rhs->cost;
    }
};

// Function to solve TSP using Branch and Bound approach
int branchAndBound(int costMatrix[MAX_N][MAX_N]) {
    // Create a priority queue to store live nodes
    priority_queue<Node*, vector<Node*>, comp> pq;

    // Create a root node and calculate its cost
    int path[MAX_N] = {0};
    Node* root = newNode(costMatrix, path, 0, 0);
    root->cost = calculateCost(root->reducedMatrix);

    // Initialize lower bound of the root node
    int minCost = INT_MAX;

    // Add root to the list of live nodes
    pq.push(root);

    // Branch and Bound algorithm
    while (!pq.empty()) {
        // Get the current node with least cost
        Node* minNode = pq.top();
        pq.pop();

        // Current vertex is the last added vertex in path
        int currentVertex = minNode->vertex;

        // If all cities are included in the path
        if (minNode->path[MAX_N-1] == 1 && minNode->reducedMatrix[currentVertex][0] != INT_MAX) {
            // Calculate cost of the complete path
            int currentCost = minNode->cost + minNode->reducedMatrix[currentVertex][0];
            // Update minimum cost, if needed
            minCost = min(minCost, currentCost);
        }

        // Else for each adjacent vertex, calculate cost and add the state to priority queue
        for (int i = 0; i < MAX_N; ++i) {
            if (minNode->reducedMatrix[currentVertex][i] != INT_MAX && minNode->path[i] == 0) {
                // Create a child node and calculate its cost
                Node* child = newNode(minNode->reducedMatrix, minNode->path, minNode->cost, i);
                child->cost += minNode->reducedMatrix[currentVertex][i];

                // Exclude next vertex from current path
                for (int j = 0; j < MAX_N; ++j) {
                    child->reducedMatrix[currentVertex][j] = INT_MAX;
                    child->reducedMatrix[j][i] = INT_MAX;
                }

                // Add path to queue
                pq.push(child);
            }
        }

        // Free the allocated memory
        delete minNode;
    }
    return minCost;
}

int main() {
    // Example cost matrix for 4 cities
    int costMatrix[MAX_N][MAX_N] = {
        {INT_MAX, 10, 15, 20},
        {10, INT_MAX, 35, 25},
        {15, 35, INT_MAX, 30},
        {20, 25, 30, INT_MAX}
    };

    // Solve TSP using Branch and Bound approach
    int minCost = branchAndBound(costMatrix);
    
    // Print the minimum cost
    cout << "Minimum cost of the TSP tour: " << minCost << endl;

    return 0;
}
