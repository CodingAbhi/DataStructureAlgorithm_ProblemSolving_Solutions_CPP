#include <iostream>
#include <vector>

using namespace std;

class Graph {
    int V; // Number of vertices
    vector<vector<int>> adjList; // Adjacency list
    
    // Helper function for DFS to detect cycles
    bool dfs(int node, vector<bool>& visited, vector<bool>& recStack) {
        // Mark the current node as visited and add it to the recursion stack
        visited[node] = true;
        recStack[node] = true;
        
        // Iterate over all the neighbors of the current node
        for (int neighbor : adjList[node]) {
            // If the neighbor is not visited, recurse
            if (!visited[neighbor]) {
                if (dfs(neighbor, visited, recStack)) {
                    return true;
                }
            }
            // If the neighbor is already in the recursion stack, a cycle is detected
            else if (recStack[neighbor]) {
                return true;
            }
        }
        
        // Remove the current node from the recursion stack
        recStack[node] = false;
        return false;
    }
    
public:
    // Constructor
    Graph(int V) {
        this->V = V;
        adjList.resize(V);
    }
    
    // Function to add an edge to the graph
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
    }
    
    // Function to check if the graph contains a cycle
    bool hasCycle() {
        vector<bool> visited(V, false);  // To keep track of visited nodes
        vector<bool> recStack(V, false); // To keep track of nodes in the recursion stack
        
        // Perform DFS for each node to detect cycles
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                if (dfs(i, visited, recStack)) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0); // This creates a cycle
    g.addEdge(2, 3);
    
    if (g.hasCycle()) {
        cout << "Graph contains a cycle" << endl;
    } else {
        cout << "Graph does not contain a cycle" << endl;
    }
    
    return 0;
}