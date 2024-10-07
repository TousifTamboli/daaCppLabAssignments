#include <iostream>
#include <algorithm> // For qsort function
using namespace std;

struct Edge {
    int src, dest, weight;
};

struct Graph {
    int V, E;
    Edge* edge;
};

struct Subset {
    int parent;
    int rank;
};

// Function prototypes
Graph* createGraph(int V, int E);
int find(Subset subsets[], int i);
void Union(Subset subsets[], int x, int y);
int compareEdges(const void* a, const void* b);
void KruskalMST(Graph* graph);

// Function to create a graph
Graph* createGraph(int V, int E) {
    Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
    graph->edge = new Edge[E];
    return graph;
}

// Function to find the subset of an element
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

// Function to union two subsets
void Union(Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);
    if (subsets[rootX].rank < subsets[rootY].rank) {
        subsets[rootX].parent = rootY;
    } else if (subsets[rootX].rank > subsets[rootY].rank) {
        subsets[rootY].parent = rootX;
    } else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

// Comparison function for qsort
int compareEdges(const void* a, const void* b) {
    Edge* edgeA = (Edge*)a;
    Edge* edgeB = (Edge*)b;
    return edgeA->weight > edgeB->weight;
}

// Function to perform Kruskal's algorithm
void KruskalMST(Graph* graph) {
    int V = graph->V;
    Edge* result = new Edge[V]; // To store the resultant MST
    int e = 0; // Index for result[]
    int i = 0; // Index for sorted edges

    // Step 1: Sort all the edges in non-decreasing order of their weight
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), compareEdges);

    // Create V subsets with single elements
    Subset* subsets = new Subset[V];
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Step 2: Pick the smallest edge and increment the index for next iteration
    while (e < V - 1 && i < graph->E) {
        Edge nextEdge = graph->edge[i++];

        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);

        // If including this edge does not cause a cycle
        if (x != y) {
            result[e++] = nextEdge;
            Union(subsets, x, y);
        }
    }

    // Print the constructed MST
    cout << "Following are the edges in the constructed MST\n";
    for (i = 0; i < e; ++i) {
        cout << result[i].src << " -- " << result[i].dest << " == " << result[i].weight << endl;
    }

    delete[] subsets;
    delete[] result;
}

int main() {
    // Example graph
    int V = 4; // Number of vertices in graph
    int E = 5; // Number of edges in graph
    Graph* graph = createGraph(V, E);

    // Adding edges
    graph->edge[0].src = 0; graph->edge[0].dest = 1; graph->edge[0].weight = 10;
    graph->edge[1].src = 0; graph->edge[1].dest = 2; graph->edge[1].weight = 6;
    graph->edge[2].src = 0; graph->edge[2].dest = 3; graph->edge[2].weight = 5;
    graph->edge[3].src = 1; graph->edge[3].dest = 3; graph->edge[3].weight = 15;
    graph->edge[4].src = 2; graph->edge[4].dest = 3; graph->edge[4].weight = 4;

    // Running Kruskal's algorithm
    KruskalMST(graph);

    // Free allocated memory
    delete[] graph->edge;
    delete graph;

    return 0;
}
